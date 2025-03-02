#include "global.h"
#include "gflib.h"
#include "decompress.h"
#include "graphics.h"
#include "task.h"
#include "text_window.h"
#include "menu.h"
#include "menu_helpers.h"
#include "new_menu_helpers.h"
#include "list_menu.h"
#include "item.h"
#include "item_menu.h"
#include "link.h"
#include "money.h"
#include "shop.h"
#include "teachy_tv.h"
#include "pokemon_storage_system.h"
#include "party_menu.h"
#include "tm_case.h"
#include "data.h"
#include "scanline_effect.h"
#include "strings.h"
#include "menu_indicators.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "pokemon_icon.h"
#include "pokemon.h"
#include "gba/types.h"

#define TM_CASE_TM_TAG 400 //figure what this is as well. vsonic

//port from upgraded pret, most unused current just using win ids

#define TAG_SCROLL_ARROW 110

enum {
    WIN_LIST,
    WIN_DESCRIPTION,
    WIN_SELECTED_MSG,
    WIN_TITLE,
    WIN_MOVE_INFO_LABELS,
    WIN_MOVE_INFO,
    WIN_MESSAGE,
    WIN_SELL_QUANTITY,
    WIN_MONEY,
};

// Window IDs for the context menu that opens when a TM/HM is selected
enum {
    WIN_USE_GIVE_EXIT,
    WIN_GIVE_EXIT,
};

// IDs for the actions in the context menu
enum {
    ACTION_USE,
    ACTION_GIVE,
    ACTION_EXIT
};

enum {
    COLOR_LIGHT,
    COLOR_DARK,
    COLOR_CURSOR_SELECTED,
    COLOR_MOVE_INFO,
    COLOR_CURSOR_ERASE = 0xFF
};

// Base position for TM/HM disc sprite
#define DISC_BASE_X 41
#define DISC_BASE_Y 35

#define DISC_CASE_DISTANCE 20 // The total number of pixels a disc travels vertically in/out of the case
#define DISC_Y_MOVE 10 // The number of pixels a disc travels vertically per movement step

#define TAG_DISC 400

//change to never run into  a possible tm value
//and not use 0xFFFF because storage value is an s16
#define DISC_HIDDEN 0x4000 // When no TM/HM is selected, hide the disc sprite

enum {
    ANIM_TM,
    ANIM_HM,
};


struct UnkStruct_203B10C
{
    void (* savedCallback)(void);
    u8 tmCaseMenuType;
    u8 unk_05;
    u8 unk_06;
    u16 selectedRow;
    u16 scrollOffset;
};

struct UnkStruct_203B118
{
    void (* savedCallback)(void);
    u8 tmSpriteId;
    u8 maxTMs_Hms_Shown;
    u8 numTMs_HMs;
    u8 contextMenuWindowId;
    u8 scrollIndicatorArrowPairId;
    u16 currItem;
    const u8 * menuActionIndices;
    u8 numMenuActions;
    s16 seqId;
    u8 filler_14[8];
};//decided rename some of these, as name is misleding its both tm & hms

struct UnkStruct_203B11C
{
    struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    u16 unk_160;
    u16 unk_162;
};

static EWRAM_DATA struct UnkStruct_203B10C sTMCaseStaticResources = {};
static EWRAM_DATA struct UnkStruct_203B118 * sTMCaseDynamicResources = NULL;
static EWRAM_DATA struct UnkStruct_203B11C * sPokedudePackBackup = NULL;
static EWRAM_DATA void * sTilemapBuffer = NULL; // tilemap buffer
static EWRAM_DATA struct ListMenuItem * sListMenuItemsBuffer = NULL;
static EWRAM_DATA u8 (* sListMenuStringsBuffer)[29] = NULL;
static EWRAM_DATA u16 * sTMSpritePaletteBuffer = NULL;
//added for new tm case
static EWRAM_DATA u8    spriteIdData[PARTY_SIZE] = {};
static EWRAM_DATA u16   spriteIdPalette[PARTY_SIZE] = {};

extern const struct SpritePalette gMonIconPaletteTable[6];

static void CB2_SetUpTMCaseUI_Blocking(void);
static bool8 DoSetUpTMCaseUI(void);
static void ResetBufferPointers_NoFree(void);
static void LoadBGTemplates(void);
static bool8 HandleLoadTMCaseGraphicsAndPalettes(void);
static void CreateTMCaseListMenuBuffers(void);
static void InitTMCaseListMenuItems(void);
static void GetTMNumberAndMoveString(u8 * dest, u16 itemId);
static void TMCase_MoveCursorFunc(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void TMCase_ItemPrintFunc(u8 windowId, s32 itemId, u8 y);
static void TMCase_MoveCursor_UpdatePrintedDescription(s32 itemIndex);
static void PrintListMenuCursorAt_WithColorIdx(u8 a0, u8 a1);
static void CreateTMCaseScrollIndicatorArrowPair_Main(void);
static void TMCaseSetup_GetTMCount(void);
static void TMCaseSetup_InitListMenuPositions(void);
static void TMCaseSetup_UpdateVisualMenuOffset(void);
static void Task_FadeOutAndCloseTMCase(u8 taskId);
static void Task_TMCaseMain(u8 taskId);
static void Task_SelectTMAction_FromFieldBag(u8 taskId);
static void Task_TMContextMenu_HandleInput(u8 taskId);
static void TMHMContextMenuAction_Use(u8 taskId);
static void TMHMContextMenuAction_Give(u8 taskId);
static void PrintError_ThereIsNoPokemon(u8 taskId);
static void PrintError_ItemCantBeHeld(u8 taskId);
static void Task_WaitButtonAfterErrorPrint(u8 taskId);
static void Subtask_CloseContextMenuAndReturnToMain(u8 taskId);
static void TMHMContextMenuAction_Exit(u8 taskId);
static void Task_SelectTMAction_Type1(u8 taskId);
static void Task_SelectTMAction_Type3(u8 taskId);
static void Task_SelectTMAction_FromSellMenu(u8 taskId);
static void Task_AskConfirmSaleWithAmount(u8 taskId);
static void Task_PlaceYesNoBox(u8 taskId);
static void Task_SaleOfTMsCanceled(u8 taskId);
static void Task_InitQuantitySelectUI(u8 taskId);
static void SellTM_PrintQuantityAndSalePrice(s16 quantity, s32 value);
static void Task_QuantitySelect_HandleInput(u8 taskId);
static void Task_PrintSaleConfirmedText(u8 taskId);
static void Task_DoSaleOfTMs(u8 taskId);
static void Task_AfterSale_ReturnToList(u8 taskId);
static void Task_TMCaseDude1(u8 taskId);
static void Task_TMCaseDude_Playback(u8 taskId);
static void InitWindowTemplatesAndPals(void);
static void AddTextPrinterParameterized_ColorByIndex(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx);
static void TMCase_SetWindowBorder1(u8 windowId);
static void TMCase_SetWindowBorder2(u8 windowId);
static void TMCase_PrintMessageWithFollowupTask(u8 taskId, u8 windowId, const u8 * str, TaskFunc func);
static void PrintStringTMCaseOnWindow3(void);
static void DrawMoveInfoUIMarkers(void);
static void TMCase_MoveCursor_UpdatePrintedTMInfo(u16 itemId);
static void PlaceHMTileInWindow(u8 windowId, u8 x, u8 y);
static void HandlePrintMoneyOnHand(void);
static void HandleCreateYesNoMenu(u8 taskId, const struct YesNoFuncTable * ptrs);
static u8 AddTMContextMenu(u8 * a0, u8 a1);
static void RemoveTMContextMenu(u8 * a0);
static u8 CreateTMSprite(u16 itemId);
static void SetTMSpriteAnim(struct Sprite * sprite, u8 mode); //mode is if tmhm
static void TintTMSpriteByType(u8 type); //
static void UpdateTMSpritePosition(struct Sprite * sprite, u16 tmIdx); //u16 tmidx specifically so DISC_HIDDEN doesn't overwrite tm, max tm/hm still 254
static void InitSelectedTMSpriteData(u8 a0, u16 itemId);
static void SpriteCB_MoveTMSpriteInCase(struct Sprite * sprite);
static void LoadTMTypePalettes(void); //
//added for new tm case
static void DrawPartyMonIcons(void);
static void TintPartyMonIcons(u16 tm, s32 itemIndex);
static void DestroyPartyMonIcons(void);


static const struct BgTemplate sBGTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0x000
    }, {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }, {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x000
    }
};

static void (*const sSelectTMActionTasks[])(u8 taskId) = {
    Task_SelectTMAction_FromFieldBag,
    Task_SelectTMAction_Type1,
    Task_SelectTMAction_FromSellMenu,
    Task_SelectTMAction_Type3
};

static const struct MenuAction sMenuActions_UseGiveExit[] = {
    {gOtherText_Use,  TMHMContextMenuAction_Use },
    {gOtherText_Give, TMHMContextMenuAction_Give},
    {gOtherText_Exit, TMHMContextMenuAction_Exit},
};

static const u8 sMenuActionIndices_Field[] = {0, 1, 2};
static const u8 sMenuActionIndices_UnionRoom[] = {1, 2};
static const struct YesNoFuncTable sYesNoFuncTable = {Task_PrintSaleConfirmedText, Task_SaleOfTMsCanceled};

static const u8 sText_ClearTo18[] = _("{CLEAR_TO 18}");
static const u8 sText_SingleSpace[] = _(" ");

static ALIGNED(4) const u16 sPal3Override[] = {RGB(8, 8, 8), RGB(30, 16, 6)};

static const u8 sTextColors[][3] = {
    [COLOR_LIGHT] = {0, 1, 2},
    [COLOR_DARK] = {0, 2, 3},
    [COLOR_CURSOR_SELECTED] = {0, 3, 6},
    [COLOR_MOVE_INFO] = {0, 14, 10},
};

static const struct WindowTemplate sWindowTemplates[] = {
    [WIN_LIST] = {
        .bg = 0,
        .tilemapLeft = 10,
        .tilemapTop = 1,
        .width = 19,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 0x081
    },//is item list not tm case decrease height by 2
    [WIN_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 9,
        .width = 18,
        .height = 11,
        .paletteNum = 10,
        .baseBlock = 0x13f
    }, //or this is description //decrease top by 3 increase height by 3
    [WIN_SELECTED_MSG] = {
        .bg = 1,
        .tilemapLeft = 5,
        .tilemapTop = 15,
        .width = 15,
        .height = 4,
        .paletteNum = 13,
        .baseBlock = 0x1f9
    },
    [WIN_TITLE] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x255
    }, //think tm case name window? raised top by 1
    [WIN_MOVE_INFO_LABELS] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 11,
        .width = 5,
        .height = 8,
        .paletteNum = 12,
        .baseBlock = 0x269
    }, //believe icons type power acc in box  //decrease top by 2 increase height by 2
    [WIN_MOVE_INFO] = {
        .bg = 0,
        .tilemapLeft = 7,
        .tilemapTop = 11,
        .width = 5,
        .height = 8,
        .paletteNum = 12,
        .baseBlock = 0x310
    }, //think values that go with type power acc in box  //decrease top by 2 increase height by 2
    [WIN_MESSAGE] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 11,
        .baseBlock = 0x295
    },
    [WIN_SELL_QUANTITY] = {
        .bg = 1,
        .tilemapLeft = 17,
        .tilemapTop = 9,
        .width = 12,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x310
    },
    [WIN_MONEY] = {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 8,
        .height = 3,
        .paletteNum = 13,
        .baseBlock = 0x34d
    },
    DUMMY_WIN_TEMPLATE
};


static const struct WindowTemplate sWindowTemplates2[] = {
    [WIN_LIST] = {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 1,
        .width = 15,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 0x081
    }, //is item list not tm case decrease height by 2
    [WIN_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 9,
        .width = 18,
        .height = 11,
        .paletteNum = 10,
        .baseBlock = 0x100
    }, //or this is description //decrease top by 3 increase height by 3
    [WIN_SELECTED_MSG] = {
        .bg = 1,
        .tilemapLeft = 5,
        .tilemapTop = 15,
        .width = 15,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1f9
    },
    [WIN_TITLE] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x255
    }, //think tm case name window? raised top by 1
    [WIN_MOVE_INFO_LABELS] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 11,
        .width = 5,
        .height = 8,
        .paletteNum = 12,
        .baseBlock = 0x269
    }, //believe icons type power acc in box  //decrease top by 2 increase height by 2
    [WIN_MOVE_INFO] = {
        .bg = 0,
        .tilemapLeft = 7,
        .tilemapTop = 11,
        .width = 5,
        .height = 8,
        .paletteNum = 12,
        .baseBlock = 0x310
    }, //think values that go with type power acc in box  //decrease top by 2 increase height by 2
    [WIN_MESSAGE] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 11,
        .baseBlock = 0x295
    },
    [WIN_SELL_QUANTITY] = {
        .bg = 1,
        .tilemapLeft = 17,
        .tilemapTop = 9,
        .width = 12,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x310
    },
    [WIN_MONEY] = {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 8,
        .height = 3,
        .paletteNum = 13,
        .baseBlock = 0x34d
    },
    DUMMY_WIN_TEMPLATE
};

/*
static const struct WindowTemplate sWindowTemplates[] = {
    {0x00, 0x0a, 0x01, 0x13, 0x0a, 0x0f, 0x0081},
    {0x00, 0x0c, 0x0c, 0x12, 0x08, 0x0a, 0x013f},
    {0x01, 0x05, 0x0f, 0x0f, 0x04, 0x0d, 0x01f9},
    {0x00, 0x00, 0x01, 0x0a, 0x02, 0x0f, 0x0235},
    {0x00, 0x01, 0x0d, 0x05, 0x06, 0x0c, 0x0249},
    {0x00, 0x07, 0x0d, 0x05, 0x06, 0x0c, 0x0267},
    {0x01, 0x02, 0x0f, 0x1a, 0x04, 0x0b, 0x0285},
    {0x01, 0x11, 0x09, 0x0c, 0x04, 0x0f, 0x02ed},
    {0x01, 0x01, 0x01, 0x08, 0x03, 0x0d, 0x031d},
    DUMMY_WIN_TEMPLATE
};//figure what these do / kept using for mart sell tms



static const struct WindowTemplate sWindowTemplates2[] = {
    {0x00, 0x0e, 0x01, 0x0f, 0x0a, 0x0f, 0x0081},
    {0x00, 0x0c, 0x0c, 0x12, 0x08, 0x0a, 0x013f},
    {0x01, 0x05, 0x0f, 0x0f, 0x04, 0x0f, 0x01f9},
    {0x00, 0x00, 0x01, 0x0a, 0x02, 0x0f, 0x0235},
    {0x00, 0x01, 0x0d, 0x05, 0x06, 0x0c, 0x0249},
    {0x00, 0x07, 0x0d, 0x05, 0x06, 0x0c, 0x0267},
    {0x01, 0x02, 0x0f, 0x1a, 0x04, 0x0b, 0x0285},
    {0x01, 0x11, 0x09, 0x0c, 0x04, 0x0f, 0x02ed},
    {0x01, 0x01, 0x01, 0x08, 0x03, 0x0d, 0x031d},
    DUMMY_WIN_TEMPLATE
}; //version from port for tm case update
*/


static const struct WindowTemplate sYesNoWindowTemplate = {0x01, 0x15, 0x09, 0x06, 0x04, 0x0f, 0x0335};

static const struct WindowTemplate sTMContextWindowTemplates[] = {
    {0x01, 0x16, 0x0d, 0x07, 0x06, 0x0f, 0x01cf},
    {0x01, 0x16, 0x0f, 0x07, 0x04, 0x0f, 0x01cf}
};

static const struct OamData sTMSpriteOamData = {
    .size = 2,
    .priority = 2
};

static const union AnimCmd sTMSpriteAnim0[] = {
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd sTMSpriteAnim1[] = {
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sTMSpriteAnims[] = {
    sTMSpriteAnim0,
    sTMSpriteAnim1
};

static const struct CompressedSpriteSheet sTMSpriteSheet = {
    (const void *)gTMCase_TMSpriteGfx,
    0x400,
    TM_CASE_TM_TAG
};

static const struct SpriteTemplate sTMSpriteTemplate = {
    TM_CASE_TM_TAG,
    TM_CASE_TM_TAG,
    &sTMSpriteOamData,
    sTMSpriteAnims,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

//each type pallete is 16 bytes, 
//so anything added would increase by 0x10
static const u16 sTMSpritePaletteOffsetByType[] = { // fairy addition need do, need do sound as well
    [TYPE_NORMAL]   = 0x000,
    [TYPE_FIRE]     = 0x010,
    [TYPE_WATER]    = 0x020,
    [TYPE_GRASS]    = 0x030,
    [TYPE_ELECTRIC] = 0x040,
    [TYPE_ROCK]     = 0x050,
    [TYPE_GROUND]   = 0x060,
    [TYPE_ICE]      = 0x070,
    [TYPE_FLYING]   = 0x080,
    [TYPE_FIGHTING] = 0x090,
    [TYPE_GHOST]    = 0x0a0,
    [TYPE_BUG]      = 0x0b0,
    [TYPE_POISON]   = 0x0c0,
    [TYPE_PSYCHIC]  = 0x0d0,
    [TYPE_STEEL]    = 0x0e0,
    [TYPE_DARK]     = 0x0f0,
    [TYPE_DRAGON]   = 0x100,
    [TYPE_FAIRY]    = 0X110   //works
};

void InitTMCase(u8 type, void (* exitCallback)(void), bool8 allowSelectClose)
{
    ResetBufferPointers_NoFree();
    sTMCaseDynamicResources = Alloc(sizeof(struct UnkStruct_203B118));
    sTMCaseDynamicResources->savedCallback = NULL;
    sTMCaseDynamicResources->scrollIndicatorArrowPairId = TASK_NONE;
    sTMCaseDynamicResources->contextMenuWindowId = WINDOW_NONE;
    if (type != TMCASE_REOPENING)
        sTMCaseStaticResources.tmCaseMenuType = type;
    if (exitCallback != NULL)
        sTMCaseStaticResources.savedCallback = exitCallback;
    if (allowSelectClose != TMCASE_KEEP_PREV)
        sTMCaseStaticResources.unk_05 = allowSelectClose;
    gTextFlags.autoScroll = FALSE;
    SetMainCallback2(CB2_SetUpTMCaseUI_Blocking);
}

static void CB2_Idle(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_Idle(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_SetUpTMCaseUI_Blocking(void)
{
    while (1)
    {
        if (MenuHelpers_CallLinkSomething() == TRUE)
            break;
        if (DoSetUpTMCaseUI() == TRUE)
            break;
        if (MenuHelpers_IsLinkActive() == TRUE)
            break;
    }
}

static bool8 DoSetUpTMCaseUI(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        gMain.state++;
        break;
    case 4:
        ResetSpriteData();
        gMain.state++;
        break;
    case 5:
        ResetTasks();
        gMain.state++;
        break;
    case 6:
        LoadBGTemplates();
        sTMCaseDynamicResources->seqId = 0;
        gMain.state++;
        break;
    case 7:
        InitWindowTemplatesAndPals();
        gMain.state++;
        break;
    case 8:
        if (HandleLoadTMCaseGraphicsAndPalettes())
            gMain.state++;
        break;
    case 9:
        SortPocketAndPlaceHMsFirst(&gBagPockets[POCKET_TM_CASE - 1]);
        gMain.state++;
        break;
    case 10:
        TMCaseSetup_GetTMCount();
        TMCaseSetup_InitListMenuPositions();
        TMCaseSetup_UpdateVisualMenuOffset();
        gMain.state++;
        break;
    case 11:
        DrawMoveInfoUIMarkers();
        if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] != sSelectTMActionTasks[2])
            DrawPartyMonIcons();  //part of tm case port
        gMain.state++;
        break;
    case 12:
        CreateTMCaseListMenuBuffers();
        InitTMCaseListMenuItems();
        gMain.state++;
        break;
    case 13:
        PrintStringTMCaseOnWindow3();
        gMain.state++;
        break;
    case 14:
        if (sTMCaseStaticResources.tmCaseMenuType == 4)
            taskId = CreateTask(Task_TMCaseDude1, 0);
        else
            taskId = CreateTask(Task_TMCaseMain, 0);
        gTasks[taskId].data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sTMCaseStaticResources.scrollOffset, sTMCaseStaticResources.selectedRow, DEFAULT_MODE);
        gMain.state++;
        break;
    case 15:
        CreateTMCaseScrollIndicatorArrowPair_Main();
        gMain.state++;
        break;
    case 16:
        if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] == sSelectTMActionTasks[2])
        sTMCaseDynamicResources->tmSpriteId = CreateTMSprite(BagGetItemIdByPocketPosition(POCKET_TM_CASE, sTMCaseStaticResources.scrollOffset + sTMCaseStaticResources.selectedRow));
        gMain.state++;
        break;
    case 17:
        BlendPalettes(0xFFFFFFFF, 16, 0);
        gMain.state++;
        break;
    case 18:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_Idle);
        SetMainCallback2(CB2_Idle);
        return TRUE;
    }

    return FALSE;
}

static void ResetBufferPointers_NoFree(void)
{
    sTMCaseDynamicResources = NULL;
    sTilemapBuffer = NULL;
    sListMenuItemsBuffer = NULL;
    sListMenuStringsBuffer = NULL;
    sTMSpritePaletteBuffer = NULL;
}

static void LoadBGTemplates(void)
{
    void ** ptr;
    ResetAllBgsCoordinatesAndBgCntRegs();
    ptr = &sTilemapBuffer;
    *ptr = AllocZeroed(0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBGTemplates, NELEMS(sBGTemplates));
    SetBgTilemapBuffer(2, *ptr);
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
}

static bool8 HandleLoadTMCaseGraphicsAndPalettes(void)
{
    switch (sTMCaseDynamicResources->seqId)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, gUnknown_8E845D8, 0, 0, 0);
        sTMCaseDynamicResources->seqId++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] == sSelectTMActionTasks[2]) //if selling tm
                LZDecompressWram(gTMCase_TM_list_window, sTilemapBuffer);
            else
                LZDecompressWram(gTMCase_TM_list_newTMcase_window, sTilemapBuffer); //windows moved over for mon icons
            sTMCaseDynamicResources->seqId++;
        }
        break;
    case 2:
        if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] == sSelectTMActionTasks[2])
            LZDecompressWram(gTMCase_TM_box, GetBgTilemapBuffer(1)); //sets tm case inside graphic for tms to sit in
        else
            LZDecompressWram(gTMCase_TM_cleared_box, GetBgTilemapBuffer(1)); //removes box graphic so only view icons
        sTMCaseDynamicResources->seqId++;
        break;
    case 3:
        if (gSaveBlock2Ptr->playerGender == MALE)
            LoadCompressedPalette(gUnknown_8E84CB0, 0, 0x80);
        else
            LoadCompressedPalette(gUnknown_8E84D20, 0, 0x80);
        sTMCaseDynamicResources->seqId++;
        break;
    case 4:
        LoadCompressedSpriteSheet(&sTMSpriteSheet);
        sTMCaseDynamicResources->seqId++;
        break;
    default:
        LoadTMTypePalettes();
        sTMCaseDynamicResources->seqId = 0;
        return TRUE;
    }

    return FALSE;
}

static void CreateTMCaseListMenuBuffers(void)
{
    struct BagPocket * pocket = &gBagPockets[POCKET_TM_CASE - 1];
    sListMenuItemsBuffer = Alloc((pocket->capacity + 1) * sizeof(struct ListMenuItem));
    sListMenuStringsBuffer = Alloc(sTMCaseDynamicResources->numTMs_HMs * 29);
}

static void InitTMCaseListMenuItems(void)
{
    struct BagPocket * pocket = &gBagPockets[POCKET_TM_CASE - 1];
    u16 i;

    for (i = 0; i < sTMCaseDynamicResources->numTMs_HMs; i++)
    {
        GetTMNumberAndMoveString(sListMenuStringsBuffer[i], pocket->itemSlots[i].itemId);
        sListMenuItemsBuffer[i].label = sListMenuStringsBuffer[i];
        sListMenuItemsBuffer[i].index = i;
    }
    sListMenuItemsBuffer[i].label = gText_Close;
    sListMenuItemsBuffer[i].index = -2;
    gMultiuseListMenuTemplate.items = sListMenuItemsBuffer;
    gMultiuseListMenuTemplate.totalItems = sTMCaseDynamicResources->numTMs_HMs + 1;
    gMultiuseListMenuTemplate.windowId = 0;
    gMultiuseListMenuTemplate.header_X = 0;
    gMultiuseListMenuTemplate.item_X = 8;
    gMultiuseListMenuTemplate.cursor_X = 0;
    gMultiuseListMenuTemplate.lettersSpacing = 0;
    gMultiuseListMenuTemplate.itemVerticalPadding = 2;
    gMultiuseListMenuTemplate.upText_Y = 2;
    gMultiuseListMenuTemplate.maxShowed = sTMCaseDynamicResources->maxTMs_Hms_Shown;
    gMultiuseListMenuTemplate.fontId = 2;
    gMultiuseListMenuTemplate.cursorPal = 2;
    gMultiuseListMenuTemplate.fillValue = 0;
    gMultiuseListMenuTemplate.cursorShadowPal = 3;
    gMultiuseListMenuTemplate.moveCursorFunc = TMCase_MoveCursorFunc;
    gMultiuseListMenuTemplate.itemPrintFunc = TMCase_ItemPrintFunc;
    gMultiuseListMenuTemplate.cursorKind = 0;
    gMultiuseListMenuTemplate.scrollMultiple = TRUE; //changed to true to allow use left/right to scroll by max shown
}

//vsonic display tmhm number
//would like separate from Id limit,
//if can do with Name instead would be great
//would need remove TM/HM from the name, then add leading zeroes as needed
//see if can remove/ignore zeroes before a number that isn't 0?
//then add leading zeroes back?

//new idea can use sTMHMMoves array
//to decide what the tm value is,
//check if move listed in array is a tmhm
//then loop array check if secondaryId moveId
//matches item id if so break,
//and return array id + 1
//doesn't work for hms so will need to separte
//hms out into their own array?
//luckily nothing else uses sTMHMMoves
//ok DONE I THINK, this should do what I need,
//and order tms (as displayed by this function)
//accordingly.
//Only issue would be finding Tms/Hms in overworld.
//since pretty sure those follow item name,
//belive I could probably change that
//most likely will make an attempt. hmm
//if works will be extrmeley easy 
//to adjust in game tms/hms won't even need to worry about
//shifting Item Ids, just set the item to tmcase pocket
//and adjust the two arrays 
//would do similar effect to this,
//but think do a string append for the found id,
//with either TM or HM based on which it is
//tested works, only issue is
//the order the tms get printed in,
//that is unchanged, even if I make fly the first HM
//cut is still printed first
static void GetTMNumberAndMoveString(u8 * dest, u16 itemId)
{
    u32 TMHMValue;
    u8 isHM = TRUE; //loop tmlist if found there set to false

    StringCopy(gStringVar4, gText_FontSize0);
    GetMoveName(gStringVar3,ItemIdToBattleMoveId(itemId));
    
    for (TMHMValue = 0; gTM_Moves[TMHMValue] != LIST_END; ++TMHMValue)
    {
        if (ItemIdToBattleMoveId(itemId) == gTM_Moves[TMHMValue])
        {
            isHM = FALSE;
            break;
        }    
    }

    if (isHM)
    {
        for (TMHMValue = 0; gHM_Moves[TMHMValue] != LIST_END; ++TMHMValue)
        {
            if (ItemIdToBattleMoveId(itemId) == gHM_Moves[TMHMValue])
            break;  
        }
    }
    
    if (IsTMHM(itemId))
    {

        if (isHM)
        {
            StringAppend(gStringVar4, sText_ClearTo18);
            StringAppend(gStringVar4, gOtherText_UnkF9_08_Clear_01);
            ConvertIntToDecimalStringN(gStringVar1, TMHMValue + 1, STR_CONV_MODE_LEADING_ZEROS, 1);
            StringAppend(gStringVar4, gStringVar1);
        }
        else
        {
            StringAppend(gStringVar4, gOtherText_UnkF9_08_Clear_01);
            ConvertIntToDecimalStringN(gStringVar1, TMHMValue + 1, STR_CONV_MODE_LEADING_ZEROS, 3);
            StringAppend(gStringVar4, gStringVar1);
        }
    }

    StringAppend(gStringVar4, sText_SingleSpace);
    StringAppend(gStringVar4, gText_FontSize2);
    StringAppend(gStringVar4, gStringVar3);
    StringCopy(dest, gStringVar4);
}

//vsonic important, see what that pocket position thing is
//my be the issue I'm having screwing order
static void TMCase_MoveCursorFunc(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    u16 itemId;

    if (itemIndex == -2) //index -2 seems to be close tm box
        itemId = 0;
    else
        itemId = BagGetItemIdByPocketPosition(POCKET_TM_CASE, itemIndex);

    if (onInit != TRUE)
    {
        PlaySE(SE_SELECT);
        if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] == sSelectTMActionTasks[2])
        InitSelectedTMSpriteData(sTMCaseDynamicResources->tmSpriteId, itemId);
    }
    TMCase_MoveCursor_UpdatePrintedDescription(itemIndex);
    TMCase_MoveCursor_UpdatePrintedTMInfo(itemId);
}

static void TMCase_ItemPrintFunc(u8 windowId, s32 itemId, u8 y)
{
    if (itemId != -2) //this seems to be same as itemIndex??
    {
        if (!itemid_is_unique(BagGetItemIdByPocketPosition(POCKET_TM_CASE, itemId)))
        {
            ConvertIntToDecimalStringN(gStringVar1, BagGetQuantityByPocketPosition(POCKET_TM_CASE, itemId), STR_CONV_MODE_RIGHT_ALIGN, 3);
            StringExpandPlaceholders(gStringVar4, gText_TimesStrVar1);
            AddTextPrinterParameterized_ColorByIndex(windowId, 0, gStringVar4, 0x7E, y, 0, 0, 0xFF, 1);
        }
        else
        {
            PlaceHMTileInWindow(windowId, 8, y); //for replacing NO text with HM for hm use
        }
    }
}

static void TMCase_MoveCursor_UpdatePrintedDescription(s32 itemIndex)
{
    const u8 * str;
    u16 itemId = BagGetItemIdByPocketPosition(POCKET_TM_CASE, itemIndex);
    if (itemIndex != -2)
    {
        str = ItemId_GetDescription(itemId);
    }
    else
    {
        str = gText_TMCaseWillBePutAway;
    }
    FillWindowPixelBuffer(1, 0);
    AddTextPrinterParameterized_ColorByIndex(1, 2, str, 2, 3, 0, 0, 0, 0);

    // update icons
    if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] != sSelectTMActionTasks[2])
        TintPartyMonIcons(itemId, itemIndex);
}

// Darkens (or subsequently lightens) the blue bg tiles around the description window when a TM/HM is selected.
// shade=0: lighten, shade=1: darken
static void SetDescriptionWindowShade(s32 shade)
{
    SetBgTilemapPalette(2, 0, 12, 30, 8, 2 * shade + 1);
    ScheduleBgCopyTilemapToVram(2);
}

static void PrintListMenuCursorByID_WithColorIdx(u8 a0, u8 a1)
{
    PrintListMenuCursorAt_WithColorIdx(ListMenuGetYCoordForPrintingArrowCursor(a0), a1);
}

static void PrintListMenuCursorAt_WithColorIdx(u8 a0, u8 a1)
{
    if (a1 == 0xFF)
    {
        FillWindowPixelRect(0, 0, 0, a0, GetFontAttribute(2, 0), GetFontAttribute(2, 1));
        CopyWindowToVram(0, COPYWIN_GFX);
    }
    else
    {
        AddTextPrinterParameterized_ColorByIndex(0, 2, gText_SelectorArrow2, 0, a0, 0, 0, 0, a1);
    }
}

static void CreateTMCaseScrollIndicatorArrowPair_Main(void)
{
    sTMCaseDynamicResources->scrollIndicatorArrowPairId = AddScrollIndicatorArrowPairParameterized(2, 0xA0, 0x08, 0x3d, sTMCaseDynamicResources->numTMs_HMs - sTMCaseDynamicResources->maxTMs_Hms_Shown + 1, 0x6E, 0x6E, &sTMCaseStaticResources.scrollOffset);
}

static void CreateTMCaseScrollIndicatorArrowPair_SellQuantitySelect(void)
{
    sTMCaseDynamicResources->currItem = 1;
    sTMCaseDynamicResources->scrollIndicatorArrowPairId = AddScrollIndicatorArrowPairParameterized(2, 0x98, 0x48, 0x4d, 2, 0x6E, 0x6E, &sTMCaseDynamicResources->currItem);
}

static void RemoveTMCaseScrollIndicatorArrowPair(void)
{
    if (sTMCaseDynamicResources->scrollIndicatorArrowPairId != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(sTMCaseDynamicResources->scrollIndicatorArrowPairId);
        sTMCaseDynamicResources->scrollIndicatorArrowPairId = 0xFF;
    }
}

void ResetTMCaseCursorPos(void)
{
    sTMCaseStaticResources.selectedRow = 0;
    sTMCaseStaticResources.scrollOffset = 0;
}

//confused on how this works, and
//how its deciding to increment numTMs_HMs
//ok its checking the tm case pocket
//stops if itemid is item_none, so would be cancel button?
//otherwise to seems to loop until it hits capacity
//which I believe should be tm count + hm count
//so its num of individual tms in your bag
//not what they are, and doesn't split hms?
static void TMCaseSetup_GetTMCount(void)
{
    struct BagPocket * pocket = &gBagPockets[POCKET_TM_CASE - 1];
    u16 i;

    BagPocketCompaction(pocket->itemSlots, pocket->capacity);
    sTMCaseDynamicResources->numTMs_HMs = 0;
    for (i = 0; i < pocket->capacity; i++)
    {
        if (pocket->itemSlots[i].itemId == ITEM_NONE)
            break;
        sTMCaseDynamicResources->numTMs_HMs++;
    }
    sTMCaseDynamicResources->maxTMs_Hms_Shown = min(sTMCaseDynamicResources->numTMs_HMs + 1, 3); //determines how many tms to display on screen, was 5 with grhaphic change swap to 3
}

static void TMCaseSetup_InitListMenuPositions(void)
{
    if (sTMCaseStaticResources.scrollOffset != 0)
    {
        if (sTMCaseStaticResources.scrollOffset + sTMCaseDynamicResources->maxTMs_Hms_Shown > sTMCaseDynamicResources->numTMs_HMs + 1)
            sTMCaseStaticResources.scrollOffset = sTMCaseDynamicResources->numTMs_HMs + 1 - sTMCaseDynamicResources->maxTMs_Hms_Shown;
    }
    if (sTMCaseStaticResources.scrollOffset + sTMCaseStaticResources.selectedRow >= sTMCaseDynamicResources->numTMs_HMs + 1)
    {
        if (sTMCaseDynamicResources->numTMs_HMs + 1 < 2)
            sTMCaseStaticResources.selectedRow = 0;
        else
            sTMCaseStaticResources.selectedRow = sTMCaseDynamicResources->numTMs_HMs;
    }
}

//think this is scroll effect, when you scroll passed more than 3 values it "scrolls" to update position
static void TMCaseSetup_UpdateVisualMenuOffset(void) 
{
    u8 i;
    if (sTMCaseStaticResources.selectedRow > 1) //adjusted for new graphic from 3 to 1, hope work
    {
        for (i = 0; i <= sTMCaseStaticResources.selectedRow - 1 && sTMCaseStaticResources.scrollOffset + sTMCaseDynamicResources->maxTMs_Hms_Shown != sTMCaseDynamicResources->numTMs_HMs + 1; i++)
        {
            do {} while (0);
            sTMCaseStaticResources.selectedRow--;
            sTMCaseStaticResources.scrollOffset++;
        }
    }
}

static void DestroyTMCaseBuffers(void)
{
    if (sTMCaseDynamicResources != NULL)
        Free(sTMCaseDynamicResources);
    if (sTilemapBuffer != NULL)
        Free(sTilemapBuffer);
    if (sListMenuItemsBuffer != NULL)
        Free(sListMenuItemsBuffer);
    if (sListMenuStringsBuffer != NULL)
        Free(sListMenuStringsBuffer);
    if (sTMSpritePaletteBuffer != NULL)
        Free(sTMSpritePaletteBuffer);
    FreeAllWindowBuffers();
}

static void Task_BeginFadeOutFromTMCase(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, -2, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_FadeOutAndCloseTMCase;
}

static void Task_FadeOutAndCloseTMCase(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        DestroyListMenuTask(data[0], &sTMCaseStaticResources.scrollOffset, &sTMCaseStaticResources.selectedRow);
        if (sTMCaseDynamicResources->savedCallback != NULL)
            SetMainCallback2(sTMCaseDynamicResources->savedCallback);
        else
            SetMainCallback2(sTMCaseStaticResources.savedCallback);
        RemoveTMCaseScrollIndicatorArrowPair();
        DestroyTMCaseBuffers();
        DestroyTask(taskId);
    }
}

static void Task_TMCaseMain(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    s32 input;

    if (!gPaletteFade.active)
    {
        if (MenuHelpers_CallLinkSomething() != TRUE)
        {
            input = ListMenu_ProcessInput(data[0], DEFAULT_MODE);
            ListMenuGetScrollAndRow(data[0], &sTMCaseStaticResources.scrollOffset, &sTMCaseStaticResources.selectedRow);
            if (JOY_NEW(SELECT_BUTTON) && sTMCaseStaticResources.unk_05 == 1)
            {
                PlaySE(SE_SELECT);
                gSpecialVar_ItemId = ITEM_NONE;
                Task_BeginFadeOutFromTMCase(taskId);
            }
            else
            {
                switch (input)
                {
                case -1:
                    break;
                case -2:
                    PlaySE(SE_SELECT);
                    gSpecialVar_ItemId = 0;
                    Task_BeginFadeOutFromTMCase(taskId);
                    break;
                default:
                    PlaySE(SE_SELECT);
                    //SetDescriptionWindowShade(1);
                    RemoveTMCaseScrollIndicatorArrowPair();
                    PrintListMenuCursorByID_WithColorIdx(data[0], 2);
                    data[1] = input;
                    data[2] = BagGetQuantityByPocketPosition(POCKET_TM_CASE, input);
                    gSpecialVar_ItemId = BagGetItemIdByPocketPosition(POCKET_TM_CASE, input);
                    gTasks[taskId].func = sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType];
                    break;
                }
            }
        }
    }
}

static void Subtask_ReturnToTMCaseMain(u8 taskId)
{
    //SetDescriptionWindowShade(0);
    CreateTMCaseScrollIndicatorArrowPair_Main();
    gTasks[taskId].func = Task_TMCaseMain;
}

static void Task_SelectTMAction_FromFieldBag(u8 taskId)
{
    u8 * strbuf;
    TMCase_SetWindowBorder2(2);
    if (!MenuHelpers_IsLinkActive() && InUnionRoom() != TRUE)
    {
        AddTMContextMenu(&sTMCaseDynamicResources->contextMenuWindowId, 0);
        sTMCaseDynamicResources->menuActionIndices = sMenuActionIndices_Field;
        sTMCaseDynamicResources->numMenuActions = NELEMS(sMenuActionIndices_Field);
    }
    else
    {
        AddTMContextMenu(&sTMCaseDynamicResources->contextMenuWindowId, 1);
        sTMCaseDynamicResources->menuActionIndices = sMenuActionIndices_UnionRoom;
        sTMCaseDynamicResources->numMenuActions = NELEMS(sMenuActionIndices_UnionRoom);
    }
    AddItemMenuActionTextPrinters(sTMCaseDynamicResources->contextMenuWindowId, 2, GetMenuCursorDimensionByFont(2, 0), 2, 0, GetFontAttribute(2, 1) + 2, sTMCaseDynamicResources->numMenuActions, sMenuActions_UseGiveExit, sTMCaseDynamicResources->menuActionIndices);
    Menu_InitCursor(sTMCaseDynamicResources->contextMenuWindowId, 2, 0, 2, GetFontAttribute(2, 1) + 2, sTMCaseDynamicResources->numMenuActions, 0);
    strbuf = Alloc(256);
    GetTMNumberAndMoveString(strbuf, gSpecialVar_ItemId);
    StringAppend(strbuf, gText_Var1IsSelected + 2); // +2 skips over the stringvar
    AddTextPrinterParameterized_ColorByIndex(2, 2, strbuf, 0, 2, 0, 0, 0, 1);
    Free(strbuf);
    
    //RemoveTMContextMenu(&sTMCaseDynamicResources->contextMenuWindowId); //below is essentially this funtion, but couldnt get to take arg 2
    ClearStdWindowAndFrameToTransparent(2, FALSE); //replace these with above function if figure out pointer logic...
    ClearWindowTilemap(2);
    //RemoveWindow(2);
    ScheduleBgCopyTilemapToVram(0); //to hopefully remove window for selected tezxt / worked perfect
    
    if (itemid_is_unique(gSpecialVar_ItemId)) //should check make sure hm stuff still works with window removal
    {
        PlaceHMTileInWindow(2, 0, 2); //for adding HM graphic before NO for hms
        CopyWindowToVram(2, COPYWIN_GFX);
    } 
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    gTasks[taskId].func = Task_TMContextMenu_HandleInput;
}

static void Task_TMContextMenu_HandleInput(u8 taskId)
{
    s8 input;

    if (MenuHelpers_CallLinkSomething() != TRUE)
    {
        input = Menu_ProcessInputNoWrapAround();
        switch (input)
        {
        case -1:
            PlaySE(SE_SELECT);
            sMenuActions_UseGiveExit[sTMCaseDynamicResources->menuActionIndices[sTMCaseDynamicResources->numMenuActions - 1]].func.void_u8(taskId);
            break;
        case -2:
            break;
        default:
            PlaySE(SE_SELECT);
            sMenuActions_UseGiveExit[sTMCaseDynamicResources->menuActionIndices[input]].func.void_u8(taskId);
            break;
        }
    }
}

static void TMHMContextMenuAction_Use(u8 taskId)
{
    RemoveTMContextMenu(&sTMCaseDynamicResources->contextMenuWindowId);
    ClearStdWindowAndFrameToTransparent(2, 0);
    ClearWindowTilemap(2);
    PutWindowTilemap(0);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    if (CalculatePlayerPartyCount() == 0)
    {
        PrintError_ThereIsNoPokemon(taskId);
    }
    else
    {
        gItemUseCB = ItemUseCB_TMHM;
        sTMCaseDynamicResources->savedCallback = CB2_ShowPartyMenuForItemUse;
        Task_BeginFadeOutFromTMCase(taskId);
    }
}

static void TMHMContextMenuAction_Give(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u16 itemId = BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1]);
    RemoveTMContextMenu(&sTMCaseDynamicResources->contextMenuWindowId);
    ClearStdWindowAndFrameToTransparent(2, 0);
    ClearWindowTilemap(2);
    PutWindowTilemap(1);
    PutWindowTilemap(4);
    PutWindowTilemap(5);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);

    PrintError_ItemCantBeHeld(taskId);
    //block both tms and hms from being given as held items,
    //no idea why this was allowed
}

static void PrintError_ThereIsNoPokemon(u8 taskId)
{
    TMCase_PrintMessageWithFollowupTask(taskId, 2, gText_ThereIsNoPokemon, Task_WaitButtonAfterErrorPrint);
}

static void PrintError_ItemCantBeHeld(u8 taskId)
{
    StringExpandPlaceholders(gStringVar4, gText_ItemCantBeHeld2);
    TMCase_PrintMessageWithFollowupTask(taskId, 2, gStringVar4, Task_WaitButtonAfterErrorPrint);
}

static void Task_WaitButtonAfterErrorPrint(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        Subtask_CloseContextMenuAndReturnToMain(taskId);
    }
}

static void Subtask_CloseContextMenuAndReturnToMain(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    DestroyListMenuTask(data[0], &sTMCaseStaticResources.scrollOffset, &sTMCaseStaticResources.selectedRow);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sTMCaseStaticResources.scrollOffset, sTMCaseStaticResources.selectedRow, DEFAULT_MODE);
    PrintListMenuCursorByID_WithColorIdx(data[0], 1);
    ClearDialogWindowAndFrameToTransparent(6, 0);
    ClearWindowTilemap(6);
    PutWindowTilemap(1);
    PutWindowTilemap(4);
    PutWindowTilemap(5);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    Subtask_ReturnToTMCaseMain(taskId);
}

static void TMHMContextMenuAction_Exit(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    RemoveTMContextMenu(&sTMCaseDynamicResources->contextMenuWindowId);
    ClearStdWindowAndFrameToTransparent(2, 0);
    ClearWindowTilemap(2);
    PutWindowTilemap(0);
    PrintListMenuCursorByID_WithColorIdx(data[0], 1);
    PutWindowTilemap(1);
    PutWindowTilemap(4);
    PutWindowTilemap(5);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    Subtask_ReturnToTMCaseMain(taskId);
}

static void Task_SelectTMAction_Type1(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!itemid_is_unique(BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1])))
    {
        sTMCaseDynamicResources->savedCallback = CB2_GiveHoldItem;
        Task_BeginFadeOutFromTMCase(taskId);
    }
    else
    {
        PrintError_ItemCantBeHeld(taskId);
    }
}

static void Task_SelectTMAction_Type3(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!itemid_is_unique(BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1])))
    {
        sTMCaseDynamicResources->savedCallback = Cb2_ReturnToPSS;
        Task_BeginFadeOutFromTMCase(taskId);
    }
    else
    {
        PrintError_ItemCantBeHeld(taskId);
    }
}

static void Task_SelectTMAction_FromSellMenu(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (itemid_get_market_price(gSpecialVar_ItemId) == 0)
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_OhNoICantBuyThat);
        TMCase_PrintMessageWithFollowupTask(taskId, GetDialogBoxFontId(), gStringVar4, Subtask_CloseContextMenuAndReturnToMain);
    }
    else
    {
        data[8] = 1;
        if (data[2] == 1)
        {
            HandlePrintMoneyOnHand();
            Task_AskConfirmSaleWithAmount(taskId);
        }
        else
        {
            if (data[2] > 99)
                data[2] = 99;
            CopyItemName(gSpecialVar_ItemId, gStringVar1);
            StringExpandPlaceholders(gStringVar4, gText_HowManyWouldYouLikeToSell);
            TMCase_PrintMessageWithFollowupTask(taskId, GetDialogBoxFontId(), gStringVar4, Task_InitQuantitySelectUI);
        }
    }
}

static void Task_AskConfirmSaleWithAmount(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    ConvertIntToDecimalStringN(gStringVar3, itemid_get_market_price(BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1])) / 2 * data[8], STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, gText_ICanPayThisMuch_WouldThatBeOkay);
    TMCase_PrintMessageWithFollowupTask(taskId, GetDialogBoxFontId(), gStringVar4, Task_PlaceYesNoBox);
}

static void Task_PlaceYesNoBox(u8 taskId)
{
    HandleCreateYesNoMenu(taskId, &sYesNoFuncTable);
}

static void Task_SaleOfTMsCanceled(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    ClearStdWindowAndFrameToTransparent(8, 0);
    ClearDialogWindowAndFrameToTransparent(6, 0);
    PutWindowTilemap(0);
    PutWindowTilemap(1);
    PutWindowTilemap(3);
    PutWindowTilemap(4);
    PutWindowTilemap(5);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    PrintListMenuCursorByID_WithColorIdx(data[0], 1);
    Subtask_ReturnToTMCaseMain(taskId);
}

static void Task_InitQuantitySelectUI(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    TMCase_SetWindowBorder1(7);
    ConvertIntToDecimalStringN(gStringVar1, 1, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringExpandPlaceholders(gStringVar4, gText_TimesStrVar1);
    AddTextPrinterParameterized_ColorByIndex(7, 0, gStringVar4, 4, 10, 0, 0, 0, 1);
    SellTM_PrintQuantityAndSalePrice(1, itemid_get_market_price(BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1])) / 2 * data[8]);
    HandlePrintMoneyOnHand();
    CreateTMCaseScrollIndicatorArrowPair_SellQuantitySelect();
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    gTasks[taskId].func = Task_QuantitySelect_HandleInput;
}

static void SellTM_PrintQuantityAndSalePrice(s16 quantity, s32 amount)
{
    FillWindowPixelBuffer(7, 0x11);
    ConvertIntToDecimalStringN(gStringVar1, quantity, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringExpandPlaceholders(gStringVar4, gText_TimesStrVar1);
    AddTextPrinterParameterized_ColorByIndex(7, 0, gStringVar4, 4, 10, 0, 0, 0, 1);
    PrintMoneyAmount(7, 0x38, 0x0A, amount, 0);
}

static void Task_QuantitySelect_HandleInput(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&data[8], data[2]) == 1)
    {
        SellTM_PrintQuantityAndSalePrice(data[8], itemid_get_market_price(BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1])) / 2 * data[8]);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(7, 0);
        ScheduleBgCopyTilemapToVram(0);
        ScheduleBgCopyTilemapToVram(1);
        RemoveTMCaseScrollIndicatorArrowPair();
        Task_AskConfirmSaleWithAmount(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(7, 0);
        ClearStdWindowAndFrameToTransparent(8, 0);
        ClearDialogWindowAndFrameToTransparent(6, 0);
        PutWindowTilemap(3);
        PutWindowTilemap(0);
        PutWindowTilemap(1);
        ScheduleBgCopyTilemapToVram(0);
        ScheduleBgCopyTilemapToVram(1);
        RemoveTMCaseScrollIndicatorArrowPair();
        PrintListMenuCursorByID_WithColorIdx(data[0], 1);
        Subtask_ReturnToTMCaseMain(taskId);
    }
}

static void Task_PrintSaleConfirmedText(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    PutWindowTilemap(0);
    ScheduleBgCopyTilemapToVram(0);
    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar3, itemid_get_market_price(BagGetItemIdByPocketPosition(POCKET_TM_CASE, data[1])) / 2 * data[8], STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, gText_TurnedOverItemsWorthYen);
    TMCase_PrintMessageWithFollowupTask(taskId, 2, gStringVar4, Task_DoSaleOfTMs);
}

static void Task_DoSaleOfTMs(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    PlaySE(SE_SHOP);
    RemoveBagItem(gSpecialVar_ItemId, data[8]);
    AddMoney(&gSaveBlock1Ptr->money, itemid_get_market_price(gSpecialVar_ItemId) / 2 * data[8]);
    RecordItemPurchase(gSpecialVar_ItemId, data[8], 2);
    DestroyListMenuTask(data[0], &sTMCaseStaticResources.scrollOffset, &sTMCaseStaticResources.selectedRow);
    TMCaseSetup_GetTMCount();
    TMCaseSetup_InitListMenuPositions();
    InitTMCaseListMenuItems();
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sTMCaseStaticResources.scrollOffset, sTMCaseStaticResources.selectedRow, DEFAULT_MODE);
    PrintListMenuCursorByID_WithColorIdx(data[0], 2);
    PrintMoneyAmountInMoneyBox(8, GetMoney(&gSaveBlock1Ptr->money), 0);
    gTasks[taskId].func = Task_AfterSale_ReturnToList;
}

static void Task_AfterSale_ReturnToList(u8 taskId)
{
    if (JOY_NEW(A_BUTTON) || JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(8, 0);
        ClearDialogWindowAndFrameToTransparent(6, 0);
        PutWindowTilemap(1);
        PutWindowTilemap(3);
        PutWindowTilemap(4);
        PutWindowTilemap(5);
        Subtask_CloseContextMenuAndReturnToMain(taskId);
    }
}

void Pokedude_InitTMCase(void) //for teach tv
{
    sPokedudePackBackup = AllocZeroed(sizeof(*sPokedudePackBackup));
    memcpy(sPokedudePackBackup->bagPocket_TMHM, gSaveBlock1Ptr->bagPocket_TMHM, sizeof(gSaveBlock1Ptr->bagPocket_TMHM));
    memcpy(sPokedudePackBackup->bagPocket_KeyItems, gSaveBlock1Ptr->bagPocket_KeyItems, sizeof(gSaveBlock1Ptr->bagPocket_KeyItems));
    sPokedudePackBackup->unk_160 = sTMCaseStaticResources.selectedRow;
    sPokedudePackBackup->unk_162 = sTMCaseStaticResources.scrollOffset;
    ClearItemSlots(gSaveBlock1Ptr->bagPocket_TMHM, NELEMS(gSaveBlock1Ptr->bagPocket_TMHM));
    ClearItemSlots(gSaveBlock1Ptr->bagPocket_KeyItems, NELEMS(gSaveBlock1Ptr->bagPocket_KeyItems));
    ResetTMCaseCursorPos();
    AddBagItem(ITEM_TM01, 1);
    AddBagItem(ITEM_TM03, 1);
    AddBagItem(ITEM_TM09, 1);
    AddBagItem(ITEM_TM35, 1);
    InitTMCase(4, CB2_ReturnToTeachyTV, 0);
}

static void Task_TMCaseDude1(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        data[8] = 0;
        data[9] = 0;
        gTasks[taskId].func = Task_TMCaseDude_Playback;
    }
}

//think either for just teach tv or quest log event so leave the shade for this as is
static void Task_TMCaseDude_Playback(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (JOY_NEW(B_BUTTON))
    {
        if (data[8] < 21)
        {
            data[8] = 21;
            SetTeachyTvControllerModeToResume();
        }
    }

    switch (data[8])
    {
    case 0:
        BeginNormalPaletteFade(0xFFFF8405, 4, 0, 6, 0);
        SetDescriptionWindowShade(1);
        data[8]++;
        break;
    case 1:
    case 11:
        if (!gPaletteFade.active)
        {
            data[9]++;
            if (data[9] > 0x65)
            {
                data[9] = 0;
                data[8]++;
            }
        }
        break;
    case 2:
    case 3:
    case 4:
    case 12:
    case 13:
    case 14:
        if (data[9] == 0)
        {
            gMain.newKeys = 0;
            gMain.newAndRepeatedKeys = DPAD_DOWN;
            ListMenu_ProcessInput(data[0], DEFAULT_MODE);
        }
        data[9]++;
        if (data[9] > 0x65)
        {
            data[9] = 0;
            data[8]++;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 15:
    case 16:
    case 17:
        if (data[9] == 0)
        {
            gMain.newKeys = 0;
            gMain.newAndRepeatedKeys = DPAD_UP;
            ListMenu_ProcessInput(data[0], DEFAULT_MODE);
        }
        data[9]++;
        if (data[9] > 0x65)
        {
            data[9] = 0;
            data[8]++;
        }
        break;
    case 8:
        SetDescriptionWindowShade(1);
        TMCase_PrintMessageWithFollowupTask(taskId, 4, gPokedudeText_TMTypes, 0);
        gTasks[taskId].func = Task_TMCaseDude_Playback;
        data[8]++;
        break;
    case 9:
    case 19:
        RunTextPrinters();
        if (!IsTextPrinterActive(6))
            data[8]++;
        break;
    case 10:
        if (JOY_NEW(A_BUTTON | B_BUTTON))
        {
            SetDescriptionWindowShade(0);
            BeginNormalPaletteFade(0x00000400, 0, 6, 0, 0);
            ClearDialogWindowAndFrameToTransparent(6, 0);
            ScheduleBgCopyTilemapToVram(1);
            data[8]++;
        }
        break;
    case 18:
        SetDescriptionWindowShade(1);
        TMCase_PrintMessageWithFollowupTask(taskId, 4, gPokedudeText_ReadTMDescription, NULL);
        gTasks[taskId].func = Task_TMCaseDude_Playback; // this function
        data[8]++;
        break;
    case 20:
        if (JOY_NEW(A_BUTTON | B_BUTTON))
            data[8]++;
        break;
    case 21:
        if (!gPaletteFade.active)
        {
            memcpy(gSaveBlock1Ptr->bagPocket_TMHM, sPokedudePackBackup->bagPocket_TMHM, sizeof(gSaveBlock1Ptr->bagPocket_TMHM));
            memcpy(gSaveBlock1Ptr->bagPocket_KeyItems, sPokedudePackBackup->bagPocket_KeyItems, sizeof(gSaveBlock1Ptr->bagPocket_KeyItems));
            DestroyListMenuTask(data[0], NULL, NULL);
            sTMCaseStaticResources.selectedRow = sPokedudePackBackup->unk_160;
            sTMCaseStaticResources.scrollOffset = sPokedudePackBackup->unk_162;
            Free(sPokedudePackBackup);
            CpuFastCopy(gPlttBufferFaded, gPlttBufferUnfaded, 0x400);
            CB2_SetUpReshowBattleScreenAfterMenu();
            BeginNormalPaletteFade(0xFFFFFFFF, -2, 0, 16, 0);
            data[8]++;
        }
        break;
    default:
        if (!gPaletteFade.active)
        {
            SetMainCallback2(sTMCaseStaticResources.savedCallback);
            RemoveTMCaseScrollIndicatorArrowPair();
            DestroyTMCaseBuffers();
            DestroyTask(taskId);
        }
        break;
    }
}

static void InitWindowTemplatesAndPals(void) //90% this isn't' gonna work. ...it actually worked. o.o
{
    u8 i;
    if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] == sSelectTMActionTasks[2])
        InitWindows(sWindowTemplates);
    else
        InitWindows(sWindowTemplates2);
    DeactivateAllTextPrinters();
    LoadUserWindowGfx(0, 0x5B, 0xE0);
    TextWindow_LoadResourcesStdFrame0(0, 0x64, 0xB0);
    LoadStdWindowGfx(0, 0x78, 0xD0);
    LoadPalette(gStandardMenuPalette, 0xF0, 0x20);
    LoadPalette(gStandardMenuPalette, 0xA0, 0x20);
    LoadPalette(sPal3Override, 0xF6, 0x04);
    LoadPalette(sPal3Override, 0xD6, 0x04);
    ListMenuLoadStdPalAt(0xc0, 0x01);
    for (i = 0; i < 9; i++)
        FillWindowPixelBuffer(i, 0x00);
    PutWindowTilemap(0);
    PutWindowTilemap(1);
    PutWindowTilemap(3);
    PutWindowTilemap(4);
    PutWindowTilemap(5);
    ScheduleBgCopyTilemapToVram(0);
}

static void AddTextPrinterParameterized_ColorByIndex(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx)
{
    AddTextPrinterParameterized4(windowId, fontId, x, y, letterSpacing, lineSpacing, sTextColors[colorIdx], speed, str);
}

static void TMCase_SetWindowBorder1(u8 windowId)
{
    DrawStdFrameWithCustomTileAndPalette(windowId, FALSE, 0x5B, 0x0E);
}

static void TMCase_SetWindowBorder2(u8 windowId)
{
    DrawStdFrameWithCustomTileAndPalette(windowId, FALSE, 0x78, 0x0D);
}

static void TMCase_PrintMessageWithFollowupTask(u8 taskId, u8 windowId, const u8 * str, TaskFunc func)
{
    DisplayMessageAndContinueTask(taskId, 6, 0x64, 0x0B, windowId, GetPlayerTextSpeedDelay(), str, func);
    ScheduleBgCopyTilemapToVram(1);
}

static void PrintStringTMCaseOnWindow3(void) //thought was entire tm case graphic is instead just text for tm case
{
    u32 distance;

    if (sSelectTMActionTasks[sTMCaseStaticResources.tmCaseMenuType] == sSelectTMActionTasks[2]) //works but not what I expected
        distance = 72 - GetStringWidth(1, gText_TMCase, 0);  //should hopefully be in mart/sale
    else
        distance = 100 - GetStringWidth(1, gText_TMCase, 0);
    AddTextPrinterParameterized3(3, 1, distance / 2, 1, sTextColors[0], 0, gText_TMCase);
}

static void DrawMoveInfoUIMarkers(void)
{
    BlitMoveInfoIcon(4, MENU_INFO_ICON_TYPE, 0, 0);
    BlitMoveInfoIcon(4, MENU_INFO_ICON_POWER, 0, 12);
    BlitMoveInfoIcon(4, MENU_INFO_ICON_ACCURACY, 0, 24);
    BlitMoveInfoIcon(4, MENU_INFO_ICON_PP, 0, 36);
    CopyWindowToVram(4, COPYWIN_GFX);
}

static void TMCase_MoveCursor_UpdatePrintedTMInfo(u16 itemId)
{
    u8 i;
    u16 move;
    const u8 * str;

    FillWindowPixelRect(5, 0, 0, 0, 40, 48);
    if (itemId == ITEM_NONE)
    {
        for (i = 0; i < 4; i++)
        {
            AddTextPrinterParameterized_ColorByIndex(5, 3, gText_ThreeHyphens, 7, 12 * i, 0, 0, 0xFF, 3);
        }
        CopyWindowToVram(5, COPYWIN_GFX);
    }
    else
    {
        move = ItemIdToBattleMoveId(itemId);
        BlitMoveInfoIcon(5, gBattleMoves[move].type + 1, 0, 0);
        if (gBattleMoves[move].power < 2)
            str = gText_ThreeHyphens;
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[move].power, STR_CONV_MODE_RIGHT_ALIGN, 3);
            str = gStringVar1;
        }
        AddTextPrinterParameterized_ColorByIndex(5, 3, str, 7, 12, 0, 0, 0xFF, 3);
        if (gBattleMoves[move].accuracy == 0)
            str = gText_ThreeHyphens;
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[move].accuracy, STR_CONV_MODE_RIGHT_ALIGN, 3);
            str = gStringVar1;
        }
        AddTextPrinterParameterized_ColorByIndex(5, 3, str, 7, 24, 0, 0, 0xFF, 3);
        ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[move].pp, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized_ColorByIndex(5, 3, gStringVar1, 7, 36, 0, 0, 0xFF, 3);
        CopyWindowToVram(5, COPYWIN_GFX);
    }
}

static void PlaceHMTileInWindow(u8 windowId, u8 x, u8 y)
{
    BlitBitmapToWindow(windowId, gUnknown_8E99118, x, y, 16, 12);
}

static void HandlePrintMoneyOnHand(void)
{
    PrintMoneyAmountInMoneyBoxWithBorder(8, 0x78, 0xD, GetMoney(&gSaveBlock1Ptr->money));
}

static void HandleCreateYesNoMenu(u8 taskId, const struct YesNoFuncTable *ptrs)
{
    CreateYesNoMenuWithCallbacks(taskId, &sYesNoWindowTemplate, 2, 0, 2, 0x5B, 0x0E, ptrs);
}

static u8 AddTMContextMenu(u8 * windowId, u8 windowIndex)
{
    if (*windowId == 0xFF)
    {
        *windowId = AddWindow(&sTMContextWindowTemplates[windowIndex]);
        TMCase_SetWindowBorder1(*windowId);
        ScheduleBgCopyTilemapToVram(0);
    }
    return *windowId;
}

static void RemoveTMContextMenu(u8 * windowId)
{
    ClearStdWindowAndFrameToTransparent(*windowId, FALSE);
    ClearWindowTilemap(*windowId);
    RemoveWindow(*windowId);
    ScheduleBgCopyTilemapToVram(0);
    *windowId = 0xFF;
}

//go through these, that use tmIdx, or ITEM_TM01
//change to separate from item id,
//for tmIdx mostly want to keep from having to calculate
//in this function
//but idea for the ones that need to do something
//diff if tm or hm, add mode value
//hopefully can do search before this,
//if itemId is locked in above this,
//as my current search is slow, //well no that's the fill,
//should be much faster as I won't need to double loop,
//if I can do above this can potentially return if tm or hm as well,
//maybe make a function that can return both?
//would need to do the type split thing I used for relative evo,
//split a u32 into 2 u16s?
//ok unfortunately this is the first instance of item set...
//even more unfortunately its built off scroll index,
//so if my logic is too slow, it'll directly affect scroll speed
//or at the least be VERY noticeable...
static u8 CreateTMSprite(u16 itemId)
{
    u8 spriteId = CreateSprite(&sTMSpriteTemplate, DISC_BASE_X, DISC_BASE_Y, 0); //think is coord for tm sprite sits in case 
    u16 itemData = GetTMHMNumberandCategory(itemId); //store data so don't need 2nd function call
    u8 tmIdx = (itemData & 0xFF); //tm/hm id
    u8 tmCat = ((itemData & 0xFF00) >> 8); //is tm or hm
    
    if (itemId == ITEM_NONE) //ok didn't have the constant  in, but THIS is where value of disc hidden is relevant
    {
        UpdateTMSpritePosition(&gSprites[spriteId], DISC_HIDDEN);
        return spriteId;
    }
    else
    {
        SetTMSpriteAnim(&gSprites[spriteId], tmCat); //or not, did expansion so not usign bit field but still worked as is?
        TintTMSpriteByType(gBattleMoves[ItemIdToBattleMoveId(itemId)].type);
        UpdateTMSpritePosition(&gSprites[spriteId], tmIdx);
        return spriteId;
    }
}

//as only condition is tm or hm, swap tmIdx for cat/mode
static void SetTMSpriteAnim(struct Sprite * sprite, u8 mode)
{
    if (mode == HM_MOVE) //believe this is also for tm hm, and would need to change i.e 50 base tms
        StartSpriteAnim(sprite, ANIM_HM);
    else if (mode == TM_MOVE)
        StartSpriteAnim(sprite, ANIM_TM);
}

static void TintTMSpriteByType(u8 type) //don't get this type here is worthless all that matters is offset?
{
    u8 palIndex = IndexOfSpritePaletteTag(TM_CASE_TM_TAG) << 4;
    LoadPalette(sTMSpritePaletteBuffer + sTMSpritePaletteOffsetByType[type], OBJ_PLTT_OFFSET  | palIndex, 0x20);
    if (sTMCaseStaticResources.tmCaseMenuType == 4)     //The 0x100 that was here had nothing to do w offset replaced w constant to make clearer
    {
        BlendPalettes(1 << (0x10 + palIndex), 4, RGB_BLACK);
    }
}

static void UpdateTMSpritePosition(struct Sprite * sprite, u16 tmIdx) //vsonic
{
    s32 x, y;
    if (tmIdx == DISC_HIDDEN) //var is tm id,  ff is close menu I believe
    {
        x = 0x1B;
        y = 0x28;
        sprite->pos2.y = 0x10; //still need check but believe will need adjust both these y values, up(lower) to account for changed graphic
    }
    else
    {

        x = DISC_BASE_X - Q_24_8_TO_INT(Q_24_8(14 * tmIdx) / (NUM_TECHNICAL_MACHINES + NUM_HIDDEN_MACHINES));
        y = DISC_BASE_Y + Q_24_8_TO_INT(Q_24_8(8 * tmIdx) / (NUM_TECHNICAL_MACHINES + NUM_HIDDEN_MACHINES));
    }
    sprite->pos1.x = x;
    sprite->pos1.y = y; //0x16 value was 2E
}//changed tmIdx to u16 think shouldn't cause any issue, value stored there isn't changing.

#define sItemId  data[0]
#define sState   data[1]
static void InitSelectedTMSpriteData(u8 spriteId, u16 itemId)
{
    gSprites[spriteId].sItemId = itemId;
    gSprites[spriteId].sState = 0;
    gSprites[spriteId].callback = SpriteCB_MoveTMSpriteInCase;
}

static void SpriteCB_MoveTMSpriteInCase(struct Sprite * sprite) //vsonic
{
    u16 itemData = GetTMHMNumberandCategory(sprite->sItemId); //store data so don't need 2nd function call
    u8 tmIdx = (itemData & 0xFF); //tm/hm id
    u8 tmCat = ((itemData & 0xFF00) >> 8); //is tm or hm

    switch (sprite->sState)
    {
    case 0:
        // Lower old disc back into case
        if (sprite->pos2.y >= 10)   //is meant to be distance but my value uses 10, default is 20
        {
            // Old disc is hidden, set up new disc
            if (sprite->sItemId != ITEM_NONE)
            {
                sprite->sState++;
                TintTMSpriteByType(gBattleMoves[ItemIdToBattleMoveId(sprite->sItemId)].type);
                SetTMSpriteAnim(sprite, tmCat);
                UpdateTMSpritePosition(sprite, tmIdx);
            }
            else
                sprite->callback = SpriteCallbackDummy;
        }
        else
        {
            sprite->pos2.y += DISC_Y_MOVE;
        }
        break;
    case 1:
        if (sprite->pos2.y <= 0)
            sprite->callback = SpriteCallbackDummy;
        else
            sprite->pos2.y -= DISC_Y_MOVE;
    }
}

/*static void LoadTMTypePalettes(void)
{
    struct SpritePalette spritePalette;

    sTMSpritePaletteBuffer = Alloc(0x110 * sizeof(u16));
    LZDecompressWram(gTMCaseDiscTypes1_Pal, sTMSpritePaletteBuffer);
    LZDecompressWram(gTMCaseDiscTypes2_Pal, sTMSpritePaletteBuffer + 0x110);
    spritePalette.data = sTMSpritePaletteBuffer + 0x110;
    spritePalette.tag = TM_CASE_TM_TAG;
    LoadSpritePalette(&spritePalette);
}*/

// - 1 excludes TYPE_MYSTERY
//had issue w load time, but seems first intuition was correct issue was use of hex w binary subtract, so change type constants from hex to binary values
//ok important thing is number of colors, the number of palettes incompassing the 2 disc type pals below
//type1_pal is a 8bps range w 256 colors 16 colors per palette 256 read as 0x100
//old type2_pal was a 4bps range w 16 colors which would be 0x10
//but w expansion of types needed add 3 palett for new types, w that changed
//type2_pal is now changed to a 8bps range like type 1 adding another 0x100
//so in total I need to allocate 0x200 and that worked
//this change gives enough space for 32 diff pallets for types
//so the value no longer needs to be changed its future proof (effectively)

//seems work for tm case but not debug?
static void LoadTMTypePalettes(void) //would need item and type values
{
    struct SpritePalette spritePalette;
    //u16 itemId = BagGetItemIdByPocketPosition(POCKET_TM_CASE, sTMCaseStaticResources.scrollOffset + sTMCaseStaticResources.selectedRow);
    //u8 type = gBattleMoves[ItemIdToBattleMoveId(itemId)].type;

    sTMSpritePaletteBuffer = Alloc(0x200 * sizeof(u16)); //alloc is end of offset, each is last start offset is 0x100, ends at 0x110 so 0x10 + last offset listed in type offset array
    LZDecompressWram(gTMCaseDiscTypes1_Pal, sTMSpritePaletteBuffer); // Decompress the first 16
    LZDecompressWram(gTMCaseDiscTypes2_Pal, sTMSpritePaletteBuffer + 0x100); // Decompress the rest (Only 17 total, this is just Dragon type)
    spritePalette.data = sTMSpritePaletteBuffer + 0x200; //I have two more types fairy and sound so I need 2 more rows
    spritePalette.tag = TM_CASE_TM_TAG; //the 0x100 is to find start position, of pal, based on type offset could make simpler by using type arg
    LoadSpritePalette(&spritePalette);//think don't need change, would make worse not better
} //ok I get it and the offset chart now, god this was confuisng,
//so the entire palette is thing is differenet palettes stacked on top of each other
//17 in total, the size is 16 bytes, which is why the offset increases in groups of 16,
//each 16 is the start of the next palette
//think beacause larger image need entire different set since its still fills up all 16

//added functions for new tm case 
#define sMonIconStill data[3]
static void SpriteCb_MonIcon(struct Sprite *sprite)
{
    if (!sprite->sMonIconStill)
        UpdateMonIconFrame(sprite);
}
#undef sMonIconStill

#define MON_ICON_START_X  0x10
#define MON_ICON_START_Y  0x1d
#define MON_ICON_PADDING  0x20


void LoadMonIconPalettesTinted(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(gMonIconPaletteTable); i++)
    {
        LoadSpritePalette(&gMonIconPaletteTable[i]);
        TintPalette_GrayScale2(&gPlttBufferUnfaded[0x170 + i*16], 16);
    }
}


static void DrawPartyMonIcons(void)
{
    u8 i;
    u16 species;
    u8 icon_x = 0;
    u8 icon_y = 0;

    LoadMonIconPalettesTinted();

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        //calc icon position (centered)
        if (gPlayerPartyCount == 1)
        {
            icon_x = MON_ICON_START_X;
            icon_y = MON_ICON_START_Y;
        }
        else if (gPlayerPartyCount == 2)
        {
            icon_x = i < 2 ? MON_ICON_START_X + MON_ICON_PADDING*0.5 + MON_ICON_PADDING * i : MON_ICON_START_X + MON_ICON_PADDING*0.5 + MON_ICON_PADDING * (i - 2);
            icon_y = MON_ICON_START_Y + MON_ICON_PADDING*0.5;
        }else if (gPlayerPartyCount == 3)
        {
            icon_x = i < 3 ? MON_ICON_START_X + MON_ICON_PADDING * i : MON_ICON_START_X + MON_ICON_PADDING * (i - 3);
            icon_y = MON_ICON_START_Y + MON_ICON_PADDING*0.5;
        }
        else if (gPlayerPartyCount == 4)
        {
            icon_x = i < 2 ? MON_ICON_START_X + MON_ICON_PADDING*0.5 + MON_ICON_PADDING * i : MON_ICON_START_X + MON_ICON_PADDING*0.5 + MON_ICON_PADDING * (i - 2);
            icon_y = i < 2 ? MON_ICON_START_Y : MON_ICON_START_Y + MON_ICON_PADDING;
        }
        else
        {
            icon_x = i < 3 ? MON_ICON_START_X + MON_ICON_PADDING * i : MON_ICON_START_X + MON_ICON_PADDING * (i - 3);
            icon_y = i < 3 ? MON_ICON_START_Y : MON_ICON_START_Y + MON_ICON_PADDING;
        }
        //get species
        species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);

        //create icon sprite

        spriteIdData[i] = CreateMonIcon(species, SpriteCb_MonIcon, icon_x, icon_y, 1, GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY), TRUE);


        //Set priority, stop movement and save original palette position
        gSprites[spriteIdData[i]].oam.priority = 0;
        StartSpriteAnim(&gSprites[spriteIdData[i]], 4); //full stop
        spriteIdPalette[i] = gSprites[spriteIdData[i]].oam.paletteNum; //save correct palette number to array
    }
}

/*can potentially experiment with this for future dex nav setup where things are fully blacked out
so its blacked out on route unless you've already caught the mon (or mon in evo chain?)
but when you see it on the route it'll reveal the mon so you can see the progress for revealing encounters
for dexnav to work think I may need to make a separate mon seen value*/
#define MON_TINT_LOGIC
static void TintPartyMonIcons(u16 tm, s32 itemIndex)
{
    u8 i;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(7, 11));
        
        if (itemIndex == -2) //I'm so stupid this was so simple smh, ok, ensures that mon sprite is faded if on close tm case option
        {
            gSprites[spriteIdData[i]].oam.objMode = ST_OAM_OBJ_BLEND;//gMonIconPaletteIndices[species];
        }
        else if (!CanMonLearnTMHM(&gPlayerParty[i], tm))//if cant learn tmhm grey out, 
        {
            gSprites[spriteIdData[i]].oam.objMode = ST_OAM_OBJ_BLEND;
        }
        else
        {
            gSprites[spriteIdData[i]].oam.objMode = ST_OAM_OBJ_NORMAL;//gMonIconPaletteIndices[species];
        }

    }

}

static void DestroyPartyMonIcons(void)
{
    u8 i;
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        DestroyMonIcon(&gSprites[spriteIdData[i]]);
        FreeMonIconPalettes();
    }
}
