#include "global.h"
#include "bg.h"
#include "battle.h"
#include "battle_anim.h"
#include "pokemon.h"
#include "party_menu.h"
#include "event_data.h"
#include "malloc.h"
#include "trainer_tower.h"

void AllocateBattleResources(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
        InitTrainerTowerBattleStruct();
    if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        s32 i;

        for (i = 0; i < 4; ++i)
            gPokedudeBattlerStates[i] = AllocZeroed(sizeof(struct PokedudeBattlerState));
    }
    gBattleStruct = AllocZeroed(sizeof(*gBattleStruct));
    gAiBattleData = AllocZeroed(sizeof(*gAiBattleData));
    gAiThinkingStruct = AllocZeroed(sizeof(*gAiThinkingStruct));
    gAiLogicData = AllocZeroed(sizeof(*gAiLogicData));
    gAiPartyData = AllocZeroed(sizeof(*gAiPartyData));
    gBattleHistory = AllocZeroed(sizeof(*gBattleHistory));

    gBattleResources = AllocZeroed(sizeof(*gBattleResources));
    gBattleResources->battleScriptsStack = AllocZeroed(sizeof(*gBattleResources->battleScriptsStack));
    gBattleResources->battleCallbackStack = AllocZeroed(sizeof(*gBattleResources->battleCallbackStack));
    gBattleResources->beforeLvlUp = AllocZeroed(sizeof(*gBattleResources->beforeLvlUp));
    
    //gLinkBattleSendBuffer = AllocZeroed(BATTLE_BUFFER_LINK_SIZE);
    //gLinkBattleRecvBuffer = AllocZeroed(BATTLE_BUFFER_LINK_SIZE);

    gBattleAnimBgTileBuffer = AllocZeroed(0x2000);
    gBattleAnimBgTilemapBuffer = AllocZeroed(0x1000);
    SetBgTilemapBuffer(1, gBattleAnimBgTilemapBuffer);
    SetBgTilemapBuffer(2, gBattleAnimBgTilemapBuffer);
}

void FreeBattleResources(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
        FreeTrainerTowerBattleStruct();
    if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        s32 i;

        for (i = 0; i < 4; ++i)
        {
            FREE_AND_SET_NULL(gPokedudeBattlerStates[i]);
        }
    }
    if (gBattleResources != NULL)
    {
        FREE_AND_SET_NULL(gBattleStruct);
        FREE_AND_SET_NULL(gAiBattleData);
        FREE_AND_SET_NULL(gAiThinkingStruct);
        FREE_AND_SET_NULL(gAiLogicData);
        FREE_AND_SET_NULL(gAiPartyData);
        FREE_AND_SET_NULL(gBattleHistory);

        FREE_AND_SET_NULL(gBattleResources->battleScriptsStack);
        FREE_AND_SET_NULL(gBattleResources->battleCallbackStack);
        FREE_AND_SET_NULL(gBattleResources->beforeLvlUp);

        //FREE_AND_SET_NULL(gLinkBattleSendBuffer);
        //FREE_AND_SET_NULL(gLinkBattleRecvBuffer);

        FREE_AND_SET_NULL(gBattleResources);
        FREE_AND_SET_NULL(gBattleAnimBgTileBuffer);
        FREE_AND_SET_NULL(gBattleAnimBgTilemapBuffer);
    }
}

void AdjustFriendshipOnBattleFaint(enum BattlerId battlerId)
{
    u8 opposingBattlerId, opposingBattlerId2;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        opposingBattlerId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        opposingBattlerId2 = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        if (gBattleMons[opposingBattlerId2].level > gBattleMons[opposingBattlerId].level)
            opposingBattlerId = opposingBattlerId2;
    }
    else
    {
        opposingBattlerId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    }
    if (gBattleMons[opposingBattlerId].level > gBattleMons[battlerId].level)
    {
        if (gBattleMons[opposingBattlerId].level - gBattleMons[battlerId].level > 29)
            AdjustFriendship(&gPlayerParty[gBattlerPartyIndexes[battlerId]], FRIENDSHIP_EVENT_FAINT_LARGE);
        else
            AdjustFriendship(&gPlayerParty[gBattlerPartyIndexes[battlerId]], FRIENDSHIP_EVENT_FAINT_SMALL);
    }
    else
    {
        AdjustFriendship(&gPlayerParty[gBattlerPartyIndexes[battlerId]], FRIENDSHIP_EVENT_FAINT_SMALL);
    }
}

void SwitchPartyOrderInGameMulti(enum BattlerId battler, u8 arg1)
{
    if (IsOnPlayerSide(battler))
    {
        s32 i;
        for (i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
            gBattlePartyCurrentOrder[i] = *(i + (u8 *)(gBattleStruct->battlerPartyOrders));

        SwitchPartyMonSlots(GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[battler]), GetPartyIdFromBattlePartyId(arg1));

        for (i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
            *(i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
    }
}