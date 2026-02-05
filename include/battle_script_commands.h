#ifndef GUARD_BATTLE_SCRIPT_COMMANDS_H
#define GUARD_BATTLE_SCRIPT_COMMANDS_H

#include "global.h"
#include "constants/battle_script_commands.h"


#define STAT_CHANGE_WORKED      0
#define STAT_CHANGE_DIDNT_WORK  1

#define WINDOW_CLEAR            0x1
#define WINDOW_x80              0x80

void SetMoveEffect(enum BattlerId battler, u32 effectBattler, bool32 primary, bool32 certain);
u32 GetMoveTwoTurnAttackStringId(u16 move); //script chooser set values for charge turn of two turn moves
bool8 UproarWakeUpCheck(enum BattlerId battlerId);
u8 AI_TypeCalc(u16 move, u16 targetSpecies, u16 targetAbility);	//return value is u8 so function can stay u8, even if all elements aren't
u8 TypeCalc(u16 move, u8 attacker, u8 defender);
void AI_CalcDmg(u8 attacker, u8 defender);
bool32 IsMonGettingExpSentOut(void);
void BattleCreateYesNoCursorAt(void);
void BattleDestroyYesNoCursorAt(void);
bool32 CanBattlerSwitch(enum BattlerId battlerId);
void HandleBattleWindow(u8 xStart, u8 yStart, u8 xEnd, u8 yEnd, u8 flags);
u8 GetBattlerTurnOrderNum(enum BattlerId battlerId);
void BufferMoveToLearnIntoBattleTextBuff2(void);
void HazardClearNoMessage(enum BattlerId battler);
bool32 DoesSubstituteBlockMove(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 move);
bool32 DoesDisguiseBlockMove(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 move);
bool32 NoAliveMonsForEitherParty(void);
bool32 CanUseLastResort(enum BattlerId battlerId);
bool32 IsTelekinesisBannedSpecies(u16 species);
u32 IsFlowerVeilProtected(enum BattlerId battler);
u32 IsLeafGuardProtected(enum BattlerId battler);
bool32 IsShieldsDownProtected(enum BattlerId battler);
u32 IsAbilityStatusProtected(enum BattlerId battler);
bool32 TryResetBattlerStatChanges(enum BattlerId battler);
bool32 CanCamouflage(enum BattlerId battlerId);
void StealTargetItem(enum BattlerId battlerStealer, enum BattlerId battlerItem);
bool32 CanStealItem(enum BattlerId battlerStealing, enum BattlerId battlerItem, u16 item);
bool32 ProteanTryChangeType(enum BattlerId battler, u32 ability, u32 move, u32 moveType);
s32 AICalcCritChance(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 move, bool32 recordAbility);
u16 GetNaturePowerMove(void);
s8 GetInverseCritChance(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 move);
s32 AI_CalcDmgFormula(u8 attacker, u8 defender);
u32 GetTotalAccuracy(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 move, u32 atkAbility, u32 defAbility, u32 atkHoldEffect, u32 defHoldEffect);
bool32 IsStallActive(enum BattlerId battler); //new checks for ability stall
bool8 CanMultiTask(enum Ability abilityAtk, enum Move move);
bool32 TryKnockOffBattleScript(u32 loseitembattler, u32 EffectUser, u16 moveEffect);
u8 CanMoveHitSwitchingTarget(u16 move);
u8 IsExemptFromPursuit(enum BattlerId battler); //for blocking effect without needing separate battlescript
bool8 IsMoveAffectedByParentalBond(u16 move, enum BattlerId battlerId);
//EE function for recalc stats this used in place of transform logic for recalcs outside of transform and ditto
void RecalcBattlerStats(enum BattlerId battler, struct Pokemon *mon);
void CopyMonLevelAndBaseStatsToBattleMon(enum BattlerId battler, struct Pokemon *mon);
void CopyMonAbilityAndTypesToBattleMon(enum BattlerId battler, struct Pokemon *mon);

s32 CalculateMoveDamage(u16 move, enum BattlerId battlerAtk, enum BattlerId battlerDef, u8 moveType, s32 fixedBasePower, bool32 isCrit, bool32 randomFactor, bool32 updateFlags);

extern const u16 gCriticalHitChance[];	//made global, so can run in ai file

extern void (* const gBattleScriptingCommandsTable[])(void);

u8 GetCatchingBattler(void);
bool32 ProteanTryChangeType(enum BattlerId battler, enum Ability ability, enum Move move, enum Type moveType);
u8 GetFirstFaintedPartyIndex(enum BattlerId battlerId);
void SaveBattlerTarget(enum BattlerId battler);
void SaveBattlerAttacker(enum BattlerId battler);
bool32 CanBurnHitThaw(enum Move move);



#endif // GUARD_BATTLE_SCRIPT_COMMANDS_H
