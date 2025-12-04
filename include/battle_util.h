#ifndef GUARD_BATTLE_UTIL_H
#define GUARD_BATTLE_UTIL_H

#include "global.h"

#define MOVE_LIMITATION_ZEROMOVE                (1 << 0)
#define MOVE_LIMITATION_PP                      (1 << 1)
#define MOVE_LIMITATION_DISABLED                (1 << 2)
#define MOVE_LIMITATION_TORMENTED               (1 << 3)
#define MOVE_LIMITATION_TAUNT                   (1 << 4)
#define MOVE_LIMITATION_IMPRISON                (1 << 5)

//vsonic important more need add here from EE
#define MOVE_LIMITATIONS_ALL                    0xFF


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
#define ABILITYEFFECT_ONETURN_SWITCHIN_RESOLUTION  0x19
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

#define ITEMEFFECT_ON_SWITCH_IN                 0x0
#define ITEMEFFECT_NORMAL                       0x1
#define ITEMEFFECT_MOVE_END                     0x3
#define ITEMEFFECT_KINGSROCK          0x4		//removed shell bell from this effect and renamed to just kingsrock
#define ITEMEFFECT_TARGET                       0x5
#define ITEMEFFECT_ORBS                         0x6
#define ITEMEFFECT_LIFEORB_SHELLBELL            0x7		
#define ITEMEFFECT_USE_LAST_ITEM                0x8


#define BS_GET_TARGET                   0
#define BS_GET_ATTACKER                 1
#define BS_GET_EFFECT_BANK              2
#define BS_GET_SCRIPTING_BANK           10
#define BS_GET_PLAYER1                  11
#define BS_GET_OPPONENT1                12
#define BS_GET_PLAYER2                  13
#define BS_GET_OPPONENT2                14

u8 GetBattlerForBattleScript(u8 caseId);

void PressurePPLose(u8 target, u8 attacker, u16 move);
void PressurePPLoseOnUsingImprison(u8 attacker);
void PressurePPLoseOnUsingPerishSong(u8 attacker);
void MarkAllBattlersForControllerExec(void);
void MarkBattlerForControllerExec(u8 battlerId);
void MarkBattlerReceivedLinkData(u8 battlerId);
const u8* CancelMultiTurnMoves(u32 battler);
bool32 WasUnableToUseMove(u32 battler);
void PrepareStringBattle(u16 stringId, u32 battler);
void ResetSentPokesToOpponentValue(void);
void sub_8017434(u8 battler);
void UpdateSentPokesToOpponentValue(u8 battler);
void BattleScriptPush(const u8 *bsPtr);
void BattleScriptPushCursor(void);
void BattleScriptCall(const u8 *bsPtr);
void BattleScriptPop(void);
u8 TrySetCantSelectMoveBattleScript(u32 battler);
u8 CheckMoveLimitations(u32 battler, u8 unusableMoves, u16 check);
bool32 AreAllMovesUnusable(u32 battler);
u8 GetImprisonedMovesCount(u8 battlerId, u16 move);
u8 DoFieldEndTurnEffects(void);
s32 GetDrainedBigRootHp(u32 battler, s32 hp);
u8 DoBattlerEndTurnEffects(void);
bool32 HandleWishPerishSongOnTurnEnd(void);
bool8 HandleFaintedMonActions(void);
void ClearRageStatuses(u8 battler);
u8 AtkCanceller_UnableToUseMove(void);
u8 AtkCanceller_UnableToUseMove2(void);
bool8 IsFloatingSpecies(u16 species);
bool8 IsFlyingTypeSpeciesUnableToFly(u16 battler); //used just for trap effect debuff logic
bool8 IsBattlerGrounded(u8 battlerId);
bool8 IsFloatingTargetImmunetoGroundMoves(u8 battler_atk, u8 battler_def, u16 move, u8 moveType);
bool8 HasNoMonsToSwitch(u8 battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2);
bool32 TryChangeBattleWeather(u8 battler, u32 weatherEnumId, bool32 viaAbility);
u8 CastformDataTypeChange(u8 battler);
u32 AbilityBattleEffects(u32 caseID, u32 battler, u32 ability, u32 special, u32 moveArg);
void BattleScriptExecute(const u8 *BS_ptr);
void BattleScriptPushCursorAndCallback(const u8 *BS_ptr);
u32 ItemBattleEffects(enum ItemCaseId caseID, u32 battler, bool32 moveTurn);
void ClearDestinyBondGrudge(u8 battlerId);
void HandleAction_RunBattleScript(void);
u8 GetMoveTarget(u16 move, u8 setTarget);
u32 SetRandomTarget(u32 battlerId);
bool32 IsAffectedByFollowMe(u32 battlerAtk, u32 defSide, u32 move);
u8 IsMonDisobedient(void);
//bool32 SetIllusionMon(struct Pokemon *mon, u32 battlerId);
u32 GetBattleMoveSplit(u32 moveId);
u32 GetBattleMoveDamageCategory(u32 attackerId, u16 move);
bool8 IsBattlerAlive(u8 battlerId);
bool8 IsBlackFogNotOnField(void);
u32 GetBattlerAbility(u32 battler);
u32 GetBattlerWeight(u8 battlerId);
u32 GetFlingPowerFromItemId(u32 itemId);
//u16 GetPrimalReversionSpecies(u16 preEvoSpecies, u16 heldItemId);
//u16 GetMegaEvolutionSpecies(u16 preEvoSpecies, u16 heldItemId);
//u16 GetWishMegaEvolutionSpecies(u16 preEvoSpecies, u16 moveId1, u16 moveId2, u16 moveId3, u16 moveId4);
bool32 CanMegaEvolve(u32 battler);  //updated from ee new version
//void UndoMegaEvolution(u32 monId);  no longer used
bool32 IsBattlerAffectedByHazards(u32 battler, bool32 toxicSpikes);
void UndoFormChange(u32 monId, u32 side, bool32 isSwitchingOut);
bool32 DoBattlersShareType(u32 battler1, u32 battler2);
bool32 CanBattlerEscape(u32 battler);
bool32 IsHealBlockPreventingMove(u32 battler, u32 move);
u32 IsAbilityPreventingEscape(u32 battlerId);
u32 IsAbilityOnFieldExcept(u32 battlerId, u32 ability);
u32 IsAbilityOnField(u32 ability); 
u32 GetBattlerHoldEffect(u32 battler, bool32 checkNegating);
u32 GetBattlerHoldEffectIgnoreAbility(u32 battler, bool32 checkNegating);
u32 GetBattlerHoldEffectInternal(u32 battler, bool32 checkNegating, bool32 checkAbility);
u32 GetBattlerHoldEffectParam(u8 battlerId, u32 itemId);
bool8 IsMoveMakingContact(u16 move, u8 battlerAtk); //made bool8 since its just a true false return
bool8 CanBattlerGetOrLoseItem(u8 battlerId, u16 itemId); //same as above
struct Pokemon *GetIllusionMonPtr(u32 battlerId);
void ClearIllusionMon(u32 battlerId);
bool32 SetIllusionMon(struct Pokemon *mon, u32 battlerId);
u32 IsAbilityOnSide(u32 battlerId, u32 ability);
u32 IsAbilityOnOpposingSide(u32 battlerId, u32 ability);
u32 DoesSideHaveAbility(u32 battlerId, u32 ability); // //adapted abilityonside function that doesn't use getbattlerability
bool8 DoesBattlerHaveSureHitAbility(u8 battlerId);
bool32 CanFling(u8 battlerId);
bool32 IsRolePlayBannedAbilityAtk(u16 ability);  //looping array kept 32
bool32 IsRolePlayBannedAbility(u16 ability);
bool32 IsSkillSwapBannedAbility(u16 ability);
bool32 IsWorrySeedBannedAbility(u16 ability);
bool32 IsGastroAcidBannedAbility(u16 ability);
bool32 IsMoldBreakerAffectedAbility(u16 ability); //new addition to clean up get battler ability
bool32 IsEntrainmentBannedAbilityAttacker(u16 ability);
bool32 IsEntrainmentTargetOrSimpleBeamBannedAbility(u16 ability);
bool32 IsBattlerTerrainAffected(u8 battlerId, u32 terrainFlag);
bool8 IsMoveCounterAttack(u16 move); 
bool32 CanSleep(u8 battlerId);
bool32 CanPoisonType(u8 battlerAttacker, u8 battlerTarget);
bool32 CanBePoisoned(u8 PoisonUser, u8 PoisonTarget); //actually needs to be different from type
bool32 CanBeBurned(u8 battlerId);
bool32 CanBeParalyzed(u8 battlerId);
bool32 CanBeParalyzedViaAbility(u8 battlerId);
bool32 CanBeFrozen(u8 battlerId);
bool32 CanThaw(u32 move, u32 battler); //always use gcurrentmove hope work, need rewrite for modern update
bool32 CanBeConfused(u8 battlerId);
bool32 CanBattlerHeal(u8 battlerId); //simplify heal check
bool32 CanTeleport(u8 battlerId); //new teleport logic
bool32 HasEnoughHpToEatBerry(u8 battlerId, u32 hpFraction, u16 itemId);
bool32 ShouldPranksterBoostedMoveFail(u16 move, u8 battlerwithPrankster, u8 battlerDef, bool32 checkTarget);
bool32 IsMoonbasedMove(u16 move); //in prep for lunar power etc.
bool32 CompareStat(u8 battlerId, u8 statId, u8 cmpTo, u8 cmpKind);
bool32 IsBattlerWeatherAffected(u8 battlerId, u32 weatherFlags);
u16 GetUsedHeldItem(u8 battler);
bool32 TryRoomService(u8 battlerId);
bool32 TestSheerForceFlag(u8 battler, u16 move);
u8 TryHandleSeed(u8 battler, u32 terrainFlag, u8 statId, u16 itemId, bool32 execute);
void TryToRevertMimicry(void);
void TryToApplyMimicry(u8 battlerId, bool8 various);
void RestoreBattlerOriginalTypes(u8 battlerId);
void MulModifier(uq4_12_t *modifier, u16 val);
u32 ApplyModifier(uq4_12_t modifier, u32 val);
bool32 UnnerveOn(u32 battlerId, u32 itemId);
bool32 ShouldIgnoreBattlerHeldItem(u32 battler); //combine klutz mega primal logic for ignoring item, basis for mega form upgrade
void TryRestoreStolenItems(void);
void TrySaveExchangedItem(u8 battlerId, u16 stolenItem);
bool32 CanActivateTimeControl(u32 battler);
bool32 TryActivateBattlePoisonHeal(u32 battler);   //replaced normal poisonheal checks, allows use for poison types
bool32 TryActivateHeatTrance(u32 battler);
uq4_12_t CalcTypeEffectivenessMultiplier(u16 move, u8 moveType, u8 battlerAtk, u8 battlerDef, bool32 recordAbilities);
u32 GetBattlerMoveTargetType(u8 battlerId, u16 move); //need port these two fully
bool32 CanTargetBattler(u8 battlerAtk, u8 battlerDef, u16 move);
u16 GetTypeModifier(u8 atkType, u8 defType);
u32 GetMoveSlot(u16 *moves, u32 move); //added w battle ai port
//u16 CalcPartyMonTypeEffectivenessMultiplier(u16 move, u16 speciesDef, u16 abilityDef);  ported in case, but pretty sure I have no use for this, as these are just for reading battlre data and running dmg calc predictions
s32 CalculateMoveDamageAndEffectiveness(u16 move, u8 battlerAtk, u8 battlerDef, u8 moveType, u16 *typeEffectivenessModifier);
//learned defined need be on one line, this should be logic for thawing i.e remove frozen status
//removed fire fang restriction, any heat transafer is good enough

//new custom function, for storing ability timers by battler, 
//instead of in disable struct so lasts all battle
//keeps from being reset on switch/faint
u8 GetAbilityTimer(u16 ability);
//reworked function to include moldbreaker negate for cleaner use
bool8 DoesBattlerGetTypeBasedAffinity(u32 attacker, u16 atkability, u32 battler, u16 battlerAbility, u8 typeFactor); //for new category of abiility, replace sipmle checks for isbattler type
u8 ShouldActivateBindingBand(void); //function made for attempt setup pre healthbar drop activation

u8 ShouldAbilityAbsorb(u16 move); //ATTEMPT workaroud for absorb abilty/lightning rod targetting

bool32 TryRemoveScreens(u8 battler); //made non-static to use with brick break too

bool32 TestMoveFlags(u16 move, u32 flag);

void SetAtkCancellerForCalledMove(void);

//two custom functions for ability absorb along w new macro should do what I need
bool32 CanAbilityAbsorb(u8 MoveUser, u8 AbilityUser, u8 MoveType);
bool32 DoesBattlerAbilityAbsorbMoveType(u8 moveTarget, u8 MoveType);
u8 CanMovebeRedirected(void); //for adjusting absorb ability targetting

bool8 CanSurviveInstantKOWithSturdy(u8 battler); //for sturdy conditions 

s32 CountUsablePartyMons(u32 battlerId);

bool8 CanActivateExpShare(void);
bool8 CanActivateExpNull(void);
//condition for using Exp items

bool8 IsBattlerUnderProtectEffect(u8 battler);
void ClearMoldBreakerSetStatus(u8 battler);

bool32 ShouldActivateFugue(u32 battleratk, u32 battlerdef);
bool32 ShouldActivateObliviousLike(u32 battler); //oblivious femme fatale ability block was constalty resetting cuz didn't have top condition

//cacophony based functions - also affects perish song, bypasses walls and protection
//and sets sleep and confusion effects to max duration on status set
bool8 ShouldCacophonyBoostAccuracy(u16 move);
bool8 ShouldCacophonyBoostEffectChance(u16 move);
bool8 ShouldCacophonyElevateMoveEffect(u16 move);
void CacophonyElevateMoveEffect(void);
u8 GetMoveType(u32 moveType, u32 btlAttacker);
void GetBattlerTypes(u32 battler, bool32 ignoreTera, u32 types[/*static*/ 3]); //according to mcgriffin static check should work w my compiler version but doesn't.. advised remove static for now
u32 GetBattlerType(u32 battler, u32 typeIndex, bool32 ignoreTera);
u32 CountBattlerStatIncreases(u32 battler, bool32 countEvasionAcc);
bool32 CheckBattlerHpThreshold(u32 battler, u8 Comparison, u8 percentHp);
bool32 IsMoldBreakerTypeAbilityActive(u32 battler, u32 ability);
bool32 IsNeutralizingGasTypeAbilityActive(u32 battler, u32 ability); //attempt simplify getbattlerability logic

//added from EE for form change update (not planning to use for transform/ditto)
bool32 TryBattleFormChange(u8 battlerId, u16 method); //actualy doesn't work on transformed mon, just returns false
bool32 DoesSpeciesUseHoldItemToChangeForm(u16 species, u16 heldItemId);
bool32 CanBattlerFormChange(u8 battlerId, u16 method);
u16 GetBattleFormChangeTargetSpecies(u8 battlerId, u16 method);
bool32 IsBattlerMegaEvolved(u8 battlerId);
bool32 IsBattlerPrimalReverted(u8 battlerId);
bool32 IsBattlerUltraBeast(u8 battlerId);
bool32 IsSpeciesUltraBeast(u16 species);

bool8 IscurrentMonOnFieldAtPos(struct Pokemon *mon, u8 position); //check mon is field/well checks battler side not entire field just a check for if mon is in battle vs party
//checks for type other than user
//added for new idea plus/minus buff 
u32 IsTypeOnField(u32 battlerId, u8 type); 
s32 DoMoveDamageCalc(u16 move, u8 battlerAtk, u8 battlerDef, u8 moveType, s32 fixedBasePower,
    bool32 isCrit, bool32 randomFactor, bool32 updateFlags, u16 typeEffectivenessModifier);

u16 GetMoveEffect(u16 move);
u16 SanitizeMoveId(u16 move);
bool32 WeatherHasEffect(void); //meant to replace macro for Weather_has_effect
bool8 CanActivateForewarnAnticipation(u8 battler);
bool8 IsFixationMoveEffect(u16 move); //SETUP FOR new category of move inspired by legends arceus

enum {
    OBEYS,
    DISOBEYS_LOAFS,
    DISOBEYS_HITS_SELF,
    DISOBEYS_FALL_ASLEEP,
    DISOBEYS_WHILE_ASLEEP,
    DISOBEYS_RANDOM_MOVE,
};

//rewokr make easier,
//all fire type or fire argument if two turned effect
//or has effect burn hit
//remove power condition
//use dynamic type so hidden power etc. can also work
//compare against emerald/research
//according to EE it has some special logic for fire type removal moves
//i.e burn up etc.
//understand now, burn up should fail if user is not type fire
//under that condition it shouldn't thaw
#define THAW_CONDITION(move, battler) ((gBattleMoves[move].effect == EFFECT_BURN_HIT) || (gBattleStruct->dynamicMoveType == TYPE_FIRE || gBattleMoves[move].type == TYPE_FIRE) || (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE && gBattleMoves[move].argument == TYPE_FIRE) || (gBattleMoves[move].effect == EFFECT_LOSETYPE_HIT && gBattleMoves[move].argument == TYPE_FIRE && IS_BATTLER_OF_TYPE(battler, TYPE_FIRE)))

//#define THAW_CONDITION(move) ((move == MOVE_SCALD) || (((gBattleMoves[move].type == TYPE_FIRE) || (gBattleMoves[move].argument == TYPE_FIRE)) && (gBattleMoves[move].power >= 60 || gDynamicBasePower >= 60)))

#define HEALING_EFFECT ((EFFECT_RESTORE_HP || EFFECT_REST || EFFECT_MORNING_SUN || EFFECT_MOONLIGHT || EFFECT_SYNTHESIS || EFFECT_HEAL_PULSE || EFFECT_HEALING_WISH || EFFECT_ROOST || EFFECT_SWALLOW || EFFECT_WISH || EFFECT_SOFTBOILED || EFFECT_ABSORB))

static const u8 gSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 gHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
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
extern const u16 gAbilitiesAffectedByMoldBreaker[];

#endif // GUARD_BATTLE_UTIL_H
