#include "global.h"
#include "gflib.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_main.h"
#include "battle_message.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "battle_string_ids.h"
#include "berry.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "evolution_scene.h"
#include "graphics.h"
#include "help_system.h"
#include "item.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "m4a.h"
#include "party_menu.h"
#include "pokeball.h"
#include "pokedex.h"
#include "quest_log.h"
#include "random.h"
#include "roamer.h"
#include "safari_zone.h"
#include "scanline_effect.h"
#include "task.h"
#include "trig.h"
#include "test_runner.h"
#include "vs_seeker.h"
#include "util.h"
#include "new_menu_helpers.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_effects.h"
#include "constants/battle_setup.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/songs.h"
#include "constants/trainer_classes.h"
#include "constants/opponents.h" //believe trainerNum, should be same as values for opponents in opponents.h since trainer.h is in same order

//static void SpriteCB_UnusedDebugSprite(struct Sprite *sprite);
//static void SpriteCB_UnusedDebugSprite_Step(struct Sprite *sprite);
static void HandleAction_UseMove(void);
static void HandleAction_Switch(void);
static void HandleAction_UseItem(void);
static void HandleAction_Run(void);
static void HandleAction_WatchesCarefully(void);
static void HandleAction_SafariZoneBallThrow(void);
static void HandleAction_ThrowBait(void);
static void HandleAction_ThrowRock(void);
static void HandleAction_SafariZoneRun(void);
static void HandleAction_OldManBallThrow(void);
static void HandleAction_TryFinish(void);
static void HandleAction_NothingIsFainted(void);
static void HandleAction_WaitTurnEnd(void);
static void HandleAction_ActionFinished(void);
static void HandleEndTurn_ContinueBattle(void);
static void HandleEndTurn_BattleWon(void);
static void HandleEndTurn_BattleLost(void);
static void HandleEndTurn_RanFromBattle(void);
static void HandleEndTurn_MonFled(void);
static void HandleEndTurn_FinishBattle(void);
static void CB2_InitBattleInternal(void);
static void CB2_PreInitMultiBattle(void);
static void CB2_HandleStartMultiBattle(void);
static u8 CreateNPCTrainerParty(struct Pokemon *party, u16 trainerNum);
static void CB2_HandleStartBattle(void);
static void TryCorrectShedinjaLanguage(struct Pokemon *mon);
static void BattleMainCB1(void);
static void CB2_QuitPokedudeBattle(void);
static void CB2_EndLinkBattle(void);
static void EndLinkBattleInSteps(void);
static void SpriteCB_MoveWildMonToRight(struct Sprite *sprite);
static void SpriteCB_WildMonShowHealthbox(struct Sprite *sprite);
//static void SpriteCB_Unused_8011E28_Step(struct Sprite *sprite);
static void SpriteCB_AnimFaintOpponent(struct Sprite *sprite);
static void SpriteCb_BlinkVisible(struct Sprite *sprite);
static void oac_poke_ally_(struct Sprite *sprite);
static void SpriteCallbackDummy3(struct Sprite *sprite);
static void SpriteCB_BounceEffect(struct Sprite *sprite);
static void SpriteCB_PlayerThrowUpdate(struct Sprite *sprite);
static void BattleStartClearSetData(void);
static void BattleIntroGetMonsData(void);
static void TurnValuesCleanUp(bool8 var0);
static void SpecialStatusesClear(void);
static void BattleIntroPrepareBackgroundSlide(void);
static void BattleIntroDrawTrainersOrMonsSprites(void);
static void BattleIntroDrawPartySummaryScreens(void);
static void BattleIntroPrintTrainerWantsToBattle(void);
static void BattleIntroPrintWildMonAttacked(void);
static void BattleIntroPrintOpponentSendsOut(void);
static void BattleIntroPrintPlayerSendsOut(void);
static void BattleIntroRecordMonsToDex(void);
static void BattleIntroOpponentSendsOutMonAnimation(void);
static void BattleIntroPlayerSendsOutMonAnimation(void);
static void TryDoEventsBeforeFirstTurn(void);
static void HandleTurnActionSelectionState(void);
static void RunTurnActionsFunctions(void);
static void SetActionsAndBattlersTurnOrder(void);
static void CheckFocusPunch_ClearVarsBeforeTurnStarts(void);
static void HandleEndTurn_FinishBattle(void);
static void FreeResetData_ReturnToOvOrDoEvolutions(void);
static void ReturnFromBattleToOverworld(void);
static void TryEvolvePokemon(void);
static void WaitForEvoSceneToFinish(void);


EWRAM_DATA u16 gBattle_BG0_X = 0;
EWRAM_DATA u16 gBattle_BG0_Y = 0;
EWRAM_DATA u16 gBattle_BG1_X = 0;
EWRAM_DATA u16 gBattle_BG1_Y = 0;
EWRAM_DATA u16 gBattle_BG2_X = 0;
EWRAM_DATA u16 gBattle_BG2_Y = 0;
EWRAM_DATA u16 gBattle_BG3_X = 0;
EWRAM_DATA u16 gBattle_BG3_Y = 0;
EWRAM_DATA u16 gBattle_WIN0H = 0;
EWRAM_DATA u16 gBattle_WIN0V = 0;
EWRAM_DATA u16 gBattle_WIN1H = 0;
EWRAM_DATA u16 gBattle_WIN1V = 0; //gonna try 380, estimated by counting hover over values for 3 buffs and gunown below whih was about 73
EWRAM_DATA u8 gDisplayedStringBattle[380] = {0}; //need increase from 300 to fix brocks
EWRAM_DATA u8 gBattleTextBuff1[TEXT_BUFF_ARRAY_COUNT] = {0};
EWRAM_DATA u8 gBattleTextBuff2[TEXT_BUFF_ARRAY_COUNT] = {0};
EWRAM_DATA u8 gBattleTextBuff3[TEXT_BUFF_ARRAY_COUNT] = {0};
//static EWRAM_DATA u32 gUnknown_2022AE8[25] = {0}; //zsonic  //GriffinR came through again,  thought this was unused but removing is what broke brocks battle.
EWRAM_DATA u32 gBattleTypeFlags = 0;
EWRAM_DATA u8 gBattleTerrain = 0;
EWRAM_DATA u32 gUnknown_2022B54 = 0;
EWRAM_DATA struct MultiBattlePokemonTx gMultiPartnerParty[3] = {0};
EWRAM_DATA u8 *gBattleAnimMons_BgTilesBuffer = NULL;
EWRAM_DATA u8 *gBattleAnimMons_BgTilemapBuffer = NULL;
static EWRAM_DATA u16 *sUnknownDebugSpriteDataBuffer = NULL;
EWRAM_DATA u8 gBattleBufferA[MAX_BATTLERS_COUNT][0x200] = {0};
EWRAM_DATA u8 gBattleBufferB[MAX_BATTLERS_COUNT][0x200] = {0};
EWRAM_DATA u8 gActiveBattler = 0;
EWRAM_DATA u8 gBattlerAbility = 0;  //didn't want to port but its required since its the main thing used with ability popups
EWRAM_DATA u32 gBattleControllerExecFlags = 0;
EWRAM_DATA u8 gBattlersCount = 0;
EWRAM_DATA u16 gBattlerPartyIndexes[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerPositions[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gActionsByTurnOrder[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerByTurnOrder[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gCurrentTurnActionNumber = 0;
EWRAM_DATA u8 gCurrentActionFuncId = 0;
EWRAM_DATA struct BattlePokemon gBattleMons[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerSpriteIds[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gCurrMovePos = 0;
EWRAM_DATA u8 gChosenMovePos = 0;
EWRAM_DATA u16 gCurrentMove = 0;
EWRAM_DATA u16 gChosenMove = 0;
EWRAM_DATA u16 gCalledMove = 0; //gbattlemovedamage is total damage, but whether it goes into damage formula is based on if script has damagecalc bs command in it, that is what weights things against defense etc.
EWRAM_DATA u16 gBattleMovePower = 0;
EWRAM_DATA s32 gBattleMoveDamage = 0;   //make notse on this, does it go through damage formula, is it affected by defense/split? offense stats? or does it bypass everything to do true damage?
EWRAM_DATA s32 gHpDealt = 0;
EWRAM_DATA s32 gTakenDmg[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastUsedItem = 0;
EWRAM_DATA u16 gLastUsedAbility = 0;
EWRAM_DATA u8 gBattlerAttacker = 0; 
EWRAM_DATA u8 gBattlerTarget = 0; 
EWRAM_DATA u8 gBattlerFainted = 0;
EWRAM_DATA u8 gEffectBattler = 0;
EWRAM_DATA u8 gPotentialItemEffectBattler = 0;
EWRAM_DATA u8 gAbsentBattlerFlags = 0;
EWRAM_DATA u8 gCritMultiplier = 0;
EWRAM_DATA u8 gMultiHitCounter = 0;
EWRAM_DATA u8 gMultiTask = 0;
EWRAM_DATA const u8 *gBattlescriptCurrInstr = NULL;
EWRAM_DATA u32 gUnusedBattleMainVar = 0;
EWRAM_DATA u8 gChosenActionByBattler[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA const u8 *gSelectionBattleScripts[MAX_BATTLERS_COUNT] = {NULL};
EWRAM_DATA u16 gLastPrintedMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastLandedMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastHitByType[MAX_BATTLERS_COUNT] = {0};    //may need to add last hit by move for fly cancel?
EWRAM_DATA u16 gLastResultingMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLockedMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastUsedMove = 0; //still unsure if I need to add this or can just use gLastResultingMoves which seems to be equivalent
EWRAM_DATA u8 gLastHitBy[MAX_BATTLERS_COUNT] = {0};//ran make with and without above line came to same conclusion so either works
EWRAM_DATA u16 gChosenMoveByBattler[MAX_BATTLERS_COUNT] = {0};//rn I'll use existing value to save on ram
EWRAM_DATA u8 gMoveResultFlags = 0;
EWRAM_DATA u32 gHitMarker = 0;
static EWRAM_DATA u8 gUnknown_2023DD4[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gTakenDmgByBattler[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gUnknown_2023DDC = 0;
EWRAM_DATA u32 gSideStatuses[2] = {0};
EWRAM_DATA struct SideTimer gSideTimers[2] = {0};
EWRAM_DATA u32 gStatuses3[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u32 gStatuses4[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct DisableStruct gDisableStructs[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gPauseCounterBattle = 0;
EWRAM_DATA u16 gPaydayMoney = 0;
EWRAM_DATA u16 gRandomTurnNumber = 0;
EWRAM_DATA u8 gBattleCommunication[BATTLE_COMMUNICATION_ENTRIES_COUNT] = {0};
EWRAM_DATA u8 gBattleOutcome = 0;
EWRAM_DATA struct ProtectStruct gProtectStructs[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct SpecialStatus gSpecialStatuses[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gBattleWeather = 0;
EWRAM_DATA struct WishFutureKnock gWishFutureKnock = {0};
EWRAM_DATA u16 gIntroSlideFlags = 0;
EWRAM_DATA u8 gSentPokesToOpponent[2] = {0};
EWRAM_DATA u16 gDynamicBasePower = 0;
EWRAM_DATA u16 gExpShareExp = 0;
EWRAM_DATA struct BattleEnigmaBerry gEnigmaBerries[MAX_BATTLERS_COUNT] = {0}; //onlyused for ereader stuff can remove - is very pervasive
EWRAM_DATA struct BattleScripting gBattleScripting = {0};
EWRAM_DATA struct BattleStruct *gBattleStruct = NULL;
EWRAM_DATA u8 *gLinkBattleSendBuffer = NULL;
EWRAM_DATA u8 *gLinkBattleRecvBuffer = NULL;
EWRAM_DATA struct BattleResources *gBattleResources = NULL;  //edited includes flags I added i.e flashfire etc. appears only clear on battle start, switch or faint
EWRAM_DATA u8 gActionSelectionCursor[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gMoveSelectionCursor[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerStatusSummaryTaskId[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerInMenuId = 0;
EWRAM_DATA bool8 gDoingBattleAnim = FALSE;
//EWRAM_DATA u32 gTransformedPersonalities[MAX_BATTLERS_COUNT] = {0}; //vsonic can remove this, not really needed
EWRAM_DATA struct BattleSpriteData *gBattleSpritesDataPtr = NULL;
EWRAM_DATA struct MonSpritesGfx *gMonSpritesGfxPtr = NULL;
EWRAM_DATA u16 gMoveToLearn = 0;
EWRAM_DATA u8 gBattleMonForms[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u32 gFieldStatuses = 0;
EWRAM_DATA struct FieldTimer gFieldTimers = { 0 };
//EWRAM_DATA struct TotemBoost gTotemBoosts[MAX_BATTLERS_COUNT] = { 0 };  //not gonna use for my stuff so can comment out
EWRAM_DATA bool8 gHasFetchedBall = FALSE;
EWRAM_DATA u8 gLastUsedBall = 0;    //need to implement add in these 2 somewhere
EWRAM_DATA u16 gLastThrownBall = 0;
EWRAM_DATA bool8 gSwapDamageCategory = FALSE; // Photon Geyser, Shell Side Arm, Light That Burns the Sky

void (*gPreBattleCallback1)(void);
void (*gBattleMainFunc)(void);
struct BattleResults gBattleResults;
u8 gLeveledUpInBattle;
void (*gBattlerControllerFuncs[MAX_BATTLERS_COUNT])(void);
u8 gHealthboxSpriteIds[MAX_BATTLERS_COUNT];
u8 gMultiUsePlayerCursor;
u8 gNumberOfMovesToChoose;
u8 gBattleControllerData[MAX_BATTLERS_COUNT];

static const struct ScanlineEffectParams sIntroScanlineParams16Bit =
{
    &REG_BG3HOFS, SCANLINE_EFFECT_DMACNT_16BIT, 1
};

/*const struct SpriteTemplate gUnknownDebugSprite =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_UnusedDebugSprite,
};*/

static const u8 sText_ShedinjaJpnName[] = _("ヌケニン"); // Nukenin

const struct OamData gOamData_BattlerOpponent =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_NORMAL,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0,
};

const struct OamData gOamData_BattlerPlayer =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_NORMAL,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 2,
    .affineParam = 0,
};

// not used
static const union AnimCmd gUnknown_824F020[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_JUMP(0),
};

// not used
static const union AnimCmd *const gUnknown_824F028[] =
{
    gUnknown_824F020,
};

// not used
static const union AffineAnimCmd gUnknown_824F02C[] =
{
    AFFINEANIMCMD_FRAME(-0x10, 0x0, 0, 4),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 0x3C),
    AFFINEANIMCMD_JUMP(1),
};

// not used
static const union AffineAnimCmd *const gUnknown_824F044[] =
{
    gUnknown_824F02C,
};

static const s8 sPlayerThrowXTranslation[] = { -32, -16, -16, -32, -32, 0, 0, 0 };

#define X UQ_4_12
#define ______ X(1.0) // Regular effectiveness.
//rows are attacking type
//columns are defending type 
//still confused about static vs const but pretty sure static can be called outside of file, just not directly
//no idea how never realized but type is organized from physical to special
const u16 gTypeEffectivenessTable[NUMBER_OF_MON_TYPES][NUMBER_OF_MON_TYPES] =
{
//                       normal    fight     flying    poison    ground     rock      bug       ghost    steel     mystery    fire      water      grass    electric   psychic   ice      dragon     dark     fairy      sound
    //Attack Type
    [TYPE_NORMAL] =    {______,    ______,   ______,   ______,   ______,   X(0.5),   ______,   X(0.0),   X(0.5),   ______,    ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______}, // normal

    [TYPE_FIGHTING] =   {X(1.55),  ______,   X(0.5),   X(0.5),   ______,   X(1.55),   X(0.5),   X(0.0),   X(1.55),  ______,    ______,   ______,   ______,   ______,   X(0.5),   X(1.55),   ______,  X(1.55),   X(0.5),   ______}, // fight

    [TYPE_FLYING] =     {______,   X(1.55),   ______,   ______,   X(0.5),   X(0.5),   X(1.55),   ______,   X(0.5),   ______,  ______,   ______,   X(1.55),   X(0.5),   X(0.5),   X(0.5),   ______,   ______,   ______,   ______}, // flying

    [TYPE_POISON] =     {______,   X(1.55),   ______,   X(0.0),   X(0.5),   X(0.0),   ______,   X(0.5),   X(0.0),   ______,    ______,   ______,   X(1.55),   ______,   ______,   X(0.5),   ______,  X(0.5),   X(1.55),   ______}, // poison

    [TYPE_GROUND] =     {______,   ______,   ______,   X(1.55),   ______,   X(1.55),  X(0.5),   ______,   ______,   ______,   X(1.55),   ______,   X(0.5),   X(1.55),   ______,   X(0.5),   ______,   ______,   ______,   ______}, // ground

    [TYPE_ROCK] =       {______,   X(0.5),   X(1.55),   ______,   X(0.5),   X(0.5),   X(1.55),   ______,   X(0.5),   ______,  X(1.55),   ______,   ______,   ______,   ______,   X(1.55),   ______,   ______,   ______,   ______}, // rock

    [TYPE_BUG] =        {______,   X(0.5),   X(0.5),   X(0.5),   ______,   ______,    ______,   ______,   ______,   ______,   X(0.5),    ______,   X(1.55),   ______,  X(1.55),   X(0.5),  ______,   X(1.55),  ______,  ______}, // bug

    [TYPE_GHOST] =      {X(0.0),   ______,   ______,   ______,   ______,   ______,    ______,   X(1.55),   ______,   ______,  ______,    ______,   ______,   ______,   ______,   ______,   ______,   X(0.5),   X(0.5),    ______}, // ghost

    [TYPE_STEEL] =      {______,   ______,   ______,   ______,   ______,   X(1.55),   ______,   ______,   X(0.5),   ______,   X(0.5),    X(0.5),   ______,   X(0.5),   ______,   X(1.55),   ______,   ______,   X(1.55),   ______}, // steel

    [TYPE_MYSTERY] =    {______,   ______,   ______,   ______,   ______,   ______,   ______,     ______,  ______,   ______,   ______,   ______,   ______,    ______,   ______,   ______,   ______,   ______,   ______,   ______}, // mystery

    [TYPE_FIRE] =       {______,   ______,   ______,   ______,   X(0.5),   X(0.5),   X(1.55),    X(0.5),  X(1.55),   ______,  X(0.5),   X(0.5),   X(1.55),   ______,   ______,   X(1.55),  X(0.5),   ______,   ______,   ______}, // fire

    [TYPE_WATER] =      {______,   ______,   ______,   ______,   X(1.55),   X(1.55),   ______,   ______,   ______,   ______,  X(1.55),   X(0.5),   X(0.5),   ______,   ______,   X(0.5),   X(0.5),   ______,   ______,   ______}, // water

    [TYPE_GRASS] =      {______,   ______,   X(0.5),   X(0.5),   X(1.55),   X(1.55),   X(0.5),   ______,   X(0.5),   ______,  X(0.5),   X(1.55),   X(0.5),   ______,   ______,   ______,   X(0.5),   ______,   ______,   ______}, // grass

    [TYPE_ELECTRIC] =   {______,   ______,   X(1.55),  ______,    X(0.0),   X(0.5),   X(0.5),   ______,   X(1.55),   ______,  ______,   X(1.55),   ______,   X(0.5),   ______,   X(0.5),   X(0.5),   ______,   ______,   ______}, // electric

    [TYPE_PSYCHIC] =    {______,   X(1.55),   ______,   X(1.55),  ______,   ______,   ______,   ______,   X(0.5),   ______,   ______,   ______,   ______,   ______,   X(0.5),   ______,   ______,   X(0.0),   ______,   ______}, // psychic

    [TYPE_ICE] =        {______,   ______,   X(1.55),   ______,   X(1.55),   ______,   X(1.55),   X(0.5),  X(0.5),  ______,   X(0.5),  ______,   X(1.55),   ______,   ______,   X(0.5),   X(1.55),   ______,   ______,   ______}, // ice

    [TYPE_DRAGON] =     {______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   X(0.5),   ______,   ______,   ______,   ______,   ______,   ______,   X(0.5),   X(1.55),   ______,    X(0.0),   ______}, // dragon

    [TYPE_DARK] =       {______,   X(0.5),   ______,   ______,   ______,   ______,   X(0.5),   X(0.5),   ______,   ______,   ______,   ______,   ______,   ______,   X(1.55),   ______,   ______,   X(1.55),   X(1.55),   ______}, // dark

    [TYPE_FAIRY] =      {X(1.55),  ______,   ______,   X(0.5),   ______,   ______,   X(0.5),   ______,   X(0.5),   ______,   X(0.5),   ______,   X(0.0),   ______,   X(0.5),   ______,   X(1.55),   X(1.55),   ______,   ______}, // fairy

       /*sound*/        {______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,   ______,    ______,   ______,    ______}, // sound
};//                     normal    fight      flying    poison    ground     rock      bug       ghost    steel     mystery    fire      water    grass    electric   psychic    ice      dragon     dark     fairy      sound

#undef X



// format: attacking type, defending type, damage multiplier
// the multiplier is a (decimal) fixed-point number:
// 20 is ×2.0 TYPE_MUL_SUPER_EFFECTIVE
// 10 is ×1.0 TYPE_MUL_NORMAL
// 05 is ×0.5 TYPE_MUL_NOT_EFFECTIVE
// 00 is ×0.0 TYPE_MUL_NO_EFFECT

//each line adds 3 because there are 3 arguments in each line, atk type, def type, & effectiveness  /so SUBTRACT 3 for any lines kept but commented out
//DON'T FORGET every time I change below, need to update in the .h / also need to update table above, so ai, and other pre-damage type calcs are accurate
#define TYPE_CHART

//I kind of like the idea of giving poison dark resistance,
//they had in shadows, psychics can read their thoughts and find them, making them a counter
//and they have high sp def, but resistances to some commonly strong physical types? -mostly just it resisting fighting

//would break funny number but considering make fairy resist normal
//as I've nerfed fairies offensiveness a good deal?
//makes some sense, and also matches them as ghost counter part,
//fae and spirits were seen as same thing, hmm nah, too strong
//no longer used for type reading but keeping as its more readable, a good visual
const u8 gTypeEffectiveness[] = // 336 is number of entries x 3 i.e number of efffectiveness since only super not effective and no effect are included. 
{ // counted from ompen bracket to end of table. so subtract line first entry is on from line closing bracket is on  then multipy by 3.
    TYPE_NORMAL, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_NORMAL, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_STEEL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_WATER, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE, //NEW effectiveness for snivy, also gives closer tie between rock/ground
    TYPE_FIRE, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE, //ghost adjustment same logic as ice
    TYPE_FIRE, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_FIRE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_GROUND, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_WATER, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_GRASS, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_WATER, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_STEEL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_FLYING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_ELECTRIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,   //new change mostly for cloyster but makes sense.
    TYPE_ELECTRIC, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,    //tentative change to make ice better defensively //there are several water ice & flying ice, makes science sense as well
    TYPE_ELECTRIC, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE, //made bug resist electric always made sense to me, they can chew threw electric cables    
    TYPE_ELECTRIC, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_GROUND, TYPE_MUL_NO_EFFECT,  //plus swarms of bugs are able to generate electricity,as well as some capable of generating bio-electricity
    TYPE_GRASS, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GRASS, TYPE_WATER, TYPE_MUL_SUPER_EFFECTIVE,//removed grass resistance to electric,  lighting splits trees and can spark fire, didn't make sense, leaving neutral
    TYPE_GRASS, TYPE_GROUND, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GRASS, TYPE_GRASS, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,    
    TYPE_GRASS, TYPE_FLYING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ICE, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ICE, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE,   //ghost adjustment, the dead aren't bothered by cold
    TYPE_ICE, TYPE_GROUND, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_FLYING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_DRAGON, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ICE, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_NORMAL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_FLYING, TYPE_MUL_NOT_EFFECTIVE, //when grounded fighting should do normal damage to flying
    TYPE_FIGHTING, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,    //dont understand this other than some super sentai stuff but I'm keeping it
    TYPE_FIGHTING, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE,  //technically not true physical attacks are strong aginst fae because of their fragile bodies but keeping
    TYPE_FIGHTING, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_STEEL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_POISON, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_POISON, TYPE_FIGHTING, TYPE_MUL_SUPER_EFFECTIVE,   //poison resists fighting, usually type is super against what it resists, also poison spreads faster in more active, and best way to take out physically strong opponents
    TYPE_POISON, TYPE_FAIRY, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_POISON, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_POISON, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,  //cold slows spread of poison
    TYPE_POISON, TYPE_DARK, TYPE_MUL_NOT_EFFECTIVE, //doing this way works even better than I thought as makes triangle relation w bug, psn resist bug, bug beats dark, dark resist psn
    TYPE_POISON, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_POISON, TYPE_POISON, TYPE_MUL_NO_EFFECT,       //furthering of late gen poison can't be poisoned logic, also makes better as a pivot/defensive typing
    TYPE_POISON, TYPE_STEEL, TYPE_MUL_NO_EFFECT,
    TYPE_POISON, TYPE_ROCK, TYPE_MUL_NO_EFFECT,     //same as steel, not alive so not affecting by poison
    TYPE_GROUND, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,  //logic water in the ground gets frozen earth cant shift/move
    TYPE_GROUND, TYPE_FIRE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GROUND, TYPE_ELECTRIC, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GROUND, TYPE_GRASS, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GROUND, TYPE_POISON, TYPE_MUL_SUPER_EFFECTIVE,// delete ground to flying so its set to normal effective
    TYPE_GROUND, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE, //then create condition where its set to no effect if not grounded
    TYPE_GROUND, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE, //made ground steel neutral, as its better rock, and materiel for steel comes from the earth, also earthquakes resistant buildings are a thing
    TYPE_FLYING, TYPE_ELECTRIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FLYING, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,  //makes sense flying resists grass, birds make their home in trees,also hurricanes/tornadoes uproot & destroy trees
    TYPE_FLYING, TYPE_FIGHTING, TYPE_MUL_SUPER_EFFECTIVE,   // I have the HIGH GROUND Anakin!!!
    TYPE_FLYING, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FLYING, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FLYING, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE,   //wind doesn't really affect ground itself, after torandoes/hurricanes ground itself is undamage just everying on top (and mon can just go underground to avoid attacks)
    TYPE_FLYING, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FLYING, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,  //screw it!! it makes sense so I'm doing it, psychic abilities already catch things in the air and throw them around, even control wind
    TYPE_FLYING, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,      //Removed psychic super to flying, too strong, psychic strong offensively can already beat flying at neutral
    TYPE_PSYCHIC, TYPE_FIGHTING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_PSYCHIC, TYPE_POISON, TYPE_MUL_SUPER_EFFECTIVE,    //think logic is psychic powers would keep you from being poisoned/subtle attacks you could read their mind, so its "very effective"
    TYPE_PSYCHIC, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,     //psychic power can stop a target cold, can keep them from flying, or confuse them which would make it impossible to fly, so makes sense,
    TYPE_PSYCHIC, TYPE_DARK, TYPE_MUL_NO_EFFECT,        //mostly done to counter fairy resistance
    TYPE_PSYCHIC, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,   //effect prob too strong, flying is weak defensively and psychic is strong offenseively
    //TYPE_PSYCHIC, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE, //decided change fairy resist to psychic, to a psychic resist to fairy, as psychic mostly fell off, and was replaced by fairy, - change logic to psychic doesn't believe in fairy/mystics
    TYPE_BUG, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,    //plus fairy nerfed, will replace with resistancee instad of super effectiveness
    TYPE_BUG, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_FLYING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE, 
    TYPE_BUG, TYPE_PSYCHIC, TYPE_MUL_SUPER_EFFECTIVE,//removed ghost resistance to bug by accident in my chart, but was so good will add to my chart
    TYPE_BUG, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE, //removed still resist to bug, apparently many insect types are known to destroy/consume light metals, would be great for the type
    TYPE_ROCK, TYPE_FIRE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ROCK, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ROCK, TYPE_FLYING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ROCK, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,   //doesn't strictly make sense, but better for type defense
    TYPE_GHOST, TYPE_NORMAL, TYPE_MUL_NO_EFFECT,
    TYPE_GHOST, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE, //research ghost fairy thought to be same thing, difference ghosts are dead fae are considered alive, but at they were at one point both considered spirits
    TYPE_GHOST, TYPE_DARK, TYPE_MUL_NOT_EFFECTIVE,          //removed ghost psychic effect as typically mediums and ghosts are mostly equal enemies,  psychis exorsise ghosts but ghosts also kill psychis
    TYPE_GHOST, TYPE_GHOST, TYPE_MUL_SUPER_EFFECTIVE,           
    TYPE_DRAGON, TYPE_DRAGON, TYPE_MUL_SUPER_EFFECTIVE, 
    TYPE_DRAGON, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,  //Mostly done to keep num types, but also works for giving an extra reason to use ice type mon against dragons over just using an ice move
    TYPE_DRAGON, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,    //-ok so I over nerfed fairy to buff other things, am unwillign to remove them so instead will put dragon immunity back, I'm already abiding a resist that doesn't make sense but for balance so whatever
    TYPE_DRAGON, TYPE_FAIRY, TYPE_MUL_NO_EFFECT,    //i can't explain fairy immunity to dragon, other than a pure balance decision, there's no lore that I can find to any relation between them.
    TYPE_DARK, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,   //I thought it was a king arthur thing, but he never actually fought a dragon, though he did have protection of fae magic
    TYPE_DARK, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,    //type change from wolveyvgc to buff bugs, its weak to bugs, so resists it, and dark is evil & bugs are associated with heroes through kamen rider so makes sense
    TYPE_DARK, TYPE_PSYCHIC, TYPE_MUL_SUPER_EFFECTIVE,  //-keeping psychic weakness to dark post ghost change as dark is living and able to do physical attacks while psychic is usually phsycially weak
    TYPE_DARK, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE,  //changed there's nothing significant bout dark, its more or less same as ghost but alive, and ghosts thrive in darkness
    //TYPE_DARK, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,   //change essentially makes ghost inverse of normal type effect wise, where most things are neutral and it has 1 weakness
    //TYPE_DARK, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE, //-similar to ghost logic, poison hides in darkness, is linked w dark intentions, actually think will reverse this make dark resist poison, will go more to make counter to fairy who is weak to poison
    TYPE_DARK, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE,//removing gen 3 steel resist to dark, with dark changes realized ruins it offensively
    TYPE_DARK, TYPE_FAIRY, TYPE_MUL_SUPER_EFFECTIVE, //plus dosen't really make sense when you have cursed blades, and haunted blades exist, i.e dark and ghost affecting steel
    TYPE_STEEL, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,//NEW type relation for dark types, showed positively for offense capability and makes sense sneaky backstabbers bad guys take each other out often.
    TYPE_STEEL, TYPE_WATER, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_STEEL, TYPE_ELECTRIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_STEEL, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_STEEL, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_FAIRY, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_NORMAL, TYPE_MUL_SUPER_EFFECTIVE, //fairy can control beasts, mostly just for balance to counter fairy nerfs replace fighting advantage
    TYPE_FAIRY, TYPE_DRAGON, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FAIRY, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FAIRY, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE, //bug buff because bug beats grass and is similar to nature
    TYPE_FAIRY, TYPE_GRASS, TYPE_MUL_NO_EFFECT,     //grass buff, and based on idea fairy are nature spirits i.e can't hurt nature as they can't exist without it
    TYPE_FORESIGHT, TYPE_FORESIGHT, TYPE_MUL_NO_EFFECT, //can remove this when confident removed all type_foresight checks, would give room for 1 type change well I could leave it idk, i'll leave it...becuz I want the dumb 420 number...
    TYPE_NORMAL, TYPE_GHOST, TYPE_MUL_NO_EFFECT, //will eventually remove type foresight so num types will change, so would want to add something
    TYPE_FIGHTING, TYPE_GHOST, TYPE_MUL_NO_EFFECT,  //I'm thinkikng of making a fairy/fairy immunity, its all same class of magic, and would lean more into making it a counter part to dark
    TYPE_SOUND, TYPE_SOUND, TYPE_MUL_NO_EFFECT,     //which is now super to iself,   and make dark//fairy a true chaos hybrid best of both worlds type deal, need check type calculator
    TYPE_ENDTABLE, TYPE_ENDTABLE, TYPE_MUL_NO_EFFECT    //tabling fairy resist for now, would have to play test but loooks like any change to  fairy either immune to or resisting self just makes it worse overall, though I do prefer making it resist itself for dark/fairy
};

//questioned bug and ice resistance to electricity, but after research it made even more sense, than I initially thought.
//initial basis was grass resists, bug is like nature so is similar, also bugs chew threw electrical cables,
//and ice slowls electron flow, which can prevent electrical flow.
//but later found, not only  does ice stop electrical flow, bugs and ice are capable of producing lightning/electricity mostly via friction
//and as electric resists electric, that is another reason ice/bug resistance to electricity makes sense.

//logic for dark beating dark is similar to dragon, bad guys/evil are most likely to backstab/take each other out
//same as dragons fight and defeat other dragons

//reearch notes and rational for removing ground weakness for steel
/*
However, buildings consisting primarily of steel or other metals are much better
at resisting earthquakes. Steel is much lighter than concrete,
but it still brings a great deal of durability to construction projects.
More flexible than concrete and other building materials,
steel is more likely to bend instead of break when experiencing seismic force.

(Steel and other metals are a major factor in earthquake resistance 
not a detriment. A sinkhole would most likely still collapse a building
but most earth moves are seismic effects/brute force and don't involve sinkholes etc.
So is more a case of only the extreme being effective.

With that in mind an argument could be made for the steel resisting groud, 
instead keeeping it neutral is a good compromsise and balance in my mind.
)
*/

//nature of resists/effectiveness try to keep to absolute
//ex. adding more fire will always just make the fire stronger as its adding more of itself
//a bug fighting another bug the advantage goes to whichever is stronger
//now for rock against rock, some of that same bug logic applies, depends on which rock is stronger
//and eventually if a big enough or enough rocks are used the target stone will crack
//but that said, rocks still fair much better against rocks, than any most other types
//so there's a valid argument for a resist there.

    //consider makign bugs immune to confusion status, like wolfeyvgc said, he didn't explain but I gather logic is most bugs work by hivemind,
//on top of having some type of extra sensory options with its feelers etc. will have to add dark type exception to prankster back i guess
//think this is done?

#define TYPE_NAMES
const u8 gTypeNames[][TYPE_NAME_LENGTH + 1] =
{
    _("NORMAL"),
    _("FIGHT"),
    _("FLYING"),
    _("POISON"),
    _("GROUND"),
    _("ROCK"),
    _("BUG"),
    _("GHOST"),
    _("STEEL"),
    _("???"),
    _("FIRE"),
    _("WATER"),
    _("GRASS"),
    _("ELECTR"),
    _("PSYCHC"),
    _("ICE"),
    _("DRAGON"),
    _("DARK"),
    _("FAIRY"), //fairy addition
    _("SOUND"),
}; //uses same type order as list_menu.c so this fairy is 12, but my actuall fairy type
//was at 17. fixed now they are both 12.
//had to retruncate type names to fit move name

//also needed change value in & pokemon.h

// This is a factor in how much money you get for beating a trainer.
const struct TrainerMoney gTrainerMoneyTable[] =
{
    { CLASS_LEADER_2, 25 },
    { CLASS_ELITE_FOUR_2, 25 },
    { CLASS_PKMN_PROF, 25 },
    { CLASS_RIVAL, 4 },
    { CLASS_RIVAL_2, 9 },
    { CLASS_CHAMPION_2, 25 },
    { CLASS_YOUNGSTER_2, 4 },
    { CLASS_BUG_CATCHER_2, 3 },
    { CLASS_HIKER_2, 9 },
    { CLASS_BIRD_KEEPER_2, 6 },
    { CLASS_PICNICKER_2, 5 },
    { CLASS_SUPER_NERD, 6 },
    { CLASS_FISHERMAN_2, 9 },
    { CLASS_TEAM_ROCKET, 8 },
    { CLASS_LASS_2, 4 },
    { CLASS_BEAUTY_2, 18 },
    { CLASS_BLACK_BELT_2, 6 },
    { CLASS_CUE_BALL, 6 },
    { CLASS_CHANNELER, 8 },
    { CLASS_ROCKER, 6 },
    { CLASS_GENTLEMAN_2, 18 },
    { CLASS_BURGLAR, 22 },
    { CLASS_SWIMMER_MALE_2, 1 },
    { CLASS_ENGINEER, 12 },
    { CLASS_JUGGLER, 10 },
    { CLASS_SAILOR_2, 8 },
    { CLASS_COOLTRAINER_2, 9 },
    { CLASS_POKEMANIAC_2, 12 },
    { CLASS_TAMER, 10 },
    { CLASS_CAMPER_2, 5 },
    { CLASS_PSYCHIC_2, 5 },
    { CLASS_BIKER, 5 },
    { CLASS_GAMBLER, 18 },
    { CLASS_SCIENTIST, 12 },
    { CLASS_CRUSH_GIRL, 6 },
    { CLASS_TUBER_3, 1 },
    { CLASS_PKMN_BREEDER_2, 7 },
    { CLASS_PKMN_RANGER_2, 9 },
    { CLASS_AROMA_LADY_2, 7 },
    { CLASS_RUIN_MANIAC_2, 12 },
    { CLASS_LADY_2, 50 },
    { CLASS_PAINTER, 4 },
    { CLASS_TWINS_2, 3 },
    { CLASS_YOUNG_COUPLE_2, 7 },
    { CLASS_SIS_AND_BRO_2, 1 },
    { CLASS_COOL_COUPLE, 6 },
    { CLASS_CRUSH_KIN, 6 },
    { CLASS_SWIMMER_FEMALE_2, 1 },
    { CLASS_PLAYER, 1 },
    { CLASS_LEADER, 25 },
    { CLASS_ELITE_FOUR, 25 },
    { CLASS_LASS, 4 },
    { CLASS_YOUNGSTER, 4 },
    { CLASS_PKMN_TRAINER_3, 15 },
    { CLASS_HIKER, 10 },
    { CLASS_BEAUTY, 20 },
    { CLASS_FISHERMAN, 10 },
    { CLASS_LADY, 50 },
    { CLASS_TRIATHLETE, 10 },
    { CLASS_TEAM_AQUA, 5 },
    { CLASS_TWINS, 3 },
    { CLASS_SWIMMER_FEMALE, 2 },
    { CLASS_BUG_CATCHER, 4 },
    { CLASS_SCHOOL_KID, 5 },
    { CLASS_RICH_BOY, 50 },
    { CLASS_SR_AND_JR, 4 },
    { CLASS_BLACK_BELT, 8 },
    { CLASS_TUBER, 1 },
    { CLASS_HEX_MANIAC, 6 },
    { CLASS_PKMN_BREEDER, 10 },
    { CLASS_TEAM_MAGMA, 5 },
    { CLASS_INTERVIEWER, 12 },
    { CLASS_TUBER_2, 1 },
    { CLASS_YOUNG_COUPLE, 8 },
    { CLASS_GUITARIST, 8 },
    { CLASS_GENTLEMAN, 20 },
    { CLASS_CHAMPION, 50 },
    { CLASS_MAGMA_LEADER, 20 },
    { CLASS_BATTLE_GIRL, 6 },
    { CLASS_SWIMMER_MALE, 2 },
    { CLASS_POKEFAN, 20 },
    { CLASS_EXPERT, 10 },
    { CLASS_DRAGON_TAMER, 12 },
    { CLASS_BIRD_KEEPER, 8 },
    { CLASS_NINJA_BOY, 3 },
    { CLASS_PARASOL_LADY, 10 },
    { CLASS_BUG_MANIAC, 15 },
    { CLASS_SAILOR, 8 },
    { CLASS_COLLECTOR, 15 },
    { CLASS_PKMN_RANGER, 12 },
    { CLASS_MAGMA_ADMIN, 10 },
    { CLASS_AROMA_LADY, 10 },
    { CLASS_RUIN_MANIAC, 15 },
    { CLASS_COOLTRAINER, 12 },
    { CLASS_POKEMANIAC, 15 },
    { CLASS_KINDLER, 8 },
    { CLASS_CAMPER, 4 },
    { CLASS_PICNICKER, 4 },
    { CLASS_PSYCHIC, 6 },
    { CLASS_SIS_AND_BRO, 3 },
    { CLASS_OLD_COUPLE, 10 },
    { CLASS_AQUA_ADMIN, 10 },
    { CLASS_AQUA_LEADER, 20 },
    { CLASS_BOSS, 25 },
    { 0xFF, 5 },
};


static void (*const sTurnActionsFuncsTable[])(void) =
{
    [B_ACTION_USE_MOVE] = HandleAction_UseMove,
    [B_ACTION_USE_ITEM] = HandleAction_UseItem,
    [B_ACTION_SWITCH] = HandleAction_Switch,
    [B_ACTION_RUN] = HandleAction_Run,
    [B_ACTION_SAFARI_WATCH_CAREFULLY] = HandleAction_WatchesCarefully,
    [B_ACTION_SAFARI_BALL] = HandleAction_SafariZoneBallThrow,
    [B_ACTION_SAFARI_BAIT] = HandleAction_ThrowBait,
    [B_ACTION_SAFARI_GO_NEAR] = HandleAction_ThrowRock,
    [B_ACTION_SAFARI_RUN] = HandleAction_SafariZoneRun,
    [B_ACTION_OLDMAN_THROW] = HandleAction_OldManBallThrow,
    [B_ACTION_EXEC_SCRIPT] = HandleAction_RunBattleScript,
    [B_ACTION_TRY_FINISH] = HandleAction_TryFinish,
    [B_ACTION_FINISHED] = HandleAction_ActionFinished,
    [B_ACTION_NOTHING_FAINTED] = HandleAction_NothingIsFainted,
};

static void (*const sEndTurnFuncsTable[])(void) =
{
    [0] = HandleEndTurn_ContinueBattle, //B_OUTCOME_NONE? //for battle still in progress, everything else goes to finish battle in some way
    [B_OUTCOME_WON] = HandleEndTurn_BattleWon,
    [B_OUTCOME_LOST] = HandleEndTurn_BattleLost,
    [B_OUTCOME_DREW] = HandleEndTurn_BattleLost,
    [B_OUTCOME_RAN] = HandleEndTurn_RanFromBattle,
    [B_OUTCOME_PLAYER_TELEPORTED] = HandleEndTurn_FinishBattle,
    [B_OUTCOME_MON_FLED] = HandleEndTurn_MonFled,
    [B_OUTCOME_CAUGHT] = HandleEndTurn_FinishBattle,
    [B_OUTCOME_NO_SAFARI_BALLS] = HandleEndTurn_FinishBattle,
}; //while not shown all other effects eventually get to HandleEndTurn_FinishBattle

const u8 gStatusConditionString_PoisonJpn[8] = _("どく$$$$$");
const u8 gStatusConditionString_SleepJpn[8] = _("ねむり$$$$");
const u8 gStatusConditionString_ParalysisJpn[8] = _("まひ$$$$$");
const u8 gStatusConditionString_BurnJpn[8] = _("やけど$$$$");
const u8 gStatusConditionString_IceJpn[8] = _("こおり$$$$");
const u8 gStatusConditionString_ConfusionJpn[8] = _("こんらん$$$");
const u8 gStatusConditionString_LoveJpn[8] = _("メロメロ$$$");

const u8 *const gStatusConditionStringsTable[7][2] =
{
    {gStatusConditionString_PoisonJpn, gText_Poison},
    {gStatusConditionString_SleepJpn, gText_Sleep},
    {gStatusConditionString_ParalysisJpn, gText_Paralysis},
    {gStatusConditionString_BurnJpn, gText_Burn},
    {gStatusConditionString_IceJpn, gText_Ice},
    {gStatusConditionString_ConfusionJpn, gText_Confusion},
    {gStatusConditionString_LoveJpn, gText_Love}
};

void CB2_InitBattle(void)
{
    MoveSaveBlocks_ResetHeap();
    AllocateBattleResources();
    AllocateBattleSpritesData();
    AllocateMonSpritesGfx();
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI) //not link, but multiplayer
    {
        return;
        SetMainCallback2(CB2_PreInitMultiBattle);
        gBattleCommunication[MULTIUSE_STATE] = 0;
    } 
    else
    {
        CB2_InitBattleInternal();
      /*  if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
        {
            if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                    SetHelpContext(HELPCONTEXT_TRAINER_BATTLE_DOUBLE);
                else
                    SetHelpContext(HELPCONTEXT_TRAINER_BATTLE_SINGLE);
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
            {
                SetHelpContext(HELPCONTEXT_SAFARI_BATTLE);
            }
            else
            {
                SetHelpContext(HELPCONTEXT_WILD_BATTLE);
            }
        }*/
    }
}

static void CB2_InitBattleInternal(void)
{
    s32 i;

    SetHBlankCallback(NULL);
    SetVBlankCallback(NULL);
    CpuFill32(0, (void *)VRAM, VRAM_SIZE);
    SetGpuReg(REG_OFFSET_MOSAIC, 0);
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0, 0xF0));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(0x50, 0x51));
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    gBattle_WIN0H = WIN_RANGE(0, 0xF0);
    gBattle_WIN0V = WIN_RANGE(0x50, 0x51);
    ScanlineEffect_Clear();
    for (i = 0; i < 80; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = 0xF0;
        gScanlineEffectRegBuffers[1][i] = 0xF0;
    }
    for (; i < 160; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = 0xFF10;
        gScanlineEffectRegBuffers[1][i] = 0xFF10;
    }
    ScanlineEffect_SetParams(sIntroScanlineParams16Bit);
    ResetPaletteFade();
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
    gBattle_BG2_X = 0;
    gBattle_BG2_Y = 0;
    gBattle_BG3_X = 0;
    gBattle_BG3_Y = 0;
    gBattleTerrain = BattleSetup_GetTerrainId();
    InitBattleBgsVideo();
    LoadBattleTextboxAndBackground();
    ResetSpriteData();
    ResetTasks();
    DrawBattleEntryBackground();
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = 4;
    SetVBlankCallback(VBlankCB_Battle);
    SetUpBattleVars();
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        SetMainCallback2(CB2_HandleStartMultiBattle);
    else
        SetMainCallback2(CB2_HandleStartBattle);
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        CreateNPCTrainerParty(&gEnemyParty[0], gTrainerBattleOpponent_A);
        SetWildMonHeldItem();
    }
    gMain.inBattle = TRUE;
    for (i = 0; i < PARTY_SIZE; ++i)
        AdjustFriendship(&gPlayerParty[i], FRIENDSHIP_EVENT_LEAGUE_BATTLE);
    gBattleCommunication[MULTIUSE_STATE] = 0;
}
//believe this is summary screen during battle 
#define BUFFER_PARTY_VS_SCREEN_STATUS(party, flags, i)              \
    for ((i) = 0; (i) < PARTY_SIZE; (i)++)                          \
    {                                                               \
        u16 species = GetMonData(&(party)[(i)], MON_DATA_SPECIES_OR_EGG); \
        u16 hp = GetMonData(&(party)[(i)], MON_DATA_HP);            \
        u32 status = GetMonData(&(party)[(i)], MON_DATA_STATUS);    \
                                                                    \
        if (species == SPECIES_NONE)                                \
            continue;                                               \
                                                                    \
        /* Is healthy mon? */                                       \
        if (species != SPECIES_EGG && hp != 0 && status == 0)       \
            (flags) |= 1 << (i) * 2;                                \
                                                                    \
        if (species == SPECIES_NONE) /* Redundant */                \
            continue;                                               \
                                                                    \
        /* Is Egg or statused? */                                   \
        if (hp != 0 && (species == SPECIES_EGG || status != 0))     \
            (flags) |= 2 << (i) * 2;                                \
                                                                    \
        if (species == SPECIES_NONE) /* Redundant */                \
            continue;                                               \
                                                                    \
        /* Is fainted? */                                           \
        if (species != SPECIES_EGG && hp == 0)                      \
            (flags) |= 3 << (i) * 2;                                \
    }

static void BufferPartyVsScreenHealth_AtStart(void)
{
    u16 flags = 0;
    s32 i;

    BUFFER_PARTY_VS_SCREEN_STATUS(gPlayerParty, flags, i);
    gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsLo = flags;
    *(&gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsHi) = flags >> 8;
}

/*static const u8 sFlailHpScaleToPowerTable[] =
{
    1, 200,
    4, 150,
    9, 100,
    16, 80,
    32, 40,
    48, 20
};*/

// format: min. weight (hectograms), base power
static const u16 sWeightToDamageTable[] =
{
    100, 20,
    250, 40,
    500, 60,
    1000, 80,
    2000, 100,
    0xFFFF, 0xFFFF
};

static const u8 sSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 sHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
static const u8 sTrumpCardPowerTable[] = {200, 80, 60, 50, 40};

const struct TypePower gNaturalGiftTable[] =
{
    [ITEM_TO_BERRY(ITEM_CHERI_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_CHESTO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_PECHA_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RAWST_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_ASPEAR_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_LEPPA_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_ORAN_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_PERSIM_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_LUM_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_SITRUS_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_FIGY_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_WIKI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_MAGO_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_AGUAV_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_IAPAPA_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_RAZZ_BERRY)] = {TYPE_STEEL, 80},
    /*[ITEM_TO_BERRY(ITEM_OCCA_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_PASSHO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_WACAN_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RINDO_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_YACHE_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_CHOPLE_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_KEBIA_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_SHUCA_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_COBA_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_PAYAPA_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_TANGA_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_CHARTI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_KASIB_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_HABAN_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_COLBUR_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_BABIRI_BERRY)] = {TYPE_STEEL, 80},
    [ITEM_TO_BERRY(ITEM_CHILAN_BERRY)] = {TYPE_NORMAL, 80},
    [ITEM_TO_BERRY(ITEM_ROSELI_BERRY)] = {TYPE_FAIRY, 80},*/
    [ITEM_TO_BERRY(ITEM_BLUK_BERRY)] = {TYPE_FIRE, 90},
    [ITEM_TO_BERRY(ITEM_NANAB_BERRY)] = {TYPE_WATER, 90},
    [ITEM_TO_BERRY(ITEM_WEPEAR_BERRY)] = {TYPE_ELECTRIC, 90},
    [ITEM_TO_BERRY(ITEM_PINAP_BERRY)] = {TYPE_GRASS, 90},
    [ITEM_TO_BERRY(ITEM_POMEG_BERRY)] = {TYPE_ICE, 90},
    [ITEM_TO_BERRY(ITEM_KELPSY_BERRY)] = {TYPE_FIGHTING, 90},
    [ITEM_TO_BERRY(ITEM_QUALOT_BERRY)] = {TYPE_POISON, 90},
    [ITEM_TO_BERRY(ITEM_HONDEW_BERRY)] = {TYPE_GROUND, 90},
    [ITEM_TO_BERRY(ITEM_GREPA_BERRY)] = {TYPE_FLYING, 90},
    [ITEM_TO_BERRY(ITEM_TAMATO_BERRY)] = {TYPE_PSYCHIC, 90},
    [ITEM_TO_BERRY(ITEM_CORNN_BERRY)] = {TYPE_BUG, 90},
    [ITEM_TO_BERRY(ITEM_MAGOST_BERRY)] = {TYPE_ROCK, 90},
    [ITEM_TO_BERRY(ITEM_RABUTA_BERRY)] = {TYPE_GHOST, 90},
    [ITEM_TO_BERRY(ITEM_NOMEL_BERRY)] = {TYPE_DRAGON, 90},
    [ITEM_TO_BERRY(ITEM_SPELON_BERRY)] = {TYPE_DARK, 90},
    [ITEM_TO_BERRY(ITEM_PAMTRE_BERRY)] = {TYPE_STEEL, 90},
    [ITEM_TO_BERRY(ITEM_WATMEL_BERRY)] = {TYPE_FIRE, 100},
    [ITEM_TO_BERRY(ITEM_DURIN_BERRY)] = {TYPE_WATER, 100},
    [ITEM_TO_BERRY(ITEM_BELUE_BERRY)] = {TYPE_ELECTRIC, 100},
    [ITEM_TO_BERRY(ITEM_LIECHI_BERRY)] = {TYPE_GRASS, 100},
    [ITEM_TO_BERRY(ITEM_GANLON_BERRY)] = {TYPE_ICE, 100},
    [ITEM_TO_BERRY(ITEM_SALAC_BERRY)] = {TYPE_FIGHTING, 100},
    [ITEM_TO_BERRY(ITEM_PETAYA_BERRY)] = {TYPE_POISON, 100},
    [ITEM_TO_BERRY(ITEM_APICOT_BERRY)] = {TYPE_GROUND, 100},
    [ITEM_TO_BERRY(ITEM_LANSAT_BERRY)] = {TYPE_FLYING, 100},
    [ITEM_TO_BERRY(ITEM_STARF_BERRY)] = {TYPE_PSYCHIC, 100},
    [ITEM_TO_BERRY(ITEM_ENIGMA_BERRY)] = {TYPE_BUG, 100},
    /*[ITEM_TO_BERRY(ITEM_MICLE_BERRY)] = {TYPE_ROCK, 100},
    [ITEM_TO_BERRY(ITEM_CUSTAP_BERRY)] = {TYPE_GHOST, 100},
    [ITEM_TO_BERRY(ITEM_JABOCA_BERRY)] = {TYPE_DRAGON, 100},
    [ITEM_TO_BERRY(ITEM_ROWAP_BERRY)] = {TYPE_DARK, 100},
    [ITEM_TO_BERRY(ITEM_KEE_BERRY)] = {TYPE_FAIRY, 100},
    [ITEM_TO_BERRY(ITEM_MARANGA_BERRY)] = {TYPE_DARK, 100},*/
};

static void SetPlayerBerryDataInBattleStruct(void)
{
    s32 i;
    struct BattleStruct *battleStruct = gBattleStruct;
    struct BattleEnigmaBerry *battleBerry = &battleStruct->multiBuffer.linkPartnerHeader.battleEnigmaBerry;

    if (IsEnigmaBerryValid() == TRUE)
    {
        for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            battleBerry->name[i] = gSaveBlock1Ptr->enigmaBerry.berry.name[i];
        battleBerry->name[i] = EOS;
        for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            battleBerry->itemEffect[i] = gSaveBlock1Ptr->enigmaBerry.itemEffect[i];
        battleBerry->holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
        battleBerry->holdEffectParam = gSaveBlock1Ptr->enigmaBerry.holdEffectParam;
    }
    else
    {
        const struct Berry *berryData = GetBerryInfo(ItemIdToBerryType(ITEM_ENIGMA_BERRY));

        for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            battleBerry->name[i] = berryData->name[i];
        battleBerry->name[i] = EOS;
        for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            battleBerry->itemEffect[i] = 0;
        battleBerry->holdEffect = HOLD_EFFECT_NONE;
        battleBerry->holdEffectParam = 0;
    }
}

static void SetAllPlayersBerryData(void)
{
    s32 i, j;

    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        if (IsEnigmaBerryValid() == TRUE)
        {
            for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            {
                gEnigmaBerries[0].name[i] = gSaveBlock1Ptr->enigmaBerry.berry.name[i];
                gEnigmaBerries[2].name[i] = gSaveBlock1Ptr->enigmaBerry.berry.name[i];
            }
            gEnigmaBerries[0].name[i] = EOS;
            gEnigmaBerries[2].name[i] = EOS;
            for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            {
                gEnigmaBerries[0].itemEffect[i] = gSaveBlock1Ptr->enigmaBerry.itemEffect[i];
                gEnigmaBerries[2].itemEffect[i] = gSaveBlock1Ptr->enigmaBerry.itemEffect[i];
            }
            gEnigmaBerries[0].holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
            gEnigmaBerries[2].holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
            gEnigmaBerries[0].holdEffectParam = gSaveBlock1Ptr->enigmaBerry.holdEffectParam;
            gEnigmaBerries[2].holdEffectParam = gSaveBlock1Ptr->enigmaBerry.holdEffectParam;
        }
        else
        {
            const struct Berry *berryData = GetBerryInfo(ItemIdToBerryType(ITEM_ENIGMA_BERRY));

            for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            {
                gEnigmaBerries[0].name[i] = berryData->name[i];
                gEnigmaBerries[2].name[i] = berryData->name[i];
            }
            gEnigmaBerries[0].name[i] = EOS;
            gEnigmaBerries[2].name[i] = EOS;
            for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            {
                gEnigmaBerries[0].itemEffect[i] = 0;
                gEnigmaBerries[2].itemEffect[i] = 0;
            }
            gEnigmaBerries[0].holdEffect = HOLD_EFFECT_NONE;
            gEnigmaBerries[2].holdEffect = HOLD_EFFECT_NONE;
            gEnigmaBerries[0].holdEffectParam = 0;
            gEnigmaBerries[2].holdEffectParam = 0;
        }
    }
    else
    {
        s32 numPlayers;
        struct BattleEnigmaBerry *src;
        u8 battlerId;

        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            for (i = 0; i < 4; ++i)
            {
                src = (struct BattleEnigmaBerry *)(gBlockRecvBuffer[i] + 2);
                battlerId = gLinkPlayers[i].id;
                for (j = 0; j < BERRY_NAME_LENGTH; ++j)
                    gEnigmaBerries[battlerId].name[j] = src->name[j];
                gEnigmaBerries[battlerId].name[j] = EOS;
                for (j = 0; j < BERRY_ITEM_EFFECT_COUNT; ++j)
                    gEnigmaBerries[battlerId].itemEffect[j] = src->itemEffect[j];
                gEnigmaBerries[battlerId].holdEffect = src->holdEffect;
                gEnigmaBerries[battlerId].holdEffectParam = src->holdEffectParam;
            }
        }
        else
        {
            for (i = 0; i < 2; ++i)
            {
                src = (struct BattleEnigmaBerry *)(gBlockRecvBuffer[i] + 2);
                for (j = 0; j < BERRY_NAME_LENGTH; ++j)
                {
                    gEnigmaBerries[i].name[j] = src->name[j];
                    gEnigmaBerries[i + 2].name[j] = src->name[j];
                }
                gEnigmaBerries[i].name[j] = EOS;
                gEnigmaBerries[i + 2].name[j] = EOS;
                for (j = 0; j < BERRY_ITEM_EFFECT_COUNT; ++j)
                {
                    gEnigmaBerries[i].itemEffect[j] = src->itemEffect[j];
                    gEnigmaBerries[i + 2].itemEffect[j] = src->itemEffect[j];
                }
                gEnigmaBerries[i].holdEffect = src->holdEffect;
                gEnigmaBerries[i + 2].holdEffect = src->holdEffect;
                gEnigmaBerries[i].holdEffectParam = src->holdEffectParam;
                gEnigmaBerries[i + 2].holdEffectParam = src->holdEffectParam;
            }
        }
    }
}

//have plans for but not currently used
/*
static void HandleAction_WaitTurnEnd(void) {
    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
    {
        gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
        PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, *(gBattleStruct->battlerPartyIndexes + gBattlerAttacker));
        gBattleScripting.battler = gBattlerAttacker;
        gBattlescriptCurrInstr = BattleScript_SkipTurn;
        gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
        //gCurrentActionFuncId = B_ACTION_FINISHED;
        //++gCurrentTurnActionNumber;
    }
}*/

//make strings for these, and for the move iteslf
//can use to just make strings that I can define here, rather than needing to make new string ids
//StringExpandPlaceholders(gStringVar4, sText_EVO_ITEM_HOLD_NIGHT );
//use {B_DEF_NAME}  for target name, can make one string and just 
//populate a buffer with case specific text using compoundstring
//static const u8 sText_EVO_SPECIFIC_MON_IN_PARTY[] = _("{LV}{UP_ARROW} with {STR_VAR_2} in party");


void SetJudgmentTypeString(u8 type) //if type is normal skip the jugment string in script
{
    switch (type) //Target Name faces X Judgement!  //buffering X here  - do like magnitude after move name, before animation
    {
        
        case TYPE_FIGHTING:
            StringCopy(gStringVar2, COMPOUND_STRING("Fierce")); //doesn't throw up errors so gues I'm good, that said prob need actually define later for placeholder cap
        break;
        case TYPE_FLYING:
            StringCopy(gStringVar2, COMPOUND_STRING("the Sky's")); //the Sky's /Sky
        break;
        case TYPE_POISON:
            StringCopy(gStringVar2, COMPOUND_STRING("Toxic")); //Toxic/Poisonous
        break;
        case TYPE_GROUND:
            StringCopy(gStringVar2, COMPOUND_STRING("Earth")); // the Earth's /Earth
        break;
        case TYPE_ROCK:
            StringCopy(gStringVar2, COMPOUND_STRING("Stone")); //Stone
        break;
        case TYPE_BUG:
            StringCopy(gStringVar2, COMPOUND_STRING("Bug")); //Bug
        break;
        case TYPE_GHOST:
            StringCopy(gStringVar2, COMPOUND_STRING("Spooky")); //Spooky/Ghost
        break;
        case TYPE_STEEL:
            StringCopy(gStringVar2, COMPOUND_STRING("Iron")); //Steel
        break;
        case TYPE_FIRE:
            StringCopy(gStringVar2, COMPOUND_STRING("Fiery")); // Fiery
        break;
        case TYPE_WATER:
            StringCopy(gStringVar2, COMPOUND_STRING("Watery")); //Watery
        break;
        case TYPE_GRASS:
            StringCopy(gStringVar2, COMPOUND_STRING("Nature's")); //Nature's / Nature
        break;
        case TYPE_ELECTRIC:
            StringCopy(gStringVar2, COMPOUND_STRING("Shocking")); //Shocking
        break;
        case TYPE_PSYCHIC:
            StringCopy(gStringVar2, COMPOUND_STRING("Psychic")); //Mental / Psychic
        break;
        case TYPE_ICE:
            StringCopy(gStringVar2, COMPOUND_STRING("Cold")); //Cold
        break;
        case TYPE_DRAGON:
            StringCopy(gStringVar2, COMPOUND_STRING("Draconic")); //Draconic
        break;
        case TYPE_DARK:
            StringCopy(gStringVar2, COMPOUND_STRING("Dark")); //Dark
        break;
        case TYPE_FAIRY:
            StringCopy(gStringVar2, COMPOUND_STRING("Fae")); //Fae
        break;
    }
    
}

#define LOGIC_FOR_MOVETYPE_CHANGE
void SetTypeBeforeUsingMove(u16 move, u8 battlerAtk)
{
    s32 typeBits;
    u32 moveType, ateType, attackerAbility;
    u16 holdEffect = GetBattlerHoldEffect(battlerAtk, TRUE);

    if (move == MOVE_STRUGGLE || move == MOVE_BIDE)
        return;

    gBattleStruct->dynamicMoveType = 0xFF; //change for new setup
    gBattleStruct->ateBoost[battlerAtk] = 0;
    gSpecialStatuses[battlerAtk].gemBoost = FALSE;

    
    if (gBattleMoves[move].effect == EFFECT_CHANGE_TYPE_ON_ITEM) //not fling
    {
        if (holdEffect == gBattleMoves[move].argument)
            gBattleStruct->dynamicMoveType = ItemId_GetSecondaryId(gBattleMons[battlerAtk].item);// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].effect == EFFECT_REVELATION_DANCE)
    {
        if (gBattleMons[battlerAtk].type1 != TYPE_MYSTERY)
            gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type1;// | F_DYNAMIC_TYPE_2;
        else if (gBattleMons[battlerAtk].type2 != TYPE_MYSTERY)
            gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type2;// | F_DYNAMIC_TYPE_2;
        else if (gBattleMons[battlerAtk].type3 != TYPE_MYSTERY)
            gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type3;// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].effect == EFFECT_NATURAL_GIFT)
    {
        if (ItemId_GetPocket(gBattleMons[battlerAtk].item) == POCKET_BERRY_POUCH)
            gBattleStruct->dynamicMoveType = gNaturalGiftTable[ITEM_TO_BERRY(gBattleMons[battlerAtk].item)].type;
    }
    else if (gBattleMoves[move].effect == EFFECT_TERRAIN_PULSE)
    {
        if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_TERRAIN_ANY))
        {
            if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_GRASS;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_FAIRY;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_PSYCHIC;// | F_DYNAMIC_TYPE_2;
            else //failsafe
                gBattleStruct->dynamicMoveType = TYPE_NORMAL;// | F_DYNAMIC_TYPE_2;
        }
    }
    else if ((move == MOVE_WEATHER_BALL) && (WEATHER_HAS_EFFECT)) //thought set elsewhere but guess no longer need that
    {
         if (gBattleWeather & WEATHER_RAIN_ANY) //TEST TO MAKE SURE WORKS - works
            gBattleStruct->dynamicMoveType = TYPE_WATER;
        else if (gBattleWeather & WEATHER_SANDSTORM_ANY)
            gBattleStruct->dynamicMoveType = TYPE_ROCK;
        else if (gBattleWeather & WEATHER_SUN_ANY)
            gBattleStruct->dynamicMoveType = TYPE_FIRE;
        else if (gBattleWeather & WEATHER_HAIL_ANY)
            gBattleStruct->dynamicMoveType = TYPE_ICE;
        else if (gBattleWeather & WEATHER_STRONG_WINDS)
            gBattleStruct->dynamicMoveType = TYPE_FLYING;
        else
            gBattleStruct->dynamicMoveType = TYPE_NORMAL;
    }

    attackerAbility = GetBattlerAbility(battlerAtk);
    GET_MOVE_TYPE(move, moveType);

    //don't attempt to put type changes here that happen BEFORE target selction
    //those must be done in typecalc


    if (move == MOVE_RAGE) //sets rage type with preference for non normal
        {
            if (gBattleMons[battlerAtk].type1 == TYPE_NORMAL 
            && gBattleMons[battlerAtk].type2 != TYPE_NORMAL)
                gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type2;
            else //sets rage to type 1
                gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type1; //need make sure use battlerAtk not gbattlerattacker that causes errors for some reason
        }

    if ((gFieldStatuses & STATUS_FIELD_ION_DELUGE && moveType == TYPE_NORMAL)//add absolute zero, check if ability on field, like stench then do water chance to ice
        || gStatuses4[battlerAtk] & STATUS4_ELECTRIFIED)
    {
        gBattleStruct->dynamicMoveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;   //need test if these work without this extra value
    }
    else if (IsAbilityOnField(ABILITY_ABSOLUTE_ZERO) && moveType == TYPE_WATER)
    {
        gBattleStruct->dynamicMoveType = TYPE_ICE;
    }
    else if (gBattleMoves[move].type == TYPE_NORMAL
             && move != MOVE_HIDDEN_POWER    //can remove effects for hidden ower and weather ball can just use hit, and do everything w move name 
             && move != MOVE_WEATHER_BALL    //as effects are never reused, i.e only for those specific moves
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && ((attackerAbility == ABILITY_PIXILATE && (ateType = TYPE_FAIRY))
                 || (attackerAbility == ABILITY_REFRIGERATE && (ateType = TYPE_ICE))
                 || (attackerAbility == ABILITY_AERILATE && (ateType = TYPE_FLYING))
                 || (attackerAbility == ABILITY_GALVANIZE && (ateType = TYPE_ELECTRIC))
                 || (attackerAbility == ABILITY_UNCHAINED_MELODY && (ateType = TYPE_SOUND))))
    {
        gBattleStruct->dynamicMoveType = ateType;// | F_DYNAMIC_TYPE_2; //above should do type change already, dmg boosts are already in pokemon.c
        gBattleStruct->ateBoost[battlerAtk] = 1;
    }
    else if (gBattleMoves[move].type == TYPE_SOUND
             && move != MOVE_HIDDEN_POWER
             && move != MOVE_WEATHER_BALL
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && ((attackerAbility == ABILITY_PIXILATE && (ateType = TYPE_FAIRY))))//Think leave just for fairy? fairy for sound kinda makes sense to me, think they sing?
    {
        gBattleStruct->dynamicMoveType = ateType;// | F_DYNAMIC_TYPE_2; //above should do type change already, dmg boosts are already in pokemon.c
        gBattleStruct->ateBoost[battlerAtk] = 1;
    }
    else if ((move != MOVE_HIDDEN_POWER
             && move != MOVE_WEATHER_BALL
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM)
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && attackerAbility == ABILITY_NORMALIZE)   //thought to remove normal exclusion, but would just result in them getting much weaker
    {                                                   //without stab, so not worth
        gBattleStruct->dynamicMoveType = TYPE_NORMAL;// | F_DYNAMIC_TYPE_2;    //WILL MAke moves do neutral damage to everything, need exclude from joat.
        gBattleStruct->ateBoost[battlerAtk] = 1;    //actually I can do this with typecalc function and they can keep stab.
    }
    else if (gBattleMoves[move].flags & FLAG_SOUND
             && attackerAbility == ABILITY_LIQUID_VOICE)
    {
        gBattleStruct->dynamicMoveType = TYPE_WATER;// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].type == TYPE_WATER
        && attackerAbility == ABILITY_LIQUID_SOUL)
    {
        gBattleStruct->dynamicMoveType = TYPE_GHOST;// | F_DYNAMIC_TYPE_2;
    }
    else if (attackerAbility == ABILITY_WETIKO)//technically should put last, but I like the idea of it hitting everything except hidden power
    {
        gBattleStruct->dynamicMoveType = TYPE_ICE;// | F_DYNAMIC_TYPE_2;
    }
    else if (gStatuses4[battlerAtk] & STATUS4_PLASMA_FISTS && moveType == TYPE_NORMAL)
    {
        gBattleStruct->dynamicMoveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;
    }
    else if (move == MOVE_AURA_WHEEL && gBattleMons[battlerAtk].species == SPECIES_MORPEKO_HANGRY)
    {
        gBattleStruct->dynamicMoveType = TYPE_DARK;// | F_DYNAMIC_TYPE_2;
    }

    else if (move == MOVE_HIDDEN_POWER)
    {

        typeBits = ((gBattleMons[battlerAtk].hpIV & 1) << 0)
            | ((gBattleMons[battlerAtk].attackIV & 1) << 1)
            | ((gBattleMons[battlerAtk].defenseIV & 1) << 2)
            | ((gBattleMons[battlerAtk].speedIV & 1) << 3)
            | ((gBattleMons[battlerAtk].spAttackIV & 1) << 4)
            | ((gBattleMons[battlerAtk].spDefenseIV & 1) << 5);

        //// Subtract 3 instead of 1 below because 2 types are excluded (TYPE_NORMAL and TYPE_MYSTERY)
         // The final + 1 skips past Normal, and the following conditional skips TYPE_MYSTERY
        //changed to -4 for sound type addition, need test unsure if fully necessary
        gBattleStruct->dynamicMoveType = ((NUMBER_OF_MON_TYPES - 4) * typeBits) / 63 + 1; //think changing from 15 to 16 adds one more type to options so now have fairy
        if (gBattleStruct->dynamicMoveType == TYPE_MYSTERY || gBattleStruct->dynamicMoveType == TYPE_SOUND) //add or for type sound
            gBattleStruct->dynamicMoveType = TYPE_FAIRY; 
        gBattleStruct->dynamicMoveType |= F_DYNAMIC_TYPE_1 | F_DYNAMIC_TYPE_2;
    }

    // Check if a gem should activate.
    GET_MOVE_TYPE(move, moveType);
    if (holdEffect == HOLD_EFFECT_GEMS
        && moveType == ItemId_GetSecondaryId(gBattleMons[battlerAtk].item))
    {
        gSpecialStatuses[battlerAtk].gemParam = GetBattlerHoldEffectParam(battlerAtk, gBattleMons[battlerAtk].item);
        gSpecialStatuses[battlerAtk].gemBoost = TRUE;
    }
}

//-works perfectly, need make sure keep in track with above function - unsure if properly tracks hidden power?
//could change this make use function argument to instead of actually setting dynamic type,
//would be able to use to test what type will be, could be used everywhere
//without needing to worry about actually setting the type
u8 ReturnMoveType(u16 move, u8 battlerAtk) 
{
    s32 typeBits;
    u32 moveType, ateType, attackerAbility;
    u16 holdEffect = GetBattlerHoldEffect(battlerAtk, TRUE);

    //populate default type, go through assignment and return what would be changed type
    moveType = gBattleMoves[move].type;

    if (move == MOVE_STRUGGLE || move == MOVE_BIDE)
        return 0xFF;


    gBattleStruct->ateBoost[battlerAtk] = 0;
    gSpecialStatuses[battlerAtk].gemBoost = FALSE;

    
    if (gBattleMoves[move].effect == EFFECT_CHANGE_TYPE_ON_ITEM) //not fling
    {
        if (holdEffect == gBattleMoves[move].argument)
            moveType = ItemId_GetSecondaryId(gBattleMons[battlerAtk].item);// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].effect == EFFECT_REVELATION_DANCE)
    {
        if (gBattleMons[battlerAtk].type1 != TYPE_MYSTERY)
            moveType = gBattleMons[battlerAtk].type1;// | F_DYNAMIC_TYPE_2;
        else if (gBattleMons[battlerAtk].type2 != TYPE_MYSTERY)
            moveType = gBattleMons[battlerAtk].type2;// | F_DYNAMIC_TYPE_2;
        else if (gBattleMons[battlerAtk].type3 != TYPE_MYSTERY)
            moveType = gBattleMons[battlerAtk].type3;// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].effect == EFFECT_NATURAL_GIFT)
    {
        if (ItemId_GetPocket(gBattleMons[battlerAtk].item) == POCKET_BERRY_POUCH)
            moveType = gNaturalGiftTable[ITEM_TO_BERRY(gBattleMons[battlerAtk].item)].type;
    }
    else if (gBattleMoves[move].effect == EFFECT_TERRAIN_PULSE)
    {
        if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_TERRAIN_ANY))
        {
            if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
                moveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
                moveType = TYPE_GRASS;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
                moveType = TYPE_FAIRY;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
                moveType = TYPE_PSYCHIC;// | F_DYNAMIC_TYPE_2;
            else //failsafe
                moveType = TYPE_NORMAL;// | F_DYNAMIC_TYPE_2;
        }
    }
    else if ((move == MOVE_WEATHER_BALL) && (WEATHER_HAS_EFFECT))
    {
         if (gBattleWeather & WEATHER_RAIN_ANY) //TEST TO MAKE SURE WORKS - works
            moveType = TYPE_WATER;
        else if (gBattleWeather & WEATHER_SANDSTORM_ANY)
            moveType = TYPE_ROCK;
        else if (gBattleWeather & WEATHER_SUN_ANY)
            moveType = TYPE_FIRE;
        else if (gBattleWeather & WEATHER_HAIL_ANY)
            moveType = TYPE_ICE;
        else if (gBattleWeather & WEATHER_STRONG_WINDS)
            moveType = TYPE_FLYING;
        else
            moveType = TYPE_NORMAL;
    }

    attackerAbility = GetBattlerAbility(battlerAtk);
    //GET_MOVE_TYPE(move, moveType);


    if (move == MOVE_RAGE) //sets rage type with preference for non normal
        {
            if (gBattleMons[battlerAtk].type1 == TYPE_NORMAL 
            && gBattleMons[battlerAtk].type2 != TYPE_NORMAL)
                moveType = gBattleMons[battlerAtk].type2;
            else //sets rage to type 1
                moveType = gBattleMons[battlerAtk].type1; //need make sure use battlerAtk not gbattlerattacker that causes errors for some reason
        }

    if ((gFieldStatuses & STATUS_FIELD_ION_DELUGE && moveType == TYPE_NORMAL)//add absolute zero, check if ability on field, like stench then do water chance to ice
        || gStatuses4[battlerAtk] & STATUS4_ELECTRIFIED)
    {
        moveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;   //need test if these work without this extra value
    }
    else if (IsAbilityOnField(ABILITY_ABSOLUTE_ZERO) && moveType == TYPE_WATER)
    {
        moveType = TYPE_ICE;
    }
    else if (gBattleMoves[move].type == TYPE_NORMAL
             && move != MOVE_HIDDEN_POWER
             && move != MOVE_WEATHER_BALL
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && ((attackerAbility == ABILITY_PIXILATE && (ateType = TYPE_FAIRY))
                 || (attackerAbility == ABILITY_REFRIGERATE && (ateType = TYPE_ICE))
                 || (attackerAbility == ABILITY_AERILATE && (ateType = TYPE_FLYING))
                 || ((attackerAbility == ABILITY_GALVANIZE) && (ateType = TYPE_ELECTRIC))
                 || (attackerAbility == ABILITY_UNCHAINED_MELODY && (ateType = TYPE_SOUND))))
    {
        moveType = ateType;// | F_DYNAMIC_TYPE_2; //above should do type change already, dmg boosts are already in pokemon.c

    }
    else if (gBattleMoves[move].type == TYPE_SOUND
             && move != MOVE_HIDDEN_POWER
             && move != MOVE_WEATHER_BALL
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && ((attackerAbility == ABILITY_PIXILATE && (ateType = TYPE_FAIRY))))//Think leave just for fairy? fairy for sound kinda makes sense to me, think they sing?
    {
        moveType = ateType;// | F_DYNAMIC_TYPE_2; //above should do type change already, dmg boosts are already in pokemon.c

    }
    else if ((move != MOVE_HIDDEN_POWER
             && move != MOVE_WEATHER_BALL //note was before changed type calc, 
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM)
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && attackerAbility == ABILITY_NORMALIZE)   //thought to remove normal exclusion, but would just result in them getting much weaker
    {                                                   //without stab, so not worth
        moveType = TYPE_NORMAL;// | F_DYNAMIC_TYPE_2;    //WILL MAke moves do neutral damage to everything, need exclude from joat.
                                                        //actually I can do this with typecalc function and they can keep stab.
    }
    else if (gBattleMoves[move].flags & FLAG_SOUND
             && attackerAbility == ABILITY_LIQUID_VOICE)
    {
        moveType = TYPE_WATER;// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].type == TYPE_WATER
        && attackerAbility == ABILITY_LIQUID_SOUL)
    {
        moveType = TYPE_GHOST;// | F_DYNAMIC_TYPE_2;
    }
    else if (attackerAbility == ABILITY_WETIKO)
    {
        moveType = TYPE_ICE;// | F_DYNAMIC_TYPE_2;
    }
    else if (gStatuses4[battlerAtk] & STATUS4_PLASMA_FISTS && moveType == TYPE_NORMAL)
    {
        moveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;
    }
    else if (move == MOVE_AURA_WHEEL && gBattleMons[battlerAtk].species == SPECIES_MORPEKO_HANGRY)
    {
        moveType = TYPE_DARK;// | F_DYNAMIC_TYPE_2;
    }

    else if (move == MOVE_HIDDEN_POWER)
    {

        typeBits = ((gBattleMons[battlerAtk].hpIV & 1) << 0)
            | ((gBattleMons[battlerAtk].attackIV & 1) << 1)
            | ((gBattleMons[battlerAtk].defenseIV & 1) << 2)
            | ((gBattleMons[battlerAtk].speedIV & 1) << 3)
            | ((gBattleMons[battlerAtk].spAttackIV & 1) << 4)
            | ((gBattleMons[battlerAtk].spDefenseIV & 1) << 5);

        //// Subtract 3 instead of 1 below because 2 types are excluded (TYPE_NORMAL and TYPE_MYSTERY)
         // The final + 1 skips past Normal, and the following conditional skips TYPE_MYSTERY
        //changed to -4 for sound type addition, need test unsure if fully necessary
        moveType = ((NUMBER_OF_MON_TYPES - 4) * typeBits) / 63 + 1; //think changing from 15 to 16 adds one more type to options so now have fairy
        if (moveType == TYPE_MYSTERY || moveType == TYPE_SOUND) //add or for type sound
            moveType = TYPE_FAIRY; 
        moveType |= F_DYNAMIC_TYPE_1 | F_DYNAMIC_TYPE_2;
    }

    return moveType;
}

static void LinkBattleComputeBattleTypeFlags(u8 numPlayers, u8 multiPlayerId)
{
    u8 found = 0;

    // If player 1 is playing the minimum version, player 1 is master.
    if (gBlockRecvBuffer[0][0] == 0x100)
    {
        if (multiPlayerId == 0)
            gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_TRAINER;
        else
            gBattleTypeFlags |= BATTLE_TYPE_TRAINER;
        ++found;
    }
    if (found == 0)
    {
        // If multiple different versions are being used, player 1 is master.
        s32 i;

        for (i = 0; i < numPlayers; ++i)
            if (gBlockRecvBuffer[0][0] != gBlockRecvBuffer[i][0])
                break;
        if (i == numPlayers)
        {
            if (multiPlayerId == 0)
                gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_TRAINER;
            else
                gBattleTypeFlags |= BATTLE_TYPE_TRAINER;
            ++found;
        }
        if (found == 0)
        {
            // Lowest index player with the highest game version is master.
            for (i = 0; i < numPlayers; ++i)
            {
                if (gBlockRecvBuffer[i][0] == 0x201 && i != multiPlayerId)
                    if (i < multiPlayerId)
                        break;
                if (gBlockRecvBuffer[i][0] > 0x201 && i != multiPlayerId)
                    break;
            }
            if (i == numPlayers)
                gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_TRAINER;
            else
                gBattleTypeFlags |= BATTLE_TYPE_TRAINER;
        }
    }
}

static void CB2_HandleStartBattle(void)
{
    u8 playerMultiplayerId;
    u8 enemyMultiplayerId;

    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    playerMultiplayerId = GetMultiplayerId();
    gBattleStruct->multiplayerId = playerMultiplayerId;
    enemyMultiplayerId = playerMultiplayerId ^ BIT_SIDE;
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            ShowBg(3);
            BattleInterfaceSetWindowPals();
            gBattleCommunication[MULTIUSE_STATE] = 1;
        }
        if (gWirelessCommType)
            LoadWirelessStatusIndicatorSpriteGfx();
        break;
    case 1:
        if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        {
            if (gReceivedRemoteLinkPlayers)
            {
                if (IsLinkTaskFinished())
                {
                    // 0x201
                    *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureLo) = 1;
                    *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureHi) = 2;
                    BufferPartyVsScreenHealth_AtStart();
                    SetPlayerBerryDataInBattleStruct();
                    SendBlock(bitmask_all_link_players_but_self(), &gBattleStruct->multiBuffer.linkPartnerHeader, sizeof(gBattleStruct->multiBuffer.linkPartnerHeader));
                    gBattleCommunication[MULTIUSE_STATE] = 2;
                }
                if (gWirelessCommType != 0)
                    CreateWirelessStatusIndicatorSprite(0, 0);
            }
        }
        else
        {
            gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER;
            gBattleCommunication[MULTIUSE_STATE] = 15;
            SetAllPlayersBerryData();
        }
        break; 
    case 2:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            u8 taskId;

            ResetBlockReceivedFlags();
            LinkBattleComputeBattleTypeFlags(2, playerMultiplayerId);
            SetAllPlayersBerryData();
            taskId = CreateTask(InitLinkBattleVsScreen, 0);
            gTasks[taskId].data[1] = 270;
            gTasks[taskId].data[2] = 90;
            gTasks[taskId].data[5] = 0;
            gTasks[taskId].data[3] = gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsLo | (gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsHi << 8);
            gTasks[taskId].data[4] = gBlockRecvBuffer[enemyMultiplayerId][1];
            SetDeoxysStats();
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 3:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 4:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(gEnemyParty, gBlockRecvBuffer[enemyMultiplayerId], sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 7:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty + 2, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 8:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(gEnemyParty + 2, gBlockRecvBuffer[enemyMultiplayerId], sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 11:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty + 4, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 12:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(gEnemyParty + 4, gBlockRecvBuffer[enemyMultiplayerId], sizeof(struct Pokemon) * 2);
            TryCorrectShedinjaLanguage(&gEnemyParty[0]);
            TryCorrectShedinjaLanguage(&gEnemyParty[1]);
            TryCorrectShedinjaLanguage(&gEnemyParty[2]);
            TryCorrectShedinjaLanguage(&gEnemyParty[3]);
            TryCorrectShedinjaLanguage(&gEnemyParty[4]);
            TryCorrectShedinjaLanguage(&gEnemyParty[5]);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 15:
        InitBtlControllers();
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[SPRITES_INIT_STATE1] = 0;
        gBattleCommunication[SPRITES_INIT_STATE2] = 0;
        break;
    case 16:
        if (BattleInitAllSprites(&gBattleCommunication[SPRITES_INIT_STATE1], &gBattleCommunication[SPRITES_INIT_STATE2]))
        {
            gPreBattleCallback1 = gMain.callback1;
            gMain.callback1 = BattleMainCB1;
            SetMainCallback2(BattleMainCB2);
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
            {
                gBattleTypeFlags |= BATTLE_TYPE_20;
            }
        }
        break;
    case 5:
    case 9:
    case 13:
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[1] = 1;
    case 6:
    case 10:
    case 14:
        if (--gBattleCommunication[1] == 0)
            ++gBattleCommunication[MULTIUSE_STATE];
        break;
    }
}

static void PrepareOwnMultiPartnerBuffer(void)
{
    s32 i, j;
    u8 *nick, *cur;

    for (i = 0; i < 3; ++i)
    {
        gMultiPartnerParty[i].species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        gMultiPartnerParty[i].heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
        nick = gMultiPartnerParty[i].nickname;
        GetMonData(&gPlayerParty[i], MON_DATA_NICKNAME, nick);
        gMultiPartnerParty[i].level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
        gMultiPartnerParty[i].hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
        gMultiPartnerParty[i].maxhp = GetMonData(&gPlayerParty[i], MON_DATA_MAX_HP);
        gMultiPartnerParty[i].status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
        gMultiPartnerParty[i].personality = GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY);
        gMultiPartnerParty[i].gender = GetMonGender(&gPlayerParty[i]);
        StripExtCtrlCodes(nick);
        if (GetMonData(&gPlayerParty[i], MON_DATA_LANGUAGE) != LANGUAGE_JAPANESE)
        {
            for (cur = nick, j = 0; cur[j] != EOS; ++j)
                ;
            while (j < 6)
                cur[j++] = 0;
            cur[j] = EOS;
        }
    }
    memcpy(gBattleStruct->multiBuffer.multiBattleMons, gMultiPartnerParty, sizeof(gMultiPartnerParty));
}

static void CB2_PreInitMultiBattle(void)
{
    s32 i;
    u8 playerMultiplierId;
    u8 r4 = 0xF;
    u16 *savedBattleTypeFlags;
    void (**savedCallback)(void);

    playerMultiplierId = GetMultiplayerId();
    gBattleStruct->multiplayerId = playerMultiplierId;
    savedCallback = &gBattleStruct->savedCallback;
    savedBattleTypeFlags = &gBattleStruct->savedBattleTypeFlags;

    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        if (gReceivedRemoteLinkPlayers && IsLinkTaskFinished())
        {
            PrepareOwnMultiPartnerBuffer();
            SendBlock(bitmask_all_link_players_but_self(), gBattleStruct->multiBuffer.multiBattleMons, sizeof(gBattleStruct->multiBuffer.multiBattleMons));
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 1:
        if ((GetBlockReceivedStatus() & r4) == r4)
        {
            ResetBlockReceivedFlags();
            for (i = 0; i < 4; ++i)
            {
                if (i == playerMultiplierId)
                    continue;
                if ((!(gLinkPlayers[i].id & 1) && !(gLinkPlayers[playerMultiplierId].id & 1))
                 || (gLinkPlayers[i].id & 1 && gLinkPlayers[playerMultiplierId].id & 1))
                    memcpy(gMultiPartnerParty, gBlockRecvBuffer[i], sizeof(gMultiPartnerParty));
            }
            ++gBattleCommunication[MULTIUSE_STATE];
            *savedCallback = gMain.savedCallback;
            *savedBattleTypeFlags = gBattleTypeFlags;
            gMain.savedCallback = CB2_PreInitMultiBattle;
            ShowPartyMenuToShowcaseMultiBattleParty();
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            ++gBattleCommunication[MULTIUSE_STATE];
            if (gWirelessCommType)
                SetLinkStandbyCallback();
            else
                SetCloseLinkCallback();
        }
        break;
    case 3:
        if (gWirelessCommType)
        {
            if (IsLinkRfuTaskFinished())
            {
                gBattleTypeFlags = *savedBattleTypeFlags;
                gMain.savedCallback = *savedCallback;
                SetMainCallback2(CB2_InitBattleInternal);
            }
        }
        else if (!gReceivedRemoteLinkPlayers)
        {
            gBattleTypeFlags = *savedBattleTypeFlags;
            gMain.savedCallback = *savedCallback;
            SetMainCallback2(CB2_InitBattleInternal);
        }
        break;
    }
}

static void CB2_HandleStartMultiBattle(void)
{
    u8 playerMultiplayerId;
    s32 id;
    u8 taskId;

    playerMultiplayerId = GetMultiplayerId();
    gBattleStruct->multiplayerId = playerMultiplayerId;
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            ShowBg(3);
            BattleInterfaceSetWindowPals();
            gBattleCommunication[MULTIUSE_STATE] = 1;
        }
        if (gWirelessCommType)
            LoadWirelessStatusIndicatorSpriteGfx();
        break;
    case 1:
        if (gReceivedRemoteLinkPlayers)
        {
            if (IsLinkTaskFinished())
            {
                // 0x201
                *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureLo) = 1;
                *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureHi) = 2;
                BufferPartyVsScreenHealth_AtStart();
                SetPlayerBerryDataInBattleStruct();
                SendBlock(bitmask_all_link_players_but_self(), &gBattleStruct->multiBuffer.linkPartnerHeader, sizeof(gBattleStruct->multiBuffer.linkPartnerHeader));
                ++gBattleCommunication[MULTIUSE_STATE];
            }
            if (gWirelessCommType)
                CreateWirelessStatusIndicatorSprite(0, 0);
        }
        break; 
    case 2:
        if ((GetBlockReceivedStatus() & 0xF) == 0xF)
        {
            ResetBlockReceivedFlags();
            LinkBattleComputeBattleTypeFlags(4, playerMultiplayerId);
            SetAllPlayersBerryData();
            SetDeoxysStats();
            //memcpy(gDecompressionBuffer, gPlayerParty, sizeof(struct Pokemon) * 3); //for some reason not in EE
            taskId = CreateTask(InitLinkBattleVsScreen, 0);
            gTasks[taskId].data[1] = 270;
            gTasks[taskId].data[2] = 90;
            gTasks[taskId].data[5] = 0;
            gTasks[taskId].data[3] = 0;
            gTasks[taskId].data[4] = 0;
            for (id = 0; id < MAX_LINK_PLAYERS; ++id)
            {
                switch (gLinkPlayers[id].id)
                {
                case 0:
                    gTasks[taskId].data[3] |= gBlockRecvBuffer[id][1] & 0x3F;
                    break;
                case 1:
                    gTasks[taskId].data[4] |= gBlockRecvBuffer[id][1] & 0x3F;
                    break;
                case 2:
                    gTasks[taskId].data[3] |= (gBlockRecvBuffer[id][1] & 0x3F) << 6;
                    break;
                case 3:
                    gTasks[taskId].data[4] |= (gBlockRecvBuffer[id][1] & 0x3F) << 6;
                    break;
                }
            }
            ZeroPlayerPartyMons();
            ZeroEnemyPartyMons();
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        else
        {
            break;
        }
        // fall through
    case 3:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 4:
        if ((GetBlockReceivedStatus() & 0xF) == 0xF)
        {
            ResetBlockReceivedFlags();
            for (id = 0; id < MAX_LINK_PLAYERS; ++id)
            {
                if (id == playerMultiplayerId)
                {
                    switch (gLinkPlayers[id].id)
                    {
                    case 0:
                    case 3:
                        memcpy(gPlayerParty, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                        break;
                    case 1:
                    case 2:
                        memcpy(gPlayerParty + 3, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                        break;
                    }
                }
                else
                {
                    if ((!(gLinkPlayers[id].id & 1) && !(gLinkPlayers[playerMultiplayerId].id & 1))
                     || ((gLinkPlayers[id].id & 1) && (gLinkPlayers[playerMultiplayerId].id & 1)))
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gPlayerParty, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        case 1:
                        case 2:
                            memcpy(gPlayerParty + 3, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        }
                    }
                    else
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gEnemyParty, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        case 1:
                        case 2:
                            memcpy(gEnemyParty + 3, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        }
                    }
                }
            }
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 7:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty + 2, sizeof(struct Pokemon));
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break; 
    case 8:
        if ((GetBlockReceivedStatus() & 0xF) == 0xF)
        {
            ResetBlockReceivedFlags();
            for (id = 0; id < MAX_LINK_PLAYERS; ++id)
            {
                if (id == playerMultiplayerId)
                {
                    switch (gLinkPlayers[id].id)
                    {
                    case 0:
                    case 3:
                        memcpy(gPlayerParty + 2, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                        break;
                    case 1:
                    case 2:
                        memcpy(gPlayerParty + 5, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                        break;
                    }
                }
                else
                {
                    if ((!(gLinkPlayers[id].id & 1) && !(gLinkPlayers[playerMultiplayerId].id & 1))
                     || ((gLinkPlayers[id].id & 1) && (gLinkPlayers[playerMultiplayerId].id & 1)))
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gPlayerParty + 2, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        case 1:
                        case 2:
                            memcpy(gPlayerParty + 5, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        }
                    }
                    else
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gEnemyParty + 2, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        case 1:
                        case 2:
                            memcpy(gEnemyParty + 5, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        }
                    }
                }
            } 
            TryCorrectShedinjaLanguage(&gPlayerParty[0]);
            TryCorrectShedinjaLanguage(&gPlayerParty[1]);
            TryCorrectShedinjaLanguage(&gPlayerParty[2]);
            TryCorrectShedinjaLanguage(&gPlayerParty[3]);
            TryCorrectShedinjaLanguage(&gPlayerParty[4]);
            TryCorrectShedinjaLanguage(&gPlayerParty[5]);
            TryCorrectShedinjaLanguage(&gEnemyParty[0]);
            TryCorrectShedinjaLanguage(&gEnemyParty[1]);
            TryCorrectShedinjaLanguage(&gEnemyParty[2]);
            TryCorrectShedinjaLanguage(&gEnemyParty[3]);
            TryCorrectShedinjaLanguage(&gEnemyParty[4]);
            TryCorrectShedinjaLanguage(&gEnemyParty[5]);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 11:
        InitBtlControllers();
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[SPRITES_INIT_STATE1] = 0;
        gBattleCommunication[SPRITES_INIT_STATE2] = 0;
        break;
    case 12:
        if (BattleInitAllSprites(&gBattleCommunication[SPRITES_INIT_STATE1], &gBattleCommunication[SPRITES_INIT_STATE2]))
        {
            gPreBattleCallback1 = gMain.callback1;
            gMain.callback1 = BattleMainCB1;
            SetMainCallback2(BattleMainCB2);
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
                gBattleTypeFlags |= BATTLE_TYPE_20;
        }
        break;
    case 5:
    case 9:
        ++gBattleCommunication[0];
        gBattleCommunication[SPRITES_INIT_STATE1] = 1;
        // fall through
    case 6:
    case 10:
        if (--gBattleCommunication[SPRITES_INIT_STATE1] == 0)
            ++gBattleCommunication[0];
        break;
    }
}

#define BATTLE_SPEED_UP
void BattleMainCB2(void) //make my setup test it stash it thentry hers for messages
{
    u8 speedScale = Rogue_GetBattleSpeedScale();

    //expirment with this later, but think I can get away with messing with
    //delays in battle_anim file if I have this
    //ok won't be including this in patch, for some resaon actually makes things longer
    //with things that have pauses?  intimidate has several longpauses //nvm i'm stupid I left 4x on -__-
     

    // If we are processing a palette fade we need to temporarily fall back to 1x speed otherwise there is graphical corruption
    if(PrevPaletteFadeResult() == PALETTE_FADE_STATUS_LOADING)
        speedScale = 1;


    //CONFIRMED its level up, not learn move  // should but glveleveupinbattle not working for me
    if (gBattleResults.caughtMonSpecies)    //WORKED!!
        speedScale = 1;

    


    if(speedScale <= 1)
    {
        // Maintain OG order for compat
        AnimateSprites();
        BuildOamBuffer();
        RunTextPrinters();
        UpdatePaletteFade();
        RunTasks();
    }
    else
    {
        u8 s;
        u8 fadeResult;

        // Update select entries at higher speed
        // disable speed up during palette fades otherwise we run into issues with blending 
        //(e.g. moves that change background like Psychic can get stuck or have their colours overflow)
        for(s = 1; s < speedScale; ++s)
        {
            AnimateSprites();
            RunTextPrinters();
            fadeResult = UpdatePaletteFade();

            if(fadeResult == PALETTE_FADE_STATUS_LOADING)
            {
                // minimal final update as we've just started a fade
                BuildOamBuffer();
                RunTasks();
                break;
            }
            else
            {
                RunTasks();
                VBlankCB_Battle();

                // Call it again to make sure everything is behaving as it should (this is crazy town now)
                if (gMain.callback1)
                    gMain.callback1();
            }
        }

        if(fadeResult != PALETTE_FADE_STATUS_LOADING) //believe final loop
        {
            // final update
            AnimateSprites();
            BuildOamBuffer();
            RunTextPrinters();
            UpdatePaletteFade();
            RunTasks();
        }
    }
    if (JOY_HELD(B_BUTTON) && gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        // Player pressed B during recorded battle playback, end battle
        gSpecialVar_Result = gBattleOutcome = B_OUTCOME_DREW;
        ResetPaletteFadeControl();
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        SetMainCallback2(CB2_QuitPokedudeBattle);
    }
}

void FreeRestoreBattleData(void)
{
    gMain.callback1 = gPreBattleCallback1;
    gScanlineEffect.state = 3;
    gMain.inBattle = FALSE;
    ZeroEnemyPartyMons();
    m4aSongNumStop(SE_LOW_HEALTH);
    FreeMonSpritesGfx();
    FreeBattleSpritesData();
    FreeBattleResources();
}

void CB2_QuitRecordedBattle(void)
{
    UpdatePaletteFade();
    if (!gPaletteFade.active)
    {
        m4aMPlayStop(&gMPlayInfo_SE1);
        m4aMPlayStop(&gMPlayInfo_SE2);
        if (gTestRunnerEnabled)
            TestRunner_Battle_AfterLastTurn();
        FreeRestoreBattleData();
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void CB2_QuitPokedudeBattle(void)
{
    UpdatePaletteFade();
    if (!gPaletteFade.active)
    {
        FreeRestoreBattleData();
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

/*static void SpriteCB_UnusedDebugSprite(struct Sprite *sprite)
{
    sprite->data[0] = 0;
    sprite->callback = SpriteCB_UnusedDebugSprite_Step;
}

static void SpriteCB_UnusedDebugSprite_Step(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sUnknownDebugSpriteDataBuffer = AllocZeroed(0x1000);
        ++sprite->data[0];
        sprite->data[1] = 0;
        sprite->data[2] = 0x281;
        sprite->data[3] = 0;
        sprite->data[4] = 1;
        // fall through
    case 1:
        if (--sprite->data[4] == 0)
        {
            s32 i, r2, r0;

            sprite->data[4] = 2;
            r2 = sprite->data[1] + sprite->data[3] * 32;
            r0 = sprite->data[2] - sprite->data[3] * 32;
            for (i = 0; i <= 29; i += 2)
            {
                *(&sUnknownDebugSpriteDataBuffer[r2] + i) = 0x3D;
                *(&sUnknownDebugSpriteDataBuffer[r0] + i) = 0x3D;
            }
            if (++sprite->data[3] == 21)
            {
                ++sprite->data[0];
                sprite->data[1] = 32;
            }
        }
        break;
    case 2:
        if (--sprite->data[1] == 20)
        {
            if (sUnknownDebugSpriteDataBuffer != NULL)
            {
                memset(sUnknownDebugSpriteDataBuffer, 0, 0x1000);
                FREE_AND_SET_NULL(sUnknownDebugSpriteDataBuffer);
            }
            SetMainCallback2(CB2_InitBattle);
        }
        break;
    }
}*/

bool8 IsRivalBattle(u16 trainerNum)
{
    u8 trainerClass = gTrainers[trainerNum].trainerClass;
    if (trainerClass == CLASS_RIVAL || trainerClass == CLASS_RIVAL_2 || trainerClass == CLASS_CHAMPION_2)
        return TRUE;
    else
        return FALSE;
}

#define TRAINER_PARTY_DATA
static u8 CreateNPCTrainerParty(struct Pokemon *party, u16 trainerNum)
{
    u32 nameHash = 0; //check other function that sets abilitysot for wilds may not need that randomability value vsonic
    u8 RandomAbility;    //to put in setmondata dataarg to hopefully set random ability slot 0-3
    u32 personalityValue; //personality now uses name hash, which is trainer name
    u8 fixedIV; //figure how to set personality for individual pokemon, or at least set their ability
    u8 abilityNum;  //should let set ability slot for mon
    u16 totalEVs = 0;
    u16 evs[NUM_EV_STATS];
    u16 species,targetSpecies;
    s32 i, j;
    int l = 0;
    u16 Global_Stat_Total_Limit;

    if (trainerNum == TRAINER_SECRET_BASE)
        return 0;
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
     && !(gBattleTypeFlags & (BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_TRAINER_TOWER)))
    {
        ZeroEnemyPartyMons();//would need put logic for filtering party size directly below this
        for (i = 0; i < gTrainers[trainerNum].partySize; ++i)   //uses i, to loop through trainers entir party 
        {//vsonic

            if (gTrainers[trainerNum].battleType == BATTLE_TYPE_DOUBLE) //may need change to just not singles, since adding more?
                personalityValue = 0x80;
            else if (gTrainers[trainerNum].encounterMusic_gender & 0x80) //specific value for male/female trainers to set party mon gender
                personalityValue = 0x78;
            else
                personalityValue = 0x88;
            for (j = 0; gTrainers[trainerNum].trainerName[j] != EOS; ++j)
                nameHash += gTrainers[trainerNum].trainerName[j];
            switch (gTrainers[trainerNum].partyFlags)
            {
            case 0: //evolution works, only issue is if you give the rival multiple instances of the same starter line, with the evolved form first
                //because their both using the same var, it just eliminated the unevolved version of the pokemon if it comes after the evolved form.
            {
                const struct TrainerMonNoItemDefaultMoves *partyData = gTrainers[trainerNum].party.NoItemDefaultMoves;
                if (IsRivalBattle(trainerNum)) // && i == gTrainers[trainerNum].partySize - 1) //probably go back & make a nested function based on the species
                    //of the starter in trainer_parties, it may need to be constant so instead of a variable I'll use a define like weather_hail but for starter 
                    //to set teh species checks it'll be partyData[i].species == StarterEvo_0  up to StarterEvo_2 for last evolution
                    //if species can't evolve target species will be species
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter, to species
                        VarSet(VAR_RIVAL_EVO, 0);   //gaurantees values are different, as species will never be none\ to prime evolution condition
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            if (VarGet(VAR_RIVAL_STARTER) == SPECIES_EEVEE) //prevent multi trigger as rival starter is updated after function/evolution 
                                targetSpecies = RivalEeveelutionForPlayerStarter(); //as eevee is a one stage evolution, only needs this addition default logic will ensure it persists
                            else
                                targetSpecies = evolutions[l].targetSpecies; //replace target species value if eevee starter here with "RivalEeveelutionForPlayerStarter"
                            
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                            }
                                                        
                        }
                        else
                            species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                        //check first evo 
                        //if evolution branches preferrably pick the one with type advantage to player starter,
                        //to do this realize I need another var to hold player starter, and use basestates type (playervar) to check its type
                        //to help ai pick evolution     actually only eevee has branch evo

                        //in that case make it based on partydatea.species if its charizard be flareon, if venusaur lefeon or jolteon
                        //and vaporeon if blastoise check what mon I put in lists again I may make the eeveelutions have 2 options per starter group
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            targetSpecies = evolutions[l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                                VarSet(VAR_RIVAL_EVO, 0);
                                
                            }
                            
                        }  //check 2nd/final evo
                        else
                            species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                    }
                   else// for mon in party other than starter
                        species = partyData[i].species;
                }// for non rival battles
                else
                    species = partyData[i].species;

                for (j = 0; gBaseStats[species].speciesName[j] != EOS; ++j) //starting from 0, loops through all the species names until it matches for each slot in party
                    nameHash += gBaseStats[species].speciesName[j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;   //I think actually is Ivs, uses weird logic to make fixed iv, think will set to random
                //but if I set it to random, but refight trainers, does it keep the iv distribution or generate a new one..?
                //I'm gonna guess it regenerates, based on how the roamers are handled, where it specifically saves all their data
                //ok setting random but attempt to treat rival starter like roamer so it keeps iv distribution
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)
                    fixedIV = USE_RANDOM_IVS; //for early game balance may lower brocks party ivs to use random value
                
                //as ability and ev are not part of CreateMon arguments may need to put these two below createmon function to have them take effect. hm,
                //checked against custom move set  and move assignment logic is BELOW createmon so that confirms I need to move createmon up to here.
                //double checked again, and Ivs and Evs need to go BEFORE cretemon as function uses those to do calcstats
                //so for now will leave these where they are I "think" it will work. or just move ability data to below function...
                /*//Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs               
                //ok so evs aren't random set they are user set, good.
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);
                    Global_Stat_Total_Limit = GetBaseStatTotal(partyData[i].species) < 600 ? 600 : 650; //sets limit based on bst
                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);
                RandomAbility = Random() % 4;
                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility); //for some reason only worked with u8??
                else                                                              
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);
                break; //&party[i] checks mon slot.   next one checks species for that slot
            }
            case F_TRAINER_PARTY_CUSTOM_MOVESET: //could probably get custom moves working with same trick as above but going to a different array
            { //but that can probably better be solved by getting my smart learnsets up and running
                const struct TrainerMonNoItemCustomMoves *partyData = gTrainers[trainerNum].party.NoItemCustomMoves;
                if (IsRivalBattle(trainerNum))
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter, to species
                        VarSet(VAR_RIVAL_EVO, 0);   //gaurantees values are different, as species will never be none\ to prime evolution condition
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            if (VarGet(VAR_RIVAL_STARTER) == SPECIES_EEVEE) //prevent multi trigger as rival starter is updated after function/evolution 
                                targetSpecies = RivalEeveelutionForPlayerStarter(); //as eevee is a one stage evolution, only needs this addition default logic will ensure it persists
                            else
                                targetSpecies = evolutions[l].targetSpecies; //replace target species value if eevee starter here with "RivalEeveelutionForPlayerStarter"
                            
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        //if evolution branches preferrably pick the one with type advantage to player starter,
                        //to do this realize I need another var to hold player starter, and use basestates type (playervar) to check its type
                        //to help ai pick evolution     actually only eevee has branch evo

                        //in that case make it based on partydatea.species if its charizard be flareon, if venusaur lefeon or jolteon
                        //and vaporeon if blastoise check what mon I put in lists again I may make the eeveelutions have 2 options per starter group
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            targetSpecies = evolutions[l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                                VarSet(VAR_RIVAL_EVO, 0);
                                
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd/final evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else// for mon in party other than starter
                        species = partyData[i].species;
                }
                else// for non rival battles
                    species = partyData[i].species;

                for (j = 0; gBaseStats[species].speciesName[j] != EOS; ++j)
                    nameHash += gBaseStats[species].speciesName[j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)
                    fixedIV = USE_RANDOM_IVS;
                
               /* //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);
                    Global_Stat_Total_Limit = GetBaseStatTotal(partyData[i].species) < 600 ? 600 : 650; //sets limit based on bst

                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);
                RandomAbility = Random() % 4;
                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility);
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);

                for (j = 0; j < MAX_MON_MOVES; ++j) //max moves is 4, .moves field is size 4, so loop is to loop through all possible moves
                {
                    SetMonData(&party[i], MON_DATA_MOVE1 + j, &partyData[i].moves[j]); //actually I need custom moves, otherwise its not a good base
                    SetMonData(&party[i], MON_DATA_PP1 + j, &gBattleMoves[partyData[i].moves[j]].pp); //so I need a way to change how this works

                    if (partyData[i].moves[0] == MOVE_NONE) //hopefully this'll do what I want. set to default moves, if mon has none set
                        GiveMonInitialMoveset(&party[i]);
                }
                break; //like custom moves for some, but if its blank just give them default moves.  I think it defaults to 0, if nothing is there.
                //so making it break if move is move_none should let it default to normal learnset.?

                //note, to change battle type, i.e custom moves no item, etc. need to change trainer.h & trainer_parties.h files
            }
            case F_TRAINER_PARTY_HELD_ITEM: //make choose ai flags for individual pokemon, instead of party/trainer
            { //also add pp bonus setting to custom moves,for more strategy/control //important
                const struct TrainerMonItemDefaultMoves *partyData = gTrainers[trainerNum].party.ItemDefaultMoves;
                if (IsRivalBattle(trainerNum))
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter, to species
                        VarSet(VAR_RIVAL_EVO, 0);   //gaurantees values are different, as species will never be none\ to prime evolution condition
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            if (VarGet(VAR_RIVAL_STARTER) == SPECIES_EEVEE) //prevent multi trigger as rival starter is updated after function/evolution 
                                targetSpecies = RivalEeveelutionForPlayerStarter(); //as eevee is a one stage evolution, only needs this addition default logic will ensure it persists
                            else
                                targetSpecies = evolutions[l].targetSpecies; //replace target species value if eevee starter here with "RivalEeveelutionForPlayerStarter"
                            
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        //if evolution branches preferrably pick the one with type advantage to player starter,
                        //to do this realize I need another var to hold player starter, and use basestates type (playervar) to check its type
                        //to help ai pick evolution     actually only eevee has branch evo

                        //in that case make it based on partydatea.species if its charizard be flareon, if venusaur lefeon or jolteon
                        //and vaporeon if blastoise check what mon I put in lists again I may make the eeveelutions have 2 options per starter group
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            targetSpecies = evolutions[l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                                VarSet(VAR_RIVAL_EVO, 0);
                                
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd/final evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else// for mon in party other than starter
                        species = partyData[i].species;
                }
                else// for non rival battles
                    species = partyData[i].species;

                for (j = 0; gBaseStats[species].speciesName[j] != EOS; ++j)
                    nameHash += gBaseStats[species].speciesName[j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)
                    fixedIV = USE_RANDOM_IVS;
                
                /*//Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);
                    Global_Stat_Total_Limit = GetBaseStatTotal(partyData[i].species) < 600 ? 600 : 650; //sets limit based on bst

                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);
                RandomAbility = Random() % 4;
                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility);
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);

                SetMonData(&party[i], MON_DATA_HELD_ITEM, &partyData[i].heldItem);
                break;
            }
            case F_TRAINER_PARTY_CUSTOM_MOVESET | F_TRAINER_PARTY_HELD_ITEM:
            {
                const struct TrainerMonItemCustomMoves *partyData = gTrainers[trainerNum].party.ItemCustomMoves;
                if (IsRivalBattle(trainerNum))
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter, to species
                        VarSet(VAR_RIVAL_EVO, 0);   //gaurantees values are different, as species will never be none\ to prime evolution condition
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            if (VarGet(VAR_RIVAL_STARTER) == SPECIES_EEVEE) //prevent multi trigger as rival starter is updated after function/evolution 
                                targetSpecies = RivalEeveelutionForPlayerStarter(); //as eevee is a one stage evolution, only needs this addition default logic will ensure it persists
                            else
                                targetSpecies = evolutions[l].targetSpecies; //replace target species value if eevee starter here with "RivalEeveelutionForPlayerStarter"
                            
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        //if evolution branches preferrably pick the one with type advantage to player starter,
                        //to do this realize I need another var to hold player starter, and use basestates type (playervar) to check its type
                        //to help ai pick evolution     actually only eevee has branch evo

                        //in that case make it based on partydatea.species if its charizard be flareon, if venusaur lefeon or jolteon
                        //and vaporeon if blastoise check what mon I put in lists again I may make the eeveelutions have 2 options per starter group
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            const struct Evolution *evolutions = GetSpeciesEvolutions(VarGet(VAR_RIVAL_STARTER));

                            targetSpecies = evolutions[l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                                species = VarGet(VAR_RIVAL_EVO);  //Set dynamic starter, to species
                                VarSet(VAR_RIVAL_EVO, 0);
                                
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd/final evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else// for mon in party other than starter
                        species = partyData[i].species;
                }
                else// for non rival mon
                    species = partyData[i].species;

                for (j = 0; gBaseStats[species].speciesName[j] != EOS; ++j)
                    nameHash += gBaseStats[species].speciesName[j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)    //for new game plus do flag check and set fixed ivs to max per stat, would require you ev train 
                    fixedIV = USE_RANDOM_IVS;   //mon instead of needing perfect ivs, and ideally you should alraedy have trained mon, and easy access to fast training items.

                /*//Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum != 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1)); //random ability setting odds already handled in other function
                               //so all I need here is, if num mot 0  set
                    */

                //Set Evs
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);
                    Global_Stat_Total_Limit = GetBaseStatTotal(partyData[i].species) < 600 ? 600 : 650; //sets limit based on bst
                    
                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit

                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if ((GetBaseStatTotal(partyData[i].species) + (totalEVs / 4)) >= Global_Stat_Total_Limit)
                            break;

                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) >= GLOBAL_PER_STAT_LIMIT)
                            break;
                        

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }


                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        //actually do need a break
                        //but put this line below the else if to adjust stat gain
                        if ((GetIndividualBaseStatValue(partyData[i].species, j) + (evs[j] / 4)) > GLOBAL_PER_STAT_LIMIT)
                        {
                            evs[j] = max((GLOBAL_PER_STAT_LIMIT - (GetIndividualBaseStatValue(partyData[i].species, j))), 0) * 4;
                        } //wrote out formuola works, should assign to fit limit
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }//had to readjust order, as ev set had to go before CreateMon, for Evs to be applied, now matches order of struct as well
                //iv ev lvl species Helditem moves
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);
                SetMonData(&party[i], MON_DATA_HELD_ITEM, &partyData[i].heldItem);
                RandomAbility = Random() % 4;
                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility);
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);

                for (j = 0; j < MAX_MON_MOVES; ++j)
                {
                    SetMonData(&party[i], MON_DATA_MOVE1 + j, &partyData[i].moves[j]);
                    SetMonData(&party[i], MON_DATA_PP1 + j, &gBattleMoves[partyData[i].moves[j]].pp);

                    if (partyData[i].moves[0] == MOVE_NONE) //hopefully this'll do what I want. set to default moves, if mon has none set
                        GiveMonInitialMoveset(&party[i]);   //it works!!
                }//works but had to change, to only if moveslot 1 is no move, otherwise it replaced custom setting that has slots set to move_none
            }
            break;
            }   //end of switch case
        }//end of i
       gBattleTypeFlags |= gTrainers[trainerNum].battleType;
    }
    return gTrainers[trainerNum].partySize;
}

// not used
UNUSED static void unused_80116CC(void)
{
    if (REG_VCOUNT < 0xA0 && REG_VCOUNT >= 0x6F)
        REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(24) | BGCNT_16COLOR | BGCNT_TXT256x512;
}

void VBlankCB_Battle(void)
{
    // Change gRngSeed every vblank.
    Random();
    SetGpuReg(REG_OFFSET_BG0HOFS, gBattle_BG0_X);
    SetGpuReg(REG_OFFSET_BG0VOFS, gBattle_BG0_Y);
    SetGpuReg(REG_OFFSET_BG1HOFS, gBattle_BG1_X);
    SetGpuReg(REG_OFFSET_BG1VOFS, gBattle_BG1_Y);
    SetGpuReg(REG_OFFSET_BG2HOFS, gBattle_BG2_X);
    SetGpuReg(REG_OFFSET_BG2VOFS, gBattle_BG2_Y);
    SetGpuReg(REG_OFFSET_BG3HOFS, gBattle_BG3_X);
    SetGpuReg(REG_OFFSET_BG3VOFS, gBattle_BG3_Y);
    SetGpuReg(REG_OFFSET_WIN0H, gBattle_WIN0H);
    SetGpuReg(REG_OFFSET_WIN0V, gBattle_WIN0V);
    SetGpuReg(REG_OFFSET_WIN1H, gBattle_WIN1H);
    SetGpuReg(REG_OFFSET_WIN1V, gBattle_WIN1V);
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ScanlineEffect_InitHBlankDmaTransfer();
}

void SpriteCB_VsLetterDummy(struct Sprite *sprite)
{
}

static void SpriteCB_VsLetter(struct Sprite *sprite)
{
    if (sprite->data[0] != 0)
        sprite->pos1.x = sprite->data[1] + ((sprite->data[2] & 0xFF00) >> 8);
    else
        sprite->pos1.x = sprite->data[1] - ((sprite->data[2] & 0xFF00) >> 8);
    sprite->data[2] += 0x180;
    if (sprite->affineAnimEnded)
    {
        FreeSpriteTilesByTag(ANIM_SPRITES_START);
        FreeSpritePaletteByTag(ANIM_SPRITES_START);
        FreeSpriteOamMatrix(sprite);
        DestroySprite(sprite);
    }
}

void SpriteCB_VsLetterInit(struct Sprite *sprite)
{
    StartSpriteAffineAnim(sprite, 1);
    sprite->callback = SpriteCB_VsLetter;
    PlaySE(SE_MUGSHOT);
}

static void BufferPartyVsScreenHealth_AtEnd(u8 taskId)
{
    struct Pokemon *party1 = NULL;
    struct Pokemon *party2 = NULL;
    u8 multiplayerId = gBattleStruct->multiplayerId;
    u32 r7;
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        switch (gLinkPlayers[multiplayerId].id)
        {
        case 0:
        case 2:
            party1 = gPlayerParty;
            party2 = gEnemyParty;
            break;
        case 1:
        case 3:
            party1 = gEnemyParty;
            party2 = gPlayerParty;
            break;
        }
    }
    else
    {
        party1 = gPlayerParty;
        party2 = gEnemyParty;
    }
    r7 = 0;
    BUFFER_PARTY_VS_SCREEN_STATUS(party1, r7, i);
    gTasks[taskId].data[3] = r7;
    r7 = 0;
    BUFFER_PARTY_VS_SCREEN_STATUS(party2, r7, i);
    gTasks[taskId].data[4] = r7;
}

void CB2_InitEndLinkBattle(void)
{
    s32 i;
    u8 taskId;

    SetHBlankCallback(NULL);
    SetVBlankCallback(NULL);
    CpuFill32(0, (void *)VRAM, VRAM_SIZE);
    SetGpuReg(REG_OFFSET_MOSAIC, 0);
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0, 0xF0));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(0x50, 0x51));
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    gBattle_WIN0H = WIN_RANGE(0, 0xF0);
    gBattle_WIN0V = WIN_RANGE(0x50, 0x51);
    ScanlineEffect_Clear();
    for (i = 0; i < 80; ++i)
        return; //why did I add this again? //was part of expansion worked previously
    {
        gScanlineEffectRegBuffers[0][i] = 0xF0;
        gScanlineEffectRegBuffers[1][i] = 0xF0;
    }

    for (; i < 160; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = 0xFF10;
        gScanlineEffectRegBuffers[1][i] = 0xFF10;
    }
    ResetPaletteFade();
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
    gBattle_BG2_X = 0;
    gBattle_BG2_Y = 0;
    gBattle_BG3_X = 0;
    gBattle_BG3_Y = 0;
    InitBattleBgsVideo();
    LoadCompressedPalette(gBattleInterface_Textbox_Pal, 0, 64);
    LoadBattleMenuWindowGfx();
    ResetSpriteData();
    ResetTasks();
    DrawBattleEntryBackground();
    SetGpuReg(REG_OFFSET_WINOUT, WININ_WIN0_BG0 | WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = 4;
    SetVBlankCallback(VBlankCB_Battle);
    taskId = CreateTask(InitLinkBattleVsScreen, 0);
    gTasks[taskId].data[1] = 270;
    gTasks[taskId].data[2] = 90;
    gTasks[taskId].data[5] = 1;
    BufferPartyVsScreenHealth_AtEnd(taskId);
    SetMainCallback2(CB2_EndLinkBattle);
    gBattleCommunication[MULTIUSE_STATE] = 0;
}

static void CB2_EndLinkBattle(void) 
{
    return; //possible brock issue? //no part of expansion remove link battles
    EndLinkBattleInSteps();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    RunTasks();
}

static void EndLinkBattleInSteps(void)
{
    s32 i;

    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        gBattleCommunication[1] = 0xFF;
        ++gBattleCommunication[MULTIUSE_STATE];
        break;
    case 1:
        if (--gBattleCommunication[1] == 0)
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            SetMainCallback2(gMain.savedCallback);
          //  TrySetQuestLogLinkBattleEvent();
            FreeMonSpritesGfx();
            FreeBattleSpritesData();
            FreeBattleResources();
        }
        break;
    }
}

u32 GetBattleBgAttribute(u8 arrayId, u8 caseId)
{
    u32 ret = 0;

    switch (caseId)
    {
    case 0:
        ret = gBattleBgTemplates[arrayId].bg;
        break;
    case 1:
        ret = gBattleBgTemplates[arrayId].charBaseIndex;
        break;
    case 2:
        ret = gBattleBgTemplates[arrayId].mapBaseIndex;
        break;
    case 3:
        ret = gBattleBgTemplates[arrayId].screenSize;
        break;
    case 4:
        ret = gBattleBgTemplates[arrayId].paletteMode;
        break;
    case 5:
        ret = gBattleBgTemplates[arrayId].priority;
        break;
    case 6:
        ret = gBattleBgTemplates[arrayId].baseTile;
        break;
    }
    return ret;
}

static void TryCorrectShedinjaLanguage(struct Pokemon *mon)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 language = LANGUAGE_JAPANESE;

    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_SHEDINJA
     && GetMonData(mon, MON_DATA_LANGUAGE) != language)
    {
        GetMonData(mon, MON_DATA_NICKNAME, nickname);
        if (StringCompareWithoutExtCtrlCodes(nickname, sText_ShedinjaJpnName) == 0)
            SetMonData(mon, MON_DATA_LANGUAGE, &language);
    }
}//japanese doesn't have different cases/upper/lower so no need to change here

#define sBattler            data[0]
#define sSpeciesId          data[2]

void SpriteCB_EnemyMon(struct Sprite *sprite)
{
    sprite->callback = SpriteCB_MoveWildMonToRight;
    StartSpriteAnimIfDifferent(sprite, 0);
    BeginNormalPaletteFade(0x20000, 0, 10, 10, RGB(8, 8, 8));
}

static void SpriteCB_MoveWildMonToRight(struct Sprite *sprite)
{
    if ((gIntroSlideFlags & 1) == 0)
    {
        sprite->pos2.x += 2;
        if (sprite->pos2.x == 0)
        {
            sprite->callback = SpriteCB_WildMonShowHealthbox;
            PlayCry_Normal(sprite->data[2], 25);
        }
    }
}

static void SpriteCB_WildMonShowHealthbox(struct Sprite *sprite)
{
    if (sprite->animEnded)
    {
        StartHealthboxSlideIn(sprite->sBattler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[sprite->sBattler]);
        sprite->callback = SpriteCallbackDummy2;
        StartSpriteAnimIfDifferent(sprite, 0);
        BeginNormalPaletteFade(0x20000, 0, 10, 0, RGB(8, 8, 8));
    }
}

void SpriteCallbackDummy2(struct Sprite *sprite)
{
}

// not used
/*UNUSED static void SpriteCB_Unused_8011E28(struct Sprite *sprite)
{
    sprite->data[3] = 6;
    sprite->data[4] = 1;
    sprite->callback = SpriteCB_Unused_8011E28_Step;
}

// not used
static void SpriteCB_Unused_8011E28_Step(struct Sprite *sprite)
{
    --sprite->data[4];
    if (sprite->data[4] == 0)
    {
        sprite->data[4] = 8;
        sprite->invisible ^= 1;
        --sprite->data[3];
        if (sprite->data[3] == 0)
        {
            sprite->invisible = FALSE;
            sprite->callback = SpriteCallbackDummy2;
            gUnknown_2022AE8[0] = 0;
        }
    }
}*/

void SpriteCB_FaintOpponentMon(struct Sprite *sprite)
{
    u8 battler = sprite->sBattler;
    u16 species;
    u8 yOffset;

    if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies != 0)
        species = gBattleSpritesDataPtr->battlerData[battler].transformSpecies;
    else
        species = sprite->sSpeciesId;
    GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_PERSONALITY);  // Unused return value.

    //...why did I rove this for unown? need keep actually since unown works diff than how I thought
    //its fine new function accounts for unown
    /*if (species == SPECIES_UNOWN)
    {
        u32 personalityValue = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_PERSONALITY);
        u16 unownForm = ((((personalityValue & 0x3000000) >> 18) | ((personalityValue & 0x30000) >> 12) | ((personalityValue & 0x300) >> 6) | (personalityValue & 3)) % 0x1C);
        u16 unownSpecies;

        if (unownForm == 0)
            unownSpecies = SPECIES_UNOWN;  // Use the A Unown form.
        else
            unownSpecies = NUM_SPECIES + unownForm;  // Use one of the other Unown letters.
        yOffset = gMonFrontPicCoords[unownSpecies].y_offset;
    }
    else if (species == SPECIES_CASTFORM)
    {
        yOffset = gCastformFrontSpriteCoords[gBattleMonForms[battler]].y_offset;
    }
    else if (species > NUM_SPECIES)
    {
        yOffset = gMonFrontPicCoords[SPECIES_NONE].y_offset; //again capitalization matters. mime broke because it wasn't Mime
    } //                                           
    else
    {
        yOffset = gMonFrontPicCoords[species].y_offset;
    }*/
    yOffset = GetBattlerYDelta(battler, species);

    sprite->data[3] = 8 - yOffset / 8;
    sprite->data[4] = 1;
    sprite->callback = SpriteCB_AnimFaintOpponent;
}

static void SpriteCB_AnimFaintOpponent(struct Sprite *sprite)
{
    s32 i;

    if (--sprite->data[4] == 0)
    {
        sprite->data[4] = 2;
        sprite->pos2.y += 8; // Move the sprite down.
        if (--sprite->data[3] < 0)
        {
            FreeSpriteOamMatrix(sprite);
            DestroySprite(sprite);
        }
        else // Erase bottom part of the sprite to create a smooth illusion of mon falling down.
        {
            u8 *dst = (u8 *)gMonSpritesGfxPtr->sprites[GetBattlerPosition(sprite->sBattler)] + (gBattleMonForms[sprite->sBattler] << 11) + (sprite->data[3] << 8);

            for (i = 0; i < 0x100; ++i)
                *(dst++) = 0;
            StartSpriteAnim(sprite, gBattleMonForms[sprite->sBattler]);
        }
    }
}

void SpriteCb_ShowAsMoveTarget(struct Sprite *sprite)
{
    sprite->data[3] = 8;
    sprite->data[4] = sprite->invisible;
    sprite->callback = SpriteCb_BlinkVisible;
}

static void SpriteCb_BlinkVisible(struct Sprite *sprite)
{
    --sprite->data[3];
    if (sprite->data[3] == 0)
    {
        sprite->invisible ^= 1;
        sprite->data[3] = 8;
    }
}

void SpriteCb_HideAsMoveTarget(struct Sprite *sprite)
{
    sprite->invisible = sprite->data[4];
    sprite->data[4] = FALSE;
    sprite->callback = SpriteCallbackDummy2;
}

void SpriteCB_AllyMon(struct Sprite *sprite)
{
    sprite->callback = oac_poke_ally_;
}

static void oac_poke_ally_(struct Sprite *sprite)
{
    if (!(gIntroSlideFlags & 1))
    {
        sprite->pos2.x -= 2;
        if (sprite->pos2.x == 0)
        {
            sprite->callback = SpriteCallbackDummy3;
            sprite->data[1] = 0;
        }
    }
}

void SpriteCB_SetToDummy3(struct Sprite *sprite)
{
    sprite->callback = SpriteCallbackDummy3;
}

static void SpriteCallbackDummy3(struct Sprite *sprite)
{
}

void SpriteCB_FaintSlideAnim(struct Sprite *sprite)
{
    if (!(gIntroSlideFlags & 1))
    {
        sprite->pos2.x += sprite->data[1];
        sprite->pos2.y += sprite->data[2];
    }
}

#define sSinIndex           data[0]
#define sDelta              data[1]
#define sAmplitude          data[2]
#define sBouncerSpriteId    data[3]
#define sWhich              data[4]

void DoBounceEffect(u8 battler, u8 which, s8 delta, s8 amplitude)
{
    u8 invisibleSpriteId;
    u8 bouncerSpriteId;

    switch (which)
    {
    case BOUNCE_HEALTHBOX:
    default:
        if (gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing)
            return;
        break;
    case BOUNCE_MON:
        if (gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing)
            return;
        break;
    }
    invisibleSpriteId = CreateInvisibleSpriteWithCallback(SpriteCB_BounceEffect);
    if (which == BOUNCE_HEALTHBOX)
    {
        bouncerSpriteId = gHealthboxSpriteIds[battler];
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxBounceSpriteId = invisibleSpriteId;
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing = 1;
        gSprites[invisibleSpriteId].sSinIndex = 128; // 0
    }
    else
    {
        bouncerSpriteId = gBattlerSpriteIds[battler];
        gBattleSpritesDataPtr->healthBoxesData[battler].battlerBounceSpriteId = invisibleSpriteId;
        gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing = 1;
        gSprites[invisibleSpriteId].sSinIndex = 192; // -1
    }
    gSprites[invisibleSpriteId].sDelta = delta;
    gSprites[invisibleSpriteId].sAmplitude = amplitude;
    gSprites[invisibleSpriteId].sBouncerSpriteId = bouncerSpriteId;
    gSprites[invisibleSpriteId].sWhich = which;
    gSprites[bouncerSpriteId].pos2.x = 0;
    gSprites[bouncerSpriteId].pos2.y = 0;
}

void EndBounceEffect(u8 battler, u8 which)
{
    u8 bouncerSpriteId;

    if (which == BOUNCE_HEALTHBOX)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing)
            return;

        bouncerSpriteId = gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].healthboxBounceSpriteId].sBouncerSpriteId;
        DestroySprite(&gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].healthboxBounceSpriteId]);
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing = 0;
    }
    else
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing)
            return;

        bouncerSpriteId = gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].battlerBounceSpriteId].sBouncerSpriteId;
        DestroySprite(&gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].battlerBounceSpriteId]);
        gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing = 0;
    }
    gSprites[bouncerSpriteId].pos2.x = 0;
    gSprites[bouncerSpriteId].pos2.y = 0;
}

static void SpriteCB_BounceEffect(struct Sprite *sprite)
{
    u8 bouncerSpriteId = sprite->sBouncerSpriteId;
    s32 index;

    if (sprite->sWhich == BOUNCE_HEALTHBOX)
        index = sprite->sSinIndex;
    else
        index = sprite->sSinIndex;
    gSprites[bouncerSpriteId].pos2.y = Sin(index, sprite->sAmplitude) + sprite->sAmplitude;
    sprite->sSinIndex = (sprite->sSinIndex + sprite->sDelta) & 0xFF;
}

void SpriteCB_PlayerThrowInit(struct Sprite *sprite)
{
    StartSpriteAnim(sprite, 1);
    sprite->callback = SpriteCB_PlayerThrowUpdate;
}

void UpdatePlayerPosInThrowAnim(struct Sprite *sprite)
{
    if (sprite->animDelayCounter == 0)
        sprite->centerToCornerVecX = sPlayerThrowXTranslation[sprite->animCmdIndex];
}

static void SpriteCB_PlayerThrowUpdate(struct Sprite *sprite)
{
    UpdatePlayerPosInThrowAnim(sprite);
    if (sprite->animEnded)
        sprite->callback = SpriteCallbackDummy3;
}

void BattleDummy(void)
{
}

void BeginBattleIntro(void)
{
    BattleStartClearSetData();
    gBattleCommunication[1] = 0;
    gBattleMainFunc = BattleIntroGetMonsData;
}

//for speedup 
//since don't understand will have to take exactly as is
bool8 InBattleChoosingMoves() //base function didn't have void don't understand
{
    return gBattleMainFunc == HandleTurnActionSelectionState;
}

bool8 InBattleRunningActions() //just used for battle scene off w speed up
{
    return gBattleMainFunc == RunTurnActionsFunctions;
}

static void BattleMainCB1(void)
{
    gBattleMainFunc();
    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        gBattlerControllerFuncs[gActiveBattler]();
}

static void BattleStartClearSetData(void)
{
    s32 i;

    TurnValuesCleanUp(FALSE);
    SpecialStatusesClear();

    memset(&gDisableStructs, 0, sizeof(gDisableStructs)); 
    memset(&gFieldTimers, 0, sizeof(gFieldTimers));
    memset(&gSideStatuses, 0, sizeof(gSideStatuses));
    memset(&gSideTimers, 0, sizeof(gSideTimers));
    memset(&gWishFutureKnock, 0, sizeof(gWishFutureKnock));
    memset(&gBattleResults, 0, sizeof(gBattleResults));

    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
    {
        gStatuses3[i] = 0;
        gStatuses4[i] = 0;
        gDisableStructs[i].isFirstTurn = 2; //beelieve is switching in? based on emerald comment    //vsonic
        gUnknown_2023DD4[i] = 0;
        gLastMoves[i] = MOVE_NONE;
        gLastLandedMoves[i] = MOVE_NONE;
        gLastHitByType[i] = 0;
        gLastResultingMoves[i] = MOVE_NONE;
        gLastHitBy[i] = 0xFF;
        gLockedMoves[i] = MOVE_NONE;
        gLastPrintedMoves[i] = MOVE_NONE;
        gBattleResources->flags->flags[i] = 0;
        gBattleStruct->lastTakenMove[i] = MOVE_NONE;
        gBattleStruct->choicedMove[i] = MOVE_NONE;
        gBattleStruct->changedItems[i] = 0;
        gBattleStruct->lastTakenMoveFrom[i][0] = MOVE_NONE;
        gBattleStruct->lastTakenMoveFrom[i][1] = MOVE_NONE;
        gBattleStruct->lastTakenMoveFrom[i][2] = MOVE_NONE;
        gBattleStruct->lastTakenMoveFrom[i][3] = MOVE_NONE;
        gBattleStruct->AI_monToSwitchIntoId[i] = PARTY_SIZE;
        gBattleStruct->skyDropTargets[i] = 0xFF;
        gBattleStruct->overwrittenAbilities[i] = ABILITY_NONE;
        // Record HP of each battler
        gBattleStruct->hpBefore[i] = gBattleMons[i].hp;
    }

    gLastUsedMove = 0;
    gFieldStatuses = 0;

    gHasFetchedBall = FALSE;
    gLastUsedBall = 0;

    gBattlerAttacker = 0;
    gBattlerTarget = 0;
    gBattleWeather = 0;
    gHitMarker = 0;

    if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_POKEDUDE)) && gSaveBlock2Ptr->optionsBattleSceneOff)
        gHitMarker |= HITMARKER_NO_ANIMATIONS;
    
    gBattleScripting.battleStyle = gSaveBlock2Ptr->optionsBattleStyle;
    gMultiHitCounter = 0;
    gMultiTask = 0;
    gBattleScripting.savedDmg = 0;
    gBattleOutcome = 0;
    gBattleControllerExecFlags = 0;
    gPaydayMoney = 0;
    gBattleResources->battleScriptsStack->size = 0;
    gBattleResources->battleCallbackStack->size = 0;
    for (i = 0; i < BATTLE_COMMUNICATION_ENTRIES_COUNT; ++i)
        gBattleCommunication[i] = 0;

    gPauseCounterBattle = 0;
    gBattleMoveDamage = 0;
    gIntroSlideFlags = 0;
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gLeveledUpInBattle = 0;
    gAbsentBattlerFlags = 0;
    gBattleStruct->runTries = 0;
    gBattleStruct->safariGoNearCounter = 0;
    gBattleStruct->safariPkblThrowCounter = 0;
    gBattleStruct->safariCatchFactor = gBaseStats[GetMonData(&gEnemyParty[0], MON_DATA_SPECIES)].catchRate * 100 / 1275;
    gBattleStruct->safariEscapeFactor = gBaseStats[GetMonData(&gEnemyParty[0], MON_DATA_SPECIES)].safariZoneFleeRate * 100 / 1275;
    if (gBattleStruct->safariEscapeFactor <= 1)
        gBattleStruct->safariEscapeFactor = 2;
    gBattleStruct->wildVictorySong = 0;
    gBattleStruct->moneyMultiplier = 1;
    gBattleStruct->debugAISet = FALSE;

    //gRandomTurnNumber = Random();
    
    //for (i = 0; i < 8; ++i)
    //{
       /* *((u8 *)gBattleStruct->lastTakenMove + i) = MOVE_NONE;
        //*((u8 *)gBattleStruct->usedHeldItems + i) = ITEM_NONE;
        *((u8 *)gBattleStruct->choicedMove + i) = MOVE_NONE;
        *((u8 *)gBattleStruct->changedItems + i) = ITEM_NONE;
        *(i + 0 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i + 1 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i + 2 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i + 3 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;*/
    //}
    for (i = 0; i < PARTY_SIZE; i++) //had to move after change define for usedHeldItem hope works... vsonic    //seems to be working?
    {
        gBattleStruct->usedHeldItems[i][B_SIDE_PLAYER] = FALSE;
        gBattleStruct->usedHeldItems[i][B_SIDE_OPPONENT] = FALSE;

        gBattleStruct->usedSingleUseAbility[i][B_SIDE_PLAYER] = FALSE;
        gBattleStruct->usedSingleUseAbility[i][B_SIDE_OPPONENT] = FALSE;
        
        gBattleStruct->SingleUseAbilityTimers[i][B_SIDE_PLAYER] = FALSE;
        gBattleStruct->SingleUseAbilityTimers[i][B_SIDE_OPPONENT] = FALSE;

        
        gBattleStruct->ToxicTurnCounter[i][B_SIDE_PLAYER] = 0;
        gBattleStruct->ToxicTurnCounter[i][B_SIDE_OPPONENT] = 0;

        gBattleStruct->SleepTimer[i][B_SIDE_PLAYER] = 0;
        gBattleStruct->SleepTimer[i][B_SIDE_OPPONENT] = 0;

        gBattleStruct->SecondaryItemSlot[i][B_SIDE_PLAYER] = ITEM_NONE;
        gBattleStruct->SecondaryItemSlot[i][B_SIDE_OPPONENT] = ITEM_NONE;

        gBattleStruct->itemStolen[i].originalItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);

        //gBattleStruct->allowedToChangeFormInWeather[i][B_SIDE_PLAYER] = FALSE;
        //gBattleStruct->allowedToChangeFormInWeather[i][B_SIDE_OPPONENT] = FALSE;
    }
    //*(gBattleStruct->AI_monToSwitchIntoId + 0) = PARTY_SIZE;
    //*(gBattleStruct->AI_monToSwitchIntoId + 1) = PARTY_SIZE;
    gBattleStruct->givenExpMons = 0;
    gBattleStruct->mega.triggerSpriteId = 0xFF;

    gBattleStruct->stickyWebUser = 0xFF;
    gBattleStruct->appearedInBattle = 0;  //not making burmy change form,, will keep whatever form you caught it with

    //hmm fill like this actually off and this and catchattempt should use pokeball_count
    //as their are 12 ball types 
    for (i = 0; i < POKEBALL_COUNT; ++i)
        gBattleResults.catchAttempts[i] = 0; //believe these first few are just statistics
    gBattleResults.battleTurnCounter = 0;
    gBattleResults.playerFaintCounter = 0;
    gBattleResults.opponentFaintCounter = 0;
    gBattleResults.playerSwitchesCounter = 0;
    gBattleResults.opponentSwitchesCounter = 0;
    gBattleResults.numHealingItemsUsed = 0;
    gBattleResults.numRevivesUsed = 0;
    gBattleResults.playerMonWasDamaged = FALSE;
    gBattleResults.usedMasterBall = FALSE;
    gBattleResults.lastOpponentSpecies = SPECIES_NONE;
    gBattleResults.lastUsedMovePlayer = MOVE_NONE;
    gBattleResults.lastUsedMoveOpponent = MOVE_NONE;
    gBattleResults.playerMon1Species = SPECIES_NONE;
    gBattleResults.playerMon2Species = SPECIES_NONE;
    gBattleResults.caughtMonSpecies = SPECIES_NONE;
    for (i = 0; i < POKEMON_NAME_LENGTH; ++i)
    {
        gBattleResults.playerMon1Name[i] = 0;
        gBattleResults.playerMon2Name[i] = 0; //may asso need to add on to this if for triple battles etc.
        gBattleResults.caughtMonNick[i] = 0;//potentially just add another field moonnick2 may work for double wild catching
    }
    gBattleStruct->swapDamageCategory = FALSE; // Photon Geyser, Shell Side Arm, Light That Burns the Sky
    gBattleStruct->pursuitTarget = 0;
    gBattleStruct->pursuitSwitchByMove = FALSE;
    gBattleStruct->pursuitStoredSwitch = 0;
    gSelectedMonPartyId = PARTY_SIZE; // Revival Blessing
}

#define CLEARDATA_ON_SWITCH
void SwitchInClearSetData(void) //handles what gets reset on switchout
{
    s32 i;
    struct DisableStruct disableStructCopy = gDisableStructs[gActiveBattler];

    ClearIllusionMon(gActiveBattler);
    if (gBattleMoves[gCurrentMove].effect != EFFECT_BATON_PASS)
    {
        for (i = 0; i < NUM_BATTLE_STATS; ++i)
            gBattleMons[gActiveBattler].statStages[i] = DEFAULT_STAT_STAGE; //6 is 0 so this resets to normal levels
        for (i = 0; i < gBattlersCount; ++i)
        {
            if ((gBattleMons[i].status2 & STATUS2_ESCAPE_PREVENTION) && gDisableStructs[i].battlerPreventingEscape == gActiveBattler)
                gBattleMons[i].status2 &= ~STATUS2_ESCAPE_PREVENTION; //if mon blocking escape switches, removes escape prevention status from target
            if ((gStatuses3[i] & STATUS3_ALWAYS_HITS) && gDisableStructs[i].battlerWithSureHit == gActiveBattler)
            {
                gStatuses3[i] &= ~STATUS3_ALWAYS_HITS;
                gDisableStructs[i].battlerWithSureHit = 0;
            }
        }//exclude STATUS2_SWITCH_LOCKED from here so user can switch out and still lock enemy
    }
    if (gBattleMoves[gCurrentMove].effect == EFFECT_BATON_PASS) //added yawn to baton pass effects with change to activation should work
    {
        gBattleMons[gActiveBattler].status2 &= (STATUS2_CONFUSION | STATUS2_FOCUS_ENERGY | STATUS2_SUBSTITUTE | STATUS2_ESCAPE_PREVENTION | STATUS2_SWITCH_LOCKED | STATUS2_CURSED);
        gStatuses3[gActiveBattler] &= (STATUS3_LEECHSEED_BATTLER | STATUS3_LEECHSEED | STATUS3_ALWAYS_HITS | STATUS3_YAWN | STATUS3_PERISH_SONG | STATUS3_ROOTED
                                       | STATUS3_GASTRO_ACID | STATUS3_TELEKINESIS | STATUS3_MAGNET_RISE | STATUS3_AQUA_RING | STATUS3_POWER_TRICK);
        for (i = 0; i < gBattlersCount; ++i)
        {
            if (GetBattlerSide(gActiveBattler) != GetBattlerSide(i)
             && (gStatuses3[i] & STATUS3_ALWAYS_HITS) != 0
             && (gDisableStructs[i].battlerWithSureHit == gActiveBattler))
            {
                gStatuses3[i] &= ~(STATUS3_ALWAYS_HITS);
                gStatuses3[i] |= 0x10;
            }
        }
        if (gStatuses3[gActiveBattler] & STATUS3_POWER_TRICK) //would make it easy to set more swap variants, i.e there isn't a special one
            SWAP(gBattleMons[gActiveBattler].attack, gBattleMons[gActiveBattler].defense, i);
    }
    else //if not using baton pass clear status 2 & 3 on switch? //this is status clear on mon switching out
    {
        gBattleMons[gActiveBattler].status2 = 0;
        gBattleMons[gActiveBattler].status4 = 0;
        gStatuses3[gActiveBattler] = 0; //guess so but seems I misunderstood switch clear it clears data when they switch into battle not switching out
        gStatuses4[gActiveBattler] = 0; // if don't clear could make status 4 traps permament so don't need to swap to status1
        //could just put if battler that set status was holding grip claw don't clear   
        //look to wrapped by logic for example, use that as battlerId and check hold effect vsonic
        //should be simple change to trappedby  and use for all traps
    }
    for (i = 0; i < gBattlersCount; ++i)// is this something that removes wrap, and infatuation if the mon that caused the effect is switched out? yes
    {
        if (gBattleMons[i].status2 & STATUS2_INFATUATED_WITH(gActiveBattler))
            gBattleMons[i].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler)); //forgot I planned steup for suction cup and certain held item to make traps persist

        if ((GetBattlerAbility(gActiveBattler) != ABILITY_SUCTION_CUPS) && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_GRIP_CLAW)
        {
            if ((gBattleMons[i].status2 & STATUS2_WRAPPED) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
                gBattleMons[i].status2 &= ~(STATUS2_WRAPPED); 
            if ((gBattleMons[i].status4 & STATUS4_BIND) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
                gBattleMons[i].status4 &= ~(STATUS4_BIND); 
            if ((gBattleMons[i].status4 & STATUS4_CLAMP) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
                gBattleMons[i].status4 &= ~(STATUS4_CLAMP); 
            if ((gBattleMons[i].status4 & STATUS4_SWARM) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
                gBattleMons[i].status4 &= ~(STATUS4_SWARM); 
            if ((gBattleMons[i].status4 & STATUS4_THUNDER_CAGE) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
                gBattleMons[i].status4 &= ~(STATUS4_THUNDER_CAGE);  
            if ((gDisableStructs[i].environmentTrapTurns) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            {
                gDisableStructs[i].environmentTrapTurns = 0;
                gBattleMons[i].status4 &= ~STATUS4_FIRE_SPIN;
                gBattleMons[i].status4 &= ~STATUS4_WHIRLPOOL;
                gBattleMons[i].status4 &= ~STATUS4_SAND_TOMB;
                gBattleMons[i].status4 &= ~STATUS4_MAGMA_STORM;
            }//snaptrap not included here, so trap will persist if switch like I want
        }
    }
    gActionSelectionCursor[gActiveBattler] = 0;
    gMoveSelectionCursor[gActiveBattler] = 0;

    memset(&gDisableStructs[gActiveBattler], 0, sizeof(struct DisableStruct));
    
    if (gBattleMoves[gCurrentMove].effect == EFFECT_BATON_PASS)
    {
        gDisableStructs[gActiveBattler].substituteHP = disableStructCopy.substituteHP;
        gDisableStructs[gActiveBattler].battlerWithSureHit = disableStructCopy.battlerWithSureHit;
        gDisableStructs[gActiveBattler].perishSongTimer = disableStructCopy.perishSongTimer;
        gDisableStructs[gActiveBattler].SwitchBinding = disableStructCopy.SwitchBinding;
        gDisableStructs[gActiveBattler].battlerPreventingEscape = disableStructCopy.battlerPreventingEscape;
    }
    gMoveResultFlags = 0;
    gDisableStructs[gActiveBattler].isFirstTurn = 2; // turn of switch in
    gLastMoves[gActiveBattler] = MOVE_NONE;
    gLastLandedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitByType[gActiveBattler] = 0;
    gLastResultingMoves[gActiveBattler] = MOVE_NONE;
    gLastPrintedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitBy[gActiveBattler] = 0xFF;
    gBattleStruct->sameMoveTurns[gActiveBattler] = 0;
    gBattleStruct->lastTakenMove[gActiveBattler] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][0] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][1] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][2] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][3] = 0;
    gBattleStruct->lastMoveFailed &= ~(gBitTable[gActiveBattler]);

    if (gActiveBattler == gBattleStruct->stickyWebUser)
        gBattleStruct->stickyWebUser = 0xFF;    // Switched into sticky web user slot so reset it
    
    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != gActiveBattler && GetBattlerSide(i) != GetBattlerSide(gActiveBattler))
            gBattleStruct->lastTakenMove[i] = MOVE_NONE;

        gBattleStruct->lastTakenMoveFrom[i][gActiveBattler] = 0;
    }
    gBattleStruct->choicedMove[gActiveBattler] = MOVE_NONE;
    gBattleResources->flags->flags[gActiveBattler] = 0;
    gCurrentMove = MOVE_NONE;

    // Record HP of incoming battler
    gBattleStruct->hpBefore[gActiveBattler] = gBattleMons[gActiveBattler].hp;


    // Reset damage to prevent things like red card activating if the switched-in mon is holding it
    gSpecialStatuses[gActiveBattler].physicalDmg = 0;
    gSpecialStatuses[gActiveBattler].specialDmg = 0;

    gBattleStruct->overwrittenAbilities[gActiveBattler] = ABILITY_NONE;

    // Clear selected party ID so Revival Blessing doesn't get confused.
    gSelectedMonPartyId = PARTY_SIZE;
}

#define CLEARDATA_ON_FAINT
void FaintClearSetData(void) //see about make status1 not fade wen faint?
{
    s32 i;
    u8 *ptr;
    struct Pokemon *party;

    for (i = 0; i < NUM_BATTLE_STATS; ++i)
        gBattleMons[gActiveBattler].statStages[i] = 6;
    gBattleMons[gActiveBattler].status2 = 0;
    gBattleMons[gActiveBattler].status4 = 0;
    gStatuses3[gActiveBattler] = 0;
    gStatuses4[gActiveBattler] = 0;
    for (i = 0; i < gBattlersCount; ++i) //trap etc removal on faint
    {
        //also exclude STATUS2_SWITCH_LOCKED from this, so effect persists
        if ((gBattleMons[i].status2 & STATUS2_ESCAPE_PREVENTION) && gDisableStructs[i].battlerPreventingEscape == gActiveBattler)
            gBattleMons[i].status2 &= ~STATUS2_ESCAPE_PREVENTION;
        if (gBattleMons[i].status2 & STATUS2_INFATUATED_WITH(gActiveBattler))
            gBattleMons[i].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler));

        if ((gBattleMons[i].status2 & STATUS2_WRAPPED) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status2 &= ~(STATUS2_WRAPPED);
        if ((gBattleMons[i].status4 & STATUS4_BIND) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status4 &= ~(STATUS4_BIND); 
        if ((gBattleMons[i].status4 & STATUS4_CLAMP) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status4 &= ~(STATUS4_CLAMP); 
        if ((gBattleMons[i].status4 & STATUS4_SWARM) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status4 &= ~(STATUS4_SWARM); 
        if ((gBattleMons[i].status4 & STATUS4_THUNDER_CAGE) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status4 &= ~(STATUS4_THUNDER_CAGE);  
        if ((gDisableStructs[i].environmentTrapTurns) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            {
                gDisableStructs[i].environmentTrapTurns = 0;
                gBattleMons[i].status4 &= ~STATUS4_FIRE_SPIN;
                gBattleMons[i].status4 &= ~STATUS4_WHIRLPOOL;
                gBattleMons[i].status4 &= ~STATUS4_SAND_TOMB;
                gBattleMons[i].status4 &= ~STATUS4_MAGMA_STORM;
            }
    }//leaving snaptrap, as they are separate from the battler's body/control they will still exist even if they faint

    gActionSelectionCursor[gActiveBattler] = 0;
    gMoveSelectionCursor[gActiveBattler] = 0;
    ptr = (u8 *)&gDisableStructs[gActiveBattler];
    for (i = 0; i < sizeof(struct DisableStruct); ++i)
        ptr[i] = 0;
    gProtectStructs[gActiveBattler].protected = FALSE;
    gProtectStructs[gActiveBattler].endured = FALSE;
    gProtectStructs[gActiveBattler].noValidMoves = FALSE;
    gProtectStructs[gActiveBattler].helpingHand = FALSE;
    gProtectStructs[gActiveBattler].spikyShielded = FALSE;
    gProtectStructs[gActiveBattler].kingsShielded = FALSE;
    gProtectStructs[gActiveBattler].banefulBunkered = FALSE;
    gProtectStructs[gActiveBattler].bounceMove = FALSE;
    gProtectStructs[gActiveBattler].stealMove = FALSE;
    gProtectStructs[gActiveBattler].flag0Unknown = FALSE;
    gProtectStructs[gActiveBattler].prlzImmobility = FALSE;
    gProtectStructs[gActiveBattler].confusionSelfDmg = FALSE;
    gProtectStructs[gActiveBattler].targetNotAffected = FALSE;
    gProtectStructs[gActiveBattler].chargingTurn = FALSE;
    gProtectStructs[gActiveBattler].fleeFlag = 0;
    gProtectStructs[gActiveBattler].usedImprisonedMove = FALSE;
    gProtectStructs[gActiveBattler].loveImmobility = FALSE;
    gProtectStructs[gActiveBattler].obstructed = FALSE;
    gProtectStructs[gActiveBattler].usedDisabledMove = FALSE;
    gProtectStructs[gActiveBattler].usedTauntedMove = FALSE;
    gProtectStructs[gActiveBattler].flag2Unknown = FALSE;
    gProtectStructs[gActiveBattler].flinchImmobility = FALSE;
    gProtectStructs[gActiveBattler].notFirstStrike = FALSE;
    gProtectStructs[gActiveBattler].pranksterElevated = FALSE;
    gProtectStructs[gActiveBattler].galewingsElevated = FALSE;
    gProtectStructs[gActiveBattler].triageElevated = FALSE;
    gProtectStructs[gActiveBattler].OmniAideElevated = FALSE;
    gProtectStructs[gActiveBattler].NuisanceElevated = FALSE;
    gProtectStructs[gActiveBattler].LightMetalElevated = FALSE;
    gProtectStructs[gActiveBattler].LongReachElevated = FALSE;
    gProtectStructs[gActiveBattler].usedHealBlockedMove = FALSE;
    gProtectStructs[gActiveBattler].usesBouncedMove = FALSE;
    gProtectStructs[gActiveBattler].usedGravityPreventedMove = FALSE;
    gProtectStructs[gActiveBattler].usedThroatChopPreventedMove = FALSE; 
    gDisableStructs[gActiveBattler].isFirstTurn = 2;
    gLastMoves[gActiveBattler] = MOVE_NONE;
    gLastLandedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitByType[gActiveBattler] = MOVE_NONE;
    gLastResultingMoves[gActiveBattler] = MOVE_NONE;
    gLastPrintedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitBy[gActiveBattler] = 0xFF;
    gBattleStruct->sameMoveTurns[gActiveBattler] = 0; //hope works since others writ diff in fire red/emerald
    gBattleStruct->choicedMove[gActiveBattler] = MOVE_NONE;
    gBattleStruct->lastTakenMove[gActiveBattler] = MOVE_NONE;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][0] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][1] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][2] = 0;
    gBattleStruct->lastTakenMoveFrom[gActiveBattler][3] = 0;
    gBattleStruct->pursuitTarget = 0;
    gBattleStruct->pursuitSwitchByMove = FALSE;
    gBattleStruct->pursuitStoredSwitch = 0;

    if (gActiveBattler == gBattleStruct->stickyWebUser)
        gBattleStruct->stickyWebUser = 0xFF;    // User of sticky web fainted, so reset the stored battler ID
        //looking at this can do same for forewarn/anticipation, if ability wasn't triggered but stored mon fainted,
        // reset the abiity check and let it pick another mon

    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != gActiveBattler && GetBattlerSide(i) != GetBattlerSide(gActiveBattler))
            gBattleStruct->lastTakenMove[i] = MOVE_NONE;

        gBattleStruct->lastTakenMoveFrom[i][gActiveBattler] = 0;
    }
    gBattleResources->flags->flags[gActiveBattler] = 0;
    gBattleMons[gActiveBattler].type1 = gBaseStats[gBattleMons[gActiveBattler].species].type1;
    gBattleMons[gActiveBattler].type2 = gBaseStats[gBattleMons[gActiveBattler].species].type2;
    gBattleMons[gActiveBattler].type3 = TYPE_MYSTERY;

    //Ai_UpdateFaintData(gActiveBattler);
    TryBattleFormChange(gActiveBattler, FORM_CHANGE_FAINT); //replaced undomegaevolution

    //UndoFormChange(gBattlerPartyIndexes[gActiveBattler], GET_BATTLER_SIDE(gActiveBattler), FALSE); //vsonic some logic still to do
    /*if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        UndoMegaEvolution(gBattlerPartyIndexes[gActiveBattler]);*/


    gBattleStruct->overwrittenAbilities[gActiveBattler] = ABILITY_NONE;

    // If the fainted mon was involved in a Sky Drop
    if (gBattleStruct->skyDropTargets[gActiveBattler] != 0xFF)
    {
        // Get battler id of the other Pokemon involved in this Sky Drop
        u8 otherSkyDropper = gBattleStruct->skyDropTargets[gActiveBattler];

        // Clear Sky Drop data
        gBattleStruct->skyDropTargets[gActiveBattler] = 0xFF;
        gBattleStruct->skyDropTargets[otherSkyDropper] = 0xFF;

        // If the other Pokemon involved in this Sky Drop was the target, not the attacker
        if (gStatuses3[otherSkyDropper] & STATUS3_SKY_DROPPED)
        {
            // Release the target and take them out of the semi-invulnerable state
            gStatuses3[otherSkyDropper] &= ~(STATUS3_SKY_DROPPED | STATUS3_ON_AIR);

            // Make the target's sprite visible
            gSprites[gBattlerSpriteIds[otherSkyDropper]].invisible = FALSE;

            // If the target was sky dropped in the middle of using Outrage/Petal Dance/Thrash,
            // confuse them upon release and print "confused via fatigue" message and animation.
            if (gBattleMons[otherSkyDropper].status2 & STATUS2_LOCK_CONFUSE)
            {
                gBattleMons[otherSkyDropper].status2 &= ~(STATUS2_LOCK_CONFUSE);

                // If the released mon can be confused, do so.
                // Don't use CanBeConfused here, since it can cause issues in edge cases.
                if (!(GetBattlerAbility(otherSkyDropper) == ABILITY_OWN_TEMPO
                    || gBattleMons[otherSkyDropper].status2 & STATUS2_CONFUSION
                    || IsBattlerTerrainAffected(otherSkyDropper, STATUS_FIELD_MISTY_TERRAIN)))
                {
                    gDisableStructs[otherSkyDropper].ConfusionTurns = ((Random()% 4) + 2);
                    gBattlerAttacker = otherSkyDropper;
                    gBattlescriptCurrInstr = BattleScript_ThrashConfuses - 2;
                }
            }
        }
    }

    /*// Clear Z-Move data
    gBattleStruct->zmove.active = FALSE;
    gBattleStruct->zmove.toBeUsed[gActiveBattler] = MOVE_NONE;
    gBattleStruct->zmove.effect = EFFECT_HIT;*/ //vsonic for latetr

    if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT) //use this instead taken from mega logic
        party = &gEnemyParty[gBattlerPartyIndexes[gActiveBattler]];  //mon being transformed
    else
        party = &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]];

    //removed transformatino line as status2 would alraedy be removed  fron fainted
    //if (gBattleMons[gActiveBattler].status2 & STATUS2_TRANSFORMED)
        CalculateMonStats(party); //to reset stats to normal  
    //lost location don't display if 0,

    //boxhp only set if is 0                
    if (IsNuzlockeModeOn() && (GetMonData(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_HP, NULL) == 0)
    && FlagGet(FLAG_SYS_POKEDEX_GET)
    && GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
    {
        u8 boxHP = 0;
        //u8 map = GetCurrentRegionMapSectionId();
        //SetMonData(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_LOST_LOCATION, &map);
        SetMonData(party, MON_DATA_BOX_HP, &boxHP);
    }    //this works here
}

static void BattleIntroGetMonsData(void)
{
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        gActiveBattler = gBattleCommunication[1];
        BtlController_EmitGetMonData(0, REQUEST_ALL_BATTLE, 0);
        MarkBattlerForControllerExec(gActiveBattler);
        ++gBattleCommunication[MULTIUSE_STATE];
        break;
    case 1:
        if (gBattleControllerExecFlags == 0)
        {
            ++gBattleCommunication[1];
            if (gBattleCommunication[1] == gBattlersCount)
                gBattleMainFunc = BattleIntroPrepareBackgroundSlide;
            else
                gBattleCommunication[MULTIUSE_STATE] = 0;
        }
        break;
    }
}

static void BattleIntroPrepareBackgroundSlide(void)
{
    if (gBattleControllerExecFlags == 0)
    {
        gActiveBattler = GetBattlerAtPosition(0);
        BtlController_EmitIntroSlide(0, gBattleTerrain);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattleMainFunc = BattleIntroDrawTrainersOrMonsSprites;
        gBattleCommunication[MULTIUSE_STATE] = 0;
        gBattleCommunication[SPRITES_INIT_STATE1] = 0;
    }
}

//ok I think THIS is where type gets set to battle values for battle start,
//and possibly reason for type bug, it wasn't something I changed but something I DIDN'T change,
//type3 wasn't added to this, but it was used for typecalc, and I think its absense just left it as 0, since battlestruct does get 0'd at some point
//so it was getting 0'd but not set, similar to wrap issue but in reverse
//confirmed this was the issue
#define BATTLE_START_VALUES
static void BattleIntroDrawTrainersOrMonsSprites(void)
{
    u8 *ptr;
    s32 i;

    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if ((gBattleTypeFlags & BATTLE_TYPE_SAFARI)
             && GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            {
                ptr = (u8 *)&gBattleMons[gActiveBattler];
                for (i = 0; i < sizeof(struct BattlePokemon); ++i)
                    ptr[i] = 0;
            }
            else // all non-safari battles
            {
                u16 *hpOnSwitchout;

                ptr = (u8 *)&gBattleMons[gActiveBattler];
                for (i = 0; i < sizeof(struct BattlePokemon); ++i)
                    ptr[i] = gBattleBufferB[gActiveBattler][4 + i];
                gBattleMons[gActiveBattler].type1 = gBaseStats[gBattleMons[gActiveBattler].species].type1;
                gBattleMons[gActiveBattler].type2 = gBaseStats[gBattleMons[gActiveBattler].species].type2;
                gBattleMons[gActiveBattler].type3 = TYPE_MYSTERY;
                gBattleMons[gActiveBattler].ability = GetAbilityBySpecies(gBattleMons[gActiveBattler].species, gBattleMons[gActiveBattler].abilityNum);
                hpOnSwitchout = &gBattleStruct->hpOnSwitchout[GetBattlerSide(gActiveBattler)];
                *hpOnSwitchout = gBattleMons[gActiveBattler].hp;
                for (i = 0; i < NUM_BATTLE_STATS; ++i)
                    gBattleMons[gActiveBattler].statStages[i] = 6; //important, these two reset stat buffs, and clear status2 effects on switch
                gBattleMons[gActiveBattler].status2 = 0; //or is it for batle start?
                gBattleMons[gActiveBattler].status4 = 0;
            }
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_LEFT)
            {
                BtlController_EmitDrawTrainerPic(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
            {
                if (GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_LEFT)
                {
                    BtlController_EmitDrawTrainerPic(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT
                 && !(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                       | BATTLE_TYPE_POKEDUDE
                                       | BATTLE_TYPE_LINK
                                       | BATTLE_TYPE_GHOST
                                       | BATTLE_TYPE_OLD_MAN_TUTORIAL
                                       | BATTLE_TYPE_LEGENDARY)))
                    HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
            }
            else
            {
                if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT)
                {
                    if (gBattleTypeFlags & (BATTLE_TYPE_GHOST | BATTLE_TYPE_GHOST_UNVEILED))
                    {
                        if (!IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))
                            HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
                    }
                    else if (!(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                                | BATTLE_TYPE_POKEDUDE
                                                | BATTLE_TYPE_LINK
                                                | BATTLE_TYPE_GHOST
                                                | BATTLE_TYPE_OLD_MAN_TUTORIAL
                                                | BATTLE_TYPE_LEGENDARY)))
                    {
                        HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
                    }
                    BtlController_EmitLoadMonSprite(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI
             && (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_RIGHT || GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_RIGHT))
            {
                BtlController_EmitDrawTrainerPic(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleMainFunc = BattleIntroDrawPartySummaryScreens;
    }
}

static void BattleIntroDrawPartySummaryScreens(void)
{
    s32 i;
    struct HpAndStatus hpStatus[PARTY_SIZE];

    if (!gBattleControllerExecFlags)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
                 || GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
                {
                    hpStatus[i].hp = 0xFFFF;
                    hpStatus[i].status = 0;
                }
                else
                {
                    hpStatus[i].hp = GetMonData(&gEnemyParty[i], MON_DATA_HP);
                    hpStatus[i].status = GetMonData(&gEnemyParty[i], MON_DATA_STATUS);
                }
            }
            gActiveBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            BtlController_EmitDrawPartyStatusSummary(0, hpStatus, 0x80);
            MarkBattlerForControllerExec(gActiveBattler);
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
                 || GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
                {
                    hpStatus[i].hp = 0xFFFF;
                    hpStatus[i].status = 0;
                }
                else
                {
                    hpStatus[i].hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
                    hpStatus[i].status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
                }
            }
            gActiveBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            BtlController_EmitDrawPartyStatusSummary(0, hpStatus, 0x80);
            MarkBattlerForControllerExec(gActiveBattler);

            gBattleMainFunc = BattleIntroPrintTrainerWantsToBattle;
        }
        else
        {
            // The struct gets set here, but nothing is ever done with it since
            // wild battles don't show the party summary.
            // Still, there's no point in having dead code.
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
                 || GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
                {
                    hpStatus[i].hp = 0xFFFF;
                    hpStatus[i].status = 0;
                }
                else
                {
                    hpStatus[i].hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
                    hpStatus[i].status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
                }
            }
            gBattleMainFunc = BattleIntroPrintWildMonAttacked;
        }
    }
}

static void BattleIntroPrintTrainerWantsToBattle(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        PrepareStringBattle(STRINGID_INTROMSG, gActiveBattler);
        gBattleMainFunc = BattleIntroPrintOpponentSendsOut;
    }
}

static void BattleIntroPrintWildMonAttacked(void)
{
    if (!gBattleControllerExecFlags)
    {
        gBattleMainFunc = BattleIntroPrintPlayerSendsOut;
        PrepareStringBattle(STRINGID_INTROMSG, 0);
        if (IS_BATTLE_TYPE_GHOST_WITH_SCOPE(gBattleTypeFlags))
        {
            gBattleScripting.battler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            BattleScriptExecute(BattleScript_SilphScopeUnveiled);
        }
    }
}

static void BattleIntroPrintOpponentSendsOut(void)
{
    if (!gBattleControllerExecFlags)
    {
        PrepareStringBattle(STRINGID_INTROSENDOUT, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
        gBattleMainFunc = BattleIntroOpponentSendsOutMonAnimation;
    }
}

static void BattleIntroOpponentSendsOutMonAnimation(void)
{
    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_LEFT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_RIGHT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleMainFunc = BattleIntroRecordMonsToDex;
    }
}

static void BattleIntroRecordMonsToDex(void)
{
    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT
             && !(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                   | BATTLE_TYPE_POKEDUDE
                                   | BATTLE_TYPE_LINK
                                   | BATTLE_TYPE_GHOST
                                   | BATTLE_TYPE_OLD_MAN_TUTORIAL
                                   | BATTLE_TYPE_LEGENDARY)))
                HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
        gBattleMainFunc = BattleIntroPrintPlayerSendsOut;
    }
}

// not used
static void Unused_AutoProgressToIntro(void)
{
    if (!gBattleControllerExecFlags)
        gBattleMainFunc = BattleIntroPrintPlayerSendsOut;
}

void BattleIntroPrintPlayerSendsOut(void)
{
    if (!gBattleControllerExecFlags)
    {
        if (!(gBattleTypeFlags & BATTLE_TYPE_SAFARI))
            PrepareStringBattle(STRINGID_INTROSENDOUT, GetBattlerAtPosition(B_POSITION_PLAYER_LEFT));
        gBattleMainFunc = BattleIntroPlayerSendsOutMonAnimation;
    }
}

static void BattleIntroPlayerSendsOutMonAnimation(void)
{
    u32 position;

    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_LEFT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_RIGHT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleStruct->switchInAbilitiesCounter = 0;
        gBattleStruct->switchInItemsCounter = 0;
        gBattleStruct->overworldWeatherDone = FALSE;
        gBattleMainFunc = TryDoEventsBeforeFirstTurn;
    }
}

// not used
static void Unused_AutoProgressToSwitchInAnims(void)
{
    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            {
                BtlController_EmitSwitchInAnim(0, gBattlerPartyIndexes[gActiveBattler], FALSE);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleStruct->switchInAbilitiesCounter = 0;
        gBattleStruct->switchInItemsCounter = 0;
        gBattleStruct->overworldWeatherDone = FALSE;
        gBattleMainFunc = TryDoEventsBeforeFirstTurn;
    }
}

//didn't understand but think this is effect checks
//before first turn for BATTLER, not all battle,
//so switch in stuff etc. other chekcs for before new mon hits field
//well not before it hits field, but before turn start i.e move selection
static void TryDoEventsBeforeFirstTurn(void)
{
    s32 i, j;
    u8 effect = 0;

    if (!gBattleControllerExecFlags)
    {
        
        if (gBattleStruct->switchInAbilitiesCounter == 0)
        {
            for (i = 0; i < gBattlersCount; ++i)
                gBattlerByTurnOrder[i] = i;
            for (i = 0; i < gBattlersCount - 1; ++i)
                for (j = i + 1; j < gBattlersCount; ++j)    //functino is weird, way works if 0 I attack first, 
                    if (GetWhoStrikesFirst(gBattlerByTurnOrder[i], gBattlerByTurnOrder[j], TRUE) != 0) //which iswhy here it swaps order, 
                        SwapTurnOrder(i, j);
        }
        
        if (!gBattleStruct->terrainDone && AbilityBattleEffects(0, 0, 0, ABILITYEFFECT_SWITCH_IN_TERRAIN, 0) != 0)
        {
            gBattleStruct->terrainDone = TRUE;
            return;
        }
        if (!gBattleStruct->overworldWeatherDone && AbilityBattleEffects(0, 0, 0, ABILITYEFFECT_SWITCH_IN_WEATHER, 0) != 0)
        {
            gBattleStruct->overworldWeatherDone = TRUE; //move here cuz I want terrain to trigger first
            return;
        }
        // Totem boosts
        /*for (i = 0; i < gBattlersCount; i++)
        {
            if (gTotemBoosts[i].stats != 0)
            {
                gBattlerAttacker = i;
                BattleScriptExecute(BattleScript_TotemVar);
                return;
            }
        }
        memset(gTotemBoosts, 0, sizeof(gTotemBoosts));  // erase all totem boosts just to be safe
        */
        // Primal Reversion
        for (i = 0; i < gBattlersCount; i++)
        {
            if (CanMegaEvolve(i)
                && GetBattlerHoldEffect(i, TRUE) == HOLD_EFFECT_PRIMAL_ORB)
            {
                gBattlerAttacker = i;
                BattleScriptExecute(BattleScript_PrimalReversion);
                return;
            }
        }

        // Check neutralizing gas
        if (AbilityBattleEffects(ABILITYEFFECT_NEUTRALIZINGGAS, 0, 0, 0, 0) != 0)
            return;//note removal of levitate will make flying types safer
        //from poison/weezing, but countred by increasd smackdown learnset and roost change

        // Check all switch in abilities happening from the fastest mon to slowest.
        while (gBattleStruct->switchInAbilitiesCounter < gBattlersCount) //want to change to work on switchin and when opponent switches pokemon.
        {
            if (AbilityBattleEffects(ABILITYEFFECT_ON_SWITCHIN, gBattlerByTurnOrder[gBattleStruct->switchInAbilitiesCounter], 0, 0, 0) != 0)
                ++effect; //believe this is looping through only switch in abilities, I think long as ability isn't none?
            ++gBattleStruct->switchInAbilitiesCounter; //intimidate2 isn't referenced anywhere, so I assume its just baked into normal switchin
            //if I want another category of switchin abilities, pretty sure all I need to do is add it in here above the counter? unless this is all really battle 1st turn
            //and not firstturn for mon in which case it wouldn't work for my needs..
            if (effect)//think if effect increments counts as activated so returns and checks next battler?
                return; //yeah checking mon in battle for if they have switchin abilities, and activates them if they do.
        } //check pursuit it may be the best way to do this, since it tells when a battler is switching and activates an effect
        //plan to pattern after spikes instead as that effects side, and only on mon switching in
        if (AbilityBattleEffects(ABILITYEFFECT_INTIMIDATE1, 0, 0, 0, 0) != 0) //this is battle start intimidate.
            return;
        if (AbilityBattleEffects(ABILITYEFFECT_TRACE, 0, 0, 0, 0) != 0)
            return;
        // Check all switch in items having effect from the fastest mon to slowest.
        while (gBattleStruct->switchInItemsCounter < gBattlersCount)
        {
            if (ItemBattleEffects(ITEMEFFECT_ON_SWITCH_IN, gBattlerByTurnOrder[gBattleStruct->switchInItemsCounter], FALSE))
                ++effect;
            ++gBattleStruct->switchInItemsCounter;
            if (effect)
                return;
        }
        for (i = 0; i < gBattlersCount; ++i) // pointless, ruby leftover
            ;
        for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        {
            *(gBattleStruct->monToSwitchIntoId + i) = PARTY_SIZE;
            gChosenActionByBattler[i] = B_ACTION_NONE;
            gChosenMoveByBattler[i] = MOVE_NONE;
        }
        TurnValuesCleanUp(FALSE);
        SpecialStatusesClear();
        *(&gBattleStruct->absentBattlerFlags) = gAbsentBattlerFlags;
        gBattleMainFunc = HandleTurnActionSelectionState;
        ResetSentPokesToOpponentValue();
        for (i = 0; i < BATTLE_COMMUNICATION_ENTRIES_COUNT; ++i)
            gBattleCommunication[i] = 0;
        for (i = 0; i < gBattlersCount; ++i)
            gBattleMons[i].status2 &= ~(STATUS2_FLINCHED);
        *(&gBattleStruct->turnEffectsTracker) = 0;
        *(&gBattleStruct->turnEffectsBattlerId) = 0;
        *(&gBattleStruct->wishPerishSongState) = 0;
        *(&gBattleStruct->wishPerishSongBattlerId) = 0;
        gBattleScripting.atk49_state = 0;
        gBattleStruct->faintedActionsState = 0;
        gBattleStruct->turnCountersTracker = 0;
        gMoveResultFlags = 0;
        gRandomTurnNumber = Random();

        //seems EE later replaced this w SetAiLogicDataForTurn
        GetAiLogicData(); // get assumed abilities, hold effects, etc of all battlers
    }
}

static void HandleEndTurn_ContinueBattle(void)
{
    s32 i;
    u32 j;

    if (!gBattleControllerExecFlags)
    {
        gBattleMainFunc = BattleTurnPassed;
        for (i = 0; i < BATTLE_COMMUNICATION_ENTRIES_COUNT; ++i)
            gBattleCommunication[i] = 0;
        for (i = 0; i < gBattlersCount; ++i)
        {
            gBattleMons[i].status2 &= ~(STATUS2_FLINCHED);
            //if ((gBattleMons[i].status1 & STATUS1_SLEEP) && (gBattleMons[i].status2 & STATUS2_MULTIPLETURNS))
            if ((gBattleMons[i].status1 & STATUS1_SLEEP)) //pretty sure no reason not to just make it auto run on sleep
                CancelMultiTurnMoves(i);

            //...ok so think what this actually does is make it so no mon on the side can use this ability at all? or is it anymon?    
            for (j = 0; j < PARTY_SIZE; ++j) //ok actually have to use party size i.e loop 6 for this to properly track no idea why it works but it works
            {
                //&gEnemyParty[gBattlerPartyIndexes[gActiveBattler]]
                if (gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[j]][GetBattlerSide(i)] == TRUE 
                && (gBattleMons[i].ability == ABILITY_FOREWARN || gBattleMons[i].ability == ABILITY_ANTICIPATION))
                {
                    gDisableStructs[i].forewarnedMove = MOVE_UNAVAILABLE; //-_- yup ability fails to work for ANYONE after turn 1 because of this
                    gDisableStructs[i].anticipatedMove = MOVE_UNAVAILABLE;  //to clear out effects at endturn properly
                }
            }//attempted fix, hopefully doesn't lag to hell. - no lag, fix not quite there yet, or if rihgt, not fully explored
            //actyally this might do it, long as this in right place, this would set the side as haing used ability,
            //then whatever mon with these two abilities that goes out, would have themselves set as being unable to use it
            //no matter what battle position, because it loops all of them


            //...or does it just block all singlue useabilities if any of the category get used... isgh
            //well I guess that's an issue if single use isn't actually tracking to the battler and just a position...
            //which now that I think about it,  based on how disguise works it looks like its working correctly
            //and tracking wherever the mon is switched?

            //think it works? tested w two mimikyu,  one got busted swapped it out for another and it still took the hit,
            //since it wasn't teh same one, so seems to prove it follows the mon rather than just the slot

            //may need add check that indexedd mon is not mimikyu or doe snot have disguise to ensure mon in questino
            //actually used forewarn or anticipation
        }
        gBattleStruct->turnEffectsTracker = 0;
        gBattleStruct->turnEffectsBattlerId = 0;
        gBattleStruct->wishPerishSongState = 0;
        gBattleStruct->wishPerishSongBattlerId = 0;
        gBattleStruct->turnCountersTracker = 0;
        gMoveResultFlags = 0;
        if (VarGet(VAR_LAST_MULTIHIT_RESULT))
            VarSet(VAR_LAST_MULTIHIT_RESULT, 0);    //clear last result var for multihit at turn end
    }
}

void BattleTurnPassed(void) //after all moves used
{
    s32 i;

    TurnValuesCleanUp(TRUE); //protect and endure specifically cleared here
    if (gBattleOutcome == 0) //starting value //battle not done
    {
        if (DoFieldEndTurnEffects()) //probably posssible wrap trap logic?  actually no, that is in battlereffecfs... missed turn counter reset in endturn wish seeing if that was issue
            return; //wish wasn't it, but missed turnisde increment in aurora veil, due to bad replace could be it?
        if (DoBattlerEndTurnEffects()) //identified fieldendturn is the probolem / fixed that , that was part of freeze, but main issue for wrap dmg is battlerendturn
            return;
    }
    if (HandleFaintedMonActions())
        return;
    gBattleStruct->faintedActionsState = 0;
    if (HandleWishPerishSongOnTurnEnd())
        return;
    //entire protect struct values are cleaned in this function,  (false version only)
    //also where isFirstTurn decrement happens
    TurnValuesCleanUp(FALSE); 
    gHitMarker &= ~(HITMARKER_NO_ATTACKSTRING);
    gHitMarker &= ~(HITMARKER_UNABLE_TO_USE_MOVE);
    gHitMarker &= ~(HITMARKER_PLAYER_FAINTED);
    gHitMarker &= ~(HITMARKER_PASSIVE_DAMAGE);
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gBattleScripting.atk49_state = 0;
    gBattleMoveDamage = 0;
    gMoveResultFlags = 0;
    for (i = 0; i < 5; ++i)
        gBattleCommunication[i] = 0;
    if (gBattleOutcome != 0)
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        gBattleMainFunc = RunTurnActionsFunctions;
        return;
    }
    if (gBattleResults.battleTurnCounter < 0xFF)
        ++gBattleResults.battleTurnCounter;

    for (i = 0; i < gBattlersCount; ++i)
    {
        gChosenActionByBattler[i] = B_ACTION_NONE;
        gChosenMoveByBattler[i] = MOVE_NONE;
    }
    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        *(gBattleStruct->monToSwitchIntoId + i) = PARTY_SIZE;

    *(&gBattleStruct->absentBattlerFlags) = gAbsentBattlerFlags;
    GetAiLogicData(); // get assumed abilities, hold effects, etc of all battlers
    gBattleMainFunc = HandleTurnActionSelectionState;
    gRandomTurnNumber = Random();
}

#define RUN_LOGIC_PT1 //realized this isn't same as being able to switch need set that up
u8 IsRunningFromBattleImpossible(void) // equal to emerald is ability preventing escape  put logic in here.
{
    u8 holdEffect;
    u8 side;
    s32 i;
    u8 battler;

    if (gBattleMons[gActiveBattler].item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[gActiveBattler].holdEffect;
    else
        holdEffect = GetBattlerHoldEffect(gActiveBattler, TRUE);
    gPotentialItemEffectBattler = gActiveBattler;

    if (holdEffect == HOLD_EFFECT_CAN_ALWAYS_RUN
     || (gBattleTypeFlags & BATTLE_TYPE_LINK)
     || (GetBattlerAbility(gActiveBattler) == ABILITY_RUN_AWAY) //
     || (GetBattlerAbility(gActiveBattler) == ABILITY_AVIATOR) //
     || (GetBattlerAbility(gActiveBattler) == ABILITY_DEFEATIST //
         && gDisableStructs[gActiveBattler].defeatistActivated) //
     || holdEffect == HOLD_EFFECT_SHED_SHELL
     || IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_GHOST)
     || (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))) //added cuz issue created with adding shadow tag to gastly
        return BATTLE_RUN_SUCCESS;
    
    /*side = GetBattlerSide(gActiveBattler);
    for (i = 0; i < gBattlersCount; ++i)
    {
        if (/*side != GetBattlerSide(i)
         && IsAbilityOnOpposingSide(i, ABILITY_SHADOW_TAG)
         && gBattleMons[i].ability == ABILITY_SHADOW_TAG //since shadow tag is like an exorcism talismon 
            IsAbilityOnOpposingSide(i, ABILITY_SHADOW_TAG)
         && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_GHOST))//meant to keep spirits from escaping it makes sense for shadow tag
            // to still lock in ghost types
        {
            //gBattleScripting.battler = i;
            gBattleScripting.battler = battler = IsAbilityOnOpposingSide(i, ABILITY_SHADOW_TAG);
            //gLastUsedAbility = gBattleMons[i].ability;
            gLastUsedAbility = gBattleMons[battler].ability;
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;//shadow tag isn't an exorcism talisom based on translation its the ghost posessing your shadow, keeping you from moving
            return BATTLE_RUN_FAILURE;  //like seen in horror or movies ghost touching your shadow affects person, logic behind it not affecting ghost is I guess ghosts don't have shadows
        }
        if (side != GetBattlerSide(i)
         && gBattleMons[gActiveBattler].ability != ABILITY_LEVITATE
         && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_FLYING)
         && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_GHOST)
         && gBattleMons[i].ability == ABILITY_ARENA_TRAP
         IsAbilityOnOpposingSide(i, ABILITY_ARENA_TRAP)
         && IsBattlerGrounded(gActiveBattler)) //need add grounded check for flying  vsonic
        {
            //gBattleScripting.battler = i;
            gBattleScripting.battler = battler = IsAbilityOnOpposingSide(i, ABILITY_ARENA_TRAP);
            //gLastUsedAbility = gBattleMons[i].ability;
            gLastUsedAbility = gBattleMons[battler].ability;
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            return BATTLE_RUN_FAILURE;
        }
    }*/
    if (IsAbilityPreventingEscape(gActiveBattler)) //if works can remove i, and side
    {
        gBattleScripting.battler = battler = (IsAbilityPreventingEscape(gActiveBattler) - 1);
        gLastUsedAbility = gBattleMons[battler].ability;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        return BATTLE_RUN_FAILURE;
    }
    /*i = AbilityBattleEffects(ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER, gActiveBattler, ABILITY_MAGNET_PULL, 0, 0);
    if (i != 0 && IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_STEEL))
    {
        gBattleScripting.battler = i - 1;
        gLastUsedAbility = gBattleMons[i - 1].ability;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        return BATTLE_RUN_FAILURE;
    }*/
    //vsonic IMPORTANT do search, for status2_wrapped & wrappedby  implement new trap checks where it makes sense
    //similar to as below
    /*if ((gBattleMons[gActiveBattler].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_SWITCH_LOCKED | STATUS2_WRAPPED))//vsonic need add new trap status here
     || (gBattleMons[gActiveBattler].status4 & (ITS_A_TRAP_STATUS4)
     || (gStatuses3[gActiveBattler] & STATUS3_ROOTED)
     || (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)))*///I need to redo this setup,
     /*|| (!IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_GHOST)
        && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_FLYING))*/
     //&& IsBattlerGrounded(gActiveBattler)) // I made it impossible to flee unless not gronded because I used or instead of and -__
     //undid grouding logic potentally too destabalizing for balance
     //but primarily if they are in the trap then they should be trapped
     //also having easy/early access to free escape would cause pathing issues
     //and trivialize early difficult
    if (!CanBattlerEscape(gActiveBattler))
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        return BATTLE_RUN_FORBIDDEN;
    }//more research switch lock shouldn't have to do w grounding
    //unless ghosts if closs to groud they should have a shadow floating or not
    //double check floating list, think may have made prerequisite
    //they could actually leave the groud and float to a greater height?
    //if so theyn floating works as a flying type standin
    //past 350 floating mon, and sub 150 of that is flyign type


    //thought  separate STATUS2_SWITCH_LOCKED  as effect shouldn't have to do w grounding
    //since its spirit based could also make it only affect that could lock ghosts hmm
    //looked up move description and no, it works exactly as shadow tag does
    //it works by stiching to shadow on the ground

    if (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE)
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        return BATTLE_RUN_FORBIDDEN;
    }
    return BATTLE_RUN_SUCCESS;
}

void UpdatePartyOwnerOnSwitch_NonMulti(u8 battler)
{
    s32 i;
    u8 r4, r1;

    for (i = 0; i < 3; ++i)
        gBattlePartyCurrentOrder[i] = *(battler * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders));
    r4 = GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[battler]);
    r1 = GetPartyIdFromBattlePartyId(*(gBattleStruct->monToSwitchIntoId + battler));
    SwitchPartyMonSlots(r4, r1);
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        for (i = 0; i < 3; ++i)
        {
            *(battler * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
            *(BATTLE_PARTNER(battler) * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
        }
    }
    else
    {
        for (i = 0; i < 3; ++i)
            *(battler * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
    }
}

enum
{
    STATE_TURN_START_RECORD,
    STATE_BEFORE_ACTION_CHOSEN,
    STATE_WAIT_ACTION_CHOSEN,
    STATE_WAIT_ACTION_CASE_CHOSEN,
    STATE_WAIT_ACTION_CONFIRMED_STANDBY,
    STATE_WAIT_ACTION_CONFIRMED,
    STATE_SELECTION_SCRIPT,
    STATE_WAIT_SET_BEFORE_ACTION,
};

#define TURN_ACTIONS_SWITCH_ETC

static void HandleTurnActionSelectionState(void) //think need add case for my swith action
{
    s32 i;

    gBattleCommunication[ACTIONS_CONFIRMED_COUNT] = 0;
    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
    {
        u8 position = GetBattlerPosition(gActiveBattler);

        switch (gBattleCommunication[gActiveBattler])
        {
        case STATE_TURN_START_RECORD: // Recorded battle related action on start of every turn.
            //RecordedBattle_CopyBattlerMoves(gActiveBattler); //added back when add recordedbattle files, will need for test system believe
            gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;

            // Do AI score computations here so we can use them in AI_TrySwitchOrUseItem
            if ((gBattleTypeFlags & BATTLE_TYPE_HAS_AI || IsWildMonSmart()) && IsBattlerAIControlled(gActiveBattler)) {
                gBattleStruct->aiMoveOrAction[gActiveBattler] = ComputeBattleAiScores(gActiveBattler);
            }
            //break;
            // fallthrough
        case STATE_BEFORE_ACTION_CHOSEN: // Choose an action.
            *(gBattleStruct->monToSwitchIntoId + gActiveBattler) = PARTY_SIZE;
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI
             || (position & BIT_FLANK) == B_FLANK_LEFT
             || gBattleStruct->absentBattlerFlags & gBitTable[GetBattlerAtPosition(BATTLE_PARTNER(position))]
             || gBattleCommunication[GetBattlerAtPosition(BATTLE_PARTNER(position))] == STATE_WAIT_ACTION_CONFIRMED) //partner already chose action
            {
                if (gBattleStruct->absentBattlerFlags & gBitTable[gActiveBattler])
                {
                    gChosenActionByBattler[gActiveBattler] = B_ACTION_NOTHING_FAINTED;
                    if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED;
                    else
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                }
                else
                {
                    //believe this change should do what I want,
                    //of not skipping player choice if need recharge
                    //should allow player choose action, good it works perfectly
                    if (gBattleMons[gActiveBattler].status2 & STATUS2_MULTIPLETURNS)
                    // || gDisableStructs[gActiveBattler].rechargeTimer)
                    {
                        gChosenActionByBattler[gActiveBattler] = B_ACTION_USE_MOVE; //skip to use move
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                    }
                    else
                    {
                        BtlController_EmitChooseAction(0, gChosenActionByBattler[0], gBattleBufferB[0][1] | (gBattleBufferB[0][2] << 8));
                        MarkBattlerForControllerExec(gActiveBattler);
                        ++gBattleCommunication[gActiveBattler];
                    }
                }
            }
            break;
        case STATE_WAIT_ACTION_CHOSEN: // Try to perform an action. //i.e selection from fight,pokemon,item/run
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF << 28) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
            {
                //passes selected action, to gchosen for next link in action chain, 
                //present task identify process to fix bind, then return to dex
                gChosenActionByBattler[gActiveBattler] = gBattleBufferB[gActiveBattler][1];
                switch (gBattleBufferB[gActiveBattler][1])
                {
                case B_ACTION_USE_MOVE:
                    //this calls util  CheckMoveLimitations  function
                    if (AreAllMovesUnusable())//think was same issue as other place w struggle set
                    {
                        gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                        *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                        *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                        *(gBattleStruct->moveTarget + gActiveBattler) = gBattleBufferB[gActiveBattler][3];
                        return;
                    }
                    else if (gDisableStructs[gActiveBattler].encoredMove != MOVE_NONE)
                    {
                        gChosenMoveByBattler[gActiveBattler] = gDisableStructs[gActiveBattler].encoredMove;
                        *(gBattleStruct->chosenMovePositions + gActiveBattler) = gDisableStructs[gActiveBattler].encoredMovePos;
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                        return;
                    }
                    //else if (gDisableStructs[gActiveBattler].bindedMove != MOVE_NONE) //ok now undersetand these are fail conditinons nvm was wrong...
                    else if (gBattleMons[gActiveBattler].status4 & STATUS4_BIND)// && (gDisableStructs[gActiveBattler].bindedMove != MOVE_NONE)) //conditions shuold be more or less on same level don' tknow why this one fails
                    {
                        gChosenMoveByBattler[gActiveBattler] = gDisableStructs[gActiveBattler].bindedMove;
                        *(gBattleStruct->chosenMovePositions + gActiveBattler) = gDisableStructs[gActiveBattler].bindMovepos; //without this fainted logic works??
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                        return;
                    }  //working
                    else
                    {
                        struct ChooseMoveStruct moveInfo;

                        moveInfo.species = gBattleMons[gActiveBattler].species;
                        moveInfo.monType1 = gBattleMons[gActiveBattler].type1;
                        moveInfo.monType2 = gBattleMons[gActiveBattler].type2;
                        for (i = 0; i < MAX_MON_MOVES; ++i)
                        {
                            moveInfo.moves[i] = gBattleMons[gActiveBattler].moves[i];
                            moveInfo.currentPp[i] = gBattleMons[gActiveBattler].pp[i];
                            moveInfo.maxPp[i] = CalculatePPWithBonus(gBattleMons[gActiveBattler].moves[i],
                                                                     gBattleMons[gActiveBattler].ppBonuses,
                                                                     i);
                        }
                        BtlController_EmitChooseMove(0, (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) != 0, FALSE, &moveInfo);
                        MarkBattlerForControllerExec(gActiveBattler); //unsure what above means? but its default?
                    }//I'm guessing means if double battle? if double battle flag is set?
                    break;
                case B_ACTION_USE_ITEM:
                    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER))
                    {
                        gSelectionBattleScripts[gActiveBattler] = BattleScript_ActionSelectionItemsCantBeUsed;
                        gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                        *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                        *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_BEFORE_ACTION_CHOSEN;
                        return;
                    }
                    else
                    {
                        BtlController_EmitChooseItem(0, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                    break;
                case B_ACTION_SWITCH:   //vsonic this is part that allows switch, looks like I already setup
                    *(gBattleStruct->battlerPartyIndexes + gActiveBattler) = gBattlerPartyIndexes[gActiveBattler];
                    if (!CanBattlerEscape(gActiveBattler))
                        BtlController_EmitChoosePokemon(0, PARTY_ACTION_CANT_SWITCH, 6, ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                    //uturn hit escape effects already work don't need add special logic here
                    else if (IsAbilityPreventingEscape(gActiveBattler))
                        BtlController_EmitChoosePokemon(0, ((i - 1) << 4) | PARTY_ACTION_ABILITY_PREVENTS, 6, GetBattlerAbility(IsAbilityPreventingEscape(gActiveBattler) - 1), gBattleStruct->battlerPartyOrders[gActiveBattler]);
                     //think issue is using  glastusedability, with being able to switch out, seems to mess withthe buffers, seems to have fixed it
                    else //can switch
                    {
                        if (gActiveBattler == 2 && gChosenActionByBattler[0] == B_ACTION_SWITCH)
                            BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 0), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        else if (gActiveBattler == 3 && gChosenActionByBattler[1] == B_ACTION_SWITCH)
                            BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 1), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        else
                            BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, 6, ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                    }
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case B_ACTION_SAFARI_BALL:
                    if (IsPlayerPartyAndPokemonStorageFull())
                    {
                        gSelectionBattleScripts[gActiveBattler] = BattleScript_PrintFullBox;
                        gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                        *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                        *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_BEFORE_ACTION_CHOSEN;
                        return;
                    }
                    break;
                case B_ACTION_CANCEL_PARTNER:
                    gBattleCommunication[gActiveBattler] = STATE_WAIT_SET_BEFORE_ACTION;
                    gBattleCommunication[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gActiveBattler)))] = STATE_BEFORE_ACTION_CHOSEN;
                    BtlController_EmitEndBounceEffect(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                    return;
                case B_ACTION_DEBUG:
                    BtlController_EmitDebugMenu(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case B_ACTION_MOVE_INFO:
                    BtlController_EmitMoveInfo(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                }//vsonic
                
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
                 && !(gBattleTypeFlags & BATTLE_TYPE_LINK)
                 && gBattleBufferB[gActiveBattler][1] == B_ACTION_RUN)
                {
                    BattleScriptExecute(BattleScript_PrintCantRunFromTrainer);
                    gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                }
                else if (IsRunningFromBattleImpossible() != BATTLE_RUN_SUCCESS
                      && gBattleBufferB[gActiveBattler][1] == B_ACTION_RUN)
                {
                    gSelectionBattleScripts[gActiveBattler] = BattleScript_PrintCantEscapeFromBattle;
                    gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                    *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                    *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_BEFORE_ACTION_CHOSEN;
                    return;
                }
                else
                {
                    ++gBattleCommunication[gActiveBattler];
                }
            }
            break;
        case STATE_WAIT_ACTION_CASE_CHOSEN:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
            {
                switch (gChosenActionByBattler[gActiveBattler])
                {
                case B_ACTION_USE_MOVE:
                    switch (gBattleBufferB[gActiveBattler][1]) //values 3 -9 don't know what are?
                    {
                    case 3 ... 9:
                        gChosenActionByBattler[gActiveBattler] = gBattleBufferB[gActiveBattler][1];
                        return;
                    default:
                        if ((gBattleBufferB[gActiveBattler][2] | (gBattleBufferB[gActiveBattler][3] << 8)) == 0xFFFF)
                        {
                            gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                        }
                        else if (TrySetCantSelectMoveBattleScript()) //if not vali move
                        {
                            gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                            *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                            gBattleBufferB[gActiveBattler][1] = 0;
                            *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_WAIT_ACTION_CHOSEN;
                            return;
                        }
                        else
                        {
                            *(gBattleStruct->chosenMovePositions + gActiveBattler) = gBattleBufferB[gActiveBattler][2];
                            gChosenMoveByBattler[gActiveBattler] = gBattleMons[gActiveBattler].moves[*(gBattleStruct->chosenMovePositions + gActiveBattler)];
                            *(gBattleStruct->moveTarget + gActiveBattler) = gBattleBufferB[gActiveBattler][3];
                            ++gBattleCommunication[gActiveBattler];
                        }
                        break;
                    }
                    break;
                case B_ACTION_USE_ITEM:
                    if ((gBattleBufferB[gActiveBattler][1] | (gBattleBufferB[gActiveBattler][2] << 8)) == 0)
                    {
                        gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                    }
                    else
                    {
                        gLastUsedItem = (gBattleBufferB[gActiveBattler][1] | (gBattleBufferB[gActiveBattler][2] << 8));
                        ++gBattleCommunication[gActiveBattler];
                    }
                    break;
                case B_ACTION_SWITCH:
                    if (gBattleBufferB[gActiveBattler][1] == PARTY_SIZE)
                    {
                        gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                    }
                    else
                    {
                        *(gBattleStruct->monToSwitchIntoId + gActiveBattler) = gBattleBufferB[gActiveBattler][1];
                        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        {
                            *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) &= 0xF;
                            *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) |= (gBattleBufferB[gActiveBattler][2] & 0xF0);
                            *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 1) = gBattleBufferB[gActiveBattler][3];
                            *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) &= (0xF0);
                            *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) |= (gBattleBufferB[gActiveBattler][2] & 0xF0) >> 4;
                            *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 2) = gBattleBufferB[gActiveBattler][3];
                        }
                        ++gBattleCommunication[gActiveBattler];
                    }
                    break;
                case B_ACTION_RUN:
                    gHitMarker |= HITMARKER_RUN;
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_WATCH_CAREFULLY:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_BALL:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_BAIT:
                case B_ACTION_SAFARI_GO_NEAR:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_RUN:
                    gHitMarker |= HITMARKER_RUN;
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_OLDMAN_THROW:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_DEBUG:
                    gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                    break;
                case B_ACTION_MOVE_INFO:
                    gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                    break;
                }
            }
            break;
        case STATE_WAIT_ACTION_CONFIRMED_STANDBY:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
            {
                if (((gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_DOUBLE)) != BATTLE_TYPE_DOUBLE)
                 || (position & BIT_FLANK) != B_FLANK_LEFT
                 || (*(&gBattleStruct->absentBattlerFlags) & gBitTable[GetBattlerAtPosition(position ^ BIT_FLANK)]))
                    BtlController_EmitLinkStandbyMsg(0, 0);
                else
                    BtlController_EmitLinkStandbyMsg(0, 1);
                MarkBattlerForControllerExec(gActiveBattler);
                ++gBattleCommunication[gActiveBattler];
            }
            break;
        case STATE_WAIT_ACTION_CONFIRMED:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
                ++gBattleCommunication[ACTIONS_CONFIRMED_COUNT];
            break;
        case STATE_SELECTION_SCRIPT:
            if (*(gBattleStruct->selectionScriptFinished + gActiveBattler))
            {
                gBattleCommunication[gActiveBattler] = *(gBattleStruct->stateIdAfterSelScript + gActiveBattler);
            }
            else
            {
                gBattlerAttacker = gActiveBattler;
                gBattlescriptCurrInstr = gSelectionBattleScripts[gActiveBattler];
                if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
                    gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
                gSelectionBattleScripts[gActiveBattler] = gBattlescriptCurrInstr;
            }
            break;
        case STATE_WAIT_SET_BEFORE_ACTION:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
                gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
            break;
        }
    }
    // Check if everyone chose actions.
    if (gBattleCommunication[ACTIONS_CONFIRMED_COUNT] == gBattlersCount)
        gBattleMainFunc = SetActionsAndBattlersTurnOrder;
}

void SwapTurnOrder(u8 id1, u8 id2)
{
    u32 temp;

    SWAP(gActionsByTurnOrder[id1], gActionsByTurnOrder[id2], temp);
    SWAP(gBattlerByTurnOrder[id1], gBattlerByTurnOrder[id2], temp);
}

u32 GetBattlerTotalSpeedStat(u8 battlerId)
{
    u32 speed = gBattleMons[battlerId].speed; //activebattler /attacker
    u32 targetspeed = gBattleMons[gBattlerTarget].speed; //may work may not, for now use ability on opposing field
    u32 ability = GetBattlerAbility(battlerId);
    u32 partnerability = GetBattlerAbility(BATTLE_PARTNER(battlerId));
    u32 holdEffect = GetBattlerHoldEffect(battlerId, TRUE);
    u32 highestStat = GetHighestStatId(battlerId);  //3was for protosynthesis will use for ultranerozma move instead i think

    // weather abilities
    if (ability == ABILITY_SWIFT_SWIM && IsBattlerWeatherAffected(battlerId, WEATHER_RAIN_ANY))
        speed *= 2;
    else if (ability == ABILITY_CHLOROPHYLL && IsBattlerWeatherAffected(battlerId, WEATHER_SUN_ANY))
        speed *= 2;
    else if (ability == ABILITY_SAND_RUSH && IsBattlerWeatherAffected(battlerId, WEATHER_SANDSTORM_ANY))
        speed *= 2;
    else if (ability == ABILITY_SLUSH_RUSH && IsBattlerWeatherAffected(battlerId, WEATHER_HAIL))
        speed *= 2;
    else if (ability == ABILITY_FLUORESCENCE && IsBattlerWeatherAffected(battlerId, WEATHER_SUN_ANY))
        speed = (speed * 150) / 100;


    // other abilities
    if (ability == ABILITY_QUICK_FEET && gBattleMons[battlerId].status1 & STATUS1_ANY)
        speed = (speed * 150) / 100;
    else if (ability == ABILITY_TANGLED_FEET && gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
        speed = (speed * 150) / 100;
    else if (ability == ABILITY_SURGE_SURFER && gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
        speed *= 2;
    else if (ability == ABILITY_SLOW_START && gBattleStruct->SingleUseAbilityTimers[gBattlerPartyIndexes[battlerId]][GetBattlerSide(battlerId)] != 0)
        speed /= 2;

    else if (ability == ABILITY_DEFEATIST && gDisableStructs[battlerId].defeatistActivated)
        speed *= 2;

    //think want to change how this works, point is to raise speed like getting serious,
    //but dont want to lower speed again if they heal
    //on the other hand if i do it this way it still opens me up to stat stage speedboosts
    //ok what I can do is set it to use,  usedsingleuseability, so the speed boost would stay
    //for the whole fight //makes more sense practically but isthat too strong??
    //probably is, for regular game its pretty much free, rather than having
    //to potentially think around pivot itd just be play get hit, switch out, heal,
    //blast through everything potentially without getting touched
    //ok middle ground will set disable struct, so it resets on faint or switch
    else if (ability == ABILITY_WEIGHTED_GI)
    { 
        if (gBattleMons[battlerId].hp <= (gBattleMons[battlerId].maxHP / 2) && !gDisableStructs[battlerId].ActivatedWeightedGi)
            gDisableStructs[battlerId].ActivatedWeightedGi = TRUE;
         //   gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[battlerId]][GetBattlerSide(battlerId)] = TRUE; 

        //if (gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[battlerId]][GetBattlerSide(battlerId)] == TRUE)
        if (gDisableStructs[battlerId].ActivatedWeightedGi)
            speed *= 2; //speed = (speed * 150) / 100; unsure which stick with
    }

    if (IsAbilityOnField(ABILITY_TABLETS_OF_RUIN) && GetBattlerAbility(battlerId) != ABILITY_TABLETS_OF_RUIN)
        speed = (speed * 75) / 100;  //wo chien ability buff
        

    if (ability == ABILITY_VICTORY_STAR
    ||  partnerability == ABILITY_VICTORY_STAR) //gave speed buff rather than crit or dmg, sinc acc & speed are biggest factors for victory usually
        speed = (speed * 120) / 100;    //extra synergy with wo chien

    if (IsAbilityPreventingEscape(battlerId)) //realize this need be an if, to always trigger
        speed = (speed * 67) / 100; //buff for all of category, magnet pull, arena trap, shadow tag  /equivalent to 1 stage drop
    
    //gen 9 //-protosynthesis requires gen9 item Booster Energy to be complete accurate
    else if (ability == ABILITY_PROTOSYNTHESIS && IsBattlerWeatherAffected(battlerId, WEATHER_SUN_ANY) && highestStat == STAT_SPEED)
        speed = (speed * 150) / 100;
    else if (ability == ABILITY_QUARK_DRIVE && IsBattlerTerrainAffected(battlerId, STATUS_FIELD_ELECTRIC_TERRAIN) && highestStat == STAT_SPEED)
        speed = (speed * 150) / 100;

        // stat stages
    speed *= gStatStageRatios[gBattleMons[battlerId].statStages[STAT_SPEED]][0];
    speed /= gStatStageRatios[gBattleMons[battlerId].statStages[STAT_SPEED]][1];

    // player's badge boost
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK)
        && FlagGet(FLAG_BADGE03_GET)
        && GetBattlerSide(battlerId) == B_SIDE_PLAYER)
    {
        speed = (speed * 110) / 100;
    }

    // item effects
    if ((holdEffect == HOLD_EFFECT_MACHO_BRACE 
    || holdEffect == HOLD_EFFECT_ULTIMA_BRACE 
    || holdEffect ==  HOLD_EFFECT_POWERITEM)
    && (ability != ABILITY_TANGLED_FEET
    && ability != ABILITY_AVIATOR
    && ability != ABILITY_RUN_AWAY
    && ability != ABILITY_QUICK_FEET
            ))
        speed /= 2;

    else if (holdEffect == HOLD_EFFECT_IRON_BALL) //MADE float stone counterpart to iron ball
        speed /= 2;
    else if (IS_BATTLER_OF_TYPE(battlerId, TYPE_ROCK) && holdEffect == HOLD_EFFECT_FLOAT_STONE)
        speed = (speed * 150) / 100;
    else if (holdEffect == HOLD_EFFECT_CHOICE_SCARF)
        speed = (speed * 150) / 100;
    else if (holdEffect == HOLD_EFFECT_QUICK_POWDER && gBattleMons[battlerId].species == SPECIES_DITTO /*&& !(gBattleMons[battlerId].status2 & STATUS2_TRANSFORMED)*/)
        speed *= 2; //fix so keep speed boost even when transformed

    // various effects
    if (gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_TAILWIND)
        speed *= 2;
    if (gBattleResources->flags->flags[battlerId] & RESOURCE_FLAG_UNBURDEN)
        speed *= 2;
    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_GRASS) && (gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_WATERSPORT)) //give to more grass types
        speed = (speed * 150) / 100; //should prob make grass specific text string, i.e x became revitalized

    // paralysis drop
    if ((gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
        && (ability != ABILITY_QUICK_FEET
            && ability != ABILITY_TANGLED_FEET
            && ability != ABILITY_AVIATOR
            && ability != ABILITY_RUN_AWAY
            )
        && IsBlackFogNotOnField())
        speed /= 4;

    //trap effects
    if ((gBattleMons[battlerId].status4 & STATUS4_WHIRLPOOL)
        && IsBlackFogNotOnField())  //should be good
        speed /= 2; //cut speed by half, which is the same as 2 stat stage drops & guess it makes more sense to cut 
    if ((gBattleMons[battlerId].status2 & STATUS2_WRAPPED)
        && IsBlackFogNotOnField())
        speed /= 2; //cut speed by half, which is the same as 2 stat stage drops & guess it makes more sense to cut 

    return speed;
}

// Sort an array of battlers by speed
// Useful for effects like pickpocket, eject button, red card, dancer
//-personal note, need update getbattlertotalspeedstat  from getwhostriksfirst, or just use that
//these loop all battlers, getwhotrikesfirst only uses 2, so prob need to adapat that function to use just 1 battler
//argument and loop gbattlerscount
void SortBattlersBySpeed(u8 *battlers, bool8 slowToFast)
{
    int i, j, currSpeed, currBattler;
    u16 speeds[4] = {0};

    for (i = 0; i < gBattlersCount; i++)
        speeds[i] = GetBattlerTotalSpeedStat(battlers[i]);

    for (i = 1; i < gBattlersCount; i++)
    {
        currBattler = battlers[i];
        currSpeed = speeds[i];
        j = i - 1;

        if (slowToFast)
        {
            while (j >= 0 && speeds[j] > currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && speeds[j] < currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }

        battlers[j + 1] = currBattler;
        speeds[j + 1] = currSpeed;
    }
}

//updating to emerald standard, remove speed checks to getbattlertotalspeed intead
//remove badge boosts, ability checks other than quick draw, and status effects
//DONE, 
//also //realized it only holds 2 battlers, so how does it work for doubles?
//could be reads one side ata time, need check 
u8 GetWhoStrikesFirst(u8 battler1, u8 battler2, bool8 ignoreChosenMoves) 
{
    u8 strikesFirst = 0;
    u32 speedBattler1 = 0, speedBattler2 = 0;
    u32 holdEffectBattler1 = 0, holdEffectBattler2 = 0;
    u8 holdEffectParam1 = 0,holdEffectParam2 = 0;

    s8 priority1 = 0, priority2 = 0;
    u16 ability1 = GetBattlerAbility(battler1);
    u16 ability2 = GetBattlerAbility(battler2);

    
    // Battler 1
    speedBattler1 = GetBattlerTotalSpeedStat(battler1);
    holdEffectBattler1 = GetBattlerHoldEffect(battler1, TRUE);
    holdEffectParam1 = ItemId_GetHoldEffectParam(gBattleMons[battler1].item);
  
    
    //Quick Claw        //ok works now, but doesnt' have activation animation, and even at 40% odds are still pretty lackluster 60% is slihtly too much  55 feels good
    if ((holdEffectBattler1 == HOLD_EFFECT_QUICK_CLAW && gRandomTurnNumber < (0xFFFF * holdEffectParam1) / 100)   //buffed param to 45% rathre than 20
        || (holdEffectBattler1 == HOLD_EFFECT_CUSTAP_BERRY && HasEnoughHpToEatBerry(battler1, 4, gBattleMons[battler1].item)))
        gProtectStructs[battler1].usedCustapBerry = TRUE; //realize used wrong values for battler 2 may be issue here/seems to have fixed? yup


    // Quick Draw
    if (!ignoreChosenMoves && ability1 == ABILITY_QUICK_DRAW && !IS_MOVE_STATUS(gChosenMoveByBattler[battler1]) && Random() % 100 < 30)
        gProtectStructs[battler1].quickDraw = TRUE;   //pretty sure can use this rather than needing take memory for struc
        //gProtectStructs[battler1].quickDraw = TRUE;

    // check second battlerId's speed
    // Battler 2
    speedBattler2 = GetBattlerTotalSpeedStat(battler2);
    holdEffectBattler2 = GetBattlerHoldEffect(battler2, TRUE);
    holdEffectParam2 = ItemId_GetHoldEffectParam(gBattleMons[battler2].item);
    
    // Quick Claw
    if ((holdEffectBattler2 == HOLD_EFFECT_QUICK_CLAW && gRandomTurnNumber < (0xFFFF * holdEffectParam2) / 100)   //buffed param to 45% rathre than 20
        || (holdEffectBattler2 == HOLD_EFFECT_CUSTAP_BERRY && HasEnoughHpToEatBerry(battler2, 4, gBattleMons[battler2].item)))
        gProtectStructs[battler2].usedCustapBerry = TRUE;
    // Quick Draw
    if (!ignoreChosenMoves && ability2 == ABILITY_QUICK_DRAW && !IS_MOVE_STATUS(gChosenMoveByBattler[battler2]) && Random() % 100 < 30)
        gProtectStructs[battler2].quickDraw = TRUE; //like how came out, item versino has better odds since it takes up an item slot, 

    if (!ignoreChosenMoves)
    {
        if (gChosenActionByBattler[battler1] == B_ACTION_USE_MOVE)
            priority1 = GetChosenMovePriority(battler1);
        if (gChosenActionByBattler[battler2] == B_ACTION_USE_MOVE)
            priority2 = GetChosenMovePriority(battler2);
    }
    
    // both move priorities are different than 0
    if (priority1 == priority2)
    {
        // both priorities are the same

        
                // QUICK CLAW / CUSTAP - always first
                // LAGGING TAIL - always last
                // STALL - always last
        if (gProtectStructs[battler1].quickDraw && !gProtectStructs[battler2].quickDraw)
            strikesFirst = USER_FIRST;
        else if (!gProtectStructs[battler1].quickDraw && gProtectStructs[battler2].quickDraw)
            strikesFirst = BATTLER_FIRST;
        else if (gProtectStructs[battler1].usedCustapBerry && !gProtectStructs[battler2].usedCustapBerry)
            strikesFirst = USER_FIRST;
        else if (gProtectStructs[battler2].usedCustapBerry && !gProtectStructs[battler1].usedCustapBerry)
            strikesFirst = BATTLER_FIRST;
        /*else if (holdEffectBattler1 == HOLD_EFFECT_LAGGING_TAIL && holdEffectBattler2 != HOLD_EFFECT_LAGGING_TAIL)
            strikesFirst = 1;
        else if (holdEffectBattler2 == HOLD_EFFECT_LAGGING_TAIL && holdEffectBattler1 != HOLD_EFFECT_LAGGING_TAIL)
            strikesFirst = 0;
        else if (ability1 == ABILITY_STALL && ability2 != ABILITY_STALL)
            strikesFirst = 1;
        else if (ability2 == ABILITY_STALL && ability1 != ABILITY_STALL)
            strikesFirst = 0;*/
        else //trick room logic below to explicitly exclude above  affects from calculation
        {
            if (speedBattler1 == speedBattler2 && Random() & 1)
            {
                //same speed - 
                if (IsStallActive(battler1) && !IsStallActive(battler2))
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = USER_FIRST;
                    else
                        strikesFirst = BATTLER_FIRST;
                }
                else if (IsStallActive(battler2) && !IsStallActive(battler1))
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = BATTLER_FIRST;
                    else
                        strikesFirst = USER_FIRST;
                }
                else
                    strikesFirst = SPEED_TIE; // same speeds, same priorities  is there a point in it being 2?  dont think so, effect is same other than separating it from the normal effect logic
            }
                

            else if (speedBattler1 < speedBattler2)
            {
                // battler2 has more speed
                if (IsStallActive(battler1) && !IsStallActive(battler2))
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = USER_FIRST;
                    else
                        strikesFirst = BATTLER_FIRST;
                }
                else if (IsStallActive(battler2) && !IsStallActive(battler1))
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = BATTLER_FIRST;
                    else
                        strikesFirst = USER_FIRST;
                }
                else //applies for both have ability and neither have ability
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = USER_FIRST;
                    else
                        strikesFirst = BATTLER_FIRST;
                }               
                
            }
            else
            {
                // battler1 has more speed
                if (IsStallActive(battler1) && !IsStallActive(battler2))
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = USER_FIRST;
                    else
                        strikesFirst = BATTLER_FIRST;
                }
                else if (IsStallActive(battler2) && !IsStallActive(battler1))
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = BATTLER_FIRST;
                    else
                        strikesFirst = USER_FIRST;
                }
                else //applies for both have ability and neither have ability
                {
                    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
                        strikesFirst = BATTLER_FIRST;
                    else
                        strikesFirst = USER_FIRST;
                }
                
            }
        }//almost working how I want, but previously worked by setting to -12 priority for dmg moves
        //meaning could avoid the effects of low priority moves that only work by going last
        //previously was -12 priority at base, check existing negative priority moves to see what is best
    }
    else if (priority1 < priority2)
    {    
        //effect to get to move last regardless of priority, so can ignore
        //moves that activate only when moving last such as counter, would work for that,
        //but add draw back that priority moves are worthles,
        //and outside of trick room, would be completely coutered by force switch moves
        //i.e things like dragon tail which would otherwise move last, but switch out the target
        if (IsStallActive(battler2)
        && (!(gFieldStatuses & STATUS_FIELD_TRICK_ROOM)))
            strikesFirst = USER_FIRST;
        else
            strikesFirst = BATTLER_FIRST; // battler2's move has greater priority
    }
    else
    {    
        if (IsStallActive(battler1)
        && (!(gFieldStatuses & STATUS_FIELD_TRICK_ROOM)))
            strikesFirst = BATTLER_FIRST;
        else
            strikesFirst = USER_FIRST; // battler1's move has greater priority   //why is battler1 (me) strikingfirst default to false for when the condition is true? 
                            //that's just confusing 
                            //reason is its not a conditional, its a state check, 0,1,2 not true false
    }
    

    return strikesFirst;
}

static void SetActionsAndBattlersTurnOrder(void)
{
    s32 turnOrderId = 0;
    s32 i, j;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[gActiveBattler];
            gBattlerByTurnOrder[turnOrderId] = gActiveBattler;
            ++turnOrderId;
        }
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_RUN)
                {
                    turnOrderId = 5;
                    break;
                }
            }
        }
        else if (gChosenActionByBattler[0] == B_ACTION_RUN)
        {
            gActiveBattler = 0;
            turnOrderId = 5;
        }
        if (turnOrderId == 5) // One of battlers wants to run.
        {
            gActionsByTurnOrder[0] = gChosenActionByBattler[gActiveBattler];
            gBattlerByTurnOrder[0] = gActiveBattler;
            turnOrderId = 1;
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (i != gActiveBattler)
                {
                    gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[i];
                    gBattlerByTurnOrder[turnOrderId] = i;
                    ++turnOrderId;
                }
            }
            gBattleMainFunc = CheckFocusPunch_ClearVarsBeforeTurnStarts;//   removed here put at end
            //gBattleStruct->focusPunchBattlerId = 0;
            return;
        }
        else
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_USE_ITEM || gChosenActionByBattler[gActiveBattler] == B_ACTION_SWITCH)
                {
                    gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[gActiveBattler];
                    gBattlerByTurnOrder[turnOrderId] = gActiveBattler;
                    ++turnOrderId;
                }
            }
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gChosenActionByBattler[gActiveBattler] != B_ACTION_USE_ITEM && gChosenActionByBattler[gActiveBattler] != B_ACTION_SWITCH)
                {
                    gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[gActiveBattler];
                    gBattlerByTurnOrder[turnOrderId] = gActiveBattler;
                    ++turnOrderId;
                }
            }
            for (i = 0; i < gBattlersCount - 1; ++i)
            {
                for (j = i + 1; j < gBattlersCount; ++j)
                {
                    u8 battler1 = gBattlerByTurnOrder[i];
                    u8 battler2 = gBattlerByTurnOrder[j];

                    if (gActionsByTurnOrder[i] != B_ACTION_USE_ITEM
                     && gActionsByTurnOrder[j] != B_ACTION_USE_ITEM
                     && gActionsByTurnOrder[i] != B_ACTION_SWITCH
                     && gActionsByTurnOrder[j] != B_ACTION_SWITCH)
                        if (GetWhoStrikesFirst(battler1, battler2, FALSE))
                            SwapTurnOrder(i, j);
                }
            }
        }
    }//emerald replaced below with CheckQuickClaw_CustapBerryActivation & gBattleStruct->quickClawBattlerId = 0;
    gBattleMainFunc = CheckFocusPunch_ClearVarsBeforeTurnStarts;    //keep also used for rage etc.  
    gBattleStruct->quickClawBattlerId = 0;
}

#define END_TURN_RESET //resets values for end turn
static void TurnValuesCleanUp(bool8 var0) //resets protect structs specific disble structs and folloemetimer at turn end
{
    s32 i; //not used presently, needed for activebat replacement 
    //u8 *dataPtr;

    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
    {
        if (var0)
        {
            //gProtectStructs[gActiveBattler].protected = FALSE;
            //gProtectStructs[gActiveBattler].endured = FALSE;
            
            gProtectStructs[gActiveBattler].protected = FALSE;
            gProtectStructs[gActiveBattler].spikyShielded = FALSE;
            gProtectStructs[gActiveBattler].kingsShielded = FALSE;
            gProtectStructs[gActiveBattler].banefulBunkered = FALSE;
            gProtectStructs[gActiveBattler].quash = FALSE;
            gProtectStructs[gActiveBattler].usedCustapBerry = FALSE;
            gProtectStructs[gActiveBattler].quickDraw = FALSE;
            //memset(&gQueuedStatBoosts[gActiveBattler], 0, sizeof(struct QueuedStatBoost));
        }
        else
        {
            //dataPtr = (u8 *)(&gProtectStructs[gActiveBattler]);
            //for (i = 0; i < sizeof(struct ProtectStruct); ++i)
            //    dataPtr[i] = 0; //clears protect struct
            
            memset(&gProtectStructs[gActiveBattler], 0, sizeof(struct ProtectStruct));

            if (gDisableStructs[gActiveBattler].isFirstTurn) //starts at 2, think this decrements so its no longer switch in?
                --gDisableStructs[gActiveBattler].isFirstTurn;

            //if (!(gBattleMons[gActiveBattler].status2 & STATUS2_LOCK_CONFUSE))
            //    gDisableStructs[gActiveBattler].rampageMoveTurns = 0;
            
            //confusing but pretty sure even without my change
            //by default this was never used to clear the effect it got cleared in atk canceler?
           /*if (gDisableStructs[gActiveBattler].rechargeTimer)
            {
                --gDisableStructs[gActiveBattler].rechargeTimer;
                
            }
            else
            {
                if (gDisableStructs[gActiveBattler].rechargeTimer == 0)
                    gBattleMons[gActiveBattler].status2 &= ~(STATUS2_RECHARGE);
            }*/
           //removed recharge logic just leaving to be handled in atk canceler
                
        }
        if (gDisableStructs[gActiveBattler].substituteHP == 0)
            gBattleMons[gActiveBattler].status2 &= ~(STATUS2_SUBSTITUTE);

    }
    gSideStatuses[B_SIDE_PLAYER] &= ~(SIDE_STATUS_QUICK_GUARD | SIDE_STATUS_WIDE_GUARD | SIDE_STATUS_CRAFTY_SHIELD | SIDE_STATUS_MAT_BLOCK);
    gSideStatuses[B_SIDE_OPPONENT] &= ~(SIDE_STATUS_QUICK_GUARD | SIDE_STATUS_WIDE_GUARD | SIDE_STATUS_CRAFTY_SHIELD | SIDE_STATUS_MAT_BLOCK);
    gSideTimers[0].followmeTimer = 0;
    gSideTimers[1].followmeTimer = 0;

    gBattleStruct->pursuitTarget = 0;
    gBattleStruct->pursuitSwitchByMove = FALSE;
    gBattleStruct->pursuitStoredSwitch = 0;

    //gBattleStruct->pledgeMove = FALSE; // combined pledge move may not have been used due to a canceller
}

static void SpecialStatusesClear(void) //intimidatedmon is a special status so this function is what's resetting it outside of the faint condition
{
    memset(&gSpecialStatuses, 0, sizeof(gSpecialStatuses));
    /*for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
    {
        s32 i;
        u8 *dataPtr = (u8 *)(&gSpecialStatuses[gActiveBattler]);

        for (i = 0; i < sizeof(struct SpecialStatus); ++i)
            dataPtr[i] = 0;
        

    }*/
}

static void CheckFocusPunch_ClearVarsBeforeTurnStarts(void)
{
    if (!(gHitMarker & HITMARKER_RUN))
    {
        /*while (gBattleStruct->focusPunchBattlerId < gBattlersCount)
        {
            gActiveBattler = gBattlerAttacker = gBattleStruct->focusPunchBattlerId;
            ++gBattleStruct->focusPunchBattlerId;
            if (gChosenMoveByBattler[gActiveBattler] == MOVE_FOCUS_PUNCH
             && !(gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP)
             && !(gDisableStructs[gBattlerAttacker].truantCounter)
             && !(gProtectStructs[gActiveBattler].noValidMoves))
            {
                BattleScriptExecute(BattleScript_FocusPunchSetUp);
                return;
            }
        }*/
        while (gBattleStruct->quickClawBattlerId < gBattlersCount) //port from emerald, to get quick claw activate animation - works, but not how I thought
        {
            gActiveBattler = gBattlerAttacker = gBattleStruct->quickClawBattlerId;
            gBattleStruct->quickClawBattlerId++;
            if (gChosenActionByBattler[gActiveBattler] == B_ACTION_USE_MOVE
             //&& gChosenMoveByBattler[gActiveBattler] != MOVE_FOCUS_PUNCH   // quick claw message doesn't need to activate here
             && (gProtectStructs[gActiveBattler].usedCustapBerry || gProtectStructs[gActiveBattler].quickDraw)
             && !(gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP)
             && !(gDisableStructs[gBattlerAttacker].truantCounter)
             && !(gProtectStructs[gActiveBattler].noValidMoves))
            {
                if (gProtectStructs[gActiveBattler].usedCustapBerry)
                {
                    gProtectStructs[gActiveBattler].usedCustapBerry = FALSE;
                    gLastUsedItem = gBattleMons[gActiveBattler].item;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    GetItemName(gBattleTextBuff1, gLastUsedItem);
                    if (GetBattlerHoldEffect(gActiveBattler, FALSE) == HOLD_EFFECT_CUSTAP_BERRY)
                    {
                        // don't record berry since its gone now
                        BattleScriptExecute(BattleScript_CustapBerryActivation);
                    }
                    else
                    {
                        RecordItemEffectBattle(gActiveBattler, GetBattlerHoldEffect(gActiveBattler, FALSE));
                        BattleScriptExecute(BattleScript_QuickClawActivation);
                    }
                }
                else if (gProtectStructs[gActiveBattler].quickDraw)
                {
                    gBattlerAbility = gActiveBattler;
                    gProtectStructs[gActiveBattler].quickDraw = FALSE;
                    gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    RecordAbilityBattle(gActiveBattler, gLastUsedAbility);
                    BattleScriptExecute(BattleScript_QuickDrawActivation);
                }
                return;
            }
        }
    }
    //TryClearRageStatuses();
    gCurrentTurnActionNumber = 0;
    {
        // something stupid needed to match
        u8 zero;

        gCurrentActionFuncId = gActionsByTurnOrder[(zero = 0)];
    }
    gDynamicBasePower = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleStruct->effectsBeforeUsingMoveDone = FALSE;
    gBattleMainFunc = RunTurnActionsFunctions;  //this is where functions actually start, use move goes to handleusmove
    gBattleCommunication[3] = 0;
    gBattleCommunication[4] = 0;
    gBattleScripting.multihitMoveEffect = 0;
    gBattleResources->battleScriptsStack->size = 0;
}

/*static bool32 TryDoGimmicksBeforeMoves(void)
{
    if (!(gHitMarker & HITMARKER_RUN)
        && (gBattleStruct->mega.toEvolve || gBattleStruct->burst.toBurst || gBattleStruct->dynamax.toDynamax))
    {
        u32 i, battler;
        u8 order[MAX_BATTLERS_COUNT];

        PopulateArrayWithBattlers(order);
        SortBattlersBySpeed(order, FALSE);
        for (i = 0; i < gBattlersCount; i++)
        {
            // Dynamax Check
            if (gBattleStruct->dynamax.toDynamax & gBitTable[order[i]])
            {
                gBattlerAttacker = order[i];
                gBattleScripting.battler = gBattlerAttacker;
                gBattleStruct->dynamax.toDynamax &= ~(gBitTable[gBattlerAttacker]);
                PrepareBattlerForDynamax(gBattlerAttacker);
                BattleScriptExecute(BattleScript_DynamaxBegins);
                return TRUE;
            }
            // Mega Evo Check
            if (gBattleStruct->mega.toEvolve & gBitTable[order[i]]
                && !(gProtectStructs[order[i]].noValidMoves))
            {
                gBattlerAttacker = order[i];
                gBattleStruct->mega.toEvolve &= ~(gBitTable[gBattlerAttacker]);
                gLastUsedItem = gBattleMons[gBattlerAttacker].item;
                if (GetBattleFormChangeTargetSpecies(gBattlerAttacker, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE) != SPECIES_NONE)
                    BattleScriptExecute(BattleScript_WishMegaEvolution);
                else
                    BattleScriptExecute(BattleScript_MegaEvolution);
                return TRUE;
            }
            // Ultra Burst Check
            if (gBattleStruct->burst.toBurst & gBitTable[order[i]]
                && !(gProtectStructs[order[i]].noValidMoves))
            {
                battler = gBattlerAttacker = order[i];
                gBattleStruct->burst.toBurst &= ~(gBitTable[battler]);
                gLastUsedItem = gBattleMons[battler].item;
                BattleScriptExecute(BattleScript_UltraBurst);
                return TRUE;
            }
        }
    }

    if (B_MEGA_EVO_TURN_ORDER >= GEN_7)
        TryChangeTurnOrder(); // This will just do nothing if no mon has mega evolved.
    return FALSE;
}*/

static bool32 TryDoMoveEffectsBeforeMoves(void)
{
    if (!(gHitMarker & HITMARKER_RUN))
    {
        u32 i;
        u8 battlers[MAX_BATTLERS_COUNT];

        //PopulateArrayWithBattlers(battlers);
        SortBattlersBySpeed(battlers, FALSE);
        for (i = 0; i < gBattlersCount; i++)
        {
            if (gBattleMons[battlers[i]].status4 & STATUS4_BIND) //conditions shuold be more or less on same level don' tknow why this one fails
            {
                //shold handle switch in bind case, to make use random move
                if (gDisableStructs[battlers[i]].bindedMove == MOVE_NONE) //ok this just isn't workingand I don't know why
                {
                    u8 numMoves;
                    u8 movePos;
                    for (numMoves = 0; gBattleMons[battlers[i]].moves[numMoves] != MOVE_NONE; ++numMoves)
                                        if (gBattleMons[battlers[i]].moves[numMoves] == MOVE_NONE)
                                            break;
                    movePos = Random() % numMoves;
                    gDisableStructs[battlers[i]].bindedMove = gBattleMons[battlers[i]].moves[movePos];
                    gDisableStructs[battlers[i]].bindMovepos = movePos;
                
                    switch (gDisableStructs[battlers[i]].bindedMove)
                    {
                        case MOVE_ENCORE:
                        case MOVE_TRANSFORM:
                        case MOVE_MIMIC:
                        case MOVE_SKETCH:
                        case MOVE_SLEEP_TALK:
                        case MOVE_MIRROR_MOVE:
                        gDisableStructs[battlers[i]].bindedMove = MOVE_STRUGGLE;
                        break;
                    }
                    
                    gChosenMoveByBattler[battlers[i]] = gDisableStructs[battlers[i]].bindedMove;
                    *(gBattleStruct->chosenMovePositions + battlers[i]) = gDisableStructs[battlers[i]].bindMovepos; //without this fainted logic works??
                    
                    return TRUE;
                }
            }
            /*if (!(gBattleStruct->focusPunchBattlers & gBitTable[battlers[i]])
                && !(gBattleMons[battlers[i]].status1 & STATUS1_SLEEP)
                && !(gDisableStructs[battlers[i]].truantCounter)
                && !(gProtectStructs[battlers[i]].noValidMoves))
            {
                gBattleStruct->focusPunchBattlers |= gBitTable[battlers[i]];
                gBattlerAttacker = battlers[i];
                switch (gChosenMoveByBattler[gBattlerAttacker])
                {
                
                /*case MOVE_BEAK_BLAST:
                    BattleScriptExecute(BattleScript_BeakBlastSetUp);
                    return TRUE;
                case MOVE_SHELL_TRAP:
                    BattleScriptExecute(BattleScript_ShellTrapSetUp);
                    return TRUE;
                }
            }*/
        }
    }

    return FALSE;
}

// In gen7, priority and speed are recalculated during the turn in which a pokemon mega evolves
/*static void TryChangeTurnOrder(void)
{
    u32 i, j;
    for (i = 0; i < gBattlersCount - 1; i++)
    //for (i = gCurrentTurnActionNumber; i < gBattlersCount - 1; i++)
    {
        for (j = i + 1; j < gBattlersCount; j++)
        {
            u32 battler1 = gBattlerByTurnOrder[i];
            u32 battler2 = gBattlerByTurnOrder[j];

            if (gActionsByTurnOrder[i] == B_ACTION_USE_MOVE
                && gActionsByTurnOrder[j] == B_ACTION_USE_MOVE)
            {
                if (GetWhichBattlerFaster(battler1, battler2, FALSE) == -1)
                    SwapTurnOrder(i, j);
            }
        }
    }
}*/ //sigh more stuff need to port smh

static void RunTurnActionsFunctions(void) //important
{
    if (gBattleOutcome != 0)
        gCurrentActionFuncId = B_ACTION_FINISHED;
     // Mega Evolve / Focus Punch-like moves after switching, items, running, but before using a move.
    if (gCurrentActionFuncId == B_ACTION_USE_MOVE && !gBattleStruct->effectsBeforeUsingMoveDone)
    {
         if (!gBattleStruct->pursuitTarget)
        {
            //if (TryDoGimmicksBeforeMoves())
             //   return;
            //else if
            if (TryDoMoveEffectsBeforeMoves())
                return;
            gBattleStruct->effectsBeforeUsingMoveDone = TRUE;
        }
        /*else
        {
            if (TryActivateGimmick(gBattlerByTurnOrder[gCurrentTurnActionNumber]))
                return;
        }*/
    }

    *(&gBattleStruct->savedTurnActionNumber) = gCurrentTurnActionNumber;
    sTurnActionsFuncsTable[gCurrentActionFuncId]();

    if (gCurrentTurnActionNumber >= gBattlersCount) // everyone did their actions, turn finished
    {
        gHitMarker &= ~(HITMARKER_PASSIVE_DAMAGE);
        gBattleMainFunc = sEndTurnFuncsTable[gBattleOutcome & 0x7F]; //default but why does it use this value?

    }
    else
    {
        if (gBattleStruct->savedTurnActionNumber != gCurrentTurnActionNumber) // action turn has been done, clear hitmarker bits for another battlerId
        {
            gHitMarker &= ~(HITMARKER_NO_ATTACKSTRING);
            gHitMarker &= ~(HITMARKER_UNABLE_TO_USE_MOVE);
        }
    }
}

static void HandleEndTurn_BattleWon(void)
{
    gCurrentActionFuncId = 0;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gBattleTextBuff1[0] = gBattleOutcome;
        gBattlerAttacker = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    //    gBattlescriptCurrInstr = BattleScript_LinkBattleWonOrLost;
        gBattleOutcome &= ~(B_OUTCOME_LINK_BATTLE_RAN);
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_BATTLE_TOWER))
    {
        BattleStopLowHpSound();
        PlayBGM(MUS_VICTORY_TRAINER);
        gBattlescriptCurrInstr = BattleScript_BattleTowerTrainerBattleWon;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && !(gBattleTypeFlags & BATTLE_TYPE_LINK)) //can put pokevial logic here
    {
        BattleStopLowHpSound();
        gBattlescriptCurrInstr = BattleScript_LocalTrainerBattleWon;
        switch (gTrainers[gTrainerBattleOpponent_A].trainerClass)
        {
        case CLASS_LEADER_2:
        case CLASS_CHAMPION_2:
            PlayBGM(MUS_VICTORY_GYM_LEADER);
            break;
        case CLASS_BOSS:
        case CLASS_TEAM_ROCKET:
        case CLASS_COOLTRAINER_2:
        case CLASS_ELITE_FOUR_2:
        case CLASS_GENTLEMAN_2:
        default:
            PlayBGM(MUS_VICTORY_TRAINER);
            break;
        }
    }
    else
    {
        gBattlescriptCurrInstr = BattleScript_PayDayMoneyAndPickUpItems;
    }
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_BattleLost(void)
{
    gCurrentActionFuncId = 0;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gBattleTextBuff1[0] = gBattleOutcome;
        gBattlerAttacker = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    //    gBattlescriptCurrInstr = BattleScript_LinkBattleWonOrLost;
        gBattleOutcome &= ~(B_OUTCOME_LINK_BATTLE_RAN);
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && GetTrainerBattleMode() == TRAINER_BATTLE_EARLY_RIVAL)
        {
            if (GetRivalBattleFlags() & RIVAL_BATTLE_HEAL_AFTER)
                gBattleCommunication[MULTISTRING_CHOOSER] = 1; // Dont do white out text
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 2; // Do white out text
            gBattlerAttacker = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
        gBattlescriptCurrInstr = BattleScript_LocalBattleLost;
    }
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_RanFromBattle(void)
{
    gCurrentActionFuncId = 0;
    switch (gProtectStructs[gBattlerAttacker].fleeFlag)
    {
    default:
        gBattlescriptCurrInstr = BattleScript_GotAwaySafely;
        break;
    case 1:
        gBattlescriptCurrInstr = BattleScript_SmokeBallEscape;
        break;
    case 2:
        gBattlescriptCurrInstr = BattleScript_RanAwayUsingMonAbility;
        break;
    }
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_MonFled(void)
{
    gCurrentActionFuncId = 0;
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker]);
    gBattlescriptCurrInstr = BattleScript_WildMonFled;
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_FinishBattle(void)
{
    u32 i;
    u8 freedomFlag = 0;

    for (i = 0; i < PARTY_SIZE; i++) //seems to work
    {    
        if (gBattleStruct->SecondaryItemSlot[i][B_SIDE_PLAYER] == ITEM_NONE)
            continue;

        if (gBattleStruct->SecondaryItemSlot[i][B_SIDE_PLAYER] != ITEM_NONE)
            {
                
                if (!(gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_OLD_MAN_TUTORIAL | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_LINK)))
                {
                    freedomFlag = TRUE;
                    AddBagItem(gBattleStruct->SecondaryItemSlot[i][B_SIDE_PLAYER], 1);
                }
                gBattleStruct->SecondaryItemSlot[i][B_SIDE_PLAYER] = ITEM_NONE;
            }
    }
    if (freedomFlag)
        BattleScriptExecute(BattleScript_SecondaryItemtoBag);

    if (gCurrentActionFuncId == B_ACTION_TRY_FINISH || gCurrentActionFuncId == B_ACTION_FINISHED)
    {
        if (!(gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_OLD_MAN_TUTORIAL | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_SAFARI | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_LINK)))
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
                {
                    if (gBattleResults.playerMon1Species == SPECIES_NONE)
                    {
                        gBattleResults.playerMon1Species = gBattleMons[gActiveBattler].species;
                        StringCopy(gBattleResults.playerMon1Name, gBattleMons[gActiveBattler].nickname);
                    }
                    else
                    {
                        gBattleResults.playerMon2Species = gBattleMons[gActiveBattler].species;
                        StringCopy(gBattleResults.playerMon2Name, gBattleMons[gActiveBattler].nickname);
                    }
                }//since I swap case further up in the pipeline it should already populate correct case here Ibelieve
            }//yeah works
        }
        TrySetQuestLogBattleEvent();
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER) //might not be needed but just extra protection
        TryRestoreStolenItems();    //missing part of knock off, that restorees item. //ok this was issue for items returning, potentially put somewhere else then?
        //beleive working now, pretty sure issue was it was triggering for enemy side and re-restoring the item I had just stolen.
        //seems if it changes items the same turn I stole it with pickup, it still breaks?  leads me to believe the issue is with my pickup logic then
        //how its assigning items?  yup looks like it, I set changeditem in my function, and that goes to a move end argument that's AFTER item theft
        //so its pretty much resetting the item to the battler after I removed it, /confirmed that was issue

        
        
        
        BeginFastPaletteFade(3);
        FadeOutMapMusic(5);

        //if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)  //this flag true/false is diff between trainer battle & wilds
         //   TryRestoreStolenItems();  unsure if was unecessary dupe
        if (VarGet(VAR_LAST_MULTIHIT_RESULT))
            VarSet(VAR_LAST_MULTIHIT_RESULT, 0);    //clear last result var for multihit at turn end

        for (i = 0; i < PARTY_SIZE; i++)
        {
            //UndoMegaEvolution(i);
            //UndoFormChange(i, B_SIDE_PLAYER, FALSE);
            //UndoFormChange(i, B_SIDE_OPPONENT, FALSE); //change opponent, for catching transformed mon
            //DoBurmyFormChange(i); don't know why this is here, form change didn't change to my knowledge so not doing that

            bool8 changedForm = FALSE;
            // Appeared in battle and didn't faint
            if ((gBattleStruct->appearedInBattle & gBitTable[i]) && GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) != 0)
                changedForm = TryFormChange(i, B_SIDE_PLAYER, FORM_CHANGE_END_BATTLE_TERRAIN);
            if (!changedForm)
                changedForm = TryFormChange(i, B_SIDE_PLAYER, FORM_CHANGE_END_BATTLE);

            // Clear original species field
            gBattleStruct->changedSpecies[B_SIDE_PLAYER][i] = SPECIES_NONE;
            gBattleStruct->changedSpecies[B_SIDE_OPPONENT][i] = SPECIES_NONE;

            
        }//prob need add a script for this like I did for caught mon held items

        for (i = 0; i < MAX_BATTLERS_COUNT; i++)
            RevertTransformedHP(i);

        for (i = 0; i < PARTY_SIZE; i++) //erecalc stat after battle
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG)
            {
                
                CalculateMonStats(&gPlayerParty[i]);
            }
        }

        
        // Clear battle mon species to avoid a bug on the next battle that causes
        // healthboxes loading incorrectly due to it trying to create a Mega Indicator
        // if the previous battler would've had it.
        for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        {
            gBattleMons[i].species = SPECIES_NONE;
        }  //added from emerald

        gBattleMainFunc = FreeResetData_ReturnToOvOrDoEvolutions;
        gCB2_AfterEvolution = BattleMainCB2;
    }
    else if (!gBattleControllerExecFlags)
    {
        gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
    }
}

static void FreeResetData_ReturnToOvOrDoEvolutions(void) //  this causes end battle, and starts evolutions, need to make one for in battle, 
{ // the way this is setup to work on palettefade causes it to happen one after another, return to overworld causes palette fade the else make evo happen during palette fade.
    if (!gPaletteFade.active)
    { // Ok it wasn't that simple for some reason, so this leads to one function, which leads to another that actually does the palette fade that triggers the evo...
        ResetSpriteData();
        if (gLeveledUpInBattle == 0 || (gBattleOutcome != B_OUTCOME_WON  && gBattleOutcome != B_OUTCOME_CAUGHT)) //0 is false anything but 0. //ok this is reason for not evoling w exp on catch
            gBattleMainFunc = ReturnFromBattleToOverworld;
        else
            gBattleMainFunc = TryEvolvePokemon; //hope works should allow evo if caught mon - works
        FreeAllWindowBuffers();
        if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
        {
            FreeMonSpritesGfx();
            FreeBattleSpritesData();
            FreeBattleResources();
        }
    }
}

#define EVOLUTION_LOGIC

static void TryEvolvePokemon(void) //want battle evolution for player and opponenet for enemy need to work out how to give them exp.
{ //     after they have exp need set function to make it feel real that they would level up i.e they aren't starting from 0.
    s32 i; //  for that make random function that would get their needed exp to level and then random divide that by either 2, 3, or 4 to increase their chance of lvl in battle.
    // player can use this and the above function to evolve, but enemy needs a specific one, that won't take out of battle, make it so if they can evolve they will. 
    while (gLeveledUpInBattle != 0) // use CFRU mega evolve for opponent.
    {
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            if (gLeveledUpInBattle & gBitTable[i])
            {
                u16 species;
                u8 levelUpBits = gLeveledUpInBattle;

                levelUpBits &= ~(gBitTable[i]);
                gLeveledUpInBattle = levelUpBits;
                species = GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_NORMAL, levelUpBits);
                if (species != SPECIES_NONE)
                {
                    gBattleMainFunc = WaitForEvoSceneToFinish;
                    EvolutionScene(&gPlayerParty[i], species, 0x81, i);
                    return;
                }// for evo in battle, use  if (gCurrentTurnActionNumber >= gBattlersCount) && (gLeveledUpInBattle != 0 || gBattleOutcome != B_OUTCOME_WON)
            }// need to import mega evo graphic,  also make it check for or come after learn move on level up then, go into gBattleMainFunc = TryEvolvePokemon;
        } //vsonic IMPORTANT
    }
    gBattleMainFunc = ReturnFromBattleToOverworld;
}

static void WaitForEvoSceneToFinish(void)
{
    if (gMain.callback2 == BattleMainCB2)
        gBattleMainFunc = TryEvolvePokemon;
}

static void ReturnFromBattleToOverworld(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        RandomlyGivePartyPokerus(gPlayerParty);
        PartySpreadPokerus(gPlayerParty);
    }
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK) || !gReceivedRemoteLinkPlayers)
    {
        gSpecialVar_Result = gBattleOutcome;
        gMain.inBattle = FALSE;
        gMain.callback1 = gPreBattleCallback1;
        if (gBattleTypeFlags & BATTLE_TYPE_ROAMER)
        {
            UpdateRoamerHPStatus(&gEnemyParty[0]);
#ifdef BUGFIX
            if ((gBattleOutcome == B_OUTCOME_WON) || gBattleOutcome == B_OUTCOME_CAUGHT)
#else
            if ((gBattleOutcome & B_OUTCOME_WON) || gBattleOutcome == B_OUTCOME_CAUGHT) // Bug: When Roar is used by roamer, gBattleOutcome is B_OUTCOME_PLAYER_TELEPORTED (5).
#endif                                                                                  // & with B_OUTCOME_WON (1) will return TRUE and deactivates the roamer.
                SetRoamerInactive();
        }
        m4aSongNumStop(SE_LOW_HEALTH);
        SetMainCallback2(gMain.savedCallback);
    }
}

void RunBattleScriptCommands_PopCallbacksStack(void)
{
    if (gCurrentActionFuncId == B_ACTION_TRY_FINISH || gCurrentActionFuncId == B_ACTION_FINISHED)
    {
        if (gBattleResources->battleCallbackStack->size != 0)
            --gBattleResources->battleCallbackStack->size;
        gBattleMainFunc = gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size];
    }
    else
    {
        if (!gBattleControllerExecFlags)
            gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
    }
}

void RunBattleScriptCommands(void)
{
    if (!gBattleControllerExecFlags)
        gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
}



//not exactly sure when this function triggers?
static void HandleAction_UseMove(void)
{
    u32 i, side, moveType, argument;
    u32 moveArgument = 0;
    u32 var = 4; //previously defined wrong, because didn't know couldn't multi initialize and define the value in one line
    u16 moveTarget; //changing that didn't fix anything, targetting still fails

    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (*(&gBattleStruct->absentBattlerFlags) & gBitTable[gBattlerAttacker])
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }
    gCritMultiplier = 1;
    //gBattleScripting.dmgMultiplier = 1;
    gBattleStruct->atkCancellerTracker = 0;
    gMoveResultFlags = 0;
    gMultiHitCounter = 0;
    gBattleCommunication[6] = 0;
    gBattleScripting.savedMoveEffect = 0;
    gCurrMovePos = gChosenMovePos = *(gBattleStruct->chosenMovePositions + gBattlerAttacker);
    
    gBattleStruct->obedienceResult = IsMonDisobedient();
    
    // choose move
    if (gProtectStructs[gBattlerAttacker].noValidMoves) //this is what makes it default to sturggle, bindedmove is none, it checks for moves and finds none
    {
        gProtectStructs[gBattlerAttacker].noValidMoves = 0;
        gCurrentMove = gChosenMove = MOVE_STRUGGLE;
        gHitMarker |= HITMARKER_NO_PPDEDUCT;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(MOVE_STRUGGLE, 0);
    }
    else if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS || gDisableStructs[gBattlerAttacker].rechargeTimer)
    {
        gCurrentMove = gChosenMove = gLockedMoves[gBattlerAttacker];
    }
    //else if (gDisableStructs[gBattlerAttacker].bindedMove != MOVE_NONE
    //    && gDisableStructs[gBattlerAttacker].bindedMove == gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].bindMovepos])  //should always be true cuz bs com logic
    else if (gDisableStructs[gBattlerAttacker].bindTurns && gDisableStructs[gBattlerAttacker].bindedMove != MOVE_NONE) //move should already be set I think
    {
        gCurrentMove = gChosenMove = gDisableStructs[gBattlerAttacker].bindedMove;  //bind move
        if (gCurrentMove != MOVE_STRUGGLE)
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].bindMovepos;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
        //fixed bind not working on first move
    }
    // encore forces you to use the same move
    else if (gDisableStructs[gBattlerAttacker].encoredMove != MOVE_NONE
          && gDisableStructs[gBattlerAttacker].encoredMove == gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].encoredMovePos])
    {
        gCurrentMove = gChosenMove = gDisableStructs[gBattlerAttacker].encoredMove;
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].encoredMovePos;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
    }
    // check if the encored move wasn't overwritten
    else if (gDisableStructs[gBattlerAttacker].encoredMove != MOVE_NONE
          && gDisableStructs[gBattlerAttacker].encoredMove != gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].encoredMovePos])
    {
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].encoredMovePos;
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gDisableStructs[gBattlerAttacker].encoredMove = MOVE_NONE;
        gDisableStructs[gBattlerAttacker].encoredMovePos = 0;
        gDisableStructs[gBattlerAttacker].encoreTimer = 0;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
    }
    else if (gBattleMons[gBattlerAttacker].moves[gCurrMovePos] != gChosenMoveByBattler[gBattlerAttacker]) //force sets move to curr move if chosen move doesnt match
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos]; //so think need bind logic in else if above this block
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
    }
    else if (ShouldAbilityAbsorb(gBattleMons[gBattlerAttacker].moves[gCurrMovePos])) //tink need add extra condition? makae this else if, cehck for absorb ability on other side then go here, then put else with original condition
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        if (CanMovebeRedirected()) //putting a block here does seem to prevent retargetting
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, TRUE);  //don't know if there are consequences but putting this her makes work?
    } //just need to add dynamic type logic to getmovetarget, and  put argument logic below this
    //using getmovetarget, does cause issue, it makes target swap work, but then for abilities that shouldn't be absorbed/retargetted, they get moved too
    //ex I use electric move into lightning rod, mon, it gets pulled, then I use non electric move, and it still gets pulled next turn
    else
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
    }//these last two, are relevant for absorb retargetting

    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER) //and add targetBattler adjust logic to rest of abilities in getmovetarget
        gBattleResults.lastUsedMovePlayer = gCurrentMove;
    else
        gBattleResults.lastUsedMoveOpponent = gCurrentMove;

    // Set dynamic move type. - done in get move target so possibly can replace
    //but multi turns doesn't have getmovetarget  so I guess need to keep
    //this may be necessaary to set opponent type?
    //as player has it set at move chose in battle controller or I put it there?
    SetTypeBeforeUsingMove(gChosenMove, gBattlerAttacker); 
    //GET_MOVE_TYPE(gChosenMove, moveType); //need add argument type, for two type move




    // choose target - need look into may not need this anymore
    side = GetBattlerSide(gBattlerAttacker) ^ BIT_SIDE; //comparing getmovetarget logic appears almost identical, far as checks
    if (gSideTimers[side].followmeTimer != 0
     && gBattleMoves[gCurrentMove].target == MOVE_TARGET_SELECTED
     && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gSideTimers[side].followmeTarget)
     && gBattleMons[gSideTimers[side].followmeTarget].hp != 0)
    {
        gBattlerTarget = gSideTimers[side].followmeTarget;  //think use gBattlerTarget = GetMoveTarget(gCurrentMove, TRUE); somewhere
    }
    
    else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
          && gBattleMoves[gChosenMove].target & MOVE_TARGET_RANDOM)
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        {
            if (Random() & 1)
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            else
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        }
        else
        {
            if (Random() & 1)
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            else
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        }
        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget]
         && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
    }
    else
    {
        gBattlerTarget = *(gBattleStruct->moveTarget + gBattlerAttacker);
        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
        {
            if (GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            {
                gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
            }
            else
            {
                gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_SIDE);
                if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                    gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
            }
        }
    }

    // Record HP of each battler
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (gBattleStruct->hpBefore[i] != gBattleMons[i].hp) //change to catch potential hp adjustments
        gBattleStruct->hpBefore[i] = gBattleMons[i].hp;
    }

    gBattlescriptCurrInstr = gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect];   //important, link for battle_1.s effects at top to effects from battle_effects.h   vsonic
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}//when use move above line will read effect and make it start at specific battlescript as ordered by battle_move_effects
//but there are also move_effects as named from the /constants/battle.h  this is needlesl confusing
//plan rename gBattleScriptsForMoveEffects  gBattleScriptsForBattleEffects
//rename all includes for file battle_move_effects.h to battle_effects.h
//make new file battle_move_effects.h copy all move effects from constants/battle.h to that file
//then every file where constants/battle is included should also include new battle_move_effects.h constant file
//finally rename seteffectwithchance command/function  setmoveeffectwithchance  so its clear that is for move effects

static void HandleAction_Switch(void) //actual switch code
{
    struct Pokemon *party;

    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gActionSelectionCursor[gBattlerAttacker] = 0;
    gMoveSelectionCursor[gBattlerAttacker] = 0;
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, *(gBattleStruct->battlerPartyIndexes + gBattlerAttacker));
    gBattleScripting.battler = gBattlerAttacker;
    gBattlescriptCurrInstr = BattleScript_ActionSwitch;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    if (gBattleResults.playerSwitchesCounter < 255)
        ++gBattleResults.playerSwitchesCounter;

    //doesn't effect transform, that's below
    //UndoFormChange(gBattlerPartyIndexes[gBattlerAttacker], GetBattlerSide(gBattlerAttacker), TRUE); replaced with EE, but kept separate frmo transform stuff

    //transform logic
    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT) //use this instead taken from mega logic
    {    
        party = &gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]];  //mon being transformed
        if (gBattleResults.opponentSwitchesCounter < 3)
        ++gBattleResults.opponentSwitchesCounter;
    }
    else
        party = &gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]];

    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_TRANSFORMED) //*warning dont mess w this stuff, transform uses custom logic
    {

        RevertTransformedHP(gBattlerAttacker);
   
        CalculateMonStats(party); //for resetting stats to normal
    }
    else
        TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_SWITCH);
}

static void HandleAction_UseItem(void)
{
    gBattlerAttacker = gBattlerTarget = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    ClearFuryCutterDestinyBondGrudge(gBattlerAttacker);
    gLastUsedItem = gBattleBufferB[gBattlerAttacker][1] | (gBattleBufferB[gBattlerAttacker][2] << 8);
    if (gLastUsedItem <= ITEM_PREMIER_BALL) // is ball
    {
        gBattlescriptCurrInstr = gBattlescriptsForBallThrow[gLastUsedItem];
    }
    else if (gLastUsedItem == ITEM_POKE_DOLL || gLastUsedItem == ITEM_FLUFFY_TAIL)
    {
        gBattlescriptCurrInstr = gBattlescriptsForRunningByItem[0];
    }
    else if (gLastUsedItem == ITEM_POKE_FLUTE)
    {
        gBattlescriptCurrInstr = gBattlescriptsForRunningByItem[1];
    }
    else if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
    {
        gBattlescriptCurrInstr = gBattlescriptsForUsingItem[0];
    }
    else
    {
        gBattleScripting.battler = gBattlerAttacker;
        switch (*(gBattleStruct->AI_itemType + (gBattlerAttacker >> 1)))
        {
        case AI_ITEM_FULL_RESTORE:
        case AI_ITEM_HEAL_HP:
            break;
        case AI_ITEM_CURE_CONDITION:
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            if (*(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) & 1)
            {
                if (*(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) & 0x3E)
                    gBattleCommunication[MULTISTRING_CHOOSER] = 5;
            }
            else
            {
                while (!(*(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) & 1))
                {
                    *(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) >>= 1;
                    ++gBattleCommunication[MULTISTRING_CHOOSER];
                }
            }
            break;
        case AI_ITEM_X_STAT:
            gBattleCommunication[MULTISTRING_CHOOSER] = 4;
            if (*(gBattleStruct->AI_itemFlags + (gBattlerAttacker >> 1)) & 0x80)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = 5;
            }
            else
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_ATK);
                PREPARE_STRING_BUFFER(gBattleTextBuff2, CHAR_X);
                while (!((*(gBattleStruct->AI_itemFlags + (gBattlerAttacker >> 1))) & 1))
                {
                    *(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) >>= 1;
                    ++gBattleTextBuff1[2];
                }
                gBattleScripting.animArg1 = gBattleTextBuff1[2] + 14;
                gBattleScripting.animArg2 = 0;
            }
            break;
        case AI_ITEM_GUARD_SPECS:
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            break;
        }

        gBattlescriptCurrInstr = gBattlescriptsForUsingItem[*(gBattleStruct->AI_itemType + gBattlerAttacker / 2)];
    }
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}



#define RUN_LOGIC_PT2
bool8 TryRunFromBattle(u8 battler)
{
    bool8 effect = FALSE;
    u8 holdEffect;
    u8 speedVar;

    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[battler].holdEffect;
    else
        holdEffect = GetBattlerHoldEffect(battler, TRUE);
    gPotentialItemEffectBattler = battler;
    if (holdEffect == HOLD_EFFECT_CAN_ALWAYS_RUN)
    {
        gLastUsedItem = gBattleMons[battler].item;
        gProtectStructs[battler].fleeFlag = FLEE_ITEM;
        ++effect;
    }
    else if (IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
    {
        ++effect;
    }
    else if (gBattleMons[battler].ability == ABILITY_RUN_AWAY)
    {
        gLastUsedAbility = ABILITY_RUN_AWAY;
        gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
        ++effect;
    }
    else if (gBattleMons[battler].ability == ABILITY_DEFEATIST
        && gDisableStructs[battler].defeatistActivated)
    {
        gLastUsedAbility = ABILITY_DEFEATIST;
        gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
        ++effect;
    }
    else if (gBattleMons[battler].ability == ABILITY_AVIATOR)
    {
        gLastUsedAbility = ABILITY_AVIATOR;
        gProtectStructs[battler].fleeFlag = FLEE_ABILITY;
        ++effect;
    }
    else if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))
    {
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
            ++effect;
    }
    else
    {
        if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
        {
            if (gBattleMons[battler].speed < gBattleMons[BATTLE_OPPOSITE(battler)].speed)
            {
                speedVar = (gBattleMons[battler].speed * 128) / (gBattleMons[BATTLE_OPPOSITE(battler)].speed) + (gBattleStruct->runTries * 30);
                if (speedVar > (Random() & 0xFF))
                    ++effect;
            }
            else // same speed or faster
            {
                ++effect;
            }
        }

        if (gBattleStruct->runTries <= 30)
        ++gBattleStruct->runTries; //believe new max val is 31
    }
    if (effect)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        gBattleOutcome = B_OUTCOME_RAN;
    }
    return effect;
}

static void HandleAction_Run(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_LOST;
            }
            else
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_WON;
            }
        }
        gBattleOutcome |= B_OUTCOME_LINK_BATTLE_RAN;
    }
    else
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        {
            if (!TryRunFromBattle(gBattlerAttacker)) // failed to run away
            {
                ClearFuryCutterDestinyBondGrudge(gBattlerAttacker);
                gBattleCommunication[MULTISTRING_CHOOSER] = 3;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
        }
        else
        {
            if (!CanBattlerEscape(gBattlerAttacker))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = 4;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
            else
            {
                gCurrentTurnActionNumber = gBattlersCount;
                gBattleOutcome = B_OUTCOME_MON_FLED;
            }
        }
    }
}

static void HandleAction_WatchesCarefully(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    if (gBattleStruct->safariGoNearCounter != 0)
    {
        --gBattleStruct->safariGoNearCounter;
        if (gBattleStruct->safariGoNearCounter == 0)
        {
            *(&gBattleStruct->safariCatchFactor) = gBaseStats[GetMonData(gEnemyParty, MON_DATA_SPECIES)].catchRate * 100 / 1275;
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        }
    }
    else
    {
        if (gBattleStruct->safariPkblThrowCounter != 0)
        {
            --gBattleStruct->safariPkblThrowCounter;
            if (gBattleStruct->safariPkblThrowCounter == 0)
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            else
                gBattleCommunication[5] = 2;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
    }
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[0];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_SafariZoneBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    --gNumSafariBalls;
    gLastUsedItem = ITEM_SAFARI_BALL;
    gBattlescriptCurrInstr = gBattlescriptsForBallThrow[ITEM_SAFARI_BALL];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_ThrowBait(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattleStruct->safariPkblThrowCounter += Random() % 5 + 2;
    if (gBattleStruct->safariPkblThrowCounter > 6)
        gBattleStruct->safariPkblThrowCounter = 6;
    gBattleStruct->safariGoNearCounter = 0;
    gBattleStruct->safariCatchFactor >>= 1;
    if (gBattleStruct->safariCatchFactor <= 2)
        gBattleStruct->safariCatchFactor = 3;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[2];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_ThrowRock(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattleStruct->safariGoNearCounter += Random() % 5 + 2;
    if (gBattleStruct->safariGoNearCounter > 6)
        gBattleStruct->safariGoNearCounter = 6;
    gBattleStruct->safariPkblThrowCounter = 0;
    gBattleStruct->safariCatchFactor <<= 1;
    if (gBattleStruct->safariCatchFactor > 20)
        gBattleStruct->safariCatchFactor = 20;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_SafariZoneRun(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    PlaySE(SE_FLEE);
    gCurrentTurnActionNumber = gBattlersCount;
    gBattleOutcome = B_OUTCOME_RAN;
}

static void HandleAction_OldManBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[3];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    gActionsByTurnOrder[1] = B_ACTION_FINISHED;
}

static void HandleAction_TryFinish(void)
{
    if (!HandleFaintedMonActions())
    {
        gBattleStruct->faintedActionsState = 0;
        gCurrentActionFuncId = B_ACTION_FINISHED;
    }
}


static void HandleAction_NothingIsFainted(void)
{
    ++gCurrentTurnActionNumber;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    gHitMarker &= ~(HITMARKER_DESTINYBOND | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_ATTACKSTRING_PRINTED
                    | HITMARKER_NO_PPDEDUCT | HITMARKER_PASSIVE_DAMAGE
                    | HITMARKER_OBEYS | HITMARKER_WAKE_UP_CLEAR | HITMARKER_SYNCHRONIZE_EFFECT
                    | HITMARKER_CHARGING | HITMARKER_NEVER_SET);
}

static void HandleAction_ActionFinished(void) //may be important for intimidate synchronize adn trace changes
{
    u32 i, j, moveType;
    bool32 afterYouActive = gSpecialStatuses[gBattlerByTurnOrder[gCurrentTurnActionNumber + 1]].afterYou;
    *(gBattleStruct->monToSwitchIntoId + gBattlerByTurnOrder[gCurrentTurnActionNumber]) = gSelectedMonPartyId = PARTY_SIZE;
    
    ++gCurrentTurnActionNumber;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    SpecialStatusesClear(); //yeah the function call here is what resets intimidated mon status, each turn
    gHitMarker &= ~(HITMARKER_DESTINYBOND | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_ATTACKSTRING_PRINTED 
                    | HITMARKER_NO_PPDEDUCT | HITMARKER_PASSIVE_DAMAGE
                    | HITMARKER_OBEYS | HITMARKER_WAKE_UP_CLEAR | HITMARKER_SYNCHRONIZE_EFFECT
                    | HITMARKER_CHARGING | HITMARKER_NEVER_SET | HITMARKER_IGNORE_DISGUISE);
    
    // check if Stellar type boost should be used up
    //moveType = GetMoveType(gCurrentMove);
    GET_MOVE_TYPE(gCurrentMove, moveType);//EE addition attempt workaround

    /*if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_TERA
        && GetBattlerTeraType(gBattlerAttacker) == TYPE_STELLAR
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS
        && IsTypeStellarBoosted(gBattlerAttacker, moveType))
    {
        ExpendTypeStellarBoost(gBattlerAttacker, moveType);
    }*///put in later revisist vsonic Important
    
    
    
    gCurrentMove = MOVE_NONE; // but it doesn't loop because the function doesn't get called except at battle start and switch i.e switch in abilities
    gBattleMoveDamage = 0;
    gMoveResultFlags = 0; //so what I need is to change activation condition or add a new activation condtions
    gBattleScripting.animTurn = 0; //that will be on switch in but check opposite field for a mon with intimidate
    gBattleScripting.animTargetsHit = 0;//and reactivate intimidate if mon doesn't have STATUS3_INTIMIDATE_POKES
    gLastLandedMoves[gBattlerAttacker] = 0;
    gLastHitByType[gBattlerAttacker] = 0;//actually all I need to do is add that extra function call, for switch in
    gBattleStruct->dynamicMoveType = 0;//and then add STATUS3_INTIMIDATE_POKES filter to existing break condition and it should work perfect
    gDynamicBasePower = 0;//if target is on opposite side and visible and not already intimidated it will activate otherwise it'll skip/do nothing!! need test
    gBattleScripting.atk49_state = 0;
    gBattleCommunication[MOVE_EFFECT_BYTE] = 0;
    gBattleCommunication[ACTIONS_CONFIRMED_COUNT] = 0;
    gBattleScripting.multihitMoveEffect = 0;
    gBattleResources->battleScriptsStack->size = 0;

    if (!afterYouActive/* && !gBattleStruct->pledgeMove*/)
    {
        // i starts at `gCurrentTurnActionNumber` because we don't want to recalculate turn order for mon that have already
        // taken action. It's been previously increased, which we want in order to not recalculate the turn of the mon that just finished its action
        for (i = gCurrentTurnActionNumber; i < gBattlersCount - 1; i++)
        {
            for (j = i + 1; j < gBattlersCount; j++)
            {
                u32 battler1 = gBattlerByTurnOrder[i];
                u32 battler2 = gBattlerByTurnOrder[j];

                if (gProtectStructs[battler1].quash || gProtectStructs[battler2].quash
                    || gProtectStructs[battler1].shellTrap || gProtectStructs[battler2].shellTrap)
                    continue;

                // We recalculate order only for action of the same priority. If any action other than switch/move has been taken, they should
                // have been executed before. The only recalculation needed is for moves/switch. Mega evolution is handled in src/battle_main.c/TryChangeOrder
                if((gActionsByTurnOrder[i] == B_ACTION_USE_MOVE && gActionsByTurnOrder[j] == B_ACTION_USE_MOVE))
                {
                    if (GetWhoStrikesFirst(battler1, battler2, FALSE))
                        SwapTurnOrder(i, j);
                }
                else if ((gActionsByTurnOrder[i] == B_ACTION_SWITCH && gActionsByTurnOrder[j] == B_ACTION_SWITCH))
                {
                    if (GetWhoStrikesFirst(battler1, battler2, TRUE)) // If the actions chosen are switching, we recalc order but ignoring the moves
                        SwapTurnOrder(i, j);
                }
            }
        }
    }
}

s8 GetChosenMovePriority(u8 battlerId) //made u8 (in test build)
{
    u16 move;
    gProtectStructs[battlerId].pranksterElevated = FALSE;
    gProtectStructs[battlerId].galewingsElevated = FALSE;
    gProtectStructs[battlerId].triageElevated = FALSE;
    gProtectStructs[battlerId].OmniAideElevated = FALSE;
    gProtectStructs[battlerId].NuisanceElevated = FALSE;
    gProtectStructs[battlerId].LightMetalElevated = FALSE;
    gProtectStructs[battlerId].LongReachElevated = FALSE;

    if (gProtectStructs[battlerId].noValidMoves) //think put called move effec here, ad set move to called move rather than used move?
        move = MOVE_STRUGGLE;
    else
        move = gBattleMons[battlerId].moves[*(gBattleStruct->chosenMovePositions + battlerId)];

    return GetMovePriority(battlerId, move);
}

#define PRIORITY_EFFECTS

s8 GetMovePriority(u8 battlerId, u16 move) //ported from emerald the EXACT thing I needed to make nuisance work (facepalm)
{ //adjusted battlerId made u8,
    s8 priority;
    u16 power = gDynamicBasePower != 0 ? gDynamicBasePower : gBattleMoves[move].power;
    u8 moveType = ReturnMoveType(move, battlerId);

    priority = gBattleMoves[move].priority;
 
    //if gBattleMoves[move].flags == FLAG_DMG_2X_IN_AIR & target is STATUS3_ON_AIR increment priority (gStatuses3[battler] & STATUS3_SKY_DROPPED)
    if ((gBattleMoves[move].flags == FLAG_WIND_MOVE && !IS_MOVE_STATUS(move) && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR) //done because flying mon are fast, and most mon with this move are slow, so would never land otherwise
    || (gBattleMoves[move].flags & FLAG_DMG_2X_UNDERGROUND && gStatuses3[gBattlerTarget] & STATUS3_UNDERGROUND)
    || (gBattleMoves[move].flags & FLAG_DMG_2X_UNDERWATER && gStatuses3[gBattlerTarget] & STATUS3_UNDERWATER))
    {
        priority++;
    }//that's good, just need to figure how to set grounded if by 2x flag move while in air - done in bs command
    //may bneed add this to queenly majesty too? //or could remove, may do that
    //may keep the idea is good, a punish for semi invul, since all those effects 
    //are based on going a certain distance away that would otherwise make them untouchable
    //it makes sense that because of that they wouldn't be able to reach me in time to counter
    //me using a move that COULD reach them.
    //hmm thinkcan leave as the single exclusion to queenly majesty, can't excert control while underground
    //think will remove fly effect from this, as completely invalidates fly
    //and logic for other effects is they are already in the element that is hitting them
    //so should be faster so equivalent would be change
    //fly stuff to if hit by wind move?
    //keep an eye on this effect

    if (GetBattlerAbility(battlerId) == ABILITY_GALE_WINGS
        && moveType == TYPE_FLYING
        && (gBattleMons[battlerId].hp > (gBattleMons[battlerId].maxHP / 2)))
    {
        gProtectStructs[battlerId].galewingsElevated = TRUE;
        priority++;
    }
    else if (GetBattlerAbility(battlerId) == ABILITY_PRANKSTER && IS_MOVE_STATUS(move))
    {
        gProtectStructs[battlerId].pranksterElevated = TRUE; //setup equivalent for gale wings and triage so cna be checked by queenly majesty
        priority++; //and one for omnipotent aide as well
    }
    else if (gBattleMoves[move].effect == EFFECT_GRASSY_GLIDE && IsBattlerTerrainAffected(battlerId, STATUS_FIELD_GRASSY_TERRAIN))
    {
        priority++;
    }
    else if (GetBattlerAbility(battlerId) == ABILITY_TRIAGE)
    {
        switch (gBattleMoves[move].effect)
        {
        case EFFECT_RESTORE_HP:
        case EFFECT_REST:
        case EFFECT_MORNING_SUN:
        case EFFECT_MOONLIGHT:
        case EFFECT_SYNTHESIS:
        case EFFECT_HEAL_PULSE:
        case EFFECT_HEALING_WISH:
        case EFFECT_ROOST:
        case EFFECT_SWALLOW:
        case EFFECT_WISH:
        case EFFECT_SOFTBOILED:
        case EFFECT_ABSORB:
        {
            gProtectStructs[battlerId].triageElevated = TRUE;
            priority += 3;
        }
            break;
        }
    }
    //sets priority still need setup pass healing  to partner, also add partner mon is alive
    else if ((GetBattlerAbility(battlerId) == ABILITY_OMNIPOTENT_AIDE) && CAN_ABILITY_ABSORB(battlerId) && IsBattlerAlive(BATTLE_PARTNER(battlerId)))
    {
        switch (gBattleMoves[move].effect)
        {
        case EFFECT_RESTORE_HP:
        case EFFECT_REST:
        case EFFECT_MORNING_SUN:
        case EFFECT_MOONLIGHT:
        case EFFECT_SYNTHESIS:
        case EFFECT_HEAL_PULSE:
        case EFFECT_HEALING_WISH:
        case EFFECT_ROOST:
        case EFFECT_SWALLOW:
        case EFFECT_WISH:
        case EFFECT_SOFTBOILED:
        case EFFECT_ABSORB:
        {
            gProtectStructs[battlerId].OmniAideElevated = TRUE;
            priority += 3;
        }
            break;
        }
    }
    //potentially boost to 65 vsonic
    //doesn't seem to be working right, have 63 bp hidden power
    //and it still boosts the move priority
    //just realized this is dumb, if power is variable
    //i.e a lvl 1 move, it'd always be true
    //ok can't do anything with this, since moved dynamic power to dmg calc
    //and this is triggered in attack calnceler
    //it'll use gbalttmovepower which is 1
    //I might need to just exclude variable power moves from the list hmm
    //ok works better I guess
    //ok gbattlemovepower  is set in damagecalc, 
    //its NOT the same things as gbattlemoves[move].power
    //gbattlemovepower stores either base power or gdynamicbasepower and is augmented in calbasedamage 
    //function in pokemon.c
    //huh didn't reallize I never fixed this-fixed now
    else if (GetBattlerAbility(battlerId) == ABILITY_NUISANCE
        && (power > 1 && power <= 65) //added dynamic for moves like hidden power
        && gBattleMoves[move].split != SPLIT_STATUS) //change to balance out, so not just prankster plus, given status change
    {
        gProtectStructs[battlerId].NuisanceElevated = TRUE;
        priority += 3;
    }
    //can use other effect that I use for displaying hidden power
    else if (GetBattlerAbility(battlerId) == ABILITY_LIGHT_METAL
        && moveType == TYPE_STEEL)
    {
        gProtectStructs[battlerId].LightMetalElevated = TRUE;
        priority++;
    }
    else if (GetBattlerAbility(battlerId) == ABILITY_LONG_REACH
        && !IsMoveMakingContact(move, battlerId)
        && IsPhysicalMove(battlerId, move))
    {
        gProtectStructs[battlerId].LongReachElevated = TRUE;
        priority++;
    }
    //unsure about affect, conflicted on if it should be contact moves get priority
    //since its attacking from long range, but if its that, than it doesnt make sense to go on contact moves
    //if instead I boost the priority of non-contact physical moves, its signature move gets stronger
    //still has some good use while not being potentially broken?
    //but getting priority on contact moves is also realy nice, and would just make them good

    else if (gDisableStructs[battlerId].EmergencyExitTimer == 0
    && gBattleResources->flags->flags[battlerId] & RESOURCE_FLAG_EMERGENCY_EXIT
    && GetBattlerAbility(battlerId) == ABILITY_EMERGENCY_EXIT) 
    {   
        priority = 9;
    }//should ensure goes first, and will allow to be excluded from effects that otherwise block priority


    else if (gBattleMons[battlerId].status2 & STATUS2_BIDE
        && gDisableStructs[battlerId].bideTimer == 0) //think had to remove check for move bide, since that's not set until atk canceler
    {
        priority = 3; //if works, second attack will go before most priority moves /that did it works now
    }    

    //consider returnto previous effect, think this is better
    //but then again has exactly the issue from before,  if its not limited
    //to priorioty bracket can just infinitely switch out and shut down 
    //a target w force switch effects, but then again does require heavy setup
    else if (GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_LAGGING_TAIL)
        priority = -12;

    return priority;
}

bool8 IsPriorityElevatedviaAbility(u8 battlerId)
{
    if (gProtectStructs[battlerId].pranksterElevated
    || gProtectStructs[battlerId].galewingsElevated
    || gProtectStructs[battlerId].triageElevated
    || gProtectStructs[battlerId].OmniAideElevated
    || gProtectStructs[battlerId].NuisanceElevated
    || gProtectStructs[battlerId].LightMetalElevated
    || gProtectStructs[battlerId].LongReachElevated)
        return TRUE;

    return FALSE;
}

bool32 IsWildMonSmart(void)
{
    /*if(B_SMART_WILD_AI_FLAG == 0)
        return (FlagGet(B_SMART_WILD_AI_FLAG));
    else*/
        return FALSE;

}

