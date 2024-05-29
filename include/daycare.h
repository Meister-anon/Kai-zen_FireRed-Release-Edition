#ifndef GUARD_DAYCARE_H
#define GUARD_DAYCARE_H

#include "global.h"

u8 *GetMonNick(struct Pokemon *mon, u8 *dest);
u8 *GetBoxMonNick(struct BoxPokemon *mon, u8 *dest);
u8 CountPokemonInDaycare(struct DayCare *daycare);
//void InitDaycareMailRecordMixing(struct DayCare *daycare, struct RecordMixingDayCareMail *daycareMail);
void StoreSelectedPokemonInDaycare(void);
u16 TakePokemonFromDaycare(void);
void GetDaycareCost(void);
u8 GetNumLevelsGainedFromDaycare(void);
void TriggerPendingDaycareEgg(void);
void TriggerPendingRoute5DaycareEgg(void); //new special for daycare expansion
void RejectEggFromDayCare(void);
void SetPlayerAtRoute5Daycare(void); //new special needed for daycare expansion
void ClearVarPlayerAtRoute5Daycare(void); //same as above
void CreateEgg(struct Pokemon *mon, u16 species, bool8 setHotSpringsLocation);
void GiveEggFromDaycare(void);
bool8 DoEggActions_CheckHatch(void);
u16 GetSelectedMonNickAndSpecies(void);
void GetDaycareMonNicknames(void);
u8 GetDaycareState(void);
bool8 SetEggBoost(void); //new function/special for daycare upgrade
bool8 CheckCanProduceEggs(void); //new special checks compatibility, for daycare upgrade
void SetDaycareServiceCost(void); //nother new special for setting up effect
bool8 CheckIfBoostApplied(void); //check for if boost is applied
void SetDaycareCompatibilityString(void);
bool8 NameHasGenderSymbol(const u8 *name, u8 genderRatio);
void ShowDaycareLevelMenu(void);
void ChooseSendDaycareMon(void);

u16 GetEggSpecies(u16 species); //made global for isSameSPecies file

void ScriptHatchMon(void);
bool8 sub_8071614(void);
void EggHatch(void);
u8 GetEggStepsToSubtract(void);
u16 sub_80722E0(void);
bool8 ShouldEggHatch(void);

#endif // GUARD_DAYCARE_H
