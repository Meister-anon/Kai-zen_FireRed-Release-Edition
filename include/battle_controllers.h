#ifndef GUARD_BATTLE_CONTROLLERS_H
#define GUARD_BATTLE_CONTROLLERS_H

#include "global.h"
#include "battle.h"
#include "task.h"

enum
{
    REQUEST_ALL_BATTLE,
    REQUEST_SPECIES_BATTLE,
    REQUEST_HELDITEM_BATTLE,
    REQUEST_MOVES_PP_BATTLE,
    REQUEST_MOVE1_BATTLE,
    REQUEST_MOVE2_BATTLE,
    REQUEST_MOVE3_BATTLE,
    REQUEST_MOVE4_BATTLE,
    REQUEST_PP_DATA_BATTLE,
    REQUEST_PPMOVE1_BATTLE,
    REQUEST_PPMOVE2_BATTLE,
    REQUEST_PPMOVE3_BATTLE,
    REQUEST_PPMOVE4_BATTLE,
    REQUEST_UNUSED_13_BATTLE,
    REQUEST_UNUSED_14_BATTLE,
    REQUEST_UNUSED_15_BATTLE,
    REQUEST_UNUSED_16_BATTLE,
    REQUEST_OTID_BATTLE,
    REQUEST_EXP_BATTLE,
    REQUEST_HP_EV_BATTLE,
    REQUEST_ATK_EV_BATTLE,
    REQUEST_DEF_EV_BATTLE,
    REQUEST_SPEED_EV_BATTLE,
    REQUEST_SPATK_EV_BATTLE,
    REQUEST_SPDEF_EV_BATTLE,
    REQUEST_FRIENDSHIP_BATTLE,
    //REQUEST_POKERUS_BATTLE,
    REQUEST_MET_LOCATION_BATTLE,
    REQUEST_MET_LEVEL_BATTLE,
    REQUEST_MET_GAME_BATTLE,
    REQUEST_POKEBALL_BATTLE,
    REQUEST_ALL_IVS_BATTLE,
    REQUEST_HP_IV_BATTLE,
    REQUEST_ATK_IV_BATTLE,
    REQUEST_DEF_IV_BATTLE,
    REQUEST_SPEED_IV_BATTLE,
    REQUEST_SPATK_IV_BATTLE,
    REQUEST_SPDEF_IV_BATTLE,
    REQUEST_PERSONALITY_BATTLE,
    REQUEST_CHECKSUM_BATTLE,
    REQUEST_STATUS_BATTLE,
    REQUEST_LEVEL_BATTLE,
    REQUEST_HP_BATTLE,
    REQUEST_MAX_HP_BATTLE,
    REQUEST_ATK_BATTLE,
    REQUEST_DEF_BATTLE,
    REQUEST_SPEED_BATTLE,
    REQUEST_SPATK_BATTLE,
    REQUEST_SPDEF_BATTLE,
    REQUEST_COOL_BATTLE,
    REQUEST_BEAUTY_BATTLE,
    REQUEST_CUTE_BATTLE,
    REQUEST_SMART_BATTLE,
    REQUEST_TOUGH_BATTLE,
    //REQUEST_SHEEN_BATTLE,
    REQUEST_COOL_RIBBON_BATTLE,
    REQUEST_BEAUTY_RIBBON_BATTLE,
    REQUEST_CUTE_RIBBON_BATTLE,
    REQUEST_SMART_RIBBON_BATTLE,
    REQUEST_TOUGH_RIBBON_BATTLE,
};

enum { // Values given to the emit functions to choose gBattleResources->bufferA or gBattleResources->bufferB
    BUFFER_A,   //Values given to the emit functions to choose gBattleResources->bufferA or gBattleResources->bufferB
    BUFFER_B    //Values given to the emit functions to choose gBattleResources->bufferA or gBattleResources->bufferB
};

#define RESET_ACTION_MOVE_SELECTION     0
#define RESET_ACTION_SELECTION          1
#define RESET_MOVE_SELECTION            2

enum {
    LINK_STANDBY_MSG_STOP_BOUNCE,
    LINK_STANDBY_STOP_BOUNCE_ONLY,
    LINK_STANDBY_MSG_ONLY,
};

#define BALL_NO_SHAKES          0
#define BALL_1_SHAKE            1
#define BALL_2_SHAKES           2
#define BALL_3_SHAKES_FAIL      3
#define BALL_3_SHAKES_SUCCESS   4
#define BALL_TRAINER_BLOCK      5
#define BALL_GHOST_DODGE        6

//#define RET_VALUE_LEVELLED_UP   11

#define INSTANT_HP_BAR_DROP     0x7FFF

#define PARTY_SUMM_SKIP_DRAW_DELAY (1 << 7)

// Special return values in gBattleResources->bufferB from Battle Controller functions.
#define RET_VALUE_LEVELED_UP   11
#define RET_MEGA_EVOLUTION (1 << 7)
#define RET_GIMMICK       (1 << 7)  //believe same as above

struct BattleBoxMessageDisplay
{
    u8 unk : 7;
    u8 flag : 1;
};

struct HpAndStatus
{
    u16 hp;
    u32 status;
};

struct MovePpInfo
{
    u16 moves[MAX_MON_MOVES];
    u8 pp[MAX_MON_MOVES];
    u8 ppBonuses;
};

struct ChooseMoveStruct
{
    u16 moves[MAX_MON_MOVES];
    u8 currentPp[MAX_MON_MOVES];
    u8 maxPp[MAX_MON_MOVES];
    u16 species;
    u8 monType1;
    u8 monType2;
    u8 monType3;
    struct MegaEvolutionData mega;
};

enum
{
    CONTROLLER_GETMONDATA,
    CONTROLLER_GETRAWMONDATA,
    CONTROLLER_SETMONDATA,
    CONTROLLER_SETRAWMONDATA,
    CONTROLLER_LOADMONSPRITE,
    CONTROLLER_SWITCHINANIM,
    CONTROLLER_RETURNMONTOBALL,
    CONTROLLER_DRAWTRAINERPIC,
    CONTROLLER_TRAINERSLIDE,
    CONTROLLER_TRAINERSLIDEBACK,
    CONTROLLER_FAINTANIMATION,
    CONTROLLER_PALETTEFADE,
    CONTROLLER_SUCCESSBALLTHROWANIM,
    CONTROLLER_BALLTHROWANIM,
    CONTROLLER_PAUSE,
    CONTROLLER_MOVEANIMATION,
    CONTROLLER_PRINTSTRING,
    CONTROLLER_PRINTSTRINGPLAYERONLY,
    CONTROLLER_CHOOSEACTION,
    CONTROLLER_UNKNOWNYESNOBOX,
    CONTROLLER_CHOOSEMOVE,
    CONTROLLER_OPENBAG,
    CONTROLLER_CHOOSEPOKEMON,
    CONTROLLER_23,
    CONTROLLER_HEALTHBARUPDATE,
    CONTROLLER_EXPUPDATE,
    CONTROLLER_STATUSICONUPDATE,
    CONTROLLER_STATUSANIMATION,
    CONTROLLER_STATUSXOR,
    CONTROLLER_DATATRANSFER,
    CONTROLLER_DMA3TRANSFER,
    CONTROLLER_PLAYBGM,
    CONTROLLER_32,
    CONTROLLER_TWORETURNVALUES,
    CONTROLLER_CHOSENMONRETURNVALUE,
    CONTROLLER_ONERETURNVALUE,
    CONTROLLER_ONERETURNVALUE_DUPLICATE,
    CONTROLLER_CLEARUNKVAR,
    CONTROLLER_SETUNKVAR,
    CONTROLLER_CLEARUNKFLAG,
    CONTROLLER_TOGGLEUNKFLAG,
    CONTROLLER_HITANIMATION,
    CONTROLLER_CANTSWITCH,
    CONTROLLER_PLAYSE,
    CONTROLLER_PLAYFANFAREORBGM, //CONTROLLER_PLAYFANFAREORBGM
    CONTROLLER_FAINTINGCRY,
    CONTROLLER_INTROSLIDE,
    CONTROLLER_INTROTRAINERBALLTHROW,
    CONTROLLER_DRAWPARTYSTATUSSUMMARY,
    CONTROLLER_HIDEPARTYSTATUSSUMMARY,
    CONTROLLER_ENDBOUNCE,
    CONTROLLER_SPRITEINVISIBILITY,
    CONTROLLER_BATTLEANIMATION,
    CONTROLLER_LINKSTANDBYMSG,
    CONTROLLER_RESETACTIONMOVESELECTION,
    CONTROLLER_ENDLINKBATTLE,
    CONTROLLER_DEBUGMENU,
    /*new controllers should go here*/
    CONTROLLER_MOVEINFO,    //jump to summ screen move info to get move cat etc.
    CONTROLLER_TERMINATOR_NOP,
    CONTROLLER_CMDS_COUNT
};

extern struct BattleBoxMessageDisplay gUnusedControllerStruct; //absolutely NOT unused, without this text doesn't display in battle boxes

// general functions
//void HandleLinkBattleSetup(void);
void SetUpBattleVars(void);
void InitBtlControllers(void);
bool32 IsValidForBattle(struct Pokemon *mon);

u8 Rogue_GetBattleSpeedScale(void); //added for speed up PokAbbie
u8 GetBattleSpeedOption(void);

//void TryReceiveLinkBattleData(void);
//void PrepareBufferDataTransferLink(u32 battler, u32 bufferId, u16 size, u8 *data);

// emitters
void BtlController_EmitGetMonData(u32 battler, u32 bufferId, u8 requestId, u8 monToCheck);
void BtlController_EmitSetMonData(u32 battler, u32 bufferId, u8 requestId, u8 monToCheck, u8 bytes, void *data);
void BtlController_EmitLoadMonSprite(u32 battler, u32 bufferId);
void BtlController_EmitSwitchInAnim(u32 battler, u32 bufferId, u8 partyId, bool8 dontClearTransform, bool8 dontClearSubstituteBit);
void BtlController_EmitReturnMonToBall(u32 battler, u32 bufferId, bool8 skipAnim);
void BtlController_EmitDrawTrainerPic(u32 battler, u32 bufferId);
void BtlController_EmitTrainerSlide(u32 battler, u32 bufferId);
void BtlController_EmitTrainerSlideBack(u32 battler, u32 bufferId);
void BtlController_EmitFaintAnimation(u32 battler, u32 bufferId);
void BtlController_EmitBallThrowAnim(u32 battler, u32 bufferId, u8 caseId);
void BtlController_EmitMoveAnimation(u32 battler, u32 bufferId, u16 move, u8 turnOfMove, u16 movePower, s32 dmg, u8 friendship, u8 multihit);
void BtlController_EmitPrintString(u32 battler, u32 bufferId, u16 stringId);
void BtlController_EmitPrintSelectionString(u32 battler, u32 bufferId, u16 stringId);
void BtlController_EmitChooseAction(u32 battler, u32 bufferId, u8 action, u16 itemId);
void BtlController_EmitChooseMove(u32 battler, u32 bufferId, bool8 isDoubleBattle, bool8 NoPpNumber, struct ChooseMoveStruct *movePpData);
void BtlController_EmitChooseItem(u32 battler, u32 bufferId, u8 *arg1);
void BtlController_EmitChoosePokemon(u32 battler, u32 bufferId, u8 caseId, u8 arg2, u16 abilityId, u8 *arg4);
void BtlController_EmitHealthBarUpdate(u32 battler, u32 bufferId, u16 hpValue);
void BtlController_EmitExpUpdate(u32 battler, u32 bufferId, u8 partyId, s32 expPoints);
void BtlController_EmitStatusIconUpdate(u32 battler, u32 bufferId, u32 status);
void BtlController_EmitStatusAnimation(u32 battler, u32 bufferId, bool8 isVolatile, u32 status);
void BtlController_EmitDataTransfer(u32 battler, u32 bufferId, u16 size, void *data);
void BtlController_EmitTwoReturnValues(u32 battler, u32 bufferId, u8 ret8, u32 ret32);
void BtlController_EmitChosenMonReturnValue(u32 battler, u32 bufferId, u8 b, u8 *c);
void BtlController_EmitOneReturnValue(u32 battler, u32 bufferId, u16 arg1);
void BtlController_EmitOneReturnValue_Duplicate(u32 battler, u32 bufferId, u16 b);
void BtlController_EmitHitAnimation(u32 battler, u32 bufferId);
void BtlController_EmitCantSwitch(u32 battler, u32 bufferId);
void BtlController_EmitPlaySE(u32 battler, u32 bufferId, u16 songId);
void BtlController_EmitPlayFanfareOrBGM(u32 battler, u32 bufferId, u16 songId, bool8 playBGM);
void BtlController_EmitFaintingCry(u32 battler, u32 bufferId);
void BtlController_EmitIntroSlide(u32 battler, u32 bufferId, u8 terrainId);
void BtlController_EmitIntroTrainerBallThrow(u32 battler, u32 bufferId);
void BtlController_EmitDrawPartyStatusSummary(u32 battler, u32 bufferId, struct HpAndStatus *hpAndStatus, u8 param);
void BtlController_EmitHidePartyStatusSummary(u32 battler, u32 bufferId);
void BtlController_EmitEndBounceEffect(u32 battler, u32 bufferId);
void BtlController_EmitSpriteInvisibility(u32 battler, u32 bufferId, bool8 isInvisible);
void BtlController_EmitBattleAnimation(u32 battler, u32 bufferId, u8 animationId, u16 argument);
void BtlController_EmitLinkStandbyMsg(u32 battler, u32 bufferId, u8 mode);
void BtlController_EmitResetActionMoveSelection(u32 battler, u32 bufferId, u8 caseId);
void BtlController_EmitEndLinkBattle(u32 battler, u32 bufferId, u8 battleOutcome);

void BtlController_EmitDebugMenu(u32 battler, u32 bufferId);
void BtlController_EmitMoveInfo(u32 battler, u32 bufferId);

// player controller
void BattleControllerDummy(u32 battler);
void SetControllerToPlayer(u32 battler);
void PlayerHandleGetRawMonData(u32 battler);
void SpriteCB_FreePlayerSpriteLoadMonSprite(struct Sprite *sprite);
void SetCB2ToReshowScreenAfterMenu(void);
void SetCB2ToReshowScreenAfterMenu2(void);
void SetCB2ToReshowScreenAfterCatchPcAccess(void); //custom version made for pc access post catch
void Task_PlayerController_RestoreBgmAfterCry(u8 taskId);
void ActionSelectionCreateCursorAt(u8 cursorPos, u8 unused);
void ActionSelectionDestroyCursorAt(u8 cursorPos);
void InitMoveSelectionsVarsAndStrings(u32 battler);
void SetBattleEndCallbacks(u32 battler);
void MoveSelectionCreateCursorAt(u8 cursorPos, u8 baseTileNum);
void MoveSelectionDestroyCursorAt(u8 cursorPos);
void HandleInputChooseMove(u32 battler);

// opponent controller
void SetControllerToOpponent(u32 battler);
void OpponentBufferExecCompleted(u32 battler);

// safari controller
void SetControllerToSafari(u32 battler);

// pokedude controller
void SetControllerToPokedude(u32 battler);
void InitPokedudePartyAndOpponent(void);

// oak and old man controller
void SetControllerToOakOrOldMan(u32 battler);

// These flags are set to signal that the indicated message
// was already emitted

// Inflicting damage is key
#define FIRST_BATTLE_MSG_FLAG_INFLICT_DMG    0x1
// Lowering stats is advantageous
#define FIRST_BATTLE_MSG_FLAG_STAT_CHG       0x2
// Keep an eye on your HP
#define FIRST_BATTLE_MSG_FLAG_HP_RESTORE     0x4
// for opening party menu swtich
#define FIRST_BATTLE_MSG_FLAG_PARTY_MENU     0x8
//  move learn ui adjusts (for first time learn new move)
#define FIRST_LEARNED_MOVE_MSG_FLAG         0x10 //should this be 10?  
//^custom  for displaying can move to stat screen from level up move info

bool8 BtlCtrl_OakOldMan_TestState2Flag(u8 mask);
void BtlCtrl_OakOldMan_SetState2Flag(u8 mask);
void PrintOakText_InflictingDamageIsKey(u32 battler);
void PrintOakText_HowDisappointing(u32 battler);
void PrintOakText_OakNoRunningFromATrainer(u32 battler);
void OakOldManHandleInputChooseMove(u32 battler);
void BtlCtrl_DrawVoiceoverMessageFrame(void);
void BtlCtrl_RemoveVoiceoverMessageFrame(void);

// link opponent controller
void SetControllerToLinkOpponent(u32 battler);

// link partner controller
void SetControllerToLinkPartner(u32 battler);

#define tExpTask_monId      data[0]
#define tExpTask_battler    data[2]
#define tExpTask_gainedExp_1    data[3] //changed from s32 as task data is s16
#define tExpTask_gainedExp_2    data[4] // Stored as two half-words containing a word.
#define tExpTask_frames     data[10]

static inline s32 GetTaskExpValue(u8 taskId)
{
    return (u16)(gTasks[taskId].tExpTask_gainedExp_1) | (gTasks[taskId].tExpTask_gainedExp_2 << 16);
}

#endif // GUARD_BATTLE_CONTROLLERS_H
