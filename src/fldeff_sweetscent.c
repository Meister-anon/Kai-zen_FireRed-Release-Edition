#include "global.h"
#include "gflib.h"
#include "field_player_avatar.h"
#include "field_effect.h"
#include "malloc.h"
#include "party_menu.h"
#include "script.h"
#include "fldeff.h"
#include "event_scripts.h"
#include "field_weather.h"
#include "wild_encounter.h"
#include "util.h"
#include "constants/songs.h"

static EWRAM_DATA u8 *gUnknown_203AAB0 = NULL;

static void FieldCallback_SweetScent(void);
static void StartSweetScentFieldEffect(void);
static void TrySweetScentEncounter(u8 taskId);
static void FailSweetScentEncounter(u8 taskId);

static void Unused_StartSweetscentFldeff(void)
{
	gPartyMenu.slotId = 0;
	FieldCallback_SweetScent();
}

bool8 SetUpFieldMove_SweetScent(void)
{
    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = FieldCallback_SweetScent;
    return TRUE;
}

static void FieldCallback_SweetScent(void)
{
    FieldEffectStart(FLDEFF_SWEET_SCENT);
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
}

bool8 FldEff_SweetScent(void)
{
    u8 taskId;

    SetWeatherScreenFadeOut();
    taskId = CreateFieldEffectShowMon();
    FLDEFF_SET_FUNC_TO_DATA(StartSweetScentFieldEffect);
    return FALSE;
}

#define tPalBuffer1 data[1]
#define tPalBuffer2 data[2]
static void StartSweetScentFieldEffect(void)
{
    void *palBuffer;
    u32 taskId;
    u32 palettes = ~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16) | (1 << 13) | (1 << 14) | (1 << 15));


    PlaySE(SE_M_SWEET_SCENT);
    //gUnknown_203AAB0 = (u8 *)Alloc(0x400);
    palBuffer = Alloc(PLTT_SIZE);
    CpuFastCopy(gPlttBufferUnfaded, palBuffer, PLTT_SIZE);
    CpuFastCopy(gPlttBufferFaded, gPlttBufferUnfaded, PLTT_SIZE);
    //CpuFastSet(gPlttBufferUnfaded, gUnknown_203AAB0, 0x100);
    //CpuFastSet(gPlttBufferFaded, gPlttBufferUnfaded, 0x100);
    //BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 0, 8, RGB_RED);
    BeginNormalPaletteFade(palettes, 4, 0, 8, RGB_RED);
    taskId = CreateTask(TrySweetScentEncounter, 0);
    gTasks[taskId].data[0] = 0;
    StoreWordInTwoHalfwords((u16 *)&gTasks[taskId].tPalBuffer1, (u32) palBuffer);
    FieldEffectActiveListRemove(FLDEFF_SWEET_SCENT);
}

static void *GetPalBufferPtr(u32 taskId)
{
    u32 palBuffer;

    LoadWordFromTwoHalfwords((u16 *)&gTasks[taskId].tPalBuffer1, &palBuffer);
    return (void *) palBuffer;
}

static void FreeDestroyTask(u32 taskId)
{
    Free(GetPalBufferPtr(taskId));
    DestroyTask(taskId);
}

static void TrySweetScentEncounter(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        BlendPalettes(0x00000040, 8, RGB_RED); //need test
        if (data[0] == 64)
        {
            data[0] = 0;
            if (SweetScentWildEncounter() == TRUE)
            {
                //Free(gUnknown_203AAB0);
                FreeDestroyTask(taskId);
                
            }
            else
            {
                gTasks[taskId].func = FailSweetScentEncounter;
                BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 8, 0, RGB(31, 0, 0));
            }
        }
        else
        {
            data[0]++;
        }
    }
}

static void FailSweetScentEncounter(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        //CpuFastSet(gUnknown_203AAB0, gPlttBufferUnfaded, 0x100);
        CpuFastCopy(GetPalBufferPtr(taskId), gPlttBufferUnfaded, PLTT_SIZE);
        SetWeatherPalStateIdle();
        //Free(gUnknown_203AAB0);
        ScriptContext_SetupScript(EventScript_FailSweetScent);
        FreeDestroyTask(taskId);
    }
}

#undef tPalBuffer1
#undef tPalBuffer2