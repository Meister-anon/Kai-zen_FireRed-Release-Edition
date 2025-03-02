#include "global.h"
#include "gflib.h"
#include "bike.h"
#include "coord_event_weather.h"
#include "daycare.h"
#include "debug.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_control_avatar.h"
#include "field_fadetransition.h"
#include "field_player_avatar.h"
#include "field_poison.h"
#include "field_specials.h"
#include "item_menu.h"
#include "link.h"
#include "menews_jisan.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "renewable_hidden_items.h"
#include "quest_log.h"
#include "safari_zone.h"
#include "script.h"
#include "start_menu.h"
#include "trainer_see.h"
#include "vs_seeker.h"
#include "wild_encounter.h"
#include "config/overworld.h"
#include "constants/songs.h"
#include "constants/event_bg.h"
#include "constants/event_objects.h"
#include "constants/maps.h"
#include "constants/metatile_behaviors.h"
#include "constants/abilities.h"
#include "pokemon.h"
#include "random.h"
#include "field_message_box.h"
#include "party_menu.h"
#include "item.h"
#include "battle_script_commands.h"
#include "strings.h"
#include "constants/items.h"    //for NUM_TECHNICAL_MACHINES constant


#define SIGNPOST_POKECENTER 0
#define SIGNPOST_POKEMART 1
#define SIGNPOST_INDIGO_1 2
#define SIGNPOST_INDIGO_2 3
#define SIGNPOST_SCRIPTED 240
#define SIGNPOST_NA 255

static void QuestLogOverrideJoyVars(struct FieldInput *input, u16 *newKeys, u16 *heldKeys);
static void Task_QuestLogPlayback_OpenStartMenu(u8 taskId);
static void GetPlayerPosition(struct MapPosition * position);
static void GetInFrontOfPlayerPosition(struct MapPosition * position);
static u16 GetPlayerCurMetatileBehavior(void);
static bool8 TryStartInteractionScript(struct MapPosition * position, u16 metatileBehavior, u8 playerDirection);
static const u8 *GetInteractionScript(struct MapPosition * position, u8 metatileBehavior, u8 playerDirection);
static const u8 *GetInteractedObjectEventScript(struct MapPosition * position, u8 metatileBehavior, u8 playerDirection);
static const u8 *GetInteractedBackgroundEventScript(struct MapPosition * position, u8 metatileBehavior, u8 playerDirection);
static const struct BgEvent *GetBackgroundEventAtPosition(struct MapHeader *, u16, u16, u8);
static const u8 *GetInteractedMetatileScript(struct MapPosition * position, u8 metatileBehavior, u8 playerDirection);
static const u8 *GetInteractedWaterScript(struct MapPosition * position, u8 metatileBehavior, u8 playerDirection);
static bool8 TryStartStepBasedScript(struct MapPosition * position, u16 metatileBehavior, u16 playerDirection);
static bool8 TryStartCoordEventScript(struct MapPosition * position);
static bool8 TryStartMiscWalkingScripts(u16 metatileBehavior);
static bool8 TryStartStepCountScript(u16 metatileBehavior);
static void UpdateHappinessStepCounter(void);
static void UpdatePickupCounter(void);
static void UpdateBoxEXPStepCounter(void);
static bool8 UpdatePoisonStepCounter(void);
static bool8 CheckStandardWildEncounter(u32 encounter);
static bool8 TrySetUpWalkIntoSignpostScript(struct MapPosition * position, u16 metatileBehavior, u8 playerDirection);
static void SetUpWalkIntoSignScript(const u8 *script, u8 playerDirection);
static u8 GetFacingSignpostType(u16 metatileBehvaior, u8 direction);
static const u8 *GetSignpostScriptAtMapPosition(struct MapPosition * position);
static bool8 TryArrowWarp(struct MapPosition * position, u16 metatileBehavior, u8 playerDirection);
static bool8 TryStartWarpEventScript(struct MapPosition * position, u16 metatileBehavior);
static bool8 IsWarpMetatileBehavior(u16 metatileBehavior);
static void SetupWarp(struct MapHeader * mapHeader, s8 warpId, struct MapPosition * position);
static bool8 IsArrowWarpMetatileBehavior(u16 metatileBehavior, u8 playerDirection);
static s8 GetWarpEventAtMapPosition(struct MapHeader * mapHeader, struct MapPosition * mapPosition);
static bool8 TryDoorWarp(struct MapPosition * position, u16 metatileBehavior, u8 playerDirection);
static s8 GetWarpEventAtPosition(struct MapHeader * mapHeader, u16 x, u16 y, u8 z);
static const u8 *GetCoordEventScriptAtPosition(struct MapHeader * mapHeader, u16 x, u16 y, u8 z);


struct PickupItem
{
    u16 itemId;
    u8 chance;
};

//revert to static and move these 2 to field_control_avatar?
//but would still need it for battle_util.c  ;  nvm will make separate one for that, since not all of these items can be used in battle
//and I'm going to be setting the list as held items
static const struct PickupItem sPickupItems[] =
{
    { ITEM_ORAN_BERRY, 15 },
    { ITEM_CHERI_BERRY, 25 },
    { ITEM_CHESTO_BERRY, 35 },
    { ITEM_PECHA_BERRY, 45 },
    { ITEM_POKE_BALL, 50 },
    { ITEM_RAWST_BERRY, 55 },
    { ITEM_ASPEAR_BERRY, 65 },
    { ITEM_PERSIM_BERRY, 75 },
    { ITEM_TM10, 80 },
    { ITEM_PP_UP, 85 },
    { ITEM_RARE_CANDY, 90 },
    { ITEM_NUGGET, 95 },
    { ITEM_SPELON_BERRY, 96 },
    { ITEM_PAMTRE_BERRY, 97 },
    { ITEM_WATMEL_BERRY, 98 },
    { ITEM_DURIN_BERRY, 99 },
    { ITEM_LUXURY_BALL, 100 },
};

struct FieldInput gInputToStoreInQuestLogMaybe;

void FieldClearPlayerInput(struct FieldInput *input)
{
    input->pressedAButton = FALSE;
    input->checkStandardWildEncounter = FALSE;
    input->pressedStartButton = FALSE;
    input->pressedSelectButton = FALSE;
    input->heldDirection = FALSE;
    input->heldDirection2 = FALSE;
    input->tookStep = FALSE;
    input->pressedBButton = FALSE;
    input->pressedRButton = FALSE;
    input->input_field_1_0 = FALSE;
    input->input_field_1_1 = FALSE;
    input->input_field_1_2 = FALSE;
    input->input_field_1_3 = FALSE;
    input->dpadDirection = 0;
}

void FieldGetPlayerInput(struct FieldInput *input, u16 newKeys, u16 heldKeys)
{
    u8 runningState = gPlayerAvatar.runningState;
    u8 tileTransitionState = gPlayerAvatar.tileTransitionState;
    bool8 forcedMove = MetatileBehavior_IsForcedMovementTile(GetPlayerCurMetatileBehavior());

    if (!ScriptContext1_IsScriptSetUp() && IsQuestLogInputDpad() == TRUE)
    {
        QuestLogOverrideJoyVars(input, &newKeys, &heldKeys);
    }
    if ((tileTransitionState == T_TILE_CENTER && forcedMove == FALSE) || tileTransitionState == T_NOT_MOVING)
    {
        if (GetPlayerSpeed() != 4)
        {
            if ((newKeys & START_BUTTON) && !(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_FISHING))
                input->pressedStartButton = TRUE;
            if (!QL_IS_PLAYBACK_STATE)
            {
                if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_FISHING))
                {
                    if (newKeys & SELECT_BUTTON)
                        input->pressedSelectButton = TRUE;
                    if (newKeys & A_BUTTON)
                        input->pressedAButton = TRUE;
                    if (newKeys & B_BUTTON)
                        input->pressedBButton = TRUE;
                    if (newKeys & R_BUTTON)
                        input->pressedRButton = TRUE;
                }
            }
        }

        if (!QL_IS_PLAYBACK_STATE)
        {
            if (heldKeys & (DPAD_UP | DPAD_DOWN | DPAD_LEFT | DPAD_RIGHT))
            {
                input->heldDirection = TRUE;
                input->heldDirection2 = TRUE;
            }
        }

    }

    if (forcedMove == FALSE)
    {
        if (tileTransitionState == T_TILE_CENTER && runningState == MOVING)
            input->tookStep = TRUE;
        if (forcedMove == FALSE && tileTransitionState == T_TILE_CENTER)
            input->checkStandardWildEncounter = TRUE;
    }

    if (!QL_IS_PLAYBACK_STATE)
    {
        if (heldKeys & DPAD_UP)
            input->dpadDirection = DIR_NORTH;
        else if (heldKeys & DPAD_DOWN)
            input->dpadDirection = DIR_SOUTH;
        else if (heldKeys & DPAD_LEFT)
            input->dpadDirection = DIR_WEST;
        else if (heldKeys & DPAD_RIGHT)
            input->dpadDirection = DIR_EAST;
    }

#if DEBUG_OVERWORLD_MENU == TRUE && DEBUG_OVERWORLD_IN_MENU == FALSE
    if ((heldKeys & DEBUG_OVERWORLD_HELD_KEYS) && input->DEBUG_OVERWORLD_TRIGGER_EVENT)
    {
        input->input_field_1_2 = TRUE;
        input->DEBUG_OVERWORLD_TRIGGER_EVENT = FALSE;
    }
#endif
}

static void QuestLogOverrideJoyVars(struct FieldInput *input, u16 *newKeys, u16 *heldKeys)
{
    switch (GetRegisteredQuestLogInput())
    {
    case QL_INPUT_OFF:
        break;
    case QL_INPUT_UP:
        *heldKeys = *newKeys = DPAD_UP;
        break;
    case QL_INPUT_DOWN:
        *heldKeys = *newKeys = DPAD_DOWN;
        break;
    case QL_INPUT_LEFT:
        *heldKeys = *newKeys = DPAD_LEFT;
        break;
    case QL_INPUT_RIGHT:
        *heldKeys = *newKeys = DPAD_RIGHT;
        break;
    case QL_INPUT_L:
        *heldKeys = *newKeys = L_BUTTON;
        break;
    case QL_INPUT_R:
        *heldKeys = *newKeys = R_BUTTON;
        break;
    case QL_INPUT_START:
        *heldKeys = *newKeys = START_BUTTON;
        break;
    case QL_INPUT_SELECT:
        *heldKeys = *newKeys = SELECT_BUTTON;
        break;
    }
    ClearQuestLogInputIsDpadFlag();
    ClearQuestLogInput();
}

int ProcessPlayerFieldInput(struct FieldInput *input)
{
    struct MapPosition position;
    u8 playerDirection;
    u16 metatileBehavior;
    u32 r8;

    ResetFacingNpcOrSignPostVars();
    playerDirection = GetPlayerFacingDirection();
    GetPlayerPosition(&position);
    r8 = MapGridGetMetatileAttributeAt(position.x, position.y, 0xFF);
    metatileBehavior = MapGridGetMetatileBehaviorAt(position.x, position.y);

    FieldClearPlayerInput(&gInputToStoreInQuestLogMaybe);
    gInputToStoreInQuestLogMaybe.dpadDirection = input->dpadDirection;

    if (CheckForTrainersWantingBattle() == TRUE)
        return TRUE;

    if (TryRunOnFrameMapScript() == TRUE)
        return TRUE;

    if (input->tookStep)
    {
        IncrementGameStat(GAME_STAT_STEPS);
        MENewsJisanStepCounter();
        IncrementRenewableHiddenItemStepCounter();
        RunMassageCooldownStepCounter();
        IncrementResortGorgeousStepCounter();
        IncrementBirthIslandRockStepCount();
        if (TryStartStepBasedScript(&position, metatileBehavior, playerDirection) == TRUE)
        {
            gInputToStoreInQuestLogMaybe.tookStep = TRUE;
            return TRUE;
        }
    }
    if (input->checkStandardWildEncounter)
    {
        if (input->dpadDirection == 0 || input->dpadDirection == playerDirection)
        {
            GetInFrontOfPlayerPosition(&position);
            metatileBehavior = MapGridGetMetatileBehaviorAt(position.x, position.y);
            if (TrySetUpWalkIntoSignpostScript(&position, metatileBehavior, playerDirection) == TRUE)
            {
                gInputToStoreInQuestLogMaybe.checkStandardWildEncounter = TRUE;
                return TRUE;
            }
            GetPlayerPosition(&position);
            metatileBehavior = MapGridGetMetatileBehaviorAt(position.x, position.y);
        }
    }
    if (input->checkStandardWildEncounter && CheckStandardWildEncounter(r8) == TRUE)
    {
        gInputToStoreInQuestLogMaybe.checkStandardWildEncounter = TRUE;
        return TRUE;
    }
    if (input->heldDirection && input->dpadDirection == playerDirection)
    {
        if (TryArrowWarp(&position, metatileBehavior, playerDirection) == TRUE)
        {
            gInputToStoreInQuestLogMaybe.heldDirection = TRUE;
            return TRUE;
        }
    }

    GetInFrontOfPlayerPosition(&position);
    metatileBehavior = MapGridGetMetatileBehaviorAt(position.x, position.y);
    if (input->heldDirection && input->dpadDirection == playerDirection)
    {
        if (TrySetUpWalkIntoSignpostScript(&position, metatileBehavior, playerDirection) == TRUE)
        {
            gInputToStoreInQuestLogMaybe.heldDirection = TRUE;
            return TRUE;
        }
    }

    if (input->pressedAButton && TryStartInteractionScript(&position, metatileBehavior, playerDirection) == TRUE)
    {
        gInputToStoreInQuestLogMaybe.pressedAButton = TRUE;
        return TRUE;
    }

    if (input->heldDirection2 && input->dpadDirection == playerDirection)
    {
        if (TryDoorWarp(&position, metatileBehavior, playerDirection) == TRUE)
        {
            gInputToStoreInQuestLogMaybe.heldDirection2 = TRUE;
            return TRUE;
        }
    }

    if (input->pressedStartButton)
    {
        gInputToStoreInQuestLogMaybe.pressedStartButton = TRUE;
        FlagSet(FLAG_OPENED_START_MENU);
        PlaySE(SE_WIN_OPEN);
        ShowStartMenu();
        return TRUE;
    }
    if (input->pressedSelectButton && UseRegisteredKeyItemOnField() == TRUE)
    {
        gInputToStoreInQuestLogMaybe.pressedSelectButton = TRUE;
        return TRUE;
    }

#if DEBUG_OVERWORLD_MENU == TRUE && DEBUG_OVERWORLD_IN_MENU == FALSE
    if (input->input_field_1_2)
    {
        PlaySE(SE_WIN_OPEN);
        FreezeObjectEvents();
        Debug_ShowMainMenu();
        return TRUE;
    }
#endif

    return FALSE;
}

void FieldInput_HandleCancelSignpost(struct FieldInput * input)
{
    if (ScriptContext1_IsScriptSetUp() == TRUE)
    {
        if (gWalkAwayFromSignInhibitTimer != 0)
            gWalkAwayFromSignInhibitTimer--;
        else if (CanWalkAwayToCancelMsgBox() == TRUE)
        {
            if (input->dpadDirection != 0 && GetPlayerFacingDirection() != input->dpadDirection)
            {
                if (IsMsgBoxWalkawayDisabled() == TRUE)
                    return;
                if (input->dpadDirection == DIR_NORTH)
                    RegisterQuestLogInput(QL_INPUT_UP);
                else if (input->dpadDirection == DIR_SOUTH)
                    RegisterQuestLogInput(QL_INPUT_DOWN);
                else if (input->dpadDirection == DIR_WEST)
                    RegisterQuestLogInput(QL_INPUT_LEFT);
                else if (input->dpadDirection == DIR_EAST)
                    RegisterQuestLogInput(QL_INPUT_RIGHT);
                ScriptContext1_SetupScript(EventScript_CancelMessageBox);
                LockPlayerFieldControls();
            }
            else if (input->pressedStartButton)
            {
                ScriptContext1_SetupScript(EventScript_CancelMessageBox);
                LockPlayerFieldControls();
                if (!FuncIsActiveTask(Task_QuestLogPlayback_OpenStartMenu))
                    CreateTask(Task_QuestLogPlayback_OpenStartMenu, 8);
            }
        }
    }
}

static void Task_QuestLogPlayback_OpenStartMenu(u8 taskId)
{
    if (!ArePlayerFieldControlsLocked())
    {
        PlaySE(SE_WIN_OPEN);
        ShowStartMenu();
        DestroyTask(taskId);
    }
}

static void GetPlayerPosition(struct MapPosition *position)
{
    PlayerGetDestCoords(&position->x, &position->y);
    position->height = PlayerGetZCoord();
}

static void GetInFrontOfPlayerPosition(struct MapPosition *position)
{
    s16 x, y;

    GetXYCoordsOneStepInFrontOfPlayer(&position->x, &position->y);
    PlayerGetDestCoords(&x, &y);
    if (MapGridGetZCoordAt(x, y) != 0)
        position->height = PlayerGetZCoord();
    else
        position->height = 0;
}

void GetPositionByObjectEventId(u8 objectId, s16 *x, s16 *y)
{
    *x = gObjectEvents[objectId].currentCoords.x;
    *y = gObjectEvents[objectId].currentCoords.y;
}

void GetZCoordByObjectEventId(u8 objectId, s16 *z)
{
    *z = gObjectEvents[objectId].previousElevation;
}

static u16 GetPlayerCurMetatileBehavior(void)
{
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    return MapGridGetMetatileBehaviorAt(x, y);
}

static bool8 TryStartInteractionScript(struct MapPosition *position, u16 metatileBehavior, u8 direction)
{
    const u8 *script = GetInteractionScript(position, metatileBehavior, direction);
    if (script == NULL)
        return FALSE;

    // Don't play interaction sound for certain scripts.
    if (script != PalletTown_PlayersHouse_2F_EventScript_PC
        && script != EventScript_PC)
        PlaySE(SE_SELECT);

    ScriptContext1_SetupScript(script);
    return TRUE;
}

static const u8 *GetInteractionScript(struct MapPosition *position, u8 metatileBehavior, u8 direction)
{
    const u8 *script = GetInteractedObjectEventScript(position, metatileBehavior, direction);
    if (script != NULL)
        return script;

    script = GetInteractedBackgroundEventScript(position, metatileBehavior, direction);
    if (script != NULL)
        return script;

    script = GetInteractedMetatileScript(position, metatileBehavior, direction);
    if (script != NULL)
        return script;

    script = GetInteractedWaterScript(position, metatileBehavior, direction);
    if (script != NULL)
        return script;

    return NULL;
}

const u8 *GetInteractedLinkPlayerScript(struct MapPosition *position, u8 metatileBehavior, u8 direction)
{
    u8 objectEventId;
    s32 i;

    if (!MetatileBehavior_IsCounter(MapGridGetMetatileBehaviorAt(position->x, position->y)))
        objectEventId = GetObjectEventIdByXYZ(position->x, position->y, position->height);
    else
        objectEventId = GetObjectEventIdByXYZ(position->x + gDirectionToVectors[direction].x, position->y + gDirectionToVectors[direction].y, position->height);

    if (objectEventId == OBJECT_EVENTS_COUNT || gObjectEvents[objectEventId].localId == OBJ_EVENT_ID_PLAYER)
        return NULL;

    for (i = 0; i < MAX_LINK_PLAYERS; i++)
    {
        if (gLinkPlayerObjectEvents[i].active == TRUE && gLinkPlayerObjectEvents[i].objEventId == objectEventId)
            return NULL;
    }

    gSelectedObjectEvent = objectEventId;
    gSpecialVar_LastTalked = gObjectEvents[objectEventId].localId;
    gSpecialVar_Facing = direction;
    return GetObjectEventScriptPointerByObjectEventId(objectEventId);
}

static const u8 *GetInteractedObjectEventScript(struct MapPosition *position, u8 metatileBehavior, u8 direction)
{
    u8 objectEventId;
    const u8 *script;

    objectEventId = GetObjectEventIdByXYZ(position->x, position->y, position->height);
    if (objectEventId == OBJECT_EVENTS_COUNT || gObjectEvents[objectEventId].localId == OBJ_EVENT_ID_PLAYER)
    {
        if (MetatileBehavior_IsCounter(metatileBehavior) != TRUE)
            return NULL;

        // Look for an object event on the other side of the counter.
        objectEventId = GetObjectEventIdByXYZ(position->x + gDirectionToVectors[direction].x, position->y + gDirectionToVectors[direction].y, position->height);
        if (objectEventId == OBJECT_EVENTS_COUNT || gObjectEvents[objectEventId].localId == OBJ_EVENT_ID_PLAYER)
            return NULL;
    }

   /* if (InUnionRoom() == TRUE && !ObjectEventCheckHeldMovementStatus(&gObjectEvents[objectEventId]))
        return NULL;*/

    gSelectedObjectEvent = objectEventId;
    gSpecialVar_LastTalked = gObjectEvents[objectEventId].localId;
    gSpecialVar_Facing = direction;

    script = GetObjectEventScriptPointerByObjectEventId(objectEventId);

    script = GetRamScript(gSpecialVar_LastTalked, script);
    return script;
}

static const u8 *GetInteractedBackgroundEventScript(struct MapPosition *position, u8 metatileBehavior, u8 direction)
{
    u8 signpostType;
    const struct BgEvent *bgEvent = GetBackgroundEventAtPosition(&gMapHeader, position->x - 7, position->y - 7, position->height);

    if (bgEvent == NULL)
        return NULL;
    if (bgEvent->bgUnion.script == NULL)
        return EventScript_TestSignpostMsg;

    signpostType = GetFacingSignpostType(metatileBehavior, direction);

    switch (bgEvent->kind)
    {
    case BG_EVENT_PLAYER_FACING_ANY:
    default:
        break;
    case BG_EVENT_PLAYER_FACING_NORTH:
        if (direction != DIR_NORTH)
            return NULL;
        break;
    case BG_EVENT_PLAYER_FACING_SOUTH:
        if (direction != DIR_SOUTH)
            return NULL;
        break;
    case BG_EVENT_PLAYER_FACING_EAST:
        if (direction != DIR_EAST)
            return NULL;
        break;
    case BG_EVENT_PLAYER_FACING_WEST:
        if (direction != DIR_WEST)
            return NULL;
        break;
    case 5:
    case 6:
    case BG_EVENT_HIDDEN_ITEM:
        if (GetHiddenItemAttr((u32)bgEvent->bgUnion.script, HIDDEN_ITEM_UNDERFOOT) == TRUE)
            return NULL;
        gSpecialVar_0x8005 = GetHiddenItemAttr((u32)bgEvent->bgUnion.script, HIDDEN_ITEM_ID);
        gSpecialVar_0x8004 = GetHiddenItemAttr((u32)bgEvent->bgUnion.script, HIDDEN_ITEM_FLAG);
        gSpecialVar_0x8006 = GetHiddenItemAttr((u32)bgEvent->bgUnion.script, HIDDEN_ITEM_QUANTITY);
        if (FlagGet(gSpecialVar_0x8004) == TRUE)
            return NULL;
        gSpecialVar_Facing = direction;
        return EventScript_HiddenItemScript;
    }

    if (signpostType != SIGNPOST_NA)
        MsgSetSignPost();
    gSpecialVar_Facing = direction;
    return bgEvent->bgUnion.script;
}

static const u8 *GetInteractedMetatileScript(struct MapPosition *position, u8 metatileBehavior, u8 direction)
{
    gSpecialVar_Facing = direction;
    if (MetatileBehavior_IsPC(metatileBehavior) == TRUE)
        return EventScript_PC;
    if (MetatileBehavior_IsRegionMap(metatileBehavior) == TRUE)
        return EventScript_WallTownMap;
    if (MetatileBehavior_IsBookshelf(metatileBehavior) == TRUE)
        return gUnknown_81A7606;
    if (MetatileBehavior_IsPokeMartShelf(metatileBehavior) == TRUE)
        return gUnknown_81A760F;
    if (MetatileBehavior_IsFood(metatileBehavior) == TRUE)
        return gUnknown_81A7618;
    if (MetatileBehavior_IsImpressiveMachine(metatileBehavior) == TRUE)
        return gUnknown_81A7633;
    if (MetatileBehavior_IsBlueprints(metatileBehavior) == TRUE)
        return gUnknown_81A763C;
    if (MetatileBehavior_IsVideoGame(metatileBehavior) == TRUE)
        return gUnknown_81A7621;
    if (MetatileBehavior_IsBurglary(metatileBehavior) == TRUE)
        return gUnknown_81A7645;
    if (MetatileBehavior_IsComputer(metatileBehavior) == TRUE)
        return gUnknown_81A762A;
    if (MetatileBehavior_IsMBA3(metatileBehavior) == TRUE)
        return TrainerTower_EventScript_ShowTime;
    if (MetatileBehavior_IsPlayerFacingTVScreen(metatileBehavior, direction) == TRUE)
        return gUnknown_81A764E;
    if (MetatileBehavior_IsCabinet(metatileBehavior) == TRUE)
        return gUnknown_81A7657;
    if (MetatileBehavior_IsKitchen(metatileBehavior) == TRUE)
        return gUnknown_81A7660;
    if (MetatileBehavior_IsDresser(metatileBehavior) == TRUE)
        return gUnknown_81A7669;
    if (MetatileBehavior_IsSnacks(metatileBehavior) == TRUE)
        return gUnknown_81A7672;
    if (MetatileBehavior_IsPainting(metatileBehavior) == TRUE)
        return gUnknown_81A767B;
    if (MetatileBehavior_IsPowerPlantMachine(metatileBehavior) == TRUE)
        return gUnknown_81A7684;
    if (MetatileBehavior_IsTelephone(metatileBehavior) == TRUE)
        return gUnknown_81A768D;
    if (MetatileBehavior_IsAdvertisingPoster(metatileBehavior) == TRUE)
        return gUnknown_81A7696;
    if (MetatileBehavior_IsTastyFood(metatileBehavior) == TRUE)
        return gUnknown_81A769F;
    if (MetatileBehavior_IsTrashBin(metatileBehavior) == TRUE)
        return gUnknown_81A76A8;
    if (MetatileBehavior_IsCup(metatileBehavior) == TRUE)
        return gUnknown_81A76B1;
    if (MetatileBehavior_ReturnFalse_19(metatileBehavior) == TRUE)
        return gUnknown_81A76BA;
    if (MetatileBehavior_ReturnFalse_20(metatileBehavior) == TRUE)
        return gUnknown_81A76C3;
    if (MetatileBehavior_IsBlinkingLights(metatileBehavior) == TRUE)
        return gUnknown_81A76CC;
    if (MetatileBehavior_IsMB9F(metatileBehavior) == TRUE)
        return gUnknown_81A76D5;
    if (MetatileBehavior_IsPlayerFacingMB_8D(metatileBehavior, direction) == TRUE)
        return CableClub_EventScript_81BBFD8;
    if (MetatileBehavior_IsQuestionnaire(metatileBehavior) == TRUE)
        return EventScript_Questionnaire;
    if (MetatileBehavior_IsPlayerFacingBattleRecords(metatileBehavior, direction) == TRUE)
        return CableClub_EventScript_ShowBattleRecords;
    if (MetatileBehavior_IsIndigoPlateauMark(metatileBehavior) == TRUE)
    {
        MsgSetSignPost();
        return EventScript_Indigo_UltimateGoal;
    }
    if (MetatileBehavior_IsIndigoPlateauMark2(metatileBehavior) == TRUE)
    {
        MsgSetSignPost();
        return EventScript_Indigo_HighestAuthority;
    }
    if (MetatileBehavior_IsPlayerFacingPokeMartSign(metatileBehavior, direction) == TRUE)
    {
        MsgSetSignPost();
        return EventScript_PokemartSign;
    }
    if (MetatileBehavior_IsPlayerFacingPokemonCenterSign(metatileBehavior, direction) == TRUE)
    {
        MsgSetSignPost();
        return EventScript_PokecenterSign;
    }
    return NULL;
}

static const u8 *GetInteractedWaterScript(struct MapPosition *unused1, u8 metatileBehavior, u8 direction)
{

    if (MetatileBehavior_IsSemiDeepWater(metatileBehavior) == TRUE && PartyHasMonWithSurf() == TRUE)    
        return EventScript_CurrentTooFast;
    if (PartyHasMonWithSurf() == TRUE && IsPlayerFacingSurfableFishableWater() == TRUE)
        return EventScript_UseSurf;

    if (MetatileBehavior_IsWaterfall(metatileBehavior) == TRUE)
    {
        //SLIGHT effect change here, instead of requiring waterfall mon just have badge and mon that can surf
        if (ShouldDisplayHMFieldMove(FIELD_MOVE_WATERFALL) && IsPlayerSurfingNorth() == TRUE)
            return EventScript_Waterfall;
        else
            return EventScript_CantUseWaterfall;
    }
    return NULL;
}

static bool8 TryStartStepBasedScript(struct MapPosition *position, u16 metatileBehavior, u16 direction)
{
    if (TryStartCoordEventScript(position) == TRUE)
        return TRUE;
    if (TryStartWarpEventScript(position, metatileBehavior) == TRUE)
        return TRUE;
    if (TryStartMiscWalkingScripts(metatileBehavior) == TRUE)
        return TRUE;
    if (TryStartStepCountScript(metatileBehavior) == TRUE)
        return TRUE;
    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_FISHING) && !MetatileBehavior_IsForcedMovementTile(metatileBehavior) && UpdateRepelCounter() == TRUE)
        return TRUE;
    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_FISHING) && !MetatileBehavior_IsForcedMovementTile(metatileBehavior) && UpdateBadOnionCounter() == TRUE)
        return TRUE;
    return FALSE;
}

static bool8 TryStartCoordEventScript(struct MapPosition *position)
{
    const u8 *script = GetCoordEventScriptAtPosition(&gMapHeader, position->x - 7, position->y - 7, position->height);

    if (script == NULL)
        return FALSE;
    ScriptContext1_SetupScript(script);
    return TRUE;
}

static bool8 TryStartMiscWalkingScripts(u16 metatileBehavior)
{
    // Dummied
    return FALSE;
}

static bool8 TryStartStepCountScript(u16 metatileBehavior)
{
    u8 i;
    bool8 found = FALSE;



    /*if (InUnionRoom() == TRUE)
        return FALSE;*/
    if (gQuestLogState == QL_STATE_PLAYBACK)
        return FALSE;

    UpdateHappinessStepCounter();

    for (i = 0; i < PARTY_SIZE; ++i)
    {

        if ((GetMonAbility(&gPlayerParty[i]) == ABILITY_PICKUP)
        && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)) //works, also learned daycare eggs aren't treated as species egg, cuz don't sue species2
        {
            found = TRUE;

        }//forgot exclude egg from check, its triggering for eggs

        if (IsNuzlockeModeOn() && (GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) == 0)
        && FlagGet(FLAG_SYS_POKEDEX_GET))
            found = FALSE; //ensure mon not counted if dead by nuzlocke clause
    }

    UpdateBoxEXPStepCounter(); //hope works    //put out here so still works with movement scripts
    

    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_FISHING) && !MetatileBehavior_IsForcedMovementTile(metatileBehavior))
    {
        /*if (UpdateVsSeekerStepCounter() == TRUE)
        {
            ScriptContext1_SetupScript(EventScript_VsSeekerChargingDone);
            return TRUE;
        }
        else */
        if (found == TRUE)
            UpdatePickupCounter();

        else if (found == FALSE)    //if doesn't find pickup mon in party, reset counter to 0
        {
            VarSet(VAR_PICKUP_COUNTER, 0);
        }    
        
        
        if (UpdatePoisonStepCounter() == TRUE)
        {
            ScriptContext1_SetupScript(EventScript_FieldPoison);
            return TRUE;
        }//below is else if to prevent occuring at same time

        else if (ShouldEggHatch())
        {
            IncrementGameStat(GAME_STAT_HATCHED_EGGS);
            ScriptContext1_SetupScript(EventScript_EggHatch);
            return TRUE;
        }
    }
    if (SafariZoneTakeStep() == TRUE)
        return TRUE;
    return FALSE;
}

static void Unref_ClearHappinessStepCounter(void)
{
    VarSet(VAR_HAPPINESS_STEP_COUNTER, 0);
}

static void UpdateHappinessStepCounter(void)
{
    u16 *ptr = GetVarPointer(VAR_HAPPINESS_STEP_COUNTER);
    int i;

    (*ptr)++;
    (*ptr) %= 128;
    if (*ptr == 0)
    {
        struct Pokemon *mon = gPlayerParty;
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (!(IsNuzlockeModeOn() && (GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) == 0)
            && FlagGet(FLAG_SYS_POKEDEX_GET)))
            AdjustFriendship(mon, FRIENDSHIP_EVENT_WALKING);
            mon++;
        }
    }
}

static void UpdatePickupCounter(void)
{
    u16 *ptr = GetVarPointer(VAR_PICKUP_COUNTER);
    s32 i;
    u32 j,k;
    s32 randomTM = Random() % NUM_TECHNICAL_MACHINES;   //using will make function automatically scale
    u16 arrayItem = sPickupItems[j].itemId;
    

    (*ptr)++;       //increment counter
    (*ptr) %= 325;   //wrap around at 325

        for (i = 0; i < PARTY_SIZE; ++i)
        {
            if (GetMonAbility(&gPlayerParty[i]) == ABILITY_PICKUP)
                break;
        } //looks in party for mon with pickup, functionally stops at first party slot that encounters ability


        if (*ptr == 0)  //can use pointer without ability check, as ability check is already in call for this function
        {
            s32 random = Random() % 101;
            for (j = 0; j < ARRAY_COUNT(sPickupItems); ++j) //minus 1 was specific for this array, as it wasn't made to go to last value, I changed it.
            {
                if (sPickupItems[j].chance > random)
                    break;
            }

            if ((sPickupItems[j].itemId == ITEM_TM10_HIDDEN_POWER) && (BagGetQuantityByItemId(ITEM_TM10_HIDDEN_POWER) != 0))
            {    //makes it only do swap 1/3rd of the time
                if ((Random() % 3) == 0)
                {
                    for (k = ITEM_NONE; k != ITEMS_COUNT; k++)
                    {
                        if (gItems[k].pocket != POCKET_TM_CASE)
                            continue;
                        if (ItemIdToBattleMoveId(k) == gTM_Moves[randomTM])
                            break;
                    }
                    arrayItem = (k);// give random tm, if already have tm10, will put add random%3  so not super easy to get everything
                }                    
                else
                    arrayItem = sPickupItems[j].itemId;
            }
            else
                arrayItem = sPickupItems[j].itemId;

            if (AddBagItem(sPickupItems[j].itemId, 1) == TRUE)  //attempting remove from loop. think placing within made it add for each value of  the array. yup that's why *facepalm
            {

                GetMonNickname(&gPlayerParty[i], gStringVar2);  //for battle effect
                CopyItemName(sPickupItems[j].itemId, gStringVar1);
                LockForFieldEffect();

                ShowFieldMessage(gText_MonPickedUpItem);
                ScriptContext1_SetupScript(EventScript_DelayedCancelMessageBox);

            }

        }
    
}

static void UpdateBoxEXPStepCounter(void)
{
    u16 *ptr = GetVarPointer(VAR_OAK_RANCH_COUNTER_WRAP);


    if (FlagGet(FLAG_START_OAK_RANCH_COUNTER))
    {
        (*ptr)++;
        (*ptr) %= 7; //wrap around to increment exp
        if (*ptr == 0)
        {
            //flag set on deposit to pc, just need to have clear and reset on exit pc
            gSaveBlock1Ptr->oakRanchStepCounter++; //hope works    //put out here so still works with movement scripts
        }
    }
    else if (*ptr != 0) //if flag nto set and pointer isn't 0
        ClearOakRanchVar(); //should auto clear var, when flag gets cleared

}

void ClearOakRanchVar(void)
{
    VarSet(VAR_OAK_RANCH_COUNTER_WRAP, 0);
}



void ClearPoisonStepCounter(void)
{
    VarSet(VAR_POISON_STEP_COUNTER, 0);
}

static bool8 UpdatePoisonStepCounter(void)
{
    u16 *ptr;

    if (gMapHeader.mapType != MAP_TYPE_SECRET_BASE)
    {
        ptr = GetVarPointer(VAR_POISON_STEP_COUNTER);
        (*ptr)++;
        (*ptr) %= 5;    //wrap around value
        if (*ptr == 0)//when the counter wraps around to do the effect
        {
            switch (DoPoisonFieldEffect())
            {
            case FLDPSN_NONE:
                return FALSE;
            case FLDPSN_PSN:
                return FALSE;
            case FLDPSN_FNT:
                return TRUE;
            }
        }
    }
    return FALSE;
}

void RestartWildEncounterImmunitySteps(void)
{
    ResetEncounterRateModifiers();
}

static bool8 CheckStandardWildEncounter(u32 encounter)
{
#if OW_FLAG_NO_ENCOUNTER != 0
    if (FlagGet(OW_FLAG_NO_ENCOUNTER))
        return FALSE;
#endif

    return TryStandardWildEncounter(encounter);
}

static bool8 TrySetUpWalkIntoSignpostScript(struct MapPosition * position, u16 metatileBehavior, u8 playerDirection)
{
    u8 r4;
    const u8 * script;
    if (JOY_HELD(DPAD_LEFT | DPAD_RIGHT))
        return FALSE;
    if (playerDirection == DIR_EAST || playerDirection == DIR_WEST)
        return FALSE;

    r4 = GetFacingSignpostType(metatileBehavior, playerDirection);
    if (r4 == SIGNPOST_POKECENTER)
    {
        SetUpWalkIntoSignScript(EventScript_PokecenterSign, playerDirection);
        return TRUE;
    }
    else if (r4 == SIGNPOST_POKEMART)
    {
        SetUpWalkIntoSignScript(EventScript_PokemartSign, playerDirection);
        return TRUE;
    }
    else if (r4 == SIGNPOST_INDIGO_1)
    {
        SetUpWalkIntoSignScript(EventScript_Indigo_UltimateGoal, playerDirection);
        return TRUE;
    }
    else if (r4 == SIGNPOST_INDIGO_2)
    {
        SetUpWalkIntoSignScript(EventScript_Indigo_HighestAuthority, playerDirection);
        return TRUE;
    }
    else
    {
        script = GetSignpostScriptAtMapPosition(position);
        if (script == NULL)
            return FALSE;
        if (r4 != SIGNPOST_SCRIPTED)
            return FALSE;
        SetUpWalkIntoSignScript(script, playerDirection);
        return TRUE;
    }
}

static u8 GetFacingSignpostType(u16 metatileBehavior, u8 playerDirection)
{
    if (MetatileBehavior_IsPlayerFacingPokemonCenterSign(metatileBehavior, playerDirection) == TRUE)
        return SIGNPOST_POKECENTER;

    if (MetatileBehavior_IsPlayerFacingPokeMartSign(metatileBehavior, playerDirection) == TRUE)
        return SIGNPOST_POKEMART;

    if (MetatileBehavior_IsIndigoPlateauMark(metatileBehavior) == TRUE)
        return SIGNPOST_INDIGO_1;

    if (MetatileBehavior_IsIndigoPlateauMark2(metatileBehavior) == TRUE)
        return SIGNPOST_INDIGO_2;

    if (MetatileBehavior_IsSignpost(metatileBehavior) == TRUE)
        return SIGNPOST_SCRIPTED;

    return SIGNPOST_NA;
}

static void SetUpWalkIntoSignScript(const u8 *script, u8 playerDirection)
{
    gSpecialVar_Facing = playerDirection;
    ScriptContext1_SetupScript(script);
    SetWalkingIntoSignVars();
    MsgSetSignPost();
}

static const u8 *GetSignpostScriptAtMapPosition(struct MapPosition * position)
{
    const struct BgEvent * event = GetBackgroundEventAtPosition(&gMapHeader, position->x - 7, position->y - 7, position->height);
    if (event == NULL)
        return NULL;
    if (event->bgUnion.script != NULL)
        return event->bgUnion.script;
    return EventScript_TestSignpostMsg;
}

static bool8 TryArrowWarp(struct MapPosition *position, u16 metatileBehavior, u8 direction)
{
    s8 warpEventId = GetWarpEventAtMapPosition(&gMapHeader, position);
    u16 delay;

    if (warpEventId != -1)
    {
        if (IsArrowWarpMetatileBehavior(metatileBehavior, direction) == TRUE)
        {
            StoreInitialPlayerAvatarState();
            SetupWarp(&gMapHeader, warpEventId, position);
            DoWarp();
            return TRUE;
        }
        else if (IsDirectionalStairWarpMetatileBehavior(metatileBehavior, direction) == TRUE)
        {
            delay = 0;
            if (gPlayerAvatar.flags & (PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
            {
                SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
                delay = 12;
            }
            StoreInitialPlayerAvatarState();
            SetupWarp(&gMapHeader, warpEventId, position);
            DoStairWarp(metatileBehavior, delay);
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 TryStartWarpEventScript(struct MapPosition *position, u16 metatileBehavior)
{
    s8 warpEventId = GetWarpEventAtMapPosition(&gMapHeader, position);

    if (warpEventId != -1 && IsWarpMetatileBehavior(metatileBehavior) == TRUE)
    {
        StoreInitialPlayerAvatarState();
        SetupWarp(&gMapHeader, warpEventId, position);
        if (MetatileBehavior_IsEscalator(metatileBehavior) == TRUE)
        {
            DoEscalatorWarp(metatileBehavior);
            return TRUE;
        }
        if (MetatileBehavior_IsLavaridgeB1FWarp(metatileBehavior) == TRUE)
        {
            DoLavaridgeGymB1FWarp();
            return TRUE;
        }
        if (MetatileBehavior_IsLavaridge1FWarp(metatileBehavior) == TRUE)
        {
            DoLavaridgeGym1FWarp();
            return TRUE;
        }
        if (MetatileBehavior_IsWarpPad(metatileBehavior) == TRUE)
        {
            DoTeleportWarp();
            return TRUE;
        }
        if (MetatileBehavior_IsUnionRoomWarp(metatileBehavior) == TRUE)
        {
            DoUnionRoomWarp();
            return TRUE;
        }
        if (MetatileBehavior_IsFallWarp(metatileBehavior) == TRUE)
        {
            ResetInitialPlayerAvatarState();
            ScriptContext1_SetupScript(EventScript_1C1361);
            return TRUE;
        }
        DoWarp();
        return TRUE;
    }
    return FALSE;
}

static bool8 IsWarpMetatileBehavior(u16 metatileBehavior)
{
    if (MetatileBehavior_IsWarpDoor(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsLadder(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsEscalator(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsNonAnimDoor(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsLavaridgeB1FWarp(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsLavaridge1FWarp(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsWarpPad(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsFallWarp(metatileBehavior) == TRUE)
        return TRUE;
    if (MetatileBehavior_IsUnionRoomWarp(metatileBehavior) == TRUE)
        return TRUE;
    return FALSE;
}

bool8 IsDirectionalStairWarpMetatileBehavior(u16 metatileBehavior, u8 playerDirection)
{
    switch (playerDirection)
    {
    case DIR_WEST:
        if (MetatileBehavior_IsDirectionalUpLeftStairWarp(metatileBehavior))
            return TRUE;
        if (MetatileBehavior_IsDirectionalDownLeftStairWarp(metatileBehavior))
            return TRUE;
        break;
    case DIR_EAST:
        if (MetatileBehavior_IsDirectionalUpRightStairWarp(metatileBehavior))
            return TRUE;
        if (MetatileBehavior_IsDirectionalDownRightStairWarp(metatileBehavior))
            return TRUE;
        break;
    }
    return FALSE;
}

static bool8 IsArrowWarpMetatileBehavior(u16 metatileBehavior, u8 direction)
{
    switch (direction)
    {
    case DIR_NORTH:
        return MetatileBehavior_IsNorthArrowWarp(metatileBehavior);
    case DIR_SOUTH:
        return MetatileBehavior_IsSouthArrowWarp(metatileBehavior);
    case DIR_WEST:
        return MetatileBehavior_IsWestArrowWarp(metatileBehavior);
    case DIR_EAST:
        return MetatileBehavior_IsEastArrowWarp(metatileBehavior);
    }
    return FALSE;
}

static s8 GetWarpEventAtMapPosition(struct MapHeader *mapHeader, struct MapPosition *position)
{
    return GetWarpEventAtPosition(mapHeader, position->x - 7, position->y - 7, position->height);
}

static void SetupWarp(struct MapHeader *unused, s8 warpEventId, struct MapPosition *position)
{
    const struct WarpEvent *warpEvent;

    warpEvent = &gMapHeader.events->warps[warpEventId];

    if (warpEvent->mapNum == MAP_NUM(NONE))
    {
        SetWarpDestinationToDynamicWarp(warpEvent->warpId);
    }
    else
    {
        const struct MapHeader *mapHeader;

        SetWarpDestinationToMapWarp(warpEvent->mapGroup, warpEvent->mapNum, warpEvent->warpId);
        UpdateEscapeWarp(position->x, position->y);
        mapHeader = Overworld_GetMapHeaderByGroupAndId(warpEvent->mapGroup, warpEvent->mapNum);
        if (mapHeader->events->warps[warpEvent->warpId].mapNum == MAP_NUM(NONE))
            SetDynamicWarp(mapHeader->events->warps[warpEventId].warpId, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, warpEventId);
    }
}

static bool8 TryDoorWarp(struct MapPosition *position, u16 metatileBehavior, u8 direction)
{
    s8 warpEventId;

    if (direction == DIR_NORTH)
    {
        if (MetatileBehavior_IsWarpDoor(metatileBehavior) == TRUE)
        {
            warpEventId = GetWarpEventAtMapPosition(&gMapHeader, position);
            if (warpEventId != -1 && IsWarpMetatileBehavior(metatileBehavior) == TRUE)
            {
                StoreInitialPlayerAvatarState();
                SetupWarp(&gMapHeader, warpEventId, position);
                DoDoorWarp();
                return TRUE;
            }
        }
    }
    return FALSE;
}

static s8 GetWarpEventAtPosition(struct MapHeader *mapHeader, u16 x, u16 y, u8 elevation)
{
    s32 i;
    struct WarpEvent *warpEvent = mapHeader->events->warps;
    u8 warpCount = mapHeader->events->warpCount;

    for (i = 0; i < warpCount; i++, warpEvent++)
    {
        if ((u16)warpEvent->x == x && (u16)warpEvent->y == y)
        {
            if (warpEvent->elevation == elevation || warpEvent->elevation == 0)
                return i;
        }
    }
    return -1;
}

static const u8 *TryRunCoordEventScript(struct CoordEvent *coordEvent)
{
    if (coordEvent != NULL)
    {
        if (coordEvent->script == NULL)
        {
            DoCoordEventWeather(coordEvent->trigger);
            return NULL;
        }
        if (coordEvent->trigger == 0)
        {
            ScriptContext2_RunNewScript(coordEvent->script);
            return NULL;
        }
        if (VarGet(coordEvent->trigger) == (u8)coordEvent->index)
            return coordEvent->script;
    }
    return NULL;
}

static const u8 *GetCoordEventScriptAtPosition(struct MapHeader *mapHeader, u16 x, u16 y, u8 elevation)
{
    s32 i;
    struct CoordEvent *coordEvents = mapHeader->events->coordEvents;
    u8 coordEventCount = mapHeader->events->coordEventCount;

    for (i = 0; i < coordEventCount; i++)
    {
        if ((u16)coordEvents[i].x == x && (u16)coordEvents[i].y == y)
        {
            if (coordEvents[i].elevation == elevation || coordEvents[i].elevation == 0)
            {
                const u8 *script = TryRunCoordEventScript(&coordEvents[i]);
                if (script != NULL)
                    return script;
            }
        }
    }
    return NULL;
}

void HandleBoulderFallThroughHole(struct ObjectEvent * object)
{
    if (MapGridGetMetatileBehaviorAt(object->currentCoords.x, object->currentCoords.y) == MB_FALL_WARP)
    {
        PlaySE(SE_FALL);
        RemoveObjectEventByLocalIdAndMap(object->localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
        FlagClear(GetObjectEventFlagByLocalIdAndMap(object->localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup));
    }
}

void HandleBoulderActivateVictoryRoadSwitch(u16 x, u16 y)
{
    int i;
    const struct CoordEvent * events = gMapHeader.events->coordEvents;
    int n = gMapHeader.events->coordEventCount;

    if (MapGridGetMetatileBehaviorAt(x, y) == MB_STRENGTH_BUTTON)
    {
        for (i = 0; i < n; i++)
        {
            if (events[i].x + 7 == x && events[i].y + 7 == y)
            {
                QuestLog_CutRecording();
                ScriptContext1_SetupScript(events[i].script);
                LockPlayerFieldControls();
            }
        }
    }
}

const u8 *GetCoordEventScriptAtMapPosition(struct MapPosition *position)
{
    return GetCoordEventScriptAtPosition(&gMapHeader, position->x - 7, position->y - 7, position->height);
}

static const struct BgEvent *GetBackgroundEventAtPosition(struct MapHeader *mapHeader, u16 x, u16 y, u8 elevation)
{
    u8 i;
    struct BgEvent *bgEvents = mapHeader->events->bgEvents;
    u8 bgEventCount = mapHeader->events->bgEventCount;

    for (i = 0; i < bgEventCount; i++)
    {
        if ((u16)bgEvents[i].x == x && (u16)bgEvents[i].y == y)
        {
            if (bgEvents[i].elevation == elevation || bgEvents[i].elevation == 0)
                return &bgEvents[i];
        }
    }
    return NULL;
}

bool8 dive_warp(struct MapPosition *position, u16 metatileBehavior)
{
    if (gMapHeader.mapType == MAP_TYPE_UNDERWATER && !MetatileBehavior_IsUnableToEmerge(metatileBehavior))
    {
        if (SetDiveWarpEmerge(position->x - 7, position->y - 7))
        {
            StoreInitialPlayerAvatarState();
            DoDiveWarp();
            PlaySE(SE_M_DIVE);
            return TRUE;
        }
    }
    else if (MetatileBehavior_IsDiveable(metatileBehavior) == TRUE)
    {
        if (SetDiveWarpDive(position->x - 7, position->y - 7))
        {
            StoreInitialPlayerAvatarState();
            DoDiveWarp();
            PlaySE(SE_M_DIVE);
            return TRUE;
        }
    }
    return FALSE;
}

static u8 TrySetDiveWarp(void)
{
    s16 x, y;
    u8 metatileBehavior;

    PlayerGetDestCoords(&x, &y);
    metatileBehavior = MapGridGetMetatileBehaviorAt(x, y);
    if (gMapHeader.mapType == MAP_TYPE_UNDERWATER && !MetatileBehavior_IsUnableToEmerge(metatileBehavior))
    {
        if (SetDiveWarpEmerge(x - 7, y - 7) == TRUE)
            return 1;
    }
    else if (MetatileBehavior_IsDiveable(metatileBehavior) == TRUE)
    {
        if (SetDiveWarpDive(x - 7, y - 7) == TRUE)
            return 2;
    }
    return 0;
}

static const u8 *GetObjectEventScriptPointerPlayerFacing(void)
{
    u8 direction;
    struct MapPosition position;

    direction = GetPlayerMovementDirection();
    GetInFrontOfPlayerPosition(&position);
    return GetInteractedObjectEventScript(&position, MapGridGetMetatileBehaviorAt(position.x, position.y), direction);
}

int SetCableClubWarp(void)
{
    struct MapPosition position;

    GetPlayerMovementDirection();  // unnecessary
    GetPlayerPosition(&position);
    MapGridGetMetatileBehaviorAt(position.x, position.y);  // unnecessary
    SetupWarp(&gMapHeader, GetWarpEventAtMapPosition(&gMapHeader, &position), &position);
    return 0;
}
