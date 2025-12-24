#ifndef GUARD_FIELD_CONTROL_AVATAR_H
#define GUARD_FIELD_CONTROL_AVATAR_H

#include "global.h"

struct FieldInput
{
    bool8 pressedAButton:1;
    bool8 checkStandardWildEncounter:1;
    bool8 pressedStartButton:1;
    bool8 pressedSelectButton:1;
    bool8 heldDirection:1;
    bool8 heldDirection2:1;
    bool8 tookStep:1;
    bool8 pressedBButton:1;
    bool8 pressedRButton:1;
    bool8 input_field_1_0:1;
    bool8 input_field_1_1:1;
    bool8 input_field_1_2:1;
    bool8 input_field_1_3:1;
    u8 dpadDirection;
};

extern struct FieldInput gFieldInputRecord;

enum PickupAbilityEventState
{
    UPDATE_PICKUP_VARIABLES,
    END_TASK_NO_VIABLE_MON,
    ASSIGN_ITEM_TO_ARRAY,
    CHECK_ITEM_SPACE, //rather than addbagitem think repalce chekbaghasspace 
    ADD_ITEM_BAG, //if true go to bag if false add to pc then do print string and loop
    ADD_ITEM_PC,
    PRINT_STRING,
    LOOP_FROM_ASSIGNMENT //check numpickup mon decrement if not 0 jump to assignment and loop //increment loopincrement
};
//if no space think print no space and return or add to pc
//had considered setup auto add to player item pc
//via addbagitem function if no space in bag
//never setup
//has add to pc function

void RestartWildEncounterImmunitySteps(void);
void ClearPoisonStepCounter(void);
void ClearOakRanchVar(void); //for box exp
int SetCableClubWarp(void);
void HandleBoulderFallThroughHole(struct ObjectEvent *);
bool8 dive_warp(struct MapPosition * pos, u16 behavior);
bool8 IsDirectionalStairWarpMetatileBehavior(u16 metatileBehavior, u8 playerDirection);
const u8 *GetInteractedLinkPlayerScript(struct MapPosition *position, u8 metatileBehavior, u8 direction);
const u8 *GetCoordEventScriptAtMapPosition(struct MapPosition *position);
void FieldClearPlayerInput(struct FieldInput *input);
int ProcessPlayerFieldInput(struct FieldInput *input);
void FieldInput_HandleCancelSignpost(struct FieldInput * input);
void FieldGetPlayerInput(struct FieldInput *input, u16 newKeys, u16 heldKeys);
void HandleBoulderActivateVictoryRoadSwitch(u16 x, u16 y);

//new additions for getting player position relative to talking object
void GetPositionByObjectEventId(u8 objectId, s16 *x, s16 *y);
void GetZCoordByObjectEventId(u8 objectId, s16 *z);

#endif //GUARD_FIELD_CONTROL_AVATAR_H
