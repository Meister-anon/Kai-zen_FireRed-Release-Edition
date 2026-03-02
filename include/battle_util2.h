#ifndef GUARD_BATTLE_UTIL2_H
#define GUARD_BATTLE_UTIL2_H

#include "global.h"

void AllocateBattleResources(void);
void FreeBattleResources(void);
void AdjustFriendshipOnBattleFaint(enum BattlerId battler);
void SwitchPartyOrderInGameMulti(enum BattlerId battler, u8 arg1);


#endif // GUARD_BATTLE_UTIL_H
