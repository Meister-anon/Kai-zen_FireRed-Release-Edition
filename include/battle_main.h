#ifndef GUARD_BATTLE_MAIN_H
#define GUARD_BATTLE_MAIN_H

#include "battle_util.h"
#include "pokemon.h"
#include "constants/hold_effects.h"


struct TypeInfo
{
    u8 name[TYPE_NAME_LENGTH + 1];
    bool8 isHiddenPowerType; // Changing this for any type will change the distribution of all Hidden Power types from vanilla.
    u16 tmhmSpritePalOffset;
    bool8 isTeraType;
    //u8 *const TeraIndicatorGfx;
};
//replace sTMSpritePaletteOffsetByType
//each type pallete is 16 bytes, 
//so anything added would increase by 0x10
//did I work out something for sound type just in case?

// For displaying a multi battle partner's Pokémon in the party menu
struct MultiPartnerMenuPokemon
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 heldItem;
    /*0x04*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x0F*/ u8 level;
    /*0x10*/ u16 hp;
    /*0x12*/ u16 maxhp;
    /*0x14*/ u32 status;
    /*0x18*/ u32 personality;
    /*0x1C*/ u8 gender;
    /*0x1D*/ u8 language;
};

enum BattleIntroStates
{
    BATTLE_INTRO_STATE_GET_MON_DATA,
    BATTLE_INTRO_STATE_LOOP_BATTLER_DATA,
    BATTLE_INTRO_STATE_PREPARE_BG_SLIDE,
    BATTLE_INTRO_STATE_WAIT_FOR_BG_SLIDE,
    BATTLE_INTRO_STATE_DRAW_SPRITES,
    BATTLE_INTRO_STATE_DRAW_PARTY_SUMMARY,
    BATTLE_INTRO_STATE_WAIT_FOR_PARTY_SUMMARY,
    BATTLE_INTRO_STATE_INTRO_TEXT,
    BATTLE_INTRO_STATE_WAIT_FOR_INTRO_TEXT,
    BATTLE_INTRO_STATE_TRAINER_SEND_OUT_TEXT,
    BATTLE_INTRO_STATE_WAIT_FOR_TRAINER_SEND_OUT_TEXT,
    BATTLE_INTRO_STATE_TRAINER_1_SEND_OUT_ANIM,
    BATTLE_INTRO_STATE_TRAINER_2_SEND_OUT_ANIM,
    BATTLE_INTRO_STATE_WAIT_FOR_TRAINER_2_SEND_OUT_ANIM,
    BATTLE_INTRO_STATE_WAIT_FOR_WILD_BATTLE_TEXT,
    BATTLE_INTRO_STATE_PRINT_PLAYER_SEND_OUT_TEXT,
    BATTLE_INTRO_STATE_WAIT_FOR_PLAYER_SEND_OUT_TEXT,
    BATTLE_INTRO_STATE_PRINT_PLAYER_1_SEND_OUT_TEXT,
    BATTLE_INTRO_STATE_PRINT_PLAYER_2_SEND_OUT_TEXT,
    BATTLE_INTRO_STATE_SET_DEX_AND_BATTLE_VARS
};

enum FirstTurnEventsStates
{
    FIRST_TURN_EVENTS_START,
    FIRST_TURN_EVENTS_OVERWORLD_WEATHER,
    FIRST_TURN_EVENTS_TERRAIN,
    FIRST_TURN_EVENTS_STARTING_STATUS,
    FIRST_TURN_EVENTS_TOTEM_BOOST,
    FIRST_TURN_SWITCH_IN_EVENTS,
    FIRST_TURN_FAINTED_BATTLERS,
    FIRST_TURN_EVENTS_TRAINER_SLIDE_A,
    FIRST_TURN_EVENTS_TRAINER_SLIDE_B,
    FIRST_TURN_EVENTS_TRAINER_SLIDE_PARTNER,
    FIRST_TURN_EVENTS_END,
};

// defines for the u8 array gTypeEffectiveness
//#define TYPE_EFFECT_ATK_TYPE(i)((gTypeEffectiveness[i + 0]))    //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns
//#define TYPE_EFFECT_DEF_TYPE(i)((gTypeEffectiveness[i + 1]))    //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns
//#define TYPE_EFFECT_MULTIPLIER(i)((gTypeEffectiveness[i + 2]))  //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns

// defines for the gTypeEffectiveness multipliers
#define TYPE_MUL_NO_EFFECT          0
#define TYPE_MUL_NOT_EFFECTIVE      5
#define TYPE_MUL_NORMAL             10
#define TYPE_MUL_SUPER_EFFECTIVE    (155 / 10)//16  //changed from 20 to 15 to 16 for 1.6x dmg  change 1.55x seems works? messed up  forgot these get divided by 10 after heh

// special type table Ids
#define TYPE_FORESIGHT  0xFE
#define TYPE_ENDTABLE   0xFF

// defines for the 'DoBounceEffect' function
#define BOUNCE_MON          0x0
#define BOUNCE_HEALTHBOX    0x1


//extern const struct SpriteTemplate gUnknownDebugSprite;
extern const struct OamData gOamData_BattlerOpponent;
extern const struct OamData gOamData_BattlerPlayer;
extern const struct TypeInfo gTypesInfo[NUMBER_OF_MON_TYPES];
extern const u8 gStatusConditionString_PoisonJpn[8];
extern const u8 gStatusConditionString_SleepJpn[8];
extern const u8 gStatusConditionString_ParalysisJpn[8];
extern const u8 gStatusConditionString_BurnJpn[8];
extern const u8 gStatusConditionString_IceJpn[8];
extern const u8 gStatusConditionString_ConfusionJpn[8];
extern const u8 gStatusConditionString_LoveJpn[8];
extern const u8 *const gStatusConditionStringsTable[7][2];
extern const u16 gTypeEffectivenessTable[NUMBER_OF_MON_TYPES][NUMBER_OF_MON_TYPES]; //type table port
//extern const u8 gTypeEffectiveness[423]; //normal type array

void CB2_InitBattle(void);
void BattleMainCB2(void);
void FreeRestoreBattleData(void);
void CB2_QuitRecordedBattle(void);
void VBlankCB_Battle(void);
void SpriteCB_VsLetterDummy(struct Sprite *sprite);
void SpriteCB_VsLetterInit(struct Sprite *sprite);
//void CB2_InitEndLinkBattle(void);
u32 GetBattleBgAttribute(u8 arrayId, u8 caseId);
void SpriteCB_EnemyMon(struct Sprite *sprite);
void SpriteCallbackDummy2(struct Sprite *sprite);
void SpriteCB_FaintOpponentMon(struct Sprite *sprite);
void SpriteCB_ShowAsMoveTarget(struct Sprite *sprite);
void SpriteCB_HideAsMoveTarget(struct Sprite *sprite);
void SpriteCB_AllyMon(struct Sprite *sprite);
void SpriteCB_SetToDummy3(struct Sprite *sprite);
void SpriteCB_FaintSlideAnim(struct Sprite *sprite);
void DoBounceEffect(enum BattlerId battler, u8 which, s8 delta, s8 amplitude);
void EndBounceEffect(enum BattlerId battler, u8 which);
void SpriteCB_PlayerThrowInit(struct Sprite *sprite);
void UpdatePlayerPosInThrowAnim(struct Sprite *sprite);
void BattleDummy(void);
void BeginBattleIntro(void);


struct Volatiles; //struct pointer arg fix mostly issue of FR includes need overhaul later match EE
void SwitchInClearSetData(enum BattlerId battler, struct Volatiles *volatilesCopy);
const u8* FaintClearSetData(enum BattlerId battler);
void BattleTurnPassed(void);
u8 IsRunningFromBattleImpossible(enum BattlerId battler);
void UpdatePartyOwnerOnSwitch_NonMulti(enum BattlerId battler);
void SwitchTwoBattlersInParty(enum BattlerId battler, enum BattlerId battler2);
void SwitchPartyOrder(enum BattlerId battler);
void SwapTurnOrder(u8 id1, u8 id2);
u8 GetWhoStrikesFirst(enum BattlerId battler1, enum BattlerId battler2, bool8 ignoreChosenMoves);
u32 GetBattlerTotalSpeedStat(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect);
void RunBattleScriptCommands_PopCallbacksStack(void);
void RunBattleScriptCommands(void);
s32 GetChosenMovePriority(enum BattlerId battler, enum Ability ability);
s32 GetBattleMovePriority(enum BattlerId battler, enum Ability ability, enum Move move);
bool8 IsPriorityElevatedviaAbility(enum BattlerId battler); //new thing to track moves w boosted priority from abilities for queenly majesty
bool8 IsRivalBattle(u16 trainerNum);
bool32 IsWildMonSmart(void);
enum Type GetDynamicMoveType(struct Pokemon *mon, enum Move move, enum BattlerId battler, enum MonState monInBattle);
void SetTypeBeforeUsingMove(u32 move, enum BattlerId battlerAtk, u8 *typeStorage);

void SetJudgmentTypeString(u8 type); //make global since had move effect to battle_script_commands.c

void TryResetProtectUseCounter(enum BattlerId battler);


//EE stuff
s32 GetWhichBattlerFasterArgs(struct BattleCalcValues *calcValues, bool32 ignoreChosenMoves, u32 speedBattler1, u32 speedBattler2, s32 priority1, s32 priority2);
s32 GetWhichBattlerFasterOrTies(struct BattleCalcValues *calcValues, bool32 ignoreChosenMoves);
s32 GetWhichBattlerFaster(struct BattleCalcValues *calcValues, bool32 ignoreChosenMoves);
s32 Factorial(s32 n);
#endif // GUARD_BATTLE_MAIN_H
