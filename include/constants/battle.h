#ifndef GUARD_CONSTANTS_BATTLE_H
#define GUARD_CONSTANTS_BATTLE_H


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



enum BattlerPosition
{
    B_POSITION_PLAYER_LEFT,
    B_POSITION_OPPONENT_LEFT,
    B_POSITION_PLAYER_RIGHT,
    B_POSITION_OPPONENT_RIGHT,
    MAX_POSITION_COUNT,
    B_POSITION_ABSENT = 0xFF,
};
/*
#define B_POSITION_PLAYER_LEFT        0
#define B_POSITION_OPPONENT_LEFT      1	//read from back of enemy, oponent left is right from player view
#define B_POSITION_PLAYER_RIGHT       2
#define B_POSITION_OPPONENT_RIGHT     3	//read from back of enemy, oponent right is left from player view
*/

//battler positions for gbattlerpostions
enum BattlerId
{
    B_BATTLER_0,
    B_BATTLER_1, //read from back of enemy, oponent left is right from player view
    B_BATTLER_2,
    B_BATTLER_3, //read from back of enemy, oponent right is left from player view
    MAX_BATTLERS_COUNT,
};
//reportedely takes ewram?
//test if can hold 6 for triple battles w my ewram removal
//supposedly doesn't build for EE
//tested value 6, I have plenty of room left, nice
//for me the increase requires about 1-1.3% ewram

enum __attribute__((packed)) BattleTrainer
{
    B_TRAINER_0,
    B_TRAINER_1,
    B_TRAINER_2,
    B_TRAINER_3,
    MAX_BATTLE_TRAINERS,
};


//could read battle_position_none 
//but believe this is more readable as id is used more oft than position
#define BATTLE_ID_NONE 0xFF

// These macros can be used with either battler ID or positions to get the partner or the opposite mon
#define BATTLE_OPPOSITE(id) ((id) ^ 1)
#define BATTLE_PARTNER(id) ((id) ^ 2)

// Left and right are determined by how they're referred to in tests and everywhere else.
// Left is battlers 0 and 1, right 2 and 3; if you assume the battler referencing them is south, left is to the northeast and right to the northwest.
#define LEFT_FOE(battler) ((BATTLE_OPPOSITE(battler)) & BIT_SIDE)
#define RIGHT_FOE(battler) (((BATTLE_OPPOSITE(battler)) & BIT_SIDE) | BIT_FLANK)

enum BattleSide
{
    B_SIDE_PLAYER = 0,
    B_SIDE_OPPONENT = 1,
    NUM_BATTLE_SIDES = 2,
};

#define B_FLANK_LEFT 0
#define B_FLANK_RIGHT 1

#define BIT_SIDE        1
#define BIT_FLANK       2

// Battle Type Flags
#define BATTLE_TYPE_WILD             (0 << 0) //think can use like this  yup use gbattletypeflags == BATTLE_TYPE_WILD  specifically for wild battle for all else can use !(gBattleTypeFlags & BATTLE_TYPE_TRAINER)
#define BATTLE_TYPE_DOUBLE           (1 << 0) //relized this was used as 1 for double value in trainers.h because it lined up with this for gbattletypeflags, its the actual value, 0 is no flags so just default single I guess
#define BATTLE_TYPE_LINK             (1 << 1)
#define BATTLE_TYPE_IS_MASTER        (1 << 2) // In not-link battles, it's always set.
#define BATTLE_TYPE_TRAINER          (1 << 3)
#define BATTLE_TYPE_FIRST_BATTLE     (1 << 4)
#define BATTLE_TYPE_ROTATION         (1 << 5)     
#define BATTLE_TYPE_TRIPLE           (1 << 6)     
#define BATTLE_TWO_VS_ONE_PLAYER     (1 << 7) //planned but yet to do
#define BATTLE_TYPE_BATTLE_TOWER     (1 << 8) //last value for u8 size, so if want use this for trainer set in trainers, would need all relevant battle types below this...
#define BATTLE_TYPE_OLD_MAN_TUTORIAL (1 << 9) //checked and can move all others, without issue, trainer battle type is only one that uses u8 value all else is u32
#define BATTLE_TYPE_ROAMER           (1 << 10)
#define BATTLE_TYPE_EREADER_TRAINER  (1 << 11)	//remove this, so I can replace it.
#define BATTLE_TYPE_KYOGRE_GROUDON   (1 << 12) //Idk WHy have this already split off into individual flag for each
#define BATTLE_TYPE_LEGENDARY        (1 << 13) //with planned legendary fight change can't resuse value, hmm actually I can as it works by combining flgas, i.e  //BATTLE_TYPE_GHOST | BATTLE_TYPE_GHOST_UNVEILED  essentially what I plan do w master so its fine
#define BATTLE_TYPE_GHOST_UNVEILED   (1 << 13) // Re-use of BATTLE_TYPE_LEGENDARY, when combined with BATTLE_TYPE_GHOST
#define BATTLE_TYPE_SAFARI           (1 << 14) //no using regi can replace this //replaced w safari
#define BATTLE_TYPE_GHOST            (1 << 15) //check want to setup for if target mon is ghost type and doesnt have silf scope, to put ghosts in underpass at nighttime
#define BATTLE_TYPE_POKEDUDE         (1 << 16)
#define BATTLE_TYPE_WILD_SCRIPTED    (1 << 17)
#define BATTLE_TYPE_LEGENDARY_FRLG   (1 << 18)  //not sure why this is here? its used in conjunction w flag legendary almost never used by itself?
#define BATTLE_TYPE_TRAINER_TOWER    (1 << 19)
#define BATTLE_TYPE_20               (1 << 20)   //this appears to be for link battle?   /renmae to link at some point will eventually remove these 2?
#define BATTLE_TYPE_MULTI            (1 << 21)   //multi link battle?  swapped these 2 placement, so could use incldues for trainers.h battle type setting
#define BATTLE_TYPE_INGAME_PARTNER   (1 << 22)
#define BATTLE_TYPE_TWO_OPPONENTS    (1 << 23)	//carry over from emerald, not fully set here yet but is reason for gTrainerBattleOpponent_B  when 2 trainers approach player
#define BATTLE_TYPE_RECORDED         (1 << 24)  //also not used, or wont be
#define BATTLE_TYPE_RECORDED_LINK    (1 << 25)  //added for now, to deal w record battle link additions w test system, can prob remove later vsonic
#define BATTLE_TYPE_x4000000         (1 << 26)
#define BATTLE_TYPE_MASTER_BALL      (1 << 27) //ok can remove this and use for master ball
#define BATTLE_TYPE_GROUDON          (1 << 28)
#define BATTLE_TYPE_KYOGRE           (1 << 29)
#define BATTLE_TYPE_RAYQUAZA         (1 << 30)
#define BATTLE_TYPE_x80000000        (1 << 31)

#define IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(flags) ((flags) & BATTLE_TYPE_GHOST && !((flags) & BATTLE_TYPE_GHOST_UNVEILED))
#define IS_BATTLE_TYPE_GHOST_WITH_SCOPE(flags) ((flags) & BATTLE_TYPE_GHOST && (flags) & BATTLE_TYPE_GHOST_UNVEILED)

#define RIVAL_BATTLE_HEAL_AFTER  1  //continue after loss rn doesn't go to gbattletypeflags value mathes doubles it just goes to unique sRivalBattleFlags
#define RIVAL_BATTLE_TUTORIAL    3  

#define WILD_DOUBLE_BATTLE ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER))))
#define BATTLE_TWO_VS_ONE_OPPONENT ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && gTrainerBattleOpponent_B == 0xFFFF))
#define BATTLE_TYPE_MORE_THAN_TWO_BATTLERS  (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_TWO_OPPONENTS)
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

//vsonic important use this for bringing counters etc
//into uq
//modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(gSpecialStatuses[battlerAtk].gemParam)));
//default stab is 1.5 keep in mind for other 1.5 mods if decide adjust

#define SUPER_EFFECTIVE     UQ_4_12(1.55)
#define NOT_VERY_EFFECTIVE  UQ_4_12(0.5)
#define NO_EFFECT           UQ_4_12(0.0)

#define JOAT_MULTIPLIER          UQ_4_12(1.17)
#define SAME_TYPE_MULTIPLIER     UQ_4_12(1.35)
//above should be hard coded
//below are meant to be approximates
//of how affects are handled in base game
//think will separate things out to keep for making formulae
//ex set 0.35 as same type bonus
//this is tera w stab not base tera
//and adaptability w stab well adaptability is only ever w stab
//but point is its not breaking out the individual effects
#define STELLAR_NON_STAB            UQ_4_12(1.2)
#define STELLAR_STAB_MULTIPLIER     SUPER_EFFECTIVE
#define TERA_STAB_MULTIPLIER        SUPER_EFFECTIVE
#define ADAPTABILITY_MULTIPLIER     SUPER_EFFECTIVE
#define TERA_MULTIPLIER             SAME_TYPE_MULTIPLIER
#define TERA_JOAT                   SAME_TYPE_MULTIPLIER

#define SAME_TYPE_BONUS             UQ_4_12(0.35)
#define TERA_BONUS                  SAME_TYPE_BONUS
#define ADAPTABILITY_BONUS          SAME_TYPE_BONUS

#define TERA_ADAPTABILITY_MUL   uq4_12_add(TERA_STAB_MULTIPLIER, uq4_12_divide(ADAPTABILITY_BONUS, 2))

//(fixed still keep note)
//...adaptability is stronger than super effective here
//realized my adaptability bonus is average of
//2 results using the multiplier formula
//I supposedly just came up with...

//ok idk how that got passed me that's a serious issue
//need to bring adaptability down... I'm so confused
//wtf didn't I just use the same value as super??? 

//sigh ok fixing that, now found made formula
//that makes sense as tera is psuedo stab
//gets same bonus as stab
//but when applied with adaptability 
//it takes half of the adaptability bonus
//for base game that's a 25% bonus added
//since difference between my stab
//and super is 20 points
//I instead will have a 10% bonus added from adaptability
//oh wait no ok rework think of adaptability bonus 
//as adding stab on top of stab
//stab is 50% and adaptability adds another 50%

//and tera adaptabiltiy is half of that bonus
//since tera is already applying psuedo stab bonus
//so that becomes a 25% additive bonus

//proportionality is there but I worry I don't make them
//impactful enough blah blah applying good jrpg logic
//smaller multipliers that work togther for impact


//ok continuing did that wrong
//my tera bonus wouldn't be 10%
//it'd be .35 / 2 = .175  or .17

//ok what I'm doing is translating my formula
//while also breakikng down the default formula

//my stab no longer equates half of the super multiplier
//but I'm still keeping the frame that
//stab + tera or adaptability should equal the super multiplier

//and from there stab tera with adaptability bonus
//should add half of stab since adaptability and tera are meant to be psudo stab
//so end result for me would be super + .17  rather than the + .25 base game uses


// Non-volatile status conditions
// These persist remain outside of battle and after switching out
#define STATUS1_NONE             0
//#define STATUS1_SLEEP            (1 << 0 | 1 << 1 | 1 << 2) // First 3 bits (Number of turns to sleep)
//#define STATUS1_SLEEP_TURN(num)  ((num) << 0) // Just for readability (or if rearranging statuses)
#define STATUS1_FROSTBITE		 (1 << 0) //planned bug status  //changed mind trouble w healthbox and or balance make status 2/4
#define STATUS1_SLEEP            (1 << 1)
#define STATUS1_POISON           (1 << 2)
#define STATUS1_BURN             (1 << 3)
#define STATUS1_FREEZE           (1 << 4)
#define STATUS1_PARALYSIS        (1 << 5)
#define STATUS1_TOXIC_POISON     (1 << 6)
//#define STATUS1_TOXIC_COUNTER    (1 << 8 | 1 << 9 | 1 << 10 | 1 << 11)
//#define STATUS1_TOXIC_TURN(num)  ((num) << 10)//redid toxic, put at original value, moved others
//decide remove spirit lock  - since I made a turn counter value realized dont need turn status at all?

//for update need add frostbite as a status
//rn is inverse of toxic in that 
//its not set when the timer is set
//it counts down rather than up
//will treat them similar makes sense
//when toxic poisoned at start of next battle is 
//set to regular poison
//ok will add frostbite set logic that
//freeze becomes frost bite when timer hits 0
//may turn spirit lock into a volatile staatus
//use sweet kiss angel devils as status symbol
//would be fairy status that lowers special dmg
//set only through randoms odds as kinda too many status effects already

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

//vsonic important
//use this for icon check to ensure not removed
//when downgrade to frostbite
#define STATUS1_FREEZE_OR_FROSTBITE (STATUS1_FREEZE | STATUS1_FROSTBITE)

#define STATUS1_PSN_ANY          (STATUS1_POISON | STATUS1_TOXIC_POISON)
//will need to go through and review all use of this variable since I've expanded status1
//laso cean up status definex

#define STATUS1_CAN_MOVE         (STATUS1_PSN_ANY | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_FROSTBITE)
#define STATUS1_INCAPACITATED    (STATUS1_SLEEP | STATUS1_FREEZE)
#define STATUS1_DAMAGING         (STATUS1_PSN_ANY | STATUS1_BURN | STATUS1_FREEZE_OR_FROSTBITE)


//status1_any seeems tobe used to check all status1 but exclude toxic counter values & sleep counter
#define STATUS1_ANY              (STATUS1_SLEEP | STATUS1_POISON | STATUS1_BURN | STATUS1_FREEZE | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON | STATUS1_FROSTBITE)

//with setup switchlock realize don't need to make these status1 for them to persist
//#define STATUS1_ENVIRONMENT_TRAP (STATUS1_FIRE_SPIN || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM)

//#define ITS_A_TRAP_STATUS1 (STATUS1_SNAP_TRAP || STATUS1_FIRE_SPIN || STATUS1_CLAMP || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM || STATUS1_SWARM || STATUS1_WRAPPED)

//all status2 and 4 done can remove

// Volatile status ailments
// These are removed after exiting the battle or switching out
//from what I see game is only set up to display status animations for status 1 & status2 staus...but then leech seed works and its status3?
//if everything works will most likely reorganize
//so free space is at the bottom
//realized this is a bit field
//if value takes 1 space then its bitfield 1
#define STATUS2_CONFUSION             (1 << 0)
#define STATUS2_SPIRIT_LOCK             (1 << 1) //vsonic fairy status moved here special dmg drop
#define STATUS2_INFESTATION           (1 << 2)
//#define STATUS2_CONFUSION_TURN(num)   ((num) << 0)
#define STATUS2_FLINCHED              (1 << 3)
#define STATUS2_UPROAR                (1 << 4)
#define STATUS2_DRAGON_RAGE           (1 << 5)  //move these blanks to end weird to have them at start
#define STATUS2_NOTHING               (1 << 6)
//#define STATUS2_UPROAR_TURN(num)      ((num) << 4)
#define STATUS2_EMERGENCY_EXIT        (1 << 7)	//use for emergency exit
#define STATUS2_BIDE                  (1 << 8)
#define STATUS2_SWITCH_LOCKED         (1 << 9)// new status for spirit shackle, escape prevention on a timer, not locked to battler
//#define STATUS2_BIDE_TURN(num)        (((num) << 8) & STATUS2_BIDE)
#define STATUS2_LOCK_CONFUSE          (1 << 10) // e.g. Thrash
#define STATUS2_SKY_ATTACK            (1 << 11)
//#define STATUS2_LOCK_CONFUSE_TURN(num)((num) << 10) //this isn't the confusion effect this is how many turns outrage/thrash/petal dance lasts which should be 2-3 turns
#define STATUS2_MULTIPLETURNS         (1 << 12) //wrapped is wrap & bide  / separting just wrap, think plan put wrap into status4 so all traps together
#define STATUS2_WRAPPED               (1 << 13)	//make individual wrapped for each, but all use same wrap turn counter / cant usesame counter and multi trap so this will just be wrap
//#define STATUS2_WRAPPED_TURN(num)     ((num) << 13)	//left shift value is starting point of status wrapped
#define STATUS2_POWDER                (1 << 14)
#define STATUS2_FREE_SPACE            (1 << 15)
#define STATUS2_INFATUATION           (1 << 16)  // further reworking, plan only fails to attack w target attract battler, otherwise lower dmg long as attracted mon is on field
#define STATUS2_FREE_SPACE_1          (1 << 17)
#define STATUS2_FREE_SPACE_2          (1 << 18)
#define STATUS2_FREE_SPACE_3          (1 << 19)
#define STATUS2_FOCUS_ENERGY          (1 << 20)//think can save 3 if I setup like I did leech seed -ok done
#define STATUS2_TRANSFORMED           (1 << 21)
#define STATUS2_TWOTURN_INTERRUPT        (1 << 22) //INTERUPTS semi invulnerable moves   removing recharge as a status, as all of its logic can be done w the timer...
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
//figure this out decide if use all escape prevention, well idea is movement is restricted
//so yeah guess that tracks
//think should remove flinch?
//it activates typically after attacked,
//and is removed on attack so it would never really be noticed
//STATUS2_SWITCH_LOCKED unsure if should add think should

// Seems like per-battler statuses. Not quite sure how to categorize these
//#define STATUS3_SKY_DROPPED             0x1 // Target of Sky Drop
#define STATUS3_FREESPACE               (1 << 0)//REPLACED The battler to receive HP from Leech Seed
#define STATUS3_PLACEHOLD               (1 << 1)
#define STATUS3_CLEARED                 (1 << 2)   //redone use specila staatus as turn count 
#define STATUS3_FIXATED                 (1 << 3)  //idea from legens arceus use a move becomes fixated on it, doing some other affect on reuse,
#define STATUS3_LEECHSEED                (1 << 4) //is leech seeded status, doesn't store battler with status
#define STATUS3_ALWAYS_HITS             (1 << 5 | 1 << 6)    // two bits
#define STATUS3_ALWAYS_HITS_TURN(num)   (((num) << 5) & STATUS3_ALWAYS_HITS) // "Always Hits" is set as a 2 turn timer, i.e. next turn is the last turn when it's active
#define STATUS3_PERISH_SONG             (1 << 7)
#define STATUS3_ON_AIR                  (1 << 8)
#define STATUS3_UNDERGROUND             (1 << 9)
#define STATUS3_MINIMIZED               (1 << 10)
#define STATUS3_CHARGED_UP              (1 << 11)
#define STATUS3_ROOTED                  (1 << 12) //if I understand correctly, change gives extra statur 3 space 12 would be unused
#define STATUS3_YAWN                    (1 << 13) // Number of turns to sleep
//#define STATUS3_YAWN_TURN(num)          (((num) << 11) & STATUS3_YAWN)//  changing set status yawn, then at end turn check for it, if there remove and put to sleep
#define STATUS3_ME_FIRST                (1 << 14) //use for commander gen9, then roll into semi invul
#define STATUS3_IMPRISONED_OTHERS       (1 << 15)
#define STATUS3_GRUDGE                  (1 << 16)
#define STATUS3_CANT_SCORE_A_CRIT       (1 << 17) //never actually set
#define STATUS3_GASTRO_ACID             (1 << 18)	//is there any reaso this needs to be status3 rather than a status 2?
//#define STATUS3_EMBARGO                 (1 << 17)	//move to side status to make room
#define STATUS3_SMACKED_DOWN            (1 << 19)
//#define STATUS3_MUDSPORT                (1 << 16)	//can move these 2 to side status?
//#define STATUS3_WATERSPORT              0x20000	//(1 << 17) //remove sports later
#define STATUS3_UNDERWATER              (1 << 20)
#define STATUS3_INTIMIDATE_POKES        (1 << 21)
#define STATUS3_TRACE                   (1 << 22)

//I put in disablestruct so idk why I still have therse statuses here?
//moved ingrain and aqua ring logic to disable structs freed up space
//also moved all freed values to front for clarity


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

#define STATUS3_SEMI_INVULNERABLE       (STATUS3_ON_AIR | STATUS3_UNDERGROUND | STATUS3_UNDERWATER | STATUS3_PHANTOM_FORCE)

#define STAUS3_VULNERABLE (STATUS3_ROOTED | STATUS3_YAWN)

//signature of heliolisk, for move electrify
//similar to plasma fist effect but for target
#define STATUS4_ELECTRIFIED             (1 << 0)	//need to check how status4 is setup to make sure it runs on same conditions as status2
//if it works I can move wrap status and wrap counter up here so it all uses status4
//start of new trap effects, each will have its own status and timer in disable structs
#define STATUS4_SYRUP_BOMB              (1 << 1)
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

//compare w my own stuff to adjust
//potentially remove things that
//are moved to side status
//nah just keep timers and use those
//a hard define is good for preventing 
//manual input mistakes
//ok so these are meant to only stand for max value
//where they are actually set timer
//they do random stuff etc. as needed
//for things that shifted w gen like uproar
//think will just lower value
//but dont understand why rampage uses 4
//when timer well gen 1 timer was 3-4 so potentially that
//ok can't mess with this need answer on how volatile struct works
//the max values are confusing are they bit fields
//oh yeah the struct does say it makes bitfield
//its annoying to read but the macro makes bitfields
//based on what is set for max value  I think
//sure would be great if that was explained anywhere...
//ok so need add my own struct to not break things optimization i mean
//think will need adjust to match my values for optimization
// Various volatile timers
#define B_CONFUSION_TURNS    5
#define B_UPROAR_TURN_COUNT  5
#define B_RAMPAGE_TURNS      3
#define B_BIDE_TURNS         3 //Why didn't this exist, changed idk if need I  add 1 turn to bide
#define B_DISABLE_TIMER      4
#define B_ENCORE_TIMER       4
#define B_PERISH_SONG_TIMER  3
#define B_TAUNT_TIMER        5
#define B_SLOW_START_TIMER   5 //remove this later
#define B_EMBARGO_TIMER      5
#define B_MAGNET_RISE_TIMER  5
#define B_TELEKINESIS_TIMER  3
#define B_HEAL_BLOCK_TIMER   5
#define B_LASER_FOCUS_TIMER  2
#define B_THROAT_CHOP_TIMER  2
#define B_WRAP_TURNS         7 // Max number of turns with Grip Claw
#define B_SYRUP_BOMB_TIMER   3
#define B_TORMENT_TIMER      3
#define B_DESTINY_BOND       2  //Don't Change -value of 2 needed for gen 7 config to block successive use of Destiny Bond
#define B_ROOST_TIMER        4  //pretty sure I added but double check mathes my effect
#define B_TRENCH_RUN_TIMER   4
#define B_FREEZE_TURNS       3 //should mean 2 turns of freeze solid
#define B_SWITCH_BIND_TURNS  2 //should be target stuck in for one turn after use make sure remove when == 0
#define B_FIXATION_TURNS     3 //to track that fixation move is being repeated max value 3?
#define B_TIME_CONTROL_TIMER 2 //for dialga stay 0, set to 2 when use that should actiavte it,and decrement only if non zero in end turn
#define B_ASCENSION_TIMER    3 //for flying type recover from smack down think shoud be 2 turns in effect? //counter balance and unique effect of type

//Ability Timers
#define SLOW_START_TIMER 3
#define WONDER_GUARD_TIMER 5
#define SPECTRE_TIMER 2

#define MAX_INGRAIN_AQUA_RING_TURNS    6 //turns healing effect stacks
#define MAX_TOXIC_TURNS 16
#define MAX_CONFUSION_TURNS 5
#define MAX_SLEEP_TURNS 5
#define MAX_RAGE_BOOST_COUNTER 5
#define MAX_DRAGON_RAGE_COUNTER 5
#define MAX_OCTOLOCK_TURNS 4

enum VolatileFlags
{
    V_BATON_PASSABLE = (1 << 0),
};

//bring over infatuatedwithbattlerId
//remove wrappedby and wrappedmove
//don't see enum elsewhere so guess it creates enum 
//here based on name used

//order of below was staus2 flags etc.
//hence unsued was unused space
//think will need to redo even these top ones
//to match my status2 stuff otherwise won't be optimized right

//ok now understand max value becomes bitfield
//using some log method I don't understand
//it auto translates the given max value
//to the minimum bit field value needed to hold it,
//great for preventing overflow
//absolutely horrid for readability...
//ok so formula for max value of given bit is
//2^bit - 1  ex. 2^1 = 2 stores 2 values 0 & 1,  - 1 = 1 max value is 1

//explained to me by mgriffin
/*
 the formula for volatile max value to bit field translation is log2

 If there's n values (e.g. 0 to 2 inclusive is n=3) then you need ceiling(log2(n)) bits. 
 If your calculator doesn't have log2 you can do log(n+1) / log(2).

e.g. in Python:
>>> import math
>>> {x: math.ceil(math.log(x) / math.log(2)) for x in range(1, 6)}
{1: 0, 2: 1, 3: 2, 4: 2, 5: 3}

1 value requires 0 bits, 2 values requires 1 bit, 3/4 values requires 2 bits, 5 requires 3 bits, etc.
You can equivalently think of this via powers of 2 (log2(2^x) == x).
2^0 = 1, 2^1 = 2, 2^2 = 4, etc. 
So with 0 bits you can hold 1 value, 
with 1 bit you can hold up to 2 values, 
with 2 bits you can hold up to 4 values, etc. 


running log2 on maxvalue of 3 gives
1.5849625007211561814537389439478
which tells me it can't be stored in 1 bit
ceiling then accounts for it scaling up to use 2 bits

as 2^2 can hold 4 values and store max value of 3
max value of bit is 2^n -1

*/

/*
    +1 added to volatile timers and some values seen here as extra precaution 
    to help ensure large enough bit field is allocated for said value
    as log2 may mistakenly allocated lower than we need
    ex timer of max value 2 would need bit 2
    but log2(2) would instead allocate 1 bit

    same for max value 4, needs 3 bits
    but log2(4) would allocate 2 bits instead.
*/

//MAX_BITS(MAX_BATTLERS_COUNT) seems to return a  value of 15
//so I guess bit:4
//which I don't really get normally I'd use a byte u8 with array[4]
//to store value for each potential battler
//but if broken into a field at max it stores value between 0-3
//but has to store 4 of those
//that's bit 2 stores 4 values so 4 x 4 values is 16 values
//so techncially same space I guess but feels weird

/*Notes*(changes custom removed transformpid reworked transform logic)
rechargeTimer can use bit 1 value 1
I put decrement in atk cancler rather than end turn
just need to finish getting my new values added
will worry about optimization later
since I have my comparison repo setup
I can just bring over all files at once
and just update things one by one

sinec swapped EE to upcoming and it removed disable structs
will need to back port some of the more recent changes
I made here to EE's upcoming mostly
just things dealing with absorb logic and I guess
infatuation again
*/

//infatuation stores Pid to correctly catch mon shold be infatuated with

/* Volatile status ailments
 * These are removed after exiting the battle or switching
 *  Enum,                                   Type                           Type, max value, flags */
#define VOLATILE_DEFINITIONS(F) \
    F(VOLATILE_INFATUATION,                 infatuatedwithMon,             (u32, UINT32_MAX)) \
    F(VOLATILE_CONFUSION,                   confusionTurns,                (u32, B_CONFUSION_TURNS + 1), V_BATON_PASSABLE) \
    F(VOLATILE_INFESTATION,                 infested,                      (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_FLINCHED,                    flinched,                      (u32, 1)) \
    F(VOLATILE_UPROAR,                      uproarTurns,                   (u32, 3)) \
    F(VOLATILE_DRAGON_RAGE,                 dragonrage,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_EMERGENCY_EXIT,              emergencyExit,                 (u32, 1)) \
    F(VOLATILE_TORMENT,                     torment,                       (u32, 1)) \
    F(VOLATILE_BIDE,                        bideTurns,                     (u32, B_BIDE_TURNS)) \
    F(VOLATILE_RAMPAGE_TURNS,               rampageTurns,                  (u32, B_RAMPAGE_TURNS)) \
    F(VOLATILE_DRAGON_RAGE_COUNTER,         dragonrageCounter,             (u32, MAX_DRAGON_RAGE_COUNTER), V_BATON_PASSABLE) \
    F(VOLATILE_MULTIPLETURNS,               multipleTurns,                 (u32, 1)) \
    F(VOLATILE_WRAPPED,                     wrapped,                       (u32, 1)) \
    F(VOLATILE_POWDER,                      powder,                        (u32, 1)) \
    F(VOLATILE_TWOTURN_INTERRUPT,           twoturnInterupt,               (u32, 1)) \
    F(VOLATILE_INVERSION_TRAMSFORM,         inversionTransformed,          (u32, 1)) \
    F(VOLATILE_DEFENSE_CURL,                defenseCurl,                   (u32, 1)) \
    F(VOLATILE_TRANSFORMED,                 transformed,                   (u32, 1)) \
    F(VOLATILE_RAGE,                        rage,                          (u32, 1)) \
    F(VOLATILE_SUBSTITUTE,                  substitute,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_DESTINY_BOND,                destinyBond,                   (u32, B_DESTINY_BOND + 1)) \
    F(VOLATILE_ESCAPE_PREVENTION,           escapePrevention,              (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_NIGHTMARE,                   nightmare,                     (u32, 1)) \
    F(VOLATILE_CURSED,                      cursed,                        (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_FORESIGHT,                   foresight,                     (u32, 1)) \
    F(VOLATILE_DRAGON_CHEER,                dragonCheer,                   (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_FOCUS_ENERGY,                focusEnergy,                   (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_SEMI_INVULNERABLE,           semiInvulnerable,              (u32, SEMI_INVULNERABLE_COUNT)) \
    F(VOLATILE_ELECTRIFIED,                 electrified,                   (u32, 1)) \
    F(VOLATILE_SALT_CURE,                   saltCure,                      (u32, 1)) \
    F(VOLATILE_SYRUP_BOMB,                  syrupBomb,                     (u32, 1)) \
    F(VOLATILE_STICKY_SYRUPED_BY,           stickySyrupedBy,               (enum BattlerId, MAX_BITS(MAX_BATTLERS_COUNT))) \
    F(VOLATILE_GLAIVE_RUSH,                 glaiveRush,                    (u32, 1)) \
    F(VOLATILE_LOCK_ON,                     lockOn,                        (u32, 2), V_BATON_PASSABLE) \
    F(VOLATILE_LEECH_SEED,/*store user pos*/leechSeed,                     (enum BattlerId, MAX_BITS(MAX_BATTLERS_COUNT)), V_BATON_PASSABLE) \
    F(VOLATILE_PERISH_SONG,                 perishSong,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_FIXATED,                     fixated,                       (u32, 1)) \
    F(VOLATILE_CHARGE_TIMER,                chargeTimer,                   (u32, 3)) \
    F(VOLATILE_ROOT,                        rooted,                        (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_YAWN,                        yawn,                          (u32, 1)) \
    F(VOLATILE_IMPRISON,                    imprison,                      (u32, 1)) \
    F(VOLATILE_GRUDGE,                      grudge,                        (u32, 1)) \
    F(VOLATILE_GASTRO_ACID,                 gastroAcid,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_STURDY_HUNG_ON,              sturdyhungon,                  (u32, 1))  \
    F(VOLATILE_SMACK_DOWN,                  smackDown,                     (u32, 1)) \
    F(VOLATILE_TELEKINESIS,                 telekinesis,                   (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_MIRACLE_EYE,                 miracleEye,                    (u32, 1)) \
    F(VOLATILE_MAGNET_RISE,                 magnetRise,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_AQUA_RING,                   aquaRing,                      (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_LASER_FOCUS,                 laserFocus,                    (u32, 1)) \
    F(VOLATILE_POWER_TRICK,                 powerTrick,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_BIND,/*unsure bataonpass*/   bind,                          (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_FIRE_SPIN,                   firespin,                      (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_CLAMP,                       clamp,                         (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_WHIRLPOOL,                   whirlpool,                     (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_SAND_TOMB,                   sandtomb,                      (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_MAGMA_STORM,                 magmaStorm,                    (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_SWARM,                       swarm,                         (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_SNAP_TRAP,                   snaptrap,                      (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_THUNDER_CAGE,                thundercage,                   (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_NO_RETREAT,                  noRetreat,                     (u32, 1), V_BATON_PASSABLE) \
    F(VOLATILE_VESSEL_OF_RUIN,              vesselOfRuin,                  (u32, 1)) \
    F(VOLATILE_SWORD_OF_RUIN,               swordOfRuin,                   (u32, 1)) \
    F(VOLATILE_TABLETS_OF_RUIN,             tabletsOfRuin,                 (u32, 1)) \
    F(VOLATILE_BEADS_OF_RUIN,               beadsOfRuin,                   (u32, 1)) \
    F(VOLATILE_IS_TRANSFORMED_MON_SHINY,    isTransformedMonShiny,         (u32, 1)) \
    F(VOLATILE_DISABLED_MOVE,               disabledMove,                  (u32, MOVES_COUNT_ALL)) \
    F(VOLATILE_ENCORED_MOVE,                encoredMove,                   (u32, MOVES_COUNT_ALL)) \
    F(VOLATILE_PROTECT_USES,                protectUses,                   (u32, UINT8_MAX)) \
    F(VOLATILE_BIND_MOVE_POS,               bindMovepos,                   (u32, MAX_BITS(MAX_MON_MOVES))) \
    F(VOLATILE_BINDED_MOVE,                 bindedMove,                    (u32, MOVES_COUNT_ALL)) \
    F(VOLATILE_INTHRALL,                    inthrallTimer,                 (u32, 3)) \
    F(VOLATILE_INTHRALLED_MOVE,             inthralledMove,                (u32, MOVES_COUNT_ALL)) \
    F(VOLATILE_STOCKPILE_COUNTER,           stockpileCounter,              (u32, MAX_STAT_STAGE)) \
    F(VOLATILE_STOCKPILE_DEF,               stockpileDef,                  (u32, MAX_STAT_STAGE)) \
    F(VOLATILE_STOCKPILE_SP_DEF,            stockpileSpDef,                (u32, MAX_STAT_STAGE)) \
    F(VOLATILE_STOCKPILE_BEFORE_DEF,        stockpileBeforeDef,            (u32, MAX_STAT_STAGE)) \
    F(VOLATILE_STOCKPILE_BEFORE_SP_DEF,     stockpileBeforeSpDef,          (u32, MAX_STAT_STAGE)) \
    F(VOLATILE_INGRAIN_TURN,                ingrainTurn,                   (u32, MAX_INGRAIN_AQUA_RING_TURNS), V_BATON_PASSABLE) \
    F(VOLATILE_AQUA_RING_TURN,              aquaringTurn,                  (u32, MAX_INGRAIN_AQUA_RING_TURNS), V_BATON_PASSABLE) \
    F(VOLATILE_RAGE_COUNTER,                rageCounter,                   (u32, MAX_RAGE_BOOST_COUNTER)) \
    F(VOLATILE_SUBSTITUTE_HP,               substituteHP,                  (u32, UINT8_MAX)) \
    F(VOLATILE_ENCORED_MOVE_POS,            encoredMovePos,                (u32, MAX_BITS(MAX_MON_MOVES))) \
    F(VOLATILE_DISABLE_TIMER,               disableTimer,                  (u32, B_DISABLE_TIMER)) \
    F(VOLATILE_ENCORE_TIMER,                encoreTimer,                   (u32, B_ENCORE_TIMER)) \
    F(VOLATILE_PERISH_SONG_TIMER,           perishSongTimer,               (u32, B_PERISH_SONG_TIMER)) \
    F(VOLATILE_ROLLOUT_TIMER,               rolloutTimer,                  (u32, UINT8_MAX)) \
    F(VOLATILE_FURY_CUTTER_COUNTER,         furyCutterCounter,             (u32, UINT8_MAX)) \
    F(VOLATILE_METRONOME_ITEM_COUNTER,      metronomeItemCounter,          (u32, UINT8_MAX)) \
    F(VOLATILE_BATTLER_PREVENTING_ESCAPE,   battlerPreventingEscape,       (enum BattlerId, MAX_BITS(MAX_BATTLERS_COUNT))) \
    F(VOLATILE_BATTLER_WITH_SURE_HIT,       battlerWithSureHit,            (enum BattlerId, MAX_BITS(MAX_BATTLERS_COUNT))) \
    F(VOLATILE_MIMICKED_MOVES,              mimickedMoves,                 (u32, MAX_BITS(MAX_MON_MOVES))) \
    F(VOLATILE_RECHARGE_TIMER,              rechargeTimer,                 (u32, 2)) \
    F(VOLATILE_AUTOTOMIZE_COUNT,            autotomizeCount,               (u32, UINT8_MAX)) \
    F(VOLATILE_OCTOLOCK_COUNTER,            octolockCounter,               (u32, MAX_OCTOLOCK_TURNS)) \
    F(VOLATILE_MAGNET_RISE_TIMER,           magnetRiseTimer,               (u32, B_MAGNET_RISE_TIMER)) \
    F(VOLATILE_TELEKINESIS_TIMER,           telekinesisTimer,              (u32, B_TELEKINESIS_TIMER)) \
    F(VOLATILE_TAUNT_TIMER,                 tauntTimer,                    (u32, B_TAUNT_TIMER)) \
    F(VOLATILE_TORMENT_TIMER,               tormentTimer,                  (u32, B_TORMENT_TIMER)) \
    F(VOLATILE_LASER_FOCUS_TIMER,           laserFocusTimer,               (u32, B_LASER_FOCUS_TIMER)) \
    F(VOLATILE_THROAT_CHOP_TIMER,           throatChopTimer,               (u32, B_THROAT_CHOP_TIMER)) \
    F(VOLATILE_WRAP_TURNS,                  wrapTurns,                     (u32, B_WRAP_TURNS)) \
    F(VOLATILE_BIND_TURNS,                  bindTurns,                     (u32, B_WRAP_TURNS)) \
    F(VOLATILE_CLAMP_TURNS,                 clampTurns,                    (u32, B_WRAP_TURNS)) \
    F(VOLATILE_SWARM_TURNS,                 swarmTurns,                    (u32, B_WRAP_TURNS)) \
    F(VOLATILE_SNAPTRAP_TURNS,              snaptrapTurns,                 (u32, B_WRAP_TURNS)) \
    F(VOLATILE_THUNDERCAGE_TURNS,           thundercageTurns,              (u32, B_WRAP_TURNS)) \
    F(VOLATILE_ENVIRONMENTRAP_TURNS,        environmentTrapTurns,          (u32, B_WRAP_TURNS)) \
    F(VOLATILE_SYRUP_BOMB_TIMER,            syrupBombTimer,                (u32, B_SYRUP_BOMB_TIMER)) \
    F(VOLATILE_USED_MOVES,                  usedMoves,                     (u32, MAX_BITS(MAX_MON_MOVES))) \
    F(VOLATILE_TRUANT_COUNTER,              truantCounter,                 (u32, 1)) \
    F(VOLATILE_TRUANT_SWITCH_IN_HACK,       truantSwitchInHack,            (u32, 1)) \
    F(VOLATILE_TAR_SHOT,                    tarShot,                       (u32, 1)) \
    F(VOLATILE_OCTOLOCK,                    octolock,                      (u32, 1)) \
    F(VOLATILE_CUD_CHEW,                    cudChew,                       (u32, 1)) \
    F(VOLATILE_DEFEATIST_ACTIVATED,         defeatistActivated,            (u32, 1)) \
    F(VOLATILE_WEATHER_ABILITY_DONE,        weatherAbilityDone,            (u32, 1)) \
    F(VOLATILE_TERRAIN_ABILITY_DONE,        terrainAbilityDone,            (u32, 1)) \
    F(VOLATILE_SYRUP_BOMB_IS_SHINY,         syrupBombIsShiny,              (u32, 1)) \
    F(VOLATILE_EMERGENCY_WIMPOUT_ACTIVE,    EmergencyExitWimpoutActive,    (u32, 1)) \
    F(VOLATILE_FLASH_FIRE_BOOSTED,          flashFireBoosted,              (u32, 1)) \
    F(VOLATILE_BOOSTER_ENERGY_ACTIVATED,    boosterEnergyActivated,        (u32, 1)) \
    F(VOLATILE_OVERWRITTEN_ABILITY,         overwrittenAbility,            (u32, ABILITIES_COUNT)) \
    F(VOLATILE_ROOST_TIMER,                 roostTimer,                    (u32, B_ROOST_TIMER)) \
    F(VOLATILE_UNBURDEN_ACTIVE,             unburdenActive,                (u32, 1)) \
    F(VOLATILE_NEUTRALIZING_GAS,            neutralizingGas,               (u32, 1)) \
    F(VOLATILE_IMMUTABLE_WIND,              immutableWind,                 (u32, 1)) \
    F(VOLATILE_TRIGGER_ICE_FACE,            triggerIceFace,                (u32, 1)) \
    F(VOLATILE_UNNERVE_ACTIVATED,           unnerveActivated,              (u32, 1)) \
    F(VOLATILE_ENDURED,                     endured,                       (u32, 1)) \
    F(VOLATILE_TRY_EJECT_PACK,              tryEjectPack,                  (u32, 1)) \
    F(VOLATILE_OCTOLOCKED_BY,               octolockedBy,                  (enum BattlerId, MAX_BITS(MAX_BATTLERS_COUNT))) \
    F(VOLATILE_PARADOX_BOOSTED_STAT,        paradoxBoostedStat,            (u32, NUM_STATS)) \
    F(VOLATILE_UNABLE_TO_USE_MOVE,          unableToUseMove,               (u32, 1))    \
    F(VOLATILE_CAUGHT_MON,                  caughtMon,                     (u32, 1))  \
    F(VOLATILE_EMERGENCYEXIT_TIMER,         emergencyExitTimer,            (u32, 1))  \
    F(VOLATILE_TRENCH_RUN_TIMER,            trenchRunTimer,                (u32, B_TRENCH_RUN_TIMER))  \
    F(VOLATILE_FROZEN_TURNS,                frozenTurns,                   (u32, 2))  \
    F(VOLATILE_SLEEP_COUNTER,               sleepCounter,                  (u32, 1))  \
    F(VOLATILE_SLEEPCOUNT_SWITCH_IN_HACK,   sleepCountSwitchInHack,        (u32, 1))  \
    F(VOLATILE_FOREWARNED_BATTLER,          forewarnedBattler,             (u32, enum BattlerId, MAX_BITS(MAX_BATTLERS_COUNT)))  \
    F(VOLATILE_ANTICIPATIONFOREWARN_DONE,   anticipationForewornIsDone,    (u32, 1))  \
    F(VOLATILE_ACTIVATED_WEIGHTED_GI,       activatedWeightedGi,           (u32, 1))  \
    F(VOLATILE_SWITCHBIND_TIMER,            switchBindtimer,               (u32, B_SWITCH_BIND_TURNS), V_BATON_PASSABLE)  \
    F(VOLATILE_TRAPPED_IN_STICKY_WEB,       trappedinStickyweb,            (u32, 1))  \
    F(VOLATILE_STATUSED_VIA_MOLDBREAKER,    statusedViaMoldBreaker,        (u32, 1))  \
    F(VOLATILE_FIXATION_TURNS,              fixationTurns,                 (u32, B_FIXATION_TURNS))  \
    F(VOLATILE_FIXATED_MOVE,                fixatedMove,                   (u32, MOVES_COUNT_ALL))  \
    F(VOLATILE_FIRSTURN_ABILITY_CHECK,      isFirstTurnAbilityActive,      (u32, 1))  \
    F(VOLATILE_TIME_CONTROL,                timecontrolAbilityTimer,       (u32, B_TIME_CONTROL_TIMER))  \
    F(VOLATILE_TRAPPED_VIA_MOLDBREAKER,     trapSetViaMoldBreaker,         (u32, 1))  \
    F(VOLATILE_BIDE_STATUS,                 bide,                          (u32, 1))  \
    F(VOLATILE_ASCENSION_TIMER,             ascensionTimer,                (u32, B_ASCENSION_TIMER))  \


/* Use within a macro to get the maximum allowed value for a volatile. Requires _typeMaxValue as input. */
#define GET_VOLATILE_MAXIMUM(_typeMaxValue, ...) INVOKE_WITH_B(GET_VOLATILE_MAXIMUM_, _typeMaxValue)
#define GET_VOLATILE_MAXIMUM_(_type, ...) FIRST(__VA_OPT__(FIRST(__VA_ARGS__),) MAX_BITS((sizeof(_type) * 8)))

#define UNPACK_VOLATILE_ENUMS(_enum, ...) _enum,

enum Volatile
{
    VOLATILE_NONE,
    VOLATILE_DEFINITIONS(UNPACK_VOLATILE_ENUMS)
    /* Expands to VOLATILE_CONFUSION, VOLATILE_FLINCHED, etc. */
};
//NOTE REMOVED libero protean check for EmergencyExitWimpoutActive

enum SemiInvulnerableState
{
    STATE_NONE,
    STATE_UNDERGROUND,
    STATE_UNDERWATER,
    STATE_ON_AIR,
    STATE_PHANTOM_FORCE,
    STATE_SKY_DROP,
    STATE_COMMANDER, //unsure if need make separate one for battery, functionally the same
    SEMI_INVULNERABLE_COUNT,
};

enum SemiInvulnerableExclusion
{
    CHECK_ALL,
    EXCLUDE_COMMANDER,
};

//vsonic important remmber bit fields can store max 2^bit value
//ex bit 3  :3 is 2^3 = 8 can store 8 values between 0-7
//vsonic important disablestruct no longer exists
//set in volatiles and volatiles is in battlemon
//remove value that already exist on the list then copy over the line
//to regex to fit it in,
//wha will do is make an enum from the existing name fix by hand later
// and handle the type after
//finished adding all values just need update volatile name
//optimization will come later

    //only stores inversion see if need or
    //other value can suffice rn thinking
    //just do enum instead fo ability store
    //just do bool was able to fit into existing space of table
    //u16 transformedViaAbility; //story ability if used ability to transform, for properly showing shininess of sprite

    //counter here just for note
    //hmm maybe I can just use gmultihitcounter instead?
    //yeah should work since effect wasn't multi hit before
    //wasn't even really noticed but this move had effect
    //where the animation would flip each attack
    //as if attack was truly successive and coming from diff directions
    /*0x10*/ //u8 furyCutterCounter;  //apparently still need for anim task in anim_effects_2  //for some reason task is broken not switching hits

            //look into what this was again
             //u8 caughtMon : 1; //group  //idk what for using now for pc caught setup, since clears on switch shouldn't cause issues?
             ///u8 caughtMon : 1;
             //u8 EmergencyExitTimer:1;
             //u8 frozenTurns:2; //group  //made w sleep timer and stockpile together in mind
             //u8 truantCounter : 1;
             //u8 sleepCounter : 1; //copy of truant counter used for sleep heal may need copy switch hack as well hmm
             //u8 truantSwitchInHack : 1; // unused? 
    /*0x18*/ 
    //u8 toxicTurn; //wit change to statusnig will need move aqua ring ingrain and toxic turn counters to differnet way

    //is trap effect like wrap etc. other effects persist on switch
    //but idea is physically wrapped around target
    //but that doesn't matter as much since can be used on multiple targes
    //but effect is drop defense stats each turn of effect
    //so kinda op hmm a lock is meant to lockdown someones method of attack
    //which I guess is also reason for why it drops defenses as they can't
    //move to protect themselves
    //ok think what I can do to make this work (for graploct)
    //is make it differ from other wrap effects i.e
    //this one requires staying in, but to facilitate that
    //it lowers physical attack of trapped foe just like
    // the other traps have an effect for the duration of lowering speed
    //and as counter balance when freed defenes get reset back to normal
    //also need prevent from multi set so I need
    //both an octolock status AND an octolock timer
    //ah I see the problem this move doesn't have a timer
    //it just lasts until user switches or dies...
    //that's crazy, on a better pokemon this would be broken
    //ok so will need a timer AND a turn counter for this effect smh
    //well no maybe could just use timer can store max octolock turn count value
    //and subtract actual timer on effect end from max value to determine 
    //how far stats fell and how much they should be offset by
    //meaning I'd just need a status and a timer
    //anyway I'm thinking make value 4 turn move so at max
    //stats fall 3 stages
    //but then again getting a 3 strage drop even if for one turn is a lot
    //heck 2 stages is a lot maybe drop stats every 2 turns?
    //so you get the attack drop for duration
    //and defeses drop on first turn end
    //then on 3rd turn end it falls to 2 stage defense drop
    //which would last for a single turn and then end and get reset...
    //no combined with trapping on field that's still to much
    //main issue is ttk dropping defenses so much means a guaranteed kill
    //ok think just need a full rework, swap effect to offenses instead
    //doesn't fully make sense but it effecting sp def didn't make sense either -_-
    //ok so we have a 4 turn effect that drops offense stats each turn
    //yeah that's too much as well just do uhh first phase of rework
    //stats will drop every 2 turns, giving 1 turn
    //of the double drop before effect ends and everything resets
    //4 turns seems good
    //stat drop would occur at end of first turn
    //and be in effect for turn count 1 and 2
    //and end of second turn would set stat ot 2 stage drop
    //so for reset I just get timer if less than 2 raise stats 1 stage
    //else raise stats 2 stages
    //will change octoloc to counter not timer since goes up to 4
    //ALRIGHT DONE was able to replace slow start timer w effect I need
    //u8 octolock : 1; 

        //similar to roost plan was fly low
    //but becomes harder to track
    //so becomes grouded but gets a 2 stage evasion boost
    //doesn't "fully" make sense as still flying above ground
    //so an earthquake or fissure shouldn't effect it
    //but necessary extrapolation for balance
    //point is its on the same lane as pokemon that float
    //but can't fly and so are still hit by ground effects
    //ex geodude
    //u8 trenchRunTimer:3; //timer for trench run, 4 turns end turn decrement
    //kept here for note
    //u8 environmentTrapTurns;   //turn counter for environment traps fire spin whirlpool sandtomb magma storm
    

    //keep here for now is single use ability
    //but need make sure effect works right
    //only should work first turn but don't want to just work on any battler
    //if the battler switches first turn excepting foreworn which beleive
    //is stil tied to a specific move it shouldn't still work
    //pretty much only worry is if that switch turn would still be 
    //within timeframe of effect it shouldn't be but want to make sure
    //if I link it ot battler first turn a switched mon would still 
    //be caught in effect so may instad need to make hard timer
    //both are single use abilities could just give them timer value of 1
    //and that would work just fine
    //well they are a bit different singleu use is about activation
    //meaning ability activates once and has once timer
    //to prevent reactivation
    //forewarna and anticipation are different
    //they are broken if an entire team used just that
    //even with each mon only allowed one use of it
    //so plan for that is ability itself can only be
    //activated once per battle regardless of if more mon have it
    //think add new ability struct field for abilities
    //can put timer field on abilities
    //as well if the ability is singleActivation
    //or singleUse need better names
    //but point is if ability is singleUse
    //it can activate setusedsingleuseability from that
    //rather than me needing to keep a list of them
    //and pull timer from that as well
    //now for abilities that can only be active for one mon on team
    //can call those RestrcitedAbilities
    //can set a count for how many mon ability is restricted to
    //if it is restricted at all
    //i.e field isRestrictedAbility = 1  = 2  etc
    //but for 4 party things like battle towers
    //would want value to be 1 for every ability regardless
    //would need add usedRestrictedAbility to partyState check
    //same as us single use stores ability id
    //forewarn and anticipation are linked
    //so think best I can do is make function specific for them
    //canactivateforewornantipcation 
    //and it'd check if party member had already
    //used antipcation or forewarn as their restricted
    //would be after first restricted check
    //since this is checking 2 diff abilities not just
    //if ability itself is on list

    
    
    //hmm think this is more or less same issue of coding
    //vs game engine that just simplifies actions
    //that said idk why these things don't have both versions
    //any effect that is programmed is written in code somewhere
    //there should just be an advanced option that allows
    //coders to go in and add functionality themselves
    //and non programmers can just use the ui elements to edit
    //it sounds simple so idk why it isn't that way
    //orther than just control, if the source code is available
    //theoretically people could just strip it all out and get the beneift
    //but that still seems dumb
    
    //u8 forewarnedBattler;
    //u8 AnticipationForewornIsDone;    //for storing move from anticipation ability, may remove to make room for fixation logic
    //u8 ActivatedWeightedGi:1; //should make 1 bit, bitfied
    //u8 SwitchBinding:2;
    //u8 sturdyhungon:1; //to surivive full hp ko effect one time /destiny bond, perish song, final gambit etc.
    //u8 trappedinStickyweb:1; //needed trigger for mon trapped in sticky web and can't switch
    
    //u8 StatusSetViaMoldBreaker:1;
    //u8 fixationTurns:2;   //to track that fixation move is being repeated max value 3?
    //u16 fixatedMove; //was forewarnmove replaced for Fixation status
    //u8 hasSwitchinActivated; //use for switch in end turn check //rn just for zacian zamazenta effetcts, triggered on switch in activate/end in endturn
    //u8 timecontrolAbilityTimer:2; //for dialga stay 0, set to 2 when use that should actiavte it,and decrement only if non zero in end turn
    //u8 TrapSetViaMoldBreaker:1;
    //u8 AscensionTimer:2; //time for flying types to recover from smack down 3 turns

    /*0x1A*/ //u8 unk1A[2]; //don't think this is used
 //think I may not actually need roost start value, long as I have timer
//need look up padding and bitwise to understand how these work so i'm doing it correctly
//if I don't have proper padding it won't be faster/save space, and could actually slow it down instead
//vsonic

//largest value is u16 so think struct
//alligns to 2?


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

//thought didnt need w side timer existing
//but guess could use timer 0 w status set for permanent effects
// Per-side statuses that affect an entire party
#define SIDE_STATUS_REFLECT					(1 << 0)
#define SIDE_STATUS_LIGHTSCREEN				(1 << 1)
#define SIDE_STATUS_STICKY_WEB				(1 << 2)
#define SIDE_STATUS_SPIKES					(1 << 4) //side status fitureattack never used?, guess can remove
#define SIDE_STATUS_SAFEGUARD				(1 << 5)
#define SIDE_STATUS_FREE_SPACE  			(1 << 6)	//black fog shuold prevnt same as block burn/etc. dmg
#define SIDE_STATUS_MIST					(1 << 8)	//blocked by black fog
#define SIDE_STATUS_SPIKES_TRIGGERED		(1 << 9)    //not actually damage is just a check for if effect has triggered for condition progression
#define SIDE_STATUS_TAILWIND                (1 << 10)	//unsure could have tail wind use do defog affect, remove mist & black fog
#define SIDE_STATUS_AURORA_VEIL             (1 << 11)
#define SIDE_STATUS_LUCKY_CHANT             (1 << 12)
#define SIDE_STATUS_TOXIC_SPIKES            (1 << 13)
#define SIDE_STATUS_STEALTH_ROCK            (1 << 14) //also prevented from dmg when black fog up
#define SIDE_STATUS_STEALTH_ROCK_TRIGGERED  (1 << 15)
#define SIDE_STATUS_TOXIC_SPIKES_TRIGGERED  (1 << 16)
#define SIDE_STATUS_STICKY_WEB_TRIGGERED    (1 << 17) //can take all these triggered stuff out into disabled structs instead...
#define SIDE_STATUS_QUICK_GUARD             (1 << 18)
#define SIDE_STATUS_WIDE_GUARD              (1 << 19)
#define SIDE_STATUS_CRAFTY_SHIELD           (1 << 20)
#define SIDE_STATUS_MAT_BLOCK               (1 << 21)
#define SIDE_STATUS_HEAL_BLOCK              (1 << 22)//need setup this & embargo  heal block side status is already setup I jusut forgot...
#define SIDE_STATUS_EMBARGO					(1 << 23)
#define SIDE_STATUS_MUDSPORT				(1 << 24)
#define SIDE_STATUS_WATERSPORT				(1 << 25)
#define SIDE_STATUS_MAGIC_COAT				(1 << 26)	//for magic coat buff make 3 turn, similar in effect to a screen, but 3 instead of 5 turns as it nullifies
#define SIDE_STATUS_STEEL_SURGE             (1 << 27)  //Was copperajah gmax move will make normal status is steel stealth rock
#define SIDE_STATUS_STEEL_SURGE_TRIGGERED   (1 << 28)
#define SIDE_STATUS_RAINBOW                 (1 << 29)
#define SIDE_STATUS_SEA_OF_FIRE             (1 << 30)
#define SIDE_STATUS_SWAMP                   (1 << 31)

#define SIDE_STATUS_HAZARDS_ANY    (SIDE_STATUS_SPIKES | SIDE_STATUS_STICKY_WEB | SIDE_STATUS_TOXIC_SPIKES | SIDE_STATUS_STEALTH_ROCK | SIDE_STATUS_STEEL_SURGE)
#define SIDE_STATUS_SCREEN_ANY     (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL)
#define SIDE_STATUS_PLEDGE_ANY     (SIDE_STATUS_RAINBOW | SIDE_STATUS_SEA_OF_FIRE | SIDE_STATUS_SWAMP)

enum Hazards
{
    HAZARDS_NONE,
    HAZARDS_SPIKES,
    HAZARDS_STICKY_WEB,
    HAZARDS_TOXIC_SPIKES,
    HAZARDS_STEALTH_ROCK,
    HAZARDS_STEELSURGE,
    HAZARDS_MAX_COUNT,
};

// Used for damaging entry hazards based on type
enum TypeSideHazard
{
    TYPE_SIDE_HAZARD_POINTED_STONES = TYPE_ROCK,
    TYPE_SIDE_HAZARD_SHARP_STEEL    = TYPE_STEEL,
};


// Field affecting statuses.
#define STATUS_FIELD_MAGIC_ROOM         (1 << 0)
#define STATUS_FIELD_TRICK_ROOM        (1 << 1)
#define STATUS_FIELD_WONDER_ROOM        (1 << 2)
#define STATUS_FIELD_GRAVITY            (1 << 3)
//#define STATUS_FIELD_MUDSPORT           0x8  will try to keep these 2 in status3 because they didn't use a timer I can put them here and have them not use a timer as well.
//#define STATUS_FIELD_WATERSPORT         0x10
#define STATUS_FIELD_SCORCHED_TERRAIN   (1 << 4)	//make red version or new tile with scorched cracked earth appearane //learned about effect of pledge combos think want these to be those make this the scorch terrain
#define STATUS_FIELD_FLOODED_TERRAIN    (1 << 5)	//can use surf tile/ or edit a blue puddle into normal graphic
#define STATUS_FIELD_OCEAN_TERRAIN      (1 << 6)	//for when surfing on ocean/deeper water /grass terrain & scorched terrain wouldn't work
#define STATUS_FIELD_GRASSY_TERRAIN     (1 << 7)	//longer grass
#define STATUS_FIELD_MISTY_TERRAIN      (1 << 8)	//mist/haze/defog -?? ooh this was to use the animation from those for field effect
#define STATUS_FIELD_ELECTRIC_TERRAIN   (1 << 9)	//sparks tag
#define STATUS_FIELD_PSYCHIC_TERRAIN    (1 << 10)	//could surround field w hidden power orbs?
#define STATUS_FIELD_SNOWY_TERRAIN		(1 << 11)	//for snow area
#define STATUS_FIELD_SNOWESCAPE  (1 << 12)	//realize don't need STATUS_FIELD_TERRAIN_PERMANENT could make conditional to make it permanent using the timer?
#define STATUS_FIELD_ION_DELUGE         (1 << 13)
#define STATUS_FIELD_FAIRY_LOCK         (1 << 14)
#define STATUS_FIELD_HAZE          (1 << 15)	//will reset back to haze, to annoying to manage and too centralizing HAZE -3 full turns so timer is 4
//#define STATUS_FIELD_MUDSPORT			(1 << 15) gonna put these in side status instead
//#define STATUS_FIELD_WATERSPORT         (1 << 16)
//need pledge stuff


#define TERRAIN_DEFINES

#define STATUS_FIELD_TERRAIN_ANY              (STATUS_FIELD_SCORCHED_TERRAIN | STATUS_FIELD_FLOODED_TERRAIN | STATUS_FIELD_OCEAN_TERRAIN | STATUS_FIELD_GRASSY_TERRAIN | STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_PSYCHIC_TERRAIN)
#define PERMANENT_TERRAIN   0     //use timer value 0 so never decrements
#define PERMANENT_WEATHER   0       //same as terrain


// Flags describing move's result
#define MOVE_RESULT_MISSED                (1 << 0)
#define MOVE_RESULT_SUPER_EFFECTIVE       (1 << 1)
#define MOVE_RESULT_NOT_VERY_EFFECTIVE    (1 << 2)
#define MOVE_RESULT_DOESNT_AFFECT_FOE     (1 << 3)
#define MOVE_RESULT_ONE_HIT_KO            (1 << 4)
#define MOVE_RESULT_FAILED                (1 << 5)
#define MOVE_RESULT_FOE_ENDURED           (1 << 6)
#define MOVE_RESULT_FOE_HUNG_ON           (1 << 7)
#define MOVE_RESULT_STURDIED              (1 << 8)
#define MOVE_RESULT_AVOIDED_ATTACK        (MOVE_RESULT_MISSED | MOVE_RESULT_FAILED)
#define MOVE_RESULT_NO_EFFECT             (MOVE_RESULT_MISSED | MOVE_RESULT_FAILED | MOVE_RESULT_DOESNT_AFFECT_FOE)

enum BattleWeather
{
    BATTLE_WEATHER_RAIN,
    BATTLE_WEATHER_RAIN_PRIMAL,
    BATTLE_WEATHER_RAIN_DOWNPOUR,
    BATTLE_WEATHER_SUN,
    BATTLE_WEATHER_SUN_PRIMAL,
    BATTLE_WEATHER_SANDSTORM,
    BATTLE_WEATHER_HAIL,
    BATTLE_WEATHER_SNOW,
    BATTLE_WEATHER_MOONLIGHT,
    BATTLE_WEATHER_ACID_RAIN,
    BATTLE_WEATHER_FOG, 
    BATTLE_WEATHER_STRONG_WINDS,
    BATTLE_WEATHER_COUNT,
};
//attempting to rework fog considering set damp maybe block stat boosts
//ok think turn fog into a psuedo haze?
//sets damp stoping explosions and will treat
//enemies as if they don't have stat boosts
//hmm since want effect to be slow down tempo
//maybe just ignore only offensive stat buffs?

//fog entry message will be a  damp fog covered the field

//vsonic since added special status switchin done prob don't need now?


//used on gBattleWeather is a u16, max value is 15
//if I don't add anything else I have space for 
//1 more temp/permanent weather condition
//well guess could add snow for those that want it
//hmm or maybe acid rain, for a poison effect
//would have anotehr way to activate poison heal
//for poison types hmm yeah I like that
//can just alter hail setup like emerald
//where it can function as either hail or snow
//weather move could be poison cloud caustic cloud or something
//hmm and THAT I could roll into forecast
//could reuse same form just maybe do a palette swap?

//in research of acid rain found its combosed of two non flamable
// acids nitric acid and sulphuric acid that are very reacticive
// capable of causing fires intensifying fires or causing explosions
//with that in mind think idea of acid rain I'd go with is
//a type that boosts water AND fire dmg activates poison heal on poison types
//but damages all non poison types would still activate other rain based boosts
// enhancing fire damage is the important "drawback" here since it is still "rain"
//think fire dmg will be boosted to a less degree than sun, but boosted none the less
//gives more for rain teams but also not eliminating the place that moon weather 
//could have, mostly because it also boosts fire
//decide also have acid rain activate toxic boost
//with that I could give toxic boost...to POISON TYPES!!
//vsonic

// Battle Weather flags
#define WEATHER_NONE          0
#define WEATHER_RAIN_NORMAL   (1 << BATTLE_WEATHER_RAIN)
#define WEATHER_RAIN_PRIMAL   (1 << BATTLE_WEATHER_RAIN_PRIMAL)
#define WEATHER_RAIN_DOWNPOUR (1 << BATTLE_WEATHER_RAIN_DOWNPOUR)  // unused
#define WEATHER_RAIN_ANY          (WEATHER_RAIN_NORMAL | WEATHER_RAIN_PRIMAL | WEATHER_RAIN_DOWNPOUR)
#define WEATHER_SUN_NORMAL    (1 << BATTLE_WEATHER_SUN)
#define WEATHER_SUN_PRIMAL    (1 << BATTLE_WEATHER_SUN_PRIMAL)
#define WEATHER_SUN_ANY            (WEATHER_SUN_NORMAL | WEATHER_SUN_PRIMAL)
#define WEATHER_SANDSTORM     (1 << BATTLE_WEATHER_SANDSTORM)
#define WEATHER_HAIL          (1 << BATTLE_WEATHER_HAIL)
#define WEATHER_SNOW          (1 << BATTLE_WEATHER_SNOW)
#define WEATHER_MOON            (1 << BATTLE_WEATHER_MOONLIGHT)
#define WEATHER_ACID_RAIN       (1 << BATTLE_WEATHER_ACID_RAIN)
#define WEATHER_FOG           (1 << BATTLE_WEATHER_FOG)
#define WEATHER_STRONG_WINDS  (1 << BATTLE_WEATHER_STRONG_WINDS)

#define WEATHER_ANY           (WEATHER_RAIN_ANY | WEATHER_SANDSTORM | WEATHER_SUN_ANY | WEATHER_HAIL | WEATHER_STRONG_WINDS | WEATHER_SNOW | WEATHER_MOON | WEATHER_ACID_RAIN | WEATHER_FOG)
#define WEATHER_DAMAGING_ANY  (WEATHER_HAIL | WEATHER_SANDSTORM | WEATHER_ACID_RAIN)
#define WEATHER_ICY_ANY       (WEATHER_HAIL | WEATHER_SNOW)
#define WEATHER_LOW_LIGHT     (WEATHER_FOG | WEATHER_ICY_ANY | WEATHER_RAIN_ANY | WEATHER_SANDSTORM | WEATHER_MOON | WEATHER_ACID_RAIN)
#define WEATHER_INCLEMENT     (WEATHER_FOG | WEATHER_ICY_ANY | WEATHER_RAIN_ANY | WEATHER_SANDSTORM | WEATHER_ACID_RAIN)

#define WEATHER_PRIMAL_ANY    (WEATHER_RAIN_PRIMAL | WEATHER_SUN_PRIMAL | WEATHER_STRONG_WINDS)

#define WEATHER_RAIN_ALL    (WEATHER_RAIN_ANY | WEATHER_ACID_RAIN)
#define WEATHER_LIGHT_BASED (WEATHER_SUN_ANY | WEATHER_MOON)
#define WEATHER_ICE_SAND    (WEATHER_ICY_ANY | WEATHER_SANDSTORM)

// Explicit numbers until frostbite because those shouldn't be shifted
enum __attribute__((packed)) MoveEffect
{
    MOVE_EFFECT_NONE = 0,
    MOVE_EFFECT_SLEEP = 1,
    MOVE_EFFECT_POISON = 2,
    MOVE_EFFECT_BURN = 3,
    MOVE_EFFECT_FREEZE = 4,
    MOVE_EFFECT_PARALYSIS = 5,
    MOVE_EFFECT_TOXIC = 6,
    MOVE_EFFECT_FROSTBITE = 7,  //set freeze without setting timer
    MOVE_EFFECT_CONFUSION,
    MOVE_EFFECT_FLINCH,
    MOVE_EFFECT_TRI_ATTACK,
    MOVE_EFFECT_UPROAR,
    MOVE_EFFECT_PAYDAY,
    MOVE_EFFECT_WRAP,
    MOVE_EFFECT_ATK_PLUS_1,
    MOVE_EFFECT_DEF_PLUS_1,
    MOVE_EFFECT_SPD_PLUS_1,
    MOVE_EFFECT_SP_ATK_PLUS_1,
    MOVE_EFFECT_SP_DEF_PLUS_1,
    MOVE_EFFECT_ACC_PLUS_1,
    MOVE_EFFECT_EVS_PLUS_1,
    MOVE_EFFECT_ATK_MINUS_1,
    MOVE_EFFECT_DEF_MINUS_1,
    MOVE_EFFECT_SPD_MINUS_1,
    MOVE_EFFECT_SP_ATK_MINUS_1,
    MOVE_EFFECT_SP_DEF_MINUS_1,
    MOVE_EFFECT_ACC_MINUS_1,
    MOVE_EFFECT_EVS_MINUS_1,
    MOVE_EFFECT_REMOVE_ARG_TYPE,
    MOVE_EFFECT_RECHARGE,
    MOVE_EFFECT_RAGE,
    MOVE_EFFECT_DRAGON_RAGE,
    MOVE_EFFECT_CRIT_PROTECTION, //move critprotect bs command to move effect instead
    MOVE_EFFECT_PREVENT_ESCAPE,
    MOVE_EFFECT_NIGHTMARE,
    MOVE_EFFECT_GLAIVE_RUSH,
    MOVE_EFFECT_ALL_STATS_UP,
    MOVE_EFFECT_REMOVE_STATUS,
    MOVE_EFFECT_ATK_DEF_DOWN,
    MOVE_EFFECT_ATK_PLUS_2,
    MOVE_EFFECT_DEF_PLUS_2,
    MOVE_EFFECT_SPD_PLUS_2,
    MOVE_EFFECT_SP_ATK_PLUS_2,
    MOVE_EFFECT_SP_DEF_PLUS_2,
    MOVE_EFFECT_ACC_PLUS_2,
    MOVE_EFFECT_EVS_PLUS_2,
    MOVE_EFFECT_ATK_MINUS_2,
    MOVE_EFFECT_DEF_MINUS_2,
    MOVE_EFFECT_SPD_MINUS_2,
    MOVE_EFFECT_SP_ATK_MINUS_2,
    MOVE_EFFECT_SP_DEF_MINUS_2,
    MOVE_EFFECT_ACC_MINUS_2,
    MOVE_EFFECT_EVS_MINUS_2,
    MOVE_EFFECT_SCALE_SHOT,
    MOVE_EFFECT_THRASH,
    MOVE_EFFECT_DEF_SPDEF_DOWN,
    MOVE_EFFECT_CLEAR_SMOG,
    MOVE_EFFECT_FLAME_BURST,
    MOVE_EFFECT_FEINT,
    MOVE_EFFECT_V_CREATE,
    MOVE_EFFECT_HAPPY_HOUR,
    MOVE_EFFECT_CORE_ENFORCER,
    MOVE_EFFECT_THROAT_CHOP,
    MOVE_EFFECT_INCINERATE,
    MOVE_EFFECT_BUG_BITE,
    MOVE_EFFECT_LIGHT_RECOIL,
    MOVE_EFFECT_MED_RECOIL,
    MOVE_EFFECT_HEAVY_RECOIL,
    MOVE_EFFECT_RECOIL_HP_25,
    MOVE_EFFECT_TRAP_BOTH,
    MOVE_EFFECT_ROUND,
    MOVE_EFFECT_DIRE_CLAW,
    MOVE_EFFECT_SYRUP_BOMB,
    MOVE_EFFECT_FLORAL_HEALING,
    MOVE_EFFECT_SECRET_POWER,
    MOVE_EFFECT_PSYCHIC_NOISE,
    MOVE_EFFECT_TERA_BLAST,
    MOVE_EFFECT_ORDER_UP,
    MOVE_EFFECT_ION_DELUGE, //plasma fist
    MOVE_EFFECT_HAZE, //lets go spescial attacks
    MOVE_EFFECT_LEECH_SEED,
    MOVE_EFFECT_REFLECT,
    MOVE_EFFECT_LIGHT_SCREEN, //end lets go
    MOVE_EFFECT_SALT_CURE,
    MOVE_EFFECT_EERIE_SPELL,
    //zmove and lets go move effects
    MOVE_EFFECT_AROMATHERAPY,
    // Move effects that happen before the move hits. Set in SetPreAttackMoveEffect
    MOVE_EFFECT_BREAK_SCREEN,
    MOVE_EFFECT_STEAL_STATS,
    //custom effects
    MOVE_EFFECT_INFESTATION, //bug status
    MOVE_EFFECT_SWITCH_LOCKED, //need this to set status and timer can remove effect
    MOVE_EFFECT_SPIRIT_LOCK, //fairy status
    MOVE_EFFECT_ATTRACT,    //need to setup
    MOVE_EFFECT_HIGHEST_STAT_UP, //for MOVE_MYSTICAL_POWER
    MOVE_EFFECT_FOCUS_ENERGY,   //Plan use for triple arrow
    MOVE_EFFECT_DMG_FIXATION,   //fixation category to set volatile status of same name
    MOVE_EFFECT_SHADOW_STRIKE, //for 2nd mega gren siganture handled in move end multi hit set stat boost status
    MOVE_EFFECT_DEF_CAT_MINUS_1, //drop defense stat based on move category specific for moves that have variable split
    MOVE_EFFECT_DEF_CAT_MINUS_2,
    
    NUM_MOVE_EFFECTS
};

#define MOVE_EFFECT_CONTINUE            0x8000
// Battle environment defines for gBattleEnvironment.
enum BattleEnvironments
{
    BATTLE_ENVIRONMENT_GRASS,
    BATTLE_ENVIRONMENT_LONG_GRASS,
    BATTLE_ENVIRONMENT_SAND,
    BATTLE_ENVIRONMENT_UNDERWATER,
    BATTLE_ENVIRONMENT_WATER,
    BATTLE_ENVIRONMENT_POND,
    BATTLE_ENVIRONMENT_MOUNTAIN,
    BATTLE_ENVIRONMENT_CAVE,
    BATTLE_ENVIRONMENT_BUILDING,
    BATTLE_ENVIRONMENT_PLAIN,
    BATTLE_ENVIRONMENT_LINK,    
    BATTLE_ENVIRONMENT_GYM,
    BATTLE_ENVIRONMENT_LEADER,
    BATTLE_ENVIRONMENT_INDOOR_2,
    BATTLE_ENVIRONMENT_INDOOR_1,
    BATTLE_ENVIRONMENT_LORELEI,
    BATTLE_ENVIRONMENT_BRUNO,
    BATTLE_ENVIRONMENT_AGATHA,
    BATTLE_ENVIRONMENT_LANCE,
    BATTLE_ENVIRONMENT_CHAMPION,
    //Em values
    BATTLE_ENVIRONMENT_FRONTIER,
    BATTLE_ENVIRONMENT_MAGMA,
    BATTLE_ENVIRONMENT_AQUA,
    BATTLE_ENVIRONMENT_SIDNEY,
    BATTLE_ENVIRONMENT_PHOEBE,
    BATTLE_ENVIRONMENT_GLACIA,
    BATTLE_ENVIRONMENT_DRAKE,
    BATTLE_ENVIRONMENT_CHAMPION_EM,
    BATTLE_ENVIRONMENT_GROUDON,
    BATTLE_ENVIRONMENT_KYOGRE,
    BATTLE_ENVIRONMENT_RAYQUAZA,
    // New battle environments are used for Secret Power but not fully implemented.
    BATTLE_ENVIRONMENT_SOARING,
    BATTLE_ENVIRONMENT_SKY_PILLAR,
    BATTLE_ENVIRONMENT_BURIAL_GROUND,
    BATTLE_ENVIRONMENT_PUDDLE,
    BATTLE_ENVIRONMENT_MARSH,
    BATTLE_ENVIRONMENT_SWAMP,
    BATTLE_ENVIRONMENT_SNOW,
    BATTLE_ENVIRONMENT_ICE,
    BATTLE_ENVIRONMENT_VOLCANO,
    BATTLE_ENVIRONMENT_DISTORTION_WORLD,
    BATTLE_ENVIRONMENT_SPACE,
    BATTLE_ENVIRONMENT_ULTRA_SPACE,
    BATTLE_ENVIRONMENT_COUNT,
};


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
#define B_WAIT_TIME_UNIQUE 7    //for multihit miss and sleep heal
#define B_WAIT_TIME_LONG_LONG   8   //for mon block ball message
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

// Flag for BattlePutTextOnWindow. Never set
#define B_WIN_COPYTOVRAM (1 << 7)

// Indicator for the party summary bar to display an empty slot.
#define HP_EMPTY_SLOT 0xFFFF

enum MoveTarget
{
    TARGET_NONE,
    TARGET_SELECTED,
    TARGET_SMART, // Like target select but can also smartly redirect to partner. Works only with strikeCount > 1 moves
    TARGET_DEPENDS,
    TARGET_OPPONENT,
    TARGET_RANDOM,
    TARGET_BOTH,
    TARGET_USER,
    TARGET_ALLY,
    TARGET_USER_AND_ALLY,
    TARGET_USER_OR_ALLY, // Acupressure
    TARGET_FOES_AND_ALLY,
    TARGET_FIELD, // Moves that target the field, e.g. Rain Dance
    TARGET_OPPONENTS_FIELD, // Targets all other battlers and self, e.g. Teatime
    TARGET_ALL_BATTLERS,
};

// Constants for Parental Bond
#define PARENTAL_BOND_1ST_HIT 2
#define PARENTAL_BOND_2ND_HIT 1
#define PARENTAL_BOND_OFF     0

// Constants for if HandleScriptMegaPrimalBurst should handle Mega Evolution, Primal Reversion, or Ultra Burst.
#define HANDLE_TYPE_MEGA_EVOLUTION 0
#define HANDLE_TYPE_PRIMAL_REVERSION 1
#define HANDLE_TYPE_ULTRA_BURST 2

#define NUM_PROTECT_ODDS 4

// Constants for Torment
#define PERMANENT_TORMENT   0xF

enum FaintedActions
{
    FAINTED_ACTIONS_NO_MONS_TO_SWITCH,
    FAINTED_ACTIONS_GIVE_EXP,
    FAINTED_ACTIONS_SET_ABSENT_FLAGS,
    FAINTED_ACTIONS_WAIT_STATE,
    FAINTED_ACTIONS_HANDLE_FAINTED_MON,
    FAINTED_ACTIONS_HANDLE_NEXT_BATTLER,
    FAINTED_ACTIONS_MAX_CASE,
};

//  Enum,                                         fieldName,           Type, max value
#define STARTING_STATUS_DEFINITIONS(F) \
    F(STARTING_STATUS_ELECTRIC_TERRAIN,               electricTerrain,            (u32, 1)) /* Electric Terrain (Permanent) */             \
    F(STARTING_STATUS_ELECTRIC_TERRAIN_TEMPORARY,     electricTerrainTemporary,   (u32, 1)) /* Electric Terrain Temporary (5 turns) */     \
    F(STARTING_STATUS_MISTY_TERRAIN,                  mistyTerrain,               (u32, 1)) /* Misty Terrain (Permanent) */                \
    F(STARTING_STATUS_MISTY_TERRAIN_TEMPORARY,        mistyTerrainTemporary,      (u32, 1)) /* Misty Terrain Temporary (5 turns) */        \
    F(STARTING_STATUS_GRASSY_TERRAIN,                 grassyTerrain,              (u32, 1)) /* Grassy Terrain (Permanent) */               \
    F(STARTING_STATUS_GRASSY_TERRAIN_TEMPORARY,       grassyTerrainTemporary,     (u32, 1)) /* Grassy Terrain Temporary (5 turns) */       \
    F(STARTING_STATUS_PSYCHIC_TERRAIN,                psychicTerrain,             (u32, 1)) /* Psychic Terrain (Permanent) */              \
    F(STARTING_STATUS_PSYCHIC_TERRAIN_TEMPORARY,      psychicTerrainTemporary,    (u32, 1)) /* Psychic Terrain Temporary (5 turns) */      \
    F(STARTING_STATUS_TRICK_ROOM,                     trickRoom,                  (u32, 1)) /* Trick Room (Permanent) */                   \
    F(STARTING_STATUS_TRICK_ROOM_TEMPORARY,           trickRoomTemporary,         (u32, 1)) /* Trick Room Temporary (5 turns) */           \
    F(STARTING_STATUS_MAGIC_ROOM,                     magicRoom,                  (u32, 1)) /* Magic Room (Permanent) */                   \
    F(STARTING_STATUS_MAGIC_ROOM_TEMPORARY,           magicRoomTemporary,         (u32, 1)) /* Magic Room Temporary (5 turns) */           \
    F(STARTING_STATUS_WONDER_ROOM,                    wonderRoom,                 (u32, 1)) /* Wonder Room (Permanent) */                  \
    F(STARTING_STATUS_WONDER_ROOM_TEMPORARY,          wonderRoomTemporary,        (u32, 1)) /* Wonder Room Temporary (5 turns) */          \
    F(STARTING_STATUS_TAILWIND_PLAYER,                tailwindPlayer,             (u32, 1)) /* Tailwind Player (Permanent) */              \
    F(STARTING_STATUS_TAILWIND_PLAYER_TEMPORARY,      tailwindPlayerTemporary,    (u32, 1)) /* Tailwind Player Temporary (4/3 turns) */    \
    F(STARTING_STATUS_TAILWIND_OPPONENT,              tailwindOpponent,           (u32, 1)) /* Tailwind Opponent (Permanent) */            \
    F(STARTING_STATUS_TAILWIND_OPPONENT_TEMPORARY,    tailwindOpponentTemporary,  (u32, 1)) /* Tailwind Opponent Temporary (4/3 turns) */  \
    F(STARTING_STATUS_RAINBOW_PLAYER,                 rainbowPlayer,              (u32, 1)) /* Rainbow Player (Permanent) */               \
    F(STARTING_STATUS_RAINBOW_PLAYER_TEMPORARY,       rainbowPlayerTemporary,     (u32, 1)) /* Rainbow Player Temporary (4 turns) */       \
    F(STARTING_STATUS_RAINBOW_OPPONENT,               rainbowOpponent,            (u32, 1)) /* Rainbow Opponent (Permanent) */             \
    F(STARTING_STATUS_RAINBOW_OPPONENT_TEMPORARY,     rainbowOpponentTemporary,   (u32, 1)) /* Rainbow Opponent Temporary (4 turns) */     \
    F(STARTING_STATUS_SEA_OF_FIRE_PLAYER,             seaOfFirePlayer,            (u32, 1)) /* Sea Of Fire Player (Permanent) */           \
    F(STARTING_STATUS_SEA_OF_FIRE_PLAYER_TEMPORARY,   seaOfFirePlayerTemporary,   (u32, 1)) /* Sea Of Fire Player Temporary (4 turns) */   \
    F(STARTING_STATUS_SEA_OF_FIRE_OPPONENT,           seaOfFireOpponent,          (u32, 1)) /* Sea Of Fire Opponent (Permanent) */         \
    F(STARTING_STATUS_SEA_OF_FIRE_OPPONENT_TEMPORARY, seaOfFireOpponentTemporary, (u32, 1)) /* Sea Of Fire Opponent Temporary (4 turns) */ \
    F(STARTING_STATUS_SWAMP_PLAYER,                   swampPlayer,                (u32, 1)) /* Swamp Player (Permanent) */                 \
    F(STARTING_STATUS_SWAMP_PLAYER_TEMPORARY,         swampPlayerTemporary,       (u32, 1)) /* Swamp Player Temporary (4 turns) */         \
    F(STARTING_STATUS_SWAMP_OPPONENT,                 swampOpponent,              (u32, 1)) /* Swamp Opponent (Permanent) */               \
    F(STARTING_STATUS_SWAMP_OPPONENT_TEMPORARY,       swampOpponentTemporary,     (u32, 1)) /* Swamp Opponent Temporary (4 turns) */       \
    /* Hazards */                                                                                                                          \
    F(STARTING_STATUS_SPIKES_PLAYER_L1,               spikesPlayerL1,             (u32, 1)) /* Spikes Player Layer 1 */                    \
    F(STARTING_STATUS_SPIKES_PLAYER_L2,               spikesPlayerL2,             (u32, 1)) /* Spikes Player Layer 2 */                    \
    F(STARTING_STATUS_SPIKES_PLAYER_L3,               spikesPlayerL3,             (u32, 1)) /* Spikes Player Layer 3 */                    \
    F(STARTING_STATUS_SPIKES_OPPONENT_L1,             spikesOpponentL1,           (u32, 1)) /* Spikes Opponent Layer 1 */                  \
    F(STARTING_STATUS_SPIKES_OPPONENT_L2,             spikesOpponentL2,           (u32, 1)) /* Spikes Opponent Layer 2 */                  \
    F(STARTING_STATUS_SPIKES_OPPONENT_L3,             spikesOpponentL3,           (u32, 1)) /* Spikes Opponent Layer 3 */                  \
    F(STARTING_STATUS_TOXIC_SPIKES_PLAYER_L1,         toxicSpikesPlayerL1,        (u32, 1)) /* Toxic Spikes Player Layer 1 */              \
    F(STARTING_STATUS_TOXIC_SPIKES_PLAYER_L2,         toxicSpikesPlayerL2,        (u32, 1)) /* Toxic Spikes Player Layer 2 */              \
    F(STARTING_STATUS_TOXIC_SPIKES_OPPONENT_L1,       toxicSpikesOpponentL1,      (u32, 1)) /* Toxic Spikes Opponent Layer 1 */            \
    F(STARTING_STATUS_TOXIC_SPIKES_OPPONENT_L2,       toxicSpikesOpponentL2,      (u32, 1)) /* Toxic Spikes Opponent Layer 2 */            \
    F(STARTING_STATUS_STICKY_WEB_PLAYER,              stickyWebPlayer,            (u32, 1)) /* Sticky Web Player */                        \
    F(STARTING_STATUS_STICKY_WEB_OPPONENT,            stickyWebOpponent,          (u32, 1)) /* Sticky Web Opponent */                      \
    F(STARTING_STATUS_STEALTH_ROCK_PLAYER,            stealthRockPlayer,          (u32, 1)) /* Stealth Rock Player */                      \
    F(STARTING_STATUS_STEALTH_ROCK_OPPONENT,          stealthRockOpponent,        (u32, 1)) /* Stealth Rock Opponent */                    \
    F(STARTING_STATUS_SHARP_STEEL_PLAYER,             sharpSteelPlayer,           (u32, 1)) /* Sharp Steel Player */                       \
    F(STARTING_STATUS_SHARP_STEEL_OPPONENT,           sharpSteelOpponent,         (u32, 1)) /* Sharp Steel Opponent */                     \

#define UNPACK_STARTING_STATUS_ENUMS(_enum, ...) _enum,

// Constants for SetStartingStatus
enum StartingStatus
{
    STARTING_STATUS_DEFINITIONS(UNPACK_STARTING_STATUS_ENUMS)
};

#endif // GUARD_CONSTANTS_BATTLE_H
