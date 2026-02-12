#ifndef GUARD_BATTLE_UTIL_H
#define GUARD_BATTLE_UTIL_H

#include "global.h"
#include "constants/hold_effects.h"

#define MOVE_LIMITATION_ZEROMOVE                (1 << 0)
#define MOVE_LIMITATION_PP                      (1 << 1)
#define MOVE_LIMITATION_DISABLED                (1 << 2)
#define MOVE_LIMITATION_TORMENTED               (1 << 3)
#define MOVE_LIMITATION_TAUNT                   (1 << 4)
#define MOVE_LIMITATION_IMPRISON                (1 << 5)
#define MOVE_LIMITATION_ENCORE                  (1 << 6)
#define MOVE_LIMITATION_CHOICE_ITEM             (1 << 7)
#define MOVE_LIMITATION_ASSAULT_VEST            (1 << 8)
#define MOVE_LIMITATION_GRAVITY                 (1 << 9)
#define MOVE_LIMITATION_HEAL_BLOCK              (1 << 10)
#define MOVE_LIMITATION_BELCH                   (1 << 11)
#define MOVE_LIMITATION_THROAT_CHOP             (1 << 12)
#define MOVE_LIMITATION_STUFF_CHEEKS            (1 << 13)
#define MOVE_LIMITATION_CANT_USE_TWICE          (1 << 14)

#define MOVE_LIMITATION_PLACEHOLDER             (1 << 15)
#define MOVE_LIMITATIONS_ALL                    0xFFFF

// Switches between simulated battle calc and actual battle combat
enum ResultOption
{
    CHECK_TRIGGER, // Check the function without running scripts / setting any flags.
    AI_CHECK,  // Check the function without running scripts / setting any flags. Same as CHECK_TRIGGER but only used when additional data has to be fetched during ai calcs
    RUN_SCRIPT, // Used during actual combat where a script has to be run / flags need to be set
};

enum MoveAbsorbed
{
    MOVE_ABSORBED_BY_NO_ABILITY,
    MOVE_ABSORBED_BY_DRAIN_HP_ABILITY,
    MOVE_ABSORBED_BY_STAT_INCREASE_ABILITY,
    MOVE_ABSORBED_BY_BOOST_FLASH_FIRE,
    MOVE_ABSORBED_BY_RISING_PHOENIX_ABILITY,
};//add new effect for pheonix ability that combines fields w stat cleanse
//pretty sure not using just need setup pheonix effect first

enum FieldEffectCases
{
    FIELD_EFFECT_TRAINER_STATUSES,
    FIELD_EFFECT_OVERWORLD_TERRAIN,
    FIELD_EFFECT_OVERWORLD_WEATHER,
};

enum AbilityEffect
{
    ABILITYEFFECT_ENDTURN,
    ABILITYEFFECT_MOVE_END_ATTACKER,
    ABILITYEFFECT_PRE_HIT_ACTIVATE, // new effect for color change
    ABILITYEFFECT_COLOR_CHANGE, // Color Change / Berserk / Anger Shell
    ABILITYEFFECT_MOVE_END,
    ABILITYEFFECT_IMMUNITY,
    ABILITYEFFECT_SYNCHRONIZE,
    ABILITYEFFECT_ATK_SYNCHRONIZE,
    ABILITYEFFECT_FORM_CHANGE_ON_HIT,
    ABILITYEFFECT_MOVE_END_OTHER,
    ABILITYEFFECT_MOVE_END_FOES_FAINTED, // Moxie-like abilities / Battle Bond / Magician

    // On Switch in
    ABILITYEFFECT_TERA_SHIFT,
    ABILITYEFFECT_NEUTRALIZINGGAS,
    ABILITYEFFECT_UNNERVE,
    ABILITYEFFECT_ON_SWITCHIN,
    ABILITYEFFECT_SWITCH_IN_FORM_CHANGE,
    ABILITYEFFECT_COMMANDER, // Commander / Hospitality / Costar
    ABILITYEFFECT_ON_WEATHER,
    ABILITYEFFECT_ON_TERRAIN,
    ABILITYEFFECT_OPPORTUNIST,
};


#define ABILITYEFFECT_ON_SWITCHIN                0x0
#define ABILITYEFFECT_ENDTURN                    0x1
#define ABILITYEFFECT_MOVES_BLOCK                0x2
#define ABILITYEFFECT_ABSORBING                  0x3
#define ABILITYEFFECT_MOVE_END_ATTACKER          0x4
#define ABILITYEFFECT_MOVE_END                   0x5
#define ABILITYEFFECT_IMMUNITY                   0x6
#define ABILITYEFFECT_FORECAST                   0x7
#define ABILITYEFFECT_SYNCHRONIZE                0x8
#define ABILITYEFFECT_ATK_SYNCHRONIZE            0x9
#define ABILITYEFFECT_INTIMIDATE1                0xA
#define ABILITYEFFECT_INTIMIDATE2                0xB
#define ABILITYEFFECT_TRACE                      0xC
#define ABILITYEFFECT_CHECK_OTHER_SIDE           0xD
#define ABILITYEFFECT_CHECK_BATTLER_SIDE         0xE
#define ABILITYEFFECT_FIELD_SPORT                0xF
#define ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER 0x10 // TODO: Is it correct? 
#define ABILITYEFFECT_COUNT_OTHER_SIDE           0x11   //check what this  does, may rename
#define ABILITYEFFECT_COUNT_BATTLER_SIDE         0x12
#define ABILITYEFFECT_COUNT_ON_FIELD             0x13
#define ABILITYEFFECT_CHECK_ON_FIELD             0x14
#define ABILITYEFFECT_NEUTRALIZINGGAS			 0x15  //swapped what was a nuisance ability test
#define ABILITYEFFECT_MOVE_END_OTHER			 0x16
#define ABILITYEFFECT_SWITCH_IN_ABILITIES		 0x17   //realized ability battle effects function doesn't really separate blocks well, so added more for better organization
#define ABILITYEFFECT_SWITCH_IN_TERRAIN_ABILITY	 0x18   //nvm can't do more as new block would require new switch...and would break switch in effects i beleive //could just put in same plac as switcin think in bs commands

#define ABILITYEFFECT_ONETURN_SWITCHIN_RESOLUTION  0x19 //could this just be put in end turn? -vsonic
//#define ABILITYEFFECT_CUPIDSARROW				 0x15  //1st attempted implementation realized goes in switchin don't need new effect
#define ABILITYEFFECT_MUD_SPORT                  0xFC	//actually potentially does as trace and intimidate have them? look over implementation again
#define ABILITYEFFECT_WATER_SPORT                0xFD //changed to side status no longer needed
//figure out what this does, adn check any limitations
//I want to redo tererain graphic for something more subtle
//instead of everything glowing display graphic template that's fitting
//over/inside the mon circle, so will only be noticeable from enemy side
//i.e sparks tags for electric terrain etc.
#define ABILITYEFFECT_SWITCH_IN_TERRAIN          0xFF
#define ABILITYEFFECT_SWITCH_IN_WEATHER          0xFE   //sets battle weather from map conditions, nothing to do with ability

#define ABILITY_ON_OPPOSING_FIELD(battlerId, abilityId)(AbilityBattleEffects(ABILITYEFFECT_CHECK_OTHER_SIDE, battlerId, abilityId, 0, 0))
#define ABILITY_ON_FIELD(abilityId)(AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, abilityId, 0, 0))
#define ABILITY_ON_FIELD2(abilityId)(AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, abilityId, 0, 0))

#define IS_WHOLE_SIDE_ALIVE(battler)((IsBattlerAlive(battler) && IsBattlerAlive(BATTLE_PARTNER(battler))))
#define IS_ALIVE_AND_PRESENT(battler)   (IsBattlerAlive(battler) && IsBattlerSpritePresent(battler))





// For the first argument of ItemBattleEffects, to deteremine which block of item effects to try
enum ItemCaseId
{
    ITEMEFFECT_NONE,
    ITEMEFFECT_ON_SWITCH_IN,
    ITEMEFFECT_ON_SWITCH_IN_FIRST_TURN,
    ITEMEFFECT_NORMAL,
    ITEMEFFECT_MOVE_END,
    ITEMEFFECT_KINGSROCK,
    ITEMEFFECT_TARGET,
    ITEMEFFECT_ORBS,
    ITEMEFFECT_LIFEORB_SHELLBELL,
    ITEMEFFECT_USE_LAST_ITEM, // move end effects for just the battler, not whole field
    ITEMEFFECT_STATS_CHANGED, // For White Herb and Eject Pack
};

enum ItemEffect
{
    ITEM_NO_EFFECT,
    ITEM_STATUS_CHANGE,
    ITEM_EFFECT_OTHER,
    ITEM_PP_CHANGE,
    ITEM_HP_CHANGE,
    ITEM_STATS_CHANGE,
};

// for Natural Gift and Fling
struct TypePower
{
    enum Type type;
    u8 power;
    u16 effect;
};

enum MoveSuccessOrder
{
    CANCELER_STANCE_CHANGE_1,
    CANCELER_CLEAR_FLAGS,
    CANCELER_SKY_DROP,
    CANCELER_RECHARGE,
    CANCELER_ASLEEP_OR_FROZEN,
    CANCELER_POWER_POINTS,
    CANCELER_OBEDIENCE,
    CANCELER_TRUANT,
    CANCELER_FOCUS_GEN5,
    CANCELER_FLINCH,
    CANCELER_DISABLED,
    CANCELER_VOLATILE_BLOCKED, // Gravity / Heal Block / Throat Chop
    CANCELER_TAUNTED,
    CANCELER_IMPRISONED,
    CANCELER_CONFUSED,
    CANCELER_PARALYZED,
    CANCELER_INFATUATION,
    CANCELER_BIDE,
    CANCELER_Z_MOVES,
    CANCELER_CHOICE_LOCK,
    CANCELER_CALLSUBMOVE,
    CANCELER_THAW,
    CANCELER_STANCE_CHANGE_2,
    CANCELER_ATTACKSTRING,
    CANCELER_PPDEDUCTION,
    CANCELER_SKY_BATTLE,
    CANCELER_WEATHER_PRIMAL,
    CANCELER_FOCUS_PRE_GEN5,
    CANCELER_MOVE_FAILURE,
    CANCELER_POWDER_STATUS,
    CANCELER_PRIORITY_BLOCK,
    CANCELER_PROTEAN,
    CANCELER_EXPLODING_DAMP,
    CANCELER_EXPLOSION,
    CANCELER_CHARGING,
    CANCELER_NO_TARGET,
    CANCELER_TOOK_ATTACK,
    CANCELER_TARGET_FAILURE,
    CANCELER_NOT_FULLY_PROTECTED,
    CANCELER_MULTIHIT_MOVES,
    CANCELER_END,
};

enum Obedience
{
    OBEYS,
    DISOBEYS_LOAFS,
    DISOBEYS_HITS_SELF,
    DISOBEYS_FALL_ASLEEP,
    DISOBEYS_WHILE_ASLEEP,
    DISOBEYS_RANDOM_MOVE,
};

enum MoveCanceler
{
    MOVE_STEP_SUCCESS,
    MOVE_STEP_BREAK, // Runs script. Increments state
    MOVE_STEP_PAUSE, // Runs script. Does not increment state
    MOVE_STEP_FAILURE, // Move failed, jump to script that handles the failure
};

static const u8 gSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 gHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
//won't need trump card see if still use other two
static const u8 gTrumpCardPowerTable[] = {200, 80, 60, 50, 40};

//raising the left numbers higher, will let you do more damage from higher percent hp
static const u8 gFlailHpScaleToPowerTable[] =
{
    4, 200,
    12, 150,
    19, 100,
    25, 80,
    32, 40,
    68, 20
};

static const u16 gWeightToDamageTable[] =
{
    50, 40,
    200, 60,    //geodude is here
    500, 75,
    1000, 85,  //graveler is here
    2400, 100,  //onix is here  //snorlax is double this
    10000, 120,
    0xFFFF, 0xFFFF
};

// percent in UQ_4_12 format
extern const uq4_12_t gPercentToModifier[101];

extern const struct TypePower gNaturalGiftTable[];

// Lowest and highest percentages used for damage roll calculations
#define DMG_ROLL_PERCENT_LO 85
#define DMG_ROLL_PERCENT_HI 100

// Crit chance exceptions
#define CRITICAL_HIT_BLOCKED -1
#define CRITICAL_HIT_ALWAYS  -2

extern const u8 *const gPlayCryanims[];


struct BattleContext
{
    enum BattlerId battlerAtk:3;
    enum BattlerId battlerDef:3;
    u32 fixedBasePower:8;
    u32 weather:16;
    u32 unused:2;
    u32 fieldStatuses;

    u32 move:13;
    u32 chosenMove:13; // May be different to 'move', e.g. for Z moves.
    enum Type moveType:6; //idk why is bit 6 5 is 32 and there's only 21 types + 1 for type count
    //u32 unused2:1; //ah guess with 25 free bits they figured 1 more was inconsequential

    uq4_12_t typeEffectivenessModifier;
    enum Ability abilityAtk;
    enum Ability abilityDef;
    enum HoldEffect holdEffectAtk;
    enum HoldEffect holdEffectDef;

    // Flags
    u32 isCrit:1;
    u32 randomFactor:1;
    u32 updateFlags:1;
    u32 isAnticipation:1;
    u32 isSelfInflicted:1;
    u32 aiCalc:1;
    u32 aiCheckBerryModifier:1; // Flags that KOing through a berry should be checked
    u32 airBalloonBlocked:1;
    u32 abilityBlocked:1;
    u32 runScript:1;  // Used during actual combat where scripts have to be run / flags need to be set
    u32 padding:22;
};

// Helper struct to keep the arg list small and prevent constant recalculations of abilities/hold effects.
struct BattleCalcValues
{
    enum BattlerId battlerAtk:3;
    enum BattlerId battlerDef:3;
    u32 move:16;
    u32 padding:10;
    enum Ability abilities[MAX_BATTLERS_COUNT];
    enum HoldEffect holdEffects[MAX_BATTLERS_COUNT];
};

//not using
enum SleepClauseBlock
{
    NOT_BLOCKED_BY_SLEEP_CLAUSE,
    BLOCKED_BY_SLEEP_CLAUSE,
};

enum SkyDropState
{
    SKY_DROP_IGNORE,
    SKY_DROP_ATTACKCANCELER_CHECK,
    SKY_DROP_GRAVITY_ON_AIRBORNE,
    SKY_DROP_CANCEL_MULTI_TURN_MOVES,
    SKY_DROP_STATUS_YAWN,
    SKY_DROP_STATUS_FREEZE_SLEEP,
};

#define SKY_DROP_NO_TARGET 0xFF
#define SKY_DROP_RELEASED_TARGET 0xFE

enum EjectPackTiming
{
    START_OF_TURN,
    END_TURN,
    OTHER,
};

void HandleAction_ThrowBall(void);
uq4_12_t CalcTypeEffectivenessMultiplierHelper(enum Move move, enum Type moveType, enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, bool32 recordAbilities);
u32 GetCurrentBattleWeather(void);
bool32 EndOrContinueWeather(void);
bool32 IsUnnerveBlocked(enum BattlerId battler, u32 itemId);
bool32 IsAffectedByFollowMe(enum BattlerId battlerAtk, u32 defSide, enum Move move);
void DetermineTarget(enum MoveTarget moveTarget, bool32 overwriteTarget);
void HandleAction_UseMove(void);
void HandleAction_Switch(void);
void HandleAction_UseItem(void);
bool32 TryRunFromBattle(enum BattlerId battler);
void HandleAction_Run(void);
void HandleAction_WatchesCarefully(void);
void HandleAction_SafariZoneBallThrow(void);
void HandleAction_ThrowPokeblock(void);
void HandleAction_GoNear(void);
void HandleAction_SafariZoneRun(void);
void HandleAction_WallyBallThrow(void);
void HandleAction_TryFinish(void);
void HandleAction_NothingIsFainted(void);
void HandleAction_ActionFinished(void);
u8 GetBattlerForBattleScript(u8 caseId);

//still more things to go over here maybe>?
u32 GetFuryCutterAccuracy(u32 move);
void PressurePPLose(u8 target, u8 attacker, u16 move);
void PressurePPLoseOnUsingImprison(u8 attacker);
void PressurePPLoseOnUsingPerishSong(u8 attacker);
void MarkAllBattlersForControllerExec(void);
void MarkBattlerForControllerExec(enum BattlerId battlerId);
void MarkBattlerReceivedLinkData(enum BattlerId battlerId);
const u8* CancelMultiTurnMoves(enum BattlerId battler);
bool32 WasUnableToUseMove(enum BattlerId battler);
void PrepareStringBattle(u16 stringId, enum BattlerId battler);
void ResetSentPokesToOpponentValue(void);
void sub_8017434(enum BattlerId battler);
void UpdateSentPokesToOpponentValue(enum BattlerId battler);
void BattleScriptPush(const u8 *bsPtr);
void BattleScriptPushCursor(void);
void BattleScriptCall(const u8 *bsPtr);
void BattleScriptPop(void);
u8 TrySetCantSelectMoveBattleScript(enum BattlerId battler);
u8 CheckMoveLimitations(enum BattlerId battler, u8 unusableMoves, u16 check);
bool32 AreAllMovesUnusable(enum BattlerId battler);
u8 GetImprisonedMovesCount(enum BattlerId battlerId, u16 move);
u8 DoFieldEndTurnEffects(void);
s32 GetDrainedBigRootHp(enum BattlerId battler, s32 hp);
s32 MistyTerrainHealBoost(enum BattlerId battler, s32 healamount);
u8 DoBattlerEndTurnEffects(void);
bool32 HandleWishPerishSongOnTurnEnd(void);
void ClearRageStatuses(enum BattlerId battler);
u8 AtkCanceller_UnableToUseMove(void);
u8 AtkCanceller_UnableToUseMove2(void);
bool8 IsFloatingSpecies(u16 species);
bool8 IsFlyingTypeBattlerUnableToFly(enum BattlerId battler); //battle specific variant
bool8 CanFlyingTypeRecoverFromSmackDown(enum BattlerId battler); //for use w ascension timer prob rename later vsonic
bool32 IsBattlerGrounded(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect);
bool8 IsFloatingTargetImmunetoGroundBasedMoves(enum BattlerId battler_def, enum Ability abilityAtk, enum Ability abilityDef, u16 move);

//EE stuff
bool32 IsAbilityAndRecord(enum BattlerId battler, enum Ability battlerAbility, enum Ability abilityToCheck);
u32 DoEndTurnEffects(void);
bool32 HandleFaintedMonActions(void);
void TryClearRageAndFuryCutter(void); //THINK NOT using
enum MoveCanceler AtkCanceler_MoveSuccessOrder(void);
bool32 HasNoMonsToSwitch(enum BattlerId battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2);
bool32 TryChangeBattleWeather(enum BattlerId battler, u32 battleWeatherId, u32 ability);
bool32 TryChangeBattleTerrain(enum BattlerId battler, u32 statusFlag);
bool32 CanAbilityBlockMove(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, u32 move, enum ResultOption option);
bool32 CanTargetBlockPranksterMove(struct BattleContext *ctx, s32 movePriority);
bool32 CanPsychicTerrainProtectTarget(struct BattleContext *ctx, s32 movePriority);
bool32 CanMoveBeBlockedByTarget(struct BattleContext *ctx, s32 movePriority);
bool32 CanAbilityAbsorbMove(struct BattleContext *ctx);
bool32 TryFieldEffects(enum FieldEffectCases caseId);
u32 AbilityBattleEffects(enum AbilityEffect caseID, enum BattlerId battler, enum Ability ability, enum Move move, bool32 shouldAbilityTrigger);
bool32 TryPrimalReversion(enum BattlerId battler);
bool32 IsNeutralizingGasOnField(void);
bool32 IsMoldBreakerTypeAbility(enum BattlerId battler, enum Ability ability);
u32 GetBattlerAbilityIgnoreMoldBreaker(enum BattlerId battler);
u32 GetBattlerAbilityNoAbilityShield(enum BattlerId battler);
u32 GetBattlerAbilityInternal(enum BattlerId battler, bool32 ignoreMoldBreaker, bool32 noAbilityShield);
enum Ability GetBattlerAbility(enum BattlerId battler);
u32 IsAbilityOnSide(enum BattlerId battler, enum Ability ability);
u32 IsAbilityOnOpposingSide(enum BattlerId battler, enum Ability ability);
u32 IsAbilityOnField(enum Ability ability);
u32 IsAbilityOnFieldExcept(enum BattlerId battler, enum Ability ability);
u32 IsAbilityPreventingEscape(enum BattlerId battler);
bool32 IsBattlerProtected(struct BattleContext *ctx);
u32 GetProtectType(enum ProtectMethod method);
bool32 CanBattlerEscape(enum BattlerId battler); // no ability check
//from EE

void BattleScriptExecute(const u8 *BS_ptr);
void BattleScriptPushCursorAndCallback(const u8 *BS_ptr);
u32 ItemBattleEffects(enum ItemCaseId caseID, enum BattlerId battler, bool32 moveTurn);
void ClearDestinyBondGrudge(enum BattlerId battlerId);
void HandleAction_RunBattleScript(void);

/*u8 IsMonDisobedient(void);
u32 GetBattleMoveSplit(u32 moveId);
u32 GetBattleMoveDamageCategory(u32 attackerId, u16 move);*/
u32 GetFlingPowerFromItemId(u32 itemId);
//u16 GetPrimalReversionSpecies(u16 preEvoSpecies, u16 heldItemId);
//u16 GetMegaEvolutionSpecies(u16 preEvoSpecies, u16 heldItemId);
//u16 GetWishMegaEvolutionSpecies(u16 preEvoSpecies, u16 moveId1, u16 moveId2, u16 moveId3, u16 moveId4);
//void UndoMegaEvolution(u32 monId);  no longer used

u32 SetRandomTarget(enum BattlerId battlerAtk);
u32 GetBattleMoveTarget(enum Move move, enum MoveTarget moveTarget);
enum Obedience GetAttackerObedienceForAction(void);
enum HoldEffect GetBattlerHoldEffect(enum BattlerId battler);
enum HoldEffect GetBattlerHoldEffectIgnoreAbility(enum BattlerId battler);
enum HoldEffect GetBattlerHoldEffectIgnoreNegation(enum BattlerId battler);
enum HoldEffect GetBattlerHoldEffectInternal(enum BattlerId battler, enum Ability ability);
u32 GetBattlerHoldEffectParam(enum BattlerId battler);
bool32 CanBattlerAvoidContactEffects(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum HoldEffect holdEffectAtk, enum Move move);
bool32 IsMoveMakingContact(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum HoldEffect holdEffectAtk, enum Move move);
bool32 IsBattlerGrounded(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect);
u32 GetMoveSlot(u16 *moves, enum Move move);
u32 GetBattlerWeight(enum BattlerId battler);
s32 CalcCritChanceStage(struct BattleContext *ctx);
s32 CalcCritChanceStageGen1(struct BattleContext *ctx);
s32 CalculateMoveDamage(struct BattleContext *ctx);
s32 CalculateMoveDamageVars(struct BattleContext *ctx);
s32 DoFixedDamageMoveCalc(struct BattleContext *ctx);
s32 ApplyModifiersAfterDmgRoll(struct BattleContext *ctx, s32 dmg);
uq4_12_t CalcTypeEffectivenessMultiplier(struct BattleContext *ctx);
uq4_12_t CalcPartyMonTypeEffectivenessMultiplier(enum Move move, u16 speciesDef, enum Ability abilityDef);
uq4_12_t GetTypeModifier(enum Type atkType, enum Type defType);
uq4_12_t GetOverworldTypeEffectiveness(struct Pokemon *mon, enum Type moveType);
void UpdateMoveResultFlags(uq4_12_t modifier, u16 *resultFlags);
s32 GetStealthHazardDamage(enum TypeSideHazard hazardType, enum BattlerId battler);
s32 GetStealthHazardDamageByTypesAndHP(enum TypeSideHazard hazardType, enum Type type1, enum Type type2, u32 maxHp);
bool32 CanMegaEvolve(enum BattlerId battler);
bool32 CanUltraBurst(enum BattlerId battler);
void ActivateMegaEvolution(enum BattlerId battler);
void ActivateUltraBurst(enum BattlerId battler);
bool32 IsBattlerMegaEvolved(enum BattlerId battler);
bool32 IsBattlerPrimalReverted(enum BattlerId battler);
bool32 IsBattlerUltraBursted(enum BattlerId battler);
u32 GetBattleFormChangeTargetSpecies(enum BattlerId battler, enum FormChanges method, enum Ability ability);
bool32 TryRevertPartyMonFormChange(u32 partyIndex);
bool32 TryBattleFormChange(enum BattlerId battler, enum FormChanges method, enum Ability ability);
//From EE

bool32 DoBattlersShareType(enum BattlerId battler1, enum BattlerId battler2);
bool32 CanBattlerEscape(enum BattlerId battler);
u32 IsAbilityPreventingEscape(enum BattlerId battlerId);
u32 GetProtectType(enum ProtectMethod method);
//u32 GetBattlerHoldEffect(enum BattlerId battler, bool32 checkNegating);
//bool8 IsMoveMakingContact(u16 move, enum BattlerId battlerAtk); //made bool8 since its just a true false return
u32 DoesSideHaveAbility(enum BattlerId battlerId, u32 ability); // //adapted abilityonside function that doesn't use getbattlerability
bool8 DoesBattlerHaveSureHitAbility(enum BattlerId battlerId);
bool32 IsRolePlayBannedAbilityAtk(u16 ability);  //looping array kept 32
bool32 IsRolePlayBannedAbility(u16 ability);
bool32 IsSkillSwapBannedAbility(u16 ability);
bool32 IsWorrySeedBannedAbility(u16 ability);
bool32 IsGastroAcidBannedAbility(u16 ability);
bool32 IsMoldBreakerAffectedAbility(u16 ability); //new addition to clean up get battler ability
bool32 IsEntrainmentBannedAbilityAttacker(u16 ability);
bool32 IsEntrainmentTargetOrSimpleBeamBannedAbility(u16 ability);
bool8 IsMoveCounterAttack(u16 move); 

bool32 CanBeParalyzedViaAbility(enum BattlerId battlerId);
bool32 CanThaw(u32 move, enum BattlerId battler); //always use gcurrentmove hope work, need rewrite for modern update
bool32 CanBattlerHeal(enum BattlerId battlerId); //simplify heal check
bool32 CanTeleport(enum BattlerId battlerId); //new teleport logic
bool32 ShouldPranksterBoostedMoveFail(u16 move, enum BattlerId battlerwithPrankster, enum BattlerId battlerDef, bool32 checkTarget);
bool32 IsMoonbasedMove(u16 move); //in prep for lunar power etc.
u16 GetUsedHeldItem(enum BattlerId battler);
bool32 TryRoomService(enum BattlerId battlerId);
bool32 TestSheerForceFlag(enum BattlerId battler, u16 move);
u8 TryHandleSeed(enum BattlerId battler, u32 terrainFlag, u8 statId, u16 itemId, bool32 execute);
void TryToRevertMimicry(void);
void TryToApplyMimicry(enum BattlerId battlerId, bool8 various);
void RestoreBattlerOriginalTypes(enum BattlerId battlerId);
void MulModifier(uq4_12_t *modifier, u16 val);
u32 ApplyModifier(uq4_12_t modifier, u32 val);
bool32 UnnerveOn(enum BattlerId battlerId, u32 itemId);
bool32 ShouldIgnoreBattlerHeldItem(enum BattlerId battler); //combine klutz mega primal logic for ignoring item, basis for mega form upgrade
void TryRestoreStolenItems(void);
bool32 CanActivateTimeControl(enum BattlerId battler);
bool32 TryActivateBattlePoisonHeal(enum BattlerId battler);   //replaced normal poisonheal checks, allows use for poison types
bool32 TryActivateHeatTrance(enum BattlerId battler);
//u16 CalcPartyMonTypeEffectivenessMultiplier(u16 move, u16 speciesDef, u16 abilityDef);  ported in case, but pretty sure I have no use for this, as these are just for reading battlre data and running dmg calc predictions
//s32 CalculateMoveDamageAndEffectiveness(u16 move, enum BattlerId battlerAtk, enum BattlerId battlerDef, u8 moveType, u16 *typeEffectivenessModifier);
//learned defined need be on one line, this should be logic for thawing i.e remove frozen status
//removed fire fang restriction, any heat transafer is good enough

//EE stuff
bool32 CanBattlerGetOrLoseItem(u32 fromBattler, enum BattlerId battler, u16 itemId);
u32 GetBattlerVisualSpecies(enum BattlerId battler);
bool32 TryClearIllusion(enum BattlerId battler, enum Ability ability);
u32 GetIllusionMonSpecies(enum BattlerId battler);
struct Pokemon *GetIllusionMonPtr(enum BattlerId battler);
void ClearIllusionMon(enum BattlerId battler);
u32 GetIllusionMonPartyId(struct Pokemon *party, struct Pokemon *mon, struct Pokemon *partnerMon, enum BattlerId battler);
bool32 SetIllusionMon(struct Pokemon *mon, enum BattlerId battler);
u32 TryImmunityAbilityHealStatus(enum BattlerId battler);
bool32 ShouldGetStatBadgeBoost(u16 flagId, enum BattlerId battler);
uq4_12_t GetBadgeBoostModifier(void);
enum DamageCategory GetBattleMoveCategory(enum Move move);
void SetDynamicMoveCategory(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move);
bool32 CanFling(enum BattlerId battlerAtk, enum BattlerId battlerDef);
bool32 IsTelekinesisBannedSpecies(u16 species);
bool32 IsHealBlockPreventingMove(enum BattlerId battler, enum Move move);
bool32 IsBelchPreventingMove(enum BattlerId battler, enum Move move);
bool32 HasEnoughHpToEatBerry(enum BattlerId battler, enum Ability ability, u32 hpFraction, u32 itemId);
bool32 IsPartnerMonFromSameTrainer(enum BattlerId battler);
enum DamageCategory GetCategoryBasedOnStats(enum BattlerId battler);
void SetShellSideArmCategory(void);
bool32 MoveIsAffectedBySheerForce(enum Move move);
bool32 IsSheerForceAffected(enum Move move, enum Ability ability);
void TryRestoreHeldItems(void);
bool32 CanStealItem(enum BattlerId battlerStealing, enum BattlerId battlerItem, u16 item);
void TrySaveExchangedItem(enum BattlerId battler, u16 stolenItem);
bool32 IsBattlerAffectedByHazards(enum BattlerId battler, enum HoldEffect holdEffect, bool32 toxicSpikes);
void SortBattlersBySpeed(enum BattlerId *battlers, bool32 slowToFast);
bool32 CompareStat(enum BattlerId battler, enum Stat statId, u8 cmpTo, u8 cmpKind, enum Ability ability);
bool32 BlocksPrankster(enum Move move, enum BattlerId battlerPrankster, enum BattlerId battlerDef, bool32 checkTarget);
bool32 PickupHasValidTarget(enum BattlerId battler);
bool32 CantPickupItem(enum BattlerId battler);
bool32 IsBattlerWeatherAffected(enum BattlerId battler, u32 weatherFlags);
enum MoveTarget GetBattlerMoveTargetType(enum BattlerId battler, enum Move move);
bool32 CanTargetBattler(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move);
u32 GetNextTarget(u32 moveTarget, bool32 excludeCurrent);
void CopyMonLevelAndBaseStatsToBattleMon(enum BattlerId battler, struct Pokemon *mon);
void CopyMonAbilityAndTypesToBattleMon(enum BattlerId battler, struct Pokemon *mon);
//EE function for recalc stats this used in place of transform logic for recalcs outside of transform and ditto
void RecalcBattlerStats(enum BattlerId battler, struct Pokemon *mon, bool32 isDynamaxing);
bool32 IsGen6ExpShareEnabled(void);
bool32 MoveHasAdditionalEffect(enum Move move, enum MoveEffect moveEffect);
bool32 MoveHasAdditionalEffectWithChance(enum Move move, enum MoveEffect moveEffect, u32 chance);
bool32 MoveHasAdditionalEffectSelf(enum Move move, enum MoveEffect moveEffect);
bool32 IsMoveEffectRemoveSpeciesType(enum Move move, enum MoveEffect moveEffect, u32 argument);
bool32 MoveHasChargeTurnAdditionalEffect(enum Move move);
bool32 CanTargetPartner(enum BattlerId battlerAtk, enum BattlerId battlerDef);
bool32 IsBattlerUnaffectedByMove(enum BattlerId battler);
bool32 MoodyCantRaiseStat(u32 stat);
bool32 MoodyCantLowerStat(u32 stat);
bool32 IsPsychicTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsMistyTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsGrassyTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsElectricTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsAnyTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsBattlerTerrainAffected(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses, u32 terrainFlag);
u32 GetHighestStatId(enum BattlerId battler);
u32 GetParadoxHighestStatId(enum BattlerId battler);
u32 GetParadoxBoostedStatId(enum BattlerId battler);
//end of EE stuff

//Custom FR stuff
bool8 CanActivateExpShare(void);
bool8 CanActivateExpNull(void);
//condition for using Exp items

//new personality searches for revamped infatuation setup
u32 IsPersonalityOnSide(enum BattlerId battlerId, u32 MonPid);
u32 IsMonOnOpposingSide(enum BattlerId battlerId, u32 MonPid);
u32 GetBattlerFromPersonality(u32 MonPid);

//cacophony based functions - also affects perish song, bypasses walls and protection
//and sets sleep and confusion effects to max duration on status set
bool8 ShouldCacophonyBoostAccuracy(u16 move);
bool8 ShouldCacophonyBoostEffectChance(u16 move);
bool8 ShouldCacophonyElevateMoveEffect(u16 move);
void CacophonyElevateMoveEffect(void);

//reworked function to include moldbreaker negate for cleaner use
bool8 DoesBattlerGetTypeBasedAffinity(enum Ability atkAbility, enum BattlerId battlerToCheck, enum Ability battlerAbility, u8 typeFactor); //for new category of abiility, replace sipmle checks for isbattler type
//was still tweaking unsure if keep
u8 ShouldActivateBindingBand(void); //function made for attempt setup pre healthbar drop activation

//checks for type other than user
//added for new idea plus/minus buff 
u32 IsTypeOnFieldExcept(enum BattlerId battler, enum Type type); 



bool8 CanSurviveInstantKOWithSturdy(enum BattlerId battler); //for sturdy conditions 

bool8 CanActivateForewarnAnticipation(enum BattlerId battler);
bool8 IsFixationMoveEffect(u16 move); //SETUP FOR new category of move inspired by legends arceus

/*//used in battle_main unsure if  still need
u8 ShouldAbilityAbsorb(u16 move); //ATTEMPT workaroud for absorb abilty/lightning rod targetting
//two custom functions for ability absorb along w new macro should do what I need
bool32 CanAbilityAbsorb(u8 MoveUser, u8 AbilityUser, u8 MoveType);
bool32 DoesBattlerAbilityAbsorbMoveType(u8 moveTarget, u8 MoveType);
u8 CanMovebeRedirected(void); //for adjusting absorb ability targetting
bool8 IscurrentMonOnFieldAtPos(struct Pokemon *mon, u8 position); //check mon is field/well checks battler side not entire field just a check for if mon is in battle vs party
bool32 HasWeatherEffect(void); //meant to replace macro for Weather_has_effect
void ClearMoldBreakerSetStatus(enum BattlerId battler); //plan for moldbreaker affinity bypass
*/
//will remove sleep clause
bool32 CanBeSlept(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum SleepClauseBlock isBlockedBySleepClause);
bool32 CanBePoisoned(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef);
bool32 CanBeBurned(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability ability);
bool32 CanBeParalyzed(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef);
bool32 CanBeFrozen(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef);
bool32 CanGetFrostbite(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityDef);
bool32 CanSetNonVolatileStatus(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum MoveEffect secondaryMoveEffect, enum ResultOption option);
bool32 CanBeConfused(enum BattlerId battler);
u32 GetBattlerAffectionHearts(enum BattlerId battler);
void TryToRevertMimicryAndFlags(void);
bool32 BattleArenaTurnEnd(void);
u32 CountBattlerStatIncreases(enum BattlerId battler, bool32 countEvasionAcc);
bool32 BattlerHasCopyableChanges(enum BattlerId battler);
bool32 ChangeTypeBasedOnTerrain(enum BattlerId battler);
void RemoveConfusionStatus(enum BattlerId battler);
u8 GetBattlerGender(enum BattlerId battler);
bool32 AreBattlersOfOppositeGender(enum BattlerId battler1, enum BattlerId battler2);
bool32 AreBattlersOfSameGender(enum BattlerId battler1, enum BattlerId battler2);
u32 CalcSecondaryEffectChance(enum BattlerId battler, enum Ability battlerAbility, const struct AdditionalEffect *additionalEffect);
bool32 MoveEffectIsGuaranteed(enum BattlerId battler, enum Ability battlerAbility, const struct AdditionalEffect *additionalEffect);
void GetBattlerTypes(enum BattlerId battler, bool32 ignoreTera, enum Type types[/*static*/ 3]);//think just remove static part and can use without reworkign base stat types
enum Type GetBattlerType(enum BattlerId battler, u32 typeIndex, bool32 ignoreTera);
bool8 CanMonParticipateInSkyBattle(struct Pokemon *mon);
void RemoveBattlerType(enum BattlerId battler, enum Type type);
enum Type GetBattleMoveType(enum Move move);
void TryActivateSleepClause(enum BattlerId battler, u32 indexInParty);
void TryDeactivateSleepClause(enum BattlerId battlerSide, u32 indexInParty);
bool32 IsSleepClauseActiveForSide(enum BattlerId battlerSide);
bool32 IsSleepClauseEnabled(void);
void ClearDamageCalcResults(void);
u32 DoesDestinyBondFail(enum BattlerId battler);
bool32 IsMoveEffectBlockedByTarget(enum Ability ability);
bool32 SetTargetToNextPursuiter(enum BattlerId battlerDef);
bool32 IsPursuitTargetSet(void);
void ClearPursuitValuesIfSet(enum BattlerId battler);
void ClearPursuitValues(void);
bool32 HasWeatherEffect(void);
bool32 IsFutureSightAttackerInParty(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move);
bool32 HadMoreThanHalfHpNowDoesnt(enum BattlerId battler);
void ChooseStatBoostAnimation(enum BattlerId battler);
void UpdateStallMons(void);
bool32 TrySwitchInEjectPack(enum EjectPackTiming timing);
bool32 EmergencyExitCanBeTriggered(enum BattlerId battler);
bool32 TryTriggerSymbiosis(enum BattlerId battler, u32 ally);
bool32 TrySymbiosis(enum BattlerId battler, u32 itemId, bool32 moveEnd);
void BestowItem(enum BattlerId battlerAtk, enum BattlerId battlerDef);
ARM_FUNC u32 GetBattlerVolatile(enum BattlerId battler, enum Volatile _volatile);
void SetMonVolatile(enum BattlerId battler, enum Volatile _volatile, u32 newValue);
bool32 ItemHealMonVolatile(enum BattlerId battler, u16 itemId);
void PushHazardTypeToQueue(u32 side, enum Hazards hazardType);
bool32 IsHazardOnSide(u32 side, enum Hazards hazardType);
bool32 AreAnyHazardsOnSide(u32 side);
void RemoveAllHazardsFromField(u32 side);
bool32 IsHazardOnSideAndClear(u32 side, enum Hazards hazardType);
void RemoveHazardFromField(u32 side, enum Hazards hazardType);
bool32 CanMoveSkipAccuracyCalc(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum Move move, enum ResultOption option);
u32 GetTotalAccuracy(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, enum Ability atkAbility, enum Ability defAbility, enum HoldEffect atkHoldEffect, enum HoldEffect defHoldEffect);
bool32 IsSemiInvulnerable(enum BattlerId battler, enum SemiInvulnerableExclusion excludeCommander);
bool32 BreaksThroughSemiInvulnerablity(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability abilityAtk, enum Ability abilityDef, enum Move move);
bool32 HasPartnerTrainer(enum BattlerId battler);
bool32 IsAffectedByPowderMove(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect);
enum Move GetNaturePowerMove(enum BattlerId battler);
void RemoveAbilityFlags(enum BattlerId battler);
void CheckSetUnburden(enum BattlerId battler);
bool32 IsDazzlingAbility(enum Ability ability);
bool32 IsAllowedToUseBag(void);
bool32 IsAnyTargetTurnDamaged(enum BattlerId battlerAtk);
bool32 IsAnyTargetAffected(void);
bool32 IsMimikyuDisguised(enum BattlerId battler);
bool32 IsDoubleSpreadMove(void);
bool32 IsBattlerInvalidForSpreadMove(enum BattlerId battlerAtk, enum BattlerId battlerDef);
void SetStartingStatus(enum StartingStatus status);
void ResetStartingStatuses(void);
bool32 IsUsableWhileAsleepEffect(enum BattleMoveEffects effect);
void SetWrapTurns(enum BattlerId battler, enum HoldEffect holdEffect);
bool32 ChangeOrderTargetAfterAttacker(void);
void TryUpdateEvolutionTracker(u32 evolutionCondition, u32 upAmount, enum Move usedMove);
bool32 CanUseMoveConsecutively(enum BattlerId battler);
void TryResetConsecutiveUseCounter(enum BattlerId battler);
void SetOrClearRageVolatile(void);

#endif // GUARD_BATTLE_UTIL_H
