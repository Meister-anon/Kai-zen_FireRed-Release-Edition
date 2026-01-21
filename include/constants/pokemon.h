#ifndef GUARD_CONSTANTS_POKEMON_H
#define GUARD_CONSTANTS_POKEMON_H

// For (Set|Get)(Box)?MonData
#define MON_DATA_PERSONALITY        0
#define MON_DATA_OT_ID              1
#define MON_DATA_NICKNAME           2
#define MON_DATA_LANGUAGE           3
#define MON_DATA_SHINY_CHECK        4
#define MON_DATA_SANITY_HAS_SPECIES 5
#define MON_DATA_SANITY_IS_EGG      6
#define MON_DATA_OT_NAME            7
#define MON_DATA_MARKINGS           8
#define MON_DATA_CHECKSUM           9
#define MON_DATA_ENCRYPT_SEPARATOR 10
#define MON_DATA_SPECIES           11
#define MON_DATA_HELD_ITEM         12
#define MON_DATA_MOVE1             13
#define MON_DATA_MOVE2             14
#define MON_DATA_MOVE3             15
#define MON_DATA_MOVE4             16
#define MON_DATA_PP1               17
#define MON_DATA_PP2               18
#define MON_DATA_PP3               19
#define MON_DATA_PP4               20
#define MON_DATA_PP_BONUSES        21
#define MON_DATA_COOL              22
#define MON_DATA_BEAUTY            23
#define MON_DATA_CUTE              24
#define MON_DATA_EXP               25
#define MON_DATA_HP_EV             26
#define MON_DATA_ATK_EV            27
#define MON_DATA_DEF_EV            28
#define MON_DATA_SPEED_EV          29
#define MON_DATA_SPATK_EV          30
#define MON_DATA_SPDEF_EV          31
#define MON_DATA_FRIENDSHIP        32
#define MON_DATA_SMART             33
#define MON_DATA_FROM_MOBILE_PC    34  //was pokerus, but cleared for mobile pc access setup
#define MON_DATA_MET_LOCATION      35
#define MON_DATA_MET_LEVEL         36
#define MON_DATA_MET_GAME          37
#define MON_DATA_POKEBALL          38
#define MON_DATA_HP_IV             39
#define MON_DATA_ATK_IV            40
#define MON_DATA_DEF_IV            41
#define MON_DATA_SPEED_IV          42
#define MON_DATA_SPATK_IV          43
#define MON_DATA_SPDEF_IV          44
#define MON_DATA_IS_EGG            45
#define MON_DATA_ABILITY_NUM       46
#define MON_DATA_TOUGH             47
//#define MON_DATA_SHEEN             48     //with how value is handled believe I can just remove  without needing to reorder without breaking anything
#define MON_DATA_OT_GENDER         49
#define MON_DATA_COOL_RIBBON       50
#define MON_DATA_BEAUTY_RIBBON     51
#define MON_DATA_CUTE_RIBBON       52
#define MON_DATA_SMART_RIBBON      53
#define MON_DATA_TOUGH_RIBBON      54
#define MON_DATA_STATUS            55
#define MON_DATA_LEVEL             56
#define MON_DATA_HP                57
#define MON_DATA_MAX_HP            58
#define MON_DATA_ATK               59
#define MON_DATA_DEF               60
#define MON_DATA_SPEED             61
#define MON_DATA_SPATK             62
#define MON_DATA_SPDEF             63
#define MON_DATA_MAIL              64
#define MON_DATA_SPECIES_OR_EGG    65 //replace species_2, seems use was identical so just auto replaced
#define MON_DATA_IVS               66
#define MON_DATA_CHAMPION_RIBBON   67
#define MON_DATA_WINNING_RIBBON    68
#define MON_DATA_VICTORY_RIBBON    69
#define MON_DATA_ARTIST_RIBBON     70
#define MON_DATA_EFFORT_RIBBON     71
#define MON_DATA_MARINE_RIBBON     72//removed here
#define MON_DATA_LAND_RIBBON       73
#define MON_DATA_SKY_RIBBON        74
#define MON_DATA_COUNTRY_RIBBON    75//to here
#define MON_DATA_NATIONAL_RIBBON   76
#define MON_DATA_EARTH_RIBBON      77//and this
#define MON_DATA_WORLD_RIBBON      78 //and this,  constants still remain but struct values are gone =6 values total
#define MON_DATA_FILLER            79
#define MON_DATA_EVENT_LEGAL       80
#define MON_DATA_KNOWN_MOVES       81
#define MON_DATA_RIBBON_COUNT      82
#define MON_DATA_RIBBONS           83
/*#define MON_DATA_ATK2              84 //FACEPALM the entire reason for the stat2 variants is to exclude the stupid deoxys logic I should have removed long ago
#define MON_DATA_DEF2              85
#define MON_DATA_SPEED2            86
#define MON_DATA_SPATK2            87
#define MON_DATA_SPDEF2            88*/
#define MON_DATA_HATCHED           89   //new value to keep track of egg hatch status - needed for summary screen to properly distinguise mon got via egg
#define MON_DATA_FORM_FLAG         90   //new value for helping evo into regional forms
#define MON_DATA_EVO_LEVEL         91 //new value store level mon evolves at, moslty for keeping relative evo consistent, becomes new floor value if non -zero
#define MON_DATA_NATURE            92 //REPLACED now for nature setting  //both for nuzlocke mode //store location fainted   - onhold for now
#define MON_DATA_BOX_HP            93   //when hp is 0, pass hp to box so doesn't heal, default val 1 but need change u16 so can store actual curr hp for pc access change
#define MON_DATA_EXP_SHARE_STATE   94 //revised modern exp share, allow setting from party menu
                                      //offshoot idea block exp gain setup same way as alt, use case more direct level control
                                      //decided roll into one field
#define MON_DATA_STATUS_SET_STATE    95   
#define MON_DATA_BLOCK_BOX_EXP_GAIN 96 //joke but boxmon value to block pc exp gain, decide also use for daycare, since daycare will set for move learn/egg move
#define MON_DATA_HIDDEN_POWER_TYPE 97
#define MON_DATA_USE_TAUGHT_ABILITY 98
#define MON_DATA_LEARNED_ABILITY_ID 99
#define MON_DATA_HIDE_EGG_SPECIES 100 //for option to not display egg species for special eggs received outside daycare
#define MON_DATA_PICKUP_COUNTER 101 //for individual pickup counter
#define MON_DATA_EVOLUTION_STATE 102 //set if mon can evolve or not on lvl up special lvl up evo graphic still plays if conditions met to evolve

#define TYPE_DEFINES
// Pokemon types	type order found in list_menu.c    actually is in graphics_file_rules.mk 
//list menu is the location of the icons on the graphic

// Pokémon types
enum __attribute__((packed)) Type
{
    TYPE_NONE = 0,
    TYPE_NORMAL = 1,
    TYPE_FIGHTING = 2,
    TYPE_FLYING = 3,
    TYPE_POISON = 4,
    TYPE_GROUND = 5,
    TYPE_ROCK = 6,
    TYPE_BUG = 7,
    TYPE_GHOST = 8,
    TYPE_STEEL = 9,
    TYPE_MYSTERY = 10,
    TYPE_FIRE = 11,
    TYPE_WATER = 12,
    TYPE_GRASS = 13,
    TYPE_ELECTRIC = 14,
    TYPE_PSYCHIC = 15,
    TYPE_ICE = 16,
    TYPE_DRAGON = 17,
    TYPE_DARK = 18,
    TYPE_FAIRY = 19,
    TYPE_WIND = 20,
    TYPE_SOUND = 21,
    TYPE_STELLAR = 22,
    NUMBER_OF_MON_TYPES
};

// Pokemon egg groups
#define EGG_GROUP_NONE 0
#define EGG_GROUP_MONSTER 1
#define EGG_GROUP_WATER_1 2
#define EGG_GROUP_BUG 3
#define EGG_GROUP_FLYING 4
#define EGG_GROUP_FIELD 5
#define EGG_GROUP_FAIRY 6
#define EGG_GROUP_GRASS 7
#define EGG_GROUP_HUMAN_LIKE 8
#define EGG_GROUP_WATER_3 9
#define EGG_GROUP_MINERAL 10
#define EGG_GROUP_AMORPHOUS 11
#define EGG_GROUP_WATER_2 12
#define EGG_GROUP_DITTO 13
#define EGG_GROUP_DRAGON 14
#define EGG_GROUP_UNDISCOVERED 15

#define EGG_GROUPS_PER_MON      2

// Pokemon natures
#define NATURE_HARDY    0 // Neutral
#define NATURE_LONELY   1 // +Atk -Def
#define NATURE_BRAVE    2 // +Atk -Speed
#define NATURE_ADAMANT  3 // +Atk -SpAtk
#define NATURE_NAUGHTY  4 // +Atk -SpDef
#define NATURE_BOLD     5 // +Def -Atk
#define NATURE_DOCILE   6 // Neutral
#define NATURE_RELAXED  7 // +Def -Speed
#define NATURE_IMPISH   8 // +Def -SpAtk
#define NATURE_LAX      9 // +Def -SpDef
#define NATURE_TIMID    10 // +Speed -Atk
#define NATURE_HASTY    11 // +Speed -Def
#define NATURE_SERIOUS  12 // Neutral
#define NATURE_JOLLY    13 // +Speed -SpAtk
#define NATURE_NAIVE    14 // +Speed - SpDef
#define NATURE_MODEST   15 // +SpAtk -Atk
#define NATURE_MILD     16 // +SpAtk -Def
#define NATURE_QUIET    17 // +SpAtk -Speed
#define NATURE_BASHFUL  18 // Neutral
#define NATURE_RASH     19 // +SpAtk -SpDef
#define NATURE_CALM     20 // +SpDef -Atk
#define NATURE_GENTLE   21 // +SpDef -Def
#define NATURE_SASSY    22 // +SpDef -Speed
#define NATURE_CAREFUL  23 // +SpDef -SpAtk
#define NATURE_QUIRKY   24 // Neutral
#define NUM_NATURES     25

#define NATURE_RANDOM            NUM_NATURES
#define NATURE_MAY_SYNCHRONIZE   NUM_NATURES + 1

// Pokemon Stats
// Pokémon Stats
enum __attribute__((packed)) Stat
{
    STAT_HP,
    STAT_ATK,
    STAT_DEF,
    STAT_SPEED,
    STAT_SPATK,
    STAT_SPDEF,
    NUM_STATS,
    STAT_ACC = NUM_STATS, // Only in battles.
    STAT_EVASION,         // Only in battles.
};

#define NUM_NATURE_STATS (NUM_STATS - 1) // excludes HP
#define NUM_BATTLE_STATS (NUM_STATS + 2) // includes Accuracy and Evasion

#define MIN_STAT_STAGE     0
#define DEFAULT_STAT_STAGE 6
#define MAX_STAT_STAGE    12

#define NUM_ABILITY_SLOTS (NUM_NORMAL_ABILITY_SLOTS + NUM_HIDDEN_ABILITY_SLOTS)
#define NUM_NORMAL_ABILITY_SLOTS 2
#define NUM_HIDDEN_ABILITY_SLOTS 2
#define ABILITY_SLOT_1 0
#define ABILITY_SLOT_2 1
#define HIDDEN_ABILITY_SLOT_1 0
#define HIDDEN_ABILITY_SLOT_2 1
#define ABILITYNUM_HIDDEN_ABILITY_START 2
#define ABILITYNUM_NORMAL_ABILITY_START 0

//trainer party abilityNum values, 
#define RANDOM_ABILITY			0
#define ABILITY_1				1
#define ABILITY_2				2
#define HIDDEN_ABILITY_1		3
#define HIDDEN_ABILITY_2		4

//IV Mask
#define MAX_IV_MASK 31

// Shiny odds - reworked now odds are 1/SHINY_ODDS, approx, not quite 2x boost over original
#define SHINY_ODDS 5000 // Actual probability is SHINY_ODDS/65536

// Learning moves
#define MON_ALREADY_KNOWS_MOVE 0xFFFE
#define MON_HAS_MAX_MOVES      0xFFFF

#define PLAYER_HAS_TWO_USABLE_MONS              0x0
#define PLAYER_HAS_ONE_MON                      0x1
#define PLAYER_HAS_ONE_USABLE_MON               0x2


enum OtIdMethod
{
    OT_ID_PLAYER_ID,
    OT_ID_PRESET,
    OT_ID_RANDOM_NO_SHINY
}; //this makes random trainers have no shiny mon

#define MON_GIVEN_TO_PARTY      0x0
#define MON_GIVEN_TO_PC         0x1
#define MON_CANT_GIVE           0x2

#define MON_MALE       0x00
#define MON_FEMALE     0xFE
#define MON_GENDERLESS 0xFF

#define FRIENDSHIP_EVENT_GROW_LEVEL           0
#define FRIENDSHIP_EVENT_VITAMIN              1
#define FRIENDSHIP_EVENT_BATTLE_ITEM          2
#define FRIENDSHIP_EVENT_LEAGUE_BATTLE        3		//should include gym leaders,elite four & champion
#define FRIENDSHIP_EVENT_LEARN_TMHM           4
#define FRIENDSHIP_EVENT_WALKING              5
#define FRIENDSHIP_EVENT_MASSAGE              6
#define FRIENDSHIP_EVENT_FAINT_SMALL          7
#define FRIENDSHIP_EVENT_FAINT_OUTSIDE_BATTLE 8
#define FRIENDSHIP_EVENT_FAINT_LARGE          9
#define FRIENDSHIP_EVENT_EXP_GAINED          10		//added logic gain +1 for gaining exp in battle; also counts exp share //emerald has extra option for berries  will need to addd

#define FRIENDSHIP_FRIENDLY 100
#define FRIENDSHIP_HIGH 50
#define FRIENDSHIP_AVERAGE 35
#define FRIENDSHIP_MID 30
#define FRIENDSHIP_ABOVE_STANDARD 25
#define FRIENDSHIP_STANDARD 15
#define FRIENDSHIP_LOW 10
#define FRIENDSHIP_LEGENDARY 0

#define MAX_PER_STAT_IVS 31
#define MIN_FIXED_IVS 20	//minimum value I plan to use for trainer assignment, is used for gym leaders  [replaced IV Mask]
#define USE_RANDOM_IVS (MAX_PER_STAT_IVS + 1)	//makes createmon function use random data for ivs, just like wild mon	can override fixed value for trainer party
#define MAX_PER_STAT_EVS 360 //had changd to 564 insane	//prviously 255 //recently learned amount of stat able to add to total stat w evs is about same as an bst increase so this is insane
#define MAX_TOTAL_EVS 788 //may lower 612 also isnt bad mix of new per stat and old per stat	//previosly 510
#define EV_ITEM_BOOSTER_LIMIT 250	//how many evs can be gained from ev boost items, previously 100  each one apparently ads 10 evs? every 4 is 1 stat point
//consider raising to new per stat cap, don't want to make it to easy to get the boosted evs, I want people to actually train their mon.
#define FRIENDSHIP_EVO_LIMITER 85
//#define GLOBAL_STAT_TOTAL_LIMIT 600 // limit for ev gain + bst would be bst + total evs / 4

//think goal should be to be able to train weak mon
//up to bout mid 500s maybe 520-550 or so
//base was able to add 126 to bst
//and for mon to be considered good usually
//needs around 500

//idea  for this is with ev investment mon couldn't raise individual stat
//above 135 but that limits strong mon
//think instead need dynamic logic
//if set base stat + 63 is less than 135
//then their limit is 135 otherwise is base stat + 135
//63 being old per stat limit actually fuck this just make a function
//point is bring up lower mon, while not lowering potential
//of strong mon
#define GLOBAL_PER_STAT_LIMIT 135 //realized would need a individual stat limit as well
//will keep stats from getting too nutty, keep mon that are hyper specialized by default still special
//ex. haxorous who has +147 base, he'll still be noticeabley stronger by default than any mon that had to train
//and won't really negatively affect that many as usually you don't train the stat that's already hyper boosted
//as it'd just give diminishing returns
//ok now that have this will need to implement these in places max total evs
//and ev cap are used

//I may change this rather than using a global define for global gain limit
//I can make it a conditional via terniary operator,
//and just put it in all the functions better but not as simple to do 
//but plan is if bst is below 600  gain limit is 600
//if bst is above 600 global gain limit is 650

// Move category defines.
enum __attribute__((packed)) DamageCategory
{
    DAMAGE_CATEGORY_PHYSICAL,
    DAMAGE_CATEGORY_SPECIAL,
    DAMAGE_CATEGORY_STATUS
};

// Growth rates
enum GrowthRate
{
    GROWTH_MEDIUM_FAST,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW,
};

//Stat EV Ids- believe was mostly for power items logic
#define HpEV 0
#define AttackEV 1
#define DefenseEV 2
#define SpeedEV 3
#define SpAttackEV 4
#define SpDefenseEV 5

//changed define values from 0-3 to 1-4, to make it default to random if 0.
//ABILITY NUM DEFINES
#define RANDOM_ABILITY		0
#define ABILITY_1			1
#define ABILITY_2			2
#define HIDDEN_ABILITY		3
#define HIDDEN_ABILITY_2	4



#define PARTY_SIZE 6
#define UNOWN_FORM_COUNT 28
#define BOX_NAME_LENGTH 8
#define MAX_LEVEL_UP_MOVES 35	//attempt raisae to 35?
#define MIN_LEVEL 1
#define MAX_LEVEL 100

#define EVO_MODE_NORMAL     0
#define EVO_MODE_TRADE      1
#define EVO_MODE_ITEM_USE   2
#define EVO_MODE_ITEM_CHECK 3 // If an Everstone is being held, still want to show that the stone *could* be used on that Pokémon to evolve

// Split defines.
//not sure how to handle these rn
//using damage category now
//but considering how moves work
//moves can be physical or special
//based on what side of defense it hits enemy on
//but then there's also if it uses
//attackers phys or special attack stat
//and then there are special moves
//that use other stats to determine offense from
//just wondering how to conceptualize that
#define SPLIT_PHYSICAL  0x0
#define SPLIT_SPECIAL   0x1
#define SPLIT_STATUS    0x2

//rather than ave no mon has more than 2 stages
#define MAX_EVO_STAGES 2 //buffer so players can evolve after removing from box

enum ShinyMode {
    SHINY_MODE_ALWAYS,
    SHINY_MODE_RANDOM,
    SHINY_MODE_NEVER
};//adding idk what for rn

#define MON_PIC_WIDTH 64
#define MON_PIC_HEIGHT 64
#define MON_PIC_SIZE (MON_PIC_WIDTH * MON_PIC_HEIGHT / 2)

/*
// Most Pokémon have 2 frames (a default and an alternate for their animation).
// There are 4 exceptions:
// - Deoxys has 2 frames, 1 for each form
// - Spinda has 1 frame, presumably to avoid the work of animating its spots
// - Unown has 1 frame, presumably to avoid the work of animating all 28 of its forms
#define MAX_MON_PIC_FRAMES 2
*/
//not really using just defined
//No idea why this is 4 guess just for buffer?
#define MAX_MON_PIC_FRAMES 4

//use with CountAliveMonsInBattle
#define BATTLE_ALIVE_EXCEPT_BATTLER      0
#define BATTLE_ALIVE_EXCEPT_BATTLER_SIDE 1
#define BATTLE_ALIVE_OPPOSING_SIDE       2

// used by ShouldIgnoreDeoxysForm
#define DEOXYS_CHECK_BATTLE_SPRITE      1
#define DEOXYS_CHECK_TRADE_MAIN         3
#define DEOXYS_CHECK_BATTLE_ANIM        5

#endif // GUARD_CONSTANTS_POKEMON_H
