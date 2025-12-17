#include "global.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_ai_main.h"
#include "battle_anim.h"
#include "battle_util.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "link.h"
#include "link_rfu.h"
#include "cable_club.h"
#include "party_menu.h"
#include "task.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle.h"
//#include "constants/battle_move_effects.h"

//static EWRAM_DATA u8 sLinkSendTaskId = 0;
//static EWRAM_DATA u8 sLinkReceiveTaskId = 0;
//static EWRAM_DATA u8 gUnknown_202286E = 0;
EWRAM_DATA struct BattleBoxMessageDisplay gUnusedControllerStruct = {0};
//static EWRAM_DATA u8 sBattleBuffersTransferData[0x100] = {0}; //replaced by EE battle resource struct

//static void CreateTasksForSendRecvLinkBuffers(void);
static void InitLinkBtlControllers(void);
static void InitSinglePlayerBtlControllers(void);
static void SetBattlePartyIds(void);
//static void Task_HandleSendLinkBuffersData(u8 taskId);
//static void Task_HandleCopyReceivedLinkBuffersData(u8 taskId);

void HandleLinkBattleSetup(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        return;
        if (gWirelessCommType)
            SetWirelessCommType1();
        if (!gReceivedRemoteLinkPlayers)
            OpenLink();
        CreateTask(Task_WaitForReceivedRemoteLinkPlayers5SecondTimeout, 0);
       // CreateTasksForSendRecvLinkBuffers();
    }
}

void SetUpBattleVars(void)
{
    s32 i;

    gBattleMainFunc = BattleDummy;
    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
    {
        gBattlerControllerFuncs[i] = BattleControllerDummy;
        gBattlerPositions[i] = 0xFF;
        gActionSelectionCursor[i] = 0;
        gMoveSelectionCursor[i] = 0;
    }
    HandleLinkBattleSetup();
    gBattleControllerExecFlags = 0;
    ClearBattleAnimationVars();
    ClearBattleMonForms();
    //BattleAI_SetupItems();//NEED TO SEtu;p to use these two, instead of bottom one
    //BattleAI_SetupFlags();//currently ai process/infrastrucutre not ready to use these order of things is wrong
    BattleAI_HandleItemUseBeforeAISetup();//remove this when get process correct
}

bool32 IsValidForBattle(struct Pokemon *mon)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
    return (species != SPECIES_NONE
         && species != SPECIES_EGG
         && GetMonData(mon, MON_DATA_HP) != 0
         && GetMonData(mon, MON_DATA_IS_EGG) == FALSE);
}

void InitBtlControllers(void)
{
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        InitLinkBtlControllers();
    else
        InitSinglePlayerBtlControllers();
    SetBattlePartyIds();
    if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
        for (i = 0; i < gBattlersCount; ++i)
            BufferBattlePartyCurrentOrderBySide(i, 0);
}

static void InitSinglePlayerBtlControllers(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        gBattleMainFunc = BeginBattleIntro;
        if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
        {
            gBattlerControllerFuncs[0] = SetControllerToPokedude;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[1] = SetControllerToPokedude;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            gBattlersCount = 2;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
                gBattlerControllerFuncs[0] = SetControllerToSafari;
            else if (gBattleTypeFlags & (BATTLE_TYPE_OLD_MAN_TUTORIAL | BATTLE_TYPE_FIRST_BATTLE))
                gBattlerControllerFuncs[0] = SetControllerToOakOrOldMan;
            else
                gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[1] = SetControllerToOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            gBattlersCount = 2;
        }
    }
    else //doubles
    {
        gBattleMainFunc = BeginBattleIntro;
        if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
        {
            gBattlerControllerFuncs[0] = SetControllerToPokedude;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[1] = SetControllerToPokedude;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            gBattlerControllerFuncs[2] = SetControllerToPokedude;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;
            gBattlerControllerFuncs[3] = SetControllerToPokedude;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
            gBattlersCount = MAX_BATTLERS_COUNT;
        }
        else
        {
            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[1] = SetControllerToOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            gBattlerControllerFuncs[2] = SetControllerToPlayer;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;
            gBattlerControllerFuncs[3] = SetControllerToOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
            gBattlersCount = MAX_BATTLERS_COUNT;
        }
    }
}

static void InitLinkBtlControllers(void)
{
    s32 i;
    u8 multiplayerId;

    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
        {
            gBattleMainFunc = BeginBattleIntro;
            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[1] = SetControllerToLinkOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            gBattlersCount = 2;
        }
        else
        {
            gBattlerControllerFuncs[1] = SetControllerToPlayer;
            gBattlerPositions[1] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[0] = SetControllerToLinkOpponent;
            gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;
            gBattlersCount = 2;
        }
    }
    else if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && (gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
        {
            gBattleMainFunc = BeginBattleIntro;
            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[1] = SetControllerToLinkOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            gBattlerControllerFuncs[2] = SetControllerToPlayer;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;
            gBattlerControllerFuncs[3] = SetControllerToLinkOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
            gBattlersCount = MAX_BATTLERS_COUNT;
        }
        else
        {
            gBattlerControllerFuncs[1] = SetControllerToPlayer;
            gBattlerPositions[1] = B_POSITION_PLAYER_LEFT;
            gBattlerControllerFuncs[0] = SetControllerToLinkOpponent;
            gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;
            gBattlerControllerFuncs[3] = SetControllerToPlayer;
            gBattlerPositions[3] = B_POSITION_PLAYER_RIGHT;
            gBattlerControllerFuncs[2] = SetControllerToLinkOpponent;
            gBattlerPositions[2] = B_POSITION_OPPONENT_RIGHT;
            gBattlersCount = MAX_BATTLERS_COUNT;
        }
    }
    else
    {
        multiplayerId = GetMultiplayerId();
        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
            gBattleMainFunc = BeginBattleIntro;
        for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        {
            switch (gLinkPlayers[i].id)
            {
            case 0:
            case 3:
                BufferBattlePartyCurrentOrderBySide(gLinkPlayers[i].id, 0);
                break;
            case 1:
            case 2:
                BufferBattlePartyCurrentOrderBySide(gLinkPlayers[i].id, 1);
                break;
            }
            if (i == multiplayerId)
            {
                gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToPlayer;
                switch (gLinkPlayers[i].id)
                {
                case 0:
                case 3:
                    gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                    gBattlerPartyIndexes[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                    break;
                case 1:
                case 2:
                    gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_RIGHT;
                    gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                    break;
                }
            }
            else
            {
                if ((!(gLinkPlayers[i].id & 1) && !(gLinkPlayers[multiplayerId].id & 1)) || ((gLinkPlayers[i].id & 1) && (gLinkPlayers[multiplayerId].id & 1)))
                {
                    gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToLinkPartner;
                    switch (gLinkPlayers[i].id)
                    {
                    case 0:
                    case 3:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                        break;
                    case 1:
                    case 2:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_RIGHT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = B_POSITION_OPPONENT_RIGHT;
                        break;
                    }
                }
                else
                {
                    gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToLinkOpponent;
                    switch (gLinkPlayers[i].id)
                    {
                    case 0:
                    case 3:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_OPPONENT_LEFT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                        break;
                    case 1:
                    case 2:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_OPPONENT_RIGHT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = B_POSITION_OPPONENT_RIGHT;
                        break;
                    }
                }
            }
        }
        gBattlersCount = MAX_BATTLERS_COUNT;
    }
}

static void SetBattlePartyIds(void)
{
    s32 i, j;

    if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
    {
        for (i = 0; i < gBattlersCount; ++i)
        {
            for (j = 0; j < PARTY_SIZE; ++j)
            {
                if (i < 2)
                {
                    if (GET_BATTLER_SIDE2(i) == B_SIDE_PLAYER)
                    {
                        if (GetMonData(&gPlayerParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gPlayerParty[j], MON_DATA_IS_EGG))
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                    else
                    {
                        if (GetMonData(&gEnemyParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gEnemyParty[j], MON_DATA_IS_EGG))
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                }
                else
                {
                    if (GET_BATTLER_SIDE2(i) == B_SIDE_PLAYER)
                    {
                        if (GetMonData(&gPlayerParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES) != SPECIES_NONE  // Probably a typo by Game Freak. The rest use SPECIES2.
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gPlayerParty[j], MON_DATA_IS_EGG)
                         && gBattlerPartyIndexes[i - 2] != j)
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                    else
                    {
                        if (GetMonData(&gEnemyParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gEnemyParty[j], MON_DATA_IS_EGG)
                         && gBattlerPartyIndexes[i - 2] != j)
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                }
            }
        }
    }
}

static void PrepareBufferDataTransfer(u32 battler, u32 bufferId, u8 *data, u16 size)
{
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        //PrepareBufferDataTransferLink(battler, bufferId, size, data);
    }
    else
    {
        switch (bufferId)
        {
        case BUFFER_A:
            for (i = 0; i < size; data++, i++)
                gBattleResources->bufferA[battler][i] = *data;
            break;
        case BUFFER_B:
            for (i = 0; i < size; data++, i++)
                gBattleResources->bufferB[battler][i] = *data;
            break;
        }
    }
}

bool8 InBattleChoosingMoves(); //seems this is running the function in the file rather thana full include?
bool8 InBattleRunningActions();

u8 GetBattleSpeedOption(void) //return battle speed
{
    return gSaveBlock2Ptr->optionsBattleSpeed;
}

u8 Rogue_GetBattleSpeedScale(void) //since not taking healthbar setup make void
{
    u8 battleSpeedOption = GetBattleSpeedOption(); //retrun speed up option
    u8 hasBattleInputStarted = FALSE;

    // Hold L to slow down
    if(JOY_HELD(L_BUTTON)) //won't work for main screen as uses L for move info, but fine overall
        return 1;

    // We want to speed up all anims until input selection starts
    if(InBattleChoosingMoves())
        hasBattleInputStarted = TRUE;  //pokabbie used ewram for this nto sure why

    if(hasBattleInputStarted)
    {
        // Always run at 1x speed here // -believe should work for movingthrough bag as well
        if(InBattleChoosingMoves())
            return 1;//think will change to 2 //I see problem it treats every button press as 2...

        //ok checked and with my string change and text buff/pause changes I don't need it
        //even at 8x text is still legible its hard to tell if things are even faster but
        //that's fine lol
        // When battle anims are turned off, it's a bit too hard to read text, so force running at normal speed
        //turned off for now to test my own text options to see if can work for that
        //if (gSaveBlock2Ptr->optionsTurnBattleSceneOff == TRUE && InBattleRunningActions())
        //    return 2;

        //if(!forHealthbar && battleSceneOption == OPTIONS_BATTLE_SCENE_DISABLED && InBattleRunningActions())
        //    return 1;
    }

    // We don't need to speed up health bar anymore as that passively happens now
    switch (battleSpeedOption)
    {
    case OPTIONS_BATTLE_SPEED_1X:
        return 1;

    case OPTIONS_BATTLE_SPEED_2X:
        return 2;

    case OPTIONS_BATTLE_SPEED_3X:
        return 3;

    case OPTIONS_BATTLE_SPEED_4X:
        return 4;

    case OPTIONS_BATTLE_SPEED_5X:
        return 5;

    case OPTIONS_BATTLE_SPEED_6X:
        return 6;

    case OPTIONS_BATTLE_SPEED_7X:
        return 7;

    case OPTIONS_BATTLE_SPEED_8X:
        return 8;

    // Print text at a readable speed still
    /*case OPTIONS_BATTLE_SCENE_DISABLED:
        if(gRogueLocal.hasBattleInputStarted)
            return forHealthbar ? 10 : 1;
        else
            return 4;*/ //don't get this part
    }

    return 1; //battle speed goes through here, believe returns 1 so will always be base speed even if speed up is off
} //relatively sure this is just a safety value, since you never want this function to return 0

/*
static void CreateTasksForSendRecvLinkBuffers(void)
{
    sLinkSendTaskId = CreateTask(Task_HandleSendLinkBuffersData, 0);
    gTasks[sLinkSendTaskId].data[11] = 0;
    gTasks[sLinkSendTaskId].data[12] = 0;
    gTasks[sLinkSendTaskId].data[13] = 0;
    gTasks[sLinkSendTaskId].data[14] = 0;
    gTasks[sLinkSendTaskId].data[15] = 0;
    sLinkReceiveTaskId = CreateTask(Task_HandleCopyReceivedLinkBuffersData, 0);
    gTasks[sLinkReceiveTaskId].data[12] = 0;
    gTasks[sLinkReceiveTaskId].data[13] = 0;
    gTasks[sLinkReceiveTaskId].data[14] = 0;
    gTasks[sLinkReceiveTaskId].data[15] = 0;
    gUnknown_202286E = 0;
}

enum
{
    LINK_BUFF_BUFFER_ID,
    LINK_BUFF_ACTIVE_BATTLER,
    LINK_BUFF_ATTACKER,
    LINK_BUFF_TARGET,
    LINK_BUFF_SIZE_LO,
    LINK_BUFF_SIZE_HI,
    LINK_BUFF_ABSENT_BATTLER_FLAGS,
    LINK_BUFF_EFFECT_BATTLER,
    LINK_BUFF_DATA
};

void PrepareBufferDataTransferLink(u32 battler, u32 bufferId, u16 size, u8 *data)
{
    s32 alignedSize, i;

    alignedSize = size - size % 4 + 4;
    if (gTasks[sLinkSendTaskId].data[14] + alignedSize + LINK_BUFF_DATA + 1 > BATTLE_BUFFER_LINK_SIZE)
    {
        gTasks[sLinkSendTaskId].data[12] = gTasks[sLinkSendTaskId].data[14];
        gTasks[sLinkSendTaskId].data[14] = 0;
    }
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_BUFFER_ID] = bufferId;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_ACTIVE_BATTLER] = battler;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_ATTACKER] = gBattlerAttacker;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_TARGET] = gBattlerTarget;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_SIZE_LO] = alignedSize;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_SIZE_HI] = (alignedSize & 0x0000FF00) >> 8;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_ABSENT_BATTLER_FLAGS] = gAbsentBattlerFlags;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_EFFECT_BATTLER] = gEffectBattler;
    for (i = 0; i < size; ++i)
        gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_DATA + i] = data[i];
    gTasks[sLinkSendTaskId].data[14] = gTasks[sLinkSendTaskId].data[14] + alignedSize + LINK_BUFF_DATA;
}

static void Task_HandleSendLinkBuffersData(u8 taskId)
{
    u16 blockSize;
    s32 playerCount;

    switch (gTasks[taskId].data[11])
    {
    case 0:
        gTasks[taskId].data[10] = 100;
        ++gTasks[taskId].data[11];
        break;
    case 1:
        if (!--gTasks[taskId].data[10])
        {
            ++gTasks[taskId].data[11];
            if (gReceivedRemoteLinkPlayers)
                gTasks[taskId].data[11] = 3;
        }
        break;
    case 2:
        playerCount = GetLinkPlayerCount_2();
        if ((gBattleTypeFlags & BATTLE_TYPE_MULTI && playerCount > 3) || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && playerCount > 1))
        {
            if (IsLinkMaster())
            {
                CheckShouldAdvanceLinkState();
                ++gTasks[taskId].data[11];
            }
            else
            {
                ++gTasks[taskId].data[11];
            }
        }
        break;
    case 3:
        if (gTasks[taskId].data[15] != gTasks[taskId].data[14])
        {
            if (!gTasks[taskId].data[13])
            {
                if (gTasks[taskId].data[15] > gTasks[taskId].data[14]
                 && gTasks[taskId].data[15] == gTasks[taskId].data[12])
                {
                    gTasks[taskId].data[12] = 0;
                    gTasks[taskId].data[15] = 0;
                }
                blockSize = (gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_LO] | (gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_HI] << 8)) + LINK_BUFF_DATA;
                SendBlock(bitmask_all_link_players_but_self(), &gLinkBattleSendBuffer[gTasks[taskId].data[15]], blockSize);
                ++gTasks[taskId].data[11];
            }
            else
            {
                --gTasks[taskId].data[13];
                break;
            }
        }
        break;
    case 4:
        if (IsLinkTaskFinished())
        {
            blockSize = gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_LO] | (gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_HI] << 8);
            gTasks[taskId].data[13] = 5;
            gTasks[taskId].data[15] = gTasks[taskId].data[15] + blockSize + LINK_BUFF_DATA;
            gTasks[taskId].data[11] = 3;
        }
        break;
    case 5:
        if (!--gTasks[taskId].data[13])
        {
            gTasks[taskId].data[13] = 5;
            gTasks[taskId].data[11] = 3;
        }
        break;
    }
}

void TryReceiveLinkBattleData(void)
{
    u8 i;
    s32 j;
    u8 *recvBuffer;

    if (gReceivedRemoteLinkPlayers && (gBattleTypeFlags & BATTLE_TYPE_20) && (gLinkPlayers[0].linkType == 0x2211))
    {
        LinkRfu_DestroyIdleTask();
        for (i = 0; i < GetLinkPlayerCount(); ++i)
        {
            if (GetBlockReceivedStatus() & (1u << i))
            {
                ResetBlockReceivedFlag(i);
                recvBuffer = (u8 *)gBlockRecvBuffer[i];
                {
                    u8 *dest, *src;
                    u16 r6 = gBlockRecvBuffer[i][2];

                    if (gTasks[sLinkReceiveTaskId].data[14] + 9 + r6 > 0x1000)
                    {
                        gTasks[sLinkReceiveTaskId].data[12] = gTasks[sLinkReceiveTaskId].data[14];
                        gTasks[sLinkReceiveTaskId].data[14] = 0;
                    }
                    dest = &gLinkBattleRecvBuffer[gTasks[sLinkReceiveTaskId].data[14]];
                    src = recvBuffer;
                    for (j = 0; j < r6 + 8; ++j)
                        dest[j] = src[j];
                    gTasks[sLinkReceiveTaskId].data[14] = gTasks[sLinkReceiveTaskId].data[14] + r6 + 8;
                }
            }
        }
    }
}

static void Task_HandleCopyReceivedLinkBuffersData(u8 taskId)
{
    u16 blockSize;
    u8 battlerId;
    u8 var;

    if (gTasks[taskId].data[15] != gTasks[taskId].data[14])
    {
        if (gTasks[taskId].data[15] > gTasks[taskId].data[14]
         && gTasks[taskId].data[15] == gTasks[taskId].data[12])
        {
            gTasks[taskId].data[12] = 0;
            gTasks[taskId].data[15] = 0;
        }
        battlerId = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_ACTIVE_BATTLER];
        blockSize = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_LO] | (gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_HI] << 8);
        switch (gLinkBattleRecvBuffer[gTasks[taskId].data[15] + 0])
        {
        case 0:
            if (gBattleControllerExecFlags & (1u << battlerId))
                return;
            memcpy(gBattleResources->bufferA[battlerId], &gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_DATA], blockSize);
            MarkBattlerReceivedLinkData(battlerId);
            if (!(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER))
            {
                gBattlerAttacker = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_ATTACKER];
                gBattlerTarget = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_TARGET];
                gAbsentBattlerFlags = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_ABSENT_BATTLER_FLAGS];
                gEffectBattler = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_EFFECT_BATTLER];
            }
            break;
        case 1:
            memcpy(gBattleResources->bufferB[battlerId], &gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_DATA], blockSize);
            break;
        case 2:
            var = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_DATA];
            gBattleControllerExecFlags &= ~((1u << battlerId) << (var * 4));
            break;
        }
        gTasks[taskId].data[15] = gTasks[taskId].data[15] + blockSize + LINK_BUFF_DATA;
    }
}
*/
void BtlController_EmitGetMonData(u32 battler, u32 bufferId, u8 requestId, u8 monToCheck)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_GETMONDATA;
    gBattleResources->transferBuffer[1] = requestId;
    gBattleResources->transferBuffer[2] = monToCheck;
    gBattleResources->transferBuffer[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitSetMonData(u32 battler, u32 bufferId, u8 requestId, u8 monToCheck, u8 bytes, void *data)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_SETMONDATA;
    gBattleResources->transferBuffer[1] = requestId;
    gBattleResources->transferBuffer[2] = monToCheck;
    for (i = 0; i < bytes; ++i)
        gBattleResources->transferBuffer[3 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 3 + bytes);
}

void BtlController_EmitLoadMonSprite(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_LOADMONSPRITE;
    gBattleResources->transferBuffer[1] = CONTROLLER_LOADMONSPRITE;
    gBattleResources->transferBuffer[2] = CONTROLLER_LOADMONSPRITE;
    gBattleResources->transferBuffer[3] = CONTROLLER_LOADMONSPRITE;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitSwitchInAnim(u32 battler, u32 bufferId, u8 partyId, bool8 dontClearTransform, bool8 dontClearSubstituteBit)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_SWITCHINANIM;
    gBattleResources->transferBuffer[1] = partyId;
    gBattleResources->transferBuffer[2] = dontClearTransform;
    gBattleResources->transferBuffer[3] = dontClearSubstituteBit;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitReturnMonToBall(u32 battler, u32 bufferId, bool8 skipAnim)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_RETURNMONTOBALL;
    gBattleResources->transferBuffer[1] = skipAnim;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

void BtlController_EmitDrawTrainerPic(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_DRAWTRAINERPIC;
    gBattleResources->transferBuffer[1] = CONTROLLER_DRAWTRAINERPIC;
    gBattleResources->transferBuffer[2] = CONTROLLER_DRAWTRAINERPIC;
    gBattleResources->transferBuffer[3] = CONTROLLER_DRAWTRAINERPIC;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitTrainerSlide(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_TRAINERSLIDE;
    gBattleResources->transferBuffer[1] = CONTROLLER_TRAINERSLIDE;
    gBattleResources->transferBuffer[2] = CONTROLLER_TRAINERSLIDE;
    gBattleResources->transferBuffer[3] = CONTROLLER_TRAINERSLIDE;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitTrainerSlideBack(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_TRAINERSLIDEBACK;
    gBattleResources->transferBuffer[1] = CONTROLLER_TRAINERSLIDEBACK;
    gBattleResources->transferBuffer[2] = CONTROLLER_TRAINERSLIDEBACK;
    gBattleResources->transferBuffer[3] = CONTROLLER_TRAINERSLIDEBACK;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitFaintAnimation(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_FAINTANIMATION;
    gBattleResources->transferBuffer[1] = CONTROLLER_FAINTANIMATION;
    gBattleResources->transferBuffer[2] = CONTROLLER_FAINTANIMATION;
    gBattleResources->transferBuffer[3] = CONTROLLER_FAINTANIMATION;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

// Unused
static void BtlController_EmitPaletteFade(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_PALETTEFADE;
    gBattleResources->transferBuffer[1] = CONTROLLER_PALETTEFADE;
    gBattleResources->transferBuffer[2] = CONTROLLER_PALETTEFADE;
    gBattleResources->transferBuffer[3] = CONTROLLER_PALETTEFADE;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

// Unused
static void BtlController_EmitSuccessBallThrowAnim(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_SUCCESSBALLTHROWANIM;
    gBattleResources->transferBuffer[1] = CONTROLLER_SUCCESSBALLTHROWANIM;
    gBattleResources->transferBuffer[2] = CONTROLLER_SUCCESSBALLTHROWANIM;
    gBattleResources->transferBuffer[3] = CONTROLLER_SUCCESSBALLTHROWANIM;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitBallThrowAnim(u32 battler, u32 bufferId, u8 caseId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_BALLTHROWANIM;
    gBattleResources->transferBuffer[1] = caseId;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

// Unused
static void BtlController_EmitPause(u32 battler, u32 bufferId, u8 toWait, void *data)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_PAUSE;
    gBattleResources->transferBuffer[1] = toWait;
    for (i = 0; i < toWait * 3; ++i)
        gBattleResources->transferBuffer[2 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, toWait * 3 + 2);
}

void BtlController_EmitMoveAnimation(u32 battler, u32 bufferId, u16 move, u8 turnOfMove, u16 movePower, s32 dmg, u8 friendship, struct DisableStruct *disableStructPtr, u8 multihit)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_MOVEANIMATION;
    gBattleResources->transferBuffer[1] = move;
    gBattleResources->transferBuffer[2] = (move & 0xFF00) >> 8;
    gBattleResources->transferBuffer[3] = turnOfMove;
    gBattleResources->transferBuffer[4] = movePower;
    gBattleResources->transferBuffer[5] = (movePower & 0xFF00) >> 8;
    gBattleResources->transferBuffer[6] = dmg;
    gBattleResources->transferBuffer[7] = (dmg & 0x0000FF00) >> 8;
    gBattleResources->transferBuffer[8] = (dmg & 0x00FF0000) >> 16;
    gBattleResources->transferBuffer[9] = (dmg & 0xFF000000) >> 24;
    gBattleResources->transferBuffer[10] = friendship;
    gBattleResources->transferBuffer[11] = gMultiHitCounter; // multihit in pokeem
    if (WeatherHasEffect())
    {
        gBattleResources->transferBuffer[12] = gBattleWeather;
        gBattleResources->transferBuffer[13] = (gBattleWeather & 0xFF00) >> 8;
    }
    else
    {
        gBattleResources->transferBuffer[12] = 0;
        gBattleResources->transferBuffer[13] = 0;
    }
    gBattleResources->transferBuffer[14] = 0;
    gBattleResources->transferBuffer[15] = 0;
    memcpy(&gBattleResources->transferBuffer[16], disableStructPtr, sizeof(struct DisableStruct));
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 16 + sizeof(struct DisableStruct));
}

void BtlController_EmitPrintString(u32 battler, u32 bufferId, u16 stringID)
{
    s32 i;
    struct BattleMsgData *stringInfo;

    gBattleResources->transferBuffer[0] = CONTROLLER_PRINTSTRING;
    gBattleResources->transferBuffer[1] = gBattleOutcome;
    gBattleResources->transferBuffer[2] = stringID;
    gBattleResources->transferBuffer[3] = (stringID & 0xFF00) >> 8;
    stringInfo = (struct BattleMsgData *)(&gBattleResources->transferBuffer[4]);
    stringInfo->currentMove = gCurrentMove;
    stringInfo->originallyUsedMove = gChosenMove;
    stringInfo->lastItem = gLastUsedItem;
    stringInfo->lastAbility = gLastUsedAbility;
    stringInfo->scrActive = gBattleScripting.battler;
    stringInfo->bakScriptPartyIdx = gBattleStruct->scriptPartyIdx;
    stringInfo->hpScale = gBattleStruct->hpScale;
    stringInfo->itemEffectBattler = gPotentialItemEffectBattler;
    stringInfo->moveType = gBattleMoves[gCurrentMove].type;
    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        stringInfo->abilities[i] = gBattleMons[i].ability;
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; ++i)
    {
        stringInfo->textBuffs[0][i] = gBattleTextBuff1[i];
        stringInfo->textBuffs[1][i] = gBattleTextBuff2[i];
        stringInfo->textBuffs[2][i] = gBattleTextBuff3[i];
    }
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, sizeof(struct BattleMsgData) + 4);
}

void BtlController_EmitPrintSelectionString(u32 battler, u32 bufferId, u16 stringID)
{
    s32 i;
    struct BattleMsgData *stringInfo;

    gBattleResources->transferBuffer[0] = CONTROLLER_PRINTSTRINGPLAYERONLY;
    gBattleResources->transferBuffer[1] = CONTROLLER_PRINTSTRINGPLAYERONLY;
    gBattleResources->transferBuffer[2] = stringID;
    gBattleResources->transferBuffer[3] = (stringID & 0xFF00) >> 8;
    stringInfo = (struct BattleMsgData *)(&gBattleResources->transferBuffer[4]);
    stringInfo->currentMove = gCurrentMove;
    stringInfo->originallyUsedMove = gChosenMove;
    stringInfo->lastItem = gLastUsedItem;
    stringInfo->lastAbility = gLastUsedAbility;
    stringInfo->scrActive = gBattleScripting.battler;
    stringInfo->bakScriptPartyIdx = gBattleStruct->scriptPartyIdx;
    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        stringInfo->abilities[i] = gBattleMons[i].ability;
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; ++i)
    {
        stringInfo->textBuffs[0][i] = gBattleTextBuff1[i];
        stringInfo->textBuffs[1][i] = gBattleTextBuff2[i];
        stringInfo->textBuffs[2][i] = gBattleTextBuff3[i];
    }
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, sizeof(struct BattleMsgData) + 4);
}

// itemId only relevant for B_ACTION_USE_ITEM
void BtlController_EmitChooseAction(u32 battler, u32 bufferId, u8 action, u16 itemId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_CHOOSEACTION;
    gBattleResources->transferBuffer[1] = action;
    gBattleResources->transferBuffer[2] = itemId;
    gBattleResources->transferBuffer[3] = (itemId & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

// Unused
static void BtlController_EmitUnknownYesNoBox(u32 battler, u32 bufferId, u32 arg1) // TODO: Does the function name make sense for pokefirered?
{
    gBattleResources->transferBuffer[0] = CONTROLLER_UNKNOWNYESNOBOX;
    gBattleResources->transferBuffer[1] = arg1;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

void BtlController_EmitChooseMove(u32 battler, u32 bufferId, bool8 isDoubleBattle, bool8 NoPpNumber, struct ChooseMoveStruct *movePpData)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_CHOOSEMOVE;
    gBattleResources->transferBuffer[1] = isDoubleBattle;
    gBattleResources->transferBuffer[2] = NoPpNumber;
    gBattleResources->transferBuffer[3] = 0;
    for (i = 0; i < sizeof(*movePpData); ++i)
        gBattleResources->transferBuffer[4 + i] = *((u8 *)(movePpData) + i);
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, sizeof(*movePpData) + 4);
}

void BtlController_EmitChooseItem(u32 battler, u32 bufferId, u8 *battlePartyOrder)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_OPENBAG;
    for (i = 0; i < PARTY_SIZE / 2; i++)
        gBattleResources->transferBuffer[1 + i] = battlePartyOrder[i];
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitChoosePokemon(u32 battler, u32 bufferId, u8 caseId, u8 slotId, u16 abilityId, u8 *data)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_CHOOSEPOKEMON;
    gBattleResources->transferBuffer[1] = caseId;
    gBattleResources->transferBuffer[2] = slotId;
    gBattleResources->transferBuffer[3] = LOBYTE(abilityId);
    gBattleResources->transferBuffer[7] = HIBYTE(abilityId);
    for (i = 0; i < 3; i++)
        gBattleResources->transferBuffer[4 + i] = data[i];
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 8); // Only 7 bytes were written. //can't remember what about
}

void BtlController_EmitHealthBarUpdate(u32 battler, u32 bufferId, u16 hpValue)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_HEALTHBARUPDATE;
    gBattleResources->transferBuffer[1] = 0;
    gBattleResources->transferBuffer[2] = (s16)hpValue;
    gBattleResources->transferBuffer[3] = ((s16)hpValue & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitExpUpdate(u32 battler, u32 bufferId, u8 partyId, s32 expPoints)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_EXPUPDATE;
    gBattleResources->transferBuffer[1] = partyId;
    gBattleResources->transferBuffer[2] = expPoints;
    gBattleResources->transferBuffer[3] = (expPoints & 0x0000FF00) >> 8;
    gBattleResources->transferBuffer[4] = (expPoints & 0x00FF0000) >> 16;
    gBattleResources->transferBuffer[5] = (expPoints & 0xFF000000) >> 24;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 6);
}

void BtlController_EmitStatusIconUpdate(u32 battler, u32 bufferId, u32 status)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_STATUSICONUPDATE;
    gBattleResources->transferBuffer[1] = status;
    gBattleResources->transferBuffer[2] = (status & 0x0000FF00) >> 8;
    gBattleResources->transferBuffer[3] = (status & 0x00FF0000) >> 16;
    gBattleResources->transferBuffer[4] = (status & 0xFF000000) >> 24;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 5);
}


//seems to be same as InitAndLaunchChosenStatusAnimation function, just used from different places?
//actually this seems to be setting the values for that, then the values
//are read from that battlecontroller and actually sets the status
//statusType is value to represent fi status1 status2 or status3 etc.
//1 for status1, 2 for status2 etc.
void BtlController_EmitStatusAnimation(u32 battler, u32 bufferId, bool8 isVolatile, u32 status)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_STATUSANIMATION;
    gBattleResources->transferBuffer[1] = isVolatile; 
    gBattleResources->transferBuffer[2] = status;
    gBattleResources->transferBuffer[3] = (status & 0x0000FF00) >> 8;
    gBattleResources->transferBuffer[4] = (status & 0x00FF0000) >> 16;
    gBattleResources->transferBuffer[5] = (status & 0xFF000000) >> 24;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 6);
}

void BtlController_EmitDataTransfer(u32 battler, u32 bufferId, u16 size, void *data)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_DATATRANSFER;
    gBattleResources->transferBuffer[1] = CONTROLLER_DATATRANSFER;
    gBattleResources->transferBuffer[2] = size;
    gBattleResources->transferBuffer[3] = (size & 0xFF00) >> 8;
    for (i = 0; i < size; ++i)
        gBattleResources->transferBuffer[4 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, size + 4);
}

void BtlController_EmitTwoReturnValues(u32 battler, u32 bufferId, u8 ret8, u32 ret32)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_TWORETURNVALUES;
    gBattleResources->transferBuffer[1] = ret8;
    gBattleResources->transferBuffer[2] = ret32;
    gBattleResources->transferBuffer[3] = (ret32 & 0x0000FF00) >> 8;
    gBattleResources->transferBuffer[4] = (ret32 & 0x0000FF00) >> 16;
    gBattleResources->transferBuffer[5] = (ret32 & 0x0000FF00) >> 24;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 6);
}

void BtlController_EmitChosenMonReturnValue(u32 battler, u32 bufferId, u8 partyId, u8 *battlePartyOrder)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_CHOSENMONRETURNVALUE;
    gBattleResources->transferBuffer[1] = partyId;
    for (i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
        gBattleResources->transferBuffer[2 + i] = battlePartyOrder[i];
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 5);
}

void BtlController_EmitOneReturnValue(u32 battler, u32 bufferId, u16 ret)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_ONERETURNVALUE;
    gBattleResources->transferBuffer[1] = ret;
    gBattleResources->transferBuffer[2] = (ret & 0xFF00) >> 8;
    gBattleResources->transferBuffer[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitOneReturnValue_Duplicate(u32 battler, u32 bufferId, u16 ret)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_ONERETURNVALUE_DUPLICATE;
    gBattleResources->transferBuffer[1] = ret;
    gBattleResources->transferBuffer[2] = (ret & 0xFF00) >> 8;
    gBattleResources->transferBuffer[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

// Unused
static void BtlController_EmitClearUnkVar(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_CLEARUNKVAR;
    gBattleResources->transferBuffer[1] = CONTROLLER_CLEARUNKVAR;
    gBattleResources->transferBuffer[2] = CONTROLLER_CLEARUNKVAR;
    gBattleResources->transferBuffer[3] = CONTROLLER_CLEARUNKVAR;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

// Unused
static void BtlController_EmitSetUnkVar(u32 battler, u32 bufferId, u8 b)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_SETUNKVAR;
    gBattleResources->transferBuffer[1] = b;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

// Unused
static void BtlController_EmitClearUnkFlag(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_CLEARUNKFLAG;
    gBattleResources->transferBuffer[1] = CONTROLLER_CLEARUNKFLAG;
    gBattleResources->transferBuffer[2] = CONTROLLER_CLEARUNKFLAG;
    gBattleResources->transferBuffer[3] = CONTROLLER_CLEARUNKFLAG;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

// Unused
static void BtlController_EmitToggleUnkFlag(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_TOGGLEUNKFLAG;
    gBattleResources->transferBuffer[1] = CONTROLLER_TOGGLEUNKFLAG;
    gBattleResources->transferBuffer[2] = CONTROLLER_TOGGLEUNKFLAG;
    gBattleResources->transferBuffer[3] = CONTROLLER_TOGGLEUNKFLAG;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitHitAnimation(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_HITANIMATION;
    gBattleResources->transferBuffer[1] = CONTROLLER_HITANIMATION;
    gBattleResources->transferBuffer[2] = CONTROLLER_HITANIMATION;
    gBattleResources->transferBuffer[3] = CONTROLLER_HITANIMATION;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitCantSwitch(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_CANTSWITCH;
    gBattleResources->transferBuffer[1] = CONTROLLER_CANTSWITCH;
    gBattleResources->transferBuffer[2] = CONTROLLER_CANTSWITCH;
    gBattleResources->transferBuffer[3] = CONTROLLER_CANTSWITCH;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitPlaySE(u32 battler, u32 bufferId, u16 songId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_PLAYSE;
    gBattleResources->transferBuffer[1] = songId;
    gBattleResources->transferBuffer[2] = (songId & 0xFF00) >> 8;
    gBattleResources->transferBuffer[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitPlayFanfareOrBGM(u32 battler, u32 bufferId, u16 songId, bool8 playBGM)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_PLAYFANFAREORBGM;
    gBattleResources->transferBuffer[1] = songId;
    gBattleResources->transferBuffer[2] = (songId & 0xFF00) >> 8;
    gBattleResources->transferBuffer[3] = playBGM; //was 0 check vsonic important
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitFaintingCry(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_FAINTINGCRY;
    gBattleResources->transferBuffer[1] = CONTROLLER_FAINTINGCRY;
    gBattleResources->transferBuffer[2] = CONTROLLER_FAINTINGCRY;
    gBattleResources->transferBuffer[3] = CONTROLLER_FAINTINGCRY;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitIntroSlide(u32 battler, u32 bufferId, u8 terrainId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_INTROSLIDE;
    gBattleResources->transferBuffer[1] = terrainId;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

void BtlController_EmitIntroTrainerBallThrow(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_INTROTRAINERBALLTHROW;
    gBattleResources->transferBuffer[1] = CONTROLLER_INTROTRAINERBALLTHROW;
    gBattleResources->transferBuffer[2] = CONTROLLER_INTROTRAINERBALLTHROW;
    gBattleResources->transferBuffer[3] = CONTROLLER_INTROTRAINERBALLTHROW;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitDrawPartyStatusSummary(u32 battler, u32 bufferId, struct HpAndStatus* hpAndStatus, u8 flags)
{
    s32 i;

    gBattleResources->transferBuffer[0] = CONTROLLER_DRAWPARTYSTATUSSUMMARY;
    gBattleResources->transferBuffer[1] = flags & ~PARTY_SUMM_SKIP_DRAW_DELAY; // If true, skip player side
    gBattleResources->transferBuffer[2] = (flags & PARTY_SUMM_SKIP_DRAW_DELAY) >> 7; // If true, skip delay after drawing. True during intro
    gBattleResources->transferBuffer[3] = CONTROLLER_DRAWPARTYSTATUSSUMMARY;
    for (i = 0; i < (s32)(sizeof(struct HpAndStatus) * PARTY_SIZE); ++i)
        gBattleResources->transferBuffer[4 + i] = *(i + (u8 *)(hpAndStatus));
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, sizeof(struct HpAndStatus) * PARTY_SIZE + 4);
}//vsonic applied EE upgrade test

void BtlController_EmitHidePartyStatusSummary(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    gBattleResources->transferBuffer[1] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    gBattleResources->transferBuffer[2] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    gBattleResources->transferBuffer[3] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitEndBounceEffect(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_ENDBOUNCE;
    gBattleResources->transferBuffer[1] = CONTROLLER_ENDBOUNCE;
    gBattleResources->transferBuffer[2] = CONTROLLER_ENDBOUNCE;
    gBattleResources->transferBuffer[3] = CONTROLLER_ENDBOUNCE;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitSpriteInvisibility(u32 battler, u32 bufferId, bool8 isInvisible)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_SPRITEINVISIBILITY;
    gBattleResources->transferBuffer[1] = isInvisible;
    gBattleResources->transferBuffer[2] = CONTROLLER_SPRITEINVISIBILITY;
    gBattleResources->transferBuffer[3] = CONTROLLER_SPRITEINVISIBILITY;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4);
}

void BtlController_EmitBattleAnimation(u32 battler, u32 bufferId, u8 animationId, struct DisableStruct* disableStructPtr, u16 argument)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_BATTLEANIMATION;
    gBattleResources->transferBuffer[1] = animationId;
    gBattleResources->transferBuffer[2] = argument;
    gBattleResources->transferBuffer[3] = (argument & 0xFF00) >> 8;
    memcpy(&gBattleResources->transferBuffer[4], disableStructPtr, sizeof(struct DisableStruct));
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 4 + sizeof(struct DisableStruct));
}

// mode is a LINK_STANDBY_* constant
void BtlController_EmitLinkStandbyMsg(u32 battler, u32 bufferId, u8 mode)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_LINKSTANDBYMSG;
    gBattleResources->transferBuffer[1] = mode;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

void BtlController_EmitResetActionMoveSelection(u32 battler, u32 bufferId, u8 caseId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_RESETACTIONMOVESELECTION;
    gBattleResources->transferBuffer[1] = caseId;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

void BtlController_EmitEndLinkBattle(u32 battler, u32 bufferId, u8 battleOutcome)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_ENDLINKBATTLE;
    gBattleResources->transferBuffer[1] = battleOutcome;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 2);
}

void BtlController_EmitDebugMenu(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_DEBUGMENU;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 1);
}

void BtlController_EmitMoveInfo(u32 battler, u32 bufferId)
{
    gBattleResources->transferBuffer[0] = CONTROLLER_MOVEINFO;
    PrepareBufferDataTransfer(battler, bufferId, gBattleResources->transferBuffer, 1);
}