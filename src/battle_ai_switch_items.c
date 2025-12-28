#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "battle_controllers.h"
#include "random.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

static bool8 HasSuperEffectiveMoveAgainstOpponents(u32 battler, bool8 noRng);
static bool8 FindMonWithFlagsAndSuperEffective(u32 battler, u8 flags, u8 moduloPercent);
static bool8 ShouldUseItem(u32 battler);
static bool32 AI_ShouldHeal(u32 battler, u32 healAmount);
static bool32 AI_OpponentCanFaintAiWithMod(u32 battler, u32 healAmount);

static bool8 ShouldSwitchIfPerishSong(u32 battler)
{
    if (gStatuses3[battler] & STATUS3_PERISH_SONG
     && gDisableStructs[battler].perishSongTimer == 0)
    {
        *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = PARTY_SIZE;
        BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//vsonic important potentially make dispirit guard version
static bool8 ShouldSwitchIfWonderGuard(u32 battler)
{
    u8 opposingBattler;
    u8 moveFlags;
    s32 i, j;
    u16 move;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        return FALSE;
    if (gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].ability == ABILITY_WONDER_GUARD)
    {
        // Check if Pokemon has a super effective move.
        for (opposingBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), i = 0; i < MAX_MON_MOVES; ++i)
        {
            move = gBattleMons[battler].moves[i];
            if (move == MOVE_NONE)
                continue;
            moveFlags = AI_TypeCalc(move, gBattleMons[opposingBattler].species, gBattleMons[opposingBattler].ability);
            if (moveFlags & MOVE_RESULT_SUPER_EFFECTIVE)
                return FALSE;
        }
        // Find a Pokemon in the party that has a super effective move.
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            if (GetMonData(&gEnemyParty[i], MON_DATA_HP) == 0
             || GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
             || GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG
             || i == gBattlerPartyIndexes[battler])
                continue;
       
            for (opposingBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), j = 0; j < MAX_MON_MOVES; ++j)
            {
                move = GetMonData(&gEnemyParty[i], MON_DATA_MOVE1 + j);
                if (move == MOVE_NONE)
                    continue;
                moveFlags = AI_TypeCalc(move, gBattleMons[opposingBattler].species, gBattleMons[opposingBattler].ability);
                if (moveFlags & MOVE_RESULT_SUPER_EFFECTIVE && Random() % 3 < 2)
                {
                    // We found a mon.
                    *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = i;
                    BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
                    return TRUE;
                }
            }
        }
    }
    return FALSE; // There is not a single Pokemon in the party that has a super effective move against a mon with Wonder Guard.
}

static bool8 FindMonThatAbsorbsOpponentsMove(u32 battler)
{
    u8 battlerIn1, battlerIn2;
    u16 absorbingTypeAbility;
    s32 i;

    if ((HasSuperEffectiveMoveAgainstOpponents(battler, TRUE) && Random() % 3) 
    || (gLastLandedMoves[battler] == MOVE_NONE))
        return FALSE;
    if (gLastLandedMoves[battler] == 0xFFFF
     || gBattleMoves[gLastLandedMoves[battler]].power == 0)
        return FALSE;
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(battler)))))
            battlerIn2 = battler;
        else
            battlerIn2 = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(battler)));
    }
    else
    {
        battlerIn1 = battler;
        battlerIn2 = battler;
    }
    if (gBattleMoves[gLastLandedMoves[battler]].type == TYPE_FIRE)
        absorbingTypeAbility = ABILITY_FLASH_FIRE;
    else if (gBattleMoves[gLastLandedMoves[battler]].type == TYPE_WATER)
        absorbingTypeAbility = ABILITY_WATER_ABSORB;
    else if (gBattleMoves[gLastLandedMoves[battler]].type == TYPE_ELECTRIC)
        absorbingTypeAbility = ABILITY_VOLT_ABSORB;
    else
        return FALSE;
    if (gBattleMons[battler].ability == absorbingTypeAbility)
        return FALSE;
    for (i = 0; i < PARTY_SIZE; ++i)
    {
        u16 species;
        u16 monAbility;

        if ((GetMonData(&gEnemyParty[i], MON_DATA_HP) == 0)
         || (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE)
         || (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
         || (i == gBattlerPartyIndexes[battlerIn1])
         || (i == gBattlerPartyIndexes[battlerIn2])
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn1))
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn2)))
            continue;
        species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES);
        /*if (GetMonData(&gEnemyParty[i], MON_DATA_ABILITY_NUM) != ABILITY_NONE)
            monAbility = gBaseStats[species].abilities[1];
        else
            monAbility = gBaseStats[species].abilities[0];
            */
        
        /*switch (GetMonData(&gEnemyParty[i], MON_DATA_ABILITY_NUM))
        {
            case 0:
                monAbility = gBaseStats[species].abilities[ABILITY_SLOT_1];
                break;
            case 1:
                monAbility = gBaseStats[species].abilities[ABILITY_SLOT_2];
                break;
            case 2:
                monAbility = gBaseStats[species].abilityHidden[HIDDEN_ABILITY_SLOT_1];
                break;
            case 3:
                monAbility = gBaseStats[species].abilityHidden[HIDDEN_ABILITY_SLOT_2];
                break;
        }*/

        monAbility = GetAbilityBySpecies(species, GetMonData(&gEnemyParty[i], MON_DATA_ABILITY_NUM), &gEnemyParty[i]);

        if (absorbingTypeAbility == monAbility && Random() & 1)
        {
            // we found a mon
            *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = i;
            BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 ShouldSwitchIfNaturalCure(u32 battler)
{
    if (!(gBattleMons[battler].status1 & STATUS1_SLEEP)
     || (gBattleMons[battler].ability != ABILITY_NATURAL_CURE)
     || (gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2))
        return FALSE;
    if ((gLastLandedMoves[battler] == MOVE_NONE || gLastLandedMoves[battler] == 0xFFFF) && Random() & 1)
    {
        *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = PARTY_SIZE;
        BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    else if (gBattleMoves[gLastLandedMoves[battler]].power == 0 && Random() & 1)
    {
        *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = PARTY_SIZE;
        BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    if (FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_DOESNT_AFFECT_FOE, 1)
     || FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_NOT_VERY_EFFECTIVE, 1))
        return TRUE;
    if (Random() & 1)
    {
        *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = PARTY_SIZE;
        BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    return FALSE;
}

static bool8 HasSuperEffectiveMoveAgainstOpponents(u32 battler, bool8 noRng)
{
    s32 i;
    u8 moveFlags;
    u16 move;
    
    u32 opposingPosition = BATTLE_OPPOSITE(GetBattlerPosition(battler));
    u32 opposingBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);

    if (!(gAbsentBattlerFlags & (1u << opposingBattler)))
    {
        for (i = 0; i < MAX_MON_MOVES; ++i)
        {
            move = gBattleMons[battler].moves[i];
            if (move == MOVE_NONE)
                continue;

            moveFlags = AI_TypeCalc(move, gBattleMons[opposingBattler].species, gBattleMons[opposingBattler].ability);
            if (moveFlags & MOVE_RESULT_SUPER_EFFECTIVE)
            {
                if (noRng || (Random() % 10))
                    return TRUE;
            }
        }
    }
    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
        return FALSE;

    opposingBattler = GetBattlerAtPosition(BATTLE_PARTNER(opposingPosition));

    if (!(gAbsentBattlerFlags & (1u << opposingBattler)))
    {
        for (i = 0; i < MAX_MON_MOVES; ++i)
        {
            move = gBattleMons[battler].moves[i];
            if (move == MOVE_NONE)
                continue;
            moveFlags = AI_TypeCalc(move, gBattleMons[opposingBattler].species, gBattleMons[opposingBattler].ability);
            if (moveFlags & MOVE_RESULT_SUPER_EFFECTIVE)
            {
                if (noRng)
                    return TRUE;
                if (Random() % 10 != 0)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

static bool8 AreStatsRaised(u32 battler)
{
    u8 buffedStatsValue = 0;
    s32 i;

    for (i = 0; i < NUM_BATTLE_STATS; ++i)
    {
        if (gBattleMons[battler].statStages[i] > 6)
            buffedStatsValue += gBattleMons[battler].statStages[i] - 6;
    }
    return (buffedStatsValue > 3);
}

static bool8 FindMonWithFlagsAndSuperEffective(u32 battler, u8 flags, u8 moduloPercent)
{
    u8 battlerIn1, battlerIn2;
    s32 i, j;
    u16 move;
    u8 moveFlags;

    if (gLastLandedMoves[battler] == 0)
        return FALSE;
    if ((gLastLandedMoves[battler] == 0xFFFF)
     || (gLastHitBy[battler] == 0xFF)
     || (gBattleMoves[gLastLandedMoves[battler]].power == 0))
        return FALSE;
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(battler)))))
            battlerIn2 = battler;
        else
            battlerIn2 = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(battler)));
    }
    else
    {
        battlerIn1 = battler;
        battlerIn2 = battler;
    }
    for (i = 0; i < PARTY_SIZE; ++i)
    {
        u16 species;
        u16 monAbility;

        if ((GetMonData(&gEnemyParty[i], MON_DATA_HP) == 0)
         || (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE)
         || (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
         || (i == gBattlerPartyIndexes[battlerIn1])
         || (i == gBattlerPartyIndexes[battlerIn2])
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn1))
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn2)))
            continue;
        species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES);

        //idk what this is for yet but will need to rework this part
        //for hidden abilities will prob use switch case
        /*if (GetMonData(&gEnemyParty[i], MON_DATA_ABILITY_NUM) != ABILITY_NONE)
            monAbility = gBaseStats[species].abilities[1];
        else
            monAbility = gBaseStats[species].abilities[0];
        */

        monAbility = GetAbilityBySpecies(species, GetMonData(&gEnemyParty[i], MON_DATA_ABILITY_NUM), &gEnemyParty[i]);

        moveFlags = AI_TypeCalc(gLastLandedMoves[battler], species, monAbility);
        if (moveFlags & flags)
        {
            battlerIn1 = gLastHitBy[battler];
            for (j = 0; j < MAX_MON_MOVES; ++j)
            {
                move = GetMonData(&gEnemyParty[i], MON_DATA_MOVE1 + j);
                if (move == MOVE_NONE)
                    continue;
                moveFlags = AI_TypeCalc(move, gBattleMons[battlerIn1].species, gBattleMons[battlerIn1].ability);
                if (moveFlags & MOVE_RESULT_SUPER_EFFECTIVE && Random() % moduloPercent == 0)
                {
                    *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = i;
                    BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

bool32 ShouldSwitch(u32 battler)
{
    u8 battlerIn1, battlerIn2;
    s32 i;
    s32 availableToSwitch;

    if ((gBattleMons[battler].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION | STATUS2_SWITCH_LOCKED))
     || (gBattleMons[battler].status4 & ITS_A_TRAP_STATUS4)
     || (gStatuses3[battler] & STATUS3_ROOTED)
     || AbilityBattleEffects(ABILITYEFFECT_CHECK_OTHER_SIDE, battler, ABILITY_SHADOW_TAG, 0, 0)
     || AbilityBattleEffects(ABILITYEFFECT_CHECK_OTHER_SIDE, battler, ABILITY_ARENA_TRAP, 0, 0))
        return FALSE; // misses the flying or levitate check /and hands of fate for shadow tag
    if (AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_MAGNET_PULL, 0, 0))
        if ((gBattleMons[battler].type1 == TYPE_STEEL) || (gBattleMons[battler].type2 == TYPE_STEEL))
            return FALSE;
    availableToSwitch = 0;
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetBattlerAtPosition(GetBattlerPosition(BATTLE_PARTNER(battler)))))
            battlerIn2 = battler;
        else
            battlerIn2 = GetBattlerAtPosition(GetBattlerPosition(BATTLE_PARTNER(battler)));
    }
    else
    {
        battlerIn2 = battler;
        battlerIn1 = battler;
    }
    for (i = 0; i < PARTY_SIZE; ++i)
    {
        if ((GetMonData(&gEnemyParty[i], MON_DATA_HP) == 0)
         || (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE)
         || (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
         || (i == gBattlerPartyIndexes[battlerIn1])
         || (i == gBattlerPartyIndexes[battlerIn2])
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn1))
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn2)))
            continue;
        ++availableToSwitch;
    }
    if (!availableToSwitch)
        return FALSE;
    if (ShouldSwitchIfPerishSong(battler)
     || ShouldSwitchIfWonderGuard(battler)
     || FindMonThatAbsorbsOpponentsMove(battler)
     || ShouldSwitchIfNaturalCure(battler))
        return TRUE;
    if (HasSuperEffectiveMoveAgainstOpponents(battler, FALSE)
     || AreStatsRaised(battler))
        return FALSE;
    if (FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_DOESNT_AFFECT_FOE, 2)
     || FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_NOT_VERY_EFFECTIVE, 3))
        return TRUE;
    return FALSE;
}

void AI_TrySwitchOrUseItem(u32 battler)
{
    u8 battlerIn1, battlerIn2;

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        if (ShouldSwitch(battler))
        {
            if (*(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) == 6)
            {
                s32 monToSwitchId = GetMostSuitableMonToSwitchInto(battler);
                if (monToSwitchId == 6)
                {
                    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
                    {
                        battlerIn1 = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
                        battlerIn2 = battlerIn1;
                    }
                    else
                    {
                        battlerIn1 = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
                        battlerIn2 = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
                    }
                    for (monToSwitchId = 0; monToSwitchId < PARTY_SIZE; ++monToSwitchId)
                    {
                        if ((!GetMonData(&gEnemyParty[monToSwitchId], MON_DATA_HP) == 0)
                         && (monToSwitchId != gBattlerPartyIndexes[battlerIn1])
                         && (monToSwitchId != gBattlerPartyIndexes[battlerIn2])
                         && (monToSwitchId != *(gBattleStruct->monToSwitchIntoId + battlerIn1))
                         && (monToSwitchId != *(gBattleStruct->monToSwitchIntoId + battlerIn2)))
                            break;
                    }
                }
                *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1)) = monToSwitchId;
            }
            *(gBattleStruct->monToSwitchIntoId + battler) = *(gBattleStruct->AI_monToSwitchIntoId + (GetBattlerPosition(battler) >> 1));
            return;
        }
        else if (ShouldUseItem(battler))
        {
            return;
        }
    }
    BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_USE_MOVE, (battler ^ BIT_SIDE) << 8);
}

//remove part of cleanup to make gtypeeffectiveness array static
static void ModulateByTypeEffectiveness(u8 atkType, u8 defType1, u8 defType2, u8 *var)
{
    s32 i = 0;

    /*while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE)
    {
        if (TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT)
        {
            i += 3;
            continue;
        }
        else if (TYPE_EFFECT_ATK_TYPE(i) == atkType)
        {
            // Check type1.
            if (TYPE_EFFECT_DEF_TYPE(i) == defType1)
                *var = (*var * TYPE_EFFECT_MULTIPLIER(i)) / 10;
            // Check type2.
            if (TYPE_EFFECT_DEF_TYPE(i) == defType2 && defType1 != defType2)
                *var = (*var * TYPE_EFFECT_MULTIPLIER(i)) / 10;
        }
        i += 3;
    }*/
}

static u32 GetBestMonTypeMatchup(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 battler, u32 opposingBattler)
{
    int i, bits = 0;

    while (bits != 0x3F) // All mons were checked.
    {
        uq4_12_t bestResist = UQ_4_12(1.0);
        int bestMonId = PARTY_SIZE;
        // Find the mon whose type is the most suitable defensively.
        for (i = firstId; i < lastId; i++)
        {
            if (!((1u << i) & invalidMons) && !((1u << i) & bits))
            {
                u16 species = GetMonData(&party[i], MON_DATA_SPECIES);
                uq4_12_t typeEffectiveness = UQ_4_12(1.0);

                u8 atkType1 = gBattleMons[opposingBattler].type1;
                u8 atkType2 = gBattleMons[opposingBattler].type2;
                u8 defType1 = gBaseStats[species].type1;
                u8 defType2 = gBaseStats[species].type2;

                typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType1)));
                if (atkType2 != atkType1)
                    typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType1)));
                if (defType2 != defType1)
                {
                    typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType2)));
                    if (atkType2 != atkType1)
                        typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType2)));
                }
                if (typeEffectiveness < bestResist)
                {
                    bestResist = typeEffectiveness;
                    bestMonId = i;
                }
            }
        }

        // Ok, we know the mon has the right typing but does it have at least one super effective move?
        if (bestMonId != PARTY_SIZE)
        {
            for (i = 0; i < MAX_MON_MOVES; i++)
            {
                u32 move = GetMonData(&party[bestMonId], MON_DATA_MOVE1 + i);
                if (move != MOVE_NONE && AI_GetMoveEffectiveness(move, battler, opposingBattler) >= UQ_4_12(2.0))
                    break;
            }

            if (i != MAX_MON_MOVES)
                return bestMonId; // Has both the typing and at least one super effective move.

            bits |= (1u << bestMonId); // Sorry buddy, we want something better.
        }
        else
        {
            bits = 0x3F; // No viable mon to switch.
        }
    }

    return PARTY_SIZE;
}

u8 GetMostSuitableMonToSwitchInto(u32 battler)
{
    u8 opposingBattler;
    u8 bestDmg; // Note : should be changed to u32 for obvious reasons.
    u8 bestMonId;
    u8 battlerIn1, battlerIn2;
    s32 i, j;
    s32 firstId = 0;
    s32 lastId = 0; // + 1
    u8 invalidMons;
    u16 move;
    struct Pokemon *party;


    


    if (*(gBattleStruct->monToSwitchIntoId + battler) != PARTY_SIZE)
        return *(gBattleStruct->monToSwitchIntoId + battler);
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetBattlerAtPosition(GetBattlerPosition(battler) ^ BIT_FLANK)))
            battlerIn2 = battler;
        else
            battlerIn2 = GetBattlerAtPosition(GetBattlerPosition(battler) ^ BIT_FLANK);
        // UB: It considers the opponent only player's side even though it can battle alongside player.
        opposingBattler = Random() & BIT_FLANK;
        if (gAbsentBattlerFlags & (1u << opposingBattler))
            opposingBattler ^= BIT_FLANK;
    }
    else
    {
        opposingBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        battlerIn1 = battler;
        battlerIn2 = battler;
    }

    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);

    //can slot GetBestMonTypeMatchup in here
    //identical comments for this section
    bestMonId = GetBestMonTypeMatchup(party, firstId, lastId, invalidMons, battler, opposingBattler);
        if (bestMonId != PARTY_SIZE)
            return bestMonId;
            

    /*invalidMons = 0;
    while (invalidMons != 0x3F) // All mons are invalid.
    {
        bestDmg = 0;
        bestMonId = 6;
        // Find the mon whose type is the most suitable offensively.
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            u16 species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES);
            if (species != SPECIES_NONE
                && GetMonData(&gEnemyParty[i], MON_DATA_HP) != 0
                && !((1u << i) & invalidMons)
                && gBattlerPartyIndexes[battlerIn1] != i
                && gBattlerPartyIndexes[battlerIn2] != i
                && i != *(gBattleStruct->monToSwitchIntoId + battlerIn1)
                && i != *(gBattleStruct->monToSwitchIntoId + battlerIn2))
            {
                u8 type1 = gBaseStats[species].type1;
                u8 type2 = gBaseStats[species].type2;
                u8 typeDmg = 10;
                ModulateByTypeEffectiveness(gBattleMons[opposingBattler].type1, type1, type2, &typeDmg);
                ModulateByTypeEffectiveness(gBattleMons[opposingBattler].type2, type1, type2, &typeDmg);
                if (bestDmg < typeDmg)
                {
                    bestDmg = typeDmg;
                    bestMonId = i;
                }
            }
            else
            {
                invalidMons |= (1u << i);
            }
        }
        // Ok, we know the mon has the right typing but does it have at least one super effective move?
        if (bestMonId != PARTY_SIZE)
        {
            for (i = 0; i < MAX_MON_MOVES; ++i)
            {
                move = GetMonData(&gEnemyParty[bestMonId], MON_DATA_MOVE1 + i);
                if (move != MOVE_NONE && TypeCalc(move, battler, opposingBattler) & MOVE_RESULT_SUPER_EFFECTIVE)
                    break;
            }
            if (i != MAX_MON_MOVES)
                return bestMonId; // Has both the typing and at least one super effective move.

            invalidMons |= (1u << bestMonId); // Sorry buddy, we want something better.
        }
        else
        {
            invalidMons = 0x3F; // No viable mon to switch.
        }
    }*/


    gDynamicBasePower = 0;
    gBattleStruct->dynamicMoveType = 0;
    //gBattleScripting.dmgMultiplier = 1;
    gMoveResultFlags = 0;
    gCritMultiplier = 1;
    bestDmg = 0;
    bestMonId = 6;
    // If we couldn't find the best mon in terms of typing, find the one that deals most damage.
    for (i = 0; i < PARTY_SIZE; ++i)
    {
        if (((u16)(GetMonData(&gEnemyParty[i], MON_DATA_SPECIES)) == SPECIES_NONE)
         || (GetMonData(&gEnemyParty[i], MON_DATA_HP) == 0)
         || (gBattlerPartyIndexes[battlerIn1] == i)
         || (gBattlerPartyIndexes[battlerIn2] == i)
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn1))
         || (i == *(gBattleStruct->monToSwitchIntoId + battlerIn2)))
            continue;
        for (j = 0; j < MAX_MON_MOVES; ++j)
        {
            move = GetMonData(&gEnemyParty[i], MON_DATA_MOVE1 + j);
            gBattleMoveDamage = 0;
            if (move != MOVE_NONE && gBattleMoves[move].power != 1)
            {
                AI_CalcDmg(battler, opposingBattler);
                TypeCalc(move, battler, opposingBattler);
            }
            if (bestDmg < gBattleMoveDamage)
            {
                bestDmg = gBattleMoveDamage;
                bestMonId = i;
            }
        }
    }
    return bestMonId;
}

void GetAIPartyIndexes(u32 battlerId, s32 *firstId, s32 *lastId)
{
    if (BATTLE_TWO_VS_ONE_OPPONENT && (battlerId & BIT_SIDE) == B_SIDE_OPPONENT)
    {
        *firstId = 0, *lastId = PARTY_SIZE;
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_INGAME_PARTNER))
    {
        if ((battlerId & BIT_FLANK) == B_FLANK_LEFT)
            *firstId = 0, *lastId = PARTY_SIZE / 2;
        else
            *firstId = PARTY_SIZE / 2, *lastId = PARTY_SIZE;
    }
    else
    {
        *firstId = 0, *lastId = PARTY_SIZE;
    }
}

static u8 GetAI_ItemType(u8 itemId, const u8 *itemEffect) // NOTE: should take u16 as item Id argument
{
    if (itemId == ITEM_FULL_RESTORE)
        return AI_ITEM_FULL_RESTORE;
    else if (itemEffect[4] & ITEM4_HEAL_HP)
        return AI_ITEM_HEAL_HP;
    else if (itemEffect[3] & ITEM3_STATUS_ALL)
        return AI_ITEM_CURE_CONDITION;
    else if (itemEffect[0] & (ITEM0_HIGH_CRIT | ITEM0_X_ATTACK) || itemEffect[1] != 0 || itemEffect[2] != 0)
        return AI_ITEM_X_STAT;
    else if (itemEffect[3] & ITEM3_MIST)
        return AI_ITEM_GUARD_SPECS;
    else
        return AI_ITEM_NOT_RECOGNIZABLE;
}

static bool32 AiExpectsToFaintPlayer(u32 battler)
{

    u8 target = gBattleStruct->aiChosenTarget[battler];

    if (gBattleStruct->aiMoveOrAction[battler] > 3)
        return FALSE; // AI not planning to use move

    if (GetBattlerSide(target) != GetBattlerSide(battler)
      && CanIndexMoveFaintTarget(battler, target, gBattleStruct->aiMoveOrAction[battler], 0)
      && AI_WhoStrikesFirst(battler, target, GetAIChosenMove(battler)) == AI_IS_FASTER) {
        // We expect to faint the target and move first -> dont use an item
        return TRUE;
    }

    return FALSE;
}

static bool8 ShouldUseItem(u32 battler)
{
    struct Pokemon *party;
    s32 i;
    u8 validMons = 0;
    bool8 shouldUse = FALSE;
    // If teaming up with player and Pokemon is on the right, or Pokemon is currently held by Sky Drop
    if ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT)
       || gStatuses3[battler] & STATUS3_SKY_DROPPED)
        return FALSE;

    if (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_EMBARGO)
        return FALSE;

    if (AiExpectsToFaintPlayer(battler))
        return FALSE;

    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_HP) != 0
            && GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
            && GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG)
        {
            validMons++;
        }
    }
    for (i = 0; i < MAX_TRAINER_ITEMS; i++)
    {
        u16 item;
        const u8 *itemEffects;
        u8 paramOffset;
        u8 battlerSide;
        if (i != 0 && validMons > (gBattleResources->battleHistory->itemsNo - i) + 1)
            continue;
        item = gBattleResources->battleHistory->trainerItems[i];
        if (item == ITEM_NONE)
            continue;
        if (gItemEffectTable[item - ITEM_POTION] == NULL)
            continue;
        if (item == ITEM_ENIGMA_BERRY)
            itemEffects = gSaveBlock1Ptr->enigmaBerry.itemEffect;
        else
            itemEffects = gItemEffectTable[item - ITEM_POTION];
        *(gBattleStruct->AI_itemType + battler / 2) = GetAI_ItemType(item, itemEffects);
        switch (*(gBattleStruct->AI_itemType + battler / 2))
        {
        case AI_ITEM_FULL_RESTORE:
            if (gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 4)
                break;
            if (gBattleMons[battler].hp == 0)
                break;
            shouldUse = TRUE;
            shouldUse = AI_ShouldHeal(battler, 0);
            break;
        case AI_ITEM_HEAL_HP:
            paramOffset = GetItemEffectParamOffset(battler, item, 4, 4);
            if (paramOffset == 0 || gBattleMons[battler].hp == 0)
                break;
            if (gBattleMons[battler].hp < gBattleMons[battler].maxHP / 4 
                || gBattleMons[battler].maxHP - gBattleMons[battler].hp > itemEffects[paramOffset])
                shouldUse = TRUE;
            shouldUse = AI_ShouldHeal(battler, itemEffects[GetItemEffectParamOffset(battler, item, 4, 4)]);
            break;
        case AI_ITEM_CURE_CONDITION:
            *(gBattleStruct->AI_itemFlags + battler / 2) = 0;
            if (itemEffects[3] & ITEM3_SLEEP && gBattleMons[battler].status1 & STATUS1_SLEEP)
            {
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x20;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_POISON 
            && (gBattleMons[battler].status1 & STATUS1_POISON || gBattleMons[battler].status1 & STATUS1_TOXIC_POISON))
            {
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x10;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_BURN && gBattleMons[battler].status1 & STATUS1_BURN)
            {
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x8;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_FREEZE && gBattleMons[battler].status1 & STATUS1_FREEZE)
            {
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x4;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_PARALYSIS && gBattleMons[battler].status1 & STATUS1_PARALYSIS)
            {
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x2;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_CONFUSION && gBattleMons[battler].status2 & STATUS2_CONFUSION)
            {
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x1;
                shouldUse = TRUE;
            }
            break;
        case AI_ITEM_X_STAT:
            *(gBattleStruct->AI_itemFlags + battler / 2) = 0;
            if (gDisableStructs[battler].isFirstTurn == 0)
                break;
        #ifndef ITEM_EXPANSION
            if (itemEffects[0] & ITEM0_X_ATTACK)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x1;
            if (itemEffects[1] & ITEM1_X_DEFEND)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x2;
            if (itemEffects[1] & ITEM1_X_SPEED)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x4;
            if (itemEffects[2] & ITEM2_X_SPATK)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x8;
            if (itemEffects[2] & ITEM2_X_ACCURACY)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x20;
            if (itemEffects[0] & ITEM0_HIGH_CRIT)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= 0x80;
        #else
            if (itemEffects[1] & ITEM1_X_ATTACK)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_X_ATTACK);
            if (itemEffects[1] & ITEM1_X_DEFENSE)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_X_DEFEND);
            if (itemEffects[1] & ITEM1_X_SPEED)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_X_SPEED);
            if (itemEffects[1] & ITEM1_X_SPATK)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_X_SPATK);
            if (itemEffects[1] & ITEM1_X_SPDEF)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_X_SPDEF);
            if (itemEffects[1] & ITEM1_X_ACCURACY)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_X_ACCURACY);
            if (itemEffects[0] & ITEM0_DIRE_HIT)
                *(gBattleStruct->AI_itemFlags + battler / 2) |= (1 << AI_DIRE_HIT);
        #endif
            shouldUse = TRUE;
            break;
        case AI_ITEM_GUARD_SPECS:
            battlerSide = GetBattlerSide(battler);
            if (gDisableStructs[battler].isFirstTurn && gSideTimers[battlerSide].mistTimer == 0)
                shouldUse = TRUE;
            break;
        case AI_ITEM_NOT_RECOGNIZABLE:
            return FALSE;
        }
        if (shouldUse)
        {
            //vsonic important look into later
            //if (gBattleStruct->itemPartyIndex[battler] == PARTY_SIZE)
            //    gBattleStruct->itemPartyIndex[battler] = gBattlerPartyIndexes[battler];
            BtlController_EmitTwoReturnValues(battler, B_COMM_TO_ENGINE, B_ACTION_USE_ITEM, 0);
            *(gBattleStruct->chosenItem + (battler / 2) * 2) = item;
            gBattleResources->battleHistory->trainerItems[i] = 0;
            return shouldUse;
        }
    }

    return FALSE;
}

static bool32 AI_ShouldHeal(u32 battler, u32 healAmount)
{
    bool32 shouldHeal = FALSE;

    if (gBattleMons[battler].hp < gBattleMons[battler].maxHP / 4
     || gBattleMons[battler].hp == 0
     || (healAmount != 0 && gBattleMons[battler].maxHP - gBattleMons[battler].hp > healAmount)) {
        // We have low enough HP to consider healing
        shouldHeal = !AI_OpponentCanFaintAiWithMod(battler, healAmount); // if target can kill us even after we heal, why bother
    }

    return shouldHeal;
}

static bool32 AI_OpponentCanFaintAiWithMod(u32 battler, u32 healAmount)
{
    u32 i;
    // Check special cases to NOT heal
    for (i = 0; i < gBattlersCount; i++) {
        if (GetBattlerSide(i) == B_SIDE_PLAYER) {
            if (CanTargetFaintAiWithMod(i, battler, healAmount, 0)) {
                // Target is expected to faint us
                return TRUE;
            }
        }
    }
    return FALSE;
}