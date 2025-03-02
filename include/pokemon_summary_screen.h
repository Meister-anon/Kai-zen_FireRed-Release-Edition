#ifndef GUARD_POKEMON_SUMMARY_SCREEN_H
#define GUARD_POKEMON_SUMMARY_SCREEN_H

#include "main.h"

extern const u8 * const gMoveDescriptionPointers[];
extern const u8 * const gNatureNamePointers[];

void ShowSelectMovePokemonSummaryScreen(struct Pokemon *, u8, u8, MainCallback, u16);
u8 GetMoveSlotToReplace(void);
void SummaryScreen_SetUnknownTaskId(u8 a0);
void SummaryScreen_DestroyUnknownTask(void);
u8 GetLastViewedMonIndex(void);
void ShowPokemonSummaryScreen(struct Pokemon *party, u8 cursorPos, u8 lastIdx, void (*callback)(void), u8 mode);
void SetPokemonSummaryScreenMode(u8);

//new additions
void ShowMoveInfoForSelectedMove(struct Pokemon *party, u8 partyMember, u8 lastIdx, MainCallback savedCallback);
void ShowSummaryScreenSelectMoveFromBattle(struct Pokemon *party, u8 partyMember, u8 lastIdx, MainCallback savedCallback, u8 mode);
void ShowPokemonSummaryScreenGoToPC(struct Pokemon * party, u8 cursorPos, u8 lastIdx, MainCallback savedCallback, u8 mode);
void PokeballIcon_CaughtIn(u8 y);
void SummScreen_ChangePokemonNickname_CB(void); //to reference callback for filtering in naming_screen

//sLevelNickTextColors
#define WHITE 0
#define RED 1
#define ORANGE 2
#define PEACH 3
#define TAN 4
#define LIGHT_GREEN 5
#define LIGHT_BLUE 6
#define BLUE 7
#define PURPLE 8
#define NAVY_BLUE 9
#define GREY_LAVENDER 10
#define LIGHT_BROWN 11
#define PINK 12
#define DARK_BLUE 13
#define BLACK 14

// The Pokemon Summary Screen can operate in different modes. Certain features,
// such as move re-ordering, are available in the different modes.
enum PokemonSummaryScreenMode
{
    PSS_MODE_NORMAL,
    PSS_MODE_UNK1,
    PSS_MODE_SELECT_MOVE,
    PSS_MODE_FORGET_MOVE,
    PSS_MODE_UNK4,
    PSS_MODE_BOX,
    PSS_MODE_BATTLE_INFO,
};

enum PokemonSummaryScreenPage
{
    PSS_PAGE_INFO,
    PSS_PAGE_SKILLS,
    PSS_PAGE_MOVES,
    PSS_PAGE_MOVES_INFO,
    PSS_PAGE_UNK4,
    PSS_PAGE_MOVE_DELETER,
};

enum PokemonSummaryScreenState3270
{
    PSS_STATE3270_0,
    PSS_STATE3270_1,
    PSS_STATE3270_2,
    PSS_STATE3270_3,
    PSS_STATE3270_4,
    PSS_STATE3270_5,
    PSS_STATE3270_6
};

enum PokemonSummaryScreenStat
{
    PSS_STAT_ATK,
    PSS_STAT_DEF,
    PSS_STAT_SPA,
    PSS_STAT_SPD,
    PSS_STAT_SPE
};

#define TAG_PSS_UNK_64 0x64
#define TAG_PSS_UNK_65 0x65
#define TAG_PSS_UNK_66 0x66
#define TAG_PSS_UNK_67 0x67
#define TAG_PSS_UNK_6E 0x6E
#define TAG_PSS_UNK_78 0x78
#define TAG_PSS_UNK_82 0x82
#define TAG_PSS_UNK_8C 0x8C
#define TAG_PSS_UNK_96 0x96
#define TAG_PSS_UNK_A0 0xA0

#endif // GUARD_POKEMON_SUMMARY_SCREEN_H
