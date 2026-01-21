#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

#include <limits.h>
// should they be included here or included individually by every file?
#include "constants/battle_end_turn.h"
#include "constants/battle_switch_in.h"
//#include "global.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/battle_move_resolution.h"
#include "constants/form_change_types.h"
#include "constants/hold_effects.h"
#include "constants/battle_move_effects.h"
#include "battle_util.h"
#include "battle_script_commands.h"
#include "battle_main.h"
#include "battle_ai_switch.h"
#include "battle_gfx_sfx_util.h"
#include "battle_util2.h"
#include "battle_message.h"
#include "battle_bg.h"
//#include "battle_dynamax.h"
#include "battle_terastal.h"
#include "battle_gimmick.h"
#include "move.h"
#include "random.h" // for rng_value_t
#include "window.h" //need this for build modern to work for battle window ui
#include "generational_changes.h"

/*
    Banks are a name given to what could be called a 'battlerId' or 'monControllerId'.
    Each bank has a value consisting of two bits.
    0x1 bit is responsible for the side, 0 = player's side, 1 = opponent's side.
    0x2 bit is responsible for the id of sent out pokemon. 0 means it's the first sent out pokemon, 1 it's the second one. (Triple battle didn't exist at the time yet.)
*/

#define GET_BATTLER_POSITION(battler)((gBattlerPositions[battler]))
#define GET_BATTLER_SIDE(battler)((GetBattlerPosition(battler) & BIT_SIDE))
#define GET_BATTLER_SIDE2(battler)((GET_BATTLER_POSITION(battler) & BIT_SIDE))

// Helper for accessing command arguments and advancing gBattlescriptCurrInstr.
//
// For example accuracycheck is defined as:
//
//     .macro accuracycheck failInstr:req, move:req
//     .byte 0x1
//     .4byte \failInstr
//     .2byte \move
//     .endm
//
// Which corresponds to:
//
//     CMD_ARGS(const u8 *failInstr, u16 move);
//
// The arguments can be accessed as cmd->failInstr and cmd->move.
// gBattlescriptCurrInstr = cmd->nextInstr; advances to the next instruction.
#define CMD_ARGS(...) const struct __attribute__((packed)) { u8 opcode; RECURSIVELY(R_FOR_EACH(APPEND_SEMICOLON, __VA_ARGS__)) const u8 nextInstr[0]; } *const cmd UNUSED = (const void *)gBattlescriptCurrInstr
#define VARIOUS_ARGS(...) CMD_ARGS(enum BattlerId battler, u8 id, ##__VA_ARGS__)
#define NATIVE_ARGS(...) CMD_ARGS(void (*func)(void), ##__VA_ARGS__)

// Used to exclude moves learned temporarily by Transform or Mimic
#define MOVE_IS_PERMANENT(battler, moveSlot)                        \
   (!(gBattleMons[battler].volatiles.transformed)           \
 && !(gBattleMons[battler].volatiles.mimickedMoves & (1u << moveSlot)))

#define B_ACTION_USE_MOVE                  0
#define B_ACTION_USE_ITEM                  1
#define B_ACTION_SWITCH                    2
#define B_ACTION_RUN                       3
#define B_ACTION_SAFARI_WATCH_CAREFULLY    4
#define B_ACTION_SAFARI_BALL               5
#define B_ACTION_SAFARI_BAIT               6
#define B_ACTION_SAFARI_GO_NEAR            7
#define B_ACTION_SAFARI_RUN                8
#define B_ACTION_OLDMAN_THROW              9
#define B_ACTION_EXEC_SCRIPT               10
#define B_ACTION_TRY_FINISH                11
#define B_ACTION_FINISHED                  12
#define B_ACTION_CANCEL_PARTNER            12 // when choosing an action
#define B_ACTION_NOTHING_FAINTED           13 // when choosing an action
#define B_ACTION_DEBUG                     20 //open debug menu
#define B_ACTION_MOVE_INFO                 21 //open summ screen move info page
#define B_ACTION_NONE                      0xFF

#define MAX_TRAINER_ITEMS 4



// For the second argument of GetBattleMoveTarget, when no target override is needed
#define NO_TARGET_OVERRIDE 0




/*there isn't really much reason to have more structs than just TrainerMonItemCustomMoves, since I've fixed the move error
only values needed in selction are lvl and species, everything else can be left empty and can safely default to zero.
Check definition of struct to find base/default values.

Still need to add u8 abilityNum field so ability can track w repeated trainers,
but setup like iv field, so if left blank can just set a random value
Using multiple structs was to save memory, it wouldn't cost me too too much to consolidate
but to attempt to compensate change iv, to u8 field. its only u16 for the weird masking they do.
would require combing all trainer fields and translating from mask back to max 31
change in code would just be fixedIV = partyData[i].iv  removing the mask and 255 divisor
would only save me 1 byte for every trainer party, which would balance by adding the abilityNum field
but still a net positive

put abilityNum field below lvl, make constant defines so don't have to just use 0-3

since I want leaving blank to be set random ability, I can't use value 0 as set mon ability num
so i will need to make a function to do it, "i" value of 0 will default to setting randomly
then if not 0,  use setmondata ability num i-1    so  i value of 1, will be abilitynum 0 etc.

Replacing iv values will be easier than thought, as most entries are blank,
the only used values: 20 30 40 50 60 80 90
    100 110 120 130 150 160 170 180 or 200 220 250 & 255
so simple as running a ctrl h for  .iv = existing value,
then just multiply by 31 and divide by 255, to find the replace value
*/
/*struct TrainerMon
{
    u16 species;
    u16 heldItem;
    u8 abilityNum;
    u8 padding;
    u16 evs[6];
    u8 iv;    
    u8 lvl;    
    u16 moves[4];
    struct Formdata FormInfo;
};*/

/*struct TrainerMonFormChangeFullCustom
{
    u8 iv;
    u16 evs[6];
    u8 lvl;
    u8 abilityNum;
    u16 species;
    u16 heldItem;
    u16 moves[4];
    struct Formdata FormInfo;
};*/
//need store both form species and form moveset
//think do with an array instead?
//FormChangeMoveSet won't be triggered at battle start
//it'll just be a place I refer to for the moves when it form changes
//mid battle.
//thing I'm unsure of is if I can properly trace the mon placement
//from this?
//idea is if I have identical species etc.
//but mon switch, if I can correctly track
//what moves it would have for form given switching
//check form change logic in EE to see how it knows 
//which to transform but prob only one has mega stone etc.
//and I've removed the need for mega stones...





//removed resource flag use, saves ewram
//was able to fit into disable struct
//will need to add on to struct later tho
//for more EE port
/*#define RESOURCE_FLAG_FLASH_FIRE     1
#define RESOURCE_FLAG_ROOST          2
#define RESOURCE_FLAG_UNBURDEN       4
#define RESOURCE_FLAG_EMERGENCY_EXIT 8  //check how this used will prob do it differently for my implementation
#define RESOURCE_FLAG_NEUTRALIZING_GAS 16 //works by doubling previous
*/



// gets cleared at end turn, via TurnValuesCleanUp function
struct ProtectStruct    
{
    /* field_0 */
             u32 protected:1;
             u32 endured : 1;
             u32 noValidMoves : 1;
             u32 helpingHand : 1;
             u32 bounceMove : 1;
             u32 stealMove : 1;
             u32 flag0Unknown : 1;
             u32 prlzImmobility : 1;
             /* field_1 */
             u32 confusionSelfDmg : 1;  //will instead change ot make random target, and within that if move is non-damaging do normal confusion hit, or use move against self
             u32 targetNotAffected : 1; //opposite equivalent of targetAffected
             u32 chargingTurn : 1;
             u32 fleeFlag : 2; // for RunAway Defeatist and Smoke Ball
             u32 usedImprisonedMove : 1;
             u32 loveImmobility : 1;
             u32 usedDisabledMove : 1;
             /* field_2 */
             u32 usedTauntedMove : 1;      // 0x1
             u32 flag2Unknown : 1;         // 0x2
             u32 flinchImmobility : 1;     // 0x4
             u32 notFirstStrike : 1;       // 0x8
             u32 flag_x10 : 1;           // 0x10
             u32 flag_x20 : 1;           // 0x20
             u32 flag_x40 : 1;           // 0x40
             u32 flag_x80 : 1;           // 0x80
             /* field_3 */
             u32 field3 : 8;//field 3 because bit field 3,  this fills u32

             u16 physicalDmg;
             u16 specialDmg;
             u16 turnDmg; //handled differently from above but is general field for now only used in focus punch
             u16 physicalBattlerId:3;//u8 bitfield in EE
             u16 specialBattlerId:3;
             u16 spaceBar:10;


             u32 blockcrit : 1; //rn just giving to defense curl
             u32 blankspace : 4; //removed protect stuff in EE so these will be freed
             u32 usesBouncedMove : 1;
             u32 usedHealBlockedMove : 1;
             u32 usedGravityPreventedMove : 1;

             u32 powderSelfDmg : 1;  //not sure why  I added this I'm not gonna use it? well for someone else I guess. 
             u32 usedThroatChopPreventedMove : 1;
             u32 pranksterElevated : 1;
             u32 galewingsElevated : 1;
             u32 triageElevated : 1;
             u32 OmniAideElevated : 1; //omnipotent aide, new fields added to account for queenly majesty w status priority change
             u32 NuisanceElevated : 1;
             u32 LightMetalElevated : 1;

             u32 quickDraw : 1;
             u32 quash : 1;
             u32 beakBlastCharge : 1; //makes more sense to put thse in special status..
             u32 usedMicleBerry : 1;
             u32 usedCustapBerry : 1;    // also quick claw
             u32 touchedProtectLike : 1;
             u32 obstructed : 1;
             u32 disableEjectPack : 1; 

             u32 shellTrap:1; //hopefully doens't add space
             u32 LongReachElevated:1;//double check but don't think having protect struct is necessary for priority boost but just makes it easier to track?
             u32 activatedAbilityStatusHealing:1;  //since separated from status need this to filter so doesn't retrigger. //using for both poison heal and heat trance, 
             u32 statRaised:1;
             u32 statFell:1;
             u32 oneTurnStatBoost:3; //stat to boost set from stored value made for mega gren z, meant to be 2 stage boost
             u16 fieldE; //realized meant to store stat not a bool max stat id is 7 so thankfully fits
};

extern struct ProtectStruct gProtectStructs[MAX_BATTLERS_COUNT];

//gets cleared at end turn - actual think gets cleard at action end? yeah its action end
// Cleared at the start of HandleAction_ActionFinishedstruct 
struct SpecialStatus    
{

    u8 statLowered : 1;
    u8 restoredBattlerSprite : 1;
    u8 instructedChosenTarget:3;
    u8 mindBlownRecoil: 1;                  // 0x10
    u8 ppNotAffectedByPressure : 1;
    u8 faintedHasReplacement : 1;

    u8 field1[3]; //think this is counted different rather than a portion of 1 byte its 3 full bytes

    
    

    u8 rototillerAffected : 1;  // to be affected by rototiller    
    u8 switchInItemDone : 1;
    u8 switchInAbilityDone : 1;
    u8 semiInvulInterupt:1; //takes place of STATUS2_TWOTURN_INTERRUPT status makes more sense here want clear at end of action
    u8 afterYou:1;
    u8 berryReduced : 1;
    u8 unused : 2; // Mons that have been damaged directly by using a move, includes substitute. //NOW THAT have added can prob use to update catchexp function/macro?
    
    u8 dancerUsedMove : 1;
    u8 dancerOriginalTarget : 3; //original target of user to execute chosen move after ability ends
    u8 returnedBallMove : 1;    //equiv dancerUsedMove
    u8 BallFetchOriginalTarget : 3;//original target of user to execute chosen move after ability ends //equiv dancerOriginalTarget

    u8 immutableWindRemoved : 1;   // See Cmd_switchineffects - not used in EE
    u8 neutralizingGasRemoved : 1;    // See VARIOUS_TRY_END_NEUTRALIZING_GAS
    u8 stenchRemoved : 1;    // Set as VARIOUS_TRY_END_STENCH  both exclusive to gastro acid?
    u8 Lostresolve:1; //for ability -tweaked as for pressure and iron will, moved here as realize makes more sense as special status
    u8 firstFuturesightHits:1;
    u8 secondFuturesightHits:1;
    u8 damagedByAttack:1;
    u8 criticalHit:1;

    //emergency exit works as special status, just need to set it in attack cancelr 
    u8 EmergencyExit : 1; //logic mix truant pursuit/escape hit, setup like truant trigger on end turn that hp met theshold,raise attack then make attack first & set moveeffect escape hit so it leaves after attacking. WILL USE for both wimpout and Emergency exit just use ability check for logic change
    u8 parentalBondState : 2; // 0/1/2 is used, max is 0-3
    u8 multiHitOn : 1; //think is a state chech, replace effect multihit it checks if move is passed 1 hit and doing a multihit process
    u8 Cacophonyboosted:1; //need make function for and add to battle_main
    u8 preHitAbilityDone:1;
    u8 distortedTypeMatchups:1;
    u8 teraShellAbilityDone:1;
    
    
    u8 changedStatsBattlerId; // Battler that was responsible for the latest stat change. Can be self. 
    u8 gemParam:7;
    u8 gemBoost:1;   
    u8 field12;
    u8 field13;//check moody case for switchin line something something = 2
};



extern struct SpecialStatus gSpecialStatuses[MAX_BATTLERS_COUNT];

//think can replace most timers w bitfield 3, as usually nothing goes aboe 8
//slightly misunderstood that, is :3 can represent 8 values that's 0-7 not 0-8
//so bit 3 only works for timers that don't get extended to 8
//so not weather or terrain.
//checked EE all this is wrong
//only sticyweb uses battlerId nothing else smh
struct SideTimer    //effects below persist regardless of mon
{
    /*0x00*/
    //screens
    u16 reflectTimer:3;
    u16 lightscreenTimer:3;
    u16 magicTimer:3; ////magic coat
    u16 safeguardTimer:3;             
    u16 padding:4;


    u8 followmeTarget;
    /*0x0A*/ 
    u8 spikesAmount:2; //3 effective layers
    u8 toxicSpikesAmount:2; //2 effective layers
    u8 padding1:2; //1 effective layers    //...why is this here?? vsonic -replace w padding value
    u8 stickyWebAmount:2; //2 effective layers - ability or move to set stickyweb //bleive was my own change,
    u8 stickyWebBattlerSide; // Used for Court Change
    u8 stickyWebBattlerId; //try see why this one specifcally needs battlerid prob to do with printed string
    
    u16 auroraVeilTimer:4; //still need add to debugger
    u16 tailwindTimer:3;
    u16 luckyChantTimer:3;
    u16 healBlockTimer:3; //added for side status effect
    u16 embargoTimer:3;

    u16 mudSportTimer:3;     //put these back, gen 3 effect didn' work how I thought. effect only lasts long as user stays in, and only for user who set it.
    u16 waterSportTimer:3;  //forgot to remove these earlier, since I'm using gen 3 effects for them
    u16 mistTimer:3;
    u16 padding2:7;

    // Timers below this point are not swapped by Court Change
    u16 followmeTimer:1; //follow me only goes to 1
    u16 followmePowder:1; // Rage powder, does not affect grass type pokemon.
    u16 retaliateTimer:3;
    u16 flagspace:11;

    u16 damageNonTypesTimer;    
    u16 rainbowTimer;
    u16 seaOfFireTimer;
    u16 swampTimer;
    enum Type damageNonTypesType;
    /*0x0B*/ //u8 fieldB; never used so hopefully safe to remove
};

extern struct SideTimer gSideTimers[NUM_BATTLE_SIDES];

struct FieldTimer
{

    u8 wonderRoomTimer;
    u8 magicRoomTimer;
    u8 trickRoomTimer;
    u8 terrainTimer; //can go to 8 so needs bit 4
    u8 echoVoiceCounter; //5 effective stacks bp 40, increases by 40, each turnup to 200
    u8 gravityTimer;
    u8 fairyLockTimer;
    u8 IonDelugeTimer; // this & roost will be only ones that don't fail if used when timer isn't 0
    u8 HazeTimer;
    u8 SnowescapeTimer; //linked to weather duration


};//check how I setup roost may not need iondelugetimer here
//can't make fieldtimers bitfields

struct AI_SavedBattleMon
{
    enum Ability ability;
    enum Move moves[MAX_MON_MOVES];
    u16 heldItem;
    u16 species:15;
    u16 saved:1;
    enum Type types[3];
};

struct AiPartyMon
{
    u16 species;
    enum Item item;
    enum HoldEffect heldEffect;
    enum Ability ability;
    u16 level;
    enum Move moves[MAX_MON_MOVES];
    u32 status;
    u8 switchInCount; // Counts how many times this Pokemon has been sent out or switched into in a battle.
    u8 gender:2;
    u8 isFainted:1;
    u8 wasSentInBattle:1;
    u8 padding:4;
};

struct AiPartyData // Opposing battlers - party mons.
{
    struct AiPartyMon mons[NUM_BATTLE_SIDES][PARTY_SIZE]; // 2 parties(player, opponent). Used to save information on opposing party.
    u8 count[NUM_BATTLE_SIDES];
};

struct SimulatedDamage
{
    u16 minimum;
    u16 median;
    u16 maximum;
};

// Ai Data used when deciding which move to use, computed only once before each turn's start.
struct AiLogicData
{
    enum Ability abilities[MAX_BATTLERS_COUNT];
    enum Item items[MAX_BATTLERS_COUNT];
    enum HoldEffect holdEffects[MAX_BATTLERS_COUNT];
    u8 holdEffectParams[MAX_BATTLERS_COUNT];
    enum Move lastUsedMove[MAX_BATTLERS_COUNT];
    u8 hpPercents[MAX_BATTLERS_COUNT];
    enum Move partnerMove;
    u16 speedStats[MAX_BATTLERS_COUNT]; // Speed stats for all battles, calculated only once, same way as damages
    struct SimulatedDamage simulatedDmg[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // attacker, target, moveIndex
    uq4_12_t effectiveness[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // attacker, target, moveIndex
    u8 moveAccuracy[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // attacker, target, moveIndex
    u8 moveLimitations[MAX_BATTLERS_COUNT];
    u8 monToSwitchInId[MAX_BATTLERS_COUNT]; // ID of the mon to switch in.
    u8 mostSuitableMonId[MAX_BATTLERS_COUNT]; // Stores result of GetMostSuitableMonToSwitchInto, which decides which generic mon the AI would switch into if they decide to switch. This can be overruled by specific mons found in ShouldSwitch; the final resulting mon is stored in AI_monToSwitchIntoId.
    enum Move predictedMove[MAX_BATTLERS_COUNT];
    u8 resistBerryAffected[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // Tracks whether currently calc'd move is affected by a resist berry into given target

    // Flags
    u32 weatherHasEffect:1; // The same as HasWeatherEffect(). Stored here, so it's called only once.
    u32 ejectButtonSwitch:1; // Tracks whether current switch out was from Eject Button
    u32 ejectPackSwitch:1; // Tracks whether current switch out was from Eject Pack
    u32 predictingSwitch:1; // Determines whether AI will use switch predictions this turn or not
    u32 aiPredictionInProgress:1; // Tracks whether the AI is in the middle of running prediction calculations
    u32 aiCalcInProgress:1;
    u32 predictingMove:1; // Determines whether AI will use move predictions this turn or not
    u32 shouldConsiderExplosion:1; // Determines whether AI should consider explosion moves this turn
    u32 shouldSwitch:4; // Stores result of ShouldSwitch, which decides whether a mon should be switched out
    u32 shouldConsiderFinalGambit:1; // Determines whether AI should consider Final Gambit this turn
    u32 padding2:19;
};

struct AiThinkingStruct
{
    u8 aiState;
    u8 movesetIndex;
    u16 moveConsidered;
    s32 score[MAX_MON_MOVES];
    u64 aiFlags[MAX_BATTLERS_COUNT];
    u8 aiAction;
    u8 aiLogicId;
    struct AI_SavedBattleMon saved[MAX_BATTLERS_COUNT];
};

#define AI_MOVE_HISTORY_COUNT 3 //not sure what for at this point

extern u8 gBattlerAbility;
extern u8 gBattlerTarget;
extern u8 gAbsentBattlerFlags;

extern struct BattlePokemon gBattleMons[MAX_BATTLERS_COUNT];
extern u8 gBattlerSpriteIds[MAX_BATTLERS_COUNT];
/*struct UsedMoves
{
    u16 moves[MAX_BATTLERS_COUNT];
    u16 unknown[MAX_BATTLERS_COUNT];
};*/


struct BattleHistory
{
    enum Ability abilities[MAX_BATTLERS_COUNT];
    u8 itemEffects[MAX_BATTLERS_COUNT];
    u16 usedMoves[MAX_BATTLERS_COUNT][MAX_MON_MOVES];
    u16 moveHistory[MAX_BATTLERS_COUNT][AI_MOVE_HISTORY_COUNT]; // 3 last used moves for each battler
    u8 moveHistoryIndex[MAX_BATTLERS_COUNT];
    u16 trainerItems[MAX_BATTLERS_COUNT];
    u8 itemsNo;
    u16 heldItems[MAX_BATTLERS_COUNT];
};//dont remember why in last implementation used old struct rather than new version
//prob to build faster without further changes needed

struct BattleScriptsStack
{
    const u8 *ptr[8];
    u8 size;
};

struct BattleCallbacksStack
{
    void (*function[8])(void);
    u8 size;
};

struct StatsArray
{
    u16 stats[NUM_STATS];
    u16 level:15;
    u16 learnMultipleMoves:1;
};

struct BattleResources
{
    //struct SecretBase *secretBase;
    struct BattleScriptsStack *battleScriptsStack;
    struct BattleCallbacksStack *battleCallbackStack;
    struct StatsArray *beforeLvlUp;
    u8 bufferA[MAX_BATTLERS_COUNT][0x200];
    u8 bufferB[MAX_BATTLERS_COUNT][0x200];//wrong this is equivalent of gbattlebuffers
    u8 transferBuffer[0x100];
};



struct BattleResults
{
    u8 playerFaintCounter;    // 0x0
    u8 opponentFaintCounter;  // 0x1
    u8 playerSwitchesCounter; // 0x2    //vsonic IMPORTANT make opponent vers of this & use for ai cap at num switch
    u8 numHealingItemsUsed;   // 0x3
    u8 numRevivesUsed:6;        // 0x4  //max 63 now, 64 value
    u8 opponentSwitchesCounter:2;   //shoudl work   max 3 should be enough,
    u8 playerMonWasDamaged : 1; // 0x5
    u8 usedMasterBall : 1;      // 0x5
    u8 caughtMonBall : 4;       // 0x5
    u8 shinyWildMon : 1;        // 0x5
    u8 unk5_7 : 1;              // 0x5
    u16 playerMon1Species;    // 0x6
    u8 playerMon1Name[POKEMON_NAME_LENGTH + 1];    // 0x8
    u8 battleTurnCounter;     // 0x13
    u8 playerMon2Name[POKEMON_NAME_LENGTH + 1];    // 0x14
    u8 pokeblockThrows;       // 0x1F   //leave in in case I can implement contest/ emerlad style safari zone planters
    u16 lastOpponentSpecies;  // 0x20
    u16 lastUsedMovePlayer;   // 0x22
    u16 lastUsedMoveOpponent; // 0x24
    u16 playerMon2Species;    // 0x26
    u16 caughtMonSpecies;     // 0x28
    u8 caughtMonNick[POKEMON_NAME_LENGTH];     // 0x2A
    u8 filler34[2];
    //u8 catchAttempts[11];     // 0x36
    u8 catchAttempts[POKEBALL_COUNT];     // 0x36
};//some of these seem just for statistics so may remove
//compard to emerald 11 wasn't name was number diff balls,
//apparently count increments for each type of ball used
//still irrelevant until fetch applied, then uses to tell if has thrown a ball
//odd seems most of these are un used?


extern struct BattleResults gBattleResults;

struct LinkBattlerHeader
{
    u8 versionSignatureLo;
    u8 versionSignatureHi;
    u8 vsScreenHealthFlagsLo;
    u8 vsScreenHealthFlagsHi;
    struct BattleEnigmaBerry battleEnigmaBerry;
};

struct MegaEvolutionData //could change to altered/elevated/termporary state struct and put terra here? 
{
    u8 toEvolve; // As flags using gBitTable.
    u8 evolvedPartyIds[2]; // As flags using gBitTable;
    bool8 alreadyEvolved[4]; // Array id is used for mon position.
    u16 evolvedSpecies[MAX_BATTLERS_COUNT];
    u16 playerEvolvedSpecies;
    u8 primalRevertedPartyIds[2]; // As flags using gBitTable;
    u16 primalRevertedSpecies[MAX_BATTLERS_COUNT];
    u16 playerPrimalRevertedSpecies;
    enum BattlerId battlerId;
    bool8 playerSelect;
    u8 triggerSpriteId;
    bool8 isWishMegaEvo:1;
    bool8 isPrimalReversion:1;
    bool8 padding:6; //potential terra stuff
};

enum IllusionState
{
    ILLUSION_NOT_SET,
    ILLUSION_OFF,
    ILLUSION_ON
};

struct Illusion
{
    enum IllusionState state;
    struct Pokemon *mon;
};

struct ZMoveData
{
    u8 viable:1;   // current move can become a z move
    u8 viewing:1;  // if player is viewing the z move name instead of regular moves
    u8 healReplacement:6;
    u8 possibleZMoves[MAX_BATTLERS_COUNT];
    u16 baseMoves[MAX_BATTLERS_COUNT];
};

struct DynamaxData
{
    u16 dynamaxTurns[MAX_BATTLERS_COUNT];
    u16 baseMoves[MAX_BATTLERS_COUNT]; // base move of Max Move
    u16 lastUsedBaseMove;
};

struct BattleGimmickData
{
    u8 usableGimmick[MAX_BATTLERS_COUNT];                // first usable gimmick that can be selected for each battler
    bool8 playerSelect;                                  // used to toggle trigger and update battle UI
    u8 triggerSpriteId;
    u8 indicatorSpriteId[MAX_BATTLERS_COUNT];
    u8 toActivate;                                       // stores whether a battler should transform at start of turn as bitfield
    u8 activeGimmick[NUM_BATTLE_SIDES][PARTY_SIZE];      // stores the active gimmick for each party member
    bool8 activated[MAX_BATTLERS_COUNT][GIMMICKS_COUNT]; // stores whether a trainer has used gimmick
};

struct RemovedItem //struct LostItem
{
    u16 originalItem : 15;
    u16 stolen : 1;
};

struct BattleVideo {
    u32 battleTypeFlags;
    rng_value_t rngSeed;
};

struct StatFractions
{
    u8 dividend;
    u8 divisor;
};

extern const struct StatFractions gAccuracyStageRatios[];

union TRANSPARENT StatChangeFlags
{
    int raw;
    u32 raw_u32;
    u16 raw_u16;
    u8 raw_u8;
    struct {
        bool32 allowPtr:1; // STAT_CHANGE_ALLOW_PTR
        bool32 mirrorArmored:1; // STAT_CHANGE_MIRROR_ARMOR
        bool32 onlyChecking:1; // STAT_CHANGE_ONLY_CHECKING
        bool32 notProtectAffected:1; // STAT_CHANGE_NOT_PROTECT_AFFECTED
        bool32 updateMoveEffect:1; // STAT_CHANGE_UPDATE_MOVE_EFFECT
        bool32 statDropPrevention:1; // STAT_CHANGE_CHECK_PREVENTION
        bool32 certain:1; // STAT_CHANGE_CERTAIN
        bool32 padding:25;
    };
};

struct Wish
{
    u16 counter;
    u8 partyId;
};

struct FutureSight
{
    u16 move;
    u16 counter:5;
    u16 counter2:5;
    enum BattlerId battlerIndex:3;
    u16 partyIndex:3;
};

struct WeatherEffects
{
    u8 weatherDuration;
    u8 forecastedCurrWeather; //will be 1st weather effect predicted on switchin by forecast, set so can compare effects before set
    u8 forecastedNextWeather; //will be second weather effect predicted on switchin by forecast
};

struct BattlerState
{
    u8 targetsDone[MAX_BATTLERS_COUNT];

    u32 commandingPartner:1; //will rename since battery work samme just say commandingAlly or somehting
    u32 focusPunchBattlers:1;
    u32 multipleSwitchInBattlers:1;
    u32 alreadyStatusedMoveAttempt:1; // For example when using Thunder Wave on an already paralyzed Pokémon.
    u32 activeAbilityPopUps:1;
    u32 forcedSwitch:1;
    u32 storedHealingWish:1;
    u32 storedLunarDance:1;
    u32 usedEjectItem:1;
    u32 sleepClauseEffectExempt:1; // Stores whether effect should be exempt from triggering Sleep Clause (Effect Spore)
    u32 usedMicleBerry:1;
    u32 pursuitTarget:1;
    u32 stompingTantrumTimer:2;
    u32 canPickupItem:1; //with my reworked effect prob don't need this prob don't even need for honey gather ...but why is it a battler effet...rather than party
    u32 ateBoost:1;
    u32 wasAboveHalfHp:1; // For Berserk, Emergency Exit, Wimp Out and Anger Shell.
    u32 freespace:11; //realize since I want for full turn best put turn dmg in protectstructs
    u32 selectionScriptFinished:1;
    u32 lastMoveTarget:3; // The last target on which each mon used a move, for the sake of Instruct
    // End of Word
    u16 hpOnSwitchout;
    u16 switchIn:1;
    u16 fainted:1;
    u16 isFirstTurn:2;
    u16 protectSuccessiveFail:1; //if fails successive use //think I made may return space
    u16 protectTurnOrderFail:1; //if fails because moved last in turn
    u16 numMisses:3; //added just for multihit result bring actually can use bool, wrong was missing logic, but could lower 1 bit as don't need accout for pop bomb
    u16 successfulHit:1; //needed for stomping tantrum with multihit miss change instad of count miss use to count success if none set stompingtantrum
    u16 commanderType:3;
    u16 padding:3;//prob remove successfail stuff
};
//shouldn't caught mon also be in here? -believe is custom I added

struct PartyState
{
    //Ah right I didn't make this once per battle
    //u32 intrepidSwordBoost:1; //may not need these two can prob wrap in single use ability use
    //u32 dauntlessShieldBoost:1; //yeah that's essentially what these do
    u32 freespace:2;
    u32 ateBerry:1;
    u32 battleBondBoost:1;
    u32 transformZeroToHero:1;
    u32 supersweetSyrup:1;
    u32 timesGotHit:5; //check think this for evo stuff if so may remove
    u32 changedSpecies:11; // For forms when multiple mons can change into the same pokemon.
    u32 sentOut:1; //^w form species change my not use that, but may take que from for setup
    u32 numPhysHits:2; //using for ice face to count hits taken till reset, realize need putin party to prevent abuse
    u32 isKnockedOff:1;
    u32 padding:6;//need tweak singleuseability secondaryitemslot and heldItem use as swap order of side and battlerId
    //end byte
    //u32 knockedOffItem; //was isKnockedOff
    
    u8 ToxicTurnCounter:5; //MAX_TOXIC_TURNS 16 //change make toxic dmg tracked not reset on switch
    u8 SleepTimer:3; //MAX_SLEEP_TURNS 5
    u8 cachedAbilityTimers; //rn just for slow start / wonder guard
    u16 usedHeldItem;//check may need adjust harvest recycle w setup for 2nd held slot
    u16 usedSingleUseAbility; //for abilities that activate once per battle - my addition //not bool stores ability too
    u16 SecondaryItemSlot;//for pickpocket and magician store taken item if already holding item

};//taken from EE may be able to use for 
//single use effects 
//my single use ability stuff
//uses same fields too
//call
//GetBattlerPartyState(battler)->intrepidSwordBoost = TRUE;

struct EventStates
{
    enum EndTurnResolutionOrder endTurn:8;
    u32 endTurnBlock:8; // FirstEventBlock, SecondEventBlock, ThirdEventBlock
    enum BattlerId endTurnBattler:4;
    u32 arenaTurn:8; //battle fronteir stuff not using but keep
    enum BattleSide battlerSide:4;
    enum BattlerId moveEndBattler:4;
    enum FirstTurnEventsStates beforeFirstTurn:8;
    enum FaintedActions faintedAction:8;
    enum BattlerId faintedActionBattler:4;
    enum CancelerState atkCanceler:8;
    enum BattlerId atkCancelerBattler:4;
    enum BattleIntroStates battleIntro:8;
    enum SwitchInEvents switchIn:8;
    enum BattlerId battlerSwitchIn:8; // SwitchInFirstEventBlock, SwitchInSecondEventBlock
    u32 moveEndBlock:8;
};

//think effects meant to last all battle should go here rather than special status as that is cleared on switch
//ya know the simplest solution here is just to further buff traps
//so they aren't cleared when the setting mon switches out...
//plus that already makes sense for the environment traps
//they all have timers so just make them free chip damage at the cost
//of investing in weaker move
// Cleared at the beginning of the battle. Fields need to be cleared when needed manually otherwise.
//vsonic important really need go over this
//pretty sure A LOT of this is outdated or unneeded
//and also just horribly optimized <<<<<<<
/*struct BattleStruct //fill in unused fields when porting
{
    struct BattlerState battlerState[MAX_BATTLERS_COUNT];
    struct PartyState partyState[NUM_BATTLE_SIDES][PARTY_SIZE];
    struct EventStates eventState;
    struct WeatherEffects weatherEffects; //couldn't find in EE cuz forgot I made to combine forecast change w new weather refactor
    struct FutureSight futureSight[MAX_BATTLERS_COUNT];
    struct Wish wish[MAX_BATTLERS_COUNT];
    u8 debugBattler;
    //wrapped move is no longer used, still needfigure how to adjust wrappedby tho
    //u16 wrappedMove[MAX_BATTLERS_COUNT]; // Leftover from Ruby's ewram access. /u16 because epanded move ids  //no longer need the * 2 forgot I redid these
    u16 moveTarget[MAX_BATTLERS_COUNT]; //checked is u16 in emerald, and fixed missed replacement of wrappedMove logic
    u8 expGetterMonId;
    bool8 debugAISet;
    u8 wildVictorySong;//yeah decide move to pokemon struct but will use party size set true false to indicate which battler set effect
    u8 sentInPokes;
    enum BattlerId battlerPreventingSwitchout;
    u8 moneyMultiplier;
    u8 moneyMultiplierMove : 1;
    u8 overworldWeatherDone:1;
    u8 terrainDone:1; //realistically run attempts almost never get into double digits
    u8 runTries:4;//used for boosting run success odds based on number attempts//could shrink and link with moneymultipliermove
    
    u8 savedTurnActionNumber;
    u8 switchInAbilitiesCounter;
    u8 faintedActionsState;
    u8 faintedActionsBattlerId;
    // balign 2
    u16 expValue;
    u8 scriptPartyIdx; // for printing the nickname
    bool8 selectionScriptFinished[MAX_BATTLERS_COUNT];
    enum BattlerId battlerPartyIndexes[MAX_BATTLERS_COUNT];
    u8 monToSwitchIntoId[MAX_BATTLERS_COUNT];
    enum BattlerId battlerPartyOrders[MAX_BATTLERS_COUNT][3];
    u8 caughtMonNick[POKEMON_NAME_LENGTH + 1];
    //u8 caughtMonNick[POKEMON_NAME_LENGTH + 1][2]; //think this will work for catching multiple mon i.e doubles
    struct MegaEvolutionData mega;
    //u8 field_78; // unused
    u8 safariGoNearCounter;
    u8 safariPkblThrowCounter;
    u8 safariEscapeFactor;
    u8 safariCatchFactor;
    u8 linkBattleVsSpriteId_V;
    u8 linkBattleVsSpriteId_S;
    u8 formToChangeInto;
    u8 chosenMovePositions[MAX_BATTLERS_COUNT];
    u8 stateIdAfterSelScript[MAX_BATTLERS_COUNT];
    struct Illusion illusion[MAX_BATTLERS_COUNT];
    //u8 field_88; // unused
    //u8 field_89; // unused
    //u8 field_8A; // unused
    u8 playerPartyIdx;
    //u8 field_8C; // unused
    //u8 field_8D; // unused
    s8 aiFinalScore[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // AI, target, moves to make debugging easier
    u8 aiMoveOrAction[MAX_BATTLERS_COUNT];
    u8 aiChosenTarget[MAX_BATTLERS_COUNT]; //ported these 3 hope ot a problem
    u8 soulheartBattlerId;  //Magearna ability
    u8 friskedBattler; // Frisk needs to identify 2 battlers in double battles.
    bool8 friskedAbility; // If identifies two mons, show the ability pop-up only once.
    u16 changedSpecies[NUM_BATTLE_SIDES][PARTY_SIZE]; // For Zygarde or future forms when multiple mons can change into the same pokemon.
    u8 stringMoveType;
    u8 expGetterBattlerId;
    bool8 ateBoost[MAX_BATTLERS_COUNT];//says that but ateberry seems to only be used by dodriogame
    u8 ateBerry[2]; // array id determined by side, each party pokemon as bit
    u8 stolenStats[NUM_BATTLE_STATS]; // hp byte is used for which stats to raise, other inform about by how many stages
    //u8 field_90; // unused   //ok thank god these really are unused, I'll replace when I need to bing stuff from emerald
    u8 absentBattlerFlags;
    u8 AI_monToSwitchIntoId[MAX_BATTLERS_COUNT]; //changed from 2, based on emerald
    u8 simulatedInputState[4];  // used by Oak/Old Man/Pokedude controllers
    //u8 lastTakenMove[MAX_BATTLERS_COUNT * 2 * 2]; // ask gamefreak why they declared it that way /original here, emerald version below
    u16 lastTakenMove[MAX_BATTLERS_COUNT]; // Last move that a battler was hit with.
    u8 lastMoveFailed; // as bits for each battler, for the sake of Stomping Tantrum
    u8 lastMoveTarget[MAX_BATTLERS_COUNT]; // The last target on which each mon used a move, for the sake of Instruct
    u16 hpOnSwitchout[2];
    u16 abilityPreventingSwitchout; //could probably use lastTakenMove with ai, to keep a count of a party mons moveset.
    u8 hpScale;
    u16 savedBattleTypeFlags;
    void (*savedCallback)(void);
    u16 synchronizeMoveEffect;
    u8 multiplayerId;
    u8 unableToUseMove:1; // for the current action only, to check if the battler failed to act at end turn use the DisableStruct member
    u8 unused:7;
    u8 atkCancellerTracker;//almost feels like I should turn these party wide things into their own struct at this point
    //u16 usedHeldItems[MAX_BATTLERS_COUNT]; //original value below is emerald expansion changed version,  
    //u16 usedHeldItems[PARTY_SIZE][NUM_BATTLE_SIDES]; //check may need adjust harvest recycle w setup for 2nd held slot // For each party member and side. For harvest, recycle  //think I"m setup to use this? adjusted all values now
    //can save some space here, this is different from above it doesn't store id of what was used it just does true/false
    //then again as I'm just checking for a positive value if I stored the ability used
    //then I can use this to ensure anticipation/forewarn can't reactivate for a different mon
    u16 chosenItem[4]; // why is this an u8?
    u8 AI_itemType[2];
    u8 AI_itemFlags[2];
    u16 choicedMove[MAX_BATTLERS_COUNT];
    u16 changedItems[MAX_BATTLERS_COUNT];
    u8 intimidateBattler;
    u8 switchInItemsCounter;
    u8 field_DA; // battle tower related
    u8 turnSideTracker;
    //u8 fillerDC[0xDF - 0xDC];
    u8 givenExpMons;
    u16 lastTakenMoveFrom[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT];// a 2-D array [target][attacker]
    u16 castformPalette[MAX_BATTLERS_COUNT][16]; //important, may be how they fixed alcremie?
    u8 wishPerishSongState;
    u8 wishPerishSongBattlerId;
    u8 isAtkCancelerForCalledMove:1; // Certain cases in atk canceler should only be checked once, when the original move is called, however others need to be checked the twice.
    u8 savedBattlerTarget;
    bool8 anyMonHasTransformed; // Only used in battle_tv.c
    u16 tracedAbility[MAX_BATTLERS_COUNT]; //didn't really need to port, but prob can use it to show current ability in menu summary screen //important
    u16 hpBefore[MAX_BATTLERS_COUNT]; // Hp of battlers before using a move. For Berserk
    bool8 spriteIgnore0Hp;//vsonic look into
    u8 field_182; //look into this
    u8 quickClawBattlerId;
    struct RemovedItem itemLost[NUM_BATTLE_SIDES][PARTY_SIZE];  // Player's team that had items stolen (two bytes per party member)
    u8 blunderPolicy : 1; // should blunder policy activate
    u8 swapDamageCategory:1; // Photon Geyser, Shell Side Arm, Light That Burns the Sky
    u8 sameMoveTurns[MAX_BATTLERS_COUNT]; // For Metronome, number of times the same moves has been SUCCESFULLY used.
    u16 moveEffect2; // For Knock Off smack down and removestatus moves i.e smelling salts wakeupslap & sparklin aria   -PORTED
    u8 ballSpriteIds[2];    // item gfx, window gfx
    u8 shouldPrintPreHitAbilityText:1;
    u8 padding:7;
    u8 appearedInBattle; // Bitfield to track which Pokemon appeared in battle. Used for Burmy's form change
    u8 skyDropTargets[MAX_BATTLERS_COUNT]; // For Sky Drop, to account for if multiple Pokemon use Sky Drop in a double battle.
    // When using a move which hits multiple opponents which is then bounced by a target, we need to make sure, the move hits both opponents, the one with bounce, and the one without.
    bool8 effectsBeforeUsingMoveDone:1; // Mega Evo and Focus Punch/Shell Trap effects.  //adding to hopefully fix bind not working on switch-in
    u8 attackerBeforeBounce : 2;
    u16 overwrittenAbilities[MAX_BATTLERS_COUNT];    // abilities overwritten during battle (keep separate from battle history in case of switching)
    u8 usedExclusiveFormGimmick[NUM_BATTLE_SIDES];// Bitfield for each party. //for my use mega or primal reversion since only 1 per battle tobe activated on switchin or turn use
    u8 pursuitTarget:4; // Each battler as a bit.
    u8 pursuitSwitchByMove:1;
    u8 pursuitStoredSwitch; // Stored id for the Pursuit target's switch
    u8 obedienceResult:3;
    u8 pledgeMove;
    u8 padded[3]; //added to keep padding below on 4 byte divislbe in case was beneficial
    //u8 presentBasePower; //used for   multihit move effect check, but with my version don't need this
    //bool8 slowstartDone[MAX_BATTLERS_COUNT]; don't need this, also go over these structs as well like I did pokemon.h
    // align 4
    union {
        struct LinkBattlerHeader linkBattlerHeader;
        struct MultiPartnerMenuPokemon multiBattleMons[3];
    } multiBuffer;
    u8 padding_1E4[0x18];

    
}; // size == 0x200 bytes
*/


struct BattleStruct
{
    struct BattlerState battlerState[MAX_BATTLERS_COUNT];
    struct PartyState partyState[NUM_BATTLE_SIDES][PARTY_SIZE];
    struct EventStates eventState;
    struct WeatherEffects weatherEffects; //couldn't find in EE cuz forgot I made to combine forecast change w new weather refactor
    struct FutureSight futureSight[MAX_BATTLERS_COUNT];
    struct Wish wish[MAX_BATTLERS_COUNT];
    u16 moveTarget[MAX_BATTLERS_COUNT];
    u32 expShareExpValue;
    u32 expValue;
    u8 weatherDuration;
    u8 expGettersOrder[PARTY_SIZE]; // First battlers which were sent out, then via exp-share
    u8 expGetterMonId;
    u8 expOrderId:3;
    u8 expGetterBattlerId:2;
    //may use or just make exp was shared message
    u8 teamGotExpMsgPrinted:1; // The 'Rest of your team got msg' has been printed.
    u8 givenExpMons; // Bits for enemy party's pokemon that gave exp to player's party.
    u8 expSentInMons; // As bits for player party mons - not including exp share mons.
    u8 wildVictorySong;
    enum Type dynamicMoveType;
    enum BattlerId battlerPreventingSwitchout;
    u8 moneyMultiplier:6;
    u8 moneyMultiplierItem:1;
    u8 moneyMultiplierMove:1;
    u8 savedTurnActionNumber;
    u8 scriptPartyIdx; // for printing the nickname
    u8 battlerPartyIndexes[MAX_BATTLERS_COUNT];
    u8 monToSwitchIntoId[MAX_BATTLERS_COUNT];
    u8 battlerPartyOrders[MAX_BATTLERS_COUNT][PARTY_SIZE / 2];
    u8 runTries;
    u8 caughtMonNick[POKEMON_NAME_LENGTH + 1];
    u8 safariGoNearCounter;
    u8 safariPkblThrowCounter;
    u8 safariEscapeFactor;
    u8 safariCatchFactor;
    u8 linkBattleVsSpriteId_V; // The letter "V"
    u8 linkBattleVsSpriteId_S; // The letter "S"
    u8 chosenMovePositions[MAX_BATTLERS_COUNT];
    u8 stateIdAfterSelScript[MAX_BATTLERS_COUNT];
    u8 prevSelectedPartySlot;
    u8 stringMoveType;
    //not using
    u8 palaceFlags; // First 4 bits are "is <= 50% HP and not asleep" for each battler, last 4 bits are selected moves to pass to AI
    u8 field_93; // related to choosing pokemon? //doesn't exist in FR not used at all
    u8 wallyBattleState;
    u8 wallyMovesState;
    u8 wallyWaitFrames;
    u8 wallyMoveFrames;
    //end of not used
    u16 lastTakenMove[MAX_BATTLERS_COUNT]; // Last move that a battler was hit with.
    u32 savedBattleTypeFlags;
    u16 abilityPreventingSwitchout;
    u8 hpScale;
    u16 synchronizeMoveEffect;
    //not using
    u8 anyMonHasTransformed:1; // Only used in battle_tv.c
    u8 sleepClauseNotBlocked:1;
    u8 isSkyBattle:1;
    //end of not using
    u8 unableToUseMove:1; // for the current action only, to check if the battler failed to act at end turn use the DisableStruct member
    u8 bypassMoldBreakerChecks:1; // for ABILITYEFFECT_IMMUNITY
    u8 shouldPrintPreHitAbilityText:1;
    u8 unused:2;
    void (*savedCallback)(void);
    u16 chosenItem[MAX_BATTLERS_COUNT];
    u16 choicedMove[MAX_BATTLERS_COUNT];
    u16 changedItems[MAX_BATTLERS_COUNT];
    u8 switchInBattlerCounter; //replaces switchInItemsCounter and switch in abilitiescounter
    u16 lastTakenMoveFrom[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT]; // a 2-D array [target][attacker]
    union {
        struct LinkBattlerHeader linkBattlerHeader;
        struct BattleVideo battleVideo; //is truct MultiPartnerMenuPokemon multiBattleMons[3] in FR
    } multiBuffer; //ok see in EM above is moved to battle_main instead of here it has an equivalent
    u8 battlerKOAnimsRunning:3; //think animation on faint foe, not using vsonic
    //also plan not use dont want ability pop ups
    u8 friskedAbility:1; // If identifies two mons, show the ability pop-up only once.
    u8 fickleBeamBoosted:1;
    u8 poisonPuppeteerConfusion:1;
    u8 toxicChainPriority:1; // If Toxic Chain will trigger on target, all other non volatiles will be blocked
    u8 battlersSorted:1; // To avoid unnessasery computation
    //review feature may not use
    //struct BattleTvMovePoints tvMovePoints; //keeping off for now
    //struct BattleTv tv;
    u8 AI_monToSwitchIntoId[MAX_BATTLERS_COUNT];
    //fronteir stuff not using
    s8 arenaMindPoints[NUM_BATTLE_SIDES];
    s8 arenaSkillPoints[NUM_BATTLE_SIDES];
    u16 arenaStartHp[NUM_BATTLE_SIDES];
    u8 arenaLostPlayerMons; // Bits for party member, lost as in referee's decision, not by fainting.
    u8 arenaLostOpponentMons;
    //end not using
    u8 debugBattler;
    u8 magnitudeBasePower;
    u8 presentBasePower;
    u8 savedBattlerTarget[5];
    u8 savedBattlerAttacker[5];
    u8 savedTargetCount:4;
    u8 savedAttackerCount:4;
    //prob not using
    u8 abilityPopUpSpriteIds[MAX_BATTLERS_COUNT][NUM_BATTLE_SIDES];    // two per battler
    struct ZMoveData zmove;
    struct DynamaxData dynamax;
    struct BattleGimmickData gimmick;
    //unsure bout this
    const u8 *trainerSlideMsg;
    u8 stolenStats[NUM_BATTLE_STATS]; // hp byte is used for which stats to raise, other inform about by how many stages
    enum Ability tracedAbility[MAX_BATTLERS_COUNT];
    struct Illusion illusion[MAX_BATTLERS_COUNT];
    enum BattlerId soulheartBattlerId;
    enum BattlerId friskedBattler; // Frisk needs to identify 2 battlers in double battles.
    enum BattlerId quickClawBattlerId;
    struct RemovedItem itemLost[NUM_BATTLE_SIDES][PARTY_SIZE];  // Pokemon that had items consumed or stolen (two bytes per party member per side)
    u8 blunderPolicy:1; // should blunder policy activate
    u8 swapDamageCategory:1; // Photon Geyser, Shell Side Arm, Light That Burns the Sky
    u8 bouncedMoveIsUsed:1; //^believe end of values I already ported
    u8 snatchedMoveIsUsed:1;
    u8 descriptionSubmenu:1; // For Move Description window in move selection screen //not using made callback instead
    u8 ackBallUseBtn:1; // Used for the last used ball feature
    u8 ballSwapped:1; // Used for the last used ball feature
    u8 throwingPokeBall:1;
    u8 ballSpriteIds[2];    // item gfx, window gfx
    u8 moveInfoSpriteId; // move info, window gfx
    u8 skyDropTargets[MAX_BATTLERS_COUNT]; // For Sky Drop, to account for if multiple Pokemon use Sky Drop in a double battle.
    // When using a move which hits multiple opponents which is then bounced by a target, we need to make sure, the move hits both opponents, the one with bounce, and the one without.
    u16 beatUpSpecies[PARTY_SIZE]; // Species for Gen5+ Beat Up, otherwise party indexes
    u8 attackerBeforeBounce:2;
    u8 beatUpSlot:3;
    u8 pledgeMove:1;
    u8 effectsBeforeUsingMoveDone:1; // Mega Evo and Focus Punch/Shell Trap effects.
    u8 padding3:1;
    u8 itemPartyIndex[MAX_BATTLERS_COUNT];
    u8 itemMoveIndex[MAX_BATTLERS_COUNT];
    s32 aiDelayTimer; // Counts number of frames AI takes to choose an action.
    s32 aiDelayFrames; // Number of frames it took to choose an action.
    s32 aiDelayCycles; // Number of cycles it took to choose an action.
    u8 supremeOverlordCounter[MAX_BATTLERS_COUNT];
    u8 shellSideArmCategory[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT];
    u8 speedTieBreaks; // MAX_BATTLERS_COUNT! values.
    enum DamageCategory categoryOverride:8; // for Z-Moves and Max Moves
    u32 stellarBoostFlags[NUM_BATTLE_SIDES]; // stored as a bitfield of flags for all types for each side
    u8 monCausingSleepClause[NUM_BATTLE_SIDES]; // Stores which pokemon on a given side is causing Sleep Clause to be active as the mon's index in the party //not using
    u16 opponentMonCanTera:6;
    u16 opponentMonCanDynamax:6;
    u16 additionalEffectsCounter:4; // A counter for the additionalEffects applied by the current move in Cmd_setadditionaleffects
    u8 pursuitStoredSwitch; // Stored id for the Pursuit target's switch
    s32 battlerExpReward;
    u16 prevTurnSpecies[MAX_BATTLERS_COUNT]; // Stores species the AI has in play at start of turn
    s16 passiveHpUpdate[MAX_BATTLERS_COUNT]; // non-move damage and healing
    s16 moveDamage[MAX_BATTLERS_COUNT];
    u16 moveResultFlags[MAX_BATTLERS_COUNT];
    enum CalcDamageState noResultString[MAX_BATTLERS_COUNT];
    u8 doneDoublesSpreadHit:1;
    u8 calculatedDamageDone:1;
    u8 calculatedSpreadMoveAccuracy:1;
    u8 printedStrongWindsWeakenedAttack:1;
    u8 numSpreadTargets:3;
    u8 moldBreakerActive:1;
    //struct MessageStatus slideMessageStatus; vsonic
    u8 trainerSlideSpriteIds[MAX_BATTLERS_COUNT];
    //unsure if need above 2
    u8 hazardsQueue[NUM_BATTLE_SIDES][HAZARDS_MAX_COUNT];
    u8 numHazards[NUM_BATTLE_SIDES];
    u8 hazardsCounter:4; // Counter for applying hazard on switch in
    enum SubmoveState submoveAnnouncement:2;
    u8 tryDestinyBond:1;
    u8 tryGrudge:1;
    u16 flingItem;
    u8 incrementEchoedVoice:1;
    u8 echoedVoiceCounter:3;
    u8 preAttackAnimPlayed:1;
    u8 padding4:1;
    u8 magicCoatActive:1;
    u8 magicBounceActive:1;
    u8 moveBouncer;
};
extern struct BattleStruct *gBattleStruct;

struct AiBattleData
{
    s32 finalScore[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // AI, target, moves to make debugging easier
    u8 playerStallMons[PARTY_SIZE];
    u8 chosenMoveIndex[MAX_BATTLERS_COUNT];
    u8 chosenTarget[MAX_BATTLERS_COUNT];
    u16 aiUsingGimmick:6;
    u8 actionFlee:1;
    u8 choiceWatch:1;
    u8 padding:6;
};

#define DYNAMIC_TYPE_MASK                 ((1 << 6) - 1)
#define F_DYNAMIC_TYPE_IGNORE_PHYSICALITY  (1 << 6) // If set, the dynamic type's physicality won't be used for certain move effects.
#define F_DYNAMIC_TYPE_SET                 (1 << 7) // Set for all dynamic types to distinguish a dynamic type of Normal (0) from no dynamic type.
//pretty sure no longer necessary now that type none is added

//looking over EE seems this is only necessary for
//differentiating dynamicmovetype 0 from 0 of type normal
//but EE also adjusted type define so normal is 1 not 0
//meaning its no longer necessary - thankful since I'm currently not using
//can remove the whole 0xFF thing if I update type defines as well.

//changing this as it is, doesn't work right with things that set 
//type normal but aren't normal, since normal is type 0
//think this may be only change I need to make actually
#define GET_MOVE_TYPE(move, typeArg)                                    \
{                                                                       \
    if (gBattleStruct->dynamicMoveType)                                 \
        typeArg = gBattleStruct->dynamicMoveType;                       \
    else                                                                \
        typeArg = gMovesInfo[move].type;                              \
}

//leave else set to 0, as first argument should always be true, 
//so essentially just means if not two typed move,
//in which case I don't want to read the argument as a type at all
//changed to read as mystery so if there is an accident and its read it'll 
//have no effect hopefully - or should I do the opposite and make it very obvious
//nvm its fine, the is only used in casess where I explicitly say its two typed
//and it doesnt effect anything else so secondary argument doesn't matter at all
//change don't want to worry bout changing secondary type
#define GET_MOVE_ARGUMENT(move, typeArg)                                   \
{                                                                          \
    if (gMovesInfo[move].effect == EFFECT_TWO_TYPED_MOVE)               \
        typeArg = gMovesInfo[move].argument;                             \
}

//#define IS_TYPE_PHYSICAL(moveType)(moveType < TYPE_MYSTERY)
//#define IS_TYPE_SPECIAL(moveType)(moveType > TYPE_MYSTERY)


#define IS_MOVE_PHYSICAL(move)(GetBattleMoveSplit(move) == DAMAGE_CATEGORY_PHYSICAL)
#define IS_MOVE_SPECIAL(move)(GetBattleMoveSplit(move) == DAMAGE_CATEGORY_SPECIAL)
#define BATTLER_MAX_HP(battlerId)(gBattleMons[battlerId].hp == gBattleMons[battlerId].maxHP)
#define TARGET_TURN_DAMAGED ((gProtectStructs[gBattlerTarget].physicalDmg != 0 || gProtectStructs[gBattlerTarget].specialDmg != 0))
//#define IS_BATTLER_OF_TYPE(battlerId, type)((gBattleMons[battlerId].type1 == type || gBattleMons[battlerId].type2 == type || gBattleMons[battlerId].type3 == type))
#define IS_SPECIES_OF_TYPE(species, type)((gSpeciesInfo[species].type1 == type || gSpeciesInfo[species].type2 == type))

static inline bool32 IsBattleMovePhysical(enum Move move)
{
    return GetBattleMoveCategory(move) == DAMAGE_CATEGORY_PHYSICAL;
}

static inline bool32 IsBattleMoveSpecial(enum Move move)
{
    return GetBattleMoveCategory(move) == DAMAGE_CATEGORY_SPECIAL;
}

static inline bool32 IsBattleMoveStatus(enum Move move)
{
    return GetMoveCategory(move) == DAMAGE_CATEGORY_STATUS;
}

/* Checks if 'battlerId' is any of the types.
 * Passing multiple types is more efficient than calling this multiple
 * times with one type because it shares the 'GetBattlerTypes' result. */
#define _IS_BATTLER_ANY_TYPE(battlerId, ignoreTera, ...) \
    ({ \
        enum Type types[3]; \
        GetBattlerTypes(battlerId, ignoreTera, types); \
        RECURSIVELY(R_FOR_EACH(_IS_BATTLER_ANY_TYPE_HELPER, __VA_ARGS__)) FALSE; \
    })

#define _IS_BATTLER_ANY_TYPE_HELPER(type) (types[0] == type) || (types[1] == type) || (types[2] == type) ||

#define IS_BATTLER_ANY_TYPE(battlerId, ...) _IS_BATTLER_ANY_TYPE(battlerId, FALSE, __VA_ARGS__)

#define IS_BATTLER_OF_TYPE IS_BATTLER_ANY_TYPE
#define IS_BATTLER_ANY_BASE_TYPE(battlerId, ...) _IS_BATTLER_ANY_TYPE(battlerId, TRUE, __VA_ARGS__)
#define IS_BATTLER_OF_BASE_TYPE IS_BATTLER_ANY_BASE_TYPE

#define IS_BATTLER_TYPELESS(battlerId) \
    ({ \
        enum Type types[3]; \
        GetBattlerTypes(battlerId, FALSE, types); \
        types[0] == TYPE_MYSTERY && types[1] == TYPE_MYSTERY && types[2] == TYPE_MYSTERY; \
    })

#define SET_BATTLER_TYPE(battlerId, type)           \
{                                                   \
    gBattleMons[battlerId].type1 = type;            \
    gBattleMons[battlerId].type2 = type;            \
    gBattleMons[battlerId].type3 = TYPE_MYSTERY;    \
}
//made this myself
#define SET_BATTLER_TYPE2(battlerId, type)           \
{                                                   \
    gBattleMons[battlerId].type2 = type;            \
    gBattleMons[battlerId].type3 = TYPE_MYSTERY;    \
}

//made this myself
//plan use this for planned idea of terra
#define SET_BATTLER_TYPE3(battlerId, type)           \
{                                                   \
    gBattleMons[battlerId].type3 = type;            \
}

//change so type 3 is unaffected
#define SET_BATTLER_TYPE_PROTEAN(battlerId, type)   \
{                                                   \
    gBattleMons[battlerId].type1 = type;            \
    gBattleMons[battlerId].type2 = type;            \
}

#define GET_STAT_BUFF_ID(n)((n & 7))              // first three bits 0x1, 0x2, 0x4
#define GET_STAT_BUFF_VALUE_WITH_SIGN(n)((n & 0xF8))
#define GET_STAT_BUFF_VALUE(n)(((n >> 3) & 0xF))      // 0x8, 0x10, 0x20, 0x40
#define STAT_BUFF_NEGATIVE 0x80                     // 0x80, the sign bit

#define SET_STAT_BUFF_VALUE(n)((((n) << 3) & 0xF8))

#define SET_STATCHANGER(statId, stage, goesDown)(gBattleScripting.statChanger = (statId) + ((stage) << 3) + (goesDown << 7))
#define SET_STATCHANGER2(dst, statId, stage, goesDown)(dst = (statId) + ((stage) << 3) + (goesDown << 7)) //for changing 2 different stats in a turn

// NOTE: The members of this struct have hard-coded offsets 
//       in include/constants/battle_script_commands.h
//very finicky so not gonna bit field this
struct BattleScripting  //remember expanding this costs ewram
{
    s32 painSplitHp;
    s32 bideDmg;
    u8 multihitString[6];
    u16 savedStringId; //originally store table id for stringid of two turn moves, made u16 to store actually stringIds for other effects
    u8 animArg1;
    u8 animArg2;
    u16 multihitMoveEffect;
    u8 moveendState;; //move end
    enum BattlerId battlerWithAbility;
    u8 statChangeId; //new for dynamic stat set, this stat id will be passed to statchanger
    enum BattlerId battler;
    u8 animTurn;
    u8 animTargetsHit;
    u8 statChanger;
    bool8 statAnimPlayed;
    u8 atk23_getexpState;
    u8 battleStyle;
    u8 atk6C_drawlvlupboxState;
    u8 learnMoveState;
    u8 field_25_pursuitDoublesAttacker; //pursuit damage  //not sure what htis does don't see it used and double damage is handled in script not with this value?
    u8 reshowMainState;
    u8 reshowHelperState;
    u8 levelUpHP;    //used for hp change on level up & shedinja hp stuff in pokemon.c
//new values below here
    u8 savedStatChanger; // For if attempting to change stat two times(ex. Moody)
    u8 savedBattler;  //for now saveBattler not used just using normal sBattler - ported just in case there's issue

    /* u8 illusionNickHack; // To properly display nick in STRINGID_ENEMYABOUTTOSWITCHPKMN.
     bool8 fixedPopup;   // Force ability popup to stick until manually called back
     u16 abilityPopupOverwrite;  //UNCOMMENT if you want these features
     u16 savedMoveEffect; // For moves hitting multiple targets.
     u16 moveEffect;*/
    u8 switchCase;  // Special switching conditions, eg. red card
    u8 overrideBerryRequirements;
    //bool8 monCaught;  //believe most of these aren't needed, can be handled with battlescript , they are just different ways of doing things, btu I prefer saving ram.
    s32 savedDmg;   //port feature leaving out for now - added as needed for bs somehow
    u16 savedMoveEffect; // For moves hitting multiple targets.
    u16 moveEffect; //don't change capitalization won't be able to just copy from emerald easily
    u8 stickyWebStatDrop; // To prevent Defiant activating on a Court Change'd Sticky Web
};

enum
{
    BACK_PIC_RED,
    BACK_PIC_LEAF,
    BACK_PIC_RS_BRENDAN,
    BACK_PIC_RS_MAY,
    BACK_PIC_POKEDUDE,
    BACK_PIC_OLDMAN
};

enum turn_Priority
{
    USER_FIRST = 0,
    BATTLER_FIRST = 1,
    SPEED_TIE = 2
};


struct BattleSpriteInfo
{
    u16 invisible:1; // 0x1
    u16 lowHpSong:1; // 0x2
    u16 behindSubstitute:1; // 0x4
    u16 flag_x8:1; // 0x8
    u16 hpNumbersNoBars:1; // 0x10
    u16 transformSpecies;
};

struct BattleAnimationInfo
{
    u16 animArg; // to fill up later
    u8 field_2;
    u8 field_3;
    u8 field_4;
    u8 field_5;
    u8 field_6;
    u8 field_7;
    u8 ballThrowCaseId:6;
    u8 isCriticalCapture:1;
    u8 criticalCaptureSuccess:1;
    u8 introAnimActive:1;
    u8 wildMonInvisible:1;
    u8 field_9_x1C:3;
    u8 field_9_x20:1;
    u8 field_9_x40:1;
    u8 field_9_x80:1;
    u8 numBallParticles;
    u8 field_B;
    s16 ballSubpx;
    u8 field_E;
    u8 field_F;
};

struct BattleHealthboxInfo
{
    u8 partyStatusSummaryShown:1;
    u8 healthboxIsBouncing:1;
    u8 battlerIsBouncing:1;
    u8 ballAnimActive:1; // 0x8
    u8 statusAnimActive:1; // x10
    u8 animFromTableActive:1; // x20
    u8 specialAnimActive:1; // x40
    u8 triedShinyMonAnim:1;
    u8 finishedShinyMonAnim:1;
    u8 opponentDrawPartyStatusSummaryDelay:4;
    u8 bgmRestored:1;
    u8 waitForCry:1;
    u8 healthboxSlideInStarted:1;
    u8 healthboxBounceSpriteId;
    enum BattlerId battlerBounceSpriteId;
    u8 animationState;
    u8 partyStatusDelayTimer;
    u8 matrixNum;

    u8 shadowSpriteIdPrimary;
    u8 shadowSpriteIdSecondary;

    u8 soundTimer;
    u8 introEndDelay;
    u8 field_A;
    u8 field_B;
};

struct BattleBarInfo
{
    u8 healthboxSpriteId;
    s32 maxValue;
    s32 oldValue;
    s32 receivedValue;
    s32 currValue;
};

struct BattleSpriteData
{
    struct BattleSpriteInfo *battlerData;
    struct BattleHealthboxInfo *healthBoxesData;
    struct BattleAnimationInfo *animationData;
    struct BattleBarInfo *battleBars;
};

extern struct BattleSpriteData *gBattleSpritesDataPtr;



// Move this somewhere else

#include "sprite.h"

struct MonSpritesGfx
{
    void *firstDecompressed; // ptr to the decompressed sprite of the first pokemon
    u8 *spritesGfx[MAX_BATTLERS_COUNT];
    struct SpriteTemplate templates[MAX_BATTLERS_COUNT];
    struct SpriteFrameImage frameImages[MAX_BATTLERS_COUNT][4];
    u8 *barFontGfx;
    u16 *buffer;
};

struct PokedudeBattlerState
{
    u8 action_idx;
    u8 move_idx;
    u8 timer;
    u8 msg_idx;
    u8 saved_bg0y;
};

/*struct TotemBoost
{
    u8 stats;   // bitfield for each battle stat that is set if the stat changes
    s8 statChanges[NUM_BATTLE_STATS - 1];    // highest bit being set decreases the stat
}; */
/* size = 8 */

//put here to make non-static so can refer to in other files
//this is window used for battle move selection ui
extern const struct WindowTemplate sStandardBattleWindowTemplates[];

// All battle variables are declared in battle_main.c
extern u16 gBattle_BG0_X;
extern u16 gBattle_BG0_Y;
extern u16 gBattle_BG1_X;
extern u16 gBattle_BG1_Y;
extern u16 gBattle_BG2_X;
extern u16 gBattle_BG2_Y;
extern u16 gBattle_BG3_X;
extern u16 gBattle_BG3_Y;
extern u16 gBattle_WIN0H;
extern u16 gBattle_WIN0V;
extern u16 gBattle_WIN1H;
extern u16 gBattle_WIN1V;
extern struct BattleSpritesGfx *gMonSpritesGfx;
extern u8 gBattleOutcome;
extern u16 gLastUsedItem;
extern u32 gBattleTypeFlags;
extern struct MonSpritesGfx *gMonSpritesGfxPtr;
extern u16 gTrainerBattleOpponent_A;
extern u16 gTrainerBattleOpponent_B;
extern u16 gPartnerTrainerId;
extern u16 gMoveToLearn;
extern u16 gBattleMovePower;
extern struct BattleEnigmaBerry gEnigmaBerries[MAX_BATTLERS_COUNT];
extern u16 gCurrentMove;
extern u16 gChosenMove;
extern u16 gCalledMove;
extern u8 gCritMultiplier;
extern u16 gBattleWeather;
extern u16 gLastUsedAbility;
extern u8 gBattlerInMenuId;
extern u8 gPotentialItemEffectBattler;
extern u8 gBattlersCount;
extern u16 gBattlerPartyIndexes[MAX_BATTLERS_COUNT];
extern s32 gBattleMoveDamage;
extern s32 gStoredHp;
extern u16 gIntroSlideFlags;
//extern u32 gTransformedPersonalities[MAX_BATTLERS_COUNT];
//extern struct TotemBoost gTotemBoosts[MAX_BATTLERS_COUNT];
extern u8 gBattlerPositions[MAX_BATTLERS_COUNT];
extern u8 gHealthboxSpriteIds[MAX_BATTLERS_COUNT];
extern u8 gBattleOutcome;  //no idea why I had removed this
extern u8 gBattleMonForms[MAX_BATTLERS_COUNT]; //vsonic important not used in EE
extern void (*gBattlerControllerFuncs[MAX_BATTLERS_COUNT])(enum BattlerId battler);
extern u32 gBattleControllerExecFlags;
extern u8 gActionSelectionCursor[MAX_BATTLERS_COUNT];
extern void (*gPreBattleCallback1)(void);
extern bool8 gDoingBattleAnim;
extern u32 gTransformedPersonalities[MAX_BATTLERS_COUNT];
extern bool8 gTransformedShininess[MAX_BATTLERS_COUNT];
extern struct PokedudeBattlerState *gPokedudeBattlerStates[MAX_BATTLERS_COUNT];
extern u8 *gBattleAnimBgTileBuffer;
extern u8 *gBattleAnimBgTilemapBuffer;
extern void (*gBattleMainFunc)(void);
extern u8 gMoveSelectionCursor[MAX_BATTLERS_COUNT];
extern u8 gSavedPartyCount;
extern u8 gBattlerAttacker;
extern u8 gEffectBattler;
extern u8 gMultiHitCounter;
extern u8 gMultiTask;
extern struct BattleScripting gBattleScripting;
extern struct StartingStatuses gStartingStatuses;
extern struct AiBattleData *gAiBattleData;
extern struct AiThinkingStruct *gAiThinkingStruct;
extern struct AiLogicData *gAiLogicData;
extern struct AiPartyData *gAiPartyData;
extern struct BattleHistory *gBattleHistory;
extern u8 gBattlerFainted;
extern u8 gSentPokesToOpponent[2];
extern const u8 *gBattlescriptCurrInstr;
extern const u8 *gSelectionBattleScripts[MAX_BATTLERS_COUNT];
extern u16 gLastMoves[MAX_BATTLERS_COUNT];
extern u8 gBattlerByTurnOrder[MAX_BATTLERS_COUNT];
extern u8 gBattleCommunication[BATTLE_COMMUNICATION_ENTRIES_COUNT];
extern u32 gSideStatuses[2];    //upgraded from u16, because of increase in side status flags
extern u32 gHitMarker;
extern u16 gChosenMoveByBattler[MAX_BATTLERS_COUNT];
extern u8 gMoveResultFlags;
extern s32 gTakenDmg[MAX_BATTLERS_COUNT];
extern u8 gTakenDmgByBattler[MAX_BATTLERS_COUNT];
extern u8 gCurrentActionFuncId;
extern u8 gCurrMovePos;
extern u8 gChosenMovePos;
extern u8 gBattleControllerData[MAX_BATTLERS_COUNT];
extern u8 gBattlerStatusSummaryTaskId[MAX_BATTLERS_COUNT];
extern u16 gDynamicBasePower;
extern u32 gFieldStatuses;
extern struct FieldTimer gFieldTimers; //both needed for things like gravity etc.  //can apparently hold more than one effect at once?
extern u8 gCatchTargetId; //replaced fetch use to replace hard code battle position
extern u16 gLastUsedBall;
extern bool8 gSwapDamageCategory; // Photon Geyser, Shell Side Arm, Light That Burns the Sky
extern u16 gLastLandedMoves[MAX_BATTLERS_COUNT];
extern u8 gLastHitBy[MAX_BATTLERS_COUNT];
extern u16 gLastUsedMoveType[MAX_BATTLERS_COUNT];
extern u8 gMultiUsePlayerCursor;
extern u8 gNumberOfMovesToChoose;
extern u16 gLastHitByType[MAX_BATTLERS_COUNT];
extern s32 gHpDealt;
extern u16 gPauseCounterBattle;
extern u16 gPaydayMoney;
extern u16 gLockedMoves[MAX_BATTLERS_COUNT];
extern u16 gLastUsedMove;
extern u8 gCurrentTurnActionNumber;
extern struct BattleResources *gBattleResources;
extern u16 gExpShareExp;
extern u8 gParticipatedInBattle; //replaced gLeveledUpInBattle for evo rework
extern u16 gLastResultingMoves[MAX_BATTLERS_COUNT];
extern u16 gLastPrintedMoves[MAX_BATTLERS_COUNT];
extern u8 gActionsByTurnOrder[MAX_BATTLERS_COUNT];
extern u8 gChosenActionByBattler[MAX_BATTLERS_COUNT];
extern u8 gBattleEnvironment;
extern struct MultiPartnerMenuPokemon gMultiPartnerParty[3];
extern u16 gRandomTurnNumber;

extern const u16 gProtectSuccessRates[NUM_PROTECT_ODDS];

static inline bool32 IsBattlerAlive(enum BattlerId battler)
{
    if (battler >= gBattlersCount)
        return FALSE;
    else if (gBattleMons[battler].hp == 0)
        return FALSE;
    else if (gAbsentBattlerFlags & (1u << battler))
        return FALSE;
    else
        return TRUE;
}

static inline bool32 IsBattlerTurnDamaged(enum BattlerId battler)
{
    return gSpecialStatuses[battler].damagedByAttack;
}

static inline u32 GetBattlerPosition(enum BattlerId battler)
{
    return gBattlerPositions[battler];
}

static inline u32 GetBattlerAtPosition(u32 position)
{
    enum BattlerId battler;
    for (battler = 0; battler < gBattlersCount; battler++)
    {
        if (GetBattlerPosition(battler) == position)
            break;
    }
    return battler;
}

static inline u32 GetPartnerBattler(enum BattlerId battler)
{
    return GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(battler)));
}

static inline u32 GetOppositeBattler(enum BattlerId battler)
{
    return GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerPosition(battler)));
}

static inline u32 GetBattlerSide(enum BattlerId battler)
{
    return GetBattlerPosition(battler) & BIT_SIDE;
}

static inline u32 IsOnPlayerSide(enum BattlerId battler)
{
    return GetBattlerSide(battler) == B_SIDE_PLAYER;
}

static inline bool32 IsBattlerAlly(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    return GetBattlerSide(battlerAtk) == GetBattlerSide(battlerDef);
}

static inline u32 GetOpposingSideBattler(enum BattlerId battler)
{
    return GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerSide(battler)));
}

static inline struct Pokemon* GetBattlerMon(enum BattlerId battler)
{
    u32 index = gBattlerPartyIndexes[battler];
    return !IsOnPlayerSide(battler) ? &gEnemyParty[index] : &gPlayerParty[index];
}


static inline struct Pokemon *GetSideParty(u32 side)
{
    return side == B_SIDE_PLAYER ? gPlayerParty : gEnemyParty;
}

static inline struct Pokemon *GetBattlerParty(enum BattlerId battlerId)
{
    return GetSideParty(GetBattlerSide(battlerId));
}

//unsure if works, so not yet using
//compiler error so guess is wrong
//remove pointer logic for u32 maybe fine now
//if works can prob use to cleanup infatuation stuff
//idk if personality can be zero need find out
static inline u32 GetBattlerPersonality(enum BattlerId battler)
{
    u32 index = gBattlerPartyIndexes[battler];
    return !IsOnPlayerSide(battler) ? GetMonData(&gEnemyParty[index], MON_DATA_PERSONALITY) : GetMonData(&gPlayerParty[index], MON_DATA_PERSONALITY);
}

//unsure but believe can only use when is pointing or assigning value 
//based on pointing to data
//means for when assigning hard constatn value I think will have to
//write out entire value,
//need adjust make sure all values match
static inline struct PartyState *GetBattlerPartyState(enum BattlerId battler)
{
    return &gBattleStruct->partyState[GetBattlerSide(battler)][gBattlerPartyIndexes[battler]];
}

static inline bool32 InfatuatedWithBattler(enum BattlerId battler, enum BattlerId battlerInLove)
{
    if (gBattleMons[battlerInLove].volatiles.infatuatedwithMon)
        return (GetBattlerPersonality(battler) == gBattleMons[battlerInLove].volatiles.infatuatedwithMon);

    return FALSE;
}
//need setup check if mon in love with is on opposing side at all

//battler should be one with infatuation status
static inline bool32 IsMonInfatuatedWithOnOpposingSide(enum BattlerId battler)
{
    
    if (!gBattleMons[battler].volatiles.infatuatedwithMon)
        return FALSE;
    
    if (IsMonOnOpposingSide(battler, gBattleMons[battler].volatiles.infatuatedwithMon))
        return TRUE;

    return FALSE;
}

static inline bool32 IsDoubleBattle(void)
{
    return !!(gBattleTypeFlags & BATTLE_TYPE_MORE_THAN_TWO_BATTLERS);
}

static inline bool32 IsSpreadMove(u32 moveTarget)
{
    return IsDoubleBattle() && (moveTarget == TARGET_BOTH || moveTarget == TARGET_FOES_AND_ALLY);
}

static inline u32 GetChosenMoveFromPosition(enum BattlerId battler)
{
    return gBattleMons[battler].moves[gBattleStruct->chosenMovePositions[battler]];
}

//these are abilities that hit through semiinvul and skip acc check
//rename later with new understanding of what these do
//makes sense to break through ground miss
//so slight overlap w moldbreaker stuff
//really need to rename this
//isSureHitAbility maybe idk somehtiing better
static inline bool32 IsSureHitAbility(enum Ability ability)
{
    return (ability == ABILITY_NO_GUARD || ability == ABILITY_COMPASS);
}

static inline void ClearOctolockValues(enum BattlerId battler)
{
    gBattleMons[battler].volatiles.octolock = FALSE;
    gBattleMons[battler].volatiles.octolockedBy = 0;
    gBattleMons[battler].volatiles.octolockCounter = 0;
    gBattleMons[battler].volatiles.escapePrevention = FALSE;
    gBattleMons[battler].volatiles.battlerPreventingEscape = 0;
}

//wanted to replace value w max() check
//but realized value is signed type
//and would break negative values
//that said can't imagine there's a case where either
//of these functions takes a negative value
//checked w rhh techniically could change value to u32
//-1 * value causes problems since can't store well
//NOTE**( from Mgriffin -1 * value would be invalid for any u32 value greater than INT_MAX)
//so would need to pass positive to passivehpupdate
//and just multiply that by negative 1
//ok ironically while there's no reason for EE to have this signed
//I NEED it to be signed, this is the best way for me to 
//do my anti heal effect,
//hmm conversly I could just include battler ability on field check
//and do and make it skip the negative 1 hmm ok!
static inline void SetPassiveDamageAmount(enum BattlerId battler, u32 value)
{
    value = max(value, 1);
    gBattleStruct->passiveHpUpdate[battler] = value;
}

static inline void SetHealAmount(enum BattlerId battler, u32 value)
{
    value = max(value, 1);
    gBattleStruct->passiveHpUpdate[battler] = value;
    //attempt cap so do lesser of heal amount and quarter health
    if (IsAbilityOnOpposingSide(battler, ABILITY_DESPAIR))
        gBattleStruct->passiveHpUpdate[battler] = min(value, max(gBattleMons[battler].maxHP / 4, 1));
    else
        gBattleStruct->passiveHpUpdate[battler] *= -1;
}

static inline void ClearPartyStateStatusTimers(enum BattlerId battler)
{
    GetBattlerPartyState(battler)->ToxicTurnCounter = 0;
    GetBattlerPartyState(battler)->SleepTimer = 0;
}

static inline bool32 IsBattlerAtMaxHp(enum BattlerId battler)
{
    return gBattleMons[battler].hp == gBattleMons[battler].maxHP;
}

static inline bool32 IsBattlerAboveHalfHP(enum BattlerId battler)
{
    return gBattleMons[battler].hp > (gBattleMons[battler].maxHP / 2);
}

static inline bool32 DoesProtectFail(enum BattlerId battler)
{
    return (gBattleStruct->battlerState[battler].protectSuccessiveFail
    || gBattleStruct->battlerState[battler].protectTurnOrderFail);
}

static inline enum Ability AbilityPreventsRecoilDmg(enum Ability ability)
{
    //check if has ability that blocks recoil 
    //returns ability count to not trigger
    //negated abilities in IsAbilityAndRecord
    //where this is used
    //nvm above reworked IsAbilityAndRecord
    switch (ability)
    {
        case ABILITY_MAGIC_GUARD:
        case ABILITY_BONE_ARMOR:
        case ABILITY_ROCK_HEAD:
        case ABILITY_KLUTZ:
            return ability;
        break;
        default:
            return ABILITY_NONE;
        break;
    }
}

//not fully sure if want to use movepower or base move power
//don't want any plain move or prio move to proc ability
//but would like synergy with rain
//moved these here to fix include isssue
static inline u32 CanActivateGulpMissle(u32 move)
{
    return (gBattleMovePower >= 80 && GetMoveType(move) == TYPE_WATER);
}

//is meant to hold unique form condition activation
//since form change table refactor is a bit restrictive
//want a better name
static inline bool32 TryActivateUniqueFormChangeCondition(struct FormChangeContext *ctx)
{
    switch (ctx->ability)
    {
        case ABILITY_GULP_MISSILE:
            return CanActivateGulpMissle(gCurrentMove);
        break;
    }
}


static inline bool32 DoesTargetAbilityBlockCrit(enum BattlerId battlerAtk, enum BattlerId battlerDef, u32 move, enum Ability abilityDef)
{

     return (abilityDef == ABILITY_BATTLE_ARMOR
        || abilityDef == ABILITY_SHELL_ARMOR
        || (abilityDef == ABILITY_MAGMA_ARMOR && IsPhysicalMove(battlerAtk, move)) //removed physical move macro for function consolidating effects
        || abilityDef == ABILITY_INNER_FOCUS
        || abilityDef == ABILITY_REIKI
        || (abilityDef == ABILITY_TANGLED_FEET && gBattleMons[battlerDef].volatiles.confusionTurns)
        || abilityDef == ABILITY_GRASS_PELT);

}

static inline bool32 DoesTargetAbilityBlockFlinch(enum BattlerId battlerDef, enum  Ability ability)
{
    if (ability == ABILITY_REIKI
    || ability == ABILITY_INNER_FOCUS
    || (ability == ABILITY_ILLUSION
    && gBattleStruct->illusion[battlerDef].state == ILLUSION_ON))
        return TRUE;

    return FALSE;    
}


//can't  remember where I had notes for 
//new weather change but point was
//unique thing was effect can't be negated with items
//effect todo was set damp
//do psuedo haze attack drops no longer have affect
//also instead of acc drop effect because reduced vision in fog
//what will do is fog prevents redirection effects 
//well not bounce effects just prevents move redirection
//things like lightning rod
//consider also interact with some low level water based
//abilities? 
//already said its wet since works in place of damp
//considering allowing to activate water absorb
//done decide use w effects that imply moisture
//rather than direct related to rain
//redirection block would also stop rage powder 
//and follow me
static inline bool32 IsFogOnField(void)
{
    return (HasWeatherEffect() && gBattleWeather & WEATHER_FOG);
}

//consolidation of trap effects
//can use for speed drop clause
//just realized why is octolock not counter?
//other than not doing endturn dmg and not having set duration
//its effectively the same?
//hmm octo lock doesn't even do dmg at all its a status move
//so if I put here it'd be a neutral priority 
//effect that drops both attack stats in end turn
//traps foe on field indefinitely and also 
//cuts speed in half o.0
//well actually my version has definite turns now
//it lasts 4 turns and unlike others
//user must stay on field for continue effect
//quite strong but think manageable
//actually no its annoying but I think
//I need to leave octolock off this for balance
//best I could do otherwise is put in separate category
//i.e toss into ability trap category
//which is much smaller speed drop
//either way should count for ability absorb prevention
//thankfully that will be sep function so can add in there
static inline bool32 IsBattlerTrappedViaMove(enum BattlerId battler)
{
    if (gBattleMons[battler].volatiles.bind
    || gBattleMons[battler].volatiles.clamp
    || gBattleMons[battler].volatiles.swarm
    || gBattleMons[battler].volatiles.wrapped
    || gBattleMons[battler].volatiles.thundercage
    || gBattleMons[battler].volatiles.snaptrap
    || gBattleMons[battler].volatiles.firespin
    || gBattleMons[battler].volatiles.whirlpool
    || gBattleMons[battler].volatiles.sandtomb
    || gBattleMons[battler].volatiles.magmaStorm
    )
        return TRUE;

    return FALSE;
}

//could add sky drop but relatively sure 
//that should already be covered in effect
//is replacement for preocupied status macro
static inline bool32 IsBattlerHindered(enum BattlerId battler)
{
    if (gBattleMons[battler].volatiles.rechargeTimer
    || gBattleMons[battler].volatiles.confusionTurns
    || gBattleMons[battler].volatiles.bide
    || gBattleMons[battler].volatiles.switchBindtimer
    || gBattleMons[battler].volatiles.escapePrevention
    || gBattleMons[battler].volatiles.octolock
    || gBattleMons[battler].volatiles.rooted
    || gBattleMons[battler].volatiles.yawn
    || IsBattlerTrappedViaMove(battler))
        return TRUE;

    return FALSE;
}

//vsonic important
//using for print result message
//and effectiveness sound
//unsure may not need power check, may already skip
//from type calc change so wouldn't have result
//does job but won't need on update
//as EE does this better
static inline bool32 TrySkipMoveResultChecks(u16 move)
{
    return (gMovesInfo[move].power == 0
    || GetMoveEffect(move) == EFFECT_FIXED_PERCENT_DAMAGE
    || GetMoveEffect(move) == EFFECT_FIXED_HP_DAMAGE);
}

static inline bool32 IsAirborneType(enum Type type)
{
    if (type == TYPE_FLYING
    || type == TYPE_WIND)
        return TRUE;

    return FALSE;
}

//ok should now be rather than not taking dmg
//before attack goes off.
//it'll fail if you take more than a threshold of dmg
//at current level is 1/4th i.e 25% of maxhp
static inline bool32 CanFocusPunchSucceed(enum BattlerId battler)
{
    return gProtectStructs[battler].turnDmg < (gBattleMons[battler].maxHP / 4);
}

static inline bool32 IsbattlerDivergentTypeOfMove(enum BattlerId battler, enum Type moveType)
{
    if (IS_BATTLER_OF_TYPE(battler, TYPE_FLYING)
    && moveType == TYPE_WIND)
        return TRUE;

    //could work but problem with this is 
    //ground and rock aren't cut from same thing
    //fear would diminish reason to use rock
    //wind is very rare also they are better defensively
    //you'd prefer to be wind type
    //so better for flying to get the boost
    //here ground is better defensively while rock has
    //i think better offense options for its moves
    //despite its moves being worse (before) cuz acc
    //also of note there are no flying wind types but
    //there are many ground rock types
    //so this would also invalidate them
    /*if (IS_BATTLER_OF_TYPE(battler, TYPE_GROUND)
    && moveType == TYPE_ROCK)
        return TRUE;
    */

   return FALSE;
    
}

static inline bool32 DoesBattlerGetStabOnMove(enum BattlerId battler, enum Type moveType)
{
    if (IS_BATTLER_OF_TYPE(battler, moveType)
    || IsbattlerDivergentTypeOfMove(battler, moveType))
        return TRUE;

    return FALSE;
}

//unsure how pledge move work with this
//has some interaction w redirection
//first mon in combo sets target
//but second mon is responsible for actual attack
//checked bulbapedia seems sky drop is immune to redirection
//via follow me or rage powder and since no ability presently exists
//that draws in specifically flying moves that's all that could effect it
//but I feel safe in excluding it from redirection based on that
//think will make function and add as move characteristic
//with that think will remove snipe_shot effect
//as presently affect was only for redirection there
//sky drop keeps effect but still replaced in function
static inline bool32 PreventsRedirection(enum BattlerId battlerAtk, u32 move)
{
    enum Ability ability = GetBattlerAbility(battlerAtk);

    if (IsFogOnField()
    || DoesMovePreventRedirection(move)
    || IsAbilityAndRecord(battlerAtk, ability, ABILITY_PROPELLER_TAIL)
    || IsAbilityAndRecord(battlerAtk, ability, ABILITY_STALWART)
    )
        return TRUE;
    
    return FALSE;
}

static inline u32 GetCommanderType(u16 species)
{
    switch (species)
    {
    case SPECIES_TATSUGIRI_CURLY:
        return COMMANDER_TATSU_CURLY;
        break;
    case SPECIES_TATSUGIRI_DROOPY:
        return COMMANDER_TATSU_DROOPY;
        break;
    case SPECIES_TATSUGIRI_STRETCHY:
        return COMMANDER_TATSU_STRETCHY;
        break;
    case SPECIES_CHARJABUG:
        return COMMANDER_CHARJABUG;
    default:
        return COMMANDER_NONE;
        break;
    }
}

//should be fine constants included in file used in
static inline u32 GetAbilityTimer(enum Ability ability)
{
    /*switch (ability)
    {
        case ABILITY_SLOW_START:
            return SLOW_START_TIMER;
        break;
        case ABILITY_WONDER_GUARD:
            return WONDER_GUARD_TIMER; //might use 5
        break;//review effect base version of use is clear weaknesses then switch in shedinja to sweep untouchable
        //need remember what changes I made along w timer is it immune to weather and hazards?
        //consider adjust timer to what makes sense for vgc average length 
        //believe my change makes it both easier and harder to use shedinja
        //which technically is the goal, just want to make sure the value is still there
        
        case ABILITY_SPECTRE:
            return SPECTRE_TIMER;
        break; //causes memory corruption to rear its head, I give up
        //I'm gonna just swap to modern fix everything as it builds and pray to GOD 
        //I find the damned source of the issue
        //awesome fixes from building modern was able to address memory corruption
        //linked w this at least
        //still need test make sure effects still work, (believe they should)

    }*/
    return gAbilitiesInfo[ability].timer;
}

//isu32 is bigg enough to hold
//vsonic important should work long as DON'T use w dynamax hp
//may need specifically use getnondynamaxed hp function?
//found better check, from hp check in formchangetargetspecies function
static inline bool32 CheckBattlerHpThreshold(enum BattlerId battler, u8 Comparison, u8 percentHp)
{
    u32 maxHp = (gBattleMons[battler].maxHP);
    u32 currHp = (gBattleMons[battler].hp);
    // We multiply by 100 to make sure that integer division doesn't mess with the health check.
    u32 hpCheck = (currHp * 100 * 100) / maxHp;
    u32 hpThreshold = percentHp * 100;

    
    switch (Comparison)
    {
        case LESS_THAN:
            return (currHp < hpThreshold);
        break;
        case GREATER_THAN:
            return (currHp > hpThreshold);
        break;
        case EQUAL_TO:
            return (currHp == hpThreshold);
        break;
        case NOT_EQUAL:
            return (currHp != hpThreshold);
        break;
        case LESS_THAN_OR_EQUAL:
            return (currHp <= hpThreshold);
        break;
        case GREATER_THAN_OR_EQUAL:
            return (currHp >= hpThreshold);
        break;
    }

    return FALSE;
}


//missing include
static inline void SetSingleUseAbilityValues(enum BattlerId battler, enum Ability ability)
{
    gBattleStruct->partyState[GetBattlerSide(battler)][gBattlerPartyIndexes[battler]].cachedAbilityTimers = GetAbilityTimer(ability);
    gBattleStruct->partyState[GetBattlerSide(battler)][gBattlerPartyIndexes[battler]].usedSingleUseAbility = ability;
}

enum FugueStates
{
    FUGUE_FAILS,
    FUGUE_SLEEP_MODE,
    FUGUE_CONFUSION
};

//active sleep effects not yawn
//not powder sleep.
static inline u32 ShouldActivateFugue(enum BattlerId battleratk, enum BattlerId battlerdef, enum Ability abilityAtk, enum Move move)
{
    if (battleratk == battlerdef)
        return FALSE;

    //intention has fugue, sleep effect logic, or confuse effect logic
    //sleep is meant to exclude things like yawn and powder
    //to specifically be hypnosis effects
    if (IsBattlerAlive(battleratk) && abilityAtk == ABILITY_FUGUE)
    {
        if (GetMoveEffect(move) == EFFECT_NON_VOLATILE_STATUS
        && GetMoveNonVolatileStatus(move) == MOVE_EFFECT_SLEEP
        && !IsPowderMove(move))
            return FUGUE_SLEEP_MODE;

        else if (GetMoveEffect(move) == EFFECT_CONFUSE
        || GetMoveAdditionalEffectById(move, 0)->moveEffect == MOVE_EFFECT_CONFUSION
        || GetMoveAdditionalEffectById(move, 1)->moveEffect == MOVE_EFFECT_CONFUSION)
            return FUGUE_CONFUSION;
    }
    

    return FALSE;
}

//attempt simplify readability as won't different version for diff places
static inline bool32 FugueActivatesSleep(enum BattlerId battleratk, enum BattlerId battlerdef, enum Ability abilityAtk, enum Move move)
{
    return ShouldActivateFugue(battleratk, battlerdef, abilityAtk, move) == FUGUE_SLEEP_MODE;
}

static inline bool32 FugueCausesConfusion(enum BattlerId battleratk, enum BattlerId battlerdef, enum Ability abilityAtk, enum Move move)
{
    return ShouldActivateFugue(battleratk, battlerdef, abilityAtk, move) == FUGUE_CONFUSION;
}

//note believe should add assert later
//to catch use of abilities that aren't hp dependent
//made rework order
//using getbattler for ability would return false posiitve
//on assert if suppressed so better to use flat battler ability
//then don't return hp check
//can instaed use that as bool condition
//to return getbattlerability != none
static inline bool32 CanActivateHpBasedAbility(enum BattlerId battler)
{
    enum Ability ability = gBattleMons[battler].ability;
    u8 comparisonOperator = gAbilitiesInfo[ability].basedOnHp.comparison;
    u8 percent = gAbilitiesInfo[ability].basedOnHp.percentHp;

    if (CheckBattlerHpThreshold(battler, comparisonOperator, percent))
       return GetBattlerAbility(battler) != ABILITY_NONE;

    return FALSE;
}
//ok fog already blocks redirection from above
//with far more reliable exclusions
//don't want/need too many blocks here
//think just want to cut down preoccupied status
//think lock to confusion wrap and bide
//think will leave status 1 as main block
//will leave lightning rod with advantage still
//which is good, if paralysis is main status to set
//it'll mostly be excluded for lightning rod mon
static inline bool32 CanBattlerAbilityDrawInMove(enum BattlerId battlerDef)
{
    if (gBattleMons[battlerDef].status1 == 0 
    && !IsBattlerHindered(battlerDef))
        return TRUE;
    
    return FALSE;
}

enum BattleTypes
{
    PRIMARY_TYPE,
    SECONDARY_TYPE,
    AUXILIARY_TYPE,
    NUM_BATTLE_TYPES,
};

static inline enum Type GetBattlerTypebySlot(enum BattlerId battler, enum BattleTypes typeId)
{
    switch (typeId)
    {
        case PRIMARY_TYPE:
            return gBattleMons[battler].type1;
        break;
        case SECONDARY_TYPE:
            return gBattleMons[battler].type2;
        break;
        case AUXILIARY_TYPE:
            return gBattleMons[battler].type3;
        break;
    }
}

static inline void SetBattlerTypebySlot(enum BattlerId battler, enum BattleTypes typeId, enum Type typeAssigned)
{
    switch (typeId)
    {
        case PRIMARY_TYPE:
            gBattleMons[battler].type1 = typeAssigned;
        break;
        case SECONDARY_TYPE:
            gBattleMons[battler].type2 = typeAssigned;
        break;
        case AUXILIARY_TYPE:
            gBattleMons[battler].type3 = typeAssigned;
        break;
    }
}

static inline enum Type GetBattlerPrimaryType(enum BattlerId battler)
{
    return GetBattlerTypebySlot(battler, PRIMARY_TYPE);   
}

static inline enum Type GetBattlerSecondaryType(enum BattlerId battler)
{
    return GetBattlerTypebySlot(battler, SECONDARY_TYPE);   
}

static inline enum Type GetBattlerAuxiliaryType(enum BattlerId battler)
{
    return GetBattlerTypebySlot(battler, AUXILIARY_TYPE);   
}

#endif // GUARD_BATTLE_H
