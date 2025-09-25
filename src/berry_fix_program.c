#include "global.h"
#include "gpu_regs.h"
#include "multiboot.h"
#include "graphics.h"
#include "main.h"
#include "sprite.h"
#include "task.h"
#include "scanline_effect.h"
#include "help_system.h"
#include "m4a.h"

enum {
    SCENE_ENSURE_CONNECT,
    SCENE_TURN_OFF_POWER,
    SCENE_TRANSMITTING,
    SCENE_FOLLOW_INSTRUCT,
    SCENE_TRANSMIT_FAILED,
    SCENE_BEGIN,
};

enum {
    STATE_BEGIN,
    STATE_CONNECT,
    STATE_TURN_OFF_POWER,
    STATE_UNUSED,
    STATE_INIT_MULTIBOOT,
    STATE_MULTIBOOT,
    STATE_TRANSMIT,
    STATE_SUCCEEDED,
    STATE_EXIT,
    STATE_FAILED,
    STATE_RETRY,
};

COMMON_DATA const void *gMultibootStart = NULL;
COMMON_DATA int gMultibootStatus = 0;
COMMON_DATA size_t gMultibootSize = 0;
COMMON_DATA struct MultiBootParam gMultibootParam = {0};

static void mb_berry_fix_maincb(void);
static void mb_berry_fix_task(u8 taskId);

// .rodata

static const void *const gUnknown_847A890[][3] = {
    {
        gBerryFixGameboy_Gfx,
        gBerryFixGameboy_Tilemap,
        gBerryFixGameboy_Pal
    }, {
        gBerryFixGameboyLogo_Gfx,
        gBerryFixGameboyLogo_Tilemap,
        gBerryFixGameboyLogo_Pal
    }, {
        gBerryFixGbaTransfer_Gfx,
        gBerryFixGbaTransfer_Tilemap,
        gBerryFixGbaTransfer_Pal
    }, {
        gBerryFixGbaTransferHighlight_Gfx,
        gBerryFixGbaTransferHighlight_Tilemap,
        gBerryFixGbaTransferHighlight_Pal
    }, {
        gBerryFixGbaTransferError_Gfx,
        gBerryFixGbaTransferError_Tilemap,
        gBerryFixGbaTransferError_Pal
    }, {
        gBerryFixWindow_Gfx,
        gBerryFixWindow_Tilemap,
        gBerryFixWindow_Pal
    },
};

extern const u8 gMultiBootProgram_BerryGlitchFix_Start[0x3BF4];
extern const u8 gMultiBootProgram_BerryGlitchFix_End[];

// .text

#define tState data[0]
#define tTimer data[1]

static void mb_berry_fix_print(int scene)
{
    REG_DISPCNT = 0;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    REG_BLDCNT = 0;
    LZ77UnCompVram(gUnknown_847A890[scene][0], (void *)BG_CHAR_ADDR(0));
    LZ77UnCompVram(gUnknown_847A890[scene][1], (void *)BG_SCREEN_ADDR(31));
    CpuCopy16(gUnknown_847A890[scene][2], (void *)BG_PLTT, 0x200);
    REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_16COLOR | BGCNT_SCREENBASE(31) | BGCNT_TXT256x256;
    REG_DISPCNT = DISPCNT_BG0_ON;
}

void mb_berry_fix_serve(void) // noreturn
{
    u8 taskId;
    DisableInterrupts(0xFFFF);
    EnableInterrupts(INTR_FLAG_VBLANK);
    m4aSoundVSyncOff();
    SetVBlankCallback(NULL);
    DmaFill32(3, 0, (void *)VRAM, VRAM_SIZE);
    DmaFill32(3, 0, (void *)PLTT, PLTT_SIZE);
    ResetSpriteData();
    ResetTasks();
    ScanlineEffect_Stop();
    gHelpSystemEnabled = FALSE;
    taskId = CreateTask(mb_berry_fix_task, 0);
    gTasks[taskId].data[0] = 0;
    SetMainCallback2(mb_berry_fix_maincb);
}

static void mb_berry_fix_maincb(void)
{
    RunTasks();
}

static void mb_berry_fix_task(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    switch (data[0])
    {
    case 0:
        mb_berry_fix_print(5);
        data[0] = 1;
        break;
    case 1:
        if (JOY_NEW(A_BUTTON))
        {
            mb_berry_fix_print(0);
            data[0] = 2;
        }
        break;
    case 2:
        if (JOY_NEW(A_BUTTON))
        {
            mb_berry_fix_print(1);
            data[0] = 4;
        }
        break;
    case STATE_INIT_MULTIBOOT:
        gMultibootStart = gMultiBootProgram_BerryGlitchFix_Start;
        gMultibootSize = gMultiBootProgram_BerryGlitchFix_End - gMultiBootProgram_BerryGlitchFix_Start;
        gMultibootParam.masterp = (void *)gMultiBootProgram_BerryGlitchFix_Start;
        gMultibootParam.server_type = MULTIBOOT_SERVER_TYPE_NORMAL;
        MultiBootInit(&gMultibootParam);
        tTimer = 0;
        tState = STATE_MULTIBOOT;
        break;
    case STATE_MULTIBOOT:
        if (gMultibootParam.probe_count == 0 && gMultibootParam.response_bit & 0x2 && gMultibootParam.client_bit & 0x2)
        {
            data[1]++;
            if (data[1] > 180)
            {
                mb_berry_fix_print(SCENE_TRANSMITTING);
                MultiBootStartMaster(&gMultibootParam, gMultibootStart + MULTIBOOT_HEADER_SIZE, gMultibootSize - MULTIBOOT_HEADER_SIZE, 4, 1);
                tTimer = 0;
                tState = STATE_TRANSMIT;
            }
            else
            {
                gMultibootStatus = MultiBootMain(&gMultibootParam);
            }
        }
        else
        {
            tTimer = 0;
            gMultibootStatus = MultiBootMain(&gMultibootParam);
        }
        break;
    case STATE_TRANSMIT:
        gMultibootStatus = MultiBootMain(&gMultibootParam);
        if (MultiBootCheckComplete(&gMultibootParam))
        {
            mb_berry_fix_print(3);
            data[0] = 7;
        }
        else if (!(gMultibootParam.client_bit & 2))
        {
            tState = STATE_FAILED;
        }
        break;
    case 7:
        data[0] = 8;
        break;
    case 8:
        if (JOY_NEW(A_BUTTON))
        {
            DestroyTask(taskId);
            DoSoftReset();
        }
        break;
    case 9:
        mb_berry_fix_print(4);
        data[0] = 10;
        break;
    case 10:
        if (JOY_NEW(A_BUTTON))
            data[0] = 0;
        break;
    }
}
