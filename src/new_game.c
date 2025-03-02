#include "global.h"
#include "gflib.h"
#include "random.h"
#include "overworld.h"
#include "constants/maps.h"
#include "load_save.h"
#include "save.h"
#include "item_menu.h"
#include "tm_case.h"
#include "berry_pouch.h"
#include "quest_log.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "mail_data.h"
#include "play_time.h"
#include "money.h"
#include "battle_records.h"
#include "pokemon_size_record.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "item.h"
#include "player_pc.h"
#include "berry.h"
#include "easy_chat.h"
#include "union_room_chat.h"
#include "mevent.h"
#include "renewable_hidden_items.h"
#include "trainer_tower.h"
#include "script.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "event_scripts.h"
//may be able to ues some of these functions to make a new file, for "new game+" just need be selective in which things get reset.
//my idea for new game place, was to keep all pokemon, change level (probably do by changing amount of exp) of party pokemon, 
//keep all items, so don't affect pc,  and keep track of when the new game +/ number of playthroughs.  Since i removed link battle, maybe I can have playthrough numbers shown 
//on card instead.

// this file's functions
//static void ResetMiniGamesResults(void);

// EWRAM vars
EWRAM_DATA bool8 gDifferentSaveFile = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < 4; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetTextCapFlags(void)
{

    FlagSet(FLAG_CAPITALIZE_SPECIES_TEXT); //plan rename to capitalize

    FlagSet(FLAG_CAPITALIZE_ABILITY_TEXT);

    FlagSet(FLAG_CAPITALIZE_MOVE_TEXT);

    FlagSet(FLAG_CAPITALIZE_ITEM_TEXT);

    FlagSet(FLAG_CAPITALIZE_MISC_PLACEHOLDER);

}

//seems irrelevant? , oh nvm not used in normal new game start
//yeah this has nothing to do with setting new game stuff, 
//and yet somehow I did change textspeed to fast in the past?
//nvm it is this, its just only triggered the first stime you start game
//doesn't trigger if you already had a save
static void SetDefaultOptions(void) //changed setup, now when start new game, will rollover options from existing save if in saveblock
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FASTER;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE; //?  uses a double negative for some reason
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_LR;
    gSaveBlock2Ptr->optionsBattleSpeed = OPTIONS_BATTLE_SPEED_2X;
    gSaveBlock2Ptr->optionsEventSpeedup = TRUE;
    gSaveBlock2Ptr->optionsDisplayTypeEffect = FALSE;
    gSaveBlock2Ptr->optionsNuzlockeMode = FALSE;
    //SetTextCapFlags();  //works / thought this worked but things aren't set?
} //ok just doesn't work on as part of this function, think issue is it not being part of save block
//so can't be set and saved, when its being set, i.e before game start?

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

static void sub_80549D4(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->battleTower, sizeof(gSaveBlock2Ptr->battleTower));
}

static void WarpToPlayersRoom(void)
{
    SetWarpDestination(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagCursorPositions();
    ResetTMCaseCursorPos();
    BerryPouch_CursorResetToTop();
    ResetQuestLog();
    SeedWildEncounterRng(Random());
    ResetSpecialVars();
}

void NewGameInitData(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();//skip for new game plus
    ZeroEnemyPartyMons();
    sub_80549D4();
    ClearSav1();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    //gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->field_AC = 1;
    gSaveBlock2Ptr->field_AD = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();//skip for new game plus
    ClearPokedexFlags(); //skip for new game plus
    InitEventData();
    ResetFameChecker(); 
    SetMoney(&gSaveBlock1Ptr->money, 3000);//skip for new game plus
    ResetGameStats();//skip for new game plus
    //ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    EnableNationalPokedex_RSE();
    gPlayerPartyCount = 0; // change this & zeroplayerpartymons for new game+
    ZeroPlayerPartyMons();//skip for new game plus
    ResetPokemonStorageSystem();//skip for new game plus
    ClearRoamerData();//skip for new game plus
    gSaveBlock1Ptr->registeredItem = 0;
    gSaveBlock1Ptr->oakRanchStepCounter = 0;
    ClearBag();//skip for new game plus
    NewGameInitPCItems();//skip for new game plus
    sub_809C794();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    UnionRoomChat_InitializeRegisteredTexts();
    //ResetMiniGamesResults();
    InitMEventData();
    SetAllRenewableItemFlags();
    //SetDefaultOptions();
    WarpToPlayersRoom();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags); 
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();
    SetTextCapFlags(); //sets cap but keeps game options from main save
    if (Random() % 10 == 6)
        FlagClear(FLAG_HIDE_FISHERMAN_IN_PALLET_TOWN);
}
/*
static void ResetMiniGamesResults(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
   // SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokeJumpResults();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}*/
