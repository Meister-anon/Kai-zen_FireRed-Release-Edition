#include "global.h"
#include "gflib.h"
#include "decompress.h"
#include "task.h"
#include "blend_palette.h"
#include "text_window.h"
#include "menu.h"
#include "help_system.h"
#include "new_menu_helpers.h"
#include "event_scripts.h"
#include "scanline_effect.h"
#include "pokeball.h"
#include "event_data.h"
#include "naming_screen.h"
#include "math_util.h"
#include "overworld.h"
#include "random.h"
#include "data.h"
#include "constants/songs.h"

#define INTRO_SPECIES SPECIES_NIDORAN_F

enum
{
    WIN_INTRO_TEXTBOX,
    WIN_INTRO_BOYGIRL,
    WIN_INTRO_YESNO,
    WIN_INTRO_NAMES,
    NUM_INTRO_WINDOWS,
};

struct OakSpeechResources
{
    void * oakSpeechBackgroundTiles;
    void * trainerPicTilemapBuffer;
    void * pikachuIntroTilemap;
    void *unused1;
    u16 hasPlayerBeenNamed;
    u16 currentPage;
    u16 windowIds[NUM_INTRO_WINDOWS]; //don't understand this, thought was amount of windows
    u8 textColor[3]; //but seems increasing or reducing has no affect on it
    u8 textSpeed;
    u8 unused2[0x1800];
    u8 bg2TilemapBuffer[0x400];
    u8 bg1TilemapBuffer[0x800];
}; //size=0x2420

static EWRAM_DATA struct OakSpeechResources * sOakSpeechResources = NULL;


static void Task_NewGameScene(u8 taskId);

static void ControlsGuide_LoadPage1(void);
static void Task_ControlsGuide_HandleInput(u8 taskId);
static void Task_ControlsGuide_ChangePage(u8 taskId);
static void Task_ControlsGuide_Clear(u8 taskId);
static void Task_OakSpeech6(u8 taskId);
static void Task_OakSpeech7(u8 taskId);
static void Task_OakSpeech8(u8 taskId);
static void Task_OakSpeech9(u8 taskId);
static void Task_OakSpeech10(u8 taskId);
static void Task_OakSpeech10(u8 taskId);
static void Task_OakSpeech11(u8 taskId);
static void Task_OakSpeech12(u8 taskId);
static void Task_OakSpeech13(u8 taskId);
static void Task_OakSpeech14(u8 taskId);
static void Task_OakSpeech15(u8 taskId);
static void Task_OakSpeech16(u8 taskId);
static void Task_OakSpeech17(u8 taskId);
static void Task_OakSpeech18(u8 taskId);
static void Task_OakSpeech19(u8 taskId);
static void Task_OakSpeech20(u8 taskId);
static void Task_OakSpeech21(u8 taskId);
static void Task_OakSpeech22(u8 taskId);
static void Task_OakSpeech23(u8 taskId);
static void Task_OakSpeech24(u8 taskId);
static void Task_OakSpeech29(u8 taskId);
static void Task_OakSpeech25(u8 taskId);
static void Task_OakSpeech26(u8 taskId);
static void Task_OakSpeech27(u8 taskId);
static void Task_OakSpeech28(u8 taskId);
static void Task_OakSpeech30(u8 taskId);
static void Task_OakSpeech31(u8 taskId);
static void Task_OakSpeech32(u8 taskId);
static void Task_OakSpeech34(u8 taskId);
static void Task_OakSpeech3C(u8 taskId); //new version of 34 for the player, to lead into 35
static void Task_OakSpeech33(u8 taskId);
static void Task_OakSpeech35(u8 taskId);
static void Task_OakSpeech36(u8 taskId);
static void Task_OakSpeech37(u8 taskId);
static void Task_OakSpeech38(u8 taskId);
static void Task_OakSpeech38_3(u8 taskId);
static void Task_OakSpeech39(u8 taskId);
static void Task_OakSpeech38_1(u8 taskId);
static void Task_OakSpeech38_sub1(u8 taskId);
static void Task_OakSpeech38_2(u8 taskId);
static void Task_OakSpeech38_sub2(u8 taskId);
static void Task_OakSpeech40(u8 taskId);
static void Task_OakSpeech41(u8 taskId);
static void Task_OakSpeech42(u8 taskId);

static void CB2_ReturnFromNamingScreen(void);
static void CreateNidoranFSprite(u8 taskId);
static void CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(u8 taskId, u8 state);
static void DestroyLinkedPikaOrGrassPlatformSprites(u8 taskId, u8 state);
static void LoadOaksSpeechTrainerPic(u16 whichPic, u16 tileOffset);
static void DestroyOaksSpeechTrainerPic(void);
static void CreateFadeInTask(u8 taskId, u8 state);
static void CreateFadeOutTask(u8 taskId, u8 state);
static void PrintNameChoiceOptions(u8 taskId, u8 state);
static void GetDefaultName(u8 hasPlayerBeenNamed, u8 namePick);
static void GetRandomPlayerName(u8 hasPlayerBeenNamed, u8 namePick);

extern const u8 gText_Controls[];
extern const u8 gText_ABUTTONNext[];
extern const u8 gText_ABUTTONNext_BBUTTONBack[];
extern const u8 gText_Boy[];
extern const u8 gText_Girl[];

extern const struct OamData gOamData_AffineOff_ObjBlend_32x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x8;

ALIGNED(4) static const u16 sHelpDocsPalette[] = INCBIN_U16("graphics/oak_speech/help_docs_palette.gbapal");
static const u32 sOakSpeechGfx_GameStartHelpUI[] = INCBIN_U32("graphics/oak_speech/game_start_help_ui.4bpp.lz");
static const u32 sNewGameAdventureIntroTilemap[] = INCBIN_U32("graphics/oak_speech/new_game_adventure_intro_tilemap.bin.lz");
static const u32 sOakSpeechGfx_SolidColors[] = INCBIN_U32("graphics/oak_speech/solid_colors.4bpp.lz");
static const u32 sOakSpeech_BackgroundTilemap[] = INCBIN_U32("graphics/oak_speech/background_tilemap.bin.lz");
static const u16 sHelpDocsPage2Tilemap[] = INCBIN_U16("graphics/oak_speech/help_docs_page2_tilemap.bin");
static const u16 sHelpDocsPage3Tilemap[] = INCBIN_U16("graphics/oak_speech/help_docs_page3_tilemap.bin");
static const u16 sOakSpeechGfx_LeafPal[] = INCBIN_U16("graphics/oak_speech/leaf_pal.gbapal");
static const u32 sOakSpeechGfx_LeafPic[] = INCBIN_U32("graphics/oak_speech/leaf_pic.8bpp.lz");
static const u16 sOakSpeechGfx_RedPal[] = INCBIN_U16("graphics/oak_speech/red_pal.gbapal");
static const u32 sOakSpeechGfx_RedPic[] = INCBIN_U32("graphics/oak_speech/red_pic.8bpp.lz");
static const u16 sOakSpeechGfx_OakPal[] = INCBIN_U16("graphics/oak_speech/oak_pal.gbapal");
static const u32 sOakSpeechGfx_OakPic[] = INCBIN_U32("graphics/oak_speech/oak_pic.8bpp.lz");
static const u16 sOakSpeechGfx_RivalPal[] = INCBIN_U16("graphics/oak_speech/rival_pal.gbapal");
static const u32 sOakSpeechGfx_RivalPic[] = INCBIN_U32("graphics/oak_speech/rival_pic.8bpp.lz");
static const u16 sOakSpeech_Platform_Pal[] = INCBIN_U16("graphics/oak_speech/grass_platform_palette.gbapal");
static const u16 sPikachuIntro_Pikachu_Pal[] = INCBIN_U16("graphics/oak_speech/pika_palette.gbapal");
static const u32 sOakSpeechGfx_GrassPlatform[] = INCBIN_U32("graphics/oak_speech/grass_platform.4bpp.lz");
static const u32 sOakSpeechGfx_Pika1[] = INCBIN_U32("graphics/oak_speech/pika1.4bpp.lz");
static const u32 sOakSpeechGfx_Pika2[] = INCBIN_U32("graphics/oak_speech/pika2.4bpp.lz");
static const u32 sOakSpeechGfx_PikaEyes[] = INCBIN_U32("graphics/oak_speech/pika_eyes.4bpp.lz");

static const struct BgTemplate sBgTemplates[3] = {
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }, {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x000
    }, {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 1,
        .paletteMode = 1,
        .priority = 1,
        .baseTile = 0x000
    }
};

enum
{
    CONTROLS_GUIDE_PAGE_1_WINDOW,
    NUM_CONTROLS_GUIDE_PAGE_1_WINDOWS,
};

static const struct WindowTemplate sHelpDocsWindowTemplates1[] = {
    
    [CONTROLS_GUIDE_PAGE_1_WINDOW] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x00,
        .tilemapTop = 0x03,
        .width = 0x1e,
        .height = 0xf,
        .paletteNum = 0x0f,
        .baseBlock = 0x0001
    }, DUMMY_WIN_TEMPLATE
};

enum
{
    CONTROLS_GUIDE_PAGES_2_3_WINDOW_TOP,
    CONTROLS_GUIDE_PAGES_2_3_WINDOW_MIDDLE,
    CONTROLS_GUIDE_PAGES_2_3_WINDOW_BOTTOM,
    NUM_CONTROLS_GUIDE_PAGES_2_3_WINDOWS,
};


static const struct WindowTemplate sHelpDocsWindowTemplates2[] = {
    
    [CONTROLS_GUIDE_PAGES_2_3_WINDOW_TOP] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x06,
        .tilemapTop = 0x03,
        .width = 0x18,
        .height = 0x06,
        .paletteNum = 0x0f,
        .baseBlock = 0x0001
    }, 
    
    [CONTROLS_GUIDE_PAGES_2_3_WINDOW_MIDDLE] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x06,
        .tilemapTop = 0x0a,
        .width = 0x18,
        .height = 0x04,
        .paletteNum = 0x0f,
        .baseBlock = 0x0092
    }, 
    
    [CONTROLS_GUIDE_PAGES_2_3_WINDOW_BOTTOM] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x06,
        .tilemapTop = 0x0f,
        .width = 0x18,
        .height = 0x04,
        .paletteNum = 0x0f,
        .baseBlock = 0x00f3
    }, 
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sHelpDocsWindowTemplates3[] = {
    
    [CONTROLS_GUIDE_PAGES_2_3_WINDOW_TOP] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x06,
        .tilemapTop = 0x03,
        .width = 0x18,
        .height = 0x04,
        .paletteNum = 0x0f,
        .baseBlock = 0x0001
    }, 
    
    [CONTROLS_GUIDE_PAGES_2_3_WINDOW_MIDDLE] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x06,
        .tilemapTop = 0x08,
        .width = 0x18,
        .height = 0x04,
        .paletteNum = 0x0f,
        .baseBlock = 0x0062
    }, 
    
    [CONTROLS_GUIDE_PAGES_2_3_WINDOW_BOTTOM] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x06,
        .tilemapTop = 0x0d,
        .width = 0x18,
        .height = 0x06,
        .paletteNum = 0x0f,
        .baseBlock = 0x00c3
    }, 
    DUMMY_WIN_TEMPLATE
};

enum
{
    CONTROLS_GUIDE_PAGE_1,
    CONTROLS_GUIDE_PAGE_2,
    CONTROLS_GUIDE_PAGE_3,
    CONTROLS_GUIDE_PAGE_4,
    NUM_CONTROLS_GUIDE_PAGES,
};//go over my setup unsure if should have a page 4 or should just add to 3

//need find what this is,
//hmm  I think I may have made this myself?
static const struct WindowTemplate sHelpDocsWindowTemplates4[] = {
    {
        .bg = 0x00,
        .tilemapLeft = 0x00,
        .tilemapTop = 0x03,
        .width = 0x1e,
        .height = 0xf,
        .paletteNum = 0x0f,
        .baseBlock = 0x0001
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate *const sHelpDocsWindowTemplatePtrs[4] = {
    [CONTROLS_GUIDE_PAGE_1] = sHelpDocsWindowTemplates1,
    [CONTROLS_GUIDE_PAGE_2] = sHelpDocsWindowTemplates2,
    [CONTROLS_GUIDE_PAGE_3] = sHelpDocsWindowTemplates3,
    [CONTROLS_GUIDE_PAGE_4] = sHelpDocsWindowTemplates4
};

static const struct WindowTemplate sNewGameAdventureIntroWindowTemplates[NUM_INTRO_WINDOWS + 1] = {
    
    [WIN_INTRO_TEXTBOX] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x01,
        .tilemapTop = 0x04,
        .width = 0x1c,
        .height = 0x0f,
        .paletteNum = 0x0f,
        .baseBlock = 0x0001
    }, 
    
    [WIN_INTRO_BOYGIRL] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x12,
        .tilemapTop = 0x09,
        .width = 0x09,
        .height = 0x04,
        .paletteNum = 0x0f,
        .baseBlock = 0x0174
    }, 
    
    [WIN_INTRO_YESNO] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x02,
        .tilemapTop = 0x02,
        .width = 0x06,
        .height = 0x04,
        .paletteNum = 0x0f,
        .baseBlock = 0x0180
    }, 
    
    [WIN_INTRO_NAMES] =
    {
        .bg = 0x00,
        .tilemapLeft = 0x02,
        .tilemapTop = 0x02,
        .width = 0x0c,
        .height = 0x0a,
        .paletteNum = 0x0f,
        .baseBlock = 0x0001
    }, 
    DUMMY_WIN_TEMPLATE
};

//sTextColor_White
static const u8 sTextColor_HelpSystem[4] = {
    0x00, 0x01, 0x02, 0x00
};

//sTextColor_DarkGray
static const u8 sTextColor_OakSpeech[4] = {
    0x00, 0x02, 0x03, 0x00
};

enum
{
    PIKACHU_INTRO_PAGE_1,
    PIKACHU_INTRO_PAGE_2,
    PIKACHU_INTRO_PAGE_3,
    NUM_PIKACHU_INTRO_PAGES,
};

static const u8 *const sPikachuIntro_Strings[NUM_PIKACHU_INTRO_PAGES] = {
    [PIKACHU_INTRO_PAGE_1] = gNewGameAdventureIntro1,
    [PIKACHU_INTRO_PAGE_2] = gNewGameAdventureIntro2,
    [PIKACHU_INTRO_PAGE_3] = gNewGameAdventureIntro3
};

#define GFX_TAG_PLATFORM     0x1000
#define GFX_TAG_PIKACHU      0x1001
#define GFX_TAG_PIKACHU_EARS 0x1002
#define GFX_TAG_PIKACHU_EYES 0x1003

#define PAL_TAG_PLATFORM     0x1000
#define PAL_TAG_PIKACHU      0x1001

enum
{
    SPRITE_TYPE_PIKACHU,
    SPRITE_TYPE_PLATFORM,
};

enum
{
    PIKACHU_BODY_PLATFORM_LEFT,
    PIKACHU_EARS_PLATFORM_MIDDLE,
    PIKACHU_EYES_PLATFORM_RIGHT,
    NUM_PIKACHU_PLATFORM_SPRITES,
};

static const struct CompressedSpriteSheet sOakSpeech_PikaSpriteSheets[3] = {
    
    [PIKACHU_BODY_PLATFORM_LEFT] =
    {
        .data = sOakSpeechGfx_Pika1,
        .size = 0x400,
        .tag = GFX_TAG_PIKACHU
    },
    [PIKACHU_EARS_PLATFORM_MIDDLE] =
    {
        .data = sOakSpeechGfx_Pika2,
        .size = 0x200,
        .tag = GFX_TAG_PIKACHU_EARS
    },
    [PIKACHU_EYES_PLATFORM_RIGHT] =
    {
        .data = sOakSpeechGfx_PikaEyes,
        .size = 0x80,
        .tag = GFX_TAG_PIKACHU_EYES
    },
};

static const struct CompressedSpriteSheet sOakSpeech_Platform_SpriteSheet = {
    .data = sOakSpeechGfx_GrassPlatform,
    .size = 0x600,
    .tag = GFX_TAG_PLATFORM
};

static const struct SpritePalette sOakSpeech_PikaSpritePal = {
    .data = sPikachuIntro_Pikachu_Pal,
    .tag = PAL_TAG_PIKACHU
};

static const struct SpritePalette sOakSpeech_Platform_SpritePalette = {
    .data = sOakSpeech_Platform_Pal,
    .tag = PAL_TAG_PLATFORM
};

static const union AnimCmd sOakSpeech_PlatformLeft_Anim[] = {
    ANIMCMD_FRAME( 0, 0),
    ANIMCMD_END
};

static const union AnimCmd sOakSpeech_PlatformMiddle_Anim[] = {
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_END
};

static const union AnimCmd sOakSpeech_PlatformRight_Anim[] = {
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sOakSpeech_PlatformLeft_Anims[] = {
    sOakSpeech_PlatformLeft_Anim
};
static const union AnimCmd *const sOakSpeech_PlatformRight_Anims[] = {
    sOakSpeech_PlatformMiddle_Anim
};
static const union AnimCmd *const sOakSpeech_Platform_SpriteTemplates[] = {
    sOakSpeech_PlatformRight_Anim
};


static const struct SpriteTemplate sOakSpeech_GrassPlatformSpriteTemplates[3] = {

    [PIKACHU_BODY_PLATFORM_LEFT] =
    {
        .tileTag = GFX_TAG_PLATFORM,
        .paletteTag = PAL_TAG_PLATFORM,
        .oam = &gOamData_AffineOff_ObjBlend_32x32,
        .anims = sOakSpeech_PlatformLeft_Anims,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    [PIKACHU_EARS_PLATFORM_MIDDLE] =
    {
        .tileTag = GFX_TAG_PLATFORM,
        .paletteTag = PAL_TAG_PLATFORM,
        .oam = &gOamData_AffineOff_ObjBlend_32x32,
        .anims = sOakSpeech_PlatformRight_Anims,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    [PIKACHU_EYES_PLATFORM_RIGHT] =
    {
        .tileTag = GFX_TAG_PLATFORM,
        .paletteTag = PAL_TAG_PLATFORM,
        .oam = &gOamData_AffineOff_ObjBlend_32x32,
        .anims = sOakSpeech_Platform_SpriteTemplates,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
};

static const union AnimCmd sPikachuIntro_PikachuBody_Anim[] = {
    ANIMCMD_FRAME( 0, 30),
    ANIMCMD_FRAME(16, 30),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd sPikaAnim2[] = {
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd sPikaAnim3[] = {
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_FRAME(0,  8),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_FRAME(0,  8),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sPikaAnims1[] = {
    sPikachuIntro_PikachuBody_Anim
};
static const union AnimCmd *const sPikaAnims2[] = {
    sPikaAnim2
};
static const union AnimCmd *const sPikaAnims3[] = {
    sPikaAnim3
};

static const struct SpriteTemplate sOakSpeech_PikaSpriteTemplates[3] = {
    { 0x1001, 0x1001, &gOamData_AffineOff_ObjNormal_32x32, sPikaAnims1, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
    { 0x1002, 0x1001, &gOamData_AffineOff_ObjNormal_32x16, sPikaAnims2, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
    { 0x1003, 0x1001, &gOamData_AffineOff_ObjNormal_16x8, sPikaAnims3, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy }
};

static const u8 *const sHelpDocsPtrs[] = {
    gNewGame_HelpDocs2, gNewGame_HelpDocs3, gNewGame_HelpDocs4,
    gNewGame_HelpDocs5, gNewGame_HelpDocs6, gNewGame_HelpDocs7,
    gNewGame_HelpDocs8
};

static const u8 *const sMaleNameChoices[] = {
#if defined(FIRERED)
    gNameChoice_Red,
    gNameChoice_Fire,
    gNameChoice_Ash,
    gNameChoice_Kene,
    gNameChoice_Geki,
#elif defined(LEAFGREEN)
    gNameChoice_Blue,
    gNameChoice_Leaf,
    //gNameChoice_Gary,
    gNameChoice_Ash,
    gNameChoice_Kaz,
    gNameChoice_Toru,
#endif
    gNameChoice_Jak,
    gNameChoice_Janne,
    gNameChoice_Jonn,
    gNameChoice_Kamon,
    gNameChoice_Karl,
    gNameChoice_Taylor,
    gNameChoice_Oscar,
    gNameChoice_Hiro,
    gNameChoice_Max,
    gNameChoice_Jon,
    gNameChoice_Ralph,
    gNameChoice_Kay,
    gNameChoice_Tosh,
    gNameChoice_Roak
};

//why did I separate these out is leaf and green different characters
static const u8 *const sFemaleNameChoices[] = {
#if defined(FIRERED)
    gNameChoice_Red,
    gNameChoice_Fire,
#elif defined(LEAFGREEN)
    gNameChoice_Green,   
    gNameChoice_Leaf,
#endif
    gNameChoice_Omi,
    gNameChoice_Jodi,
    gNameChoice_Amanda,
    //gNameChoice_Hillary,
    gNameChoice_Makey,
    gNameChoice_Michi,
    gNameChoice_Paula,
    gNameChoice_June,
    gNameChoice_Cassie,
    gNameChoice_Green,
    gNameChoice_Seda,
    gNameChoice_Kiko,
    gNameChoice_Mina,
    gNameChoice_Norie,
    gNameChoice_Red,
    gNameChoice_Sai,
    gNameChoice_Momo,
    gNameChoice_Suzi
};

static const u8 *const sRivalNameChoices[] = {
#if defined(FIRERED)
    gNameChoice_Blue,
    gNameChoice_Gary,
    gNameChoice_Kaz,
    gNameChoice_Toru
#elif defined(LEAFGREEN)
    gNameChoice_Blue,
    gNameChoice_Gary,
    gNameChoice_Kene,
    gNameChoice_Red    
#endif
}; //vsonic make sure ther's a check to ensure player and rival name are different

static const u8 *const sPlayerMaleNameChoices[] = {
    gNameChoice_Red,
#if defined(FIRERED) 
    gNameChoice_Fire,
#elif defined(LEAFGREEN)
    gNameChoice_Leaf,
#endif
    gNameChoice_Ash,
    gNameChoice_OtherName
};

static const u8 *const sPlayerFemaleNameChoices[] = {
    gNameChoice_Green,
#if defined(FIRERED)
    gNameChoice_Fire,
#elif defined(LEAFGREEN)
    gNameChoice_Leaf,
#endif
    gNameChoice_Kiko,
    gNameChoice_OtherName
};

static void VBlankCB_NewGameOaksSpeech(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_NewGameOaksSpeech(void)
{
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void StartNewGameScene(void)
{
    gPlttBufferUnfaded[0] = RGB_BLACK;
    gPlttBufferFaded[0]   = RGB_BLACK;
    CreateTask(Task_NewGameScene, 0);
    SetMainCallback2(CB2_NewGameOaksSpeech);
}

static void Task_NewGameScene(u8 taskId)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        DmaFill16(3, 0, VRAM, VRAM_SIZE);
        DmaFill32(3, 0, OAM, OAM_SIZE);
        DmaFill16(3, 0, PLTT + sizeof(u16), PLTT_SIZE - 2);
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetTempTileDataBuffers();
        //SetHelpContext(HELPCONTEXT_NEW_GAME);
        break;
    case 1:
        sOakSpeechResources = AllocZeroed(sizeof(*sOakSpeechResources));
        OakSpeechNidoranFSetup(1, 1);
        break;
    case 2:
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        break;
    case 3:
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(1, sBgTemplates, NELEMS(sBgTemplates));
        SetBgTilemapBuffer(1, sOakSpeechResources->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sOakSpeechResources->bg2TilemapBuffer);
        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(2, 0, 0);
        ChangeBgY(2, 0, 0);
        gSpriteCoordOffsetX = 0;
        gSpriteCoordOffsetY = 0;
        break;
    case 4:
        gPaletteFade.bufferTransferDisabled = TRUE;
        InitStandardTextBoxWindows();
        ResetBg0();
        Menu_LoadStdPalAt(0xD0);
        LoadPalette(sHelpDocsPalette, 0x000, 0x080);
        LoadPalette(GetTextWindowPalette(2) + 15, 0x000, 0x002);
        break;
    case 5:
        sOakSpeechResources->textSpeed = GetPlayerTextSpeedDelay();
        gTextFlags.canABSpeedUpPrint = TRUE;
        DecompressAndCopyTileDataToVram(1, sOakSpeechGfx_GameStartHelpUI, 0, 0, 0);
        break;
    case 6:
        if (FreeTempTileDataBuffersIfPossible())
            return;
        ClearDialogWindowAndFrame(0, 1);
        FillBgTilemapBufferRect_Palette0(1, 0x0000,  0,  0, 32, 32);
        CopyBgTilemapBufferToVram(1);
        break;
    case 7:
        CreateTopBarWindowLoadPalette(0, 30, 0, 13, 0x1C4);
        FillBgTilemapBufferRect_Palette0(1, 0xD00F,  0,  0, 30, 2);
        FillBgTilemapBufferRect_Palette0(1, 0xD002,  0,  2, 30, 1);
        FillBgTilemapBufferRect_Palette0(1, 0xD00E,  0, 19, 30, 1);
        ControlsGuide_LoadPage1();
        gPaletteFade.bufferTransferDisabled = FALSE;
        gTasks[taskId].data[5] = CreateTextCursorSpriteForOakSpeech(0, 0xE6, 0x95, 0, 0);
        BlendPalettes(0xFFFFFFFF, 0x10, 0x00);
        break;
    case 10:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        SetVBlankCallback(VBlankCB_NewGameOaksSpeech);
        PlayBGM(MUS_NEW_GAME_INSTRUCT);
        gTasks[taskId].func = Task_ControlsGuide_HandleInput;
        gMain.state = 0;
        return;
    }

    gMain.state++;
}

static void ControlsGuide_LoadPage1(void)
{
    TopBarWindowPrintTwoStrings(gText_Controls, gText_ABUTTONNext, 0, 0, 1);
    sOakSpeechResources->windowIds[0] = AddWindow(sHelpDocsWindowTemplatePtrs[sOakSpeechResources->currentPage]);
    PutWindowTilemap(sOakSpeechResources->windowIds[0]);
    FillWindowPixelBuffer(sOakSpeechResources->windowIds[0], 0x00);
    AddTextPrinterParameterized4(sOakSpeechResources->windowIds[0], 2, 2, 0, 0, 1, sTextColor_HelpSystem, 0, gNewGame_HelpDocs1);
    CopyWindowToVram(sOakSpeechResources->windowIds[0], COPYWIN_BOTH);
    FillBgTilemapBufferRect_Palette0(1, 0x3000, 1, 3, 5, 16);
    CopyBgTilemapBufferToVram(1);
}

//was i < 3 changed to 4
static void Task_ControlsGuide_LoadPage(u8 taskId)
{
    u8 currWindow = 0;
    u8 page2Or3 = sOakSpeechResources->currentPage - 1;
    if (sOakSpeechResources->currentPage == CONTROLS_GUIDE_PAGE_1)
    {
        ControlsGuide_LoadPage1();
    }
    else
    {
        TopBarWindowPrintString(gText_ABUTTONNext_BBUTTONBack, 0, TRUE);
        for (currWindow = CONTROLS_GUIDE_PAGES_2_3_WINDOW_TOP; currWindow < 4; currWindow++)
        {
            //looks weird but belive is right, as both are array of arrays first is pick page then window within page?
            sOakSpeechResources->windowIds[currWindow] = AddWindow(&sHelpDocsWindowTemplatePtrs[sOakSpeechResources->currentPage][currWindow]);
            PutWindowTilemap(sOakSpeechResources->windowIds[currWindow]);
            FillWindowPixelBuffer(sOakSpeechResources->windowIds[currWindow], 0x00);
            AddTextPrinterParameterized4(sOakSpeechResources->windowIds[currWindow], 2, 6, 0, 0, 1, sTextColor_HelpSystem, 0, sHelpDocsPtrs[currWindow + page2Or3 * 3]);
            CopyWindowToVram(sOakSpeechResources->windowIds[currWindow], COPYWIN_BOTH);
        }

        if (sOakSpeechResources->currentPage == CONTROLS_GUIDE_PAGE_2)
        {
            CopyToBgTilemapBufferRect(1, sHelpDocsPage2Tilemap, 1, 3, 5, 16);
        }
        else if (sOakSpeechResources->currentPage == CONTROLS_GUIDE_PAGE_3)
        {
            CopyToBgTilemapBufferRect(1, sHelpDocsPage3Tilemap, 1, 3, 5, 16);
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(1, 0x3000, 1, 3, 5, 16);
        }
        CopyBgTilemapBufferToVram(1);
    }
    BeginNormalPaletteFade(0xFFFFDFFF, -1, 16, 0, GetTextWindowPalette(2)[15]);
    gTasks[taskId].func = Task_ControlsGuide_HandleInput;
}

static void Task_ControlsGuide_HandleInput(u8 taskId)
{
    if (!gPaletteFade.active && JOY_NEW((A_BUTTON | B_BUTTON)))
    {
        if (JOY_NEW(A_BUTTON))
        {
            gTasks[taskId].data[15] = 1;
            if (sOakSpeechResources->currentPage < 3)
            {
                BeginNormalPaletteFade(0xFFFFDFFF, -1, 0, 16, GetTextWindowPalette(2)[15]);
            }
        }
        else
        {
            if (sOakSpeechResources->currentPage != 0)
            {
                gTasks[taskId].data[15] = -1;
                BeginNormalPaletteFade(0xFFFFDFFF, -1, 0, 16, GetTextWindowPalette(2)[15]);
            }
            else
                return;
        }
    }
    else
        return;
    PlaySE(SE_SELECT);
    gTasks[taskId].func = Task_ControlsGuide_ChangePage;
}

//ok this is for of pages for main help window
//but not for the pika window that's a different place
static void Task_ControlsGuide_ChangePage(u8 taskId) //this seems most importnat for determing num pages?
{
    u8 r8 = 0;
    u8 i;

    if (!gPaletteFade.active)
    {
        switch (sOakSpeechResources->currentPage) {
        case 0:
            r8 = 1;
            break;
        case 1:
        case 2:
        case 3:
            r8 = 4;
            break;
        }
        sOakSpeechResources->currentPage += gTasks[taskId].data[15];
        if (sOakSpeechResources->currentPage < 4)
        {
            for (i = 0; i < r8; i++)
            {
                FillWindowPixelBuffer(sOakSpeechResources->windowIds[i], 0x00);
                ClearWindowTilemap(sOakSpeechResources->windowIds[i]);
                CopyWindowToVram(sOakSpeechResources->windowIds[i], COPYWIN_BOTH);
                RemoveWindow(sOakSpeechResources->windowIds[i]);
                sOakSpeechResources->windowIds[i] = 0;
            }
            gTasks[taskId].func = Task_ControlsGuide_LoadPage;
        }
        else
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 2, 0, 16, 0);
            gTasks[taskId].func = Task_ControlsGuide_Clear;
        }
    }
}

static void Task_ControlsGuide_Clear(u8 taskId)
{
    u8 i = 0;

    if (!gPaletteFade.active)
    {
        for (i = 0; i < 3; i++)
        {
            FillWindowPixelBuffer(sOakSpeechResources->windowIds[i], 0x00);
            ClearWindowTilemap(sOakSpeechResources->windowIds[i]);
            CopyWindowToVram(sOakSpeechResources->windowIds[i], COPYWIN_BOTH);
            RemoveWindow(sOakSpeechResources->windowIds[i]);
            sOakSpeechResources->windowIds[i] = 0;
        }
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 18);
        CopyBgTilemapBufferToVram(1);
        sub_8006398(gTasks[taskId].data[5]);
        sOakSpeechResources->windowIds[0] = RGB_BLACK;
        LoadPalette(sOakSpeechResources->windowIds, 0, 2);
        gTasks[taskId].data[3] = 32;
        gTasks[taskId].func = Task_OakSpeech6;
    }
}

static void Task_OakSpeech6(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u32 sp14 = 0;

    if (data[3] != 0)
        data[3]--;
    else
    {
        PlayBGM(MUS_NEW_GAME_INTRO);
        ClearTopBarWindow();
        TopBarWindowPrintString(gText_ABUTTONNext, 0, 1);
        sOakSpeechResources->pikachuIntroTilemap = MallocAndDecompress(sNewGameAdventureIntroTilemap, &sp14);
        CopyToBgTilemapBufferRect(1, sOakSpeechResources->pikachuIntroTilemap, 0, 2, 30, 19);
        CopyBgTilemapBufferToVram(1);
        Free(sOakSpeechResources->pikachuIntroTilemap);
        sOakSpeechResources->pikachuIntroTilemap = NULL;
        data[14] = AddWindow(&sNewGameAdventureIntroWindowTemplates[0]);
        PutWindowTilemap(data[14]);
        FillWindowPixelBuffer(data[14], 0x00);
        CopyWindowToVram(data[14], COPYWIN_BOTH);
        sOakSpeechResources->currentPage = 0;
        gMain.state = 0;
        data[15] = 16;
        AddTextPrinterParameterized4(data[14], 2, 3, 5, 0, 0, sTextColor_OakSpeech, 0, sPikachuIntro_Strings[0]);
        data[5] = CreateTextCursorSpriteForOakSpeech(0, 0xe2, 0x91, 0, 0);
        gSprites[data[5]].oam.objMode = ST_OAM_OBJ_BLEND;
        gSprites[data[5]].oam.priority = 0;
        CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(taskId, 0);
        BeginNormalPaletteFade(0xFFFFFFFF, 2, 16, 0, 0);
        gTasks[taskId].func = Task_OakSpeech7;
    }
}

//pika page
static void Task_OakSpeech7(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    switch (gMain.state)
    {
    case 0:
        if (!gPaletteFade.active)
        {
            SetGpuReg(REG_OFFSET_WIN0H, 0x00F0);
            SetGpuReg(REG_OFFSET_WIN0V, 0x10A0);
            SetGpuReg(REG_OFFSET_WININ, 0x003F);
            SetGpuReg(REG_OFFSET_WINOUT, 0x001F);
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON);
            gMain.state = 1;
        }
        break;
    case 1:
        if (JOY_NEW((A_BUTTON | B_BUTTON)))
        {
            if (JOY_NEW(A_BUTTON))
            {
                sOakSpeechResources->currentPage++;
            }
            else if (sOakSpeechResources->currentPage != 0)
            {
                sOakSpeechResources->currentPage--;
            }
            else
            {
                break;
            }
            PlaySE(SE_SELECT);
            if (sOakSpeechResources->currentPage == 3) //limit of pika adventure pages
            {
                gMain.state = 4;
            }
            else
            {
                SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1);
                SetGpuReg(REG_OFFSET_BLDALPHA, (16 - data[15]) | data[15]);
                gMain.state++;
            }
        }
        break;
    case 2:
        data[15] -= 2;
        SetGpuReg(REG_OFFSET_BLDALPHA, ((16 - data[15]) << 8) | data[15]);
        if (data[15] <= 0)
        {
            FillWindowPixelBuffer(data[14], 0x00);
            AddTextPrinterParameterized4(data[14], 2, 3, 5, 0, 0, sTextColor_OakSpeech, 0, sPikachuIntro_Strings[sOakSpeechResources->currentPage]);
            if (sOakSpeechResources->currentPage == 0)
            {
                ClearTopBarWindow();
                TopBarWindowPrintString(gText_ABUTTONNext, 0, 1);
            }
            else
            {
                ClearTopBarWindow();
                TopBarWindowPrintString(gText_ABUTTONNext_BBUTTONBack, 0, 1);
            }
            gMain.state++;
        }
        break;
    case 3:
        data[15] += 2;
        SetGpuReg(REG_OFFSET_BLDALPHA, ((16 - data[15]) << 8) | data[15]);
        if (data[15] >= 16)
        {
            data[15] = 16;
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            gMain.state = 1;
        }
        break;
    case 4:
        sub_8006398(gTasks[taskId].data[5]);
        PlayBGM(MUS_NEW_GAME_EXIT);
        data[15] = 24;
        gMain.state++;
        break;
    default:
        if (data[15] != 0)
            data[15]--;
        else
        {
            gMain.state = 0;
            sOakSpeechResources->currentPage = 0;
            SetGpuReg(REG_OFFSET_WIN0H, 0);
            SetGpuReg(REG_OFFSET_WIN0V, 0);
            SetGpuReg(REG_OFFSET_WININ, 0);
            SetGpuReg(REG_OFFSET_WINOUT, 0);
            ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON);
            BeginNormalPaletteFade(0xFFFFFFFF, 2, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_OakSpeech8;
        }
        break;
    }
}

static void Task_OakSpeech8(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        DestroyTopBarWindow();
        FillWindowPixelBuffer(data[14], 0x00);
        ClearWindowTilemap(data[14]);
        CopyWindowToVram(data[14], COPYWIN_BOTH);
        RemoveWindow(data[14]);
        data[14] = 0;
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        CopyBgTilemapBufferToVram(1);
        DestroyLinkedPikaOrGrassPlatformSprites(taskId, 0);
        data[3] = 80;
        gTasks[taskId].func = Task_OakSpeech9;
    }
}

static void Task_OakSpeech9(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u32 size = 0;

    if (data[3] != 0)
        data[3]--;
    else
    {
        sOakSpeechResources->oakSpeechBackgroundTiles = MallocAndDecompress(sOakSpeechGfx_SolidColors, &size);
        LoadBgTiles(1, sOakSpeechResources->oakSpeechBackgroundTiles, size, 0);
        CopyToBgTilemapBuffer(1, sOakSpeech_BackgroundTilemap, 0, 0);
        CopyBgTilemapBufferToVram(1);
        CreateNidoranFSprite(taskId);
        LoadOaksSpeechTrainerPic(3, 0);
        CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(taskId, 1);
        PlayBGM(MUS_ROUTE24);
        BeginNormalPaletteFade(0xFFFFFFFF, 5, 16, 0, RGB_BLACK);
        data[3] = 80;
        ShowBg(2);
        gTasks[taskId].func = Task_OakSpeech10;
    }
}

#define OaksSpeechPrintMessage(str, speed) ({ \
    DrawDialogueFrame(0, FALSE);\
    if (str != gStringVar4) \
    { \
        StringExpandPlaceholders(gStringVar4, str); \
        AddTextPrinterParameterized2(0, 4, gStringVar4, speed, NULL, 2, 1, 3); \
    } \
    else \
    { \
        AddTextPrinterParameterized2(0, 4, str, speed, NULL, 2, 1, 3); \
    } \
    CopyWindowToVram(0, COPYWIN_BOTH); \
})

static void Task_OakSpeech10(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (data[3] != 0)
            data[3]--;
        else
        {
            OaksSpeechPrintMessage(gOakText_WelcomeToTheWorld, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech11;
        }
    }
}

static void Task_OakSpeech11(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        OaksSpeechPrintMessage(gOakText_WorldInhabited1, sOakSpeechResources->textSpeed);
        gTasks[taskId].data[3] = 30;
        gTasks[taskId].func = Task_OakSpeech12;
    }
}

static void Task_OakSpeech12(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u8 spriteId;

    if (!IsTextPrinterActive(0))
    {
        if (data[3] != 0)
            data[3]--;
        // else {
        spriteId = gTasks[taskId].data[4];
        gSprites[spriteId].invisible = FALSE;
        gSprites[spriteId].data[0] = 0;
        CreatePokeballSpriteToReleaseMon(spriteId, gSprites[spriteId].oam.paletteNum, 0x64, 0x42, 0, 0, 32, 0xFFFF1FFF);
        gTasks[taskId].func = Task_OakSpeech13;
        gTasks[taskId].data[3] = 0;
        // }
    }
}

static void Task_OakSpeech13(u8 taskId)
{
    if (IsCryFinished())
    {
        if (gTasks[taskId].data[3] >= 96)
            gTasks[taskId].func = Task_OakSpeech14;
    }
    if (gTasks[taskId].data[3] < 0x4000)
    {
        gTasks[taskId].data[3]++;
        if (gTasks[taskId].data[3] == 32)
        {
            OaksSpeechPrintMessage(gOakText_WorldInhabited2, sOakSpeechResources->textSpeed);
           PlayCry_Normal(SPECIES_NIDORAN_F, 0);
        }
    }
}

static void Task_OakSpeech14(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        OaksSpeechPrintMessage(gOakText_PetsBattlingStudy, sOakSpeechResources->textSpeed);
        gTasks[taskId].func = Task_OakSpeech15;
    }
}

static void Task_OakSpeech15(u8 taskId)
{
    u8 spriteId;

    if (!IsTextPrinterActive(0))
    {
        ClearDialogWindowAndFrame(0, 1);
        spriteId = gTasks[taskId].data[4];
        gTasks[taskId].data[6] = CreateTradePokeballSprite(spriteId, gSprites[spriteId].oam.paletteNum, 0x64, 0x42, 0, 0, 32, 0xFFFF1F3F);
        gTasks[taskId].data[3] = 48;
        gTasks[taskId].data[0] = 64;
        gTasks[taskId].func = Task_OakSpeech16;
    }
}

static void Task_OakSpeech16(u8 taskId) //new beginnning of rename loop
{
    s16 * data = gTasks[taskId].data;

    if (data[0] != 0)
    {
        if (data[0] < 24)
        {
            gSprites[data[4]].pos1.y--;
            
        }
        data[0]--;
    }
    else
    {
        if (data[3] == 48)
        {
            DestroySprite(&gSprites[data[4]]);
            DestroySprite(&gSprites[data[6]]);
        }
        if (data[3] != 0)
        {
            data[3]--;
        }
        else
        {
            OaksSpeechPrintMessage(gOakText_TellMeALittleAboutYourself, sOakSpeechResources->textSpeed); 
            gTasks[taskId].func = Task_OakSpeech17;
        }
    }
}

static void Task_OakSpeech17(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!IsTextPrinterActive(0))
    {
        ClearDialogWindowAndFrame(0, 1);
        CreateFadeInTask(taskId, 2); 
        data[3] = 48;
        gTasks[taskId].func = Task_OakSpeech18;
    }
}

static void Task_OakSpeech18(u8 taskId) //ok HERE is where it asks gender.
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        if (data[3] != 0)
            data[3]--;
        else
        {
            data[1] = -60;
            DestroyOaksSpeechTrainerPic();
            
            OaksSpeechPrintMessage(gOakText_AskPlayerGender, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech19;
        }
    }
}

static void Task_OakSpeech19(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        
        gTasks[taskId].data[13] = AddWindow(&sNewGameAdventureIntroWindowTemplates[1]);
        PutWindowTilemap(gTasks[taskId].data[13]);
        DrawStdFrameWithCustomTileAndPalette(gTasks[taskId].data[13], 1, GetStdWindowBaseTileNum(), 14);
        FillWindowPixelBuffer(gTasks[taskId].data[13], 0x11);
        sOakSpeechResources->textColor[0] = 1;
        sOakSpeechResources->textColor[1] = 2;
        sOakSpeechResources->textColor[2] = 3;
        AddTextPrinterParameterized3(gTasks[taskId].data[13], 2, 8, 1, sOakSpeechResources->textColor, 0, gText_Boy);
        sOakSpeechResources->textColor[0] = 1;
        sOakSpeechResources->textColor[1] = 2;
        sOakSpeechResources->textColor[2] = 3;
        AddTextPrinterParameterized3(gTasks[taskId].data[13], 2, 8, 17, sOakSpeechResources->textColor, 0, gText_Girl);
        Menu_InitCursor(gTasks[taskId].data[13], 2, 0, 1, GetFontAttribute(2, 1) + 2, 2, 0);
        CopyWindowToVram(gTasks[taskId].data[13], COPYWIN_BOTH);
        gTasks[taskId].func = Task_OakSpeech20;
    }
}

static void Task_OakSpeech20(u8 taskId) //gender finalized
{
    s8 input = Menu_ProcessInputNoWrapAround();
    switch (input)
    {
    case 0:
        gSaveBlock2Ptr->playerGender = MALE;
        break;
    case 1:
        gSaveBlock2Ptr->playerGender = FEMALE;
        break;
    case -1:
    case -2:
        return;
    }
    gTasks[taskId].func = Task_OakSpeech21;

}

static void Task_OakSpeech21(u8 taskId) //believe its change window, and set background
{
    s16 * data = gTasks[taskId].data;
    ClearStdWindowAndFrameToTransparent(data[13], 1);
    RemoveWindow(data[13]);
    data[13] = 0;
    ClearDialogWindowAndFrame(0, 1);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
    CopyBgTilemapBufferToVram(0);
    gTasks[taskId].func = Task_OakSpeech22;
}

static void Task_OakSpeech22(u8 taskId) //loads the big trainer pic, for after gender select
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        LoadOaksSpeechTrainerPic(MALE, 0);
    else
        LoadOaksSpeechTrainerPic(FEMALE, 0);
    CreateFadeOutTask(taskId, 2);
    gTasks[taskId].data[3] = 32; //first case of data[3]
    gTasks[taskId].func = Task_OakSpeech23;
}

static void Task_OakSpeech23(u8 taskId) //beginning of player naming
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        if (data[3] != 0)
            data[3]--;
        else
        {
            data[1] = 0;
            //OaksSpeechPrintMessage(gOakText_AskPlayerName, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech3C; //new attempt skips 24, but stilll eventually should get to 25
        } 
    }
}

static void Task_OakSpeech24(u8 taskId)// previously there was a loop on 24 & 25, fading screen and calling player naming screen.
{   //but I removed that to loop back to gender select instead. task16
    if (!IsTextPrinterActive(0))
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        sOakSpeechResources->hasPlayerBeenNamed = FALSE;
        gTasks[taskId].func = Task_OakSpeech25; //this is what I need to change, I swapped the loop
        //gTasks[taskId].func = Task_OakSpeech3C; //as unk0010 is set here, would allow PrintNameChoiceOptions to pickup plaer options 
    } // options is either 35 or could be 28 //35 didn't work think I need to go Task_OakSpeech34
    // to lead into 35 like rival does instead of going directly
}

//alt verion of oakspeech34 for the player
static void Task_OakSpeech3C(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0) //issue is either this, or text not coming up in time with input and window gets cleared so its caught in between trying to print next image
    {
        sOakSpeechResources->hasPlayerBeenNamed = FALSE;
        //if (!IsTextPrinterActive(0))
        //OaksSpeechPrintMessage(gOakText_AskPlayerName, sOakSpeechResources->textSpeed);        
        gTasks[taskId].func = Task_OakSpeech35;
    }
}

static void Task_OakSpeech35(u8 taskId) //important slide sprite to the right, and create window for default name choices
{
    s16 * data = gTasks[taskId].data;

    //ok I konw it executes both blocks before going to 29
    if (!IsTextPrinterActive(0)) //want to just move pic if it was centered but not on redisplay for player naming
    {
        if (data[1] > -60) //data[1] is set to 0 right before this in oakspeech23,  oakspeech18 sets it to -60 (also decrement data[3]?) os18 is first instance of data[1]
        {
            data[1] -= 2; //if this is removed function can't work/continue, think may need to just completely change how this function works/undestand data[1]
            //gSpriteCoordOffsetX = 64; using this pair fixes drift issue, but isn't a smooth transition...
	    //ChangeBgX(2, -0x3C00, 0);
	    gSpriteCoordOffsetX += 2;//but commenting this out moves character but not the circle it stands on..
            ChangeBgX(2, 0x200, 2);//commenting this keeps character from moving (think it slides the backgruond image to simulate movement?)
        }
        else
        {
            data[1] = -60;
            if (sOakSpeechResources->hasPlayerBeenNamed == FALSE)
                OaksSpeechPrintMessage(gOakText_AskPlayerName, sOakSpeechResources->textSpeed); //gave in put text after slide works perfectly
            PrintNameChoiceOptions(taskId, sOakSpeechResources->hasPlayerBeenNamed);
            gTasks[taskId].func = Task_OakSpeech29;
        }
    }
}

static void Task_OakSpeech28(u8 taskId) //believe paired with task_23 alternates to rival if palyer name chosen
{   //actually isn't, though it has a player option the player never actually triggers this task,
    //its rival only
    //Guess player was added here for simplicity and to make them all match. 
    PrintNameChoiceOptions(taskId, sOakSpeechResources->hasPlayerBeenNamed);
    if (sOakSpeechResources->hasPlayerBeenNamed == FALSE)
    {
        OaksSpeechPrintMessage(gOakText_AskPlayerName, sOakSpeechResources->textSpeed);
    }
    else
    {
        OaksSpeechPrintMessage(gOakText_AskRivalName, 0);
    }
    gTasks[taskId].func = Task_OakSpeech29;
}

static void Task_OakSpeech29(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    s8 input = Menu_ProcessInput();

    if (sOakSpeechResources->hasPlayerBeenNamed == FALSE) //now seutp different functionality for player and rival
    { //player name selection
        switch (input) //this is the name window, 0 is new name 1-4 are the selected names
        {
        case 1:
        case 2:
        case 3:
            // player name options, case 4 rerserved for random selection
            PlaySE(SE_SELECT);
            ClearStdWindowAndFrameToTransparent(data[13], TRUE);
            RemoveWindow(data[13]);
            GetDefaultName(sOakSpeechResources->hasPlayerBeenNamed, input - 1); //saves the name option
            data[15] = 1;
            gTasks[taskId].func = Task_OakSpeech26; // go to confirm name choice
            break;
        case 4:
            PlaySE(SE_SELECT);
            ClearStdWindowAndFrameToTransparent(data[13], TRUE);
            RemoveWindow(data[13]);
            GetRandomPlayerName(sOakSpeechResources->hasPlayerBeenNamed, input - 1);
            data[15] = 1;
            gTasks[taskId].func = Task_OakSpeech26; // go to confirm name choice
            break;
        case 0: //New Name
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
            gTasks[taskId].func = Task_OakSpeech25; //go to DoNamingScreen
            break;
        case -1: // if press B, fade into gender select   new Loop start
            PlaySE(SE_SELECT);
            ClearStdWindowAndFrameToTransparent(data[13], TRUE);
            RemoveWindow(data[13]);
            //DestroyOaksSpeechTrainerPic();
            gSpriteCoordOffsetX -= 60; //circle
            ChangeBgX(2, -0x3C00, 2); //sprite need make clean between but think using slide over set, works best? just need to find EXACT values
           // gSpriteCoordOffsetX = 0; //reset values back to center in pret for slide on reset
           // ChangeBgX(2, 0, 0); 
            gTasks[taskId].func = Task_OakSpeech16;
            break;
        }
    }
    else
    { //rival name selection
        switch (input) //this is the name window, 0 is new name 1-4 are the selected names
        {
        case 1:
        case 2:
        case 3:
        case 4: // name options -rival has 4 options
            PlaySE(SE_SELECT);
            ClearStdWindowAndFrameToTransparent(data[13], TRUE);
            RemoveWindow(data[13]);
            GetDefaultName(sOakSpeechResources->hasPlayerBeenNamed, input - 1);
            data[15] = 1;
            gTasks[taskId].func = Task_OakSpeech26; // go to task setname choose rival name
            break;
        case 0: //New name
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
            gTasks[taskId].func = Task_OakSpeech25; //go to DoNamingScreen
            break;
        case -1:
            break;
        }
    }
    
}

static void Task_OakSpeech25(u8 taskId) //important reset player gender new game  done
{
    if (!gPaletteFade.active) //here getDefaultName, is picking a name from the list for the player, so this must be loop, to get a different name each time
    {
        GetDefaultName(sOakSpeechResources->hasPlayerBeenNamed, FALSE); //next step, get player name select like rival, if click newname then go to naming screen
        if (sOakSpeechResources->hasPlayerBeenNamed == FALSE) //i.e make name select for player like rival
        { 
            DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->playerGender, 0, 0, CB2_ReturnFromNamingScreen);
        }
        else // rival
        {
            ClearStdWindowAndFrameToTransparent(gTasks[taskId].data[13], 1);
            RemoveWindow(gTasks[taskId].data[13]);
            DoNamingScreen(NAMING_SCREEN_RIVAL, gSaveBlock1Ptr->rivalName, 0, 0, 0, CB2_ReturnFromNamingScreen);
        }
        DestroyLinkedPikaOrGrassPlatformSprites(taskId, 1);
        FreeAllWindowBuffers();
    }
}

static void Task_OakSpeech26(u8 taskId) // continues from 25 after pallleteFade ends & goes to 27  for player and rival
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (data[15] == 1)
        {
            if (sOakSpeechResources->hasPlayerBeenNamed == FALSE)
            {
                StringExpandPlaceholders(gStringVar4, gOakText_FinalizePlayerName);
            }
            else
            {
                StringExpandPlaceholders(gStringVar4, gOakText_ConfirmRivalName);
            }
            OaksSpeechPrintMessage(gStringVar4, sOakSpeechResources->textSpeed);
            data[15] = 0;
            data[3] = 25;
        }
        else if (!IsTextPrinterActive(0))
        {
            if (data[3] != 0)
                data[3]--;
            else
            {
                CreateYesNoMenu(&sNewGameAdventureIntroWindowTemplates[2], 2, 0, 2, GetStdWindowBaseTileNum(), 14, 0);
                gTasks[taskId].func = Task_OakSpeech27;
            }
        }
    }
}

static void Task_OakSpeech27(u8 taskId)
{
    s8 input = Menu_ProcessInputNoWrapClearOnChoose();
    switch (input)
    {
    case 0: //choose yes
        PlaySE(SE_SELECT);
        gTasks[taskId].data[3] = 40;
        if (sOakSpeechResources->hasPlayerBeenNamed == FALSE) //player
        {
            ClearDialogWindowAndFrame(0, 1);
            CreateFadeInTask(taskId, 2);        
            gTasks[taskId].func = Task_OakSpeech30; // goto choose rival name
        }
        else //rival  //rival name finalized
        {
            StringExpandPlaceholders(gStringVar4, gOakText_RememberRivalName);
            OaksSpeechPrintMessage(gStringVar4, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech31;
        }
        break;
    case 1:
    case -1: //choose no
        PlaySE(SE_SELECT);
        if (sOakSpeechResources->hasPlayerBeenNamed == FALSE) //confirmed this just means if player
            //gTasks[taskId].func = Task_OakSpeech24; //ok think this is what I need to replace
            gTasks[taskId].func = Task_OakSpeech28; //changed, moved loop to earlier
        else
            gTasks[taskId].func = Task_OakSpeech28; //choose rival name
        break;
    }
}

static void Task_OakSpeech30(u8 taskId) //finish naming player go to rival
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        DestroyOaksSpeechTrainerPic();
        if (data[3] != 0)
            data[3]--; // think this is a loop/return, think this sends me back to previous task i.e to 29, if condition isn't met.?
        else             //no nvm this isnt gtasts.func so its something different
            gTasks[taskId].func = Task_OakSpeech32;
    }
}

static void Task_OakSpeech31(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        ClearDialogWindowAndFrame(0, 1);
        CreateFadeInTask(taskId, 2);
        gTasks[taskId].func = Task_OakSpeech33;
    }
}

static void Task_OakSpeech32(u8 taskId) //important begin rival name choice, rival-style player name select  2nd part in oakspeech35
{   //load centered sprite
    ChangeBgX(2, 0, 0);
    gTasks[taskId].data[1] = 0;
    gSpriteCoordOffsetX = 0;
    LoadOaksSpeechTrainerPic(2, 0); //create rival pic
    CreateFadeOutTask(taskId, 2);
    gTasks[taskId].func = Task_OakSpeech34;
}

static void Task_OakSpeech34(u8 taskId)//edit this to check for player set unk to 0, and ask player name
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        OaksSpeechPrintMessage(gOakText_IntroduceRival, sOakSpeechResources->textSpeed);
        sOakSpeechResources->hasPlayerBeenNamed = TRUE;
        gTasks[taskId].func = Task_OakSpeech35;
    }
}

static void Task_OakSpeech33(u8 taskId) //after naming rival
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        DestroyOaksSpeechTrainerPic(); //remove rival pic after naming him, then show player
        if (data[3] != 0)
            data[3]--;
        else
        {
            if (gSaveBlock2Ptr->playerGender == MALE)
                LoadOaksSpeechTrainerPic(MALE, 0);
            else
                LoadOaksSpeechTrainerPic(FEMALE, 0);
            gTasks[taskId].data[1] = 0;
            gSpriteCoordOffsetX = 0; //believe this puts them at center
            ChangeBgX(2, 0, 0);
            CreateFadeOutTask(taskId, 2);
            gTasks[taskId].func = Task_OakSpeech36;
        }
    }
}

static void Task_OakSpeech36(u8 taskId) //Oak's last line
{
    if (gTasks[taskId].data[2] != 0)
    {
        StringExpandPlaceholders(gStringVar4, gOakText_LegendAboutToUnfold);
        OaksSpeechPrintMessage(gStringVar4, sOakSpeechResources->textSpeed);
        VarSet(VAR_MOMS_GIFT, 0);
        gTasks[taskId].data[3] = 30;
        gTasks[taskId].func = Task_OakSpeech37;
    }
}

static void Task_OakSpeech37(u8 taskId) //last task before gamestart warp
{
    if (!IsTextPrinterActive(0))
    {
        if (gTasks[taskId].data[3] != 0)
            gTasks[taskId].data[3]--;
        else
        {
            FadeOutBGM(4);
            gTasks[taskId].func = Task_OakSpeech38;
        }
    }
}

static void Task_OakSpeech38(u8 taskId)
{
    sOakSpeechResources->currentPage = 0;
    Task_OakSpeech38_1(taskId);
    Task_OakSpeech38_2(taskId);
    Task_OakSpeech38_3(taskId);
}

static void Task_OakSpeech38_3(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    SetBgAttribute(2, 6, 1);
    data[0] = 0;
    data[1] = 0;
    data[2] = 256;
    data[15] = 0;
    gTasks[taskId].func = Task_OakSpeech39;
}

static void Task_OakSpeech39(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    s16 x, y;
    u16 r0;

    sOakSpeechResources->currentPage++;
    if (sOakSpeechResources->currentPage % 20 == 0)
    {
        if (sOakSpeechResources->currentPage == 40)
            PlaySE(SE_WARP_IN);
        r0 = data[2];
        data[2] -= 32;
        x = MathUtil_Inv16(r0 - 8);
        y = MathUtil_Inv16(data[2] - 16);
        SetBgAffine(2, 0x7800, 0x5400, 0x78, 0x54, x, y, 0);
        if (data[2] <= 96)
        {
            data[15] = 1;
            data[0] = 36;
            gTasks[taskId].func = Task_OakSpeech40;
        }
    }
}

static void Task_OakSpeech38_1(u8 taskId)
{
    u8 taskId2 = CreateTask(Task_OakSpeech38_sub1, 1);
    s16 * data = gTasks[taskId2].data;
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[15] = 0;
    BeginNormalPaletteFade(0xFFFF0FCF, 4, 0, 16, RGB_BLACK);
}

static void Task_OakSpeech38_sub1(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        if (data[1] != 0)
        {
            DestroyTask(taskId);
            DestroyLinkedPikaOrGrassPlatformSprites(taskId, 1);
        }
        else
        {
            data[1]++;
            BeginNormalPaletteFade(0x0000F000, 0, 0, 16, RGB_BLACK);
        }
    }
}

static void Task_OakSpeech38_2(u8 taskId)
{
    u8 taskId2 = CreateTask(Task_OakSpeech38_sub2, 2);
    s16 * data = gTasks[taskId2].data;
    data[0] = 8;
    data[1] = 0;
    data[2] = 8;
    data[14] = 0;
    data[15] = 0;
}

static void Task_OakSpeech38_sub2(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u8 i;

    if (data[0] != 0)
        data[0]--;
    else
    {
        if (data[1] <= 0 && data[2] != 0)
            data[2]--;
        BlendPalette(0x40, 0x20, data[14], RGB_WHITE);
        data[14]++;
        data[1]--;
        data[0] = data[2];
        if (data[14] > 14)
        {
            for (i = 0; i < 32; i++)
            {
                gPlttBufferFaded[i + 0x40] = RGB_WHITE;
                gPlttBufferUnfaded[i + 0x40] = RGB_WHITE;
            }
            DestroyTask(taskId);
        }
    }
}

static void Task_OakSpeech40(u8 taskId)
{
    if (gTasks[taskId].data[0] != 0)
        gTasks[taskId].data[0]--;
    else
    {
        BeginNormalPaletteFade(0x00000030, 2, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_OakSpeech41;
    }
}

static void Task_OakSpeech41(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_OakSpeech42;
    }
}

static void Task_OakSpeech42(u8 taskId)
{
    FreeAllWindowBuffers();
    OakSpeechNidoranFFreeResources();
    Free(sOakSpeechResources);
    sOakSpeechResources = NULL;
    gTextFlags.canABSpeedUpPrint = FALSE;
    SetMainCallback2(CB2_NewGame);
    DestroyTask(taskId);
}

static void CB2_ReturnFromNamingScreen(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        DmaFill16(3, 0, VRAM, VRAM_SIZE);
        DmaFill32(3, 0, OAM, OAM_SIZE);
        DmaFill16(3, RGB_BLACK, PLTT + sizeof(u16), PLTT_SIZE - sizeof(u16));
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetTempTileDataBuffers();
        break;
    case 1:
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(1, sBgTemplates, NELEMS(sBgTemplates));
        SetBgTilemapBuffer(1, sOakSpeechResources->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sOakSpeechResources->bg2TilemapBuffer);
        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(2, 0, 0);
        ChangeBgY(2, 0, 0);
        break;
    case 2:
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        break;
    case 3:
        FreeAllWindowBuffers();
        InitStandardTextBoxWindows();
        ResetBg0();
        LoadPalette(sHelpDocsPalette, 0, 0xe0);
        break;
    case 4:
        DecompressAndCopyTileDataToVram(1, sOakSpeechGfx_SolidColors, 0, 0, 0);
        break;
    case 5:
        if (FreeTempTileDataBuffersIfPossible())
            return;
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        CopyToBgTilemapBuffer(1, sOakSpeech_BackgroundTilemap, 0, 0);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 30, 20);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        break;
    case 6:
        taskId = CreateTask(Task_OakSpeech26, 0);
        if (sOakSpeechResources->hasPlayerBeenNamed == FALSE)
        {
            if (gSaveBlock2Ptr->playerGender == MALE)
                LoadOaksSpeechTrainerPic(MALE, 0);
            else
                LoadOaksSpeechTrainerPic(FEMALE, 0);
        }
        else
            LoadOaksSpeechTrainerPic(2, 0);
        gTasks[taskId].data[1] = -60;
        gSpriteCoordOffsetX += 60;
        ChangeBgX(2, -0x3E00, 0);
        CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(taskId, 1);
        gTasks[taskId].data[15] = 1;
        break;
    case 7:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetVBlankCallback(VBlankCB_NewGameOaksSpeech);
        gTextFlags.canABSpeedUpPrint = TRUE;
        SetMainCallback2(CB2_NewGameOaksSpeech);
        return;
    }

    gMain.state++;
}

static void CreateNidoranFSprite(u8 taskId)
{
    u8 spriteId;

    HandleLoadSpecialPokePic_DontHandleDeoxys(TRUE, OakSpeechNidoranFGetBuffer(0), SPECIES_NIDORAN_F, 0);
    LoadCompressedSpritePaletteWithTag(gSpeciesGraphics[SPECIES_NIDORAN_F].palette, SPECIES_NIDORAN_F);
    SetMultiuseSpriteTemplateToPokemon(SPECIES_NIDORAN_F, 0);
    spriteId = CreateSprite(&gMultiuseSpriteTemplate, 0x60, 0x60, 1);
    gSprites[spriteId].callback = SpriteCallbackDummy;
    gSprites[spriteId].oam.priority = 1;
    gSprites[spriteId].invisible = TRUE;
    gTasks[taskId].data[4] = spriteId;
}

static void SpriteCB_PikaSync(struct Sprite * sprite)
{
    sprite->pos2.y = gSprites[sprite->data[0]].animCmdIndex;
}

static void CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(u8 taskId, u8 state)
{
    u8 spriteId; //vsonic could I use this for battle?
    u8 i = 0;

    switch (state)
    {
    case 0:
        LoadCompressedSpriteSheet(&sOakSpeech_PikaSpriteSheets[0]);
        LoadCompressedSpriteSheet(&sOakSpeech_PikaSpriteSheets[1]);
        LoadCompressedSpriteSheet(&sOakSpeech_PikaSpriteSheets[2]);
        LoadSpritePalette(&sOakSpeech_PikaSpritePal);
        spriteId = CreateSprite(&sOakSpeech_PikaSpriteTemplates[0], 0x10, 0x11, 2);
        gSprites[spriteId].oam.priority = 0;
        gTasks[taskId].data[7] = spriteId;
        spriteId = CreateSprite(&sOakSpeech_PikaSpriteTemplates[1], 0x10, 0x09, 3);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].data[0] = gTasks[taskId].data[7];
        gSprites[spriteId].callback = SpriteCB_PikaSync;
        gTasks[taskId].data[8] = spriteId;
        spriteId = CreateSprite(&sOakSpeech_PikaSpriteTemplates[2], 0x18, 0x0D, 1);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].data[0] = gTasks[taskId].data[7];
        gSprites[spriteId].callback = SpriteCB_PikaSync;
        gTasks[taskId].data[9] = spriteId;
        break;
    case 1:
        LoadCompressedSpriteSheet(&sOakSpeech_Platform_SpriteSheet);
        LoadSpritePalette(&sOakSpeech_Platform_SpritePalette);
        for (i = 0; i < 3; i++)
        {
            spriteId = CreateSprite(&sOakSpeech_GrassPlatformSpriteTemplates[i], i * 32 + 88, 0x70, 1);
            gSprites[spriteId].oam.priority = 2;
            gSprites[spriteId].animPaused = TRUE;
            gSprites[spriteId].coordOffsetEnabled = TRUE;
            gTasks[taskId].data[7 + i] = spriteId;
        }
        break;
    }
}

static void DestroyLinkedPikaOrGrassPlatformSprites(u8 taskId, u8 state)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        DestroySprite(&gSprites[gTasks[taskId].data[7 + i]]);
    }

    switch (state)
    {
    case 0:
        FreeSpriteTilesByTag(0x1003);
        FreeSpriteTilesByTag(0x1002);
        FreeSpriteTilesByTag(0x1001);
        FreeSpritePaletteByTag(0x1001);
        break;
    case 1:
        FreeSpriteTilesByTag(0x1000);
        FreeSpritePaletteByTag(0x1000);
        break;
    }
}

static void LoadOaksSpeechTrainerPic(u16 whichPic, u16 tileOffset)
{
    u32 i;

    switch (whichPic)
    {
    case 0: // FIRE
        LoadPalette(sOakSpeechGfx_RedPal, 0x40, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_RedPic, (void *)0x06000600 + tileOffset);
        break;
    case 1: // LEAF
        LoadPalette(sOakSpeechGfx_LeafPal, 0x40, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_LeafPic, (void *)0x06000600 + tileOffset);
        break;
    case 2: // BLUE
        LoadPalette(sOakSpeechGfx_RivalPal, 0x60, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_RivalPic, (void *)0x06000600 + tileOffset);
        break;
    case 3: // OAK
        LoadPalette(sOakSpeechGfx_OakPal, 0x60, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_OakPic, (void *)0x06000600 + tileOffset);
        break;
    default:
        return;
    }

    sOakSpeechResources->trainerPicTilemapBuffer = AllocZeroed(0x60);
    for (i = 0; i < 0x60; i++)
        ((u8 *)sOakSpeechResources->trainerPicTilemapBuffer)[i] = i;
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 32, 32, 0x10);
    CopyRectToBgTilemapBufferRect(2, sOakSpeechResources->trainerPicTilemapBuffer, 0, 0, 8, 12, 11, 2, 8, 12, 0x10, (tileOffset / 64) + 0x18, 0x00);
    CopyBgTilemapBufferToVram(2);
    Free(sOakSpeechResources->trainerPicTilemapBuffer);
    sOakSpeechResources->trainerPicTilemapBuffer = 0;
}

static void DestroyOaksSpeechTrainerPic(void)
{
    FillBgTilemapBufferRect(2, 0x000, 11, 1, 8, 12, 0x10);
    CopyBgTilemapBufferToVram(2);
}

static void Task_SlowFadeIn(u8 taskId)
{
    u8 i = 0;
    if (gTasks[taskId].data[1] == 0)
    {
        gTasks[gTasks[taskId].data[0]].data[2] = 1;
        DestroyTask(taskId);
        for (i = 0; i < 3; i++)
        {
            gSprites[gTasks[taskId].data[7 + i]].invisible = TRUE;
        }
    }
    else
    {
        if (gTasks[taskId].data[4] != 0)
            gTasks[taskId].data[4]--;
        else
        {
            gTasks[taskId].data[4] = gTasks[taskId].data[3];
            gTasks[taskId].data[1]--;
            gTasks[taskId].data[2]++;
            if (gTasks[taskId].data[1] == 8)
            {
                for (i = 0; i < 3; i++)
                {
                    gSprites[gTasks[taskId].data[7 + i]].invisible ^= TRUE;
                }
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, (gTasks[taskId].data[2] * 256) + gTasks[taskId].data[1]);
        }
    }
}

static void CreateFadeInTask(u8 taskId, u8 state)
{
    u8 taskId2;
    u8 i = 0;

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_OBJ);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0x10);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    gTasks[taskId].data[2] = 0;
    taskId2 = CreateTask(Task_SlowFadeIn, 0);
    gTasks[taskId2].data[0] = taskId;
    gTasks[taskId2].data[1] = 16;
    gTasks[taskId2].data[2] = 0;
    gTasks[taskId2].data[3] = state;
    gTasks[taskId2].data[4] = state;
    for (i = 0; i < 3; i++)
    {
        gTasks[taskId2].data[7 + i] = gTasks[taskId].data[7 + i];
    }
}

static void Task_SlowFadeOut(u8 taskId)
{
    u8 i = 0;

    if (gTasks[taskId].data[1] == 16)
    {
        if (!gPaletteFade.active)
        {
            gTasks[gTasks[taskId].data[0]].data[2] = 1;
            DestroyTask(taskId);
        }
    }
    else
    {
        if (gTasks[taskId].data[4] != 0)
            gTasks[taskId].data[4]--;
        else
        {
            gTasks[taskId].data[4] = gTasks[taskId].data[3];
            gTasks[taskId].data[1] += 2;
            gTasks[taskId].data[2] -= 2;
            if (gTasks[taskId].data[1] == 8)
            {
                for (i = 0; i < 3; i++)
                {
                    gSprites[gTasks[taskId].data[7 + i]].invisible ^= TRUE;
                }
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, (gTasks[taskId].data[2] * 256) + gTasks[taskId].data[1]);
        }
    }
}

static void CreateFadeOutTask(u8 taskId, u8 state)
{
    u8 taskId2;
    u8 i = 0;

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_OBJ);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0x1000);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    gTasks[taskId].data[2] = 0;
    taskId2 = CreateTask(Task_SlowFadeOut, 0);
    gTasks[taskId2].data[0] = taskId;
    gTasks[taskId2].data[1] = 0;
    gTasks[taskId2].data[2] = 16;
    gTasks[taskId2].data[3] = state;
    gTasks[taskId2].data[4] = state;
    for (i = 0; i < 3; i++)
    {
        gTasks[taskId2].data[7 + i] = gTasks[taskId].data[7 + i];
    }
}

static void PrintNameChoiceOptions(u8 taskId, u8 state)//
{
    s16 * data = gTasks[taskId].data;
    const u8 *const * textPtrs;
    u8 i;

    data[13] = AddWindow(&sNewGameAdventureIntroWindowTemplates[3]);
    PutWindowTilemap(data[13]);
    DrawStdFrameWithCustomTileAndPalette(data[13], 1, GetStdWindowBaseTileNum(), 14);
    FillWindowPixelBuffer(gTasks[taskId].data[13], 0x11);
    AddTextPrinterParameterized(data[13], 2, gOtherText_NewName, 8, 1, 0, NULL);
    //my addition not working yet, still jumping straight to naming screen
    if (state == 0) {
        if (gSaveBlock2Ptr->playerGender == MALE) //adjusted here to emulate rival
        {
            textPtrs = sPlayerMaleNameChoices;
            for (i = 0; i < 4; i++)
            {
                AddTextPrinterParameterized(data[13], 2, textPtrs[i], 8, 16 * (i + 1) + 1, 0, NULL);
            }
            Menu_InitCursor(data[13], 2, 0, 1, 16, 5, 0);
            CopyWindowToVram(data[13], COPYWIN_BOTH);
        }
        else if (gSaveBlock2Ptr->playerGender == FEMALE)
        {
            textPtrs = sPlayerFemaleNameChoices;
            for (i = 0; i < 4; i++)
            {
                AddTextPrinterParameterized(data[13], 2, textPtrs[i], 8, 16 * (i + 1) + 1, 0, NULL);
            }
            Menu_InitCursor(data[13], 2, 0, 1, 16, 5, 0);
            CopyWindowToVram(data[13], COPYWIN_BOTH);
        }
    }
    else
        textPtrs = sRivalNameChoices;
    for (i = 0; i < 4; i++)
    {
        AddTextPrinterParameterized(data[13], 2, textPtrs[i], 8, 16 * (i + 1) + 1, 0, NULL);
    }
    Menu_InitCursor(data[13], 2, 0, 1, 16, 5, 0);
    CopyWindowToVram(data[13], COPYWIN_BOTH);
}

//ok I have no idea why I set it to 19 when the array is
//split between FR & LG and never uses the other names??
static void GetRandomPlayerName(u8 hasPlayerBeenNamed, u8 namePick) 
{
    const u8 * src;
    u8 * dest;
    u8 i;

    if (hasPlayerBeenNamed == FALSE)
    {
        if (gSaveBlock2Ptr->playerGender == MALE)
            src = sMaleNameChoices[Random() % ARRAY_COUNT(sMaleNameChoices)]; //picks a random name
        else
            src = sFemaleNameChoices[Random() % ARRAY_COUNT(sFemaleNameChoices)];
        dest = gSaveBlock2Ptr->playerName;
    }
    for (i = 0; i < PLAYER_NAME_LENGTH && src[i] != EOS; i++)
        dest[i] = src[i];
    for (; i < PLAYER_NAME_LENGTH + 1; i++)
        dest[i] = EOS;
}

static void GetDefaultName(u8 hasPlayerBeenNamed, u8 namePick) //not name selection window, but the random name set if not choose name
{
    const u8 * src;
    u8 * dest;
    u8 i;

    if (hasPlayerBeenNamed == FALSE)
    {
        if (gSaveBlock2Ptr->playerGender == MALE)
            src = sPlayerMaleNameChoices[namePick]; //picks a random name
        else
            src = sPlayerFemaleNameChoices[namePick];
        dest = gSaveBlock2Ptr->playerName;
    }
    else
    {
        src = sRivalNameChoices[namePick];//name pick think always 0, so always loads first name
        dest = gSaveBlock1Ptr->rivalName;
    }
    for (i = 0; i < PLAYER_NAME_LENGTH && src[i] != EOS; i++)
        dest[i] = src[i];
    for (; i < PLAYER_NAME_LENGTH + 1; i++)
        dest[i] = EOS;
}

/*
#undef tSpriteTimer
#undef tTrainerPicPosX
#undef tTrainerPicFadeState
#undef tTimer
#undef tNidoranFSpriteId
#undef tTextCursorSpriteId
#undef tPokeBallSpriteId
#undef tMenuWindowId
#undef tTextboxWindowId
#undef tDelta
#undef tPlayerPicFadeOutTimer
#undef tScaleDelta
#undef tPlayerIsShrunk
#undef shrinkTimer
#undef tPlayerPicFadeWhiteTimer
#undef tUnderflowingTimer
#undef tSecondaryTimer
#undef tBlendCoefficient
#undef tNameNotConfirmed
#undef sBodySpriteId
#undef tParentTaskId
#undef tBlendTarget1
#undef tBlendTarget2
#undef tUnusedState
#undef tFadeTimer
*/
