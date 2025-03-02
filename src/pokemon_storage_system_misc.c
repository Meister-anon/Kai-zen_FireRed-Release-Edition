#include <stdlib.h> // to declare abs
#include "global.h"
#include "gflib.h"
#include "pokemon_icon.h"
#include "pokemon_storage_system_internal.h"
#include "text_window.h"
#include "decompress.h"
#include "item.h"
#include "item_menu_icons.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "trig.h"
#include "constants/items.h"

struct MoveMons
{
    u8 field_0;
    u8 state;
    u8 fromRow;
    u8 fromColumn;
    u8 toRow;
    u8 toColumn;
    u8 field_6;
    u8 field_7;
    u8 minRow;
    u8 minColumn;
    u8 rowsTotal;
    u8 columsTotal;
    u16 bgX;
    u16 bgY;
    u16 field_10;
    struct BoxPokemon boxMons[IN_BOX_COUNT];
};

static EWRAM_DATA struct MoveMons *sMoveMonsPtr = NULL;

static bool8 sub_8095138(void);
static bool8 sub_8095234(void);
static bool8 sub_80952A0(void);
static bool8 sub_8095314(void);
static bool8 sub_8095394(void);
static bool8 sub_80953BC(void);
static void sub_8095520(void);
static void sub_80955C4(u8 arg0, u8 arg1, u8 arg2);
static void sub_80955FC(u8 arg0, u8 arg1, u8 arg2);
static void sub_8095634(u8 arg0, u8 arg1, u8 arg2);
static void sub_809566C(u8 arg0, u8 arg1, u8 arg2);
static void sub_80956A4(u8 x, u8 y);
static void sub_809572C(u8 x, u8 y);
static void sub_8095780(u16 bgX, u16 bgY, u16 duration);
static u8 sub_8095790(void);
static void sub_80957C8(void);
static void sub_80958A0(void);
static void sub_8095918(void);
static void sub_80959A8(void);
static void sub_8095A58(void);

static const struct WindowTemplate gUnknown_83D35D4 = {
    .bg = 0,
    .tilemapLeft = 10,
    .tilemapTop = 3,
    .width = 20,
    .height = 18,
    .paletteNum = 9,
    .baseBlock = 0x00a
};

bool8 sub_8095050(void)
{
    sMoveMonsPtr = Alloc(sizeof(*sMoveMonsPtr));
    if (sMoveMonsPtr != NULL)
    {
        gPSSData->field_2200 = AddWindow8Bit(&gUnknown_83D35D4);
        if (gPSSData->field_2200 != 0xFF)
        {
            FillWindowPixelBuffer(gPSSData->field_2200, PIXEL_FILL(0));
            return TRUE;
        }
    }

    return FALSE;
}

void sub_80950A4(void)
{
    if (sMoveMonsPtr != NULL)
        Free(sMoveMonsPtr);
}

void MultiMove_SetFunction(u8 arg0)
{
    sMoveMonsPtr->field_0 = arg0;
    sMoveMonsPtr->state = 0;
}

bool8 MultiMove_RunFunction(void)
{
    switch (sMoveMonsPtr->field_0)
    {
    case 0:
        return sub_8095138();
    case 1:
        return sub_8095234();
    case 2:
        return sub_80952A0();
    case 3:
        return sub_8095314();
    case 4:
        return sub_8095394();
    case 5:
        return sub_80953BC();
    }

    return FALSE;
}

static bool8 sub_8095138(void)
{
    switch (sMoveMonsPtr->state)
    {
    case 0:
        HideBg(0);
        LoadMonIconPalettesAt(0x80);
        sMoveMonsPtr->state++;
        break;
    case 1:
        GetCursorBoxColumnAndRow(&sMoveMonsPtr->fromRow, &sMoveMonsPtr->fromColumn);
        sMoveMonsPtr->toRow = sMoveMonsPtr->fromRow;
        sMoveMonsPtr->toColumn = sMoveMonsPtr->fromColumn;
        ChangeBgX(0, -1024, 0);
        ChangeBgY(0, -1024, 0);
        FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 0x20, 0x20);
        FillWindowPixelBuffer8Bit(gPSSData->field_2200, PIXEL_FILL(0));
        sub_80956A4(sMoveMonsPtr->fromRow, sMoveMonsPtr->fromColumn);
        SetBgAttribute(0, BG_ATTR_PALETTEMODE, 1);
        PutWindowTilemap(gPSSData->field_2200);
        CopyWindowToVram8Bit(gPSSData->field_2200, COPYWIN_BOTH);
        BlendPalettes(0x3F00, 8, RGB_WHITE);
        StartCursorAnim(2);
        SetGpuRegBits(REG_OFFSET_BG0CNT, BGCNT_256COLOR);
        sMoveMonsPtr->state++;
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            ShowBg(0);
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool8 sub_8095234(void)
{
    switch (sMoveMonsPtr->state)
    {
    case 0:
        HideBg(0);
        sMoveMonsPtr->state++;
        break;
    case 1:
        sub_8095A58();
        StartCursorAnim(0);
        sMoveMonsPtr->state++;
        break;
    case 2:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            sub_8094D40();
            LoadPalette(GetTextWindowPalette(3), 0xD0, 0x20);
            ShowBg(0);
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static bool8 sub_80952A0(void)
{
    switch (sMoveMonsPtr->state)
    {
    case 0:
        if (!sub_80924A8())
        {
            GetCursorBoxColumnAndRow(&sMoveMonsPtr->field_6, &sMoveMonsPtr->field_7);
            sub_8095520();
            sMoveMonsPtr->toRow = sMoveMonsPtr->field_6;
            sMoveMonsPtr->toColumn = sMoveMonsPtr->field_7;
            CopyWindowToVram8Bit(gPSSData->field_2200, COPYWIN_GFX);
            sMoveMonsPtr->state++;
        }
        break;
    case 1:
        return IsDma3ManagerBusyWithBgCopy();
    }

    return TRUE;
}

static bool8 sub_8095314(void)
{
    u8 var1, var2;

    switch (sMoveMonsPtr->state)
    {
    case 0:
        sub_80957C8();
        sub_80958A0();
        sub_8092BAC(FALSE);
        sMoveMonsPtr->state++;
        break;
    case 1:
        if (!DoMonPlaceChange())
        {
            StartCursorAnim(3);
            sub_8095780(0, 256, 8);
            sub_8092BAC(TRUE);
            sMoveMonsPtr->state++;
        }
        break;
    case 2:
        var1 = sub_8095790();
        var2 = DoMonPlaceChange();
        if (!var1 && !var2)
            return FALSE;
        break;
    }

    return TRUE;
}

static bool8 sub_8095394(void)
{
    u8 var1 = sub_80924A8();
    u8 var2 = sub_8095790();

    if (!var1 && !var2)
        return FALSE;
    else
        return TRUE;
}

static bool8 sub_80953BC(void)
{
    switch (sMoveMonsPtr->state)
    {
    case 0:
        sub_80959A8();
        sub_8095780(0, -256, 8);
        sub_8092BAC(FALSE);
        sMoveMonsPtr->state++;
        break;
    case 1:
        if (!DoMonPlaceChange() && !sub_8095790())
        {
            sub_8095918();
            StartCursorAnim(2);
            sub_8092BAC(TRUE);
            HideBg(0);
            sMoveMonsPtr->state++;
        }
        break;
    case 2:
        if (!DoMonPlaceChange())
        {
            StartCursorAnim(0);
            sub_8095A58();
            sMoveMonsPtr->state++;
        }
        break;
    case 3:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            LoadPalette(GetTextWindowPalette(3), 0xD0, 0x20);
            sub_8094D40();
            ShowBg(0);
            return FALSE;
        }
        break;
    }

    return TRUE;
}

bool8 sub_8095474(u8 arg0)
{
    switch (arg0)
    {
    case 0: // up
        if (sMoveMonsPtr->minColumn == 0)
            return FALSE;
        sMoveMonsPtr->minColumn--;
        sub_8095780(0, 1024, 6);
        break;
    case 1: // down
        if (sMoveMonsPtr->minColumn + sMoveMonsPtr->columsTotal >= 5)
            return FALSE;
        sMoveMonsPtr->minColumn++;
        sub_8095780(0, -1024, 6);
        break;
    case 2: // left
        if (sMoveMonsPtr->minRow == 0)
            return FALSE;
        sMoveMonsPtr->minRow--;
        sub_8095780(1024, 0, 6);
        break;
    case 3: // right
        if (sMoveMonsPtr->minRow + sMoveMonsPtr->rowsTotal > 5)
            return FALSE;
        sMoveMonsPtr->minRow++;
        sub_8095780(-1024, 0, 6);
        break;
    }

    return TRUE;
}

static void sub_8095520(void)
{
    s16 var = (abs(sMoveMonsPtr->fromRow - sMoveMonsPtr->field_6)) - (abs(sMoveMonsPtr->fromRow - sMoveMonsPtr->toRow));
    s16 var2 = (abs(sMoveMonsPtr->fromColumn - sMoveMonsPtr->field_7)) - (abs(sMoveMonsPtr->fromColumn - sMoveMonsPtr->toColumn));

    if (var > 0)
        sub_80955C4(sMoveMonsPtr->field_6, sMoveMonsPtr->fromColumn, sMoveMonsPtr->toColumn);

    if (var < 0)
    {
        sub_8095634(sMoveMonsPtr->toRow, sMoveMonsPtr->fromColumn, sMoveMonsPtr->toColumn);
        sub_80955C4(sMoveMonsPtr->field_6, sMoveMonsPtr->fromColumn, sMoveMonsPtr->toColumn);
    }

    if (var2 > 0)
        sub_80955FC(sMoveMonsPtr->field_7, sMoveMonsPtr->fromRow, sMoveMonsPtr->toRow);

    if (var2 < 0)
    {
        sub_809566C(sMoveMonsPtr->toColumn, sMoveMonsPtr->fromRow, sMoveMonsPtr->toRow);
        sub_80955FC(sMoveMonsPtr->field_7, sMoveMonsPtr->fromRow, sMoveMonsPtr->toRow);
    }
}

static void sub_80955C4(u8 arg0, u8 arg1, u8 arg2)
{
    u8 var1 = arg1;

    if (arg1 > arg2)
    {
        arg1 = arg2;
        arg2 = var1;
    }

    while (arg1 <= arg2)
        sub_80956A4(arg0, arg1++);
}

static void sub_80955FC(u8 arg0, u8 arg1, u8 arg2)
{
    u8 var1 = arg1;

    if (arg1 > arg2)
    {
        arg1 = arg2;
        arg2 = var1;
    }

    while (arg1 <= arg2)
        sub_80956A4(arg1++, arg0);
}

static void sub_8095634(u8 arg0, u8 arg1, u8 arg2)
{
    u8 var1 = arg1;

    if (arg1 > arg2)
    {
        arg1 = arg2;
        arg2 = var1;
    }

    while (arg1 <= arg2)
        sub_809572C(arg0, arg1++);
}

static void sub_809566C(u8 arg0, u8 arg1, u8 arg2)
{
    u8 var1 = arg1;

    if (arg1 > arg2)
    {
        arg1 = arg2;
        arg2 = var1;
    }

    while (arg1 <= arg2)
        sub_809572C(arg1++, arg0);
}

static void sub_80956A4(u8 x, u8 y)
{
    u8 position = x + (IN_BOX_ROWS * y);
    u16 species = GetCurrentBoxMonData(position, MON_DATA_SPECIES_OR_EGG);
    u32 personality = GetCurrentBoxMonData(position, MON_DATA_PERSONALITY);

    if (species != SPECIES_NONE)
    {
        const u8 *iconGfx = GetMonIconPtr(species, personality, 1);
        u8 index = GetValidMonIconPalIndex(species) + 8;

        BlitBitmapRectToWindow4BitTo8Bit(gPSSData->field_2200,
                                         iconGfx,
                                         0,
                                         0,
                                         32,
                                         32,
                                         24 * x,
                                         24 * y,
                                         32,
                                         32,
                                         index);
    }
}

static void sub_809572C(u8 x, u8 y)
{
    u8 position = x + (IN_BOX_ROWS * y);
    u16 species = GetCurrentBoxMonData(position, MON_DATA_SPECIES_OR_EGG);

    if (species != SPECIES_NONE)
    {
        FillWindowPixelRect8Bit(gPSSData->field_2200,
                                PIXEL_FILL(0),
                                24 * x,
                                24 * y,
                                32,
                                32);
    }
}

static void sub_8095780(u16 bgX, u16 bgY, u16 duration)
{
    sMoveMonsPtr->bgX = bgX;
    sMoveMonsPtr->bgY = bgY;
    sMoveMonsPtr->field_10 = duration;
}

static u8 sub_8095790(void)
{
    if (sMoveMonsPtr->field_10 != 0)
    {
        ChangeBgX(0, sMoveMonsPtr->bgX, 1);
        ChangeBgY(0, sMoveMonsPtr->bgY, 1);
        sMoveMonsPtr->field_10--;
    }

    return sMoveMonsPtr->field_10;
}


static u8 sub_80961D8(void);
static bool32 sub_8096210(u8 cursorArea, u8 cursorPos);
static u8 sub_8096258(u8 cursorArea, u8 cursorPos);
static void sub_80962F0(u8 id, u8 cursorArea, u8 cursorPos);
static void sub_8096408(u8 id, const u32 * tiles, const u32 * pal);
static void sub_80964B8(u8 id, u8 affineAnimNo);
static void sub_80964E8(u8 id, u8 command, u8 cursorArea, u8 cursorPos);
static void sub_8096624(u8 id, bool8 show);
//static const u32 *GetItemIconPic(u16 itemId);
//static const u32 *GetItemIconPalette(u16 itemId);
static void sub_8096898(u32 x);
static void sub_809692C(struct Sprite * sprite);
static void sub_8096958(struct Sprite * sprite);
static void sub_80969BC(struct Sprite * sprite);
static void sub_80969F4(struct Sprite * sprite);
static void sub_8096A74(struct Sprite * sprite);
static void sub_8096B10(struct Sprite * sprite);
static void sub_8096BAC(struct Sprite * sprite);

static const u32 gUnknown_83D35DC[] = INCBIN_U32("graphics/interface/pss_unk_83D35DC.4bpp");

static const struct OamData gUnknown_83D365C = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_NORMAL,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0x000,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AffineAnimCmd gUnknown_83D3664[] = {
    AFFINEANIMCMD_FRAME(128, 128, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_83D3674[] = {
    AFFINEANIMCMD_FRAME(88, 88, 0, 0),
    AFFINEANIMCMD_FRAME(5, 5, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_83D368C[] = {
    AFFINEANIMCMD_FRAME(128, 128, 0, 0),
    AFFINEANIMCMD_FRAME(-5, -5, 0, 8),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_83D36A4[] = {
    AFFINEANIMCMD_FRAME(128, 128, 0, 0),
    AFFINEANIMCMD_FRAME(10, 10, 0, 12),
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_83D36C4[] = {
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_FRAME(-10, -10, 0, 12),
    AFFINEANIMCMD_FRAME(128, 128, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_83D36E4[] = {
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_FRAME(-5, -5, 0, 16),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_83D36FC[] = {
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const gUnknown_83D370C[] = {
    gUnknown_83D3664,
    gUnknown_83D3674,
    gUnknown_83D368C,
    gUnknown_83D36A4,
    gUnknown_83D36C4,
    gUnknown_83D36E4,
    gUnknown_83D36FC
};

static const struct SpriteTemplate gUnknown_83D3728 = {
    .tileTag = TAG_TILE_7,
    .paletteTag = TAG_PAL_DACB,
    .oam = &gUnknown_83D365C,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83D370C,
    .callback = SpriteCallbackDummy,
};

void CreateItemIconSprites(void)
{
    s32 i;
    u8 spriteId;
    struct CompressedSpriteSheet spriteSheet;
    struct SpriteTemplate spriteTemplate;
    static u32 gUnknown_3000FE8[0x61];

    if (gPSSData->boxOption == BOX_OPTION_MOVE_ITEMS)
    {
        spriteSheet.data = gUnknown_3000FE8;
        spriteSheet.size = 0x200;
        spriteTemplate = gUnknown_83D3728;

        for (i = 0; i < MAX_ITEM_ICONS; i++)
        {
            spriteSheet.tag = TAG_TILE_7 + i;
            LoadCompressedSpriteSheet(&spriteSheet);
            gPSSData->itemIconSprites[i].tiles = GetSpriteTileStartByTag(spriteSheet.tag) * 32 + (void*)(OBJ_VRAM0);
            gPSSData->itemIconSprites[i].palIndex = AllocSpritePalette(TAG_PAL_DACB + i);
            gPSSData->itemIconSprites[i].palIndex *= 16;
            gPSSData->itemIconSprites[i].palIndex += 0x100;
            spriteTemplate.tileTag = TAG_TILE_7 + i;
            spriteTemplate.paletteTag = TAG_PAL_DACB + i;
            spriteId = CreateSprite(&spriteTemplate, 0, 0, 11);
            gPSSData->itemIconSprites[i].sprite = &gSprites[spriteId];
            gPSSData->itemIconSprites[i].sprite->invisible = TRUE;
            gPSSData->itemIconSprites[i].active = 0;
        }
    }
    gPSSData->movingItem = ITEM_NONE;
}

void TryLoadItemIconAtPos(u8 cursorArea, u8 cursorPos)
{
    u16 heldItem;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;
    if (sub_8096210(cursorArea, cursorPos))
        return;

    switch (cursorArea)
    {
    case CURSOR_AREA_IN_BOX:
        if (!GetCurrentBoxMonData(cursorPos, MON_DATA_SANITY_HAS_SPECIES))
            return;
        heldItem = GetCurrentBoxMonData(cursorPos, MON_DATA_HELD_ITEM);
        break;
    case CURSOR_AREA_IN_PARTY:
        if (!GetMonData(&gPlayerParty[cursorPos], MON_DATA_SANITY_HAS_SPECIES))
            return;
        heldItem = GetMonData(&gPlayerParty[cursorPos], MON_DATA_HELD_ITEM);
        break;
    default:
        return;
    }

    if (heldItem != ITEM_NONE)
    {
        const u32 *tiles = GetItemIconPic(heldItem);
        const u32 *pal = GetItemIconPalette(heldItem);
        u8 id = sub_80961D8();

        sub_80962F0(id, cursorArea, cursorPos);
        sub_8096408(id, tiles, pal);
        sub_80964B8(id, 1);
        sub_8096624(id, TRUE);
    }
}

void sub_8095D44(u8 cursorArea, u8 cursorPos)
{
    u8 id;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;

    id = sub_8096258(cursorArea, cursorPos);
    sub_80964B8(id, 2);
    sub_80964E8(id, 0, cursorArea, cursorPos);
}

void Item_FromMonToMoving(u8 cursorArea, u8 cursorPos)
{
    u8 id;
    u16 item;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;

    id = sub_8096258(cursorArea, cursorPos);
    item = 0;
    sub_80964B8(id, ITEM_ANIM_PICK_UP);
    sub_80964E8(id, ITEM_CB_TO_HAND, cursorArea, cursorPos);
    sub_80962F0(id, CURSOR_AREA_IN_HAND, 0);
    if (cursorArea  == CURSOR_AREA_IN_BOX)
    {
        SetCurrentBoxMonData(cursorPos, MON_DATA_HELD_ITEM, &item);
        SetBoxMonIconObjMode(cursorPos, ST_OAM_OBJ_BLEND);
    }
    else
    {
        SetMonData(&gPlayerParty[cursorPos], MON_DATA_HELD_ITEM, &item);
        SetPartyMonIconObjMode(cursorPos, ST_OAM_OBJ_BLEND);
    }

    gPSSData->movingItem = gPSSData->cursorMonItem;
}

void InitItemIconInCursor(u16 item)
{
    const u32 *tiles = GetItemIconPic(item);
    const u32 *pal = GetItemIconPalette(item);
    u8 id = sub_80961D8();

    sub_8096408(id, tiles, pal);
    sub_80964B8(id, ITEM_ANIM_LARGE);
    sub_80964E8(id, ITEM_CB_TO_HAND, 0, 0);
    sub_80962F0(id, CURSOR_AREA_IN_HAND, 0);
    sub_8096624(id, TRUE);
    gPSSData->movingItem = item;
}

void Item_SwitchMonsWithMoving(u8 cursorArea, u8 cursorPos)
{
    u8 id;
    u16 item;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;

    id = sub_8096258(cursorArea, cursorPos);
    sub_80964B8(id, ITEM_ANIM_PICK_UP);
    sub_80964E8(id, ITEM_CB_SWAP_TO_HAND, CURSOR_AREA_IN_HAND, 0);
    if (cursorArea == CURSOR_AREA_IN_BOX)
    {
        item = GetCurrentBoxMonData(cursorPos, MON_DATA_HELD_ITEM);
        SetCurrentBoxMonData(cursorPos, MON_DATA_HELD_ITEM, &gPSSData->movingItem);
        gPSSData->movingItem = item;
    }
    else
    {
        item = GetMonData(&gPlayerParty[cursorPos], MON_DATA_HELD_ITEM);
        SetMonData(&gPlayerParty[cursorPos], MON_DATA_HELD_ITEM, &gPSSData->movingItem);
        gPSSData->movingItem = item;
    }

    id = sub_8096258(2, 0);
    sub_80964B8(id, ITEM_ANIM_PUT_DOWN);
    sub_80964E8(id, ITEM_CB_SWAP_TO_MON, cursorArea, cursorPos);
}

void Item_GiveMovingToMon(u8 cursorArea, u8 cursorPos)
{
    u8 id;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;

    id = sub_8096258(2, 0);
    sub_80964B8(id, ITEM_ANIM_PUT_DOWN);
    sub_80964E8(id, ITEM_CB_TO_MON, cursorArea, cursorPos);
    if (cursorArea == CURSOR_AREA_IN_BOX)
    {
        SetCurrentBoxMonData(cursorPos, MON_DATA_HELD_ITEM, &gPSSData->movingItem);
        SetBoxMonIconObjMode(cursorPos, ST_OAM_OBJ_NORMAL);
    }
    else
    {
        SetMonData(&gPlayerParty[cursorPos], MON_DATA_HELD_ITEM, &gPSSData->movingItem);
        SetPartyMonIconObjMode(cursorPos, ST_OAM_OBJ_NORMAL);
    }
}

void Item_TakeMons(u8 cursorArea, u8 cursorPos)
{
    u8 id;
    u16 item;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;

    item = ITEM_NONE;
    id = sub_8096258(cursorArea, cursorPos);
    sub_80964B8(id, ITEM_ANIM_DISAPPEAR);
    sub_80964E8(id, ITEM_CB_WAIT_ANIM, cursorArea, cursorPos);
    if (cursorArea  == CURSOR_AREA_IN_BOX)
    {
        SetCurrentBoxMonData(cursorPos, MON_DATA_HELD_ITEM, &item);
        SetBoxMonIconObjMode(cursorPos, ST_OAM_OBJ_BLEND);
    }
    else
    {
        SetMonData(&gPlayerParty[cursorPos], MON_DATA_HELD_ITEM, &item);
        SetPartyMonIconObjMode(cursorPos, ST_OAM_OBJ_BLEND);
    }
}

void sub_8096088(void)
{
    if (gPSSData->boxOption == BOX_OPTION_MOVE_ITEMS)
    {
        u8 id = sub_8096258(CURSOR_AREA_IN_HAND, 0);
        sub_80964B8(id, ITEM_ANIM_PUT_AWAY);
        sub_80964E8(id, ITEM_CB_WAIT_ANIM, 2, 0);
    }
}

// The party menu is being closed, if the cursor is on
// a Pokémon that has a held item make sure it slides
// up along with the closing menu.
void MoveHeldItemWithPartyMenu(void)
{
    s32 i;

    if (gPSSData->boxOption != BOX_OPTION_MOVE_ITEMS)
        return;

    for (i = 0; i < MAX_ITEM_ICONS; i++)
    {
        if (gPSSData->itemIconSprites[i].active && gPSSData->itemIconSprites[i].cursorArea == CURSOR_AREA_IN_PARTY)
            sub_80964E8(i, ITEM_CB_HIDE_PARTY, 2, 0);
    }
}

bool8 IsItemIconAnimActive(void)
{
    s32 i;

    for (i = 0; i < MAX_ITEM_ICONS; i++)
    {
        if (gPSSData->itemIconSprites[i].active)
        {
            if (!gPSSData->itemIconSprites[i].sprite->affineAnimEnded && gPSSData->itemIconSprites[i].sprite->affineAnimBeginning)
                return TRUE;
            if (gPSSData->itemIconSprites[i].sprite->callback != SpriteCallbackDummy && gPSSData->itemIconSprites[i].sprite->callback != sub_80969BC)
                return TRUE;
        }
    }

    return FALSE;
}

bool8 IsActiveItemMoving(void)
{
    s32 i;

    if (gPSSData->boxOption == BOX_OPTION_MOVE_ITEMS)
    {
        for (i = 0; i < MAX_ITEM_ICONS; i++)
        {
            if (gPSSData->itemIconSprites[i].active && gPSSData->itemIconSprites[i].cursorArea == CURSOR_AREA_BOX_TITLE)
                return TRUE;
        }
    }

    return FALSE;
}

const u8 *GetMovingItemName(void)
{
    return ItemId_GetName(gPSSData->movingItem);
}

u16 GetMovingItem(void)
{
    return gPSSData->movingItem;
}

static u8 sub_80961D8(void)
{
    u8 i;

    for (i = 0; i < MAX_ITEM_ICONS; i++)
    {
        if (!gPSSData->itemIconSprites[i].active)
        {
            gPSSData->itemIconSprites[i].active = TRUE;
            return i;
        }
    }

    return MAX_ITEM_ICONS;
}

static bool32 sub_8096210(u8 cursorArea, u8 cursorPos)
{
    s32 i;

    for (i = 0; i < MAX_ITEM_ICONS; i++)
    {
        if (gPSSData->itemIconSprites[i].active
            && gPSSData->itemIconSprites[i].cursorArea == cursorArea
            && gPSSData->itemIconSprites[i].cursorPos == cursorPos)
            return TRUE;
    }

    return FALSE;
}

static u8 sub_8096258(u8 cursorArea, u8 cursorPos)
{
    u8 i;

    for (i = 0; i < MAX_ITEM_ICONS; i++)
    {
        if (gPSSData->itemIconSprites[i].active
            && gPSSData->itemIconSprites[i].cursorArea == cursorArea
            && gPSSData->itemIconSprites[i].cursorPos == cursorPos)
            return i;
    }

    return MAX_ITEM_ICONS;
}

static u8 sub_80962A8(struct Sprite *sprite)
{
    u8 i;

    for (i = 0; i < MAX_ITEM_ICONS; i++)
    {
        if (gPSSData->itemIconSprites[i].active
            && gPSSData->itemIconSprites[i].sprite == sprite)
            return i;
    }

    return MAX_ITEM_ICONS;
}

static void sub_80962F0(u8 id, u8 cursorArea, u8 cursorPos)
{
    u8 row, column;

    if (id >= MAX_ITEM_ICONS)
        return;

    switch (cursorArea)
    {
    case CURSOR_AREA_IN_BOX:
        row = cursorPos % IN_BOX_ROWS;
        column = cursorPos / IN_BOX_ROWS;
        gPSSData->itemIconSprites[id].sprite->pos1.x = (24 * row) + 112;
        gPSSData->itemIconSprites[id].sprite->pos1.y = (24 * column) + 56;
        gPSSData->itemIconSprites[id].sprite->oam.priority = 2;
        break;
    case CURSOR_AREA_IN_PARTY:
        if (cursorPos == 0)
        {
            gPSSData->itemIconSprites[id].sprite->pos1.x = 116;
            gPSSData->itemIconSprites[id].sprite->pos1.y = 76;
        }
        else
        {
            gPSSData->itemIconSprites[id].sprite->pos1.x = 164;
            gPSSData->itemIconSprites[id].sprite->pos1.y = 24 * (cursorPos - 1) + 28;
        }
        gPSSData->itemIconSprites[id].sprite->oam.priority = 1;
        break;
    }

    gPSSData->itemIconSprites[id].cursorArea = cursorArea;
    gPSSData->itemIconSprites[id].cursorPos = cursorPos;
}

static void sub_8096408(u8 id, const u32 *itemTiles, const u32 *itemPal)
{
    s32 i;

    if (id >= MAX_ITEM_ICONS)
        return;

    CpuFastFill(0, gPSSData->itemIconBuffer, 0x200);
    LZ77UnCompWram(itemTiles, gPSSData->PSS_tileBuffer);
    for (i = 0; i < 3; i++)
        CpuFastCopy(gPSSData->PSS_tileBuffer + (i * 0x60), gPSSData->itemIconBuffer + (i * 0x80), 0x60);

    CpuFastCopy(gPSSData->itemIconBuffer, gPSSData->itemIconSprites[id].tiles, 0x200);
    LZ77UnCompWram(itemPal, gPSSData->itemIconBuffer);
    LoadPalette(gPSSData->itemIconBuffer, gPSSData->itemIconSprites[id].palIndex, 0x20);
}

static void sub_80964B8(u8 id, u8 animNum)
{
    if (id >= MAX_ITEM_ICONS)
        return;

    StartSpriteAffineAnim(gPSSData->itemIconSprites[id].sprite, animNum);
}

static void sub_80964E8(u8 id, u8 command, u8 cursorArea, u8 cursorPos)
{
    if (id >= MAX_ITEM_ICONS)
        return;

    switch (command)
    {
    case 0:
        gPSSData->itemIconSprites[id].sprite->data[0] = id;
        gPSSData->itemIconSprites[id].sprite->callback = sub_809692C;
        break;
    case 1:
        gPSSData->itemIconSprites[id].sprite->data[0] = 0;
        gPSSData->itemIconSprites[id].sprite->callback = sub_8096958;
        break;
    case 2:
        gPSSData->itemIconSprites[id].sprite->data[0] = 0;
        gPSSData->itemIconSprites[id].sprite->data[6] = cursorArea;
        gPSSData->itemIconSprites[id].sprite->data[7] = cursorPos;
        gPSSData->itemIconSprites[id].sprite->callback = sub_80969F4;
        break;
    case 3:
        gPSSData->itemIconSprites[id].sprite->data[0] = 0;
        gPSSData->itemIconSprites[id].sprite->callback = sub_8096A74;
        gPSSData->itemIconSprites[id].sprite->data[6] = cursorArea;
        gPSSData->itemIconSprites[id].sprite->data[7] = cursorPos;
        break;
    case 4:
        gPSSData->itemIconSprites[id].sprite->data[0] = 0;
        gPSSData->itemIconSprites[id].sprite->data[6] = cursorArea;
        gPSSData->itemIconSprites[id].sprite->data[7] = cursorPos;
        gPSSData->itemIconSprites[id].sprite->callback = sub_8096B10;
        break;
    case 7:
        gPSSData->itemIconSprites[id].sprite->callback = sub_8096BAC;
        break;
    }
}

static void sub_8096624(u8 id, bool8 show)
{
    if (id >= MAX_ITEM_ICONS)
        return;

    gPSSData->itemIconSprites[id].active = show;
    gPSSData->itemIconSprites[id].sprite->invisible = (show == FALSE);
}

const u32 *GetItemIconPic(u16 itemId)
{
    return GetItemIconGfxPtr(itemId, 0);
}

const u32 *GetItemIconPalette(u16 itemId)
{
    return GetItemIconGfxPtr(itemId, 1);
}

void PrintItemDescription(void)
{
    const u8 *description;

    if (IsActiveItemMoving())
        description = ItemId_GetDescription(gPSSData->movingItem);
    else
        description = ItemId_GetDescription(gPSSData->cursorMonItem);

    FillWindowPixelBuffer(2, PIXEL_FILL(1));
    AddTextPrinterParameterized5(2, 2, description, 2, 0, 0, NULL, 0, 0);
}

void sub_80966F4(void)
{
    gPSSData->field_2236 = 25;
    LoadBgTiles(0, gUnknown_83D35DC, 0x80, 0x1A4);
    sub_8096898(0);
}

bool8 sub_8096728(void)
{
    s32 i, var;

    if (gPSSData->field_2236 == 0)
        return FALSE;

    gPSSData->field_2236--;
    var = 25 - gPSSData->field_2236;
    for (i = 0; i < var; i++)
    {
        WriteSequenceToBgTilemapBuffer(0, GetBgAttribute(0, BG_ATTR_BASETILE) + 0x14 + gPSSData->field_2236 + i, i, 12, 1, 8, 15, 25);
    }

    sub_8096898(var);
    return (gPSSData->field_2236 != 0);
}

bool8 sub_80967C0(void)
{
    s32 i, var;

    if (gPSSData->field_2236 == 25)
        return FALSE;

    if (gPSSData->field_2236 == 0)
        FillBgTilemapBufferRect(0, 0, 25, 11, 1, 10, 17);

    gPSSData->field_2236++;
    var = 25 - gPSSData->field_2236;
    for (i = 0; i < var; i++)
    {
        WriteSequenceToBgTilemapBuffer(0, GetBgAttribute(0, BG_ATTR_BASETILE) + 0x14 + gPSSData->field_2236 + i, i, 12, 1, 8, 15, 25);
    }

    sub_8096898(var);

    FillBgTilemapBufferRect(0, 0, var, 11, 1, 10, 0x11);
    return (gPSSData->field_2236 != 25);
}

static void sub_8096898(u32 x)
{
    if (x != 0)
    {
        FillBgTilemapBufferRect(0, 0x1A4, 0, 0xB, x, 1, 0xFu);
        FillBgTilemapBufferRect(0, 0x9A4, 0, 0x14, x, 1, 0xFu);
    }
    FillBgTilemapBufferRect(0, 0x1A5, x, 0xC, 1, 8, 0xFu);
    FillBgTilemapBufferRect(0, 0x1A6, x, 0xB, 1, 1, 0xFu);
    FillBgTilemapBufferRect(0, 0x1A7, x, 0x14, 1, 1, 0xFu);
    ScheduleBgCopyTilemapToVram(0);
}

static void sub_809692C(struct Sprite *sprite)
{
    if (sprite->affineAnimEnded)
    {
        sub_8096624(sprite->data[0], FALSE);
        sprite->callback = SpriteCallbackDummy;
    }
}

static void sub_8096958(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->data[1] = sprite->pos1.x << 4;
        sprite->data[2] = sprite->pos1.y << 4;
        sprite->data[3] = 10;
        sprite->data[4] = 21;
        sprite->data[5] = 0;
        sprite->data[0]++;
    case 1:
        sprite->data[1] -= sprite->data[3];
        sprite->data[2] -= sprite->data[4];
        sprite->pos1.x = sprite->data[1] >> 4;
        sprite->pos1.y = sprite->data[2] >> 4;
        if (++sprite->data[5] > 11)
            sprite->callback = sub_80969BC;
        break;
    }
}

static void sub_80969BC(struct Sprite *sprite)
{
    sprite->pos1.x = gPSSData->field_CB4->pos1.x + 4;
    sprite->pos1.y = gPSSData->field_CB4->pos1.y + gPSSData->field_CB4->pos2.y + 8;
    sprite->oam.priority = gPSSData->field_CB4->oam.priority;
}

static void sub_80969F4(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->data[1] = sprite->pos1.x << 4;
        sprite->data[2] = sprite->pos1.y << 4;
        sprite->data[3] = 10;
        sprite->data[4] = 21;
        sprite->data[5] = 0;
        sprite->data[0]++;
    case 1:
        sprite->data[1] += sprite->data[3];
        sprite->data[2] += sprite->data[4];
        sprite->pos1.x = sprite->data[1] >> 4;
        sprite->pos1.y = sprite->data[2] >> 4;
        if (++sprite->data[5] > 11)
        {
            sub_80962F0(sub_80962A8(sprite), sprite->data[6], sprite->data[7]);
            sprite->callback = SpriteCallbackDummy;
        }
        break;
    }
}

static void sub_8096A74(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->data[1] = sprite->pos1.x << 4;
        sprite->data[2] = sprite->pos1.y << 4;
        sprite->data[3] = 10;
        sprite->data[4] = 21;
        sprite->data[5] = 0;
        sprite->data[0]++;
    case 1:
        sprite->data[1] -= sprite->data[3];
        sprite->data[2] -= sprite->data[4];
        sprite->pos1.x = sprite->data[1] >> 4;
        sprite->pos1.y = sprite->data[2] >> 4;
        sprite->pos2.x = gSineTable[sprite->data[5] * 8] >> 4;
        if (++sprite->data[5] > 11)
        {
            sub_80962F0(sub_80962A8(sprite), sprite->data[6], sprite->data[7]);
            sprite->pos2.x = 0;
            sprite->callback = sub_80969BC;
        }
        break;
    }
}

static void sub_8096B10(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->data[1] = sprite->pos1.x << 4;
        sprite->data[2] = sprite->pos1.y << 4;
        sprite->data[3] = 10;
        sprite->data[4] = 21;
        sprite->data[5] = 0;
        sprite->data[0]++;
    case 1:
        sprite->data[1] += sprite->data[3];
        sprite->data[2] += sprite->data[4];
        sprite->pos1.x = sprite->data[1] >> 4;
        sprite->pos1.y = sprite->data[2] >> 4;
        sprite->pos2.x = -(gSineTable[sprite->data[5] * 8] >> 4);
        if (++sprite->data[5] > 11)
        {
            sub_80962F0(sub_80962A8(sprite), sprite->data[6], sprite->data[7]);
            sprite->callback = SpriteCallbackDummy;
            sprite->pos2.x = 0;
        }
        break;
    }
}

static void sub_8096BAC(struct Sprite *sprite)
{
    sprite->pos1.y -= 8;
    if (sprite->pos1.y + sprite->pos2.y < -16)
    {
        sprite->callback = SpriteCallbackDummy;
        sub_8096624(sub_80962A8(sprite), FALSE);
    }
}

static void sub_80957C8(void)
{
    s32 i, j;
    s32 rowCount, columnCount;
    u8 boxId;
    u8 monArrayId;

    sMoveMonsPtr->minRow = min(sMoveMonsPtr->fromRow, sMoveMonsPtr->toRow);
    sMoveMonsPtr->minColumn = min(sMoveMonsPtr->fromColumn, sMoveMonsPtr->toColumn);
    sMoveMonsPtr->rowsTotal = abs(sMoveMonsPtr->fromRow - sMoveMonsPtr->toRow) + 1;
    sMoveMonsPtr->columsTotal = abs(sMoveMonsPtr->fromColumn - sMoveMonsPtr->toColumn) + 1;
    boxId = StorageGetCurrentBox();
    monArrayId = 0;
    rowCount = sMoveMonsPtr->minRow + sMoveMonsPtr->rowsTotal;
    columnCount = sMoveMonsPtr->minColumn + sMoveMonsPtr->columsTotal;
    for (i = sMoveMonsPtr->minColumn; i < columnCount; i++)
    {
        u8 boxPosition = (IN_BOX_ROWS * i) + sMoveMonsPtr->minRow;
        for (j = sMoveMonsPtr->minRow; j < rowCount; j++)
        {
            struct BoxPokemon *boxMon = GetBoxedMonPtr(boxId, boxPosition);

            sMoveMonsPtr->boxMons[monArrayId] = *boxMon;
            monArrayId++;
            boxPosition++;
        }
    }
}

static void sub_80958A0(void)
{
    s32 i, j;
    s32 rowCount = sMoveMonsPtr->minRow + sMoveMonsPtr->rowsTotal;
    s32 columnCount = sMoveMonsPtr->minColumn + sMoveMonsPtr->columsTotal;
    u8 boxId = StorageGetCurrentBox();

    for (i = sMoveMonsPtr->minColumn; i < columnCount; i++)
    {
        u8 boxPosition = (IN_BOX_ROWS * i) + sMoveMonsPtr->minRow;
        for (j = sMoveMonsPtr->minRow; j < rowCount; j++)
        {
            DestroyBoxMonIconAtPosition(boxPosition);
            ZeroBoxMonAt(boxId, boxPosition);
            boxPosition++;
        }
    }
}

static void sub_8095918(void)
{
    s32 i, j;
    s32 rowCount = sMoveMonsPtr->minRow + sMoveMonsPtr->rowsTotal;
    s32 columnCount = sMoveMonsPtr->minColumn + sMoveMonsPtr->columsTotal;
    u8 monArrayId = 0;

    for (i = sMoveMonsPtr->minColumn; i < columnCount; i++)
    {
        u8 boxPosition = (IN_BOX_ROWS * i) + sMoveMonsPtr->minRow;
        for (j = sMoveMonsPtr->minRow; j < rowCount; j++)
        {
            if (GetBoxMonData(&sMoveMonsPtr->boxMons[monArrayId], MON_DATA_SANITY_HAS_SPECIES))
                CreateBoxMonIconAtPos(boxPosition);
            monArrayId++;
            boxPosition++;
        }
    }
}

static void sub_80959A8(void)
{
    s32 i, j;
    s32 rowCount = sMoveMonsPtr->minRow + sMoveMonsPtr->rowsTotal;
    s32 columnCount = sMoveMonsPtr->minColumn + sMoveMonsPtr->columsTotal;
    u8 boxId = StorageGetCurrentBox();
    u8 monArrayId = 0;

    for (i = sMoveMonsPtr->minColumn; i < columnCount; i++)
    {
        u8 boxPosition = (IN_BOX_ROWS * i) + sMoveMonsPtr->minRow;
        for (j = sMoveMonsPtr->minRow; j < rowCount; j++)
        {
            if (GetBoxMonData(&sMoveMonsPtr->boxMons[monArrayId], MON_DATA_SANITY_HAS_SPECIES))
                SetBoxMonAt(boxId, boxPosition, &sMoveMonsPtr->boxMons[monArrayId]);
            boxPosition++;
            monArrayId++;
        }
    }
}

static void sub_8095A58(void)
{
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    SetBgAttribute(0, BG_ATTR_PALETTEMODE, 0);
    ClearGpuRegBits(REG_OFFSET_BG0CNT, BGCNT_256COLOR);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 32, 32);
    CopyBgTilemapBufferToVram(0);
}

u8 sub_8095AA0(void)
{
    return (IN_BOX_ROWS * sMoveMonsPtr->fromColumn) + sMoveMonsPtr->fromRow;
}

bool8 sub_8095ABC(void)
{
    s32 i, j;
    s32 rowCount = sMoveMonsPtr->minRow + sMoveMonsPtr->rowsTotal;
    s32 columnCount = sMoveMonsPtr->minColumn + sMoveMonsPtr->columsTotal;
    u8 monArrayId = 0;

    for (i = sMoveMonsPtr->minColumn; i < columnCount; i++)
    {
        u8 boxPosition = (IN_BOX_ROWS * i) + sMoveMonsPtr->minRow;
        for (j = sMoveMonsPtr->minRow; j < rowCount; j++)
        {
            if (GetBoxMonData(&sMoveMonsPtr->boxMons[monArrayId], MON_DATA_SANITY_HAS_SPECIES)
                && GetCurrentBoxMonData(boxPosition, MON_DATA_SANITY_HAS_SPECIES))
                return FALSE;

            monArrayId++;
            boxPosition++;
        }
    }

    return TRUE;
}


//  Some data transfer utility that goes functionally unused.
//  It gets initialized with UnkUtil_Init, and run every vblank in Pokémon
//  Storage with UnkUtil_Run, but neither of the Add functions are ever used,
//  so UnkUtil_Run performs no actions.

static EWRAM_DATA struct UnkStruct_2000020 *gUnknown_203982C = NULL;

static void sub_8096CDC(struct UnkStruct_2000028 *unkStruct);
static void sub_8096D70(struct UnkStruct_2000028 *unkStruct);

void sub_8096BE4(struct UnkStruct_2000020 *arg0, struct UnkStruct_2000028 *arg1, u32 arg2)
{
    gUnknown_203982C = arg0;
    arg0->unk_00 = arg1;
    arg0->unk_05 = arg2;
    arg0->unk_04 = 0;
}

void sub_8096BF8(void)
{
    u16 i;

    if (gUnknown_203982C->unk_04)
    {
        for (i = 0; i < gUnknown_203982C->unk_04; i++)
        {
            struct UnkStruct_2000028 *unkStruct = &gUnknown_203982C->unk_00[i];
            unkStruct->unk_0c(unkStruct);
        }

        gUnknown_203982C->unk_04 = 0;
    }
}

static bool8 sub_8096C40(u8 *dest, u16 dLeft, u16 dTop, const u8 *src, u16 sLeft, u16 sTop, u16 width, u16 height, u16 unkArg)
{
    struct UnkStruct_2000028 *unkStruct;

    if (gUnknown_203982C->unk_04 >= gUnknown_203982C->unk_05)
        return FALSE;

    unkStruct = &gUnknown_203982C->unk_00[gUnknown_203982C->unk_04++];
    unkStruct->unk_08 = width * 2;
    unkStruct->unk_04 = dest + 2 * (dTop * 32 + dLeft);
    unkStruct->unk_00 = src + 2 * (sTop * unkArg + sLeft);
    unkStruct->newField = height;
    unkStruct->unk_0a = unkArg;
    unkStruct->unk_0c = sub_8096CDC;
    return TRUE;
}

static void sub_8096CDC(struct UnkStruct_2000028 *unkStruct)
{
    u16 i;

    for (i = 0; i < unkStruct->newField; i++)
    {
        CpuCopy16(unkStruct->unk_00, unkStruct->unk_04, unkStruct->unk_08);
        unkStruct->unk_04 += 64;
        unkStruct->unk_00 += (unkStruct->unk_0a * 2);
    }
}

static bool8 sub_8096D14(void *dest, u16 dLeft, u16 dTop, u16 width, u16 height)
{
    struct UnkStruct_2000028 *unkStruct;

    if (gUnknown_203982C->unk_04 >= gUnknown_203982C->unk_05)
        return FALSE;

    unkStruct = &gUnknown_203982C->unk_00[gUnknown_203982C->unk_04++];
    unkStruct->unk_08 = width * 2;
    unkStruct->unk_04 = dest + ((dTop * 32) + dLeft) * 2;
    unkStruct->newField = height;
    unkStruct->unk_0c = sub_8096D70;
    return TRUE;
}

// Functionally unused
static void sub_8096D70(struct UnkStruct_2000028 *unkStruct)
{
    u16 i;

    for (i = 0; i < unkStruct->newField; i++)
    {
        Dma3FillLarge_(0, unkStruct->unk_04, unkStruct->unk_08, 16);
        unkStruct->unk_04 += 64;
    }
}

