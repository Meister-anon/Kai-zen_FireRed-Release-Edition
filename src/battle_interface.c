#include "global.h"
#include "gflib.h"
#include "battle_anim.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "decompress.h"
#include "graphics.h"
#include "menu.h"
#include "pokedex.h"
#include "pokemon_summary_screen.h"
#include "safari_zone.h"
#include "constants/songs.h"

#define GetStringRightAlignXOffset(fontId, string, destWidth) ({ \
    s32 w = GetStringWidth(fontId, string, 0);                   \
    destWidth - w;                                               \
})

#undef abs
#define abs(a) ((a) < 0 ? -(a) : (a))


struct TestingBar
{
    s32 maxValue;
    s32 oldValue;
    s32 receivedValue;
    u32 pal:5;
    u32 tileOffset;
};

enum
{   // Corresponds to gHealthboxElementsGfxTable (and the tables after it) in graphics.c
    // These are indexes into the tables, which are filled with 8x8 square pixel data.
    HEALTHBOX_GFX_0, //hp bar [black section]
    HEALTHBOX_GFX_1, //hp bar "H"
    HEALTHBOX_GFX_2, //hp bar "P"
    HEALTHBOX_GFX_HP_BAR_GREEN, //hp bar [0 pixels]
    HEALTHBOX_GFX_4,  //hp bar [1 pixels]
    HEALTHBOX_GFX_5,  //hp bar [2 pixels]
    HEALTHBOX_GFX_6,  //hp bar [3 pixels]
    HEALTHBOX_GFX_7,  //hp bar [4 pixels]
    HEALTHBOX_GFX_8,  //hp bar [5 pixels]
    HEALTHBOX_GFX_9,  //hp bar [6 pixels]
    HEALTHBOX_GFX_10, //hp bar [7 pixels]
    HEALTHBOX_GFX_11, //hp bar [8 pixels]
    HEALTHBOX_GFX_12, //exp bar [0 pixels]
    HEALTHBOX_GFX_13, //exp bar [1 pixels]
    HEALTHBOX_GFX_14, //exp bar [2 pixels]
    HEALTHBOX_GFX_15, //exp bar [3 pixels]
    HEALTHBOX_GFX_16, //exp bar [4 pixels]
    HEALTHBOX_GFX_17, //exp bar [5 pixels]
    HEALTHBOX_GFX_18, //exp bar [6 pixels]
    HEALTHBOX_GFX_19, //exp bar [7 pixels]
    HEALTHBOX_GFX_20, //exp bar [8 pixels]
    HEALTHBOX_GFX_STATUS_PSN_BATTLER0,  //status psn "(P"
    HEALTHBOX_GFX_22,                   //status psn "SN"
    HEALTHBOX_GFX_23,                   //status psn "|)""
    HEALTHBOX_GFX_STATUS_PRZ_BATTLER0,  //status prz
    HEALTHBOX_GFX_25,
    HEALTHBOX_GFX_26,
    HEALTHBOX_GFX_STATUS_SLP_BATTLER0,  //status slp
    HEALTHBOX_GFX_28,
    HEALTHBOX_GFX_29,
    HEALTHBOX_GFX_STATUS_FRZ_BATTLER0,  //status frz
    HEALTHBOX_GFX_31,
    HEALTHBOX_GFX_32,
    HEALTHBOX_GFX_STATUS_BRN_BATTLER0,  //status brn
    HEALTHBOX_GFX_34,
    HEALTHBOX_GFX_35,
    HEALTHBOX_GFX_36, //misc [Black section]
    HEALTHBOX_GFX_37, //misc [Black section]
    HEALTHBOX_GFX_38, //misc [Black section]
    HEALTHBOX_GFX_39, //misc [Blank Health Window?]
    HEALTHBOX_GFX_40, //misc [Blank Health Window?]
    HEALTHBOX_GFX_41, //misc [Blank Health Window?]
    HEALTHBOX_GFX_42, //misc [Blank Health Window?]
    HEALTHBOX_GFX_43, //misc [Top of Health Window?]
    HEALTHBOX_GFX_44, //misc [Top of Health Window?]
    HEALTHBOX_GFX_45, //misc [Top of Health Window?]
    HEALTHBOX_GFX_46, //misc [Blank Health Window?]
    HEALTHBOX_GFX_HP_BAR_YELLOW, //hp bar yellow [0 pixels]
    HEALTHBOX_GFX_48, //hp bar yellow [1 pixels]
    HEALTHBOX_GFX_49, //hp bar yellow [2 pixels]
    HEALTHBOX_GFX_50, //hp bar yellow [3 pixels]
    HEALTHBOX_GFX_51, //hp bar yellow [4 pixels]
    HEALTHBOX_GFX_52, //hp bar yellow [5 pixels]
    HEALTHBOX_GFX_53, //hp bar yellow [6 pixels]
    HEALTHBOX_GFX_54, //hp bar yellow [7 pixels]
    HEALTHBOX_GFX_55, //hp bar yellow [8 pixels]
    HEALTHBOX_GFX_HP_BAR_RED,  //hp bar red [0 pixels]
    HEALTHBOX_GFX_57, //hp bar red [1 pixels]
    HEALTHBOX_GFX_58, //hp bar red [2 pixels]
    HEALTHBOX_GFX_59, //hp bar red [3 pixels]
    HEALTHBOX_GFX_60, //hp bar red [4 pixels]
    HEALTHBOX_GFX_61, //hp bar red [5 pixels]
    HEALTHBOX_GFX_62, //hp bar red [6 pixels]
    HEALTHBOX_GFX_63, //hp bar red [7 pixels]
    HEALTHBOX_GFX_64, //hp bar red [8 pixels]
    HEALTHBOX_GFX_65, //hp bar frame end
    HEALTHBOX_GFX_66, //status ball [full]
    HEALTHBOX_GFX_67, //status ball [empty]
    HEALTHBOX_GFX_68, //status ball [fainted]
    HEALTHBOX_GFX_69, //status ball [statused]
    HEALTHBOX_GFX_70, //status ball [unused extra]
    HEALTHBOX_GFX_STATUS_PSN_BATTLER1, //status2 "PSN"
    HEALTHBOX_GFX_72,
    HEALTHBOX_GFX_73,
    HEALTHBOX_GFX_STATUS_PRZ_BATTLER1, //status2 "PRZ"
    HEALTHBOX_GFX_75,
    HEALTHBOX_GFX_76,
    HEALTHBOX_GFX_STATUS_SLP_BATTLER1, //status2 "SLP"
    HEALTHBOX_GFX_78,
    HEALTHBOX_GFX_79,
    HEALTHBOX_GFX_STATUS_FRZ_BATTLER1, //status2 "FRZ"
    HEALTHBOX_GFX_81,
    HEALTHBOX_GFX_82,
    HEALTHBOX_GFX_STATUS_BRN_BATTLER1, //status2 "BRN"
    HEALTHBOX_GFX_84,
    HEALTHBOX_GFX_85,
    HEALTHBOX_GFX_STATUS_PSN_BATTLER2, //status3 "PSN"
    HEALTHBOX_GFX_87,
    HEALTHBOX_GFX_88,
    HEALTHBOX_GFX_STATUS_PRZ_BATTLER2, //status3 "PRZ"
    HEALTHBOX_GFX_90,
    HEALTHBOX_GFX_91,
    HEALTHBOX_GFX_STATUS_SLP_BATTLER2, //status3 "SLP"
    HEALTHBOX_GFX_93,
    HEALTHBOX_GFX_94,
    HEALTHBOX_GFX_STATUS_FRZ_BATTLER2, //status3 "FRZ"
    HEALTHBOX_GFX_96,
    HEALTHBOX_GFX_97,
    HEALTHBOX_GFX_STATUS_BRN_BATTLER2, //status3 "BRN"
    HEALTHBOX_GFX_99,
    HEALTHBOX_GFX_100,
    HEALTHBOX_GFX_STATUS_PSN_BATTLER3, //status4 "PSN"
    HEALTHBOX_GFX_102,
    HEALTHBOX_GFX_103,
    HEALTHBOX_GFX_STATUS_PRZ_BATTLER3, //status4 "PRZ"
    HEALTHBOX_GFX_105,
    HEALTHBOX_GFX_106,
    HEALTHBOX_GFX_STATUS_SLP_BATTLER3, //status4 "SLP"
    HEALTHBOX_GFX_108,
    HEALTHBOX_GFX_109,
    HEALTHBOX_GFX_STATUS_FRZ_BATTLER3, //status4 "FRZ"
    HEALTHBOX_GFX_111,
    HEALTHBOX_GFX_112,
    HEALTHBOX_GFX_STATUS_BRN_BATTLER3, //status4 "BRN"
    HEALTHBOX_GFX_114,
    HEALTHBOX_GFX_115,
    HEALTHBOX_GFX_116, //unknown_D12FEC
    HEALTHBOX_GFX_117, //unknown_D1300C
};

// Because the healthbox is too large to fit into one sprite, it is divided
// into two sprites. The left sprite is used as the 'main' healthbox sprite,
// while the right sprite is the 'other' healthbox sprite.
// There is also a third sprite for the healthbar, visible on the healthbox.

// sprite data for main (left) healthbox sprite
#define sHealthboxOtherSpriteId oam.affineParam
#define sHealthBarSpriteId      data[5]
#define sBattlerId              data[6]

// sprite data for other (right) healthbox sprite
#define sHealthboxSpriteId      data[5]

// sprite data for healthbar sprite
#define sHealthboxSpriteId      data[5]
#define sHealthbarType          data[6]

static void SpriteCB_HealthBoxOther(struct Sprite * sprite);
static void SpriteCB_HealthBar(struct Sprite * sprite);
static const u8 *GetHealthboxElementGfxPtr(u8 which);
static void UpdateHpTextInHealthboxInDoubles(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent);
static void sub_8049388(u8 taskId);
static void sub_80493E4(u8 taskId);
static void sub_8049568(struct Sprite * sprite);
static void sub_8049630(struct Sprite * sprite);
static void sub_804948C(u8 taskId);
static void SpriteCB_StatusSummaryBallsOnSwitchout(struct Sprite * sprite);
static void UpdateStatusIconInHealthbox(u8 spriteId);
static void SpriteCB_StatusSummaryBar(struct Sprite * sprite);
static void SpriteCB_StatusSummaryBallsOnBattleStart(struct Sprite * sprite);
static u8 GetStatusIconForBattlerId(u8 statusElementId, u8 battlerId);
static void MoveBattleBarGraphically(u8 battlerId, u8 whichBar);
static u8 GetScaledExpFraction(s32 oldValue, s32 receivedValue, s32 maxValue, u8 scale);
static u8 CalcBarFilledPixels(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 *arg4, u8 scale);
static s32 CalcNewBarValue(s32 maxValue, s32 currValue, s32 receivedValue, s32 *arg3, u8 arg4, u16 arg5);
static void sub_804A510(struct TestingBar *barInfo, s32 *currValue, u8 bg, u8 x, u8 y);
static void SafariTextIntoHealthboxObject(void *dest, u8 *windowTileData, u32 windowWidth);
static u8 *AddTextPrinterAndCreateWindowOnHealthbox(const u8 *str, u32 x, u32 y, u32 *windowId);
static void RemoveWindowOnHealthbox(u32 windowId);
static void TextIntoHealthboxObject(void *dest, u8 *windowTileData, s32 windowWidth);
//void CreateAbilityPopUp(u8 battlerId, u32 ability, bool32 isDoubleBattle)

static const struct OamData gOamData_8260270 = {
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .priority = 1
};

static const struct SpriteTemplate sHealthboxPlayerSpriteTemplates[] = {
    {
        .tileTag = 55039,
        .paletteTag = 55039,
        .oam = &gOamData_8260270,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }, {
        .tileTag = 55040,
        .paletteTag = 55039,
        .oam = &gOamData_8260270,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }
};

static const struct SpriteTemplate sHealthboxOpponentSpriteTemplates[] = {
    {
        .tileTag = 55041,
        .paletteTag = 55039,
        .oam = &gOamData_8260270,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }, {
        .tileTag = 55042,
        .paletteTag = 55039,
        .oam = &gOamData_8260270,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }
};

static const struct SpriteTemplate sHealthboxSafariSpriteTemplate =
{
    .tileTag = 55051,
    .paletteTag = 55039,
    .oam = &gOamData_8260270,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct OamData gUnknown_82602F0 = {
    .shape = SPRITE_SHAPE(32x8),
    .size = SPRITE_SIZE(32x8),
    .priority = 1
};

static const struct SpriteTemplate gUnknown_82602F8[] = {
    {
        .tileTag = 55044,
        .paletteTag = 55044,
        .oam = &gUnknown_82602F0,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    }, {
        .tileTag = 55045,
        .paletteTag = 55044,
        .oam = &gUnknown_82602F0,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    }, {
        .tileTag = 55046,
        .paletteTag = 55044,
        .oam = &gUnknown_82602F0,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    }, {
        .tileTag = 55047,
        .paletteTag = 55044,
        .oam = &gUnknown_82602F0,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_HealthBar
    }
};

/*   v-- Origin
[0   +         ][1     ]
[              ][      ]
[              ][      ]
[______________][______]   96x40
[2     ][3     ][4     ]
*/

static const struct Subsprite gUnknown_8260358[] = {
    { 240, 0, SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 0x0000, 1 },
    { 48, 0, SPRITE_SHAPE(32x32), SPRITE_SIZE(32x32), 0x0020, 1 },
    { 240, 32, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0030, 1 },
    { 16, 32, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0034, 1 },
    { 48, 32, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0038, 1 }
};

static const struct Subsprite gUnknown_826036C[] = {
    { 240, 0, SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 0x0040, 1 },
    { 48, 0, SPRITE_SHAPE(32x32), SPRITE_SIZE(32x32), 0x0060, 1 },
    { 240, 32, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0070, 1 },
    { 16, 32, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0074, 1 },
    { 48, 32, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0078, 1 }
};

static const struct Subsprite gUnknown_8260380[] = {
    { 240, 0, SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 0x0000, 1 },
    { 48, 0, SPRITE_SHAPE(32x32), SPRITE_SIZE(32x32), 0x0020, 1 }
};

static const struct Subsprite gUnknown_8260388[] = {
    { 240, 0, SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), 0x0000, 1 },
    { 48, 0, SPRITE_SHAPE(32x32), SPRITE_SIZE(32x32), 0x0020, 1 }
};

static const struct Subsprite gUnknown_8260390[] = {
    { 240, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0000, 1 },
    { 16, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0004, 1 }
};

static const struct Subsprite gUnknown_8260398[] = {
    { 240, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0000, 1 },
    { 16, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0004, 1 },
    { 224, 0, SPRITE_SHAPE(8x8), SPRITE_SIZE(8x8), 0x0008, 1 }
};

static const struct SubspriteTable gUnknown_82603A4[] = {
    {NELEMS(gUnknown_8260358), gUnknown_8260358},
    {NELEMS(gUnknown_8260380), gUnknown_8260380},
    {NELEMS(gUnknown_826036C), gUnknown_826036C},
    {NELEMS(gUnknown_8260388), gUnknown_8260388}
};

static const struct SubspriteTable gUnknown_82603C4[] = {
    {NELEMS(gUnknown_8260390), gUnknown_8260390},
    {NELEMS(gUnknown_8260398), gUnknown_8260398}
};

static const struct Subsprite gUnknown_82603D4[] = {
    { 160, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0000, 1 },
    { 192, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0004, 1 },
    { 224, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0008, 1 },
    { 0, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x000c, 1 }
};

static const struct Subsprite gUnknown_82603E4[] = {
    { 160, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0000, 1 },
    { 192, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0004, 1 },
    { 224, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0008, 1 },
    { 0, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0008, 1 },
    { 32, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x0008, 1 },
    { 64, 0, SPRITE_SHAPE(32x8), SPRITE_SIZE(32x8), 0x000c, 1 }
};

static const struct SubspriteTable sStatusSummaryBar_SubspriteTable[] =
{
    {NELEMS(gUnknown_82603D4), gUnknown_82603D4}
};

static const struct SubspriteTable gUnknown_8260404[] = {
    {NELEMS(gUnknown_82603E4), gUnknown_82603E4}
};

static const u16 gUnknown_26040C[] = INCBIN_U16("graphics/battle_interface/unk_826404C.4bpp");

static const struct CompressedSpriteSheet sStatusSummaryBarSpriteSheets[] = {
    {gFile_graphics_battle_interface_ball_status_bar_sheet, 0x0200, 55052},
    {gFile_graphics_battle_interface_ball_status_bar_sheet, 0x0200, 55053}
};

static const struct SpritePalette sStatusSummaryBarSpritePals[] = {
    {gBattleInterface_BallStatusBarPal, 55056},
    {gBattleInterface_BallStatusBarPal, 55057}
};

static const struct SpritePalette sStatusSummaryBallsSpritePals[] = {
    {gBattleInterface_BallDisplayPal, 55058},
    {gBattleInterface_BallDisplayPal, 55059}
};

static const struct SpriteSheet sStatusSummaryBallsSpriteSheets[] = {
    {gUnknown_8D12404, 0x0080, 55060},
    {gUnknown_8D12404, 0x0080, 55061}
};

static const struct OamData gUnknown_82604AC = {
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .priority = 1
};

static const struct OamData gUnknown_82604B4 = {
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = 1
};

static const struct SpriteTemplate sStatusSummaryBarSpriteTemplates[] = {
    {
        .tileTag = 55052,
        .paletteTag = 55056,
        .oam = &gOamData_8260270,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBar
    }, {
        .tileTag = 55053,
        .paletteTag = 55057,
        .oam = &gOamData_8260270,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBar
    }
};

static const struct SpriteTemplate sStatusSummaryBallsSpriteTemplates[] = {
    {
        .tileTag = 55060,
        .paletteTag = 55058,
        .oam = &gUnknown_82604B4,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBallsOnBattleStart
    }, {
        .tileTag = 55061,
        .paletteTag = 55059,
        .oam = &gUnknown_82604B4,
        .anims = gDummySpriteAnimTable,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCB_StatusSummaryBallsOnBattleStart
    }
};

static void sub_8047B0C(s16 number, u16 *dest, bool8 unk)
{
    s8 i, j;
    u8 buff[4];

    for (i = 0; i < 4; i++)
    {
        buff[i] = 0;
    }

    for (i = 3; ; i--)
    {
        if (number > 0)
        {
            buff[i] = number % 10;
            number /= 10;
        }
        else
        {
            for (; i > -1; i--)
            {
                buff[i] = 0xFF;
            }
            if (buff[3] == 0xFF)
                buff[3] = 0;
            break;
        }
    }



    if (!unk)
    {
        for (i = 0, j = 0; i < 4; i++)
        {
            if (buff[j] == 0xFF)
            {
                dest[j + 0x00] &= 0xFC00;
                dest[j + 0x00] |= 0x1E;
                dest[i + 0x20] &= 0xFC00;
                dest[i + 0x20] |= 0x1E;
            }
            else
            {
                dest[j + 0x00] &= 0xFC00;
                dest[j + 0x00] |= 0x14 + buff[j];
                dest[i + 0x20] &= 0xFC00;
                dest[i + 0x20] |= 0x34 + buff[i];
            }
            j++;
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            if (buff[i] == 0xFF)
            {
                dest[i + 0x00] &= 0xFC00;
                dest[i + 0x00] |= 0x1E;
                dest[i + 0x20] &= 0xFC00;
                dest[i + 0x20] |= 0x1E;
            }
            else
            {
                dest[i + 0x00] &= 0xFC00;
                dest[i + 0x00] |= 0x14 + buff[i];
                dest[i + 0x20] &= 0xFC00;
                dest[i + 0x20] |= 0x34 + buff[i];
            }
        }
    }
}

static void sub_8047CAC(s16 num1, s16 num2, u16 *dest)
{
    dest[4] = 0x1E;
    sub_8047B0C(num2, &dest[0], FALSE);
    sub_8047B0C(num1, &dest[5], TRUE);
}

// Because the healthbox is too large to fit into one sprite, it is divided into two sprites.
// healthboxLeft  or healthboxMain  is the left part that is used as the 'main' sprite.
// healthboxRight or healthboxOther is the right part of the healthbox.
// There's also the third sprite under name of healthbarSprite that refers to the healthbar visible on the healtbox.

// data fields for healthboxMain
// oam.affineParam holds healthboxRight spriteId
#define hMain_HealthBarSpriteId     data[5]
#define hMain_Battler               data[6]
#define hMain_Data7                 data[7]

// data fields for healthboxRight
#define hOther_HealthBoxSpriteId    data[5]

// data fields for healthbar
#define hBar_HealthBoxSpriteId      data[5]
#define hBar_Data6                  data[6]

u8 CreateBattlerHealthboxSprites(u8 a)
{
    s16 data6 = 0;
    u8 healthboxLeftSpriteId;
    u8 healthboxRightSpriteId;
    u8 healthbarSpriteId;
    struct Sprite *sprite;

    if (!IsDoubleBattle())
    {
        if (GetBattlerSide(a) == B_SIDE_PLAYER)
        {
            healthboxLeftSpriteId = CreateSprite(&sHealthboxPlayerSpriteTemplates[0], 240, 160, 1);
            healthboxRightSpriteId = CreateSpriteAtEnd(&sHealthboxPlayerSpriteTemplates[0], 240, 160, 1);

            gSprites[healthboxLeftSpriteId].oam.shape = SPRITE_SHAPE(64x64);
            gSprites[healthboxRightSpriteId].oam.shape = SPRITE_SHAPE(64x64);
            gSprites[healthboxRightSpriteId].oam.tileNum += 64;
        }
        else
        {
            healthboxLeftSpriteId = CreateSprite(&sHealthboxOpponentSpriteTemplates[0], 240, 160, 1);
            healthboxRightSpriteId = CreateSpriteAtEnd(&sHealthboxOpponentSpriteTemplates[0], 240, 160, 1);

            gSprites[healthboxRightSpriteId].oam.tileNum += 32;
            data6 = 2;
        }

        gSprites[healthboxLeftSpriteId].oam.affineParam = healthboxRightSpriteId;
        gSprites[healthboxRightSpriteId].hBar_HealthBoxSpriteId = healthboxLeftSpriteId;
        gSprites[healthboxRightSpriteId].callback = SpriteCB_HealthBoxOther;
    }
    else
    {
        if (GetBattlerSide(a) == B_SIDE_PLAYER)
        {
            healthboxLeftSpriteId = CreateSprite(&sHealthboxPlayerSpriteTemplates[GetBattlerPosition(a) / 2], 240, 160, 1);
            healthboxRightSpriteId = CreateSpriteAtEnd(&sHealthboxPlayerSpriteTemplates[GetBattlerPosition(a) / 2], 240, 160, 1);

            gSprites[healthboxLeftSpriteId].oam.affineParam = healthboxRightSpriteId;
            gSprites[healthboxRightSpriteId].hBar_HealthBoxSpriteId = healthboxLeftSpriteId;
            gSprites[healthboxRightSpriteId].oam.tileNum += 32;
            gSprites[healthboxRightSpriteId].callback = SpriteCB_HealthBoxOther;
            data6 = 1;
        }
        else
        {
            healthboxLeftSpriteId = CreateSprite(&sHealthboxOpponentSpriteTemplates[GetBattlerPosition(a) / 2], 240, 160, 1);
            healthboxRightSpriteId = CreateSpriteAtEnd(&sHealthboxOpponentSpriteTemplates[GetBattlerPosition(a) / 2], 240, 160, 1);

            gSprites[healthboxLeftSpriteId].oam.affineParam = healthboxRightSpriteId;
            gSprites[healthboxRightSpriteId].hBar_HealthBoxSpriteId = healthboxLeftSpriteId;
            gSprites[healthboxRightSpriteId].oam.tileNum += 32;
            gSprites[healthboxRightSpriteId].callback = SpriteCB_HealthBoxOther;
            data6 = 2;
        }
    }
    healthbarSpriteId = CreateSpriteAtEnd(&gUnknown_82602F8[gBattlerPositions[a]], 140, 60, 0);
    sprite = &gSprites[healthbarSpriteId];
    SetSubspriteTables(sprite, &gUnknown_82603C4[GetBattlerSide(a)]);
    sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
    sprite->oam.priority = 1;
    CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_1), OBJ_VRAM0 + sprite->oam.tileNum * 32, 64);

    gSprites[healthboxLeftSpriteId].hBar_HealthBoxSpriteId = healthbarSpriteId;
    gSprites[healthboxLeftSpriteId].hBar_Data6 = a;
    gSprites[healthboxLeftSpriteId].invisible = TRUE;
    gSprites[healthboxRightSpriteId].invisible = TRUE;
    sprite->data[5] = healthboxLeftSpriteId;
    sprite->data[6] = data6;
    sprite->invisible = TRUE;

    return healthboxLeftSpriteId;
}

u8 CreateSafariPlayerHealthboxSprites(void)
{
    u8 healthboxLeftSpriteId = CreateSprite(&sHealthboxSafariSpriteTemplate, 240, 160, 1);
    u8 healthboxRightSpriteId = CreateSpriteAtEnd(&sHealthboxSafariSpriteTemplate, 240, 160, 1);

    gSprites[healthboxLeftSpriteId].oam.shape = SPRITE_SHAPE(64x64);
    gSprites[healthboxRightSpriteId].oam.shape = SPRITE_SHAPE(64x64);
    gSprites[healthboxRightSpriteId].oam.tileNum += 0x40;
    gSprites[healthboxLeftSpriteId].oam.affineParam = healthboxRightSpriteId;
    gSprites[healthboxRightSpriteId].hBar_HealthBoxSpriteId = healthboxLeftSpriteId;
    gSprites[healthboxRightSpriteId].callback = SpriteCB_HealthBoxOther;
    return healthboxLeftSpriteId;
}

static const u8 *GetHealthboxElementGfxPtr(u8 elementId)
{
    return gHealthboxElementsGfxTable[elementId];
}

// Syncs the position of healthbar accordingly with the healthbox.
static void SpriteCB_HealthBar(struct Sprite *sprite)
{
    u8 r5 = sprite->data[5];

    switch (sprite->data[6])
    {
    case 0:
        sprite->pos1.x = gSprites[r5].pos1.x + 16;
        sprite->pos1.y = gSprites[r5].pos1.y;
        break;
    case 1:
        sprite->pos1.x = gSprites[r5].pos1.x + 16;
        sprite->pos1.y = gSprites[r5].pos1.y;
        break;
    default:
    case 2:
        sprite->pos1.x = gSprites[r5].pos1.x + 8;
        sprite->pos1.y = gSprites[r5].pos1.y;
        break;
    }
    sprite->pos2.x = gSprites[r5].pos2.x;
    sprite->pos2.y = gSprites[r5].pos2.y;
}

static void SpriteCB_HealthBoxOther(struct Sprite *sprite)
{
    u8 healthboxMainSpriteId = sprite->hOther_HealthBoxSpriteId;

    sprite->pos1.x = gSprites[healthboxMainSpriteId].pos1.x + 64;
    sprite->pos1.y = gSprites[healthboxMainSpriteId].pos1.y;

    sprite->pos2.x = gSprites[healthboxMainSpriteId].pos2.x;
    sprite->pos2.y = gSprites[healthboxMainSpriteId].pos2.y;
}

void SetBattleBarStruct(u8 battlerId, u8 healthboxSpriteId, s32 maxVal, s32 oldVal, s32 receivedValue)
{
    gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId = healthboxSpriteId;
    gBattleSpritesDataPtr->battleBars[battlerId].maxValue = maxVal;
    gBattleSpritesDataPtr->battleBars[battlerId].oldValue = oldVal;
    gBattleSpritesDataPtr->battleBars[battlerId].receivedValue = receivedValue;
    gBattleSpritesDataPtr->battleBars[battlerId].currValue = -32768;
}

void SetHealthboxSpriteInvisible(u8 healthboxSpriteId)
{
    gSprites[healthboxSpriteId].invisible = TRUE;
    gSprites[gSprites[healthboxSpriteId].hMain_HealthBarSpriteId].invisible = TRUE;
    gSprites[gSprites[healthboxSpriteId].oam.affineParam].invisible = TRUE;
}

void SetHealthboxSpriteVisible(u8 healthboxSpriteId)
{
    gSprites[healthboxSpriteId].invisible = FALSE;
    gSprites[gSprites[healthboxSpriteId].hMain_HealthBarSpriteId].invisible = FALSE;
    gSprites[gSprites[healthboxSpriteId].oam.affineParam].invisible = FALSE;
}

static void UpdateSpritePos(u8 spriteId, s16 x, s16 y)
{
    gSprites[spriteId].pos1.x = x;
    gSprites[spriteId].pos1.y = y;
}

void DestoryHealthboxSprite(u8 healthboxSpriteId)
{
    DestroySprite(&gSprites[gSprites[healthboxSpriteId].oam.affineParam]);
    DestroySprite(&gSprites[gSprites[healthboxSpriteId].hMain_HealthBarSpriteId]);
    DestroySprite(&gSprites[healthboxSpriteId]);
}

void DummyBattleInterfaceFunc(u8 healthboxSpriteId, bool8 isDoubleBattleBattlerOnly)
{

}

void UpdateOamPriorityInAllHealthboxes(u8 priority)
{
    s32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        u8 healthboxLeftSpriteId = gHealthboxSpriteIds[i];
        u8 healthboxRightSpriteId = gSprites[gHealthboxSpriteIds[i]].oam.affineParam;
        u8 healthbarSpriteId = gSprites[gHealthboxSpriteIds[i]].hMain_HealthBarSpriteId;

        gSprites[healthboxLeftSpriteId].oam.priority = priority;
        gSprites[healthboxRightSpriteId].oam.priority = priority;
        gSprites[healthbarSpriteId].oam.priority = priority;
    }
}

void InitBattlerHealthboxCoords(u8 battler)
{
    s16 x = 0, y = 0;

    if (!IsDoubleBattle())
    {
        if (GetBattlerSide(battler) != B_SIDE_PLAYER)
            x = 44, y = 30;
        else
            x = 158, y = 88;
    }
    else
    {
        switch (GetBattlerPosition(battler))
        {
        case B_POSITION_PLAYER_LEFT:
            x = 159, y = 75;
            break;
        case B_POSITION_PLAYER_RIGHT:
            x = 171, y = 100;
            break;
        case B_POSITION_OPPONENT_LEFT:
            x = 44, y = 19;
            break;
        case B_POSITION_OPPONENT_RIGHT:
            x = 32, y = 44;
            break;
        }
    }

    UpdateSpritePos(gHealthboxSpriteIds[battler], x, y);
}

static void UpdateLvlInHealthbox(u8 healthboxSpriteId, u8 lvl)
{
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    u8 text[16] = _("{LV_2}");
    u32 xPos, var1;
    void *objVram;

    xPos = (u32) ConvertIntToDecimalStringN(text + 2, lvl, STR_CONV_MODE_LEFT_ALIGN, 3);
    // Alright, that part was unmatchable. It's basically doing:
    // xPos = 5 * (3 - (u32)(&text[2]));
    xPos--;
    xPos--;
    xPos -= ((u32)(text));
    var1 = (3 - xPos);
    xPos = 4 * var1;
    xPos += var1;

    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, xPos, 3, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;

    if (GetBattlerSide(gSprites[healthboxSpriteId].hMain_Battler) == B_SIDE_PLAYER)
    {
        objVram = (void*)(OBJ_VRAM0);
        if (!IsDoubleBattle())
            objVram += spriteTileNum + 0x820;
        else
            objVram += spriteTileNum + 0x420;
    }
    else
    {
        objVram = (void*)(OBJ_VRAM0);
        objVram += spriteTileNum + 0x400;
    }
    TextIntoHealthboxObject(objVram, windowTileData, 3);
    RemoveWindowOnHealthbox(windowId);
}

void UpdateHpTextInHealthbox(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent)
{
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    u8 *strptr;
    void *objVram;

    if (GetBattlerSide(gSprites[healthboxSpriteId].hMain_Battler) == B_SIDE_PLAYER && !IsDoubleBattle())
    {
        u8 text[8];
        if (maxOrCurrent != HP_CURRENT) // singles, max
        {
            ConvertIntToDecimalStringN(text, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 0, 5, &windowId);
            spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum;
            TextIntoHealthboxObject( (void*)(OBJ_VRAM0) + spriteTileNum * TILE_SIZE_4BPP + 0xA40, windowTileData, 2);
            RemoveWindowOnHealthbox(windowId);
        }
        else // singles, current
        {
            strptr = ConvertIntToDecimalStringN(text, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            *strptr++ = CHAR_SLASH;
            *strptr++ = EOS;
            windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 4, 5, &windowId);
            spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum;
            TextIntoHealthboxObject((void *)(OBJ_VRAM0) + spriteTileNum * TILE_SIZE_4BPP + 0x2E0, windowTileData, 1);
            TextIntoHealthboxObject((void *)(OBJ_VRAM0) + spriteTileNum * TILE_SIZE_4BPP + 0xA00, windowTileData + 0x20, 2);
            RemoveWindowOnHealthbox(windowId);
        }
    }
    else
    {
        u8 battler;

        u8 text[20] = __("{COLOR 01}{HIGHLIGHT 02}");
        battler = gSprites[healthboxSpriteId].hMain_Battler;
        if (IsDoubleBattle() == TRUE || GetBattlerSide(battler) == B_SIDE_OPPONENT)
        {
            UpdateHpTextInHealthboxInDoubles(healthboxSpriteId, value, maxOrCurrent);
        }
        else
        {
            u32 var;
            u8 i;

            if (GetBattlerSide(gSprites[healthboxSpriteId].data[6]) == B_SIDE_PLAYER)
            {
                if (maxOrCurrent == HP_CURRENT)
                    var = 29;
                else
                    var = 89;
            }
            else
            {
                if (maxOrCurrent == HP_CURRENT)
                    var = 20;
                else
                    var = 48;
            }

            ConvertIntToDecimalStringN(text + 6, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            RenderTextFont9(gMonSpritesGfxPtr->barFontGfx, 0, text, 0, 0, 0, 0, 0);

            for (i = 0; i < 3; i++)
            {
                CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[i * 64 + 32],
                          (void*)((OBJ_VRAM0) + TILE_SIZE_4BPP * (gSprites[healthboxSpriteId].oam.tileNum + var + i)),
                          0x20);
            }
        }
    }
}

static const u8 gUnknown_8260540[] = _("/");

static void UpdateHpTextInHealthboxInDoubles(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent)
{
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    void *objVram;

    u8 battlerId;

    u8 text[20] = __("{COLOR 01}{HIGHLIGHT 00}");
    battlerId = gSprites[healthboxSpriteId].hMain_Battler;

    if (gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars) // don't print text if only bars are visible
    {
        u8 var = 4;
        u8 r7;
        u8 *txtPtr;
        u8 i;

        if (maxOrCurrent == HP_CURRENT)
            var = 0;

        r7 = gSprites[healthboxSpriteId].data[5];
        txtPtr = ConvertIntToDecimalStringN(text + 6, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
        if (!maxOrCurrent)
            StringCopy(txtPtr, gUnknown_8260540);
        RenderTextFont9(gMonSpritesGfxPtr->barFontGfx, 0, text, 0, 0, 0, 0, 0);

        for (i = var; i < var + 3; i++)
        {
            if (i < 3)
            {
                CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[((i - var) * 64) + 32],
                          (void*)((OBJ_VRAM0) + 32 * (1 + gSprites[r7].oam.tileNum + i)),
                          0x20);
            }
            else
            {
                CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[((i - var) * 64) + 32],
                          (void*)((OBJ_VRAM0 + 0x20) + 32 * (i + gSprites[r7].oam.tileNum)),
                          0x20);
            }
        }

        if (maxOrCurrent == HP_CURRENT)
        {
            CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[224],
                      (void*)((OBJ_VRAM0) + ((gSprites[r7].oam.tileNum + 4) * TILE_SIZE_4BPP)),
                      0x20);
            CpuFill32(0, (void*)((OBJ_VRAM0) + (gSprites[r7].oam.tileNum * TILE_SIZE_4BPP)), 0x20);
        }
        else
        {
            if (GetBattlerSide(battlerId) == B_SIDE_PLAYER) // Impossible to reach part, because the battlerId is from the opponent's side.
            {
                CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_116), //dang its a good thing I kept notes on the previous values of those things.
                          (void*)(OBJ_VRAM0) + ((gSprites[healthboxSpriteId].oam.tileNum + 52) * TILE_SIZE_4BPP),
                          0x20);
            }
        }
    }
}

// Prints mon's nature, catch and flee rate. Probably used to test pokeblock-related features.
static void PrintSafariMonInfo(u8 healthboxSpriteId, struct Pokemon *mon)
{
    u8 text[20] = __("{COLOR 01}{HIGHLIGHT 02}");
    s32 j, spriteTileNum;
    u8 *barFontGfx;
    u8 i, var, nature, healthBarSpriteId;

    barFontGfx = &gMonSpritesGfxPtr->barFontGfx[0x520 + (GetBattlerPosition(gSprites[healthboxSpriteId].hMain_Battler) * 384)];
    var = 5;
    nature = GetNature(mon);
    StringCopy(text + 6, gNatureNamePointers[nature]);
    RenderTextFont9(barFontGfx, 0, text, 0, 0, 0, 0, 0);

    for (j = 6, i = 0; i < var; i++, j++)
    {
        u8 elementId;

        if ((text[j] >= 55 && text[j] <= 74) || (text[j] >= 135 && text[j] <= 154))
            elementId = HEALTHBOX_GFX_44;
        else if ((text[j] >= 75 && text[j] <= 79) || (text[j] >= 155 && text[j] <= 159))
            elementId = HEALTHBOX_GFX_45;
        else
            elementId = HEALTHBOX_GFX_43;

        CpuCopy32(GetHealthboxElementGfxPtr(elementId), barFontGfx + (i * 64), 0x20);
    }

    for (j = 1; j < var + 1; j++)
    {
        spriteTileNum = (gSprites[healthboxSpriteId].oam.tileNum + (j - (j / 8 * 8)) + (j / 8 * 64)) * TILE_SIZE_4BPP;
        CpuCopy32(barFontGfx, (void*)(OBJ_VRAM0) + (spriteTileNum), 0x20);
        barFontGfx += 0x20;

        spriteTileNum = (8 + gSprites[healthboxSpriteId].oam.tileNum + (j - (j / 8 * 8)) + (j / 8 * 64)) * TILE_SIZE_4BPP;
        CpuCopy32(barFontGfx, (void*)(OBJ_VRAM0) + (spriteTileNum), 0x20);
        barFontGfx += 0x20;
    }

    healthBarSpriteId = gSprites[healthboxSpriteId].hMain_HealthBarSpriteId;
    ConvertIntToDecimalStringN(text + 6, gBattleStruct->safariCatchFactor, STR_CONV_MODE_RIGHT_ALIGN, 2);
    ConvertIntToDecimalStringN(text + 9, gBattleStruct->safariEscapeFactor, STR_CONV_MODE_RIGHT_ALIGN, 2);
    text[5] = CHAR_SPACE;
    text[8] = CHAR_SLASH;
    RenderTextFont9(gMonSpritesGfxPtr->barFontGfx, 0, text, 0, 0, 0, 0, 0);

    j = healthBarSpriteId; // Needed to match for some reason.
    for (j = 0; j < 5; j++)
    {
        if (j <= 1)
        {
            CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[0x40 * j + 0x20],
                      (void*)(OBJ_VRAM0) + (gSprites[healthBarSpriteId].oam.tileNum + 2 + j) * TILE_SIZE_4BPP,
                      32);
        }
        else
        {
            CpuCopy32(&gMonSpritesGfxPtr->barFontGfx[0x40 * j + 0x20],
                      (void*)(OBJ_VRAM0 + 0xC0) + (j + gSprites[healthBarSpriteId].oam.tileNum) * TILE_SIZE_4BPP,
                      32);
        }
    }
}

void SwapHpBarsWithHpText(void)
{
    s32 i;
    u8 healthBarSpriteId;

    for (i = 0; i < gBattlersCount; i++)
    {
        //ok think was able to mostly fix, part of the issue seemed to be
        //missing enemey side logic in updatehealthboxattribute function,
        //it never had hp logic for the enemy side
        if (gSprites[gHealthboxSpriteIds[i]].callback == SpriteCallbackDummy //without that works but not fully right,
            //&& GetBattlerSide(i) != B_SIDE_OPPONENT                       //piece of hp bar still showing for opponent
            && (IsDoubleBattle() || GetBattlerSide(i) != B_SIDE_PLAYER))    //and doesn't clear well when change menu
        {
            bool8 noBars;   //simple thing make it load back to hp bars when change menu/page
                            //it works correctly for player side
                            //want to remove exclusion for battler side opponent to use for both sides

            gBattleSpritesDataPtr->battlerData[i].hpNumbersNoBars ^= 1;
            noBars = gBattleSpritesDataPtr->battlerData[i].hpNumbersNoBars;
            if (GetBattlerSide(i) == B_SIDE_PLAYER)
            {
                if (!IsDoubleBattle())
                    continue;
                if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
                    continue;

                if (noBars == TRUE) // bars to text
                {
                    healthBarSpriteId = gSprites[gHealthboxSpriteIds[i]].hMain_HealthBarSpriteId;

                    CpuFill32(0, (void*)(OBJ_VRAM0 + gSprites[healthBarSpriteId].oam.tileNum * TILE_SIZE_4BPP), 0x100);
                    UpdateHpTextInHealthboxInDoubles(gHealthboxSpriteIds[i], GetMonData(&gPlayerParty[gBattlerPartyIndexes[i]], MON_DATA_HP), HP_CURRENT);
                    UpdateHpTextInHealthboxInDoubles(gHealthboxSpriteIds[i], GetMonData(&gPlayerParty[gBattlerPartyIndexes[i]], MON_DATA_MAX_HP), HP_MAX);
                }
                else // text to bars
                {
                    UpdateStatusIconInHealthbox(gHealthboxSpriteIds[i]);
                    UpdateHealthboxAttribute(gHealthboxSpriteIds[i], &gPlayerParty[gBattlerPartyIndexes[i]], HEALTHBOX_HEALTH_BAR);
                    CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_117), (void*)(OBJ_VRAM0 + 0x680 + gSprites[gHealthboxSpriteIds[i]].oam.tileNum * TILE_SIZE_4BPP), 32);
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_SAFARI) //skip debug stuff
                    continue;

                if (noBars == TRUE) // bars to text
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
                    {
                        // Most likely a debug function.
                        PrintSafariMonInfo(gHealthboxSpriteIds[i], &gEnemyParty[gBattlerPartyIndexes[i]]);
                    }
                    else
                    {
                        healthBarSpriteId = gSprites[gHealthboxSpriteIds[i]].hMain_HealthBarSpriteId;

                        CpuFill32(0, (void *)(OBJ_VRAM0 + gSprites[healthBarSpriteId].oam.tileNum * TILE_SIZE_4BPP), 0x100);
                        UpdateHpTextInHealthboxInDoubles(gHealthboxSpriteIds[i], GetMonData(&gEnemyParty[gBattlerPartyIndexes[i]], MON_DATA_HP), HP_CURRENT);
                        UpdateHpTextInHealthboxInDoubles(gHealthboxSpriteIds[i], GetMonData(&gEnemyParty[gBattlerPartyIndexes[i]], MON_DATA_MAX_HP), HP_MAX);
                    }
                }
                else // text to bars
                {
                    UpdateStatusIconInHealthbox(gHealthboxSpriteIds[i]);
                    UpdateHealthboxAttribute(gHealthboxSpriteIds[i], &gEnemyParty[gBattlerPartyIndexes[i]], HEALTHBOX_HEALTH_BAR);
                    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
                        UpdateHealthboxAttribute(gHealthboxSpriteIds[i], &gEnemyParty[gBattlerPartyIndexes[i]], HEALTHBOX_NICK);
                }
            }
            gSprites[gHealthboxSpriteIds[i]].hMain_Data7 ^= 1;
        }
    }
}

#define tBattler                data[0]
#define tSummaryBarSpriteId     data[1]
#define tBallIconSpriteId(n)    data[3 + n]
#define tIsBattleStart          data[10]
#define tData15                 data[15]

u8 CreatePartyStatusSummarySprites(u8 battlerId, struct HpAndStatus *partyInfo, bool8 isSwitchingMons, bool8 isBattleStart)
{
    bool8 isOpponent;
    s8 nValidMons;
    s16 bar_X, bar_Y, bar_pos2_X, bar_data0;
    s32 i;
    u8 summaryBarSpriteId;
    u8 ballIconSpritesIds[PARTY_SIZE];
    u8 taskId;

    if (!isSwitchingMons || GetBattlerPosition(battlerId) != B_POSITION_OPPONENT_RIGHT)
    {
        if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        {
            isOpponent = FALSE;
            bar_X = 136, bar_Y = 96;
            bar_pos2_X = 100;
            bar_data0 = -5;
        }
        else
        {
            isOpponent = TRUE;

            if (!isSwitchingMons || !IsDoubleBattle())
                bar_X = 104, bar_Y = 40;
            else
                bar_X = 104, bar_Y = 16;

            bar_pos2_X = -100;
            bar_data0 = 5;
        }
    }
    else
    {
        isOpponent = TRUE;
        bar_X = 104, bar_Y = 40;
        bar_pos2_X = -100;
        bar_data0 = 5;
    }

    for (i = 0, nValidMons = 0; i < PARTY_SIZE; i++)
    {
        if (partyInfo[i].hp != 0xFFFF)
            nValidMons++;
    }

    LoadCompressedSpriteSheetUsingHeap(&sStatusSummaryBarSpriteSheets[isOpponent]);
    LoadSpriteSheet(&sStatusSummaryBallsSpriteSheets[isOpponent]);
    LoadSpritePalette(&sStatusSummaryBarSpritePals[isOpponent]);
    LoadSpritePalette(&sStatusSummaryBallsSpritePals[isOpponent]);

    summaryBarSpriteId = CreateSprite(&sStatusSummaryBarSpriteTemplates[isOpponent], bar_X, bar_Y, 10);
    SetSubspriteTables(&gSprites[summaryBarSpriteId], sStatusSummaryBar_SubspriteTable);
    gSprites[summaryBarSpriteId].pos2.x = bar_pos2_X;
    gSprites[summaryBarSpriteId].data[0] = bar_data0;

    if (isOpponent)
    {
        gSprites[summaryBarSpriteId].pos1.x -= 96;
        gSprites[summaryBarSpriteId].oam.matrixNum = ST_OAM_HFLIP;
    }
    else
    {
        gSprites[summaryBarSpriteId].pos1.x += 96;
    }

    for (i = 0; i < PARTY_SIZE; i++)
    {
        ballIconSpritesIds[i] = CreateSpriteAtEnd(&sStatusSummaryBallsSpriteTemplates[isOpponent], bar_X, bar_Y - 4, 9);

        if (!isBattleStart)
            gSprites[ballIconSpritesIds[i]].callback = SpriteCB_StatusSummaryBallsOnSwitchout;

        if (!isOpponent)
        {
            gSprites[ballIconSpritesIds[i]].pos2.x = 0;
            gSprites[ballIconSpritesIds[i]].pos2.y = 0;
        }

        gSprites[ballIconSpritesIds[i]].data[0] = summaryBarSpriteId;

        if (!isOpponent)
        {
            gSprites[ballIconSpritesIds[i]].pos1.x += 10 * i + 24;
            gSprites[ballIconSpritesIds[i]].data[1] = i * 7 + 10;
            gSprites[ballIconSpritesIds[i]].pos2.x = 120;
        }
        else
        {
            gSprites[ballIconSpritesIds[i]].pos1.x -= 10 * (5 - i) + 24;
            gSprites[ballIconSpritesIds[i]].data[1] = (6 - i) * 7 + 10;
            gSprites[ballIconSpritesIds[i]].pos2.x = -120;
        }

        gSprites[ballIconSpritesIds[i]].data[2] = isOpponent;
    }

    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                if (partyInfo[i].hp == 0xFFFF) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[i]].data[7] = 1;
                }
                else if (partyInfo[i].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 3;
                }
                else if (partyInfo[i].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 2;
                }
            }
            else
            {
                if (i >= nValidMons) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[i]].data[7] = 1;
                }
                else if (partyInfo[i].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 3;
                }
                else if (partyInfo[i].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[i]].oam.tileNum += 2;
                }
            }
        }
    }
    else
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                if (partyInfo[i].hp == 0xFFFF) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[5 - i]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[5 - i]].data[7] = 1;
                }
                else if (partyInfo[i].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[5 - i]].oam.tileNum += 3;
                }
                else if (partyInfo[i].status != 0) // mon with major status
                {
                    gSprites[ballIconSpritesIds[5 - i]].oam.tileNum += 2;
                }
            }
            else
            {
                ballIconSpritesIds[5 - i] += 0;
                if (i >= nValidMons) // empty slot or an egg
                {
                    gSprites[ballIconSpritesIds[5 - i]].oam.tileNum += 1;
                    gSprites[ballIconSpritesIds[5 - i]].data[7] = 1;
                }
                else if (partyInfo[i].hp == 0) // fainted mon
                {
                    gSprites[ballIconSpritesIds[5 - i]].oam.tileNum += 3;
                }
                else if (partyInfo[i].status != 0) // mon with major status
                {
                    do
                    {
                        gSprites[ballIconSpritesIds[5 - i]].oam.tileNum += 2;
                    } while (0);
                }
            }
            ballIconSpritesIds[5 - ++i] += 0; i--;
        }
    }

    taskId = CreateTask(TaskDummy, 5);
    gTasks[taskId].tBattler = battlerId;
    gTasks[taskId].tSummaryBarSpriteId = summaryBarSpriteId;

    for (i = 0; i < PARTY_SIZE; i++)
        gTasks[taskId].tBallIconSpriteId(i) = ballIconSpritesIds[i];

    gTasks[taskId].tIsBattleStart = isBattleStart;
    PlaySE12WithPanning(SE_BALL_TRAY_ENTER, 0);
    return taskId;
}

void Task_HidePartyStatusSummary(u8 taskId)
{
    u8 ballIconSpriteIds[PARTY_SIZE];
    bool8 isBattleStart;
    u8 summaryBarSpriteId;
    u8 battlerId;
    s32 i;

    isBattleStart = gTasks[taskId].tIsBattleStart;
    summaryBarSpriteId = gTasks[taskId].tSummaryBarSpriteId;
    battlerId = gTasks[taskId].tBattler;

    for (i = 0; i < PARTY_SIZE; i++)
        ballIconSpriteIds[i] = gTasks[taskId].tBallIconSpriteId(i);

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));

    gTasks[taskId].tData15 = 16;

    for (i = 0; i < PARTY_SIZE; i++)
        gSprites[ballIconSpriteIds[i]].oam.objMode = ST_OAM_OBJ_BLEND;

    gSprites[summaryBarSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;

    if (isBattleStart)
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetBattlerSide(battlerId) != B_SIDE_PLAYER)
            {
                gSprites[ballIconSpriteIds[5 - i]].data[1] = 7 * i;
                gSprites[ballIconSpriteIds[5 - i]].data[3] = 0;
                gSprites[ballIconSpriteIds[5 - i]].data[4] = 0;
                gSprites[ballIconSpriteIds[5 - i]].callback = sub_8049630;
            }
            else
            {
                gSprites[ballIconSpriteIds[i]].data[1] = 7 * i;
                gSprites[ballIconSpriteIds[i]].data[3] = 0;
                gSprites[ballIconSpriteIds[i]].data[4] = 0;
                gSprites[ballIconSpriteIds[i]].callback = sub_8049630;
            }
        }
        gSprites[summaryBarSpriteId].data[0] /= 2;
        gSprites[summaryBarSpriteId].data[1] = 0;
        gSprites[summaryBarSpriteId].callback = sub_8049568;
        SetSubspriteTables(&gSprites[summaryBarSpriteId], gUnknown_8260404);
        gTasks[taskId].func = sub_8049388;
    }
    else
    {
        gTasks[taskId].func = sub_804948C;
    }
}

static void sub_8049388(u8 taskId)
{
    if ((gTasks[taskId].data[11]++ % 2) == 0)
    {
        if (--gTasks[taskId].tData15 < 0)
            return;

        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[15], 16 - gTasks[taskId].data[15]));
    }
    if (gTasks[taskId].tData15 == 0)
        gTasks[taskId].func = sub_80493E4;
}

static void sub_80493E4(u8 taskId)
{
    u8 ballIconSpriteIds[PARTY_SIZE];
    s32 i;

    u8 battlerId = gTasks[taskId].tBattler;
    if (--gTasks[taskId].tData15 == -1)
    {
        u8 summaryBarSpriteId = gTasks[taskId].tSummaryBarSpriteId;

        for (i = 0; i < PARTY_SIZE; i++)
            ballIconSpriteIds[i] = gTasks[taskId].tBallIconSpriteId(i);

        DestroySpriteAndFreeResources(&gSprites[summaryBarSpriteId]);
        DestroySpriteAndFreeResources(&gSprites[ballIconSpriteIds[0]]);

        for (i = 1; i < PARTY_SIZE; i++)
            DestroySprite(&gSprites[ballIconSpriteIds[i]]);
    }
    else if (gTasks[taskId].tData15 == -3)
    {
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyTask(taskId);
    }
}

static void sub_804948C(u8 taskId)
{
    u8 ballIconSpriteIds[PARTY_SIZE];
    s32 i;
    u8 battlerId = gTasks[taskId].tBattler;

    if (--gTasks[taskId].tData15 >= 0)
    {
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[15], 16 - gTasks[taskId].data[15]));
    }
    else if (gTasks[taskId].tData15 == -1)
    {
        u8 summaryBarSpriteId = gTasks[taskId].tSummaryBarSpriteId;

        for (i = 0; i < PARTY_SIZE; i++)
            ballIconSpriteIds[i] = gTasks[taskId].tBallIconSpriteId(i);

        DestroySpriteAndFreeResources(&gSprites[summaryBarSpriteId]);
        DestroySpriteAndFreeResources(&gSprites[ballIconSpriteIds[0]]);

        for (i = 1; i < PARTY_SIZE; i++)
            DestroySprite(&gSprites[ballIconSpriteIds[i]]);
    }
    else if (gTasks[taskId].tData15 == -3)
    {
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyTask(taskId);
    }
}

#undef tBattler
#undef tSummaryBarSpriteId
#undef tBallIconSpriteId
#undef tIsBattleStart
#undef tData15

static void SpriteCB_StatusSummaryBar(struct Sprite *sprite)
{
    if (sprite->pos2.x != 0)
        sprite->pos2.x += sprite->data[0];
}

static void sub_8049568(struct Sprite *sprite)
{
    sprite->data[1] += 32;
    if (sprite->data[0] > 0)
        sprite->pos2.x += sprite->data[1] >> 4;
    else
        sprite->pos2.x -= sprite->data[1] >> 4;
    sprite->data[1] &= 0xF;
}

static void SpriteCB_StatusSummaryBallsOnBattleStart(struct Sprite *sprite)
{
    u8 var1;
    u16 var2;
    s8 pan;

    if (sprite->data[1] > 0)
    {
        sprite->data[1]--;
        return;
    }

    var1 = sprite->data[2];
    var2 = sprite->data[3];
    var2 += 56;
    sprite->data[3] = var2 & 0xFFF0;

    if (var1 != 0)
    {
        sprite->pos2.x += var2 >> 4;
        if (sprite->pos2.x > 0)
            sprite->pos2.x = 0;
    }
    else
    {
        sprite->pos2.x -= var2 >> 4;
        if (sprite->pos2.x < 0)
            sprite->pos2.x = 0;
    }

    if (sprite->pos2.x == 0)
    {
        pan = SOUND_PAN_TARGET;
        if (var1 != 0)
            pan = SOUND_PAN_ATTACKER;

        if (sprite->data[7] != 0)
            PlaySE2WithPanning(SE_BALL_TRAY_EXIT, pan);
        else
            PlaySE1WithPanning(SE_BALL_TRAY_BALL, pan);

        sprite->callback = SpriteCallbackDummy;
    }
}

static void sub_8049630(struct Sprite *sprite)
{
    u8 var1;
    u16 var2;

    if (sprite->data[1] > 0)
    {
        sprite->data[1]--;
        return;
    }
    var1 = sprite->data[2];
    var2 = sprite->data[3];
    var2 += 56;
    sprite->data[3] = var2 & 0xFFF0;
    if (var1 != 0)
        sprite->pos2.x += var2 >> 4;
    else
        sprite->pos2.x -= var2 >> 4;
    if (sprite->pos2.x + sprite->pos1.x > 248
        || sprite->pos2.x + sprite->pos1.x < -8)
    {
        sprite->invisible = TRUE;
        sprite->callback = SpriteCallbackDummy;
    }
}

static void SpriteCB_StatusSummaryBallsOnSwitchout(struct Sprite *sprite)
{
    u8 barSpriteId = sprite->data[0];

    sprite->pos2.x = gSprites[barSpriteId].pos2.x;
    sprite->pos2.y = gSprites[barSpriteId].pos2.y;
}

static const u8 gUnknown_8260556[] = _("{HIGHLIGHT 02}");

void UpdateNickInHealthbox(u8 healthboxSpriteId, struct Pokemon *mon)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 *ptr;
    u32 windowId, spriteTileNum;
    u8 *windowTileData;
    u16 species;
    u8 gender;

    ptr = StringCopy(gDisplayedStringBattle, gUnknown_8260556);
    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    gender = GetMonGender(mon);
    species = GetMonData(mon, MON_DATA_SPECIES);

    if (StringCompare(gBaseStats[species].speciesName, nickname) == IDENTICAL) //if not nicknamed reassign tempStr to speciesname, making it update capitalization
        GetSpeciesName(nickname, species); //seems need this?

    StringGet_Nickname(nickname);
    ptr = StringCopy(ptr, nickname);
    *ptr++ = EXT_CTRL_CODE_BEGIN;
    *ptr++ = EXT_CTRL_CODE_COLOR;

    

    if ((species == SPECIES_NIDORAN_F || species == SPECIES_NIDORAN_M) && StringCompare(nickname, gBaseStats[species].speciesName) == IDENTICAL)
        gender = 100;

    if (CheckBattleTypeGhost(mon, gSprites[healthboxSpriteId].hMain_Battler))
        gender = 100;

    // AddTextPrinterAndCreateWindowOnHealthbox's arguments are the same in all 3 cases.
    // It's possible they may have been different in early development phases.
    switch (gender)
    {
    default:
        *ptr++ = TEXT_DYNAMIC_COLOR_2;
        *ptr++ = EOS;
        windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(gDisplayedStringBattle, 0, 3, &windowId);
        break;
    case MON_MALE:
        *ptr++ = TEXT_DYNAMIC_COLOR_2;
        *ptr++ = CHAR_MALE;
        *ptr++ = EOS;
        windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(gDisplayedStringBattle, 0, 3, &windowId);
        break;
    case MON_FEMALE:
        *ptr++ = TEXT_DYNAMIC_COLOR_1;
        *ptr++ = CHAR_FEMALE;
        *ptr++ = EOS;
        windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(gDisplayedStringBattle, 0, 3, &windowId);
        break;
    }

    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;

    //ok player uses 2 different healthbox sizes for single & double battles
    //enemy uses the same healthbox for both, they use the small one that player uses for doubles
    //based on function is 32 * tile size 4bpp
    if (GetBattlerSide(gSprites[healthboxSpriteId].sBattlerId) == B_SIDE_PLAYER)
    {
        TextIntoHealthboxObject((void *)(OBJ_VRAM0 + 2 * TILE_SIZE_4BPP + spriteTileNum), windowTileData, 6);//which is last value here
        ptr = (void *)(OBJ_VRAM0);
        if (!IsDoubleBattle())
            ptr += spriteTileNum + 64 * TILE_SIZE_4BPP; //is 64 because first function uses 2 x TILE_SIZE_4BPP which is 64, this because player has doubl size healthbox
        else
            ptr += spriteTileNum + 32 * TILE_SIZE_4BPP;


        if ((StringLength(nickname)) > 11)
        {
            TextIntoHealthboxObject(ptr, windowTileData + 6 * TILE_SIZE_4BPP, 2); //changed from 1 to 2 seemed to fix. for expanded spec names
        }
        if ((StringLength(nickname)) < 11)
            TextIntoHealthboxObject(ptr, windowTileData + 6 * TILE_SIZE_4BPP, 1);
    }//value added to windowTileData uses 6 because 1st function ended in window width 6
    //end width 1 is default, 2 works   //fix so health box updates with name length
    else
    {
        TextIntoHealthboxObject((void *)(OBJ_VRAM0 + TILE_SIZE_4BPP + spriteTileNum), windowTileData, 7);// & here  original line
        ptr = (void *)(OBJ_VRAM0);
        
        ptr += spriteTileNum + 32 * TILE_SIZE_4BPP; //if right and this is for change in size of healthbox for doubles, then enemy side doesn't need it

        if ((StringLength(nickname)) > 11)  //value 11 here is for original species name length limit
        {
            TextIntoHealthboxObject(ptr, windowTileData + 7 * TILE_SIZE_4BPP, 1);
        }
        if ((StringLength(nickname)) < 11) //think using nickname alone will work, as if you dont nickname belive it defaults to same as species name
            TextIntoHealthboxObject(ptr, windowTileData + 7 * TILE_SIZE_4BPP, 0); //7 sems right    
    }//since using 7 rathre than end width 1, need base to be 0, and when having longer name use window width 1, that way it is equal to if I use width 2, on 6 for playre side

    RemoveWindowOnHealthbox(windowId);
}

void TryAddPokeballIconToHealthbox(u8 healthboxSpriteId, bool8 noStatus)
{
    u8 battlerId, healthBarSpriteId;

    if (gBattleTypeFlags & (BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_OLD_MAN_TUTORIAL | BATTLE_TYPE_POKEDUDE))
        return;

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        return;

    battlerId = gSprites[healthboxSpriteId].hMain_Battler;
    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        return;
    if (CheckBattleTypeGhost(&gEnemyParty[gBattlerPartyIndexes[battlerId]], battlerId))
        return;
    if (!GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerId]], MON_DATA_SPECIES)), FLAG_GET_CAUGHT))
        return;

    healthBarSpriteId = gSprites[healthboxSpriteId].hMain_HealthBarSpriteId;

    if (noStatus)
        CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_70), (void*)(OBJ_VRAM0 + (gSprites[healthBarSpriteId].oam.tileNum + 8) * TILE_SIZE_4BPP), 32);
    else
    CpuFill32(0, (void*)(OBJ_VRAM0 + (gSprites[healthBarSpriteId].oam.tileNum + 8) * TILE_SIZE_4BPP), 32);
}

enum
{
    PAL_STATUS_PSN,
    PAL_STATUS_PAR,
    PAL_STATUS_SLP,
    PAL_STATUS_FRZ,
    PAL_STATUS_BRN,
    PAL_STATUS_INF  //not working in battle yet
    //PAL_STATUS_SPRT
};

//rgb uses 32 max range so divide colors 255 range by 8 to get value
static const u16 sStatusIconColors[] = {
    [PAL_STATUS_PSN] = RGB(24, 12, 24),
    [PAL_STATUS_PAR] = RGB(23, 23, 3),
    [PAL_STATUS_SLP] = RGB(20, 20, 17),
    [PAL_STATUS_FRZ] = RGB(17, 22, 28),
    [PAL_STATUS_BRN] = RGB(28, 14, 10),
    [PAL_STATUS_INF] = RGB(23, 23, 3),
    //[PAL_STATUS_SPRT] = RGB(6, 26, 24)
};

static void UpdateStatusIconInHealthbox(u8 healthboxSpriteId)
{
    s32 i;
    u8 battlerId, healthBarSpriteId;
    u32 status, pltAdder;
    const u8 *statusGfxPtr;
    s16 tileNumAdder;
    u8 statusPalId;

    battlerId = gSprites[healthboxSpriteId].hMain_Battler;
    healthBarSpriteId = gSprites[healthboxSpriteId].hMain_HealthBarSpriteId;
    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
    {
        status = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_STATUS);
        if (!IsDoubleBattle())
            tileNumAdder = 0x1A;
        else
            tileNumAdder = 0x12;
    }
    else
    {
        status = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerId]], MON_DATA_STATUS);
        tileNumAdder = 0x11;
    }

    if (status & STATUS1_SLEEP)
    {
        statusGfxPtr = GetHealthboxElementGfxPtr(GetStatusIconForBattlerId(HEALTHBOX_GFX_STATUS_SLP_BATTLER0, battlerId));
        statusPalId = PAL_STATUS_SLP;
    }
    else if (status & STATUS1_PSN_ANY)
    {
        statusGfxPtr = GetHealthboxElementGfxPtr(GetStatusIconForBattlerId(HEALTHBOX_GFX_STATUS_PSN_BATTLER0, battlerId));
        statusPalId = PAL_STATUS_PSN;
    }
    else if (status & STATUS1_BURN)
    {
        statusGfxPtr = GetHealthboxElementGfxPtr(GetStatusIconForBattlerId(HEALTHBOX_GFX_STATUS_BRN_BATTLER0, battlerId));
        statusPalId = PAL_STATUS_BRN;
    }
    else if (status & STATUS1_FREEZE)
    {
        statusGfxPtr = GetHealthboxElementGfxPtr(GetStatusIconForBattlerId(HEALTHBOX_GFX_STATUS_FRZ_BATTLER0, battlerId));
        statusPalId = PAL_STATUS_FRZ;
    }
    else if (status & STATUS1_PARALYSIS)
    {
        statusGfxPtr = GetHealthboxElementGfxPtr(GetStatusIconForBattlerId(HEALTHBOX_GFX_STATUS_PRZ_BATTLER0, battlerId));
        statusPalId = PAL_STATUS_PAR;
    }
    else
    {
        statusGfxPtr = GetHealthboxElementGfxPtr(HEALTHBOX_GFX_39);

        for (i = 0; i < 3; i++)
            CpuCopy32(statusGfxPtr, (void*)(OBJ_VRAM0 + (gSprites[healthboxSpriteId].oam.tileNum + tileNumAdder + i) * TILE_SIZE_4BPP), 32);

        if (!gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars)
            CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_1), (void *)(OBJ_VRAM0 + gSprites[healthBarSpriteId].oam.tileNum * TILE_SIZE_4BPP), 64);

        TryAddPokeballIconToHealthbox(healthboxSpriteId, TRUE);
        return;
    }

    pltAdder = gSprites[healthboxSpriteId].oam.paletteNum * 16;
    pltAdder += battlerId + 12;

    FillPalette(sStatusIconColors[statusPalId], pltAdder + 0x100, 2);
    CpuCopy16(gPlttBufferUnfaded + 0x100 + pltAdder, (void*)(OBJ_PLTT + pltAdder * 2), 2);
    CpuCopy32(statusGfxPtr, (void*)(OBJ_VRAM0 + (gSprites[healthboxSpriteId].oam.tileNum + tileNumAdder) * TILE_SIZE_4BPP), 96);
    if (IsDoubleBattle() == TRUE || GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
    {
        if (!gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars)
        {
            CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_0), (void*)(OBJ_VRAM0 + gSprites[healthBarSpriteId].oam.tileNum * TILE_SIZE_4BPP), 32);
            CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_65), (void*)(OBJ_VRAM0 + (gSprites[healthBarSpriteId].oam.tileNum + 1) * TILE_SIZE_4BPP), 32);
        }
    }
    TryAddPokeballIconToHealthbox(healthboxSpriteId, FALSE);
}

//no idea how this works,
//and why it doesn't just blit the icon
//from the tilemap onto the health box
//oh right becuuse its dumb and health box is 
//split up on many different parts without a clear order...
static u8 GetStatusIconForBattlerId(u8 statusElementId, u8 battlerId)
{
    u8 ret = statusElementId;

    switch (statusElementId)
    {
    case HEALTHBOX_GFX_STATUS_PSN_BATTLER0:
        if (battlerId == 0)
            ret = HEALTHBOX_GFX_STATUS_PSN_BATTLER0;
        else if (battlerId == 1)
            ret = HEALTHBOX_GFX_STATUS_PSN_BATTLER1;
        else if (battlerId == 2)
            ret = HEALTHBOX_GFX_STATUS_PSN_BATTLER2;
        else
            ret = HEALTHBOX_GFX_STATUS_PSN_BATTLER3;
        break;
    case HEALTHBOX_GFX_STATUS_PRZ_BATTLER0:
        if (battlerId == 0)
            ret = HEALTHBOX_GFX_STATUS_PRZ_BATTLER0;
        else if (battlerId == 1)
            ret = HEALTHBOX_GFX_STATUS_PRZ_BATTLER1;
        else if (battlerId == 2)
            ret = HEALTHBOX_GFX_STATUS_PRZ_BATTLER2;
        else
            ret = HEALTHBOX_GFX_STATUS_PRZ_BATTLER3;
        break;
    case HEALTHBOX_GFX_STATUS_SLP_BATTLER0:
        if (battlerId == 0)
            ret = HEALTHBOX_GFX_STATUS_SLP_BATTLER0;
        else if (battlerId == 1)
            ret = HEALTHBOX_GFX_STATUS_SLP_BATTLER1;
        else if (battlerId == 2)
            ret = HEALTHBOX_GFX_STATUS_SLP_BATTLER2;
        else
            ret = HEALTHBOX_GFX_STATUS_SLP_BATTLER3;
        break;
    case HEALTHBOX_GFX_STATUS_FRZ_BATTLER0:
        if (battlerId == 0)
            ret = HEALTHBOX_GFX_STATUS_FRZ_BATTLER0;
        else if (battlerId == 1)
            ret = HEALTHBOX_GFX_STATUS_FRZ_BATTLER1;
        else if (battlerId == 2)
            ret = HEALTHBOX_GFX_STATUS_FRZ_BATTLER2;
        else
            ret = HEALTHBOX_GFX_STATUS_FRZ_BATTLER3;
        break;
    case HEALTHBOX_GFX_STATUS_BRN_BATTLER0:
        if (battlerId == 0)
            ret = HEALTHBOX_GFX_STATUS_BRN_BATTLER0;
        else if (battlerId == 1)
            ret = HEALTHBOX_GFX_STATUS_BRN_BATTLER1;
        else if (battlerId == 2)
            ret = HEALTHBOX_GFX_STATUS_BRN_BATTLER2;
        else
            ret = HEALTHBOX_GFX_STATUS_BRN_BATTLER3;
        break;
    /*case HEALTHBOX_GFX_STATUS_SPRT_BATTLER0
        if (battlerId == 0)
            ret = HEALTHBOX_GFX_STATUS_SPRT_BATTLER0;
        else if (battlerId == 1)
            ret = HEALTHBOX_GFX_STATUS_SPRT_BATTLER1;
        else if (battlerId == 2)
            ret = HEALTHBOX_GFX_STATUS_SPRT_BATTLER2;
        else
            ret = HEALTHBOX_GFX_STATUS_SPRT_BATTLER3;
        break;*/
    }
    return ret;
}

static void UpdateSafariBallsTextOnHealthbox(u8 healthboxSpriteId)
{
    u32 windowId, spriteTileNum;
    u8 *windowTileData;

    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(gText_SafariBalls, 0, 3, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;
    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x40) + spriteTileNum, windowTileData, 6);
    TextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x800) + spriteTileNum, windowTileData + 0xC0, 2);
    RemoveWindowOnHealthbox(windowId);
}

static void UpdateLeftNoOfBallsTextOnHealthbox(u8 healthboxSpriteId)
{
    u8 text[16];
    u8 *txtPtr;
    u32 windowId, spriteTileNum;
    u8 *windowTileData;

    txtPtr = StringCopy(text, gText_HighlightRed_Left);
    ConvertIntToDecimalStringN(txtPtr, gNumSafariBalls, STR_CONV_MODE_LEFT_ALIGN, 2);

    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, GetStringRightAlignXOffset(0, text, 0x2F), 3, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * TILE_SIZE_4BPP;
    SafariTextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0x2C0) + spriteTileNum, windowTileData, 2);
    SafariTextIntoHealthboxObject((void*)(OBJ_VRAM0 + 0xA00) + spriteTileNum, windowTileData + 0x40, 4);
    RemoveWindowOnHealthbox(windowId);
}

#define HEALTHBOX_LOGIC
void UpdateHealthboxAttribute(u8 healthboxSpriteId, struct Pokemon *mon, u8 elementId)
{
    s32 maxHp, currHp;
    u8 battlerId = gSprites[healthboxSpriteId].hMain_Battler;
    u32 btlrcurrhp = gBattleMons[battlerId].hp;
    u32 btlrMaxhp = gBattleMons[battlerId].maxHP; 

    if (elementId == HEALTHBOX_ALL && !IsDoubleBattle())
        GetBattlerSide(battlerId); // Pointless function call.

    if (GetBattlerSide(gSprites[healthboxSpriteId].hMain_Battler) == B_SIDE_PLAYER)
    {
        u8 isDoubles;
        
        if (elementId == HEALTHBOX_LEVEL || elementId == HEALTHBOX_ALL)
            UpdateLvlInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_LEVEL));
        
        if (gBattleMons[battlerId].status2 & STATUS2_TRANSFORMED)
        {
            if (elementId == HEALTHBOX_CURRENT_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, btlrcurrhp, HP_CURRENT);
            if (elementId == HEALTHBOX_MAX_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, btlrMaxhp, HP_MAX);

            if (elementId == HEALTHBOX_HEALTH_BAR || elementId == HEALTHBOX_ALL)
            {
                LoadBattleBarGfx(0);
                maxHp = btlrMaxhp;
                currHp = btlrcurrhp;
                SetBattleBarStruct(battlerId, healthboxSpriteId, maxHp, currHp, 0);
                MoveBattleBar(battlerId, healthboxSpriteId, HEALTH_BAR, 0);
            }
        }
        else
        {
            if (elementId == HEALTHBOX_CURRENT_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_HP), HP_CURRENT);
            if (elementId == HEALTHBOX_MAX_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_MAX_HP), HP_MAX);

            if (elementId == HEALTHBOX_HEALTH_BAR || elementId == HEALTHBOX_ALL)
            {
                LoadBattleBarGfx(0);
                maxHp = GetMonData(mon, MON_DATA_MAX_HP);
                currHp = GetMonData(mon, MON_DATA_HP);
                SetBattleBarStruct(battlerId, healthboxSpriteId, maxHp, currHp, 0);
                MoveBattleBar(battlerId, healthboxSpriteId, HEALTH_BAR, 0);
            }
        }
        
        
        
        isDoubles = IsDoubleBattle();
        if (!isDoubles && (elementId == HEALTHBOX_EXP_BAR || elementId == HEALTHBOX_ALL))
        {
            u16 species;
            u32 exp, currLevelExp;
            s32 currExpBarValue, maxExpBarValue;
            u8 level;

            LoadBattleBarGfx(3);
            species = GetMonData(mon, MON_DATA_SPECIES);
            level = GetMonData(mon, MON_DATA_LEVEL);
            exp = GetMonData(mon, MON_DATA_EXP);
            currLevelExp = gExperienceTables[gBaseStats[species].growthRate][level];
            currExpBarValue = exp - currLevelExp;
            maxExpBarValue = gExperienceTables[gBaseStats[species].growthRate][level + 1] - currLevelExp;
            SetBattleBarStruct(battlerId, healthboxSpriteId, maxExpBarValue, currExpBarValue, isDoubles);
            MoveBattleBar(battlerId, healthboxSpriteId, EXP_BAR, 0);
        }
        if (elementId == HEALTHBOX_NICK || elementId == HEALTHBOX_ALL)
            UpdateNickInHealthbox(healthboxSpriteId, mon);
        if (elementId == HEALTHBOX_STATUS_ICON || elementId == HEALTHBOX_ALL)
            UpdateStatusIconInHealthbox(healthboxSpriteId);
        if (elementId == HEALTHBOX_SAFARI_ALL_TEXT)
            UpdateSafariBallsTextOnHealthbox(healthboxSpriteId);
        if (elementId == HEALTHBOX_SAFARI_ALL_TEXT || elementId == HEALTHBOX_SAFARI_BALLS_TEXT)
            UpdateLeftNoOfBallsTextOnHealthbox(healthboxSpriteId);
    }
    else
    {
        if (elementId == HEALTHBOX_LEVEL || elementId == HEALTHBOX_ALL)
            UpdateLvlInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_LEVEL));

        //made changes and added values for hptext as seemed enemy side never had it,
        //could be reason why my attempted change for displaying hp num on enemy side never worked
        //vsonic
        if (gBattleMons[battlerId].status2 & STATUS2_TRANSFORMED)
        {
            if (elementId == HEALTHBOX_CURRENT_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, btlrcurrhp, HP_CURRENT);
            if (elementId == HEALTHBOX_MAX_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, btlrMaxhp, HP_MAX);

            if (elementId == HEALTHBOX_HEALTH_BAR || elementId == HEALTHBOX_ALL)
            {
                LoadBattleBarGfx(0);
                maxHp = btlrMaxhp;
                currHp = btlrcurrhp;
                SetBattleBarStruct(battlerId, healthboxSpriteId, maxHp, currHp, 0);
                MoveBattleBar(battlerId, healthboxSpriteId, HEALTH_BAR, 0);
            }
        }
        else
        {
            if (elementId == HEALTHBOX_CURRENT_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_HP), HP_CURRENT);
            if (elementId == HEALTHBOX_MAX_HP || elementId == HEALTHBOX_ALL)
                UpdateHpTextInHealthbox(healthboxSpriteId, GetMonData(mon, MON_DATA_MAX_HP), HP_MAX);

            if (elementId == HEALTHBOX_HEALTH_BAR || elementId == HEALTHBOX_ALL)
            {
                LoadBattleBarGfx(0);
                maxHp = GetMonData(mon, MON_DATA_MAX_HP);
                currHp = GetMonData(mon, MON_DATA_HP);
                SetBattleBarStruct(battlerId, healthboxSpriteId, maxHp, currHp, 0);
                MoveBattleBar(battlerId, healthboxSpriteId, HEALTH_BAR, 0);
            }
        }


        if (elementId == HEALTHBOX_NICK || elementId == HEALTHBOX_ALL)
            UpdateNickInHealthbox(healthboxSpriteId, mon);
        if (elementId == HEALTHBOX_STATUS_ICON || elementId == HEALTHBOX_ALL)
            UpdateStatusIconInHealthbox(healthboxSpriteId);
    }
}

#define B_EXPBAR_PIXELS 64
#define B_HEALTHBAR_PIXELS 48

s32 MoveBattleBar(u8 battlerId, u8 healthboxSpriteId, u8 whichBar, u8 unused)
{
    s32 currentBarValue;

    if (whichBar == HEALTH_BAR) // health bar
    {
        currentBarValue = CalcNewBarValue(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                                          gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                                          gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                                          &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                                          B_HEALTHBAR_PIXELS / 8, 1);
    }
    else // exp bar
    {
        u16 expFraction = GetScaledExpFraction(gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                                               gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                                               gBattleSpritesDataPtr->battleBars[battlerId].maxValue, 8);
        if (expFraction == 0)
            expFraction = 1;
        expFraction = abs(gBattleSpritesDataPtr->battleBars[battlerId].receivedValue / expFraction);

        currentBarValue = CalcNewBarValue(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                                          gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                                          gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                                          &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                                          B_EXPBAR_PIXELS / 8, expFraction);
    }

    if (whichBar == EXP_BAR || (whichBar == HEALTH_BAR && !gBattleSpritesDataPtr->battlerData[battlerId].hpNumbersNoBars))
        MoveBattleBarGraphically(battlerId, whichBar);

    if (currentBarValue == -1)
        gBattleSpritesDataPtr->battleBars[battlerId].currValue = 0;

    return currentBarValue;
}

static void MoveBattleBarGraphically(u8 battlerId, u8 whichBar)
{
    u8 array[8];
    u8 filledPixelsCount, level;
    u8 barElementId;
    u8 i;

    switch (whichBar)
    {
    case HEALTH_BAR:
        filledPixelsCount = CalcBarFilledPixels(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                                                gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                                                gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                                                &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                                                array, B_HEALTHBAR_PIXELS / 8);

        if (filledPixelsCount > (B_HEALTHBAR_PIXELS * 50 / 100)) // more than 50 % hp
            barElementId = HEALTHBOX_GFX_HP_BAR_GREEN;
        else if (filledPixelsCount > (B_HEALTHBAR_PIXELS * 20 / 100)) // more than 20% hp
            barElementId = HEALTHBOX_GFX_HP_BAR_YELLOW;
        else
            barElementId = HEALTHBOX_GFX_HP_BAR_RED; // 20 % or less

        for (i = 0; i < 6; i++)
        {
            u8 healthbarSpriteId = gSprites[gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId].hMain_HealthBarSpriteId;
            if (i < 2)
                CpuCopy32(GetHealthboxElementGfxPtr(barElementId) + array[i] * 32,
                          (void*)(OBJ_VRAM0 + (gSprites[healthbarSpriteId].oam.tileNum + 2 + i) * TILE_SIZE_4BPP), 32);
            else
                CpuCopy32(GetHealthboxElementGfxPtr(barElementId) + array[i] * 32,
                          (void*)(OBJ_VRAM0 + 64 + (i + gSprites[healthbarSpriteId].oam.tileNum) * TILE_SIZE_4BPP), 32);
        }
        break;
    case EXP_BAR:
        CalcBarFilledPixels(gBattleSpritesDataPtr->battleBars[battlerId].maxValue,
                            gBattleSpritesDataPtr->battleBars[battlerId].oldValue,
                            gBattleSpritesDataPtr->battleBars[battlerId].receivedValue,
                            &gBattleSpritesDataPtr->battleBars[battlerId].currValue,
                            array, B_EXPBAR_PIXELS / 8);
        level = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_LEVEL);
        if (level == MAX_LEVEL)
        {
            for (i = 0; i < 8; i++)
                array[i] = 0;
        }
        for (i = 0; i < 8; i++)
        {
            if (i < 4)
                CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_12) + array[i] * 32,
                          (void*)(OBJ_VRAM0 + (gSprites[gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId].oam.tileNum + 0x24 + i) * TILE_SIZE_4BPP), 32);
            else
                CpuCopy32(GetHealthboxElementGfxPtr(HEALTHBOX_GFX_12) + array[i] * 32,
                          (void*)(OBJ_VRAM0 + 0xB80 + (i + gSprites[gBattleSpritesDataPtr->battleBars[battlerId].healthboxSpriteId].oam.tileNum) * TILE_SIZE_4BPP), 32);
        }
        break;
    }
}
static s32 CalcNewBarValue(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 scale, u16 toAdd)
{
    s32 ret, newValue;
    scale *= 8;

    if (*currValue == -32768) // first function call
    {
        if (maxValue < scale)
            *currValue = Q_24_8(oldValue);
        else
            *currValue = oldValue;
    }

    newValue = oldValue - receivedValue;
    if (newValue < 0)
        newValue = 0;
    else if (newValue > maxValue)
        newValue = maxValue;

    if (maxValue < scale)
    {
        if (newValue == Q_24_8_TO_INT(*currValue) && (*currValue & 0xFF) == 0)
            return -1;
    }
    else
    {
        if (newValue == *currValue) // we're done, the bar's value has been updated
            return -1;
    }

    if (maxValue < scale) // handle cases of max var having less pixels than the whole bar
    {
        s32 toAdd_ = Q_24_8(maxValue) / scale;

        if (receivedValue < 0) // fill bar right
        {
            *currValue += toAdd_;
            ret = Q_24_8_TO_INT(*currValue);
            if (ret >= newValue)
            {
                *currValue = Q_24_8(newValue);
                ret = newValue;
            }
        }
        else // move bar left
        {
            *currValue -= toAdd_;
            ret = Q_24_8_TO_INT(*currValue);
            // try round up
            if ((*currValue & 0xFF) > 0)
                ret++;
            if (ret <= newValue)
            {
                *currValue = Q_24_8(newValue);
                ret = newValue;
            }
        }
    }
    else
    {
        if (receivedValue < 0) // fill bar right
        {
            *currValue += toAdd;
            if (*currValue > newValue)
                *currValue = newValue;
            ret = *currValue;
        }
        else // move bar left
        {
            *currValue -= toAdd;
            if (*currValue < newValue)
                *currValue = newValue;
            ret = *currValue;
        }
    }

    return ret;
}

static u8 CalcBarFilledPixels(s32 maxValue, s32 oldValue, s32 receivedValue, s32 *currValue, u8 *arg4, u8 scale)
{
    u8 pixels, filledPixels, totalPixels;
    u8 i;

    s32 newValue = oldValue - receivedValue;
    if (newValue < 0)
        newValue = 0;
    else if (newValue > maxValue)
        newValue = maxValue;

    totalPixels = scale * 8;

    for (i = 0; i < scale; i++)
        arg4[i] = 0;

    if (maxValue < totalPixels)
        pixels = (*currValue * totalPixels / maxValue) >> 8;
    else
        pixels = *currValue * totalPixels / maxValue;

    filledPixels = pixels;

    if (filledPixels == 0 && newValue > 0)
    {
        arg4[0] = 1;
        filledPixels = 1;
    }
    else
    {
        for (i = 0; i < scale; i++)
        {
            if (pixels >= 8)
            {
                arg4[i] = 8;
            }
            else
            {
                arg4[i] = pixels;
                break;
            }
            pixels -= 8;
        }
    }

    return filledPixels;
}

// These functions seem as if they were made for testing the health bar.
static s16 sub_804A460(struct TestingBar *barInfo, s32 *currValue, u8 bg, u8 x, u8 y)
{
    s16 ret;

    ret = CalcNewBarValue(barInfo->maxValue,
                          barInfo->oldValue,
                          barInfo->receivedValue,
                          currValue, B_HEALTHBAR_PIXELS / 8, 1);

    sub_804A510(barInfo, currValue, bg, x, y);

    return ret;
}

static s16 sub_804A4C8(struct TestingBar *barInfo, s32 *currValue)
{
    s16 ret;

    ret = CalcNewBarValue(barInfo->maxValue,
                          barInfo->oldValue,
                          barInfo->receivedValue,
                          currValue, B_HEALTHBAR_PIXELS / 8, 1);

    return ret;
}

static void sub_804A4F0(struct TestingBar *barInfo, s32 *currValue, u8 bg, u8 x, u8 y)
{
    sub_804A510(barInfo, currValue, bg, x, y);
}

static void sub_804A510(struct TestingBar *barInfo, s32 *currValue, u8 bg, u8 x, u8 y)
{
    u8 spC[B_HEALTHBAR_PIXELS / 8];
    u16 tiles[B_HEALTHBAR_PIXELS / 8];
    u8 i;

    CalcBarFilledPixels(barInfo->maxValue,
                        barInfo->oldValue,
                        barInfo->receivedValue,
                        currValue, spC, B_HEALTHBAR_PIXELS / 8);

    for (i = 0; i < B_HEALTHBAR_PIXELS / 8; i++)
    {
        tiles[i] = (barInfo->pal << 12) | (barInfo->tileOffset + spC[i]);
    }

    CopyToBgTilemapBufferRect_ChangePalette(bg, tiles, x, y, 6, 1, 17);
}

static u8 GetScaledExpFraction(s32 oldValue, s32 receivedValue, s32 maxValue, u8 scale)
{
    s32 newVal, result;
    s8 oldToMax, newToMax;

    scale *= 8;
    newVal = oldValue - receivedValue;

    if (newVal < 0)
        newVal = 0;
    else if (newVal > maxValue)
        newVal = maxValue;

    oldToMax = oldValue * scale / maxValue;
    newToMax = newVal * scale / maxValue;
    result = oldToMax - newToMax;

    return abs(result);
}

u8 GetScaledHPFraction(s16 hp, s16 maxhp, u8 scale)
{
    u8 result = hp * scale / maxhp;

    if (result == 0 && hp > 0)
        return 1;

    return result;
}

u8 GetHPBarLevel(s16 hp, s16 maxhp)
{
    u8 result;

    if (hp == maxhp)
    {
        result = HP_BAR_FULL;
    }
    else
    {
        u8 fraction = GetScaledHPFraction(hp, maxhp, B_HEALTHBAR_PIXELS);
        if (fraction > (B_HEALTHBAR_PIXELS * 50 / 100)) // more than 50 % hp
            result = HP_BAR_GREEN;
        else if (fraction > (B_HEALTHBAR_PIXELS * 20 / 100)) // more than 20% hp; less than or equal 50 %
            result = HP_BAR_YELLOW;
        else if (fraction > 0)      //more than 0% less than or equal to 20%
            result = HP_BAR_RED;
        else
            result = HP_BAR_EMPTY;
    }//so in a pinch makes sense, and will activate soon as hp is in yellow

    return result;
}

static const struct WindowTemplate sHealthboxWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x000
};


static u8* AddTextPrinterAndCreateWindowOnHealthbox(const u8 *str, u32 x, u32 y, u32 *windowId)
{
    u16 winId;
    u8 color[3];
    struct WindowTemplate winTemplate = sHealthboxWindowTemplate;

    winId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(winId, PIXEL_FILL(2));

    color[0] = 2;
    color[1] = 1;
    color[2] = 3;

    AddTextPrinterParameterized4(winId, 0, x, y, 0, 0, color, -1, str);

    *windowId = winId;
    return (u8*)(GetWindowAttribute(winId, WINDOW_TILE_DATA));
}

static void RemoveWindowOnHealthbox(u32 windowId)
{
    RemoveWindow(windowId);
}

static void TextIntoHealthboxObject(void *dest, u8 *windowTileData, s32 windowWidth)
{
    CpuCopy32(windowTileData + 256, dest + 256, windowWidth * TILE_SIZE_4BPP);
// + 256 as that prevents the top 4 blank rows of sHealthboxWindowTemplate from being copied
    if (windowWidth > 0)
    {
        do
        {
            CpuCopy32(windowTileData + 20, dest + 20, 12);
            dest += 32, windowTileData += 32;
            windowWidth--;
        } while (windowWidth != 0);
    }
}

static void SafariTextIntoHealthboxObject(void *dest, u8 *windowTileData, u32 windowWidth)
{
    CpuCopy32(windowTileData, dest, windowWidth * TILE_SIZE_4BPP);
    CpuCopy32(windowTileData + 256, dest + 256, windowWidth * TILE_SIZE_4BPP);
}

//ABILITY POPUP
/*
#define ABILITY_POP_UP_TAG 0xD720

// for sprite
#define tOriginalX      data[0]
#define tHide           data[1]
#define tFrames         data[2]
#define tRightToLeft    data[3]
#define tBattlerId      data[4]
#define tIsMain         data[5]

// for task
#define tSpriteId1      data[6]
#define tSpriteId2      data[7]

static const u8 sAbilityPopUpGfx[] = INCBIN_U8("graphics/battle_interface/ability_pop_up.4bpp");
static const u16 sAbilityPopUpPalette[] = INCBIN_U16("graphics/battle_interface/ability_pop_up.gbapal");

static const struct SpriteSheet sSpriteSheet_AbilityPopUp =
{
    sAbilityPopUpGfx, sizeof(sAbilityPopUpGfx), ABILITY_POP_UP_TAG
};
static const struct SpritePalette sSpritePalette_AbilityPopUp =
{
    sAbilityPopUpPalette, ABILITY_POP_UP_TAG
};

static const struct OamData sOamData_AbilityPopUp =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = ST_OAM_H_RECTANGLE,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_AbilityPopUp1[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd* const sSpriteAnimTable_AbilityPopUp1[] =
{
    sSpriteAnim_AbilityPopUp1
};

static const struct SpriteTemplate sSpriteTemplate_AbilityPopUp1 =
{
    .tileTag = ABILITY_POP_UP_TAG,
    .paletteTag = ABILITY_POP_UP_TAG,
    .oam = &sOamData_AbilityPopUp,
    .anims = sSpriteAnimTable_AbilityPopUp1,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_AbilityPopUp
};

static const union AnimCmd sSpriteAnim_AbilityPopUp2[] =
{
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_END
};

static const union AnimCmd* const sSpriteAnimTable_AbilityPopUp2[] =
{
    sSpriteAnim_AbilityPopUp2
};

static const struct SpriteTemplate sSpriteTemplate_AbilityPopUp2 =
{
    .tileTag = ABILITY_POP_UP_TAG,
    .paletteTag = ABILITY_POP_UP_TAG,
    .oam = &sOamData_AbilityPopUp,
    .anims = sSpriteAnimTable_AbilityPopUp2,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_AbilityPopUp
};

#define ABILITY_POP_UP_POS_X_DIFF 64
#define ABILITY_POP_UP_POS_X_SLIDE 68

static const s16 sAbilityPopUpCoordsDoubles[MAX_BATTLERS_COUNT][2] =
{
    {29, 80}, // player left
    {204, 19}, // opponent left
    {29, 97}, // player right
    {204, 36}, // opponent right
};

static const s16 sAbilityPopUpCoordsSingles[MAX_BATTLERS_COUNT][2] =
{
    {29, 93}, // player
    {204, 23}, // opponent
};

static u8* AddTextPrinterAndCreateWindowOnAbilityPopUp(const u8* str, u32 x, u32 y, u32 color1, u32 color2, u32 color3, u32* windowId)
{
    u8 color[3] = { color1, color2, color3 };
    struct WindowTemplate winTemplate = { 0 };
    winTemplate.width = 8;
    winTemplate.height = 2;

    *windowId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(*windowId, (color1 << 4) | (color1));

    AddTextPrinterParameterized4(*windowId, 0, x, y, 0, 0, color, -1, str);
    return (u8*)(GetWindowAttribute(*windowId, WINDOW_TILE_DATA));
}

static void TextIntoAbilityPopUp(void* dest, u8* windowTileData, s32 arg2, bool32 arg3)
{
    CpuCopy32(windowTileData + 256, dest + 256, arg2 * 32);
    if (arg2 > 0)
    {
        do
        {
            if (arg3)
                CpuCopy32(windowTileData + 16, dest + 16, 16);
            else
                CpuCopy32(windowTileData + 20, dest + 20, 12);
            dest += 32, windowTileData += 32;
            arg2--;
        } while (arg2 != 0);
    }
}

#define MAX_CHARS_PRINTED 12

static void PrintOnAbilityPopUp(const u8* str, u8* spriteTileData1, u8* spriteTileData2, u32 x1, u32 x2, u32 y, u32 color1, u32 color2, u32 color3)
{
    u32 windowId, i;
    u8* windowTileData;
    u8 text1[MAX_CHARS_PRINTED + 2];
    u8 text2[MAX_CHARS_PRINTED + 2];

    for (i = 0; i < MAX_CHARS_PRINTED + 1; i++)
    {
        text1[i] = str[i];
        if (text1[i] == EOS)
            break;
    }
    text1[i] = EOS;

    windowTileData = AddTextPrinterAndCreateWindowOnAbilityPopUp(text1, x1, y, color1, color2, color3, &windowId);
    TextIntoAbilityPopUp(spriteTileData1, windowTileData, 8, (y == 0));
    RemoveWindow(windowId);

    if (i == MAX_CHARS_PRINTED + 1)
    {
        for (i = 0; i < MAX_CHARS_PRINTED; i++)
        {
            text2[i] = str[MAX_CHARS_PRINTED + i];
            if (text2[i] == EOS)
                break;
        }
        text2[i] = EOS;

        windowTileData = AddTextPrinterAndCreateWindowOnAbilityPopUp(text2, x2, y, color1, color2, color3, &windowId);
        TextIntoAbilityPopUp(spriteTileData2, windowTileData, 1, (y == 0));
        RemoveWindow(windowId);
    }
}

static void PrintBattlerOnAbilityPopUp(u8 battlerId, u8 spriteId1, u8 spriteId2)
{
    int i;
    u8 lastChar;
    u8* name;
    u8 monName[POKEMON_NAME_LENGTH + 3] = { 0 };
    u8* nick = gBattleMons[battlerId].nickname;

    for (i = 0; i < POKEMON_NAME_LENGTH; ++i)
    {
        monName[i] = nick[i];
        if (nick[i] == EOS || i + 1 == POKEMON_NAME_LENGTH)
            break;
    }

    name = monName + i + 1;
    if (*(name - 1) == EOS)
        name--;

    lastChar = *(name - 1);
    name[0] = CHAR_SGL_QUOTE_RIGHT; // apostraphe
    name++;
    if (lastChar != CHAR_S && lastChar != CHAR_s)
    {
        name[0] = CHAR_s;
        name++;
    }

    name[0] = EOS;
    PrintOnAbilityPopUp((const u8*)monName,
        (void*)(OBJ_VRAM0)+(gSprites[spriteId1].oam.tileNum * 32),
        (void*)(OBJ_VRAM0)+(gSprites[spriteId2].oam.tileNum * 32),
        7, 0,
        0,
        2, 7, 1);
}

static void PrintAbilityOnAbilityPopUp(u32 ability, u8 spriteId1, u8 spriteId2)
{
    PrintOnAbilityPopUp(gAbilityNames[ability],
        (void*)(OBJ_VRAM0)+(gSprites[spriteId1].oam.tileNum * 32) + 256,
        (void*)(OBJ_VRAM0)+(gSprites[spriteId2].oam.tileNum * 32) + 256,
        7, 1,
        4,
        7, 9, 1);
}*/

//#define PIXEL_COORDS_TO_OFFSET(x, y)(            \
/*Add tiles by X*/                                \
((y / 8) * 32 * 8)                                \
/*Add tiles by X*/                                \
+ ((x / 8) * 32)                                \
/*Add pixels by Y*/                                \
+ ((((y) - ((y / 8) * 8))) * 4)                    \
/*Add pixels by X*/                                \
+ ((((x) - ((x / 8) * 8)) / 2)))

/*static const u16 sOverwrittenPixelsTable[][2] =
{
    {PIXEL_COORDS_TO_OFFSET(0, 0), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 1), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 2), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 3), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 4), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 5), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 6), 5},
    {PIXEL_COORDS_TO_OFFSET(0, 7), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 8), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 9), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 10), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 11), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 12), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 13), 8},

    {PIXEL_COORDS_TO_OFFSET(8, 13), 8},
    {PIXEL_COORDS_TO_OFFSET(16, 13), 8},
    {PIXEL_COORDS_TO_OFFSET(24, 13), 8},
    {PIXEL_COORDS_TO_OFFSET(32, 13), 8},
    {PIXEL_COORDS_TO_OFFSET(40, 13), 8},
    {PIXEL_COORDS_TO_OFFSET(48, 13), 8},
    {PIXEL_COORDS_TO_OFFSET(56, 13), 8},

    {PIXEL_COORDS_TO_OFFSET(0, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(8, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(16, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(24, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(32, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(40, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(48, 14), 8},
    {PIXEL_COORDS_TO_OFFSET(56, 14), 8},

    {PIXEL_COORDS_TO_OFFSET(0, 15), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 16), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 17), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 18), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 19), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 20), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 21), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 22), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 23), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 24), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 25), 3},
    {PIXEL_COORDS_TO_OFFSET(0, 26), 3},
};

static inline void CopyPixels(u8* dest, const u8* src, u32 pixelCount)
{
    u32 i = 0;

    if (pixelCount & 1)
    {
        while (pixelCount != 0)
        {
            dest[i] &= ~(0xF);
            dest[i] |= (src[i] & 0xF);
            if (--pixelCount != 0)
            {
                dest[i] &= ~(0xF0);
                dest[i] |= (src[i] & 0xF0);
                pixelCount--;
            }
            i++;
        }
    }
    else
    {
        for (i = 0; i < pixelCount / 2; i++)
            dest[i] = src[i];
    }
}

static void RestoreOverwrittenPixels(u8* tiles)
{
    u32 i;
    u8* buffer = Alloc(sizeof(sAbilityPopUpGfx) * 2);

    CpuCopy32(tiles, buffer, sizeof(sAbilityPopUpGfx));

    for (i = 0; i < ARRAY_COUNT(sOverwrittenPixelsTable); i++)
    {
        CopyPixels(buffer + sOverwrittenPixelsTable[i][0],
            sAbilityPopUpGfx + sOverwrittenPixelsTable[i][0],
            sOverwrittenPixelsTable[i][1]);
    }

    CpuCopy32(buffer, tiles, sizeof(sAbilityPopUpGfx));
    Free(buffer);
}

void CreateAbilityPopUp(u8 battlerId, u32 ability, bool32 isDoubleBattle)
{
    const s16(*coords)[2];
    u8 spriteId1, spriteId2, battlerPosition, taskId;


    if (gBattleScripting.abilityPopupOverwrite != 0)
        ability = gBattleScripting.abilityPopupOverwrite;

    if (!gBattleStruct->activeAbilityPopUps)
    {
        LoadSpriteSheet(&sSpriteSheet_AbilityPopUp);
        LoadSpritePalette(&sSpritePalette_AbilityPopUp);
    }
    gBattleStruct->activeAbilityPopUps |= gBitTable[battlerId];
    battlerPosition = GetBattlerPosition(battlerId);

    if (isDoubleBattle)
        coords = sAbilityPopUpCoordsDoubles;
    else
        coords = sAbilityPopUpCoordsSingles;

    if ((battlerPosition & BIT_SIDE) == B_SIDE_PLAYER)
    {
        spriteId1 = CreateSprite(&sSpriteTemplate_AbilityPopUp1,
            coords[battlerPosition][0] - ABILITY_POP_UP_POS_X_SLIDE,
            coords[battlerPosition][1], 0);
        spriteId2 = CreateSprite(&sSpriteTemplate_AbilityPopUp2,
            coords[battlerPosition][0] - ABILITY_POP_UP_POS_X_SLIDE + ABILITY_POP_UP_POS_X_DIFF,
            coords[battlerPosition][1], 0);

        gSprites[spriteId1].tOriginalX = coords[battlerPosition][0];
        gSprites[spriteId2].tOriginalX = coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_DIFF;

        gSprites[spriteId1].tRightToLeft = TRUE;
        gSprites[spriteId2].tRightToLeft = TRUE;
    }
    else
    {
        spriteId1 = CreateSprite(&sSpriteTemplate_AbilityPopUp1,
            coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_SLIDE,
            coords[battlerPosition][1], 0);
        spriteId2 = CreateSprite(&sSpriteTemplate_AbilityPopUp2,
            coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_SLIDE + ABILITY_POP_UP_POS_X_DIFF,
            coords[battlerPosition][1], 0);

        gSprites[spriteId1].tOriginalX = coords[battlerPosition][0];
        gSprites[spriteId2].tOriginalX = coords[battlerPosition][0] + ABILITY_POP_UP_POS_X_DIFF;

        gSprites[spriteId1].tRightToLeft = FALSE;
        gSprites[spriteId2].tRightToLeft = FALSE;
    }

    gBattleStruct->abilityPopUpSpriteIds[gBattleAnimAttacker][0] = spriteId1;
    gBattleStruct->abilityPopUpSpriteIds[gBattleAnimAttacker][1] = spriteId2;

    taskId = CreateTask(Task_FreeAbilityPopUpGfx, 5);
    gTasks[taskId].tSpriteId1 = spriteId1;
    gTasks[taskId].tSpriteId2 = spriteId2;

    gSprites[spriteId1].tIsMain = TRUE;
    gSprites[spriteId1].tBattlerId = battlerId;
    gSprites[spriteId2].tBattlerId = battlerId;

    StartSpriteAnim(&gSprites[spriteId1], 0);
    StartSpriteAnim(&gSprites[spriteId2], 0);

    PrintBattlerOnAbilityPopUp(battlerId, spriteId1, spriteId2);
    PrintAbilityOnAbilityPopUp(ability, spriteId1, spriteId2);
    RestoreOverwrittenPixels((void*)(OBJ_VRAM0)+(gSprites[spriteId1].oam.tileNum * 32));
}

#define FRAMES_TO_WAIT 48

static void SpriteCb_AbilityPopUp(struct Sprite* sprite)
{
    if (!sprite->tHide) // Show
    {
        if (sprite->tIsMain && ++sprite->tFrames == 4)
            PlaySE(SE_SELECT);
        if ((!sprite->tRightToLeft && (sprite->pos1.x -= 4) <= sprite->tOriginalX)
            || (sprite->tRightToLeft && (sprite->pos1.x += 4) >= sprite->tOriginalX)
            )
        {
            sprite->pos1.x = sprite->tOriginalX;
            sprite->tHide = TRUE;
            sprite->tFrames = FRAMES_TO_WAIT;
        }
    }
    else // Hide
    {
        if (sprite->tFrames == 0)
        {
            if ((!sprite->tRightToLeft && (sprite->pos1.x += 4) >= sprite->tOriginalX + ABILITY_POP_UP_POS_X_SLIDE)
                || (sprite->tRightToLeft && (sprite->pos1.x -= 4) <= sprite->tOriginalX - ABILITY_POP_UP_POS_X_SLIDE)
                )
            {
                gBattleStruct->activeAbilityPopUps &= ~(gBitTable[sprite->tBattlerId]);
                DestroySprite(sprite);
            }
        }
        else
        {
            if (!gBattleScripting.fixedPopup)
                sprite->tFrames--;
        }
    }
}

void DestroyAbilityPopUp(u8 battlerId)
{
    gSprites[gBattleStruct->abilityPopUpSpriteIds[battlerId][0]].tFrames = 0;
    gSprites[gBattleStruct->abilityPopUpSpriteIds[battlerId][1]].tFrames = 0;
    gBattleScripting.fixedPopup = FALSE;
}

static void Task_FreeAbilityPopUpGfx(u8 taskId)
{
    if (!gSprites[gTasks[taskId].tSpriteId1].inUse
        && !gSprites[gTasks[taskId].tSpriteId2].inUse
        && !gBattleStruct->activeAbilityPopUps)
    {
        FreeSpriteTilesByTag(ABILITY_POP_UP_TAG);
        FreeSpritePaletteByTag(ABILITY_POP_UP_TAG);
        DestroyTask(taskId);
    }
}
*/