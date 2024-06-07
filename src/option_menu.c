#include "global.h"
#include "gflib.h"
#include "scanline_effect.h"
#include "text_window_graphics.h"
#include "menu.h"
#include "task.h"
#include "event_data.h" //for flag get/set
#include "overworld.h"
#include "help_system.h"
#include "text_window.h"
#include "strings.h"
#include "field_fadetransition.h"
#include "gba/m4a_internal.h"

// can't include the one in menu_helpers.h since Task_OptionMenu needs bool32 for matching
bool32 MenuHelpers_CallLinkSomething(void);


enum MainOptionsMenu
{
    MAIN_MENU_GAME_OPTIONS = 0,
    MAIN_MENU_TEXT_OPTIONS,
    MAIN_MENU_MISC_OPTIONS,
    MAIN_MENU_CANCEL,
    MAIN_MENU_COUNT
};

// Menu items - split these off
enum    GameOptions
{
    GAME_MENUITEM_TEXTSPEED = 0,
    GAME_MENUITEM_BATTLESCENE,
    GAME_MENUITEM_BATTLESTYLE,
    GAME_MENUITEM_SOUND,
    GAME_MENUITEM_BUTTONMODE,
    GAME_MENUITEM_FRAMETYPE,
    
    GAME_MENUITEM_CANCEL,
    GAME_MENUITEM_COUNT
};

enum TextOptions //I have space to add battle speed up option here, could just change to Misc. option
{
    TEXT_MENUITEM_CAP_SPECIES,
    TEXT_MENUITEM_CAP_ABILITY,
    TEXT_MENUITEM_CAP_MOVES,
    TEXT_MENUITEM_CAP_ITEMS,
    TEXT_MENUITEM_CAP_PLACEHOLDERS, //misc cap, but more descriptive
    
    TEXT_MENUITEM_CANCEL,
    TEXT_MENUITEM_COUNT
};//change back to text, but still add misc options field

enum MiscOptions
{   MISC_MENUITEM_EVENT_SPEEDUP,
    MISC_MENUITEM_BATTLE_SPEED,
    MISC_MENUITEM_NUZLOCKE_MODE,
    MISC_MENUITEM_CANCEL,
    MISC_MENUITEM_COUNT
};

#define MAX_OPTIONS_ON_SCREEN 6 //to not need scroll/fit properly cancel must be 6 max

//for binary state  (text options)
enum
{
    OFF,
    ON
};

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

//enum subs to stand in for menu type
enum MenuCat
{
    MAIN_MENU,
    GAME_OPTIONS,
    TEXT_OPTIONS,
    MISC_OPTIONS,

};

// RAM symbols
struct OptionMenu
{
    /*0x00*/ u16 MainOptionsMenu[MAIN_MENU_COUNT]; //hopefuly not a problem, num options will be up to that, but change with menu cat -main menu
             u16 GameOptions[GAME_MENUITEM_COUNT];
             u16 TextOptions[TEXT_MENUITEM_COUNT];
             u16 MiscOptions[MISC_MENUITEM_COUNT];
    /*0x0E*/ u16 cursorPos;
    /*0x10*/ u8 loadState;
    /*0x11*/ u8 state;
    /*0x12*/ u8 loadPaletteState;
             u8 MenuCategory; //to differentiate which menu I'm in
};

static EWRAM_DATA struct OptionMenu *sOptionMenuPtr = NULL;

#define Y_DIFF 16 // Difference in pixels between items.

#define NUM_OPTIONS_FROM_BORDER 1

//Function Declarataions
static void CB2_InitOptionMenu(void);
static void VBlankCB_OptionMenu(void);
static void OptionMenu_InitCallbacks(void);
static void OptionMenu_SetVBlankCallback(void);
static void CB2_OptionMenu(void);
static void SetOptionMenuTask(void);
static void InitOptionMenuBg(void);
static void OptionMenu_PickSwitchCancel(void);
static void OptionMenu_ResetSpriteData(void);
static bool8 LoadOptionMenuPalette(void);
static void Task_OptionMenu(u8 taskId);
static u8 OptionMenu_ProcessInput(void);
static void BufferOptionMenuString(u8 selection);
static void CloseAndSaveOptionMenu(u8 taskId);
static void PrintOptionMenuHeader(void);
static void DrawOptionMenuBg(void);
static void LoadOptionMenuItemNames(void);
static void UpdateSettingSelectionDisplay(u16 selection);

static void UpdateSettingDecapSpecies(u8 selection);
static void UpdateSettingDecapAbility(u8 selection);
static void UpdateSettingDecapMoves(u8 selection);
static void UpdateSettingDecapItem(u8 selection);
static void UpdateSettingDecapMisc(u8 selection);


// Data Definitions
static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 7,
        .width = 26,
        .height = 12,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    {
        .bg = 2,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 0xF,
        .baseBlock = 0x16e
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
   {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   },
   {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 2,
       .charBaseIndex = 1,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
       .baseTile = 0
   },
};

static const u16 sOptionMenuPalette[] = INCBIN_U16("graphics/misc/unk_83cc2e4.gbapal");

static const u8 *const sMainOptionMenuItemsNames[MAIN_MENU_COUNT] = 
{
    [MAIN_MENU_GAME_OPTIONS]    =  gText_GameOptions,
    [MAIN_MENU_TEXT_OPTIONS]    =  gText_TextOptions,
    [MAIN_MENU_MISC_OPTIONS]    =  gText_MiscOptions,
    [MAIN_MENU_CANCEL]          =  gText_OptionMenuCancel,
};

static const u16 sMainOptionMenuItemCounts[MAIN_MENU_COUNT] =
{
    [MAIN_MENU_GAME_OPTIONS]    =  0,
    [MAIN_MENU_TEXT_OPTIONS]    =  0,
    [MAIN_MENU_MISC_OPTIONS]    =  0,
    [MAIN_MENU_CANCEL]          =  0,
};


static const u16 sGameOptionMenuItemCounts[GAME_MENUITEM_COUNT] = 
{
    [GAME_MENUITEM_TEXTSPEED]        = 5, 
    [GAME_MENUITEM_BATTLESCENE]      = 2, 
    [GAME_MENUITEM_BATTLESTYLE]      = 2, 
    [GAME_MENUITEM_SOUND]            = 2, 
    [GAME_MENUITEM_BUTTONMODE]       = 3, 
    [GAME_MENUITEM_FRAMETYPE]        = 10, 
    [GAME_MENUITEM_CANCEL]           = 0
};//num menu options for each category on/off is 2

static const u16 sTextOptionsMenuItemCounts[TEXT_MENUITEM_COUNT] =
{
    [TEXT_MENUITEM_CAP_SPECIES]      = 2,
    [TEXT_MENUITEM_CAP_ABILITY]      = 2,
    [TEXT_MENUITEM_CAP_MOVES]        = 2,
    [TEXT_MENUITEM_CAP_ITEMS]        = 2,
    [TEXT_MENUITEM_CAP_PLACEHOLDERS] = 2,
   
    [TEXT_MENUITEM_CANCEL]           = 0
};

static const u16 sMiscOptionsMenuItemCounts[TEXT_MENUITEM_COUNT] =
{
    [MISC_MENUITEM_EVENT_SPEEDUP]     = 2, //OFF - ON
    [MISC_MENUITEM_BATTLE_SPEED]     = 4, //1x - 4x
    [MISC_MENUITEM_NUZLOCKE_MODE]   = 2, //OFF - ON

    [MISC_MENUITEM_CANCEL]          = 0,
};

static const u8 *const sGameOptionMenuItemsNames[GAME_MENUITEM_COUNT] =
{
    [GAME_MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [GAME_MENUITEM_BATTLESCENE] = gText_BattleScene,
    [GAME_MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [GAME_MENUITEM_SOUND]       = gText_Sound,
    [GAME_MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [GAME_MENUITEM_FRAMETYPE]   = gText_Frame,


    [GAME_MENUITEM_CANCEL]      = gText_OptionMenuCancel,
};

static const u8 *const sTextOptionMenuItemsNames[TEXT_MENUITEM_COUNT] =
{
    [TEXT_MENUITEM_CAP_SPECIES]      = gText_SpeciesCap,
    [TEXT_MENUITEM_CAP_ABILITY]      = gText_AbilityCap,
    [TEXT_MENUITEM_CAP_MOVES]        = gText_MoveCap,
    [TEXT_MENUITEM_CAP_ITEMS]        = gText_ItemCap,
    [TEXT_MENUITEM_CAP_PLACEHOLDERS] = gText_MiscPlaceholderCap,
    [TEXT_MENUITEM_CANCEL]           = gText_OptionMenuCancel,
};

static const u8 *const sMiscOptionMenuItemsNames[MISC_MENUITEM_COUNT] =
{
    [MISC_MENUITEM_EVENT_SPEEDUP]     = gText_EventSpeedup,
    [MISC_MENUITEM_BATTLE_SPEED]      = gText_BattleSpeed,
    [MISC_MENUITEM_NUZLOCKE_MODE]     = gText_NuzlockeMode,
    [MISC_MENUITEM_CANCEL]            = gText_OptionMenuCancel,
};

static const u8 *const sTextSpeedOptions[] =
{
    gText_TextSpeedSlow, 
    gText_TextSpeedMid, 
    gText_TextSpeedFast,
    gText_TextSpeedFaster,
    gText_TextSpeedHyperFast
};

static const u8 *const sBattleSpeedOptions[] =
{
    COMPOUND_STRING("1x"),
    COMPOUND_STRING("2x"),
    COMPOUND_STRING("3x"),
    COMPOUND_STRING("4x")
};

static const u8 *const sBattleSceneOptions[] =
{
    gText_BattleSceneOn, 
    gText_BattleSceneOff
};

//this was the problem FACEPALM, on off from battle scene was reversed, because 
//the save block for that is reversed cuz its calling battle scene off = false, to turn it on
static const u8 *const sTextCapOptions[] =
{
    gText_BattleSceneOff,
    gText_BattleSceneOn, 
};

static const u8 *const sBattleStyleOptions[] =
{
    gText_BattleStyleShift,
    gText_BattleStyleSet
};

static const u8 *const sSoundOptions[] =
{
    gText_SoundMono, 
    gText_SoundStereo
};

static const u8 *const sButtonTypeOptions[] =
{
    gText_ButtonTypeHelp,
	gText_ButtonTypeLR,
	gText_ButtonTypeLEqualsA
};

static const u8 sOptionMenuPickSwitchCancelTextColor[] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GREY};
static const u8 sOptionMenuTextColor[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED, TEXT_COLOR_RED};

// Functions
static void CB2_InitOptionMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_OptionMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

//vsonic
void CB2_OptionsMenuFromStartMenu(void)
{
    u8 i;
    
    if (gMain.savedCallback == CB2_ReturnToFieldWithOpenMenu)
        sOptionMenuPtr = AllocZeroed(sizeof(struct OptionMenu));  //its this that sets all to 0, making  cat default to main 
    
    //callback is already set when it gets here
    //its CB2_ReturnToFieldWithOpenMenu  this is just a safety net
    if (gMain.savedCallback == NULL)//optionmenuptr starts at null so don't need to set menucat to 0
    {
        gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
        
    }      
    

    sOptionMenuPtr->loadState = 0;
    sOptionMenuPtr->loadPaletteState = 0;
    sOptionMenuPtr->state = 0;
    //sOptionMenuPtr->cursorPos = 0;

    //these should stay here, this is populating the base value/cursor position for each menu option
    //not printing them
    sOptionMenuPtr->GameOptions[GAME_MENUITEM_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
    sOptionMenuPtr->GameOptions[GAME_MENUITEM_BATTLESCENE] = gSaveBlock2Ptr->optionsBattleSceneOff;
    sOptionMenuPtr->GameOptions[GAME_MENUITEM_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
    sOptionMenuPtr->GameOptions[GAME_MENUITEM_SOUND] = gSaveBlock2Ptr->optionsSound;
    sOptionMenuPtr->GameOptions[GAME_MENUITEM_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
    sOptionMenuPtr->GameOptions[GAME_MENUITEM_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;
    
    sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_SPECIES] = FlagGet(FLAG_CAPITALIZE_SPECIES_TEXT);
    sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_ABILITY] = FlagGet(FLAG_CAPITALIZE_ABILITY_TEXT);
    sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_MOVES] = FlagGet(FLAG_CAPITALIZE_MOVE_TEXT);
    sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_ITEMS] = FlagGet(FLAG_CAPITALIZE_ITEM_TEXT);
    sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_PLACEHOLDERS] = FlagGet(FLAG_CAPITALIZE_MISC_PLACEHOLDER);
    
    sOptionMenuPtr->MiscOptions[MISC_MENUITEM_EVENT_SPEEDUP] = gSaveBlock2Ptr->optionsEventSpeedup;
    sOptionMenuPtr->MiscOptions[MISC_MENUITEM_BATTLE_SPEED] = gSaveBlock2Ptr->optionsBattleSpeed;
    sOptionMenuPtr->MiscOptions[MISC_MENUITEM_NUZLOCKE_MODE] = gSaveBlock2Ptr->optionsNuzlockeMode;
    
    switch (sOptionMenuPtr->MenuCategory)
    {
        case GAME_OPTIONS:
            for (i = 0; i < GAME_MENUITEM_COUNT - 1; i++)
            {
                if (sOptionMenuPtr->GameOptions[i] > (sGameOptionMenuItemCounts[i]) - 1)
                    sOptionMenuPtr->GameOptions[i] = 0;
            }
        break;
        case TEXT_OPTIONS:
            for (i = 0; i < TEXT_MENUITEM_COUNT - 1; i++)
            {
                if (sOptionMenuPtr->TextOptions[i] > (sTextOptionsMenuItemCounts[i]) - 1)
                    sOptionMenuPtr->TextOptions[i] = 0; 
            }
        break;
        case MISC_OPTIONS:
            for (i = 0; i < MISC_MENUITEM_COUNT - 1; i++)
            {
                if (sOptionMenuPtr->MiscOptions[i] > (sMiscOptionsMenuItemCounts[i]) - 1)
                    sOptionMenuPtr->MiscOptions[i] = 0; 
            }
        break;
    }

    SetHelpContext(HELPCONTEXT_OPTIONS);
    SetMainCallback2(CB2_OptionMenu); 
}

static void OptionMenu_InitCallbacks(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

static void OptionMenu_SetVBlankCallback(void)
{
    SetVBlankCallback(VBlankCB_OptionMenu);
}

//vsonic
static void CB2_OptionMenu(void)
{
    u8 i, state;
    u8 Menu_Count = 0;
    state = sOptionMenuPtr->state;

    switch (sOptionMenuPtr->MenuCategory)
    {
        case MAIN_MENU:
            Menu_Count = MAIN_MENU_COUNT;
        break;
        case GAME_OPTIONS:
            Menu_Count = GAME_MENUITEM_COUNT;
        break;
        case TEXT_OPTIONS:
            Menu_Count = TEXT_MENUITEM_COUNT;
        break;
        case MISC_OPTIONS:
            Menu_Count = MISC_MENUITEM_COUNT;
        break;
    }

    switch (state)
    {
    case 0:
        OptionMenu_InitCallbacks();
        break;
    case 1:
        InitOptionMenuBg();
        break;
    case 2:
        OptionMenu_ResetSpriteData();
        break;
    case 3:
        if (LoadOptionMenuPalette() != TRUE)
            return;
        break;
    case 4:
        PrintOptionMenuHeader(); 
        break;
    case 5:
        DrawOptionMenuBg();
        break;
    case 6:
        LoadOptionMenuItemNames(); 
        break;
    case 7:
        for (i = 0; i < Menu_Count; i++) 
            BufferOptionMenuString(i); //this is more important thatn above as this puts the tilemap done to make visiible
        break;
    case 8:
        UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
        break;
    case 9:
        OptionMenu_PickSwitchCancel(); 
        break;
    default:
        SetOptionMenuTask(); //guess with below increment it goes through all these?
		break;
    }
    sOptionMenuPtr->state++;
}

static void SetOptionMenuTask(void)
{
    CreateTask(Task_OptionMenu, 0);
    SetMainCallback2(CB2_InitOptionMenu);
}

static void InitOptionMenuBg(void)
{
    void * dest = (void *)VRAM;
    DmaClearLarge16(3, dest, VRAM_SIZE, 0x1000);    
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);    
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sOptionMenuBgTemplates, NELEMS(sOptionMenuBgTemplates));
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    InitWindows(sOptionMenuWinTemplates);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_EFFECT_LIGHTEN);
    SetGpuReg(REG_OFFSET_BLDY, BLDCNT_TGT1_BG1);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_CLR);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
};

static void OptionMenu_PickSwitchCancel(void) 
{
    s32 x;

    x = 0xE4 - GetStringWidth(0, gText_PickSwitchCancel, 0);
    FillWindowPixelBuffer(2, PIXEL_FILL(15)); 
    if (sOptionMenuPtr->MenuCategory != MAIN_MENU)
        AddTextPrinterParameterized3(2, 0, x, 0, sOptionMenuPickSwitchCancelTextColor, 0, gText_PickSwitchCancel);
    PutWindowTilemap(2);
    CopyWindowToVram(2, COPYWIN_BOTH);

}

static void OptionMenu_ResetSpriteData(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

static bool8 LoadOptionMenuPalette(void)
{
    switch (sOptionMenuPtr->loadPaletteState)
    {
    case 0:
        LoadBgTiles(1, GetUserFrameGraphicsInfo(sOptionMenuPtr->GameOptions[GAME_MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
        break;
    case 1:
        LoadPalette(GetUserFrameGraphicsInfo(sOptionMenuPtr->GameOptions[GAME_MENUITEM_FRAMETYPE])->palette, 0x20, 0x20);
        break;
    case 2:
        LoadPalette(sOptionMenuPalette, 0x10, 0x20);
        LoadPalette(stdpal_get(2), 0xF0, 0x20);
        break;
    case 3:
        DrawWindowBorderWithStdpal3(1, 0x1B3, 0x30);
        break;
    default:
        return TRUE;
    }
    sOptionMenuPtr->loadPaletteState++;
    return FALSE;
}

static void Task_OptionMenu(u8 taskId)
{
    switch (sOptionMenuPtr->loadState)
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0x10, 0, RGB_BLACK);
        OptionMenu_SetVBlankCallback();
        sOptionMenuPtr->loadState++;
        break;
    case 1:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 2:
        if (((bool32)MenuHelpers_CallLinkSomething()) == TRUE)
            break;
        
        switch (OptionMenu_ProcessInput())
        {
        case 0:
            break;
        case 1:
            sOptionMenuPtr->loadState++;
            break;
        case 2:
            LoadBgTiles(1, GetUserFrameGraphicsInfo(sOptionMenuPtr->GameOptions[GAME_MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
            LoadPalette(GetUserFrameGraphicsInfo(sOptionMenuPtr->GameOptions[GAME_MENUITEM_FRAMETYPE])->palette, 0x20, 0x20);
            BufferOptionMenuString(sOptionMenuPtr->cursorPos);
            break;
        case 3:
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            break;
        case 4:
            BufferOptionMenuString(sOptionMenuPtr->cursorPos);
            break;
        case 5:
            SetMainCallback2(CB2_OptionsMenuFromStartMenu);
            FreeAllWindowBuffers();
            break;
        } //process input end switch

        break; //break for case 2 of main switch
    case 3:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        sOptionMenuPtr->loadState++;
        break;
    case 4:
        if (gPaletteFade.active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 5:
        CloseAndSaveOptionMenu(taskId);
        break;
    }
}

static u8 OptionMenu_ProcessInput(void)
{ 
    u16 current;
    u16* curr;

    switch (sOptionMenuPtr->MenuCategory)
    {
        case MAIN_MENU:
            if (JOY_REPT(DPAD_UP)) //this is the important part that allows it to  skip from bottom to top, if its juist process input, put  in dex and store as well  vsonic
            {
                if (sOptionMenuPtr->cursorPos == MAIN_MENU_GAME_OPTIONS)
                    sOptionMenuPtr->cursorPos = MAIN_MENU_CANCEL;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
                return 3;        
            }
            else if (JOY_REPT(DPAD_DOWN))
            {
                if (sOptionMenuPtr->cursorPos == MAIN_MENU_CANCEL)
                    sOptionMenuPtr->cursorPos = MAIN_MENU_GAME_OPTIONS;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
                return 3;
            }
            else if (JOY_NEW(A_BUTTON)) 
            {
                if (sOptionMenuPtr->cursorPos == MAIN_MENU_GAME_OPTIONS)
                {
                    sOptionMenuPtr->cursorPos = 0;
                    sOptionMenuPtr->MenuCategory = GAME_OPTIONS;
                    gMain.savedCallback = NULL;  //to ensure doesn't reset menu cat on callback
                    return 5; 
                }
                else if (sOptionMenuPtr->cursorPos == MAIN_MENU_TEXT_OPTIONS)
                {
                    sOptionMenuPtr->cursorPos = 0;
                    sOptionMenuPtr->MenuCategory = TEXT_OPTIONS;
                    gMain.savedCallback = NULL;  //to ensure doesn't reset menu cat on callback
                    return 5;
                }
                else if (sOptionMenuPtr->cursorPos == MAIN_MENU_MISC_OPTIONS)
                {
                    sOptionMenuPtr->cursorPos = 0;
                    sOptionMenuPtr->MenuCategory = MISC_OPTIONS;
                    gMain.savedCallback = NULL;  //to ensure doesn't reset menu cat on callback
                    return 5;
                }
                else
                    return 1;
                
            }    
            else if (JOY_NEW(B_BUTTON))
            {
                return 1;   //fade close menu go to closesavemenu exit
            }
            else
            {
                return 0; //do nothing
            }
        break;
        case GAME_OPTIONS:
            if (JOY_REPT(DPAD_RIGHT))
            {
                current = sOptionMenuPtr->GameOptions[(sOptionMenuPtr->cursorPos)];
                if (current == (sGameOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1))
                    sOptionMenuPtr->GameOptions[sOptionMenuPtr->cursorPos] = 0;
                else
                    sOptionMenuPtr->GameOptions[sOptionMenuPtr->cursorPos] = current + 1;
                if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_FRAMETYPE)
                    return 2;
                else
                    return 4;
            }
            else if (JOY_REPT(DPAD_LEFT))
            {
                curr = &sOptionMenuPtr->GameOptions[sOptionMenuPtr->cursorPos];
                if (*curr == 0)
                    *curr = sGameOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1;
                else
                    --*curr;
                
                if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_FRAMETYPE)
                    return 2;
                else
                    return 4;
            }
            else if (JOY_REPT(DPAD_UP))
            {
                if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_TEXTSPEED)
                    sOptionMenuPtr->cursorPos = GAME_MENUITEM_CANCEL;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
                return 3;        
            }
            else if (JOY_REPT(DPAD_DOWN))
            {
                if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_CANCEL)
                    sOptionMenuPtr->cursorPos = GAME_MENUITEM_TEXTSPEED;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
                return 3;
            }
            else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
            {
                /*sOptionMenuPtr->cursorPos = MAIN_MENU_GAME_OPTIONS;
                sOptionMenuPtr->MenuCategory = MAIN_MENU;
                gMain.savedCallback = NULL;*/  //to ensure doesn't reset menu cat on callback
                return 1; //think I was supposed to change this but didn't realize
            }
            else
            {
                return 0;
            }
        break;
        case TEXT_OPTIONS: 
           if (JOY_REPT(DPAD_RIGHT))
            {
                current = sOptionMenuPtr->TextOptions[(sOptionMenuPtr->cursorPos)];
                if (current == (sTextOptionsMenuItemCounts[sOptionMenuPtr->cursorPos] - 1))
                    sOptionMenuPtr->TextOptions[sOptionMenuPtr->cursorPos] = 0;
                else
                    sOptionMenuPtr->TextOptions[sOptionMenuPtr->cursorPos] = current + 1;

                    return 4;
            }
            else if (JOY_REPT(DPAD_LEFT))
            {
                curr = &sOptionMenuPtr->TextOptions[sOptionMenuPtr->cursorPos];
                if (*curr == 0)
                    *curr = sTextOptionsMenuItemCounts[sOptionMenuPtr->cursorPos] - 1;
                else
                    --*curr;
                
                    return 4;
            }
            else if (JOY_REPT(DPAD_UP)) 
            {
                if (sOptionMenuPtr->cursorPos == TEXT_MENUITEM_CAP_SPECIES)
                    sOptionMenuPtr->cursorPos = TEXT_MENUITEM_CANCEL;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
                return 3;        
            }
            else if (JOY_REPT(DPAD_DOWN))
            {
                if (sOptionMenuPtr->cursorPos == TEXT_MENUITEM_CANCEL)
                    sOptionMenuPtr->cursorPos = TEXT_MENUITEM_CAP_SPECIES;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
                return 3;
            }
            else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
            {
                /*sOptionMenuPtr->cursorPos = MAIN_MENU_TEXT_OPTIONS;
                sOptionMenuPtr->MenuCategory = MAIN_MENU;
                gMain.savedCallback = NULL;*/  //to ensure doesn't reset menu cat on callback
                return 1;
            }
            else
            {
                return 0;
            }

        break; 
        case MISC_OPTIONS: 
           if (JOY_REPT(DPAD_RIGHT))
            {
                current = sOptionMenuPtr->MiscOptions[(sOptionMenuPtr->cursorPos)];
                if (current == (sMiscOptionsMenuItemCounts[sOptionMenuPtr->cursorPos] - 1))
                    sOptionMenuPtr->MiscOptions[sOptionMenuPtr->cursorPos] = 0;
                else
                    sOptionMenuPtr->MiscOptions[sOptionMenuPtr->cursorPos] = current + 1;

                    return 4;
            }
            else if (JOY_REPT(DPAD_LEFT))
            {
                curr = &sOptionMenuPtr->MiscOptions[sOptionMenuPtr->cursorPos];
                if (*curr == 0)
                    *curr = sMiscOptionsMenuItemCounts[sOptionMenuPtr->cursorPos] - 1;
                else
                    --*curr;
                
                    return 4;
            }
            else if (JOY_REPT(DPAD_UP)) 
            {
                if (sOptionMenuPtr->cursorPos == MISC_MENUITEM_EVENT_SPEEDUP)
                    sOptionMenuPtr->cursorPos = MISC_MENUITEM_CANCEL;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
                return 3;        
            }
            else if (JOY_REPT(DPAD_DOWN))
            {
                if (sOptionMenuPtr->cursorPos == MISC_MENUITEM_CANCEL)
                    sOptionMenuPtr->cursorPos = MISC_MENUITEM_EVENT_SPEEDUP;
                else
                    sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
                return 3;
            }
            else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
            {
                /*sOptionMenuPtr->cursorPos = MAIN_MENU_MISC_OPTIONS;
                sOptionMenuPtr->MenuCategory = MAIN_MENU;
                gMain.savedCallback = NULL;*/  //to ensure doesn't reset menu cat on callback
                return 1;
            }
            else
            {
                return 0;
            }

        break;
    }

    //OK THINK BELOW is extra stuff can remove

    /*if (JOY_REPT(DPAD_RIGHT))
    {
        current = sOptionMenuPtr->GameOptions[(sOptionMenuPtr->cursorPos)];
        if (current == (sGameOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1))
            sOptionMenuPtr->GameOptions[sOptionMenuPtr->cursorPos] = 0;
        else
            sOptionMenuPtr->GameOptions[sOptionMenuPtr->cursorPos] = current + 1;
        if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_FRAMETYPE)
            return 2;
        else
            return 4;
    }
    else if (JOY_REPT(DPAD_LEFT))
    {
        curr = &sOptionMenuPtr->GameOptions[sOptionMenuPtr->cursorPos];
        if (*curr == 0)
            *curr = sGameOptionMenuItemCounts[sOptionMenuPtr->cursorPos] - 1;
        else
            --*curr;
        
        if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_FRAMETYPE)
            return 2;
        else
            return 4;
    }
    else if (JOY_REPT(DPAD_UP))
    {
        if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_TEXTSPEED)
            sOptionMenuPtr->cursorPos = GAME_MENUITEM_CANCEL;
        else
            sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos - 1;
        return 3;        
    }
    else if (JOY_REPT(DPAD_DOWN))
    {
        if (sOptionMenuPtr->cursorPos == GAME_MENUITEM_CANCEL)
            sOptionMenuPtr->cursorPos = GAME_MENUITEM_TEXTSPEED;
        else
            sOptionMenuPtr->cursorPos = sOptionMenuPtr->cursorPos + 1;
        return 3;
    }
    else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        return 1;
    }
    else
    {
        return 0;
    }*/
}

//NEEd menu cat here as well, but can skip main menu stuff as that's for 0
//this builds options labels for each field
static void BufferOptionMenuString(u8 selection)
{
    u8 str[20];
    u8 buf[12];
    u8 dst[3];
    u8 x, y;
    
    memcpy(dst, sOptionMenuTextColor, 3);
    x = 0x82;
    y = ((GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT) - 1) * selection) + 2;
    FillWindowPixelRect(1, 1, x, y, 0x46, GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT));

    switch (sOptionMenuPtr->MenuCategory)
    {
        case MAIN_MENU:
        break;
        case GAME_OPTIONS:
            switch (selection)
            {
            case GAME_MENUITEM_TEXTSPEED:
                AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sTextSpeedOptions[sOptionMenuPtr->GameOptions[selection]]);
                break;
            case GAME_MENUITEM_BATTLESCENE:
                AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sBattleSceneOptions[sOptionMenuPtr->GameOptions[selection]]); 
                break;
            case GAME_MENUITEM_BATTLESTYLE:
                AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sBattleStyleOptions[sOptionMenuPtr->GameOptions[selection]]);
                break;
            case GAME_MENUITEM_SOUND:
                AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sSoundOptions[sOptionMenuPtr->GameOptions[selection]]);
                break;
            case GAME_MENUITEM_BUTTONMODE:
                AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sButtonTypeOptions[sOptionMenuPtr->GameOptions[selection]]);
                break;
            case GAME_MENUITEM_FRAMETYPE:
                StringCopy(str, gText_FrameType);
                ConvertIntToDecimalStringN(buf, sOptionMenuPtr->GameOptions[selection] + 1, 1, 2);
                StringAppendN(str, buf, 3);
                AddTextPrinterParameterized3(1, 2, x, y, dst, -1, str);
                break;
            default:
                break;
            }
        break;
        case TEXT_OPTIONS:
           switch (selection)
            {
                case TEXT_MENUITEM_CAP_SPECIES:
                case TEXT_MENUITEM_CAP_ABILITY:
                case TEXT_MENUITEM_CAP_MOVES:
                case TEXT_MENUITEM_CAP_ITEMS:
                case TEXT_MENUITEM_CAP_PLACEHOLDERS:
                    AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sTextCapOptions[sOptionMenuPtr->TextOptions[selection]]); 
                break;
            }
        break;
        case MISC_OPTIONS:
            switch (selection)
            {
                case MISC_MENUITEM_EVENT_SPEEDUP:
                case MISC_MENUITEM_NUZLOCKE_MODE:
                    AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sTextCapOptions[sOptionMenuPtr->MiscOptions[selection]]); 
                break;
                case MISC_MENUITEM_BATTLE_SPEED:                    
                    AddTextPrinterParameterized3(1, 2, x, y, dst, -1, sBattleSpeedOptions[sOptionMenuPtr->MiscOptions[selection]]); 
                break;
            }
            break;
    }
    
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_BOTH);
}

static void CloseAndSaveOptionMenu(u8 taskId) //vsonic this is where values are set from selection via menu
{

    
    switch (sOptionMenuPtr->MenuCategory) //actually this is last step before close options menu entirely so don't need filter
    {
        case MAIN_MENU:
            gFieldCallback = FieldCB_DefaultWarpExit;
            SetMainCallback2(gMain.savedCallback); //should be return to field with open menu
            FreeAllWindowBuffers(); 
        break;
        case GAME_OPTIONS:
            gSaveBlock2Ptr->optionsTextSpeed = sOptionMenuPtr->GameOptions[GAME_MENUITEM_TEXTSPEED];
            gSaveBlock2Ptr->optionsBattleSceneOff = sOptionMenuPtr->GameOptions[GAME_MENUITEM_BATTLESCENE];
            gSaveBlock2Ptr->optionsBattleStyle = sOptionMenuPtr->GameOptions[GAME_MENUITEM_BATTLESTYLE];
            gSaveBlock2Ptr->optionsSound = sOptionMenuPtr->GameOptions[GAME_MENUITEM_SOUND];
            gSaveBlock2Ptr->optionsButtonMode = sOptionMenuPtr->GameOptions[GAME_MENUITEM_BUTTONMODE];
            gSaveBlock2Ptr->optionsWindowFrameType = sOptionMenuPtr->GameOptions[GAME_MENUITEM_FRAMETYPE];
            SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
            SetMainCallback2(CB2_OptionsMenuFromStartMenu);
            FreeAllWindowBuffers();
        break;
        case TEXT_OPTIONS:
        UpdateSettingDecapSpecies(sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_SPECIES]);
        UpdateSettingDecapAbility(sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_ABILITY]);
        UpdateSettingDecapMoves(sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_MOVES]);
        UpdateSettingDecapItem(sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_ITEMS]);
        UpdateSettingDecapMisc(sOptionMenuPtr->TextOptions[TEXT_MENUITEM_CAP_PLACEHOLDERS]);;
        SetMainCallback2(CB2_OptionsMenuFromStartMenu);
        FreeAllWindowBuffers();
        break;
        case MISC_OPTIONS:
        gSaveBlock2Ptr->optionsEventSpeedup = sOptionMenuPtr->MiscOptions[MISC_MENUITEM_EVENT_SPEEDUP];
        gSaveBlock2Ptr->optionsBattleSpeed = sOptionMenuPtr->MiscOptions[MISC_MENUITEM_BATTLE_SPEED];
        gSaveBlock2Ptr->optionsNuzlockeMode = sOptionMenuPtr->MiscOptions[MISC_MENUITEM_NUZLOCKE_MODE];
        SetMainCallback2(CB2_OptionsMenuFromStartMenu);
        FreeAllWindowBuffers();
        break;
    }   

    
    
    FREE_AND_SET_NULL(sOptionMenuPtr);
    DestroyTask(taskId);
}

static void PrintOptionMenuHeader(void)
{
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_TEXT_OPTION, 2, gText_MenuOption, 8, 1, TEXT_SPEED_FF, NULL);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_BOTH);
}

static void DrawOptionMenuBg(void)
{
    u8 h;
    h = 2;
    
    FillBgTilemapBufferRect(1, 0x1B3, 1, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B4, 2, 2, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B5, 0x1C, 2, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1B6, 1, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B8, 0x1C, 3, 1, h, 3);
    FillBgTilemapBufferRect(1, 0x1B9, 1, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BA, 2, 5, 0x1B, 1, 3);
    FillBgTilemapBufferRect(1, 0x1BB, 0x1C, 5, 1, 1, 3);
    FillBgTilemapBufferRect(1, 0x1AA, 1, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AB, 2, 6, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1AC, 0x1C, 6, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1AD, 1, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1AF, 0x1C, 7, 1, 0x10, h);
    FillBgTilemapBufferRect(1, 0x1B0, 1, 0x13, 1, 1, h);
    FillBgTilemapBufferRect(1, 0x1B1, 2, 0x13, 0x1A, 1, h);
    FillBgTilemapBufferRect(1, 0x1B2, 0x1C, 0x13, 1, 1, h);
    CopyBgTilemapBufferToVram(1);
}

static void Init_OptionsMenuListNames(void)
{
    u8 Menu_Count = 0;
    u8 i;

    switch (sOptionMenuPtr->MenuCategory)
    {
        case MAIN_MENU:
            Menu_Count = MAIN_MENU_COUNT;
            for (i = 0; i < Menu_Count; i++) 
            {
                AddTextPrinterParameterized(WIN_OPTIONS, 2, sMainOptionMenuItemsNames[i], 8, (u8)((i * (GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - i, TEXT_SPEED_FF, NULL);    
            }
        break;
        case GAME_OPTIONS:
            Menu_Count = GAME_MENUITEM_COUNT;
            for (i = 0; i < Menu_Count; i++) 
            {
                AddTextPrinterParameterized(WIN_OPTIONS, 2, sGameOptionMenuItemsNames[i], 8, (u8)((i * (GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - i, TEXT_SPEED_FF, NULL);    
            }
        break;
        case TEXT_OPTIONS:
            Menu_Count = TEXT_MENUITEM_COUNT;
            for (i = 0; i < Menu_Count; i++) 
            {
                AddTextPrinterParameterized(WIN_OPTIONS, 2, sTextOptionMenuItemsNames[i], 8, (u8)((i * (GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - i, TEXT_SPEED_FF, NULL);    
            }
        break;
        case MISC_OPTIONS:
            Menu_Count = MISC_MENUITEM_COUNT;
            for (i = 0; i < Menu_Count; i++) 
            {
                AddTextPrinterParameterized(WIN_OPTIONS, 2, sMiscOptionMenuItemsNames[i], 8, (u8)((i * (GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - i, TEXT_SPEED_FF, NULL);    
            }
        break;
    }
}

static void LoadOptionMenuItemNames(void)
{   
    FillWindowPixelBuffer(1, PIXEL_FILL(1));
    Init_OptionsMenuListNames();
}

static void UpdateSettingSelectionDisplay(u16 selection)
{
    u16 maxLetterHeight, y;
    
    maxLetterHeight = GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT);
    y = selection * (maxLetterHeight - 1) + 0x3A;
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(y, y + maxLetterHeight));
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0x10, 0xE0));
}

static void UpdateSettingDecapSpecies(u8 selection)
{
    if (selection == ON)
        FlagSet(FLAG_CAPITALIZE_SPECIES_TEXT);
    else if (selection == OFF)
        FlagClear(FLAG_CAPITALIZE_SPECIES_TEXT);
}
static void UpdateSettingDecapAbility(u8 selection)
{
    if (selection == ON)
        FlagSet(FLAG_CAPITALIZE_ABILITY_TEXT);
    else if (selection == OFF)
        FlagClear(FLAG_CAPITALIZE_ABILITY_TEXT);
}
static void UpdateSettingDecapMoves(u8 selection)
{
    if (selection == ON)
        FlagSet(FLAG_CAPITALIZE_MOVE_TEXT);
    else if (selection == OFF)
        FlagClear(FLAG_CAPITALIZE_MOVE_TEXT);
}
static void UpdateSettingDecapItem(u8 selection)
{
    if (selection == ON)
        FlagSet(FLAG_CAPITALIZE_ITEM_TEXT);
    else if (selection == OFF)
        FlagClear(FLAG_CAPITALIZE_ITEM_TEXT);
}
static void UpdateSettingDecapMisc(u8 selection)
{
    if (selection == ON)
        FlagSet(FLAG_CAPITALIZE_MISC_PLACEHOLDER);
    else if (selection == OFF)
        FlagClear(FLAG_CAPITALIZE_MISC_PLACEHOLDER);
}

u8 IsEventSpeedupOn(void)
{
    if (gSaveBlock2Ptr->optionsEventSpeedup)
        return TRUE;

    return FALSE;
}

u8 IsNuzlockeModeOn(void)
{
    if (gSaveBlock2Ptr->optionsNuzlockeMode)
        return TRUE;

    return FALSE;
}
