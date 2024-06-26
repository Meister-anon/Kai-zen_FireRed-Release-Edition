#ifndef GUARD_POKEDEX_SCREEN_H
#define GUARD_POKEDEX_SCREEN_H

#define DEX_MODE(name) (DEX_CATEGORY_COUNT + DEX_ORDER_##name)

#define DEX_CATEGORY_GRASSLAND     0
#define DEX_CATEGORY_FOREST        1
#define DEX_CATEGORY_WATERS_EDGE   2
#define DEX_CATEGORY_SEA           3
#define DEX_CATEGORY_CAVE          4
#define DEX_CATEGORY_MOUNTAIN      5
#define DEX_CATEGORY_ROUGH_TERRAIN 6
#define DEX_CATEGORY_URBAN         7
#define DEX_CATEGORY_RARE          8
#define DEX_CATEGORY_COUNT         9

#define DEX_ORDER_NUMERICAL_KANTO    0
#define DEX_ORDER_ATOZ               1
#define DEX_ORDER_TYPE               2
#define DEX_ORDER_LIGHTEST           3
#define DEX_ORDER_SMALLEST           4
#define DEX_ORDER_NUMERICAL_NATIONAL 5

#define DEX_MODE(name) (DEX_CATEGORY_COUNT + DEX_ORDER_##name)

#include "pokedex.h"

extern const struct PokedexEntry gPokedexEntries[];
extern const struct FormdexEntries gFormdexEntries[]; //simplified list for species forms
extern const struct FormdexCategories gFormdexCategoryName[];

void CB2_OpenPokedexFromStartMenu(void);
s8 DexScreen_GetSetPokedexFlag(u16 nationalDexNo, u8 caseId, bool8 indexIsSpecies);
u16 DexScreen_FormFilter(u16 species); //check if species should use 

//new additions for summ screen dex callback
void CB2_OpenDexPageFromSummScreen(void);
void CB2_OpenDexPageFromPCSummScreen(void); //alt needed for pc summ screen calback

void CB2_ClosePokedexGotoSummaryScreen(void);

#define END_LIST 0XFFFF


#endif //GUARD_POKEDEX_SCREEN_H
