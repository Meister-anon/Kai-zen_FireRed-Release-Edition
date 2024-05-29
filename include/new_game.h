#ifndef GUARD_NEW_GAME_H
#define GUARD_NEW_GAME_H

#include "global.h"

extern bool8 gDifferentSaveFile;

void SetTrainerId(u32 trainerId, u8 *dst);
void CopyTrainerId(u8 *dst, u8 *src);
void NewGameInitData(void);
void ResetMenuAndMonGlobals(void);
void Sav2_ClearSetDefault(void);

extern const u16 *const gMartItemIndexesbyGymBadge[NUM_BADGES + 1]; //add for attempt at new script command

u8 GetNumBadges(void);//used for mart scripts made in scrcmd.c wasn't sure where to put

#endif // GUARD_NEW_GAME_H
