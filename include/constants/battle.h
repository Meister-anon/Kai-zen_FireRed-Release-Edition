#ifndef GUARD_CONSTANTS_BATTLE_H
#define GUARD_CONSTANTS_BATTLE_H

#include "battle_move_effects.h"

/*
 * A battler may be in one of four positions on the field. The first bit determines
 * what side the battler is on, either the player's side or the opponent's side.
 * The second bit determines what flank the battler is on, either the left or right.
 * Note that the opponent's flanks are drawn corresponding to their perspective, so
 * their right mon appears on the left, and their left mon appears on the right.
 * The battler ID is usually the same as the position, except in the case of link battles.
 *
 *   + ------------------------- +
 *   |           Opponent's side |
 *   |            Right    Left  |
 *   |              3       1    |
 *   |                           |
 *   | Player's side             |
 *   |  Left   Right             |
 *   |   0       2               |
 *   ----------------------------+
 *   |                           |
 *   |                           |
 *   +---------------------------+
 */

#define MAX_BATTLERS_COUNT  4
//reportedely takes ewram?
//test if can hold 6 for triple battles w my ewram removal
//supposedly doesn't build for EE
//tested value 6, I have plenty of room left, nice
//for me the increase requires about 1-1.3% ewram

 //battler positions for gbattlerpostions
#define B_POSITION_PLAYER_LEFT        0
#define B_POSITION_OPPONENT_LEFT      1	//read from back of enemy, oponent left is right from player view
#define B_POSITION_PLAYER_RIGHT       2
#define B_POSITION_OPPONENT_RIGHT     3	//read from back of enemy, oponent right is left from player view

// These macros can be used with either battler ID or positions to get the partner or the opposite mon
#define BATTLE_OPPOSITE(id) ((id) ^ 1)
#define BATTLE_PARTNER(id) ((id) ^ 2)

#define B_SIDE_PLAYER     0
#define B_SIDE_OPPONENT   1
#define NUM_BATTLE_SIDES  2

#define B_FLANK_LEFT 0
#define B_FLANK_RIGHT 1

#define BIT_SIDE        1
#define BIT_FLANK       2

// Battle Type Flags
#define BATTLE_TYPE_WILD             0x0000 //think can use like this  yup use gbattletypeflags == BATTLE_TYPE_WILD  specifically for wild battle for all else can use !(gBattleTypeFlags & BATTLE_TYPE_TRAINER)
#define BATTLE_TYPE_DOUBLE           0x0001 //relized this was used as 1 for double value in trainers.h because it lined up with this for gbattletypeflags, its the actual value, 0 is no flags so just default single I guess
#define BATTLE_TYPE_LINK             0x0002
#define BATTLE_TYPE_IS_MASTER        0x0004 // In not-link battles, it's always set.
#define BATTLE_TYPE_TRAINER          0x0008
#define BATTLE_TYPE_FIRST_BATTLE     0x0010
#define BATTLE_TYPE_ROTATION         0x0020     
#define BATTLE_TYPE_TRIPLE           0x0040     
#define BATTLE_TWO_VS_ONE_PLAYER     0x0080 //planned but yet to do
#define BATTLE_TYPE_BATTLE_TOWER     0x0100 //last value for u8 size, so if want use this for trainer set in trainers, would need all relevant battle types below this...
#define BATTLE_TYPE_OLD_MAN_TUTORIAL 0x0200 //checked and can move all others, without issue, trainer battle type is only one that uses u8 value all else is u32
#define BATTLE_TYPE_ROAMER           0x0400
#define BATTLE_TYPE_EREADER_TRAINER  0x0800	//remove this, so I can replace it.
#define BATTLE_TYPE_KYOGRE_GROUDON   0x1000
#define BATTLE_TYPE_LEGENDARY        0x2000
#define BATTLE_TYPE_GHOST_UNVEILED   0x2000 // Re-use of BATTLE_TYPE_LEGENDARY, when combined with BATTLE_TYPE_GHOST
#define BATTLE_TYPE_SAFARI           0x4000 //no using regi can replace this //replaced w safari
#define BATTLE_TYPE_GHOST            0x8000 //check want to setup for if target mon is ghost type and doesnt have silf scope, to put ghosts in underpass at nighttime
#define BATTLE_TYPE_POKEDUDE         0x10000
#define BATTLE_TYPE_WILD_SCRIPTED    0x20000
#define BATTLE_TYPE_LEGENDARY_FRLG   0x40000
#define BATTLE_TYPE_TRAINER_TOWER    0x80000
#define BATTLE_TYPE_20               0x100000   //this appears to be for link battle?   /renmae to link at some point will eventually remove these 2
#define BATTLE_TYPE_MULTI            0x200000   //multi link battle?  swapped these 2 placement, so could use incldues for trainers.h battle type setting
#define BATTLE_TYPE_INGAME_PARTNER   0x400000
#define BATTLE_TYPE_TWO_OPPONENTS    0x800000	//carry over from emerald, not fully set here yet but is reason for gTrainerBattleOpponent_B  when 2 trainers approach player
#define BATTLE_TYPE_RECORDED         0x1000000  //also not used, or wont be
#define BATTLE_TYPE_RECORDED_LINK    0x2000000  //added for now, to deal w record battle link additions w test system, can prob remove later vsonic
#define BATTLE_TYPE_x4000000         0x4000000
#define BATTLE_TYPE_SECRET_BASE      0x8000000
#define BATTLE_TYPE_GROUDON          0x10000000
#define BATTLE_TYPE_KYOGRE           0x20000000
#define BATTLE_TYPE_RAYQUAZA         0x40000000
#define BATTLE_TYPE_x80000000        0x80000000

#define IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(flags) ((flags) & BATTLE_TYPE_GHOST && !((flags) & BATTLE_TYPE_GHOST_UNVEILED))
#define IS_BATTLE_TYPE_GHOST_WITH_SCOPE(flags) ((flags) & BATTLE_TYPE_GHOST && (flags) & BATTLE_TYPE_GHOST_UNVEILED)

#define RIVAL_BATTLE_HEAL_AFTER  1
#define RIVAL_BATTLE_TUTORIAL    3

#define WILD_DOUBLE_BATTLE ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER))))
#define BATTLE_TWO_VS_ONE_OPPONENT ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && gTrainerBattleOpponent_B == 0xFFFF))
#define BATTLE_TYPE_HAS_AI          (BATTLE_TYPE_TRAINER | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_SAFARI | BATTLE_TYPE_ROAMER | BATTLE_TYPE_INGAME_PARTNER)


// Battle Outcome defines
#define B_OUTCOME_WON                  0x1
#define B_OUTCOME_LOST                 0x2
#define B_OUTCOME_DREW                 0x3
#define B_OUTCOME_RAN                  0x4
#define B_OUTCOME_PLAYER_TELEPORTED    0x5
#define B_OUTCOME_MON_FLED             0x6
#define B_OUTCOME_CAUGHT               0x7
#define B_OUTCOME_NO_SAFARI_BALLS      0x8
#define B_OUTCOME_FORFEITED            0x9
#define B_OUTCOME_MON_TELEPORTED       0xA
#define B_OUTCOME_LINK_BATTLE_RAN      0x80


// Non-volatile status conditions
// These persist remain outside of battle and after switching out
#define STATUS1_NONE             0
//#define STATUS1_SLEEP            (1 << 0 | 1 << 1 | 1 << 2) // First 3 bits (Number of turns to sleep)
//#define STATUS1_SLEEP_TURN(num)  ((num) << 0) // Just for readability (or if rearranging statuses)
#define STATUS1_SLEEP            (1 << 1)
#define STATUS1_POISON           (1 << 2)
#define STATUS1_BURN             (1 << 3)
#define STATUS1_FREEZE           (1 << 4)
#define STATUS1_PARALYSIS        (1 << 5)
#define STATUS1_TOXIC_POISON     (1 << 6)
#define STATUS1_SPIRIT_LOCK      (1 << 7)	//not using for now
#define STATUS1_PLACEHOLDER		 (1 << 8) //planned bug status  //changed mind trouble w healthbox and or balance make status 2/4
//#define STATUS1_TOXIC_COUNTER    (1 << 8 | 1 << 9 | 1 << 10 | 1 << 11)
#define STATUS1_TOXIC_TURN(num)  ((num) << 10)//redid toxic, put at original value, moved others
//decide remove spirit lock


//can prob reduce values for ones that use timer
//if can rmeove turn count from actually being needed to store the values
//and instead just be an auto updated, sort of like I have toxic set now
//where it no longe ruses toxic counter to determine damage
//and instead uses the toxic turn count to update a disablestruct value
//if could do same/similar for sleep turn could reduce sleep status to 1
//and not need to store the turn timers in data at all, meaning their value wouldn't matter
//so I could move them up and bring other status down
//should give space for 2 statuses, 
//frees flag 2, and flag 8
//for binary patch could remoev spirit lock and infest
//so people hvae space to add their own new status?

//could decide what things I want to separate out for main distribution


#define STATUS1_PSN_ANY          (STATUS1_POISON | STATUS1_TOXIC_POISON)
//will need to go through and review all use of this variable since I've expanded status1
//laso cean up status definex

//status1_any seeems tobe used to check all status1 but exclude toxic counter values & sleep counter
#define STATUS1_ANY              (STATUS1_SLEEP | STATUS1_POISON | STATUS1_BURN | STATUS1_FREEZE | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON)

//with setup switchlock realize don't need to make these status1 for them to persist
//#define STATUS1_ENVIRONMENT_TRAP (STATUS1_FIRE_SPIN || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM)

//#define ITS_A_TRAP_STATUS1 (STATUS1_SNAP_TRAP || STATUS1_FIRE_SPIN || STATUS1_CLAMP || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM || STATUS1_SWARM || STATUS1_WRAPPED)

// Volatile status ailments
// These are removed after exiting the battle or switching out
//from what I see game is only set up to display status animations for status 1 & status2 staus...but then leech seed works and its status3?
//if everything works will most likely reorganize
//so free space is at the bottom
#define STATUS2_CONFUSION             (1 << 0)
#define STATUS2_FREESPACE             (1 << 1)
#define STATUS2_BLANK                 (1 << 2)
//#define STATUS2_CONFUSION_TURN(num)   ((num) << 0)
#define STATUS2_FLINCHED              (1 << 3)
#define STATUS2_UPROAR                (1 << 4)
#define STATUS2_BLANK_SPACE           (1 << 5)
#define STATUS2_NOTHING               (1 << 6)
//#define STATUS2_UPROAR_TURN(num)      ((num) << 4)
#define STATUS2_EMERGENCY_EXIT        (1 << 7)	//use for emergency exit
#define STATUS2_BIDE                  (1 << 8) //w timer don't need take up 8 and 9 //will prob eventually remove all timer flags replace w struct values
#define STATUS2_SWITCH_LOCKED         (1 << 9)// new status for spirit shackle, escape prevention on a timer, not locked to battler
//#define STATUS2_BIDE_TURN(num)        (((num) << 8) & STATUS2_BIDE)
#define STATUS2_LOCK_CONFUSE          (1 << 10) // e.g. Thrash
#define STATUS2_UNUSED                (1 << 11)
//#define STATUS2_LOCK_CONFUSE_TURN(num)((num) << 10) //this isn't the confusion effect this is how many turns outrage/thrash/petal dance lasts which should be 2-3 turns
#define STATUS2_MULTIPLETURNS         (1 << 12) //wrapped is wrap & bide  / separting just wrap, think plan put wrap into status4 so all traps together
#define STATUS2_WRAPPED               (1 << 13)	//make individual wrapped for each, but all use same wrap turn counter / cant usesame counter and multi trap so this will just be wrap
//#define STATUS2_WRAPPED_TURN(num)     ((num) << 13)	//left shift value is starting point of status wrapped
#define STATUS2_POWDER                (1 << 14)
#define STATUS2_FREE_SPACE            (1 << 15)
#define STATUS2_INFATUATION           (1 << 16 | 1 << 17 | 1 << 18 | 1 << 19)  // 4 bits, one for every battler
#define STATUS2_INFATUATED_WITH(battler) (gBitTable[battler] << 16)
#define STATUS2_FOCUS_ENERGY          (1 << 20)
#define STATUS2_TRANSFORMED           (1 << 21)
#define STATUS2_PLACEHOLDER           (1 << 22) //removing recharge as a status, as all of its logic can be done w the timer...
#define STATUS2_RAGE                  (1 << 23)
#define STATUS2_SUBSTITUTE            (1 << 24)
#define STATUS2_DESTINY_BOND          (1 << 25)
#define STATUS2_ESCAPE_PREVENTION     (1 << 26)
#define STATUS2_NIGHTMARE             (1 << 27)
#define STATUS2_CURSED                (1 << 28)
#define STATUS2_FORESIGHT             (1 << 29)
#define STATUS2_DEFENSE_CURL          (1 << 30)
#define STATUS2_TORMENT               (1 << 31)	//ok updated from current firered thought would let me have more status
//but realized its u32  cant go higher than 31, either make new status type or replace existing
//haev 2 extra spaces now
/*
    Can make space for gen 9 additions by removing all timer based values
    like I did w sleep, previously covered values 0, 1 , 2
    and sleep turn was ((num) << 0)
    //used bit logic to set, but I can just set it directly
    when clear can make first value (1 << 0)  as that equates to 1

    don't want to mess w infatuate
    but can make space in confuse, lock confuse, and upraor
*/
//status 2 that takes users attention so would not be able to absorb ability setup like status1 any I think
//having status flinch makes sense here, even though its only noticed on attack cancel, the effect is already set
//still to test double battle but most of these seem to work when set via debug
//but bide doesn't (not unexpected since I changed it a good deal)
//rage , escape prevention, and torment don't work, ok this seems to be issues w the debugger
//surprisingly enough and not actually my macro
#define PREOCCUPIED_STATUS (STATUS2_CONFUSION | STATUS2_FLINCHED | STATUS2_UPROAR | STATUS2_BIDE | STATUS2_LOCK_CONFUSE\
| STATUS2_MULTIPLETURNS | STATUS2_WRAPPED | STATUS2_INFATUATION | STATUS2_RAGE\
| STATUS2_ESCAPE_PREVENTION | STATUS2_TORMENT)

// Seems like per-battler statuses. Not quite sure how to categorize these
//#define STATUS3_SKY_DROPPED             0x1 // Target of Sky Drop
#define STATUS3_LEECHSEED_BATTLER       (1 << 0 | 1 << 1) // The battler to receive HP from Leech Seed
#define STATUS3_LEECHSEED                (1 << 2) //is leech seeded status, doesn't store battler with status
#define STATUS3_ALWAYS_HITS             (1 << 3 | 1 << 4)    // two bits
#define STATUS3_ALWAYS_HITS_TURN(num)   (((num) << 3) & STATUS3_ALWAYS_HITS) // "Always Hits" is set as a 2 turn timer, i.e. next turn is the last turn when it's active
#define STATUS3_PERISH_SONG             (1 << 5)
#define STATUS3_ON_AIR                  (1 << 6)
#define STATUS3_UNDERGROUND             (1 << 7)
#define STATUS3_MINIMIZED               (1 << 8)
#define STATUS3_CHARGED_UP              (1 << 9)
#define STATUS3_ROOTED                  (1 << 10) //if I understand correctly, change gives extra statur 3 space 12 would be unused
#define STATUS3_YAWN                    (1 << 11) // Number of turns to sleep
//#define STATUS3_YAWN_TURN(num)          (((num) << 11) & STATUS3_YAWN)//  changing set status yawn, then at end turn check for it, if there remove and put to sleep
#define STATUS3_ME_FIRST               (1 << 12) //use for commander gen9, then roll into semi invul
#define STATUS3_IMPRISONED_OTHERS       (1 << 13)
#define STATUS3_GRUDGE                  (1 << 14)
#define STATUS3_CANT_SCORE_A_CRIT       (1 << 15)
//#define STATUS3_MUDSPORT                (1 << 16)	//can move these 2 to side status?
//#define STATUS3_WATERSPORT              0x20000	//(1 << 17) //remove sports later
#define STATUS3_UNDERWATER              (1 << 18)
#define STATUS3_INTIMIDATE_POKES        (1 << 19)
#define STATUS3_TRACE                   (1 << 20)
#define STATUS3_ROOTED_SHIFT (21)   //redone use specila staatus as turn count 
#define STATUS3_ROOTED_TURN(num) ((num) << STATUS3_ROOTED_SHIFT) //15 there was for max turns new max turns is 8, max turns for aqua ring is 6
#define STATUS3_AQUARING_SHIFT (22)
#define STATUS3_AQUARING_TURN(num) ((num) << STATUS3_AQUARING_SHIFT) //way used these aren't really statuses, they don't get set they are more just macros for turn tracking

//has room for 1 more status3 at 12 now
//can replace always hits timer, to make room for commander

#define STATUS3_GASTRO_ACID             (1 << 16)	//is there any reaso this needs to be status3 rather than a status 2?
//#define STATUS3_EMBARGO                 (1 << 17)	//move to side status to make room
#define STATUS3_SMACKED_DOWN            (1 << 17)
#define STATUS3_TELEKINESIS             (1 << 23)
#define STATUS3_PHANTOM_FORCE           (1 << 24)
#define STATUS3_MIRACLE_EYED            (1 << 25)
#define STATUS3_MAGNET_RISE             (1 << 26)
#define STATUS3_AQUA_RING               (1 << 27)
#define STATUS3_LASER_FOCUS             (1 << 28)
#define STATUS3_TIGER_MOM_ATTACKS       (1 << 29)
#define STATUS3_POWER_TRICK             (1 << 30)
#define STATUS3_SKY_DROPPED				(1 << 31) //will be side affecting, this just for first turn effects,  change move to target both to match intentions
//#define STATUS3_HEAL_BLOCK				(1 << 31) //will be side affecting, this just for first turn effects,  change move to target both to match intentions

#define STATUS3_SEMI_INVULNERABLE       (STATUS3_UNDERGROUND | STATUS3_ON_AIR | STATUS3_UNDERWATER | STATUS3_PHANTOM_FORCE)

#define STAUS3_VULNERABLE (STATUS3_ROOTED | STATUS3_YAWN)

//signature of heliolisk, for move electrify
//similar to plasma fist effect but for target
#define STATUS4_ELECTRIFIED             (1 << 0)	//need to check how status4 is setup to make sure it runs on same conditions as status2
#define STATUS4_PLASMA_FISTS            (1 << 1)	//if it works I can move wrap status and wrap counter up here so it all uses status4
//start of new trap effects, each will have its own status and timer in disable structs
#define STATUS4_BIND                    (1 << 2)
#define STATUS4_FIRE_SPIN				(1 << 3)
#define STATUS4_CLAMP					(1 << 4)
#define STATUS4_WHIRLPOOL				(1 << 5)
#define STATUS4_SAND_TOMB				(1 << 6)
#define STATUS4_MAGMA_STORM				(1 << 7)
#define STATUS4_SWARM   				(1 << 8)
#define STATUS4_SNAP_TRAP               (1 << 9)
#define STATUS4_THUNDER_CAGE            (1 << 10)
#define STATUS4_SALT_CURED              (1 << 11) //Doesn't prevent escape so don't treat as trap, mix of leech seed and stealth rock, 1/8th max hp, double status dmg against water and steel
#define STATUS4_INFESTATION             (1 << 12)
//removed replaced w timer
//#define STATUS4_GROUNDED                (1 << 11)  //new status  set for move effect trench_run to more easily translate mon into grounded state, add status to groudned function

//was able to save great amount of space with emerald upgrades
//but now dont have separate counter for each status
//I could make one without issue by adding to disable struct
//but further thought it doesnt make sense for most of the status
//to interact since they are environment based.
//only ones that make sense are clamp, infestation & snaptrap

//hmm keep that in mind for later,
//2 types of traps environment vs physical, where physical has separate wrap timer & can stack

//statuses for traps together forgot can't do this  since not all  .status2
//#define ITS_A_TRAP_STATUS (STATUS2_WRAPPED | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_MAGMA_STORM | STATUS4_INFESTATION)

#define STATUS4_ENVIRONMENT_TRAP (STATUS4_FIRE_SPIN | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_MAGMA_STORM)

//trap statuses not immune to floating enemies
//#define ITS_A_TRAP_STATUS_2 (STATUS2_WRAPPED | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_INFESTATION)

//temp just the status4 stuff		//OK so status4 not currently used in battle? its not in BattlePokemon struct need add and investigate
#define ITS_A_TRAP_STATUS4 (STATUS4_BIND | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_MAGMA_STORM | STATUS4_SWARM | STATUS4_SNAP_TRAP | STATUS4_THUNDER_CAGE)


// Not really sure what a "hitmarker" is.
#define HITMARKER_WAKE_UP_CLEAR         (1 << 4)	//// Cleared when waking up. Never set or checked.
#define HITMARKER_SKIP_DMG_TRACK        (1 << 5)
#define HITMARKER_DESTINYBOND           (1 << 6)
#define HITMARKER_NO_ANIMATIONS         (1 << 7)
#define HITMARKER_IGNORE_SUBSTITUTE     (1 << 8)
#define HITMARKER_NO_ATTACKSTRING       (1 << 9)
#define HITMARKER_ATTACKSTRING_PRINTED  (1 << 10)
#define HITMARKER_NO_PPDEDUCT           (1 << 11)
#define HITMARKER_SWAP_ATTACKER_TARGET  (1 << 12)
//#define HITMARKER_IGNORE_SAFEGUARD      (1 << 13) //updated to emerald standard so removed this, can replace
#define HITMARKER_SYNCHRONIZE_EFFECT    (1 << 14)
#define HITMARKER_RUN                   (1 << 15)
#define HITMARKER_IGNORE_DISGUISE       (1 << 16)
//#define HITMARKER_IGNORE_ON_AIR         0x00010000 //remove later
//#define HITMARKER_IGNORE_UNDERGROUND    0x00020000 //remove later
//#define HITMARKER_IGNORE_UNDERWATER     0x00040000 //remove later
// 3 free spots because of change in handling of UNDERGROUND/UNDERWATER/ON AIR
#define HITMARKER_UNABLE_TO_USE_MOVE    (1 << 19)
#define HITMARKER_PASSIVE_DAMAGE        (1 << 20)
#define HITMARKER_DISOBEDIENT_MOVE      (1 << 21)
#define HITMARKER_PLAYER_FAINTED        (1 << 22)
#define HITMARKER_ALLOW_NO_PP           (1 << 23)
#define HITMARKER_GRUDGE                (1 << 24)
#define HITMARKER_OBEYS                 (1 << 25)
#define HITMARKER_NEVER_SET             (1 << 26) // Cleared as part of a large group. Never set or checked
#define HITMARKER_CHARGING              (1 << 27)
#define HITMARKER_FAINTED(battler)      (1u << (battler + 28))
#define HITMARKER_FAINTED2(battler)     HITMARKER_FAINTED(battler)	//removed hitmarker semi invul underground etc. can't go up to fainted2 value
#define HITMARKER_STRING_PRINTED        (1 << 29) //extra from emerald in case need

// Per-side statuses that affect an entire party
#define SIDE_STATUS_REFLECT					(1 << 0)
#define SIDE_STATUS_LIGHTSCREEN				(1 << 1)
#define SIDE_STATUS_STICKY_WEB				(1 << 2)
#define SIDE_STATUS_SPIKES					(1 << 4) //side status fitureattack never used?, guess can remove
#define SIDE_STATUS_SAFEGUARD				(1 << 5)
#define SIDE_STATUS_FREE_SPACE  			(1 << 6)	//black fog shuold prevnt same as block burn/etc. dmg
#define SIDE_STATUS_MIST					(1 << 8)	//blocked by black fog
#define SIDE_STATUS_SPIKES_DAMAGED			(1 << 9)
#define SIDE_STATUS_TAILWIND                (1 << 10)	//unsure could have tail wind use do defog affect, remove mist & black fog
#define SIDE_STATUS_AURORA_VEIL             (1 << 11)
#define SIDE_STATUS_LUCKY_CHANT             (1 << 12)
#define SIDE_STATUS_TOXIC_SPIKES            (1 << 13)
#define SIDE_STATUS_STEALTH_ROCK            (1 << 14) //also prevented from dmg when black fog up
#define SIDE_STATUS_STEALTH_ROCK_DAMAGED    (1 << 15)
#define SIDE_STATUS_TOXIC_SPIKES_DAMAGED    (1 << 16)
#define SIDE_STATUS_STICKY_WEB_DAMAGED      (1 << 17)
#define SIDE_STATUS_QUICK_GUARD             (1 << 18)
#define SIDE_STATUS_WIDE_GUARD              (1 << 19)
#define SIDE_STATUS_CRAFTY_SHIELD           (1 << 20)
#define SIDE_STATUS_MAT_BLOCK               (1 << 21)
#define SIDE_STATUS_HEAL_BLOCK              (1 << 22)//need setup this & embargo  heal block side status is already setup I jusut forgot...
#define SIDE_STATUS_EMBARGO					(1 << 23)
#define SIDE_STATUS_MUDSPORT				(1 << 24)
#define SIDE_STATUS_WATERSPORT				(1 << 25)
#define SIDE_STATUS_MAGIC_COAT				(1 << 26)	//for magic coat buff make 3 turn, similar in effect to a screen, but 3 instead of 5 turns as it nullifies

#define SIDE_STATUS_HAZARDS_ANY    (SIDE_STATUS_SPIKES | SIDE_STATUS_STICKY_WEB | SIDE_STATUS_TOXIC_SPIKES | SIDE_STATUS_STEALTH_ROCK)
#define SIDE_STATUS_SCREEN_ANY     (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL)

// Field affecting statuses.
#define STATUS_FIELD_MAGIC_ROOM         (1 << 0)
#define STATUS_FIELD_TRICK_ROOM        (1 << 1)
#define STATUS_FIELD_WONDER_ROOM        (1 << 2)
#define STATUS_FIELD_GRAVITY            (1 << 3)
//#define STATUS_FIELD_MUDSPORT           0x8  will try to keep these 2 in status3 because they didn't use a timer I can put them here and have them not use a timer as well.
//#define STATUS_FIELD_WATERSPORT         0x10
#define STATUS_FIELD_SCORCHED_TERRAIN   (1 << 4)	//make red version or new tile with scorched cracked earth appearane
#define STATUS_FIELD_FLOODED_TERRAIN    (1 << 5)	//can use surf tile/ or edit a blue puddle into normal graphic
#define STATUS_FIELD_OCEAN_TERRAIN      (1 << 6)	//for when surfing on ocean/deeper water /grass terrain & scorched terrain wouldn't work
#define STATUS_FIELD_GRASSY_TERRAIN     (1 << 7)	//longer grass
#define STATUS_FIELD_MISTY_TERRAIN      (1 << 8)	//mist/haze/defog -?? ooh this was to use the animation from those for field effect
#define STATUS_FIELD_ELECTRIC_TERRAIN   (1 << 9)	//sparks tag
#define STATUS_FIELD_PSYCHIC_TERRAIN    (1 << 10)	//could surround field w hidden power orbs?
#define STATUS_FIELD_SNOWY_TERRAIN		(1 << 11)	//for snow area
#define STATUS_FIELD_TERRAIN_PERMANENT  (1 << 12)		//last terrain effect so putting here //(1 << 12)   
#define STATUS_FIELD_ION_DELUGE         (1 << 13)
#define STATUS_FIELD_FAIRY_LOCK         (1 << 14)
#define STATUS_FIELD_BLACK_FOG          (1 << 15)	//HAZE -3 full turns so timer is 4
//#define STATUS_FIELD_MUDSPORT			(1 << 15) gonna put these in side status instead
//#define STATUS_FIELD_WATERSPORT         (1 << 16)

#define TERRAIN_DEFINES

#define STATUS_FIELD_TERRAIN_ANY              (STATUS_FIELD_SCORCHED_TERRAIN | STATUS_FIELD_FLOODED_TERRAIN | STATUS_FIELD_OCEAN_TERRAIN | STATUS_FIELD_GRASSY_TERRAIN | STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_PSYCHIC_TERRAIN)

// Flags describing move's result
#define MOVE_RESULT_MISSED             (1 << 0)
#define MOVE_RESULT_SUPER_EFFECTIVE    (1 << 1)
#define MOVE_RESULT_NOT_VERY_EFFECTIVE (1 << 2)
#define MOVE_RESULT_DOESNT_AFFECT_FOE  (1 << 3)
#define MOVE_RESULT_ONE_HIT_KO         (1 << 4)
#define MOVE_RESULT_FAILED             (1 << 5)
#define MOVE_RESULT_FOE_ENDURED        (1 << 6)
#define MOVE_RESULT_FOE_HUNG_ON        (1 << 7)

#define MOVE_RESULT_NO_EFFECT          (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_FAILED)

// Battle Weather as enum
#define ENUM_WEATHER_NONE			      0
#define ENUM_WEATHER_RAIN		          1
#define ENUM_WEATHER_SUN	              2
#define ENUM_WEATHER_SANDSTORM			  3
#define ENUM_WEATHER_HAIL				  4
#define ENUM_WEATHER_SUN_PRIMAL           5
#define ENUM_WEATHER_RAIN_PRIMAL          6
#define ENUM_WEATHER_STRONG_WINDS         7
//vsonic since added special status switchin done prob don't need now?
//think can just use that
#define REPEAT_SWITCH_IN            8
//hopefully to make macro for list of abilities
//to repeat on opponent switch in/send out


// Battle Weather flags
#define WEATHER_RAIN_TEMPORARY			(1 << 0)
#define WEATHER_RAIN_DOWNPOUR			(1 << 1)  // unused
#define WEATHER_RAIN_PERMANENT			(1 << 2)
#define WEATHER_RAIN_PRIMAL				(1 << 11)
#define WEATHER_RAIN_NON_TEMP			(WEATHER_RAIN_DOWNPOUR | WEATHER_RAIN_PERMANENT | WEATHER_RAIN_PRIMAL)	//excludes tmporary rain effects
#define WEATHER_RAIN_ANY				(WEATHER_RAIN_TEMPORARY | WEATHER_RAIN_DOWNPOUR | WEATHER_RAIN_PERMANENT | WEATHER_RAIN_PRIMAL)
#define WEATHER_SANDSTORM_TEMPORARY		(1 << 3)
#define WEATHER_SANDSTORM_PERMANENT		(1 << 4)
#define WEATHER_SANDSTORM_NON_TEMP		(WEATHER_SANDSTORM_PERMANENT)	//irrelevant unless add more sandstorm types
#define WEATHER_SANDSTORM_ANY			(WEATHER_SANDSTORM_TEMPORARY | WEATHER_SANDSTORM_PERMANENT)
#define WEATHER_SUN_TEMPORARY			(1 << 5)
#define WEATHER_SUN_PERMANENT			(1 << 6)
#define WEATHER_SUN_PRIMAL				(1 << 9)
#define WEATHER_SUN_NON_TEMP			(WEATHER_SUN_PERMANENT | WEATHER_SUN_PRIMAL)	//excludes temporary sun effects
#define WEATHER_SUN_ANY					(WEATHER_SUN_TEMPORARY | WEATHER_SUN_PERMANENT | WEATHER_SUN_PRIMAL)
#define WEATHER_HAIL					(1 << 7)
#define WEATHER_HAIL_PERMANENT			(1 << 8)
#define WEATHER_STRONG_WINDS			(1 << 10)
#define WEATHER_HAIL_NON_TEMP			(WEATHER_HAIL_PERMANENT)	//only relevant if add more hail types
#define WEATHER_HAIL_ANY				(WEATHER_HAIL | WEATHER_HAIL_PERMANENT)
#define WEATHER_ANY						(WEATHER_RAIN_ANY | WEATHER_SANDSTORM_ANY | WEATHER_SUN_ANY | WEATHER_HAIL_ANY)
#define WEATHER_PRIMAL_ANY				(WEATHER_RAIN_PRIMAL | WEATHER_SUN_PRIMAL | WEATHER_STRONG_WINDS)


// Battle terrain defines for gBattleTerrain.
#define BATTLE_TERRAIN_GRASS        0
#define BATTLE_TERRAIN_LONG_GRASS   1
#define BATTLE_TERRAIN_SAND         2
#define BATTLE_TERRAIN_UNDERWATER   3
#define BATTLE_TERRAIN_WATER        4
#define BATTLE_TERRAIN_POND         5
#define BATTLE_TERRAIN_MOUNTAIN     6
#define BATTLE_TERRAIN_CAVE         7
#define BATTLE_TERRAIN_BUILDING     8
#define BATTLE_TERRAIN_PLAIN        9
#define BATTLE_TERRAIN_LINK        10
#define BATTLE_TERRAIN_GYM         11
#define BATTLE_TERRAIN_LEADER      12
#define BATTLE_TERRAIN_INDOOR_2    13
#define BATTLE_TERRAIN_INDOOR_1    14
#define BATTLE_TERRAIN_LORELEI     15
#define BATTLE_TERRAIN_BRUNO       16
#define BATTLE_TERRAIN_AGATHA      17
#define BATTLE_TERRAIN_LANCE       18
#define BATTLE_TERRAIN_CHAMPION    19

// Return value for IsRunningFromBattleImpossible. 
#define BATTLE_RUN_SUCCESS        0
#define BATTLE_RUN_FORBIDDEN      1
#define BATTLE_RUN_FAILURE        2

//sub for wait time for battlescript
#define B_WAIT_TIME_LONG     0
#define B_WAIT_TIME_MED      1
#define B_WAIT_TIME_SHORT    2
#define B_WAIT_TIME_SHORTEST 3
#define B_WAIT_TIME_BRIEFEST 4
#define B_WAIT_TIME_CLEAR_BUFF 5
#define B_WAIT_TIME_CLEAR_BUFF_2 6
#define B_WAIT_TIME_UNIQUE 7
#define B_WAIT_TIME_LONG_LONG   8
#define B_WAIT_TIME_IMPORTANT_STRINGS 9  //Replace wait time long for printstrings not crit message result message
//changed to be array values pause time is still teh same

//flee flags for tryRunfrombattle function
#define FLEE_ITEM    1
#define FLEE_ABILITY 2

// Window Ids for sTextOnWindowsInfo_Normal
#define B_WIN_MSG                 0
#define B_WIN_ACTION_PROMPT       1 // "What will {x} do?"
#define B_WIN_ACTION_MENU         2 // "Fight/Pok�mon/Bag/Run" menu
#define B_WIN_MOVE_NAME_1         3 // Top left
#define B_WIN_MOVE_NAME_2         4 // Top right
#define B_WIN_MOVE_NAME_3         5 // Bottom left
#define B_WIN_MOVE_NAME_4         6 // Bottom right
#define B_WIN_PP				  9	// pp symbol	B_WIN_PP_REMAINING
#define B_WIN_MOVE_TYPE           8 // name of selected move type
#define B_WIN_PP_REMAINING        7 // current & max pp values	B_WIN_PP
#define B_WIN_DUMMY              10
#define B_WIN_SWITCH_PROMPT      11 // "Switch which?"
#define B_WIN_LEVEL_UP_BOX       12
#define B_WIN_LEVEL_UP_BANNER    13
#define B_WIN_YESNO              14
#define B_WIN_VS_PLAYER          15
#define B_WIN_VS_OPPONENT        16
#define B_WIN_VS_MULTI_PLAYER_1  17
#define B_WIN_VS_MULTI_PLAYER_2  18
#define B_WIN_VS_MULTI_PLAYER_3  19
#define B_WIN_VS_MULTI_PLAYER_4  20
#define B_WIN_VS_OUTCOME_DRAW    21
#define B_WIN_VS_OUTCOME_LEFT    22
#define B_WIN_VS_OUTCOME_RIGHT   23
#define B_WIN_OAK_OLD_MAN        24

#define B_TEXT_FLAG_NPC_CONTEXT_FONT    (1 << 6)
#define B_TEXT_FLAG_WINDOW_CLEAR        (1 << 7)

// Constants for Parental Bond
#define PARENTAL_BOND_1ST_HIT 2
#define PARENTAL_BOND_2ND_HIT 1
#define PARENTAL_BOND_OFF     0

// Constants for if HandleScriptMegaPrimalBurst should handle Mega Evolution, Primal Reversion, or Ultra Burst.
#define HANDLE_TYPE_MEGA_EVOLUTION 0
#define HANDLE_TYPE_PRIMAL_REVERSION 1
#define HANDLE_TYPE_ULTRA_BURST 2

#endif // GUARD_CONSTANTS_BATTLE_H
