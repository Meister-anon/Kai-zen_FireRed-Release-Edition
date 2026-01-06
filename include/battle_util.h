#ifndef GUARD_BATTLE_UTIL_H
#define GUARD_BATTLE_UTIL_H

#include "global.h"

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
enum FunctionCallOption
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
};//add new effect for pheonix ability that combines fields w stat cleanse

enum FieldEffectCases
{
    FIELD_EFFECT_TRAINER_STATUSES,
    FIELD_EFFECT_OVERWORLD_TERRAIN,
    FIELD_EFFECT_OVERWORLD_WEATHER,
};

enum AbilityEffect
{
    ABILITYEFFECT_ON_SWITCHIN,
    ABILITYEFFECT_ENDTURN,
    ABILITYEFFECT_MOVE_END_ATTACKER,
    ABILITYEFFECT_PRE_HIT_REACT, // new effect for color change
    ABILITYEFFECT_COLOR_CHANGE, // Color Change / Berserk / Anger Shell
    ABILITYEFFECT_MOVE_END,
    ABILITYEFFECT_IMMUNITY,
    ABILITYEFFECT_SYNCHRONIZE,
    ABILITYEFFECT_ATK_SYNCHRONIZE,
    ABILITYEFFECT_MOVE_END_OTHER,
    ABILITYEFFECT_MOVE_END_FOES_FAINTED, // Moxie-like abilities / Battle Bond / Magician

    // On Switch in
    ABILITYEFFECT_TERA_SHIFT,
    ABILITYEFFECT_NEUTRALIZINGGAS,
    ABILITYEFFECT_UNNERVE,
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

//unsure how pledge move work with this
//has some interaction w redirection
//first mon in combo sets target
//but second mon is responsible for actual attack
//checked bulbapedia seems sky drop is immune to redirection
//via follow me or rage powder and since no ability presently exists
//that draws in specifically flying moves that's all that could effect it
//but I feel safe in excluding it from redirection based on that
//think will make function and add as move characteristic
//with that think will remove snipe_shot effect
//as presently affect was only for redirection there
//sky drop keeps effect but still replaced in function
static inline bool32 PreventsRedirection(u32 battlerAtk, u32 move)
{
    enum Ability ability = GetBattlerAbility(battlerAtk);

    if (IsFogOnField()
    || DoesMovePreventRedirection(move)
    || IsAbilityAndRecord(battlerAtk, ability, ABILITY_PROPELLER_TAIL)
    || IsAbilityAndRecord(battlerAtk, ability, ABILITY_STALWART)
    )
        return TRUE;
    
    return FALSE;
}

static inline u32 GetAbilityTimer(enum Ability ability)
{
    switch (ability)
    {
        case ABILITY_SLOW_START:
            return 3;
        break;
        case ABILITY_WONDER_GUARD:
            return 4; //might use 5
        break;
        
        case ABILITY_SPECTRE:
            return 2;
        break; //causes memory corruption to rear its head, I give up
        //I'm gonna just swap to modern fix everything as it builds and pray to GOD 
        //I find the damned source of the issue
        //awesome fixes from building modern was able to address memory corruption
        //linked w this at least
        //still need test make sure effects still work, (believe they should)

    }
}

//missing include
static inline void SetSingleUseAbilityValues(u32 battler, enum Ability ability)
{
    GetBattlerPartyState(battler)->SingleUseAbilityTimers = GetAbilityTimer(ability);
    GetBattlerPartyState(battler)->usedSingleUseAbility = ability;
}

//ok fog already blocks redirection from above
//with far more reliable exclusions
//don't want/need too many blocks here
//think just want to cut down preoccupied status
//think lock to confusion wrap and bide
//think will leave status 1 as main block
//will leave lightning rod with advantage still
//which is good, if paralysis is main status to set
//it'll mostly be excluded for lightning rod mon
static inline bool32 CanBattlerAbilityDrawInMove(u32 battlerDef)
{
    if (gBattleMons[battlerDef].status1 == 0 
    && !gDisableStructs[battlerDef].rechargeTimer 
    && !(gBattleMons[battlerDef].status2 & PREOCCUPIED_STATUS) 
    && !(gStatuses3[battlerDef] & STAUS3_VULNERABLE) 
    && !(gBattleMons[battlerDef].status4 & ITS_A_TRAP_STATUS4))
        return TRUE;
    
    return FALSE;
}

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
    CANCELER_WEATHER_PRIMAL,
    CANCELER_FOCUS_PRE_GEN5,
    CANCELER_MOVE_FAILURE,
    CANCELER_POWDER_STATUS,
    CANCELER_PRIORITY_BLOCK,
    CANCELER_PROTEAN,
    CANCELER_EXPLODING_DAMP,
    CANCELER_EXPLOSION,
    CANCELER_MULTIHIT_MOVES,
    CANCELER_MULTI_TARGET_MOVES,
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
    MOVE_STEP_BREAK, // Breaks out of the function to run a script
    MOVE_STEP_FAILURE, // Same as break but breaks out of it due to move failure and jumps to script that handles the failure
};

extern const struct TypePower gNaturalGiftTable[];

struct BattleContext
{
    u32 battlerAtk:3;
    u32 battlerDef:3;
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
    u32 padding:25;
};

// Helper struct to keep the arg list small and prevent constant recalculations of abilities/hold effects.
struct BattleCalcValues
{
    u32 battlerAtk:3;
    u32 battlerDef:3;
    u32 move:16;
    u32 padding:10;
    enum Ability abilities[MAX_BATTLERS_COUNT];
    enum HoldEffect holdEffects[MAX_BATTLERS_COUNT];
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

// Lowest and highest percentages used for damage roll calculations
#define DMG_ROLL_PERCENT_LO 85
#define DMG_ROLL_PERCENT_HI 100

// Crit chance exceptions
#define CRITICAL_HIT_BLOCKED -1
#define CRITICAL_HIT_ALWAYS  -2

extern const u8 *const gPlayCryanims[];

u8 GetBattlerForBattleScript(u8 caseId);

u32 GetFuryCutterAccuracy(u32 battlerAtk, u32 move);
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
s32 MistyTerrainHealBoost(u32 battler, s32 healamount);
u8 DoBattlerEndTurnEffects(void);
bool32 HandleWishPerishSongOnTurnEnd(void);
bool8 HandleFaintedMonActions(void);
void ClearRageStatuses(u8 battler);
u8 AtkCanceller_UnableToUseMove(void);
u8 AtkCanceller_UnableToUseMove2(void);
bool8 IsFloatingSpecies(u16 species);
bool8 IsFlyingTypeBattlerUnableToFly(u32 battler); //battle specific variant
bool8 CanFlyingTypeRecoverFromSmackDown(u32 battler); //for use w ascension timer prob rename later vsonic
bool8 IsBattlerGrounded(u8 battlerId);
bool8 IsFloatingTargetImmunetoGroundBasedMoves(u8 battler_atk, u8 battler_def, u16 move);
bool8 HasNoMonsToSwitch(u8 battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2);
bool32 TryChangeBattleWeather(u8 battler, u32 weatherEnumId, bool32 viaAbility);
u8 CastformDataTypeChange(u8 battler);
u32 AbilityBattleEffects(u32 caseID, u32 battler, u32 ability, u32 special, u32 moveArg);
void BattleScriptExecute(const u8 *BS_ptr);
void BattleScriptPushCursorAndCallback(const u8 *BS_ptr);
u32 ItemBattleEffects(enum ItemCaseId caseID, u32 battler, bool32 moveTurn);
void ClearDestinyBondGrudge(u8 battlerId);
void HandleAction_RunBattleScript(void);
u8 GetBattleMoveTarget(u16 move, u8 setTarget);
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
bool32 IsBattlerProtected(u32 battlerAtk, u32 battlerDef, u32 move);
u32 GetProtectType(enum ProtectMethod method);
u32 GetBattlerHoldEffect(u32 battler, bool32 checkNegating);
u32 GetBattlerHoldEffectIgnoreAbility(u32 battler, bool32 checkNegating);
u32 GetBattlerHoldEffectInternal(u32 battler, bool32 checkNegating, bool32 checkAbility);
u32 GetBattlerHoldEffectParam(u8 battlerId, u32 itemId);
bool32 CanBattlerAvoidContactEffects(u32 battlerAtk, u32 battlerDef, enum Ability abilityAtk, enum HoldEffect holdEffectAtk, u32 move);
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

bool32 IsPsychicTerrainAffected(u32 battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsMistyTerrainAffected(u32 battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsGrassyTerrainAffected(u32 battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsElectricTerrainAffected(u32 battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsAnyTerrainAffected(u32 battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses);
bool32 IsBattlerTerrainAffected(u32 battler, enum Ability ability, enum HoldEffect holdEffect, u32 fieldStatuses, u32 terrainFlag);
u32 GetHighestStatId(u32 battler);
u32 GetParadoxHighestStatId(u32 battler);
u32 GetParadoxBoostedStatId(u32 battler);

//new custom function, for storing ability timers by battler, 
//instead of in disable struct so lasts all battle
//keeps from being reset on switch/faint
u8 GetAbilityTimer(u16 ability);
//reworked function to include moldbreaker negate for cleaner use
bool8 DoesBattlerGetTypeBasedAffinity(u32 attacker, u32 battler, u8 typeFactor, bool32 checkAI); //for new category of abiility, replace sipmle checks for isbattler type
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

//new personality searches for revamped infatuation setup
u32 IsPersonalityOnSide(u32 battlerId, u32 MonPid);
u32 IsMonOnOpposingSide(u32 battlerId, u32 MonPid);
u32 GetBattlerFromPersonality(u32 MonPid);

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


bool32 HasWeatherEffect(void); //meant to replace macro for Weather_has_effect
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

u32 DoEndTurnEffects(void);

#endif // GUARD_BATTLE_UTIL_H
