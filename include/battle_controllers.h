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

enum BattleController
{
    BATTLE_CONTROLLER_NONE,
    BATTLE_CONTROLLER_PLAYER,
    BATTLE_CONTROLLER_PLAYER_PARTNER,
    BATTLE_CONTROLLER_OPPONENT,
    BATTLE_CONTROLLER_LINK_PARTNER,
    BATTLE_CONTROLLER_LINK_OPPONENT,
    BATTLE_CONTROLLER_SAFARI,
    BATTLE_CONTROLLER_WALLY,
    BATTLE_CONTROLLER_RECORDED_PLAYER,
    BATTLE_CONTROLLER_RECORDED_PARTNER,
    BATTLE_CONTROLLER_RECORDED_OPPONENT,
    BATTLE_CONTROLLER_OAK_OLD_MAN,
    BATTLE_CONTROLLERS_COUNT,
};

// Accessors for gBattleControllerExecFlags.
//
// These are provided for documentation purposes, to make the battle
// controller internals and the link communication internals more
// legible. Several of these have functions that you should call
// (e.g. MarkBattlerForControllerExec) instead of using these macros
// directly.

static inline void MarkBattleControllerActiveOnLocal(enum BattlerId battler)
{
    gBattleControllerExecFlags |= (1u << battler);
}

static inline void MarkBattleControllerIdleOnLocal(enum BattlerId battler)
{
    gBattleControllerExecFlags &= ~(1u << battler);
}

static inline bool32 IsBattleControllerActiveOnLocal(enum BattlerId battler)
{
    return gBattleControllerExecFlags & (1u << battler);
}

static inline void MarkBattleControllerMessageOutboundOverLink(enum BattlerId battler)
{
    gBattleControllerExecFlags |= ((1u << battler) << (32 - MAX_BATTLERS_COUNT));
}

static inline void MarkBattleControllerMessageSynchronizedOverLink(enum BattlerId battler)
{
    gBattleControllerExecFlags &= ~((1 << 28) << (battler));
}

static inline bool32 IsBattleControllerMessageSynchronizedOverLink(enum BattlerId battler)
{
    return gBattleControllerExecFlags & (1u << (battler + 28));
}

static inline void MarkBattleControllerActiveForPlayer(enum BattlerId battler, u32 playerId)
{
    gBattleControllerExecFlags |= ((1u << battler) << ((playerId) << 2));
}

static inline void MarkBattleControllerIdleForPlayer(enum BattlerId battler, u32 playerId)
{
    gBattleControllerExecFlags &= ~((1u << battler) << ((playerId) * 4));
}

static inline bool32 IsBattleControllerActiveForPlayer(enum BattlerId battler, u32 playerId)
{
    return gBattleControllerExecFlags & ((1u << battler) << ((playerId) * 4));
}

// This actually checks if a specific controller is active on any player or if
// *any* controller is pending sync over link communications, but the macro name
// can only be so specific before it just gets ridiculous.
static inline bool32 IsBattleControllerActiveOrPendingSyncAnywhere(enum BattlerId battler)
{
   return gBattleControllerExecFlags & (
                  (1u << battler)
                | (0xF << 28)
                | (1u << battler << 4)
                | (1u << battler << 8)
                | (1u << battler << 12));
}

// Special arguments for Battle Controller functions.

// Values given to the emit functions to choose gBattleResources->bufferA or gBattleResources->bufferB
enum {
   // For commands sent from the core battle engine to a controller.
   B_COMM_TO_CONTROLLER, // gBattleResources->bufferA

   // For replies sent from a controller to the core battle engine.
   B_COMM_TO_ENGINE, // gBattleResources->bufferB

   // During local play, a controller must directly mark itself as
   // inactive when it's done processing, whether or not it sends
   // a reply. During multiplayer, it must NOT directly mark itself
   // as inactive, but instead send one of these, with the player's
   // multiplayer ID as data.
   B_COMM_CONTROLLER_IS_DONE
};

enum {
    RESET_ACTION_MOVE_SELECTION,
    RESET_ACTION_SELECTION,
    RESET_MOVE_SELECTION,
};


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
//new funcs
extern void (*gBattlerControllerFuncs[MAX_BATTLERS_COUNT])(enum BattlerId battler);
extern void (*gBattlerControllerEndFuncs[MAX_BATTLERS_COUNT])(enum BattlerId battler);
extern u8 gBattleControllerData[MAX_BATTLERS_COUNT];
extern u8 gBattlerBattleController[MAX_BATTLERS_COUNT];

// general functions
//void HandleLinkBattleSetup(void);
void SetUpBattleVars(void);
void InitBtlControllers(void);
bool32 IsValidForBattle(struct Pokemon *mon);

u8 Rogue_GetBattleSpeedScale(void); //added for speed up PokAbbie
u8 GetBattleSpeedOption(void);

//void TryReceiveLinkBattleData(void);
//void PrepareBufferDataTransferLink(enum BattlerId battler, u32 bufferId, u16 size, u8 *data);
bool32 IsAiVsAiBattle(void);
// emitters
void BtlController_EmitGetMonData(enum BattlerId battler, u32 bufferId, u8 requestId, u8 monToCheck);
void BtlController_EmitSetMonData(enum BattlerId battler, u32 bufferId, u8 requestId, u8 monToCheck, u8 bytes, void *data);
void BtlController_EmitLoadMonSprite(enum BattlerId battler, u32 bufferId);
void BtlController_EmitSwitchInAnim(enum BattlerId battler, u32 bufferId, u8 partyId, bool8 dontClearTransform, bool8 dontClearSubstituteBit);
void BtlController_EmitReturnMonToBall(enum BattlerId battler, u32 bufferId, bool8 skipAnim);
void BtlController_EmitDrawTrainerPic(enum BattlerId battler, u32 bufferId);
void BtlController_EmitTrainerSlide(enum BattlerId battler, u32 bufferId);
void BtlController_EmitTrainerSlideBack(enum BattlerId battler, u32 bufferId);
void BtlController_EmitFaintAnimation(enum BattlerId battler, u32 bufferId);
void BtlController_EmitBallThrowAnim(enum BattlerId battler, u32 bufferId, u8 caseId);
void BtlController_EmitMoveAnimation(enum BattlerId battler, u32 bufferId, u16 move, u8 turnOfMove, u16 movePower, s32 dmg, u8 friendship, u8 multihit);
void BtlController_EmitPrintString(enum BattlerId battler, u32 bufferId, u16 stringId);
void BtlController_EmitPrintSelectionString(enum BattlerId battler, u32 bufferId, u16 stringId);
void BtlController_EmitChooseAction(enum BattlerId battler, u32 bufferId, u8 action, u16 itemId);
void BtlController_EmitChooseMove(enum BattlerId battler, u32 bufferId, bool8 isDoubleBattle, bool8 NoPpNumber, struct ChooseMoveStruct *movePpData);
void BtlController_EmitChooseItem(enum BattlerId battler, u32 bufferId, u8 *arg1);
void BtlController_EmitChoosePokemon(enum BattlerId battler, u32 bufferId, u8 caseId, u8 arg2, u16 abilityId, u8 *arg4);
void BtlController_EmitHealthBarUpdate(enum BattlerId battler, u32 bufferId, u16 hpValue);
void BtlController_EmitExpUpdate(enum BattlerId battler, u32 bufferId, u8 partyId, s32 expPoints);
void BtlController_EmitStatusIconUpdate(enum BattlerId battler, u32 bufferId, u32 status);
void BtlController_EmitStatusAnimation(enum BattlerId battler, u32 bufferId, bool8 isVolatile, u32 status);
void BtlController_EmitDataTransfer(enum BattlerId battler, u32 bufferId, u16 size, void *data);
void BtlController_EmitTwoReturnValues(enum BattlerId battler, u32 bufferId, u8 ret8, u32 ret32);
void BtlController_EmitChosenMonReturnValue(enum BattlerId battler, u32 bufferId, u8 b, u8 *c);
void BtlController_EmitOneReturnValue(enum BattlerId battler, u32 bufferId, u16 arg1);
void BtlController_EmitOneReturnValue_Duplicate(enum BattlerId battler, u32 bufferId, u16 b);
void BtlController_EmitHitAnimation(enum BattlerId battler, u32 bufferId);
void BtlController_EmitCantSwitch(enum BattlerId battler, u32 bufferId);
void BtlController_EmitPlaySE(enum BattlerId battler, u32 bufferId, u16 songId);
void BtlController_EmitPlayFanfareOrBGM(enum BattlerId battler, u32 bufferId, u16 songId, bool8 playBGM);
void BtlController_EmitFaintingCry(enum BattlerId battler, u32 bufferId);
void BtlController_EmitIntroSlide(enum BattlerId battler, u32 bufferId, u8 terrainId);
void BtlController_EmitIntroTrainerBallThrow(enum BattlerId battler, u32 bufferId);
void BtlController_EmitDrawPartyStatusSummary(enum BattlerId battler, u32 bufferId, struct HpAndStatus *hpAndStatus, u8 param);
void BtlController_EmitHidePartyStatusSummary(enum BattlerId battler, u32 bufferId);
void BtlController_EmitEndBounceEffect(enum BattlerId battler, u32 bufferId);
void BtlController_EmitSpriteInvisibility(enum BattlerId battler, u32 bufferId, bool8 isInvisible);
void BtlController_EmitBattleAnimation(enum BattlerId battler, u32 bufferId, u8 animationId, u16 argument);
void BtlController_EmitLinkStandbyMsg(enum BattlerId battler, u32 bufferId, u8 mode);
void BtlController_EmitResetActionMoveSelection(enum BattlerId battler, u32 bufferId, u8 caseId);
void BtlController_EmitEndLinkBattle(enum BattlerId battler, u32 bufferId, u8 battleOutcome);

void BtlController_EmitDebugMenu(enum BattlerId battler, u32 bufferId);
void BtlController_EmitMoveInfo(enum BattlerId battler, u32 bufferId);

// player controller
void BattleControllerDummy(enum BattlerId battler);
void SetControllerToPlayer(enum BattlerId battler);
void PlayerHandleGetRawMonData(enum BattlerId battler);
void SpriteCB_FreePlayerSpriteLoadMonSprite(struct Sprite *sprite);
void SetCB2ToReshowScreenAfterMenu(void);
void SetCB2ToReshowScreenAfterMenu2(void);
void SetCB2ToReshowScreenAfterCatchPcAccess(void); //custom version made for pc access post catch
void Task_PlayerController_RestoreBgmAfterCry(u8 taskId);
void ActionSelectionCreateCursorAt(u8 cursorPos, u8 unused);
void ActionSelectionDestroyCursorAt(u8 cursorPos);
void InitMoveSelectionsVarsAndStrings(enum BattlerId battler);
void SetBattleEndCallbacks(enum BattlerId battler);
void MoveSelectionCreateCursorAt(u8 cursorPos, u8 baseTileNum);
void MoveSelectionDestroyCursorAt(u8 cursorPos);
void HandleInputChooseMove(enum BattlerId battler);
bool32 BattlerHasAi(enum BattlerId battlerId);

// opponent controller
void SetControllerToOpponent(enum BattlerId battler);
void OpponentBufferExecCompleted(enum BattlerId battler);

// safari controller
void SetControllerToSafari(enum BattlerId battler);

// pokedude controller
void SetControllerToPokedude(enum BattlerId battler);
void InitPokedudePartyAndOpponent(void);

// oak and old man controller
void SetControllerToOakOrOldMan(enum BattlerId battler);

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
void PrintOakText_InflictingDamageIsKey(enum BattlerId battler);
void PrintOakText_HowDisappointing(enum BattlerId battler);
void PrintOakText_OakNoRunningFromATrainer(enum BattlerId battler);
void OakOldManHandleInputChooseMove(enum BattlerId battler);
void BtlCtrl_DrawVoiceoverMessageFrame(void);
void BtlCtrl_RemoveVoiceoverMessageFrame(void);

// link opponent controller
void SetControllerToLinkOpponent(enum BattlerId battler);

// link partner controller
void SetControllerToLinkPartner(enum BattlerId battler);

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
