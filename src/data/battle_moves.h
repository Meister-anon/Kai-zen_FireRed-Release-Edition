#include "constants/battle_script_commands.h"
#include "constants/battle.h"
#include "battle_string_ids.h"
//EE uses .battleAnimScript = gBattleAnimMove_Struggle,
//instead I want to set pointer table
//mine will be .battleAnimScriptId
//I'l just set a move id to the field
//and it'll be the move animation I want the move to use
//simple if I want to make simple placeholder effects ex copy slash
//I'll make a function to get move animation
//and i'll use the animId with the pointer table to direct to the anim
//rn animations all use same name just in Lowercase for move
//ex. MOVE_NONE  anim is Move_NONE
//shouldn't be too hard to use python to make a file for the table
//just take argument from moves constant file
//moveId is moves as is,  move anims will
//split moveid apart after MOVE use title command on it 
//to make it Move  then just put it back together
//and add that to move anim array
//after its all printed then I just need to do a control h
//to rename all the moveanim to the new emerald naming convention
//simply replace Move w gBattleAnimMove
//then in this file just loop it take move id in brackets
// and add it on at bottom of file
//so replace line },  w .battleAnimScriptId = MOVE_ID  \n},
//pretty much

/*plan rework move flag files and struct
to match EE and setup new flag 
to synergize with floating effect
where rather than ground type
its based on move flag
of not being able to hit floating targets

believe can simplify transition
by making git diff with EE move_info file
and then using that "patch" in a git apply
to this file.

should allow to run like merge conflicts
making much easier to add effects.
Still mostly tedious but much better
following that think may merge with move info file
so can have descriptions etc. all in one place
or move them to move description file
and then just include it here? hmmm

uhh can't merge make diff like I wanted 
will need to use python instead make moves list from names here,
take what I need from moves_info and apply changes here
do like did tm list data file

use   const struct BattleMove gBattleMoves[MOVES_COUNT] =
as the start point

when name matches start adding data
for everything below .category from other file
that will add contest stuff

        .contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Frustration,
        .validApprenticeMove = TRUE,

think can use regex for final pass to clear those lines out after the fact
think may keep battleanim stuff just comment it out for later update

*/

const struct BattleMove gBattleMoves[MOVES_COUNT] =
{
    [MOVE_NONE] =
    {
        .effect = EFFECT_HIT, //put here just so would compile, ie has a place where define is used
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .sketchBanned = TRUE,
        .assistBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_None,
    },

    [MOVE_POUND] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_POUND,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Pound,
    },

    [MOVE_KARATE_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_KarateChop,
    },

    [MOVE_DOUBLE_SLAP] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_POUND},
        //.battleAnimScript = gBattleAnimMove_DoubleSlap,
    },

    [MOVE_COMET_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 21,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CometPunch,
    }, //gave priority

    [MOVE_MEGA_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_MegaPunch,
    },

    [MOVE_PAY_DAY] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PayDay,
    },

    [MOVE_FIRE_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_FIRE_PUNCH,
        //.contestComboMoves = {COMBO_STARTER_ICE_PUNCH, COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_THUNDER_PUNCH},
        //.battleAnimScript = gBattleAnimMove_FirePunch,
    },

    [MOVE_ICE_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_ICE_PUNCH,
        //.contestComboMoves = {COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_THUNDER_PUNCH},
        //.battleAnimScript = gBattleAnimMove_IcePunch,
    },

    [MOVE_THUNDER_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_THUNDER_PUNCH,
        //.contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_ICE_PUNCH},
        //.battleAnimScript = gBattleAnimMove_ThunderPunch,
    },

    [MOVE_SCRATCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SCRATCH,
        //.contestComboMoves = {COMBO_STARTER_LEER},
        //.battleAnimScript = gBattleAnimMove_Scratch,
    },

    [MOVE_VICE_GRIP] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
    },

    [MOVE_GUILLOTINE] =
    {
        .effect = EFFECT_OHKO,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 30, //change these back - was base 30, made 50 reset back to 40  / may make 35 test later
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = -5,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        //.battleAnimScript = gBattleAnimMove_Guillotine,
    },

    [MOVE_RAZOR_WIND] =
    {
        .effect = EFFECT_TWO_TYPED_MOVE,
        .power = 80,
        .type = TYPE_NORMAL, //since joat change, this doesn't do much other than just giving stab since move is mostly for normal types
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .windMove = TRUE,
        .slicingMove = TRUE,
        .enhancedCritrate = TRUE,
        .damagesAirborneDoubleDamage = TRUE,
        .argument = { .storedValue = TYPE_FLYING },
       .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNWHIPPEDWHIRLWIND },
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RazorWind,
    },
    //think will give to more flying types
    //ok new schema for two typed moves
    //they offer two opportunities to gain stab
    //and while can be redirected they
    //bypass absorb affects to still do damage
    //without giving the benefit of the ability

    //ok with that in mind I SHOULD still keep the idea
    //that absorb abilities should read from both main type or 2nd type
    //to attempt absorption

    [MOVE_SWORDS_DANCE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 20,
        #else
            .pp = 30,
        #endif
        .effect = EFFECT_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_SWORDS_DANCE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SwordsDance,
    },

    [MOVE_CUT] =
    {
        .effect = EFFECT_TARGET_TYPE_DAMAGE,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_Cut,
        .argument = {
        .storedValue = TYPE_GRASS,
        .damagePercentage = 300}, //power x multiplier / 10 basically is just times 3...
    }, //make effect easy to adjust, change command  to read type to effct from argument, and dmg multiplier from gbattlemovedmg * argumetn chance/ 10
    //ok hopefully this works vsonic
    //if I instead change to 300 I think I can use PercentToUQ4_12 function to make it 3.0
    //and can just do multiply power x percent

    [MOVE_GUST] =
    {
        .effect = EFFECT_HIT,  //does nothing just goes to hit, can change to hit
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborneDoubleDamage = TRUE,
        .windMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Gust,
    }, //blunt wind damage

    [MOVE_WING_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WingAttack,
    },
    //turn into precision attack

    [MOVE_WHIRLWIND] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 0,
            #elif B_UPDATED_MOVE_DATA == GEN_5
            .accuracy = 100,
            #else
            .accuracy = 100,
            #endif
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .split = SPLIT_STATUS,
        .windMove = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Whirlwind,
    },
    //these effects seem worthless, but are exactly what you wish
    //you had when an enemy gets stat buffed on you.
    //but are kinda still near worthless since you have to wait for
    //them to attack you and prey you survive a hit to get this off.
    //so with addition of non repeat move effects
    //like blood moon blast and gigaton hammer
    //what if rather than negative priority 
    //I just make the switch effects neutral
    //but unable to be spammed each turn. that should fix them
    //I imagine.
    //talked w alex and mgriffin and its still too good of an effect
    //especially in vgc without negative priority it speeds up battles
    //and allows switching things into damage without anyway to protect them
    //this and other effects will just have to be good
    //based on existence of guard mode, you could more easily survive
    //to get the effect off.

    [MOVE_FLY] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 80,
        #else
            .power = 70,
        #endif
        .effect = EFFECT_FLY, //think will just make effect fly that goes to semi invul
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNFLEWHIGH, .status = STATE_ON_AIR },
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Fly,
    },
    //if take time to aim decide to add high crit
    //with other effects can make bp 80 to be on line with other effects
    //think add x_bell idea skips executes in single turn
    //in tail wind?
    //I think two turn effects aren't actually as bad as people are making them
    //out to be.
    //long as you're faster you dodge an attack so its effectively protect
    //without fail chance.
    //and people say its invalidated by just protecting, or switching to a resist
    //but not every mon has protect, or would even want to use a protet then
    //forcing a protect is still useful imo
    //and dependign on type a resist might not even be available
    //and again that's still giving up tempo
    //plus in doubles any counter would hinge on properly
    //predicting the intended target
    //since effect is more beneficial when faster
    //should I just give all semi invul effects priority? 
    //negatives would still be there, but it'd be easier
    //to get something out of the move at least.
    //something of a tempo stealer
    //to avoid stall would lower pp of moves to 5 or so.
    //reivalluating this most mon that get it are fast
    //I've added a way for it to attack in same turn
    //and it also has high crit now
    //I feel this may be strong enough to not need
    //boost to priority? 
    //would potentially drop pp to 10 to accomodate
    //gave to more slower mon so screw it
    //will make this the quintissential flying move
    //it'll underscore what the type is about
    //speed utility versatility
    //remembered I setup semi invul interupt effect
    //so think this should be balanced at 10 pp

    

    [MOVE_BIND] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .accuracy = 90,
        #else
            .accuracy = 75,
        #endif
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_NORMAL,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_BIND,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        //.battleAnimScript = gBattleAnimMove_Bind,
    }, //idae from bug, but making this do encore so attack and enemy cant change moves while trapped

    [MOVE_SLAM] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_POUND},
        //.battleAnimScript = gBattleAnimMove_Slam,
    },//think will turn this into upgrade of tackle keep 95 acc
    //equiv beam move now separate from body slam
    //vsonic important 15 bp inrease so coulda kinda stay where it is in movesets
    //but is far more accurate now which is more fitting for mid to late move
    //adjust learnsets for below 20-25 raise up 5-7 levels

    [MOVE_VINE_WHIP] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 45,
            .pp = 25,
        #elif B_UPDATED_MOVE_DATA == GEN_4 || B_UPDATED_MOVE_DATA == GEN_5
            .power = 35,
            .pp = 15,
        #else
            .power = 35,
            .pp = 10,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_VineWhip,
    },//leafage pretty much takes teh job of his,
    //but can make unique if I change it to a flinch hit?
    //believe would be pretty much only grass move that has that effect

    [MOVE_STOMP] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        .kickingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_LEER},
        //.battleAnimScript = gBattleAnimMove_Stomp,
    },

    [MOVE_DOUBLE_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DoubleKick,
    },

    [MOVE_MEGA_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 85, //idk what I was thinking with this,  mega punch is 80 power w 85 acc  base 90 for this is crazy
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_MegaKick,
    },

    [MOVE_JUMP_KICK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 100,
            .pp = 10,
        #elif B_UPDATED_MOVE_DATA == GEN_4
            .power = 85,
            .pp = 25,
        #else
            .power = 70,
            .pp = 25,
        #endif
        .effect = EFFECT_RECOIL_IF_MISS,    //BattleScript_EffectRecoilIfMiss
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .recoilMove = TRUE,
        .gravityBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_JumpKick,
    },

    [MOVE_ROLLING_KICK] =
    {

        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RollingKick,
    },
    //think move isn't bad but barely any mon get it
    //machop only by breeding,
    //hitmonlee and hitmontop, who historically are slow
    //and marshadow, the only mon that can actually use it well...

    [MOVE_SAND_ATTACK] =
    {
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_SAND_ATTACK,
        //.contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM},
        //.battleAnimScript = gBattleAnimMove_SandAttack,
    },

    [MOVE_HEADBUTT] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .headbuttMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_Headbutt,
    },

    [MOVE_HORN_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .headbuttMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_HORN_ATTACK,
        //.contestComboMoves = {COMBO_STARTER_LEER},
        //.battleAnimScript = gBattleAnimMove_HornAttack,
    },

    [MOVE_FURY_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .headbuttMove = TRUE,
        .enhancedCritrate = TRUE,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HORN_ATTACK, COMBO_STARTER_PECK},
        //.battleAnimScript = gBattleAnimMove_FuryAttack,
    },//since hit is with horn or beak i.e head

    [MOVE_HORN_DRILL] =
    {
        .effect = EFFECT_OHKO,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = -5,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HORN_ATTACK},
        //.battleAnimScript = gBattleAnimMove_HornDrill,
    },

    [MOVE_TACKLE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .power = 40,
            .accuracy = 95,
        #elif B_UPDATED_MOVE_DATA == GEN_5 || B_UPDATED_MOVE_DATA == GEN_6
            .power = 50,
            .accuracy = 100,
        #else
            .power = 35,
            .accuracy = 95,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_NORMAL,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN, COMBO_STARTER_LEER},
        //.battleAnimScript = gBattleAnimMove_Tackle,
    },

    [MOVE_BODY_SLAM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            #else
            #endif
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BodySlam,
    },

    [MOVE_WRAP] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .accuracy = 90, //need decide if new wrapping moves (ones w base 15 power) should be base 85 or 90 accuracy
        #else   //will make base 90 thse are setup moves really useless if they miss
            .accuracy = 85,
        #endif
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_NORMAL,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_WRAP,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Wrap,
    },

    [MOVE_TAKE_DOWN] =
    {
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_LIGHT_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        //.battleAnimScript = gBattleAnimMove_TakeDown,
    },

    [MOVE_THRASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 120,
            .pp = 10,
        #else
            .power = 90,
            .pp = 20,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAGE},
        //.battleAnimScript = gBattleAnimMove_Thrash,
    },

    [MOVE_DOUBLE_EDGE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_MED_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        //.battleAnimScript = gBattleAnimMove_DoubleEdge,
    },

    [MOVE_TAIL_WHIP] =
    {
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARM},
        //.battleAnimScript = gBattleAnimMove_TailWhip,
    },

    [MOVE_POISON_STING] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PoisonSting,
    },

    [MOVE_TWINEEDLE] =
    {
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Twineedle,
    },

    [MOVE_PIN_MISSILE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 25,
            .accuracy = 95,
        #else
            .power = 14,
            .accuracy = 85,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_BUG,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PinMissile,
    },

    [MOVE_LEER] =
    {
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_LEER,
        //.contestComboMoves = {COMBO_STARTER_RAGE, COMBO_STARTER_SCARY_FACE},
        //.battleAnimScript = gBattleAnimMove_Leer,
    },

    [MOVE_BITE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_SCARY_FACE},
        //.battleAnimScript = gBattleAnimMove_Bite,
    },

    [MOVE_GROWL] =
    {
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARM},
        //.battleAnimScript = gBattleAnimMove_Growl,
    },

    [MOVE_ROAR] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 0,
            #elif B_UPDATED_MOVE_DATA == GEN_5
            .accuracy = 100,
            #else
            .accuracy = 100,
            #endif
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_SOUND,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Roar,
    }, //cacophony boost could make this do dmage percent hp
    //may do like prankster make field cacophony boosted

    [MOVE_SING] =
    {
        .effect = EFFECT_NON_VOLATILE_STATUS, //giving effects that immobalize priority are too broken
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //since this keeps opponent from attacking will keep base priority / also because of high accuracy and good distributnion
        .split = SPLIT_STATUS,
       .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_SING,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Sing,
    },//accuracy buff based on anime logic, and raririty
    //part of me things this should be side target i.e both 
    //since sing in lore puts everyone to sleep, but with that 
    //all sleep effects outside of hypnosis 
    //and even all powder effects should work the same way
    //which would just be overpowering

    [MOVE_SUPERSONIC] =
    {
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 75,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Supersonic,
    },

    //BREAK
    [MOVE_SONIC_SCREECH] =
    {
        .effect = EFFECT_FIXED_HP_DAMAGE,
        .power = 1, //idk why I did this makes it typless think shouldn't do that just cuz its fixed
        .type = TYPE_SOUND,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .multiTaskBanned = TRUE,
        .argument = { .fixedDamage = 20 },
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SonicBoom,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),*/
    },//previously sonic boom / idk but doesn't seem to be setting confuse effect?
    //cacophony boost  increase effect chance as well as infiltrate

    [MOVE_DISABLE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .accuracy = 85,
            #elif B_UPDATED_MOVE_DATA == GEN_4
            .accuracy = 80,
            #else
            .accuracy = 55,
            #endif
        .effect = EFFECT_DISABLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Disable,
    },

    [MOVE_ACID] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
            /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Acid,
    },

    [MOVE_EMBER] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_Ember,
    },

    [MOVE_FLAMETHROWER] =
    {

        .power = 95,
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_Flamethrower,
    },//Think flamethrower is too common to be a knock down move, then again good for boosting fire type back up?

    [MOVE_MIST] =
    {
        .effect = EFFECT_MIST,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Mist,
    },

    [MOVE_WATER_GUN] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_WATER_SPORT},
        //.battleAnimScript = gBattleAnimMove_WaterGun,
    },

    [MOVE_HYDRO_PUMP] =
    {
        .power = 120,
        .effect = EFFECT_HIT,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_HydroPump,
    },

    [MOVE_SURF] =
    {
        .power = 95,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .effect = EFFECT_HIT,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesUnderwater = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_SURF,
        //.contestComboMoves = {COMBO_STARTER_DIVE, COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Surf,
    },//revert for balance
    //realize otherwise everyone just clicks surf

    [MOVE_ICE_BEAM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 95,
        #else
            .power = 95,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            // The following effect is also relevant in battle_Pike.c
            // If you cherry-pick this to use something other than the config, make sure to update it there too
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_IceBeam,
    },//yeah no, idk wtf I was thinking, not giving ice a flying knock outside of blizzard

    [MOVE_BLIZZARD] =
    {
        .power = 110,
        .effect = EFFECT_HIT, //drop power same reason thunder can be sure hit
        .type = TYPE_ICE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .damagesAirborne = TRUE,
        .alwaysHitsInHailSnow = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_POWDER_SNOW},
        //.battleAnimScript = gBattleAnimMove_Blizzard,
    },

    [MOVE_PSYBEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_Psybeam,
    },

    [MOVE_BUBBLE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_BubbleBeam,
    },

    [MOVE_AURORA_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_AuroraBeam,
    },

    [MOVE_HYPER_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HyperBeam,
    },

    [MOVE_PECK] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_PECK,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Peck,
    },

    [MOVE_DRILL_PECK] =
    {
        .effect = EFFECT_BRICK_BREAK,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_PECK},
        //.battleAnimScript = gBattleAnimMove_DrillPeck,
    },
    //saw comment on rigamarolled vid I like make drill peck break screens
    //drill enemy weak spot

    [MOVE_SUBMISSION] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 5,    //lowered pp for higher distribution
        #else
            .pp = 25,
        #endif
        .effect = EFFECT_SUBMISSION, //should break walls & protect
        .power = 80, //^prob eventually switch to brick_break
        .type = TYPE_FIGHTING,//ok think only reason not using brick break effect
        .accuracy = 90, //is wanted specific print string,used for both raging bull too when breaking protect
        .target = MOVE_TARGET_SELECTED,//so this could prob use brick break only raging bull would need its own effect
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_LIGHT_RECOIL,
                .self = TRUE,
            }),*/ //vsonic adjust down as needed
        .recoilMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_Submission,
    },
    //was at some point strongest fighting move, think will change to ultimate fighting technique
    //does recoil but breaks through protect essentially same effect as raging bull
    //recoil works off effect only? so don't think can do raging bull & recoil?
    //done just needed its own effect
    //changed ignoresproetect means it fully bypasses protect
    //can just do effect brick break then
    //changed back since plan was increase distribution
    //change to hit protect like and do low recoil rather than mid
    //for the most part thing leftovers should cover effect

    [MOVE_LOW_KICK] =
    {
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LowKick,
    },

    [MOVE_COUNTER] =
    {

        .effect = EFFECT_COUNTER,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TAUNT},
        //.battleAnimScript = gBattleAnimMove_Counter,
    },

    [MOVE_SEISMIC_TOSS] =
    {
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        //.battleAnimScript = gBattleAnimMove_SeismicToss,
    },

    [MOVE_STRENGTH] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .setfromatkcanceler = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Strength,
    },

    [MOVE_ABSORB] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 25,
        #else
            .pp = 20,
        #endif
        .effect = EFFECT_ABSORB,
        .power = 30,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_Absorb,
    },

    [MOVE_MEGA_DRAIN] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 15,
        #else
            .pp = 10,
        #endif
        .effect = EFFECT_ABSORB,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_MegaDrain,
    },

    [MOVE_LEECH_SEED] =
    {
        .effect = EFFECT_LEECH_SEED,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_LEECH_SEED,
        //.contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_WORRY_SEED},
        //.battleAnimScript = gBattleAnimMove_LeechSeed,
    },

    [MOVE_GROWTH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 20,
        #else
            .pp = 40,
        #endif
        .effect = EFFECT_GROWTH, //doubles stat boost in sun
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_GROWTH,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Growth,
    },

    [MOVE_RAZOR_LEAF] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .slicingMove = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_RazorLeaf,
    },

    [MOVE_SOLAR_BEAM] =
    {
        .effect = EFFECT_SOLAR_BEAM,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .multiTaskBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
       .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNTOOKSUNLIGHT, .status = WEATHER_SUN_ANY },
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_SolarBeam,
    },

    [MOVE_POISON_POWDER] =
    {
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 75,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
       .argument = { .nonVolatileStatus = MOVE_EFFECT_POISON },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        //.battleAnimScript = gBattleAnimMove_PoisonPowder,
    },

    [MOVE_STUN_SPORE] =
    {
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        .powderMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        //.battleAnimScript = gBattleAnimMove_StunSpore,
    },

    [MOVE_SLEEP_POWDER] =
    {
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //since this keeps opponent from attacking will keep base priority//allow priority on this because accuracy is low
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        //.battleAnimScript = gBattleAnimMove_SleepPowder,
    },

    [MOVE_PETAL_DANCE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 120,
            .pp = 10,
        #elif B_UPDATED_MOVE_DATA == GEN_4
            .power = 90,
            .pp = 20,
        #else
            .power = 70,
            .pp = 20,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .makesContact = TRUE,
        .danceMove = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_PetalDance,
    },

    [MOVE_STRING_SHOT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .effect = EFFECT_SPEED_DOWN_2,
        #else
            .effect = EFFECT_SPEED_DOWN,
        #endif
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_STRING_SHOT,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StringShot,
    },

    [MOVE_DRAGON_RAGE] =
    {
        .effect = EFFECT_FIXED_HP_DAMAGE,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .multiTaskBanned = TRUE,
        .argument = { .fixedDamage = 40 },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DRAGON_RAGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_DRAGON_RAGE,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        //.battleAnimScript = gBattleAnimMove_DragonRage,
    },
    //new idea potentially turn dragon rage
    //into special class of fixation effect
    //that does rage like effect
    //but only works for dragon moves? 
    //each hit taken increases counter up to max 5
    //will do damage formula of 100 + counter * 10
    //divided by 100. so maxes 150
    //think should be good, won't break early game
    //or really affect it at all
    //but offers options for certain mon 
    //especially redidrago

    [MOVE_FIRE_SPIN] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 30,
            .accuracy = 90,
        #else
            .power = 15,
            .accuracy = 70,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_FIRE_SPIN,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_FireSpin,
    },

    [MOVE_THUNDER_SHOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_ThunderShock,
    },

    [MOVE_THUNDERBOLT] =
    {

        .power = 95,
        .effect = EFFECT_HIT,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_Thunderbolt,
    },
    //used many times to hit flying enemies guess can give hits flying?
    //if I give a good variety of moves this effect its good for ground types
    //as it gives them more options but it also invalidates the new mechanic for flying types?
    //idk maybe its fine if I"m gonna add a mnew mechanic good idea
    //to have at least a few of said mechanic/category for each type

    [MOVE_THUNDER_WAVE] =
    {

        .accuracy = 90,
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_ThunderWave,
    },

    [MOVE_THUNDER] =
    {
        .power = 110,
        .effect = EFFECT_HIT, //sets paralysis can move to argument nvm did with flag can leave as is
        .type = TYPE_ELECTRIC,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborneDoubleDamage = TRUE,
        .alwaysHitsInRain = TRUE,
        .accuracy50InSun = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_LOCK_ON, COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Thunder,
    },
    //since has conditional perfect acc makes sense to drop power some

    [MOVE_ROCK_THROW] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .damagesAirborneDoubleDamage = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_ROCK_THROW,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RockThrow,
    },  //now that can hit in air, may give to more fighting types; 
    ////also since its not easy to hit flying target change accuraacy against in air targets
    //don't like that as a standard, just slightly lowered Accuracy instead, since making standardized effect

    [MOVE_EARTHQUAKE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GROUND, //issue was the battlescript for earthquake outdated using unique bs when it shoud just go to hit, like surf smh
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY, //MOVE_TARGET_BOTH, think want to keep broad target for this
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_EARTHQUAKE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Earthquake,
    },//remove target foes adn ally, from most things as it doesn't make sense, keep for explosion etc.

    [MOVE_FISSURE] =
    {
        .effect = EFFECT_OHKO,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = -5,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_EARTHQUAKE},
        //.battleAnimScript = gBattleAnimMove_Fissure,
    },

    [MOVE_DIG] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 80,
        #else
            .power = 60,
        #endif
        .effect = EFFECT_SEMI_INVULNERABLE,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .cantdamageFloating = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNDUGHOLE, .status = STATE_UNDERGROUND },
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Dig,
    },//if current move make grounded
    //since have to deal with floating immunity
    //think will let dig be only move to keep full pp

    [MOVE_TOXIC] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .accuracy = 90,
        #else
            .accuracy = 85,
        #endif
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_POISON,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_TOXIC },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_TOXIC,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Toxic,
    },

    [MOVE_CONFUSION] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_CONFUSION,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        //.battleAnimScript = gBattleAnimMove_Confusion,
    },

    [MOVE_PSYCHIC] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_PSYCHIC,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_CONFUSION, COMBO_STARTER_KINESIS},
        //.battleAnimScript = gBattleAnimMove_Psychic,
    },

    [MOVE_HYPNOSIS] =
    {
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 75,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //since this keeps opponent from attacking will keep base priority//since acc is lower will try give priority,
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_HYPNOSIS,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Hypnosis,
    },//unsure if acc is too high
    //with lack of type immunity and compound eyes
    //acc boost items in mind
    //vsonic - dropped to sleep powder range

    [MOVE_MEDITATE] =
    {
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_Meditate,
    },

    [MOVE_AGILITY] =
    {
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        //.battleAnimScript = gBattleAnimMove_Agility,
    },

    [MOVE_QUICK_ATTACK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        //.battleAnimScript = gBattleAnimMove_QuickAttack,
    },

    [MOVE_RAGE] =
    {
        .effect = EFFECT_RAGE, //new effect instead boost attack raise move power for rage each boost, formula gbattlemovepower = power + (10 * rage counter)
        .power = 25,    //assume hit each turn and use each turn after first use, move gains 20 power each turn
        .type = TYPE_MYSTERY, //Its power of anger type of attack would depend on mon type etc. so doesn't really make sense to be normal
        .accuracy = 100, //ok got it fixed, setup dynamictype so move type will match mon's type 1, rather than just being normal /think done had rearrange type order for mon that were normal
        .pp = 13,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_RAGE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Rage,
    },//I feel like this could be a good tm?
    //boosts atk when hit
    //boosts power when use move

    [MOVE_TELEPORT] =
    {
        .effect = EFFECT_TELEPORT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = -6,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CONFUSION, COMBO_STARTER_DOUBLE_TEAM, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        //.battleAnimScript = gBattleAnimMove_Teleport,
    }, //fully updated to modern effect
    //consider make neutral priority so more psychic types
    //can use effect slow mon wouldn't be affected
    //except case of intentinonally using neg priority moves
    //which presently aren't used outside of force switch effects?
    //only difference for fast mon hard switching
    //is being able to avoid pursuit
    //which being psychic is the entire point
    //not a big deal in official play because
    //pursuit is no longer in the game

    [MOVE_NIGHT_SHADE] =
    {
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NightShade,
    },

    [MOVE_MIMIC] =
    {
        .effect = EFFECT_MIMIC,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Mimic,
    },//keep effect of lasting til end of battle not modern effect to last only until switch

    [MOVE_SCREECH] =
    {
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 95,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Screech,
    },

    [MOVE_DOUBLE_TEAM] =
    {
        .effect = EFFECT_EVASION_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_DOUBLE_TEAM,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DoubleTeam,
    },

    [MOVE_RECOVER] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 10,
        #else
            .pp = 20,
        #endif
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 1, //allowing this as  counter balance for dropped healing
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Recover,
    },

    [MOVE_HARDEN] =
    {
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_HARDEN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Harden,
    },

    [MOVE_MINIMIZE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 10,
        #else
            .pp = 20,
        #endif
        .effect = EFFECT_MINIMIZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Minimize,
    },

    [MOVE_SMOKESCREEN] =
    {
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SMOG},
        //.battleAnimScript = gBattleAnimMove_Smokescreen,
    },

    [MOVE_CONFUSE_RAY] =
    {
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ConfuseRay,
    },

    [MOVE_WITHDRAW] =
    {
        .effect = EFFECT_WITHDRAW,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Withdraw,
    },//reduced pp to 25 for new effects w pp max
    //can get original pp

    [MOVE_DEFENSE_CURL] =
    {
        .effect = EFFECT_DEFENSE_CURL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_DEFENSE_CURL,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DefenseCurl,
    },

    [MOVE_BARRIER] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 20,
        #else
            .pp = 30,
        #endif
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Barrier,
    },

    [MOVE_LIGHT_SCREEN] =
    {
        .effect = EFFECT_LIGHT_SCREEN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_LightScreen,
    },

    [MOVE_HAZE] =
    {
        .effect = EFFECT_HAZE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0, //since  so strong will keep as is, vsonic important
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_Haze,
    },//black fog, setup but never put command in sript, now is in need test ...breaks game
    //fixed, full effect isn't working. , for now commented out mist command

    [MOVE_REFLECT] =
    {
        .effect = EFFECT_REFLECT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_Reflect,
    },

    [MOVE_FOCUS_ENERGY] =
    {
        .effect = EFFECT_FOCUS_ENERGY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .status = VOLATILE_FOCUS_ENERGY },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_FOCUS_ENERGY,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FocusEnergy,
    },

    [MOVE_BIDE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .accuracy = 0,
            .priority = 1,
        #else
            .accuracy = 100,
            .priority = 0,
        #endif
        .effect = EFFECT_BIDE,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Bide,
    },// made typeless dmg, and buffed revenge damage priority & slight damage buff to account for loss of stab

    [MOVE_METRONOME] =
    {
        .effect = EFFECT_METRONOME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 1, //same logic as assist
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Metronome,
    },

    [MOVE_MIRROR_MOVE] =
    {
        .effect = EFFECT_MIRROR_MOVE,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS, //MOVE_TARGET_SELECTED
        .priority = 3, //think will give priority so can get accurate move easier?
        .split = SPLIT_STATUS,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MirrorMove,
    }, //idea birds ability to parrot/copy, move kinda sucks , but is a bit better with my normal type change, as would always get psudo stab if mon is normal
    //speaking just for spearow/fearow rn
     //plan replace mirror move until switched out fainted or battle ends
    

    [MOVE_SELF_DESTRUCT] =
    {
        .effect = EFFECT_MIND_BLOWN,
        .power = 140,// 200,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
        .multiTaskBanned = TRUE,
        .dampBanned = TRUE,
        .ballisticMove = TRUE,
        .explosiveMove = TRUE,
        .argument = { .sacrificedHpPercentage = 50 },
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SelfDestruct,
    },//will drop power since added back defense fall,
    //but keep above misty explosion as is normal type
    //hmm couple put self destruct at 140, below hyper beams
    //but since it cuts defense its actually twice as strong?
    //to differentiate from explosion
    //think make this drop hp by half so can survive
    //hmm but this is essentially what mindblown already does
    //but that move sucks, well its bad prob cuz it doesn't have
    //the def cut
    //base power in gen 1 was 130, buffed keeping at 140,
    //cuz normal and to attempt stand out from other effects
    //well since you no longer have to die for it, 
    //is prob still worth at 130
    //but will drop the typed variants to base 100
    //as they are able to hit super effectively
    //change mind blown to sacrifice 50% max hp 
    //to attempt blow everyone 
    //the change of needing to survive the hp drop to 
    //get the effect off is prob most important point of balance
    //for this...
    //other variants max out at 465 power but requires
    //significant setup

    [MOVE_EGG_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SOFT_BOILED},
        //.battleAnimScript = gBattleAnimMove_EggBomb,
    },

    [MOVE_AURORA_VEIL] =
    {
        .effect = EFFECT_AURORA_VEIL,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_AuroraVeil,
    },//should I set this back to prio 0?
    //I feel like I should it requires hail/snow setting
    //but multiple mon can do so with snowarning
    //this being prio allows veil to be able tobe setup
    //if a pair has the move effects required between them
    //aighgt think I'll leave it
    //default only about a quarter of mon that get this move
    //have snow warning

    [MOVE_SMOG] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 35,
        #else
            .power = 20,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_POISON,
        .accuracy = 80,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 40,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SMOG,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Smog,
    },

    [MOVE_SLUDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SLUDGE,
        //.contestComboMoves = {COMBO_STARTER_SLUDGE_BOMB},
        //.battleAnimScript = gBattleAnimMove_Sludge,
    },

    [MOVE_BONE_CLUB] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_BONE_CLUB,
        //.contestComboMoves = {COMBO_STARTER_BONEMERANG, COMBO_STARTER_BONE_RUSH, COMBO_STARTER_SHADOW_BONE},
        //.battleAnimScript = gBattleAnimMove_BoneClub,
    },

    [MOVE_FIRE_BLAST] =
    {

        .power = 120,
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_FireBlast,
    },

    [MOVE_WATERFALL] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Waterfall,
    },

    [MOVE_CLAMP] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .accuracy = 90,
            .pp = 15,
        #else
            .accuracy = 75,
            .pp = 10,
        #endif
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_WATER,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_CLAMP,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Clamp,
    },//I'd like to also add a flinch chance to this if I can, maybe with argument?
    //need to use argumenttomoveeffect  command to make use of arguments    uses   VARIOUS_ARGUMENT_TO_MOVE_EFFECT
    //also uses VARIOUS_ARGUMENT_STATUS_EFFECT to transfer effect into status still using secondaryeffectchance
    //so need to decouple trap effect from secondaryeffect  think can do by using make certain

[MOVE_SWIFT] =
{
    .effect = EFFECT_HIT,
    .power = 60,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 20,
    .target = MOVE_TARGET_BOTH,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Swift,
},
//potentially make this tutor move rather than tm

[MOVE_SKULL_BASH] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .power = 130,
        .pp = 10,
    #else
        .power = 100,
        .pp = 15,
    #endif
    .effect = EFFECT_TWO_TURNS_ATTACK,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .makesContact = TRUE,
    .headbuttMove = TRUE,
    .sleepTalkBanned = TRUE,
    .instructBanned = TRUE,
    .multiTaskBanned = TRUE,
    .argument.twoTurnAttack = { .stringId = STRINGID_PKMNLOWEREDHEAD },
    /*.additionalEffects = ADDITIONAL_EFFECTS({
        .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
        .self = TRUE,
        .onChargeTurnOnly = TRUE,
    }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SkullBash,
},

[MOVE_SPIKE_CANNON] =
{
    .effect = EFFECT_HIT,
    .power = 20,
    .type = TYPE_ROCK,
    .accuracy = 100, //was buffed is only 100 acc multi move
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .multiTaskBanned = TRUE,
    .variableMultihit = TRUE,
    .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpikeCannon,
},

[MOVE_CONSTRICT] =
{
    .effect = EFFECT_HIT,
    .power = 10,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .pp = 35,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Constrict,
},

[MOVE_AMNESIA] =
{
    .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
    .power = 0,
    .type = TYPE_PSYCHIC,
    .accuracy = 0,
    .pp = 20,
    .target = MOVE_TARGET_USER,
    .priority = 1,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Amnesia,
},

[MOVE_KINESIS] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
    #else
    #endif
    .effect = EFFECT_ACCURACY_DOWN,
    .power = 0,
    .type = TYPE_PSYCHIC,
    .accuracy = 100,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_KINESIS,
        //.contestComboMoves = {COMBO_STARTER_CONFUSION, COMBO_STARTER_PSYCHIC},
        //.battleAnimScript = gBattleAnimMove_Kinesis,
},

[MOVE_SOFT_BOILED] =
{
    .effect = EFFECT_SOFTBOILED, 
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .pp = 10,
    .target = MOVE_TARGET_USER,
    .priority = 1,
    .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_SOFT_BOILED,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SoftBoiled,
},

[MOVE_HI_JUMP_KICK] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
        .power = 130,
        .pp = 10,
    #elif B_UPDATED_MOVE_DATA == GEN_4
        .power = 100,
        .pp = 20,
    #else
        .power = 85,
        .pp = 20,
    #endif
    .effect = EFFECT_RECOIL_IF_MISS,
    .type = TYPE_FIGHTING,
    .accuracy = 90,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .makesContact = TRUE,
    .kickingMove = TRUE,
    .recoilMove = TRUE,
    .damagesAirborneDoubleDamage = TRUE,
    .gravityBanned = TRUE,
},
//since is jumping kick game hit in air, and since is resisted by flying and risks recoil
//made 2x

[MOVE_GLARE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .accuracy = 100,
    #elif B_UPDATED_MOVE_DATA == GEN_5
        .accuracy = 90,
    #else
        .accuracy = 75,
    #endif
    .effect = EFFECT_NON_VOLATILE_STATUS,
    .power = 0,
    .type = TYPE_DARK,
    .pp = 30,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_LEER},
        //.battleAnimScript = gBattleAnimMove_Glare,
},

[MOVE_DREAM_EATER] =
{
    .effect = EFFECT_DREAM_EATER,
    .power = 100,
    .type = TYPE_PSYCHIC,
    .accuracy = 100,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .healingMove = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_HYPNOSIS},
        //.battleAnimScript = gBattleAnimMove_DreamEater,
},

[MOVE_POISON_GAS] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .accuracy = 90,
        .target = MOVE_TARGET_BOTH,
    #elif B_UPDATED_MOVE_DATA == GEN_5
        .accuracy = 80,
        .target = MOVE_TARGET_BOTH,
    #else
        .accuracy = 55,
        .target = MOVE_TARGET_SELECTED,
    #endif
    .effect = EFFECT_NON_VOLATILE_STATUS,
    .power = 0,
    .type = TYPE_POISON,
    .pp = 40,
    .priority = 1,
    .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_POISON },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PoisonGas,
},

[MOVE_BARRAGE] =
{
    .effect = EFFECT_STAT_BASED_SPLIT,//Forgot also gave this dmg swap based on stats
    .power = 15,
    .type = TYPE_NORMAL, //idea is uses psychic energy to pick up and throw
    .accuracy = 95, //objects at the enemy with force
    .pp = 20,   //ok think what can do is make into psyshock hits defense but uses special
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .multiTaskBanned = TRUE,
    .ballisticMove = TRUE,
    .variableMultihit = TRUE,
    //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
    //.contestCategory = CONTEST_CATEGORY_TOUGH,
    //.contestComboStarterId = 0,
    //.contestComboMoves = {0},
    //.battleAnimScript = gBattleAnimMove_Barrage,
    /*.additionalEffects = ADDITIONAL_EFFECTS({
        .moveEffect = MOVE_EFFECT_DEF_MINUS_1, //should i make new effect that'll swap def 
        .chance = 15, //to drop based on dmg category? since it could be special?
    }),*/
}, //exegcuttor line siganture , test may make 100 acc,  balance acc w effect chance
//could be normal cuz just objects
//could be psychic cuz covered in psychic energy
//ok decided will leave normal as leaves room open for 
//making multi type from the other abilities
//i.e galvanize aerialate pixilate refrigerate
//decide change was exeggcute signature so they would use psychic ability to throw stuff
//will make this use highest offense stat
//but still hit defense as throwing objects

[MOVE_LEECH_LIFE] =
{
    .effect = EFFECT_ABSORB,
    .power = 42,
    .type = TYPE_BUG,
    .accuracy = 100,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .argument = { .absorbPercentage = 100 },
        .makesContact = TRUE,
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LeechLife,
     // restores 75% HP instead of 50% HP
     //removed infest chance to boost healing, to compete with mega drain
}, //check balance

[MOVE_LOVELY_KISS] =
{
    .effect = EFFECT_NON_VOLATILE_STATUS,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 75,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0, //since this keeps opponent from attacking will keep base priority
    .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LovelyKiss,
},

[MOVE_SKY_ATTACK] =
{

    .effect = EFFECT_SEMI_INVULNERABLE, //wait rather than a charge move why don't I make it a literal flying attack?
    .power = 140,   //could make this the upgrade to fly and be an actually good semi-invulnerable move
    .type = TYPE_FLYING,
    .accuracy = 100, //raised accuracy cant have charge a turn and still miss smh
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,//could do took to the air then end turn effect glowing w energy strnig?
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .enhancedCritrate = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = B_UPDATED_MOVE_DATA >= GEN_4 ? STRINGID_CLOAKEDINAHARSHLIGHT : STRINGID_PKMNISGLOWING },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SkyAttack,
}, //DO SOMething with this, thinking raise evasiveness one or two stages, may lower power since hitting both
//it stil needs to be strongest flying move though and brave bird is base 120 no charge 
//ok alraedy added a 2 stage evasion boost to this, done on the charging turn
//with change to flying types the evasion boost on this is exemplary of the type
//as the strongest move potentially lower to 1 stage evasion boost
//vsonic don't want the move to be too free, that its spammable
//review revise remove evasion boost as flying types now already get that
//instead leave it up to strategizing i.e force target follow me stuff like that
//to ensure can survive to do damage - done removed stat boost
//decided will change to 2 turn into teh air semi invulnerable move
//double benefit will remove knocked down status when takes to the air
//gives reason for moves that do damage in air
//the semi invul moves and the effects that can hit them in that state
//almost never come up
//ok need make end turn effect so can display charging message
//ah see power her also works on invul moves like dig dive fly
//cool than changing to semi invlunerable it wouldn't lose
//power herb option
//all done just need end turn strign now done fixed

[MOVE_TRANSFORM] =
{
    .effect = EFFECT_TRANSFORM,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 2,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Transform,
},

[MOVE_BUBBLE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .power = 40,
    #else
        .power = 20,
    #endif
    .effect = EFFECT_HIT,
    .type = TYPE_WATER,
    .accuracy = 95,
    .pp = 30,
    .target = MOVE_TARGET_BOTH,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Bubble,
},
//bubbles are slow, changed acc to give water gun back a niche

[MOVE_DIZZY_PUNCH] =
{
    .effect = EFFECT_HIT,
    .power = 70,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DizzyPunch,
},

[MOVE_SPORE] =
{
    .effect = EFFECT_NON_VOLATILE_STATUS,
    .power = 0,
    .type = TYPE_GRASS,
    .accuracy = 95,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0, 
    .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Spore,
},//keep an eye on -vsonic
//talked w chief making negative priority does nothing for the problem,
//just make it hard/impossible for faster mon to use the move,
//when the issue is just amoongus, who's so bulky it just doesn't have to worry,
//so best thing I can do is just, and I do mean just, to lower its accuracy
//at most lower to 90

[MOVE_FLASH] =
{
    //since I'm strengthening effect I may lowered accuracy from 100
    .accuracy = 85,
    .effect = EFFECT_ACCURACY_DOWN, //lower acc guaranteed and flinch chance
    .power = 0,
    .type = TYPE_NORMAL,
    .pp = 20,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1, //since is an hm I guess I could allow this?
    .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Flash,
},//later test flinch chance to see if too much

[MOVE_PSYWAVE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .accuracy = 100,
    #else
        .accuracy = 80,
    #endif
    .effect = EFFECT_PSYWAVE, //ignores resistance
    .power = 1, //since typeless think should have made this power 0 but forgot
    .type = TYPE_PSYCHIC, //change power as no longer typeless
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_Psywave,
},

[MOVE_SPLASH] =
{
    .effect = EFFECT_DO_NOTHING,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 40,
    .target = MOVE_TARGET_USER,
    .priority = 3,
    .split = SPLIT_PHYSICAL,//SPLIT_STATUS, //think change to physical
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .gravityBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Splash,
},//vsonic important check make sure no issue

[MOVE_ACID_ARMOR] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .pp = 20,
    #else
        .pp = 40,
    #endif
    .effect = EFFECT_DEFENSE_UP_2,
    .power = 0,
    .type = TYPE_POISON,
    .accuracy = 0,
    .target = MOVE_TARGET_USER,
    .priority = 1,
    .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AcidArmor,
},

[MOVE_CRABHAMMER] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .power = 100,
        .accuracy = 90,
    #elif B_UPDATED_MOVE_DATA == GEN_5
        .power = 90,
        .accuracy = 90,
    #else
        .power = 90,
        .accuracy = 85,
    #endif
    .effect = EFFECT_HIT,
    .type = TYPE_WATER,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .enhancedCritrate = TRUE, //oh right think put crit on this to try making krabby better
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_Crabhammer,
},

[MOVE_EXPLOSION] =
{
    .effect = EFFECT_EXPLOSION,
    .power = 170,//250,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .pp = 5,
    .target = MOVE_TARGET_FOES_AND_ALLY,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
        .multiTaskBanned = TRUE,
        .dampBanned = TRUE,
        .ballisticMove = TRUE,
        .explosiveMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Explosion,
},//gen 1 power 170 consider drop and rework self destruct
//cut distribution may boost power up slighty
//if need give reason to use over self destruct
//well a difference I could make is
//self destruct and mind blown would fail
//if didn't have enoough hp to activate it
//i.e they die before it goes off.
//leaving explosion as the pre-eminent boom.
//think that's good, requires a bit of planning and forethought
//vsonic
//sturdy mon could survive 
//making them best bomb users as well

[MOVE_FURY_SWIPES] =
{
    .effect = EFFECT_HIT,
    .power = 15,
    .type = TYPE_NORMAL,
    .accuracy = 90,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .makesContact = TRUE,
    .multiTaskBanned = TRUE,
    .enhancedCritrate = TRUE,
    .variableMultihit = TRUE,
    //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
    //.contestCategory = CONTEST_CATEGORY_TOUGH,
    //.contestComboStarterId = 0,
    //.contestComboMoves = {COMBO_STARTER_SCRATCH},
    //.battleAnimScript = gBattleAnimMove_FurySwipes,
},

[MOVE_BONEMERANG] =
{
    .effect = EFFECT_HIT,
    .power = 50,
    .type = TYPE_GROUND,
    .accuracy = 90,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .damagesAirborne = TRUE,
    .strikeCount = 2,
    .multiTaskBanned = TRUE,
    //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
    //.contestCategory = CONTEST_CATEGORY_TOUGH,
    //.contestComboStarterId = COMBO_STARTER_BONEMERANG,
    //.contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONE_RUSH, COMBO_STARTER_SHADOW_BONE},
    //.battleAnimScript = gBattleAnimMove_Bonemerang,
},

[MOVE_REST] =
{
    .effect = EFFECT_REST,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 10,
    .target = MOVE_TARGET_USER,
    .priority = 0, //since is full hp don't think I can boost,
    .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_REST,
        //.contestComboMoves = {COMBO_STARTER_BELLY_DRUM, COMBO_STARTER_CHARM, COMBO_STARTER_YAWN},
        //.battleAnimScript = gBattleAnimMove_Rest,
},

[MOVE_ROCK_SLIDE] =
{
    .effect = EFFECT_HIT,
    .power = 75,
    .type = TYPE_ROCK,
    .accuracy = 90,
    .pp = 10,
    .target = MOVE_TARGET_BOTH,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        //.battleAnimScript = gBattleAnimMove_RockSlide,
},//may set back to 90, and 30 w onix buffs makes onix best rock slide user
//a significant buff for it... yeah think I will
//effect is good enough that the accuracy  isn't strange

[MOVE_HYPER_FANG] =
{
    .effect = EFFECT_HIT,
    .power = 95,
    .type = TYPE_NORMAL,
    .accuracy = 90,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HyperFang,
},

[MOVE_SHARPEN] =
{
    .effect = EFFECT_ATTACK_UP,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 30,
    .target = MOVE_TARGET_USER,
    .priority = 1,
    .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Sharpen,
},

[MOVE_CONVERSION] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
    #else
    #endif
    .effect = EFFECT_CONVERSION,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 30,
    .target = MOVE_TARGET_USER,
    .priority = 1,
    .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Conversion,
},

[MOVE_TRI_ATTACK] =
{
    .effect = EFFECT_STAT_BASED_SPLIT,
    .power = 80,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TRI_ATTACK,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_LOCK_ON},
        //.battleAnimScript = gBattleAnimMove_TriAttack,
},

[MOVE_SUPER_FANG] =
{
    .effect = EFFECT_FIXED_PERCENT_DAMAGE,
    .power = 1,
    .type = TYPE_NORMAL,
    .accuracy = 90,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .argument = { .damagePercentage = 50 },
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        //.battleAnimScript = gBattleAnimMove_SuperFang,
},

[MOVE_SLASH] =
{
    .effect = EFFECT_HIT,
    .power = 75,
    .type = TYPE_NORMAL,
    .accuracy = 95,
    .pp = 20,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SCRATCH, COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_Slash,
},

[MOVE_SUBSTITUTE] =
{
    .effect = EFFECT_SUBSTITUTE,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 95,
    .pp = 10,
    .target = MOVE_TARGET_USER,
    .priority = 0, //would like to do but worry makes it too risk free? same as rest
    .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Substitute,
},

[MOVE_STRUGGLE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
        .accuracy = 0,
    #else
        .accuracy = 100,
    #endif
    .effect = EFFECT_RECOIL, //w my change struggle is far less punishing, potentially swap effect for EFECT_MED_RECOIL
    .power = 50,
    .type = TYPE_NORMAL,//tested seems fine at boosted recoil
    .pp = 1,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_MED_RECOIL,
                .self = TRUE,
            }),*/
        //.battleAnimScript = gBattleAnimMove_Struggle,
},

[MOVE_SKETCH] =
{
    .effect = EFFECT_SKETCH,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Sketch,
},

[MOVE_TRIPLE_KICK] =
{
    .effect = EFFECT_TRIPLE_KICK,   //changing triple kick effect, handling like gen 2 with dmg multiple, will be done in dmg calc command, 
    .power = 15,
    .type = TYPE_FIGHTING,
    .accuracy = 90,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .strikeCount = 3,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_TripleKick,
},

[MOVE_THIEF] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .power = 60,
        .pp = 25,
    #else
        .power = 40,
        .pp = 10,
    #endif
    .effect = EFFECT_STEAL_ITEM,
    .type = TYPE_DARK,
    .accuracy = 95,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Thief,
},

[MOVE_SPIDER_WEB] =
{

    .effect = EFFECT_NON_VOLATILE_STATUS,
    .power = 0,
    .type = TYPE_BUG,
    .accuracy = 0,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_PARALYSIS },
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_STRING_SHOT},
        //.battleAnimScript = gBattleAnimMove_SpiderWeb,
},
//taken over by swarm/infestation and sticky web
//spider webs to my knowledge have effect of paralyzing those stuck in it?
//yup found some spiders lace web in neurotoxin that can paralyze those stuck in it
//for them to eat later
//so rework this into bug move that paralyzes
//even better as would work on electric types
//since no good mon get this think am safe to leave it sure hit
//thunder wave was nerfed becuause of high access and 
//it being on legendary mon

[MOVE_MIND_READER] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
        .accuracy = 0,
    #else
        .accuracy = 100,
    #endif
    .effect = EFFECT_LOCK_ON,
    .power = 0,
    .type = TYPE_NORMAL,
    .pp = 5,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_MIND_READER,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MindReader,
},

[MOVE_NIGHTMARE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
        .accuracy = 100,
    #else
        .accuracy = 0,
    #endif
    .effect = EFFECT_NIGHTMARE,
    .power = 0,
    .type = TYPE_GHOST,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Nightmare,
},

[MOVE_FLAME_WHEEL] =
{
    .effect = EFFECT_FIXATION,//think for this set fixation turns based on number times used it, increment in attack canceler
    .power = 60,
    .type = TYPE_FIRE,//change back to 60 base power 2 turn fixation
    .accuracy = 100,
    .pp = 25,
    .target = MOVE_TARGET_SELECTED,//note since effect is in atk canceler completely ignores acc/need for move to actually land
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_DMG_FIXATION,
            .self = TRUE,
        }),*/
        .argument = {.fixedDamage = 15},
        //think wanna do something like improved condition
        //w repeated use can't be starteled or can't lose heart something
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING, 
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_FlameWheel,
},
//rebalanced effect for this max is 2
//effect inspired by legends arceus fixated status
//incrases move power with repeated use
//plan have this as category of effect no idea about more moves
//core principle user fixates on move gets better with repeated use
//in some way.
//not always dmg, just it becomes improved in some way over time
//dmg, acc, or some other additional benefit
//vsonic Important
//could do with move effect
//set base effect as Fixation
//then use additional effects to set category of fixation? 
//then again that would take up an effect when
//I could easily put that in effect
//but for sake of balance that would be 
//a lot to put on something to have 2 full slots
//in addition to an effect that is good/gets better w use
//decided generalize effect set category w move effect and self
//then have move effect set volatile status specifically 
//based on category so can filter in the fixation canceler
//ok technically don't need effect fixation it'd just be hit
//but will have same balane issue instead
//keep effect_fixation and have that be the requirement
//for using fixation move effects the move has to be a fixation move
//the effect requirement is both thematic and for balance

[MOVE_SNORE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .power = 75,
    #elif B_UPDATED_MOVE_DATA == GEN_5
        .power = 40,
    #else
        .power = 40,
    #endif
    .effect = EFFECT_SNORE,
    .type = TYPE_SOUND,
    .accuracy = 100,
    .pp = 15,
    .target = MOVE_TARGET_BOTH,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_REST},
        //.battleAnimScript = gBattleAnimMove_Snore,
}, 
//redid script put flinch in move argument not on snore script itself
//should make a good tm?
//does flinch so no cacophony boost,hmm well I could screw it
//check what mon get snore, since changed to both may need drop strength?
//ok so only fast mon that learns snore is Dedenne,
//so I guess its fine?

[MOVE_CURSE] =
{

    .type = TYPE_MYSTERY,
    .effect = EFFECT_CURSE,
    .power = 0,
    .accuracy = 0,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .argument = { .sacrificedHpPercentage = 50 }, //for ghost curse
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_CURSE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Curse,
},

[MOVE_FLAIL] =
{
    .effect = EFFECT_FLAIL,
    .power = 1,
    .type = TYPE_NORMAL,
    .accuracy = 100,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ENDURE},
        //.battleAnimScript = gBattleAnimMove_Flail,
},

[MOVE_CONVERSION_2] =
{
    .effect = EFFECT_CONVERSION,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 30,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1, //can change priority when finish new effect so not based on last move hit by
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Conversion2,
},//now same as conversion 1, so reuse effect, just does type 2 instead

[MOVE_AEROBLAST] =
{
    .effect = EFFECT_HIT,
    .power = 100,
    .type = TYPE_FLYING,
    .accuracy = 95,
    .pp = 5,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
    /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 50,
        }),*/
        .windMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Aeroblast,
},
//w sp def drop consider may remove high crit?
//would make it more balanced and allow me to spread its distribution
//giving more flying mon a good special option other than hurricane
//think just make this a tm
//think put in same place get lugia
//after lugia fight, lugia drops tm in its place
//vsonic

[MOVE_COTTON_SPORE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .accuracy = 100,
        .target = MOVE_TARGET_BOTH,
    #elif B_UPDATED_MOVE_DATA == GEN_5
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
    #else
        .accuracy = 85,
        .target = MOVE_TARGET_SELECTED,
    #endif
    .effect = EFFECT_SPEED_DOWN_2,
    .power = 0,
    .type = TYPE_GRASS,
    .pp = 40,
    .priority = 1,
    .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CottonSpore,
},

[MOVE_REVERSAL] =
{
    .effect = EFFECT_FLAIL,
    .power = 1,
    .type = TYPE_FIGHTING,
    .accuracy = 100,
    .pp = 15,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ENDURE},
        //.battleAnimScript = gBattleAnimMove_Reversal,
},

[MOVE_SPITE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
    #else
    #endif
    .effect = EFFECT_SPITE,
    .power = 0,
    .type = TYPE_GHOST,
    .accuracy = 100,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CURSE},
        //.battleAnimScript = gBattleAnimMove_Spite,
},//keep as is ,relies on move beign used

[MOVE_POWDER_SNOW] =
{
    .effect = EFFECT_HIT,
    .power = 40,
    .type = TYPE_ICE,
    .accuracy = 100,
    .pp = 25,
    .target = MOVE_TARGET_BOTH,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_POWDER_SNOW,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_PowderSnow,
},

[MOVE_PROTECT] =
{
    .priority = 4,
    .effect = EFFECT_PROTECT,
    .power = 0,
    .type = TYPE_NORMAL,
    .accuracy = 0,
    .pp = 10,
    .target = MOVE_TARGET_USER,
    .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_NORMAL },
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HARDEN},
        //.battleAnimScript = gBattleAnimMove_Protect,
},

[MOVE_MACH_PUNCH] =
{
    .effect = EFFECT_HIT,
    .power = 40,
    .type = TYPE_FIGHTING,
    .accuracy = 100,
    .pp = 30,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MachPunch,
},

[MOVE_SCARY_FACE] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
        .accuracy = 100,
    #else
        .accuracy = 90,
    #endif
    .effect = EFFECT_SPEED_DOWN_2,
    .power = 0,
    .type = TYPE_NORMAL,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SCARY_FACE,
        //.contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_RAGE},
        //.battleAnimScript = gBattleAnimMove_ScaryFace,
},

[MOVE_FEINT_ATTACK] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
    #else
    #endif
    .effect = EFFECT_HIT,
    .power = 60,
    .type = TYPE_DARK,
    .accuracy = 0,
    .pp = 20,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_LEER, COMBO_STARTER_POUND},
        //.battleAnimScript = gBattleAnimMove_FeintAttack,
},

[MOVE_SWEET_KISS] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_6
        .type = TYPE_FAIRY,
    #else
        .type = TYPE_NORMAL,
    #endif
    .effect = EFFECT_CONFUSE,
    .power = 0,
    .accuracy = 85,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARM},
        //.battleAnimScript = gBattleAnimMove_SweetKiss,
},
//don't understand why this has 75 acc when confuse ray is 100
//I guess only reason is its paired with lovely kiss which is 
//a sleep move
//already shares naming convention and animation
//I can buff its acc and it can still function as paired move

[MOVE_BELLY_DRUM] =
{
    .effect = EFFECT_BELLY_DRUM, //huh could actually make this the sacrifice health effect
    .power = 0,
    .type = TYPE_NORMAL, //nah needs unique effect for ai checks,
    .accuracy = 0, //could make general script tho, sacrifice health boost stat etc.
    .pp = 10,
    .target = MOVE_TARGET_USER,
    .priority = 0, //unsure bout this can't tell if its an advantage or disadvantage for the move to go first
    .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .argument = { .sacrificedHpPercentage = 50 },
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_BELLY_DRUM,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BellyDrum,
},//ok decide its better this goes last better chance of surviving the turn
//rather than using it first and having chance get killed now you use it last
//and have a chance of wasting the turn if the opponent drops you to half
//alternately keep; at 0 or plus one and allow a healer to go after,
//or the move that lets target attack twice
//could use rest w sleep talk, or go directly into an attack

[MOVE_SLUDGE_BOMB] =
{
    .effect = EFFECT_HIT,
    .power = 90,
    .type = TYPE_POISON,
    .accuracy = 100,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SLUDGE_BOMB,
        //.contestComboMoves = {COMBO_STARTER_SLUDGE},
        //.battleAnimScript = gBattleAnimMove_SludgeBomb,
},

[MOVE_MUD_SLAP] =
{
    .effect = EFFECT_HIT,
    .power = 30,
    .type = TYPE_GROUND,
    .accuracy = 100,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_MUD_SLAP,
        //.contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_SAND_ATTACK, COMBO_STARTER_SANDSTORM},
        //.battleAnimScript = gBattleAnimMove_MudSlap,
},

[MOVE_OCTAZOOKA] =
{
    .effect = EFFECT_HIT,
    .power = 85,
    .type = TYPE_WATER,
    .accuracy = 85,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_LOCK_ON, COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Octazooka,
},

[MOVE_SPIKES] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
    #else
    #endif
    .effect = EFFECT_SPIKES,
    .power = 0,
    .type = TYPE_GROUND,
    .accuracy = 0,
    .pp = 20,
    .target = MOVE_TARGET_OPPONENTS_FIELD,
    .priority = 0,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = TRUE,
        .forcePressure = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Spikes,
},

[MOVE_ZAP_CANNON] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
        .power = 80,
    #else
        .power = 100,
    #endif
    .effect = EFFECT_HIT,
    .type = TYPE_ELECTRIC,
    .accuracy = 90,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_LOCK_ON},
        //.battleAnimScript = gBattleAnimMove_ZapCannon,
},

[MOVE_FORESIGHT] =
{
    .accuracy = 0,
    .effect = EFFECT_FORESIGHT,
    .power = 0,
    .type = TYPE_NORMAL,
    .pp = 40,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
    .magicCoatAffected = TRUE,
    .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Foresight,
},

[MOVE_DESTINY_BOND] =
{
    .effect = EFFECT_DESTINY_BOND,
    .power = 0,
    .type = TYPE_GHOST,
    .accuracy = 0,
    .pp = 5,
    .target = MOVE_TARGET_USER,
    .priority = 1,
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CURSE, COMBO_STARTER_ENDURE, COMBO_STARTER_MEAN_LOOK},
        //.battleAnimScript = gBattleAnimMove_DestinyBond,
},

[MOVE_PERISH_SONG] =
{
    .effect = EFFECT_PERISH_SONG,
    .power = 0,
    .type = TYPE_SOUND,
    .accuracy = 0,
    .pp = 5,
    .target = MOVE_TARGET_USER,
    .priority = 1, //keep an eye on, but good for increasing moves pressure without overall being oppressive
    .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_SING},
        //.battleAnimScript = gBattleAnimMove_PerishSong,
},//need test, attempt set cacophony perish song to set lower timer for opposing side

[MOVE_ICY_WIND] =
{
    .effect = EFFECT_HIT,
    .power = 55,
    .type = TYPE_ICE,
    .accuracy = 95,
    .pp = 15,
    .target = MOVE_TARGET_BOTH,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_IcyWind,
},

[MOVE_DETECT] =
{
    .priority = 4,
    .effect = EFFECT_PROTECT,
    .power = 0,
    .type = TYPE_FIGHTING,
    .accuracy = 0,
    .pp = 5,
    .target = MOVE_TARGET_USER,
    .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_NORMAL },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TAUNT},
        //.battleAnimScript = gBattleAnimMove_Detect,
},

[MOVE_BONE_RUSH] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
        .accuracy = 90,
    #else
        .accuracy = 80,
    #endif
    .effect = EFFECT_HIT,
    .power = 28,
    .type = TYPE_GROUND,
    .pp = 10,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
    .multiTaskBanned = TRUE,
    .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_BONE_RUSH,
        //.contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONEMERANG, COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_SHADOW_BONE},
        //.battleAnimScript = gBattleAnimMove_BoneRush,
},

[MOVE_LOCK_ON] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_4
        .accuracy = 0,
    #else
        .accuracy = 100,
    #endif
    .effect = EFFECT_LOCK_ON,
    .power = 0,
    .type = TYPE_NORMAL,
    .pp = 5,
    .target = MOVE_TARGET_SELECTED,
    .priority = 1,
    .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_LOCK_ON,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LockOn,
},

[MOVE_OUTRAGE] =
{


    .power = 120,
    .pp = 15,
    .effect = EFFECT_HIT,
    .type = TYPE_DRAGON,
    .accuracy = 100,
    .target = MOVE_TARGET_RANDOM,
    .priority = 0,
    .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Outrage,
},

[MOVE_SANDSTORM] =
{
    .effect = EFFECT_SANDSTORM,
    .power = 0,
    .type = TYPE_ROCK,
    .accuracy = 0,
    .pp = 5,
    .target = MOVE_TARGET_USER,
    .priority = 1, //thought about it decided going first is good for move gives needed utility back to moves
    .split = SPLIT_STATUS, //has wider  distribution than abilities and with priority gives reason to use the move
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .windMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SANDSTORM,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Sandstorm,
},//would ironically work just like abilities whicher mon is slower if both set weather gest the priority for setting weather

[MOVE_GIGA_DRAIN] =
{
    #if B_UPDATED_MOVE_DATA >= GEN_5
        .power = 85,
        .pp = 15,
    #elif B_UPDATED_MOVE_DATA == GEN_4
        .power = 60,
        .pp = 10,
    #else
        .power = 60,
        .pp = 5,
    #endif
    .effect = EFFECT_ABSORB,
    .type = TYPE_GRASS,
    .accuracy = 100,
    .target = MOVE_TARGET_SELECTED,
    .priority = 0,
    .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_GigaDrain,
},//actually think 95 is too much power for a healing move
//did need better grass moves but going to 95 power was too much

[MOVE_ENDURE] =
{   //prefer keeping at priority 3 hmm point of making +4 is to survive fake out.. ok i'll do it
    #if B_UPDATED_MOVE_DATA >= GEN_5
        .priority = 4,
    #else
        .priority = 3,
    #endif
        .effect = EFFECT_ENDURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_ENDURE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Endure,
    },

    [MOVE_CHARM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .type = TYPE_FAIRY,
        #else
            .type = TYPE_NORMAL,
        #endif
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_CHARM,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Charm,
    },

    [MOVE_ROLLOUT] =
    {
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN},
        //.battleAnimScript = gBattleAnimMove_Rollout,
    },

    [MOVE_FALSE_SWIPE] =
    {
        .effect = EFFECT_FALSE_SWIPE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_FalseSwipe,
    },

    [MOVE_SWAGGER] =
    {
        /*#if B_UPDATED_MOVE_DATA >= GEN_7
            .accuracy = 0,
        #else*/
            .accuracy = 90,
        //#endif
        .effect = EFFECT_SWAGGER,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Swagger,
    },

    [MOVE_MILK_DRINK] =
    {
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MilkDrink,
    },

    [MOVE_SPARK] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_Spark,
    },

    [MOVE_FURY_CUTTER] =
    {
        .effect = EFFECT_FURY_CUTTER,
        .power = 15, //chec furycutter calc command, need further fine tune dmg, still over performing
        .type = TYPE_BUG,
        .accuracy = 100, //for some reason started over-performing, changed mind, will doit in function instead
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .multiTaskBanned = TRUE,
        .strikeCount = 5, //attempts 5 hit but w acc decrement
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_FuryCutter,
    }, 

    [MOVE_STEEL_WING] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SteelWing,
    },

    [MOVE_MEAN_LOOK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            #else
            #endif
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_MEAN_LOOK,
        //.contestComboMoves = {COMBO_STARTER_CURSE},
        //.battleAnimScript = gBattleAnimMove_MeanLook,
    },

    [MOVE_ATTRACT] =
    {
        .effect = EFFECT_ATTRACT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Attract,
    },

    [MOVE_SLEEP_TALK] =
    {
        .effect = EFFECT_SLEEP_TALK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 1, //same logic as assist
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mimicBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_REST},
        //.battleAnimScript = gBattleAnimMove_SleepTalk,
    },

    [MOVE_HEAL_BELL] =
    {
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_HEAL_BELL,
        //.contestComboMoves = {COMBO_STARTER_LUCKY_CHANT},
        //.battleAnimScript = gBattleAnimMove_HealBell,
    },

    [MOVE_RETURN] =
    {
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Return,
    },

    [MOVE_PRESENT] =
    {
        .effect = EFFECT_PRESENT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL, //unsure if shold be physical? ok yeah its, a boobytrap bomb, if explosion is physical this should be too
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Present,
    },
    //vsonic important think need update kins rock with dmg logic to make sure doesn't activate on heal?

    [MOVE_FRUSTRATION] =
    {
        .effect = EFFECT_FRUSTRATION,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Frustration,
    },

    [MOVE_SAFEGUARD] =
    {
        .effect = EFFECT_SAFEGUARD,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Safeguard,
    },

    [MOVE_PAIN_SPLIT] =
    {
        .effect = EFFECT_PAIN_SPLIT,
        .power = 0,
        .type = TYPE_GHOST, //was normal but so linked to ghost in mind just changed
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,//usually better to go last so keep as is
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ENDURE},
        //.battleAnimScript = gBattleAnimMove_PainSplit,
    },//changed mostly spidops in mind, its not broken since its an average 
    //rather than flat cutting enemy hp in half
    //hmm what if I made this ignore protect
    //vsonic

    [MOVE_SACRED_FIRE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .thawsUser = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_SacredFire,
    },

    [MOVE_MAGNITUDE] =
    {
        .effect = EFFECT_MAGNITUDE,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        .multiTaskBanned = TRUE, //vsonic can prob get working w refactor
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Magnitude,
    },
    //w script changes unsureright sript, need change branch
    //and go back to check this and earthquake
    //mostly check animations

    [MOVE_DYNAMIC_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 85,    //think this better at 85 for the pp and effects
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 70,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_DynamicPunch,
    },

    [MOVE_MEGAHORN] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 10,  //since I gave it flinch should lower pp to 5
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .headbuttMove = TRUE,
         /*.additionalEffects = ADDITIONAL_EFFECTS(
         {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
         },
         {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 5,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Megahorn,
    },
    //most mon that get it are slow so can keep at 10pp

    [MOVE_DRAGON_BREATH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_DRAGON_BREATH,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        //.battleAnimScript = gBattleAnimMove_DragonBreath,
    },

    [MOVE_BATON_PASS] =
    {
        .effect = EFFECT_BATON_PASS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,//1, //makes stronger but still have option to beat w pursuit or priority move
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BatonPass,
    }, //what happens if the user is trapper/has escape prevention? if also blocks then even better
    //seems sometimes you want slower baton pass so guess keep this as is

    [MOVE_ENCORE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_ENCORE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .encoreBanned = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Encore,
    },//added to priority boosted list since makes easie to use

    [MOVE_PURSUIT] =
    {
        .effect = EFFECT_PURSUIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 95, 
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Pursuit,
    }, //boosted to 60 compare to assurance, make sense as assurance previously was also base 50
    //decide do middle ground make bp 50 change boost to 1.5 rather than 2
    // so a 5bp drop at max but good deal stronger overall
    //decide do same as knock off, remove bonus damage drop acc
    //making all 60 would give move comparity between
    //pursuit knock off and feint attack, each with their own niche
    //realized thief also counts as dark move with broken effect
    //that is 60 bp
    //need double check script so accuracy change would work correctly here

    [MOVE_RAPID_SPIN] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 50,
        #else
            .power = 20,
        #endif
        .effect = EFFECT_RAPID_SPIN,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS(
            {
                .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
                .self = TRUE,
                .chance = 100,
            }),*/
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RapidSpin,
    },//need redo this script, make go to hit from atkcancel or atkstring, consider  using emerald additional effect implementation
    //should work same but potentially cut down on redundent scripts made. would not need new effect for everyone just to assign the move effect
    //if it was that simple ex. rather than needing a rapid spin effect to set moveeffect rapid spin, 
    //they have effect hit, and then 2 additional affects that set rapidspin move effect adn the speed pls move effect...

    [MOVE_SWEET_SCENT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .effect = EFFECT_EVASION_DOWN_2,
        #else
            .effect = EFFECT_EVASION_DOWN,
        #endif
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_SWEET_SCENT,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SweetScent,
    },

    [MOVE_IRON_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IronTail,
    },//for some reason defense lower affected self??
    //issue is all stat down hit, working on fixnig

    [MOVE_METAL_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_METAL_SOUND},
        //.battleAnimScript = gBattleAnimMove_MetalClaw,
    },//ok but THIS worked correctly?? not sure if it played correct animation, was green expected tobe red
    //they use same flags so may be effect stat setting affect issue not issue w flag

    [MOVE_VITAL_THROW] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        //.battleAnimScript = gBattleAnimMove_VitalThrow,
    },

    [MOVE_MORNING_SUN] =
    {
        .effect = EFFECT_MORNING_SUN,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_MorningSun,
    },//buffed recovery movs to standard base 10, more optimal for player, harder to deal with in opponet
    //but has options in heal block, and pp drop effects

    [MOVE_SYNTHESIS] =
    {
        .effect = EFFECT_SYNTHESIS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_Synthesis,
    },

    [MOVE_MOONLIGHT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .type = TYPE_FAIRY,
        #else
            .type = TYPE_NORMAL,
        #endif
        .effect = EFFECT_MOONLIGHT,
        .power = 0,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_Moonlight,
    },

    [MOVE_HIDDEN_POWER] =
    {
        .power = 1, //change to show varying power
        .effect = EFFECT_HIT,
        .type = TYPE_MYSTERY, //MOVED power set to damagecalc
        .accuracy = 100,    
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HiddenPower,
    },

    [MOVE_CROSS_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_CrossChop,
    },

    [MOVE_TWISTER] =
    {
        .effect = EFFECT_HIT, //smack down effect done with flag check, twister sets flinch
        .power = 55,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborneDoubleDamage = TRUE,
        .windMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Twister,
    },

    [MOVE_RAIN_DANCE] =
    {
        .effect = EFFECT_RAIN_DANCE,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_RAIN_DANCE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RainDance,
    },//has dance in name but not categorized as dance move
    //as there is no point in it working with Dancer ability
    //as if used after move was already used it would just fail

    [MOVE_SUNNY_DAY] =
    {
        .effect = EFFECT_SUNNY_DAY,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_SUNNY_DAY,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SunnyDay,
    },

    [MOVE_CRUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
            /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        //.battleAnimScript = gBattleAnimMove_Crunch,
    },

    [MOVE_MIRROR_COAT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #elif B_UPDATED_MOVE_DATA == GEN_4
            #else
            #endif
        .effect = EFFECT_MIRROR_COAT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .split = SPLIT_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TAUNT},
        //.battleAnimScript = gBattleAnimMove_MirrorCoat,
    },

    [MOVE_PSYCH_UP] =
    {
        .effect = EFFECT_PSYCH_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PsychUp,
    },

    [MOVE_EXTREME_SPEED] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .priority = 2, //why did I incrase the priority to 3?
        #else
            .priority = 1,
        #endif
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ExtremeSpeed,
    },

    [MOVE_ANCIENT_POWER] =
    {

        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AncientPower,
    },

    [MOVE_SHADOW_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShadowBall,
    },//again feel is too common to do flying knock, think intead put on ominous wind?

    [MOVE_FUTURE_SIGHT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6 //actually Ill use this since there are no 120 power psychic moves
            .power = 120,
            .accuracy = 100,
            .pp = 10,
        #elif B_UPDATED_MOVE_DATA == GEN_5
            .power = 100,
            .accuracy = 100,
            .pp = 10,
        #else
            .power = 80,
            .accuracy = 90,
            .pp = 15,
        #endif
        .effect = EFFECT_FUTURE_SIGHT,
        .type = TYPE_PSYCHIC,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_CONFUSION, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        //.battleAnimScript = gBattleAnimMove_FutureSight,
    },

    [MOVE_ROCK_SMASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 50,
        #else
            .power = 20,
        #endif
        .effect = EFFECT_TARGET_TYPE_DAMAGE, 
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),*/
        .argument = {
        .storedValue = TYPE_ROCK,
        .damagePercentage = 200},
        //.contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RockSmash,
    }, //Redid the seutp for this to make more flexible and easier to use for binary edits argument chance is multiplier
    //gets divided by  10,  so value of 20 is 2x dmg, binary cant do extra effects though, had to use call if in script to make defense drop work- test
    //same as how I did function for hidden power make conditions to augment damage
    //specifically if target is a rock type, want to double move power.  works!

    [MOVE_WHIRLPOOL] =
    {
        .power = 30,
        .accuracy = 90,
        .effect = EFFECT_HIT,
        .type = TYPE_WATER,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesUnderwater = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_WHIRLPOOL,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Whirlpool,
    },

    [MOVE_BEAT_UP] =
    {

        .power = 0,
        .effect = EFFECT_BEAT_UP,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BeatUp,
    },//makes sense to be a contact move, but no way to make work right with contact effects

    [MOVE_FAKE_OUT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .priority = 3,
            #elif B_UPDATED_MOVE_DATA == GEN_4
            .priority = 1,
            #else
            .priority = 1,
            #endif
        .effect = EFFECT_FIRST_TURN_ONLY,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_FAKE_OUT,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FakeOut,
    },

    [MOVE_UPROAR] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 90,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_UPROAR,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE, //mostly cuz fail ends upraor
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_UPROAR,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Uproar,
    },

    [MOVE_STOCKPILE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 20,
        #else
            .pp = 10,
        #endif
        .effect = EFFECT_STOCKPILE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_STOCKPILE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Stockpile,
    },
    //keep 3 stage effect but allow 2 uses 
    //of companion move before charge goes away
    //think keep status change just remove stockpiled status
    //diff idea, stockpile level has 3 stages
    //after 2 uses of companion moves i.e usedStoredStockpile
    //rollover at 2, when is equal to 2, decrement
    //stockpile stage, if after decrement is 0, then remove status
    //and can't use stock pile moves until stores more charges
    //for balance think will only remove stat buffs
    //if stockpile hits 0? unsure VSONIC

    [MOVE_SPIT_UP] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 1,
        #else
            .power = 100,
        #endif
        .effect = EFFECT_SPIT_UP,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_STOCKPILE},
        //.battleAnimScript = gBattleAnimMove_SpitUp,
    },

    [MOVE_SWALLOW] =
    {
        .effect = EFFECT_SWALLOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_STOCKPILE},
        //.battleAnimScript = gBattleAnimMove_Swallow,
    },

    [MOVE_HEAT_WAVE] =
    {

        .power = 100,
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_HeatWave,
    },

    [MOVE_HAIL] =
    {
        .effect = EFFECT_HAIL,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_HAIL,
        //.contestComboMoves = {0},
        //.battleAnimScript = (B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW) ? gBattleAnimMove_Snowscape : gBattleAnimMove_Hail,
    },

    [MOVE_TORMENT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_TORMENT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Torment,
    },

    [MOVE_FLATTER] =
    {
        .effect = EFFECT_FLATTER,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 95, //keep higher acc just beacuse sp atkers have less things working against them
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARM},
        //.battleAnimScript = gBattleAnimMove_Flatter,
    },
    //hmm has no downside could change, either also raise attack,
    //so takes more damage if hit themselves,
    //or lower defense and raise sp atk 2 stages
    //leaning towards latter rn
    //considering acc drop most sp equivalents of physical effects are strictly better
    //for some reason. hmm if don't make equal guess  could just make 95 acc

    [MOVE_WILL_O_WISP] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 85,
        #else
            .accuracy = 75,
        #endif
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_FIRE,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_BURN },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_WillOWisp,
    },//should I drop priority on thsi?
    //I did for flash freeze but that's incompaciating,
    //that logic works keep all incompacitating moves at 0
    


    [MOVE_MEMENTO] =
    {
        .effect = EFFECT_MEMENTO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED, //vsonic important
        .priority = 0, //giving plus 1 lets it go off, but removes option of slow momento to keep switchin mon from taking dmg
        .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Memento,
    },//should bypass acc hit semi invul double check it still does that
    //good deal of mon can learn both fast and slow
    //think I'll just make a negativepriority move,
    //it'll be something you have to plan for

    [MOVE_FACADE] =
    {
        .effect = EFFECT_FACADE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Facade,
    },

    [MOVE_FOCUS_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 80,
        }),*/
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_FocusPunch,
    },

    [MOVE_SMELLING_SALTS] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 80,
        #else
            .power = 60,
        #endif
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .status = STATUS1_PARALYSIS },
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SmellingSalts,
    },
    //very low distribution, removes desirable effect
    //requires setup that nearly no mon with move can provide alone
    //i.e only given to fighting mon to level and few normal mon via breeding,
    //none that can paralyze
    //woot mentioned to make fighing type but not many normal moves
    //so think just keep normal but remove effect of curing paralysis
    //changed boosted base power since normal, lowered boosted power
    //and removed status removal


    [MOVE_FOLLOW_ME] =
    {

        .priority = 3,
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FollowMe,
    },

    [MOVE_NATURE_POWER] =
    {
        .effect = EFFECT_NATURE_POWER,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .split = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NaturePower,
    },//buffing add more powerful moves & make flying move condition side status tail wind to be mor accssible //vsonic

    [MOVE_CHARGE] =
    {
        .effect = EFFECT_CHARGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_CHARGE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Charge,
    },//see if this works attempt do same effect from unbreakable ties
    //idk what was going on with this, but don't need argument
    //better to just do stat change in script itself
    //argument command breaks otherswise

    [MOVE_TAUNT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #elif B_UPDATED_MOVE_DATA == GEN_4
            #else
            #endif
        .effect = EFFECT_TAUNT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_TAUNT,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Taunt,
    },

    [MOVE_HELPING_HAND] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .target = MOVE_TARGET_USER,
        #else
            .target = MOVE_TARGET_USER,
        #endif
        .effect = EFFECT_HELPING_HAND,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .priority = 5,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HelpingHand,
    },

    [MOVE_TRICK] =
    {
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Trick,
    },//item swap

    [MOVE_ROLE_PLAY] =
    {
        .effect = EFFECT_ROLE_PLAY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RolePlay,
    }, //copies target ability

    [MOVE_WISH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_WISH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Wish,
    },

    [MOVE_ASSIST] =
    {
        .effect = EFFECT_ASSIST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 1, //while is calling a move as it normally gets no priority beneift of said move, and its random think safe to give priority
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Assist,
    },

    [MOVE_INGRAIN] =
    {
        .effect = EFFECT_INGRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1, //is end turn effect so wouldn't change it overall
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Ingrain,
    },

    [MOVE_SUPERPOWER] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_DEF_DOWN,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_LOCK_ON, COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_Superpower,
    }, //yeah this is low recoil, double edge is medium recoil 33%
    //could reset back, but only reason to keep as is
    //would be contrary strats which only spinda could do
    //nd I want more recoil moves to show off the effect rebalance
    //think may increase to medium recoil effect? think this is low recoil?
    //ah yeah spinda doesn't even get this move naturally its a hidden event thing only in platinum
    //gave to spinda, and reset back to normal effects
    //removed from most mon distribution as worse close combat
    //replaced w recoil version, but will add back
    //just to have an option
    //actually no I'll just turn it into a tm

    [MOVE_MAGIC_COAT] =
    {
        .effect = EFFECT_MAGIC_COAT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 2,  //added 1 priority back, so can contest with prankster status, not a full block would rely on speed, nvm most prankster mon are fastr than mon that get this
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MagicCoat,
    },//removed priority move becomes 3 turn effect

    [MOVE_RECYCLE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_RECYCLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,  //stall strats add to list too strong to boost priority
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Recycle,
    },

    [MOVE_REVENGE] =
    {
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -4,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_REVENGE,
        //.contestComboMoves = {COMBO_STARTER_PAYBACK},
        //.battleAnimScript = gBattleAnimMove_Revenge,
    },

    [MOVE_BRICK_BREAK] =
    {
        .effect = EFFECT_BRICK_BREAK,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_BrickBreak,
    },

    [MOVE_YAWN] =
    {
        .effect = EFFECT_YAWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_YAWN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Yawn,
    },

    [MOVE_KNOCK_OFF] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 60,
        #else
            .power = 20,
        #endif
        .effect = EFFECT_KNOCK_OFF,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        //.battleAnimScript = gBattleAnimMove_KnockOff,
    },//took riggamarolled idea remove dmg boost


    [MOVE_ENDEAVOR] =
    {
        .effect = EFFECT_ENDEAVOR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ENDURE},
        //.battleAnimScript = gBattleAnimMove_Endeavor,
    },

    [MOVE_ERUPTION] =
    {
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_EARTHQUAKE, COMBO_STARTER_ENDURE, COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_Eruption,
    },

    [MOVE_SKILL_SWAP] =
    {
        .effect = EFFECT_SKILL_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SkillSwap,
    },//ability swap

    [MOVE_IMPRISON] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_IMPRISON,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .forcePressure = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Imprison,
    }, //seals opponent move if shared by user
    //thought about raising to plus 2 priority but since you want slower mon 
    //to operate in trick room a fast mon with imprison should still counter them


    [MOVE_REFRESH] =
    {
        .effect = EFFECT_REFRESH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SING, COMBO_STARTER_WATER_SPORT},
        //.battleAnimScript = gBattleAnimMove_Refresh,
    },

    [MOVE_GRUDGE] =
    {
        .effect = EFFECT_GRUDGE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CURSE},
        //.battleAnimScript = gBattleAnimMove_Grudge,
    },
    //change effect instead of reduce last move to 0
    //cut all pp in half

    [MOVE_SNATCH] =
    {
        .effect = EFFECT_SNATCH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .forcePressure = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Snatch,
    },

    [MOVE_SECRET_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SECRET_POWER,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SecretPower,
    },

    [MOVE_DIVE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 80,
        #else
            .power = 60,
        #endif
        .effect = EFFECT_SEMI_INVULNERABLE,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNHIDUNDERWATER, .status = STATE_UNDERWATER },
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_DIVE,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SURF},
        //.battleAnimScript = gBattleAnimMove_Dive,
    },

    [MOVE_ARM_THRUST] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_ArmThrust,
    },

    [MOVE_CAMOUFLAGE] =
    {
        .effect = EFFECT_CAMOUFLAGE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Camouflage,
    }, //change type based on bg environment

    [MOVE_TAIL_GLOW] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .effect = EFFECT_SPECIAL_ATTACK_UP_3,
        #else
            .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        #endif
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TailGlow,
    },

    [MOVE_LUSTER_PURGE] =
    {
        .effect = EFFECT_HIT,
        .power = 95, //gen 9 power upgrade
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_LusterPurge,
    },

    [MOVE_MIST_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_MistBall,
    },//somehow always thought this was a fairy move but it was psychic

    [MOVE_FEATHER_DANCE] =
    {
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .danceMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FeatherDance,
    },

    [MOVE_TEETER_DANCE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            #else
            #endif
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 1,
        .split = SPLIT_STATUS,
        .danceMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TeeterDance,
    },//think pair well w telepathy see if /make sure telepathy counts for this
    //and not just damaging moves
    //vsonic

    [MOVE_BLAZE_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .enhancedCritrate = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_BlazeKick,
    },

    [MOVE_MUD_SPORT] =
    {
        .effect = EFFECT_MUD_SPORT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1, //usually used for slow mon, make priority to get the benefit
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_MUD_SPORT,
        //.contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM, COMBO_STARTER_WATER_SPORT},
        //.battleAnimScript = gBattleAnimMove_MudSport,
    },

    [MOVE_ICE_BALL] =
    {
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .instructBanned = TRUE,
        .multiTaskBanned = TRUE,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_IceBall,
    },

    [MOVE_NEEDLE_ARM] =
    {

        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .evasiveBreak = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NeedleArm,
    }, //equivalent to punching moves/ mega punch

    [MOVE_SLACK_OFF] =
    {
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SlackOff,
    }, //could make tm, but then no one would use rest

    [MOVE_HYPER_VOICE] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSE,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HyperVoice,
    }, //didn't realize changing moves to sound would exclude from normal transformation abilities like pixelate etc.
    //could make sound type included in those abilities, but will be a trade off, since sound moves have their own effectiveness?
    //yeah go ahead and do that, would be a small trade off to the ability, - done, but just for pixilate idea fairy singing

    [MOVE_TOXIC_FANG] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
        #else
        #endif
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = 40,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        /*.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},*/
        //.battleAnimScript = gBattleAnimMove_PoisonFang,
    }, //potentially lower this? since I changed poison this is technically even easier to set toxic with
    //should I give this small flinch chance? since is biting move, would give 10%

    [MOVE_CRUSH_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_CrushClaw,
    },

    [MOVE_BLAST_BURN] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_BlastBurn,
    },

    [MOVE_HYDRO_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_HydroCannon,
    },

    [MOVE_METEOR_MASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 100,
            .accuracy = 90,
        #else
            .power = 100,
            .accuracy = 85,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_STEEL,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MeteorMash,
    },

    [MOVE_SPOOK] =
    {

        .power = 30,
        .accuracy = 100,
        .effect = EFFECT_HIT,
        .type = TYPE_GHOST,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .evasiveBreak = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Astonish,
    },
    //previously astonish
    //added to sound list after realized was based on voice
    //hmm matter of fact I thinkm I'm gonna rename this move, its a ghost move
    //and the name just doesn't really fit, same as how sonic boom didn't fit for what was 

    [MOVE_WEATHER_BALL] =
    {
        .effect = EFFECT_HIT,//EFFECT_WEATHER_BALL, //can just use effect hit now
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SANDSTORM, COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_WeatherBall,
    },
    //think fine to buff this up to 60, almost no one gets it
    //plus the required setup, mostly just for mega pidgeot buff
    //oh no they gave a lot more mon weather ball o.0

    [MOVE_AROMATHERAPY] =
    {
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Aromatherapy,
    },

    [MOVE_FAKE_TEARS] =
    {
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FakeTears,
    },

    [MOVE_AIR_CUTTER] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 55,
        #else
            .power = 55,
        #endif
        .effect = EFFECT_HIT, //think drop back to 55
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .slicingMove = TRUE,
        .enhancedCritrate = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AirCutter,
    },
    //unique point is it can't miss/100% accurate
    //hmm actually think will make this special aerial ace
    //nah aerial ace needs its own niche
    //may drop to 50 compare to disarming voice

    [MOVE_OVERHEAT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 130,
            #elif B_UPDATED_MOVE_DATA == GEN_4 || B_UPDATED_MOVE_DATA == GEN_5
            .power = 140,
            #else
            .power = 140,
            #endif
        .effect = EFFECT_HIT,  
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_Overheat,
    },//think may still change this to a low recoil move
    //just to boost back up fire type offense

    [MOVE_ODOR_SLEUTH] =
    {
        .accuracy = 0,
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_OdorSleuth,
    },

    [MOVE_ROCK_TOMB] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 60,
            .accuracy = 95,
            .pp = 15,
        #else
            .power = 50,
            .accuracy = 80,
            .pp = 10,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_ROCK,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        //.battleAnimScript = gBattleAnimMove_RockTomb,
    },

    [MOVE_SILVER_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SilverWind,
    },

    [MOVE_METAL_SOUND] =
    {
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_METAL_SOUND,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MetalSound,
    },//cacophony boost drop 3 // think too much instead boost accuracy to 100

    [MOVE_GRASS_WHISTLE] =
    {
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //since this keeps opponent from attacking will keep base priority
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GrassWhistle,
    }, //equal acc to sleep powder
    //lower acc than spore and sleep powder already exists
    //only reason to use thisi is to have a sleep move that can also hit grass types?
    //well its also a sound move so coincidentally has the niche of pairing with
    //cacophony for more consistent/useful sleep
    //would always be 5 turns of sleep

    [MOVE_TICKLE] =
    {
        .effect = EFFECT_TICKLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Tickle,
    },

    [MOVE_COSMIC_POWER] =
    {
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CosmicPower,
    },

    [MOVE_WATER_SPOUT] =
    {
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_WaterSpout,
    },

    [MOVE_SIGNAL_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SignalBeam,
    },

    [MOVE_SHADOW_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShadowPunch,
    },

    [MOVE_EXTRASENSORY] =
    {

        .pp = 30,
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .evasiveBreak = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Extrasensory,
    },

    [MOVE_SKY_UPPERCUT] =
    {
        .effect = EFFECT_HIT, //doesnt do anything goes to hit, can change to hit
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_SkyUppercut,
    },

    [MOVE_SAND_TOMB] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 30,
            .accuracy = 90,
        #else
            .power = 15,
            .accuracy = 70,
        #endif
        .effect = EFFECT_HIT,  //all trap effects have 100 secondary chance want to change so can use effect chance for argument extra effect
        .type = TYPE_GROUND,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED, //also rather than just buff damage for traps give each unique trap its own debuff style trap effect
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_SAND_TOMB,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SANDSTORM},
        //.battleAnimScript = gBattleAnimMove_SandTomb,
    },//clamp = flinch sand tomb = lower accuracy for duration whirlpool = lower speed for duration etc.
    //for sky attack argumenttomoveeffect script command went before hitfromacccheck so before dmg & animation stuff
    //sky attack won't work for tis its 2 battlescripts intead of one, instead think emulate relic song
    //it uses seteffectwithchance followed by argumentstatuseffect right before try faint mon & move end try to that but with argumenttomoveeffect

    [MOVE_SHEER_COLD] =
    {
        .effect = EFFECT_OHKO,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = -5,
        .split = SPLIT_SPECIAL,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_SheerCold,
    },

    [MOVE_MUDDY_WATER] =
    {
        .power = 65, //95
        .effect = EFFECT_TWO_TYPED_MOVE,  //    EFFECT_HIT
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        .damagesUnderwater = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_MuddyWater,
       .argument = { .storedValue = TYPE_GROUND },
    },//think want to make into two typed move, make custom effect so can set accuracy drop in bs would drop power to compensate
    //thinking water//ground bp 65, would still be strong as most things weak to water are also weak to ground
    //can potentially do accuracy drop with call_if?  since tink two typed effect doesn't actually set anything to move effect?
    //works!  two typed move and also drops accuracy
    

    [MOVE_BULLET_SEED] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 25,
        #else
            .power = 10,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .ballisticMove = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_BulletSeed,
    },

    [MOVE_AERIAL_ACE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AerialAce,
    },
    //potentially make this speed up hit nah already made flying speed boost 
    //just need to give it more spread

    [MOVE_ICICLE_SPEAR] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 25,
        #else
            .power = 10,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IcicleSpear,
    },

    [MOVE_IRON_DEFENSE] =
    {
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IronDefense,
    },

    [MOVE_BLOCK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            #else
            #endif
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Block,
    },

    [MOVE_HOWL] =
    {
        .effect = EFFECT_ATTACK_UP_USER_ALLY, //gen 8 boosts attkck for whole side, nice.   //try put in double wilds should be funny
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Howl,
    },

    [MOVE_DRAGON_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        //.battleAnimScript = gBattleAnimMove_DragonClaw,
    },

    [MOVE_FRENZY_PLANT] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_FrenzyPlant,
    },

    [MOVE_BULK_UP] =
    {
        .effect = EFFECT_BULK_UP,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BulkUp,
    },

    [MOVE_BOUNCE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNSPRANGUP, .status = STATE_ON_AIR },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Bounce,
    },
    //buffed acc so can work as alt option to floaty fall
    //make both into tms

    [MOVE_MUD_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SANDSTORM},
        //.battleAnimScript = gBattleAnimMove_MudShot,
    }, //ranged attack so potentially set dmg airborne
    

    [MOVE_POISON_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PoisonTail,
    },

    [MOVE_COVET] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 60,
            .pp = 25,
            #elif B_UPDATED_MOVE_DATA == GEN_5
            .power = 60,
            .pp = 40,
            #elif B_UPDATED_MOVE_DATA == GEN_4
            .power = 40,
            .pp = 40,
            #else
            .power = 40,
            .pp = 40,
            #endif
        .effect = EFFECT_STEAL_ITEM,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Covet,
    },

    [MOVE_VOLT_TACKLE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .recoilMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_MED_RECOIL,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_VoltTackle,
    },

    [MOVE_MAGICAL_LEAF] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_MagicalLeaf,
    },

    [MOVE_WATER_SPORT] =
    {
        .effect = EFFECT_WATER_SPORT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_WATER_SPORT,
        //.contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_WaterSport,
    },

    [MOVE_CALM_MIND] =
    {
        .effect = EFFECT_CALM_MIND,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_CALM_MIND,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CalmMind,
    },

    [MOVE_LEAF_BLADE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .power = 90,
        #else
            .power = 70,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LeafBlade,
    },

    [MOVE_DRAGON_DANCE] =
    {
        .effect = EFFECT_DRAGON_DANCE,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_DRAGON_DANCE,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        //.battleAnimScript = gBattleAnimMove_DragonDance,
    },

    [MOVE_ROCK_BLAST] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .accuracy = 90,
            #elif B_UPDATED_MOVE_DATA == GEN_5 || B_UPDATED_MOVE_DATA == GEN_6
            .accuracy = 90,
            #else
            .accuracy = 80,
            #endif
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_ROCK,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .ballisticMove = TRUE,
        .variableMultihit = TRUE,
        .damagesAirborneDoubleDamage = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RockBlast,
    }, //give to sandshrew
    //considering if should downgrade to just dmg in air, fly is rare
    //but doubling damage effectively turns this into explosion,
    //and logically you wouldn't hit all 5, yeah this shoul just be hit in air
    //put 2x back to make diff to spike cannon on top of lower acc
    //on the otehr hand nothing ever uses fly...
    //hmm if I made sky attack an in the air charge move maybe 
    //it'd see more use...

    [MOVE_SHOCK_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_ShockWave,
    },

    [MOVE_WATER_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_WaterPulse,
    },

    [MOVE_DOOM_DESIRE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 140,
            .accuracy = 100,
        #else
            .power = 120,
            .accuracy = 85,
        #endif
        .effect = EFFECT_FUTURE_SIGHT,
        .type = TYPE_STEEL,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DoomDesire,
    },

    [MOVE_PSYCHO_BOOST] =
    {
        .effect = EFFECT_HIT,  //changed to MOVE_EFFECT_MEDIUM_RECOIL
        .power = 140,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CALM_MIND},
        //.battleAnimScript = gBattleAnimMove_PsychoBoost,
    },

    [MOVE_ROOST] =
    {
        .effect = EFFECT_ROOST,//EFFECT_ROOST,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_BRAVE_BIRD},
        //.battleAnimScript = gBattleAnimMove_Roost,
    },//with new change don't want to give this priority boost
    //as move now does end turn healing, hmm or does it not heal on
    //turn its used...ok yeah it doesn't end turn heal on that turn

    [MOVE_GRAVITY] =
    {
        .effect = EFFECT_GRAVITY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Gravity,
    },

    [MOVE_MIRACLE_EYE] =
    {
        .effect = EFFECT_MIRACLE_EYE,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MiracleEye,
    },//removes type immunity, i.e psychic can hit dark
    //make change effect to work like EFFECT_TARGET_TYPE_DAMAGE
    //can put in same place and have argument be type it removes immunity
    //vsonic important,  
    //nvm since is specific to immunity from a certain type
    //would require two type arguments
    //unless the effect is to fully remove immunity
    //since foresight is normal but targets ghosts
    //and removes both its normal and fighting immunity
    //this targets dark and its only immunity is psychic
    //ok I think if I change it to that, then it can work
    //technically matches default effect
    //but still slightly different in execution
    //realized dont need separate effect to do effect
    //no real benefit to consolidating

    [MOVE_WAKE_UP_SLAP] =
    {
        .power = 70,
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .status = STATUS1_SLEEP },
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WakeUpSlap,
    },
    //this is balanced better by my given status changes

    [MOVE_HAMMER_ARM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_HammerArm,
    },

    [MOVE_GYRO_BALL] =
    {
        .effect = EFFECT_GYRO_BALL,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GyroBall,
    },

    [MOVE_HEALING_WISH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_HEALING_WISH,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = -1, //to keep new mon from taking switchin dmg
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HealingWish,
    },//vsonic important look into modern affect in EE
    //as it suposedly changes when mon gets switched in I assume to prevent switch in dmg
    //seem if could work for this and momento, if not keep negative priority

    [MOVE_BRINE] =
    {
        .effect = EFFECT_BRINE,
        .power = 75,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Brine,
    },
    //slight buff to make more competitively viable

    [MOVE_NATURAL_GIFT] =
    {
        .effect = EFFECT_NATURAL_GIFT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NaturalGift,
    },
    //also effect wasn't setup...
    //changed to no longer remove item on use
    //alowing move to be reused similar to hidden power
    //but requiring item slot
    //stops working when berry gets consumed/used
    //makes physical counterpart to hidden power
    //names work well together too.


    [MOVE_FEINT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 35,
            #elif B_UPDATED_MOVE_DATA >= GEN_5
            .power = 30,
            #else
            .power = 50,
            #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .split = SPLIT_PHYSICAL,
        .ignoresProtect = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),*/
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Feint,
    }, //hits and removes protect likes, decided to make fighting, as a counter part to brick break

    [MOVE_PLUCK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BUG_BITE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Pluck,
    },
    //sharpness/crit doesn't make sense overall it alrady does all it needs to.

    [MOVE_TAILWIND] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 15,
        #else
            .pp = 30,
        #endif
        .effect = EFFECT_TAILWIND,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,//think affect is too strong to be given priority, same as rest
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .windMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Tailwind,
    },//vsonic important

    [MOVE_ACUPRESSURE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_ACUPRESSURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER | MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Acupressure,
    },

    [MOVE_METAL_BURST] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_4
            #else
            #endif
        .effect = EFFECT_METAL_BURST,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS, //potentially look at this for figuring  set targetting for lightning rod
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .meFirstBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_METAL_SOUND},
        //.battleAnimScript = gBattleAnimMove_MetalBurst,
    }, //think this couter move

    [MOVE_U_TURN] =
    {
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_UTurn,
        
    },//too good, and too wide spread to have infestation,
    //want to be mostly on bugs, w a rare mon being able to get access that isn't bug type

    [MOVE_CLOSE_COMBAT] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        //.battleAnimScript = gBattleAnimMove_CloseCombat,
    }, //remove iron fist flag, as want to emphasize superpower instead

    [MOVE_PAYBACK] =
    {
        .effect = EFFECT_PAYBACK,
        .power = 50,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_PAYBACK,
        //.contestComboMoves = {COMBO_STARTER_REVENGE},
        //.battleAnimScript = gBattleAnimMove_Payback,
    },
    //check effect see how will use,
    //as effect changed w gens
    //research deside how will setup
    //vsonic
    //w status change think too easy to get boost
    //think will change to specifically an attack
    //has to have been used beforehand
    //i.e add check for lastusedmove by target is not status
    //not many mon get it, could instead just move higher in
    //learnsets and replace w insurance at low level if really 
    //want a dark move

    [MOVE_ASSURANCE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 60,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_ASSURANCE,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_PAYBACK, COMBO_STARTER_REVENGE},
        //.battleAnimScript = gBattleAnimMove_Assurance,
    },

    [MOVE_EMBARGO] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_EMBARGO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Embargo,
    },

    [MOVE_FLING] =
    {
        .effect = EFFECT_FLING,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Fling,
    },

    [MOVE_PSYCHO_SHIFT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 100,
        #else
            .accuracy = 90,
        #endif
        .effect = EFFECT_PSYCHO_SHIFT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PsychoShift,
    },//curses status1 and afflicts them to target

    [MOVE_TRUMP_CARD] =
    {
        .effect = EFFECT_TRUMP_CARD,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TrumpCard,
    },

    [MOVE_HEAL_BLOCK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_HEAL_BLOCK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_OPPONENTS_FIELD, // if setup rotation/triple battles may need to change this to opponent field target
        .priority = 2,  //added little priority to be able to pre-empt a heal.
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HealBlock,
    }, //make heal block stop potions etc.e simple enough just add clause to itemuse function i think
    //so healing items can't be used if target status is heal block
    //make sure to set as team/side wide status
    //vsonic important - also added extra priority to accont for status priority boosts

    [MOVE_WRING_OUT] =
    {
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WringOut,
        .argument = {.damagePercentage = 120},
    },
    //doublne check this think w power 0 it'll do typeless damage?
    //unsure if should be but seems fine?

    [MOVE_POWER_TRICK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_POWER_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PowerTrick,
    },

    [MOVE_GASTRO_ACID] =
    {
        .effect = EFFECT_GASTRO_ACID,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GastroAcid,
    },

    [MOVE_LUCKY_CHANT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_LUCKY_CHANT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_LUCKY_CHANT,
        //.contestComboMoves = {COMBO_STARTER_HEAL_BELL},
        //.battleAnimScript = gBattleAnimMove_LuckyChant,
    },

    [MOVE_ME_FIRST] =
    {
        .effect = EFFECT_ME_FIRST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,//leaving as is since calling a move
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MeFirst,
    },

    [MOVE_COPYCAT] =
    {
        .effect = EFFECT_COPYCAT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 1,//must go first
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Copycat,
    },

    [MOVE_POWER_SWAP] =
    {
        .effect = EFFECT_POWER_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PowerSwap,
    },

    [MOVE_GUARD_SWAP] =
    {
        .effect = EFFECT_GUARD_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GuardSwap,
    },

    [MOVE_PUNISHMENT] =
    {
        .effect = EFFECT_PUNISHMENT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Punishment,
    },

    [MOVE_LAST_RESORT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .power = 140,
        #else
            .power = 130,
        #endif
        .effect = EFFECT_LAST_RESORT,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LastResort,
    },

    [MOVE_WORRY_SEED] =
    {
        .effect = EFFECT_OVERWRITE_ABILITY,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .argument = { .storedValue = ABILITY_INSOMNIA },
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_WORRY_SEED,
        //.contestComboMoves = {COMBO_STARTER_LEECH_SEED},
        //.battleAnimScript = gBattleAnimMove_WorrySeed,
    },//makes target ability insomnia
    //for some reason this broke game?
    //or it breaks starter battle
    //changed to use call native now works

    [MOVE_SUCKER_PUNCH] =
    {

        .power = 65,    //LOWEred power by 5 to counter pp increase, making it harder to stall out, test and consider
        .effect = EFFECT_SUCKER_PUNCH,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .punchingMove = TRUE,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SuckerPunch,
    },//remove pp increase on things like megsa
    //pp stalling is the only way to stay alive
    //as I saw playing unbreakable ties
    //applied late gen power drop
    //iron fist on this is slightly nutty, lowered bp further
    //thankfully only one dark mon with both sucker punch and iron fist - pangooro...

    [MOVE_TOXIC_SPIKES] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_TOXIC_SPIKES,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = TRUE,
        .forcePressure = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ToxicSpikes,
    },

    [MOVE_HEART_SWAP] =
    {
        .effect = EFFECT_HEART_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HeartSwap,
    },//swap stat stages

    [MOVE_AQUA_RING] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_AQUA_RING,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AquaRing,
    },

    [MOVE_MAGNET_RISE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_MAGNET_RISE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .gravityBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MagnetRise,
    },
    //makes float

    [MOVE_FLARE_BLITZ] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .recoilMove = TRUE,
        .thawsUser = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_MED_RECOIL,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_FlareBlitz,
    },

    [MOVE_FORCE_PALM] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ForcePalm,
    },

    [MOVE_AURA_SPHERE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 80,
        #else
            .power = 90,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AuraSphere,
    },

    [MOVE_ROCK_POLISH] =
    {
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RockPolish,
    },

    [MOVE_POISON_JAB] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PoisonJab,
    },

    [MOVE_DARK_PULSE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DarkPulse,
    },
    //think will buff this to give better dark special options
    //...this may be broken eh cut distribution to mostly dark types
    //hopefully that'll work

    [MOVE_NIGHT_SLASH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NightSlash,
    },

    [MOVE_AQUA_TAIL] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_AquaTail,
    },

    [MOVE_SEED_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ballisticMove = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SeedBomb,
    },

    [MOVE_AIR_SLASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 10,
            #elif B_UPDATED_MOVE_DATA == GEN_5
            .pp = 20,
            #else
            .pp = 20,
            #endif
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AirSlash,
    },
    //think will drop power on this by 10

    [MOVE_X_SCISSOR] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        //.battleAnimScript = gBattleAnimMove_XScissor,
    },

    [MOVE_BUG_BUZZ] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BugBuzz,
    },
    //potentially lower power back down
    //since I want bug to be a utility type
    //rather than a big dmg dealer

    [MOVE_DRAGON_PULSE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 85,
        #else
            .power = 90,  //unsure if want to reboost power
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DragonPulse,
    },//vsonic seems animation for this not right?

    [MOVE_DRAGON_RUSH] =
    {

        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_DRAGON,
        .accuracy = 80,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_DRAGON_RUSH,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_TAIL},
        //.battleAnimScript = gBattleAnimMove_DragonRush,
    },//slight power buff to compete w draco meteor

    [MOVE_POWER_GEM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 95,
        #else
            .power = 70,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PowerGem,
    },
    //turned into psychic
    //maybe should make base 95? doesn't have other effect
    //and is pretty much only accessible special rock move
    //yeah same as previous note for lack of better options
    //the strength of one thing is the strength of everything
    //so this needs to be ACTUALLY good

    [MOVE_DRAIN_PUNCH] =
    {
        .power = 60,
        .pp = 10,
        .effect = EFFECT_ABSORB,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_DrainPunch,
    },

    [MOVE_VACUUM_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_VacuumWave,
    },

    [MOVE_FOCUS_BLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        //.battleAnimScript = gBattleAnimMove_FocusBlast,
    },

    [MOVE_ENERGY_BALL] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 90,
        #else
            .power = 80,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_EnergyBall,
    },

    [MOVE_BRAVE_BIRD] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_MED_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_BRAVE_BIRD,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BraveBird,
    },
    //think leave crit off this, just let recoil rework be the buff

    [MOVE_EARTH_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_EarthPower,
    },

    [MOVE_SWITCHEROO] =
    {
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Switcheroo,
    }, //teach this
    //swaps items

    [MOVE_GIGA_IMPACT] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GigaImpact,
    },

    [MOVE_NASTY_PLOT] =
    {
        .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NastyPlot,
    },

    [MOVE_BULLET_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BulletPunch,
    },

    [MOVE_AVALANCHE] =
    {
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = -4,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Avalanche,
    },

    [MOVE_ICE_SHARD] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IceShard,
    },

    [MOVE_SHADOW_CLAW] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_GHOST,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShadowClaw,
    },

    [MOVE_THUNDER_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 15,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
        }),*/
    },

    [MOVE_ICE_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 15,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
        }),*/
    },

    [MOVE_FIRE_FANG] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 15,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
        }),*/
    }, //intuition was corret, well teh note was correct, the issue was use of effect_flinch_status
    //rather than my argument move effect setup, believe problem somehow linked to argumenttostatus command?
    //argument to status is meant ot be about the same as setting move effect to arg itself, 
    //but I never set arg with cmd arg var arg properly so its jumping wrong

    [MOVE_SHADOW_SNEAK] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShadowSneak,
    },

    [MOVE_MUD_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MudBomb,
    },
    

    [MOVE_PSYCHO_CUT] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PsychoCut,
    },

    [MOVE_ZEN_HEADBUTT] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .headbuttMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ZenHeadbutt,
    },

    [MOVE_MIRROR_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MirrorShot,
    },

    [MOVE_FLASH_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FlashCannon,
    }, //makes sense compared to aura sphere description, similar.
    //change mostly for a blastoise buff

    [MOVE_ROCK_CLIMB] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RockClimb,
    },

    [MOVE_DEFOG] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_DEFOG,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        //.ignoresSubstitute = TRUE, In Gen5+, the evasion drop will no longer bypass Substitute. However, this is tricky to code
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Defog,
    },

    [MOVE_TRICK_ROOM] =
    {
        .effect = EFFECT_TRICK_ROOM,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = -7,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TrickRoom,
    },

    [MOVE_DRACO_METEOR] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 130,
        #else
            .power = 140,
        #endif
        .effect = EFFECT_HIT,  //changed to MOVE_EFFECT_MEDIUM_RECOIL
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DracoMeteor,
    },

    [MOVE_DISCHARGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,    //keep for this, as is actually an indiscriminate attack
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_Discharge,
    },

    [MOVE_LAVA_PLUME] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,    //same logic as above 
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_LavaPlume,
    },

    [MOVE_LEAF_STORM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 130,
        #else
            .power = 140,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LeafStorm,
    },

    [MOVE_POWER_WHIP] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_PowerWhip,
    }, //add to tangela learnset

    [MOVE_ROCK_WRECKER] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RockWrecker,
    },

    [MOVE_CROSS_POISON] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_POISON,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CrossPoison,
    },

    [MOVE_GUNK_SHOT] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .accuracy = 85,
        #else
            .accuracy = 70,
        #endif
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_POISON,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GunkShot,
    },

    [MOVE_IRON_HEAD] =
    {

        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .headbuttMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IronHead,
    },

    [MOVE_MAGNET_BOMB] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MagnetBomb,
    },

    [MOVE_STONE_EDGE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .enhancedCritrate = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StoneEdge,
    },
    //there are very few rock moves
    //should I increase accuracy of this?
    //because of scarceness not really room
    //to have a move be bad just to make it an alternative
    //niche option to another move,
    //it just makes the entire move category bad.
    //ok other comparable moves are base 95 acc so yeah -_-

    [MOVE_CAPTIVATE] =
    {
        .effect = EFFECT_CAPTIVATE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARM},
        //.battleAnimScript = gBattleAnimMove_Captivate,
    },//lower stats if opposite gender

    [MOVE_STEALTH_ROCK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_STEALTH_ROCK,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .forcePressure = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StealthRock,
    },//check for how I adjusted stealth rock think I rebalanced it?
    //think if I don't want traps to auto be set in every match
    //I shouldn't give them priority, with ttk changes
    //and with planned guard mode, I think its safe enough to be
    //worth investement as is

    [MOVE_GRASS_KNOT] =
    {
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GrassKnot,
    },

    [MOVE_CHATTER] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 75,
            #elif B_UPDATED_MOVE_DATA == GEN_5
            .power = 60,
            #else
            .power = 60,
            #endif
        .effect = EFFECT_HIT,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,//change to target both with cacophony becomes guaranteed confuse
        .priority = 0,          //w max confuse odds
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .chance = 50,
        #elif B_UPDATED_MOVE_DATA >= GEN_5
            .chance = 10,
        #else
            .chance = 31,
        #endif
        }),*/
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Chatter,
    }, //did I intend this to eb a gauranteed confuse?
    //for this and other foncuse will use cacophonyboosted special status to allow to confuse bugs etc.
    //nvm that would be hell to setup just make confuse mon that otherwise block confuse
    //don't need do that, forgot was gonna set max turns
    //don't want to overwrite confuse immunity as that would run into new territory
    //of countering existing mechanics or blocking other ability effects, 
    //giving immunity is one thing
    //while that is another and would be a power creep

    [MOVE_JUDGMENT] =
    {
        .effect = EFFECT_JUDGMENT,
        .power = 100,
        .type = TYPE_MYSTERY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.argument = { .holdEffect = HOLD_EFFECT_PLATE },
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Judgment,
        //forgot changed to no longer need plate
    }, //thinik add message passed judgement def can no longer escape!
    //vsonic  //actually too strong, since this thing is already hella op
    //do second idea, and make random type that will do most damage to target
    //so rolls random move type as long as its super effective.
    //create string before effectieness read,  "Target name was Judged by X"
    //where X, is a standin for the type,
    //ex  dark type  Judged by Darkness
    //grass Judged by Nature,  Fairy = by The Fae
    //... or maybe  Target Name faced X Judgement?
    //Faced Fiery Judgment,  COld Judgment,  Fae Judgement? hmm
    //yeah I like that later better

    [MOVE_BUG_BITE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BUG_BITE,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BugBite,
    },

    [MOVE_CHARGE_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 70,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_ChargeBeam,
    },

    [MOVE_WOOD_HAMMER] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_MED_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WoodHammer,
    },

    [MOVE_AQUA_JET] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_AquaJet,
    },

    [MOVE_ATTACK_ORDER] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .enhancedCritrate = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 20, //potentially drop to 15
        }),*/
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_ATTACK_ORDER,
        //.contestComboMoves = {COMBO_STARTER_DEFEND_ORDER, COMBO_STARTER_HEAL_ORDER},
        //.battleAnimScript = gBattleAnimMove_AttackOrder,
    },

    [MOVE_DEFEND_ORDER] =
    {
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_DEFEND_ORDER,
        //.contestComboMoves = {COMBO_STARTER_ATTACK_ORDER, COMBO_STARTER_HEAL_ORDER},
        //.battleAnimScript = gBattleAnimMove_DefendOrder,
    },

    [MOVE_HEAL_ORDER] =
    {
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_HEAL_ORDER,
        //.contestComboMoves = {COMBO_STARTER_ATTACK_ORDER, COMBO_STARTER_DEFEND_ORDER},
        //.battleAnimScript = gBattleAnimMove_HealOrder,
    },

    [MOVE_HEAD_SMASH] =
    {
        .effect = EFFECT_RECOIL,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_HEAVY_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        .headbuttMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HeadSmash,
    },//consider raising accuracy vsonic double edge has triple pp and is 100% accurate
    //did boost acc from 85 to 90
    //think will go to 95 has heavy recoil and half the pp of most double edge likes
    //oh sorry a THIRD the pp 0.o  with just 30 more bp

    [MOVE_DOUBLE_HIT] =
    {
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DoubleHit,
    },

    [MOVE_ROAR_OF_TIME] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RoarOfTime,
    },

    [MOVE_SPACIAL_REND] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpacialRend,
    },

    [MOVE_LUNAR_DANCE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_HEALING_WISH,//nvm this is different its suppoed to recover pp as well
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = -1,//change ensure mon comes in last
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .danceMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LunarDance,
    },

    [MOVE_CRUSH_GRIP] =
    {
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP, //effect isn't setup...
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CrushGrip,
        .argument = {.damagePercentage = 150},
    },
    //may make this power 0 so it ignores type calc

    [MOVE_MAGMA_STORM] =
    {
        .power = 110,
        .accuracy = 85,
        .effect = EFFECT_HIT,   //no major buffs just accuracy buff w gauranteed burn which main game already added apparenlty
        .type = TYPE_FIRE,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_MAGMA_STORM,
        },
        {
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_MagmaStorm,
    },

    [MOVE_DARK_VOID] =
    {

        .accuracy = 80,
        .effect = EFFECT_NON_VOLATILE_STATUS,
        .power = 0,
        .type = TYPE_DARK,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0, //leave as is
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_SLEEP },
        .magicCoatAffected = TRUE,
        .sketchBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DarkVoid,
    },//instead of dropping accuracy just keep from being sketched by smeargle -_-

    [MOVE_SEED_FLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 40,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SeedFlare,
    },

    [MOVE_OMINOUS_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_OminousWind,
    },

    [MOVE_SHADOW_FORCE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 120,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1, //ironically description was vanished instantly
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .evasiveBreak = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_VANISHEDINSTANTLY, .status = STATE_PHANTOM_FORCE },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShadowForce,
    },
    //like phantom force this also ignores and removes protect
    //difference is this is giratina exclusive think can give prio boost
    //is "worst" legendary and meant to compete against the others
    //so now it can disappear first, and then rip away the protect
    //meant to block it at the start of the turn

    [MOVE_HONE_CLAWS] =
    {
        .effect = EFFECT_ATTACK_ACCURACY_UP,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HoneClaws,
    },

    [MOVE_WIDE_GUARD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_WIDE_GUARD },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WideGuard,
    },
    //vsonic potentialy add to more rock types

    [MOVE_GUARD_SPLIT] =
    {
        .effect = EFFECT_GUARD_SPLIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GuardSplit,
    },

    [MOVE_POWER_SPLIT] =
    {
        .effect = EFFECT_POWER_SPLIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PowerSplit,
    },

    [MOVE_WONDER_ROOM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .priority = 1,
        #else
            .priority = -7,
        #endif
        .effect = EFFECT_WONDER_ROOM,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WonderRoom,
    },//swap defense sp defense of all

    [MOVE_PSYSHOCK] =
    {
        .effect = EFFECT_PSYSHOCK,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Psyshock,
    },

    [MOVE_VENOSHOCK] =
    {
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS, //double damage if target poisoned
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .status = STATUS1_PSN_ANY },
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TOXIC},
        //.battleAnimScript = gBattleAnimMove_Venoshock,
    },

    [MOVE_AUTOTOMIZE] =
    {
        .effect = EFFECT_AUTOTOMIZE,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Autotomize,
    },

    [MOVE_RAGE_POWDER] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .priority = 2,
        #else
            .priority = 3,
        #endif
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .powderMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RagePowder,
    },

    [MOVE_TELEKINESIS] =
    {
        .effect = EFFECT_TELEKINESIS,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .gravityBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Telekinesis,
    },

    [MOVE_MAGIC_ROOM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .priority = 1,
        #else
            .priority = -7,
        #endif
        .effect = EFFECT_MAGIC_ROOM,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MagicRoom,
    },//blocks all item use on field,
    //with my embargo change this is kinda obsolete

    [MOVE_SMACK_DOWN] =
    {
        .effect = EFFECT_HIT, //sets move effect smack down which plays script and sets smack down status which grounds target
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SmackDown,
    }, //now that moved smackdown effect to flag, no longer need effect, repalce with hit,

    [MOVE_STORM_THROW] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 45,
        #else
            .power = 40,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .alwaysCriticalHit = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StormThrow,
    },
    //would be better if there were any fighting mon that
    //got sniper but its almost exclusively water types hmm
    //medicham maybe idea hit pressure points
    //or actually better to just make fighting version
    //so it makes sense?
    //precise strike

    [MOVE_FLAME_BURST] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLAME_BURST,
            .self = TRUE,
        },
        {
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*///vsonic hopefully can work burn burst target
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FlameBurst,
    },
    //may need to revise battle script to actually set adjacent burn effect
    //vsonic

    [MOVE_SLUDGE_WAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SludgeWave,
    },

    [MOVE_QUIVER_DANCE] =
    {
        .effect = EFFECT_QUIVER_DANCE,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_QuiverDance,
    },

    [MOVE_HEAVY_SLAM] =
    {
        .effect = EFFECT_HEAT_CRASH,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HeavySlam,
    },

    [MOVE_SYNCHRONOISE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 120,
            .pp = 10,
        #else
            .power = 70,
            .pp = 15,
        #endif
        .effect = EFFECT_SYNCHRONOISE,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Synchronoise,
    },
    //set effect to ignore resist
    //and give stab

    [MOVE_ELECTRO_BALL] =
    {
        .effect = EFFECT_ELECTRO_BALL,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ElectroBall,
         /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
    },
    //saw damage function this move is practicaly useless.
    //on average would only ever be base 50 power
    //change to be a more dynamic formulal like gyro ball 
    //also give a paralyze chance
    //THINK press L to show move power in battle window
    //replace pp and type data

    [MOVE_SOAK] =
    {
        .effect = EFFECT_SOAK,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .storedValue = TYPE_WATER },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Soak,
    }, //set type to water

    [MOVE_FLAME_CHARGE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FlameCharge,
    },

    [MOVE_COIL] =
    {
        .effect = EFFECT_COIL,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Coil,
    },

    [MOVE_LOW_SWEEP] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 65,
        #else
            .power = 60,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LowSweep,
    },

    [MOVE_ACID_SPRAY] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AcidSpray,
    },

    [MOVE_FOUL_PLAY] =
    {
        .effect = EFFECT_FOUL_PLAY,
        .power = 95,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FoulPlay,
    },

    [MOVE_SIMPLE_BEAM] =
    {
        .effect = EFFECT_OVERWRITE_ABILITY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .argument = { .storedValue = ABILITY_SIMPLE },
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SimpleBeam,
    },//set target ability to simple - doubles stat changes

    [MOVE_ENTRAINMENT] =
    {
        .effect = EFFECT_ENTRAINMENT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Entrainment,
    },//makes target ability same as user
    //look into move, this seems like a good tm?
    //vsonic important

    [MOVE_AFTER_YOU] =
    {
        .effect = EFFECT_AFTER_YOU,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AfterYou,
    },//makes target move after user, only useful for doubles+
    //this will be a huge change, before would be used to speed up slower mon
    //but now would function like helping hand, where I boost their priority to the top

    [MOVE_ROUND] =
    {
        .effect = EFFECT_ROUND,
        .power = 60,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ROUND,
        }),*/
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Round,
    },

    [MOVE_ECHOED_VOICE] =
    {
        .effect = EFFECT_ECHOED_VOICE,
        .power = 40,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_EchoedVoice,
    },

    [MOVE_CHIP_AWAY] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetDefenseEvasionStages = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ChipAway,
    },//think change to unique effect, ignores changes to def stat and evasion stat of target
    //would like make special veriant for normal 
    //ahh seems effect was never set...
    //ahh done w flag instead my bad

    [MOVE_CLEAR_SMOG] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CLEAR_SMOG,
        }),*/
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ClearSmog,
    },

    [MOVE_STORED_POWER] =
    {
        .effect = EFFECT_STORED_POWER,
        .power = 20,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StoredPower,
    },//potentially use with moody mon

    [MOVE_QUICK_GUARD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_QUICK_GUARD, },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_QuickGuard,
    },//make sure this is using correct effect and doesn't have decreasing odds each use
    //check how works as meant to stop all priority moves - works
    //sets sidestatus  on move not effect

    [MOVE_ALLY_SWITCH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .priority = 2,
        #else
            .priority = 1,
        #endif
        .effect = EFFECT_ALLY_SWITCH,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AllySwitch,
    },

    [MOVE_SCALD] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .thawsUser = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 25,
        }),*///vsonic should I drop this to 25?
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SCALD,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Scald,
    },

    [MOVE_SHELL_SMASH] =
    {
        .effect = EFFECT_SHELL_SMASH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = -1, //this functions better if last
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShellSmash,
    },//alrigth every mon that learns this is slow, so will just make negative priority

    [MOVE_HEAL_PULSE] =
    {
        .effect = EFFECT_HEAL_PULSE, //missed this healing move, kept normal healing for mega launcher
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .pulseMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HealPulse,
    },
    //give blastoise heal pulse
    //heal pulse is meant to have long rage,
    //should be able to target anyone even in a triple battle

    [MOVE_HEX] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 65,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,   //effect not in bs commands, its in pokemon.c effectively just does hit otherwise
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .status = STATUS1_ANY },
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TOXIC},
        //.battleAnimScript = gBattleAnimMove_Hex,
    },

    [MOVE_SKY_DROP] =
    {
        .effect = EFFECT_SKY_DROP, // Needs a custom move effect
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .ignoresRedirection = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNTOOKTARGETHIGH, .status = STATE_ON_AIR },
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SkyDrop,
    },//vsonic never tested if works

    [MOVE_SHIFT_GEAR] =
    {
        .effect = EFFECT_SHIFT_GEAR,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShiftGear,
    },

    [MOVE_CIRCLE_THROW] =
    {
        .effect = EFFECT_HIT_SWITCH_TARGET,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CircleThrow,
    },

    [MOVE_INCINERATE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 60,
        #else
            .power = 30,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INCINERATE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Incinerate,
    },

    [MOVE_QUASH] =
    {
        .effect = EFFECT_QUASH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Quash,
    },
    //opposite of after you, makes target act last
    //like after you this is a massive buff

    [MOVE_ACROBATICS] =
    {
        .effect = EFFECT_ACROBATICS,
        .power = 55,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Acrobatics,
    },
    //ground dwelling mon can use and its used a lot to hit flying 
    //or other enemies that need to be attacked in unique ways so make hit floating

    [MOVE_REFLECT_TYPE] =
    {
        .effect = EFFECT_REFLECT_TYPE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ReflectType,
    },//is just conversion, but with greater access
    //copies target's type(s)

    [MOVE_RETALIATE] =
    {
        .effect = EFFECT_RETALIATE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Retaliate,
    },

    [MOVE_FINAL_GAMBIT] =
    {
        .effect = EFFECT_FINAL_GAMBIT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FinalGambit,
    },
    //review this may have changed effect
    //think will revert my change didn't initially
    //understand use case for move
    //vsonic important
    //effect is damage equals remainig hp,
    //I changed to dmg equals lost hp
    //so you could still get effect out of the mon
    //vs needing to use it, as soon as it hit the field
    //but if I do it as a last ditch effort, 
    //its easier to use but overall the overall damage output
    //is also lower, which balances I guess
    //with being able to do damage before using the move

    [MOVE_BESTOW] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            #else
            #endif
        .effect = EFFECT_BESTOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Bestow,
    },//gives held item to target
    //this I feel should probably keep where it is?
    //just because it seems like something where strategies are already locked in and very specific
    //nvm seems bestoy strats aren't really a thing, otehr than to throw away bad items?

    [MOVE_INFERNO] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Inferno,
    },

    [MOVE_WATER_PLEDGE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 80,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_PLEDGE,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WaterPledge,
    },

    [MOVE_FIRE_PLEDGE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 80,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_PLEDGE, //need finish setup effect for this vsonic
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FirePledge,
    },

    [MOVE_GRASS_PLEDGE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 80,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_PLEDGE,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GrassPledge,
    },

    [MOVE_VOLT_SWITCH] =
    {
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_VoltSwitch,
    },

    [MOVE_STRUGGLE_BUG] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 40,
        #else
            .power = 30,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StruggleBug,
    }, //hm so is this guaranteed both?if so its VERY good now, yup looks like it
    //put this exclusively in pre evo bug learnset not full evo
    //ex caterpie, not kakuna and butterfree
    //hmm unsure when or why but i made this physical when base game has it as special
    //90% bugs are physical so its fine imo, may lower power even further
    //since effect is so good, honestly is prob best bug move,
    //the only thing keeping it from being broken is that it isn't a status move
    //vsonic

    [MOVE_BULLDOZE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Bulldoze,
    },
    //gave underground boost but otherwise change targetting to make it more accessible version of earthquake

    [MOVE_FROST_BREATH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 55,
        #else
            .power = 40,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .alwaysCriticalHit = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FrostBreath,
    },//add to more learnsets
    //almost better than blizzard, difference is no acc boost in hail

    [MOVE_DRAGON_TAIL] =
    {
        .effect = EFFECT_HIT_SWITCH_TARGET,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_DRAGON_TAIL,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH},
        //.battleAnimScript = gBattleAnimMove_DragonTail,
    },

    [MOVE_WORK_UP] =
    {
        .effect = EFFECT_ATTACK_SPATK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WorkUp,
    },

    [MOVE_ELECTROWEB] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Electroweb,
    },

    [MOVE_WILD_CHARGE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_LIGHT_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WildCharge,
    },

    [MOVE_DRILL_RUN] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DrillRun,
    },

    [MOVE_DUAL_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DualChop,
    },//renamed dual chop

    [MOVE_HEART_STAMP] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HeartStamp,
    },

    [MOVE_HORN_LEECH] =
    {
        .effect = EFFECT_ABSORB,
        .power = 85,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HornLeech,
    },

    [MOVE_SACRED_SWORD] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 15,
        #else
            .pp = 20,
        #endif
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetDefenseEvasionStages = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SacredSword,
    },

    [MOVE_RAZOR_SHELL] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RazorShell,
    },

    [MOVE_HEAT_CRASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            #else
            #endif
        .effect = EFFECT_HEAT_CRASH,
        .power = 1,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HeatCrash,
    },

    [MOVE_LEAF_TORNADO] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LeafTornado,
    },

    [MOVE_STEAMROLLER] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Steamroller,
    },

    [MOVE_COTTON_GUARD] =
    {
        .effect = EFFECT_DEFENSE_UP_3,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CottonGuard,
    },

    [MOVE_NIGHT_DAZE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 40,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NightDaze,
    },

    [MOVE_PSYSTRIKE] =
    {
        .effect = EFFECT_PSYSHOCK,
        .power = 120,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Psystrike,
    },//mewtwo signature

    [MOVE_TAIL_SLAP] =
    {
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .makesContact = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TailSlap,
    },

    [MOVE_HURRICANE] =
    {

        .power = 120,
        .effect = EFFECT_HIT, //does confusion
        .type = TYPE_FLYING,
        .accuracy = 80,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .slicingMove = TRUE,
        .damagesAirborneDoubleDamage = TRUE,
        .alwaysHitsInRain = TRUE,
        .accuracy50InSun = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Hurricane,
    },
    //may change to more literal translation 
    //'Windstorm' cutting wind attack
    //rn is pretty much best flying move, which honestly I think it should be
    //its just very inaccurate
    //oh hurricane does make sense it has a rain based component
    //w that in mind dropped crit, but keep sharpness boost

    [MOVE_HEAD_CHARGE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_LIGHT_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        .headbuttMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HeadCharge,
    },

    [MOVE_GEAR_GRIND] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GearGrind,
    },

    [MOVE_SEARING_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,    //is similar to lava plume so keep
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SearingShot,
    },

    [MOVE_TECHNO_BLAST] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 120,
        #else
            .power = 85,
        #endif
        .effect = EFFECT_CHANGE_TYPE_ON_ITEM,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .holdEffect = HOLD_EFFECT_DRIVE },
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TechnoBlast,
    },
    //may give move property so can distinguish between the moves
    //of shared effect
    //PROB best to just do same thing I did with judgment
    //think will change effect of plates and drive
    //drive especially has little use
    //so what think will do is give it a type resist
    //so fire drive would give you a resistance to fire type moves for genesect
    //hmm ok think do something different for plates
    //rather than giving single type waakness since would be worse
    //than its existing effect would set to give type attribute and benefits
    //so give type affinity i.e fire cant be burned
    //and then also give the benefit of the types resistances
    //but without becoming said type
    //think check type argument from plate fire plate
    //integrate with type check, when found item
    //check if attack type would be resisted by item arg type
    //if so calc damage using said type
    //sounds good, think will make memories do same thing as drive
    //to drive home its not arceus
    //or keep memories to default
    //yeah think like that better that way memories and plates
    //are similarly linked while drive gets its own
    //distinct effect
    //since type is a loop and odd
    //think best way is just do a 50% power drop
    //if atk type matches drive type
    //and w technoblast separted from drive
    //can have a way to use the move
    //while having a separte option to use the drive


    //potentially change cosmetic form species 
    //to just be same as how ogerpon etc. was handled
    //but idk if that actually saves any space
    //or if its just a visual distinction
    //ahh EE already did that
    //ok unfortunately is just for visial benefit
    //and ease of working with data.
    //the only way to cut space on base stats
    //is to not have a species value there in the first place
    //since all the data is the same for cosmetic forms outside 
    //of graphics I could keep hascosmeticforms value on base form
    //and use that for species check to get alt graphics
    //remove them from base stats and just call all the base forms data
    //outside of graphics and type for arceus etc.
    //potentially change cosmetic form value to have bit 2
    //so can store states since some like castform and arceus
    //wouldn't work cuz would still need to display proper type
    //outside of battle as well. smh
    //vsonic important

    [MOVE_RELIC_SONG] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .status = STATUS1_SLEEP },
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SLEEP,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RelicSong,
    },//test this, replaced use of argumenttostatus

    [MOVE_SECRET_SWORD] =
    {
        .effect = EFFECT_PSYSHOCK,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .slicingMove = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SecretSword,
    },

    [MOVE_GLACIATE] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Glaciate,
    },

    [MOVE_BOLT_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BoltStrike,
    },
    //zekrom special move

    [MOVE_BLUE_FLARE] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BlueFlare,
    },//may need buff this and below,
    //signature of reshiram and zeckrom, kinda underwhelming
    //for signature moves is just slightly better thunder and fireblast

    [MOVE_FIERY_DANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .danceMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FieryDance,
    },

    [MOVE_FREEZE_SHOCK] =
    {
        .effect = EFFECT_TWO_TYPED_MOVE,
        .power = 90,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
       //.argument.twoTurnAttack = { .stringId = STRINGID_CLOAKEDINAFREEZINGLIGHT },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FreezeShock,
       .argument = { .storedValue = TYPE_ELECTRIC },
    },//maintained paralysis chance

    [MOVE_ICE_BURN] =
    {
        .effect = EFFECT_TWO_TYPED_MOVE,
        .power = 90,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
       //.argument.twoTurnAttack = { .stringId = STRINGID_CLOAKEDINAFREEZINGLIGHT },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IceBurn,
       .argument = { .storedValue = TYPE_FIRE },
    },//will still burn
    //think these are just kyurem black/white moves

    [MOVE_SNARL] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Snarl,
    },

    [MOVE_ICICLE_CRASH] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IcicleCrash,
    },

    [MOVE_V_CREATE] =
    {
        .effect = EFFECT_HIT,
        .power = 180,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_V_CREATE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_VCreate,
    },

    [MOVE_FUSION_FLARE] =
    {
        .effect = EFFECT_FUSION_COMBO,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .thawsUser = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FusionFlare,
    },

    [MOVE_FUSION_BOLT] =
    {
        .effect = EFFECT_FUSION_COMBO,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FusionBolt,
    },

    [MOVE_FLYING_PRESS] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .power = 100,
        #else
            .power = 80,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        .gravityBanned = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FlyingPress,
    },
    //this move is actually just horrendous, the types don't compliment each other at all
    //best I could do is intead turn this into a two turn semi invul
    // fighting move?
    //or I could make it a fighting move that can and nock down floating mon
    // and mon flying in air?  since it grounds flying mon
    //would remove the flying resist on follow up

    [MOVE_MAT_BLOCK] =
    {
        .effect = EFFECT_MAT_BLOCK,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_MAT_BLOCK, },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MatBlock,
    },//only works first turn mon is in, doesn't block status moves
    //big buff for the move, but its only learned by throh and greninja
    //and greninja is already faster than most, 
    //so this just lets throh actually use the move I guess
    //or was it set that way to only work in trick room?

    [MOVE_BELCH] =
    {
        .effect = EFFECT_BELCH,
        .power = 120,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Belch,
    },

    [MOVE_ROTOTILLER] =
    {
        .effect = EFFECT_ROTOTILLER,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Rototiller,
    },//confusing name but pretty much just means plow/till the land to enrich it
    //boost offense stats for all grass mon on field
    //plan give to some horse/cow mon as they were used to plow the soil
    //i.e milk tank the tauros forms rapidash etc.

    [MOVE_STICKY_WEB] =
    {
        .effect = EFFECT_STICKY_WEB,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StickyWeb,
    },
    //stiky web doesn't cause dmg,
    //and is on thought to be "weakest" type
    //long as keep to only bugs
    //think fine to give this only priority
    //keep an eye on this
    //think buffed more check if still good
    //vsonic

    [MOVE_FELL_STINGER] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .power = 50,
        #else
            .power = 30,
        #endif
        .effect = EFFECT_FELL_STINGER,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FellStinger,
         /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 35,
        }),*/
    },

    [MOVE_PHANTOM_FORCE] =
    {
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ignoresProtect = TRUE,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .multiTaskBanned = TRUE,
        .damagesAirborne = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_VANISHEDINSTANTLY, .status = STATE_PHANTOM_FORCE },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),*/
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PhantomForce,
    },
    //difference of having feint effect with ignoreProtect
    //is that not only will it hit through
    //but will also remove the protect effect
    //since so strong will keep to priority 0

    [MOVE_TRICK_OR_TREAT] =
    {
        .effect = EFFECT_THIRD_TYPE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .storedValue = TYPE_GHOST },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TrickOrTreat,
    },

    [MOVE_NOBLE_ROAR] =
    {
        .effect = EFFECT_NOBLE_ROAR,
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NobleRoar,
    },
    //pyroar line signature, drops atk/sp atk

    [MOVE_ION_DELUGE] =
    {
        .effect = EFFECT_ION_DELUGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_IonDeluge,
    },

    [MOVE_PARABOLIC_CHARGE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .power = 65,
        #else
            .power = 50,
        #endif
        .effect = EFFECT_ABSORB,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ParabolicCharge,
    },//heliolisk signature potentially spread around
    //too good to not have drawback
    //with more types resisting electric is ironically easier to use

    [MOVE_FORESTS_CURSE] =
    {
        .effect = EFFECT_THIRD_TYPE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .storedValue = TYPE_GRASS },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ForestsCurse,
    },

    [MOVE_PETAL_BLIZZARD] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .windMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PetalBlizzard,
    },

    [MOVE_FREEZE_DRY] =
    {
        .effect = EFFECT_SUPER_EFFECTIVE_ON_ARG,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .storedValue = TYPE_WATER },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FreezeDry,
    },//add to more learnsets

    [MOVE_DISARMING_VOICE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DisarmingVoice,
    }, //doesn't make sense for this to have confusion despite being sound move as its quite
    //don't know what to do with this far as cacophony since I don't have dmg boost it would do nothing to this
    //could make boost damaage? just for this kinda stuff, but I prefer for it to not do damage
    //so its separate from sonar

    [MOVE_PARTING_SHOT] =
    {
        .effect = EFFECT_PARTING_SHOT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PartingShot,
    },//lower offense stats then switch
    //consider if this priority shold go back down

    [MOVE_TOPSY_TURVY] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .accuracy = 0,
        #else
            .accuracy = 100,
        #endif
        .effect = EFFECT_TOPSY_TURVY,
        .power = 0,
        .type = TYPE_DARK,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TopsyTurvy,
    },//reverse target stat change

    [MOVE_DRAINING_KISS] =
    {
        .effect = EFFECT_ABSORB,
        .power = 50,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 75 },
        .makesContact = TRUE,
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DrainingKiss,
    },

    [MOVE_CRAFTY_SHIELD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_CRAFTY_SHIELD },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CraftyShield,
    },

    [MOVE_FLOWER_SHIELD] =
    {
        .effect = EFFECT_FLOWER_SHIELD,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FlowerShield,
    },//boost defense of all grass types

    [MOVE_GRASSY_TERRAIN] =
    {
        .effect = EFFECT_GRASSY_TERRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_GRASSY_TERRAIN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GrassyTerrain,
    },//same thing as weather moves, gives some impact back to the moves

    [MOVE_MISTY_TERRAIN] =
    {
        .effect = EFFECT_MISTY_TERRAIN,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = COMBO_STARTER_MISTY_TERRAIN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MistyTerrain,
    },

    [MOVE_ELECTRIFY] =
    {
        .effect = EFFECT_ELECTRIFY,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Electrify,
    },//make target move electric
    //would be good for galvanize replacement 
    //if could get on psychic type w telepathy
    //could have safe stab super explosion  pair w sturdy
    //only available mon is alolan raichu, gave telepathy to attempt

    [MOVE_PLAY_ROUGH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PlayRough,
    },

    [MOVE_FAIRY_WIND] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FairyWind,
    },

    [MOVE_MOONBLAST] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Moonblast,
    },//again too common so won't put knock move on this

    [MOVE_BOOMBURST] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_SOUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,//might be broken w cacophony may need put target back to foes and ally
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Boomburst,
    },

    [MOVE_FAIRY_LOCK] =
    {
        .effect = EFFECT_FAIRY_LOCK,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FairyLock,
    },//klefki signature prevents all mon on field excpet ghosts
    //from being able to switch or flee next turn

    [MOVE_KINGS_SHIELD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_KINGS_SHIELD },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_KingsShield,
    },

    [MOVE_PLAY_NICE] =
    {
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PlayNice,
    },

    [MOVE_CONFIDE] =
    {
        .effect = EFFECT_SPECIAL_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_SOUND,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Confide,
    },

    [MOVE_DIAMOND_STORM] =
    {

        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_2,
            .self = TRUE,
            .chance = 50,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DiamondStorm,
    },

    [MOVE_STEAM_ERUPTION] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .thawsUser = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SCALD},
        //.battleAnimScript = gBattleAnimMove_SteamEruption,
    },

    [MOVE_HYPERSPACE_HOLE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_HYPERSPACE_HOLE,
        //.contestComboMoves = {COMBO_STARTER_HYPERSPACE_FURY},
        //.battleAnimScript = gBattleAnimMove_HyperspaceHole,
    },

    [MOVE_WATER_SHURIKEN] =
    {
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WaterShuriken,
    },

    [MOVE_MYSTICAL_FIRE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_7
            .power = 75,
        #else
            .power = 65,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MysticalFire,
    },

    [MOVE_SPIKE_SHIELD] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_SPIKY_SHIELD },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpikyShield,
    },

    [MOVE_AROMATIC_MIST] =
    {
        .effect = EFFECT_AROMATIC_MIST,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AromaticMist,
    }, //teach bellowsom etc.
    //vsonic important
    //buff sp def of an ally

    [MOVE_EERIE_IMPULSE] =
    {
        .effect = EFFECT_SPECIAL_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_EerieImpulse,
    },

    [MOVE_VENOM_DRENCH] =
    {
        .effect = EFFECT_VENOM_DRENCH,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TOXIC},
        //.battleAnimScript = gBattleAnimMove_VenomDrench,
    },//lower stats of all poisoned target  atk/spatk & speed

    [MOVE_POWDER] =
    {
        .effect = EFFECT_POWDER,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .powderMove = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Powder,
    },//this move is crazy its a fire type counter, spread to more mon, but make it make sense dustox vespiqueen butterfree etc

    [MOVE_GEOMANCY] =
    {
        .effect = EFFECT_GEOMANCY,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKNMABSORBINGPOWER },
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Geomancy,
    },//xerneas signature charge turn then buff stats
    //seems like it sucks but xerneas is bulky and power herb exists

    [MOVE_MAGNETIC_FLUX] =
    {
        .effect = EFFECT_MAGNETIC_FLUX,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MagneticFlux,
    },
    //raise defense stats of user and ally if ability plus or minus

    [MOVE_HAPPY_HOUR] =
    {
        .effect = EFFECT_HAPPY_HOUR,    //appears to be actual effect
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HappyHour,
    },//huh this is meant to double money post battle
    //stacks with amulet coin/luck incense and also doubles payday /make it rain returns

    [MOVE_ELECTRIC_TERRAIN] =
    {
        .effect = EFFECT_ELECTRIC_TERRAIN,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_ELECTRIC_TERRAIN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ElectricTerrain,
    },

    [MOVE_DAZZLING_GLEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DazzlingGleam,
    },

    [MOVE_CELEBRATE] =
    {
        .effect = EFFECT_CELEBRATE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Celebrate,
    },

    [MOVE_HOLD_HANDS] =
    {
        .effect = EFFECT_HOLD_HANDS, //give its own effect
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HoldHands,
    },//buff two different strings, /normal string when does nothing "ally was happy"
    // when rolls effect  "ally got excited! all stats went up" then set all stats go up

    [MOVE_BABY_DOLL_EYES] =
    {
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BabyDollEyes,
    },//think make this a plus 2 to preserve effect?

    [MOVE_NUZZLE] =
    {
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Nuzzle,
    },

    [MOVE_HOLD_BACK] =
    {
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HoldBack,
    }, //make early level move for more professional style fighting mon i.e hitmon chan lee, hariyama sawk medicham
    //add for tyrogue machop vsonic

    [MOVE_SWARM] =
    {
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INFESTATION,
        }),*/
    },//previously infestation

    [MOVE_POWER_UP_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PowerUpPunch,
    },
    //...why did I boost this moves power???
    //lowered pp to balance
    //over used in gen 6 be more sparing with distribution
    //give to charmeleon not charizard
    //and keep to typhlosion
    //keep to hypno, imagine put to sleep and dream eater pow punch
    //vsonic

    [MOVE_OBLIVION_WING] =
    {
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 75 },
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_OblivionWing,
    },

    [MOVE_THOUSAND_ARROWS] =
    {
        .effect = EFFECT_HIT, //replaced smack down effect w flag check
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .damagesAirborne = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_THOUSAND_ARROWS,
        //.contestComboMoves = {COMBO_STARTER_THOUSAND_WAVES},
        //.battleAnimScript = gBattleAnimMove_ThousandArrows,
    },

    [MOVE_THOUSAND_WAVES] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .cantdamageFloating = TRUE,
        .damagesUnderground = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_THOUSAND_WAVES,
        //.contestComboMoves = {COMBO_STARTER_THOUSAND_ARROWS},
        //.battleAnimScript = gBattleAnimMove_ThousandWaves,
    },

    [MOVE_LANDS_WRATH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .damagesUnderground = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LandsWrath,
    },//need to differentiate from thousand waves
    //gonna make small logic leap say the beams of light are what does dmg so can hit floating
    //the trap effect will be what makes people decide if they want this or thousand waves

    [MOVE_LIGHT_OF_RUIN] =
    {
        .effect = EFFECT_RECOIL,
        .power = 140,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_HEAVY_RECOIL,
                .self = TRUE,
            }),*/
        .recoilMove = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_LightOfRuin,
    },

    [MOVE_ORIGIN_PULSE] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_OriginPulse,
    },

    [MOVE_PRECIPICE_BLADES] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .damagesAirborne = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PrecipiceBlades,
    },//Groudon Unique ability,  made flg dmg in air as in show move is shown to blast up from the ocean floor,
    //high into the air... and other games describe it as being able to hit far away targets
    //want make standard clone of this move
    //move rising ridge, controls ground to rip shards/peaks of groud from the earth
    //to attak the foe, think may make just hit floating not flying? buff acc make 95 or something?
    //single target
    //vsonic important

    [MOVE_DRAGON_ASCENT] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DragonAscent,
    },//change from flying to dragon type, give out to more mon,
    // as physical draco meteor

    [MOVE_HYPERSPACE_FURY] =
    {
        .effect = EFFECT_HYPERSPACE_FURY,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            // Feint move effect handled in script as it goes before animation
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_HYPERSPACE_FURY,
        //.contestComboMoves = {COMBO_STARTER_HYPERSPACE_HOLE},
        //.battleAnimScript = gBattleAnimMove_HyperspaceFury,
    },

    [MOVE_SHORE_UP] =
    {
        .effect = EFFECT_SHORE_UP,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SANDSTORM},
        //.battleAnimScript = gBattleAnimMove_ShoreUp,
    },

    [MOVE_FIRST_IMPRESSION] =
    {
        .effect = EFFECT_FIRST_TURN_ONLY,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .split = SPLIT_PHYSICAL,
        .argument = { .moveProperty = MOVE_FIRST_IMPRESSION },
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FirstImpression,
    },
    //MOVE IS already really good, may remove fakeout effect
    //oh it doesn't flinch fakeout effect is just 1st turn effect
    //I guess argument chance was meant to be for infestation idk if will use

    [MOVE_BANEFUL_BUNKER] =
    {
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_BANEFUL_BUNKER },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BanefulBunker,
    },

    [MOVE_SPIRIT_SHACKLE] =
    {
        .effect = EFFECT_HIT, //changed from escape prevention now applier of effect doesn't have to stay in
        .power = 80,
        .type = TYPE_GHOST, //don't give effect to otehr move, if do and not ghost/dark will need adjust script for hand of fate check
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SWITCH_LOCKED,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpiritShackle,
    },//think may buff to be high crit,  since signature move and weakned ghost offensively
    //need test this, w long reach this becomes quite strong
    //hmm actually rather than high crit I think I would like to give this
    //pursuits effect, but would need to rewrite pursuit logic to make work
    //its to convoluted to easly make changes to right now,
    //plus since this does hit escape idea is it would do more damage (1.5?)
    //intead of double, and then also cancel the script, so they can't switch out
    
    //hmm since is a bit differen than other escape blocks in that its using an external factor
    //I could make it unique, with this could set it up so its a supernatural effect binding the target
    // so they'd stay stuck even if the user switched out.
    //to balance that I'd make it temporary, idea it lasts for 3 turns
    //and doesn't get reaplied if hit before the thing, 
    //tldr I'm mkaing a new status least I believe I need to make a new status

    //still todo is setup pursuit effect/rework pursui

    [MOVE_DARKEST_LARIAT] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetDefenseEvasionStages = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DarkestLariat,
    },

    [MOVE_SPARKLING_ARIA] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH, //changed to target both to give niche over surf
        .priority = 0, //then again if you want to cure your own burn you have to give up dmg
        .split = SPLIT_SPECIAL, //most times you won't want to cure your burn so guess its good
        .argument = { .status = STATUS1_BURN },
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
            .sheerForceOverride = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SCALD},
        //.battleAnimScript = gBattleAnimMove_SparklingAria,
    }, //like disarming voice can't do much with this with cacophony and I guess that's fine?
    //ended up buffing disarming voice

    [MOVE_ICE_HAMMER] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_IceHammer,
    },

    [MOVE_FLORAL_HEALING] =
    {
        .effect = EFFECT_HEAL_PULSE,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .moveProperty = MOVE_EFFECT_FLORAL_HEALING },
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FloralHealing,
    },//vsonic important need add logic to heal pulse various command

    [MOVE_HIGH_HORSEPOWER] =
    {
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_HighHorsepower,
    },

    [MOVE_STRENGTH_SAP] =
    {
        .effect = EFFECT_STRENGTH_SAP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .healingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StrengthSap,
    }, //want to make all healing effects snatchable,  will help cutdown on stall
    //lower target attack recover by same amount as effective attack before stat drop

    [MOVE_SOLAR_BLADE] =
    {
        .effect = EFFECT_SOLAR_BEAM,
        .power = 125,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .multiTaskBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNTOOKSUNLIGHT, .status = WEATHER_SUN_ANY },
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_SolarBlade,
    },

    [MOVE_LEAFAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_Leafage,
    },

    [MOVE_SPOTLIGHT] =
    {
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Spotlight,
    },

    [MOVE_TOXIC_THREAD] =
    {
        .effect = EFFECT_TOXIC_THREAD,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TOXIC},
        //.battleAnimScript = gBattleAnimMove_ToxicThread,
    },//supposed to poison and drop speed but still drops speed even if can't poison
    //but with my changes to make status moves follow type calc that no longer works
    //consider whether to reinstate the effect, would be an exception to my rule if so

    [MOVE_LASER_FOCUS] =
    {
        .effect = EFFECT_LASER_FOCUS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LaserFocus,
    },
    //if can crit next attack will crit

    [MOVE_GEAR_UP] =
    {
        .effect = EFFECT_GEAR_UP,   //need test
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GearUp,
    },
    //same as magnetic flux but for offense stats

    [MOVE_THROAT_CHOP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THROAT_CHOP,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ThroatChop,
    },

    [MOVE_POLLEN_PUFF] =
    {
        .effect = EFFECT_HIT_ENEMY_HEAL_ALLY,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PollenPuff,
    },

    [MOVE_ANCHOR_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AnchorShot,
    },

    [MOVE_PSYCHIC_TERRAIN] =
    {
        .effect = EFFECT_PSYCHIC_TERRAIN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_PSYCHIC_TERRAIN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PsychicTerrain,
    },

    [MOVE_LUNGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Lunge,
    },

    [MOVE_FIRE_LASH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .damagesAirborne = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        //.battleAnimScript = gBattleAnimMove_FireLash,
    },//decide make this the fire flying hit not flamethrower

    [MOVE_POWER_TRIP] =
    {
        .effect = EFFECT_STORED_POWER,
        .power = 20,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PowerTrip,
    },

    [MOVE_BURN_OUT] =
    {
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .storedValue = TYPE_FIRE },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),*/
    },

    [MOVE_SPEED_SWAP] =
    {
        .effect = EFFECT_SPEED_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpeedSwap,
    },

    [MOVE_SMART_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SmartStrike,
    },

    [MOVE_PURIFY] =
    {
        .effect = EFFECT_PURIFY,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_STATUS,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Purify,
    },
    //if target has status1 cure status then heals user

    [MOVE_REVELATION_DANCE] =
    {
        .effect = EFFECT_REVELATION_DANCE,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .danceMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_RevelationDance,
    },

    [MOVE_CORE_ENFORCER] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CORE_ENFORCER,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CoreEnforcer,
    },

    [MOVE_TROP_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TropKick,
    },

    [MOVE_INSTRUCT] =
    {
        .effect = EFFECT_INSTRUCT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //leave as is relies on last move, plus seems has complicated turn order logic?
        .split = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .instructBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Instruct,
    },

    [MOVE_BEAK_BLAST] =
    {
        .effect = EFFECT_BEAK_BLAST,    //Todo  vsonic
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .ballisticMove = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BeakBlast,
    },
    //burns on contact and charge phase ignores attackcanceler
    //attack cancel doesn't trigger until attack at negative priority
    //charge is triggered at beginning of turn before all others attack
    //think need EE do effects before turn start?

    [MOVE_CLANGING_SCALES] =
    {
        .effect = EFFECT_HIT, //already uses certain effect in battle script
        .power = 110,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresSubstitute = TRUE,
        .soundMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .self = TRUE,
        },
        {
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ClangingScales,
    },

    [MOVE_DRAGON_HAMMER] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_RUSH, COMBO_STARTER_DRAGON_TAIL},
        //.battleAnimScript = gBattleAnimMove_DragonHammer,
    },

    [MOVE_BRUTAL_SWING] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,    //keeeping this, is indiscriminate attack, buffed dmg make in line with other similar moves, same logic gave secondary effect to balance
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BrutalSwing,
    },

    [MOVE_LICK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 42,        //thanks for all the fish
        #else
            .power = 20,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Lick,
    },

    [MOVE_SHELL_TRAP] =
    {
        .effect = EFFECT_SHELL_TRAP,    //todo  EFFECT_SHELL_TRAP
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .split = SPLIT_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShellTrap,
    },

    [MOVE_FLEUR_CANNON] =
    {
        .effect = EFFECT_HIT,  //changed to MOVE_EFFECT_MEDIUM_RECOIL
        .power = 130,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FleurCannon,
    },

    [MOVE_PSYCHIC_FANGS] =
    {
        .effect = EFFECT_BRICK_BREAK,
        .power = 75,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PsychicFangs,
    },// kept at power 75, added flinch and effect chance boosted to level of bite

    [MOVE_STOMPING_TANTRUM] =
    {
        .effect = EFFECT_STOMPING_TANTRUM,
        .power = 75,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StompingTantrum,
    },

    [MOVE_SHADOW_BONE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_SHADOW_BONE,
        //.contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONEMERANG, COMBO_STARTER_BONE_RUSH},
        //.battleAnimScript = gBattleAnimMove_ShadowBone,
    },

    [MOVE_ACCELEROCK] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Accelerock,
    },//made equivalent of extreme speed rather than quick attack, es is base 80,but most mon that learn it aren't normal, so this equivalent dmg w stab in mind

    [MOVE_LIQUIDATION] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Liquidation,
    },

    [MOVE_PRISMATIC_LASER] =
    {
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PrismaticLaser,
    },

    [MOVE_SPECTRAL_THIEF] =
    {
        .effect = EFFECT_SPECTRAL_THIEF,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ignoresSubstitute = TRUE,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpectralThief,
    },

    [MOVE_SUNSTEEL_STRIKE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetAbility = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SunsteelStrike,
    },

    [MOVE_MOONGEIST_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresTargetAbility = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MoongeistBeam,
    },

    [MOVE_TEARFUL_LOOK] =
    {
        .effect = EFFECT_NOBLE_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TearfulLook,
    },

    [MOVE_ZING_ZAP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_CHARGE},
        //.battleAnimScript = gBattleAnimMove_ZingZap,
    },//had lowered but think will put at ame level as bite?
    //eh screw it will keep unnerfed as electric rock slide

    [MOVE_NATURES_MADNESS] =
    {
        .effect = EFFECT_FIXED_PERCENT_DAMAGE,
        .power = 1,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .damagePercentage = 50 },
        .metronomeBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NaturesMadness,
    },

    [MOVE_MULTI_ATTACK] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 120,
        #else
            .power = 90,
        #endif
        .effect = EFFECT_CHANGE_TYPE_ON_ITEM,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .holdEffect = HOLD_EFFECT_MEMORY },
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MultiAttack,
    }, //unsure if want to give free super like arceus
    //is meant to be a failed copy

    [MOVE_MIND_BLOWN] =
    {
        .effect = EFFECT_MIND_BLOWN,
        .power = 100, //cut down cuz like misty explosion can get super, and also boosted in sun
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,    //is explosion
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .multiTaskBanned = TRUE,
        .metronomeBanned = TRUE,
        .dampBanned = TRUE,
        .ballisticMove = TRUE,
        .explosiveMove = TRUE,
        .argument = { .sacrificedHpPercentage = 50 },
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MindBlown,
    },//work todo
    //move custs half the user's hp rather than doing recoil
    //so there's never a reason to use this move,
    //with bs rework make this heavy recoil effect instead
    //that is just canceled by damp
    //would need make new bs command fail if damp etc.
    //change mind may keep effect 
    //misty explosion should be same as mind blown
    //but just boosted on fairy terrain
    //while this would get boosted by sun
    //and self destruct would just be higher in power

    [MOVE_PLASMA_FIST] =
    {
        .effect = EFFECT_HIT, // Needs a custom move effect    //sets ion deluge single turn
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .metronomeBanned = TRUE,
        /*.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},*/
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ION_DELUGE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),*/
        //.battleAnimScript = gBattleAnimMove_PlasmaFists,
    },//want anim to be trailing blue lightning effect, like wing attack does for tornado  rebalanced, inspired by zera unite move, raw plasma will seek out a target 

    [MOVE_PHOTON_GEYSER] =
    {
        .effect = EFFECT_PHOTON_GEYSER, // Needs a custom move effect //similar to my hidden power effect, it changes split, based on user offense stat, 
        .power = 100,
        .type = TYPE_PSYCHIC,       //this is meant to lean into the specialties of the different forms, so intead of stat will make split species based
        .accuracy = 100,            //and then for ultra necrozma, make it based on enemies highest def stat, so you always attack their weakness
        .pp = 5,
        .target = MOVE_TARGET_BOTH,    //changed from ally and foe target,may make single target    //but mon is a bit of a glass cannon
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .ignoresTargetAbility = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PhotonGeyser,
    },//has a function for doesn't need to do in bs, meaning this can just go to hit
    //ok adjusted now goes to hit, should still adjust split

    [MOVE_ZIPPY_ZAP] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .pp = 15,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .alwaysCriticalHit = TRUE,
        .metronomeBanned = TRUE,
            /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_EVS_PLUS_1,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_ZippyZap,
    },

    [MOVE_SPLISHY_SPLASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            #else
            #endif
        .effect = EFFECT_TWO_TYPED_MOVE,      //changed two a dual typed move with paralyze chance. lol i made it more op than ever
        .power = 90,        //something between discharge and surf, discharge is base 80,  surf is base 95
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,    //lol its a giant electrified surf, that is gonna have to hit everyone, you can't avoid that XD
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        .argument = { .storedValue = TYPE_ELECTRIC },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SplishySplash,
       
    },

    [MOVE_FLOATY_FALL] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
            .sheerForceOverride = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_FloatyFall,
    },
    //hmm unique pika exclusive but think I may actualy give this 
    //to gyarados as solid physical move outside of bounce
    //already lowered effect odds to balance but if its meant to compare w bounce
    //may need to lower further to 15%?
    //yeah that seems good, most flinch effects outside unique things are 15% i.e all fangs
    //hmm actually nvm bite is 25%

    [MOVE_PIKA_PAPOW] =
    {
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_PikaPapow,
    },

    [MOVE_BOUNCY_BUBBLE] =
    {
        .power = 60,
        .pp = 20,
        .effect = EFFECT_ABSORB,
        .type = TYPE_WATER,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 100 },
        .metronomeBanned = TRUE,
        .healingMove = TRUE,
        //.battleAnimScript = gBattleAnimMove_BouncyBubble,
    },

    [MOVE_BUZZY_BUZZ] =
    {
        .power = 80,
        .pp = 15,
        .effect = EFFECT_HIT,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
        }),*/
        //.battleAnimScript = gBattleAnimMove_BuzzyBuzz,
    },

    [MOVE_SIZZLY_SLIDE] =
    {
        .power = 80,
        .pp = 15,
        .effect = EFFECT_HIT,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SizzlySlide,
    },

    [MOVE_GLITZY_GLOW] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 80,
            .accuracy = 95,
            #else
            .power = 90,
            .accuracy = 100,
            #endif
        .effect = EFFECT_HIT,   //TODO (Light Screen + Hit)
        .type = TYPE_PSYCHIC,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LIGHT_SCREEN,
        }),*/
        //.battleAnimScript = gBattleAnimMove_GlitzyGlow,
    },

    [MOVE_BADDY_BAD] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 80,
            .accuracy = 95,
            #else
            .power = 90,
            .accuracy = 100,
            #endif
        .effect = EFFECT_HIT,   //TODO (Reflect + Hit)
        .type = TYPE_DARK,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REFLECT,
        }),*/
        //.battleAnimScript = gBattleAnimMove_BaddyBad,
    },

    [MOVE_SAPPY_SEED] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 100,
            .accuracy = 90,
            .pp = 10,
            #else
            .power = 90,
            .accuracy = 100,
            .pp = 15,
            #endif
        .effect = EFFECT_HIT,   //TODO (Leech Seed + Hit)
        .type = TYPE_GRASS,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .magicCoatAffected = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LEECH_SEED,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SappySeed,
    },

    [MOVE_FREEZY_FROST] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 100,
            .accuracy = 90,
            .pp = 10,
            #else
            .power = 90,
            .accuracy = 100,
            .pp = 15,
            #endif
        .effect = EFFECT_HIT,   //TODO (Haze + Hit)
        .type = TYPE_ICE,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_HAZE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_FreezyFrost,
    },

    [MOVE_SPARKLY_SWIRL] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .power = 120,
            .accuracy = 85,
            .pp = 5,
            #else
            .power = 90,
            .accuracy = 100,
            .pp = 15,
            #endif
        .effect = EFFECT_HIT,   //TODO (Heal Bell + Hit)
        .type = TYPE_FAIRY,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_AROMATHERAPY,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SparklySwirl,
    },

    [MOVE_VEEVEE_VOLLEY] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_8
            #else
            #endif
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_VeeveeVolley,
    },

    [MOVE_DOUBLE_IRON_BASH] =
    {

        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .strikeCount = 2,
        .evasiveBreak = TRUE,
        .metronomeBanned = TRUE,
        .multiTaskBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DoubleIronBash,
    },

    [MOVE_DYNAMAX_CANNON] =
    {
        .effect = EFFECT_BOOST_PWR_BASED_WEIGHT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mimicBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DynamaxCannon,
    },

    [MOVE_SNIPE_SHOT] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .enhancedCritrate = TRUE,
        .ignoresRedirection = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SnipeShot,
    },

    [MOVE_JAW_LOCK] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_HIT_BOTH,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_JawLock,
    },
    //vsonic think give move to feraligator

    [MOVE_STUFF_CHEEKS] =
    {
        .effect = EFFECT_STUFF_CHEEKS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StuffCheeks,
    },//eat berry  boost defense activate effect

    [MOVE_NO_RETREAT] =
    {
        .effect = EFFECT_NO_RETREAT,   //TODO
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_NoRetreat,
    },//buffs all stats prevents retreat/flee/escape

    [MOVE_TAR_SHOT] =
    {
        .effect = EFFECT_TAR_SHOT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TarShot,
    },
    //lower speed increase fire dmg dealt to target

    [MOVE_MAGIC_POWDER] =
    {
        .effect = EFFECT_SOAK,  //believe this is type change to psychic, similar to soak is type change to water
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .argument = { .storedValue = TYPE_PSYCHIC },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MagicPowder,
    },

    [MOVE_DRAGON_DARTS] =
    {
        .effect = EFFECT_DRAGON_DARTS, //TODO   //weird effect, rather than double target, is a single target move that moves on to the next target after landing, think can use intimidate logic
        .power = 50,
        .type = TYPE_DRAGON, //I can chese this actually, since single target effects only hit single target, make target both, and specific bs command for it, put effect in multihit 
        .accuracy = 100, //switch case, and have it read the number of enemies on enemy side, if 2 set to 1 hit, if 1 set to 2 hits
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        .parentalBondBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DragonDarts,
    }, //simplest thing is make normal hit, but make target both, unless it would hit twice if single target?

    [MOVE_TEATIME] =
    {
        .effect = EFFECT_TEATIME,   //TODO   //looks like forces evryone to eat their berries, bypasses unnerve & magic guard, fails if no one has berries
        .power = 0,
        .type = TYPE_NORMAL, //loop battlers check has berries if someone does activate loop consume berry else fail need teatime bs command
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Teatime,
    },

    [MOVE_OCTOLOCK] =
    {
        .effect = EFFECT_OCTOLOCK,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Octolock,
    },//prevent escape switch lower defense stats each end turn

    [MOVE_BOLT_BEAK] =
    {
        .effect = EFFECT_BOLT_BEAK,   //TODO
        .power = 85,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BoltBeak,
    },

    [MOVE_FISHIOUS_REND] =
    {
        .effect = EFFECT_BOLT_BEAK,   //TODO. same as bolt beak
        .power = 85,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FishiousRend,
    },

    [MOVE_COURT_CHANGE] =
    {
        .effect = EFFECT_COURT_CHANGE,   //TODO  //check side status enemy side copy to my side and do same for my side to their side? does it keep current timers?
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CourtChange,
    },//make activebattle effects swap sides

    [MOVE_CLANGOROUS_SOUL] =
    {
        .effect = EFFECT_CLANGOROUS_SOUL,   //TODO  can make bs command for it, use setstatchanger and loop the battle stats until all stats are boosted
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        .danceMove = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ClangorousSoul,
    },//might be set but test

    [MOVE_BODY_PRESS] =
    {
        .effect = EFFECT_BODY_PRESS,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BodyPress,
    },

    [MOVE_DECORATE] =
    {
        .effect = EFFECT_DECORATE,   // TODO .. EFFECT_DECORATE
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Decorate,
    },

    [MOVE_DRUM_BEATING] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DrumBeating,
    },

    //notes from bulbapedia
    /*In addition to dealing damage, Snap Trap inflicts 1/8 of the target's maximum HP
    as damage per turn for four to five turns upon use. It also traps the target, preventing switching and escape.
    If the user switches out, the target will be freed.
    If the user of Snap Trap is holding a Grip Claw, the duration will always be 7 turns.
    If a Binding Band is held by the user, the damage done at the end of each turn
    will increase from 1 / 8 of the target's maximum HP to 1/6.*/
    [MOVE_SNAP_TRAP] =
    {
        .effect = EFFECT_HIT,  //TODO: add case/effect  think use random%2 +4 should make be between 0 & 1 the plus 4 will make it return 4 & 5
        .power = 35,
        .type = TYPE_STEEL, //after that just need specific logic for grip claw     //also changing from grass to a steel move -_-
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_SNAP_TRAP,
        },
        {
            .moveEfect = MOVE_EFFECT_FLINCH,
            .chance = 25,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SnapTrap,
    },


    [MOVE_PYRO_BALL] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .thawsUser = TRUE,
        .ballisticMove = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_PyroBall,
    },

    [MOVE_BEHEMOTH_BLADE] =
    {
        .effect = EFFECT_BOOST_PWR_BASED_WEIGHT,   //TODO: 2x damage if dynamaxed? meh...
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .mimicBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BehemothBlade,
    },//if add an extra effect could add power boost based on weight
    //setup, remmeber to rename later, behemoth burst effect or something
    //40% power boost

    [MOVE_BEHEMOTH_BASH] =
    {
        .effect = EFFECT_BOOST_PWR_BASED_WEIGHT,   //TODO: 2x damage if dynamaxed? meh...
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .mimicBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BehemothBash,
    },

    [MOVE_AURA_WHEEL] =
    {
        .effect = EFFECT_AURA_WHEEL,
        .power = 110,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AuraWheel,
    },

    [MOVE_BREAKING_SWIPE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BreakingSwipe,
    },

    [MOVE_BRANCH_POKE] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BranchPoke,
    },

    [MOVE_OVERDRIVE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Overdrive,
    },

    [MOVE_APPLE_ACID] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AppleAcid,
    },

    [MOVE_GRAV_APPLE] =
    {
        .effect = EFFECT_GRAV_APPLE,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GravApple,
    },
    //think also give to bombirdier as entire thing is dropping 
    //things on people

    [MOVE_SPIRIT_BREAK] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SpiritBreak,
    },

    [MOVE_STRANGE_STEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FAIRY,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_StrangeSteam,
    },

    [MOVE_LIFE_DEW] =
    {
        .effect = EFFECT_JUNGLE_HEALING,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LifeDew,
    },
    //restore hp of user and ally 25% of max

    [MOVE_OBSTRUCT] =
    {
        .effect = EFFECT_PROTECT,   //TODO. EFFECT_PROTECT?
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_OBSTRUCT },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .instructBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Obstruct,
    },

    [MOVE_FALSE_SURRENDER] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FalseSurrender,
    },

    [MOVE_METEOR_ASSAULT] =
    {
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .instructBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MeteorAssault,
    },

    [MOVE_ETERNABEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Eternabeam,
    },

    [MOVE_STEEL_BEAM] =
    {
        .effect = EFFECT_RECOIL,
        .power = 140,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .recoilMove = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_HEAVY_RECOIL,
                .self = TRUE,
            }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SteelBeam,
    },//give to empoleon since it lacks steel moves
    //test may lower to med recoil
    //looked into different from reg recoil
    //takes 50% health not 50% dmg dealt
    //believe basis its only special recoil move
    //so its not a reckless rush
    //its a high stamina draining effect
    //which is why it doesn't synergize with
    //rockhead or recless
    //so can adjust so those affects specify
    //physical recoil only
    //edit. description it rips metal 
    //from its own body to use for attack
    //was normal recoil in arceus think will go with that
    //actualy weird, chloroblast does same thing as this,
    //and is also special, but it gets rock head reckless boost..

    [MOVE_EXPANDING_FORCE] =
    {
        .effect = EFFECT_EXPANDING_FORCE,   //TODO  /done think need animation
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_PSYCHIC_TERRAIN},
        //.battleAnimScript = gBattleAnimMove_ExpandingForce,
    },

    [MOVE_STEEL_ROLLER] =
    {
        .effect = EFFECT_STEEL_ROLLER,   //Think done
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SteelRoller,
    },
    //change to base power 90, 
    //becomes 130 only if terrain is up

    [MOVE_SCALE_SHOT] =
    {
        .effect = EFFECT_HIT,   
        .power = 25,
        .type = TYPE_DRAGON,    //me look at how double iron bash was done may be able to do these myself
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .multiTaskBanned = TRUE,
        .variableMultihit = TRUE,
        .argument = { .moveProperty = MOVE_EFFECT_SCALE_SHOT },
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ScaleShot,
    }, //shold be able to do with bs, just add check for effect or move  and lower defense if found move/effet or potentially put in move end?
    //yeah doing with moveed,  all have to do is set statchangers in function, (like moody) and use if no move result no effect

    [MOVE_METEOR_BEAM] =
    {
        .effect = EFFECT_TWO_TURNS_ATTACK,   //TODO
        .power = 120,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_METEORBEAMCHARGING },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .onChargeTurnOnly = TRUE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MeteorBeam,
    },//similar to skull bash but boosts sp atk
    //and seems it has effect that once charge starts
    //effect will continue until it executes even if flinches or otherwise
    //incapacitated i.e sleep freeze etc.
    //idk if all charge moves work that way but they should
    //wait this is literally just electro shot ex without rain effect
    //why is this not setup?
    //old setup/not updated from EE
    //need move effect bs update

    [MOVE_SHELL_SIDE_ARM] =
    {
        .effect = EFFECT_SHELL_SIDE_ARM,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShellSideArm,
    },

    [MOVE_MISTY_EXPLOSION] =
    {
        .effect = EFFECT_EXPLOSION,
        .power = 100,   //was base 100 made 120 to compare to explosion w change type multiplier accounter for
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .multiTaskBanned = TRUE,
        .dampBanned = TRUE,
        .ballisticMove = TRUE,
        .explosiveMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_MISTY_TERRAIN},
        //.battleAnimScript = gBattleAnimMove_MistyExplosion,
    }, 
    //need also remember that this gets boosted further by terrain
    //buffed was given explosion effect defense stat drop (will drop sp def)
    //think reason for lower power as only non normal explosion so can get type multiplier,
    //seems my change is appropriate buff without breaking its balance
    //think remove misty explosion from balistic i.e bulletproof immunity, not physical,
    //and is mystical in nature
    //dumb idea point is its an explosion so keep effect

    [MOVE_GRASSY_GLIDE] =
    {
        .effect = EFFECT_GRASSY_GLIDE,
        .power = 65,    //already done
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GRASSY_TERRAIN},
        //.battleAnimScript = gBattleAnimMove_GrassyGlide,
    },

    [MOVE_RISING_VOLTAGE] =
    {
        .effect = EFFECT_RISING_VOLTAGE,   //TODO
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ELECTRIC_TERRAIN},
        //.battleAnimScript = gBattleAnimMove_RisingVoltage,
    },

    [MOVE_TERRAIN_PULSE] =
    {
        .effect = EFFECT_TERRAIN_PULSE,   //TODO
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .pulseMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_ELECTRIC_TERRAIN, COMBO_STARTER_MISTY_TERRAIN, COMBO_STARTER_GRASSY_TERRAIN, COMBO_STARTER_PSYCHIC_TERRAIN},
        //.battleAnimScript = gBattleAnimMove_TerrainPulse,
    },

    [MOVE_SKITTER_SMACK] =
    {
        .effect = EFFECT_HIT,
        .power = 55, //base game is 70, may make my version 50?
        .type = TYPE_BUG,
        .accuracy = 100,//hmm w stab at 60 is base while 55 is just shy of 75 that seems better?
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        },
        {
            .moveEffect = MOVE_EFFECT_INFESTATION,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SkitterSmack,
    },//think argument defaults to 0, point is to add 
    //when I get it working w teh proper animation, and have all bug moves a 10% chance to infest
    //think will rework this to priority move,
    //also works w what I want for bug, to be not super oppressive but very annoying
    //giving to scyther as way of handling psychic types, also has good bug move to use now
    //note need test how fury cutter plays with technician ok in same function so now
    //would trigger for early hits not for later hits seems fine

    [MOVE_BURNING_JEALOUSY] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIRE,//believe mayu need raise pp to 10
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .onlyIfTargetRaisedStats = TRUE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_BurningJealousy,
        .argument = MOVE_EFFECT_BURN,
    },//think make - priorty move if on a fast mon not usefl
    //potentially give to reshiram
    //unsure if should make electric variant for zekrom?
    //shocking malice vsonic
    //balanced by needing to boost target stat
    //and status having random elemnet to it,
    //requires doubles to work
    //but gives 100% paralysis which was lost with thunder wave
    //plus damage

    [MOVE_LASH_OUT] =
    {
        .effect = EFFECT_LASH_OUT,   //TODO
        .power = 75,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_LashOut,
    },

    [MOVE_POLTERGEIST] =
    {
        .effect = EFFECT_POLTERGEIST,   //TODO
        .power = 110,
        .type = TYPE_GHOST,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Poltergeist,
    },

    [MOVE_CORROSIVE_GAS] =
    {
        .effect = EFFECT_CORROSIVE_GAS,   //TODO   is essentially knock off why was this not done?
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_BOTH, //changed to make more useful.
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CorrosiveGas,
    },

    [MOVE_COACHING] =
    {
        .effect = EFFECT_COACHING,   //TODO
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Coaching,
    },//boost ally atk def

    [MOVE_FLIP_TURN] =
    {
        .effect = EFFECT_HIT_ESCAPE,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FlipTurn,
    },

    [MOVE_TRIPLE_AXEL] =
    {
        .effect = EFFECT_TRIPLE_KICK,   //TODO: Increase damage by 20 instead of 10   /Done 
        .power = 20,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .strikeCount = 3,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TripleAxel,
    },

    [MOVE_DUAL_WINGBEAT] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DualWingbeat,
    },
    //kinda want to buff but its fine, being double  hit is its own good point

    [MOVE_SCORCHING_SANDS] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .thawsUser = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ScorchingSands,
    },
    //attacks by tossing sand so not exactly ground locked I guess

    [MOVE_JUNGLE_HEALING] =
    {
        .effect = EFFECT_JUNGLE_HEALING,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_JungleHealing,
    },//effect should be heal quarter max hp user and ally
    //but jungle healing also cures status 1

    [MOVE_WICKED_BLOW] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_WickedBlow,
    },

    [MOVE_SURGING_STRIKES] =
    {
        .effect = EFFECT_TRIPLE_KICK,   
        .power = 25,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .strikeCount = 3,
        .multiTaskBanned = TRUE,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SurgingStrikes,
    }, //rebalanced these 2 for og crit
    //on advice from Chief, changing from full crit to defense pen, will ignore either 25% or 35% of defense
    //in exchange can't crit
    //made small tweak to rebalance ability unseen fist, so signature moves can still be used w ability
    //plan only allow moves below power 75 to slip through protect
    //makes it more of a chip ability somewhat

    [MOVE_THUNDER_CAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
            .multistring.wrapped = B_MSG_WRAPPED_THUNDER_CAGE,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ThunderCage,
    },
    //gave effect trap damage can paralyze, working on

    [MOVE_DRAGON_ENERGY] =
    {
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DragonEnergy,
    },

    [MOVE_FREEZING_GLARE] =
    {
        .power = 90,
        .effect = EFFECT_HIT,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FreezingGlare,
    },

    [MOVE_FIERY_WRATH] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_FieryWrath,
    },

    [MOVE_THUNDEROUS_KICK] =
    {
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ThunderousKick,
    },

    [MOVE_GLACIAL_LANCE] =
    {
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_GlacialLance,
    },

    [MOVE_ASTRAL_BARRAGE] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AstralBarrage,
    },

    [MOVE_EERIE_SPELL] =
    {
        .effect = EFFECT_HIT, // Done. It's a copy of Spite that inflicts damage and reduced the target's last move's PP by 3 instead of 4.
        .power = 80,
        .type = TYPE_PSYCHIC,   //test  //since its a 5 pp move, I think I'll just give it the normal spite effect I made, rather than limiting it to reduce 3 pp.
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .multiTaskBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_EERIE_SPELL,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_EerieSpell,
    },//ok checked double checked japanese translation and there's no reason for this move to be a sound move. its just a dark magic spell
    //idk maybe need something like generates sound in enemies head that curses them -vsonic
    //vsonic set to new spite effect maybe?

    //Legends Arceus moves
    [MOVE_DIRE_CLAW] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 80,
        #else
            .power = 60,
        #endif
        .effect = EFFECT_HIT, // EFFECT_DIRE_CLAW,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DIRE_CLAW,
            .chance = 50,
        }),*/
        //.battleAnimScript = gBattleAnimMove_DireClaw,
    },

    [MOVE_PSYSHIELD_BASH] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_PsyshieldBash,
    },

    [MOVE_POWER_SHIFT] =
    {
        .effect = EFFECT_POWER_TRICK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_PowerShift,
    },

    [MOVE_STONE_AXE] =
    {
        .effect = EFFECT_STONE_AXE,
        .power = 65,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .sheerForceOverride = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_StoneAxe,
    }, //need test
    //low power no reason to have such low acc
    //especially when stealth rocks don't stack
    //acc not being perfect is best balance willing to do with this

    [MOVE_SPRINGTIDE_STORM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 100,
        #else
            .power = 95,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_FAIRY,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .metronomeBanned = TRUE,
        //.alwaysHitsInRain = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 30,
        },
        {
            .moveEffect = MOVE_EFFECT_ATTRACT,
            //.chance = 30,            
        }),*/
        //.battleAnimScript = gBattleAnimMove_SpringtideStorm,
    },

    [MOVE_MYSTICAL_POWER] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_HIGHEST_STAT_UP,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_MysticalPower,
    },
    //changing from sp atk up hit
    //May change, signature of lake spirits LA affect was boost offense stats or defense stats whichever was higher
    //think what can do is change to boost highest base stat? other than hp, hopefully different stat for each fairy
    //ok use highest battle stat not base stat,
    //since mespirit and azelf have tied base stats
    //uxie will always boost sp def pretty much
    //vsonic unsure if should work w snatch?


    [MOVE_RAGING_FURY] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 120,
        #else
            .power = 90,
        #endif
        .effect = EFFECT_HIT, //outrage,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .multiTaskBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_RagingFury,
    },

    [MOVE_WAVE_CRASH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 120,
        #else
            .power = 75,
        #endif
        .effect = EFFECT_RECOIL,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_MED_RECOIL,
                .self = TRUE,
            }),*/
        .makesContact = TRUE,
        .recoilMove = TRUE,
        //.battleAnimScript = gBattleAnimMove_WaveCrash,
    },//so they turned it from wter take down to water double edge, but the recoil is still less
    //*idea rampage plus recoil, potentially no confusion,  -vsonic

    [MOVE_CHLOROBLAST] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 150,
        #else
            .power = 120,
        #endif
        .effect = EFFECT_RECOIL,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .recoilMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_HEAVY_RECOIL,
                .self = TRUE,
            }),*/
        //.battleAnimScript = gBattleAnimMove_Chloroblast,
    },

    [MOVE_MOUNTAIN_GALE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_MountainGale,
    },
    //buffed since only given to avalug
    //turns into ice rock slide
    //requires trick room setup

    [MOVE_VICTORY_DANCE] =
    {
        .effect = EFFECT_VICTORY_DANCE,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_VictoryDance,
    },//boost atk def & speed

    [MOVE_HEADLONG_RUSH] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 120,
        #else
            .power = 100,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .headbuttMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_HeadlongRush,
    },
    //note gets iron fist boost cuz name is sumo term, rush forward while thrusting fists/open palms forwward to attack
    //not overheat effect, supposed to lower def & sp def
    //oh I made it overheat to make it a recoil move, hmmm
    //I had reworked recoil so may do that instead?
    // vsonic keep an eye on

    [MOVE_BARB_BARRAGE] =
    {
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = 60,
        .type = TYPE_POISON, //poison hit + hex well actually literally just poison hit
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .status = STATUS1_PSN_ANY },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 50,
        }),*/
        //.battleAnimScript = gBattleAnimMove_BarbBarrage,
    },
    //double damage if target poisoned, and set poison

    [MOVE_ESPER_WING] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 80,
        #else
            .power = 75,
        #endif
        .effect = EFFECT_TWO_TYPED_MOVE,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
       .argument = { .storedValue = TYPE_FLYING },
        //.battleAnimScript = gBattleAnimMove_EsperWing,
    },//vsonic want to make this two typed psychic flying

    [MOVE_BITTER_MALICE] =
    {

        .power = 60,
        .effect = EFFECT_HIT, //freeze hit plus hex
        .type = TYPE_GHOST, //while would be cool to have ghost freeze move
        .accuracy = 100, //think thematicaly (based on move description)
        .pp = 10,       //prefer this as atk and sp atk drop
        .target = MOVE_TARGET_SELECTED, //for that use shadow ball background with creeping ice crystals from bottom up
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        },
        {
            .moveEffect = MOVE_EFFECT_FROSTBITE,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_BitterMalice,
    },//vsonic - make bitter malilce its own effect atk/spatkdown hit
    //use BattleScript_EffectNobleRoar  as template
    //ok change mind what i'll do is keep power at 60
    //pp at 10  do atk & sp atk drop, but also add frostbite chance
    //as doesn't make sense to freeze solid, 
    //make atk sp atk down hit and add freeze chanace
    //then in setmove effect think in freeze set will need
    //check curr move and set timer to 0
    //and accomodate for re-freeze so doesn't trigger that
    //done - w freeze chance added decided do just atk down

    [MOVE_SHELTER] =
    {
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_Shelter,
    },

    [MOVE_TRIPLE_ARROWS] =
    {
        .power = 65,
        .effect = EFFECT_HIT, // sets focus energy to raise crit chance, lowers defense with augment & higher crit chance
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .enhancedCritrate = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FOCUS_ENERGY,
            .self = TRUE,
            .setfromatkcanceler = TRUE,
        },
        {
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 30,
        }),*/
    },  //need test fixed put focus energy effect at end, so doesn't trigger before damage done. / changed mind put at start, mon is still relatively frail

    [MOVE_INFERNAL_PARADE] =
    {
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS, // EFFECT_INFERNAL_PARADE,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .status = STATUS1_ANY },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_InfernalParade,
    },
    //hex + burn chance

    [MOVE_CEASELESS_EDGE] =
    {
        .effect = EFFECT_CEASELESS_EDGE,
        .power = 65,
        .type = TYPE_DARK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .sheerForceOverride = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_CeaselessEdge,
    },
    //sets spikes
    //lower acc than stone axe because not dark, and effect stacks

    [MOVE_BLEAKWIND_STORM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 100,
            .pp = 5,
        #else
            .power = 95,
            .pp = 5,
        #endif
        .effect = EFFECT_HIT,//EFFECT_HIT, //put freeze back on this
        .type = TYPE_FLYING, //is balanced w my freeze changes
        .accuracy = 85,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .alwaysHitsInRain = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 20,
        }),*/
        //.battleAnimScript = gBattleAnimMove_BleakwindStorm,
    },//signature move of therian tornadus, make form different mon so can only learn this
    //move in therian form, guess will need make a replacement like rotom,
    //so move changes to something else when in incarnate form, and reverts to this when changed to therian
    //issue is incanrate tornadus ability makes having this too, too oppressive
        //vsonic important

    [MOVE_WILDBOLT_STORM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 100,
            .pp = 10,
        #else
            .power = 95,
            .pp = 5,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_ELECTRIC,
        .accuracy = 80,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .alwaysHitsInRain = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 20,
        }),*/
        //.battleAnimScript = gBattleAnimMove_WildboltStorm,
    },

    [MOVE_SANDSEAR_STORM] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_9
            .power = 100,
            .pp = 10,
        #else
            .power = 95,
            .pp = 5,
        #endif
        .effect = EFFECT_HIT,
        .type = TYPE_GROUND,
        .accuracy = 80,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .windMove = TRUE,
        .alwaysHitsInRain = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SandsearStorm,
    },//dmg in air was only used here because is ground type move but reworked effect
    //effects of these 3 storm moves
    //are supposed to be perfect acc in rain 
    //worried is too much
    //vsonic important

    [MOVE_LUNAR_BLESSING] =
    {
        .effect = EFFECT_JUNGLE_HEALING, // EFFECT_LUNAR_BLESSING,
        .power = 0,
        .type = TYPE_PSYCHIC, //understand why they hadnt filled this in now
        .accuracy = 0,  //they were planning to setup the arceus effect
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        //.battleAnimScript = gBattleAnimMove_LunarBlessing,
    },//restore 25% max hp user and allies plus remove status 1
    //essentially jungle healing
    //to make it its own thing may buff to 33%? //no don't buff sheesh

    [MOVE_TAKE_HEART] =
    {
        .effect = EFFECT_HIT, // EFFECT_TAKE_HEART,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_TakeHeart,
    },
    //cures ALL status conditions (make custom list of negative ones to remove)
    //then reaises atk and def  at end turn for 4 turns
    //manaphy phione signature
    
    //Gen 9 Moves
    [MOVE_TERA_BLAST] =
    {
        .effect = EFFECT_TERA_BLAST,    //Todo // EFFECT_TERA_BLAST,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .forcePressure = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TERA_BLAST,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_TeraBlast,
    },

    [MOVE_SILK_TRAP] =
    {
        .effect = EFFECT_PROTECT,    //Todo // EFFECT_PROTECT with extra checks
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_SILK_TRAP },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_SilkTrap,
    },

    [MOVE_AXE_KICK] =
    {
        .effect = EFFECT_RECOIL_IF_MISS,    
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .kickingMove = TRUE,
        .damagesAirborne = TRUE,
        .recoilMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_AxeKick,
    },

    [MOVE_LAST_RESPECTS] =
    {
        .effect = EFFECT_LAST_RESPECTS,    //Todo // EFFECT_LAST_RESPECTS
        .power = 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        //.metronomeBanned = TRUE, // Only since it isnt implemented yet
         //.battleAnimScript = gBattleAnimMove_LastRespects,
    },

    [MOVE_LUMINA_CRASH] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_LuminaCrash,
    },

    [MOVE_ORDER_UP] =
    {
        .effect = EFFECT_ORDER_UP,    //Todo // EFFECT_ORDER_UP  //boost certain stat based on form of tatsugiri it targets
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ORDER_UP,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_OrderUp,
    },
    //I never saw anyone use anything but the attack boosting tatsugiri
    //maybe should adjust stat gain its speed stat is so low base 35 
    //there no reason to use that one, would need use bout 4 times before could see speed gains
    //otherwise best to just use trick room,
    //and defense sees diminisning returns with gains and its sp def is low so people could just attack that
    //solution boost speed 2 stages per use
    //potentially do same for defense? 
    //attack is preferred for obvious reason its physical attacker,
    //so can always get benefit of atk boost
    //defense boost is diminishing and people can just bypass
    //it by using special move
    //its already very dominant so I'm worried about buffing defense?
    //nvm missed that the tatsugiri already boosts all dodonzo's stats by 2 stages
    //dont think anything I can do at this point

    [MOVE_JET_PUNCH] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_JetPunch,
        // The datamine master sheet mentions uncopiable by Metronome but that sounds odd? not yet implemented
    },

    [MOVE_SPICY_EXTRACT] =
    {
        .effect = EFFECT_SPICY_EXTRACT,  //atk up 2 def down 2, so a doubles support move
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0, // Supposedly never misses? needs a double check?
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_SpicyExtract,
        // The datamine master sheet mentions uncopiable by Metronome but that sounds odd? not yet implemented
    },
    //should make scovillian amazing but it never gets used
    //it can't stick around,

    [MOVE_SPIN_OUT] =
    {
        .effect = EFFECT_HIT,    //Todo // EFFECT_SPIN_OUT
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_2,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SpinOut,
    },

    [MOVE_POPULATION_BOMB] =
    {
        .effect = EFFECT_POPULATION_BOMB,    //
        .power = 20, //EFFECT_POPULATION_BOMB doesn't really need compare w my version of multihit this is moslty for rng seeding
        .type = TYPE_NORMAL, //of note multihit scripts all go to effect hit much simpler to setup multitask that way...
        .accuracy = 90, //vsonic important
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .metronomeBanned = TRUE,
        .strikeCount = 10,
        .multiTaskBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_PopulationBomb,
        //Supposedly uncallable by Metronome? (if so, needs implementation)
        //The master sheet mentions a "slicing" flag but I'm not sure what it refers to
    },

    [MOVE_ICE_SPINNER] =
    {
        .effect = EFFECT_ICE_SPINNER, //EFFECT_DAMAGE_SET_TERRAIN, //this is meant to remove terrain
        .power = 80,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.battleAnimScript = gBattleAnimMove_IceSpinner,
    },

    [MOVE_GLAIVE_RUSH] =
    {
        .effect = EFFECT_GLAIVE_RUSH,    //Todo // EFFECT_GLAIVE_RUSH
        .power = 120,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.battleAnimScript = gBattleAnimMove_GlaiveRush,
    },

    [MOVE_REVIVAL_BLESSING] =
    {
        .effect = EFFECT_REVIVAL_BLESSING,    //Todo // EFFECT_REVIVAL_BLESSING
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .healingMove = TRUE,
        .sketchBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_RevivalBlessing,
        // Uncallable by Metronome (to be implemented)
    },//move revives a selected fainted mon to 50% hp
    //doesn't cost user their life, also is meant to be excluded from PP up effects
    //beleive too good to be able to have priority

    [MOVE_SALT_CURE] =
    {
        .effect = EFFECT_HIT,    //Todo // EFFECT_SALT_CURE
        .power = 40,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SALT_CURE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_SaltCure,
        // Supposedly uncallable by Metronome, but dubious
    },
    //should  be status2, but isn't passed by baton pass

    [MOVE_TRIPLE_DIVE] =
    {
        .effect = EFFECT_TRIPLE_KICK,
        .power = 30,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 3,
        .multiTaskBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_TripleDive,
    },

    [MOVE_MORTAL_SPIN] =
    {
        .effect = EFFECT_HIT,    //Todo // EFFECT_MORTAL_SPIN
        .power = 30,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS(
        {
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_MortalSpin,
    },

    [MOVE_DOODLE] =
    {
        .effect = EFFECT_DOODLE,    //Todo // EFFECT_DOODLE
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED, // Supposedly unconfirmed? //can't target ally
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_Doodle,
        // Supposedly uncallable by Metronome (unimplemented)
    },
    //changes ability of user and ally to that of target
    //potentially need new target logic for this? select target but never ally

    [MOVE_FILLET_AWAY] =
    {
        .effect = EFFECT_FILLET_AWAY,    //Todo // EFFECT_FILLET_AWAY
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .argument = { .sacrificedHpPercentage = 50 },
        //.battleAnimScript = gBattleAnimMove_FilletAway,
        // Supposedly uncallable by Metronome (unimplemented)
    },
    //takes half hp (belly drum) but raises atk sp atk and speed 2 stages
    //could give priority but seems better withuot it?
    //yeah leaving at priority 0

    [MOVE_KOWTOW_CLEAVE] =
    {
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.battleAnimScript = gBattleAnimMove_KowtowCleave,
        // Needs a "slicing" flag (not sure what it refers to)
    },

    [MOVE_FLOWER_TRICK] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .alwaysCriticalHit = TRUE,
        //.battleAnimScript = gBattleAnimMove_FlowerTrick,
    },

    [MOVE_TORCH_SONG] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_TorchSong,
    },

    [MOVE_AQUA_STEP] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .danceMove = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_AquaStep,
    },

    [MOVE_RAGING_BULL] =
    {
        .effect = EFFECT_RAGING_BULL,    //works - brick break without immunity break, and breaks through protect but still takes touch effects
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        .ignoresProtect = TRUE, //needs effect makes still touch protect like
        //.battleAnimScript = gBattleAnimMove_RagingBull,
    },
    //change type based on tauros form,
    //since I changed tauros form may need change move type of first form
    //decide will keep fighitng type for base form
    //decided make dark type
    //most mon set screns are psychic/fairy I think so dark would hit better?
    //dark has more resistances I think, but overall no immunities at least
    //Should I make this break protect? should trigger effects
    //of contact based protects but still hit target
    //so an effect that is weaker than unseen fist
    //which competely bypasses protect
    //this would run through it instead
    //see how to setup since doesn't fully ignore protect

    [MOVE_MAKE_IT_RAIN] =
    {
        .effect = EFFECT_HIT,    //Todo // EFFECT_MAKE_IT_RAIN
        .power = 120,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
        },
        {
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .self = TRUE,
        }),*/
        // Uncallable by Metronome (to be implemented)
    },
    //payday and sp atk drop

    [MOVE_RUINATION] =
    {
        .effect = EFFECT_FIXED_PERCENT_DAMAGE,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .damagePercentage = 50 },
        .metronomeBanned = TRUE,
        .multiTaskBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_Ruination,
        // Uncallable by Metronome (to be implemented)
    },

    [MOVE_COLLISION_COURSE] =
    {
        .effect = EFFECT_COLLISION_COURSE,    //Todo // EFFECT_COLLISION_COURSE
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_CollisionCourse,
        // Uncallable by Metronome (to be implemented)
    },

    [MOVE_ELECTRO_DRIFT] =
    {
        .effect = EFFECT_COLLISION_COURSE,    //Todo // EFFECT_COLLISION_COURSE
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_ElectroDrift,
        // Uncallable by Metronome (to be implemented)
    },

    [MOVE_SHED_TAIL] =
    {
        .effect = EFFECT_SHED_TAIL,    //Todo // EFFECT_SHED_TAIL
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_ShedTail,
        // Uncallable by Metronome (to be implemented)
        // Supposedly unsnatchable?
    },
    //switch out user setup substitute for incoming mon,
    //also better without priority, not big deal,
    //but allows for slow switch

    [MOVE_CHILLY_RECEPTION] =
    {
        .effect = EFFECT_CHILLY_RECEPTION,    //Todo // EFFECT_CHILLY_RECEPTION
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_ChillyReception,
        // Supposedly uncallable by Metronome? (to be implemented)
    },
    //tells bad joke then switches out, sets hail/snow 5 turns as if used move hail
    //so is same idea switch out but also get move effect
    //same deal keep at prio 0
    //this move can combo w new cloud nine effect,
    //also curious about mega sceptile w regenerator running shed tail
    //into shedinja hmm

    [MOVE_TIDY_UP] =
    {
        .effect = EFFECT_TIDY_UP,    //Todo // EFFECT_TIDY_UP
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_TidyUp,
        // Supposedly uncallable by Metronome? (to be implemented)
        // Supposedly unsnatchable?
    },
    //clears spikes and substitute on field
    //then raises atk & speed one stage
    //signature of maushold

    [MOVE_SNOWESCAPE] =
    {
        .effect = EFFECT_SNOWESCAPE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.battleAnimScript = (B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL) ? gBattleAnimMove_Hail : gBattleAnimMove_Snowscape,
        // Currently an exact copy of Hail until we figure out what to do with it
    },
    //ok new idea, change to name icescape well might keep, as a pun for snow escape
    //but idea is weather setting but also trap
    //sets 5 turn hail for the duration the enemy can't switch
    //unsure if should include user or user side in hazard set for balance
    //keeping user from switching would make it not broken
    //but unsure if that's worth using vsonic
    //well if I did that, there are still effects
    //that could bypass the lock
    //such as uturn teleport etc.
    //emergency exit
    //somewhat like idea of having both snow and hail
    //and having them both perform differently.
    //ex. icescue's ice face ability would only activate in hail
    //regi ice's ability would only heal itself in hail etc.
    //snow cloak would only work in snow specifically
    //while some things like ice body could work in both
    //hail may be better for singles
    //snow better for vgc at first glance

    [MOVE_GRASSHOPPER] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_Pounce,
    },
    //renamed from pounce

    [MOVE_TRAILBLAZE] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.battleAnimScript = gBattleAnimMove_Trailblaze,
    },

    [MOVE_CHILLING_WATER] =
    {
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        },
        {
            .moveEffect = MOVE_EFFECT_FROSTBITE,
            .chance = 30,
        }),*/ //potentially drop to 20
        //.battleAnimScript = gBattleAnimMove_ChillingWater,
    },

    [MOVE_HYPER_DRILL] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_HyperDrill,
    },

    [MOVE_TWIN_BEAM] =
    {
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_TwinBeam,
    },

    [MOVE_RAGE_FIST] =
    {
        .effect = EFFECT_RAGE_FIST,    //Todo // EFFECT_RAGE_FIST
        .power = 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_RageFist,
    },//change annihalape evo to perform rage fist at max rage
    //rather than needing a new field I can set a flag like I do w region sand

    [MOVE_ARMOR_CANNON] =
    {
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .metronomeBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_ArmorCannon,
    },

    [MOVE_BITTER_BLADE] =
    {
        .effect = EFFECT_ABSORB,
        .power = 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .healingMove = TRUE,
        //.battleAnimScript = gBattleAnimMove_BitterBlade,
    },

    [MOVE_GIGATON_HAMMER] =
    {
        .effect = EFFECT_HIT,    //Todo // EFFECT_GIGATON_HAMMER
        .power = 160,
        .type = TYPE_STEEL, //self torment cant use move twice in a row normally
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .cantUseTwice = TRUE,
        //.battleAnimScript = gBattleAnimMove_GigatonHammer,
    },
    //move cant be used in succession, but not a recharge move.
    //(seems game freak realized how useless they were)
    //instad user isn't allowed to select move, similar to taunt etc.
    //so would need to set last used move is hammer add to locked
    //the seletion block can be bypassed by instruct and sleep talk successfully
    //but if done so via encore or choice items, the pokemon will instead struggle
    //summary don't think need special effect for this
    //eh guess can do as a new catgory of move
    //vsonic

    [MOVE_COMEUPPANCE] =
    {
        .effect = EFFECT_METAL_BURST,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        //.battleAnimScript = gBattleAnimMove_Comeuppance,
    },

    [MOVE_AQUA_CUTTER] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        //.battleAnimScript = gBattleAnimMove_AquaCutter,
        // Needs the "slicing" flag
    },//doesn't actually make contact

    [MOVE_BLAZING_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_BlazingTorque,
    },//think make these revaroom move tutor moves
    //if the gen 1 truck is in the game put an npc by it

    [MOVE_WICKED_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SLEEP,
            .chance = 10,
        }),*/
        //.battleAnimScript = gBattleAnimMove_WickedTorque,
    },//check update fo EE should have ability set move effect without needing new effect

    [MOVE_NOXIOUS_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_NoxiousTorque,
    },

    [MOVE_COMBAT_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_CombatTorque,
    },
    //may give to mega mewtwo x

    [MOVE_MAGICAL_TORQUE] =
    {
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),*/
        //.battleAnimScript = gBattleAnimMove_MagicalTorque,
    },
    //boosted up as pretty much only physical fairy move of strength

    /*[MOVE_PSYBLADE] =
    {
        .name = COMPOUND_STRING("Psyblade"),
        .description = COMPOUND_STRING(
            "This move's power increases\n"
            "when on Electric Terrain."),
        .effect = EFFECT_PSYBLADE,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Psyblade,
    },

    [MOVE_HYDRO_STEAM] =
    {
        .name = COMPOUND_STRING("Hydro Steam"),
        .description = COMPOUND_STRING(
            "This move's power increases\n"
            "under harsh sunlight."),
        .effect = EFFECT_HYDRO_STEAM,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .thawsUser = TRUE,
        .battleAnimScript = gBattleAnimMove_HydroSteam,
    },

    [MOVE_BLOOD_MOON] =
    {
        .name = COMPOUND_STRING("Blood Moon"),
        .description = COMPOUND_STRING(
            "Unleashes the blood moon.\n"
            "Can't be used twice in a row."),
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .cantUseTwice = TRUE,
        .battleAnimScript = gBattleAnimMove_BloodMoon,
    },

    [MOVE_MATCHA_GOTCHA] =
    {
        .name = COMPOUND_STRING("Matcha Gotcha"),
        .description = COMPOUND_STRING(
            "Absorbs half the damage\n"
            "inflicted. May cause a burn."),
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .thawsUser = TRUE,
        .metronomeBanned = TRUE,
        .healingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
        .battleAnimScript = gBattleAnimMove_MatchaGotcha,
    },

    [MOVE_SYRUP_BOMB] =
    {
        .name = COMPOUND_STRING("Syrup Bomb"),
        .description = COMPOUND_STRING(
            "Lowers the foe's speed\n"
            "each turn for 3 turns."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .ballisticMove = TRUE,
        .metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SYRUP_BOMB,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_SyrupBomb,
    },

    [MOVE_IVY_CUDGEL] =
    {
        .name = COMPOUND_STRING("Ivy Cudgel"),
        .description = COMPOUND_STRING(
            "Type changes with held mask.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_IVY_CUDGEL,
        .power = 100,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .enhancedCritrate = TRUE,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_IvyCudgel,
    },

    [MOVE_ELECTRO_SHOT] =
    {
        .name = COMPOUND_STRING("Electro Shot"),
        .description = COMPOUND_STRING(
            "Gathers electricity, then\n"
            "fires a high-voltage shot."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .argument.twoTurnAttack = { .stringId = STRINGID_ELECTROSHOTCHARGING, .status = WEATHER_RAIN_ANY },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .onChargeTurnOnly = TRUE,
            .sheerForceOverride = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_ElectroShot,
    },

    [MOVE_TERA_STARSTORM] =
    {
        .name = COMPOUND_STRING("Tera Starstorm"),
        .description = COMPOUND_STRING(
            "In Terapagos's Stellar\n"
            "Form, it hits all foes."),
        .effect = EFFECT_TERA_STARSTORM,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .assistBanned = TRUE,
        .copycatBanned = TRUE,
        .mimicBanned = TRUE,
        .sketchBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_TeraStarstorm,
    },

    [MOVE_FICKLE_BEAM] =
    {
        .name = COMPOUND_STRING("Fickle Beam"),
        .description = COMPOUND_STRING(
            "Shoots a beam of light.\n"
            "Sometimes twice as strong."),
        .effect = EFFECT_FICKLE_BEAM,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .battleAnimScript = gBattleAnimMove_FickleBeam,
    },

    [MOVE_BURNING_BULWARK] =
    {
        .name = COMPOUND_STRING("Burning Bulwark"),
        .description = COMPOUND_STRING(
            "Evades attack, and burns\n"
            "the foe if struck."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_BURNING_BULWARK },
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_BurningBulwark,
    },

    [MOVE_THUNDERCLAP] =
    {
        .name = COMPOUND_STRING("Thunderclap"),
        .description = sSuckerPunchDescription,
        .effect = EFFECT_SUCKER_PUNCH,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = SPLIT_SPECIAL,
        .battleAnimScript = gBattleAnimMove_Thunderclap,
    },

    [MOVE_MIGHTY_CLEAVE] =
    {
        .name = COMPOUND_STRING("Mighty Cleave"),
        .description = sFeintDescription,
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MightyCleave,
    },

    [MOVE_TACHYON_CUTTER] =
    {
        .name = COMPOUND_STRING("Tachyon Cutter"),
        .description = COMPOUND_STRING(
            "Launches particle blades at\n"
            "the target. Strikes twice."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .strikeCount = 2,
        .multiTaskBanned = TRUE,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TachyonCutter,
    },

    [MOVE_HARD_PRESS] =
    {
        .name = COMPOUND_STRING("Hard Press"),
        .description = sWringOutDescription,
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .battleAnimScript = gBattleAnimMove_HardPress,
    },

    [MOVE_DRAGON_CHEER] =
    {
        .name = COMPOUND_STRING("Dragon Cheer"),
        .description = COMPOUND_STRING(
            "Increases allies' critical hit\n"
            "ratio, especially if Dragons."),
        .effect = EFFECT_DRAGON_CHEER,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .category = SPLIT_STATUS,
        .ignoresSubstitute = TRUE,
        .battleAnimScript = gBattleAnimMove_DragonCheer,
    },

    [MOVE_ALLURING_VOICE] =
    {
        .name = COMPOUND_STRING("Alluring Voice"),
        .description = COMPOUND_STRING(
            "Confuses foe if its stats\n"
            "were boosted this turn."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .onlyIfTargetRaisedStats = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_AlluringVoice,
    },

    [MOVE_TEMPER_FLARE] =
    {
        .name = COMPOUND_STRING("Temper Flare"),
        .description = COMPOUND_STRING(
            "A desperation attack. Power\n"
            "doubles if last move failed."),
        .effect = EFFECT_STOMPING_TANTRUM,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .battleAnimScript = gBattleAnimMove_TemperFlare,
    },

    [MOVE_SUPERCELL_SLAM] =
    {
        .name = COMPOUND_STRING("Supercell Slam"),
        .description = COMPOUND_STRING(
            "An electrified slam. If it\n"
            "misses, the user is hurt."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .evasiveBreak = TRUE,
        .battleAnimScript = gBattleAnimMove_SupercellSlam,
    },

    [MOVE_PSYCHIC_NOISE] =
    {
        .name = COMPOUND_STRING("Psychic Noise"),
        .description = COMPOUND_STRING(
            "Sound waves that damage and\n"
            "prevent healing for 2 turns."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PSYCHIC_NOISE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_PsychicNoise,
    },

    [MOVE_UPPER_HAND] =
    {
        .effect = EFFECT_UPPER_HAND,
        .name = COMPOUND_STRING("Upper Hand"),
        .description = COMPOUND_STRING(
            "Makes the target flinch if\n"
            "readying a priority move."),
        .power = 65,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .category = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_UpperHand,
    },

    [MOVE_MALIGNANT_CHAIN] =
    {
        .name = COMPOUND_STRING("Malignant Chain"),
        .description = COMPOUND_STRING(
            "A corrosive chain attack\n"
            "that may badly poison."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = SPLIT_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = 50,
        }),
        .battleAnimScript = gBattleAnimMove_MalignantChain,
    },*/


    //Custom Moves 

    [MOVE_COCOON] =
    {
        .effect = EFFECT_COCOON,//EFFECT_COCOON,    //made its own effect because it also lowers speed
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
    }, //need change animation effect with new emerald graphics, it has a coccon effect already I can use.

    [MOVE_MONOTYPE] =
    {
        .effect = EFFECT_MONOTYPE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Sketch,
    },

    [MOVE_FLASH_FREEZE] =
    {
        .accuracy = 75, //85 was way too high
        .effect = EFFECT_NON_VOLATILE_STATUS,   //ice will o wisp - give to regice also need to make animation maybe just use sheer cold animation? done
        .power = 0,
        .type = TYPE_ICE,
        .pp = 10,  //consider making a 5 pp move, but sleep powder is 15, so is sing
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //since this keeps opponent from attacking will keep base priority
        .split = SPLIT_STATUS,
        .argument = { .nonVolatileStatus = MOVE_EFFECT_FREEZE },
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_FlashFreeze,
    },//lowered to 10 pp, since imobilizing status have lower pp to other similar variant moves
    //vsonic important keep an eye on

    [MOVE_DRYADS_CURSE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            .type = TYPE_GRASS,
        #else
            .type = TYPE_MYSTERY,
        #endif
        .effect = EFFECT_DRYADS_CURSE, //attempt lower self atk stat to set curse
        .power = 0,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,  //lowest priority set unless I can figure a way to make it use dmg from previous turn for calc
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = COMBO_STARTER_CURSE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DryadsCurse,
    },//DOES ghost curse effect to last damaged sacrificin stats instead of health
    //give to bug fairy and grass types   def give shiinotic, maybe sudowoodo
    //since I'm applying affect to mon that hit me last I have to take damage
    //that already makes it equal to loss of sacrificing hp to activate curse
    //think droppign stat as well is too much
    //do work on this don't want make -6 priority
    //instead want to set status so applies curse to next mon to hit
    //can do move end effect make like destiny bond
    //set timer or status then make move end effect
    //if attacker does damage to target with timer
    //set curse upon them

    [MOVE_SHIELD_BASH] =
    {
        .effect = EFFECT_SHIELD_BASH, //does protect script but doesn't cancel moves. should play endure brace script?
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .split = SPLIT_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .argument = { .protectMethod = PROTECT_SHIELD_BASH },
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShieldBash,
    }, //vsonic when stable test new moves if work can then add new post gen3 learnsets in
    //decide want to give to chespin line as well
    /*so I'm thinking of putting it up to 70% since it's mostly as a scout like you said,
and if the move is preparing to block their body with a shield before hand.
the dr should be higher, and its to keep them from being taken out of the fight
rom taking a special attack, since many w high def have low sp def*/

/*shield bash -  signature move for shield mon,    mon with physical shields. and protect like moves king shield baneful bunker etc.
[shieldon/bastiodon line, chesnaught, etc.  think will give to shieeldon line as an evolution move
priority move mon blocks body with their shield, and counter attacks
if hit with physical/contact move (like spike shield) damage is based on defense stat.
defense/2 = base power or dynamicbasepower

during turn mon gains 35%-70% damage reduction
(will make special status, so can store effect & clear each turn.)*/

/* ok base 70 % dmg reduc, if against a super effecive move it goes up to 85 % ?
but you lose counter attack
use wonder gaurd logic to determine its super effective
*/
    [MOVE_UP_ROOT] =
    {
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_UTurn,
    },

    [MOVE_DIVE_BOMB] =
    {
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_UTurn,
    },

    [MOVE_NETTLE_WHIP] =
    {
        .effect = EFFECT_NETTLE_WHIP, //in set move effect put not grass check
        .power = 85,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .damagesAirborne = TRUE,
        .argument = { .storedValue = TYPE_GRASS },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),*/
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_GROWTH},
        //.battleAnimScript = gBattleAnimMove_VineWhip,
    },//GRASS types will be immune to this status condition, potentially make its own effect, then can do grass status exclusion with bs command
    //think give to mostly grass/poison types
    //since effect is essentially poison
    //differet kind of burn but is still burn
    //is more like a chemical burn than a fire burn
    //think may setup to bypass fire type immunity?
    //ok will do both will make its own effect so can get around burn
    //otherwise keep effect for specific status setting
    
    [MOVE_SONIC_BOOM] =
    {
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .argument = MOVE_EFFECT_CONFUSION,
        /*.additionalEffects = ADDITIONAL_EFFECTS(
            {
                .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
                .self = TRUE,
                .chance = 100,
            },
            {
                .moveEffect = MOVE_EFFECT_CONFUSION,
                .chance = 10,
            }),*/
    },//since effect is affects user its already certain
    //think give this uproar effect as well, good idea
    //to have more sleep control in game even with rebalance
    //only give to expert flyers garchomp too

    [MOVE_OVER_MAX_POWER] =
    {
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE, //remember plan to set this up for entire battle 
        .power = 150,       //think will do by storing move used, and removing type based on that, potentially set a status?
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .storedValue = TYPE_PSYCHIC },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),*/
    },

    [MOVE_SHIMON] =
    {
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .argument = { .storedValue = TYPE_FIGHTING },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),*/
    },

    [MOVE_FINAL_FLIGHT] =
    {
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 150,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        //.enhancedCritrate = TRUE, //this is prob too much no? vsonic
        .argument = { .storedValue = TYPE_FLYING },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),*/
    },//Check flying type average stats, see if need to make this physical
    //idea is user pushes themselves to the limit, and gives everything they have to perform an acrobatic feat  /vsonic
    //let pidgeot get but think this should be a tutor move?
    //decide give crit as exemplary of flying

    [MOVE_PLASMA_RAILGUN] =
    {
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 150,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .storedValue = TYPE_ELECTRIC },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),*/
    },

    [MOVE_BOLTBEAM] =
    {
        .effect = EFFECT_TWO_TYPED_MOVE,
        .power = 90,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
       .argument = { .storedValue = TYPE_ELECTRIC },
       /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE,
            .chance = 30,
        }),*/
    },
    //two typed attack w chance to freeze

    [MOVE_BACK_STAB] =
    {
        .power = 100,
        .effect = EFFECT_SUCKER_PUNCH, //EFFECT_SUCKER_PUNCH either let attack regardless or make only work when target is gearing up an attack
        .type = TYPE_DARK,
        .accuracy = 90, //feel like i need to make this base 90?    //should be good moves like hyper beam are base 90 and still good.
        .pp = 5,    //should be a TM move, exclusive to dark types
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .enhancedCritrate = TRUE,
    },  //point of move isn't necessarily to replace sucker punch, but instead to be an option for slower dark types to take advantage of new dark type change
    //so only give to mon that DON'T get sucker punch and make sure to keep sparse
    //like say give to guzzlord

    [MOVE_DOUBLE_SHOCK] =
    {
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 150,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .metronomeBanned = TRUE,
        .argument = { .storedValue = TYPE_ELECTRIC },
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),*/
        //.battleAnimScript = gBattleAnimMove_DoubleShock,
    },//making all losetype 150 because changing effect to last entire battle not just until switch out, also keeping move as my version was special

    [MOVE_POUNCE] =
    {
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Pounce,
    },//normal or dark type  thought up with luxray line in mind and zenmodeYT  
    //keeping normal

    [MOVE_CHEAP_SHOT] =
    {
        .effect = EFFECT_HIT_ESCAPE,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -1,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_CheapShot,
    },//made for crabominable line but can give to machamp as well


    [MOVE_SNOWBALL] =
    {
        .effect = EFFECT_SNOWBALL,  //changed
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .ballisticMove = TRUE,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 15,
        }),*/
        //.contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        //.contestCategory = CONTEST_CATEGORY_CUTE,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_Snowball,
    }, //still need get animatino how I want to change sprite size with ppower
    //3 stage effect diff power like ice ball want change anim based on power

    [MOVE_TRENCH_RUN] =
    {
        .effect = EFFECT_TRENCH_RUN,  //need make its own effect, planned evasion up 2 and grounds battler like roost
        .power = 0,
        .type = TYPE_FLYING, //almost got it, made 4 turn effect
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0, //weight this as flying mon are fast, may make 0 priority so its an option more for faster birds not just all
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_TrenchRun,
    },
    //maybe just drop effect evasion boosting is annoying
    //this is better double team plus runs counter to flying affinity buff
    //well is cool idea think will keep
    //especially if I can get the bee figher jet fake mon


    [MOVE_SPIN_DASH] =
    {
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .damagesAirborne = TRUE,
        .ballisticMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DEFENSE_CURL},
        //.battleAnimScript = gBattleAnimMove_SpinDash,
    },//uses rollout animation
    //why didn't I make this damage in air?
    //hmm I guess because it requries a launching pad?
    //sonic use it to hit aerial targets all the time, changing this

    [MOVE_ARCTIC_RAKE] =
    {
        .effect = EFFECT_TWO_TYPED_MOVE,
        .power = 70,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
       .argument = { .storedValue = TYPE_DARK },
        .enhancedCritrate = TRUE,
        .slicingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ArcticRake,
    }, //alt slash wnat use shadow claw animation, two claws one white one black slashing enemy
    //think get move at 35 or so?
    //think was mostly for sneasal
    //Think doesn't make contact cuz like aqua cutter attacks with wave of ice and shadow

    
    [MOVE_CONVERSION_Z] =
    {
        .effect = EFFECT_CONVERSION_Z,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1, //can change priority when finish new effect as not based on last move hit by
        .split = SPLIT_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ConversionZ,
    },

    [MOVE_SOLAR_FLARE] =
    {
        .effect = EFFECT_SPEED_DOWN,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),*/
        //.contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SolarFlare,
    },//think may keep priority at 0,
    //flinch chance is low but as it hits both
    //still a good idea to lower
    //idea is flinch from heat not brightness
    //still to do add animation for now using superpower
    //signature for solrock, 
    //later rework animation combine superpower charge effect
    //w heatwave animation
    //maybe charge glow with fire spin going around it 
    //then heatwave and do enemy knock back?
    //Note superpower anim broken by speed up
    //vsonic

    [MOVE_MUDSLIDE] =
    {
        .effect = EFFECT_HIT,
        .power = 95,        
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY, //same debuff as surf but much  more manageable as can just avoid by floating
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .cantdamageFloating = TRUE,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 20,
        }),*/
         //.contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_MUDSLIDE,
        //.contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        //.battleAnimScript = gBattleAnimMove_Mudslide,
    },
    //think I need drop this to acc 90
    //otherwise not much reason to use earth power
    //mix of heat wave and surf
    //vsonic still todo add new moves to leanrsets
    //idk maybe would make this a tm?
    //ah right I made this to have some good special moves
    //for rogenrolla

    [MOVE_SPICE_TRADE] =
    {
        .effect = EFFECT_OVERWRITE_ABILITY, //new effect change target ability 
        .power = 0,
        .type = TYPE_FIRE, //similar to move entrainmet will default to that animation temp
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .split = SPLIT_STATUS,
        .magicCoatAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        .argument = { .storedValue = ABILITY_HEAT_TRANCE },
        //.battleAnimScript = gBattleAnimMove_SpiceTrade,
    },//didn't realize but didn't need make a new effect for
    //this is just what worry seed etc. does
    /*
        @make imperfect acc as very strong
        @and idea is sharing spicy food target may not like it
        @hmm ok if I make this a categorical effect
        @it'll have 90 acc but as scovillain exclussive make perf acc
        @dont want to run into flying type acc debuff when I'm tryign to use it smh
        @think would also make 0 priority for categorical effect
    */

    [MOVE_PEPPER_POPPER] =
    {
        .effect = EFFECT_SPEED_UP_2, //new effect change target ability 
        .power = 0,
        .type = TYPE_FIRE, //unsure if should be type grass or fire
        .accuracy = 0, //capsakid not fire yet so guess keep as grass move? hmm nah make fire
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        //.contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        //.battleAnimScript = gBattleAnimMove_Agility,
    },
    //temp animation accupressure
    //capsakid can learn this
    //ah forgot this was meant to be new evo learn move
    //since the move it does learn is next to useless in solo play


    [MOVE_STEEL_SURGE] =
    {
        #if B_UPDATED_MOVE_DATA >= GEN_5
            #else
            #endif
        .effect = EFFECT_STEEL_SURGE,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = TRUE,
        .forcePressure = TRUE,
        //.contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_SteelSurge,
    },
    //turned g max move into regualr move
    //still give to copperajah
    //and good counter balance for fairy/ice
    //copperajah signature but give to more mon
    //rn just uses spikes anim, 

    [MOVE_DIRT_NAP] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .cantdamageFloating = TRUE,
    },
    //dirt nap and respite 
    //meant to be new category move effect
    //something between protect and sucker punch
    //but using semi invulnerable status to hide 
    //may make flying variant, soar
    //point is to have more ways of taking advantage of
    //2x dmg underground/underwater with only 1 move apeice
    //theres no real reason/means of taking advantage of it
    //thought about putting healign on effect but must be tired
    //as that's way too good/strong/defining
    //point of effect is just to be protect
    //writing for later wi clear head
    //if I did add healing what I would do is
    //debuff clear and small heal if by end of turn
    //it wasn't attacked.
    //so hide at start of turn attack if was attacked,
    //while dodging attack,
    //but if no one attacked it would act last
    //return to field refreshed and do maybe 25% 
    //or 15% heal

    [MOVE_WATERY_GRAVE] =
    {
        .effect = EFFECT_SKY_DROP, // Needs a custom move effect
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .ignoresRedirection = TRUE,
    },//give to SPECIES_DHELMISE
    //idea drags targetted foe underwater

    [MOVE_SEAFLOOR_RESPITE] =
    {
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
    },

    [MOVE_BRUTE_FORCE] =
    {
        .effect = EFFECT_RECOIL,
        .power = 130,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
        .recoilMove = TRUE,
        .punchingMove = TRUE,
        //.contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        //.contestCategory = CONTEST_CATEGORY_TOUGH,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        //.battleAnimScript = gBattleAnimMove_BruteForce,
    },
    //super power clone

    [MOVE_SHOCKING_MALICE] =
    {
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        /*.additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .onlyIfTargetRaisedStats = TRUE,
            .chance = 100,
        }),*/
        //.contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_ShockingMalice,
    },
    //burning jealousy clone
    //may not be that big of a deal but think never give to thunderous
    //just need check emerald for how they track status boost
    //gave effect to reshiram too but this move means more for zekrom
    //as it has a reliable acc stab special move
    //to get around intimidate lock
    //w sheerforce life orb 
    //and if you're able to setup the paralysis doesn't even matter
    //if you don't finish in one hit they'll be too slow
    //on following turn

    [MOVE_MOONDANCE] =
    {
        .effect = EFFECT_MOONDANCE,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_MOONDANCE,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_MoonDance,
    },
    //EFFECT_MOONDANCE //intentional spelling don't add space

    [MOVE_ACID_RAIN] =
    {
        .effect = EFFECT_ACID_RAIN,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = COMBO_STARTER_ACID_RAIN,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_AcidRain,
    },
    
    [MOVE_COLD_FRONT] =
    {
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 120,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNTOOKSUNLIGHT, .status = WEATHER_HAIL_ANY },
        //.contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_HAIL},
        //.battleAnimScript = gBattleAnimMove_ColdFront,
    },
    //will be ice move that fires in one turn
    //if in hail
    //w addition snow make ice weather constant
    
    [MOVE_LIFE_DRAIN] =
    {
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .makesContact = TRUE,
    },//decide make phsyical counter of shadow ball, but healings
    //undecided if should make tm

    [MOVE_DARK_SWAMP] =
    {
        .effect = EFFECT_ABSORB,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .split = SPLIT_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = TRUE,
    },
    //made 60 bp to continue trend of oddly broken dark moves category

    [MOVE_SNOW_DAY] =
    {
        .effect = EFFECT_SNOW_DAY,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS, //change use calming effect
        //.contestCategory = CONTEST_CATEGORY_BEAUTY,
        //.contestComboStarterId = COMBO_STARTER_HAIL,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_Snowscape
    },
    //snowday replaces original snowscape

    [MOVE_FOG_HORN] =
    {
        .effect = EFFECT_FOG,
        .power = 0,
        .type = TYPE_NORMAL, //idk stuck between water normal or sound
        .accuracy = 0, //
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 1,
        .split = SPLIT_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        //.contestCategory = CONTEST_CATEGORY_SMART,
        //.contestComboStarterId = COMBO_STARTER_HAIL,
        //.contestComboMoves = {0},
        //.battleAnimScript = (B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW) ? gBattleAnimMove_Snowscape : gBattleAnimMove_Hail,
    },

    //name pending
    [MOVE_SHADOW_STRIKE] =
    {
        .effect = EFFECT_DRAGON_DARTS,
        .power = 25,
        .type = TYPE_DARK, //I can chese this actually, since single target effects only hit single target, make target both, and specific bs command for it, put effect in multihit 
        .accuracy = 100, //switch case, and have it read the number of enemies on enemy side, if 2 set to 1 hit, if 1 set to 2 hits
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .split = SPLIT_PHYSICAL,
        .strikeCount = 4,
        .multiTaskBanned = TRUE,
        .parentalBondBanned = TRUE,
        //new category effect at moveend
        //set special protectstatus one turn stat boost
        //will store stat to boost from storedValue
        //convenient since value 0 is hp 
        //overall same as how protect method is stored
        //unsure how will do this, can do with moveproperty
        //or a move effect to set status
        .argument = {
        .moveProperty = MOVE_EFFECT_SHADOW_STRIKE,
        .storedValue = STAT_EVASION},       
        //.contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {0},
        //.battleAnimScript = gBattleAnimMove_DragonDarts,
    },
    //for anim do double team animation and then something like
    //beatup

    [MOVE_FENCE] =
    {
        .priority = 4,
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .split = SPLIT_STATUS,
        .argument = { .protectMethod = PROTECT_FENCE },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        //.contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        //.contestCategory = CONTEST_CATEGORY_COOL,
        //.contestComboStarterId = 0,
        //.contestComboMoves = {COMBO_STARTER_TAUNT},
        //.battleAnimScript = gBattleAnimMove_Detect,
    },//name is funny double entendre
    //fence meaning a means of protection
    //and fance meaning a person who receives stolen goods

};
