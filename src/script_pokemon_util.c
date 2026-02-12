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

        if (IsMonNuzlockeDead(&gPlayerParty[i]))
            continue;
        

            
        
        arg[0] = maxHP;
        arg[1] = maxHP >> 8;
        SetMonData(&gPlayerParty[i], MON_DATA_HP, arg);
        SetMonData(&gPlayerParty[i], MON_DATA_BOX_HP, arg);
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
        && (gBaseStats[SanitizeSpeciesId(species)].isMegaEvolution
        || gBaseStats[SanitizeSpeciesId(species)].isPrimalReversion
        || IsRegionalVariant(species)))
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
        && (gBaseStats[SanitizeSpeciesId(species)].isMegaEvolution
        || gBaseStats[SanitizeSpeciesId(species)].isPrimalReversion
        || IsRegionalVariant(species)))
        {
            GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetFormSpeciesId(species, 0)), FLAG_SET_SEEN);
            //if catch form should set base form is seen so can navigate to dex page
        }
        break;
    }

    Free(mon);
    return sentToPc;
}

u8 ScriptGiveEgg(u16 species, u8 isSecretEgg)
{
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));
    bool8 isEgg;
    bool8 sentToPc;

    CreateEgg(mon, species, TRUE);

    if (isSecretEgg)
        SetMonData(mon, MON_DATA_HIDE_EGG_SPECIES, &isSecretEgg);

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

void CanHyperTrain(struct ScriptContext *ctx)
{
    u32 stat = ScriptReadByte(ctx);
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1);

    assertf(stat < NUM_STATS, "invalid stat: %d", stat)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    CalculatePlayerPartyCount();
    assertf(partyIndex < gPlayerPartyCount, "invalid party index: %d", partyIndex)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    if (!GetMonData(&gPlayerParty[partyIndex], MON_DATA_HYPER_TRAINED_HP + stat)
     && GetMonData(&gPlayerParty[partyIndex], MON_DATA_HP_IV + stat) < MAX_PER_STAT_IVS)
    {
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

void HyperTrain(struct ScriptContext *ctx)
{
    u32 stat = ScriptReadByte(ctx);
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    assertf(stat < NUM_STATS, "invalid stat: %d", stat)
    {
        return;
    }

    CalculatePlayerPartyCount();
    assertf(partyIndex < gPlayerPartyCount, "invalid party index: %d", partyIndex)
    {
        return;
    }

    bool32 data = TRUE;
    SetMonData(&gPlayerParty[partyIndex], MON_DATA_HYPER_TRAINED_HP + stat, &data);
    CalculateMonStats(&gPlayerParty[partyIndex]);
}

void HasGigantamaxFactor(struct ScriptContext *ctx)
{
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1);

    if (partyIndex < PARTY_SIZE)
        gSpecialVar_Result = GetMonData(&gPlayerParty[partyIndex], MON_DATA_GIGANTAMAX_FACTOR);
    else
        gSpecialVar_Result = FALSE;
}

void ToggleGigantamaxFactor(struct ScriptContext *ctx)
{
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    gSpecialVar_Result = FALSE;

    if (partyIndex < PARTY_SIZE)
    {
        bool32 gigantamaxFactor;

        if (gSpeciesInfo[SanitizeSpeciesId(GetMonData(&gPlayerParty[partyIndex], MON_DATA_SPECIES))].isMythical)
            return;

        gigantamaxFactor = GetMonData(&gPlayerParty[partyIndex], MON_DATA_GIGANTAMAX_FACTOR);
        gigantamaxFactor = !gigantamaxFactor;
        SetMonData(&gPlayerParty[partyIndex], MON_DATA_GIGANTAMAX_FACTOR, &gigantamaxFactor);
        gSpecialVar_Result = TRUE;
    }
}

void CheckTeraType(struct ScriptContext *ctx)
{
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1);

    gSpecialVar_Result = TYPE_NONE;

    if (partyIndex < PARTY_SIZE)
        gSpecialVar_Result = GetMonData(&gPlayerParty[partyIndex], MON_DATA_TERA_TYPE);
}

void SetTeraType(struct ScriptContext *ctx)
{
    enum Type type = ScriptReadByte(ctx);
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    if (type < NUMBER_OF_MON_TYPES && partyIndex < PARTY_SIZE)
        SetMonData(&gPlayerParty[partyIndex], MON_DATA_TERA_TYPE, &type);
}

/* Creates a Pokemon via script
 * if side/slot are assigned, it will create the mon at the assigned party location
 * if slot == PARTY_SIZE, it will give the mon to first available party or storage slot
 */
static u32 ScriptGiveMonParameterized(u8 side, u8 slot, u16 species, u8 level, enum Item item, enum PokeBall ball, u8 nature, u8 abilityNum, u8 gender, u16 *evs, u16 *ivs, enum Move *moves, enum ShinyMode shinyMode, bool8 gmaxFactor, enum Type teraType, u8 dmaxLevel)
{
    struct Pokemon mon;
    u32 i;
    bool32 isShiny;

    u32 personality = GetMonPersonality(species, gender, nature, RANDOM_UNOWN_LETTER);
    CreateMon(&mon, species, level, personality, OTID_STRUCT_PLAYER_ID);

    // shininess
    if (shinyMode == SHINY_MODE_ALWAYS || (P_FLAG_FORCE_SHINY != 0 && FlagGet(P_FLAG_FORCE_SHINY)))
        isShiny = TRUE;
    else if (shinyMode == SHINY_MODE_NEVER || (P_FLAG_FORCE_NO_SHINY != 0 && FlagGet(P_FLAG_FORCE_NO_SHINY)))
        isShiny = FALSE;
    else
        isShiny = GetMonData(&mon, MON_DATA_IS_SHINY);

    SetMonData(&mon, MON_DATA_IS_SHINY, &isShiny);

    // gigantamax factor
    SetMonData(&mon, MON_DATA_GIGANTAMAX_FACTOR, &gmaxFactor);

    // Dynamax Level
    SetMonData(&mon, MON_DATA_DYNAMAX_LEVEL, &dmaxLevel);

    // tera type
    if (teraType == TYPE_NONE || teraType == TYPE_MYSTERY || teraType >= NUMBER_OF_MON_TYPES)
        teraType = GetTeraTypeFromPersonality(&mon);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &teraType);

    // EV and IV
    for (i = 0; i < NUM_STATS; i++)
    {
        // EV
        if (evs[i] <= MAX_PER_STAT_EVS)
            SetMonData(&mon, MON_DATA_HP_EV + i, &evs[i]);

        // IV
        if (ivs[i] <= MAX_PER_STAT_IVS)
            SetMonData(&mon, MON_DATA_HP_IV + i, &ivs[i]);
    }
    CalculateMonStats(&mon);

    // moves
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == MOVE_NONE)
            break;
        if (moves[i] < MOVES_COUNT)
        {
            SetMonMoveSlot(&mon, moves[i], i);
        }
        else if (moves[i] == MOVE_DEFAULT)
        {
            GiveMonDefaultMove(&mon, i);
            continue;
        }
        else
        {
            assertf(FALSE, "invalid move: %d", moves[i]) {}
        }
    }

    // ability
    if (abilityNum != NUM_ABILITY_PERSONALITY)
    {
        assertf(abilityNum < NUM_ABILITY_SLOTS && GetAbilityBySpecies(species, abilityNum) != ABILITY_NONE,
                "invalid ability num %d for species %d", abilityNum, species)
        {
            // If the ability num is invalid, we loop to find a valid one
            do {
                abilityNum = Random() % NUM_ABILITY_SLOTS; // includes hidden abilities
            } while (GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE);
        }
        SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilityNum);
    }

    // ball
    if (ball > POKEBALL_COUNT)
        ball = BALL_POKE;
    SetMonData(&mon, MON_DATA_POKEBALL, &ball);

    // held item
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);

    // In case a mon with a form changing item is given. Eg: SPECIES_ARCEUS_NORMAL with ITEM_SPLASH_PLATE will transform into SPECIES_ARCEUS_WATER upon gifted.
    TryFormChange(&mon, FORM_CHANGE_ITEM_HOLD);

    if (side == B_SIDE_PLAYER)
        return GiveScriptedMonToPlayer(&mon, slot);

    assertf(slot < PARTY_SIZE, "invalid slot: %d", slot)
    {
        return MON_CANT_GIVE;
    }
    CopyMon(&gEnemyParty[slot], &mon, sizeof(struct Pokemon));
    return MON_GIVEN_TO_PARTY;
}

u32 ScriptGiveMon(u16 species, u8 level, enum Item item)
{
    struct Pokemon mon;
    u8 heldItem[2];

    CreateRandomMon(&mon, species, level);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&mon, MON_DATA_HELD_ITEM, heldItem);
    }

    return GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
}

#define PARSE_FLAG(n, default_) (flags & (1 << (n))) ? VarGet(ScriptReadHalfword(ctx)) : (default_)

#define ADD_MOVE_IF_NOT_DEFAULT(i, move)               \
    if (move && move != MOVE_DEFAULT)                  \
    {                                                  \
        moves[i] = move;                               \
        i++;                                           \
    }

#define ADD_MOVE_IF_DEFAULT(i, move)                   \
    if (moves[i] == MOVE_NONE && move == MOVE_DEFAULT) \
    {                                                  \
        moves[i] = MOVE_DEFAULT;                       \
        i++;                                           \
    }

/* Give or create a mon to either player or opponent
 */


void ScrCmd_createmon(struct ScriptContext *ctx)
{
    u8 side           = ScriptReadByte(ctx);
    u8 slot           = ScriptReadByte(ctx);
    u16 species       = VarGet(ScriptReadHalfword(ctx));
    u8 level          = VarGet(ScriptReadHalfword(ctx));

    u32 flags         = ScriptReadWord(ctx);
    enum Item item    = PARSE_FLAG(0, ITEM_NONE);
    u8 ball           = PARSE_FLAG(1, ITEM_POKE_BALL);
    u8 nature         = PARSE_FLAG(2, NATURE_RANDOM);
    u8 abilityNum     = PARSE_FLAG(3, NUM_ABILITY_PERSONALITY);
    u8 gender         = PARSE_FLAG(4, MON_GENDER_RANDOM);

    u32 i;
    u16 evs[NUM_STATS];
    for (i = 0; i < NUM_STATS; i++)
    {
        evs[i] = PARSE_FLAG(5 + i, 0);
        assertf(evs[i] <= MAX_PER_STAT_EVS, "invalid ev value of %d above maximum of %d", evs[i], MAX_PER_STAT_EVS)
        {
            evs[i] = MAX_PER_STAT_EVS;
        }
    }

    u16 ivs[NUM_STATS];
    u32 nonFixedIvCount = 0;
    enum Stat availableIVs[NUM_STATS];
    enum Stat selectedIvs[NUM_STATS];
    for (i = 0; i < NUM_STATS; i++)
    {
        ivs[i] = PARSE_FLAG(11 + i, USE_RANDOM_IVS);
        assertf(ivs[i] <= USE_RANDOM_IVS, "invalid iv value of %d above maximum of %d", ivs[i], MAX_PER_STAT_IVS)
        {
            ivs[i] = MAX_PER_STAT_IVS;
        }
        if (ivs[i] == USE_RANDOM_IVS)
        {
            availableIVs[nonFixedIvCount] = i;
            ivs[i] = Random() % (MAX_PER_STAT_IVS + 1);
            nonFixedIvCount++;
        }
    }

    // Perfect IV calculation
    if (gSpeciesInfo[species].perfectIVCount != 0)
    {
        // Select the IVs that will be perfected.
        for (i = 0; i < nonFixedIvCount && i < gSpeciesInfo[species].perfectIVCount; i++)
        {
            u8 index = Random() % (nonFixedIvCount - i);
            selectedIvs[i] = availableIVs[index];
            RemoveIVIndexFromList(availableIVs, index);
        }
        for (i = 0; i < nonFixedIvCount && i < gSpeciesInfo[species].perfectIVCount; i++)
        {
            ivs[selectedIvs[i]] = MAX_PER_STAT_IVS;
        }
    }

    enum Move move1          = PARSE_FLAG(17, MOVE_DEFAULT);
    enum Move move2          = PARSE_FLAG(18, MOVE_DEFAULT);
    enum Move move3          = PARSE_FLAG(19, MOVE_DEFAULT);
    enum Move move4          = PARSE_FLAG(20, MOVE_DEFAULT);
    enum ShinyMode shinyMode = PARSE_FLAG(21, SHINY_MODE_RANDOM);
    bool8 gmaxFactor         = PARSE_FLAG(22, FALSE);
    enum Type teraType       = PARSE_FLAG(23, NUMBER_OF_MON_TYPES);
    u8 dmaxLevel             = PARSE_FLAG(24, 0);

    enum Move moves[MAX_MON_MOVES];
    for (i = 0; i < MAX_MON_MOVES; i++)
        moves[i] = MOVE_NONE;

    i = 0;
    //Reorder moves to put non-default moves first, default moves second and empty moves last
    ADD_MOVE_IF_NOT_DEFAULT(i, move1)
    ADD_MOVE_IF_NOT_DEFAULT(i, move2)
    ADD_MOVE_IF_NOT_DEFAULT(i, move3)
    ADD_MOVE_IF_NOT_DEFAULT(i, move4)
    ADD_MOVE_IF_DEFAULT(i, move1)
    ADD_MOVE_IF_DEFAULT(i, move2)
    ADD_MOVE_IF_DEFAULT(i, move3)
    ADD_MOVE_IF_DEFAULT(i, move4)

    enum GeneratedMonOrigin origin;
    if (side == 0)
    {
        //Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
        origin = GIFTMON_ORIGIN;
    }
    else
    {
        //Script_RequestEffects(SCREFF_V1);
        origin = STATIC_WILDMON_ORIGIN;
    }

    if (gender == MON_GENDER_MAY_CUTE_CHARM)
        gender = GetSynchronizedGender(origin, species);
    if (nature == NATURE_MAY_SYNCHRONIZE)
        nature = GetSynchronizedNature(origin, species);

    gSpecialVar_Result = ScriptGiveMonParameterized(side, slot, species, level, item, ball, nature, abilityNum, gender, evs, ivs, moves, shinyMode, gmaxFactor, teraType, dmaxLevel);
}

#undef PARSE_FLAG

void Script_GetChosenMonOffensiveEVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_ATK_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPATK_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPEED_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_GetChosenMonDefensiveEVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_HP_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_DEF_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPDEF_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_GetChosenMonOffensiveIVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_ATK_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPATK_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPEED_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_GetChosenMonDefensiveIVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_HP_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_DEF_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPDEF_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_SetStatus1(struct ScriptContext *ctx)
{
    u32 status1 = VarGet(ScriptReadHalfword(ctx));
    u32 slot = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    if (slot >= PARTY_SIZE)
    {
        u16 species;

        for (slot = 0; slot < PARTY_SIZE; slot++)
        {
            species = GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES);
            if (species != SPECIES_NONE
             && species != SPECIES_EGG
             && GetMonData(&gPlayerParty[slot], MON_DATA_HP) != 0)
                SetMonData(&gPlayerParty[slot], MON_DATA_STATUS, &status1);
        }
    }
    else
    {
        SetMonData(&gPlayerParty[slot], MON_DATA_STATUS, &status1);
    }
}

void Script_SetKO(struct ScriptContext *ctx)
{
    u32 slot = VarGet(ScriptReadHalfword(ctx));

    //Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    if (slot < PARTY_SIZE)
    {
        u32 hp = 0;
        SetMonData(&gPlayerParty[slot], MON_DATA_HP, &hp);
    }
}
