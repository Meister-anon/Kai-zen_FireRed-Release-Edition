#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H

void Debug_ShowMainMenu(void);
const u8 *GetWeatherName(u32 weatherId);
const struct Trainer* GetDebugAiTrainer(void);
u16 Debug_GetAbilityBySpecies(u16 species, u8 abilityNum); //using for ability capsule for case I don't need check taught ability state
void Debug_CallLvlCapMenu(void); //copy for lvl cap seutp

extern EWRAM_DATA bool8 gIsDebugBattle;
extern EWRAM_DATA u64 gDebugAIFlags;

extern EWRAM_DATA bool8 gIsDebugPC;

#endif // GUARD_DEBUG_H