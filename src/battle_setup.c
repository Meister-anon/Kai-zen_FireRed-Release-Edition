#include "global.h"
#include "task.h"
#include "help_system.h"
#include "overworld.h"
#include "item.h"
#include "sound.h"
#include "pokemon.h"
#include "load_save.h"
#include "safari_zone.h"
#include "trainer_see.h"
#include "quest_log.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "strings.h"
#include "string_util.h"
#include "data.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "metatile_behavior.h"
#include "event_scripts.h"
#include "fldeff.h"
#include "fieldmap.h"
#include "field_control_avatar.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_message_box.h"
#include "vs_seeker.h"
#include "battle.h"
#include "battle_transition.h"
#include "battle_controllers.h"
#include "constants/battle_setup.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/pokemon.h"
#include "constants/trainers.h"

enum {
    TRANSITION_TYPE_NORMAL,
    TRANSITION_TYPE_CAVE,
    TRANSITION_TYPE_FLASH,
    TRANSITION_TYPE_WATER,
};

// this file's functions
static void DoSafariBattle(void);
static void DoGhostBattle(void);
static void DoStandardWildBattle(void);
static void CB2_EndWildBattle(void);
static void CB2_EndScriptedWildBattle(void);
static void CB2_EndMarowakBattle(void);
static bool32 IsPlayerDefeated(u32 battleOutcome);
static void CB2_EndTrainerBattle(void);
static const u8 *GetIntroSpeechOfApproachingTrainer(void);
static const u8 *GetTrainerCantBattleSpeech(void);
static void SaveChangesToPlayerParty(void);
static void HandleBattleVariantEndParty(void);

//EE
//static void DoBattlePikeWildBattle(void);

#define TRAINER_APPROACH_SETUP
EWRAM_DATA TrainerBattleParameter gTrainerBattleParameter = {0};
EWRAM_DATA u16 gPartnerTrainerId = 0;
EWRAM_DATA static u8 *sTrainerBattleEndScript = NULL;
EWRAM_DATA static bool8 sShouldCheckTrainerBScript = FALSE;
EWRAM_DATA static u8 sNoOfPossibleTrainerRetScripts = 0;

// The first transition is used if the enemy pokemon are lower level than our pokemon.
// Otherwise, the second transition is used.
static const u8 sBattleTransitionTable_Wild[][2] =
{
    [TRANSITION_TYPE_NORMAL] = {B_TRANSITION_SLICE,          B_TRANSITION_WHITE_BARS_FADE},
    [TRANSITION_TYPE_CAVE]   = {B_TRANSITION_CLOCKWISE_WIPE, B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_FLASH]  = {B_TRANSITION_BLUR,           B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_WATER]  = {B_TRANSITION_WAVE,           B_TRANSITION_RIPPLE},
};

static const u8 sBattleTransitionTable_Trainer[][2] =
{
    [TRANSITION_TYPE_NORMAL] = {B_TRANSITION_POKEBALLS_TRAIL, B_TRANSITION_ANGLED_WIPES},
    [TRANSITION_TYPE_CAVE]   = {B_TRANSITION_SHUFFLE,         B_TRANSITION_BIG_POKEBALL},
    [TRANSITION_TYPE_FLASH]  = {B_TRANSITION_BLUR,            B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_WATER]  = {B_TRANSITION_SWIRL,           B_TRANSITION_RIPPLE},
};

//start of FR stuff to remove
/*static const struct TrainerBattleParameter sOrdinaryBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&TRAINER_BATTLE_PARAM.opponentA,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sContinueScriptBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&TRAINER_BATTLE_PARAM.opponentA,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sDoubleBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&TRAINER_BATTLE_PARAM.opponentA,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sOrdinaryNoIntroBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&TRAINER_BATTLE_PARAM.opponentA,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sEarlyRivalBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&TRAINER_BATTLE_PARAM.opponentA,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sRivalBattleFlags,            TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sContinueScriptDoubleBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&TRAINER_BATTLE_PARAM.opponentA,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};*/
//End of Old FR logic

// Battle Frontier (excluding Pyramid and Dome, which have their own tables below)
/*static const u8 sBattleTransitionTable_BattleFrontier[] =
{
    B_TRANSITION_FRONTIER_LOGO_WIGGLE,
    B_TRANSITION_FRONTIER_LOGO_WAVE,
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_CIRCLES_MEET,
    B_TRANSITION_FRONTIER_CIRCLES_CROSS,
    B_TRANSITION_FRONTIER_CIRCLES_ASYMMETRIC_SPIRAL,
    B_TRANSITION_FRONTIER_CIRCLES_SYMMETRIC_SPIRAL,
    B_TRANSITION_FRONTIER_CIRCLES_MEET_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_CROSS_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_ASYMMETRIC_SPIRAL_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_SYMMETRIC_SPIRAL_IN_SEQ
};

static const u8 sBattleTransitionTable_BattlePyramid[] =
{
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_SQUARES_SPIRAL
};

static const u8 sBattleTransitionTable_BattleDome[] =
{
    B_TRANSITION_FRONTIER_LOGO_WIGGLE,
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_SQUARES_SPIRAL
};
*/

#define REMATCH(trainer1, trainer2, trainer3, trainer4, trainer5, map)  \
{                                                                       \
    .trainerIds = {trainer1, trainer2, trainer3, trainer4, trainer5},   \
    .mapGroup = MAP_GROUP(map),                                         \
    .mapNum = MAP_NUM(map),                                             \
}

const struct RematchTrainer gRematchTable[] =
{
    /*[REMATCH_ROSE] = REMATCH(TRAINER_ROSE_1, TRAINER_ROSE_2, TRAINER_ROSE_3, TRAINER_ROSE_4, TRAINER_ROSE_5, ROUTE118),
    [REMATCH_ANDRES] = REMATCH(TRAINER_ANDRES_1, TRAINER_ANDRES_2, TRAINER_ANDRES_3, TRAINER_ANDRES_4, TRAINER_ANDRES_5, ROUTE105),
    [REMATCH_DUSTY] = REMATCH(TRAINER_DUSTY_1, TRAINER_DUSTY_2, TRAINER_DUSTY_3, TRAINER_DUSTY_4, TRAINER_DUSTY_5, ROUTE111),
    [REMATCH_LOLA] = REMATCH(TRAINER_LOLA_1, TRAINER_LOLA_2, TRAINER_LOLA_3, TRAINER_LOLA_4, TRAINER_LOLA_5, ROUTE109),
    [REMATCH_RICKY] = REMATCH(TRAINER_RICKY_1, TRAINER_RICKY_2, TRAINER_RICKY_3, TRAINER_RICKY_4, TRAINER_RICKY_5, ROUTE109),
    [REMATCH_LILA_AND_ROY] = REMATCH(TRAINER_LILA_AND_ROY_1, TRAINER_LILA_AND_ROY_2, TRAINER_LILA_AND_ROY_3, TRAINER_LILA_AND_ROY_4, TRAINER_LILA_AND_ROY_5, ROUTE124),
    [REMATCH_CRISTIN] = REMATCH(TRAINER_CRISTIN_1, TRAINER_CRISTIN_2, TRAINER_CRISTIN_3, TRAINER_CRISTIN_4, TRAINER_CRISTIN_5, ROUTE121),
    [REMATCH_BROOKE] = REMATCH(TRAINER_BROOKE_1, TRAINER_BROOKE_2, TRAINER_BROOKE_3, TRAINER_BROOKE_4, TRAINER_BROOKE_5, ROUTE111),
    [REMATCH_WILTON] = REMATCH(TRAINER_WILTON_1, TRAINER_WILTON_2, TRAINER_WILTON_3, TRAINER_WILTON_4, TRAINER_WILTON_5, ROUTE111),
    [REMATCH_VALERIE] = REMATCH(TRAINER_VALERIE_1, TRAINER_VALERIE_2, TRAINER_VALERIE_3, TRAINER_VALERIE_4, TRAINER_VALERIE_5, MT_PYRE_6F),
    [REMATCH_CINDY] = REMATCH(TRAINER_CINDY_1, TRAINER_CINDY_3, TRAINER_CINDY_4, TRAINER_CINDY_5, TRAINER_CINDY_6, ROUTE104),
    [REMATCH_THALIA] = REMATCH(TRAINER_THALIA_1, TRAINER_THALIA_2, TRAINER_THALIA_3, TRAINER_THALIA_4, TRAINER_THALIA_5, ABANDONED_SHIP_ROOMS_1F),
    [REMATCH_JESSICA] = REMATCH(TRAINER_JESSICA_1, TRAINER_JESSICA_2, TRAINER_JESSICA_3, TRAINER_JESSICA_4, TRAINER_JESSICA_5, ROUTE121),
    [REMATCH_WINSTON] = REMATCH(TRAINER_WINSTON_1, TRAINER_WINSTON_2, TRAINER_WINSTON_3, TRAINER_WINSTON_4, TRAINER_WINSTON_5, ROUTE104),
    [REMATCH_STEVE] = REMATCH(TRAINER_STEVE_1, TRAINER_STEVE_2, TRAINER_STEVE_3, TRAINER_STEVE_4, TRAINER_STEVE_5, ROUTE114),
    [REMATCH_TONY] = REMATCH(TRAINER_TONY_1, TRAINER_TONY_2, TRAINER_TONY_3, TRAINER_TONY_4, TRAINER_TONY_5, ROUTE107),
    [REMATCH_NOB] = REMATCH(TRAINER_NOB_1, TRAINER_NOB_2, TRAINER_NOB_3, TRAINER_NOB_4, TRAINER_NOB_5, ROUTE115),
    [REMATCH_KOJI] = REMATCH(TRAINER_KOJI_1, TRAINER_KOJI_2, TRAINER_KOJI_3, TRAINER_KOJI_4, TRAINER_KOJI_5, ROUTE127),
    [REMATCH_FERNANDO] = REMATCH(TRAINER_FERNANDO_1, TRAINER_FERNANDO_2, TRAINER_FERNANDO_3, TRAINER_FERNANDO_4, TRAINER_FERNANDO_5, ROUTE123),
    [REMATCH_DALTON] = REMATCH(TRAINER_DALTON_1, TRAINER_DALTON_2, TRAINER_DALTON_3, TRAINER_DALTON_4, TRAINER_DALTON_5, ROUTE118),
    [REMATCH_BERNIE] = REMATCH(TRAINER_BERNIE_1, TRAINER_BERNIE_2, TRAINER_BERNIE_3, TRAINER_BERNIE_4, TRAINER_BERNIE_5, ROUTE114),
    [REMATCH_ETHAN] = REMATCH(TRAINER_ETHAN_1, TRAINER_ETHAN_2, TRAINER_ETHAN_3, TRAINER_ETHAN_4, TRAINER_ETHAN_5, JAGGED_PASS),
    [REMATCH_JOHN_AND_JAY] = REMATCH(TRAINER_JOHN_AND_JAY_1, TRAINER_JOHN_AND_JAY_2, TRAINER_JOHN_AND_JAY_3, TRAINER_JOHN_AND_JAY_4, TRAINER_JOHN_AND_JAY_5, METEOR_FALLS_1F_2R),
    [REMATCH_JEFFREY] = REMATCH(TRAINER_JEFFREY_1, TRAINER_JEFFREY_2, TRAINER_JEFFREY_3, TRAINER_JEFFREY_4, TRAINER_JEFFREY_5, ROUTE120),
    [REMATCH_CAMERON] = REMATCH(TRAINER_CAMERON_1, TRAINER_CAMERON_2, TRAINER_CAMERON_3, TRAINER_CAMERON_4, TRAINER_CAMERON_5, ROUTE123),
    [REMATCH_JACKI] = REMATCH(TRAINER_JACKI_1, TRAINER_JACKI_2, TRAINER_JACKI_3, TRAINER_JACKI_4, TRAINER_JACKI_5, ROUTE123),
    [REMATCH_WALTER] = REMATCH(TRAINER_WALTER_1, TRAINER_WALTER_2, TRAINER_WALTER_3, TRAINER_WALTER_4, TRAINER_WALTER_5, ROUTE121),
    [REMATCH_KAREN] = REMATCH(TRAINER_KAREN_1, TRAINER_KAREN_2, TRAINER_KAREN_3, TRAINER_KAREN_4, TRAINER_KAREN_5, ROUTE116),
    [REMATCH_JERRY] = REMATCH(TRAINER_JERRY_1, TRAINER_JERRY_2, TRAINER_JERRY_3, TRAINER_JERRY_4, TRAINER_JERRY_5, ROUTE116),
    [REMATCH_ANNA_AND_MEG] = REMATCH(TRAINER_ANNA_AND_MEG_1, TRAINER_ANNA_AND_MEG_2, TRAINER_ANNA_AND_MEG_3, TRAINER_ANNA_AND_MEG_4, TRAINER_ANNA_AND_MEG_5, ROUTE117),
    [REMATCH_ISABEL] = REMATCH(TRAINER_ISABEL_1, TRAINER_ISABEL_2, TRAINER_ISABEL_3, TRAINER_ISABEL_4, TRAINER_ISABEL_5, ROUTE110),
    [REMATCH_MIGUEL] = REMATCH(TRAINER_MIGUEL_1, TRAINER_MIGUEL_2, TRAINER_MIGUEL_3, TRAINER_MIGUEL_4, TRAINER_MIGUEL_5, ROUTE103),
    [REMATCH_TIMOTHY] = REMATCH(TRAINER_TIMOTHY_1, TRAINER_TIMOTHY_2, TRAINER_TIMOTHY_3, TRAINER_TIMOTHY_4, TRAINER_TIMOTHY_5, ROUTE115),
    [REMATCH_SHELBY] = REMATCH(TRAINER_SHELBY_1, TRAINER_SHELBY_2, TRAINER_SHELBY_3, TRAINER_SHELBY_4, TRAINER_SHELBY_5, MT_CHIMNEY),
    [REMATCH_CALVIN] = REMATCH(TRAINER_CALVIN_1, TRAINER_CALVIN_2, TRAINER_CALVIN_3, TRAINER_CALVIN_4, TRAINER_CALVIN_5, ROUTE102),
    [REMATCH_ELLIOT] = REMATCH(TRAINER_ELLIOT_1, TRAINER_ELLIOT_2, TRAINER_ELLIOT_3, TRAINER_ELLIOT_4, TRAINER_ELLIOT_5, ROUTE106),
    [REMATCH_ISAIAH] = REMATCH(TRAINER_ISAIAH_1, TRAINER_ISAIAH_2, TRAINER_ISAIAH_3, TRAINER_ISAIAH_4, TRAINER_ISAIAH_5, ROUTE128),
    [REMATCH_MARIA] = REMATCH(TRAINER_MARIA_1, TRAINER_MARIA_2, TRAINER_MARIA_3, TRAINER_MARIA_4, TRAINER_MARIA_5, ROUTE117),
    [REMATCH_ABIGAIL] = REMATCH(TRAINER_ABIGAIL_1, TRAINER_ABIGAIL_2, TRAINER_ABIGAIL_3, TRAINER_ABIGAIL_4, TRAINER_ABIGAIL_5, ROUTE110),
    [REMATCH_DYLAN] = REMATCH(TRAINER_DYLAN_1, TRAINER_DYLAN_2, TRAINER_DYLAN_3, TRAINER_DYLAN_4, TRAINER_DYLAN_5, ROUTE117),
    [REMATCH_KATELYN] = REMATCH(TRAINER_KATELYN_1, TRAINER_KATELYN_2, TRAINER_KATELYN_3, TRAINER_KATELYN_4, TRAINER_KATELYN_5, ROUTE128),
    [REMATCH_BENJAMIN] = REMATCH(TRAINER_BENJAMIN_1, TRAINER_BENJAMIN_2, TRAINER_BENJAMIN_3, TRAINER_BENJAMIN_4, TRAINER_BENJAMIN_5, ROUTE110),
    [REMATCH_PABLO] = REMATCH(TRAINER_PABLO_1, TRAINER_PABLO_2, TRAINER_PABLO_3, TRAINER_PABLO_4, TRAINER_PABLO_5, ROUTE126),
    [REMATCH_NICOLAS] = REMATCH(TRAINER_NICOLAS_1, TRAINER_NICOLAS_2, TRAINER_NICOLAS_3, TRAINER_NICOLAS_4, TRAINER_NICOLAS_5, METEOR_FALLS_1F_2R),
    [REMATCH_ROBERT] = REMATCH(TRAINER_ROBERT_1, TRAINER_ROBERT_2, TRAINER_ROBERT_3, TRAINER_ROBERT_4, TRAINER_ROBERT_5, ROUTE120),
    [REMATCH_LAO] = REMATCH(TRAINER_LAO_1, TRAINER_LAO_2, TRAINER_LAO_3, TRAINER_LAO_4, TRAINER_LAO_5, ROUTE113),
    [REMATCH_CYNDY] = REMATCH(TRAINER_CYNDY_1, TRAINER_CYNDY_2, TRAINER_CYNDY_3, TRAINER_CYNDY_4, TRAINER_CYNDY_5, ROUTE115),
    [REMATCH_MADELINE] = REMATCH(TRAINER_MADELINE_1, TRAINER_MADELINE_2, TRAINER_MADELINE_3, TRAINER_MADELINE_4, TRAINER_MADELINE_5, ROUTE113),
    [REMATCH_JENNY] = REMATCH(TRAINER_JENNY_1, TRAINER_JENNY_2, TRAINER_JENNY_3, TRAINER_JENNY_4, TRAINER_JENNY_5, ROUTE124),
    [REMATCH_DIANA] = REMATCH(TRAINER_DIANA_1, TRAINER_DIANA_2, TRAINER_DIANA_3, TRAINER_DIANA_4, TRAINER_DIANA_5, JAGGED_PASS),
    [REMATCH_AMY_AND_LIV] = REMATCH(TRAINER_AMY_AND_LIV_1, TRAINER_AMY_AND_LIV_2, TRAINER_AMY_AND_LIV_4, TRAINER_AMY_AND_LIV_5, TRAINER_AMY_AND_LIV_6, ROUTE103),
    [REMATCH_ERNEST] = REMATCH(TRAINER_ERNEST_1, TRAINER_ERNEST_2, TRAINER_ERNEST_3, TRAINER_ERNEST_4, TRAINER_ERNEST_5, ROUTE125),
    [REMATCH_CORY] = REMATCH(TRAINER_CORY_1, TRAINER_CORY_2, TRAINER_CORY_3, TRAINER_CORY_4, TRAINER_CORY_5, ROUTE108),
    [REMATCH_EDWIN] = REMATCH(TRAINER_EDWIN_1, TRAINER_EDWIN_2, TRAINER_EDWIN_3, TRAINER_EDWIN_4, TRAINER_EDWIN_5, ROUTE110),
    [REMATCH_LYDIA] = REMATCH(TRAINER_LYDIA_1, TRAINER_LYDIA_2, TRAINER_LYDIA_3, TRAINER_LYDIA_4, TRAINER_LYDIA_5, ROUTE117),
    [REMATCH_ISAAC] = REMATCH(TRAINER_ISAAC_1, TRAINER_ISAAC_2, TRAINER_ISAAC_3, TRAINER_ISAAC_4, TRAINER_ISAAC_5, ROUTE117),
    [REMATCH_GABRIELLE] = REMATCH(TRAINER_GABRIELLE_1, TRAINER_GABRIELLE_2, TRAINER_GABRIELLE_3, TRAINER_GABRIELLE_4, TRAINER_GABRIELLE_5, MT_PYRE_3F),
    [REMATCH_CATHERINE] = REMATCH(TRAINER_CATHERINE_1, TRAINER_CATHERINE_2, TRAINER_CATHERINE_3, TRAINER_CATHERINE_4, TRAINER_CATHERINE_5, ROUTE119),
    [REMATCH_JACKSON] = REMATCH(TRAINER_JACKSON_1, TRAINER_JACKSON_2, TRAINER_JACKSON_3, TRAINER_JACKSON_4, TRAINER_JACKSON_5, ROUTE119),
    [REMATCH_HALEY] = REMATCH(TRAINER_HALEY_1, TRAINER_HALEY_2, TRAINER_HALEY_3, TRAINER_HALEY_4, TRAINER_HALEY_5, ROUTE104),
    [REMATCH_JAMES] = REMATCH(TRAINER_JAMES_1, TRAINER_JAMES_2, TRAINER_JAMES_3, TRAINER_JAMES_4, TRAINER_JAMES_5, PETALBURG_WOODS),
    [REMATCH_TRENT] = REMATCH(TRAINER_TRENT_1, TRAINER_TRENT_2, TRAINER_TRENT_3, TRAINER_TRENT_4, TRAINER_TRENT_5, ROUTE112),
    [REMATCH_SAWYER] = REMATCH(TRAINER_SAWYER_1, TRAINER_SAWYER_2, TRAINER_SAWYER_3, TRAINER_SAWYER_4, TRAINER_SAWYER_5, MT_CHIMNEY),
    [REMATCH_KIRA_AND_DAN] = REMATCH(TRAINER_KIRA_AND_DAN_1, TRAINER_KIRA_AND_DAN_2, TRAINER_KIRA_AND_DAN_3, TRAINER_KIRA_AND_DAN_4, TRAINER_KIRA_AND_DAN_5, ABANDONED_SHIP_ROOMS2_1F),
    [REMATCH_WALLY_VR] = REMATCH(TRAINER_WALLY_VR_2, TRAINER_WALLY_VR_3, TRAINER_WALLY_VR_4, TRAINER_WALLY_VR_5, TRAINER_WALLY_VR_5, VICTORY_ROAD_1F),
    [REMATCH_ROXANNE] = REMATCH(TRAINER_ROXANNE_1, TRAINER_ROXANNE_2, TRAINER_ROXANNE_3, TRAINER_ROXANNE_4, TRAINER_ROXANNE_5, RUSTBORO_CITY),
    [REMATCH_BRAWLY] = REMATCH(TRAINER_BRAWLY_1, TRAINER_BRAWLY_2, TRAINER_BRAWLY_3, TRAINER_BRAWLY_4, TRAINER_BRAWLY_5, DEWFORD_TOWN),
    [REMATCH_WATTSON] = REMATCH(TRAINER_WATTSON_1, TRAINER_WATTSON_2, TRAINER_WATTSON_3, TRAINER_WATTSON_4, TRAINER_WATTSON_5, MAUVILLE_CITY),
    [REMATCH_FLANNERY] = REMATCH(TRAINER_FLANNERY_1, TRAINER_FLANNERY_2, TRAINER_FLANNERY_3, TRAINER_FLANNERY_4, TRAINER_FLANNERY_5, LAVARIDGE_TOWN),
    [REMATCH_NORMAN] = REMATCH(TRAINER_NORMAN_1, TRAINER_NORMAN_2, TRAINER_NORMAN_3, TRAINER_NORMAN_4, TRAINER_NORMAN_5, PETALBURG_CITY),
    [REMATCH_WINONA] = REMATCH(TRAINER_WINONA_1, TRAINER_WINONA_2, TRAINER_WINONA_3, TRAINER_WINONA_4, TRAINER_WINONA_5, FORTREE_CITY),
    [REMATCH_TATE_AND_LIZA] = REMATCH(TRAINER_TATE_AND_LIZA_1, TRAINER_TATE_AND_LIZA_2, TRAINER_TATE_AND_LIZA_3, TRAINER_TATE_AND_LIZA_4, TRAINER_TATE_AND_LIZA_5, MOSSDEEP_CITY),
    [REMATCH_JUAN] = REMATCH(TRAINER_JUAN_1, TRAINER_JUAN_2, TRAINER_JUAN_3, TRAINER_JUAN_4, TRAINER_JUAN_5, SOOTOPOLIS_CITY),
    [REMATCH_SIDNEY] = REMATCH(TRAINER_SIDNEY, TRAINER_SIDNEY, TRAINER_SIDNEY, TRAINER_SIDNEY, TRAINER_SIDNEY, EVER_GRANDE_CITY),
    [REMATCH_PHOEBE] = REMATCH(TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, EVER_GRANDE_CITY),
    [REMATCH_GLACIA] = REMATCH(TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, EVER_GRANDE_CITY),
    [REMATCH_DRAKE] = REMATCH(TRAINER_DRAKE, TRAINER_DRAKE, TRAINER_DRAKE, TRAINER_DRAKE, TRAINER_DRAKE, EVER_GRANDE_CITY),
    [REMATCH_WALLACE] = REMATCH(TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, EVER_GRANDE_CITY),
    */
};

#define tState data[0]
#define tTransition data[1]

static void Task_BattleStart(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        if (!FldEffPoison_IsActive())
        {
            HelpSystem_Disable();
            BattleTransition_StartOnField(tTransition);
            ++tState;
        }
        break;
    case 1:
        if (IsBattleTransitionDone() == TRUE)
        {
        	HelpSystem_Enable();
            CleanupOverworldWindowsAndTilemaps();
            SetMainCallback2(CB2_InitBattle);
            RestartWildEncounterImmunitySteps();
            ClearPoisonStepCounter();
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateBattleStartTask(u8 transition, u16 song) // song == 0 means default music for current map
{
    u8 taskId = CreateTask(Task_BattleStart, 1);

    gTasks[taskId].tTransition = transition;
    PlayMapChosenOrBattleBGM(song);
}

static bool8 CheckSilphScopeInPokemonTower(u16 mapGroup, u16 mapNum)
{
    if (mapGroup == MAP_GROUP(POKEMON_TOWER_1F)
     && ((u16)(mapNum - MAP_NUM(POKEMON_TOWER_1F)) <= 6)
     && !(CheckBagHasItem(ITEM_SILPH_SCOPE, 1)))
        return TRUE;
    else
        return FALSE;
}

void BattleSetup_StartWildBattle(void)
{
    if (GetSafariZoneFlag())
        DoSafariBattle();
    else if (CheckSilphScopeInPokemonTower(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
        DoGhostBattle();
    else
        DoStandardWildBattle();
}

static void DoStandardWildBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = 0;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void BattleSetup_StartRoamerBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_ROAMER;
    CreateBattleStartTask(GetWildBattleTransition(), MUS_VS_LEGEND);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

static void DoSafariBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndSafariBattle;
    gBattleTypeFlags = BATTLE_TYPE_SAFARI;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
}

static void DoGhostBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_GHOST;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    SetMonData(&gEnemyParty[0], MON_DATA_NICKNAME, gText_Ghost);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

static void DoTrainerBattle(void)
{
    CreateBattleStartTask(GetTrainerBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_TRAINER_BATTLES);
}

void StartOldManTutorialBattle(void) // teech tv battle interesting wonder if, I can change his actions 
// to battle first maybe demo feature/type changes?
{
    CreateMaleMon(&gEnemyParty[0], SPECIES_WEEDLE, 5);
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_ReturnToFieldContinueScriptPlayMapMusic;
    gBattleTypeFlags = BATTLE_TYPE_CATCH_TUTORIAL;
    CreateBattleStartTask(B_TRANSITION_SLICE, 0);
}

void BattleSetup_StartScriptedWildBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_WILD_SCRIPTED;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void BattleSetup_StartScriptedDoubleWildBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_DOUBLE;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    //IncrementDailyWildBattles();
    //TryUpdateGymLeaderRematchFromWild();
}

void StartMarowakBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndMarowakBattle;
    if (CheckBagHasItem(ITEM_SILPH_SCOPE, 1))
    {
        gBattleTypeFlags = BATTLE_TYPE_GHOST | BATTLE_TYPE_GHOST_UNVEILED;
        CreateMonWithGenderNatureLetter(gEnemyParty, SPECIES_MAROWAK, 30, 31, MON_FEMALE, NATURE_SERIOUS, 0);
    }
    else
    {
        gBattleTypeFlags = BATTLE_TYPE_GHOST;
    }
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    SetMonData(&gEnemyParty[0], MON_DATA_NICKNAME, gText_Ghost);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void StartSouthernIslandBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void StartLegendaryBattle(void)
{
    u16 species;
    
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_LEGENDARY_FRLG;
    species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
    switch (species)
    {
    case SPECIES_MEWTWO:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_VS_MEWTWO);
        break;
    case SPECIES_DEOXYS:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_VS_DEOXYS);
        break;
    case SPECIES_MOLTRES:
    case SPECIES_ARTICUNO:
    case SPECIES_ZAPDOS:
    case SPECIES_HO_OH:
    case SPECIES_LUGIA:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_VS_LEGEND);
        break;
    default:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_RS_VS_TRAINER);
        break;
    }
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void StartGroudonKyogreBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_KYOGRE_GROUDON;
    if (gGameVersion == VERSION_FIRE_RED)
        CreateBattleStartTask(B_TRANSITION_ANGLED_WIPES, MUS_RS_VS_TRAINER);
    else // pointless, exactly the same
        CreateBattleStartTask(B_TRANSITION_ANGLED_WIPES, MUS_RS_VS_TRAINER);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void StartRegiBattle(void)  //not using this, just use StartLegendaryBattle, same effect
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;
    CreateBattleStartTask(B_TRANSITION_BLUR, MUS_RS_VS_TRAINER);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

// not used
static void sub_807FAF8(void)
{
    LoadPlayerParty();
    CB2_EndWildBattle();
}

// not used
static void sub_807FB08(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = sub_807FAF8;
    SavePlayerParty();
    InitPokedudePartyAndOpponent();
    CreateBattleStartTask(GetWildBattleTransition(), 0);
}

static void CB2_EndWildBattle(void)
{
    CpuFill16(0, (void *)BG_PLTT, BG_PLTT_SIZE);
    ResetOamRange(0, 128);
    if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToField);
        gFieldCallback = FieldCB_SafariZoneRanOutOfBalls;
    }
}

static void CB2_EndScriptedWildBattle(void)
{
    CpuFill16(0, (void *)BG_PLTT, BG_PLTT_SIZE);
    ResetOamRange(0, 128);
    if (IsPlayerDefeated(gBattleOutcome) == TRUE)
        SetMainCallback2(CB2_WhiteOut);
    else
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void CB2_EndMarowakBattle(void)
{
    CpuFill16(0, (void *)BG_PLTT, BG_PLTT_SIZE);
    ResetOamRange(0, 128);
    if (IsPlayerDefeated(gBattleOutcome))
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        // If result is TRUE player didnt defeat Marowak, force player back from stairs
        if (gBattleOutcome == B_OUTCOME_WON)
            gSpecialVar_Result = FALSE;
        else
            gSpecialVar_Result = TRUE;
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
}

#define BATTLE_SETUP_TERRAIN//sets battle terrain from metatile/environment
u8 BattleSetup_GetEnvironmentId(void)
{
    u16 tileBehavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);
    if (MetatileBehavior_IsTallGrass_2(tileBehavior))
        return BATTLE_ENVIRONMENT_GRASS;
    if (MetatileBehavior_IsLongGrass(tileBehavior))
        return BATTLE_ENVIRONMENT_LONG_GRASS;
    if (MetatileBehavior_IsSandOrShallowFlowingWater(tileBehavior))
        return BATTLE_ENVIRONMENT_SAND;
    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
        break;
    case MAP_TYPE_UNDERGROUND:
        if (MetatileBehavior_IsIndoorEncounter(tileBehavior))
            return BATTLE_ENVIRONMENT_BUILDING;
        if (MetatileBehavior_IsSurfable(tileBehavior))
            return BATTLE_ENVIRONMENT_POND;
        return BATTLE_ENVIRONMENT_CAVE;
    case MAP_TYPE_INDOOR:
    case MAP_TYPE_SECRET_BASE:
        return BATTLE_ENVIRONMENT_BUILDING;
    case MAP_TYPE_UNDERWATER:
        return BATTLE_ENVIRONMENT_UNDERWATER;
    case MAP_TYPE_OCEAN_ROUTE:
        if (MetatileBehavior_IsSurfable(tileBehavior))
            return BATTLE_ENVIRONMENT_WATER;
        return BATTLE_ENVIRONMENT_PLAIN;
    }
    if (MetatileBehavior_IsDeepSemiDeepOrSplashingWater(tileBehavior))
        return BATTLE_ENVIRONMENT_WATER;
    if (MetatileBehavior_IsSurfable(tileBehavior))
        return BATTLE_ENVIRONMENT_POND;
    if (MetatileBehavior_IsMountain(tileBehavior))
        return BATTLE_ENVIRONMENT_MOUNTAIN;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        if (MetatileBehavior_GetBridgeType(tileBehavior))
            return BATTLE_ENVIRONMENT_POND;
        if (MetatileBehavior_IsBridge(tileBehavior) == TRUE)
            return BATTLE_ENVIRONMENT_WATER;
    }
    return BATTLE_ENVIRONMENT_PLAIN;
}

static u8 GetBattleTransitionTypeByMap(void)
{
    u16 behavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);

    if (Overworld_GetFlashLevel())
        return TRANSITION_TYPE_FLASH;

    if (MetatileBehavior_IsSurfable(behavior))
        return TRANSITION_TYPE_WATER;

    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_UNDERGROUND:
        return TRANSITION_TYPE_CAVE;
    case MAP_TYPE_UNDERWATER:
        return TRANSITION_TYPE_WATER;
    default:
        return TRANSITION_TYPE_NORMAL;
    }
}

static u16 GetSumOfPlayerPartyLevel(u8 numMons) //important useful data
{
    u8 sum = 0;
    s32 i;

    for (i = 0; i < PARTY_SIZE; ++i)
    {
        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);

        if (species != SPECIES_EGG && species != SPECIES_NONE && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
        {
            sum += GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            if (--numMons == 0)
                break;
        }
    }
    return sum;
}

//check and only use for battle transition
//doesn't actually check entire enemy team
//it only checks first sent out mon
static u8 GetSumOfEnemyPartyLevel(u16 opponentId, u8 numMons)
{
    u8 i;
    u8 sum;
    u32 count = numMons;
    const struct TrainerMon *party;

    if (gTrainers[opponentId].partySize < count)
        count = gTrainers[opponentId].partySize;
    sum = 0;

    party = gTrainers[opponentId].party;
    for (i = 0; i < count; ++i)
        sum += party[i].lvl;

    return sum;
}

u8 GetWildBattleTransition(void)
{
    u8 transitionType = GetBattleTransitionTypeByMap();
    u8 enemyLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u8 playerLevel = GetSumOfPlayerPartyLevel(1);

    if (enemyLevel < playerLevel)
        return sBattleTransitionTable_Wild[transitionType][0];
    else
        return sBattleTransitionTable_Wild[transitionType][1];
}

u8 GetTrainerBattleTransition(void)
{
    u8 minPartyCount;
    u8 transitionType;
    u8 enemyLevel;
    u8 playerLevel;
    u32 trainerId = SanitizeTrainerId(TRAINER_BATTLE_PARAM.opponentA);
    u32 trainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);

    /*if (trainerId == TRAINER_SECRET_BASE)
        return B_TRANSITION_BLUE;*/
    if (trainerClass == CLASS_ELITE_FOUR_FRLG)
    {
        if (trainerId == TRAINER_ELITE_FOUR_LORELEI || trainerId == TRAINER_ELITE_FOUR_LORELEI_2)
            return B_TRANSITION_LORELEI;
        if (trainerId == TRAINER_ELITE_FOUR_BRUNO || trainerId == TRAINER_ELITE_FOUR_BRUNO_2)
            return B_TRANSITION_BRUNO;
        if (trainerId == TRAINER_ELITE_FOUR_AGATHA || trainerId == TRAINER_ELITE_FOUR_AGATHA_2)
            return B_TRANSITION_AGATHA;
        if (trainerId == TRAINER_ELITE_FOUR_LANCE || trainerId == TRAINER_ELITE_FOUR_LANCE_2)
            return B_TRANSITION_LANCE;
        return B_TRANSITION_BLUE; //shouldn't be here already triggered by champion
    }
    if (trainerClass == CLASS_CHAMPION_FRLG)
        return B_TRANSITION_BLUE;
    if (gTrainers[trainerId].battleType == BATTLE_TYPE_DOUBLE) //eventually add on or replace with switch vsonic
        minPartyCount = 2; // double battles always at least have 2 pokemon.
    else //important, test 2 on 1 battles
        //Ketsuban in pret, informed me that by default if 1 pokemon in double battle
        //player pokemon will get split between both positions.

        //so will prob have to set up special battle type just for that, 
        //where there are 2 positions on opponent side, and only 1 on player side.
        
        //maybe set it be used in the case you only have 1.
        minPartyCount = 1;
    transitionType = GetBattleTransitionTypeByMap();
    enemyLevel = GetSumOfEnemyPartyLevel(trainerId, minPartyCount);
    playerLevel = GetSumOfPlayerPartyLevel(minPartyCount);
    if (enemyLevel < playerLevel)
        return sBattleTransitionTable_Trainer[transitionType][0];
    else
        return sBattleTransitionTable_Trainer[transitionType][1];
}

u8 BattleSetup_GetBattleTowerBattleTransition(void)
{
    u8 enemyLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u8 playerLevel = GetSumOfPlayerPartyLevel(1);

    if (enemyLevel < playerLevel)
        return B_TRANSITION_POKEBALLS_TRAIL;
    else
        return B_TRANSITION_BIG_POKEBALL;
}

//EE stuff specific to birch battle
/*void ChooseStarter(void)
{
    SetMainCallback2(CB2_ChooseStarter);
    gMain.savedCallback = CB2_GiveStarter;
}

static void CB2_GiveStarter(void)
{
    u16 starterMon;

    *GetVarPointer(VAR_STARTER_MON) = gSpecialVar_Result;
    starterMon = GetStarterPokemon(gSpecialVar_Result);
    ScriptGiveMon(starterMon, 5, ITEM_NONE);
    ResetTasks();
    PlayBattleBGM();
    SetMainCallback2(CB2_StartFirstBattle);
    BattleTransition_Start(B_TRANSITION_BLUR);
}

static void CB2_StartFirstBattle(void)
{
    UpdatePaletteFade();
    RunTasks();

    if (IsBattleTransitionDone() == TRUE)
    {
        gBattleTypeFlags = BATTLE_TYPE_FIRST_BATTLE;
        gMain.savedCallback = CB2_EndFirstBattle;
        FreeAllWindowBuffers();
        SetMainCallback2(CB2_InitBattle);
        RestartWildEncounterImmunitySteps();
        ClearPoisonStepCounter();
        IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
        IncrementGameStat(GAME_STAT_WILD_BATTLES);
        IncrementDailyWildBattles();
        TryUpdateGymLeaderRematchFromWild();
    }
}

static void CB2_EndFirstBattle(void)
{
    Overworld_ClearSavedMusic();
    DowngradeBadPoison();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}*/

//prob won't use these either believe is linked to match call feature
static void TryUpdateGymLeaderRematchFromWild(void)
{
    //if (GetGameStat(GAME_STAT_WILD_BATTLES) % 60 == 0)
    //    UpdateGymLeaderRematch();
}

static void TryUpdateGymLeaderRematchFromTrainer(void)
{
    //if (GetGameStat(GAME_STAT_TRAINER_BATTLES) % 20 == 0)
    //    UpdateGymLeaderRematch();
}

static u16 GetTrainerAFlag(void)
{
    return TRAINER_FLAGS_START + TRAINER_BATTLE_PARAM.opponentA;
}

static u16 GetTrainerBFlag(void)
{
    return TRAINER_FLAGS_START + TRAINER_BATTLE_PARAM.opponentB;
}

static bool32 IsPlayerDefeated(u32 battleOutcome)
{
    switch (battleOutcome)
    {
    case B_OUTCOME_LOST:
    case B_OUTCOME_DREW:
        return TRUE;
    case B_OUTCOME_WON:
    case B_OUTCOME_RAN:
    case B_OUTCOME_PLAYER_TELEPORTED:
    case B_OUTCOME_MON_FLED:
    case B_OUTCOME_CAUGHT:
        return FALSE;
    default:
        return FALSE;
    }
}

void ResetTrainerOpponentIds(void)
{
    TRAINER_BATTLE_PARAM.opponentA = 0;
    TRAINER_BATTLE_PARAM.opponentB = 0;
}

void InitTrainerBattleParameter(void)
{
    memset(gTrainerBattleParameter.data, 0, sizeof(TrainerBattleParameter));
    sTrainerBattleEndScript = NULL;
}

void TrainerBattleLoadArgs(const u8 *data)
{
    InitTrainerBattleParameter();
    memcpy(gTrainerBattleParameter.data, data, sizeof(TrainerBattleParameter));
    sTrainerBattleEndScript = (u8*)data + sizeof(TrainerBattleParameter);
}

void TrainerBattleLoadArgsTrainerA(const u8 *data)
{
    TrainerBattleParameter *temp = (TrainerBattleParameter*)data;

    TRAINER_BATTLE_PARAM.playMusicA = temp->params.playMusicA;
    TRAINER_BATTLE_PARAM.objEventLocalIdA = temp->params.objEventLocalIdA;
    TRAINER_BATTLE_PARAM.opponentA = temp->params.opponentA;
    TRAINER_BATTLE_PARAM.introTextA = temp->params.introTextA;
    TRAINER_BATTLE_PARAM.defeatTextA = temp->params.defeatTextA;
    TRAINER_BATTLE_PARAM.battleScriptRetAddrA = temp->params.battleScriptRetAddrA;
}

void TrainerBattleLoadArgsTrainerB(const u8 *data)
{
    TrainerBattleParameter *temp = (TrainerBattleParameter*)data;

    TRAINER_BATTLE_PARAM.playMusicB = temp->params.playMusicB;
    TRAINER_BATTLE_PARAM.objEventLocalIdB = temp->params.objEventLocalIdB;
    TRAINER_BATTLE_PARAM.opponentB = temp->params.opponentB;
    TRAINER_BATTLE_PARAM.introTextB = temp->params.introTextB;
    TRAINER_BATTLE_PARAM.defeatTextB = temp->params.defeatTextB;
    TRAINER_BATTLE_PARAM.battleScriptRetAddrB = temp->params.battleScriptRetAddrB;
}

// loads trainer A parameter to trainer B. Used for second trainer in trainer_see.c
void TrainerBattleLoadArgsSecondTrainer(const u8 *data)
{
    TrainerBattleParameter *temp = (TrainerBattleParameter*)data;

    TRAINER_BATTLE_PARAM.playMusicB = temp->params.playMusicA;
    TRAINER_BATTLE_PARAM.objEventLocalIdB = temp->params.objEventLocalIdA;
    TRAINER_BATTLE_PARAM.opponentB = temp->params.opponentA;
    TRAINER_BATTLE_PARAM.introTextB = temp->params.introTextA;
    TRAINER_BATTLE_PARAM.defeatTextB = temp->params.defeatTextA;
    TRAINER_BATTLE_PARAM.battleScriptRetAddrB = temp->params.battleScriptRetAddrA;
}

void SetMapVarsToTrainerA(void)
{
    if (TRAINER_BATTLE_PARAM.objEventLocalIdA != 0)
    {
        gSpecialVar_LastTalked = TRAINER_BATTLE_PARAM.objEventLocalIdA;
        gSelectedObjectEvent = GetObjectEventIdByLocalIdAndMap(TRAINER_BATTLE_PARAM.objEventLocalIdA, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    }
}

void SetMapVarsToTrainerB(void)
{
    if (TRAINER_BATTLE_PARAM.objEventLocalIdB != 0)
    {
        gSpecialVar_LastTalked = TRAINER_BATTLE_PARAM.objEventLocalIdB;
        gSelectedObjectEvent = GetObjectEventIdByLocalIdAndMap(TRAINER_BATTLE_PARAM.objEventLocalIdB, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    }
}

// expects parameters have been loaded correctly with TrainerBattleLoadArgs
const u8 *BattleSetup_ConfigureTrainerBattle(const u8 *data)
{
    switch (TRAINER_BATTLE_PARAM.mode)
    {
    case TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT:
        return EventScript_DoNoIntroTrainerBattle;
    case TRAINER_BATTLE_DOUBLE:
        SetMapVarsToTrainerA();
        return EventScript_TryDoDoubleTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT:
        if (gApproachingTrainerId == 0)
        {
            SetMapVarsToTrainerA();
        }
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC:
        SetMapVarsToTrainerA();
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE:
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC:
        SetMapVarsToTrainerA();
        return EventScript_TryDoDoubleTrainerBattle;
    //previously tied to vs seeker on longer using replace w new rematch setup
    //may do states based on badge count so trainer party size increase
    //well could rematch match lvl then have rematch states
    //that expand party something idk -vsonic important
    /*case TRAINER_BATTLE_REMATCH_DOUBLE:
        QL_FinishRecordingScene();
        SetMapVarsToTrainerA();
        TRAINER_BATTLE_PARAM.opponentA = GetRematchTrainerId(TRAINER_BATTLE_PARAM.opponentA);
        return EventScript_TryDoDoubleRematchBattle;
    case TRAINER_BATTLE_REMATCH:
        QL_FinishRecordingScene();
        SetMapVarsToTrainerA();
        TRAINER_BATTLE_PARAM.opponentA = GetRematchTrainerId(TRAINER_BATTLE_PARAM.opponentA);
        return EventScript_TryDoRematchBattle;*/
    case TRAINER_BATTLE_EARLY_RIVAL:
        SetMapVarsToTrainerA();
        return EventScript_DoNoIntroTrainerBattle;
    case TRAINER_BATTLE_TWO_TRAINERS_NO_INTRO:
        gNoOfApproachingTrainers = 2; // set TWO_OPPONENTS gBattleTypeFlags
        gApproachingTrainerId = 1; // prevent trainer approach
        return EventScript_DoNoIntroTrainerBattle;
    default:
        if (gApproachingTrainerId == 0)
        {
            SetMapVarsToTrainerA();
        }
        return EventScript_TryDoNormalTrainerBattle;
    }
}

void ConfigureAndSetUpOneTrainerBattle(u8 trainerObjEventId, const u8 *trainerScript)
{
    gSelectedObjectEvent = trainerObjEventId;
    gSpecialVar_LastTalked = gObjectEvents[trainerObjEventId].localId;
    TrainerBattleLoadArgs(trainerScript + 1);
    BattleSetup_ConfigureTrainerBattle(trainerScript + 1);
    ScriptContext_SetupScript(EventScript_StartTrainerApproach);
    LockPlayerFieldControls();
}


void ConfigureTwoTrainersBattle(u8 trainerObjEventId, const u8 *trainerScript)
{
    gSelectedObjectEvent = trainerObjEventId;
    gSpecialVar_LastTalked = gObjectEvents[trainerObjEventId].localId;

    if (gApproachingTrainerId == 0) 
        TrainerBattleLoadArgs(trainerScript + 1);
    else 
        TrainerBattleLoadArgsSecondTrainer(trainerScript + 1);

    BattleSetup_ConfigureTrainerBattle(trainerScript + 1);
}

void SetUpTwoTrainersBattle(void)
{
    ScriptContext_SetupScript(EventScript_StartTrainerApproach);
    LockPlayerFieldControls();
}

#define OPCODE_OFFSET 1
bool32 GetTrainerFlagFromScriptPointer(const u8 *data)
{
    TrainerBattleParameter *temp = (TrainerBattleParameter*)(data + OPCODE_OFFSET);
    return FlagGet(TRAINER_FLAGS_START + temp->params.opponentA);
}
#undef OPCODE_OFFSET

// Set trainer's movement type so they stop and remain facing that direction
// Note: Only for trainers who are spoken to directly
//       For trainers who spot the player this is handled by PlayerFaceApproachingTrainer
void SetTrainerFacingDirection(void)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[gSelectedObjectEvent];
    SetTrainerMovementType(objectEvent, GetTrainerFacingDirectionMovementType(objectEvent->facingDirection));
}

u8 GetTrainerBattleMode(void)
{
    return TRAINER_BATTLE_PARAM.mode;
}

u16 GetRivalBattleFlags(void)
{
    return TRAINER_BATTLE_PARAM.rivalBattleFlags;
}

#define TRAINER_REMATCH
bool8 GetTrainerFlag(void)
{
    /*if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        return GetBattlePyramidTrainerFlag(gSelectedObjectEvent);
    else if (InTrainerHill())
        return GetHillTrainerFlag(gSelectedObjectEvent);
    else*/
        return FlagGet(GetTrainerAFlag());
}

void SetBattledTrainerFlags(void)
{
    if (TRAINER_BATTLE_PARAM.opponentB != 0)
        FlagSet(GetTrainerBFlag());
    FlagSet(GetTrainerAFlag());
}

// not used
static void SetBattledTrainerFlag2(void)
{
    FlagSet(GetTrainerAFlag());
}

bool8 HasTrainerBeenFought(u16 trainerId)
{
    return FlagGet(TRAINER_FLAGS_START + trainerId);
}

void SetTrainerFlag(u16 trainerId)
{
    FlagSet(TRAINER_FLAGS_START + trainerId);
}

void ClearTrainerFlag(u16 trainerId)
{
    FlagClear(TRAINER_FLAGS_START + trainerId);
}

void BattleSetup_StartTrainerBattle(void)
{
    if (gNoOfApproachingTrainers == 2)
    {
        /*if (FollowerNPCIsBattlePartner())
            gBattleTypeFlags = (BATTLE_TYPE_MULTI | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_TRAINER);
        else*/
            gBattleTypeFlags = (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_TRAINER);
    }
    else
    {
        /*if (FollowerNPCIsBattlePartner())
        {
            gBattleTypeFlags = (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TRAINER);
            TRAINER_BATTLE_PARAM.opponentB = 0xFFFF;
        }
        else*/
        {
            gBattleTypeFlags = (BATTLE_TYPE_TRAINER);
        }
    }

    if (GetTrainerBattleMode() == TRAINER_BATTLE_EARLY_RIVAL && GetRivalBattleFlags() & RIVAL_BATTLE_TUTORIAL)
        gBattleTypeFlags |= BATTLE_TYPE_FIRST_BATTLE;

    /*if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
    {
        VarSet(VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;

        if (gNoOfApproachingTrainers == 2)
        {
            FillFrontierTrainersParties(1);
            ZeroMonData(&gEnemyParty[1]);
            ZeroMonData(&gEnemyParty[2]);
            ZeroMonData(&gEnemyParty[4]);
            ZeroMonData(&gEnemyParty[5]);
        }
        else
        {
            FillFrontierTrainerParty(1);
            ZeroMonData(&gEnemyParty[1]);
            ZeroMonData(&gEnemyParty[2]);
        }

        MarkApproachingPyramidTrainersAsBattled();
    }
    else if (InTrainerHillChallenge())
    {
        gBattleTypeFlags |= BATTLE_TYPE_TRAINER_HILL;

        if (gNoOfApproachingTrainers == 2)
            FillHillTrainersParties();
        else
            FillHillTrainerParty();

        SetHillTrainerFlag();
    }
    else*/ if (GetTrainerBattleType(TRAINER_BATTLE_PARAM.opponentA) == TRAINER_BATTLE_TYPE_DOUBLES)
    {
        gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
    }

    sNoOfPossibleTrainerRetScripts = gNoOfApproachingTrainers;
    gNoOfApproachingTrainers = 0;
    sShouldCheckTrainerBScript = FALSE;
    gWhichTrainerToFaceAfterBattle = 0;
    gMain.savedCallback = CB2_EndTrainerBattle;

    /*if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE || InTrainerHillChallenge())
        DoBattlePyramidTrainerHillBattle();
    else*/
        DoTrainerBattle();

    ScriptContext_Stop();
}

static void SaveChangesToPlayerParty(void)
{
    u8 i = 0, j = 0;
    u8 participatedPokemon = VarGet(B_VAR_SKY_BATTLE);
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if ((participatedPokemon >> i & 1) == 1)
        {
            SavePlayerPartyMon(i, &gPlayerParty[j]);
            j++;
        }
    }
}

//idk what for unsure if both are just for sky battles
//which I won't be using,
//they're just annoying
static void HandleBattleVariantEndParty(void)
{
    if (B_FLAG_SKY_BATTLE == 0 || !FlagGet(B_FLAG_SKY_BATTLE))
        return;
    SaveChangesToPlayerParty();
    LoadPlayerParty();
    FlagClear(B_FLAG_SKY_BATTLE);
}

static void CB2_EndTrainerBattle(void)
{
    HandleBattleVariantEndParty();

     gIsDebugBattle = FALSE;


    if (GetTrainerBattleMode() == TRAINER_BATTLE_EARLY_RIVAL)
    {
        if (IsPlayerDefeated(gBattleOutcome) == TRUE)
        {
            gSpecialVar_Result = TRUE;
            if (GetRivalBattleFlags() & RIVAL_BATTLE_HEAL_AFTER)
            {
                HealPlayerParty();
            }
            else
            {
                SetMainCallback2(CB2_WhiteOut);
                return;
            }            
            
        }
        else
        {
            gSpecialVar_Result = FALSE;
        }
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        SetBattledTrainerFlags();
        QuestLogEvents_HandleEndTrainerBattle();
        

    }
    else
    {
       /* if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_SECRET_BASE)
        {
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        }
        else */
        if (IsPlayerDefeated(gBattleOutcome) == TRUE)
        {
            SetMainCallback2(CB2_WhiteOut);
        }
        else
        {
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
            SetBattledTrainerFlags();
            QuestLogEvents_HandleEndTrainerBattle();
        }
    }
}

static void CB2_EndRematchBattle(void) //can't just remove rematch far too difficult, have change every trainer script
{
    /*if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_SECRET_BASE)
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
    else */if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        SetBattledTrainerFlags();
        //ClearRematchStateOfLastTalked();
        ResetDeferredLinkEvent();
    }
}

void StartRematchBattle(void)
{
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    gMain.savedCallback = CB2_EndRematchBattle;
    DoTrainerBattle();
    ScriptContext_Stop();
}

void ShowTrainerIntroSpeech(void)
{
    ShowFieldMessage(GetIntroSpeechOfApproachingTrainer());
}

const u8 *BattleSetup_GetScriptAddrAfterBattle(void)
{
    if (sTrainerBattleEndScript != NULL)
        return sTrainerBattleEndScript;
    else
        return EventScript_TestSignpostMsg;
}

const u8 *BattleSetup_GetTrainerPostBattleScript(void)
{
    if (sShouldCheckTrainerBScript)
    {
        sShouldCheckTrainerBScript = FALSE;
        if (TRAINER_BATTLE_PARAM.battleScriptRetAddrB != NULL)
        {
            gWhichTrainerToFaceAfterBattle = 1;
            return TRAINER_BATTLE_PARAM.battleScriptRetAddrB;
        }
    }
    else
    {
        if (TRAINER_BATTLE_PARAM.battleScriptRetAddrA != NULL)
        {
            gWhichTrainerToFaceAfterBattle = 0;
            return TRAINER_BATTLE_PARAM.battleScriptRetAddrA;
        }
    }

    return EventScript_TryGetTrainerScript;
}

void ShowTrainerCantBattleSpeech(void)
{
    ShowFieldMessage(GetTrainerCantBattleSpeech());
}

void PlayTrainerEncounterMusic(void)
{
    u16 trainerId;
    u16 music;

    if (gApproachingTrainerId == 0)
        trainerId = TRAINER_BATTLE_PARAM.opponentA;
    else
        trainerId = TRAINER_BATTLE_PARAM.opponentB;

    if (!QL_IS_PLAYBACK_STATE
    && TRAINER_BATTLE_PARAM.mode != TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC
    && TRAINER_BATTLE_PARAM.mode != TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC)
    {
        switch (GetTrainerEncounterMusicId(TRAINER_BATTLE_PARAM.opponentA))
        {
        case TRAINER_ENCOUNTER_MUSIC_FEMALE:
        case TRAINER_ENCOUNTER_MUSIC_GIRL:
        case TRAINER_ENCOUNTER_MUSIC_TWINS:
            music = MUS_ENCOUNTER_GIRL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_MALE:
        case TRAINER_ENCOUNTER_MUSIC_INTENSE:
        case TRAINER_ENCOUNTER_MUSIC_COOL:
        case TRAINER_ENCOUNTER_MUSIC_SWIMMER:
        case TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR:
        case TRAINER_ENCOUNTER_MUSIC_HIKER:
        case TRAINER_ENCOUNTER_MUSIC_INTERVIEWER:
        case TRAINER_ENCOUNTER_MUSIC_RICH:
            music = MUS_ENCOUNTER_BOY;
            break;
        default:
            music = MUS_ENCOUNTER_ROCKET;
            break;
        }
        PlayNewMapMusic(music);
    }
}

static const u8 *ReturnEmptyStringIfNull(const u8 *string)
{
    if (string == NULL)
        return gString_Dummy;
    else
        return string;
}

static const u8 *GetIntroSpeechOfApproachingTrainer(void)
{
    if (gApproachingTrainerId == 0)
        return ReturnEmptyStringIfNull(TRAINER_BATTLE_PARAM.introTextA);
    else
        return ReturnEmptyStringIfNull(TRAINER_BATTLE_PARAM.introTextB);
}

const u8 *GetTrainerALoseText(void)
{
    const u8 *string;

    /*if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_SECRET_BASE)
        string = GetSecretBaseTrainerLoseText();
    else*/
        string = TRAINER_BATTLE_PARAM.defeatTextA;

    StringExpandPlaceholders(gStringVar4, ReturnEmptyStringIfNull(string));
    return gStringVar4;
}

const u8 *GetTrainerBLoseText(void)
{
    StringExpandPlaceholders(gStringVar4, ReturnEmptyStringIfNull(TRAINER_BATTLE_PARAM.defeatTextB));
    return gStringVar4;
}

const u8 *GetTrainerWonSpeech(void)
{
    return ReturnEmptyStringIfNull(TRAINER_BATTLE_PARAM.victoryText);
}

static const u8 *GetTrainerCantBattleSpeech(void)
{
    return ReturnEmptyStringIfNull(TRAINER_BATTLE_PARAM.cannotBattleText);
}

void SetMultiTrainerBattle(struct ScriptContext *ctx)
{
    InitTrainerBattleParameter();

    TRAINER_BATTLE_PARAM.opponentA = ScriptReadHalfword(ctx);
    TRAINER_BATTLE_PARAM.defeatTextA = (u8*)ScriptReadWord(ctx);
    TRAINER_BATTLE_PARAM.opponentB = ScriptReadHalfword(ctx);
    TRAINER_BATTLE_PARAM.defeatTextB = (u8*)ScriptReadWord(ctx);
    gPartnerTrainerId = TRAINER_PARTNER(ScriptReadHalfword(ctx));
};

