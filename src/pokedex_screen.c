#include "global.h"
#include "gflib.h"
#include "graphics.h"
#include "m4a.h"
#include "scanline_effect.h"
#include "task.h"
#include "new_menu_helpers.h"
#include "event_data.h"
#include "help_system.h"
#include "menu_indicators.h"
#include "overworld.h"
#include "strings.h"
#include "menu.h"
#include "pokedex_screen.h"
#include "data.h"
#include "pokedex.h"
#include "trainer_pokemon_sprites.h"
#include "battle_anim.h"
#include "pokeball.h"
#include "pokemon_icon.h"
#include "decompress.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "pokedex_area_markers.h"
#include "pokemon_summary_screen.h"
#include "party_menu.h"
#include "region_map.h"
#include "field_specials.h"
#include "rtc.h"
#include "item.h"

#define TAG_AREA_MARKERS 2001

#define DEX_MAX_SHOWN sListMenuTemplate_OrderedListMenu.maxShowed//9  //plan use for amount of mon to initially load, for speed sake, then expand on as scroll


#define SCROLL_UP 1
#define SCROLL_DOWN 0
#define EXIT_DEX_ENTRY 2

enum TextMode {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};

//for setting up Input functions
//need listing for every relevant page of dex
//don't need a new one, looks like can just use
//the DexScreen_ProcessInput that I made already
//sPokedexScreenData->currentPage go through navigation of dex menus, and add to places so it can be read when setup
enum DexContextMenu {
    DEX_MAIN_PAGE,
    DEX_NUMERICAL_LIST,
    DEX_INFO_FROM_LIST,
    DEX_EVO_FROM_LIST,
    DEX_AREA_FROM_LIST,
    DEX_HABITAT_PAGE,
    DEX_INFO_FROM_HABITAT,
    DEX_EVO_FROM_HABITAT,
    DEX_AREA_FROM_HABITAT,
    DEX_REGISTER_PAGE
};

struct EvoScreenData
{
    //bool8 fromEvoPage;
    u8 numAllEvolutions;
    u16 targetSpecies[20]; //think will need increase this, since boosted pre evo setting and have 10 values for target species
    //u8 numSeen;
    //bool8 seen[10]; //not using this at all so can save some space by removing
    u8 menuPos;  //unfortunately removing above didn't save space
    u8 arrowSpriteId;
    #ifdef POKEMON_EXPANSION //megas are in form dex, but I did planto make permanent mega, so may add
    bool8 isMega;
    #endif
};

struct PokedexScreenData
{
    u8 taskId;
    u8 state;
    u8 data[2]; //doesn't go above 1, so only 2 fileds, so using 4 is unnecessary
    u8 areaMarkersTaskId;
    u32 unlockedCategories;
    u32 modeSelectInput;  //no idea what to call this but is used on main dex page, w process input to kinda chose what dex mode to use
    u16 modeSelectItemsAbove;
    u16 modeSelectCursorPos;
    u8 modeSelectWindowId;
    u8 selectionIconWindowId;
    u8 dexCountsWindowId; //used to hold kanto dex/nat dex seen/owned counts, may be able to use window, for stats bar...prob best to make own window to be more exact smh
    u8 modeSelectListMenuId;
    u16 pageSpecies[4];
    u8 categoryMonWindowIds[4];
    u8 categoryMonInfoWindowIds[4];
    u8 category;    //stores species category for mon
    u8 firstPageInCategory;
    u8 lastPageInCategory;
    u8 pageNum;
    u8 numMonsOnPage;
    u8 categoryCursorPosInPage;
    u8 categoryPageSelectionCursorTimer;
    u8 parentOfCategoryMenu;
    u32 characteristicMenuInput;
    u16 kantoOrderMenuItemsAbove;
    u16 kantoOrderMenuCursorPos;
    u16 characteristicOrderMenuItemsAbove;
    u16 characteristicOrderMenuCursorPos;
    u16 nationalOrderMenuItemsAbove;
    u16 nationalOrderMenuCursorPos;
    u8 numericalOrderWindowId;
    u8 orderedListMenuTaskId;
    u8 dexOrderId;
    struct ListMenuItem * listItems; //reverted below for space saving, think otherwise its same affect, didn't affect load time, saves bout 10Kb of rom space
   // struct ListMenuItem listItems[NATIONAL_DEX_COUNT + 1]; //making this lets me skip alloc in load resources, costs good deal of space, but hopefully will svae me elsewher
    u16 orderedDexCount;
    u16 CurrentIndexValue; //added for categorica lists, to store array value that alligns w current index, takes i + 1 for this, so next trigger will be in allignment
    u8 windowIds[0x10]; //16 values, seems to be for labels for main page, exactly matches w num main page labels
    u16 dexSpecies;
    u16 * bgBufsMem;
    u8 scrollArrowsTaskId;
    u8 categoryPageCursorTaskId;
    u16 modeSelectCursorPosBak;
    u8 unlockedSeviiAreas;
    u16 numSeenKanto;
    u16 numOwnedKanto;
    u16 numSeenNational;
    u16 numOwnedNational;
    struct EvoScreenData sEvoScreenData; //HGSS_Ui
    u8 statBarsSpriteId; //HGSS_Ui
    u8 statBarsBgSpriteId; //HGSS_Ui
    u8 numPreEvolutions; //HGSS_Ui
    u8 ballIconSpriteId; //for displaying pokeball on evo page 
    u8 currentPage; //store what page you are on within the dex for navigation/dexscreenprocessinput similar use to what did in options
};

struct PokedexScreenWindowGfx
{
    const u16 * tiles;
    const u16 * pal;
};

struct PokedexCategoryPage
{
    const u16 * species;
    u8 count;
};

//equivalent of sPokedexScreenData in emerald meaning dexscreendata is = PokedexView
EWRAM_DATA static struct PokedexScreenData * sPokedexScreenData = NULL;

//can just use AREA SCREEN SIZE pallete for sillouting I'm so STUPID!!

//HGSS DEX additions
static const u8 sCaughtBall_Gfx[] = INCBIN_U8("graphics/pokedex/caught_ball.4bpp"); //need add this,
//think insteaed use CreateBallIconObj  from summary screen,
//just adjust spacing between method and text to account

//text additions - need add text for my custom evo methods
//also some cases are just not in method  function
//believe for longer methods i.e dark in party/amped nature, will need exclude evo effort
static const u8 sText_EVO_Buttons[] = _("{DPAD_UPDOWN}EVOs  {A_BUTTON}CHECK");
static const u8 sText_EVO_Buttons_Decapped[] = _("{DPAD_UPDOWN}Evos  {A_BUTTON}Check");
static const u8 sText_EVO_Buttons_PE[] = _("{DPAD_UPDOWN}EVOs  {A_BUTTON}CHECK  {START_BUTTON}FORMs");
static const u8 sText_EVO_Buttons_Decapped_PE[] = _("{DPAD_UPDOWN}Evos  {A_BUTTON}Check  {START_BUTTON}Forms");
static const u8 sText_EVO_Name[] = _("{STR_VAR_3}:");
static const u8 sText_EVO_PreEvo[] = _("{STR_VAR_1} evolves from {STR_VAR_2}");
static const u8 sText_EVO_PreEvo_PE_Mega[] = _("{STR_VAR_1} Mega Evolves with {STR_VAR_2}");
static const u8 sText_EVO_FRIENDSHIP[] = _("{LV}{UP_ARROW}, high friendship");
static const u8 sText_EVO_FRIENDSHIP_DAY[] = _("{LV}{UP_ARROW}, high friendship, day");
static const u8 sText_EVO_FRIENDSHIP_NIGHT[] = _("{LV}{UP_ARROW}, high friendship, night");
static const u8 sText_EVO_FRIENDSHIP_MOVE_TYPE[] = _("{LV}{UP_ARROW}, high friendship, {STR_VAR_2} move");
static const u8 sText_EVO_LEVEL[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv");
static const u8 sText_EVO_TRADE[] = _("Trading");
static const u8 sText_EVO_TRADE_ITEM[] = _("Trading, holding {STR_VAR_2}");
static const u8 sText_EVO_ITEM[] = _("{STR_VAR_2} is used");
static const u8 sText_EVO_LEVEL_ATK_GT_DEF[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, Atk > Def, or +{STR_VAR_3} Lv"); //comparison symobols aren't in charmap need add
static const u8 sText_EVO_LEVEL_ATK_EQ_DEF[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, Atk = Def, or +{STR_VAR_3} Lv");
static const u8 sText_EVO_LEVEL_ATK_LT_DEF[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, Atk < Def, or +{STR_VAR_3} Lv");
static const u8 sText_EVO_LEVEL_SILCOON[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, Silcoon persona");
static const u8 sText_EVO_LEVEL_CASCOON[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, Cascoon persona");
static const u8 sText_EVO_LEVEL_NINJASK[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv");
static const u8 sText_EVO_LEVEL_SHEDINJA[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, party<6, 1x POKéBALL");
static const u8 sText_EVO_BEAUTY[] = _("{LV}{UP_ARROW}, high beauty");
static const u8 sText_EVO_LEVEL_FEMALE[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, is female");
static const u8 sText_EVO_LEVEL_MALE[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, is male");
static const u8 sText_EVO_LEVEL_NIGHT[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, night");
static const u8 sText_EVO_LEVEL_DAY[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, day");
static const u8 sText_EVO_LEVEL_DUSK[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, dusk (5-6PM)");
static const u8 sText_EVO_ITEM_HOLD_DAY[] = _("{LV}{UP_ARROW}, holds {STR_VAR_2}, day");
static const u8 sText_EVO_ITEM_HOLD_NIGHT[] = _("{LV}{UP_ARROW}, holds {STR_VAR_2}, night");
static const u8 sText_EVO_MOVE[] = _("{LV}{UP_ARROW}, knows {STR_VAR_2}");
static const u8 sText_EVO_MOVE_TYPE[] = _("{LV}{UP_ARROW}, knows move of {STR_VAR_2} type");
static const u8 sText_EVO_MAPSEC[] = _("{LV}{UP_ARROW} in {STR_VAR_2}");
static const u8 sText_EVO_ITEM_MALE[] = _("{STR_VAR_2} used on male");
static const u8 sText_EVO_ITEM_FEMALE[] = _("{STR_VAR_2} used on female");
static const u8 sText_EVO_LEVEL_RAIN[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv while raining");
static const u8 sText_EVO_SPECIFIC_MON_IN_PARTY[] = _("{LV}{UP_ARROW} with {STR_VAR_2} in party");
static const u8 sText_EVO_LEVEL_DARK_TYPE_MON_IN_PARTY[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv with dark type in party"); //too long
static const u8 sText_EVO_TRADE_SPECIFIC_MON[] = _("Traded for {STR_VAR_2}");
static const u8 sText_EVO_SPECIFIC_MAP[] = _("{LV}{UP_ARROW} on {STR_VAR_2}");
static const u8 sText_EVO_LEVEL_NATURE_AMPED[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, Amped natures"); //too long
static const u8 sText_EVO_LEVEL_NATURE_LOW_KEY[] = _("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, Low Key natures");
static const u8 sText_EVO_CRITICAL_HITS[] = _("Land {STR_VAR_2} critical hits in\nsingle battle");
static const u8 sText_EVO_SCRIPT_TRIGGER_DMG[] = _("Takes at least {STR_VAR_2} HP in damage");
static const u8 sText_EVO_DARK_SCROLL[] = _("ScrollOfDarkness is used");
static const u8 sText_EVO_WATER_SCROLL[] = _("ScrollOfWaters is used");
static const u8 sText_EVO_ITEM_NIGHT[] = _("{STR_VAR_2} is used, night");
static const u8 sText_EVO_ITEM_DAY[] = _("{STR_VAR_2} is used, day");
static const u8 sText_EVO_ITEM_HOLD[] = _("{LV}{UP_ARROW}, holds {STR_VAR_2}");
static const u8 sText_EVO_LEVEL_MOVE_TWENTY_TIMES[] = _("{LV}{UP_ARROW} after 20x {STR_VAR_2}");
static const u8 sText_EVO_LEVEL_RECOIL_DAMAGE_MALE[] = _("{LV}{UP_ARROW} with {STR_VAR_2} recoil, male");
static const u8 sText_EVO_LEVEL_RECOIL_DAMAGE_FEMALE[] = _("{LV}{UP_ARROW} with {STR_VAR_2} recoil, female");
static const u8 sText_EVO_UNKNOWN[] = _("Method unknown");
static const u8 sText_EVO_NONE[] = _("{STR_VAR_1} has no evolution.");
static const u8 sText_EVO_MILCERY[] =_(""); //similar cascoon, friendship + flavor personality
static const u8 sText_EVO_ITEM_FORM[] =_("{STR_VAR_2} is used w. {STR_VAR_3}"); //buffer flag param - make function take evo param 2 and assign buffer and string
static const u8 sText_EVO_LEVEL_FORM[] =_("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, w. ");//buffer flag param
static const u8 sText_EVO_LEVEL_FORM_NIGHT[] =_("{LV}{UP_ARROW}to {STR_VAR_2}, or +{STR_VAR_3} Lv, night, w. ");//buffer flag param
static const u8 sText_EVO_MOVE_TYPE_ATK_GT_DEF[] =_("{LV}{UP_ARROW}, w. {STR_VAR_2} type move, Atk > Def"); //string var 4 doesn't exist? find some extra buffer to use for flags
static const u8 sText_EVO_MOVE_TYPE_ATK_LT_DEF[] =_("{LV}{UP_ARROW}, w. {STR_VAR_2} type move, Atk < Def");//{STR_VAR_1} can hopefully use without issue
static const u8 sText_EVO_HIGH_RICHES[] =_("{LV}{UP_ARROW}, w. ¥{STR_VAR_2}");

static void ResetEvoScreenDataStruct(void);
static void GetSeenFlagTargetSpecies(void); //not sure if will need this
static void Task_LoadEvolutionScreen(u8 taskId);
static void Task_HandleEvolutionScreenInput(u8 taskId);
static void HandleTargetSpeciesPrintText(u16 targetSpecies, u8 base_x, u8 base_y, u8 base_y_offset, u8 base_i);
static void HandleTargetSpeciesPrintIcon(u8 taskId, u16 targetSpecies, u8 base_i, u8 times);
static void CreateCaughtBallEvolutionScreen(u16 targetSpecies, u8 x, u8 y, u16 unused); //again use other graphic if can
static void HandlePreEvolutionSpeciesPrint(u8 taskId, u16 preSpecies, u16 species, u8 base_x, u8 base_y, u8 base_y_offset, u8 base_i);
static u8 PrintPreEvolutions(u8 taskId, u16 species);
static u8 PrintEvolutionTargetSpeciesAndMethod(u8 taskId, u16 species, u8 depth, u8 base_i_offset, u32 alreadyPrintedIcons[], u32 *base_icon_i_offSet);
static void Task_SwitchScreensFromEvolutionScreen(void);
static void Task_ExitEvolutionScreen(u8 taskId);
static void PrintInfoScreenTextSmall(const u8* str, u8 left, u8 top);
static void FreeInfoScreenWindowAndBgBuffers(void); //not used

static void ShowOrHideDexBallIconObj(u8 invisible); //takenfrom  summ screen for thsi
static void DestroyDexBallIconObj(void); //taken from summ screen for this
static void UpdateStatBars(u16 species); //nemw thing added attempt update stat bar as scroll
static u8 AssignPreEvoData(u16 *speciesArrayOne, u16 *speciesArrayTwo, u16 species, u8 taskId, u8 base_x, u8 base_y, u8 base_y_offset, bool8 hasPrePreEvo); //added to store multiple pre evos
//end HGSS dex

static void Task_PokedexScreen(u8 taskId);
static void DexScreen_InitGfxForTopMenu(void);
static void Task_DexScreen_NumericalOrder(u8 taskId);
static void DexScreen_InitGfxForNumericalOrderList(void);
static void Task_DexScreen_CharacteristicOrder(u8 taskId);
static void DexScreen_CreateCharacteristicListMenu(void);
static u16 DexScreen_CountMonsInOrderedList(u8 orderIdx);
static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order);
static u8 DexScreen_CreateDexOrderScrollArrows(void);
static void DexScreen_DestroyDexOrderListMenu(u8 order);
static void Task_DexScreen_CategorySubmenu(u8 taskId);
static u8 DexScreen_CreateCategoryMenuScrollArrows(void);
static int DexScreen_InputHandler_GetShoulderInput(void);
static void Task_DexScreen_ShowMonPage(u8 taskId);
static bool32 DexScreen_TryScrollMonVertical(u8 direction);
static bool32 DexScreen_TryDisplayForms(u8 direction); //new addition for displauing forms w left/right press
static void DexScreen_RemoveWindow(u8 *windowId_p); //pret made static, which makes sense these aren't used elsewhere
static void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y);
static u16 DexScreen_GetDexCount(u8 caseId, bool8 whichDex);
static void DexScreen_PrintControlInfo(const u8 *src);
static void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void);
static bool8 DexScreen_CreateCategoryListGfx(bool8 justRegistered);
static void DexScreen_CreateCategoryPageSelectionCursor(u8 cursorPos);
static void DexScreen_UpdateCategoryPageCursorObject(u8 taskId, u8 cursorPos, u8 numMonsInPage);
static bool8 DexScreen_FlipCategoryPageInDirection(u8 direction);
void DexScreen_DexPageZoomEffectFrame(u8 bg, u8 scale);
static u8 DexScreen_DrawMonDexPage(bool8 justRegistered);
static u8 DexScreen_DrawMonEvoPage(bool8 justRegistered);
static void TryDestroyStatBars(void);   //stats
static void TryDestroyStatBarsBg(void);
static void CreateStatBars(u32 species);
static void CreateStatBarsBg(void);
static void SpriteCB_StatBars(struct Sprite *sprite);
static void SpriteCB_StatBarsBg(struct Sprite *sprite);
u8 RemoveDexPageWindows(void);
u8 DexScreen_DrawMonAreaPage(void);
static bool8 DexScreen_CanShowMonInCategory(u8 category, u8 pageNum); //same as is page unlocked just prefer name
static bool8 DexScreen_IsCategoryUnlocked(u8 category);
static u8 DexScreen_GetPageLimitsForCategory(u8 category);
static bool8 DexScreen_LookUpCategoryBySpecies(u16 species);
u8 DexScreen_DestroyAreaScreenResources(void);
void DexScreen_CreateCategoryPageSpeciesList(u8 category, u8 pageNum);
static u8 DexScreen_PageNumberToRenderablePages(u16 page);
void DexScreen_InputHandler_StartToCry(void);
void DexScreen_PrintStringWithAlignment(const u8 *str, s32 mode);
static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void ItemPrintFunc_DexModeSelect(u8 windowId, s32 itemId, u8 y);
static void ItemPrintFunc_OrderedListMenu(u8 windowId, s32 itemId, u8 y);
static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId);
static void Task_DexScreen_RegisterMonToPokedex(u8 taskId);

//new stuff
static s32 DexScreen_ProcessInput(u8 listTaskId); //replace list menu input so can adjust separately for in dex list
static void DexScreen_LoadIndex(u32 count, u8 direction, int selectedIndex, s8 scroll_increment);//load list indexs on scroll
//added scroll increment to attempt help keep placement - works done
static u16 DexScreen_CreateList_ReturnCount(u8 orderIdx, int selectedIndex); //moved new list creation logic here, still to be called from DexScreen_CountMonsInOrderedList
static void Task_DexScreen_DexPageFromSummaryScreen(u8 taskId);
static void Task_DexScreen_DexPageFromPCSummaryScreen(u8 taskId);


//#include "data/pokemon_graphics/footprint_table.h"

//Stat bars by DizzyEgg
#define TAG_STAT_BAR 4097
#define TAG_STAT_BAR_BG 4098

#define MAX_ICONS 9 //rn 9 is used for  alreadyPrintedIcons changing number doesn't affect vaporeon not showing up
static const struct OamData sOamData_StatBar =
{
    .y = 160,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
};
static const struct OamData sOamData_StatBarBg =
{
    .y = 160,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
};
static const struct SpriteTemplate sStatBarSpriteTemplate =
{
    .tileTag = TAG_STAT_BAR,
    .paletteTag = TAG_STAT_BAR,
    .oam = &sOamData_StatBar,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_StatBars,
};
static const struct SpriteTemplate sStatBarBgSpriteTemplate =
{
    .tileTag = TAG_STAT_BAR_BG,
    .paletteTag = TAG_STAT_BAR_BG,
    .oam = &sOamData_StatBarBg,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_StatBarsBg,
};
enum
{
    COLOR_ID_ALPHA,
    COLOR_ID_BAR_WHITE,
    // These are repeated 6 times
    COLOR_ID_FILL,
    COLOR_ID_FILL_SHADOW,
    COLOR_ID_FONT = 14,
    COLOR_ID_FONT_SHADOW = 15,
};
enum
{
    COLOR_BEST, // Light blue
    COLOR_VERY_GOOD, // Green
    COLOR_GOOD, // Light Green
    COLOR_AVERAGE, // Yellow
    COLOR_BAD, // Orange
    COLOR_WORST, // Red
};
static const u8 sStatBarsGfx[] = INCBIN_U8("graphics/pokedex/stat_bars.4bpp");
static const u16 sStatBarPalette[16] = {
    [COLOR_ID_ALPHA] = RGB(0, 0, 10),
    [COLOR_ID_BAR_WHITE] = RGB_WHITE,

    [COLOR_ID_FILL + COLOR_BEST * 2] = RGB(2, 25, 25),
    [COLOR_ID_FILL_SHADOW + COLOR_BEST * 2] = RGB(13, 27, 27),

    [COLOR_ID_FILL + COLOR_VERY_GOOD * 2] = RGB(11, 25, 2),
    [COLOR_ID_FILL_SHADOW + COLOR_VERY_GOOD * 2] = RGB(19, 27, 13),

    [COLOR_ID_FILL + COLOR_GOOD * 2] = RGB(22, 25, 2),
    [COLOR_ID_FILL_SHADOW + COLOR_GOOD * 2] = RGB(26, 27, 13),

    [COLOR_ID_FILL + COLOR_AVERAGE * 2] = RGB(25, 22, 2),
    [COLOR_ID_FILL_SHADOW + COLOR_AVERAGE * 2] = RGB(27, 26, 13),

    [COLOR_ID_FILL + COLOR_BAD * 2] = RGB(25, 17, 2),
    [COLOR_ID_FILL_SHADOW + COLOR_BAD * 2] = RGB(27, 22, 13),

    [COLOR_ID_FILL + COLOR_WORST * 2] = RGB(25, 4, 2),
    [COLOR_ID_FILL_SHADOW + COLOR_WORST * 2] = RGB(27, 15, 13),

    [COLOR_ID_FONT] = RGB_BLACK,
    [COLOR_ID_FONT_SHADOW] = RGB(22, 22, 22),
};
static const struct SpritePalette sStatBarSpritePal[] = //{sStatBarPalette, TAG_STAT_BAR};
{
    {sStatBarPalette, TAG_STAT_BAR},
    {sStatBarPalette, TAG_STAT_BAR_BG},
    {0}
};

//const u8 sCategoryMonInfoBgTiles[] = INCBIN_U8("graphics/pokedex/unk_8440124.bin.lz"); //think was previous category image

/*#ifdef SPECIES_NAME_EXPANSION
const u32 sCategoryMonLargeInfoBgTiles[] = INCBIN_U32("graphics/pokedex/large_mini_page.4bpp.lz");
const u32 sCategoryMonMediumInfoBgTiles[] = INCBIN_U32("graphics/pokedex/medium_mini_page.4bpp.lz");
const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("graphics/pokedex/mini_page.4bpp.lz");
#else
const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("graphics/pokedex/mini_page.4bpp.lz");
#endif // SPECIES_NAME_EXPANSION */

const u8 sCategoryMonInfoBgTiles[] = INCBIN_U8("graphics/pokedex/mini_page.bin.lz");
const u8 sKantoDexTiles[] = INCBIN_U8("graphics/pokedex/unk_8440274.4bpp.lz");
const u8 sNatDexTiles[] = INCBIN_U8("graphics/pokedex/unk_84403AC.4bpp.lz");
const u16 sKantoDexPalette[] = INCBIN_U16("graphics/pokedex/unk_84404C8.gbapal");

const u16 sDexScreen_CategoryCursorPals[] = {
    RGB(24, 22, 17), RGB(26, 24, 20),
    RGB(26, 20, 15), RGB(27, 23, 19),
    RGB(28, 18, 15), RGB(28, 22, 19),
    RGB(30, 16, 13), RGB(29, 21, 18),
    RGB(28, 18, 15), RGB(28, 22, 19),
    RGB(26, 20, 15), RGB(27, 23, 19)
};

const u16 sNationalDexPalette[] = INCBIN_U16("graphics/pokedex/unk_84406E0.gbapal");
const u16 sTopMenuIconTiles_Cave[] = INCBIN_U16("graphics/pokedex/unk_84408E0.bin.lz");
const u16 sTopMenuIconTiles_Urban[] = INCBIN_U16("graphics/pokedex/unk_8440BD8.bin.lz");
const u32 sTopMenuSelectionIconTiles_Cancel[] = INCBIN_U32("graphics/pokedex/unk_8440EF0.bin.lz");
const u16 sTopMenuIconTiles_Forest[] = INCBIN_U16("graphics/pokedex/unk_844112C.bin.lz");
const u16 sTopMenuIconTiles_Grassland[] = INCBIN_U16("graphics/pokedex/unk_84414BC.bin.lz");
const u32 sTopMenuIconTiles_QuestionMark[] = INCBIN_U32("graphics/pokedex/unk_8441808.bin.lz");
const u16 sTopMenuIconTiles_Mountain[] = INCBIN_U16("graphics/pokedex/unk_8441A40.bin.lz");
const u16 sTopMenuIconTiles_Rare[] = INCBIN_U16("graphics/pokedex/unk_8441D54.bin.lz");
const u16 sTopMenuIconTiles_Sea[] = INCBIN_U16("graphics/pokedex/unk_8442004.bin.lz");
const u16 sTopMenuIconTiles_Numerical[] = INCBIN_U16("graphics/pokedex/unk_844223C.bin.lz");
const u16 sTopMenuIconTiles_RoughTerrain[] = INCBIN_U16("graphics/pokedex/unk_84424E4.bin.lz");
const u16 sTopMenuIconTiles_WatersEdge[] = INCBIN_U16("graphics/pokedex/unk_8442838.bin.lz");
const u16 sTopMenuIconTiles_Type[] = INCBIN_U16("graphics/pokedex/unk_8442BC0.bin.lz");
const u16 sTopMenuIconTiles_Lightest[] = INCBIN_U16("graphics/pokedex/unk_8442EF8.bin.lz");
const u16 sTopMenuIconTiles_Smallest[] = INCBIN_U16("graphics/pokedex/unk_844318C.bin.lz");
const u16 sTopMenuIconPals_Cave[] = INCBIN_U16("graphics/pokedex/unk_8443420.gbapal");
const u16 sTopMenuIconPals_Urban[] = INCBIN_U16("graphics/pokedex/unk_8443440.gbapal");
const u16 sTopMenuSelectionIconPals_Cancel[] = INCBIN_U16("graphics/pokedex/unk_8443460.gbapal");
const u16 sTopMenuIconPals_Forest[] = INCBIN_U16("graphics/pokedex/unk_8443480.gbapal");
const u16 sTopMenuIconPals_Grassland[] = INCBIN_U16("graphics/pokedex/unk_84434A0.gbapal");
const u16 sTopMenuIconPals_QuestionMark[] = INCBIN_U16("graphics/pokedex/unk_84434C0.gbapal");
const u16 sTopMenuIconPals_Mountain[] = INCBIN_U16("graphics/pokedex/unk_84434E0.gbapal");
const u16 sTopMenuIconPals_Rare[] = INCBIN_U16("graphics/pokedex/unk_8443500.gbapal");
const u16 sTopMenuIconPals_Sea[] = INCBIN_U16("graphics/pokedex/unk_8443520.gbapal");
const u16 sTopMenuIconPals_Numerical[] = INCBIN_U16("graphics/pokedex/unk_8443540.gbapal");
const u16 sTopMenuIconPals_RoughTerrain[] = INCBIN_U16("graphics/pokedex/unk_8443560.gbapal");
const u16 sTopMenuIconPals_WatersEdge[] = INCBIN_U16("graphics/pokedex/unk_8443580.gbapal");
const u16 sTopMenuIconPals_Type[] = INCBIN_U16("graphics/pokedex/unk_84435A0.gbapal");
const u16 sTopMenuIconPals_Lightest[] = INCBIN_U16("graphics/pokedex/unk_84435C0.gbapal");
const u16 sTopMenuIconPals_Smallest[] = INCBIN_U16("graphics/pokedex/unk_84435E0.gbapal");
const u8 sDexScreen_CaughtIcon[] = INCBIN_U8("graphics/pokedex/unk_8443600.4bpp");
const u32 sTilemap_AreaMap_Kanto[] = INCBIN_U32("graphics/pokedex/unk_8443620.bin.lz");
const u32 sTilemap_AreaMap_OneIsland[] = INCBIN_U32("graphics/pokedex/unk_8443910.bin.lz");
const u32 sTilemap_AreaMap_TwoIsland[] = INCBIN_U32("graphics/pokedex/unk_8443988.bin.lz");
const u32 sTilemap_AreaMap_ThreeIsland[] = INCBIN_U32("graphics/pokedex/unk_84439FC.bin.lz");
const u32 sTilemap_AreaMap_FourIsland[] = INCBIN_U32("graphics/pokedex/unk_8443A78.bin.lz");
const u32 sTilemap_AreaMap_FiveIsland[] = INCBIN_U32("graphics/pokedex/unk_8443AF8.bin.lz");
const u32 sTilemap_AreaMap_SixIsland[] = INCBIN_U32("graphics/pokedex/unk_8443BB0.bin.lz");
const u32 sTilemap_AreaMap_SevenIsland[] = INCBIN_U32("graphics/pokedex/unk_8443C54.bin.lz");
const u16 sBlitTiles_WideEllipse[] = INCBIN_U16("graphics/pokedex/unk_8443D00.4bpp");

#include "data/pokemon/pokedex_orders.h"

static const u8 gExpandedPlaceholder_PokedexDescription[] = _("");

#include "data/pokemon/pokedex_text.h"
#include "data/pokemon/pokedex_entries.h"

static const struct BgTemplate sBgTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 5,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x0000
    },
    {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 4,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0x0000
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x0000
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 7,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0x0000
    },
};

static const struct WindowTemplate sWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x03c4
    },
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 18,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0388
    },
    {
        .bg = 255,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 0,
        .height = 0,
        .paletteNum = 0,
        .baseBlock = 0x0000
    },
};

static const struct PokedexScreenData sDexScreenDataInitialState = {
    .modeSelectItemsAbove = 1,  //this works like n-1 so value 1 always just means 0/top of list
    .modeSelectWindowId = -1,
    .selectionIconWindowId = -1,
    .dexCountsWindowId = -1,
    .pageSpecies = {-1, -1, -1, -1},
    .categoryMonWindowIds = {-1, -1, -1, -1},
    .categoryMonInfoWindowIds = {-1, -1, -1, -1},
    .numericalOrderWindowId = -1,
    .windowIds = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    .scrollArrowsTaskId = -1,
    .categoryPageCursorTaskId = -1,
};


static const struct WindowTemplate sWindowTemplate_ModeSelect = {
    .bg = 1,
    .tilemapLeft = 1,
    .tilemapTop = 2,
    .width = 20,
    .height = 16,
    .paletteNum = 0,
    .baseBlock = 0x0008
};

static const struct WindowTemplate sWindowTemplate_SelectionIcon = {
    .bg = 1,
    .tilemapLeft = 21,
    .tilemapTop = 11,
    .width = 8,
    .height = 6,
    .paletteNum = 1,
    .baseBlock = 0x0148
};

static const struct WindowTemplate sWindowTemplate_DexCounts = {
    .bg = 1,
    .tilemapLeft = 21,
    .tilemapTop = 2,
    .width = 9,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x0178
};

static const struct ListMenuItem sListMenuItems_KantoDexModeSelect[] = {
    {gText_PokemonList,                  LIST_HEADER},
    {gText_NumericalMode,                DEX_MODE(NUMERICAL_KANTO)},
    {gText_PokemonHabitats,              LIST_HEADER},
    {gText_DexCategory_GrasslandPkmn,    DEX_CATEGORY_GRASSLAND},
    {gText_DexCategory_ForestPkmn,       DEX_CATEGORY_FOREST},
    {gText_DexCategory_WatersEdgePkmn,   DEX_CATEGORY_WATERS_EDGE},
    {gText_DexCategory_SeaPkmn,          DEX_CATEGORY_SEA},
    {gText_DexCategory_CavePkmn,         DEX_CATEGORY_CAVE},
    {gText_DexCategory_MountainPkmn,     DEX_CATEGORY_MOUNTAIN},
    {gText_DexCategory_RoughTerrainPkmn, DEX_CATEGORY_ROUGH_TERRAIN},
    {gText_DexCategory_UrbanPkmn,        DEX_CATEGORY_URBAN},
    {gText_DexCategory_RarePkmn,         DEX_CATEGORY_RARE},
    {gText_Search,                       LIST_HEADER},
    {gText_AToZMode,                     DEX_MODE(ATOZ)},
    {gText_TypeMode,                     DEX_MODE(TYPE)},
    {gText_LightestMode,                 DEX_MODE(LIGHTEST)},
    {gText_SmallestMode,                 DEX_MODE(SMALLEST)},
    {gText_PokedexOther,                 LIST_HEADER},
    {gText_ClosePokedex,                 LIST_CANCEL},
};

static const struct ListMenuTemplate sListMenuTemplate_KantoDexModeSelect = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sListMenuItems_KantoDexModeSelect),
    .maxShowed = 9, //same as below but just withuot national dex stuff
    .windowId = 0,
    .header_X = 0,
    .item_X = 12,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ListMenuItem sListMenuItems_NatDexModeSelect[] = {
    {gText_PokemonList,                  LIST_HEADER},
    {gText_NumericalModeKanto,           DEX_MODE(NUMERICAL_KANTO)},
    {gText_NumericalModeNational,        DEX_MODE(NUMERICAL_NATIONAL)},
    {gText_PokemonHabitats,              LIST_HEADER},
    {gText_DexCategory_GrasslandPkmn,    DEX_CATEGORY_GRASSLAND},
    {gText_DexCategory_ForestPkmn,       DEX_CATEGORY_FOREST},
    {gText_DexCategory_WatersEdgePkmn,   DEX_CATEGORY_WATERS_EDGE},
    {gText_DexCategory_SeaPkmn,          DEX_CATEGORY_SEA},
    {gText_DexCategory_CavePkmn,         DEX_CATEGORY_CAVE},
    {gText_DexCategory_MountainPkmn,     DEX_CATEGORY_MOUNTAIN},
    {gText_DexCategory_RoughTerrainPkmn, DEX_CATEGORY_ROUGH_TERRAIN},
    {gText_DexCategory_UrbanPkmn,        DEX_CATEGORY_URBAN},
    {gText_DexCategory_RarePkmn,         DEX_CATEGORY_RARE},
    {gText_Search,                       LIST_HEADER},
    {gText_AToZMode,                     DEX_MODE(ATOZ)},
    {gText_TypeMode,                     DEX_MODE(TYPE)},
    {gText_LightestMode,                 DEX_MODE(LIGHTEST)},
    {gText_SmallestMode,                 DEX_MODE(SMALLEST)},
    {gText_PokedexOther,                 LIST_HEADER},
    {gText_ClosePokedex,                 LIST_CANCEL},
};

static const struct ListMenuTemplate sListMenuTemplate_NatDexModeSelect = {
    .items = sListMenuItems_NatDexModeSelect,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sListMenuItems_NatDexModeSelect),
    .maxShowed = 9, //max seen on page, and amount moved by when moving left and right
    .windowId = 0, //oh wait thats in geneeral not for the mon dex page, it only shows 9 lines in general
    .header_X = 0,
    .item_X = 12,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_KantoDex = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 10,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_NatDex = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 11,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1
};


static const struct PokedexScreenWindowGfx sTopMenuSelectionIconGfxPtrs[] = {
    [DEX_CATEGORY_GRASSLAND] = {
        .tiles = sTopMenuIconTiles_Grassland,
        .pal   = sTopMenuIconPals_Grassland
    },
    [DEX_CATEGORY_FOREST] = {
        .tiles = sTopMenuIconTiles_Forest,
        .pal   = sTopMenuIconPals_Forest
    },
    [DEX_CATEGORY_WATERS_EDGE] = {
        .tiles = sTopMenuIconTiles_WatersEdge,
        .pal   = sTopMenuIconPals_WatersEdge
    },
    [DEX_CATEGORY_SEA] = {
        .tiles = sTopMenuIconTiles_Sea,
        .pal   = sTopMenuIconPals_Sea
    },
    [DEX_CATEGORY_CAVE] = {
        .tiles = sTopMenuIconTiles_Cave,
        .pal   = sTopMenuIconPals_Cave
    },
    [DEX_CATEGORY_MOUNTAIN] = {
        .tiles = sTopMenuIconTiles_Mountain,
        .pal   = sTopMenuIconPals_Mountain
    },
    [DEX_CATEGORY_ROUGH_TERRAIN] = {
        .tiles = sTopMenuIconTiles_RoughTerrain,
        .pal   = sTopMenuIconPals_RoughTerrain
    },
    [DEX_CATEGORY_URBAN] = {
        .tiles = sTopMenuIconTiles_Urban,
        .pal   = sTopMenuIconPals_Urban
    },
    [DEX_CATEGORY_RARE] = {
        .tiles = sTopMenuIconTiles_Rare,
        .pal   = sTopMenuIconPals_Rare
    },
    [DEX_MODE(NUMERICAL_KANTO)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal   = sTopMenuIconPals_Numerical
    },
    [DEX_MODE(ATOZ)] = {
        .tiles = gDexScreen_TopMenuIconTiles_AtoZ,
        .pal   = gDexScreen_TopMenuIconPals_AtoZ
    },
    [DEX_MODE(TYPE)] = {
        .tiles = sTopMenuIconTiles_Type,
        .pal   = sTopMenuIconPals_Type
    },
    [DEX_MODE(LIGHTEST)] = {
        .tiles = sTopMenuIconTiles_Lightest,
        .pal   = sTopMenuIconPals_Lightest
    },
    [DEX_MODE(SMALLEST)] = {
        .tiles = sTopMenuIconTiles_Smallest,
        .pal   = sTopMenuIconPals_Smallest
    },
    [DEX_MODE(NUMERICAL_NATIONAL)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal   = sTopMenuIconPals_Numerical
    },
};

//main window for list effects numerical & search modes
static const struct WindowTemplate sWindowTemplate_OrderedListMenu = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 2,
    .width = 37,
    .height = 16,
    .paletteNum = 0,
    .baseBlock = 0x0008
};

static const struct ListMenuTemplate sListMenuTemplate_OrderedListMenu = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = ItemPrintFunc_OrderedListMenu,
    .totalItems = 0,
    .maxShowed = 9, //ok THIS is actually for the dex list page
    .windowId = 0,
    .header_X = 0,
    .item_X = 65,   //think may be x valuye of index/label? lower number moves index string left, higher moves right, keep in line w changes to species name window
    .cursor_X = 6, //believe to be arrow?
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_MULTIPLE_SCROLL_DPAD,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

enum {
    LIST_MENU_CURSOR_DEXNUM,
    LIST_MENU_MONCAUGHT_ICON,
    LIST_MENU_SPECIES_NAME,
    LIST_MENU_TYPE_ICONS,
    LIST_MENU_0,
};

//used for all the list views in the menus, numerical order & all the search filters. eaech is a separate window  
//believe its the window the values sit in, not the main window as changnig x value doesn't seem to move values,
//just move the space they sit on?
//these are windows can't change without moving actual values?

static const struct ListMenuWindowRect sListMenuRects_OrderedList[] = {
    [LIST_MENU_CURSOR_DEXNUM] = {
        .x = 0,
        .y = 0,
        .width = 6,
        .height = 16,
        .palNum = 0
    },
    [LIST_MENU_MONCAUGHT_ICON] = {
        .x = 6,
        .y = 0,
        .width = 2,
        .height = 16,
        .palNum = 1
    },
    [LIST_MENU_SPECIES_NAME] = {
        .x = 8,
        .y = 0,
        .width = 9,
        .height = 16,
        .palNum = 0
    },
    [LIST_MENU_TYPE_ICONS] = {
        .x = 18,
        .y = 0,
        .width = 10,
        .height = 16,
        .palNum = 2,
    },
    [LIST_MENU_0] = {
        .x = 0xFF,
        .y = 0xFF,
        .width = 0xFF,
        .height = 0xFF,
        .palNum = 0xFF
    }
};

//red scroll arrows for lists
static const struct ScrollArrowsTemplate sDexOrderScrollArrowsTemplate = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1,
};

//reorg base dex navigation to work more like this much cleaner
//vsonic, for when I get to evo page, EE uses A to scroll evos
//I'll chanage to up/down and add dpad to page
//plan may keep navigating to cursor pos page, but decide be able to 
//update stat bar by scrolling over the evos
//make separate task input pressing A would navigate to page,pressing B
//would take to evo page task, and remove arrow?
//then with arrow removed, Press A would navigate the windows
enum  Dex_screens
{
    INFO_SCREEN,
    EVO_SCREEN, //planned additions
    AREA_SCREEN,
    SCREEN_COUNT
};

static const struct WindowTemplate sWindowTemplate_CategoryMonIcon = {
    .bg = 2,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 8,
    .paletteNum = 0,
    .baseBlock = 0x0000
};

static const struct WindowTemplate sWindowTemplate_CategoryMonInfo = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 5,
    .paletteNum = 0,
    .baseBlock = 0x0000
};

const struct WindowTemplate sWindowTemplate_DexEntry_MonPic = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 3,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x01a8
};

//separate window need load for larger species that sit too low otherwise, as 
//I don't currently have an elevation value I can use to put them at different space 
//within window, I can only raise window
const struct WindowTemplate sWindowTemplate_DexEntry_MonPic2_Large = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 2,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x02d8
}; //need make 3rd window for mon still too long, think just 3 elves
//uxie mespirit and azelf
//thinkm can just put a conditional where using first list to continue if species matches any of those 3
//or just put otehr window there..

const struct WindowTemplate sWindowTemplate_DexEntry_MonPic3_Highest = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 1,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x0348
};

const struct WindowTemplate sWindowTemplate_DexEntry_SpeciesStats = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 13,
    .height = 8,
    .paletteNum = 0,
    .baseBlock = 0x0408
};

const struct WindowTemplate sWindowTemplate_DexEntry_FlavorText = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 10,
    .width = 30,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x045A
};

const struct WindowTemplate sWindowTemplate_AreaMap_MonIcon = {
    .bg = 2,
    .tilemapLeft = 1,
    .tilemapTop = 2,
    .width = 4,
    .height = 4,
    .paletteNum = 10,
    .baseBlock = 0x01a8
};

const struct WindowTemplate sWindowTemplate_AreaMap_SpeciesName = {
    .bg = 2,
    .tilemapLeft = 5,
    .tilemapTop = 2,
    .width = 10,
    .height = 5,
    .paletteNum = 0,
    .baseBlock = 0x01b8
};

const struct WindowTemplate sWindowTemplate_AreaMap_Size = {
    .bg = 2,
    .tilemapLeft = 2,
    .tilemapTop = 7,
    .width = 10,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x01d5
};

const struct WindowTemplate sWindowTemplate_AreaMap_Area = {
    .bg = 2,
    .tilemapLeft = 18,
    .tilemapTop = 2,
    .width = 10,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x01e9
};

const struct WindowTemplate sWindowTemplate_AreaMap_MonTypes = {
    .bg = 2,
    .tilemapLeft = 5,
    .tilemapTop = 6,
    .width = 9,
    .height = 2,
    .paletteNum = 11,
    .baseBlock = 0x01fd
};

const struct WindowTemplate sWindowTemplate_AreaMap_Kanto = {
    .bg = 2,
    .tilemapLeft = 17,
    .tilemapTop = 4,
    .width = 12,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x020d
};

static const struct WindowTemplate sWindowTemplate_AreaMap_OneIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 4,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0279
};

static const struct WindowTemplate sWindowTemplate_AreaMap_TwoIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 7,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0285
};

static const struct WindowTemplate sWindowTemplate_AreaMap_ThreeIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 10,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0292
};

static const struct WindowTemplate sWindowTemplate_AreaMap_FourIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x029d
};

static const struct WindowTemplate sWindowTemplate_AreaMap_FiveIsland = {
    .bg = 2,
    .tilemapLeft = 17,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02ad
};

static const struct WindowTemplate sWindowTemplate_AreaMap_SixIsland = {
    .bg = 2,
    .tilemapLeft = 21,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02bd
};

static const struct WindowTemplate sWindowTemplate_AreaMap_SevenIsland = {
    .bg = 2,
    .tilemapLeft = 25,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02cd
};

struct {
    const struct WindowTemplate * window;
    const u32 * tiles;          //changed from tilemap idk of difference if any
} const sAreaMapStructs_SeviiIslands[] = {
    {&sWindowTemplate_AreaMap_OneIsland,   sTilemap_AreaMap_OneIsland},
    {&sWindowTemplate_AreaMap_TwoIsland,   sTilemap_AreaMap_TwoIsland},
    {&sWindowTemplate_AreaMap_ThreeIsland, sTilemap_AreaMap_ThreeIsland},
    {&sWindowTemplate_AreaMap_FourIsland,  sTilemap_AreaMap_FourIsland},
    {&sWindowTemplate_AreaMap_FiveIsland,  sTilemap_AreaMap_FiveIsland},
    {&sWindowTemplate_AreaMap_SixIsland,   sTilemap_AreaMap_SixIsland},
    {&sWindowTemplate_AreaMap_SevenIsland, sTilemap_AreaMap_SevenIsland},
};

static const u16 sCategoryPageIconWindowBg[] = INCBIN_U16("graphics/pokedex/unk_845228C.bin");

//Category page Circular window mon icon x/y;
//Rectangular window x/y mon info caught num name & image
static const u8 sPageIconCoords_1Mon[1][4] = {
    {0x0b, 0x03, 0x0b, 0x0b},
};

static const u8 sPageIconCoords_2Mons[2][4] = {
    {0x03, 0x03, 0x0b, 0x03},
    {0x12, 0x09, 0x0a, 0x0b},
};

static const u8 sPageIconCoords_3Mons[3][4] = {
    {0x01, 0x02, 0x09, 0x02},
    {0x0b, 0x09, 0x03, 0x0b},
    {0x15, 0x03, 0x15, 0x0b}
};

static const u8 sPageIconCoords_4Mons[4][4] = {
    {0x00, 0x02, 0x06, 0x03},
    {0x07, 0x0a, 0x00, 0x0c},
    {0x0f, 0x0a, 0x16, 0x0b},
    {0x16, 0x02, 0x0f, 0x04}
};//left in hex

const u8 (*const sCategoryPageIconCoords[])[4] = {
    sPageIconCoords_1Mon,
    sPageIconCoords_2Mons,
    sPageIconCoords_3Mons,
    sPageIconCoords_4Mons,
};

static const u8 *const sDexCategoryNamePtrs[] = {
    gText_DexCategory_GrasslandPkmn,
    gText_DexCategory_ForestPkmn,
    gText_DexCategory_WatersEdgePkmn,
    gText_DexCategory_SeaPkmn,
    gText_DexCategory_CavePkmn,
    gText_DexCategory_MountainPkmn,
    gText_DexCategory_RoughTerrainPkmn,
    gText_DexCategory_UrbanPkmn,
    gText_DexCategory_RarePkmn,
};

const u16 sPalette_Silhouette[] = INCBIN_U16("graphics/pokedex/unk_8452368.gbapal");

static const u8 sDexScreenPageTurnColumns[][30] = {
    {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 5, 11, 17, 23, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  5,  8, 11, 14, 17, 20, 23, 26, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  4,  5,  7,  8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 1,  2,  3,  4,  7,  8,  9, 10, 11, 12, 13, 15, 16, 17, 19, 20, 21, 23, 24, 25, 27, 28, 29, 30, 30, 30, 30, 30, 30, 30},
    { 1,  2,  3,  4,  5,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 30, 30, 30},
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 30, 30},
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_CategoryMenu = {
    .firstArrowType = 0,
    .firstX = 16,
    .firstY = 80,
    .secondArrowType = 1,
    .secondX = 224,
    .secondY = 80,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1,
};

const struct CursorStruct sCursorStruct_CategoryPage = {
    .left = 0,
    .top = 160,
    .rowWidth = 64,
    .rowHeight = 40,
    .tileTag = 2002,
    .palTag = 0xFFFF,
    .palNum = 4,
};

#include "data/pokemon/pokedex_categories.h"

static void VBlankCB(void)//modern identifies same name, function/ had change to static to fix
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_PokedexScreen(void)
{
    if (!gPaletteFade.active || IsDma3ManagerBusyWithBgCopy())
    {
        RunTasks(); //believe tasks are from DexScreen_loadResources
        RunTextPrinters();
        AnimateSprites();
        BuildOamBuffer();
    }
    else
    {
        UpdatePaletteFade();
    }
}

//looks to be a good plae to put, last view index
void DexScreen_LoadResources(void) //look into equiv emerald function, may be what I need
{
    bool8 natDex;
    u8 taskId;

    natDex = IsNationalPokedexEnabled();
    m4aSoundVSyncOff();
    SetVBlankCallback(NULL);
    ResetPaletteFade();
    ResetSpriteData();
    ResetTasks();
    ScanlineEffect_Stop();
    ResetBgsAndClearDma3BusyFlags(TRUE);
    InitBgsFromTemplates(0, sBgTemplates, NELEMS(sBgTemplates));
    SetBgTilemapBuffer(3, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(2, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(1, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(0, (u16 *)Alloc(BG_SCREEN_SIZE));
    if (natDex)
        DecompressAndLoadBgGfxUsingHeap(3, (void *)sNatDexTiles, BG_SCREEN_SIZE, 0, 0);
    else
        DecompressAndLoadBgGfxUsingHeap(3, (void *)sKantoDexTiles, BG_SCREEN_SIZE, 0, 0);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    m4aSoundVSyncOn();
    SetVBlankCallback(VBlankCB);
    EnableInterrupts(INTR_FLAG_VBLANK);
    taskId = CreateTask(Task_PokedexScreen, 0);//actually think its equiv to pokedexListf
    sPokedexScreenData = Alloc(sizeof(struct PokedexScreenData)); //think  listItems equivalent to pokemonListCount  in EE, which is 0 at start and built w dex IMPORTANT
    *sPokedexScreenData = sDexScreenDataInitialState;
    sPokedexScreenData->taskId = taskId; //without below value graphic gets broken - FOR SOME reason below buffer no longer works? the graphic breaks as I scroll, idk what changed it or what value is needed now
    //...huh...using actual species count fixed it, 907 is species fraejta
    //not sure why am having issues, used base species count but was still able to display
    //form mon since wasn't actually creating new index for those,
    //base species count/species count sould be fine just covering all species indexes that get displayed
    //but the page isn't loading...

    //ok see what works is having a value that is 2 higher than national_species_Count?
    //fucking hell idk why but that worked. *facepalm
    //ok loads nat dex page but still has some things broken for scroll :)
    //no idea if that's because of incomplete data for gen 9 mon or becuase 
    //of my layout rework for dexpagess
    //I assume its gen9 as kanto dex has same layout but no issues
    //idk had to increasse for some reason ogerpon entry wasn't working?
    sPokedexScreenData->listItems = Alloc((BASE_SPECIES_COUNT + 8) * sizeof(struct ListMenuItem)); //AsparagusEduardo from rhh mentnioed this could be problamatic
    sPokedexScreenData->numSeenNational = DexScreen_GetDexCount(FLAG_GET_SEEN, 1);  //need look into how ee (actualy basic emerald logic) does the dex it loads in pieces
    sPokedexScreenData->numOwnedNational = DexScreen_GetDexCount(FLAG_GET_CAUGHT, 1);//rather than all at once, which is what I had in mind
    sPokedexScreenData->numSeenKanto = DexScreen_GetDexCount(FLAG_GET_SEEN, 0);
    sPokedexScreenData->numOwnedKanto = DexScreen_GetDexCount(FLAG_GET_CAUGHT, 0);
    SetBGMVolume_SuppressHelpSystemReduction(0x80);//think I'm better understanding the listitem thing, it uses nationaldexcount to  make a list item and index for every mon
    ChangeBgX(0, 0, 0);     //but think those values don't get populated until the later function getorderedlist count sometjhing
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    gPaletteFade.bufferTransferDisabled = TRUE;
    if (natDex)
        LoadPalette(sNationalDexPalette, BG_PLTT_ID(0), sizeof(sNationalDexPalette)); //instead of sizeof was 0x200
    else
        LoadPalette(sKantoDexPalette, BG_PLTT_ID(0), sizeof(sKantoDexPalette));
    FillBgTilemapBufferRect(3, 0x001, 0,  0, 32, 32, 0);
    FillBgTilemapBufferRect(2, 0x000, 0,  0, 32, 32, 17);
    FillBgTilemapBufferRect(1, 0x000, 0,  0, 32, 32, 17);
    FillBgTilemapBufferRect(0, 0x003, 0,  0, 32,  2, 15);
    FillBgTilemapBufferRect(0, 0x000, 0,  2, 32, 16, 17);
    FillBgTilemapBufferRect(0, 0x003, 0, 18, 32,  2, 15);
}

//beginning of function
void CB2_OpenPokedexFromStartMenu(void)
{
    DexScreen_LoadResources();
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetMainCallback2(CB2_PokedexScreen);
    //SetHelpContext(HELPCONTEXT_POKEDEX);
}

#define FREE_IF_NOT_NULL(ptr0) ({ void *ptr = (ptr0); if (ptr) Free(ptr); })

bool8 DoClosePokedex(void)
{
    switch (gMain.state)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gMain.state++;
        return FALSE;
    case 1:
        if (!gPaletteFade.active) //in callback ran frame by frame, doesn't progress until fade done
            gMain.state = 2;
        else
            UpdatePaletteFade();
        return FALSE;
    case 2:
        FREE_IF_NOT_NULL(sPokedexScreenData->listItems);
        FREE_IF_NOT_NULL(sPokedexScreenData);
        FreeAllWindowBuffers();
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(0));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(1));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(2));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(3));
        BGMVolumeMax_EnableHelpSystemReduction();
        break;
    }
    return TRUE;
}

void CB2_ClosePokedex(void)
{
    if (DoClosePokedex())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    }
}

void CB2_ClosePokedexGotoSummaryScreen(void)
{
    if (DoClosePokedex())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetMainCallback2(CB2_ShowPokemonSummaryScreen2);
        
    }//this part works at least
}//or it seems to, attempting to use this callback elsewhere breaks things

void CB2_ClosePokedexGotoPC(void)
{
    if (DoClosePokedex())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetMainCallback2(CB2_ShowPokemonSummaryScreen3);
        
    }//this part works at least
}

//could also put it here, so isnt triged excesively
//looked further and its perfect, this called in creation and in case for closing dex list, so only need to add it here to both set and clear
//this is task that covers main menu of pokedex, the start of dex logic
//from here it goes to Task_DexScreen_NumericalOrder
//into  Task_DexScreen_ShowMonPage
//task pages work the same process input is used to navigate through pages
//and clears and loads backgrounds and windows as we go
//vsonic IMPORTANT
static void Task_PokedexScreen(u8 taskId) //appears be top menu
{
    int i;
    switch (sPokedexScreenData->state)
    {
    case 0:
        sPokedexScreenData->currentPage = DEX_MAIN_PAGE;
        sPokedexScreenData->CurrentIndexValue = 0; //works, also added on clear - feels like this isn't doing anythingbu Ihvae the value used so keeping..
        sPokedexScreenData->unlockedCategories = 0;
        for (i = 0; i < 9; i++)
            sPokedexScreenData->unlockedCategories |= (DexScreen_IsCategoryUnlocked(i) << i);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        SetMainCallback2(CB2_ClosePokedex);
        DestroyTask(taskId);
        break;
    case 2:
        DexScreen_InitGfxForTopMenu();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);
        if (gPaletteFade.bufferTransferDisabled)
        {
            gPaletteFade.bufferTransferDisabled = FALSE;
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0, RGB_WHITEALPHA);
        }
        else
            BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);  //was 0xFFFF7FFF
        sPokedexScreenData->state = 5;
        break;
    case 5: //can't tell where modeSelectCursorPosBak is getting a value from where it seems to only be set in places I'm not navigating too (now) or yet
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL); //ah this funtion is  assignign it
        if (IsNationalPokedexEnabled())
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sScrollArrowsTemplate_NatDex, &sPokedexScreenData->modeSelectCursorPosBak);
        else
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sScrollArrowsTemplate_KantoDex, &sPokedexScreenData->modeSelectCursorPosBak);
        sPokedexScreenData->state = 6;//think this is end of just displaying the main dex page, after this it takes inpputs for navigation
        break;
    case 6:
        sPokedexScreenData->modeSelectInput = ListMenu_ProcessInput(sPokedexScreenData->modeSelectListMenuId, DEFAULT_MODE); //ok so this is VERY weird, what it does is take the input without actually doing anything with it
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);//just returning the index in the case of pressing A
        if (JOY_NEW(A_BUTTON))
        {
            switch (sPokedexScreenData->modeSelectInput)//different things based on what menu its in
            {
            case LIST_CANCEL: //believe this is last value i.e close pokedex index
                sPokedexScreenData->state = 1; //goes to close pokedex
                break;
            case DEX_CATEGORY_GRASSLAND:
            case DEX_CATEGORY_FOREST:
            case DEX_CATEGORY_WATERS_EDGE:
            case DEX_CATEGORY_SEA:
            case DEX_CATEGORY_CAVE:
            case DEX_CATEGORY_MOUNTAIN:
            case DEX_CATEGORY_ROUGH_TERRAIN:
            case DEX_CATEGORY_URBAN:
            case DEX_CATEGORY_RARE:
                if (DexScreen_IsCategoryUnlocked(sPokedexScreenData->modeSelectInput))
                {
                    RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                    sPokedexScreenData->category = sPokedexScreenData->modeSelectInput;
                    BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                    sPokedexScreenData->state = 7; //load category page
                }
                break;
            case DEX_MODE(NUMERICAL_KANTO):
            case DEX_MODE(NUMERICAL_NATIONAL):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - DEX_CATEGORY_COUNT;
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9; //load numerical dex
                break;
            case DEX_MODE(ATOZ):
            case DEX_MODE(TYPE):
            case DEX_MODE(LIGHTEST):
            case DEX_MODE(SMALLEST):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId); //remove scroll arrow for previous menu, in prep loading next one
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - DEX_CATEGORY_COUNT; //selects mode i.e which list generate based on selection
                sPokedexScreenData->characteristicOrderMenuItemsAbove = sPokedexScreenData->characteristicOrderMenuCursorPos = 0;
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9; //...welp it was as simple as changing this  to 9 and now goes to dex list page not cat page at 7
                break;
            }
            break;
        }
        if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        sPokedexScreenData->pageNum = 0;
        sPokedexScreenData->categoryCursorPosInPage = 0;
        sPokedexScreenData->parentOfCategoryMenu = 0;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu;
        sPokedexScreenData->state = 0;
        break;
    case 8:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
        sPokedexScreenData->state = 0;
        break;
    case 9:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder; //this list function for setting up dex list
        sPokedexScreenData->state = 0;
        break;
    }//removes all stuff for main page, then ends this function as you are moving away from front page of dex
}

static void DexScreen_InitGfxForTopMenu(void)
{
    struct ListMenuTemplate listMenuTemplate;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 30, 20, 17);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 30, 20, 17);
    sPokedexScreenData->modeSelectWindowId = AddWindow(&sWindowTemplate_ModeSelect);
    sPokedexScreenData->selectionIconWindowId = AddWindow(&sWindowTemplate_SelectionIcon);
    sPokedexScreenData->dexCountsWindowId = AddWindow(&sWindowTemplate_DexCounts);
    if (IsNationalPokedexEnabled())
    {
        listMenuTemplate = sListMenuTemplate_NatDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId; //assigns cursor pos and items above from this below in ListMenuInitInternal via ListMenuInit
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->modeSelectItemsAbove, DEFAULT_MODE);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0)); //ok this sets cursor pos, which is passed in the other function,
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Seen, 0, 2, 0); //is where menu starts i.e what value it opens on
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 4, 13, 0); //i.e the row, I think itemsabove, shows 
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenKanto, 46, 13, 2);//how many items in lilst to put above teh selection

        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 4, 24, 0);//if zero you are at top of list?

        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenNational, 46, 24, 2);//seems no? cant tell what items above does here
        
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Owned, 0, 37, 0);//items above seems work same but at value of n-1
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 4, 48, 0); //if select 2 it will sart you 1 value lower?
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedKanto, 46, 48, 2);//ok I understand the effect now but not the purpose

        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 4, 59, 0);

        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedNational, 46, 59, 2);
    }
    else
    {
        listMenuTemplate = sListMenuTemplate_KantoDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId;
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->modeSelectItemsAbove, DEFAULT_MODE);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Seen, 0, 9, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numSeenKanto, 32, 21, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Owned, 0, 37, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numOwnedKanto, 32, 49, 2);
    }
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokedexTableOfContents, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOK);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_GFX);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);
    PutWindowTilemap(sPokedexScreenData->dexCountsWindowId);
    CopyWindowToVram(sPokedexScreenData->dexCountsWindowId, COPYWIN_GFX);
}

static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (!onInit)
        PlaySE(SE_SELECT);
    if (itemIndex == LIST_CANCEL)
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconTiles_Cancel, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconPals_Cancel, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    }
    else
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconGfxPtrs[itemIndex].tiles, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconGfxPtrs[itemIndex].pal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    }
    PutWindowTilemap(sPokedexScreenData->selectionIconWindowId);
    CopyWindowToVram(sPokedexScreenData->selectionIconWindowId, COPYWIN_GFX);
}

static void ItemPrintFunc_DexModeSelect(u8 windowId, s32 itemId, u8 y) //pret eventually made u32 not s, so will have to go through and adjust,
{
    if (itemId >= DEX_CATEGORY_COUNT || sPokedexScreenData->unlockedCategories & (1 << itemId))
        ListMenuOverrideSetColors(TEXT_COLOR_WHITE, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_GREY);
    else
        ListMenuOverrideSetColors(TEXT_DYNAMIC_COLOR_1, TEXT_COLOR_TRANSPARENT, TEXT_DYNAMIC_COLOR_2);
}

//vsonic IMPORTANT this is the function I need, it sets everyting for display of firered dex list
static void Task_DexScreen_NumericalOrder(u8 taskId)
{
    if (sPokedexScreenData->dexOrderId == DEX_ORDER_NUMERICAL_KANTO)
    sPokedexScreenData->orderedDexCount = KANTO_DEX_COUNT;

    if (sPokedexScreenData->dexOrderId == DEX_ORDER_NUMERICAL_NATIONAL)
    sPokedexScreenData->orderedDexCount = NATIONAL_SPECIES_COUNT;//see fi this works
    //dumb fix but works

    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(BG_PLTT_ID(1), 0);
        ListMenuLoadStdPalAt(BG_PLTT_ID(2), 1);
        sPokedexScreenData->orderedDexCount = DexScreen_CountMonsInOrderedList(sPokedexScreenData->dexOrderId); //needed to return list size, butalso to run funciton logic
        sPokedexScreenData->currentPage = DEX_NUMERICAL_LIST;
        sPokedexScreenData->state = 2;//countmons ^ used to tell size of list , changing thing itself didn't affet load times
        break;
    case 1:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_PokedexScreen; //start of dex building, so rebuild main dex page
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_InitGfxForNumericalOrderList();//orderedDexCount used here to make list count, actually building the list
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //same as before was 0xFFFF7FFF
        sPokedexScreenData->state = 5;
        break;
    case 5://modeSelectListMenuId set by ListMenuInit in DexScreen_InitGfxForTopMenu function paasses values cursor pos to the backup here
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL); //but this uses cursorposbak, assuming a backup value?
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateDexOrderScrollArrows();//idk why this ^ is in case 5 & 6 doesn't appear to do anything in 5?
        sPokedexScreenData->state = 6;//could possibly be a good fit to, put initial load basedon index/cursor here?  in case 5
        break;//yeah think that may be it
    case 6://thinking need replace ListMenu_ProcessInput, to control how it would go from here? , without process input list doesn't scroll, Only B press works
        //sPokedexScreenData->characteristicMenuInput = ListMenu_ProcessInput(sPokedexScreenData->orderedListMenuTaskId); //think this is end of dispaly then goes into navigation away from this page
        sPokedexScreenData->characteristicMenuInput = DexScreen_ProcessInput(sPokedexScreenData->orderedListMenuTaskId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);//creates top arrow?
        if (JOY_NEW(A_BUTTON))
        {
            if ((sPokedexScreenData->characteristicMenuInput >> 16) & 1) //pretty much if actually selected someting, i.e selected populated index, there's a mon there
            {
                sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7; //go to mons dex entry
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1; //close dex list
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_DexScreen_ShowMonPage;
        sPokedexScreenData->state = 0;
        break;
    }
}

/*
// u16 ignored is passed but never used - /for port remove ignored, put this in place of ListMenu_ProcessInput think shold work,
//functions used here ported to bottom of file
static u16 TryDoPokedexScroll(u16 selectedMon) //vsonic IMPORTANT  //think equiv ListMenu_ProcessInput
{
    u8 scrollTimer;
    u8 scrollMonIncrement;
    u8 i;
    u16 startingPos;
    u8 scrollDir = 0;

    if (JOY_HELD(DPAD_UP) && (selectedMon > 0)) //selected mon here is more position in the list, i.e not 0 and not end of list
    {
        scrollDir = 1;
        selectedMon = GetNextPosition(1, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);
        CreateScrollingPokemonSprite(1, selectedMon);
        CreateMonListEntry(1, selectedMon); //put so list updates w scroll. ok makes sense
        PlaySE(SE_DEX_SCROLL);//tested and this does indeed only preclude scrolling up and down with dpad not left and right
        //createmonlistentry was the entry for updating based on scroll, so removing that stopped the list updating by not via moving left 
    }
    else if (JOY_HELD(DPAD_DOWN) && (selectedMon < sPokedexScreenData->pokemonListCount - 1))
    {
        scrollDir = 2;
        selectedMon = GetNextPosition(0, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);
        CreateScrollingPokemonSprite(2, selectedMon);
        CreateMonListEntry(2, selectedMon);
        PlaySE(SE_DEX_SCROLL);
    }
    else if (JOY_NEW(DPAD_LEFT) && (selectedMon > 0))
    {
        startingPos = selectedMon;

        for (i = 0; i < 9; i++) //think this is somehow the update, 8 list per page on EE so think this it?
            selectedMon = GetNextPosition(1, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);
        sPokedexScreenData->pokeBallRotation += 16 * (selectedMon - startingPos);
        ClearMonSprites();
        CreateMonSpritesAtPos(selectedMon, 0xE); //this is the left right for createmonlistentry, function is called through this
        PlaySE(SE_DEX_PAGE);
    }
    else if (JOY_NEW(DPAD_RIGHT) && (selectedMon < sPokedexScreenData->pokemonListCount - 1))
    {
        startingPos = selectedMon;
        for (i = 0; i < 9; i++) //has left and right move by 7, in firered moves by 9
            selectedMon = GetNextPosition(0, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);//for porting need top 3 lines and createmonlistentry for left right
        sPokedexScreenData->pokeBallRotation += 16 * (selectedMon - startingPos);
        ClearMonSprites();
        CreateMonSpritesAtPos(selectedMon, 0xE); - replace these

        CreateMonListEntry(0, selectedMon); //believe not needed? for emerald because it displays mon pick as scroll, so think skip this use of the function
    SetGpuReg(REG_OFFSET_BG2VOFS, sPokedexScreenData->initialVOffset); //ok think was wrong PRETTY SURE THIS, is left right scroll and that first arg is scroll direction
        //1 and 2 are up and down respectively, and zero is left right
    sPokedexScreenData->listVOffset = 0;
    sPokedexScreenData->listMovingVOffset = 0;    don't konw if need all, or just createmonlistentry 0

        PlaySE(SE_DEX_PAGE);
    }

    if (scrollDir == 0)
    {
        // Left/right input just snaps up/down, no scrolling
        sPokedexScreenData->scrollSpeed = 0;
        return selectedMon;
    }
    //think most this below is irrelevant for port, along w scroll speed/increment stuff
    //emerald speeds up to max, while firered has one constant max speed when held.
    //so think can ignore everthing below other than the return?

    scrollMonIncrement = sScrollMonIncrements[sPokedexScreenData->scrollSpeed / 4];
    scrollTimer = sScrollTimers[sPokedexScreenData->scrollSpeed / 4];
    sPokedexScreenData->scrollTimer = scrollTimer;
    sPokedexScreenData->maxScrollTimer = scrollTimer;
    sPokedexScreenData->scrollMonIncrement = scrollMonIncrement;
    sPokedexScreenData->scrollDirection = scrollDir;
    sPokedexScreenData->pokeBallRotationStep = scrollMonIncrement / 2;
    UpdateDexListScroll(sPokedexScreenData->scrollDirection, sPokedexScreenData->scrollMonIncrement, sPokedexScreenData->maxScrollTimer);
    if (sPokedexScreenData->scrollSpeed < 12) //^says dexList but seems has nothing to do w list and is just mon icons and the the pokeball when scrolling?
        sPokedexScreenData->scrollSpeed++;
    return selectedMon;
}
*/

//vsonic IMPORTANT, what builds the dex list
static void DexScreen_InitGfxForNumericalOrderList(void) //important
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 17);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu; //template info for displaying dex list mon
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount; //changign this doesnt chagne load time
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId);//think this the important value //passes template to use to make page
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokemonListNoColor, TEXT_CENTER);//above line and this paired, fill buffer, than print onto space, same as two below
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX); //then copies two windows to ram, meaning actual building part is DexScreen_InitListMenuForOrderedList
}

//changing list here does nothing, think becuase changed case for category to no longer go to list?
static void Task_DexScreen_CharacteristicOrder(u8 taskId) //changes here also seemed to have no effect?
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(BG_PLTT_ID(1), 0);
        ListMenuLoadStdPalAt(BG_PLTT_ID(2), 1);
        sPokedexScreenData->orderedDexCount = DexScreen_CountMonsInOrderedList(sPokedexScreenData->dexOrderId);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_PokedexScreen;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_CreateCharacteristicListMenu();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateDexOrderScrollArrows();
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->characteristicMenuInput = ListMenu_ProcessInput(sPokedexScreenData->orderedListMenuTaskId, DEX_LIST_MODE);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            if (((sPokedexScreenData->characteristicMenuInput >> 16) & 1) && !DexScreen_LookUpCategoryBySpecies(sPokedexScreenData->characteristicMenuInput))
            {
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        sPokedexScreenData->parentOfCategoryMenu = 1;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu; 
        sPokedexScreenData->state = 0;
        break;
    }
}

//doesn't do anything, was potentially for other pages that used to go from category pages but I changed?
//either way this isn't what I need to change I believe
static void DexScreen_CreateCharacteristicListMenu(void) //vsonic like numericla dex lit but for teh non numerical lists i.e weight a-z type etc.
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 17);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount;
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId); //think this the important value,// removing this doesn't affect load times
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_SearchNoColor, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

//vsonic IMPORTANT also relevant for dex change plans,
//need make read like emerald load dex in pieces nto all mon
//think equivalent to CreatePokedexList in EE
static u16 DexScreen_CountMonsInOrderedList(u8 orderIdx) //this function returns size of list, but ALSO sets cursor position callback, when opening for first time
{
    
    int selectedIndex;
    u16 *itemsAbove_p, *cursorPos_p;


    switch (orderIdx)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        cursorPos_p = &sPokedexScreenData->kantoOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->kantoOrderMenuItemsAbove;
        break;
    case DEX_ORDER_ATOZ:    
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        cursorPos_p = &sPokedexScreenData->characteristicOrderMenuCursorPos; //think see now why it always defaults to 0, they share same value 
        itemsAbove_p = &sPokedexScreenData->characteristicOrderMenuItemsAbove; //while national and kanto have their own,
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        cursorPos_p = &sPokedexScreenData->nationalOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->nationalOrderMenuItemsAbove;
        break;
    }
    
    selectedIndex = *cursorPos_p + *itemsAbove_p;

    return DexScreen_CreateList_ReturnCount(orderIdx,selectedIndex); //should hopefully work the same, just look better - works
    
    //can put everythin gbelow this in a funtion, use like process input, to assign ret, have it do funtion logic and do return value u16 ret
    //need take argument orderIdx, and selectedIndex, put most arguments inside function, leave only ret selectedIndex & itemsabove and cursorPos in this function

    
}

//vsonic IMPORTANT
static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order) //belive this is actual dex list build, i.e what builds it at once
{
    switch (order)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->kantoOrderMenuCursorPos, sPokedexScreenData->kantoOrderMenuItemsAbove, DEX_LIST_MODE);
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->characteristicOrderMenuCursorPos, sPokedexScreenData->characteristicOrderMenuItemsAbove, DEX_LIST_MODE);
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->nationalOrderMenuCursorPos, sPokedexScreenData->nationalOrderMenuItemsAbove, DEX_LIST_MODE);
        break;
    }
}


//and here
static void DexScreen_DestroyDexOrderListMenu(u8 order)
{
    switch (order)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->kantoOrderMenuCursorPos, &sPokedexScreenData->kantoOrderMenuItemsAbove);
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->characteristicOrderMenuCursorPos, &sPokedexScreenData->characteristicOrderMenuItemsAbove);
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->nationalOrderMenuCursorPos, &sPokedexScreenData->nationalOrderMenuItemsAbove);
        break;
    }
}

static u8 DexScreen_CreateDexOrderScrollArrows(void)
{
    struct ScrollArrowsTemplate template = sDexOrderScrollArrowsTemplate;
    if (sPokedexScreenData->orderedDexCount > sListMenuTemplate_OrderedListMenu.maxShowed)
        template.fullyDownThreshold = sPokedexScreenData->orderedDexCount - sListMenuTemplate_OrderedListMenu.maxShowed;
    else
        template.fullyDownThreshold = 0;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->modeSelectCursorPosBak);
}

struct PokedexListItem
{
    u16 species;
    bool8 seen:1;
    bool8 caught:1;
};

static void ItemPrintFunc_OrderedListMenu(u8 windowId, s32 itemId, u8 y)
{
    u32 itemId_ = itemId; //potentially revise later when change itemId stuff to u32
    u16 species = itemId_;
    bool8 seen = (itemId_ >> 16) & 1;  // not used but required to match
    bool8 caught = (itemId_ >> 17) & 1;
    u8 type1;
    u8 x = 14; //total graphic shift x -4. pokeball + 2, so sub 2
    u8 Type_xValue = 148;
    DexScreen_PrintMonDexNo(sPokedexScreenData->numericalOrderWindowId, FONT_SMALL, species, x, y); //x was 12
    if (caught)
    {
        BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, MENU_INFO_ICON_CAUGHT, x + 33, y); //pokeball icon //x was 40
        type1 = gBaseStats[species].type1;
        BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, type1 + 1, Type_xValue, y); //4bpp 32 width between these 2 type icons
        if (type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, gBaseStats[species].type2 + 1, Type_xValue + 36, y);
    }
}


#define POKEDEX_CATEGORY_CURSOR_DATA
static void Task_DexScreen_CategorySubmenu(u8 taskId)
{
    int pageFlipCmd;
    u8 *ptr;
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->currentPage = DEX_HABITAT_PAGE;
        DexScreen_GetPageLimitsForCategory(sPokedexScreenData->category);
        if (sPokedexScreenData->pageNum < sPokedexScreenData->firstPageInCategory)
            sPokedexScreenData->pageNum = sPokedexScreenData->firstPageInCategory;
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        HideBg(2);
        HideBg(1);
        switch (sPokedexScreenData->parentOfCategoryMenu)
        {
        case 0:
        default:
            gTasks[taskId].func = Task_PokedexScreen;
            break;
        case 1:
            gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
            break;
        }
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_CreateCategoryListGfx(FALSE);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        sPokedexScreenData->state = 3;
        break;
    case 3:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 4;
        break;
    case 4: //believe for accessing category from within pokedex
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateCategoryMenuScrollArrows();
        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, sPokedexScreenData->numMonsOnPage);
        sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
        pageFlipCmd = 0;
        if (JOY_NEW(A_BUTTON) && DexScreen_GetSetPokedexFlag(sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage], FLAG_GET_SEEN, TRUE))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 12;
            break;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_LEFT))
        {
            if (sPokedexScreenData->categoryCursorPosInPage != 0)
            {
                sPokedexScreenData->categoryCursorPosInPage--;
                PlaySE(SE_SELECT);
                break;
            }
            else
                pageFlipCmd = 1;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_RIGHT))
        {
            if (sPokedexScreenData->categoryCursorPosInPage < sPokedexScreenData->numMonsOnPage - 1)
            {
                sPokedexScreenData->categoryCursorPosInPage++;
                PlaySE(SE_SELECT);
                break;
            }
            else
                pageFlipCmd = 2;
        }
        if (pageFlipCmd == 0)
            pageFlipCmd = DexScreen_InputHandler_GetShoulderInput();
        switch (pageFlipCmd)
        {
        case 0: // No action
            break;
        case 1: // Left
            while (sPokedexScreenData->pageNum > sPokedexScreenData->firstPageInCategory)
            {
                sPokedexScreenData->pageNum--;
                if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, sPokedexScreenData->pageNum))
                {
                    sPokedexScreenData->state = 8;
                    break;
                }
            }
            if (sPokedexScreenData->state != 8)
                sPokedexScreenData->state = 6;
            break;
        case 2: // Right
            while (sPokedexScreenData->pageNum < sPokedexScreenData->lastPageInCategory - 1)
            {
                sPokedexScreenData->pageNum++;
                if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, sPokedexScreenData->pageNum))
                {
                    sPokedexScreenData->state = 10;
                    break;
                }
            }
            if (sPokedexScreenData->state != 10)
                sPokedexScreenData->state = 6;
            break;
        }
        if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 6;
        }
        break;
    case 6:
    case 7:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
        ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
        BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
        sPokedexScreenData->state = 1;
        break;
    case 8:
    case 10:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        ListMenuUpdateCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0, 0xA0, 0);
        sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->state++;
        break;
    case 9:
        if (DexScreen_FlipCategoryPageInDirection(0))
        {
            sPokedexScreenData->categoryCursorPosInPage = sPokedexScreenData->numMonsOnPage - 1;
            sPokedexScreenData->state = 5;
        }
        break;
    case 11:
        if (DexScreen_FlipCategoryPageInDirection(1))
        {
            sPokedexScreenData->categoryCursorPosInPage = 0;
            sPokedexScreenData->state = 5;
        }
        break;
    case 12:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage];
        PlaySE(SE_SELECT);
        sPokedexScreenData->state = 14; //goes to creating info page
        break;
    case 13:
        RemoveDexPageWindows();
        sPokedexScreenData->state = 4;
        break;
    case 14:
        sPokedexScreenData->currentPage = DEX_INFO_FROM_HABITAT;
        DexScreen_DrawMonDexPage(FALSE); //from category page go to dex entry page
        sPokedexScreenData->state = 15;
        break;
    case 15:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
        // fallthrough
    case 16:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0])
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
            {
                sPokedexScreenData->data[0]--;
            }
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 17;
        }
        break;
    case 17: //navigation, think attempt put scrollmon vertical here, vsonic, hopefully simple as but need it to update cat page num as well
        if (JOY_NEW(A_BUTTON)) //believe can'tuse tryscrollmon vertical, as that explicitly uses dex list stuff and not category org stuff
        {
            RemoveDexPageWindows();
            //FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);//but need compare w default to see how changed, if need make scroll logic
            //CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->currentPage = DEX_EVO_FROM_HABITAT;
            sPokedexScreenData->state = 28;
            //sPokedexScreenData->state = 21; //change to evo page start 28
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 18;
        }
        else if (JOY_NEW(DPAD_LEFT) && DexScreen_TryDisplayForms(1)) //use of this function means if able to scroll in that direction
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 27; //works now yay
        }
        else if (JOY_NEW(DPAD_RIGHT) && DexScreen_TryDisplayForms(0)) //vsonic attempt use add scrolling between category dex entires
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 27; //tried 27 and 14
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;//wow so this repeats the dex info page logic, area page and all, but more restricted
    case 18: //and with my form dex changes I would need to add on here for form dex to work from cateogry page...
        DexScreen_CreateCategoryListGfx(FALSE);
        DexScreen_DexPageZoomEffectFrame(0, 6);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 19;
        break;
    case 19:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 6;
        sPokedexScreenData->state++;
        // fallthrough
    case 20:
        if (sPokedexScreenData->data[1])
        {
            if (sPokedexScreenData->data[0])
            {
                sPokedexScreenData->data[1]--;
                FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 1; //BACK to category page
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 13;
        }
        break;
    case 21:
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->currentPage = DEX_AREA_FROM_HABITAT;
        sPokedexScreenData->state = 22;
        break;
    case 22:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 23;
        break;
    case 23: //area page navigation
        if (JOY_NEW(A_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 26; //back to cat view
        }
        else if (JOY_NEW(B_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 30;//24;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 24: //equiv of 10
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 25;
        break;
    case 25: //equiv of 11
        DexScreen_DrawMonDexPage(FALSE); //pressing B return from Area page, in category menu/task
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 17; //change to info page naviation case,is already that
        break;
    case 26:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 18;
        break;
    case 27: //for form dex left right, on dex page
        HideBg(2); //will need set dexSpecies reassignment in new function, that loops form id table
        HideBg(1); //if dexspecies is entry 0, before reassignment, don't make left arrow,  if next entry is 0xffff don't make right arrow
        // foud this can use GET_BASE_SPECIES_ID(speciesId) can use to check if put left arrow
        sPokedexScreenData->state = 36; //32; //where dex page first drawn
        break;
    case 28: //evo page exper
         //values for dex evo page
         //wrap this in function called drawevo page, so can bring in text changes
        //has issues make new function for rather than trying to half ass it
        //FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
        //DexScreen_PrintControlInfo(gText_NextPreviousData);
        //CopyBgTilemapBufferToVram(1); //or not, hidebg isn't working here there's some kind of leak or something idk fuck I'm tired
        //ShowBg(1); //realized what these are for now, 
        //some processes are longer and will make data display before it should withoutmaking it invisible
        DexScreen_DrawMonEvoPage(FALSE);
        sPokedexScreenData->state = 29; //put icon stat bar logic here or so
        //HideBg(2);
        //HideBg(1);//this appears to do same as fill bg, guess in different ways, proba fail safe?
        break; //think just makes invisible doesn't actually clear data?
    case 29: //equiv 15
    {
        UpdateStatBars(sPokedexScreenData->dexSpecies);
        if (JOY_NEW(A_BUTTON)) //evo page navigation
        {
            Task_SwitchScreensFromEvolutionScreen();
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
            CopyBgTilemapBufferToVram(1);
            //Task_SwitchScreensFromEvolutionScreen();
            sPokedexScreenData->state = 21; //go to area page
        }
        else if (JOY_NEW(B_BUTTON))
        {
            /*FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);*/
            Task_SwitchScreensFromEvolutionScreen();

            //doens't seem to be needed
            //RemoveDexPageWindows();  skipping this in case its the issue
            sPokedexScreenData->state = 24; //this seems to be working
            //sPokedexScreenData->state = 10;
        }
        else if (JOY_NEW(DPAD_DOWN)) //move to new case for scrolling evo methods, //up down, press b to return here, A goes to info page of that mon
        {
            //believe means if has evolution
            if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)// && sPokedexScreenData->sEvoScreenData.numSeen != 0) //this is part that prevents arrow from showing for only 1 evo/mon seen
            {
                sPokedexScreenData->sEvoScreenData.arrowSpriteId = CreateSprite(&gSpriteTemplate_Arrow, 7, 88, 0);
                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].animNum = 2;
                sPokedexScreenData->state = 35; //make new cases
            }
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
    }
        break;
    case 30: //clear area page go to evo, //copy of 1o for area to avoidp break flow
        
        //added block -from numerical
            /*FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);*/
        
        DexScreen_DestroyAreaScreenResources();
        RemoveDexPageWindows();
        sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
        sPokedexScreenData->state = 31;
        break;
    case 31:
        DexScreen_DrawMonEvoPage(FALSE); 
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 29;
        break;
    case 32:
        sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE); //draws the mon info page, false is for saying its not a mon just adding to dex from catch
        sPokedexScreenData->state++;
        break; 
    case 33:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL); //play cry as page loads
        sPokedexScreenData->state++;
        break;
    case 34:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //fade in finish displaying page
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 17;
        break;
    case 35: 
    {
        u8 base_y = 88;  //only used with moving arrow sprite and sprite start value is 58,  so think thsoe need to match
        u8 base_y_offset = 9;   //that was correct
        //u8 pos = sPokedexScreenData->sEvoScreenData.menuPos;
        //u8 max = sPokedexScreenData->sEvoScreenData.numAllEvolutions;
        u16 targetSpecies = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
        
        //if not set, set, should only work first time hopefully, make sure to clear when done
        if (!(VarGet(VAR_0x408C)))
            VarSet(VAR_0x408C, sPokedexScreenData->dexSpecies);
            //store initial species page, if curr page species doesn;t equal var, set target sppecies to var
            //otherwise close
            //potentially clear var afterwards
            //start of setup to attempt track navigating between evo pages
        
        UpdateStatBars(sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos]);
        
        if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)
        {
            if (JOY_NEW(DPAD_DOWN)) //dpad on evo doesn't work right, moving up works, but moving down only works when already down
            {
                /*while (TRUE)
                {
                    pos += 1;
                    if (pos >= max)
                        pos = 0;

                    if (sPokedexScreenData->sEvoScreenData.seen[pos] == TRUE)
                        break;
                }*/
                if (sPokedexScreenData->sEvoScreenData.menuPos == sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1)
                    sPokedexScreenData->sEvoScreenData.menuPos = 0;// = sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1;
                else
                    sPokedexScreenData->sEvoScreenData.menuPos += 1;

                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].pos1.y = base_y + base_y_offset * sPokedexScreenData->sEvoScreenData.menuPos;
                targetSpecies = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
                UpdateStatBars(sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos]);
                //sPokedexScreenData->sEvoScreenData.menuPos = pos; //store end position
            }
            else if (JOY_NEW(DPAD_UP))
            {
                if (sPokedexScreenData->sEvoScreenData.menuPos == 0)
                    sPokedexScreenData->sEvoScreenData.menuPos = sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1;
                else
                    sPokedexScreenData->sEvoScreenData.menuPos -= 1;

                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].pos1.y = base_y + base_y_offset * sPokedexScreenData->sEvoScreenData.menuPos;
                targetSpecies = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
                UpdateStatBars(sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos]);
            }
        }

        
        
       if (JOY_NEW(A_BUTTON))
        {
            sPokedexScreenData->dexSpecies = targetSpecies;                

               
                //sPokedexScreenData->sEvoScreenData.fromEvoPage = TRUE;
                PlaySE(SE_SELECT);
                DestroySprite(&gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId]); //clear the arrow
                //Task_SwitchScreensFromEvolutionScreen();
                RemoveDexPageWindows();
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA); 
                Task_SwitchScreensFromEvolutionScreen();               
                sPokedexScreenData->state++;  //go to build up from info page
                 //not quite right has graphic issues when going to between pika evos
                //sPokedexScreenData->state = 10;
                //sPokedexScreenData->state = 14;
                //sPokedexScreenData->state = 16;
                //BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                //gTasks[taskId].func = Task_LoadInfoScreenWaitForFade;
                //gTasks[taskId].func = Task_LoadEvolutionScreen;               

        }


        //Exit to overview
        if (JOY_NEW(B_BUTTON))
        {   //if not on initial species page you loaded into dex with, load that page
            /*if (VarGet(VAR_0x408C) != sPokedexScreenData->dexSpecies)//NationalPokedexNumToSpeciesHGSS(sPokedexListItem->dexNum))
            {
                u16 targetSpecies   = VarGet(VAR_0x408C); //load initial dex page
                u16 dexNum          = SpeciesToNationalPokedexNum(targetSpecies);
                sPokedexScreenData->dexSpecies = targetSpecies;
                //sPokedexListItem->seen   = GetSetPokedexFlag(dexNum, FLAG_GET_SEEN);
                //sPokedexListItem->owned  = GetSetPokedexFlag(dexNum, FLAG_GET_CAUGHT);

                //sPokedexScreenData->sEvoScreenData.fromEvoPage = TRUE;
                PlaySE(SE_PC_OFF); //may remove sound use
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                //gTasks[taskId].func = Task_LoadInfoScreenWaitForFade;
                Task_SwitchScreensFromEvolutionScreen();
                UpdateStatBars(VarGet(VAR_0x408C));
                sPokedexScreenData->state = 16;
                //gTasks[taskId].func = Task_LoadEvolutionScreen;
            }
            else*/
            {
                
                //BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
                //PlaySE(SE_PC_OFF);
                //Task_SwitchScreensFromEvolutionScreen();
                DestroySprite(&gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId]); //clear the arrow
                sPokedexScreenData->sEvoScreenData.menuPos = 0; //make sure arrow position reset back to 0, for when call arrows again
                VarSet(VAR_0x408C, 0);
                sPokedexScreenData->state = 29; //should hopefully clear page so doesn't build up
                //return;               //seems to work to clear resources only thing left is getting rid of the damn icon
            } //change to hopefully clear array change bar without reloading page
        } 
       
    }
    break;
    case 36:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->state++;
    case 37:
        sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE); //draws the mon info page, false is for saying its not a mon just adding to dex from catch
        sPokedexScreenData->state++;
        break; 
    case 38:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL); //play cry as page loads
        sPokedexScreenData->state++;
        break;
    case 39:
        //without fade doesn't load correctly for some reason - still doesn't clear stat bars
        TryDestroyStatBars();  //works, don't know why this specifically needed extra protection but it all works
        TryDestroyStatBarsBg();
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //fade in finish displaying page
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 17;//believe here is where displaying mon info page is actually complete
        break;
    
    }
    
}

static u8 DexScreen_CreateCategoryMenuScrollArrows(void)
{
    struct ScrollArrowsTemplate template = sScrollArrowsTemplate_CategoryMenu;
    template.fullyUpThreshold = sPokedexScreenData->firstPageInCategory;
    template.fullyDownThreshold = sPokedexScreenData->lastPageInCategory - 1;
    sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->modeSelectCursorPosBak);
}

/*
 * Returns 1 to flip pages left, 2 to flip pages right, 0 for no action
 */
static int DexScreen_InputHandler_GetShoulderInput(void)
{
    switch (gSaveBlock2Ptr->optionsButtonMode)
    {
    case OPTIONS_BUTTON_MODE_L_EQUALS_A:
        // Using the JOY_HELD and JOY_NEW macros here does not match!
        if ((gMain.heldKeys & R_BUTTON) && (gMain.newKeys & DPAD_LEFT))
            return 1;
        else if ((gMain.heldKeys & R_BUTTON) && (gMain.newKeys & DPAD_RIGHT))
            return 2;
        else
            return 0;
    case OPTIONS_BUTTON_MODE_LR:
        if (gMain.newKeys & L_BUTTON)
            return 1;
        else if (gMain.newKeys & R_BUTTON)
            return 2;
        else
            return 0;
    case OPTIONS_BUTTON_MODE_HELP:
    default:
        return 0;
    }
}

void CB2_OpenDexPageFromSummScreen(void)
{


    DmaFillLarge16(3, 0, (u8 *)VRAM, VRAM_SIZE, 0x1000)
    DmaClear32(3, OAM, OAM_SIZE);
    DmaClear16(3, PLTT, PLTT_SIZE);
    DexScreen_LoadResources();

    sPokedexScreenData->dexSpecies = GetMonData(&gPlayerParty[GetLastViewedMonIndex()],MON_DATA_SPECIES);
    DexScreen_LookUpCategoryBySpecies(sPokedexScreenData->dexSpecies);
    gTasks[sPokedexScreenData->taskId].func = Task_DexScreen_DexPageFromSummaryScreen; //again putting here below lookup just in case order matered
    
    SetMainCallback2(CB2_PokedexScreen);
}

void CB2_OpenDexPageFromPCSummScreen(void)
{


    DmaFillLarge16(3, 0, (u8 *)VRAM, VRAM_SIZE, 0x1000)
    DmaClear32(3, OAM, OAM_SIZE);
    DmaClear16(3, PLTT, PLTT_SIZE);
    DexScreen_LoadResources();

    //this part is the problem, gplayerparty not right to use
    //works for loading species, but returning to party menu doesn't work
    sPokedexScreenData->dexSpecies = GetMonData(GetBoxedMonPtr(StorageGetCurrentBox(), GetLastViewedMonIndex()),MON_DATA_SPECIES);
    DexScreen_LookUpCategoryBySpecies(sPokedexScreenData->dexSpecies);
    gTasks[sPokedexScreenData->taskId].func = Task_DexScreen_DexPageFromPCSummaryScreen; //again putting here below lookup just in case order matered
    
    SetMainCallback2(CB2_PokedexScreen);//
}

static void Task_DexScreen_DexPageFromSummaryScreen(u8 taskId) //called from above dexScreen register function, which is called only from bs_commands so change need go there
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        PutWindowTilemap(0);
        PutWindowTilemap(1);

        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 3;
        break;
    case 1:
        RemoveDexPageWindows();

        gMain.state = 0;
        sPokedexScreenData->state = 2;
        break;
    case 2:
        SetMainCallback2(CB2_ClosePokedexGotoSummaryScreen);
        DestroyTask(taskId);
        break;
    case 3:
        gPaletteFade.bufferTransferDisabled = 0;
        //removing palette loads it MUCH faster
        //conclusion was putting fade upon fade and making it wait longer
        //BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0xffff);

        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);
        sPokedexScreenData->state = 4;        
        break;
    case 4:
    sPokedexScreenData->state = 5; 
        break;
    case 5:
        DexScreen_DestroyAreaScreenResources(); //for some reason need this up here for 
        DexScreen_CreateCategoryListGfx(TRUE);//full window to load without cutt off stat bars
        DexScreen_DrawMonDexPage(FALSE); 
        sPokedexScreenData->currentPage = DEX_REGISTER_PAGE;
        sPokedexScreenData->state = 6;
       break;
    case 6:
         sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
    case 7:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0]) //just makes it zoom in doesn't fix glitch, but actually like the zoom
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state++;
        }
        break;
    case 8://replace w full input
        sPokedexScreenData->state++;
        break;
    case 9:
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
            sPokedexScreenData->state = 14; //going to evo page
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 2;
        }
        else if (JOY_NEW(DPAD_LEFT) && DexScreen_TryDisplayForms(1)) //use of this function means if able to scroll in that direction
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 10;
        }
        else if (JOY_NEW(DPAD_RIGHT) && DexScreen_TryDisplayForms(0)) //vsonic attempt use add scrolling between category dex entires
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 10;
        } //fill in when fix //looks like all Ineed to do is change dexSPecis
        else //else here just means pressing start?
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 10:
        HideBg(2); //will need set dexSpecies reassignment in new function, that loops form id table
        HideBg(1); //if dexspecies is entry 0, before reassignment, don't make left arrow,  if next entry is 0xffff don't make right arrow
        // foud this can use GET_BASE_SPECIES_ID(speciesId) can use to check if put left arrow
        sPokedexScreenData->state++;
        break;
    case 11:
    sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE); //draws the mon info page, false is for saying its not a mon just adding to dex from catch
        sPokedexScreenData->state++;
        break; 
    case 12:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL); //play cry as page loads
        sPokedexScreenData->state++;
        break;
    case 13:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //fade in finish displaying page
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 9;
        break;//end of form loop
    case 14: //evo page exper
        DexScreen_DrawMonEvoPage(FALSE);
        sPokedexScreenData->state = 15; 
        break; 
    case 15://evo navi
    {
        UpdateStatBars(sPokedexScreenData->dexSpecies); //now creates bars nto just update
        if (JOY_NEW(A_BUTTON))//evo navigation page make down dpad craete arrow// then go to new navigation case so A B do different things
        {
            sPokedexScreenData->state = 2;
            /*Task_SwitchScreensFromEvolutionScreen();
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state++;//go to area*/
        }
        else if (JOY_NEW(B_BUTTON))//and down and up move through evolutions
        {
            Task_SwitchScreensFromEvolutionScreen(); //might be fix I need. was going to draw evo without doign the clear
            RemoveDexPageWindows();
            sPokedexScreenData->state = 21; //this seems to be working //why am I going to 10?
        }//back to info
    }
    break;//think want add a left right, input function specifically for register dex
    //would be to check evo paths bst and stat distribution but since its still for register dex keep it bare bones
    //so no checking and navigating to evo entries
    case 16: //draw area page -area didn't load right skipping 
        sPokedexScreenData->currentPage = DEX_AREA_FROM_LIST;
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state++;
        break;
    case 17:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state++;
        break;
    case 18:     //area page naviagation //nother stand in for process input function
        if (JOY_NEW(A_BUTTON)) //close
        {
            //BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 2;
        }
        else if (JOY_NEW(B_BUTTON))//return to evo page
        {
            
            sPokedexScreenData->state++; //changed here was 10 - made universal clear
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 19: //clear area page go to evo, //copy of 1o for area to avoidp break flow

            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);

        DexScreen_DestroyAreaScreenResources();
        RemoveDexPageWindows();
        sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
        sPokedexScreenData->state++;
        break;
    case 20:
        DexScreen_DrawMonEvoPage(FALSE); //ok looks like its workin
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state++;
        break;//end area page naviation
    case 21: //evo navigate to info
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state++;
        break;
    case 22:
        sPokedexScreenData->currentPage = DEX_INFO_FROM_LIST;
        DexScreen_DrawMonDexPage(FALSE); //same as other, Press B return from area page
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        //sPokedexScreenData->state = 14;
        sPokedexScreenData->state = 9;
        break;
    }
    
}

static void Task_DexScreen_DexPageFromPCSummaryScreen(u8 taskId) //called from above dexScreen register function, which is called only from bs_commands so change need go there
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        PutWindowTilemap(0);
        PutWindowTilemap(1);

        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 3;
        break;
    case 1:
        RemoveDexPageWindows();

        gMain.state = 0;
        sPokedexScreenData->state = 2;
        break;
    case 2:
        SetMainCallback2(CB2_ClosePokedexGotoPC);
        DestroyTask(taskId);
        break;
    case 3:
        gPaletteFade.bufferTransferDisabled = 0;
        //removing palette loads it MUCH faster
        //conclusion was putting fade upon fade and making it wait longer
        //BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0xffff);

        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);
        sPokedexScreenData->state = 4;        
        break;
    case 4:
    sPokedexScreenData->state = 5; 
        break;
    case 5:
        DexScreen_DestroyAreaScreenResources(); //for some reason need this up here for 
        DexScreen_CreateCategoryListGfx(TRUE);//full window to load without cutt off stat bars
        DexScreen_DrawMonDexPage(FALSE); 
        sPokedexScreenData->currentPage = DEX_REGISTER_PAGE;
        sPokedexScreenData->state = 6;
       break;
    case 6:
         sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
    case 7:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0]) //just makes it zoom in doesn't fix glitch, but actually like the zoom
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state++;
        }
        break;
    case 8://replace w full input
        sPokedexScreenData->state++;
        break;
    case 9:
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
            sPokedexScreenData->state = 14; //going to evo page
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 2;
        }
        else if (JOY_NEW(DPAD_LEFT) && DexScreen_TryDisplayForms(1)) //use of this function means if able to scroll in that direction
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 10;
        }
        else if (JOY_NEW(DPAD_RIGHT) && DexScreen_TryDisplayForms(0)) //vsonic attempt use add scrolling between category dex entires
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 10;
        } //fill in when fix //looks like all Ineed to do is change dexSPecis
        else //else here just means pressing start?
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 10:
        HideBg(2); //will need set dexSpecies reassignment in new function, that loops form id table
        HideBg(1); //if dexspecies is entry 0, before reassignment, don't make left arrow,  if next entry is 0xffff don't make right arrow
        // foud this can use GET_BASE_SPECIES_ID(speciesId) can use to check if put left arrow
        sPokedexScreenData->state++;
        break;
    case 11:
    sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE); //draws the mon info page, false is for saying its not a mon just adding to dex from catch
        sPokedexScreenData->state++;
        break; 
    case 12:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL); //play cry as page loads
        sPokedexScreenData->state++;
        break;
    case 13:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //fade in finish displaying page
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 9;
        break;//end of form loop
    case 14: //evo page exper
        DexScreen_DrawMonEvoPage(FALSE);
        sPokedexScreenData->state = 15; 
        break; 
    case 15://evo navi
    {
        UpdateStatBars(sPokedexScreenData->dexSpecies); //now creates bars nto just update
        if (JOY_NEW(A_BUTTON))//evo navigation page make down dpad craete arrow// then go to new navigation case so A B do different things
        {
            sPokedexScreenData->state = 2;
            /*Task_SwitchScreensFromEvolutionScreen();
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state++;//go to area*/
        }
        else if (JOY_NEW(B_BUTTON))//and down and up move through evolutions
        {
            Task_SwitchScreensFromEvolutionScreen(); //might be fix I need. was going to draw evo without doign the clear
            RemoveDexPageWindows();
            sPokedexScreenData->state = 21; //this seems to be working //why am I going to 10?
        }//back to info
    }
    break;//think want add a left right, input function specifically for register dex
    //would be to check evo paths bst and stat distribution but since its still for register dex keep it bare bones
    //so no checking and navigating to evo entries
    case 16: //draw area page -area didn't load right skipping 
        sPokedexScreenData->currentPage = DEX_AREA_FROM_LIST;
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state++;
        break;
    case 17:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state++;
        break;
    case 18:     //area page naviagation //nother stand in for process input function
        if (JOY_NEW(A_BUTTON)) //close
        {
            //BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 2;
        }
        else if (JOY_NEW(B_BUTTON))//return to evo page
        {
            
            sPokedexScreenData->state++; //changed here was 10 - made universal clear
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 19: //clear area page go to evo, //copy of 1o for area to avoidp break flow

            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);

        DexScreen_DestroyAreaScreenResources();
        RemoveDexPageWindows();
        sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
        sPokedexScreenData->state++;
        break;
    case 20:
        DexScreen_DrawMonEvoPage(FALSE); //ok looks like its workin
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state++;
        break;//end area page naviation
    case 21: //evo navigate to info
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state++;
        break;
    case 22:
        sPokedexScreenData->currentPage = DEX_INFO_FROM_LIST;
        DexScreen_DrawMonDexPage(FALSE); //same as other, Press B return from area page
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        //sPokedexScreenData->state = 14;
        sPokedexScreenData->state = 9;
        break;
    }
    
}

//so learned a lot from going over options menu/
//biggest take away is what I did by accident
//making a struct value to track what page I was on, is a MAJOR help
//rather than needing to make massive switch cases to track movement
//I can put that individual logic in a process input that will change based on the page
//OptionMenu_ProcessInput
//and long functions like this can be broken up
//as it is  now, this funciton covers the info page, and area page
static void Task_DexScreen_ShowMonPage(u8 taskId)//think task show dex entry from the scrolled list page, so possibly what I need  //vsonic
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->currentPage = DEX_INFO_FROM_LIST;
        sPokedexScreenData->state = 2;
        break;
    case 1:
        HideBg(2);
        HideBg(1);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder; //return to previous page, i.e back to list
        sPokedexScreenData->state = 0;
        break;
    case 2:
        sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE); //draws the mon info page, false is for saying its not a mon just adding to dex from catch
        sPokedexScreenData->state = 3;
        break; 
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL); //play cry as page loads
        sPokedexScreenData->state = 4;
        break;
    case 4:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //fade in finish displaying page
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 5;//believe here is where displaying mon info page is actually complete
        break;
    case 5: //navigation from on the dex info page / ok this is a stnadin for a process input function
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            /*FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 7;*/
            sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
            sPokedexScreenData->state = 14; //going to evo page
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        else if (JOY_NEW(DPAD_UP) && DexScreen_TryScrollMonVertical(1)) //use of this function means if able to scroll in that direction
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else if (JOY_NEW(DPAD_DOWN) && DexScreen_TryScrollMonVertical(0)) //vsonic attempt use add scrolling between category dex entires
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else if (JOY_NEW(DPAD_LEFT) && DexScreen_TryDisplayForms(1)) //use of this function means if able to scroll in that direction
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 13;
        }
        else if (JOY_NEW(DPAD_RIGHT) && DexScreen_TryDisplayForms(0)) //vsonic attempt use add scrolling between category dex entires
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 13;
        } //fill in when fix //looks like all Ineed to do is change dexSPecis
        else //else here just means pressing start?
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 6:
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
        sPokedexScreenData->state = 2;
        break;
    case 7: //area page
        sPokedexScreenData->currentPage = DEX_AREA_FROM_LIST;
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state = 8;
        break;
    case 8:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 9;
        break;
    case 9:     //area page naviagation //nother stand in for process input function
        if (JOY_NEW(A_BUTTON))
        {
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 12;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            
            sPokedexScreenData->state = 16; //changed here was 10 - made universal clear
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 10:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 11;
        break;
    case 11:
        sPokedexScreenData->currentPage = DEX_INFO_FROM_LIST;
        DexScreen_DrawMonDexPage(FALSE); //same as other, Press B return from area page
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        //sPokedexScreenData->state = 14;
        sPokedexScreenData->state = 5;
        break;
    case 12:
        DexScreen_DestroyAreaScreenResources();
        FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 1;
        break;//put alt version of case 6, for form navigation below this, same just exclude dex->species setting
    case 13:
        HideBg(2); //will need set dexSpecies reassignment in new function, that loops form id table
        HideBg(1); //if dexspecies is entry 0, before reassignment, don't make left arrow,  if next entry is 0xffff don't make right arrow
        // foud this can use GET_BASE_SPECIES_ID(speciesId) can use to check if put left arrow
        sPokedexScreenData->state = 2;
        break;
    case 14: //evo page exper
         //values for dex evo page
         //wrap this in function called drawevo page, so can bring in text changes
        //has issues make new function for rather than trying to half ass it
        //FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
        //DexScreen_PrintControlInfo(gText_NextPreviousData);
        //CopyBgTilemapBufferToVram(1); //or not, hidebg isn't working here there's some kind of leak or something idk fuck I'm tired
        //ShowBg(1); //realized what these are for now, 
        //some processes are longer and will make data display before it should withoutmaking it invisible
        DexScreen_DrawMonEvoPage(FALSE);
        //gTasks[taskId].func = Task_LoadEvolutionScreen; //partially works
        sPokedexScreenData->state = 15; //put icon stat bar logic here or so
        //HideBg(2);
        //HideBg(1);//this appears to do same as fill bg, guess in different ways, proba fail safe?
        break; //think just makes invisible doesn't actually clear data?
    case 15:
    {
        UpdateStatBars(sPokedexScreenData->dexSpecies); //now creates bars nto just update
        if (JOY_NEW(A_BUTTON))//evo navigation page make down dpad craete arrow// then go to new navigation case so A B do different things
        {
            Task_SwitchScreensFromEvolutionScreen();
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 4, 30, 14);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 7;
        }
        else if (JOY_NEW(B_BUTTON))//and down and up move through evolutions
        {
            Task_SwitchScreensFromEvolutionScreen(); //might be fix I need. was going to draw evo without doign the clear
            RemoveDexPageWindows();
            sPokedexScreenData->state = 10; //this seems to be working //why am I going to 10?
        }//10 was for area page, not using anymore I should have changed
        else if (JOY_NEW(DPAD_DOWN)) //move to new case for scrolling evo methods, //up down, press b to return here, A goes to info page of that mon
        {
            //believe means if has evolution
            if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)// && sPokedexScreenData->sEvoScreenData.numSeen != 0) //this is part that prevents arrow from showing for only 1 evo/mon seen
            {
                sPokedexScreenData->sEvoScreenData.arrowSpriteId = CreateSprite(&gSpriteTemplate_Arrow, 7, 88, 0);
                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].animNum = 2;
                sPokedexScreenData->state = 18;
            }
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
    }
        break;
    case 16: //clear area page go to evo, //copy of 1o for area to avoidp break flow

            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);

        DexScreen_DestroyAreaScreenResources();
        RemoveDexPageWindows();
        sPokedexScreenData->currentPage = DEX_EVO_FROM_LIST;
        sPokedexScreenData->state = 17;
        break;
    case 17:
        DexScreen_DrawMonEvoPage(FALSE); //ok looks like its workin
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 15;
        break;
    case 18: 
    {
        u8 base_y = 88;  //only used with moving arrow sprite and sprite start value is 58,  so think thsoe need to match
        u8 base_y_offset = 9;   //that was correct
        //u8 pos = sPokedexScreenData->sEvoScreenData.menuPos;
        //u8 max = sPokedexScreenData->sEvoScreenData.numAllEvolutions;
        u16 targetSpecies = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
        
        //if not set, set, should only work first time hopefully, make sure to clear when done
        if (!(VarGet(VAR_0x408C)))
            VarSet(VAR_0x408C, sPokedexScreenData->dexSpecies);
            //store initial species page, if curr page species doesn;t equal var, set target sppecies to var
            //otherwise close
            //potentially clear var afterwards
            //start of setup to attempt track navigating between evo pages
        
        UpdateStatBars(sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos]);
        
        if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)
        {
            if (JOY_NEW(DPAD_DOWN)) //dpad on evo doesn't work right, moving up works, but moving down only works when already down
            {
                /*while (TRUE)
                {
                    pos += 1;
                    if (pos >= max)
                        pos = 0;

                    if (sPokedexScreenData->sEvoScreenData.seen[pos] == TRUE)
                        break;
                }*/
                if (sPokedexScreenData->sEvoScreenData.menuPos == sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1)
                    sPokedexScreenData->sEvoScreenData.menuPos = 0;// = sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1;
                else
                    sPokedexScreenData->sEvoScreenData.menuPos += 1;

                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].pos1.y = base_y + base_y_offset * sPokedexScreenData->sEvoScreenData.menuPos;
                targetSpecies = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
                UpdateStatBars(sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos]);
                //sPokedexScreenData->sEvoScreenData.menuPos = pos; //store end position
            }
            else if (JOY_NEW(DPAD_UP))
            {
                if (sPokedexScreenData->sEvoScreenData.menuPos == 0)
                    sPokedexScreenData->sEvoScreenData.menuPos = sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1;
                else
                    sPokedexScreenData->sEvoScreenData.menuPos -= 1;

                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].pos1.y = base_y + base_y_offset * sPokedexScreenData->sEvoScreenData.menuPos;
                targetSpecies = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
                UpdateStatBars(sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos]);
            }
        }

        
        //still bugged so for now turned off for playtest - believe fixed, issue was in destroystatbar and destroystatbarbg wasn't clearing
       if (JOY_NEW(A_BUTTON))
        {
            sPokedexScreenData->dexSpecies = targetSpecies;                

               
                //sPokedexScreenData->sEvoScreenData.fromEvoPage = TRUE;
                PlaySE(SE_SELECT);
                DestroySprite(&gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId]); //clear the arrow
                //Task_SwitchScreensFromEvolutionScreen();
                RemoveDexPageWindows();
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA); 
                Task_SwitchScreensFromEvolutionScreen();               
                sPokedexScreenData->state = 0;
                //sPokedexScreenData->state = 10;
                //sPokedexScreenData->state = 14;
                //sPokedexScreenData->state = 16;
                //BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                //gTasks[taskId].func = Task_LoadInfoScreenWaitForFade;
                //gTasks[taskId].func = Task_LoadEvolutionScreen;               

        }


        //Exit to overview
        if (JOY_NEW(B_BUTTON))
        {   //if not on initial species page you loaded into dex with, load that page
            /*if (VarGet(VAR_0x408C) != sPokedexScreenData->dexSpecies)//NationalPokedexNumToSpeciesHGSS(sPokedexListItem->dexNum))
            {
                u16 targetSpecies   = VarGet(VAR_0x408C); //load initial dex page
                u16 dexNum          = SpeciesToNationalPokedexNum(targetSpecies);
                sPokedexScreenData->dexSpecies = targetSpecies;
                //sPokedexListItem->seen   = GetSetPokedexFlag(dexNum, FLAG_GET_SEEN);
                //sPokedexListItem->owned  = GetSetPokedexFlag(dexNum, FLAG_GET_CAUGHT);

                //sPokedexScreenData->sEvoScreenData.fromEvoPage = TRUE;
                PlaySE(SE_PC_OFF); //may remove sound use
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                //gTasks[taskId].func = Task_LoadInfoScreenWaitForFade;
                Task_SwitchScreensFromEvolutionScreen();
                UpdateStatBars(VarGet(VAR_0x408C));
                sPokedexScreenData->state = 16;
                //gTasks[taskId].func = Task_LoadEvolutionScreen;
            }
            else*/
            {
                
                //BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
                //PlaySE(SE_PC_OFF);
                //Task_SwitchScreensFromEvolutionScreen();
                DestroySprite(&gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId]); //clear the arrow
                sPokedexScreenData->sEvoScreenData.menuPos = 0; //make sure arrow position reset back to 0, for when call arrows again
                VarSet(VAR_0x408C, 0);
                sPokedexScreenData->state = 15; //should hopefully clear page so doesn't build up
                //return;               //seems to work to clear resources only thing left is getting rid of the damn icon
            } //change to hopefully clear array change bar without reloading page
        } 
       
    }
    break;
    }
    
}

//left right
static bool32 DexScreen_TryDisplayForms(u8 direction)
{
    s32 i;
    u32 a = 0; //to get base form use in seen only 
    u16 seen, caught;
    u16 species = sPokedexScreenData->dexSpecies;   //is species of pokemon viewing
    u8 FormId = GetFormIdFromFormSpeciesId(species); //id in relevant table of current species
    u8 FinalFormId = GetFinalFormSpeciesId(species); //id of last form in table
    u16 FormFilter;
    u8 IsMegaPrimal = FALSE;
    u8 PassMegaChecks = FALSE;


   

    if (direction) // Seek left
    {
        if (FormId == 0)
            return FALSE;
        for (i = FormId - 1; i >= 0; i--)
        {
            //decides whether to display base form species or species form
            FormFilter = DexScreen_FormFilter(GetFormSpeciesId(species, i)); //assign based on which form displaying
            
            //seen = DexScreen_GetSetPokedexFlag(GetFormSpeciesId(species, i), FLAG_GET_SEEN, TRUE);
            //seen = DexScreen_GetSetPokedexFlag(FormFilter, FLAG_GET_SEEN, TRUE);

            /*switch (GetFormType(GetFormSpeciesId(species, i)))
            {
                case MISC_FORM:
                if (seen)
                {
                    sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                    return TRUE;
                }
                break;
                case MEGA_FORM:
                if (seen)// && check bag has ITEM_MEGA_RING
                {
                    sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                    return TRUE;
                }
                break;
                case PRIMAL_FORM:
                if (FormFilter == SPECIES_GROUDON)
                {
                    if (seen && (CheckBagHasItem(ITEM_RED_ORB, 1))) //check species groudon red orb
                    {
                        sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                        return TRUE;
                    }
                    break;
                }
                else if (FormFilter == SPECIES_KYOGRE)
                {
                    if (seen && (CheckBagHasItem(ITEM_BLUE_ORB, 1)))//check species kyogre blue orb,
                    {
                        sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                        return TRUE;
                    }
                    break;
                }
                
            }*/


                sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                return TRUE;

                
        }
        return FALSE;
    }
    else    //seek right
    {
        if (FormId == FinalFormId || gFormSpeciesIdTables[species] == NULL)
            return FALSE;

        for (i = FormId + 1; i <= FinalFormId; i++)
        {
            FormFilter = DexScreen_FormFilter(GetFormSpeciesId(species, i)); //assign based on which form displaying
            //seen = DexScreen_GetSetPokedexFlag(GetFormSpeciesId(species, i), FLAG_GET_SEEN, TRUE);
            //seen = DexScreen_GetSetPokedexFlag(FormFilter, FLAG_GET_SEEN, TRUE);
            //caught = DexScreen_GetSetPokedexFlag(GetFormSpeciesId(species, i), FLAG_GET_CAUGHT, TRUE); //seems to work makes mega visible if caught it

            /*switch (GetFormType(GetFormSpeciesId(species, i)))
            {
                case MISC_FORM:
                //if (seen)
                {
                    sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                    return TRUE;
                }
                break;
                case MEGA_FORM:
                //if ((seen && (CheckBagHasItem(ITEM_MEGA_RING, 1))) || caught)// && check bag has ITEM_MEGA_RING
                {
                    sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                    return TRUE;
                }
                break;
                case PRIMAL_FORM:
                if (FormFilter == SPECIES_GROUDON)
                {
                    //if ((seen && (CheckBagHasItem(ITEM_RED_ORB, 1))) || caught) //check species groudon red orb
                    {
                        sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                        return TRUE;
                    }
                    break;
                }
                else if (FormFilter == SPECIES_KYOGRE)
                {
                    //if ((seen && (CheckBagHasItem(ITEM_BLUE_ORB, 1))) || caught)//check species kyogre blue orb,
                    {
                        sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
                        return TRUE;
                    }
                    break;
                }
                
            }*/
           
      
            sPokedexScreenData->dexSpecies = GetFormSpeciesId(species, i);
            return TRUE;
                
        }
        return FALSE;

    }
}

//vsonic
static bool32 DexScreen_TryScrollMonVertical(u8 direction) //vsonic important think    seems equivalent of GetNextPosition but writes arguments instead of taking them
{
    int selectedIndex;
    u16 *itemsAbove_p, *cursorPos_p;

    switch (sPokedexScreenData->dexOrderId)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        cursorPos_p = &sPokedexScreenData->kantoOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->kantoOrderMenuItemsAbove;
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        cursorPos_p = &sPokedexScreenData->characteristicOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->characteristicOrderMenuItemsAbove;
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        cursorPos_p = &sPokedexScreenData->nationalOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->nationalOrderMenuItemsAbove;
        break;
    }
    
    selectedIndex = *cursorPos_p + *itemsAbove_p;
    if (direction) // Seek up   //but think this applies to both up and left, since they both go in that direction based on emerald
    {
        if (selectedIndex == 0) //ok has going up vs going down, but where is logic for the scroll from left right inputs?
            return FALSE; //ok that's all handled in list menu file, done in ListMenu_ProcessInput function


        //if (selectedIndex >= 10) //oh realized I can do more, since it scrolls fast now
        //this doesn't need to be as large, if I'm going up I've already been there,
        //so its alreadybeen loaded
            DexScreen_LoadIndex(50 + 1, SCROLL_UP, selectedIndex, 1); //works
        //selectedIndex--;
        while (--selectedIndex >= 0) //Should be while (--selectedIndex >= 0) without the selectedIndex-- in the body or before the while at all, but this is needed to match.
        {
            
            if ((sPokedexScreenData->listItems[selectedIndex].index >> 16) & 1)
            {
                break;
            }
            //selectedIndex--;
        }

        if (selectedIndex < 0)
        {
            return FALSE;
        }
    }
    else // Seek down
    {
        if (selectedIndex == sPokedexScreenData->orderedDexCount - 1)
        {
            return FALSE;
        }
        // depending on where you are compared to the limit of the dex
        //meaning if you're scrolling the full range without hittnig a limit
        //it gets kind of slow, and since I want game to be fast unless
        //I can somehow shorten the actual fade in fade out time, (which I THINK is possible)
        //then i would need to lower the number to cut the processing load
        //nvm I need to lower the range, the process goes before the fade 
        //so the fade would be delayed regardless of shortening it,
        //(255, SCROLL_DOWN, selectedIndex, 1);//discovered issue when scroll on entry need value large enough to cover blank entries or wont' scroll
        //ok bounds hold, seems works without issue, huh even with the far larger value, it doesn't add to load time, nice :D
        //ok this is good enough, nvm tested w full dex and its much slower
        //when having to navigate filled values and can't just write blank entries

        //I feel like there's a better way to do this than just loading every entry from where I am to the next non blank value?
        //like if I could seen dex flags and go to the next seen one and then just load
        //the tiles around me? enough to  see a full page should I exit from there
        /*potentially make new function?
        rather than increment by 1 and load based on a count
        can loop from index, stop when encounter next seen value assign to Nextseen
        and make increment Nextseen - index?
        make that curr index and then think do like create list and build page around me at 13 values,
        well however the bottom works*/
        DexScreen_LoadIndex(102, SCROLL_DOWN, selectedIndex, 1);//only slows if i need to go full length, load time is based on distance to next value

        while (++selectedIndex < sPokedexScreenData->orderedDexCount)
        {            

            if ((sPokedexScreenData->listItems[selectedIndex].index >> 16) & 1) //I think should put the dpad loads within these loops?
                break; //<< 16 is seen, believe << 17 is caught, confirmed
        }
        if (selectedIndex >= sPokedexScreenData->orderedDexCount)
        {
            return FALSE;
        }
    }
    sPokedexScreenData->characteristicMenuInput = sPokedexScreenData->listItems[selectedIndex].index; //the mon you're on

    // as this part is CLEARLY only for being read on a list, hmm but removing it ONLY removed ability to scroll dex entries..
    //this is translating cursor position on list with where you are since you've moving "above" it in the info pages
    if (sPokedexScreenData->orderedDexCount > sListMenuTemplate_OrderedListMenu.maxShowed)//if can scroll, and total list longer than max shown
    {
        if (selectedIndex < 4) //both instances of 4, mean to scroll vertically when would be within 4 spaces/rows of max shown from either top or bottom
        {
            *cursorPos_p = 0;
            *itemsAbove_p = selectedIndex;
        }
        else if (selectedIndex >= (sPokedexScreenData->orderedDexCount - 4)) //if can scroll i.e is not 4 away from end of list
        {
            *cursorPos_p = (sPokedexScreenData->orderedDexCount - sListMenuTemplate_OrderedListMenu.maxShowed);
            *itemsAbove_p = selectedIndex + sListMenuTemplate_OrderedListMenu.maxShowed - (sPokedexScreenData->orderedDexCount);
        }
        else
        {
            *cursorPos_p = selectedIndex - 4;
            *itemsAbove_p = 4;
        } 
    } 
    else
    {
        *cursorPos_p = 0;
        *itemsAbove_p = selectedIndex;
    }
    return TRUE;
}

static s32 DexScreen_ProcessInput(u8 listTaskId)//replaced listmenu process input
{
    
    struct ListMenu *list = (struct ListMenu *)gTasks[listTaskId].data;
    struct ListMenuTemplate template;

    u32 selectedIndex = list->cursorPos + list->itemsAbove;

    if (JOY_NEW(A_BUTTON))
    {
        return list->template.items[list->cursorPos + list->itemsAbove].index;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        return LIST_CANCEL;
    }
    else if (gMain.newAndRepeatedKeys & DPAD_UP)
    {

        DexScreen_LoadIndex(list->template.maxShowed, SCROLL_UP, selectedIndex, 1);
        ListMenuChangeSelection(list, TRUE, 1, FALSE, DEX_LIST_MODE); 
        return LIST_NOTHING_CHOSEN;
    }
    else if (gMain.newAndRepeatedKeys & DPAD_DOWN)
    {

        DexScreen_LoadIndex(list->template.maxShowed, SCROLL_DOWN, selectedIndex, 1);
        ListMenuChangeSelection(list, TRUE, 1, TRUE, DEX_LIST_MODE);
        return LIST_NOTHING_CHOSEN;
    }
    else // try to move by one window scroll
    {
        bool16 rightButton, leftButton;
        switch (list->template.scrollMultiple)
        {
        case LIST_NO_MULTIPLE_SCROLL:
        default:
            leftButton = FALSE;
            rightButton = FALSE;
            break;
        case LIST_MULTIPLE_SCROLL_DPAD:
            leftButton = gMain.newAndRepeatedKeys & DPAD_LEFT;
            rightButton = gMain.newAndRepeatedKeys & DPAD_RIGHT;
            break;
        case LIST_MULTIPLE_SCROLL_L_R:
            leftButton = gMain.newAndRepeatedKeys & L_BUTTON;
            rightButton = gMain.newAndRepeatedKeys & R_BUTTON;
            break;
        }
        if (leftButton)
        {
            
            DexScreen_LoadIndex(13, SCROLL_UP, selectedIndex, list->template.maxShowed);
            ListMenuChangeSelection(list, TRUE, list->template.maxShowed, FALSE, DEX_LIST_MODE); 
            return LIST_NOTHING_CHOSEN;
        }
        else if (rightButton)
        {
            DexScreen_LoadIndex(13, SCROLL_DOWN, selectedIndex, list->template.maxShowed); //14 / or 13 to cover where scroll, so always full window //works
            ListMenuChangeSelection(list, TRUE, list->template.maxShowed, TRUE, DEX_LIST_MODE);
            return LIST_NOTHING_CHOSEN;
        }
        else
        {
            return LIST_NOTHING_CHOSEN;
        }
    }
}

static void DexScreen_RemoveWindow(u8 *windowId_p)
{
    if (*windowId_p != 0xFF)
    {
        RemoveWindow(*windowId_p);
        *windowId_p = 0xFF;
    }
}

static void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx)
{
    u8 textColor[3];
    switch (colorIdx)
    {
    case 0:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 3;
        break;
    case 1:
        textColor[0] = 0;
        textColor[1] = 5;
        textColor[2] = 1;
        break;
    case 2:
        textColor[0] = 0;
        textColor[1] = 15;
        textColor[2] = 14;
        break;
    case 3:
        textColor[0] = 0;
        textColor[1] = 11;
        textColor[2] = 1;
        break;
    case 4:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 2;
        break;
    }
    AddTextPrinterParameterized4(windowId, fontId, x, y, 0, 0, textColor, -1, str);
    //AddTextPrinterParameterized4(windowId, fontId, x, y, fontId == FONT_SMALL ? 0 : 1, 0, textColor, -1, str);
}

static void DexScreen_DexNumAddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx)
{
    u8 textColor[3];
    switch (colorIdx)
    {
    case 0:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 3;
        break;
    case 1:
        textColor[0] = 0;
        textColor[1] = 5;
        textColor[2] = 1;
        break;
    case 2:
        textColor[0] = 0;
        textColor[1] = 15;
        textColor[2] = 14;
        break;
    case 3:
        textColor[0] = 0;
        textColor[1] = 11;
        textColor[2] = 1;
        break;
    case 4:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 2;
        break;
    }
    AddTextPrinterParameterized4(windowId, fontId, x, y, 1, 0, textColor, -1, str);
    //AddTextPrinterParameterized4(windowId, fontId, x, y, fontId == FONT_SMALL ? 0 : 1, 0, textColor, -1, str);
}

//used only in this functinon so can make alternate logic/potentially rename
static void DexScreen_PrintNum3LeadingZeroes(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
{

    u8 buff[5];
    u8 MaxDigits = num <= 999 ? 3 : 4;
    
    ConvertIntToDecimalStringN(buff, num, STR_CONV_MODE_LEADING_ZEROS, MaxDigits);

    DexScreen_AddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
}

static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
{
    u8 buff[5];
    u8 MaxDigits = num <= 999 ? 3 : 4;
    
    ConvertIntToDecimalStringN(buff, num, STR_CONV_MODE_RIGHT_ALIGN, MaxDigits); //surprsingly works
    if (MaxDigits == 3)
        DexScreen_AddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
    else
        DexScreen_DexNumAddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
}//works w this, keeps default spacing until hits 4 digits and actually needs it for readability

static u32 DexScreen_GetDefaultPersonality(int species)
{
    switch (species)
    {
    case SPECIES_SPINDA:
        return gSaveBlock2Ptr->pokedex.spindaPersonality;
    case SPECIES_UNOWN:
        return gSaveBlock2Ptr->pokedex.unownPersonality;
    default:
        return 0;
    }
}

//all need is use dexSPecies for argument
static void DexScreen_LoadMonPicInWindow(u8 windowId, u16 species, u16 paletteOffset, bool8 LoadMonPalette)
{
    LoadMonPicInWindow(species, SHINY_ODDS, DexScreen_GetDefaultPersonality(species), TRUE, paletteOffset >> 4, windowId, LoadMonPalette);
}

//use getbase form for this, make if species greater than, nat species count, assign species to base form id
//vsonic then do same for ht wt etc.
static void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y)
{
    u16 dexNum;

        if (species > NATIONAL_SPECIES_COUNT)
            species = GetFormSpeciesId(species, 0); //returns base form species, and num, w/o changing dexspecis
    dexNum = SpeciesToNationalPokedexNum(species);
    DexScreen_AddTextPrinterParameterized(windowId, fontId, gText_PokedexNo, x, y, 0);//NO symbol
    DexScreen_PrintNum3LeadingZeroes(windowId, fontId, dexNum, x + 9, y, 0);//actual space/ammount of numbers
}//3 appears to refer to number of zeroes, not function number  //is num for dex page

s8 DexScreen_GetSetPokedexFlag(u16 nationalDexNo, u8 caseId, bool8 indexIsSpecies)
{
    u8 index;
    u8 bit;
    u8 mask;
    s8 retVal;

    if (indexIsSpecies)
        nationalDexNo = SpeciesToNationalPokedexNum(nationalDexNo);

    nationalDexNo--;
    index = nationalDexNo / 8;
    bit = nationalDexNo % 8;
    mask = 1 << bit;
    retVal = 0;
    switch (caseId)
    {
    case FLAG_GET_SEEN:
        if (gSaveBlock2Ptr->pokedex.seen[index] & mask)
        {
            // Anticheat
            if ((gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_GET_CAUGHT:
        if (gSaveBlock2Ptr->pokedex.owned[index] & mask)
        {
            // Anticheat
            if ((gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock2Ptr->pokedex.seen[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_SET_SEEN:
        gSaveBlock2Ptr->pokedex.seen[index] |= mask;
        // Anticheat
        gSaveBlock1Ptr->seen1[index] |= mask;
        gSaveBlock1Ptr->seen2[index] |= mask;
        break;
    case FLAG_SET_CAUGHT:
        gSaveBlock2Ptr->pokedex.owned[index] |= mask;
        break;
    }
    return retVal;
    //return 1;   //dex test value  //other in event_data.c IsNationalPokedexEnabled function
} //for some reason navigation only works with my dex test breaks, without them everything gets fucked so EVEN MORE FUCKING WORK

static u16 DexScreen_GetDexCount(u8 caseId, bool8 whichDex) //vsonic IMPORTANT, right now have more nat dex species values than I actually have array spots or dex entries
{
    u16 count = 0;
    u16 i;

    switch (whichDex)
    {
    case 0: // Kanto
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))  //for seen amount but doesnt make appear in dex
                count++;
        }
        break;
    case 1: // National
        for (i = 0; i < NATIONAL_SPECIES_COUNT; i++) //so same as other places can't use NATIONAL_DEX_COUNT for this rn, to use nat count, need update search arrays, and add entry data
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))//changed back only reason this was issue was I was using numseen as size, which used this
                count++;

        }
        break; //changed from NATIONAL_DEX_COUNT
    }
    return count;
}

static void DexScreen_PrintControlInfo(const u8 *src)
{
    DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, src, 236 - GetStringWidth(FONT_SMALL, src, 0), 2, 4);
}

bool8 DexScreen_DrawMonPicInCategoryPage(u16 species, u8 slot, u8 numSlots)
{
    struct WindowTemplate template;
    numSlots--;
    CopyToBgTilemapBufferRect_ChangePalette(3, sCategoryPageIconWindowBg, sCategoryPageIconCoords[numSlots][slot][0], sCategoryPageIconCoords[numSlots][slot][1], 8, 8, slot + 5);
    if (sPokedexScreenData->categoryMonWindowIds[slot] == 0xFF)
    {
        template = sWindowTemplate_CategoryMonIcon;
        template.tilemapLeft = sCategoryPageIconCoords[numSlots][slot][0];
        template.tilemapTop = sCategoryPageIconCoords[numSlots][slot][1];
        template.paletteNum = slot + 1;
        template.baseBlock = slot * 64 + 8;
        sPokedexScreenData->categoryMonWindowIds[slot] = AddWindow(&template);
        FillWindowPixelBuffer(sPokedexScreenData->categoryMonWindowIds[slot], PIXEL_FILL(0));
        DexScreen_LoadMonPicInWindow(sPokedexScreenData->categoryMonWindowIds[slot], species, slot * 16 + 16, TRUE);
        PutWindowTilemap(sPokedexScreenData->categoryMonWindowIds[slot]);
        CopyWindowToVram(sPokedexScreenData->categoryMonWindowIds[slot], COPYWIN_GFX);
    }
    else
        PutWindowTilemap(sPokedexScreenData->categoryMonWindowIds[slot]);

    if (sPokedexScreenData->categoryMonInfoWindowIds[slot] == 0xFF)
    {
        if (species != SPECIES_NONE)
        {
            template = sWindowTemplate_CategoryMonInfo;
            template.tilemapLeft = sCategoryPageIconCoords[numSlots][slot][2];
            template.tilemapTop = sCategoryPageIconCoords[numSlots][slot][3];
            template.baseBlock = slot * 40 + 0x108;
            sPokedexScreenData->categoryMonInfoWindowIds[slot] = AddWindow(&template);
            CopyToWindowPixelBuffer(sPokedexScreenData->categoryMonInfoWindowIds[slot], sCategoryMonInfoBgTiles, 0, 0);
            DexScreen_PrintMonDexNo(sPokedexScreenData->categoryMonInfoWindowIds[slot], FONT_SMALL, species, 12, 0);
            
            GetSpeciesName(gStringVar1, species); 
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->categoryMonInfoWindowIds[slot], FONT_NORMAL, gStringVar1, 2, 13, 0);

            if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE))
                BlitBitmapRectToWindow(sPokedexScreenData->categoryMonInfoWindowIds[slot], sDexScreen_CaughtIcon, 0, 0, 8, 8, 2, 3, 8, 8);
            PutWindowTilemap(sPokedexScreenData->categoryMonInfoWindowIds[slot]);
            CopyWindowToVram(sPokedexScreenData->categoryMonInfoWindowIds[slot], COPYWIN_GFX);
        }
    }
    else
        PutWindowTilemap(sPokedexScreenData->categoryMonInfoWindowIds[slot]);

    return TRUE;
}

static void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonWindowIds[i]);
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonInfoWindowIds[i]);
    }
}

static void DexScreen_PrintCategoryPageNumbers(u8 windowId, u16 currentPage, u16 totalPages, u16 x, u16 y)
{
    u8 buffer[30];
    u8 *ptr = StringCopy(buffer, gText_Page);
    ptr = ConvertIntToDecimalStringN(ptr, currentPage, STR_CONV_MODE_RIGHT_ALIGN, 2);
    *ptr++ = CHAR_SLASH;
    ptr = ConvertIntToDecimalStringN(ptr, totalPages, STR_CONV_MODE_RIGHT_ALIGN, 2);
    DexScreen_PrintStringWithAlignment(buffer, TEXT_RIGHT);
}

static bool8 DexScreen_CreateCategoryListGfx(bool8 justRegistered)
{
    FillBgTilemapBufferRect_Palette0(3, 2, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 32, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
    DexScreen_CreateCategoryPageSpeciesList(sPokedexScreenData->category, sPokedexScreenData->pageNum);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    if (justRegistered)
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], TEXT_CENTER);
    }
    else
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], TEXT_LEFT);
        DexScreen_PrintCategoryPageNumbers(0, DexScreen_PageNumberToRenderablePages(sPokedexScreenData->pageNum), DexScreen_PageNumberToRenderablePages(sPokedexScreenData->lastPageInCategory - 1), 160, 2);
    }
    CopyWindowToVram(0, COPYWIN_GFX);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    if (!justRegistered)
        DexScreen_PrintControlInfo(gText_PickFlipPageCheckCancel);
    CopyWindowToVram(1, COPYWIN_GFX);

    if (justRegistered) //to override pulling species from an existing cat page
    {
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->dexSpecies, 0, 1);   //WORKS!!!

    }//slot needs to be 0
        
    if (!justRegistered)
    {
    if (sPokedexScreenData->pageSpecies[0] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[0], 0, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[1] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[1], 1, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[2] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[2], 2, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[3] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[3], 3, sPokedexScreenData->numMonsOnPage);
    }
    return FALSE;
}

static void DexScreen_CreateCategoryPageSelectionCursor(u8 cursorPos)
{
    int i;
    u32 palIdx;

    if (cursorPos == 0xFF)
    {
        for (i = 0; i < 4; i++)
        {
            LoadPalette(&sDexScreen_CategoryCursorPals[0], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));   //LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x52 + 0x10 * i, 2);
            LoadPalette(&sDexScreen_CategoryCursorPals[1], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));   //LoadPalette(&sDexScreen_CategoryCursorPals[1], 0x58 + 0x10 * i, 2);
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x141, PLTT_SIZEOF(1));
        sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
    }
    else
    {
        sPokedexScreenData->categoryPageSelectionCursorTimer++;
        if (sPokedexScreenData->categoryPageSelectionCursorTimer == 16)
            sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
        palIdx = sPokedexScreenData->categoryPageSelectionCursorTimer >> 2;
        for (i = 0; i < 4; i++)
        {
            if (i == cursorPos)
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 2], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 3], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            }
            else
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[0], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
                LoadPalette(&sDexScreen_CategoryCursorPals[1], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            }
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 2], OBJ_PLTT_ID(4) + 1, PLTT_SIZEOF(1));
    }
}

static void DexScreen_UpdateCategoryPageCursorObject(u8 taskId, u8 cursorPos, u8 numMonsInPage)
{
    numMonsInPage--;
    ListMenuUpdateCursorObject(taskId, sCategoryPageIconCoords[numMonsInPage][cursorPos][2] * 8, sCategoryPageIconCoords[numMonsInPage][cursorPos][3] * 8, 0);
}

bool8 DexPage_TileBuffer_CopyCol(const u16 *srcBuf, u8 srcCol, u16 *dstBuf, u8 dstCol)
{
    int i;
    const u16 *src = &srcBuf[srcCol];
    u16 *dst = &dstBuf[dstCol];
    for (i = 0; i < 20; i++)
    {
        *dst = *src;
        dst += 32;
        src += 32;
    }
    return FALSE;
}

bool8 DexPage_TileBuffer_FillCol(u16 tileNo, u16 *tileBuf, u8 x)
{
    int i;
    u16 *dst = &tileBuf[x];
    for (i = 0; i < 20; i++)
    {
        *dst = tileNo;
        dst += 32;
    }
    return FALSE;
}

bool8 DexScreen_TurnCategoryPage_BgEffect(u8 page)
{
    int dstCol;
    int srcCol;
    u16 *bg1buff = GetBgTilemapBuffer(1);
    u16 *bg2buff = GetBgTilemapBuffer(2);
    u16 *bg3buff = GetBgTilemapBuffer(3);
    u16 *bg1mem = sPokedexScreenData->bgBufsMem + 0x800;
    u16 *bg2mem = sPokedexScreenData->bgBufsMem + 0x400;
    u16 *bg3mem = sPokedexScreenData->bgBufsMem + 0x000;
    for (dstCol = 0; dstCol < 30; dstCol++)
    {
        srcCol = sDexScreenPageTurnColumns[page][dstCol];
        if (srcCol == 30)
        {
            DexPage_TileBuffer_FillCol(0x000, bg1buff, dstCol);
            DexPage_TileBuffer_FillCol(0x000, bg2buff, dstCol);
            DexPage_TileBuffer_FillCol(0x00C, bg3buff, dstCol);
        }
        else
        {
            DexPage_TileBuffer_CopyCol(bg1mem, srcCol, bg1buff, dstCol);
            DexPage_TileBuffer_CopyCol(bg2mem, srcCol, bg2buff, dstCol);
            DexPage_TileBuffer_CopyCol(bg3mem, srcCol, bg3buff, dstCol);
        }
    }
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(2);
    CopyBgTilemapBufferToVram(3);
    return FALSE;
}

/*
 * Direction = 0: Left; 1: Right
 */
static bool8 DexScreen_FlipCategoryPageInDirection(u8 direction)
{
    u16 color;
    if (IsNationalPokedexEnabled())
        color = sNationalDexPalette[7];
    else
        color = sKantoDexPalette[7];
    switch (sPokedexScreenData->data[0])
    {
    case 0:
        sPokedexScreenData->bgBufsMem = Alloc(3 * BG_SCREEN_SIZE);
        if (direction)
            sPokedexScreenData->data[0] = 6;
        else
            sPokedexScreenData->data[0] = 2;
        break;
    case 1:
        Free(sPokedexScreenData->bgBufsMem);
        return TRUE;
        // Go left
    case 2:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 16, color);
        sPokedexScreenData->data[0]++;
        break;
    case 3:
        FillBgTilemapBufferRect_Palette0(3, 0x00C, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 32, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sPokedexScreenData->data[0]++;
        break;
    case 4:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 0, color);
        DexScreen_CreateCategoryListGfx(FALSE);
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->bgBufsMem[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->bgBufsMem[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->bgBufsMem[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        FillBgTilemapBufferRect_Palette0(3, 0x00C, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 32, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);

        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 5:
        if (sPokedexScreenData->data[1] < 10)
        {
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]++;
        }
        else
        {
            sPokedexScreenData->data[0] = 1;
        }
        break;
        // Go right
    case 6:
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->bgBufsMem[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->bgBufsMem[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->bgBufsMem[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);

        sPokedexScreenData->data[1] = 9;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 7:
        if (sPokedexScreenData->data[1] != 0)
        {
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]--;
        }
        else
        {
#ifdef BUGFIX
            DexScreen_TurnCategoryPage_BgEffect(0);
#else
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[0]);
#endif
            BeginNormalPaletteFade(0x00007FFF, 0, 16, 16, color);
            sPokedexScreenData->data[0]++;
        }
        break;
    case 8:
        gPaletteFade.bufferTransferDisabled = TRUE;
        DexScreen_CreateCategoryListGfx(FALSE);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sPokedexScreenData->data[0]++;
        break;
    case 9:
        gPaletteFade.bufferTransferDisabled = FALSE;
        BeginNormalPaletteFade(0x00007FFF, 0, 16, 0, color);
        sPokedexScreenData->data[0] = 1;
        break;
    }
    return FALSE;
}

#define POKEDEX_PAGE_FUNCTIONS
// Scale from 0 to 6
void DexScreen_DexPageZoomEffectFrame(u8 bg, u8 scale)
{
    u8 tileLeft, tileTop, width, height;
    s16 left, top, divY;

    if (!sPokedexScreenData->numMonsOnPage)
    {
        tileLeft = sCategoryPageIconCoords[0][0][2];
        tileTop = sCategoryPageIconCoords[0][0][3];
    }
    else
    {
        tileLeft = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->categoryCursorPosInPage][2];
        tileTop = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->categoryCursorPosInPage][3];
    }

    width = 6 + (scale * 4);
    height = 3 + (scale * 2);
    if (width >= 28) // Make sure it's not wider than the screen
        width = 28;
    if (height >= 14) // Make sure it's not taller than the screen
        height = 14;

    left = tileLeft - ((scale * 4) / 2);
    top = tileTop - ((scale * 2) / 2);
    if ((left + width + 2) >= 30) // Don't wrap right...
        left -= ((left + width + 2) - 30);
    else if (left < 0) // ... left ...
        left = 0;
    if ((top + height + 2) >= 18) // ... down ...
        top -= ((top + height + 2) - 18);
    else if (top < 2) // or up.
        top = 2;

    //either adjust this or height value
    divY = (top + 1) + ((height / 2) - 1);// The horizontal divider    //this determines space for dex entries/ this was my change to give more room for text space
            //to keep dividing line where it is,  changes to tilemap top, must be contrasted by double the change by height, in the opposite
            //i.e if I decrease top by 1 I must increase height by 2
    // Top edge
    FillBgTilemapBufferRect_Palette0(bg, 4, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 5, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(4), left + 1 + width, top, 1, 1);

    // Bottom edge
    FillBgTilemapBufferRect_Palette0(bg, 10, left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 11, left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(10), left + 1 + width, top + 1 + height, 1, 1);

    // Left edge
    FillBgTilemapBufferRect_Palette0(bg, 6, left, top + 1, 1, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, 7, left, divY, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 9, left, divY + 1, 1, top + height - divY);

    // Right edge
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(6), left + 1 + width, top + 1, 1, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(7), left + 1 + width, divY, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(9), left + 1 + width, divY + 1, 1, top + height - divY);

    // Interior
    FillBgTilemapBufferRect_Palette0(bg, 1, left + 1, top + 1, width, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, 8, left + 1, divY, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, 2, left + 1, divY + 1, width, top + height - divY);
}

void DexScreen_PrintMonCategory(u8 windowId, u16 species, u8 x, u8 y)
{
    u8 * categoryName; //ok works now
    u8 index;
    u32 i;
    u8 categoryStr[13];//changed from 12 - issue was this, wasn't defined right, needed  be separate
    u16 speciesArgument;
    u16 FormSpecies;
    bool8 UniqueCategory = FALSE;
    //bool8 UseBaseForm = FALSE;
    u16 NatSpecies = SpeciesToNationalPokedexNum(species);
    u16 caught = DoesSpeciesHaveCosmeticForms(species) ? DexScreen_GetSetPokedexFlag(GetFormSpeciesId(species, 0), FLAG_GET_CAUGHT, TRUE) :  DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE);


    //plan make  gen9 defualt to 0 so dex entries load, instead of causing freeze for empty data
    //species = (species <= NATIONAL_SPECIES_COUNT && species > SPECIES_ENAMORUS_INCARNATE) ? SPECIES_NONE : SpeciesToNationalPokedexNum(species);
    //can use ternary operator or just a conditional assignment
    //yeah prob better to do conditional assignment
    //to pass off whether it'll check if you've caught the 
    //base species or the form species will replace 
    //use of sPokedexScreenData->dexSpecies

    //if I can return the species argument from
    //gFormChangeTablePointers that would be a good split
    //for if the specie is a temp form or permanent form.
    //as that is used for species that change forms in battle
    

    //if mega use base form for catch otherwise use dex species
    if (species > NATIONAL_SPECIES_COUNT
    && gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION)
    {
        FormSpecies = GetFormSpeciesId(species, 0);
    }
    else
        FormSpecies = species; //already uses dex->species

    
    
    //check for forms that actually have different cat from base forms
    for (i = 0; i < NELEMS(gdexCatFormSpecies); i++) //only the cat names I need change
    {
        if (NatSpecies > NATIONAL_SPECIES_COUNT) 
        {
            if (NatSpecies == gdexCatFormSpecies[i])
            {
                UniqueCategory = TRUE;
                break;
            }
            
        }
        
    }

    if (UniqueCategory == TRUE)
    {
        categoryName = (u8 *)gFormdexCategoryName[NatSpecies].categoryName;
    }
    else
    {
        ////put and not on gen9 exclusion list right here, w if
        //if on list set species argument to species, if not on list do below
        //way it worked would just pass species if didnt have form
        //since gen9 is a form but has data in gPokedexEntries need explicitly pass species
        if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START)
            speciesArgument = GetFormSpeciesId(species, 0);
        else
            speciesArgument = species;
        
        if (gPokedexEntries[NatSpecies].categoryName[0] == 0)
            speciesArgument = GetFormSpeciesId(species, 0);

        speciesArgument = SpeciesToNationalPokedexNum(speciesArgument);
        categoryName = (u8 *)gPokedexEntries[speciesArgument].categoryName;
    }
               
    
    
    
    /*for (i = 0; i < NELEMS(gdexEntryFormSpecies); i++) //only the cat names I need change
    {
        if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START)
        {
            if (species == gdexEntryFormSpecies[i])
            {
                UseBaseForm = TRUE;
                break;
            }
            
        }
        
    }

    //if specis is on list use the base form to decide if should display 
    //put this in display form as well
    //still need go over array values to clean up

    //try sepaaret from use of i, in case some issue, well that fixed it suprisingly
    if (UseBaseForm == TRUE)
        speciesFilter = GetFormSpeciesId(species, 0);
    else
        speciesFilter = sPokedexScreenData->dexSpecies;*/

        

    index = 0;

    //think need change DexScreen_FormFilter back to bool
    // then can have two diff versions of below condition
    

    //think may need change this, since not all forms are permanent, keep in mind and find answer later
    //current issue is override for dex category isn't working anymore, 
    //vsonic 
    //change to work if form species, or species, plan specifically to let catching megas still display correftly
    if (DexScreen_GetSetPokedexFlag(FormSpecies, FLAG_GET_CAUGHT, TRUE) || caught)    
    {
        //#if REVISION == 0
        //       while ((categoryName[index] != CHAR_SPACE) && (index <= 13)) //potentially this is issue, need raise this
        //#else
        while ((categoryName[index] != EOS) && (index <= 13)) //ok realized issue, above code is wrong, breaks line as soon as encounter space, replace with eos
        //#endif
        {
            categoryStr[index] = categoryName[index];
            index++;
        }
    }
    else
    {
        while (index < 11) //if this is length, this is just about filling blanks, so can leave as is
        {
            categoryStr[index] = CHAR_QUESTION_MARK;
            index++;
        }
    }

    categoryStr[index] = EOS;

    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, categoryStr, x, y, 0);
    x += GetStringWidth(FONT_SMALL, categoryStr, 0);
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, gText_PokedexPokemon, x, y, 0);
}

void DexScreen_PrintMonHeight(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 height;
    u32 inches, feet;
    const u8 *labelText;
    u8 buffer[32];
    u8 i;
    u16 FormSpecies;
    u16 caught = DoesSpeciesHaveCosmeticForms(sPokedexScreenData->dexSpecies) ? DexScreen_GetSetPokedexFlag(GetFormSpeciesId(sPokedexScreenData->dexSpecies, 0), FLAG_GET_CAUGHT, TRUE) :  DexScreen_GetSetPokedexFlag(sPokedexScreenData->dexSpecies, FLAG_GET_CAUGHT, TRUE);


    if (species > NATIONAL_SPECIES_COUNT
    && gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION)
    {
        FormSpecies = GetFormSpeciesId(species, 0);
    }
    else
        FormSpecies = species; //already uses dex->species

    

    
    if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START)//put and not on gen9 exclusion list
        species = GetFormSpeciesId(species, 0);

    if (gPokedexEntries[SpeciesToNationalPokedexNum(species)].height == 0)
        species = GetFormSpeciesId(species, 0);

    //plan make  gen9 defualt to 0 so dex entries load, instead of causing freeze for empty data
    //species = (species <= NATIONAL_SPECIES_COUNT && species > SPECIES_ENAMORUS_INCARNATE) ? SPECIES_NONE : SpeciesToNationalPokedexNum(species);
    species = SpeciesToNationalPokedexNum(species);

    height = gPokedexEntries[species].height;

    labelText = gText_HT;

    if (sPokedexScreenData->dexSpecies == SPECIES_MEWTWO_MEGA_Y)
        height = gPokedexEntries[species].height / 3;

    

    i = 0;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 0;
    buffer[i++] = CHAR_SPACE;

    if (DexScreen_GetSetPokedexFlag(FormSpecies, FLAG_GET_CAUGHT, TRUE) || caught) //this needs to use source value nto species
    {
        inches = 10000 * height / 254; // actually tenths of inches here
        if (inches % 10 >= 5)
            inches += 10;
        feet = inches / 120;
        inches = (inches - (feet * 120)) / 10;
        if (feet / 10 == 0)
        {
            buffer[i++] = 0;
            buffer[i++] = feet + CHAR_0;
        }
        else
        {
            buffer[i++] = feet / 10 + CHAR_0;
            buffer[i++] = feet % 10 + CHAR_0;
        }
        buffer[i++] = CHAR_SGL_QUOTE_RIGHT;
        buffer[i++] = inches / 10 + CHAR_0;
        buffer[i++] = inches % 10 + CHAR_0;
        buffer[i++] = CHAR_DBL_QUOTE_RIGHT;
        buffer[i++] = EOS;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_SGL_QUOTE_RIGHT;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_DBL_QUOTE_RIGHT;
    }

    buffer[i++] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelText, x, y, 0);
    x += 10;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, buffer, x, y, 0);
}

void DexScreen_PrintMonWeight(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 weight;
    u32 lbs;
    bool8 output;
    const u8 * labelText;
    const u8 * lbsText;
    u8 buffer[32];
    u8 i;
    u32 j;
    u16 FormSpecies;
    u16 caught = DoesSpeciesHaveCosmeticForms(sPokedexScreenData->dexSpecies) ? DexScreen_GetSetPokedexFlag(GetFormSpeciesId(sPokedexScreenData->dexSpecies, 0), FLAG_GET_CAUGHT, TRUE) :  DexScreen_GetSetPokedexFlag(sPokedexScreenData->dexSpecies, FLAG_GET_CAUGHT, TRUE);

    //says national_species_count but actually uses species list to define
    //not national species list
    //make list of exclusions, like I did for pic height
    //just need to exclude the gen 9 form mon
    if (species > NATIONAL_SPECIES_COUNT 
    && gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION)
    {
        FormSpecies = GetFormSpeciesId(species, 0);
    }
    else
        FormSpecies = species; //already uses dex->species

    if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START) //put and not on gen9 exclusion list
        species = GetFormSpeciesId(species, 0);

    if (gPokedexEntries[SpeciesToNationalPokedexNum(species)].weight == 0)
        species = GetFormSpeciesId(species, 0);

    //plan make  gen9 defualt to 0 so dex entries load, instead of causing freeze for empty data
    //species = (species <= NATIONAL_SPECIES_COUNT && species > SPECIES_ENAMORUS_INCARNATE) ? SPECIES_NONE : SpeciesToNationalPokedexNum(species);

    species = SpeciesToNationalPokedexNum(species);

    weight = gPokedexEntries[species].weight;
    labelText = gText_WT;
    lbsText = gText_Lbs;

    if (sPokedexScreenData->dexSpecies == SPECIES_MEWTWO_MEGA_Y)
        weight = gPokedexEntries[species].weight / 13;

    i = 0;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 0;

    //realized don't need formspecies for thsi dexspecies is best since you've already caught it to trigger this
    //what I need is for catching a form to make the base form seen so you're able to navigate to form page in dex.
    //actually do need formspecies filter, but not for gender species, I could say only mega form and primal reversion use bsae form species
    //along w exclusion for ash gren and zen_mode mon, but that still leaves issue of randomizers, or when you'd actually catch those mon directly
    //nvm ash gren is already accounted for it leads to nat dex gren, so itll be fine, so I just need to worry bout megas
    //if (DexScreen_GetSetPokedexFlag(FormSpecies, FLAG_GET_CAUGHT, TRUE))//prints weight only if current species cuaght, issue is with megas can fix use constant
    //nvm fixed w use of or
    if (DexScreen_GetSetPokedexFlag(FormSpecies, FLAG_GET_CAUGHT, TRUE) || caught)
    {
        lbs = (weight * 100000) / 4536; // Convert to hundredths of lb

        // Round up to the nearest 0.1 lb
        if (lbs % 10 >= 5)
            lbs += 10;

        output = FALSE;

        if ((buffer[i] = (lbs / 100000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 100000;
        if ((buffer[i] = (lbs / 10000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 10000;
        if ((buffer[i] = (lbs / 1000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 1000;
        buffer[i++] = (lbs / 100) + CHAR_0;
        lbs %= 100;
        buffer[i++] = CHAR_PERIOD;
        buffer[i++] = (lbs / 10) + CHAR_0;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_PERIOD;
        buffer[i++] = CHAR_QUESTION_MARK;
    }
    buffer[i++] = CHAR_SPACE;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 0;

    for (j = 0; j < 33 - i && lbsText[j] != EOS; j++)
        buffer[i + j] = lbsText[j];

    buffer[i + j] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelText, x, y, 0);
    x += 10;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, buffer, x, y, 0);
}

//gText_StatTotal
//no way to take on to existing page cleanly,
//instead press Select to make clear page info/top half
//of everything except dexnum and species name
//to clear space for displaying stats
//thoughts now that dex is more relevant 
//could potentially make battle callback that will go to dex mon info page
//mid battle and then return, just like a real trainer checking the dex when they encounter a mon.
//hopefully not break battle music
//I know its doable since people have setup battle menu callbacks before
//make task if in callback, can do left right to swap enemy side mon, 
//for if its doubles etc.

//think will be like other hacks
//press L on main battle page to load dex from battler
//press L on move selection to Load move info page

//think checke if in battle, and when pull mon page load type info
//even if not caught, now once I have that info it doesn't make sense
//for that info to go away if not able to catch, so make field
//battleDexUsed, and if true will load the mon types on the dex page,
//after battle from then on //so make field caught or seen w battle dex
//i.e seen and species battledexused == true
//believe make as field added to base stats //no don't add to base stats its const so cant change
//could just use variable battleDexUsed in function
//if  in battle set  battleDexUsed = TRUE
//then when you load mon page, if that's true and not caught, load and set types to display or something
#define NEW_DEX_USE_NOTES
void DexScreen_PrintMonStatPage(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 statTotal;
    const u8 * labelTextTotal;
    u8 bufferTotal[32];
    u8 i;



    //assign stat field
    statTotal = GetBaseStatTotal(species);

    //assign label
    labelTextTotal = gText_StatTotal;


    //prepare buffers
    i = 0;
    bufferTotal[i++] = EXT_CTRL_CODE_BEGIN;
    bufferTotal[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    bufferTotal[i++] = 0; 


    //this to isolate individual numbers place to add to string
    statTotal %= 1000; //hundreds place
    if ((bufferTotal[i] = (statTotal / 100) + CHAR_0) == CHAR_0)
    {
        bufferTotal[i++] = CHAR_SPACE;
    }
    else
    {
        i++;
    }

    statTotal %= 100; //10s place

    bufferTotal[i++] = (statTotal / 10) + CHAR_0;

    statTotal %= 10; //1s place
    bufferTotal[i++] = (statTotal) + CHAR_0;


    /*{ //Removed Seen Check
        bufferTotal[i++] = CHAR_QUESTION_MARK;
        bufferTotal[i++] = CHAR_QUESTION_MARK;
        bufferTotal[i++] = CHAR_QUESTION_MARK;
    }
    */
    bufferTotal[i++] = CHAR_SPACE;
    bufferTotal[i++] = EXT_CTRL_CODE_BEGIN;
    bufferTotal[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    bufferTotal[i++] = 0;
    
    //hmm thnk I can do entire stat list in this function long as I make multiplebuffers
    //and can just increment x and y like below, long as i do it in proper order should be no issue
    bufferTotal[i] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelTextTotal, x, y, 0);
    y += 12;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, bufferTotal, x, y, 0);
}

//DexScreen_PrintMonCategory
void DexScreen_PrintMonFlavorText(u8 windowId, u16 species, u8 x, u8 y)
{
    struct TextPrinterTemplate printerTemplate;
    u16 length;
    s32 xCenter;
    u32 i;
    u16 NatSpecies;
    u16 FormSpecies;
    u16 caught = DoesSpeciesHaveCosmeticForms(species) ? DexScreen_GetSetPokedexFlag(GetFormSpeciesId(species, 0), FLAG_GET_CAUGHT, TRUE) :  DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE);


    if (species > NATIONAL_SPECIES_COUNT
    && gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION)
    {
        FormSpecies = GetFormSpeciesId(species, 0);
    }

        
    

    //bool8 UseBaseForm = FALSE;
    //can use ternary operator or just a conditional assignment
    //yeah prob better to do conditional assignment
    //to pass off whether it'll check if you've caught the 
    //base species or the form species will replace 
    //use of sPokedexScreenData->dexSpecies

    //if I can return the species argument from
    //gFormChangeTablePointers that would be a good split
    //for if the specie is a temp form or permanent form.
    //as that is used for species that change forms in battle

    //can't pull species since its a pointer table,
    //instead need copy species constants in array,
    //and compare against that
    
    //if (species > NATIONAL_SPECIES_COUNT)
    //    species = GetFormSpeciesId(species, 0);

    

    
    /*for (i = 0; i < NELEMS(gdexEntryFormSpecies); i++) //only the cat names I need change
    {
        if (species > NATIONAL_SPECIES_COUNT)
        {
            if (species == gdexEntryFormSpecies[i])
            {
                break;
            }
            
        }
        
    }*/

    /*if (species == gdexEntryFormSpecies[i])
        speciesArgument = GetFormSpeciesId(species, 0);
    else   
        speciesArgument = sPokedexScreenData->dexSpecies;*/

    //if specis is on list use the base form to decide if should display 
    //put this in display form as well
    //still need go over array values to clean up
    /*for (i = 0; i < NELEMS(gdexEntryFormSpecies); i++) //only the cat names I need change
    {
        if (species > NATIONAL_SPECIES_COUNT)
        {
            if (species == gdexEntryFormSpecies[i])
            {
                UseBaseForm = TRUE;
                break;
            }
            
        }
        
    }
    

    //try sepaaret from use of i, in case some issue, well that fixed it suprisingly
    if (UseBaseForm == TRUE)
        speciesArgument = GetFormSpeciesId(species, 0);
    else
        speciesArgument = sPokedexScreenData->dexSpecies;*/

    

    //speciesArgument = DexScreen_FormFilter(species);


    
    if (DexScreen_GetSetPokedexFlag(FormSpecies, FLAG_GET_CAUGHT, TRUE) || caught)
    {

        //plan make  gen9 defualt to 0 so dex entries load, instead of causing freeze for empty data
        //species = (species <= NATIONAL_SPECIES_COUNT && species > SPECIES_ENAMORUS_INCARNATE) ? SPECIES_NONE : SpeciesToNationalPokedexNum(species);
        //welp ok checked emerald and none of these needed nat dex entries
        //I coiuld literally just use species smh
        //EE has entries for forms etc. but doesn't have nat dex stuff for them
        
        //GetFormSpeciesId(species, 0);
        FormSpecies = GetFormSpeciesId(species, 0);
        //NatSpecies = SpeciesToNationalPokedexNum(species);

        NatSpecies = SpeciesToNationalPokedexNum(species);

        //if pre gen 9  check formdex list if not in that use base form entry in dexlist
        if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START) //put and not on gen9 exclusion list
        {
            if (gFormdexEntries[NatSpecies].description != NULL)
                printerTemplate.currentChar = gFormdexEntries[NatSpecies].description;
            else
                printerTemplate.currentChar = gPokedexEntries[SpeciesToNationalPokedexNum(FormSpecies)].description;
        }
        else
        {
            if (gPokedexEntries[NatSpecies].description != NULL)
                printerTemplate.currentChar = gPokedexEntries[NatSpecies].description;
            else
                printerTemplate.currentChar = gPokedexEntries[SpeciesToNationalPokedexNum(FormSpecies)].description;
        }
            

        printerTemplate.windowId = windowId;
        printerTemplate.fontId = FONT_NORMAL;
        printerTemplate.letterSpacing = 0;
        printerTemplate.lineSpacing = 0;
        printerTemplate.unk = 0;
        printerTemplate.fgColor = 1;
        printerTemplate.bgColor = 0;
        printerTemplate.shadowColor = 2;

        if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START)
        {
            if (gFormdexEntries[NatSpecies].description != NULL)
                length = GetStringWidth(FONT_NORMAL, gFormdexEntries[NatSpecies].description, 0);
            else
                length = GetStringWidth(FONT_NORMAL,  gPokedexEntries[SpeciesToNationalPokedexNum(FormSpecies)].description, 0);
        }
        else
        {
            if (gPokedexEntries[NatSpecies].description != NULL)
                length = GetStringWidth(FONT_NORMAL, gPokedexEntries[NatSpecies].description, 0);
            else
                length = GetStringWidth(FONT_NORMAL,  gPokedexEntries[SpeciesToNationalPokedexNum(FormSpecies)].description, 0);
        }

        xCenter = x + (240 - length) / 2;

        if (xCenter > 0)
            x = xCenter;
        else
            x = 0;

        printerTemplate.x = x;
        printerTemplate.y = y;
        printerTemplate.currentX = x;
        printerTemplate.currentY = y;

        AddTextPrinter(&printerTemplate, TEXT_SKIP_DRAW, NULL);
    }
}

//turned into function -
//if specis is on list use the base form to decide if should display 
    //put this in display form as well
    //still need go over array values to clean up //change use flag check instead makes more sense, but keep for dex entry
u16 DexScreen_FormFilter(u16 species)
{
    u32 i;
    bool8 UseBaseForm = FALSE;

    for (i = 0; i < NELEMS(gdexEntryFormSpecies); i++)
    {
        if (species > FORMS_START)
        {
            if (species == gdexEntryFormSpecies[i]) //remember put spiky pikachu castform unown etc. on list
            {
                UseBaseForm = TRUE;
                break;
            }
            
        }
        
    }

    if (UseBaseForm)
        return  GetFormSpeciesId(species, 0);
    else
        return  species;  //potentially change to just species

}

//unused
void DexScreen_DrawMonFootprint(u8 windowId, u16 species, u8 x, u8 y)
{
    return;
    /*u16 i, j, unused, tileIdx;
    u8 footprintPixel, footprintTile;
    u8 * buffer;
    u8 * footprint;

    if (!(DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE)))
        return;
    footprint = (u8 *)(gMonFootprint_None); //this is what where replaced  gfootprint stuff
    buffer = gDecompressionBuffer;
    unused = 0;
    tileIdx = 0;

    // Expand 1bpp to 4bpp
    for (i = 0; i < 32; i++)
    {
        footprintPixel = footprint[i];
        for (j = 0; j < 4; j++)
        {
            footprintTile = 0;
            if (footprintPixel & (1 << (j * 2)))
                footprintTile |= 0x01;
            if (footprintPixel & (2 << (j * 2)))
                footprintTile |= 0x10;
            buffer[tileIdx] = footprintTile;
            tileIdx++;
        }
    }
    BlitBitmapRectToWindow(windowId, buffer, 0, 0, 16, 16, x, y, 16, 16);*/
}

#define CREATE_POKEDEX_PAGE
static u8 DexScreen_DrawMonDexPage(bool8 justRegistered) //should be able to usse this to breakdown dex navigation this will only exist from a place that lists the mon
{
    u32 i;
    u16 seen = DoesSpeciesHaveCosmeticForms(sPokedexScreenData->dexSpecies) ? DexScreen_GetSetPokedexFlag(GetFormSpeciesId(sPokedexScreenData->dexSpecies, 0), FLAG_GET_SEEN, TRUE) :  DexScreen_GetSetPokedexFlag(sPokedexScreenData->dexSpecies, FLAG_GET_SEEN, TRUE);
    u16 SpeciesVal = DoesSpeciesHaveCosmeticForms(sPokedexScreenData->dexSpecies) ? GetFormSpeciesId(sPokedexScreenData->dexSpecies, 0) : sPokedexScreenData->dexSpecies;
    DexScreen_DexPageZoomEffectFrame(3, 6);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    for (i = 0; gDexAdjusting[i] != END_LIST; i++)
    {
        if (sPokedexScreenData->dexSpecies == gDexAdjusting[i]) //this works now just need a list of all mon I Need the bigger window for a make it do a loop
            break;
    }
    if (sPokedexScreenData->dexSpecies == SPECIES_AZELF 
    || sPokedexScreenData->dexSpecies == SPECIES_MESPRIT 
    || sPokedexScreenData->dexSpecies == SPECIES_UXIE
    || sPokedexScreenData->dexSpecies == SPECIES_ORBEETLE
    || sPokedexScreenData->dexSpecies == SPECIES_TINKATON
    || sPokedexScreenData->dexSpecies == SPECIES_KINGAMBIT) //SEE IF LOOKS BETTER
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic3_Highest); //works

    else if (sPokedexScreenData->dexSpecies != gDexAdjusting[i]) //if mon not in list, uses higher window
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic2_Large);
        
    else
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic);

    sPokedexScreenData->windowIds[1] = AddWindow(&sWindowTemplate_DexEntry_SpeciesStats);
    sPokedexScreenData->windowIds[2] = AddWindow(&sWindowTemplate_DexEntry_FlavorText);

    // Mon pic
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[0], PIXEL_FILL(0));
    //104 does silouette but swapping between dex pages for forms breaks it, doesn't display right palette?
    //mcgriffin advice its not loading new palette when going from  full to silloueted
    //tested and confirmed it just takes the palette from the original species and applies to all the blacked out ones
    //I gues what i need is to clear the palette?
    
    if (seen)  //wanted to add a bit of mystery to this for evo page,
    {  //would have been blacked out mon pics but able to see mon icons, but give up
        //FreeAllSpritePalettes();
    //attempted set to swap palette didn't work
        DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144, TRUE);     //144 is start fo 10th palette 144/16 so that just means start of palette data
 
    } 
    else //work around / I did it!!
        DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144, FALSE);     //144 is start fo 10th palette 144/16 so that just means start of palette data
       // LoadMonPicInWindow(SPECIES_NONE, SHINY_ODDS, DexScreen_GetDefaultPersonality(SPECIES_NONE), FALSE, 144 >> 4, sPokedexScreenData->windowIds[0], TRUE);

    /*else
    {
        u8 *framePics;
        
        framePics = Alloc(4 * 0x800);
        if (framePics && !DecompressPic_HandleDeoxys(sPokedexScreenData->dexSpecies, SHINY_ODDS, TRUE, (u8 *)GetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILE_DATA), FALSE))
        {
            BlitBitmapRectToWindow(sPokedexScreenData->windowIds[0], framePics, 0, 0, 0x40, 0x40, 0, 0, 0x40, 0x40);
            //LoadPicPaletteBySlot(species, otId, personality, paletteSlot, FALSE);
            LoadSpritePalettes(sStatBarSpritePal);
            CreateMonPicSprite(sPokedexScreenData->dexSpecies,SHINY_ODDS, DexScreen_GetDefaultPersonality(sPokedexScreenData->dexSpecies),TRUE, 0,0, 144, TAG_BLANK_MON_PIC, FALSE);
            Free(framePics);
            //return 0;
        }
        DecompressPic_HandleDeoxys(sPokedexScreenData->dexSpecies, SHINY_ODDS, TRUE, (u8 *)GetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILE_DATA), FALSE);
        //DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144);
        
        LoadPalette(sPalette_Silhouette, OBJ_PLTT_ID(2), sizeof(sPalette_Silhouette));
    }*/
        

    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    //GetSpeciesName(gStringVar1, SpeciesVal);
    //used this over getspeciesname function,
    //to get around cur str limit as not using for health box
    StringCopy(gStringVar1,gBaseStats[SpeciesVal].speciesName);
    if (ShouldCapitalizeSpecies())
        CapializeString(gStringVar1);


    // Species stats -need change these print functions, dexno cat, height & weight
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[1], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[1], FONT_SMALL, SpeciesVal, 0, 1);
    //print name
    if (SpeciesVal <= 999)
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[1], FONT_NORMAL, gStringVar1, 28, 1, 0);
    else
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[1], FONT_NORMAL, gStringVar1, 32, 1, 0); //for 4 digit num, num fits perfect

    DexScreen_PrintMonCategory(sPokedexScreenData->windowIds[1], SpeciesVal, 0, 16);
    DexScreen_PrintMonHeight(sPokedexScreenData->windowIds[1], SpeciesVal, 0, 28);
    DexScreen_PrintMonWeight(sPokedexScreenData->windowIds[1], SpeciesVal, 0, 40);
    DexScreen_PrintMonStatPage(sPokedexScreenData->windowIds[1], SpeciesVal, 75, 28);
    //DexScreen_DrawMonFootprint(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 88, 32);
    PutWindowTilemap(sPokedexScreenData->windowIds[1]);
    CopyWindowToVram(sPokedexScreenData->windowIds[1], COPYWIN_GFX);

    // Dex entry
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[2], PIXEL_FILL(0));
    DexScreen_PrintMonFlavorText(sPokedexScreenData->windowIds[2], SpeciesVal, 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[2]);
    CopyWindowToVram(sPokedexScreenData->windowIds[2], COPYWIN_GFX);

    // Control info - cancel/next buttons
    FillWindowPixelBuffer(1, PIXEL_FILL(15)); //was 255  /is same thing calcs to 15 bitwise or 15 left shft 4
    if (justRegistered == FALSE)
    {
        DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_Cry, 8, 2, 4);
        if (gFormSpeciesIdTables[sPokedexScreenData->dexSpecies] != NULL) //if has a form should display form text
            DexScreen_PrintControlInfo(gText_FormsNextDataCancel);
        else
            DexScreen_PrintControlInfo(gText_NextDataCancel);//wa bale to update and add a dpad forms graphic to this don't need scroll arrows
    }
    else
        // Just registered
        DexScreen_PrintControlInfo(gText_Next);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);

    return 1;
}

static void UpdateStatBars(u16 species)
{
    u16 SpeciesVal = DoesSpeciesHaveCosmeticForms(species) ? GetFormSpeciesId(species, 0) : species;
    //LoadSpritePalettes(sStatBarSpritePal);
    //taken from emerald doesn't appear to use window ids at all instead?
    //if right cna get rid of window 0 below
    //sPokedexScreenData->statBarsSpriteId = 0xFF;  //stat bars
    CreateStatBars(SpeciesVal); //stat bars
    //sPokedexScreenData->statBarsBgSpriteId = 0xFF;  //stat bars background
    CreateStatBarsBg(); //stat bars background
}

static u8 DexScreen_DrawMonEvoPage(bool8 justRegistered) //should be able to usse this to breakdown dex navigation this will only exist from a place that lists the mon
{
    u32 i;
    u8 taskId = 0;
    u32 alreadyPrintedIcons[MAX_ICONS] = {0};
    //u32 preservedPalettes; //not doing anything rn?
    u32 iconOffset;
    u16 SpeciesVal = DoesSpeciesHaveCosmeticForms(sPokedexScreenData->dexSpecies) ? GetFormSpeciesId(sPokedexScreenData->dexSpecies, 0) : sPokedexScreenData->dexSpecies;

    DexScreen_DexPageZoomEffectFrame(3, 6);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    /*for (i = 0; gDexAdjusting[i] != END_LIST; i++)
    {
        if (sPokedexScreenData->dexSpecies == gDexAdjusting[i]) //this works now just need a list of all mon I Need the bigger window for a make it do a loop
            break;
    }
    if (sPokedexScreenData->dexSpecies == SPECIES_AZELF 
    || sPokedexScreenData->dexSpecies == SPECIES_MESPRIT 
    || sPokedexScreenData->dexSpecies == SPECIES_UXIE
    || sPokedexScreenData->dexSpecies == SPECIES_ORBEETLE) //SEE IF LOOKS BETTER
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic3_Highest); //works

    else if (sPokedexScreenData->dexSpecies != gDexAdjusting[i]) //if mon not in list, uses higher window
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic2_Large);
        
    else
    */
    //forgot to actually fill this window, an think replace with actual stat window, if need be
    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic);
        

    sPokedexScreenData->windowIds[1] = AddWindow(&sWindowTemplate_DexEntry_SpeciesStats);
    sPokedexScreenData->windowIds[2] = AddWindow(&sWindowTemplate_DexEntry_FlavorText);

    FreeAllSpritePalettes(); //attempt fix for palette issue
    LoadSpritePalettes(sStatBarSpritePal);
    //taken from emerald doesn't appear to use window ids at all instead?
    //if right cna get rid of window 0 below
    sPokedexScreenData->statBarsSpriteId = 0xFF;  //stat bars
    //CreateStatBars(sPokedexScreenData->dexSpecies); //stat bars
    sPokedexScreenData->statBarsBgSpriteId = 0xFF;  //stat bars background
    //CreateStatBarsBg(); //stat bars background
    //seems works for memory manageent bars now built by UpdateStatBars function
    //cuts back on double building - it fixed all navigation issues it seems
    

    // Mon pic - stats Bar //having this is necessary to clear mon pic on move to evo page
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[0], PIXEL_FILL(0));
    //DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144);     //interestingly using 104 makes it siloutted could use for dexnav vsonic
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    GetSpeciesName(gStringVar1, SpeciesVal);

    
    //keep dex num and name, remove others and put evo line sprites here
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[1], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[1], FONT_SMALL, sPokedexScreenData->dexSpecies, 0, 1);

    if (SpeciesVal <= 999)
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[1], FONT_NORMAL, gStringVar1, 28, 1, 0);
    else
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[1], FONT_NORMAL, gStringVar1, 32, 1, 0); //for 4 digit num, num fits perfect
    

    PutWindowTilemap(sPokedexScreenData->windowIds[1]);
    CopyWindowToVram(sPokedexScreenData->windowIds[1], COPYWIN_GFX);

    // Dex entry / evo methods printed here
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[2], PIXEL_FILL(0));
    //DexScreen_PrintMonFlavorText(sPokedexScreenData->windowIds[2], sPokedexScreenData->dexSpecies, 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[2]);
    CopyWindowToVram(sPokedexScreenData->windowIds[2], COPYWIN_GFX);

    ResetEvoScreenDataStruct();
            //Icon
            //FreeMonIconPalettes(); //Free space for new pallete
            //SafeFreeMonIconPalette(sPokedexScreenData->dexSpecies);
            FreeMonIconPalette(sPokedexScreenData->dexSpecies); //replace for use of outside numspecies
            LoadMonIconPalette(sPokedexScreenData->dexSpecies); //Loads pallete for current mon, same for this, I need to load the palette
            PrintPreEvolutions(taskId, sPokedexScreenData->dexSpecies); //this is the problem, 
            #ifdef POKEMON_EXPANSION
                gTasks[taskId].data[4] = CreateMonIcon(sPokedexScreenData->dexSpecies, SpriteCB_MonIcon, 18 + 32*sPokedexScreenData->numPreEvolutions, 31, 4, 0); //Create pokemon sprite
            #else
                gTasks[taskId].data[4] = CreateMonIcon(sPokedexScreenData->dexSpecies, SpriteCB_MonIcon, 18 + 32*sPokedexScreenData->numPreEvolutions, 36, 4, 0, TRUE); //Create pokemon sprite
            #endif //handles icon for current mon, i.e selected species
            //EvoFormsPage_PrintNavigationButtons(); //HGSS_Ui Navigation buttons
            gSprites[gTasks[taskId].data[4]].oam.priority = 0;

    //Print evo info and icons
        iconOffset = sPokedexScreenData->numPreEvolutions;
        gTasks[taskId].data[3] = 0;  //prevents freeze
        PrintEvolutionTargetSpeciesAndMethod(taskId, sPokedexScreenData->dexSpecies, 0, sPokedexScreenData->numPreEvolutions, alreadyPrintedIcons, &iconOffset);
        LoadSpritePalette(&gSpritePalette_Arrow);
 
    // Control info - cancel/next buttons
    FillWindowPixelBuffer(1, PIXEL_FILL(15)); //was 255  /is same thing calcs to 15 bitwise or 15 left shft 4
    if (justRegistered == FALSE)
    {
        //didn't plan to but will keep cry, page looks off without it,
        //just make sure to remember ot add functionality that cry played
        //will be for mon hovering over. so can play the evos cry even if not showing mon pic
        DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_DexEvoLeftPanel, 8, 2, 4);
        DexScreen_PrintControlInfo(gText_NextPreviousData);//wa bale to update and add a dpad forms graphic to this don't need scroll arrows
    }
    else
        // Just registered
        DexScreen_PrintControlInfo(gText_Next);

    return 1;
}

u8 RemoveDexPageWindows(void)
{
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[0]);
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[1]);
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[2]);

    return 0;
}

//************************************
//*                                  *
//*        STATS BARS                *
//*                                  *
//************************************

//Stat bars on main screen, code by DizzyEgg, idea and graphics by Jaizu
#define PIXEL_COORDS_TO_OFFSET(x, y)(			\
/*Add tiles by X*/								\
((y / 8) * 32 * 8)								\
/*Add tiles by X*/								\
+ ((x / 8) * 32)								\
/*Add pixels by Y*/								\
+ ((((y) - ((y / 8) * 8))) * 4)				    \
/*Add pixels by X*/								\
+ ((((x) - ((x / 8) * 8)) / 2)))

static inline void WritePixel(u8 *dst, u32 x, u32 y, u32 value)
{
    if (x & 1)
    {
        dst[PIXEL_COORDS_TO_OFFSET(x, y)] &= ~0xF0;
        dst[PIXEL_COORDS_TO_OFFSET(x, y)] |= (value << 4);
    }
    else
    {
        dst[PIXEL_COORDS_TO_OFFSET(x, y)] &= ~0xF;
        dst[PIXEL_COORDS_TO_OFFSET(x, y)] |= (value);
    }
}
#define STAT_BAR_X_OFFSET 10
static void CreateStatBar(u8 *dst, u32 y, u32 width)
{
    u32 i, color;

    switch (width)
    {
    case 0 ... 5:
        color = COLOR_WORST;
        break;
    case 6 ... 15:
        color = COLOR_BAD;
        break;
    case 16 ... 25:
        color = COLOR_AVERAGE;
        break;
    case 26 ... 31:
        color = COLOR_GOOD;
        break;
    case 32 ... 35: //was 37 upper limit, 36 is about stat value 140
        color = COLOR_VERY_GOOD; //seem to be good, previously even stat value 160+ didn't change color
        break;
    default:
        color = COLOR_BEST;
        break;
    }

    // white pixes left side
    WritePixel(dst, STAT_BAR_X_OFFSET, y + 0, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET, y + 1, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET, y + 2, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET, y + 3, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET, y + 4, COLOR_ID_BAR_WHITE);

    // white pixels right side
    WritePixel(dst, STAT_BAR_X_OFFSET + width - 1, y + 0, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET + width - 1, y + 1, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET + width - 1, y + 2, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET + width - 1, y + 3, COLOR_ID_BAR_WHITE);
    WritePixel(dst, STAT_BAR_X_OFFSET + width - 1, y + 4, COLOR_ID_BAR_WHITE);

    // Fill
    for (i = 1; i < width - 1; i++)
    {
        WritePixel(dst, STAT_BAR_X_OFFSET + i, y + 0, COLOR_ID_BAR_WHITE);
        WritePixel(dst, STAT_BAR_X_OFFSET + i, y + 1, COLOR_ID_FILL_SHADOW + color * 2);
        WritePixel(dst, STAT_BAR_X_OFFSET + i, y + 2, COLOR_ID_FILL + color * 2);
        WritePixel(dst, STAT_BAR_X_OFFSET + i, y + 3, COLOR_ID_FILL + color * 2);
        WritePixel(dst, STAT_BAR_X_OFFSET + i, y + 4, COLOR_ID_BAR_WHITE);
    }
}
static const u8 sBaseStatOffsets[] =
{
    offsetof(struct BaseStats, baseHP),
    offsetof(struct BaseStats, baseAttack),
    offsetof(struct BaseStats, baseDefense),
    offsetof(struct BaseStats, baseSpAttack),
    offsetof(struct BaseStats, baseSpDefense),
    offsetof(struct BaseStats, baseSpeed),
};
static void TryDestroyStatBars(void)
{
    //if (sPokedexScreenData->statBarsSpriteId != 0xFF) //removing this block to free, seems to have fix memory issue
    {
        FreeSpriteTilesByTag(TAG_STAT_BAR);
        //FreeSpriteOamMatrix(&gSprites[sPokedexScreenData->statBarsSpriteId]);
        DestroySprite(&gSprites[sPokedexScreenData->statBarsSpriteId]);
        sPokedexScreenData->statBarsSpriteId = 0xFF;
    }
}
static void TryDestroyStatBarsBg(void)
{
    //if (sPokedexScreenData->statBarsBgSpriteId != 0xFF)
    {
        FreeSpriteTilesByTag(TAG_STAT_BAR_BG);
        //FreeSpriteOamMatrix(&gSprites[sPokedexScreenData->statBarsBgSpriteId]);
        DestroySprite(&gSprites[sPokedexScreenData->statBarsBgSpriteId]);
        sPokedexScreenData->statBarsBgSpriteId = 0xFF;
    }
}
static void CreateStatBars(u32 species)//(struct PokedexListItem *dexMon)
{
    u8 offset_x = 184; //Moves the complete stat box left/right
    u8 offset_y = 1; //Moves the complete stat box up/down


    //sPokedexScreenData->justScrolled = FALSE;

    //if (dexMon->owned) // Show filed bars
    //{
        u8 i;
        u32 width, statValue;
        u8 *gfx = Alloc(64 * 64);
        static const u8 sBarsYOffset[] = {4, 13, 21, 31, 40, 49};
        struct SpriteSheet sheet = {gfx, 64 * 64, TAG_STAT_BAR};
        //u32 species = NationalPokedexNumToSpecies(dexMon->dexNum);
        //u32 species = sPokedexScreenData->dexSpecies;
        TryDestroyStatBars();

        memcpy(gfx, sStatBarsGfx, sizeof(sStatBarsGfx));
        for (i = 0; i < NUM_STATS; i++)
        {
            statValue = *((u8*)(&gBaseStats[species]) + sBaseStatOffsets[i]);
            if (statValue <= 100)
            {
                width = statValue / 3;
                if (width >= 33)
                    width -= 1;
            }
            else
                width = (100 / 3) + ((statValue - 100) / 14);

            if (width > 39) // Max pixels
                width = 39;
            if (width < 3)
                width = 3;

            CreateStatBar(gfx, sBarsYOffset[i], width);
        }

        LoadSpriteSheet(&sheet);
        Free(gfx);

    sPokedexScreenData->statBarsSpriteId = CreateSprite(&sStatBarSpriteTemplate, 36+offset_x, 48+offset_y, 10);
}
static void CreateStatBarsBg(void) //stat bars background text
{
    static const struct SpriteSheet sheetStatBarsBg = {sStatBarsGfx, 64 * 64, TAG_STAT_BAR_BG};
    u8 offset_x = 184; //Moves the complete stat box left/right
    u8 offset_y = 1; //Moves the complete stat box up/down  //think will use 2 or 0 for y value

    TryDestroyStatBarsBg();

    LoadSpriteSheet(&sheetStatBarsBg);
    sPokedexScreenData->statBarsBgSpriteId = CreateSprite(&sStatBarBgSpriteTemplate, 36+offset_x, 48+offset_y, 0);
}
// Hack to destroy sprites when a pokemon data is being loaded in
static bool32 IsMonInfoBeingLoaded(void) //don't have a use for yet
{
    return 0;//(gSprites[sPokedexScreenData->selectedMonSpriteId].callback == SpriteCB_MoveMonForInfoScreen);
}
static void SpriteCB_StatBars(struct Sprite *sprite)
{
    //if (IsMonInfoBeingLoaded())//loading is for between info page and mainpage, callback is for moving mon sprite position
    if (JOY_NEW(B_BUTTON))   
       sprite->invisible = TRUE;//so if this is true below isn't true? and below is for destroying stats sprites, this just hides it

    //means destroy if not on main page or search page, for me it would be if not on evo page
    if (sPokedexScreenData->currentPage != DEX_EVO_FROM_LIST && sPokedexScreenData->currentPage != DEX_EVO_FROM_HABITAT)
    {
        FreeSpriteTilesByTag(TAG_STAT_BAR);
        FreeSpriteOamMatrix(&gSprites[sPokedexScreenData->statBarsSpriteId]);
        DestroySprite(&gSprites[sPokedexScreenData->statBarsSpriteId]);
        sPokedexScreenData->statBarsSpriteId = 0xFF;
    }
}
static void SpriteCB_StatBarsBg(struct Sprite *sprite)
{
    
    //if (IsMonInfoBeingLoaded())
    if (JOY_NEW(B_BUTTON))
        sprite->invisible = TRUE;
    if (sPokedexScreenData->currentPage != DEX_EVO_FROM_LIST && sPokedexScreenData->currentPage != DEX_EVO_FROM_HABITAT)
    {
        FreeSpriteTilesByTag(TAG_STAT_BAR_BG);
        FreeSpriteOamMatrix(&gSprites[sPokedexScreenData->statBarsBgSpriteId]);
        DestroySprite(&gSprites[sPokedexScreenData->statBarsBgSpriteId]);
        sPokedexScreenData->statBarsBgSpriteId = 0xFF;
    }
}
//
/*END STAT BAR*/

u8 DexScreen_DrawMonAreaPage(void)
{
    int i;
    u8 width, height;
    bool8 monIsCaught = FALSE;
    s16 left, top;
    u16 speciesId;
    u16 species = sPokedexScreenData->dexSpecies;
    u16 kantoMapVoff;
    u16 monScale;
    u16 FormSpecies;


    if (species > NATIONAL_SPECIES_COUNT
    && gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION)
    {
        FormSpecies = GetFormSpeciesId(species, 0);
    }
    else
        FormSpecies = species; //already uses dex->species
    

    //seems can just fully replace speciesId use, as its only used in size comparison
    if (species > NATIONAL_SPECIES_COUNT && species < GEN_9_FORMS_START)
        speciesId = SpeciesToNationalPokedexNum(GetFormSpeciesId(species, 0)); //returns base form species
    //else
        //speciesId = SpeciesToNationalPokedexNum(species);
        //plan make  gen9 defualt to 0 so dex entries load, instead of causing freeze for empty data
    //    speciesId = (species <= NATIONAL_SPECIES_COUNT && species > SPECIES_ENAMORUS_INCARNATE) ? SPECIES_NONE : SpeciesToNationalPokedexNum(species);
    //doesn't work with out below
    //speciesId = SpeciesToNationalPokedexNum(species); //kept this , as before was using nat number so hopefully won't break anything
    
    if (DexScreen_GetSetPokedexFlag(FormSpecies, FLAG_GET_CAUGHT, TRUE) || DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE))
        monIsCaught = TRUE;
    width = 28;
    height = 14;
    left = 0;
    top = 2;

    FillBgTilemapBufferRect_Palette0(3, 4, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_FLIP(4), left + 1 + width, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_V_FLIP(4), left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_V_FLIP(4), left + 1 + width, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 5, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_V_FLIP(5), left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(3, 6, left, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_FLIP(6), left + 1 + width, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(3, 1, left + 1, top + 1, width, height);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    width = 10;
    height = 6;
    left = 1;
    top = 9;

    FillBgTilemapBufferRect_Palette0(0, 29, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_FLIP(29), left + 1 + width, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_V_FLIP(29), left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_V_FLIP(29), left + 1 + width, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 30, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_V_FLIP(30), left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(0, 31, left, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_FLIP(31), left + 1 + width, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);

    sPokedexScreenData->unlockedSeviiAreas = GetUnlockedSeviiAreas();
    kantoMapVoff = 4;
    // If any of the postgame islands are unlocked, Kanto map needs to be flush with the
    // top of the screen.
    for (i = 3; i < 7; i++)
        if ((sPokedexScreenData->unlockedSeviiAreas >> i) & 1)
            kantoMapVoff = 0;

    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_AreaMap_Kanto);
    CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[0], (void *)sTilemap_AreaMap_Kanto, 0, 0);
    SetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILEMAP_TOP,
                       GetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILEMAP_TOP) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    for (i = 0; i < 7; i++)
        if ((sPokedexScreenData->unlockedSeviiAreas >> i) & 1)
        {
            sPokedexScreenData->windowIds[i + 1] = AddWindow(sAreaMapStructs_SeviiIslands[i].window);
            CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[i + 1], sAreaMapStructs_SeviiIslands[i].tiles, 0, 0);
            SetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP) + kantoMapVoff);
            PutWindowTilemap(sPokedexScreenData->windowIds[i + 1]);
            CopyWindowToVram(sPokedexScreenData->windowIds[i + 1], COPYWIN_GFX);
        }
    sPokedexScreenData->windowIds[8] = AddWindow(&sWindowTemplate_AreaMap_SpeciesName); //also dex number?
    sPokedexScreenData->windowIds[9] = AddWindow(&sWindowTemplate_AreaMap_Size);
    sPokedexScreenData->windowIds[10] = AddWindow(&sWindowTemplate_AreaMap_Area);
    sPokedexScreenData->windowIds[11] = AddWindow(&sWindowTemplate_AreaMap_MonIcon);
    sPokedexScreenData->windowIds[12] = AddWindow(&sWindowTemplate_AreaMap_MonTypes);

    // Draw the mon icon
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[11], PIXEL_FILL(0));
    ListMenu_LoadMonIconPalette(BG_PLTT_ID(10), species);
    ListMenu_DrawMonIconGraphics(sPokedexScreenData->windowIds[11], species, DexScreen_GetDefaultPersonality(species), 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[11]);
    CopyWindowToVram(sPokedexScreenData->windowIds[11], COPYWIN_GFX);

    // Print "Size"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[9], PIXEL_FILL(0));
    {
        s32 strWidth = GetStringWidth(FONT_SMALL, gText_Size, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[9], FONT_SMALL, gText_Size, (sWindowTemplate_AreaMap_Size.width * 8 - strWidth) / 2, 4, 0);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[9]);
    CopyWindowToVram(sPokedexScreenData->windowIds[9], COPYWIN_GFX);

    // Print "Area"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[10], PIXEL_FILL(0));
    {
        s32 strWidth = GetStringWidth(FONT_SMALL, gText_Area, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[10], FONT_SMALL, gText_Area, (sWindowTemplate_AreaMap_Area.width * 8 - strWidth) / 2, 4, 0);
    }
    SetWindowAttribute(sPokedexScreenData->windowIds[10], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[10], WINDOW_TILEMAP_TOP) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[10]);
    CopyWindowToVram(sPokedexScreenData->windowIds[10], COPYWIN_GFX);

    GetSpeciesName(gStringVar1,species);

    // Print species name
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[8], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[8], FONT_SMALL, species, 0, 4);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[8], FONT_NORMAL, gStringVar1, 3, 16, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[8]);
    CopyWindowToVram(sPokedexScreenData->windowIds[8], COPYWIN_GFX);

    // Type icons
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[12], PIXEL_FILL(0));
    ListMenuLoadStdPalAt(BG_PLTT_ID(11), 1);

    if (monIsCaught)
    {
        BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type1, 0, 1);
        if (gBaseStats[species].type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type2, 34, 1);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[12]);
    CopyWindowToVram(sPokedexScreenData->windowIds[12], COPYWIN_GFX);

    // Show size comparison
    ResetAllPicSprites();
    LoadPalette(sPalette_Silhouette, OBJ_PLTT_ID(2), PLTT_SIZE_4BPP);

    //will now fill baseform if above species count
    //something wrong w base spepcies pikachu bigger than forms
    //despite supposedly using same values
    monScale = gPokedexEntries[speciesId].pokemonScale;
    if (monIsCaught) 
    {
        sPokedexScreenData->windowIds[14] = CreateMonPicSprite_HandleDeoxys(species, SHINY_ODDS, DexScreen_GetDefaultPersonality(species), TRUE, 40, 104, 0, 0xFFFF); //was 65535
        gSprites[sPokedexScreenData->windowIds[14]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[sPokedexScreenData->windowIds[14]].oam.matrixNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[14]].pos2.y = gPokedexEntries[speciesId].pokemonOffset; //this is elevation of mon pic
        if (sPokedexScreenData->dexSpecies == SPECIES_MEWTWO_MEGA_Y)
            monScale = gPokedexEntries[SpeciesToNationalPokedexNum(SPECIES_MEW)].pokemonScale;
        SetOamMatrix(2, monScale, 0, 0, monScale);
        //trainer pic values
        sPokedexScreenData->windowIds[15] = CreateTrainerPicSprite(PlayerGenderToFrontTrainerPicId_Debug(gSaveBlock2Ptr->playerGender, TRUE), 1, 80, 104, 0, 0xFFFF); //same as above
        gSprites[sPokedexScreenData->windowIds[15]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[15]].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[sPokedexScreenData->windowIds[15]].oam.matrixNum = 1;
        gSprites[sPokedexScreenData->windowIds[15]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[15]].pos2.y = gPokedexEntries[speciesId].trainerOffset;
        SetOamMatrix(1, gPokedexEntries[speciesId].trainerScale, 0, 0, gPokedexEntries[speciesId].trainerScale);
    }
    else
    {
        sPokedexScreenData->windowIds[14] = 0xff;
        sPokedexScreenData->windowIds[15] = 0xff;
    }

    // Create the area markers
    sPokedexScreenData->areaMarkersTaskId = CreatePokedexAreaMarkers(species, TAG_AREA_MARKERS, 3, kantoMapVoff * 8);
    if (GetNumPokedexAreaMarkers(sPokedexScreenData->areaMarkersTaskId) == 0)
    {
        // No markers, display "Area Unknown"
        BlitBitmapRectToWindow(sPokedexScreenData->windowIds[0], (void *)sBlitTiles_WideEllipse, 0, 0, 88, 16, 4, 28, 88, 16);
        {
            s32 strWidth = GetStringWidth(FONT_SMALL, gText_AreaUnknown, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[0], FONT_SMALL, gText_AreaUnknown, (96 - strWidth) / 2, 29, 0);
        }
    }
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    // Draw the control info
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_Cry, 8, 2, 4);
    DexScreen_PrintControlInfo(gText_CancelPreviousData);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);

    return 1;
}


u8 DexScreen_DestroyAreaScreenResources(void)
{
    int i;

    DestroyPokedexAreaMarkers(sPokedexScreenData->areaMarkersTaskId);

    for (i = 0; i < 13; i++)
        DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[i]);
    if (sPokedexScreenData->windowIds[15] != 0xff)
        FreeAndDestroyTrainerPicSprite(sPokedexScreenData->windowIds[15]);
    if (sPokedexScreenData->windowIds[14] != 0xff)
        FreeAndDestroyMonPicSprite(sPokedexScreenData->windowIds[14]);
    return 0;
}

//no idea why I didn't just remove this...
static int DexScreen_CanShowMonInDex(u16 species)
{
    if (IsNationalPokedexEnabled() == TRUE)
        return TRUE;
    //if (SpeciesToNationalPokedexNum(species) <= KANTO_DEX_COUNT)
    //    return TRUE;
    return FALSE;
}

static u8 DexScreen_CanShowMonInCategory(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;

    for (i = 0; i < 4; i++)
    {
        if (i < count)
        {
            species = gDexCategories[categoryNum].page[pageNum].species[i];
            if (/*DexScreen_CanShowMonInDex(species) == TRUE &&*/ DexScreen_GetSetPokedexFlag(species, FLAG_GET_SEEN, TRUE))
                return TRUE;
        }
    }
    return FALSE;
}

static bool8 DexScreen_IsCategoryUnlocked(u8 categoryNum)
{
    int i;
    u8 count;

    count = gDexCategories[categoryNum].count;

    for (i = 0; i < count; i++)
        if (DexScreen_CanShowMonInCategory(categoryNum, i))
            return 1;

    return 0;
}

void DexScreen_CreateCategoryPageSpeciesList(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;
    sPokedexScreenData->numMonsOnPage = 0;

    for (i = 0; i < 4; i++) //max number mon on category page
        sPokedexScreenData->pageSpecies[i] = 0xffff;
    for (i = 0; i < count; i++) //dex page, also limited to 4 to fit
    {
        species = gDexCategories[categoryNum].page[pageNum].species[i];
        if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, FLAG_GET_SEEN, TRUE))
        {
            sPokedexScreenData->pageSpecies[sPokedexScreenData->numMonsOnPage] = gDexCategories[categoryNum].page[pageNum].species[i];
            sPokedexScreenData->numMonsOnPage++;
        }
    }
}

static u8 DexScreen_GetPageLimitsForCategory(u8 category)
{
    int i;
    u8 count, firstPage, lastPage;

    count = gDexCategories[category].count;
    firstPage = 0xff;
    lastPage = 0xff;

    for (i = 0; i < count; i++)
        if (DexScreen_CanShowMonInCategory(category, i))
        {
            if (firstPage == 0xff)
                firstPage = i;
            lastPage = i;
        }
    if (lastPage != 0xff)
    {
        sPokedexScreenData->firstPageInCategory = firstPage;
        sPokedexScreenData->lastPageInCategory = lastPage + 1;
        return FALSE;
    }
    else
    {
        sPokedexScreenData->firstPageInCategory = 0;
        sPokedexScreenData->lastPageInCategory = 0;
        return TRUE;
    }
}

enum DexCategories {
    Grassland_Pokemon,
    Forest_Pokemon,
    WatersEdge_Pokemon,
    Sea_Pokemon,
    Cave_Pokemon,
    Mountain_Pokemon,
    RoughTerrain_Pokemon,
    Urban_Pokemon,
    Rare_Pokemon,    
};

//still searching but need find a way to replace 
//mon for loading dex stuff on catch
//without neeeding to create a category page for them
static u8 DexScreen_LookUpCategoryBySpecies(u16 species)
{
    int i, j;
    u16 dexSpecies;
    u16 foundSpecies = 0; //check to break out of main loop after find species

    for (i = 0; i < NELEMS(gDexCategories); i++) //change to an i value check make enum to match array
    {   
        
        if (Grassland_Pokemon == i) //written this just cuz felt was more readable
        {
            for (j = 0; j < NELEMS(gDexCategory_GrasslandPkmnlist); j++)
            {
                if (species == gDexCategory_GrasslandPkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_GrasslandPkmnlist[j]))
                {
                    foundSpecies = gDexCategory_GrasslandPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }


        if (Forest_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_ForestPkmnlist); j++)
            {
                if (species == gDexCategory_ForestPkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_ForestPkmnlist[j]))
                {
                    foundSpecies = gDexCategory_ForestPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

            
        if (WatersEdge_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_WatersEdgePkmnlist); j++)
            {
                if (species == gDexCategory_WatersEdgePkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_WatersEdgePkmnlist[j]))
                {
                    foundSpecies = gDexCategory_WatersEdgePkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Sea_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_SeaPkmnlist); j++)
            {
                if (species == gDexCategory_SeaPkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_SeaPkmnlist[j]))
                {
                    foundSpecies = gDexCategory_SeaPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Cave_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_CavePkmnlist); j++)
            {
                if (species == gDexCategory_CavePkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_CavePkmnlist[j]))
                {
                    foundSpecies = gDexCategory_CavePkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Mountain_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_MountainPkmnlist); j++)
            {
                if (species == gDexCategory_MountainPkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_MountainPkmnlist[j]))
                {
                    foundSpecies = gDexCategory_MountainPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (RoughTerrain_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_RoughTerrainPkmnlist); j++)
            {
                if (species == gDexCategory_RoughTerrainPkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_RoughTerrainPkmnlist[j]))
                {
                    foundSpecies = gDexCategory_RoughTerrainPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Urban_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_UrbanPkmnlist); j++)
            {
                if (species == gDexCategory_UrbanPkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_UrbanPkmnlist[j]))
                {
                    foundSpecies = gDexCategory_UrbanPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Rare_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_RarePkmnlist); j++)
            {
                if (species == gDexCategory_RarePkmnlist[j] || (GetFormSpeciesId(species, 0) == gDexCategory_RarePkmnlist[j]))
                {
                    foundSpecies = gDexCategory_RarePkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }
        
        if (foundSpecies)   //realized only need one
            break;  //break out of main loop
        
    }

        //this needed to pass to screendeta->dexspecies to
        //populate dex as well as play correct cry on dex load - need check cry play w volume but from looks should work correctly
        sPokedexScreenData->dexSpecies = species;
        dexSpecies = foundSpecies;

        //got it all working, all need is store category, removed need for other values
        //instead of reading dex category struct, it'll fill in the template page with its image species name and dex number, 
        //same as if it actually had a cat page.
        //this saves me a good deal of physical space, and also I just don't want to add a BUNCH of category pages that already move slowly
        //that no one really looks through, it'd just be unnecesary bloat
        if (species == dexSpecies || (species == GetFormSpeciesId(dexSpecies, 0)))
        {
            sPokedexScreenData->category = i; //this sets category text, only part I needed from original function      
            
            return FALSE; 
           
        }
        
    return TRUE;
}

static u8 DexScreen_PageNumberToRenderablePages(u16 page)
{
    int i, count;

    for (i = 0, count = 0; i < page; i++)
        if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, i))
            count++;

    return count + 1;
}

void DexScreen_InputHandler_StartToCry(void)
{
    if (JOY_NEW(START_BUTTON))
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
}

//for forms that are counted as same mon, would want form check here as well,
//so they would display as caught or seen - may have already done that? idk
//checked seems in battle only sets seen from enemy side, so player changing into form for first time
//wouldn't set seenm, hmm but it does do so for evolution scene,
//so if I do something similar for form change, it'd work for my needs
//would just need a check to make sure its not already set i.e use get_seen/getcaught  if not 
//then set..VSONIC IMPORTANT
u8 DexScreen_RegisterMonToPokedex(u16 species) //now has nat dex, need workaround register mon setup, for cat page, half working dex loads correct not cat page
{
    DexScreen_GetSetPokedexFlag(species, FLAG_SET_SEEN, TRUE);
    DexScreen_GetSetPokedexFlag(species, FLAG_SET_CAUGHT, TRUE);

    if (species > NATIONAL_SPECIES_COUNT
    && !(GetSetPokedexFlag((GetFormSpeciesId(species, 0)), FLAG_GET_SEEN))
    && (gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION
    || gBaseStats[SanitizeSpeciesId(species)].flags == F_ALOLAN_FORM
    || gBaseStats[SanitizeSpeciesId(species)].flags == F_GALARIAN_FORM
    || gBaseStats[SanitizeSpeciesId(species)].flags == F_HISUIAN_FORM
    || gBaseStats[SanitizeSpeciesId(species)].flags == F_PALDEAN_FORM))
    {
        DexScreen_GetSetPokedexFlag(GetFormSpeciesId(species, 0), FLAG_SET_SEEN, TRUE); //if catch form should set base form is seen so can navigate to dex page
    }//if a form, but not seen base form, set base seen so can acces form dex of caught mon

    //if (!IsNationalPokedexEnabled() && SpeciesToNationalPokedexNum(species) > KANTO_DEX_COUNT)
    //    return CreateTask(Task_DexScreen_RegisterNonKantoMonBeforeNationalDex, 0);

    DexScreen_LoadResources();
    
    DexScreen_LookUpCategoryBySpecies(species);//with nat dex enabled at start am able to trigger full mon caught script, but issue is expansion mon
                                        //dont have a species category page, and without that they can't show up properly, it instead defaults to rattata.
                                        //but I don't want to bloat the category dex with a bunch of extra pages so hopefully I can just display the mon in the category
                                        //and won't need an actual page for them.       vsonic IMPORTANT
    gTasks[sPokedexScreenData->taskId].func = Task_DexScreen_RegisterMonToPokedex; //again putting here below lookup just in case order matered
    return sPokedexScreenData->taskId;
}

static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId)
{
    DestroyTask(taskId);
}

//for when catching mon, vsonic edit later for double wilds
//think add some kind of loop/check if battle type double wild and caught both mon
static void Task_DexScreen_RegisterMonToPokedex(u8 taskId) //called from above dexScreen register function, which is called only from bs_commands so change need go there
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        DexScreen_GetPageLimitsForCategory(sPokedexScreenData->category);
        if (sPokedexScreenData->pageNum < sPokedexScreenData->firstPageInCategory)
            sPokedexScreenData->pageNum = sPokedexScreenData->firstPageInCategory;
        sPokedexScreenData->state = 3;
        break;
    case 1:
        RemoveDexPageWindows();
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();

        gMain.state = 0;
        sPokedexScreenData->state = 2;
        break;
    case 2:
        if (DoClosePokedex())
            DestroyTask(taskId);
        break; //nothing appers to go to 1?
    case 3:
        DexScreen_CreateCategoryListGfx(TRUE);
        PutWindowTilemap(0);
        PutWindowTilemap(1);

        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);

        DexScreen_CreateCategoryPageSelectionCursor(0xff);

        sPokedexScreenData->state = 4;
        break;
    case 4:
        gPaletteFade.bufferTransferDisabled = 0;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0xffff);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);

        sPokedexScreenData->state = 5;
        break;
    case 5: //think for when mon first caught
        gTasks[taskId].data[0] = 30;
        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, 1); //this seems to have fixed cursor

        if (gTasks[taskId].data[0])
            gTasks[taskId].data[0]--;
        else
        {
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 7;
        }
        break;
    case 7: 
        sPokedexScreenData->state = 8; 
        break;
    case 8:
        DexScreen_DrawMonDexPage(TRUE); 
        sPokedexScreenData->currentPage = DEX_REGISTER_PAGE;
        sPokedexScreenData->state = 9;
        break;
    case 9:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
    case 10:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0])
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);

            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 11;
        }
        break;
    case 11:
        if (JOY_NEW(A_BUTTON | B_BUTTON))  //this part is similar to EE where the navigation is at the very end
            sPokedexScreenData->state = 2;
        break;
    }//think want add a left right, input function specifically for register dex
    //would be to check evo paths bst and stat distribution but since its still for register dex keep it bare bones
    //so no checking and navigating to evo entries
}

void DexScreen_PrintStringWithAlignment(const u8 * str, s32 mode)
{
    u32 x;

    switch (mode)
    {
    case TEXT_LEFT:
        x = 8;
        break;
    case TEXT_CENTER:
        x = (u32)(240 - GetStringWidth(FONT_NORMAL, str, 0)) / 2;
        break;
    case TEXT_RIGHT:
    default:
        x = 232 - GetStringWidth(FONT_NORMAL, str, 0);
        break;
    }

    DexScreen_AddTextPrinterParameterized(0, FONT_NORMAL, str, x, 2, 4);
}

//building w scroll, not building based on index pos when press b, from info page
//idk what the fuck is wrong but its broken AGAIN somehow, duplicate values on scrolll, not displaying entire list,
//kanto dex is showing 150 values not 151, but if I close and reopen when at end of index it displays correctly so somehting happens
//but ONLY when I effing scroll effing wonderful
//...got it working instantly after gonna pass out now
//issue was just it not properly lining up with other function that created list. smh
//needed + 1 because the natdex stuff subtracts 1, from value
static void DexScreen_LoadIndex(u32 count, u8 direction, int selectedIndex, s8 scroll_increment)
{
    s32 i,j,d;
    bool8 caught;
    bool8 seen;
    struct ListMenu *list = (struct ListMenu *)gTasks[sPokedexScreenData->orderedListMenuTaskId].data;
    s16 ndex_num = selectedIndex;
    
    switch (sPokedexScreenData->dexOrderId)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        if (direction == SCROLL_DOWN)
        {

            for (i = 0; i <= count; i++) //can have this be taken by count argument, so its same code for increasing once
            {
                

                seen = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function
                
                
                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gBaseStats[NationalPokedexNumToSpecies(ndex_num + i + 1)].speciesName;
                }
                else
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gText_5Dashes; //ok the + 1 WAS right, issue was the other part was wrong first, facepalm
                }
                sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num + i + 1);

                if (ndex_num + i == sPokedexScreenData->orderedDexCount) //to stop the function effect so I don't increment passed what I need to
                    break; //needed to prevent graphic glitch from going too high

            }

        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0; i < count; i++) //can have this be taken by count argument, so its same code for increasing once
            {
                

                if (ndex_num - i < 0) //to stop the function effect so I don't increment passed what I need to
                    break; //changed worked for preventing breaks, can now remove limiter on function, should hopefullyu fix az
                    //with signed changed, changed from <= to just < think is more correct

                seen = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function
                
                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {   
                    sPokedexScreenData->listItems[ndex_num - i].label = gBaseStats[NationalPokedexNumToSpecies(ndex_num - i + 1)].speciesName;
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gText_5Dashes;
                }
                sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num - i + 1);
            

            }
        }
        break;
    case DEX_ORDER_ATOZ:
       
        if (direction == SCROLL_DOWN)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Alphabetical); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_CAUGHT, FALSE);
                if (seen)
                {
                                        
                    sPokedexScreenData->listItems[ndex_num + i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
            
        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_CAUGHT, FALSE); 
                if (seen)
                {
                    
                    sPokedexScreenData->listItems[ndex_num - i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
            
        }
        break;
    case DEX_ORDER_TYPE: //can't build automatically would need to loop entire species list MANY times, so would take forever
        //now that I'm saving time I MAY be able to build with a function - attempt w python
        
        if (direction == SCROLL_DOWN)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Type); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    
                    sPokedexScreenData->listItems[ndex_num + i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
            
        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_CAUGHT, FALSE); 
                if (caught)
                {
                    

                    sPokedexScreenData->listItems[ndex_num - i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
            
        }
        break; //order by type and weight, just wouldn't work with my changes/species expansion would require, going through and creating list by hand
    case DEX_ORDER_LIGHTEST: //this is built by weight, but for identical weight it goes in order of lowest to highest height

        if (direction == SCROLL_DOWN)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Weight); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    
                    sPokedexScreenData->listItems[ndex_num + i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
            
        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_CAUGHT, FALSE); 
                if (caught)
                {

                    sPokedexScreenData->listItems[ndex_num - i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
            
        }
        break;
    case DEX_ORDER_SMALLEST:

        if (direction == SCROLL_DOWN)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Height); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    
                    sPokedexScreenData->listItems[ndex_num + i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
            
        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_CAUGHT, FALSE); 
                if (caught)
                {
                    

                    sPokedexScreenData->listItems[ndex_num - i].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[j])].speciesName;
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[j]);
                    
                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
            
        }
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        if (direction == SCROLL_DOWN)
        {
            

            for (i = 0; i <= count; i++) //can have this be taken by count argument, so its same code for increasing once
            {
                //if (count >= (selectedIndex + 100)) //to stop the function effect so I don't increment passed what I need to
                //   break;

                seen = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function

                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {   

                    sPokedexScreenData->listItems[ndex_num + i].label = gBaseStats[NationalPokedexNumToSpecies(ndex_num + i + 1)].speciesName;
                    
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gText_5Dashes;
                }
                sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num + i + 1);

                if (ndex_num + i == sPokedexScreenData->orderedDexCount) //to stop the function effect so I don't increment passed what I need to
                    break; //needed to prevent graphic glitch from going too high

                //if (ndex_num + count >= selectedIndex + 100) //to stop the function effect so I don't increment passed what I need to
                //    break; //for scrolling mon info page, issues are caused when scrolling larger interval than count, testing here
            }
            
        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0; i < count; i++) //can have this be taken by count argument, so its same code for increasing once
            {

                if (ndex_num - i < 0) //to stop the function effect so I don't increment passed what I need to
                    break;

                seen = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function

                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {

                    sPokedexScreenData->listItems[ndex_num - i].label = gBaseStats[NationalPokedexNumToSpecies(ndex_num - i + 1)].speciesName;
                    
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gText_5Dashes;
                }
                sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num - i + 1);
            }
            
        }
        break;
    }
}


static u16 DexScreen_CreateList_ReturnCount(u8 orderIdx, int selectedIndex)
{
    u32 entryPos;
    u16 ndex_num;
    u16 ret = NATIONAL_DEX_NONE;
    s32 i,j, d;
    bool8 caught;  //true false
    bool8 seen;
    u16 NumSeen = IsNationalPokedexEnabled() ? sPokedexScreenData->numSeenNational : sPokedexScreenData->numSeenKanto;
    u16 NumCaught = IsNationalPokedexEnabled() ? sPokedexScreenData->numOwnedNational : sPokedexScreenData->numOwnedKanto;

    //still need make a script change to explain dex changess

    entryPos = selectedIndex;


    switch (orderIdx)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
    {    
        
        for (i = 0; i <= KANTO_DEX_COUNT; i++)
        {
          

            if (entryPos <= DEX_MAX_SHOWN && i == entryPos) 
            {
                for (j = 0; j <= DEX_MAX_SHOWN; j++,i++)
                {
                    seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                            if (seen)
                            {
                                sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(j + 1)].speciesName;
                            }   
                            else
                            {
                                sPokedexScreenData->listItems[j].label = gText_5Dashes;
                            }
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                            ret++;

                }
            }

            if (entryPos > DEX_MAX_SHOWN && i == entryPos && entryPos < sPokedexScreenData->orderedDexCount - 4) //loop 10, over i -5 label & index
            {

                for (j = i - DEX_MAX_SHOWN; j <= entryPos + DEX_MAX_SHOWN; j++) //changed to better fill, because issue w az etc. changess
                {
                    seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE); //attempt expand above, can't scroll if empty space between entries is bigger than first load
                    caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                            if (seen)
                            {
                                //u8 text[20];
                                //u8 *buffer = AllocZeroed(sizeof(text));
                                //ReturnSpeciesNameConst(buffer, NationalPokedexNumToSpecies(j + 1));
                                sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(j + 1)].speciesName;
                                //free(buffer);

                            }
                            else
                            {
                                sPokedexScreenData->listItems[j].label = gText_5Dashes;
                            }
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                            ret++;

                        if (j > entryPos)
                            i++;

                }
                
            } 
            if (i == entryPos && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                for (j = i - DEX_MAX_SHOWN; j <= sPokedexScreenData->orderedDexCount; j++) //works
                {
                    seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                            if (seen)
                            {
                                //u8 text[20];
                                //u8 *buffer = AllocZeroed(sizeof(text));
                                //ReturnSpeciesNameConst(buffer, NationalPokedexNumToSpecies(j + 1));
                                sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(j + 1)].speciesName;
                                //free(buffer);

                            }
                            else
                            {
                                sPokedexScreenData->listItems[j].label = gText_5Dashes;
                            }
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                            ret++;

                        if (j > entryPos)
                            i++;

                }

            }
            else
            {
                sPokedexScreenData->listItems[i].label = gText_5Dashes;
                sPokedexScreenData->listItems[i].index = 0;
                //sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(i + 1); //fixed
                //ok didn't need that line, was just an issue with my scroll function now fixed
            }
            
            ret = KANTO_DEX_COUNT;
                    
        }
        
    }
        break;
    case DEX_ORDER_ATOZ: //look into making this load in sections?, think issue is would need to continuously retrigger this function?, not az but all national lists
    {
        
        for (i = 0; i <= NELEMS(gPokedexOrder_Alphabetical); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[i], FLAG_GET_CAUGHT, FALSE);

            if (seen && ret < NELEMS(gPokedexOrder_Alphabetical) && ret < NumSeen) //had to add extra change so its still limited to numseen/caught
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumSeen <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumSeen == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumSeen > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Alphabetical))
                    {
                        
                        if (seen)
                        {
                            

                            sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[i])].speciesName;                            
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumSeen > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (seen) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])].speciesName;   
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])].speciesName;   
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])].speciesName;   
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])].speciesName;   
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }  

        }
       //only kanto and national dex list should fill empty space with dashes, rest are supposed to ONLY show number you've seen or caught based on their condition
        
    }
        break;
    case DEX_ORDER_TYPE: //can't build automatically would need to loop entire species list MANY times, so would take forever
    { //now that I'm saving time I MAY be able to build with a function
        
        for (i = 0; i <= NELEMS(gPokedexOrder_Type); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[i], FLAG_GET_CAUGHT, FALSE);

            if (caught && ret < NELEMS(gPokedexOrder_Type) && ret < NumCaught)
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumCaught <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumCaught == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumCaught > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Type))
                    {
                        
                        if (caught)
                        {
                            
                            
                            
                            sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[i])].speciesName;   
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumCaught > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (caught) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])].speciesName; 
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])].speciesName; 
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])].speciesName; 
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])].speciesName; 
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])].speciesName; 
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }
        }
        
    }
        break; //order by type and weight, just wouldn't work with my changes/species expansion would require, going through and creating list by hand
    case DEX_ORDER_LIGHTEST:
    {    
        
        for (i = 0; i <= NELEMS(gPokedexOrder_Weight); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[i], FLAG_GET_CAUGHT, FALSE);

            if (caught && ret < NELEMS(gPokedexOrder_Weight) && ret < NumCaught)
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumCaught <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumCaught == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumCaught > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Weight))
                    {
                        
                        if (caught)
                        {
                            
                            
                            
                            sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[i])].speciesName; 
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumCaught > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (caught) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])].speciesName; 
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }
        }
        
    }
        break;
    case DEX_ORDER_SMALLEST:
    {
        
        for (i = 0; i <= NELEMS(gPokedexOrder_Height); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[i], FLAG_GET_CAUGHT, FALSE);

            if (caught && ret < NELEMS(gPokedexOrder_Height) && ret < NumCaught) //issue its not currently matching numcaught, works
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumCaught <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumCaught == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumCaught > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Height))
                    {
                        
                        if (caught)
                        {
                            
                            
                            
                            sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[i])].speciesName;
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumCaught > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (caught) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        
                        
                        
                        sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])].speciesName;
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }
        }
        
    }
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
    {
        
        for (i = 0; i <= NATIONAL_SPECIES_COUNT; i++) //ok this changes load times, and num entries on list,
        {
            
            if (entryPos <= DEX_MAX_SHOWN && i == entryPos)
                {
                    for (j = 0; j <= DEX_MAX_SHOWN; j++,i++)
                    {
                        seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                        caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);
                                if (seen)
                                {
                                    
                                    
                                    
                                    sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(j + 1)].speciesName;
                                    
                                }
                                else
                                {
                                    sPokedexScreenData->listItems[j].label = gText_5Dashes;
                                }
                                sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                                

                    }
                }

                if (entryPos > DEX_MAX_SHOWN && i == entryPos && entryPos < sPokedexScreenData->orderedDexCount - 4) //loop 10, over i -5 label & index
                {
                    for (j = i - DEX_MAX_SHOWN; j <= entryPos + DEX_MAX_SHOWN; j++) //changed to better fill, because issue w az etc. changess
                    {
                        seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE); //attempt expand above, can't scroll if empty space between entries is bigger than first load
                        caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                                if (seen)
                                {
                                    
                                    
                                    
                                    sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(j + 1)].speciesName;
                       
                                }
                                else
                                {
                                    sPokedexScreenData->listItems[j].label = gText_5Dashes;
                                }
                                sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                                

                            if (j > entryPos)
                                i++;

                    }
                    
                } 
                if (i == entryPos && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
                {
                    for (j = i - DEX_MAX_SHOWN; j <= sPokedexScreenData->orderedDexCount; j++) //works
                    {
                        seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                        caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);
                                if (seen)
                                {
                                    
                                    
                                    
                                    sPokedexScreenData->listItems[j].label = gBaseStats[NationalPokedexNumToSpecies(j + 1)].speciesName;
                             
                                }
                                else
                                {
                                    sPokedexScreenData->listItems[j].label = gText_5Dashes;
                                }
                                sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                                

                            if (j > entryPos)
                                i++;

                    }
                }
                else
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                }

                
                ret = NATIONAL_SPECIES_COUNT;
                

        }
        //hopefully works, changed nothing, still has memory issue
        //so at best its just completely unnecessary
        //idk whats going on now. changed both scroll functions to free memory
        //but didn't change, even undoing teh dex allignment changes didn't affect it
        //so idk what's going on, unless its literally just the dex spsecies value
        //which I have no idea what it should be
    }
        break; //changing  index affects, species number displayed and mon type displayed, not the nmae
    }


    return ret; //this would be end of new function

}





//HGSS EVO DEX STUFF - starts here
static void ResetEvoScreenDataStruct(void)
{
    u8 i;
    sPokedexScreenData->sEvoScreenData.numAllEvolutions = 0;
    //sPokedexScreenData->sEvoScreenData.numSeen = 0; //can remove, I changed the code to not need this
    sPokedexScreenData->sEvoScreenData.menuPos = 0;
    for (i = 0; i < 10; i++)
    {
        sPokedexScreenData->sEvoScreenData.targetSpecies[i] = 0;
        //sPokedexScreenData->sEvoScreenData.seen[i] = 0;
    }

}

//not using this either - go over files below not used
static void GetSeenFlagTargetSpecies(void)
{
    u8 i;
    u16 species;
    for (i = 0; i < sPokedexScreenData->sEvoScreenData.numAllEvolutions; i++)
    {
        species = sPokedexScreenData->sEvoScreenData.targetSpecies[i];
       /* if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_SEEN))
        {
            sPokedexScreenData->sEvoScreenData.seen[i] = TRUE;
            //sPokedexScreenData->sEvoScreenData.numSeen += 1;
        }*/

    }
}

/*Part of planned reorg for file clean up*/


//Blanked for now cuz too many undefined tings
static void Task_LoadEvolutionScreen(u8 taskId)
{
    switch (gMain.state)
    {
    //case 0:
    default:
        /*if (!gPaletteFade.active)
        {
            u16 r2;

            sPokedexScreenData->currentPage = EVO_SCREEN;
            gPokedexVBlankCB = gMain.vblankCallback;
            SetVBlankCallback(NULL);
            r2 = 0;
            if (gTasks[taskId].data[1] != 0)
                r2 += DISPCNT_OBJ_ON;
            if (gTasks[taskId].data[2] != 0)
                r2 |= DISPCNT_BG1_ON;
            ResetOtherVideoRegisters(r2);
            gMain.state = 1;
        }
        break;
    case 1:
        LoadTilesetTilemapHGSS(EVO_SCREEN);
        FillWindowPixelBuffer(WIN_INFO, PIXEL_FILL(0));
        PutWindowTilemap(WIN_INFO);
        CopyWindowToVram(WIN_INFO, 3);
        FillWindowPixelBuffer(WIN_NAVIGATION_BUTTONS, PIXEL_FILL(0));
        PutWindowTilemap(WIN_NAVIGATION_BUTTONS);
        CopyWindowToVram(WIN_NAVIGATION_BUTTONS, 3);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        gMain.state++;
        break;
    case 2:
        LoadScreenSelectBarMain(0xD);
        LoadPokedexBgPalette(sPokedexScreenData->isSearchResults);
        gMain.state++;
        break;
    case 3:
        if (gTasks[taskId].data[1] == 0) //and right below here
        {*/
            sPokedexScreenData->currentPage = EVO_SCREEN;
            ResetEvoScreenDataStruct();
            //Icon
            FreeMonIconPalettes(); //Free space for new pallete
            LoadMonIconPalette(sPokedexScreenData->dexSpecies); //Loads pallete for current mon
            PrintPreEvolutions(taskId, sPokedexScreenData->dexSpecies);
            #ifdef POKEMON_EXPANSION
                gTasks[taskId].data[4] = CreateMonIcon(sPokedexScreenData->dexSpecies, SpriteCB_MonIcon, 18 + 32*sPokedexScreenData->numPreEvolutions, 31, 4, 0); //Create pokemon sprite
            #else
                gTasks[taskId].data[4] = CreateMonIcon(sPokedexScreenData->dexSpecies, SpriteCB_MonIcon, 18 + 32*sPokedexScreenData->numPreEvolutions, 38, 4, 0, TRUE); //Create pokemon sprite
            #endif //handles icon for current mon, i.e selected species
            //EvoFormsPage_PrintNavigationButtons(); //HGSS_Ui Navigation buttons
            gSprites[gTasks[taskId].data[4]].oam.priority = 0;
        //}
        gMain.state = 4;
        //gMain.state++;
        break;
    case 4:
    //Print evo info and icons
    {
       
        u32 alreadyPrintedIcons[MAX_ICONS] = {0};
        u32 iconOffset = sPokedexScreenData->numPreEvolutions;
        gTasks[taskId].data[3] = 0;
        PrintEvolutionTargetSpeciesAndMethod(taskId, sPokedexScreenData->dexSpecies, 0, sPokedexScreenData->numPreEvolutions, alreadyPrintedIcons, &iconOffset);
        LoadSpritePalette(&gSpritePalette_Arrow);
        GetSeenFlagTargetSpecies();

        //believe means if has evolution
        if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)// && sPokedexScreenData->sEvoScreenData.numSeen != 0) //this is part that prevents arrow from showing for only 1 evo/mon seen
        {
            sPokedexScreenData->sEvoScreenData.arrowSpriteId = CreateSprite(&gSpriteTemplate_Arrow, 7, 88, 0);
            gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].animNum = 2;
        }
        gMain.state++;
    }
        break;
    case 5:
        {
        u32 preservedPalettes = 0;

        if (gTasks[taskId].data[2] != 0)
            preservedPalettes = 0x14; // each bit represents a palette index
        if (gTasks[taskId].data[1] != 0)
            preservedPalettes |= (1 << (gSprites[gTasks[taskId].data[4]].oam.paletteNum + 16));
        //BeginNormalPaletteFade(~preservedPalettes, 0, 16, 0, RGB_BLACK);
        //SetVBlankCallback(gPokedexVBlankCB);
        gMain.state++;
        }
        break;
    case 6:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        HideBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        gMain.state++;
        break;
    case 7:
        if (!gPaletteFade.active)
            gMain.state++;
        break;
    case 8:
        gMain.state++;
        break;
    case 9:
        //sPokedexScreenData->screenSwitchState = 0;
        gTasks[taskId].data[0] = 0;
        gTasks[taskId].data[1] = 0;
        gTasks[taskId].data[2] = 1;
        gTasks[taskId].func = Task_HandleEvolutionScreenInput;
        gMain.state = 0;
        break;
    }
}

static void Task_HandleEvolutionScreenInput(u8 taskId)
{
    //Switch to forms screen, Pokemon Expansion only (rhh)
    /*#ifdef POKEMON_EXPANSION
    if (JOY_NEW(START_BUTTON))
    {
        sPokedexScreenData->selectedScreen = FORMS_SCREEN;
        BeginNormalPaletteFade(0xFFFFFFEB, 0, 0, 0x10, RGB_BLACK);
        sPokedexScreenData->screenSwitchState = 3;
        gTasks[taskId].func = Task_SwitchScreensFromEvolutionScreen;
        PlaySE(SE_PIN);
    }
    #endif*/

    //tested in EE changes work fixes navigation
   // if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)// && sPokedexScreenData->sEvoScreenData.numSeen != 0)
    //{
        //u8 i;
        u8 base_y = 88;  //only used with moving arrow sprite and sprite start value is 58,  so think thsoe need to match
        u8 base_y_offset = 9;   //that was correct
        //u8 pos = sPokedexScreenData->sEvoScreenData.menuPos;
        //u8 max = sPokedexScreenData->sEvoScreenData.numAllEvolutions;
        if (sPokedexScreenData->sEvoScreenData.numAllEvolutions != 0)
        {
            if (JOY_NEW(DPAD_DOWN)) //dpad on evo doesn't work right, moving up works, but moving down only works when already down
            {
                /*while (TRUE)
                {
                    pos += 1;
                    if (pos >= max)
                        pos = 0;

                    if (sPokedexScreenData->sEvoScreenData.seen[pos] == TRUE)
                        break;
                }*/
                if (sPokedexScreenData->sEvoScreenData.menuPos == sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1)
                    sPokedexScreenData->sEvoScreenData.menuPos = 0;// = sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1;
                else
                    sPokedexScreenData->sEvoScreenData.menuPos += 1;

                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].pos1.y = base_y + base_y_offset * sPokedexScreenData->sEvoScreenData.menuPos;
                //sPokedexScreenData->sEvoScreenData.menuPos = pos; //store end position
            }
            else if (JOY_NEW(DPAD_UP))
            {
                if (sPokedexScreenData->sEvoScreenData.menuPos == 0)
                    sPokedexScreenData->sEvoScreenData.menuPos = sPokedexScreenData->sEvoScreenData.numAllEvolutions - 1;
                else
                    sPokedexScreenData->sEvoScreenData.menuPos -= 1;

                gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId].pos1.y = base_y + base_y_offset * sPokedexScreenData->sEvoScreenData.menuPos;
            }
        }

        //if not set, set, should only work first time hopefully, make sure to clear when done
        if (!(VarGet(VAR_0x408C)))
            VarSet(VAR_0x408C, sPokedexScreenData->dexSpecies);
            //store initial species page, if curr page species doesn;t equal var, set target sppecies to var
            //otherwise close
            //potentially clear var afterwards

        if (JOY_NEW(A_BUTTON))
        {
            u16 targetSpecies   = sPokedexScreenData->sEvoScreenData.targetSpecies[sPokedexScreenData->sEvoScreenData.menuPos];
            u16 dexNum          = SpeciesToNationalPokedexNum(targetSpecies);
            
            //if (sPokedexScreenData->sEvoScreenData.seen[sPokedexScreenData->sEvoScreenData.menuPos] == FALSE)
            //    PlaySE(SE_FAILURE);
           // else
            {
                sPokedexScreenData->dexSpecies = dexNum;
                //hmm I do need to know if its seen/caught before I load the page
                //sPokedexListItem->seen   = GetSetPokedexFlag(dexNum, FLAG_GET_SEEN);
                //sPokedexListItem->owned  = GetSetPokedexFlag(dexNum, FLAG_GET_CAUGHT);
                

                /*#ifdef POKEMON_EXPANSION
                    if (gFormSpeciesIdTables[targetSpecies] != NULL)
                        sPokedexScreenData->formSpecies = targetSpecies;
                    else
                        sPokedexScreenData->formSpecies = 0;
                #endif
                */
            

            
                //sPokedexScreenData->sEvoScreenData.fromEvoPage = TRUE;
                PlaySE(SE_PIN);
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                //gTasks[taskId].func = Task_LoadInfoScreenWaitForFade;
                gTasks[taskId].func = Task_LoadEvolutionScreen;
                
            }
        }
    //}

    //Exit to overview
    if (JOY_NEW(B_BUTTON))
    {   //if not on initial species page you loaded into dex with, load that page
        if (VarGet(VAR_0x408C) != sPokedexScreenData->dexSpecies)//NationalPokedexNumToSpeciesHGSS(sPokedexListItem->dexNum))
        {
            u16 targetSpecies   = VarGet(VAR_0x408C); //load initial dex page
            u16 dexNum          = SpeciesToNationalPokedexNum(targetSpecies);
            sPokedexScreenData->dexSpecies = dexNum;
            //sPokedexListItem->seen   = GetSetPokedexFlag(dexNum, FLAG_GET_SEEN);
            //sPokedexListItem->owned  = GetSetPokedexFlag(dexNum, FLAG_GET_CAUGHT);

            //sPokedexScreenData->sEvoScreenData.fromEvoPage = TRUE;
            PlaySE(SE_PC_OFF); //may remove sound use
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            //gTasks[taskId].func = Task_LoadInfoScreenWaitForFade;
            gTasks[taskId].func = Task_LoadEvolutionScreen;
        }
        else
        {
            VarSet(VAR_0x408C, 0);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_ExitEvolutionScreen;
            PlaySE(SE_PC_OFF);
            return;
        }
    } //this makes exit out completely, what i want is to store the species
    //of evo page you started on, so if stored species of current page doesn't match
    //pressing B will return to start page, so you can continue from what you started
    //want to be on the evo page as well
    //to ensure its not overwritten this field will start at 0,
    //should only write to the field if the value is 0

    //and since i want to fix dex icon phase by scrolling different evo paths
    //I'd need to separate the logic of evo page into diff tasks
    //make pressing up and down do the icon scroll
    //then if I press A when mon has evos, to check out
    //should send me to a different tasks function, 
    //which would start by populating the arrow, from there 
    //should work like its setup here.

    //Switch screens
    if ((JOY_NEW(DPAD_LEFT) || (JOY_NEW(L_BUTTON) && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR)))
    {
        sPokedexScreenData->currentPage = INFO_SCREEN;
        BeginNormalPaletteFade(0xFFFFFFEB, 0, 0, 0x10, RGB_BLACK);
        //sPokedexScreenData->screenSwitchState = 1;
        //gTasks[taskId].func = Task_SwitchScreensFromEvolutionScreen;
        PlaySE(SE_PIN);
    }
    if ((JOY_NEW(DPAD_RIGHT) || (JOY_NEW(R_BUTTON) && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR)))
    {
        //if (!sPokedexListItem->owned)
        //    PlaySE(SE_FAILURE);
        //else
        
        sPokedexScreenData->currentPage = AREA_SCREEN;
        BeginNormalPaletteFade(0xFFFFFFEB, 0, 0, 0x10, RGB_BLACK);
        //sPokedexScreenData->screenSwitchState = 2;
        //gTasks[taskId].func = Task_SwitchScreensFromEvolutionScreen;
        PlaySE(SE_PIN);
        
    }
}
//end of org functions

//split functions from DUke
static void HandleTargetSpeciesPrintText(u16 targetSpecies, u8 base_x, u8 base_y, u8 base_y_offset, u8 base_i)
{
    //bool8 seen = GetSetPokedexFlag(SpeciesToNationalPokedexNum(targetSpecies), FLAG_GET_SEEN);

    GetSpeciesName(gStringVar4, targetSpecies);
    //if (seen || !HGSS_HIDE_UNSEEN_EVOLUTION_NAMES)
        StringCopy(gStringVar3, gStringVar4); //evolution mon name
    //else
    //    StringCopy(gStringVar3, gText_ThreeQuestionMarks); //show questionmarks instead of name
    StringExpandPlaceholders(gStringVar3, sText_EVO_Name); //evolution mon name
    PrintInfoScreenTextSmall(gStringVar3, base_x, base_y + base_y_offset*base_i); //evolution mon name
}

//don't forget for mon that haven't been seen want to use blend from tm_case stuff to make icons siloutted
//as player would likely want to see bst, of said evo, for navigating to evo,
//make navigate to evo page, where you can press B to go back to info, to see BST
//if mon not seen make front pic of species greyed out w blend as well.
//if mon index doesn't exist, make sure exiting dex page goes back to initial species page, preferably from evo page
//same as its setup here.
//new order of page should be info-page, evo-page, area-page
//plan setup for evo page, is keep mon name at top, remove mon pic, and dex entry
//clear all entries from top menu, print species icon at bottom just above line,
//and think add  stat dist bars  on the evo page, either above, or at spot where mon pic usually is
#define MAX_LINE_ICONS 4  //4  //would fit wurmple line,base species + 4 icons
static void HandleTargetSpeciesPrintIcon(u8 taskId, u16 targetSpecies, u8 base_i, u8 times)
{
    u32 personality = DexScreen_GetDefaultPersonality(targetSpecies);

    //think can do without as only use for this is form dif from gender
    //my setup sets them as separate species so I shouldn't have any issue just using normal function
    //LoadMonIconPalettePersonality(targetSpecies, personality); //Loads pallete for current mon
    
    LoadMonIconPalette(targetSpecies); //try use base_i as value for num icons, check if greater than 1 use createicon at diff y value
    if (times > 6) //number of evos
    {
        if (base_i < MAX_LINE_ICONS)   //top line, else bottom line
            gTasks[taskId].data[5+base_i] = CreateMonIcon(targetSpecies, SpriteCB_MonIcon, 45 + 26*base_i, 36, 4, personality, TRUE); //Create pokemon sprite
        else
            gTasks[taskId].data[5+base_i] = CreateMonIcon(targetSpecies, SpriteCB_MonIcon, 45 + 26*(base_i - (MAX_LINE_ICONS + 1)), 60, 4, personality, TRUE); //Create pokemon sprite
    }       
        
    else
    {
        if (base_i < MAX_LINE_ICONS) //base i value 0 seems to be for first target species, not base species, so value 1 is for 2nd evo
            gTasks[taskId].data[5+base_i] = CreateMonIcon(targetSpecies, SpriteCB_MonIcon, 50 + 32*base_i, 36, 4, personality, TRUE); //Create pokemon sprite
        else
            gTasks[taskId].data[5+base_i] = CreateMonIcon(targetSpecies, SpriteCB_MonIcon, 50 + 32*(base_i - (MAX_LINE_ICONS + 1)), 60, 4, personality, TRUE); //Create pokemon sprite
    }//to get correct x value on print, do base_i - number icons already printed, so MAX_LINE_ICONS + 1
        
    gSprites[gTasks[taskId].data[5+base_i]].oam.priority = 0;
}//prints target evos, need make new logic for times, so prints to second line when onvalue above 5
//for new line will only need change here, not other createicon

//this si fr dex I already have caught symbols, I don't need it within the evo page
static void CreateCaughtBallEvolutionScreen(u16 targetSpecies, u8 x, u8 y, u16 unused)
{
    bool8 owned = GetSetPokedexFlag(SpeciesToNationalPokedexNum(targetSpecies), FLAG_GET_CAUGHT);
    
    /*if (owned) //doesn't sit right, would be cool but lack space already, will just port emerlad graphic
    {
        BlitBitmapToWindow(sPokedexScreenData->windowIds[1], sCaughtBall_Gfx, x, y-1, 8, 16);
    }    
    else*/
    {
        //FillWindowPixelRect(0, PIXEL_FILL(0), x, y, 8, 16); //not sure why this was even here
        PrintInfoScreenTextSmall(gText_OneDash, x+1, y-1); //may need more space between x
    }
    //look at logic for stat bars, since no longer using blit and insteadusing a sprite
    //logic will prob be more like that
}

static void ShowOrHideDexBallIconObj(u8 invisible)
{
    gSprites[sPokedexScreenData->ballIconSpriteId].invisible = invisible;
}

static void DestroyDexBallIconObj(void)
{
    // Redundant, as DestroySpriteAndFreeResources could've been used.
    DestroySpriteAndFreeResources2(&gSprites[sPokedexScreenData->ballIconSpriteId]);
}

static void HandlePreEvolutionSpeciesPrint(u8 taskId, u16 preSpecies, u16 species, u8 base_x, u8 base_y, u8 base_y_offset, u8 base_i)
{
    bool8 seen = GetSetPokedexFlag(SpeciesToNationalPokedexNum(preSpecies), FLAG_GET_SEEN);

    GetSpeciesName(gStringVar1, species);

    #ifdef POKEMON_EXPANSION
    if (sPokedexScreenData->sEvoScreenData.isMega)
        StringExpandPlaceholders(gStringVar3, sText_EVO_PreEvo_PE_Mega);
    else
    {
    #endif

    GetSpeciesName(gStringVar2, preSpecies);

    StringExpandPlaceholders(gStringVar3, sText_EVO_PreEvo); //evolution mon name

    #ifdef POKEMON_EXPANSION
    }
    #endif

    PrintInfoScreenTextSmall(gStringVar3, base_x, base_y + base_y_offset*base_i); //evolution mon name

    //remember base_i is somewhat tied to the number of icons/order of icons dispalyed so this could potentially be an issue if mon had more evos?
    //but should be good as it is, since its below the limit for printing sprites on next line but I guess wouldn't be difficult to add logic for that?
    if (base_i < MAX_LINE_ICONS) //don't know why this does this, also doesn't seem to be working for mankey evo/ratticate,the palette is messed up not icon print
    {
        LoadMonIconPalette(preSpecies); //Loads pallete for current mon
        #ifndef POKEMON_EXPANSION
            gTasks[taskId].data[5+base_i] = CreateMonIcon(preSpecies, SpriteCB_MonIcon, 18 + 32*base_i, 36, 4, 0, TRUE); //Create pokemon sprite
        #endif
        #ifdef POKEMON_EXPANSION
            gTasks[taskId].data[4+base_i] = CreateMonIcon(preSpecies, SpriteCB_MonIcon, 18 + 32*base_i, 38, 4, 0); //Create pokemon sprite
        #endif
        gSprites[gTasks[taskId].data[5+base_i]].oam.priority = 0;
    }
    else
    {
        LoadMonIconPalette(preSpecies); //Loads pallete for current mon
        #ifndef POKEMON_EXPANSION
            gTasks[taskId].data[5+base_i] = CreateMonIcon(preSpecies, SpriteCB_MonIcon, 18 + 32*(base_i - (MAX_LINE_ICONS + 1)), 60, 4, 0, TRUE); //Create pokemon sprite
        #endif
        #ifdef POKEMON_EXPANSION
            gTasks[taskId].data[4+base_i] = CreateMonIcon(preSpecies, SpriteCB_MonIcon, 18 + 32*(base_i - (MAX_LINE_ICONS + 1)), 60, 4, 0); //Create pokemon sprite
        #endif
        gSprites[gTasks[taskId].data[5+base_i]].oam.priority = 0;
    }
}

#define MAX_PRE_EVOS 3
//won't need state just do everything in one
static u8 AssignPreEvoData(u16 *speciesArrayOne, u16 *speciesArrayTwo, u16 species, u8 taskId, u8 base_x, u8 base_y, u8 base_y_offset, bool8 hasPrePreEvo)
{
    u8 numPreEvolutions = 0;   
    u8 numPrePreEvolves = 0;
    u32 i;

    //separated these out since were paired, 3 pre evos and 1 pre pre evo for each pre evo
    if (hasPrePreEvo) //speciesarray2 is prepreevos, so put that BEFORE array1
    {
        if (speciesArrayTwo[0] != SPECIES_NONE)
        {
            sPokedexScreenData->sEvoScreenData.targetSpecies[numPrePreEvolves] = speciesArrayTwo[0];
            numPrePreEvolves++;
            CreateCaughtBallEvolutionScreen(speciesArrayTwo[0], base_x - 9, base_y + base_y_offset*(numPrePreEvolves - 1), 0);
            HandlePreEvolutionSpeciesPrint(taskId, speciesArrayTwo[0], speciesArrayOne[0], base_x, base_y, base_y_offset, numPrePreEvolves - 1);
        } //since prepreevos branch will have to separate those out

        if (speciesArrayTwo[1] != SPECIES_NONE)
        {
            sPokedexScreenData->sEvoScreenData.targetSpecies[numPrePreEvolves] = speciesArrayTwo[1];
            numPrePreEvolves++;
            CreateCaughtBallEvolutionScreen(speciesArrayTwo[1], base_x - 9, base_y + base_y_offset*(numPrePreEvolves - 1), 0);
            HandlePreEvolutionSpeciesPrint(taskId, speciesArrayTwo[1], speciesArrayOne[1], base_x, base_y, base_y_offset, numPrePreEvolves - 1);
        } 

        if (speciesArrayTwo[2] != SPECIES_NONE) 
        {
            sPokedexScreenData->sEvoScreenData.targetSpecies[numPrePreEvolves] = speciesArrayTwo[2];
            numPrePreEvolves++;
            CreateCaughtBallEvolutionScreen(speciesArrayTwo[2], base_x - 9, base_y + base_y_offset*(numPrePreEvolves - 1), 0);
            HandlePreEvolutionSpeciesPrint(taskId, speciesArrayTwo[2], speciesArrayOne[2], base_x, base_y, base_y_offset, numPrePreEvolves - 1);
        } 

        for (i = 0; i < MAX_PRE_EVOS; i++)
        {
            if (speciesArrayOne[i] != SPECIES_NONE) 
            {
                numPreEvolutions++;
                sPokedexScreenData->sEvoScreenData.targetSpecies[numPrePreEvolves + (numPreEvolutions - 1)] = speciesArrayOne[i];
                CreateCaughtBallEvolutionScreen(speciesArrayOne[i], base_x - 9, base_y + base_y_offset*(numPrePreEvolves + (numPreEvolutions - 1)), 0);
                HandlePreEvolutionSpeciesPrint(taskId, speciesArrayOne[i], species, base_x, base_y, base_y_offset, numPrePreEvolves + (numPreEvolutions - 1));
            }
        }
    }
    else
    {
        for (i = 0; i < MAX_PRE_EVOS; i++)
        {
            if (speciesArrayOne[i] != SPECIES_NONE) 
            {
                numPreEvolutions++;
                sPokedexScreenData->sEvoScreenData.targetSpecies[numPreEvolutions - 1] = speciesArrayOne[i];
                CreateCaughtBallEvolutionScreen(speciesArrayOne[i], base_x - 9, base_y + base_y_offset*(numPreEvolutions - 1), 0);
                HandlePreEvolutionSpeciesPrint(taskId, speciesArrayOne[i], species, base_x, base_y, base_y_offset, numPreEvolutions - 1);
            }
        }
    }

    return (numPreEvolutions + numPrePreEvolves);
}


static u8 PrintPreEvolutions(u8 taskId, u16 species)
{
    u16 i;
    u16 j;

    u8 base_x = 13+8;
    u8 base_y = 1;//51;
    u8 base_y_offset = 9;
    u8 base_i = 0;
    u8 depth_x = 16;


    u16 * preEvolutionOne;
    u16 * preEvolutionTwo;
    u8 TotalPreEvos; //don't need below 2, put in other function instead, and asign this value from function, then set to numpreevos at bottom
    u8 numPreEvolutions = 0;    //numPreEvolutions = (PreEvolutions & 0xFF)
    u8 numPrePreEvolves = 0;    //numPrePreEvolves = ((PreEvolutions & 0xFF00) >> 8);
    //nvm mind don't need return 2 values can just have num evos etc set and assigned within other funciton and just return it
    //will keep num prepreevolves what that will do is tell otehr function if has them, but neither will be used in actually calculating placement of values or numpreevos
    u8 setslot0 = 0;
    u8 setslot1 = 0;
    u8 setslot2 = 0; //needed set to prevent garbage data in pre preevo setting

    #ifdef POKEMON_EXPANSION
    bool8 isMega = FALSE;
    sPokedexScreenData->sEvoScreenData.isMega = FALSE;
    #endif

    #ifdef TX_RANDOMIZER_AND_CHALLENGES
    if (gSaveBlock1Ptr->tx_Random_Evolutions || gSaveBlock1Ptr->tx_Random_EvolutionMethods)
        return 0;
    #endif

    preEvolutionOne = AllocZeroed(sizeof(*preEvolutionOne) * MAX_PRE_EVOS);
    preEvolutionTwo = AllocZeroed(sizeof(*preEvolutionTwo) * MAX_PRE_EVOS);

    if (DoesSpeciesHaveCosmeticForms(species))
        species = GetFormSpeciesId(species, 0);
    //Calculate previous evolution
    for (i = 0; i < NUM_SPECIES; i++) //would work but still has issue of 2nd pre evo calced after pre evo is checked, when I need it first
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(i);
        if (evolutions == NULL)
            continue;

        if (numPreEvolutions == MAX_PRE_EVOS)
            break;

        for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
        {
            if (evolutions[j].targetSpecies == species)
            {
                preEvolutionOne[numPreEvolutions] = i; //keep here for building species array
                numPreEvolutions++; //fixed issue moved here to fit all pre evos without replacement //will not matter
                
                #ifdef POKEMON_EXPANSION
                    if (evolutions[j].method == EVO_MEGA_EVOLUTION)
                    {
                        CopyItemName(evolutions[j].param, gStringVar2); //item
                        isMega = TRUE;
                    }
                #endif
                break;
            }
        }
    }

    #ifdef POKEMON_EXPANSION
    if (isMega)
    {
        sPokedexScreenData->numPreEvolutions = numPreEvolutions;
        sPokedexScreenData->sEvoScreenData.numAllEvolutions += numPreEvolutions;
        sPokedexScreenData->sEvoScreenData.isMega = isMega;

        CreateCaughtBallEvolutionScreen(preEvolutionOne, base_x - 9 - 8, base_y + base_y_offset*(numPreEvolutions - 1), 0);
        HandlePreEvolutionSpeciesPrint(taskId, preEvolutionOne, species, base_x - 8, base_y, base_y_offset, numPreEvolutions - 1);
        return numPreEvolutions;
    }
    #endif

    //Calculate if previous evolution also has a previous evolution
    if (numPreEvolutions != 0)
    {
        for (i = 0; i < NUM_SPECIES; i++)
        {
            const struct Evolution *evolutions = GetSpeciesEvolutions(i);
            if (evolutions == NULL)
                continue;
            
            if (numPrePreEvolves == MAX_PRE_EVOS)
                break;

            for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
            {
                
                if (evolutions[j].targetSpecies == preEvolutionOne[0]) //in main function will need compare against all 3, do if else if 
                {
                    if (!(setslot0)) //to ensure doesn't repeat, ok that fixed it
                    {
                    preEvolutionTwo[0] = i;
                    numPrePreEvolves++;
                    setslot0 = TRUE;
                    }
                    break;
                }

                else if (evolutions[j].targetSpecies == preEvolutionOne[1]) //in main function will need compare against all 3, do if else if 
                {
                    if (!(setslot1))
                    {
                    preEvolutionTwo[1] = i;
                    numPrePreEvolves++;
                    setslot1 = TRUE;
                    }
                    break;
                }

                else if (evolutions[j].targetSpecies == preEvolutionOne[2]) //in main function will need compare against all 3, do if else if 
                {
                    if (!(setslot2))
                    {
                    preEvolutionTwo[2] = i;
                    numPrePreEvolves++;
                    setslot2 = TRUE;
                    }
                    break;
                }
            }
        }
    }

    //instead of needing to take i, think I can loop for sizeof preevolutiontwo, 
    //and assign species if not 0, and increment numPrePreEvolves there
    //this function will return numPreEvos,
    //since is array think need pointer for this
    //don't need a base_i value that's set based on num pre evos, even though function has base_i value for no reason
    //I'll assign species to preevolution1 and 2 arrays in main function and increment 
    TotalPreEvos = AssignPreEvoData(preEvolutionOne, preEvolutionTwo, species, taskId, base_x, base_y, base_y_offset, numPrePreEvolves);


    /*What this is doing by only storing targetspecies 0 and 1
    is working within the limitation of the existing system.
    As it is by default there is only one pre evo species that can evolve into a target evolution
    i.e only pichu goes into pikachu etc.
    and that works until you change things
    which is why pikachu broke things, as soon as I had pichu and spiky pichu
    2 different species evolving into the same mon the whole thing fell apart
    
    think I can make it work will just have to do how it was and set everything outside the loop
    all I need to do for that ischange preevolutionone and preevolutiontwo to arrays so each field stores about 3 mon
    then think make a function to store the numpreevo pre preevo stuff and assign target species based on taht*/

    sPokedexScreenData->numPreEvolutions = TotalPreEvos;
    sPokedexScreenData->sEvoScreenData.numAllEvolutions += sPokedexScreenData->numPreEvolutions;

    Free(preEvolutionTwo);
    Free(preEvolutionOne);

    return sPokedexScreenData->numPreEvolutions;
}

#define EVO_SCREEN_LVL_DIGITS 2

static u8 PrintEvolutionTargetSpeciesAndMethod(u8 taskId, u16 species, u8 depth, u8 base_i_offset, u32 alreadyPrintedIcons[], u32 *base_icon_i_offSet)
{
    u16 i;
    const struct MapHeader *mapHeader;
    u16 NexttargetSpecies = 0;
    u16 currentTargetSpecies = 0;
    u16 targetSpecies;

    u16 item;

    bool8 left = TRUE;
    u8 base_x = 13+8;
    u8 base_x_offset = 54+8;
    u8 base_y = 1;//51;
    u8 base_y_offset = 9;
    u8 base_i = 0;
    u8 times = 0; //times gets number of direct evolution for the species
    u8 depth_x = 16;
    bool8 NoEvo = FALSE;
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);


    //found form view evo page has the task input I need, it doesn't create an arrow until you press A
    #ifdef POKEMON_EXPANSION
    if (sPokedexScreenData->sEvoScreenData.isMega)
        return 0;
    #endif


    GetSpeciesName(gStringVar1, species);

    //if (species == SPECIES_EEVEE)
      //  isEevee = TRUE;

    #ifdef TX_RANDOMIZER_AND_CHALLENGES
    if (EvolutionBlockedByEvoLimit(species)) //No Evos already previously checked
        species = SPECIES_NONE;
    else if (gSaveBlock1Ptr->tx_Random_EvolutionMethods)
        species = GetSpeciesRandomSeeded(species, TX_RANDOM_T_EVO_METH, 0);
    #endif

    if (NoEvo == FALSE)
    {
        if (evolutions[0].method == 0)
        {
            //If there are no evolutions print text - took fix from Snead69 (snead is Duke lol), was more efficient than my own.
            //learned depth is the indentation for the print, depth 0 is first value
            if (depth == 0 && base_i_offset == 0) //this part works but because of recursion evolution species keeps changing, need to limit to say does NOT have pre evo
            {    
                StringExpandPlaceholders(gStringVar4, sText_EVO_NONE);
                PrintInfoScreenTextSmall(gStringVar4, base_x-7-7, base_y + base_y_offset*base_i_offset);        
                NoEvo = TRUE;
            }
                return 0;
        }//ok thank god this works, pretty sure reason couldn't use evo 0 .mehhod is 0 is because it was already inside evo == null, so basically same thing
    } //duh

    if (NoEvo == FALSE)
    {


         //Calculate number of possible direct evolutions (e.g. Eevee has 5 but torchic has 1)
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (evolutions[i].method != EVOLUTIONS_END)
            {
                if (evolutions[0].method != 0) //think this is just extra protection
                times++;
                
            }
        }
        gTasks[taskId].data[3] = times;
        sPokedexScreenData->sEvoScreenData.numAllEvolutions += times;


    //If there are evolutions find out which and print them 1 by 1
    for (i = 0; i < times; i++)
    {
        int j;
        base_i = i + base_i_offset;
        left = !left;

        if (evolutions[i + 1].method != 0) //shoudl be fine scince this is just for printing icons
        {
            currentTargetSpecies = evolutions[i].targetSpecies;
            NexttargetSpecies = evolutions[i + 1].targetSpecies;
        }
        targetSpecies = evolutions[i].targetSpecies;

        sPokedexScreenData->sEvoScreenData.targetSpecies[base_i] = currentTargetSpecies;
        #ifdef TX_DIFFICULTY_CHALLENGES_USED
            if (gSaveBlock1Ptr->txRandEvolutions && currentTargetSpecies != SPECIES_NONE) //tx_difficulty_challenges
                currentTargetSpecies = GetSpeciesRandomSeeded(currentTargetSpecies, TX_RANDOM_T_EVO, 0);
        #endif

        if (evolutions[0].method != 0 || depth != 0) //should allow print if mon is first mon printed w no evos, i.e smeargle etc.
        {
            CreateCaughtBallEvolutionScreen(currentTargetSpecies, base_x + depth_x*depth-9, base_y + base_y_offset*base_i, 0);
            HandleTargetSpeciesPrintText(currentTargetSpecies, base_x + depth_x*depth, base_y, base_y_offset, base_i);
        }

        for (j = 0; j < MAX_ICONS; j++)
        {
            if (alreadyPrintedIcons[j] == targetSpecies)
                break;
            if (alreadyPrintedIcons[j] == SPECIES_NONE)
            { 
                HandleTargetSpeciesPrintIcon(taskId, targetSpecies, *base_icon_i_offSet, times);
                alreadyPrintedIcons[j] = targetSpecies;
                (*base_icon_i_offSet)++;
                break;
            }
        }
        
        switch (evolutions[i].method)
        {
        case EVO_FRIENDSHIP:
            ConvertIntToDecimalStringN(gStringVar2, 220, STR_CONV_MODE_LEADING_ZEROS, 3); //friendship value
            StringExpandPlaceholders(gStringVar4, sText_EVO_FRIENDSHIP );
            break;
        case EVO_FRIENDSHIP_DAY:
            StringExpandPlaceholders(gStringVar4, sText_EVO_FRIENDSHIP_DAY );
            break;
        case EVO_FRIENDSHIP_NIGHT:
            StringExpandPlaceholders(gStringVar4, sText_EVO_FRIENDSHIP_NIGHT );
            break;
        case EVO_LEVEL:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL );
            break;
        case EVO_TRADE:
            StringExpandPlaceholders(gStringVar4, sText_EVO_TRADE );
            break;
        case EVO_TRADE_ITEM:
            item = evolutions[i].param; //item
            CopyItemName(item, gStringVar2); //item
            StringExpandPlaceholders(gStringVar4, sText_EVO_TRADE_ITEM );
            break;
        case EVO_ITEM:
            item = evolutions[i].param;
            CopyItemName(item, gStringVar2);
            StringExpandPlaceholders(gStringVar4, sText_EVO_ITEM );
            break;
        case EVO_LEVEL_ATK_GT_DEF:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_ATK_GT_DEF );
            break;
        case EVO_LEVEL_ATK_EQ_DEF:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_ATK_EQ_DEF );
            break;
        case EVO_LEVEL_ATK_LT_DEF:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_ATK_LT_DEF );
            break;
        case EVO_LEVEL_SILCOON:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_SILCOON );
            break;
        case EVO_LEVEL_CASCOON:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_CASCOON );
            break;
        case EVO_LEVEL_NINJASK:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_NINJASK );
            break;
        case EVO_LEVEL_SHEDINJA:
            ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
            StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_SHEDINJA );
            break;
        case EVO_BEAUTY:
            ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param, STR_CONV_MODE_LEADING_ZEROS, 3); //beauty
            StringExpandPlaceholders(gStringVar4, sText_EVO_BEAUTY );
            break;
        //#ifdef POKEMON_EXPANSION
            case EVO_LEVEL_FEMALE:
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_FEMALE );
                break;
            case EVO_LEVEL_MALE:
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_MALE );
                break;
            case EVO_LEVEL_NIGHT:
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_NIGHT );
                break;
            case EVO_LEVEL_DAY:
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_DAY );
                break;
            case EVO_LEVEL_DUSK:
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_DUSK );
                break;
            case EVO_ITEM_HOLD_DAY:
                item = evolutions[i].param; //item
                CopyItemName(item, gStringVar2); //item
                StringExpandPlaceholders(gStringVar4, sText_EVO_ITEM_HOLD_DAY );
                break;
            case EVO_ITEM_HOLD_NIGHT:
                item = evolutions[i].param; //item
                CopyItemName(item, gStringVar2); //item
                StringExpandPlaceholders(gStringVar4, sText_EVO_ITEM_HOLD_NIGHT );
                break;
            case EVO_MOVE:
                StringCopy(gStringVar2, gMoveNames[evolutions[i].param]);
                StringExpandPlaceholders(gStringVar4, sText_EVO_MOVE );
                break;
            case EVO_MOVE_TYPE:
                StringCopy(gStringVar2, gTypeNames[evolutions[i].param]);
                StringExpandPlaceholders(gStringVar4, sText_EVO_MOVE_TYPE );
                break;
            case EVO_MAPSEC:
                GetMapName(gStringVar2, evolutions[i].param, 0);
                StringExpandPlaceholders(gStringVar4, sText_EVO_MAPSEC );
                break;
            case EVO_ITEM_MALE:
                item = evolutions[i].param; //item
                CopyItemName(item, gStringVar2); //item
                StringExpandPlaceholders(gStringVar4, sText_EVO_ITEM_MALE );
                break;
            case EVO_ITEM_FEMALE:
                item = evolutions[i].param; //item
                CopyItemName(item, gStringVar2); //item
                StringExpandPlaceholders(gStringVar4, sText_EVO_ITEM_FEMALE );
                break;
            case EVO_LEVEL_RAIN: //this also needs level parm
                //if (j == WEATHER_RAIN || j == WEATHER_RAIN_THUNDERSTORM || j == WEATHER_DOWNPOUR)
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_RAIN);
                break;
            case EVO_SPECIFIC_MON_IN_PARTY:
                GetSpeciesName(gStringVar2, evolutions[i].param);
                StringExpandPlaceholders(gStringVar4, sText_EVO_SPECIFIC_MON_IN_PARTY );
                break;
            case EVO_LEVEL_DARK_TYPE_MON_IN_PARTY: //this needs level parm
                ConvertIntToDecimalStringN(gStringVar3, ((evolutions[i].param & 0xFF00) >> 8), STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param & 0xFF, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS); //level
                StringExpandPlaceholders(gStringVar4, sText_EVO_LEVEL_DARK_TYPE_MON_IN_PARTY );
                break;
            case EVO_TRADE_SPECIFIC_MON:
                GetSpeciesName(gStringVar2, evolutions[i].param);
                StringExpandPlaceholders(gStringVar4, sText_EVO_TRADE_SPECIFIC_MON );
                break;
            case EVO_SPECIFIC_MAP:  //not using this method, so doesn't matter its not right
                mapHeader = Overworld_GetMapHeaderByGroupAndId(evolutions[i].param >> 8, evolutions[i].param & 0xFF);
                GetMapName(gStringVar2, mapHeader->regionMapSectionId, 0);
                StringExpandPlaceholders(gStringVar4, sText_EVO_SPECIFIC_MAP );
                break; //need add on to this with, my custom methods,can remove trade methods as well
            /*New Additions*/
            case EVO_HIGH_RICHES:
                ConvertIntToDecimalStringN(gStringVar2, evolutions[i].param, STR_CONV_MODE_LEADING_ZEROS, EVO_SCREEN_LVL_DIGITS);
                StringExpandPlaceholders(gStringVar4, sText_EVO_HIGH_RICHES ); //hope got right
                break;
        //#endif
        default:
            StringExpandPlaceholders(gStringVar4, sText_EVO_UNKNOWN );
            break;
        }//Switch end

        if (evolutions[0].method != 0)
        {
            //rough estiate but believe about +5 needed for each additional char?
            if (StringLength(gBaseStats[targetSpecies].speciesName) <= 8) //think string length removes terminator so need -1 from speciesname value
                PrintInfoScreenTextSmall(gStringVar4, base_x + depth_x*depth+base_x_offset - 15, base_y + base_y_offset*base_i); //Print actual instructions
            else if (StringLength(gBaseStats[targetSpecies].speciesName) <= 10)
                PrintInfoScreenTextSmall(gStringVar4, base_x + depth_x*depth+base_x_offset - 5, base_y + base_y_offset*base_i); //Print actual instructions
            else
                PrintInfoScreenTextSmall(gStringVar4, base_x + depth_x*depth+base_x_offset + 5, base_y + base_y_offset*base_i); //Print actual instructions
        }
            if (currentTargetSpecies != NexttargetSpecies) //this makes text print how I want,
                base_i_offset += PrintEvolutionTargetSpeciesAndMethod(taskId, currentTargetSpecies, depth+1, base_i+1, alreadyPrintedIcons, base_icon_i_offSet); //recursive call
    }//For loop end
            //learned depth is the indentation for the print, depth 0 is first value

    } //attempt skip print for null

    return times;//current issue, doens't remove pre evo after navigate to stage 3 evo
    //when press B after checkign Evos and reloads page, causes some form of leak/overflow
    //plan navigate to 15 don't reload window all need do is, update stat bar and remove arrow 

    //workaround for mid evo break if naviagate to second evo, tehnback tofirst and THEN to 3rd evo, 
    //the graphic doesn't break

    //has to hit B and go to info page before changing selected evo stage

    //caught monicon doesn't appear to load, also graphic isnt' right with background color for fr dex

    //nothre error of overflow seems to come from moving back and forth between evo page to area page
}

static void Task_SwitchScreensFromEvolutionScreen(void) //was u8 taskId
{
    u8 i;
    u8 taskId = 0;
    //if (!gPaletteFade.active)
    //{
        FreeMonIconPalettes();                                          //Destroy pokemon icon sprite
        DestroyMonIcon(&gSprites[gTasks[taskId].data[4]]); //Destroy pokemon icon sprite
         //don't konw why but with mothod != 0 change needed add plus 1 here to clear final evo
         //ok believe identified problem, times/ num evos to display is menat to be stored in data[3]
         //but it seems its getting reset before it gets here, so it can't clean the icons
         //and I believe its only reset in drawmonevo page, soI need to set this BEFORE I navigate to that

        // i think this'll work now, made base icon 4, and extra start on 5
        //since this starts at i value 1, it'll begin removing from 5 on up
        //no idea why I need it but using +1 works/helps
        //ok this works phew
        //figured should be able to just use numpreevoltuoins since that's used for counting icons 
        //but doesn't work facepalm
        //FUCKING HELL this works for clearing pre evo, but does'nt work for regular evos
        //the above one works for normal evos but DOESN'T work for pre evos!!!
        //for (i = 0; i <= sPokedexScreenData->numPreEvolutions; i++) 

        //ok maybe this will work, if times is num evos, and pre evos is strictly for pre evolution?
        //should work same if there are no pre evos but increase if there are?
        //OH MY GOD THAT ACTUALLY WORKED YESS!!!!
        for (i = 0; i <= (gTasks[taskId].data[3] + sPokedexScreenData->numPreEvolutions + 4); i++) //entire issue is using int to loop to clear value        
        {
            DestroyMonIcon(&gSprites[gTasks[taskId].data[5+i]]); //Destroy pokemon icon sprite
        }
        
        //FreeAndDestroyMonPicSprite(gTasks[taskId].data[12]); //idk what to do w this
        DestroySprite(&gSprites[gTasks[taskId].data[4]]); //changed from 4 to new data value and now this works to clear base icon
        DestroySprite(&gSprites[sPokedexScreenData->sEvoScreenData.arrowSpriteId]); //clear the arrow
        
        /*switch (sPokedexScreenData->screenSwitchState)
        {
        case 1:
            gTasks[taskId].func = Task_LoadStatsScreen;
            break;
        case 2:
            gTasks[taskId].func = Task_LoadCryScreen;
            break;
        #ifdef POKEMON_EXPANSION
            case 3:
                gTasks[taskId].func = Task_LoadFormsScreen;
                break;
        #endif
        default:
            gTasks[taskId].func = Task_LoadInfoScreen;
            break;
        }*/



    //}
}

static void Task_ExitEvolutionScreen(u8 taskId)
{
    u8 i;
    if (!gPaletteFade.active)
    {
        FreeMonIconPalettes();                                          //Destroy pokemon icon sprite
        DestroyMonIcon(&gSprites[gTasks[taskId].data[4]]); //Destroy pokemon icon sprite
        for (i = 1; i <= gTasks[taskId].data[3]; i++)
        {
            DestroyMonIcon(&gSprites[gTasks[taskId].data[4+i]]); //Destroy pokemon icon sprite
        }
        //DestroyMonIcon(gTasks[taskId].data[4]); // idk what to do with this
        //FreeInfoScreenWindowAndBgBuffers();
        DestroyTask(taskId);
    }
}

static void PrintInfoScreenTextSmall(const u8* str, u8 left, u8 top)
{
    u8 color[3];
    color[0] = TEXT_COLOR_TRANSPARENT;  //background shadow
    color[1] = TEXT_BLACK_maybe; //text color   
    color[2] = TEXT_COLOR_DARK_GREY;   //high light shadow  - think this works

    AddTextPrinterParameterized4(sPokedexScreenData->windowIds[2], 0, left, top, 0, 0, color, 0, str);
}//plan print into dex entry window so not using window 0

//not used?
static void FreeInfoScreenWindowAndBgBuffers(void)
{
    void *tilemapBuffer;

    FreeAllWindowBuffers();
    tilemapBuffer = GetBgTilemapBuffer(0);
    if (tilemapBuffer)
        Free(tilemapBuffer);
    tilemapBuffer = GetBgTilemapBuffer(1);
    if (tilemapBuffer)
        Free(tilemapBuffer);
    tilemapBuffer = GetBgTilemapBuffer(2);
    if (tilemapBuffer)
        Free(tilemapBuffer);
    tilemapBuffer = GetBgTilemapBuffer(3);
    if (tilemapBuffer)
        Free(tilemapBuffer);
}