#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "field_fadetransition.h"
#include "field_weather.h"
#include "help_system.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "overworld.h"
#include "pokemon_storage_system_internal.h"
#include "script.h"
#include "strings.h"
#include "task.h"
#include "trainer_card.h"
#include "constants/songs.h"
#include "constants/field_weather.h"
#include "constants/help_system.h"

struct PSS_MenuStringPtrs
{
    const u8 *text;
    const u8 *desc;
};

static EWRAM_DATA u8 sPreviousBoxOption = 0;
static EWRAM_DATA struct ChooseBoxMenu *sBoxSelectionPopupSpriteManager = NULL;

static void PSS_CreatePCMenu(u8 whichMenu, s16 *windowIdPtr);
static void sub_808C9C4(u8 curBox);
static void sub_808CBA4(void);
static void UpdateBoxNameAndCountSprite_WraparoundRight(void);
static void UpdateBoxNameAndCountSprite_WraparoundLeft(void);
static void PrintBoxNameAndCountToSprite(void);
static void PrintToSpriteWithTagUnk0240(const u8 *a0, u16 x, u16 y);
static void sub_808CD64(struct Sprite * sprite);

// Forward declarations

static const u16 sBoxSelectionPopupPalette[];
static const u16 sBoxSelectionPopupCenterTiles[];
static const u16 sBoxSelectionPopupSidesTiles[];



void DrawTextWindowAndBufferTiles(const u8 *string, void *dst, u8 zero1, u8 zero2, u8 *buffer, s32 bytesToBuffer)
{
    s32 i, tileBytesToBuffer, remainingBytes;
    u16 windowId;
    u8 txtColor[3];
    u8 *tileData1, *tileData2;
    struct WindowTemplate winTemplate = {0};

    winTemplate.width = 24;
    winTemplate.height = 2;
    windowId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(zero2));
    tileData1 = (u8*)GetWindowAttribute(windowId, WINDOW_TILE_DATA);
    tileData2 = (winTemplate.width * 32) + tileData1;

    if (!zero1)
        txtColor[0] = TEXT_COLOR_TRANSPARENT;
    else
        txtColor[0] = zero2;
    txtColor[1] = TEXT_DYNAMIC_COLOR_6;
    txtColor[2] = TEXT_DYNAMIC_COLOR_5;
    AddTextPrinterParameterized4(windowId, 1, 0, 2, 0, 0, txtColor, -1, string);

    tileBytesToBuffer = bytesToBuffer;
    if (tileBytesToBuffer > 6)
        tileBytesToBuffer = 6;
    remainingBytes = bytesToBuffer - 6;
    if (tileBytesToBuffer > 0)
    {
        for (i = tileBytesToBuffer; i != 0; i--)
        {
            CpuCopy16(tileData1, dst, 0x80);
            CpuCopy16(tileData2, dst + 0x80, 0x80);
            tileData1 += 0x80;
            tileData2 += 0x80;
            dst += 0x100;
        }
    }

    // Never used. bytesToBuffer is always passed <= 6, so remainingBytes is always <= 0 here
    if (remainingBytes > 0)
        CpuFill16((zero2 << 4) | zero2, dst, (u32)(remainingBytes) * 0x100);

    RemoveWindow(windowId);
}

static void PrintStringToBufferCopyNow(const u8 *string, void *dst, u16 rise, u8 bgClr, u8 fgClr, u8 shClr, u8 *buffer)
{
    u32 var;
    u8 windowId;
    u8 txtColor[3];
    u8 *tileData1, *tileData2;
    struct WindowTemplate winTemplate = {0};

    winTemplate.width = StringLength_Multibyte(string);
    winTemplate.height = 2;
    var = winTemplate.width * 32;
    windowId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(bgClr));
    tileData1 = (u8*)GetWindowAttribute(windowId, WINDOW_TILE_DATA);
    tileData2 = (winTemplate.width * 32) + tileData1;
    txtColor[0] = bgClr;
    txtColor[1] = fgClr;
    txtColor[2] = shClr;
    AddTextPrinterParameterized4(windowId, 1, 0, 2, 0, 0, txtColor, -1, string);
    CpuCopy16(tileData1, dst, var);
    CpuCopy16(tileData2, dst + rise, var);
    RemoveWindow(windowId);
}

//with how setup, may need to 
//make multiple different tables for each state?
//checked and yes each menu referes to this,

/*static const struct PSS_MenuStringPtrs sPSS_DefaultState[] = {
    {gText_WithdrawPokemon, gText_WithdrawMonDescription},
    {gText_DepositPokemon,  gText_DepositMonDescription },
    {gText_MovePokemon,     gText_MoveMonDescription    },
    {gText_MoveItems,       gText_MoveItemsDescription  },
    {gText_SeeYa,           gText_SeeYaDescription      }
};
*/

//remove withdraw and dposit when I fully understand logic
static const struct PSS_MenuStringPtrs sPSS_DefaultState[] = {
    //{gText_WithdrawPokemon, gText_WithdrawMonDescription},
    //{gText_DepositPokemon,  gText_DepositMonDescription },
    {gText_MovePokemon,     gText_MoveMonDescription    },
    {gText_MoveItems,       gText_MoveItemsDescription  },
    {gText_SeeYa,           gText_SeeYaDescription      }
};

static const struct PSS_MenuStringPtrs sPSS_State1[] = {
    {gText_MovePokemon,     gText_MoveMonDescription    },
    {gText_MoveItems,       gText_MoveItemsDescription  },
    {gText_DeleteMove,       gText_DeleteMoveDescription  },
    //{gText_RelearnMove,       gText_RelearnMoveDescription  },
    {gText_SeeYa,           gText_SeeYaDescription      }
};

static const struct PSS_MenuStringPtrs sPSS_State2[] = {
    {gText_MovePokemon,     gText_MoveMonDescription    },
    {gText_MoveItems,       gText_MoveItemsDescription  },
    //{gText_DeleteMove,       gText_DeleteMoveDescription  },
    {gText_RelearnMove,       gText_RelearnMoveDescription  },
    {gText_SeeYa,           gText_SeeYaDescription      }
};

static const struct PSS_MenuStringPtrs sPSS_FinalState[] = {
    {gText_MovePokemon,     gText_MoveMonDescription    },
    {gText_MoveItems,       gText_MoveItemsDescription  },
    {gText_DeleteMove,       gText_DeleteMoveDescription  },
    {gText_RelearnMove,       gText_RelearnMoveDescription  },
    {gText_SeeYa,           gText_SeeYaDescription      }
};

static u8 ReturnPSS_ListSizebyState(void)
{
    if ((FlagGet(FLAG_TAUGHT_MOVE_DELETE) && FlagGet(FLAG_TAUGHT_MOVE_RELEARN)) || FlagGet(FLAG_NEW_GAME_PLUS))
        return NELEMS(sPSS_FinalState);    
    else if (FlagGet(FLAG_TAUGHT_MOVE_DELETE))
        return NELEMS(sPSS_State1);
    else if (FlagGet(FLAG_TAUGHT_MOVE_RELEARN))
        return NELEMS(sPSS_State2);
    else
        return NELEMS(sPSS_DefaultState);
}

static const u8 *ReturnPSS_ListDescription(u8 fillValue)
{
   // sPSS_DefaultState[task->tSelectedOption].desc
   if ((FlagGet(FLAG_TAUGHT_MOVE_DELETE) && FlagGet(FLAG_TAUGHT_MOVE_RELEARN)) || FlagGet(FLAG_NEW_GAME_PLUS))
        return sPSS_FinalState[fillValue].desc;    
    else if (FlagGet(FLAG_TAUGHT_MOVE_DELETE))
        return sPSS_State1[fillValue].desc;
    else if (FlagGet(FLAG_TAUGHT_MOVE_RELEARN))
        return sPSS_State2[fillValue].desc;
    else
        return sPSS_DefaultState[fillValue].desc;
}

static const struct PSS_MenuStringPtrs *ReturnPSSListArray_BasedOnState(void)
{
    if ((FlagGet(FLAG_TAUGHT_MOVE_DELETE) && FlagGet(FLAG_TAUGHT_MOVE_RELEARN)) || FlagGet(FLAG_NEW_GAME_PLUS))
        return sPSS_FinalState;    
    else if (FlagGet(FLAG_TAUGHT_MOVE_DELETE))
        return sPSS_State1;
    else if (FlagGet(FLAG_TAUGHT_MOVE_RELEARN))
        return sPSS_State2;
    else
        return sPSS_DefaultState;

}

static u8 CountMonsInBox(u8 boxId)
{
    u16 i, count;

    for (i = 0, count = 0; i < IN_BOX_COUNT; i++)
    {
        if (GetBoxMonDataAt(boxId, i, MON_DATA_SPECIES) != SPECIES_NONE)
            count++;
    }

    return count;
}

//vsonic use for press b while holding mon to put mon in space
s16 GetFirstFreeBoxSpot(u8 boxId)
{
    u16 i;

    for (i = 0; i < IN_BOX_COUNT; i++)
    {
        if (GetBoxMonDataAt(boxId, i, MON_DATA_SPECIES) == SPECIES_NONE)
            return i;
    }

    return -1; // all spots are taken
}

u8 CountPartyNonEggMons(void)
{
    u16 i, count;

    for (i = 0, count = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE
            && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
        {
            count++;
        }
    }

    return count;
}

u8 CountPartyAliveNonEggMonsExcept(u8 slotToIgnore)
{
    u16 i, count;

    for (i = 0, count = 0; i < PARTY_SIZE; i++)
    {
        if (i != slotToIgnore
            && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE
            && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)
            && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
        {
            count++;
        }
    }

    return count;
}

u16 CountPartyAliveNonEggMons_IgnoreVar0x8004Slot(void)
{
    return CountPartyAliveNonEggMonsExcept(gSpecialVar_0x8004);
}

u8 CountPartyMons(void)
{
    u16 i, count;

    for (i = 0, count = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE)
        {
            count++;
        }
    }

    return count;
}

static u8 *StringCopyAndFillWithSpaces(u8 *dst, const u8 *src, u16 n)
{
    u8 *str;

    for (str = StringCopy(dst, src); str < dst + n; str++)
        *str = CHAR_SPACE;

    *str = EOS;
    return str;
}

static void sub_808C25C(u16 *dest, u16 dest_left, u16 dest_top, const u16 *src, u16 src_left, u16 src_top, u16 dest_width, u16 dest_height, u16 src_width)
{
    u16 i;

    dest_width *= 2;
    dest += dest_top * 0x20 + dest_left;
    src += src_top * src_width + src_left;
    for (i = 0; i < dest_height; i++)
    {
        CpuCopy16(src, dest, dest_width);
        dest += 0x20;
        src += src_width;
    }
}

static void sub_808C2D8(u16 *dest, u16 dest_left, u16 dest_top, u16 width, u16 height)
{
    u16 i;

    dest += dest_top * 0x20 + dest_left;
    width *= 2;
    for (i = 0; i < height; dest += 0x20, i++)
        Dma3FillLarge16_(0, dest, width);
}

enum {
    STATE_LOAD,
    STATE_FADE_IN,
    STATE_HANDLE_INPUT,
    STATE_ERROR_MSG,
    STATE_ENTER_PC,
};

//references from pret,
//never undefined by on average
//end of use is around line 370
//can safely do a ranged selection to replace
#define tState          data[0]
#define tSelectedOption data[1]
#define tInput          data[2]
#define tNextOption     data[3]
#define tWindowId       data[15]
#define MORE_PCLOGIC
static void Task_PokemonStorageSystemPC(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
    case STATE_LOAD:
        //SetHelpContext(HELPCONTEXT_BILLS_PC);
        PSS_CreatePCMenu(task->tSelectedOption, &task->tWindowId);
        LoadStdWindowFrameGfx();
        DrawDialogueFrame(0, 0);
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        //think make a function to return pointer
        //of list I need to use same as other function
        AddTextPrinterParameterized2(0, 2, ReturnPSS_ListDescription(task->tSelectedOption), TEXT_SKIP_DRAW, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
        //AddTextPrinterParameterized2(0, 2, sPSS_DefaultState[task->tSelectedOption].desc, TEXT_SKIP_DRAW, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
        CopyWindowToVram(0, COPYWIN_BOTH);
        CopyWindowToVram(task->tWindowId, COPYWIN_BOTH);
        task->tState++;
        break;
    case STATE_FADE_IN:
        if (IsWeatherNotFadingIn())
        {
            task->tState++;
        }
        break;
    case STATE_HANDLE_INPUT:
        task->tInput = Menu_ProcessInput(); //ok think I found my problem, its going off of cursor position for input, and that's what sets boxoption
        switch(task->tInput)
        {
        case MENU_NOTHING_CHOSEN:
            task->tNextOption = task->tSelectedOption;
            if (JOY_NEW(DPAD_UP) && --task->tNextOption < 0)//I believe it is, think this should be size of list NELEMS(sPSS_DefaultState)
                task->tNextOption = (ReturnPSS_ListSizebyState() - 1);
                //task->tNextOption = 4; 

            //if (JOY_NEW(DPAD_DOWN) && ++task->tNextOption > 4) //find if this is related to size of list
            if (JOY_NEW(DPAD_DOWN) && ++task->tNextOption > (ReturnPSS_ListSizebyState() - 1)) //find if this is related to size of list
                task->tNextOption = 0;
            if (task->tSelectedOption != task->tNextOption)//if so think will make function to return correct size based on state
            {
                task->tSelectedOption = task->tNextOption;
                FillWindowPixelBuffer(0, PIXEL_FILL(1));
                AddTextPrinterParameterized2(0, 2, ReturnPSS_ListDescription(task->tSelectedOption), 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
                //AddTextPrinterParameterized2(0, 2, sPSS_DefaultState[task->tSelectedOption].desc, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            }
            break;
        case MENU_B_PRESSED:
            if (CountPartyMons() == 0) //
            {
                FillWindowPixelBuffer(0, PIXEL_FILL(1));
                AddTextPrinterParameterized2(0, 2, gText_NoPkmnInParty, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
                task->tState = 3;
            }//no break because I want fallthrough
        /*case  BOX_OPTION_EXIT:
            ClearStdWindowAndFrame(0, TRUE);
            ClearStdWindowAndFrame(task->tWindowId, TRUE);
            UnlockPlayerFieldControls();    //unlocks me
            EnableBothScriptContexts();     //...locks me again
            DestroyTask(taskId);//believe thsi is end of task, or one of them, so from here would end pss and go back to main pc menu
            break;*/
        default:    //these trigger on outside of pc menu,  think this is what I was looking for but this is for pressing A I want pressing B.
            if (task->tInput == MENU_B_PRESSED
            || task->tInput == (ReturnPSS_ListSizebyState() - 1))//ok awesome this worked, no longer need box_option_exit
            {
                ClearStdWindowAndFrame(0, TRUE);
                ClearStdWindowAndFrame(task->tWindowId, TRUE);
                UnlockPlayerFieldControls();    //unlocks me
                EnableBothScriptContexts();     //...locks me again
                DestroyTask(taskId);//believe thsi is end of task, or one of them, so from here would end pss and go back to main pc menu
                break;
            }
            else if (task->tInput == BOX_OPTION_WITHDRAW && CountPartyMons() == PARTY_SIZE) //I think numbers are for menu list, 0 is top, withdraw
            {
                FillWindowPixelBuffer(0, PIXEL_FILL(1));
                AddTextPrinterParameterized2(0, 2, gText_PartyFull, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
                task->tState = 3;
            }
            else if (task->tInput == BOX_OPTION_DEPOSIT && CountPartyMons() == 1)   //1 is middle deposit //hmm but this also works for move    prevents putting away last mon, remove this
            {
                FillWindowPixelBuffer(0, PIXEL_FILL(1));
                AddTextPrinterParameterized2(0, 2, gText_JustOnePkmn, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
                task->tState = 3;
            } //removing allows for depositing full party, still has issues to work out, code otherwhere,  that create a default question mark icon that doesn't track
            else //success condition access box
            {
                FadeScreen(FADE_TO_BLACK, 0);
                task->tState = 4;
            }
            break;
        }
        break;
    case STATE_ERROR_MSG:
        if (JOY_NEW(A_BUTTON | B_BUTTON))   //pressign A or B, after can't access box messages redisplays menu cursor options and goes back to case 2
        {
            FillWindowPixelBuffer(0, PIXEL_FILL(1));
            AddTextPrinterParameterized2(0, 2, ReturnPSS_ListDescription(task->tSelectedOption), 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            //AddTextPrinterParameterized2(0, 2, sPSS_DefaultState[task->tSelectedOption].desc, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            task->tState = 2;
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (--task->tSelectedOption < 0)
                task->tSelectedOption = (ReturnPSS_ListSizebyState() - 1);
                //task->tSelectedOption = 4;
            Menu_MoveCursor(-1);
            task->tSelectedOption = Menu_GetCursorPos();
            FillWindowPixelBuffer(0, PIXEL_FILL(1));
            AddTextPrinterParameterized2(0, 2, ReturnPSS_ListDescription(task->tSelectedOption), 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            //AddTextPrinterParameterized2(0, 2, sPSS_DefaultState[task->tSelectedOption].desc, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            task->tState = 2;
        }
        else if (JOY_NEW(DPAD_DOWN))
        {   
            //if (++task->tSelectedOption > 3)
            //double check this substittion see if this works
            if (++task->tSelectedOption > (ReturnPSS_ListSizebyState() - 2))
                task->tSelectedOption = 0;
            Menu_MoveCursor(1);
            task->tSelectedOption = Menu_GetCursorPos();
            FillWindowPixelBuffer(0, PIXEL_FILL(1));
            AddTextPrinterParameterized2(0, 2, ReturnPSS_ListDescription(task->tSelectedOption), 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            //AddTextPrinterParameterized2(0, 2, sPSS_DefaultState[task->tSelectedOption].desc, 0, NULL, TEXT_COLOR_DARK_GREY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GREY);
            task->tState = 2;
        }
        break;
    case STATE_ENTER_PC:
        if (!gPaletteFade.active)
        {
            CleanupOverworldWindowsAndTilemaps();
            Cb2_EnterPSS(task->tInput);
            DestroyTask(taskId);
        }
        break;
    }
}

void ShowPokemonStorageSystemPC(void)
{
    u8 taskId = CreateTask(Task_PokemonStorageSystemPC, 80);
    gTasks[taskId].tState = 0;
    gTasks[taskId].tSelectedOption = 0;
    LockPlayerFieldControls();
}

static void FieldCb_ReturnToPcMenu(void)
{
    u8 taskId;
    MainCallback vblankCb = gMain.vblankCallback;

    SetVBlankCallback(NULL);
    taskId = CreateTask(Task_PokemonStorageSystemPC, 80);   //reloads pss menu
    gTasks[taskId].tState = 0;
    gTasks[taskId].tSelectedOption = sPreviousBoxOption;    //returns cursor to box option initially clicked
    Task_PokemonStorageSystemPC(taskId);
    SetVBlankCallback(vblankCb);
    FadeInFromBlack();      //removes black screen, so everything is visible
}

//need template for each state w diff num entries
//4 states but only 3 different sizes as state1 and state2 are same num entires
//height is the only diff factor,
//default is 5 strings/list entires,
//so assuming value of 2 for each as default is 10
static const struct WindowTemplate sWindowTemplate_MainMenu_FinalState = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 17,
    .height = 10,
    .paletteNum = 15,
    .baseBlock = 0x001
};

static const struct WindowTemplate sWindowTemplate_MainMenu_MiddleState = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 17,
    .height = 8,
    .paletteNum = 15,
    .baseBlock = 0x001
};

static const struct WindowTemplate sWindowTemplate_MainMenu_DefaultState = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 17,
    .height = 6,
    .paletteNum = 15,
    .baseBlock = 0x001
};

static const struct WindowTemplate* ReturnWindowTemplateFromState(void)
{
    if ((FlagGet(FLAG_TAUGHT_MOVE_DELETE) && FlagGet(FLAG_TAUGHT_MOVE_RELEARN)) || FlagGet(FLAG_NEW_GAME_PLUS))
        return &sWindowTemplate_MainMenu_FinalState;    
    else if (FlagGet(FLAG_TAUGHT_MOVE_DELETE))
        return &sWindowTemplate_MainMenu_MiddleState;
    else if (FlagGet(FLAG_TAUGHT_MOVE_RELEARN))
        return &sWindowTemplate_MainMenu_MiddleState;
    else
        return &sWindowTemplate_MainMenu_DefaultState;
}


static void PSS_CreatePCMenu(u8 whichMenu, s16 *windowIdPtr)
{
    s16 windowId;
    //windowId = AddWindow(&sWindowTemplate_MainMenu_DefaultState);
    windowId = AddWindow(ReturnWindowTemplateFromState());

    DrawStdWindowFrame(windowId, FALSE);
    PrintTextArray(windowId, 2, GetMenuCursorDimensionByFont(2, 0), 2, 16, ReturnPSS_ListSizebyState(), (void *)ReturnPSSListArray_BasedOnState());
    Menu_InitCursor(windowId, 2, 0, 2, 16, ReturnPSS_ListSizebyState(), whichMenu);
    *windowIdPtr = windowId;
    //if (FlagGet(FLAG_START_OAK_RANCH_COUNTER) && gSaveBlock1Ptr->oakRanchStepCounter != 0)
    //    UpdatePokemonStorageSystemMonExp(); //forgot to set here to update when open pc
}

void Cb2_ExitPSS(void)  //exit box to return to pss menu
{
    sPreviousBoxOption = GetCurrentBoxOption();
    gFieldCallback = FieldCb_ReturnToPcMenu;
    if (CheckIfPcEmpty() && FlagGet(FLAG_START_OAK_RANCH_COUNTER)) //make only run loop check if pc empty and flag has been set before
    {
        FlagClear(FLAG_START_OAK_RANCH_COUNTER);
        gSaveBlock1Ptr->oakRanchStepCounter = 0;
    }
    else if (!(FlagGet(FLAG_START_OAK_RANCH_COUNTER)))
        FlagSet(FLAG_START_OAK_RANCH_COUNTER); //forgot need here to set counter, when depositing mon physically
    SetMainCallback2(CB2_ReturnToField);
}

void ResetPokemonStorageSystem(void)
{
    u16 boxId, boxPosition;

    SetCurrentBox(0);
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
            ZeroBoxMonAt(boxId, boxPosition);
    }
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        u8 *dest = StringCopy(GetBoxNamePtr(boxId), gText_Box);
        ConvertIntToDecimalStringN(dest, boxId + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
    }
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        SetBoxWallpaper(boxId, boxId % 4);
    }
}

//main call function put in close pc logic
//for check if shuold reset oakranch counter, if functino return true clear flag and reset counter
u8 CheckIfPcEmpty(void)
{
    u16 boxId, boxPosition;
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            if ((GetBoxMonDataAt(boxId,boxPosition, MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE)
            && (GetBoxMonDataAt(boxId,boxPosition, MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG))
                return FALSE;
        }
    }

    return TRUE;
}

//need setup function for clearing and starting stepcounter, 
//if there are no mon in pc clear counter and stop incrementing
//also need to start counter soon as first mon goes into pc
//so think set flag when catch mon that goes to pc for first time
//that will start counter auto,
//this function below should be run soon as you boot up a pc /not player pc
//and think I can run couter state update funtion when you close pc

//plan make command to run this
//to have more control over where I run it,
//could hide in sound effect etc.
//MGriffin had idea to make version that is a task
//that I could run to do a box over a number of frames
//would allow me to do exp setting on scroll over would just need to lock player movement until its done
//so can't select mon.
//for first box would need to load as pc opens, but other than that,
//can run it on scroll over
//could get complex with having to store which mon/boxes were affected before exit
//since would need to ensure run exp update on all boxes that have mon but weren't checked
//on exit would just be on the fade screen so would work fine
//would be complex but prob most efficient thing
//would need be like pokedex screen where a data array
//is set to store all teh possible values, in this case max boxes
//when open on pc, run box 0, and set box0 as run.
//store which are already run, change on scroll over
//then when close loop all box slots, if not run update on box
//run the exp set and then reset counter to 0
//would still need to use this version of  function/cmd for mon catching
//but can prob disguise it inside the sound effect that plays when having caught a mon
void UpdatePokemonStorageSystemMonExp(void)
{
    u16 boxId, boxPosition;
    
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++) //put species filter in, on adisement to hopefully cut down unnecessary processing
        {
            struct BoxPokemon * checkingMon = GetBoxedMonPtr(boxId, boxPosition); //need within loop so updates
            u32 species = GetBoxMonData(checkingMon, MON_DATA_SPECIES);

            if (species == SPECIES_NONE || species == SPECIES_EGG) continue;


            BoxMonAtGainExp(checkingMon, species, CanBoxMonGainExp(checkingMon, species)); //for level cap use num badges with mon level  /if (GetMonData(&dst, MON_DATA_LEVEL) <= 40)

            /*if (CanBoxMonGainExp(checkingMon, species))
            {
                //should mon gain exp (checkingMon) //for most part isn't an issue until safrom, the game is wide open then, so that's where I need the cap
                //just need cap not be higher than sabrina ace by much so, <= 6 badges level not greater than 41 I guess
                //if (CanBoxMonGainExp(checkingMon))
                    
            }   */             
            
        }
            
    }
    gSaveBlock1Ptr->oakRanchStepCounter = 0; //after give exp reset counter
}
//pretty sure issue is doing dopuble loop
//if I get a bit creative and do double assignments
//I THINK I can make less costly by doing the same thing
//within one for lopop
//ok for loop would be same thing but if I do a do while?
//that would let me set conditionals and do what I need

//mcgriphin sylph is in,
//mentioned multiple things using boxmon for I didn't need to,
//and could calk level from experience and growth rate so think chage this to take species

//could turn this into a u32 and make it return exp and pass to BoxMonAtGainExp
//to reduce need to call getboxmon again
//would just need to change BoxMonAtGainExp to take currExp
u32 CanBoxMonGainExp(struct BoxPokemon *mon, u16 species) //lvl cap works - didnt actually work before, badge count function was off, but now is correct
{
    //struct Pokemon dst;
    //BoxMonToMon(mon, &dst); //num badge function is countering wrong after getting brock badge its returning 0
    bool8 Blocked = FALSE;
    u32 experience = GetBoxMonData(mon, MON_DATA_EXP);
    //u32 level;
    //can use getmondata experience loop level
    //compare actual experience if experience is equal break return level
    //if experience is less, break return level - 1
    //gExperienceTables[gBaseStats[species].growthRate][level]

    //if (experience <= gExperienceTables[gBaseStats[species].growthRate][12])

    if (GetBoxMonData(mon, MON_DATA_BLOCK_BOX_EXP_GAIN))   
        return FALSE;

    if (GetNumberofBadges() < 1 && (experience < gExperienceTables[gBaseStats[species].growthRate][12])) //mostly just for pidgey, shuold be before first badge
        return experience; //to ensure non  0
     //if num badges <= 6 and mon level <= 41  yes else no
    else if (GetNumberofBadges() <= 6
    && (experience < gExperienceTables[gBaseStats[species].growthRate][41])) //should freeze box exp gain at lvl 41 until you get sabrina's badge
        return experience;
    else if (GetNumberofBadges() > 6) //think thsi should be fine, game opens up adn you can go to either koga sabrina or blaine
        return experience;  //but can't do erika until after sabrina and rocket stuff
    else
        return FALSE;
}

void LoadBoxSelectionPopupSpriteGfx(struct ChooseBoxMenu *a0, u16 tileTag, u16 palTag, u8 a3, bool32 loadPal)
{
    struct SpritePalette palette = {
        sBoxSelectionPopupPalette, palTag
    };
    struct SpriteSheet sheets[] = {
        {sBoxSelectionPopupCenterTiles, 0x800, tileTag},
        {sBoxSelectionPopupSidesTiles,  0x180, tileTag + 1},
        {}
    };

    if (loadPal)
        LoadSpritePalette(&palette);

    LoadSpriteSheets(sheets);
    sBoxSelectionPopupSpriteManager = a0;
    a0->tilesTag = tileTag;
    a0->paletteTag = palTag;
    a0->subpriority = a3;
    a0->loadPal = loadPal;
}

void FreeBoxSelectionPopupSpriteGfx(void)
{
    if (sBoxSelectionPopupSpriteManager->loadPal)
        FreeSpritePaletteByTag(sBoxSelectionPopupSpriteManager->paletteTag);
    FreeSpriteTilesByTag(sBoxSelectionPopupSpriteManager->tilesTag);
    FreeSpriteTilesByTag(sBoxSelectionPopupSpriteManager->tilesTag + 1);
}

void CreateChooseBoxMenuSprites(u8 curBox)
{
    sub_808C9C4(curBox);
}

void DestroyChooseBoxMenuSprites(void)
{
    sub_808CBA4();
}

u8 HandleBoxChooseSelectionInput(void)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        return 201;
    }
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        return sBoxSelectionPopupSpriteManager->curBox;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        PlaySE(SE_SELECT);
        UpdateBoxNameAndCountSprite_WraparoundLeft();
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        UpdateBoxNameAndCountSprite_WraparoundRight();
    }
    return 200;
}

static const union AnimCmd gUnknown_83CDA50[] = {
    ANIMCMD_FRAME( 0, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_83CDA58[] = {
    ANIMCMD_FRAME( 4, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_83CDA60[] = {
    ANIMCMD_FRAME( 6, 5),
    ANIMCMD_END
};

static const union AnimCmd gUnknown_83CDA68[] = {
    ANIMCMD_FRAME(10, 5),
    ANIMCMD_END
};

static const union AnimCmd *const gUnknown_83CDA70[] = {
    gUnknown_83CDA50,
    gUnknown_83CDA58,
    gUnknown_83CDA60,
    gUnknown_83CDA68
};

static const union AffineAnimCmd gUnknown_83CDA80[] = {
    AFFINEANIMCMD_FRAME(224, 224, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const gUnknown_83CDA90[] = {
    gUnknown_83CDA80
};

static void sub_808C9C4(u8 curBox)
{
    u16 i;
    u8 spriteId;
    struct SpriteTemplate template;
    struct OamData oamData = {};
    oamData.size = SPRITE_SIZE(64x64);
    oamData.paletteNum = 1;
    template = (struct SpriteTemplate){
        0, 0, &oamData, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy
    };
    {
    const u8 gUnknown_83CDA94[] = _("/30");

    sBoxSelectionPopupSpriteManager->curBox = curBox;
    template.tileTag = sBoxSelectionPopupSpriteManager->tilesTag;
    template.paletteTag = sBoxSelectionPopupSpriteManager->paletteTag;

    spriteId = CreateSprite(&template, 160, 96, 0);
    sBoxSelectionPopupSpriteManager->unk_0000 = gSprites + spriteId;

    // Manual subsprites
    oamData.shape = SPRITE_SHAPE(8x32);
    oamData.size = SPRITE_SIZE(8x32);
    template.tileTag = sBoxSelectionPopupSpriteManager->tilesTag + 1;
    template.anims = gUnknown_83CDA70;
    for (i = 0; i < 4; i++)
    {
        u16 r5;
        spriteId = CreateSprite(&template, 124, 80, sBoxSelectionPopupSpriteManager->subpriority);
        sBoxSelectionPopupSpriteManager->unk_0004[i] = gSprites + spriteId;
        r5 = 0;
        if (i & 2)
        {
            sBoxSelectionPopupSpriteManager->unk_0004[i]->pos1.x = 196;
            r5 = 2;
        }
        if (i & 1)
        {
            sBoxSelectionPopupSpriteManager->unk_0004[i]->pos1.y = 112;
            sBoxSelectionPopupSpriteManager->unk_0004[i]->oam.size = SPRITE_SIZE(8x16);
            r5++;
        }
        StartSpriteAnim(sBoxSelectionPopupSpriteManager->unk_0004[i], r5);
    }
    for (i = 0; i < 2; i++)
    {
        sBoxSelectionPopupSpriteManager->unkUtil[i] = sub_809223C(72 * i + 0x7c, 0x58, i, 0, sBoxSelectionPopupSpriteManager->subpriority);
        if (sBoxSelectionPopupSpriteManager->unkUtil[i])
        {
            sBoxSelectionPopupSpriteManager->unkUtil[i]->data[0] = (i == 0 ? -1 : 1);
            sBoxSelectionPopupSpriteManager->unkUtil[i]->callback = sub_808CD64;
        }
    }
    PrintBoxNameAndCountToSprite();
    PrintToSpriteWithTagUnk0240(gUnknown_83CDA94, 5, 3);
    }
}

static void sub_808CBA4(void)
{
    u16 i;
    if (sBoxSelectionPopupSpriteManager->unk_0000)
    {
        DestroySprite(sBoxSelectionPopupSpriteManager->unk_0000);
        sBoxSelectionPopupSpriteManager->unk_0000 = NULL;
    }
    for (i = 0; i < 4; i++)
    {
        if (sBoxSelectionPopupSpriteManager->unk_0004[i])
        {
            DestroySprite(sBoxSelectionPopupSpriteManager->unk_0004[i]);
            sBoxSelectionPopupSpriteManager->unk_0004[i] = NULL;
        }
    }
    for (i = 0; i < 2; i++)
    {
        if (sBoxSelectionPopupSpriteManager->unkUtil[i])
            DestroySprite(sBoxSelectionPopupSpriteManager->unkUtil[i]);
    }
}

static void UpdateBoxNameAndCountSprite_WraparoundRight(void)
{
    if (++sBoxSelectionPopupSpriteManager->curBox >= TOTAL_BOXES_COUNT)
        sBoxSelectionPopupSpriteManager->curBox = 0;
    PrintBoxNameAndCountToSprite();
}

static void UpdateBoxNameAndCountSprite_WraparoundLeft(void)
{
    sBoxSelectionPopupSpriteManager->curBox = (sBoxSelectionPopupSpriteManager->curBox == 0 ? TOTAL_BOXES_COUNT - 1 : sBoxSelectionPopupSpriteManager->curBox - 1);
    PrintBoxNameAndCountToSprite();
}

static void PrintBoxNameAndCountToSprite(void)
{
    u8 nPokemonInBox = CountMonsInBox(sBoxSelectionPopupSpriteManager->curBox);
    u8 *boxName = StringCopy(sBoxSelectionPopupSpriteManager->strbuf, GetBoxNamePtr(sBoxSelectionPopupSpriteManager->curBox));

    while (boxName < sBoxSelectionPopupSpriteManager->strbuf + BOX_NAME_LENGTH)
        *boxName++ = CHAR_SPACE;
    *boxName = EOS;

    PrintToSpriteWithTagUnk0240(sBoxSelectionPopupSpriteManager->strbuf, 0, 1);

    ConvertIntToDecimalStringN(sBoxSelectionPopupSpriteManager->strbuf, nPokemonInBox, STR_CONV_MODE_RIGHT_ALIGN, 2);

    PrintToSpriteWithTagUnk0240(sBoxSelectionPopupSpriteManager->strbuf, 3, 3);
}

static void PrintToSpriteWithTagUnk0240(const u8 *str, u16 x, u16 y)
{
    u16 tileStart = GetSpriteTileStartByTag(sBoxSelectionPopupSpriteManager->tilesTag);
    PrintStringToBufferCopyNow(str, (void *)(OBJ_VRAM0 + tileStart * 32 + 256 * y + 32 * x), 0x100, TEXT_COLOR_RED, TEXT_DYNAMIC_COLOR_6, TEXT_DYNAMIC_COLOR_5, sBoxSelectionPopupSpriteManager->buffer);
}

static void sub_808CD64(struct Sprite *sprite)
{
    if (++sprite->data[1] > 3)
    {
        sprite->data[1] = 0;
        sprite->pos2.x += sprite->data[0];
        if (++sprite->data[2] > 5)
        {
            sprite->data[2] = 0;
            sprite->pos2.x = 0;
        }
    }
}

// Forward-declared rodata

static const u16 sBoxSelectionPopupPalette[] = INCBIN_U16("graphics/interface/pss_unk_83CDA98.gbapal");
static const u16 sBoxSelectionPopupCenterTiles[] = INCBIN_U16("graphics/interface/pss_unk_83CDAB8.4bpp");
static const u16 sBoxSelectionPopupSidesTiles[] = INCBIN_U16("graphics/interface/pss_unk_83CE2B8.4bpp");
