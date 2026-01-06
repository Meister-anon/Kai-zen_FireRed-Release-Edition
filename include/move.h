#ifndef GUARD_MOVE_H
#define GUARD_MOVE_H

//#include "contest_effect.h"
#include "constants/pokemon.h"
#include "constants/battle.h"
#include "constants/battle_effects.h"
#include "constants/battle_string_ids.h"
#include "constants/moves.h"

// For defining EFFECT_HIT etc. with battle TV scores and flags etc.
struct __attribute__((packed, aligned(2))) BattleMoveEffect
{
    const u8 *battleScript;
    u16 battleTvScore:3; //unsure need but keep for now mostly emerald stuff
    u16 encourageEncore:1;
    u16 twoTurnEffect:1;
    u16 semiInvulnerableEffect:1;
    u16 usesProtectCounter:1;
    u16 hasAccCheckAfterAtkstring:1; //for new pre hit ability effect, keep an eye out for effects that go to same battlescript where condition should be TRUE
    u16 padding:8;
};

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
    u8 setfromatkcanceler:1; //rn for strength and triple arrow, attempt do setmoveeffect stuff in attack canceler if move succeeds
    u8 padding:3; //^realize effect needs to go here rather than on battle effect so correct effect gets set
    union PACKED {
        enum WrappedStringID wrapped;
    } multistring;
    u8 chance; // 0% = effect certain, primary effect
};//vsonic will have to add base doesn't have that remove any checks for not 0

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

//reworking struct start w flags 
//hmm well when I bring the flag in it'll be everything 
//at once...
//I'll work on this over time, first can do flags
//then can figure out the rest as I go
struct BattleMove
{
    u16 effect;
    u16 target;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    s8 priority;
    u8 split;
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
    bool32 damagesAirborne:1;
    bool32 damagesAirborneDoubleDamage:1;
    bool32 cantdamageFloating:1; //no longer needs was just thousand arrows - ignoreTypeIfFlyingAndUngrounded
    bool32 thawsUser:1; //^ replaced above for new ground affecting mechanic - look for other types than ground to apply too
    bool32 ignoresSubstitute:1;//oh thawsUser is a different thing nvm
    bool32 forcePressure:1; //(for self-targeted moves that are affected by Pressure) //idk how this makes sense yet
    bool32 cantUseTwice:1;
    // Ban flags
    bool32 gravityBanned:1; //used to tell what move gets canceled by gravity etc.
    bool32 mirrorMoveBanned:1;
    bool32 meFirstBanned:1;
    bool32 mimicBanned:1;
    bool32 metronomeBanned:1;
    // end of word

    bool32 copycatBanned:1;
    bool32 assistBanned:1; // Matches same moves as copycatBanned + semi-invulnerable moves and Mirror Coat.
    bool32 sleepTalkBanned:1;
    bool32 instructBanned:1;
    bool32 encoreBanned:1;
    bool32 parentalBondBanned:1;
    bool32 recoilMove:1; //removed  skybattle stuff just use for reckless 
    bool32 sketchBanned:1; //would use for monotype as well
    bool32 headbuttMove:1;
    //Other
    bool32 alwaysCriticalHit:1;
    bool32 enhancedCritrate:1; //will rename to enhanced crit rate
    bool32 dampBanned:1;    //Damp blocks move
    bool32 alwaysHitsInHailSnow:1;
    bool32 alwaysHitsInRain:1;
    bool32 accuracy50InSun:1;
    u32 numAdditionalEffects:2; // limited to 3 - don't want to get too crazy
    u32 strikeCount:4; // Max 15 hits. Defaults to 1 if not set. May apply its effect on each hit.
    u32 multiTaskBanned:1; // remove need for multitask exclude 
    u32 explosiveMove:1; //simplify logic for moves/effects that do defense stripping just explosion likes
    u32 variableMultihit:1; //replace effect multihit
    bool32 ignoresRedirection:1;
    u32 padding:7; //have multi hit count in atk cancel use this but default to 2-5 if multihit and strike count not set perhaps
    // end of word
    union {
        struct {
            u16 stringId;
            u16 status;
        } twoTurnAttack;
        u32 protectMethod;
        u32 status;
        u32 moveProperty;
        u32 holdEffect;
        u32 storedValue; //think use this for general storage type ebility etc. rename storedValue
        u32 fixedDamage;
        u32 damagePercentage;
        u32 absorbPercentage;
        u32 sacrificedHpPercentage; //decide use for hp loss for self destruct mind blown may filter into curse as well
        u32 nonVolatileStatus; //looking at plasma fists which can go use effect_hit then go to other move effect
    } argument; //think may not need recoilType at all

    // primary/secondary effects
    const struct AdditionalEffect *additionalEffects;
};//without u32 flags, type overflowed with added moves
//argument is for extra effects other than secondary effect
//vsonic important seems ignoresKingsRock value isn't necessary
//only applies for specific  prior gen stuff
//but should now be done with check additional effects for flinch
//not presently ported in EE but just need to add that line
//to EE code

extern const struct BattleMove gBattleMoves[];
extern const struct BattleMoveEffect gBattleMoveEffects[];

static inline u32 SanitizeMoveId(u32 moveId)
{
    if (moveId >= MOVES_COUNT)
        return MOVE_NONE;
    else
        return moveId;
}

/*static inline const u8 *GetMoveName(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].name;
}

static inline const u8 *GetMoveDescription(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoves[moveId].effect == EFFECT_HIT)
        return gNotDoneYetDescription;
    return gBattleMoves[moveId].description;
}*/

static inline u32 GetMoveEffect(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].effect;
}

static inline u32 GetBaseMoveType(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].type;
}//vsonic renamed from GetMoveType

//think wanted to separate split and category damagecategory would be what defense stat move hits
//then would have something for what offense stat effect comes out of?
static inline u32 GetMoveCategory(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].split;
}

static inline bool32 IsBattleMoveStatus(u32 moveId)
{
    return GetMoveCategory(moveId) == SPLIT_STATUS;
}

static inline u32 GetMovePower(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].power;
}

static inline u32 GetMoveAccuracy(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].accuracy;
}

static inline u32 GetMoveTarget(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].target;
}

static inline u32 GetMovePP(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].pp;
}

static inline s32 GetMovePriority(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].priority;
}

static inline u32 GetMoveStrikeCount(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].strikeCount;
}

static inline u32 IsEnhancedCritMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].enhancedCritrate;
}

static inline bool32 MoveAlwaysCrits(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].alwaysCriticalHit;
}

static inline u32 GetMoveAdditionalEffectCount(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].numAdditionalEffects;
}

static inline bool32 MoveMakesContact(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].makesContact;
}

static inline bool32 MoveIgnoresProtect(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].ignoresProtect;
}

static inline bool32 MoveCanBeBouncedBack(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].magicCoatAffected;
}

static inline bool32 MoveCanBeSnatched(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].snatchAffected;
}

static inline bool32 IsHeadbuttMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].headbuttMove;
}

static inline bool32 IsRecoilMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].recoilMove;
}

static inline bool32 IsPunchingMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].punchingMove;
}

static inline bool32 IsKickingMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].kickingMove;
}

static inline bool32 IsBitingMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].bitingMove;
}

static inline bool32 IsPulseMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].pulseMove;
}

static inline bool32 IsSoundMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].soundMove;
}

static inline bool32 IsBallisticMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].ballisticMove;
}

static inline bool32 IsPowderMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].powderMove;
}

static inline bool32 IsDanceMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].danceMove;
}

static inline bool32 IsWindMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].windMove;
}

static inline bool32 IsSlicingMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].slicingMove;
}

static inline bool32 IsHealingMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].healingMove;
}

static inline bool32 IsMoveDampBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].dampBanned;
}

static inline bool32 IsMoveMultiTaskBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].multiTaskBanned;
}

static inline bool32 IsVariableMultiHitMove(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].variableMultihit;
}

static inline bool32 IsMultiHitMove(u32 moveId)
{
    return (GetMoveStrikeCount(moveId) > 1 || IsVariableMultiHitMove(moveId));
}

static inline bool32 MoveSureHitEvasionBoostedTargets(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].evasiveBreak;
}

static inline bool32 DoesMovePreventRedirection(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].ignoresRedirection;
}

//mold breaker
static inline bool32 MoveIgnoresTargetAbility(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].ignoresTargetAbility;
}

static inline bool32 MoveIgnoresDefenseEvasionStages(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].ignoresTargetDefenseEvasionStages;
}

static inline bool32 MoveDamagesUnderground(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].damagesUnderground;
}

static inline bool32 MoveDamagesUnderWater(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].damagesUnderwater;
}

static inline bool32 MoveDamagesAirborne(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].damagesAirborne;
}

static inline bool32 MoveDamagesAirborneDoubleDamage(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].damagesAirborneDoubleDamage;
}

static inline bool32 MoveCanDamageAirborne(u32 moveId)
{
    return (gBattleMoves[moveId].damagesAirborne == TRUE
    || gBattleMoves[moveId].damagesAirborneDoubleDamage == TRUE);
}

//for most part is category without a distinction
//intention is to differentiate new category of
//effects that are unable to hit floating mon separate from type
//ex. moves that explicitly flow along the ground
//this should now be main distinction of whether moves can hit floating types
static inline bool32 MoveCantDamageFloatingTargets(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].cantdamageFloating;
}

//update this to be more inline w 
//my own thaw logic vsonic
static inline bool32 MoveThawsUser(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].thawsUser;
}

static inline bool32 MoveIgnoresSubstitute(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].ignoresSubstitute;
}

static inline bool32 MoveForcesPressure(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].forcePressure;
}

static inline bool32 MoveCantBeUsedTwice(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].cantUseTwice;
}

static inline bool32 MoveAlwaysHitsInRain(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].alwaysHitsInRain;
}

static inline bool32 MoveHas50AccuracyInSun(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].accuracy50InSun;
}

static inline bool32 MoveAlwaysHitsInHailSnow(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].alwaysHitsInHailSnow;
}

static inline bool32 IsMoveGravityBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].gravityBanned;
}

static inline bool32 IsMoveMirrorMoveBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].mirrorMoveBanned;
}

static inline bool32 IsMoveMeFirstBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].meFirstBanned;
}

static inline bool32 IsMoveMimicBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].mimicBanned;
}

static inline bool32 IsMoveMetronomeBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].metronomeBanned;
}

static inline bool32 IsMoveCopycatBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].copycatBanned;
}

static inline bool32 IsMoveAssistBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].assistBanned;
}

static inline bool32 IsMoveSleepTalkBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].sleepTalkBanned;
}

static inline bool32 IsMoveInstructBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].instructBanned;
}

static inline bool32 IsMoveEncoreBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].encoreBanned;
}

static inline bool32 IsMoveParentalBondBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].parentalBondBanned;
}


static inline bool32 IsMoveSketchBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].sketchBanned;
}

static inline u32 GetMoveTwoTurnAttackStringId(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.twoTurnAttack.stringId;
}

static inline u32 GetMoveTwoTurnAttackStatus(u32 moveId)
{
    return UNCOMPRESS_BITS(gBattleMoves[SanitizeMoveId(moveId)].argument.twoTurnAttack.status);
}

static inline u32 GetMoveTwoTurnAttackWeather(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.twoTurnAttack.status;
}

static inline enum ProtectMethod GetMoveProtectMethod(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.protectMethod;
}

static inline u32 GetMoveTerrainFlag(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.moveProperty;
}

static inline u32 GetMoveEffectArg_Status(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.status;
}

static inline u32 GetMoveEffectArg_MoveProperty(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.moveProperty;
}

static inline u32 GetMoveEffectArg_HoldEffect(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.holdEffect;
}

//think will split into dif functions for simplicity
static inline u32 GetMoveStoredValue(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.storedValue;
}

//don't need this can just used storedvalue
static inline u32 GetMoveOverwriteAbility(u32 moveId)
{
    return GetMoveStoredValue(moveId);
}

static inline u32 GetTwoTypedMove2ndType(u32 moveId)
{
    return GetMoveStoredValue(moveId);
}

static inline u32 GetMoveArgType(u32 moveId)
{
    return GetMoveStoredValue(moveId);
}

static inline u32 GetMoveFixedDamage(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.fixedDamage;
}

static inline u32 GetMoveAbsorbPercentage(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoves[moveId].argument.absorbPercentage == 0)
        return 50;
    return gBattleMoves[moveId].argument.absorbPercentage;
}

static inline u32 GetHpPercentagetoSacrifice(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    return gBattleMoves[moveId].argument.sacrificedHpPercentage;
}

static inline u32 GetMoveNonVolatileStatus(u32 move)
{
    move = SanitizeMoveId(move);
    switch(GetMoveEffect(move))
    {
    case EFFECT_NON_VOLATILE_STATUS:
    case EFFECT_YAWN:
    case EFFECT_DARK_VOID:
        return gBattleMoves[move].argument.nonVolatileStatus;
    default:
        return MOVE_EFFECT_NONE;
    }
}

static inline u32 GetMoveDamagePercentage(u32 move)
{
    return gBattleMoves[SanitizeMoveId(move)].argument.damagePercentage;
}


static inline const struct AdditionalEffect *GetMoveAdditionalEffectById(u32 moveId, u32 effect)
{
    return &gBattleMoves[SanitizeMoveId(moveId)].additionalEffects[effect];
}

/*

static inline u32 GetMoveContestEffect(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].contestEffect;
}

static inline u32 GetMoveContestCategory(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].contestCategory;
}

static inline u32 GetMoveContestComboStarter(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].contestComboStarterId;
}

static inline u32 GetMoveContestComboMoves(u32 moveId, u32 comboMove)
{
    return gBattleMoves[SanitizeMoveId(moveId)].contestComboMoves[comboMove];
}

static inline const u8 *GetMoveAnimationScript(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoves[moveId].battleAnimScript == NULL)
    {
        DebugPrintfLevel(MGBA_LOG_WARN, "No animation for moveId=%u", moveId);
        return gBattleMoves[MOVE_NONE].battleAnimScript;
    }
    return gBattleMoves[moveId].battleAnimScript;
}*/

static inline bool32 IsOHKOmoveEffect(u32 moveId)
{
    return (GetMoveEffect(moveId) == EFFECT_SHEER_COLD 
            || GetMoveEffect(moveId) == EFFECT_OHKO);
}

static inline bool32 IsExplosionMove(u32 moveId)
{
    return gBattleMoves[moveId].explosiveMove;
}

static inline const u8 *GetMoveBattleScript(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoveEffects[gBattleMoves[moveId].effect].battleScript == NULL)
    {
        DebugPrintfLevel(MGBA_LOG_WARN, "No effect for moveId=%u", moveId);
        return gBattleMoveEffects[EFFECT_PLACEHOLDER].battleScript;
    }
    return gBattleMoveEffects[gBattleMoves[moveId].effect].battleScript;
}
#endif // GUARD_MOVE_H
