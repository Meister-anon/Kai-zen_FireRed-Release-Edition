#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_terastal.h"
#include "battle_gimmick.h"
#include "battle_scripts.h"
#include "event_data.h"
#include "item.h"
#include "palette.h"
#include "pokemon.h"
#include "safari_zone.h"
#include "sprite.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/rgb.h"

// Sets flags and variables upon a battler's Terastallization.
void ActivateTera(enum BattlerId battler)
{
    // Set appropriate flags.
    SetActiveGimmick(battler, GIMMICK_TERA);
    SetGimmickAsActivated(battler, GIMMICK_TERA);

    // Remove Tera Orb charge.
    if (B_FLAG_TERA_ORB_CHARGED != 0
        && (B_FLAG_TERA_ORB_NO_COST == 0 || !FlagGet(B_FLAG_TERA_ORB_NO_COST))
        && IsOnPlayerSide(battler)
        && !(IsDoubleBattle() && !IsPartnerMonFromSameTrainer(battler)))
    {
        FlagClear(B_FLAG_TERA_ORB_CHARGED);
    }

    // Execute battle script.
    PREPARE_TYPE_BUFFER(gBattleTextBuff1, GetBattlerTeraType(battler));
    if (TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_TERASTALLIZATION, GetBattlerAbility(gBattlerAttacker)))
        BattleScriptPushCursorAndCallback(BattleScript_TeraFormChange);
    else if (gBattleStruct->illusion[gBattlerAttacker].state == ILLUSION_ON
          && DoesSpeciesHaveFormChangeMethod(GetIllusionMonSpecies(gBattlerAttacker), FORM_CHANGE_BATTLE_TERASTALLIZATION))
        BattleScriptPushCursorAndCallback(BattleScript_IllusionOffAndTerastallization);
    else
        BattleScriptPushCursorAndCallback(BattleScript_Terastallization);
}

// Applies palette blend and enables UI indicator after animation has played
void ApplyBattlerVisualsForTeraAnim(enum BattlerId battler)
{
    struct Pokemon *party = GetBattlerParty(battler);
    u32 index = gBattlerPartyIndexes[battler];

    // Show indicator and do palette blend.
    UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &party[index], HEALTHBOX_ALL);
    BlendPalette(OBJ_PLTT_ID(battler), 16, 8, GetTeraTypeRGB(GetBattlerTeraType(battler)));
    CpuCopy32(gPlttBufferFaded + OBJ_PLTT_ID(battler), gPlttBufferUnfaded + OBJ_PLTT_ID(battler), PLTT_SIZEOF(16));

    // We apply the animation behind a white screen, so restore the blended color here to avoid a pop
    BlendPalette(OBJ_PLTT_ID(battler), 16, 16, RGB_WHITEALPHA);
}

// Returns whether a battler can Terastallize.
bool32 CanTerastallize(enum BattlerId battler)
{
    enum HoldEffect holdEffect = GetBattlerHoldEffectIgnoreNegation(battler);

    if (gBattleMons[battler].volatiles.transformed && GET_BASE_SPECIES_ID(gBattleMons[battler].species) == SPECIES_TERAPAGOS)
        return FALSE;

    // Prevents Zigzagoon from terastalizing in vanilla.
    if (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE && !IsOnPlayerSide(battler))
        return FALSE;

    if (TESTING || !IsOnPlayerSide(battler))
    {
        // Skip all other checks in this block, go to HasTrainerUsedGimmick
    }
    else if (!CheckBagHasItem(ITEM_TERA_ORB, 1))
    {
        return FALSE;
    }
    else if (FlagGet(B_FLAG_TERA_ORB_NO_COST))
    {
        // Tera Orb is not depleted, go to HasTrainerUsedGimmick
    }
    else if (!FlagGet(B_FLAG_TERA_ORB_CHARGED))
    {
        return FALSE;
    }

    // Check if Trainer has already Terastallized.
    if (HasTrainerUsedGimmick(battler, GIMMICK_TERA))
        return FALSE;

    // Check if AI battler is intended to Terastallize.
    if (!ShouldTrainerBattlerUseGimmick(battler, GIMMICK_TERA))
        return FALSE;

    // Check if battler has another gimmick active.
    if (GetActiveGimmick(battler) != GIMMICK_NONE)
        return FALSE;

    // Check if battler is holding a Z-Crystal or Mega Stone.
    if (!TESTING && (holdEffect == HOLD_EFFECT_Z_CRYSTAL || holdEffect == HOLD_EFFECT_MEGA_STONE)) // tests make this check already
        return FALSE;

    // Every check passed!
    return TRUE;
}

// Returns a battler's Tera type.
enum Type GetBattlerTeraType(enum BattlerId battler)
{
    return GetMonData(GetBattlerMon(battler), MON_DATA_TERA_TYPE);
}

// Uses up a type's Stellar boost.
void ExpendTypeStellarBoost(enum BattlerId battler, enum Type type)
{
    if (type < 32 && gBattleMons[battler].species != SPECIES_TERAPAGOS_STELLAR) // avoid OOB access
        gBattleStruct->stellarBoostFlags[GetBattlerSide(battler)] |= 1u << type;
}

// Checks whether a type's Stellar boost has been expended.
bool32 IsTypeStellarBoosted(enum BattlerId battler, enum Type type)
{
    if (type < 32) // avoid OOB access
        return !(gBattleStruct->stellarBoostFlags[GetBattlerSide(battler)] & (1u << type));
    else
        return FALSE;
}
        return FALSE;
    }
    else if (FlagGet(B_FLAG_TERA_ORB_NO_COST))
    {
        // Tera Orb is not depleted, go to HasTrainerUsedGimmick
    }
    else if (!FlagGet(B_FLAG_TERA_ORB_CHARGED))
    {
        return FALSE;
    }

    // Check if Trainer has already Terastallized.
    if (HasTrainerUsedGimmick(battler, GIMMICK_TERA))
        return FALSE;

    // Check if AI battler is intended to Terastallize.
    if (!ShouldTrainerBattlerUseGimmick(battler, GIMMICK_TERA))
        return FALSE;

    // Check if battler has another gimmick active.
    if (GetActiveGimmick(battler) != GIMMICK_NONE)
        return FALSE;

    // Check if battler is holding a Z-Crystal or Mega Stone.
    if (!TESTING && (holdEffect == HOLD_EFFECT_Z_CRYSTAL || holdEffect == HOLD_EFFECT_MEGA_STONE)) // tests make this check already
        return FALSE;

    // Every check passed!
    return TRUE;
}

// Returns a battler's Tera type.
enum Type GetBattlerTeraType(enum BattlerId battler)
{
    return GetMonData(GetBattlerMon(battler), MON_DATA_TERA_TYPE);
}

// Uses up a type's Stellar boost.
void ExpendTypeStellarBoost(enum BattlerId battler, enum Type type)
{
    if (type < 32 && gBattleMons[battler].species != SPECIES_TERAPAGOS_STELLAR) // avoid OOB access
        gBattleStruct->stellarBoostFlags[GetBattlerSide(battler)] |= 1u << type;
}

// Checks whether a type's Stellar boost has been expended.
bool32 IsTypeStellarBoosted(enum BattlerId battler, enum Type type)
{
    if (type < 32) // avoid OOB access
        return !(gBattleStruct->stellarBoostFlags[GetBattlerSide(battler)] & (1u << type));
    else
        return FALSE;
}

// Returns the STAB power multiplier to use when Terastallized.
// Power multipliers from Smogon Research thread.
//need add joat to this
//tera normal gives joat
//tera normal on a normal mon boosts joat to stab levels
uq4_12_t GetTeraMultiplier(struct BattleContext *ctx)
{
    enum Type teraType = GetBattlerTeraType(ctx->battlerAtk);

    // Safety check.
    if (GetActiveGimmick(ctx->battlerAtk) != GIMMICK_TERA)
        return UQ_4_12(1.0);

    // Stellar-type checks.
    if (teraType == TYPE_STELLAR)
    {
        bool32 shouldBoost = IsTypeStellarBoosted(ctx->battlerAtk, ctx->moveType);
        if (IS_BATTLER_OF_BASE_TYPE(ctx->battlerAtk, ctx->moveType))
        {
            if (shouldBoost)
                return STELLAR_STAB_MULTIPLIER;
            else
                return SAME_TYPE_MULTIPLIER;
        }
        else if (shouldBoost)
            return STELLAR_NON_STAB;
        else
            return UQ_4_12(1.0);
    }
    // Base and Tera type. w stab
    if (ctx->moveType == teraType && IS_BATTLER_OF_BASE_TYPE(ctx->battlerAtk, ctx->moveType))
    {
        if (ctx->abilityAtk == ABILITY_ADAPTABILITY)
            return TERA_ADAPTABILITY_MUL;
        else
            return TERA_STAB_MULTIPLIER;
    }
    //decide need separate out tera and stab to propelry do joat
    // Tera type only.
    else if (ctx->moveType == teraType && !IS_BATTLER_OF_BASE_TYPE(ctx->battlerAtk, ctx->moveType))
    {
        //non tera adaptability stab
        if (ctx->abilityAtk == ABILITY_ADAPTABILITY)
            return ADAPTABILITY_MULTIPLIER;
        else
            return TERA_MULTIPLIER;
            //just stab or tera bonus
    }
    //base stab joat here
    //supposedly adaptability only works off tera type
    //so actually think adaptability shouldn't activate
    else if (ctx->moveType != teraType)
    {
        if (IS_BATTLER_OF_BASE_TYPE(ctx->battlerAtk, ctx->moveType))
            return SAME_TYPE_MULTIPLIER;
        else if (teraType == TYPE_NORMAL)
        {
            if (IS_BATTLER_OF_BASE_TYPE(ctx->battlerAtk, teraType))
                return TERA_JOAT;
            else
                return JOAT_MULTIPLIER;
        }

    }

    // Neither base or Tera type.
    else
    {
        return UQ_4_12(1.0);
    }
}

/*
attempt to formulize multipliers

stab 1.5 becomes 2 in same type tera or w adaptability
can be calculatated multiplicatively

as   mod * 2 - 1   
(1.5 * 2 = 3 - 1 = 2)

or additively as 
  mod \ 3 + mod

(1.5 \ 3 = 0.5 + 1.5 = 2)

rightness is determined by what's most consistent

adaptability bonus applied to same type tera is less it instead 
goes from 2 to 2.25   


neither works right as a function of mod
but if you apply them individually off of base mod
as additive base mod multipliers w conditions it makes senes

(which is mostly how EE handles it)
you get stab done first

base is 1.5
checks if tera because tera changes how adaptability is applied
if not tera

can do base mod of stab formula
1.5 \ 3 = 0.5  to get adaptability bonus to apply additively

now for tera adaptabiliy only applies for tera type matching

and same type tera ads same bonus as adaptability

so you're already at 1.5 + 0.5

for balance the adaptability bonus is then cut in half 
before being applied.
so rather than adding another 0.5 you get

1.5 + 0.5 + 0.25  = 2.25


and that works
but multiplicative version doesn't

so think will attempt calc my multipliers using that
and see how things go. 
should be able to get a comparative value but mine won't break as even as 1.5

while I've made a formula I doubt a formula was involved in creating the multiplier interactions
developing values for multipliers

and my formula is about off since its determining based on stab as the base
when all changes are applied on the base value of 1.0 no boosts

but that said its somewhat clear tera bonus was meant to be a psuedo stab
since it applied the same bonus as stab to a different type

and adaptability is meant to be a modifier for existing stab
and same type tera does the same thing

so it makes sense to think of the interaction between them
is alternates on modifiying stab

tldr the formula still tracks

last thought note
issue w switching to formula is returned value is far less visible
if can get right function to do effects so that it returns the same for 
default values I can just make a comment on the function
with the base values so not that big of a deal.

until you change it like i did...
... I think I already found these formulas
as looking at my adaptability bonus it doesn't make sense otherwise

using the multiplicative formula I get a lower result for my values
but a higher result for additive

the adaptability bonus I have is smack dab in the middle of both smh
meaning I must have averaged then

but regardless its still higher than the super effective multiplier is...
*/

u16 GetTeraTypeRGB(enum Type type)
{
    return gTypesInfo[type].teraTypeRGBValue;
}
