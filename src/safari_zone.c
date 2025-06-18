#include "global.h"
#include "battle.h"
#include "event_scripts.h"
#include "overworld.h"
#include "script.h"
#include "event_data.h"
#include "field_screen_effect.h"

EWRAM_DATA u8 gNumSafariBalls = 0;
EWRAM_DATA u16 gSafariZoneStepCounter = 0;

bool32 GetSafariZoneFlag(void)
{
    return FlagGet(FLAG_SYS_SAFARI_MODE);
}

void SetSafariZoneFlag(void)
{
    FlagSet(FLAG_SYS_SAFARI_MODE);
}

void ResetSafariZoneFlag(void)
{
    FlagClear(FLAG_SYS_SAFARI_MODE);
}

void EnterSafariMode(void)
{
    IncrementGameStat(GAME_STAT_ENTERED_SAFARI_ZONE);
    SetSafariZoneFlag();
    if (FlagGet(FLAG_SAFARI_VIP))//initial plan was 150, may lower
        gNumSafariBalls = 250;
    else
        gNumSafariBalls = 30;

    gSafariZoneStepCounter = 600;
    
}
//think will leave at 250 w catch odds 
//is possible to blow through 30 balls on like 2-5 encounters

//set here so doesn't interupt current safari zone instance
void ExitSafariMode(void)
{
    if (FlagGet(FLAG_GOT_HM03) && (!(FlagGet(FLAG_SAFARI_VIP))))
        FlagSet(FLAG_SAFARI_VIP);
    ResetSafariZoneFlag();
    gNumSafariBalls = 0;
    gSafariZoneStepCounter = 0;
}

//don't include step count in vip mode
bool8 SafariZoneTakeStep(void)
{
    if (GetSafariZoneFlag() == FALSE)
        return FALSE;
    if (!(FlagGet(FLAG_SAFARI_VIP)))
        gSafariZoneStepCounter--;

    if (gSafariZoneStepCounter == 0)
    {
        ScriptContext1_SetupScript(SafariZone_EventScript_TimesUp);
        return TRUE;
    }
    return FALSE;
}

void SafariZoneRetirePrompt(void)
{
    ScriptContext1_SetupScript(SafariZone_EventScript_RetirePrompt);
}

void CB2_EndSafariBattle(void)
{
    if (gNumSafariBalls != 0)
    {
        SetMainCallback2(CB2_ReturnToField);
    }
    else if (gBattleOutcome == B_OUTCOME_NO_SAFARI_BALLS)
    {
        ScriptContext2_RunNewScript(SafariZone_EventScript_OutOfBallsMidBattle);
        WarpIntoMap();
        gFieldCallback = FieldCB_SafariZoneRanOutOfBalls;
        SetMainCallback2(CB2_LoadMap);
    }
    else if (gBattleOutcome == B_OUTCOME_CAUGHT)
    {
        ScriptContext1_SetupScript(SafariZone_EventScript_OutOfBalls);
        ScriptContext1_Stop();
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
}
