#include "global.h"
#include "gflib.h"
#include "battle.h"
#include "constants/form_change_types.h"
#include "constants/items.h"
#include "mail_data.h"
#include "pokemon_storage_system.h"
#include "event_data.h"
#include "random.h"
#include "constants/moves.h"
#include "data.h"
#include "item.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "script.h"
#include "strings.h"
#include "party_menu.h"
#include "pokemon.h"
#include "list_menu.h"
#include "overworld.h"
#include "pokedex.h"
#include "decompress.h"
#include "constants/songs.h"
#include "text_window.h"
#include "trig.h"
#include "m4a.h"
#include "graphics.h"
#include "scanline_effect.h"
#include "naming_screen.h"
#include "help_system.h"
#include "field_fadetransition.h"
#include "trade.h"
#include "daycare.h"
#include "constants/daycare.h"
#include "constants/region_map_sections.h"
#include "daycare.h"
#include "pokemon_storage_system_internal.h"

// Combination of RSE's Day-Care (re-used on Four Island), FRLG's Day-Care, and egg_hatch.c

struct EggHatchData
{
    u8 eggSpriteID;
    u8 pokeSpriteID;
    u8 CB2_state;
    u8 CB2_PalCounter;
    u8 eggPartyID;
    u8 unused_5;
    u8 unused_6;
    u8 eggShardVelocityID;
    u8 windowId;
    u8 unused_9;
    u8 unused_A;
    u16 species;
    u8 textColor[3];
};

// this file's functions
//static void ClearDaycareMonMail(struct DayCareMail *mail);
static void SetInitialEggData(struct Pokemon *mon, u16 species, struct DayCare *daycare, u8 *parentSlots);
static u8 GetRoute5DaycareCompatibilityScore(struct DayCare *daycare);
//static u8 GetDaycareCompatibilityScore(struct DayCare *daycare);
static void DaycarePrintMonInfo(u8 windowId, s32 daycareSlotId, u8 y);

static void Task_EggHatch(u8 taskID);
static void CB2_EggHatch_0(void);
static void CB2_EggHatch_1(void);
static void SpriteCB_Egg_0(struct Sprite* sprite);
static void SpriteCB_Egg_1(struct Sprite* sprite);
static void SpriteCB_Egg_2(struct Sprite* sprite);
static void SpriteCB_Egg_3(struct Sprite* sprite);
static void SpriteCB_Egg_4(struct Sprite* sprite);
static void SpriteCB_Egg_5(struct Sprite* sprite);
static void SpriteCB_EggShard(struct Sprite* sprite);
static void EggHatchPrintMessage(u8 windowId, u8* string, u8 x, u8 y, u8 speed);
static void CreateRandomEggShardSprite(void);
static void CreateEggShardSprite(u8 x, u8 y, s16 data1, s16 data2, s16 data3, u8 spriteAnimIndex);

// IWRAM bss
static struct EggHatchData *sEggHatchData;

// RAM buffers used to assist with BuildEggMoveset()
EWRAM_DATA static u16 sHatchedEggLevelUpMoves[EGG_LVL_UP_MOVES_ARRAY_COUNT] = {0};
EWRAM_DATA static u16 sHatchedEggFatherMoves[4] = {0};
EWRAM_DATA static u16 sHatchedEggFinalMoves[4] = {0};
EWRAM_DATA static u16 sHatchedEggEggMoves[EGG_MOVES_ARRAY_COUNT] = {0};
EWRAM_DATA static u16 sHatchedEggMotherMoves[4] = {0};

enum  ParentSlot
{
    Mother,
    Father
};

#include "data/pokemon/egg_moves.h"

static const struct WindowTemplate sDaycareLevelMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 12,
    .tilemapTop = 1,
    .width = 17,
    .height = 5,
    .paletteNum = 15,
    .baseBlock = 8
};

static const struct ListMenuItem sLevelMenuItems[] =
{
    {gExpandedPlaceholder_Empty, 0},
    {gExpandedPlaceholder_Empty, 1},
    {gOtherText_Exit, DAYCARE_LEVEL_MENU_EXIT}
};

static const struct ListMenuTemplate sDaycareListMenuLevelTemplate =
{
    .items = sLevelMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = DaycarePrintMonInfo,
    .totalItems = 3,
    .maxShowed = 3,
    .windowId = 0,
    .header_X = 2,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 0,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 3,
    .cursorKind = 0
};

static const u8 *const sCompatibilityMessages[] =
{
    COMPOUND_STRING("The two seem to be\npractically inseparable!"),
    gDaycareText_GetAlongVeryWell,
    gDaycareText_GetAlong,
    gDaycareText_DontLikeOther,
    gDaycareText_PlayOther
};

static const u8 sNewLineText[] = _("\n");
static const u8 sJapaneseEggNickname[] = _("タマゴ"); // "tamago" ("egg" in Japanese)

static const u16 sEggPalette[] = INCBIN_U16("graphics/pokemon/egg/normal.gbapal");
static const u8 sEggHatchTiles[] = INCBIN_U8("graphics/misc/egg_hatch.4bpp");
static const u8 sEggShardTiles[] = INCBIN_U8("graphics/misc/egg_shard.4bpp");

static const struct OamData sOamData_EggHatch =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_EggHatch0[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_EggHatch1[] =
{
    ANIMCMD_FRAME(16, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_EggHatch2[] =
{
    ANIMCMD_FRAME(32, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_EggHatch3[] =
{
    ANIMCMD_FRAME(48, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_EggHatch[] =
{
    sSpriteAnim_EggHatch0,
    sSpriteAnim_EggHatch1,
    sSpriteAnim_EggHatch2,
    sSpriteAnim_EggHatch3,
};

static const struct SpriteSheet sEggHatch_Sheet =
{
    .data = sEggHatchTiles,
    .size = 2048,
    .tag = 12345,
};

static const struct SpriteSheet sEggShards_Sheet =
{
    .data = sEggShardTiles,
    .size = 128,
    .tag = 23456,
};

static const struct SpritePalette sEgg_SpritePalette =
{
    .data = sEggPalette,
    .tag = 54321
};

static const struct SpriteTemplate sSpriteTemplate_EggHatch =
{
    .tileTag = 12345,
    .paletteTag = 54321,
    .oam = &sOamData_EggHatch,
    .anims = sSpriteAnimTable_EggHatch,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct OamData sOamData_EggShard =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_EggShard0[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_EggShard1[] =
{
    ANIMCMD_FRAME(1, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_EggShard2[] =
{
    ANIMCMD_FRAME(2, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_EggShard3[] =
{
    ANIMCMD_FRAME(3, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_EggShard[] =
{
    sSpriteAnim_EggShard0,
    sSpriteAnim_EggShard1,
    sSpriteAnim_EggShard2,
    sSpriteAnim_EggShard3,
};

static const struct SpriteTemplate sSpriteTemplate_EggShard =
{
    .tileTag = 23456,
    .paletteTag = 54321,
    .oam = &sOamData_EggShard,
    .anims = sSpriteAnimTable_EggShard,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_EggShard
};

static const struct BgTemplate sBgTemplates_EggHatch[2] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 24,
        .screenSize = 3,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },

    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 8,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
};

static const struct WindowTemplate sWinTemplates_EggHatch[2] =
{
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 64
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sYesNoWinTemplate =
{
    .bg = 0,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 6,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 424
};

static const s16 sEggShardVelocities[][2] =
{
    {Q_8_8(-1.5),       Q_8_8(-3.75)},
    {Q_8_8(-5),         Q_8_8(-3)},
    {Q_8_8(3.5),        Q_8_8(-3)},
    {Q_8_8(-4),         Q_8_8(-3.75)},
    {Q_8_8(2),          Q_8_8(-1.5)},
    {Q_8_8(-0.5),       Q_8_8(-6.75)},
    {Q_8_8(5),          Q_8_8(-2.25)},
    {Q_8_8(-1.5),       Q_8_8(-3.75)},
    {Q_8_8(4.5),        Q_8_8(-1.5)},
    {Q_8_8(-1),         Q_8_8(-6.75)},
    {Q_8_8(4),          Q_8_8(-2.25)},
    {Q_8_8(-3.5),       Q_8_8(-3.75)},
    {Q_8_8(1),          Q_8_8(-1.5)},
    {Q_8_8(-3.515625),  Q_8_8(-6.75)},
    {Q_8_8(4.5),        Q_8_8(-2.25)},
    {Q_8_8(-0.5),       Q_8_8(-7.5)},
    {Q_8_8(1),          Q_8_8(-4.5)},
    {Q_8_8(-2.5),       Q_8_8(-2.25)},
    {Q_8_8(2.5),        Q_8_8(-7.5)},
};

// code

static u8 *DayCare_GetMonNickname(struct Pokemon *mon, u8 *dest)
{
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];

    GetMonData(mon, MON_DATA_NICKNAME, nickname); //when has data field, 3rd argument found data is passed to that and stored
    return StringCopy_Nickname(dest, nickname);
}

static u8 *DayCare_GetBoxMonNickname(struct BoxPokemon *mon, u8 *dest)
{
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];

    GetBoxMonData(mon, MON_DATA_NICKNAME, nickname);
    return StringCopy_Nickname(dest, nickname);
}

u8 CountPokemonInDaycare(struct DayCare *daycare)
{
    u8 i, count;
    count = 0;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            if (GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_SPECIES) != 0)
                count++;
        }
    }
    else
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            if (GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES) != 0)
                count++;
        }
    }

    return count;
}

/*void InitDaycareMailRecordMixing(struct DayCare *daycare, struct RecordMixingDayCareMail *daycareMail)
{
    u8 i;
    u8 numDaycareMons = 0;

    for (i = 0; i < DAYCARE_MON_COUNT; i++)
    {
        if (GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            numDaycareMons++;
            if (GetBoxMonData(&daycare->mons[i].mon, MON_DATA_HELD_ITEM) == ITEM_NONE)
            {
                daycareMail->holdsItem[i] = FALSE;
            }
            else
            {
                daycareMail->holdsItem[i] = TRUE;
            }
        }
        else
        {
            daycareMail->holdsItem[i] = TRUE;
        }
    }

    daycareMail->numDaycareMons = numDaycareMons;
}*/

s8 Daycare_FindEmptySpot(struct DayCare *daycare)
{
    u8 i;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            if (GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_SPECIES) == 0)
                return i;
        }
    }
    else
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            if (GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES) == 0)
                return i;
        }
    }

    return -1;
}

static void StorePokemonInDaycare(struct Pokemon *mon, struct DaycareMon *daycareMon)
{
    if (MonHasMail(mon))
    {
        u8 mailId;

       // StringCopy(daycareMon->mail.OT_name, gSaveBlock2Ptr->playerName);
       // DayCare_GetMonNickname(mon, daycareMon->mail.monName);
//        StripExtCtrlCodes(daycareMon->mail.monName);
//        daycareMon->mail.gameLanguage = LANGUAGE_ENGLISH;
//        daycareMon->mail.monLanguage = GetMonData(mon, MON_DATA_LANGUAGE);
        //mailId = GetMonData(mon, MON_DATA_MAIL);
     //   daycareMon->mail.message = gSaveBlock1Ptr->mail[mailId];
        TakeMailFromMon(mon);
    }

    daycareMon->mon = mon->box;
    BoxMonRestorePP(&daycareMon->mon);
    daycareMon->steps = 0;
    ZeroMonData(mon);
    CompactPartySlots();
    CalculatePlayerPartyCount();
}

static void StorePokemonInDaycare2(struct BoxPokemon *mon, struct DaycareMon *daycareMon)
{
    if (BoxMonHasMail(mon))
    {
        u8 mailId;

        /*StringCopy(daycareMon->mail.otName, gSaveBlock2Ptr->playerName);
        DayCare_GetMonNickname(mon, daycareMon->mail.monName);
        StripExtCtrlCodes(daycareMon->mail.monName);
        daycareMon->mail.gameLanguage = GAME_LANGUAGE;
        daycareMon->mail.monLanguage = GetBoxMonData(mon, MON_DATA_LANGUAGE);
        mailId = GetBoxMonData(mon, MON_DATA_MAIL);
        daycareMon->mail.message = gSaveBlock1Ptr->mail[mailId];
        */
        //TakeMailFromBoxMon(mon);
    }

    daycareMon->mon = *mon;
    daycareMon->steps = 0;
    BoxMonRestorePP(&daycareMon->mon);
    ZeroBoxMonData(mon);
    CalculatePlayerPartyCount();

    //attempt set this later,
    //gen9 transfer egg movesby being in daycare together
    //if (P_EGG_MOVE_TRANSFER >= GEN_8)
    //    TransferEggMoves();
}

static void StorePokemonInEmptyDaycareSlot(struct Pokemon *mon, struct DayCare *daycare)
{
    s8 slotId = Daycare_FindEmptySpot(daycare);
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        StorePokemonInDaycare(mon, &daycare->route5_daycareMon[slotId]);
    else
        StorePokemonInDaycare(mon, &daycare->mons[slotId]);
}

static void StorePokemonInEmptyDaycareSlot2(struct BoxPokemon *mon, struct DayCare *daycare)
{
    s8 slotId = Daycare_FindEmptySpot(daycare);
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        StorePokemonInDaycare2(mon, &daycare->route5_daycareMon[slotId]);
    else
        StorePokemonInDaycare2(mon, &daycare->mons[slotId]);
}

//this command is used
//add check here for MON_DATA_BLOCK_BOX_EXP_GAIN
//so I can trigger a text for the daycare person to  say
//"this pokemon wont gain exp with us, is that ok" YES/NO
//moslty so player is aware the block is indeed working
//then go to normal alright we'll take care of this pokemon 

void StoreSelectedPokemonInDaycare(void)
{
    //u8 monId = GetCursorSelectionMonId();
    u8 monId = GetBoxCursorPosition();
    if(GetInPartyMenu())
    {
        if ((IsNuzlockeModeOn() && (GetMonData(&gPlayerParty[monId], MON_DATA_HP, NULL) == 0)))
        {
            gSpecialVar_0x8008 = NUZLOCKE_BANNED_MON;
            return;
        } //need do sometning figure how to make play print text and continue script
            //say sorry I can't take that pokemon
            //hmm can do set result var then put a compare var result after
            //to jump to other command
            //yeah that'd work
        
        //unsure if should use this or slot2
        //want to only access through box?
        StorePokemonInEmptyDaycareSlot(&gPlayerParty[monId], &gSaveBlock1Ptr->daycare);
    }
    else
    {
        u8 boxId = StorageGetCurrentBox();
        if (IsNuzlockeModeOn() && (GetCurrentBoxMonData(monId, MON_DATA_BOX_HP) == 0))
        {
            gSpecialVar_0x8008 = NUZLOCKE_BANNED_MON;
            return;
        }
        StorePokemonInEmptyDaycareSlot2(&gPokemonStoragePtr->boxes[boxId][monId], &gSaveBlock1Ptr->daycare);
    }
    
}

// Shifts the second daycare pokemon slot into the first slot.
static void ShiftDaycareSlots(struct DayCare *daycare)
{
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        if (GetBoxMonData(&daycare->route5_daycareMon[1].mon, MON_DATA_SPECIES) != SPECIES_NONE
            && GetBoxMonData(&daycare->route5_daycareMon[0].mon, MON_DATA_SPECIES) == SPECIES_NONE)
        {
            daycare->route5_daycareMon[0].mon = daycare->route5_daycareMon[1].mon;
            ZeroBoxMonData(&daycare->route5_daycareMon[1].mon);

            daycare->route5_daycareMon[0].steps = daycare->route5_daycareMon[1].steps;
            daycare->route5_daycareMon[1].steps = 0;
        }
    }
    else
    {
        // This condition is only satisfied when the player takes out the first pokemon from the daycare.
        if (GetBoxMonData(&daycare->mons[1].mon, MON_DATA_SPECIES) != SPECIES_NONE
            && GetBoxMonData(&daycare->mons[0].mon, MON_DATA_SPECIES) == SPECIES_NONE)
        {
            daycare->mons[0].mon = daycare->mons[1].mon;
            ZeroBoxMonData(&daycare->mons[1].mon);

            //daycare->mons[0].mail = daycare->mons[1].mail;
            daycare->mons[0].steps = daycare->mons[1].steps;
            daycare->mons[1].steps = 0;
            //ClearDaycareMonMail(&daycare->mons[1].mail);
        }
    }
}

//since doesn't use expfunction bs command don't have to worry about the friendship gain from exp.
//think mon in daycare don't gain friendship?  searched and they dont' good.
//can just copy and slap into pc logic then with a flag check, then again, doesn't really make sense,
//and would just make extra early mon caught at a disadvantage/unusable for longer if you leave them
//preference is exp gain/ lvl gain to be at a slightly lower rate than normal fighting/
static void ApplyDaycareExperience(struct Pokemon *mon)
{
    s32 i;
    bool8 firstMove;
    u16 learnedMove;

    for (i = 0; i < MAX_LEVEL; i++)
    {
        TryIncrementMonLevel(mon); //increment level if less than max level, commented out move learn
        // Add the mon's gained daycare experience level by level until it can't level up anymore.
        /*if (TryIncrementMonLevel(mon)) //hmm so its not exactly experience its instaed just a level gain? hmm
        {
            // Teach the mon new moves it learned while in the daycare.  //prob just delete this
            firstMove = TRUE;
            while ((learnedMove = MonTryLearningNewMove(mon, firstMove)) != 0)
            {
                firstMove = FALSE;
                if (learnedMove == MON_HAS_MAX_MOVES)
                    DeleteFirstMoveAndGiveMoveToMon(mon, gMoveToLearn);
            }
        }
        else
        {
            break;
        }*/
    }
    
    // Re-calculate the mons stats at its new level.
    CalculateMonStats(mon);
}

//VSONIC
static u16 TakeSelectedPokemonFromDaycare(struct DaycareMon *daycareMon)
{
    u16 species,newSpecies;
    u32 experience;
    struct Pokemon pokemon;

    DayCare_GetBoxMonNickname(&daycareMon->mon, gStringVar1);
    species = GetBoxMonData(&daycareMon->mon, MON_DATA_SPECIES);
    BoxMonToMon(&daycareMon->mon, &pokemon);

    newSpecies = GetFormChangeTargetSpecies(&pokemon, FORM_CHANGE_WITHDRAW, 0);
    if (newSpecies != SPECIES_NONE)
    {
        SetMonData(&pokemon, MON_DATA_SPECIES, &newSpecies);
        CalculateMonStats(&pokemon);
        species = newSpecies;
    } //dont know when this would be used but adding

    if (GetMonData(&pokemon, MON_DATA_LEVEL) != MAX_LEVEL)
    {
        if (GetBoxMonData(&daycareMon->mon, MON_DATA_BLOCK_BOX_EXP_GAIN))   
            experience = GetMonData(&pokemon, MON_DATA_EXP);
        else
            experience = GetMonData(&pokemon, MON_DATA_EXP) + daycareMon->steps;
        SetMonData(&pokemon, MON_DATA_EXP, &experience);
        ApplyDaycareExperience(&pokemon);
    }

    gPlayerParty[PARTY_SIZE - 1] = pokemon;
    /*if (daycareMon->mail.message.itemId)
    {
        GiveMailToMon2(&gPlayerParty[PARTY_SIZE - 1], &daycareMon->mail.message);
        ClearDaycareMonMail(&daycareMon->mail);
    }*/

    ZeroBoxMonData(&daycareMon->mon);
    daycareMon->steps = 0;
    CompactPartySlots();
    CalculatePlayerPartyCount();
    return species;
}

static u16 TakeSelectedPokemonMonFromDaycareShiftSlots(struct DayCare *daycare, u8 slotId)
{
    u16 species;
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        species = TakeSelectedPokemonFromDaycare(&daycare->route5_daycareMon[slotId]);
    else
        species = TakeSelectedPokemonFromDaycare(&daycare->mons[slotId]);
    ShiftDaycareSlots(daycare);
    return species;
}

u16 TakePokemonFromDaycare(void)
{
    return TakeSelectedPokemonMonFromDaycareShiftSlots(&gSaveBlock1Ptr->daycare, gSpecialVar_0x8004);
}

static u8 GetLevelAfterDaycareSteps(struct BoxPokemon *mon, u32 steps)
{
    struct BoxPokemon tempMon = *mon;

    u32 experience = GetBoxMonData(mon, MON_DATA_EXP) + steps;
    SetBoxMonData(&tempMon, MON_DATA_EXP,  &experience);
    return GetLevelFromBoxMonExp(&tempMon);
}

static u8 GetNumLevelsGainedFromSteps(struct DaycareMon *daycareMon)
{
    u8 levelBefore;
    u8 levelAfter;

    levelBefore = GetLevelFromBoxMonExp(&daycareMon->mon);
    levelAfter = GetLevelAfterDaycareSteps(&daycareMon->mon, daycareMon->steps);
    return levelAfter - levelBefore;
}

static u8 GetNumLevelsGainedForDaycareMon(struct DaycareMon *daycareMon)
{
    u8 numLevelsGained = GetNumLevelsGainedFromSteps(daycareMon);
    ConvertIntToDecimalStringN(gStringVar2, numLevelsGained, STR_CONV_MODE_LEFT_ALIGN, 2);
    DayCare_GetBoxMonNickname(&daycareMon->mon, gStringVar1);
    return numLevelsGained;
}

static u32 GetDaycareCostForSelectedMon(struct DaycareMon *daycareMon)
{
    u32 cost;

    u8 numLevelsGained = GetNumLevelsGainedFromSteps(daycareMon);
    DayCare_GetBoxMonNickname(&daycareMon->mon, gStringVar1);
    cost = 100 + 100 * numLevelsGained;
    ConvertIntToDecimalStringN(gStringVar2, cost, STR_CONV_MODE_LEFT_ALIGN, 5);
    return cost;
}

static u16 GetDaycareCostForMon(struct DayCare *daycare, u8 slotId)
{
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        return GetDaycareCostForSelectedMon(&daycare->route5_daycareMon[slotId]);
    else
        return GetDaycareCostForSelectedMon(&daycare->mons[slotId]);
}

void GetDaycareCost(void)
{
    gSpecialVar_0x8005 = GetDaycareCostForMon(&gSaveBlock1Ptr->daycare, gSpecialVar_0x8004);
}

static void Debug_AddDaycareSteps(u16 numSteps)
{
    gSaveBlock1Ptr->daycare.mons[0].steps += numSteps;
    gSaveBlock1Ptr->daycare.mons[1].steps += numSteps;
    //gSaveBlock1Ptr->route5DayCareMon.steps += numSteps;
}

u8 GetNumLevelsGainedFromDaycare(void)
{
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        if (GetBoxMonData(&gSaveBlock1Ptr->daycare.route5_daycareMon[gSpecialVar_0x8004], MON_DATA_SPECIES) != 0)
            return GetNumLevelsGainedForDaycareMon(&gSaveBlock1Ptr->daycare.route5_daycareMon[gSpecialVar_0x8004]);
    }
    else
    {
        if (GetBoxMonData(&gSaveBlock1Ptr->daycare.mons[gSpecialVar_0x8004], MON_DATA_SPECIES) != 0)
            return GetNumLevelsGainedForDaycareMon(&gSaveBlock1Ptr->daycare.mons[gSpecialVar_0x8004]);
    }
    return 0;
}

/*static void ClearDaycareMonMail(struct DayCareMail *mail)
{
    s32 i;

    for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
        mail->OT_name[i] = 0;
    for (i = 0; i < POKEMON_NAME_LENGTH + 1; i++)
        mail->monName[i] = 0;

    ClearMailStruct(&mail->message);
}*/

static void ClearDaycareMon(struct DaycareMon *daycareMon)
{
    ZeroBoxMonData(&daycareMon->mon);
    daycareMon->steps = 0;
    //ClearDaycareMonMail(&daycareMon->mail);
    //daycare->boost = 0; //might remove this, yeah think will, that way only removing all mon would remove bonus
}

//oh this isn't used?
static void ClearAllDaycareData(struct DayCare *daycare)
{
    u8 i;

    for (i = 0; i < DAYCARE_MON_COUNT; i++)
        ClearDaycareMon(&daycare->mons[i]);

    daycare->offspringPersonality = 0;
    daycare->stepCounter = 0;
    daycare->boost = 0;
}

// Determines what the species of an Egg would be based on the given species.
// It determines this by working backwards through the evolution chain of the
// given species.
u16 GetEggSpecies(u16 species) //vsonic
{
    int i, j, k;
    bool8 found;
    u16 NUM_EVOS_CAP = (gBaseStats[SanitizeSpeciesId(species)].evolutions == NULL) ? EVOS_PER_MON : EVOLUTIONS_END;
    

    // Working backwards up to 5 times seems arbitrary, since the maximum number
    // of times would only be 3 for 3-stage evolutions.
    for (i = 0; i < EVOS_PER_MON; i++)
    {
        found = FALSE;
        for (j = 1; j < NUM_SPECIES; j++)
        {
            const struct Evolution *evolutions = GetSpeciesEvolutions(j);
            if (evolutions == NULL)
                continue;

            for (k = 0; evolutions[k].method != EVOLUTIONS_END; k++)
            //for (k = 0; evolutions[k].method != NUM_EVOS_CAP; k++)
            {
                if (SanitizeSpeciesId(evolutions[k].targetSpecies) == species)
                {
                    species = j;
                    found = TRUE;
                    break; //breaks out k loop back to j loop
                }
            }

            if (found)
                break;//if k loop found species, keep species assingment and return to i loop
        }

        if (j == NUM_SPECIES)
            break;
    }

    return species;
}
//
//static s32 GetSlotToInheritNature(struct DayCare *daycare)
//{
//    u32 species[DAYCARE_MON_COUNT];
//    s32 i;
//    s32 dittoCount;
//    s32 slot = -1;
//
//    // search for female gender
//    for (i = 0; i < DAYCARE_MON_COUNT; i++)
//    {
//        if (GetBoxMonGender(&daycare->mons[i].mon) == MON_FEMALE)
//            slot = i;
//    }
//
//    // search for ditto
//    for (dittoCount = 0, i = 0; i < DAYCARE_MON_COUNT; i++)
//    {
//        species[i] = GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES);
//        if (species[i] == SPECIES_DITTO)
//            dittoCount++, slot = i;
//    }
//
//    // coin flip on ...two Dittos
//    if (dittoCount == 2)
//    {
//        if (Random() >= USHRT_MAX / 2)
//            slot = 0;
//        else
//            slot = 1;
//    }
//
//    // nature inheritance only if holds everstone
//    if (GetBoxMonData(&daycare->mons[slot].mon, MON_DATA_HELD_ITEM) != ITEM_EVERSTONE
//        || Random() >= USHRT_MAX / 2)
//    {
//        return -1;
//    }
//
//    return slot;
//}

static void _TriggerPendingRoute5DaycareEgg(struct DayCare *daycare)
{
    daycare->route5_offspringPersonality = ((Random()) % 0xFFFE) + 1;
    FlagSet(FLAG_PENDING_ROUTE_5_DAYCARE_EGG);
}

static void _TriggerPendingDaycareEgg(struct DayCare *daycare)
{
//    s32 natureSlot;
//    s32 natureTries = 0;
//
//    SeedRng2(gMain.vblankCounter2);
//    natureSlot = GetSlotToInheritNature(daycare);
//
//    if (natureSlot < 0)
//    {
//        daycare->offspringPersonality = (Random2() << 0x10) | ((Random() % 0xfffe) + 1);
//    }
//    else
//    {
//        u8 wantedNature = GetNatureFromPersonality(GetBoxMonData(&daycare->mons[natureSlot].mon, MON_DATA_PERSONALITY, NULL));
//        u32 personality;
//
//        do
//        {
//            personality = (Random2() << 0x10) | (Random());
//            if (wantedNature == GetNatureFromPersonality(personality) && personality != 0)
//                break; // we found a personality with the same nature
//
//            natureTries++;
//        } while (natureTries <= 2400);
//
//        daycare->offspringPersonality = personality;
//    }


    daycare->offspringPersonality = ((Random()) % 0xFFFE) + 1;
    FlagSet(FLAG_PENDING_DAYCARE_EGG);
    
}

static void _TriggerPendingDaycareMaleEgg(struct DayCare *daycare)
{
    daycare->offspringPersonality = (Random()) | (EGG_GENDER_MALE);
    FlagSet(FLAG_PENDING_DAYCARE_EGG);
}

void TriggerPendingDaycareEgg(void)
{
    _TriggerPendingDaycareEgg(&gSaveBlock1Ptr->daycare);
}

void TriggerPendingRoute5DaycareEgg(void)
{
    _TriggerPendingRoute5DaycareEgg(&gSaveBlock1Ptr->daycare);
}

static void TriggerPendingDaycareMaleEgg(void)
{
    _TriggerPendingDaycareMaleEgg(&gSaveBlock1Ptr->daycare);
}

// Removes the selected index from the given IV list and shifts the remaining
// elements to the left.
static void RemoveIVIndexFromList(u8 *ivs, u8 selectedIv)
{
    s32 i, j;
    u8 temp[NUM_STATS];

    ivs[selectedIv] = 0xFF;
    for (i = 0; i < NUM_STATS; i++)
    {
        temp[i] = ivs[i];
    }

    j = 0;
    for (i = 0; i < NUM_STATS; i++)
    {
        if (temp[i] != 0xFF)
            ivs[j++] = temp[i];
    }
}

static void InheritIVs(struct Pokemon *egg, struct DayCare *daycare)
{
    u8 i;
    u8 selectedIvs[INHERITED_IV_COUNT];
    u8 availableIVs[NUM_STATS];
    u8 whichParent[NELEMS(selectedIvs)];
    u8 iv;

    // Initialize a list of IV indices.
    for (i = 0; i < NUM_STATS; i++)
    {
        availableIVs[i] = i;
    }

    // Select the 3 IVs that will be inherited.
    for (i = 0; i < NELEMS(selectedIvs); i++)
    {
        // Randomly pick an IV from the available list and stop from being chosen again.
        selectedIvs[i] = availableIVs[Random() % (NUM_STATS - i)];
        RemoveIVIndexFromList(availableIVs, selectedIvs[i]);
    }

    // Determine which parent each of the selected IVs should inherit from.
    for (i = 0; i < NELEMS(selectedIvs); i++)
    {
        whichParent[i] = Random() % DAYCARE_MON_COUNT;
    }
    
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        // Set each of inherited IVs on the egg mon.
        for (i = 0; i < NELEMS(selectedIvs); i++)
        {
            switch (selectedIvs[i])
            {
                case 0:
                    iv = GetBoxMonData(&daycare->route5_daycareMon[whichParent[i]].mon, MON_DATA_HP_IV);
                    SetMonData(egg, MON_DATA_HP_IV, &iv);
                    break;
                case 1:
                    iv = GetBoxMonData(&daycare->route5_daycareMon[whichParent[i]].mon, MON_DATA_ATK_IV);
                    SetMonData(egg, MON_DATA_ATK_IV, &iv);
                    break;
                case 2:
                    iv = GetBoxMonData(&daycare->route5_daycareMon[whichParent[i]].mon, MON_DATA_DEF_IV);
                    SetMonData(egg, MON_DATA_DEF_IV, &iv);
                    break;
                case 3:
                    iv = GetBoxMonData(&daycare->route5_daycareMon[whichParent[i]].mon, MON_DATA_SPEED_IV);
                    SetMonData(egg, MON_DATA_SPEED_IV, &iv);
                    break;
                case 4:
                    iv = GetBoxMonData(&daycare->route5_daycareMon[whichParent[i]].mon, MON_DATA_SPATK_IV);
                    SetMonData(egg, MON_DATA_SPATK_IV, &iv);
                    break;
                case 5:
                    iv = GetBoxMonData(&daycare->route5_daycareMon[whichParent[i]].mon, MON_DATA_SPDEF_IV);
                    SetMonData(egg, MON_DATA_SPDEF_IV, &iv);
                    break;
            }
        }
    }
    else
    {
        // Set each of inherited IVs on the egg mon.
        for (i = 0; i < NELEMS(selectedIvs); i++)
        {
            switch (selectedIvs[i])
            {
                case 0:
                    iv = GetBoxMonData(&daycare->mons[whichParent[i]].mon, MON_DATA_HP_IV);
                    SetMonData(egg, MON_DATA_HP_IV, &iv);
                    break;
                case 1:
                    iv = GetBoxMonData(&daycare->mons[whichParent[i]].mon, MON_DATA_ATK_IV);
                    SetMonData(egg, MON_DATA_ATK_IV, &iv);
                    break;
                case 2:
                    iv = GetBoxMonData(&daycare->mons[whichParent[i]].mon, MON_DATA_DEF_IV);
                    SetMonData(egg, MON_DATA_DEF_IV, &iv);
                    break;
                case 3:
                    iv = GetBoxMonData(&daycare->mons[whichParent[i]].mon, MON_DATA_SPEED_IV);
                    SetMonData(egg, MON_DATA_SPEED_IV, &iv);
                    break;
                case 4:
                    iv = GetBoxMonData(&daycare->mons[whichParent[i]].mon, MON_DATA_SPATK_IV);
                    SetMonData(egg, MON_DATA_SPATK_IV, &iv);
                    break;
                case 5:
                    iv = GetBoxMonData(&daycare->mons[whichParent[i]].mon, MON_DATA_SPDEF_IV);
                    SetMonData(egg, MON_DATA_SPDEF_IV, &iv);
                    break;
            }
        }
    }
}

// Counts the number of egg moves a pokemon learns and stores the moves in
// the given array.
static u8 GetEggMoves(struct Pokemon *pokemon, u16 *eggMoves)
{
    u16 eggMoveIdx;
    u16 numEggMoves;
    u16 species;
    u16 i;

    numEggMoves = 0;
    eggMoveIdx = 0;
    species = GetMonData(pokemon, MON_DATA_SPECIES);
    for (i = 0; i < NELEMS(gEggMoves) - 1; i++)
    {
        if (gEggMoves[i] == species + EGG_MOVES_SPECIES_OFFSET)
        {
            eggMoveIdx = i + 1;
            break;
        }
    }

    for (i = 0; i < EGG_MOVES_ARRAY_COUNT; i++)
    {
        if (gEggMoves[eggMoveIdx + i] > EGG_MOVES_SPECIES_OFFSET)
        {
            // TODO: the curly braces around this if statement are required for a matching build.
            break;
        }

        eggMoves[i] = gEggMoves[eggMoveIdx + i];
        numEggMoves++;
    }

    return numEggMoves;
}

static void BuildEggMoveset(struct Pokemon *egg, struct BoxPokemon *father, struct BoxPokemon *mother)
{
    u16 numSharedParentMoves;
    u32 numLevelUpMoves;
    u16 numEggMoves;
    u16 i, j;

    numSharedParentMoves = 0;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        sHatchedEggMotherMoves[i] = MOVE_NONE;
        sHatchedEggFatherMoves[i] = MOVE_NONE;
        sHatchedEggFinalMoves[i] = MOVE_NONE;
    }
    for (i = 0; i < EGG_MOVES_ARRAY_COUNT; i++)
        sHatchedEggEggMoves[i] = MOVE_NONE;
    for (i = 0; i < EGG_LVL_UP_MOVES_ARRAY_COUNT; i++)
        sHatchedEggLevelUpMoves[i] = MOVE_NONE;

    numLevelUpMoves = GetLevelUpMovesBySpecies(GetMonData(egg, MON_DATA_SPECIES), sHatchedEggLevelUpMoves);
    //figure out how to do move passing,
    //thought set with held item but that keeps me from using
    //an item that's actually useful for breeding
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        sHatchedEggFatherMoves[i] = GetBoxMonData(father, MON_DATA_MOVE1 + i);
        sHatchedEggMotherMoves[i] = GetBoxMonData(mother, MON_DATA_MOVE1 + i);
    }

    numEggMoves = GetEggMoves(egg, sHatchedEggEggMoves);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (sHatchedEggFatherMoves[i] != MOVE_NONE)
        {
            for (j = 0; j < numEggMoves; j++)
            {
                if (sHatchedEggFatherMoves[i] == sHatchedEggEggMoves[j])
                {
                    if (GiveMoveToMon(egg, sHatchedEggFatherMoves[i]) == MON_HAS_MAX_MOVES)
                        DeleteFirstMoveAndGiveMoveToMon(egg, sHatchedEggFatherMoves[i]);
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    //hmm realize the main impact of this system
    //was lost when tms became reusable
    //its not doing anything you can't already do
    //perhaps do same thing for learnset?
    //if mon knows a move within eggs learnset teach it the move?
    //potential being  low level mon with much higher moves
    //makes it designer and would cut down time getting mon "usable"
    //also consider tutor moves
    //oh it already inherists learnset moves, ok,
    //so all I'd have to do is add the search for tutor moves
    //at the end, to give them preference
    //only issue is too random can't control,
    //so set it up so holding certain item,
    //lets decide if take all move from mother or all from father,
    //without that default behavior should just be to take first 2 move slots
    //from both
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (sHatchedEggFatherMoves[i] != MOVE_NONE)
        {
            for (j = 0; j < NUM_TECHNICAL_MACHINES + NUM_HIDDEN_MACHINES; j++)
            {
                if (sHatchedEggFatherMoves[i] == ItemIdToBattleMoveId(gTMHM_List[j]) && CanMonLearnTMHM(egg, gTMHM_List[j]))
                {
                    if (GiveMoveToMon(egg, sHatchedEggFatherMoves[i]) == MON_HAS_MAX_MOVES)
                        DeleteFirstMoveAndGiveMoveToMon(egg, sHatchedEggFatherMoves[i]);
                }
            }
        }
    }
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (sHatchedEggFatherMoves[i] == MOVE_NONE)
            break;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (sHatchedEggFatherMoves[i] == sHatchedEggMotherMoves[j] && sHatchedEggFatherMoves[i] != MOVE_NONE)
                sHatchedEggFinalMoves[numSharedParentMoves++] = sHatchedEggFatherMoves[i];
        }
    }

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (sHatchedEggFinalMoves[i] == MOVE_NONE)
            break;
        for (j = 0; j < numLevelUpMoves; j++)
        {
            if (sHatchedEggLevelUpMoves[j] != MOVE_NONE && sHatchedEggFinalMoves[i] == sHatchedEggLevelUpMoves[j])
            {
                if (GiveMoveToMon(egg, sHatchedEggFinalMoves[i]) == MON_HAS_MAX_MOVES)
                    DeleteFirstMoveAndGiveMoveToMon(egg, sHatchedEggFinalMoves[i]);
                break;
            }
        }
    }
}

void SetPlayerAtRoute5Daycare(void)
{
    VarSet(VAR_PLAYER_AT_ROUTE5_DAYCARE, TRUE);
}

void ClearVarPlayerAtRoute5Daycare(void)
{
    VarSet(VAR_PLAYER_AT_ROUTE5_DAYCARE, 0);
}

//this is called both when rejecting an egg, or when taking it from daycare
static void RemoveEggFromDayCare(struct DayCare *daycare)
{
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        daycare->route5_offspringPersonality = 0;
        daycare->stepCounter = 0; //hmmm important because  stepcounter is used to set egg cycles
        daycare->route5_eggTimer = 0;
        ClearVarPlayerAtRoute5Daycare(); //put here as shoudl be end of script with daycare man
    }
    else
    {
        daycare->offspringPersonality = 0;
        daycare->stepCounter = 0; //hmmm important because  stepcounter is used to set egg cycles
        daycare->eggTimer = 0;
        if (daycare->boost == TRUE)
            daycare->eggCount++;

        if (daycare->eggCount == 3)
        {
            daycare->boost = FALSE;
            daycare->eggCount = FALSE;
        }
    }
}

void RejectEggFromDayCare(void)
{
    RemoveEggFromDayCare(&gSaveBlock1Ptr->daycare);
}

static void AlterEggSpeciesWithIncenseItem(u16 *species, struct DayCare *daycare)
{
    u16 motherItem, fatherItem;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        motherItem = GetBoxMonData(&daycare->route5_daycareMon[Mother].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->route5_daycareMon[Father].mon, MON_DATA_HELD_ITEM);   
    }
    else
    {
        motherItem = GetBoxMonData(&daycare->mons[Mother].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->mons[Father].mon, MON_DATA_HELD_ITEM);
    }

        
    if (*species == SPECIES_WYNAUT || *species == SPECIES_AZURILL)
    {
        
        if (*species == SPECIES_WYNAUT && motherItem != ITEM_LAX_INCENSE && fatherItem != ITEM_LAX_INCENSE)
        {
            *species = SPECIES_WOBBUFFET;
        }

        if (*species == SPECIES_AZURILL && motherItem != ITEM_SEA_INCENSE && fatherItem != ITEM_SEA_INCENSE)
        {
            *species = SPECIES_MARILL;
        }
    }

    

    /*GetMonData(&daycare->mons[Mother].mon, MON_DATA_SPECIES, data);
    for (i = SPECIES_RATTATA_ALOLAN; gSpeciesNames[i] != gSpeciesNames[data]; i++)
    {
        //if mon has alt form reset species, i..e a species with same name (excluding megas)
        if ((!(StringCompare(gSpeciesNames[i], gSpeciesNames[data])))
        &&  !IsRegionalVariant(data)) //and mother species isn't already a variant
        {
            GetSpeciesPreEvolution(data,i)

        }//check if item flag matches form flag of alt species i.e i value
        //potentially do like power items where seondaryid field for item is used to hold value I need
    }*/
    
    
} //for species that have alt base forms, change species to that form with held sand
//for mon that evolve into alt form, set flag that allows them to do so here,
//benefit being you don't need to consume a sand to do so.
//require different logic for each effect,
//for evolving defualt base form into other species can just use my new planned revised function
//for checking if they shoud evolve into form
//for mon that have an alt base form, thinnk check female for another species
//that shares the same gspeciesname of that region, 
//ex zigzagoon and galarian zigzagoon are both zigzagoon.
//so change species to that of galraian form if either parent held galrian item

//if (StringCompare(gBaseStats[GetMonData(pokemon, MON_DATA_SPECIES, NULL)]].speciesName, gStringVar1) != 0)
//this what I use,  first value should be mother species, look for mon that shares name
//that base stat flag matches the item value to set
//replace gStringVar1  with target species  
//then just have *species = that

//think can use this for breed alt forms
//check if father is from alt region based on flag, or is same type as alt form of mother species
//ex. female raticate with dark type absol, could make alolan rattata
//change mind doing with item
//vsonic IMPORTANT
static void GiveVoltTackleIfLightBall(struct Pokemon *mon, struct DayCare *daycare)
{
    u32 motherItem;
    u32 fatherItem;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        motherItem = GetBoxMonData(&daycare->route5_daycareMon[Mother].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->route5_daycareMon[Father].mon, MON_DATA_HELD_ITEM);
    }
    else
    {
        motherItem = GetBoxMonData(&daycare->mons[Mother].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->mons[Father].mon, MON_DATA_HELD_ITEM);
    }


    if (motherItem == ITEM_LIGHT_BALL || fatherItem == ITEM_LIGHT_BALL)
    {
        if (GiveMoveToMon(mon, MOVE_VOLT_TACKLE) == MON_HAS_MAX_MOVES)
            DeleteFirstMoveAndGiveMoveToMon(mon, MOVE_VOLT_TACKLE);
    }
}

static u16 DetermineEggSpeciesAndParentSlots(struct DayCare *daycare, u8 *parentSlots)
{
    u16 i,j;
    u16 species[DAYCARE_MON_COUNT];
    u16 eggSpecies;
    
    u16 motherItem, fatherItem;
    u16 MotherSpecies;
    
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            species[i] = GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_SPECIES);
            if (species[i] == SPECIES_DITTO)
            {
                parentSlots[Mother] = i ^ 1;
                parentSlots[Father] = i;
            }
            else if (GetBoxMonGender(&daycare->route5_daycareMon[i].mon) == MON_FEMALE)
            {
                parentSlots[Mother] = i;
                parentSlots[Father] = i ^ 1;
            }
        }
        
        motherItem = GetBoxMonData(&daycare->route5_daycareMon[parentSlots[Mother]].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->route5_daycareMon[parentSlots[Father]].mon, MON_DATA_HELD_ITEM);

        MotherSpecies = GetMonData(&daycare->route5_daycareMon[parentSlots[Mother]].mon, MON_DATA_SPECIES, NULL);
    }
    else
    {
        // Determine which of the daycare mons is the mother and father of the egg.
        // The 0th index of the parentSlots array is considered the mother slot, and the
        // 1st index is the father slot.
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            species[i] = GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES);
            if (species[i] == SPECIES_DITTO)
            {
                parentSlots[Mother] = i ^ 1;
                parentSlots[Father] = i;
            }
            else if (GetBoxMonGender(&daycare->mons[i].mon) == MON_FEMALE)
            {
                parentSlots[Mother] = i;
                parentSlots[Father] = i ^ 1;
            }
        }
        
        motherItem = GetBoxMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->mons[parentSlots[Father]].mon, MON_DATA_HELD_ITEM);

        MotherSpecies = GetMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_SPECIES, NULL);
    }

    for (j = SPECIES_RATTATA_ALOLAN; j != NUM_SPECIES; j++)
    {
        if (IsRegionalVariant(j)) //need this as ran into cosplay forms instead of regionals
        {
            //if mother species has alt form reset species, i..e a species with same name (excluding megas)
            if (((StringCompare(gBaseStats[j].speciesName, gBaseStats[MotherSpecies].speciesName)) == IDENTICAL)
            &&  !IsRegionalVariant(GetMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_SPECIES, NULL))) //and mother species isn't already a variant
            {
                if ((ItemId_GetSecondaryId(motherItem) == gBaseStats[j].flags)
                || (ItemId_GetSecondaryId(fatherItem) == gBaseStats[j].flags))
                {   
                    eggSpecies = GetEggSpecies(j);
                    break;
                    //would be more accurate to use IsRegionalVariant(GetEggSpecies(j))
                    //but that would be double loop and seems to cause lag
                    //doesn't cause a problem as is, would just be same result as normal
                    //if egg species 
                }
                //in case of multiple forms, because of break, will take first form matches criteria

            }//check if item flag matches form flag of alt species i.e i value
            //potentially do like power items where seondaryid field for item is used to hold value I need
        }
    } //if riht should asign j value -//works how I want, and even works with ditto and male mon of species so works perectly


    if (j == NUM_SPECIES)
            eggSpecies = GetEggSpecies(species[parentSlots[Mother]]);

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        if (eggSpecies == SPECIES_NIDORAN_F && daycare->route5_offspringPersonality & EGG_GENDER_MALE)
        {
            eggSpecies = SPECIES_NIDORAN_M;
        }
        if (eggSpecies == SPECIES_ILLUMISE && daycare->route5_offspringPersonality & EGG_GENDER_MALE)
        {
            eggSpecies = SPECIES_VOLBEAT;
        }

        // Make Ditto the "mother" slot if the other daycare mon is male.
        if (species[parentSlots[Father]] == SPECIES_DITTO && GetBoxMonGender(&daycare->route5_daycareMon[parentSlots[Mother]].mon) != MON_FEMALE)
        {
            u8 ditto = parentSlots[Father];
            parentSlots[Father] = parentSlots[Mother];
            parentSlots[Mother] = ditto;
        }
    }
    else
    {

        if (eggSpecies == SPECIES_NIDORAN_F && daycare->offspringPersonality & EGG_GENDER_MALE)
        {
            eggSpecies = SPECIES_NIDORAN_M;
        }
        if (eggSpecies == SPECIES_ILLUMISE && daycare->offspringPersonality & EGG_GENDER_MALE)
        {
            eggSpecies = SPECIES_VOLBEAT;
        }

        // Make Ditto the "mother" slot if the other daycare mon is male.
        if (species[parentSlots[Father]] == SPECIES_DITTO && GetBoxMonGender(&daycare->mons[parentSlots[Mother]].mon) != MON_FEMALE)
        {
            u8 ditto = parentSlots[Father];
            parentSlots[Father] = parentSlots[Mother];
            parentSlots[Mother] = ditto;
        }
    }

    return eggSpecies;
}

//triggered when at daycare picking up egg
static void _GiveEggFromDaycare(struct DayCare *daycare)
{
    struct Pokemon egg;
    u16 species;
    u8 parentSlots[DAYCARE_MON_COUNT];
    bool8 isEgg;

    species = DetermineEggSpeciesAndParentSlots(daycare, parentSlots);
    AlterEggSpeciesWithIncenseItem(&species, daycare);
    SetInitialEggData(&egg, species, daycare, parentSlots);
    InheritIVs(&egg, daycare);

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        BuildEggMoveset(&egg, &daycare->route5_daycareMon[parentSlots[Father]].mon, &daycare->route5_daycareMon[parentSlots[Mother]].mon);
    else
        BuildEggMoveset(&egg, &daycare->mons[parentSlots[Father]].mon, &daycare->mons[parentSlots[Mother]].mon);

    if (species == SPECIES_PICHU)
        GiveVoltTackleIfLightBall(&egg, daycare);

    isEgg = TRUE;
    SetMonData(&egg, MON_DATA_IS_EGG, &isEgg);
    gPlayerParty[PARTY_SIZE - 1] = egg;
    CompactPartySlots();
    CalculatePlayerPartyCount();
    RemoveEggFromDayCare(daycare);
}

//think this specific for r/s/e receiving egg event from lavaridge town
void CreateEgg(struct Pokemon *mon, u16 species, bool8 setHotSpringsLocation) 
{
    u8 metLevel,hatched;
    u16 ball;
    u8 language;
    u8 metLocation;
    u8 isEgg;

    CreateMon(mon, species, EGG_HATCH_LEVEL, 32, FALSE, 0, OT_ID_PLAYER_ID, 0);
    metLevel = EGG_HATCH_LEVEL;
    hatched = FALSE;
    ball = ITEM_POKE_BALL;
    language = LANGUAGE_JAPANESE;
    SetMonData(mon, MON_DATA_POKEBALL, &ball);
    SetMonData(mon, MON_DATA_NICKNAME, sJapaneseEggNickname);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &gBaseStats[species].eggCycles); //so this friendship based on egg cycles and friendship is then used for egg steps?
    SetMonData(mon, MON_DATA_MET_LEVEL, &metLevel);
    SetMonData(mon, MON_DATA_HATCHED, &hatched);
    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    if (setHotSpringsLocation)
    {
        metLocation = METLOC_SPECIAL_EGG;
        SetMonData(mon, MON_DATA_MET_LOCATION, &metLocation);
    }

    isEgg = TRUE;
    SetMonData(mon, MON_DATA_IS_EGG, &isEgg);
}

static void SetInitialEggData(struct Pokemon *mon, u16 species, struct DayCare *daycare, u8 *parentSlots) //seems daycare egg normal events?
{
    u32 personality;
    u16 ball;
    u8 metLevel,hatched;
    u8 language;
    u16 motherItem, fatherItem;
    u8 data;
    u16 monfilter[DAYCARE_MON_COUNT];
    u16 monitems[DAYCARE_MON_COUNT];
    u8 i;



    u16 MotherSpecies,FatherSpecies;// = GetMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_SPECIES, NULL);
    
    //motherItem = GetBoxMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_HELD_ITEM);
    //fatherItem = GetBoxMonData(&daycare->mons[parentSlots[Father]].mon, MON_DATA_HELD_ITEM);

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            monfilter[i] = GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_SPECIES);
            if (monfilter[i] == SPECIES_DITTO)
            {
                parentSlots[Mother] = i ^ 1;
                parentSlots[Father] = i;
            }
            else if (GetBoxMonGender(&daycare->route5_daycareMon[i].mon) == MON_FEMALE)
            {
                parentSlots[Mother] = i;
                parentSlots[Father] = i ^ 1;
            }
        }
        
        motherItem = GetBoxMonData(&daycare->route5_daycareMon[parentSlots[Mother]].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->route5_daycareMon[parentSlots[Father]].mon, MON_DATA_HELD_ITEM);

        MotherSpecies = GetMonData(&daycare->route5_daycareMon[parentSlots[Mother]].mon, MON_DATA_SPECIES, NULL);
        FatherSpecies = GetMonData(&daycare->route5_daycareMon[parentSlots[Father]].mon, MON_DATA_SPECIES, NULL);

        personality = daycare->route5_offspringPersonality | (Random() << 16);
    }
    else
    {

        // Determine which of the daycare mons is the mother and father of the egg.
        // The 0th index of the parentSlots array is considered the mother slot, and the
        // 1st index is the father slot.
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            monfilter[i] = GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES);
            if (monfilter[i] == SPECIES_DITTO)
            {
                parentSlots[Mother] = i ^ 1;
                parentSlots[Father] = i;
            }
            else if (GetBoxMonGender(&daycare->mons[i].mon) == MON_FEMALE)
            {
                parentSlots[Mother] = i;
                parentSlots[Father] = i ^ 1;
            }
        }
        
        motherItem = GetBoxMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_HELD_ITEM);
        fatherItem = GetBoxMonData(&daycare->mons[parentSlots[Father]].mon, MON_DATA_HELD_ITEM);

        MotherSpecies = GetMonData(&daycare->mons[parentSlots[Mother]].mon, MON_DATA_SPECIES, NULL);
        FatherSpecies = GetMonData(&daycare->mons[parentSlots[Father]].mon, MON_DATA_SPECIES, NULL);

        personality = daycare->offspringPersonality | (Random() << 16);
    }

    CreateMon(mon, species, EGG_HATCH_LEVEL, 32, TRUE, personality, OT_ID_PLAYER_ID, 0);
    metLevel = EGG_HATCH_LEVEL;
    hatched = FALSE;
    ball = ITEM_POKE_BALL;
    language = LANGUAGE_JAPANESE;
    SetMonData(mon, MON_DATA_POKEBALL, &ball);
    SetMonData(mon, MON_DATA_NICKNAME, sJapaneseEggNickname);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &gBaseStats[species].eggCycles);
    SetMonData(mon, MON_DATA_MET_LEVEL, &metLevel);
    SetMonData(mon, MON_DATA_HATCHED, &hatched);
    SetMonData(mon, MON_DATA_LANGUAGE, &language);

    //appears found issue, it was missing the logic that assigned daycare slots
    //based on gender etc. without that the slots are just the slots 0 and 1.
    //I was attempting to use the 0 slot when my form mon was in the 1 slot smh
    if (CheckFormViability(UseRegionSand(mon), motherItem))
    {
        switch(motherItem) //still to change, need set function to receive above and do switch itself
        {
            case ITEM_ALOLAN_SAND:
            data = ItemId_GetSecondaryId(motherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
            case ITEM_GALAR_SAND:
            data = ItemId_GetSecondaryId(motherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
            case ITEM_HISUIAN_SAND:
            data = ItemId_GetSecondaryId(motherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
            case ITEM_PALDEAN_SAND:
            data = ItemId_GetSecondaryId(motherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
        }
    }//think need to separate these into 2 separate functions for parents  so item doesn't pass when it shouldn't

    if (CheckFormViability(UseRegionSand(mon), fatherItem))
    {
        switch(fatherItem) //still to change, need set function to receive above and do switch itself
        {
            case ITEM_ALOLAN_SAND:
            data = ItemId_GetSecondaryId(fatherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
            case ITEM_GALAR_SAND:
            data = ItemId_GetSecondaryId(fatherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
            case ITEM_HISUIAN_SAND:
            data = ItemId_GetSecondaryId(fatherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
            case ITEM_PALDEAN_SAND:
            data = ItemId_GetSecondaryId(fatherItem);
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
            break;
        }
    }

    if (IsRegionalVariant(MotherSpecies)
    && !IsRegionalVariant(GetEggSpecies(MotherSpecies)))
    {
        data = gBaseStats[MotherSpecies].flags;
        SetMonData(mon, MON_DATA_FORM_FLAG, &data);
    } //appears to be working,

    if (MotherSpecies != FatherSpecies
    && (IsSameSpeciesFamily(MotherSpecies, FatherSpecies))) //ok got it now smh
    {   
        if (IsRegionalVariant(FatherSpecies)
        && !IsRegionalVariant(MotherSpecies))
        {
            data = gBaseStats[FatherSpecies].flags;
            SetMonData(mon, MON_DATA_FORM_FLAG, &data);
        }
    }//ok this isn't right, for this to work it'd need to check entire evo like regiion sand does
    //sigh welp time to make a new function smh
    //same evo family
    //same species family
    //if source is in same family as comparison return true
    //use regionsand logic for doing evo loop
    //I FORGOT TO DEFINE FATHER SPECIES YOU DONKEY!!!
    
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        if (monfilter[parentSlots[Father]] == SPECIES_DITTO && GetBoxMonGender(&daycare->route5_daycareMon[parentSlots[Mother]].mon) != MON_FEMALE)
        {
            u8 ditto = parentSlots[Father];
            parentSlots[Father] = parentSlots[Mother];
            parentSlots[Mother] = ditto;
        }
    }
    else
    {
        // Make Ditto the "mother" slot if the other daycare mon is male.
        if (monfilter[parentSlots[Father]] == SPECIES_DITTO && GetBoxMonGender(&daycare->mons[parentSlots[Mother]].mon) != MON_FEMALE)
        {
            u8 ditto = parentSlots[Father];
            parentSlots[Father] = parentSlots[Mother];
            parentSlots[Mother] = ditto;
        }
    }
    

    //if mother species is variant but egg would not be auto set flag to evolve into variant
   //fuck this actually worked,so the entire time I was loading the wrong mon?
  //yup I'm a fucking idiot, top day care spot is 0, bottom slot is 1,
  //without the logic swaps around the slot from the other function it only reads it that way,
  //and I had raihcu in the second slot so it needed the father tag smh, need to figure better way for this

}

void GiveEggFromDaycare(void)
{
    _GiveEggFromDaycare(&gSaveBlock1Ptr->daycare);
}

static bool8 CheckRoute5Daycare(struct DayCare *daycare)
{
    u32 i, validEggs = 0;

    for (i = 0; i < DAYCARE_MON_COUNT; i++)
    {
        if (GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_SANITY_HAS_SPECIES))
            daycare->route5_daycareMon[i].steps++, validEggs++;
    }

    if (daycare->route5_offspringPersonality == 0 && validEggs == DAYCARE_MON_COUNT)// && (*ptr == 0)) //(daycare->mons[1].steps & 0xFF) == 0xFF)
    {
        u8 compatibility = GetRoute5DaycareCompatibilityScore(daycare);

        //should equate to, can produce egg, and no egg waiting, increase timer
        if (compatibility != 0)
        {    
            daycare->route5_eggTimer++;
            

            if (daycare->route5_eggTimer >= (400 / compatibility))
            {    
                TriggerPendingRoute5DaycareEgg();//think can make daycare item clear function
                //to clear effect of compatibility item
                //or could trigger after a certain number of eggs
                //if do that way would also need a clear in function that removes mon from daycare
                //also ofspringPersonality value is filter for if an egg is not alraedy wating
                

            }
        }
    }
}

static bool8 TryProduceOrHatchEgg(struct DayCare *daycare)
{
    u32 i, validEggs = 0;
    u8 fireBoost = FALSE;
    //u32 *ptr;

    for (i = 0; i < DAYCARE_MON_COUNT; i++)
    {
        if (GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SANITY_HAS_SPECIES))
            daycare->mons[i].steps++, validEggs++;
    }//valid eggs here seems to just mean you have 2 mon in daycare
    //actually think this is also adding the exp for mon in daycare?
    //yeah this is the only place where steps gets incremented...

    //can make route5 equivalent of this function that does, above, and attempt egg produce
    CheckRoute5Daycare(daycare);


    //taken from poison counter attempted use here
    //ptr = &(daycare->mons[1].steps); //had to remove, believe it was actuall changing daycare value not just pointer stored value
    //    (*ptr) = 0;
        //(*ptr)++;
        //(*ptr) %= 5;    //wrap around value
        //if (*ptr == 0)//when the counter wraps around to do the effect
    //this function is in same place as poison counter, believe its checked each step
    //so think above should work?

    // Check if an egg should be produced
    //if understand correctly all the conditions except steps should be met after loop above finishes,
    //so I think the function needs to be triggered multiple times before it actually attempts to produce an egg?
    //which maes sense since before the function operated on odds, of course it had multiple triggers
    //if right it had multiple delays built in, have to wait for steps to get high enough,
    //and then also have to wait for rng to line up, on top of forced low compatibility slowing things down further
    //removed extra filter value, so now directly tied to steps doesn't require overlap.
    //with that compatibility item would directly affect egg production time
    if (daycare->offspringPersonality == 0 && validEggs == DAYCARE_MON_COUNT)// && (*ptr == 0)) //(daycare->mons[1].steps & 0xFF) == 0xFF)
    {
        u8 compatibility = GetDaycareCompatibilityScore(daycare);

        //should equate to, can produce egg, and no egg waiting, increase timer
        if (compatibility != 0)
        {    
            daycare->eggTimer++;

            //if (daycare->boost == TRUE)
            //?? ok doing this made it actually work, apparently it was somehow returning a value other than 0 or 1???
            //I can only assume void functions are different and I was somehow retruning the function address?
            //daycare->boost = TRUE;
            
            if (CheckIfBoostApplied() == TRUE) 
                compatibility = (PARENTS_MAX_COMPATIBILITY * 2); 

            if (daycare->eggTimer >= (400 / compatibility))
            {    
                TriggerPendingDaycareEgg();//think can make daycare item clear function
                //to clear effect of compatibility item
                //or could trigger after a certain number of eggs
                //if do that way would also need a clear in function that removes mon from daycare
                //also ofspringPersonality value is filter for if an egg is not alraedy wating
                

            }
            //believe discovered issue, think it was removal of this line (daycare->mons[1].steps & 0xFF) == 0xFF
            //hmm or may be making it based on steps, since I'm not resetting steps,
            //it would always be greater than compatibility once triggered...
            //so each additional step...would generate a new egg
        //if (compatibility > (Random() * 100u) / USHRT_MAX)
            //TriggerPendingDaycareEgg();
        }
        //idk what's goingn game seems to be lagging  whenever I have a mon in daycare
        //more for 2 mon?  no idea why this is suddenly happening,
        //from what I can tell its NOT when an egg is produced
        //seems to happen more intensily if 2 mon in daycare/more mon in daycare
        //and doesn't appear to be tied to mon in daycare leveling up?
        //ok checked with task manager seems to coincide with a large cpu usage spike...
        //ok I'm gonna GUESS that its when mon is gaining exp?
        //I copied pc exp gain logic from daycare exp? I think
        //so its possible its lagging when both pc mon and daycare mon need to gain exp?
        //idk if that's right since everything should be on separate timers.
        //need get someon else to do a test

        //...wait ok so it lags even without a mon in daycare, or an egg in party.
    }

    //check party for mon boosts egg hatch speed
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (GetMonAbility(&gPlayerParty[i]) == ABILITY_FLAME_BODY
        || GetMonAbility(&gPlayerParty[i]) == ABILITY_MAGMA_ARMOR
        || GetMonAbility(&gPlayerParty[i]) == ABILITY_STEAM_ENGINE
        || GetMonAbility(&gPlayerParty[i]) == ABILITY_RISING_PHOENIX)
            fireBoost = TRUE;
        if (IsMonType(&gPlayerParty[i], TYPE_FIRE))
            fireBoost = TRUE;

        if (fireBoost)
            break;
    }

    // Hatch Egg
    if (++daycare->stepCounter == 255) //ok so seems steps is mon friendship, but only decrements every 255 steps?
    {
        s32 steps; //changed to s, over u, since my fix broke things, and could jump passed 0 and reset

        for (i = 0; i < gPlayerPartyCount; i++)
        {
            if (!GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
                continue;

            steps = GetMonData(&gPlayerParty[i], MON_DATA_FRIENDSHIP);
            if (steps != 0)
            {
                if (fireBoost)
                    steps -= 7; //extra boost 
                else
                    steps -= 3;
                SetMonData(&gPlayerParty[i], MON_DATA_FRIENDSHIP, &steps); //says friendship but its actually egg cycle, already assigned at egg creation
            }
            if (steps <= 0) // hatch the egg  //because this uses else, it forces you to go through another cycle before it can hatch the egg, so removing that
            {
                gSpecialVar_0x8004 = i;
                return TRUE;
            }
        }

    }

    return FALSE; // no hatching
}

bool8 ShouldEggHatch(void) //need figure what route5 stuff is doing
{
    //with new setup can remove conditional, and just put incrememnt in above function tryproduce or hatch
    //if (GetBoxMonData(&gSaveBlock1Ptr->route5DayCareMon.mon, MON_DATA_SANITY_HAS_SPECIES))
    //    gSaveBlock1Ptr->route5DayCareMon.steps++;   //this appears to not be used for anything?, ok name isn't used but its passed to daycaremon
    return TryProduceOrHatchEgg(&gSaveBlock1Ptr->daycare); //and believe used to store exp gain for single mon in route 5 daycare
}

static bool8 IsEggPending(struct DayCare *daycare)
{
    return (daycare->offspringPersonality != 0);
}

static bool8 IsRoute5EggPending(struct DayCare *daycare)
{
    return (daycare->route5_offspringPersonality != 0);
}

// gStringVar1 = first mon's nickname
// gStringVar2 = second mon's nickname
// gStringVar3 = first mon trainer's name
static void _GetDaycareMonNicknames(struct DayCare *daycare)
{
    u8 text[12];
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        if (GetBoxMonData(&daycare->route5_daycareMon[0].mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            DayCare_GetBoxMonNickname(&daycare->route5_daycareMon[0].mon, gStringVar1);
            GetBoxMonData(&daycare->route5_daycareMon[0].mon, MON_DATA_OT_NAME, text);
            StringCopy(gStringVar3, text);
        }

        if (GetBoxMonData(&daycare->route5_daycareMon[1].mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            DayCare_GetBoxMonNickname(&daycare->route5_daycareMon[1].mon, gStringVar2);
        }
    }
    else
    {
        if (GetBoxMonData(&daycare->mons[0].mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            DayCare_GetBoxMonNickname(&daycare->mons[0].mon, gStringVar1);
            GetBoxMonData(&daycare->mons[0].mon, MON_DATA_OT_NAME, text);
            StringCopy(gStringVar3, text);
        }

        if (GetBoxMonData(&daycare->mons[1].mon, MON_DATA_SPECIES) != SPECIES_NONE)
        {
            DayCare_GetBoxMonNickname(&daycare->mons[1].mon, gStringVar2);
        }
    }
}

//believe this doesn't run through get species name
//so may not do proper caps? vsonic important
u16 GetSelectedMonNicknameAndSpecies(void)
{
    //DayCare_GetBoxMonNickname(&gPlayerParty[GetCursorSelectionMonId()].box, gStringVar1);
    //return GetBoxMonData(&gPlayerParty[GetCursorSelectionMonId()].box, MON_DATA_SPECIES);

     if(GetInPartyMenu()!=0){
        DayCare_GetBoxMonNickname(&gPlayerParty[GetBoxCursorPosition()].box, gStringVar1);
        return GetBoxMonData(&gPlayerParty[GetBoxCursorPosition()].box, MON_DATA_SPECIES);
    }
    DayCare_GetBoxMonNickname(&gPokemonStoragePtr->boxes[StorageGetCurrentBox()][GetBoxCursorPosition()], gStringVar1);
    return GetBoxMonData(&gPokemonStoragePtr->boxes[StorageGetCurrentBox()][GetBoxCursorPosition()], MON_DATA_SPECIES);
}

void GetDaycareMonNicknames(void)
{
    _GetDaycareMonNicknames(&gSaveBlock1Ptr->daycare);
}

static u8 GetRoute5DaycarePokemonCount(void)
{
    struct DayCare *daycare;

    u8 ret = CountPokemonInDaycare(&gSaveBlock1Ptr->daycare);
    if (ret)
        return ret;

    daycare = &gSaveBlock1Ptr->daycare;
    
    daycare->route5_eggTimer = FALSE;            //mostly just as an extra pre-caution to ensure there's no garbage data
    
    return 0;
}

static u8 GetDaycarePokemonCount(void)
{
    struct DayCare *daycare;

    u8 ret = CountPokemonInDaycare(&gSaveBlock1Ptr->daycare);
    if (ret)
        return ret;

    daycare = &gSaveBlock1Ptr->daycare;
    
    daycare->boost = FALSE; //this function refers to a special, that appears to not be used
    daycare->eggCount = FALSE;            //the setup for this is convenient, will use in place of nummons above so can set boost to false
    daycare->eggTimer = FALSE;            //mostly just as an extra pre-caution to ensure there's no garbage data
    
    return 0;
} //since changed and using here, removed from specials list

u8 GetDaycareState(void)
{
    //struct DayCare *daycare;
    u8 numMons;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        if (IsRoute5EggPending(&gSaveBlock1Ptr->daycare))
        {
            return DAYCARE_EGG_WAITING;
        }

        //numMons = CountPokemonInDaycare(&gSaveBlock1Ptr->daycare);
        numMons = GetRoute5DaycarePokemonCount();
    }
    else
    {

    
        if (IsEggPending(&gSaveBlock1Ptr->daycare))
        {
            return DAYCARE_EGG_WAITING;
        }

        //numMons = CountPokemonInDaycare(&gSaveBlock1Ptr->daycare);
        numMons = GetDaycarePokemonCount();
    }

    if (numMons != 0)
    {
        return numMons + 1; // DAYCARE_ONE_MON or DAYCARE_TWO_MONS
    }




    return DAYCARE_NO_MONS;
}//special is triggered by daycare man, and daycare woman



//will need to have context with text scripts the old daycare lady says
//so think will need a special to check for if boost is set
bool8 SetEggBoost(void) //doesn't work, for some reason doesn't set value
{
    struct DayCare *daycare;
    daycare = &gSaveBlock1Ptr->daycare;

    //will turn into a special to trigger from script,
    //replace GetDaycarePokemonCount special
    //if mon can produce egg, i.e compatibility not 0, set boost
    daycare->boost = TRUE;

    if (daycare->boost == TRUE)
    {
        return TRUE;
    }

    return FALSE;

}//for some reason boost isn't being applied or at least not recognized?

bool8 CheckCanProduceEggs(void) //works
{
    if (GetDaycareCompatibilityScore(&gSaveBlock1Ptr->daycare))
        return TRUE;
    
    return FALSE;
    //return GetDaycareCompatibilityScore(&gSaveBlock1Ptr->daycare); //can't do liek this, special cant read state
}

bool8 CheckIfBoostApplied(void) //doesn't work, always returns true, no matter what condition I set??
{
    struct DayCare *daycare;
    daycare = &gSaveBlock1Ptr->daycare;

    if (daycare->boost == TRUE)
        return TRUE;

    return FALSE;
}//fixed issue was syntax used, for some reason not saying function() == true, made it return a non 0 or 1 value?

void SetDaycareServiceCost(void) //works
{
    u32 cost;

    cost = 700;
    ConvertIntToDecimalStringN(gStringVar2, cost, STR_CONV_MODE_LEFT_ALIGN, 5);
    gSpecialVar_0x8005 = cost;
}

// Determine if the two given egg group lists contain any of the
// same egg groups.
static bool8 EggGroupsOverlap(u16 *eggGroups1, u16 *eggGroups2)
{
    s32 i, j;

    for (i = 0; i < EGG_GROUPS_PER_MON; i++)
    {
        for (j = 0; j < EGG_GROUPS_PER_MON; j++)
        {
            if (eggGroups1[i] == eggGroups2[j])
                return TRUE;
        }
    }

    return FALSE;
}

static u8 GetRoute5DaycareCompatibilityScore(struct DayCare *daycare)
{
    u32 i;
    u16 eggGroups[DAYCARE_MON_COUNT][EGG_GROUPS_PER_MON];
    u16 species[DAYCARE_MON_COUNT];
    u32 trainerIds[DAYCARE_MON_COUNT];
    u32 genders[DAYCARE_MON_COUNT];
    u8 compatibility;
    
    for (i = 0; i < DAYCARE_MON_COUNT; i++)
    {
        u32 personality;

        species[i] = GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_SPECIES);
        trainerIds[i] = GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_OT_ID);
        personality = GetBoxMonData(&daycare->route5_daycareMon[i].mon, MON_DATA_PERSONALITY);
        genders[i] = GetGenderFromSpeciesAndPersonality(species[i], personality);
        eggGroups[i][0] = gBaseStats[species[i]].eggGroup1;
        eggGroups[i][1] = gBaseStats[species[i]].eggGroup2;
    }

    // check unbreedable egg group
    if (eggGroups[0][0] == EGG_GROUP_UNDISCOVERED || eggGroups[1][0] == EGG_GROUP_UNDISCOVERED)
        return PARENTS_INCOMPATIBLE;
    // two Ditto can't breed
    if (eggGroups[0][0] == EGG_GROUP_DITTO && eggGroups[1][0] == EGG_GROUP_DITTO)
        return PARENTS_INCOMPATIBLE;

    // one parent is Ditto
    if (eggGroups[0][0] == EGG_GROUP_DITTO || eggGroups[1][0] == EGG_GROUP_DITTO)
    {
        if (trainerIds[0] == trainerIds[1]) //can't trade in hack, plus dumb to make that a factor for system already clunky
            compatibility = PARENTS_LOW_COMPATIBILITY;
        else
            compatibility = PARENTS_LOW_COMPATIBILITY;   //made identical, changed ditto to be low compat option, since it otherwise works with everyone
    }
    // neither parent is Ditto
    else
    {
        if (genders[0] == genders[1])
            return PARENTS_INCOMPATIBLE;
        if (genders[0] == MON_GENDERLESS || genders[1] == MON_GENDERLESS)
            return PARENTS_INCOMPATIBLE;
        if (!EggGroupsOverlap(eggGroups[0], eggGroups[1]))
            return PARENTS_INCOMPATIBLE;

        //if (species[0] == species[1]) //could change this here, to be same speciesfamily
        if (IsSameSpeciesFamily(species[0],species[1]))
        {
            if (trainerIds[0] == trainerIds[1])
                compatibility = PARENTS_MAX_COMPATIBILITY; // same species, same trainer
            else
                compatibility = PARENTS_MAX_COMPATIBILITY; // same species, different trainers
        }
        else
        {
            if (trainerIds[0] != trainerIds[1])
                compatibility = PARENTS_MED_COMPATIBILITY; // different species, different trainers
            else
                compatibility = PARENTS_MED_COMPATIBILITY; // different species, same trainer
        }
    }

    //new idea for quick breeding, setup function for new effect
    //can give day care man an item, to pass to pokemon,
    //oh you have a gift for your pokemon? Why I'm sure they'll enjoy this!
    //can have two variants, but main idea is an item that will greatly speed up egg production time
    //for cases where your only goal is making an egg, and you don't have something else to do
    //what will do is set compatibility to hgih compatibility x 10  should make an egg produce in 5 steps?
    //double check how steps work, may not be how I want/ think it uses a wrap around value?
    
    //if (daycare->boost == TRUE)
    //    compatibility = (PARENTS_MAX_COMPATIBILITY * 2);  //should generate egg every 16 steps, enough space to change mon if needed
    
    //this is the effect but will make function that does this
    //ok made function still need setup proper condition to track
    //from selection in daycare script, right now its just always on

    //other idea is an item that would speed up exp gain, but idk that's not very accurate so may table that

    return compatibility;
}
//sped up egg generation, works
//think for that need change how compatibility is assigned
u8 GetDaycareCompatibilityScore(struct DayCare *daycare)
{
    u32 i;
    u16 eggGroups[DAYCARE_MON_COUNT][EGG_GROUPS_PER_MON];
    u16 species[DAYCARE_MON_COUNT];
    u32 trainerIds[DAYCARE_MON_COUNT];
    u32 genders[DAYCARE_MON_COUNT];
    u8 compatibility;
    
    for (i = 0; i < DAYCARE_MON_COUNT; i++)
    {
        u32 personality;

        species[i] = GetBoxMonData(&daycare->mons[i].mon, MON_DATA_SPECIES);
        trainerIds[i] = GetBoxMonData(&daycare->mons[i].mon, MON_DATA_OT_ID);
        personality = GetBoxMonData(&daycare->mons[i].mon, MON_DATA_PERSONALITY);
        genders[i] = GetGenderFromSpeciesAndPersonality(species[i], personality);
        eggGroups[i][0] = gBaseStats[species[i]].eggGroup1;
        eggGroups[i][1] = gBaseStats[species[i]].eggGroup2;
    }

    // check unbreedable egg group
    if (eggGroups[0][0] == EGG_GROUP_UNDISCOVERED || eggGroups[1][0] == EGG_GROUP_UNDISCOVERED)
        return PARENTS_INCOMPATIBLE;
    // two Ditto can't breed
    if (eggGroups[0][0] == EGG_GROUP_DITTO && eggGroups[1][0] == EGG_GROUP_DITTO)
        return PARENTS_INCOMPATIBLE;

    // one parent is Ditto
    if (eggGroups[0][0] == EGG_GROUP_DITTO || eggGroups[1][0] == EGG_GROUP_DITTO)
    {
        if (trainerIds[0] == trainerIds[1]) //can't trade in hack, plus dumb to make that a factor for system already clunky
            compatibility = PARENTS_LOW_COMPATIBILITY;
        else
            compatibility = PARENTS_LOW_COMPATIBILITY;   //made identical, changed ditto to be low compat option, since it otherwise works with everyone
    }
    // neither parent is Ditto
    else
    {
        if (genders[0] == genders[1])
            return PARENTS_INCOMPATIBLE;
        if (genders[0] == MON_GENDERLESS || genders[1] == MON_GENDERLESS)
            return PARENTS_INCOMPATIBLE;
        if (!EggGroupsOverlap(eggGroups[0], eggGroups[1]))
            return PARENTS_INCOMPATIBLE;

        //if (species[0] == species[1]) //could change this here, to be same speciesfamily
        if (IsSameSpeciesFamily(species[0],species[1]))
        {
            if (trainerIds[0] == trainerIds[1])
                compatibility = PARENTS_MAX_COMPATIBILITY; // same species, same trainer
            else
                compatibility = PARENTS_MAX_COMPATIBILITY; // same species, different trainers
        }
        else
        {
            if (trainerIds[0] != trainerIds[1])
                compatibility = PARENTS_MED_COMPATIBILITY; // different species, different trainers
            else
                compatibility = PARENTS_MED_COMPATIBILITY; // different species, same trainer
        }
    }

    //new idea for quick breeding, setup function for new effect
    //can give day care man an item, to pass to pokemon,
    //oh you have a gift for your pokemon? Why I'm sure they'll enjoy this!
    //can have two variants, but main idea is an item that will greatly speed up egg production time
    //for cases where your only goal is making an egg, and you don't have something else to do
    //what will do is set compatibility to hgih compatibility x 10  should make an egg produce in 5 steps?
    //double check how steps work, may not be how I want/ think it uses a wrap around value?
    
    //if (daycare->boost == TRUE)
    //    compatibility = (PARENTS_MAX_COMPATIBILITY * 2);  //should generate egg every 16 steps, enough space to change mon if needed
    
    //this is the effect but will make function that does this
    //ok made function still need setup proper condition to track
    //from selection in daycare script, right now its just always on

    //other idea is an item that would speed up exp gain, but idk that's not very accurate so may table that

    return compatibility;
}

static u8 GetDaycareCompatibilityScoreFromSave(void)
{
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        return GetRoute5DaycareCompatibilityScore(&gSaveBlock1Ptr->daycare);
    else
        return GetDaycareCompatibilityScore(&gSaveBlock1Ptr->daycare);
}

void SetDaycareCompatibilityString(void)
{
    struct DayCare *daycare;
    u8 whichString;
    u8 relationshipScore;

    relationshipScore = GetDaycareCompatibilityScoreFromSave();

    //if (CheckIfBoostApplied)
    if (CheckIfBoostApplied() == TRUE)
        relationshipScore = (PARENTS_MAX_COMPATIBILITY * 2); 

    whichString = 0;
    if (relationshipScore == PARENTS_INCOMPATIBLE)
        whichString = 4;
    if (relationshipScore == PARENTS_LOW_COMPATIBILITY)
        whichString = 3;
    if (relationshipScore == PARENTS_MED_COMPATIBILITY)
        whichString = 2;
    if (relationshipScore == PARENTS_MAX_COMPATIBILITY)
        whichString = 1;

    StringCopy(gStringVar4, sCompatibilityMessages[whichString]);
}

bool8 NameHasGenderSymbol(const u8 *name, u8 genderRatio)
{
    u8 i;
    u8 symbolsCount[GENDER_COUNT];
    symbolsCount[MALE] = symbolsCount[FEMALE] = 0;

    for (i = 0; name[i] != EOS; i++)
    {
        if (name[i] == CHAR_MALE)
            symbolsCount[MALE]++;
        if (name[i] == CHAR_FEMALE)
            symbolsCount[FEMALE]++;
    }

    if (genderRatio == MON_MALE   && symbolsCount[MALE] != 0 && symbolsCount[FEMALE] == 0)
        return TRUE;
    if (genderRatio == MON_FEMALE && symbolsCount[FEMALE] != 0 && symbolsCount[MALE] == 0)
        return TRUE;

    return FALSE;
}

static u8 *AppendGenderSymbol(u8 *name, u8 gender)
{
    if (gender == MON_MALE)
    {
        if (!NameHasGenderSymbol(name, MON_MALE))
            return StringAppend(name, gText_MaleSymbol4);
    }
    else if (gender == MON_FEMALE)
    {
        if (!NameHasGenderSymbol(name, MON_FEMALE))
            return StringAppend(name, gText_FemaleSymbol4);
    }

    return StringAppend(name, gText_GenderlessSymbol);
}

static u8 *AppendMonGenderSymbol(u8 *name, struct BoxPokemon *boxMon)
{
    return AppendGenderSymbol(name, GetBoxMonGender(boxMon));
}

//VSONIC
static void GetDaycareLevelMenuText(struct DayCare *daycare, u8 *dest)
{
    u8 monNames[DAYCARE_MON_COUNT][POKEMON_NAME_BUFFER_SIZE];
    u8 i;

    *dest = EOS;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            DayCare_GetBoxMonNickname(&daycare->route5_daycareMon[i].mon, monNames[i]);
            AppendMonGenderSymbol(monNames[i], &daycare->route5_daycareMon[i].mon);
        }
    }
    else
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            DayCare_GetBoxMonNickname(&daycare->mons[i].mon, monNames[i]);
            AppendMonGenderSymbol(monNames[i], &daycare->mons[i].mon);
        }
    }

    StringCopy(dest, monNames[0]);
    StringAppend(dest, sNewLineText);
    StringAppend(dest, monNames[1]);
    StringAppend(dest, sNewLineText);
    StringAppend(dest, gOtherText_Exit);
}

static void GetDaycareLevelMenuLevelText(struct DayCare *daycare, u8 *dest)
{
    u8 i;
    u8 level;
    u8 text[POKEMON_NAME_BUFFER_SIZE];

    *dest = EOS;

    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            StringAppend(dest, gText_Lv);
            level = GetLevelAfterDaycareSteps(&daycare->route5_daycareMon[i].mon, daycare->route5_daycareMon[i].steps);
            ConvertIntToDecimalStringN(text, level, STR_CONV_MODE_LEFT_ALIGN, 3);
            StringAppend(dest, text);
            StringAppend(dest, sNewLineText);
        }
    }
    else
    {
        for (i = 0; i < DAYCARE_MON_COUNT; i++)
        {
            StringAppend(dest, gText_Lv);
            level = GetLevelAfterDaycareSteps(&daycare->mons[i].mon, daycare->mons[i].steps);
            ConvertIntToDecimalStringN(text, level, STR_CONV_MODE_LEFT_ALIGN, 3);
            StringAppend(dest, text);
            StringAppend(dest, sNewLineText);
        }
    }
}

static void DaycareAddTextPrinter(u8 windowId, const u8 *text, u32 x, u32 y)
{
    struct TextPrinterTemplate printer;

    printer.currentChar = text;
    printer.windowId = windowId;
    printer.fontId = 3;
    printer.x = x;
    printer.y = y;
    printer.currentX = x;
    printer.currentY = y;
    printer.unk = 0;
    gTextFlags.useAlternateDownArrow = 0;
    printer.letterSpacing = 0;
    printer.lineSpacing = 1;
    printer.fgColor = 2;
    printer.bgColor = 1;
    printer.shadowColor = 3;

    AddTextPrinter(&printer, 0xFF, NULL);
}

static void DaycarePrintMonNickname(struct DayCare *daycare, u8 windowId, u32 daycareSlotId, u32 y)
{
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
    {
        DayCare_GetBoxMonNickname(&daycare->route5_daycareMon[daycareSlotId].mon, nickname);
        AppendMonGenderSymbol(nickname, &daycare->route5_daycareMon[daycareSlotId].mon);
    }
    else
    {
        DayCare_GetBoxMonNickname(&daycare->mons[daycareSlotId].mon, nickname);
        AppendMonGenderSymbol(nickname, &daycare->mons[daycareSlotId].mon);
    }
    
    DaycareAddTextPrinter(windowId, nickname, 8, y);
}

static void DaycarePrintMonLvl(struct DayCare *daycare, u8 windowId, u32 daycareSlotId, u32 y)
{
    u8 level;
    u32 x;
    u8 lvlText[12];
    u8 intText[8];

#if REVISION == 0
    strcpy((char *)lvlText, (const char *)gText_Lv);
#else
    StringCopy(lvlText, gText_Lv);
#endif
    if (VarGet(VAR_PLAYER_AT_ROUTE5_DAYCARE) == TRUE)
        level = GetLevelAfterDaycareSteps(&daycare->route5_daycareMon[daycareSlotId].mon, daycare->route5_daycareMon[daycareSlotId].steps);
    else
        level = GetLevelAfterDaycareSteps(&daycare->mons[daycareSlotId].mon, daycare->mons[daycareSlotId].steps);
    ConvertIntToDecimalStringN(intText, level, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(lvlText, intText);
    x = 132 - GetStringWidth(3, lvlText, 0);
    DaycareAddTextPrinter(windowId, lvlText, x, y);
}

static void DaycarePrintMonInfo(u8 windowId, s32 daycareSlotId, u8 y)
{
    if (daycareSlotId < (unsigned) DAYCARE_MON_COUNT)
    {
        DaycarePrintMonNickname(&gSaveBlock1Ptr->daycare, windowId, daycareSlotId, y);
        DaycarePrintMonLvl(&gSaveBlock1Ptr->daycare, windowId, daycareSlotId, y);
    }
}

#define tMenuListTaskId     data[0]
#define tWindowId           data[1]

static void Task_HandleDaycareLevelMenuInput(u8 taskId)
{
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuListTaskId, DEFAULT_MODE);

    if (gMain.newKeys & A_BUTTON)
    {
        switch (input)
        {
        case 0:
        case 1:
            gSpecialVar_Result = input;
            break;
        case DAYCARE_LEVEL_MENU_EXIT:
            gSpecialVar_Result = DAYCARE_EXITED_LEVEL_MENU;
            break;
        }
        DestroyListMenuTask(gTasks[taskId].tMenuListTaskId, NULL, NULL);
        ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
        RemoveWindow(gTasks[taskId].tWindowId);
        DestroyTask(taskId);
        EnableBothScriptContexts();
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        gSpecialVar_Result = DAYCARE_EXITED_LEVEL_MENU;
        DestroyListMenuTask(gTasks[taskId].tMenuListTaskId, NULL, NULL);
        ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
        RemoveWindow(gTasks[taskId].tWindowId);
        DestroyTask(taskId);
        EnableBothScriptContexts();
    }
}

void ShowDaycareLevelMenu(void)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 listMenuTaskId;
    u8 daycareMenuTaskId;

    windowId = AddWindow(&sDaycareLevelMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    menuTemplate = sDaycareListMenuLevelTemplate;
    menuTemplate.windowId = windowId;
    listMenuTaskId = ListMenuInit(&menuTemplate, 0, 0, DEFAULT_MODE);

    CopyWindowToVram(windowId, COPYWIN_BOTH);

    daycareMenuTaskId = CreateTask(Task_HandleDaycareLevelMenuInput, 3);
    gTasks[daycareMenuTaskId].tMenuListTaskId = listMenuTaskId;
    gTasks[daycareMenuTaskId].tWindowId = windowId;
}

#undef tMenuListTaskId
#undef tWindowId

void ChooseSendDaycareMon(void)
{
    ChooseMonForDaycare();
    gMain.savedCallback = CB2_ReturnToField;
}

// Route 5 Daycare
//VSONIC    -no longer used
void PutMonInRoute5Daycare(void)
{
    u8 monIdx = GetCursorSelectionMonId();
    //StorePokemonInDaycare(&gPlayerParty[monIdx], &gSaveBlock1Ptr->route5DayCareMon);
    StorePokemonInDaycare(&gPlayerParty[monIdx], &gSaveBlock1Ptr->daycare.route5_daycareMon[0]);
}

void GetCostToWithdrawRoute5DaycareMon(void)
{
    u16 cost = GetDaycareCostForSelectedMon(&gSaveBlock1Ptr->daycare.route5_daycareMon[0]);
    gSpecialVar_0x8005 = cost;
}

//this all works
//put single mon in, everything populated, and was able to retreive mon no problem
bool8 IsThereMonInRoute5Daycare(void)
{
    //if (GetBoxMonData(&gSaveBlock1Ptr->route5DayCareMon.mon, MON_DATA_SPECIES) != SPECIES_NONE)
    //    return TRUE;

    if (GetBoxMonData(&gSaveBlock1Ptr->daycare.route5_daycareMon[0].mon, MON_DATA_SPECIES) != SPECIES_NONE)
        return TRUE;

    return FALSE;
}//route5_daycareMon

//VSONIC
u8 GetNumLevelsGainedForRoute5DaycareMon(void)
{
    return GetNumLevelsGainedForDaycareMon(&gSaveBlock1Ptr->daycare.route5_daycareMon[0]);
}

u16 TakePokemonFromRoute5Daycare(void)
{
    return TakeSelectedPokemonFromDaycare(&gSaveBlock1Ptr->daycare.route5_daycareMon[0]);
}

static void CreatedHatchedMon(struct Pokemon *egg, struct Pokemon *temp)
{
    u16 species;
    u32 personality, pokerus;
    u8 i, friendship, language, gameMet, markings, formFlag;
    u16 moves[4];
    u32 ivs[NUM_STATS];
    u8 hatched = TRUE;


    species = GetMonData(egg, MON_DATA_SPECIES);

    for (i = 0; i < 4; i++)
    {
        moves[i] = GetMonData(egg, MON_DATA_MOVE1 + i);
    }

    personality = GetMonData(egg, MON_DATA_PERSONALITY);

    for (i = 0; i < NUM_STATS; i++)
    {
        ivs[i] = GetMonData(egg, MON_DATA_HP_IV + i);
    }

//    language = GetMonData(egg, MON_DATA_LANGUAGE);
    gameMet = GetMonData(egg, MON_DATA_MET_GAME);
    //markings = GetMonData(egg, MON_DATA_MARKINGS);
    pokerus = GetMonData(egg, MON_DATA_POKERUS);
    //isEventLegal = GetMonData(egg, MON_DATA_EVENT_LEGAL);
    formFlag = GetMonData(egg, MON_DATA_FORM_FLAG);

    CreateMon(temp, species, EGG_HATCH_LEVEL, 32, TRUE, personality, 0, 0);

    for (i = 0; i < 4; i++)
    {
        SetMonData(temp, MON_DATA_MOVE1 + i,  &moves[i]);
    }

    for (i = 0; i < NUM_STATS; i++)
    {
        SetMonData(temp, MON_DATA_HP_IV + i,  &ivs[i]);
    }

    language = GAME_LANGUAGE;
    SetMonData(temp, MON_DATA_LANGUAGE, &language);
    SetMonData(temp, MON_DATA_MET_GAME, &gameMet);
    //SetMonData(temp, MON_DATA_MARKINGS, &markings);

    friendship = 40; //missed this, as part of friendship revamp.
    SetMonData(temp, MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(temp, MON_DATA_POKERUS, &pokerus);
    //SetMonData(temp, MON_DATA_EVENT_LEGAL, &isEventLegal);

    SetMonData(temp, MON_DATA_HATCHED, &hatched);
    SetMonData(temp, MON_DATA_FORM_FLAG, &formFlag); //ASSUMIGN this was issue, wasn't passing value

    *egg = *temp;
}

static void AddHatchedMonToParty(u8 id)
{
    u8 isEgg = 0x46; // ?       despite not being 0, this works for checking if hatched mon is not egg
    u16 pokeNum;
    u8 name[12];
    u16 ball;
    u16 caughtLvl;
    u8 mapNameID;
    struct Pokemon* mon = &gPlayerParty[id];

    CreatedHatchedMon(mon, &gEnemyParty[0]);
    SetMonData(mon, MON_DATA_IS_EGG, &isEgg);

    pokeNum = GetMonData(mon, MON_DATA_SPECIES);
    GetSpeciesName(name, pokeNum);
    SetMonData(mon, MON_DATA_NICKNAME, name);

    pokeNum = SpeciesToNationalPokedexNum(pokeNum); //think can leave as is, since no way to get mega etc. from egg? and gender form should alreaady be on right form
    GetSetPokedexFlag(pokeNum, FLAG_SET_SEEN);
    GetSetPokedexFlag(pokeNum, FLAG_SET_CAUGHT);

    if (GetMonData(mon, MON_DATA_SPECIES) > NATIONAL_SPECIES_COUNT
    && !(GetSetPokedexFlag((GetFormSpeciesId(GetMonData(mon, MON_DATA_SPECIES), 0)), FLAG_GET_SEEN))
    && (gBaseStats[SanitizeSpeciesId(GetMonData(mon, MON_DATA_SPECIES))].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION
    || gBaseStats[SanitizeSpeciesId(GetMonData(mon, MON_DATA_SPECIES))].flags == F_ALOLAN_FORM
    || gBaseStats[SanitizeSpeciesId(GetMonData(mon, MON_DATA_SPECIES))].flags == F_GALARIAN_FORM
    || gBaseStats[SanitizeSpeciesId(GetMonData(mon, MON_DATA_SPECIES))].flags == F_HISUIAN_FORM
    || gBaseStats[SanitizeSpeciesId(GetMonData(mon, MON_DATA_SPECIES))].flags == F_PALDEAN_FORM))
    {
        GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetFormSpeciesId(GetMonData(mon, MON_DATA_SPECIES), 0)), FLAG_SET_SEEN);
        //if catch form should set base form is seen so can navigate to dex page
    }

    DayCare_GetMonNickname(mon, gStringVar1);

    ball = ITEM_POKE_BALL;
    SetMonData(mon, MON_DATA_POKEBALL, &ball);

    //caughtLvl = 5;
    caughtLvl = GetMonData(mon, MON_DATA_MET_LEVEL);
    SetMonData(mon, MON_DATA_MET_LEVEL, &caughtLvl);

    mapNameID = GetCurrentRegionMapSectionId();
    SetMonData(mon, MON_DATA_MET_LOCATION, &mapNameID);

    MonRestorePP(mon);
    CalculateMonStats(mon);
}

void ScriptHatchMon(void)
{
    AddHatchedMonToParty(gSpecialVar_0x8004);
}

/*static bool8 sub_8046E34(struct DayCare *daycare, u8 daycareId)
{
    u8 nick[0x20];
    struct DaycareMon *daycareMon = &daycare->mons[daycareId];

    DayCare_GetBoxMonNickname(&daycareMon->mon, nick);
    if (daycareMon->mail.message.itemId != 0
        && (StringCompare(nick, daycareMon->mail.monName) != IDENTICAL
            || StringCompare(gSaveBlock2Ptr->playerName, daycareMon->mail.OT_name) != IDENTICAL))
    {
        StringCopy(gStringVar1, nick);
        StringCopy(gStringVar2, daycareMon->mail.OT_name);
        StringCopy(gStringVar3, daycareMon->mail.monName);
        return TRUE;
    }
    return FALSE;
}

//special never used
bool8 DaycareMonReceivedMail(void)
{
    return sub_8046E34(&gSaveBlock1Ptr->daycare, gSpecialVar_0x8004);
}*/

//think can remove this but save for later so doesn't get lost
//think is used for functino below as it use tag from compressed sheet
//but I don't use that for my new setup nor does EE

//NO LONGER useing tag so think fines
//extern const struct CompressedSpriteSheet gMonFrontPicTable[];

static u8 EggHatchCreateMonSprite(u8 a0, u8 switchID, u8 pokeID, u16* speciesLoc)
{
    u8 r4 = 0;
    u8 spriteID = 0; // r7
    struct Pokemon* mon = NULL; // r5
    u16 species = SPECIES_NONE;

    if (a0 == 0)
    {
        mon = &gPlayerParty[pokeID];
        r4 = 1;
    }
    if (a0 == 1)
    {
        mon = &gPlayerParty[pokeID];
        r4 = 3;
    }
    species = GetMonData(mon, MON_DATA_SPECIES);
    switch (switchID)
    {
    case 0:
    {
        u32 pid = GetMonData(mon, MON_DATA_PERSONALITY);
        HandleLoadSpecialPokePic(TRUE, gMonSpritesGfxPtr->sprites[(a0 * 2) + 1], species, pid);
        LoadCompressedSpritePaletteWithTag(GetMonSpritePal(mon), species);
        *speciesLoc = species;
    }
        break;
    case 1:
        SetMultiuseSpriteTemplateToPokemon(species, r4);
        spriteID = CreateSprite(&gMultiuseSpriteTemplate, 120, 70, 6);
        gSprites[spriteID].invisible = TRUE;
        gSprites[spriteID].callback = SpriteCallbackDummy;
        break;
    }
    return spriteID;
}

static void VBlankCB_EggHatch(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void EggHatch(void) //source of special egg hatch
{
    LockPlayerFieldControls();
    CreateTask(Task_EggHatch, 10);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
    HelpSystem_Disable();
}

static void Task_EggHatch(u8 taskID)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_EggHatch_0);
        gFieldCallback = FieldCB_ContinueScriptHandleMusic;
        DestroyTask(taskID);
    }
}

static void CB2_EggHatch_0(void)
{
    switch (gMain.state)
    {
    case 0:
        SetGpuReg(REG_OFFSET_DISPCNT, 0);

        sEggHatchData = Alloc(sizeof(struct EggHatchData));
        AllocateMonSpritesGfx();
        sEggHatchData->eggPartyID = gSpecialVar_0x8004;
        sEggHatchData->eggShardVelocityID = 0;

        SetVBlankCallback(VBlankCB_EggHatch);
        gSpecialVar_0x8005 = GetCurrentMapMusic();

        ResetTempTileDataBuffers();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates_EggHatch, NELEMS(sBgTemplates_EggHatch));

        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(0, 0, 0);
        ChangeBgY(0, 0, 0);

        SetBgAttribute(1, 7, 2);
        SetBgTilemapBuffer(1, Alloc(0x1000));
        SetBgTilemapBuffer(0, Alloc(0x2000));

        DeactivateAllTextPrinters();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        ResetSpriteData();
        ResetTasks();
        ScanlineEffect_Stop();
        m4aSoundVSyncOn();
        gMain.state++;
        break;
    case 1:
        InitWindows(sWinTemplates_EggHatch);
        sEggHatchData->windowId = 0;
        gMain.state++;
        break;
    case 2:
        DecompressAndLoadBgGfxUsingHeap(0, gBattleInterface_Textbox_Gfx, 0, 0, 0);
        CopyToBgTilemapBuffer(0, gBattleInterface_Textbox_Tilemap, 0, 0);
        LoadCompressedPalette(gBattleInterface_Textbox_Pal, 0, 0x20);
        gMain.state++;
        break;
    case 3:
        LoadSpriteSheet(&sEggHatch_Sheet);
        LoadSpriteSheet(&sEggShards_Sheet);
        LoadSpritePalette(&sEgg_SpritePalette);
        gMain.state++;
        break;
    case 4:
        CopyBgTilemapBufferToVram(0);
        AddHatchedMonToParty(sEggHatchData->eggPartyID);
        gMain.state++;
        break;
    case 5:
        EggHatchCreateMonSprite(0, 0, sEggHatchData->eggPartyID, &sEggHatchData->species);
        gMain.state++;
        break;
    case 6:
        sEggHatchData->pokeSpriteID = EggHatchCreateMonSprite(0, 1, sEggHatchData->eggPartyID, &sEggHatchData->species);
        gMain.state++;
        break;
    case 7:
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        LoadPalette(gTradeGba2_Pal, 0x10, 0xA0);
        LoadBgTiles(1, gTradeGba_Gfx, 0x1420, 0);
        CopyToBgTilemapBuffer(1, gUnknown_826601C, 0x1000, 0);
        CopyBgTilemapBufferToVram(1);
        gMain.state++;
        break;
    case 8:
        SetMainCallback2(CB2_EggHatch_1);
        sEggHatchData->CB2_state = 0;
        break;
    }
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void EggHatchSetMonNickname(void)
{
    SetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar3);
    FreeMonSpritesGfx();
    Free(sEggHatchData);
    HelpSystem_Enable();
    SetMainCallback2(CB2_ReturnToField);
}

static void Task_EggHatchPlayBGM(u8 taskID)
{
    if (gTasks[taskID].data[0] == 0)
    {
        StopMapMusic();
    }
    if (gTasks[taskID].data[0] == 1)
        PlayBGM(MUS_EVOLUTION_INTRO);
    if (gTasks[taskID].data[0] > 60)
    {
        PlayBGM(MUS_EVOLUTION);
        DestroyTask(taskID);
        // UB: task is destroyed, yet the value is incremented
    }
    gTasks[taskID].data[0]++;
}

static void CB2_EggHatch_1(void)
{
    u16 species;
    u8 gender;
    u32 personality;

    switch (sEggHatchData->CB2_state)
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0x10, 0, RGB_BLACK);
        sEggHatchData->eggSpriteID = CreateSprite(&sSpriteTemplate_EggHatch, 120, 75, 5);
        ShowBg(0);
        ShowBg(1);
        sEggHatchData->CB2_state++;
        CreateTask(Task_EggHatchPlayBGM, 5);
        break;
    case 1:
        if (!gPaletteFade.active)
        {
            FillWindowPixelBuffer(sEggHatchData->windowId, 0x00);
            sEggHatchData->CB2_PalCounter = 0;
            sEggHatchData->CB2_state++;
        }
        break;
    case 2:
        if (++sEggHatchData->CB2_PalCounter > 30)
        {
            sEggHatchData->CB2_state++;
            gSprites[sEggHatchData->eggSpriteID].callback = SpriteCB_Egg_0;
        }
        break;
    case 3:
        if (gSprites[sEggHatchData->eggSpriteID].callback == SpriteCallbackDummy)
        {
           PlayCry_Normal(sEggHatchData->species, 0);
            sEggHatchData->CB2_state++;
        }
        break;
    case 4:
        if (IsCryFinished())
        {
            sEggHatchData->CB2_state++;
        }
        break;
    case 5:
        DayCare_GetMonNickname(&gPlayerParty[sEggHatchData->eggPartyID], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_HatchedFromEgg);
        EggHatchPrintMessage(sEggHatchData->windowId, gStringVar4, 0, 3, 0xFF);
        PlayFanfare(MUS_EVOLVED);
        sEggHatchData->CB2_state++;
        PutWindowTilemap(sEggHatchData->windowId);
        CopyWindowToVram(sEggHatchData->windowId, COPYWIN_BOTH);
        break;
    case 6:
        if (IsFanfareTaskInactive())
            sEggHatchData->CB2_state++;
        break;
    case 7:
        if (IsFanfareTaskInactive())
            sEggHatchData->CB2_state++;
        break;
    case 8:
        DayCare_GetMonNickname(&gPlayerParty[sEggHatchData->eggPartyID], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_NickHatchPrompt);
        EggHatchPrintMessage(sEggHatchData->windowId, gStringVar4, 0, 2, 1);
        sEggHatchData->CB2_state++;
        break;
    case 9:
        if (!IsTextPrinterActive(sEggHatchData->windowId))
        {
            LoadUserWindowBorderGfx(sEggHatchData->windowId, 0x140, 0xE0);
            CreateYesNoMenu(&sYesNoWinTemplate, 3, 0, 2, 0x140, 0xE, 0);
            sEggHatchData->CB2_state++;
        }
        break;
    case 10:
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0:
            DayCare_GetMonNickname(&gPlayerParty[sEggHatchData->eggPartyID], gStringVar3);
            species = GetMonData(&gPlayerParty[sEggHatchData->eggPartyID], MON_DATA_SPECIES);
            gender = GetMonGender(&gPlayerParty[sEggHatchData->eggPartyID]);
            personality = GetMonData(&gPlayerParty[sEggHatchData->eggPartyID], MON_DATA_PERSONALITY, 0);
            DoNamingScreen(NAMING_SCREEN_NICKNAME, gStringVar3, species, gender, personality, EggHatchSetMonNickname);
            break;
        case 1:
        case -1:
            sEggHatchData->CB2_state++;
        }
        break;
    case 11:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        sEggHatchData->CB2_state++;
        break;
    case 12:
        if (!gPaletteFade.active)
        {
            RemoveWindow(sEggHatchData->windowId);
            UnsetBgTilemapBuffer(0);
            UnsetBgTilemapBuffer(1);
            Free(sEggHatchData);
            SetMainCallback2(CB2_ReturnToField);
            HelpSystem_Enable();
        }
        break;
    }

    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void SpriteCB_Egg_0(struct Sprite* sprite)
{
    if (++sprite->data[0] > 20)
    {
        sprite->callback = SpriteCB_Egg_1;
        sprite->data[0] = 0;
    }
    else
    {
        sprite->data[1] = (sprite->data[1] + 20) & 0xFF;
        sprite->pos2.x = Sin(sprite->data[1], 1);
        if (sprite->data[0] == 15)
        {
            PlaySE(SE_BALL);
            StartSpriteAnim(sprite, 1);
            CreateRandomEggShardSprite();
        }
    }
}

static void SpriteCB_Egg_1(struct Sprite* sprite)
{
    if (++sprite->data[2] > 30)
    {
        if (++sprite->data[0] > 20)
        {
            sprite->callback = SpriteCB_Egg_2;
            sprite->data[0] = 0;
            sprite->data[2] = 0;
        }
        else
        {
            sprite->data[1] = (sprite->data[1] + 20) & 0xFF;
            sprite->pos2.x = Sin(sprite->data[1], 2);
            if (sprite->data[0] == 15)
            {
                PlaySE(SE_BALL);
                StartSpriteAnim(sprite, 2);
            }
        }
    }
}

/*struct UnkStruct_82349CC
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
};

extern const struct UnkStruct_82349CC gMonFrontPicCoords[NUM_SPECIES];*/

static void SpriteCB_Egg_2(struct Sprite* sprite)
{
    if (++sprite->data[2] > 30)
    {
        if (++sprite->data[0] > 38)
        {
            u16 species;

            sprite->callback = SpriteCB_Egg_3;
            sprite->data[0] = 0;
            species = GetMonData(&gPlayerParty[sEggHatchData->eggPartyID], MON_DATA_SPECIES);
            gSprites[sEggHatchData->pokeSpriteID].pos2.x = 0;
            gSprites[sEggHatchData->pokeSpriteID].pos2.y = gSpeciesGraphics[species].frontPicYOffset; //was field1, just taking a guess
        }
        else
        {
            sprite->data[1] = (sprite->data[1] + 20) & 0xFF;
            sprite->pos2.x = Sin(sprite->data[1], 2);
            if (sprite->data[0] == 15)
            {
                PlaySE(SE_BALL);
                StartSpriteAnim(sprite, 2);
                CreateRandomEggShardSprite();
                CreateRandomEggShardSprite();
            }
            if (sprite->data[0] == 30)
                PlaySE(SE_BALL);
        }
    }
}

static void SpriteCB_Egg_3(struct Sprite* sprite)
{
    if (++sprite->data[0] > 50)
    {
        sprite->callback = SpriteCB_Egg_4;
        sprite->data[0] = 0;
    }
}

static void SpriteCB_Egg_4(struct Sprite* sprite)
{
    s16 i;
    if (sprite->data[0] == 0)
        BeginNormalPaletteFade(0xFFFFFFFF, -1, 0, 0x10, 0xFFFF);
    if (sprite->data[0] < 4u)
    {
        for (i = 0; i <= 3; i++)
            CreateRandomEggShardSprite();
    }
    sprite->data[0]++;
    if (!gPaletteFade.active)
    {
        PlaySE(SE_EGG_HATCH);
        sprite->invisible = TRUE;
        sprite->callback = SpriteCB_Egg_5;
        sprite->data[0] = 0;
    }
}

static void SpriteCB_Egg_5(struct Sprite* sprite)
{
    if (sprite->data[0] == 0)
    {
        gSprites[sEggHatchData->pokeSpriteID].invisible = FALSE;
        StartSpriteAffineAnim(&gSprites[sEggHatchData->pokeSpriteID], 1);
    }
    if (sprite->data[0] == 8)
        BeginNormalPaletteFade(0xFFFFFFFF, -1, 0x10, 0, 0xFFFF);
    if (sprite->data[0] <= 9)
        gSprites[sEggHatchData->pokeSpriteID].pos1.y -= 1;
    if (sprite->data[0] > 40)
        sprite->callback = SpriteCallbackDummy;
    sprite->data[0]++;
}

static void SpriteCB_EggShard(struct Sprite* sprite)
{
    sprite->data[4] += sprite->data[1];
    sprite->data[5] += sprite->data[2];

    sprite->pos2.x = sprite->data[4] / 256;
    sprite->pos2.y = sprite->data[5] / 256;

    sprite->data[2] += sprite->data[3];

    if (sprite->pos1.y + sprite->pos2.y > sprite->pos1.y + 20 && sprite->data[2] > 0)
        DestroySprite(sprite);
}

static void CreateRandomEggShardSprite(void)
{
    u16 spriteAnimIndex;

    s16 velocity1 = sEggShardVelocities[sEggHatchData->eggShardVelocityID][0];
    s16 velocity2 = sEggShardVelocities[sEggHatchData->eggShardVelocityID][1];
    sEggHatchData->eggShardVelocityID++;
    spriteAnimIndex = Random() % 4;
    CreateEggShardSprite(120, 60, velocity1, velocity2, 100, spriteAnimIndex);
}

static void CreateEggShardSprite(u8 x, u8 y, s16 data1, s16 data2, s16 data3, u8 spriteAnimIndex)
{
    u8 spriteID = CreateSprite(&sSpriteTemplate_EggShard, x, y, 4);
    gSprites[spriteID].data[1] = data1;
    gSprites[spriteID].data[2] = data2;
    gSprites[spriteID].data[3] = data3;
    StartSpriteAnim(&gSprites[spriteID], spriteAnimIndex);
}

static void EggHatchPrintMessage(u8 windowId, u8* string, u8 x, u8 y, u8 speed)
{
    FillWindowPixelBuffer(windowId, 0xFF);
    sEggHatchData->textColor[0] = 0;
    sEggHatchData->textColor[1] = 5;
    sEggHatchData->textColor[2] = 6;
    AddTextPrinterParameterized4(windowId, 3, x, y, 0, 1, sEggHatchData->textColor, speed, string);
}
