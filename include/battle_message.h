#ifndef GUARD_BATTLE_MESSAGE_H
#define GUARD_BATTLE_MESSAGE_H

#include "global.h"

// for 0xFD values in charmap.txt
//what I don't understand is why we don't use the same names
//as the actual buffer? If I used the actual names I wouldn't have to be guessing what I need to use.

#define B_BUFF1 0x0
#define B_BUFF2 0x1
#define B_COPY_VAR_1 0x2
#define B_COPY_VAR_2 0x3
#define B_COPY_VAR_3 0x4
#define B_PLAYER_MON1_NAME 0x5
#define B_OPPONENT_MON1_NAME 0x6
#define B_PLAYER_MON2_NAME 0x7
#define B_OPPONENT_MON2_NAME 0x8
#define B_LINK_PLAYER_MON1_NAME 0x9
#define B_LINK_OPPONENT_MON1_NAME 0xA
#define B_LINK_PLAYER_MON2_NAME 0xB
#define B_LINK_OPPONENT_MON2_NAME 0xC
#define B_ATK_NAME_WITH_PREFIX_MON1 0xD
#define B_ATK_PARTNER_NAME 0xE
#define B_ATK_NAME_WITH_PREFIX 0xF  //B_ATK_NAME_WITH_PREFIX  names used in battle_message.c are determined by charmap.txt and match this list order 0xF here FD 0F there
#define B_DEF_NAME_WITH_PREFIX 0x10
#define B_EFF_NAME_WITH_PREFIX 0x11 // EFF = short for gEffectBank
#define B_ACTIVE_NAME_WITH_PREFIX 0x12
#define B_SCR_ACTIVE_NAME_WITH_PREFIX 0x13
#define B_CURRENT_MOVE 0x14
#define B_LAST_MOVE 0x15
#define B_LAST_ITEM 0x16
#define B_LAST_ABILITY 0x17
#define B_ATK_ABILITY 0x18
#define B_DEF_ABILITY 0x19
#define B_SCR_ACTIVE_ABILITY 0x1A
#define B_EFF_ABILITY 0x1B
#define B_TRAINER1_CLASS 0x1C
#define B_TRAINER1_NAME 0x1D
#define B_LINK_PLAYER_NAME 0x1E
#define B_LINK_PARTNER_NAME 0x1F
#define B_LINK_OPPONENT1_NAME 0x20
#define B_LINK_OPPONENT2_NAME 0x21
#define B_LINK_SCR_TRAINER_NAME 0x22
#define B_PLAYER_NAME 0x23
#define B_TRAINER1_LOSE_TEXT 0x24
#define B_TRAINER1_WIN_TEXT 0x25
#define B_26 0x26
#define B_PC_CREATOR_NAME 0x27
#define B_ATK_PREFIX1 0x28
#define B_DEF_PREFIX1 0x29
#define B_ATK_PREFIX2 0x2A
#define B_DEF_PREFIX2 0x2B
#define B_ATK_PREFIX3 0x2C
#define B_DEF_PREFIX3 0x2D
#define B_TRAINER2_CLASS 0x2E
#define B_TRAINER2_NAME 0x2F
#define B_TRAINER2_LOSE_TEXT 0x30
#define B_TRAINER2_WIN_TEXT 0x31
#define B_PARTNER_CLASS 0x32
#define B_PARTNER_NAME 0x33
#define B_BUFF3 0x34
#define B_ATK_TRAINER_NAME 0x35
#define B_ATK_TRAINER_CLASS 0x36
#define B_ATK_TEAM1 0x37 // Your/The opposing
#define B_ATK_TEAM2 0x38 // your/the opposing
#define B_DEF_NAME 0x39
#define B_DEF_TEAM1 0x3A // Your/The opposing
#define B_DEF_TEAM2 0x3B // your/the opposing
#define B_ACTIVE_NAME 0x3C
#define B_ACTIVE_NAME2 0x3D // no Illusion check
#define B_ATK_ITEM 0x3E  //added for single use belch set attacker item

// for B_TXT_BUFF1, B_TXT_BUFF2 and B_TXT_BUFF3

#define B_BUFF_STRING                   0
#define B_BUFF_NUMBER                   1
#define B_BUFF_MOVE                     2
#define B_BUFF_TYPE                     3
#define B_BUFF_MON_NICK_WITH_PREFIX     4
#define B_BUFF_STAT                     5
#define B_BUFF_SPECIES                  6
#define B_BUFF_MON_NICK                 7
#define B_BUFF_NEGATIVE_FLAVOR          8
#define B_BUFF_ABILITY                  9
#define B_BUFF_ITEM                     10

#define B_BUFF_PLACEHOLDER_BEGIN        0xFD
#define B_BUFF_EOS                      0xFF

#define PREPARE_FLAVOR_BUFFER(textVar, flavorId)                            \
{                                                                           \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                                  \
    textVar[1] = B_BUFF_NEGATIVE_FLAVOR;                                    \
    textVar[2] = flavorId;                                                  \
    textVar[3] = B_BUFF_EOS;                                                \
}

#define PREPARE_STAT_BUFFER(textVar, statId)                                \
{                                                                           \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                                  \
    textVar[1] = B_BUFF_STAT;                                               \
    textVar[2] = statId;                                                    \
    textVar[3] = B_BUFF_EOS;                                                \
}

#define PREPARE_ABILITY_BUFFER(textVar, abilityId)                          \
{                                                                           \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                                  \
    textVar[1] = B_BUFF_ABILITY;                                            \
    textVar[2] = abilityId;                                                 \
    textVar[3] = (abilityId & 0xFF00) >> 8;                                 \
    textVar[4] = B_BUFF_EOS;                                                \
}

#define PREPARE_TYPE_BUFFER(textVar, typeId)                                \
{                                                                           \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                                  \
    textVar[1] = B_BUFF_TYPE;                                               \
    textVar[2] = typeId;                                                    \
    textVar[3] = B_BUFF_EOS;                                                \
}

#define PREPARE_BYTE_NUMBER_BUFFER(textVar, maxDigits, number)  \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_NUMBER;                                 \
    textVar[2] = 1;                                             \
    textVar[3] = maxDigits;                                     \
    textVar[4] = (number);                                      \
    textVar[5] = B_BUFF_EOS;                                    \
}

#define PREPARE_HWORD_NUMBER_BUFFER(textVar, maxDigits, number)             \
{                                                                           \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                                  \
    textVar[1] = B_BUFF_NUMBER;                                             \
    textVar[2] = 2;                                                         \
    textVar[3] = maxDigits;                                                 \
    textVar[4] = (number);                                                  \
    textVar[5] = (number & 0x0000FF00) >> 8;                                \
    textVar[6] = B_BUFF_EOS;                                                \
}

#define PREPARE_WORD_NUMBER_BUFFER(textVar, maxDigits, number)  \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_NUMBER;                                 \
    textVar[2] = 4;                                             \
    textVar[3] = maxDigits;                                     \
    textVar[4] = (number);                                      \
    textVar[5] = (number & 0x0000FF00) >> 8;                    \
    textVar[6] = (number & 0x00FF0000) >> 16;                   \
    textVar[7] = (number & 0xFF000000) >> 24;                   \
    textVar[8] = B_BUFF_EOS;                                    \
}

#define PREPARE_STRING_BUFFER(textVar, stringId)                \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_STRING;                                 \
    textVar[2] = stringId & 0xFF;                               \
    textVar[3] = (stringId & 0xFF00) >> 8;                      \
    textVar[4] = B_BUFF_EOS;                                    \
}//ok way this works, can't have comments or spaces after  or between backslash stuff

#define PREPARE_MOVE_BUFFER(textVar, move)                      \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_MOVE;                                   \
    textVar[2] = (move & 0xFF);                                 \
    textVar[3] = (move & 0xFF00) >> 8;                          \
    textVar[4] = B_BUFF_EOS;                                    \
}//changed  textvar 2 from just move; w update of levelup move struct

#define PREPARE_ITEM_BUFFER(textVar, item)                      \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_ITEM;                                   \
    textVar[2] = item;                                          \
    textVar[3] = (item & 0xFF00) >> 8;                          \
    textVar[4] = B_BUFF_EOS;                                    \
}

#define PREPARE_SPECIES_BUFFER(textVar, species)                \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_SPECIES;                                \
    textVar[2] = species;                                       \
    textVar[3] = (species & 0xFF00) >> 8;                       \
    textVar[4] = B_BUFF_EOS;                                    \
}

#define PREPARE_MON_NICK_WITH_PREFIX_BUFFER(textVar, bank, partyId)         \
{                                                                           \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                                  \
    textVar[1] = B_BUFF_MON_NICK_WITH_PREFIX;                               \
    textVar[2] = bank;                                                      \
    textVar[3] = partyId;                                                   \
    textVar[4] = B_BUFF_EOS;                                                \
}

#define PREPARE_MON_NICK_BUFFER(textVar, bank, partyId)         \
{                                                               \
    textVar[0] = B_BUFF_PLACEHOLDER_BEGIN;                      \
    textVar[1] = B_BUFF_MON_NICK;                               \
    textVar[2] = bank;                                          \
    textVar[3] = partyId;                                       \
    textVar[4] = B_BUFF_EOS;                                    \
}

// This buffer can hold many different things. Some of the things it can hold
// that have explicit sizes are listed below to ensure it can contain them.
#define TEXT_BUFF_ARRAY_COUNT   max(16, \
                                max(MOVE_NAME_LENGTH + 2, /* +2 to hold the "!" and EOS. */ \
                                max(POKEMON_NAME_LENGTH + 1, \
                                    ABILITY_NAME_LENGTH + 1)))

struct BattleMsgData
{
    u16 currentMove;
    u16 originallyUsedMove;
    u16 lastItem;
    u16 lastAbility;
    u8 scrActive;
    u8 bakScriptPartyIdx;
    u8 hpScale;
    u8 itemEffectBattler;
    u8 moveType;
    u16 abilities[4];
    u8 textBuffs[3][TEXT_BUFF_ARRAY_COUNT];
};

void BufferStringBattle(u16 stringID);
u32 BattleStringExpandPlaceholdersToDisplayedString(const u8* src);
u32 BattleStringExpandPlaceholders(const u8* src, u8* dst);
void BattleHandleAddTextPrinter(const u8* text, u8 arg1);
void SetPpNumbersPaletteInMoveSelection(void);
u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp);
void BattlePutTextOnWindow(const u8* text, u8 windowId_flags);
bool8 BattleStringShouldBeColored(u16);

void SetMoveTypePaletteInMoveSelection_Singles(u16 move, u8 moveType); //adapted from PP version
u8 GetTypeEffectivenessState_Singles(u16 move, u8 moveType);
void SetMoveTypePaletteInMoveSelection_Doubles(u16 move, u8 moveType); //sets target id for color
u8 GetTypeEffectivenessState_Doubles(u16 move, u8 moveType, u8 targetId);
extern struct BattleMsgData *gBattleMsgDataPtr;


extern u8 gDisplayedStringBattle[380];
extern u8 gBattleTextBuff1[TEXT_BUFF_ARRAY_COUNT];
extern u8 gBattleTextBuff2[TEXT_BUFF_ARRAY_COUNT];
extern u8 gBattleTextBuff3[TEXT_BUFF_ARRAY_COUNT];

extern const u8* const gBattleStringsTable[];
extern const u8* const gStatNamesTable[];
extern const u8* const gPokeblockWasTooXStringTable[];
extern const u8* const gRefereeStringsTable[];
extern const u8* const gStatNamesTable2[];

extern const u16 gMissStringIds[];
extern const u16 gTrappingMoves[];

extern const u8 gText_Sleep[];
extern const u8 gText_Poison[];
extern const u8 gText_Burn[];
extern const u8 gText_Paralysis[];
extern const u8 gText_Ice[];
extern const u8 gText_Confusion[];
extern const u8 gText_Love[];

extern const u8 gUnknown_83FE859[];
extern const u8 gUnknown_83FE85E[];
extern const u8 gUnknown_83FE85C[];
extern const u8 gUnknown_83FE860[];
extern const u8 gUnknown_83FE864[];

extern const u8 gText_SafariBalls[];
extern const u8 gText_HighlightRed_Left[];

extern const u8 gText_Win[];
extern const u8 gText_Loss[];
extern const u8 gText_Draw[];

#endif // GUARD_BATTLE_MESSAGE_H
