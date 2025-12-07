#ifndef GUARD_MOVE_H
#define GUARD_MOVE_H

//#include "contest_effect.h"
#include "constants/battle_effects.h"
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
    u8 padding:4;
    union PACKED {
        enum WrappedStringID wrapped;
    } multistring;
    u8 chance; // 0% = effect certain, primary effect
};

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
};

static inline u32 SanitizeMoveId(u32 moveId)
{
    if (moveId >= MOVES_COUNT)
        return MOVE_NONE;
    else
        return moveId;
}

static inline const u8 *GetMoveName(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].name;
}

static inline const u8 *GetMoveDescription(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoves[moveId].effect == EFFECT_HIT)
        return gNotDoneYetDescription;
    return gBattleMoves[moveId].description;
}

static inline u32 GetMoveEffect(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].effect;
}

static inline u32 GetMoveType(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].type;
}

//think wanted to separate split and category damagecategory would be what defense stat move hits
//then would have something for what offense stat effect comes out of?
static inline u32 GetMoveCategory(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].category;
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

/*static inline u32 GetMoveZEffect(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].zMove.effect;
}

static inline u32 GetMoveZPowerOverride(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].zMove.powerOverride;
}
*/

static inline s32 GetMovePriority(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].priority;
}

static inline u32 GetMoveStrikeCount(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].strikeCount;
}

static inline u32 GetMoveCriticalHitStage(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].criticalHitStage;
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

static inline bool32 MoveSureHitEvasionBoostedTargets(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].evasiveBreak;
}

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

static inline bool32 MoveCantDamageFloatingTargets(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].cantdamageFloating;
}

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

static inline bool32 IsMoveSkyBattleBanned(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].skyBattleBanned;
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

static inline u32 GetMoveProtectSide(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.protect.side;
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

static inline u32 GetMoveArgType(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.type;
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

static inline u32 GetMoveRecoil(u32 moveId)
{
    return gBattleMoves[SanitizeMoveId(moveId)].argument.recoilPercentage;
}

static inline const struct AdditionalEffect *GetMoveAdditionalEffectById(u32 moveId, u32 effect)
{
    return &gBattleMoves[SanitizeMoveId(moveId)].additionalEffects[effect];
}

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
