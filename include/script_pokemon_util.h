#ifndef GUARD_SCRIPT_POKEMON_UTIL_H
#define GUARD_SCRIPT_POKEMON_UTIL_H

bool8 ScriptGiveMon(u16 species, u8 level, enum Item item);
bool8 ScriptGiveMon2(u16 species, u8 level, enum Item item);
bool8 ScriptGiveEgg(u16 species, u8 isSecretEgg);
void ScriptSetMonMoveSlot(u8 partyIdx, u16 move, u8 slot);
void HealPlayerParty(void);
void ReducePlayerPartyToThree(void);
void CreateScriptedWildMon(u16 species, u8 level, u16 item);
u16 GetAveragePlayerPartyLevel(void); //use to set level

#endif //GUARD_SCRIPT_POKEMON_UTIL_H
