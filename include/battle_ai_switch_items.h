#ifndef GUARD_BATTLE_AI_SWITCH_ITEMS_H
#define GUARD_BATTLE_AI_SWITCH_ITEMS_H

#include "global.h"

enum
{
    AI_ITEM_FULL_RESTORE = 1,
    AI_ITEM_HEAL_HP,
    AI_ITEM_CURE_CONDITION,
    AI_ITEM_X_STAT,
    AI_ITEM_GUARD_SPECS,
    AI_ITEM_NOT_RECOGNIZABLE
};

void AI_TrySwitchOrUseItem(void);
u8 GetMostSuitableMonToSwitchInto(void);
bool32 ShouldSwitch(void);
void GetAIPartyIndexes(u32 battlerId, s32 *firstId, s32 *lastId);

#endif // GUARD_BATTLE_AI_SWITCH_ITEMS_H
