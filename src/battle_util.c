#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_anim_scripts.h"
//#include "battle_arena.h"
#include "battle_environment.h"
//#include "battle_pyramid.h"
#include "battle_util.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_z_move.h"
#include "battle_gimmick.h"
#include "battle_hold_effects.h"
#include "generational_changes.h"
#include "party_menu.h"
#include "pokemon.h"
//#include "international_string_util.h"
#include "item.h"
#include "util.h"
#include "battle_scripts.h"
#include "random.h"
#include "text.h"
#include "safari_zone.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "test_runner.h"
#include "trig.h"
#include "trainer_slide.h"
#include "window.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "event_data.h"
#include "link.h"
#include "malloc.h"
#include "berry.h"
#include "pokedex.h"
#include "mail.h"
#include "field_weather.h"
#include "constants/hold_effects.h"
#include "constants/abilities.h"
#include "constants/battle_anim.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_string_ids.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/weather.h"
#include "constants/pokemon.h"

static bool32 TryRemoveScreens(enum BattlerId battler);
static bool32 IsUnnerveAbilityOnOpposingSide(enum BattlerId battler);
static bool32 IsNonVolatileStatusBlocked(enum BattlerId battlerDef, enum Ability abilityDef, bool32 abilityAffected, const u8 *battleScript, enum ResultOption option);
static bool32 CanSleepDueToSleepClause(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum ResultOption option);
static bool32 IsOpposingSideEmpty(enum BattlerId battler);
static void ResetParadoxWeatherStat(enum BattlerId battler);
static void ResetParadoxTerrainStat(enum BattlerId battler);
static bool32 CanBattlerFormChange(enum BattlerId battler, enum FormChanges method);
static bool32 IsPowderMoveBlocked(struct BattleContext *ctx);
const u8 *AbsorbedByDrainHpAbility(enum BattlerId battlerDef);
const u8 *AbsorbedByStatIncreaseAbility(enum BattlerId battlerDef, enum Ability abilityDef, enum Stat statId, u32 statAmount);
const u8 *AbsorbedByFlashFire(enum BattlerId battlerDef);
const u8 *AbsorbDoRisingPheonix(enum BattlerId battlerDef);
static bool32 CanAbilityAbsorbMoveType(enum BattlerId battlerDef, enum Type mainMoveType, enum Type SecondaryMoveType);


//customs
static u16 WeightBoostedDamageFormula(enum BattlerId battlerTarget); //new seismic toss boost


ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12(u32 percent);
ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12_Floored(u32 percent);

extern const u8 *const gBattlescriptsForRunningByItem[];
extern const u8 *const gBattlescriptsForUsingItem[];
extern const u8 *const gBattlescriptsForSafariActions[];

/*static const u8 sPkblToEscapeFactor[][3] = {
    {
        [B_MSG_MON_CURIOUS]    = 0,
        [B_MSG_MON_ENTHRALLED] = 0,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 3,
        [B_MSG_MON_ENTHRALLED] = 5,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 2,
        [B_MSG_MON_ENTHRALLED] = 3,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 1,
        [B_MSG_MON_ENTHRALLED] = 2,
        [B_MSG_MON_IGNORED]    = 0
    },{
        [B_MSG_MON_CURIOUS]    = 1,
        [B_MSG_MON_ENTHRALLED] = 1,
        [B_MSG_MON_IGNORED]    = 0
    }
};
static const u8 sGoNearCounterToCatchFactor[] = {4, 3, 2, 1};
static const u8 sGoNearCounterToEscapeFactor[] = {4, 4, 4, 4};
*/

struct BattleWeatherInfo
{
    u16 flag;
    u8 rock;
    u8 abilityStartMessage;
    u8 moveStartMessage;
    u8 endMessage;
    u8 continuesMessage;
    u8 animation;
};

static const struct BattleWeatherInfo sBattleWeatherInfo[BATTLE_WEATHER_COUNT] = {
    [BATTLE_WEATHER_RAIN] =
    {
        .flag = WEATHER_RAIN_NORMAL,
        .rock = HOLD_EFFECT_DAMP_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DRIZZLE,
        .moveStartMessage = B_MSG_STARTED_RAIN,
        .endMessage = B_MSG_WEATHER_END_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_RAIN,
        .animation = B_ANIM_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_RAIN_PRIMAL] =
    {
        .flag = WEATHER_RAIN_PRIMAL,
        .rock = HOLD_EFFECT_DAMP_ROCK,
        .abilityStartMessage = B_MSG_STARTED_PRIMORDIAL_SEA,
        .moveStartMessage = B_MSG_STARTED_RAIN, // Placeholder
        .endMessage = B_MSG_WEATHER_END_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_RAIN,
        .animation = B_ANIM_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_RAIN_DOWNPOUR] =
    {
        .flag = WEATHER_RAIN_NORMAL,
        .rock = HOLD_EFFECT_DAMP_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DRIZZLE,
        .moveStartMessage = B_MSG_STARTED_RAIN,
        .endMessage = B_MSG_WEATHER_END_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_DOWNPOUR,
        .animation = B_ANIM_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_SUN] =
    {
        .flag = WEATHER_SUN_NORMAL,
        .rock = HOLD_EFFECT_HEAT_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DROUGHT,
        .moveStartMessage = B_MSG_STARTED_SUNLIGHT,
        .endMessage = B_MSG_WEATHER_END_SUN,
        .continuesMessage = B_MSG_WEATHER_TURN_SUN,
        .animation = B_ANIM_SUN_CONTINUES,
    },

    [BATTLE_WEATHER_SUN_PRIMAL] =
    {
        .flag = WEATHER_SUN_PRIMAL,
        .rock = HOLD_EFFECT_HEAT_ROCK,
        .abilityStartMessage = B_MSG_STARTED_DESOLATE_LAND,
        .moveStartMessage = B_MSG_STARTED_SUNLIGHT, // Placeholder
        .endMessage = B_MSG_WEATHER_END_SUN,
        .continuesMessage = B_MSG_WEATHER_TURN_SUN,
        .animation = B_ANIM_SUN_CONTINUES,
    },

    [BATTLE_WEATHER_SANDSTORM] =
    {
        .flag = WEATHER_SANDSTORM,
        .rock = HOLD_EFFECT_SMOOTH_ROCK,
        .abilityStartMessage = B_MSG_STARTED_SAND_STREAM,
        .moveStartMessage = B_MSG_STARTED_SANDSTORM,
        .endMessage = B_MSG_WEATHER_END_SANDSTORM,
        .continuesMessage = B_MSG_WEATHER_TURN_SANDSTORM,
        .animation = B_ANIM_SANDSTORM_CONTINUES,
    },

    [BATTLE_WEATHER_HAIL] =
    {
        .flag = WEATHER_HAIL,
        .rock = HOLD_EFFECT_ICY_ROCK,
        .abilityStartMessage = B_MSG_STARTED_HAIL_STORM,
        .moveStartMessage = B_MSG_STARTED_HAIL,
        .endMessage = B_MSG_WEATHER_END_HAIL,
        .continuesMessage = B_MSG_WEATHER_TURN_HAIL,
        .animation = B_ANIM_HAIL_CONTINUES,
    },

    [BATTLE_WEATHER_SNOW] =
    {
        .flag = WEATHER_SNOW,
        .rock = HOLD_EFFECT_ICY_ROCK,
        .abilityStartMessage = B_MSG_STARTED_SNOW_WARNING,
        .moveStartMessage = B_MSG_STARTED_SNOW,
        .endMessage = B_MSG_WEATHER_END_SNOW,
        .continuesMessage = B_MSG_WEATHER_TURN_SNOW,
        .animation = B_ANIM_SNOW_CONTINUES,
    },

    [BATTLE_WEATHER_MOONLIGHT] =
    {
        .flag = WEATHER_MOON,
        .rock = HOLD_EFFECT_MOON_ROCK,
        .endMessage = B_MSG_WEATHER_END_MOON,
        .continuesMessage = B_MSG_WEATHER_TURN_MOON,
        .animation = B_ANIM_MOONLIGHT_SHINES,
    },

    [BATTLE_WEATHER_ACID_RAIN] =
    {
        .flag = WEATHER_ACID_RAIN,
        .rock = HOLD_EFFECT_SLIMY_ROCK,
        .endMessage = B_MSG_WEATHER_END_ACID_RAIN,
        .continuesMessage = B_MSG_WEATHER_TURN_ACID_RAIN,
        .animation = B_ANIM_ACID_RAIN_CONTINUES,
    },

    [BATTLE_WEATHER_FOG] =
    {
        .flag = WEATHER_FOG,
        .rock = HOLD_EFFECT_NONE, //dry ice? smoky rock idk may keep nothing
        .abilityStartMessage = B_MSG_STARTED_DRIZZLE, // Placeholder
        .moveStartMessage = B_MSG_STARTED_RAIN, // Placeholder
        .endMessage = B_MSG_WEATHER_END_FOG,
        .continuesMessage = B_MSG_WEATHER_TURN_FOG,
        .animation = B_ANIM_FOG_CONTINUES,
    },//dont replace just add above moon and acid rain
    //rock moon stone and slimy rock like limestone

    [BATTLE_WEATHER_STRONG_WINDS] =
    {
        .flag = WEATHER_STRONG_WINDS,
        .rock = HOLD_EFFECT_NONE,
        .abilityStartMessage = B_MSG_STARTED_STRONG_WINDS,
        .moveStartMessage = B_MSG_STARTED_RAIN, // Placeholder
        .endMessage = B_MSG_WEATHER_END_STRONG_WINDS,
        .continuesMessage = B_MSG_WEATHER_TURN_STRONG_WINDS,
        .animation = B_ANIM_STRONG_WINDS,
    },
};


u32 GetCurrentBattleWeather(void)
{
    u32 currBattleWeather = 0xFF;

    for (u32 weather = 0; weather < ARRAY_COUNT(sBattleWeatherInfo); weather++)
    {
        if (gBattleWeather & sBattleWeatherInfo[weather].flag)
        {
            currBattleWeather = weather;
            break;
        }
    }

    return currBattleWeather;
}

bool32 EndOrContinueWeather(void)
{
    u32 currBattleWeather = GetCurrentBattleWeather();

    if (currBattleWeather == 0xFF)
        return FALSE;

    if (gBattleStruct->weatherDuration > 0 && --gBattleStruct->weatherDuration == 0)
    {
        gBattleWeather = WEATHER_NONE;
        for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
        {
            gBattleMons[battler].volatiles.weatherAbilityDone = FALSE;
            ResetParadoxWeatherStat(battler);
        }
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[currBattleWeather].endMessage;
        BattleScriptExecute(BattleScript_WeatherFaded);
        return TRUE;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[currBattleWeather].continuesMessage;
        gBattleScripting.animArg1 = sBattleWeatherInfo[currBattleWeather].animation;
        BattleScriptExecute(BattleScript_WeatherContinues);
        return TRUE;
    }

    return FALSE;
}

// Gen5+
static u32 CalcBeatUpPower(void)
{
    u32 species = gBattleStruct->beatUpSpecies[gBattleStruct->beatUpSlot++];
    // FIXME: Why call CalcBeatUpPower when 'beatUpSlot' is OOB?
    if (species == 0xFFFF)
        return 0;
    return (GetSpeciesBaseAttack(species) / 10) + 5;
}

// Gen 3/4
static s32 CalcBeatUpDamage(struct BattleContext *ctx)
{
    u32 partyIndex = gBattleStruct->beatUpSpecies[gBattleStruct->beatUpSlot++];
    struct Pokemon *party = GetBattlerParty(ctx->battlerAtk);
    u32 species = GetMonData(&party[partyIndex], MON_DATA_SPECIES);
    u32 levelFactor = GetMonData(&party[partyIndex], MON_DATA_LEVEL) * 2 / 5 + 2;
    s32 dmg = GetSpeciesBaseAttack(species);

    dmg *= GetMovePower(ctx->move);
    dmg *= levelFactor;
    dmg /= GetSpeciesBaseDefense(gBattleMons[ctx->battlerDef].species);
    dmg = (dmg / 50) + 2;

    if (gProtectStructs[ctx->battlerAtk].helpingHand)
        dmg = dmg * 15 / 10;
    if (ctx->isCrit)
        dmg *= 2;

    return dmg;
}

enum DamageCategory GetReflectDamageMoveDamageCategory(enum BattlerId battler, enum Move move)
{
    u32 damageCategories = GetMoveReflectDamage_DamageCategories(move);

    if (damageCategories == 1u << DAMAGE_CATEGORY_PHYSICAL) // Counter
        return DAMAGE_CATEGORY_PHYSICAL;
    if (damageCategories == 1u << DAMAGE_CATEGORY_SPECIAL) // Mirror Coat
        return DAMAGE_CATEGORY_SPECIAL;

    // Metal Burst / Comeuppance
    if (gProtectStructs[battler].lastHitBySpecialMove)
        return DAMAGE_CATEGORY_SPECIAL;
    else
        return DAMAGE_CATEGORY_PHYSICAL;
}

static bool32 ShouldTeraShellDistortTypeMatchups(enum Move move, enum BattlerId battlerDef, enum Ability abilityDef)
{
    if (!gSpecialStatuses[battlerDef].distortedTypeMatchups
     && gBattleMons[battlerDef].species == SPECIES_TERAPAGOS_TERASTAL
     && gBattleMons[battlerDef].hp == gBattleMons[battlerDef].maxHP
     && !IsBattleMoveStatus(move)
     && abilityDef == ABILITY_TERA_SHELL)
        return TRUE;

    return FALSE;
}

bool32 IsUnnerveBlocked(enum BattlerId battler, enum Item itemId)
{
    if (GetItemPocket(itemId) != POCKET_BERRIES)
        return FALSE;

    if (gBattleScripting.overrideBerryRequirements > 0) // Berries that aren't eaten naturally ignore unnerve
        return FALSE;

    if (IsUnnerveAbilityOnOpposingSide(battler))
        return TRUE;

    return FALSE;
}

//note as one already too strong
//but the idea is literally merge them together
//since calyrex has unnerve
//could keep the new effect to just unnerve itself
//just pass berry block to combined version
static bool32 IsUnnerveAbilityOnOpposingSide(enum BattlerId battler)
{
    for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
    {
        if (battler == battlerDef || IsBattlerAlly(battler, battlerDef))
            continue;

        if (!IsBattlerAlive(battlerDef))
            continue;

        enum Ability ability = GetBattlerAbility(battlerDef);
        switch (ability)
        {
        case ABILITY_UNNERVE:
        case ABILITY_AS_ONE_ICE_RIDER:
        case ABILITY_AS_ONE_SHADOW_RIDER:
            return TRUE;
        default:
            break;
        }
    }

    return FALSE;
}

static inline bool32 IsDragonDartsSecondHit(enum BattlerId battlerAtk, enum Move move)
{
    if (GetBattlerMoveTargetType(battlerAtk, move) != TARGET_SMART)
        return FALSE;

    if (gMultiHitCounter < GetMoveStrikeCount(move))
        return TRUE;

    return FALSE;
}

//may change effects and ability checks
//into single canberedirected
//or cannotberedirected check
bool32 IsAffectedByFollowMe(enum BattlerId battlerAtk, enum BattleSide defSide, enum Move move)
{
    enum Ability ability = GetBattlerAbility(battlerAtk);
    enum BattleMoveEffects effect = GetMoveEffect(move);
    //waiting on word from test if it can be ability redirected
    //need add skydrop as specified exception rather than
    //one that's just immune to all redirection
    if (gSideTimers[defSide].followmeTimer == 0
        || (!IsBattlerAlive(gSideTimers[defSide].followmeTarget) && !IsDragonDartsSecondHit(battlerAtk, move))
        || PreventsRedirection(battlerAtk, move, ability)
        /*|| effect == EFFECT_SNIPE_SHOT
        || effect == EFFECT_SKY_DROP
        || IsAbilityAndRecord(battlerAtk, ability, ABILITY_PROPELLER_TAIL)
        || IsAbilityAndRecord(battlerAtk, ability, ABILITY_STALWART)*/
        )
        return FALSE;

    if (effect == EFFECT_PURSUIT && IsPursuitTargetSet())
        return FALSE;

    //USED ABILITY none as meant to be rage power self affecting
    if (gSideTimers[defSide].followmePowder && !IsAffectedByPowderMove(battlerAtk, ability, ABILITY_NONE, GetBattlerHoldEffect(battlerAtk)))
        return FALSE;

    return TRUE;
}

/*
ok need 3 splits
1 can ability absorb move type -includes dual type move
2 can battler with ability redirect said move
and 3 does incomming move bypass absorb immunity - rejects dual type move takes damage

//issue right now is seems EE just uses 1 function for all parts
except redirection TryHandleAbilityAbsorbMove - was CanAbilityAbsorbMove

//checked my base code and I excluded 
//non elemental effects from redirect
//i.e things like wind moves soud moves etc.
didn't jump in front which I guess works for me
make it just an elemntal thing I guess
*/
//static in EE
bool32 HandleMoveTargetRedirection(void)
{
    u32 redirectorOrderNum = MAX_BATTLERS_COUNT;
    enum MoveTarget moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove);
    enum Type moveType = GetBattleMoveType(gCurrentMove);
    enum Type SecondarymoveType = GetTwoTypedMove2ndType(gCurrentMove);
    enum BattleMoveEffects moveEffect = GetMoveEffect(gCurrentMove);
    enum BattleSide side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));


    if (moveEffect == EFFECT_REFLECT_DAMAGE)
    {
        enum DamageCategory reflectCategory = GetReflectDamageMoveDamageCategory(gBattlerAttacker, gCurrentMove);

        if (reflectCategory == DAMAGE_CATEGORY_PHYSICAL)
            gBattleStruct->moveTarget[gBattlerAttacker] = gProtectStructs[gBattlerAttacker].physicalBattlerId;
        else
            gBattleStruct->moveTarget[gBattlerAttacker] = gProtectStructs[gBattlerAttacker].specialBattlerId;
    }

    //covers rage powder here
    if (IsAffectedByFollowMe(gBattlerAttacker, side, gCurrentMove)
     && (moveTarget == TARGET_SELECTED || moveTarget == TARGET_SMART || moveEffect == EFFECT_REFLECT_DAMAGE)
     && !IsBattlerAlly(gBattlerAttacker, gSideTimers[side].followmeTarget))
    {
        gBattleStruct->moveTarget[gBattlerAttacker] = gBattlerTarget = gSideTimers[side].followmeTarget; // follow me moxie fix
        return TRUE;
    }

    //my change added exceptions so mon even with an absorb ability
    //may be unable to absorb effect
    //the question is if I should change condition to absorb capabiltiy
    //problem is that stops redirection which isn't what I want.
    //if I make function for each effect should be fine
    //one for redirection one for absorption
    //makes sense since I effectively already had that actually...
    //hmm actually no only had things that bypass abroption recently
    //with change to two typed move effect I think???
    //vsonic important took a big search
    //but yes canabsorb was logic for REDIRECTION only
    //not whether if hit they shouldn't absorb it
    //consider should I add that for incapacitating status?
    //would be sleep and freeze sleep is already damn op
    //lil unsure about adding more benefits to it
    //main consideration is if things like lightning rod storm drain etc.
    //are active or passive effects
    //in anime things like pikachu explicitly direct their tail in front of attack
    //or rhyhorn again using their horn to draw in or asborb attacks
    //but then things like storm drain you have pokemon absorbing the element 
    //directly into themselves can go either way
    //if its passive....ok I think purely for sake of balance
    //its too strong for statuses that already completely incapacitate
    //to also turn off immunities so will leave only 
    //true absorption bypass to be two type moves

    //move of absorbable type 
    //not targetting a mon with absorb ability
    //note is meant to redirect from a mon that is unable to absorb effect
    u16 defbattler = gBattleStruct->moveTarget[gBattlerAttacker];
    bool32 currTargetCantAbsorb = CanAbilityAbsorbMoveType(defbattler, moveType, SecondarymoveType) ? FALSE : TRUE;

    //previous versoion of effect
    //had block to ignore status moves
    //removed believe leave only two typed moves
    //to escape absorption
    if (currTargetCantAbsorb
     && IsDoubleBattle()
     && gSideTimers[side].followmeTimer == 0
     && moveTarget != TARGET_USER
     && moveTarget != TARGET_ALL_BATTLERS
     && moveTarget != TARGET_FIELD)
    {
        // Find first battler that redirects the move (in turn order)
        enum Ability abilityAtk = GetBattlerAbility(gBattlerAttacker);
        enum BattlerId battler;
        for (battler = 0; battler < gBattlersCount; battler++)
        {
            if (!IsBattlerAlly(gBattlerAttacker, battler)
                && battler != gBattlerAttacker
                && gBattleStruct->moveTarget[gBattlerAttacker] != battler
                && (CanAbilityAbsorbMoveType(battler, moveType, SecondarymoveType)
                && CanBattlerAbilityDrawInMove(battler))
                //&& ((ability == ABILITY_LIGHTNING_ROD && moveType == TYPE_ELECTRIC)
                // || (ability == ABILITY_STORM_DRAIN && moveType == TYPE_WATER))
                && GetBattlerTurnOrderNum(battler) < redirectorOrderNum
                && !PreventsRedirection(gBattlerAttacker, gCurrentMove, abilityAtk)
                //&& moveEffect != EFFECT_SNIPE_SHOT
                //&& moveEffect != EFFECT_PLEDGE
                //&& !IsAbilityAndRecord(gBattlerAttacker, abilityAtk, ABILITY_PROPELLER_TAIL)
                //&& !IsAbilityAndRecord(gBattlerAttacker, abilityAtk, ABILITY_STALWART)
                )
            {
                redirectorOrderNum = GetBattlerTurnOrderNum(battler);
            }
        }
        if (redirectorOrderNum != MAX_BATTLERS_COUNT && moveEffect != EFFECT_TEATIME)
        {
            enum Ability battlerAbility;
            battler = gBattlerByTurnOrder[redirectorOrderNum];
            battlerAbility = GetBattlerAbility(battler);
            RecordAbilityBattle(battler, battlerAbility);
            //gSpecialStatuses[battler].abilityRedirected = TRUE;
            gBattlerTarget = battler;
            return TRUE;
        }
    }
    return FALSE;
}

void DetermineTarget(enum MoveTarget moveTarget, bool32 overwriteTarget)
{
    if (HandleMoveTargetRedirection())
        return;

    if (IsDoubleBattle() && moveTarget == TARGET_RANDOM)
    {
        gBattlerTarget = SetRandomTarget(gBattlerAttacker);
        if (gAbsentBattlerFlags & (1u << gBattlerTarget)
            && !IsBattlerAlly(gBattlerAttacker, gBattlerTarget))
        {
            gBattlerTarget = GetPartnerBattler(gBattlerTarget);
        }
    }
    else if (moveTarget == TARGET_ALLY)
    {
        if (IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker)) && !gProtectStructs[BATTLE_PARTNER(gBattlerAttacker)].usedAllySwitch)
            gBattlerTarget = BATTLE_PARTNER(gBattlerAttacker);
        else
            gBattlerTarget = gBattlerAttacker;
    }
    else if (IsDoubleBattle() && moveTarget == TARGET_FOES_AND_ALLY)
    {
        for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; gBattlerTarget++)
        {
            if (gBattlerTarget == gBattlerAttacker)
                continue;
            if (IsBattlerAlive(gBattlerTarget))
                break;
        }
    }
    else if (moveTarget == TARGET_USER || moveTarget == TARGET_USER_AND_ALLY)
    {
        gBattlerTarget = gBattlerAttacker;
    }
    else if (overwriteTarget)
    {
        gBattlerTarget = gBattleStruct->moveTarget[gBattlerAttacker];
        if (!IsBattlerAlive(gBattlerTarget)
        && moveTarget != TARGET_OPPONENTS_FIELD
        && IsDoubleBattle()
        && (!IsBattlerAlly(gBattlerAttacker, gBattlerTarget)))
        {
            gBattlerTarget = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
        }
    }
}

static bool32 WasOriginalTargetAlly(enum MoveTarget target)
{
    if (!gProtectStructs[BATTLE_PARTNER(gBattlerAttacker)].usedAllySwitch)
        return FALSE;

    if ((target == TARGET_ALLY || target == TARGET_USER_OR_ALLY) && gBattlerAttacker == gBattlerTarget)
        return TRUE;

    return FALSE;
}

// Functions
void HandleAction_UseMove(void)
{
    u32 i, moveTarget;

    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (gAbsentBattlerFlags & 1u << gBattlerAttacker
     || gBattleStruct->battlerState[gBattlerAttacker].commandingPartner
     || !IsBattlerAlive(gBattlerAttacker))
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }

    gCurrMovePos = gChosenMovePos = gBattleStruct->chosenMovePositions[gBattlerAttacker];

    // choose move
    if (gProtectStructs[gBattlerAttacker].noValidMoves)
    {
        gProtectStructs[gBattlerAttacker].noValidMoves = FALSE;
        gCurrentMove = gChosenMove = MOVE_STRUGGLE;
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(MOVE_STRUGGLE, TARGET_NONE);
    }
    else if (gBattleMons[gBattlerAttacker].volatiles.multipleTurns || gBattleMons[gBattlerAttacker].volatiles.rechargeTimer)
    {
        gCurrentMove = gChosenMove = gLockedMoves[gBattlerAttacker];
    }
    else if (gBattleMons[gBattlerAttacker].volatiles.bindTurns && gBattleMons[gBattlerAttacker].volatiles.bindedMove != MOVE_NONE) //move should already be set I think
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].volatiles.bindedMove;  //bind move
        if (gCurrentMove != MOVE_STRUGGLE)
        gCurrMovePos = gChosenMovePos = gBattleMons[gBattlerAttacker].volatiles.bindMovepos;
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
        //fixed bind not working on first move
    }
    // encore forces you to use the same move
    else if (GetActiveGimmick(gBattlerAttacker) != GIMMICK_Z_MOVE && gBattleMons[gBattlerAttacker].volatiles.encoredMove != MOVE_NONE
             && gBattleMons[gBattlerAttacker].volatiles.encoredMove == gBattleMons[gBattlerAttacker].moves[gBattleMons[gBattlerAttacker].volatiles.encoredMovePos])
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].volatiles.encoredMove;
        gCurrMovePos = gChosenMovePos = gBattleMons[gBattlerAttacker].volatiles.encoredMovePos;
        if (GetConfig(B_ENCORE_TARGET) < GEN_5)
            gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
    }
    // check if the encored move wasn't overwritten
    else if (GetActiveGimmick(gBattlerAttacker) != GIMMICK_Z_MOVE && gBattleMons[gBattlerAttacker].volatiles.encoredMove != MOVE_NONE
          && gBattleMons[gBattlerAttacker].volatiles.encoredMove != gBattleMons[gBattlerAttacker].moves[gBattleMons[gBattlerAttacker].volatiles.encoredMovePos])
    {
        gCurrMovePos = gChosenMovePos = gBattleMons[gBattlerAttacker].volatiles.encoredMovePos;
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gBattleMons[gBattlerAttacker].volatiles.encoredMove = MOVE_NONE;
        gBattleMons[gBattlerAttacker].volatiles.encoredMovePos = 0;
        gBattleMons[gBattlerAttacker].volatiles.encoreTimer = 0;
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
    }
    else if (gBattleMons[gBattlerAttacker].moves[gCurrMovePos] != gChosenMoveByBattler[gBattlerAttacker])
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gBattleStruct->moveTarget[gBattlerAttacker] = GetBattleMoveTarget(gCurrentMove, TARGET_NONE);
    }
    else
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
    }

    if (IsBattlerAlive(gBattlerAttacker))
    {
        if (IsOnPlayerSide(gBattlerAttacker))
            gBattleResults.lastUsedMovePlayer = gCurrentMove;
        else
            gBattleResults.lastUsedMoveOpponent = gCurrentMove;
    }

    // Set dynamic move type.
    SetTypeBeforeUsingMove(gChosenMove, gBattlerAttacker, &gBattleStruct->dynamicMoveType);

    // check Z-Move used
    if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_Z_MOVE && !IsBattleMoveStatus(gCurrentMove) && !IsZMove(gCurrentMove))
    {
        gBattleStruct->categoryOverride = GetMoveCategory(gCurrentMove);
        gCurrentMove = gChosenMove = GetUsableZMove(gBattlerAttacker, gCurrentMove);
    }
    // check Max Move used
    /*else if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_DYNAMAX)
    {
        gBattleStruct->categoryOverride = GetMoveCategory(gCurrentMove);
        gCurrentMove = gChosenMove = GetMaxMove(gBattlerAttacker, gCurrentMove);
    }*/

    gBattleStruct->eventState.atkCanceler = 0;
    ClearDamageCalcResults();
    gMultiHitCounter = 0;
    gBattleCommunication[MISS_TYPE] = 0;

    moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove);
    DetermineTarget(moveTarget, TRUE);


    /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE && gProtectStructs[gBattlerAttacker].palaceUnableToUseMove)
    {
        // Battle Palace, select battle script for failure to use move
        if (!IsBattlerAlive(gBattlerAttacker))
        {
            gCurrentActionFuncId = B_ACTION_FINISHED;
            return;
        }
        else if (gPalaceSelectionBattleScripts[gBattlerAttacker] != NULL)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_INCAPABLE_OF_POWER;
            gBattlescriptCurrInstr = gPalaceSelectionBattleScripts[gBattlerAttacker];
            gPalaceSelectionBattleScripts[gBattlerAttacker] = NULL;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_INCAPABLE_OF_POWER;
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
        }
    }
    else*/ if (IsBattlerAlly(gBattlerAttacker, gBattlerTarget) && !IsBattlerAlive(gBattlerTarget))
    {
        gBattlescriptCurrInstr = BattleScript_FailedFromAtkCanceler;
    }
    else if (WasOriginalTargetAlly(moveTarget))
    {
        gBattlescriptCurrInstr = BattleScript_FailedFromAtkCanceler;
    }
    else
    {
        gBattlescriptCurrInstr = GetMoveBattleScript(gCurrentMove);
    }

    /*if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
        BattleArena_AddMindPoints(gBattlerAttacker);*/

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        gBattleStruct->battlerState[i].wasAboveHalfHp = gBattleMons[i].hp > gBattleMons[i].maxHP / 2;

    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_Switch(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];

    // if switching to a mon that is already on field, cancel switch
    if (!(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(gBattlerAttacker)))
     && IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker))
     && gBattlerPartyIndexes[BATTLE_PARTNER(gBattlerAttacker)] == gBattleStruct->monToSwitchIntoId[gBattlerAttacker])
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gActionSelectionCursor[gBattlerAttacker] = 0;
    gMoveSelectionCursor[gBattlerAttacker] = 0;

    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattleStruct->battlerPartyIndexes[gBattlerAttacker]);

    gBattleScripting.battler = gBattlerAttacker;
    gBattlescriptCurrInstr = BattleScript_ActionSwitch;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;

    if (gBattleResults.playerSwitchesCounter < 255)
        gBattleResults.playerSwitchesCounter++;

    //unsure if will still need this
    if (gBattleMons[gBattlerAttacker].volatiles.transformed) //*warning dont mess w this stuff, transform uses custom logic
    {

        RevertTransformedHP(gBattlerAttacker);
   
        CalculateMonStats(GetBattlerMon(gBattlerAttacker)); //for resetting stats to normal
    }
    else
    TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_SWITCH_OUT, GetBattlerAbility(gBattlerAttacker));
}

//not setup yet
/*void HandleAction_UseItem(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    ClearVariousBattlerFlags(gBattlerAttacker);

    gLastUsedItem = gBattleResources->bufferB[gBattlerAttacker][1] | (gBattleResources->bufferB[gBattlerAttacker][2] << 8);
    if (X_ITEM_FRIENDSHIP_INCREASE > 0
        && GetItemEffectType(gLastUsedItem) == ITEM_EFFECT_X_ITEM
        && !ShouldSkipFriendshipChange())
        UpdateFriendshipFromXItem(gBattlerAttacker);

    gBattlescriptCurrInstr = gBattlescriptsForUsingItem[GetItemBattleUsage(gLastUsedItem) - 1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}*/

//EE moved to this file
#define RUN_LOGIC_PT2 //feels like run logic is all over the place potentially clean up later
bool32 TryRunFromBattle(enum BattlerId battler)
{
    bool32 effect = FALSE;
    u8 holdEffect;
    u8 pyramidMultiplier;
    u8 speedVar;
    enum Ability ability = GetBattlerAbility(battler);

    // If this flag is set, running will never be successful under any circumstances.
    if (FlagGet(B_FLAG_NO_RUNNING))
        return effect;

    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        holdEffect = gEnigmaBerries[battler].holdEffect;
    else
        holdEffect = GetItemHoldEffect(gBattleMons[battler].item);

    gPotentialItemEffectBattler = battler;

    if (holdEffect == HOLD_EFFECT_CAN_ALWAYS_RUN)
    {
        gLastUsedItem = gBattleMons[battler].item;
        gProtectStructs[battler].fleeFlag = FLEE_ITEM;
        effect++;
    }
    //needs to always be able to trigger or game breaks
    else if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))
    {
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
            ++effect;
    }

    else if ((gBattleMons[battler].volatiles.escapePrevention
    || gBattleMons[battler].volatiles.switchBindtimer
    || gBattleMons[battler].volatiles.noRetreat
    || IsBattlerTrappedViaMove(battler))
    && gBattleMons[battler].volatiles.trapSetViaMoldBreaker)
        return FALSE;

    //replace w battler trapped
    //need to look at escape prevent trap
    //speed effect to see what is included
    //does mean liook switch bind count?
    //I know wrap does ok only wrap counts for trap speed drop


    else if (DoesBattlerGetTypeBasedAffinity(ability, battler, ability, TYPE_GHOST, TRUE) && gBattleMons[battler].species != SPECIES_SPIRITOMB)
    {
        ++effect;
    }//vsonic if add ability that gives ghost type affinity keep isbattlertype and add below same as aviator
    
    else if (gBattleMons[battler].volatiles.trappedinStickyweb)
        return FALSE;

    //with ability flag check, can use affinity here
    //Oh nvm I separate it so can have diff msg for ability
    //ok need to figure this out want to be able to flee
    //regardless of smack down but hard grouding effects
    //like iron ball and gravity should still stop it.
    //don't make too strict if I use grouded logic
    //it'll block things ghost types would be able to escape under
    //and its not switching its just run away
    //only relevant for player or for roaming battles
    //so think just gravity and iron ball
    else if ((IS_BATTLER_OF_TYPE(battler, TYPE_FLYING) 
    || IS_BATTLER_OF_TYPE(battler, TYPE_WIND))
    && gBattleMons[battler].ability != ABILITY_AVIATOR
    && !IsFlyingTypeBattlerUnableToFly(battler))
    {
        ++effect;
    }
    else if (gBattleMons[battler].ability == ABILITY_RUN_AWAY)
    {
        gLastUsedAbility = ABILITY_RUN_AWAY;
        gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
        ++effect;
    }
    else if (gBattleMons[battler].ability == ABILITY_DEFEATIST
        && gBattleMons[battler].volatiles.defeatistActivated)
    {
        gLastUsedAbility = ABILITY_DEFEATIST;
        gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
        ++effect;
    }

    //want to remove species check instead making grounded
    //but grounded check includes species, oh wait I removed that lol
    //but is better to use getbattlerability here considering
    //ability flag check, don't want to activate if ability is suprressed
    //just specifically this ability isn't suprressable
    //just more consistent
    //nvm the nvm some abilities have affects that would be surpressed
    //but should not effect the escape portion so this is
    //more appropriate
    else if (gBattleMons[battler].ability == ABILITY_AVIATOR
    && !IsFlyingTypeBattlerUnableToFly(battler))
    {
        gLastUsedAbility = ABILITY_AVIATOR;
        gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
        ++effect;
    }
    //end custom logic

    /*else if (B_GHOSTS_ESCAPE >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
    {
        effect++;
    }
    else if (GetBattlerAbility(battler) == ABILITY_RUN_AWAY)
    {
        if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        {
            gBattleStruct->runTries++;
            pyramidMultiplier = GetPyramidRunMultiplier();
            speedVar = (gBattleMons[battler].speed * pyramidMultiplier) / (gBattleMons[BATTLE_OPPOSITE(battler)].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
            {
                gLastUsedAbility = ABILITY_RUN_AWAY;
                gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
                effect++;
            }
        }
        else
        {
            gLastUsedAbility = ABILITY_RUN_AWAY;
            gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
            effect++;
        }
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_TRAINER_HILL) && gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        effect++;
    }
    else if (CanPlayerForfeitNormalTrainerBattle())
    {
        effect++;
    }*/
    else
    {
        u8 runningFromBattler = BATTLE_OPPOSITE(battler);
        if (!IsBattlerAlive(runningFromBattler))
            runningFromBattler |= BIT_FLANK;

        /*if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        {
            pyramidMultiplier = GetPyramidRunMultiplier();
            speedVar = (gBattleMons[battler].speed * pyramidMultiplier) / (gBattleMons[runningFromBattler].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
                effect++;
        }
        else */if (gBattleMons[battler].speed < gBattleMons[runningFromBattler].speed)
        {
            speedVar = (gBattleMons[battler].speed * 128) / (gBattleMons[runningFromBattler].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
                effect++;
        }
        else // same speed or faster
        {
            effect++;
        }

        gBattleStruct->runTries++;
    }

    if (effect != 0)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        gBattleOutcome = B_OUTCOME_RAN;
    }

    return effect;
}

void HandleAction_Run(void)
{
    s32 i;

    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
    {
        gCurrentTurnActionNumber = gBattlersCount;

        for (i = 0; i < gBattlersCount; i++)
        {
            if (IsOnPlayerSide(i))
            {
                if (gChosenActionByBattler[i] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_LOST;
            }
            else
            {
                if (gChosenActionByBattler[i] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_WON;
            }
        }

        gBattleOutcome |= B_OUTCOME_LINK_BATTLE_RAN;
        //gSaveBlock2Ptr->frontier.disableRecordBattle = TRUE;
    }
    else
    {
        if (IsOnPlayerSide(gBattlerAttacker))
        {
            if (!TryRunFromBattle(gBattlerAttacker)) // failed to run away
            {
                ClearVariousBattlerFlags(gBattlerAttacker);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_ESCAPE_2;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
        }
        else
        {
            if (GetBattlerHoldEffect(gBattlerAttacker) != HOLD_EFFECT_CAN_ALWAYS_RUN
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_RUN_AWAY
             && !CanBattlerEscape(gBattlerAttacker))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_ATTACKER_CANT_ESCAPE;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
            else
            {
                gCurrentTurnActionNumber = gBattlersCount;
                gBattleOutcome = B_OUTCOME_MON_FLED;
            }
        }
    }
}

/*void HandleAction_WatchesCarefully(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[0];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}*/

/*void HandleAction_SafariZoneBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gNumSafariBalls--;
    gLastUsedItem = ITEM_SAFARI_BALL;
    gBattlescriptCurrInstr = BattleScript_SafariBallThrow;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

//seem not used
void HandleAction_ThrowBall(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    //gLastUsedItem = gBallToDisplay;
    if (!IsItemUnique(gLastUsedItem))
    	RemoveBagItem(gLastUsedItem, 1);
    gBattlescriptCurrInstr = BattleScript_BallThrow;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}*/

//not used
/*void HandleAction_ThrowPokeblock(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattleCommunication[MULTISTRING_CHOOSER] = gBattleResources->bufferB[gBattlerAttacker][1] - 1;
    gLastUsedItem = gBattleResources->bufferB[gBattlerAttacker][2];

    if (gBattleResults.pokeblockThrows < 255)
        gBattleResults.pokeblockThrows++;
    if (gBattleStruct->safariPkblThrowCounter < 3)
        gBattleStruct->safariPkblThrowCounter++;
    if (gBattleStruct->safariEscapeFactor > 1)
    {
        // BUG: safariEscapeFactor can become 0 below. This causes the pokeblock throw glitch.
        #ifdef BUGFIX
        if (gBattleStruct->safariEscapeFactor <= sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]])
        #else
        if (gBattleStruct->safariEscapeFactor < sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]])
        #endif
            gBattleStruct->safariEscapeFactor = 1;
        else
            gBattleStruct->safariEscapeFactor -= sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]];
    }

    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[2];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

//not used believe all part of Em safari
//not realevant for FR
void HandleAction_GoNear(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;

    gBattleStruct->safariCatchFactor += sGoNearCounterToCatchFactor[gBattleStruct->safariGoNearCounter];
    if (gBattleStruct->safariCatchFactor > 20)
        gBattleStruct->safariCatchFactor = 20;

    gBattleStruct->safariEscapeFactor += sGoNearCounterToEscapeFactor[gBattleStruct->safariGoNearCounter];
    if (gBattleStruct->safariEscapeFactor > 20)
        gBattleStruct->safariEscapeFactor = 20;

    if (gBattleStruct->safariGoNearCounter < 3)
    {
        gBattleStruct->safariGoNearCounter++;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CREPT_CLOSER;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_GET_CLOSER;
    }
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_SafariZoneRun(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    PlaySE(SE_FLEE);
    gCurrentTurnActionNumber = gBattlersCount;
    gBattleOutcome = B_OUTCOME_RAN;
}*/

/*void HandleAction_WallyBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;

    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])

    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[3];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    gActionsByTurnOrder[1] = B_ACTION_FINISHED;
}*/

/*void HandleAction_TryFinish(void)
{
    if (!HandleFaintedMonActions())
    {
        gBattleStruct->eventState.faintedAction = 0;
        gCurrentActionFuncId = B_ACTION_FINISHED;
    }
}*/

void HandleAction_NothingIsFainted(void)
{
    gCurrentTurnActionNumber++;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;
}

void HandleAction_ActionFinished(void)
{
    u32 i, j;
    bool32 afterYouActive = gSpecialStatuses[gBattlerByTurnOrder[gCurrentTurnActionNumber + 1]].afterYou;
    gBattleStruct->monToSwitchIntoId[gBattlerByTurnOrder[gCurrentTurnActionNumber]] = gSelectedMonPartyId = PARTY_SIZE;
    gCurrentTurnActionNumber++;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    memset(&gSpecialStatuses, 0, sizeof(gSpecialStatuses));

    gCurrentMove = MOVE_NONE;
    ClearDamageCalcResults(); // Relies on gCurrentMove
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleStruct->bouncedMoveIsUsed = FALSE;
    gBattleStruct->snatchedMoveIsUsed = FALSE;
    gBattleScripting.moveendState = 0;
    gBattleCommunication[3] = 0;
    gBattleCommunication[4] = 0;
    gBattleScripting.multihitMoveEffect = 0; //need look in to what is again, if still need
    gBattleResources->battleScriptsStack->size = 0;
    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;

    if (GetConfig(B_RECALC_TURN_AFTER_ACTIONS) >= GEN_8 && !afterYouActive && !gBattleStruct->pledgeMove && !IsPursuitTargetSet())
    {
        // i starts at `gCurrentTurnActionNumber` because we don't want to recalculate turn order for mon that have already
        // taken action. It's been previously increased, which we want in order to not recalculate the turn of the mon that just finished its action

        struct BattleCalcValues calcValues = {0};
        for (i = 0; i < gBattlersCount; i++)
        {
            calcValues.abilities[i] = GetBattlerAbility(i);
            calcValues.holdEffects[i] = GetBattlerHoldEffect(i);
        }
        for (i = gCurrentTurnActionNumber; i < gBattlersCount - 1; i++)
        {
            for (j = i + 1; j < gBattlersCount; j++)
            {
                calcValues.battlerAtk = gBattlerByTurnOrder[i];
                calcValues.battlerDef = gBattlerByTurnOrder[j];

                if (gProtectStructs[calcValues.battlerAtk].quash || gProtectStructs[calcValues.battlerDef].quash
                    || gProtectStructs[calcValues.battlerAtk].shellTrap || gProtectStructs[calcValues.battlerDef].shellTrap)
                    continue;

                // We recalculate order only for action of the same priority. If any action other than switch/move has been taken, they should
                // have been executed before. The only recalculation needed is for moves/switch. Mega evolution is handled in src/battle_main.c/TryChangeOrder
                if ((gActionsByTurnOrder[i] == B_ACTION_USE_MOVE && gActionsByTurnOrder[j] == B_ACTION_USE_MOVE))
                {
                    if (GetWhichBattlerFaster(&calcValues, FALSE) == -1)
                        SwapTurnOrder(i, j);
                }
                else if ((gActionsByTurnOrder[i] == B_ACTION_SWITCH && gActionsByTurnOrder[j] == B_ACTION_SWITCH))
                {
                    if (GetWhichBattlerFaster(&calcValues, TRUE) == -1) // If the actions chosen are switching, we recalc order but ignoring the moves
                        SwapTurnOrder(i, j);
                }
            }
        }
    }
}

// code

ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12(u32 percent)
{
    return (4096 * percent + 50) / 100;
}

ARM_FUNC NOINLINE static uq4_12_t PercentToUQ4_12_Floored(u32 percent)
{
    return (4096 * percent) / 100;
}

static inline uq4_12_t PercentToUQ4_12AddOne(u32 percent)
{
    return uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(percent));
}

uq4_12_t GetTypeBasedBoostMultiplier(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    assertf(gMovesInfo[moveId].effect == EFFECT_TARGET_TYPE_DAMAGE, "not a type boosted move: %S", GetMoveName_(moveId));
    return PercentToUQ4_12(gMovesInfo[moveId].argument.typeBasedPowerBoost.powerMultiplier);
}

u8 GetBattlerForBattleScript(u8 caseId)
{
    u8 ret = 0;
    switch (caseId)
    {
    case BS_TARGET:
        ret = gBattlerTarget;
        break;
    case BS_ATTACKER:
        ret = gBattlerAttacker;
        break;
    case BS_ATTACKER_PARTNER:
        ret = BATTLE_PARTNER(gBattlerAttacker);
        break;
    case BS_EFFECT_BATTLER:
        ret = gEffectBattler;
        break;
    case BS_BATTLER_0:
        ret = 0;
        break;
    case BS_SCRIPTING:
        ret = gBattleScripting.battler;
        break;
    case BS_FAINTED:
        ret = gBattlerFainted;
        break;
    case BS_FAINTED_MULTIPLE_1:
        ret = gBattlerFainted;
        break;
    case BS_FAINTED_MULTIPLE_2:
        ret = BATTLE_PARTNER(gBattlerFainted);
        break;
    case BS_ATTACKER_WITH_PARTNER:
    case BS_ATTACKER_SIDE:
    case BS_TARGET_SIDE:
    case BS_PLAYER1:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        break;
    case BS_OPPONENT1:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        break;
    case BS_PLAYER2:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        break;
    case BS_OPPONENT2:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        break;
    case BS_ABILITY_BATTLER:
        ret = gBattlerAbility;
        break;
    }
    return ret;
}

static void UNUSED MarkAllBattlersForControllerExec(void)
{
    int i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        for (i = 0; i < gBattlersCount; i++)
            MarkBattleControllerMessageOutboundOverLink(i);
    }
    else
    {
        for (i = 0; i < gBattlersCount; i++)
            MarkBattleControllerActiveOnLocal(i);
    }
}


bool32 IsBattlerMarkedForControllerExec(enum BattlerId battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        return IsBattleControllerMessageSynchronizedOverLink(battler);
    else
        return IsBattleControllerActiveOnLocal(battler);
}

void MarkBattlerForControllerExec(enum BattlerId battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        MarkBattleControllerMessageOutboundOverLink(battler);
    else
        MarkBattleControllerActiveOnLocal(battler);
}

void MarkBattlerReceivedLinkData(enum BattlerId battler)
{
    s32 i;

    for (i = 0; i < GetLinkPlayerCount(); i++)
        MarkBattleControllerActiveForPlayer(battler, i);

    MarkBattleControllerMessageSynchronizedOverLink(battler);
}

const u8 *CheckSkyDropState(enum BattlerId battler, enum SkyDropState skyDropState)
{
    const u8 *result = NULL;

    u8 otherSkyDropper = gBattleStruct->skyDropTargets[battler];
    gBattleMons[battler].volatiles.semiInvulnerable = STATE_NONE;

    // Makes both attacker and target's sprites visible
    gSprites[gBattlerSpriteIds[battler]].invisible = FALSE;
    gSprites[gBattlerSpriteIds[otherSkyDropper]].invisible = FALSE;

    // If target was sky dropped in the middle of Outrage/Thrash/Petal Dance,
    // confuse them upon release and display "confused by fatigue" message & animation.
    // Don't do this if this CancelMultiTurnMoves is caused by falling asleep via Yawn.
    if (gBattleMons[otherSkyDropper].volatiles.rampageTurns && skyDropState != SKY_DROP_STATUS_YAWN)
    {
        gBattleMons[otherSkyDropper].volatiles.rampageTurns = 0;

        // If the target can be confused, confuse them.
        // Don't use CanBeConfused, can cause issues in edge cases.
        enum Ability ability = GetBattlerAbility(otherSkyDropper);
        if (!(gBattleMons[otherSkyDropper].volatiles.confusionTurns > 0
            || IsAbilityAndRecord(otherSkyDropper, ability, ABILITY_OWN_TEMPO)
            || IsMistyTerrainAffected(otherSkyDropper, ability, GetBattlerHoldEffect(otherSkyDropper), gFieldStatuses)))
        {
            gBattleMons[otherSkyDropper].volatiles.confusionTurns = RandomUniform(RNG_CONFUSION_TURNS, 2, B_CONFUSION_TURNS); // 2-5 turns
            if (skyDropState == SKY_DROP_ATTACKCANCELER_CHECK)
            {
                gBattleStruct->skyDropTargets[battler] = SKY_DROP_RELEASED_TARGET;
            }
            else if (skyDropState == SKY_DROP_GRAVITY_ON_AIRBORNE)
            {
                // Reapplying STATE_SKY_DROPPED allows for avoiding unecessary messages when Gravity is applied to the target.
                gBattleStruct->skyDropTargets[battler] = SKY_DROP_RELEASED_TARGET;
                gBattleMons[otherSkyDropper].volatiles.semiInvulnerable = STATE_SKY_DROP;
            }
            else if (skyDropState == SKY_DROP_CANCEL_MULTI_TURN_MOVES)
            {
                gBattlerAttacker = otherSkyDropper;
                result = BattleScript_ThrashConfuses;
            }
            else if (skyDropState == SKY_DROP_STATUS_FREEZE_SLEEP)
            {
                gBattlerAttacker = otherSkyDropper;
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                result = BattleScript_ThrashConfuses;
            }
        }
    }

    // Clear skyDropTargets data, unless this CancelMultiTurnMoves is caused by Yawn, attackcanceler, or VARIOUS_GRAVITY_ON_AIRBORNE_MONS
    if (!(gBattleMons[otherSkyDropper].volatiles.rampageTurns) && gBattleStruct->skyDropTargets[battler] < 4)
    {
        gBattleStruct->skyDropTargets[battler] = SKY_DROP_NO_TARGET;
        gBattleStruct->skyDropTargets[otherSkyDropper] = SKY_DROP_NO_TARGET;
    }

    return result;
}

const u8 *CancelMultiTurnMoves(enum BattlerId battler, enum SkyDropState skyDropState)
{
    const u8 *result = NULL;
    gBattleMons[battler].volatiles.uproarTurns = 0;
    gBattleMons[battler].volatiles.bideTurns = 0;

    if (B_RAMPAGE_CANCELLING < GEN_5)
    {
        gBattleMons[battler].volatiles.multipleTurns = 0;
        gBattleMons[battler].volatiles.rampageTurns = 0;
    }
    else if (!gBattleMons[battler].volatiles.rampageTurns
     || gBattleMons[battler].volatiles.rampageTurns > 1)
    {
        gBattleMons[battler].volatiles.multipleTurns = 0;
    }

    // Clear battler's semi-invulnerable bits if they are not held by Sky Drop.
    if (gBattleMons[battler].volatiles.semiInvulnerable != STATE_SKY_DROP)
        gBattleMons[battler].volatiles.semiInvulnerable = STATE_NONE;

    if (gBattleStruct->skyDropTargets[battler] != SKY_DROP_NO_TARGET && gBattleMons[battler].volatiles.semiInvulnerable != STATE_SKY_DROP)
        result = CheckSkyDropState(battler, skyDropState);

    gBattleMons[battler].volatiles.rolloutTimer = 0;
    //gBattleMons[battler].volatiles.furyCutterCounter = 0;

    return result;
}


// Returns TRUE if no other battler after this one in turn order will use a move
bool32 IsLastMonToMove(enum BattlerId battler)
{
    u32 i;
    enum BattlerId battlerTurnOrderNum = GetBattlerTurnOrderNum(battler);

    if (battlerTurnOrderNum >= gBattlersCount - 1)
        return TRUE;

    for (i = battlerTurnOrderNum + 1; i < gBattlersCount; i++)
    {
        u32 otherBattler = gBattlerByTurnOrder[i];
        if (!IsBattlerAlive(otherBattler))
            continue;
        if (gActionsByTurnOrder[i] == B_ACTION_USE_MOVE)
            return FALSE;
    }
    return TRUE;
}

bool32 ShouldDefiantCompetitiveActivate(enum BattlerId battler, enum Ability ability)
{
    enum BattleSide side = GetBattlerSide(battler);
    if (ability != ABILITY_DEFIANT && ability != ABILITY_COMPETITIVE)
        return FALSE;
    // if an ally dropped the stats (except for Sticky Web), don't activate
    if (IsBattlerAlly(gSpecialStatuses[battler].changedStatsBattlerId, battler) && !gBattleScripting.stickyWebStatDrop)
        return FALSE;

    if (GetConfig(B_DEFIANT_STICKY_WEB) >= GEN_9 || !gBattleScripting.stickyWebStatDrop)
        return TRUE;
    // only activate Defiant/Competitive if Web was setup by foe
    return gSideTimers[side].stickyWebBattlerSide != side;
}

void PrepareStringBattle(enum StringID stringId, enum BattlerId battler)
{
    enum BattlerId battlerAbility = GetBattlerAbility(battler);
    u16 targetAbility = GetBattlerAbility(gBattlerTarget);
    // Support for Contrary ability.
    // If a move attempted to raise stat - print "won't increase".
    // If a move attempted to lower stat - print "won't decrease".
    switch (stringId)
    {
    case STRINGID_ATTACKERSSTATROSE:
    case STRINGID_DEFENDERSSTATROSE:
    case STRINGID_STATSWONTINCREASE:
    case STRINGID_USINGITEMSTATOFPKMNROSE:
        if (gBattleScripting.statChanger & STAT_BUFF_NEGATIVE)
            stringId = gStatDownStringIds[gBattleCommunication[MULTISTRING_CHOOSER]];
        break;
    case STRINGID_ATTACKERSSTATFELL:
    case STRINGID_DEFENDERSSTATFELL:
    case STRINGID_STATSWONTDECREASE:
    case STRINGID_USINGITEMSTATOFPKMNFELL:
        if (!(gBattleScripting.statChanger & STAT_BUFF_NEGATIVE))
            stringId = gStatUpStringIds[gBattleCommunication[MULTISTRING_CHOOSER]];
        break;
    case STRINGID_STATSWONTINCREASE2:
        if (battlerAbility == ABILITY_CONTRARY)
            stringId = STRINGID_STATSWONTDECREASE2;
        break;
    case STRINGID_STATSWONTDECREASE2:
        if (battlerAbility == ABILITY_CONTRARY)
            stringId = STRINGID_STATSWONTINCREASE2;
        break;
    case STRINGID_PKMNCUTSATTACKWITH:
        if (GetConfig(B_UPDATED_INTIMIDATE) >= GEN_8
         && targetAbility == ABILITY_RATTLED
         && CompareStat(gBattlerTarget, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN, targetAbility))
        {
            gBattlerAbility = gBattlerTarget;
            BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
            SET_STATCHANGER(STAT_SPEED, 1, FALSE);
        }
        else if (targetAbility == ABILITY_CONTRARY)
        {
            stringId = STRINGID_DEFENDERSSTATROSE;
        }
        break;
    case STRINGID_ITDOESNTAFFECT:
    case STRINGID_PKMNUNAFFECTED:
        TryInitializeTrainerSlideEnemyMonUnaffected(gBattlerTarget);
        break;
    default:
        break;
    }

    if ((stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_DEFENDERSSTATFELL)
     && ShouldDefiantCompetitiveActivate(gBattlerTarget, targetAbility))
    {
        gBattlerAbility = gBattlerTarget;
        BattleScriptCall(BattleScript_AbilityRaisesDefenderStat);
        if (targetAbility == ABILITY_DEFIANT)
            SET_STATCHANGER(STAT_ATK, 2, FALSE);
        else
            SET_STATCHANGER(STAT_SPATK, 2, FALSE);
    }

    BtlController_EmitPrintString(battler, B_COMM_TO_CONTROLLER, stringId);
    MarkBattlerForControllerExec(battler);
}

void ResetSentPokesToOpponentValue(void)
{
    s32 i;
    u32 bits = 0;

    gSentPokesToOpponent[0] = 0;
    gSentPokesToOpponent[1] = 0;

    for (i = 0; i < gBattlersCount; i += 2)
        bits |= 1u << gBattlerPartyIndexes[i];

    for (i = 1; i < gBattlersCount; i += 2)
        gSentPokesToOpponent[(i & BIT_FLANK) >> 1] = bits;
}

void OpponentSwitchInResetSentPokesToOpponentValue(enum BattlerId battler)
{
    s32 i = 0;
    u32 bits = 0;

    if (!IsOnPlayerSide(battler))
    {
        u8 flank = ((battler & BIT_FLANK) >> 1);
        gSentPokesToOpponent[flank] = 0;

        for (i = 0; i < gBattlersCount; i += 2)
        {
            if (!(gAbsentBattlerFlags & (1u << i)))
                bits |= 1u << gBattlerPartyIndexes[i];
        }
        gSentPokesToOpponent[flank] = bits;
    }
}

void UpdateSentPokesToOpponentValue(enum BattlerId battler)
{
    if (!IsOnPlayerSide(battler))
    {
        OpponentSwitchInResetSentPokesToOpponentValue(battler);
    }
    else
    {
        s32 i;
        for (i = 1; i < gBattlersCount; i++)
            gSentPokesToOpponent[(i & BIT_FLANK) >> 1] |= 1u << gBattlerPartyIndexes[battler];
    }
}

void BattleScriptPush(const u8 *bsPtr)
{
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = bsPtr;
}

void BattleScriptPushCursor(void)
{
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = gBattlescriptCurrInstr;
}

void BattleScriptCall(const u8 *bsPtr)
{
    BattleScriptPushCursor();
    gBattlescriptCurrInstr = bsPtr;
}

void BattleScriptPop(void)
{
    if (gBattleResources->battleScriptsStack->size != 0)
        gBattlescriptCurrInstr = gBattleResources->battleScriptsStack->ptr[--gBattleResources->battleScriptsStack->size];
}

bool32 IsGravityPreventingMove(enum Move move)
{
    if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
        return FALSE;

    return IsMoveGravityBanned(move);
}

bool32 IsHealBlockPreventingMove(enum BattlerId battler, enum Move move)
{
    if (!(gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_HEAL_BLOCK))
        return FALSE;

    return IsHealingMove(move);
}

bool32 IsBelchPreventingMove(enum BattlerId battler, enum Move move)
{
    if (GetMoveEffect(move) != EFFECT_BELCH)
        return FALSE;
    
    if (GetItemPocket(gBattleMons[battler].item) == POCKET_BERRIES)
    {
        if (GetBattlerPartyState(battler)->ateBerry == FALSE)
            PREPARE_ITEM_BUFFER(gBattleTextBuff1, gBattleMons[battler].item);
        return FALSE;  //works
    }

    if (GetBattlerAbility(battler) == ABILITY_CHEEK_POUCH)
        return FALSE;

    return !GetBattlerPartyState(battler)->ateBerry;
}

// Dynamax bypasses all selection prevention except Taunt and Assault Vest.
#define DYNAMAX_BYPASS_CHECK    (!IsGimmickSelected(battler, GIMMICK_DYNAMAX) && GetActiveGimmick(battler) != GIMMICK_DYNAMAX)

u32 TrySetCantSelectMoveBattleScript(enum BattlerId battler)
{
    u32 limitations = 0;
    u8 moveId = gBattleResources->bufferB[battler][2] & ~RET_GIMMICK;
    enum Move move = gBattleMons[battler].moves[moveId];
    enum HoldEffect holdEffect = GetBattlerHoldEffect(battler);
    enum Move *choicedMove = &gBattleStruct->choicedMove[battler];
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);

    if (GetConfig(B_ENCORE_TARGET) >= GEN_5
     && DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.encoredMove != move && gBattleMons[battler].volatiles.encoredMove != MOVE_NONE)
    {
        gBattleScripting.battler = battler;
        gCurrentMove = gBattleMons[battler].volatiles.encoredMove;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_EncoredMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_EncoredMove;
            limitations++;
        }
        return limitations;
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.disabledMove == move && move != MOVE_NONE)
    {
        gBattleScripting.battler = battler;
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingDisabledMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingDisabledMove;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && move == gLastMoves[battler] && move != MOVE_STRUGGLE && (gBattleMons[battler].volatiles.torment == TRUE))
    {
        CancelMultiTurnMoves(battler, SKY_DROP_IGNORE);
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingTormentedMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingTormentedMove;
            limitations++;
        }
    }

    if (GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.tauntTimer != 0 && IsBattleMoveStatus(move))
    {
        /*if ((GetActiveGimmick(battler) == GIMMICK_DYNAMAX))
            gCurrentMove = MOVE_MAX_GUARD;
        else*/
            gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveTauntInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveTaunt;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && gBattleMons[battler].volatiles.throatChopTimer > 0 && IsSoundMove(move))
    {
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveThroatChopInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveThroatChop;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && GetImprisonedMovesCount(battler, move))
    {
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingImprisonedMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingImprisonedMove;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && IsGravityPreventingMove(move))
    {
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGravityInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGravity;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && IsHealBlockPreventingMove(battler, move))
    {
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveHealBlockInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveHealBlock;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && GetActiveGimmick(battler) != GIMMICK_Z_MOVE && IsBelchPreventingMove(battler, move))
    {
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedBelchInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedBelch;
            limitations++;
        }
    }

    if (DYNAMAX_BYPASS_CHECK && moveEffect == EFFECT_STUFF_CHEEKS && GetItemPocket(gBattleMons[battler].item) != POCKET_BERRIES)
    {
        gCurrentMove = move;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedStuffCheeksInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedStuffCheeks;
            limitations++;
        }
    }

    if (MoveCantBeUsedTwice(move) && move == gLastResultingMoves[battler])
    {
        gCurrentMove = move;
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gCurrentMove);
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMove;
            limitations++;
        }
    }

    gPotentialItemEffectBattler = battler;
    if (DYNAMAX_BYPASS_CHECK && IsHoldEffectChoice(holdEffect) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = gBattleMons[battler].item;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveChoiceItemInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveChoiceItem;
            limitations++;
        }
    }
    else if (holdEffect == HOLD_EFFECT_ASSAULT_VEST && IsBattleMoveStatus(move) && moveEffect != EFFECT_ME_FIRST)
    {
        /*if ((GetActiveGimmick(battler) == GIMMICK_DYNAMAX))
            gCurrentMove = MOVE_MAX_GUARD;
        else*/
            gCurrentMove = move;
        gLastUsedItem = gBattleMons[battler].item;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVestInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVest;
            limitations++;
        }
    }
    if (DYNAMAX_BYPASS_CHECK && (GetBattlerAbility(battler) == ABILITY_GORILLA_TACTICS) && *choicedMove != MOVE_NONE
              && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = gBattleMons[battler].item;
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGorillaTacticsInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGorillaTactics;
            limitations++;
        }
    }

    if (gBattleMons[battler].pp[moveId] == 0)
    {
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingMoveWithNoPP;
            limitations++;
        }
    }

    if (moveEffect == EFFECT_PLACEHOLDER)
    {
        /*if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedPlaceholderInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else*/
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedPlaceholder;
            limitations++;
        }
    }

    return limitations;
}

u32 CheckMoveLimitations(enum BattlerId battler, u8 unusableMoves, u16 check)
{
    enum Move move;
    enum BattleMoveEffects moveEffect;
    enum HoldEffect holdEffect = GetBattlerHoldEffect(battler);
    enum Move *choicedMove = &gBattleStruct->choicedMove[battler];
    s32 i;

    gPotentialItemEffectBattler = battler;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = gBattleMons[battler].moves[i];
        moveEffect = GetMoveEffect(move);
        // No move
        if (check & MOVE_LIMITATION_ZEROMOVE && move == MOVE_NONE)
            unusableMoves |= 1u << i;
        // No PP
        else if (check & MOVE_LIMITATION_PP && gBattleMons[battler].pp[i] == 0)
            unusableMoves |= 1u << i;
        // Placeholder
        else if (check & MOVE_LIMITATION_PLACEHOLDER && moveEffect == EFFECT_PLACEHOLDER)
            unusableMoves |= 1u << i;
        // Disable
        else if (check & MOVE_LIMITATION_DISABLED && move == gBattleMons[battler].volatiles.disabledMove)
            unusableMoves |= 1u << i;
        // Torment
        else if (check & MOVE_LIMITATION_TORMENTED && move == gLastMoves[battler] && gBattleMons[battler].volatiles.torment == TRUE)
            unusableMoves |= 1u << i;
        // Taunt
        else if (check & MOVE_LIMITATION_TAUNT && gBattleMons[battler].volatiles.tauntTimer && IsBattleMoveStatus(move))
            unusableMoves |= 1u << i;
        // Imprison
        else if (check & MOVE_LIMITATION_IMPRISON && GetImprisonedMovesCount(battler, move))
            unusableMoves |= 1u << i;
        // Bind
        /*
            if (gBattleMons[battler].volatiles.bindTurns && gBattleMons[battler].volatiles.bindedMove != MOVE_NONE)
            if (gBattleMons[battler].volatiles.bindedMove != move) //checking existing moves for locked move, if bind move is move none ex. switch all moves are unusable?
            unusableMoves |= (1u << i); //adds moves to unusable list
        *///vsonic
        // Encore
        else if (check & MOVE_LIMITATION_ENCORE && gBattleMons[battler].volatiles.encoreTimer && gBattleMons[battler].volatiles.encoredMove != move)
            unusableMoves |= 1u << i;
        // Choice Items
        else if (check & MOVE_LIMITATION_CHOICE_ITEM && IsHoldEffectChoice(holdEffect) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
            unusableMoves |= 1u << i;
        // Assault Vest
        else if (check & MOVE_LIMITATION_ASSAULT_VEST && holdEffect == HOLD_EFFECT_ASSAULT_VEST && IsBattleMoveStatus(move) && moveEffect != EFFECT_ME_FIRST)
            unusableMoves |= 1u << i;
        // Gravity
        else if (check & MOVE_LIMITATION_GRAVITY && IsGravityPreventingMove(move))
            unusableMoves |= 1u << i;
        // Heal Block
        else if (check & MOVE_LIMITATION_HEAL_BLOCK && IsHealBlockPreventingMove(battler, move))
            unusableMoves |= 1u << i;
        // Belch
        else if (check & MOVE_LIMITATION_BELCH && IsBelchPreventingMove(battler, move))
            unusableMoves |= 1u << i;
        // Throat Chop
        else if (check & MOVE_LIMITATION_THROAT_CHOP && gBattleMons[battler].volatiles.throatChopTimer > 0 && IsSoundMove(move))
            unusableMoves |= 1u << i;
        // Stuff Cheeks
        else if (check & MOVE_LIMITATION_STUFF_CHEEKS && moveEffect == EFFECT_STUFF_CHEEKS && GetItemPocket(gBattleMons[battler].item) != POCKET_BERRIES)
            unusableMoves |= 1u << i;
        // Gorilla Tactics
        else if (check & MOVE_LIMITATION_CHOICE_ITEM && GetBattlerAbility(battler) == ABILITY_GORILLA_TACTICS && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
            unusableMoves |= 1u << i;
        // Can't Use Twice flag
        else if (check & MOVE_LIMITATION_CANT_USE_TWICE && MoveCantBeUsedTwice(move) && move == gLastResultingMoves[battler])
            unusableMoves |= 1u << i;
    }
    return unusableMoves;
}

#define ALL_MOVES_MASK ((1 << MAX_MON_MOVES) - 1)
bool32 AreAllMovesUnusable(enum BattlerId battler)
{
    u32 unusable = CheckMoveLimitations(battler, 0, MOVE_LIMITATIONS_ALL);

    if (unusable == ALL_MOVES_MASK) // All moves are unusable.
    {
        gProtectStructs[battler].noValidMoves = TRUE;
        gSelectionBattleScripts[battler] = BattleScript_NoMovesLeft;
    }
    else
    {
        gProtectStructs[battler].noValidMoves = FALSE;
    }

    return (unusable == ALL_MOVES_MASK);
}

u8 GetImprisonedMovesCount(enum BattlerId battler, u16 move)
{
    s32 i;
    u8 imprisonedMoves = 0;
    enum BattlerId battlerSide = GetBattlerSide(battler);

    for (i = 0; i < gBattlersCount; i++)
    {
        if (battlerSide != GetBattlerSide(i) && gBattleMons[i].volatiles.imprison)
        {
            s32 j;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (move == gBattleMons[i].moves[j])
                    break;
            }
            if (j < MAX_MON_MOVES)
                imprisonedMoves++;
        }
    }

    return imprisonedMoves;
}


// gBattlerAttacker is the battler that's trying to raise their stats and due to limitations of RandomUniformExcept, cannot be an argument
bool32 MoodyCantRaiseStat(u32 stat)
{
    return CompareStat(gBattlerAttacker, stat, MAX_STAT_STAGE, CMP_EQUAL, GetBattlerAbility(gBattlerAttacker));
}

// gBattlerAttacker is the battler that's trying to lower their stats and due to limitations of RandomUniformExcept, cannot be an argument
bool32 MoodyCantLowerStat(u32 stat)
{
    return stat == GET_STAT_BUFF_ID(gBattleScripting.statChanger) || CompareStat(gBattlerAttacker, stat, MIN_STAT_STAGE, CMP_EQUAL, GetBattlerAbility(gBattlerAttacker));
}

void TryToRevertMimicryAndFlags(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        gBattleMons[battler].volatiles.terrainAbilityDone = FALSE;
        ResetParadoxTerrainStat(battler);
        if (IsAbilityAndRecord(battler, GetBattlerAbility(battler), ABILITY_MIMICRY))
            RESTORE_BATTLER_TYPE(battler);
    }
}

bool32 BattleArenaTurnEnd(void)
{
    if ((gBattleTypeFlags & BATTLE_TYPE_ARENA)
     && gBattleStruct->eventState.arenaTurn == 2
     && IsBattlerAlive(B_POSITION_PLAYER_LEFT) && IsBattlerAlive(B_POSITION_OPPONENT_LEFT))
    {
        for (enum BattlerId battler = 0; battler < 2; battler++)
            CancelMultiTurnMoves(battler, SKY_DROP_IGNORE);

        gBattlescriptCurrInstr = BattleScript_ArenaDoJudgment;
        BattleScriptExecute(BattleScript_ArenaDoJudgment);
        return TRUE;
    }
    return FALSE;
}

// Ingrain, Leech Seed, Strength Sap and Aqua Ring
//also used for general drain effects
s32 GetDrainedBigRootHp(enum BattlerId battler, s32 hp)
{
    if (GetBattlerHoldEffect(battler) == HOLD_EFFECT_BIG_ROOT)
        hp = (hp * 1300) / 1000;
    if (hp == 0)
        hp = 1;

    return hp;
}

//effects together are a 1.69 boost vsonic
s32 MistyTerrainHealBoost(enum BattlerId battler, s32 healamount)
{
    if (IsMistyTerrainAffected(battler, GetBattlerAbility(battler), GetBattlerHoldEffect(battler), gFieldStatuses))
    {
        healamount = (healamount * 1300) / 1000;
        if (healamount == 0)
            healamount = 1;    
    }
    
    return healamount;
}

// Should always be the last check. Otherwise the ability might be wrongly recorded.
bool32 IsAbilityAndRecord(enum BattlerId battler, enum Ability battlerAbility, enum Ability abilityToCheck)
{
    //change to account for using ability return function
    //for abilitytoCheck to avoid false positive
    if (battlerAbility != abilityToCheck
    || battlerAbility == ABILITY_NONE)
        return FALSE;

    RecordAbilityBattle(battler, abilityToCheck);
    return TRUE;
}

bool32 HandleFaintedMonActions(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return FALSE;

    do
    {
        s32 i;
        switch (gBattleStruct->eventState.faintedAction)
        {
        case FAINTED_ACTIONS_NO_MONS_TO_SWITCH:
            gBattleStruct->eventState.faintedActionBattler = 0;
            gBattleStruct->eventState.faintedAction++;
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gAbsentBattlerFlags & (1u << i) && !HasNoMonsToSwitch(i, PARTY_SIZE, PARTY_SIZE))
                    gAbsentBattlerFlags &= ~(1u << i);
            }
            // fall through
        case FAINTED_ACTIONS_GIVE_EXP:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->eventState.faintedActionBattler;
                if (gBattleMons[gBattleStruct->eventState.faintedActionBattler].hp == 0
                 && !(gBattleStruct->givenExpMons & (1u << gBattlerPartyIndexes[gBattleStruct->eventState.faintedActionBattler]))
                 && !(gAbsentBattlerFlags & (1u << gBattleStruct->eventState.faintedActionBattler)))
                {
                    BattleScriptExecute(BattleScript_GiveExp);
                    gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_SET_ABSENT_FLAGS;
                    return TRUE;
                }
            } while (++gBattleStruct->eventState.faintedActionBattler != gBattlersCount);
            gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_WAIT_STATE;
            break;
        case FAINTED_ACTIONS_SET_ABSENT_FLAGS:
            OpponentSwitchInResetSentPokesToOpponentValue(gBattlerFainted);
            if (++gBattleStruct->eventState.faintedActionBattler == gBattlersCount)
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_WAIT_STATE;
            else
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_GIVE_EXP;
            // Don't switch mons until all pokemon performed their actions or the battle's over.
            if (B_FAINT_SWITCH_IN >= GEN_4
                && gBattleOutcome == 0
                && !NoAliveMonsForEitherParty()
                && gCurrentTurnActionNumber != gBattlersCount)
            {
                gAbsentBattlerFlags |= 1u << gBattlerFainted;
                if (gBattleStruct->eventState.faintedAction != FAINTED_ACTIONS_GIVE_EXP)
                    return FALSE;
            }
            break;
        case FAINTED_ACTIONS_WAIT_STATE:
            // Don't switch mons until all pokemon performed their actions or the battle's over.
            if (B_FAINT_SWITCH_IN >= GEN_4
                && gBattleOutcome == 0
                && !NoAliveMonsForEitherParty()
                && gCurrentTurnActionNumber != gBattlersCount)
            {
                return FALSE;
            }
            gBattleStruct->eventState.faintedActionBattler = 0;
            gBattleStruct->eventState.faintedAction++;
            // fall through
        case FAINTED_ACTIONS_HANDLE_FAINTED_MON:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->eventState.faintedActionBattler;
                if (gBattleMons[gBattleStruct->eventState.faintedActionBattler].hp == 0
                 && !(gAbsentBattlerFlags & (1u << gBattleStruct->eventState.faintedActionBattler)))
                {
                    BattleScriptExecute(BattleScript_HandleFaintedMon);
                    gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_HANDLE_NEXT_BATTLER;
                    return TRUE;
                }
            } while (++gBattleStruct->eventState.faintedActionBattler != gBattlersCount);
            gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_MAX_CASE;
            break;
        case FAINTED_ACTIONS_HANDLE_NEXT_BATTLER:
            if (++gBattleStruct->eventState.faintedActionBattler == gBattlersCount)
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_MAX_CASE;
            else
                gBattleStruct->eventState.faintedAction = FAINTED_ACTIONS_HANDLE_FAINTED_MON;
            break;
        case FAINTED_ACTIONS_MAX_CASE:
            break;
        }
    } while (gBattleStruct->eventState.faintedAction != FAINTED_ACTIONS_MAX_CASE);
    return FALSE;
}

//vsonic reworked this
//hmm actually may have just straight up deleted
//had renamed TryClearRageStatuses
void TryClearRageAndFuryCutter(void)
{
    s32 i;
    for (i = 0; i < gBattlersCount; i++)
    {
        enum BattleMoveEffects effect = GetMoveEffect(gChosenMoveByBattler[i]);
        if (gBattleMons[i].volatiles.rage && effect != EFFECT_RAGE)
            gBattleMons[i].volatiles.rage = FALSE;
    }
}

bool32 HasNoMonsToSwitch(enum BattlerId battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2)
{
    u32 i, playerId, flankId;
    struct Pokemon *party;

    if (!IsDoubleBattle())
        return FALSE;

    bool32 isPlayerside = IsOnPlayerSide(battler);

    if (BATTLE_TWO_VS_ONE_OPPONENT && !isPlayerside)
    {
        flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        party = gEnemyParty;

        // Edge case: If both opposing Pokemon were knocked out on the same turn,
        // make sure opponent only sends out the final Pokemon once.
        if (battler == playerId
         && (gHitMarker & HITMARKER_FAINTED(flankId))
         && (gHitMarker & HITMARKER_FAINTED(playerId)))
        {
            u8 count = 0;
            for (i = 0; i < PARTY_SIZE; i++)
                if (IsValidForBattle(&party[i]))
                    count++;

            if (count < 2)
                return TRUE;
        }

        if (partyIdBattlerOn1 == PARTY_SIZE)
            partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
        if (partyIdBattlerOn2 == PARTY_SIZE)
            partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i])
             && i != partyIdBattlerOn1 && i != partyIdBattlerOn2
             && i != gBattleStruct->monToSwitchIntoId[flankId] && i != playerId[gBattleStruct->monToSwitchIntoId])
                break;
        }
        return (i == PARTY_SIZE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        party = GetBattlerParty(battler);
        if (!isPlayerside && WILD_DOUBLE_BATTLE)
        {
            flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);

            if (partyIdBattlerOn1 == PARTY_SIZE)
                partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
            if (partyIdBattlerOn2 == PARTY_SIZE)
                partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

            for (i = 0; i < PARTY_SIZE; i++)
            {
                if (IsValidForBattle(&party[i])
                 && i != partyIdBattlerOn1 && i != partyIdBattlerOn2
                 && i != gBattleStruct->monToSwitchIntoId[flankId] && i != playerId[gBattleStruct->monToSwitchIntoId])
                    break;
            }
            return (i == PARTY_SIZE);
        }
        else
        {
            playerId = ((battler & BIT_FLANK) / 2);
            for (i = playerId * MULTI_PARTY_SIZE; i < playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE; i++)
            {
                if (IsValidForBattle(&party[i]))
                    break;
            }
            return (i == playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE);
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
        {
            if (isPlayerside)
            {
                party = gPlayerParty;
                flankId = GetBattlerMultiplayerId(battler);
                playerId = GetLinkTrainerFlankId(flankId);
            }
            else
            {
                party = gEnemyParty;
                if (battler == 1)
                    playerId = 0;
                else
                    playerId = 1;
            }
        }
        else
        {
            flankId = GetBattlerMultiplayerId(battler);
            party = GetBattlerParty(battler);
            playerId = GetLinkTrainerFlankId(flankId);
        }

        for (i = playerId * MULTI_PARTY_SIZE; i < playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]))
                break;
        }
        return (i == playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE);
    }
    else if ((gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) && !isPlayerside)
    {
        party = gEnemyParty;

        if (battler == 1)
            playerId = 0;
        else
            playerId = MULTI_PARTY_SIZE;

        for (i = playerId; i < playerId + MULTI_PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]))
                break;
        }
        return (i == playerId + 3);
    }
    else
    {
        if (!isPlayerside)
        {
            flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
            party = gEnemyParty;
        }
        else
        {
            flankId = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
            party = gPlayerParty;
        }

        if (partyIdBattlerOn1 == PARTY_SIZE)
            partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
        if (partyIdBattlerOn2 == PARTY_SIZE)
            partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i])
             && i != partyIdBattlerOn1 && i != partyIdBattlerOn2
             && i != gBattleStruct->monToSwitchIntoId[flankId] && i != playerId[gBattleStruct->monToSwitchIntoId])
                break;
        }
        return (i == PARTY_SIZE);
    }
}

bool32 TryChangeBattleWeather(enum BattlerId battler, u32 battleWeatherId, enum Ability ability)
{
    if (gBattleWeather & sBattleWeatherInfo[battleWeatherId].flag)
        return FALSE;
        
    else if (gBattleWeather & WEATHER_PRIMAL_ANY
          && ability != ABILITY_DESOLATE_LAND
          && ability != ABILITY_PRIMORDIAL_SEA
          && ability != ABILITY_DELTA_STREAM)
    {
        return FALSE;
    }

    if (GetConfig(B_ABILITY_WEATHER) < GEN_6 && ability != ABILITY_NONE)
    {
        gBattleWeather = sBattleWeatherInfo[battleWeatherId].flag;
    }
    else
    {
        u32 rock = sBattleWeatherInfo[battleWeatherId].rock;
        gBattleWeather = sBattleWeatherInfo[battleWeatherId].flag;
        if (gBattleWeather & WEATHER_PRIMAL_ANY)
            gBattleStruct->weatherDuration = 0;
        else if (rock != 0 && GetBattlerHoldEffect(battler) == rock)
            gBattleStruct->weatherDuration = 8;
        else
            gBattleStruct->weatherDuration = 5;
    }
    
    if (ability != ABILITY_NONE) // Weather started by Ability
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[battleWeatherId].abilityStartMessage;
        gBattleScripting.animArg1 = sBattleWeatherInfo[battleWeatherId].animation;
    }
    else // Weather started by Move
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = sBattleWeatherInfo[battleWeatherId].moveStartMessage;
    }

    for (u32 i = 0; i < gBattlersCount; i++)
    {
        gBattleMons[i].volatiles.weatherAbilityDone = FALSE;
        ResetParadoxWeatherStat(i);
    }

    return TRUE;
}

bool32 TryChangeBattleTerrain(enum BattlerId battler, u32 statusFlag)
{
    if (gBattleStruct->isSkyBattle)
        return FALSE;

    if (!(gFieldStatuses & statusFlag))
    {
        gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;
        gFieldStatuses |= statusFlag;
        for (u32 i = 0; i < gBattlersCount; i++)
        {
            gBattleMons[i].volatiles.terrainAbilityDone = FALSE;
            ResetParadoxTerrainStat(i);
        }
        if (GetBattlerHoldEffect(battler) == HOLD_EFFECT_TERRAIN_EXTENDER)
            gFieldTimers.terrainTimer = 8;
        else
            gFieldTimers.terrainTimer = 5;
        gBattleScripting.battler = battler;
        return TRUE;
    }

    return FALSE;
}

static void ForewarnChooseMove(enum BattlerId battler)
{
    struct Forewarn {
        enum BattlerId battler;
        u8 power;
        u16 moveId;
    };
    u32 i, j, bestId, count;
    struct Forewarn *data = Alloc(sizeof(struct Forewarn) * MAX_BATTLERS_COUNT * MAX_MON_MOVES);

    // Put all moves
    for (count = 0, i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (IsBattlerAlive(i) && !IsBattlerAlly(i, battler))
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[i].moves[j] == MOVE_NONE)
                    continue;
                data[count].moveId = gBattleMons[i].moves[j];
                data[count].battler = i;
                switch (GetMoveEffect(data[count].moveId))
                {
                case EFFECT_OHKO:
                case EFFECT_SHEER_COLD:
                    data[count].power = 150;
                    break;
                case EFFECT_REFLECT_DAMAGE:
                    data[count].power = 120;
                    break;
                default:
                {
                    u32 movePower = GetMovePower(data[count].moveId);
                    if (movePower == 1)
                        data[count].power = 80;
                    else
                        data[count].power = movePower;
                    break;
                }
                }
                count++;
            }
        }
    }

    for (bestId = 0, i = 1; i < count; i++)
    {
        if (data[i].power > data[bestId].power)
            bestId = i;
        else if (data[i].power == data[bestId].power && Random() & 1)
            bestId = i;
    }

    gEffectBattler = data[bestId].battler;
    PREPARE_MOVE_BUFFER(gBattleTextBuff1, data[bestId].moveId)
    RecordKnownMove(data[bestId].battler, data[bestId].moveId);

    Free(data);
}

bool32 ChangeTypeBasedOnTerrain(enum BattlerId battler)
{
    enum Type battlerType;

    if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
        battlerType = TYPE_ELECTRIC;
    else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
        battlerType = TYPE_GRASS;
    else if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
        battlerType = TYPE_FAIRY;
    else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
        battlerType = TYPE_PSYCHIC;
    else // failsafe
        return FALSE;

    SET_BATTLER_TYPE(battler, battlerType);
    PREPARE_TYPE_BUFFER(gBattleTextBuff1, battlerType);
    return TRUE;
}

static inline u8 GetSideFaintCounter(enum BattleSide side)
{
    return (side == B_SIDE_PLAYER) ? gBattleResults.playerFaintCounter : gBattleResults.opponentFaintCounter;
}

static inline u8 GetBattlerSideFaintCounter(enum BattlerId battler)
{
    return GetSideFaintCounter(GetBattlerSide(battler));
}

// Supreme Overlord adds a x0.1 damage boost for each fainted ally.
static inline uq4_12_t GetSupremeOverlordModifier(enum BattlerId battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(gBattleStruct->supremeOverlordCounter[battler] * 10));
}

bool32 HadMoreThanHalfHpNowDoesnt(enum BattlerId battler)
{
    // Had more than half of hp before, now has less
    return gBattleStruct->battlerState[battler].wasAboveHalfHp
        && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2;
}

u32 NumFaintedBattlersByAttacker(enum BattlerId battlerAtk)
{
    enum BattlerId battler, numMonsFainted = 0;

    for (battler = 0; battler < gBattlersCount; battler++)
    {
        if (battler == battlerAtk)
            continue;

        if (IsBattlerTurnDamaged(battler) && !IsBattlerAlive(battler))
            numMonsFainted++;
    }

    return numMonsFainted;
}

#define ANIM_STAT_HP      0
#define ANIM_STAT_ATK     1
#define ANIM_STAT_DEF     2
#define ANIM_STAT_SPATK   3
#define ANIM_STAT_SPDEF   4
#define ANIM_STAT_SPEED   5
#define ANIM_STAT_ACC     6
#define ANIM_STAT_EVASION 7
void ChooseStatBoostAnimation(enum BattlerId battler)
{
    u32 stat;
    bool32 statBuffMoreThan1 = FALSE;
    u32 static const statsOrder[NUM_BATTLE_STATS] =
    {
        [ANIM_STAT_HP]      = STAT_HP,
        [ANIM_STAT_ATK]     = STAT_ATK,
        [ANIM_STAT_DEF]     = STAT_DEF,
        [ANIM_STAT_SPATK]   = STAT_SPATK,
        [ANIM_STAT_SPDEF]   = STAT_SPDEF,
        [ANIM_STAT_SPEED]   = STAT_SPEED,
        [ANIM_STAT_ACC]     = STAT_ACC,
        [ANIM_STAT_EVASION] = STAT_EVASION,
    };
    gBattleScripting.animArg1 = 0;

    for (stat = 1; stat < NUM_BATTLE_STATS; stat++) // Start loop at 1 to avoid STAT_HP
    {
        if ((gQueuedStatBoosts[battler].stats & (1 << statsOrder[stat])) == 0)
            continue;

        if (!statBuffMoreThan1)
            statBuffMoreThan1 = ((gQueuedStatBoosts[battler].stats & (1 << statsOrder[stat])) > 1);

        if (gBattleScripting.animArg1 != 0) // Already set in a different stat so now boosting multiple stats
            gBattleScripting.animArg1 = (statBuffMoreThan1 ? STAT_ANIM_MULTIPLE_PLUS2 : STAT_ANIM_MULTIPLE_PLUS1);
        else
            gBattleScripting.animArg1 = GET_STAT_BUFF_ID((statsOrder[stat] + 1)) + (statBuffMoreThan1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
    }
}
#undef ANIM_STAT_HP
#undef ANIM_STAT_ATK
#undef ANIM_STAT_DEF
#undef ANIM_STAT_SPATK
#undef ANIM_STAT_SPDEF
#undef ANIM_STAT_SPEED
#undef ANIM_STAT_ACC
#undef ANIM_STAT_EVASION

//effect was separated canabilityblock move handled non absorb abilities
//bullet proof soudproof good as gold
//and tryhandleabsorb was my logic for absorb abilities
//think best case is set that again split off between the two
//recreate canabilityblock move using ctx and put that in 
//canmovebeblockedbytarget replace instances of abilityblockmove
//with that and pair w tryhandleabsorbmove
//as returns true false think will revert name change
//back to canabilityasbrobmove
bool32 CanAbilityBlockMove(struct BattleContext *ctx)
{
    const u8 *battleScript = NULL;

    switch (ctx->abilityDef)
    {
        case ABILITY_SOUNDPROOF:
        if (IsSoundMove(ctx->move))
            battleScript = BattleScript_SoundproofProtected;
        break;
    case ABILITY_BULLETPROOF:
        if (IsBallisticMove(ctx->move))
            battleScript = BattleScript_SoundproofProtected;
        break;
    case ABILITY_GOOD_AS_GOLD:
        if (IsBattleMoveStatus(ctx->move))
        {
            enum MoveTarget target = GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move);
            if (target != TARGET_OPPONENTS_FIELD && target != TARGET_ALL_BATTLERS)
                battleScript = BattleScript_GoodAsGoldActivates;
        }
        break;
    default:
        break;
    }

    if (battleScript == NULL)
        return FALSE;

    if (ctx->runScript)
    {
        gLastUsedAbility = ctx->abilityDef;
        gBattleScripting.battler = gBattlerAbility = ctx->battlerDef;
        BattleScriptCall(battleScript);
    }

    return TRUE;
}

//use separtely with CanAbilityAbsorbMove
bool32 CanMoveBeBlockedByTarget(struct BattleContext *ctx, s32 movePriority)
{
    return CanPsychicTerrainProtectTarget(ctx, movePriority)
        || CanTargetBlockPranksterMove(ctx, movePriority)
        || IsPowderMoveBlocked(ctx)
        || CanAbilityBlockMove(ctx);
}

bool32 CanPsychicTerrainProtectTarget(struct BattleContext *ctx, s32 movePriority)
{
    if (movePriority <= 0
     || !IsPsychicTerrainAffected(ctx->battlerDef, ctx->abilityDef, ctx->holdEffectDef, gFieldStatuses)
     || IsBattlerAlly(ctx->battlerAtk, ctx->battlerDef)
     || GetMoveTarget(ctx->move) == TARGET_ALL_BATTLERS
     || GetMoveTarget(ctx->move) == TARGET_OPPONENTS_FIELD)
        return FALSE;

    if (ctx->runScript)
        BattleScriptCall(BattleScript_MoveUsedPsychicTerrainPrevents);

    return TRUE;
}

bool32 CanTargetBlockPranksterMove(struct BattleContext *ctx, s32 movePriority)
{
    if (movePriority <= 0
     || !IsBattleMoveStatus(ctx->move)
     || !BlocksPrankster(ctx->move, ctx->battlerAtk, ctx->battlerDef, TRUE)
     || (IsBattleMoveStatus(ctx->move) && (ctx->abilityDef == ABILITY_MAGIC_BOUNCE || gProtectStructs[ctx->battlerDef].bounceMove)))
        return FALSE;

    if (ctx->runScript)
        BattleScriptCall(BattleScript_DoesntAffectScripting);

    return TRUE;
}

static bool32 IsPowderMoveBlocked(struct BattleContext *ctx)
{
    if (!IsPowderMove(ctx->move)
     || ctx->battlerAtk == ctx->battlerDef
     || IsAffectedByPowderMove(ctx->battlerDef, ctx->abilityDef, ctx->abilityAtk, ctx->holdEffectDef))
        return FALSE;

    if (ctx->runScript)
    {
        gLastUsedAbility = ctx->abilityDef;
        gBattlerAbility = ctx->battlerDef;
        BattleScriptCall(BattleScript_PowderMoveNoEffect);
    }

    return TRUE;
}

//may rename to draw in or redirect
//oh this is specifically does battler have ability
//that can draw in and absorb move type
//its just specifically applied in the redirection functions
static bool32 CanAbilityAbsorbMoveType(enum BattlerId battlerDef, enum Type mainMoveType, enum Type SecondaryMoveType)
{
    u32 abilityDef = GetBattlerAbility(battlerDef);

    switch (abilityDef)
        {
        case ABILITY_RISING_PHOENIX:
            return ((mainMoveType == TYPE_FIRE || SecondaryMoveType == TYPE_FIRE));
            break;
        case ABILITY_VOLT_DASH:
        case ABILITY_VOLT_ABSORB:
            return ((mainMoveType == TYPE_ELECTRIC || SecondaryMoveType == TYPE_ELECTRIC));
            break;
        case ABILITY_WATER_ABSORB:
        case ABILITY_DRY_SKIN:
            return ((mainMoveType == TYPE_WATER || SecondaryMoveType == TYPE_WATER));
            break;
        case ABILITY_GLACIAL_ICE:
            return ((mainMoveType == TYPE_ICE || SecondaryMoveType == TYPE_ICE));
            break;
        case ABILITY_EROSION:
            return ((mainMoveType == TYPE_ROCK || SecondaryMoveType == TYPE_ROCK));
            break;
        case ABILITY_EARTH_EATER:
            return ((mainMoveType == TYPE_GROUND || SecondaryMoveType == TYPE_GROUND));
            break;
        case ABILITY_MOTOR_DRIVE:
            return ((mainMoveType == TYPE_ELECTRIC || SecondaryMoveType == TYPE_ELECTRIC));
            break;
        case ABILITY_TERAVOLT:
        case ABILITY_LIGHTNING_ROD:
            return ((mainMoveType == TYPE_ELECTRIC || SecondaryMoveType == TYPE_ELECTRIC));
            break;
        case ABILITY_PLASMA_OVERDRIVE:
            return ((mainMoveType == TYPE_ELECTRIC || SecondaryMoveType == TYPE_ELECTRIC))
            || ((mainMoveType == TYPE_FIRE || SecondaryMoveType == TYPE_FIRE));
            break;
        case ABILITY_STORM_DRAIN:
            return ((mainMoveType == TYPE_WATER || SecondaryMoveType == TYPE_WATER));
            break;
        case ABILITY_SAP_SIPPER:
            return ((mainMoveType == TYPE_GRASS || SecondaryMoveType == TYPE_GRASS));
            break;
        case ABILITY_JEWEL_METABOLISM:
            return ((mainMoveType == TYPE_ROCK || SecondaryMoveType == TYPE_ROCK));
            break;
        case ABILITY_WELL_BAKED_BODY:
            return ((mainMoveType == TYPE_FIRE || SecondaryMoveType == TYPE_FIRE));
            break;
        case ABILITY_LAVA_FISSURE:
        case ABILITY_TURBOBLAZE:
        case ABILITY_FLASH_FIRE:
            return ((mainMoveType == TYPE_FIRE || SecondaryMoveType == TYPE_FIRE));
            break;
        default:
            return FALSE;
            break;
        }
}

//need rework this or make inline to check this
//added two typed move effect bypass
//wait realize this isn't a check for absorption
//this is a check for if can redirect to user w absorption ability
//confirmed by searching old repo this is meant to be only 
//a check for if mon with ability can jump in front of a mon that can't absorb the hit

//NOTE**(testing one step at a time, first, just to fix targetting for normal moves, then to see if can use this for statusing exclusion
//-worked for separatng targetting, last check is if I status the absorb mon, will it prevent them from swapping the targetting
//-nice it works perfectly!! if absorb mon is statused according to conditoin, they can't "jump in front of" the attack,
//but if targetted directly they still absorb it!!)

//think may make simpler
//just need add absorb prevention  preceding switch
//ok logic is still done separately in GetBattleMoveTarget function
//so need find and figure out what this is actually use for..?
//looks like I'll need to still use my massive unweidly logic for that...
//I removed the special status in my version can't remember why tho...
//HandleMoveTargetRedirection also relevant
//point of remove is ability redirected special status
//is so move anim actually plays instead of just skip it
//this function does full absorption effect including script logic
//consider rename to attempt absorb move should be final step of trio
//adjust macro and rename function that's it
//pr in coming to address targetting for these etc.
//keep an eye on vsonic
bool32 CanAbilityAbsorbMove(struct BattleContext *ctx)
{
    const u8 *battleScript = NULL;

    bool32 can_absorb = FALSE;

    //do below only if can absorb is true
    if (GetMoveEffect(ctx->move) != EFFECT_TWO_TYPED_MOVE)
        can_absorb = TRUE;

    //double check work as I plan my version
    //only healed for non status moves
    //remembered think was setting up my version to not
    //draw in ally moves, they'll still activate if hit
    //but consider more active ability rather than thoughtless passive
    //which believe is why I was adding in the extra fail conditions in the first place
    //as a sort of counter buff
    //hmm thinking further believe would also like to set fog 
    //as an option to prevent move redirection.
    //i.e can't see attack coming as well so can't get ahead of it

    if (can_absorb)
    {
        switch (ctx->abilityDef)
        {
            //vsonic still in progress
        case ABILITY_RISING_PHOENIX:
            if (ctx->moveType == TYPE_FIRE)
                battleScript = AbsorbDoRisingPheonix(ctx->battlerDef);
                //effect = MOVE_ABSORBED_BY_RISING_PHOENIX_ABILITY;
            break;//do heal and status cleanse & reset dropped stats to default
        case ABILITY_VOLT_DASH:
        case ABILITY_VOLT_ABSORB:
            if (ctx->moveType == TYPE_ELECTRIC)
                battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
            break;
        case ABILITY_WATER_ABSORB:
        case ABILITY_DRY_SKIN:
            if (ctx->moveType == TYPE_WATER)
                battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
            break;
        case ABILITY_GLACIAL_ICE:
            if (ctx->moveType == TYPE_ICE)
                battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
            break;
        case ABILITY_EROSION:
            if (ctx->moveType == TYPE_ROCK)
                battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
            break;
        case ABILITY_EARTH_EATER:
            if (ctx->moveType == TYPE_GROUND)
                battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
            break;
        case ABILITY_NEW_MOON:
            if (IsMoonbasedMove(ctx->move))
                battleScript = AbsorbedByDrainHpAbility(ctx->battlerDef);
            break;
        case ABILITY_MOTOR_DRIVE:
            if (ctx->moveType == TYPE_ELECTRIC)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_SPEED, 1);
            break;
        case ABILITY_TERAVOLT:
        case ABILITY_LIGHTNING_ROD:
            if (ctx->moveType == TYPE_ELECTRIC)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_SPATK, 1);
            break;
        case ABILITY_PLASMA_OVERDRIVE:
            if (ctx->moveType == TYPE_ELECTRIC)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_SPATK, 1);
            else if (ctx->moveType == TYPE_FIRE)
                battleScript = AbsorbedByFlashFire(ctx->battlerDef);
            break;
        case ABILITY_STORM_DRAIN:
            if (ctx->moveType == TYPE_WATER)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_SPATK, 1);
            break;
        case ABILITY_SAP_SIPPER:
            if (ctx->moveType == TYPE_GRASS)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_ATK, 1);
            break;
        case ABILITY_JEWEL_METABOLISM:
            if (ctx->moveType == TYPE_ROCK)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_DEF, 1);
            break;
        case ABILITY_WELL_BAKED_BODY:
            if (ctx->moveType == TYPE_FIRE)
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_DEF, 2);
            break;
        case ABILITY_GALEFORCE:
            if (IsWindMove(ctx->move))
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_SPATK, 1);
            break;
        case ABILITY_DUST_DEVIL:
        case ABILITY_WIND_RIDER:
            if (IsWindMove(ctx->move))
                battleScript = AbsorbedByStatIncreaseAbility(ctx->battlerDef, ctx->abilityDef, STAT_ATK, 1);//EE moves weather moves to target_field instead of user, I would need to add field exclusion to user as well
            break;
        case ABILITY_LAVA_FISSURE:
        case ABILITY_TURBOBLAZE:
        case ABILITY_FLASH_FIRE:
            if (ctx->moveType == TYPE_FIRE)
                battleScript = AbsorbedByFlashFire(ctx->battlerDef);
            break;
        default:
        break;
        }
    }
    

    if (battleScript == NULL)
        return FALSE;

    if (ctx->runScript)
    {
        gLastUsedAbility = ctx->abilityDef;
        gBattleScripting.battler = gBattlerAbility = ctx->battlerDef;
        BattleScriptCall(battleScript);
    }

    return TRUE;
}


const u8 *AbsorbDoRisingPheonix(enum BattlerId battlerDef)
{
    enum BattleSide defSide = GetBattlerSide(battlerDef);

    //status cleanse
    if (gBattleMons[battlerDef].status1 & STATUS1_ANY)
    {
        struct Pokemon *mon = GetBattlerMon(battlerDef);
        HealStatusConditions(mon, STATUS1_ANY, battlerDef);
    }

    if (gBattleMons[battlerDef].volatiles.leechSeed)
        gBattleMons[battlerDef].volatiles.leechSeed = 0;

    //stat reset
    for (u32 i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battlerDef].statStages[i] < DEFAULT_STAT_STAGE)
            gBattleMons[battlerDef].statStages[i] = DEFAULT_STAT_STAGE;
    }

    //hazard removal
    if (AreAnyHazardsOnSide(defSide))
    {
        for (u32 hazardType = HAZARDS_NONE + 1; hazardType < HAZARDS_MAX_COUNT; hazardType++)
        {
            if (IsHazardOnSideAndClear(defSide, hazardType))
            {
                gBattleStruct->numHazards[defSide]--;
                gBattleCommunication[MULTISTRING_CHOOSER] = hazardType;
            }
        }
    }//need do trap removal but will have to wait
    //till figure out setup

    //attempt heal
    if (IsBattlerAtMaxHp(battlerDef) || gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_HEAL_BLOCK)
    {
        return BattleScript_MonMadeMoveUseless;
    }
    else
    {
        SetHealAmount(battlerDef, GetNonDynamaxMaxHP(battlerDef) / 4);
        return BattleScript_MoveHPDrain;
    }
}

const u8 *AbsorbedByDrainHpAbility(enum BattlerId battlerDef)
{
    if (IsBattlerAtMaxHp(battlerDef) || gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_HEAL_BLOCK)
    {
        return BattleScript_MonMadeMoveUseless;
    }
    else
    {
        SetHealAmount(battlerDef, GetNonDynamaxMaxHP(battlerDef) / 4);
        return BattleScript_MoveHPDrain;
    }
}

const u8 *AbsorbedByStatIncreaseAbility(enum BattlerId battlerDef, enum Ability abilityDef, enum Stat statId, u32 statAmount)
{
    if (!CompareStat(battlerDef, statId, MAX_STAT_STAGE, CMP_LESS_THAN, abilityDef))
    {
        return BattleScript_MonMadeMoveUseless;
    }
    else
    {
        SET_STATCHANGER(statId, statAmount, FALSE);
        return BattleScript_MoveStatDrain;
    }
}

const u8 *AbsorbedByFlashFire(enum BattlerId battlerDef)
{
    if (!gBattleMons[battlerDef].volatiles.flashFireBoosted)
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FLASH_FIRE_BOOST;
        gBattleMons[battlerDef].volatiles.flashFireBoosted = TRUE;
        return BattleScript_FlashFireBoost;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FLASH_FIRE_NO_BOOST;
        return BattleScript_FlashFireBoost;
    }
}

static u32 GetFirstBattlerOnSide(enum BattleSide side)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (GetBattlerSide(battler) == side && !IsBattlerAlive(battler))
            return battler;
    }

    return GetBattlerAtPosition(side == B_SIDE_PLAYER ? B_POSITION_PLAYER_LEFT : B_POSITION_OPPONENT_LEFT);
}

static inline bool32 SetStartingFieldStatus(u32 flag, u32 message, u32 anim, u8 time)
{
    if (!(gFieldStatuses & flag))
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = message;
        if (STATUS_FIELD_TERRAIN_ANY & flag)
            gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;
        gFieldStatuses |= flag;
        gBattleScripting.animArg1 = anim;
        SetFieldTimer(flag, time);

        return TRUE;
    }

    return FALSE;
}//review think if time 0 is infinite? 

static inline bool32 SetStartingSideStatus(u32 flag, enum BattleSide side, u32 message, u32 anim, u8 time)
{
    //if flag not already set
    if (!(gSideStatuses[side] & flag))
    {
        gBattlerAttacker = gBattlerTarget = side;
        gBattleCommunication[MULTISTRING_CHOOSER] = message;
        gSideStatuses[side] |= flag;
        gBattleScripting.animArg1 = anim;
        SetSideTimer(flag, side, time);

        return TRUE;
    }

    return FALSE;
}

//believe will have to update with my changes
//to hazards mostly stickyweb once I get figured out
static bool32 SetStartingHazardStatus(enum Hazards hazard, u32 targetSide, u8 layers, enum StartingStatusStringID messageId)
{
    bool32 effect = FALSE;
    u32 setterSide = (targetSide == B_SIDE_PLAYER) ? B_SIDE_OPPONENT : B_SIDE_PLAYER;

    switch (hazard)
    {
    case HAZARDS_SPIKES:
        if (layers != 0)
        {
            if (!IsHazardOnSide(targetSide, HAZARDS_SPIKES))
                PushHazardTypeToQueue(targetSide, HAZARDS_SPIKES);
            gSideTimers[targetSide].spikesAmount = layers;
            effect = TRUE;
        }
        break;
    case HAZARDS_TOXIC_SPIKES:
        if (layers != 0)
        {
            if (!IsHazardOnSide(targetSide, HAZARDS_TOXIC_SPIKES))
                PushHazardTypeToQueue(targetSide, HAZARDS_TOXIC_SPIKES);
            gSideTimers[targetSide].toxicSpikesAmount = layers;
            effect = TRUE;
        }
        break;
    case HAZARDS_STICKY_WEB:
        if (!IsHazardOnSide(targetSide, HAZARDS_STICKY_WEB))
        {
            PushHazardTypeToQueue(targetSide, HAZARDS_STICKY_WEB);
            gSideTimers[targetSide].stickyWebBattlerId = 0xFF;
            gSideTimers[targetSide].stickyWebBattlerSide = setterSide;
            effect = TRUE;
        }
        break;
    case HAZARDS_STEALTH_ROCK:
        if (!IsHazardOnSide(targetSide, HAZARDS_STEALTH_ROCK))
        {
            PushHazardTypeToQueue(targetSide, HAZARDS_STEALTH_ROCK);
            effect = TRUE;
        }
        break;
    case HAZARDS_STEELSURGE:
        if (!IsHazardOnSide(targetSide, HAZARDS_STEELSURGE))
        {
            PushHazardTypeToQueue(targetSide, HAZARDS_STEELSURGE);
            effect = TRUE;
        }
        break;
    case HAZARDS_NONE:
    case HAZARDS_MAX_COUNT:
        break;
    }

    if (effect)
    {
        gBattlerAttacker = GetFirstBattlerOnSide(setterSide);
        gBattleScripting.battler = gBattlerAttacker;
        gBattlerTarget = GetFirstBattlerOnSide(targetSide);
        gBattleCommunication[MULTISTRING_CHOOSER] = messageId;
        BattleScriptPushCursorAndCallback(BattleScript_OverworldHazard);
    }

    return effect;
}

bool32 TryFieldEffects(enum FieldEffectCases caseId)
{
    bool32 effect = FALSE;
    bool32 isTerrain = FALSE;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return FALSE;

    switch (caseId)
    {
    case FIELD_EFFECT_TRAINER_STATUSES:  // starting field/side/etc statuses with a variable
        if (gStartingStatuses.electricTerrain || gStartingStatuses.electricTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_ELECTRIC_TERRAIN,
                        B_MSG_TERRAIN_SET_ELECTRIC,
                        0,
                        gStartingStatuses.electricTerrain ? 0 : 5);
            gStartingStatuses.electricTerrainTemporary = gStartingStatuses.electricTerrain = FALSE;
            isTerrain = TRUE;
            if (effect)
            {
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                return TRUE;
            }
        }
        else if (gStartingStatuses.mistyTerrain || gStartingStatuses.mistyTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_MISTY_TERRAIN,
                        B_MSG_TERRAIN_SET_MISTY,
                        0,
                        gStartingStatuses.mistyTerrain ? 0 : 5);
            gStartingStatuses.mistyTerrainTemporary = gStartingStatuses.mistyTerrain = FALSE;
            isTerrain = TRUE;
            if (effect)
            {
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                return TRUE;
            }
        }
        else if (gStartingStatuses.grassyTerrain || gStartingStatuses.grassyTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_GRASSY_TERRAIN,
                        B_MSG_TERRAIN_SET_GRASSY,
                        0,
                        gStartingStatuses.grassyTerrain ? 0 : 5);
            gStartingStatuses.grassyTerrainTemporary = gStartingStatuses.grassyTerrain = FALSE;
            isTerrain = TRUE;
            if (effect)
            {
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                return TRUE;
            }
        }
        else if (gStartingStatuses.psychicTerrain || gStartingStatuses.psychicTerrainTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_PSYCHIC_TERRAIN,
                        B_MSG_TERRAIN_SET_PSYCHIC,
                        0,
                        gStartingStatuses.psychicTerrain ? 0 : 5);
            gStartingStatuses.psychicTerrainTemporary = gStartingStatuses.psychicTerrain = FALSE;
            isTerrain = TRUE;
        }
        else if (gStartingStatuses.trickRoom || gStartingStatuses.trickRoomTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_TRICK_ROOM,
                        B_MSG_SET_TRICK_ROOM,
                        B_ANIM_TRICK_ROOM,
                        gStartingStatuses.trickRoom ? 0 : 5);
            gStartingStatuses.trickRoomTemporary = gStartingStatuses.trickRoom = FALSE;
        }
        else if (gStartingStatuses.magicRoom || gStartingStatuses.magicRoomTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_MAGIC_ROOM,
                        B_MSG_SET_MAGIC_ROOM,
                        B_ANIM_MAGIC_ROOM,
                        gStartingStatuses.magicRoom ? 0 : 5);
            gStartingStatuses.magicRoomTemporary = gStartingStatuses.magicRoom = FALSE;
        }
        else if (gStartingStatuses.wonderRoom || gStartingStatuses.wonderRoomTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_WONDER_ROOM,
                        B_MSG_SET_WONDER_ROOM,
                        B_ANIM_WONDER_ROOM,
                        gStartingStatuses.wonderRoom ? 0 : 5);
            gStartingStatuses.wonderRoomTemporary = gStartingStatuses.wonderRoom = FALSE;
        }
        else if (gStartingStatuses.iondeluge || gStartingStatuses.iondelugeTemporary)
        {
            effect = SetStartingFieldStatus(
                        STATUS_FIELD_WONDER_ROOM,
                        B_MSG_SET_WONDER_ROOM,
                        B_ANIM_WONDER_ROOM,
                        gStartingStatuses.iondeluge ? 0 : B_ION_DELUGE_TIMER);
            gStartingStatuses.iondeluge = gStartingStatuses.iondeluge = FALSE;
        }
        else if (gStartingStatuses.tailwindPlayer || gStartingStatuses.tailwindPlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_TAILWIND,
                        B_SIDE_PLAYER,
                        B_MSG_SET_TAILWIND,
                        B_ANIM_TAILWIND,
                        gStartingStatuses.tailwindPlayer ? 0 : (B_TAILWIND_TURNS >= GEN_5 ? 4 : 3));
            gStartingStatuses.tailwindPlayerTemporary = gStartingStatuses.tailwindPlayer = FALSE;
        }
        else if (gStartingStatuses.tailwindOpponent || gStartingStatuses.tailwindOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_TAILWIND,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_TAILWIND,
                        B_ANIM_TAILWIND,
                        gStartingStatuses.tailwindOpponent ? 0 : (B_TAILWIND_TURNS >= GEN_5 ? 4 : 3));
            gStartingStatuses.tailwindOpponentTemporary = gStartingStatuses.tailwindOpponent = FALSE;
        }
        else if (gStartingStatuses.rainbowPlayer || gStartingStatuses.rainbowPlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_RAINBOW,
                        B_SIDE_PLAYER,
                        B_MSG_SET_RAINBOW,
                        B_ANIM_RAINBOW,
                        gStartingStatuses.rainbowPlayer ? 0 : 4);
            gStartingStatuses.rainbowPlayerTemporary = gStartingStatuses.rainbowPlayer = FALSE;
        }
        else if (gStartingStatuses.rainbowOpponent || gStartingStatuses.rainbowOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_RAINBOW,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_RAINBOW,
                        B_ANIM_RAINBOW,
                        gStartingStatuses.rainbowOpponent ? 0 : 4);
            gStartingStatuses.rainbowOpponentTemporary = gStartingStatuses.rainbowOpponent = FALSE;
        }
        else if (gStartingStatuses.seaOfFirePlayer || gStartingStatuses.seaOfFirePlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SEA_OF_FIRE,
                        B_SIDE_PLAYER,
                        B_MSG_SET_SEA_OF_FIRE,
                        B_ANIM_SEA_OF_FIRE,
                        gStartingStatuses.seaOfFirePlayer ? 0 : 4);
            gStartingStatuses.seaOfFirePlayerTemporary = gStartingStatuses.seaOfFirePlayer = FALSE;
        }
        else if (gStartingStatuses.seaOfFireOpponent || gStartingStatuses.seaOfFireOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SEA_OF_FIRE,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_SEA_OF_FIRE,
                        B_ANIM_SEA_OF_FIRE,
                        gStartingStatuses.seaOfFireOpponent ? 0 : 4);
            gStartingStatuses.seaOfFireOpponentTemporary = gStartingStatuses.seaOfFireOpponent = FALSE;
        }
        else if (gStartingStatuses.swampPlayer || gStartingStatuses.swampPlayerTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SWAMP,
                        B_SIDE_PLAYER,
                        B_MSG_SET_SWAMP,
                        B_ANIM_SWAMP,
                        gStartingStatuses.swampPlayer ? 0 : 4);
            gStartingStatuses.swampPlayerTemporary = gStartingStatuses.swampPlayer = FALSE;
        }
        else if (gStartingStatuses.swampOpponent || gStartingStatuses.swampOpponentTemporary)
        {
            effect = SetStartingSideStatus(
                        SIDE_STATUS_SWAMP,
                        B_SIDE_OPPONENT,
                        B_MSG_SET_SWAMP,
                        B_ANIM_SWAMP,
                        gStartingStatuses.swampOpponent ? 0 : 4);
            gStartingStatuses.swampOpponentTemporary = gStartingStatuses.swampOpponent = FALSE;
        }
        // Hazards - Spikes
        else if (gStartingStatuses.spikesPlayerL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_PLAYER, 1, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesPlayerL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesPlayerL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_PLAYER, 2, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesPlayerL2 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesPlayerL3)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_PLAYER, 3, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesPlayerL3 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesOpponentL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_OPPONENT, 1, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesOpponentL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesOpponentL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_OPPONENT, 2, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesOpponentL2 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.spikesOpponentL3)
        {
            effect = SetStartingHazardStatus(HAZARDS_SPIKES, B_SIDE_OPPONENT, 3, B_MSG_SET_SPIKES);
            gStartingStatuses.spikesOpponentL3 = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Toxic Spikes
        else if (gStartingStatuses.toxicSpikesPlayerL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_PLAYER, 1, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesPlayerL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.toxicSpikesPlayerL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_PLAYER, 2, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesPlayerL2 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.toxicSpikesOpponentL1)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_OPPONENT, 1, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesOpponentL1 = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.toxicSpikesOpponentL2)
        {
            effect = SetStartingHazardStatus(HAZARDS_TOXIC_SPIKES, B_SIDE_OPPONENT, 2, B_MSG_SET_POISON_SPIKES);
            gStartingStatuses.toxicSpikesOpponentL2 = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Sticky Web
        else if (gStartingStatuses.stickyWebPlayer)
        {
            effect = SetStartingHazardStatus(HAZARDS_STICKY_WEB, B_SIDE_PLAYER, 1, B_MSG_SET_STICKY_WEB);
            gStartingStatuses.stickyWebPlayer = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.stickyWebOpponent)
        {
            effect = SetStartingHazardStatus(HAZARDS_STICKY_WEB, B_SIDE_OPPONENT, 1, B_MSG_SET_STICKY_WEB);
            gStartingStatuses.stickyWebOpponent = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Stealth Rock
        else if (gStartingStatuses.stealthRockPlayer)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEALTH_ROCK, B_SIDE_PLAYER, 1, B_MSG_SET_STEALTH_ROCK);
            gStartingStatuses.stealthRockPlayer = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.stealthRockOpponent)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEALTH_ROCK, B_SIDE_OPPONENT, 1, B_MSG_SET_STEALTH_ROCK);
            gStartingStatuses.stealthRockOpponent = FALSE;
            if (effect)
                return TRUE;
        }
        // Hazards - Steelsurge
        else if (gStartingStatuses.sharpSteelPlayer)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEELSURGE, B_SIDE_PLAYER, 1, B_MSG_SET_SHARP_STEEL);
            gStartingStatuses.sharpSteelPlayer = FALSE;
            if (effect)
                return TRUE;
        }
        else if (gStartingStatuses.sharpSteelOpponent)
        {
            effect = SetStartingHazardStatus(HAZARDS_STEELSURGE, B_SIDE_OPPONENT, 1, B_MSG_SET_SHARP_STEEL);
            gStartingStatuses.sharpSteelOpponent = FALSE;
            if (effect)
                return TRUE;
        }
        if (effect)
        {
            if (isTerrain)
                BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            else
                BattleScriptPushCursorAndCallback(BattleScript_OverworldStatusStarts);
        }

        break;
    case FIELD_EFFECT_OVERWORLD_TERRAIN:   // terrain starting from overworld weather
        if (B_THUNDERSTORM_TERRAIN == TRUE
         && !(gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
         && GetCurrentWeather() == OVERWORLD_WEATHER_RAIN_THUNDERSTORM)
        {
            // overworld weather started rain, so just do electric terrain anim
            gFieldStatuses = STATUS_FIELD_ELECTRIC_TERRAIN;
            gFieldTimers.terrainTimer = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_TERRAIN_SET_ELECTRIC;
            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect = TRUE;
        }
        /*else if (B_OVERWORLD_FOG >= GEN_8
              && (GetCurrentWeather() == OVERWORLD_WEATHER_FOG_HORIZONTAL || GetCurrentWeather() == OVERWORLD_WEATHER_FOG_DIAGONAL)
              && !(gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN))
        {
            gFieldStatuses = STATUS_FIELD_MISTY_TERRAIN;
            gFieldTimers.terrainTimer = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_TERRAIN_SET_MISTY;
            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect = TRUE;
        }//think change to fog weather vsonic
        break;*/
        break;
    case FIELD_EFFECT_OVERWORLD_WEATHER:
        if (!(gBattleTypeFlags & BATTLE_TYPE_RECORDED))
        {
            switch (GetCurrentWeather())
            {
            case OVERWORLD_WEATHER_RAIN:
            case OVERWORLD_WEATHER_RAIN_THUNDERSTORM:
            case OVERWORLD_WEATHER_DOWNPOUR:
                if (!(gBattleWeather & WEATHER_RAIN))
                {
                    gBattleWeather = WEATHER_RAIN_NORMAL;
                    gBattleScripting.animArg1 = B_ANIM_RAIN_CONTINUES;
                    effect = TRUE;
                }
                break;
            case OVERWORLD_WEATHER_ACID_RAIN:
                if (!(gBattleWeather & WEATHER_ACID_RAIN))
                {
                    gBattleWeather = WEATHER_ACID_RAIN;
                    gBattleScripting.animArg1 = B_ANIM_ACID_RAIN_CONTINUES;
                    effect = TRUE;
                }
                break;
            case OVERWORLD_WEATHER_SANDSTORM:
                if (!(gBattleWeather & WEATHER_SANDSTORM))
                {
                    gBattleWeather = WEATHER_SANDSTORM;
                    gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                    effect = TRUE;
                }
                break;
            case OVERWORLD_WEATHER_DROUGHT:
                if (!(gBattleWeather & WEATHER_SUN))
                {
                    gBattleWeather = WEATHER_SUN_NORMAL;
                    gBattleScripting.animArg1 = B_ANIM_SUN_CONTINUES;
                    effect = TRUE;
                }
                break;
            case OVERWORLD_WEATHER_SNOW:
                if (!(gBattleWeather & WEATHER_ICY_ANY))
                {
                    if (B_OVERWORLD_SNOW >= GEN_9)
                    {
                        gBattleWeather = WEATHER_SNOW;
                        gBattleScripting.animArg1 = B_ANIM_SNOW_CONTINUES;
                    }
                    else
                    {
                        gBattleWeather = WEATHER_HAIL;
                        gBattleScripting.animArg1 = B_ANIM_HAIL_CONTINUES;
                    }
                    effect = TRUE;
                }
                break;
            case OVERWORLD_WEATHER_FOG_DIAGONAL:
            case OVERWORLD_WEATHER_FOG_HORIZONTAL:
            case OVERWORLD_WEATHER_DARKFOG_HORIZONTAL:
                if (!(gBattleWeather & WEATHER_FOG))
                {
                    gBattleWeather = WEATHER_FOG;
                    gBattleScripting.animArg1 = B_ANIM_FOG_CONTINUES;
                    effect = TRUE;
                }
                break;
            }
        }
        if (effect)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = GetCurrentWeather();
            BattleScriptPushCursorAndCallback(BattleScript_OverworldWeatherStarts);
        }
        break;
    }

    return effect;
}

u32 AbilityBattleEffects(enum AbilityEffect caseID, enum BattlerId battler, enum Ability ability, enum Move move, bool32 shouldAbilityTrigger)
{
    u32 effect = 0;
    enum Type moveType = 0;
    u32 side = 0;
    u32 i = 0, j = 0;
    u32 partner = 0;
    u32 speciesForm = SPECIES_NONE;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return 0;

    if (gBattlerAttacker >= gBattlersCount)
        gBattlerAttacker = battler;

    if (ability)
        gLastUsedAbility = ability;
    else
        gLastUsedAbility = GetBattlerAbility(battler);

    if (move == MOVE_NONE)
        move = gCurrentMove;

    moveType = GetBattleMoveType(move);

    switch (caseID)
    {
    case ABILITYEFFECT_ON_SWITCHIN:
        gBattleScripting.battler = battler;
        switch (gLastUsedAbility)
        {
        case ABILITY_TRACE:
            {
                u32 chosenTarget;
                u32 target1;
                u32 target2;

                if (GetBattlerHoldEffectIgnoreAbility(battler) == HOLD_EFFECT_ABILITY_SHIELD)
                    break;

                side = (BATTLE_OPPOSITE(GetBattlerPosition(battler))) & BIT_SIDE;
                target1 = GetBattlerAtPosition(side);
                target2 = GetBattlerAtPosition(side + BIT_FLANK);
                if (IsDoubleBattle())
                {
                    if (!gAbilitiesInfo[gBattleMons[target1].ability].cantBeTraced && gBattleMons[target1].hp != 0
                        && !gAbilitiesInfo[gBattleMons[target2].ability].cantBeTraced && gBattleMons[target2].hp != 0)
                        chosenTarget = GetBattlerAtPosition((RandomPercentage(RNG_TRACE, 50) * 2) | side), effect++;
                    else if (!gAbilitiesInfo[gBattleMons[target1].ability].cantBeTraced && gBattleMons[target1].hp != 0)
                        chosenTarget = target1, effect++;
                    else if (!gAbilitiesInfo[gBattleMons[target2].ability].cantBeTraced && gBattleMons[target2].hp != 0)
                        chosenTarget = target2, effect++;
                }
                else
                {
                    if (!gAbilitiesInfo[gBattleMons[target1].ability].cantBeTraced && gBattleMons[target1].hp != 0)
                        chosenTarget = target1, effect++;
                }

                if (effect != 0)
                {
                    BattleScriptCall(BattleScript_TraceActivates);
                    gBattleStruct->tracedAbility[battler] = gLastUsedAbility = gBattleMons[chosenTarget].ability;
                    RecordAbilityBattle(chosenTarget, gLastUsedAbility); // Record the opposing battler has this ability
                    PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, chosenTarget, gBattlerPartyIndexes[chosenTarget])
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff2, gLastUsedAbility)
                }
            }
            break;
        case ABILITY_IMPOSTER:
            if (gBattleStruct->battlerState[battler].switchIn)
            {
                u32 diagonalBattler = BATTLE_OPPOSITE(battler);
                if (IsDoubleBattle())
                    diagonalBattler = BATTLE_PARTNER(diagonalBattler);

                // Imposter only activates when the battler first switches in
                if (!gBattleMons[battler].volatiles.overwrittenAbility
                    && IsBattlerAlive(diagonalBattler)
                    && !gBattleMons[diagonalBattler].volatiles.substitute
                    && !gBattleMons[diagonalBattler].volatiles.transformed
                    && !gBattleMons[battler].volatiles.transformed
                    && gBattleStruct->illusion[diagonalBattler].state != ILLUSION_ON
                    && !IsSemiInvulnerable(diagonalBattler, EXCLUDE_COMMANDER))
                {
                    SaveBattlerAttacker(gBattlerAttacker);
                    SaveBattlerTarget(gBattlerTarget);
                    gBattlerAttacker = battler;
                    gBattlerTarget = diagonalBattler;
                    BattleScriptCall(BattleScript_ImposterActivates);
                    effect++;
                }
            }
            break;
        case ABILITY_MOLD_BREAKER:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_MOLDBREAKER;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_TERAVOLT:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_TERAVOLT;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_TURBOBLAZE:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_TURBOBLAZE;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_SLOW_START:
            if (shouldAbilityTrigger)
            {
                //vsonic use battle party stuff singleuseability
                SetSingleUseAbilityValues(battler, gLastUsedAbility);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_SLOWSTART;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_CURIOUS_MEDICINE:
            if (shouldAbilityTrigger
             && IsDoubleBattle()
             && IsBattlerAlive(BATTLE_PARTNER(battler))
             && TryResetBattlerStatChanges(BATTLE_PARTNER(battler)))
            {
                gEffectBattler = BATTLE_PARTNER(battler);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_CURIOUS_MEDICINE;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_PASTEL_VEIL:
            if (shouldAbilityTrigger)
            {
                SaveBattlerTarget(gBattlerTarget);
                gBattlerTarget = battler;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_PASTEL_VEIL;
                BattleScriptCall(BattleScript_PastelVeilActivates);
                effect++;
            }
            break;//vsonic
        case ABILITY_ANTICIPATION:
            if (shouldAbilityTrigger)
            {
                struct BattleContext ctx = {0};
                uq4_12_t modifier = UQ_4_12(1.0);
                for (i = 0; i < MAX_BATTLERS_COUNT; i++)
                {
                    if (IsBattlerAlive(i) && !IsBattlerAlly(i, battler))
                    {
                        for (j = 0; j < MAX_MON_MOVES; j++)
                        {
                            move = gBattleMons[i].moves[j];
                            enum BattleMoveEffects moveEffect = GetMoveEffect(move);
                            moveType = GetBattleMoveType(move);

                            ctx.battlerAtk = i;
                            ctx.battlerDef = battler;
                            ctx.move = ctx.chosenMove = move;
                            ctx.moveType = moveType;
                            ctx.isAnticipation = TRUE;
                            modifier = CalcTypeEffectivenessMultiplier(&ctx);

                            if (modifier >= SUPER_EFFECTIVE
                             || moveEffect == EFFECT_OHKO
                             || moveEffect == EFFECT_SHEER_COLD)
                            {
                                effect++;
                                break;
                            }
                        }
                    }
                }

                if (effect != 0)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_ANTICIPATION;
                    BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                }
            }
            break;
        case ABILITY_FRISK:
            if (shouldAbilityTrigger)
            {
                BattleScriptCall(BattleScript_FriskActivates);
                effect++;
            }
            return effect; // Note: It returns effect as to not record the ability if Frisk does not activate.
        case ABILITY_FOREWARN:
            if (shouldAbilityTrigger)
            {
                ForewarnChooseMove(battler);//vsonic
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_FOREWARN;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_DOWNLOAD:
            if (shouldAbilityTrigger)
            {
                enum Stat statId;
                u32 opposingBattler;
                u32 opposingDef = 0, opposingSpDef = 0;

                opposingBattler = BATTLE_OPPOSITE(battler);
                for (i = 0; i < 2; opposingBattler ^= BIT_FLANK, i++)
                {
                    if (IsBattlerAlive(opposingBattler))
                    {
                        opposingDef += gBattleMons[opposingBattler].defense
                                    * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][0]
                                    / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][1];
                        opposingSpDef += gBattleMons[opposingBattler].spDefense
                                      * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][0]
                                      / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][1];
                    }
                }

                if (opposingDef < opposingSpDef)
                    statId = STAT_ATK;
                else
                    statId = STAT_SPATK;

                if (CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
                {
                    SET_STATCHANGER(statId, 1, FALSE);
                    SaveBattlerAttacker(gBattlerAttacker);
                    gBattlerAttacker = battler;
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
                    BattleScriptCall(BattleScript_AttackerAbilityStatRaiseEnd3);
                    effect++;
                }
            }
            break;
        case ABILITY_PRESSURE:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_PRESSURE;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_DARK_AURA:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_DARKAURA;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_FAIRY_AURA:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_FAIRYAURA;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_AURA_BREAK:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_AURABREAK;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_COMATOSE:
            if (shouldAbilityTrigger)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_COMATOSE;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_SCREEN_CLEANER:
            if (shouldAbilityTrigger && TryRemoveScreens(battler))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_SCREENCLEANER;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_DRIZZLE:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_RAIN, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect())
            {
                BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                effect++;
            }
            break;
        case ABILITY_SAND_STREAM:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SANDSTORM, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect())
            {
                BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                effect++;
            }
            break;
        case ABILITY_ORICHALCUM_PULSE:
        case ABILITY_DROUGHT:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SUN, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect())
            {
                BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                effect++;
            }
            break;
        case ABILITY_SNOW_WARNING:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SNOW, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }

            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect())
            {
                BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                effect++;
            }
            break;
        case ABILITY_CRYOSTORM:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_HAIL, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect() && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptCall(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_LUNAR_SOLSTICE:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_MOONLIGHT, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect() && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptCall(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_TOXIC_DELUGE:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_ACID_RAIN, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            else if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect() && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptCall(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_AURORA_SHIFT:
            if (!(gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_AURORA_VEIL))
            {
                if (IsBattlerWeatherAffected(battler, WEATHER_ICY_ANY))
                {
                    
                    gSideStatuses[GetBattlerSide(battler)] |= SIDE_STATUS_AURORA_VEIL;
                    if (GetBattlerHoldEffect(battler) == HOLD_EFFECT_LIGHT_CLAY)
                        gSideTimers[GetBattlerSide(battler)].auroraVeilTimer = 8;
                    else
                        gSideTimers[GetBattlerSide(battler)].auroraVeilTimer = 5;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_AURORA_SHIFT;
                    BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                else if (GetBattlerPartyState(battler)->usedSingleUseAbility != TRUE)
                {
                    gSideStatuses[GetBattlerSide(battler)] |= SIDE_STATUS_AURORA_VEIL;
                    if (GetBattlerHoldEffect(battler) == HOLD_EFFECT_LIGHT_CLAY)
                        gSideTimers[GetBattlerSide(battler)].auroraVeilTimer = 8;
                    else
                        gSideTimers[GetBattlerSide(battler)].auroraVeilTimer = 5;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_AURORA_SHIFT;
                    BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                    TrySetUsedSingleUseAbility_SwitchIn(battler);
                    effect++;
                }
            }
            break;
        case ABILITY_ELECTRIC_SURGE:
        case ABILITY_HADRON_ENGINE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
            {
                BattleScriptCall(BattleScript_ElectricSurgeActivates);
                effect++;
            }
            break;
        case ABILITY_GRASSY_SURGE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_GRASSY_TERRAIN))
            {
                BattleScriptCall(BattleScript_GrassySurgeActivates);
                effect++;
            }
            break;
        case ABILITY_MISTY_SURGE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_MISTY_TERRAIN))
            {
                BattleScriptCall(BattleScript_MistySurgeActivates);
                effect++;
            }
            break;
        case ABILITY_PSYCHIC_SURGE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_PSYCHIC_TERRAIN))
            {
                BattleScriptCall(BattleScript_PsychicSurgeActivates);
                effect++;
            }
            break;
        case ABILITY_INTIMIDATE:
            if (shouldAbilityTrigger && !IsOpposingSideEmpty(battler))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                SET_STATCHANGER(STAT_ATK, 1, TRUE);
                BattleScriptCall(BattleScript_IntimidateActivates);
                effect++;
            }
            break;
        case ABILITY_TIGER_MOM:
            if (shouldAbilityTrigger && !IsOpposingSideEmpty(battler))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                SET_STATCHANGER(STAT_DEF, 1, TRUE);
                BattleScriptCall(BattleScript_IntimidateActivates);
                effect++;
            }
            break;
        case ABILITY_SUPERSWEET_SYRUP:
            if (shouldAbilityTrigger
             && !GetBattlerPartyState(battler)->supersweetSyrup
             && !IsOpposingSideEmpty(battler))
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = battler;
                GetBattlerPartyState(battler)->supersweetSyrup = TRUE;
                BattleScriptCall(BattleScript_SupersweetSyrupActivates);
                effect++;
            }
            break;
        case ABILITY_STORM_BREAK:
        case ABILITY_AIR_LOCK:
            if (shouldAbilityTrigger)
            {
                BattleScriptCall(BattleScript_AnnounceAirLockCloudNine);
                effect++;
            }
            break;
        case ABILITY_TERAFORM_ZERO:
            if (gBattleMons[battler].species == SPECIES_TERAPAGOS_STELLAR)
            {
                BattleScriptCall(BattleScript_ActivateTeraformZero);
                effect++;
            }
            break;
        case ABILITY_INTREPID_SWORD:
            if (shouldAbilityTrigger /*&& !GetBattlerPartyState(battler)->intrepidSwordBoost*/)
            {
                /*if (GetConfig(B_INTREPID_SWORD) == GEN_9)
                    GetBattlerPartyState(battler)->intrepidSwordBoost = TRUE;*/

                if (CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
                {
                    SET_STATCHANGER(STAT_ATK, 1, FALSE);
                    BattleScriptCall(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                    effect++;
                }
            }
            break;//vsonic my reworks
        case ABILITY_DAUNTLESS_SHIELD:
            if (shouldAbilityTrigger /*&& !GetBattlerPartyState(battler)->dauntlessShieldBoost*/)
            {
                /*if (GetConfig(B_DAUNTLESS_SHIELD) == GEN_9)
                    GetBattlerPartyState(battler)->dauntlessShieldBoost = TRUE;*/

                if (CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
                {
                    SET_STATCHANGER(STAT_DEF, 1, FALSE);
                    BattleScriptCall(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                    effect++;
                }
            }
            break;
        case ABILITY_WIND_RIDER:
            if (shouldAbilityTrigger
             && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility)
             && gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND)
            {
                SET_STATCHANGER(STAT_ATK, 1, FALSE);
                BattleScriptCall(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                effect++;
            }
            break;
        case ABILITY_DESOLATE_LAND:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SUN_PRIMAL, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_PRIMORDIAL_SEA:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_RAIN_PRIMAL, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_DELTA_STREAM:
            if (TryChangeBattleWeather(battler, BATTLE_WEATHER_STRONG_WINDS, gLastUsedAbility))
            {
                BattleScriptCall(BattleScript_WeatherAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_VESSEL_OF_RUIN:
            if (shouldAbilityTrigger)
            {
                gBattleMons[battler].volatiles.vesselOfRuin = TRUE;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPATK);
                BattleScriptCall(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_SWORD_OF_RUIN:
            if (shouldAbilityTrigger)
            {
                gBattleMons[battler].volatiles.swordOfRuin = TRUE;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_DEF);
                BattleScriptCall(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_TABLETS_OF_RUIN:
            if (shouldAbilityTrigger)
            {
                gBattleMons[battler].volatiles.tabletsOfRuin = TRUE;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPEED);
                BattleScriptCall(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_BEADS_OF_RUIN:
            if (shouldAbilityTrigger)
            {
                gBattleMons[battler].volatiles.beadsOfRuin = TRUE;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPDEF);
                BattleScriptCall(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_SUPREME_OVERLORD:
            if (shouldAbilityTrigger)
            {
                gBattleStruct->supremeOverlordCounter[battler] = min(5, GetBattlerSideFaintCounter(battler));
                if (gBattleStruct->supremeOverlordCounter[battler] > 0)
                {
                    BattleScriptCall(BattleScript_SupremeOverlordActivates);
                    effect++;
                }
            }
            break;
        case ABILITY_ZERO_TO_HERO:
            if (GetMonData(GetBattlerMon(battler), MON_DATA_SPECIES) == SPECIES_PALAFIN_HERO
             && !GetBattlerPartyState(battler)->transformZeroToHero)
            {
                GetBattlerPartyState(battler)->transformZeroToHero = TRUE;
                BattleScriptCall(BattleScript_ZeroToHeroActivates);
                effect++;
            }
            break;
        case ABILITY_EMBODY_ASPECT_TEAL_MASK:
        case ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK:
        case ABILITY_EMBODY_ASPECT_WELLSPRING_MASK:
        case ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK:
            if (shouldAbilityTrigger)
            {
                enum Stat stat;

                if (gLastUsedAbility == ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK)
                    stat = STAT_ATK;
                else if (gLastUsedAbility == ABILITY_EMBODY_ASPECT_WELLSPRING_MASK)
                    stat = STAT_SPDEF;
                else if (gLastUsedAbility == ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK)
                    stat = STAT_DEF;
                else //ABILITY_EMBODY_ASPECT_TEAL_MASK
                    stat = STAT_SPEED;

                if (CompareStat(battler, stat, MAX_STAT_STAGE, CMP_EQUAL, gLastUsedAbility))
                    break;

                SET_STATCHANGER(stat, 1, FALSE);
                BattleScriptCall(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_SWITCH_IN_FORM_CHANGE:
        if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_HP_PERCENT_SEND_OUT, ability))
        {
            gBattleScripting.battler = battler;
            // To prevent the new form's ability from pop up
            //gBattleScripting.abilityPopupOverwrite = ability;
            BattleScriptCall(BattleScript_BattlerFormChange);
            effect++;
        }
        break;
    case ABILITYEFFECT_ENDTURN:
        if (IsBattlerAlive(battler))
        {
            gBattlerAttacker = battler;
            switch (gLastUsedAbility)
            {
            case ABILITY_PICKUP:
                if (gBattleMons[battler].item == ITEM_NONE
                 && gBattleStruct->changedItems[battler] == ITEM_NONE   // Will not inherit an item
                 && PickupHasValidTarget(battler))
                {
                    gBattlerTarget = RandomUniformExcept(RNG_PICKUP, 0, gBattlersCount - 1, CantPickupItem);
                    gLastUsedItem = GetBattlerPartyState(gBattlerTarget)->usedHeldItem;
                    BattleScriptExecute(BattleScript_PickupActivates);
                    effect++;
                }
                break;
            case ABILITY_HARVEST:
                if ((IsBattlerWeatherAffected(battler, WEATHER_SUN) || RandomPercentage(RNG_HARVEST, 50))
                 && gBattleMons[battler].item == ITEM_NONE
                 && gBattleStruct->changedItems[battler] == ITEM_NONE   // Will not inherit an item
                 && GetItemPocket(GetBattlerPartyState(battler)->usedHeldItem) == POCKET_BERRIES)
                {
                    gLastUsedItem = GetBattlerPartyState(battler)->usedHeldItem;
                    BattleScriptExecute(BattleScript_HarvestActivates);
                    effect++;
                }
                break;
            case ABILITY_ICE_BODY:
                if (IsBattlerWeatherAffected(battler, WEATHER_ICY_ANY)
                 && !IsBattlerAtMaxHp(battler)
                 && gBattleMons[battler].volatiles.semiInvulnerable != STATE_UNDERGROUND
                 && gBattleMons[battler].volatiles.semiInvulnerable != STATE_UNDERWATER
                 && !gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_HEAL_BLOCK)
                {
                    BattleScriptExecute(BattleScript_IceBodyHeal);
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / 16);
                    effect++;
                }
                break;
            case ABILITY_DRY_SKIN:
                if (IsBattlerWeatherAffected(battler, WEATHER_SUN))
                    goto SOLAR_POWER_HP_DROP;
                else if ((IsBattlerWeatherAffected(battler, WEATHER_RAIN)
                || IsFogOnField())
                && CanBattlerHeal(battler))
                {
                    s32 healAmount = 8;
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / healAmount);
                    BattleScriptExecute(BattleScript_EndTurnAbilityHpHeal);
                    effect++;
                }
                break;
            // Dry Skin works similarly to Rain Dish in Rain
            //not sure why they did it this way, not doin that
            //also rebalanced heal effects
            //had removed dry skin drop from dry skin
            //but makes sense think what will do instead
            //is just lower dmg insteed of 1/8  do 1/12 - done
            case ABILITY_WATER_ABSORB:
                if ((IsBattlerWeatherAffected(battler, WEATHER_RAIN)
                || IsFogOnField())
                && CanBattlerHeal(battler))
                    {
                        s32 healAmount = 16;
                        SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / healAmount);
                        BattleScriptExecute(BattleScript_EndTurnAbilityHpHeal);
                        ++effect;
                    }
                    break;
            case ABILITY_RAIN_DISH:
                if (IsBattlerWeatherAffected(battler, WEATHER_RAIN)
                 && CanBattlerHeal(battler))
                {
                    s32 healAmount = 12;
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / healAmount);
                    BattleScriptExecute(BattleScript_EndTurnAbilityHpHeal);
                    effect++;
                }
                break;
            case ABILITY_HYDRATION:
                if (IsBattlerWeatherAffected(battler, WEATHER_RAIN)
                 && gBattleMons[battler].status1 & STATUS1_ANY)
                {
                    goto ABILITY_HEAL_MON_STATUS;
                }
                break;//vsonic
            case ABILITY_SHED_SKIN:
                if ((gBattleMons[battler].status1 & STATUS1_ANY)
                 && (B_ABILITY_TRIGGER_CHANCE == GEN_4 ? RandomPercentage(RNG_SHED_SKIN, 30) : RandomChance(RNG_SHED_SKIN, 1, 3)))
                {
                ABILITY_HEAL_MON_STATUS:
                    if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON))
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                    if (gBattleMons[battler].status1 & STATUS1_SLEEP)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        TryDeactivateSleepClause(GetBattlerSide(battler), gBattlerPartyIndexes[battler]);
                    }

                    if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                    if (gBattleMons[battler].status1 & STATUS1_BURN)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                    if (gBattleMons[battler].status1 & (STATUS1_FREEZE | STATUS1_FROSTBITE))
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);

                    gBattleMons[battler].status1 = 0;
                    gBattleMons[battler].volatiles.nightmare = FALSE;
                    gBattleScripting.battler = battler;
                    BattleScriptExecute(BattleScript_ShedSkinActivates);
                    BtlController_EmitSetMonData(battler, B_COMM_TO_CONTROLLER, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    effect++;
                }
                break;
            case ABILITY_SPEED_BOOST:
                if (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility) && gBattleStruct->battlerState[battler].isFirstTurn != 2)
                {
                    SaveBattlerAttacker(gBattlerAttacker);
                    SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                    BattleScriptExecute(BattleScript_AttackerAbilityStatRaiseEnd2);
                    gBattleScripting.battler = battler;
                    effect++;
                }
                break;
            case ABILITY_MOODY:
                if (gBattleStruct->battlerState[battler].isFirstTurn != 2)
                {
                    u32 validToRaise = 0, validToLower = 0;
                    u32 statsNum = GetConfig(B_MOODY_ACC_EVASION) >= GEN_8 ? NUM_STATS : NUM_BATTLE_STATS;

                    for (i = STAT_ATK; i < statsNum; i++)
                    {
                        if (CompareStat(battler, i, MIN_STAT_STAGE, CMP_GREATER_THAN, gLastUsedAbility))
                            validToLower |= 1u << i;
                        if (CompareStat(battler, i, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
                            validToRaise |= 1u << i;
                    }

                    gBattleScripting.statChanger = gBattleScripting.savedStatChanger = 0; // for raising and lowering stat respectively
                    if (validToRaise) // Find stat to raise
                    {
                        i = RandomUniformExcept(RNG_MOODY_INCREASE, STAT_ATK, statsNum - 1, MoodyCantRaiseStat);
                        SET_STATCHANGER(i, 2, FALSE);
                        validToLower &= ~(1u << i); // Can't lower the same stat as raising.
                    }
                    if (validToLower) // Find stat to lower
                    {
                        // MoodyCantLowerStat already checks that both stats are different
                        i = RandomUniformExcept(RNG_MOODY_DECREASE, STAT_ATK, statsNum - 1, MoodyCantLowerStat);
                        SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 1, TRUE);
                    }
                    BattleScriptExecute(BattleScript_MoodyActivates);
                    effect++;
                }
                break;
            case ABILITY_TRUANT:
                gBattleMons[gBattlerAttacker].volatiles.truantCounter ^= 1;
                break;
            case ABILITY_SLOW_START:
                if (GetBattlerPartyState(battler)->cachedAbilityTimers > 0 && --GetBattlerPartyState(battler)->cachedAbilityTimers == 0)
                {
                    BattleScriptExecute(BattleScript_SlowStartEnds);
                    effect++;
                }
                break;
            case ABILITY_BAD_DREAMS:
                BattleScriptExecute(BattleScript_BadDreamsActivates);
                effect++;
                break;
            case ABILITY_SOLAR_POWER:
                if (IsBattlerWeatherAffected(battler, WEATHER_SUN))
                {
                SOLAR_POWER_HP_DROP:
                    SetPassiveDamageAmount(battler, GetNonDynamaxMaxHP(battler) / 8);
                    BattleScriptExecute(BattleScript_SolarPowerActivates);
                    effect++;
                }
                break;
            case ABILITY_HEALER:
                gBattleScripting.battler = BATTLE_PARTNER(battler);
                if (IsBattlerAlive(gBattleScripting.battler)
                    && gBattleMons[gBattleScripting.battler].status1 & STATUS1_ANY
                    && RandomPercentage(RNG_HEALER, 30))
                {
                    BattleScriptExecute(BattleScript_HealerActivates);
                    effect++;
                }
                break;
            case ABILITY_BALL_FETCH:
                if (!(gBattleTypeFlags & BATTLE_TYPE_RAID)
                    && gBattleMons[battler].item == ITEM_NONE
                    && gBattleResults.catchAttempts[ItemIdToBallId(gLastThrownBall)] >= 1)
                    //&& !gHasFetchedBall)
                {
                    gLastUsedItem = gLastThrownBall;
                    gBattleScripting.battler = battler;
                    gBattleMons[battler].item = gLastUsedItem;
                    BtlController_EmitSetMonData(battler, B_COMM_TO_CONTROLLER, REQUEST_HELDITEM_BATTLE, 0, 2, &gLastUsedItem);
                    MarkBattlerForControllerExec(battler);
                    //gHasFetchedBall = TRUE;
                    BattleScriptExecute(BattleScript_BallFetch);
                    effect++;
                }
                break;
            case ABILITY_CUD_CHEW:
                if (gBattleMons[battler].volatiles.cudChew == TRUE)
                {
                    gBattleScripting.battler = battler;
                    gBattleMons[battler].volatiles.cudChew = FALSE;
                    gLastUsedItem = GetBattlerPartyState(battler)->usedHeldItem;
                    GetBattlerPartyState(battler)->usedHeldItem = ITEM_NONE;
                    BattleScriptExecute(BattleScript_CudChewActivates);
                    effect++;
                }
                else if (!gBattleMons[battler].volatiles.cudChew && GetItemPocket(GetBattlerPartyState(battler)->usedHeldItem) == POCKET_BERRIES)
                {
                    gBattleMons[battler].volatiles.cudChew = TRUE;
                }
                break;
            default:
                break;
            }
        }
        break;//vsonic
    case ABILITYEFFECT_COLOR_CHANGE:
        switch (gLastUsedAbility)
        {
        case ABILITY_BERSERK:
            if (IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && HadMoreThanHalfHpNowDoesnt(battler)
             && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
            {
                gEffectBattler = gBattlerAbility = battler;
                SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                BattleScriptCall(BattleScript_BerserkActivates);
                effect++;
            }
            break;
        case ABILITY_ANGER_SHELL:
            if (IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && HadMoreThanHalfHpNowDoesnt(battler))
            {
                gEffectBattler = gBattlerAbility = battler;
                BattleScriptCall(BattleScript_AngerShellActivates);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END: // Think contact abilities.
        switch (gLastUsedAbility)
        {
        case ABILITY_JUSTIFIED:
            if (IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && moveType == TYPE_DARK
             && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
            {
                gEffectBattler = gBattlerAbility = battler;
                SET_STATCHANGER(STAT_ATK, 1, FALSE);
                BattleScriptCall(BattleScript_TargetAbilityStatRaiseRet);
                effect++;
            }
            break;
        case ABILITY_RATTLED:
            if (IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && (moveType == TYPE_DARK || moveType == TYPE_BUG || moveType == TYPE_GHOST)
             && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
            {
                gEffectBattler = gBattlerAbility = battler;
                SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                BattleScriptCall(BattleScript_TargetAbilityStatRaiseRet);
                effect++;
            }
            break;
        case ABILITY_WATER_COMPACTION:
            if (IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && moveType == TYPE_WATER
             && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
            {
                gEffectBattler = gBattlerAbility = battler;
                SET_STATCHANGER(STAT_DEF, 2, FALSE);
                BattleScriptCall(BattleScript_TargetAbilityStatRaiseRet);
                effect++;
            }
            break;
        case ABILITY_STAMINA:
            if (gBattlerAttacker != gBattlerTarget
             && IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(battler)
             && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
            {
                gEffectBattler = gBattlerAbility = battler;
                SET_STATCHANGER(STAT_DEF, 1, FALSE);
                BattleScriptCall(BattleScript_TargetAbilityStatRaiseRet);
                effect++;
            }
            break;
        case ABILITY_WEAK_ARMOR:
            if (IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && IsBattleMovePhysical(gCurrentMove)
             && (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility) // Don't activate if both Speed and Defense cannot be raised.
               || CompareStat(battler, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN, gLastUsedAbility)))
            {
                if (GetMoveEffect(gCurrentMove) == EFFECT_HIT_ESCAPE && CanBattlerSwitch(gBattlerAttacker))
                    gProtectStructs[battler].disableEjectPack = TRUE;  // Set flag for target

                BattleScriptCall(BattleScript_WeakArmorActivates);
                effect++;
            }
            break;
        case ABILITY_CURSED_BODY:
            if (IsBattlerTurnDamaged(gBattlerTarget)
             && gBattleMons[gBattlerAttacker].volatiles.disabledMove == MOVE_NONE
             && IsBattlerAlive(gBattlerAttacker)
             && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
             && gChosenMove != MOVE_STRUGGLE
             && RandomPercentage(RNG_CURSED_BODY, 30))
            {
                gBattleMons[gBattlerAttacker].volatiles.disabledMove = gChosenMove;
                gBattleMons[gBattlerAttacker].volatiles.disableTimer = B_DISABLE_TIMER;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gChosenMove);
                BattleScriptCall(BattleScript_CursedBodyActivates);
                effect++;
            }
            break;
        case ABILITY_LINGERING_AROMA:
        case ABILITY_MUMMY:
            if (IsBattlerAlive(gBattlerAttacker)
             && IsBattlerTurnDamaged(gBattlerTarget)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move)
             && gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility != GetBattlerAbility(gBattlerTarget)
             && gBattleMons[gBattlerAttacker].ability != ABILITY_MUMMY
             && gBattleMons[gBattlerAttacker].ability != ABILITY_LINGERING_AROMA
             && !gAbilitiesInfo[gBattleMons[gBattlerAttacker].ability].cantBeSuppressed)
            {
                if (GetBattlerHoldEffectIgnoreAbility(gBattlerAttacker) == HOLD_EFFECT_ABILITY_SHIELD)
                {
                    RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
                    break;
                }

                RemoveAbilityFlags(gBattlerAttacker);
                gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
                gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility = gBattleMons[gBattlerTarget].ability;
                BattleScriptCall(BattleScript_MummyActivates);
                effect++;
                break;
            }
            break;
        case ABILITY_WANDERING_SPIRIT:
            if (IsBattlerAlive(gBattlerAttacker)
             && IsBattlerTurnDamaged(gBattlerTarget)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move)
             && !(GetActiveGimmick(gBattlerTarget) == GIMMICK_DYNAMAX)
             && !gAbilitiesInfo[gBattleMons[gBattlerAttacker].ability].cantBeSwapped)
            {
                if (GetBattlerHoldEffectIgnoreAbility(gBattlerAttacker) == HOLD_EFFECT_ABILITY_SHIELD)
                {
                    RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
                    break;
                }
                if (GetBattlerHoldEffectIgnoreAbility(gBattlerTarget) == HOLD_EFFECT_ABILITY_SHIELD)
                {
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_ABILITY_SHIELD);
                    break;
                }

                RemoveAbilityFlags(gBattlerAttacker);
                gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
                gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerAttacker].volatiles.overwrittenAbility = gBattleMons[gBattlerTarget].ability;
                gBattleMons[gBattlerTarget].ability = gBattleMons[gBattlerTarget].volatiles.overwrittenAbility = gLastUsedAbility;
                BattleScriptCall(BattleScript_WanderingSpiritActivates);
                effect++;
                break;
            }
            break;
        case ABILITY_ANGER_POINT:
            if (gSpecialStatuses[battler].criticalHit
             && IsBattlerTurnDamaged(battler)
             && IsBattlerAlive(battler)
             && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility))
            {
                SET_STATCHANGER(STAT_ATK, MAX_STAT_STAGE - gBattleMons[battler].statStages[STAT_ATK], FALSE);
                BattleScriptCall(BattleScript_TargetsStatWasMaxedOut);
                effect++;
            }
            break;
        case ABILITY_GOOEY:
        case ABILITY_TANGLING_HAIR:
            if (IsBattlerAlive(gBattlerAttacker)
             && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN, gLastUsedAbility) || GetBattlerAbility(gBattlerAttacker) == ABILITY_MIRROR_ARMOR)
             && !gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move))
            {
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptCall(BattleScript_GooeyActivates);
                effect++;
            }
            break;
        case ABILITY_ROUGH_SKIN:
        case ABILITY_IRON_BARBS:
            if (IsBattlerAlive(gBattlerAttacker)
             && !gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move))
            {
                SetPassiveDamageAmount(gBattlerAttacker, GetNonDynamaxMaxHP(gBattlerAttacker) / (B_ROUGH_SKIN_DMG >= GEN_4 ? 8 : 16));
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptCall(BattleScript_RoughSkinActivates);
                effect++;
            }
            break;
        case ABILITY_AFTERMATH:
            if (!IsBattlerUnaffectedByMove(gBattlerTarget)
             && !IsBattlerAlive(gBattlerTarget)
             && IsBattlerAlive(gBattlerAttacker)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move))
            {
                if ((battler = IsAbilityOnField(ABILITY_DAMP)))
                {
                    gBattleScripting.battler = battler - 1;
                    BattleScriptCall(BattleScript_DampPreventsAftermath);
                }
                else
                {
                    gBattleScripting.battler = gBattlerTarget;
                    SetPassiveDamageAmount(gBattlerAttacker, GetNonDynamaxMaxHP(gBattlerAttacker) / 4);
                    BattleScriptCall(BattleScript_AftermathDmg);
                }
                effect++;
            }
            break;

        case ABILITY_INNARDS_OUT: //effect reworked need check if future logic still makes sense vsonic
            if (!IsBattlerUnaffectedByMove(gBattlerTarget)
             && !IsBattlerAlive(gBattlerTarget)
             && IsBattlerAlive(gBattlerAttacker))
            {
                // Prevent Innards Out effect if Future Sight user is currently not on field
                if (IsFutureSightAttackerInParty(gBattlerAttacker, gBattlerTarget, gCurrentMove))
                    break;

                gBattleScripting.battler = gBattlerTarget;
                SetPassiveDamageAmount(gBattlerAttacker, gBattleStruct->moveDamage[gBattlerTarget]);
                BattleScriptCall(BattleScript_AftermathDmg);
                effect++;
            }
            break;
        case ABILITY_EFFECT_SPORE:
        {   //vsonic
            enum Ability abilityAtk = GetBattlerAbility(gBattlerAttacker);
            enum HoldEffect holdEffectAtk = GetBattlerHoldEffect(gBattlerAttacker);
            if (IsAffectedByPowderMove(gBattlerAttacker, abilityAtk, abilityAtk, holdEffectAtk))
            {
                u32 poison, paralysis, sleep;

                if (B_ABILITY_TRIGGER_CHANCE >= GEN_5)
                {
                    poison = 9;
                    paralysis = 19;
                }
                else
                {
                    poison = 10;
                    paralysis = 20;
                }
                sleep = 30;

                i = RandomUniform(RNG_EFFECT_SPORE, 0, B_ABILITY_TRIGGER_CHANCE >= GEN_4 ? 99 : 299);
                if (i < poison)
                    goto POISON_POINT;
                if (i < paralysis)
                    goto STATIC;
                // Sleep
                if (i < sleep
                 && IsBattlerAlive(gBattlerAttacker)
                 && !gBattleStruct->unableToUseMove
                 && IsBattlerTurnDamaged(gBattlerTarget) //already checked powder checks so no ability should prevent
                 && CanBeSlept(gBattlerTarget, gBattlerAttacker, ABILITY_NONE, abilityAtk, NOT_BLOCKED_BY_SLEEP_CLAUSE)
                 && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, abilityAtk, holdEffectAtk, move))
                {
                    if (IsSleepClauseEnabled())
                        gBattleStruct->battlerState[gBattlerAttacker].sleepClauseEffectExempt = TRUE;
                    gEffectBattler = gBattlerAttacker;
                    gBattleScripting.battler = gBattlerTarget;
                    gBattleScripting.moveEffect = MOVE_EFFECT_SLEEP;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptCall(BattleScript_AbilityStatusEffect);
                    effect++;
                }
            }
        }
            break;
        case ABILITY_POISON_POINT:
            if (B_ABILITY_TRIGGER_CHANCE >= GEN_4 ? RandomPercentage(RNG_POISON_POINT, 30) : RandomChance(RNG_POISON_POINT, 1, 3))
            {
            POISON_POINT:
            {
                enum Ability abilityAtk = GetBattlerAbility(gBattlerAttacker);
                if (IsBattlerAlive(gBattlerAttacker)
                && !gBattleStruct->unableToUseMove
                && IsBattlerTurnDamaged(gBattlerTarget)
                && CanBePoisoned(gBattlerTarget, gBattlerAttacker, gLastUsedAbility, abilityAtk)
                && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, abilityAtk, GetBattlerHoldEffect(gBattlerAttacker), move))
                {
                    gEffectBattler = gBattlerAttacker;
                    gBattleScripting.battler = gBattlerTarget;
                    gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptCall(BattleScript_AbilityStatusEffect);
                    effect++;
                }
            }
            }
            break;
        case ABILITY_STATIC:
            if (B_ABILITY_TRIGGER_CHANCE >= GEN_4 ? RandomPercentage(RNG_STATIC, 30) : RandomChance(RNG_STATIC, 1, 3))
            {
            STATIC:
            {
                enum Ability abilityAtk = GetBattlerAbility(gBattlerAttacker);
                if (IsBattlerAlive(gBattlerAttacker)
                && !gBattleStruct->unableToUseMove
                && IsBattlerTurnDamaged(gBattlerTarget)
                && CanBeParalyzed(gBattlerTarget, gBattlerAttacker, abilityAtk)
                && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, abilityAtk, GetBattlerHoldEffect(gBattlerAttacker), move))
                {
                    gEffectBattler = gBattlerAttacker;
                    gBattleScripting.battler = gBattlerTarget;
                    gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptCall(BattleScript_AbilityStatusEffect);
                    effect++;
                }
            }
            }
            break;
        case ABILITY_FLAME_BODY:
            if (IsBattlerAlive(gBattlerAttacker)
             && !gBattleStruct->unableToUseMove
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move)
             && IsBattlerTurnDamaged(gBattlerTarget)
             && CanBeBurned(gBattlerTarget, gBattlerAttacker, GetBattlerAbility(gBattlerAttacker))
             && (B_ABILITY_TRIGGER_CHANCE >= GEN_4 ? RandomPercentage(RNG_FLAME_BODY, 30) : RandomChance(RNG_FLAME_BODY, 1, 3)))
            {
                gEffectBattler = gBattlerAttacker;
                gBattleScripting.battler = gBattlerTarget;
                gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptCall(BattleScript_AbilityStatusEffect);
                effect++;
            }
            break;
        case ABILITY_CUTE_CHARM:
            if (IsBattlerAlive(gBattlerAttacker)
             && !gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(gBattlerTarget)
             && (B_ABILITY_TRIGGER_CHANCE >= GEN_4 ? RandomPercentage(RNG_CUTE_CHARM, 30) : RandomChance(RNG_CUTE_CHARM, 1, 3))
             && !(gBattleMons[gBattlerAttacker].volatiles.infatuatedwithMon)
             && AreBattlersOfOppositeGender(gBattlerAttacker, gBattlerTarget)
             && !IsAbilityAndRecord(gBattlerAttacker, GetBattlerAbility(gBattlerAttacker), ABILITY_OBLIVIOUS)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move)
             && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL))
            {
                gBattleMons[gBattlerAttacker].volatiles.infatuatedwithMon = GetBattlerPersonality(gBattlerTarget);
                BattleScriptCall(BattleScript_CuteCharmActivates);
                effect++;
            }
            break;
        case ABILITY_ILLUSION:
            if (gBattleStruct->illusion[gBattlerTarget].state == ILLUSION_ON && IsBattlerTurnDamaged(gBattlerTarget))
            {
                gBattleScripting.battler = gBattlerTarget;
                BattleScriptCall(BattleScript_IllusionOff);
                effect++;
            }
            break;
        case ABILITY_COTTON_DOWN:
            if (IsBattlerAlive(gBattlerAttacker)
             && !gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget))
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptCall(BattleScript_CottonDownActivates);
                effect++;
            }
            break;
        case ABILITY_STEAM_ENGINE:
            if (IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(battler)
             && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility)
             && (moveType == TYPE_FIRE || moveType == TYPE_WATER))
            {
                gEffectBattler = gBattlerAbility = battler;
                SET_STATCHANGER(STAT_SPEED, 6, FALSE);
                BattleScriptCall(BattleScript_TargetAbilityStatRaiseRet);
                effect++;
            }
            break;
        case ABILITY_SAND_SPIT:
            if (!gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && !(gBattleWeather & WEATHER_SANDSTORM && HasWeatherEffect()))
            {
                if (gBattleWeather & WEATHER_PRIMAL_ANY && HasWeatherEffect())
                {
                    BattleScriptCall(BattleScript_BlockedByPrimalWeather);
                    effect++;
                }
                else if (TryChangeBattleWeather(battler, BATTLE_WEATHER_SANDSTORM, ABILITY_SAND_STREAM))
                {
                    gBattleScripting.battler = battler;
                    BattleScriptCall(BattleScript_WeatherAbilityActivates);
                    effect++;
                }
            }
            break;
        case ABILITY_PERISH_BODY:
            if (!gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(battler)
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move)
             && !gBattleMons[gBattlerAttacker].volatiles.perishSong)
            {
                if (!gBattleMons[battler].volatiles.perishSong)
                {
                    gBattleMons[battler].volatiles.perishSong = TRUE;
                    gBattleMons[battler].volatiles.perishSongTimer = 3;
                }
                gBattleMons[gBattlerAttacker].volatiles.perishSong = TRUE;
                gBattleMons[gBattlerAttacker].volatiles.perishSongTimer = 3;
                BattleScriptCall(BattleScript_PerishBodyActivates);
                effect++;
            }
            break;
        case ABILITY_SEED_SOWER:
            if (!gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(gBattlerTarget)
             && TryChangeBattleTerrain(gBattlerTarget, STATUS_FIELD_GRASSY_TERRAIN))
            {
                BattleScriptCall(BattleScript_SeedSowerActivates);
                effect++;
            }
            break;
        case ABILITY_THERMAL_EXCHANGE:
            if (IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(gBattlerTarget)
             && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN, gLastUsedAbility)
             && moveType == TYPE_FIRE)
            {
                gEffectBattler = gBattlerAbility = gBattlerTarget;
                SET_STATCHANGER(STAT_ATK, 1, FALSE);
                BattleScriptCall(BattleScript_TargetAbilityStatRaiseRet);
                effect++;
            }
            break;
        case ABILITY_WIND_POWER:
            if (!IsWindMove(gCurrentMove))
                break;
            // fall through
        case ABILITY_ELECTROMORPHOSIS:
            if (!gBattleStruct->unableToUseMove
             && IsBattlerTurnDamaged(gBattlerTarget)
             && IsBattlerAlive(gBattlerTarget))
            {
                BattleScriptCall(BattleScript_WindPowerActivates);
                effect++;
            }
            break;
        case ABILITY_ICE_FACE:
            if (!gBattleStruct->unableToUseMove
             && IsBattleMovePhysical(gCurrentMove)
             && IsBattlerAlive(gBattlerTarget)
             && !gBattleMons[gBattlerTarget].volatiles.triggerIceFace
             && gBattleMons[battler].species == GetBaseFormSpecies(gBattleMons[battler].species))
            {
                BattleScriptCall(BattleScript_IceFaceTookHit);
                effect++;
            }
            break;
        case ABILITY_TOXIC_DEBRIS:
            if (!gBattleStruct->isSkyBattle
             && !gBattleStruct->unableToUseMove
             && IsBattleMovePhysical(gCurrentMove)
             && IsBattlerTurnDamaged(gBattlerTarget)
             && (gSideTimers[GetBattlerSide(gBattlerAttacker)].toxicSpikesAmount != 2))
            {
                SaveBattlerTarget(gBattlerTarget);
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = gBattlerTarget;
                gBattlerTarget = BATTLE_OPPOSITE(gBattlerAttacker);
                BattleScriptCall(BattleScript_ToxicDebrisActivates);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END_ATTACKER: // Same as above, but for attacker
        switch (gLastUsedAbility)
        {
        case ABILITY_POISON_TOUCH:
            if (IsBattlerAlive(gBattlerTarget)
             && !gBattleStruct->unableToUseMove
             && CanBePoisoned(gBattlerAttacker, gBattlerTarget, gLastUsedAbility, GetBattlerAbility(gBattlerTarget))
             && !CanBattlerAvoidContactEffects(gBattlerAttacker, gBattlerTarget, GetBattlerAbility(gBattlerAttacker), GetBattlerHoldEffect(gBattlerAttacker), move)
             && IsBattlerTurnDamaged(gBattlerTarget) // Need to actually hit the target
             && RandomPercentage(RNG_POISON_TOUCH, 30))
            {
                gEffectBattler = gBattlerTarget;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptCall(BattleScript_AbilityStatusEffect);
                effect++;
            }
            break;
        case ABILITY_TOXIC_CHAIN:
            if (gBattleStruct->toxicChainPriority)
            {
                gBattleStruct->toxicChainPriority = FALSE;
                gEffectBattler = gBattlerTarget;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleScripting.moveEffect = MOVE_EFFECT_TOXIC;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptCall(BattleScript_AbilityStatusEffect);
                effect++;
            }
            break;//vsonic
        case ABILITY_STENCH:
            if (IsBattlerAlive(gBattlerTarget)
             && !gBattleStruct->unableToUseMove
             && RandomChance(RNG_STENCH, 1, 10)
             && IsBattlerTurnDamaged(gBattlerTarget)
             && !MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_FLINCH))
            {
                SetMoveEffect(gBattlerAttacker, gBattlerTarget, MOVE_EFFECT_FLINCH, gBattlescriptCurrInstr, EFFECT_PRIMARY);
                effect++;
            }
            break;
        case ABILITY_POISON_PUPPETEER:
            if (gBattleMons[gBattlerAttacker].species == SPECIES_PECHARUNT
             && gBattleStruct->poisonPuppeteerConfusion == TRUE
             && CanBeConfused(gBattlerTarget))
            {
                gBattleStruct->poisonPuppeteerConfusion = FALSE;
                gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptCall(BattleScript_AbilityStatusEffect);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_FORM_CHANGE_ON_HIT:
        speciesForm = gBattleMons[gBattlerTarget].species;

        if (gBattleStruct->unableToUseMove
         || !IsBattlerTurnDamaged(gBattlerTarget)
         || !TryBattleFormChange(gBattlerTarget, FORM_CHANGE_BATTLE_HIT_BY_MOVE_CATEGORY, ability))
            break;

        //gBattleScripting.abilityPopupOverwrite = ability;
        gBattleScripting.battler = battler;
        effect++;

        switch (ability)
        {
        case ABILITY_GULP_MISSILE:
            if (!IsBattlerAlive(gBattlerAttacker))
                break;

            //with increased viability may need cut this down
            //didn't realize was 1/4th max hp
            //if don't want to adjust to much could change to 1/4th curr hp
            //so at high hp is about same but gets weaker with time
            //oh lol there's even a function for that ok nice
            if (!IsAbilityAndRecord(gBattlerAttacker, GetBattlerAbility(gBattlerAttacker), ABILITY_MAGIC_GUARD))
                SetPassiveDamageAmount(gBattlerAttacker, GetNonDynamaxHP(gBattlerAttacker) / 4);

            switch (speciesForm)
            {
            case SPECIES_CRAMORANT_GORGING:
                BattleScriptCall(BattleScript_GulpMissileGorging);
                break;
            case SPECIES_CRAMORANT_GULPING:
                BattleScriptCall(BattleScript_GulpMissileGulping);
                break;
            default:
                BattleScriptCall(BattleScript_BattlerFormChange); // Fallback
                break;
            }
            break;
        case ABILITY_DISGUISE:
            if (GetConfig(B_DISGUISE_HP_LOSS) >= GEN_8 && ability == ABILITY_DISGUISE)
                //SetPassiveDamageAmount(gBattlerTarget, GetNonDynamaxMaxHP(gBattlerTarget) / 8);
                SetPassiveDamageAmount(gBattlerTarget, 1);
            BattleScriptCall(BattleScript_BattlerFormChangeDisguise);
            break;
        case ABILITY_ICE_FACE:
            if (gBattleMons[gBattlerTarget].volatiles.triggerIceFace)
            {
                SetPassiveDamageAmount(gBattlerTarget, 1);
                BattleScriptCall(BattleScript_IceFaceNullsDamage);
            }
            break;
        default:
            BattleScriptCall(BattleScript_BattlerFormChange);
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END_OTHER: // Abilities that activate on *another* battler's moveend: Dancer, Soul-Heart, Receiver, Symbiosis
        switch (GetBattlerAbility(battler))
        {
        case ABILITY_DANCER:
            if (IsBattlerAlive(battler)
             && IsDanceMove(move)
             && !gSpecialStatuses[battler].dancerUsedMove
             && gBattlerAttacker != battler)
            {
                // Set bit and save Dancer mon's original target
                gSpecialStatuses[battler].dancerUsedMove = TRUE;
                gSpecialStatuses[battler].dancerOriginalTarget = gBattleStruct->moveTarget[battler] | 0x4;
                gBattlerAttacker = gBattlerAbility = battler;
                gCalledMove = move;

                // Set the target to the original target of the mon that first used a Dance move
                gBattlerTarget = gBattleScripting.savedBattler & 0x3;

                // Make sure that the target isn't an ally - if it is, target the original user
                if (IsBattlerAlly(gBattlerTarget, gBattlerAttacker))
                    gBattlerTarget = (gBattleScripting.savedBattler & 0xF0) >> 4;
                BattleScriptExecute(BattleScript_DancerActivates);
                effect++;
            }
            break;//vsonic
        default:
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END_FOES_FAINTED:
        switch (ability)
        {
        case ABILITY_MAGICIAN:
            if (GetMoveEffect(move) != EFFECT_FLING
             && GetMoveEffect(move) != EFFECT_NATURAL_GIFT
             && gBattleMons[battler].item == ITEM_NONE
             && IsBattlerAlive(battler)
             && !gSpecialStatuses[battler].gemBoost) // In base game, gems are consumed after magician would activate.
            {
                u32 numMagicianTargets = 0;
                u32 magicianTargets = 0;

                for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
                {
                    if (gBattleMons[battlerDef].item != ITEM_NONE
                     && battlerDef != battler
                     && IsBattlerTurnDamaged(battlerDef)
                     && CanStealItem(battler, battlerDef, gBattleMons[battlerDef].item)
                     && !GetBattlerPartyState(battlerDef)->lostItemtoKnockOff
                     && !DoesSubstituteBlockMove(battler, battlerDef, move)
                     && (GetBattlerAbility(battlerDef) != ABILITY_STICKY_HOLD || !IsBattlerAlive(battlerDef)))
                    {
                        magicianTargets |= 1u << battlerDef;
                        numMagicianTargets++;
                    }
                }

                if (numMagicianTargets == 0)
                {
                    effect = FALSE;
                    break;
                }

                enum BattlerId battlers[4] = {0, 1, 2, 3};
                if (numMagicianTargets > 1)
                    SortBattlersBySpeed(battlers, FALSE);

                for (u32 i = 0; i < gBattlersCount; i++)
                {
                    u32 targetBattler = battlers[i];

                    if (!(magicianTargets & 1u << targetBattler))
                        continue;

                    StealTargetItem(battler, targetBattler);
                    gBattlerAbility = battler;
                    gEffectBattler = targetBattler;
                    BattleScriptCall(BattleScript_MagicianActivates);
                    effect = TRUE;
                    break; // found target to steal from
                }
            }
            break;
        case ABILITY_MOXIE:
        case ABILITY_CHILLING_NEIGH:
        case ABILITY_AS_ONE_ICE_RIDER:
        case ABILITY_GRIM_NEIGH:
        case ABILITY_AS_ONE_SHADOW_RIDER:
        case ABILITY_BEAST_BOOST:
            {
                if (!IsBattlerAlive(battler) || NoAliveMonsForEitherParty())
                    break;

                enum Stat stat = STAT_ATK;
                u32 numMonsFainted = NumFaintedBattlersByAttacker(battler);

                if (ability == ABILITY_BEAST_BOOST)
                    stat = GetHighestStatId(battler);
                else if (ability == ABILITY_GRIM_NEIGH || ability == ABILITY_AS_ONE_SHADOW_RIDER)
                    stat = STAT_SPATK;

                if (numMonsFainted && CompareStat(battler, stat, MAX_STAT_STAGE, CMP_LESS_THAN, ability))
                {
                    gLastUsedAbility = ability;
                    /*if (ability == ABILITY_AS_ONE_ICE_RIDER)
                        gBattleScripting.abilityPopupOverwrite = gLastUsedAbility = ABILITY_CHILLING_NEIGH;
                    else if (ability == ABILITY_AS_ONE_SHADOW_RIDER)
                        gBattleScripting.abilityPopupOverwrite = gLastUsedAbility = ABILITY_GRIM_NEIGH;*/

                    SET_STATCHANGER(stat, numMonsFainted, FALSE);
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, stat);
                    gBattleScripting.animArg1 = GET_STAT_BUFF_ID(stat) + (numMonsFainted > 1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
                    BattleScriptCall(BattleScript_RaiseStatOnFaintingTarget);
                    effect = TRUE;
                }
            }
            break;
        case ABILITY_BATTLE_BOND:
            {
                if (!IsBattlerAlive(battler)
                 || NoAliveMonsForEitherParty()
                 || NumFaintedBattlersByAttacker(battler) == 0)
                    break;

                if (GetBattlerPartyState(battler)->battleBondBoost 
                || GET_BASE_SPECIES_ID(gBattleMons[battler].species) != SPECIES_GRENINJA)
                    break;

                //if (GetConfig(B_BATTLE_BOND) < GEN_9)
                {
                    // Can't use TryBattleFormChange as we can't test form change const data changes.
                    gLastUsedAbility = ability;
                    GetBattlerPartyState(battler)->battleBondBoost = TRUE;
                    PREPARE_SPECIES_BUFFER(gBattleTextBuff1, gBattleMons[battler].species);
                    GetBattlerPartyState(battler)->changedSpecies = gBattleMons[battler].species;
                    gBattleMons[battler].species = SPECIES_GRENINJA_ASH;
                    BattleScriptCall(BattleScript_BattleBondActivatesOnMoveEndAttacker);
                    effect = TRUE;
                }
                /*else
                {
                    u32 numStatBuffs = 0;
                    if (CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN, ability))
                    {
                        gBattleScripting.animArg1 = GET_STAT_BUFF_ID(STAT_ATK) + STAT_ANIM_PLUS1;
                        numStatBuffs++;
                    }
                    if (CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN, ability))
                    {
                        gBattleScripting.animArg1 = GET_STAT_BUFF_ID(STAT_SPATK) + STAT_ANIM_PLUS1;
                        numStatBuffs++;
                    }
                    if (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN, ability))
                    {
                        gBattleScripting.animArg1 = GET_STAT_BUFF_ID(STAT_SPEED) + STAT_ANIM_PLUS1;
                        numStatBuffs++;
                    }

                    if (numStatBuffs > 0)
                    {
                        if (numStatBuffs > 1)
                            gBattleScripting.animArg1 = STAT_ANIM_MULTIPLE_PLUS1;

                        gLastUsedAbility = ability;
                        gBattlerAbility = battler;
                        GetBattlerPartyState(battler)->battleBondBoost = TRUE;
                        BattleScriptCall(BattleScript_EffectBattleBondStatIncrease);
                        effect = TRUE;
                    }
                }*/
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_OPPORTUNIST:
        switch (ability)
        {
        case ABILITY_OPPORTUNIST:
            if (gProtectStructs[battler].activateOpportunist == 2)
            {
                gBattleScripting.battler = battler;
                gProtectStructs[battler].activateOpportunist--;
                ChooseStatBoostAnimation(battler);
                BattleScriptCall(BattleScript_OpportunistCopyStatChange);
                effect = 1;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_IMMUNITY:
        effect = TryImmunityAbilityHealStatus(battler);
        if (effect)
            return effect;
        break;
    case ABILITYEFFECT_SYNCHRONIZE:
        if (gLastUsedAbility == ABILITY_SYNCHRONIZE && gBattleStruct->synchronizeMoveEffect != MOVE_EFFECT_NONE)
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerTarget;
            RecordAbilityBattle(gBattlerTarget, ABILITY_SYNCHRONIZE);

            if (GetConfig(B_SYNCHRONIZE_TOXIC) < GEN_5 && gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

            if (CanSetNonVolatileStatus(
                    gBattlerTarget,
                    gBattlerAttacker,
                    gLastUsedAbility,
                    GetBattlerAbility(gBattlerAttacker),
                    gBattleStruct->synchronizeMoveEffect,
                    CHECK_TRIGGER))
            {
                gEffectBattler = gBattlerAttacker;
                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, ABILITY_SYNCHRONIZE);
                BattleScriptCall(BattleScript_SynchronizeActivates);
                effect++;
            }
            else // Synchronize ability pop up still shows up even if status fails
            {
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;
        }
        break;
    case ABILITYEFFECT_ATK_SYNCHRONIZE: //vsonic
        if (gLastUsedAbility == ABILITY_SYNCHRONIZE && gBattleStruct->synchronizeMoveEffect != MOVE_EFFECT_NONE)
        {
            gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
            RecordAbilityBattle(gBattlerAttacker, ABILITY_SYNCHRONIZE);

            if (GetConfig(B_SYNCHRONIZE_TOXIC) < GEN_5 && gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

            if (CanSetNonVolatileStatus(
                    gBattlerAttacker,
                    gBattlerTarget,
                    gLastUsedAbility,
                    GetBattlerAbility(gBattlerAttacker),
                    gBattleStruct->synchronizeMoveEffect,
                    CHECK_TRIGGER))
            {
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

                gEffectBattler = gBattlerTarget;
                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, ABILITY_SYNCHRONIZE);
                BattleScriptCall(BattleScript_SynchronizeActivates);
                effect++;
            }
            else // Synchronize ability pop up still shows up even if status fails
            {
                BattleScriptCall(BattleScript_AbilityPopUp);
            }
            gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_NONE;
        }
        break;
    case ABILITYEFFECT_TERA_SHIFT:
        if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_SWITCH_IN, ability))
        {
            gBattleScripting.battler = battler;
            gLastUsedAbility = ability;
            //gBattleScripting.abilityPopupOverwrite = gLastUsedAbility = ability;
            BattleScriptCall(BattleScript_BattlerFormChangeWithString);
            effect++;
        }
        break;
    case ABILITYEFFECT_NEUTRALIZINGGAS:
        if (ability == ABILITY_NEUTRALIZING_GAS && !gBattleMons[battler].volatiles.neutralizingGas)
        {
            gBattleMons[battler].volatiles.neutralizingGas = TRUE;
            gBattlerAbility = battler;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_NEUTRALIZING_GAS;
            BattleScriptCall(BattleScript_SwitchInAbilityMsg);
            effect++;
        }
        break;
    case ABILITYEFFECT_UNNERVE:
        switch (ability)
        {
        case ABILITY_UNNERVE:
            if (shouldAbilityTrigger && !gBattleMons[battler].volatiles.unnerveActivated)
            {
                gBattleScripting.battler = battler;
                gEffectBattler = GetOppositeBattler(battler);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_UNNERVE;
                gBattleMons[battler].volatiles.unnerveActivated = TRUE;
                BattleScriptCall(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_AS_ONE_ICE_RIDER:
        case ABILITY_AS_ONE_SHADOW_RIDER:
            if (shouldAbilityTrigger && !gBattleMons[battler].volatiles.unnerveActivated)
            {
                gBattleScripting.battler = battler;
                gEffectBattler = GetOppositeBattler(battler);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_ASONE;
                gBattleMons[battler].volatiles.unnerveActivated = TRUE;
                BattleScriptCall(BattleScript_ActivateAsOne);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_COMMANDER:
        gBattleScripting.battler = battler;
        partner = BATTLE_PARTNER(battler);
        switch (ability)
        {
        case ABILITY_COMMANDER:
            if (IsBattlerAlive(partner)
             && IsBattlerAlive(battler)
             && gBattleStruct->battlerState[partner].commanderType == COMMANDER_NONE
             && gBattleMons[partner].species == SPECIES_DONDOZO
             && GET_BASE_SPECIES_ID(GetMonData(GetBattlerMon(battler), MON_DATA_SPECIES)) == SPECIES_TATSUGIRI)
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = partner;
                gBattleStruct->battlerState[battler].commandingPartner = TRUE;
                gBattleStruct->battlerState[partner].commanderType = GetCommanderType(gBattleMons[battler].species);
                gBattleMons[battler].volatiles.semiInvulnerable = STATE_COMMANDER;
                if (gBattleMons[battler].volatiles.confusionTurns > 0)
                    gBattleMons[battler].volatiles.confusionTurns--;
                BtlController_EmitSpriteInvisibility(battler, B_COMM_TO_CONTROLLER, TRUE);
                MarkBattlerForControllerExec(battler);
                BattleScriptCall(BattleScript_CommanderActivates);
                effect++;
            }
            break;
        case ABILITY_BATTERY:
            if (IsBattlerAlive(partner)
             && IsBattlerAlive(battler)
             && gBattleStruct->battlerState[partner].commanderType == COMMANDER_NONE
             && gBattleMons[partner].species == SPECIES_VIKAVOLT
             && GET_BASE_SPECIES_ID(GetMonData(GetBattlerMon(battler), MON_DATA_SPECIES)) == SPECIES_CHARJABUG)
            {
                SaveBattlerAttacker(gBattlerAttacker);
                gBattlerAttacker = partner;
                gBattleStruct->battlerState[battler].commandingPartner = TRUE;
                gBattleStruct->battlerState[partner].commanderType = GetCommanderType(gBattleMons[battler].species);
                gBattleMons[battler].volatiles.semiInvulnerable = STATE_COMMANDER;
                if (gBattleMons[battler].volatiles.confusionTurns > 0)
                    gBattleMons[battler].volatiles.confusionTurns--;
                BtlController_EmitSpriteInvisibility(battler, B_COMM_TO_CONTROLLER, TRUE);
                MarkBattlerForControllerExec(battler);
                BattleScriptCall(BattleScript_BatteryActivates);
                effect++;
            }//smaller boost than commander think need change so base effect stops working?
            break;//think done
        case ABILITY_HOSPITALITY:
            if (shouldAbilityTrigger
             && IsDoubleBattle()
             && !gSideStatuses[GetBattlerSide(partner)] & SIDE_STATUS_HEAL_BLOCK
             && gBattleMons[partner].hp < gBattleMons[partner].maxHP
             && IsBattlerAlive(partner))
            {
                gEffectBattler = partner;
                SetHealAmount(partner, GetNonDynamaxMaxHP(partner) / 4);
                BattleScriptCall(BattleScript_HospitalityActivates);
                effect++;
            }
            break;
        case ABILITY_COSTAR:
            if (shouldAbilityTrigger
             && IsDoubleBattle()
             && IsBattlerAlive(partner)
             && BattlerHasCopyableChanges(partner))
            {
                for (i = 0; i < NUM_BATTLE_STATS; i++)
                    gBattleMons[battler].statStages[i] = gBattleMons[partner].statStages[i];
                // Copy crit boosts (Focus Energy, Dragon Cheer, G-Max Chi Strike)
                gBattleMons[battler].volatiles.focusEnergy = gBattleMons[partner].volatiles.focusEnergy;
                gBattleMons[battler].volatiles.dragonCheer = gBattleMons[partner].volatiles.dragonCheer;
                gEffectBattler = partner;
                BattleScriptCall(BattleScript_CostarActivates);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_ON_WEATHER: // For ability effects that activate when the battle weather changes.
        if (!IsBattlerAlive(battler))
            return effect;
        gLastUsedAbility = GetBattlerAbility(battler);
        switch (gLastUsedAbility)
        {
        case ABILITY_FORECAST:
        case ABILITY_FLOWER_GIFT:
        case ABILITY_ICE_FACE:
        {
            enum BattlerId battlerWeatherAffected = IsBattlerWeatherAffected(battler, gBattleWeather);
            if (battlerWeatherAffected && !CanBattlerFormChange(battler, FORM_CHANGE_BATTLE_WEATHER))
            {
                // If Hail/Snow activates when in Eiscue is in base, prevent reversion when Eiscue Noice gets broken
                gBattleMons[battler].volatiles.weatherAbilityDone = TRUE;
            }

            if (((!gBattleMons[battler].volatiles.weatherAbilityDone && battlerWeatherAffected)
             || gBattleWeather == WEATHER_NONE
             || !HasWeatherEffect()) // Air Lock active
             && TryBattleFormChange(battler, FORM_CHANGE_BATTLE_WEATHER, gLastUsedAbility))
            {
                if (gLastUsedAbility == ABILITY_ICE_FACE)
                    GetBattlerPartyState(battler)->numPhysHits = 0;
                gBattleScripting.battler = battler;
                gBattleMons[battler].volatiles.weatherAbilityDone = TRUE;
                BattleScriptCall(BattleScript_BattlerFormChangeWithString);
                effect++;
            }
            break;
        }
        case ABILITY_PROTOSYNTHESIS:
            if (!gBattleMons[battler].volatiles.weatherAbilityDone
             && (gBattleWeather & WEATHER_SUN) && HasWeatherEffect()
             && !gBattleMons[battler].volatiles.transformed
             && !gBattleMons[battler].volatiles.boosterEnergyActivated)
            {
                gBattleMons[battler].volatiles.weatherAbilityDone = TRUE;
                gBattleMons[battler].volatiles.paradoxBoostedStat = GetParadoxHighestStatId(battler);
                PREPARE_STAT_BUFFER(gBattleTextBuff1, gBattleMons[battler].volatiles.paradoxBoostedStat);
                gBattleScripting.battler = battler;
                BattleScriptCall(BattleScript_ProtosynthesisActivates);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_ON_TERRAIN:  // For ability effects that activate when the field terrain changes.
        if (!IsBattlerAlive(battler))
            return effect;
        gLastUsedAbility = GetBattlerAbility(battler);
        switch (gLastUsedAbility)
        {
        case ABILITY_MIMICRY:
            if (!gBattleMons[battler].volatiles.terrainAbilityDone && ChangeTypeBasedOnTerrain(battler))
            {
                gBattleMons[battler].volatiles.terrainAbilityDone = TRUE;
                ChangeTypeBasedOnTerrain(battler);
                gBattlerAbility = gBattleScripting.battler = battler;
                BattleScriptCall(BattleScript_MimicryActivates);
                effect++;
            }
            break;
        case ABILITY_QUARK_DRIVE:
            if (!gBattleMons[battler].volatiles.terrainAbilityDone
             && gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN
             && !gBattleMons[battler].volatiles.transformed
             && !gBattleMons[battler].volatiles.boosterEnergyActivated)
            {
                gBattleMons[battler].volatiles.terrainAbilityDone = TRUE;
                gBattleMons[battler].volatiles.paradoxBoostedStat = GetParadoxHighestStatId(battler);
                PREPARE_STAT_BUFFER(gBattleTextBuff1, gBattleMons[battler].volatiles.paradoxBoostedStat);
                gBattlerAbility = gBattleScripting.battler = battler;
                BattleScriptCall(BattleScript_QuarkDriveActivates);
                effect++;
            }
            break;
        default:
            break;
        }
        break;
    case ABILITYEFFECT_PRE_HIT_ACTIVATE:

        gLastUsedAbility = GetBattlerAbility(battler);
        switch (gLastUsedAbility)
        {
        case ABILITY_COLOR_CHANGE:
            if (move != MOVE_STRUGGLE
            //&& battler != gBattlerAttacker
            && battler == gBattlerTarget //with add gulp missle here need split battle side
            && IsBattlerAlive(battler)
            && !IsBattleMoveStatus(move)
            && !IS_BATTLER_OF_TYPE(battler, moveType)
            && moveType != TYPE_STELLAR
            && moveType != TYPE_MYSTERY
            && GetActiveGimmick(battler) != GIMMICK_TERA
            && !gSpecialStatuses[battler].preHitAbilityDone
            )
            {
                gBattlerAbility = battler; //pretty sure is for abilitypopup
                gBattleStruct->shouldPrintPreHitAbilityText = TRUE;
                gSpecialStatuses[battler].preHitAbilityDone = TRUE;
                SET_BATTLER_TYPE2(battler, moveType);
                effect++;//affect works but can't yet workout how to get battlescript and ability popup working
            }            
            break;//unsure if this version of effect believe would not be affected by future sight or doom desire
        case ABILITY_GULP_MISSILE:
            if (CanActivateGulpMissle(move)
            && battler == gBattlerAttacker
            && gBattleMons[battler].species == SPECIES_CRAMORANT
            && GetActiveGimmick(battler) != GIMMICK_DYNAMAX
            && !gSpecialStatuses[battler].preHitAbilityDone)
            {
                //since want form change to use pre heal hp
                //attempt to store hp and pass back to passivehp after heal
                s32 storedHp = gBattleMons[battler].hp;
                

                if (CanBattlerHeal(battler))
                {
                    s32 healAmount = 7; //potentially 6
                    SetHealAmount(battler, GetNonDynamaxMaxHP(battler) / healAmount);
                    gBattlerAbility = battler; //pretty sure is for abilitypopup
                    gBattleStruct->shouldPrintPreHitAbilityText = TRUE;
                    gSpecialStatuses[battler].preHitAbilityDone = TRUE;
                    BattleScriptCall(BattleScript_AbilityHpHeal);
                }
                SetPassiveDamageAmount(battler, storedHp);
                effect++;               
                
            }
            break;//think do call basic anim heal here then have print text come in other function

        }
    
    }

    if (effect)
    {
        RecordAbilityBattle(battler, gLastUsedAbility);
        gBattlerAbility = battler;
    }

    return effect;
}

bool32 TryPrimalReversion(enum BattlerId battler)
{
    if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_PRIMAL_REVERSION, GetBattlerAbility(battler)))
    {
        gBattleScripting.battler = battler;
        BattleScriptCall(BattleScript_PrimalReversion);
        return TRUE;
    }
    return FALSE;
}

bool32 IsNeutralizingGasOnField(void)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (gBattleMons[i].volatiles.neutralizingGas && !gBattleMons[i].volatiles.gastroAcid)
            return TRUE;
    }

    return FALSE;
}

bool32 IsMoldBreakerTypeAbility(enum BattlerId battler, enum Ability ability)
{
    if (gBattleMons[battler].volatiles.gastroAcid)
        return FALSE;

    if (ability == ABILITY_MOLD_BREAKER
     || ability == ABILITY_TERAVOLT
     || ability == ABILITY_TURBOBLAZE
     || (ability == ABILITY_MYCELIUM_MIGHT && IsBattleMoveStatus(gCurrentMove)))
    {
        RecordAbilityBattle(battler, ability);
        return TRUE;
    }

    return FALSE;
}

static inline bool32 CanBreakThroughAbility(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 hasAbilityShield, u32 ignoreMoldBreaker)
{
    if (hasAbilityShield || ignoreMoldBreaker || battlerDef == battlerAtk)
        return FALSE;
    return gBattleStruct->moldBreakerActive && gAbilitiesInfo[gBattleMons[battlerDef].ability].breakable;
}

u32 GetBattlerAbilityNoAbilityShield(enum BattlerId battler)
{
    return GetBattlerAbilityInternal(battler, FALSE, TRUE);
}

u32 GetBattlerAbilityIgnoreMoldBreaker(enum BattlerId battler)
{
    return GetBattlerAbilityInternal(battler, TRUE, FALSE);
}

enum Ability GetBattlerAbility(enum BattlerId battler)
{
    return GetBattlerAbilityInternal(battler, FALSE, FALSE);
}

u32 GetBattlerAbilityInternal(enum BattlerId battler, bool32 ignoreMoldBreaker, bool32 noAbilityShield)
{
    bool32 hasAbilityShield = !noAbilityShield && GetBattlerHoldEffectIgnoreAbility(battler) == HOLD_EFFECT_ABILITY_SHIELD;
    bool32 abilityCantBeSuppressed = gAbilitiesInfo[gBattleMons[battler].ability].cantBeSuppressed;

    if (abilityCantBeSuppressed)
    {
        // Edge case: pokemon under the effect of gastro acid transforms into a pokemon with Comatose (Todo: verify how other unsuppressable abilities behave)
        if (gBattleMons[battler].volatiles.transformed
            && gBattleMons[battler].volatiles.gastroAcid
            && gBattleMons[battler].ability == ABILITY_COMATOSE)
                return ABILITY_NONE;

        if (CanBreakThroughAbility(gBattlerAttacker, battler, hasAbilityShield, ignoreMoldBreaker))
            return ABILITY_NONE;

        return gBattleMons[battler].ability;
    }

    if (gBattleMons[battler].volatiles.gastroAcid)
        return ABILITY_NONE;

    if (!hasAbilityShield
     && IsNeutralizingGasOnField()
     && (gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS || gBattleMons[battler].volatiles.gastroAcid))
        return ABILITY_NONE;

    if (CanBreakThroughAbility(gBattlerAttacker, battler, hasAbilityShield, ignoreMoldBreaker))
        return ABILITY_NONE;

    return gBattleMons[battler].ability;
}

//make new chategory of ability that gives mon the same bonuses as being of said type
//ex ice types can't be frozen, and not hurt by hail, and get hail bonus
//poison types can't be poisened, immune to poison moves(maybe)
//bug dont get confused,
//electric cant be paralyzed by electric moves
//normal gets joat
//think will keep this separted from type chart relations
//need to be considerate of how I use this, as may not want ability to give ALL characteristcs
//ex toadstool nymph just gives fairy stab
//while sixth sense isn't exactly linked directly to bug, but gives the bug type immunity to confusion selfhit
//but I do like the idea of making mon linked w a type without needing them to specifically be the type
//ex could give tepig line fire affinity, and make like toadstool nymph where it gives fire stab
//now if I have separate abilities that give different varying degrees of affinity/or different effects
//I could add an abilityEffect to this function u16, so I could specify the ability I'm looking for
//but that would break the battle script changes for jumpiftypeaffinity
//hmm actually that wouldn't even work for this either, hmm no it would work
//would be battler type factor abilityeffect
//would auto go to only the type case I'm looking for,
//than would be, is battler type or ability == abilityeffect
//wouldn't see the specific abilities that affect it here within function
//but logic would work
//anyway need give more thought to establish how I'll do this
//could make separate function for most of repo for specificying the ability that shuold get effect
//than just keep this for bs, with the abilities that get the full set of affinities
//TypeAffinityCheck - will be for type and specific ability
//changed but realized target doesnt work as some case are offense affinity user i.e curse and sure hit poison
//removing ai check with addition of ctx struct can get what  need from that
//don't think can use ctx as argument tho
#define NEW_ABILITY_CATEGORY //-use only for things that don't affect type chart relations
bool8 DoesBattlerGetTypeBasedAffinity(enum Ability atkAbility, enum BattlerId battlerToCheck, enum Ability battlerAbility, u8 typeFactor, bool32 SelfAffecting)
{
    //extra protection for effects that check partner 
    //takes place before attacks so think should be fine without alive check?
    //so rather than an automatic check that would
    //ignore moldbreaker block if target was user
    //I instead set it to require specifically setting
    //each case to properly set if ability should check for moldbreaker...
    //stupid but still difficult to get atk battler and def battler for each argumetn
    //want atkability and battler to check and battlerAtk
    //so need battlerAtk  atkAbility  battlertocheck battlerability and then type
    //wish it was but not any simpler if I use contxt, would require set before I use func
    //annoying to set wbattleratk could instead go back to old method
    //have bool at end checks whether self affecting
    //issue is adding atk ability and battleratk
    //requires large changes to be able to pass from terrain functions
    //hazard set and isbattlergrounded functions etc.
    //going back I don't need battleratk I really can just use have a bool for selftarget
    //I just brain farted and couldn't realize it, should be fine to pass from
    //ai functions
    if (SelfAffecting == FALSE
    && atkAbility == ABILITY_MOLD_BREAKER)
        return FALSE;

    switch(typeFactor)
    {
        case TYPE_FLYING:
        {
            return (IS_BATTLER_OF_TYPE(battlerToCheck, typeFactor) || battlerAbility == ABILITY_AVIATOR);
                
        }
        break;
        case TYPE_FIRE:
        {
            return (IS_BATTLER_OF_TYPE(battlerToCheck, typeFactor) || battlerAbility == ABILITY_TORCHSOUL);
                
        }
        break;
        case TYPE_BUG:
        {
            return (IS_BATTLER_OF_TYPE(battlerToCheck, typeFactor) || battlerAbility == ABILITY_APOTHEOSCENT);
                   
        }
        break;
        case TYPE_POISON:
        {
            return (IS_BATTLER_OF_TYPE(battlerToCheck, typeFactor) || battlerAbility == ABILITY_GRUNGE);
                   
        }
        break;
        case TYPE_FAIRY:
        {
            return (IS_BATTLER_OF_TYPE(battlerToCheck, typeFactor) || battlerAbility == ABILITY_TOADSTOOL_NYMPH);
                
        }//toadstool nymph is just to give stab on fairy moves
        break;
        default:
        {
            return (IS_BATTLER_OF_TYPE(battlerToCheck, typeFactor));
                
        }

    }

}

u32 IsAbilityOnSide(enum BattlerId battler, enum Ability ability)
{
    if (IsBattlerAlive(battler) && GetBattlerAbility(battler) == ability)
        return battler + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battler)) && GetBattlerAbility(BATTLE_PARTNER(battler)) == ability)
        return BATTLE_PARTNER(battler) + 1;
    else
        return 0;
}

u32 IsAbilityOnOpposingSide(enum BattlerId battler, enum Ability ability)
{
    return IsAbilityOnSide(BATTLE_OPPOSITE(battler), ability);
}

u32 IsAbilityOnField(enum Ability ability)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && GetBattlerAbility(i) == ability)
            return i + 1;
    }

    return 0;
}

u32 IsAbilityOnFieldExcept(enum BattlerId battler, enum Ability ability)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != battler && IsBattlerAlive(i) && GetBattlerAbility(i) == ability)
            return i + 1;
    }

    return 0;
}

u32 IsTypeOnFieldExcept(enum BattlerId battler, enum Type type)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != battler && IsBattlerAlive(i) && IS_BATTLER_OF_TYPE(i) == type)
            return i + 1;
    }

    return 0;
}

u32 IsAbilityPreventingEscape(enum BattlerId battler)
{
    if (B_GHOSTS_ESCAPE >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return 0;

    bool32 isBattlerGrounded = IsBattlerGrounded_IgnoreException(battler, GetBattlerAbility(battler), GetBattlerHoldEffect(battler));
    for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
    {
        if (battler == battlerDef || IsBattlerAlly(battler, battlerDef))
            continue;

        enum Ability ability = GetBattlerAbility(battlerDef);

        if (ability == ABILITY_SHADOW_TAG && (B_SHADOW_TAG_ESCAPE <= GEN_3 || GetBattlerAbility(battler) != ABILITY_SHADOW_TAG))
            return battlerDef + 1;

        if (ability == ABILITY_ARENA_TRAP && isBattlerGrounded)
            return battlerDef + 1;

        if (ability == ABILITY_MAGNET_PULL && IS_BATTLER_OF_TYPE(battler, TYPE_STEEL))
            return battlerDef + 1;
    }

    return 0;
}

//run from battle not switch
//need add flying type to this
//well add back my custom work
//seems weird battler can't run from wild battle if in commander state
//but apparently is default
bool32 CanBattlerEscape(enum BattlerId battler) // no ability check
{
    if (gBattleStruct->battlerState[battler].commanderType != COMMANDER_NONE)
        return FALSE;
    else if (B_GHOSTS_ESCAPE >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TRUE;
    else if (gBattleMons[battler].volatiles.escapePrevention)
        return FALSE;
    else if (gBattleMons[battler].volatiles.wrapped)
        return FALSE;
    else if (gBattleMons[battler].volatiles.rooted)
        return FALSE;
    else if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
        return FALSE;
    else if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return FALSE;
    else
        return TRUE;
}

void BattleScriptExecute(const u8 *BS_ptr)
{
    gBattlescriptCurrInstr = BS_ptr;
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands_PopCallbacksStack;
    gCurrentActionFuncId = 0;
}

void BattleScriptPushCursorAndCallback(const u8 *BS_ptr)
{
    BattleScriptCall(BS_ptr);
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands;
}

bool32 IsPsychicTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, ability, holdEffect, fieldStatuses, STATUS_FIELD_PSYCHIC_TERRAIN);
}

bool32 IsMistyTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, ability, holdEffect, fieldStatuses, STATUS_FIELD_MISTY_TERRAIN);
}

bool32 IsGrassyTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, ability, holdEffect, fieldStatuses, STATUS_FIELD_GRASSY_TERRAIN);
}

bool32 IsElectricTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, ability, holdEffect, fieldStatuses, STATUS_FIELD_ELECTRIC_TERRAIN);
}

bool32 IsAnyTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses)
{
    return IsBattlerTerrainAffected(battler, ability, holdEffect, fieldStatuses, STATUS_FIELD_TERRAIN_ANY);
}

bool32 IsBattlerTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatus, u32 terrainFlag)
{
    if (!(fieldStatus & terrainFlag))
        return FALSE;
    if (IsSemiInvulnerable(battler, CHECK_ALL))
        return FALSE;
    
    else if (ability == ABILITY_EVERGREEN
    && terrainFlag == STATUS_FIELD_GRASSY_TERRAIN)
        return TRUE;

    return IsBattlerGrounded_IgnoreException(battler, ability, holdEffect);
}

u32 GetHighestStatId(enum BattlerId battler)
{
    u32 highestId = STAT_ATK;
    bool32 wonderRoom = (gFieldStatuses & STATUS_FIELD_WONDER_ROOM) != 0;
    u32 highestStat = gBattleMons[battler].attack;

    for (u32 stat = STAT_DEF; stat < NUM_STATS; stat++)
    {
        if (stat == STAT_SPEED)
            continue;

        u32 statVal;
        switch (stat)
        {
        case STAT_ATK:
            statVal = gBattleMons[battler].attack;
            break;
        case STAT_DEF:
            statVal = wonderRoom ? gBattleMons[battler].spDefense : gBattleMons[battler].defense;
            break;
        case STAT_SPATK:
            statVal = gBattleMons[battler].spAttack;
            break;
        case STAT_SPDEF:
            statVal = wonderRoom ? gBattleMons[battler].defense : gBattleMons[battler].spDefense;
            break;
        default:
            continue;
        }

        if (statVal > highestStat)
        {
            highestStat = statVal;
            highestId = stat;
        }
    }

    if (gBattleMons[battler].speed > highestStat)
        highestId = STAT_SPEED;

    return highestId;
}

static u32 GetStatValueWithStages(enum BattlerId battler, u32 stat)
{
    u32 statValue;

    switch (stat)
    {
    case STAT_ATK:
        statValue = gBattleMons[battler].attack;
        break;
    case STAT_DEF:
        statValue = gBattleMons[battler].defense;
        break;
    case STAT_SPATK:
        statValue = gBattleMons[battler].spAttack;
        break;
    case STAT_SPDEF:
        statValue = gBattleMons[battler].spDefense;
        break;
    case STAT_SPEED:
        statValue = gBattleMons[battler].speed;
        break;
    default:
        return 0;
    }

    statValue *= gStatStageRatios[gBattleMons[battler].statStages[stat]][0];
    statValue /= gStatStageRatios[gBattleMons[battler].statStages[stat]][1];

    return statValue;
}

u32 GetParadoxHighestStatId(enum BattlerId battler)
{
    u32 highestId = STAT_ATK;
    u32 highestStat = GetStatValueWithStages(battler, STAT_ATK);

    for (u32 stat = STAT_DEF; stat < NUM_STATS; stat++)
    {
        if (stat == STAT_SPEED)
            continue;

        u32 statValue = GetStatValueWithStages(battler, stat);
        if (statValue > highestStat)
        {
            highestStat = statValue;
            highestId = stat;
        }
    }

    u32 speed = GetStatValueWithStages(battler, STAT_SPEED);
    if (speed > highestStat)
        highestId = STAT_SPEED;

    return highestId;
}

static void ResetParadoxWeatherStat(enum BattlerId battler)
{
    if (gBattleMons[battler].ability == ABILITY_PROTOSYNTHESIS
     && !gBattleMons[battler].volatiles.boosterEnergyActivated)
        gBattleMons[battler].volatiles.paradoxBoostedStat = 0;
}

static void ResetParadoxTerrainStat(enum BattlerId battler)
{
    if (gBattleMons[battler].ability == ABILITY_QUARK_DRIVE
     && !gBattleMons[battler].volatiles.boosterEnergyActivated)
        gBattleMons[battler].volatiles.paradoxBoostedStat = 0;
}

u32 GetParadoxBoostedStatId(enum BattlerId battler)
{
    if (gBattleMons[battler].volatiles.paradoxBoostedStat == 0)
        gBattleMons[battler].volatiles.paradoxBoostedStat = GetParadoxHighestStatId(battler);

    return gBattleMons[battler].volatiles.paradoxBoostedStat;
}

//with swap to cansetnonvolatilestatus
//will need to redo all well no
//just need to slot in my use of abilityaffinity
//vsonic
bool32 CanBeSlept(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum SleepClauseBlock isBlockedBySleepClause)
{
    if (IsSleepClauseActiveForSide(GetBattlerSide(battlerDef)) && isBlockedBySleepClause != NOT_BLOCKED_BY_SLEEP_CLAUSE)
        return FALSE;

    if (isBlockedBySleepClause == NOT_BLOCKED_BY_SLEEP_CLAUSE)
        gBattleStruct->sleepClauseNotBlocked = TRUE;

    bool32 effect = FALSE;

    //atk ability would matter for my set
    //because mold breaker ignoring affinities
    //think just make inline to check if ability moldbreaker
    //if yes return moldbreaker otherwise ability_none
    //in cansetnonvola just add check for IsMoldBreakerTypeAbility
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            abilityAtk, // attacker ability does not matter
            abilityDef,
            MOVE_EFFECT_SLEEP, // also covers yawn
            CHECK_TRIGGER))
        effect = TRUE;

    gBattleStruct->sleepClauseNotBlocked = FALSE;
    return effect;
}

bool32 CanBePoisoned(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            abilityAtk,
            abilityDef,
            MOVE_EFFECT_TOXIC, // also covers poison
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

// TODO: check order of battlerAtk and battlerDef
bool32 CanBeBurned(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            ABILITY_NONE, // attacker ability does not matter
            abilityDef,
            MOVE_EFFECT_BURN,
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

bool32 CanBeParalyzed(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            ABILITY_NONE, // attacker ability does not matter
            abilityDef,
            MOVE_EFFECT_PARALYSIS,
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

bool32 CanBeFrozen(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            ABILITY_NONE, // attacker ability does not matter
            abilityDef,
            MOVE_EFFECT_FREEZE,
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

// Unused, technically also redundant because it is just a copy of CanBeFrozen
//differetn will be used since using both free and frostbite
//diff will be can't get frostbite will frozen
bool32 CanGetFrostbite(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef)
{
    if (CanSetNonVolatileStatus(
            battlerAtk,
            battlerDef,
            ABILITY_NONE, // attacker ability does not matter
            abilityDef,
            MOVE_EFFECT_FROSTBITE, // also covers frostbite
            CHECK_TRIGGER))
        return TRUE;
    return FALSE;
}

bool32 CanSetNonVolatileStatus(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum MoveEffect effect, enum ResultOption option)
{
    const u8 *battleScript = NULL;
    u32 sideBattler = ABILITY_NONE;
    bool32 abilityAffected = FALSE;

    // Move specific checks
    switch (effect)
    {
    case MOVE_EFFECT_POISON:
    case MOVE_EFFECT_TOXIC:
        if (gBattleMons[battlerDef].status1 & STATUS1_TOXIC_POISON)
        {
            battleScript = BattleScript_AlreadyPoisoned;
        }
        else if (abilityAtk != ABILITY_CORROSION && IS_BATTLER_ANY_TYPE(battlerDef, TYPE_POISON, TYPE_STEEL))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if ((sideBattler = IsAbilityOnSide(battlerDef, ABILITY_PASTEL_VEIL)))
        {
            abilityAffected = TRUE;
            battlerDef = sideBattler - 1;
            abilityDef = ABILITY_PASTEL_VEIL;
            battleScript = BattleScript_ImmunityProtected;
        }
        else if (abilityDef == ABILITY_IMMUNITY)
        {
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        break;
    case MOVE_EFFECT_PARALYSIS:
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS)
        {
            battleScript = BattleScript_AlreadyParalyzed;
        }
        else if (GetConfig(B_PARALYZE_ELECTRIC) >= GEN_6 && IS_BATTLER_OF_TYPE(battlerDef, TYPE_ELECTRIC))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if (option == RUN_SCRIPT && IsBattlerUnaffectedByMove(battlerDef))
        {
            battleScript = BattleScript_ButItFailed;
        }
        else if (abilityDef == ABILITY_LIMBER)
        {
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        break;
    case MOVE_EFFECT_BURN:
        if (gBattleMons[battlerDef].status1 & STATUS1_BURN)
        {
            battleScript = BattleScript_AlreadyBurned;
        }
        else if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_FIRE))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if (abilityDef == ABILITY_WATER_VEIL || abilityDef == ABILITY_WATER_BUBBLE)
        {
            abilityAffected = TRUE;
            battleScript = BattleScript_ImmunityProtected;
        }
        else if (abilityDef == ABILITY_THERMAL_EXCHANGE)
        {
            abilityAffected = TRUE;
            battleScript = BattleScript_AbilityProtectsDoesntAffect;
        }
        break;
    case MOVE_EFFECT_SLEEP:
        if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP)
        {
            battleScript = BattleScript_AlreadyAsleep;
        }
        else if (UproarWakeUpCheck(battlerDef))
        {
            battleScript = BattleScript_CantMakeAsleep;
        }
        else if (!gBattleStruct->sleepClauseNotBlocked && CanSleepDueToSleepClause(battlerAtk, battlerDef, option))
        {
            battleScript = BattleScript_SleepClauseBlocked;
        }
        else if (IsElectricTerrainAffected(battlerDef, abilityDef, GetBattlerHoldEffect(battlerDef), gFieldStatuses))
        {
            battleScript = BattleScript_ElectricTerrainPrevents;
        }
        else if ((sideBattler = IsAbilityOnSide(battlerDef, ABILITY_SWEET_VEIL)))
        {
            abilityAffected = TRUE;
            battlerDef = sideBattler - 1;
            abilityDef = ABILITY_SWEET_VEIL;
            battleScript = BattleScript_ImmunityProtected;
        }
        else if (abilityDef == ABILITY_VITAL_SPIRIT || abilityDef == ABILITY_INSOMNIA)
        {
            abilityAffected = TRUE;
            battleScript = BattleScript_PrintAbilityMadeIneffective;
        }
        break;
    case MOVE_EFFECT_FREEZE:
    case MOVE_EFFECT_FROSTBITE:
        if (gBattleMons[battlerDef].status1 & (STATUS1_FREEZE | STATUS1_FROSTBITE))
        {
            battleScript = BattleScript_AlreadyBurned;
        }
        else if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE) || IsBattlerWeatherAffected(battlerDef, WEATHER_SUN))
        {
            battleScript = BattleScript_NotAffected;
        }
        else if (abilityDef == ABILITY_MAGMA_ARMOR)
        {
            abilityAffected = TRUE;
            battleScript = BattleScript_NotAffected;
        }
        break;
    default:
        break;
    }

    if (IsNonVolatileStatusBlocked(battlerDef, abilityDef, abilityAffected, battleScript, option))
        return FALSE;

    // Checks that apply to all non volatile statuses
    if (abilityDef == ABILITY_COMATOSE
     || abilityDef == ABILITY_PURIFYING_SALT)
    {
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if (IsMistyTerrainAffected(battlerDef, abilityDef, GetBattlerHoldEffect(battlerDef), gFieldStatuses))
    {
        battleScript = BattleScript_MistyTerrainPrevents;
    }
    else if (IsLeafGuardProtected(battlerDef, abilityDef))
    {
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if (IsShieldsDownProtected(battlerDef, abilityDef))
    {
        abilityAffected = TRUE;
        battleScript = BattleScript_AbilityProtectsDoesntAffect;
    }
    else if ((sideBattler = IsFlowerVeilProtected(battlerDef)))
    {
        abilityAffected = TRUE;
        battlerDef = sideBattler - 1;
        abilityDef = ABILITY_FLOWER_VEIL;
        battleScript = BattleScript_FlowerVeilProtects;
    }
    else if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_SAFEGUARD)
    {
        battleScript = BattleScript_SafeguardProtected;
    }
    else if (gBattleMons[battlerDef].status1 & STATUS1_ANY)
    {
        battleScript = BattleScript_ButItFailed;
    }

    if (IsNonVolatileStatusBlocked(battlerDef, abilityDef, abilityAffected, battleScript, option))
        return FALSE;

    return TRUE;
}


static bool32 IsNonVolatileStatusBlocked(enum BattlerId battlerDef, enum Ability abilityDef, bool32 abilityAffected, const u8 *battleScript, enum ResultOption option)
{
    if (battleScript != NULL)
    {
        if (option == RUN_SCRIPT)
        {
            if (battleScript != BattleScript_NotAffected)
                gBattleStruct->moveResultFlags[battlerDef] |= MOVE_RESULT_FAILED;

            if (abilityAffected)
            {
                gLastUsedAbility = abilityDef;
                gBattleScripting.battler = gBattlerAbility = battlerDef;
                RecordAbilityBattle(battlerDef, abilityDef);
            }

            gBattlescriptCurrInstr = battleScript;
        }

        return TRUE;
    }

    return FALSE;
}

static bool32 CanSleepDueToSleepClause(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum ResultOption option)
{
    // Can freely sleep own partner
    if (IsDoubleBattle() && IsSleepClauseEnabled() && IsBattlerAlly(battlerAtk, battlerDef))
    {
        if (option == RUN_SCRIPT)
            gBattleStruct->battlerState[battlerDef].sleepClauseEffectExempt = TRUE;
        return FALSE;
    }

    if (option == RUN_SCRIPT)
        gBattleStruct->battlerState[battlerDef].sleepClauseEffectExempt = FALSE;
    // Can't sleep if clause is active otherwise
    if (IsSleepClauseActiveForSide(GetBattlerSide(battlerDef)))
        return TRUE;

    return FALSE;
}

bool32 CanBeConfused(enum BattlerId battler)
{
    enum Ability ability = GetBattlerAbility(battler);
    if (gBattleMons[battler].volatiles.confusionTurns > 0
     || IsMistyTerrainAffected(battler, ability, GetBattlerHoldEffect(battler), gFieldStatuses)
     || IsAbilityAndRecord(battler, ability, ABILITY_OWN_TEMPO))
        return FALSE;
    return TRUE;
}

// second argument is 1/X of current hp compared to max hp
bool32 HasEnoughHpToEatBerry(enum BattlerId battler, enum Ability ability, u32 hpFraction, u32 itemId)
{
    if (!IsBattlerAlive(battler))
        return FALSE;
    if (gBattleScripting.overrideBerryRequirements)
        return TRUE;
    if (gBattleMons[battler].hp <= gBattleMons[battler].maxHP / hpFraction)
        return TRUE;

    if (hpFraction <= 4 && GetItemPocket(itemId) == POCKET_BERRIES
         && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2
         && IsAbilityAndRecord(battler, GetBattlerAbility(battler), ABILITY_GLUTTONY))
        return TRUE;

    return FALSE;
}

//vsonic believe don't need furycutter here
void ClearVariousBattlerFlags(enum BattlerId battler)
{
    //gBattleMons[battler].volatiles.furyCutterCounter = 0;
    gBattleMons[battler].volatiles.destinyBond = 0;
    gBattleMons[battler].volatiles.glaiveRush = FALSE;
    gBattleMons[battler].volatiles.grudge = FALSE;
}

void HandleAction_RunBattleScript(void) // identical to RunBattleScriptCommands
{
    if (gBattleControllerExecFlags == 0)
        gBattleScriptingCommandsTable[*gBattlescriptCurrInstr]();
}

u32 SetRandomTarget(enum BattlerId battlerAtk)
{
    u32 target;
    static const u8 targets[2][2] =
    {
        [B_SIDE_PLAYER] = {B_POSITION_OPPONENT_LEFT, B_POSITION_OPPONENT_RIGHT},
        [B_SIDE_OPPONENT] = {B_POSITION_PLAYER_LEFT, B_POSITION_PLAYER_RIGHT},
    };

    if (IsDoubleBattle())
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battlerAtk)][RandomUniform(RNG_RANDOM_TARGET, 0, 1)]);
        if (!IsBattlerAlive(target))
            target ^= BIT_FLANK;
    }
    else
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battlerAtk)][0]);
    }

    return target;
}

u32 GetBattleMoveTarget(enum Move move, enum MoveTarget moveTarget)
{
    u32 targetBattler = 0;
    u32 side;
    enum Type SecondarymoveType = GetTwoTypedMove2ndType(move);
    enum Type moveType = GetBattleMoveType(move);

    if (moveTarget == TARGET_NONE)
        moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, move);

    switch (moveTarget)
    {
    case TARGET_SELECTED:
    case TARGET_SMART:
    case TARGET_OPPONENT:
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (IsAffectedByFollowMe(gBattlerAttacker, side, move))
        {
            targetBattler = gSideTimers[side].followmeTarget;
        }
        else
        {
            //think not using
            //enum Ability battlerAbilityOnField = 0;

            targetBattler = SetRandomTarget(gBattlerAttacker);
            
            
            //vsonic review this see if makes sense
            //make sure am not missing case that if I'm attacking ally
            //move should still get drawn in.
            //all I wanted to remove was ally drawing in moves
            //yeah think is wrong and need add extra case for
            //if targetbattler equals ally and use opposite attacker and partner opposite attaacker
            //then can keep below as else case
           if (!CanAbilityAbsorbMoveType(targetBattler, moveType, SecondarymoveType))
           {
                
                if (CanAbilityAbsorbMoveType(GetPartnerBattler(targetBattler), moveType, SecondarymoveType)
                && CanBattlerAbilityDrawInMove(GetPartnerBattler(targetBattler)))
                {
                    targetBattler =  GetPartnerBattler(targetBattler);
                    RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                }
           }
            
            //if type is absorbable but target battler doesnt have
            //redirect ability check if mon on side does
            //if so assign targetId to them
            /*if (moveType == TYPE_ELECTRIC && GetBattlerAbility(targetBattler) != ABILITY_LIGHTNING_ROD)
            {
                if (B_REDIRECT_ABILITY_ALLIES >= GEN_4)
                    battlerAbilityOnField = IsAbilityOnField(ABILITY_LIGHTNING_ROD);
                else
                    battlerAbilityOnField = IsAbilityOnOpposingSide(targetBattler, ABILITY_LIGHTNING_ROD);

                if (battlerAbilityOnField > 0 && (battlerAbilityOnField - 1) != gBattlerAttacker)
                {
                    targetBattler = battlerAbilityOnField - 1;
                    RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                    gSpecialStatuses[targetBattler].abilityRedirected = TRUE;
                }
            }
            else if (moveType == TYPE_WATER && GetBattlerAbility(targetBattler) != ABILITY_STORM_DRAIN)
            {
                if (B_REDIRECT_ABILITY_ALLIES >= GEN_4)
                    battlerAbilityOnField = IsAbilityOnField(ABILITY_STORM_DRAIN);
                else
                    battlerAbilityOnField = IsAbilityOnOpposingSide(targetBattler, ABILITY_STORM_DRAIN);

                if (battlerAbilityOnField > 0 && (battlerAbilityOnField - 1) != gBattlerAttacker)
                {
                    targetBattler = battlerAbilityOnField - 1;
                    RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                    gSpecialStatuses[targetBattler].abilityRedirected = TRUE;
                }
            }*/
        }
        break;
    case TARGET_DEPENDS:
    case TARGET_BOTH:
    case TARGET_FOES_AND_ALLY:
        targetBattler = GetOpposingSideBattler(gBattlerAttacker);
        if (IsDoubleBattle() && !IsBattlerAlive(targetBattler))
            targetBattler ^= BIT_FLANK;
        break;
    case TARGET_OPPONENTS_FIELD:
        targetBattler = GetOpposingSideBattler(gBattlerAttacker);
        break;
    case TARGET_RANDOM:
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (IsAffectedByFollowMe(gBattlerAttacker, side, move))
            targetBattler = gSideTimers[side].followmeTarget;
        else if (IsDoubleBattle())
            targetBattler = SetRandomTarget(gBattlerAttacker);
        else
            targetBattler = GetOpposingSideBattler(gBattlerAttacker);
        break;
    case TARGET_USER:
    default:
        targetBattler = gBattlerAttacker;
        break;
    case TARGET_ALLY:
        if (IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker)))
            targetBattler = BATTLE_PARTNER(gBattlerAttacker);
        else
            targetBattler = gBattlerAttacker;
        break;
    }

    gBattleStruct->moveTarget[gBattlerAttacker] = targetBattler;

    return targetBattler;
}

//vsonic
enum Obedience GetAttackerObedienceForAction(void)
{
    s32 rnd;
    s32 calc;
    u8 obedienceLevel = 0;
    u8 levelReferenced;
    enum Ability abilityAtk = GetBattlerAbility(gBattlerAttacker);

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
        return OBEYS;
    if (BattlerHasAi(gBattlerAttacker))
        return OBEYS;

    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && GetBattlerPosition(gBattlerAttacker) == B_POSITION_PLAYER_RIGHT)
        return OBEYS;
    if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
        return OBEYS;
    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        return OBEYS;
    if (B_OBEDIENCE_MECHANICS < GEN_8 && !IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName))
        return OBEYS;
    if (FlagGet(FLAG_BADGE08_GET)) // Rain Badge, ignore obedience altogether
        return OBEYS;

    obedienceLevel = 10;

    if (FlagGet(FLAG_BADGE01_GET)) // Stone Badge
        obedienceLevel = 20;
    if (FlagGet(FLAG_BADGE02_GET)) // Knuckle Badge
        obedienceLevel = 30;
    if (FlagGet(FLAG_BADGE03_GET)) // Dynamo Badge
        obedienceLevel = 40;
    if (FlagGet(FLAG_BADGE04_GET)) // Heat Badge
        obedienceLevel = 50;
    if (FlagGet(FLAG_BADGE05_GET)) // Balance Badge
        obedienceLevel = 60;
    if (FlagGet(FLAG_BADGE06_GET)) // Feather Badge
        obedienceLevel = 70;
    if (FlagGet(FLAG_BADGE07_GET)) // Mind Badge
        obedienceLevel = 80;

    if (B_OBEDIENCE_MECHANICS >= GEN_8
     && !IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName))
        levelReferenced = GetMonData(GetBattlerMon(gBattlerAttacker), MON_DATA_MET_LEVEL);
    else
        levelReferenced = gBattleMons[gBattlerAttacker].level;

    if (levelReferenced <= obedienceLevel)
        return OBEYS;

    rnd = Random();
    calc = (levelReferenced + obedienceLevel) * (rnd & 255) >> 8;
    if (calc < obedienceLevel)
        return OBEYS;

    //  Clear the Z-Move flags if the battler is disobedient as to not waste the Z-Move
    if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_Z_MOVE)
    {
        gBattleStruct->gimmick.activated[gBattlerAttacker][GIMMICK_Z_MOVE] = FALSE;
        gBattleStruct->gimmick.activeGimmick[GetBattlerSide(gBattlerAttacker)][gBattlerPartyIndexes[gBattlerAttacker]] = GIMMICK_NONE;
    }

    // is not obedient
    enum BattleMoveEffects moveEffect = GetMoveEffect(gCurrentMove);
    if (MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_RAGE))
        gBattleMons[gBattlerAttacker].volatiles.rage = FALSE;
    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP && IsUsableWhileAsleepEffect(moveEffect))
        return DISOBEYS_WHILE_ASLEEP;

    calc = (levelReferenced + obedienceLevel) * ((rnd >> 8) & 255) >> 8;
    if (calc < obedienceLevel)
    {
        calc = CheckMoveLimitations(gBattlerAttacker, 1u << gCurrMovePos, MOVE_LIMITATIONS_ALL);
        if (calc == ALL_MOVES_MASK) // all moves cannot be used
            return DISOBEYS_LOAFS;
        else // use a random move
            do
                gCurrMovePos = gChosenMovePos = MOD(Random(), MAX_MON_MOVES);
            while ((1u << gCurrMovePos) & calc);
        return DISOBEYS_RANDOM_MOVE;
    }
    else
    {
        obedienceLevel = levelReferenced - obedienceLevel;

        calc = ((rnd >> 16) & 255);
        if (calc < obedienceLevel && CanBeSlept(gBattlerAttacker, gBattlerAttacker, abilityAtk, abilityAtk, NOT_BLOCKED_BY_SLEEP_CLAUSE))
        {
            // try putting asleep
            enum BattlerId i;
            for (i = 0; i < gBattlersCount; i++)
                if (gBattleMons[i].volatiles.uproarTurns)
                    break;
            if (i == gBattlersCount)
                return DISOBEYS_FALL_ASLEEP;
        }
        calc -= obedienceLevel;
        if (calc < obedienceLevel)
            return DISOBEYS_HITS_SELF;
        else
            return DISOBEYS_LOAFS;
    }
}

//put fury cutter logic together
//returns move acc if not move
//vsonic
u32 GetFuryCutterAccuracy(enum Move move, enum BattlerId battlerAtk)
{
    u32 i, furyCutterAccDrop;
    
    if (move == MOVE_FURY_CUTTER) { //still not quite right, doesn't display right message for things like wonderguard

        //Logic for altering animation used in battle_anim_effects_2

        //acc drop effect
        furyCutterAccDrop = GetMoveAccuracy(move);

        for (i = 0; i <= gBattleMons[battlerAtk].volatiles.furyCutterCounter; ++i) { //triggers on second hit, so i = 1 - current num hits, i =3 on4th hit
            
            if (i == 2) //should be 3rd hit
            {
                furyCutterAccDrop = 90; //set 3rd hit to 95, 4th hit remains the same, set main acc to 100, to ensure first 2 hits land
            }
            
            //need to lower this much more
            if (i >= 3) //makes only trigger onlast 4th/5th hit, to slightly lower chance of landing 4th hit if you rolled it
            {
                furyCutterAccDrop -= (i * 2); //think this should be good
                furyCutterAccDrop *= 92; //so far is working to stop the move,
                furyCutterAccDrop /= 100;
            }  //makes 4th hit have 85 accuracy - lower now
            //if (i == 3) 
            //{/
            //   furyCutterAccDrop -= 16; //weighting for last 2 hits, only need to do for one i value as its all passed to next
            //}
            //furyCutterAccDrop *= 95; //so far is working to stop the move,
            //furyCutterAccDrop /= 100;  //may replace with just moveAcc  still don't know why not working
            
        } //seems still overperforming potentially drop above 7 to a 8 or 9? or drop to third hit ni stead of 4th? by changing == 3 to ==2 ?  check later vsonic

        return furyCutterAccDrop;
    } 
    else    
        return GetMoveAccuracy(move);
}

enum HoldEffect GetBattlerHoldEffect(enum BattlerId battler)
{
    return GetBattlerHoldEffectInternal(battler, GetBattlerAbility(battler));
}

enum HoldEffect GetBattlerHoldEffectIgnoreAbility(enum BattlerId battler)
{
    return GetBattlerHoldEffectInternal(battler, ABILITY_NONE);
}

enum HoldEffect GetBattlerHoldEffectInternal(enum BattlerId battler, enum Ability ability)
{
    
    if (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_EMBARGO)
        return HOLD_EFFECT_NONE;
    if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
        return HOLD_EFFECT_NONE;
    if (ability == ABILITY_KLUTZ && !gBattleMons[battler].volatiles.gastroAcid)
        return HOLD_EFFECT_NONE;

    gPotentialItemEffectBattler = battler;

    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffect;
    else
        return GetItemHoldEffect(gBattleMons[battler].item);
}

enum HoldEffect GetBattlerHoldEffectIgnoreNegation(enum BattlerId battler)
{
    gPotentialItemEffectBattler = battler;
    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffect;
    else
        return GetItemHoldEffect(gBattleMons[battler].item);
}

u32 GetBattlerHoldEffectParam(enum BattlerId battler)
{
    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffectParam;
    else
        return GetItemHoldEffectParam(gBattleMons[battler].item);
}

bool32 CanBattlerAvoidContactEffects(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum HoldEffect holdEffectAtk, enum Move move)
{
    if (holdEffectAtk == HOLD_EFFECT_PROTECTIVE_PADS)
    {
        RecordItemEffectBattle(battlerAtk, HOLD_EFFECT_PROTECTIVE_PADS);
        return TRUE;
    }

    return !IsMoveMakingContact(battlerAtk, battlerDef, abilityAtk, holdEffectAtk, move);
}

bool32 IsMoveMakingContact(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum HoldEffect holdEffectAtk, enum Move move)
{
    if (!(MoveMakesContact(move) || (GetMoveEffect(move) == EFFECT_SHELL_SIDE_ARM
                                  && gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] == DAMAGE_CATEGORY_PHYSICAL)))
    {
        return FALSE;
    }
    else if (holdEffectAtk == HOLD_EFFECT_PUNCHING_GLOVE && IsPunchingMove(move))
    {
        RecordItemEffectBattle(battlerAtk, HOLD_EFFECT_PUNCHING_GLOVE);
        return FALSE;
    }
    else if (holdEffectAtk == HOLD_EFFECT_LEG_WEIGHTS && IsKickingMove(move))
    {
        RecordItemEffectBattle(battlerAtk, HOLD_EFFECT_LEG_WEIGHTS);
        return FALSE;
    }
    else if (abilityAtk == ABILITY_LONG_REACH)
    {
        RecordAbilityBattle(battlerAtk, ABILITY_LONG_REACH);
        return FALSE;
    }
    return TRUE;
}

static inline bool32 IsSideProtected(enum BattlerId battler, enum ProtectMethod method)
{
    return gProtectStructs[battler].protected == method
        || gProtectStructs[BATTLE_PARTNER(battler)].protected == method;
}

bool32 IsBattlerProtected(struct BattleContext *ctx)
{
    if (gProtectStructs[ctx->battlerDef].protected == PROTECT_NONE
     && gProtectStructs[BATTLE_PARTNER(ctx->battlerDef)].protected == PROTECT_NONE)
        return FALSE;

    if (GetMoveEffect(ctx->move) == EFFECT_CURSE && !IS_BATTLER_OF_TYPE(ctx->battlerAtk, TYPE_GHOST))
        return FALSE;

    if (gProtectStructs[ctx->battlerDef].protected != PROTECT_MAX_GUARD && !MoveIgnoresProtect(ctx->move))
    {
        if (IsZMove(ctx->move) || IsMaxMove(ctx->move))
            return FALSE; // Z-Moves and Max Moves bypass protection (except Max Guard).
        if (ctx->abilityAtk == ABILITY_UNSEEN_FIST
         && IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ctx->abilityAtk, ctx->holdEffectAtk, ctx->move))
            return FALSE;
    }

    if (GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move) == TARGET_ALL_BATTLERS)
        return FALSE;

    bool32 isProtected = FALSE;

    if (IsSideProtected(ctx->battlerDef, PROTECT_CRAFTY_SHIELD)
     && IsBattleMoveStatus(ctx->move)
     && GetMoveEffect(ctx->move) != EFFECT_COACHING)
        isProtected = TRUE;
    else if (MoveIgnoresProtect(ctx->move))
        isProtected = FALSE;
    else if (IsSideProtected(ctx->battlerDef, PROTECT_WIDE_GUARD) && IsSpreadMove(GetBattlerMoveTargetType(ctx->battlerAtk, ctx->move)))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_NORMAL)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_SPIKY_SHIELD)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_MAX_GUARD)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_BANEFUL_BUNKER)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_BURNING_BULWARK)
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_OBSTRUCT && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_SILK_TRAP && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_KINGS_SHIELD && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (IsSideProtected(ctx->battlerDef, PROTECT_QUICK_GUARD) && GetChosenMovePriority(ctx->battlerAtk, GetBattlerAbility(ctx->battlerAtk)) > 0)
        isProtected = TRUE;
    else if (IsSideProtected(ctx->battlerDef, PROTECT_MAT_BLOCK) && !IsBattleMoveStatus(ctx->move))
        isProtected = TRUE;
    else if (gProtectStructs[ctx->battlerDef].protected == PROTECT_FENCE)
        isProtected = TRUE;
    else
        isProtected = FALSE;

    return isProtected;
}

u32 GetProtectType(enum ProtectMethod method)
{
    switch (method)
    {
    case PROTECT_NONE:
        return PROTECT_TYPE_NONE;
    case PROTECT_NORMAL:
    case PROTECT_SHIELD_BASH: //unsure but putting here
    case PROTECT_SPIKY_SHIELD:
    case PROTECT_KINGS_SHIELD:
    case PROTECT_BANEFUL_BUNKER:
    case PROTECT_BURNING_BULWARK:
    case PROTECT_OBSTRUCT:
    case PROTECT_FENCE:
    case PROTECT_SILK_TRAP:
    case PROTECT_MAX_GUARD:
        return PROTECT_TYPE_SINGLE;
    case PROTECT_WIDE_GUARD:
    case PROTECT_QUICK_GUARD:
    case PROTECT_CRAFTY_SHIELD:
    case PROTECT_MAT_BLOCK:
        return PROTECT_TYPE_SIDE;
    }

    return FALSE;
}

enum InverseBattleCheck
{
    INVERSE_BATTLE,
    NOT_INVERSE_BATTLE
};

enum IronBallCheck
{
    CHECK_IRON_BALL,
    IGNORE_IRON_BALL
};

//can use this for mon or battler
//for battler take gBattleMons[battlerId].species
bool8 IsFloatingSpecies(u16 species) 
{
    s32 i;

    if (gSpeciesInfo[species].floating)
        return TRUE;

    return FALSE;
}

//VSONIC not 100% but original was false for check negation
//so think ignore negation is correct
bool8 IsFlyingTypeBattlerUnableToFly(enum BattlerId battler)
{
    u16 species = gBattleMons[battler].species;

    if (gFieldStatuses & STATUS_FIELD_GRAVITY
    || (GetBattlerHoldEffectIgnoreNegation(battler) == HOLD_EFFECT_IRON_BALL))
        return TRUE;

   
    if (IsFloatingSpecies(species))
        return FALSE;
    else
        return TRUE;

}

//simplify rather than include affinty check
//assume flying just include things necessary
//to not be grounded
//hopefully accounts for loss of item as well 
//well those are prob both move end affects
//so may need to shift move end affect so
//item removal happens before MOVE_END_GROUND_TARGET
//vsonic important
bool8 CanFlyingTypeRecoverFromSmackDown(enum BattlerId battler)
{
    u16 species = gBattleMons[battler].species;

    if (IsFloatingSpecies(species))
        return TRUE;
    else if (GetBattlerHoldEffect(battler) == HOLD_EFFECT_FLOAT_STONE)
            return TRUE;

    return FALSE;

}

#define GROUNDED_FUNCTION

// Only called directly when calculating damage type effectiveness, and Iron Ball's type effectiveness mechanics
//with levitate removal wont be using abiilty argument
//this function doesn't have roost check cuz it has flying type check
//and default effect makes lose flying type defaulting it to grouded status - my version doesn't
static bool32 IsBattlerGroundedInverseCheck(enum BattlerId battler, enum Ability ability, enum Ability atkAbility, enum HoldEffect holdEffect, enum InverseBattleCheck checkInverse, bool32 isAnticipation)
{
    /*if (holdEffect == HOLD_EFFECT_IRON_BALL)
        return TRUE;
    if (gFieldStatuses & STATUS_FIELD_GRAVITY && isAnticipation == FALSE)
        return TRUE;
    if (B_ROOTED_GROUNDING >= GEN_4 && gBattleMons[battler].volatiles.rooted)
        return TRUE;
    if (gBattleMons[battler].volatiles.smackDown)
        return TRUE;
    if (gBattleMons[battler].volatiles.telekinesis)
        return FALSE;
    if (gBattleMons[battler].volatiles.magnetRise)
        return FALSE;
    if (holdEffect == HOLD_EFFECT_AIR_BALLOON)
        return FALSE;

    if (IS_BATTLER_OF_TYPE(battler, TYPE_FLYING) && (checkInverse != INVERSE_BATTLE || !FlagGet(B_FLAG_INVERSE_BATTLE)))
        return FALSE;
    return TRUE;*/
    //need figure how to do inverse stuff interact
    //w my floating mechancic changes as defaults to neutral
    //on chart then gets set immune

    u16 species = gBattleMons[battler].species;
    bool8 grounded = TRUE; //changed so goes through all checks  //not using else, so need to make it default TRUE

    //order is bad, need setup so if I change it from not grounded, it doesn't get cleared -fixed orderr
    //setup is different from emerald, that uses return to immediately  stop if found true case
    //but I have cases that don't get removed/are always true, so I need to filter

    if (IsFloatingSpecies(species))//used if as breakline, as else if only reads if everything above it is false
        grounded = FALSE; //nice new version of floating setup greatly cleanns up this function

    else if ((DoesBattlerGetTypeBasedAffinity(atkAbility, battler, ability, TYPE_FLYING, FALSE)
    || DoesBattlerGetTypeBasedAffinity(atkAbility, battler, ability, TYPE_WIND, FALSE))
     && holdEffect == HOLD_EFFECT_FLOAT_STONE)
        grounded = FALSE;
    //for setting the sript to play think can do it in atk49 moveend
    //check battlescript.moveeffect if sleep or paralysis
    //can do a before and after thing like how emergency exit does before after hp checks
    //put check in attack canceler if mon is not grounded
    //and then in move end check if becomes grounded and set script then
    //if can get that to work can consolidate effect
    //won't need do separate effects for each thing,

    //need put logic in status cure 
    //may just make a new ewram thing that can loop all battlers
    //at turn start from main, to check if they are grounded
    //turnstartgroundedcheck  just a true false assignment
    //then in endturn/moveend can do what I need to, to update
    //MOVE_END_GROUND_TARGET already handle that without new ewram thing
    //if (gBattleMons[battler].status1 & STATUS1_PARALYSIS) 
    //    grounded = TRUE; //may remove from paralysis think anime still fly plus too strong for effect
    
    if (gBattleMons[battler].status1 & STATUS1_INCAPACITATED) 
        grounded = TRUE;

    //if (gBattleMons[battler].volatiles.frozenTurns != 0) //frozen solid since adding frostbite can explicilty set as freeze
    //    grounded = TRUE;
    //added status excemptions to replace lose of synergy with 
    //ability removal/swap effects/moldbreaker likes
    //needed some form of accessible effect removal besides just
    //requiring speific moves - review can't remember if moldbreaker still allows
    //getting passed floating mechanic as if tied to ability
    //since I have it affecting affinities vsonic
    
    //have roost timer now don't imagine would need this?
    //if (gBattleResources->flags->flags[battler] & RESOURCE_FLAG_ROOST)
    //    grounded = TRUE; //hope this set up right/works
    //according to Mcgriffin needed make flying & roost flag true statement
    //as else at bottom just means not flyign or has roost flag, TRUE

    //looking at these realize I prob have in wrong order
    //smack down trench run and roost shoulnt stop magnet rise telekinesis etc.
    //not setup fully yet vsonic -//hmm w ground flying change this is also more balanced now vsonic
    if (gBattleMons[battler].volatiles.trenchRunTimer) //change name, using for trench run
        grounded = TRUE;
    if (gBattleMons[battler].volatiles.roostTimer) //
        grounded = TRUE;
    

    if ((gBattleMons[battler].volatiles.telekinesis))
        grounded = FALSE;
    if ((gBattleMons[battler].volatiles.magnetRise))
        grounded = FALSE;
    
    if ((holdEffect == HOLD_EFFECT_AIR_BALLOON))
        grounded = FALSE;

    //still don't see point of anticipation check
    //ancticipation is only able to read it in gen 4 for type calc vsonic
    if (gFieldStatuses & STATUS_FIELD_GRAVITY && isAnticipation == FALSE)
        grounded = TRUE;
    if (gBattleMons[battler].volatiles.rooted)
        grounded = TRUE;
    //oh might be wrong in origial smack down superscedes magnet rise
    //and telekinesis apparently
    if (gBattleMons[battler].volatiles.smackDown)
        grounded = TRUE;
    
    
    if (holdEffect == HOLD_EFFECT_IRON_BALL)
        grounded = TRUE;   
    
    //doesn't matter much other than smacking down targets
    //in mid flight still think may not need
    //as triggering on air status already clears smackdown
    //if ((gBattleMons[battler].volatiles.semiInvulnerable == STATE_ON_AIR))
    //    grounded = FALSE;

    //while makes sense they never "fixed" this so I guess
    //that's an intentional oversight for fun/unique options
    //but then again is better for ground type to work,
    //and not working flies in face of water version of effect
    //that works as expected this doesn't
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_UNDERGROUND)
        grounded = TRUE;
    
    return grounded;
}

bool32 IsBattlerGrounded(enum BattlerId battler, enum Ability ability, enum Ability atkAbility, enum HoldEffect holdEffect)
{
    return IsBattlerGroundedInverseCheck(battler, ability, atkAbility, holdEffect, NOT_INVERSE_BATTLE, FALSE);
}

bool32 IsBattlerGrounded_IgnoreException(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect)
{
    return IsBattlerGroundedInverseCheck(battler, ability, ABILITY_NONE, holdEffect, NOT_INVERSE_BATTLE, FALSE);
}

u32 GetMoveSlot(u16 *moves, enum Move move)
{
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == move)
            break;
    }
    return i;
}

u32 GetBattlerWeight(enum BattlerId battler)
{
    u32 i;
    u32 weight = GetPokedexHeightWeight(SpeciesToNationalPokedexNum(gBattleMons[battler].species), 1);    //weight measured in kilo grams 69 = 6.9 kg -bulbasaur
    enum Ability ability = GetBattlerAbility(battler);
    enum HoldEffect holdEffect = GetBattlerHoldEffect(battler);

    if (ability == ABILITY_HEAVY_METAL)
        weight *= 2;
    else if (ability == ABILITY_LIGHT_METAL
        || ability == ABILITY_LIQUID_METAL)
        weight /= 2;

    if (holdEffect == HOLD_EFFECT_FLOAT_STONE)
        weight /= 2;

    if (holdEffect == HOLD_EFFECT_IRON_BALL)//lower cuz stacks
        weight = (weight * 150) / 100;

    for (i = 0; i < gBattleMons[battler].volatiles.autotomizeCount; i++)
    {
        if (weight > 1000)
        {
            weight -= 1000;
        }
        else if (weight <= 1000)
        {
            weight = 1;
            break;
        }
    }

    if (weight == 0)
        weight = 1;

    return weight;
}

u32 CountBattlerStatIncreases(enum BattlerId battler, bool32 countEvasionAcc)
{
    enum Stat i;
    u32 count = 0;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if ((i == STAT_ACC || i == STAT_EVASION) && !countEvasionAcc)
            continue;
        if (gBattleMons[battler].statStages[i] > DEFAULT_STAT_STAGE) // Stat is increased.
            count += gBattleMons[battler].statStages[i] - DEFAULT_STAT_STAGE;
    }

    return count;
}

bool32 BattlerHasCopyableChanges(enum BattlerId battler)
{
    u32 i;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battler].statStages[i] != DEFAULT_STAT_STAGE)
            return TRUE;
    }

    if (gBattleMons[battler].volatiles.focusEnergy
     || gBattleMons[battler].volatiles.dragonCheer)
        return TRUE;

    return FALSE;
}

u32 GetMoveTargetCount(struct BattleContext *ctx)
{
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;

    switch (GetBattlerMoveTargetType(battlerAtk, move))
    {
    case TARGET_BOTH:
        return !(gAbsentBattlerFlags & (1u << battlerDef))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerDef)));
    case TARGET_FOES_AND_ALLY:
        return !(gAbsentBattlerFlags & (1u << battlerDef))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerDef)))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerAtk)));
    case TARGET_OPPONENTS_FIELD:
        return 1;
    case TARGET_DEPENDS:
    case TARGET_SELECTED:
    case TARGET_RANDOM:
    case TARGET_OPPONENT:
        return IsBattlerAlive(battlerDef);
    case TARGET_USER:
        return IsBattlerAlive(battlerAtk);
    default:
        return 0;
    }
}

static const u8 sFlailHpScaleToPowerTable[] =
{
    1, 200,
    4, 150,
    9, 100,
    16, 80,
    32, 40,
    48, 20
};

// format: min. weight (hectograms), base power
static const u16 sWeightToDamageTable[] =
{
    50, 40,
    200, 60,    //geodude is here
    500, 75,
    1000, 85,  //graveler is here
    2400, 100,  //onix is here  //snorlax is double this
    10000, 120,
    0xFFFF, 0xFFFF
};

static const u8 sSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 sHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
static const u8 sTrumpCardPowerTable[] = {200, 80, 60, 50, 40};

static u16 WeightBoostedDamageFormula(enum BattlerId battlerTarget)
{
    s32 i;
    u8 damage;

    for (i = 0; sWeightToDamageTable[i] != 0xFFFF; i += 2) //go to next row, if not 0xffff
    {
        if (sWeightToDamageTable[i] > GetBattlerWeight(battlerTarget)) //using this function over base species weight allows automize, float stone, heavy and light metal to have affect on dmg formula
            break;
    }
    if (sWeightToDamageTable[i] != 0xFFFF) //will always break before reach ffff, max dmg 120
        damage = sWeightToDamageTable[i + 1];

    return damage;
}

const struct TypePower gNaturalGiftTable[] =
{
    [ITEM_TO_BERRY(ITEM_CHERI_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_CHESTO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_PECHA_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RAWST_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_ASPEAR_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_LEPPA_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_ORAN_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_PERSIM_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_LUM_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_SITRUS_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_FIGY_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_WIKI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_MAGO_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_AGUAV_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_IAPAPA_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_RAZZ_BERRY)] = {TYPE_STEEL, 80},
    [ITEM_TO_BERRY(ITEM_OCCA_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_PASSHO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_WACAN_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RINDO_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_YACHE_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_CHOPLE_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_KEBIA_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_SHUCA_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_COBA_BERRY)] = {TYPE_WIND, 80},
    [ITEM_TO_BERRY(ITEM_PAYAPA_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_TANGA_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_CHARTI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_KASIB_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_HABAN_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_COLBUR_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_BABIRI_BERRY)] = {TYPE_STEEL, 80},
    [ITEM_TO_BERRY(ITEM_CHILAN_BERRY)] = {TYPE_NORMAL, 80},
    [ITEM_TO_BERRY(ITEM_ROSELI_BERRY)] = {TYPE_FAIRY, 80},
    [ITEM_TO_BERRY(ITEM_BLUK_BERRY)] = {TYPE_FIRE, 90},
    [ITEM_TO_BERRY(ITEM_NANAB_BERRY)] = {TYPE_WATER, 90},
    [ITEM_TO_BERRY(ITEM_WEPEAR_BERRY)] = {TYPE_ELECTRIC, 90},
    [ITEM_TO_BERRY(ITEM_PINAP_BERRY)] = {TYPE_GRASS, 90},
    [ITEM_TO_BERRY(ITEM_POMEG_BERRY)] = {TYPE_ICE, 90},
    [ITEM_TO_BERRY(ITEM_KELPSY_BERRY)] = {TYPE_FIGHTING, 90},
    [ITEM_TO_BERRY(ITEM_QUALOT_BERRY)] = {TYPE_POISON, 90},
    [ITEM_TO_BERRY(ITEM_HONDEW_BERRY)] = {TYPE_GROUND, 90},
    [ITEM_TO_BERRY(ITEM_GREPA_BERRY)] = {TYPE_FLYING, 90},
    [ITEM_TO_BERRY(ITEM_TAMATO_BERRY)] = {TYPE_PSYCHIC, 90},
    [ITEM_TO_BERRY(ITEM_CORNN_BERRY)] = {TYPE_BUG, 90},
    [ITEM_TO_BERRY(ITEM_MAGOST_BERRY)] = {TYPE_ROCK, 90},
    [ITEM_TO_BERRY(ITEM_RABUTA_BERRY)] = {TYPE_GHOST, 90},
    [ITEM_TO_BERRY(ITEM_NOMEL_BERRY)] = {TYPE_DRAGON, 90},
    [ITEM_TO_BERRY(ITEM_SPELON_BERRY)] = {TYPE_DARK, 90},
    [ITEM_TO_BERRY(ITEM_PAMTRE_BERRY)] = {TYPE_STEEL, 90},
    [ITEM_TO_BERRY(ITEM_WATMEL_BERRY)] = {TYPE_FIRE, 100},
    [ITEM_TO_BERRY(ITEM_DURIN_BERRY)] = {TYPE_WATER, 100},
    [ITEM_TO_BERRY(ITEM_BELUE_BERRY)] = {TYPE_ELECTRIC, 100},
    [ITEM_TO_BERRY(ITEM_LIECHI_BERRY)] = {TYPE_GRASS, 100},
    [ITEM_TO_BERRY(ITEM_GANLON_BERRY)] = {TYPE_ICE, 100},
    [ITEM_TO_BERRY(ITEM_SALAC_BERRY)] = {TYPE_FIGHTING, 100},
    [ITEM_TO_BERRY(ITEM_PETAYA_BERRY)] = {TYPE_POISON, 100},
    [ITEM_TO_BERRY(ITEM_APICOT_BERRY)] = {TYPE_GROUND, 100},
    [ITEM_TO_BERRY(ITEM_LANSAT_BERRY)] = {TYPE_FLYING, 100},
    [ITEM_TO_BERRY(ITEM_STARF_BERRY)] = {TYPE_PSYCHIC, 100},
    [ITEM_TO_BERRY(ITEM_ENIGMA_BERRY)] = {TYPE_BUG, 100},
    [ITEM_TO_BERRY(ITEM_MICLE_BERRY)] = {TYPE_ROCK, 100},
    [ITEM_TO_BERRY(ITEM_CUSTAP_BERRY)] = {TYPE_GHOST, 100},
    [ITEM_TO_BERRY(ITEM_JABOCA_BERRY)] = {TYPE_DRAGON, 100},
    [ITEM_TO_BERRY(ITEM_ROWAP_BERRY)] = {TYPE_DARK, 100},
    [ITEM_TO_BERRY(ITEM_KEE_BERRY)] = {TYPE_FAIRY, 100},
    [ITEM_TO_BERRY(ITEM_MARANGA_BERRY)] = {TYPE_DARK, 100},
};

static inline u32 CalcRolloutBasePower(enum BattlerId battlerAtk, u32 basePower)
{
    u32 i;
    for (i = 0; i < gBattleMons[battlerAtk].volatiles.rolloutTimer; i++)
        basePower *= 2;
    if (gBattleMons[battlerAtk].volatiles.defenseCurl)
        basePower *= 2;
    return basePower;
}


static inline u32 CalcFuryCutterBasePower(enum BattlerId battlerAtk, u32 basePower)
{
    for (u32 i = 0; i < gBattleMons[battlerAtk].volatiles.furyCutterCounter; i++)
        basePower += 10;
    return basePower;
}

static inline u32 CalcTerrainBoostedPower(struct BattleContext *ctx, u32 basePower)
{
    bool32 isTerrainAffected = FALSE;

    if (GetMoveTerrainBoost_GroundCheck(ctx->move) == GROUND_CHECK_USER)
        isTerrainAffected = IsBattlerTerrainAffected(ctx->battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk, ctx->fieldStatuses, GetMoveTerrainBoost_Terrain(ctx->move));
    else if (GetMoveTerrainBoost_GroundCheck(ctx->move) == GROUND_CHECK_TARGET)
        isTerrainAffected = IsBattlerTerrainAffected(ctx->battlerDef, ctx->abilityDef, ctx->holdEffectDef, ctx->fieldStatuses, GetMoveTerrainBoost_Terrain(ctx->move));
    else if (ctx->fieldStatuses & GetMoveTerrainBoost_Terrain(ctx->move)) // no ground check (Psyblade)
        isTerrainAffected = TRUE;

    if (isTerrainAffected)
        basePower = uq4_12_multiply(basePower, PercentToUQ4_12AddOne(GetMoveTerrainBoost_Percent(ctx->move)));

    return basePower;
}

//vsonic //unsure what to make of this, as added extra effects
//mud boosts ground rock sp def
//water boosts grass speed
//ok this is just for the dmg halving effect
//may still rename later as should only
//relate to dmg cut for move type
static inline u32 IsMudSportAffected(enum Type moveType, enum BattlerId battlerDef)
{
    if (moveType != TYPE_ELECTRIC)
        return FALSE;

    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MUDSPORT)
        return TRUE;


    return FALSE;
}

static inline u32 IsWaterSportAffected(enum Type moveType, enum BattlerId battlerDef)
{
    if (moveType != TYPE_FIRE)
        return FALSE;

    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_WATERSPORT)
        return TRUE;


    return FALSE;
}

static inline u32 CalcMoveBasePower(struct BattleContext *ctx)
{
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;

    u32 i;
    u32 basePower = GetMovePower(move);
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    u32 weight, hpFraction, speed;

    if (GetActiveGimmick(battlerAtk) == GIMMICK_Z_MOVE)
        return GetZMovePower(gCurrentMove);

    if (GetActiveGimmick(battlerAtk) == GIMMICK_DYNAMAX)
        return GetMaxMovePower(move);

    switch (moveEffect)
    {
    case EFFECT_PLEDGE:
        if (gBattleStruct->pledgeMove)
            basePower = 150;
        break;
    case EFFECT_FLING:
        basePower = GetFlingPowerFromItemId(gBattleMons[battlerAtk].item);
        break;
    case EFFECT_POWER_BASED_ON_USER_HP:
        basePower = gBattleMons[battlerAtk].hp * basePower / gBattleMons[battlerAtk].maxHP;
        break;
    case EFFECT_FLAIL:
        hpFraction = GetScaledHPFraction(gBattleMons[battlerAtk].hp, gBattleMons[battlerAtk].maxHP, 48);
        for (i = 0; i < sizeof(sFlailHpScaleToPowerTable); i += 2)
        {
            if (hpFraction <= sFlailHpScaleToPowerTable[i])
                break;
        }
        basePower = sFlailHpScaleToPowerTable[i + 1];
        break;
    case EFFECT_RETURN:
        basePower = 10 * (gBattleMons[battlerAtk].friendship) / 25;
        break;
    case EFFECT_FRUSTRATION:
        basePower = 10 * (MAX_FRIENDSHIP - gBattleMons[battlerAtk].friendship) / 25;
        break;//reworking will use frustrationCounter
    case EFFECT_FURY_CUTTER:
        basePower = CalcFuryCutterBasePower(battlerAtk, basePower);
        break;
    case EFFECT_ROLLOUT:
        basePower = CalcRolloutBasePower(battlerAtk, basePower);
        break;
    case EFFECT_MAGNITUDE:
        basePower = gBattleStruct->magnitudeBasePower;
        break;
    case EFFECT_PRESENT:
        basePower = gBattleStruct->presentBasePower;
        break;//vsonic
    case EFFECT_TRIPLE_KICK:
        basePower *= 1 + GetMoveStrikeCount(move) - gMultiHitCounter;
        break;
    case EFFECT_SPIT_UP:
        basePower = 100 * gBattleMons[battlerAtk].volatiles.stockpileCounter;
        break;
    case EFFECT_REVENGE:
        if (gProtectStructs[battlerAtk].revengeDoubled & 1u << battlerDef)
            basePower *= 2;
        break;
    case EFFECT_WEATHER_BALL:
        if (ctx->weather & WEATHER_ANY)
            basePower *= 2;
        break;
    /*case EFFECT_PURSUIT:
        if (gBattleStruct->battlerState[battlerDef].pursuitTarget)
            basePower *= 2;
        break;*/
    case EFFECT_NATURAL_GIFT:
        basePower = gNaturalGiftTable[ITEM_TO_BERRY(gBattleMons[battlerAtk].item)].power;
        break;
    case EFFECT_DOUBLE_POWER_ON_ARG_STATUS:
        // Comatose targets treated as if asleep
        if ((gBattleMons[battlerDef].status1 | (STATUS1_SLEEP * (ctx->abilityDef == ABILITY_COMATOSE))) & GetMoveEffectArg_Status(move)
         && !((GetMoveAdditionalEffectById(move, 0)->moveEffect == MOVE_EFFECT_REMOVE_STATUS) && DoesSubstituteBlockMove(battlerAtk, battlerDef, move)))
            basePower *= 2;
        break;
    case EFFECT_POWER_BASED_ON_TARGET_HP:
        basePower = gBattleMons[battlerDef].hp * GetMoveDamagePercentage(move) / gBattleMons[battlerDef].maxHP;
        basePower = max(basePower, 40);
        break;
    case EFFECT_ASSURANCE:
        if (gProtectStructs[battlerDef].assuranceDoubled)
            basePower *= 2;
        break;
    /*case EFFECT_TRUMP_CARD:
        i = GetMoveSlot(gBattleMons[battlerAtk].moves, move);
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[battlerAtk].pp[i] >= ARRAY_COUNT(sTrumpCardPowerTable))
                basePower = sTrumpCardPowerTable[ARRAY_COUNT(sTrumpCardPowerTable) - 1];
            else
                basePower = sTrumpCardPowerTable[gBattleMons[battlerAtk].pp[i]];
        }
        break;*///reworking trump card oh made into status so can remove this vsonic note to self make 90 acc not sure hit
    case EFFECT_ACROBATICS:
        if (gBattleMons[battlerAtk].item == ITEM_NONE
            // Edge case, because removal of items happens after damage calculation.
            || (gSpecialStatuses[battlerAtk].gemBoost && GetBattlerHoldEffect(battlerAtk) == HOLD_EFFECT_GEMS))
            basePower *= 2;
        break;
    case EFFECT_LOW_KICK:
        weight = GetBattlerWeight(battlerDef);
        for (i = 0; sWeightToDamageTable[i] != 0xFFFF; i += 2)
        {
            if (sWeightToDamageTable[i] > weight)
                break;
        }
        if (sWeightToDamageTable[i] != 0xFFFF)
            basePower = sWeightToDamageTable[i + 1];
        else
            basePower = 120;
        break;
    case EFFECT_HEAT_CRASH:
        weight = GetBattlerWeight(battlerAtk) / GetBattlerWeight(battlerDef);
        if (weight >= ARRAY_COUNT(sHeatCrashPowerTable))
            basePower = sHeatCrashPowerTable[ARRAY_COUNT(sHeatCrashPowerTable) - 1];
        else
            basePower = sHeatCrashPowerTable[weight];
        break;
    case EFFECT_PUNISHMENT:
        basePower = 60 + (CountBattlerStatIncreases(battlerDef, FALSE) * 20);
        if (basePower > 200)
            basePower = 200;
        break;
    case EFFECT_STORED_POWER:
        basePower += (CountBattlerStatIncreases(battlerAtk, TRUE) * 20);
        break;
    case EFFECT_ELECTRO_BALL:

        basePower = ((60 * GetBattlerTotalSpeedStat(battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk)) / GetBattlerTotalSpeedStat(battlerDef, ctx->abilityDef, ctx->holdEffectDef)) + 1;
        if (basePower > 150)
            basePower = 150;
        if (basePower < 40)
            basePower = 40;
        break; //reworked effect
    case EFFECT_GYRO_BALL:
        {
            u32 attackerSpeed = GetBattlerTotalSpeedStat(battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk);
            if (attackerSpeed == 0)
            {
                basePower = 1;
            }
            else
            {
                basePower = ((25 * GetBattlerTotalSpeedStat(battlerDef, ctx->abilityDef, ctx->holdEffectDef)) / attackerSpeed) + 1;
                if (basePower > 150)
                    basePower = 150;
            }
            break;
        }
    case EFFECT_ECHOED_VOICE:
        // gBattleStruct->echoedVoiceCounter incremented in EndTurnVarious called by DoEndTurnEffects
        if (gBattleStruct->echoedVoiceCounter != 0)
        {
            basePower += (basePower * gBattleStruct->echoedVoiceCounter);
            if (basePower > 200)
                basePower = 200;
        }
        break;
    case EFFECT_PAYBACK:
        if (HasBattlerActedThisTurn(battlerDef)
            && (B_PAYBACK_SWITCH_BOOST < GEN_5 || gBattleStruct->battlerState[battlerDef].isFirstTurn != 2))
            basePower *= 2;
        break;
    case EFFECT_BOLT_BEAK:
        if (!HasBattlerActedThisTurn(battlerDef)
            || gBattleStruct->battlerState[battlerDef].isFirstTurn == 2)
            basePower *= 2;
        break;
    case EFFECT_FUSION_COMBO:
        if (move == gLastUsedMove)
            break;
        // fallthrough
    case EFFECT_ROUND:
        // don't double power due to previous turn's Round/Fusion move
        if (gCurrentTurnActionNumber != 0
         && gActionsByTurnOrder[gCurrentTurnActionNumber - 1] == B_ACTION_USE_MOVE
         && GetMoveEffect(gLastUsedMove) == moveEffect)
            basePower *= 2;
        break;
    case EFFECT_LASH_OUT:
        if (gProtectStructs[battlerAtk].lashOutAffected)
            basePower *= 2;
        break;
        //seems replaces misty explosion effect
        //I'm reworking that as well but still need mist boost
        //consider put on move flag instead of effect
        //and potentially move to power modifier after basepower
        //so not hard restricted to move effects vsonic important
    case EFFECT_TERRAIN_BOOST:
        basePower = CalcTerrainBoostedPower(ctx, basePower);
        break;
    case EFFECT_BOOST_PWR_BASED_WEIGHT: //replaces EFFECT_DYNAMAX_DOUBLE_DMG
        {
            weight = GetBattlerWeight(battlerDef);

            //is just below onix
            if (weight >= 2000)
                basePower = (140 * basePower) / 100;
        }
    case EFFECT_HIDDEN_POWER:
    {
        s32 powerBits = ((gBattleMons[battlerAtk].hpIV & 2) >> 1)
                        | ((gBattleMons[battlerAtk].attackIV & 2) << 0)
                        | ((gBattleMons[battlerAtk].defenseIV & 2) << 1)
                        | ((gBattleMons[battlerAtk].speedIV & 2) << 2)
                        | ((gBattleMons[battlerAtk].spAttackIV & 2) << 3)
                        | ((gBattleMons[battlerAtk].spDefenseIV & 2) << 4);

        basePower = (35 * powerBits) / 63 + 45;
        break;//reworked custom hp power func
    }
    case EFFECT_GRAV_APPLE:
        if (ctx->fieldStatuses & STATUS_FIELD_GRAVITY)
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.5));
        break;
    case EFFECT_TERRAIN_PULSE:
        if (IsAnyTerrainAffected(battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk, ctx->fieldStatuses))
            basePower *= 2;
        break;
    case EFFECT_BEAT_UP:
        if (GetConfig(B_BEAT_UP) >= GEN_5)
            basePower = CalcBeatUpPower();
        break;
    case EFFECT_MAX_MOVE:
        basePower = GetMaxMovePower(GetBattlerChosenMove(battlerAtk));
        break;
    case EFFECT_RAGE_FIST:
        basePower += 50 * GetBattlerPartyState(battlerAtk)->timesGotHit;
        basePower = (basePower > 350) ? 350 : basePower;
        break;
    case EFFECT_FICKLE_BEAM:
        if (gBattleStruct->fickleBeamBoosted)
            basePower *= 2;
        break;
    case EFFECT_TERA_BLAST:
        if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA && GetBattlerTeraType(battlerAtk) == TYPE_STELLAR)
            basePower = 100;
        break;
    case EFFECT_LAST_RESPECTS:
        basePower += (basePower * min(100, GetBattlerSideFaintCounter(battlerAtk)));
        break;
    case EFFECT_SPECIES_POWER_OVERRIDE:
        if (gBattleMons[battlerAtk].species == GetMoveSpeciesPowerOverride_Species(ctx->move))
            basePower = GetMoveSpeciesPowerOverride_Power(ctx->move);
    default:
        break;
    }

    if (basePower == 0)
        basePower = 1;
    return basePower;
}

static inline u32 CalcMoveBasePowerAfterModifiers(struct BattleContext *ctx)
{
    u32 holdEffectParamAtk;
    u32 basePower = CalcMoveBasePower(ctx);
    bool32 FluorescenceActive = (ctx->abilityAtk == ABILITY_FLUORESCENCE);
    bool32 CloudNineOnSide = (DoesSideHaveAbility(ctx->battlerAtk, ABILITY_CLOUD_NINE));
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum Type moveType = ctx->moveType;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);

    uq4_12_t holdEffectModifier;
    uq4_12_t modifier = UQ_4_12(1.0);
    enum BattleSide atkSide = GetBattlerSide(battlerAtk);

    // move effect
    switch (moveEffect)
    {
    case EFFECT_FACADE://STATUS1_CAN_MOVE
        if (gBattleMons[battlerAtk].status1 & (STATUS1_BURN | STATUS1_PSN_ANY | STATUS1_PARALYSIS | STATUS1_FROSTBITE))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_TARGET_TYPE_DAMAGE:
        if (IS_BATTLER_OF_TYPE(battlerDef, GetTypeBasedBoostTypeCheck(move)))
            modifier = uq4_12_multiply(modifier, GetTypeBasedBoostMultiplier(move));
        break;
    case EFFECT_BRINE:
        if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP / 2))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_RETALIATE:
        if (gSideTimers[atkSide].retaliateTimer == 1)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;//vsonic look into this think reworked retaliate
    case EFFECT_SOLAR_BEAM:
        if (IsBattlerWeatherAffected(battlerAtk, WEATHER_LOW_LIGHT)
            && !FluorescenceActive
            && !CloudNineOnSide)
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        break;
    case EFFECT_STOMPING_TANTRUM:
        if (gBattleStruct->battlerState[battlerAtk].stompingTantrumTimer == 1)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_MAGNITUDE:
    case EFFECT_EARTHQUAKE:
        if (ctx->fieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && !IsSemiInvulnerable(battlerDef, CHECK_ALL))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        break;
    /*case EFFECT_KNOCK_OFF:
        if (B_KNOCK_OFF_DMG >= GEN_6
            && gBattleMons[battlerDef].item != ITEM_NONE
            && CanBattlerGetOrLoseItem(battlerDef, battlerAtk, gBattleMons[battlerDef].item))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;*/
    default:
        break;
    }

    // various effects
    for (u32 i = 0; i < gProtectStructs[battlerAtk].helpingHand; i++)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));

    if (gSpecialStatuses[battlerAtk].gemBoost)
        modifier = uq4_12_multiply(modifier, PercentToUQ4_12AddOne(gSpecialStatuses[battlerAtk].gemParam));
    //reworked this is now just the effect of charge state via ability
    //w lower cost no need to raise above 2x multiplier
    if (moveType == TYPE_ELECTRIC && gBattleMons[battlerAtk].volatiles.chargedUp > 0)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (GetMoveEffect(ctx->chosenMove) == EFFECT_ME_FIRST)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (IsGrassyTerrainAffected(battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk, ctx->fieldStatuses) && moveType == TYPE_GRASS)
        modifier = uq4_12_multiply(modifier, (B_TERRAIN_TYPE_BOOST >= GEN_8 ? UQ_4_12(1.3) : UQ_4_12(1.5)));
    if (IsMistyTerrainAffected(battlerDef, ctx->abilityDef, ctx->holdEffectDef, ctx->fieldStatuses) && moveType == TYPE_DRAGON)
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    if (IsElectricTerrainAffected(battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk, ctx->fieldStatuses) && moveType == TYPE_ELECTRIC)
        modifier = uq4_12_multiply(modifier, (B_TERRAIN_TYPE_BOOST >= GEN_8 ? UQ_4_12(1.3) : UQ_4_12(1.5)));
    if (IsPsychicTerrainAffected(battlerAtk, ctx->abilityAtk, ctx->holdEffectAtk, ctx->fieldStatuses) && moveType == TYPE_PSYCHIC)
        modifier = uq4_12_multiply(modifier, (B_TERRAIN_TYPE_BOOST >= GEN_8 ? UQ_4_12(1.3) : UQ_4_12(1.5)));
    if (IsMudSportAffected(ctx->moveType, battlerDef))
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    if (IsWaterSportAffected(ctx->moveType, battlerDef))
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));

    if (gBattleMons[battlerAtk].volatiles.dragonrage
    && moveType == TYPE_DRAGON)
    {
        //this too
        switch (gBattleMons[battlerAtk].volatiles.dragonrageCounter)
        {
            //annoying but best I could figure
            case 1:
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.1));
            break;
            case 2:
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
            break;
            case 3:
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            break;
            case 4:
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.4));
            break;
            case 5:
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
            break;
        }
    }

    // attacker's abilities
    switch (ctx->abilityAtk)
    {
    case ABILITY_TECHNICIAN:
        if (basePower <= 60)
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_FLARE_BOOST:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BURN && IsBattleMoveSpecial(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_TOXIC_BOOST:
        if (gBattleMons[battlerAtk].status1 & STATUS1_PSN_ANY && IsBattleMovePhysical(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_RECKLESS:
        if (MoveEffectDoesRecoil(moveEffect))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_IRON_FIST:
        if (IsPunchingMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_HUNGER_SWITCH:
        if (moveType == GetHungerSwitchType(gBattleMons[ctx->battlerAtk].species, ctx->abilityAtk))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_LETHAL_LEGS:
        if (IsKickingMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_SHEER_FORCE:
        if (MoveIsAffectedBySheerForce(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_SAND_FORCE:
        if ((moveType == TYPE_STEEL || moveType == TYPE_ROCK || moveType == TYPE_GROUND)
            && ctx->weather & WEATHER_SANDSTORM)
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_RIVALRY:
        if (AreBattlersOfSameGender(battlerAtk, battlerDef))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        else if (AreBattlersOfOppositeGender(battlerAtk, battlerDef))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
        break;
    case ABILITY_ANALYTIC:
        if (IsLastMonToMove(battlerAtk) && moveEffect != EFFECT_FUTURE_SIGHT)
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_TOUGH_CLAWS:
        if (IsMoveMakingContact(battlerAtk, battlerDef, ctx->abilityAtk, ctx->holdEffectAtk, ctx->move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_STRONG_JAW:
        if (IsBitingMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_MEGA_LAUNCHER:
        if (IsPulseMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_WATER_BUBBLE:
        if (moveType == TYPE_WATER)
           modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_STEELWORKER:
        if (moveType == TYPE_STEEL)
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PIXILATE:
        if (moveType == TYPE_FAIRY && gBattleStruct->battlerState[battlerAtk].ateBoost)
            modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_ATE_MULTIPLIER) >= GEN_7 ? 1.2 : 1.3));
        break;
    case ABILITY_GALVANIZE:
        if (moveType == TYPE_ELECTRIC && gBattleStruct->battlerState[battlerAtk].ateBoost)
            modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_ATE_MULTIPLIER) >= GEN_7 ? 1.2 : 1.3));
        break;
    case ABILITY_REFRIGERATE:
        if (moveType == TYPE_ICE && gBattleStruct->battlerState[battlerAtk].ateBoost)
            modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_ATE_MULTIPLIER) >= GEN_7 ? 1.2 : 1.3));
        break;
    case ABILITY_AERILATE:
        if (moveType == TYPE_FLYING && gBattleStruct->battlerState[battlerAtk].ateBoost)
            modifier = uq4_12_multiply(modifier, UQ_4_12(GetConfig(B_ATE_MULTIPLIER) >= GEN_7 ? 1.2 : 1.3));
        break;
    case ABILITY_NORMALIZE:
        if (moveType == TYPE_NORMAL && gBattleStruct->battlerState[battlerAtk].ateBoost && GetConfig(B_ATE_MULTIPLIER) >= GEN_7)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_PUNK_ROCK:
        if (IsSoundMove(move))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_STEELY_SPIRIT:
        if (moveType == TYPE_STEEL)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_SHARPNESS:
        if (IsSlicingMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_SUPREME_OVERLORD:
        modifier = uq4_12_multiply(modifier, GetSupremeOverlordModifier(battlerAtk));
        break;
    default:
        break;
    }

    // field abilities
    if ((IsAbilityOnField(ABILITY_DARK_AURA) && moveType == TYPE_DARK)
     || (IsAbilityOnField(ABILITY_FAIRY_AURA) && moveType == TYPE_FAIRY))
    {
        if (IsAbilityOnField(ABILITY_AURA_BREAK))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
        else
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.33));
    }

    // attacker partner's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        switch (GetBattlerAbility(BATTLE_PARTNER(battlerAtk)))
        {
        case ABILITY_BATTERY:
            if (IsBattleMoveSpecial(move)
            && !gBattleStruct->battlerState[BATTLE_PARTNER(battlerAtk)].commandingPartner)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            break;
        case ABILITY_POWER_SPOT:
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            break;
        case ABILITY_STEELY_SPIRIT:
            if (moveType == TYPE_STEEL)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
            break;
        default:
            break;
        }
    }

    // target's abilities
    switch (ctx->abilityDef)
    {
    case ABILITY_HEATPROOF:
    case ABILITY_WATER_BUBBLE:
        if (moveType == TYPE_FIRE)
        {
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
            if (ctx->updateFlags)
                RecordAbilityBattle(battlerDef, ctx->abilityDef);
        }
        break;
    case ABILITY_DRY_SKIN:
        if (moveType == TYPE_FIRE)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        break;
    case ABILITY_WATER_COMPACTION:
    if (moveType == TYPE_WATER)
        {
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
        }
        break;
    default:
        break;
    }

    holdEffectParamAtk = GetBattlerHoldEffectParam(battlerAtk);
    if (holdEffectParamAtk > 100)
        holdEffectParamAtk = 100;

    holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(holdEffectParamAtk));

    // attacker's hold effect
    switch (ctx->holdEffectAtk)
    {
    /*case HOLD_EFFECT_MUSCLE_BAND:
        if (IsBattleMovePhysical(move))
            modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12_Floored(holdEffectParamAtk)));
        break;
    case HOLD_EFFECT_WISE_GLASSES:
        if (IsBattleMoveSpecial(move))
            modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12_Floored(holdEffectParamAtk)));
        break;*/
    case HOLD_EFFECT_LUSTROUS_ORB:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_PALKIA && (moveType == TYPE_WATER || moveType == TYPE_DRAGON))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_ADAMANT_ORB:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_DIALGA && (moveType == TYPE_STEEL || moveType == TYPE_DRAGON))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_GRISEOUS_ORB:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_GIRATINA && (moveType == TYPE_GHOST || moveType == TYPE_DRAGON))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_SOUL_DEW:
        if ((gBattleMons[battlerAtk].species == SPECIES_LATIAS || gBattleMons[battlerAtk].species == SPECIES_LATIOS)
            && ((B_SOUL_DEW_BOOST >= GEN_7 && (moveType == TYPE_PSYCHIC || moveType == TYPE_DRAGON))
             || (B_SOUL_DEW_BOOST < GEN_7 && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER) && IsBattleMoveSpecial(move))))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_TYPE_POWER:
    case HOLD_EFFECT_PLATE:
        if (moveType == GetItemSecondaryId(gBattleMons[battlerAtk].item))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_PUNCHING_GLOVE:
        if (IsPunchingMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.15));
        break;
    case HOLD_EFFECT_LEG_WEIGHTS:
        if (IsKickingMove(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.15));
        break;
    case HOLD_EFFECT_OGERPON_MASK:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_OGERPON)
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    default:
        break;
    }

    // Terastallization boosts weak, non-priority, non-multi hit moves after modifiers to 60 BP.
    if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA
        && (moveType == GetBattlerTeraType(battlerAtk)
        || (GetBattlerTeraType(battlerAtk) == TYPE_STELLAR && IsTypeStellarBoosted(battlerAtk, moveType)))
        && uq4_12_multiply_by_int_half_down(modifier, basePower) < 60
        && GetMovePower(move) > 1
        && !IsMultiHitMove(move)
        && moveEffect != EFFECT_POWER_BASED_ON_USER_HP
        && moveEffect != EFFECT_POWER_BASED_ON_TARGET_HP
        && GetMovePriority(move) == 0)
    {
        return 60;
    }

    return uq4_12_multiply_by_int_half_down(modifier, basePower);
}

static bool32 IsRuinStatusActive(u32 fieldEffect)
{
    bool32 isNeutralizingGasOnField = IsNeutralizingGasOnField();
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        // Mold Breaker doesn't ignore Ruin field status but Gastro Acid and Neutralizing Gas do
        if (gBattleMons[battler].volatiles.gastroAcid)
            continue;
        if (GetBattlerHoldEffectIgnoreAbility(battler) != HOLD_EFFECT_ABILITY_SHIELD
         && isNeutralizingGasOnField
         && gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS)
            continue;

        if (GetBattlerVolatile(battler, fieldEffect))
            return TRUE;
    }

    return FALSE;
}

static inline uq4_12_t ApplyOffensiveBadgeBoost(uq4_12_t modifier, enum BattlerId battler, enum Move move)
{
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_ATTACK, battler) && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_SPATK, battler) && IsBattleMoveSpecial(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    return modifier;
}

static inline uq4_12_t ApplyDefensiveBadgeBoost(uq4_12_t modifier, enum BattlerId battler, enum Move move)
{
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_DEFENSE, battler) && IsBattleMovePhysical(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    if (ShouldGetStatBadgeBoost(B_FLAG_BADGE_BOOST_SPDEF, battler) && IsBattleMoveSpecial(move))
        modifier = uq4_12_multiply_half_down(modifier, GetBadgeBoostModifier());
    return modifier;
}

static inline u32 CalcAttackStat(struct BattleContext *ctx)
{
    u8 atkStage;
    u32 atkStat;
    uq4_12_t modifier;
    u16 atkBaseSpeciesId;
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum Type moveType = ctx->moveType;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    bool32 FogNegates = IsFogOnField();

    atkBaseSpeciesId = GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species);

    if (moveEffect == EFFECT_FOUL_PLAY)
    {
        if (IsBattleMovePhysical(move))
        {
            atkStat = gBattleMons[battlerDef].attack;
            atkStage = gBattleMons[battlerDef].statStages[STAT_ATK];
        }
        else
        {
            atkStat = gBattleMons[battlerDef].spAttack;
            atkStage = gBattleMons[battlerDef].statStages[STAT_SPATK];
        }
    }
    else if (moveEffect == EFFECT_BODY_PRESS)
    {
        if (IsBattleMovePhysical(move))
        {
            atkStat = gBattleMons[battlerAtk].defense;
            // Edge case: Body Press used during Wonder Room. For some reason, it still uses Defense over Sp.Def, but uses Sp.Def stat changes
            if (ctx->fieldStatuses & STATUS_FIELD_WONDER_ROOM)
                atkStage = gBattleMons[battlerAtk].statStages[STAT_SPDEF];
            else
                atkStage = gBattleMons[battlerAtk].statStages[STAT_DEF];
        }
        else
        {
            atkStat = gBattleMons[battlerAtk].spDefense;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_SPDEF];
        }
    }
    else
    {
        if (IsBattleMovePhysical(move))
        {
            atkStat = gBattleMons[battlerAtk].attack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_ATK];
        }
        else
        {
            atkStat = gBattleMons[battlerAtk].spAttack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_SPATK];
        }
    }

    atkStage = FogNegates ? DEFAULT_STAT_STAGE : atkStage;

    // critical hits ignore attack stat's stage drops
    if (ctx->isCrit && atkStage < DEFAULT_STAT_STAGE)
        atkStage = DEFAULT_STAT_STAGE;
    // pokemon with unaware ignore attack stat changes while taking damage
    if (ctx->abilityDef == ABILITY_UNAWARE)
        atkStage = DEFAULT_STAT_STAGE;

    atkStat *= gStatStageRatios[atkStage][0];
    atkStat /= gStatStageRatios[atkStage][1];

    // apply attack stat modifiers
    modifier = UQ_4_12(1.0);

    if (ctx->isSelfInflicted)
        return uq4_12_multiply_by_int_half_down(ApplyOffensiveBadgeBoost(modifier, battlerAtk, move), atkStat);

    //nightmare - offense stat 15% drop
    //idea just to give it a niche outside dream eater
    //rn works well to cut new sleep heal effect
    //now is also good to counter sleep talk strats
    //dropped more this 15% is essentially nothing
    if (gBattleMons[battlerAtk].volatiles.nightmare)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.80));

    //equates to a 1 stage then 2 stage drop
    if (gBattleMons[battlerAtk].volatiles.octolock)
    {
        if (gBattleMons[battlerAtk].volatiles.octolockCounter == 1)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.67));
        else if (gBattleMons[battlerAtk].volatiles.octolockCounter == 3)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.50));
    }
    
    // attacker's abilities
    switch (ctx->abilityAtk)
    {
    case ABILITY_HUGE_POWER:
    case ABILITY_PURE_POWER:
        if (IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_SLOW_START:
        if (GetBattlerPartyState(battlerAtk)->cachedAbilityTimers > 0)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case ABILITY_SOLAR_POWER:
        if (IsBattleMoveSpecial(move) && IsBattlerWeatherAffected(battlerAtk, WEATHER_SUN))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_DEFEATIST:
        if (gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 2))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case ABILITY_FLASH_FIRE:
        if (moveType == TYPE_FIRE && gBattleMons[battlerAtk].volatiles.flashFireBoosted)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_SWARM:
        if (moveType == TYPE_BUG && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_TORRENT:
        if (moveType == TYPE_WATER && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_BLAZE:
        if (moveType == TYPE_FIRE && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_OVERGROW:
        if (moveType == TYPE_GRASS && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PLUS:
        if (IsBattleMoveSpecial(move) && IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
        {
            enum Ability partnerAbility = GetBattlerAbility(BATTLE_PARTNER(battlerAtk));
            if (partnerAbility == ABILITY_MINUS
            || (B_PLUS_MINUS_INTERACTION >= GEN_5 && partnerAbility == ABILITY_PLUS))
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        }
        break;
    case ABILITY_MINUS:
        if (IsBattleMoveSpecial(move) && IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
        {
            enum Ability partnerAbility = GetBattlerAbility(BATTLE_PARTNER(battlerAtk));
            if (partnerAbility == ABILITY_PLUS
            || (B_PLUS_MINUS_INTERACTION >= GEN_5 && partnerAbility == ABILITY_MINUS))
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        }
        break;
    case ABILITY_FLOWER_GIFT:
        if (gBattleMons[battlerAtk].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(battlerAtk, WEATHER_SUN) && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_HUSTLE:
        if (IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_STAKEOUT:
        if (gBattleStruct->battlerState[battlerDef].isFirstTurn == 2) // just switched in
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_GUTS:
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_TRANSISTOR:
        if (moveType == TYPE_ELECTRIC)
        {
            if (GetConfig(B_TRANSISTOR_BOOST) >= GEN_9)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            else
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        }
        break;
    case ABILITY_DRAGONS_MAW:
        if (moveType == TYPE_DRAGON)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_GORILLA_TACTICS:
        if (IsBattleMovePhysical(move))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_ROCKY_PAYLOAD:
        if (moveType == TYPE_ROCK)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PROTOSYNTHESIS:
        if (!(gBattleMons[battlerAtk].volatiles.transformed))
        {
            enum Stat atkHighestStat = GetParadoxBoostedStatId(battlerAtk);
            if (ctx->weather & WEATHER_SUN || gBattleMons[battlerAtk].volatiles.boosterEnergyActivated)
            {
                if ((IsBattleMovePhysical(move) && atkHighestStat == STAT_ATK) || (IsBattleMoveSpecial(move) && atkHighestStat == STAT_SPATK))
                    modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            }
        }
        break;
    case ABILITY_QUARK_DRIVE:
        if (!(gBattleMons[battlerAtk].volatiles.transformed))
        {
            enum Stat atkHighestStat = GetParadoxBoostedStatId(battlerAtk);
            if (ctx->fieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN || gBattleMons[battlerAtk].volatiles.boosterEnergyActivated)
            {
                if ((IsBattleMovePhysical(move) && atkHighestStat == STAT_ATK) || (IsBattleMoveSpecial(move) && atkHighestStat == STAT_SPATK))
                    modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            }
        }
        break;
    case ABILITY_ORICHALCUM_PULSE:
        if (ctx->weather & WEATHER_SUN && IsBattleMovePhysical(move)
         && ctx->holdEffectAtk != HOLD_EFFECT_UTILITY_UMBRELLA)
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.3333));
        break;
    case ABILITY_HADRON_ENGINE:
        if (ctx->fieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN && IsBattleMoveSpecial(move))
           modifier = uq4_12_multiply(modifier, UQ_4_12(1.3333));
        break;
    default:
        break;
    }

    // target's abilities
    switch (ctx->abilityDef)
    {
    case ABILITY_THICK_FAT:
        if (moveType == TYPE_FIRE || moveType == TYPE_ICE)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
            if (ctx->updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_THICK_FAT);
        }
        break;
    case ABILITY_PURIFYING_SALT:
        if (moveType == TYPE_GHOST)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
            if (ctx->updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_PURIFYING_SALT);
        }
        break;
    default:
        break;
    }

    // ally's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        switch (GetBattlerAbility(BATTLE_PARTNER(battlerAtk)))
        {
        case ABILITY_FLOWER_GIFT:
            if (gBattleMons[BATTLE_PARTNER(battlerAtk)].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(BATTLE_PARTNER(battlerAtk), WEATHER_SUN) && IsBattleMovePhysical(move))
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            break;
        default:
            break;
        }
    }

    // Ruin field effects
    if (IsBattleMoveSpecial(move) && !gBattleMons[ctx->battlerAtk].volatiles.vesselOfRuin && IsRuinStatusActive(VOLATILE_VESSEL_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    if (IsBattleMovePhysical(move) && !gBattleMons[ctx->battlerAtk].volatiles.tabletsOfRuin && IsRuinStatusActive(VOLATILE_TABLETS_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    // attacker's hold effect
    switch (ctx->holdEffectAtk)
    {
    case HOLD_EFFECT_THICK_CLUB:
        if ((atkBaseSpeciesId == SPECIES_CUBONE || atkBaseSpeciesId == SPECIES_MAROWAK) && IsBattleMovePhysical(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_DEEP_SEA_TOOTH:
        if (gBattleMons[battlerAtk].species == SPECIES_CLAMPERL && IsBattleMoveSpecial(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_LIGHT_BALL:
        if (atkBaseSpeciesId == SPECIES_PIKACHU)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_CHOICE_BAND:
        if (IsBattleMovePhysical(move) && GetActiveGimmick(battlerAtk) != GIMMICK_DYNAMAX)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_CHOICE_SPECS:
        if (IsBattleMoveSpecial(move) && GetActiveGimmick(battlerAtk) != GIMMICK_DYNAMAX)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    default:
        break;
    }

    modifier = ApplyOffensiveBadgeBoost(modifier, battlerAtk, move);

    return uq4_12_multiply_by_int_half_down(modifier, atkStat);
}

//removed can't remember why
/*static bool32 CanEvolve(u32 species)
{
    u32 i;
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    if (evolutions != NULL)
    {
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (evolutions[i].method
             && SanitizeSpeciesId(evolutions[i].targetSpecies) != SPECIES_NONE)
                return TRUE;
        }
    }
    return FALSE;
}*/

static inline u32 CalcDefenseStat(struct BattleContext *ctx)
{
    bool32 usesDefStat;
    u8 defStage;
    u32 defStat, def, spDef;
    u32 sideStatus = gSideStatuses[GetBattlerSide(ctx->battlerDef)];
    uq4_12_t modifier;
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);

    def = gBattleMons[battlerDef].defense;
    spDef = gBattleMons[battlerDef].spDefense;

    if (moveEffect == EFFECT_PSYSHOCK || IsBattleMovePhysical(move)) // uses defense stat instead of sp.def
    {
        if (ctx->fieldStatuses & STATUS_FIELD_WONDER_ROOM) // the defense stats are swapped
        {
            defStat = spDef;
            usesDefStat = FALSE;
        }
        else
        {
            defStat = def;
            usesDefStat = TRUE;
        }
        defStage = gBattleMons[battlerDef].statStages[STAT_DEF];
    }
    else // is special
    {
        if (ctx->fieldStatuses & STATUS_FIELD_WONDER_ROOM) // the defense stats are swapped
        {
            defStat = def;
            usesDefStat = TRUE;
        }
        else
        {
            defStat = spDef;
            usesDefStat = FALSE;
        }
        defStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
    }

    // Self-destruct / Explosion cut defense in half
    if (IsExplosionMove(move))
        defStat /= 2;

    // critical hits ignore positive stat changes
    if (ctx->isCrit && defStage > DEFAULT_STAT_STAGE)
        defStage = DEFAULT_STAT_STAGE;
    // pokemon with unaware ignore defense stat changes while dealing damage
    if (ctx->abilityAtk == ABILITY_UNAWARE)
        defStage = DEFAULT_STAT_STAGE;
    // certain moves also ignore stat changes
    if (MoveIgnoresDefenseEvasionStages(move))
        defStage = DEFAULT_STAT_STAGE;

    defStat *= gStatStageRatios[defStage][0];
    defStat /= gStatStageRatios[defStage][1];

    // apply defense stat modifiers
    modifier = UQ_4_12(1.0);

    if (ctx->isSelfInflicted)
        return uq4_12_multiply_by_int_half_down(ApplyDefensiveBadgeBoost(modifier, battlerDef, move), defStat);

    // target's abilities
    switch (ctx->abilityDef)
    {
    case ABILITY_MARVEL_SCALE:
        if (gBattleMons[battlerDef].status1 & STATUS1_ANY && usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            if (ctx->updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_MARVEL_SCALE);
        }
        break;
    case ABILITY_FUR_COAT:
        if (usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
            if (ctx->updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_FUR_COAT);
        }
        break;
    case ABILITY_GRASS_PELT:
        if (ctx->fieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            if (ctx->updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_GRASS_PELT);
        }
        break;
    case ABILITY_FLOWER_GIFT:
        if (gBattleMons[battlerDef].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(battlerDef, WEATHER_SUN) && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PROTOSYNTHESIS:
        {
            enum Stat defHighestStat = GetParadoxBoostedStatId(battlerDef);
            if (((ctx->weather & WEATHER_SUN && HasWeatherEffect()) || gBattleMons[battlerDef].volatiles.boosterEnergyActivated)
             && ((IsBattleMovePhysical(move) && defHighestStat == STAT_DEF) || (IsBattleMoveSpecial(move) && defHighestStat == STAT_SPDEF))
             && !(gBattleMons[battlerDef].volatiles.transformed))
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        }
        break;
    case ABILITY_QUARK_DRIVE:
        {
            u32 defHighestStat = GetParadoxBoostedStatId(battlerDef);
            if ((gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN || gBattleMons[battlerDef].volatiles.boosterEnergyActivated)
             && ((IsBattleMovePhysical(move) && defHighestStat == STAT_DEF) || (IsBattleMoveSpecial(move) && defHighestStat == STAT_SPDEF))
             && !(gBattleMons[battlerDef].volatiles.transformed))
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        }
        break;
    default:
        break;
    }

    // ally's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerDef)))
    {
        switch (GetBattlerAbility(BATTLE_PARTNER(battlerDef)))
        {
        case ABILITY_FLOWER_GIFT:
            if (gBattleMons[BATTLE_PARTNER(battlerDef)].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(BATTLE_PARTNER(battlerDef), WEATHER_SUN) && !usesDefStat)
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            break;
        default:
            break;
        }
    }

    // Ruin field effects
    if (usesDefStat && !gBattleMons[ctx->battlerDef].volatiles.swordOfRuin && IsRuinStatusActive(VOLATILE_SWORD_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    if (!usesDefStat && !gBattleMons[ctx->battlerDef].volatiles.beadsOfRuin && IsRuinStatusActive(VOLATILE_BEADS_OF_RUIN))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    // target's hold effects
    switch (ctx->holdEffectDef)
    {
    case HOLD_EFFECT_DEEP_SEA_SCALE:
        if (gBattleMons[battlerDef].species == SPECIES_CLAMPERL && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_METAL_POWDER:
        if (gBattleMons[battlerDef].species == SPECIES_DITTO && usesDefStat && !(gBattleMons[battlerDef].volatiles.transformed))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_EVIOLITE:
        if (CanEvioliteActivate(battlerDef))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_ASSAULT_VEST:
        if (!usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_SOUL_DEW:
        if (B_SOUL_DEW_BOOST < GEN_7
         && (gBattleMons[battlerDef].species == SPECIES_LATIAS || gBattleMons[battlerDef].species == SPECIES_LATIOS)
         && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
         && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    default:
        break;
    }

    //move effects
    //35% drop gives equive stab boost
    if (move == MOVE_SURGING_STRIKES || move == MOVE_WICKED_BLOW)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.65));

    //status effects
    if (DoesBattlerGetTypeBasedAffinity(ctx->abilityAtk, ctx->battlerDef, ctx->abilityDef, TYPE_GROUND, FALSE) 
    && (sideStatus & SIDE_STATUS_MUDSPORT) && !usesDefStat) //if done right these should stack
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.7));
        //spDefense = (170 * spDefense) / 100; 

    if (gBattleMons[battlerDef].volatiles.infested) //liked the idea of creating a bug status effect, change  move infestaion to swarm, atked by biting swarm!          
    {
            //67% is 1 stage drop
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.67));
    }

    // sandstorm sp.def boost for rock types
    if ((DoesBattlerGetTypeBasedAffinity(ctx->abilityAtk, ctx->battlerDef, ctx->abilityDef, TYPE_ROCK, FALSE) 
    || DoesBattlerGetTypeBasedAffinity(ctx->abilityAtk, ctx->battlerDef, ctx->abilityDef, TYPE_GROUND, FALSE)) 
    && IsBattlerWeatherAffected(battlerDef, WEATHER_SANDSTORM) && !usesDefStat)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));

    //considered giving hail and snow diff buffs more phsy def for hail
    //but believe too much to manage and too much w defense changes to type    
    // snow def boost for ice types
    if (DoesBattlerGetTypeBasedAffinity(ctx->abilityAtk, ctx->battlerDef, ctx->abilityDef, TYPE_ICE, FALSE) 
    && IsBattlerWeatherAffected(battlerDef, WEATHER_ICY_ANY))
    {
        if (usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.35));
        else
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.15));
    }

    modifier = ApplyDefensiveBadgeBoost(modifier, battlerDef, move);

    return uq4_12_multiply_by_int_half_down(modifier, defStat);
}

// base damage formula before adding any modifiers
//added defenderlevel and attack battler argument
static inline s32 CalculateBaseDamage(enum BattlerId battlerAtk, u32 power, u32 userFinalAttack, u32 levelAtk, u32 levelDef, u32 targetFinalDefense)
{

    s32 FinalValue;

    //return power * userFinalAttack * (2 * level / 5 + 2) / targetFinalDefense / 50 + 2;

    //portion fits into (2 * level)
    if ((levelDef - levelAtk >= 7 && !IsOnPlayerSide(battlerAtk))
    || (levelAtk < 6 && levelDef >= 3 && levelDef < 6 && !GetNumBadges()))
        FinalValue = power * userFinalAttack *  (max(2 * levelAtk / 5, 1) + 3); //speed up early leveling a bit
    else
        FinalValue = power * userFinalAttack *  ((((levelAtk*110)/100)/5)+(((levelAtk*168)/100)/11)+2); //perfect formula

    FinalValue /= targetFinalDefense;

    //end divisor after target defense
    if ((levelAtk - levelDef >= 4 && levelAtk <= 12) //dmg feels GOOD,w new formula may inreas this to 10
        || levelAtk - levelDef >= 10)
            FinalValue /= 60;
        else if (levelDef - levelAtk >= 5) //boost underlevel enmemise added back
            FinalValue /= 42; //keep; an eye on this since it would work for both sides
        else
            FinalValue /= 51;

    
    return FinalValue;


}

//vsonic check this
static inline uq4_12_t GetTargetDamageModifier(struct BattleContext *ctx)
{
    if (IsDoubleBattle())
	{
        if (GetMoveTargetCount(ctx) == 2)
            return B_MULTIPLE_TARGETS_DMG >= GEN_4 ? UQ_4_12(0.75) : UQ_4_12(0.5);
        else if (GetMoveTargetCount(ctx) >= 3)
            return B_MULTIPLE_TARGETS_DMG >= GEN_4 ? UQ_4_12(0.75) : UQ_4_12(1.0);
	}
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetParentalBondModifier(enum BattlerId battlerAtk)
{
    if (gSpecialStatuses[battlerAtk].parentalBondState != PARENTAL_BOND_2ND_HIT)
        return UQ_4_12(1.0);
    return UQ_4_12(0.25);
}

//ok NOW think should be good unsure if I need add bide as well? vsonic
//since include joat etc decide rename function was GetSameTypeAttackBonusModifier
static inline uq4_12_t GetTypeBasedBonusModifier(struct BattleContext *ctx)
{
    enum Type SecondarymoveType = GetTwoTypedMove2ndType(ctx->move);

    //if its just returning neutral do I need these at all here?
    //yeah it needs to return something cuz multiplies result
    if (ctx->move == MOVE_STRUGGLE || ctx->move == MOVE_NONE)
        return UQ_4_12(1.0);
        
    else if (GetBaseFormSpecies(gBattleMons[ctx->battlerAtk].species) == SPECIES_ARCEUS)
        return SAME_TYPE_MULTIPLIER;

    else if (ctx->moveType == TYPE_MYSTERY
    || (ctx->moveType == TYPE_SOUND && !IS_BATTLER_OF_TYPE(ctx->battlerAtk, TYPE_NORMAL)))
        return UQ_4_12(1.0);

    else if (gBattleStruct->pledgeMove && DoesBattlerGetStabOnMove(BATTLE_PARTNER(ctx->battlerAtk), ctx->moveType))
        return (ctx->abilityAtk == ABILITY_ADAPTABILITY) ? ADAPTABILITY_MULTIPLIER : SAME_TYPE_MULTIPLIER;

    //normal stab, applied for two typed moves  as well
    else if (DoesBattlerGetStabOnMove(ctx->battlerAtk, ctx->moveType)
    || DoesBattlerGetStabOnMove(ctx->battlerAtk, SecondarymoveType))
        return (ctx->abilityAtk == ABILITY_ADAPTABILITY) ? ADAPTABILITY_MULTIPLIER : SAME_TYPE_MULTIPLIER;
    
    //ability psuedo stab effects
    else if (GetBattlerAbility(ctx->battlerAtk) == ABILITY_TOADSTOOL_NYMPH
    && (ctx->moveType == TYPE_FAIRY || SecondarymoveType == TYPE_FAIRY))
        return SAME_TYPE_MULTIPLIER;
    else if (GetBattlerAbility(ctx->battlerAtk) == ABILITY_CREATION_ENGINE
    && (ctx->moveType == TYPE_FIRE || ctx->moveType == TYPE_ICE || ctx->moveType == TYPE_ELECTRIC) 
    || (SecondarymoveType == TYPE_FIRE || SecondarymoveType == TYPE_ICE || SecondarymoveType == TYPE_ELECTRIC))
        return SAME_TYPE_MULTIPLIER;

    else if (IS_BATTLER_OF_TYPE(ctx->battlerAtk, TYPE_NORMAL))
        return JOAT_MULTIPLIER;

    return UQ_4_12(1.0); //catch all


    //return (ctx->abilityAtk == ABILITY_ADAPTABILITY) ? ADAPTABILITY_MULTIPLIER : SAME_TYPE_MULTIPLIER;
}

// Utility Umbrella holders take normal damage from what would be rain- and sun-weakened attacks.
//need also put cloud nine changes here and castform effects
//vsonic
static uq4_12_t GetWeatherDamageModifier(struct BattleContext *ctx)
{

    bool32 CloudNineAffected = (ctx->abilityDef == ABILITY_CLOUD_NINE);
    bool32 CloudNineOnSide = (DoesSideHaveAbility(ctx->battlerAtk, ABILITY_CLOUD_NINE));
    bool32 AtkCastform = (GetBaseFormSpecies(gBattleMons[ctx->battlerAtk].species) == SPECIES_CASTFORM);
    bool32 OceanMemoryActive = (ctx->abilityAtk == ABILITY_OCEAN_MEMORY && GetMoveType(ctx->move) == TYPE_WATER);

    if (ctx->weather == WEATHER_NONE)
        return UQ_4_12(1.0);
    if (GetMoveEffect(ctx->move) == EFFECT_HYDRO_STEAM && (ctx->weather & WEATHER_SUN) && ctx->holdEffectAtk != HOLD_EFFECT_UTILITY_UMBRELLA
    && !CloudNineAffected)
        return UQ_4_12(1.5);

    //this is weather dmg modifiers
    //utilty umbrella returns early cuz in old gen only
    //rain and sun which umbrella blocks affected typed move damage
    //acid rain would still fit but since I've added hail/snow effects
    //is no longer accurate to just return
    //vsonic need update w new values
    //unsure if will set theese up like this
    //review if need safety goggles and umbrella need be changed buffed
    if (ctx->holdEffectDef == HOLD_EFFECT_UTILITY_UMBRELLA
    && (ctx->weather & WEATHER_RAIN_ALL
    || ctx->weather & WEATHER_LIGHT_BASED))
        return UQ_4_12(1.0);

    //rn only ice has dmg based weather effect
    //but including for sake of
    if (ctx->holdEffectDef == HOLD_EFFECT_SAFETY_GOGGLES
    && ctx->weather & WEATHER_ICE_SAND)
        return UQ_4_12(1.0);

    if (ctx->weather & WEATHER_RAIN)
    {
        //default wasn't affected by cloudnine
        //think will make that change tho
        //doesn't block ability entire effect
        if (OceanMemoryActive && !CloudNineAffected)
            return UQ_4_12(1.5);

        if (ctx->moveType != TYPE_FIRE && ctx->moveType != TYPE_WATER)
            return UQ_4_12(1.0);
        else if (ctx->moveType == TYPE_WATER)
        {
            return (!CloudNineAffected) ? UQ_4_12(1.5) : UQ_4_12(1.0);
        }

        return (!AtkCastform && !CloudNineOnSide) ? UQ_4_12(0.5) : UQ_4_12(1.0);
    }
    if (ctx->weather & WEATHER_ACID_RAIN) //FIRE WATER
    {
        if (ctx->moveType != TYPE_FIRE && ctx->moveType != TYPE_WATER)
            return UQ_4_12(1.0);

        return (!CloudNineAffected) ? UQ_4_12(1.3) : UQ_4_12(1.0);
    }
    if (ctx->weather & WEATHER_SUN)
    {
        if (ctx->moveType != TYPE_FIRE && ctx->moveType != TYPE_WATER
        && ctx->moveType != TYPE_ICE)
            return UQ_4_12(1.0);
        else if (ctx->moveType == TYPE_FIRE)
        {
            return (!CloudNineAffected) ? UQ_4_12(1.5) : UQ_4_12(1.0);
        }
        
        return (!AtkCastform && !CloudNineOnSide) ? UQ_4_12(0.5) : UQ_4_12(1.0);
    }
    if (ctx->weather & WEATHER_MOON) //water fairy
    {
        if (ctx->moveType != TYPE_WATER && ctx->moveType != TYPE_FAIRY)
            return UQ_4_12(1.0);
        return (!CloudNineAffected) ? UQ_4_12(1.3) : UQ_4_12(1.0);
    }
    if (ctx->weather & WEATHER_ICY_ANY) //fire drop
    {
        if (ctx->moveType != TYPE_FIRE)
            return UQ_4_12(1.0);
        return (!AtkCastform && !CloudNineOnSide) ? UQ_4_12(0.8) : UQ_4_12(1.0);
    }
    return UQ_4_12(1.0);
}

//removed frostbite was just legends arcues sp atk drop
//put infatuation drop here rename function to status modifiers
//actually no will make another one to put after this
//so its its own thing
static inline uq4_12_t GetBurnOrFrostBiteModifier(struct BattleContext *ctx)
{
    enum BattleMoveEffects moveEffect = GetMoveEffect(ctx->move);

    if (gBattleMons[ctx->battlerAtk].status1 & STATUS1_BURN
        && IsBattleMovePhysical(ctx->move)
        && moveEffect != EFFECT_FACADE
        && ctx->abilityAtk != ABILITY_GUTS
        && ctx->abilityAtk != ABILITY_HEAT_TRANCE
        && ctx->abilityAtk != ABILITY_TOOLS_OF_THE_TRADE)
        {
            //halves effects from burn & heat/fire  //so burn atk cut is less
            if (ctx->abilityAtk == ABILITY_HEATPROOF 
            || ctx->abilityAtk == ABILITY_DESERT_DWELLER)
                return UQ_4_12(0.75);
            else
                return UQ_4_12(0.5);
        }
        
    
    /*
    if (gBattleMons[ctx->battlerAtk].status1 & STATUS1_FROSTBITE
        && IsBattleMoveSpecial(ctx->move)
        && moveEffect != EFFECT_FACADE)
        return UQ_4_12(0.5);
    */
    
    return UQ_4_12(1.0);
}

//made its on thing and moved further down
//to avoid getting truncated with other multipliers applying
//should hopefully be more in line with intention.
static inline uq4_12_t GetInfatuationModifier(struct BattleContext *ctx)
{

    if (IsMonInfatuatedWithOnOpposingSide(ctx->battlerAtk))
        return UQ_4_12(0.75);
        
    
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetCriticalModifier(bool32 isCrit)
{
    if (isCrit)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetGlaiveRushModifier(enum BattlerId battlerDef)
{
    if (gBattleMons[battlerDef].volatiles.glaiveRush)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

//not using z or max moves but function is useful
//potentially rename to protectBreak effects 
//GetProtectBreakModifiers
//hmm with that in mind could make new cat
//separates ignores protect and breaks through protect
//on the other hand think bad for balance for breaking through
//protect to become a common effect 
//so better to just leave to a few moves that bypass alltogether
//was GetZMaxMoveAgainstProtectionModifier
//may keep z move implementation just not use it
static inline uq4_12_t GetProtectBreakModifiers(struct BattleContext *ctx)
{
    u32 protected = gProtectStructs[ctx->battlerDef].protected;
    
    if (protected == PROTECT_SHIELD_BASH && !ctx->isCrit)
    {
        //believe initially made this w original super multiplier
        //so think need adjust since super no longer 2x
        if (ctx->typeEffectivenessModifier >= SUPER_EFFECTIVE)
            return UQ_4_12(0.20);
        else
            return UQ_4_12(0.30);
    }
    
    else if (!IsZMove(ctx->move) && !IsMaxMove(ctx->move))
        return UQ_4_12(1.0);

    
    if (GetProtectType(protected) == PROTECT_TYPE_SINGLE && protected != PROTECT_MAX_GUARD)
        return UQ_4_12(0.25);
    return UQ_4_12(1.0);
}

//not using renamed to evasive break
//becomes sure hit not increased dmg
/*static inline uq4_12_t GetMinimizeModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveIncreasesPowerToMinimizedTargets(move) && gBattleMons[battlerDef].volatiles.minimize)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}*/

static inline uq4_12_t GetUndergroundModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveDamagesUnderground(move) && gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_UNDERGROUND)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDiveModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveDamagesUnderWater(move) && gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_UNDERWATER)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAirborneModifier(enum Move move, enum BattlerId battlerDef)
{
    if (MoveDamagesAirborneDoubleDamage(move) && gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_ON_AIR)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetScreensModifier(struct BattleContext *ctx)
{
    u32 sideStatus = gSideStatuses[GetBattlerSide(ctx->battlerDef)];
    bool32 lightScreen = (sideStatus & SIDE_STATUS_LIGHTSCREEN) && IsBattleMoveSpecial(ctx->move);
    bool32 reflect = (sideStatus & SIDE_STATUS_REFLECT) && IsBattleMovePhysical(ctx->move);
    bool32 auroraVeil = sideStatus & SIDE_STATUS_AURORA_VEIL;

    if (ctx->isCrit || ctx->isSelfInflicted)
    {
        return UQ_4_12(1.0);
    }
    if (ctx->abilityAtk == ABILITY_INFILTRATOR)
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerAtk, ctx->abilityDef);
        return UQ_4_12(1.0);
    }
    if (reflect || lightScreen || auroraVeil)
    {
        return (IsDoubleBattle()) ? UQ_4_12(0.667) : UQ_4_12(0.5);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetCollisionCourseElectroDriftModifier(enum Move move, uq4_12_t typeEffectivenessModifier)
{
    if (GetMoveEffect(move) == EFFECT_COLLISION_COURSE && typeEffectivenessModifier >= UQ_4_12(2.0))
        return UQ_4_12(1.3333);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAttackerAbilitiesModifier(enum BattlerId battlerAtk, uq4_12_t typeEffectivenessModifier, bool32 isCrit, enum Ability abilityAtk)
{
    switch (abilityAtk)
    {
    case ABILITY_NEUROFORCE:
        if (typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(1.25);
        break;
    case ABILITY_SNIPER:
        if (isCrit)
            return UQ_4_12(1.5);
        break;
    case ABILITY_TINTED_LENS:
        if (typeEffectivenessModifier <= UQ_4_12(0.5))
            return UQ_4_12(2.0);
        break;
    default:
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderAbilitiesModifier(struct BattleContext *ctx)
{
    bool32 recordAbility = FALSE;
    uq4_12_t modifier = UQ_4_12(1.0);

    switch (ctx->abilityDef)
    {
    case ABILITY_MULTISCALE:
    case ABILITY_SHADOW_SHIELD:
        if (IsBattlerAtMaxHp(ctx->battlerDef))
        {
            modifier = UQ_4_12(0.5);
            recordAbility = TRUE;
        }
        break;
    case ABILITY_FILTER:
    case ABILITY_SOLID_ROCK:
    case ABILITY_PRISM_ARMOR:
        if (ctx->typeEffectivenessModifier >= UQ_4_12(2.0))
        {
            modifier = UQ_4_12(0.75);
            recordAbility = TRUE;
        }
        break;
    case ABILITY_FLUFFY:
        if (ctx->moveType == TYPE_FIRE && !IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ABILITY_NONE, ctx->holdEffectAtk, ctx->move))
        {
            modifier = UQ_4_12(2.0);
            recordAbility = TRUE;
        }
        if (ctx->moveType != TYPE_FIRE && IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ABILITY_NONE, ctx->holdEffectAtk, ctx->move))
        {
            modifier = UQ_4_12(0.5);
            recordAbility = TRUE;
        }
        break;
    case ABILITY_PUNK_ROCK:
        if (IsSoundMove(ctx->move))
        {
            modifier = UQ_4_12(0.5);
            recordAbility = TRUE;
        }
        break;
    case ABILITY_ICE_SCALES:
        if (IsBattleMoveSpecial(ctx->move))
        {
            modifier =  UQ_4_12(0.5);
            recordAbility = TRUE;
        }
        break;
    default:
        break;
    }

    if (recordAbility && ctx->updateFlags)
        RecordAbilityBattle(ctx->battlerAtk, ctx->abilityDef);

    return modifier;
}

static inline uq4_12_t GetDefenderPartnerAbilitiesModifier(enum BattlerId battlerPartnerDef)
{
    if (!IsBattlerAlive(battlerPartnerDef))
        return UQ_4_12(1.0);

    switch (GetBattlerAbility(battlerPartnerDef))
    {
    case ABILITY_FRIEND_GUARD:
        return UQ_4_12(0.75);
        break;
    default:
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAttackerItemsModifier(enum BattlerId battlerAtk, uq4_12_t typeEffectivenessModifier, enum HoldEffect holdEffectAtk)
{
    u32 metronomeTurns;
    uq4_12_t metronomeBoostBase;
    switch (holdEffectAtk)
    {
    case HOLD_EFFECT_METRONOME:
        metronomeBoostBase = PercentToUQ4_12(GetBattlerHoldEffectParam(battlerAtk));
        metronomeTurns = min(gBattleMons[battlerAtk].volatiles.metronomeItemCounter, 5);
        // according to bulbapedia this is the "correct" way to calculate the metronome boost
        // due to the limited domain of damage numbers it will never really matter whether this is off by one
        return uq4_12_add(UQ_4_12(1.0), metronomeBoostBase * metronomeTurns);
        break;
    case HOLD_EFFECT_EXPERT_BELT:
        if (typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(1.2);
        break;
    case HOLD_EFFECT_LIFE_ORB:
        return UQ_4_12_FLOORED(1.3);
        break;
    default:
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderItemsModifier(struct BattleContext *ctx)
{
    switch (ctx->holdEffectDef)
    {
    case HOLD_EFFECT_RESIST_BERRY:
        if (IsUnnerveBlocked(ctx->battlerDef, gBattleMons[ctx->battlerDef].item))
            return UQ_4_12(1.0);
        if (ctx->moveType == GetBattlerHoldEffectParam(ctx->battlerDef) && (ctx->moveType == TYPE_NORMAL || ctx->typeEffectivenessModifier >= UQ_4_12(2.0)))
        {
            if (ctx->updateFlags)
                gSpecialStatuses[ctx->battlerDef].berryReduced = TRUE;
            if (ctx->aiCalc && AI_DAMAGES_THROUGH_BERRIES)
                ctx->aiCheckBerryModifier = TRUE;
            return (ctx->abilityDef == ABILITY_RIPEN) ? UQ_4_12(0.25) : UQ_4_12(0.5);
        }
        break;
    default:
        break;
    }
    return UQ_4_12(1.0);
}

#define DAMAGE_MULTIPLY_MODIFIER(modifier) do {                     \
    finalModifier = uq4_12_multiply_half_down(modifier, finalModifier); \
} while (0)

// Calculates the "other" modifier which accounts for held items, abilities,
// or very specific interactions of moves that are not handled in the basic
// damage calculation. It is implemented as described by bulbapedia:
// https://bulbapedia.bulbagarden.net/wiki/Damage#Generation_V_onward
// Please Note: Fixed Point Multiplication is not associative.
// The order of operations is relevant.
static inline uq4_12_t GetOtherModifiers(struct BattleContext *ctx)
{
    uq4_12_t finalModifier = UQ_4_12(1.0);
    enum BattlerId battlerDefPartner = BATTLE_PARTNER(ctx->battlerDef);
    u32 unmodifiedAttackerSpeed = gBattleMons[ctx->battlerAtk].speed;
    u32 unmodifiedDefenderSpeed = gBattleMons[ctx->battlerDef].speed;

    //TODO: Behemoth Blade, Behemoth Bash, Dynamax Cannon (Dynamax)
    //DAMAGE_MULTIPLY_MODIFIER(GetMinimizeModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetUndergroundModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetDiveModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetAirborneModifier(ctx->move, ctx->battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetScreensModifier(ctx));
    DAMAGE_MULTIPLY_MODIFIER(GetCollisionCourseElectroDriftModifier(ctx->move, ctx->typeEffectivenessModifier));

    if (unmodifiedAttackerSpeed >= unmodifiedDefenderSpeed)
    {
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerAbilitiesModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier, ctx->isCrit, ctx->abilityAtk));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderAbilitiesModifier(ctx));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerAbilitiesModifier(battlerDefPartner));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerItemsModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier, ctx->holdEffectAtk));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderItemsModifier(ctx));
    }
    else
    {
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderAbilitiesModifier(ctx));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerAbilitiesModifier(battlerDefPartner));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerAbilitiesModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier, ctx->isCrit, ctx->abilityAtk));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderItemsModifier(ctx));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerItemsModifier(ctx->battlerAtk, ctx->typeEffectivenessModifier, ctx->holdEffectAtk));
    }
    return finalModifier;
}

#undef DAMAGE_ACCUMULATE_MULTIPLIER

#define DAMAGE_APPLY_MODIFIER(modifier) do {               \
    dmg = uq4_12_multiply_by_int_half_down(modifier, dmg); \
} while (0)


//used to exclude for bottom effect doesn't include status moves that do so
//well nah might as well include all
const u8 *const gPlayCryanims[] =
{
    gBattleAnimMove_AlluringVoice,
    gBattleAnimMove_Boomburst,
    gBattleAnimMove_RelicSong,
    gBattleAnimMove_TorchSong,
    gBattleAnimMove_HyperVoice,
    gBattleAnimMove_Round,
    gBattleAnimMove_Chatter,
    gBattleAnimMove_RoarOfTime,
    gBattleAnimMove_DisarmingVoice,
    gBattleAnimMove_HyperspaceFury
};

//used to exclude for bottom effect doesn't include status moves that do so
//well nah might as well include all
static bool32 DoesMoveUseCryInBattleAnim(u16 move)
{
    u32 i;
    GetMoveAnimationScript(move);

    for (i = 0; i < sizeof(gPlayCryanims); i++)
    {
        if (GetMoveAnimationScript(move) == gPlayCryanims[i])
            return TRUE;
    }

    return FALSE;


}

//need test
static inline s32 ApplyMuscleWiseAdditiveBoosts(struct BattleContext *ctx, s32 Dmg)
{
    //still deciding do 5% or 10%
    //uq4_12_t multiplier = UQ_4_12(0.05);
    uq4_12_t multiplier = UQ_4_12(0.1);
    uq4_12_t modifier = UQ_4_12(0.0); //ensure no garbage data
    u32 atkStat;


    switch (ctx->holdEffectAtk)
    {
    case HOLD_EFFECT_MUSCLE_BAND:
        if (IsBattleMovePhysical(ctx->move))
        {
            atkStat = gBattleMons[ctx->battlerAtk].attack;
            modifier = uq4_12_multiply_by_int_half_down(multiplier, atkStat);
        }
        break;
    case HOLD_EFFECT_WISE_GLASSES:
        if (IsBattleMoveSpecial(ctx->move))
        {
            atkStat = gBattleMons[ctx->battlerAtk].spAttack;
            modifier = uq4_12_multiply_by_int_half_down(multiplier, atkStat);
        }
        break;
    }
    return Dmg += modifier;
}

//idk where this applies but need to adjust this
//to get my update for cry to play on high roll or crit
//may need make new ewram value to store that it should do so
static inline s32 DoMoveDamageCalcVars(struct BattleContext *ctx)
{
    s32 dmg;
    u32 userFinalAttack;
    u32 targetFinalDefense;
    u32 dmgroll = DMG_ROLL_PERCENT_HI - RandomUniform(RNG_DAMAGE_MODIFIER, 0, DMG_ROLL_PERCENT_HI - DMG_ROLL_PERCENT_LO);

    if (ctx->fixedBasePower)
        gBattleMovePower = ctx->fixedBasePower;
    else
        gBattleMovePower = CalcMoveBasePowerAfterModifiers(ctx);

    userFinalAttack = CalcAttackStat(ctx);
    targetFinalDefense = CalcDefenseStat(ctx);

    dmg = CalculateBaseDamage(ctx->battlerAtk, gBattleMovePower, userFinalAttack, gBattleMons[ctx->battlerAtk].level, gBattleMons[ctx->battlerDef].level, targetFinalDefense);
    DAMAGE_APPLY_MODIFIER(GetTargetDamageModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetParentalBondModifier(ctx->battlerAtk));
    DAMAGE_APPLY_MODIFIER(GetWeatherDamageModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetCriticalModifier(ctx->isCrit));
    DAMAGE_APPLY_MODIFIER(GetGlaiveRushModifier(ctx->battlerDef));

    if (ctx->randomFactor)
    {
        dmg *= dmgroll;
        dmg /= 100;

        //works in EE putting within randomfactor should
        //naturally exclude things like fixed effects and status moves
        if (gMain.inBattle && !DoesMoveUseCryInBattleAnim(ctx->move)
        && (dmgroll == DMG_ROLL_PERCENT_HI || ctx->isCrit))
            PlayCry_Normal(gBattleMons[ctx->battlerAtk].species, 25);

    }
    else // Apply rest of modifiers in the ai function
    {
        if (dmg == 0)
            dmg = 1;
        return ApplyMuscleWiseAdditiveBoosts(ctx, dmg);
    }//unsure think just for ai
    //oh only time see random false is for self hit
    //if effect of muslc band stuff is too strong
    //can put here as drawback effects
    //nah I want that in general
    //should already be strong as works w fixed dmg moves as well
    //think may need check adjust self hit dmg/moves to ensure
    //are effected by either not just only muscle band
    //nvm bit annoying but no way to do that
    //confusion already leaned towards only affecting physcal
    //was entire reason I reworked flatter rather than
    //just being a sp atk boost

    dmg = ApplyModifiersAfterDmgRoll(ctx, dmg);

    if (dmg == 0)
        dmg = 1;
    return ApplyMuscleWiseAdditiveBoosts(ctx, dmg);
}

s32 ApplyModifiersAfterDmgRoll(struct BattleContext *ctx, s32 dmg)
{
    if (GetActiveGimmick(ctx->battlerAtk) == GIMMICK_TERA)
        DAMAGE_APPLY_MODIFIER(GetTeraMultiplier(ctx)); //includes stab
    else
        DAMAGE_APPLY_MODIFIER(GetTypeBasedBonusModifier(ctx)); //stab and the like
    DAMAGE_APPLY_MODIFIER(ctx->typeEffectivenessModifier);
    DAMAGE_APPLY_MODIFIER(GetBurnOrFrostBiteModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetInfatuationModifier(ctx));
    DAMAGE_APPLY_MODIFIER(GetProtectBreakModifiers(ctx));
    DAMAGE_APPLY_MODIFIER(GetOtherModifiers(ctx));

    return dmg;
}

//wokrs cuz only used in the specific place it can apply
static s32 returnVariableDmg(struct BattleContext *ctx)
{
    s32 moveDamage = 0;

    switch (GetMoveEffect(ctx->move))
    {
        case EFFECT_LEVEL_DAMAGE:
        {
            u8 level_Limiter;// = gBattleMons[gBattlerAttacker].level;
            u32 weightscaling;
            u8 lvl_scaling = 70;  //means % dmg is from lvl
            u8 UserLevel = gBattleMons[ctx->battlerAtk].level;

            //min dmg at lvl 5 is 7hp, think should be fine now
            if (ctx->move == MOVE_SEISMIC_TOSS)
            {
                
                weightscaling = (WeightBoostedDamageFormula(ctx->battlerDef) / 10);
                weightscaling = UserLevel <= 15 ? weightscaling : (WeightBoostedDamageFormula(ctx->battlerDef) / 5);
                weightscaling = UserLevel < 30  ? weightscaling : (WeightBoostedDamageFormula(ctx->battlerDef) / 3);
                weightscaling = UserLevel < 45  ? weightscaling : (WeightBoostedDamageFormula(ctx->battlerDef) / 2);


                level_Limiter = max((gBattleMons[ctx->battlerAtk].level * lvl_scaling) / 100, 1);


                moveDamage = level_Limiter + weightscaling;// * (level_Limiter / max_skill_lvl)); //max 145 or +45% lvl

            }
            else
                moveDamage = gBattleMons[ctx->battlerAtk].level;
        }
        break;
        case EFFECT_PSYWAVE:
        {
            s32 randDamage;
            u8 scaler = 50;
            u8 lvl = gBattleMons[ctx->battlerAtk].level;

            //experession/condition? value : value2  see if use for different values without having to use big if elses etc
            //found its ternary operator if value before ? is true value uses value before colon, else uses value after colon
            randDamage = (Random() % 9) + 2; //VALUe between 2-10 with scaler is 70% up to 120%

            randDamage *= 10;   //becomes a value between 20 & 100
            moveDamage = lvl * (randDamage + scaler) / 100;  
    
        }
        break;
    }

    return moveDamage;
}

//mostly done just setup beatup think
//make sure test seismic toss
//values here make it do typeless dmg
s32 DoFixedDamageMoveCalc(struct BattleContext *ctx)
{
    s32 dmg = INT32_MAX;
    s32 randDamage;

    switch (GetMoveEffect(ctx->move))
    {
    case EFFECT_LEVEL_DAMAGE:
        dmg = returnVariableDmg(ctx);
        break;
    case EFFECT_PSYWAVE:
        //randDamage = B_PSYWAVE_DMG >= GEN_5 ? (Random() % 101) : ((Random() % 11) * 10);
        //dmg = gBattleMons[ctx->battlerAtk].level * (randDamage + 50) / 100;
        dmg = returnVariableDmg(ctx);
        break;
    case EFFECT_FIXED_HP_DAMAGE:
        dmg = GetMoveFixedDamage(ctx->move);
        break;
    case EFFECT_FIXED_PERCENT_DAMAGE:
        dmg = GetNonDynamaxHP(ctx->battlerDef) * GetMoveDamagePercentage(ctx->move) / 100;
        break;
    case EFFECT_FINAL_GAMBIT:
        dmg = GetNonDynamaxHP(ctx->battlerAtk);
        break;
    case EFFECT_BEAT_UP:
        if (GetConfig(B_BEAT_UP) < GEN_5)
            dmg = CalcBeatUpDamage(ctx);//check this vsonic
        break;
    case EFFECT_REFLECT_DAMAGE:
        if (!ctx->aiCalc)
        {
            u32 percentMultiplier = GetMoveReflectDamage_DamagePercent(ctx->move);
            enum DamageCategory reflectCategory = GetReflectDamageMoveDamageCategory(ctx->battlerAtk, ctx->move);
            s32 baseDamage;

            if (reflectCategory == DAMAGE_CATEGORY_PHYSICAL)
                baseDamage = gProtectStructs[ctx->battlerAtk].physicalDmg;
            else
                baseDamage = gProtectStructs[ctx->battlerAtk].specialDmg;

            dmg = (baseDamage - 1) * percentMultiplier / 100;
        }
        break;
    case EFFECT_ENDEAVOR:
        if (GetNonDynamaxHP(ctx->battlerDef) <= gBattleMons[ctx->battlerAtk].hp)
        {
            dmg = 0;
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        }
        else
        {
            dmg = GetNonDynamaxHP(ctx->battlerDef) - gBattleMons[ctx->battlerAtk].hp;
        }
        break;
    default:
        break;
    }

    if (dmg == INT32_MAX)
        return dmg;

    gBattleStruct->moveResultFlags[ctx->battlerDef] &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);

    if (dmg == 0)
        dmg = 1;

    return ApplyMuscleWiseAdditiveBoosts(ctx, dmg);
}

//if is fixed move skip calcvar function
//whihc makes it skip type check and do typeless dmg
static inline s32 DoMoveDamageCalc(struct BattleContext *ctx)
{
    if (ctx->typeEffectivenessModifier == UQ_4_12(0.0))
        return 0;

    s32 dmg = DoFixedDamageMoveCalc(ctx);
    if (dmg != INT32_MAX)
        return dmg;

    return DoMoveDamageCalcVars(ctx);
}

//no crit no stab typless dmg
//no crit added stab back
//will keep typeless rework description
//rather than hurling psychic energy at foe to damage them
//they use their psychic powers to peer into the future
//to cause the target harm
static inline s32 DoFutureSightAttackDamageCalcVars(struct BattleContext *ctx)
{
    s32 dmg;
    u32 userFinalAttack;
    u32 targetFinalDefense;
    enum BattlerId battlerAtk = ctx->battlerAtk;
    enum BattlerId battlerDef = ctx->battlerDef;
    enum Move move = ctx->move;
    enum Type moveType = ctx->moveType;

    struct Pokemon *party = GetBattlerParty(battlerAtk);
    struct Pokemon *partyMon = &party[gBattleStruct->futureSight[battlerDef].partyIndex];
    u32 partyMonLevel = GetMonData(partyMon, MON_DATA_LEVEL);
    u32 partyMonSpecies = GetMonData(partyMon, MON_DATA_SPECIES);
    u32 targetMonLevel = GetMonData(GetBattlerMon(battlerDef), MON_DATA_LEVEL);
    gBattleMovePower = GetMovePower(move);

    if (IsBattleMovePhysical(move))
        userFinalAttack = GetMonData(partyMon, MON_DATA_ATK);
    else
        userFinalAttack = GetMonData(partyMon, MON_DATA_SPATK);

    targetFinalDefense = CalcDefenseStat(ctx);
    dmg = CalculateBaseDamage(battlerAtk, gBattleMovePower, userFinalAttack, partyMonLevel, targetMonLevel, targetFinalDefense);

    //DAMAGE_APPLY_MODIFIER(GetCriticalModifier(ctx->isCrit));

    if (ctx->randomFactor)
    {
        dmg *= DMG_ROLL_PERCENT_HI - RandomUniform(RNG_DAMAGE_MODIFIER, 0, DMG_ROLL_PERCENT_HI - DMG_ROLL_PERCENT_LO);
        dmg /= 100;
    }

    // Same type attack bonus
    if (GetSpeciesPrimaryType(partyMonSpecies) == moveType || GetSpeciesSecondaryType(partyMonSpecies) == moveType)
        DAMAGE_APPLY_MODIFIER(SAME_TYPE_MULTIPLIER);
    else
        DAMAGE_APPLY_MODIFIER(UQ_4_12(1.0));

    //DAMAGE_APPLY_MODIFIER(ctx->typeEffectivenessModifier);

    if (dmg == 0)
        dmg = 1;

    return dmg;
}

//ok previously move type was set to mystery
//its fine just don't need change just set typeless logic in
//that function that way will return value 1 same as before
static inline s32 DoFutureSightAttackDamageCalc(struct BattleContext *ctx)
{
    if (ctx->typeEffectivenessModifier == NO_EFFECT)
        return 0;

    return DoFutureSightAttackDamageCalcVars(ctx);
}

bool32 IsFutureSightAttackerInParty(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (GetMoveEffect(move) != EFFECT_FUTURE_SIGHT)
        return FALSE;

    struct Pokemon *party = GetBattlerParty(battlerAtk);
    if (IsDoubleBattle())
    {
        return &party[gBattleStruct->futureSight[battlerDef].partyIndex] != &party[gBattlerPartyIndexes[battlerAtk]]
            && &party[gBattleStruct->futureSight[battlerDef].partyIndex] != &party[gBattlerPartyIndexes[BATTLE_PARTNER(battlerAtk)]];
    }

    return &party[gBattleStruct->futureSight[battlerDef].partyIndex] != &party[gBattlerPartyIndexes[battlerAtk]];
}

#undef DAMAGE_APPLY_MODIFIER

// The chance is 1/N for each stage.
static const u32 sGen7CriticalHitOdds[] = {24,  8,  2,  1,   1}; // 1/X
static const u32 sGen6CriticalHitOdds[] = {16,  8,  2,  1,   1}; // 1/X
static const u32 sCriticalHitOdds[]     = {16,  8,  4,  3,   2}; // 1/X, Gens 3,4,5
static const u32 sGen2CriticalHitOdds[] = {17, 32, 64, 85, 128}; // X/256
static const u32 sCriticalHitChance[]   = { 16, 6, 4, 2, 1 }; // 1/x  my version //3rd stage was 3 made 2 unsure since still full double crit

static inline u32 GetCriticalHitOdds(u32 critChance)
{
    /*if (GetConfig(B_CRIT_CHANCE) >= GEN_7)
        return sGen7CriticalHitOdds[critChance];
    if (GetConfig(B_CRIT_CHANCE) == GEN_6)
        return sGen6CriticalHitOdds[critChance];
    if (GetConfig(B_CRIT_CHANCE) == GEN_2)
        return sGen2CriticalHitOdds[critChance];*/

    return sCriticalHitChance[critChance];
}

static inline u32 IsBattlerLeekAffected(enum BattlerId battler, enum HoldEffect holdEffect)
{
    if (holdEffect == HOLD_EFFECT_LEEK)
    {
        return GET_BASE_SPECIES_ID(gBattleMons[battler].species) == SPECIES_FARFETCHD
            || gBattleMons[battler].species == SPECIES_SIRFETCHD;
    }
    return FALSE;
}

static inline u32 GetHoldEffectCritChanceIncrease(enum BattlerId battler, enum HoldEffect holdEffect)
{
    u32 critStageIncrease = 0;

    switch (holdEffect)
    {
    case HOLD_EFFECT_SCOPE_LENS:
        critStageIncrease = 1;
        break;
    case HOLD_EFFECT_LUCKY_PUNCH:
        if (gBattleMons[battler].species == SPECIES_CHANSEY)
            critStageIncrease = 2;
        break;
    case HOLD_EFFECT_LEEK:
        if (IsBattlerLeekAffected(battler, holdEffect))
            critStageIncrease = 2;
        break;
    default:
        critStageIncrease = 0;
        break;
    }

    return critStageIncrease;
}

s32 CalcCritChanceStage(struct BattleContext *ctx)
{
    s32 critChance = 0;

    if (gSideStatuses[GetBattlerSide(ctx->battlerDef)] & SIDE_STATUS_LUCKY_CHANT
    || gProtectStructs[ctx->battlerDef].blockcrit)
    {
        critChance = CRITICAL_HIT_BLOCKED;
    }
    else if (gBattleMons[ctx->battlerAtk].volatiles.laserFocus
          || MoveAlwaysCrits(ctx->move)
          || (ctx->abilityAtk == ABILITY_MERCILESS && gBattleMons[ctx->battlerDef].status1 & STATUS1_PSN_ANY))
    {
        critChance = CRITICAL_HIT_ALWAYS;
    }
    else
    {
        //need add dark deal to this etc.
        critChance  = (gBattleMons[ctx->battlerAtk].volatiles.focusEnergy != 0 ? 2 : 0)
                    + (gBattleMons[ctx->battlerAtk].volatiles.dragonCheer != 0 ? 1 : 0)
                    + IsEnhancedCritMove(ctx->move)
                    + GetHoldEffectCritChanceIncrease(ctx->battlerAtk, ctx->holdEffectAtk)
                    + (ctx->abilityAtk == ABILITY_SUPER_LUCK ? 1 : 0);

        if (critChance >= ARRAY_COUNT(sCriticalHitChance))
            critChance = ARRAY_COUNT(sCriticalHitChance) - 1;
    }

    if (critChance != CRITICAL_HIT_BLOCKED && DoesTargetAbilityBlockCrit(ctx->battlerAtk, ctx->battlerDef, ctx->move, ctx->abilityDef))
    {
        // Record ability only if move had 100% chance to get a crit
        if (ctx->updateFlags)
        {
            if (critChance == CRITICAL_HIT_ALWAYS)
                RecordAbilityBattle(ctx->battlerDef, ctx->abilityDef);
            else if (GetCriticalHitOdds(critChance) == 1)
                RecordAbilityBattle(ctx->battlerDef, ctx->abilityDef);
        }
        critChance = CRITICAL_HIT_BLOCKED;
    }

    return critChance;
}

// Bulbapedia: https://bulbapedia.bulbagarden.net/wiki/Critical_hit#Generation_I
// Crit chance = Threshold / 256, Threshold maximum of 255
// Threshold = Base Speed / 2
// High crit move = 8 * (Base Speed / 2)
// Focus Energy = 4 * (Base Speed / 2)
s32 CalcCritChanceStageGen1(struct BattleContext *ctx)
{
    s32 critChance = 0;
    s32 moveCritStage = IsEnhancedCritMove(ctx->move);
    u32 holdEffectCritStage = GetHoldEffectCritChanceIncrease(ctx->battlerAtk, ctx->holdEffectAtk);
    u16 baseSpeed = GetSpeciesBaseSpeed(gBattleMons[ctx->battlerAtk].species);

    critChance = baseSpeed / 2;

    // Crit scaling
    if (moveCritStage > 0)
        critChance *= 8 * moveCritStage;


    if (gBattleMons[ctx->battlerAtk].volatiles.focusEnergy)
        critChance *= 4;
    else if (gBattleMons[ctx->battlerAtk].volatiles.dragonCheer)
        critChance *= 2;

    if (holdEffectCritStage > 0)
        critChance *= 4 * holdEffectCritStage;

    if (ctx->abilityAtk == ABILITY_SUPER_LUCK)
        critChance *= 4;

    if (critChance > 255)
        critChance = 255;

    // Prevented crits
    if (gSideStatuses[ctx->battlerDef] & SIDE_STATUS_LUCKY_CHANT)
        critChance = CRITICAL_HIT_BLOCKED;
    else if (ctx->abilityDef == ABILITY_BATTLE_ARMOR || ctx->abilityDef == ABILITY_SHELL_ARMOR)
    {
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerDef, ctx->abilityDef);
        critChance = CRITICAL_HIT_BLOCKED;
    }

    // Guaranteed crits
    else if (gBattleMons[ctx->battlerAtk].volatiles.laserFocus
             || MoveAlwaysCrits(ctx->move)
             || (ctx->abilityAtk == ABILITY_MERCILESS && gBattleMons[ctx->battlerDef].status1 & STATUS1_PSN_ANY))
    {
        critChance = CRITICAL_HIT_ALWAYS;
    }

    return critChance;
}

static bool32 IsCriticalHit(struct BattleContext *ctx)
{
    bool32 isCrit = FALSE;
    s32 critChance = 0;

    /*if (GetConfig(B_CRIT_CHANCE) == GEN_1)
        critChance = CalcCritChanceStageGen1(ctx);
    else*/
        critChance = CalcCritChanceStage(ctx);

    if (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE)
        isCrit = FALSE;
    else if (critChance == -1)
        isCrit = FALSE;
    else if (critChance == -2)
        isCrit = TRUE;
    else
    {
        /*if (GetConfig(B_CRIT_CHANCE) == GEN_1)
            isCrit = RandomChance(RNG_CRITICAL_HIT, critChance, 256);
        else if (GetConfig(B_CRIT_CHANCE) == GEN_2)
            isCrit = RandomChance(RNG_CRITICAL_HIT, GetCriticalHitOdds(critChance), 256);
        else*/
            isCrit = RandomChance(RNG_CRITICAL_HIT, 1, GetCriticalHitOdds(critChance));
    }

    gSpecialStatuses[ctx->battlerDef].criticalHit = isCrit;
    return isCrit;
}

s32 GetAdjustedDamage(struct BattleContext *ctx, s32 damage)
{
    if (DoesSubstituteBlockMove(ctx->battlerAtk, ctx->battlerDef, ctx->move)
     || DoesDisguiseBlockMove(ctx->battlerDef, ctx->move)
     || DoesIceFaceBlockMove(ctx->battlerDef, ctx->move))
        return damage; // No damage will be dealt

    if (gBattleMons[ctx->battlerDef].hp > damage)
        return damage;

    bool32 enduredHit = FALSE;
    u32 rand = Random() % 100;

    if (GetMoveEffect(ctx->move) == EFFECT_FALSE_SWIPE)
    {
        enduredHit = TRUE;
    }
    else if (gBattleMons[ctx->battlerDef].volatiles.endured)
    {
        enduredHit = TRUE;
        gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_ENDURED;
    }
    else if (ctx->holdEffectDef == HOLD_EFFECT_FOCUS_BAND && rand < GetBattlerHoldEffectParam(ctx->battlerDef))
    {
        enduredHit = TRUE;
        RecordItemEffectBattle(ctx->battlerDef, ctx->holdEffectDef);
        gLastUsedItem = gBattleMons[ctx->battlerDef].item;
        gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_HUNG_ON;
    }
    else if (GetConfig(B_STURDY) >= GEN_5 && ctx->abilityDef == ABILITY_STURDY && IsBattlerAtMaxHp(ctx->battlerDef))
    {
        enduredHit = TRUE;
        RecordAbilityBattle(ctx->battlerDef, ABILITY_STURDY);
        gLastUsedAbility = ABILITY_STURDY;
        gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_STURDIED;
    }
    else if (ctx->holdEffectDef == HOLD_EFFECT_FOCUS_SASH && IsBattlerAtMaxHp(ctx->battlerDef))
    {
        enduredHit = TRUE;
        RecordItemEffectBattle(ctx->battlerDef, ctx->holdEffectDef);
        gLastUsedItem = gBattleMons[ctx->battlerDef].item;
        gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_FOE_HUNG_ON;
    }

    if (enduredHit)
    {
        damage = gBattleMons[ctx->battlerDef].hp - 1; // Reduce damage to 1 hp.
        gProtectStructs[ctx->battlerDef].assuranceDoubled = TRUE;
    }

    return damage;
}

//previously got type set from GetBattleMoveType
//read certain move effects and set them to type mystery
//which is what made effects do typeless dmg
s32 CalculateMoveDamage(struct BattleContext *ctx)
{
    ctx->abilityAtk = GetBattlerAbility(ctx->battlerAtk);
    ctx->abilityDef = GetBattlerAbility(ctx->battlerDef);
    ctx->holdEffectAtk = GetBattlerHoldEffect(ctx->battlerAtk);
    ctx->holdEffectDef = GetBattlerHoldEffect(ctx->battlerDef);

    ctx->typeEffectivenessModifier = CalcTypeEffectivenessMultiplier(ctx);
    if (!ctx->isSelfInflicted)
        ctx->isCrit = IsCriticalHit(ctx);

    if (IsFutureSightAttackerInParty(ctx->battlerAtk, ctx->battlerDef, ctx->move))
        return DoFutureSightAttackDamageCalc(ctx);

    return DoMoveDamageCalc(ctx);
}

// for AI so that typeEffectivenessModifier, weather, abilities and holdEffects are calculated only once
s32 CalculateMoveDamageVars(struct BattleContext *ctx)
{
    return DoMoveDamageCalcVars(ctx);
}

static inline bool32 ActivateGenesectDownloadDefense(enum BattlerId battler)
{
    if (GetBaseFormSpecies(gBattleMons[battler].species) == SPECIES_GENESECT
    && GetBattlerHoldEffect(battler) == HOLD_EFFECT_DRIVE)
        return TRUE;

    return FALSE;
}

static inline bool32 ActivateArcuesMultiTypeDefense(enum BattlerId battler)
{
    if (GetBaseFormSpecies(gBattleMons[battler].species) == SPECIES_ARCEUS
    && GetBattlerHoldEffect(battler) == HOLD_EFFECT_PLATE)
        return TRUE;

    return FALSE;
}

static inline void MulByTypeEffectiveness(struct BattleContext *ctx, uq4_12_t *modifier, enum Type defType)
{
    uq4_12_t mod = GetTypeModifier(ctx->moveType, defType);
    uq4_12_t arceus_mod = UQ_4_12(5.0);

    //set unique modifier for arcues based on if def type was 
    //type of plate so don't have to actually change form
    //not done yet but need accout for def type and mod changes
    //but then again since I only want benefits
    //technically I'd ignore effects that would make you weaker
    //ok think should be simple think can safely ignore most things
    if (ActivateArcuesMultiTypeDefense(ctx->battlerDef))
        arceus_mod = GetTypeModifier(ctx->moveType, GetItemSecondaryId(gBattleMons[ctx->battlerDef].item));

    //don't have to worry about this for multi type
    //since already determined by hold effect
    if (mod == UQ_4_12(0.0) && ctx->holdEffectDef == HOLD_EFFECT_RING_TARGET)
    {
        mod = UQ_4_12(1.0);
        if (ctx->updateFlags)
            RecordItemEffectBattle(ctx->battlerDef, HOLD_EFFECT_RING_TARGET);
    }
    
    //change effects foresight and miracel eye slightly
    //rather than stating types to ignore
    //just set so whatever immunity is to block it
    //belive would need logic to prevent from doing so based on inverse type matchup
    //hmm actually no, keep that, makes it more useful
    //since I've added and remove no immunities from these types
    //functions effectively the same in base
    //still need update ability and move descriptions
    else if (/*(ctx->moveType == TYPE_FIGHTING || ctx->moveType == TYPE_NORMAL) &&*/ defType == TYPE_GHOST && gBattleMons[ctx->battlerDef].volatiles.foresight && mod == NO_EFFECT)
    {
        mod = UQ_4_12(1.0);
    }
    else if (/*(ctx->moveType == TYPE_FIGHTING || ctx->moveType == TYPE_NORMAL) &&*/ defType == TYPE_GHOST
        && (ctx->abilityAtk == ABILITY_SCRAPPY || ctx->abilityAtk == ABILITY_MINDS_EYE || ctx->abilityAtk == ABILITY_REIKI
        || (ctx->abilityAtk == ABILITY_PHANTOM_TOUCH && IsMoveMakingContact(ctx->battlerAtk, ctx->battlerDef, ctx->abilityAtk, ctx->holdEffectAtk, ctx->move))
        )
        && mod == NO_EFFECT)
    {
        mod = UQ_4_12(1.0);
        if (ctx->updateFlags)
            RecordAbilityBattle(ctx->battlerAtk, ctx->abilityAtk);
    }

    if (/*ctx->moveType == TYPE_PSYCHIC &&*/ defType == TYPE_DARK && gBattleMons[ctx->battlerDef].volatiles.miracleEye && mod == NO_EFFECT)
        mod = UQ_4_12(1.0);

    if (ctx->moveType == TYPE_FIGHTING && IsAirborneType(defType) 
    && IsBattlerGrounded(ctx->battlerDef, ctx->abilityDef, ctx->abilityAtk, ctx->holdEffectDef)
    && mod == NOT_VERY_EFFECTIVE)
        mod = UQ_4_12(1.0);

    //make exclusive for flying type only as for wind would remove its only weakness
    if (ctx->moveType == TYPE_ELECTRIC && defType == TYPE_FLYING 
    && IsBattlerGrounded(ctx->battlerDef, ctx->abilityDef, ctx->abilityAtk, ctx->holdEffectDef)
    && mod == NOT_VERY_EFFECTIVE)
        mod = UQ_4_12(1.0);

    //believe is things like freeze dry
    if (GetMoveEffect(ctx->move) == EFFECT_SUPER_EFFECTIVE_ON_ARG && defType == GetMoveArgType(ctx->move) && !ctx->isAnticipation)
        mod = SUPER_EFFECTIVE;
    //pretty sure don't need with other groud change
    /*if (ctx->moveType == TYPE_GROUND && IsAirborneType(defType) && IsBattlerGrounded(ctx->battlerDef, ctx->abilityDef, ctx->holdEffectDef) && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);*/
    if (ctx->moveType == TYPE_STELLAR && GetActiveGimmick(ctx->battlerDef) == GIMMICK_TERA)
        mod = SUPER_EFFECTIVE;

    // WEATHER_STRONG_WINDS weakens Super Effective moves against Flying-type Pokémon
    //now including wind type so effect will reduce dif types for each
    if (ctx->weather & WEATHER_STRONG_WINDS && !ctx->isAnticipation)
    {
        if (IsAirborneType(defType) && mod >= SUPER_EFFECTIVE)
            mod = UQ_4_12(1.0);
    }

    if (gSpecialStatuses[ctx->battlerDef].distortedTypeMatchups || (mod > UQ_4_12(0.0) && ShouldTeraShellDistortTypeMatchups(ctx->move, ctx->battlerDef, ctx->abilityDef)))
    {
        mod = NOT_VERY_EFFECTIVE;
        if (ctx->updateFlags)
        {
            RecordAbilityBattle(ctx->battlerDef, ctx->abilityDef);
            gSpecialStatuses[ctx->battlerDef].distortedTypeMatchups = TRUE;
            gSpecialStatuses[ctx->battlerDef].teraShellAbilityDone = TRUE;
        }
    }

    //if not arceus will always be true
    //should be no problems and can't be equal
    //and since arceues is type neutral 
    //should do what I want and only bring in 
    //resistances of type
    if (mod < arceus_mod)
        *modifier = uq4_12_multiply(*modifier, mod);
    else
        *modifier = uq4_12_multiply(*modifier, arceus_mod);
}

static inline void TryNoticeIllusionInTypeEffectiveness(enum Move move, enum Type moveType, enum BattlerId battlerAtk, enum BattlerId battlerDef, uq4_12_t resultingModifier, u32 illusionSpecies)
{
    // Check if the type effectiveness would've been different if the pokemon really had the types as the disguise.
    uq4_12_t presumedModifier = UQ_4_12(1.0);

    struct BattleContext ctx = {0};
    ctx.battlerAtk = battlerAtk;
    ctx.battlerDef = battlerDef;
    ctx.move = ctx.chosenMove = move;
    ctx.moveType = moveType;
    ctx.updateFlags = FALSE;
    ctx.abilityAtk = GetBattlerAbility(battlerAtk);
    ctx.abilityDef = ABILITY_ILLUSION;
    ctx.holdEffectAtk = GetBattlerHoldEffect(battlerAtk);
    ctx.holdEffectDef = GetBattlerHoldEffect(battlerDef);

    MulByTypeEffectiveness(&ctx, &presumedModifier, GetSpeciesPrimaryType(illusionSpecies));
    if (GetSpeciesPrimaryType(illusionSpecies))
        MulByTypeEffectiveness(&ctx, &presumedModifier, GetSpeciesSecondaryType(illusionSpecies));

    if (presumedModifier != resultingModifier)
        RecordAbilityBattle(ctx.battlerDef, ABILITY_ILLUSION);
}

void UpdateMoveResultFlags(uq4_12_t modifier, u16 *resultFlags)
{
    if (modifier == UQ_4_12(0.0))
    {
        *resultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        *resultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);
        gBattleStruct->blunderPolicy = FALSE; // Don't activate if missed
    }
    else if (modifier == UQ_4_12(1.0))
    {
        *resultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else if (modifier > UQ_4_12(1.0))
    {
        *resultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
        *resultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else //if (modifier < UQ_4_12(1.0))
    {
        *resultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        *resultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
}

//in progress vsonic
static inline uq4_12_t CalcTypeEffectivenessMultiplierInternal(struct BattleContext *ctx, uq4_12_t modifier)
{
    u32 illusionSpecies;
    enum Type types[3];
    GetBattlerTypes(ctx->battlerDef, FALSE, types);

    MulByTypeEffectiveness(ctx, &modifier, types[0]);
    if (types[1] != types[0])
        MulByTypeEffectiveness(ctx, &modifier, types[1]);
    if (types[2] != TYPE_MYSTERY && types[2] != types[1] && types[2] != types[0])
        MulByTypeEffectiveness(ctx, &modifier, types[2]);
    if (ctx->moveType == TYPE_FIRE && gBattleMons[ctx->battlerDef].volatiles.tarShot)
        modifier = uq4_12_multiply(modifier, SUPER_EFFECTIVE);

    if (ctx->moveType == GetItemSecondaryId(gBattleMons[ctx->battlerDef].item)
    && ActivateGenesectDownloadDefense(ctx->battlerDef))
        modifier = uq4_12_multiply(modifier, NOT_VERY_EFFECTIVE);
    

    if (ctx->updateFlags && (illusionSpecies = GetIllusionMonSpecies(ctx->battlerDef)))
        TryNoticeIllusionInTypeEffectiveness(ctx->move, ctx->moveType, ctx->battlerAtk, ctx->battlerDef, modifier, illusionSpecies);

    if (GetMoveCategory(ctx->move) == DAMAGE_CATEGORY_STATUS && ctx->move != MOVE_THUNDER_WAVE)
    {
        modifier = UQ_4_12(1.0);
        if (ctx->move == MOVE_GLARE && DoesBattlerGetTypeBasedAffinity(ctx->abilityAtk, ctx->battlerDef, ctx->abilityDef, TYPE_GHOST, FALSE))
            modifier = UQ_4_12(0.0);
    }

    //need test hopefully works right
    //meant to allow no gurad to bypass ground miss
    //since they can already hit through semi invulnerable
    else if (IsFloatingTargetImmunetoGroundBasedMoves(ctx->battlerDef, ctx->abilityAtk, ctx->abilityDef, ctx->move) 
    && !IsBattlerGroundedInverseCheck(ctx->battlerDef, ctx->abilityDef, ctx->abilityAtk, ctx->holdEffectDef, INVERSE_BATTLE, ctx->isAnticipation) 
    )
    {
        modifier = UQ_4_12(0.0);
        
        if (ctx->updateFlags /*&& ctx->abilityDef == ABILITY_LEVITATE*/)
        {
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            //gLastUsedAbility = ABILITY_LEVITATE;
            gLastLandedMoves[ctx->battlerDef] = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_GROUND_MISS;
            //RecordAbilityBattle(ctx->battlerDef, ABILITY_LEVITATE);
        }//think is right
        
    }
    else if (GetMoveEffect(ctx->move) == EFFECT_SHEER_COLD 
    && DoesBattlerGetTypeBasedAffinity(ctx->abilityAtk, ctx->battlerDef, ctx->abilityDef, TYPE_ICE, FALSE))
    {
        modifier = UQ_4_12(0.0);
    }

    // Thousand Arrows ignores type modifiers for flying mons
    /*if (MoveIgnoresTypeIfFlyingAndUngrounded(ctx->move)
     && !IsBattlerGrounded(ctx->battlerDef, ctx->abilityDef, ctx->holdEffectDef)
     && IS_BATTLER_OF_TYPE(ctx->battlerDef, TYPE_FLYING))
    {
        modifier = UQ_4_12(1.0);
    }*/

    // Iron Ball ignores type modifiers for flying-type mons if it is the only source of grounding
    //think don't need this wrapped in grouded
    /*if (B_IRON_BALL >= GEN_5
        && ctx->moveType == TYPE_GROUND
        && ctx->holdEffectDef == HOLD_EFFECT_IRON_BALL
        && IS_BATTLER_OF_TYPE(ctx->battlerDef, TYPE_FLYING)
        && !IsBattlerGrounded(ctx->battlerDef, ctx->abilityDef, HOLD_EFFECT_NONE) // We want to ignore Iron Ball so skip item check
        && !FlagGet(B_FLAG_INVERSE_BATTLE))
    {
        modifier = UQ_4_12(1.0);
    }*/

    if (((ctx->abilityDef == ABILITY_WONDER_GUARD && modifier <= UQ_4_12(1.0))
    || (ctx->abilityDef == ABILITY_DISPIRIT_GUARD && modifier >= UQ_4_12(1.0))
        || (ctx->abilityDef == ABILITY_TELEPATHY && ctx->battlerDef == BATTLE_PARTNER(ctx->battlerAtk)))
        && GetMovePower(ctx->move) != 0)
    {
        modifier = UQ_4_12(0.0);
        ctx->abilityBlocked = TRUE;
        if (ctx->updateFlags)
        {
            gLastUsedAbility = ctx->abilityDef;
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_MISSED;
            RecordAbilityBattle(ctx->battlerDef, gBattleMons[ctx->battlerDef].ability);
        }
    }

    //why do I keep mixing these up
    //this is supposed to be ocean memory
    //ok vsonic removed gBattleStruct->missStringId[ctx->battlerDef]
    //can't remember if I made that and for what purpose
    //I "think" MAYBE it was for multi hit miss stuff
    //idk its not on master can't really identify it from comparison repo smh
    if ((ctx->abilityDef == ABILITY_OCEAN_MEMORY && ctx->moveType == TYPE_WATER)
        && GetBattleMoveCategory(ctx->move) != DAMAGE_CATEGORY_STATUS)
    {
        modifier = UQ_4_12(0.0);
        if (ctx->updateFlags)
        {
            gLastUsedAbility = ctx->abilityDef;
            ctx->abilityBlocked = TRUE;
            gBattleStruct->moveResultFlags[ctx->battlerDef] |= MOVE_RESULT_MISSED;
            gLastLandedMoves[ctx->battlerDef] = 0;
            PREPARE_TYPE_BUFFER(gBattleTextBuff1, ctx->moveType);
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_ABILITY_TYPE_MISS;
            RecordAbilityBattle(ctx->battlerDef, gBattleMons[ctx->battlerDef].ability);
        }
    }

    //if (ctx->updateFlags)
    //    TryInitializeFirstSTABMoveTrainerSlide(ctx->battlerDef, ctx->battlerAtk, ctx->moveType);

    return modifier;
}

uq4_12_t CalcTypeEffectivenessMultiplier(struct BattleContext *ctx)
{
    uq4_12_t modifier = UQ_4_12(1.0);

    if (ctx->move != MOVE_STRUGGLE && ctx->moveType != TYPE_SOUND && ctx->moveType != TYPE_MYSTERY
    && !MoveDoesTypelessDmg(ctx->move))
    {
        modifier = CalcTypeEffectivenessMultiplierInternal(ctx, modifier);

        //vsonic unusre bout this why anticipation can't sense this?
        if (GetMoveEffect(ctx->move) == EFFECT_TWO_TYPED_MOVE && !ctx->isAnticipation)
        {
            ctx->moveType = GetTwoTypedMove2ndType(ctx->move);
            modifier = CalcTypeEffectivenessMultiplierInternal(ctx, modifier);
        }
    }

    if (ctx->updateFlags)
        UpdateMoveResultFlags(modifier, &gBattleStruct->moveResultFlags[ctx->battlerDef]);
    return modifier;
}

//unsure what this does only clue find is its used in battle ai for some reason
uq4_12_t CalcPartyMonTypeEffectivenessMultiplier(enum Move move, u16 speciesDef, enum Ability abilityDef)
{
    uq4_12_t modifier = UQ_4_12(1.0);
    enum Type moveType = GetBattleMoveType(move);

    if (move != MOVE_STRUGGLE && moveType != TYPE_MYSTERY)
    {
        struct BattleContext ctx = {0};
        ctx.move = ctx.chosenMove = move;
        ctx.moveType = moveType;
        ctx.updateFlags = FALSE;
        ctx.abilityDef = abilityDef;

        MulByTypeEffectiveness(&ctx, &modifier, GetSpeciesPrimaryType(speciesDef));
        if (GetSpeciesPrimaryType(speciesDef))
            MulByTypeEffectiveness(&ctx, &modifier, GetSpeciesSecondaryType(speciesDef));
        //very weird in that this doesnt check hold effects at all
        if (ctx.moveType == TYPE_GROUND && IsFloatingSpecies(speciesDef) && !(gFieldStatuses & STATUS_FIELD_GRAVITY))
            modifier = UQ_4_12(0.0);
        if ((abilityDef == ABILITY_WONDER_GUARD && modifier <= UQ_4_12(1.0))
        || (abilityDef == ABILITY_DISPIRIT_GUARD && modifier >= UQ_4_12(1.0)) 
        && GetMovePower(move) != 0)
            modifier = UQ_4_12(0.0);
    }

    return modifier;
}

//vsonic need double check but believe I adjusted this
//intead of immune becoming super it becomes neutral
//and neutral becomes immune?
static uq4_12_t GetInverseTypeMultiplier(uq4_12_t multiplier)
{
    switch (multiplier)
    {
    case UQ_4_12(0.0):
        return UQ_4_12(1.0);
    case UQ_4_12(0.5):
        return UQ_4_12(1.55);
    case UQ_4_12(1.55):
        return UQ_4_12(0.5);
    case UQ_4_12(1.0):
    default:
        return UQ_4_12(0.0);
    }
}//unsure if default matters here

uq4_12_t GetOverworldTypeEffectiveness(struct Pokemon *mon, enum Type moveType)
{
    uq4_12_t modifier = UQ_4_12(1.0);

    if (moveType == TYPE_MYSTERY)
        return modifier;


    struct BattleContext ctx = {0};
    ctx.abilityDef = GetMonAbility(mon);
    ctx.move = ctx.chosenMove = MOVE_POUND;
    ctx.moveType = moveType;
    ctx.updateFlags = FALSE;

    u32 speciesDef = GetMonData(mon, MON_DATA_SPECIES);
    enum Type type1 = GetSpeciesPrimaryType(speciesDef);
    enum Type type2 = GetSpeciesSecondaryType(speciesDef);

    MulByTypeEffectiveness(&ctx, &modifier, type1);
    if (type2 != type1)
        MulByTypeEffectiveness(&ctx, &modifier, type2);

    if ((modifier <= UQ_4_12(1.0) && ctx.abilityDef == ABILITY_WONDER_GUARD)
     || CanAbilityAbsorbMove(&ctx))
        modifier = UQ_4_12(0.0);

    return modifier;
}

uq4_12_t GetTypeModifier(enum Type atkType, enum Type defType)
{
    if (B_FLAG_INVERSE_BATTLE != 0 && FlagGet(B_FLAG_INVERSE_BATTLE))
        return GetInverseTypeMultiplier(gTypeEffectivenessTable[atkType][defType]);
    return gTypeEffectivenessTable[atkType][defType];
}

//done
s32 GetStealthHazardDamageByTypesAndHP(enum TypeSideHazard hazardType, enum Type type1, enum Type type2, u32 maxHp)
{
    s32 dmg = 0;
    uq4_12_t modifier = UQ_4_12(1.0);

    modifier = uq4_12_multiply(modifier, GetTypeModifier((u8)hazardType, type1));
    if (type2 != type1)
        modifier = uq4_12_multiply(modifier, GetTypeModifier((u8)hazardType, type2));

    switch (modifier)
    {
    case UQ_4_12(0.0):
        dmg = 0;
        break;
    case UQ_4_12(0.25):
        dmg = max(maxHp / 32, 1);
        break;
    case UQ_4_12(0.5):
        dmg = max(maxHp / 16, 1);
        break;
    case UQ_4_12(1.0):
    default:
        dmg = max(maxHp / 8, 1);
        break;
    /*case UQ_4_12(2.0):
        dmg = maxHp / 4;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(4.0):
        dmg = maxHp / 2;
        if (dmg == 0)
            dmg = 1;
        break;*/
    }

    //realized needed default as super and resisted is no longer neutral
    //this outside conditional will handle everything else
    if (modifier > UQ_4_12(1.0))
    {
        dmg = max(maxHp / 6, 1);//had at 5 change to 6 so super gives extra 50% of base effect
    }

    return dmg;
}

s32 GetStealthHazardDamage(enum TypeSideHazard hazardType, enum BattlerId battler)
{
    enum Type types[3];
    GetBattlerTypes(battler, FALSE, types);
    u32 maxHp = gBattleMons[battler].maxHP;

    return GetStealthHazardDamageByTypesAndHP(hazardType, types[0], types[1], maxHp);
}

bool32 IsPartnerMonFromSameTrainer(enum BattlerId battler)
{
    if (!IsOnPlayerSide(battler))
        return !(gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS);
    else
        return !(gBattleTypeFlags & BATTLE_TYPE_MULTI);
}

//vsonic just merge in form change branch 
//making such a big change no reason to keep it separate
//think will leave primal reversion separte
//so rayquaza stays special plus they already have broken ability
bool32 DoesSpeciesUseHoldItemToChangeForm(u16 species, u16 heldItemId)
{
    u32 i;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        enum FormChanges method = formChanges[i].method;
        switch (method)
        {
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
        case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
        case FORM_CHANGE_BATTLE_ULTRA_BURST:
        case FORM_CHANGE_ITEM_HOLD:
        case FORM_CHANGE_BEGIN_BATTLE:
            if (formChanges[i].param1 == heldItemId)
                return TRUE;
            break;
        default:
            break;
        }
    }
    return FALSE;
}

bool32 CanMegaEvolve(enum BattlerId battler)
{
    enum HoldEffect holdEffect = GetBattlerHoldEffectIgnoreNegation(battler);

    // Check if Player has a Mega Ring.
    if (!TESTING
        && (GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT))
        && !CheckBagHasItem(ITEM_MEGA_RING, 1))
        return FALSE;

    // Check if Trainer has already Mega Evolved.
    if (HasTrainerUsedGimmick(battler, GIMMICK_MEGA))
        return FALSE;

    // Check if battler has another gimmick active.
    if (GetActiveGimmick(battler) != GIMMICK_NONE)
        return FALSE;

    // Check if battler is currently held by Sky Drop.
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return FALSE;

    // Check if battler is holding a Z-Crystal.
    if (holdEffect == HOLD_EFFECT_Z_CRYSTAL)
        return FALSE;

    enum Ability ability = GetBattlerAbility(battler);

    // Check if there is an entry in the form change table for regular Mega Evolution and battler is holding Mega Stone.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM, ability) != gBattleMons[battler].species)
        return TRUE;

    // Check if there is an entry in the form change table for Wish Mega Evolution.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE, ability) != gBattleMons[battler].species)
        return TRUE;

    // No checks passed, the mon CAN'T mega evolve.
    return FALSE;
}

bool32 CanUltraBurst(enum BattlerId battler)
{
    enum HoldEffect holdEffect = GetBattlerHoldEffectIgnoreNegation(battler);

    // Check if Player has a Z-Ring
    if (!TESTING && (GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT
        || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT))
        && !CheckBagHasItem(ITEM_Z_POWER_RING, 1))
        return FALSE;

    // Check if Trainer has already Ultra Bursted.
    if (HasTrainerUsedGimmick(battler, GIMMICK_ULTRA_BURST))
        return FALSE;

    // Check if battler has another gimmick active.
    if (GetActiveGimmick(battler) != GIMMICK_NONE)
        return FALSE;

    // Check if mon is currently held by Sky Drop
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return FALSE;

    enum Ability ability = GetBattlerAbility(battler);

    // Check if there is an entry in the form change table for Ultra Burst and battler is holding a Z-Crystal.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_ULTRA_BURST, ability) != gBattleMons[battler].species && holdEffect == HOLD_EFFECT_Z_CRYSTAL)
        return TRUE;

    // No checks passed, the mon CAN'T ultra burst.
    return FALSE;
}

void ActivateMegaEvolution(enum BattlerId battler)
{
    enum Ability ability = GetBattlerAbility(battler);
    gLastUsedItem = gBattleMons[battler].item;
    SetActiveGimmick(battler, GIMMICK_MEGA);
    SetGimmickAsActivated(battler, GIMMICK_MEGA);

    if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE, ability))
    {
        BattleScriptPushCursorAndCallback(BattleScript_WishMegaEvolution);
    }
    else
    {
        TryBattleFormChange(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM, ability);
        BattleScriptPushCursorAndCallback(BattleScript_MegaEvolution);
    }
}

void ActivateUltraBurst(enum BattlerId battler)
{
    enum Ability ability = GetBattlerAbility(battler);
    gLastUsedItem = gBattleMons[battler].item;
    SetActiveGimmick(battler, GIMMICK_ULTRA_BURST);
    SetGimmickAsActivated(battler, GIMMICK_ULTRA_BURST);
    TryBattleFormChange(battler, FORM_CHANGE_BATTLE_ULTRA_BURST, ability);
    BattleScriptPushCursorAndCallback(BattleScript_UltraBurst);
}

bool32 IsBattlerMegaEvolved(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Mega Evolution.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isMegaEvolution);
}

bool32 IsBattlerPrimalReverted(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Primal Revesion.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isPrimalReversion);
}

bool32 IsBattlerUltraBursted(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Ultra Burst.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isUltraBurst);
}

bool32 IsBattlerInTeraForm(enum BattlerId battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as a true Tera Form.
    if (gBattleMons[battler].volatiles.transformed)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].isTeraForm);
}

u32 GetBattleFormChangeTargetSpecies(enum BattlerId battler, enum FormChanges method, enum Ability ability)
{
    u32 species = gBattleMons[battler].species;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    if (formChanges == NULL)
        return species;

    struct FormChangeContext ctx =
    {
        .method = method,
        .currentSpecies = gBattleMons[battler].species,
        .heldItem = gBattleMons[battler].item,
        .ability = ability,
        .status = gBattleMons[battler].status1,
        .gmaxFactor = GetMonData(GetBattlerMon(battler), MON_DATA_GIGANTAMAX_FACTOR),
        .hp = ability == ABILITY_GULP_MISSILE ? gBattleStruct->passiveHpUpdate[battler] : gBattleMons[battler].hp,
        .maxHP = gBattleMons[battler].maxHP,
        .teraType = GetBattlerTeraType(battler),
        .level = gBattleMons[battler].level,
    };

    for (u32 i = 0; i < MAX_MON_MOVES; i++)
        ctx.moves[i] = gBattleMons[battler].moves[i];

    if (ability == ABILITY_GULP_MISSILE)
        gBattleStruct->passiveHpUpdate[battler] = 0;

    return GetFormChangeTargetSpecies_Internal(ctx);
}

static bool32 CanBattlerFormChange(enum BattlerId battler, enum FormChanges method)
{
    // Can't change form if transformed.
    if (gBattleMons[battler].volatiles.transformed
        && B_TRANSFORM_FORM_CHANGES >= GEN_5)
        return FALSE;

    switch (method)
    {
    case FORM_CHANGE_END_BATTLE:
        if (IsBattlerPrimalReverted(battler))
            return TRUE;
        // Fallthrough
    case FORM_CHANGE_FAINT:
        if (IsBattlerMegaEvolved(battler) || IsBattlerUltraBursted(battler) || IsBattlerInTeraForm(battler) || IsGigantamaxed(battler))
            return TRUE;
        break;
    case FORM_CHANGE_BATTLE_SWITCH_OUT:
        if (IsGigantamaxed(battler))
            return TRUE;
        else if (GetActiveGimmick(battler) == GIMMICK_TERA && DoesSpeciesHaveFormChangeMethod(gBattleMons[battler].species, FORM_CHANGE_BATTLE_TURN_END))
            return FALSE;
        break;
    case FORM_CHANGE_BATTLE_TURN_END:
        if (GetActiveGimmick(battler) == GIMMICK_TERA)
            return FALSE;
        break;
    default:
        break;
    }
    return DoesSpeciesHaveFormChangeMethod(gBattleMons[battler].species, method);
}

bool32 TryRevertPartyMonFormChange(u32 partyIndex)
{
     bool32 changedForm = FALSE;

    // Appeared in battle and didn't faint
    if (gBattleStruct->partyState[B_SIDE_PLAYER][partyIndex].sentOut && GetMonData(&gPlayerParty[partyIndex], MON_DATA_HP) != 0)
        changedForm = TryFormChange(&gPlayerParty[partyIndex], FORM_CHANGE_END_BATTLE_ENVIRONMENT);

    if (!changedForm)
        changedForm = TryFormChange(&gPlayerParty[partyIndex], FORM_CHANGE_END_BATTLE);

    // Clear original species field
    gBattleStruct->partyState[B_SIDE_PLAYER][partyIndex].changedSpecies = SPECIES_NONE;

    return changedForm;
}

bool32 TryBattleFormChange(enum BattlerId battler, enum FormChanges method, enum Ability ability)
{
    struct Pokemon *mon = GetBattlerMon(battler);

    if (!CanBattlerFormChange(battler, method))
        return FALSE;

    u32 currentSpecies = GetMonData(mon, MON_DATA_SPECIES);
    u32 targetSpecies = GetBattleFormChangeTargetSpecies(battler, method, ability);

    struct PartyState *battlePartyState = GetBattlerPartyState(battler);
    // If the battle ends, and there's not a specified species to change back to,
    // use the species at the start of the battle.
    if (targetSpecies == SPECIES_NONE
        && battlePartyState != NULL && battlePartyState->changedSpecies != SPECIES_NONE
        // This is added to prevent FORM_CHANGE_END_BATTLE_ENVIRONMENT from omitting move changes
        // at the end of the battle, as it was being counting as a successful form change.
        && (method == FORM_CHANGE_END_BATTLE || method == FORM_CHANGE_FAINT))
    {
        targetSpecies = battlePartyState->changedSpecies;
    }

    assertf(targetSpecies != SPECIES_NONE, "form change target returned NONE. cur:%d, method:%d", currentSpecies, method)
    {
        return FALSE;
    }

    if (targetSpecies != currentSpecies)
    {
        // Saves the original species on the first form change.
        if (GetBattlerPartyState(battler)->changedSpecies == SPECIES_NONE)
            GetBattlerPartyState(battler)->changedSpecies = gBattleMons[battler].species;

        TryToSetBattleFormChangeMoves(mon, method);
        SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
        gBattleMons[battler].species = targetSpecies;
        RecalcBattlerStats(battler, mon, FALSE);
        return TRUE;
    }

    return FALSE;
}

bool32 DoBattlersShareType(enum BattlerId battler1, enum BattlerId battler2)
{
    s32 i;
    enum Type battler1types[3], battler2types[3];
    GetBattlerTypes(battler1, FALSE, battler1types);
    GetBattlerTypes(battler2, FALSE, battler2types);

    if (battler1types[2] == TYPE_MYSTERY)
        battler1types[2] = battler1types[0];

    if (battler2types[2] == TYPE_MYSTERY)
        battler2types[2] = battler2types[0];

    for (i = 0; i < 3; i++)
    {
        if (battler1types[i] == battler2types[0] || battler1types[i] == battler2types[1] 
        || battler1types[i] == battler2types[2])
            return TRUE;
    }

    return FALSE;
}

bool32 CanBattlerGetOrLoseItem(u32 fromBattler, enum BattlerId battler, u16 itemId)
{
    u16 species = gBattleMons[fromBattler].species;
    enum HoldEffect holdEffect = GetItemHoldEffect(itemId); // Raw hold effect

    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
        return FALSE;
    else if (DoesSpeciesUseHoldItemToChangeForm(species, itemId))
        return FALSE;
    else if (holdEffect == HOLD_EFFECT_Z_CRYSTAL)
        return FALSE;
    else if (holdEffect == HOLD_EFFECT_BOOSTER_ENERGY
         && (gSpeciesInfo[gBattleMons[fromBattler].species].isParadox || gSpeciesInfo[gBattleMons[battler].species].isParadox))
        return FALSE;
    else
        return TRUE;
}

u32 GetBattlerVisualSpecies(enum BattlerId battler)
{
    u32 illusionSpecies = GetIllusionMonSpecies(battler);
    if (illusionSpecies != SPECIES_NONE)
        return illusionSpecies;
    return gBattleMons[battler].species;
}

bool32 TryClearIllusion(enum BattlerId battler, enum Ability ability)
{
    if (gBattleStruct->illusion[battler].state != ILLUSION_ON)
        return FALSE;
    if (ability == ABILITY_ILLUSION && IsBattlerAlive(battler))
        return FALSE;

    gBattleScripting.battler = battler;
    BattleScriptCall(BattleScript_IllusionOff);
    return TRUE;
}

struct Pokemon *GetIllusionMonPtr(enum BattlerId battler)
{
    if (gBattleStruct->illusion[battler].state == ILLUSION_NOT_SET)
        SetIllusionMon(GetBattlerMon(battler), battler);
    if (gBattleStruct->illusion[battler].state != ILLUSION_ON)
        return NULL;

    return gBattleStruct->illusion[battler].mon;
}

void ClearIllusionMon(enum BattlerId battler)
{
    memset(&gBattleStruct->illusion[battler], 0, sizeof(gBattleStruct->illusion[battler]));
}

u32 GetIllusionMonSpecies(enum BattlerId battler)
{
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    if (illusionMon != NULL)
        return GetMonData(illusionMon, MON_DATA_SPECIES);
    return SPECIES_NONE;
}

u32 GetIllusionMonPartyId(struct Pokemon *party, struct Pokemon *mon, struct Pokemon *partnerMon, enum BattlerId battler)
{
    s32 partyEnd=6;
    s32 partyStart=0;

    // Adjust party search range for Multibattles and Player vs two-trainers
    if ((GetBattlerSide(battler) == B_SIDE_PLAYER && (gBattleTypeFlags & BATTLE_TYPE_MULTI))
        || (GetBattlerSide(battler) == B_SIDE_OPPONENT && (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)))
        {
            if ((GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT) || (GetBattlerPosition(battler) == B_POSITION_OPPONENT_LEFT))
            {
                partyEnd = 3;
                partyStart = 0;
            }
            else
            {
                partyEnd = 6;
                partyStart = 3;
            }
        }

    // Find last alive non-egg pokemon.
    for (s32 id = partyEnd - 1; id >= partyStart; id--)
    {
        if (GetMonData(&party[id], MON_DATA_SANITY_HAS_SPECIES)
            && GetMonData(&party[id], MON_DATA_HP)
            && !GetMonData(&party[id], MON_DATA_IS_EGG))
        {
            u32 species = GetMonData(&party[id], MON_DATA_SPECIES);
            if (species == SPECIES_TERAPAGOS_STELLAR || (species >= SPECIES_OGERPON_TEAL_MASK_TERA && species <= SPECIES_OGERPON_CORNERSTONE_MASK_TERA))
                continue;
            if (&party[id] != mon && &party[id] != partnerMon)
                return id;
            else // If this pokemon or its partner is last in the party, ignore Illusion.
                return PARTY_SIZE;
        }
    }
    return PARTY_SIZE;
}

bool32 SetIllusionMon(struct Pokemon *mon, enum BattlerId battler)
{
    struct Pokemon *party, *partnerMon;
    u32 id;

    gBattleStruct->illusion[battler].state = ILLUSION_OFF;
    if (GetMonAbility(mon) != ABILITY_ILLUSION)
        return FALSE;

    party = GetBattlerParty(battler);

    if (IsBattlerAlive(BATTLE_PARTNER(battler)))
        partnerMon = &party[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]];
    else
        partnerMon = mon;

    id = GetIllusionMonPartyId(party, mon, partnerMon, battler);
    if (id != PARTY_SIZE)
    {
        gBattleStruct->illusion[battler].state = ILLUSION_ON;
        gBattleStruct->illusion[battler].mon = &party[id];
        return TRUE;
    }

    return FALSE;
}

u32 TryImmunityAbilityHealStatus(enum BattlerId battler)
{
    u32 effect = 0;
    switch (GetBattlerAbilityIgnoreMoldBreaker(battler))
    {
    case ABILITY_IMMUNITY:
    case ABILITY_PASTEL_VEIL:
        if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON))
        {
            StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
            effect = 1;
        }
        break;
    case ABILITY_OWN_TEMPO:
        if (gBattleMons[battler].volatiles.confusionTurns > 0)
        {
            StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
            effect = 2;
        }
        break;
    case ABILITY_LIMBER:
        if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
        {
            StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
            effect = 1;
        }
        break;
    case ABILITY_INSOMNIA:
    case ABILITY_VITAL_SPIRIT:
        if (gBattleMons[battler].status1 & STATUS1_SLEEP)
        {
            TryDeactivateSleepClause(GetBattlerSide(battler), gBattlerPartyIndexes[battler]);
            gBattleMons[battler].volatiles.nightmare = FALSE;
            StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
            effect = 1;
        }
        break;
    case ABILITY_WATER_VEIL:
    case ABILITY_WATER_BUBBLE:
    case ABILITY_THERMAL_EXCHANGE:
        if (gBattleMons[battler].status1 & STATUS1_BURN)
        {
            StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
            effect = 1;
        }
        break;
    case ABILITY_MAGMA_ARMOR:
        if (gBattleMons[battler].status1 & (STATUS1_FREEZE | STATUS1_FROSTBITE))
        {
            StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
            effect = 1;
        }
        break;
    case ABILITY_FEMME_FATALE:
    case ABILITY_OBLIVIOUS:
        if (gBattleMons[battler].volatiles.infatuatedwithMon)
            effect = 3;
        //add torment to this double check oblivious effect
        else if (GetConfig(B_OBLIVIOUS_TAUNT) >= GEN_6 && gBattleMons[battler].volatiles.tauntTimer != 0)
            effect = 4;
        break;
    }

    if (effect != 0)
    {
        switch (effect)
        {
        case 1: // status cleared
            gBattleMons[battler].status1 = 0;
            ClearPartyStateStatusTimers(battler);
            BattleScriptCall(BattleScript_AbilityCuredStatus);
            break;
        case 2: // get rid of confusion
            RemoveConfusionStatus(battler);
            BattleScriptCall(BattleScript_AbilityCuredStatus);
            break;
        case 3: // get rid of infatuation
            gBattleMons[battler].volatiles.infatuatedwithMon = 0;
            BattleScriptCall(BattleScript_AbilityCuredStatus);
            break;
        case 4: // get rid of taunt
            gBattleMons[battler].volatiles.tauntTimer = 0;
            BattleScriptCall(BattleScript_AbilityCuredStatus);
            break;
        }

        gBattleScripting.battler = gBattlerAbility = battler;
        BtlController_EmitSetMonData(battler, B_COMM_TO_CONTROLLER, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
        MarkBattlerForControllerExec(battler);
        return effect;
    }

    return 0;
}

uq4_12_t GetBadgeBoostModifier(void)
{
    if (GetConfig(B_BADGE_BOOST) < GEN_3)
        return UQ_4_12(1.125);
    else
        return UQ_4_12(1.1);
}

bool32 ShouldGetStatBadgeBoost(u16 badgeFlag, enum BattlerId battler)
{
    if (GetConfig(B_BADGE_BOOST) <= GEN_3 && badgeFlag != 0)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_FRONTIER))
            return FALSE;
        else if (!IsOnPlayerSide(battler))
            return FALSE;
        else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && TRAINER_BATTLE_PARAM.opponentA == TRAINER_SECRET_BASE)
            return FALSE;
        else if (FlagGet(badgeFlag))
            return TRUE;
    }
    return FALSE;
}

static enum DamageCategory SwapMoveDamageCategory(enum Move move)
{
    if (GetMoveCategory(move) == DAMAGE_CATEGORY_PHYSICAL)
        return DAMAGE_CATEGORY_SPECIAL;
    return DAMAGE_CATEGORY_PHYSICAL;
}

/*
    The Global States gBattleStruct->categoryOverride and gBattleStruct->swapDamageCategory
    can be removed but a lot of function arguments (battlerAtk and battlerDef) have to be added for this, about 50+.
    This is potentially a good change because it is less likely to cause bugs in the future.
*/
enum DamageCategory GetBattleMoveCategory(enum Move move)
{
    if (gMain.inBattle)
    {
        if (gBattleStruct->swapDamageCategory) // Photon Geyser, Shell Side Arm, Light That Burns the Sky, Tera Blast
            return SwapMoveDamageCategory(move);
        if (IsZMove(move) || IsMaxMove(move)) // TODO: Might be buggy depending on when this is called.
            return gBattleStruct->categoryOverride;
        if (IsBattleMoveStatus(move))
            return DAMAGE_CATEGORY_STATUS;
    }

    //if (B_PHYSICAL_SPECIAL_SPLIT < GEN_4)
    //    return gTypesInfo[GetBattleMoveType(move)].damageCategory;

    return GetMoveCategory(move);
}

void SetDynamicMoveCategory(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_HIDDEN_POWER:
    case EFFECT_STAT_BASED_SPLIT:
    case EFFECT_PHOTON_GEYSER:
        gBattleStruct->swapDamageCategory = (GetCategoryBasedOnStats(battlerAtk, battlerDef, move) != GetMoveCategory(move));
        break;
    case EFFECT_SHELL_SIDE_ARM:
        if (gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] == DAMAGE_CATEGORY_PHYSICAL)
            gBattleStruct->swapDamageCategory = TRUE;
        break;
    case EFFECT_TERA_BLAST:
        if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA)
            gBattleStruct->swapDamageCategory = GetCategoryBasedOnStats(battlerAtk, battlerDef, move) == DAMAGE_CATEGORY_PHYSICAL;
        break;
    case EFFECT_TERA_STARSTORM:
        if (GetActiveGimmick(battlerAtk) == GIMMICK_TERA && GET_BASE_SPECIES_ID(GetMonData(GetBattlerMon(battlerAtk), MON_DATA_SPECIES)) == SPECIES_TERAPAGOS)
            gBattleStruct->swapDamageCategory = GetCategoryBasedOnStats(battlerAtk, battlerDef, move) == DAMAGE_CATEGORY_PHYSICAL;
        break;
    default:
        gBattleStruct->swapDamageCategory = FALSE;
        break;
    }
}

static bool32 TryRemoveScreens(enum BattlerId battler)
{
    bool32 removed = FALSE;
    enum BattleSide battlerSide = GetBattlerSide(battler);
    enum BattleSide enemySide = GetBattlerSide(BATTLE_OPPOSITE(battler));

    // try to remove from battler's side
    if (gSideStatuses[battlerSide] & SIDE_STATUS_SCREEN_ANY)
    {
        gSideStatuses[battlerSide] &= ~SIDE_STATUS_SCREEN_ANY;
        removed = TRUE;
    }

    // try to remove from battler opponent's side
    if (gSideStatuses[enemySide] & SIDE_STATUS_SCREEN_ANY)
    {
        gSideStatuses[enemySide] &= ~SIDE_STATUS_SCREEN_ANY;
        removed = TRUE;
    }

    return removed;
}

// Photon Geyser, Light That Burns the Sky, Tera Blast
enum DamageCategory GetCategoryBasedOnStats(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    u32 attack = gBattleMons[battlerAtk].attack;
    u32 spAttack = gBattleMons[battlerAtk].spAttack;

    u32 defense = gBattleMons[battlerAtk].defense;
    u32 spDefense = gBattleMons[battlerAtk].spDefense;

    attack = attack * gStatStageRatios[gBattleMons[battlerAtk].statStages[STAT_ATK]][0];
    attack = attack / gStatStageRatios[gBattleMons[battlerAtk].statStages[STAT_ATK]][1];

    spAttack = spAttack * gStatStageRatios[gBattleMons[battlerAtk].statStages[STAT_SPATK]][0];
    spAttack = spAttack / gStatStageRatios[gBattleMons[battlerAtk].statStages[STAT_SPATK]][1];

    defense = defense * gStatStageRatios[gBattleMons[battlerDef].statStages[STAT_DEF]][0];
    defense = defense / gStatStageRatios[gBattleMons[battlerDef].statStages[STAT_DEF]][1];

    spDefense = spDefense * gStatStageRatios[gBattleMons[battlerDef].statStages[STAT_SPDEF]][0];
    spDefense = spDefense / gStatStageRatios[gBattleMons[battlerDef].statStages[STAT_SPDEF]][1];

    if ((spAttack < attack || GetBattlerAbility(battlerAtk) == ABILITY_MUSCLE_MAGIC)
    || (spAttack == attack && GetBattlerMoveTargetType(gBattlerAttacker, move) == TARGET_SELECTED
    && defense < spDefense))
        return DAMAGE_CATEGORY_PHYSICAL;
    else
        return DAMAGE_CATEGORY_SPECIAL;


}

u32 GetFlingPowerFromItemId(enum Item itemId)
{
    if (gItemsInfo[itemId].pocket == POCKET_TM_CASE)
    {
        u32 power = GetMovePower(ItemIdToBattleMoveId(itemId));
        if (power > 1)
            return power;
        return 10; // Status moves and moves with variable power always return 10 power.
    }
    else
        return GetItemFlingPower(itemId);
}

//vsonic change embargo to sidestatus
bool32 CanFling(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    u16 item = gBattleMons[battlerAtk].item;

    if (item == ITEM_NONE
      || (GetBattlerAbility(battlerAtk) == ABILITY_KLUTZ)
      || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM
      || (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_EMBARGO)
      || GetFlingPowerFromItemId(item) == 0
      || !CanBattlerGetOrLoseItem(battlerAtk, battlerDef, item))
        return FALSE;

    return TRUE;
}

// Sort an array of battlers by speed
// Useful for effects like pickpocket, eject button, red card, dancer
void SortBattlersBySpeed(enum BattlerId *battlers, bool32 slowToFast)
{
    int i, j, currSpeed;
    enum BattlerId currBattler;
    u16 speeds[MAX_BATTLERS_COUNT] = {0};

    for (i = 0; i < gBattlersCount; i++)
    {
        enum BattlerId battler = battlers[i];
        speeds[i] = GetBattlerTotalSpeedStat(battler, GetBattlerAbility(battler), GetBattlerHoldEffect(battler));
    }

    for (i = 1; i < gBattlersCount; i++)
    {
        currBattler = battlers[i];
        currSpeed = speeds[i];
        j = i - 1;

        if (slowToFast)
        {
            while (j >= 0 && speeds[j] > currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && speeds[j] < currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }

        battlers[j + 1] = currBattler;
        speeds[j + 1] = currSpeed;
    }
}

void TryRestoreHeldItems(void)
{
    u32 i;
    bool32 returnNPCItems = B_RETURN_STOLEN_NPC_ITEMS >= GEN_5 && gBattleTypeFlags & BATTLE_TYPE_TRAINER;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        // Check if held items should be restored after battle based on generation
        if (B_RESTORE_HELD_BATTLE_ITEMS >= GEN_9 || gBattleStruct->itemLost[B_SIDE_PLAYER][i].stolen || returnNPCItems)
        {
            u16 lostItem = gBattleStruct->itemLost[B_SIDE_PLAYER][i].originalItem;

            // Check if the lost item is a berry and the mon is not holding it
            if (GetItemPocket(lostItem) == POCKET_BERRIES && GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) != lostItem)
                lostItem = ITEM_NONE;

            // Check if the lost item should be restored
            if ((lostItem != ITEM_NONE || returnNPCItems) && GetItemPocket(lostItem) != POCKET_BERRIES)
                SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &lostItem);
        }
    }
}

bool32 CanStealItem(enum BattlerId battlerStealing, enum BattlerId battlerItem, u16 item)
{
    enum BattleSide stealerSide = GetBattlerSide(battlerStealing);

    /*if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
        return FALSE;

    // Check if the battler trying to steal should be able to
    if (stealerSide == B_SIDE_OPPONENT
        && !(gBattleTypeFlags &
             (BATTLE_TYPE_EREADER_TRAINER
              | BATTLE_TYPE_FRONTIER
              | BATTLE_TYPE_LINK
              | BATTLE_TYPE_RECORDED_LINK
              | BATTLE_TYPE_SECRET_BASE
              | (B_TRAINERS_KNOCK_OFF_ITEMS == TRUE ? BATTLE_TYPE_TRAINER : 0)
              )))
    {
        return FALSE;
    }
    else if (!(gBattleTypeFlags &
          (BATTLE_TYPE_EREADER_TRAINER
           | BATTLE_TYPE_FRONTIER
           | BATTLE_TYPE_LINK
           | BATTLE_TYPE_RECORDED_LINK
           | BATTLE_TYPE_SECRET_BASE))
        && GetBattlerPartyState(battlerStealing)->lostItemtoKnockOff)
    {
        return FALSE;
    }

    // It's supposed to pop before trying to steal but this also works
    if (GetItemHoldEffect(item) == HOLD_EFFECT_AIR_BALLOON)
        return FALSE;*/

    if (!CanBattlerGetOrLoseItem(battlerItem, battlerStealing, item)      // Battler with item cannot have it stolen
     || !CanBattlerGetOrLoseItem(battlerStealing, battlerItem, item)) // Stealer cannot take the item
        return FALSE;

    return TRUE;
}

void TrySaveExchangedItem(enum BattlerId battler, u16 stolenItem)
{
    // Because BtlController_EmitSetMonData does SetMonData, we need to save the stolen item only if it matches the battler's original
    // So, if the player steals an item during battle and has it stolen from it, it will not end the battle with it (naturally)
    if (B_TRAINERS_KNOCK_OFF_ITEMS == FALSE)
        return;
    // If regular trainer battle and mon's original item matches what is being stolen, save it to be restored at end of battle
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
      && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
      && IsOnPlayerSide(battler)
      && stolenItem == gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]].originalItem)
        gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]].stolen = TRUE;
}

bool32 IsBattlerAffectedByHazards(enum BattlerId battler, enum HoldEffect holdEffect, bool32 toxicSpikes)
{
    bool32 ret = TRUE;
    if (!IsBattlerAlive(battler))
    {
        ret = FALSE;
    }
    else if (toxicSpikes && holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS && !IS_BATTLER_OF_TYPE(battler, TYPE_POISON))
    {
        ret = FALSE;
        RecordItemEffectBattle(battler, holdEffect);
    }
    else if (holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS)
    {
        ret = FALSE;
        RecordItemEffectBattle(battler, holdEffect);
    }
    return ret;
}


bool32 IsSheerForceAffected(enum Move move, enum Ability ability)
{
    return ability == ABILITY_SHEER_FORCE && MoveIsAffectedBySheerForce(move);
}

// This function is the body of "jumpifstat", but can be used dynamically in a function
bool32 CompareStat(enum BattlerId battler, enum Stat statId, u8 cmpTo, u8 cmpKind, enum Ability ability)
{
    bool32 ret = FALSE;
    u8 statValue = gBattleMons[battler].statStages[statId];

    // Because this command is used as a way of checking if a stat can be lowered/raised,
    // we need to do some modification at run-time.
    if (ability == ABILITY_CONTRARY)
    {
        if (cmpKind == CMP_GREATER_THAN)
            cmpKind = CMP_LESS_THAN;
        else if (cmpKind == CMP_LESS_THAN)
            cmpKind = CMP_GREATER_THAN;

        if (cmpTo == MIN_STAT_STAGE)
            cmpTo = MAX_STAT_STAGE;
        else if (cmpTo == MAX_STAT_STAGE)
            cmpTo = MIN_STAT_STAGE;
    }

    switch (cmpKind)
    {
    case CMP_EQUAL:
        if (statValue == cmpTo)
            ret = TRUE;
        break;
    case CMP_NOT_EQUAL:
        if (statValue != cmpTo)
            ret = TRUE;
        break;
    case CMP_GREATER_THAN:
        if (statValue > cmpTo)
            ret = TRUE;
        break;
    case CMP_LESS_THAN:
        if (statValue < cmpTo)
            ret = TRUE;
        break;
    case CMP_COMMON_BITS:
        if (statValue & cmpTo)
            ret = TRUE;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(statValue & cmpTo))
            ret = TRUE;
        break;
    }

    return ret;
}

bool32 BlocksPrankster(enum Move move, enum BattlerId battlerPrankster, enum BattlerId battlerDef, bool32 checkTarget)
{
    if (GetConfig(B_PRANKSTER_DARK_TYPES) < GEN_7)
        return FALSE;
    if (!gProtectStructs[battlerPrankster].pranksterElevated)
        return FALSE;
    if (IsBattlerAlly(battlerPrankster, battlerDef))
        return FALSE;
    if (checkTarget && GetBattlerMoveTargetType(battlerPrankster, move) == TARGET_DEPENDS)
        return FALSE;
    if (checkTarget && GetBattlerMoveTargetType(battlerPrankster, move) == TARGET_OPPONENTS_FIELD)
        return FALSE;
    if (!IS_BATTLER_OF_TYPE(battlerDef, TYPE_DARK))
        return FALSE;
    if (IsSemiInvulnerable(battlerDef, CHECK_ALL))
        return FALSE;

    return TRUE;
}

//can potentially remove all, or repurpose for my version
bool32 CantPickupItem(u32 battler)
{
    // Used by RandomUniformExcept() for RNG_PICKUP
    if (battler == gBattlerAttacker && (GetConfig(B_PICKUP_WILD) < GEN_9 || gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_LINK)))
        return TRUE;
    return !(IsBattlerAlive(battler) && GetBattlerPartyState(battler)->usedHeldItem && gBattleStruct->battlerState[battler].canPickupItem);
}

//not using battler argument not using func anyway
//have my custom effect but could be make void instead
//vsonic
bool32 PickupHasValidTarget(enum BattlerId battler)
{
    u32 i;
    for (i = 0; i < gBattlersCount; i++)
    {
        if (!CantPickupItem(i))
            return TRUE;
    }
    return FALSE;
}

bool32 IsBattlerWeatherAffected(enum BattlerId battler, u32 weatherFlags)
{
    if (gBattleWeather & weatherFlags && HasWeatherEffect())
    {
        // given weather is active -> check if its sun, rain against utility umbrella (since only 1 weather can be active at once)
        //umbrella covers moonlight cuz parasoul
        if (gBattleWeather & (WEATHER_SUN | WEATHER_RAIN | WEATHER_MOON | WEATHER_ACID_RAIN) && GetBattlerHoldEffect(battler) == HOLD_EFFECT_UTILITY_UMBRELLA)
            return FALSE; // utility umbrella blocks sun, rain effects
        //usually wouldn't be good this is literally only good because of my custom effects
        //otherwise does nothing as apparently safety goggles already prevented
        //hail and sandstorm dmg
        else if (gBattleWeather & (WEATHER_ICY_ANY | WEATHER_SANDSTORM) && GetBattlerHoldEffect(battler) == HOLD_EFFECT_SAFETY_GOGGLES)
            return FALSE; //major upgrade to safety goggles, blocks hail and sandstorm effects, useful dealing sandstorm acc drop

        return TRUE;
    }
    return FALSE;
}

static u32 CanBattlerHitBothFoesInTerrain(enum BattlerId battler, enum Move move, enum BattleMoveEffects effect)
{
    return effect == EFFECT_TERRAIN_BOOST
        && GetMoveTerrainBoost_HitsBothFoes(move)
        && IsBattlerTerrainAffected(battler, GetBattlerAbility(battler), GetBattlerHoldEffect(battler), gFieldStatuses, GetMoveTerrainBoost_Terrain(move));
}

enum MoveTarget GetBattlerMoveTargetType(enum BattlerId battler, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (effect == EFFECT_CURSE && !IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TARGET_USER;
    if (CanBattlerHitBothFoesInTerrain(battler, move, effect))
        return TARGET_BOTH;
    if (effect == EFFECT_TERA_STARSTORM && gBattleMons[battler].species == SPECIES_TERAPAGOS_STELLAR)
        return TARGET_BOTH;

    return GetMoveTarget(move);
}

bool32 CanTargetBattler(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (GetMoveEffect(move) == EFFECT_HIT_ENEMY_HEAL_ALLY
    &&  IsBattlerAlly(battlerAtk, battlerDef)
    &&  gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HEAL_BLOCK)
        return FALSE;   // Pokémon affected by Heal Block cannot target allies with Pollen Puff
    if (IsBattlerAlly(battlerAtk, battlerDef) && (GetActiveGimmick(battlerAtk) == GIMMICK_DYNAMAX
                                               || IsGimmickSelected(battlerAtk, GIMMICK_DYNAMAX)))
        return FALSE;

    return TRUE;
}

u32 GetNextTarget(u32 moveTarget, bool32 excludeCurrent)
{
    enum BattlerId battler;
    for (battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
    {
        if (battler == gBattlerAttacker || !IsBattlerAlive(battler))
            continue;

        if (!(excludeCurrent && battler == gBattlerTarget)
         && !gBattleStruct->battlerState[gBattlerAttacker].targetsDone[battler]
         && (!IsBattlerAlly(battler, gBattlerAttacker) || moveTarget == TARGET_FOES_AND_ALLY))
            break;
    }
    return battler;
}

void CopyMonLevelAndBaseStatsToBattleMon(enum BattlerId battler, struct Pokemon *mon)
{
    gBattleMons[battler].level = GetMonData(mon, MON_DATA_LEVEL);
    gBattleMons[battler].hp = GetMonData(mon, MON_DATA_HP);
    gBattleMons[battler].maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
}

void CopyMonAbilityAndTypesToBattleMon(enum BattlerId battler, struct Pokemon *mon)
{
    gBattleMons[battler].ability = GetMonAbility(mon);
    #if TESTING
    if (gTestRunnerEnabled)
    {
        u32 array = (!IsPartnerMonFromSameTrainer(battler)) ? battler : GetBattlerSide(battler);
        u32 partyIndex = gBattlerPartyIndexes[battler];
        if (TestRunner_Battle_GetForcedAbility(array, partyIndex))
            gBattleMons[battler].ability = TestRunner_Battle_GetForcedAbility(array, partyIndex);
    }
    #endif
    gBattleMons[battler].type1 = GetSpeciesPrimaryType(gBattleMons[battler].species);
    gBattleMons[battler].type2 = GetSpeciesSecondaryType(gBattleMons[battler].species);
    gBattleMons[battler].type3 = TYPE_MYSTERY;
}

void RecalcBattlerStats(enum BattlerId battler, struct Pokemon *mon, bool32 isDynamaxing)
{
    u32 hp = GetMonData(mon, MON_DATA_HP);
    u32 oldMaxHp = GetMonData(mon, MON_DATA_MAX_HP);
    CalculateMonStats(mon);
    if (GetActiveGimmick(battler) == GIMMICK_DYNAMAX && gChosenActionByBattler[battler] != B_ACTION_SWITCH)
    {
        ApplyDynamaxHPMultiplier(mon);
        u32 newMaxHp = GetMonData(mon, MON_DATA_MAX_HP);
        if (!isDynamaxing)
        {
            if (newMaxHp > oldMaxHp) // restore hp gained from changing form, without this, dynamaxed form changes are calculated incorrectly
            {
                hp += (newMaxHp - oldMaxHp);
                SetMonData(mon, MON_DATA_HP, &hp);
            }
            else
            {
                SetMonData(mon, MON_DATA_HP, &hp);
            }
        }
    }
    CopyMonLevelAndBaseStatsToBattleMon(battler, mon);
    CopyMonAbilityAndTypesToBattleMon(battler, mon);
}

void RemoveConfusionStatus(enum BattlerId battler)
{
    gBattleMons[battler].volatiles.confusionTurns = 0;
}

u8 GetBattlerGender(enum BattlerId battler)
{
    return GetGenderFromSpeciesAndPersonality(gBattleMons[battler].species,
                                              gBattleMons[battler].personality);
}

bool32 AreBattlersOfOppositeGender(enum BattlerId battler1, enum BattlerId battler2)
{
    u8 gender1 = GetBattlerGender(battler1);
    u8 gender2 = GetBattlerGender(battler2);

    return (gender1 != MON_GENDERLESS && gender2 != MON_GENDERLESS && gender1 != gender2);
}

bool32 AreBattlersOfSameGender(enum BattlerId battler1, enum BattlerId battler2)
{
    u8 gender1 = GetBattlerGender(battler1);
    u8 gender2 = GetBattlerGender(battler2);

    return (gender1 != MON_GENDERLESS && gender2 != MON_GENDERLESS && gender1 == gender2);
}

u32 CalcSecondaryEffectChance(enum BattlerId battler, enum Ability battlerAbility, const struct AdditionalEffect *additionalEffect)
{
    bool8 hasSereneGrace = (battlerAbility == ABILITY_SERENE_GRACE);
    bool8 hasRainbow = (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_RAINBOW) != 0;
    u16 secondaryEffectChance = additionalEffect->chance;

    if (hasRainbow && hasSereneGrace && additionalEffect->moveEffect == MOVE_EFFECT_FLINCH)
        return secondaryEffectChance * 2;

    if (hasSereneGrace)
        secondaryEffectChance *= 2;
    if (hasRainbow && additionalEffect->moveEffect != MOVE_EFFECT_SECRET_POWER)
        secondaryEffectChance *= 2;

    return secondaryEffectChance;
}

bool32 MoveEffectIsGuaranteed(enum BattlerId battler, enum Ability battlerAbility, const struct AdditionalEffect *additionalEffect)
{
    return additionalEffect->chance == 0 || CalcSecondaryEffectChance(battler, battlerAbility, additionalEffect) >= 100;
}

//vsonic to remove later
bool32 IsGen6ExpShareEnabled(void)
{
    //if (I_EXP_SHARE_FLAG <= TEMP_FLAGS_END)
        return FALSE;

    //return FlagGet(I_EXP_SHARE_FLAG);
}


bool32 MoveHasAdditionalEffect(enum Move move, enum MoveEffect moveEffect)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == moveEffect && additionalEffect->self == FALSE)
            return TRUE;
    }
    return FALSE;
}

bool32 MoveHasAdditionalEffectWithChance(enum Move move, enum MoveEffect moveEffect, u32 chance)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == moveEffect && additionalEffect->chance == chance)
            return TRUE;
    }
    return FALSE;
}

bool32 MoveHasAdditionalEffectSelf(enum Move move, enum MoveEffect moveEffect)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == moveEffect && additionalEffect->self == TRUE)
            return TRUE;
    }
    return FALSE;
}

bool32 IsMoveEffectRemoveSpeciesType(enum Move move, enum MoveEffect moveEffect, u32 argument)
{
    return (MoveHasAdditionalEffectSelf(move, moveEffect) && GetMoveArgType(move) == argument);
}

bool32 MoveHasChargeTurnAdditionalEffect(enum Move move)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        if (GetMoveAdditionalEffectById(move, i)->onChargeTurnOnly)
            return TRUE;
    }
    return FALSE;
}

bool32 MoveIsAffectedBySheerForce(enum Move move)
{
    u32 i;
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if ((additionalEffect->chance > 0) != additionalEffect->sheerForceOverride)
            return TRUE;
    }
    return FALSE;
}

//not using this but adjust logic
//need also well actually change this to is floating
bool8 CanMonParticipateInSkyBattle(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u16 monAbilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM);

    //bool8 hasLevitateAbility = GetSpeciesAbility(species, monAbilityNum) == ABILITY_LEVITATE;
    bool8 isFlyingType = GetSpeciesPrimaryType(species) == TYPE_FLYING || GetSpeciesSecondaryType(species) == TYPE_FLYING;
    bool8 monIsValidAndNotEgg = GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES) && !GetMonData(mon, MON_DATA_IS_EGG);

    if (monIsValidAndNotEgg)
    {
        if (IsFloatingSpecies(species) && !IsMonBannedFromSkyBattles(species))
            return TRUE;
    }
    return FALSE;
}

//huh weird pokemon already has short list
//of mon that couldn't fly
bool8 IsMonBannedFromSkyBattles(u16 species)
{
    switch (species)
    {
#if B_SKY_BATTLE_STRICT_ELIGIBILITY == TRUE
        case SPECIES_SPEAROW:
        case SPECIES_FARFETCHD:
        case SPECIES_DODUO:
        case SPECIES_DODRIO:
        case SPECIES_HOOTHOOT:
        case SPECIES_NATU:
        case SPECIES_MURKROW:
        case SPECIES_DELIBIRD:
        case SPECIES_TAILLOW:
        case SPECIES_STARLY:
        case SPECIES_CHATOT:
        case SPECIES_SHAYMIN:
        case SPECIES_PIDOVE:
        case SPECIES_ARCHEN:
        case SPECIES_DUCKLETT:
        case SPECIES_RUFFLET:
        case SPECIES_VULLABY:
        case SPECIES_FLETCHLING:
        case SPECIES_HAWLUCHA:
        case SPECIES_ROWLET:
        case SPECIES_PIKIPEK:
#endif
        case SPECIES_EGG:
            return TRUE;
        default:
            return FALSE;
    }
}

//populate given array with battle types
void GetBattlerTypes(enum BattlerId battler, bool32 ignoreTera, enum Type types[/*static*/ 3])
{
    // Terastallization.
    bool32 isTera = GetActiveGimmick(battler) == GIMMICK_TERA;
    if (!ignoreTera && isTera)
    {
        enum Type teraType = GetBattlerTeraType(battler);
        if (teraType != TYPE_STELLAR)
        {
            types[0] = types[1] = types[2] = teraType;
            return;
        }
    }

    types[0] = gBattleMons[battler].type1;
    types[1] = gBattleMons[battler].type2;
    types[2] = gBattleMons[battler].type3;


}

//return filled array of type data
//used mostly for performing operations based on
//but not directly affecting battler type
enum Type GetBattlerType(enum BattlerId battler, u32 typeIndex, bool32 ignoreTera)
{
    enum Type types[3];
    GetBattlerTypes(battler, ignoreTera, types);
    return types[typeIndex];
}

//reworked w my type functions
void RemoveBattlerType(enum BattlerId battler, enum Type type)
{
    u32 i;
    if (GetActiveGimmick(battler) == GIMMICK_TERA) // don't remove type if Terastallized
        return;
    for (i = 0; i < NUM_BATTLE_TYPES; i++)
    {
        if (GetBattlerTypebySlot(battler, i) == type)
            SetBattlerTypebySlot(battler, i, TYPE_MYSTERY);
    }
}

void SetShellSideArmCategory(void)
{
    enum BattlerId battlerAtk, battlerDef;
    u32 attackerAtkStat;
    u32 targetDefStat;
    u32 attackerSpAtkStat;
    u32 targetSpDefStat;
    u8 statStage;
    u32 physical;
    u32 special;
    u32 power = GetMovePower(MOVE_SHELL_SIDE_ARM);

    // Don't run this check for Safari Battles. Because player's stats are zeroed out, this performs division by zero which previously would crash on certain emulators in Safari Zone.
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return;

    for (battlerAtk = 0; battlerAtk < gBattlersCount; battlerAtk++)
    {
        attackerAtkStat = gBattleMons[battlerAtk].attack;
        statStage = gBattleMons[battlerAtk].statStages[STAT_ATK];
        attackerAtkStat *= gStatStageRatios[statStage][0];
        attackerAtkStat /= gStatStageRatios[statStage][1];

        attackerSpAtkStat = gBattleMons[battlerAtk].spAttack;
        statStage = gBattleMons[battlerAtk].statStages[STAT_SPATK];
        attackerSpAtkStat *= gStatStageRatios[statStage][0];
        attackerSpAtkStat /= gStatStageRatios[statStage][1];

        for (battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
        {
            if (battlerAtk == battlerDef)
                continue;

            targetDefStat = gBattleMons[battlerDef].defense;
            statStage = gBattleMons[battlerDef].statStages[STAT_DEF];
            targetDefStat *= gStatStageRatios[statStage][0];
            targetDefStat /= gStatStageRatios[statStage][1];
            if (targetDefStat == 0)
                targetDefStat = 1;

            physical = ((((2 * gBattleMons[battlerAtk].level / 5 + 2) * power * attackerAtkStat) / targetDefStat) / 50);

            targetSpDefStat = gBattleMons[battlerDef].spDefense;
            statStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
            targetSpDefStat *= gStatStageRatios[statStage][0];
            targetSpDefStat /= gStatStageRatios[statStage][1];
            if (targetSpDefStat == 0)
                targetSpDefStat = 1;

            special = ((((2 * gBattleMons[battlerAtk].level / 5 + 2) * power * attackerSpAtkStat) / targetSpDefStat) / 50);

            if ((physical > special) || (physical == special && RandomPercentage(RNG_SHELL_SIDE_ARM, 50)))
                gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] = DAMAGE_CATEGORY_PHYSICAL;
            else
                gBattleStruct->shellSideArmCategory[battlerAtk][battlerDef] = DAMAGE_CATEGORY_SPECIAL;
        }
    }
}

bool32 CanTargetPartner(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    return (IsDoubleBattle()
         && IsBattlerAlive(BATTLE_PARTNER(battlerDef))
         && battlerDef != BATTLE_PARTNER(battlerAtk));
}
/*
static inline bool32 DoesBattlerHaveAbilityImmunity(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Type moveType)
{
    enum Ability abilityDef = GetBattlerAbility(battlerDef);

    return (CanAbilityBlockMove(battlerAtk, battlerDef, GetBattlerAbility(battlerAtk), abilityDef, gCurrentMove, CHECK_TRIGGER)
        || TryHandleAbilityAbsorbMove(battlerAtk, battlerDef, abilityDef, gCurrentMove, moveType, CHECK_TRIGGER));
}

bool32 TargetFullyImmuneToCurrMove(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    enum Type moveType = GetBattleMoveType(gCurrentMove);
    return ((CalcTypeEffectivenessMultiplierHelper(gCurrentMove, moveType, battlerAtk, battlerDef, GetBattlerAbility(battlerAtk), GetBattlerAbility(battlerDef), FALSE) == UQ_4_12(0.0))
         || IsBattlerProtected(battlerAtk, battlerDef, gCurrentMove)
         || !BreaksThroughSemiInvulnerablity(battlerDef, gCurrentMove)
         || DoesBattlerHaveAbilityImmunity(battlerAtk, battlerDef, moveType));
}*/

bool32 IsBattlerUnaffectedByMove(enum BattlerId battler)
{
    return gBattleStruct->moveResultFlags[battler] & MOVE_RESULT_NO_EFFECT;
}

//for beatup think what I did was give stab
//but make do typeless so gets around wonder guard? 
//ok this is the part that makes things do typeless dmg
//but its conflated with type mystery to make it skip dmg calc
//and thus wonder guard logic
//which doesnt allow me to set stab becuase it overwrites move type
//it works for what EE wants but for me I'll just make a flag
//to set typeless dmg without overwriting type
//vsonic
enum Type GetBattleMoveType(enum Move move)
{
    if (gMain.inBattle)
    {
        if (gBattleStruct->dynamicMoveType)
            return gBattleStruct->dynamicMoveType & DYNAMIC_TYPE_MASK;

        //value removed was just for typeless set
        //enum BattleMoveEffects effect = GetMoveEffect(move);
    }
    return GetMoveType(move);
}

void TryActivateSleepClause(enum BattlerId battler, u32 indexInParty)
{
    if (gBattleStruct->battlerState[battler].sleepClauseEffectExempt)
    {
        gBattleStruct->battlerState[battler].sleepClauseEffectExempt = FALSE;
        return;
    }

    if (IsSleepClauseEnabled())
        gBattleStruct->monCausingSleepClause[GetBattlerSide(battler)] = indexInParty;
}

void TryDeactivateSleepClause(enum BattlerId battlerSide, u32 indexInParty)
{
    // If the pokemon on the given side at the given index in the party is the one causing Sleep Clause to be active,
    // set monCausingSleepClause[battlerSide] = PARTY_SIZE, which means Sleep Clause is not active for the given side
    if (IsSleepClauseEnabled() && gBattleStruct->monCausingSleepClause[battlerSide] == indexInParty)
        gBattleStruct->monCausingSleepClause[battlerSide] = PARTY_SIZE;
}

bool32 IsSleepClauseActiveForSide(enum BattlerId battlerSide)
{
    // If monCausingSleepClause[battlerSide] == PARTY_SIZE, Sleep Clause is not active for the given side.
    // If monCausingSleepClause[battlerSide] < PARTY_SIZE, it means it is storing the index of the mon that is causing Sleep Clause to be active,
    // from which it follows that Sleep Clause is active.
    return (IsSleepClauseEnabled() && (gBattleStruct->monCausingSleepClause[battlerSide] < PARTY_SIZE));
}

bool32 IsSleepClauseEnabled()
{
    /*if (B_SLEEP_CLAUSE)
        return TRUE;
    if (FlagGet(B_FLAG_SLEEP_CLAUSE))
        return TRUE;*/
    return FALSE;
}

void ClearDamageCalcResults(void)
{
    for (enum BattlerId battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
    {
        gBattleStruct->moveDamage[battler] = 0;
        gBattleStruct->moveResultFlags[battler] = 0;
        gSpecialStatuses[battler].criticalHit = FALSE;
        gSpecialStatuses[battler].damagedByAttack = FALSE;
    }

    gBattleStruct->doneDoublesSpreadHit = FALSE;
    gBattleStruct->calculatedDamageDone = FALSE;
    gBattleStruct->calculatedSpreadMoveAccuracy = FALSE;
    gBattleStruct->printedStrongWindsWeakenedAttack = FALSE;
    gBattleStruct->numSpreadTargets = 0;
    gBattleStruct->unableToUseMove = FALSE;
	gBattleStruct->preAttackAnimPlayed = FALSE;
    gBattleScripting.savedDmg = 0;
    if (gCurrentMove != MOVE_NONE)
        gBattleStruct->moldBreakerActive = IsMoldBreakerTypeAbility(gBattlerAttacker, GetBattlerAbility(gBattlerAttacker)) || MoveIgnoresTargetAbility(gCurrentMove);
    else
        gBattleStruct->moldBreakerActive = FALSE;
}

//think I don't need this, places where this is
//it also checks for destinybond status
bool32 DoesDestinyBondFail(enum BattlerId battler)
{
    return GetConfig(B_DESTINY_BOND_FAIL) >= GEN_7 && gBattleMons[battler].volatiles.destinyBond;
}

// This check has always to be the last in a condtion statement because of the recording of AI data.
bool32 IsMoveEffectBlockedByTarget(enum Ability ability)
{
    if (ability == ABILITY_SHIELD_DUST)
    {
        RecordAbilityBattle(gBattlerTarget, ability);
        return TRUE;
    }
    else if (GetBattlerHoldEffect(gBattlerTarget) == HOLD_EFFECT_COVERT_CLOAK)
    {
        RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_COVERT_CLOAK);
        return TRUE;
    }

    return FALSE;
}

bool32 SetTargetToNextPursuiter(enum BattlerId battlerDef)
{
    u32 i;
    for (i = gCurrentTurnActionNumber + 1; i < gBattlersCount; i++)
    {
        enum BattlerId battler = gBattlerByTurnOrder[i];
        if (gChosenActionByBattler[battler] == B_ACTION_USE_MOVE
        && GetMoveEffect(gChosenMoveByBattler[battler]) == EFFECT_PURSUIT
        && IsBattlerAlive(battlerDef)
        && IsBattlerAlive(battler)
        && !IsBattlerAlly(battler, battlerDef)
        && (B_PURSUIT_TARGET >= GEN_4 || gBattleStruct->moveTarget[battler] == battlerDef)
        && !IsGimmickSelected(battler, GIMMICK_Z_MOVE)
        && !IsGimmickSelected(battler, GIMMICK_DYNAMAX)
        && GetActiveGimmick(battler) != GIMMICK_DYNAMAX)
        {
            gBattlerTarget = battler;
            return TRUE;
        }
    }
    return FALSE;
}

bool32 IsPursuitTargetSet(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (gBattleStruct->battlerState[battler].pursuitTarget)
            return TRUE;
    }
    return FALSE;
}

void ClearPursuitValues(void)
{
    for (u32 i = 0; i < gBattlersCount; i++)
        gBattleStruct->battlerState[i].pursuitTarget = FALSE;
    gBattleStruct->pursuitStoredSwitch = PARTY_SIZE;
}

void ClearPursuitValuesIfSet(enum BattlerId battler)
{
    if (gBattleStruct->battlerState[battler].pursuitTarget)
        ClearPursuitValues();
}

bool32 HasWeatherEffect(void)
{
    //added for some reason
    //if (!gMain.inBattle)
    //    return FALSE;
    
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (!IsBattlerAlive(battler))
            continue;

        enum Ability ability = GetBattlerAbility(battler);
        switch (ability)
        {
        case ABILITY_STORM_BREAK:
        case ABILITY_AIR_LOCK:
            return FALSE;
        default:
            break;
        }
    }

    return TRUE;
}

void UpdateStallMons(void)
{
    if (IsBattlerTurnDamaged(gBattlerTarget) || GetMoveCategory(gCurrentMove) == DAMAGE_CATEGORY_STATUS)
        return;

    struct BattleContext ctx = {0};
    ctx.battlerAtk = gBattlerAttacker;
    ctx.battlerDef = gBattlerTarget;
    ctx.move = ctx.chosenMove = gCurrentMove;
    ctx.moveType = GetBattleMoveType(gCurrentMove); //  Probably doesn't handle dynamic move types right now
    ctx.abilityAtk = GetBattlerAbility(ctx.battlerAtk);
    ctx.abilityDef = GetBattlerAbility(ctx.battlerDef);
    ctx.holdEffectAtk = GetBattlerHoldEffect(ctx.battlerAtk);
    ctx.holdEffectDef = GetBattlerHoldEffect(ctx.battlerDef);

    if (IsBattlerProtected(&ctx))
        return;

    enum MoveTarget target = GetBattlerMoveTargetType(ctx.battlerAtk, ctx.move);
    if (!IsDoubleBattle()
     || target == TARGET_SELECTED
     || target == TARGET_SMART)
    {
        if (CanMoveBeBlockedByTarget(&ctx, GetChosenMovePriority(ctx.battlerAtk, ctx.abilityAtk))
        || CanAbilityAbsorbMove(&ctx))
        {
            gAiBattleData->playerStallMons[gBattlerPartyIndexes[gBattlerTarget]]++;
        }
        else if (CalcTypeEffectivenessMultiplier(&ctx) == UQ_4_12(0.0))
        {
            gAiBattleData->playerStallMons[gBattlerPartyIndexes[gBattlerTarget]]++;
        }
    }
    //  Handling for moves that target multiple opponents in doubles not handled currently
}

bool32 TrySwitchInEjectPack(enum EjectPackTiming timing)
{
    // Because sorting the battlers by speed takes lots of cycles, it's better to just check if any of the battlers has the Eject items.
    u32 ejectPackBattlers = 0;
    u32 numEjectPackBattlers = 0;

    for (u32 i = 0; i < gBattlersCount; i++)
    {
        if (gBattleMons[i].volatiles.tryEjectPack
         && GetBattlerHoldEffect(i) == HOLD_EFFECT_EJECT_PACK
         && IsBattlerAlive(i)
         && CountUsablePartyMons(i) > 0)
        {
            ejectPackBattlers |= 1u << i;
            numEjectPackBattlers++;
        }
    }

    if (numEjectPackBattlers == 0)
        return FALSE;

    enum BattlerId battlers[4] = {0, 1, 2, 3};
    if (numEjectPackBattlers > 1)
        SortBattlersBySpeed(battlers, FALSE);

    for (u32 i = 0; i < gBattlersCount; i++)
        gBattleMons[i].volatiles.tryEjectPack = FALSE;

    for (u32 i = 0; i < gBattlersCount; i++)
    {
        enum BattlerId battler = battlers[i];

        if (!(ejectPackBattlers & 1u << battler))
            continue;

        gBattleScripting.battler = battler;
        gLastUsedItem = gBattleMons[battler].item;
        if (timing == END_TURN)
            BattleScriptExecute(BattleScript_EjectPackActivate_End2);
        else
            BattleScriptCall(BattleScript_EjectPackActivate_Ret);
        gAiLogicData->ejectPackSwitch = TRUE;
        return TRUE;
    }

    return FALSE;
}

//vsonic reworked effect may not need
bool32 EmergencyExitCanBeTriggered(enum BattlerId battler)
{
    enum Ability ability = GetBattlerAbility(battler);

    if (ability != ABILITY_EMERGENCY_EXIT && ability != ABILITY_WIMP_OUT)
        return FALSE;

    if (IsBattlerAlive(battler)
     && HadMoreThanHalfHpNowDoesnt(battler)
     && (CanBattlerSwitch(battler) || !(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
     && !(gBattleTypeFlags & BATTLE_TYPE_ARENA)
     && gBattleMons[battler].volatiles.semiInvulnerable != STATE_SKY_DROP)
        return TRUE;

    return FALSE;
}

bool32 TryTriggerSymbiosis(enum BattlerId battler, u32 ally)
{
    return GetBattlerAbility(ally) == ABILITY_SYMBIOSIS
        && gBattleMons[battler].item == ITEM_NONE
        && gBattleMons[ally].item != ITEM_NONE
        && CanBattlerGetOrLoseItem(battler, ally, gBattleMons[ally].item)
        && CanBattlerGetOrLoseItem(ally, battler, gBattleMons[ally].item)
        && IsBattlerAlive(battler)
        && IsBattlerAlive(ally);
}

// Called by Cmd_removeitem. itemId represents the item that was removed, not being given.
bool32 TrySymbiosis(enum BattlerId battler, u32 itemId, bool32 moveEnd)
{
    if (!gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]].stolen
        && gBattleStruct->changedItems[battler] == ITEM_NONE
        && GetBattlerHoldEffect(battler) != HOLD_EFFECT_EJECT_BUTTON
        && GetBattlerHoldEffect(battler) != HOLD_EFFECT_EJECT_PACK
        && (GetConfig(B_SYMBIOSIS_GEMS) < GEN_7 || !(gSpecialStatuses[battler].gemBoost))
        && GetMoveEffect(gCurrentMove) != EFFECT_FLING //Fling and damage-reducing berries are handled separately.
        && !gSpecialStatuses[battler].berryReduced
        && TryTriggerSymbiosis(battler, BATTLE_PARTNER(battler)))
    {
        BestowItem(BATTLE_PARTNER(battler), battler);
        gLastUsedAbility = gBattleMons[BATTLE_PARTNER(battler)].ability;
        gEffectBattler = battler;
        gBattleScripting.battler = gBattlerAbility = BATTLE_PARTNER(battler);
        if (moveEnd)
            BattleScriptPushCursor();
        else
            BattleScriptPush(gBattlescriptCurrInstr + 2);
        gBattlescriptCurrInstr = BattleScript_SymbiosisActivates;
        return TRUE;
    }
    return FALSE;
}

// Used by Bestow and Symbiosis to take an item from one battler and give to another.
void BestowItem(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    gLastUsedItem = gBattleMons[battlerAtk].item;

    gBattleMons[battlerAtk].item = ITEM_NONE;
    BtlController_EmitSetMonData(battlerAtk, B_COMM_TO_CONTROLLER, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[battlerAtk].item), &gBattleMons[battlerAtk].item);
    MarkBattlerForControllerExec(battlerAtk);
    CheckSetUnburden(battlerAtk);

    gBattleMons[battlerDef].item = gLastUsedItem;
    BtlController_EmitSetMonData(battlerDef, B_COMM_TO_CONTROLLER, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[battlerDef].item), &gBattleMons[battlerDef].item);
    MarkBattlerForControllerExec(battlerDef);
    gBattleMons[battlerDef].volatiles.unburdenActive = FALSE;
}

#define UNPACK_VOLATILE_GETTERS(_enum, _fieldName, _typeMaxValue, ...) case _enum: return gBattleMons[battler].volatiles._fieldName;

// Gets the value of a volatile status flag for a certain battler
// Primarily used for the debug menu and scripts. Outside of it explicit references are preferred
// Uses Arm because there is a compiler bug when it tries to compile in thumb
ARM_FUNC u32 GetBattlerVolatile(enum BattlerId battler, enum Volatile _volatile)
{
    switch (_volatile)
    {
        VOLATILE_DEFINITIONS(UNPACK_VOLATILE_GETTERS)
        /* Expands to:
        case VOLATILE_CONFUSION:
            return gBattleMons[battler].volatiles.confusionTurns;
        */
        default: // Invalid volatile status
            return 0;
    }
}

#define UNPACK_VOLATILE_SETTERS(_enum, _fieldName, _typeMaxValue, ...) case _enum: gBattleMons[battler].volatiles._fieldName = min(GET_VOLATILE_MAXIMUM(_typeMaxValue), newValue); break;

// Sets the value of a volatile status flag for a certain battler
// Primarily used for the debug menu and scripts. Outside of it explicit references are preferred
void SetMonVolatile(enum BattlerId battler, enum Volatile _volatile, u32 newValue)
{
    switch (_volatile)
    {
        VOLATILE_DEFINITIONS(UNPACK_VOLATILE_SETTERS)
        /* Expands to:
        case VOLATILE_CONFUSION:
            gBattleMons[battler].volatiles.confusionTurns = min(MAX_BITS(3), newValue);
            break;
        */
        default: // Invalid volatile status
            return;
    }
}

bool32 ItemHealMonVolatile(enum BattlerId battler, u16 itemId)
{
    bool32 statusChanged = FALSE;
    const u8 *effect = GetItemEffect(itemId);
    if (effect[3] & ITEM3_STATUS_ALL)
    {
        statusChanged = (gBattleMons[battler].volatiles.infatuatedwithMon || gBattleMons[battler].volatiles.confusionTurns > 0);
        gBattleMons[battler].volatiles.infatuatedwithMon = 0;
        gBattleMons[battler].volatiles.confusionTurns = 0;
    }
    else if (effect[0] & ITEM0_INFATUATION)
    {
        statusChanged = !!gBattleMons[battler].volatiles.infatuatedwithMon;
        gBattleMons[battler].volatiles.infatuatedwithMon = 0;
    }
    else if (effect[3] & ITEM3_CONFUSION)
    {
        statusChanged = (gBattleMons[battler].volatiles.confusionTurns > 0);
        gBattleMons[battler].volatiles.confusionTurns = 0;
    }

    return statusChanged;
}

// Hazards are added to a queue and applied based in order (FIFO)
void PushHazardTypeToQueue(u32 side, enum Hazards hazardType)
{
    if (!IsHazardOnSide(side, hazardType)) // Failsafe
        gBattleStruct->hazardsQueue[side][gBattleStruct->numHazards[side]++] = hazardType;
}

bool32 IsHazardOnSide(u32 side, enum Hazards hazardType)
{
    for (u32 i = 0; i < HAZARDS_MAX_COUNT; i++)
    {
        if (gBattleStruct->hazardsQueue[side][i] == hazardType)
            return TRUE;
    }
    return FALSE;
}

bool32 AreAnyHazardsOnSide(u32 side)
{
    return gBattleStruct->numHazards[side] > 0;
}

//vsonic, believe done
bool32 IsHazardOnSideAndClear(u32 side, enum Hazards hazardType)
{
    for (u32 i = 0; i < HAZARDS_MAX_COUNT; i++)
    {
        if (gBattleStruct->hazardsQueue[side][i] == hazardType)
        {
            gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
            if (hazardType == HAZARDS_SPIKES)
                gSideTimers[side].spikesAmount = 0;
            else if (hazardType == HAZARDS_TOXIC_SPIKES)
                gSideTimers[side].toxicSpikesAmount = 0;
            else if (hazardType == HAZARDS_STICKY_WEB)
                gSideTimers[side].stickyWebAmount = 0;
            return TRUE;
        }
    }
    return FALSE;
}

//done
void RemoveAllHazardsFromField(u32 side)
{
    gSideTimers[side].spikesAmount = 0;
    gSideTimers[side].toxicSpikesAmount = 0;
    gSideTimers[side].stickyWebAmount = 0;
    gBattleStruct->numHazards[side] = 0;
    for (u32 i = 0; i < HAZARDS_MAX_COUNT; i++)
        gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
}

//done
void RemoveHazardFromField(u32 side, enum Hazards hazardType)
{
    u32 i;
    for (i = 0; i < HAZARDS_MAX_COUNT; i++)
    {
        if (gBattleStruct->hazardsQueue[side][i] == hazardType)
        {
            gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
            gBattleStruct->numHazards[side]--;
            if (hazardType == HAZARDS_SPIKES)
                gSideTimers[side].spikesAmount = 0;
            else if (hazardType == HAZARDS_TOXIC_SPIKES)
                gSideTimers[side].toxicSpikesAmount = 0;
            else if (hazardType == HAZARDS_STICKY_WEB)
            {
                gSideTimers[side].stickyWebAmount = 0;
                gSideTimers[side].stickyWebBattlerSide = BATTLE_ID_NONE;
            }
            break;
        }
    }
    while (i < HAZARDS_MAX_COUNT)
    {
        if (i+1 == HAZARDS_MAX_COUNT)
        {
            gBattleStruct->hazardsQueue[side][i] = HAZARDS_NONE;
            break;
        }
        gBattleStruct->hazardsQueue[side][i] = gBattleStruct->hazardsQueue[side][i+1];
        i++;
    }
}

static bool32 CanMoveSkipAccuracyCheck(enum BattlerId battlerAtk, u32 move)
{
    return (move == MOVE_TOXIC && IS_BATTLER_OF_TYPE(battlerAtk, GetMoveType(move)));
}

//believe done
//may need add argument if this is used in ai
//for affinity check function to know if it should use ai version
bool32 CanMoveSkipAccuracyCalc(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum Move move, enum ResultOption option)
{
    bool32 effect = FALSE;
    enum Ability ability = ABILITY_NONE;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    u32 nonVolatileStatus = GetMoveNonVolatileStatus(move);

    if ((gBattleMons[battlerDef].volatiles.lockOn && gBattleMons[battlerDef].volatiles.battlerWithSureHit == battlerAtk)
     || (move == MOVE_TOXIC && DoesBattlerGetTypeBasedAffinity(abilityAtk, battlerDef, abilityDef, TYPE_POISON, FALSE))
     || gBattleMons[battlerDef].volatiles.glaiveRush)
    {
        effect = TRUE;
    }
    // If the attacker has the ability No Guard and they aren't targeting a Pokemon involved in a Sky Drop with the move Sky Drop, move hits.
    else if (IsSureHitAbility(abilityAtk)
          && gBattleMons[battlerDef].volatiles.semiInvulnerable != STATE_COMMANDER
          && (moveEffect != EFFECT_SKY_DROP || gBattleStruct->skyDropTargets[battlerDef] == SKY_DROP_NO_TARGET))
    {
        effect = TRUE;
        ability = abilityAtk;
    }
    // If the target has the ability No Guard and they aren't involved in a Sky Drop or the current move isn't Sky Drop, move hits.
    else if (IsSureHitAbility(abilityDef)
          && (moveEffect != EFFECT_SKY_DROP || gBattleStruct->skyDropTargets[battlerDef] == SKY_DROP_NO_TARGET))
    {
        effect = TRUE;
        ability = abilityDef;
    }
    // If the target is under the effects of Telekinesis, and the move isn't a OH-KO move, move hits.
    else if (gBattleMons[battlerDef].volatiles.telekinesis
          && !IsSemiInvulnerable(battlerDef, CHECK_ALL)
          && moveEffect != EFFECT_OHKO
          && moveEffect != EFFECT_SHEER_COLD)
    {
        effect = TRUE;
    }
    else if (gBattleStruct->battlerState[battlerDef].pursuitTarget)
    {
        effect = TRUE;
    }
    /*else if (GetActiveGimmick(battlerAtk) == GIMMICK_Z_MOVE && !IsSemiInvulnerable(battlerDef, CHECK_ALL))
    {
        effect = TRUE;
    }*/

    //believe should be simpler way to do what I want? vsonic
    else if (gBattleMons[battlerDef].statStages[STAT_EVASION] > DEFAULT_STAT_STAGE
     && MoveSureHitEvasionBoostedTargets(move))
    {
        effect = TRUE;
    }
    else if (GetMoveAccuracy(move) == 0)
    {
        effect = TRUE;
    }

    //think will change to use weather all to include acid rain
    //no this isn't just thunder affects hurricane etc.
    //ok nvm the nvm acid rain CAN occur in thunderstorms
    if (!effect && HasWeatherEffect())
    {
        if (MoveAlwaysHitsInRain(move) && IsBattlerWeatherAffected(battlerDef, WEATHER_RAIN_ALL))
            effect = TRUE;
        else if (MoveAlwaysHitsInHailSnow(move) && IsBattlerWeatherAffected(battlerDef, WEATHER_ICY_ANY))
            effect = TRUE;

        if (effect)
            return effect;
    }

    if (ability != ABILITY_NONE && option == RUN_SCRIPT)
        RecordAbilityBattle(battlerAtk, ability);

    return effect;
}

u32 GetTotalAccuracy(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, enum Ability atkAbility, enum Ability defAbility, enum HoldEffect atkHoldEffect, enum HoldEffect defHoldEffect)
{
    u32 calc, moveAcc;
    s8 buff, accStage, evasionStage;
    u32 atkParam = GetBattlerHoldEffectParam(battlerAtk);
    u32 defParam = GetBattlerHoldEffectParam(battlerDef);

    gPotentialItemEffectBattler = battlerDef;
    accStage = gBattleMons[battlerAtk].statStages[STAT_ACC];
    evasionStage = gBattleMons[battlerDef].statStages[STAT_EVASION];
    if (gProtectStructs[battlerDef].oneTurnStatBoost == STAT_EVASION)
        evasionStage += 2;
    if (atkAbility == ABILITY_UNAWARE || atkAbility == ABILITY_KEEN_EYE || atkAbility == ABILITY_MINDS_EYE || atkAbility == ABILITY_APOTHEOSCENT)
        evasionStage = DEFAULT_STAT_STAGE;
    if (MoveIgnoresDefenseEvasionStages(move))
        evasionStage = DEFAULT_STAT_STAGE;
    if (defAbility == ABILITY_UNAWARE)
        accStage = DEFAULT_STAT_STAGE;

    if (gBattleMons[battlerDef].volatiles.foresight || gBattleMons[battlerDef].volatiles.miracleEye)
        buff = accStage;
    else
        buff = accStage + DEFAULT_STAT_STAGE - evasionStage;

    if (buff < MIN_STAT_STAGE)
        buff = MIN_STAT_STAGE;
    if (buff > MAX_STAT_STAGE)
        buff = MAX_STAT_STAGE;

    //moveAcc = GetMoveAccuracy(move);

    //should work gets acc check if fury cutter
    //otherwise just sets normal move acc
    moveAcc = GetFuryCutterAccuracy(move, battlerAtk);

    //cacophony boost
    if (ShouldCacophonyBoostAccuracy(move))
        moveAcc = 100;

    if (IsBattlerWeatherAffected(battlerAtk, WEATHER_INCLEMENT)
    && move == MOVE_SPORE)
        moveAcc = 85;
            
    // Check Thunder and Hurricane on sunny weather.
    if (IsBattlerWeatherAffected(battlerDef, WEATHER_SUN) && MoveHas65AccuracyInSun(move))
        moveAcc = 65; //made slightly more forgiving
    // Check Wonder Skin.
    if ((defAbility == ABILITY_WONDER_SKIN
        || defAbility == ABILITY_IMMUTABLE_WIND) 
        && IsBattleMoveStatus(move) && moveAcc > 50)
        moveAcc = 50;

    if (atkAbility == ABILITY_SPACE_CONTROL
        && !IsBattleMoveStatus(move)
        && moveAcc != 0)
            moveAcc = 100;
    
    if (FugueActivatesSleep(battlerAtk, battlerDef, atkAbility, move)
    && moveAcc < 95 && moveAcc != 0)
        moveAcc = 95;

    calc = gAccuracyStageRatios[buff].dividend * moveAcc;
    calc /= gAccuracyStageRatios[buff].divisor;


    #define FLYING_TYPE_BONUS
        if (IsBattlerGrounded_IgnoreException(battlerAtk, atkAbility, atkHoldEffect)
        && !IsBattlerGrounded_IgnoreException(battlerDef, defAbility, defHoldEffect) //make function for below
        && (DoesBattlerGetTypeBasedAffinity(atkAbility, battlerDef, defAbility, TYPE_FLYING, FALSE)
        || DoesBattlerGetTypeBasedAffinity(atkAbility, battlerDef, defAbility, TYPE_WIND, FALSE))
        && atkAbility != ABILITY_KEEN_EYE
        && atkAbility != ABILITY_MINDS_EYE
        && atkAbility != ABILITY_APOTHEOSCENT
        && !MoveCanDamageAirborne(gCurrentMove)
        && !MoveSureHitEvasionBoostedTargets(gCurrentMove)
        )
            calc = (calc * 88) / 100;  //was 93, dropped to 88 - think i sfine where is at most drop to 87 want keep above sand veil likes
        //think may lower this a bit more?  
        //if I drop to .8 (won't actually) it'd effectively be enough to lower a stat stage drop to the next stage down

    // Attacker's ability
    switch (atkAbility)
    {
    case ABILITY_ILLUMINATE:
    case ABILITY_COMPOUND_EYES:
        calc = (calc * 130) / 100; // 1.3 compound eyes boost
        break;
    case ABILITY_VICTORY_STAR:
        calc = (calc * 120) / 100; // 1.1 victory star boost
        break;
    case ABILITY_KEEN_EYE:
        calc = (calc * 115) / 100;
        break;
    case ABILITY_HUSTLE:
        if (IsBattleMovePhysical(move))
            calc = (calc * 95) / 100; // 1.2 hustle loss
        break;
    default:
        break;
    }

        //when I get around to it, safety goggles item should also go on these I thnk
        //hold effect already set but think will just setup like umbrella
        //done wrapped it into weather affected
        //added sixth sense as an ability not meant to relyon eyes
        //sand stream is not here beacuse it explicitly does not give weather immunity
        if (IsBattlerWeatherAffected(battlerAtk, WEATHER_SANDSTORM) 
        && !(MoveSureHitEvasionBoostedTargets(gCurrentMove))
        && !DoesBattlerGetTypeBasedAffinity(atkAbility, battlerAtk, atkAbility, TYPE_ROCK, TRUE)
        && !DoesBattlerGetTypeBasedAffinity(atkAbility, battlerAtk, atkAbility, TYPE_STEEL, TRUE)
        && !DoesBattlerGetTypeBasedAffinity(atkAbility, battlerAtk, atkAbility, TYPE_GROUND, TRUE)
        && atkAbility != ABILITY_SAND_RUSH
        && atkAbility != ABILITY_SAND_VEIL
        && atkAbility != ABILITY_SAND_FORCE
        && atkAbility != ABILITY_APOTHEOSCENT
        && atkAbility != ABILITY_DUST_DEVIL
        && atkAbility != ABILITY_WIND_RIDER    //addition since is wind move
        && !DoesSideHaveAbility(battlerAtk, ABILITY_CLOUD_NINE) //need test hope works
        && GetBaseFormSpecies(gBattleMons[battlerAtk].species) != SPECIES_CASTFORM)
            calc = (calc * 90) / 100; // new 10% sandstorm loss (extra effect given since hail got extra stuff) changed to 5%, changed back given mudsport changes

        //trap effect,
        if (((gBattleMons[battlerAtk].volatiles.sandtomb)
       )
        && !(MoveSureHitEvasionBoostedTargets(gCurrentMove))
        && !DoesBattlerGetTypeBasedAffinity(atkAbility, battlerAtk, atkAbility, TYPE_ROCK, TRUE)
        && !DoesBattlerGetTypeBasedAffinity(atkAbility, battlerAtk, atkAbility, TYPE_STEEL, TRUE)
        && !DoesBattlerGetTypeBasedAffinity(atkAbility, battlerAtk, atkAbility, TYPE_GROUND, TRUE)
        && atkAbility != ABILITY_SAND_RUSH
        && atkAbility != ABILITY_SAND_VEIL
        && atkAbility != ABILITY_SAND_FORCE
        && atkAbility != ABILITY_APOTHEOSCENT
        && GetBaseFormSpecies(gBattleMons[battlerAtk].species) != SPECIES_CASTFORM) //change tobe base form as can't remember if changes species on weather
        {
            calc = (calc * 90) / 100; //since most mon that have this also have access to sandstorm or are in desert made less punishing
            //moveAcc = (moveAcc * 60) / 100; //euivalent of a 2 stage acc drop
        }//leaving keen eye and sixth sense out of this and sandstorm acc drop, 
        //as special exclusions to strengthen affect/mechanic

    // Target's ability
    switch (defAbility)
    {
        //to make not too oppressive think will lower effect
        //since it stacks with weather drop (requires weather)
    case ABILITY_SAND_VEIL:
        if (IsBattlerWeatherAffected(battlerAtk, WEATHER_SANDSTORM)
        && !(MoveSureHitEvasionBoostedTargets(gCurrentMove)))
            calc = (calc * 89) / 100; // 1.2 sand veil loss
        break;
        //vsonic come back to this deciding how to split out snow hail effects
    case ABILITY_SNOW_CLOAK:
        if (IsBattlerWeatherAffected(battlerAtk, WEATHER_ICY_ANY)
        && !(MoveSureHitEvasionBoostedTargets(gCurrentMove)))
            calc = (calc * 80) / 100; // 1.2 snow cloak loss
        break;
    case ABILITY_TANGLED_FEET:
        if (gBattleMons[battlerDef].volatiles.confusionTurns)
            calc = (calc * 67) / 100; // 1.5 tangled feet loss
            //rebalanced
            //evasionStage *= 2;//raises evasion double but evasion calcs different so thats +3 intead of +2
        break;
    default:
        break;
    }

    //status based Acc effects
    if (gBattleMons[battlerDef].volatiles.infatuatedwithMon) //need to figure out how to lower evasion to go along with these accuracy boosts.
            calc = (calc * 140) / 100;
    if ((gBattleMons[battlerDef].volatiles.confusionTurns) && defAbility != ABILITY_TANGLED_FEET)
            calc = (calc * 120) / 100;
    if (IsBattlerTrappedViaMove(battlerDef))
                calc = (calc * 115) / 100;//  should still select normally before hand, but it just change when executed.
    if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP) { //.target = MOVE_TARGET_SELECTED, 
        if (DoesBattlerGetTypeBasedAffinity(atkAbility, battlerDef, defAbility, TYPE_PSYCHIC, FALSE)) //important chek this think have function for type checking
            calc = (calc * 105) / 100; // to take advantage of these buffs I want to have a button to display real move accuracy in battle. maybe L
        else
            calc = (calc * 160) / 100;
    }
    if (gBattleMons[battlerDef].status1 & STATUS1_BURN)
                   calc = (calc * 110) / 100;
            //evasionStage = 4;
        if (gBattleMons[battlerDef].status1 & STATUS1_POISON) // I think I may remove the accuracy buff and just keep evasion drop, or make it more severe.
            calc = (calc * 110) / 100; //depends on how evasion works, if lowered evasion alone increases chance of move hitting, then I don't need accuracy buff.
         //   evasionStage = 4;
        if (gBattleMons[battlerDef].status1 & STATUS1_FREEZE)
            calc = (calc * 160) / 100;
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS) //ok evasion and accuracy stages are put together, so I'll just use evasion.
            calc = (calc * 130) / 100;
          //  evasionStage = 3;
        if (gBattleMons[battlerDef].status1 & STATUS1_TOXIC_POISON)
            calc = (calc * 115) / 100;

    // Attacker's ally's ability
    u32 atkAlly = BATTLE_PARTNER(battlerAtk);
    switch (GetBattlerAbility(atkAlly))
    {
    case ABILITY_VICTORY_STAR:
        if (IsBattlerAlive(atkAlly))
            calc = (calc * 120) / 100; // 1.1 ally's victory star boost
        break;
    default:
        break;
    }

    // Attacker's hold effect
    switch (atkHoldEffect)
    {
    case HOLD_EFFECT_WIDE_LENS:
        calc = (calc * (100 + atkParam)) / 100;
        break;
    case HOLD_EFFECT_ZOOM_LENS:
        if (HasBattlerActedThisTurn(battlerDef))
            calc = (calc * (100 + atkParam)) / 100;
        break;//vsonic coulda sworn I reworked one of these to be more unique
    default:
        break;
    }

    // Target's hold effect
    switch (defHoldEffect)
    {
    case HOLD_EFFECT_EVASION_UP:
        calc = (calc * (100 - defParam)) / 100;
        break;
    default:
        break;
    }

    if (gBattleStruct->battlerState[battlerAtk].usedMicleBerry)
    {
        // TODO: Is this true?
        if (atkAbility == ABILITY_RIPEN)
            calc = (calc * 140) / 100;  // ripen gives 40% acc boost
        else
            calc = (calc * 120) / 100;  // 20% acc boost
    }

    //go through and replace most cases of
    //of unnecessary status w just timer
    if (gFieldStatuses & STATUS_FIELD_GRAVITY)
        calc = (calc * 5) / 3; // 1.66 Gravity acc boost


    return calc;
}

bool32 IsSemiInvulnerable(enum BattlerId battler, enum SemiInvulnerableExclusion excludeCommander)
{
    if (gBattleMons[battler].volatiles.semiInvulnerable == STATE_COMMANDER)
        return excludeCommander != EXCLUDE_COMMANDER;
    return gBattleMons[battler].volatiles.semiInvulnerable != STATE_NONE;
}

//lil weird but uses ability argument for efficiency,
//passing argument from original call rather than recalling function
bool32 BreaksThroughSemiInvulnerablity(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum Move move)
{
    enum SemiInvulnerableState state = gBattleMons[battlerDef].volatiles.semiInvulnerable;

    if (state != STATE_COMMANDER)
    {
        if (move == MOVE_TOXIC && DoesBattlerGetTypeBasedAffinity(abilityAtk, battlerDef, abilityDef, TYPE_POISON, FALSE))
            return TRUE;
        if (IsSureHitAbility(abilityAtk) || IsSureHitAbility(abilityDef))
            return TRUE;
        if (gBattleMons[battlerDef].volatiles.lockOn && gBattleMons[battlerDef].volatiles.battlerWithSureHit == battlerAtk)
            return TRUE;
    }

    switch (state)
    {
    case STATE_UNDERGROUND:
        return MoveDamagesUnderground(move);
    case STATE_UNDERWATER:
        return MoveDamagesUnderWater(move);
    case STATE_ON_AIR:
    case STATE_SKY_DROP:
        return MoveDamagesAirborne(move) || MoveDamagesAirborneDoubleDamage(move);
    case STATE_PHANTOM_FORCE:
        return FALSE;
    case STATE_COMMANDER:
        return GetMoveEffect(move) == EFFECT_TRANSFORM;
    case STATE_NONE:
    case SEMI_INVULNERABLE_COUNT:
        return TRUE;
    }

    return FALSE;
}

bool32 HasPartnerTrainer(enum BattlerId battler)
{
    if ((GetBattlerSide(battler) == B_SIDE_PLAYER && gBattleTypeFlags & BATTLE_TYPE_PLAYER_HAS_PARTNER)
     || (GetBattlerSide(battler) == B_SIDE_OPPONENT && gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS))
        return TRUE;
    else
        return FALSE;
}

static bool32 IsOpposingSideEmpty(enum BattlerId battler)
{
    u32 oppositeBattler = BATTLE_OPPOSITE(battler);

    if (IsBattlerAlive(oppositeBattler))
        return FALSE;

    if (!IsDoubleBattle())
        return TRUE;

    if (IsBattlerAlive(BATTLE_PARTNER(oppositeBattler)))
        return FALSE;
    return TRUE;
}

//VSONIC add affinity check ADD atk ability here for affinity check
bool32 IsAffectedByPowderMove(enum BattlerId battler, enum Ability ability, enum Ability atkAbility, enum HoldEffect holdEffect)
{
    if ((ability == ABILITY_OVERCOAT)
        || DoesBattlerGetTypeBasedAffinity(atkAbility, battler, ability, TYPE_GRASS, FALSE)
        || holdEffect == HOLD_EFFECT_SAFETY_GOGGLES)
        return FALSE;
    return TRUE;
}

//may be a few more suicide moves I'll have to add to this
//only reason have to add healing wish is user fainting is part of effect
//tied in so much that move script opens party menu to force switch
//fixed effect now works one time per on field so requires
//healing and switching out and back in to reset
//making it abusable but not completely free
//believe still need setup gbattlemovedamage change to fully work
bool8 CanSurviveInstantKOWithSturdy(enum BattlerId battler)
{
    if (GetBattlerAbility(battler) == ABILITY_STURDY
    && gBattleMons[battler].hp >= (gBattleMons[battler].maxHP / 4)//think need to change this, without an indicator Im' just recreating the in a pinch problem
    && gMovesInfo[gCurrentMove].effect != EFFECT_HEALING_WISH //better to change it to when hp becomes red?
    && !gBattleMons[battler].volatiles.sturdyhungon)
    {
        return TRUE;
    }
    return FALSE;
}

//for some reason wasn't tracking propery
//for type effect display w mold breaker
//but making movetype an argument fixed issue
bool8 IsFloatingTargetImmunetoGroundBasedMoves(enum BattlerId battler_def, enum Ability abilityAtk, enum Ability abilityDef, u16 move)
{

    //is a bit confusing no guard hits semi invulnerable
    //but invulnerabilities are ignored
    //in my thing ground vs flying technically isn't an immunity
    //but a mechanic ok it makes sense logically
    //if it can hit through semi invulnerablility
    //even flying high in the air it should hit this
    //but is a major balance inflection point
    //making too many mon with these abilities
    //would break flying types
    if (MoveCantDamageFloatingTargets(move) && !IsBattlerGrounded_IgnoreException(battler_def, abilityDef, GetBattlerHoldEffect(battler_def)))
    {

        if ((abilityAtk == ABILITY_MOLD_BREAKER)
        || (IsSureHitAbility(abilityAtk) || IsSureHitAbility(abilityDef)))
            return FALSE;
        else
            return TRUE;
    }

    return FALSE;
}

//for use in party menu
bool8 CanActivateExpShare(void)
{
    if (FlagGet(FLAG_NEW_GAME_PLUS) || FlagGet(FLAG_GOT_EXP_SHARE))
        return TRUE;
    return FALSE;
}

bool8 CanActivateExpNull(void)
{
    if (FlagGet(FLAG_NEW_GAME_PLUS) || FlagGet(FLAG_GOT_EXP_NULL_FROM_MOM))
        return TRUE;
    return FALSE;
}

//put in acc check if true set to acc to 100
//make sure to put high enough it can take effect but still be affected
//by other accuracy factors
//for sound status moves that change stat stage at above stage 1
//vsonic important do these effects better, better condition
//that categorizes what has what effect and why
//if can do that can potentially consolidate functions
//do state return based on condition
bool8 ShouldCacophonyBoostAccuracy(u16 move)
{


    if (gMovesInfo[move].category == DAMAGE_CATEGORY_STATUS && gSpecialStatuses[gBattlerAttacker].Cacophonyboosted
    &&  (move == MOVE_METAL_SOUND
    || move == MOVE_SCREECH))
        return TRUE;
    else
        return FALSE;
}

//double relevant effect chance
//sound moves w effects not including sleep or confusion
//think had that wrong, was thinking of ...
//nah well long as sleep chance is low should be fine
bool8 ShouldCacophonyBoostEffectChance(u16 move)
{

    //uses secondary effect chance
    if (gSpecialStatuses[gBattlerAttacker].Cacophonyboosted
    && (move == MOVE_CLANGING_SCALES
    || move == MOVE_OVERDRIVE
    || move == MOVE_SONIC_BOOM
    || move == MOVE_SONIC_SCREECH
    || move == MOVE_SNORE
    || move == MOVE_HYPER_VOICE
    || move == MOVE_ASTONISH
    || move == MOVE_BUG_BUZZ
    || move == MOVE_CHATTER
    || move == MOVE_ECHOED_VOICE
    || move == MOVE_RELIC_SONG
    || move == MOVE_DISARMING_VOICE))
        return TRUE;
    //for moves thata use argument chance
    /*else if (gSpecialStatuses[gBattlerAttacker].Cacophonyboosted
    && (move == MOVE_CLANGING_SCALES))
        return TRUE;*/
    else
        return FALSE;
}

//two part companion function
//for dmging sound based mvoes that change stat stage
//at lvl 1, most done in script but this is for generic ones
//without unique move effect  ex. effect attack down hit
//use snarl to test if affect works
bool8 ShouldCacophonyElevateMoveEffect(u16 move)
{
    if (gSpecialStatuses[gBattlerAttacker].Cacophonyboosted
    && (move == MOVE_BUG_BUZZ
    || move == MOVE_SNARL
    || move == MOVE_DISARMING_VOICE))
        return TRUE;
    else
        return FALSE;
}

void CacophonyElevateMoveEffect(void)
{
    switch (gBattleScripting.moveEffect)
    {
        case MOVE_EFFECT_ATK_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_ATK_PLUS_2;
                break;
            case MOVE_EFFECT_DEF_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_DEF_PLUS_2;
                break;
            case MOVE_EFFECT_SPD_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_SPD_PLUS_2;
                break;
            case MOVE_EFFECT_SP_ATK_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_SP_ATK_PLUS_2;
                break;
            case MOVE_EFFECT_SP_DEF_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_SP_DEF_PLUS_2;
                break;
            case MOVE_EFFECT_ACC_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_ACC_PLUS_2;
                break;
            case MOVE_EFFECT_EVS_PLUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_EVS_PLUS_2;
                break;
            case MOVE_EFFECT_ATK_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_ATK_MINUS_2;
                break;
            case MOVE_EFFECT_DEF_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_2;
                break;
            case MOVE_EFFECT_SPD_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_2;
                break;
            case MOVE_EFFECT_SP_ATK_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2;
                break;
            case MOVE_EFFECT_SP_DEF_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2;
                break;
            case MOVE_EFFECT_ACC_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_ACC_MINUS_2;
                break;
            case MOVE_EFFECT_EVS_MINUS_1:
            gBattleScripting.moveEffect = MOVE_EFFECT_EVS_MINUS_2;
                break;
            break;
    }
}

void RemoveAbilityFlags(enum BattlerId battler)
{
    switch (GetBattlerAbility(battler))
    {
    case ABILITY_FLASH_FIRE:
        gBattleMons[battler].volatiles.flashFireBoosted = FALSE;
        break;
    case ABILITY_VESSEL_OF_RUIN:
        gBattleMons[battler].volatiles.vesselOfRuin = FALSE;    //SP ATK
        break;
    case ABILITY_TABLETS_OF_RUIN:
        gBattleMons[battler].volatiles.tabletsOfRuin = FALSE;   //SPEED
        break;
    case ABILITY_SWORD_OF_RUIN:
        gBattleMons[battler].volatiles.swordOfRuin = FALSE; //DEF
        break;
    case ABILITY_BEADS_OF_RUIN:
        gBattleMons[battler].volatiles.beadsOfRuin = FALSE; //SP DEF
        break;
    default:
       break;
    }
}

void CheckSetUnburden(enum BattlerId battler)
{
    if (IsAbilityAndRecord(battler, GetBattlerAbility(battler), ABILITY_UNBURDEN))
        gBattleMons[battler].volatiles.unburdenActive = TRUE;
}

bool32 IsAnyTargetTurnDamaged(enum BattlerId battlerAtk)
{
    for (enum BattlerId battlerDef = 0; battlerDef < gBattlersCount; battlerDef++)
    {
        if (battlerDef == battlerAtk)
            continue;
        if (IsBattlerTurnDamaged(battlerDef))
            return TRUE;
    }
    return FALSE;
}

bool32 IsAnyTargetAffected(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (battler == gBattlerAttacker)
            continue;

        if (!IsBattlerUnaffectedByMove(battler))
            return TRUE;
    }
    return FALSE;
}

//not using
bool32 IsAllowedToUseBag(void)
{
    switch(VarGet(B_VAR_NO_BAG_USE))
    {
    case NO_BAG_RESTRICTION:
        return TRUE;
    case NO_BAG_AGAINST_TRAINER: //True in wild battle; False in trainer battle
        return (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER));
    case NO_BAG_IN_BATTLE:
        return FALSE;
    default:
        return TRUE; // Undefined Behavior
    }
}

//since plan make heal block ability affect/antiheal
//and there are moves that do single target healblock
//think best idea to make function for healblockaffected
//to consolidate said effects
// vsonic
bool32 CanBattlerHeal(enum BattlerId battlerId)
{
    if (IsBattlerAlive(battlerId))
    {

        if (IsBattlerAtMaxHp(battlerId) 
        || (gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
            return FALSE;
        
        return TRUE;
    }
    
    return FALSE;
}

//unsure if using, have singlueuseability logic
//can rely on
bool32 IsMimikyuDisguised(enum BattlerId battler)
{
    return gBattleMons[battler].species == SPECIES_MIMIKYU_DISGUISED;
        //|| gBattleMons[battler].species == SPECIES_MIMIKYU_TOTEM_DISGUISED;
}

//attempt reurn if battelr is on field w alive check
//can use hopefully to clean up summary screen functions
//changed make return battler for easy app into summary funcions
//BATTLER id only needed for getting correct side
//ok revised should check if mon at position is alive
//and matches personality of mon at pos with that of current viewing summ mon
//doesn't check all player side of field, only checks specific position
//mostly used for poke sumary screen battle update logic
bool8 IscurrentMonOnFieldAtPos(struct Pokemon *mon, u8 position)
{

    
    u8 battler = GetBattlerAtPosition(position);
    u8 side = GetBattlerSide(battler);
    u32 battler_personality = gBattleMons[battler].personality;
    u32 mon_personality = GetMonData(mon, MON_DATA_PERSONALITY);

    if (IsBattlerAlive(battler) && IsOnPlayerSide(battler)
    && battler_personality == mon_personality)
        return TRUE;

    return FALSE;


}

//these two functions are put in end turn so self affectings
bool32 TryActivateBattlePoisonHeal(enum BattlerId battler)  //change mind better to do 2 functions, rather than do 2 different effects with one.
{
    u16 ability = GetBattlerAbility(battler);

    if (!gProtectStructs[battler].activatedAbilityStatusHealing
    && (ability == ABILITY_POISON_HEAL && IsBattlerAlive(battler)))
    {

        if (gBattleMons[battler].status1 & STATUS1_POISON
            || gBattleMons[battler].status1 & STATUS1_TOXIC_POISON
            || IsBattlerWeatherAffected(battler, WEATHER_ACID_RAIN))
        {
            return TRUE;
        }

        else if (DoesBattlerGetTypeBasedAffinity(ability, battler, ability, TYPE_POISON, TRUE) 
            && ((GetBattlerHoldEffect(battler) == HOLD_EFFECT_BLACK_SLUDGE)
            || (GetBattlerHoldEffect(battler) == HOLD_EFFECT_TOXIC_ORB)))
        {
            return TRUE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;

    
}

//fire type poison healing mostly for capsakid/scovillain
//ok yeah think I'm fine with this activating in sun too
//is on fire type to begin with so I'd never get burned in a normal playthrough
bool32 TryActivateHeatTrance(enum BattlerId battler)  //change mind better to do 2 functions, rather than do 2 different effects with one.
{

    u16 ability = GetBattlerAbility(battler);

    if (!gProtectStructs[battler].activatedAbilityStatusHealing
    && (ability == ABILITY_HEAT_TRANCE && IsBattlerAlive(battler)))
    {

        if (gBattleMons[battler].status1 & STATUS1_BURN
            || IsBattlerWeatherAffected(battler, WEATHER_SUN) //may keep?
            )
        {
            return TRUE;
        }

        //since I already stipulated ability is heat trance this is fine
        //it just means is fire type
        else if (DoesBattlerGetTypeBasedAffinity(ability, battler, ability, TYPE_FIRE, TRUE) 
            && ((GetBattlerHoldEffect(battler) == HOLD_EFFECT_FLAME_ORB)))
        {
            return TRUE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;

    
}

//can't use before use move battle controller is done
//because called move & gcurrent move aren't set until its used
//need execute as part of bs (??)
//not same as EE version of function prob rename later
//rn only using for charge status
//got removed unsure if still need
/*enum Type GetMoveType(u32 moveType, u32 btlAttacker)
{
    u16 move; //move should be current move unless move that calls move than instead is calledmove
    u8 Type, moveArgument;

    move = gCalledMove == 0 ? gCurrentMove : gCalledMove;
    moveArgument = 0xFE;
    SetTypeBeforeUsingMove(move, btlAttacker, &Type);
    //GET_MOVE_TYPE(move, Type); //need add argument type, for two type move

    if (gMovesInfo[move].effect == EFFECT_TWO_TYPED_MOVE)
        moveArgument = gMovesInfo[move].argument;
    
    if ((Type || moveArgument) == moveType)
        return Type;
    else
        return TYPE_NONE; //return this if not find type to avoid issue w type none


}*/

#define FIXATION_EFFECTS
//present form useless plan rework
//to instead check for fixated status
//ex. volatile dmg fixation
bool8 IsFixationMoveEffect(u16 move)
{
    switch (GetMoveEffect(move))
    {
        case EFFECT_FIXATION:
            return TRUE;
            break;
        default:
            return FALSE;
    }
}

bool8 CanActivateForewarnAnticipation(enum BattlerId battler)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetBattlerPartyState(i)->usedSingleUseAbility == ABILITY_ANTICIPATION
        || GetBattlerPartyState(i)->usedSingleUseAbility == ABILITY_FOREWARN)
            break;
    }

    //can activate only if none has used it i party
    //so i is party size means that's true
    return (i == PARTY_SIZE);

}

u32 IsPersonalityOnSide(enum BattlerId battlerId, u32 MonPid)
{
    if (IsBattlerAlive(battlerId) && GetMonData(GetBattlerMon(battlerId), MON_DATA_PERSONALITY) == MonPid)
        return battlerId + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battlerId)) && GetMonData(GetBattlerMon(BATTLE_PARTNER(battlerId)), MON_DATA_PERSONALITY) == MonPid)
        return BATTLE_PARTNER(battlerId) + 1;
    else
        return FALSE;
}

u32 IsMonOnOpposingSide(enum BattlerId battlerId, u32 MonPid)
{
    return IsPersonalityOnSide(BATTLE_OPPOSITE(battlerId), MonPid);
}

u32 GetBattlerFromPersonality(u32 MonPid)
{
    for (u32 i = 0; i < gBattlersCount; i++)
    {
        if (GetMonData(GetBattlerMon(i), MON_DATA_PERSONALITY) == MonPid)
            return i;
    }

    return BATTLE_ID_NONE;
}

#define UNPACK_STARTING_STATUS_TO_EWRAM(_enum, _fieldName, ...) case _enum: gStartingStatuses._fieldName = TRUE; break;

void SetStartingStatus(enum StartingStatus status)
{
    switch (status)
    {
    STARTING_STATUS_DEFINITIONS(UNPACK_STARTING_STATUS_TO_EWRAM);
    }
}

#define UNPACK_STARTING_STATUS_RESET(_enum, _fieldName, ...) gStartingStatuses._fieldName = FALSE;

//what are these
void ResetStartingStatuses(void)
{
    STARTING_STATUS_DEFINITIONS(UNPACK_STARTING_STATUS_RESET);
}

bool32 IsUsableWhileAsleepEffect(enum BattleMoveEffects effect)
{
    // All moves usable while asleep like Snore, Sleep Talk, etc.
    switch (effect)
    {
    case EFFECT_SNORE:
    case EFFECT_SLEEP_TALK:
        return TRUE;
    default:
        return FALSE;
    }
}

//may remove
void SetWrapTurns(enum BattlerId battler, enum HoldEffect holdEffect)
{
    u32 normalWrapTurns = B_WRAP_TURNS - 2; // 5 turns
    if (holdEffect == HOLD_EFFECT_GRIP_CLAW)
        gBattleMons[battler].volatiles.wrapTurns = GetConfig(B_BINDING_TURNS) >= GEN_5 ? B_WRAP_TURNS : normalWrapTurns;
    else
        gBattleMons[battler].volatiles.wrapTurns = GetConfig(B_BINDING_TURNS) >= GEN_5 ? RandomUniform(RNG_WRAP, 4, normalWrapTurns) : RandomUniform(RNG_WRAP, 2, normalWrapTurns);
}

// Return True if the order was changed, and false if the order was not changed(for example because the target would move after the attacker anyway).
bool32 ChangeOrderTargetAfterAttacker(void)
{
    u32 i;
    u8 data[MAX_BATTLERS_COUNT];
    u8 actionsData[MAX_BATTLERS_COUNT];
    u32 attackerTurnOrderNum = GetBattlerTurnOrderNum(gBattlerAttacker);
    u32 targetTurnOrderNum = GetBattlerTurnOrderNum(gBattlerTarget);

    if (attackerTurnOrderNum > targetTurnOrderNum)
        return FALSE;
    if (attackerTurnOrderNum + 1 == targetTurnOrderNum)
        return GetConfig(B_AFTER_YOU_TURN_ORDER) >= GEN_8;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        data[i] = gBattlerByTurnOrder[i];
        actionsData[i] = gActionsByTurnOrder[i];
    }
    if (attackerTurnOrderNum == 0 && targetTurnOrderNum == 2)
    {
        gBattlerByTurnOrder[1] = gBattlerTarget;
        gActionsByTurnOrder[1] = actionsData[2];
        gBattlerByTurnOrder[2] = data[1];
        gActionsByTurnOrder[2] = actionsData[1];
    }
    else if (attackerTurnOrderNum == 0 && targetTurnOrderNum == 3)
    {
        gBattlerByTurnOrder[1] = gBattlerTarget;
        gActionsByTurnOrder[1] = actionsData[3];
        gBattlerByTurnOrder[2] = data[1];
        gActionsByTurnOrder[2] = actionsData[1];
        gBattlerByTurnOrder[3] = data[2];
        gActionsByTurnOrder[3] = actionsData[2];
    }
    else // attackerTurnOrderNum == 1, targetTurnOrderNum == 3
    {
        gBattlerByTurnOrder[2] = gBattlerTarget;
        gActionsByTurnOrder[2] = actionsData[3];
        gBattlerByTurnOrder[3] = data[2];
        gActionsByTurnOrder[3] = actionsData[2];
    }
    return TRUE;
}

//vsonic pretty sure not using
void TryUpdateEvolutionTracker(u32 evolutionCondition, u32 upAmount, enum Move usedMove)
{
    /*u32 i, j;

    if (IsOnPlayerSide(gBattlerAttacker)
     && ((TESTING && IsDoubleBattle()) // To be removed when Wild Double Battles are added to tests
     || !(gBattleTypeFlags & (BATTLE_TYPE_LINK    
                             | BATTLE_TYPE_EREADER_TRAINER
                             | BATTLE_TYPE_RECORDED_LINK
                             | BATTLE_TYPE_TRAINER_HILL
                             | BATTLE_TYPE_FRONTIER))))
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(gBattleMons[gBattlerAttacker].species);
        if (evolutions == NULL)
            return;

        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;
            if (evolutions[i].params == NULL)
                continue;

            for (j = 0; evolutions[i].params[j].condition != CONDITIONS_END; j++)
            {
                if (evolutions[i].params[j].condition != evolutionCondition)
                    continue;

                struct Pokemon *monAtk = GetBattlerMon(gBattlerAttacker);
                struct Pokemon *monDef = GetBattlerMon(gBattlerTarget);
                // We only have 10 bits to use
                u16 val = min(1023, GetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER) + upAmount);
                // Reset progress if you faint for the recoil method.
                switch (evolutionCondition)
                {
                case IF_USED_MOVE_X_TIMES:
                    if (evolutions[i].params[j].arg1 == usedMove)
                        SetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER, &val);
                    break;
                case IF_RECOIL_DAMAGE_GE:
                    if (gBattleMons[gBattlerAttacker].hp == 0)
                        val = 0;
                    SetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER, &val);
                    break;
                case IF_DEFEAT_X_WITH_ITEMS:
                    if (GetMonData(monDef, MON_DATA_SPECIES) == evolutions[i].params[j].arg1
                     && GetMonData(monDef, MON_DATA_HELD_ITEM) == evolutions[i].params[j].arg2)
                        SetMonData(monAtk, MON_DATA_EVOLUTION_TRACKER, &val);
                    break;
                }
                return;
            }
        }
    }*/
}

static const u16 sProtectSuccessRates[] =
{
    USHRT_MAX,
    USHRT_MAX / 2,
    USHRT_MAX / 4,
    USHRT_MAX / 8
};

static const u16 sGen5ProtectSuccessRates[] =
{
    USHRT_MAX,
    USHRT_MAX / 3,
    USHRT_MAX / 9,
    USHRT_MAX / 27
};

bool32 CanUseMoveConsecutively(enum BattlerId battler)
{
    u32 moveUses = gBattleMons[battler].volatiles.consecutiveMoveUses;
    if (moveUses >= ARRAY_COUNT(sProtectSuccessRates))
        moveUses = ARRAY_COUNT(sProtectSuccessRates) - 1;

    u32 successRate = sGen5ProtectSuccessRates[moveUses];
    if (B_PROTECT_FAILURE_RATE < GEN_5)
        successRate = sProtectSuccessRates[moveUses];

    return successRate >= RandomUniform(RNG_PROTECT_FAIL, 0, USHRT_MAX);
}

// Used for Protect, Endure and Ally switch
void TryResetConsecutiveUseCounter(enum BattlerId battler)
{
    u32 lastMove = gLastResultingMoves[battler];
    if (lastMove == MOVE_UNAVAILABLE)
    {
        gBattleMons[battler].volatiles.consecutiveMoveUses = 0;
        return;
    }

    enum BattleMoveEffects lastEffect = GetMoveEffect(lastMove);
    if (!gBattleMoveEffects[lastEffect].usesProtectCounter)
    {
        if (GetConfig(B_ALLY_SWITCH_FAIL_CHANCE) < GEN_9 || lastEffect != EFFECT_ALLY_SWITCH)
            gBattleMons[battler].volatiles.consecutiveMoveUses = 0;
    }
}

void SetOrClearRageVolatile(void)
{
    if (GetConfig(B_RAGE_BUILDS) <= GEN_3 && MoveHasAdditionalEffect(gCurrentMove, MOVE_EFFECT_RAGE))
        gBattleMons[gBattlerAttacker].volatiles.rage = TRUE;
    else
        gBattleMons[gBattlerAttacker].volatiles.rage = FALSE;
}

//initialsetup was turn off rage but keep counter
//unsure if still want that
void ClearRageStatuses(enum BattlerId battler) //remove rage if  move used other than rage, changed so just don't call this
{
    //gBattleMons[gBattlerAttacker].volatiles.rageCounter = 0;  don't reset counter so keep power boosts, 
    //gBattleMons[battler].volatiles.rage = FALSE);
    gBattleMons[battler].volatiles.rage = FALSE;
    gBattleMons[battler].volatiles.rageCounter = 0;
}
