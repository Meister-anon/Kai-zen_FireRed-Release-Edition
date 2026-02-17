#ifndef GUARD_POKEMON_H
#define GUARD_POKEMON_H

#include "global.h"
#include "sprite.h"
#include "move.h"
#include "data.h"
#include "constants/form_change_types.h"
#include "constants/pokemon.h"
#include "constants/battle.h"
#include "pokemon_icon.h"
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

struct AbilityInfo
{
    u8 name[ABILITY_NAME_LENGTH + 1];
    const u8 *description;
    s8 aiRating;
    u8 cantBeCopied:1; // cannot be copied by Role Play or Doodle
    u8 cantBeSwapped:1; // cannot be swapped with Skill Swap or Wandering Spirit
    u8 cantBeTraced:1; // cannot be copied by Trace - same as cantBeCopied except for Wonder Guard
    u8 cantBeSuppressed:1; // cannot be negated by Gastro Acid or Neutralizing Gas
    u8 cantBeOverwritten:1; // cannot be overwritten by Entrainment, Worry Seed or Simple Beam (but can be by Mummy) - same as cantBeSuppressed except for Truant
    u8 breakable:1; // can be bypassed by Mold Breaker and clones
    u8 failsOnImposter:1; // doesn't work on an Imposter mon; when can we actually use this?
    u8 padding:1;
    struct {
    u16 percentHp:7; //make function get ability hp threshold take value use percenttohp
    u16 comparison:3; //use Comparison_Operators_Constants use as argument for CheckBattlerHpThreshold to get result
    }basedOnHp;
    u16 numAllowedInParty:2; //restriction
    u16 isSingleUse:1;//every single use has a timer not every timer is singleUse
    u16 timer:3;//using timer here rather than a volatile meant to represent a timer that isn't reset on switch
};
//ok think can set usedsingleuse ability on switch
//if ability has no timer? hmm most all have timers tho
//yeah they all have timers
//ok so they all have timers will setusedsingleuse ability
//only if timer is expended
//original point was to prevent timers from resetting in first place
//was a fix for slow start
//make functions for should set SingleUseAbilityTimer
//hmm actually think will rename party effect to just keep track
//of party member ability timer
//that way can make effects with timer that aren't single use
//but that obviously I wouldn't want to be able to be abused by switching
//ex diff of having an ability that stat boosts for 3 turns on switch in
//and having the 3 turns be counted concurrently
//vs constantly reset
//the former is more balanced.
//ok renamed partydata field, will be used to store all abilityTimers
//but when timer ends if ability is singleuse stores
//ability to usedSingleUseAbility field 
//would prevent ability from reactivating, but if somehow
//another ability was passed or given wouldnt affect its activation
//which is what I want

//basedonHp will be value from 0-100 which would be bit 7
//isRestricted or Restriction would be num mon restricted to think making bit 2 is fine but most values would be 1 0 is no restriction
//isSingleUse can just be a Bool
//think last thing need from there is a
//the timer max rn is 5 plan use 1 for forewarn anticipation
//so bit 3 should cover that well enough
//so turn bit field into a u32 should cover everything
//leave raiting out as is signed

//talked with Alex logic is mostly if involves a form or something that would cause bug if transferred
//can't be copied swapped or traced, 
//for skill swap wonder guard idea make move end effect if curr move effect skill swap etc.
//and hp doesn't equal 1 set hp to 1 and go to update hp bar script
//check existing logic if I didn't already do something

//for modern have to specifically consider struct order for proper padding/space saving
//starts w u32 so is 4byte aligned, struct is organized in groups of 4byte sections
//note will most likely have to rearrange again when change mame buffers vsonic IMPORTANT
//need make boxHp u16 but don't have enough space
//need find room somehow if I put in bitfield
//it'll require bit 10, can I make a ribbon u8?
//can I remove hasSpecies?
//hmm ok pokerus isn't even in fire red
//and don't exactly need with my other qol changes
//removed pokerus
//can remove hasSpecies and MON_DATA_SANITY_HAS_SPECIES checks
//for use of mon_data_species, or species_or_egg not equal egg
struct BoxPokemon
{
    u32 personality;
    u32 otId;
    u8 nickname[POKEMON_NAME_LENGTH];
    
    
    u8 otName[OT_NAME_LENGTH]; //odd name length so believe makes even again
    u8 cuteRibbon:3;
    u8 toughRibbon:3;
    u8 victoryRibbon:1; //this and winning ribbon //these two for emerald battle tower
    u8 padding:1;
    
    u8 language:3; // 7 languages
    u8 nature:5;  // 1-0xF is the timer. 0x10 is set when timer runs out  //single byte think odd, think will reset back to EE way so doesn't potentially affect nature set odds/distribution
    u8 isMonShiny:1; //potentially replace w removal of checksum? //yeah can get rid of this its all determined by checksum replace w shiny set
    u8 isEgg:1;
    u8 winningRibbon:1; //made more space for padding
    u8 storedviaMobilePc:1; //for tracking if mon came from mobile pc for hp reconsiliation
    u8 metGame:4;    //byte 29?
    //byte 30? so even again - ok perfect so should be able to add u16 below this to not add extra padding
    u8 NoBoxExp:1; //true false is all I need for this
    u8 UseTaughtAbility:1; //true false
    u8 hideEggSpecies:1; //use for hide egg species, for certain gift eggs you wnt to be a surprise pretty much just restore default logic but just for this add argument to function shouldhideeggspecies and read that to set boxmon value within function put true/false in macros think giveegg givesecretegg
    u8 HiddenPowerType:5; //20 types need bit 5 to store //may just set its own byte to keep padd space //need add new u16 removnig pad to save space
    u8 cool; //put to fix odd/even //think read that wrong, putting there broke it so now toss on end, no it was right

    u32 species:11;
    u32 heldItem:10; //looks like both of these will be bit 10
    //don't need bit 11 for this just that's the freed space
    //default ev count can fit in bit 9
    //so at most I guess I'd need bit 10 for this,
    //if I realy needed to free up more space
    //so new idea is all mon give flat evs on death
    //but you have to pay to allocate them
    //using or holding a training item
    //would auto allocate gained evs directly to a stat
    //think what I'll do is keep ev gain invisible
    //and then have a point in the game where I explain the system
    //and show players how to access menu etc.
    //think will be like other sum screen stuff just press start
    //on specific page but guess have flag check or new game plus mode
    //so its not activated by accident
    //makes first playthrough harder but also makes
    //new game plus more things to work with from start
    //think will do at the saffron fighting gym
    //after beating gym have an npc sell training items from there
    //planning same thing for erica's gym but berry stuff
    //vsonic important
    u32 totalUnallocatedEvs:11;//couple ways can do, pay to set or only pay to respec if former ev items bypass cost and auto set for free would require reset base stats exp yield thankfully didn't delete bs values would just need regexsub to make general evs
 
    u8 ppBonuses;
    u8 otGender:1;
    u8 metLevel:7;
    u8 metLocation;

    u8 friendship;
    u8 formflag;
    u8 hatched:1;  //new thing to replace met level 0 in daycare - need test to make sure doesn't mess w evoLevel
    u8 evoLevel:7;

        //think I can make space by turning this into bit field
    //has sub 400 abilties rn with everything if I make bit 9 can hold 512 max
    //then move some ribbons in to fill space
    //added back type to abilityId since curr abilities are at 400
    u16 LearnedAbilityId:10; //after all done may add byte back to this to give more space for cap at 10 would be +1k
    u16 beautyRibbon:3;
    u16 smartRibbon:3;

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
    u32 pokeball:5; //pokeball stored in? curr allows for 32 diff values 0-31, not sure of exact value stored to rn

    u32 speedEV:9;
    u32 spAttackEV:9;
    u32 spDefenseEV:9;
    u32 championRibbon:1; //hall of fame league champion ribbon
    u32 effortRibbon:1; //given for a pokmeon that maxed EVs, have already updated script commands, still need update field_specials commands for box access instead of just party
    u32 coolRibbon:3;    //these are 3 because multiple levels, so can't lower
    
    u32 experience:21; //there are 31 natures? either way need bit 5
    u32 boxHp:10;
    u32 hasSpecies:1;    //MON_DATA_SANITY_HAS_SPECIES and all mentions of bad egg can be removed
    //u32 beautyRibbon:3; //running short on ewram; while cool think may scrap lostlocation so can set nature //when I do nature task think need run calcmonstat to readjust

    u8 beauty;
    u8 cute;
    u8 smart;
    u8 tough;

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

//note size of struct pokemon does effect ewram
//goes through struct PokemonStorageSystemData
//which stores the struct multiple times
//in that case I might as well use up my free space
//and its a bad idea to attempt store form data here
//...but there's literally no where else to put it
//yeah go ahead and use the space, its necessary for
//4 byte allignment anyway

//looks weird but keep struct at top rather than bottom for sake of match
//form species change don't put in pokemon struct
//just make its own buffer store one value
//don't need for entire party as only one mon can activate anyway
//potentially change mail to bitstruct
//use 1 bit for is formbuffer active
//that way can know to load relevant data from form buffer
//instead of pokemon struct
//to ensure buffer not accidentally overwritten
//store species of form changed into
//and personality so I know regardless of slot position
//which mon it is
//and only to reset values stored to form buffer
//if species and or personality differ from what's inside
//store both only for rare chance have multiple of the same species
//in party able to formchange into same form stored
//...but in that case would need identifier so dont
//form change wrong one... *facepalm
//sigh ok now need make a paryt menu symbol or icon
//for form stored mon
struct Pokemon
{
    struct BoxPokemon box; //size of this is size of mon in box, so multiply by mon in box x number of boxes to get size boxes take
    u32 status;
    u16 hp;
    u16 maxHP;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
    u16 pickupCounter;// - from 4 allignment
    u8 StatusSetState:2;//states are both 3 options so take bitfield 2
    u8 Exp_state:2; //sinec is 4 alligned need pad byte can't make up space
    u8 DenyEvolution:1;//new field for evolution rework need set at end of battle check for evo
    u8 padding:3;//not just lvl up from exp function need update eviolite and everstone remove evo block logic
    u8 level;
    u8 mail; //remove mail   vsonic
    //u8 isFormbufferActive:1; //replacement for mail
    //u8 freespace:7;
    u8 padspace;
   
};//ok with the stuff I added
//I now have 2 bytes of extra space
//I plan to remove mail 
//removing mail won't save space
//as for allignment will still need
//to keep value for padding byte
//new idea I will have 3 bytes of unused space
//when done could use 2 bytes
//to make pickup timer attached to pokemon itself
//that way intead of var could have multiple individual
//opportunities to get resoures
//making the weak pickup mon
//the most advantageous for nuzlockes/resource farming
//seems fine, even EE doens't have extra things
//stored to pokemon struct



//believe put formchange stuff here
//thikn long as keep out of boxPokemon
//will be able to add on but not take up ewram
//needed for pc expansion
//need 4 u16 for move and pp data
//ivs will stay same but want Evs to be unique for form
//initial just copy ev from base form to form ev
//but allow changes to be made to form evs
//that won't track to base on revert
//but then again if dont change 
//would want to keep evs gained when in form...

//being able to put my form stuff directly on the
//pokemon would be much easier and remove need
//for form buffer
//slightly annoying that it would 
//add on stuff that not every mon could use
//but functionally worthwhile,
//and consistent i.e not every mon can evolve
//and yet evo data is on basestats struct
//vsonic important since form have different learnset
//will need to adjust trainer party data struct for forms
//if mon should mega evolve it'll need a separate move set
//for mega form think keep megas to single ability
//much simpler to deal with


//note plan for this was store base form and form to change into
//but realized there are mon with more than 1 mega form
//and without requiring mon to hold specific mega stone to
//determine the form to change into will need some other determinator
//maybe should make 3 slots have them be numbered by form?
//0 be base form
//1 be first mega form ex charizard x
//2 be 2nd mega form ex charizard y ?
//and when its trying to transform mid battle,
//it should read slot 1 and 2 for said pokemon
//and transform based on whichever one is NOT empty/NULL?
//or just move1 isn't 0? since I can just check first byte value?
//will need to make sure to 0 out the data at the party slot
//for a mon removed from the party either via trade, daycare or pc
//vsonic
struct FormDataStorage {
    u16 move1:10;
    u16 pp1:6;
    u16 move2:10;
    u16 pp2:6;
    u16 move3:10;
    u16 pp3:6;
    u16 move4:10;
    u16 pp4:6;

    //idea ev duplicate for forms
    //so its not lost when boxed
    //is much more a pain to reset evs than moves
    //after you change forms
    u32 Form_hpEV:9; //FACEPALM I never adjusted these for the new cap!!! //max per stat 360
    u32 Form_attackEV:9; //wich is bit 9
    u32 Form_defenseEV:9;    
    u32 abilityNum:2;
    u32 blank:3;

    u32 Form_speedEV:9; //FACEPALM I never adjusted these for the new cap!!! //max per stat 360
    u32 Form_spAttackEV:9; //wich is bit 9
    u32 Form_spDefenseEV:9;  
    u32 HiddenPowerType:5;  //perfectly fits free space, add in case want to change
    
   //goes over ewram cap
   //belive applying compression update can save
   //me enough ewram to add this for form update
   //found way to fix do fangame style ev respec
   //can allocate from the pool of available unallocated evs
   //just need a single u16 field to keep track of unallocated evs
   //works against idea of evs only given via macho bracer
   //as if a mon is used in mega form it couldn't gain evs
   //so will combine, make ev items proper way to train
   //but think fighting any mon will give a single ev
   //to unallocated evs?
   //Setting evs through respec/allocation will cost money
   //but a flat amount per respec rather than based on
   //how many evs you're moving think 10-15k
   //but using an ev item will directly allocate evs
   //to the desired stat
   //by default copy mon's exact ev distriution when change forms
   //then allow to respec and save specific distribution for said form
   //seems odd to have so many differences i.e full ev change and moves
   //but think about like full transformation it makes sense
   //its all the same things that change with use of transform

    u8 ppBonuses;    //potentially remove for space and simplicity, lost on boxing so not much point
    u8 blankspace; //if give megas hidden ability then I need to store abilityNum so that reverts correctly too
    u16 species;
    u32 personality;

};
//8 x 4 =32  x 6 = 130 bytes
//guess should be 10 bytes total
//then storage is that times 2
//for entire party
//so 120? (actual is 144)
//wondering if i need pp fields as well here? unsure how pp decrement/storage works rn
//base game uses ppbonus in single u8 so 
//guess I don't need a field for each move?

//put buffer in ewram would prefer to dynamically allocate
//memory but I'm bad with that
//plan is to get it working as is,
//then attempt make dynamic
#define MAX_FORM_DATA_STORED 2

#define BASE_FORM 0
#define CHANGED_FORM 1
//realied don't need make extra slot 
//I just need to store species in form data
//in task I can chose which species I want to form change to
//of those available simple.

//its only charizard and mewtwo that have 2 mega forms
//and thankfully they are both X / Y forms

//for battle transform first check if has more than 1 mega form
//or just check base species yeah that's simpler, no loop involved
//just transform if not divergengt species
//otherwise loop form space starting from value 1, to 2
//and if non 0 break and just transform into that form
//but how does that tell it what species to turn into?
//need to figure that out, since I guess I want to add dynamax?
//hmm but I"m turning gigantimax into new meags so that doesn't work
//well I guess it can just go through the form change table
//if the only forms are mega and primal reversion?
//and mon that have other forms i.e hoopa tornadus etc.
//don't have megas so I guess that would work
//so think would nee to take mega form value and do - 1
// to find correct species in table?
//or I can change table lookup, so it can use mega form number
//in said lookup
//param 1 has the item  to transform, 
//param 2 data filled in for form buffer slot
//but then that would mean can't use it unless you've 
//actually set moves beforehand...? idk
//its how you should do it but idk if its how you need to?


//meant to store move info for mon swaping between forms,
//ex base moves w pp bonus for base form and set moves for alt form
//so can keep assigned moves between forms,
//resets when goes in box
//need assignn memory think will make ewram value?
//putting in battle main set from overworld
//but will be accessed in battle so fine
//form variable will be directly set by function accessing array/value
//will have task to check if can change form, 
//loop party for single use form i.e mega/primal reversion
//depending on what forms the mon in question has
//if mon has a mega loop party check if mega/primal species is in party
//note mon revert on enter pc
//after that works can have unique learnsets for forms
//had wrong idea can work for anymon in party don't need store for EVERY
//mon in party wait actually no I do need it for every mon
//just don't need the extra 2 form stuff
//needed for every so can store data for any mon
//so any mon can be viable to form change
extern struct FormDataStorage gFormSwapBuffer[PARTY_SIZE];


bool32 CanEvolve(u32 species);
u8 GetLevelFromMonExp(struct Pokemon *mon);
u16 ModifyStatByNature(u8 nature, u16 stat, u8 statIndex);//made global for bs command level up calc
u8 GetMonHiddenPowerType(struct Pokemon *mon); //simplified call
u8 GetBattlerHiddenPowerType(enum BattlerId battler);
void SetHiddenPowerType(struct BoxPokemon *mon);

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

#define UNPACK_VOLATILE_STRUCT(_enum, _fieldName, _typeMaxValue, ...) INVOKE_WITH_(UNPACK_VOLATILE_STRUCT_, _fieldName, UNPACK_B(_typeMaxValue));
#define UNPACK_VOLATILE_STRUCT_(_fieldName, _type, ...) _type FIRST(__VA_OPT__(_fieldName:BIT_SIZE(FIRST(__VA_ARGS__)),) _fieldName)

//replaced disablestructs
struct Volatiles
{
    VOLATILE_DEFINITIONS(UNPACK_VOLATILE_STRUCT)
    // Expands to:
    // u32 confusionTurns:3;
    // u32 flinched:1;
    // u32 uproarTurns:3;
    // etc.
};

//EE has otid at bottom,
//my version alingns to 4 bytes rather than 2
//go over see which works best
struct BattlePokemon
{
    /*0x58*/ u32 otId; //may not need status4 in struct status3 & 4 seem to work through gstatuses3 & gstatus4 the same as status 2 already?

    /*0x00*/ u16 species;
    /*0x02*/ u16 attack;
    /*0x04*/ u16 defense;
    /*0x06*/ u16 speed;
    /*0x08*/ u16 spAttack;
    /*0x0A*/ u16 spDefense;
    /*0x0C*/ u16 moves[MAX_MON_MOVES];
    
    /*0x14*/ u32 hpIV:5;
    /*0x14*/ u32 attackIV:5;
    /*0x15*/ u32 defenseIV:5;
    /*0x15*/ u32 speedIV:5;
    /*0x16*/ u32 spAttackIV:5;
    /*0x17*/ u32 spDefenseIV:5;
    /*0x17*/ u32 abilityNum:2;
    /*0x18*/ s8 statStages[BATTLE_STATS_NO];
    /*0x20*/ u16 ability; //this is off throws off rest should be 2 bytes not 1
    /*0x22*/ u8 type1;
    /*0x23*/ u8 type2;
    /*0x24*/ u8 type3; //no space change replaced unknown
    /*0x25*/ bool8 isShiny:1; //take ismonshiny pass on set battle data put here for alingment idk if can be bitfield
             bool8 isEgg:1;
             u8 padding:6;
    /*0x26*/ u8 pp[MAX_MON_MOVES];
    /*0x29*/ u16 hp;
    /*0x2B*/ u8 level;
    /*0x2C*/ u8 friendship;
    /*0x2D*/ u16 maxHP;
    /*0x2F*/ u16 item;
    /*0x31*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x3C*/ u8 ppBonuses;
    /*0x3D*/ u8 otName[OT_NAME_LENGTH + 1];             
    /*0x45*/ u32 experience;
    /*0x49*/ u32 personality;
    /*0x4D*/ u32 status1;   //stays on switch
             struct Volatiles volatiles; //replace other statusses

}; 

//believe all fields default to 0, if not set?
//nope is just nothingn so need to set to false in base
//I think its just used like a pointer if I don't put something there
//or set to the struct to 0, in main, it'll just be garbage data
//so yeah I need to set it myself
struct SpeciesInfo  // had to adjust struct order to match paste value from base_stats.h
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
            u8 speciesName[POKEMON_NAME_LENGTH + 1];
 /* 0x1E */ u8 padspace;   //will be replaced w padding but keeping here for now
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
 /* 0x16 */ enum Ability abilities[2]; //[partysize] is 6 values, so this is ability 1 and ability 2, doesn't include hidden //this means 2 states, 0 & 1
 /* 0x1B */ enum Ability abilityHidden[2]; //need to make sure ability num can be 2, then set that as hidden ability
 /* 0x1D */ //u16 bodyColor : 7; //ok bodyColor is leftover of emerald is literally just an pokedex filter option that doesn't exist in fr, but is here for sake of trading to those games
            // Flags
            u16 noFlip : 1;  //represents if sprite is flipped in summary screen and trade screen, normal is the pc sprite
            u16 floating : 1; // logic flying and non flying mon that can fly/float or who's natural state is floating, (replace levitate) mon has to display ability to do more than just hover slightly over ground to exclude legendaries to prevent destroy groud type, think need logic for mon to do most of its fighting in air as well
            u16 isLegendaryOrMythical:1;
            //u16 isMythical:1; //will combine these two as practically no real distinction
            u16 isUltraBeast:1; //handling elsewhere curr can blank for more space
            u16 isParadox:1; //can do same logic for ultra beast as is only for Booster Energy
            u16 isPrimalReversion:1;
            u16 isUltraBurst:1; //is only necrozma so idk why need this? just for sake of identifying mechanic i.e can code that it should work like mega but isn't mega, but think coudl consolidate w primal reversion?
            u16 isMegaEvolution:1; //nvm primal reversion is stronger than mega, huh, doesn't get removed on faint, better to not consolidate as would need to filter for battle mechanic allowed to use, as they don't block each other can use both in battle
            u16 isTeraForm:1;
            u16 isAlolanForm:1;
            u16 isGalarianForm:1;
            u16 isHisuianForm:1;
            u16 isPaldeanForm:1;
            u16 hasCosmeticForms:1;
            u16 buffer:2; //can get more space if remove ultrabeast and paradox, as those are niche use and can be handled with simple species filter
            const struct AbilityLearnset *abilityLearnset;
            const struct LevelUpMove *levelUpLearnset; //replace leveluplearnset pointers file, below replace tmhmlearnset pointers file
            const u16 *tmhmLearnset; //these are just names, in struct will be .name
            const struct Evolution *evolutions;
};



#define IS_CRIT (gCritMultiplier > 1)

// Battle move flags
#define FLAG_MAKES_CONTACT          (1 << 0)
#define FLAG_PROTECT_AFFECTED       (1 << 1)
#define FLAG_MAGIC_COAT_AFFECTED    (1 << 2)
#define FLAG_SNATCH_AFFECTED        (1 << 3)
#define FLAG_MIRROR_MOVE_AFFECTED   (1 << 4)    //check if move allowable with mirror move to copy
#define FLAG_GRAVITY_CANCELED       (1 << 5)    //for moves that get canceled by gravity field status
#define FLAG_HIGH_CRIT              (1 << 6)
#define FLAG_RECKLESS_BOOST         (1 << 7)    //just for recoil finding
#define FLAG_IRON_FIST_BOOST        (1 << 8)    //1 byte
#define FLAG_SHEER_FORCE_BOOST      (1 << 9)
#define FLAG_STRONG_JAW_BOOST       (1 << 10) //biting
#define FLAG_MEGA_LAUNCHER_BOOST    (1 << 11) //pulse move
#define FLAG_EVASIVE_BREAK          (1 << 12)   //reworked minimize effect //sure hit if evasion stage boosted and ignore other boosted evasion effects
#define FLAG_DMG_2X_UNDERGROUND     (1 << 13)
#define FLAG_DMG_2X_UNDERWATER      (1 << 14)
#define FLAG_SOUND                  (1 << 15)   //2 byte
#define FLAG_BALLISTIC              (1 << 16)
#define FLAG_PROTECTION_MOVE        (1 << 17)
#define FLAG_POWDER_MOVE            (1 << 18)
#define FLAG_TARGET_ABILITY_IGNORED (1 << 19) //just sunsteeel strike and moongeist beam but still unsure what does?, ok is mold breaker effect but as a move, ex can ignore wonder guard
#define FLAG_DANCE                  (1 << 20)
#define FLAG_DMG_IN_AIR             (1 << 21) // If target is in the air, can hit.
#define FLAG_DMG_2X_IN_AIR          (1 << 22) // If target is in the air, can hit and deal double damage.
//#define FLAG_DMG_UNGROUNDED_IGNORE_TYPE_IF_FLYING (1 << 24) // Makes a Ground type move do 1x damage to flying and levitating targets /realied already changed type so this doesn't do anything 
//#define FLAG_THAW_USER                            (1 << 25) //since changed thaw to conditional effect can remove this
//#define FLAG_TWO_STRIKES                          (1 << 27) // A move with this flag will strike twice, and may apply its effect on each hit //whgy is this necessary multihit already works that way?
#define FLAG_HIT_IN_SUBSTITUTE      (1 << 23) // Hyperspace Fury  //3 byte  //could prob remove this and just put in substitute function? vsonic
#define FLAG_HEADBUTT_MOVE        (1 << 24)   //EQUIvalent iron fist will boost moves that used head
#define FLAG_WIND_MOVE              (1 << 25)   //added for rotom ability
#define FLAG_LETHAL_LEGS_BOOST      (1 << 26)  //hitmon lee ability kick move boost
#define FLAG_ALWAYS_CRIT            (1 << 27)   //replace effect always crit do with flag check, simpler
#define FLAG_SHARPNESS_AFFECTED     (1 << 28)
#define FLAG_UNUSUED_MOVE_CAT       (1 << 29)   //unsure if keeping this vaery sparse not as useful as knock down unsure if category is worthwhile
#define FLAG_FREE_SPACE             (1 << 30)   //unsure if will use for this idk maybe find something else, but don't think have need for other effect
#define FLAG_BLANKSPACE             (1 << 31)   //removed flag was FLAG_STAT_STAGES_IGNORED noww move effect instead

#define FLAG_DAMAGE_AIRBORNE          (FLAG_DMG_IN_AIR | FLAG_DMG_2X_IN_AIR)

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

//think can use level_up_learnsets as template 
//use pyton to generate new abilityLearnsets file
//just copy cerain data to new array
//lines w static const struct, LEVEL_UP_END & }; w new line characte
//if line is }; new line  add that to list but also append extra new line character
//to add space before next value
struct AbilityLearnset
{
    u16 Teachable_Ability;
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
    u16 param3;
    u16 param4;
};

struct FormChangeContext
{
    enum FormChanges method:16;
    u16 currentSpecies;
    u16 partyItemUsed;
    u16 multichoiceSelection;
    u16 heldItem;
    u16 ability;
    u16 learnedMove;
    u32 status;
    u16 moves[MAX_MON_MOVES];
    u16 hp;
    u16 maxHP;
    u32 gmaxFactor:1;
    enum Type teraType;
    u32 level:7;
    u32 padding:8;
};

enum FusionExtraMoveHandling
{
    FORGET_EXTRA_MOVES,
    SWAP_EXTRA_MOVES_KYUREM_WHITE,
    SWAP_EXTRA_MOVES_KYUREM_BLACK
};

struct Fusion
{
    u16 fusionStorageIndex;
    u16 itemId;
    u16 targetSpecies1;
    u16 targetSpecies2;
    u16 fusingIntoMon;
    u16 fusionMove;
    enum FusionExtraMoveHandling extraMoveHandling;
};
//looking at this it seems it has most 
//of the logic I want for my form change already
//stores all relevant data of the fusion mon
//until needed for reversion
//so can prob just use that
//for what I have planned
//fusion stuff fails if party full
//prompts to remove mon first
//so that's fine with my mobile pc setup is easy

extern const struct Fusion *const gFusionTablePointers[NUM_SPECIES];


//replaces front_pic_table back_pic_table front_pic_coordinates back_pic_coordinates pokemon_icon.c arrays palette_table  & shiny_palette_table
struct SpeciesGraphicInfo 
{

    const u32 *frontPic;
 /* 0x74 */ //u16 frontPicSize; // The dimensions of this drawn pixel area.
            //u16 tag;
 /* 0x50 */ const u32 *backPic;
 /* 0x76 */ //u16 backPicSize; // The dimensions of this drawn pixel area.

 /* 0x58 */ const u16 *palette;
 /* 0x60 */ const u16 *shinyPalette;

 /* 0x68 */ const u8 *iconSprite;

            u8 frontCoordSize;
 /* 0x75 */ u8 frontPicYOffset; // The number of pixels between the drawn pixel area and the bottom edge.

            u8 backCoordSize;
 /* 0x77 */ u8 backPicYOffset; // The number of pixels between the drawn pixel area and the bottom edge.

 /* 0x78 */ u8 iconPalIndex:3;
            u8 enemyMonElevation;
            struct ToneData *cryData; //couldn't figure set SetPokemonCryTone back to normal make macro fill all from here
            struct ToneData *cryData_Reverse;
}; //all of these values have macros excluding iconPalIndex which should allow me to copy directly from existing arrays
//think take all extra values/functions in file excluding table and put in single graphics file
//at make a macro to display place of each files start, and at top of consilidated file put goto MACRONAME  for each section
//for quick navigation


//believe still need this for daycare, review again and figure how to remove evo_cap, treid quickly stil had isue so reverted
#define EVOS_PER_MON 16 // set to 16 in case I need the shedinja byte change fix

//decided like idea of keeping evo levels high/where they were
//pokemon treats power and evolution as a function of bonds
//so makes sense that even if a pokemon was strong it would need 
//time together to unlock power of evolution
//could also be a balane thing the wild evo level is high
//or a mon could be presented late in game
//and be a counter to a fight but not be able to
//get it up to lvl before lvl cap ex elite four
//so you either have to use it un evolved
//or breed it and raise that mon up,
//where it would evolve much lower
//like the idea of incentivizing breeding
//spending time training a mon
//idk if could make the most of this mechanic tho
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
extern const struct SpeciesInfo gSpeciesInfo[];
extern const u16 *const gGenderForms[];
extern const u16 *const gSpeciesGroups[];
extern const struct SpeciesGraphicInfo gSpeciesGraphics[];
extern const struct AbilityInfo gAbilitiesInfo[];
extern const u8 *const gItemEffectTable[];
//extern const struct Evolution gEvolutionTable[][EVOS_PER_MON]; //plan remove replace w EE version built into basestats
extern const u8 gStatStageRatios[][2];
extern struct SpriteTemplate gMultiuseSpriteTemplate;
extern struct PokemonStorage* gPokemonStoragePtr;
extern const u32 gExperienceTables[][MAX_LEVEL + 1];
extern const u8 gFacilityClassToPicIndex[];
extern const u8 gFacilityClassToTrainerClass[];
extern const struct SpriteTemplate gBattlerSpriteTemplates[];
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
void RevertTransformedHP(enum BattlerId battlerId);
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
s32 CalculateBaseDamage(struct BattlePokemon *attacker, struct BattlePokemon *defender, u32 move, u32 sideStatus, u16 powerOverride, u8 typeOverride, enum BattlerId battlerIdAtk, enum BattlerId battlerIdDef);
u8 GetWeatherBallType(u16 move);
//sidestatus meant to hold gsidestatus but forgot I had to upgrade that to u32 *facepalm

//recent emerald addditions, change for form change (not planning use for ditto/transform)
u16 GetFormChangeTargetSpecies(struct Pokemon *mon, u16 method, u32 arg);
u16 GetFormChangeTargetSpeciesBoxMon(struct Pokemon *mon, u16 method, u32 arg);//still works same just adjusted for getablilitybyspecies change
bool8 DoesSpeciesHaveCosmeticForms(u16 species);

#define BATTLE_ALIVE_EXCEPT_ACTIVE  0
#define BATTLE_ALIVE_ATK_SIDE       1
#define BATTLE_ALIVE_DEF_SIDE       2

u8 CountAliveMonsInBattle(u8 caseId, enum BattlerId battler);

u8 GetDefaultMoveTarget(enum BattlerId battler);
u8 GetMonGender(struct Pokemon *mon);
u8 GetBoxMonGender(struct BoxPokemon *boxMon);
u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);
void SetMultiuseSpriteTemplateToPokemon(u16 speciesTag, enum BattlerId battlerPosition);
void SetMultiuseSpriteTemplateToTrainerBack(u16 trainerSpriteId, enum BattlerId battlerPosition);

/* GameFreak called Get(Box)MonData with either 2 or 3 arguments, for
 * type safety we have a Get(Box)MonData macro which dispatches to
 * either Get(Box)MonData2 or Get(Box)MonData3 based on the number of
 * arguments. The two functions are aliases of each other, but they
 * differ for matching purposes in the caller's codegen. */
#define GetMonData(...) CAT(GetMonData, NARG_8(__VA_ARGS__))(__VA_ARGS__)
#define GetBoxMonData(...) CAT(GetBoxMonData, NARG_8(__VA_ARGS__))(__VA_ARGS__)
u32 GetMonData3(struct Pokemon *mon, s32 field, u8 *data);
u32 GetMonData2(struct Pokemon *mon, s32 field);
u32 GetBoxMonData3(struct BoxPokemon *boxMon, s32 field, u8 *data);
u32 GetBoxMonData2(struct BoxPokemon *boxMon, s32 field);

void SetMonData(struct Pokemon *mon, s32 field, const void *dataArg);
void SetBoxMonData(struct BoxPokemon *boxMon, s32 field, const void *dataArg);
void CopyMon(void *dest, void *src, size_t size);
u8 GiveMonToPlayer(struct Pokemon *mon);
u8 CalculatePlayerPartyCount(void);
u8 CalculateEnemyPartyCount(void);
u8 GetMonsStateToDoubles(void);
u16 GetAbilityBySpecies(u16 species, bool8 abilityNum, struct Pokemon *mon); //change for taught abilities
u16 GetMonAbility(struct Pokemon *mon);
u32 ShouldUseTaughtAbility(struct Pokemon *mon);
void ResetLearnedAbilityValues(struct Pokemon *mon);
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
bool8 PokemonItemUseNoEffect(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex);
bool8 PokemonUseItemEffects(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex, bool8 usedByAI);
u8 GetItemEffectParamOffset(enum BattlerId battler, u16 itemId, u8 effectByte, u8 effectBit);
const u8 *Battle_PrintStatBoosterEffectMessage(u16 itemId);
u8 GetNature(struct Pokemon *mon);
u8 SetNature(struct BoxPokemon *mon);
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
u8 GetListOfTeachableAbilities(u16 species, u16 *abilityList);
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
const u16 *GetMonSpritePal(struct Pokemon *mon);
const u16 *GetMonSpritePalFromSpeciesAndPersonality(u16 species, bool32 isShiny, u32 personality);
const u16 *GetMonSpritePalOfSpecies(struct Pokemon *mon, u16 species); //use mon for shiny retrieves set species, use for evolution scene mostly
//const struct SpritePalette *GetMonSpritePalStruct(struct Pokemon *mon);

//const struct SpritePalette *GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality);
//replaced previous
const u16 *GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality);
bool8 IsPokeSpriteNotFlipped(u16 species);
s8 GetMonFlavorRelation(struct Pokemon *mon, u8 flavor);//replaces below
bool8 IsTradedMon(struct Pokemon *mon);
bool8 IsOtherTrainer(u32 otId, u8 *otName);
void MonRestorePP(struct Pokemon *mon);
void BoxMonRestorePP(struct BoxPokemon *boxMon);
void SetMonPreventsSwitchingString(void);
void SetWildMonHeldItem(void);

//u8 *GetTrainerPartnerName(void);
u8 GetPlayerPartyHighestLevel(void);
u16 FacilityClassToPicIndex(u16 facilityClass);
bool8 ShouldIgnoreDeoxysForm(u8 caseId, enum BattlerId battlerId);
void SetDeoxysStats(void);
u16 GetUnionRoomTrainerPic(void);
u16 GetUnionRoomTrainerClass(void);
void CreateEventLegalEnemyMon(void);
void HandleSetPokedexFlag(u16 nationalNum, u8 caseId, u32 personality);
bool8 CheckBattleTypeGhost(struct Pokemon *mon, enum BattlerId battlerId);
struct OakSpeechNidoranFStruct *OakSpeechNidoranFSetup(u8 battlePosition, bool8 enable);
void OakSpeechNidoranFFreeResources(void);
void *OakSpeechNidoranFGetBuffer(u8 bufferId);
u16 GetBaseFormSpecies(u16 speciesId);
u16 GetFormSpeciesId(u16 speciesId, u8 formId);
u8 GetFormIdFromFormSpeciesId(u16 formSpeciesId);
u8 GetFinalFormSpeciesId(u16 formSpeciesId); //added for dex changes to read forms
u16 GetBaseStatTotal(u16 species);
u16 GetIndividualBaseStatValue(u16 species, u8 statIndex); //pull base stat for selected stat //mostly used for settin up new ev caps logic
u16 GetGlobalStatTotal(struct Pokemon *mon); //takes stats from evs + bst //for use as limiter
bool8 CanEvioliteActivate(u8 target);
bool8 IsMegaSpecies(u16 species); //mostly use for cry alter
s16 atk_diff(void);
s16 spatk_diff(void); //put here, used for hidden power change split
bool8 IsPhysicalMove(u32 attackerId, enum Move move); //new function consolidating effects for if move is physical or not
void ApplyScreenModifier(enum BattlerId battlerAtk, enum BattlerId battlerDef, u16 move, u8 DamageCategory, s32 damage);
void ApplyMovePowerModifiers(enum BattlerId battlerAtk, u16 move, u16 power);

enum Ability GetSpeciesAbility(u16 species, u8 slot);
u32 GetSpeciesBaseHP(u16 species);
u32 GetSpeciesBaseAttack(u16 species);
u32 GetSpeciesBaseDefense(u16 species);
u32 GetSpeciesBaseSpAttack(u16 species);
u32 GetSpeciesBaseSpDefense(u16 species);
u32 GetSpeciesBaseSpeed(u16 species);
u32 GetSpeciesBaseStat(u16 species, u32 statIndex);
const struct AbilityLearnset *GetSpeciesTeachableAbilities(u16 species);
const struct LevelUpMove *GetSpeciesLevelUpLearnset(u16 species);
const u16 *GetSpeciesTeachableLearnset(u16 species);
const struct Evolution *GetSpeciesEvolutions(u16 species);
//new functions for file reorg based on EE
u8 GetFormType(u16 species); //set mostly for dex changes
struct ToneData *GetCryIdBySpecies(u16 species, bool8 reverse); //added for cry table rehash

//u8 IsMonShiny(struct Pokemon *mon); //for species graphic file setup
bool8 IsMonShiny(struct Pokemon *mon);
bool8 IsBoxMonShiny(struct BoxPokemon *mon);
bool8 IsShinyOtIdPersonality(u32 otId, u32 personality);
bool8 IsMonNuzlockeDead(struct Pokemon *mon);
bool8 IsBoxMonNuzlockeDead(struct BoxPokemon *mon);
const u16 *GetMonSpritePalFromSpecies(u16 species, bool32 isShiny);

void PokemonToBattleMon(struct Pokemon *src, struct BattlePokemon *dst);
bool8 IsPokemonStorageFull(void); //for set egg to pc by default

u8 GetEnemyPartyAverageLevel(u16 trainerId);

//ported things for debug
u8 GetNatureFromPersonality(u32 personality);
u8 SendMonToPC(struct Pokemon* mon);
void GiveBoxMonInitialMoveset_Fast(struct BoxPokemon *boxMon);
void GiveBattleMonInitialMoveset_Fast(struct Pokemon *mon, u16 Species); //made attempt get inversion move set change worknig 

static inline enum Ability SanitizeAbilityId(enum Ability ability)
{
    if (ability >= ABILITIES_COUNT)
        return ABILITY_NONE;
    else
        return ability;
}

static inline u16 SanitizeSpeciesId(u16 species)
{
    if (species >= NUM_SPECIES)
        return SPECIES_NONE;
    else
        return species;
}

enum SpeciesType
{
    PRIMARY_TYPE,
    SECONDARY_TYPE,
    NUM_SPECIES_TYPES,
};

static inline enum Type GetSpeciesType(u16 species, u8 slot)
{
    switch (slot)
    {
        case PRIMARY_TYPE:
            return gSpeciesInfo[SanitizeSpeciesId(species)].type1;
        break;
        case SECONDARY_TYPE:
            return gSpeciesInfo[SanitizeSpeciesId(species)].type2;
        break;
    }
}

static inline enum Type GetSpeciesPrimaryType(u16 species)
{
    return GetSpeciesType(species, PRIMARY_TYPE);
}

static inline enum Type GetSpeciesSecondaryType(u16 species)
{
    return GetSpeciesType(species, SECONDARY_TYPE);
}

//Type boosted by hunger switch form and type of aura wheel
//I want to use context for this but arguemnt itself 
//should just be battler and ability
//and should be fine since just reading data not changing it
//use species of atk battler
static inline enum Type GetHungerSwitchType(u16 species, enum Ability abilityAtk)
{
    if (GET_BASE_SPECIES_ID(species) == SPECIES_MORPEKO_FULL_BELLY
    && abilityAtk == ABILITY_HUNGER_SWITCH)
        return (species == SPECIES_MORPEKO_FULL_BELLY ? TYPE_ELECTRIC : TYPE_DARK);
}



static inline void CopySpeciesNameToBuff(u8 *nameBuff, u32 species)
{
    s32 i;

    // Hmm? FRLG has < while Ruby/Emerald has <=
    for (i = 0; i < POKEMON_NAME_LENGTH; i++)
    {
        nameBuff[i] = gSpeciesInfo[SanitizeSpeciesId(species)].speciesName[i];

        if (nameBuff[i] == EOS)
            break;
    }

    nameBuff[i] = EOS;

}


static inline void CopyAbilityNameToBuff(u8 *nameBuff, enum Ability ability)
{
    u32 i;

    // Hmm? FRLG has < while Ruby/Emerald has <=
    for (i = 0; i < ABILITY_NAME_LENGTH; i++)
    {

        nameBuff[i] = gAbilitiesInfo[SanitizeAbilityId(ability)].name[i];

        if (nameBuff[i] == EOS)
            break;
    }

    nameBuff[i] = EOS;

}



//stuff from EE form change port
const u8 *GetTrainerPartnerName(void);
void BattleAnimateFrontSprite(struct Sprite *sprite, u16 species, bool8 noCry, u8 panMode);
void DoMonFrontSpriteAnimation(struct Sprite *sprite, u16 species, bool8 noCry, u8 panModeAnimFlag);
void PokemonSummaryDoMonAnimation(struct Sprite *sprite, u16 species, bool8 oneFrame);
void StopPokemonAnimationDelayTask(void);
void BattleAnimateBackSprite(struct Sprite *sprite, u16 species);
u8 GetOpposingLinkMultiBattlerId(bool8 rightSide, u8 multiplayerId);
//enum TrainerPicID FacilityClassToPicIndex(u16 facilityClass);
//enum TrainerPicID PlayerGenderToFrontTrainerPicId(enum Gender playerGender);
//void HandleSetPokedexFlag(enum NationalDexOrder nationalNum, u8 caseId, u32 personality);
void HandleSetPokedexFlagFromMon(struct Pokemon *mon, u32 caseId);
//bool8 HasTwoFramesAnimation(u16 species);
struct MonSpritesGfxManager *CreateMonSpritesGfxManager(u8 managerId, u8 mode);
void DestroyMonSpritesGfxManager(u8 managerId);
u8 *MonSpritesGfxManager_GetSpritePtr(u8 managerId, u8 spriteNum);
u16 GetFormSpeciesId(u16 speciesId, u8 formId);
u8 GetFormIdFromFormSpeciesId(u16 formSpeciesId);
u32 GetFormChangeTargetSpecies_Internal(struct FormChangeContext ctx);
bool32 DoesSpeciesHaveFormChangeMethod(u16 species, enum FormChanges method);
u16 MonTryLearningNewMoveEvolution(struct Pokemon *mon, bool8 firstMove);
void RemoveIVIndexFromList(u8 *ivs, u8 selectedIv);
void TrySpecialOverworldEvo(void);
bool32 SpeciesHasGenderDifferences(u16 species);
bool32 TryFormChange(struct Pokemon *mon, enum FormChanges method);
bool32 TryBoxMonFormChange(struct BoxPokemon *boxMon, enum FormChanges method);
void TryToSetBattleFormChangeMoves(struct Pokemon *mon, enum FormChanges method);
u32 GetMonFriendshipScore(struct Pokemon *pokemon);
u32 GetMonAffectionHearts(struct Pokemon *pokemon);
void UpdateMonPersonality(struct BoxPokemon *boxMon, u32 personality);
u8 CalculatePartyCount(struct Pokemon *party);
u16 SanitizeSpeciesId(u16 species);
bool32 IsSpeciesEnabled(u16 species);
//u16 GetSpeciesPreEvolution(u16 species); check later unsure if will switch from my version
void HealPokemon(struct Pokemon *mon);
void HealBoxPokemon(struct BoxPokemon *boxMon);
void UpdateDaysPassedSinceFormChange(u16 days);
void TrySetDayLimitToFormChange(struct Pokemon *mon);
enum Type CheckDynamicMoveType(struct Pokemon *mon, enum Move move, enum BattlerId battler, enum MonState state);
uq4_12_t GetDynamaxLevelHPMultiplier(u32 dynamaxLevel, bool32 inverseMultiplier);
u32 GetRegionalFormByRegion(u32 species, u32 region);
bool32 IsSpeciesForeignRegionalForm(u32 species, u32 currentRegion);
enum Type GetTeraTypeFromPersonality(struct Pokemon *mon);
bool8 ShouldSkipFriendshipChange(void);
struct Pokemon *GetSavedPlayerPartyMon(u32 index);
u8 *GetSavedPlayerPartyCount(void);
void SavePlayerPartyMon(u32 index, struct Pokemon *mon);
bool32 IsSpeciesOfType(u32 species, enum Type type);
struct BoxPokemon *GetSelectedBoxMonFromPcOrParty(void);
u32 GiveScriptedMonToPlayer(struct Pokemon *mon, u8 slot);
void ChangePokemonNicknameWithCallback(void (*callback)(void));

#endif // GUARD_POKEMON_H
