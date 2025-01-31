#include "global.h"
#include "gflib.h"
#include "decompress.h"

extern const struct CompressedSpriteSheet gMonFrontPicTable[];
extern const struct CompressedSpriteSheet gMonBackPicTable[];
extern const struct CompressedSpriteSheet gTrainerFrontPicTable[];
extern const struct CompressedSpriteSheet gTrainerBackPicTable[];
extern const struct CompressedSpritePalette gTrainerFrontPicPaletteTable[];
extern const union AnimCmd *const gSpriteAnimTable_82349BC[];
extern const union AnimCmd *const *const gTrainerFrontAnimsPtrTable[];

// Static type declarations

struct PicData
{
    u8 *frames;
    struct SpriteFrameImage *images;
    u16 paletteTag;
    u8 spriteId;
    u8 active;
};

// Static RAM declarations
#define PICS_COUNT 8

static EWRAM_DATA struct SpriteTemplate sCreatingSpriteTemplate = {};
static EWRAM_DATA struct PicData sSpritePics[PICS_COUNT] = {};

// Static ROM declarations

// .rodata

static const struct PicData gUnknown_8453178 = {};

static const struct OamData gUnknown_8453184 =
{
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64)
};

// .text

void DummyPicSpriteCallback(struct Sprite *sprite)
{

}

bool16 ResetAllPicSprites(void)
{
    int i;

    for (i = 0; i < PICS_COUNT; i ++)
        sSpritePics[i] = gUnknown_8453178;

    return FALSE;
}

static bool16 DecompressPic(u16 species, u32 personality, bool8 isFrontPic, u8 *dest, bool8 isTrainer, bool8 ignoreDeoxys)
{
    if (!isTrainer)
    {
        if (isFrontPic)
        {
            if (!ignoreDeoxys)
                LoadSpecialPokePic( dest, species, personality, isFrontPic);
            else
                LoadSpecialPokePic_DontHandleDeoxys( dest, species, personality, isFrontPic);
        }
        else
        {
            if (!ignoreDeoxys)
                LoadSpecialPokePic( dest, species, personality, isFrontPic);
            else
                LoadSpecialPokePic_DontHandleDeoxys( dest, species, personality, isFrontPic);
        }
    }
    else
    {
        if (isFrontPic)
            DecompressPicFromTable(&gTrainerFrontPicTable[species], dest, species);
        else
            DecompressPicFromTable(&gTrainerBackPicTable[species], dest, species);
    }
    return FALSE;
}

static bool16 DecompressPic_HandleDeoxys(u16 species, u32 personality, bool8 isFrontPic, u8 *dest, bool8 isTrainer)
{
    return DecompressPic(species, personality, isFrontPic, dest, isTrainer, FALSE);
}

//important need this for showing right pal
//in sum screen etc. believe
void LoadPicPaletteByTagOrSlot(u16 species, bool8 isShiny, u32 personality, u8 paletteSlot, u16 paletteTag, bool8 isTrainer)
{
    if (!isTrainer)
    {
        if (paletteTag == TAG_NONE)
        {
            sCreatingSpriteTemplate.paletteTag = TAG_NONE;
            LoadCompressedPalette(GetMonSpritePalFromSpeciesAndPersonality(species, isShiny, personality), 0x100 + paletteSlot * 0x10, 0x20);
        }
        else
        {
            sCreatingSpriteTemplate.paletteTag = paletteTag;
            LoadCompressedSpritePaletteWithTag(GetMonSpritePalFromSpeciesAndPersonality(species, isShiny, personality), species);
        }
    }
    else
    {
        if (paletteTag == TAG_NONE)
        {
            sCreatingSpriteTemplate.paletteTag = TAG_NONE;
            LoadCompressedPalette(gTrainerFrontPicPaletteTable[species].data, 0x100 + paletteSlot * 0x10, 0x20);
        }
        else
        {
            sCreatingSpriteTemplate.paletteTag = paletteTag;
            LoadCompressedSpritePalette(&gTrainerFrontPicPaletteTable[species]);
        }
    }
}

void LoadPicPaletteBySlot(u16 species, bool8 isShiny, u32 personality, u8 paletteSlot, bool8 isTrainer)
{
    if (!isTrainer)
        LoadCompressedPalette(GetMonSpritePalFromSpeciesAndPersonality(species, isShiny, personality), paletteSlot * 0x10, 0x20);
    else
        LoadCompressedPalette(gTrainerFrontPicPaletteTable[species].data, paletteSlot * 0x10, 0x20);
}

void AssignSpriteAnimsTable(bool8 isTrainer)
{
    if (!isTrainer)
        sCreatingSpriteTemplate.anims = gSpriteAnimTable_82349BC;
    else
        sCreatingSpriteTemplate.anims = gTrainerFrontAnimsPtrTable[0];
}

u16 CreatePicSprite(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, s16 x, s16 y, u8 paletteSlot, u16 paletteTag, bool8 isTrainer, bool8 ignoreDeoxys)
{
    u8 i;
    u8 *framePics;
    struct SpriteFrameImage *images;
    int j;
    u8 spriteId;

    for (i = 0; i < PICS_COUNT; i ++)
    {
        if (!sSpritePics[i].active)
        {
            break;
        }
    }
    if (i == PICS_COUNT)
    {
        return 0xFFFF;
    }
    framePics = Alloc(4 * 0x800);
    if (!framePics)
    {
        return 0xFFFF;
    }
    images = Alloc(4 * sizeof(struct SpriteFrameImage));
    if (!images)
    {
        Free(framePics);//never frees images is that an issue?
        return 0xFFFF;
    }
    if (DecompressPic(species, personality, isFrontPic, framePics, isTrainer, ignoreDeoxys))
    {
        // debug trap?
        return 0xFFFF;
    }
    for (j = 0; j < 4; j ++)
    {
        images[j].data = framePics + 0x800 * j;
        images[j].size = 0x800;
    }
    sCreatingSpriteTemplate.tileTag = 0xFFFF;
    sCreatingSpriteTemplate.oam = &gUnknown_8453184;
    AssignSpriteAnimsTable(isTrainer);
    sCreatingSpriteTemplate.images = images;
    sCreatingSpriteTemplate.affineAnims = gDummySpriteAffineAnimTable;
    sCreatingSpriteTemplate.callback = DummyPicSpriteCallback;
    LoadPicPaletteByTagOrSlot(species, isShiny, personality, paletteSlot, paletteTag, isTrainer);
    spriteId = CreateSprite(&sCreatingSpriteTemplate, x, y, 0);
    if (paletteTag == 0xFFFF)
    {
        gSprites[spriteId].oam.paletteNum = paletteSlot;
    }
    sSpritePics[i].frames = framePics;
    sSpritePics[i].images = images;
    sSpritePics[i].paletteTag = paletteTag;
    sSpritePics[i].spriteId = spriteId;
    sSpritePics[i].active = TRUE;
    return spriteId;
}

u16 CreatePicSprite_HandleDeoxys(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, s16 x, s16 y, u8 paletteSlot, u16 paletteTag, bool8 isTrainer)
{
    return CreatePicSprite(species, isShiny, personality, isFrontPic, x, y, paletteSlot, paletteTag, isTrainer, FALSE);
}

u16 FreeAndDestroyPicSpriteInternal(u16 spriteId)
{
    u8 i;
    u8 *framePics;
    struct SpriteFrameImage *images;

    for (i = 0; i < PICS_COUNT; i ++)
    {
        if (sSpritePics[i].spriteId == spriteId)
        {
            break;
        }
    }
    if (i == PICS_COUNT)
    {
        return 0xFFFF;
    }
    framePics = sSpritePics[i].frames;
    images = sSpritePics[i].images;
    if (sSpritePics[i].paletteTag != 0xFFFF)
    {
        FreeSpritePaletteByTag(GetSpritePaletteTagByPaletteNum(gSprites[spriteId].oam.paletteNum));
    }
    DestroySprite(&gSprites[spriteId]);
    Free(framePics);
    Free(images);
    sSpritePics[i] = gUnknown_8453178;
    return 0;
}

//think never called
u16 LoadPicSpriteInWindow(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, u8 paletteSlot, u8 windowId, bool8 isTrainer)
{
    if (DecompressPic_HandleDeoxys(species, personality, isFrontPic, (u8 *)GetWindowAttribute(windowId, WINDOW_TILE_DATA), FALSE))
    {
        return 0xFFFF;
    }
    LoadPicPaletteBySlot(species, isShiny, personality, paletteSlot, isTrainer);
    return 0;
}

//used for both trainer pics and pokemon pics
//shiny is false in every use so dont need to worry about that
u16 CreateTrainerCardSprite(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, u16 destX, u16 destY, u8 paletteSlot, u8 windowId, bool8 isTrainer, bool8 LoadMonPalette)
{
    u8 *framePics;

    framePics = Alloc(4 * 0x800);

    if (framePics && !DecompressPic_HandleDeoxys(species, personality, isFrontPic, framePics, isTrainer))
    {
        BlitBitmapRectToWindow(windowId, framePics, 0, 0, 0x40, 0x40, destX, destY, 0x40, 0x40);
        if (LoadMonPalette)
            LoadPicPaletteBySlot(species, isShiny, personality, paletteSlot, isTrainer);
        else
        //load black palatte
        {
            LoadPicPaletteBySlot(SPECIES_NONE, isShiny, 8, paletteSlot, isTrainer);
        } //sems setting personality to above 8 makes use shiny pal
        //done this way I can use the shiny palette for question mark, which would never come up
        //leavig the normal one untouched
        //don't rememberwhy I did this, or if its even still relevant?
        //I may have undone whatever change this was
        //ok I think it actually means to lock it from being shiny?
        //may not need at all but kept personality value as 8, for caution
            
        Free(framePics);
        return 0;
    }
    return 0xFFFF;
}

u16 CreateMonPicSprite(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, s16 x, s16 y, u8 paletteSlot, u16 paletteTag, bool8 ignoreDeoxys)
{
    return CreatePicSprite(species, isShiny, personality, isFrontPic, x, y, paletteSlot, paletteTag, FALSE, ignoreDeoxys);
}

u16 CreateMonPicSprite_HandleDeoxys(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, s16 x, s16 y, u8 paletteSlot, u16 paletteTag)
{
    return CreateMonPicSprite(species, isShiny, personality, isFrontPic, x, y, paletteSlot, paletteTag, FALSE);
}

u16 FreeAndDestroyMonPicSprite(u16 spriteId)
{
    return FreeAndDestroyPicSpriteInternal(spriteId);
}

//never loads shiny pic, just default palette
u16 LoadMonPicInWindow(u16 species, bool8 isShiny, u32 personality, bool8 isFrontPic, u8 paletteSlot, u8 windowId, bool8 LoadMonPalette)
{
    return CreateTrainerCardSprite(species, isShiny, personality, isFrontPic, 0, 0, paletteSlot, windowId, FALSE, LoadMonPalette);
}

//unused
u16 CreateTrainerCardMonIconSprite(u16 species, u32 otId, u32 personality, bool8 isFrontPic, u16 destX, u16 destY, u8 paletteSlot, u8 windowId, bool8 LoadMonPalette)
{
    return CreateTrainerCardSprite(species, otId, personality, isFrontPic, destX, destY, paletteSlot, windowId, FALSE, TRUE);
}

u16 CreateTrainerPicSprite(u16 species, bool8 isFrontPic, s16 x, s16 y, u8 paletteSlot, u16 paletteTag)
{
    return CreatePicSprite_HandleDeoxys(species, 0, 0, isFrontPic, x, y, paletteSlot, paletteTag, TRUE);
}

u16 FreeAndDestroyTrainerPicSprite(u16 spriteId)
{
    return FreeAndDestroyPicSpriteInternal(spriteId);
}

///unused
u16 LoadTrainerPicInWindow(u16 species, bool8 isFrontPic, u8 paletteSlot, u8 windowId)
{
    return LoadPicSpriteInWindow(species, 0, 0, isFrontPic, paletteSlot, windowId, TRUE);
}

//also never loads shiny pic
u16 CreateTrainerCardTrainerPicSprite(u16 species, bool8 isFrontPic, u16 destX, u16 destY, u8 paletteSlot, u8 windowId)
{
    return CreateTrainerCardSprite(species, FALSE, 0, isFrontPic, destX, destY, paletteSlot, windowId, TRUE, TRUE);
}

u16 PlayerGenderToFrontTrainerPicId_Debug(u8 gender, bool8 getClass)
{
    if (getClass == TRUE)
    {
        switch (gender)
        {
        default:
            return gFacilityClassToPicIndex[0x87];
        case MALE:
            return gFacilityClassToPicIndex[0x86];
        }
    }
    return gender;
}
