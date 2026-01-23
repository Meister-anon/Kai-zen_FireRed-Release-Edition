#ifndef GUARD_BATTLE_STRING_IDS_H
#define GUARD_BATTLE_STRING_IDS_H

//actually did I remove the need for this
#define BATTLESTRINGS_ID_ADDER  12 // all battlestrings have its ID + 12, because first 5 are reserved

#define STRINGID_INTROMSG       0
#define STRINGID_INTROSENDOUT   1
#define STRINGID_RETURNMON      2
#define STRINGID_SWITCHINMON    3
#define STRINGID_USEDMOVE       4
#define STRINGID_BATTLEEND      5
#define STRINGID_TRAINERSLIDE   6

//Damaging weather ids 
//for gBattleCommunication
#define B_MSG_SANDSTORM_ID  0
#define B_MSG_HAIL_ID       1
#define B_MSG_ACID_RAIN_ID  2

// gInobedientStringIds
#define B_MSG_LOAFING            0
#define B_MSG_WONT_OBEY          1
#define B_MSG_TURNED_AWAY        2
#define B_MSG_PRETEND_NOT_NOTICE 3
#define NUM_DISOBEY_STRINGS         4 // For randomly selecting a disobey string


// gFlashFireStringIds
#define B_MSG_FLASH_FIRE_BOOST    0
#define B_MSG_FLASH_FIRE_NO_BOOST 1

// gUproarOverTurnStringIds
#define B_MSG_UPROAR_CONTINUES  0
#define B_MSG_UPROAR_ENDS       1

// gMissStringIds					//need add logic
/*#define B_MSG_MISSED       0
#define B_MSG_PROTECTED    1
#define B_MSG_AVOIDED_ATK  2
#define B_MSG_AVOIDED_DMG  3
#define B_MSG_GROUND_MISS  4
#define B_MSG_ABILITY_TYPE_MISS 5*/

// gProtectLikeUsedStringIds		//need add logic
#define B_MSG_PROTECTED_ITSELF 0
#define B_MSG_BRACED_ITSELF    1
#define B_MSG_PROTECT_FAILED   2
#define B_MSG_PROTECTED_TEAM   3

// gStatUpStringIds
#define B_MSG_ATTACKER_STAT_ROSE 0
#define B_MSG_DEFENDER_STAT_ROSE 1
#define B_MSG_STAT_WONT_INCREASE 2
#define B_MSG_STAT_ROSE_EMPTY    3
#define B_MSG_STAT_ROSE_ITEM     4
#define B_MSG_USED_DIRE_HIT      5

// gStatDownStringIds
#define B_MSG_ATTACKER_STAT_FELL 0
#define B_MSG_DEFENDER_STAT_FELL 1
#define B_MSG_STAT_WONT_DECREASE 2
#define B_MSG_STAT_FELL_EMPTY    3

// gSwitchInAbilityStringIds
#define B_MSG_SWITCHIN_MOLDBREAKER      0
#define B_MSG_SWITCHIN_TERAVOLT         1
#define B_MSG_SWITCHIN_TURBOBLAZE       2
#define B_MSG_SWITCHIN_SLOWSTART        3
#define B_MSG_SWITCHIN_UNNERVE          4
#define B_MSG_SWITCHIN_ANTICIPATION     5
#define B_MSG_SWITCHIN_FOREWARN         6
#define B_MSG_SWITCHIN_PRESSURE         7
#define B_MSG_SWITCHIN_DARKAURA         8
#define B_MSG_SWITCHIN_FAIRYAURA        9
#define B_MSG_SWITCHIN_AURABREAK        10
#define B_MSG_SWITCHIN_COMATOSE         11
#define B_MSG_SWITCHIN_SCREENCLEANER    12
#define B_MSG_SWITCHIN_ASONE            13
#define B_MSG_SWITCHIN_CURIOUS_MEDICINE 14
#define B_MSG_SWITCHIN_PASTEL_VEIL      15
#define B_MSG_SWITCHIN_CORRUPTION       16
#define B_MSG_SWITCHIN_STENCH			17
#define B_MSG_SWITCHIN_NEUTRALIZING_GAS 18
#define B_MSG_SWITCHIN_IMMUTABLE_WIND 19
#define B_MSG_SWITCHIN_BANDIT			20
#define B_MSG_SWITCHIN_FLUORESCENT      21
#define B_MSG_SWITCHIN_WONDERGUARD      22
#define B_MSG_SWITCHIN_SUPERSWEET_SYRUP 23

// gMentalHerbCureStringIds
#define B_MSG_MENTALHERBCURE_INFATUATION       0
#define B_MSG_MENTALHERBCURE_TAUNT             1
#define B_MSG_MENTALHERBCURE_ENCORE            2
#define B_MSG_MENTALHERBCURE_TORMENT           3
#define B_MSG_MENTALHERBCURE_HEALBLOCK         4
#define B_MSG_MENTALHERBCURE_DISABLE           5

// gBerryEffectStringIds
#define B_MSG_CURED_PROBLEM     0
#define B_MSG_NORMALIZED_STATUS 1

//  gDmgHazardsStringIds
#define B_MSG_PKMNHURTBYSPIKES 0
#define B_MSG_STEALTHROCKDMG 1
#define B_MSG_SHARPSTEELDMG 2
#define B_MSG_POINTEDSTONESFLOAT 3
#define B_MSG_SPIKESSCATTERED 4
#define B_MSG_SHARPSTEELFLOATS 5

// gTerrainStringIds
#define B_MSG_TERRAIN_SET_MISTY     0
#define B_MSG_TERRAIN_SET_ELECTRIC  1
#define B_MSG_TERRAIN_SET_PSYCHIC   2
#define B_MSG_TERRAIN_SET_GRASSY    3
#define B_MSG_TERRAIN_END_MISTY     4
#define B_MSG_TERRAIN_END_ELECTRIC  5
#define B_MSG_TERRAIN_END_PSYCHIC   6
#define B_MSG_TERRAIN_END_GRASSY    7
#define B_MSG_TERRAIN_COUNT         8

// gStartingStatusStringIds
#define B_MSG_TERRAIN_SET_MISTY     0
#define B_MSG_TERRAIN_SET_ELECTRIC  1
#define B_MSG_TERRAIN_SET_PSYCHIC   2
#define B_MSG_TERRAIN_SET_GRASSY    3
#define B_MSG_SET_TRICK_ROOM        4
#define B_MSG_SET_MAGIC_ROOM        5
#define B_MSG_SET_WONDER_ROOM       6
#define B_MSG_SET_TAILWIND          7
#define B_MSG_SET_RAINBOW           8
#define B_MSG_SET_SEA_OF_FIRE       9
#define B_MSG_SET_SWAMP             10
#define B_MSG_STARTING_STATUS_COUNT 11

//idk what's up with this but it breaks
//with the packed attribute on it
//needed preproc update for packed
// gWrappedStringIds
enum __attribute__((packed)) WrappedStringID
{
    B_MSG_WRAPPED_BIND,
    B_MSG_WRAPPED_WRAP,
    B_MSG_WRAPPED_FIRE_SPIN,
    B_MSG_WRAPPED_CLAMP,
    B_MSG_WRAPPED_WHIRLPOOL,
    B_MSG_WRAPPED_SAND_TOMB,
    B_MSG_WRAPPED_MAGMA_STORM,
    B_MSG_WRAPPED_SWARM,
    B_MSG_WRAPPED_SNAP_TRAP,
    B_MSG_WRAPPED_THUNDER_CAGE,
    NUM_TRAPPING_MOVES,    
};
//think all traps do slow
//several have extra effects
//think only whirlpool wrap does nothing extra? 
//bind does encore
//fire spin increases burn odds
//sand tomb drops acc
//magma storm just has guaranteed burn now and better acc
//swarm sets infestation for duration which does equiv of 1 stage def drop
//believe both clamp and snaptrap have flinch chance for duration
//-sounds op but should be wild w inner focus etc.
//thunder cage believe should have chance to paralyze each turn it does dmg

// The below IDs are all indexes into battle message tables,
// used to determine which of a set of messages to print.
// They are assigned to the MULTISTRING_CHOOSER byte of gBattleCommunication
// and read when e.g. the command printfromtable is used.

// gStatUpStringIds and gStatDownStringIds
enum StatChangedStringID
{
    B_MSG_ATTACKER_STAT_CHANGED,
    B_MSG_DEFENDER_STAT_CHANGED,
    B_MSG_STAT_WONT_CHANGE,
    B_MSG_STAT_CHANGE_EMPTY,
    B_MSG_STAT_CHANGED_ITEM,
    //B_MSG_USED_DIRE_HIT,
};

// gMissStringIds
enum MissStringID
{
    B_MSG_MISSED,
    B_MSG_PROTECTED,
    B_MSG_AVOIDED_ATK,
    B_MSG_AVOIDED_DMG,
    B_MSG_GROUND_MISS,
    B_MSG_ABILITY_TYPE_MISS,
};

// gAbsorbDrainStringIds
enum AbsorbDrainStringID
{
    B_MSG_ABSORB,
    B_MSG_ABSORB_OOZE,
};

// gLeechSeedStringIds
enum LeechSeedStringID
{
    B_MSG_LEECH_SEED_SET,
    B_MSG_LEECH_SEED_MISS,
    B_MSG_LEECH_SEED_FAIL,
    B_MSG_LEECH_SEED_DRAIN,
    B_MSG_LEECH_SEED_OOZE,
};

// gMoveWeatherChangeStringIds
//no move effect for strong winds
enum MoveWeatherChangeStringID
{
    B_MSG_STARTED_RAIN,
    B_MSG_STARTED_DOWNPOUR, //was unused
    B_MSG_STARTED_SUNLIGHT,
    B_MSG_WEATHER_FAILED,
    B_MSG_STARTED_SANDSTORM,    
    B_MSG_STARTED_HAIL,
    B_MSG_STARTED_SNOW,
    B_MSG_STARTED_MOONLIGHT,
    B_MSG_STARTED_ACID_RAIN,
    B_MSG_STARTED_FOG,
};

// gWeatherEndsStringIds
enum WeatherEndStringID
{
    B_MSG_WEATHER_END_RAIN,
    B_MSG_WEATHER_END_SUN,
    B_MSG_WEATHER_END_SANDSTORM,
    B_MSG_WEATHER_END_HAIL,
    B_MSG_WEATHER_END_SNOW,
    B_MSG_WEATHER_END_MOON,
    B_MSG_WEATHER_END_ACID_RAIN,
    B_MSG_WEATHER_END_FOG,
    B_MSG_WEATHER_END_STRONG_WINDS,
    B_MSG_WEATHER_END_COUNT
};

// gWeatherTurnStringIds
enum WeatherTurnStringID
{
    B_MSG_WEATHER_TURN_RAIN,
    B_MSG_WEATHER_TURN_DOWNPOUR,
    B_MSG_WEATHER_TURN_SUN,
    B_MSG_WEATHER_TURN_SANDSTORM,
    B_MSG_WEATHER_TURN_HAIL,
    B_MSG_WEATHER_TURN_SNOW,
    B_MSG_WEATHER_TURN_MOON,
    B_MSG_WEATHER_TURN_ACID_RAIN,
    B_MSG_WEATHER_TURN_FOG,
    B_MSG_WEATHER_TURN_STRONG_WINDS,
};

enum DamagingWeatherStringID
{
    B_MSG_SANDSTORM,
    B_MSG_HAIL,
    B_MSG_ACID_RAIN,
};

// gRainContinuesStringIds
#define B_MSG_RAIN_CONTINUES     0
#define B_MSG_DOWNPOUR_CONTINUES 1
#define B_MSG_RAIN_STOPPED       2


// gFirstTurnOfTwoStringIds
#define B_MSG_TURN1_RAZOR_WIND     0
#define B_MSG_TURN1_SOLAR_BEAM     1
#define B_MSG_TURN1_SKULL_BASH     2
#define B_MSG_TURN1_SKY_ATTACK     3
#define B_MSG_TURN1_FLY            4
#define B_MSG_TURN1_DIG            5
#define B_MSG_TURN1_DIVE           6
#define B_MSG_TURN1_BOUNCE         7
#define B_MSG_TURN1_PHANTOM_FORCE  8
#define B_MSG_TURN1_GEOMANCY       9
#define B_MSG_TURN1_FREEZE_SHOCK   10
#define B_MSG_TURN1_SKY_DROP       11
#define B_MSG_TURN1_METEOR_BEAM    12
#define B_MSG_TURN1_COLD_FRONT     13

//#define NUM_TRAPPING_MOVES 10

//read battle_message.c  gbattlestringstable from line STRINGID_PKMNGREWTOLV
//copy stringId  and string within parenthesis excluding compound_string

//may put definiion in battle_message.c file
//simpler to have all the buff stuff searchable

/* Battle String values
 * To create stringIds and assign text at same time
 *  Enum,                                                   txtstring */
    // todo: make some of those names less vague: attacker/target vs pkmn, etc.
#define BATTLE_STRING_DEFINITIONS(F) \
    F(STRINGID_TRAINER1LOSETEXT,                            ("{B_TRAINER1_LOSE_TEXT}")) \
    F(STRINGID_PKMNGAINEDEXP,                               ("{B_BUFF1} gained{B_BUFF2} {B_BUFF3} Exp. Points!\p"))\
    F(STRINGID_PKMNGREWTOLV,                                        ("{B_BUFF1} grew to\nLV. {B_BUFF2}!{WAIT_SE}\p"))\
    F(STRINGID_PKMNLEARNEDMOVE,                                        ("{B_BUFF1} learned\n{B_BUFF2}!{WAIT_SE}\p"))\
    F(STRINGID_TRYTOLEARNMOVE1,                                        ("{B_BUFF1} is trying to\nlearn {B_BUFF2}.\p"))\
    F(STRINGID_TRYTOLEARNMOVE2,                                        ("But, {B_BUFF1} can't learn\nmore than four moves.\p"))\
    F(STRINGID_TRYTOLEARNMOVE3,                                        ("Delete a move to make\nroom for {B_BUFF2}?"))\
    F(STRINGID_PKMNFORGOTMOVE,                                        ("{B_BUFF1} forgot\n{B_BUFF2}.\p"))\
    F(STRINGID_STOPLEARNINGMOVE,                                        ("{PAUSE 32}Stop learning\n{B_BUFF2}?"))\
    F(STRINGID_DIDNOTLEARNMOVE,                                        ("{B_BUFF1} did not learn\n{B_BUFF2}.\p"))\
    F(STRINGID_PKMNLEARNEDMOVE2,                                        ("{B_ATK_NAME_WITH_PREFIX} learned\n{B_BUFF1}!"))\
    F(STRINGID_TRAINER2CLASS,                              ("{B_TRAINER2_CLASS}"))\
    F(STRINGID_TRAINER2NAME,                              ("{B_TRAINER2_NAME}"))\
    F(STRINGID_PLAYERWHITEDOUT,                              ("{B_PLAYER_NAME} whited out!{PAUSE_UNTIL_PRESS}"))\
    F(STRINGID_MONTOOSCAREDTOMOVE,                              ("{B_ATK_NAME_WITH_PREFIX} is too scared to move!"))\
    F(STRINGID_GHOSTGETOUTGETOUT,                              ("GHOST: Get out…… Get out……"))\
    F(STRINGID_SILPHSCOPEUNVEILED,                              ("SILPH SCOPE unveiled the GHOST's\nidentity!"))\
    F(STRINGID_GHOSTWASMAROWAK,                              ("The GHOST was MAROWAK!\p\n"))\
    F(STRINGID_TRAINER1MON1COMEBACK,                              ("{B_TRAINER1_NAME}: {B_OPPONENT_MON1_NAME}, come back!"))\
    F(STRINGID_TRAINER1WINTEXT,                              ("{B_TRAINER1_WIN_TEXT}"))\
    F(STRINGID_TRAINER1MON2COMEBACK,                              ("{B_TRAINER1_NAME}: {B_OPPONENT_MON2_NAME}, come back!"))\
    F(STRINGID_TRAINER1MON1AND2COMEBACK,                              ("{B_TRAINER1_NAME}: {B_OPPONENT_MON1_NAME} and\n{B_OPPONENT_MON2_NAME}, come back!"))\
    F(STRINGID_ATTACKMISSED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s\nattack missed!"))\
    F(STRINGID_PKMNPROTECTEDITSELF,                                        ("{B_DEF_NAME_WITH_PREFIX}\nprotected itself!"))\
    F(STRINGID_STATSWONTINCREASE2,                                        ("{B_ATK_NAME_WITH_PREFIX}'s stats won't\ngo any higher!"))\
    F(STRINGID_AVOIDEDDAMAGE,                                        ("{B_DEF_NAME_WITH_PREFIX} avoided\ndamage with {B_DEF_ABILITY}!"))\
    F(STRINGID_ITDOESNTAFFECT,                                        ("It doesn't affect\n{B_DEF_NAME_WITH_PREFIX}…"))\
    F(STRINGID_ATTACKERFAINTED,                                        ("{B_ATK_NAME_WITH_PREFIX}\nfainted!\p"))\
    F(STRINGID_TARGETFAINTED,                                        ("{B_DEF_NAME_WITH_PREFIX}\nfainted!\p"))\
    F(STRINGID_PLAYERGOTMONEY,                                        ("{B_PLAYER_NAME} got ¥{B_BUFF1}\nfor winning!\p"))\
    F(STRINGID_PLAYERWHITEOUT,                                        ("{B_PLAYER_NAME} is out of\nusable POKéMON!\p"))\
    F(STRINGID_PLAYERWHITEOUT2,                                        ("{B_PLAYER_NAME} panicked and lost ¥{B_BUFF1}…\p… … … …\p{B_PLAYER_NAME} whited out!{PAUSE_UNTIL_PRESS}"))\
    F(STRINGID_PREVENTSESCAPE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} prevents\nescape with {B_SCR_ACTIVE_ABILITY}!\p"))\
    F(STRINGID_HITXTIMES,                                        ("Hit {B_BUFF1} time(s)!"))\
    F(STRINGID_PKMNFROSTBITTEN,                                        ("{B_EFF_NAME_WITH_PREFIX} got frostbite!"))\
    F(STRINGID_PKMNFELLASLEEP,                                        ("{B_EFF_NAME_WITH_PREFIX}\nfell asleep!"))\
    F(STRINGID_PKMNMADESLEEP,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade {B_EFF_NAME_WITH_PREFIX} sleep!"))\
    F(STRINGID_PKMNALREADYASLEEP,                                        ("{B_DEF_NAME_WITH_PREFIX} is\nalready asleep!"))\
    F(STRINGID_PKMNALREADYASLEEP2,                                        ("{B_ATK_NAME_WITH_PREFIX} is\nalready asleep!"))\
    F(STRINGID_PKMNWASNTAFFECTED,                                        ("{B_DEF_NAME_WITH_PREFIX}\nwasn't affected!"))\
    F(STRINGID_PKMNWASPOISONED,                                        ("{B_EFF_NAME_WITH_PREFIX}\nwas poisoned!"))\
    F(STRINGID_PKMNPOISONEDBY,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\npoisoned {B_EFF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNHURTBYPOISON,                                        ("{B_ATK_NAME_WITH_PREFIX} is hurt\nby poison!"))\
    F(STRINGID_PKMNALREADYPOISONED,                                        ("{B_DEF_NAME_WITH_PREFIX} is already\npoisoned."))\
    F(STRINGID_PKMNBADLYPOISONED,                                        ("{B_EFF_NAME_WITH_PREFIX} is badly\npoisoned!"))\
    F(STRINGID_PKMNENERGYDRAINED,                                        ("{B_DEF_NAME_WITH_PREFIX} had its\nenergy drained!"))\
    F(STRINGID_PKMNWASBURNED,                                        ("{B_EFF_NAME_WITH_PREFIX} was burned!"))\
    F(STRINGID_PKMNBURNEDBY,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nburned {B_EFF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNHURTBYBURN,                                        ("{B_ATK_NAME_WITH_PREFIX} is hurt\nby its burn!"))\
    F(STRINGID_PKMNHURTBYFREEZE,                                        ("{B_ATK_NAME_WITH_PREFIX} is hurt\nby the cold!"))\
    F(STRINGID_PKMNWASFROZEN,                                        ("{B_EFF_NAME_WITH_PREFIX} was\nfrozen!"))\
    F(STRINGID_PKMNFROZENBY,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nfroze {B_EFF_NAME_WITH_PREFIX} solid!"))\
    F(STRINGID_PKMNISFROZEN,                                        ("{B_ATK_NAME_WITH_PREFIX} is\nfrozen solid!"))\
    F(STRINGID_PKMNWASDEFROSTED,                                        ("{B_DEF_NAME_WITH_PREFIX} was\ndefrosted!"))\
    F(STRINGID_PKMNWASDEFROSTED2,                                        ("{B_ATK_NAME_WITH_PREFIX} was\ndefrosted!"))\
    F(STRINGID_PKMNWASDEFROSTEDBY,                                        ("{B_ATK_NAME_WITH_PREFIX} was\ndefrosted by {B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNWASPARALYZED,                                        ("{B_EFF_NAME_WITH_PREFIX} is paralyzed!\nIt may be unable to move!"))\
    F(STRINGID_PKMNWASPARALYZEDBY,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nparalyzed {B_EFF_NAME_WITH_PREFIX}!\lIt may be unable to move!"))\
    F(STRINGID_PKMNISPARALYZED,                                        ("{B_ATK_NAME_WITH_PREFIX} is paralyzed!\nIt can't move!"))\
    F(STRINGID_PKMNISALREADYPARALYZED,                                        ("{B_DEF_NAME_WITH_PREFIX} is\nalready paralyzed!"))\
    F(STRINGID_PKMNHEALEDPARALYSIS,                                        ("{B_DEF_NAME_WITH_PREFIX} was\nhealed of paralysis!"))\
    F(STRINGID_PKMNDREAMEATEN,                                        ("{B_DEF_NAME_WITH_PREFIX}'s\ndream was eaten!"))\
    F(STRINGID_STATSWONTINCREASE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\nwon't go higher!"))\
    F(STRINGID_STATSWONTDECREASE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwon't go lower!"))\
    F(STRINGID_TEAMSTOPPEDWORKING,                                        ("Your team's {B_BUFF1}\nstopped working!"))\
    F(STRINGID_FOESTOPPEDWORKING,                                        ("The foe's {B_BUFF1}\nstopped working!"))\
    F(STRINGID_PKMNISCONFUSED,                                        ("{B_ATK_NAME_WITH_PREFIX} is\nconfused!"))\
    F(STRINGID_PKMNHEALEDCONFUSION,                                        ("{B_ATK_NAME_WITH_PREFIX} snapped\nout of confusion!"))\
    F(STRINGID_PKMNWASCONFUSED,                                        ("{B_EFF_NAME_WITH_PREFIX} became\nconfused!"))\
    F(STRINGID_PKMNALREADYCONFUSED,                                        ("{B_DEF_NAME_WITH_PREFIX} is\nalready confused!"))\
    F(STRINGID_PKMNFELLINLOVE,                                        ("{B_DEF_NAME_WITH_PREFIX}\nfell in love!"))\
    F(STRINGID_PKMNINLOVEWITHBATTLER,                                        ("{B_ATK_NAME_WITH_PREFIX} is in love\nwith {B_SCR_ACTIVE_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNINLOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} is in love!"))\
    F(STRINGID_PKMNIMMOBILIZEDBYLOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} is\nimmobilized by love!"))\
    F(STRINGID_PKMNBLOWNAWAY,                                        ("{B_DEF_NAME_WITH_PREFIX} was\nblown away!"))\
    F(STRINGID_PKMNCHANGEDTYPE,                                        ("{B_ATK_NAME_WITH_PREFIX} transformed\ninto the {B_BUFF1} type!"))\
    F(STRINGID_PKMNFLINCHED,                                        ("{B_ATK_NAME_WITH_PREFIX} flinched!"))\
    F(STRINGID_PKMNREGAINEDHEALTH,                                        ("{B_DEF_NAME_WITH_PREFIX} regained\nhealth!"))\
    F(STRINGID_PKMNHPFULL,                                        ("{B_DEF_NAME_WITH_PREFIX}'s\nHP is full!"))\
    F(STRINGID_PKMNRAISEDSPDEF,                                        ("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised SP. DEF!"))\
    F(STRINGID_PKMNRAISEDDEF,                                        ("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised DEFENSE!"))\
    F(STRINGID_PKMNCOVEREDBYVEIL,                                        ("{B_ATK_PREFIX2}'s party is covered\nby a veil!"))\
    F(STRINGID_PKMNUSEDSAFEGUARD,                                        ("{B_DEF_NAME_WITH_PREFIX}'s party is protected\nby SAFEGUARD!"))\
    F(STRINGID_PKMNSAFEGUARDEXPIRED,                                        ("{B_ATK_PREFIX3}'s party is no longer\nprotected by SAFEGUARD!"))\
    F(STRINGID_PKMNWENTTOSLEEP,                                        ("{B_ATK_NAME_WITH_PREFIX} went\nto sleep!"))\
    F(STRINGID_PKMNSLEPTHEALTHY,                                        ("{B_ATK_NAME_WITH_PREFIX} slept and\nbecame healthy!"))\
    F(STRINGID_PKMNWHIPPEDWHIRLWIND,                                        ("{B_ATK_NAME_WITH_PREFIX} whipped\nup a whirlwind!"))\
    F(STRINGID_PKMNTOOKSUNLIGHT,                                        ("{B_ATK_NAME_WITH_PREFIX} took\nin sunlight!"))\
    F(STRINGID_PKMNLOWEREDHEAD,                                        ("{B_ATK_NAME_WITH_PREFIX} lowered\nits head!"))\
    F(STRINGID_PKMNISGLOWING,                                        ("{B_ATK_NAME_WITH_PREFIX} is glowing!"))\
    F(STRINGID_PKMNFLEWHIGH,                                        ("{B_ATK_NAME_WITH_PREFIX} flew\nup high!"))\
    F(STRINGID_PKMNDUGHOLE,                                        ("{B_ATK_NAME_WITH_PREFIX} dug a hole!"))\
    F(STRINGID_PKMNSQUEEZEDBYBIND,                                        ("{B_DEF_NAME_WITH_PREFIX} was squeezed by\n{B_ATK_NAME_WITH_PREFIX}'s BIND!"))\
    F(STRINGID_PKMNTRAPPEDINVORTEX,                                        ("{B_DEF_NAME_WITH_PREFIX} was trapped\nin the vortex!"))\
    F(STRINGID_PKMNWRAPPEDBY,                                        ("{B_DEF_NAME_WITH_PREFIX} was WRAPPED by\n{B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNCLAMPED,                                        ("{B_ATK_NAME_WITH_PREFIX} CLAMPED\n{B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNHURTBY,                                        ("{B_ATK_NAME_WITH_PREFIX} is hurt\nby {B_BUFF1}!"))\
    F(STRINGID_PKMNFREEDFROM,                                        ("{B_ATK_NAME_WITH_PREFIX} was freed\nfrom {B_BUFF1}!"))\
    F(STRINGID_PKMNCRASHED,                                        ("{B_ATK_NAME_WITH_PREFIX} kept going\nand crashed!"))\
    F(STRINGID_PKMNSHROUDEDINMIST,                                        ("{B_ATK_PREFIX2} became\nshrouded in MIST!"))\
    F(STRINGID_PKMNPROTECTEDBYMIST,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is protected\nby MIST!"))\
    F(STRINGID_PKMNGETTINGPUMPED,                                        ("{B_ATK_NAME_WITH_PREFIX} is getting\npumped!"))\
    F(STRINGID_PKMNHITWITHRECOIL,                                        ("{B_ATK_NAME_WITH_PREFIX} is hit\nwith recoil!"))\
    F(STRINGID_PKMNPROTECTEDITSELF2,                                        ("{B_ATK_NAME_WITH_PREFIX} protected\nitself!"))\
    F(STRINGID_PKMNBUFFETEDBYSANDSTORM,                                        ("{B_ATK_NAME_WITH_PREFIX} is buffeted\nby the sandstorm!"))\
    F(STRINGID_PKMNPELTEDBYHAIL,                                        ("{B_ATK_NAME_WITH_PREFIX} is pelted\nby HAIL!"))\
    F(STRINGID_PKMNSEEDED,                                        ("{B_DEF_NAME_WITH_PREFIX} was seeded!"))\
    F(STRINGID_PKMNEVADEDATTACK,                                        ("{B_DEF_NAME_WITH_PREFIX} evaded\nthe attack!"))\
    F(STRINGID_PKMNSAPPEDBYLEECHSEED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s health is\nsapped by LEECH SEED!"))\
    F(STRINGID_PKMNFASTASLEEP,                                        ("{B_ATK_NAME_WITH_PREFIX} is fast\nasleep."))\
    F(STRINGID_PKMNWOKEUP,                                        ("{B_ATK_NAME_WITH_PREFIX} woke up!"))\
    F(STRINGID_PKMNUPROARKEPTAWAKE,                                        ("But {B_SCR_ACTIVE_NAME_WITH_PREFIX}'s UPROAR\nkept it awake!"))\
    F(STRINGID_PKMNWOKEUPINUPROAR,                                        ("{B_ATK_NAME_WITH_PREFIX} woke up\nin the UPROAR!"))\
    F(STRINGID_PKMNWOKEUPREFRESHED,                                        ("{B_ATK_NAME_WITH_PREFIX} woke up\nrefreshed!"))\
    F(STRINGID_PKMNCAUSEDUPROAR,                                        ("{B_ATK_NAME_WITH_PREFIX} caused\nan UPROAR!"))\
    F(STRINGID_PKMNMAKINGUPROAR,                                        ("{B_ATK_NAME_WITH_PREFIX} is making\nan UPROAR!"))\
    F(STRINGID_PKMNCALMEDDOWN,                                        ("{B_ATK_NAME_WITH_PREFIX} calmed down."))\
    F(STRINGID_PKMNCANTSLEEPINUPROAR,                                        ("But {B_DEF_NAME_WITH_PREFIX} can't\nsleep in an UPROAR!"))\
    F(STRINGID_PKMNSTOCKPILED,                                        ("{B_ATK_NAME_WITH_PREFIX} STOCKPILED\n{B_BUFF1}!"))\
    F(STRINGID_PKMNCANTSTOCKPILE,                                        ("{B_ATK_NAME_WITH_PREFIX} can't\nSTOCKPILE any more!"))\
    F(STRINGID_PKMNCANTSLEEPINUPROAR2,                                        ("But {B_DEF_NAME_WITH_PREFIX} can't\nsleep in an UPROAR!"))\
    F(STRINGID_UPROARKEPTPKMNAWAKE,                                        ("But the UPROAR kept\n{B_DEF_NAME_WITH_PREFIX} awake!"))\
    F(STRINGID_PKMNSTAYEDAWAKEUSING,                                        ("{B_DEF_NAME_WITH_PREFIX} stayed awake\nusing its {B_DEF_ABILITY}!"))\
    F(STRINGID_PKMNSTORINGENERGY,                                        ("{B_ATK_NAME_WITH_PREFIX} is storing\nenergy!"))\
    F(STRINGID_PKMNUNLEASHEDENERGY,                                        ("{B_ATK_NAME_WITH_PREFIX} unleashed\nenergy!"))\
    F(STRINGID_PKMNFATIGUECONFUSION,                                        ("{B_ATK_NAME_WITH_PREFIX} became\nconfused due to fatigue!"))\
    F(STRINGID_PKMNPICKEDUPITEM,                                        ("{B_PLAYER_NAME} picked up\n¥{B_BUFF1}!\p"))\
    F(STRINGID_PKMNUNAFFECTED,                                        ("{B_DEF_NAME_WITH_PREFIX} is\nunaffected!"))\
    F(STRINGID_PKMNTRANSFORMEDINTO,                                        ("{B_ATK_NAME_WITH_PREFIX} transformed\ninto {B_BUFF1}!"))\
    F(STRINGID_PKMNMADESUBSTITUTE,                                        ("{B_ATK_NAME_WITH_PREFIX} made\na SUBSTITUTE!"))\
    F(STRINGID_PKMNHASSUBSTITUTE,                                        ("{B_ATK_NAME_WITH_PREFIX} already\nhas a SUBSTITUTE!"))\
    F(STRINGID_SUBSTITUTEDAMAGED,                                        ("The SUBSTITUTE took damage\nfor {B_DEF_NAME_WITH_PREFIX}!\p"))\
    F(STRINGID_PKMNSUBSTITUTEFADED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s\nSUBSTITUTE faded!\p"))\
    F(STRINGID_PKMNMUSTRECHARGE,                                        ("{B_ATK_NAME_WITH_PREFIX} must\nrecharge!"))\
    F(STRINGID_PKMNRAGEBUILDING,                                        ("{B_DEF_NAME_WITH_PREFIX}'s RAGE\nis building!"))\
    F(STRINGID_PKMNMOVEWASDISABLED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwas disabled!"))\
    F(STRINGID_PKMNMOVEISDISABLED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE}\nis disabled!\p"))\
    F(STRINGID_PKMNMOVEDISABLEDNOMORE,                                        ("{B_ATK_NAME_WITH_PREFIX} is disabled\nno more!"))\
    F(STRINGID_PKMNGOTENCORE,                                        ("{B_DEF_NAME_WITH_PREFIX} got\nan ENCORE!"))\
    F(STRINGID_PKMNENCOREENDED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s ENCORE\nended!"))\
    F(STRINGID_PKMNTOOKAIM,                                        ("{B_ATK_NAME_WITH_PREFIX} took aim\nat {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNSKETCHEDMOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} SKETCHED\n{B_BUFF1}!"))\
    F(STRINGID_PKMNTRYINGTOTAKEFOE,                                        ("{B_ATK_NAME_WITH_PREFIX} is trying\nto take its foe with it!"))\
    F(STRINGID_PKMNTOOKFOE,                                        ("{B_DEF_NAME_WITH_PREFIX} took\n{B_ATK_NAME_WITH_PREFIX} with it!"))\
    F(STRINGID_PKMNREDUCEDPP,                                        ("{B_DEF_NAME_WITH_PREFIX}{B_BUFF3}\n{B_BUFF1} was reduced by {B_BUFF2}!"))\
    F(STRINGID_PKMNSTOLEITEM,                                        ("{B_ATK_NAME_WITH_PREFIX} stole\n{B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!"))\
    F(STRINGID_TARGETCANTESCAPENOW,                                        ("{B_DEF_NAME_WITH_PREFIX} can't\nescape now!"))\
    F(STRINGID_PKMNFELLINTONIGHTMARE,                                        ("{B_DEF_NAME_WITH_PREFIX} fell into\na NIGHTMARE!"))\
    F(STRINGID_PKMNLOCKEDINNIGHTMARE,                                        ("{B_ATK_NAME_WITH_PREFIX} is locked\nin a NIGHTMARE!"))\
    F(STRINGID_PKMNLAIDCURSE,                                        ("{B_ATK_NAME_WITH_PREFIX} cut its own HP and\nlaid a CURSE on {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNAFFLICTEDBYCURSE,                                        ("{B_ATK_NAME_WITH_PREFIX} is afflicted\nby the CURSE!"))\
    F(STRINGID_SPIKESSCATTERED,                                        ("SPIKES were scattered all around\nthe opponent's side!"))\
    F(STRINGID_PKMNHURTBYSPIKES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is hurt\nby SPIKES!"))\
    F(STRINGID_PKMNIDENTIFIED,                                        ("{B_ATK_NAME_WITH_PREFIX} identified\n{B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNPERISHCOUNTFELL,                                        ("{B_ATK_NAME_WITH_PREFIX}'s PERISH count\nfell to {B_BUFF1}!"))\
    F(STRINGID_PKMNBRACEDITSELF,                                        ("{B_ATK_NAME_WITH_PREFIX} braced\nitself!"))\
    F(STRINGID_PKMNENDUREDHIT,                                        ("{B_DEF_NAME_WITH_PREFIX} ENDURED\nthe hit!"))\
    F(STRINGID_MAGNITUDESTRENGTH,                                        ("MAGNITUDE {B_BUFF1}!"))\
    F(STRINGID_PKMNCUTHPMAXEDATTACK,                                        ("{B_ATK_NAME_WITH_PREFIX} cut its own HP\nand maximized ATTACK!"))\
    F(STRINGID_PKMNCOPIEDSTATCHANGES,                                        ("{B_ATK_NAME_WITH_PREFIX} copied\n{B_DEF_NAME_WITH_PREFIX}'s stat changes!"))\
    F(STRINGID_PKMNGOTFREE,                                        ("{B_ATK_NAME_WITH_PREFIX} got free of\nall traps!"))\
    F(STRINGID_PKMNSHEDLEECHSEED,                                        ("{B_ATK_NAME_WITH_PREFIX} shed\nLEECH SEED!"))\
    F(STRINGID_PKMNBLEWAWAYSPIKES,                                        ("{B_ATK_NAME_WITH_PREFIX} blew away\nSPIKES!"))\
    F(STRINGID_PKMNFLEDFROMBATTLE,                                        ("{B_ATK_NAME_WITH_PREFIX} fled from\nbattle!"))\
    F(STRINGID_PKMNFORESAWATTACK,                                        ("{B_ATK_NAME_WITH_PREFIX} foresaw\nan attack!"))\
    F(STRINGID_PKMNTOOKATTACK,                                        ("{B_DEF_NAME_WITH_PREFIX} took the\n{B_BUFF1} attack!"))\
    F(STRINGID_PKMNATTACK,                                        ("{B_BUFF1}'s attack!"))\
    F(STRINGID_PKMNCENTERATTENTION,                                        ("{B_ATK_NAME_WITH_PREFIX} became the\ncenter of attention!"))\
    F(STRINGID_PKMNCHARGINGPOWER,                                        ("{B_ATK_NAME_WITH_PREFIX} began\ncharging power!"))\
    F(STRINGID_NATUREPOWERTURNEDINTO,                                        ("NATURE POWER turned into\n{B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNSTATUSNORMAL,                                        ("{B_ATK_NAME_WITH_PREFIX}'s status\nreturned to normal!"))\
    F(STRINGID_PKMNHASNOMOVESLEFT,                                        ("{B_ATK_NAME_WITH_PREFIX} has no\nmoves left!\p"))\
    F(STRINGID_PKMNSUBJECTEDTOTORMENT,                                        ("{B_DEF_NAME_WITH_PREFIX} was subjected\nto TORMENT!"))\
    F(STRINGID_PKMNCANTUSEMOVETORMENT,                                        ("{B_ATK_NAME_WITH_PREFIX} can't use the same\nmove in a row due to the TORMENT!\p"))\
    F(STRINGID_PKMNTIGHTENINGFOCUS,                                        ("{B_ATK_NAME_WITH_PREFIX} is tightening\nits focus!"))\
    F(STRINGID_PKMNFELLFORTAUNT,                                        ("{B_DEF_NAME_WITH_PREFIX} fell for\nthe TAUNT!"))\
    F(STRINGID_PKMNCANTUSEMOVETAUNT,                                        ("{B_ATK_NAME_WITH_PREFIX} can't use\n{B_CURRENT_MOVE} after the TAUNT!\p"))\
    F(STRINGID_PKMNREADYTOHELP,                                        ("{B_ATK_NAME_WITH_PREFIX} is ready to\nhelp {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNSWITCHEDITEMS,                                        ("{B_ATK_NAME_WITH_PREFIX} switched\nitems with its opponent!"))\
    F(STRINGID_PKMNCOPIEDFOE,                                        ("{B_ATK_NAME_WITH_PREFIX} copied\n{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!"))\
    F(STRINGID_PKMNMADEWISH,                                        ("{B_ATK_NAME_WITH_PREFIX} made a WISH!"))\
    F(STRINGID_PKMNWISHCAMETRUE,                                        ("{B_BUFF1}'s WISH\ncame true!"))\
    F(STRINGID_PKMNPLANTEDROOTS,                                        ("{B_ATK_NAME_WITH_PREFIX} planted its roots!"))\
    F(STRINGID_PKMNABSORBEDNUTRIENTS,                                        ("{B_ATK_NAME_WITH_PREFIX} absorbed\nnutrients with its roots!"))\
    F(STRINGID_PKMNANCHOREDITSELF,                                        ("{B_DEF_NAME_WITH_PREFIX} anchored\nitself with its roots!"))\
    F(STRINGID_PKMNWASMADEDROWSY,                                        ("{B_ATK_NAME_WITH_PREFIX} made\n{B_DEF_NAME_WITH_PREFIX} drowsy!"))\
    F(STRINGID_PKMNKNOCKEDOFF,                                        ("{B_ATK_NAME_WITH_PREFIX} knocked off\n{B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!"))\
    F(STRINGID_PKMNSWAPPEDABILITIES,                                        ("{B_ATK_NAME_WITH_PREFIX} swapped abilities\nwith its opponent!"))\
    F(STRINGID_PKMNSEALEDOPPONENTMOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} sealed the\nopponent's moveシsス!"))\
    F(STRINGID_PKMNCANTUSEMOVESEALED,                                        ("{B_ATK_NAME_WITH_PREFIX} can't use the\nsealed {B_CURRENT_MOVE}!\p"))\
    F(STRINGID_PKMNWANTSGRUDGE,                                        ("{B_ATK_NAME_WITH_PREFIX} wants the\nopponent to bear a GRUDGE!"))\
    F(STRINGID_PKMNLOSTPPGRUDGE,                                        ("{B_ATK_NAME_WITH_PREFIX} lost\nPP due to the GRUDGE!"))\
    F(STRINGID_PKMNSHROUDEDITSELF,                                        ("{B_ATK_NAME_WITH_PREFIX} shrouded\nitself in {B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNMOVEBOUNCED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE}\nwas bounced back by MAGIC COAT!"))\
    F(STRINGID_PKMNWAITSFORTARGET,                                        ("{B_ATK_NAME_WITH_PREFIX} waits for its foe\nto make a move!"))\
    F(STRINGID_PKMNSNATCHEDMOVE,                                        ("{B_DEF_NAME_WITH_PREFIX} SNATCHED\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s move!"))\
    F(STRINGID_PKMNMADEITRAIN,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade it rain!"))\
    F(STRINGID_PKMNRAISEDSPEED,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nraised its SPEED!"))\
    F(STRINGID_PKMNPROTECTEDBY,                                        ("{B_DEF_NAME_WITH_PREFIX} was protected\nby {B_DEF_ABILITY}!"))\
    F(STRINGID_PKMNPREVENTSUSAGE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents {B_ATK_NAME_WITH_PREFIX}\lfrom using {B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNRESTOREDHPUSING,                                        ("{B_DEF_NAME_WITH_PREFIX} restored HP\nusing its {B_DEF_ABILITY}!"))\
    F(STRINGID_PKMNCHANGEDTYPEWITH,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nmade it the {B_BUFF1} type!"))\
    F(STRINGID_PKMNPREVENTSPARALYSISWITH,                                        ("{B_EFF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents paralysis!"))\
    F(STRINGID_PKMNIGNOREDADVANCESWITH,                                        ("{B_DEF_NAME_WITH_PREFIX}'s remained\n{B_DEF_ABILITY}!"))\
    F(STRINGID_PKMNPREVENTSPOISONINGWITH,                                        ("{B_EFF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents poisoning!"))\
    F(STRINGID_PKMNPREVENTSCONFUSIONWITH,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents confusion!"))\
    F(STRINGID_PKMNRAISEDFIREPOWERWITH,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nraised its FIRE power!"))\
    F(STRINGID_PKMNANCHORSITSELFWITH,                                        ("{B_DEF_NAME_WITH_PREFIX} anchors\nitself with {B_DEF_ABILITY}!"))\
    F(STRINGID_PKMNCUTSATTACKWITH,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncuts {B_DEF_NAME_WITH_PREFIX}'s ATTACK!"))\ 
    F(STRINGID_DARKTYPE_INTIMIDATE_RESIST,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nhas no affect on Dark Types!"))\
    F(STRINGID_PKMNPREVENTSSTATLOSSWITH,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nprevents stat loss!"))\
    F(STRINGID_PKMNHURTSWITHABILITY,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nhurt {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNTRACED,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} TRACED\n{B_BUFF1}'s {B_BUFF2}!"))\
    F(STRINGID_STATSHARPLY,                                        ("sharply "))\
    F(STRINGID_STATROSE,                                        ("rose!"))\
    F(STRINGID_STATHARSHLY,                                        ("harshly "))\
    F(STRINGID_STATFELL,                                        ("fell!"))\
    F(STRINGID_ATTACKERSSTATROSE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}"))\
    F(STRINGID_DEFENDERSSTATROSE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}"))\
    F(STRINGID_SCRIPTINGSTATROSE,                                      ("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}rose!"))\
    F(STRINGID_ATTACKERSSTATFELL,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}"))\
    F(STRINGID_DEFENDERSSTATFELL,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}"))\
    F(STRINGID_CRITICALHIT,                                        ("A critical hit!"))\
    F(STRINGID_ONEHITKO,                                        ("It's a one-hit KO!"))\
    F(STRINGID_123POOF,                                        ("{PAUSE 32}1, {PAUSE 15}2, and{PAUSE 15}… {PAUSE 15}… {PAUSE 15}… {PAUSE 15}{PLAY_SE SE_BALL_BOUNCE_1}Poof!\p"))\
    F(STRINGID_ANDELLIPSIS,                                        ("And…\p"))\
    F(STRINGID_NOTVERYEFFECTIVE,                                        ("It's not very effective…"))\
    F(STRINGID_SUPEREFFECTIVE,                                        ("It's super effective!"))\
    F(STRINGID_GOTAWAYSAFELY,                                        ("{PLAY_SE SE_FLEE}Got away safely!\p"))\
    F(STRINGID_WILDPKMNFLED,                                        ("{PLAY_SE SE_FLEE}Wild {B_BUFF1} fled!"))\
    F(STRINGID_NORUNNINGFROMTRAINERS,                                        ("No! There's no running\nfrom a TRAINER battle!\p"))\
    F(STRINGID_CANTESCAPE,                                        ("Can't escape!\p"))\
    F(STRINGID_DONTLEAVEBIRCH,                                        (""))\
    F(STRINGID_BUTNOTHINGHAPPENED,                                        ("…\nBut nothing happened!"))\
    F(STRINGID_BUTITFAILED,                                        ("But it failed!"))\
    F(STRINGID_ITHURTCONFUSION,                                        ("It hurt itself in its\nconfusion!"))\
    F(STRINGID_MIRRORMOVEFAILED,                                        ("The MIRROR MOVE failed!"))\
    F(STRINGID_STARTEDTORAIN,                                        ("It started to rain!"))\
    F(STRINGID_DOWNPOURSTARTED,                                        ("A downpour started!"))\
    F(STRINGID_RAINCONTINUES,                                        ("Rain continues to fall."))\
    F(STRINGID_DOWNPOURCONTINUES,                                        ("The downpour continues."))\
    F(STRINGID_RAINSTOPPED,                                        ("The rain stopped."))\
    F(STRINGID_SANDSTORMBREWED,                                        ("A sandstorm brewed!"))\
    F(STRINGID_SANDSTORMRAGES,                                        ("The sandstorm rages."))\
    F(STRINGID_SANDSTORMSUBSIDED,                                        ("The sandstorm subsided."))\
    F(STRINGID_SUNLIGHTGOTBRIGHT,                                        ("The sunlight got bright!"))\
    F(STRINGID_SUNLIGHTSTRONG,                                        ("The sunlight is strong."))\
    F(STRINGID_SUNLIGHTFADED,                                        ("The sunlight faded."))\
    F(STRINGID_STARTEDHAIL,                                        ("It started to hail!"))\
    F(STRINGID_HAILCONTINUES,                                        ("Hail continues to fall."))\
    F(STRINGID_HAILSTOPPED,                                        ("The hail stopped."))\
    F(STRINGID_FAILEDTOSPITUP,                                        ("But it failed to SPIT UP\na thing!"))\
    F(STRINGID_FAILEDTOSWALLOW,                                        ("But it failed to SWALLOW\na thing!"))\
    F(STRINGID_WINDBECAMEHEATWAVE,                                        ("The wind turned into a\nHEAT WAVE!"))\
    F(STRINGID_STATCHANGESGONE,                                        ("All stat changes were\neliminated!"))\
    F(STRINGID_COINSSCATTERED,                                        ("Coins scattered everywhere!"))\
    F(STRINGID_TOOWEAKFORSUBSTITUTE,                                        ("It was too weak to make\na SUBSTITUTE!"))\
    F(STRINGID_SHAREDPAIN,                                        ("The battlers shared\ntheir pain!"))\
    F(STRINGID_BELLCHIMED,                                        ("A bell chimed!"))\
    F(STRINGID_FAINTINTHREE,                                        ("All affected POKéMON will\nfaint in three turns!"))\
    F(STRINGID_NOPPLEFT,                                        ("There's no PP left for\nthis move!\p"))\
    F(STRINGID_BUTNOPPLEFT,                                        ("But there was no PP left\nfor the move!"))\
    F(STRINGID_PLAYERUSEDITEM,                                        ("{B_PLAYER_NAME} used\n{B_LAST_ITEM}!"))\
    F(STRINGID_OLDMANUSEDITEM,                                        ("The old man used\n{B_LAST_ITEM}!"))\
    F(STRINGID_TRAINERBLOCKEDBALL,                                        ("The TRAINER blocked the BALL!"))\
    F(STRINGID_DONTBEATHIEF,                                        ("Don't be a thief!"))\
    F(STRINGID_ITDODGEDBALL,                                        ("It dodged the thrown BALL!\nThis POKéMON can't be caught!{PAUSE 10}"))\
    F(STRINGID_YOUMISSEDPKMN,                                        ("You missed!\nThe POKéMON dodged the thrown BALL!{PAUSE 10}"))\
    F(STRINGID_PKMNBROKEFREE,                                        ("Oh, no!\nThe POKéMON broke free!"))\
    F(STRINGID_ITAPPEAREDCAUGHT,                                        ("Aww!\nIt appeared to be caught!"))\
    F(STRINGID_AARGHALMOSTHADIT,                                        ("Aargh!\nAlmost had it!"))\
    F(STRINGID_SHOOTSOCLOSE,                                        ("Shoot!\nIt was so close, too!"))\
    F(STRINGID_GOTCHAPKMNCAUGHT,                                        ("Gotcha!\n{B_DEF_NAME} was caught!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p"))\
    F(STRINGID_GOTCHAPKMNCAUGHT2,                                        ("Gotcha!\n{B_DEF_NAME} was caught!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}"))\
    F(STRINGID_GIVENICKNAMECAPTURED,                                        ("Give a nickname to the\ncaptured {B_OPPONENT_MON1_NAME}?"))\
    F(STRINGID_PKMNSENTTOPC,                                        ("{B_DEF_NAME} was sent to\n{B_PC_CREATOR_NAME} PC."))\
    F(STRINGID_PKMNDATAADDEDTODEX,                                        ("{B_DEF_NAME}'s data was\nadded to the POKéDEX.\p"))\
    F(STRINGID_ITISRAINING,                                        ("It is raining."))\
    F(STRINGID_SANDSTORMISRAGING,                                        ("A sandstorm is raging."))\
    F(STRINGID_CANTESCAPE2,                                        ("Can't escape!\p"))\
    F(STRINGID_PKMNIGNORESASLEEP,                                        ("{B_ATK_NAME_WITH_PREFIX} ignored\norders while asleep!"))\
    F(STRINGID_PKMNIGNOREDORDERS,                                        ("{B_ATK_NAME_WITH_PREFIX} ignored\norders!"))\
    F(STRINGID_PKMNBEGANTONAP,                                        ("{B_ATK_NAME_WITH_PREFIX} began to nap!"))\
    F(STRINGID_PKMNLOAFING,                                        ("{B_ATK_NAME_WITH_PREFIX} is\nloafing around!"))\
    F(STRINGID_PKMNWONTOBEY,                                        ("{B_ATK_NAME_WITH_PREFIX} won't\nobey!"))\
    F(STRINGID_PKMNTURNEDAWAY,                                        ("{B_ATK_NAME_WITH_PREFIX} turned away!"))\
    F(STRINGID_PKMNPRETENDNOTNOTICE,                                        ("{B_ATK_NAME_WITH_PREFIX} pretended\nnot to notice!"))\
    F(STRINGID_ENEMYABOUTTOSWITCHPKMN,                                        ("{B_TRAINER1_NAME_WITH_CLASS} is\nabout to send out\ltheir next POKéMON.\pWill {B_PLAYER_NAME} change\nPOKéMON?"))\
    F(STRINGID_THREWROCK,                                        ("{B_PLAYER_NAME} threw a ROCK\nat the {B_OPPONENT_MON1_NAME}!"))\
    F(STRINGID_THREWBAIT,                                        ("{B_PLAYER_NAME} threw some BAIT\nat the {B_OPPONENT_MON1_NAME}!"))\
    F(STRINGID_PKMNWATCHINGCAREFULLY,                                        ("{B_OPPONENT_MON1_NAME} is watching\ncarefully!"))\
    F(STRINGID_PKMNANGRY,                                        ("{B_OPPONENT_MON1_NAME} is angry!"))\
    F(STRINGID_PKMNEATING,                                        ("{B_OPPONENT_MON1_NAME} is eating!"))\
    F(STRINGID_DUMMY288,                                        (""))\
    F(STRINGID_DUMMY289,                                        (""))\
    F(STRINGID_OUTOFSAFARIBALLS,                                        ("{PLAY_SE SE_DING_DONG}ANNOUNCER: You're out of\nSAFARI BALLS! Game over!\p"))\
    F(STRINGID_PKMNSITEMCUREDPARALYSIS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ncured paralysis!"))\
    F(STRINGID_PKMNSITEMCUREDPOISON,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ncured poison!"))\
    F(STRINGID_PKMNSITEMHEALEDBURN,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nhealed its burn!"))\
    F(STRINGID_PKMNSITEMDEFROSTEDIT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ndefrosted it!"))\
    F(STRINGID_PKMNSITEMWOKEIT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nwoke it from its sleep!"))\
    F(STRINGID_PKMNSITEMSNAPPEDOUT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nsnapped it out of confusion!"))\
    F(STRINGID_PKMNSITEMCUREDPROBLEM,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ncured its {B_BUFF1} problem!"))\
    F(STRINGID_PKMNSITEMRESTOREDHEALTH,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored health!"))\
    F(STRINGID_PKMNSITEMRESTOREDPP,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored {B_BUFF1}'s PP!"))\
    F(STRINGID_PKMNSITEMRESTOREDSTATUS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored its status!"))\
    F(STRINGID_PKMNSITEMRESTOREDHPALITTLE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored its HP a little!"))\
    F(STRINGID_ITEMALLOWSONLYYMOVE,                                        ("{B_LAST_ITEM}'s effect allows only\n{B_CURRENT_MOVE} to be used!\p"))\
    F(STRINGID_PKMNHUNGONWITHX,                                        ("{B_DEF_NAME_WITH_PREFIX} hung on\nusing its {B_LAST_ITEM}!"))\
    F(STRINGID_EMPTYSTRING3,                                        (""))\
    F(STRINGID_PKMNSXPREVENTSBURNS,                                        ("{B_EFF_NAME_WITH_PREFIX}'s {B_EFF_ABILITY}\nprevents burns!"))\
    F(STRINGID_PKMNSXBLOCKSY,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nblocks {B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNSXRESTOREDHPALITTLE2,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nrestored its HP a little!"))\
    F(STRINGID_PKMNSXWHIPPEDUPSANDSTORM,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nwhipped up a sandstorm!"))\
    F(STRINGID_PKMNSXPREVENTSYLOSS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nprevents {B_BUFF1} loss!"))\
    F(STRINGID_PKMNSXINFATUATEDY,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\ninfatuated {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNSXMADEYINEFFECTIVE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nmade {B_CURRENT_MOVE} ineffective!"))\
    F(STRINGID_PKMNSXCUREDYPROBLEM,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncured its {B_BUFF1} problem!"))\
    F(STRINGID_ITSUCKEDLIQUIDOOZE,                                        ("It sucked up the\nLIQUID OOZE!"))\
    F(STRINGID_PKMNTRANSFORMED,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} transformed!"))\
    F(STRINGID_ELECTRICITYWEAKENED,                                        ("Electricity's power was\nweakened!"))\
    F(STRINGID_FIREWEAKENED,                                        ("Fire's power was\nweakened!"))\
    F(STRINGID_PKMNHIDUNDERWATER,                                        ("{B_ATK_NAME_WITH_PREFIX} hid\nunderwater!"))\
    F(STRINGID_PKMNSPRANGUP,                                        ("{B_ATK_NAME_WITH_PREFIX} sprang up!"))\
    F(STRINGID_HMMOVESCANTBEFORGOTTEN,                                        ("HM moves can't be\nforgotten now.\p"))\
    F(STRINGID_XFOUNDONEY,                                        ("{B_ATK_NAME_WITH_PREFIX} found\none {B_LAST_ITEM}!"))\
    F(STRINGID_PLAYERDEFEATEDTRAINER1,                                        ("Player defeated\n{B_TRAINER1_NAME_WITH_CLASS}!\p"))\
    F(STRINGID_SOOTHINGAROMA,                                        ("A soothing aroma wafted\nthrough the area!"))\
    F(STRINGID_ITEMSCANTBEUSEDNOW,                                        ("Items can't be used now.{PAUSE 34}"))\
    F(STRINGID_FORXCOMMAYZ,                                        ("For {B_SCR_ACTIVE_NAME_WITH_PREFIX},\n{B_LAST_ITEM} {B_BUFF1}"))\
    F(STRINGID_USINGXTHEYOFZN,                                        ("Using {B_LAST_ITEM}, the {B_BUFF1}\nof {B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_BUFF2}"))\
    F(STRINGID_PKMNUSEDXTOGETPUMPED,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} used\n{B_LAST_ITEM} to hustle!"))\
    F(STRINGID_PKMNSXMADEYUSELESS,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nmade {B_CURRENT_MOVE} useless!"))\
    F(STRINGID_PKMNTRAPPEDBYSANDTOMB,                                        ("{B_DEF_NAME_WITH_PREFIX} was trapped\nby SAND TOMB!"))\
    F(STRINGID_EMPTYSTRING4,                                        (""))\
    F(STRINGID_ABOOSTED,                                        (" a boosted"))\
    F(STRINGID_PKMNSXINTENSIFIEDSUN,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nintensified the sun's rays!"))\
    F(STRINGID_PKMNMAKESGROUNDMISS,                                        ("{B_DEF_NAME_WITH_PREFIX} can float!\nGROUND-based moves can't hit it!{PAUSE 8}"))\
    F(STRINGID_YOUTHROWABALLNOWRIGHT,                                        ("You throw a BALL now, right?\nI… I'll do my best!"))\
    F(STRINGID_PKMNSXTOOKATTACK,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\ntook the attack!"))\
    F(STRINGID_PKMNCHOSEXASDESTINY,                                        ("{B_ATK_NAME_WITH_PREFIX} chose\n{B_CURRENT_MOVE} as its destiny!"))\
    F(STRINGID_PKMNLOSTFOCUS,                                        ("{B_ATK_NAME_WITH_PREFIX} lost its\nfocus and couldn't move!"))\
    F(STRINGID_USENEXTPKMN,                                        ("Use next POKéMON?"))\
    F(STRINGID_PKMNFLEDUSINGITS,                                        ("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} fled\nusing its {B_LAST_ITEM}!\p"))\
    F(STRINGID_PKMNFLEDUSING,                                        ("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} fled\nusing {B_ATK_ABILITY}!\p"))\
    F(STRINGID_PKMNWASDRAGGEDOUT,                                        ("{B_DEF_NAME_WITH_PREFIX} was\ndragged out!\p"))\
    F(STRINGID_PREVENTEDFROMWORKING,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevented {B_SCR_ACTIVE_NAME_WITH_PREFIX}'s\l{B_BUFF1} from working!"))\
    F(STRINGID_PKMNSITEMNORMALIZEDSTATUS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nnormalized its status!"))\
    F(STRINGID_TRAINER1USEDITEM,                                        ("{B_TRAINER1_NAME_WITH_CLASS}\nused {B_LAST_ITEM}!"))\
    F(STRINGID_BOXISFULL,                                        ("The BOX is full!\nYou can't catch any more!\p"))\
    F(STRINGID_PKMNAVOIDEDATTACK,                                        ("{B_DEF_NAME_WITH_PREFIX} avoided\nthe attack!"))\
    F(STRINGID_PKMNSXMADEITINEFFECTIVE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade it ineffective!"))\
    F(STRINGID_PKMNSXPREVENTSFLINCHING,                                        ("{B_EFF_NAME_WITH_PREFIX}'s {B_EFF_ABILITY}\nprevents flinching!"))\
    F(STRINGID_PKMNALREADYHASBURN,                                        ("{B_DEF_NAME_WITH_PREFIX} already\nhas a burn."))\
    F(STRINGID_STATSWONTDECREASE2,                                        ("{B_DEF_NAME_WITH_PREFIX}'s stats won't\ngo any lower!"))\
    F(STRINGID_PKMNSXBLOCKSY2,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nblocks {B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNSXWOREOFF,                                        ("{B_ATK_PREFIX1}'s {B_BUFF1}\nwore off!"))\
    F(STRINGID_PKMNRAISEDDEFALITTLE,                                        ("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised DEFENSE a little!"))\
    F(STRINGID_PKMNRAISEDSPDEFALITTLE,                                        ("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised SP. DEF a little!"))\
    F(STRINGID_THEWALLSHATTERED,                                        ("The wall shattered!"))\
    F(STRINGID_PKMNSXPREVENTSYSZ,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nprevents {B_DEF_NAME_WITH_PREFIX}'s\l{B_DEF_ABILITY} from working!"))\
    F(STRINGID_ATTACKERCANTESCAPE,                                        ("{B_ATK_NAME_WITH_PREFIX} can't escape!"))\
    F(STRINGID_PKMNOBTAINEDX,                                        ("{B_ATK_NAME_WITH_PREFIX} obtained\n{B_BUFF1}."))\
    F(STRINGID_PKMNOBTAINEDX2,                                        ("{B_DEF_NAME_WITH_PREFIX} obtained\n{B_BUFF2}."))\
    F(STRINGID_PKMNOBTAINEDXYOBTAINEDZ,                                        ("{B_ATK_NAME_WITH_PREFIX} obtained\n{B_BUFF1}.\p{B_DEF_NAME_WITH_PREFIX} obtained\n{B_BUFF2}."))\
    F(STRINGID_BUTNOEFFECT,                                        ("But it had no effect!"))\
    F(STRINGID_PKMNSXHADNOEFFECTONY,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nhad no effect on {B_EFF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_OAKPLAYERWON,                                        ("OAK: Hm! Excellent!\pIf you win, you earn prize money,\nand your POKéMON will grow!\pBattle other TRAINERS and make\nyour POKéMON strong!\p"))\
    F(STRINGID_OAKPLAYERLOST,                                        ("OAK: Hm…\nHow disappointing…\pIf you win, you earn prize money,\nand your POKéMON grow.\pBut if you lose, {B_PLAYER_NAME}, you end\nup paying prize money…\pHowever, since you had no warning\nthis time, I'll pay for you.\pBut things won't be this way once\nyou step outside these doors.\pThat's why you must strengthen your\nPOKéMON by battling wild POKéMON.\p"))\
    F(STRINGID_PLAYERLOSTAGAINSTENEMYTRAINER,                                        ("{B_PLAYER_NAME} is out of\nusable POKéMON!\pPlayer lost against\n{B_TRAINER1_NAME_WITH_CLASS}!{PAUSE_UNTIL_PRESS}"))\ 
    F(STRINGID_PLAYERPAIDPRIZEMONEY,                                        ("{B_PLAYER_NAME} paid ¥{B_BUFF1} as the prize\nmoney…\p… … … …\p{B_PLAYER_NAME} whited out!{PAUSE_UNTIL_PRESS}"))\
    F(STRINGID_PKMNTRANSFERREDSOMEONESPC,                                        ("{STR_VAR_2} was transferred to\nSomeone's PC.\pIt was placed in\nBOX “{STR_VAR_1}.”"))\
    F(STRINGID_PKMNTRANSFERREDBILLSPC,                                        ("{STR_VAR_2} was transferred to\nBILL'S PC.\pIt was placed in\nBOX “{STR_VAR_1}.”"))\
    F(STRINGID_PKMNBOXSOMEONESPCFULL,                                        ("BOX “{STR_VAR_3}” on\nSomeone's PC was full.\p{STR_VAR_2} was transferred to\nBOX “{STR_VAR_1}.”"))\
    F(STRINGID_PKMNBOXBILLSPCFULL,                                        ("BOX “{STR_VAR_3}” on\nBILL'S PC was full.\p{STR_VAR_2} was transferred to\nBOX “{STR_VAR_1}.”"))\
    F(STRINGID_POKEDUDEUSED,                                        ("The POKé DUDE used\n{B_LAST_ITEM}!"))\
    F(STRINGID_POKEFLUTECATCHY,                                        ("{B_PLAYER_NAME} played the {B_LAST_ITEM}.\pNow, that's a catchy tune!"))\
    F(STRINGID_POKEFLUTE,                                        ("{B_PLAYER_NAME} played the\n{B_LAST_ITEM}."))\
    F(STRINGID_MONHEARINGFLUTEAWOKE,                                        ("The POKéMON hearing the FLUTE\nawoke!"))\
    F(STRINGID_PKMNSXCALLEDDOWNHAIL,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncalled down hail!"))\
    F(STRINGID_POKEMONBLOCKEDBALL,                                        ("The Wild {B_DEF_NAME}\nblocked the BALL!{PAUSE 10}"))\
    F(STRINGID_NEUTRALIZINGGASENTERS,                                        ("Neutralizing Gas filled the area!"))\
    F(STRINGID_NEUTRALIZINGGASOVER,                                        ("The effects of Neutralizing Gas\n wore off!"))\
    F(STRINGID_INFESTATION,                                        ("{B_DEF_NAME_WITH_PREFIX} has been afflicted\nwith an infestation!"))\
    F(STRINGID_ENDUREDSTURDY,                                        ("{B_DEF_NAME_WITH_PREFIX} ENDURED\nthe hit via {B_DEF_ABILITY}!"))\
    F(STRINGID_POWERHERB,                                        ("{B_ATK_NAME_WITH_PREFIX} became fully charged\ndue to its {B_LAST_ITEM}!"))\
    F(STRINGID_HURTBYITEM,                                        ("{B_ATK_NAME_WITH_PREFIX} was hurt\nby its {B_LAST_ITEM}!"))\
    F(STRINGID_PSNBYITEM,                                        ("{B_EFF_NAME_WITH_PREFIX} was badly \npoisoned by the {B_LAST_ITEM}!"))\
    F(STRINGID_BRNBYITEM,                                        ("{B_EFF_NAME_WITH_PREFIX} was burned\nby the {B_LAST_ITEM}!"))\
    F(STRINGID_DEFABILITYIN,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} activates!"))\
    F(STRINGID_GRAVITYINTENSIFIED,                                        ("GRAVITY intensified!"))\
    F(STRINGID_TARGETIDENTIFIED,                                        ("{B_DEF_NAME_WITH_PREFIX} was \nidentified!"))\
    F(STRINGID_TARGETWOKEUP,                                        ("{B_DEF_NAME_WITH_PREFIX} woke up!"))\
    F(STRINGID_PKMNSTOLEANDATEITEM,                                        ("{B_ATK_NAME_WITH_PREFIX} stole and\nate {B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!"))\
    F(STRINGID_TAILWINDBLEW,                                        ("The tailwind blew from\nbehind {B_ATK_TEAM2} team!"))\
    F(STRINGID_PKMNWENTBACK,                                        ("{B_ATK_NAME_WITH_PREFIX} went back\nto {B_ATK_TRAINER_CLASS}{B_ATK_TRAINER_NAME}"))\
    F(STRINGID_PKMNCANTUSEITEMSANYMORE,                                        ("{B_DEF_NAME_WITH_PREFIX} can't use\nitems anymore!"))\
    F(STRINGID_PKMNFLUNG,                                        ("{B_ATK_NAME_WITH_PREFIX} flung its\n{B_LAST_ITEM}!"))\
    F(STRINGID_PKMNPREVENTEDFROMHEALING,                                        ("{B_DEF_NAME_WITH_PREFIX} was prevented\nfrom healing!"))\
    F(STRINGID_PKMNSWITCHEDATKANDDEF,                                        ("{B_ATK_NAME_WITH_PREFIX} switched its\nAttack and Defense!"))\
    F(STRINGID_PKMNSABILITYSUPPRESSED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s ability\nwas suppressed!"))\
    F(STRINGID_SHIELDEDFROMCRITICALHITS,                                        ("The {B_CURRENT_MOVE} shielded {B_ATK_TEAM2}\nteam from critical hits!"))\
    F(STRINGID_SWITCHEDATKANDSPATK,                                        ("{B_ATK_NAME_WITH_PREFIX} switched all its\nchanges to its Attack and\pSp. Atk with the target!"))\
    F(STRINGID_SWITCHEDDEFANDSPDEF,                                        ("{B_ATK_NAME_WITH_PREFIX} switched all its\nchanges to its Defense and\pSp. Def with the target!"))\
    F(STRINGID_PKMNACQUIREDABILITY,                                        ("{B_DEF_NAME_WITH_PREFIX} acquired\n{B_DEF_ABILITY}!"))\
    F(STRINGID_POISONSPIKESSCATTERED,                                        ("Poison Spikes were scattered all\naround the opposing team's feet!"))\
    F(STRINGID_PKMNSWITCHEDSTATCHANGES,                                        ("{B_ATK_NAME_WITH_PREFIX} switched stat changes\nwith the target!"))\
    F(STRINGID_PKMNSURROUNDEDWITHVEILOFWATER,                                        ("{B_ATK_NAME_WITH_PREFIX} surrounded itself\nwith a veil of water!"))\
    F(STRINGID_PKMNLEVITATEDONELECTROMAGNETISM,                                        ("{B_ATK_NAME_WITH_PREFIX} levitated on\nelectromagnetism!"))\
    F(STRINGID_PKMNTWISTEDDIMENSIONS,                                        ("{B_ATK_NAME_WITH_PREFIX} twisted\nthe dimensions!"))\
    F(STRINGID_POINTEDSTONESFLOAT,                                        ("Pointed stones float in the air\naround {B_DEF_TEAM2} team!"))\
    F(STRINGID_CLOAKEDINMYSTICALMOONLIGHT,                                        ("It became cloaked in mystical\nmoonlight!"))\
    F(STRINGID_TRAPPEDBYSWIRLINGMAGMA,                                        ("{B_DEF_NAME_WITH_PREFIX} became\ntrapped by swirling magma!"))\
    F(STRINGID_VANISHEDINSTANTLY,                                        ("{B_ATK_NAME_WITH_PREFIX} vanished\ninstantly!"))\
    F(STRINGID_PROTECTEDTEAM,                                        ("{B_CURRENT_MOVE} protected\n{B_ATK_TEAM2} team!"))\
    F(STRINGID_SHAREDITSGUARD,                                        ("{B_ATK_NAME_WITH_PREFIX} shared its\nguard with the target!"))\
    F(STRINGID_SHAREDITSPOWER,                                        ("{B_ATK_NAME_WITH_PREFIX} shared its\npower with the target!"))\
    F(STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON,                                        ("It created a bizarre area in which\nthe Defense and Sp.Def stats are swapped!"))\
    F(STRINGID_BECAMENIMBLE,                                        ("{B_ATK_NAME_WITH_PREFIX} became nimble!"))\
    F(STRINGID_HURLEDINTOTHEAIR,                                        ("{B_DEF_NAME_WITH_PREFIX} was hurled\ninto the air!"))\
    F(STRINGID_HELDITEMSLOSEEFFECTS,                                        ("It created a bizarre area in which\nPokémon's held items lose their effects!"))\
    F(STRINGID_FELLSTRAIGHTDOWN,                                        ("{B_DEF_NAME_WITH_PREFIX} fell\nstraight down!"))\
    F(STRINGID_TRANSFORMEDINTOWATERTYPE,                                        ("{B_DEF_NAME_WITH_PREFIX} transformed\ninto the water type!"))\
    F(STRINGID_PKMNACQUIREDSIMPLE,                                        ("{B_DEF_NAME_WITH_PREFIX} acquired\nSimple!"))\
    F(STRINGID_EMPTYSTRING5,                                        (""))\
    F(STRINGID_KINDOFFER,                                        ("{B_DEF_NAME_WITH_PREFIX}\ntook the kind offer!"))\
    F(STRINGID_RESETSTARGETSSTATLEVELS,                                        ("{B_DEF_NAME_WITH_PREFIX}'s stat changes\nwere removed!"))\
    F(STRINGID_EMPTYSTRING6,                                        (""))\
    F(STRINGID_ALLYSWITCHPOSITION,                                        ("{B_ATK_NAME_WITH_PREFIX} and\n{B_SCR_ACTIVE_NAME_WITH_PREFIX} switched places!"))\
    F(STRINGID_RESTORETARGETSHEALTH,                                        ("{B_DEF_NAME_WITH_PREFIX}'s HP was restored!"))\
    F(STRINGID_TOOKPKMNINTOTHESKY,                                        ("{B_ATK_NAME_WITH_PREFIX} took\n{B_DEF_NAME_WITH_PREFIX} into the sky!"))\
    F(STRINGID_FREEDFROMSKYDROP,                                        ("{B_DEF_NAME_WITH_PREFIX} was freed\nfrom the Sky Drop!"))\
    F(STRINGID_POSTPONETARGETMOVE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s move\nwas postponed!"))\
    F(STRINGID_REFLECTTARGETSTYPE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s type\nchanged to match the {B_DEF_NAME_WITH_PREFIX}'s!"))\
    F(STRINGID_TRANSFERHELDITEM,                                        ("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM}\nfrom {B_ATK_NAME_WITH_PREFIX}"))\
    F(STRINGID_EMBARGOENDS,                                        ("{B_ATK_TEAM1} side can\nuse items again!"))\
    F(STRINGID_ELECTROMAGNETISM,                                        ("electromagnetism"))\
    F(STRINGID_BUFFERENDS,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\nwore off!"))\
    F(STRINGID_TELEKINESISENDS,                                        ("{B_ATK_NAME_WITH_PREFIX} was freed\nfrom the telekinesis!"))\
    F(STRINGID_TAILWINDENDS,                                        ("{B_ATK_TEAM1} team's tailwind\n petered out!"))\
    F(STRINGID_LUCKYCHANTENDS,                                        ("{B_ATK_TEAM1} team's Lucky Chant\n wore off!"))\
    F(STRINGID_TRICKROOMENDS,                                        ("The twisted dimensions returned to\nnormal!"))\
    F(STRINGID_WONDERROOMENDS,                                        ("Wonder Room wore off, and\nDefense and Sp. Def stats returned to normal!"))\
    F(STRINGID_MAGICROOMENDS,                                        ("Magic Room wore off, and\nheld items' effects returned to normal!"))\
    F(STRINGID_MUDSPORTENDS,                                        ("The effects of Mud Sport have faded."))\
    F(STRINGID_WATERSPORTENDS,                                        ("The effects of Water Sport have faded."))\
    F(STRINGID_GRAVITYENDS,                                        ("Gravity returned to normal!"))\
    F(STRINGID_AQUARINGHEAL,                                        ("Aqua Ring restored\n{B_ATK_NAME_WITH_PREFIX}'s HP!"))\
    F(STRINGID_AURORAVEILENDS,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nwore off!"))\
    F(STRINGID_ELECTRICTERRAINENDS,                                        ("The electricity disappeared\nfrom the battlefield."))\
    F(STRINGID_MISTYTERRAINENDS,                                        ("The mist disappeared\nfrom the battlefield."))\
    F(STRINGID_PSYCHICTERRAINENDS,                                        ("The weirdness disappeared\nfrom the battlefield."))\
    F(STRINGID_GRASSYTERRAINENDS,                                        ("The grass disappeared\nfrom the battlefield."))\
    F(STRINGID_TARGETABILITYSTATRAISE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nraised its {B_BUFF1}!"))\
    F(STRINGID_TARGETSSTATWASMAXEDOUT,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} maxed\nits {B_BUFF1}!"))\
    F(STRINGID_ATTACKERABILITYSTATRAISE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nraised its {B_BUFF1}!"))\
    F(STRINGID_POISONHEALHPUP,                                        ("The poison restored {B_ATK_NAME_WITH_PREFIX}'s\nHP a little!"))\
    F(STRINGID_BADDREAMSDMG,                                        ("{B_DEF_NAME_WITH_PREFIX} is tormented\nby {B_ATK_ABILITY}!"))\
    F(STRINGID_MOLDBREAKERENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} breaks the mold!"))\
    F(STRINGID_TERAVOLTENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating \na bursting aura!"))\
    F(STRINGID_TURBOBLAZEENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating\na blazing aura!"))\
    F(STRINGID_SLOWSTARTENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is\nin a weakened state!{PAUSE 9}"))\
    F(STRINGID_SLOWSTARTEND,                                        ("{B_ATK_NAME_WITH_PREFIX}'s power has\nreturned to its zenith!{PAUSE 9}"))\
    F(STRINGID_SOLARPOWERHPDROP,                                        ("The {B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\ntook its toll!"))\
    F(STRINGID_AFTERMATHDMG,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} tried to take\n{B_ATK_NAME_WITH_PREFIX} out with them!"))\
    F(STRINGID_ANTICIPATIONACTIVATES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} sensed {B_BUFF1}\nand shuddered in anticipation!"))\
    F(STRINGID_FOREWARNACTIVATES,                                        ("{B_SCR_ACTIVE_ABILITY} {B_BUFF3} {B_SCR_ACTIVE_NAME_WITH_PREFIX}\n{B_BUFF2} {B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}!"))\
    F(STRINGID_ICEBODYHPGAIN,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nhealed it a little bit!"))\
    F(STRINGID_CRYOSTORMHAIL,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncalled down hail!"))\
    F(STRINGID_FRISKACTIVATES,                                        ("{B_ATK_NAME_WITH_PREFIX} frisked {B_DEF_NAME_WITH_PREFIX} and\nfound its {B_LAST_ITEM}!"))\
    F(STRINGID_UNNERVEENTERS,                                        ("The opposing team is too nervous\nto eat Berries!"))\
    F(STRINGID_HARVESTBERRY,                                        ("{B_ATK_NAME_WITH_PREFIX} harvested\nits {B_LAST_ITEM}!"))\
    F(STRINGID_LASTABILITYRAISEDSTAT,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} raised its Attack!"))\
    F(STRINGID_MAGICBOUNCEACTIVATES,                                        ("The {B_DEF_NAME_WITH_PREFIX} bounced the\n{B_ATK_NAME_WITH_PREFIX} back!"))\
    F(STRINGID_PROTEANTYPECHANGE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} transformed\nit into the {B_BUFF1} type!"))\
    F(STRINGID_SYMBIOSISITEMPASS,                                        ("{B_ATK_NAME_WITH_PREFIX} passed its {B_LAST_ITEM}\nto {B_SCR_ACTIVE_NAME_WITH_PREFIX} through {B_ATK_ABILITY}!"))\
    F(STRINGID_STEALTHROCKDMG,                                        ("Pointed stones dug into\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}!"))\
    F(STRINGID_TOXICSPIKESABSORBED,                                        ("The poison spikes disappeared\nfrom around {B_ATK_TEAM2} team's feet!"))\
    F(STRINGID_TOXICSPIKESPOISONED,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} was poisoned!"))\
    F(STRINGID_STICKYWEBSWITCHIN,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} was\ncaught in a Sticky Web!"))\
    F(STRINGID_HEALINGWISHCAMETRUE,                                        ("The healing wish came true\nfor {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_HEALINGWISHHEALED,                                        ("{B_ATK_NAME_WITH_PREFIX} regained health!"))\
    F(STRINGID_LUNARDANCECAMETRUE,                                        ("{B_ATK_NAME_WITH_PREFIX} became cloaked\nin mystical moonlight!"))\
    F(STRINGID_CUSEDBODYDISABLED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} was disabled\nby {B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!"))\
    F(STRINGID_ATTACKERACQUIREDABILITY,                                        ("{B_ATK_NAME_WITH_PREFIX} acquired {B_LAST_ABILITY}!"))\
    F(STRINGID_TARGETABILITYSTATLOWER,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nlowered its {B_BUFF1}!"))\
    F(STRINGID_TARGETSTATWONTGOHIGHER,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwon't go higher!"))\
    F(STRINGID_PKMNMOVEBOUNCEDABILITY,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} was refelcted\nby {B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}{PAUSE 26}!"))\
    F(STRINGID_IMPOSTERTRANSFORM,                                        ("{B_ATK_NAME_WITH_PREFIX} transformed into\na {B_DEF_NAME_WITH_PREFIX} using {B_BUFF2}!"))\
    F(STRINGID_ASSAULTVESTDOESNTALLOW,                                        ("The effects of the {B_LAST_ITEM} prevent status\nmoves from being used!\p"))\
    F(STRINGID_GRAVITYPREVENTSUSAGE,                                        ("{B_ATK_NAME_WITH_PREFIX} can't use {B_CURRENT_MOVE}\nbecause of gravity!\p"))\
    F(STRINGID_HEALBLOCKPREVENTSUSAGE,                                        ("{B_ATK_NAME_WITH_PREFIX} was\nprevented from healing!\p"))\
    F(STRINGID_NOTDONEYET,                                        ("Not Done Yet"))\
    F(STRINGID_STICKYWEBUSED,                                        ("A sticky web spreads out on the\nground around {B_DEF_TEAM2} team!"))\
    F(STRINGID_QUASHSUCCESS,                                        ("The opposing {B_ATK_NAME_WITH_PREFIX}'s move was postponed!"))\
    F(STRINGID_PKMNBLEWAWAYTOXICSPIKES,                                        ("{B_ATK_NAME_WITH_PREFIX} blew away\nTOXIC SPIKES!"))\
    F(STRINGID_PKMNBLEWAWAYSTICKYWEB,                                        ("{B_ATK_NAME_WITH_PREFIX} blew away\nSTICKY WEB!"))\
    F(STRINGID_PKMNBLEWAWAYSTEALTHROCK,                                        ("{B_ATK_NAME_WITH_PREFIX} blew away\nSTEALTH ROCK!"))\
    F(STRINGID_IONDELUGEON,                                        ("A deluge of ions showers\nthe battlefield!"))\
    F(STRINGID_TOPSYTURVYSWITCHEDSTATS,                                        ("{B_DEF_NAME_WITH_PREFIX}'s stat changes were\nall reversed!"))\
    F(STRINGID_TERRAINBECOMESMISTY,                                        ("Mist swirled about\nthe battlefield!"))\
    F(STRINGID_TERRAINBECOMESGRASSY,                                        ("Grass grew to cover\nthe battlefield!"))\
    F(STRINGID_TERRAINBECOMESELECTRIC,                                        ("An electric current runs across\nthe battlefield!"))\
    F(STRINGID_TERRAINBECOMESPSYCHIC,                                        ("The battlefield got weird!"))\
    F(STRINGID_TARGETELECTRIFIED,                                        ("The {B_DEF_NAME_WITH_PREFIX}'s moves\nhave been electrified!"))\
    F(STRINGID_MEGAEVOREACTING,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ITEM} is \nreacting to {B_ATK_TRAINER_NAME}'s Mega Ring!"))\
    F(STRINGID_MEGAEVOEVOLVED,                                        ("{B_ATK_NAME_WITH_PREFIX} has Mega\nEvolved into Mega {B_BUFF1}!"))\    
    F(STRINGID_DRASTICALLY,                                        ("drastically "))\
    F(STRINGID_SEVERELY,                                        ("severely "))\
    F(STRINGID_NOEFFECTONTARGET,                                        ("It had no effect\non {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_BURSTINGFLAMESHIT,                                        ("The bursting flames\nhit {B_SCR_ACTIVE_NAME_WITH_PREFIX}!"))\
    F(STRINGID_BESTOWITEMGIVING,                                        ("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM}\nfrom {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_THIRDTYPEADDED,                                        ("{B_BUFF1} type was added to\n{B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_FELLFORFEINT,                                        ("{B_DEF_NAME_WITH_PREFIX} fell for\nthe feint!"))\
    F(STRINGID_POKEMONCANNOTUSEMOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} cannot\nuse {B_CURRENT_MOVE}!"))\
    F(STRINGID_COVEREDINPOWDER,                                        ("{B_DEF_NAME_WITH_PREFIX} is covered in powder!"))\
    F(STRINGID_POWDEREXPLODES,                                        ("When the flame touched the powder\non the Pokémon, it exploded!"))\
    F(STRINGID_BELCHCANTSELECT,                                        ("Belch cannot be used!\p"))\
    F(STRINGID_SPECTRALTHIEFSTEAL,                                        ("{B_ATK_NAME_WITH_PREFIX} stole the target's\nboosted stats!"))\
    F(STRINGID_GRAVITYGROUNDING,                                        ("{B_DEF_NAME_WITH_PREFIX} can't stay airborne\nbecause of gravity!"))\
    F(STRINGID_MISTYTERRAINPREVENTS,                                        ("{B_DEF_NAME_WITH_PREFIX} surrounds itself\nwith a protective mist!"))\
    F(STRINGID_GRASSYTERRAINHEALS,                                        ("{B_ATK_NAME_WITH_PREFIX} is healed\nby the grassy terrain!"))\
    F(STRINGID_ELECTRICTERRAINPREVENTS,                                        ("{B_DEF_NAME_WITH_PREFIX} surrounds itself\nwith electrified terrain!"))\
    F(STRINGID_PSYCHICTERRAINPREVENTS,                                        ("{B_DEF_NAME_WITH_PREFIX} surrounds itself\nwith psychic terrain!"))\
    F(STRINGID_SAFETYGOGGLESPROTECTED,                                        ("{B_DEF_NAME_WITH_PREFIX} is not affected\nthanks to its {B_LAST_ITEM}!"))\
    F(STRINGID_FLOWERVEILPROTECTED,                                        ("{B_DEF_NAME_WITH_PREFIX} surrounded itself\nwith a veil of petals!"))\
    F(STRINGID_SWEETVEILPROTECTED,                                        ("{B_DEF_NAME_WITH_PREFIX} surrounded itself\nwith a veil of sweetness!"))\
    F(STRINGID_AROMAVEILPROTECTED,                                        ("{B_DEF_NAME_WITH_PREFIX} is protected\nby an aromatic veil!"))\
    F(STRINGID_CELEBRATEMESSAGE,                                        ("Congratulations, {B_PLAYER_NAME}!"))\
    F(STRINGID_USEDINSTRUCTEDMOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} used the move\ninstructed by {B_BUFF1}!"))\
    F(STRINGID_THROATCHOPENDS,                                        ("{B_ATK_NAME_WITH_PREFIX} can\nuse sound-based moves again!"))\
    F(STRINGID_PKMNCANTUSEMOVETHROATCHOP,                                        ("{B_ATK_NAME_WITH_PREFIX} can't use\n{B_CURRENT_MOVE} due to Throat Chop!\p"))\    
    F(STRINGID_LASERFOCUS,                                        ("{B_ATK_NAME_WITH_PREFIX}\nconcentrated intensely!"))\
    F(STRINGID_GEMACTIVATES,                                        ("{B_LAST_ITEM} strengthened\n{B_ATK_NAME_WITH_PREFIX}'s power!"))\
    F(STRINGID_BERRYDMGREDUCES,                                        ("{B_LAST_ITEM} weakened the damage\nto {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_TARGETATEITEM,                                        ("{B_DEF_NAME_WITH_PREFIX} ate its {B_LAST_ITEM}!"))\
    F(STRINGID_AIRBALLOONFLOAT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} floats in the air\nwith its {B_LAST_ITEM}!"))\
    F(STRINGID_AIRBALLOONPOP,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM} popped!"))\
    F(STRINGID_INCINERATEBURN,                                        ("{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nwas burnt up!"))\
    F(STRINGID_BUGBITE,                                        ("{B_ATK_NAME_WITH_PREFIX} stole and ate\n{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!"))\
    F(STRINGID_ILLUSIONWOREOFF,                                        ("{B_DEF_NAME_WITH_PREFIX}'s Illusion wore off!"))\
    F(STRINGID_ATTACKERCUREDTARGETSTATUS,                                        ("{B_ATK_NAME_WITH_PREFIX} cured\n{B_DEF_NAME_WITH_PREFIX}'s problem!"))\
    F(STRINGID_ATTACKERLOSTTYPE,                                        ("{B_ATK_NAME_WITH_PREFIX} lost it's {B_BUFF3} type!"))\
    F(STRINGID_HEALERCURE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ABILITY}\ncured {B_SCR_ACTIVE_NAME_WITH_PREFIX}'s problem!"))\
    F(STRINGID_SCRIPTINGABILITYSTATRAISE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nraised its {B_BUFF1}!"))\
    F(STRINGID_RECEIVERABILITYTAKEOVER,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nwas taken over!"))\
    F(STRINGID_PKNMABSORBINGPOWER,                                        ("{B_ATK_NAME_WITH_PREFIX} is absorbing power!"))\
    F(STRINGID_NOONEWILLBEABLETORUNAWAY,                                        ("No one will be able to run away\nduring the next turn!"))\
    F(STRINGID_DESTINYKNOTACTIVATES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} fell in love\nfrom the {B_LAST_ITEM}!"))\
    F(STRINGID_CLOAKEDINAFREEZINGLIGHT,                                        ("{B_ATK_NAME_WITH_PREFIX} became cloaked\nin a freezing light!"))\
    F(STRINGID_STATWASNOTLOWERED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwas not lowered!"))\
    F(STRINGID_FERVENTWISHREACHED,                                        ("{B_ATK_TRAINER_NAME}'s fervent wish\nhas reached {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_AIRLOCKACTIVATES,                                        ("The effects of weather\ndisappeared."))\
    F(STRINGID_PRESSUREENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is exerting its\npressure!"))\
    F(STRINGID_DARKAURAENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating\na dark aura!"))\
    F(STRINGID_FAIRYAURAENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating\na fairy aura!"))\
    F(STRINGID_AURABREAKENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} reversed all\nother POKéMON's auras!"))\
    F(STRINGID_COMATOSEENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is drowsing!"))\
    F(STRINGID_SCREENCLEANERENTERS,                                        ("All screens on the field were\ncleansed!"))\
    F(STRINGID_FETCHEDPOKEBALL,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} found\na {B_LAST_ITEM}!"))\
    F(STRINGID_BATTLERABILITYRAISEDSTAT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nraised its {B_BUFF1}!"))\
    F(STRINGID_ASANDSTORMKICKEDUP,                                        ("A sandstorm kicked up!"))\
    F(STRINGID_ATTACKERWILLPERISHIN3TURNS,                                        ("{B_ATK_NAME_WITH_PREFIX} will perish\nin three turns!"))\
    F(STRINGID_ABILITYRAISEDSTATDRASTICALLY,                                        ("{B_DEF_ABILITY} raised {B_DEF_NAME_WITH_PREFIX}'s\n{B_BUFF1} drastically!"))\  
    F(STRINGID_AURAFLAREDTOLIFE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s aura flared to life!"))\
    F(STRINGID_ASONEENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} has two Abilities!"))\
    F(STRINGID_CURIOUSMEDICINEENTERS,                                        ("{B_EFF_NAME_WITH_PREFIX}'s\nstat changes were reset!"))\
    F(STRINGID_CANACTFASTERTHANKSTO,                                        ("{B_ATK_NAME_WITH_PREFIX} moved faster,\nthanks to {B_BUFF1}!"))\
    F(STRINGID_MICLEBERRYACTIVATES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} boosted the accuracy of its\nnext move using {B_LAST_ITEM}!"))\
    F(STRINGID_PKMNSHOOKOFFTHETAUNT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} shook off\nthe taunt!"))\
    F(STRINGID_PKMNGOTOVERITSINFATUATION,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} got over\nits infatuation!"))\
    F(STRINGID_ITEMCANNOTBEREMOVED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s item cannot be removed!"))\
    F(STRINGID_STICKYBARBTRANSFER,                                        ("The {B_LAST_ITEM} attached itself to\n{B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNBURNHEALED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s\nburn was healed."))\
    F(STRINGID_REDCARDACTIVATE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} held up its {B_LAST_ITEM}\nagainst {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_EJECTBUTTONACTIVATE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is switched\nout with the {B_LAST_ITEM}!"))\
    F(STRINGID_ATKGOTOVERINFATUATION,                                        ("{B_ATK_NAME_WITH_PREFIX} got over\nits infatuation!"))\
    F(STRINGID_TORMENTEDNOMORE,                                        ("{B_ATK_NAME_WITH_PREFIX} is\ntormented no more!"))\
    F(STRINGID_HEALBLOCKEDNOMORE,                                        ("{B_ATK_NAME_WITH_PREFIX} is cured of\nits heal block!"))\
    F(STRINGID_ATTACKERBECAMEFULLYCHARGED,                                        ("{B_ATK_NAME_WITH_PREFIX} became fully charged\ndue to its bond with its trainer!\p"))\
    F(STRINGID_ATTACKERBECAMEASHSPECIES,                                        ("{B_ATK_NAME_WITH_PREFIX} became Ash-{B_BUFF1}!\p"))\
    F(STRINGID_EXTREMELYHARSHSUNLIGHT,                                        ("The sunlight turned\nextremely harsh!"))\
    F(STRINGID_EXTREMESUNLIGHTFADED,                                        ("The extreme sunlight faded.{PAUSE 32}"))\
    F(STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,                                        ("The Water-type attack evaporated\nin the harsh sunlight!"))\
    F(STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED,                                        ("The extremely harsh sunlight\nwas not lessened at all!"))\
    F(STRINGID_HEAVYRAIN,                                        ("A heavy rain began to fall!"))\
    F(STRINGID_HEAVYRAINLIFTED,                                        ("The heavy rain has lifted!{PAUSE 32}"))\
    F(STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,                                        ("The Fire-type attack fizzled out\nin the heavy rain!"))\
    F(STRINGID_NORELIEFROMHEAVYRAIN,                                        ("There is no relief from\nthis heavy rain!"))\
    F(STRINGID_MYSTERIOUSAIRCURRENT,                                        ("A mysterious air current is\nprotecting Flying-type Pokémon!"))\
    F(STRINGID_STRONGWINDSDISSIPATED,                                        ("The mysterious strong winds\nhave dissipated!{PAUSE 32}"))\
    F(STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,                                        ("The mysterious air current\nblows on regardless!"))\
    F(STRINGID_ATTACKWEAKENEDBYSTRONGWINDS,                                        ("The mysterious strong winds\nweakened the attack!"))\
    F(STRINGID_STUFFCHEEKSCANTSELECT,                                        ("Stuff Cheeks cannot be\nselected without a Berry!\p"))\
    F(STRINGID_PKMNREVERTEDTOPRIMAL,                                        ("{B_ATK_NAME_WITH_PREFIX} reverted to its primal form!"))\
    F(STRINGID_BUTPOKEMONCANTUSETHEMOVE,                                        ("But {B_ATK_NAME_WITH_PREFIX} can't\nuse the move!"))\
    F(STRINGID_BUTHOOPACANTUSEIT,                                        ("But Hoopa can't use it\nthe way it is now!"))\
    F(STRINGID_BROKETHROUGHPROTECTION,                                        ("It broke through the\n{B_DEF_NAME_WITH_PREFIX}'s protection!"))\
    F(STRINGID_ABILITYALLOWSONLYMOVE,                                        ("{B_ATK_ABILITY} allows the\nuse of only {B_CURRENT_MOVE}!\p"))\
    F(STRINGID_SWAPPEDABILITIES,                                        ("{B_DEF_NAME_WITH_PREFIX} swapped Abilities\nwith its target!"))\
    F(STRINGID_PASTELVEILPROTECTED,                                        ("{B_DEF_NAME_WITH_PREFIX} is protected\nby a pastel veil!"))\
    F(STRINGID_PASTELVEILENTERS,                                        ("{B_DEF_NAME_WITH_PREFIX} was cured\nof its poisoning!"))\
    F(STRINGID_BATTLERTYPECHANGEDTO,                                        ("{B_BUFF1}'s type\nchanged to {B_BUFF2}!"))\
    F(STRINGID_BOTHCANNOLONGERESCAPE,                                        ("Neither Pokémon can run away!"))\
    F(STRINGID_CANTESCAPEDUETOUSEDMOVE,                                        ("{B_ATK_NAME_WITH_PREFIX} can no longer escape\nbecause it used {B_CURRENT_MOVE}!"))\
    F(STRINGID_PKMNBECAMEWEAKERTOFIRE,                                        ("{B_DEF_NAME_WITH_PREFIX} became\nweaker to fire!"))\
    F(STRINGID_ABOUTTOUSEPOLTERGEIST,                                        ("{B_DEF_NAME_WITH_PREFIX} is about\nto be attacked by its {B_BUFF1}!"))\
    F(STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE,                                        ("{B_DEF_NAME_WITH_PREFIX} can no longer escape\nbecause of {B_CURRENT_MOVE}!"))\
    F(STRINGID_TARGETTOOHEAVY,                                        ("But the target was too heavy!"))\
    F(STRINGID_PKMNTOOKTARGETHIGH,                                        ("{B_ATK_NAME_WITH_PREFIX} took {B_DEF_NAME_WITH_PREFIX}\ninto the air!"))\        
    F(STRINGID_CUPIDSARROWSTRUCK,                                        ("{B_DEF_NAME_WITH_PREFIX} fell in love\nat first sight!"))\
    F(STRINGID_PKMNALREADYFROZEN,                                        ("{B_DEF_NAME_WITH_PREFIX} is already\nfrozen."))\
    F(STRINGID_SNAPTRAP,                                        ("{B_DEF_NAME_WITH_PREFIX} was ensnared\nby {B_ATK_NAME_WITH_PREFIX}'s trap!"))\
    F(STRINGID_PKMNSTOPPEDROOSTING,                                        ("{B_ATK_NAME_WITH_PREFIX} stopped roosting\nand took to the air!{PAUSE 15}"))\
    F(STRINGID_CONFIRMFORGETMOVE,                                        ("{PAUSE 32}Are you sure you want to\nforget {B_BUFF2}?"))\
    F(STRINGID_TERRAINBECOMESFIRE,                                        ("The battlefield was set aflame!"))\
    F(STRINGID_TERRAINBECOMESWATER,                                        ("Water flooded The battlefield!"))\
    F(STRINGID_TERRAINBECOMESDEEPWATER,                                        ("The battlefield is covered by\ndeep water!"))\
    F(STRINGID_CRASHEDTOTHEGROUND,                                        ("{B_DEF_NAME_WITH_PREFIX} crashed\nto the ground!"))\
    F(STRINGID_DEFEATISTACTIVATED,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} lost the will to fight\nand is ready to run!{PAUSE 22}"))\
    F(STRINGID_PKMNHURTBYFROSTBITE,                                        ("{B_ATK_NAME_WITH_PREFIX} is hurt\nby frostbite!"))\
    F(STRINGID_IRONWILL_ATKCANCEL,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} made\n{B_SCR_ACTIVE_NAME_WITH_PREFIX} too afraid to attack!"))\
    F(STRINGID_STEALTHROCKABROSBED,                                        ("Pointed stones disappeared\nfrom around {B_ATK_TEAM2}'s team!"))\
    F(STRINGID_PICKUP_ITEM,                                        ("{B_ATK_NAME_WITH_PREFIX} picked up\na {B_BUFF1}!{PAUSE 12}"))\
    F(STRINGID_TIGER_MOM_ACTIVATES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} pressured\n{B_DEF_NAME_WITH_PREFIX} cutting its DEFENSE!"))\
    F(STRINGID_DEFROST_POKEMON,                                        ("{B_ATK_TEAM1} {B_SCR_ACTIVE_NAME_WITH_PREFIX} was\ndefrosted!"))\
    F(STRINGID_CORRUPTIONENTERS,                                        ("{B_ATK_NAME_WITH_PREFIX} spread {B_ATK_ABILITY}!\n{B_DEF_TEAM1} side can't heal!\p"))\
    F(STRINGID_BANDITENTERS,                                        ("The {B_ATK_ABILITY} is on the scene!\n{B_DEF_TEAM1} side can't use items!{PAUSE 32}"))\
    F(STRINGID_ANTICIPATE_EXPLOSION,                                        ("an explosive move"))\
    F(STRINGID_ANTICIPATE_OHKO,                                        ("a one-hit KO move"))\
    F(STRINGID_ANTICIPATE_DEFAULT,                                        ("a dangerous move"))\
    F(STRINGID_SPITE_BADLUCK,                                        (" had bad luck!"))\
    F(STRINGID_SPITE_TOTAL_LOSS,                                        ("'s luck ran out!"))\
    F(STRINGID_PKMNSPOISONWORSENED,                                        ("{B_EFF_NAME_WITH_PREFIX}'s poisoning got worse!\nIt's badly poisoned!"))\
    F(STRINGID_STENCHENTERS,                                        ("A foul stench is in the air!"))\
    F(STRINGID_STENCHENDS,                                        ("The foul odor has cleared!"))\
    F(STRINGID_WELLRESTED,                                        ("{B_ATK_NAME_WITH_PREFIX} is\nwell rested!"))\
    F(STRINGID_PKMNHURTSWITH2,                                        ("{B_ATK_NAME_WITH_PREFIX} was hurt by\n{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}!"))\
    F(STRINGID_PKMNSABILITYPREVENTSABILITY,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nprevents {B_DEF_NAME_WITH_PREFIX}'s\l{B_DEF_ABILITY} from working!"))\
    F(STRINGID_STICKYHOLDABSORBEDITEM,                                        ("{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM} was absorbed\nby {B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!"))\
    F(STRINGID_METEORBEAMCHARGING,                                        ("{B_ATK_NAME_WITH_PREFIX} is overflowing\nwith space energy!"))\
    F(STRINGID_HEATUPBEAK,                                        ("{B_ATK_NAME_WITH_PREFIX} started\nheating up its beak!"))\
    F(STRINGID_EMPATHIC_CURSE_ACTIVATES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} suffered\nthe {B_DEF_ABILITY}!"))\
    F(STRINGID_ATTACKER_STURDY,                                        ("{B_ATK_NAME_WITH_PREFIX} hung on\nvia {B_ATK_ABILITY}!"))\
    F(STRINGID_TARGETSXWHIPPEDUPSANDSTORM,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nwhipped up a sandstorm!"))\
    F(STRINGID_ATTACKER_ABILITYHURTS_TARGET,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\nhurt {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNINFESTED,                                        ("{B_ATK_NAME_WITH_PREFIX} is infested!"))\
    F(STRINGID_PKMNPANICKED,                                        ("{B_ATK_NAME_WITH_PREFIX} panicked\nand used a random move!"))\
    F(STRINGID_ABILITYNULLIFYTYPEDAMAGE,                                        ("{B_DEF_NAME_WITH_PREFIX} nullifies {B_BUFF1}\nmoves with {B_DEF_ABILITY}!"))\
    F(STRINGID_CAUGHTMONDROPPEDITEM,                                        ("{B_DEF_NAME} dropped a {B_BUFF3}!\p"))\
    F(STRINGID_MONROOSTING,                                        ("{B_ATK_NAME_WITH_PREFIX} is resting\non the ground."))\
    F(STRINGID_ATK_RAGEBUILDING,                                        ("{B_ATK_NAME_WITH_PREFIX}'s RAGE\nis building!"))\
    F(STRINGID_ATK_RAGEABATED,                                        ("{B_ATK_NAME_WITH_PREFIX}'s RAGE\nabated!{PAUSE 15}"))\
    F(STRINGID_BIND_NO_PP,                                        ("{B_BUFF1} ran out PP!"))\ 
    F(STRINGID_FEMME_FATALE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nresisted the infatuation."))\
    F(STRINGID_ABILITY_LOSTRESOLVE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} made\n{B_ATK_NAME_WITH_PREFIX} lose its resolve!"))\
    F(STRINGID_AURA_OF_LIGHT_AWOKE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ABILITY}\nawoke {B_SCR_ACTIVE_NAME_WITH_PREFIX}!"))\
    F(STRINGID_PKMNMOVESEALEDNOMORE,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} is\nno longer sealed!"))\
    F(STRINGID_PKMNMOVESEALED,                                        ("{B_DEF_NAME_WITH_PREFIX} has lost the memory\nof how to use {B_BUFF1}!"))\
    F(STRINGID_ATEBERRY,                                        ("{B_ATK_NAME_WITH_PREFIX} ate its {B_BUFF1}!"))\
    F(STRINGID_PHOENIX_CLEANSE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nhealed itself and\lcleansed hazards from the field!{PAUSE 97}"))\  
    F(STRINGID_PLAYER_FOREWARN,                                        ("to the"))\
    F(STRINGID_ENEMY_FOREAWRN,                                        ("to"))\ 
    F(STRINGID_PLAYER_ALERT,                                        ("alerted"))\
    F(SRINGID_ENEMY_ALERT,                                        ("alerted the"))\
    F(STRINGID_ANTICIPATE_STRONG_MOVE,                                        ("a strong move"))\
    F(STRINGID_FORECAST_BLIZZARD,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\na chilling Blizzard!\p"))\
    F(STRINGID_FORECAST_DUST_STORM,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\na harsh Dust Storm!\p"))\
    F(STRINGID_FORECAST_HEATWAVE,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\na blazing Heatwave!\p"))\
    F(STRINGID_FORECAST_TORRENTIAL_RAIN,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\nTorrential Rain!\p"))\
    F(STRINGID_FORECAST_SANDSTORM,                                        ("The Forecast came true!\nA sandstorm brewed!\p"))\
    F(STRINGID_FORECAST_HAIL,                                        ("The Forecast came true!\nIt started to hail!\p"))\
    F(STRINGID_FORECAST_RAIN,                                        ("The Forecast came true!\nIt started to rain!\p"))\
    F(STRINGID_FORECAST_SUNNY,                                        ("The Forecast came true!\nThe sunlight got bright!\p"))\
    F(STRINGID_FORECAST_PREDICTION,                                         ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\n{B_BUFF1} and {B_BUFF2}!\p"))\
    F(STRINGID_RAIN,                                        ("rain"))\ 
    F(STRINGID_SUN,                                        ("sun"))\ 
    F(STRINGID_SAND,                                        ("sand"))\ 
    F(STRINGID_HAIL,                                        ("hail"))\ 
    F(STRINGID_STATWENTBACKDOWN,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} went back down!"))\
    F(STRINGID_CELEBRATE,                                        ("{B_ATK_NAME_WITH_PREFIX} began to dance strangely!"))\
    F(STRINGID_ANTICIPATE_SOME_MOVE,                                        ("something"))\
    F(STRINGID_JUDGMENT,                                        ("{B_DEF_NAME} faced {STR_VAR_2} Judgment!{PAUSE 15}"))\
    F(STRINGID_GROUND_NULLIFY,                                        ("GROUND Types can't be blinded\nby Earth attacks!{PAUSE 5}"))\
    F(STRINGID_NOE_FLIGHT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is flying under the radar!"))\
    F(STRINGID_WONDER_GUARD_ENTERS,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is wreathed in\nan otherworldly veil!{PAUSE 36}"))\
    F(STRINGID_WONDER_GUARD_ENDS,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nhas dissipated!{PAUSE 36}"))\
    F(STRINGID_DEF_RAGEABATED,                                        ("{B_DEF_NAME_WITH_PREFIX}'s RAGE\nabated!{PAUSE 15}"))\
    F(STRINGID_IMMUTABLEWIND_ENTERS,                                        ("A strange cold wind blows!"))\
    F(STRINGID_IMMUTABLEWIND_ENDS,                                        ("The strange wind\nfinally subsided!"))\
    F(STRINGID_ITEMTOBAG,                                        ("Item(s) added to the bag.{PAUSE 47}"))\
    F(STRINGID_DAMP_PREVENTS_AFTERMATH,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents {B_SCR_ACTIVE_NAME_WITH_PREFIX}\lfrom using {B_LAST_ABILITY}!"))\
    F(STRINGID_CUPIDSARROWSTRUCK_BOTH,                                        ("{B_SCR_ACTIVE_ABILITY} struck both targets!"))\
    F(STRINGID_ATK_CUTECHARM,                                        ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\ninfatuated {B_DEF_NAME_WITH_PREFIX}!"))\
    F(STRINGID_INVERSIONTRANSFORM,                                        ("{B_ATK_NAME_WITH_PREFIX} transformed into\na {B_BUFF1} using {B_BUFF2}!"))\
    F(STRINGID_BATTLERABILITYSTAT_INCREASE_ENDS,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} increase from\n{B_ATK_ABILITY} came to an end!"))\
    F(STRINGID_SWITCH_LOCK_ENDS,                                        ("{B_ATK_NAME_WITH_PREFIX} is no longer bound!"))\
    F(STRINGID_BEINGHITCHARGEDPKMNWITHPOWER,                                        ("Being hit by {B_CURRENT_MOVE}\ncharged {B_DEF_NAME_WITH_PREFIX} with power!"))\
    F(STRINGID_REFLECT_INTIMIDATE,                                        ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} sent\nthe effect back to {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_CHANGE_ABILITY_TO,                                        ("{B_DEF_NAME_WITH_PREFIX}'s abiity changed\nto {B_BUFF1}!"))\
    F(STRINGID_HEAT_TRANCE_HPUP,                                        ("The burn restored {B_ATK_NAME_WITH_PREFIX}'s\nHP a little!"))\
    F(STIRNGID_SPIKESABSORBED,                                        ("The pointed spikes around {B_ATK_TEAM2}'s team\nsunk into the ground!"))\
    F(STRINGID_CONSUMED_HAZARD,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} consumed the {STR_VAR_2}\nthanks to {B_SCR_ACTIVE_ABILITY}!"))\
    F(STRINGID_PKMNBLEWAWAYSHARPSTEEL,                                        ("{B_ATK_NAME_WITH_PREFIX} blew away\nSTEEL SURGE!"))\
    F(STRINGID_SHARPSTEELFLOATS,                                        ("Floating steel spears\nsurround {B_DEF_TEAM2}'s Pokémon!"))\
    F(STRINGID_SHARPSTEEL_ABSORBED,                                        ("The steel spears disappeared\nfrom around {B_ATK_TEAM2}'s team!"))\
    F(STRINGID_SHARPSTEELDMG,                                        ("The sharp steel bit into {B_SCR_ACTIVE_NAME_WITH_PREFIX}!"))\
    F(STRINGID_RAGINGBULL_BREAKSTHROUGH,                                        ("{B_ATK_NAME_WITH_PREFIX} broke through the foe's defenses!"))\
    F(STRINGID_SUPERSWEETAROMAWAFTS,                                        ("A supersweet aroma is wafting from\nthe syrup covering {B_ATK_NAME_WITH_PREFIX}!"))\
    F(STRINGID_FORCEDTOSURFACE,                                        ("{B_DEF_NAME_WITH_PREFIX} was forced\nto surface!{PAUSE 36}"))\
    F(STRINGID_PKMNINSNAPTRAP,                                        ("{B_DEF_NAME_WITH_PREFIX} got trapped by\na snap trap!"))\
    F(STRINGID_THUNDERCAGETRAPPED,                                        ("{B_DEF_NAME_WITH_PREFIX} was caught in\na shocking trap!"))\
    F(STRINGID_TAKECAUGHTMONFROMPC,                                        ("Take Caught Mon From PC?"))\
    F(STRINGID_MOONLIGHT_SHINING_BRIGHT,                                        ("The Moon's light shown brightly!"))\
    F(STRINGID_MOONLIGHT_SHINES,                                        ("Moonlight shines down."))\
    F(STRINGID_MOONLIGHTFADED,                                        ("The Moon's rays faded from view.{PAUSE 36}"))\
    F(STRINGID_STARTEDSNOW,                                        ("It started to snow!"))\
    F(STRINGID_PKMNSXINTENSIFIEDMOONLIGHT,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nintensified the moon's rays!"))\
    F(STRINGID_ACIDRAIN_FALLS,                                        ("A toxic rain began to fall!"))\
    F(STRINGID_HURTBYRAIN,                                        ("{B_ATK_NAME_WITH_PREFIX} is seared\nby ACID RAIN!"))\
    F(STRINGID_TARGETISGETTINGSERIOUS,                                        ("{B_DEF_NAME_WITH_PREFIX} is getting serious now!"))\
    F(STRINGID_TARGETCHANGEDMODE,                                        ("{B_DEF_NAME_WITH_PREFIX} entered Showdown Mode!\p"))\
    /*For flame wheel*/F(STRINGID_BATTLER_ON_A_ROLL,                                        ("{B_ATK_NAME_WITH_PREFIX} is on a roll!"))\
    F(STRINGID_PKMNDROPPEDTEMP,                                        ("{B_ATK_NAME_WITH_PREFIX} dropped the temperature!"))\
    F(STRINGID_PKMNSWARMED,                                        ("{B_DEF_NAME_WITH_PREFIX} was trapped\nin a swirling Swarm!"))\
    F(STRINGID_PKMNCAMETOITSSENSES,                                        ("{B_SCR_ACTIVE_NAME_WITH_PREFIX} came to its senses!"))\
    F(STRINGID_PKMNRETURNEDTOAIR,                                        ("{B_ATK_NAME_WITH_PREFIX} returned to the air!"))\
/*EE*/    F(STRINGID_TWOENEMIESDEFEATED,                                         ("You defeated {B_TRAINER1_NAME_WITH_CLASS} and {B_TRAINER2_NAME_WITH_CLASS}!\p"))\
    F(STRINGID_TRAINER2LOSETEXT,                                         ("{B_TRAINER2_LOSE_TEXT}"))\
    F(STRINGID_PKMNINCAPABLEOFPOWER,                                         ("{B_ATK_NAME_WITH_PREFIX} appears incapable of using its power!"))\
    F(STRINGID_GLINTAPPEARSINEYE,                                         ("A glint appears in {B_SCR_NAME_WITH_PREFIX2}'s eyes!"))\
    F(STRINGID_PKMNGETTINGINTOPOSITION,                                         ("{B_SCR_NAME_WITH_PREFIX} is getting into position!"))\
    F(STRINGID_PKMNBEGANGROWLINGDEEPLY,                                         ("{B_SCR_NAME_WITH_PREFIX} began growling deeply!"))\
    F(STRINGID_PKMNEAGERFORMORE,                                         ("{B_SCR_NAME_WITH_PREFIX} is eager for more!"))\
    F(STRINGID_DEFEATEDOPPONENTBYREFEREE,                                         ("{B_PLAYER_MON1_NAME} defeated the opponent {B_OPPONENT_MON1_NAME} in a REFEREE's decision!"))\
    F(STRINGID_LOSTTOOPPONENTBYREFEREE,                                         ("{B_PLAYER_MON1_NAME} lost to the opponent {B_OPPONENT_MON1_NAME} in a REFEREE's decision!"))\
    F(STRINGID_TIEDOPPONENTBYREFEREE,                                         ("{B_PLAYER_MON1_NAME} tied the opponent {B_OPPONENT_MON1_NAME} in a REFEREE's decision!"))\
    F(STRINGID_QUESTIONFORFEITMATCH,                                         ("Would you like to forfeit the match and quit now?"))\
    F(STRINGID_FORFEITEDMATCH,                                         ("The match was forfeited."))\
    F(STRINGID_TRAINER1WINTEXT,                                         ("{B_TRAINER1_WIN_TEXT}"))\
    F(STRINGID_TRAINER2WINTEXT,                                         ("{B_TRAINER2_WIN_TEXT}"))\
    F(STRINGID_ENDUREDSTURDY,                                         ("{B_DEF_NAME_WITH_PREFIX} endured the hit using {B_DEF_ABILITY}!"))\
    F(STRINGID_POWERHERB,                                         ("{B_ATK_NAME_WITH_PREFIX} became fully charged due to its {B_LAST_ITEM}!"))\
    F(STRINGID_HURTBYITEM,                                         ("{B_ATK_NAME_WITH_PREFIX} was hurt by the {B_LAST_ITEM}!"))\
    F(STRINGID_PSNBYITEM,                                         ("{B_EFF_NAME_WITH_PREFIX} was badly poisoned by the {B_LAST_ITEM}!"))\
    F(STRINGID_BRNBYITEM,                                         ("{B_EFF_NAME_WITH_PREFIX} was burned by the {B_LAST_ITEM}!"))\
    F(STRINGID_DEFABILITYIN,                                         ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} activates!"))\
    F(STRINGID_GRAVITYINTENSIFIED,                                         ("Gravity intensified!"))\
    F(STRINGID_TARGETIDENTIFIED,                                         ("{B_DEF_NAME_WITH_PREFIX} was identified!"))\
    F(STRINGID_TARGETWOKEUP,                                         ("{B_DEF_NAME_WITH_PREFIX} woke up!"))\
    F(STRINGID_PKMNSTOLEANDATEITEM,                                         ("{B_ATK_NAME_WITH_PREFIX} stole and ate its target's {B_LAST_ITEM}!"))\
    F(STRINGID_TAILWINDBLEW,                                         ("The Tailwind blew from behind {B_ATK_TEAM2} team!"))\
    F(STRINGID_PKMNWENTBACK,                                         ("{B_ATK_NAME_WITH_PREFIX} went back to {B_ATK_TRAINER_NAME}!"))\
    F(STRINGID_PKMNCANTUSEITEMSANYMORE,                                         ("{B_DEF_NAME_WITH_PREFIX} can't use items anymore!"))\
    F(STRINGID_PKMNFLUNG,                                         ("{B_ATK_NAME_WITH_PREFIX} flung its {B_LAST_ITEM}!"))\
    F(STRINGID_PKMNPREVENTEDFROMHEALING,                                         ("{B_DEF_NAME_WITH_PREFIX} was prevented from healing!"))\
    F(STRINGID_PKMNSWITCHEDATKANDDEF,                                         ("{B_ATK_NAME_WITH_PREFIX} switched its Attack and Defense!"))\
    F(STRINGID_PKMNSABILITYSUPPRESSED,                                         ("{B_DEF_NAME_WITH_PREFIX}'s Ability was suppressed!"))\
    F(STRINGID_SHIELDEDFROMCRITICALHITS,                                         ("Lucky Chant shielded {B_ATK_TEAM2} team from critical hits!"))\
    F(STRINGID_SWITCHEDATKANDSPATK,                                         ("{B_ATK_NAME_WITH_PREFIX} switched all changes to its Attack and Sp. Atk\pwith its target!"))\
    F(STRINGID_SWITCHEDDEFANDSPDEF,                                         ("{B_ATK_NAME_WITH_PREFIX} switched all changes to its Defense and Sp. Def\pwith its target!"))\
    F(STRINGID_PKMNACQUIREDABILITY,                                         ("{B_DEF_NAME_WITH_PREFIX} acquired {B_DEF_ABILITY}!"))\
    F(STRINGID_POISONSPIKESSCATTERED,                                         ("Poison spikes were scattered on the ground all around {B_DEF_TEAM2} team!"))\
    F(STRINGID_PKMNSWITCHEDSTATCHANGES,                                         ("{B_ATK_NAME_WITH_PREFIX} switched stat changes with its target!"))\
    F(STRINGID_PKMNSURROUNDEDWITHVEILOFWATER,                                         ("{B_ATK_NAME_WITH_PREFIX} surrounded itself with a veil of water!"))\
    F(STRINGID_PKMNLEVITATEDONELECTROMAGNETISM,                                         ("{B_ATK_NAME_WITH_PREFIX} levitated with electromagnetism!"))\
    F(STRINGID_PKMNTWISTEDDIMENSIONS,                                         ("{B_ATK_NAME_WITH_PREFIX} twisted the dimensions!"))\
    F(STRINGID_POINTEDSTONESFLOAT,                                         ("Pointed stones float in the air around {B_DEF_TEAM2} team!"))\
    F(STRINGID_CLOAKEDINMYSTICALMOONLIGHT,                                         ("{B_ATK_NAME_WITH_PREFIX} became cloaked in mystical moonlight!"))\
    F(STRINGID_TRAPPEDBYSWIRLINGMAGMA,                                         ("{B_DEF_NAME_WITH_PREFIX} became trapped by swirling magma!"))\
    F(STRINGID_VANISHEDINSTANTLY,                                         ("{B_ATK_NAME_WITH_PREFIX} vanished instantly!"))\
    F(STRINGID_PROTECTEDTEAM,                                         ("{B_CURRENT_MOVE} protected {B_ATK_TEAM2} team!"))\
    F(STRINGID_SHAREDITSGUARD,                                         ("{B_ATK_NAME_WITH_PREFIX} shared its guard with the target!"))\
    F(STRINGID_SHAREDITSPOWER,                                         ("{B_ATK_NAME_WITH_PREFIX} shared its power with the target!"))\
    F(STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON,                                         ("It created a bizarre area in which Defense and Sp. Def stats are swapped!"))\
    F(STRINGID_BECAMENIMBLE,                                         ("{B_ATK_NAME_WITH_PREFIX} became nimble!"))\
    F(STRINGID_HURLEDINTOTHEAIR,                                         ("{B_DEF_NAME_WITH_PREFIX} was hurled into the air!"))\
    F(STRINGID_HELDITEMSLOSEEFFECTS,                                         ("It created a bizarre area in which Pokémon's held items lose their effects!"))\
    F(STRINGID_FELLSTRAIGHTDOWN,                                         ("{B_DEF_NAME_WITH_PREFIX} fell straight down!"))\
    F(STRINGID_TARGETCHANGEDTYPE,                                         ("{B_DEF_NAME_WITH_PREFIX} transformed into the {B_BUFF1} type!"))\
/*not used*/    F(STRINGID_PKMNACQUIREDSIMPLE,                                         ("{B_DEF_NAME_WITH_PREFIX} acquired Simple!"))\
    F(STRINGID_KINDOFFER,                                         ("{B_DEF_NAME_WITH_PREFIX} took the kind offer!"))\
    F(STRINGID_RESETSTARGETSSTATLEVELS,                                         ("{B_DEF_NAME_WITH_PREFIX}'s stat changes were removed!"))\
    F(STRINGID_ALLYSWITCHPOSITION,                                         ("{B_ATK_NAME_WITH_PREFIX} and {B_SCR_NAME_WITH_PREFIX2} switched places!"))\
    F(STRINGID_RESTORETARGETSHEALTH,                                         ("{B_DEF_NAME_WITH_PREFIX}'s HP was restored!"))\
    F(STRINGID_TOOKPKMNINTOTHESKY,                                         ("{B_ATK_NAME_WITH_PREFIX} took {B_DEF_NAME_WITH_PREFIX2} into the sky!"))\
    F(STRINGID_FREEDFROMSKYDROP,                                         ("{B_DEF_NAME_WITH_PREFIX} was freed from the Sky Drop!"))\
    F(STRINGID_POSTPONETARGETMOVE,                                         ("{B_DEF_NAME_WITH_PREFIX}'s move was postponed!"))\
    F(STRINGID_REFLECTTARGETSTYPE,                                         ("{B_ATK_NAME_WITH_PREFIX} became the same type as {B_DEF_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_TRANSFERHELDITEM,                                         ("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM} from {B_ATK_NAME_WITH_PREFIX2}"))\
    F(STRINGID_EMBARGOENDS,                                         ("{B_ATK_NAME_WITH_PREFIX} can use items again!"))\
    F(STRINGID_ELECTROMAGNETISM,                                         ("electromagnetism"))\
    F(STRINGID_BUFFERENDS,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} wore off!"))\
    F(STRINGID_TELEKINESISENDS,                                         ("{B_ATK_NAME_WITH_PREFIX} was freed from the telekinesis!"))\
    F(STRINGID_TAILWINDENDS,                                         ("{B_ATK_TEAM1} team's Tailwind petered out!"))\
    F(STRINGID_LUCKYCHANTENDS,                                         ("{B_ATK_TEAM1} team's Lucky Chant wore off!"))\
    F(STRINGID_TRICKROOMENDS,                                         ("The twisted dimensions returned to normal!"))\
    F(STRINGID_WONDERROOMENDS,                                         ("Wonder Room wore off, and Defense and Sp. Def stats returned to normal!"))\
    F(STRINGID_MAGICROOMENDS,                                         ("Magic Room wore off, and held items' effects returned to normal!"))\
    F(STRINGID_MUDSPORTENDS,                                         ("The effects of Mud Sport have faded."))\
    F(STRINGID_WATERSPORTENDS,                                         ("The effects of Water Sport have faded."))\
    F(STRINGID_GRAVITYENDS,                                         ("Gravity returned to normal!"))\
    F(STRINGID_AQUARINGHEAL,                                         ("A veil of water restored {B_ATK_NAME_WITH_PREFIX2}'s HP!"))\
    F(STRINGID_ELECTRICTERRAINENDS,                                         ("The electricity disappeared from the battlefield."))\
    F(STRINGID_MISTYTERRAINENDS,                                         ("The mist disappeared from the battlefield."))\
    F(STRINGID_PSYCHICTERRAINENDS,                                         ("The weirdness disappeared from the battlefield!"))\
    F(STRINGID_GRASSYTERRAINENDS,                                         ("The grass disappeared from the battlefield."))\
    F(STRINGID_TARGETABILITYSTATRAISE,                                         ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"))\
    F(STRINGID_TARGETSSTATWASMAXEDOUT,                                         ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} maxed its {B_BUFF1}!"))\
    F(STRINGID_ATTACKERABILITYSTATRAISE,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"))\
/*check if used*/    F(STRINGID_POISONHEALHPUP,                                         ("The poisoning healed {B_ATK_NAME_WITH_PREFIX2} a little bit!"))\
    F(STRINGID_BADDREAMSDMG,                                         ("{B_DEF_NAME_WITH_PREFIX} is tormented!"))\
    F(STRINGID_MOLDBREAKERENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} breaks the mold!"))\
    F(STRINGID_TERAVOLTENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is radiating a bursting aura!"))\
    F(STRINGID_TURBOBLAZEENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is radiating a blazing aura!"))\
    F(STRINGID_SLOWSTARTENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is slow to get going!"))\
    F(STRINGID_SLOWSTARTEND,                                         ("{B_ATK_NAME_WITH_PREFIX} finally got its act together!"))\
/*check if used*/    F(STRINGID_SOLARPOWERHPDROP,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} takes its toll!"))\
    F(STRINGID_AFTERMATHDMG,                                         ("{B_ATK_NAME_WITH_PREFIX} was hurt!"))\
    F(STRINGID_ANTICIPATIONACTIVATES,                                         ("{B_SCR_NAME_WITH_PREFIX} shuddered!"))\
    F(STRINGID_FOREWARNACTIVATES,                                         ("{B_SCR_ABILITY} alerted {B_SCR_NAME_WITH_PREFIX2} to {B_EFF_NAME_WITH_PREFIX2}'s {B_BUFF1}!"))\
/*check if used*/    F(STRINGID_ICEBODYHPGAIN,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} healed it a little bit!"))\
    F(STRINGID_SNOWWARNINGHAIL,                                         ("It started to hail!"))\
    F(STRINGID_FRISKACTIVATES,                                         ("{B_ATK_NAME_WITH_PREFIX} frisked {B_DEF_NAME_WITH_PREFIX2} and found its {B_LAST_ITEM}!"))\
    F(STRINGID_UNNERVEENTERS,                                         ("{B_EFF_TEAM1} team is too nervous to eat Berries!"))\
    F(STRINGID_HARVESTBERRY,                                         ("{B_ATK_NAME_WITH_PREFIX} harvested its {B_LAST_ITEM}!"))\
    F(STRINGID_MAGICBOUNCEACTIVATES,                                         ("{B_DEF_NAME_WITH_PREFIX} bounced the {B_ATK_NAME_WITH_PREFIX2} back!"))\
    F(STRINGID_PROTEANTYPECHANGE,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} transformed it into the {B_BUFF1} type!"))\
    F(STRINGID_SYMBIOSISITEMPASS,                                         ("{B_SCR_NAME_WITH_PREFIX} passed its {B_LAST_ITEM} to {B_EFF_NAME_WITH_PREFIX2} through {B_LAST_ABILITY}!"))\
    F(STRINGID_STEALTHROCKDMG,                                         ("Pointed stones dug into {B_SCR_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_TOXICSPIKESABSORBED,                                         ("The poison spikes disappeared from the ground around {B_EFF_TEAM2} team!"))\
    F(STRINGID_TOXICSPIKESPOISONED,                                         ("{B_SCR_NAME_WITH_PREFIX} was poisoned!"))\
    F(STRINGID_TOXICSPIKESBADLYPOISONED,                                         ("{B_SCR_NAME_WITH_PREFIX} was badly poisoned!"))\
    F(STRINGID_STICKYWEBSWITCHIN,                                         ("{B_SCR_NAME_WITH_PREFIX} was caught in a sticky web!"))\
    F(STRINGID_HEALINGWISHCAMETRUE,                                         ("The healing wish came true for {B_SCR_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_HEALINGWISHHEALED,                                         ("{B_SCR_NAME_WITH_PREFIX} regained health!"))\
    F(STRINGID_LUNARDANCECAMETRUE,                                         ("{B_SCR_NAME_WITH_PREFIX} became cloaked in mystical moonlight!"))\
    F(STRINGID_CURSEDBODYDISABLED,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} was disabled by {B_DEF_NAME_WITH_PREFIX2}'s {B_DEF_ABILITY}!"))\
    F(STRINGID_ATTACKERACQUIREDABILITY,                                         ("{B_ATK_NAME_WITH_PREFIX} acquired {B_ATK_ABILITY}!"))\
    F(STRINGID_TARGETABILITYSTATLOWER,                                         ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} {B_BUFF2}lowered its {B_BUFF1}!"))\
    F(STRINGID_TARGETSTATWONTGOHIGHER,                                         ("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} won't go any higher!"))\
    F(STRINGID_PKMNMOVEBOUNCEDABILITY,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} was bounced back by {B_DEF_NAME_WITH_PREFIX2}'s {B_DEF_ABILITY}!"))\
    F(STRINGID_IMPOSTERTRANSFORM,                                         ("{B_ATK_NAME_WITH_PREFIX} transformed into {B_DEF_NAME_WITH_PREFIX2} using {B_LAST_ABILITY}!"))\
    F(STRINGID_ASSAULTVESTDOESNTALLOW,                                         ("The effects of the {B_LAST_ITEM} prevent status moves from being used!\p"))\
    F(STRINGID_GRAVITYPREVENTSUSAGE,                                         ("{B_ATK_NAME_WITH_PREFIX} can't use {B_CURRENT_MOVE} because of gravity!\p"))\
    F(STRINGID_HEALBLOCKPREVENTSUSAGE,                                         ("{B_ATK_NAME_WITH_PREFIX} was prevented from healing!\p"))\
    F(STRINGID_NOTDONEYET,                                         ("This move effect is not done yet!\p"))\
    F(STRINGID_STICKYWEBUSED,                                         ("A sticky web has been laid out on the ground around {B_DEF_TEAM2} team!"))\
    F(STRINGID_QUASHSUCCESS,                                         ("{B_DEF_NAME_WITH_PREFIX}'s move was postponed!"))\
    F(STRINGID_PKMNBLEWAWAYTOXICSPIKES,                                         ("{B_ATK_NAME_WITH_PREFIX} blew away Toxic Spikes!"))\
    F(STRINGID_PKMNBLEWAWAYSTICKYWEB,                                         ("{B_ATK_NAME_WITH_PREFIX} blew away Sticky Web!"))\
    F(STRINGID_PKMNBLEWAWAYSTEALTHROCK,                                         ("{B_ATK_NAME_WITH_PREFIX} blew away Stealth Rock!"))\
    F(STRINGID_IONDELUGEON,                                         ("A deluge of ions showers the battlefield!"))\
    F(STRINGID_TOPSYTURVYSWITCHEDSTATS,                                         ("All stat changes on {B_DEF_NAME_WITH_PREFIX2} were inverted!"))\
    F(STRINGID_TERRAINBECOMESMISTY,                                         ("Mist swirled around the battlefield!"))\
    F(STRINGID_TERRAINBECOMESGRASSY,                                         ("Grass grew to cover the battlefield!"))\
    F(STRINGID_TERRAINBECOMESELECTRIC,                                         ("An electric current ran across the battlefield!"))\
    F(STRINGID_TERRAINBECOMESPSYCHIC,                                         ("The battlefield got weird!"))\
    F(STRINGID_TARGETELECTRIFIED,                                         ("{B_DEF_NAME_WITH_PREFIX}'s moves have been electrified!"))\
/*not added*/    F(STRINGID_MEGAEVOREACTING,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ITEM} is reacting to {B_ATK_TRAINER_NAME}'s Mega Ring!"))\
    F(STRINGID_MEGAEVOEVOLVED,                                         ("{B_ATK_NAME_WITH_PREFIX} has Mega Evolved into Mega {B_BUFF1}!"))\
    F(STRINGID_DRASTICALLY,                                         ("drastically "))\
    F(STRINGID_SEVERELY,                                         ("severely "))\
    F(STRINGID_INFESTATION,                                         ("{B_DEF_NAME_WITH_PREFIX} has been afflicted with an infestation by {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_NOEFFECTONTARGET,                                         ("It won't have any effect on {B_DEF_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_BURSTINGFLAMESHIT,                                         ("The bursting flames hit {B_SCR_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_BESTOWITEMGIVING,                                         ("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM} from {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_THIRDTYPEADDED,                                         ("{B_BUFF1} type was added to {B_DEF_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_FELLFORFEINT,                                         ("{B_DEF_NAME_WITH_PREFIX} fell for the feint!"))\
    F(STRINGID_POKEMONCANNOTUSEMOVE,                                         ("{B_ATK_NAME_WITH_PREFIX} cannot use {B_CURRENT_MOVE}!"))\
    F(STRINGID_COVEREDINPOWDER,                                         ("{B_DEF_NAME_WITH_PREFIX} is covered in powder!"))\
    F(STRINGID_POWDEREXPLODES,                                         ("When the flame touched the powder on the Pokémon, it exploded!"))\
    F(STRINGID_BELCHCANTSELECT,                                         ("{B_ATK_NAME_WITH_PREFIX} hasn't eaten any held Berries, so it can't possibly belch!\p"))\
    F(STRINGID_SPECTRALTHIEFSTEAL,                                         ("{B_ATK_NAME_WITH_PREFIX} stole the target's boosted stats!"))\
    F(STRINGID_GRAVITYGROUNDING,                                         ("{B_DEF_NAME_WITH_PREFIX} fell from the sky due to the gravity!"))\
    F(STRINGID_MISTYTERRAINPREVENTS,                                         ("{B_DEF_NAME_WITH_PREFIX} surrounds itself with a protective mist!"))\
    F(STRINGID_GRASSYTERRAINHEALS,                                         ("{B_ATK_NAME_WITH_PREFIX} is healed by the grassy terrain!"))\
    F(STRINGID_ELECTRICTERRAINPREVENTS,                                         ("{B_DEF_NAME_WITH_PREFIX} surrounds itself with electrified terrain!"))\
    F(STRINGID_PSYCHICTERRAINPREVENTS,                                         ("{B_SCR_NAME_WITH_PREFIX} is protected by the Psychic Terrain!"))\
    F(STRINGID_SAFETYGOGGLESPROTECTED,                                         ("{B_SCR_NAME_WITH_PREFIX} is not affected thanks to its {B_LAST_ITEM}!"))\
    F(STRINGID_FLOWERVEILPROTECTED,                                         ("{B_DEF_NAME_WITH_PREFIX} surrounded itself with a veil of petals!"))\
    F(STRINGID_SWEETVEILPROTECTED,                                         ("{B_DEF_NAME_WITH_PREFIX} can't fall asleep due to a veil of sweetness!"))\
    F(STRINGID_AROMAVEILPROTECTED,                                         ("{B_DEF_NAME_WITH_PREFIX} is protected by an aromatic veil!"))\
    F(STRINGID_CELEBRATEMESSAGE,                                         ("Congratulations, {B_PLAYER_NAME}!"))\
    F(STRINGID_USEDINSTRUCTEDMOVE,                                         ("{B_DEF_NAME_WITH_PREFIX} followed {B_ATK_NAME_WITH_PREFIX2}'s instructions!"))\
    F(STRINGID_THROATCHOPENDS,                                         ("{B_ATK_NAME_WITH_PREFIX} can use sound-based moves again!"))\
    F(STRINGID_PKMNCANTUSEMOVETHROATCHOP,                                         ("The effects of Throat Chop prevent {B_ATK_NAME_WITH_PREFIX2} from using certain moves!\p"))\
    F(STRINGID_LASERFOCUS,                                         ("{B_ATK_NAME_WITH_PREFIX} concentrated intensely!"))\
    F(STRINGID_GEMACTIVATES,                                         ("The {B_LAST_ITEM} strengthened {B_ATK_NAME_WITH_PREFIX2}'s power!"))\
    F(STRINGID_BERRYDMGREDUCES,                                         ("The {B_LAST_ITEM} weakened the damage to {B_SCR_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_AIRBALLOONFLOAT,                                         ("{B_SCR_NAME_WITH_PREFIX} floats in the air with its Air Balloon!"))\
    F(STRINGID_AIRBALLOONPOP,                                         ("{B_DEF_NAME_WITH_PREFIX}'s Air Balloon popped!"))\
    F(STRINGID_INCINERATEBURN,                                         ("{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM} was burnt up!"))\
    F(STRINGID_BUGBITE,                                         ("{B_ATK_NAME_WITH_PREFIX} stole and ate its target's {B_LAST_ITEM}!"))\
    F(STRINGID_ILLUSIONWOREOFF,                                         ("{B_SCR_NAME_WITH_PREFIX}'s illusion wore off!"))\
    F(STRINGID_ATTACKERCUREDTARGETSTATUS,                                         ("{B_ATK_NAME_WITH_PREFIX} cured {B_DEF_NAME_WITH_PREFIX2}'s problem!"))\
    F(STRINGID_ATTACKERLOSTFIRETYPE,                                         ("{B_ATK_NAME_WITH_PREFIX} burned itself out!"))\
    F(STRINGID_HEALERCURE,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ABILITY} cured {B_SCR_NAME_WITH_PREFIX2}'s problem!"))\
    F(STRINGID_SCRIPTINGABILITYSTATRAISE,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"))\
    F(STRINGID_RECEIVERABILITYTAKEOVER,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} was taken over!"))\
    F(STRINGID_PKNMABSORBINGPOWER,                                         ("{B_ATK_NAME_WITH_PREFIX} is absorbing power!"))\
    F(STRINGID_NOONEWILLBEABLETORUNAWAY,                                         ("No one will be able to run away during the next turn!"))\
    F(STRINGID_DESTINYKNOTACTIVATES,                                         ("{B_DEF_NAME_WITH_PREFIX} fell in love because of the {B_LAST_ITEM}!"))\
    F(STRINGID_CLOAKEDINAFREEZINGLIGHT,                                         ("{B_ATK_NAME_WITH_PREFIX} became cloaked in a freezing light!"))\
    F(STRINGID_CLEARAMULETWONTLOWERSTATS,                                         ("The effects of the {B_LAST_ITEM} held by {B_SCR_NAME_WITH_PREFIX2} prevents its stats from being lowered!"))\
    F(STRINGID_FERVENTWISHREACHED,                                         ("{B_ATK_TRAINER_NAME}'s fervent wish has reached {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_AIRLOCKACTIVATES,                                         ("The effects of the weather disappeared."))\
    F(STRINGID_PRESSUREENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is exerting its pressure!"))\
    F(STRINGID_DARKAURAENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is radiating a dark aura!"))\
    F(STRINGID_FAIRYAURAENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is radiating a fairy aura!"))\
    F(STRINGID_AURABREAKENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} reversed all other Pokémon's auras!"))\
    F(STRINGID_COMATOSEENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} is drowsing!"))\
    F(STRINGID_SCREENCLEANERENTERS,                                         ("All screens on the field were cleansed!"))\
    F(STRINGID_FETCHEDPOKEBALL,                                         ("{B_SCR_NAME_WITH_PREFIX} found a {B_LAST_ITEM}!"))\
    F(STRINGID_ASANDSTORMKICKEDUP,                                         ("A sandstorm kicked up!"))\
    F(STRINGID_PKMNSWILLPERISHIN3TURNS,                                         ("Both Pokémon will perish in three turns!"))\
    F(STRINGID_AURAFLAREDTOLIFE,                                         ("{B_DEF_NAME_WITH_PREFIX}'s aura flared to life!"))\
    F(STRINGID_ASONEENTERS,                                         ("{B_SCR_NAME_WITH_PREFIX} has two Abilities!"))\
    F(STRINGID_CURIOUSMEDICINEENTERS,                                         ("{B_EFF_NAME_WITH_PREFIX}'s stat changes were removed!"))\
    F(STRINGID_CANACTFASTERTHANKSTO,                                         ("{B_ATK_NAME_WITH_PREFIX} can act faster than normal, thanks to its {B_BUFF1}!"))\
    F(STRINGID_MICLEBERRYACTIVATES,                                         ("{B_SCR_NAME_WITH_PREFIX} boosted the accuracy of its next move using {B_LAST_ITEM}!"))\
    F(STRINGID_PKMNSHOOKOFFTHETAUNT,                                         ("{B_SCR_NAME_WITH_PREFIX} shook off the taunt!"))\
    F(STRINGID_PKMNGOTOVERITSINFATUATION,                                         ("{B_SCR_NAME_WITH_PREFIX} got over its infatuation!"))\
    F(STRINGID_ITEMCANNOTBEREMOVED,                                         ("{B_ATK_NAME_WITH_PREFIX}'s item cannot be removed!"))\
    F(STRINGID_STICKYBARBTRANSFER,                                         ("The {B_LAST_ITEM} attached itself to {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_PKMNBURNHEALED,                                         ("{B_DEF_NAME_WITH_PREFIX}'s burn was cured!"))\
    F(STRINGID_REDCARDACTIVATE,                                         ("{B_SCR_NAME_WITH_PREFIX} held up its Red Card against {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_EJECTBUTTONACTIVATE,                                         ("{B_SCR_NAME_WITH_PREFIX} is switched out with the {B_LAST_ITEM}!"))\
    F(STRINGID_ATKGOTOVERINFATUATION,                                         ("{B_SCR_NAME_WITH_PREFIX} got over its infatuation!"))\
    F(STRINGID_TORMENTEDNOMORE,                                         ("{B_SCR_NAME_WITH_PREFIX} is no longer tormented!"))\
    F(STRINGID_HEALBLOCKEDNOMORE,                                         ("{B_SCR_NAME_WITH_PREFIX} is cured of its heal block!"))\
    F(STRINGID_ATTACKERBECAMEFULLYCHARGED,                                         ("{B_ATK_NAME_WITH_PREFIX} became fully charged due to its bond with its trainer!\p"))\
    F(STRINGID_ATTACKERBECAMEASHSPECIES,                                         ("{B_ATK_NAME_WITH_PREFIX} became Ash-Greninja!\p"))\
    F(STRINGID_EXTREMELYHARSHSUNLIGHT,                                         ("The sunlight turned extremely harsh!"))\
    F(STRINGID_EXTREMESUNLIGHTFADED,                                         ("The extremely harsh sunlight faded!"))\
    F(STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,                                         ("The Water-type attack evaporated in the extremely harsh sunlight!"))\
    F(STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED,                                         ("The extremely harsh sunlight was not lessened at all!"))\
    F(STRINGID_HEAVYRAIN,                                         ("A heavy rain began to fall!"))\
    F(STRINGID_HEAVYRAINLIFTED,                                         ("The heavy rain has lifted!"))\
    F(STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,                                         ("The Fire-type attack fizzled out in the heavy rain!"))\
    F(STRINGID_NORELIEFROMHEAVYRAIN,                                         ("There is no relief from this heavy rain!"))\
    F(STRINGID_MYSTERIOUSAIRCURRENT,                                         ("Mysterious strong winds are protecting Flying-type Pokémon!"))\
    F(STRINGID_STRONGWINDSDISSIPATED,                                         ("The mysterious strong winds have dissipated!"))\
    F(STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,                                         ("The mysterious strong winds blow on regardless!"))\
    F(STRINGID_ATTACKWEAKENEDBSTRONGWINDS,                                         ("The mysterious strong winds weakened the attack!"))\
    F(STRINGID_STUFFCHEEKSCANTSELECT,                                         ("It can't use the move because it doesn't have a Berry!\p"))\
    F(STRINGID_PKMNREVERTEDTOPRIMAL,                                         ("{B_SCR_NAME_WITH_PREFIX}'s Primal Reversion! It reverted to its primal state!"))\
    F(STRINGID_BUTPOKEMONCANTUSETHEMOVE,                                         ("But {B_ATK_NAME_WITH_PREFIX2} can't use the move!"))\
    F(STRINGID_BUTHOOPACANTUSEIT,                                         ("But {B_ATK_NAME_WITH_PREFIX2} can't use it the way it is now!"))\
    F(STRINGID_BROKETHROUGHPROTECTION,                                         ("It broke through {B_DEF_NAME_WITH_PREFIX2}'s protection!"))\
    F(STRINGID_ABILITYALLOWSONLYMOVE,                                         ("{B_ATK_ABILITY} only allows the use of {B_CURRENT_MOVE}!\p"))\
    F(STRINGID_SWAPPEDABILITIES,                                         ("{B_DEF_NAME_WITH_PREFIX} swapped Abilities with its target!"))\
    F(STRINGID_PASTELVEILENTERS,                                         ("{B_DEF_NAME_WITH_PREFIX} was cured of its poisoning!"))\
    F(STRINGID_BATTLERTYPECHANGEDTO,                                         ("{B_SCR_NAME_WITH_PREFIX}'s type changed to {B_BUFF1}!"))\
    F(STRINGID_BOTHCANNOLONGERESCAPE,                                         ("Neither Pokémon can run away!"))\
    F(STRINGID_CANTESCAPEDUETOUSEDMOVE,                                         ("{B_ATK_NAME_WITH_PREFIX} can no longer escape because it used No Retreat!"))\
    F(STRINGID_PKMNBECAMEWEAKERTOFIRE,                                         ("{B_DEF_NAME_WITH_PREFIX} became weaker to fire!"))\
    F(STRINGID_ABOUTTOUSEPOLTERGEIST,                                         ("{B_DEF_NAME_WITH_PREFIX} is about to be attacked by its {B_BUFF1}!"))\
    F(STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE,                                         ("{B_DEF_NAME_WITH_PREFIX} can no longer escape because of Octolock!"))\
    F(STRINGID_NEUTRALIZINGGASENTERS,                                         ("Neutralizing gas filled the area!"))\
    F(STRINGID_NEUTRALIZINGGASOVER,                                         ("The effects of the neutralizing gas wore off!"))\
    F(STRINGID_TARGETTOOHEAVY,                                         ("{B_DEF_NAME_WITH_PREFIX} is too heavy to be lifted!"))\
    F(STRINGID_PKMNTOOKTARGETHIGH,                                         ("{B_ATK_NAME_WITH_PREFIX} took {B_DEF_NAME_WITH_PREFIX2} into the sky!"))\
    F(STRINGID_PKMNINSNAPTRAP,                                         ("{B_DEF_NAME_WITH_PREFIX} got trapped by a snap trap!"))\
    F(STRINGID_METEORBEAMCHARGING,                                         ("{B_ATK_NAME_WITH_PREFIX} is overflowing with space power!"))\
    F(STRINGID_HEATUPBEAK,                                         ("{B_ATK_NAME_WITH_PREFIX} started heating up its beak!"))\
    F(STRINGID_COURTCHANGE,                                         ("{B_ATK_NAME_WITH_PREFIX} swapped the battle effects affecting each side of the field!"))\
    F(STRINGID_ZPOWERSURROUNDS,                                         ("{B_ATK_NAME_WITH_PREFIX} surrounded itself with its Z-Power!"))\
    F(STRINGID_ZMOVEUNLEASHED,                                         ("{B_ATK_NAME_WITH_PREFIX} unleashes its full-force Z-Move!"))\
    F(STRINGID_ZMOVERESETSSTATS,                                         ("{B_SCR_NAME_WITH_PREFIX} returned its decreased stats to normal using its Z-Power!"))\
    F(STRINGID_ZMOVEALLSTATSUP,                                         ("{B_SCR_NAME_WITH_PREFIX} boosted its stats using its Z-Power!"))\
    F(STRINGID_ZMOVEZBOOSTCRIT,                                         ("{B_SCR_NAME_WITH_PREFIX} boosted its critical-hit ratio using its Z-Power!"))\
    F(STRINGID_ZMOVERESTOREHP,                                         ("{B_SCR_NAME_WITH_PREFIX} restored its HP using its Z-Power!"))\
    F(STRINGID_ZMOVESTATUP,                                         ("{B_SCR_NAME_WITH_PREFIX} boosted its stats using its Z-Power!"))\
    F(STRINGID_ZMOVEHPTRAP,                                         ("{B_SCR_NAME_WITH_PREFIX}'s HP was restored by the Z-Power!"))\
    F(STRINGID_ATTACKEREXPELLEDTHEPOISON,                                         ("{B_ATK_NAME_WITH_PREFIX} managed to expel the poison so you wouldn't worry!"))\
    F(STRINGID_ATTACKERSHOOKITSELFAWAKE,                                         ("{B_ATK_NAME_WITH_PREFIX} shook itself awake so you wouldn't worry!"))\
    F(STRINGID_ATTACKERBROKETHROUGHPARALYSIS,                                         ("{B_ATK_NAME_WITH_PREFIX} gathered all its energy to break through its paralysis so you wouldn't worry!"))\
    F(STRINGID_ATTACKERHEALEDITSBURN,                                         ("{B_ATK_NAME_WITH_PREFIX} cured its burn through sheer determination so you wouldn't worry!"))\
    F(STRINGID_ATTACKERMELTEDTHEICE,                                         ("{B_ATK_NAME_WITH_PREFIX} melted the ice with its fiery determination so you wouldn't worry!"))\
    F(STRINGID_TARGETTOUGHEDITOUT,                                         ("{B_DEF_NAME_WITH_PREFIX} toughed it out so you wouldn't feel sad!"))\
    F(STRINGID_ATTACKERLOSTELECTRICTYPE,                                         ("{B_ATK_NAME_WITH_PREFIX} used up all its electricity!"))\
    F(STRINGID_ATTACKERSWITCHEDSTATWITHTARGET,                                         ("{B_ATK_NAME_WITH_PREFIX} switched {B_BUFF1} with its target!"))\
    F(STRINGID_BEINGHITCHARGEDPKMNWITHPOWER,                                         ("Being hit by {B_CURRENT_MOVE} charged {B_DEF_NAME_WITH_PREFIX2} with power!"))\
    F(STRINGID_SUNLIGHTACTIVATEDABILITY,                                         ("The harsh sunlight activated {B_SCR_NAME_WITH_PREFIX2}'s Protosynthesis!"))\
    F(STRINGID_STATWASHEIGHTENED,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} was heightened!"))\
    F(STRINGID_ELECTRICTERRAINACTIVATEDABILITY,                                         ("The Electric Terrain activated {B_SCR_NAME_WITH_PREFIX2}'s Quark Drive!"))\
    F(STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} weakened the {B_BUFF1} of all surrounding Pokémon!\p"))\
    F(STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN,                                         ("{B_SCR_NAME_WITH_PREFIX} gained strength from the fallen!"))\
/*not in gen 5+, abl popup*/    F(STRINGID_PKMNSABILITYPREVENTSABILITY,                      ("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} prevents {B_DEF_NAME_WITH_PREFIX2}'s {B_DEF_ABILITY} from working!"))\
    F(STRINGID_PREPARESHELLTRAP,                                         ("{B_ATK_NAME_WITH_PREFIX} set a shell trap!"))\
    F(STRINGID_SHELLTRAPDIDNTWORK,                                         ("{B_ATK_NAME_WITH_PREFIX}'s shell trap didn't work!"))\
    F(STRINGID_SPIKESDISAPPEAREDFROMTEAM,                                         ("The spikes disappeared from the ground around {B_ATK_TEAM2} team!"))\
    F(STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM,                                         ("The poison spikes disappeared from the ground around {B_ATK_TEAM2} team!"))\
    F(STRINGID_STICKYWEBDISAPPEAREDFROMTEAM,                                         ("The sticky web has disappeared from the ground around {B_ATK_TEAM2} team!"))\
    F(STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM,                                         ("The pointed stones disappeared from around {B_ATK_TEAM2} team!"))\
    F(STRINGID_COULDNTFULLYPROTECT,                                         ("{B_DEF_NAME_WITH_PREFIX} couldn't fully protect itself and got hurt!"))\
    F(STRINGID_STOCKPILEDEFFECTWOREOFF,                                         ("{B_ATK_NAME_WITH_PREFIX}'s stockpiled effect wore off!"))\
    F(STRINGID_PKMNREVIVEDREADYTOFIGHT,                                         ("{B_BUFF1} was revived and is ready to fight again!"))\
    F(STRINGID_ITEMRESTOREDSPECIESHEALTH,                                         ("{B_BUFF1} had its HP restored."))\
    F(STRINGID_ITEMCUREDSPECIESSTATUS,                                         ("{B_BUFF1} had its status healed!"))\
    F(STRINGID_ITEMRESTOREDSPECIESPP,                                         ("{B_BUFF1} had its PP restored!"))\
    F(STRINGID_THUNDERCAGETRAPPED,                                         ("{B_ATK_NAME_WITH_PREFIX} trapped {B_DEF_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_PKMNHURTBYFROSTBITE,                                         ("{B_ATK_NAME_WITH_PREFIX} was hurt by its frostbite!"))\
    F(STRINGID_PKMNGOTFROSTBITE,                                         ("{B_EFF_NAME_WITH_PREFIX} got frostbite!"))\
    F(STRINGID_PKMNSITEMHEALEDFROSTBITE,                                         ("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} cured its frostbite!"))\
    F(STRINGID_ATTACKERHEALEDITSFROSTBITE,                                         ("{B_ATK_NAME_WITH_PREFIX} cured its frostbite through sheer determination so you wouldn't worry!"))\
    F(STRINGID_PKMNFROSTBITEHEALED,                                         ("{B_DEF_NAME_WITH_PREFIX}'s frostbite was cured!"))\
    F(STRINGID_PKMNFROSTBITEHEALED2,                                         ("{B_ATK_NAME_WITH_PREFIX}'s frostbite was cured!"))\
    F(STRINGID_PKMNFROSTBITEHEALEDBY,                                         ("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} cured its frostbite!"))\
    F(STRINGID_MIRRORHERBCOPIED,                                         ("{B_SCR_NAME_WITH_PREFIX} used its Mirror Herb to mirror its opponent's stat changes!"))\
    F(STRINGID_STARTEDSNOW,                                         ("It started to snow!"))\
    /*//not in gen 5+ (lol)*/F(STRINGID_SNOWCONTINUES,            ("Snow continues to fall."))\
    F(STRINGID_SNOWSTOPPED,                                         ("The snow stopped."))\
    F(STRINGID_SNOWWARNINGSNOW,                                         ("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade it snow!"))\
    F(STRINGID_PKMNITEMMELTED,                                         ("{B_ATK_NAME_WITH_PREFIX} corroded {B_DEF_NAME_WITH_PREFIX2}'s {B_LAST_ITEM}!"))\
    F(STRINGID_ULTRABURSTREACTING,                                         ("Bright light is about to burst out of {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_ULTRABURSTCOMPLETED,                                         ("{B_ATK_NAME_WITH_PREFIX} regained its true power through Ultra Burst!"))\
    F(STRINGID_TEAMGAINEDEXP,                                         ("The rest of your team gained Exp. Points thanks to the Exp. Share!\p"))\
    F(STRINGID_CURRENTMOVECANTSELECT,                                         ("{B_BUFF1} cannot be used!\p"))\
    F(STRINGID_TARGETISBEINGSALTCURED,                                         ("{B_DEF_NAME_WITH_PREFIX} is being salt cured!"))\
    F(STRINGID_TARGETISHURTBYSALTCURE,                                         ("{B_ATK_NAME_WITH_PREFIX} is hurt by {B_BUFF1}!"))\
    F(STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP,                                         ("{B_DEF_NAME_WITH_PREFIX} got covered in sticky candy syrup!"))\
    F(STRINGID_SHARPSTEELFLOATS,                                         ("Sharp-pointed pieces of steel started floating around {B_DEF_TEAM2} Pokémon!"))\
    F(STRINGID_SHARPSTEELDMG,                                         ("The sharp steel bit into {B_DEF_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_PKMNBLEWAWAYSHARPSTEEL,                                         ("{B_ATK_NAME_WITH_PREFIX} blew away sharp steel!"))\
    F(STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM,                                         ("The pieces of steel surrounding {B_ATK_TEAM2} Pokémon disappeared!"))\
    F(STRINGID_TEAMTRAPPEDWITHVINES,                                         ("{B_DEF_TEAM1} Pokémon got trapped with vines!"))\
    F(STRINGID_PKMNHURTBYVINES,                                         ("{B_ATK_NAME_WITH_PREFIX} is hurt by G-Max Vine Lash's ferocious beating!"))\
    F(STRINGID_TEAMCAUGHTINVORTEX,                                         ("{B_DEF_TEAM1} Pokémon got caught in a vortex of water!"))\
    F(STRINGID_PKMNHURTBYVORTEX,                                         ("{B_ATK_NAME_WITH_PREFIX} is hurt by G-Max Cannonade's vortex!"))\
    F(STRINGID_TEAMSURROUNDEDBYFIRE,                                         ("{B_DEF_TEAM1} Pokémon were surrounded by fire!"))\
    F(STRINGID_PKMNBURNINGUP,                                         ("{B_ATK_NAME_WITH_PREFIX} is burning up within G-Max Wildfire's flames!"))\
    F(STRINGID_TEAMSURROUNDEDBYROCKS,                                         ("{B_DEF_TEAM1} Pokémon became surrounded by rocks!"))\
    F(STRINGID_PKMNHURTBYROCKSTHROWN,                                         ("{B_ATK_NAME_WITH_PREFIX} is hurt by rocks thrown out by G-Max Volcalith!"))\
    F(STRINGID_MOVEBLOCKEDBYDYNAMAX,                                         ("The move was blocked by the power of Dynamax!"))\
    F(STRINGID_ZEROTOHEROTRANSFORMATION,                                         ("{B_SCR_NAME_WITH_PREFIX} underwent a heroic transformation!"))\
    F(STRINGID_THETWOMOVESBECOMEONE,                                         ("The two moves have become one! It's a combined move!{PAUSE 16}"))\
    F(STRINGID_ARAINBOWAPPEAREDONSIDE,                                         ("A rainbow appeared in the sky on {B_ATK_TEAM2} team's side!"))\
    F(STRINGID_THERAINBOWDISAPPEARED,                                         ("The rainbow on {B_ATK_TEAM2} team's side disappeared!"))\
    F(STRINGID_WAITINGFORPARTNERSMOVE,                                         ("{B_ATK_NAME_WITH_PREFIX} is waiting for {B_ATK_PARTNER_NAME}'s move…{PAUSE 16}"))\
    F(STRINGID_SEAOFFIREENVELOPEDSIDE,                                         ("A sea of fire enveloped {B_DEF_TEAM2} team!"))\
    F(STRINGID_HURTBYTHESEAOFFIRE,                                         ("{B_ATK_NAME_WITH_PREFIX} was hurt by the sea of fire!"))\
    F(STRINGID_THESEAOFFIREDISAPPEARED,                                         ("The sea of fire around {B_ATK_TEAM2} team disappeared!"))\
    F(STRINGID_SWAMPENVELOPEDSIDE,                                         ("A swamp enveloped {B_DEF_TEAM2} team!"))\
    F(STRINGID_THESWAMPDISAPPEARED,                                         ("The swamp around {B_ATK_TEAM2} team disappeared!"))\
    F(STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE,                                         ("{B_ATK_NAME_WITH_PREFIX} is preparing to tell a chillingly bad joke!"))\
    F(STRINGID_HOSPITALITYRESTORATION,                                         ("{B_EFF_NAME_WITH_PREFIX} drank down all the matcha that {B_SCR_NAME_WITH_PREFIX2} made!"))\
    F(STRINGID_ELECTROSHOTCHARGING,                                         ("{B_ATK_NAME_WITH_PREFIX} absorbed electricity!"))\
    F(STRINGID_ITEMWASUSEDUP,                                         ("The {B_LAST_ITEM} was used up…"))\
    F(STRINGID_ATTACKERLOSTITSTYPE,                                         ("{B_ATK_NAME_WITH_PREFIX} lost its {B_BUFF1} type!"))\
    F(STRINGID_SHEDITSTAIL,                                         ("{B_ATK_NAME_WITH_PREFIX} shed its tail to create a decoy!"))\
    F(STRINGID_CLOAKEDINAHARSHLIGHT,                                         ("{B_ATK_NAME_WITH_PREFIX} became cloaked in a harsh light!"))\
    F(STRINGID_SUPERSWEETAROMAWAFTS,                                         ("A supersweet aroma is wafting from the syrup covering {B_ATK_NAME_WITH_PREFIX2}!"))\
    F(STRINGID_DIMENSIONSWERETWISTED,                                         ("The dimensions were twisted!"))\
    F(STRINGID_BIZARREARENACREATED,                                         ("A bizarre area was created in which Pokémon's held items lose their effects!"))\
    F(STRINGID_BIZARREAREACREATED,                                         ("A bizarre area was created in which Defense and Sp. Def stats are swapped!"))\
    F(STRINGID_TIDYINGUPCOMPLETE,                                         ("Tidying up complete!"))\
    F(STRINGID_PKMNTERASTALLIZEDINTO,                                         ("{B_ATK_NAME_WITH_PREFIX} terastallized into the {B_BUFF1} type!"))\
    F(STRINGID_BOOSTERENERGYACTIVATES,                                         ("{B_SCR_NAME_WITH_PREFIX} used its {B_LAST_ITEM} to activate {B_SCR_ABILITY}!"))\
    F(STRINGID_FOG_ROLLED_IN,                                         ("A thick fog rolled in!"))\
    F(STRINGID_FOGISDEEP,                                         ("The fog is deep…"))\
    F(STRINGID_FOGLIFTED,                                         ("The fog lifted."))\
    F(STRINGID_PKMNMADESHELLGLEAM,                                         ("{B_DEF_NAME_WITH_PREFIX} made its shell gleam! It's distorting type matchups!"))\
    F(STRINGID_FICKLEBEAMDOUBLED,                                         ("{B_ATK_NAME_WITH_PREFIX} is going all out for this attack!"))\
    F(STRINGID_COMMANDERACTIVATES,                                         ("{B_SCR_NAME_WITH_PREFIX} was swallowed by Dondozo and became Dondozo's commander!"))\
    F(STRINGID_BATTERYCONSUMED,                                         ("{B_SCR_NAME_WITH_PREFIX} was absorbed by Vikavolt and became Vikavolt's battery!"))\
    F(STRINGID_POKEFLUTECATCHY,                                         ("{B_PLAYER_NAME} played the {B_LAST_ITEM}.\pNow, that's a catchy tune!"))\
    F(STRINGID_POKEFLUTE,                                         ("{B_PLAYER_NAME} played the {B_LAST_ITEM}."))\
    F(STRINGID_MONHEARINGFLUTEAWOKE,                                         ("The Pokémon hearing the flute awoke!"))\
    F(STRINGID_SUNLIGHTISHARSH,                                         ("The sunlight is harsh!"))\
    F(STRINGID_ITISHAILING,                                         ("It's hailing!"))\
    F(STRINGID_ITISSNOWING,                                         ("It's snowing!"))\
    F(STRINGID_ISCOVEREDWITHGRASS,                                         ("The battlefield is covered with grass!"))\
    F(STRINGID_MISTSWIRLSAROUND,                                         ("Mist swirls around the battlefield!"))\
    F(STRINGID_ELECTRICCURRENTISRUNNING,                                         ("An electric current is running across the battlefield!"))\
    F(STRINGID_SEEMSWEIRD,                                         ("The battlefield seems weird!"))\
    F(STRINGID_WAGGLINGAFINGER,                                         ("Waggling a finger let it use {B_CURRENT_MOVE}!"))\
    F(STRINGID_BLOCKEDBYSLEEPCLAUSE,                                         ("Sleep Clause kept {B_DEF_NAME_WITH_PREFIX2} awake!"))\
    F(STRINGID_SUPEREFFECTIVETWOFOES,                                         ("It's super effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}!"))\
    F(STRINGID_NOTVERYEFFECTIVETWOFOES,                                         ("It's not very effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}!"))\
    F(STRINGID_ITDOESNTAFFECTTWOFOES,                                         ("It doesn't affect {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}…"))\
    F(STRINGID_SENDCAUGHTMONPARTYORBOX,                                         ("Add {B_DEF_NAME} to your party?"))\
    F(STRINGID_PKMNDYNAMAXED,                                         ("{B_ATK_NAME_WITH_PREFIX} grew huge into its Dynamax form!"))\
    F(STRINGID_PKMNGIGANTAMAXED,                                         ("{B_ATK_NAME_WITH_PREFIX} grew huge into its Gigantamax form!"))\
    F(STRINGID_TIMETODYNAMAX,                                         ("Time to Dynamax!"))\
    F(STRINGID_TIMETOGIGANTAMAX,                                         ("Time to Gigantamax!"))\
    F(STRINGID_QUESTIONFORFEITBATTLE,                                         ("Would you like to give up on this battle and quit now? Quitting the battle is the same as losing the battle."))\
    F(STRINGID_POWERCONSTRUCTPRESENCEOFMANY,                                         ("You sense the presence of many!"))\
    F(STRINGID_POWERCONSTRUCTTRANSFORM,                                         ("{B_ATK_NAME_WITH_PREFIX} transformed into its Complete Forme!"))\
    F(STRINGID_ABILITYSHIELDPROTECTS,                                         ("{B_ATK_NAME_WITH_PREFIX}'s Ability is protected by the effects of its {B_LAST_ITEM}!"))\

#define UNPACK_BATTLE_STRING_ENUMS(_enum, ...) _enum,
#define UNPACK_BATTLE_STRING_VALUES(_enum, _txtstring, ...) [_enum] = COMPOUND_STRING _txtstring,

//plan for definitinons is take battlemessage table as is
//then format to match
//what I need is to identify what string overlap
//between FR and EE I'll need to take what I have 
//since I've changed some strings as well
//start w that think want take fr specific strings at front
enum StringID
{
 //hard code ids actual text strings below this - make no string additions below this
    BATTLE_STRING_DEFINITIONS(UNPACK_BATTLE_STRING_ENUMS)
    STRINGID_COUNT

};



//ok think use this as template for how I want order in battle_message.c to be
//when properly outlined will be the order going forward
//base strings mostly same between both repos
//fire red specific strings oak pokedude ghost stuff
//followed by expansion strings
//finally custom strings
// todo: make some of those names less vague: attacker/target vs pkmn, etc.
enum StringID
{
     
     STRINGID_TRAINER1LOSETEXT, // Make sure to add new messages below this marker
     STRINGID_PKMNGAINEDEXP,
     STRINGID_PKMNGREWTOLV,
     STRINGID_PKMNLEARNEDMOVE,
     STRINGID_TRYTOLEARNMOVE1,
     STRINGID_TRYTOLEARNMOVE2,
     STRINGID_TRYTOLEARNMOVE3,
     STRINGID_PKMNFORGOTMOVE,
     STRINGID_STOPLEARNINGMOVE,
     STRINGID_DIDNOTLEARNMOVE,
     STRINGID_PKMNLEARNEDMOVE2,
     STRINGID_ATTACKMISSED,
     STRINGID_PKMNPROTECTEDITSELF,
     STRINGID_STATSWONTINCREASE2,
     STRINGID_AVOIDEDDAMAGE,
     STRINGID_ITDOESNTAFFECT,
     STRINGID_ATTACKERFAINTED,
     STRINGID_TARGETFAINTED,
     STRINGID_PLAYERGOTMONEY,
     STRINGID_PLAYERWHITEOUT,
     STRINGID_PLAYERWHITEOUT2,
     STRINGID_PREVENTSESCAPE,
     STRINGID_HITXTIMES,
     STRINGID_PKMNFELLASLEEP,
     STRINGID_PKMNMADESLEEP,
     STRINGID_PKMNALREADYASLEEP,
     STRINGID_PKMNALREADYASLEEP2,
     STRINGID_PKMNWASNTAFFECTED,
     STRINGID_PKMNWASPOISONED,
     STRINGID_PKMNPOISONEDBY,
     STRINGID_PKMNHURTBYPOISON,
     STRINGID_PKMNALREADYPOISONED,
     STRINGID_PKMNBADLYPOISONED,
     STRINGID_PKMNENERGYDRAINED,
     STRINGID_PKMNWASBURNED,
     STRINGID_PKMNBURNEDBY,
     STRINGID_PKMNHURTBYBURN,
     STRINGID_PKMNWASFROZEN,
     STRINGID_PKMNFROZENBY,
     STRINGID_PKMNISFROZEN,
     STRINGID_PKMNWASDEFROSTED,
     STRINGID_PKMNWASDEFROSTED2,
     STRINGID_PKMNWASDEFROSTEDBY,
     STRINGID_PKMNWASPARALYZED,
     STRINGID_PKMNWASPARALYZEDBY,
     STRINGID_PKMNISPARALYZED,
     STRINGID_PKMNISALREADYPARALYZED,
     STRINGID_PKMNHEALEDPARALYSIS,
     STRINGID_PKMNDREAMEATEN,
     STRINGID_STATSWONTINCREASE,
     STRINGID_STATSWONTDECREASE,
     STRINGID_TEAMSTOPPEDWORKING,
     STRINGID_FOESTOPPEDWORKING,
     STRINGID_PKMNISCONFUSED,
     STRINGID_PKMNHEALEDCONFUSION,
     STRINGID_PKMNWASCONFUSED,
     STRINGID_PKMNALREADYCONFUSED,
     STRINGID_PKMNFELLINLOVE,
     STRINGID_PKMNINLOVEWITHBATTLER,
     STRINGID_PKMNINLOVE,
     STRINGID_PKMNIMMOBILIZEDBYLOVE,
     STRINGID_PKMNBLOWNAWAY,
     STRINGID_PKMNCHANGEDTYPE,
     STRINGID_PKMNFLINCHED,
     STRINGID_PKMNREGAINEDHEALTH,
     STRINGID_PKMNHPFULL,
     STRINGID_PKMNRAISEDSPDEF,
     STRINGID_PKMNRAISEDDEF,
     STRINGID_PKMNCOVEREDBYVEIL,
     STRINGID_PKMNUSEDSAFEGUARD,
     STRINGID_PKMNSAFEGUARDEXPIRED,
     STRINGID_PKMNWENTTOSLEEP,
     STRINGID_PKMNSLEPTHEALTHY,
     STRINGID_PKMNWHIPPEDWHIRLWIND,
     STRINGID_PKMNTOOKSUNLIGHT,
     STRINGID_PKMNLOWEREDHEAD,
     STRINGID_PKMNISGLOWING,
     STRINGID_PKMNFLEWHIGH,
     STRINGID_PKMNDUGHOLE,
     STRINGID_PKMNSQUEEZEDBYBIND,
     STRINGID_PKMNTRAPPEDINVORTEX,
     STRINGID_PKMNWRAPPEDBY,
     STRINGID_PKMNCLAMPED,
     STRINGID_PKMNHURTBY,
     STRINGID_PKMNFREEDFROM,
     STRINGID_PKMNCRASHED,
     STRINGID_PKMNSHROUDEDINMIST,
     STRINGID_PKMNPROTECTEDBYMIST,
     STRINGID_PKMNGETTINGPUMPED,
     STRINGID_PKMNHITWITHRECOIL,
     STRINGID_PKMNPROTECTEDITSELF2,
     STRINGID_PKMNBUFFETEDBYSANDSTORM,
     STRINGID_PKMNPELTEDBYHAIL,
     STRINGID_PKMNSEEDED,
     STRINGID_PKMNEVADEDATTACK,
     STRINGID_PKMNSAPPEDBYLEECHSEED,
     STRINGID_PKMNFASTASLEEP,
     STRINGID_PKMNWOKEUP,
     STRINGID_PKMNUPROARKEPTAWAKE,
     STRINGID_PKMNWOKEUPINUPROAR,
     STRINGID_PKMNCAUSEDUPROAR,
     STRINGID_PKMNMAKINGUPROAR,
     STRINGID_PKMNCALMEDDOWN,
     STRINGID_PKMNCANTSLEEPINUPROAR,
     STRINGID_PKMNSTOCKPILED,
     STRINGID_PKMNCANTSTOCKPILE,
     STRINGID_PKMNCANTSLEEPINUPROAR2,
     STRINGID_UPROARKEPTPKMNAWAKE,
     STRINGID_PKMNSTAYEDAWAKEUSING,
     STRINGID_PKMNSTORINGENERGY,
     STRINGID_PKMNUNLEASHEDENERGY,
     STRINGID_PKMNFATIGUECONFUSION,
     STRINGID_PKMNPICKEDUPITEM,
     STRINGID_PKMNUNAFFECTED,
     STRINGID_PKMNTRANSFORMEDINTO,
     STRINGID_PKMNMADESUBSTITUTE,
     STRINGID_PKMNHASSUBSTITUTE,
     STRINGID_SUBSTITUTEDAMAGED,
     STRINGID_PKMNSUBSTITUTEFADED,
     STRINGID_PKMNMUSTRECHARGE,
     STRINGID_PKMNRAGEBUILDING,
     STRINGID_PKMNMOVEWASDISABLED,
     STRINGID_PKMNMOVEISDISABLED,
     STRINGID_PKMNMOVEDISABLEDNOMORE,
     STRINGID_PKMNGOTENCORE,
     STRINGID_PKMNENCOREENDED,
     STRINGID_PKMNTOOKAIM,
     STRINGID_PKMNSKETCHEDMOVE,
     STRINGID_PKMNTRYINGTOTAKEFOE,
     STRINGID_PKMNTOOKFOE,
     STRINGID_PKMNREDUCEDPP,
     STRINGID_PKMNSTOLEITEM,
     STRINGID_TARGETCANTESCAPENOW,
     STRINGID_PKMNFELLINTONIGHTMARE,
     STRINGID_PKMNLOCKEDINNIGHTMARE,
     STRINGID_PKMNLAIDCURSE,
     STRINGID_PKMNAFFLICTEDBYCURSE,
     STRINGID_SPIKESSCATTERED,
     STRINGID_PKMNHURTBYSPIKES,
     STRINGID_PKMNIDENTIFIED,
     STRINGID_PKMNPERISHCOUNTFELL,
     STRINGID_PKMNBRACEDITSELF,
     STRINGID_PKMNENDUREDHIT,
     STRINGID_MAGNITUDESTRENGTH,
     STRINGID_PKMNCUTHPMAXEDATTACK,
     STRINGID_PKMNCOPIEDSTATCHANGES,
     STRINGID_PKMNGOTFREE,
     STRINGID_PKMNSHEDLEECHSEED,
     STRINGID_PKMNBLEWAWAYSPIKES,
     STRINGID_PKMNFLEDFROMBATTLE,
     STRINGID_PKMNFORESAWATTACK,
     STRINGID_PKMNTOOKATTACK,
     STRINGID_PKMNATTACK,
     STRINGID_PKMNCENTERATTENTION,
     STRINGID_PKMNCHARGINGPOWER,
     STRINGID_NATUREPOWERTURNEDINTO,
     STRINGID_PKMNSTATUSNORMAL,
     STRINGID_PKMNHASNOMOVESLEFT,
     STRINGID_PKMNSUBJECTEDTOTORMENT,
     STRINGID_PKMNCANTUSEMOVETORMENT,
     STRINGID_PKMNTIGHTENINGFOCUS,
     STRINGID_PKMNFELLFORTAUNT,
     STRINGID_PKMNCANTUSEMOVETAUNT,
     STRINGID_PKMNREADYTOHELP,
     STRINGID_PKMNSWITCHEDITEMS,
     STRINGID_PKMNCOPIEDFOE,
     STRINGID_PKMNMADEWISH,
     STRINGID_PKMNWISHCAMETRUE,
     STRINGID_PKMNPLANTEDROOTS,
     STRINGID_PKMNABSORBEDNUTRIENTS,
     STRINGID_PKMNANCHOREDITSELF,
     STRINGID_PKMNWASMADEDROWSY,
     STRINGID_PKMNKNOCKEDOFF,
     STRINGID_PKMNSWAPPEDABILITIES,
     STRINGID_PKMNSEALEDOPPONENTMOVE,
     STRINGID_PKMNCANTUSEMOVESEALED,
     STRINGID_PKMNWANTSGRUDGE,
     STRINGID_PKMNLOSTPPGRUDGE,
     STRINGID_PKMNSHROUDEDITSELF,
     STRINGID_PKMNMOVEBOUNCED,
     STRINGID_PKMNWAITSFORTARGET,
     STRINGID_PKMNSNATCHEDMOVE,
     STRINGID_PKMNMADEITRAIN,
     STRINGID_PKMNRAISEDSPEED,
     STRINGID_PKMNPROTECTEDBY,
     STRINGID_PKMNPREVENTSUSAGE,
     STRINGID_PKMNRESTOREDHPUSING,
     STRINGID_PKMNCHANGEDTYPEWITH,
     STRINGID_PKMNPREVENTSPARALYSISWITH,
     STRINGID_PKMNIGNOREDADVANCESWITH,
     STRINGID_PKMNPREVENTSPOISONINGWITH,
     STRINGID_PKMNPREVENTSCONFUSIONWITH,
     STRINGID_PKMNRAISEDFIREPOWERWITH,
     STRINGID_PKMNANCHORSITSELFWITH,
     STRINGID_PKMNCUTSATTACKWITH,
     STRINGID_PKMNPREVENTSSTATLOSSWITH,
     STRINGID_PKMNHURTSWITHABILITY,
     STRINGID_PKMNTRACED,
     STRINGID_STATSHARPLY,
     STRINGID_STATROSE,
     STRINGID_STATHARSHLY,
     STRINGID_STATFELL,
     STRINGID_ATTACKERSSTATROSE,
     STRINGID_DEFENDERSSTATROSE,
     STRINGID_ATTACKERSSTATFELL,
     STRINGID_DEFENDERSSTATFELL,
     STRINGID_CRITICALHIT,
     STRINGID_ONEHITKO,
     STRINGID_123POOF,
     STRINGID_ANDELLIPSIS,
     STRINGID_NOTVERYEFFECTIVE,
     STRINGID_SUPEREFFECTIVE,
     STRINGID_GOTAWAYSAFELY,
     STRINGID_WILDPKMNFLED,
     STRINGID_NORUNNINGFROMTRAINERS,
     STRINGID_CANTESCAPE,
     STRINGID_DONTLEAVEBIRCH,
     STRINGID_BUTNOTHINGHAPPENED,
     STRINGID_BUTITFAILED,
     STRINGID_ITHURTCONFUSION,
     STRINGID_MIRRORMOVEFAILED,
     STRINGID_STARTEDTORAIN,
     STRINGID_DOWNPOURSTARTED,
     STRINGID_RAINCONTINUES,
     STRINGID_DOWNPOURCONTINUES,
     STRINGID_RAINSTOPPED,
     STRINGID_SANDSTORMBREWED,
     STRINGID_SANDSTORMRAGES,
     STRINGID_SANDSTORMSUBSIDED,
     STRINGID_SUNLIGHTGOTBRIGHT,
     STRINGID_SUNLIGHTSTRONG,
     STRINGID_SUNLIGHTFADED,
     STRINGID_STARTEDHAIL,
     STRINGID_HAILCONTINUES,
     STRINGID_HAILSTOPPED,
     STRINGID_FAILEDTOSPITUP,
     STRINGID_FAILEDTOSWALLOW,
     STRINGID_WINDBECAMEHEATWAVE,
     STRINGID_STATCHANGESGONE,
     STRINGID_COINSSCATTERED,
     STRINGID_TOOWEAKFORSUBSTITUTE,
     STRINGID_SHAREDPAIN,
     STRINGID_BELLCHIMED,
     STRINGID_FAINTINTHREE,
     STRINGID_NOPPLEFT,
     STRINGID_BUTNOPPLEFT,
     STRINGID_PLAYERUSEDITEM,
     STRINGID_OLDMANUSEDITEM,
     STRINGID_TRAINERBLOCKEDBALL,
     STRINGID_DONTBEATHIEF,
     STRINGID_ITDODGEDBALL,
     STRINGID_YOUMISSEDPKMN,
     STRINGID_PKMNBROKEFREE,
     STRINGID_ITAPPEAREDCAUGHT,
     STRINGID_AARGHALMOSTHADIT,
     STRINGID_SHOOTSOCLOSE,
     STRINGID_GOTCHAPKMNCAUGHT,
     STRINGID_GOTCHAPKMNCAUGHT2, //think used by wally in EE
     STRINGID_GIVENICKNAMECAPTURED,
     STRINGID_PKMNSENTTOPC,
     STRINGID_PKMNDATAADDEDTODEX,
     STRINGID_ITISRAINING,
     STRINGID_SANDSTORMISRAGING,
     STRINGID_CANTESCAPE2,
     STRINGID_PKMNIGNORESASLEEP,
     STRINGID_PKMNIGNOREDORDERS,
     STRINGID_PKMNBEGANTONAP,
     STRINGID_PKMNLOAFING,
     STRINGID_PKMNWONTOBEY,
     STRINGID_PKMNTURNEDAWAY,
     STRINGID_PKMNPRETENDNOTNOTICE,
     STRINGID_ENEMYABOUTTOSWITCHPKMN,
     STRINGID_THREWROCK,
     STRINGID_THREWBAIT,
     STRINGID_PKMNWATCHINGCAREFULLY,
     STRINGID_PKMNANGRY,
     STRINGID_PKMNEATING,
     STRINGID_DUMMY288,
     STRINGID_DUMMY289,
     STRINGID_OUTOFSAFARIBALLS,
     STRINGID_PKMNSITEMCUREDPARALYSIS,
     STRINGID_PKMNSITEMCUREDPOISON,
     STRINGID_PKMNSITEMHEALEDBURN,
     STRINGID_PKMNSITEMDEFROSTEDIT,
     STRINGID_PKMNSITEMWOKEIT,
     STRINGID_PKMNSITEMSNAPPEDOUT,
     STRINGID_PKMNSITEMCUREDPROBLEM,
     STRINGID_PKMNSITEMRESTOREDHEALTH,
     STRINGID_PKMNSITEMRESTOREDPP,
     STRINGID_PKMNSITEMRESTOREDSTATUS,
     STRINGID_PKMNSITEMRESTOREDHPALITTLE,
     STRINGID_ITEMALLOWSONLYYMOVE,
     STRINGID_PKMNHUNGONWITHX,
     STRINGID_EMPTYSTRING3,
     STRINGID_PKMNSXPREVENTSBURNS,
     STRINGID_PKMNSXBLOCKSY,
     STRINGID_PKMNSXRESTOREDHPALITTLE2,
     STRINGID_PKMNSXWHIPPEDUPSANDSTORM,
     STRINGID_PKMNSXPREVENTSYLOSS,
     STRINGID_PKMNSXINFATUATEDY,
     STRINGID_PKMNSXMADEYINEFFECTIVE,
     STRINGID_PKMNSXCUREDYPROBLEM,
     STRINGID_ITSUCKEDLIQUIDOOZE,
     STRINGID_PKMNTRANSFORMED,
     STRINGID_ELECTRICITYWEAKENED,
     STRINGID_FIREWEAKENED,
     STRINGID_PKMNHIDUNDERWATER,
     STRINGID_PKMNSPRANGUP,
     STRINGID_HMMOVESCANTBEFORGOTTEN,
     STRINGID_XFOUNDONEY,
     STRINGID_PLAYERDEFEATEDTRAINER1,
     STRINGID_SOOTHINGAROMA,
     STRINGID_ITEMSCANTBEUSEDNOW,
     STRINGID_FORXCOMMAYZ,
     STRINGID_USINGXTHEYOFZN,
     STRINGID_PKMNUSEDXTOGETPUMPED,
     STRINGID_PKMNSXMADEYUSELESS,
     STRINGID_PKMNTRAPPEDBYSANDTOMB,
     STRINGID_EMPTYSTRING4,
     STRINGID_ABOOSTED,
     STRINGID_PKMNSXINTENSIFIEDSUN,
     STRINGID_PKMNMAKESGROUNDMISS,
     STRINGID_YOUTHROWABALLNOWRIGHT,
     STRINGID_PKMNSXTOOKATTACK,
     STRINGID_PKMNCHOSEXASDESTINY,
     STRINGID_PKMNLOSTFOCUS,
     STRINGID_USENEXTPKMN,
     STRINGID_PKMNFLEDUSINGITS,
     STRINGID_PKMNFLEDUSING,
     STRINGID_PKMNWASDRAGGEDOUT,
     STRINGID_PREVENTEDFROMWORKING,
     STRINGID_PKMNSITEMNORMALIZEDSTATUS,
     STRINGID_TRAINER1USEDITEM,
     STRINGID_BOXISFULL,
     STRINGID_PKMNAVOIDEDATTACK,
     STRINGID_PKMNSXMADEITINEFFECTIVE,
     STRINGID_PKMNSXPREVENTSFLINCHING,
     STRINGID_PKMNALREADYHASBURN,
     STRINGID_STATSWONTDECREASE2,
     STRINGID_PKMNSXBLOCKSY2,
     STRINGID_PKMNSXWOREOFF,
     STRINGID_PKMNRAISEDDEFALITTLE,
     STRINGID_PKMNRAISEDSPDEFALITTLE,
     STRINGID_THEWALLSHATTERED,
     STRINGID_PKMNSXPREVENTSYSZ,
     STRINGID_PKMNSXCUREDITSYPROBLEM,
     STRINGID_ATTACKERCANTESCAPE,
     STRINGID_PKMNOBTAINEDX,
     STRINGID_PKMNOBTAINEDX2,
     STRINGID_PKMNOBTAINEDXYOBTAINEDZ,
     STRINGID_BUTNOEFFECT,
     STRINGID_PKMNSXHADNOEFFECTONY,
     //these are also fir ered specific strings guess put others here
     STRINGID_OAKPLAYERWON, 
     STRINGID_OAKPLAYERLOST,
     STRINGID_PLAYERLOSTAGAINSTENEMYTRAINER,
     STRINGID_PLAYERPAIDPRIZEMONEY,
     STRINGID_PKMNTRANSFERREDSOMEONESPC,
     STRINGID_PKMNTRANSFERREDBILLSPC,
     STRINGID_PKMNBOXSOMEONESPCFULL,
     STRINGID_PKMNBOXBILLSPCFULL,
     STRINGID_POKEDUDEUSED,
     STRINGID_POKEFLUTECATCHY,
     STRINGID_POKEFLUTE,
     STRINGID_MONHEARINGFLUTEAWOKE,
     STRINGID_PKMNSXCALLEDDOWNHAIL,
     STRINGID_POKEMONBLOCKEDBALL,
     STRINGID_TRAINER2CLASS, //will need take ee as that combined class and name  to one string
    STRINGID_TRAINER2NAME,
    STRINGID_PLAYERWHITEDOUT,
    STRINGID_MONTOOSCAREDTOMOVE,
    STRINGID_GHOSTGETOUTGETOUT,
    STRINGID_SILPHSCOPEUNVEILED,
    STRINGID_GHOSTWASMAROWAK,
    STRINGID_TRAINER1MON1COMEBACK,
    STRINGID_TRAINER1WINTEXT,
    STRINGID_TRAINER1MON2COMEBACK,
    STRINGID_TRAINER1MON1AND2COMEBACK,
     //End fire red specific strings move gas etc above
     
     STRINGID_NEUTRALIZINGGASENTERS,
     STRINGID_NEUTRALIZINGGASOVER,
//new ids
     STRINGID_ENDUREDSTURDY,
     STRINGID_POWERHERB,
     STRINGID_HURTBYITEM,
     STRINGID_PSNBYITEM,
     STRINGID_BRNBYITEM,
     STRINGID_DEFABILITYIN,
     STRINGID_GRAVITYINTENSIFIED,
     STRINGID_TARGETIDENTIFIED,
     STRINGID_TARGETWOKEUP,
     STRINGID_PKMNSTOLEANDATEITEM,
     STRINGID_TAILWINDBLEW,
     STRINGID_PKMNWENTBACK,
     STRINGID_PKMNCANTUSEITEMSANYMORE,
     STRINGID_PKMNFLUNG,
     STRINGID_PKMNPREVENTEDFROMHEALING,
     STRINGID_PKMNSWITCHEDATKANDDEF,
     STRINGID_PKMNSABILITYSUPPRESSED,
     STRINGID_SHIELDEDFROMCRITICALHITS,
     STRINGID_SWITCHEDATKANDSPATK,
     STRINGID_SWITCHEDDEFANDSPDEF,
     STRINGID_PKMNACQUIREDABILITY,
     STRINGID_POISONSPIKESSCATTERED,
     STRINGID_PKMNSWITCHEDSTATCHANGES,
     STRINGID_PKMNSURROUNDEDWITHVEILOFWATER,
     STRINGID_PKMNLEVITATEDONELECTROMAGNETISM,
     STRINGID_PKMNTWISTEDDIMENSIONS,
     STRINGID_POINTEDSTONESFLOAT,
     STRINGID_CLOAKEDINMYSTICALMOONLIGHT,
     STRINGID_TRAPPEDBYSWIRLINGMAGMA,
     STRINGID_VANISHEDINSTANTLY,
     STRINGID_PROTECTEDTEAM,
     STRINGID_SHAREDITSGUARD,
     STRINGID_SHAREDITSPOWER,
     STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON,
     STRINGID_BECAMENIMBLE,
     STRINGID_HURLEDINTOTHEAIR,
     STRINGID_HELDITEMSLOSEEFFECTS,
     STRINGID_FELLSTRAIGHTDOWN,
     STRINGID_TRANSFORMEDINTOWATERTYPE,
     STRINGID_PKMNACQUIREDSIMPLE,
     STRINGID_EMPTYSTRING5,
     STRINGID_KINDOFFER,
     STRINGID_RESETSTARGETSSTATLEVELS,
     STRINGID_EMPTYSTRING6,
     STRINGID_ALLYSWITCHPOSITION,
     STRINGID_RESTORETARGETSHEALTH,
     STRINGID_TOOKPKMNINTOTHESKY,
     STRINGID_FREEDFROMSKYDROP,
     STRINGID_POSTPONETARGETMOVE,
     STRINGID_REFLECTTARGETSTYPE,
     STRINGID_TRANSFERHELDITEM,
     STRINGID_EMBARGOENDS,
     STRINGID_ELECTROMAGNETISM,
     STRINGID_BUFFERENDS,
     STRINGID_TELEKINESISENDS,
     STRINGID_TAILWINDENDS,
     STRINGID_LUCKYCHANTENDS,
     STRINGID_TRICKROOMENDS,
     STRINGID_WONDERROOMENDS,
     STRINGID_MAGICROOMENDS,
     STRINGID_MUDSPORTENDS,
     STRINGID_WATERSPORTENDS,
     STRINGID_GRAVITYENDS,
     STRINGID_AQUARINGHEAL,
     STRINGID_AURORAVEILENDS,
     STRINGID_ELECTRICTERRAINENDS,
     STRINGID_MISTYTERRAINENDS,
     STRINGID_PSYCHICTERRAINENDS,
     STRINGID_GRASSYTERRAINENDS,
     STRINGID_TARGETABILITYSTATRAISE,
     STRINGID_TARGETSSTATWASMAXEDOUT,
     STRINGID_ATTACKERABILITYSTATRAISE,
     STRINGID_POISONHEALHPUP,
     STRINGID_BADDREAMSDMG,
     STRINGID_MOLDBREAKERENTERS,
     STRINGID_TERAVOLTENTERS,
     STRINGID_TURBOBLAZEENTERS,
     STRINGID_SLOWSTARTENTERS,
     STRINGID_SLOWSTARTEND,
     STRINGID_SOLARPOWERHPDROP,
     STRINGID_AFTERMATHDMG,
     STRINGID_ANTICIPATIONACTIVATES,
     STRINGID_FOREWARNACTIVATES,
     STRINGID_ICEBODYHPGAIN,
     STRINGID_SNOWWARNINGHAIL,
     STRINGID_FRISKACTIVATES,
     STRINGID_UNNERVEENTERS,
     STRINGID_HARVESTBERRY,
     STRINGID_LASTABILITYRAISEDSTAT,
     STRINGID_MAGICBOUNCEACTIVATES,
     STRINGID_PROTEANTYPECHANGE,
     STRINGID_SYMBIOSISITEMPASS,
     STRINGID_STEALTHROCKDMG,
     STRINGID_TOXICSPIKESABSORBED,
     STRINGID_TOXICSPIKESPOISONED,
     STRINGID_STICKYWEBSWITCHIN,
     STRINGID_HEALINGWISHCAMETRUE,
     STRINGID_HEALINGWISHHEALED,
     STRINGID_LUNARDANCECAMETRUE,
     STRINGID_CUSEDBODYDISABLED,
     STRINGID_ATTACKERACQUIREDABILITY,
     STRINGID_TARGETABILITYSTATLOWER,
     STRINGID_TARGETSTATWONTGOHIGHER,
     STRINGID_PKMNMOVEBOUNCEDABILITY,
     STRINGID_IMPOSTERTRANSFORM,
     STRINGID_ASSAULTVESTDOESNTALLOW,
     STRINGID_GRAVITYPREVENTSUSAGE,
     STRINGID_HEALBLOCKPREVENTSUSAGE,
     STRINGID_NOTDONEYET,
     STRINGID_STICKYWEBUSED,
     STRINGID_QUASHSUCCESS,
    STRINGID_PKMNBLEWAWAYTOXICSPIKES,
    STRINGID_PKMNBLEWAWAYSTICKYWEB,
    STRINGID_PKMNBLEWAWAYSTEALTHROCK,
    STRINGID_IONDELUGEON,
    STRINGID_TOPSYTURVYSWITCHEDSTATS,
    STRINGID_TERRAINBECOMESMISTY,
    STRINGID_TERRAINBECOMESGRASSY,
    STRINGID_TERRAINBECOMESELECTRIC,
    STRINGID_TERRAINBECOMESPSYCHIC,
    STRINGID_TARGETELECTRIFIED,
    STRINGID_MEGAEVOREACTING,
    STRINGID_MEGAEVOEVOLVED,
    STRINGID_DRASTICALLY,
    STRINGID_SEVERELY,
    STRINGID_NOEFFECTONTARGET,
    STRINGID_BURSTINGFLAMESHIT,
    STRINGID_BESTOWITEMGIVING,
    STRINGID_THIRDTYPEADDED,
     STRINGID_FELLFORFEINT,
     STRINGID_POKEMONCANNOTUSEMOVE,
     STRINGID_COVEREDINPOWDER,
     STRINGID_POWDEREXPLODES,
     STRINGID_BELCHCANTSELECT,
     STRINGID_SPECTRALTHIEFSTEAL,
     STRINGID_GRAVITYGROUNDING,
     STRINGID_MISTYTERRAINPREVENTS,
     STRINGID_GRASSYTERRAINHEALS,
     STRINGID_ELECTRICTERRAINPREVENTS,
     STRINGID_PSYCHICTERRAINPREVENTS,
     STRINGID_SAFETYGOGGLESPROTECTED,
     STRINGID_FLOWERVEILPROTECTED,
     STRINGID_SWEETVEILPROTECTED,
     STRINGID_AROMAVEILPROTECTED,
     STRINGID_CELEBRATEMESSAGE,
     STRINGID_USEDINSTRUCTEDMOVE,
     STRINGID_THROATCHOPENDS,
     STRINGID_PKMNCANTUSEMOVETHROATCHOP,
     STRINGID_LASERFOCUS,
     STRINGID_GEMACTIVATES,
     STRINGID_BERRYDMGREDUCES,
     STRINGID_TARGETATEITEM,
     STRINGID_AIRBALLOONFLOAT,
     STRINGID_AIRBALLOONPOP,
     STRINGID_INCINERATEBURN,
     STRINGID_BUGBITE,
     STRINGID_ILLUSIONWOREOFF,
     STRINGID_ATTACKERCUREDTARGETSTATUS,
     STRINGID_ATTACKERLOSTTYPE,
     STRINGID_HEALERCURE,
     STRINGID_SCRIPTINGABILITYSTATRAISE,
     STRINGID_RECEIVERABILITYTAKEOVER,
     STRINGID_PKNMABSORBINGPOWER,
     STRINGID_NOONEWILLBEABLETORUNAWAY,
     STRINGID_DESTINYKNOTACTIVATES,
     STRINGID_CLOAKEDINAFREEZINGLIGHT,
     STRINGID_STATWASNOTLOWERED,
     STRINGID_FERVENTWISHREACHED,
     STRINGID_AIRLOCKACTIVATES,
     STRINGID_PRESSUREENTERS,
     STRINGID_DARKAURAENTERS,
     STRINGID_FAIRYAURAENTERS,
     STRINGID_AURABREAKENTERS,
     STRINGID_COMATOSEENTERS,
     STRINGID_SCREENCLEANERENTERS,
     STRINGID_FETCHEDPOKEBALL,
     STRINGID_BATTLERABILITYRAISEDSTAT,
     STRINGID_ASANDSTORMKICKEDUP,
     STRINGID_PKMNSWILLPERISHIN3TURNS,
     STRINGID_ABILITYRAISEDSTATDRASTICALLY,
     STRINGID_AURAFLAREDTOLIFE,
     STRINGID_ASONEENTERS,
     STRINGID_CURIOUSMEDICINEENTERS,
     STRINGID_CANACTFASTERTHANKSTO,
     STRINGID_MICLEBERRYACTIVATES,
     STRINGID_PKMNSHOOKOFFTHETAUNT,
     STRINGID_PKMNGOTOVERITSINFATUATION,
     STRINGID_ITEMCANNOTBEREMOVED,
     STRINGID_STICKYBARBTRANSFER,
     STRINGID_PKMNBURNHEALED,
     STRINGID_REDCARDACTIVATE,
     STRINGID_EJECTBUTTONACTIVATE,
     STRINGID_ATKGOTOVERINFATUATION,
     STRINGID_TORMENTEDNOMORE,
     STRINGID_HEALBLOCKEDNOMORE,
     STRINGID_ATTACKERBECAMEFULLYCHARGED,
     STRINGID_ATTACKERBECAMEASHSPECIES,
     STRINGID_EXTREMELYHARSHSUNLIGHT,
     STRINGID_EXTREMESUNLIGHTFADED,
     STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,
     STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED,
     STRINGID_HEAVYRAIN,
     STRINGID_HEAVYRAINLIFTED,
     STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,
     STRINGID_NORELIEFROMHEAVYRAIN,
     STRINGID_MYSTERIOUSAIRCURRENT,
     STRINGID_STRONGWINDSDISSIPATED,
     STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
     STRINGID_ATTACKWEAKENEDBYSTRONGWINDS,
     STRINGID_STUFFCHEEKSCANTSELECT,
     STRINGID_PKMNREVERTEDTOPRIMAL,
     STRINGID_BUTPOKEMONCANTUSETHEMOVE,
     STRINGID_BUTHOOPACANTUSEIT,
     STRINGID_BROKETHROUGHPROTECTION,
     STRINGID_ABILITYALLOWSONLYMOVE,
     STRINGID_SWAPPEDABILITIES,
     STRINGID_PASTELVEILPROTECTED,
     STRINGID_PASTELVEILENTERS,
     STRINGID_BATTLERTYPECHANGEDTO,
     STRINGID_BOTHCANNOLONGERESCAPE,
     STRINGID_CANTESCAPEDUETOUSEDMOVE,
     STRINGID_PKMNBECAMEWEAKERTOFIRE,
     STRINGID_ABOUTTOUSEPOLTERGEIST,
     STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE,
     STRINGID_TARGETTOOHEAVY,	//believe these two are for sky drop
     STRINGID_PKMNTOOKTARGETHIGH,
     //think last default string not last but most are above
     //a few additions below in the custom stuff
     //delte expansion additions in below 
     //make custom strings
     //and bring ee stuff in here
     STRINGID_INFESTATION,
     STRINGID_PKMNHURTBYFREEZE,
     STRINGID_CUPIDSARROWSTRUCK,
     STRINGID_PKMNALREADYFROZEN,
     STRINGID_SNAPTRAP, //appears unused
     STRINGID_PKMNSTOPPEDROOSTING, //TEXT for when flying is no longer vulnerable to ground 
     STRINGID_CONFIRMFORGETMOVE, //TEXT for confirming move forget
     STRINGID_TERRAINBECOMESFIRE,
     STRINGID_TERRAINBECOMESWATER,
     STRINGID_TERRAINBECOMESDEEPWATER,	//attempt to use as different water terrain for surfing large body of water, prob need to be map specific
     STRINGID_CRASHEDTOTHEGROUND,
     STRINGID_DEFEATISTACTIVATED,
     STRINGID_PKMNHURTBYFROSTBITE,	//continued dot damage if not thawed/ice cured - Already in table
     STRINGID_IRONWILL_ATKCANCEL,
     STRINGID_STEALTHROCKABROSBED,
     STRINGID_PICKUP_ITEM,
     STRINGID_TIGER_MOM_ACTIVATES,
     STRINGID_DEFROST_POKEMON,
     STRINGID_CORRUPTIONENTERS,
     STRINGID_BANDITENTERS,
     STRINGID_ANTICIPATE_EXPLOSION,
     STRINGID_ANTICIPATE_OHKO,
     STRINGID_ANTICIPATE_DEFAULT,
     STRINGID_SPITE_BADLUCK,
     STRINGID_SPITE_TOTAL_LOSS,
     STRINGID_PKMNSPOISONWORSENED,		//reapply mechanic, its meant to change poison to toxic poison when target already poisened.
     STRINGID_STENCHENTERS,		
     STRINGID_STENCHENDS,	
     STRINGID_WELLRESTED,
     STRINGID_PKMNHURTSWITH2,
     STRINGID_STICKYHOLDABSORBEDITEM,
     STRINGID_EMPATHIC_CURSE_ACTIVATES,
     STRINGID_ATTACKER_STURDY,
     STRINGID_TARGETSXWHIPPEDUPSANDSTORM,
     STRINGID_ATTACKER_ABILITYHURTS_TARGET,
     STRINGID_PKMNINFESTED,
     STRINGID_PKMNPANICKED,
     STRINGID_ABILITYNULLIFYTYPEDAMAGE,
     STRINGID_CAUGHTMONDROPPEDITEM,
     STRINGID_MONROOSTING,
     STRINGID_ATK_RAGEBUILDING,
     STRINGID_ATK_RAGEABATED,
     STRINGID_BIND_NO_PP,
     STRINGID_FEMME_FATALE,
     STRINGID_ABILITY_LOSTRESOLVE,
     STRINGID_AURA_OF_LIGHT_AWOKE,
     STRINGID_PKMNMOVESEALEDNOMORE,   //uxie inthrall sealed knowledge of move
     STRINGID_PKMNMOVESEALED,     //using inthralled move
     STRINGID_ATEBERRY, //for belch
     STRINGID_PHOENIX_CLEANSE,
     STRINGID_PLAYER_FOREWARN,
     STRINGID_ENEMY_FOREAWRN,
     STRINGID_PLAYER_ALERT,
     SRINGID_ENEMY_ALERT,
     STRINGID_ANTICIPATE_STRONG_MOVE,
     STRINGID_FORECAST_BLIZZARD,
     STRINGID_FORECAST_DUST_STORM,
     STRINGID_FORECAST_HEATWAVE,
     STRINGID_FORECAST_TORRENTIAL_RAIN,
     STRINGID_FORECAST_SANDSTORM, //for predicted weather /2nd weather effects
     STRINGID_FORECAST_HAIL,
     STRINGID_FORECAST_RAIN,
     STRINGID_FORECAST_SUNNY,
     STRINGID_FORECAST_PREDICTION,
     STRINGID_RAIN,
     STRINGID_SUN,
     STRINGID_SAND,
     STRINGID_HAIL,
     STRINGID_STATWENTBACKDOWN,  //mostly used for sky attack but could be for other move effects that I want to drop stats back after raising them
     STRINGID_CELEBRATE,
     STRINGID_ANTICIPATE_SOME_MOVE, //new logic for more info from anticipate
     STRINGID_PKMNWOKEUPREFRESHED, //is already in string table, just not at end
     STRINGID_JUDGMENT,
     STRINGID_GROUND_NULLIFY,
     STRINGID_NOE_FLIGHT,
     STRINGID_WONDER_GUARD_ENTERS,
     STRINGID_WONDER_GUARD_ENDS,
     STRINGID_DEF_RAGEABATED,
     STRINGID_IMMUTABLEWIND_ENTERS,
     STRINGID_IMMUTABLEWIND_ENDS,
     STRINGID_ITEMTOBAG,
     STRINGID_DAMP_PREVENTS_AFTERMATH,
     STRINGID_CUPIDSARROWSTRUCK_BOTH,
     STRINGID_ATK_CUTECHARM,
     STRINGID_PKMNFROSTBITTEN,
     STRINGID_INVERSIONTRANSFORM,
     STRINGID_BATTLERABILITYSTAT_INCREASE_ENDS, //stat increase ended
     STRINGID_SWITCH_LOCK_ENDS,
     STRINGID_REFLECT_INTIMIDATE,
     STRINGID_DARKTYPE_INTIMIDATE_RESIST,
     STRINGID_CHANGE_ABILITY_TO,
     STRINGID_HEAT_TRANCE_HPUP, //scovillain ability
     STIRNGID_SPIKESABSORBED,
     STRINGID_CONSUMED_HAZARD, //requires use of string copy to set name of hazard to stringvar2 in each script
     STRINGID_PKMNBLEWAWAYSHARPSTEEL,
     STRINGID_SHARPSTEELFLOATS,
     STRINGID_SHARPSTEEL_ABSORBED,
     STRINGID_SHARPSTEELDMG,
     STRINGID_RAGINGBULL_BREAKSTHROUGH,   //message for raging bull going through protect
     STRINGID_FORCEDTOSURFACE,
     STRINGID_TAKECAUGHTMONFROMPC,
     STRINGID_MOONLIGHT_SHINING_BRIGHT, //WEATHER START
     STRINGID_MOONLIGHT_SHINES, //weather continues
     STRINGID_MOONLIGHTFADED, //weather ends
     STRINGID_PKMNSXINTENSIFIEDMOONLIGHT,
     STRINGID_ACIDRAIN_FALLS,
     STRINGID_HURTBYRAIN,
     STRINGID_TARGETISGETTINGSERIOUS,
     STRINGID_TARGETCHANGEDMODE,
     STRINGID_BATTLER_ON_A_ROLL, //fixation string for flame wheel
     STRINGID_PKMNDROPPEDTEMP,
     STRINGID_PKMNSWARMED,
     STRINGID_PKMNCAMETOITSSENSES,
     STRINGID_PKMNRETURNEDTOAIR,

    //new Expansion stuff - fine where things split just want post gen stuff
    STRINGID_TRAINER1LOSETEXT,
    STRINGID_PKMNGAINEDEXP,
    STRINGID_PKMNGREWTOLV,
    STRINGID_PKMNLEARNEDMOVE,
    STRINGID_TRYTOLEARNMOVE1,
    STRINGID_TRYTOLEARNMOVE2,
    STRINGID_TRYTOLEARNMOVE3,
    STRINGID_PKMNFORGOTMOVE,
    STRINGID_STOPLEARNINGMOVE,
    STRINGID_DIDNOTLEARNMOVE,
    STRINGID_PKMNLEARNEDMOVE2,
    STRINGID_ATTACKMISSED,
    STRINGID_PKMNPROTECTEDITSELF,
    STRINGID_STATSWONTINCREASE2,
    STRINGID_AVOIDEDDAMAGE,
    STRINGID_ITDOESNTAFFECT,
    STRINGID_BATTLERFAINTED,
    STRINGID_PLAYERGOTMONEY,
    STRINGID_PLAYERWHITEOUT,
    STRINGID_PLAYERWHITEOUT2_WILD,
    STRINGID_PLAYERWHITEOUT2_TRAINER,
    STRINGID_PLAYERWHITEOUT3,
    STRINGID_PREVENTSESCAPE,
    STRINGID_HITXTIMES,
    STRINGID_PKMNFELLASLEEP,
    STRINGID_PKMNMADESLEEP,
    STRINGID_PKMNALREADYASLEEP,
    STRINGID_PKMNALREADYASLEEP2,
    STRINGID_PKMNWASPOISONED,
    STRINGID_PKMNPOISONEDBY,
    STRINGID_PKMNHURTBYPOISON,
    STRINGID_PKMNALREADYPOISONED,
    STRINGID_PKMNBADLYPOISONED,
    STRINGID_PKMNENERGYDRAINED,
    STRINGID_PKMNWASBURNED,
    STRINGID_PKMNBURNEDBY,
    STRINGID_PKMNHURTBYBURN,
    STRINGID_PKMNWASFROZEN,
    STRINGID_PKMNFROZENBY,
    STRINGID_PKMNISFROZEN,
    STRINGID_PKMNWASDEFROSTED,
    STRINGID_PKMNWASDEFROSTED2,
    STRINGID_PKMNWASDEFROSTEDBY,
    STRINGID_PKMNWASPARALYZED,
    STRINGID_PKMNWASPARALYZEDBY,
    STRINGID_PKMNISPARALYZED,
    STRINGID_PKMNISALREADYPARALYZED,
    STRINGID_PKMNHEALEDPARALYSIS,
    STRINGID_STATSWONTINCREASE,
    STRINGID_STATSWONTDECREASE,
    STRINGID_PKMNISCONFUSED,
    STRINGID_PKMNHEALEDCONFUSION,
    STRINGID_PKMNWASCONFUSED,
    STRINGID_PKMNALREADYCONFUSED,
    STRINGID_PKMNFELLINLOVE,
    STRINGID_PKMNINLOVE,
    STRINGID_PKMNIMMOBILIZEDBYLOVE,
    STRINGID_PKMNCHANGEDTYPE,
    STRINGID_PKMNFLINCHED,
    STRINGID_PKMNREGAINEDHEALTH,
    STRINGID_PKMNHPFULL,
    STRINGID_PKMNRAISEDSPDEF,
    STRINGID_PKMNRAISEDDEF,
    STRINGID_PKMNCOVEREDBYVEIL,
    STRINGID_PKMNUSEDSAFEGUARD,
    STRINGID_PKMNSAFEGUARDEXPIRED,
    STRINGID_PKMNWENTTOSLEEP,
    STRINGID_PKMNSLEPTHEALTHY,
    STRINGID_PKMNWHIPPEDWHIRLWIND,
    STRINGID_PKMNTOOKSUNLIGHT,
    STRINGID_PKMNLOWEREDHEAD,
    STRINGID_PKMNISGLOWING,
    STRINGID_PKMNFLEWHIGH,
    STRINGID_PKMNDUGHOLE,
    STRINGID_PKMNSQUEEZEDBYBIND,
    STRINGID_PKMNTRAPPEDINVORTEX,
    STRINGID_PKMNWRAPPEDBY,
    STRINGID_PKMNCLAMPED,
    STRINGID_PKMNHURTBY,
    STRINGID_PKMNFREEDFROM,
    STRINGID_PKMNCRASHED,
    STRINGID_PKMNSHROUDEDINMIST,
    STRINGID_PKMNPROTECTEDBYMIST,
    STRINGID_PKMNGETTINGPUMPED,
    STRINGID_PKMNHITWITHRECOIL,
    STRINGID_PKMNPROTECTEDITSELF2,
    STRINGID_PKMNBUFFETEDBYSANDSTORM,
    STRINGID_PKMNPELTEDBYHAIL,
    STRINGID_PKMNSEEDED,
    STRINGID_PKMNEVADEDATTACK,
    STRINGID_PKMNSAPPEDBYLEECHSEED,
    STRINGID_PKMNFASTASLEEP,
    STRINGID_PKMNWOKEUP,
    STRINGID_PKMNUPROARKEPTAWAKE,
    STRINGID_PKMNWOKEUPINUPROAR,
    STRINGID_PKMNCAUSEDUPROAR,
    STRINGID_PKMNMAKINGUPROAR,
    STRINGID_PKMNCALMEDDOWN,
    STRINGID_PKMNCANTSLEEPINUPROAR,
    STRINGID_PKMNSTOCKPILED,
    STRINGID_PKMNCANTSLEEPINUPROAR2,
    STRINGID_UPROARKEPTPKMNAWAKE,
    STRINGID_PKMNSTAYEDAWAKEUSING,
    STRINGID_PKMNSTORINGENERGY,
    STRINGID_PKMNUNLEASHEDENERGY,
    STRINGID_PKMNFATIGUECONFUSION,
    STRINGID_PLAYERPICKEDUPMONEY,
    STRINGID_PKMNUNAFFECTED,
    STRINGID_PKMNTRANSFORMEDINTO,
    STRINGID_PKMNMADESUBSTITUTE,
    STRINGID_PKMNHASSUBSTITUTE,
    STRINGID_SUBSTITUTEDAMAGED,
    STRINGID_PKMNSUBSTITUTEFADED,
    STRINGID_PKMNMUSTRECHARGE,
    STRINGID_PKMNRAGEBUILDING,
    STRINGID_PKMNMOVEWASDISABLED,
    STRINGID_PKMNMOVEISDISABLED,
    STRINGID_PKMNMOVEDISABLEDNOMORE,
    STRINGID_PKMNGOTENCORE,
    STRINGID_PKMNGOTENCOREDMOVE,
    STRINGID_PKMNENCOREENDED,
    STRINGID_PKMNTOOKAIM,
    STRINGID_PKMNSKETCHEDMOVE,
    STRINGID_PKMNTRYINGTOTAKEFOE,
    STRINGID_PKMNTOOKFOE,
    STRINGID_PKMNREDUCEDPP,
    STRINGID_PKMNSTOLEITEM,
    STRINGID_TARGETCANTESCAPENOW,
    STRINGID_PKMNFELLINTONIGHTMARE,
    STRINGID_PKMNLOCKEDINNIGHTMARE,
    STRINGID_PKMNLAIDCURSE,
    STRINGID_PKMNAFFLICTEDBYCURSE,
    STRINGID_SPIKESSCATTERED,
    STRINGID_PKMNHURTBYSPIKES,
    STRINGID_PKMNIDENTIFIED,
    STRINGID_PKMNPERISHCOUNTFELL,
    STRINGID_PKMNBRACEDITSELF,
    STRINGID_PKMNENDUREDHIT,
    STRINGID_MAGNITUDESTRENGTH,
    STRINGID_PKMNCUTHPMAXEDATTACK,
    STRINGID_PKMNCOPIEDSTATCHANGES,
    STRINGID_PKMNGOTFREE,
    STRINGID_PKMNSHEDLEECHSEED,
    STRINGID_PKMNBLEWAWAYSPIKES,
    STRINGID_PKMNFLEDFROMBATTLE,
    STRINGID_PKMNFORESAWATTACK,
    STRINGID_PKMNTOOKATTACK,
    STRINGID_PKMNATTACK,
    STRINGID_PKMNCENTERATTENTION,
    STRINGID_PKMNCHARGINGPOWER,
    STRINGID_NATUREPOWERTURNEDINTO,
    STRINGID_PKMNSTATUSNORMAL,
    STRINGID_PKMNHASNOMOVESLEFT,
    STRINGID_PKMNSUBJECTEDTOTORMENT,
    STRINGID_PKMNCANTUSEMOVETORMENT,
    STRINGID_PKMNTIGHTENINGFOCUS,
    STRINGID_PKMNFELLFORTAUNT,
    STRINGID_PKMNCANTUSEMOVETAUNT,
    STRINGID_PKMNREADYTOHELP,
    STRINGID_PKMNSWITCHEDITEMS,
    STRINGID_PKMNCOPIEDFOE,
    STRINGID_PKMNWISHCAMETRUE,
    STRINGID_PKMNPLANTEDROOTS,
    STRINGID_PKMNABSORBEDNUTRIENTS,
    STRINGID_PKMNANCHOREDITSELF,
    STRINGID_PKMNWASMADEDROWSY,
    STRINGID_PKMNKNOCKEDOFF,
    STRINGID_PKMNSWAPPEDABILITIES,
    STRINGID_PKMNSEALEDOPPONENTMOVE,
    STRINGID_PKMNCANTUSEMOVESEALED,
    STRINGID_PKMNWANTSGRUDGE,
    STRINGID_PKMNLOSTPPGRUDGE,
    STRINGID_PKMNSHROUDEDITSELF,
    STRINGID_PKMNMOVEBOUNCED,
    STRINGID_PKMNWAITSFORTARGET,
    STRINGID_PKMNSNATCHEDMOVE,
    STRINGID_PKMNMADEITRAIN,
    STRINGID_PKMNPROTECTEDBY,
    STRINGID_PKMNPREVENTSUSAGE,
    STRINGID_PKMNRESTOREDHPUSING,
    STRINGID_PKMNCHANGEDTYPEWITH,
    STRINGID_PKMNPREVENTSROMANCEWITH,
    STRINGID_PKMNPREVENTSCONFUSIONWITH,
    STRINGID_PKMNRAISEDFIREPOWERWITH,
    STRINGID_PKMNANCHORSITSELFWITH,
    STRINGID_PKMNCUTSATTACKWITH,
    STRINGID_PKMNPREVENTSSTATLOSSWITH,
    STRINGID_PKMNHURTSWITH,
    STRINGID_PKMNTRACED,
    STRINGID_STATSHARPLY,
    STRINGID_STATROSE,
    STRINGID_STATHARSHLY,
    STRINGID_STATFELL,
    STRINGID_ATTACKERSSTATROSE,
    STRINGID_DEFENDERSSTATROSE,
    STRINGID_ATTACKERSSTATFELL,
    STRINGID_DEFENDERSSTATFELL,
    STRINGID_CRITICALHIT,
    STRINGID_ONEHITKO,
    STRINGID_123POOF,
    STRINGID_ANDELLIPSIS,
    STRINGID_NOTVERYEFFECTIVE,
    STRINGID_SUPEREFFECTIVE,
    STRINGID_GOTAWAYSAFELY,
    STRINGID_WILDPKMNFLED,
    STRINGID_NORUNNINGFROMTRAINERS,
    STRINGID_CANTESCAPE,
    STRINGID_DONTLEAVEBIRCH,
    STRINGID_BUTNOTHINGHAPPENED,
    STRINGID_BUTITFAILED,
    STRINGID_ITHURTCONFUSION,
    STRINGID_STARTEDTORAIN,
    STRINGID_DOWNPOURSTARTED,
    STRINGID_RAINCONTINUES,
    STRINGID_DOWNPOURCONTINUES,
    STRINGID_RAINSTOPPED,
    STRINGID_SANDSTORMBREWED,
    STRINGID_SANDSTORMRAGES,
    STRINGID_SANDSTORMSUBSIDED,
    STRINGID_SUNLIGHTGOTBRIGHT,
    STRINGID_SUNLIGHTSTRONG,
    STRINGID_SUNLIGHTFADED,
    STRINGID_STARTEDHAIL,
    STRINGID_HAILCONTINUES,
    STRINGID_HAILSTOPPED,
    STRINGID_STATCHANGESGONE,
    STRINGID_COINSSCATTERED,
    STRINGID_TOOWEAKFORSUBSTITUTE,
    STRINGID_SHAREDPAIN,
    STRINGID_BELLCHIMED,
    STRINGID_FAINTINTHREE,
    STRINGID_NOPPLEFT,
    STRINGID_BUTNOPPLEFT,
    STRINGID_PLAYERUSEDITEM,
    STRINGID_WALLYUSEDITEM,
    STRINGID_TRAINERBLOCKEDBALL,
    STRINGID_DONTBEATHIEF,
    STRINGID_ITDODGEDBALL,
    STRINGID_YOUMISSEDPKMN,
    STRINGID_PKMNBROKEFREE,
    STRINGID_ITAPPEAREDCAUGHT,
    STRINGID_AARGHALMOSTHADIT,
    STRINGID_SHOOTSOCLOSE,
    STRINGID_GOTCHAPKMNCAUGHTPLAYER,
    STRINGID_GOTCHAPKMNCAUGHTWALLY,
    STRINGID_GIVENICKNAMECAPTURED,
    STRINGID_PKMNSENTTOPC,
    STRINGID_PKMNDATAADDEDTODEX,
    STRINGID_ITISRAINING,
    STRINGID_SANDSTORMISRAGING,
    STRINGID_CANTESCAPE2,
    STRINGID_PKMNIGNORESASLEEP,
    STRINGID_PKMNIGNOREDORDERS,
    STRINGID_PKMNBEGANTONAP,
    STRINGID_PKMNLOAFING,
    STRINGID_PKMNWONTOBEY,
    STRINGID_PKMNTURNEDAWAY,
    STRINGID_PKMNPRETENDNOTNOTICE,
    STRINGID_ENEMYABOUTTOSWITCHPKMN,
    STRINGID_CREPTCLOSER,
    STRINGID_CANTGETCLOSER,
    STRINGID_PKMNWATCHINGCAREFULLY,
    STRINGID_PKMNCURIOUSABOUTX,
    STRINGID_PKMNENTHRALLEDBYX,
    STRINGID_PKMNIGNOREDX,
    STRINGID_THREWPOKEBLOCKATPKMN,
    STRINGID_OUTOFSAFARIBALLS,
    STRINGID_PKMNSITEMCUREDPARALYSIS,
    STRINGID_PKMNSITEMCUREDPOISON,
    STRINGID_PKMNSITEMHEALEDBURN,
    STRINGID_PKMNSITEMDEFROSTEDIT,
    STRINGID_PKMNSITEMWOKEIT,
    STRINGID_PKMNSITEMSNAPPEDOUT,
    STRINGID_PKMNSITEMCUREDPROBLEM,
    STRINGID_PKMNSITEMRESTOREDHEALTH,
    STRINGID_PKMNSITEMRESTOREDPP,
    STRINGID_PKMNSITEMRESTOREDSTATUS,
    STRINGID_PKMNSITEMRESTOREDHPALITTLE,
    STRINGID_ITEMALLOWSONLYYMOVE,
    STRINGID_PKMNHUNGONWITHX,
    STRINGID_EMPTYSTRING3,
    STRINGID_PKMNSXBLOCKSY,
    STRINGID_PKMNSXRESTOREDHPALITTLE2,
    STRINGID_PKMNSXWHIPPEDUPSANDSTORM,
    STRINGID_PKMNSXPREVENTSYLOSS,
    STRINGID_PKMNSXINFATUATEDY,
    STRINGID_PKMNSXMADEYINEFFECTIVE,
    STRINGID_PKMNSXCUREDYPROBLEM,
    STRINGID_ITSUCKEDLIQUIDOOZE,
    STRINGID_PKMNTRANSFORMED,
    STRINGID_ELECTRICITYWEAKENED,
    STRINGID_FIREWEAKENED,
    STRINGID_PKMNHIDUNDERWATER,
    STRINGID_PKMNSPRANGUP,
    STRINGID_HMMOVESCANTBEFORGOTTEN,
    STRINGID_XFOUNDONEY,
    STRINGID_PLAYERDEFEATEDTRAINER1,
    STRINGID_SOOTHINGAROMA,
    STRINGID_ITEMSCANTBEUSEDNOW,
    STRINGID_USINGITEMSTATOFPKMNROSE,
    STRINGID_USINGITEMSTATOFPKMNFELL,
    STRINGID_PKMNUSEDXTOGETPUMPED,
    STRINGID_PKMNSXMADEYUSELESS,
    STRINGID_PKMNTRAPPEDBYSANDTOMB,
    STRINGID_EMPTYSTRING4,
    STRINGID_ABOOSTED,
    STRINGID_PKMNSXINTENSIFIEDSUN,
    STRINGID_PKMNMAKESGROUNDMISS,
    STRINGID_YOUTHROWABALLNOWRIGHT,
    STRINGID_PKMNSXTOOKATTACK,
    STRINGID_PKMNCHOSEXASDESTINY,
    STRINGID_PKMNLOSTFOCUS,
    STRINGID_USENEXTPKMN,
    STRINGID_PKMNFLEDUSINGITS,
    STRINGID_PKMNFLEDUSING,
    STRINGID_PKMNWASDRAGGEDOUT,
    STRINGID_PKMNSITEMNORMALIZEDSTATUS,
    STRINGID_TRAINER1USEDITEM,
    STRINGID_BOXISFULL,
    STRINGID_PKMNAVOIDEDATTACK,
    STRINGID_PKMNSXMADEITINEFFECTIVE,
    STRINGID_PKMNSXPREVENTSFLINCHING,
    STRINGID_PKMNALREADYHASBURN,
    STRINGID_STATSWONTDECREASE2,
    STRINGID_PKMNSXBLOCKSY2,
    STRINGID_PKMNSXWOREOFF,
    STRINGID_THEWALLSHATTERED,
    STRINGID_PKMNSXCUREDITSYPROBLEM,
    STRINGID_ATTACKERCANTESCAPE,
    STRINGID_PKMNOBTAINEDX,
    STRINGID_PKMNOBTAINEDX2,
    STRINGID_PKMNOBTAINEDXYOBTAINEDZ,
    STRINGID_BUTNOEFFECT,
    STRINGID_TWOENEMIESDEFEATED,
    STRINGID_TRAINER2LOSETEXT,
    STRINGID_PKMNINCAPABLEOFPOWER,
    STRINGID_GLINTAPPEARSINEYE,
    STRINGID_PKMNGETTINGINTOPOSITION,
    STRINGID_PKMNBEGANGROWLINGDEEPLY,
    STRINGID_PKMNEAGERFORMORE,
    STRINGID_DEFEATEDOPPONENTBYREFEREE,
    STRINGID_LOSTTOOPPONENTBYREFEREE,
    STRINGID_TIEDOPPONENTBYREFEREE,
    STRINGID_QUESTIONFORFEITMATCH,
    STRINGID_FORFEITEDMATCH,
    STRINGID_PKMNTRANSFERREDSOMEONESPC,
    STRINGID_PKMNTRANSFERREDLANETTESPC,
    STRINGID_PKMNBOXSOMEONESPCFULL,
    STRINGID_PKMNBOXLANETTESPCFULL,
    STRINGID_TRAINER1WINTEXT,
    STRINGID_TRAINER2WINTEXT,
    STRINGID_ENDUREDSTURDY,
    STRINGID_POWERHERB,
    STRINGID_HURTBYITEM,
    STRINGID_PSNBYITEM,
    STRINGID_BRNBYITEM,
    STRINGID_DEFABILITYIN,
    STRINGID_GRAVITYINTENSIFIED,
    STRINGID_TARGETIDENTIFIED,
    STRINGID_TARGETWOKEUP,
    STRINGID_PKMNSTOLEANDATEITEM,
    STRINGID_TAILWINDBLEW,
    STRINGID_PKMNWENTBACK,
    STRINGID_PKMNCANTUSEITEMSANYMORE,
    STRINGID_PKMNFLUNG,
    STRINGID_PKMNPREVENTEDFROMHEALING,
    STRINGID_PKMNSWITCHEDATKANDDEF,
    STRINGID_PKMNSABILITYSUPPRESSED,
    STRINGID_SHIELDEDFROMCRITICALHITS,
    STRINGID_SWITCHEDATKANDSPATK,
    STRINGID_SWITCHEDDEFANDSPDEF,
    STRINGID_PKMNACQUIREDABILITY,
    STRINGID_POISONSPIKESSCATTERED,
    STRINGID_PKMNSWITCHEDSTATCHANGES,
    STRINGID_PKMNSURROUNDEDWITHVEILOFWATER,
    STRINGID_PKMNLEVITATEDONELECTROMAGNETISM,
    STRINGID_PKMNTWISTEDDIMENSIONS,
    STRINGID_POINTEDSTONESFLOAT,
    STRINGID_CLOAKEDINMYSTICALMOONLIGHT,
    STRINGID_TRAPPEDBYSWIRLINGMAGMA,
    STRINGID_VANISHEDINSTANTLY,
    STRINGID_PROTECTEDTEAM,
    STRINGID_SHAREDITSGUARD,
    STRINGID_SHAREDITSPOWER,
    STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON,
    STRINGID_BECAMENIMBLE,
    STRINGID_HURLEDINTOTHEAIR,
    STRINGID_HELDITEMSLOSEEFFECTS,
    STRINGID_FELLSTRAIGHTDOWN,
    STRINGID_TARGETCHANGEDTYPE,
    STRINGID_PKMNACQUIREDSIMPLE,
    STRINGID_KINDOFFER,
    STRINGID_RESETSTARGETSSTATLEVELS,
    STRINGID_ALLYSWITCHPOSITION,
    STRINGID_RESTORETARGETSHEALTH,
    STRINGID_TOOKPJMNINTOTHESKY,
    STRINGID_FREEDFROMSKYDROP,
    STRINGID_POSTPONETARGETMOVE,
    STRINGID_REFLECTTARGETSTYPE,
    STRINGID_TRANSFERHELDITEM,
    STRINGID_EMBARGOENDS,
    STRINGID_ELECTROMAGNETISM,
    STRINGID_BUFFERENDS,
    STRINGID_TELEKINESISENDS,
    STRINGID_TAILWINDENDS,
    STRINGID_LUCKYCHANTENDS,
    STRINGID_TRICKROOMENDS,
    STRINGID_WONDERROOMENDS,
    STRINGID_MAGICROOMENDS,
    STRINGID_MUDSPORTENDS,
    STRINGID_WATERSPORTENDS,
    STRINGID_GRAVITYENDS,
    STRINGID_AQUARINGHEAL,
    STRINGID_ELECTRICTERRAINENDS,
    STRINGID_MISTYTERRAINENDS,
    STRINGID_PSYCHICTERRAINENDS,
    STRINGID_GRASSYTERRAINENDS,
    STRINGID_TARGETABILITYSTATRAISE,
    STRINGID_TARGETSSTATWASMAXEDOUT,
    STRINGID_ATTACKERABILITYSTATRAISE,
    STRINGID_POISONHEALHPUP,
    STRINGID_BADDREAMSDMG,
    STRINGID_MOLDBREAKERENTERS,
    STRINGID_TERAVOLTENTERS,
    STRINGID_TURBOBLAZEENTERS,
    STRINGID_SLOWSTARTENTERS,
    STRINGID_SLOWSTARTEND,
    STRINGID_SOLARPOWERHPDROP,
    STRINGID_AFTERMATHDMG,
    STRINGID_ANTICIPATIONACTIVATES,
    STRINGID_FOREWARNACTIVATES,
    STRINGID_ICEBODYHPGAIN,
    STRINGID_SNOWWARNINGHAIL,
    STRINGID_FRISKACTIVATES,
    STRINGID_UNNERVEENTERS,
    STRINGID_HARVESTBERRY,
    STRINGID_MAGICBOUNCEACTIVATES,
    STRINGID_PROTEANTYPECHANGE,
    STRINGID_SYMBIOSISITEMPASS,
    STRINGID_STEALTHROCKDMG,
    STRINGID_TOXICSPIKESABSORBED,
    STRINGID_TOXICSPIKESPOISONED,
    STRINGID_TOXICSPIKESBADLYPOISONED,
    STRINGID_STICKYWEBSWITCHIN,
    STRINGID_HEALINGWISHCAMETRUE,
    STRINGID_HEALINGWISHHEALED,
    STRINGID_LUNARDANCECAMETRUE,
    STRINGID_CURSEDBODYDISABLED,
    STRINGID_ATTACKERACQUIREDABILITY,
    STRINGID_TARGETABILITYSTATLOWER,
    STRINGID_TARGETSTATWONTGOHIGHER,
    STRINGID_PKMNMOVEBOUNCEDABILITY,
    STRINGID_IMPOSTERTRANSFORM,
    STRINGID_ASSAULTVESTDOESNTALLOW,
    STRINGID_GRAVITYPREVENTSUSAGE,
    STRINGID_HEALBLOCKPREVENTSUSAGE,
    STRINGID_NOTDONEYET,
    STRINGID_STICKYWEBUSED,
    STRINGID_QUASHSUCCESS,
    STRINGID_PKMNBLEWAWAYTOXICSPIKES,
    STRINGID_PKMNBLEWAWAYSTICKYWEB,
    STRINGID_PKMNBLEWAWAYSTEALTHROCK,
    STRINGID_IONDELUGEON,
    STRINGID_TOPSYTURVYSWITCHEDSTATS,
    STRINGID_TERRAINBECOMESMISTY,
    STRINGID_TERRAINBECOMESGRASSY,
    STRINGID_TERRAINBECOMESELECTRIC,
    STRINGID_TERRAINBECOMESPSYCHIC,
    STRINGID_TARGETELECTRIFIED,
    STRINGID_MEGAEVOREACTING,
    STRINGID_MEGAEVOEVOLVED,
    STRINGID_DRASTICALLY,
    STRINGID_SEVERELY,
    STRINGID_INFESTATION,
    STRINGID_NOEFFECTONTARGET,
    STRINGID_BURSTINGFLAMESHIT,
    STRINGID_BESTOWITEMGIVING,
    STRINGID_THIRDTYPEADDED,
    STRINGID_FELLFORFEINT,
    STRINGID_POKEMONCANNOTUSEMOVE,
    STRINGID_COVEREDINPOWDER,
    STRINGID_POWDEREXPLODES,
    STRINGID_BELCHCANTSELECT,
    STRINGID_SPECTRALTHIEFSTEAL,
    STRINGID_GRAVITYGROUNDING,
    STRINGID_MISTYTERRAINPREVENTS,
    STRINGID_GRASSYTERRAINHEALS,
    STRINGID_ELECTRICTERRAINPREVENTS,
    STRINGID_PSYCHICTERRAINPREVENTS,
    STRINGID_SAFETYGOGGLESPROTECTED,
    STRINGID_FLOWERVEILPROTECTED,
    STRINGID_SWEETVEILPROTECTED,
    STRINGID_AROMAVEILPROTECTED,
    STRINGID_CELEBRATEMESSAGE,
    STRINGID_USEDINSTRUCTEDMOVE,
    STRINGID_THROATCHOPENDS,
    STRINGID_PKMNCANTUSEMOVETHROATCHOP,
    STRINGID_LASERFOCUS,
    STRINGID_GEMACTIVATES,
    STRINGID_BERRYDMGREDUCES,
    STRINGID_AIRBALLOONFLOAT,
    STRINGID_AIRBALLOONPOP,
    STRINGID_INCINERATEBURN,
    STRINGID_BUGBITE,
    STRINGID_ILLUSIONWOREOFF,
    STRINGID_ATTACKERCUREDTARGETSTATUS,
    STRINGID_ATTACKERLOSTFIRETYPE,
    STRINGID_HEALERCURE,
    STRINGID_SCRIPTINGABILITYSTATRAISE,
    STRINGID_RECEIVERABILITYTAKEOVER,
    STRINGID_PKNMABSORBINGPOWER,
    STRINGID_NOONEWILLBEABLETORUNAWAY,
    STRINGID_DESTINYKNOTACTIVATES,
    STRINGID_CLOAKEDINAFREEZINGLIGHT,
    STRINGID_CLEARAMULETWONTLOWERSTATS,
    STRINGID_FERVENTWISHREACHED,
    STRINGID_AIRLOCKACTIVATES,
    STRINGID_PRESSUREENTERS,
    STRINGID_DARKAURAENTERS,
    STRINGID_FAIRYAURAENTERS,
    STRINGID_AURABREAKENTERS,
    STRINGID_COMATOSEENTERS,
    STRINGID_SCREENCLEANERENTERS,
    STRINGID_FETCHEDPOKEBALL,
    STRINGID_ASANDSTORMKICKEDUP,
    STRINGID_PKMNSWILLPERISHIN3TURNS,
    STRINGID_AURAFLAREDTOLIFE,
    STRINGID_ASONEENTERS,
    STRINGID_CURIOUSMEDICINEENTERS,
    STRINGID_CANACTFASTERTHANKSTO,
    STRINGID_MICLEBERRYACTIVATES,
    STRINGID_PKMNSHOOKOFFTHETAUNT,
    STRINGID_PKMNGOTOVERITSINFATUATION,
    STRINGID_ITEMCANNOTBEREMOVED,
    STRINGID_STICKYBARBTRANSFER,
    STRINGID_PKMNBURNHEALED,
    STRINGID_REDCARDACTIVATE,
    STRINGID_EJECTBUTTONACTIVATE,
    STRINGID_ATKGOTOVERINFATUATION,
    STRINGID_TORMENTEDNOMORE,
    STRINGID_HEALBLOCKEDNOMORE,
    STRINGID_ATTACKERBECAMEFULLYCHARGED,
    STRINGID_ATTACKERBECAMEASHSPECIES,
    STRINGID_EXTREMELYHARSHSUNLIGHT,
    STRINGID_EXTREMESUNLIGHTFADED,
    STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,
    STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED,
    STRINGID_HEAVYRAIN,
    STRINGID_HEAVYRAINLIFTED,
    STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,
    STRINGID_NORELIEFROMHEAVYRAIN,
    STRINGID_MYSTERIOUSAIRCURRENT,
    STRINGID_STRONGWINDSDISSIPATED,
    STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
    STRINGID_ATTACKWEAKENEDBSTRONGWINDS,
    STRINGID_STUFFCHEEKSCANTSELECT,
    STRINGID_PKMNREVERTEDTOPRIMAL,
    STRINGID_BUTPOKEMONCANTUSETHEMOVE,
    STRINGID_BUTHOOPACANTUSEIT,
    STRINGID_BROKETHROUGHPROTECTION,
    STRINGID_ABILITYALLOWSONLYMOVE,
    STRINGID_SWAPPEDABILITIES,
    STRINGID_PASTELVEILENTERS,
    STRINGID_BATTLERTYPECHANGEDTO,
    STRINGID_BOTHCANNOLONGERESCAPE,
    STRINGID_CANTESCAPEDUETOUSEDMOVE,
    STRINGID_PKMNBECAMEWEAKERTOFIRE,
    STRINGID_ABOUTTOUSEPOLTERGEIST,
    STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE,
    STRINGID_NEUTRALIZINGGASENTERS,
    STRINGID_NEUTRALIZINGGASOVER,
    STRINGID_TARGETTOOHEAVY,
    STRINGID_PKMNTOOKTARGETHIGH,
    STRINGID_PKMNINSNAPTRAP,
    STRINGID_METEORBEAMCHARGING,
    STRINGID_HEATUPBEAK,
    STRINGID_COURTCHANGE,
    STRINGID_ZPOWERSURROUNDS,
    STRINGID_ZMOVEUNLEASHED,
    STRINGID_ZMOVERESETSSTATS,
    STRINGID_ZMOVEALLSTATSUP,
    STRINGID_ZMOVEZBOOSTCRIT,
    STRINGID_ZMOVERESTOREHP,
    STRINGID_ZMOVESTATUP,
    STRINGID_ZMOVEHPTRAP,
    STRINGID_ATTACKEREXPELLEDTHEPOISON,
    STRINGID_ATTACKERSHOOKITSELFAWAKE,
    STRINGID_ATTACKERBROKETHROUGHPARALYSIS,
    STRINGID_ATTACKERHEALEDITSBURN,
    STRINGID_ATTACKERMELTEDTHEICE,
    STRINGID_TARGETTOUGHEDITOUT,
    STRINGID_ATTACKERLOSTELECTRICTYPE,
    STRINGID_ATTACKERSWITCHEDSTATWITHTARGET,
    STRINGID_BEINGHITCHARGEDPKMNWITHPOWER,
    STRINGID_SUNLIGHTACTIVATEDABILITY,
    STRINGID_STATWASHEIGHTENED,
    STRINGID_ELECTRICTERRAINACTIVATEDABILITY,
    STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT,
    STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN,
    STRINGID_PKMNSABILITYPREVENTSABILITY,
    STRINGID_PREPARESHELLTRAP,
    STRINGID_SHELLTRAPDIDNTWORK,
    STRINGID_SPIKESDISAPPEAREDFROMTEAM,
    STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM,
    STRINGID_STICKYWEBDISAPPEAREDFROMTEAM,
    STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM,
    STRINGID_COULDNTFULLYPROTECT,
    STRINGID_STOCKPILEDEFFECTWOREOFF,
    STRINGID_PKMNREVIVEDREADYTOFIGHT,
    STRINGID_ITEMRESTOREDSPECIESHEALTH,
    STRINGID_ITEMCUREDSPECIESSTATUS,
    STRINGID_ITEMRESTOREDSPECIESPP,
    STRINGID_THUNDERCAGETRAPPED,
    STRINGID_PKMNHURTBYFROSTBITE,
    STRINGID_PKMNGOTFROSTBITE,
    STRINGID_PKMNSITEMHEALEDFROSTBITE,
    STRINGID_ATTACKERHEALEDITSFROSTBITE,
    STRINGID_PKMNFROSTBITEHEALED,
    STRINGID_PKMNFROSTBITEHEALED2,
    STRINGID_PKMNFROSTBITEHEALEDBY,
    STRINGID_MIRRORHERBCOPIED,
    STRINGID_STARTEDSNOW,
    STRINGID_SNOWCONTINUES,
    STRINGID_SNOWSTOPPED,
    STRINGID_SNOWWARNINGSNOW,
    STRINGID_PKMNITEMMELTED,
    STRINGID_ULTRABURSTREACTING,
    STRINGID_ULTRABURSTCOMPLETED,
    STRINGID_TEAMGAINEDEXP,
    STRINGID_CURRENTMOVECANTSELECT,
    STRINGID_TARGETISBEINGSALTCURED,
    STRINGID_TARGETISHURTBYSALTCURE,
    STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP,
    STRINGID_SHARPSTEELFLOATS,
    STRINGID_SHARPSTEELDMG,
    STRINGID_PKMNBLEWAWAYSHARPSTEEL,
    STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM,
    STRINGID_TEAMTRAPPEDWITHVINES,
    STRINGID_PKMNHURTBYVINES,
    STRINGID_TEAMCAUGHTINVORTEX,
    STRINGID_PKMNHURTBYVORTEX,
    STRINGID_TEAMSURROUNDEDBYFIRE,
    STRINGID_PKMNBURNINGUP,
    STRINGID_TEAMSURROUNDEDBYROCKS,
    STRINGID_PKMNHURTBYROCKSTHROWN,
    STRINGID_MOVEBLOCKEDBYDYNAMAX,
    STRINGID_ZEROTOHEROTRANSFORMATION,
    STRINGID_THETWOMOVESBECOMEONE,
    STRINGID_ARAINBOWAPPEAREDONSIDE,
    STRINGID_THERAINBOWDISAPPEARED,
    STRINGID_WAITINGFORPARTNERSMOVE,
    STRINGID_SEAOFFIREENVELOPEDSIDE,
    STRINGID_HURTBYTHESEAOFFIRE,
    STRINGID_THESEAOFFIREDISAPPEARED,
    STRINGID_SWAMPENVELOPEDSIDE,
    STRINGID_THESWAMPDISAPPEARED,
    STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE,
    STRINGID_HOSPITALITYRESTORATION,
    STRINGID_ELECTROSHOTCHARGING,
    STRINGID_ITEMWASUSEDUP,
    STRINGID_ATTACKERLOSTITSTYPE,
    STRINGID_SHEDITSTAIL,
    STRINGID_CLOAKEDINAHARSHLIGHT,
    STRINGID_SUPERSWEETAROMAWAFTS,
    STRINGID_DIMENSIONSWERETWISTED,
    STRINGID_BIZARREARENACREATED,
    STRINGID_BIZARREAREACREATED,
    STRINGID_TIDYINGUPCOMPLETE,
    STRINGID_PKMNTERASTALLIZEDINTO,
    STRINGID_BOOSTERENERGYACTIVATES,
    STRINGID_FOG_ROLLED_IN, //vsonic
    STRINGID_FOGISDEEP,
    STRINGID_FOGLIFTED,
    STRINGID_PKMNMADESHELLGLEAM,
    STRINGID_FICKLEBEAMDOUBLED,
    STRINGID_COMMANDERACTIVATES,
    STRINGID_BATTERYCONSUMED, //charjabug charging viikavolt
    STRINGID_POKEFLUTECATCHY,
    STRINGID_POKEFLUTE,
    STRINGID_MONHEARINGFLUTEAWOKE,
    STRINGID_SUNLIGHTISHARSH,
    STRINGID_ITISHAILING,
    STRINGID_ITISSNOWING,
    STRINGID_ISCOVEREDWITHGRASS,
    STRINGID_MISTSWIRLSAROUND,
    STRINGID_ELECTRICCURRENTISRUNNING,
    STRINGID_SEEMSWEIRD,
    STRINGID_WAGGLINGAFINGER,
    STRINGID_BLOCKEDBYSLEEPCLAUSE,
    STRINGID_SUPEREFFECTIVETWOFOES,
    STRINGID_NOTVERYEFFECTIVETWOFOES,
    STRINGID_ITDOESNTAFFECTTWOFOES,
    STRINGID_SENDCAUGHTMONPARTYORBOX,
    STRINGID_PKMNSENTTOPCAFTERCATCH,
    STRINGID_PKMNDYNAMAXED,
    STRINGID_PKMNGIGANTAMAXED,
    STRINGID_TIMETODYNAMAX,
    STRINGID_TIMETOGIGANTAMAX,
    STRINGID_QUESTIONFORFEITBATTLE,
    STRINGID_POWERCONSTRUCTPRESENCEOFMANY,
    STRINGID_POWERCONSTRUCTTRANSFORM,
    STRINGID_ABILITYSHIELDPROTECTS,
    
    //end new Expansion stuff
    STRINGID_COUNT

};



/*#define BATTLESTRINGS_COUNT     STRINGID_COUNT - 1

#define BATTLESTRING_FRLG_TABLE_START STRINGID_COUNT


#define STRINGID_TRAINER2CLASS BATTLESTRING_FRLG_TABLE_START + 1 // cutoff point. was able to confirm this does properly define
#define STRINGID_TRAINER2NAME BATTLESTRING_FRLG_TABLE_START + 2
#define STRINGID_PLAYERWHITEDOUT BATTLESTRING_FRLG_TABLE_START + 3
#define STRINGID_MONTOOSCAREDTOMOVE BATTLESTRING_FRLG_TABLE_START + 4
#define STRINGID_GHOSTGETOUTGETOUT BATTLESTRING_FRLG_TABLE_START + 5
#define STRINGID_SILPHSCOPEUNVEILED BATTLESTRING_FRLG_TABLE_START + 6
#define STRINGID_GHOSTWASMAROWAK BATTLESTRING_FRLG_TABLE_START + 7
#define STRINGID_TRAINER1MON1COMEBACK BATTLESTRING_FRLG_TABLE_START + 8
#define STRINGID_TRAINER1WINTEXT BATTLESTRING_FRLG_TABLE_START + 9
#define STRINGID_TRAINER1MON2COMEBACK BATTLESTRING_FRLG_TABLE_START + 10
#define STRINGID_TRAINER1MON1AND2COMEBACK BATTLESTRING_FRLG_TABLE_START + 11

#define BATTLESTRINGS_TABLE_START  STRINGID_TRAINER1LOSETEXT */
//used increment website but realized still need to update string  count/keep stringcount so no point in changing list

#endif // GUARD_BATTLE_STRING_IDS_H
