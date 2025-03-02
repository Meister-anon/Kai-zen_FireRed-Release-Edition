#ifndef GUARD_POKEMON_H
#define GUARD_POKEMON_H

#include "global.h"
#include "sprite.h"
#include "constants/pokemon.h"
#include "pokemon_storage_system.h"

#define GET_BASE_SPECIES_ID(speciesId) (GetFormSpeciesId(speciesId, 0))

#define GET_FINAL_FORM_SPECIES_ID(speciesId) (GetFormSpeciesId(speciesId, GetFinalFormSpeciesId(speciesId)))

//mcgriffin informed me all these need to stay 12 bytes or I lose box space...sigh
//that's why I lost so much space
//it takes ewram fuck, fuckity fuck, don't have space to add things
//struct PokemonSubstruct0 //all 4 of these max up boxmon, for mon to not heal in pc need add hp value to boxmon
//{
     //for storing level evolved at for relative evo setup
//};//add here to save space, if understood corectly size is based on largest of substructs
//so if I add on to the smaller ones it doesn't increase size

//struct PokemonSubstruct1
//{
     // 1 * 4 = 4    
//};//12 bytes

//struct PokemonSubstruct2
//{
       //think replace with flag check, planned use for exp share ev item activation condition
//}; //value default to 0,  then check what flgs are set in battle and change end outcome based on that

//pokemonflags
#define FLAG_EXP_SHARE              (1 << 0)
#define FLAG_HP_POWER_ITEM          (1 << 1)
#define FLAG_ATK_POWER_ITEM         (1 << 2)
#define FLAG_DEF_POWER_ITEM         (1 << 3)
#define FLAG_SPD_POWER_ITEM         (1 << 4)
#define FLAG_SPATK_POWER_ITEM       (1 << 5)
#define FLAG_SPDEF_POWER_ITEM       (1 << 6)

//set flags same as set for battle moves flags, 
//will effect menu but think should have fast global turn off from within key item?
//trainer suite split into exp share and ev trainer,  
//no make two separate items, exp share key item you can activate and turn off from party menu
//and ev trainer key item you setup from party menu, but also have global
//off setting from item itself for both to make easier to cut off

/*think will also use the flag for exp share and ev item boost, so don't need to waste held item slot
//part of setting it up like opal, so have key item, trainer suite, which adds menu fields EXP_SHARE & EV_TRAIN
//taking through task/menu options that would set the specific flag for that mon.
//setting exp share flag should add little "E" symbol  to partymenu window so easy to tell its active
//think can do similar thing for ev items, just set item icon in a spot on party menu to show you're ev training and what stat you're boosting.
//this would be separate from held item position as that's directly on the mon icon itself.*/
//ev shackle item would still be of use, what it would do is actually be a held item, 
//either it doesn't lower speed or its the only training tool that actually DOES lower speed when in use.
//it'd multiply the individual stat ev gain you normally get by a multiplier
//also of note you should be able to set multiple ev train items at once with this.
//since its a u8 flag I have space for 8 flags at once, and only 6 stat flags plus the exp flag, leaving one space still for the form flag!!

//put more thought into this and I'm wondering if it matters where I put the flag, 
//if I use it here itd be in basestats struct
//but evs are stored in PokemonSubstruct2, idk if it needs to be in teh same struct or not, I assume it shoudn't matter
//its just a matter of checking and setting the relevant fields as I need them.
//I believe its easier to adjust values when they are in the same struct?
//should I need to I could easily replace sheen with the flag as they would both be u8
//meaning savestruct wouldn't be affected  but for form change/breeding it makes more sense
//to use base stat struct for form change/flag check,  I could do both
//leave form change in base stats but move the exp share & ev item flag checks to PokemonSubstruct2
//in place of sheen

//struct PokemonSubstruct3
//{
 /* 0x00 */ 
 /* 0x01 */  //question is if this can even work?
            
            
            

 /* 0x02 */ 
 /* 0x02 */ 
 /* 0x03 */ 
 /* 0x03 */  //bitfields 4 ; 4  is 1 byte  2^8  7; 1 is 1 byte 
    
 /* 0x04 */  //changed abilityNum to 3, so I can get the second hidden ability slot.
 /* 0x07 */ //u32 isEgg:1;
 /* 0x07 */  // allability num are 2 in emerald. so that is the right call //  yeah didn't understand bit fields 2 is correct
                //abilityNum doesn'tfit in field since i increased from bit1 to bit 2
 /* 0x08 */ 
 /* 0x0A */ //u32 artistRibbon:1; //emerlad specific beat contest and have mon be sketched, this can remove
 /* 0x0A */  //maxing evs
 /* 0x0B */ 
 /* 0x0B */ //u32 earthRibbon:1;  checekd was specifically for ereader stuff for mon transferred to coloseum for mt battle 100 round thing
 /* 0x0B */ //u32 filler:4; //had to remove to add form flag check
 /* 0x0B */
//}; //prob also remove event legal tag eventually
//ribbon bit field also doesn't really work anymore since I removed
//several ribbons  its u32, but i'm only taking up 21...

/*union PokemonSubstruct
{
    struct PokemonSubstruct0 type0;
    struct PokemonSubstruct1 type1;
    struct PokemonSubstruct2 type2;
    struct PokemonSubstruct3 type3;
    u16 raw[6];
};*/

// Number of bytes in the largest Pokémon substruct.
// They are assumed to be the same size, and will be padded to
// the largest size by the union.
// By default they are all 12 bytes.
/*#define NUM_SUBSTRUCT_BYTES (max(sizeof(struct PokemonSubstruct0),     \
                             max(sizeof(struct PokemonSubstruct1),     \
                             max(sizeof(struct PokemonSubstruct2),     \
                                 sizeof(struct PokemonSubstruct3)))))

union PokemonSubstruct
{
    struct PokemonSubstruct0 type0;
    struct PokemonSubstruct1 type1;
    struct PokemonSubstruct2 type2;
    struct PokemonSubstruct3 type3;
    u16 raw[NUM_SUBSTRUCT_BYTES / 2]; // /2 because it's u16, not u8
};*/

//for modern have to specifically consider struct order for proper padding/space saving
//starts w u32 so is 4byte aligned, struct is organized in groups of 4byte sections
//note will most likely have to rearrange again when change mame buffers vsonic IMPORTANT
struct BoxPokemon
{
    u32 personality;
    u32 otId;
    u8 nickname[POKEMON_NAME_LENGTH];
    u8 language:3; // 7 languages
    u8 pokerus:5;  // 1-0xF is the timer. 0x10 is set when timer runs out
    
    u8 otName[OT_NAME_LENGTH];
    u8 isMonShiny:1; //potentially replace w removal of checksum? //yeah can get rid of this its all determined by checksum replace w shiny set
    u8 hasSpecies:1;    //MON_DATA_SANITY_IS_BAD_EGG and all mentions of bad egg can be removed
    u8 isEgg:1;
    u8 boxHp:1; //realized only need value 0 & 1
    u8 metGame:4;    
    
    u8 NoBoxExp:1; //true false is all I need for this
    u8 padding:7;
    
    u32 species:11;
    u32 heldItem:10; //looks like both of these will be bit 10
    u32 winningRibbon:1; //these two for emerald battle tower
    u32 victoryRibbon:1;
    u32 cuteRibbon:3;
    u32 smartRibbon:3;
    u32 toughRibbon:3;

    u8 ppBonuses;
    u8 otGender:1;
    u8 metLevel:7;
    u8 metLocation;
    u8 flagcheck;

    u8 friendship;
    u8 formflag;
    u8 hatched:1;  //new thing to replace met level 0 in daycare - need test to make sure doesn't mess w evoLevel
    u8 evoLevel:7;
    u8 cool;

    u32 hpIV:5;
    u32 attackIV:5;
    u32 defenseIV:5;
    u32 speedIV:5;
    u32 spAttackIV:5;
    u32 spDefenseIV:5;
    u32 abilityNum:2;

    u16 move1:10;
    u16 pp1:6;
    u16 move2:10;
    u16 pp2:6;
    u16 move3:10;
    u16 pp3:6;
    u16 move4:10;
    u16 pp4:6;

    u32 hpEV:9; //FACEPALM I never adjusted these for the new cap!!! //max per stat 360
    u32 attackEV:9; //wich is bit 9
    u32 defenseEV:9;    
    u32 pokeball:5;

    u32 speedEV:9;
    u32 spAttackEV:9;
    u32 spDefenseEV:9;
    u32 championRibbon:1; //hall of fame league champion ribbon
    u32 effortRibbon:1;
    u32 coolRibbon:3;    //these are 3 because multiple levels, so can't lower

    u8 beauty;
    u8 cute;
    u8 smart;
    u8 tough;
    
    u32 experience:21;
    u32 lostLocation:8;
    u32 beautyRibbon:3;

};
//wil use bit fields to cut down on substruct stuff on rec
//from josh/shinydragonhunter
//hard to get space saving since space is allocated to max of all structs
//but think can just remove and put all in boxmon here
enum ExpStates
{
    OFF,
    EXP_SHARE,
    EXP_NULL
};

enum StatsSetState
{
    NONE,
    SET_VIA_BATTLE,
    SET_VIA_PARTY
};

struct Pokemon
{
    struct BoxPokemon box; //size of this is size of mon in box, so multiply by mon in box x number of boxes to get size boxes take
    u32 status;
    u8 level;
    u8 mail; //remove mail   vsonic
    u16 hp;
    u16 maxHP;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
    u8 StatusSetState;
    u8 Exp_state;
};

u8 GetLevelFromMonExp(struct Pokemon *mon);
u16 ModifyStatByNature(u8 nature, u16 n, u8 statIndex); //made global for bs command level up calc

struct PokemonStorage
{
    /*0x0000*/ u8 currentBox;
    /*0x0001*/ struct BoxPokemon boxes[TOTAL_BOXES_COUNT][IN_BOX_COUNT];
    /*0x8344*/ u8 boxNames[TOTAL_BOXES_COUNT][BOX_NAME_LENGTH + 1];
    /*0x83C2*/ u8 boxWallpapers[TOTAL_BOXES_COUNT]; //when I'm able to expand box counts give this its own separate constant won't need 
};  //a unique wall paper for each box, could even remove some of the wall papers I don't like/no one likes



struct BattleTowerPokemon //apparently used for both battle tower leftover from emerald, AND trainer tower, on sevii island
{
             u16 species;
             u16 heldItem;
             u16 moves[4];
             u8 level;
             u8 ppBonuses;
             u8 hpEV;
             u8 attackEV;
             u8 defenseEV;
             u8 speedEV;
             u8 spAttackEV;
             u8 spDefenseEV;
             u32 otId;  //if I need to could remove this? I think this is only for the enemy party data, so idk if this is necessary? oh wait that's combined with personality to determine nature?
             u32 hpIV:5; //I think this also goes into createmon function used in battle_main.c createtrainerparty if able to set fixed nature can remove otId & personality then
             u32 attackIV:5; //nmv also sets gender
             u32 defenseIV:5; //bitfiled 5, goes up to 32 bytes guess that explains the 31 iv limit, its 0-31
             u32 speedIV:5;
             u32 spAttackIV:5; //since its restricting to bits, it doesn't much matter the type
             u32 spDefenseIV:5;
             u32 gap:2;
             u8 abilityNum:2;  //didn't properly understand bit fields, each bit stores 2 values so rather than 3 I only need 2 for 4 abilities ? i.e 0-3
             u32 personality:8;  //personality values only go up to 0x96 so think can use bitfield here
             u8 nickname[POKEMON_NAME_LENGTH + 1];
             u8 friendship; //used for frustration and return, exists in either 0 or 255
}; //don't need to change anything foud more space by removing ereader stuff
 //leave as is for now, replace above noe, with this one, when move battletower to C, adn remove trainer hill stuff
//need check padding to make sure actually saving space
//written this way saves ewram for some reason 

#define BATTLE_STATS_NO 8

struct BattlePokemon
{
    /*0x58*/ u32 otId; //may not need status4 in struct status3 & 4 seem to work through gstatuses3 & gstatus4 the same as status 2 already?

    /*0x00*/ u16 species;
    /*0x02*/ u16 attack;
    /*0x04*/ u16 defense;
    /*0x06*/ u16 speed;
    /*0x08*/ u16 spAttack;
    /*0x0A*/ u16 spDefense;
    /*0x0C*/ u16 moves[4];
    
    /*0x14*/ u32 hpIV:5;
    /*0x14*/ u32 attackIV:5;
    /*0x15*/ u32 defenseIV:5;
    /*0x15*/ u32 speedIV:5;
    /*0x16*/ u32 spAttackIV:5;
    /*0x17*/ u32 spDefenseIV:5;
    /*0x17*/ u32 abilityNum:2;
    /*0x18*/ s8 statStages[BATTLE_STATS_NO];
    /*0x20*/ u16 ability;
    /*0x21*/ u8 type1;
    /*0x22*/ u8 type2;
    /*0x23*/ u8 type3; //no space change replaced unknown
    /*0x24*/ u8 pp[MAX_MON_MOVES];
    /*0x28*/ u16 hp;
    /*0x2A*/ u8 level;
    /*0x2B*/ u8 friendship;
    /*0x2C*/ u16 maxHP;
    /*0x2E*/ u16 item;
    /*0x30*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x3B*/ u8 ppBonuses;
    /*0x3C*/ u8 otName[OT_NAME_LENGTH + 1];
             u8 isEgg:1; //changed to u8 to align w above array
             
    /*0x44*/ u32 experience;
    /*0x48*/ u32 personality;
    /*0x4C*/ u32 status1;   //stays on switch
    /*0x50*/ u32 status2;   //temp status lost on switch
    /*0x54*/ u32 status4;   //new addition  for new statuses mostly for new wrap effects, plan to make equivalent of status2
};                   //idk guessing statu1 2 and now 4 are different from status3 as its applied direclty to a mon/?  status3 seems more like a set of temp states?

//believe all fields default to 0, if not set?
//nope is just nothingn so need to set to false in base
//I think its just used like a pointer if I don't put something there
//or set to the struct to 0, in main, it'll just be garbage data
//so yeah I need to set it myself
struct BaseStats  // had to adjust struct order to match paste value from base_stats.h
{
 /* 0x00 */ u8 baseHP;
 /* 0x01 */ u8 baseAttack;
 /* 0x02 */ u8 baseDefense;
 /* 0x03 */ u8 baseSpeed;
 /* 0x04 */ u8 baseSpAttack;
 /* 0x05 */ u8 baseSpDefense;
            u16 statTotal;  //with new macro from GriffinR am able to display mon bst
 /* 0x06 */ u8 type1;
 /* 0x07 */ u8 type2;
            u8 speciesName[13];
 /* 0x08 */ u16 expYield;
 /* 0x09 */ 
 /* 0x0A */ //u16 evYield_HP:2; //not using these so might as well remove from struct to save room
 /* 0x0A */ //u16 evYield_Attack:2;
 /* 0x0A */ //u16 evYield_Defense:2;
 /* 0x0A */ //u16 evYield_Speed:2;
 /* 0x0B */ //u16 evYield_SpAttack:2;
 /* 0x0B */ //u16 evYield_SpDefense:2;
 /* 0x0C */ u16 itemCommon;
 /* 0x0E */ u16 itemRare;
 /* 0x10 */ u8 genderRatio;
 /* 0x11 */ u8 eggCycles;
 /* 0x12 */ u8 friendship;
 /* 0x13 */ u8 growthRate;
 /* 0x14 */ u8 eggGroup1;
 /* 0x15 */ u8 eggGroup2;
            u8 catchRate;
            u8 safariZoneFleeRate;
 /* 0x16 */ u16 abilities[2]; //[partysize] is 6 values, so this is ability 1 and ability 2, doesn't include hidden //this means 2 states, 0 & 1
 /* 0x1B */ u16 abilityHidden[2]; //need to make sure ability num can be 2, then set that as hidden ability
 /* 0x1D */ u8 bodyColor : 7; //what are bodyColor and noFLip fields are they necesary?
            u8 noFlip : 1;
            u8 floating : 1; //put here cuz easier to quick replace in file. replacement for use of gFloatingSpecies array, logic flynig and non flyign mon that can fly/float or who's natural state is floating, (replace levitate) mon has to display ability to do more than just hover slightly over ground
            u8 buffer:7; //since has space could potentially put byte here for cosmetic form or somehting, space is already being used anyway
 /* 0x1E */ u8 flags;   //use for gender diff & form change, when creating mon plan check for flag and divert to what should be based on form species, //also used for making beast ball work, etc.
            const struct LevelUpMove *levelUpLearnset; //replace leveluplearnset pointers file, below replace tmhmlearnset pointers file
            const u16 *tmhmLearnset; //these are just names, in struct will be .name
            const struct Evolution *evolutions;
};

struct BattleMove
{
    u16 effect;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 secondaryEffectChance;
    u16 target;
    s8 priority;
    u32 flags; // is u32 in emerald, might not need to do that, will ask //they use a lot of move flags will update
    u8 split;
    u16 argument;// for transferring move effects
    u8 argumentEffectChance; // setup status commands and seteffectwithchance function to read this as a value explicitly for argument
    //would possibly need to redo setup for effects that become certain without reading effectchance nvm it works 
    //Argument works by passive value of argument to battlescript.moveeffect
    //so just do a check in seteffectwithchance that checks if  battlescripting.moveeffect equals gbattlemons[move].effect or the argument
    //if it equals the argument use argument chance, that means it has already done the effect
    //and has passed the arugment over so it can use the argument chance
};//without u32 flags, type overflowed with added moves
//argument is for extra effects other than secondary effect

extern const struct BattleMove gBattleMoves[];

#define IS_CRIT (gCritMultiplier > 1)

// Battle move flags
#define FLAG_MAKES_CONTACT          (1 << 0)
#define FLAG_PROTECT_AFFECTED       (1 << 1)
#define FLAG_MAGIC_COAT_AFFECTED    (1 << 2)
#define FLAG_SNATCH_AFFECTED        (1 << 3)
#define FLAG_MIRROR_MOVE_AFFECTED   (1 << 4)
//#define FLAG_KINGS_ROCK_AFFECTED    (1 << 5)  udpated to modern use, works on all dmg moves not just selected ones, so dont need this
#define FLAG_HIGH_CRIT              (1 << 6)
#define FLAG_RECKLESS_BOOST         (1 << 7)
#define FLAG_IRON_FIST_BOOST        (1 << 8)    //1 byte
#define FLAG_SHEER_FORCE_BOOST      (1 << 9)
#define FLAG_STRONG_JAW_BOOST       (1 << 10)
#define FLAG_MEGA_LAUNCHER_BOOST    (1 << 11)
#define FLAG_STAT_STAGES_IGNORED    (1 << 12)
#define FLAG_DMG_MINIMIZE           (1 << 13)
#define FLAG_DMG_2X_UNDERGROUND        (1 << 14)
#define FLAG_DMG_2X_UNDERWATER         (1 << 15)
#define FLAG_SOUND                  (1 << 16)   //2 byte
#define FLAG_BALLISTIC              (1 << 17)
#define FLAG_PROTECTION_MOVE        (1 << 18)
#define FLAG_POWDER_MOVE            (1 << 19)
#define FLAG_TARGET_ABILITY_IGNORED (1 << 20)
#define FLAG_DANCE                  (1 << 21)
#define FLAG_DMG_IN_AIR             (1 << 22) // If target is in the air, can hit.
#define FLAG_DMG_2X_IN_AIR          (1 << 23) // If target is in the air, can hit and deal double damage.
//#define FLAG_DMG_UNGROUNDED_IGNORE_TYPE_IF_FLYING (1 << 24) // Makes a Ground type move do 1x damage to flying and levitating targets /realied already changed type so this doesn't do anything 
//#define FLAG_THAW_USER                            (1 << 25) //since changed thaw to conditional effect can remove this
//#define FLAG_TWO_STRIKES                          (1 << 27) // A move with this flag will strike twice, and may apply its effect on each hit //whgy is this necessary multihit already works that way?
#define FLAG_HIT_IN_SUBSTITUTE                    (1 << 24) // Hyperspace Fury  //3 byte
#define FLAG_ROCK_HEAD_BOOST        (1 << 25)   //EQUIvalent iron fist will boost moves that used head
#define FLAG_WIND_MOVE              (1 << 26)   //added for rotom ability
#define FLAG_LETHAL_LEGS_BOOST      (1 << 27)  //hitmon lee ability kick move boost
#define FLAG_ALWAYS_CRIT            (1 << 28)   //replace effect always crit do with flag check, simpler
#define FLAG_SHARPNESS_AFFECTED     (1 << 29)
#define FLAG_GROUND_DMG_FLOATING    (1 << 30)

#define FLAG_GROUND_HITS_FLOATING   (FLAG_DMG_IN_AIR | FLAG_DMG_2X_IN_AIR | FLAG_GROUND_DMG_FLOATING)

//thaw user and two strikes can be removed, FLAG_DMG_UNGROUNDED_IGNORE_TYPE_IF_FLYING  can also be removed 
//also flags are u32, so I beleive I can go up to 32 with this
//have 4 spaces left - removed kings rock flag use, so has 5 spaces now
//starts at 0 can go to 31, not 32

//if need/want to can repurpose FLAG_RECKLESS_BOOST, as EE uses a macro instead
//using the effect to determine if is a recoil move and should get the boost
//works because so few effects in category, just the 33 recoil etc and recoil if miss, and now overheat as well
//somehat unsure if changing overheat to recoil was good, makes sense for romhack as point is just to be as dangerous as possible
// but for competitive where dying for damage isn't valued I think it just makes it worse?
//especially since there are some mon that can work around the drop i.e mixed attackers,
//but there's a difference from using a strong move and all your attacks being worthless unless you switch, (taking damage on something else) and on switch in
//vs taking the hit but being able to stay in for more attacks guess effect is about the same so no point dropping the stat

#define SPINDA_SPOT_HEIGHT 16

struct SpindaSpot
{
    u8 x, y;
    u16 image[SPINDA_SPOT_HEIGHT];
};

struct LevelUpMove
{
    u16 move;
    u16 level; //coud make a bit field to save space here I'd use :7 as thaat's 128 & max lvl is 100
};//An address must be an integer number of bytes, but that is not necessarily the case for a bitfield, so it is illegal to attempt to get their address
//theoretically can make a calcuation that would generate bit fields given a constant i.e max level 100
//would save space but also potentially make things less flexible?

enum
{
    GROWTH_MEDIUM_FAST,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW
};

enum
{
    BODY_COLOR_RED,
    BODY_COLOR_BLUE,
    BODY_COLOR_YELLOW,
    BODY_COLOR_GREEN,
    BODY_COLOR_BLACK,
    BODY_COLOR_BROWN,
    BODY_COLOR_PURPLE,
    BODY_COLOR_GRAY,
    BODY_COLOR_WHITE,
    BODY_COLOR_PINK
};

//these two taken from new emerald setup not sure how to use yet
//understand it now, it uses EVOLUTIONS_END rather than evos_per_mon
//as limiting factor, so it'll check every evo method for said species
//rather than check a fixed number of times, unsure how it would handle conflicts
//think thaat would just be up to the make to ensure doesn't happen
//i.e don't use method level, w level night, would need to stipulate day so there's no overlap

//why does this have to go so high? can't
//I use 0xFF? cuz of how used in base stats
//think it needs to be 2 byte fill
#define EVOLUTIONS_END                    0xFFFF // Not an actual evolution, used to mark the end of an evolution array.
#define EVO_NONE                          0xFFFE // Not an actual evolution, used to generate offspring that can't evolve into the specified species, like regional forms.
//don't get this -not used either?

//:NOTE: If more form evo methods are added believe you need to replace the default method with them
//and add base method to end of list.
//otherwise with loop it'll just default to base method which is a problem if mon has multiple region evo paths
//ex. pika->raichu  pika->alolan raichu  both using item as evo method
//form method has more conditions so necessary to put it first to be ruled out before using default method
//:End Of Note:
//addendum note, its same for all evo methods, if you want to give a method priority it must be lower in value than the alternative methods
//this is only necessary when there would be evo methods that overlap ex. for tyrogue evo method gender with a separate evo method for move,  
//since both could be true but I want more priority to be give to move, I need to make sure that is lower - since trade is removed can swap w trade and trade item, 
//for any future evo methods I need to increase priority on, go over base stats and check for conflicts/overlap in evo methods
//only relevant for multiple evo methods that would result in different target species, irrelveant if target is same species (that can both be true)
//fixed added priority to evo logic, now that I know define value has nothing to do with it
//should reorg this just group like methods for sake of reading

//base methods
#define EVO_FRIENDSHIP       				0x0001 // Pokémon levels up with friendship ≥ FRIENDSHIP_EVO_LIMITER
#define EVO_FRIENDSHIP_DAY   				0x0002 // Pokémon levels up during the day with friendship ≥ FRIENDSHIP_EVO_LIMITER
#define EVO_FRIENDSHIP_NIGHT 				0x0003 // Pokémon levels up at night with friendship ≥ FRIENDSHIP_EVO_LIMITER
#define EVO_LEVEL            				0x0004 // Pokémon reaches the specified level
#define EVO_LEVEL_FEMALE     				0x0005 // Pokémon reaches the specified level, is female
#define EVO_LEVEL_MALE      				0x0006 // Pokémon reaches the specified level, is male
#define EVO_LEVEL_NIGHT     				0x0007 // Pokémon reaches the specified level, is night
#define EVO_LEVEL_DAY       				0x0008 // Pokémon reaches the specified level, is day
#define EVO_LEVEL_DUSK      				0x0009 // Pokémon reaches the specified level, is dusk (5-6 P.M)
#define EVO_LEVEL_RAIN     				    0x000a // Pokémon reaches the specified level while it's raining
#define EVO_LEVEL_SHELMET                   0x000b // Pokémon reaches the specified level (special value for Shelmet)
#define EVO_LEVEL_KARRABLAST                0x000c // Pokémon reaches the specified level (special value for Karrablast)
#define EVO_LEVEL_DARK_TYPE_MON_IN_PARTY    0x000d // Pokémon reaches the specified level with a Dark Type Pokémon in party

#define EVO_LEVEL_ATK_GT_DEF 				0x000e // Pokémon reaches the specified level with attack > defense
#define EVO_LEVEL_ATK_EQ_DEF 				0x000f // Pokémon reaches the specified level with attack = defense
#define EVO_LEVEL_ATK_LT_DEF 				0x0010 // Pokémon reaches the specified level with attack < defense
#define EVO_LEVEL_SILCOON    				0x0011 // Pokémon reaches the specified level with a Silcoon personality value
#define EVO_LEVEL_CASCOON    				0x0012 // Pokémon reaches the specified level with a Cascoon personality value
#define EVO_LEVEL_NINJASK    				0x0013 // Pokémon reaches the specified level (special value for Ninjask)
#define EVO_LEVEL_SHEDINJA   				0x0014 // Pokémon reaches the specified level (special value for Shedinja)
#define EVO_LEVEL_ABILITY      				0x0015 // pokemon levels up w certain ability, mostly just to replace rockruff owntempo
#define EVO_BEAUTY   		   				0x0016 // Pokémon levels up with beauty ≥ specified value
#define EVO_ITEM             				0x0017 // specified item is used on Pokémon

#define EVO_ITEM_HOLD  		    		    0x0018 // Pokémon levels up, holds specified item
#define EVO_ITEM_HOLD_DAY  		    		0x0019 // Pokémon levels up, holds specified item at day
#define EVO_ITEM_HOLD_NIGHT 				0x001a // Pokémon levels up, holds specified item at night
#define EVO_ITEM_DAY                        0x001b // specified item is used on a Pokémon at day
#define EVO_ITEM_NIGHT                      0x001c // specified item is used on a Pokémon at night
#define EVO_ITEM_FEMALE    				    0x001d // specified item is used on a female Pokémon
#define EVO_ITEM_MALE      				    0x001e // specified item is used on a male Pokémon
#define EVO_MOVE          				    0x001f // Pokémon levels up, knows specified move
#define EVO_MOVE_TYPE       				0x0020 // Pokémon levels up, knows move with specified type
#define EVO_MAPSEC          				0x0021 // Pokémon levels up on specified mapsec


#define EVO_SPECIFIC_MON_IN_PARTY         	0x0022 // Pokémon levels up with a specified Pokémon in party
#define EVO_SPECIFIC_TYPE_IN_PARTY         	0x0023 // Pokémon levels up with a specified Pokémon Type in party (made to bypass nosepass evo location requirement)

#define EVO_TRADE           			    0x0024 //not used just shifted for priority to evo move
#define EVO_TRADE_ITEM                      0x0025 // Pokémon is traded while it's holding the specified item
#define EVO_TRADE_SPECIFIC_MON   			0x0026 // Pokémon is traded for a specified Pokémon
#define EVO_SPECIFIC_MAP   				    0x0027 // Pokémon levels up in a specific room of a specified map.
#define EVO_LEVEL_NATURE_AMPED              0x0028 // Pokémon reaches the specified level, it has a Hardy, Brave, Adamant, Naughty, Docile, Impish, Lax, Hasty, Jolly, Naive, Rash, Sassy, or Quirky nature.
#define EVO_LEVEL_NATURE_LOW_KEY            0x0029 // Pokémon reaches the specified level, it has a Lonely, Bold, Relaxed, Timid, Serious, Modest, Mild, Quiet, Bashful, Calm, Gentle, or Careful nature.
#define EVO_MEGA_EVOLUTION					0x002a // (change later)Not an actual evolution, used to temporarily mega evolve in battle.
#define EVO_MOVE_MEGA_EVOLUTION		        0x002b // Mega Evolution that checks for a move instead of held item
#define EVO_PRIMAL_REVERSION                0x002c // Not an actual evolution, used to undergo primal reversion in battle.

#define EVO_CRITICAL_HITS                   0x002d // Pokémon performs specified number of critical hits in one battle
#define EVO_SCRIPT_TRIGGER_DMG              0x002e // Pokémon has specified HP below max, then player interacts trigger
#define EVO_DARK_SCROLL                     0x002f // interacts with Scroll of Darkness
#define EVO_WATER_SCROLL                    0x0030 // interacts with Scroll of Waters

#define EVO_LEVEL_FAMILY_OF_THREE           0x0037  //remember to add to add to evo priority list
#define EVO_LEVEL_FAMILY_OF_FOUR            0x0038  
#define EVO_MOVE_TWO_SEGMENT                0x0039
#define EVO_MOVE_THREE_SEGMENT              0x003a

//custom methods
#define EVO_MILCERY                         0x0031 //SPECIAL method for milcery will be friendship + special condition plan use unown personality to determine evo form
#define EVO_ITEM_FORM                       0x0032
#define EVO_LEVEL_FORM                      0x0033 //form evo methods, reads form flag from 2nd param, otherwise works same
#define EVO_LEVEL_FORM_NIGHT                0x0034
#define EVO_MOVE_TYPE_ATK_GT_DEF            0x0035 //for galarian slowbro
#define EVO_MOVE_TYPE_ATK_LT_DEF            0x0036 //new evo methods, for evolving galarian slowpoke - this for galarian slowking
#define EVO_HIGH_RICHES                     0x003b //method for gimmighoul evo 70k+ money
#define EVO_LEVEL_VIVILLON                  0x003c
#define EVO_MOVE_FORM                       0X003d
#define EVO_LEVEL_FRIENDSHIP                0x003e //level and high friendship
//all existing regional forms only use level, and item, (marowak uses level night) to evolve most have identical level except decidueye
//moved these to end so can read form data first

struct Evolution
{
    u16 method;
    u16 param;
    u16 param2;
    u16 targetSpecies;
};//thinking add 2nd param for more control
//ex would allow me to make general evo level method without having to use a pre-defined ability
//question is can I assign value to struct member when created i.e assign 0, so there's no garbage data
//rather than having to do that in a function
//well how it works now if a method doesn't use param its just set to 0
//tried can't assign values to struct member when defining, so I'll have to fill table w zeroes myself
//evo change worked, added 2nd param, zeroed out for existing values, will just need fill for new method changes
//if param 2 not mentioned in function still works fine

//planned change more complex late gen evo methods they suck and no one likes them, (think need keep for parafin though)
//ex. EVO_CRITICAL_HITS  change to level_critical_hit just be at level and land a critical hit and it would evolve
//think will keep level to 25, since these are modern mon and typically 3rd stage evo?, but can easily adjust
//ALWAYS order name convention to match order of param, i.e level critical hit 1st param level, 2nd param critical hit


struct FormChange {
    u16 method;
    u16 targetSpecies;
    u16 param1;
    u16 param2;
    u16 param3; //new adition from emerald logic
}; //may change based on how I use forms

//replaces front_pic_table back_pic_table front_pic_coordinates back_pic_coordinates pokemon_icon.c arrays palette_table  & shiny_palette_table
struct SpeciesGraphicInfo 
{

    const u32 *frontPic;
 /* 0x74 */ //u16 frontPicSize; // The dimensions of this drawn pixel area.
            //u16 tag;
 /* 0x50 */ const u32 *backPic;
 /* 0x76 */ //u16 backPicSize; // The dimensions of this drawn pixel area.

 /* 0x58 */ const u32 *palette;
 /* 0x60 */ const u32 *shinyPalette;

 /* 0x68 */ const u8 *iconSprite;

            u8 frontCoordSize;
 /* 0x75 */ u8 frontPicYOffset; // The number of pixels between the drawn pixel area and the bottom edge.

            u8 backCoordSize;
 /* 0x77 */ u8 backPicYOffset; // The number of pixels between the drawn pixel area and the bottom edge.

 /* 0x78 */ u8 iconPalIndex:3;
            u8 enemyMonElevation;
            struct ToneData *cryData; //couldn't figure set SetPokemonCryTone back to normal make macro fill all from here
}; //all of these values have macros excluding iconPalIndex which should allow me to copy directly from existing arrays
//think take all extra values/functions in file excluding table and put in single graphics file
//at make a macro to display place of each files start, and at top of consilidated file put goto MACRONAME  for each section
//for quick navigation


//believe still need this for daycare, review again and figure how to remove evo_cap, treid quickly stil had isue so reverted
#define EVOS_PER_MON 16 // set to 16 in case I need the shedinja byte change fix

//lvl gain needed for different evo thresholds
#define QUICK_EVO       5
#define LOW_EFFORT      10
#define AVERAGE_EFFORT  15
#define MEDIUM_EFFORT   20
#define ABOVE_AVERAGE_EFFORT 25
#define HIGH_EFFORT     30

extern u8 gPlayerPartyCount;
extern struct Pokemon gPlayerParty[PARTY_SIZE];
extern u8 gEnemyPartyCount;
extern struct Pokemon gEnemyParty[PARTY_SIZE];
extern const struct BaseStats gBaseStats[];
extern const u16 *const gGenderForms[];
extern const u16 *const gSpeciesGroups[];
extern const struct SpeciesGraphicInfo gSpeciesGraphics[];
extern const u8 *const gItemEffectTable[];
//extern const struct Evolution gEvolutionTable[][EVOS_PER_MON]; //plan remove replace w EE version built into basestats
extern const u8 gStatStageRatios[][2];
extern struct SpriteTemplate gMultiuseSpriteTemplate;
extern struct PokemonStorage* gPokemonStoragePtr;
extern const u32 gExperienceTables[][MAX_LEVEL + 1];
extern const struct LevelUpMove *const gLevelUpLearnsets[];
extern const u16 *const gTMHMLearnsets[];   //for adjusted new setup of tmhms, setup like levelup learnset
extern const u8 gFacilityClassToPicIndex[];
extern const u8 gFacilityClassToTrainerClass[];
extern const struct SpriteTemplate gSpriteTemplates_Battlers[];
extern const u8 gPPUpGetMask[];
extern const u16 *const gFormSpeciesIdTables[]; //needs include cosmetic so cant use numspecies
extern const struct FormChange *const gFormChangeTablePointers[NUM_SPECIES];


void ZeroBoxMonData(struct BoxPokemon *boxMon);
void ZeroMonData(struct Pokemon *mon);
void ZeroPlayerPartyMons(void);
void ZeroEnemyPartyMons(void);
void CreateMon(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId);
void CreateBoxMon(struct BoxPokemon *boxMon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId);
void CreateMonWithNature(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 nature);
void CreateMonWithGenderNatureLetter(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 gender, u8 nature, u8 unownLetter);
void CreateMaleMon(struct Pokemon *mon, u16 species, u8 level);
void CreateMonWithIVsPersonality(struct Pokemon *mon, u16 species, u8 level, u32 ivs, u32 personality);
void CreateMonWithEVSpread(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 evSpread);
void CreateBattleTowerMon(struct Pokemon *mon, struct BattleTowerPokemon *src);
void ConvertPokemonToBattleTowerPokemon(struct Pokemon *mon, struct BattleTowerPokemon *dest);
void CalculateMonStats(struct Pokemon *mon);
void TransformedMonLvlUpStatCalc(struct Pokemon *mon); //only for when a mon levels up while transformed, excludes setmon currhp
void TransformedMonHP(struct Pokemon *mon, u16 TransformAbility, u16 TransformedSpecies);
void TransformedMonStats(struct Pokemon *mon, u16 TransformAbility, u16 TransformedSpecies);
void RevertTransformedHP(u8 battlerId);
void GiveMonInitialMoveset(struct Pokemon *mon);
void GiveBoxMonInitialMoveset(struct BoxPokemon *boxMon);   //moved these defins here so could use in battle_main
void BoxMonToMon(struct BoxPokemon *src, struct Pokemon *dest);
u8 GetLevelFromBoxMonExp(struct BoxPokemon *boxMon);
u16 GiveMoveToMon(struct Pokemon *mon, u16 move);
u16 GiveMoveToBattleMon(struct BattlePokemon *mon, u16 move);
void SetMonMoveSlot(struct Pokemon *mon, u16 move, u8 slot);
void SetBattleMonMoveSlot(struct BattlePokemon *mon, u16 move, u8 slot);
u16 MonTryLearningNewMove(struct Pokemon *mon, bool8 firstMove);
u16 MonTryLearningEvoMove(struct Pokemon *mon, bool8 firstMove); //changing to use 0, with normal call forces level 0 learnig on each level up, so makeing separate
void DeleteFirstMoveAndGiveMoveToMon(struct Pokemon *mon, u16 move);
s32 CalculateBaseDamage(struct BattlePokemon *attacker, struct BattlePokemon *defender, u32 move, u32 sideStatus, u16 powerOverride, u8 typeOverride, u8 battlerIdAtk, u8 battlerIdDef);
//sidestatus meant to hold gsidestatus but forgot I had to upgrade that to u32 *facepalm

//recent emerald addditions, change for form change (not planning use for ditto/transform)
void TryToSetBattleFormChangeMoves(struct Pokemon *mon, u16 method);
bool32 TryFormChange(u32 monId, u32 side, u16 method);
u16 GetFormChangeTargetSpecies(struct Pokemon *mon, u16 method, u32 arg);
u16 GetFormChangeTargetSpeciesBoxMon(struct BoxPokemon *boxMon, u16 method, u32 arg);
bool32 DoesSpeciesHaveFormChangeMethod(u16 species, u16 method);
bool8 DoesSpeciesHaveCosmeticForms(u16 species);

#define BATTLE_ALIVE_EXCEPT_ACTIVE  0
#define BATTLE_ALIVE_ATK_SIDE       1
#define BATTLE_ALIVE_DEF_SIDE       2

u8 CountAliveMonsInBattle(u8 caseId);

u8 GetDefaultMoveTarget(u8 battlerId);
u8 GetMonGender(struct Pokemon *mon);
u8 GetBoxMonGender(struct BoxPokemon *boxMon);
u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);
void SetMultiuseSpriteTemplateToPokemon(u16 speciesTag, u8 battlerPosition);
void SetMultiuseSpriteTemplateToTrainerBack(u16 trainerSpriteId, u8 battlerPosition);

// These are full type signatures for GetMonData() and GetBoxMonData(),
// but they are not used since some code erroneously omits the third arg.
// u32 GetMonData(struct Pokemon *mon, s32 field, u8 *data);
// u32 GetBoxMonData(struct BoxPokemon *boxMon, s32 field, u8 *data);
/**/
#ifdef IS_POKEMON_C
u32 GetMonData(struct Pokemon *, s32, u8 *);
u32 GetBoxMonData(struct BoxPokemon *, s32, u8 *);
#else
u32 GetMonData();
u32 GetBoxMonData();
#endif // IS_POKEMON_C  seems like removing this was what made it work?
//*/ 
void SetMonData(struct Pokemon *mon, s32 field, const void *dataArg);
void SetBoxMonData(struct BoxPokemon *boxMon, s32 field, const void *dataArg);
void CopyMon(void *dest, void *src, size_t size);
u8 GiveMonToPlayer(struct Pokemon *mon);
u8 CalculatePlayerPartyCount(void);
u8 CalculateEnemyPartyCount(void);
u8 GetMonsStateToDoubles(void);
u16 GetAbilityBySpecies(u16 species, bool8 abilityNum);
u16 GetMonAbility(struct Pokemon *mon);
bool32 IsMonType(struct Pokemon *mon, u8 type); //uses get mondata species to check mon type from base stats, not battle type,  used for field poison
u8 GetSecretBaseTrainerPicIndex(void); //remove this later
u8 GetSecretBaseTrainerNameIndex(void); //remove this later
bool8 IsPlayerPartyAndPokemonStorageFull(void);
void GetSpeciesName(u8 *name, u16 species);
void GetAbilityName(u8 *namebuffer, u16 ability); //new functions added for Cap
void GetMoveName(u8 *name, u16 move);
void GetItemName(u8 *name, u16 item); //item names not done would need to decap all names, and they are in a field not a list *pain
void GetTmHm_Name(u8 *dest, u16 itemId);

u8 CalculatePPWithBonus(u16 move, u8 ppBonuses, u8 moveIndex);
void RemoveMonPPBonus(struct Pokemon *mon, u8 moveIndex);
void RemoveBattleMonPPBonus(struct BattlePokemon *mon, u8 moveIndex);
bool8 ExecuteTableBasedItemEffect(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex);
bool8 PokemonUseItemEffects(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex, u8 e);
bool8 PokemonItemUseNoEffect(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex);
u8 GetItemEffectParamOffset(u16 itemId, u8 effectByte, u8 effectBit);
const u8 *Battle_PrintStatBoosterEffectMessage(u16 itemId);
u8 GetNature(struct Pokemon *mon);
u16 GetEvolutionTargetSpecies(struct Pokemon *mon, u8 type, u16 evolutionItem);
u16 NationalPokedexNumToSpecies(u16 nationalNum);
u16 SpeciesToNationalPokedexNum(u16 species);
u16 HoennToNationalOrder(u16 hoennNum);
u16 SpeciesToCryId(u16 species);
void DrawSpindaSpots(u16 species, u32 personality, u8 *dest, bool8 isFrontPic);
void EvolutionRenameMon(struct Pokemon *mon, u16 oldSpecies, u16 newSpecies);
bool8 GetPlayerFlankId(void);
bool16 GetLinkTrainerFlankId(u8 linkPlayerId);
s32 GetBattlerMultiplayerId(u16 a1);
u8 GetTrainerEncounterMusicId(u16 trainer);
void AdjustFriendship(struct Pokemon *mon, u8 event);
void AdjustBoxMonFriendship(struct BoxPokemon *mon, u8 event);
void MonGainEVs(struct Pokemon *mon); //removed defeated species argument as no longer based on opponenet
u16 GetMonEVCount(struct Pokemon *mon);
void RandomlyGivePartyPokerus(struct Pokemon *party);
u8 CheckPartyPokerus(struct Pokemon *party, u8 selection);
u8 CheckPartyHasHadPokerus(struct Pokemon *party, u8 selection);
void PartySpreadPokerus(struct Pokemon *party);
bool8 TryIncrementMonLevel(struct Pokemon *mon);
u8 IsTMHM(u16 itemId);
u8 Isitem_HM(u16 itemId);
u16 GetTMHMNumberandCategory(u16 itemId); //still setting up
u8 ItemtoTMHMId(u16 itemId); //specifically made for SortAndCompactTmCase, as +1 of GetTMHMNumberandCategory funciion caused issue there
u32 CanMonLearnTMHM(struct Pokemon *mon, u16 tm); //change to u16 for both, later
u32 CanSpeciesLearnTMHMmove(u16 species, u16 move); //use this for move id, use CanMonLearnTMHM for item id based check
u8 GetMoveRelearnerMoves(struct Pokemon *mon, u16 *moves);
u8 GetLevelUpMovesBySpecies(u16 species, u16 *moves); //keep track of this for rotom forms 
u8 GetNumberOfRelearnableMoves(struct Pokemon *mon);//this too
u16 GetSpeciesPreEvolution(u16 species, u32 TargetLoop); //ported for pre evo checks
bool8 IsMonPastEvolutionLevel(struct Pokemon *mon, u32 i);// new port for simplify level evo checks
u16 GetTargetAlcremieForm(struct Pokemon *mon); //new logic for attempt make milcery evolve into diff alcremie forms based on personality, inspir by unown logic
u16 GetTargetVivillionForm(struct Pokemon *mon); //same thing but for vivillion
bool8 CanEvolveToRegionalForm(struct Pokemon *mon, u32 i); //new function for mon with alt form evos
bool8 IsRegionalVariant(u16 species); //new function to stand in for long code
bool8 UseRegionSand(struct Pokemon *mon); //new function say if mon canuse sand, still need function to read this and say what sand it can use
bool8 CheckFormViability(u8 formflags, u16 item); //last function needed, takes UseRegionSand as form flag argument
bool8 IsSameSpeciesFamily(u16 sourceSpecies, u16 comparisonSpecies); //new function compares species names, check if mon are in same species family, mostly for daycare updates
u16 SpeciesToPokedexNum(u16 species);
void ClearBattleMonForms(void);
void PlayBattleBGM(void);
void PlayMapChosenOrBattleBGM(u16 songId);
const u32 *GetMonSpritePal(struct Pokemon *mon);
const u32 *GetMonSpritePalFromSpeciesAndPersonality(u16 species, bool32 isShiny, u32 personality);
const u32 *GetMonSpritePalOfSpecies(struct Pokemon *mon, u16 species); //use mon for shiny retrieves set species, use for evolution scene mostly
//const struct CompressedSpritePalette *GetMonSpritePalStruct(struct Pokemon *mon);

//const struct CompressedSpritePalette *GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality);
//replaced previous
const u32 *GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality);
bool8 IsPokeSpriteNotFlipped(u16 species);
s8 GetFlavorRelationByPersonality(u32 personality, u8 flavor);
bool8 IsTradedMon(struct Pokemon *mon);
bool8 IsOtherTrainer(u32 otId, u8 *otName);
void MonRestorePP(struct Pokemon *mon);
void BoxMonRestorePP(struct BoxPokemon *boxMon);
void SetMonPreventsSwitchingString(void);
void SetWildMonHeldItem(void);

u8 *GetTrainerPartnerName(void);
u8 GetPlayerPartyHighestLevel(void);
u16 FacilityClassToPicIndex(u16 facilityClass);
bool8 ShouldIgnoreDeoxysForm(u8 caseId, u8 battlerId);
void SetDeoxysStats(void);
u16 GetUnionRoomTrainerPic(void);
u16 GetUnionRoomTrainerClass(void);
void CreateEventLegalEnemyMon(void);
void HandleSetPokedexFlag(u16 nationalNum, u8 caseId, u32 personality);
bool8 CheckBattleTypeGhost(struct Pokemon *mon, u8 bank);
struct OakSpeechNidoranFStruct *OakSpeechNidoranFSetup(u8 battlePosition, bool8 enable);
void OakSpeechNidoranFFreeResources(void);
void *OakSpeechNidoranFGetBuffer(u8 bufferId);
u16 GetFormSpeciesId(u16 speciesId, u8 formId);
u8 GetFormIdFromFormSpeciesId(u16 formSpeciesId);
u8 GetFinalFormSpeciesId(u16 formSpeciesId); //added for dex changes to read forms
u16 GetBaseStatTotal(u16 species);
u16 GetIndividualBaseStatValue(u16 species, u8 statIndex); //pull base stat for selected stat //mostly used for settin up new ev caps logic
u16 GetGlobalStatTotal(struct Pokemon *mon); //takes stats from evs + bst //for use as limiter
bool8 CanEvioliteActivate(u8 target);
s16 atk_diff(void);
s16 spatk_diff(void); //put here, used for hidden power change split
bool8 IsPhysicalMove(u32 attackerId, u16 move); //new function consolidating effects for if move is physical or not

const struct LevelUpMove *GetSpeciesLevelUpLearnset(u16 species);
const u16 *GetSpeciesTeachableLearnset(u16 species);
const struct Evolution *GetSpeciesEvolutions(u16 species);
u16 SanitizeSpeciesId(u16 species);
//new functions for file reorg based on EE
u8 GetFormType(u16 species); //set mostly for dex changes
struct ToneData *GetCryIdBySpecies(u16 species); //added for cry table rehash

//u8 IsMonShiny(struct Pokemon *mon); //for species graphic file setup
bool8 IsMonShiny(struct Pokemon *mon);
bool8 IsBoxMonShiny(struct BoxPokemon *mon);
bool8 IsShinyOtIdPersonality(u32 otId, u32 personality);
const u32 *GetMonSpritePalFromSpecies(u16 species, bool32 isShiny);

void PokemonToBattleMon(struct Pokemon *src, struct BattlePokemon *dst);


//ported things for debug
u8 GetNatureFromPersonality(u32 personality);
u8 SendMonToPC(struct Pokemon* mon);
void GiveBoxMonInitialMoveset_Fast(struct BoxPokemon *boxMon);
void GiveBattleMonInitialMoveset_Fast(struct Pokemon *mon, u16 Species); //made attempt get inversion move set change worknig 

#endif // GUARD_POKEMON_H
