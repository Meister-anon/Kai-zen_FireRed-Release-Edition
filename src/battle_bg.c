#include "global.h"
#include "gflib.h"
#include "battle.h"
#include "battle_bg.h"
#include "battle_anim.h"    //added for some raeson
#include "battle_message.h"
#include "battle_environment.h"
#include "decompress.h"
#include "graphics.h"
#include "link.h"
#include "new_menu_helpers.h"
#include "overworld.h"
#include "text_window.h"
#include "trig.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "data/battle_environment.h"

#define TAG_VS_LETTERS 10000


//static void CB2_unused(void);
static u8 GetBattleEnvironmentOverride(void);

static const u8 gUnknown_824829C[] = {1, 2};

static const struct OamData gOamData_82482A0 = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0x000,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct OamData gOamData_82482A8 = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0x040,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

static const union AffineAnimCmd gUnknown_82482B0[] = {
    AFFINEANIMCMD_FRAME(0x80, 0x80, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd gUnknown_82482C0[] = {
    AFFINEANIMCMD_FRAME(0x80, 0x80, 0, 0),
    AFFINEANIMCMD_FRAME(0x18, 0x18, 0x0, 0x80),
    AFFINEANIMCMD_FRAME(0x18, 0x18, 0x0, 0x80),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const gAffineAnimTable_82482E0[] = {
    gUnknown_82482B0,
    gUnknown_82482C0
};

static const struct SpriteTemplate sVsLetter_V_SpriteTemplate = {
    .tileTag = TAG_VS_LETTERS,
    .paletteTag = TAG_VS_LETTERS,
    .oam = &gOamData_82482A0,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gAffineAnimTable_82482E0,
    .callback = SpriteCB_VsLetterDummy
};

static const struct SpriteTemplate sVsLetter_S_SpriteTemplate = {
    .tileTag = TAG_VS_LETTERS,
    .paletteTag = TAG_VS_LETTERS,
    .oam = &gOamData_82482A8,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gAffineAnimTable_82482E0,
    .callback = SpriteCB_VsLetterDummy
};

static const struct CompressedSpriteSheet sVsLettersSpriteSheet = {
    gVsLettersGfx,
    0x1000,
    TAG_VS_LETTERS
};

const struct BgTemplate gBattleBgTemplates[4] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 24,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }, {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 28,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }, {
        .bg = 2,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0x000
    }, {
        .bg = 3,
        .charBaseIndex = 2,
        .mapBaseIndex = 26,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0x000
    }
};


//each constant refers to a windowID that is the window/area for each value within the main window/border of the menu
//this struct tells the dimmenssions and relative location of each windowID within the main window/border
//can rearrange move type pp etc from here, but need to figure out how to change the main window size so I can move the movenames
//tilemapLeft & tilemapTop are the respective X & Y coordinates
//need to figure out  what baseBlock means
const struct WindowTemplate sStandardBattleWindowTemplates[] = {
    [B_WIN_MSG] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 28,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x090
    },
    [B_WIN_ACTION_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 35,
        .width = 14,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 0x1c0
    },
    [B_WIN_ACTION_MENU] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 35,
        .width = 12,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x190
    },
    [B_WIN_MOVE_NAME_1] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 55,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x300
    },
    //adjusted so (MoveSelectionCreateCursorAt) will use this window position to update itself
    [B_WIN_MOVE_NAME_2] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 55,
        .width = 10,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x310
    },//original was 11, difference of 9 beetween left and right move, so increased by 4 to add increase spacing by about half, was too much 
    //brought back down to only 1 up, 13 didn't leave enough room for right side long moves
    //need to find how move cursor
    [B_WIN_MOVE_NAME_3] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 57,
        .width = 8,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x32c
    },
    [B_WIN_MOVE_NAME_4] = {
        .bg = 0,
        .tilemapLeft = 12,
        .tilemapTop = 57,
        .width = 10,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x33f
    },//width 2 starting from x coordinate 22 means my characters will fill positions 22 & 23!
    //width appears to be left alligned meaning changing with will shift the right dimmension and not the left
    [B_WIN_PP] = {
        .bg = 0,
        .tilemapLeft = 24,
        .tilemapTop = 55,
        .width = 2,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x290
    },//moving the window from 21 to 24 has overwritten the border bounds I now understand the width counts the tilemap left position as 1
    [B_WIN_MOVE_TYPE] = {
        .bg = 0,
        .tilemapLeft = 24,
        .tilemapTop = 57,
        .width = 5,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x2a6
    },//that's based on seeing the limit from pp remaining if I cound 8 from 21 & 5 from 24 I get the same ending position of 28
    //also seems width may not exactly equal number of characters since I can fit NORMAL which is 6 characters in a 5 width window
    //but width does affect the border dimmensions so I need to manage width, with tilemapLeft to make sure my window is within the bg
    [B_WIN_PP_REMAINING] = {
        .bg = 0,
        .tilemapLeft = 26,
        .tilemapTop = 55,
        .width = 3,
        .height = 2,
        .paletteNum = 5,
        .baseBlock = 0x2b6
    },
    [B_WIN_DUMMY] = {
        .bg = 0,
        .tilemapLeft = 25,
        .tilemapTop = 57,
        .width = 0,
        .height = 0,
        .paletteNum = 5,
        .baseBlock = 0x2c0
    },
    [B_WIN_SWITCH_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 24,
        .tilemapTop = 55,
        .width = 5,
        .height = 4,
        .paletteNum = 5,
        .baseBlock = 0x2c0
    },//thsi at 21 no longer fits new window had to move to 23 then need to make sure it clears, this come up with move swap in battle
    //clearing text worked after moving tileleft, just need to lower width set to 6 asame as type
    //need to move this and ppsymbol & type further over, move right lower width as needed gonna assume full width value is 30
        //since I have to account for border will make 29 max
[B_WIN_LEVEL_UP_BOX] = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 8,
    .width = 10,
    .height = 11,
    .paletteNum = 5,
    .baseBlock = 0x100
},
[B_WIN_LEVEL_UP_BANNER] = {
    .bg = 2,
    .tilemapLeft = 18,
    .tilemapTop = 0,
    .width = 12,
    .height = 3,
    .paletteNum = 6,
    .baseBlock = 0x16e
},
[B_WIN_YESNO] = {
    .bg = 0,
    .tilemapLeft = 25,
    .tilemapTop = 9,
    .width = 4,
    .height = 4,
    .paletteNum = 5,
    .baseBlock = 0x100
},
[B_WIN_VS_PLAYER] = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 3,
    .width = 7,
    .height = 2,
    .paletteNum = 5,
    .baseBlock = 0x020
},
[B_WIN_VS_OPPONENT] = {
    .bg = 2,
    .tilemapLeft = 2,
    .tilemapTop = 3,
    .width = 7,
    .height = 2,
    .paletteNum = 5,
    .baseBlock = 0x040
},
[B_WIN_VS_MULTI_PLAYER_1] = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 7,
    .height = 2,
    .paletteNum = 5,
    .baseBlock = 0x020
},
[B_WIN_VS_MULTI_PLAYER_2] = {
    .bg = 2,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 7,
    .height = 2,
    .paletteNum = 5,
    .baseBlock = 0x040
},
[B_WIN_VS_MULTI_PLAYER_3] = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 6,
    .width = 7,
    .height = 2,
    .paletteNum = 5,
    .baseBlock = 0x060
},
[B_WIN_VS_MULTI_PLAYER_4] = {
    .bg = 2,
    .tilemapLeft = 2,
    .tilemapTop = 6,
    .width = 7,
    .height = 2,
    .paletteNum = 5,
    .baseBlock = 0x080
},
[B_WIN_VS_OUTCOME_DRAW] = {
    .bg = 0,
    .tilemapLeft = 11,
    .tilemapTop = 2,
    .width = 8,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x0a0
},
[B_WIN_VS_OUTCOME_LEFT] = {
    .bg = 0,
    .tilemapLeft = 4,
    .tilemapTop = 2,
    .width = 8,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x0a0
},
[B_WIN_VS_OUTCOME_RIGHT] = {
    .bg = 0,
    .tilemapLeft = 19,
    .tilemapTop = 2,
    .width = 8,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x0b0
},
[B_WIN_OAK_OLD_MAN] = {
    .bg = 0,
    .tilemapLeft = 2,
    .tilemapTop = 15,
    .width = 26,
    .height = 4,
    .paletteNum = 7,
    .baseBlock = 0x090
},
DUMMY_WIN_TEMPLATE
};

/*UNUSED void CreateUnknownDebugSprite(void)
{
    u8 spriteId;

    ResetSpriteData();
    spriteId = CreateSprite(&gUnknownDebugSprite, 0, 0, 0);
    gSprites[spriteId].invisible = TRUE;
    SetMainCallback2(CB2_unused);
}

static void CB2_unused(void)
{
    AnimateSprites();
    BuildOamBuffer();
}*/

// If current map scene equals any of the values in sMapBattleSceneMapping,
// use its battle environment value. Otherwise, use the default.
static u8 GetBattleEnvironmentByMapScene(u8 mapBattleScene)
{
    int i;
    for (i = 0; i < NELEMS(sMapBattleSceneMapping); i++)
    {
        if (mapBattleScene == sMapBattleSceneMapping[i].mapScene)
            return sMapBattleSceneMapping[i].battleEnvironment;
    }
    return 9;
}


//will need expand for battle type i.e plan 2 v 1
#define BATTLE_ENVIRONMENT //Battle Terrain, NOT TERRAIN effect, is the entire battle field, including part battler sits on
static void LoadBattleTerrainGfx(u8 battleEnvironment)
{
    const void *tilemap;
    const void *tileset = gBattleEnvironmentInfo[battleEnvironment].background.tileset;
    const void *bgPalette = gBattleEnvironmentInfo[battleEnvironment].background.palette;
    
    if (!IsDoubleBattle())
        tilemap = gBattleEnvironmentInfo[battleEnvironment].background.tilemap;
    else
        tilemap = gBattleEnvironmentInfo[battleEnvironment].background.tilemap2;
    
    battleEnvironment = battleEnvironment >= BATTLE_ENVIRONMENT_COUNT ? BATTLE_ENVIRONMENT_GRASS : battleEnvironment;

    // Copy to bg3
    LZDecompressVram(tileset, (void*)BG_CHAR_ADDR(2));
    LZDecompressVram(tilemap, (void*)BG_SCREEN_ADDR(26));
    LoadPalette(bgPalette, 0x20, 0x60);
}

static void LoadBattleTerrainEntryGfx(u8 battleEnvironment)
{
    battleEnvironment = battleEnvironment >= BATTLE_ENVIRONMENT_COUNT ? BATTLE_ENVIRONMENT_GRASS : battleEnvironment;

    // Copy to bg1
    LZDecompressVram(gBattleEnvironmentInfo[battleEnvironment].background.entryTileset, (void*)BG_CHAR_ADDR(1));
    LZDecompressVram(gBattleEnvironmentInfo[battleEnvironment].background.entryTilemap, (void*)BG_SCREEN_ADDR(28));
}

UNUSED void GetBattleTerrainGfxPtrs(u8 battleEnvironment, const u32 **tilesPtr, const u32 **mapPtr, const u16 **palPtr)
{
    battleEnvironment = battleEnvironment >= BATTLE_ENVIRONMENT_COUNT ? BATTLE_ENVIRONMENT_GRASS : battleEnvironment;

    *tilesPtr = gBattleEnvironmentInfo[battleEnvironment].background.tileset;
    *mapPtr = gBattleEnvironmentInfo[battleEnvironment].background.tilemap;
    *palPtr = gBattleEnvironmentInfo[battleEnvironment].background.palette;
}

void BattleInitBgsAndWindows(void)
{
    ResetBgsAndClearDma3BusyFlags(FALSE);
    InitBgsFromTemplates(0, gBattleBgTemplates, NELEMS(gBattleBgTemplates));//I believe bgs & windows have different definitions than i use
    InitWindows(sStandardBattleWindowTemplates); //windows seem to be spaces where text/strings can be printed or displayed
    DeactivateAllTextPrinters();//while the bg (background) holds the window themselves?
}

void InitBattleBgsVideo(void)
{
    EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_VCOUNT | INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
    BattleInitBgsAndWindows();
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_OBJWIN_ON);
}

void LoadBattleMenuWindowGfx(void)
{
    LoadUserWindowGfx(2, 0x012, 0x10);
    LoadUserWindowGfx(2, 0x022, 0x10);
    gPlttBufferUnfaded[0x5C] = RGB( 9,  9,  9);
    gPlttBufferUnfaded[0x5D] = RGB( 9,  9,  9);
    gPlttBufferUnfaded[0x5E] = RGB(31, 31, 31);
    gPlttBufferUnfaded[0x5F] = RGB( 26,  26,  25);
    CpuCopy16(&gPlttBufferUnfaded[0x5C], &gPlttBufferFaded[0x5C], 8);
    if (gBattleTypeFlags & (BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_POKEDUDE))
    {
        Menu_LoadStdPalAt(0x70);
        TextWindow_LoadResourcesStdFrame0(0, 0x030, 0x70);
        gPlttBufferUnfaded[0x76] = RGB( 0,  0,  0);
        CpuCopy16(&gPlttBufferUnfaded[0x76], &gPlttBufferFaded[0x76], 2);
    }
}

void DrawMainBattleBackground(void)
{
    LoadBattleTerrainGfx(GetBattleEnvironmentOverride());
}

void LoadBattleTextboxAndBackground(void)
{
    LZDecompressVram(gBattleInterface_Textbox_Gfx, (void *)BG_CHAR_ADDR(0));
    CopyToBgTilemapBuffer(0, gBattleInterface_Textbox_Tilemap, 0, 0x000);
    CopyBgTilemapBufferToVram(0);
    LoadPalette(gBattleInterface_Textbox_Pal, 0x00, 0x40);
    LoadBattleMenuWindowGfx();
    DrawMainBattleBackground();
}

static void DrawLinkBattleParticipantPokeballs(u8 taskId, u8 multiplayerId, u8 bgId, u8 destX, u8 destY)
{
    s32 i;
    u16 pokeballStatuses = 0;
    u16 tiles[6];

    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gTasks[taskId].data[5] != 0)
        {
            switch (multiplayerId)
            {
            case 0:
                pokeballStatuses = 0x3F & gTasks[taskId].data[3];
                break;
            case 1:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[4]) >> 6;
                break;
            case 2:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[3]) >> 6;
                break;
            case 3:
                pokeballStatuses = 0x3F & gTasks[taskId].data[4];
                break;
            }
        }
        else
        {
            switch (multiplayerId)
            {
            case 0:
                pokeballStatuses = 0x3F & gTasks[taskId].data[3];
                break;
            case 1:
                pokeballStatuses = 0x3F & gTasks[taskId].data[4];
                break;
            case 2:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[3]) >> 6;
                break;
            case 3:
                pokeballStatuses = (0xFC0 & gTasks[taskId].data[4]) >> 6;
                break;
            }
        }

        for (i = 0; i < 3; i++)
            tiles[i] = ((pokeballStatuses & (3 << (i * 2))) >> (i * 2)) + 0x6001;

        CopyToBgTilemapBufferRect_ChangePalette(bgId, tiles, destX, destY, 3, 1, 0x11);
        CopyBgTilemapBufferToVram(bgId);
    }
    else
    {
        if (multiplayerId == gBattleStruct->multiplayerId)
            pokeballStatuses = gTasks[taskId].data[3];
        else
            pokeballStatuses = gTasks[taskId].data[4];

        for (i = 0; i < 6; i++)
            tiles[i] = ((pokeballStatuses & (3 << (i * 2))) >> (i * 2)) + 0x6001;

        CopyToBgTilemapBufferRect_ChangePalette(bgId, tiles, destX, destY, 6, 1, 0x11);
        CopyBgTilemapBufferToVram(bgId);
    }
}

static void DrawLinkBattleVsScreenOutcomeText(void)
{
    if (gBattleOutcome == B_OUTCOME_DREW)
    {
        BattlePutTextOnWindow(gText_Draw, 0x15);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleOutcome == B_OUTCOME_WON)
        {
            switch (gLinkPlayers[gBattleStruct->multiplayerId].id)
            {
            case 0:
                BattlePutTextOnWindow(gText_Win, 0x16);
                BattlePutTextOnWindow(gText_Loss, 0x17);
                break;
            case 1:
                BattlePutTextOnWindow(gText_Win, 0x17);
                BattlePutTextOnWindow(gText_Loss, 0x16);
                break;
            case 2:
                BattlePutTextOnWindow(gText_Win, 0x16);
                BattlePutTextOnWindow(gText_Loss, 0x17);
                break;
            case 3:
                BattlePutTextOnWindow(gText_Win, 0x17);
                BattlePutTextOnWindow(gText_Loss, 0x16);
                break;
            }
        }
        else
        {
            switch (gLinkPlayers[gBattleStruct->multiplayerId].id)
            {
            case 0:
                BattlePutTextOnWindow(gText_Win, 0x17);
                BattlePutTextOnWindow(gText_Loss, 0x16);
                break;
            case 1:
                BattlePutTextOnWindow(gText_Win, 0x16);
                BattlePutTextOnWindow(gText_Loss, 0x17);
                break;
            case 2:
                BattlePutTextOnWindow(gText_Win, 0x17);
                BattlePutTextOnWindow(gText_Loss, 0x16);
                break;
            case 3:
                BattlePutTextOnWindow(gText_Win, 0x16);
                BattlePutTextOnWindow(gText_Loss, 0x17);
                break;
            }
        }
    }
    else if (gBattleOutcome == B_OUTCOME_WON)
    {
        if (gLinkPlayers[gBattleStruct->multiplayerId].id != 0)
        {
            BattlePutTextOnWindow(gText_Win, 0x17);
            BattlePutTextOnWindow(gText_Loss, 0x16);
        }
        else
        {
            BattlePutTextOnWindow(gText_Win, 0x16);
            BattlePutTextOnWindow(gText_Loss, 0x17);
        }
    }
    else
    {
        if (gLinkPlayers[gBattleStruct->multiplayerId].id != 0)
        {
            BattlePutTextOnWindow(gText_Win, 0x16);
            BattlePutTextOnWindow(gText_Loss, 0x17);
        }
        else
        {
            BattlePutTextOnWindow(gText_Win, 0x17);
            BattlePutTextOnWindow(gText_Loss, 0x16);
        }
    }
}

void InitLinkBattleVsScreen(u8 taskId)
{
    struct LinkPlayer *linkPlayer;
    u8 *name;
    s32 i, palId;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            for (i = 0; i < MAX_BATTLERS_COUNT; i++)
            {
                name = gLinkPlayers[i].name;
                linkPlayer = &gLinkPlayers[i];

                switch (linkPlayer->id)
                {
                case 0:
                    BattlePutTextOnWindow(name, 0x11);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 1, 2, 4);
                    break;
                case 1:
                    BattlePutTextOnWindow(name, 0x12);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 2, 2, 4);
                    break;
                case 2:
                    BattlePutTextOnWindow(name, 0x13);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 1, 2, 8);
                    break;
                case 3:
                    BattlePutTextOnWindow(name, 0x14);
                    DrawLinkBattleParticipantPokeballs(taskId, linkPlayer->id, 2, 2, 8);
                    break;
                }
            }
        }
        else
        {
            u8 playerId = gBattleStruct->multiplayerId;
            u8 opponentId = playerId ^ BIT_SIDE;
            u8 opponentId_copy = opponentId;

            if (gLinkPlayers[playerId].id != 0)
                opponentId = playerId, playerId = opponentId_copy;

            name = gLinkPlayers[playerId].name;
            BattlePutTextOnWindow(name, 0xF);

            name = gLinkPlayers[opponentId].name;
            BattlePutTextOnWindow(name, 0x10);

            DrawLinkBattleParticipantPokeballs(taskId, playerId, 1, 2, 7);
            DrawLinkBattleParticipantPokeballs(taskId, opponentId, 2, 2, 7);
        }
        gTasks[taskId].data[0]++;
        break;
    case 1:
        palId = AllocSpritePalette(TAG_VS_LETTERS);
        gPlttBufferUnfaded[palId * 16 + 0x10F] = gPlttBufferFaded[palId * 16 + 0x10F] = RGB(31, 31, 31);
        gBattleStruct->linkBattleVsSpriteId_V = CreateSprite(&sVsLetter_V_SpriteTemplate, 108, 80, 0);
        gBattleStruct->linkBattleVsSpriteId_S = CreateSprite(&sVsLetter_S_SpriteTemplate, 132, 80, 0);
        gSprites[gBattleStruct->linkBattleVsSpriteId_V].invisible = TRUE;
        gSprites[gBattleStruct->linkBattleVsSpriteId_S].invisible = TRUE;
        gTasks[taskId].data[0]++;
        break;
    case 2:
        if (gTasks[taskId].data[5] != 0)
        {
            gBattle_BG1_X = -(20) - (Sin2(gTasks[taskId].data[1]) / 32);
            gBattle_BG2_X = -(140) - (Sin2(gTasks[taskId].data[2]) / 32);
            gBattle_BG1_Y = -36;
            gBattle_BG2_Y = -36;
        }
        else
        {
            gBattle_BG1_X = -(20) - (Sin2(gTasks[taskId].data[1]) / 32);
            gBattle_BG1_Y = (Cos2(gTasks[taskId].data[1]) / 32) - 164;
            gBattle_BG2_X = -(140) - (Sin2(gTasks[taskId].data[2]) / 32);
            gBattle_BG2_Y = (Cos2(gTasks[taskId].data[2]) / 32) - 164;
        }

        if (gTasks[taskId].data[2] != 0)
        {
            gTasks[taskId].data[2] -= 2;
            gTasks[taskId].data[1] += 2;
        }
        else
        {
            if (gTasks[taskId].data[5] != 0)
                DrawLinkBattleVsScreenOutcomeText();

            PlaySE(SE_M_HARDEN);
            DestroyTask(taskId);
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].invisible = FALSE;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].invisible = FALSE;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].oam.tileNum += 0x40;
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].data[0] = 0;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].data[0] = 1;
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].data[1] = gSprites[gBattleStruct->linkBattleVsSpriteId_V].x;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].data[1] = gSprites[gBattleStruct->linkBattleVsSpriteId_S].x;
            gSprites[gBattleStruct->linkBattleVsSpriteId_V].data[2] = 0;
            gSprites[gBattleStruct->linkBattleVsSpriteId_S].data[2] = 0;
        }
        break;
    }
}

void DrawBattleEntryBackground(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        LZDecompressVram(gFile_graphics_battle_transitions_vs_frame_sheet, (void*)(BG_CHAR_ADDR(1)));
        LZDecompressVram(gVsLettersGfx, (void*)(VRAM + 0x10000));
        LoadPalette(gFile_graphics_battle_transitions_vs_frame_palette, 0x60, 0x20);
        SetBgAttribute(1, BG_ATTR_SCREENSIZE, 1);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(0) | BGCNT_CHARBASE(1) | BGCNT_16COLOR | BGCNT_SCREENBASE(28) | BGCNT_TXT512x256);
        CopyToBgTilemapBuffer(1, gFile_graphics_battle_transitions_vs_frame_tilemap, 0, 0);
        CopyToBgTilemapBuffer(2, gFile_graphics_battle_transitions_vs_frame_tilemap, 0, 0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        gBattle_BG1_Y = -164;
        gBattle_BG2_Y = -164;
        LoadCompressedSpriteSheetUsingHeap(&sVsLettersSpriteSheet);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_GRASS);
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_LINK | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER))
    {
        LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_BUILDING);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_GROUDON)
    {

        LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_CAVE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_KYOGRE)
    {

        LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_WATER);
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            u8 trainerClass = gTrainers[gTrainerBattleOpponent_A].trainerClass;
            if (trainerClass == CLASS_GYM_LEADER_FRLG)
            {
                LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_BUILDING);
                return;
            }
            else if (trainerClass == CLASS_CHAMPION_FRLG)
            {
                LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_BUILDING);
                return;
            }
        }

        if (GetCurrentMapBattleScene() == MAP_BATTLE_SCENE_NORMAL)
        {
            LoadBattleTerrainEntryGfx(gBattleEnvironment);
        }
        else
        {
            LoadBattleTerrainEntryGfx(BATTLE_ENVIRONMENT_BUILDING);
        }
    }
}

static u8 GetBattleEnvironmentOverride(void)
{
    u8 battleScene;
    if (gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_LINK | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER))
    {
        return BATTLE_ENVIRONMENT_LINK;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        gBattleEnvironment = BATTLE_ENVIRONMENT_GRASS;
        return BATTLE_ENVIRONMENT_GRASS;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        if (gTrainers[gTrainerBattleOpponent_A].trainerClass == CLASS_GYM_LEADER_FRLG)
        {
            return BATTLE_ENVIRONMENT_LEADER;
        }
        else if (gTrainers[gTrainerBattleOpponent_A].trainerClass == CLASS_CHAMPION_FRLG)
        {
            return BATTLE_ENVIRONMENT_CHAMPION;
        }
    }
    battleScene = GetCurrentMapBattleScene();
    if (battleScene == MAP_BATTLE_SCENE_NORMAL)
    {
        return gBattleEnvironment;
    }
    return GetBattleEnvironmentByMapScene(battleScene);
}

////gBattleEnvironmentInfo[battleEnvironment].background.tilemap
bool8 LoadChosenBattleElement(u8 caseId)
{
    const void *tilemap;
    bool8 ret = FALSE;
    u8 battleScene;
    
    switch (caseId)
    {
    case 0:
        LZDecompressVram(gBattleInterface_Textbox_Gfx, (void *)BG_CHAR_ADDR(0));
        break;
    case 1:
        CopyToBgTilemapBuffer(0, gBattleInterface_Textbox_Tilemap, 0, 0x000);
        CopyBgTilemapBufferToVram(0);
        break;
    case 2:
        LoadPalette(gBattleInterface_Textbox_Pal, 0x00, 0x40);
        break;
    case 3:
        battleScene = GetBattleEnvironmentOverride();
        LZDecompressVram(gBattleEnvironmentInfo[battleScene].background.tileset, (void *)BG_CHAR_ADDR(2));
        // fallthrough
    case 4:
        battleScene = GetBattleEnvironmentOverride();
        if (!IsDoubleBattle())
            tilemap = gBattleEnvironmentInfo[battleScene].background.tilemap;
        else
            tilemap = gBattleEnvironmentInfo[battleScene].background.tilemap2;
        LZDecompressVram(tilemap, (void *)BG_SCREEN_ADDR(26));
        break;
    case 5:
        battleScene = GetBattleEnvironmentOverride();
        LoadPalette(gBattleEnvironmentInfo[battleScene].background.palette, 0x20, 0x60);
        break;
    case 6:
        LoadBattleMenuWindowGfx();
        break;
    default:
        ret = TRUE;
        break;
    }
    return ret;
}

void DrawTerrainTypeBattleBackground(void)
{
    switch (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY)
    {
    case STATUS_FIELD_GRASSY_TERRAIN:
        LoadMoveBg(BG_GRASSY_TERRAIN);
        break;
    case STATUS_FIELD_MISTY_TERRAIN:
        LoadMoveBg(BG_MISTY_TERRAIN);
        break;
    case STATUS_FIELD_ELECTRIC_TERRAIN:
        LoadMoveBg(BG_ELECTRIC_TERRAIN);
        break;
    case STATUS_FIELD_PSYCHIC_TERRAIN:
        LoadMoveBg(BG_PSYCHIC_TERRAIN);
        break;
    default:
        DrawMainBattleBackground();
        break;
    }
}