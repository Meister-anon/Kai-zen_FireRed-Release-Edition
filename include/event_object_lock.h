#ifndef GUARD_EVENT_OBJECT_LOCK_H
#define GUARD_EVENT_OBJECT_LOCK_H

#include "global.h"

bool8 NativeScript_WaitPlayerStopMoving(void);
void ScriptFreezeObjectEvents(void);
bool8 NativeScript_WaitPlayerAndTargetNPCStopMoving(void);
void LockSelectedObjectEvent(void);
void ClearPlayerHeldMovementAndUnfreezeObjectEvents(void);
bool8 IsPlayerStandingStill(void);
void UnionRoom_UnlockPlayerAndChatPartner(void);

//void sub_8098630(void);
//bool8 sub_8098734(void);

//bool8 IsFreezePlayerFinished(void);
//bool8 IsFreezeSelectedObjectAndPlayerFinished(void);
//void FreezeObjects_WaitForPlayer(void);
//void FreezeObjects_WaitForPlayerAndSelected(void);
void FreezeForApproachingTrainers(void);
bool8 IsFreezeObjectAndPlayerFinished(void);
//void ScriptUnfreezeObjectEvents(void);

#endif // GUARD_EVENT_OBJECT_LOCK_H
