#include "global.h"
#include "gflib.h"
#include "m4a.h"
#include "task.h"
#include "graphics.h"
#include "decompress.h"
#include "palette.h"
#include "sprite.h"
#include "data.h"
#include "util.h"
#include "party_menu.h"
#include "menu.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_anim.h"
#include "battle_interface.h"
#include "constants/battle_anim.h"
#include "constants/moves.h"
#include "constants/songs.h"

static bool8 ShouldAnimBeDoneRegardlessOfSubsitute(u8 animId);
static void Task_ClearBitWhenBattleTableAnimDone(u8 taskId);
static void Task_ClearBitWhenSpecialAnimDone(u8 taskId);
static void ClearSpritesBattlerHealthboxAnimData(void);

static const struct CompressedSpriteSheet sSpriteSheet_SinglesPlayerHealthbox =
{
    .data = gHealthboxSinglesPlayerGfx,
    .size = 0x1000,
    .tag = TAG_HEALTHBOX_PLAYER1_TILE,
};

static const struct CompressedSpriteSheet sSpriteSheet_SinglesOpponentHealthbox =
{
    .data = gHealthboxSinglesOpponentGfx,
    .size = 0x1000,
    .tag = TAG_HEALTHBOX_OPPONENT1_TILE,
};

static const struct CompressedSpriteSheet sSpriteSheets_DoublesPlayerHealthbox[2] =
{
    {
        .data = gHealthboxDoublesPlayerGfx,
        .size = 0x800,
        .tag = TAG_HEALTHBOX_PLAYER1_TILE,
    },
    {
        .data = gHealthboxDoublesPlayerGfx,
        .size = 0x800,
        .tag = TAG_HEALTHBOX_PLAYER2_TILE,
    },
};

static const struct CompressedSpriteSheet sSpriteSheets_DoublesOpponentHealthbox[2] =
{
    {
        .data = gHealthboxDoublesOpponentGfx,
        .size = 0x800,
        .tag = TAG_HEALTHBOX_OPPONENT1_TILE,
    },
    {
        .data = gHealthboxDoublesOpponentGfx,
        .size = 0x800,
        .tag = TAG_HEALTHBOX_OPPONENT2_TILE,
    },
};

static const struct CompressedSpriteSheet sSpriteSheet_SafariHealthbox =
{
    .data = gHealthboxSafariGfx,
    .size = 0x1000,
    .tag = TAG_HEALTHBOX_SAFARI_TILE,
};

static const struct CompressedSpriteSheet sSpriteSheets_HealthBar[MAX_BATTLERS_COUNT] =
{
    {
        .data = gBlankGfxCompressed,
        .size = 0x100,
        .tag = TAG_HEALTHBAR_PLAYER1_TILE,
    },
    {
        .data = gBlankGfxCompressed,
        .size = 0x120,
        .tag = TAG_HEALTHBAR_OPPONENT1_TILE,
    },
    {
        .data = gBlankGfxCompressed,
        .size = 0x100,
        .tag = TAG_HEALTHBAR_PLAYER2_TILE,
    },
    {
        .data = gBlankGfxCompressed,
        .size = 0x120,
        .tag = TAG_HEALTHBAR_OPPONENT2_TILE,
    },
};

const struct SpritePalette sSpritePalettes_HealthBoxHealthBar[2] =
{
    {
        .data = gBattleInterface_Healthbox_Pal,
        .tag = TAG_HEALTHBOX_PAL,
    },
    {
        .data = gBattleInterface_Healthbar_Pal,
        .tag = TAG_HEALTHBAR_PAL,
    },
};

void AllocateBattleSpritesData(void)
{
    gBattleSpritesDataPtr = AllocZeroed(sizeof(struct BattleSpriteData));
    gBattleSpritesDataPtr->battlerData = AllocZeroed(sizeof(struct BattleSpriteInfo) * MAX_BATTLERS_COUNT);
    gBattleSpritesDataPtr->healthBoxesData = AllocZeroed(sizeof(struct BattleHealthboxInfo) * MAX_BATTLERS_COUNT);
    gBattleSpritesDataPtr->animationData = AllocZeroed(sizeof(struct BattleAnimationInfo));
    gBattleSpritesDataPtr->battleBars = AllocZeroed(sizeof(struct BattleBarInfo) * MAX_BATTLERS_COUNT);
}

void FreeBattleSpritesData(void)
{
    if (gBattleSpritesDataPtr)
    {
        FREE_AND_SET_NULL(gBattleSpritesDataPtr->battleBars);
        FREE_AND_SET_NULL(gBattleSpritesDataPtr->animationData);
        FREE_AND_SET_NULL(gBattleSpritesDataPtr->healthBoxesData);
        FREE_AND_SET_NULL(gBattleSpritesDataPtr->battlerData);
        FREE_AND_SET_NULL(gBattleSpritesDataPtr);
    }
}

void SpriteCB_WaitForBattlerBallReleaseAnim(struct Sprite *sprite)
{
    u8 spriteId = sprite->data[1];

    if (!gSprites[spriteId].affineAnimEnded)
        return;
    if (gSprites[spriteId].invisible)
        return;
    if (gSprites[spriteId].animPaused)
        gSprites[spriteId].animPaused = 0;
    else if (gSprites[spriteId].animEnded)
    {
        gSprites[spriteId].callback = SpriteCB_SetToDummy3;
        StartSpriteAffineAnim(&gSprites[spriteId], 0);
        sprite->callback = SpriteCallbackDummy;
    }
}

// not used
UNUSED static void UnusedDoBattleSpriteAffineAnim(struct Sprite *sprite, bool8 arg1)
{
    sprite->animPaused = 1;
    sprite->callback = SpriteCallbackDummy;
    if (!arg1)
        StartSpriteAffineAnim(sprite, 1);
    else
        StartSpriteAffineAnim(sprite, 1);
    AnimateSprite(sprite);
}

void SpriteCB_TrainerSlideIn(struct Sprite *sprite)
{
    if (!(gIntroSlideFlags & 1))
    {
        sprite->x2 += sprite->data[0];
        if (sprite->x2 == 0)
            sprite->callback = SpriteCallbackDummy;
    }
}

#define LOWHP_MUSIC_FUNCTION
void HandleLowHpMusicChange(struct Pokemon *mon, u8 battlerId)
{
    u16 hp = GetMonData(mon, MON_DATA_HP);
    u16 maxHP = GetMonData(mon, MON_DATA_MAX_HP);

    if (GetHPBarLevel(hp, maxHP) == HP_BAR_RED)
    {
        if (!gBattleSpritesDataPtr->battlerData[battlerId].lowHpSong)
        {
            if (!gBattleSpritesDataPtr->battlerData[battlerId ^ BIT_FLANK].lowHpSong)
                PlaySE(SE_LOW_HEALTH);
            gBattleSpritesDataPtr->battlerData[battlerId].lowHpSong = 1;
        }
    }
    else
    {
        gBattleSpritesDataPtr->battlerData[battlerId].lowHpSong = 0;
        if (!IsDoubleBattle())
            m4aSongNumStop(SE_LOW_HEALTH);
        else if (IsDoubleBattle() && !gBattleSpritesDataPtr->battlerData[battlerId ^ BIT_FLANK].lowHpSong)
            m4aSongNumStop(SE_LOW_HEALTH);
    }
}

void BattleStopLowHpSound(void)
{
    u8 playerBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);

    gBattleSpritesDataPtr->battlerData[playerBattler].lowHpSong = 0;
    if (IsDoubleBattle())
        gBattleSpritesDataPtr->battlerData[playerBattler ^ BIT_FLANK].lowHpSong = 0;
    m4aSongNumStop(SE_LOW_HEALTH);
}

void HandleBattleLowHpMusicChange(void)
{
    if (gMain.inBattle)
    {
        u8 playerBattler1 = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        u8 playerBattler2 = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        u8 battler1PartyId = GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[playerBattler1]);
        u8 battler2PartyId = GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[playerBattler2]);

        if (GetMonData(&gPlayerParty[battler1PartyId], MON_DATA_HP) != 0)
            HandleLowHpMusicChange(&gPlayerParty[battler1PartyId], playerBattler1);
        if (IsDoubleBattle() && GetMonData(&gPlayerParty[battler2PartyId], MON_DATA_HP) != 0)
            HandleLowHpMusicChange(&gPlayerParty[battler2PartyId], playerBattler2);
    }
}

void DecompressGhostFrontPic(struct Pokemon *unused, u8 battlerId)
{
    u32 palOffset;
    u8 position = GetBattlerPosition(battlerId);

    LZ77UnCompWram(gGhostFrontPic, gMonSpritesGfxPtr->spritesGfx[position]);
    palOffset = OBJ_PLTT_ID(battlerId);
    LoadPalette(gGhostPalette, palOffset, PLTT_SIZE_4BPP);
    LoadPalette(gGhostPalette, BG_PLTT_ID(8) + BG_PLTT_ID(battlerId), PLTT_SIZE_4BPP);
}


//will need to change to task based work
//check if battler has status1  status2 then status4
//check if (status1) increment through each status 1 to see if htey have that status flag and do animaiton if so
//then do case checks for status2 do same thing, 
//followed by check for status 4 then switch for status4 that increments through each status4, playing animation and doing effects if present
//source chosenstatusanimation command
//rework change isstatus2 to statusCategory  rather than bool, 
//have values 1-4 for the status types, 
//problem rn is use of & w effect need change to equal
//but that alone could cause unintended overlap, so set status cat
//then do equal, w that can properly filter



/*Explanation from Sbird
they do 2 fundamentally different things. a == b as a condition means literally a is equal to b, a & b as a condition means "the result of a logical and b is not equal to 0", or in other words every bit in b is high in a.
as to why that works, status 1 can probably never overlap, i.e. a pokemon cannot be frozen and paralyzed at the same time
*/

//my understanding there's no functional difference between using them,
//far as recognizing the status itself, only in whether it can oveerlap/hold more than one status,
//so for now change all to and, so its ready, if I decide to do multi status

void InitAndLaunchChosenStatusAnimation(u32 battler, bool32 isVolatile, u32 status)
{
    gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive = 1;
    if (!isVolatile)
    {
        if (status == STATUS1_FREEZE)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_FRZ);
        else if (status == STATUS1_FROSTBITE)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_FRB);
        else if (status == STATUS1_POISON || status == STATUS1_TOXIC_POISON) //EE uses status & STATUS1_TOXIC_POISON
            LaunchStatusAnimation(battler, B_ANIM_STATUS_PSN);
        else if (status == STATUS1_BURN)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_BRN);
        else if (status == STATUS1_SLEEP)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_SLP);
        else if (status == STATUS1_PARALYSIS)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_PRZ);
        else // no animation
            gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive = 0;
    }
    else
    {
        if (status == VOLATILE_INFATUATION)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_INFATUATION);
        else if (status == VOLATILE_CONFUSION)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_CONFUSION);
        else if (status == VOLATILE_CURSED)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_CURSED);
        else if (status == VOLATILE_NIGHTMARE)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_NIGHTMARE);
        else if (status == VOLATILE_INFESTATION)
            LaunchStatusAnimation(battler, B_ANIM_STATUS_INFESTED);
        //else if (status == STATUS2_WRAPPED)
        //    LaunchStatusAnimation(battler, B_ANIM_STATUS_WRAPPED); // this animation doesn't actually exist
        else // no animation
            gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive = 0;
    }
    

}

#define tBattlerId data[0]

bool8 TryHandleLaunchBattleTableAnimation(u8 activeBattler, u8 atkBattler, u8 defBattler, u8 tableId, u16 argument)
{
    u8 taskId;

    if (tableId == B_ANIM_CASTFORM_CHANGE && (argument & 0x80))
    {
        gBattleMonForms[activeBattler] = (argument & ~(0x80));
        return TRUE;
    }
    else if (gBattleSpritesDataPtr->battlerData[activeBattler].behindSubstitute
          && !ShouldAnimBeDoneRegardlessOfSubsitute(tableId))
    {
        return TRUE;
    }
    else if (gBattleSpritesDataPtr->battlerData[activeBattler].behindSubstitute
          && tableId == B_ANIM_SUBSTITUTE_FADE
          && gSprites[gBattlerSpriteIds[activeBattler]].invisible)
    {
        LoadBattleMonGfxAndAnimate(activeBattler, TRUE, gBattlerSpriteIds[activeBattler]);
        ClearBehindSubstituteBit(activeBattler);
        return TRUE;
    }
    gBattleAnimAttacker = atkBattler;
    gBattleAnimTarget = defBattler;
    gBattleSpritesDataPtr->animationData->animArg = argument;
    LaunchBattleAnimation(ANIM_TYPE_GENERAL, tableId);
    taskId = CreateTask(Task_ClearBitWhenBattleTableAnimDone, 10);
    gTasks[taskId].tBattlerId = activeBattler;
    gBattleSpritesDataPtr->healthBoxesData[gTasks[taskId].tBattlerId].animFromTableActive = 1;
    return FALSE;
}

static void Task_ClearBitWhenBattleTableAnimDone(u8 taskId)
{
    gAnimScriptCallback();
    if (!gAnimScriptActive)
    {
        gBattleSpritesDataPtr->healthBoxesData[gTasks[taskId].tBattlerId].animFromTableActive = 0;
        DestroyTask(taskId);
    }
}

static bool8 ShouldAnimBeDoneRegardlessOfSubsitute(u8 animId)
{
    switch (animId)
    {
    case B_ANIM_SUBSTITUTE_FADE:
    case B_ANIM_RAIN_CONTINUES:
    case B_ANIM_ACID_RAIN_CONTINUES:
    case B_ANIM_MOONLIGHT_SHINES:
    case B_ANIM_SUN_CONTINUES:
    case B_ANIM_SANDSTORM_CONTINUES:
    case B_ANIM_HAIL_CONTINUES:
    case B_ANIM_SNOW_CONTINUES:
    case B_ANIM_FOG_CONTINUES:
    case B_ANIM_SNATCH_MOVE:
        return TRUE;
    default:
        return FALSE;
    }
}

void InitAndLaunchSpecialAnimation(u8 activeBattler, u8 atkBattler, u8 defBattler, u8 tableId)
{
    u8 taskId;

    gBattleAnimAttacker = atkBattler;
    gBattleAnimTarget = defBattler;
    LaunchBattleAnimation(ANIM_TYPE_SPECIAL, tableId);
    taskId = CreateTask(Task_ClearBitWhenSpecialAnimDone, 10);
    gTasks[taskId].tBattlerId = activeBattler;
    gBattleSpritesDataPtr->healthBoxesData[gTasks[taskId].tBattlerId].specialAnimActive = 1;
}

static void Task_ClearBitWhenSpecialAnimDone(u8 taskId)
{
    gAnimScriptCallback();
    if (!gAnimScriptActive)
    {
        gBattleSpritesDataPtr->healthBoxesData[gTasks[taskId].tBattlerId].specialAnimActive = 0;
        DestroyTask(taskId);
    }
}

bool8 IsMoveWithoutAnimation(u16 moveId, u8 animationTurn)
{
    return FALSE;
}

bool8 IsBattleSEPlaying(u8 battlerId)
{
    u8 zero = 0;

    if (IsSEPlaying())
    {
        ++gBattleSpritesDataPtr->healthBoxesData[battlerId].soundTimer;
        if (gBattleSpritesDataPtr->healthBoxesData[battlerId].soundTimer < 30)
            return TRUE;
        m4aMPlayStop(&gMPlayInfo_SE1);
        m4aMPlayStop(&gMPlayInfo_SE2);
    }
    if (zero == 0)
    {
        gBattleSpritesDataPtr->healthBoxesData[battlerId].soundTimer = 0;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void BattleLoadMonSpriteGfx(struct Pokemon *mon, u32 battler)
{
    u32 monsPersonality, currentPersonality, paletteOffset;
    u16 species;
    u8 position;
    const u16 *paletteData;
    bool32 isShiny;
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    if (illusionMon != NULL)
        mon = illusionMon;

    monsPersonality = GetMonData(mon, MON_DATA_PERSONALITY);
    if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies == SPECIES_NONE)
    {
        species = GetMonData(mon, MON_DATA_SPECIES);
        currentPersonality = monsPersonality;
    }
    else
    {
        //need party of targetmon
        species = gBattleSpritesDataPtr->battlerData[battler].transformSpecies;
        currentPersonality = GetMonData(GetBattlerMon(gBattlerTarget), MON_DATA_PERSONALITY);
        isShiny = IsMonShiny(GetBattlerMon(gBattlerTarget));
    }
    position = GetBattlerPosition(battler);
    HandleLoadSpecialPokePic_DontHandleDeoxys(!IsOnPlayerSide(battler),
                                              gMonSpritesGfxPtr->spritesGfx[position],
                                              species, currentPersonality);
    paletteOffset = OBJ_PLTT_ID(battler);
    
    //ok made this new value and replaced ability check as 
    //transform changes ability  works
    if (gBattleMons[battler].volatiles.inversionTransformed)
    {
        isShiny = IsMonShiny(mon);
        currentPersonality = monsPersonality;
    }
    
    if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies == SPECIES_NONE)
        paletteData = GetMonSpritePal(mon);
    else
        paletteData = GetMonSpritePalFromSpeciesAndPersonality(species, isShiny, currentPersonality);
    
    LoadPalette(paletteData, paletteOffset, PLTT_SIZE_4BPP);
    LoadPalette(paletteData, BG_PLTT_ID(8) + BG_PLTT_ID(battler), PLTT_SIZE_4BPP);


    // transform's pink color
    if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies != SPECIES_NONE)
    {
        BlendPalette(paletteOffset, 16, 6, RGB_WHITE);
        CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
    }
}

void DecompressTrainerFrontPic(u16 frontPicId, u8 battlerId)
{
    struct SpriteSheet sheet;
    u8 position = GetBattlerPosition(battlerId);

    DecompressPicFromTable(&gTrainerFrontPicTable[frontPicId], gMonSpritesGfxPtr->spritesGfx[position], SPECIES_NONE);
    sheet.data = gMonSpritesGfxPtr->spritesGfx[position];
    sheet.size = gTrainerFrontPicTable[frontPicId].size;
    sheet.tag = gTrainerFrontPicTable[frontPicId].tag;
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&gTrainerFrontPicPaletteTable[frontPicId]);
}

void DecompressTrainerBackPalette(u16 index, u8 palette)
{
    LoadPalette(gTrainerBackPicPaletteTable[index].data, (palette + 16) * 16, 0x20);
}

void BattleGfxSfxDummy3(u8 a1)
{
}

void FreeTrainerFrontPicPaletteAndTile(u16 frontPicId)
{
    FreeSpritePaletteByTag(gTrainerFrontPicPaletteTable[frontPicId].tag);
    FreeSpriteTilesByTag(gTrainerFrontPicTable[frontPicId].tag);
}

// Unused.
void BattleLoadAllHealthBoxesGfxAtOnce(void)
{
    u8 numberOfBattlers = 0;
    u8 i;

    LoadSpritePalette(&sSpritePalettes_HealthBoxHealthBar[0]);
    LoadSpritePalette(&sSpritePalettes_HealthBoxHealthBar[1]);
    if (!IsDoubleBattle())
    {
        LoadCompressedSpriteSheet(&sSpriteSheet_SinglesPlayerHealthbox);
        LoadCompressedSpriteSheet(&sSpriteSheet_SinglesOpponentHealthbox);
        numberOfBattlers = 2;
    }
    else
    {
        LoadCompressedSpriteSheet(&sSpriteSheets_DoublesPlayerHealthbox[0]);
        LoadCompressedSpriteSheet(&sSpriteSheets_DoublesPlayerHealthbox[1]);
        LoadCompressedSpriteSheet(&sSpriteSheets_DoublesOpponentHealthbox[0]);
        LoadCompressedSpriteSheet(&sSpriteSheets_DoublesOpponentHealthbox[1]);
        numberOfBattlers = MAX_BATTLERS_COUNT;
    }
    for (i = 0; i < numberOfBattlers; i++)
        LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(i)]);
}

bool8 BattleLoadAllHealthBoxesGfx(u8 state)
{
    bool8 retVal = FALSE;

    if (state != 0)
    {
        if (state == 1)
        {
            LoadSpritePalette(&sSpritePalettes_HealthBoxHealthBar[0]);
            LoadSpritePalette(&sSpritePalettes_HealthBoxHealthBar[1]);
            LoadIndicatorSpritesGfx();
            CategoryIcons_LoadSpritesGfx();
        }
        else if (!IsDoubleBattle())
        {
            if (state == 2)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
                    LoadCompressedSpriteSheet(&sSpriteSheet_SafariHealthbox);
                else
                    LoadCompressedSpriteSheet(&sSpriteSheet_SinglesPlayerHealthbox);
            }
            else if (state == 3)
            {
                LoadCompressedSpriteSheet(&sSpriteSheet_SinglesOpponentHealthbox);
            }
            else if (state == 4)
            {
                LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(B_BATTLER_0)]);
            }
            else if (state == 5)
            {
                LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(B_BATTLER_1)]);
            }
            else
            {
                retVal = TRUE;
            }
        }
        else
        {
            if (state == 2)
            {
                switch (GetBattlerCoordsIndex(B_POSITION_PLAYER_LEFT))
                {
                default:
                    LoadCompressedSpriteSheet(&sSpriteSheets_DoublesPlayerHealthbox[0]);
                    break;
                case BATTLE_COORDS_SINGLES:
                    LoadCompressedSpriteSheet(&sSpriteSheet_SinglesPlayerHealthbox);
                    break;
                }
            }
            else if (state == 3)
                LoadCompressedSpriteSheet(&sSpriteSheets_DoublesPlayerHealthbox[1]);
            else if (state == 4)
                LoadCompressedSpriteSheet(&sSpriteSheets_DoublesOpponentHealthbox[0]);
            else if (state == 5)
                LoadCompressedSpriteSheet(&sSpriteSheets_DoublesOpponentHealthbox[1]);
            else if (state == 6)
                LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(B_BATTLER_0)]);
            else if (state == 7)
                LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(B_BATTLER_1)]);
            else if (state == 8)
                LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(B_BATTLER_2)]);
            else if (state == 9)
                LoadCompressedSpriteSheet(&sSpriteSheets_HealthBar[GetBattlerPosition(B_BATTLER_3)]);
            else
                retVal = TRUE;
        }
    }

    return retVal;
}

void LoadBattleBarGfx(u8 unused)
{
    LZDecompressWram(gBattleInterfaceGfx_BattleBar, gMonSpritesGfxPtr->barFontGfx);
}

bool8 BattleInitAllSprites(u8 *state1, u8 *battler)
{
    bool8 retVal = FALSE;

    switch (*state1)
    {
    case 0:
        ClearSpritesBattlerHealthboxAnimData();
        (*state1)++;
        break;
    case 1:
        if (!BattleLoadAllHealthBoxesGfx(*battler))
        {
            (*battler)++;
        }
        else
        {
            *battler = 0;
            (*state1)++;
        }
        break;
    case 2:
        (*state1)++;
        break;
    case 3:
        if ((gBattleTypeFlags & BATTLE_TYPE_SAFARI) && *battler == 0)
            gHealthboxSpriteIds[*battler] = CreateSafariPlayerHealthboxSprites();
        else
            gHealthboxSpriteIds[*battler] = CreateBattlerHealthboxSprites(*battler);

        (*battler)++;
        if (*battler == gBattlersCount)
        {
            *battler = 0;
            (*state1)++;
        }
        break;
    case 4:
        InitBattlerHealthboxCoords(*battler);
        if (GetBattlerPosition(*battler) <= B_POSITION_OPPONENT_LEFT)
            DummyBattleInterfaceFunc(gHealthboxSpriteIds[*battler], FALSE);
        else
            DummyBattleInterfaceFunc(gHealthboxSpriteIds[*battler], TRUE);

        (*battler)++;
        if (*battler == gBattlersCount)
        {
            *battler = 0;
            (*state1)++;
        }
        break;
    case 5:
        if (!IsOnPlayerSide(*battler) || !(gBattleTypeFlags & BATTLE_TYPE_SAFARI))
            UpdateHealthboxAttribute(gHealthboxSpriteIds[*battler], GetBattlerMon(*battler), HEALTHBOX_ALL);
        SetHealthboxSpriteInvisible(gHealthboxSpriteIds[*battler]);
        (*battler)++;
        if (*battler == gBattlersCount)
        {
            *battler = 0;
            (*state1)++;
        }
        break;
    case 6:
        LoadAndCreateEnemyShadowSprites();
        BufferBattlePartyCurrentOrder();
        retVal = TRUE;
        break;
    }

    return retVal;
}

void ClearSpritesHealthboxAnimData(void)
{
    memset(gBattleSpritesDataPtr->healthBoxesData, 0, sizeof(struct BattleHealthboxInfo) * MAX_BATTLERS_COUNT);
    memset(gBattleSpritesDataPtr->animationData, 0, sizeof(struct BattleAnimationInfo));
}

static void ClearSpritesBattlerHealthboxAnimData(void)
{
    ClearSpritesHealthboxAnimData();
    memset(gBattleSpritesDataPtr->battlerData, 0, sizeof(struct BattleSpriteInfo) * MAX_BATTLERS_COUNT);
}

void CopyAllBattleSpritesInvisibilities(void)
{
    s32 i;

    for (i = 0; i < gBattlersCount; i++)
        gBattleSpritesDataPtr->battlerData[i].invisible = gSprites[gBattlerSpriteIds[i]].invisible;
}

void CopyBattleSpriteInvisibility(u8 battler)
{
    gBattleSpritesDataPtr->battlerData[battler].invisible = gSprites[gBattlerSpriteIds[battler]].invisible;
}

void HandleSpeciesGfxDataChange(u8 battlerAtk, u8 battlerDef, u8 notTransform)
{
    u16 targetSpecies;
    u32 personalityValue, paletteOffset;
    u8 position;
    const u16 *paletteData;
    bool32 isShiny;
    struct Pokemon PartyMon;

    //TODO: notTransform is bool8 in pokeem. Document it with a more reasonable name here. 
    if (notTransform == 255)
    {
        const void *src;
        void *dst;
        
        position = GetBattlerPosition(battlerAtk);
        targetSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerAtk]], MON_DATA_SPECIES);
        personalityValue = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerAtk]], MON_DATA_PERSONALITY);
        HandleLoadSpecialPokePic_DontHandleDeoxys(TRUE,
                                                  gMonSpritesGfxPtr->spritesGfx[position],
                                                  targetSpecies,
                                                  personalityValue);
        src = gMonSpritesGfxPtr->spritesGfx[position];
        dst = (void *)(VRAM + 0x10000 + gSprites[gBattlerSpriteIds[battlerAtk]].oam.tileNum * 32);
        DmaCopy32(3, src, dst, 0x800);
        paletteOffset = OBJ_PLTT_ID(battlerAtk);
        isShiny = IsMonShiny(&gEnemyParty[gBattlerPartyIndexes[battlerAtk]]);
        paletteData = GetMonSpritePalFromSpeciesAndPersonality(targetSpecies, isShiny, personalityValue);
        LoadPalette(paletteData, paletteOffset, PLTT_SIZE_4BPP);
        gSprites[gBattlerSpriteIds[battlerAtk]].y = GetBattlerSpriteDefault_Y(battlerAtk);
        StartSpriteAnim(&gSprites[gBattlerSpriteIds[battlerAtk]], gBattleMonForms[battlerAtk]);
        SetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerAtk]], MON_DATA_NICKNAME, gBaseStats[targetSpecies].speciesName);
        UpdateNickInHealthbox(gHealthboxSpriteIds[battlerAtk], &gEnemyParty[gBattlerPartyIndexes[battlerAtk]]);
        TryAddPokeballIconToHealthbox(gHealthboxSpriteIds[battlerAtk], 1); 
    }
    /*else if (notTransform) // Castform form change
    {
        StartSpriteAnim(&gSprites[gBattlerSpriteIds[battlerAtk]], gBattleSpritesDataPtr->animationData->animArg);
        paletteOffset = OBJ_PLTT_ID(battlerAtk);
        LoadPalette(gBattleStruct->castformPalette[gBattleSpritesDataPtr->animationData->animArg], paletteOffset, 32);
        gBattleMonForms[battlerAtk] = gBattleSpritesDataPtr->animationData->animArg;
        if (gBattleSpritesDataPtr->battlerData[battlerAtk].transformSpecies != SPECIES_NONE)
        {
            BlendPalette(paletteOffset, 16, 6, RGB_WHITE);
            CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
        }
        gSprites[gBattlerSpriteIds[battlerAtk]].y = GetBattlerSpriteDefault_Y(battlerAtk);
    }*/
    else //only this is transform, only change here
    {
        const void *src;
        void *dst;

        position = GetBattlerPosition(battlerAtk);
        /*if (GetBattlerSide(battlerDef) == B_SIDE_OPPONENT)
            targetSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerDef]], MON_DATA_SPECIES);
        else
            targetSpecies = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerDef]], MON_DATA_SPECIES);
        */
       //value now set in the transform logic from battlecontroller/pokemon
        targetSpecies = gBattleSpritesDataPtr->battlerData[battlerAtk].transformSpecies;
        if (GetBattlerSide(battlerAtk) == B_SIDE_PLAYER)
        {
            personalityValue = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battlerDef]], MON_DATA_PERSONALITY);
            isShiny = IsMonShiny(&gEnemyParty[gBattlerPartyIndexes[battlerDef]]);
            PartyMon = gPlayerParty[gBattlerPartyIndexes[battlerAtk]];
            HandleLoadSpecialPokePic_DontHandleDeoxys(FALSE,
                                                      gMonSpritesGfxPtr->spritesGfx[position],
                                                      targetSpecies,
                                                      personalityValue);
        }
        else
        {
            personalityValue = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerDef]], MON_DATA_PERSONALITY);
            isShiny = IsMonShiny(&gPlayerParty[gBattlerPartyIndexes[battlerDef]]);
            PartyMon = gEnemyParty[gBattlerPartyIndexes[battlerAtk]];
            HandleLoadSpecialPokePic_DontHandleDeoxys(TRUE,
                                                      gMonSpritesGfxPtr->spritesGfx[position],
                                                      targetSpecies,
                                                      personalityValue);
        }
        src = gMonSpritesGfxPtr->spritesGfx[position];
        dst = (void *)(VRAM + 0x10000 + gSprites[gBattlerSpriteIds[battlerAtk]].oam.tileNum * 32);
        DmaCopy32(3, src, dst, 0x800);
        paletteOffset = OBJ_PLTT_ID(battlerAtk);

        //as not transforming into target, should use own shiny value
        if (gBattleMons[battlerAtk].volatiles.inversionTransformed)
        {
            isShiny = IsMonShiny(&PartyMon);
            personalityValue = GetMonData(&PartyMon, MON_DATA_PERSONALITY);
        }
        paletteData = GetMonSpritePalFromSpeciesAndPersonality(targetSpecies, isShiny, personalityValue);
        LoadPalette(paletteData, paletteOffset, 32);

        //since inversion doesn't use target 
        //worried of potential issue w using BattlerDef/battlerId in gbattlemonforms

        BlendPalette(paletteOffset, 16, 6, RGB_WHITE); //pink color transorm blend
        CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
        //gBattleSpritesDataPtr->battlerData[battlerAtk].transformSpecies = targetSpecies;
        gBattleMonForms[battlerAtk] = gBattleMonForms[battlerDef]; //don't know what this is, but is transferring target form to attacker?
        gSprites[gBattlerSpriteIds[battlerAtk]].y = GetBattlerSpriteDefault_Y(battlerAtk);
        StartSpriteAnim(&gSprites[gBattlerSpriteIds[battlerAtk]], gBattleMonForms[battlerAtk]);
    }
}

void BattleLoadSubstituteOrMonSpriteGfx(u8 battler, bool8 loadMonSprite)
{
    s32 i, palOffset;
    enum BattlerPosition position;

    if (!loadMonSprite)
    {
        if (IsContest())
            position = B_POSITION_PLAYER_LEFT;
        else
            position = GetBattlerPosition(battler);

        if (IsContest() || IsOnPlayerSide(battler))//use new graphic
        { 
            LZDecompressVram(gBattleAnimSpriteGfx_SubstituteBack, gMonSpritesGfxPtr->spritesGfx[position]);
            for (i = 1; i < 4; i++)
            {
                Dma3CopyLarge32_(gMonSpritesGfxPtr->spritesGfx[position], &gMonSpritesGfxPtr->spritesGfx[position][MON_PIC_SIZE * i], MON_PIC_SIZE);
            }

            palOffset = OBJ_PLTT_ID(battler);
            LoadPalette(gBattleAnimSpritePal_Substitute, palOffset, PLTT_SIZE_4BPP);
        }
        else if (!IsOnPlayerSide(battler))//use legacy graphic
        {    
            LZDecompressVram(gBattleAnimSpriteGfx_Substitute_Legacy, gMonSpritesGfxPtr->spritesGfx[position]);
            for (i = 1; i < 4; i++)
            {
                Dma3CopyLarge32_(gMonSpritesGfxPtr->spritesGfx[position], &gMonSpritesGfxPtr->spritesGfx[position][MON_PIC_SIZE * i], MON_PIC_SIZE);
            }

            palOffset = OBJ_PLTT_ID(battler);
            LoadPalette(gBattleAnimSpritePal_Substitute_Legacy, palOffset, PLTT_SIZE_4BPP);
        }

    }
    else
    {
        if (!IsContest())
            BattleLoadMonSpriteGfx(GetBattlerMon(battler), battler);
    }
}

void LoadBattleMonGfxAndAnimate(u8 battler, bool8 loadMonSprite, u8 spriteId)
{
    BattleLoadSubstituteOrMonSpriteGfx(battler, loadMonSprite);
    StartSpriteAnim(&gSprites[spriteId], 0);

    if (!loadMonSprite)
        gSprites[spriteId].y = GetSubstituteSpriteDefault_Y(battler);
    else
        gSprites[spriteId].y = GetBattlerSpriteDefault_Y(battler);
}

void TrySetBehindSubstituteSpriteBit(u8 battler, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (effect == EFFECT_SUBSTITUTE || effect == EFFECT_SHED_TAIL)
        gBattleSpritesDataPtr->battlerData[battler].behindSubstitute = 1;
}

void ClearBehindSubstituteBit(u8 battler)
{
    gBattleSpritesDataPtr->battlerData[battler].behindSubstitute = 0;
}

// not used
static u8 GetMonHPBarLevel(struct Pokemon *mon)
{
    u16 hp = GetMonData(mon, MON_DATA_HP);
    u16 maxHP = GetMonData(mon, MON_DATA_MAX_HP);

    return GetHPBarLevel(hp, maxHP);
}

void SetBattlerSpriteAffineMode(u8 affineMode)
{
    s32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerSpritePresent(i))
        {
            gSprites[gBattlerSpriteIds[i]].oam.affineMode = affineMode;
            if (affineMode == ST_OAM_AFFINE_OFF)
            {
                gBattleSpritesDataPtr->healthBoxesData[i].matrixNum = gSprites[gBattlerSpriteIds[i]].oam.matrixNum;
                gSprites[gBattlerSpriteIds[i]].oam.matrixNum = 0;
            }
            else
            {
                gSprites[gBattlerSpriteIds[i]].oam.matrixNum = gBattleSpritesDataPtr->healthBoxesData[i].matrixNum;
            }
        }
    }
}

#define tBattlerId   data[0]
#define tSpriteSide  data[1]
#define tBaseTileNum data[2]

#define SPRITE_SIDE_LEFT    0
#define SPRITE_SIDE_RIGHT   1

void CreateEnemyShadowSprite(u32 battler)
{
    /*if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
    {
        u16 species = GetBattlerVisualSpecies(battler);
        u8 size = gSpeciesInfo[species].enemyShadowSize;

        gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary = CreateSprite(&gSpriteTemplate_EnemyShadow,
                                                                                             GetBattlerSpriteCoord(battler, BATTLER_COORD_X),
                                                                                             GetBattlerSpriteCoord(battler, BATTLER_COORD_Y),
                                                                                             0xC8);
        if (gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary < MAX_SPRITES)
        {
            struct Sprite *sprite = &gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary];
            sprite->tBattlerId = battler;
            sprite->tSpriteSide = SPRITE_SIDE_LEFT;
            sprite->tBaseTileNum = sprite->oam.tileNum;
            sprite->oam.tileNum = sprite->tBaseTileNum + (8 * size);
            sprite->invisible = TRUE;
        }

        gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary = CreateSprite(&gSpriteTemplate_EnemyShadow,
                                                                                               GetBattlerSpriteCoord(battler, BATTLER_COORD_X),
                                                                                               GetBattlerSpriteCoord(battler, BATTLER_COORD_Y),
                                                                                               0xC8);
        if (gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary < MAX_SPRITES)
        {
            struct Sprite *sprite = &gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary];
            sprite->tBattlerId = battler;
            sprite->tSpriteSide = SPRITE_SIDE_RIGHT;
            sprite->tBaseTileNum = sprite->oam.tileNum + 4;
            sprite->oam.tileNum = sprite->tBaseTileNum + (8 * size);
            sprite->invisible = TRUE;
        }
    }
    else*/
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary = CreateSprite(&gSpriteTemplate_EnemyShadow,
                                                                                             GetBattlerSpriteCoord(battler, BATTLER_COORD_X),
                                                                                             GetBattlerSpriteCoord(battler, BATTLER_COORD_Y) + 29,
                                                                                             0xC8);
        if (gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary < MAX_SPRITES)
        {
            struct Sprite *sprite = &gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary];
            sprite->tBattlerId = battler;
            sprite->tBaseTileNum = sprite->oam.tileNum;
            sprite->invisible = TRUE;
        }
    }
}

void LoadAndCreateEnemyShadowSprites(void)
{
    u8 battler;
    u32 i;

    /*if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
    {
        LoadCompressedSpriteSheet(&gSpriteSheet_EnemyShadowsSized);

        // initialize shadow sprite ids
        for (i = 0; i < gBattlersCount; i++)
        {
            gBattleSpritesDataPtr->healthBoxesData[i].shadowSpriteIdPrimary = MAX_SPRITES;
            gBattleSpritesDataPtr->healthBoxesData[i].shadowSpriteIdSecondary = MAX_SPRITES;
        }
    }
    else*/
    {
        LoadCompressedSpriteSheet(&gSpriteSheet_EnemyShadow);

        // initialize shadow sprite ids
        for (i = 0; i < gBattlersCount; i++)
        {
            gBattleSpritesDataPtr->healthBoxesData[i].shadowSpriteIdPrimary = MAX_SPRITES;
        }
    }

    battler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    CreateEnemyShadowSprite(battler);

    if (IsDoubleBattle())
    {
        battler = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        CreateEnemyShadowSprite(battler);
    }
}

static void SpriteCB_EnemyShadow(struct Sprite *shadowSprite)
{
    bool8 invisible = FALSE;
    u8 battlerId = shadowSprite->tBattlerId;
    struct Sprite *battlerSprite = &gSprites[gBattlerSpriteIds[battlerId]];

    if (!battlerSprite->inUse || !IsBattlerSpritePresent(battlerId))
    {
        shadowSprite->callback = SpriteCB_SetInvisible;
        return;
    }
    if (gAnimScriptActive || battlerSprite->invisible)
        invisible = TRUE;
    else if (gBattleSpritesDataPtr->battlerData[battlerId].transformSpecies != SPECIES_NONE
             && gSpeciesGraphics[gBattleSpritesDataPtr->battlerData[battlerId].transformSpecies].enemyMonElevation == 0)
        invisible = TRUE;
    if (gBattleSpritesDataPtr->battlerData[battlerId].behindSubstitute)
        invisible = TRUE;
    shadowSprite->x = battlerSprite->x;
    shadowSprite->x2 = battlerSprite->x2;
    shadowSprite->invisible = invisible;
}

void SpriteCB_SetInvisible(struct Sprite *sprite)
{
    sprite->invisible = TRUE;
}

void SetBattlerShadowSpriteCallback(u8 battler, u16 species)
{
    /*if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
    {
        if (IsOnPlayerSide(battler) || gBattleScripting.monCaught)
        {
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_SetInvisible;
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary].callback = SpriteCB_SetInvisible;
            return;
        }

        if (gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary >= MAX_SPRITES
            || gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary >= MAX_SPRITES)
            return;

        if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies != SPECIES_NONE)
            species = gBattleSpritesDataPtr->battlerData[battler].transformSpecies;

        if (gSpeciesInfo[SanitizeSpeciesId(species)].suppressEnemyShadow == FALSE)
        {
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_EnemyShadow;
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary].callback = SpriteCB_EnemyShadow;
        }
        else
        {
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_SetInvisible;
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary].callback = SpriteCB_SetInvisible;
        }
    }
    else*/
    {
        if (IsOnPlayerSide(battler) || gBattleScripting.monCaught)
        {
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_SetInvisible;
            return;
        }

        if (gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary >= MAX_SPRITES)
            return;

        if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies != SPECIES_NONE)
            species = gBattleSpritesDataPtr->battlerData[battler].transformSpecies;

        if (gSpeciesGraphics[SanitizeSpeciesId(species)].enemyMonElevation != 0)
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_EnemyShadow;
        else
            gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_SetInvisible;
    }
}

void HideBattlerShadowSprite(u8 battler)
{
    gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdPrimary].callback = SpriteCB_SetInvisible;
    /*if (B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE)
        gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].shadowSpriteIdSecondary].callback = SpriteCB_SetInvisible;*/
}

// Low-level function that sets specific interface tiles' palettes,
// overwriting any pixel with value 0.
void BattleInterfaceSetWindowPals(void)
{
    // 9 tiles at 0x06000240
    u16 *vramPtr = (u16 *)(BG_VRAM + 0x240);
    s32 i;
    s32 j;

    for (i = 0; i < 9; ++i)
    {
        for (j = 0; j < 16; ++vramPtr, ++j)
        {
            if (!(*vramPtr & 0xF000))
                *vramPtr |= 0xF000;
            if (!(*vramPtr & 0x0F00))
                *vramPtr |= 0x0F00;
            if (!(*vramPtr & 0x00F0))
                *vramPtr |= 0x00F0;
            if (!(*vramPtr & 0x000F))
                *vramPtr |= 0x000F;
        }
    }

    // 18 tiles at 0x06000600
    vramPtr = (u16 *)(BG_VRAM + 0x600);
    for (i = 0; i < 18; ++i)
    {
        for (j = 0; j < 16; ++vramPtr, ++j)
        {
            if (!(*vramPtr & 0xF000))
                *vramPtr |= 0x6000;
            if (!(*vramPtr & 0x0F00))
                *vramPtr |= 0x0600;
            if (!(*vramPtr & 0x00F0))
                *vramPtr |= 0x0060;
            if (!(*vramPtr & 0x000F))
                *vramPtr |= 0x0006;
        }
    }
}

//vsonic Important, believe may be important to issue of substitute fading before it shuold?
void ClearTemporarySpeciesSpriteData(u8 battlerId, bool8 dontClearSubstitute)
{
    gBattleSpritesDataPtr->battlerData[battlerId].transformSpecies = SPECIES_NONE;
    gBattleMonForms[battlerId] = 0;
    if (!dontClearSubstitute)
        ClearBehindSubstituteBit(battlerId);
}

void AllocateMonSpritesGfx(void)
{
    u8 i = 0, j;

    gMonSpritesGfxPtr = NULL;
    gMonSpritesGfxPtr = AllocZeroed(sizeof(*gMonSpritesGfxPtr));
    gMonSpritesGfxPtr->firstDecompressed = AllocZeroed(MON_PIC_SIZE * 4 * MAX_BATTLERS_COUNT);

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        gMonSpritesGfxPtr->spritesGfx[i] = gMonSpritesGfxPtr->firstDecompressed + (i * MON_PIC_SIZE * 4);
        gMonSpritesGfxPtr->templates[i] = gBattlerSpriteTemplates[i];

        for (j = 0; j < MAX_MON_PIC_FRAMES; j++)
        {
            if (gMonSpritesGfxPtr->spritesGfx[i])
            {
                gMonSpritesGfxPtr->frameImages[i][j].data = gMonSpritesGfxPtr->spritesGfx[i] + (j * MON_PIC_SIZE);
                gMonSpritesGfxPtr->frameImages[i][j].size = MON_PIC_SIZE;
            }
        }

        gMonSpritesGfxPtr->templates[i].images = gMonSpritesGfxPtr->frameImages[i];
    }

    gMonSpritesGfxPtr->barFontGfx = AllocZeroed(0x1000);
}

void FreeMonSpritesGfx(void)
{
    if (gMonSpritesGfxPtr == NULL)
        return;

    TRY_FREE_AND_SET_NULL(gMonSpritesGfxPtr->buffer);
    FREE_AND_SET_NULL(gMonSpritesGfxPtr->barFontGfx);
    FREE_AND_SET_NULL(gMonSpritesGfxPtr->firstDecompressed);
    gMonSpritesGfxPtr->spritesGfx[B_POSITION_PLAYER_LEFT] = NULL;
    gMonSpritesGfxPtr->spritesGfx[B_POSITION_OPPONENT_LEFT] = NULL;
    gMonSpritesGfxPtr->spritesGfx[B_POSITION_PLAYER_RIGHT] = NULL;
    gMonSpritesGfxPtr->spritesGfx[B_POSITION_OPPONENT_RIGHT] = NULL;
    FREE_AND_SET_NULL(gMonSpritesGfxPtr);
}

bool32 ShouldPlayNormalPokeCry(struct Pokemon *mon)
{
    s16 hp, maxHP;
    s32 barLevel;

    if (GetMonData(mon, MON_DATA_STATUS) & (STATUS1_ANY))
        return FALSE;
    hp = GetMonData(mon, MON_DATA_HP);
    maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    barLevel = GetHPBarLevel(hp, maxHP);
    if (barLevel <= HP_BAR_YELLOW)
        return FALSE;
    return TRUE;
}
