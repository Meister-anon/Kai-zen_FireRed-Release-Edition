#ifndef GUARD_POKEDEX_H
#define GUARD_POKEDEX_H
/*
#define KANTO_DEX_COUNT 151
#define HOENN_DEX_COUNT 202
#define NATIONAL_DEX_COUNT 386 */

enum
{
    DEX_MODE_KANTO,
    DEX_MODE_NATIONAL
};

enum
{
    FLAG_GET_SEEN,
    FLAG_GET_CAUGHT,
    FLAG_SET_SEEN,
    FLAG_SET_CAUGHT
};

// IDs for the pokedex area markers
enum {
    DEX_AREA_NONE,
    DEX_AREA_PALLET_TOWN,
    DEX_AREA_VIRIDIAN_CITY,
    DEX_AREA_PEWTER_CITY,
    DEX_AREA_CERULEAN_CITY,
    DEX_AREA_LAVENDER_TOWN,
    DEX_AREA_VERMILION_CITY,
    DEX_AREA_CELADON_CITY,
    DEX_AREA_FUCHSIA_CITY,
    DEX_AREA_CINNABAR_ISLAND,
    DEX_AREA_INDIGO_PLATEAU,
    DEX_AREA_SAFFRON_CITY,
    DEX_AREA_ROUTE_1,
    DEX_AREA_ROUTE_2,
    DEX_AREA_ROUTE_3,
    DEX_AREA_ROUTE_4,
    DEX_AREA_ROUTE_5,
    DEX_AREA_ROUTE_6,
    DEX_AREA_ROUTE_7,
    DEX_AREA_ROUTE_8,
    DEX_AREA_ROUTE_9,
    DEX_AREA_ROUTE_10,
    DEX_AREA_ROUTE_11,
    DEX_AREA_ROUTE_12,
    DEX_AREA_ROUTE_13,
    DEX_AREA_ROUTE_14,
    DEX_AREA_ROUTE_15,
    DEX_AREA_ROUTE_16,
    DEX_AREA_ROUTE_17,
    DEX_AREA_ROUTE_18,
    DEX_AREA_ROUTE_19,
    DEX_AREA_ROUTE_20,
    DEX_AREA_ROUTE_21,
    DEX_AREA_ROUTE_22,
    DEX_AREA_ROUTE_23,
    DEX_AREA_ROUTE_24,
    DEX_AREA_ROUTE_25,
    DEX_AREA_VIRIDIAN_FOREST,
    DEX_AREA_DIGLETTS_CAVE,
    DEX_AREA_MT_MOON,
    DEX_AREA_CERULEAN_CAVE,
    DEX_AREA_ROCK_TUNNEL,
    DEX_AREA_POWER_PLANT,
    DEX_AREA_POKEMON_TOWER,
    DEX_AREA_SAFARI_ZONE,
    DEX_AREA_SEAFOAM_ISLANDS,
    DEX_AREA_POKEMON_MANSION,
    DEX_AREA_VICTORY_ROAD,
    DEX_AREA_ONE_ISLAND,
    DEX_AREA_TWO_ISLAND,
    DEX_AREA_THREE_ISLAND,
    DEX_AREA_FOUR_ISLAND,
    DEX_AREA_FIVE_ISLAND,
    DEX_AREA_SIX_ISLAND, // Not associated with any MAPSEC
    DEX_AREA_SEVEN_ISLAND, // Not associated with any MAPSEC
    DEX_AREA_KINDLE_ROAD,
    DEX_AREA_TREASURE_BEACH,
    DEX_AREA_CAPE_BRINK,
    DEX_AREA_BOND_BRIDGE,
    DEX_AREA_THREE_ISLE_PATH,
    DEX_AREA_RESORT_GORGEOUS,
    DEX_AREA_WATER_LABYRINTH,
    DEX_AREA_FIVE_ISLE_MEADOW,
    DEX_AREA_MEMORIAL_PILLAR,
    DEX_AREA_OUTCAST_ISLAND,
    DEX_AREA_GREEN_PATH,
    DEX_AREA_WATER_PATH,
    DEX_AREA_RUIN_VALLEY,
    DEX_AREA_TRAINER_TOWER,
    DEX_AREA_CANYON_ENTRANCE,
    DEX_AREA_SEVAULT_CANYON,
    DEX_AREA_TANOBY_RUINS,
    DEX_AREA_MT_EMBER,
    DEX_AREA_BERRY_FOREST,
    DEX_AREA_ICEFALL_CAVE,
    DEX_AREA_LOST_CAVE,
    DEX_AREA_ALTERING_CAVE,
    DEX_AREA_PATTERN_BUSH,
    DEX_AREA_DOTTED_HOLE,
    DEX_AREA_TANOBY_CHAMBER,
};

struct PokedexEntry
{
    /*0x00*/ u8 categoryName[13]; // changed to 15, set back to original value of 12.
    /*0x0C*/ u16 height; //in decimeters
    /*0x0E*/ u16 weight; //in hectograms
    /*0x10*/ const u8 *description; //dex entry text
    /*0x14*/ //const u8 *unusedDescription; //literally removed these so think can get rid of? yup no problem removing this
    /*0x18*/ //u16 unused; //set cat names to 13, because match emerald //is this safe to remove as well? yeah seems fine
    /*0x1A*/ u16 pokemonScale;
    /*0x1C*/ u16 pokemonOffset;
    /*0x1E*/ u16 trainerScale;
    /*0x20*/ u16 trainerOffset;
};  /*size = 0x24*/

//smaller struct to just take necesary values for poke forms
struct FormdexEntries
{
    const u8 *description; //dex entry text
};//description field setup like in rhh so think can possibly just take directly as was

//for the few species forms that are different enought to warrant diff category name
//typically 3 legendary birs
struct FormdexCategories
{
    u8 categoryName[13];
};

void ResetPokedex(void);
void CopyMonCategoryText(u16 species, u8 *dst);
u16 GetPokedexHeightWeight(u16 dexNum, u8 data);
u16 GetNationalPokedexCount(u8);
u16 GetKantoPokedexCount(u8);
bool16 HasAllMons(void);
u8 CreateDexDisplayMonDataTask(u16 dexNum, u32 trainerId, u32 personality);
s8 GetSetPokedexFlag(u16 nationalNum, u8 caseId);
u16 GetNationalPokedexCount(u8); //idk why Ihave 2 ofthese...apparently its defaultas
u16 EC_GetNationalPokedexCount(u8 caseID); 
u16 sub_80C0844(u8);
u16 GetKantoPokedexCount(u8);
bool16 HasAllHoennMons(void);
bool16 HasAllKantoMons(void);
bool16 HasAllMons(void);

u8 DexScreen_RegisterMonToPokedex(u16 species);

#endif // GUARD_POKEDEX_H
