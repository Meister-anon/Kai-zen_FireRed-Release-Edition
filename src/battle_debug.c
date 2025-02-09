#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_debug.h"
#include "battle_util.h"
#include "battle_message.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "scanline_effect.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "item.h"
#include "task.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "strings.h"
#include "list_menu.h"
#include "decompress.h"
#include "trainer_pokemon_sprites.h"
#include "malloc.h"
#include "menu_helpers.h"
#include "string_util.h"
#include "util.h"
#include "data.h"
#include "reshow_battle_screen.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/party_menu.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/rgb.h"
#include "constants/hold_effects.h"

#if DEBUG_BATTLE_MENU == TRUE
#define MAX_MODIFY_DIGITS 4

//Sprites
#define PAL_TAG_ARROWS    0x1000
#define TILE_TAG_ARROWS   30000

static const struct OamData sOamData_Arrow =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const u32 sArrowSheet_Gfx[] = INCBIN_U32("graphics/interface/arrow_sheet.4bpp.lz");
static const u32 sArrowSheet_Pal[] = INCBIN_U32("graphics/interface/arrow_sheet.gbapal.lz");

static const struct CompressedSpriteSheet sSpriteSheet_Arrows =
{
    .data = sArrowSheet_Gfx,
    .size = 8*8,
    .tag = TILE_TAG_ARROWS,
};

static const struct CompressedSpritePalette sSpritePalette_Arrow =
{
    sArrowSheet_Pal, PAL_TAG_ARROWS
};

static const union AnimCmd sAnim_Arrow_Right[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Arrow_Down[] =
{
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Arrow_Up[] =
{
    ANIMCMD_FRAME(1, 0, .vFlip=TRUE),
    ANIMCMD_END,
};

enum {
    ARROW_RIGHT,
    ARROW_DOWN,
    ARROW_UP,
};

static const union AnimCmd *const sAnims_Arrow[] =
{
    [ARROW_RIGHT] = sAnim_Arrow_Right,
    [ARROW_DOWN]  = sAnim_Arrow_Down,
    [ARROW_UP]    = sAnim_Arrow_Up,
};

static const struct SpriteTemplate sSpriteTemplate_Arrow =
{
    .tileTag = TILE_TAG_ARROWS,
    .paletteTag = PAL_TAG_ARROWS,
    .oam = &sOamData_Arrow,
    .anims = sAnims_Arrow,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

struct BattleDebugModifyArrows
{
    u8 arrowSpriteId[2];
    u16 minValue;
    u16 maxValue;
    int currValue;
    u8 currentDigit:4;
    u8 maxDigits:4;
    u8 charDigits[MAX_MODIFY_DIGITS];
    void *modifiedValPtr;
    u8 typeOfVal;
};

struct BattleDebugMenu
{
    u8 battlerId:2;
    u8 aiBattlerId:2;

    u8 battlerWindowId;

    u8 mainListWindowId;
    u8 mainListTaskId;
    u8 currentMainListItemId;

    u8 secondaryListWindowId;
    u8 secondaryListTaskId;
    u8 currentSecondaryListItemId;
    u8 secondaryListItemCount;

    u8 modifyWindowId;

    u8 activeWindow;

    struct BattleDebugModifyArrows modifyArrows;
    const struct BitfieldInfo *bitfield;
    bool8 battlerWasChanged[MAX_BATTLERS_COUNT];

    u8 aiViewState;

    u8 aiMonSpriteId;
    u8 aiMovesWindowId;

    union
    {
        u8 aiIconSpriteIds[MAX_BATTLERS_COUNT];
        u8 aiPartyIcons[PARTY_SIZE];
    } spriteIds;
};

struct __attribute__((__packed__)) BitfieldInfo
{
    u8 bitsCount;
    u8 currBit;
};

enum
{
    LIST_ITEM_MOVES,
    LIST_ITEM_ABILITY,
    LIST_ITEM_HELD_ITEM,
    LIST_ITEM_SECONDARY_ITEM,
    LIST_ITEM_PP,
    LIST_ITEM_TYPES,
    LIST_ITEM_STATS,
    LIST_ITEM_STAT_STAGES,
    LIST_ITEM_STATUS1,
    LIST_ITEM_STATUS2,
    LIST_ITEM_STATUS3,
    LIST_ITEM_SIDE_STATUS,
    LIST_ITEM_AI,
    LIST_ITEM_VARIOUS,
    LIST_ITEM_COUNT
};

enum
{
    ACTIVE_WIN_MAIN,
    ACTIVE_WIN_SECONDARY,
    ACTIVE_WIN_MODIFY
};

enum
{
    VAL_U8,
    VAL_U16,
    VAL_U32,
    VAL_BITFIELD_8,
    VAL_BITFIELD_16,
    VAL_BITFIELD_32,
    VAR_SIDE_STATUS,
    VAR_SHOW_HP,
    VAR_SUBSTITUTE,
    VAR_IN_LOVE,
    VAR_SLEEP_TIMER,
    VAR_FREEZE_TIMER,
    VAR_TOXIC_COUNTER,
    VAR_U16_4_ENTRIES,
    VAL_S8,
    VAL_ALL_STAT_STAGES,
};

enum
{
    LIST_SIDE_REFLECT,
    LIST_SIDE_LIGHTSCREEN,
    LIST_SIDE_SPIKES,
    LIST_SIDE_SAFEGUARD,
    LIST_SIDE_MIST,
};

enum
{
    VARIOUS_SHOW_HP,
    VARIOUS_SUBSTITUTE_HP,
    VARIOUS_IN_LOVE,
    VARIOUS_SLEEP_TIMER,
    VARIOUS_FREEZE_TIMER,
    VARIOUS_TOXIC_COUNTER,
};

// Static Declarations
static const u8 *GetHoldEffectName(u16 holdEffect);
//static bool32 IsBattlerAlive(u32 battler);

// const rom data
static const u8 sText_HP[] = _("HP");
static const u8 sText_Attack[] = _("ATTACK");
static const u8 sText_Defense[] = _("DEFENSE");
static const u8 sText_SpAtk[] = _("SP. ATK");
static const u8 sText_SpDef[] = _("SP. DEF");
static const u8 sText_Speed[] = _("SPEED");
static const u8 sText_HoldEffect[] = _("Hold Effect");
static const u8 sText_Ability[] = _("Ability");
static const u8 sText_Moves[] = _("Moves");
static const u8 sText_Stats[] = _("Stats");
static const u8 sText_StatStages[] = _("Stat Stages");
static const u8 sText_Status1[] = _("Status1");
static const u8 sText_Status2[] = _("Status2");
static const u8 sText_Status3[] = _("Status3");
static const u8 sText_HeldItem[] = _("Held Item");
static const u8 sText_SecondaryItem[] = _("2nd Item");
static const u8 sText_SideStatus[] = _("Side Status");
static const u8 sText_MaxHp[] = _("HP Max");
static const u8 sText_CurrHp[] = _("HP Current");
static const u8 sText_Freeze[] = _("freeze");
static const u8 sText_Infested[] = _("infested");
static const u8 sText_ToxicPoison[] = _("toxic poison");
static const u8 sText_SleepTimer[] = _("sleep timer");
static const u8 sText_FreezeTimer[] = _("freeze timer");
static const u8 sText_ToxicCounter[] = _("toxic counter");
static const u8 sText_SetTimers[] =_("Set timers in various");
static const u8 sText_Flinch[] = _("Flinch");
static const u8 sText_Uproar[] = _("Uproar");
static const u8 sText_Bide[] = _("Bide");
static const u8 sText_LockConfuse[] = _("Lock Confuse");
static const u8 sText_MultipleTurns[] = _("MultipleTurns");
static const u8 sText_FocusEnergy[] = _("Focus Energy");
static const u8 sText_Transformed[] = _("Transformed");
static const u8 sText_Recharge[] = _("Recharge");
static const u8 sText_Rage[] = _("Rage");
static const u8 sText_Substitute[] = _("Substitute");
static const u8 sText_SubstituteHp[] = _("Substitute HP");
static const u8 sText_DestinyBond[] = _("Destiny Bond");
static const u8 sText_CantEscape[] = _("Cant Escape");
static const u8 sText_Nightmare[] = _("Nightmare");
static const u8 sText_Cursed[] = _("Cursed");
static const u8 sText_Foresight[] = _("Foresighted");
static const u8 sText_DefenseCurl[] = _("Def Curled");
static const u8 sText_Tormented[] = _("Tormented");
static const u8 sText_AlwaysHits[] = _("Sure Hit");
static const u8 sText_ChargedUp[] = _("Charged Up");
static const u8 sText_Rooted[] = _("Rooted");
static const u8 sText_Yawned[] = _("Yawned");
static const u8 sText_Minimized[] = _("Minimized");
static const u8 sText_NoCrit[] = _("No Crit");
static const u8 sText_Imprisoned[] = _("Imprison");
static const u8 sText_Reflect[] = _("Reflect");
static const u8 sText_LightScreen[] = _("Light Screen");
static const u8 sText_Spikes[] = _("Spikes");
static const u8 sText_Safeguard[] = _("Safeguard");
static const u8 sText_Mist[] = _("Mist");
static const u8 sText_ShowOpponentHP[] = _("Opponent Hp");
static const u8 sText_Types[] = _("Types");
static const u8 sText_PP[] = _("PP");
static const u8 sText_AI[] = _("AI");
static const u8 sText_NoBadMoves[] = _("No Bad Moves");
static const u8 sText_Viability[] = _("Viability");
static const u8 sText_TryFaint[] = _("Try Faint");
static const u8 sText_SetUpFirstTurn[] = _("Setup 1 turn");
static const u8 sText_Risky[] = _("Risky");
static const u8 sText_StrongestMove[] = _("Most dmg move");
static const u8 sText_Various[] = _("Various");
static const u8 sText_ShowHP[] = _("Show HP");
static const u8 sText_PreferBatonPass[] = _("Baton Pass");
static const u8 sText_InDoubles[] = _("In Doubles");
static const u8 sText_HpAware[] = _("HP aware");
static const u8 sText_Unknown[] = _("Unknown");
static const u8 sText_InLove[] = _("In Love");

static const u8 sText_EmptyString[] = _("");

static const struct BitfieldInfo sStatus1Bitfield[] =
{
    {/*Sleep*/ 1, 1}, //without sleep timer may not work
    {/*Poison*/ 1, 2},
    {/*Burn*/ 1, 3},
    {/*Freeze*/ 1, 4}, //without freeze timer is always just frostbite
    {/*Paralysis*/1, 5},
    {/*Toxic Poison*/ 1, 6},
     {/*Infested*/ 1, 8}, //infested
    //{/*Toxic Counter*/ 4, 8}, //not accessible w this, moved to its own field
};//looking at various realize can do alt effects with that
//will need to do major edits to base menu for my changes
//but all doable

enum Status2{
    CONFUSION = 0,
    FLINCH = 3,
    UPROAR = 4,
    EMERGENCY_EXIT = 7,
    BIDE = 8,
    FREE = 9,
    LOCK_CONFUSE = 10,
    MULTIPLE_TURNS = 12,
    POWDER = 14,
    FOCUS_ENERGY = 20,
    TRANSFORMED = 21,
    RECHARGE = 22,
    RAGE = 23,
    SUBSTITUTE = 24,
    DESTINY_BOND = 25,
    ESCAPE_PREVENTION = 26,
    NIGHTMARE = 27,
    CURSED = 28,
    FORESIGHT = 29,
    DEFENSE_CURL = 30,
    TORMENT = 31
};


//FIRST number how many bytes status takes up
//Second value the byte value of the status
//need to match to status value in constants battle.h
static const struct BitfieldInfo sStatus2Bitfield[] =
{
    {/*Confusion*/ 3, 0},
    {/*Flinch*/ 1, 3},
    {/*Uproar*/ 3, 4},
    // Bit 7 is unused.  //for emergency exit
    {/*Bide*/ 1, 8}, //setting this doesn't work correctly oh right I added a timer?
    {/*Lock Confuse*/ 2, 10},
    {/*Multiple Turns*/ 1, 12},
    // Wrap bits are omitted. Done in various.
    // In Love bits are omitted. Done in various.
    {/*(Focus Energy*/ 1, 20},
    {/*Transformed*/ 1, 21}, //- <- not on list
    {/*Recharge*/ 1, 22},
    {/*Rage*/ 1, 23},
    {/*Substitute*/ 1, 24},
    {/*Destiny bond*/ 1, 25}, //doesn't work?
    {/*Can't escape*/ 1, 26},//ok seems somehow out of alignment, setting substitute activated rage??
    {/*Nightmares*/ 1, 27},
    {/*Cursed*/ 1, 28},
    {/*Foresighted*/ 1, 29},
    {/*Defense Curled*/ 1, 30},
    {/*Tormented*/ 1, 31},
};//ok yeah weirdly out of allignment, setting cant escape did destiny bond?
//sigh even worse appears  to have to be set twice, has to set it, wait a turn for it to count down to 0
//then SET IT AGAIN, and then kill for it to work!!!

static const struct BitfieldInfo sStatus3Bitfield[] =
{
    {/*Always hits*/ 2, 4},
    //*Perish Song*/ 1, 5},
    // On Air 1, 6,
    // Underground 1, 7,
    {/*Minimized*/ 1, 8},
    {/*Charged Up*/ 1, 9},
    {/*Rooted*/ 1, 10},
    {/*Yawn*/ 2, 11},
    {/*Imprison*/ 1, 13},
    // Grudge 1, 14,
    {/*No Crit*/ 1, 15},
    // Mudsport 1, 16,
    // Watersport 1, 17,
    // Underwater 1, 18,
    // Intimidated Mons 1, 19,
    // Traced 1, 20,
};

static const struct BitfieldInfo sAIBitfield[] =
{
    {/*Check bad move*/ 1, 0},
    {/*Viability*/ 1, 1},
    {/*Try To Faint*/ 1, 2},
    {/*Set up first turn*/ 1, 3},
    {/*Risky*/ 1, 4},
    {/*Prefer Strongest Move*/ 1, 5},
    {/*Prefer Baton Pass*/ 1, 6},
    {/*In Doubles*/ 1, 7},
    {/*Hp aware*/ 1, 8},
    {/*Unknown*/ 1, 9},
};


static const struct ListMenuItem sMainListItems[] =
{
    {sText_Moves, LIST_ITEM_MOVES},
    {sText_Ability, LIST_ITEM_ABILITY},
    {sText_HeldItem, LIST_ITEM_HELD_ITEM},
    {sText_SecondaryItem, LIST_ITEM_SECONDARY_ITEM},
    {sText_PP, LIST_ITEM_PP},
    {sText_Types, LIST_ITEM_TYPES},
    {sText_Stats, LIST_ITEM_STATS},
    {sText_StatStages, LIST_ITEM_STAT_STAGES},
    {sText_Status1, LIST_ITEM_STATUS1},
    {sText_Status2, LIST_ITEM_STATUS2},
    {sText_Status3, LIST_ITEM_STATUS3},
    {sText_SideStatus, LIST_ITEM_SIDE_STATUS},
    {sText_AI, LIST_ITEM_AI},
    {sText_Various, LIST_ITEM_VARIOUS},
};

static const struct ListMenuItem sVariousListItems[] =
{
    {sText_ShowHP, VARIOUS_SHOW_HP},
    {sText_SubstituteHp, VARIOUS_SUBSTITUTE_HP},
    {sText_InLove, VARIOUS_IN_LOVE},
    {sText_SleepTimer, VARIOUS_SLEEP_TIMER},
    {sText_FreezeTimer, VARIOUS_FREEZE_TIMER},
    {sText_ToxicCounter, VARIOUS_TOXIC_COUNTER},
};

static const struct ListMenuItem sAIListItems[] =
{
    {sText_NoBadMoves, 0},
    {sText_Viability, 1},
    {sText_TryFaint, 2},
    {sText_SetUpFirstTurn, 3},
    {sText_Risky, 4},
    {sText_StrongestMove, 5},
    {sText_PreferBatonPass, 6},
    {sText_InDoubles, 7},
    {sText_HpAware, 8},
    {sText_Unknown, 9},
};

static const struct ListMenuItem sStatsListItems[] =
{
    {sText_CurrHp, 0},
    {sText_MaxHp, 1},
    {sText_Attack, 2},
    {sText_Defense, 3},
    {sText_Speed, 4},
    {sText_SpAtk, 5},
    {sText_SpDef, 6},
};

static const struct ListMenuItem sStatus1ListItems[] =
{
    {gText_Sleep, 0},
    {gText_Poison, 1},
    {gText_Burn, 2},
    {sText_Freeze, 3},
    {gText_Paralysis, 4},
    {sText_ToxicPoison, 5},
    {sText_Infested, 6},
    {sText_SetTimers, 7},
};

//must match order of bit field
static const struct ListMenuItem sStatus2ListItems[] =
{
    {gText_Confusion, 0},
    {sText_Flinch, 1},
    {sText_Uproar, 2},
    {sText_Bide, 3},
    {sText_LockConfuse, 4},
    {sText_MultipleTurns, 5},
    {sText_FocusEnergy, 6},
    {COMPOUND_STRING("Transform"), 7},
    {sText_Recharge, 8},
    {sText_Rage, 9},
    {sText_Substitute, 10},
    {sText_DestinyBond, 11},
    {sText_CantEscape, 12},
    {sText_Nightmare, 13},
    {sText_Cursed, 14},
    {sText_Foresight, 15},
    {sText_DefenseCurl, 16},
    {sText_Tormented, 17},
};//sigh idk how but the count is off that's why
//in statuses destiny bond is 11 not 10

static const struct ListMenuItem sStatus3ListItems[] =
{
    {sText_AlwaysHits, 0},
    {sText_Minimized, 1},
    {sText_ChargedUp, 2},
    {sText_Rooted, 3},
    {sText_Yawned, 4},
    {sText_Imprisoned, 5},
    {sText_NoCrit, 6},
};

static const struct ListMenuItem sSideStatusListItems[] =
{
    {sText_Reflect, LIST_SIDE_REFLECT},
    {sText_LightScreen, LIST_SIDE_LIGHTSCREEN},
    {sText_Spikes, LIST_SIDE_SPIKES},
    {sText_Safeguard, LIST_SIDE_SAFEGUARD},
    {sText_Mist, LIST_SIDE_MIST},
};

static const struct ListMenuItem sSecondaryListItems[] =
{
    {sText_EmptyString, 0},
    {sText_EmptyString, 1},
    {sText_EmptyString, 2},
    {sText_EmptyString, 3},
    {sText_EmptyString, 4},
    {sText_EmptyString, 5},
    {sText_EmptyString, 6},
    {sText_EmptyString, 7},
    {sText_EmptyString, 8},
};


static const struct ListMenuTemplate sMainListTemplate =
{
    .items = sMainListItems,
    .moveCursorFunc = NULL,
    .itemPrintFunc = NULL,
    .totalItems = ARRAY_COUNT(sMainListItems),
    .maxShowed = 6,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NORMAL_COPY_1,
    .cursorKind = 0
};

static const struct ListMenuTemplate sSecondaryListTemplate =
{
    .items = sSecondaryListItems,
    .moveCursorFunc = NULL,
    .itemPrintFunc = NULL,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_SMALL,
    .cursorKind = 0
};


static const struct WindowTemplate sMainListWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 3,
    .width = 9,
    .height = 12,
    .paletteNum = 0xF,
    .baseBlock = 0x2
};

static const struct WindowTemplate sSecondaryListWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 12,
    .tilemapTop = 3,
    .width = 17,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0xA0
};

static const struct WindowTemplate sModifyWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 25,
    .tilemapTop = 2,
    .width = 4,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0x240
};

static const struct WindowTemplate sBattlerWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 10,
    .tilemapTop = 0,
    .width = 14,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0x340
};

static const struct BgTemplate sBgTemplates[] =
{
   {
       .bg = 0,
       .charBaseIndex = 0,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 1,
       .charBaseIndex = 2,
       .mapBaseIndex = 20,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   }
};

static const u8 sBitsToMaxDigit[] =
{
    [0] = 0,
    [1] = 1, // max 1
    [2] = 1, // max 3
    [3] = 1, // max 7
    [4] = 2, // max 15
    [5] = 2, // max 31
    [6] = 2, // max 63
    [7] = 3, // max 127
    [8] = 3, // max 255
};

static const bool8 sHasChangeableEntries[LIST_ITEM_COUNT] =
{
    [LIST_ITEM_MOVES] = TRUE,
    [LIST_ITEM_PP] = TRUE,
    [LIST_ITEM_ABILITY] = TRUE,
    [LIST_ITEM_TYPES] = TRUE,
    [LIST_ITEM_HELD_ITEM] = TRUE,
    [LIST_ITEM_SECONDARY_ITEM] = TRUE,
    [LIST_ITEM_STAT_STAGES] = TRUE,
};

static const u16 sBgColor[] = {RGB_WHITE};

// this file's functions
static void Task_DebugMenuFadeOut(u8 taskId);
static void Task_DebugMenuProcessInput(u8 taskId);
static void Task_DebugMenuFadeIn(u8 taskId);
static void PrintOnBattlerWindow(u8 windowId, u8 battlerId);
static void UpdateWindowsOnChangedBattler(struct BattleDebugMenu *data);
static void CreateSecondaryListMenu(struct BattleDebugMenu *data);
static void PrintSecondaryEntries(struct BattleDebugMenu *data);
static void DestroyModifyArrows(struct BattleDebugMenu *data);
static void PrintDigitChars(struct BattleDebugMenu *data);
static void SetUpModifyArrows(struct BattleDebugMenu *data);
static void UpdateBattlerValue(struct BattleDebugMenu *data);
static void UpdateMonData(struct BattleDebugMenu *data);
static u8 GetSideStatusValue(struct BattleDebugMenu *data, bool32 changeStatus, u8 setValue);
static bool32 TryMoveDigit(struct BattleDebugModifyArrows *modArrows, bool32 moveUp);
static void SwitchToDebugView(u8 taskId);
static void SwitchToDebugViewFromAiParty(u8 taskId);

// code
static struct BattleDebugMenu *GetStructPtr(u8 taskId)
{
    u8 *taskDataPtr = (u8 *)(&gTasks[taskId].data[0]);

    return (struct BattleDebugMenu*)(T1_READ_PTR(taskDataPtr));
}

static void SetStructPtr(u8 taskId, void *ptr)
{
    u32 structPtr = (u32)(ptr);
    u8 *taskDataPtr = (u8 *)(&gTasks[taskId].data[0]);

    taskDataPtr[0] = structPtr >> 0;
    taskDataPtr[1] = structPtr >> 8;
    taskDataPtr[2] = structPtr >> 16;
    taskDataPtr[3] = structPtr >> 24;
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_BattleDebugMenu(void)
{
    u8 taskId;
    struct BattleDebugMenu *data;

    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        ResetVramOamAndBgCntRegs();
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ResetAllBgsCoordinatesAndBgCntRegs();
        FreeAllWindowBuffers();
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadPalette(sBgColor, 0, 2);
        LoadPalette(GetOverworldTextboxPalettePtr(), 0xf0, 16);
        gMain.state++;
        break;
    case 4:
        taskId = CreateTask(Task_DebugMenuFadeIn, 0);
        data = AllocZeroed(sizeof(struct BattleDebugMenu));
        SetStructPtr(taskId, data);

        data->battlerId = gBattleStruct->debugBattler;
        data->battlerWindowId = AddWindow(&sBattlerWindowTemplate);
        PutWindowTilemap(data->battlerWindowId);
        PrintOnBattlerWindow(data->battlerWindowId, data->battlerId);

        data->mainListWindowId = AddWindow(&sMainListWindowTemplate);

        gMultiuseListMenuTemplate = sMainListTemplate;
        gMultiuseListMenuTemplate.windowId = data->mainListWindowId;
        data->mainListTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0, DEFAULT_MODE);

        data->currentMainListItemId = 0;
        data->activeWindow = ACTIVE_WIN_MAIN;
        data->secondaryListTaskId = 0xFF;
        CopyWindowToVram(data->mainListWindowId, COPYWIN_BOTH);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(-1, 0, 0x10, 0, 0);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void SwitchToDebugView(u8 taskId)
{
    u32 i;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    FreeMonIconPalettes();
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (data->spriteIds.aiIconSpriteIds[i] != 0xFF)
            FreeAndDestroyMonIconSprite(&gSprites[data->spriteIds.aiIconSpriteIds[i]]);
    }
    FreeAndDestroyMonPicSprite(data->aiMonSpriteId);
    ClearWindowTilemap(data->aiMovesWindowId);
    RemoveWindow(data->aiMovesWindowId);

    gTasks[taskId].func = Task_DebugMenuProcessInput;
}

static void Task_DebugMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_DebugMenuProcessInput;
}

static void Task_DebugMenuProcessInput(u8 taskId)
{
    s32 listItemId = 0;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    // Exit the menu.
    if (JOY_NEW(SELECT_BUTTON) || ((JOY_NEW(B_BUTTON)) && data->activeWindow == ACTIVE_WIN_MAIN))
    {
        BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
        gTasks[taskId].func = Task_DebugMenuFadeOut;
        return;
    }

    // Try changing active battler.
    if (JOY_NEW(START_BUTTON))
    {
        if (data->battlerId++ == gBattlersCount - 1)
            data->battlerId = 0;
        UpdateWindowsOnChangedBattler(data);
    }

    // A main list item is active, handle input.
    if (data->activeWindow == ACTIVE_WIN_MAIN)
    {
        listItemId = ListMenu_ProcessInput(data->mainListTaskId, DEFAULT_MODE);
        if (listItemId != LIST_CANCEL && listItemId != LIST_NOTHING_CHOSEN && listItemId < LIST_ITEM_COUNT)
        {
            data->currentMainListItemId = listItemId;

            // Create the secondary menu list.
            CreateSecondaryListMenu(data);
            PrintSecondaryEntries(data);
            data->activeWindow = ACTIVE_WIN_SECONDARY;
        }
    }
    // Secondary list is active, handle input.
    else if (data->activeWindow == ACTIVE_WIN_SECONDARY)
    {
        listItemId = ListMenu_ProcessInput(data->secondaryListTaskId, DEFAULT_MODE);
        if (listItemId == LIST_CANCEL) //bpress
        {
            DestroyListMenuTask(data->secondaryListTaskId, NULL, NULL);
            ClearStdWindowAndFrameToTransparent(data->secondaryListWindowId, TRUE);
            RemoveWindow(data->secondaryListWindowId);
            data->activeWindow = ACTIVE_WIN_MAIN;
            data->secondaryListTaskId = 0xFF;
        }
        else if (listItemId != LIST_NOTHING_CHOSEN) // a press modify to exclude stat timer in status1
        {
            data->currentSecondaryListItemId = listItemId;
            data->modifyWindowId = AddWindow(&sModifyWindowTemplate);
            FillWindowPixelBuffer(data->modifyWindowId, PIXEL_FILL(0));
            PutWindowTilemap(data->modifyWindowId);
            CopyWindowToVram(data->modifyWindowId, COPYWIN_BOTH);
            SetUpModifyArrows(data);
            PrintDigitChars(data);
            data->activeWindow = ACTIVE_WIN_MODIFY;
        }
    }
    // Handle value modifying.
    else if (data->activeWindow == ACTIVE_WIN_MODIFY)
    {
        if (JOY_NEW(B_BUTTON | A_BUTTON))
        {
            ClearStdWindowAndFrameToTransparent(data->modifyWindowId, TRUE);
            RemoveWindow(data->modifyWindowId);
            DestroyModifyArrows(data);
            data->activeWindow = ACTIVE_WIN_SECONDARY;
        }
        else if (JOY_NEW(DPAD_RIGHT))
        {
            if (data->modifyArrows.currentDigit != (data->modifyArrows.maxDigits - 1))
            {
                data->modifyArrows.currentDigit++;
                gSprites[data->modifyArrows.arrowSpriteId[0]].pos2.x += 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].pos2.x += 6;
            }
        }
        else if (JOY_NEW(DPAD_LEFT))
        {
            if (data->modifyArrows.currentDigit != 0)
            {
                data->modifyArrows.currentDigit--;
                gSprites[data->modifyArrows.arrowSpriteId[0]].pos2.x -= 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].pos2.x -= 6;
            }
        }
        else if (JOY_NEW(DPAD_UP))
        {
            if (TryMoveDigit(&data->modifyArrows, TRUE))
            {
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                PrintSecondaryEntries(data);
            }
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            if (TryMoveDigit(&data->modifyArrows, FALSE))
            {
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                PrintSecondaryEntries(data);
            }
        }
    }
}

static void Task_DebugMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        struct BattleDebugMenu *data = GetStructPtr(taskId);
        DestroyListMenuTask(data->mainListTaskId, 0, 0);
        if (data->secondaryListTaskId != 0xFF)
            DestroyListMenuTask(data->secondaryListTaskId, 0, 0);

        FreeAllWindowBuffers();
        UpdateMonData(data);
        gBattleStruct->debugBattler = data->battlerId;
        Free(data);
        DestroyTask(taskId);
        SetMainCallback2(ReshowBattleScreenAfterMenu);
    }
}

static void PrintOnBattlerWindow(u8 windowId, u8 battlerId)
{
    u8 text[POKEMON_NAME_LENGTH + 10];

    text[0] = CHAR_0 + battlerId;
    text[1] = CHAR_SPACE;
    text[2] = CHAR_HYPHEN;
    text[3] = CHAR_SPACE;
    StringCopy(&text[4], gBattleMons[battlerId].nickname);

    FillWindowPixelBuffer(windowId, 0x11);
    AddTextPrinterParameterized(windowId, FONT_NORMAL, text, 0, 0, 0, NULL);
    CopyWindowToVram(windowId, COPYWIN_BOTH);
}

static void UpdateWindowsOnChangedBattler(struct BattleDebugMenu *data)
{
    PrintOnBattlerWindow(data->battlerWindowId, data->battlerId);
    if (data->secondaryListTaskId != 0xFF)
    {
        DestroyListMenuTask(data->secondaryListTaskId, 0, 0);
        RemoveWindow(data->secondaryListWindowId);
        CreateSecondaryListMenu(data);
        data->currentSecondaryListItemId = 0;
        PrintSecondaryEntries(data);
    }
    if (data->activeWindow == ACTIVE_WIN_MODIFY)
    {
        DestroyModifyArrows(data);
        SetUpModifyArrows(data);
        PrintDigitChars(data);
    }
}


static void CreateSecondaryListMenu(struct BattleDebugMenu *data)
{
    struct WindowTemplate winTemplate;
    struct ListMenuTemplate listTemplate;
    u8 itemsCount = 1;

    winTemplate = sSecondaryListWindowTemplate;
    listTemplate = sSecondaryListTemplate;

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_ABILITY:
        itemsCount = 1;
        break;
    case LIST_ITEM_HELD_ITEM:
        itemsCount = 1;
        break;
    case LIST_ITEM_SECONDARY_ITEM:
        itemsCount = 1;
        break;
    case LIST_ITEM_TYPES:
        itemsCount = 2;
        break;
    case LIST_ITEM_MOVES:
        itemsCount = 5;
        break;
    case LIST_ITEM_PP:
        itemsCount = 4;
        break;
    case LIST_ITEM_STATS:
        listTemplate.items = sStatsListItems;
        itemsCount = ARRAY_COUNT(sStatsListItems);
        break;
    case LIST_ITEM_STAT_STAGES:
        itemsCount = 8;
        break;
    case LIST_ITEM_STATUS1:
        listTemplate.items = sStatus1ListItems;
        itemsCount = ARRAY_COUNT(sStatus1ListItems);
        data->bitfield = sStatus1Bitfield;
        break;
    case LIST_ITEM_STATUS2:
        listTemplate.items = sStatus2ListItems;
        itemsCount = ARRAY_COUNT(sStatus2ListItems);
        data->bitfield = sStatus2Bitfield;
        winTemplate.height = 1;
        break;
    case LIST_ITEM_STATUS3:
        listTemplate.items = sStatus3ListItems;
        itemsCount = ARRAY_COUNT(sStatus3ListItems);
        data->bitfield = sStatus3Bitfield;
        break;
    case LIST_ITEM_AI:
        listTemplate.items = sAIListItems;
        itemsCount = ARRAY_COUNT(sAIListItems);
        data->bitfield = sAIBitfield;
        break;
    case LIST_ITEM_VARIOUS:
        listTemplate.items = sVariousListItems;
        itemsCount = ARRAY_COUNT(sVariousListItems);
        break;
    case LIST_ITEM_SIDE_STATUS:
        listTemplate.items = sSideStatusListItems;
        itemsCount = ARRAY_COUNT(sSideStatusListItems);
        break;
    }

    data->secondaryListItemCount = itemsCount;
    winTemplate.height *= itemsCount;
    data->secondaryListWindowId = AddWindow(&winTemplate);

    listTemplate.totalItems = itemsCount;
    listTemplate.maxShowed = itemsCount;
    if (listTemplate.maxShowed > 7 && !sHasChangeableEntries[data->currentMainListItemId])
        listTemplate.maxShowed = 7;
    listTemplate.windowId = data->secondaryListWindowId;

    data->secondaryListTaskId = ListMenuInit(&listTemplate, 0, 0, DEFAULT_MODE);
    CopyWindowToVram(data->secondaryListWindowId, COPYWIN_BOTH);
}

static void PadString(const u8 *src, u8 *dst)
{
    u32 i;

    for (i = 0; i < 17 && src[i] != EOS; i++)
        dst[i] = src[i];

    for (; i < 17; i++)
        dst[i] = CHAR_SPACE;

    dst[i] = EOS;
}

static const u8 sTextAll[] = _("All");

static void PrintSecondaryEntries(struct BattleDebugMenu *data)
{
    u8 text[20];
    s32 i;
    struct TextPrinterTemplate printer;
    u8 yMultiplier;

    // Do not print entries if they are not changing.
    if (!sHasChangeableEntries[data->currentMainListItemId])
        return;

    yMultiplier = (GetFontAttribute(sSecondaryListTemplate.fontId, 1) + sSecondaryListTemplate.itemVerticalPadding);

    printer.windowId = data->secondaryListWindowId;
    printer.fontId = FONT_SMALL;
    printer.unk = 0;
    printer.letterSpacing = 0;
    printer.lineSpacing = 1;
    printer.fgColor = 2;
    printer.bgColor = 1;
    printer.shadowColor = 3;
    printer.x = sSecondaryListTemplate.item_X;
    printer.currentX = sSecondaryListTemplate.item_X;
    printer.currentChar = text;

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_MOVES:
    case LIST_ITEM_PP:
        for (i = 0; i < 4; i++)
        {
            PadString(gMoveNames[gBattleMons[data->battlerId].moves[i]], text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        // Allow changing all moves at once. Useful for testing in wild doubles.
        if (data->currentMainListItemId == LIST_ITEM_MOVES)
        {
            PadString(sTextAll, text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    case LIST_ITEM_ABILITY:
        PadString(gAbilityNames[gBattleMons[data->battlerId].ability], text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_HELD_ITEM:
        PadString(ItemId_GetName(gBattleMons[data->battlerId].item), text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_SECONDARY_ITEM:
        PadString(ItemId_GetName(gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)]), text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_TYPES:
        for (i = 0; i < 2; i++)
        {
            u8 *types = &gBattleMons[data->battlerId].type1;

            PadString(gTypeNames[types[i]], text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    case LIST_ITEM_STAT_STAGES:
        for (i = 0; i < NUM_BATTLE_STATS - 1; i++)
        {
            u8 *txtPtr = StringCopy(text, gStatNamesTable[STAT_ATK + i]);
            txtPtr[0] = CHAR_SPACE;
            if (gBattleMons[data->battlerId].statStages[STAT_ATK + i] >= DEFAULT_STAT_STAGE)
            {
                txtPtr[1] = CHAR_PLUS;
                txtPtr[2] = CHAR_0 + (gBattleMons[data->battlerId].statStages[STAT_ATK + i] - DEFAULT_STAT_STAGE);
            }
            else
            {
                txtPtr[1] = CHAR_HYPHEN;
                txtPtr[2] = CHAR_6 - (gBattleMons[data->battlerId].statStages[STAT_ATK + i]);
            }
            txtPtr[3] = EOS;

            PadString(text, text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        // Allow changing all stat stages at once.
        PadString(sTextAll, text);
        printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    }
}

static void DestroyModifyArrows(struct BattleDebugMenu *data)
{
    FreeSpritePaletteByTag(sSpritePalette_Arrow.tag);
    if (data->modifyArrows.arrowSpriteId[0] != 0xFF)
        DestroySprite(&gSprites[data->modifyArrows.arrowSpriteId[0]]);
    if (data->modifyArrows.arrowSpriteId[1] != 0xFF)
        DestroySprite(&gSprites[data->modifyArrows.arrowSpriteId[1]]);
}

static void PrintDigitChars(struct BattleDebugMenu *data)
{
    s32 i;
    u8 text[MAX_MODIFY_DIGITS + 1];

    for (i = 0; i < data->modifyArrows.maxDigits; i++)
        text[i] = data->modifyArrows.charDigits[i];

    text[i] = EOS;

    AddTextPrinterParameterized(data->modifyWindowId, FONT_NORMAL, text, 3, 0, 0, NULL);
}

static const u32 GetBitfieldToAndValue(u32 currBit, u32 bitsCount)
{
    u32 i;
    u32 toAnd = 0;

    for (i = 0; i < bitsCount; i++)
        toAnd |= (1 << (currBit + i));

    return toAnd;
}

static const u32 GetBitfieldValue(u32 value, u32 currBit, u32 bitsCount)
{
    return (value & (GetBitfieldToAndValue(currBit, bitsCount))) >> currBit;
}

static void UpdateBattlerValue(struct BattleDebugMenu *data)
{
    u32 i;
    if (data->currentMainListItemId == LIST_ITEM_AI)
        gBattleStruct->debugAISet = TRUE;

    switch (data->modifyArrows.typeOfVal)
    {
    case VAL_U8:
        *(u8 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_S8:
        *(s8 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_U16:
        *(u16 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAR_U16_4_ENTRIES:
        ((u16 *)(data->modifyArrows.modifiedValPtr))[0] = data->modifyArrows.currValue;
        ((u16 *)(data->modifyArrows.modifiedValPtr))[1] = data->modifyArrows.currValue;
        ((u16 *)(data->modifyArrows.modifiedValPtr))[2] = data->modifyArrows.currValue;
        ((u16 *)(data->modifyArrows.modifiedValPtr))[3] = data->modifyArrows.currValue;
        break;
    case VAL_ALL_STAT_STAGES:
        for (i = 0; i < NUM_BATTLE_STATS; i++)
            gBattleMons[data->battlerId].statStages[i] = data->modifyArrows.currValue;
        break;
    case VAL_U32:
        *(u32 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_BITFIELD_32:
        *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~(GetBitfieldToAndValue(data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount));
        *(u32 *)(data->modifyArrows.modifiedValPtr) |= (data->modifyArrows.currValue << data->bitfield[data->currentSecondaryListItemId].currBit);
        break;
    case VAR_SIDE_STATUS:
        GetSideStatusValue(data, TRUE, data->modifyArrows.currValue);// = data->modifyArrows.currValue;
        break; //don't understand
    case VAR_SHOW_HP:
        (*(struct BattleSpriteInfo*)(data->modifyArrows.modifiedValPtr)).hpNumbersNoBars = data->modifyArrows.currValue;
        break;
    case VAR_SUBSTITUTE:
        *(u8 *)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        if (*(u8 *)(data->modifyArrows.modifiedValPtr) == 0)
        {
            gBattleMons[data->battlerId].status2 &= ~STATUS2_SUBSTITUTE;
            gBattleSpritesDataPtr->battlerData[data->battlerId].behindSubstitute = 0;
        }
        else
        {
            gBattleMons[data->battlerId].status2 |= STATUS2_SUBSTITUTE;
            gBattleSpritesDataPtr->battlerData[data->battlerId].behindSubstitute = 1;
        }
        break;
    case VAR_IN_LOVE:
        if (data->modifyArrows.currValue)
        {
            if (IsBattlerAlive(BATTLE_OPPOSITE(data->battlerId)))
                gBattleMons[data->battlerId].status2 |= STATUS2_INFATUATED_WITH(BATTLE_OPPOSITE(data->battlerId));
            else
                gBattleMons[data->battlerId].status2 |= STATUS2_INFATUATED_WITH(BATTLE_PARTNER(BATTLE_OPPOSITE(data->battlerId)));
        }
        else
        {
            gBattleMons[data->battlerId].status2 &= ~STATUS2_INFATUATION;
        }
        break;
    case VAR_SLEEP_TIMER:
        if (data->modifyArrows.currValue)
        {
            gBattleStruct->SleepTimer[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)] = data->modifyArrows.currValue;
        }
        else
        {
            gBattleMons[data->battlerId].status1 &= ~STATUS1_SLEEP;
        }
        break;
    case VAR_FREEZE_TIMER:
        if (data->modifyArrows.currValue)
            gDisableStructs[data->battlerId].FrozenTurns = data->modifyArrows.currValue;
        break;
    
    case VAR_TOXIC_COUNTER:
        if (data->modifyArrows.currValue)
            gBattleStruct->ToxicTurnCounter[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)] = data->modifyArrows.currValue;
        break;
    }
    data->battlerWasChanged[data->battlerId] = TRUE;
}

static u32 CharDigitsToValue(u8 *charDigits, u8 maxDigits)
{
    s32 i;
    u8 id = 0;
    u32 newValue = 0;
    u8 valueDigits[MAX_MODIFY_DIGITS];

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        valueDigits[i] = charDigits[i] - CHAR_0;

    if (maxDigits >= MAX_MODIFY_DIGITS)
        newValue += valueDigits[id++] * 1000;
    if (maxDigits >= MAX_MODIFY_DIGITS - 1)
        newValue += valueDigits[id++] * 100;
    if (maxDigits >= MAX_MODIFY_DIGITS - 2)
        newValue += valueDigits[id++] * 10;
    if (maxDigits >= MAX_MODIFY_DIGITS - 3)
        newValue += valueDigits[id++];

    return newValue;
}

static void ValueToCharDigits(u8 *charDigits, u32 newValue, u8 maxDigits)
{
    s32 i;
    u8 valueDigits[MAX_MODIFY_DIGITS];
    u8 id = 0;

    if (maxDigits >= MAX_MODIFY_DIGITS)
        valueDigits[id++] = newValue / 1000;
    if (maxDigits >= MAX_MODIFY_DIGITS - 1)
        valueDigits[id++] = (newValue % 1000) / 100;
    if (maxDigits >= MAX_MODIFY_DIGITS - 2)
        valueDigits[id++] = (newValue % 100) / 10;
    if (maxDigits >= MAX_MODIFY_DIGITS - 3)
        valueDigits[id++] = newValue % 10;

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        charDigits[i] = valueDigits[i] + CHAR_0;
}

static u8 GetSideStatusValue(struct BattleDebugMenu *data, bool32 changeStatus, u8 setValue)
{
    struct SideTimer *sideTimer = &gSideTimers[GetBattlerSide(data->battlerId)];

    switch (data->currentSecondaryListItemId)
    {
    case LIST_SIDE_REFLECT:
        if (changeStatus)
        {
            if (gSideTimers[GetBattlerSide(data->battlerId)].reflectTimer)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_REFLECT;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_REFLECT;
            gSideTimers[GetBattlerSide(data->battlerId)].reflectBattlerId = data->battlerId;
        }
        if (setValue)
            gSideTimers[GetBattlerSide(data->battlerId)].reflectTimer = setValue;

        return gSideTimers[GetBattlerSide(data->battlerId)].reflectTimer;
    case LIST_SIDE_LIGHTSCREEN:
        if (changeStatus)
        {
            if (gSideTimers[GetBattlerSide(data->battlerId)].lightscreenTimer)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_LIGHTSCREEN;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_LIGHTSCREEN;
            gSideTimers[GetBattlerSide(data->battlerId)].lightscreenBattlerId = data->battlerId;
        }
        if (setValue)
            gSideTimers[GetBattlerSide(data->battlerId)].lightscreenTimer = setValue;

        return gSideTimers[GetBattlerSide(data->battlerId)].lightscreenTimer;
    case LIST_SIDE_SPIKES:
        if (changeStatus)
        {
            if (gSideTimers[GetBattlerSide(data->battlerId)].spikesAmount)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SPIKES;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_SPIKES;
        }
        if (setValue)
            gSideTimers[GetBattlerSide(data->battlerId)].spikesAmount = setValue;

        return gSideTimers[GetBattlerSide(data->battlerId)].spikesAmount;
    case LIST_SIDE_SAFEGUARD:
        if (changeStatus)
        {
            if (gSideTimers[GetBattlerSide(data->battlerId)].safeguardTimer)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SAFEGUARD;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_SAFEGUARD;
            gSideTimers[GetBattlerSide(data->battlerId)].safeguardBattlerId = data->battlerId;
        }
        if (setValue)
            gSideTimers[GetBattlerSide(data->battlerId)].safeguardTimer = setValue;

        return gSideTimers[GetBattlerSide(data->battlerId)].safeguardTimer;
    case LIST_SIDE_MIST:
        if (changeStatus)
        {
            if (gSideTimers[GetBattlerSide(data->battlerId)].mistTimer)
                *(u32 *)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_MIST;
            else
                *(u32 *)(data->modifyArrows.modifiedValPtr) &= ~SIDE_STATUS_MIST;
            gSideTimers[GetBattlerSide(data->battlerId)].mistBattlerId = data->battlerId;
        }
        if (setValue)
            gSideTimers[GetBattlerSide(data->battlerId)].mistTimer = setValue;

        return gSideTimers[GetBattlerSide(data->battlerId)].mistTimer;
    default:
        return 0;
    }//thought it was all wrong but actually setting correctly for side status
}   //nvm it is setting wrong, it works if i use the move, but assinging from here doesn't work defaults to zero

static void SetUpModifyArrows(struct BattleDebugMenu *data)
{
    LoadCompressedSpritePalette(&sSpritePalette_Arrow);
    LoadCompressedSpriteSheet(&sSpriteSheet_Arrows);
    data->modifyArrows.arrowSpriteId[0] = CreateSprite(&sSpriteTemplate_Arrow, 207, 12, 0);
    data->modifyArrows.arrowSpriteId[1] = CreateSprite(&sSpriteTemplate_Arrow, 207, 36, 0);
    StartSpriteAnim(&gSprites[data->modifyArrows.arrowSpriteId[0]], ARROW_DOWN);
    StartSpriteAnim(&gSprites[data->modifyArrows.arrowSpriteId[1]], ARROW_UP);

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_ABILITY:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ABILITIES_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].ability;
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].ability;
        break;
    case LIST_ITEM_MOVES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = MOVES_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        if (data->currentSecondaryListItemId == 4)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].moves[0];
            data->modifyArrows.currValue = gBattleMons[data->battlerId].moves[0];
            data->modifyArrows.typeOfVal = VAR_U16_4_ENTRIES;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId];
            data->modifyArrows.currValue = gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId];
            data->modifyArrows.typeOfVal = VAL_U16;
        }
        break;
    case LIST_ITEM_PP:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = CalculatePPWithBonus(gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId], gBattleMons[data->battlerId].ppBonuses, data->currentSecondaryListItemId);
        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].pp[data->currentSecondaryListItemId];
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].pp[data->currentSecondaryListItemId];
        break;
    case LIST_ITEM_HELD_ITEM:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ITEMS_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].item;
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].item;
        break;
    case LIST_ITEM_SECONDARY_ITEM:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ITEMS_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)];
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)];
        break;
    case LIST_ITEM_TYPES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = NUMBER_OF_MON_TYPES - 1;
        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = (u8 *)((&gBattleMons[data->battlerId].type1) + data->currentSecondaryListItemId);
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = *(u8 *)((&gBattleMons[data->battlerId].type1) + data->currentSecondaryListItemId);
        break;
    case LIST_ITEM_STATS:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = 9999;
        data->modifyArrows.maxDigits = 4;
        if (data->currentSecondaryListItemId == 0)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].hp;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].hp;
            data->modifyArrows.minValue = 1;
            data->modifyArrows.maxValue = gBattleMons[data->battlerId].maxHP;
        }
        else if (data->currentSecondaryListItemId == 1)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].maxHP;
            data->modifyArrows.minValue = gBattleMons[data->battlerId].hp;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].maxHP;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = (u16 *)((&gBattleMons[data->battlerId].attack) + (data->currentSecondaryListItemId - 2));
            data->modifyArrows.currValue = *(u16 *)((&gBattleMons[data->battlerId].attack) + (data->currentSecondaryListItemId - 2));
        }
        data->modifyArrows.typeOfVal = VAL_U16;
        break;
    case LIST_ITEM_STAT_STAGES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = 12;
        data->modifyArrows.maxDigits = 2;
        if (data->currentSecondaryListItemId == NUM_BATTLE_STATS - 1) // Change all stats
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].statStages[STAT_ATK];
            data->modifyArrows.currValue = gBattleMons[data->battlerId].statStages[STAT_ATK];
            data->modifyArrows.typeOfVal = VAL_ALL_STAT_STAGES;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].statStages[data->currentSecondaryListItemId + STAT_ATK];
            data->modifyArrows.typeOfVal = VAL_U8;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].statStages[data->currentSecondaryListItemId + STAT_ATK];
        }
        break;
    case LIST_ITEM_VARIOUS:
        if (data->currentSecondaryListItemId == VARIOUS_SHOW_HP)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 1;
            data->modifyArrows.maxDigits = 1;
            data->modifyArrows.modifiedValPtr = &gBattleSpritesDataPtr->battlerData[data->battlerId];
            data->modifyArrows.typeOfVal = VAR_SHOW_HP;
            data->modifyArrows.currValue = gBattleSpritesDataPtr->battlerData[data->battlerId].hpNumbersNoBars;
        }
        else if (data->currentSecondaryListItemId == VARIOUS_SUBSTITUTE_HP)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 255;
            data->modifyArrows.maxDigits = 3;
            data->modifyArrows.modifiedValPtr = &gDisableStructs[data->battlerId].substituteHP;
            data->modifyArrows.typeOfVal = VAR_SUBSTITUTE;
            data->modifyArrows.currValue = gDisableStructs[data->battlerId].substituteHP;
        }
        else if (data->currentSecondaryListItemId == VARIOUS_IN_LOVE)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 1;
            data->modifyArrows.maxDigits = 1;
            data->modifyArrows.modifiedValPtr = NULL;
            data->modifyArrows.typeOfVal = VAR_IN_LOVE;
            data->modifyArrows.currValue = (gBattleMons[data->battlerId].status2 & STATUS2_INFATUATION) != 0;
        }
        else if (data->currentSecondaryListItemId == VARIOUS_SLEEP_TIMER)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 5;
            data->modifyArrows.maxDigits = 1;
            data->modifyArrows.modifiedValPtr = NULL;
            data->modifyArrows.typeOfVal = VAR_SLEEP_TIMER;
            data->modifyArrows.currValue = gBattleStruct->SleepTimer[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)];
        }
        else if (data->currentSecondaryListItemId == VARIOUS_FREEZE_TIMER)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 3;
            data->modifyArrows.maxDigits = 1;
            data->modifyArrows.modifiedValPtr = NULL;
            data->modifyArrows.typeOfVal = VAR_FREEZE_TIMER;
            data->modifyArrows.currValue = gDisableStructs[data->battlerId].FrozenTurns;
        }
        else if (data->currentSecondaryListItemId == VARIOUS_TOXIC_COUNTER)
        {
            data->modifyArrows.minValue = 0;
            data->modifyArrows.maxValue = 15;
            data->modifyArrows.maxDigits = 2;  
            data->modifyArrows.modifiedValPtr = &gBattleStruct->ToxicTurnCounter[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)];
            data->modifyArrows.typeOfVal = VAR_TOXIC_COUNTER;
            data->modifyArrows.currValue = gBattleStruct->ToxicTurnCounter[gBattlerPartyIndexes[data->battlerId]][GetBattlerSide(data->battlerId)];
        }
        break;//will need else if conditionals for specific effects handled differently below status that don't follow bit field logic/for adding timers
    case LIST_ITEM_STATUS1:
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].status1;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleMons[data->battlerId].status1, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS2:
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].status2;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleMons[data->battlerId].status2, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS3:
        data->modifyArrows.modifiedValPtr = &gStatuses3[data->battlerId];
        data->modifyArrows.currValue = GetBitfieldValue(gStatuses3[data->battlerId], data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_AI:
        data->modifyArrows.modifiedValPtr = &gBattleResources->ai->aiFlags;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleResources->ai->aiFlags, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    CASE_ITEM_STATUS:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = (1 << data->bitfield[data->currentSecondaryListItemId].bitsCount) - 1;
        data->modifyArrows.maxDigits = sBitsToMaxDigit[data->bitfield[data->currentSecondaryListItemId].bitsCount];
        break;
    case LIST_ITEM_SIDE_STATUS:
        data->modifyArrows.minValue = 0;

        if (data->currentSecondaryListItemId == LIST_SIDE_SPIKES)
            data->modifyArrows.maxValue = 3;
        else
            data->modifyArrows.maxValue = 8; //changed to 8, believe should be max value w extenders

        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = &gSideStatuses[GetBattlerSide(data->battlerId)];
        data->modifyArrows.typeOfVal = VAR_SIDE_STATUS;
        data->modifyArrows.currValue = GetSideStatusValue(data, FALSE, FALSE);
        break;
    }

    data->modifyArrows.currentDigit = 0;
    ValueToCharDigits(data->modifyArrows.charDigits, data->modifyArrows.currValue, data->modifyArrows.maxDigits);
}

static bool32 TryMoveDigit(struct BattleDebugModifyArrows *modArrows, bool32 moveUp)
{
    s32 i;
    u8 charDigits[MAX_MODIFY_DIGITS];
    u32 newValue;

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        charDigits[i] = modArrows->charDigits[i];

    if (moveUp)
    {
        if (charDigits[modArrows->currentDigit] == CHAR_9)
        {
            charDigits[modArrows->currentDigit] = CHAR_0;
            for (i = modArrows->currentDigit - 1; i >= 0; i--)
            {
                if (charDigits[i] == CHAR_9)
                {
                    charDigits[i] = CHAR_0;
                }
                else
                {
                    charDigits[i]++;
                    break;
                }
            }
        }
        else
            charDigits[modArrows->currentDigit]++;
    }
    else
    {
        if (charDigits[modArrows->currentDigit] == CHAR_0)
        {
            charDigits[modArrows->currentDigit] = CHAR_9;
            for (i = modArrows->currentDigit - 1; i >= 0; i--)
            {
                if (charDigits[i] == CHAR_0)
                {
                    charDigits[i] = CHAR_9;
                }
                else
                {
                    charDigits[i]--;
                    break;
                }
            }
        }
        else
            charDigits[modArrows->currentDigit]--;
    }

    newValue = CharDigitsToValue(charDigits, modArrows->maxDigits);
    if (newValue > modArrows->maxValue || newValue < modArrows->minValue)
    {
        return FALSE;
    }
    else
    {
        modArrows->currValue = newValue;
        for (i = 0; i < MAX_MODIFY_DIGITS; i++)
             modArrows->charDigits[i] = charDigits[i];
        return TRUE;
    }
}

static void UpdateMonData(struct BattleDebugMenu *data)
{
    s32 i, j;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (data->battlerWasChanged[i])
        {
            struct Pokemon *mon;
            struct BattlePokemon *battleMon = &gBattleMons[i];

            if (GetBattlerSide(i) == B_SIDE_PLAYER)
                mon = &gPlayerParty[gBattlerPartyIndexes[i]];
            else
                mon = &gEnemyParty[gBattlerPartyIndexes[i]];

            SetMonData(mon, MON_DATA_HELD_ITEM, &battleMon->item);
            SetMonData(mon, MON_DATA_STATUS, &battleMon->status1);
            SetMonData(mon, MON_DATA_HP, &battleMon->hp);
            SetMonData(mon, MON_DATA_MAX_HP, &battleMon->maxHP);
            for (j = 0; j < 4; j++)
            {
                SetMonData(mon, MON_DATA_MOVE1 + j, &battleMon->moves[j]);
                SetMonData(mon, MON_DATA_PP1 + j, &battleMon->pp[j]);
            }
        }
    }
}

static const u8 sText_HoldEffectNone[] = _("????????");
static const u8 sText_HoldEffectRestoreHp[] = _("Restore Hp");
static const u8 sText_HoldEffectCurePar[] = _("Cure Par");
static const u8 sText_HoldEffectCureSlp[] = _("Cure Slp");
static const u8 sText_HoldEffectCurePsn[] = _("Cure Psn");
static const u8 sText_HoldEffectCureBrn[] = _("Cure Brn");
static const u8 sText_HoldEffectCureFrz[] = _("Cure Frz");
static const u8 sText_HoldEffectRestorePp[] = _("Restore Pp");
static const u8 sText_HoldEffectCureConfusion[] = _("Cure Confusion");
static const u8 sText_HoldEffectCureStatus[] = _("Cure Status");
static const u8 sText_HoldEffectConfuseSpicy[] = _("Confuse Spicy");
static const u8 sText_HoldEffectConfuseDry[] = _("Confuse Dry");
static const u8 sText_HoldEffectConfuseSweet[] = _("Confuse Sweet");
static const u8 sText_HoldEffectConfuseBitter[] = _("Confuse Bitter");
static const u8 sText_HoldEffectConfuseSour[] = _("Confuse Sour");
static const u8 sText_HoldEffectAttackUp[] = _("Attack Up");
static const u8 sText_HoldEffectDefenseUp[] = _("Defense Up");
static const u8 sText_HoldEffectSpeedUp[] = _("Speed Up");
static const u8 sText_HoldEffectSpAttackUp[] = _("Sp Attack Up");
static const u8 sText_HoldEffectSpDefenseUp[] = _("Sp Defense Up");
static const u8 sText_HoldEffectCriticalUp[] = _("Critical Up");
static const u8 sText_HoldEffectRandomStatUp[] = _("Random Stat Up");
static const u8 sText_HoldEffectEvasionUp[] = _("Evasion Up");
static const u8 sText_HoldEffectRestoreStats[] = _("Restore Stats");
static const u8 sText_HoldEffectMachoBrace[] = _("Macho Brace");
static const u8 sText_HoldEffectExpShare[] = _("Exp Share");
static const u8 sText_HoldEffectQuickClaw[] = _("Quick Claw");
static const u8 sText_HoldEffectFriendshipUp[] = _("Friendship Up");
static const u8 sText_HoldEffectMentalHerb[] = _("Mental Herb");
static const u8 sText_HoldEffectChoiceBand[] = _("Choice Band");
static const u8 sText_HoldEffectFlinch[] = _("Flinch");
static const u8 sText_HoldEffectBugPower[] = _("Bug Power");
static const u8 sText_HoldEffectDoublePrize[] = _("Double Prize");
static const u8 sText_HoldEffectRepel[] = _("Repel");
static const u8 sText_HoldEffectSoulDew[] = _("Soul Dew");
static const u8 sText_HoldEffectDeepSeaTooth[] = _("Deep Sea Tooth");
static const u8 sText_HoldEffectDeepSeaScale[] = _("Deep Sea Scale");
static const u8 sText_HoldEffectCanAlwaysRun[] = _("Can Always Run");
static const u8 sText_HoldEffectPreventEvolve[] = _("Prevent Evolve");
static const u8 sText_HoldEffectFocusBand[] = _("Focus Band");
static const u8 sText_HoldEffectLuckyEgg[] = _("Lucky Egg");
static const u8 sText_HoldEffectScopeLens[] = _("Scope Lens");
static const u8 sText_HoldEffectSteelPower[] = _("Steel Power");
static const u8 sText_HoldEffectLeftovers[] = _("Leftovers");
static const u8 sText_HoldEffectDragonScale[] = _("Dragon Scale");
static const u8 sText_HoldEffectLightBall[] = _("Light Ball");
static const u8 sText_HoldEffectGroundPower[] = _("Ground Power");
static const u8 sText_HoldEffectRockPower[] = _("Rock Power");
static const u8 sText_HoldEffectGrassPower[] = _("Grass Power");
static const u8 sText_HoldEffectDarkPower[] = _("Dark Power");
static const u8 sText_HoldEffectFightingPower[] = _("Fighting Power");
static const u8 sText_HoldEffectElectricPower[] = _("Electric Power");
static const u8 sText_HoldEffectWaterPower[] = _("Water Power");
static const u8 sText_HoldEffectFlyingPower[] = _("Flying Power");
static const u8 sText_HoldEffectPoisonPower[] = _("Poison Power");
static const u8 sText_HoldEffectIcePower[] = _("Ice Power");
static const u8 sText_HoldEffectGhostPower[] = _("Ghost Power");
static const u8 sText_HoldEffectPsychicPower[] = _("Psychic Power");
static const u8 sText_HoldEffectFirePower[] = _("Fire Power");
static const u8 sText_HoldEffectDragonPower[] = _("Dragon Power");
static const u8 sText_HoldEffectNormalPower[] = _("Normal Power");
static const u8 sText_HoldEffectUpgrade[] = _("Upgrade");
static const u8 sText_HoldEffectShellBell[] = _("Shell Bell");
static const u8 sText_HoldEffectLuckyPunch[] = _("Lucky Punch");
static const u8 sText_HoldEffectMetalPowder[] = _("Metal Powder");
static const u8 sText_HoldEffectThickClub[] = _("Thick Club");
static const u8 sText_HoldEffectLeek[] = _("Leek");

static const u8 *const sHoldEffectNames[] =
{
    [HOLD_EFFECT_NONE] = sText_HoldEffectNone,
    [HOLD_EFFECT_RESTORE_HP] = sText_HoldEffectRestoreHp,
    [HOLD_EFFECT_CURE_PAR] = sText_HoldEffectCurePar,
    [HOLD_EFFECT_CURE_SLP] = sText_HoldEffectCureSlp,
    [HOLD_EFFECT_CURE_PSN] = sText_HoldEffectCurePsn,
    [HOLD_EFFECT_CURE_BRN] = sText_HoldEffectCureBrn,
    [HOLD_EFFECT_CURE_FRZ] = sText_HoldEffectCureFrz,
    [HOLD_EFFECT_RESTORE_PP] = sText_HoldEffectRestorePp,
    [HOLD_EFFECT_CURE_CONFUSION] = sText_HoldEffectCureConfusion,
    [HOLD_EFFECT_CURE_STATUS] = sText_HoldEffectCureStatus,
    [HOLD_EFFECT_CONFUSE_SPICY] = sText_HoldEffectConfuseSpicy,
    [HOLD_EFFECT_CONFUSE_DRY] = sText_HoldEffectConfuseDry,
    [HOLD_EFFECT_CONFUSE_SWEET] = sText_HoldEffectConfuseSweet,
    [HOLD_EFFECT_CONFUSE_BITTER] = sText_HoldEffectConfuseBitter,
    [HOLD_EFFECT_CONFUSE_SOUR] = sText_HoldEffectConfuseSour,
    [HOLD_EFFECT_ATTACK_UP] = sText_HoldEffectAttackUp,
    [HOLD_EFFECT_DEFENSE_UP] = sText_HoldEffectDefenseUp,
    [HOLD_EFFECT_SPEED_UP] = sText_HoldEffectSpeedUp,
    [HOLD_EFFECT_SP_ATTACK_UP] = sText_HoldEffectSpAttackUp,
    [HOLD_EFFECT_SP_DEFENSE_UP] = sText_HoldEffectSpDefenseUp,
    [HOLD_EFFECT_CRITICAL_UP] = sText_HoldEffectCriticalUp,
    [HOLD_EFFECT_RANDOM_STAT_UP] = sText_HoldEffectRandomStatUp,
    [HOLD_EFFECT_EVASION_UP] = sText_HoldEffectEvasionUp,
    [HOLD_EFFECT_RESTORE_STATS] = sText_HoldEffectRestoreStats,
    [HOLD_EFFECT_MACHO_BRACE] = sText_HoldEffectMachoBrace,
    [HOLD_EFFECT_EXP_SHARE] = sText_HoldEffectExpShare,
    [HOLD_EFFECT_QUICK_CLAW] = sText_HoldEffectQuickClaw,
    [HOLD_EFFECT_HAPPINESS_UP] = sText_HoldEffectFriendshipUp,
    [HOLD_EFFECT_CURE_ATTRACT] = sText_HoldEffectMentalHerb,
    [HOLD_EFFECT_CHOICE_BAND] = sText_HoldEffectChoiceBand,
    [HOLD_EFFECT_FLINCH] = sText_HoldEffectFlinch,
    [HOLD_EFFECT_BUG_POWER] = sText_HoldEffectBugPower,
    [HOLD_EFFECT_DOUBLE_PRIZE] = sText_HoldEffectDoublePrize,
    [HOLD_EFFECT_CLEANSE_TAG] = sText_HoldEffectRepel,
    [HOLD_EFFECT_SOUL_DEW] = sText_HoldEffectSoulDew,
    [HOLD_EFFECT_DEEP_SEA_TOOTH] = sText_HoldEffectDeepSeaTooth,
    [HOLD_EFFECT_DEEP_SEA_SCALE] = sText_HoldEffectDeepSeaScale,
    [HOLD_EFFECT_CAN_ALWAYS_RUN] = sText_HoldEffectCanAlwaysRun,
    [HOLD_EFFECT_PREVENT_EVOLVE] = sText_HoldEffectPreventEvolve,
    [HOLD_EFFECT_FOCUS_BAND] = sText_HoldEffectFocusBand,
    [HOLD_EFFECT_LUCKY_EGG] = sText_HoldEffectLuckyEgg,
    [HOLD_EFFECT_SCOPE_LENS] = sText_HoldEffectScopeLens,
    [HOLD_EFFECT_STEEL_POWER] = sText_HoldEffectSteelPower,
    [HOLD_EFFECT_LEFTOVERS] = sText_HoldEffectLeftovers,
    [HOLD_EFFECT_DRAGON_SCALE] = sText_HoldEffectDragonScale,
    [HOLD_EFFECT_LIGHT_BALL] = sText_HoldEffectLightBall,
    [HOLD_EFFECT_GROUND_POWER] = sText_HoldEffectGroundPower,
    [HOLD_EFFECT_ROCK_POWER] = sText_HoldEffectRockPower,
    [HOLD_EFFECT_GRASS_POWER] = sText_HoldEffectGrassPower,
    [HOLD_EFFECT_DARK_POWER] = sText_HoldEffectDarkPower,
    [HOLD_EFFECT_FIGHTING_POWER] = sText_HoldEffectFightingPower,
    [HOLD_EFFECT_ELECTRIC_POWER] = sText_HoldEffectElectricPower,
    [HOLD_EFFECT_WATER_POWER] = sText_HoldEffectWaterPower,
    [HOLD_EFFECT_FLYING_POWER] = sText_HoldEffectFlyingPower,
    [HOLD_EFFECT_POISON_POWER] = sText_HoldEffectPoisonPower,
    [HOLD_EFFECT_ICE_POWER] = sText_HoldEffectIcePower,
    [HOLD_EFFECT_GHOST_POWER] = sText_HoldEffectGhostPower,
    [HOLD_EFFECT_PSYCHIC_POWER] = sText_HoldEffectPsychicPower,
    [HOLD_EFFECT_FIRE_POWER] = sText_HoldEffectFirePower,
    [HOLD_EFFECT_DRAGON_POWER] = sText_HoldEffectDragonPower,
    [HOLD_EFFECT_NORMAL_POWER] = sText_HoldEffectNormalPower,
    [HOLD_EFFECT_UP_GRADE] = sText_HoldEffectUpgrade,
    [HOLD_EFFECT_SHELL_BELL] = sText_HoldEffectShellBell,
    [HOLD_EFFECT_LUCKY_PUNCH] = sText_HoldEffectLuckyPunch,
    [HOLD_EFFECT_METAL_POWDER] = sText_HoldEffectMetalPowder,
    [HOLD_EFFECT_THICK_CLUB] = sText_HoldEffectThickClub,
    [HOLD_EFFECT_LEEK] = sText_HoldEffectLeek,
};
static const u8 *GetHoldEffectName(u16 holdEffect)
{
    if (holdEffect > ARRAY_COUNT(sHoldEffectNames))
        return sHoldEffectNames[0];
    return sHoldEffectNames[holdEffect];
}

/*static bool32 IsBattlerAlive(u32 battler)
{
    if (gBattleMons[battler].hp == 0)
        return FALSE;
    else if (battler >= gBattlersCount)
        return FALSE;
    else if (gAbsentBattlerFlags & gBitTable[battler])
        return FALSE;
    else
        return TRUE;
}*/

#endif //DEBUG_BATTLE_MENU == TRUE