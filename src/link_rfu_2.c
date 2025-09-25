#include "global.h"
#include "gflib.h"
#include "librfu.h"
#include "battle.h"
#include "link.h"
#include "link_rfu.h"
#include "mystery_gift_menu.h"
#include "overworld.h"
#include "quest_log.h"
#include "random.h"
#include "task.h"
#include "constants/union_room.h"

struct SioInfo
{
    char magic[15]; // PokemonSioInfo
    u8 playerCount;
    u8 linkPlayerIdx[RFU_CHILD_MAX];
    struct LinkPlayer linkPlayers[MAX_RFU_PLAYERS];
    u8 fill_a0[0x5c];
};

static EWRAM_DATA struct InitializeParametersTag sRfuReqConfig = {};
static EWRAM_DATA struct UnkLinkRfuStruct_02022B44 gUnknown_203AC08 = {};

static u32 gf_rfu_REQ_api[RFU_API_BUFF_SIZE_RAM / 4];
static u8 sResendBlock8[CMD_LENGTH * 2];
static u16 sResendBlock16[CMD_LENGTH];

COMMON_DATA struct RfuGameData gHostRfuGameData = {0};
COMMON_DATA struct RfuManager gRfu = {0};
COMMON_DATA u8 gHostRfuUsername[PLAYER_NAME_LENGTH + 1] = {0};

static void sub_80F8AA4(void);
static void sub_80F8AEC(void);
static void MscCallback_Child(u16 a0);
static void MSCCallback_SetUnkCDB(u16 a0);
static void sub_80F906C(void);
static void RfuHandleReceiveCommand(u8 unused);
static void ResetSendDataManager(struct RfuBlockSend *data);
static void RfuPrepareSendBuffer(u16 command);
static void RfuFunc_HandleBlockSend(void);
static void RfuFunc_SendNextBlock(void);
static void RfuFunc_SendLastBlock(void);
static void CallRfuFunc(void);
static void sub_80FA738(void);
static s32 sub_80FA788(void);
static void sub_80FA834(u8 taskId);
static void sub_80FA9D0(u16 a0);
static void ValidateAndReceivePokemonSioInfo(void * a0);
static void Task_ExchangeLinkPlayers(u8 taskId);
static void sub_80FACF0(u8 taskId);
static void GetLinkmanErrorParams(u32 msg);
static void sub_80FB564(s32 bmConnectedFlag);
static void sub_80FBB74(void);
static u8 GetPartnerIndexByNameAndTrainerID(const u8 *trainerName, u16 trainerId);
static void RfuReqDisconnectSlot(u32 bmDisconnectSlot);
static void sub_80FBE20(u32 a0, u32 a1);
static void sub_80FC028(u8 taskId);
static void rfu_dbg_clear(void);
static void Task_idle(u8 taskId);

static const struct InitializeParametersTag sRfuReqConfigTemplate = {
    .maxMFrame = 4,
    .MC_TimerCount = 32,
    .availSlot_flag = 0,
    .mboot_flag = 0,
    .serialNo = 0x0002,
    .gameName = (void *)&gHostRfuGameData,
    .userName = gHostRfuUsername,
    .fastSearchParent_flag = TRUE,
    .linkRecovery_enable = FALSE,
    .linkRecovery_period = 600,
    .NI_failCounter_limit = 300
};

static const u8 sAvailSlots[] = {
    [1] = AVAIL_SLOT1,
    [2] = AVAIL_SLOT2,
    [3] = AVAIL_SLOT3,
    [4] = AVAIL_SLOT4
};

static const u32 sAllBlocksReceived[] = {
    0x000000,
    0x000001,
    0x000003,
    0x000007,
    0x00000f,
    0x00001f,
    0x00003f,
    0x00007f,
    0x0000ff,
    0x0001ff,
    0x0003ff,
    0x0007ff,
    0x000fff,
    0x001fff,
    0x003fff,
    0x007fff,
    0x00ffff,
    0x01ffff,
    0x03ffff,
    0x07ffff,
    0x0fffff,
    0x1fffff,
    0x3fffff,
    0x7fffff,
    0xffffff
};

static const u8 gUnknown_843EC38[] = {
    0, 0, 1,
    1, 2, 2,
    2, 2, 3
};

static const u8 gUnknown_843EC41[] = {
    0, 1, 1, 2,
    1, 2, 2, 3,
    1, 2, 2, 3,
    2, 3, 3, 4
};

static const u8 gUnknown_843EC51[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

static const struct {
    u8 *buffer;
    u32 size;
} gUnknown_843EC64[] = {
    { gBlockSendBuffer, 200 },
    { gBlockSendBuffer, 200 },
    { gBlockSendBuffer, 100 },
    { gBlockSendBuffer, 220 },
    { gBlockSendBuffer,  40 }
};

static const u16 sAcceptedSerialNos[] = {
    0x0002, // Pokemon FR/LG/EM
    0x7f7d,
    0xFFFF
};

static const char sUnref_843EC92[][15] = {
    "RFU WAIT",
    "RFU BOOT",
    "RFU ERROR",
    "RFU RESET",
    "RFU CONFIG",
    "RFU START",
    "RFU SC POLL",
    "RFU SP POLL",
    "RFU START",
    "RFU SEND ERR",
    "RFU CP POLL"
};

static const char sUnref_843ED37[][16] = {
    "              ",
    "RECOVER START ",
    "DISSCONECT    ",
    "RECOVER SUUSES",
    "RECOVER FAILED"
};

static const TaskFunc gUnknown_843ED88[] = {
    sub_80FA834,
    Task_ExchangeLinkPlayers,
    sub_80FACF0
};

static void rfu_dbg_print_str(const void *string, u8 x, u8 y)
{
    // debug?
}

static void rfu_dbg_print_num(u16 num, u8 x, u8 y, u8 ndigits)
{

}

void ResetLinkRfuGFLayer(void)
{
    s32 i;
    u8 errorState_bak = gRfu.errorState;
    CpuFill16(0, &gRfu, sizeof gRfu);
    gRfu.parent_child = MODE_NEUTRAL;
    gRfu.errorState = errorState_bak;
    if (gRfu.errorState != 4)
    {
        gRfu.errorState = 0;
    }
    for (i = 0; i < 5; i++)
    {
        ResetSendDataManager(gRfu.cmd_8800_recvbuf + i);
    }
    ResetSendDataManager(&gRfu.cmd_8800_sendbuf);
    RFU_queue_20_70_reset(&gRfu.unk_124);
    RFU_queue_40_14_reset(&gRfu.sendQueue);
    CpuFill16(0, gSendCmd, sizeof gSendCmd);
    CpuFill16(0, gRecvCmds, sizeof gRecvCmds);
    CpuFill16(0, gLinkPlayers, sizeof gLinkPlayers);
}

void InitRFU(void)
{
    IntrFunc serialIntr = gIntrTable[1];
    IntrFunc timerIntr = gIntrTable[2];
    sub_80F86F4();
    rfu_REQ_stopMode();
    rfu_waitREQComplete();
    REG_IME = 0;
    gIntrTable[1] = serialIntr;
    gIntrTable[2] = timerIntr;
    REG_IME = INTR_FLAG_VBLANK;
}

void sub_80F86F4(void)
{
    if (!rfu_initializeAPI(gf_rfu_REQ_api, RFU_API_BUFF_SIZE_RAM, gIntrTable + 1, TRUE))
    {
        gLinkType = 0;
        sub_80FB128(FALSE);
        ResetLinkRfuGFLayer();
        rfu_setTimerInterrupt(3, gIntrTable + 2);
    }
}

static void Task_LinkLeaderSearchForChildren(u8 taskId)
{
    sub_80FA738();
    switch (gRfu.state)
    {
    case 0:
        rfu_LMAN_initializeRFU(&sRfuReqConfig);
        gRfu.state = 1;
        gTasks[taskId].data[1] = 1;
        break;
    case 1:
        break;
    case 2:
        rfu_LMAN_establishConnection(gRfu.parent_child, 0, 240, (u16*)sAcceptedSerialNos);
        gRfu.state = 3;
        gTasks[taskId].data[1] = 6;
        break;
    case 3:
        break;
    case 4:
        rfu_LMAN_stopManager(0);
        gRfu.state = 5;
        break;
    case 5:
        break;
    case 18:
        gRfu.unk_cdb = 0;
        rfu_LMAN_setMSCCallback(MSCCallback_SetUnkCDB);
        sub_80F8AA4();
        sub_80F8AEC();
        gRfu.state = 20;
        gTasks[taskId].data[1] = 8;
        CreateTask(sub_80FA834, 5);
        DestroyTask(taskId);
        break;
    }
}

static u8 sub_80F886C(u8 idx)
{
    return gUnknown_843EC51[idx];
}

static void sub_80F887C(s32 r2, s32 r5)
{
    u8 i;
    u8 r4 = 1;
    s32 r1 = r2;
    s32 r6 = 0;
    if (r5 == -1)
    {
        for (i = 0; i < RFU_CHILD_MAX; r2 >>= 1, i++)
        {
            if (r2 & 1)
            {
                gRfu.linkPlayerIdx[i] = r4;
                r4++;
            }
        }
    }
    else
    {
        for (i = 0; i < RFU_CHILD_MAX; r1 >>= 1, i++)
        {
            if (!(r1 & 1))
            {
                gRfu.linkPlayerIdx[i] = 0;
            }
        }
        for (r4 = 4; r4 != 0; r4--)
        {
            for (i = 0; i < RFU_CHILD_MAX && gRfu.linkPlayerIdx[i] != r4; i++);
            if (i == 4)
            {
                r6 = r4;
            }
        }
        for (r5 &= ~r2, i = 0; i < RFU_CHILD_MAX; r5 >>= 1, i++)
        {
            if (r5 & 1)
            {
                gRfu.linkPlayerIdx[i] = r6++;
            }
        }
    }
}

static void Task_JoinGroupSearchForParent(u8 taskId)
{
    switch (gRfu.state)
    {
    case 0:
        rfu_LMAN_initializeRFU((INIT_PARAM*)&sRfuReqConfigTemplate);
        gRfu.state = 1;
        gTasks[taskId].data[1] = 1;
        break;
    case 1:
        break;
    case 6:
        rfu_LMAN_establishConnection(gRfu.parent_child, 0, 240, (u16*)sAcceptedSerialNos);
        gRfu.state = 7;
        gTasks[taskId].data[1] = 7;
        break;
    case 7:
        break;
    case 9:
        gTasks[taskId].data[1] = 10;
        break;
    case 11:
        switch (sub_80FA788())
        {
        case 5:
            gRfu.state = 12;
            break;
        case 6:
        case 9:
            rfu_LMAN_requestChangeAgbClockMaster();
            gRfu.unk_ce4 = 2;
            DestroyTask(taskId);
            break;
        }
        break;
    case 12:
    {
        u8 bmChildSlot = 1 << gRfu.child_slot;
        rfu_clearSlot(TYPE_NI_SEND | TYPE_NI_RECV, gRfu.child_slot);
        rfu_setRecvBuffer(TYPE_UNI, gRfu.child_slot, gRfu.unk_c3f, sizeof(gRfu.unk_c3f));
        rfu_UNI_setSendData(bmChildSlot, gRfu.unk_4c, sizeof(gRfu.unk_4c));
        gTasks[taskId].data[1] = 8;
        DestroyTask(taskId);
        if (gUnknown_203AC08.unk_0f == 0)
        {
            rfu_dbg_clear();
            gUnknown_203AC08.unk_0f++;
        }
        CreateTask(sub_80FA834, 5);
        break;
    }
    }
}

static void sub_80F8AA4(void)
{
    u8 i;
    u8 acceptSlot = lman.acceptSlot_flag;
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if (acceptSlot & 1)
        {
            rfu_setRecvBuffer(TYPE_UNI, i, gRfu.unk_14[i], sizeof(gRfu.unk_14[i]));
            rfu_clearSlot(TYPE_UNI_SEND | TYPE_UNI_RECV, i);
        }
        acceptSlot >>= 1;
    }
}

static void sub_80F8AEC(void)
{
    u8 acceptSlot = lman.acceptSlot_flag;
    rfu_UNI_setSendData(acceptSlot, gRfu.recvCmds, sizeof(gRfu.recvCmds));
    gRfu.unk_cda = sub_80F886C(acceptSlot);
    gRfu.bm_PartnerFlags = acceptSlot;
    sub_80F887C(acceptSlot, -1);
    gRfu.parent_child = MODE_PARENT;
}

static void Task_LinkRfu_UnionRoomListen(u8 taskId)
{
    if (GetHostRFUtgtGname()->activity == (ACTIVITY_PLYRTALK | IN_UNION_ROOM) && RfuGetErrorStatus() == 4)
    {
        rfu_REQ_disconnect(lman.acceptSlot_flag);
        rfu_waitREQComplete();
        RfuSetErrorStatus(0, 0);
    }
    switch (gRfu.state)
    {
    case 0:
        rfu_LMAN_initializeRFU(&sRfuReqConfig);
        gRfu.state = 1;
        gTasks[taskId].data[1] = 1;
        break;
    case 1:
        break;
    case 17:
        rfu_LMAN_establishConnection(2, 0, 240, (u16*)sAcceptedSerialNos);
        rfu_LMAN_setMSCCallback(MscCallback_Child);
        gRfu.state = 18;
        break;
    case 18:
        break;
    case 13:
        if (rfu_UNI_setSendData(1 << gRfu.child_slot, gRfu.unk_4c, sizeof(gRfu.unk_4c)) == 0)
        {
            gRfu.parent_child = MODE_CHILD;
            DestroyTask(taskId);
            if (gTasks[taskId].data[7])
            {
                CreateTask(sub_80FACF0, 1);
            }
            else
            {
                CreateTask(sub_80FA834, 5);
            }
        }
        break;
    case 14:
        rfu_LMAN_stopManager(0);
        gRfu.state = 15;
        break;
    case 15:
        break;
    case 16:
        gRfu.unk_cdb = 0;
        rfu_LMAN_setMSCCallback(MSCCallback_SetUnkCDB);
        UpdateGameData_GroupLockedIn(1);
        sub_80F8AA4();
        sub_80F8AEC();
        gRfu.state = 20;
        gTasks[taskId].data[1] = 8;
        gRfu.parent_child = MODE_PARENT;
        CreateTask(sub_80FA834, 5);
        gRfu.unk_ce8 = TRUE;
        DestroyTask(taskId);
        break;
    }
}

void LinkRfu_CreateConnectionAsParent(void)
{
    rfu_LMAN_establishConnection(MODE_PARENT, 0, 240, (u16*)sAcceptedSerialNos);
}

void LinkRfu_StopManagerBeforeEnteringChat(void)
{
    rfu_LMAN_stopManager(0);
}

static void MscCallback_Child(u16 unused)
{
    s32 i;

    for (i = 0; i < 14; i++)
    {
        gRfu.unk_4c[i] = 0;
    }
    rfu_REQ_recvData();
    rfu_waitREQComplete();
    if (gRfuSlotStatusUNI[gRfu.child_slot]->recv.newDataFlag)
    {
        gRfu.unk_cd0++;
        RFU_queue_20_70_recv(&gRfu.unk_124, gRfu.unk_c3f);
        gUnknown_203AC08.unk_06++;
        sub_80F906C();
        rfu_UNI_readySendData(gRfu.child_slot);
        rfu_UNI_clearRecvNewDataFlag(gRfu.child_slot);
    }
    rfu_LMAN_REQ_sendData(TRUE);
}

static void MSCCallback_SetUnkCDB(u16 unused)
{
    gRfu.unk_cdb = 1;
}

void LinkRfu_Shutdown(void)
{
    u8 i;

    if (QL_IS_PLAYBACK_STATE)
        return;

    rfu_LMAN_powerDownRFU();
    if (gRfu.parent_child == MODE_PARENT)
    {
        if (FuncIsActiveTask(Task_LinkLeaderSearchForChildren) == TRUE)
        {
            DestroyTask(gRfu.unk_67);
            ResetLinkRfuGFLayer();
        }
    }
    else if (gRfu.parent_child == MODE_CHILD)
    {
        if (FuncIsActiveTask(Task_JoinGroupSearchForParent) == TRUE)
        {
            DestroyTask(gRfu.unk_67);
            ResetLinkRfuGFLayer();
        }
    }
    else if (gRfu.parent_child == 2)
    {
        if (FuncIsActiveTask(Task_LinkRfu_UnionRoomListen) == TRUE)
        {
            DestroyTask(gRfu.unk_67);
            ResetLinkRfuGFLayer();
        }
    }
    for (i = 0; i < NELEMS(gUnknown_843ED88); i++)
    {
        if (FuncIsActiveTask(gUnknown_843ED88[i]) == TRUE)
        {
            DestroyTask(FindTaskIdByFunc(gUnknown_843ED88[i]));
        }
    }
}

static void CreateTask_LinkLeaderSearchForChildren(void)
{
    if (QL_IS_PLAYBACK_STATE)
        return;
    gRfu.unk_67 = CreateTask(Task_LinkLeaderSearchForChildren, 1);
}

static bool8 RfuStateIs7AndPlayerIsChild(void)
{
    if (gRfu.state == 7 && gRfu.parentId)
    {
        return TRUE;
    }
    return FALSE;
}

static bool32 IsParentSuccessfullyReconnected(void)
{
    if (gRfu.state == 7 && !rfu_LMAN_CHILD_connectParent(gRfuLinkStatus->partner[gRfu.reconnectedParentIdx].id, 240))
    {
        gRfu.state = 9;
        return TRUE;
    }
    return FALSE;
}

static void CreateTask_JoinGroupSearchForParent(void)
{
    if (QL_IS_PLAYBACK_STATE)
        return;
    gRfu.unk_67 = CreateTask(Task_JoinGroupSearchForParent, 1);
}

bool8 LmanAcceptSlotFlagIsNotZero(void)
{
    if (lman.acceptSlot_flag)
    {
        return TRUE;
    }
    return FALSE;
}

void LinkRfu_StopManagerAndFinalizeSlots(void)
{
    gRfu.state = 4;
    gRfu.acceptSlot_flag = lman.acceptSlot_flag;
}

bool32 WaitRfuState(bool32 force)
{
    if (gRfu.state == 17 || force)
    {
        gRfu.state = 18;
        return TRUE;
    }
    return FALSE;
}

void sub_80F8FA0(void)
{
    gRfu.state = 14;
}

static void sub_80F8FAC(u8 a0)
{
    u8 i;

    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if (a0 & 1)
        {
            rfu_UNI_readySendData(i);
            break;
        }
        a0 >>= 1;
    }
}

static void sub_80F8FD4(void)
{
    s32 i, j;

    for (i = 0; i < 5; i++)
    {
        struct RfuManager *ptr = &gRfu;
        for (j = 0; j < 7; j++)
        {
            ptr->recvCmds[i][j][1] = gRecvCmds[i][j] >> 8;
            ptr->recvCmds[i][j][0] = gRecvCmds[i][j];
        }
    }
    CpuFill16(0, gRecvCmds, sizeof gRecvCmds);
}

static void sub_80F9038(void)
{
    s32 i;
    for (i = 0; i < 7; i++)
    {
        gRecvCmds[0][i] = gSendCmd[i];
    }
    for (i = 0; i < 7; i++)
    {
        gSendCmd[i] = 0;
    }
}

static void sub_80F906C(void)
{
    if (gRfu.unk_c3c)
    {
        u8 r2 = RFU_queue_2_14_send(&gRfu.unk_c1c, gRfu.unk_4c);
        if (gRfu.unk_c1c.count == 0)
        {
            gRfu.unk_c3c = 0;
        }
        if (r2)
        {
            return;
        }
    }
    if (gRfu.unk_c3c == 0)
    {
        RFU_queue_40_14_send(&gRfu.sendQueue, gRfu.unk_4c);
        RFU_queue_2_14_recv(&gRfu.unk_c1c, gRfu.unk_4c);
    }
}

bool32 IsRfuRecvQueueEmpty(void)
{
    s32 i;
    s32 j;

    if (gRfuLinkStatus->sendSlotUNIFlag == 0)
    {
        return FALSE;
    }
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (gRecvCmds[i][j] != 0)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

static bool32 sub_80F911C(void)
{
    if (gRfu.state < 20)
    {
        rfu_REQ_recvData();
        rfu_waitREQComplete();
        rfu_LMAN_REQ_sendData(FALSE);
    }
    else
    {
        gRfu.unk_cdb = 0;
        if ((gRfu.bm_PartnerFlags & gRfuLinkStatus->connSlotFlag) == gRfu.bm_PartnerFlags && (gRfu.bm_PartnerFlags & gRfuLinkStatus->connSlotFlag))
        {
            if (!gRfu.unk_cdc)
            {
                if (gRfu.bm_DisconnectSlot)
                {
                    RfuReqDisconnectSlot(gRfu.bm_DisconnectSlot);
                    gRfu.bm_DisconnectSlot = 0;
                    if (gRfu.unk_ce4 == 1)
                    {
                        RfuSetErrorStatus(2, 0x8000);
                        GetLinkmanErrorParams(0x8000);
                        return FALSE;
                    }
                    if (!lman.acceptSlot_flag)
                    {
                        LinkRfu_Shutdown();
                        gReceivedRemoteLinkPlayers = FALSE;
                        return FALSE;
                    }
                }
                sub_80F8FD4();
                rfu_UNI_readySendData(gRfu.unk_cda);
                rfu_LMAN_REQ_sendData(TRUE);
            }
            else
            {
                rfu_REQ_PARENT_resumeRetransmitAndChange();
            }
            gRfu.unk_0e = 1;
        }
    }
    return FALSE;
}

static bool32 sub_80F9204(void)
{
    u16 i;
    u16 flags;
    u8 r0;
    u16 j;
    u8 retval;

    if (gRfu.state >= 20 && gRfu.unk_0e == 1)
    {
        rfu_waitREQComplete();
        while (gRfu.unk_cdb == 0)
        {
            if (gRfu.errorState != 0)
            {
                return FALSE;
            }
        }
        rfu_REQ_recvData();
        rfu_waitREQComplete();
        if ((lman.parentAck_flag & gRfu.bm_PartnerFlags) == gRfu.bm_PartnerFlags)
        {
            gRfu.unk_cdc = 0;
            gUnknown_203AC08.unk_06++;
            flags = lman.acceptSlot_flag;
            for (i = 0; i < RFU_CHILD_MAX; i++)
            {
                if (flags & 1)
                {
                    if (gRfu.unk_14[i][1])
                    {
                        if (gRfu.unk_cee[i] != 0xFF && (gRfu.unk_14[i][0] >> 5) != ((gRfu.unk_cee[i] + 1) & 7))
                        {
                            if (++gRfu.unk_cea[i] > 4)
                                GetLinkmanErrorParams(0x8100);
                        }
                        else
                        {
                            gRfu.unk_cee[i] = gRfu.unk_14[i][0] / 32;
                            gRfu.unk_cea[i] = 0;
                            gRfu.unk_14[i][0] &= 0x1f;
                            r0 = gRfu.linkPlayerIdx[i];
                            for (j = 0; j < 7; j++)
                            {
                                gRecvCmds[r0][j] = (gRfu.unk_14[i][(j << 1) + 1] << 8) | gRfu.unk_14[i][(j << 1) + 0];
                                gRfu.unk_14[i][(j << 1) + 1] = 0;
                                gRfu.unk_14[i][(j << 1) + 0] = 0;
                            }
                        }
                    }
                    rfu_UNI_clearRecvNewDataFlag(i);
                }
                flags >>= 1;
            }
            sub_80F9038();
            RfuHandleReceiveCommand(0);
            CallRfuFunc();
            if (gRfu.unk_ce5 && !gRfu.unk_cd9)
            {
                gUnknown_203AC08.unk_0e = 0;
                rfu_clearSlot(TYPE_UNI_SEND | TYPE_UNI_RECV, gRfu.unk_cda);
                for (i = 0; i < RFU_CHILD_MAX; i++)
                {
                    if ((gRfu.unk_ce5 >> i) & 1)
                    {
                        rfu_setRecvBuffer(TYPE_UNI, i, gRfu.unk_14[i], sizeof(gRfu.unk_14[i]));
                    }
                }
                sub_80F887C(gRfu.bm_PartnerFlags, gRfu.bm_PartnerFlags | gRfu.unk_ce5);
                gRfu.unk_ce9 = gRfu.unk_ce5;
                gRfu.bm_PartnerFlags |= gRfu.unk_ce5;
                gRfu.unk_ce5 = 0;
                rfu_UNI_setSendData(gRfu.bm_PartnerFlags, gRfu.recvCmds, sizeof(gRfu.recvCmds));
                gRfu.unk_cda = sub_80F886C(gRfu.bm_PartnerFlags);
                CreateTask(Task_ExchangeLinkPlayers, 0);
            }
        }
        else
        {
            gRfu.unk_cdc = 1;
            gRfu.unk_0e = 0;
        }
        gRfu.unk_0e = 0;
    }
    retval = gRfu.unk_cdc;
    return gRfuLinkStatus->sendSlotUNIFlag ? retval & 1 : FALSE;
}

static void sub_80F94BC(u16 *a0, u8 *a1)
{
    s32 i;

    if (a0[0])
    {
        a0[0] |= (gRfu.unk_102 << 5);
        gRfu.unk_102 = (gRfu.unk_102 + 1) & 7;
        for (i = 0; i < 7; i++)
        {
            a1[2 * i + 1] = a0[i] >> 8;
            a1[2 * i + 0] = a0[i];
        }
    }
    else
    {
        for (i = 0; i < 14; i++)
            a1[i] = 0;
    }
}

static bool32 RfuProcessEnqueuedRecvBlock(void)
{
    u8 i;
    u8 j;
    u8 sp00[MAX_RFU_PLAYERS * (2 * (CMD_LENGTH - 1))];
    u8 sp48[2 * (CMD_LENGTH - 1)];
    u8 switchval;

    RFU_queue_20_70_send(&gRfu.unk_124, sp00);
    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        for (j = 0; j < CMD_LENGTH - 1; j++)
        {
            gRecvCmds[i][j] = (sp00[i * 14 + (j << 1) + 1] << 8) | sp00[i * 14 + (j << 1) + 0];
        }
    }
    RfuHandleReceiveCommand(0);
    if (lman.childClockSlave_flag == 0 && gRfu.unk_ce4)
    {
        rfu_REQ_disconnect(gRfuLinkStatus->connSlotFlag | gRfuLinkStatus->linkLossSlotFlag);
        rfu_waitREQComplete();
        switchval = RfuGetErrorStatus();
        if (switchval != 1 && switchval != 6 && switchval != 9)
            RfuSetErrorStatus(2, 0x9000);
        rfu_clearAllSlot();
        gReceivedRemoteLinkPlayers = FALSE;
        gRfu.RfuFunc = NULL;
        if (gRfu.unk_ce4 == 1)
        {
            RfuSetErrorStatus(2, 0x9000);
            GetLinkmanErrorParams(0x9000);
        }
        lman.state = lman.next_state = 0;
        gRfu.unk_ce4 = 0;
    }
    if (gRfu.unk_cd0)
    {
        gRfu.unk_cd0--;
        CallRfuFunc();
        sub_80F94BC(gSendCmd, sp48);
        RFU_queue_40_14_recv(&gRfu.sendQueue, sp48);
        for (i = 0; i < CMD_LENGTH - 1; i++)
            gSendCmd[i] = 0;
    }
    return IsRfuRecvQueueEmpty();
}

static void HandleSendFailure(u8 unused, u32 flags)
{
    s32 i, j, temp;

    const u8 *payload = gRfu.cmd_8800_sendbuf.payload;
    for (i = 0; i < gRfu.cmd_8800_sendbuf.count; i++)
    {
        if (!(flags & 1))
        {
            sResendBlock16[0] = RFUCMD_SEND_BLOCK | i;
            for (j = 0; j < CMD_LENGTH - 1; j++)
            {
                temp = j * 2;
                sResendBlock16[j + 1] = (payload[(COMM_SLOT_LENGTH - 2) * i + temp + 1] << 8)
                                       | payload[(COMM_SLOT_LENGTH - 2) * i + temp + 0];
            }
            for (j = 0; j < CMD_LENGTH - 1; j++)
            {
                temp = j * 2;
                sResendBlock8[temp + 1] = sResendBlock16[j] >> 8;
                sResendBlock8[temp + 0] = sResendBlock16[j];
            }
            RFU_queue_40_14_recv(&gRfu.sendQueue, sResendBlock8);
            gRfu.cmd_8800_sendbuf.failedFlags |= (1 << i);
        }
        flags >>= 1;
    }
}

void Rfu_SetBlockReceivedFlag(u8 a0)
{
    if (gRfu.parent_child == MODE_PARENT && a0)
        gRfu.unk_61[a0] = 1;
    else
        gRfu.unk_5c[a0] = 1;
}

void Rfu_ResetBlockReceivedFlag(u8 a0)
{
    gRfu.unk_5c[a0] = 0;
    gRfu.cmd_8800_recvbuf[a0].receiving = 0;
}

static u8 sub_80F9770(const u8 *a0)
{
    u8 i;

    if (gRfu.parent_child == MODE_PARENT)
        return FALSE;
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        gRfu.linkPlayerIdx[i] = a0[i];
    }
    return a0[gRfu.child_slot];
}

static void RfuFunc_SendKeysToRfu(void)
{
     static u8 gUnknown_3001188;
    if (gReceivedRemoteLinkPlayers
        && gHeldKeyCodeToSend != LINK_KEY_CODE_NULL
        && gLinkTransferringData != TRUE)
    {
        gUnknown_3001188++;
        gHeldKeyCodeToSend |= (gUnknown_3001188 << 8);
        RfuPrepareSendBuffer(RFUCMD_SEND_HELD_KEYS);
    }
}

struct RfuGameData *GetHostRFUtgtGname(void)
{
    return &gHostRfuGameData;
}

bool32 IsSendingKeysToRfu(void)
{
    return gRfu.RfuFunc == RfuFunc_SendKeysToRfu;
}

void StartSendingKeysToRfu(void)
{
    AGB_ASSERT_EX(gRfu.RfuFunc == NULL, ABSPATH("gRfu.c"), 1473);
    gRfu.RfuFunc = RfuFunc_SendKeysToRfu;
}

void Rfu_set_zero(void)
{
    gRfu.RfuFunc = NULL;
}

static void RfuHandleReceiveCommand(u8 unused)
{
    u16 i;
    u16 j;

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        switch (gRecvCmds[i][0] & 0xff00)
        {
        case RFUCMD_SEND_PLAYER_IDS_NEW:
            if (gRfu.parent_child == MODE_CHILD && gReceivedRemoteLinkPlayers)
                return;
            // fallthrough
        case RFUCMD_SEND_PLAYER_IDS:
            if (gRfuLinkStatus->parentChild == MODE_CHILD)
            {
                gRfu.playerCount = gRecvCmds[i][1];
                gRfu.unk_cce = sub_80F9770((u8 *)(gRecvCmds[i] + 2));
            }
            break;
        case RFUCMD_SEND_BLOCK_INIT:
            if (gRfu.cmd_8800_recvbuf[i].receiving == 0)
            {
                gRfu.cmd_8800_recvbuf[i].next = 0;
                gRfu.cmd_8800_recvbuf[i].count = gRecvCmds[i][1];
                gRfu.cmd_8800_recvbuf[i].owner = gRecvCmds[i][2];
                gRfu.cmd_8800_recvbuf[i].receivedFlags = 0;
                gRfu.cmd_8800_recvbuf[i].receiving = 1;
                gRfu.unk_5c[i] = 0;
            }
            break;
        case RFUCMD_SEND_BLOCK:
            if (gRfu.cmd_8800_recvbuf[i].receiving == 1)
            {
                gRfu.cmd_8800_recvbuf[i].next = gRecvCmds[i][0] & 0xff;
                gRfu.cmd_8800_recvbuf[i].receivedFlags |= (1 << gRfu.cmd_8800_recvbuf[i].next);
                for (j = 0; j < 6; j++)
                    gBlockRecvBuffer[i][gRfu.cmd_8800_recvbuf[i].next * 6 + j] = gRecvCmds[i][j + 1];
                if (gRfu.cmd_8800_recvbuf[i].receivedFlags == sAllBlocksReceived[gRfu.cmd_8800_recvbuf[i].count])
                {
                    gRfu.cmd_8800_recvbuf[i].receiving = 2;
                    Rfu_SetBlockReceivedFlag(i);
                    if (GetHostRFUtgtGname()->activity == (ACTIVITY_CHAT | IN_UNION_ROOM) && gReceivedRemoteLinkPlayers && gRfu.parent_child == MODE_CHILD)
                        ValidateAndReceivePokemonSioInfo(gBlockRecvBuffer);
                }
            }
            break;
        case RFUCMD_SEND_BLOCK_REQ:
            Rfu_InitBlockSend(gUnknown_843EC64[gRecvCmds[i][1]].buffer, (u16)gUnknown_843EC64[gRecvCmds[i][1]].size);
            break;
        case RFUCMD_READY_CLOSE_LINK:
            gRfu.cmd5f00Ack[i] = 1;
            break;
        case RFUCMD_READY_EXIT_STANDBY:
            if (gRfu.cmd_6600_count == gRecvCmds[i][1])
                gRfu.cmd_6600_recvd[i] = 1;
            break;
        case RFUCMD_DISCONNECT:
            if (gRfu.parent_child == MODE_CHILD)
            {
                if (gReceivedRemoteLinkPlayers)
                {
                    if (gRecvCmds[i][1] & gRfuLinkStatus->connSlotFlag)
                    {
                        gReceivedRemoteLinkPlayers = FALSE;
                        rfu_LMAN_requestChangeAgbClockMaster();
                        gRfu.unk_ce4 = gRecvCmds[i][2];
                    }
                    gRfu.playerCount = gRecvCmds[i][3];
                    sub_80FA9D0(gRecvCmds[i][1]);
                }
            }
            else
            {
                RfuPrepareSendBuffer(RFUCMD_DISCONNECT_PARENT);
                gSendCmd[1] = gRecvCmds[i][1];
                gSendCmd[2] = gRecvCmds[i][2];
                gSendCmd[3] = gRecvCmds[i][3];
            }
            break;
        case RFUCMD_DISCONNECT_PARENT:
            if (gRfu.parent_child == MODE_PARENT)
            {
                gRfu.bm_DisconnectSlot |= gRecvCmds[i][1];
                gRfu.unk_ce4 = gRecvCmds[i][2];
                sub_80FA9D0(gRecvCmds[i][1]);
            }
            break;
        case RFUCMD_SEND_HELD_KEYS:
            gLinkPartnersHeldKeys[i] = gRecvCmds[i][1];
            break;
        }
        if (gRfu.parent_child == MODE_PARENT && gRfu.unk_61[i])
        {
            if (gRfu.unk_61[i] == 4)
            {
                gRfu.unk_5c[i] = 1;
                gRfu.unk_61[i] = 0;
            }
            else
                gRfu.unk_61[i]++;
        }
    }
}

static bool8 Cmd8000recvIsFinished(void)
{
    s32 i;

    for (i = 0; i < 5; i++)
    {
        if (gRfu.cmd_8800_recvbuf[i].receiving)
            return FALSE;
    }
    return TRUE;
}

static bool8 sub_80F9C78(void)
{
    s32 i;

    for (i = 0; i < gRfu.playerCount; i++)
    {
        if (gRfu.cmd_8800_recvbuf[i].receiving != 2 || gRfu.unk_5c[i] != 1)
            return FALSE;
    }
    return TRUE;
}

static void ResetSendDataManager(struct RfuBlockSend *data)
{
    data->next = 0;
    data->count = 0;
    data->payload = NULL;
    data->receivedFlags = 0;
    data->sending = 0;
    data->owner = 0;
    data->receiving = 0;
}

u8 Rfu_GetBlockReceivedStatus(void)
{
    u8 flags = 0;
    s32 i;

    for (i = 0; i < 5; i++)
    {
        if (gRfu.cmd_8800_recvbuf[i].receiving == 2 && gRfu.unk_5c[i] == 1)
        {
            flags |= (1 << i);
        }
    }
    return flags;
}

static void RfuPrepareSendBuffer(u16 command)
{
    u8 i;
    u8 *buff;
    u8 tmp;

    gSendCmd[0] = command;
    switch (command)
    {
    case RFUCMD_SEND_BLOCK_INIT:
        gSendCmd[1] = gRfu.cmd_8800_sendbuf.count;
        gSendCmd[2] = gRfu.cmd_8800_sendbuf.owner + 0x80;
        break;
    case RFUCMD_SEND_BLOCK_REQ:
        if (Cmd8000recvIsFinished())
            gSendCmd[1] = gRfu.cmdA100_blockRequestType;
        break;
    case RFUCMD_SEND_PLAYER_IDS:
    case RFUCMD_SEND_PLAYER_IDS_NEW:
        tmp = gRfu.bm_PartnerFlags ^ gRfu.bm_DisconnectSlot;
        gRfu.playerCount = gUnknown_843EC41[tmp] + 1;
        gSendCmd[1] = gRfu.playerCount;
        buff = (u8 *)(gSendCmd + 2);
        for (i = 0; i < RFU_CHILD_MAX; i++)
            buff[i] = gRfu.linkPlayerIdx[i];
        break;
    case RFUCMD_READY_EXIT_STANDBY:
    case RFUCMD_READY_CLOSE_LINK:
        gSendCmd[1] = gRfu.cmd_6600_count;
        break;
    case RFUCMD_SEND_PACKET:
        for (i = 0; i < 6; i++)
            gSendCmd[1 + i] = gRfu.unk_f2[i];
        break;
    case RFUCMD_SEND_HELD_KEYS:
        gSendCmd[1] = gHeldKeyCodeToSend;
        break;
    case RFUCMD_DISCONNECT_PARENT:
        break;
    case RFUCMD_DISCONNECT:
        break;
    }
}

void RfuPrepareSend0x2f00(void * data)
{
    if (gSendCmd[0] == 0 && !RfuIsErrorStatus1or2())
    {
        memcpy(gRfu.unk_f2, data, sizeof(gRfu.unk_f2));
        RfuPrepareSendBuffer(RFUCMD_SEND_PACKET);
    }
}

bool32 Rfu_InitBlockSend(const u8 *src, size_t size)
{
    bool8 r4;
    AGB_ASSERT_EX(size<=252, ABSPATH("gRfu.c"), 1793);
    if (gRfu.RfuFunc != NULL)
        return FALSE;
    if (gSendCmd[0] != 0)
        return FALSE;
    if (gRfu.cmd_8800_sendbuf.sending != 0)
    {
        gUnknown_203AC08.unk_83++;
        return FALSE;
    }
    r4 = (size % 12) != 0;
    gRfu.cmd_8800_sendbuf.owner = GetMultiplayerId();
    gRfu.cmd_8800_sendbuf.sending = 1;
    gRfu.cmd_8800_sendbuf.count = (size / 12) + r4;
    gRfu.cmd_8800_sendbuf.next = 0;
    if (size > 0x100) // should never be reached
        gRfu.cmd_8800_sendbuf.payload = src;
    else
    {
        if (src != gBlockSendBuffer)
            memcpy(gBlockSendBuffer, src, size);
        gRfu.cmd_8800_sendbuf.payload = gBlockSendBuffer;
    }
    RfuPrepareSendBuffer(RFUCMD_SEND_BLOCK_INIT);
    gRfu.RfuFunc = RfuFunc_HandleBlockSend;
    gRfu.unk_5b = 0;
    return TRUE;
}

static void RfuFunc_HandleBlockSend(void)
{
    if (gSendCmd[0] == 0)
    {
        RfuPrepareSendBuffer(RFUCMD_SEND_BLOCK_INIT);
        if (gRfu.parent_child == MODE_PARENT)
        {
            if (++gRfu.unk_5b > 2)
                gRfu.RfuFunc = RfuFunc_SendNextBlock;
        }
        else
        {
            if ((gRecvCmds[GetMultiplayerId()][0] & 0xff00) == RFUCMD_SEND_BLOCK_INIT)
                gRfu.RfuFunc = RfuFunc_SendNextBlock;
        }
    }
}
static void RfuFunc_SendNextBlock(void)
{
    s32 i;
    const u8 *src = gRfu.cmd_8800_sendbuf.payload;
    gSendCmd[0] = RFUCMD_SEND_BLOCK | gRfu.cmd_8800_sendbuf.next;
    for (i = 0; i < 7; i++)
        gSendCmd[i + 1] = (src[(i << 1) + gRfu.cmd_8800_sendbuf.next * 12 + 1] << 8) | src[(i << 1) + gRfu.cmd_8800_sendbuf.next * 12 + 0];
    gRfu.cmd_8800_sendbuf.next++;
    if (gRfu.cmd_8800_sendbuf.count <= gRfu.cmd_8800_sendbuf.next)
    {
        gRfu.cmd_8800_sendbuf.sending = 0;
        gRfu.RfuFunc = RfuFunc_SendLastBlock;
    }
}

static void RfuFunc_SendLastBlock(void)
{
    const u8 *src = gRfu.cmd_8800_sendbuf.payload;
    u8 mpId = GetMultiplayerId();
    s32 i;
    if (gRfu.parent_child == MODE_CHILD)
    {
        gSendCmd[0] = RFUCMD_SEND_BLOCK | (gRfu.cmd_8800_sendbuf.count - 1);
        for (i = 0; i < 7; i++)
            gSendCmd[i + 1] = (src[(i << 1) + (gRfu.cmd_8800_sendbuf.count - 1) * 12 + 1] << 8) | src[(i << 1) + (gRfu.cmd_8800_sendbuf.count - 1) * 12 + 0];
        if ((u8)gRecvCmds[mpId][0] == gRfu.cmd_8800_sendbuf.count - 1)
        {
            if (gRfu.cmd_8800_recvbuf[mpId].receivedFlags != sAllBlocksReceived[gRfu.cmd_8800_recvbuf[mpId].count])
            {
                HandleSendFailure(mpId, gRfu.cmd_8800_recvbuf[mpId].receivedFlags);
                gUnknown_203AC08.unk_64++;
            }
            else
                gRfu.RfuFunc = NULL;
        }
    }
    else
        gRfu.RfuFunc = NULL;
}

bool8 LinkRfu_PrepareCmd0xA100(u8 blockRequestType)
{
    gRfu.cmdA100_blockRequestType = blockRequestType;
    RfuPrepareSendBuffer(RFUCMD_SEND_BLOCK_REQ);
    return TRUE;
}

static void RfuFunc_End5F00_PowerDownRfu(void)
{
    rfu_clearAllSlot();
    rfu_LMAN_powerDownRFU();
    gReceivedRemoteLinkPlayers = FALSE;
    gRfu.isShuttingDown = TRUE;
    gRfu.RfuFunc = NULL;
}

static void RfuFunc_End5F00_ParentDisconnect(void)
{
    rfu_REQ_disconnect(gRfuLinkStatus->connSlotFlag | gRfuLinkStatus->linkLossSlotFlag);
    rfu_waitREQComplete();
    RfuFunc_End5F00_PowerDownRfu();
}

static void RfuFunc_End5F00(void)
{
    if (gRfu.parent_child == MODE_CHILD)
    {
        rfu_LMAN_requestChangeAgbClockMaster();
        gRfu.unk_ce4 = 2;
    }
    else
        gRfu.RfuFunc = RfuFunc_End5F00_ParentDisconnect;
}

void LinkRfu_FatalError(void)
{
    rfu_LMAN_requestChangeAgbClockMaster();
    gRfu.unk_ce4 = 1;
    gRfu.bm_DisconnectSlot = gRfuLinkStatus->connSlotFlag | gRfuLinkStatus->linkLossSlotFlag;
}

static void RfuFunc_WaitAck5F00(void)
{
    s32 i;
    u8 playerCount = gRfu.playerCount;
    s32 count = 0;

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        if (gRfu.cmd5f00Ack[i])
            count++;
    }
    if (count == playerCount)
    {
        gBattleTypeFlags &= ~(BATTLE_TYPE_20 | 0xFFFF0000);
        if (gRfu.parent_child == MODE_CHILD)
        {
            gRfu.errorState = 3;
            RfuFunc_End5F00();
        }
        else
            gRfu.RfuFunc = RfuFunc_End5F00;
    }
}

static void RfuFunc_BuildCommand5F00(void)
{
    if (gSendCmd[0] == 0 && !gRfu.unk_ce8)
    {
        RfuPrepareSendBuffer(RFUCMD_READY_CLOSE_LINK);
        gRfu.RfuFunc = RfuFunc_WaitAck5F00;
    }
}

static void Task_WaitRfuFuncAndSetBuildCmd5F00(u8 taskId)
{
    if (gRfu.RfuFunc == NULL)
    {
        gRfu.unk_cd9 = 1;
        gRfu.RfuFunc = RfuFunc_BuildCommand5F00;
        DestroyTask(taskId);
    }
}

void Rfu_BeginBuildAndSendCommand5F(void)
{
    if (!FuncIsActiveTask(Task_WaitRfuFuncAndSetBuildCmd5F00))
        CreateTask(Task_WaitRfuFuncAndSetBuildCmd5F00, 5);
}

static void RfuFunc_Send6600_3(void)
{
    u8 playerCount;
    u8 i;

    if (GetMultiplayerId() != 0) // child
    {
        if (gRfu.unk_124.count == 0 && gRfu.cmd_6600_timer > 60)
        {
            RfuPrepareSendBuffer(RFUCMD_READY_EXIT_STANDBY);
            gRfu.cmd_6600_timer = 0;
        }
    }
    playerCount = GetLinkPlayerCount();
    for (i = 0; i < playerCount; i++)
    {
        if (gRfu.cmd_6600_recvd[i] == 0)
            break;
    }
    if (i == playerCount)
    {
        for (i = 0; i < MAX_RFU_PLAYERS; i++)
            gRfu.cmd_6600_recvd[i] = 0;
        gRfu.cmd_6600_count++;
        gRfu.RfuFunc = NULL;
    }
    gRfu.cmd_6600_timer++;
}

static void RfuFunc_Send6600_2(void)
{
    if (gRfu.unk_124.count == 0 && gSendCmd[0] == 0)
    {
        RfuPrepareSendBuffer(RFUCMD_READY_EXIT_STANDBY);
        gRfu.RfuFunc = RfuFunc_Send6600_3;
    }
}

static void RfuFunc_Send6600_1(void)
{
    u8 i;
    u8 playerCount;

    if (GetMultiplayerId() != 0) // child
    {
        if (gRfu.unk_124.count == 0 && gSendCmd[0] == 0)
        {
            RfuPrepareSendBuffer(RFUCMD_READY_EXIT_STANDBY);
            gRfu.RfuFunc = RfuFunc_Send6600_3;
        }
    }
    else // parent
    {
        playerCount = GetLinkPlayerCount();
        for (i = 1; i < playerCount; i++)
        {
            if (gRfu.cmd_6600_recvd[i] == 0)
                break;
        }
        if (i == playerCount)
        {
            if (gRfu.unk_124.count == 0 && gSendCmd[0] == 0)
            {
                RfuPrepareSendBuffer(RFUCMD_READY_EXIT_STANDBY);
                gRfu.RfuFunc = RfuFunc_Send6600_2;
            }
        }
    }
}

void LinkRfu_SetRfuFuncToSend6600(void)
{
    if (gRfu.RfuFunc == NULL)
    {
        gRfu.RfuFunc = RfuFunc_Send6600_1;
        gRfu.cmd_6600_timer = 0;
    }
}

bool32 RfuSerialNumberIsValid(u32 serialNo)
{
    s32 i;
    for (i = 0; sAcceptedSerialNos[i] != serialNo; i++)
    {
        if (sAcceptedSerialNos[i] == 0xFFFF)
            return FALSE;
    }
    return TRUE;
}

u8 ToggleLMANlinkRecovery(bool32 a0)
{
    if (!a0)
        return rfu_LMAN_setLinkRecovery(0, 0);
    rfu_LMAN_setLinkRecovery(1, 600);
    return 0;
}

void sub_80FA4A8(void)
{
    gRfu.unk_cd9 = 1;
    rfu_LMAN_stopManager(0);
}

u8 LinkRfu_GetMultiplayerId(void)
{
    if (gRfu.parent_child == MODE_PARENT)
        return 0;
    return gRfu.unk_cce;
}

u8 GetRfuPlayerCount(void)
{
    return gRfu.playerCount;
}

bool8 IsLinkRfuTaskFinished(void)
{
    return gRfu.RfuFunc != NULL ? FALSE : TRUE;
}

static void CallRfuFunc(void)
{
    if (gRfu.RfuFunc != NULL)
        gRfu.RfuFunc();
}

static bool8 sub_80FA528(void)
{
    s32 i;
    bool8 retval = FALSE;
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if (gRfu.unk_cd1[i] < 5 || gRfu.unk_cd1[i] > 6)
        {
            if (gRfuSlotStatusNI[i]->recv.state == SLOT_STATE_RECV_SUCCESS || gRfuSlotStatusNI[i]->recv.state == SLOT_STATE_RECV_SUCCESS_AND_SENDSIDE_UNKNOWN)
            {
                if (gRfu.unk_cd5[i] == 8)
                {
                    gRfu.unk_cd1[i] = 9;
                    gRfu.unk_cd5[i] = 10;
                    rfu_clearSlot(TYPE_NI_RECV, i);
                    rfu_NI_setSendData(1 << i, 8, gRfu.unk_cd1 + i, 1);
                    retval = TRUE;
                }

            }
            else if (gRfuSlotStatusNI[gRfu.child_slot]->recv.state == SLOT_STATE_RECV_FAILED)
            {
                rfu_clearSlot(TYPE_NI_RECV, i);
            }
        }
    }
    return retval;
}

bool32 sub_80FA5D4(void)
{
    u8 flags = 0;
    s32 i;
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if (gRfu.unk_cd5[i] == 11)
        {
            flags |= (1 << i);
            gRfu.unk_cd5[i] = 0;
        }
    }
    if (flags)
    {
        rfu_REQ_disconnect(flags);
        rfu_waitREQComplete();
    }
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if (gRfu.unk_cd5[i] == 10 || gRfu.unk_cd5[i] == 11)
            return TRUE;
    }
    return FALSE;
}

bool32 TrainerIdAndNameStillInPartnersList(u16 trainerId, const u8 *trainerName)
{
    u8 r1 = GetPartnerIndexByNameAndTrainerID(trainerName, trainerId);
    if (r1 == 0xFF)
        return TRUE;
    if (gRfu.unk_cd1[r1] == 9)
        return TRUE;
    return FALSE;
}

void SendByteToPartnerByIdAndName(u8 value, u16 trainerId, const u8 *trainerName)
{
    u8 slotNo = GetPartnerIndexByNameAndTrainerID(trainerName, trainerId);
    gRfu.unk_cd1[slotNo] = value;
    rfu_clearSlot(TYPE_NI_SEND, slotNo);
    rfu_NI_setSendData(1 << slotNo, 8, gRfu.unk_cd1 + slotNo, 1);
}

void LinkRfuNIsend8(void)
{
    gRfu.unk_c85 = 8;
    rfu_clearSlot(TYPE_NI_SEND, gRfu.child_slot);
    rfu_NI_setSendData(1 << gRfu.child_slot, 8, &gRfu.unk_c85, 1);
}

u32 WaitSendByteToPartnerByIdAndName(u16 trainerId, const u8 *trainerName)
{
    u8 r0 = GetPartnerIndexByNameAndTrainerID(trainerName, trainerId);
    if (r0 == 0xFF)
        return 2;
    if (gRfuSlotStatusNI[r0]->send.state == SLOT_STATE_READY)
        return 1;
    return 0;
}

static void sub_80FA738(void)
{
    s32 i;

    sub_80FA528();
    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if (gRfuSlotStatusNI[i]->send.state == SLOT_STATE_SEND_SUCCESS || gRfuSlotStatusNI[i]->send.state == SLOT_STATE_SEND_FAILED)
        {
            if (gRfu.unk_cd5[i] == 10)
                gRfu.unk_cd5[i] = 11;
            rfu_clearSlot(TYPE_NI_SEND, i);
        }
    }
}

static s32 sub_80FA788(void)
{
    s32 retval = 0;
    if (gRfu.unk_c85 == 8)
    {
        if (gRfuSlotStatusNI[gRfu.child_slot]->send.state == SLOT_STATE_SEND_SUCCESS || gRfuSlotStatusNI[gRfu.child_slot]->send.state == SLOT_STATE_SEND_FAILED)
            rfu_clearSlot(TYPE_NI_SEND, gRfu.child_slot);
    }
    if (gRfuSlotStatusNI[gRfu.child_slot]->recv.state == SLOT_STATE_RECV_SUCCESS || gRfuSlotStatusNI[gRfu.child_slot]->recv.state == SLOT_STATE_RECV_SUCCESS_AND_SENDSIDE_UNKNOWN)
    {
        rfu_clearSlot(TYPE_NI_RECV, gRfu.child_slot);
        RfuSetErrorStatus(gRfu.unk_c86, 0);
        retval = gRfu.unk_c86;
    }
    else if (gRfuSlotStatusNI[gRfu.child_slot]->recv.state == SLOT_STATE_RECV_FAILED)
    {
        rfu_clearSlot(TYPE_NI_RECV, gRfu.child_slot);
        retval = 6;
    }
    return retval;
}

static void sub_80FA834(u8 taskId)
{
    s32 i;

    if (gRfu.unk_f1 == 1 || gRfu.unk_f1 == 2)
    {
        gRfu.unk_ce8 = FALSE;
        DestroyTask(taskId);
    }
    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (Cmd8000recvIsFinished())
        {
            ResetBlockReceivedFlags();
            PrepareLocalLinkPlayerBlock();
            gTasks[taskId].data[0]++;
        }
        break;
    case 1:
        if (gRfu.parent_child == MODE_PARENT)
        {
            if (gReceivedRemoteLinkPlayers)
                RfuPrepareSendBuffer(RFUCMD_SEND_PLAYER_IDS_NEW);
            else
                RfuPrepareSendBuffer(RFUCMD_SEND_PLAYER_IDS);
            gTasks[taskId].data[0] = 101;
        }
        else
            gTasks[taskId].data[0] = 2;
        break;
    case 101:
        if (gSendCmd[0] == 0)
            gTasks[taskId].data[0] = 2;
        break;
    case 2:
        if (gRfu.playerCount)
            gTasks[taskId].data[0]++;
        break;
    case 3:
        if (gRfu.parent_child == MODE_PARENT)
        {
            if (Cmd8000recvIsFinished())
            {
                gRfu.cmdA100_blockRequestType = 0;
                RfuPrepareSendBuffer(RFUCMD_SEND_BLOCK_REQ);
                gTasks[taskId].data[0]++;
            }
        }
        else
            gTasks[taskId].data[0]++;
        break;
    case 4:
        if (sub_80F9C78())
            gTasks[taskId].data[0]++;
        break;
    case 5:
        for (i = 0; i < gRfu.playerCount; i++)
        {
            LinkPlayerFromBlock(i);
            Rfu_ResetBlockReceivedFlag(i);
        }
        gTasks[taskId].data[0]++;
        break;
    case 6:
        DestroyTask(taskId);
        gReceivedRemoteLinkPlayers = TRUE;
        gRfu.unk_ce8 = FALSE;
        rfu_LMAN_setLinkRecovery(1, 600);
        if (gRfu.unionRoomChatters)
        {
            for (i = 0; i < RFU_CHILD_MAX; i++)
            {
                if ((gRfu.unionRoomChatters >> i) & 1)
                {
                    gRfu.unk_ce5 = 1 << i;
                    gRfu.unionRoomChatters ^= (1 << i);
                }
            }
        }
        break;
    }
}

static void sub_80FA9D0(u16 a0)
{
    s32 i;

    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if ((a0 >> i) & 1)
            gRfu.linkPlayerIdx[i] = 0;
    }
}

static void ReceiveRfuLinkPlayers(const struct SioInfo *chunk)
{
    s32 i;
    gRfu.playerCount = chunk->playerCount;
    for (i = 0; i < RFU_CHILD_MAX; i++)
        gRfu.linkPlayerIdx[i] = chunk->linkPlayerIdx[i];
    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        gLinkPlayers[i] = chunk->linkPlayers[i];
        IntlConvertLinkPlayerName(gLinkPlayers + i);
    }
}

// Could be relocated to top of file, but would also require relocating assert strings
static const char sASCII_PokemonSioInfo[] = "PokemonSioInfo";
ALIGNED(4) static const u8 sText_Akito[] = _("あきと"); // Presumably "Akito Mori", one of Game Freak's programmers
static const char sASCII_LinkLossDisconnect[] = "LINK LOSS DISCONNECT!";
static const char sASCII_LinkLossRecoveryNow[] = "LINK LOSS RECOVERY NOW";
ALIGNED(4) static const char sASCII_30Spaces[] = {"                              "};
static const char sASCII_15Spaces[] = {"               "};
static const char sASCII_8Spaces[] = {"        "};
ALIGNED(4) static const char sASCII_Space[] = {" "};
static const char sASCII_Asterisk[] = {"*"};
static const char sASCII_NowSlot[] = "NOWSLOT";

static const char sASCII_ClockCmds[][12] = {
    "           ",
    "CLOCK DRIFT",
    "BUSY SEND  ",
    "CMD REJECT ",
    "CLOCK SLAVE"
};

static const char sASCII_ChildParentSearch[][8] = {
    "CHILD ",
    "PARENT",
    "SEARCH"
};

static void ValidateAndReceivePokemonSioInfo(void *recvBuffer)
{
    if (strcmp("PokemonSioInfo", recvBuffer) == 0)
    {
        ReceiveRfuLinkPlayers(recvBuffer);
        CpuFill16(0, recvBuffer, sizeof(struct SioInfo));
        ResetBlockReceivedFlag(0);
    }
}

static void Task_ExchangeLinkPlayers(u8 taskId)
{
    s32 i;
    struct LinkPlayerBlock *r2;
    struct SioInfo *r5;
    u8 r4 = gRfu.linkPlayerIdx[gUnknown_843EC38[gRfu.unk_ce9]];
    if (gRfu.unk_f1 == 1 || gRfu.unk_f1 == 2)
    {
        gRfu.unk_ce8 = FALSE;
        DestroyTask(taskId);
    }
    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (gSendCmd[0] == 0)
        {
            ResetBlockReceivedFlag(r4);
            RfuPrepareSendBuffer(RFUCMD_SEND_PLAYER_IDS_NEW);
            gTasks[taskId].data[0]++;
        }
        break;
    case 1:
        if (gSendCmd[0] == 0)
            gTasks[taskId].data[0]++;
        break;
    case 2:
        if ((GetBlockReceivedStatus() >> r4) & 1)
        {
            ResetBlockReceivedFlag(r4);
            r2 = (struct LinkPlayerBlock *)gBlockRecvBuffer[r4];
            gLinkPlayers[r4] = r2->linkPlayer;
            IntlConvertLinkPlayerName(gLinkPlayers + r4);
            gTasks[taskId].data[0]++;
        }
        break;
    case 3:
        // Prepare send block
        r5 = (struct SioInfo *)gBlockSendBuffer;
        memcpy(r5->magic, "PokemonSioInfo", sizeof("PokemonSioInfo"));
        r5->playerCount = gRfu.playerCount;
        for (i = 0; i < RFU_CHILD_MAX; i++)
            r5->linkPlayerIdx[i] = gRfu.linkPlayerIdx[i];
        memcpy(r5->linkPlayers, gLinkPlayers, sizeof gLinkPlayers);
        gTasks[taskId].data[0]++;
        // fallthrough
    case 4:
        r5 = (struct SioInfo *)gBlockSendBuffer;
        r5->playerCount = gRfu.playerCount;
        for (i = 0; i < RFU_CHILD_MAX; i++)
            r5->linkPlayerIdx[i] = gRfu.linkPlayerIdx[i];
        memcpy(r5->linkPlayers, gLinkPlayers, sizeof gLinkPlayers);
        if (SendBlock(0, gBlockSendBuffer, 0xa0))
            gTasks[taskId].data[0]++;
        break;
    case 5:
        if (IsLinkTaskFinished() && GetBlockReceivedStatus() & 1)
        {
            CpuFill16(0, gBlockRecvBuffer, sizeof(struct SioInfo));
            ResetBlockReceivedFlag(0);
            gRfu.unk_ce8 = FALSE;
            if (gRfu.unionRoomChatters)
            {
                for (i = 0; i < RFU_CHILD_MAX; i++)
                {
                    if ((gRfu.unionRoomChatters >> i) & 1)
                    {
                        gRfu.unk_ce5 = 1 << i;
                        gRfu.unionRoomChatters ^= (1 << i);
                        gRfu.unk_ce8 = TRUE;
                        break;
                    }
                }
            }
            DestroyTask(taskId);
        }
        break;
    }
}

static void sub_80FACF0(u8 taskId)
{
    if (gRfu.unk_f1 == 1 || gRfu.unk_f1 == 2)
        DestroyTask(taskId);
    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (gRfu.playerCount)
        {
            PrepareLocalLinkPlayerBlock();
            SendBlock(0, gBlockSendBuffer, sizeof(struct LinkPlayerBlock));
            gTasks[taskId].data[0]++;
        }
        break;
    case 1:
        if (IsLinkTaskFinished())
            gTasks[taskId].data[0]++;
        break;
    case 2:
        if (GetBlockReceivedStatus() & 1)
        {
            ReceiveRfuLinkPlayers((const struct SioInfo *)gBlockRecvBuffer);
            ResetBlockReceivedFlag(0);
            gReceivedRemoteLinkPlayers = TRUE;
            DestroyTask(taskId);
        }
        break;
    }
}

static void RfuCheckErrorStatus(void)
{
    if (gRfu.errorState == 1 && lman.childClockSlave_flag == 0)
    {
        if (gMain.callback2 == c2_mystery_gift_e_reader_run)
            gWirelessCommType = 2;
        SetMainCallback2(CB2_LinkError);
        gMain.savedCallback = CB2_LinkError;
        SetLinkErrorFromRfu((gRfu.linkman_msg << 16) | (gRfu.linkman_param[0] << 8) | gRfu.linkman_param[1], gRfu.unk_124.count, gRfu.sendQueue.count, RfuGetErrorStatus() == 2);
        gRfu.errorState = 2;
        CloseLink();
    }
    else if (gRfu.sendQueue.full == 1 || gRfu.unk_124.full == 1)
    {
        if (lman.childClockSlave_flag)
            rfu_LMAN_requestChangeAgbClockMaster();
        RfuSetErrorStatus(1, 0x7000);
        GetLinkmanErrorParams(0x7000);
    }
}

static void rfu_REQ_recvData_then_sendData(void)
{
    if (lman.parent_child == MODE_PARENT)
    {
        rfu_REQ_recvData();
        rfu_waitREQComplete();
        rfu_LMAN_REQ_sendData(RFU_CHILD_CLOCK_SLAVE_OFF);
    }
}

bool32 LinkRfuMain1(void)
{
    bool32 retval = FALSE;
    gRfu.parentId = 0;
    rfu_LMAN_manager_entity(Random());
    if (!gRfu.isShuttingDown)
    {
        switch (gRfu.parent_child)
        {
        case 1:
            sub_80F911C();
            break;
        case 0:
            retval = RfuProcessEnqueuedRecvBlock();
            break;
        case 2:
            rfu_REQ_recvData_then_sendData();
            break;
        }
    }
    return retval;
}

bool32 LinkRfuMain2(void)
{
    bool32 retval = FALSE;
    if (!gRfu.isShuttingDown)
    {
        if (gRfu.parent_child == MODE_PARENT)
            retval = sub_80F9204();
        RfuCheckErrorStatus();
    }
    return retval;
}

static void CopyPlayerNameToUnameBuffer(void)
{
    StringCopy(gHostRfuUsername, gSaveBlock2Ptr->playerName);
}

void ClearAndInitHostRFUtgtGname(void)
{
    memset(&gHostRfuGameData, 0, RFU_GAME_NAME_LENGTH);
    InitHostRFUtgtGname(&gHostRfuGameData, 0, FALSE, 0);
}

void SetHostRFUtgtGname(u8 activity, u32 child_sprite_genders, u32 started)
{
    InitHostRFUtgtGname(&gHostRfuGameData, activity, started, child_sprite_genders);
}

void SetGnameBufferWonderFlags(bool32 hasNews, bool32 hasCard)
{
    gHostRfuGameData.unk_00.hasNews = hasNews;
    gHostRfuGameData.unk_00.hasCard = hasCard;
}

void RfuUpdatePlayerGnameStateAndSend(u32 type, u32 species, u32 level)
{
    gHostRfuGameData.tradeType = type;
    gHostRfuGameData.tradeSpecies = species;
    gHostRfuGameData.level = level;
}

void UpdateGameData_GroupLockedIn(bool8 started)
{
    gHostRfuGameData.started = started;
    rfu_REQ_configGameData(0, 0x0002, (void *)&gHostRfuGameData, gHostRfuUsername);
}

void UpdateGameDataWithActivitySpriteGendersFlag(u8 activity, u32 child_sprite_genders, u32 started)
{
    if (activity)
        SetHostRFUtgtGname(activity, child_sprite_genders, started);
    rfu_REQ_configGameData(0, 0x0002, (void *)&gHostRfuGameData, gHostRfuUsername);
}

void sub_80FB030(u32 linkPlayerCount)
{
    s32 i;
    u32 numConnectedChildren;
    u32 child_sprite_genders;
    s32 bm_child_slots;

    if (GetHostRFUtgtGname()->activity == (ACTIVITY_CHAT | IN_UNION_ROOM))
    {
        numConnectedChildren = 0;
        child_sprite_genders = 0;
        bm_child_slots = gRfu.bm_PartnerFlags ^ gRfu.bm_DisconnectSlot;
        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            if ((bm_child_slots >> i) & 1)
            {
                // The 0x80 prevents this element from being incorrectly read as a 0.
                child_sprite_genders |= ((
                    0x80 | ((gLinkPlayers[gRfu.linkPlayerIdx[i]].gender & 1) << 3) | (gLinkPlayers[gRfu.linkPlayerIdx[i]].trainerId & 7)
                ) << (numConnectedChildren << 3));
                numConnectedChildren++;
                if (numConnectedChildren == linkPlayerCount - 1)
                    break;
            }
        }
        UpdateGameDataWithActivitySpriteGendersFlag(ACTIVITY_CHAT | IN_UNION_ROOM, child_sprite_genders, 0);
    }
}

static void GetLinkmanErrorParams(u32 msg)
{
    if (gRfu.errorState == 0)
    {
        gRfu.linkman_param[0] = lman.param[0];
        gRfu.linkman_param[1] = lman.param[1];
        gRfu.linkman_msg = msg;
        gRfu.errorState = 1;
    }
}

static void ResetErrorState(void)
{
    gRfu.errorState = 0;
}

void sub_80FB128(bool32 a0)
{
    if (!a0)
        gRfu.errorState = 0;
    else
        gRfu.errorState = 4;
}

static void sub_80FB154(void)
{
    sub_80FBE20(lman.acceptSlot_flag, 1);
    gRfu.RfuFunc = NULL;
}

static void sub_80FB174(void)
{
    gRfu.RfuFunc = sub_80FB154;
}

static void LmanCallback_Parent2(u8 msg, u8 param_count)
{
    u8 i;
    u8 bmDisconnectFlag = 0;
    switch (msg)
    {
    case LMAN_MSG_INITIALIZE_COMPLETED:
        gRfu.state = 2;
        break;
    case LMAN_MSG_NEW_CHILD_CONNECT_DETECTED:
        break;
    case LMAN_MSG_NEW_CHILD_CONNECT_ACCEPTED:
        sub_80FB564(lman.param[0]);
        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            if ((lman.param[0] >> i) & 1)
            {
                struct RfuGameData *structPtr = (void *)&gRfuLinkStatus->partner[i].gname;
                if (structPtr->activity == GetHostRFUtgtGname()->activity)
                {
                    gRfu.unk_cd1[i] = 0;
                    gRfu.unk_cd5[i] = 0;
                    rfu_setRecvBuffer(TYPE_NI, i, gRfu.unk_cd5 + i, 1);
                }
                else
                {
                    bmDisconnectFlag |= (1 << i);
                }
            }
        }
        if (bmDisconnectFlag)
        {
            rfu_REQ_disconnect(bmDisconnectFlag);
            rfu_waitREQComplete();
        }
        break;
    case LMAN_MSG_NEW_CHILD_CONNECT_REJECTED:
        break;
    case LMAN_MSG_SEARCH_CHILD_PERIOD_EXPIRED:
        break;
    case LMAN_MSG_END_WAIT_CHILD_NAME:
        if (gRfu.acceptSlot_flag != lman.acceptSlot_flag)
        {
            rfu_REQ_disconnect(gRfu.acceptSlot_flag ^ lman.acceptSlot_flag);
            rfu_waitREQComplete();
        }
        gRfu.state = 17;
        break;
    case LMAN_MSG_LINK_LOSS_DETECTED_AND_START_RECOVERY:
        gRfu.linkLossRecoveryState = 1;
        break;
    case LMAN_MSG_LINK_RECOVERY_SUCCESSED:
        gRfu.linkLossRecoveryState = 3;
        break;
    case LMAN_MSG_LINK_LOSS_DETECTED_AND_DISCONNECTED:
    case LMAN_MSG_LINK_RECOVERY_FAILED_AND_DISCONNECTED:
        gRfu.linkLossRecoveryState = 4;
        gRfu.bm_PartnerFlags &= ~lman.param[0];
        if (gReceivedRemoteLinkPlayers == 1)
        {
            if (gRfu.bm_PartnerFlags == 0)
                GetLinkmanErrorParams(msg);
            else
                sub_80FB174();
        }
        RfuSetErrorStatus(2, msg);
        break;
    case 0x34:
        break;
    case LMAN_MSG_RFU_POWER_DOWN:
    case LMAN_MSG_MANAGER_STOPPED:
    case LMAN_MSG_MANAGER_FORCED_STOPPED_AND_RFU_RESET:
        break;
    case LMAN_MSG_LMAN_API_ERROR_RETURN:
        RfuSetErrorStatus(1, msg);
        GetLinkmanErrorParams(msg);
        gRfu.isShuttingDown = TRUE;
        break;
    case LMAN_MSG_REQ_API_ERROR:
    case LMAN_MSG_WATCH_DOG_TIMER_ERROR:
    case LMAN_MSG_CLOCK_SLAVE_MS_CHANGE_ERROR_BY_DMA:
    case LMAN_MSG_RFU_FATAL_ERROR:
        GetLinkmanErrorParams(msg);
        RfuSetErrorStatus(1, msg);
        gRfu.unk_cdb = 1;
        break;
    }
}

static const u8 unref_843EDF3[] = _("　あきと");

static void LmanCallback_Child(u8 msg, u8 param_count)
{
    switch (msg)
    {
    case LMAN_MSG_INITIALIZE_COMPLETED:
        gRfu.state = 6;
        break;
    case LMAN_MSG_PARENT_FOUND:
        gRfu.parentId = lman.param[0];
        break;
    case LMAN_MSG_SEARCH_PARENT_PERIOD_EXPIRED:
        break;
    case LMAN_MSG_CONNECT_PARENT_SUCCESSED:
        gRfu.child_slot = lman.param[0];
        break;
    case LMAN_MSG_CONNECT_PARENT_FAILED:
        RfuSetErrorStatus(2, msg);
        break;
    case LMAN_MSG_CHILD_NAME_SEND_COMPLETED:
        gRfu.state = 11;
        gRfu.unk_c85 = 0;
        gRfu.unk_c86 = 0;
        rfu_setRecvBuffer(TYPE_NI, gRfu.child_slot, &gRfu.unk_c86, 1);
        rfu_setRecvBuffer(TYPE_UNI, gRfu.child_slot, gRfu.unk_c3f, sizeof(gRfu.unk_c3f));
        break;
    case LMAN_MSG_CHILD_NAME_SEND_FAILED_AND_DISCONNECTED:
        RfuSetErrorStatus(2, msg);
        break;
    case LMAN_MSG_LINK_LOSS_DETECTED_AND_DISCONNECTED:
        gRfu.linkLossRecoveryState = 2;
        if (gRfu.unk_c86 == 6)
            break;
    case LMAN_MSG_LINK_RECOVERY_FAILED_AND_DISCONNECTED:
        if (gRfu.linkLossRecoveryState != 2)
            gRfu.linkLossRecoveryState = 4;
        if (gRfu.unk_c86 != 9)
            RfuSetErrorStatus(2, msg);
        rfu_dbg_print_str("LINK LOSS DISCONNECT!", 5, 5);
        if (gReceivedRemoteLinkPlayers == 1)
            GetLinkmanErrorParams(msg);
        break;
    case LMAN_MSG_LINK_LOSS_DETECTED_AND_START_RECOVERY:
        gRfu.linkLossRecoveryState = 1;
        rfu_dbg_print_str("LINK LOSS RECOVERY NOW", 5, 5);
        break;
    case LMAN_MSG_LINK_RECOVERY_SUCCESSED:
        gRfu.linkLossRecoveryState = 3;
        gRfu.unk_c3c = 1;
        break;
    case 0x34:
        break;
    case LMAN_MSG_RFU_POWER_DOWN:
    case LMAN_MSG_MANAGER_STOPPED:
    case LMAN_MSG_MANAGER_FORCED_STOPPED_AND_RFU_RESET:
        break;
    case LMAN_MSG_LMAN_API_ERROR_RETURN:
        RfuSetErrorStatus(1, msg);
        GetLinkmanErrorParams(msg);
        gRfu.isShuttingDown = TRUE;
        break;
    case LMAN_MSG_REQ_API_ERROR:
    case LMAN_MSG_WATCH_DOG_TIMER_ERROR:
    case LMAN_MSG_CLOCK_SLAVE_MS_CHANGE_ERROR_BY_DMA:
    case LMAN_MSG_RFU_FATAL_ERROR:
        RfuSetErrorStatus(1, msg);
        GetLinkmanErrorParams(msg);
        gRfu.unk_cdb = 1;
        break;
    }
}

static void sub_80FB564(s32 bmConnectedFlag)
{
    s32 i;

    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if ((bmConnectedFlag >> i) & 1)
        {
            gRfu.unk_cea[i] = 0;
            gRfu.unk_cee[i] = 0xFF;
        }
    }
}

static u8 GetNewChildrenInUnionRoomChat(s32 bmNewChildSlot)
{
    u8 ret = 0;
    u8 i;

    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if ((bmNewChildSlot >> i) & 1)
        {
            struct RfuGameData *structPtr = (void *)&gRfuLinkStatus->partner[i].gname;
            if (structPtr->activity == (ACTIVITY_CHAT | IN_UNION_ROOM))
                ret |= (1 << i);
        }
    }

    return ret;
}

static void LmanCallback_Parent(u8 msg, u8 param_count)
{
    u8 r1;

    switch (msg)
    {
    case LMAN_MSG_INITIALIZE_COMPLETED:
        gRfu.state = 17;
        break;
    case LMAN_MSG_NEW_CHILD_CONNECT_DETECTED:
        RfuSetErrorStatus(4, 0);
        break;
    case LMAN_MSG_NEW_CHILD_CONNECT_ACCEPTED:
        if (GetHostRFUtgtGname()->activity == (ACTIVITY_CHAT | IN_UNION_ROOM) && gRfu.unk_cd9 == 0)
        {
            u8 bmAcceptSlot = GetNewChildrenInUnionRoomChat(lman.param[0]);
            if (bmAcceptSlot != 0)
            {
                r1 = 1 << sub_80F886C(bmAcceptSlot);
                if (gRfu.unionRoomChatters == 0 && !gRfu.unk_ce8)
                {
                    gRfu.unk_ce5 = r1;
                    gRfu.unionRoomChatters |= (r1 ^ bmAcceptSlot);
                    gRfu.unk_ce8 = TRUE;
                }
                else
                {
                    gRfu.unionRoomChatters |= bmAcceptSlot;
                }
            }
            if (bmAcceptSlot != lman.param[0])
            {
                gRfu.bm_DisconnectSlot |= (bmAcceptSlot ^ lman.param[0]);
                gRfu.unk_ce4 = 2;
            }
        }
        else if (GetHostRFUtgtGname()->activity == (ACTIVITY_PLYRTALK | IN_UNION_ROOM))
        {
            rfu_REQ_disconnect(lman.acceptSlot_flag);
            rfu_waitREQComplete();
        }
        sub_80FB564(lman.param[0]);
        break;
    case LMAN_MSG_NEW_CHILD_CONNECT_REJECTED:
        break;
    case LMAN_MSG_SEARCH_CHILD_PERIOD_EXPIRED:
        break;
    case LMAN_MSG_END_WAIT_CHILD_NAME:
        if (GetHostRFUtgtGname()->activity != (ACTIVITY_CHAT | IN_UNION_ROOM) && lman.acceptCount > 1)
        {
            r1 = 1 << sub_80F886C(lman.param[0]);
            rfu_REQ_disconnect(lman.acceptSlot_flag ^ r1);
            rfu_waitREQComplete();
        }
        if (gRfu.state == 0xF)
            gRfu.state = 16;
        break;
    case LMAN_MSG_PARENT_FOUND:
        gRfu.parentId = lman.param[0];
        break;
    case LMAN_MSG_SEARCH_PARENT_PERIOD_EXPIRED:
        break;
    case LMAN_MSG_CONNECT_PARENT_SUCCESSED:
        gRfu.child_slot = lman.param[0];
        break;
    case LMAN_MSG_CONNECT_PARENT_FAILED:
        gRfu.state = 18;
        if (gRfu.unk_ccf < 2)
        {
            gRfu.unk_ccf++;
            CreateTask(sub_80FC028, 2);
        }
        else
        {
            RfuSetErrorStatus(2, msg);
        }
        break;
    case LMAN_MSG_CHILD_NAME_SEND_COMPLETED:
        gRfu.state = 13;
        RfuSetErrorStatus(3, 0);
        rfu_setRecvBuffer(TYPE_UNI, gRfu.child_slot, gRfu.unk_c3f, sizeof(gRfu.unk_c3f));
        break;
    case LMAN_MSG_CHILD_NAME_SEND_FAILED_AND_DISCONNECTED:
        RfuSetErrorStatus(2, msg);
        break;
    case LMAN_MSG_LINK_LOSS_DETECTED_AND_START_RECOVERY:
        if (lman.acceptSlot_flag & lman.param[0])
            gRfu.linkLossRecoveryState = 1;
        break;
    case LMAN_MSG_LINK_RECOVERY_SUCCESSED:
        gRfu.linkLossRecoveryState = 3;
        if (gRfuLinkStatus->parentChild == MODE_CHILD)
            gRfu.unk_c3c = 1;
        break;
    case LMAN_MSG_LINK_LOSS_DETECTED_AND_DISCONNECTED:
        gRfu.linkLossRecoveryState = 2;
        // fallthrough
    case LMAN_MSG_LINK_RECOVERY_FAILED_AND_DISCONNECTED:
        if (gRfu.linkLossRecoveryState != 2)
            gRfu.linkLossRecoveryState = 4;
        if (gRfu.parent_child == MODE_PARENT)
        {
            if (gReceivedRemoteLinkPlayers == 1)
            {
                gRfu.bm_PartnerFlags &= ~(lman.param[0]);
                if (gRfu.bm_PartnerFlags == 0)
                    GetLinkmanErrorParams(msg);
                else
                    sub_80FB174();
            }
        }
        else if (gRfu.unk_ce4 != 2 && gReceivedRemoteLinkPlayers == 1)
        {
            GetLinkmanErrorParams(msg);
            rfu_LMAN_stopManager(0);
        }

        if (gRfuLinkStatus->parentChild == MODE_NEUTRAL && lman.pcswitch_flag == 0 && FuncIsActiveTask(Task_LinkRfu_UnionRoomListen) == TRUE)
            gRfu.state = 17;

        RfuSetErrorStatus(2, msg);
        break;
    case LMAN_MSG_LINK_DISCONNECTED_BY_USER:
        gRfu.bm_DisconnectSlot = 0;
        break;
    case LMAN_MSG_RFU_POWER_DOWN:
    case LMAN_MSG_MANAGER_STOPPED:
    case LMAN_MSG_MANAGER_FORCED_STOPPED_AND_RFU_RESET:
        break;
    case LMAN_MSG_LMAN_API_ERROR_RETURN:
        RfuSetErrorStatus(1, msg);
        GetLinkmanErrorParams(msg);
        gRfu.isShuttingDown = TRUE;
        break;
    case LMAN_MSG_REQ_API_ERROR:
    case LMAN_MSG_WATCH_DOG_TIMER_ERROR:
    case LMAN_MSG_CLOCK_SLAVE_MS_CHANGE_ERROR_BY_DMA:
    case LMAN_MSG_RFU_FATAL_ERROR:
        GetLinkmanErrorParams(msg);
        RfuSetErrorStatus(1, msg);
        gRfu.unk_cdb = 0;
        break;
    }
}

void sub_80FB9D0(void)
{
    gRfu.unk_ce4 = 2;
}

void RfuSetErrorStatus(u8 a0, u16 msg)
{
    gRfu.unk_f1 = a0;
    gRfu.linkman_msg = msg;
}

u8 RfuGetErrorStatus(void)
{
    return gRfu.unk_f1;
}

bool32 RfuIsErrorStatus1or2(void)
{
    u32 var = RfuGetErrorStatus();
    if (var == 1 || var == 2)
        return TRUE;
    else
        return FALSE;
}

bool32 GetRfuUnkCE8(void)
{
    return gRfu.unk_ce8;
}

bool8 Rfu_IsMaster(void)
{
    return gRfu.parent_child;
}

void RFUVSync(void)
{
    rfu_LMAN_syncVBlank();
}

void ClearRecvCommands(void)
{
    CpuFill32(0, gRecvCmds, sizeof(gRecvCmds));
}

static void sub_80FBA64(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void sub_80FBA78(void)
{
    s32 i;

    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetTasks();
    ResetPaletteFade();
    SetVBlankCallback(sub_80FBA64);
    if (IsWirelessAdapterConnected())
    {
        gLinkType = LINKTYPE_0x1111;
        SetWirelessCommType1();
        OpenLink();
        SeedRng(gMain.vblankCounter2);
        for (i = 0; i < RFU_CHILD_MAX; i++)
            gSaveBlock2Ptr->playerTrainerId[i] = Random() % 256;

        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_BG0_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_1D_MAP);
        RunTasks();
        AnimateSprites();
        BuildOamBuffer();
        UpdatePaletteFade();
        LinkRfu_CreateIdleTask();
        SetMainCallback2(sub_80FBB74);
    }
}

bool32 IsUnionRoomListenTaskActive(void)
{
    return FuncIsActiveTask(Task_LinkRfu_UnionRoomListen);
}

void LinkRfu_CreateIdleTask(void)
{
    if (!FuncIsActiveTask(Task_idle))
        gRfu.unk_66 = CreateTask(Task_idle, 0);
}

void LinkRfu_DestroyIdleTask(void)
{
    if (FuncIsActiveTask(Task_idle) == TRUE)
        DestroyTask(gRfu.unk_66);
}

static void sub_80FBB74(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void InitializeRfuLinkManager_LinkLeader(u32 availSlots)
{
    gRfu.parent_child = MODE_PARENT;
    CopyPlayerNameToUnameBuffer();
    rfu_LMAN_initializeManager(LmanCallback_Parent2, NULL);
    sRfuReqConfig = sRfuReqConfigTemplate;
    sRfuReqConfig.availSlot_flag = sAvailSlots[availSlots - 1];
    CreateTask_LinkLeaderSearchForChildren();
}

void InitializeRfuLinkManager_JoinGroup(void)
{
    gRfu.parent_child = MODE_CHILD;
    CopyPlayerNameToUnameBuffer();
    rfu_LMAN_initializeManager(LmanCallback_Child, MscCallback_Child);
    CreateTask_JoinGroupSearchForParent();
}

void InitializeRfuLinkManager_EnterUnionRoom(void)
{
    if (QL_IS_PLAYBACK_STATE)
        return;
    gRfu.parent_child = 2;
    CopyPlayerNameToUnameBuffer();
    rfu_LMAN_initializeManager(LmanCallback_Parent, NULL);
    sRfuReqConfig = sRfuReqConfigTemplate;
    sRfuReqConfig.linkRecovery_enable = 0;
    sRfuReqConfig.linkRecovery_period = 600;
    gRfu.unk_67 = CreateTask(Task_LinkRfu_UnionRoomListen, 1);
}

static u16 ReadU16(const void *ptr)
{
    const u8 *ptr_ = ptr;
    return (ptr_[1] << 8) | (ptr_[0]);
}

/*
 * ================================================================
 * Looks up the player by uname and pid. Returns the index in
 * gRfuLinkStatus->partner of the first match with a valid slot ID.
 * Returns 0xFF if not found.
 * ================================================================
 */
static u8 GetPartnerIndexByNameAndTrainerID(const u8 *trainerName, u16 trainerId)
{
    u8 i;
    u8 ret = 0xFF;

    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        u16 partnerTrainerId = ReadU16(((struct RfuGameData *)gRfuLinkStatus->partner[i].gname)->unk_00.playerTrainerId);
        if (RfuSerialNumberIsValid(gRfuLinkStatus->partner[i].serialNo)
            && !StringCompare(trainerName, gRfuLinkStatus->partner[i].uname)
            && trainerId == partnerTrainerId)
        {
            ret = i;
            if (gRfuLinkStatus->partner[i].slot != 0xFF)
                break;
        }
    }

    return ret;
}

static void RfuReqDisconnectSlot(u32 bmDisconnectSlot)
{
    rfu_REQ_disconnect(bmDisconnectSlot);
    rfu_waitREQComplete();
    gRfu.bm_PartnerFlags &= ~(bmDisconnectSlot);
    rfu_clearSlot(TYPE_UNI_SEND, gRfu.unk_cda);
    rfu_UNI_setSendData(gRfu.bm_PartnerFlags, gRfu.recvCmds, 70);
    gRfu.unk_cda = sub_80F886C(gRfu.bm_PartnerFlags);
}

void RequestDisconnectSlotByTrainerNameAndId(const u8 *trainerName, u16 trainerId)
{
    u8 var = GetPartnerIndexByNameAndTrainerID(trainerName, trainerId);
    if (var != 0xFF)
        RfuReqDisconnectSlot(1 << var);
}

void sub_80FBD6C(u32 a0)
{
    if (a0 != 0)
    {
        s32 i;
        u8 var = 0;

        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            if (gRfu.linkPlayerIdx[i] == a0 && (gRfu.bm_PartnerFlags >> i) & 1)
                var |= 1 << i;
        }
        if (var)
            sub_80FBE20(var, 2);
    }
}

static void sub_80FBDB8(u8 taskId)
{
    if (gSendCmd[0] == 0 && !gRfu.unk_ce8)
    {
        RfuPrepareSendBuffer(RFUCMD_DISCONNECT);
        gSendCmd[1] = gTasks[taskId].data[0];
        gSendCmd[2] = gTasks[taskId].data[1];
        gRfu.playerCount -= gUnknown_843EC41[gTasks[taskId].data[0]];
        gSendCmd[3] = gRfu.playerCount;
        DestroyTask(taskId);
    }
}

static void sub_80FBE20(u32 a0, u32 a1)
{
    u8 taskId = FindTaskIdByFunc(sub_80FBDB8);
    if (taskId == 0xFF)
    {
        taskId = CreateTask(sub_80FBDB8, 5);
        gTasks[taskId].data[0] = a0;
    }
    else
    {
        gTasks[taskId].data[0] |= a0;
    }

    gTasks[taskId].data[1] = a1;
}

static void Task_RfuReconnectWithParent(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (RfuStateIs7AndPlayerIsChild())
    {
        u8 id = GetPartnerIndexByNameAndTrainerID((u8*)data, ReadU16(&data[8]));
        if (id != 0xFF)
        {
            if (gRfuLinkStatus->partner[id].slot != 0xFF)
            {
                gRfu.reconnectedParentIdx = id;
                if (IsParentSuccessfullyReconnected())
                    DestroyTask(taskId);
            }
            else if (GetHostRFUtgtGname()->activity == ACTIVITY_WCARD2 || GetHostRFUtgtGname()->activity == ACTIVITY_WNEWS2)
            {
                data[15]++;
            }
            else
            {
                RfuSetErrorStatus(2, 0x7000);
                DestroyTask(taskId);
            }
        }
        else
        {
            data[15]++;
            gRfu.reconnectedParentIdx = id;
        }
    }
    else
    {
        data[15]++;
    }

    if (data[15] > 240)
    {
        RfuSetErrorStatus(2, 0x7000);
        DestroyTask(taskId);
    }
}

void CreateTask_RfuReconnectWithParent(const u8 *trainerName, u16 trainerId)
{
    u8 taskId;
    s16 *data;

    gRfu.unk_f1 = 0;
    taskId = CreateTask(Task_RfuReconnectWithParent, 3);
    data = gTasks[taskId].data;
    StringCopy((u8*)(data), trainerName);
    data[8] = trainerId;
}

static bool32 ShouldRejectPartnerConnectionBasedOnActivity(s16 activity, struct RfuGameData *partnerGname)
{
    if (GetHostRFUtgtGname()->activity == (ACTIVITY_CHAT | IN_UNION_ROOM))
    {
        if (partnerGname->activity != (ACTIVITY_CHAT | IN_UNION_ROOM))
            return TRUE;
    }
    else if (partnerGname->activity != IN_UNION_ROOM)
    {
        return TRUE;
    }
    else if (activity == (ACTIVITY_TRADE | IN_UNION_ROOM))
    {
        struct RfuGameData *myTradeGname = (struct RfuGameData *)&gRfu.unk_104.gname;
        if (myTradeGname->tradeSpecies == SPECIES_EGG)
        {
            if (partnerGname->tradeSpecies == myTradeGname->tradeSpecies)
                return FALSE;
            else
                return TRUE;
        }
        else if (partnerGname->tradeSpecies != myTradeGname->tradeSpecies
                 || partnerGname->level != myTradeGname->level
                 || partnerGname->tradeType != myTradeGname->tradeType)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static void sub_80FC028(u8 taskId)
{
    if (gRfu.unk_f1 == 4)
        DestroyTask(taskId);

    if (++gTasks[taskId].data[0] > 300)
    {
        RfuSetErrorStatus(2, 0x7000);
        DestroyTask(taskId);
    }

    if (gRfu.parentId != 0 && lman.parent_child == MODE_CHILD)
    {
        u16 trainerId = ReadU16(((struct RfuGameData *)&gRfu.unk_104.gname)->unk_00.playerTrainerId);
        u8 id = GetPartnerIndexByNameAndTrainerID(gRfu.unk_104.uname, trainerId);
        if (id != 0xFF)
        {
            if (!ShouldRejectPartnerConnectionBasedOnActivity(gTasks[taskId].data[1], (struct RfuGameData *)&gRfuLinkStatus->partner[id].gname))
            {
                if (gRfuLinkStatus->partner[id].slot != 0xFF && !rfu_LMAN_CHILD_connectParent(gRfuLinkStatus->partner[id].id, 90))
                {
                    gRfu.state = 10;
                    DestroyTask(taskId);
                }
            }
            else
            {
                RfuSetErrorStatus(2, 0x7000);
                DestroyTask(taskId);
            }
        }
    }
}

void sub_80FC114(const u8 *name, struct RfuGameData *structPtr, u8 activity)
{
    u8 taskId, taskId2;

    gRfu.unk_ccf = 0;
    gRfu.unk_f1 = 0;
    StringCopy(gRfu.unk_104.uname, name);
    memcpy(gRfu.unk_104.gname, structPtr, RFU_GAME_NAME_LENGTH);
    rfu_LMAN_forceChangeSP();
    taskId = CreateTask(sub_80FC028, 2);
    gTasks[taskId].data[1] = activity;
    taskId2 = FindTaskIdByFunc(Task_LinkRfu_UnionRoomListen);
    if (activity == (ACTIVITY_CHAT | IN_UNION_ROOM))
    {
        if (taskId2 != 0xFF)
            gTasks[taskId2].data[7] = 1;
    }
    else
    {
        if (taskId2 != 0xFF)
            gTasks[taskId2].data[7] = 0;
    }
}

bool8 sub_80FC1B0(void)
{
    if (gRfu.linkLossRecoveryState == 1)
        return TRUE;
    else
        return FALSE;
}

bool32 sub_80FC1CC(void)
{
    s32 i;

    for (i = 0; i < RFU_CHILD_MAX; i++)
    {
        if ((lman.acceptSlot_flag >> i) & 1 && gRfu.unk_cd1[i] == 0)
            return FALSE;
    }

    return TRUE;
}

static void rfu_dbg_clear(void)
{
    s32 i;

    for (i = 0; i < 20; i++)
        rfu_dbg_print_str("                              ", 0, i);
}

static const char gUnknown_843EE47[16] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    '\0'
};

static const char gUnknown_843EE57[9] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    '\0'
};

static const char gUnknown_843EE60[] = {' ', '\0'};
static const char gUnknown_843EE62[] = {'*', '\0'};

static void rfu_dbg_print_status(void)
{
    s32 i, j;

    rfu_dbg_print_num(GetBlockReceivedStatus(), 0x1C, 0x13, 2);
    rfu_dbg_print_num(gRfuLinkStatus->connSlotFlag, 0x14, 1, 1);
    rfu_dbg_print_num(gRfuLinkStatus->linkLossSlotFlag, 0x17, 1, 1);
    if (gRfu.parent_child == MODE_PARENT)
    {
        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            if ((gRfuLinkStatus->getNameFlag >> i) & 1)
            {
                rfu_dbg_print_num(gRfuLinkStatus->partner[i].serialNo, 1, i + 3, 4);
                rfu_dbg_print_str((void*) &gRfuLinkStatus->partner[i].gname, 6, i + 3);
                rfu_dbg_print_str(gRfuLinkStatus->partner[i].uname, 0x16, i + 3);
            }
        }
        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            for (j = 0; j < 14; j++)
            {
                rfu_dbg_print_num(gRfu.unk_14[i][j], j * 2, i + 11, 2);
            }
        }
        rfu_dbg_print_str("NOWSLOT", 1, 0xF);
    }
    else if (gRfuLinkStatus->connSlotFlag != 0 && gRfuLinkStatus->getNameFlag != 0)
    {
        for (i = 0; i < RFU_CHILD_MAX; i++)
        {
            rfu_dbg_print_num(0, 1, i + 3, 4);
            rfu_dbg_print_str(gUnknown_843EE47, 6, i + 3);
            rfu_dbg_print_str(gUnknown_843EE57, 0x16, i + 3);
        }
        rfu_dbg_print_num(gRfuLinkStatus->partner[gRfu.child_slot].serialNo, 1, 3, 4);
        rfu_dbg_print_str(gRfuLinkStatus->partner[gRfu.child_slot].gname, 6, 3);
        rfu_dbg_print_str(gRfuLinkStatus->partner[gRfu.child_slot].uname, 0x16, 3);
    }
    else
    {
        for (i = 0; i < gRfuLinkStatus->findParentCount; i++)
        {
            if (gRfuLinkStatus->partner[i].slot != 0xFF)
            {
                rfu_dbg_print_num(gRfuLinkStatus->partner[i].serialNo, 1, i + 3, 4);
                rfu_dbg_print_num(gRfuLinkStatus->partner[i].id, 6, i + 3, 4);
                rfu_dbg_print_str(gRfuLinkStatus->partner[i].uname, 0x16, i + 3);
            }
        }
        for (; i < RFU_CHILD_MAX; i++)
        {
            rfu_dbg_print_num(0, 1, i + 3, 4);
            rfu_dbg_print_str(gUnknown_843EE47, 6, i + 3);
            rfu_dbg_print_str(gUnknown_843EE57, 0x16, i + 3);
        }
    }
}

static const char gUnknown_843EE6C[][12] = {
    "           ",
    "CLOCK DRIFT",
    "BUSY SEND  ",
    "CMD REJECT ",
    "CLOCK SLAVE"
};

static const char gUnknown_843EEA8[][8] = {
    "CHILD ",
    "PARENT",
    "SEARCH"
};

static u32 sub_80FC44C(void)
{
    return gRfu.sendQueue.count;
}

u32 GetRfuRecvQueueLength(void)
{
    return gRfu.unk_124.count;
}

static void Task_idle(u8 taskId)
{

}
