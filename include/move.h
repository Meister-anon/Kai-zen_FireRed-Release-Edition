#ifndef GUARD_MOVE_H
#define GUARD_MOVE_H

//#include "contest_effect.h"
#include "constants/pokemon.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_string_ids.h"
#include "constants/moves.h"
#include "constants/characters.h"
#include "strings.h"

// For defining EFFECT_HIT etc. with battle TV scores and flags etc.
struct __attribute__((packed, aligned(2))) BattleMoveEffect
{
    const u8 *battleScript;
    u16 battleTvScore:3; //unsure need but keep for now mostly emerald stuff
    u16 encourageEncore:1;
    u16 twoTurnEffect:1;
    u16 semiInvulnerableEffect:1;
    u16 usesProtectCounter:1;
    u16 recoilEffect:1; //for new pre hit ability effect, keep an eye out for effects that go to same battlescript where condition should be TRUE
    u16 padding:8;
};
//having effect recoil and also labelling the effect as a recoil effect
//seems unnecessarily redundent it already has recoil move effect on it as well
//shouldn't having additional effect recoil be enough?
//idk need go over my logic for this, cut down where I can
//w new battle refactors believe no longer need acc check after atk string
//as all done in atk canceler so no longer relevant

#define EFFECTS_ARR(...) (const struct AdditionalEffect[]) {__VA_ARGS__}
#define ADDITIONAL_EFFECTS(...) EFFECTS_ARR( __VA_ARGS__ ), .numAdditionalEffects = ARRAY_COUNT(EFFECTS_ARR( __VA_ARGS__ ))

struct AdditionalEffect
{
    //enum MoveEffect moveEffect;
    u32 moveEffect;
    u8 self:1;
    u8 onlyIfTargetRaisedStats:1;
    u8 onChargeTurnOnly:1;
    u8 sheerForceOverride:1; // Handles edge cases for Sheer Force - if TRUE, boosts when it shouldn't, or doesn't boost when it should
    u8 preAttackEffect:1;//EE made their own version of pre hit effect can just use this
    u8 padding:3; //only differenece is only activates if move would hit which is fine again use for strength and triple arrows stuff
    union PACKED {
        enum WrappedStringID wrapped;
    } multistring;
    u8 chance; // 0% = primary effect, 100 is effect certain //note from alex a primary effect isn't blocked by sheer force, while a certain effect would be
};//so I need to set 100 all effects I added that don't use chance... greaaaat
//oh wait actually no, so value 100 would exclude from sheerforce
//meaning that should be the exception not the norm

enum ProtectType
{
    PROTECT_TYPE_NONE,
    PROTECT_TYPE_SIDE,
    PROTECT_TYPE_SINGLE,
};

enum ProtectMethod
{
    PROTECT_NONE,
    PROTECT_NORMAL,
    PROTECT_SPIKY_SHIELD,
    PROTECT_KINGS_SHIELD,
    PROTECT_BANEFUL_BUNKER,
    PROTECT_BURNING_BULWARK,
    PROTECT_OBSTRUCT,
    PROTECT_SILK_TRAP,
    PROTECT_MAX_GUARD, //can get rid of this
    PROTECT_WIDE_GUARD,
    PROTECT_QUICK_GUARD,
    PROTECT_CRAFTY_SHIELD,
    PROTECT_MAT_BLOCK,
    PROTECT_SHIELD_BASH,
    PROTECT_FENCE,
};

enum TerrainGroundCheck
{
    GROUND_CHECK_NONE,
    GROUND_CHECK_USER,
    GROUND_CHECK_TARGET,
};

//consolidation for floating dmg effects
//save space so can do explosion change
enum AirborneDmgCheck
{
    NEUTRAL_DAMAGE,
    CANT_DAMAGE_FLOATING,
    DAMAGES_AIRBORNE,
    DOUBLE_DAMAGE_AIRBORNE,
};

//reworking struct start w flags 
//hmm well when I bring the flag in it'll be everything 
//at once...
//I'll work on this over time, first can do flags
//then can figure out the rest as I go
//struct is now fully utulitized
//only has space in union without increasing
struct MoveInfo
{
    const u8 *name; //move name length 16 chars + 1
    const u8 *description; //approx 20 chars per line 5 lines  max between 95-100 chars
    enum BattleMoveEffects effect;
    enum Type type:5;     // Up to 32
    enum DamageCategory category:2;
    u16 power:9;    // up to 511
    // end of word
    u8 pp;
    s8 priority;
    u16 accuracy:7;
    u16 target:4; //target all battlers is 14 so min space is bit 4
    u16 artMove:1;
    u16 space:4; //consider using for flag swap dmg cat, nah annoying but better using effects
    //u16 target:9; //do I need this so high, think just to fill type space
    // end of word
    // Flags
    bool32 makesContact:1;
    bool32 ignoresProtect:1;
    bool32 magicCoatAffected:1;
    bool32 snatchAffected:1;
    bool32 kickingMove:1; //think don't need kingrock logic setup my own for it
    bool32 punchingMove:1; //iron fist boost
    bool32 bitingMove:1; //strong jaw
    bool32 pulseMove:1; //mega launcher
    bool32 soundMove:1;
    bool32 ballisticMove:1;
    bool32 powderMove:1;
    bool32 danceMove:1;
    bool32 windMove:1;
    bool32 slicingMove:1; //sharpness
    bool32 healingMove:1;
    bool32 evasiveBreak:1;  //may rename was minimize, changing to surehitagainstBoostedEvasion reworked further do think just call evasive break
    bool32 ignoresTargetAbility:1;
    bool32 ignoresTargetDefenseEvasionStages:1;
    bool32 damagesUnderground:1;   //auto doubles dmg 
    bool32 damagesUnderwater:1;
    u32 airborneDmgState:2; //consolidates airborne floating stuff values set from AirborneDmgCheck
    /*bool32 damagesAirborne:1; //ok think best I can do to get byte back is combine these into a 2 bit state check
    bool32 damagesAirborneDoubleDamage:1;
    bool32 cantdamageFloating:1; //no longer needs was just thousand arrows - ignoreTypeIfFlyingAndUngrounded
    */
    bool32 thawsUser:1; //^ replaced above for new ground affecting mechanic - look for other types than ground to apply too
    bool32 ignoresSubstitute:1;//oh thawsUser is a different thing nvm
    bool32 forcePressure:1; //(for self-targeted moves that are affected by Pressure) //idk how this makes sense yet
    bool32 cantUseTwice:1;
    // Ban flags
    bool32 gravityBanned:1; //used to tell what move gets canceled by gravity etc.
    bool32 moonMove:1; //replaced mirrormove flag, use for moon move I guess
    bool32 meFirstBanned:1;
    bool32 mimicBanned:1;
    bool32 metronomeBanned:1;
    bool32 copycatBanned:1;
    // end of word -correct u32 ends here

    bool32 assistBanned:1; // Matches same moves as copycatBanned + semi-invulnerable moves and Mirror Coat.
    bool32 sleepTalkBanned:1;
    bool32 instructBanned:1;
    bool32 encoreBanned:1;
    bool32 parentalBondBanned:1;
    bool32 sketchBanned:1; //would use for monotype as well
    bool32 headbuttMove:1;
    //Other
    bool32 alwaysCriticalHit:1;
    bool32 enhancedCritrate:1; //will rename to enhanced crit rate
    bool32 dampBanned:1;    //Damp blocks move
    bool32 alwaysHitsInHailSnow:1;
    bool32 alwaysHitsInRain:1;
    bool32 accuracy65InSun:1;
    u32 numAdditionalEffects:3; // limited to 7 //was 3 expansion raised to 7 for some reason - don't want to get too crazy
    u32 strikeCount:4; // Max 15 hits. Defaults to 1 if not set. May apply its effect on each hit.
    u32 multiTaskBanned:1; // remove need for multitask exclude 
    //u32 explosiveMove:1; //simplify logic for moves/effects that do defense stripping just explosion likes
    u32 variableMultihit:1; //replace effect multihit // Takes precedence over strikeCount
    bool32 ignoresRedirection:1;
    bool32 typelessDmg:1; //replace for move power not 0, needed to do stab and typeless dmg default logic for typeless is set type mystery
    //u32 padding:8; //have multi hit count in atk cancel use this but default to 2-5 if multihit and strike count not set perhaps
    struct {
            u32 sacrificedHpPercentage:7;
            u32 failsIfNotEnoughHp:1;
        } explosionEffects; //want to use for explosion stuff but cant fit in union cuz terrain boost change
    // end of word
    union {
        struct {
            u16 stringId;
            union {
                u16 status;
                u16 weather;
            };
        } twoTurnAttack;
        struct {
            u16 species;
            u16 power:9;
            u16 numOfHits:7;
        } speciesPowerOverride;
        struct {
            u16 typeCheck;
            u16 powerMultiplier;
        } typeBasedPowerBoost;
        struct {
            u16 damagePercent:12;
            u16 damageCategories:4; // bit field
        } reflectDamage; //the space of all unions is taking 4 bytes this is 2 but guess is fine would just be blank?
        struct {
            u16 terrain;
            u16 percent:13;
            enum TerrainGroundCheck groundCheck:2;
            u16 hitsBothFoes:1;
        } terrainBoost;
        u32 protectMethod;
        u32 status;
        u32 moveProperty;
        u32 holdEffect;
        u32 typeArg; //think use this for general storage type ebility etc. rename storedValue
        u32 fixedDamage;//^didn't understand how union works more values doesn't take more space can split out betwen type and ability
        u32 damagePercentage;
        u32 absorbPercentage;//if sacrifice hp percent is just for curse can do without it, just wrap into explosion rework
        //u32 sacrificedHpPercentage; //decide use for hp loss for self destruct mind blown may filter into curse as well
        u32 nonVolatileStatus; //looking at plasma fists which can go use effect_hit then go to other move effect
        u32 overwriteAbility;
        u32 weatherType;
    } argument; //think may not need recoilType at all
    //unions are weird can't be bit field but can have bit fields within them,
    //are read as same byte so must be mutually exclusive
    //so unless its a strut within the union I can't have
    //more than 1 field assigned at a time and return values from it.
    //unions I believe save space since no matter how many members I have
    //in said union I believe its all read as a single byte/memory block

    // primary/secondary effects
    const struct AdditionalEffect *additionalEffects;
    // contest parameters
    /*u8 contestEffect;
    u8 contestCategory:3;
    u8 contestComboStarterId;
    u8 contestComboMoves[MAX_COMBO_MOVES];*/
    const u8 *battleAnimScript;
};//without u32 flags, type overflowed with added moves
//argument is for extra effects other than secondary effect
//vsonic important seems ignoresKingsRock value isn't necessary
//only applies for specific  prior gen stuff
//but should now be done with check additional effects for flinch
//not presently ported in EE but just need to add that line
//to EE code

extern const struct MoveInfo gMovesInfo[];
extern const struct BattleMoveEffect gBattleMoveEffects[];

uq4_12_t GetTypeBasedBoostMultiplier(enum Move moveId);

static inline enum Move SanitizeMoveId(enum Move moveId)
{
    if (moveId >= MOVES_COUNT)
        return MOVE_NONE;
    else
        return moveId;
}

static inline enum BattleMoveEffects SanitizeMoveEffect(enum BattleMoveEffects moveEffect)
{
    if (moveEffect >= NUM_BATTLE_MOVE_EFFECTS)
        return EFFECT_PLACEHOLDER;
    else
        return moveEffect;
}

//broke movename cap may not use
//ok useful in some places that don't go to cap like debug menu
static inline const u8 *GetMoveName_(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].name;
}

static inline void CopyMoveNameToBuff(u8 *nameBuff, enum Move moveId)
{
    s32 i;

    // Hmm? FRLG has < while Ruby/Emerald has <=
    for (i = 0; i < MOVE_NAME_LENGTH; i++)
    {
        nameBuff[i] = gMovesInfo[SanitizeMoveId(moveId)].name[i];

        if (nameBuff[i] == EOS)
            break;
    }

    nameBuff[i] = EOS;

}

static inline const u8 *GetMoveDescription(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMovesInfo[moveId].effect == EFFECT_PLACEHOLDER)
        return gNotDoneYetDescription;
    return gMovesInfo[moveId].description;
}

static inline enum BattleMoveEffects GetMoveEffect(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].effect;
}

static inline enum Type GetMoveType(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].type;
}//vsonic renamed from GetMoveType

/*
static inline u32 GetMoveBaseType(u32 move)
{
    return gMovesInfo[SanitizeMoveId(move)].type;
}*/

//think wanted to separate split and category damagecategory would be what defense stat move hits
//then would have something for what offense stat effect comes out of?
static inline u32 GetMoveCategory(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].category;
}

static inline u32 GetMovePower(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].power;
}

static inline u32 GetMoveAccuracy(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].accuracy;
}

static inline u32 GetMoveTarget(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].target;
}

static inline u32 GetMovePP(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].pp;
}

static inline s32 GetMovePriority(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].priority;
}

static inline u32 GetMoveStrikeCount(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].strikeCount;
}

static inline u32 IsEnhancedCritMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].enhancedCritrate;
}

static inline bool32 MoveAlwaysCrits(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].alwaysCriticalHit;
}

static inline u32 GetMoveAdditionalEffectCount(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].numAdditionalEffects;
}

static inline bool32 MoveMakesContact(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].makesContact;
}

static inline bool32 MoveIgnoresProtect(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].ignoresProtect;
}

static inline bool32 MoveCanBeBouncedBack(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].magicCoatAffected;
}

static inline bool32 MoveCanBeSnatched(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].snatchAffected;
}

static inline bool32 IsHeadbuttMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].headbuttMove;
}

static inline bool32 IsArtMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].artMove;
}

static inline bool32 IsPunchingMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].punchingMove;
}

static inline bool32 IsKickingMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].kickingMove;
}

static inline bool32 IsBitingMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].bitingMove;
}

static inline bool32 IsPulseMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].pulseMove;
}

static inline bool32 IsSoundMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].soundMove;
}

static inline bool32 IsBallisticMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].ballisticMove;
}

static inline bool32 IsPowderMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].powderMove;
}

static inline bool32 IsDanceMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].danceMove;
}

static inline bool32 IsWindMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].windMove;
}

static inline bool32 IsSlicingMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].slicingMove;
}

static inline bool32 IsHealingMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].healingMove;
}

static inline bool32 IsMoveDampBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].dampBanned;
}

static inline bool32 IsMoveMultiTaskBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].multiTaskBanned;
}

static inline bool32 IsVariableMultiHitMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].variableMultihit;
}

static inline bool32 IsMultiHitMove(enum Move moveId)
{
    return (GetMoveStrikeCount(moveId) > 1 || IsVariableMultiHitMove(moveId));
}

static inline bool32 MoveSureHitEvasionBoostedTargets(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].evasiveBreak;
}

//note move redirection effect works a bit dif
//than fog redirection block
//idea is these moves always land regardless
//while fog is, things are obscured
//so its not possible to body block move for ally
//important ony for ally switch other effects that swap placement
static inline bool32 DoesMovePreventRedirection(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].ignoresRedirection;
}

//mold breaker
static inline bool32 MoveIgnoresTargetAbility(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].ignoresTargetAbility;
}

static inline bool32 MoveIgnoresDefenseEvasionStages(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].ignoresTargetDefenseEvasionStages;
}

static inline bool32 MoveDamagesUnderground(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].damagesUnderground;
}

static inline bool32 MoveDamagesUnderWater(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].damagesUnderwater;
}

//consolidatres floating dmg airborne and 2x airborne into 1
static inline u32 GetAirborneDmgState(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].airborneDmgState;
}

static inline bool32 MoveDamagesAirborne(enum Move moveId)
{
    return GetAirborneDmgState(moveId) == DAMAGES_AIRBORNE;
}

static inline bool32 MoveDamagesAirborneDoubleDamage(enum Move moveId)
{
    return GetAirborneDmgState(moveId) == DOUBLE_DAMAGE_AIRBORNE;
}

static inline bool32 MoveCanDamageAirborne(enum Move moveId)
{
    return (MoveDamagesAirborne(moveId)
    || MoveDamagesAirborneDoubleDamage(moveId));
}

//for most part is category without a distinction
//intention is to differentiate new category of
//effects that are unable to hit floating mon separate from type
//ex. moves that explicitly flow along the ground
//this should now be main distinction of whether moves can hit floating types
static inline bool32 MoveCantDamageFloatingTargets(enum Move moveId)
{
    return GetAirborneDmgState(moveId) == CANT_DAMAGE_FLOATING;
}

//update this to be more inline w 
//my own thaw logic vsonic
static inline bool32 MoveThawsUser(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].thawsUser;
}

static inline bool32 MoveIgnoresSubstitute(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].ignoresSubstitute;
}

static inline bool32 MoveForcesPressure(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].forcePressure;
}

static inline bool32 MoveCantBeUsedTwice(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].cantUseTwice;
}

static inline bool32 MoveAlwaysHitsInRain(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].alwaysHitsInRain;
}

//changed to 65 not 50
//w my acc reworks didn't want something that low
static inline bool32 MoveHas65AccuracyInSun(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].accuracy65InSun;
}

static inline bool32 MoveAlwaysHitsInHailSnow(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].alwaysHitsInHailSnow;
}

static inline bool32 IsMoveGravityBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].gravityBanned;
}

static inline bool32 IsMoonbasedMove(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].moonMove;
}

static inline bool32 IsMoveMeFirstBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].meFirstBanned;
}

static inline bool32 IsMoveMimicBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].mimicBanned;
}

static inline bool32 IsMoveMetronomeBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].metronomeBanned;
}

static inline bool32 IsMoveCopycatBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].copycatBanned;
}

static inline bool32 IsMoveAssistBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].assistBanned;
}

static inline bool32 IsMoveSleepTalkBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].sleepTalkBanned;
}

static inline bool32 IsMoveInstructBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].instructBanned;
}

static inline bool32 IsMoveEncoreBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].encoreBanned;
}

static inline bool32 IsMoveParentalBondBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].parentalBondBanned;
}


static inline bool32 IsMoveSketchBanned(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].sketchBanned;
}

static inline u32 GetMoveTwoTurnAttackStringId(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.twoTurnAttack.stringId;
}

static inline u32 GetMoveTwoTurnAttackStatus(enum Move moveId)
{
    return UNCOMPRESS_BITS(gMovesInfo[SanitizeMoveId(moveId)].argument.twoTurnAttack.status);
}

static inline u32 GetMoveTwoTurnAttackWeather(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.twoTurnAttack.status;
}

static inline u32 GetMoveSpeciesPowerOverride_Species(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_SPECIES_POWER_OVERRIDE, "not a species power override move: %S", GetMoveName(moveId));
    return gMovesInfo[SanitizeMoveId(moveId)].argument.speciesPowerOverride.species;
}

static inline u32 GetMoveSpeciesPowerOverride_Power(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_SPECIES_POWER_OVERRIDE, "not a species power override move: %S", GetMoveName(moveId));
    return gMovesInfo[SanitizeMoveId(moveId)].argument.speciesPowerOverride.power;
}

static inline u32 GetMoveSpeciesPowerOverride_NumOfHits(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_SPECIES_POWER_OVERRIDE, "not a species power override move: %S", GetMoveName(moveId));
    return gMovesInfo[SanitizeMoveId(moveId)].argument.speciesPowerOverride.numOfHits;
}

static inline u32 GetMoveReflectDamage_DamagePercent(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_REFLECT_DAMAGE, "not a damage reflection move: %S", GetMoveName(moveId));
    return gMovesInfo[SanitizeMoveId(moveId)].argument.reflectDamage.damagePercent;
}

static inline u32 GetMoveReflectDamage_DamageCategories(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_REFLECT_DAMAGE, "not a damage reflection move: %S", GetMoveName(moveId));
    return gMovesInfo[SanitizeMoveId(moveId)].argument.reflectDamage.damageCategories;
}

static inline u32 GetMoveTerrainBoost_Terrain(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_TERRAIN_BOOST, "not a terrain boosted move: %S", GetMoveName(moveId));
    return gMovesInfo[moveId].argument.terrainBoost.terrain;
}

static inline u32 GetMoveTerrainBoost_Percent(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_TERRAIN_BOOST, "not a terrain boosted move: %S", GetMoveName(moveId));
    return gMovesInfo[moveId].argument.terrainBoost.percent;
}

static inline u32 GetMoveTerrainBoost_GroundCheck(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_TERRAIN_BOOST, "not a terrain boosted move: %S", GetMoveName(moveId));
    return gMovesInfo[moveId].argument.terrainBoost.groundCheck;
}

static inline bool32 GetMoveTerrainBoost_HitsBothFoes(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_TERRAIN_BOOST, "not a terrain boosted move: %S", GetMoveName(moveId));
    return gMovesInfo[moveId].argument.terrainBoost.hitsBothFoes;
}

static inline enum ProtectMethod GetMoveProtectMethod(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.protectMethod;
}

static inline u32 GetMoveTerrainFlag(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.moveProperty;
}

static inline u32 GetMoveEffectArg_Status(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.status;
}

static inline u32 GetMoveEffectArg_MoveProperty(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.moveProperty;
}

static inline u32 GetMoveEffectArg_HoldEffect(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.holdEffect;
}

//keep type u32 as returning union value
//can change func argument tho
static inline u32 GetMoveOverwriteAbility(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.overwriteAbility;
}

static inline u32 GetMoveArgType(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.typeArg;
}

//will want to add assert effect is not two tyuped move
static inline u32 GetTwoTypedMove2ndType(enum Move moveId)
{
   return GetMoveEffect(moveId) == EFFECT_TWO_TYPED_MOVE ? GetMoveArgType(moveId) : TYPE_NONE;
}

//replace getmovefixedhpdamage
//as is more than just fixedhp effects now
static inline u32 GetMoveFixedDamage(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.fixedDamage;
}

static inline u32 GetMoveAbsorbPercentage(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMovesInfo[moveId].argument.absorbPercentage == 0)
        return 50;
    return gMovesInfo[moveId].argument.absorbPercentage;
}

//both below effects need interact with sturdy
//still todo, get hp percentage
//if should survive w sturdy set hp to 1 instead of 0
static inline u32 GetHpPercentagetoSacrifice(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    return gMovesInfo[moveId].explosionEffects.sacrificedHpPercentage;
}

//if has sturdy and would fail because hp below threshold
//make move go off anyway just take out sturdy mon
//sturdy blocks ko effects above certain hp threshold
//well explosion specifically is hp threshold
//think everything lese just works
static inline bool32 DoesExplosionFailIfBelowHpThreshold(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    return gMovesInfo[moveId].explosionEffects.failsIfNotEnoughHp;
}

static inline u32 GetMoveNonVolatileStatus(u32 move)
{
    move = SanitizeMoveId(move);
    switch(GetMoveEffect(move))
    {
    case EFFECT_NON_VOLATILE_STATUS:
    case EFFECT_YAWN:
    case EFFECT_DARK_VOID:
        return gMovesInfo[move].argument.nonVolatileStatus;
    default:
        return MOVE_EFFECT_NONE;
    }
}

static inline u32 GetMoveDamagePercentage(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].argument.damagePercentage;
}

static inline u16 GetTypeBasedBoostTypeCheck(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    //assertf(gMovesInfo[moveId].effect == EFFECT_TARGET_TYPE_DAMAGE, "not a type boosted move: %S", GetMoveName_(moveId));
    return gMovesInfo[moveId].argument.typeBasedPowerBoost.typeCheck;
}


//don't need assert cuz not part of union
static inline bool32 MoveDoesTypelessDmg(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    return gMovesInfo[moveId].typelessDmg == TRUE;
}

static inline bool32 IsTwoTurnsMove(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    return (GetMoveEffect(moveId) == EFFECT_TWO_TURNS_ATTACK
    || GetMoveEffect(moveId) == EFFECT_SEMI_INVULNERABLE
    || GetMoveEffect(moveId) == EFFECT_FLY);
}

static inline u32 GetMoveWeatherType(u32 move)
{
    //assertf(gMovesInfo[move].effect == EFFECT_WEATHER || gMovesInfo[move].effect == EFFECT_WEATHER_AND_SWITCH, "not a move that sets weather: %S", gMovesInfo[move].name);
    return gMovesInfo[SanitizeMoveId(move)].argument.weatherType;
}

static inline const struct AdditionalEffect *GetMoveAdditionalEffectById(enum Move moveId, u32 effect)
{
    return &gMovesInfo[SanitizeMoveId(moveId)].additionalEffects[effect];
}

//add assert to ensure used only w recoil effect
static inline  const struct AdditionalEffect *GetMoveRecoilEffect(enum Move move)
{
    u32 numAdditionalEffects = GetMoveAdditionalEffectCount(move);
    for (u32 i = 0; i < numAdditionalEffects; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        if (additionalEffect->moveEffect == MOVE_EFFECT_LIGHT_RECOIL
        || additionalEffect->moveEffect == MOVE_EFFECT_MED_RECOIL
        || additionalEffect->moveEffect == MOVE_EFFECT_HEAVY_RECOIL)
            return &gMovesInfo[SanitizeMoveId(move)].additionalEffects[i];
    }
    
}

/*

static inline u32 GetMoveContestEffect(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestEffect;
}

static inline u32 GetMoveContestCategory(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestCategory;
}

static inline u32 GetMoveContestComboStarter(enum Move moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestComboStarterId;
}

static inline u32 GetMoveContestComboMoves(enum Move moveId, u32 comboMove)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestComboMoves[comboMove];
}*/

static inline const u8 *GetMoveAnimationScript(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMovesInfo[moveId].battleAnimScript == NULL)
    {
        DebugPrintfLevel(MGBA_LOG_WARN, "No animation for moveId=%u", moveId);
        return gMovesInfo[MOVE_NONE].battleAnimScript;
    }
    return gMovesInfo[moveId].battleAnimScript;
}

static inline bool32 IsOHKOmoveEffect(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);

    return (GetMoveEffect(moveId) == EFFECT_SHEER_COLD 
            || GetMoveEffect(moveId) == EFFECT_OHKO);
}

//prob need setup asserts especially for this
//but point is explosion effects will always sacrifice hp
static inline bool32 IsExplosionMove(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    return gMovesInfo[moveId].explosionEffects.sacrificedHpPercentage != 0;
}

static inline bool32 MoveEffectDoesRecoil(enum BattleMoveEffects moveEffect)
{
    moveEffect = SanitizeMoveEffect(moveEffect);
    return gBattleMoveEffects[moveEffect].recoilEffect;
}

static inline const u8 *GetMoveBattleScript(enum Move moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoveEffects[gMovesInfo[moveId].effect].battleScript == NULL)
    {
        DebugPrintfLevel(MGBA_LOG_WARN, "No effect for moveId=%u", moveId);
        return gBattleMoveEffects[EFFECT_PLACEHOLDER].battleScript;
    }
    return gBattleMoveEffects[gMovesInfo[moveId].effect].battleScript;
}
#endif // GUARD_MOVE_H
