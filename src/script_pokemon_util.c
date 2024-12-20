#include "global.h"
#include "gflib.h"
#include "berry.h"
#include "daycare.h"
#include "event_data.h"
#include "load_save.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokedex.h"
#include "random.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/pokemon.h"

static void CB2_ReturnFromChooseHalfParty(void);
static void CB2_ReturnFromChooseBattleTowerParty(void);

void HealPlayerParty(void)
{
    u8 i, j;
    u8 ppBonuses;
    u8 arg[4];
    u8 clearNuzlockeDeath = 1;

    // restore HP.
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        u16 maxHP = GetMonData(&gPlayerParty[i], MON_DATA_MAX_HP);

        if ((IsNuzlockeModeOn() && (GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) == 0)
        && FlagGet(FLAG_SYS_POKEDEX_GET)))
            continue;
        
        else if (!(IsNuzlockeModeOn())
        && FlagGet(FLAG_SYS_POKEDEX_GET) && (GetMonData(&gPlayerParty[i], MON_DATA_BOX_HP, NULL) == 0))
            SetMonData(&gPlayerParty[i], MON_DATA_BOX_HP, &clearNuzlockeDeath);

            
        
        arg[0] = maxHP;
        arg[1] = maxHP >> 8;
        SetMonData(&gPlayerParty[i], MON_DATA_HP, arg);
        ppBonuses = GetMonData(&gPlayerParty[i], MON_DATA_PP_BONUSES);

        // restore PP.
        for(j = 0; j < MAX_MON_MOVES; j++)
        {
            arg[0] = CalculatePPWithBonus(GetMonData(&gPlayerParty[i], MON_DATA_MOVE1 + j), ppBonuses, j);
            SetMonData(&gPlayerParty[i], MON_DATA_PP1 + j, arg);
        }

        // since status is u32, the four 0 assignments here are probably for safety to prevent undefined data from reaching SetMonData.
        arg[0] = 0;
        arg[1] = 0;
        arg[2] = 0;
        arg[3] = 0;
        SetMonData(&gPlayerParty[i], MON_DATA_STATUS, arg);
    }
}

//pretty sure rather than make this void it'd be better
//to use mon, so it could be used for either party?
//well no this isnt for battle and only way to swap between is 
//by filtering for battle side or possibly trainer id, like in battle_main npctrainerparty function
//but this for now is fine as is
#define CUSTOM_SETUP_GIVEMON
//no idea why I made this a u16 but it works without issue
u16 GetAveragePlayerPartyLevel(void) //ok so issue seems to be assingment, I guess I can't define and assign multiple values at once?
{
    u16 sum, numMons;
    //u16 numMons = 0;
    s32 i;
    u16 averageLevel;

    sum = numMons = 0;

    for (i = 0; i < PARTY_SIZE; ++i)
    {
        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);

        if (species != SPECIES_EGG)
        {
            if (species == SPECIES_NONE)
                break;
            
            sum += GetMonData(&gPlayerParty[i], MON_DATA_LEVEL); //this is the problem no idea why
           ++numMons; //what its doing instead of returning level is returning 9 for every time function call?
            
        }
    }
    if (numMons)
        averageLevel = ((sum) / numMons);
    else
        averageLevel = 7; //small fix to ensure works, and doesn't attempt divide by 0, case only exists in test where would give mon before receiving starter

    return averageLevel;
    
}

u8 ScriptGiveMon(u16 species, u8 level, u16 item, u32 unused1, u32 unused2, u8 unused3) //only thing worried about is possibility to upset caught mon,
{
    u16 nationalDexNum;
    int sentToPc;
    u8 heldItem[2];
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));

    if (level != 5) 
        level = GetAveragePlayerPartyLevel(); //hopefully works /works testing, for issue with catching generated mon

    if (species == SPECIES_NONE)
    {
        do //ok think I misunderstood htis, believe the do runs first, then it checks condition on if it should run again
        {
            species = Random() % (NUM_SPECIES - 2);
        }
        while (species == SPECIES_NONE
        || species == SPECIES_FRAEYJTA
        || species == SPECIES_CEFIREON
        || species == SPECIES_TORTERRA_MEGA
        || species == SPECIES_MAROWAK_MEGA); //should cover everything
    }//relized what caused loop freeze, it only loop if species nun,
    //but if it looped the first time,  and then landed on on of the banned species
    //it wouldn't be able to reloop and just lock, fixed by putting conditional outside

    CreateMon(mon, species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    heldItem[0] = item;
    heldItem[1] = item >> 8;
    SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);
    sentToPc = GiveMonToPlayer(mon);  //catching mon seems to work without issue,  yup no issues
    nationalDexNum = SpeciesToNationalPokedexNum(species);

    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);

        if (species > NATIONAL_SPECIES_COUNT
        && !(GetSetPokedexFlag((GetFormSpeciesId(species, 0)), FLAG_GET_SEEN))
        && (gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_ALOLAN_FORM
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_GALARIAN_FORM
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_HISUIAN_FORM
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_PALDEAN_FORM))
        {
            GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetFormSpeciesId(species, 0)), FLAG_SET_SEEN);
            //if catch form should set base form is seen so can navigate to dex page
        }
        break;
    }

    Free(mon);
    return sentToPc;
}

//original script without scaling use for testing - for more test set to give random mon at lvl
u8 ScriptGiveMon2(u16 species, u8 level, u16 item, u32 unused1, u32 unused2, u8 unused3) //only thing worried about is possibility to upset caught mon,
{
    u16 nationalDexNum;
    int sentToPc;
    u8 heldItem[2];
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));

    if (species == SPECIES_NONE)
    {
        do
        {
            species = Random() % (NUM_SPECIES - 2);
        }
        while (species == SPECIES_NONE
        || species == SPECIES_FRAEYJTA
        || species == SPECIES_CEFIREON
        || species == SPECIES_TORTERRA_MEGA
        || species == SPECIES_MAROWAK_MEGA); //should cover everything
    }

    //if (species == SPECIES_NONE)
    //    species = Random() % (NUM_SPECIES - 2); //to exclude undefined new megas

    CreateMon(mon, species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    heldItem[0] = item;
    heldItem[1] = item >> 8;
    SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);
    sentToPc = GiveMonToPlayer(mon);  //catching mon seems to work without issue,  yup no issues
    nationalDexNum = SpeciesToNationalPokedexNum(species);

    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);

        if (species > NATIONAL_SPECIES_COUNT
        && !(GetSetPokedexFlag((GetFormSpeciesId(species, 0)), FLAG_GET_SEEN))
        && (gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_ALOLAN_FORM
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_GALARIAN_FORM
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_HISUIAN_FORM
        || gBaseStats[SanitizeSpeciesId(species)].flags == F_PALDEAN_FORM))
        {
            GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetFormSpeciesId(species, 0)), FLAG_SET_SEEN);
            //if catch form should set base form is seen so can navigate to dex page
        }
        break;
    }

    Free(mon);
    return sentToPc;
}

u8 ScriptGiveEgg(u16 species)
{
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));
    bool8 isEgg;
    bool8 sentToPc;

    CreateEgg(mon, species, TRUE);
    isEgg = TRUE;
    SetMonData(mon, MON_DATA_IS_EGG, &isEgg);

    sentToPc = GiveMonToPlayer(mon);
    Free(mon);
    return sentToPc;
}

void HasEnoughMonsForDoubleBattle(void)
{
    switch (GetMonsStateToDoubles())
    {
    case PLAYER_HAS_TWO_USABLE_MONS:
        gSpecialVar_Result = PLAYER_HAS_TWO_USABLE_MONS;
        break;
    case PLAYER_HAS_ONE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_MON;
        break;
    case PLAYER_HAS_ONE_USABLE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_USABLE_MON;
        break;
    }
}

static bool8 CheckPartyMonHasHeldItem(u16 item)
{
    int i;

    for(i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);
        if (species != SPECIES_NONE && species != SPECIES_EGG && GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    return FALSE;
}

bool8 DoesPartyHaveEnigmaBerry(void)
{
    bool8 hasItem = CheckPartyMonHasHeldItem(ITEM_ENIGMA_BERRY);
    if (hasItem == TRUE)
        GetBerryNameByBerryType(ItemIdToBerryType(ITEM_ENIGMA_BERRY), gStringVar1);

    return hasItem;
}

void CreateScriptedWildMon(u16 species, u8 level, u16 item)
{
    u8 heldItem[2];

    ZeroEnemyPartyMons();
    CreateMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, 0, 0, OT_ID_PLAYER_ID, 0);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, heldItem);
    }
}

void ScriptSetMonMoveSlot(u8 monIndex, u16 move, u8 slot)
{
    if (monIndex > PARTY_SIZE)
        monIndex = gPlayerPartyCount - 1;

    SetMonMoveSlot(&gPlayerParty[monIndex], move, slot);
}

// Note: When control returns to the event script, gSpecialVar_Result will be
// TRUE if the party selection was successful.
void ChooseHalfPartyForBattle(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseHalfParty;
//    VarSet(VAR_FRONTIER_FACILITY, FACILITY_MULTI_OR_EREADER);
    InitChooseHalfPartyForBattle(0);
}

static void CB2_ReturnFromChooseHalfParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ChooseBattleTowerPlayerParty(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseBattleTowerParty;
    InitChooseHalfPartyForBattle(1);
}

static void CB2_ReturnFromChooseBattleTowerParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        LoadPlayerParty();
        gSpecialVar_Result = FALSE;
        break;
    default:
        ReducePlayerPartyToThree();
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ReducePlayerPartyToThree(void)
{
    struct Pokemon * party = AllocZeroed(3 * sizeof(struct Pokemon));
    int i;

    // copy the selected pokemon according to the order.
    for (i = 0; i < 3; i++)
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
            party[i] = gPlayerParty[gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal

    CpuFill32(0, gPlayerParty, sizeof gPlayerParty);

    // overwrite the first 3 with the order copied to.
    for (i = 0; i < 3; i++)
        gPlayerParty[i] = party[i];

    CalculatePlayerPartyCount();
    Free(party);
}
