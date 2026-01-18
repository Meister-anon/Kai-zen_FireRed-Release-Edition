#include "global.h"
#include "gflib.h"
#include "constants/battle_string_ids.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_util.h"
#include "strings.h"
#include "battle_message.h"
#include "link.h"
#include "event_scripts.h"
#include "event_data.h"
#include "item.h"
#include "battle_tower.h"
#include "trainer_tower.h"
#include "battle_setup.h"
#include "field_specials.h"
#include "new_menu_helpers.h"
#include "battle_controllers.h"
#include "graphics.h"
#include "random.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/trainer_classes.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

static EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {};
static EWRAM_DATA struct BattleMsgData *sBattleMsgDataPtr = NULL;

static void ChooseMoveUsedParticle(u8 *textPtr);
static void ChooseTypeOfMoveUsedString(u8 *textPtr);
static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst);

static const u8 sText_Empty1[] = _("");
static const u8 sText_space[] = _(" ");
static const u8 sText_Trainer1LoseText[] = _("{B_TRAINER1_LOSE_TEXT}");
static const u8 sText_Trainer2Class[] = _("{B_TRAINER2_CLASS}");
static const u8 sText_Trainer1RecallPkmn1[] = _("{B_TRAINER1_NAME}: {B_OPPONENT_MON1_NAME}, come back!");
static const u8 sText_Trainer1WinText[] = _("{B_TRAINER1_WIN_TEXT}");
static const u8 sText_Trainer1RecallPkmn2[] = _("{B_TRAINER1_NAME}: {B_OPPONENT_MON2_NAME}, come back!");
static const u8 sText_Trainer1RecallBoth[] = _("{B_TRAINER1_NAME}: {B_OPPONENT_MON1_NAME} and\n{B_OPPONENT_MON2_NAME}, come back!");
static const u8 sText_Trainer2Name[] = _("{B_TRAINER2_NAME}");
static const u8 sText_PkmnGainedEXP[] = _("{B_BUFF1} gained{B_BUFF2}\n{B_BUFF3} EXP. Points!\p");
static const u8 sText_EmptyString4[] = _("");
static const u8 sText_ABoosted[] = _(" a boosted");
static const u8 sText_PkmnGrewToLv[] = _("{B_BUFF1} grew to\nLV. {B_BUFF2}!{WAIT_SE}\p");
static const u8 sText_PkmnLearnedMove[] = _("{B_BUFF1} learned\n{B_BUFF2}!{WAIT_SE}\p");
static const u8 sText_TryToLearnMove1[] = _("{B_BUFF1} is trying to\nlearn {B_BUFF2}.\p");
static const u8 sText_TryToLearnMove2[] = _("But, {B_BUFF1} can't learn\nmore than four moves.\p");
static const u8 sText_TryToLearnMove3[] = _("Delete a move to make\nroom for {B_BUFF2}?");
static const u8 sText_PkmnForgotMove[] = _("{B_BUFF1} forgot\n{B_BUFF2}.\p");
static const u8 sText_ConfirmForgetMove[] = _("{PAUSE 32}Are you sure you want to\nforget {B_BUFF2}?");
static const u8 sText_StopLearningMove[] = _("{PAUSE 32}Stop learning\n{B_BUFF2}?");
static const u8 sText_DidNotLearnMove[] = _("{B_BUFF1} did not learn\n{B_BUFF2}.\p");
static const u8 sText_UseNextPkmn[] = _("Use next POKéMON?");
static const u8 sText_AttackMissed[] = _("{B_ATK_NAME_WITH_PREFIX}'s\nattack missed!");
static const u8 sText_PkmnProtectedItself[] = _("{B_DEF_NAME_WITH_PREFIX}\nprotected itself!");
static const u8 sText_AvoidedDamage[] = _("{B_DEF_NAME_WITH_PREFIX} avoided\ndamage with {B_DEF_ABILITY}!");
static const u8 sText_PkmnNullifyTypeViaAbility[] = _("{B_DEF_NAME_WITH_PREFIX} nullifies {B_BUFF1}\nmoves with {B_DEF_ABILITY}!");
static const u8 sText_PkmnMakesGroundMiss[] = _("{B_DEF_NAME_WITH_PREFIX} can float!\nGROUND-based moves can't hit it!{PAUSE 8}"); //gave pause to be able to read better
static const u8 sText_GroundNullifiesEarth[] = _("GROUND Types can't be blinded\nby Earth attacks!{PAUSE 5}"); //type name buffer make
static const u8 sText_PkmnRoosting[] = _("{B_ATK_NAME_WITH_PREFIX} is resting\non the ground.");
static const u8 sText_PkmnRoostEnds[] = _("{B_ATK_NAME_WITH_PREFIX} stopped roosting\nand took to the air!{PAUSE 15}"); //needed pause to read long message
static const u8 sText_PkmnAvoidedAttack[] = _("{B_DEF_NAME_WITH_PREFIX} avoided\nthe attack!");
static const u8 sText_ItDoesntAffect[] = _("It doesn't affect\n{B_DEF_NAME_WITH_PREFIX}…");
static const u8 sText_AttackerFainted[] = _("{B_ATK_NAME_WITH_PREFIX}\nfainted!\p");
static const u8 sText_TargetFainted[] = _("{B_DEF_NAME_WITH_PREFIX}\nfainted!\p");
static const u8 sText_PlayerGotMoney[] = _("{B_PLAYER_NAME} got ¥{B_BUFF1}\nfor winning!\p");
static const u8 sText_PlayerWhiteout[] = _("{B_PLAYER_NAME} is out of\nusable POKéMON!\p");
static const u8 sText_PlayerPanicked[] = _("{B_PLAYER_NAME} panicked and lost ¥{B_BUFF1}…\p… … … …\p{B_PLAYER_NAME} whited out!{PAUSE_UNTIL_PRESS}");
static const u8 sText_PlayerWhiteoutAgainstTrainer[] = _("{B_PLAYER_NAME} is out of\nusable POKéMON!\pPlayer lost against\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!{PAUSE_UNTIL_PRESS}");
static const u8 sText_PlayerPaidAsPrizeMoney[] = _("{B_PLAYER_NAME} paid ¥{B_BUFF1} as the prize\nmoney…\p… … … …\p{B_PLAYER_NAME} whited out!{PAUSE_UNTIL_PRESS}");
static const u8 sText_PlayerWhiteout2[] = _("{B_PLAYER_NAME} whited out!{PAUSE_UNTIL_PRESS}");
static const u8 sText_PreventsEscape[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} prevents\nescape with {B_SCR_ACTIVE_ABILITY}!\p");
static const u8 sText_CantEscape2[] = _("Can't escape!\p");
static const u8 sText_AttackerCantEscape[] = _("{B_ATK_NAME_WITH_PREFIX} can't escape!");
static const u8 sText_HitXTimes[] = _("Hit {B_BUFF1} time(s)!");
static const u8 sText_PkmnGotFrostbite[] = _("{B_EFF_NAME_WITH_PREFIX} got frostbite!");
static const u8 sText_PkmnFellAsleep[] = _("{B_EFF_NAME_WITH_PREFIX}\nfell asleep!");
static const u8 sText_PkmnMadeSleep[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade {B_EFF_NAME_WITH_PREFIX} sleep!");
static const u8 sText_PkmnAlreadyAsleep[] = _("{B_DEF_NAME_WITH_PREFIX} is\nalready asleep!");
static const u8 sText_PkmnAlreadyAsleep2[] = _("{B_ATK_NAME_WITH_PREFIX} is\nalready asleep!");
static const u8 sText_PkmnWasntAffected[] = _("{B_DEF_NAME_WITH_PREFIX}\nwasn't affected!");
static const u8 sText_PkmnWasPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX}\nwas poisoned!");
static const u8 sText_PkmnPoisonedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\npoisoned {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtByPoison[] = _("{B_ATK_NAME_WITH_PREFIX} is hurt\nby poison!");
static const u8 sText_PkmnAlreadyPoisoned[] = _("{B_DEF_NAME_WITH_PREFIX} is already\npoisoned.");
static const u8 sText_PkmnBadlyPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX} is badly\npoisoned!");
static const u8 sText_PkmnEnergyDrained[] = _("{B_DEF_NAME_WITH_PREFIX} had its\nenergy drained!");
static const u8 sText_PkmnWasBurned[] = _("{B_EFF_NAME_WITH_PREFIX} was burned!");
static const u8 sText_PkmnBurnedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nburned {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtByBurn[] = _("{B_ATK_NAME_WITH_PREFIX} is hurt\nby its burn!");
static const u8 sText_PkmnHurtByFrost[] = _("{B_ATK_NAME_WITH_PREFIX} is hurt\nby the cold!");
static const u8 sText_PkmnHurtByFrostbite[] = _("{B_ATK_NAME_WITH_PREFIX} is hurt\nby frostbite!");
static const u8 sText_PkmnAlreadyHasBurn[] = _("{B_DEF_NAME_WITH_PREFIX} already\nhas a burn.");
static const u8 sText_PkmnWasFrozen[] = _("{B_EFF_NAME_WITH_PREFIX} was\nfrozen!");
static const u8 sText_PkmnFrozenBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nfroze {B_EFF_NAME_WITH_PREFIX} solid!");
static const u8 sText_PkmnIsFrozen[] = _("{B_ATK_NAME_WITH_PREFIX} is\nfrozen solid!");
static const u8 sText_PkmnWasAlreadyFrozen[] = _("{B_DEF_NAME_WITH_PREFIX} is already\nfrozen.");
static const u8 sText_PkmnWasDefrosted[] = _("{B_DEF_NAME_WITH_PREFIX} was\ndefrosted!");
static const u8 sText_PkmnDefrosted[] = _("{B_ATK_TEAM1} {B_SCR_ACTIVE_NAME_WITH_PREFIX} was\ndefrosted!"); //why?? prob remove this
static const u8 sText_PkmnWasDefrosted2[] = _("{B_ATK_NAME_WITH_PREFIX} was\ndefrosted!");
static const u8 sText_PkmnWasDefrostedBy[] = _("{B_ATK_NAME_WITH_PREFIX} was\ndefrosted by {B_CURRENT_MOVE}!");
static const u8 sText_PkmnWasParalyzed[] = _("{B_EFF_NAME_WITH_PREFIX} is paralyzed!\nIt may be unable to move!");
static const u8 sText_PkmnWasParalyzedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nparalyzed {B_EFF_NAME_WITH_PREFIX}!\lIt may be unable to move!");
static const u8 sText_PkmnIsParalyzed[] = _("{B_ATK_NAME_WITH_PREFIX} is paralyzed!\nIt can't move!");
static const u8 sText_PkmnIsAlreadyParalyzed[] = _("{B_DEF_NAME_WITH_PREFIX} is\nalready paralyzed!");
static const u8 sText_PkmnHealedParalysis[] = _("{B_DEF_NAME_WITH_PREFIX} was\nhealed of paralysis!");
static const u8 sText_PkmnDreamEaten[] = _("{B_DEF_NAME_WITH_PREFIX}'s\ndream was eaten!");
static const u8 sText_StatsWontIncrease[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\nwon't go higher!");
static const u8 sText_StatsWontDecrease[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwon't go lower!");
static const u8 sText_TeamStoppedWorking[] = _("Your team's {B_BUFF1}\nstopped working!");
static const u8 sText_FoeStoppedWorking[] = _("The foe's {B_BUFF1}\nstopped working!");
static const u8 sText_PkmnIsConfused[] = _("{B_ATK_NAME_WITH_PREFIX} is\nconfused!");
static const u8 sText_PkmnHealedConfusion[] = _("{B_ATK_NAME_WITH_PREFIX} snapped\nout of confusion!");
static const u8 sText_PkmnWasConfused[] = _("{B_EFF_NAME_WITH_PREFIX} became\nconfused!");
static const u8 sText_PkmnAlreadyConfused[] = _("{B_DEF_NAME_WITH_PREFIX} is\nalready confused!");
static const u8 sText_PkmnFellInLove[] = _("{B_DEF_NAME_WITH_PREFIX}\nfell in love!");
static const u8 sText_PkmnInLoveWithBattler[] = _("{B_ATK_NAME_WITH_PREFIX} is in love\nwith {B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnInLove[] = _("{B_ATK_NAME_WITH_PREFIX} is in love!");
static const u8 sText_PkmnImmobilizedByLove[] = _("{B_ATK_NAME_WITH_PREFIX} is\nimmobilized by love!");
static const u8 sText_PkmnBlownAway[] = _("{B_DEF_NAME_WITH_PREFIX} was\nblown away!");
static const u8 sText_PkmnChangedType[] = _("{B_ATK_NAME_WITH_PREFIX} transformed\ninto the {B_BUFF1} type!");
static const u8 sText_PkmnFlinched[] = _("{B_ATK_NAME_WITH_PREFIX} flinched!");
static const u8 sText_PkmnRegainedHealth[] = _("{B_DEF_NAME_WITH_PREFIX} regained\nhealth!");
static const u8 sText_PkmnHPFull[] = _("{B_DEF_NAME_WITH_PREFIX}'s\nHP is full!");
static const u8 sText_PkmnRaisedSpDef[] = _("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised SP. DEF!");
static const u8 sText_PkmnRaisedSpDefALittle[] = _("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised SP. DEF a little!");
static const u8 sText_PkmnRaisedDef[] = _("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised DEFENSE!");
static const u8 sText_PkmnRaisedDefALittle[] = _("{B_ATK_PREFIX2}'s {B_CURRENT_MOVE}\nraised DEFENSE a little!");
static const u8 sText_PkmnCoveredByVeil[] = _("{B_ATK_PREFIX2}'s party is covered\nby a veil!");
static const u8 sText_PkmnUsedSafeguard[] = _("{B_DEF_NAME_WITH_PREFIX}'s party is protected\nby SAFEGUARD!");
static const u8 sText_PkmnSafeguardExpired[] = _("{B_ATK_PREFIX3}'s party is no longer\nprotected by SAFEGUARD!");
static const u8 sText_PkmnWentToSleep[] = _("{B_ATK_NAME_WITH_PREFIX} went\nto sleep!");
static const u8 sText_PkmnSleptHealthy[] = _("{B_ATK_NAME_WITH_PREFIX} slept and\nbecame healthy!");
static const u8 sText_PkmnWellRested[] = _("{B_ATK_NAME_WITH_PREFIX} is\nwell rested!");
static const u8 sText_PkmnWhippedWhirlwind[] = _("{B_ATK_NAME_WITH_PREFIX} whipped\nup a whirlwind!");
static const u8 sText_PkmnTookSunlight[] = _("{B_ATK_NAME_WITH_PREFIX} took\nin sunlight!");
static const u8 sText_PkmnLoweredHead[] = _("{B_ATK_NAME_WITH_PREFIX} lowered\nits head!");
static const u8 sText_PkmnIsGlowing[] = _("{B_ATK_NAME_WITH_PREFIX} is glowing!");
static const u8 sText_PkmnFlewHigh[] = _("{B_ATK_NAME_WITH_PREFIX} flew\nup high!");
static const u8 sText_PkmnDugHole[] = _("{B_ATK_NAME_WITH_PREFIX} dug a hole!");
static const u8 sText_PkmnHidUnderwater[] = _("{B_ATK_NAME_WITH_PREFIX} hid\nunderwater!");
static const u8 sText_PkmnSprangUp[] = _("{B_ATK_NAME_WITH_PREFIX} sprang up!");
static const u8 sText_PkmnSqueezedByBind[] = _("{B_DEF_NAME_WITH_PREFIX} was squeezed by\n{B_ATK_NAME_WITH_PREFIX}'s BIND!");
static const u8 sText_PkmnTrappedInVortex[] = _("{B_DEF_NAME_WITH_PREFIX} was trapped\nin the vortex!");
static const u8 sText_PkmnTrappedBySandTomb[] = _("{B_DEF_NAME_WITH_PREFIX} was trapped\nby SAND TOMB!");
static const u8 sText_PkmnWrappedBy[] = _("{B_DEF_NAME_WITH_PREFIX} was WRAPPED by\n{B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnClamped[] = _("{B_ATK_NAME_WITH_PREFIX} CLAMPED\n{B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtBy[] = _("{B_ATK_NAME_WITH_PREFIX} is hurt\nby {B_BUFF1}!");
static const u8 sText_PkmnHurtEmpathCurse[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} suffered\nthe {B_DEF_ABILITY}!");
static const u8 sText_PkmnFreedFrom[] = _("{B_ATK_NAME_WITH_PREFIX} was freed\nfrom {B_BUFF1}!");
static const u8 sText_BindMoveOutofPP[] = _("{B_BUFF1} ran out PP!");
static const u8 sText_PkmnCrashed[] = _("{B_ATK_NAME_WITH_PREFIX} kept going\nand crashed!");
const u8 gBattleText_MistShroud[] = _("{B_ATK_PREFIX2} became\nshrouded in MIST!"); //using mist
static const u8 sText_PkmnProtectedByMist[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is protected\nby MIST!");  //when targetted with mist up
const u8 gBattleeText_BlackFog[] = _("A uneartly dark fog has covered the field!");
static const u8 sText_BlackFogPersists[] = _("The dark fog still refuses to lift!"); //change to something more creepy
const u8 gBattleText_GetPumped[] = _("{B_ATK_NAME_WITH_PREFIX} is getting\npumped!");
static const u8 sText_PkmnHitWithRecoil[] = _("{B_ATK_NAME_WITH_PREFIX} is hit\nwith recoil!");
static const u8 sText_PkmnProtectedItself2[] = _("{B_ATK_NAME_WITH_PREFIX} protected\nitself!");
static const u8 sText_PkmnBuffetedBySandstorm[] = _("{B_ATK_NAME_WITH_PREFIX} is buffeted\nby the sandstorm!");
static const u8 sText_PkmnPeltedByHail[] = _("{B_ATK_NAME_WITH_PREFIX} is pelted\nby HAIL!");
static const u8 sText_PkmnsXWoreOff[] = _("{B_ATK_PREFIX1}'s {B_BUFF1}\nwore off!");
static const u8 sText_PkmnSeeded[] = _("{B_DEF_NAME_WITH_PREFIX} was seeded!");
static const u8 sText_PkmnEvadedAttack[] = _("{B_DEF_NAME_WITH_PREFIX} evaded\nthe attack!");
static const u8 sText_PkmnSappedByLeechSeed[] = _("{B_DEF_NAME_WITH_PREFIX}'s health is\nsapped by LEECH SEED!");
static const u8 sText_PkmnFastAsleep[] = _("{B_ATK_NAME_WITH_PREFIX} is fast\nasleep.");
static const u8 sText_PkmnWokeUp[] = _("{B_ATK_NAME_WITH_PREFIX} woke up!");
static const u8 sText_PkmnUproarKeptAwake[] = _("But {B_SCR_ACTIVE_NAME_WITH_PREFIX}'s UPROAR\nkept it awake!");
static const u8 sText_PkmnWokeUpInUproar[] = _("{B_ATK_NAME_WITH_PREFIX} woke up\nin the UPROAR!");
static const u8 sText_PkmnWokeUpRefreshed[] = _("{B_ATK_NAME_WITH_PREFIX} woke up\nrefreshed!");
static const u8 sText_PkmnCausedUproar[] = _("{B_ATK_NAME_WITH_PREFIX} caused\nan UPROAR!");
static const u8 sText_PkmnMakingUproar[] = _("{B_ATK_NAME_WITH_PREFIX} is making\nan UPROAR!");
static const u8 sText_PkmnCalmedDown[] = _("{B_ATK_NAME_WITH_PREFIX} calmed down.");
static const u8 sText_PkmnCantSleepInUproar[] = _("But {B_DEF_NAME_WITH_PREFIX} can't\nsleep in an UPROAR!");
static const u8 sText_PkmnStockpiled[] = _("{B_ATK_NAME_WITH_PREFIX} STOCKPILED\n{B_BUFF1}!");
static const u8 sText_PkmnCantStockpile[] = _("{B_ATK_NAME_WITH_PREFIX} can't\nSTOCKPILE any more!");
static const u8 sText_PkmnCantSleepInUproar2[] = _("But {B_DEF_NAME_WITH_PREFIX} can't\nsleep in an UPROAR!");
static const u8 sText_UproarKeptPkmnAwake[] = _("But the UPROAR kept\n{B_DEF_NAME_WITH_PREFIX} awake!");
static const u8 sText_PkmnStayedAwakeUsing[] = _("{B_DEF_NAME_WITH_PREFIX} stayed awake\nusing its {B_DEF_ABILITY}!");
static const u8 sText_PkmnStoringEnergy[] = _("{B_ATK_NAME_WITH_PREFIX} is storing\nenergy!");
static const u8 sText_PkmnUnleashedEnergy[] = _("{B_ATK_NAME_WITH_PREFIX} unleashed\nenergy!");
static const u8 sText_PkmnFatigueConfusion[] = _("{B_ATK_NAME_WITH_PREFIX} became\nconfused due to fatigue!");
static const u8 sText_PkmnPickedUpItem[] = _("{B_PLAYER_NAME} picked up\n¥{B_BUFF1}!\p");
static const u8 sText_PkmnUnaffected[] = _("{B_DEF_NAME_WITH_PREFIX} is\nunaffected!");
static const u8 sText_PkmnTransformedInto[] = _("{B_ATK_NAME_WITH_PREFIX} transformed\ninto {B_BUFF1}!");
static const u8 sText_PkmnMadeSubstitute[] = _("{B_ATK_NAME_WITH_PREFIX} made\na SUBSTITUTE!");
static const u8 sText_PkmnHasSubstitute[] = _("{B_ATK_NAME_WITH_PREFIX} already\nhas a SUBSTITUTE!");
static const u8 sText_SubstituteDamaged[] = _("The SUBSTITUTE took damage\nfor {B_DEF_NAME_WITH_PREFIX}!\p");
static const u8 sText_PkmnSubstituteFaded[] = _("{B_DEF_NAME_WITH_PREFIX}'s\nSUBSTITUTE faded!\p");
static const u8 sText_PkmnMustRecharge[] = _("{B_ATK_NAME_WITH_PREFIX} must\nrecharge!");
static const u8 sText_PkmnRageBuilding[] = _("{B_DEF_NAME_WITH_PREFIX}'s RAGE\nis building!");
static const u8 sText_AttackerRageBuilding[] = _("{B_ATK_NAME_WITH_PREFIX}'s RAGE\nis building!");
static const u8 sText_AttackerRageEnded[] = _("{B_ATK_NAME_WITH_PREFIX}'s RAGE\nabated!{PAUSE 15}");
static const u8 sText_DefenderRageEnded[] = _("{B_DEF_NAME_WITH_PREFIX}'s RAGE\nabated!{PAUSE 15}");
static const u8 sText_PkmnMoveWasDisabled[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwas disabled!");
static const u8 sText_PkmnMoveDisabledNoMore[] = _("{B_ATK_NAME_WITH_PREFIX} is disabled\nno more!");
static const u8 sText_PkmnInthralledNoMore[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} is\nno longer sealed!");
static const u8 sText_PkmnIsInthralled[] = _("{B_DEF_NAME_WITH_PREFIX} has lost the memory\nof how to use {B_BUFF1}!");
static const u8 sText_PkmnGotEncore[] = _("{B_DEF_NAME_WITH_PREFIX} got\nan ENCORE!");
static const u8 sText_PkmnEncoreEnded[] = _("{B_ATK_NAME_WITH_PREFIX}'s ENCORE\nended!");
static const u8 sText_PkmnTookAim[] = _("{B_ATK_NAME_WITH_PREFIX} took aim\nat {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnSketchedMove[] = _("{B_ATK_NAME_WITH_PREFIX} SKETCHED\n{B_BUFF1}!");
static const u8 sText_PkmnTryingToTakeFoe[] = _("{B_ATK_NAME_WITH_PREFIX} is trying\nto take its foe with it!");
static const u8 sText_PkmnTookFoe[] = _("{B_DEF_NAME_WITH_PREFIX} took\n{B_ATK_NAME_WITH_PREFIX} with it!");
static const u8 sText_PkmnReducedPP[] = _("{B_DEF_NAME_WITH_PREFIX}{B_BUFF3}\n{B_BUFF1} was reduced by {B_BUFF2}!");
static const u8 sText_SpiteBadLuck[] = _(" had bad luck!");
static const u8 sText_SpiteTotalLoss[] = _("'s luck ran out!");
static const u8 sText_PkmnStoleItem[] = _("{B_ATK_NAME_WITH_PREFIX} stole\n{B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!");
static const u8 sText_TargetCantEscapeNow[] = _("{B_DEF_NAME_WITH_PREFIX} can't\nescape now!");
static const u8 sText_PkmnFellIntoNightmare[] = _("{B_DEF_NAME_WITH_PREFIX} fell into\na NIGHTMARE!");
static const u8 sText_PkmnLockedInNightmare[] = _("{B_ATK_NAME_WITH_PREFIX} is locked\nin a NIGHTMARE!");
static const u8 sText_PkmnLaidCurse[] = _("{B_ATK_NAME_WITH_PREFIX} cut its own HP and\nlaid a CURSE on {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnAfflictedByCurse[] = _("{B_ATK_NAME_WITH_PREFIX} is afflicted\nby the CURSE!");
static const u8 sText_SpikesScattered[] = _("SPIKES were scattered all around\nthe opponent's side!");
static const u8 sText_PkmnHurtBySpikes[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is hurt\nby SPIKES!");
static const u8 sText_PkmnIdentified[] = _("{B_ATK_NAME_WITH_PREFIX} identified\n{B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnPerishCountFell[] = _("{B_ATK_NAME_WITH_PREFIX}'s PERISH count\nfell to {B_BUFF1}!");
static const u8 sText_PkmnBracedItself[] = _("{B_ATK_NAME_WITH_PREFIX} braced\nitself!");
static const u8 sText_PkmnEnduredHit[] = _("{B_DEF_NAME_WITH_PREFIX} ENDURED\nthe hit!");
static const u8 sText_MagnitudeStrength[] = _("MAGNITUDE {B_BUFF1}!");
static const u8 sText_PkmnCutHPMaxedAttack[] = _("{B_ATK_NAME_WITH_PREFIX} cut its own HP\nand maximized ATTACK!");
static const u8 sText_PkmnCopiedStatChanges[] = _("{B_ATK_NAME_WITH_PREFIX} copied\n{B_DEF_NAME_WITH_PREFIX}'s stat changes!");
static const u8 sText_PkmnGotFree[] = _("{B_ATK_NAME_WITH_PREFIX} got free of\nall traps!");
static const u8 sText_PkmnShedLeechSeed[] = _("{B_ATK_NAME_WITH_PREFIX} shed\nLEECH SEED!");
static const u8 sText_PkmnBlewAwaySpikes[] = _("{B_ATK_NAME_WITH_PREFIX} blew away\nSPIKES!");
static const u8 sText_PkmnFledFromBattle[] = _("{B_ATK_NAME_WITH_PREFIX} fled from\nbattle!");
static const u8 sText_PkmnForesawAttack[] = _("{B_ATK_NAME_WITH_PREFIX} foresaw\nan attack!");
static const u8 sText_PkmnTookAttack[] = _("{B_DEF_NAME_WITH_PREFIX} took the\n{B_BUFF1} attack!");
static const u8 sText_PkmnChoseXAsDestiny[] = _("{B_ATK_NAME_WITH_PREFIX} chose\n{B_CURRENT_MOVE} as its destiny!");
static const u8 sText_PkmnAttack[] = _("{B_BUFF1}'s attack!");
static const u8 sText_PkmnCenterAttention[] = _("{B_ATK_NAME_WITH_PREFIX} became the\ncenter of attention!");
static const u8 sText_PkmnChargingPower[] = _("{B_ATK_NAME_WITH_PREFIX} began\ncharging power!");
static const u8 sText_NaturePowerTurnedInto[] = _("NATURE POWER turned into\n{B_CURRENT_MOVE}!");
static const u8 sText_PkmnStatusNormal[] = _("{B_ATK_NAME_WITH_PREFIX}'s status\nreturned to normal!");
static const u8 sText_PkmnSubjectedToTorment[] = _("{B_DEF_NAME_WITH_PREFIX} was subjected\nto TORMENT!");
static const u8 sText_PkmnTighteningFocus[] = _("{B_ATK_NAME_WITH_PREFIX} is tightening\nits focus!");
static const u8 sText_PkmnFellForTaunt[] = _("{B_DEF_NAME_WITH_PREFIX} fell for\nthe TAUNT!");
static const u8 sText_PkmnReadyToHelp[] = _("{B_ATK_NAME_WITH_PREFIX} is ready to\nhelp {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnSwitchedItems[] = _("{B_ATK_NAME_WITH_PREFIX} switched\nitems with its opponent!");
static const u8 sText_PkmnObtainedX[] = _("{B_ATK_NAME_WITH_PREFIX} obtained\n{B_BUFF1}.");
static const u8 sText_PkmnObtainedX2[] = _("{B_DEF_NAME_WITH_PREFIX} obtained\n{B_BUFF2}.");
static const u8 sText_PkmnObtainedXYObtainedZ[] = _("{B_ATK_NAME_WITH_PREFIX} obtained\n{B_BUFF1}.\p{B_DEF_NAME_WITH_PREFIX} obtained\n{B_BUFF2}.");
static const u8 sText_PkmnCopiedFoe[] = _("{B_ATK_NAME_WITH_PREFIX} copied\n{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!");
static const u8 sText_PkmnMadeWish[] = _("{B_ATK_NAME_WITH_PREFIX} made a WISH!");
static const u8 sText_PkmnWishCameTrue[] = _("{B_BUFF1}'s WISH\ncame true!");
static const u8 sText_PkmnPlantedRoots[] = _("{B_ATK_NAME_WITH_PREFIX} planted its roots!");
static const u8 sText_PkmnAbsorbedNutrients[] = _("{B_ATK_NAME_WITH_PREFIX} absorbed\nnutrients with its roots!");
static const u8 sText_PkmnAnchoredItself[] = _("{B_DEF_NAME_WITH_PREFIX} anchored\nitself with its roots!");
static const u8 sText_PkmnWasMadeDrowsy[] = _("{B_ATK_NAME_WITH_PREFIX} made\n{B_DEF_NAME_WITH_PREFIX} drowsy!");
static const u8 sText_PkmnKnockedOff[] = _("{B_ATK_NAME_WITH_PREFIX} knocked off\n{B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!");
static const u8 sText_PkmnSwappedAbilities[] = _("{B_ATK_NAME_WITH_PREFIX} swapped abilities\nwith its opponent!");
static const u8 sText_PkmnSealedOpponentMove[] = _("{B_ATK_NAME_WITH_PREFIX} sealed the\nopponent's moveシsス!");
static const u8 sText_PkmnWantsGrudge[] = _("{B_ATK_NAME_WITH_PREFIX} wants the\nopponent to bear a GRUDGE!");
static const u8 sText_PkmnLostPPGrudge[] = _("{B_ATK_NAME_WITH_PREFIX} lost\nPP due to the GRUDGE!");
static const u8 sText_PkmnShroudedItself[] = _("{B_ATK_NAME_WITH_PREFIX} shrouded\nitself in {B_CURRENT_MOVE}!");
static const u8 sText_PkmnMoveBounced[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE}\nwas bounced back by MAGIC COAT!");
static const u8 sText_PkmnWaitsForTarget[] = _("{B_ATK_NAME_WITH_PREFIX} waits for its foe\nto make a move!");
static const u8 sText_PkmnSnatchedMove[] = _("{B_DEF_NAME_WITH_PREFIX} SNATCHED\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s move!");
static const u8 sText_ElectricityWeakened[] = _("Electricity's power was\nweakened!");
static const u8 sText_FireWeakened[] = _("Fire's power was\nweakened!");
static const u8 sText_XFoundOneY[] = _("{B_ATK_NAME_WITH_PREFIX} found\none {B_LAST_ITEM}!");
static const u8 sText_SoothingAroma[] = _("A soothing aroma wafted\nthrough the area!");
static const u8 sText_ItemsCantBeUsedNow[] = _("Items can't be used now.{PAUSE 34}");
static const u8 sText_ForXCommaYZ[] = _("For {B_SCR_ACTIVE_NAME_WITH_PREFIX},\n{B_LAST_ITEM} {B_BUFF1}");
static const u8 sText_PkmnUsedXToGetPumped[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} used\n{B_LAST_ITEM} to hustle!");
static const u8 sText_PkmnLostFocus[] = _("{B_ATK_NAME_WITH_PREFIX} lost its\nfocus and couldn't move!");
static const u8 sText_PkmnWasDraggedOut[] = _("{B_DEF_NAME_WITH_PREFIX} was\ndragged out!\p");
static const u8 sText_TheWallShattered[] = _("The wall shattered!");
static const u8 sText_ButNoEffect[] = _("But it had no effect!");
static const u8 sText_PkmnHasNoMovesLeft[] = _("{B_ATK_NAME_WITH_PREFIX} has no\nmoves left!\p");
static const u8 sText_PkmnMoveIsDisabled[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE}\nis disabled!\p");
static const u8 sText_PkmnCantUseMoveTorment[] = _("{B_ATK_NAME_WITH_PREFIX} can't use the same\nmove in a row due to the TORMENT!\p");
static const u8 sText_PkmnCantUseMoveTaunt[] = _("{B_ATK_NAME_WITH_PREFIX} can't use\n{B_CURRENT_MOVE} after the TAUNT!\p");
static const u8 sText_PkmnCantUseMoveSealed[] = _("{B_ATK_NAME_WITH_PREFIX} can't use the\nsealed {B_CURRENT_MOVE}!\p");
static const u8 sText_PkmnCantUseMoveThroatChop[] = _("{B_ATK_NAME_WITH_PREFIX} can't use\n{B_CURRENT_MOVE} due to Throat Chop!\p");
static const u8 sText_PkmnMadeItRain[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade it rain!");
static const u8 sText_PkmnRaisedSpeed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nraised its SPEED!");
static const u8 sText_PkmnProtectedBy[] = _("{B_DEF_NAME_WITH_PREFIX} was protected\nby {B_DEF_ABILITY}!");
static const u8 sText_PkmnPreventsUsage[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents {B_ATK_NAME_WITH_PREFIX}\lfrom using {B_CURRENT_MOVE}!");
static const u8 sText_PhoenixCleanse[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nhealed itself and\lcleansed hazards from the field!{PAUSE 97}");
static const u8 sText_PkmnRestoredHPUsing[] = _("{B_DEF_NAME_WITH_PREFIX} restored HP\nusing its {B_DEF_ABILITY}!");
static const u8 sText_PkmnsXMadeYUseless[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nmade {B_CURRENT_MOVE} useless!");
static const u8 sText_PkmnChangedTypeWith[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nmade it the {B_BUFF1} type!");
static const u8 sText_PkmnPreventsParalysisWith[] = _("{B_EFF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents paralysis!");
static const u8 sText_PkmnResistedtheMoodWith[] = _("{B_DEF_NAME_WITH_PREFIX}'s remained\n{B_DEF_ABILITY}!");
static const u8 sText_FemmeFataleBlocks[] =_ ("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nresisted the infatuation.");
static const u8 sText_PkmnPreventsPoisoningWith[] = _("{B_EFF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents poisoning!");
static const u8 sText_PkmnPreventsConfusionWith[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents confusion!");
static const u8 sText_PkmnRaisedFirePowerWith[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nraised its FIRE power!");
static const u8 sText_PkmnAnchorsItselfWith[] = _("{B_DEF_NAME_WITH_PREFIX} anchors\nitself with {B_DEF_ABILITY}!");
static const u8 sText_PkmnCutsAttackWith[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncuts {B_DEF_NAME_WITH_PREFIX}'s ATTACK!");
static const u8 sText_TigerMomActivation[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} pressured\n{B_DEF_NAME_WITH_PREFIX} cutting its DEFENSE!"); //maybe just do cuts defense?
static const u8 sText_DarkTypeIntimidateResist[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nhas no affect on Dark Types!");
static const u8 sText_PkmnPreventsStatLossWith[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nprevents stat loss!");
static const u8 sText_PkmnHurtsWith[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nhurt {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnHurtsWith2[] = _("{B_ATK_NAME_WITH_PREFIX} was hurt by\n{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}!");
static const u8 sText_AttackerHurtsPkmnWith[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\nhurt {B_DEF_NAME_WITH_PREFIX}!"); //only used for aftermath
static const u8 sText_PkmnTraced[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} TRACED\n{B_BUFF1}'s {B_BUFF2}!");
static const u8 sText_PkmnsXPreventsBurns[] = _("{B_EFF_NAME_WITH_PREFIX}'s {B_EFF_ABILITY}\nprevents burns!");
static const u8 sText_PkmnsXBlocksY[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nblocks {B_CURRENT_MOVE}!");
static const u8 sText_PkmnsXBlocksY2[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nblocks {B_CURRENT_MOVE}!");
static const u8 sText_PkmnsXRestoredHPALittle2[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nrestored its HP a little!");
static const u8 sText_PkmnsXWhippedUpSandstorm[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nwhipped up a sandstorm!");
static const u8 sText_TargetsXWhippedUpSandstorm[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nwhipped up a sandstorm!");
static const u8 sText_PkmnsXIntensifiedSun[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nintensified the sun's rays!");
static const u8 sText_PkmnsXIntensifiedMoon[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nintensified the moon's rays!");
static const u8 sText_PkmnsXPreventsYLoss[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nprevents {B_BUFF1} loss!");
static const u8 sText_PkmnsXInfatuatedY[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\ninfatuated {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_AttakersXInfatuatedY[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\ninfatuated {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnsXMadeYIneffective[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nmade {B_CURRENT_MOVE} ineffective!");
static const u8 sText_PkmnsXCuredYProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncured its {B_BUFF1} problem!");
static const u8 sText_ItSuckedLiquidOoze[] = _("It sucked up the\nLIQUID OOZE!");
static const u8 sText_PkmnTransformed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} transformed!");
static const u8 sText_PkmnsXTookAttack[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\ntook the attack!");
const u8 gText_PkmnsXPreventsSwitching[] = _("{B_BUFF1}'s {B_LAST_ABILITY}\nprevents switching!\p");
static const u8 sText_PreventedFromWorking[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevented {B_SCR_ACTIVE_NAME_WITH_PREFIX}'s\l{B_BUFF1} from working!");
static const u8 sText_PkmnsXMadeItIneffective[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nmade it ineffective!");
static const u8 sText_PkmnsXPreventsFlinching[] = _("{B_EFF_NAME_WITH_PREFIX}'s {B_EFF_ABILITY}\nprevents flinching!");
static const u8 sText_PkmnsXPreventsYsZ[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nprevents {B_DEF_NAME_WITH_PREFIX}'s\l{B_DEF_ABILITY} from working!");
static const u8 sText_PkmnsAbilityPreventsAbility[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nprevents {B_DEF_NAME_WITH_PREFIX}'s\l{B_DEF_ABILITY} from working!");
//taken from damp explosion logic specifically for aftermath damp
static const u8 sText_PkmnPreventsAbilityUsage[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nprevents {B_SCR_ACTIVE_NAME_WITH_PREFIX}\lfrom using {B_LAST_ABILITY}!");//{B_LAST_ABILITY}
static const u8 sText_PkmnsXCuredItsYProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncured its {B_BUFF1} problem!");
static const u8 sText_PkmnsXHadNoEffectOnY[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nhad no effect on {B_EFF_NAME_WITH_PREFIX}!");
static const u8 sText_TooScaredToMove[] = _("{B_ATK_NAME_WITH_PREFIX} is too scared to move!");
static const u8 sText_GetOutGetOut[] = _("GHOST: Get out…… Get out……");
static const u8 sText_StatSharply[] = _("sharply ");
const u8 gBattleText_Rose[] = _("rose!");
static const u8 sText_StatHarshly[] = _("harshly ");
static const u8 sText_StatFell[] = _("fell!");
static const u8 sText_drastically[] = _("drastically ");
static const u8 sText_severely[] = _("severely ");
static const u8 sText_PkmnsStatChanged[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}");
const u8 gText_PkmnsStatChanged2[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}");
static const u8 sText_UsingXTheYOfZN[] = _("Using {B_LAST_ITEM}, the {B_BUFF1}\nof {B_SCR_ACTIVE_NAME_WITH_PREFIX} {B_BUFF2}");
static const u8 sText_PkmnsStatChanged3[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}");
static const u8 sText_PkmnsStatChanged4[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\n{B_BUFF2}");
static const u8 sText_StatsWontIncrease2[] = _("{B_ATK_NAME_WITH_PREFIX}'s stats won't\ngo any higher!");
static const u8 sText_StatsWontDecrease2[] = _("{B_DEF_NAME_WITH_PREFIX}'s stats won't\ngo any lower!");
static const u8 sText_AnticipateExplosion[] = _("an explosive move");
static const u8 sText_AnticipateOHKO[] = _("a one-hit KO move");
static const u8 sText_AnticipateDefault[] = _("a dangerous move");
static const u8 sText_AnticipateStrongestMove[] = _("a strong move"); //bp 90 or better
static const u8 sText_AnticipatedMove[] = _("something"); //for strongest move, but not strong move
static const u8 sText_PlayerForewarn[] = _("to the");
static const u8 sText_EnemyForewarn[] = _("to");
static const u8 sText_PlayerForewarnalert[] = _("alerted");
static const u8 sText_EnemyForewarnalert[] = _("alerted the");
static const u8 sText_CriticalHit[] = _("A critical hit!");
static const u8 sText_OneHitKO[] = _("It's a one-hit KO!");
static const u8 sText_123Poof[] = _("{PAUSE 32}1, {PAUSE 15}2, and{PAUSE 15}… {PAUSE 15}… {PAUSE 15}… {PAUSE 15}{PLAY_SE SE_BALL_BOUNCE_1}Poof!\p");
static const u8 sText_AndEllipsis[] = _("And…\p");
static const u8 sText_HMMovesCantBeForgotten[] = _("HM moves can't be\nforgotten now.\p");
static const u8 sText_NotVeryEffective[] = _("It's not very effective…");
static const u8 sText_SuperEffective[] = _("It's super effective!");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}Got away safely!\p");
static const u8 sText_PkmnFledUsingIts[] = _("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} fled\nusing its {B_LAST_ITEM}!\p");
static const u8 sText_PkmnFledUsing[] = _("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} fled\nusing {B_ATK_ABILITY}!\p");
static const u8 sText_WildPkmnFled[] = _("{PLAY_SE SE_FLEE}Wild {B_BUFF1} fled!");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("Player defeated\n{B_LINK_OPPONENT1_NAME}!");
static const u8 sText_TwoLinkTrainersDefeated[] = _("Player beat {B_LINK_OPPONENT1_NAME}\nand {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("Player lost against\n{B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerLostToTwo[] = _("Player lost to {B_LINK_OPPONENT1_NAME}\nand {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("Player battled to a draw against\n{B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("Player battled to a draw against\n{B_LINK_OPPONENT1_NAME} and {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME} fled!");
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME} and\n{B_LINK_OPPONENT2_NAME} fled!");
static const u8 sText_NoRunningFromTrainers[] = _("No! There's no running\nfrom a TRAINER battle!\p");
static const u8 sText_CantEscape[] = _("Can't escape!\p");
static const u8 sText_EmptyString5[] = _("");   //sText_DontLeaveBirch in pokeem
static const u8 sText_ButNothingHappened[] = _("…\nBut nothing happened!");
static const u8 sText_ButItFailed[] = _("But it failed!");
static const u8 sText_ItHurtConfusion[] = _("It hurt itself in its\nconfusion!");
static const u8 sText_MirrorMoveFailed[] = _("The MIRROR MOVE failed!");
static const u8 sText_StartedToRain[] = _("It started to rain!");
static const u8 sText_DownpourStarted[] = _("A downpour started!"); // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
static const u8 sText_RainContinues[] = _("Rain continues to fall.");
static const u8 sText_DownpourContinues[] = _("The downpour continues."); // unused //NOW USED for acid rain
static const u8 sText_RainStopped[] = _("The rain stopped.");
static const u8 sText_SandstormBrewed[] = _("A sandstorm brewed!");
static const u8 sText_SandstormRages[] = _("The sandstorm rages.");
static const u8 sText_SandstormSubsided[] = _("The sandstorm subsided.");
static const u8 sText_SunlightGotBright[] = _("The sunlight got bright!");
static const u8 sText_SunlightStrong[] = _("The sunlight is strong.");
static const u8 sText_SunlightFaded[] = _("The sunlight faded.");
static const u8 sText_StartedHail[] = _("It started to hail!");
static const u8 sText_HailContinues[] = _("Hail continues to fall.");
static const u8 sText_HailStopped[] = _("The hail stopped.");
static const u8 sText_FailedToSpitUp[] = _("But it failed to SPIT UP\na thing!");
static const u8 sText_FailedToSwallow[] = _("But it failed to SWALLOW\na thing!");
static const u8 sText_WindBecameHeatWave[] = _("The wind turned into a\nHEAT WAVE!");
static const u8 sText_StatChangesGone[] = _("All stat changes were\neliminated!");
static const u8 sText_CoinsScattered[] = _("Coins scattered everywhere!");
static const u8 sText_TooWeakForSubstitute[] = _("It was too weak to make\na SUBSTITUTE!");
static const u8 sText_SharedPain[] = _("The battlers shared\ntheir pain!");
static const u8 sText_BellChimed[] = _("A bell chimed!");
static const u8 sText_FaintInThree[] = _("All affected POKéMON will\nfaint in three turns!");
static const u8 sText_NoPPLeft[] = _("There's no PP left for\nthis move!\p");
static const u8 sText_ButNoPPLeft[] = _("But there was no PP left\nfor the move!");
static const u8 sText_PkmnPanicked[] = _("{B_ATK_NAME_WITH_PREFIX} panicked\nand used a random move!");
static const u8 sText_PkmnIgnoresAsleep[] = _("{B_ATK_NAME_WITH_PREFIX} ignored\norders while asleep!");
static const u8 sText_PkmnIgnoredOrders[] = _("{B_ATK_NAME_WITH_PREFIX} ignored\norders!");
static const u8 sText_PkmnBeganToNap[] = _("{B_ATK_NAME_WITH_PREFIX} began to nap!");
static const u8 sText_PkmnLoafing[] = _("{B_ATK_NAME_WITH_PREFIX} is\nloafing around!");
static const u8 sText_PkmnWontObey[] = _("{B_ATK_NAME_WITH_PREFIX} won't\nobey!");
static const u8 sText_PkmnTurnedAway[] = _("{B_ATK_NAME_WITH_PREFIX} turned away!");
static const u8 sText_PkmnPretendNotNotice[] = _("{B_ATK_NAME_WITH_PREFIX} pretended\nnot to notice!"); // FINALLLY, found this dang string.
static const u8 sText_EnemyAboutToSwitchPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME} is\nabout to send out\ltheir next POKéMON.\pWill {B_PLAYER_NAME} change\nPOKéMON?");
static const u8 sText_PkmnLearnedMove2[] = _("{B_ATK_NAME_WITH_PREFIX} learned\n{B_BUFF1}!"); // ok now the player can't tell what pokemon is coming next.
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("Player defeated\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!\p");
static const u8 sText_ThrewARock[] = _("{B_PLAYER_NAME} threw a ROCK\nat the {B_OPPONENT_MON1_NAME}!");
static const u8 sText_ThrewSomeBait[] = _("{B_PLAYER_NAME} threw some BAIT\nat the {B_OPPONENT_MON1_NAME}!");
static const u8 sText_PkmnWatchingCarefully[] = _("{B_OPPONENT_MON1_NAME} is watching\ncarefully!"); // use, may change and use for player if I can get that skip turn idea working.
//static const u8 sText_PlayerWatchingCarefully[] = _("{B_PLAYER_NAME} is watching\ncarefully!"); //ok script is defined need to figure out how to call.
static const u8 sText_PkmnIsAngry[] = _("{B_OPPONENT_MON1_NAME} is angry!"); // think I just need make new function with that script in it.
static const u8 sText_PkmnIsEating[] = _("{B_OPPONENT_MON1_NAME} is eating!"); //like playerwaiting or doskipturn. I may change that to , B_PLAYER_MON1_NAME is awaiting instruction
static const u8 sText_OutOfSafariBalls[] = _("{PLAY_SE SE_DING_DONG}ANNOUNCER: You're out of\nSAFARI BALLS! Game over!\p");
static const u8 sText_WildPkmnAppeared[] = _("Wild {B_OPPONENT_MON1_NAME} appeared!\p"); // that way instead of constantly hearing player name, its your pokemon's name
static const u8 sText_WildPkmnAppeared2[] = _("Wild {B_OPPONENT_MON1_NAME} appeared!\p");
static const u8 sText_WildPkmnAppearedPause[] = _("Wild {B_OPPONENT_MON1_NAME} appeared!{PAUSE 127}"); //only used in teach tv tutorial
static const u8 sText_TwoWildPkmnAppeared[] = _("Wild {B_OPPONENT_MON1_NAME} and\n{B_OPPONENT_MON2_NAME} appeared!\p");
static const u8 sText_GhostAppearedCantId[] = _("The GHOST appeared!\pDarn!\nThe GHOST can't be ID'd!\p");
static const u8 sText_TheGhostAppeared[] = _("The GHOST appeared!\p");
static const u8 sText_SilphScopeUnveil[] = _("SILPH SCOPE unveiled the GHOST's\nidentity!");
static const u8 sText_TheGhostWas[] = _("The GHOST was MAROWAK!\p\n");
static const u8 sText_Trainer1WantsToBattle[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nwould like to battle!\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("{B_LINK_OPPONENT1_NAME}\nwants to battle!");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("{B_LINK_OPPONENT1_NAME} and {B_LINK_OPPONENT2_NAME}\nwant to battle!");
static const u8 sText_Trainer1SentOutPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME} sent\nout {B_OPPONENT_MON1_NAME}!{PAUSE 60}");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME} sent\nout {B_OPPONENT_MON1_NAME} and {B_OPPONENT_MON2_NAME}!{PAUSE 60}");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME} sent\nout {B_BUFF1}!");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} sent out\n{B_OPPONENT_MON1_NAME}!");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("{B_LINK_OPPONENT1_NAME} sent out\n{B_OPPONENT_MON1_NAME} and {B_OPPONENT_MON2_NAME}!");
static const u8 sText_TwoLinkTrainersSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} sent out {B_LINK_OPPONENT_MON1_NAME}!\n{B_LINK_OPPONENT2_NAME} sent out {B_LINK_OPPONENT_MON2_NAME}!");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{B_LINK_OPPONENT1_NAME} sent out\n{B_BUFF1}!");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("{B_LINK_SCR_TRAINER_NAME} sent out\n{B_BUFF1}!");
static const u8 sText_GoPkmn[] = _("Go! {B_PLAYER_MON1_NAME}!");
static const u8 sText_GoTwoPkmn[] = _("Go! {B_PLAYER_MON1_NAME} and\n{B_PLAYER_MON2_NAME}!");
static const u8 sText_GoPkmn2[] = _("Go! {B_BUFF1}!");
static const u8 sText_DoItPkmn[] = _("Do it! {B_BUFF1}!");
static const u8 sText_GoForItPkmn[] = _("Go for it, {B_BUFF1}!");
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("Your foe's weak!\nGet 'em, {B_BUFF1}!");
static const u8 sText_LinkPartnerSentOutPkmnGoPkmn[] = _("{B_LINK_PARTNER_NAME} sent out {B_LINK_PLAYER_MON2_NAME}!\nGo! {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_PkmnThatsEnough[] = _("{B_BUFF1}, that's enough!\nCome back!");
static const u8 sText_PkmnComeBack[] = _("{B_BUFF1}, come back!");
static const u8 sText_PkmnOkComeBack[] = _("{B_BUFF1}, OK!\nCome back!");
const u8 sText_PkmnGoodComeBack[] = _("{B_BUFF1}, good!\nCome back!");
static const u8 sText_Trainer1WithdrewPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nwithdrew {B_BUFF1}!");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("{B_LINK_OPPONENT1_NAME} withdrew\n{B_BUFF1}!");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{B_LINK_SCR_TRAINER_NAME} withdrew\n{B_BUFF1}!");
static const u8 sText_WildPkmnPrefix[] = _("Wild ");
static const u8 sText_FoePkmnPrefix[] = _("Foe ");
static const u8 sText_FoePkmnPrefix2[] = _("Foe");
static const u8 sText_AllyPkmnPrefix[] = _("Ally");
static const u8 sText_FoePkmnPrefix3[] = _("Foe");
static const u8 sText_AllyPkmnPrefix2[] = _("Ally");
static const u8 sText_FoePkmnPrefix4[] = _("Foe");
static const u8 sText_AllyPkmnPrefix3[] = _("Ally");        //can leave without pause just need to cut down waitmessage reduction for speedup at above 2xs
static const u8 sText_AttackerUsedX[] = _("{B_ATK_NAME_WITH_PREFIX} used\n{B_BUFF2}{PAUSE 4}"); //think cut this down   {PAUSE 4}    still would need pause
static const u8 sText_ExclamationMark[] = _("!");
static const u8 sText_ExclamationMark2[] = _("!");
static const u8 sText_ExclamationMark3[] = _("!");
static const u8 sText_ExclamationMark4[] = _("!");
static const u8 sText_ExclamationMark5[] = _("!");
static const u8 sText_EndCap[] = _("{END_CAP}");

static const u8 sText_HP2[] = _("HP");
static const u8 sText_Attack2[] = _("ATTACK");
static const u8 sText_Defense2[] = _("DEFENSE");
static const u8 sText_Speed[] = _("SPEED");
static const u8 sText_SpAtk2[] = _("SP. ATK");
static const u8 sText_SpDef2[] = _("SP. DEF");
static const u8 sText_Accuracy[] = _("accuracy");
static const u8 sText_Evasiveness[] = _("evasiveness");

const u8 *const gStatNamesTable[] = {
    sText_HP2,
    sText_Attack2,
    sText_Defense2,
    sText_Speed,
    sText_SpAtk2,
    sText_SpDef2,
    sText_Accuracy,
    sText_Evasiveness
};

static const u8 sText_PokeblockWasTooSpicy[] = _("was too spicy!"); //
static const u8 sText_PokeblockWasTooDry[] = _("was too dry!");
static const u8 sText_PokeblockWasTooSweet[] = _("was too sweet!");
static const u8 sText_PokeblockWasTooBitter[] = _("was too bitter!");
static const u8 sText_PokeblockWasTooSour[] = _("was too sour!");

const u8 *const gPokeblockWasTooXStringTable[] = {
    sText_PokeblockWasTooSpicy,
    sText_PokeblockWasTooDry,
    sText_PokeblockWasTooSweet,
    sText_PokeblockWasTooBitter,
    sText_PokeblockWasTooSour
};

static const u8 sText_PlayerUsedItem[] = _("{B_PLAYER_NAME} used\n{B_LAST_ITEM}!");
static const u8 sText_OldManUsedItem[] = _("The old man used\n{B_LAST_ITEM}!");
static const u8 sText_PokedudeUsedItem[] = _("The POKé DUDE used\n{B_LAST_ITEM}!");
static const u8 sText_Trainer1UsedItem[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nused {B_LAST_ITEM}!");
static const u8 sText_TrainerBlockedBall[] = _("The TRAINER blocked the BALL!");
static const u8 sText_DontBeAThief[] = _("Don't be a thief!");
static const u8 sText_PkmnBrokeFree[] = _("Oh, no!\nThe POKéMON broke free!");
static const u8 sText_ItAppearedCaught[] = _("Aww!\nIt appeared to be caught!");
static const u8 sText_AarghAlmostHadIt[] = _("Aargh!\nAlmost had it!");
static const u8 sText_ShootSoClose[] = _("Shoot!\nIt was so close, too!");
const u8 gUnknown_83FD78A[] = _("よけられた!\nこいつは つかまりそうにないぞ!");
static const u8 sText_ItemaddedtoBag[] = _("Item(s) added to the bag.{PAUSE 47}");
static const u8 sText_ReceiveditemfromCaughtMon[] = _("{B_DEF_NAME} dropped a {B_BUFF3}!\p"); //for taking item caught from mon
static const u8 sText_GotchaPkmnCaught[] = _("Gotcha!\n{B_DEF_NAME} was caught!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p");
static const u8 sText_GotchaPkmnCaught2[] = _("Gotcha!\n{B_DEF_NAME} was caught!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}"); //in Em used by wally
static const u8 sText_GiveNicknameCaptured[] = _("Give a nickname to the\ncaptured {B_OPPONENT_MON1_NAME}?");
static const u8 sText_PkmnSentToPC[] = _("{B_DEF_NAME} was sent to\n{B_PC_CREATOR_NAME} PC.");
static const u8 sText_Someones[] = _("someone's");
static const u8 sText_Bills[] = _("BILL's");
static const u8 sText_PkmnDataAddedToDex[] = _("{B_DEF_NAME}'s data was\nadded to the POKéDEX.\p");
static const u8 sText_ItIsRaining[] = _("It is raining."); // used only in RSE when a battle starts in a rainy area
static const u8 sText_SandstormIsRaging[] = _("A sandstorm is raging.");
static const u8 sText_BoxIsFull[] = _("The BOX is full!\nYou can't catch any more!\p");
static const u8 sText_EnigmaBerry[] = _("ENIGMA BERRY");
static const u8 sText_BerrySuffix[] = _(" BERRY");
static const u8 gUnknown_83FD8B6[] = _("ナゾ");
static const u8 sText_PkmnsItemCuredParalysis[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ncured paralysis!");
static const u8 sText_PkmnsItemCuredPoison[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ncured poison!");
static const u8 sText_PkmnsItemHealedBurn[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nhealed its burn!");
static const u8 sText_PkmnsItemDefrostedIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ndefrosted it!");
static const u8 sText_PkmnsItemWokeIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nwoke it from its sleep!");
static const u8 sText_PkmnsItemSnappedOut[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nsnapped it out of confusion!");
static const u8 sText_PkmnsItemCuredProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\ncured its {B_BUFF1} problem!");
static const u8 sText_PkmnsItemNormalizedStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nnormalized its status!");
static const u8 sText_PkmnsItemRestoredHealth[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored health!");
static const u8 sText_PkmnsItemRestoredPP[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored {B_BUFF1}'s PP!");
static const u8 sText_PkmnsItemRestoredStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored its status!");
static const u8 sText_PkmnsItemRestoredHPALittle[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nrestored its HP a little!");
static const u8 sText_ItemAllowsOnlyYMove[] = _("{B_LAST_ITEM}'s effect allows only\n{B_CURRENT_MOVE} to be used!\p");
static const u8 sText_PkmnHungOnWithX[] = _("{B_DEF_NAME_WITH_PREFIX} hung on\nusing its {B_LAST_ITEM}!");
const u8 gText_EmptyString3[] = _("");
static const u8 sText_PlayedFluteCatchyTune[] = _("{B_PLAYER_NAME} played the {B_LAST_ITEM}.\pNow, that's a catchy tune!");
static const u8 sText_PlayedThe[] = _("{B_PLAYER_NAME} played the\n{B_LAST_ITEM}.");
static const u8 sText_PkmnHearingFluteAwoke[] = _("The POKéMON hearing the FLUTE\nawoke!");
static const u8 sText_PkmnsXCalledDownHail[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\ncalled down hail!");
static const u8 sText_PokemonBlockedBall[] = _("The Wild {B_DEF_NAME}\nblocked the BALL!{PAUSE 10}");
static const u8 sText_ItDodgedBall[] = _("It dodged the thrown BALL!\nThis POKéMON can't be caught!{PAUSE 10}");
static const u8 sText_YouMissedPkmn[] = _("You missed!\nThe POKéMON dodged the thrown BALL!{PAUSE 10}");
//
static const u8 sText_NeutralizingGasEnters[] = _("Neutralizing Gas filled the area!");
static const u8 sText_NeutralizingGasOver[] = _("The effects of Neutralizing Gas\n wore off!");

static const u8 sText_StenchEnters[] = _("A foul stench is in the air!");
static const u8 sText_StenchExits[] = _("The foul odor has cleared!");  //setup in place with neutralizing gas

//issued caused by undefined buffers  "B_ATK_TRAINER_NAME B_ATK_TEAM1 B_ATK_TEAM2 B_DEF_TEAM2 B_ATK_TRAINER_CLASS   //FIXED

// New battle strings.
static const u8 sText_Infestation[] = _("{B_DEF_NAME_WITH_PREFIX} has been afflicted\nwith an infestation!");
static const u8 sText_Infested[] = _("{B_ATK_NAME_WITH_PREFIX} is infested!");
static const s8 sText_EnduredViaSturdy[] = _("{B_DEF_NAME_WITH_PREFIX} ENDURED\nthe hit via {B_DEF_ABILITY}!");
static const s8 sText_AttackerEnduredViaSturdy[] = _("{B_ATK_NAME_WITH_PREFIX} hung on\nvia {B_ATK_ABILITY}!");
static const s8 sText_PowerHerbActivation[] = _("{B_ATK_NAME_WITH_PREFIX} became fully charged\ndue to its {B_LAST_ITEM}!");
static const s8 sText_HurtByItem[] = _("{B_ATK_NAME_WITH_PREFIX} was hurt\nby its {B_LAST_ITEM}!");
static const s8 sText_BadlyPoisonedByItem[] = _("{B_EFF_NAME_WITH_PREFIX} was badly \npoisoned by the {B_LAST_ITEM}!");
static const s8 sText_BurnedByItem[] = _("{B_EFF_NAME_WITH_PREFIX} was burned\nby the {B_LAST_ITEM}!");
static const s8 sText_TargetAbilityActivates[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} activates!");
static const u8 sText_GravityIntensified[] = _("GRAVITY intensified!");
static const u8 sText_TargetIdentified[] = _("{B_DEF_NAME_WITH_PREFIX} was \nidentified!");
static const u8 sText_TargetWokeUp[] = _("{B_DEF_NAME_WITH_PREFIX} woke up!");
static const u8 sText_PkmnStoleAndAteItem[] = _("{B_ATK_NAME_WITH_PREFIX} stole and\nate {B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!");
static const u8 sText_TailWindBlew[] = _("The tailwind blew from\nbehind {B_ATK_TEAM2} team!");
static const u8 sText_PkmnWentBack[] = _("{B_ATK_NAME_WITH_PREFIX} went back\nto {B_ATK_TRAINER_CLASS}{B_ATK_TRAINER_NAME}"); //B_ATK_TRAINER_CLASS isn't used clear for now, was {B_ATK_TRAINER_CLASS} {B_ATK_TRAINER_NAME}
static const u8 sText_PkmnCantUseItemsAnymore[] = _("{B_DEF_NAME_WITH_PREFIX} can't use\nitems anymore!");
static const u8 sText_PkmnFlung[] = _("{B_ATK_NAME_WITH_PREFIX} flung its\n{B_LAST_ITEM}!");
static const u8 sText_PkmnPreventedFromHealing[] = _("{B_DEF_NAME_WITH_PREFIX} was prevented\nfrom healing!");
static const u8 sText_PkmnSwitchedAtkAndDef[] = _("{B_ATK_NAME_WITH_PREFIX} switched its\nAttack and Defense!");
static const u8 sText_PkmnsAbilitySuppressed[] = _("{B_DEF_NAME_WITH_PREFIX}'s ability\nwas suppressed!");
static const u8 sText_ShieldedFromCriticalHits[] = _("The {B_CURRENT_MOVE} shielded {B_ATK_TEAM2}\nteam from critical hits!");
static const u8 sText_SwitchedAtkAndSpAtk[] = _("{B_ATK_NAME_WITH_PREFIX} switched all its\nchanges to its Attack and\pSp. Atk with the target!");
static const u8 sText_SwitchedDefAndSpDef[] = _("{B_ATK_NAME_WITH_PREFIX} switched all its\nchanges to its Defense and\pSp. Def with the target!");
static const u8 sText_PkmnAcquiredAbility[] = _("{B_DEF_NAME_WITH_PREFIX} acquired\n{B_DEF_ABILITY}!");
static const u8 sText_PoisonSpikesScattered[] = _("Poison Spikes were scattered all\naround the opposing team's feet!");
static const u8 sText_PkmnSwitchedStatChanges[] = _("{B_ATK_NAME_WITH_PREFIX} switched stat changes\nwith the target!");
static const u8 sText_PkmnSurroundedWithVeilOfWater[] = _("{B_ATK_NAME_WITH_PREFIX} surrounded itself\nwith a veil of water!");
static const u8 sText_PkmnLevitatedOnElectromagnetism[] = _("{B_ATK_NAME_WITH_PREFIX} levitated on\nelectromagnetism!");
static const u8 sText_PkmnTwistedDimensions[] = _("{B_ATK_NAME_WITH_PREFIX} twisted\nthe dimensions!");
static const u8 sText_PointedStonesFloat[] = _("Pointed stones float in the air\naround {B_DEF_TEAM2} team!");
static const u8 sText_CloakedInMysticalMoonlight[] = _("It became cloaked in mystical\nmoonlight!");
static const u8 sText_TrappedBySwirlingMagma[] = _("{B_DEF_NAME_WITH_PREFIX} became\ntrapped by swirling magma!");
static const u8 sText_VanishedInstantly[] = _("{B_ATK_NAME_WITH_PREFIX} vanished\ninstantly!");
static const u8 sText_ProtectedTeam[] = _("{B_CURRENT_MOVE} protected\n{B_ATK_TEAM2} team!");
static const u8 sText_SharedItsGuard[] = _("{B_ATK_NAME_WITH_PREFIX} shared its\nguard with the target!");
static const u8 sText_SharedItsPower[] = _("{B_ATK_NAME_WITH_PREFIX} shared its\npower with the target!");
static const u8 sText_SwapsDefAndSpDefOfAllPkmn[] = _("It created a bizarre area in which\nthe Defense and Sp.Def stats are swapped!");
static const u8 sText_BecameNimble[] = _("{B_ATK_NAME_WITH_PREFIX} became nimble!");
static const u8 sText_HurledIntoTheAir[] = _("{B_DEF_NAME_WITH_PREFIX} was hurled\ninto the air!");
static const u8 sText_HeldItemsLoseEffects[] = _("It created a bizarre area in which\nPokémon's held items lose their effects!");
static const u8 sText_FellStraightDown[] = _("{B_DEF_NAME_WITH_PREFIX} fell\nstraight down!");
static const u8 sText_TransformedIntoWaterType[] = _("{B_DEF_NAME_WITH_PREFIX} transformed\ninto the water type!");
static const u8 sText_PkmnAcquiredSimple[] = _("{B_DEF_NAME_WITH_PREFIX} acquired\nSimple!");
static const u8 sText_KindOffer[] = _("{B_DEF_NAME_WITH_PREFIX}\ntook the kind offer!");
static const u8 sText_ResetsTargetsStatLevels[] = _("{B_DEF_NAME_WITH_PREFIX}'s stat changes\nwere removed!");
static const u8 sText_AllySwitchPosition[] = _("{B_ATK_NAME_WITH_PREFIX} and\n{B_SCR_ACTIVE_NAME_WITH_PREFIX} switched places!");
static const u8 sText_RestoreTargetsHealth[] = _("{B_DEF_NAME_WITH_PREFIX}'s HP was restored!");
static const u8 sText_TookPkmnIntoTheSky[] = _("{B_ATK_NAME_WITH_PREFIX} took\n{B_DEF_NAME_WITH_PREFIX} into the sky!");
static const u8 sText_FreedFromSkyDrop[] = _("{B_DEF_NAME_WITH_PREFIX} was freed\nfrom the Sky Drop!");
static const u8 sText_PostponeTargetMove[] = _("{B_DEF_NAME_WITH_PREFIX}'s move\nwas postponed!");
static const u8 sText_ReflectTargetsType[] = _("{B_ATK_NAME_WITH_PREFIX}'s type\nchanged to match the {B_DEF_NAME_WITH_PREFIX}'s!");
static const u8 sText_TransferHeldItem[] = _("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM}\nfrom {B_ATK_NAME_WITH_PREFIX}");
static const u8 sText_EmbargoEnds[] = _("{B_ATK_TEAM1} side can\nuse items again!"); //confusing use logic idk
static const u8 sText_Electromagnetism[] = _("electromagnetism");
static const u8 sText_BufferEnds[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1}\nwore off!");
static const u8 sText_ThroatChopEnds[] = _("{B_ATK_NAME_WITH_PREFIX} can\nuse sound-based moves again!");
static const u8 sText_TelekinesisEnds[] = _("{B_ATK_NAME_WITH_PREFIX} was freed\nfrom the telekinesis!");
static const u8 sText_TailwindEnds[] = _("{B_ATK_TEAM1} team's tailwind\n petered out!");
static const u8 sText_LuckyChantEnds[] = _("{B_ATK_TEAM1} team's Lucky Chant\n wore off!");
static const u8 sText_TrickRoomEnds[] = _("The twisted dimensions returned to\nnormal!");
static const u8 sText_WonderRoomEnds[] = _("Wonder Room wore off, and\nDefense and Sp. Def stats returned to normal!");
static const u8 sText_MagicRoomEnds[] = _("Magic Room wore off, and\nheld items' effects returned to normal!");
static const u8 sText_MudSportEnds[] = _("The effects of Mud Sport have faded.");
static const u8 sText_WaterSportEnds[] = _("The effects of Water Sport have faded.");
static const u8 sText_GravityEnds[] = _("Gravity returned to normal!");
static const u8 sText_AquaRingHeal[] = _("Aqua Ring restored\n{B_ATK_NAME_WITH_PREFIX}'s HP!");
static const u8 sText_TargetAbilityRaisedStat[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nraised its {B_BUFF1}!");
static const u8 sText_TargetAbilityLoweredStat[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nlowered its {B_BUFF1}!");
static const u8 sText_AttackerAbilityRaisedStat[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nraised its {B_BUFF1}!");
static const u8 sText_ScriptingAbilityRaisedStat[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nraised its {B_BUFF1}!");
static const u8 sText_AuroraVeilEnds[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}\nwore off!");
static const u8 sText_ElectricTerrainEnds[] = _("The electricity disappeared\nfrom the battlefield.");
static const u8 sText_MistyTerrainEnds[] = _("The mist disappeared\nfrom the battlefield.");
static const u8 sText_PsychicTerrainEnds[] = _("The weirdness disappeared\nfrom the battlefield.");
static const u8 sText_GrassyTerrainEnds[] = _("The grass disappeared\nfrom the battlefield.");
static const u8 sText_TargetsStatWasMaxedOut[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} maxed\nits {B_BUFF1}!");
static const u8 sText_PoisonHealHpUp[] = _("The poison restored {B_ATK_NAME_WITH_PREFIX}'s\nHP a little!");
static const u8 sText_HeatTranceHpUp[] = _("The burn restored {B_ATK_NAME_WITH_PREFIX}'s\nHP a little!");
static const u8 sText_BadDreamsDmg[] = _("{B_DEF_NAME_WITH_PREFIX} is tormented\nby {B_ATK_ABILITY}!");
static const u8 sText_MoldBreakerEnters[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} breaks the mold!");
static const u8 sText_TeravoltEnters[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating \na bursting aura!");
static const u8 sText_TurboblazeEnters[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating\na blazing aura!");
static const u8 sText_SlowStartEnters[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is\nin a weakened state!{PAUSE 9}");
static const u8 sText_SlowStartEnd[] = _("{B_ATK_NAME_WITH_PREFIX}'s power has\nreturned to its zenith!{PAUSE 9}");
static const u8 sText_WonderGuardEnters[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is wreathed in\nan otherworldly veil!{PAUSE 36}"); //wraith something
static const u8 sText_WonderGuardEnds[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nhas dissipated!{PAUSE 36}");
static const u8 sText_SolarPowerHpDrop[] = _("The {B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\ntook its toll!");
static const u8 sText_AftermathDmg[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} tried to take\n{B_ATK_NAME_WITH_PREFIX} out with them!"); //fix this 
static const u8 sText_AnticipationActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} sensed {B_BUFF1}\nand shuddered in anticipation!");
static const u8 sText_ForewarnActivates[] = _("{B_SCR_ACTIVE_ABILITY} {B_BUFF3} {B_SCR_ACTIVE_NAME_WITH_PREFIX}\n{B_BUFF2} {B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}!");
static const u8 sText_IceBodyHpGain[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY}\nhealed it a little bit!");
//static const u8 sText_SnowWarningHail[] = _("It started to hail!"); //vsonic end turn abilities can't use src active, would print wrong values
static const u8 sText_SnowWarningHail[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nbrought down hail!");
//predicts a blizzard //chilling
//predits a dust storm /harsh
//predicts a heatwave / blazing
//predicts torrential rain / string messages for forecast one long weather i.e curr and next weather same / holding weather item
static const u8 sText_ForecastBlizzard[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\na chilling Blizzard!\p");
static const u8 sText_ForecastDuststorm[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\na harsh Dust Storm!\p");
static const u8 sText_ForecastHeatwave[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\na blazing Heatwave!\p");
static const u8 sText_ForecastTorrentialrain[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\nTorrential Rain!\p");
//otherwise use gMoveWeatherChangeStringIds 
//below is for second weather effect
static const u8 sText_ForecastSandstorm[] = _("The Forecast came true!\nA sandstorm brewed!\p"); 
static const u8 sText_ForecastHail[] = _("The Forecast came true!\nIt started to hail!\p"); 
static const u8 sText_ForecastRain[] = _("The Forecast came true!\nIt started to rain!\p");
static const u8 sText_ForecastSunny[] = _("The Forecast came true!\nThe sunlight got bright!\p");
//simplify just buffer in words for weather can do with switch cases
//for two diff weather effects from forecast
static const u8 sText_ForecastPrediction[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY} predicted\n{B_BUFF1} and {B_BUFF2}!\p");//learned ending with new paragraph lets it stay till press
static const u8 sText_Rain[] = _("rain");
static const u8 sText_Sun[] = _("sun");
static const u8 sText_Sand[] = _("sand");
static const u8 sText_Hail[] = _("hail"); //based on how did anticipatino/forecast, think won't need stringsIds for these?

<<<<<<< HEAD
static const u8 sText_FriskActivates[] = _("{B_ATK_NAME_WITH_PREFIX} frisked {B_DEF_NAME_WITH_PREFIX} and\nfound its {B_LAST_ITEM}!");
static const u8 sText_UnnerveEnters[] = _("The opposing team is too nervous\nto eat Berries!");
static const u8 sText_HarvestBerry[] = _("{B_ATK_NAME_WITH_PREFIX} harvested\nits {B_LAST_ITEM}!");
static const u8 sText_MoxieAtkRise[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} raised its Attack!");
static const u8 sText_MagicBounceActivates[] = _("The {B_DEF_NAME_WITH_PREFIX} bounced the\n{B_ATK_NAME_WITH_PREFIX} back!");
static const u8 sText_ProteanTypeChange[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} transformed\nit into the {B_BUFF1} type!");
static const u8 sText_SymbiosisItemPass[] = _("{B_ATK_NAME_WITH_PREFIX} passed its {B_LAST_ITEM}\nto {B_SCR_ACTIVE_NAME_WITH_PREFIX} through {B_ATK_ABILITY}!");
static const u8 sText_StealthRockAbsorbed[] = _("Pointed stones disappeared\nfrom around {B_ATK_TEAM2}'s team!");
static const u8 sText_StealthRockDmg[] = _("Pointed stones dug into\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_ToxicSpikesAbsorbed[] = _("The poison spikes disappeared\nfrom around {B_ATK_TEAM2} team's feet!");
static const u8 sText_ToxicSpikesPoisoned[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} was poisoned!");
static const u8 sText_StickyWebSwitchIn[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} was\ncaught in a Sticky Web!");
static const u8 sText_HealingWishCameTrue[] = _("The healing wish came true\nfor {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_HealingWishHealed[] = _("{B_ATK_NAME_WITH_PREFIX} regained health!");
static const u8 sText_LunarDanceCameTrue[] = _("{B_ATK_NAME_WITH_PREFIX} became cloaked\nin mystical moonlight!");
static const u8 sText_CursedBodyDisabled[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} was disabled\nby {B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!");
static const u8 sText_AttackerAquiredAbility[] = _("{B_ATK_NAME_WITH_PREFIX} acquired {B_LAST_ABILITY}!");
static const u8 sText_TargetStatWontGoHigher[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwon't go higher!");
static const u8 sText_PkmnMoveBouncedViaAbility[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} was refelcted\nby {B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}{PAUSE 26}!"); //had just barely enough space to not need \l escape
static const u8 sText_ImposterTransform[] = _("{B_ATK_NAME_WITH_PREFIX} transformed into\na {B_DEF_NAME_WITH_PREFIX} using {B_BUFF2}!");//replacing  last ability w buffer
static const u8 sText_InversionTransform[] = _("{B_ATK_NAME_WITH_PREFIX} transformed into\na {B_BUFF1} using {B_BUFF2}!");
const u8 gNotDoneYetDescription[] = _("This move effect is not done yet!\p"); //also potentially replace b def name since I want target species for impostre but something dif w inversion
                                                                        //actually look into handle nik case and if can just assign the found species to buff to get prefix or b_eff_namewith prefix

//end turn name scripts need to use B_ATK_NAME_WITH_PREFIX,  scr_active name or anything else causes issues
static const u8 sText_Battle_Pickup[] = _("{B_ATK_NAME_WITH_PREFIX} picked up\na {B_BUFF1}!{PAUSE 12}");
static const u8 sText_PkmnBlewAwayToxicSpikes[] = _("{B_ATK_NAME_WITH_PREFIX} blew away\nTOXIC SPIKES!");
static const u8 sText_PkmnBlewAwayStickyWeb[] = _("{B_ATK_NAME_WITH_PREFIX} blew away\nSTICKY WEB!");
static const u8 sText_PkmnBlewAwayStealthRock[] = _("{B_ATK_NAME_WITH_PREFIX} blew away\nSTEALTH ROCK!");
static const u8 sText_PkmnBlewAwaySteelSurge[] = _("{B_ATK_NAME_WITH_PREFIX} blew away\nSTEEL SURGE!");
static const u8 sText_StickyWebUsed[] = _("A sticky web spreads out on the\nground around {B_DEF_TEAM2} team!");
static const u8 sText_QuashSuccess[] = _("The opposing {B_ATK_NAME_WITH_PREFIX}'s move was postponed!");
static const u8 sText_IonDelugeOn[] = _("A deluge of ions showers\nthe battlefield!");
static const u8 sText_TopsyTurvySwitchedStats[] = _("{B_DEF_NAME_WITH_PREFIX}'s stat changes were\nall reversed!");
static const u8 sText_TerrainBecomesMisty[] = _("Mist swirled about\nthe battlefield!");
static const u8 sText_TerrainBecomesGrassy[] = _("Grass grew to cover\nthe battlefield!");
static const u8 sText_TerrainBecomesElectric[] = _("An electric current runs across\nthe battlefield!");
static const u8 sText_TerrainBecomesPsychic[] = _("The battlefield got weird!");
static const u8 sText_TerrainBecomesScorched[] = _("The battlefield was set aflame!");
static const u8 sText_TerrainBecomesFlooded[] = _("Water flooded The battlefield!");
static const u8 sText_TerrainBecomesOceanic[] = _("The battlefield is covered by\ndeep water!");
static const u8 sText_TargetElectrified[] = _("The {B_DEF_NAME_WITH_PREFIX}'s moves\nhave been electrified!");
static const u8 sText_AssaultVestDoesntAllow[] = _("The effects of the {B_LAST_ITEM} prevent status\nmoves from being used!\p");
static const u8 sText_GravityPreventsUsage[] = _("{B_ATK_NAME_WITH_PREFIX} can't use {B_CURRENT_MOVE}\nbecause of gravity!\p");
static const u8 sText_HealBlockPreventsUsage[] = _("{B_ATK_NAME_WITH_PREFIX} was\nprevented from healing!\p");
static const u8 sText_MegaEvoReacting[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ITEM} is \nreacting to {B_ATK_TRAINER_NAME}'s Mega Ring!");
static const u8 sText_FerventWishReached[] = _("{B_ATK_TRAINER_NAME}'s fervent wish\nhas reached {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_MegaEvoEvolved[] = _("{B_ATK_NAME_WITH_PREFIX} has Mega\nEvolved into Mega {B_BUFF1}!");
static const u8 sText_NoEffectOnTarget[] = _("It had no effect\non {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_BurstingFlames[] = _("The bursting flames\nhit {B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_BestowItemGiving[] = _("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM}\nfrom {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_ThirdTypeAdded[] = _("{B_BUFF1} type was added to\n{B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_FellForFeint[] = _("{B_DEF_NAME_WITH_PREFIX} fell for\nthe feint!");
static const u8 sText_PokemonCannotUseMove[] = _("{B_ATK_NAME_WITH_PREFIX} cannot\nuse {B_CURRENT_MOVE}!");
static const u8 sText_CoveredInPowder[] = _("{B_DEF_NAME_WITH_PREFIX} is covered in powder!");
static const u8 sText_PowderExplodes[] = _("When the flame touched the powder\non the Pokémon, it exploded!");
static const u8 sText_BelchCantUse[] = _("Belch cannot be used!\p");
static const u8 sText_BelchEatBerry[] = _("{B_ATK_NAME_WITH_PREFIX} ate its {B_BUFF1}!");
static const u8 sText_SpectralThiefSteal[] = _("{B_ATK_NAME_WITH_PREFIX} stole the target's\nboosted stats!");
static const u8 sText_GravityGrounding[] = _("{B_DEF_NAME_WITH_PREFIX} can't stay airborne\nbecause of gravity!");
static const u8 sText_FlyingEnemyCrashedDown[] = _("{B_DEF_NAME_WITH_PREFIX} crashed\nto the ground!");
static const u8 sText_MistyTerrainPreventsStatus[] = _("{B_DEF_NAME_WITH_PREFIX} surrounds itself\nwith a protective mist!");
static const u8 sText_GrassyTerrainHeals[] = _("{B_ATK_NAME_WITH_PREFIX} is healed\nby the grassy terrain!");
static const u8 sText_ElectricTerrainPreventsSleep[] = _("{B_DEF_NAME_WITH_PREFIX} surrounds itself\nwith electrified terrain!");
static const u8 sText_PsychicTerrainPreventsPriority[] = _("{B_DEF_NAME_WITH_PREFIX} surrounds itself\nwith psychic terrain!");
static const u8 sText_SafetyGooglesProtected[] = _("{B_DEF_NAME_WITH_PREFIX} is not affected\nthanks to its {B_LAST_ITEM}!");
static const u8 sText_FlowerVeilProtected[] = _("{B_DEF_NAME_WITH_PREFIX} surrounded itself\nwith a veil of petals!");
static const u8 sText_SweetVeilProtected[] = _("{B_DEF_NAME_WITH_PREFIX} surrounded itself\nwith a veil of sweetness!");
static const u8 sText_AromaVeilProtected[] = _("{B_DEF_NAME_WITH_PREFIX} is protected\nby an aromatic veil!");
static const u8 sText_CelebrateMessage[] = _("Congratulations, {B_PLAYER_NAME}!");
static const u8 sText_UsedInstructedMove[] = _("{B_ATK_NAME_WITH_PREFIX} used the move\ninstructed by {B_BUFF1}!");
static const u8 sText_LaserFocusMessage[] = _("{B_ATK_NAME_WITH_PREFIX}\nconcentrated intensely!");
static const u8 sText_GemActivates[] = _("{B_LAST_ITEM} strengthened\n{B_ATK_NAME_WITH_PREFIX}'s power!");
static const u8 sText_BerryDmgReducing[] = _("{B_LAST_ITEM} weakened the damage\nto {B_DEF_NAME_WITH_PREFIX}!");
static const u8 sText_TargetAteItem[] = _("{B_DEF_NAME_WITH_PREFIX} ate its {B_LAST_ITEM}!");
static const u8 sText_AirBalloonFloat[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} floats in the air\nwith its {B_LAST_ITEM}!");
static const u8 sText_AirBalloonPop[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_LAST_ITEM} popped!");
static const u8 sText_IncinerateBurn[] = _("{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}\nwas burnt up!");
static const u8 sText_StickyHoldAbsorb[] = _("{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM} was absorbed\nby {B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!");
static const u8 sText_BugBite[] = _("{B_ATK_NAME_WITH_PREFIX} stole and ate\n{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM}!");
static const u8 sText_IllusionWoreOff[] = _("{B_DEF_NAME_WITH_PREFIX}'s Illusion wore off!");
static const u8 sText_AttackerCuredTargetStatus[] = _("{B_ATK_NAME_WITH_PREFIX} cured\n{B_DEF_NAME_WITH_PREFIX}'s problem!");
static const u8 sText_AttackerLostType[] = _("{B_ATK_NAME_WITH_PREFIX} lost it's {B_BUFF3} type!");
static const u8 sText_HealerCure[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ABILITY}\ncured {B_SCR_ACTIVE_NAME_WITH_PREFIX}'s problem!");
static const u8 sText_AuraofLightAwaken[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ABILITY}\nawoke {B_SCR_ACTIVE_NAME_WITH_PREFIX}!");
static const u8 sText_ReceiverAbilityTakeOver[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nwas taken over!");
static const u8 sText_PkmnAbsorbingPower[] = _("{B_ATK_NAME_WITH_PREFIX} is absorbing power!");
static const u8 sText_NoOneWillBeAbleToRun[] = _("No one will be able to run away\nduring the next turn!");
static const u8 sText_DestinyKnotActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} fell in love\nfrom the {B_LAST_ITEM}!");
static const u8 sText_CloakedInAFreezingLight[] = _("{B_ATK_NAME_WITH_PREFIX} became cloaked\nin a freezing light!");
static const u8 sText_StatWasNotLowered[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1}\nwas not lowered!");
static const u8 sText_AuraFlaredToLife[] = _("{B_DEF_NAME_WITH_PREFIX}'s aura flared to life!");
static const u8 sText_AirLockActivates[] = _("The effects of weather\ndisappeared.");
static const u8 sText_DefeatistActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} lost the will to fight\nand is ready to run!{PAUSE 22}");
static const u8 sText_PressureActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is exerting its\npressure!");
static const u8 sText_IronWill_AtkCancel[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} made\n{B_SCR_ACTIVE_NAME_WITH_PREFIX} too afraid to attack!");
static const u8 sText_Ability_LostResolve[] = _("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} made\n{B_ATK_NAME_WITH_PREFIX} lose its resolve!");

//need fix the buffer make a function to prooperly buffer values and do cancel -done need test
static const u8 sText_DarkAuraActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating\na dark aura!");
static const u8 sText_FairyAuraActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is radiating\na fairy aura!");
static const u8 sText_AuraBreakActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} reversed all\nother POKéMON's auras!");
static const u8 sText_ComatoseActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is drowsing!");
static const u8 sText_ScreenCleanerActivates[] = _("All screens on the field were\ncleansed!");
static const u8 sText_FetchedPokeBall[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} found\na {B_LAST_ITEM}!");
static const u8 sText_BattlerAbilityRaisedStat[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'s {B_SCR_ACTIVE_ABILITY}\nraised its {B_BUFF1}!");
static const u8 sText_ASandstormKickedUp[] = _("A sandstorm kicked up!");
static const u8 sText_PkmnsWillPerishIn3Turns[] = _("Both Pokémon will perish\nin three turns!");
static const u8 sText_AbilityRaisedStatDrastically[] = _("{B_DEF_ABILITY} raised {B_DEF_NAME_WITH_PREFIX}'s\n{B_BUFF1} drastically!");
static const u8 sText_FellInLoveAtFirstSight[] = _("{B_DEF_NAME_WITH_PREFIX} fell in love\nat first sight!");
static const u8 sText_SnapTrap[] = _("{B_DEF_NAME_WITH_PREFIX} was ensnared\nby {B_ATK_NAME_WITH_PREFIX}'s trap!");
static const u8 sText_PkmnsPoisonWorsened[] = _("{B_EFF_NAME_WITH_PREFIX}'s poisoning got worse!\nIt's badly poisoned!");


//extra stuff new
static const u8 sText_Your1[] = _("Your");
static const u8 sText_Opposing1[] = _("The opposing");
static const u8 sText_Your2[] = _("your");
static const u8 sText_Opposing2[] = _("the opposing");

static const u8 sText_AsOneEnters[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} has two Abilities!");
static const u8 sText_CuriousMedicineEnters[] = _("{B_EFF_NAME_WITH_PREFIX}'s\nstat changes were reset!");
static const u8 sText_CanActFaster[] = _("{B_ATK_NAME_WITH_PREFIX} moved faster,\nthanks to {B_BUFF1}!"); //quick claw activatino etc.
static const u8 sText_MicleBerryActivates[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} boosted the accuracy of its\nnext move using {B_LAST_ITEM}!");
static const u8 sText_PkmnShookOffTheTaunt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} shook off\nthe taunt!");
static const u8 sText_PkmnGotOverItsInfatuation[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} got over\nits infatuation!");
static const u8 sText_ItemCannotBeRemoved[] = _("{B_ATK_NAME_WITH_PREFIX}'s item cannot be removed!");
static const u8 sText_StickyBarbTransfer[] = _("The {B_LAST_ITEM} attached itself to\n{B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_PkmnBurnHealed[] = _("{B_DEF_NAME_WITH_PREFIX}'s\nburn was healed.");
static const u8 sText_RedCardActivate[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} held up its {B_LAST_ITEM}\nagainst {B_ATK_NAME_WITH_PREFIX}!");
static const u8 sText_EjectButtonActivate[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is switched\nout with the {B_LAST_ITEM}!");
static const u8 sText_AttackerGotOverInfatuation[] = _("{B_ATK_NAME_WITH_PREFIX} got over\nits infatuation!");
static const u8 sText_TormentedNoMore[] = _("{B_ATK_NAME_WITH_PREFIX} is\ntormented no more!");
static const u8 sText_HealBlockedNoMore[] = _("{B_ATK_NAME_WITH_PREFIX} is cured of\nits heal block!");
static const u8 sText_AttackerBecameFullyCharged[] = _("{B_ATK_NAME_WITH_PREFIX} became fully charged\ndue to its bond with its trainer!\p");
static const u8 sText_AttackerBecameAshSpecies[] = _("{B_ATK_NAME_WITH_PREFIX} became Ash-{B_BUFF1}!\p");
static const u8 sText_ExtremelyHarshSunlight[] = _("The sunlight turned\nextremely harsh!");
static const u8 sText_ExtremeSunlightFaded[] = _("The extreme sunlight faded.{PAUSE 32}");
static const u8 sText_MoveEvaporatedInTheHarshSunlight[] = _("The Water-type attack evaporated\nin the harsh sunlight!");
static const u8 sText_ExtremelyHarshSunlightWasNotLessened[] = _("The extremely harsh sunlight\nwas not lessened at all!");
static const u8 sText_HeavyRain[] = _("A heavy rain began to fall!");
static const u8 sText_HeavyRainLifted[] = _("The heavy rain has lifted!{PAUSE 32}");
static const u8 sText_MoveFizzledOutInTheHeavyRain[] = _("The Fire-type attack fizzled out\nin the heavy rain!");
static const u8 sText_NoReliefFromHeavyRain[] = _("There is no relief from\nthis heavy rain!");
static const u8 sText_MysteriousAirCurrent[] = _("A mysterious air current is\nprotecting Flying-type Pokémon!");
static const u8 sText_StrongWindsDissipated[] = _("The mysterious strong winds\nhave dissipated!{PAUSE 32}");
static const u8 sText_MysteriousAirCurrentBlowsOn[] = _("The mysterious air current\nblows on regardless!");
static const u8 sText_AttackWeakenedByStrongWinds[] = _("The mysterious strong winds\nweakened the attack!");
static const u8 sText_StuffCheeksCantSelect[] = _("Stuff Cheeks cannot be\nselected without a Berry!\p");
static const u8 sText_PkmnRevertedToPrimal[] = _("{B_ATK_NAME_WITH_PREFIX} reverted to its primal form!");
static const u8 sText_ButPokemonCantUseTheMove[] = _("But {B_ATK_NAME_WITH_PREFIX} can't\nuse the move!");
static const u8 sText_ButHoopaCantUseIt[] = _("But Hoopa can't use it\nthe way it is now!");
static const u8 sText_BrokeThroughProtection[] = _("It broke through the\n{B_DEF_NAME_WITH_PREFIX}'s protection!");
static const u8 sText_AbilityAllowsOnlyMove[] = _("{B_ATK_ABILITY} allows the\nuse of only {B_CURRENT_MOVE}!\p");
static const u8 sText_SwappedAbilities[] = _("{B_DEF_NAME_WITH_PREFIX} swapped Abilities\nwith its target!");
static const u8 sText_PastelVeilProtected[] = _("{B_DEF_NAME_WITH_PREFIX} is protected\nby a pastel veil!");
static const u8 sText_PastelVeilEnters[] = _("{B_DEF_NAME_WITH_PREFIX} was cured\nof its poisoning!");
static const u8 sText_CorruptionActivates[] = _("{B_ATK_NAME_WITH_PREFIX} spread {B_ATK_ABILITY}!\n{B_DEF_TEAM1} side can't heal!\p");
static const u8 sText_BanditActivates[] = _("The {B_ATK_ABILITY} is on the scene!\n{B_DEF_TEAM1} side can't use items!{PAUSE 32}");
static const u8 sText_BattlerTypeChangedTo[] = _("{B_BUFF1}'s type\nchanged to {B_BUFF2}!");
static const u8 sText_BothCanNoLongerEscape[] = _("Neither Pokémon can run away!");
static const u8 sText_CantEscapeDueToUsedMove[] = _("{B_ATK_NAME_WITH_PREFIX} can no longer escape\nbecause it used {B_CURRENT_MOVE}!");
static const u8 sText_PkmnBecameWeakerToFire[] = _("{B_DEF_NAME_WITH_PREFIX} became\nweaker to fire!");
static const u8 sText_PkmnAboutToBeAttackedByItsItem[] = _("{B_DEF_NAME_WITH_PREFIX} is about\nto be attacked by its {B_BUFF1}!");
static const u8 sText_CantEscapeBecauseOfCurrentMove[] = _("{B_DEF_NAME_WITH_PREFIX} can no longer escape\nbecause of {B_CURRENT_MOVE}!");
static const u8 sText_PkmnTookTargetHigh[] = _("{B_ATK_NAME_WITH_PREFIX} took {B_DEF_NAME_WITH_PREFIX}\ninto the air!");
static const u8 sText_TargetTooHeavy[] = _("But the target was too heavy!");  //for seismic toss fail, 
static const u8 sText_MeteorBeamCharging[] = _("{B_ATK_NAME_WITH_PREFIX} is overflowing\nwith space energy!");
static const u8 sText_HeatingUpBeak[] = _("{B_ATK_NAME_WITH_PREFIX} started\nheating up its beak!");
static const u8 sText_StatWentBackDown[] = _("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} went back down!"); //main use revert sky drop evasion boost, want specific stat tobe in buffer
static const u8 sText_CelebrateTrollString[] = _("{B_ATK_NAME_WITH_PREFIX} began to dance strangely!");
static const u8 sText_JudgmentString[] = _("{B_DEF_NAME} faced {STR_VAR_2} Judgment!{PAUSE 15}");

//default values
static const u8 sText_YouThrowABallNowRight[] = _("You throw a BALL now, right?\nI… I'll do my best!");
const u8 gText_ForPetesSake[] = _("OAK: Oh, for Pete's sake…\nSo pushy, as always.\p{B_PLAYER_NAME}.\pYou've never had a POKéMON battle\nbefore, have you?\pA POKéMON battle is when TRAINERS\npit their POKéMON against each\lother.\p");
const u8 gText_TheTrainerThat[] = _("The TRAINER that makes the other\nTRAINER's POKéMON faint by lowering\ltheir HP to “0,” wins.\p");
const u8 gText_TryBattling[] = _("But rather than talking about it,\nyou'll learn more from experience.\pTry battling and see for yourself.\p");
const u8 gText_InflictingDamageIsKey[] = _("OAK: Inflicting damage on the foe\nis the key to any battle.\p");
const u8 gText_LoweringStats[] = _("OAK: Lowering the foe's stats\nwill put you at an advantage.\p");
const u8 gText_KeepAnEyeOnHP[] = _("OAK: Keep your eyes on your\nPOKéMON's HP.\pIt will faint if the HP drops to\n“0.”\p");
const u8 gText_OakNoRunningFromATrainer[] = _("OAK: No! There's no running away\nfrom a TRAINER POKéMON battle!\p");
const u8 gText_WinEarnsPrizeMoney[] = _("OAK: Hm! Excellent!\pIf you win, you earn prize money,\nand your POKéMON will grow!\pBattle other TRAINERS and make\nyour POKéMON strong!\p");
const u8 gText_HowDissapointing[] = _("OAK: Hm…\nHow disappointing…\pIf you win, you earn prize money,\nand your POKéMON grow.\pBut if you lose, {B_PLAYER_NAME}, you end\nup paying prize money…\pHowever, since you had no warning\nthis time, I'll pay for you.\pBut things won't be this way once\nyou step outside these doors.\pThat's why you must strengthen your\nPOKéMON by battling wild POKéMON.\p");


//need add rest of EE stuff and then put into order I want
//replace all static strings with compounds
//this is array must match order of values in battle_string_ids.h to be properly defined
const u8 *const gBattleStringsTable[] = {
    [STRINGID_TRAINER1LOSETEXT]              = sText_Trainer1LoseText,
    [STRINGID_PKMNGAINEDEXP]                 = sText_PkmnGainedEXP,
    [STRINGID_PKMNGREWTOLV]                  = sText_PkmnGrewToLv,
    [STRINGID_PKMNLEARNEDMOVE]               = sText_PkmnLearnedMove,
    [STRINGID_TRYTOLEARNMOVE1]               = sText_TryToLearnMove1,
    [STRINGID_TRYTOLEARNMOVE2]               = sText_TryToLearnMove2,
    [STRINGID_TRYTOLEARNMOVE3]               = sText_TryToLearnMove3,
    [STRINGID_PKMNFORGOTMOVE]                = sText_PkmnForgotMove,
    [STRINGID_STOPLEARNINGMOVE]              = sText_StopLearningMove,
    [STRINGID_DIDNOTLEARNMOVE]               = sText_DidNotLearnMove,
    [STRINGID_PKMNLEARNEDMOVE2]              = sText_PkmnLearnedMove2,
    [STRINGID_ATTACKMISSED]                  = sText_AttackMissed,
    [STRINGID_PKMNPROTECTEDITSELF]           = sText_PkmnProtectedItself,
    [STRINGID_STATSWONTINCREASE2]            = sText_StatsWontIncrease2,
    [STRINGID_AVOIDEDDAMAGE]                 = sText_AvoidedDamage,
    [STRINGID_ITDOESNTAFFECT]                = sText_ItDoesntAffect,
    [STRINGID_ATTACKERFAINTED]               = sText_AttackerFainted,
    [STRINGID_TARGETFAINTED]                 = sText_TargetFainted,
    [STRINGID_PLAYERGOTMONEY]                = sText_PlayerGotMoney,
    [STRINGID_PLAYERWHITEOUT]                = sText_PlayerWhiteout,
    [STRINGID_PLAYERWHITEOUT2]               = sText_PlayerPanicked,
    [STRINGID_PREVENTSESCAPE]                = sText_PreventsEscape,
    [STRINGID_HITXTIMES]                     = sText_HitXTimes,
    [STRINGID_PKMNFROSTBITTEN]               = sText_PkmnGotFrostbite,
    [STRINGID_PKMNFELLASLEEP]                = sText_PkmnFellAsleep,
    [STRINGID_PKMNMADESLEEP]                 = sText_PkmnMadeSleep,
    [STRINGID_PKMNALREADYASLEEP]             = sText_PkmnAlreadyAsleep,
    [STRINGID_PKMNALREADYASLEEP2]            = sText_PkmnAlreadyAsleep2,
    [STRINGID_PKMNWASNTAFFECTED]             = sText_PkmnWasntAffected,
    [STRINGID_PKMNWASPOISONED]               = sText_PkmnWasPoisoned,
    [STRINGID_PKMNPOISONEDBY]                = sText_PkmnPoisonedBy,
    [STRINGID_PKMNHURTBYPOISON]              = sText_PkmnHurtByPoison,
    [STRINGID_PKMNALREADYPOISONED]           = sText_PkmnAlreadyPoisoned,
    [STRINGID_PKMNBADLYPOISONED]             = sText_PkmnBadlyPoisoned,
    [STRINGID_PKMNENERGYDRAINED]             = sText_PkmnEnergyDrained,
    [STRINGID_PKMNWASBURNED]                 = sText_PkmnWasBurned,
    [STRINGID_PKMNBURNEDBY]                  = sText_PkmnBurnedBy,
    [STRINGID_PKMNHURTBYBURN]                = sText_PkmnHurtByBurn,
    [STRINGID_PKMNHURTBYFREEZE]              = sText_PkmnHurtByFrost,
    [STRINGID_PKMNWASFROZEN]                 = sText_PkmnWasFrozen,
    [STRINGID_PKMNFROZENBY]                  = sText_PkmnFrozenBy,
    [STRINGID_PKMNISFROZEN]                  = sText_PkmnIsFrozen,
    [STRINGID_PKMNWASDEFROSTED]              = sText_PkmnWasDefrosted,
    [STRINGID_PKMNWASDEFROSTED2]             = sText_PkmnWasDefrosted2,
    [STRINGID_PKMNWASDEFROSTEDBY]            = sText_PkmnWasDefrostedBy,
    [STRINGID_PKMNWASPARALYZED]              = sText_PkmnWasParalyzed,
    [STRINGID_PKMNWASPARALYZEDBY]            = sText_PkmnWasParalyzedBy,
    [STRINGID_PKMNISPARALYZED]               = sText_PkmnIsParalyzed,
    [STRINGID_PKMNISALREADYPARALYZED]        = sText_PkmnIsAlreadyParalyzed,
    [STRINGID_PKMNHEALEDPARALYSIS]           = sText_PkmnHealedParalysis,
    [STRINGID_PKMNDREAMEATEN]                = sText_PkmnDreamEaten,
    [STRINGID_STATSWONTINCREASE]             = sText_StatsWontIncrease,
    [STRINGID_STATSWONTDECREASE]             = sText_StatsWontDecrease,
    [STRINGID_TEAMSTOPPEDWORKING]            = sText_TeamStoppedWorking,
    [STRINGID_FOESTOPPEDWORKING]             = sText_FoeStoppedWorking,
    [STRINGID_PKMNISCONFUSED]                = sText_PkmnIsConfused,
    [STRINGID_PKMNHEALEDCONFUSION]           = sText_PkmnHealedConfusion,
    [STRINGID_PKMNWASCONFUSED]               = sText_PkmnWasConfused,
    [STRINGID_PKMNALREADYCONFUSED]           = sText_PkmnAlreadyConfused,
    [STRINGID_PKMNFELLINLOVE]                = sText_PkmnFellInLove,
    [STRINGID_PKMNINLOVEWITHBATTLER]         = sText_PkmnInLoveWithBattler,
    [STRINGID_PKMNINLOVE]                    = sText_PkmnInLove,
    [STRINGID_PKMNIMMOBILIZEDBYLOVE]         = sText_PkmnImmobilizedByLove,
    [STRINGID_PKMNBLOWNAWAY]                 = sText_PkmnBlownAway,
    [STRINGID_PKMNCHANGEDTYPE]               = sText_PkmnChangedType,
    [STRINGID_PKMNFLINCHED]                  = sText_PkmnFlinched,
    [STRINGID_PKMNREGAINEDHEALTH]            = sText_PkmnRegainedHealth,
    [STRINGID_PKMNHPFULL]                    = sText_PkmnHPFull,
    [STRINGID_PKMNRAISEDSPDEF]               = sText_PkmnRaisedSpDef,
    [STRINGID_PKMNRAISEDDEF]                 = sText_PkmnRaisedDef,
    [STRINGID_PKMNCOVEREDBYVEIL]             = sText_PkmnCoveredByVeil,
    [STRINGID_PKMNUSEDSAFEGUARD]             = sText_PkmnUsedSafeguard,
    [STRINGID_PKMNSAFEGUARDEXPIRED]          = sText_PkmnSafeguardExpired,
    [STRINGID_PKMNWENTTOSLEEP]               = sText_PkmnWentToSleep,
    [STRINGID_PKMNSLEPTHEALTHY]              = sText_PkmnSleptHealthy,
    [STRINGID_PKMNWHIPPEDWHIRLWIND]          = sText_PkmnWhippedWhirlwind,
    [STRINGID_PKMNTOOKSUNLIGHT]              = sText_PkmnTookSunlight,
    [STRINGID_PKMNLOWEREDHEAD]               = sText_PkmnLoweredHead,
    [STRINGID_PKMNISGLOWING]                 = sText_PkmnIsGlowing,
    [STRINGID_PKMNFLEWHIGH]                  = sText_PkmnFlewHigh,
    [STRINGID_PKMNDUGHOLE]                   = sText_PkmnDugHole,
    [STRINGID_PKMNSQUEEZEDBYBIND]            = sText_PkmnSqueezedByBind,
    [STRINGID_PKMNTRAPPEDINVORTEX]           = sText_PkmnTrappedInVortex,
    [STRINGID_PKMNWRAPPEDBY]                 = sText_PkmnWrappedBy,
    [STRINGID_PKMNCLAMPED]                   = sText_PkmnClamped,
    [STRINGID_PKMNHURTBY]                    = sText_PkmnHurtBy,
    [STRINGID_PKMNFREEDFROM]                 = sText_PkmnFreedFrom,
    [STRINGID_PKMNCRASHED]                   = sText_PkmnCrashed,
    [STRINGID_PKMNSHROUDEDINMIST]            = gBattleText_MistShroud,
    [STRINGID_PKMNPROTECTEDBYMIST]           = sText_PkmnProtectedByMist,
    [STRINGID_PKMNGETTINGPUMPED]             = gBattleText_GetPumped,
    [STRINGID_PKMNHITWITHRECOIL]             = sText_PkmnHitWithRecoil,
    [STRINGID_PKMNPROTECTEDITSELF2]          = sText_PkmnProtectedItself2,
    [STRINGID_PKMNBUFFETEDBYSANDSTORM]       = sText_PkmnBuffetedBySandstorm,
    [STRINGID_PKMNPELTEDBYHAIL]              = sText_PkmnPeltedByHail,
    [STRINGID_PKMNSEEDED]                    = sText_PkmnSeeded,
    [STRINGID_PKMNEVADEDATTACK]              = sText_PkmnEvadedAttack,
    [STRINGID_PKMNSAPPEDBYLEECHSEED]         = sText_PkmnSappedByLeechSeed,
    [STRINGID_PKMNFASTASLEEP]                = sText_PkmnFastAsleep,
    [STRINGID_PKMNWOKEUP]                    = sText_PkmnWokeUp,
    [STRINGID_PKMNUPROARKEPTAWAKE]           = sText_PkmnUproarKeptAwake,
    [STRINGID_PKMNWOKEUPINUPROAR]            = sText_PkmnWokeUpInUproar,
    [STRINGID_PKMNWOKEUPREFRESHED]           = sText_PkmnWokeUpRefreshed,
    [STRINGID_PKMNCAUSEDUPROAR]              = sText_PkmnCausedUproar,
    [STRINGID_PKMNMAKINGUPROAR]              = sText_PkmnMakingUproar,
    [STRINGID_PKMNCALMEDDOWN]                = sText_PkmnCalmedDown,
    [STRINGID_PKMNCANTSLEEPINUPROAR]         = sText_PkmnCantSleepInUproar,
    [STRINGID_PKMNSTOCKPILED]                = sText_PkmnStockpiled,
    [STRINGID_PKMNCANTSTOCKPILE]             = sText_PkmnCantStockpile,
    [STRINGID_PKMNCANTSLEEPINUPROAR2]        = sText_PkmnCantSleepInUproar2,
    [STRINGID_UPROARKEPTPKMNAWAKE]           = sText_UproarKeptPkmnAwake,
    [STRINGID_PKMNSTAYEDAWAKEUSING]          = sText_PkmnStayedAwakeUsing,
    [STRINGID_PKMNSTORINGENERGY]             = sText_PkmnStoringEnergy,
    [STRINGID_PKMNUNLEASHEDENERGY]           = sText_PkmnUnleashedEnergy,
    [STRINGID_PKMNFATIGUECONFUSION]          = sText_PkmnFatigueConfusion,
    [STRINGID_PKMNPICKEDUPITEM]              = sText_PkmnPickedUpItem,
    [STRINGID_PKMNUNAFFECTED]                = sText_PkmnUnaffected,
    [STRINGID_PKMNTRANSFORMEDINTO]           = sText_PkmnTransformedInto,
    [STRINGID_PKMNMADESUBSTITUTE]            = sText_PkmnMadeSubstitute,
    [STRINGID_PKMNHASSUBSTITUTE]             = sText_PkmnHasSubstitute,
    [STRINGID_SUBSTITUTEDAMAGED]             = sText_SubstituteDamaged,
    [STRINGID_PKMNSUBSTITUTEFADED]           = sText_PkmnSubstituteFaded,
    [STRINGID_PKMNMUSTRECHARGE]              = sText_PkmnMustRecharge,
    [STRINGID_PKMNRAGEBUILDING]              = sText_PkmnRageBuilding,
    [STRINGID_PKMNMOVEWASDISABLED]           = sText_PkmnMoveWasDisabled,
    [STRINGID_PKMNMOVEISDISABLED]            = sText_PkmnMoveIsDisabled,
    [STRINGID_PKMNMOVEDISABLEDNOMORE]        = sText_PkmnMoveDisabledNoMore,
    [STRINGID_PKMNGOTENCORE]                 = sText_PkmnGotEncore,
    [STRINGID_PKMNENCOREENDED]               = sText_PkmnEncoreEnded,
    [STRINGID_PKMNTOOKAIM]                   = sText_PkmnTookAim,
    [STRINGID_PKMNSKETCHEDMOVE]              = sText_PkmnSketchedMove,
    [STRINGID_PKMNTRYINGTOTAKEFOE]           = sText_PkmnTryingToTakeFoe,
    [STRINGID_PKMNTOOKFOE]                   = sText_PkmnTookFoe,
    [STRINGID_PKMNREDUCEDPP]                 = sText_PkmnReducedPP,
    [STRINGID_PKMNSTOLEITEM]                 = sText_PkmnStoleItem,
    [STRINGID_TARGETCANTESCAPENOW]           = sText_TargetCantEscapeNow,
    [STRINGID_PKMNFELLINTONIGHTMARE]         = sText_PkmnFellIntoNightmare,
    [STRINGID_PKMNLOCKEDINNIGHTMARE]         = sText_PkmnLockedInNightmare,
    [STRINGID_PKMNLAIDCURSE]                 = sText_PkmnLaidCurse,
    [STRINGID_PKMNAFFLICTEDBYCURSE]          = sText_PkmnAfflictedByCurse,
    [STRINGID_SPIKESSCATTERED]               = sText_SpikesScattered,
    [STRINGID_PKMNHURTBYSPIKES]              = sText_PkmnHurtBySpikes,
    [STRINGID_PKMNIDENTIFIED]                = sText_PkmnIdentified,
    [STRINGID_PKMNPERISHCOUNTFELL]           = sText_PkmnPerishCountFell,
    [STRINGID_PKMNBRACEDITSELF]              = sText_PkmnBracedItself,
    [STRINGID_PKMNENDUREDHIT]                = sText_PkmnEnduredHit,
    [STRINGID_MAGNITUDESTRENGTH]             = sText_MagnitudeStrength,
    [STRINGID_PKMNCUTHPMAXEDATTACK]          = sText_PkmnCutHPMaxedAttack,
    [STRINGID_PKMNCOPIEDSTATCHANGES]         = sText_PkmnCopiedStatChanges,
    [STRINGID_PKMNGOTFREE]                   = sText_PkmnGotFree,
    [STRINGID_PKMNSHEDLEECHSEED]             = sText_PkmnShedLeechSeed,
    [STRINGID_PKMNBLEWAWAYSPIKES]            = sText_PkmnBlewAwaySpikes,
    [STRINGID_PKMNFLEDFROMBATTLE]            = sText_PkmnFledFromBattle,
    [STRINGID_PKMNFORESAWATTACK]             = sText_PkmnForesawAttack,
    [STRINGID_PKMNTOOKATTACK]                = sText_PkmnTookAttack,
    [STRINGID_PKMNATTACK]                    = sText_PkmnAttack,
    [STRINGID_PKMNCENTERATTENTION]           = sText_PkmnCenterAttention,
    [STRINGID_PKMNCHARGINGPOWER]             = sText_PkmnChargingPower,
    [STRINGID_NATUREPOWERTURNEDINTO]         = sText_NaturePowerTurnedInto,
    [STRINGID_PKMNSTATUSNORMAL]              = sText_PkmnStatusNormal,
    [STRINGID_PKMNHASNOMOVESLEFT]            = sText_PkmnHasNoMovesLeft,
    [STRINGID_PKMNSUBJECTEDTOTORMENT]        = sText_PkmnSubjectedToTorment,
    [STRINGID_PKMNCANTUSEMOVETORMENT]        = sText_PkmnCantUseMoveTorment,
    [STRINGID_PKMNTIGHTENINGFOCUS]           = sText_PkmnTighteningFocus,
    [STRINGID_PKMNFELLFORTAUNT]              = sText_PkmnFellForTaunt,
    [STRINGID_PKMNCANTUSEMOVETAUNT]          = sText_PkmnCantUseMoveTaunt,
    [STRINGID_PKMNREADYTOHELP]               = sText_PkmnReadyToHelp,
    [STRINGID_PKMNSWITCHEDITEMS]             = sText_PkmnSwitchedItems,
    [STRINGID_PKMNCOPIEDFOE]                 = sText_PkmnCopiedFoe,
    [STRINGID_PKMNMADEWISH]                  = sText_PkmnMadeWish,
    [STRINGID_PKMNWISHCAMETRUE]              = sText_PkmnWishCameTrue,
    [STRINGID_PKMNPLANTEDROOTS]              = sText_PkmnPlantedRoots,
    [STRINGID_PKMNABSORBEDNUTRIENTS]         = sText_PkmnAbsorbedNutrients,
    [STRINGID_PKMNANCHOREDITSELF]            = sText_PkmnAnchoredItself,
    [STRINGID_PKMNWASMADEDROWSY]             = sText_PkmnWasMadeDrowsy,
    [STRINGID_PKMNKNOCKEDOFF]                = sText_PkmnKnockedOff,
    [STRINGID_PKMNSWAPPEDABILITIES]          = sText_PkmnSwappedAbilities,
    [STRINGID_PKMNSEALEDOPPONENTMOVE]        = sText_PkmnSealedOpponentMove,
    [STRINGID_PKMNCANTUSEMOVESEALED]         = sText_PkmnCantUseMoveSealed,
    [STRINGID_PKMNWANTSGRUDGE]               = sText_PkmnWantsGrudge,
    [STRINGID_PKMNLOSTPPGRUDGE]              = sText_PkmnLostPPGrudge,
    [STRINGID_PKMNSHROUDEDITSELF]            = sText_PkmnShroudedItself,
    [STRINGID_PKMNMOVEBOUNCED]               = sText_PkmnMoveBounced,
    [STRINGID_PKMNWAITSFORTARGET]            = sText_PkmnWaitsForTarget,
    [STRINGID_PKMNSNATCHEDMOVE]              = sText_PkmnSnatchedMove,
    [STRINGID_PKMNMADEITRAIN]                = sText_PkmnMadeItRain,
    [STRINGID_PKMNRAISEDSPEED]               = sText_PkmnRaisedSpeed,
    [STRINGID_PKMNPROTECTEDBY]               = sText_PkmnProtectedBy,
    [STRINGID_PKMNPREVENTSUSAGE]             = sText_PkmnPreventsUsage,
    [STRINGID_PKMNRESTOREDHPUSING]           = sText_PkmnRestoredHPUsing,
    [STRINGID_PKMNCHANGEDTYPEWITH]           = sText_PkmnChangedTypeWith,
    [STRINGID_PKMNPREVENTSPARALYSISWITH]     = sText_PkmnPreventsParalysisWith,
    [STRINGID_PKMNIGNOREDADVANCESWITH]       = sText_PkmnResistedtheMoodWith,
    [STRINGID_PKMNPREVENTSPOISONINGWITH]     = sText_PkmnPreventsPoisoningWith,
    [STRINGID_PKMNPREVENTSCONFUSIONWITH]     = sText_PkmnPreventsConfusionWith,
    [STRINGID_PKMNRAISEDFIREPOWERWITH]       = sText_PkmnRaisedFirePowerWith,
    [STRINGID_PKMNANCHORSITSELFWITH]         = sText_PkmnAnchorsItselfWith,
    [STRINGID_PKMNCUTSATTACKWITH]            = sText_PkmnCutsAttackWith, 
    [STRINGID_DARKTYPE_INTIMIDATE_RESIST]    = sText_DarkTypeIntimidateResist,
    [STRINGID_PKMNPREVENTSSTATLOSSWITH]      = sText_PkmnPreventsStatLossWith,
    [STRINGID_PKMNHURTSWITHABILITY]          = sText_PkmnHurtsWith,
    [STRINGID_PKMNTRACED]                    = sText_PkmnTraced,
    [STRINGID_STATSHARPLY]                   = sText_StatSharply,
    [STRINGID_STATROSE]                      = gBattleText_Rose,
    [STRINGID_STATHARSHLY]                   = sText_StatHarshly,
    [STRINGID_STATFELL]                      = sText_StatFell,
    [STRINGID_ATTACKERSSTATROSE]              = sText_PkmnsStatChanged,
    [STRINGID_DEFENDERSSTATROSE]             = gText_PkmnsStatChanged2,
    [STRINGID_ATTACKERSSTATFELL]             = sText_PkmnsStatChanged3,
    [STRINGID_DEFENDERSSTATFELL]             = sText_PkmnsStatChanged4,
    [STRINGID_CRITICALHIT]                   = sText_CriticalHit,
    [STRINGID_ONEHITKO]                      = sText_OneHitKO,
    [STRINGID_123POOF]                       = sText_123Poof,
    [STRINGID_ANDELLIPSIS]                   = sText_AndEllipsis,
    [STRINGID_NOTVERYEFFECTIVE]              = sText_NotVeryEffective,
    [STRINGID_SUPEREFFECTIVE]                = sText_SuperEffective,
    [STRINGID_GOTAWAYSAFELY]                 = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED]                  = sText_WildPkmnFled,
    [STRINGID_NORUNNINGFROMTRAINERS]         = sText_NoRunningFromTrainers,
    [STRINGID_CANTESCAPE]                    = sText_CantEscape,
    [STRINGID_DONTLEAVEBIRCH]                = sText_EmptyString5,
    [STRINGID_BUTNOTHINGHAPPENED]            = sText_ButNothingHappened,
    [STRINGID_BUTITFAILED]                   = sText_ButItFailed,
    [STRINGID_ITHURTCONFUSION]               = sText_ItHurtConfusion,
    [STRINGID_MIRRORMOVEFAILED]              = sText_MirrorMoveFailed,
    [STRINGID_STARTEDTORAIN]                 = sText_StartedToRain,
    [STRINGID_DOWNPOURSTARTED]               = sText_DownpourStarted,
    [STRINGID_RAINCONTINUES]                 = sText_RainContinues,
    [STRINGID_DOWNPOURCONTINUES]             = sText_DownpourContinues,
    [STRINGID_RAINSTOPPED]                   = sText_RainStopped,
    [STRINGID_SANDSTORMBREWED]               = sText_SandstormBrewed,
    [STRINGID_SANDSTORMRAGES]                = sText_SandstormRages,
    [STRINGID_SANDSTORMSUBSIDED]             = sText_SandstormSubsided,
    [STRINGID_SUNLIGHTGOTBRIGHT]             = sText_SunlightGotBright,
    [STRINGID_SUNLIGHTSTRONG]                = sText_SunlightStrong,
    [STRINGID_SUNLIGHTFADED]                 = sText_SunlightFaded,
    [STRINGID_STARTEDHAIL]                   = sText_StartedHail,
    [STRINGID_HAILCONTINUES]                 = sText_HailContinues,
    [STRINGID_HAILSTOPPED]                   = sText_HailStopped,
    [STRINGID_FAILEDTOSPITUP]                = sText_FailedToSpitUp,
    [STRINGID_FAILEDTOSWALLOW]               = sText_FailedToSwallow,
    [STRINGID_WINDBECAMEHEATWAVE]            = sText_WindBecameHeatWave,
    [STRINGID_STATCHANGESGONE]               = sText_StatChangesGone,
    [STRINGID_COINSSCATTERED]                = sText_CoinsScattered,
    [STRINGID_TOOWEAKFORSUBSTITUTE]          = sText_TooWeakForSubstitute,
    [STRINGID_SHAREDPAIN]                    = sText_SharedPain,
    [STRINGID_BELLCHIMED]                    = sText_BellChimed,
    [STRINGID_FAINTINTHREE]                  = sText_FaintInThree,
    [STRINGID_NOPPLEFT]                      = sText_NoPPLeft,
    [STRINGID_BUTNOPPLEFT]                   = sText_ButNoPPLeft,
    [STRINGID_PLAYERUSEDITEM]                = sText_PlayerUsedItem,
    [STRINGID_OLDMANUSEDITEM]                = sText_OldManUsedItem,
    [STRINGID_TRAINERBLOCKEDBALL]            = sText_TrainerBlockedBall,
    [STRINGID_DONTBEATHIEF]                  = sText_DontBeAThief,
    [STRINGID_ITDODGEDBALL]                  = sText_ItDodgedBall,
    [STRINGID_YOUMISSEDPKMN]                 = sText_YouMissedPkmn,
    [STRINGID_PKMNBROKEFREE]                 = sText_PkmnBrokeFree,
    [STRINGID_ITAPPEAREDCAUGHT]              = sText_ItAppearedCaught,
    [STRINGID_AARGHALMOSTHADIT]              = sText_AarghAlmostHadIt,
    [STRINGID_SHOOTSOCLOSE]                  = sText_ShootSoClose,
    [STRINGID_GOTCHAPKMNCAUGHT]              = sText_GotchaPkmnCaught,
    [STRINGID_GOTCHAPKMNCAUGHT2]             = sText_GotchaPkmnCaught2,
    [STRINGID_GIVENICKNAMECAPTURED]          = sText_GiveNicknameCaptured,
    [STRINGID_PKMNSENTTOPC]                  = COMPOUND_STRING("{B_DEF_NAME} was sent to\n{B_PC_CREATOR_NAME} PC."),
    [STRINGID_PKMNDATAADDEDTODEX]            = sText_PkmnDataAddedToDex,
    [STRINGID_ITISRAINING]                   = sText_ItIsRaining,
    [STRINGID_SANDSTORMISRAGING]             = sText_SandstormIsRaging,
    [STRINGID_CANTESCAPE2]                   = sText_CantEscape2,
    [STRINGID_PKMNIGNORESASLEEP]             = sText_PkmnIgnoresAsleep,
    [STRINGID_PKMNIGNOREDORDERS]             = sText_PkmnIgnoredOrders,
    [STRINGID_PKMNBEGANTONAP]                = sText_PkmnBeganToNap,
    [STRINGID_PKMNLOAFING]                   = sText_PkmnLoafing,
    [STRINGID_PKMNWONTOBEY]                  = sText_PkmnWontObey,
    [STRINGID_PKMNTURNEDAWAY]                = sText_PkmnTurnedAway,
    [STRINGID_PKMNPRETENDNOTNOTICE]          = sText_PkmnPretendNotNotice,
    [STRINGID_ENEMYABOUTTOSWITCHPKMN]        = sText_EnemyAboutToSwitchPkmn,
    [STRINGID_THREWROCK]                     = sText_ThrewARock,
    [STRINGID_THREWBAIT]                     = sText_ThrewSomeBait,
    [STRINGID_PKMNWATCHINGCAREFULLY]         = sText_PkmnWatchingCarefully,
    [STRINGID_PKMNANGRY]                     = sText_PkmnIsAngry,
    [STRINGID_PKMNEATING]                    = sText_PkmnIsEating,
    [STRINGID_DUMMY288]                      = sText_Empty1,
    [STRINGID_DUMMY289]                      = sText_Empty1,
    [STRINGID_OUTOFSAFARIBALLS]              = sText_OutOfSafariBalls,
    [STRINGID_PKMNSITEMCUREDPARALYSIS]       = sText_PkmnsItemCuredParalysis,
    [STRINGID_PKMNSITEMCUREDPOISON]          = sText_PkmnsItemCuredPoison,
    [STRINGID_PKMNSITEMHEALEDBURN]           = sText_PkmnsItemHealedBurn,
    [STRINGID_PKMNSITEMDEFROSTEDIT]          = sText_PkmnsItemDefrostedIt,
    [STRINGID_PKMNSITEMWOKEIT]               = sText_PkmnsItemWokeIt,
    [STRINGID_PKMNSITEMSNAPPEDOUT]           = sText_PkmnsItemSnappedOut,
    [STRINGID_PKMNSITEMCUREDPROBLEM]         = sText_PkmnsItemCuredProblem,
    [STRINGID_PKMNSITEMRESTOREDHEALTH]       = sText_PkmnsItemRestoredHealth,
    [STRINGID_PKMNSITEMRESTOREDPP]           = sText_PkmnsItemRestoredPP,
    [STRINGID_PKMNSITEMRESTOREDSTATUS]       = sText_PkmnsItemRestoredStatus,
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE]    = sText_PkmnsItemRestoredHPALittle,
    [STRINGID_ITEMALLOWSONLYYMOVE]           = sText_ItemAllowsOnlyYMove,
    [STRINGID_PKMNHUNGONWITHX]               = sText_PkmnHungOnWithX,
    [STRINGID_EMPTYSTRING3]                  = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS]           = sText_PkmnsXPreventsBurns,
    [STRINGID_PKMNSXBLOCKSY]                 = sText_PkmnsXBlocksY,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2]      = sText_PkmnsXRestoredHPALittle2,
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM]      = sText_PkmnsXWhippedUpSandstorm,
    [STRINGID_PKMNSXPREVENTSYLOSS]           = sText_PkmnsXPreventsYLoss,
    [STRINGID_PKMNSXINFATUATEDY]             = sText_PkmnsXInfatuatedY,
    [STRINGID_PKMNSXMADEYINEFFECTIVE]        = sText_PkmnsXMadeYIneffective,
    [STRINGID_PKMNSXCUREDYPROBLEM]           = sText_PkmnsXCuredYProblem,
    [STRINGID_ITSUCKEDLIQUIDOOZE]            = sText_ItSuckedLiquidOoze,
    [STRINGID_PKMNTRANSFORMED]               = sText_PkmnTransformed,
    [STRINGID_ELECTRICITYWEAKENED]           = sText_ElectricityWeakened,
    [STRINGID_FIREWEAKENED]                  = sText_FireWeakened,
    [STRINGID_PKMNHIDUNDERWATER]             = sText_PkmnHidUnderwater,
    [STRINGID_PKMNSPRANGUP]                  = sText_PkmnSprangUp,
    [STRINGID_HMMOVESCANTBEFORGOTTEN]        = sText_HMMovesCantBeForgotten,
    [STRINGID_XFOUNDONEY]                    = sText_XFoundOneY,
    [STRINGID_PLAYERDEFEATEDTRAINER1]        = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA]                 = sText_SoothingAroma,
    [STRINGID_ITEMSCANTBEUSEDNOW]            = sText_ItemsCantBeUsedNow,
    [STRINGID_FORXCOMMAYZ]                   = sText_ForXCommaYZ,
    [STRINGID_USINGXTHEYOFZN]                = sText_UsingXTheYOfZN,
    [STRINGID_PKMNUSEDXTOGETPUMPED]          = sText_PkmnUsedXToGetPumped,
    [STRINGID_PKMNSXMADEYUSELESS]            = sText_PkmnsXMadeYUseless,
    [STRINGID_PKMNTRAPPEDBYSANDTOMB]         = sText_PkmnTrappedBySandTomb,
    [STRINGID_EMPTYSTRING4]                  = sText_EmptyString4,
    [STRINGID_ABOOSTED]                      = sText_ABoosted,
    [STRINGID_PKMNSXINTENSIFIEDSUN]          = sText_PkmnsXIntensifiedSun,
    [STRINGID_PKMNMAKESGROUNDMISS]           = sText_PkmnMakesGroundMiss,
    [STRINGID_YOUTHROWABALLNOWRIGHT]         = sText_YouThrowABallNowRight,
    [STRINGID_PKMNSXTOOKATTACK]              = sText_PkmnsXTookAttack,
    [STRINGID_PKMNCHOSEXASDESTINY]           = sText_PkmnChoseXAsDestiny,
    [STRINGID_PKMNLOSTFOCUS]                 = sText_PkmnLostFocus,
    [STRINGID_USENEXTPKMN]                   = sText_UseNextPkmn,
    [STRINGID_PKMNFLEDUSINGITS]              = sText_PkmnFledUsingIts,
    [STRINGID_PKMNFLEDUSING]                 = sText_PkmnFledUsing,
    [STRINGID_PKMNWASDRAGGEDOUT]             = sText_PkmnWasDraggedOut,
    [STRINGID_PREVENTEDFROMWORKING]          = sText_PreventedFromWorking,
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS]     = sText_PkmnsItemNormalizedStatus,
    [STRINGID_TRAINER1USEDITEM]              = sText_Trainer1UsedItem,
    [STRINGID_BOXISFULL]                     = sText_BoxIsFull,
    [STRINGID_PKMNAVOIDEDATTACK]             = sText_PkmnAvoidedAttack,
    [STRINGID_PKMNSXMADEITINEFFECTIVE]       = sText_PkmnsXMadeItIneffective,
    [STRINGID_PKMNSXPREVENTSFLINCHING]       = sText_PkmnsXPreventsFlinching,
    [STRINGID_PKMNALREADYHASBURN]            = sText_PkmnAlreadyHasBurn,
    [STRINGID_STATSWONTDECREASE2]            = sText_StatsWontDecrease2,
    [STRINGID_PKMNSXBLOCKSY2]                = sText_PkmnsXBlocksY2,
    [STRINGID_PKMNSXWOREOFF]                 = sText_PkmnsXWoreOff,
    [STRINGID_PKMNRAISEDDEFALITTLE]          = sText_PkmnRaisedDefALittle,
    [STRINGID_PKMNRAISEDSPDEFALITTLE]        = sText_PkmnRaisedSpDefALittle,
    [STRINGID_THEWALLSHATTERED]              = sText_TheWallShattered,
    [STRINGID_PKMNSXPREVENTSYSZ]             = sText_PkmnsXPreventsYsZ,
    [STRINGID_PKMNSXCUREDITSYPROBLEM]        = sText_PkmnsXCuredItsYProblem,
    [STRINGID_ATTACKERCANTESCAPE]            = sText_AttackerCantEscape,
    [STRINGID_PKMNOBTAINEDX]                 = sText_PkmnObtainedX,
    [STRINGID_PKMNOBTAINEDX2]                = sText_PkmnObtainedX2,
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ]       = sText_PkmnObtainedXYObtainedZ,
    [STRINGID_BUTNOEFFECT]                   = sText_ButNoEffect,
    [STRINGID_PKMNSXHADNOEFFECTONY]          = sText_PkmnsXHadNoEffectOnY,
    [STRINGID_OAKPLAYERWON]                  = gText_WinEarnsPrizeMoney,
    [STRINGID_OAKPLAYERLOST]                 = gText_HowDissapointing,
    [STRINGID_PLAYERLOSTAGAINSTENEMYTRAINER] = sText_PlayerWhiteoutAgainstTrainer,
    [STRINGID_PLAYERPAIDPRIZEMONEY]          = sText_PlayerPaidAsPrizeMoney,
    [STRINGID_PKMNTRANSFERREDSOMEONESPC]     = Text_MonSentToBoxInSomeonesPC,
    [STRINGID_PKMNTRANSFERREDBILLSPC]        = Text_MonSentToBoxInBillsPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL]         = Text_MonSentToBoxSomeonesBoxFull,
    [STRINGID_PKMNBOXBILLSPCFULL]            = Text_MonSentToBoxBillsBoxFull,
    [STRINGID_POKEDUDEUSED]                  = sText_PokedudeUsedItem,
    [STRINGID_POKEFLUTECATCHY]               = sText_PlayedFluteCatchyTune,
    [STRINGID_POKEFLUTE]                     = sText_PlayedThe,
    [STRINGID_MONHEARINGFLUTEAWOKE]          = sText_PkmnHearingFluteAwoke,
    [STRINGID_PKMNSXCALLEDDOWNHAIL]          = sText_PkmnsXCalledDownHail,
    [STRINGID_POKEMONBLOCKEDBALL]            = sText_PokemonBlockedBall, //
    [STRINGID_NEUTRALIZINGGASENTERS]         = sText_NeutralizingGasEnters,
    [STRINGID_NEUTRALIZINGGASOVER]           = sText_NeutralizingGasOver, //new values below
    [STRINGID_INFESTATION]                   = sText_Infestation,
    [STRINGID_ENDUREDSTURDY]                 = sText_EnduredViaSturdy,
    [STRINGID_POWERHERB]                     = sText_PowerHerbActivation,
    [STRINGID_HURTBYITEM]                    = sText_HurtByItem,
    [STRINGID_PSNBYITEM]                     = sText_BadlyPoisonedByItem,
    [STRINGID_BRNBYITEM]                     = sText_BurnedByItem,
    [STRINGID_DEFABILITYIN]                  = sText_TargetAbilityActivates,
    [STRINGID_GRAVITYINTENSIFIED]            = sText_GravityIntensified,
    [STRINGID_TARGETIDENTIFIED]              = sText_TargetIdentified,
    [STRINGID_TARGETWOKEUP]                  = sText_TargetWokeUp,
    [STRINGID_PKMNSTOLEANDATEITEM]           = sText_PkmnStoleAndAteItem,
    [STRINGID_TAILWINDBLEW]                  = sText_TailWindBlew,
    [STRINGID_PKMNWENTBACK]                  = sText_PkmnWentBack,
    [STRINGID_PKMNCANTUSEITEMSANYMORE]       = sText_PkmnCantUseItemsAnymore,
    [STRINGID_PKMNFLUNG]                     = sText_PkmnFlung,
    [STRINGID_PKMNPREVENTEDFROMHEALING]      = sText_PkmnPreventedFromHealing,
    [STRINGID_PKMNSWITCHEDATKANDDEF]         = sText_PkmnSwitchedAtkAndDef,
    [STRINGID_PKMNSABILITYSUPPRESSED]        = sText_PkmnsAbilitySuppressed,
    [STRINGID_SHIELDEDFROMCRITICALHITS]      = sText_ShieldedFromCriticalHits,
    [STRINGID_SWITCHEDATKANDSPATK]           = sText_SwitchedAtkAndSpAtk,
    [STRINGID_SWITCHEDDEFANDSPDEF]           = sText_SwitchedDefAndSpDef,
    [STRINGID_PKMNACQUIREDABILITY]           = sText_PkmnAcquiredAbility,
    [STRINGID_POISONSPIKESSCATTERED]         = sText_PoisonSpikesScattered,
    [STRINGID_PKMNSWITCHEDSTATCHANGES]       = sText_PkmnSwitchedStatChanges,
    [STRINGID_PKMNSURROUNDEDWITHVEILOFWATER] = sText_PkmnSurroundedWithVeilOfWater,
    [STRINGID_PKMNLEVITATEDONELECTROMAGNETISM] = sText_PkmnLevitatedOnElectromagnetism,
    [STRINGID_PKMNTWISTEDDIMENSIONS]         = sText_PkmnTwistedDimensions,
    [STRINGID_POINTEDSTONESFLOAT]            = sText_PointedStonesFloat,
    [STRINGID_CLOAKEDINMYSTICALMOONLIGHT]    = sText_CloakedInMysticalMoonlight,
    [STRINGID_TRAPPEDBYSWIRLINGMAGMA]        = sText_TrappedBySwirlingMagma,
    [STRINGID_VANISHEDINSTANTLY]             = sText_VanishedInstantly,
    [STRINGID_PROTECTEDTEAM]                 = sText_ProtectedTeam,
    [STRINGID_SHAREDITSGUARD]                = sText_SharedItsGuard,
    [STRINGID_SHAREDITSPOWER]                = sText_SharedItsPower,
    [STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON] = sText_SwapsDefAndSpDefOfAllPkmn,
    [STRINGID_BECAMENIMBLE]                  = sText_BecameNimble,
    [STRINGID_HURLEDINTOTHEAIR]              = sText_HurledIntoTheAir,
    [STRINGID_HELDITEMSLOSEEFFECTS]          = sText_HeldItemsLoseEffects,
    [STRINGID_FELLSTRAIGHTDOWN]              = sText_FellStraightDown,
    [STRINGID_TRANSFORMEDINTOWATERTYPE]      = sText_TransformedIntoWaterType,
    [STRINGID_PKMNACQUIREDSIMPLE]            = sText_PkmnAcquiredSimple,
    [STRINGID_EMPTYSTRING5]                  = sText_EmptyString4,
    [STRINGID_KINDOFFER]                     = sText_KindOffer,
    [STRINGID_RESETSTARGETSSTATLEVELS]       = sText_ResetsTargetsStatLevels,
    [STRINGID_EMPTYSTRING6]                  = sText_EmptyString4,
    [STRINGID_ALLYSWITCHPOSITION]            = sText_AllySwitchPosition,
    [STRINGID_RESTORETARGETSHEALTH]          = sText_RestoreTargetsHealth,
    [STRINGID_TOOKPKMNINTOTHESKY]            = sText_TookPkmnIntoTheSky,
    [STRINGID_FREEDFROMSKYDROP]              = sText_FreedFromSkyDrop,
    [STRINGID_POSTPONETARGETMOVE]            = sText_PostponeTargetMove,
    [STRINGID_REFLECTTARGETSTYPE]            = sText_ReflectTargetsType,
    [STRINGID_TRANSFERHELDITEM]              = sText_TransferHeldItem,
    [STRINGID_EMBARGOENDS]                   = sText_EmbargoEnds,
    [STRINGID_ELECTROMAGNETISM]              = sText_Electromagnetism,
    [STRINGID_BUFFERENDS]                    = sText_BufferEnds,
    [STRINGID_TELEKINESISENDS]               = sText_TelekinesisEnds,
    [STRINGID_TAILWINDENDS]                  = sText_TailwindEnds,
    [STRINGID_LUCKYCHANTENDS]                = sText_LuckyChantEnds,
    [STRINGID_TRICKROOMENDS]                 = sText_TrickRoomEnds,
    [STRINGID_WONDERROOMENDS]                = sText_WonderRoomEnds,
    [STRINGID_MAGICROOMENDS]                 = sText_MagicRoomEnds,
    [STRINGID_MUDSPORTENDS]                  = sText_MudSportEnds,
    [STRINGID_WATERSPORTENDS]                = sText_WaterSportEnds,
    [STRINGID_GRAVITYENDS]                   = sText_GravityEnds,
    [STRINGID_AQUARINGHEAL]                  = sText_AquaRingHeal,
    [STRINGID_AURORAVEILENDS]                = sText_AuroraVeilEnds,
    [STRINGID_ELECTRICTERRAINENDS]           = sText_ElectricTerrainEnds,
    [STRINGID_MISTYTERRAINENDS]              = sText_MistyTerrainEnds,
    [STRINGID_PSYCHICTERRAINENDS]            = sText_PsychicTerrainEnds,
    [STRINGID_GRASSYTERRAINENDS]             = sText_GrassyTerrainEnds,
    [STRINGID_TARGETABILITYSTATRAISE]        = sText_TargetAbilityRaisedStat,
    [STRINGID_TARGETSSTATWASMAXEDOUT]        = sText_TargetsStatWasMaxedOut,
    [STRINGID_ATTACKERABILITYSTATRAISE]      = sText_AttackerAbilityRaisedStat,
    [STRINGID_POISONHEALHPUP]                = sText_PoisonHealHpUp,
    [STRINGID_BADDREAMSDMG]                  = sText_BadDreamsDmg,
    [STRINGID_MOLDBREAKERENTERS]             = sText_MoldBreakerEnters,
    [STRINGID_TERAVOLTENTERS]                = sText_TeravoltEnters,
    [STRINGID_TURBOBLAZEENTERS]              = sText_TurboblazeEnters,
    [STRINGID_SLOWSTARTENTERS]               = sText_SlowStartEnters,
    [STRINGID_SLOWSTARTEND]                  = sText_SlowStartEnd,
    [STRINGID_SOLARPOWERHPDROP]              = sText_SolarPowerHpDrop,
    [STRINGID_AFTERMATHDMG]                  = sText_AftermathDmg,
    [STRINGID_ANTICIPATIONACTIVATES]         = sText_AnticipationActivates,
    [STRINGID_FOREWARNACTIVATES]             = sText_ForewarnActivates,
    [STRINGID_ICEBODYHPGAIN]                 = sText_IceBodyHpGain,
    [STRINGID_SNOWWARNINGHAIL]               = sText_SnowWarningHail,
    [STRINGID_FRISKACTIVATES]                = sText_FriskActivates,
    [STRINGID_UNNERVEENTERS]                 = sText_UnnerveEnters,
    [STRINGID_HARVESTBERRY]                  = sText_HarvestBerry,
    [STRINGID_LASTABILITYRAISEDSTAT]         = sText_MoxieAtkRise,
    [STRINGID_MAGICBOUNCEACTIVATES]          = sText_MagicBounceActivates,
    [STRINGID_PROTEANTYPECHANGE]             = sText_ProteanTypeChange,
    [STRINGID_SYMBIOSISITEMPASS]             = sText_SymbiosisItemPass,
    [STRINGID_STEALTHROCKDMG]                = sText_StealthRockDmg,
    [STRINGID_TOXICSPIKESABSORBED]           = sText_ToxicSpikesAbsorbed,
    [STRINGID_TOXICSPIKESPOISONED]           = sText_ToxicSpikesPoisoned,
    [STRINGID_STICKYWEBSWITCHIN]             = sText_StickyWebSwitchIn,
    [STRINGID_HEALINGWISHCAMETRUE]           = sText_HealingWishCameTrue,
    [STRINGID_HEALINGWISHHEALED]             = sText_HealingWishHealed,
    [STRINGID_LUNARDANCECAMETRUE]            = sText_LunarDanceCameTrue,
    [STRINGID_CUSEDBODYDISABLED]             = sText_CursedBodyDisabled,
    [STRINGID_ATTACKERACQUIREDABILITY]       = sText_AttackerAquiredAbility,
    [STRINGID_TARGETABILITYSTATLOWER]        = sText_TargetAbilityLoweredStat,
    [STRINGID_TARGETSTATWONTGOHIGHER]        = sText_TargetStatWontGoHigher,
    [STRINGID_PKMNMOVEBOUNCEDABILITY]        = sText_PkmnMoveBouncedViaAbility,
    [STRINGID_IMPOSTERTRANSFORM]             = sText_ImposterTransform,
    [STRINGID_ASSAULTVESTDOESNTALLOW]        = sText_AssaultVestDoesntAllow,
    [STRINGID_GRAVITYPREVENTSUSAGE]          = sText_GravityPreventsUsage,
    [STRINGID_HEALBLOCKPREVENTSUSAGE]        = sText_HealBlockPreventsUsage,
    [STRINGID_NOTDONEYET]                    = COMPOUND_STRING("Not Done Yet"),
    [STRINGID_STICKYWEBUSED]                 = sText_StickyWebUsed,
    [STRINGID_QUASHSUCCESS]                  = sText_QuashSuccess,
    [STRINGID_PKMNBLEWAWAYTOXICSPIKES]       = sText_PkmnBlewAwayToxicSpikes,
    [STRINGID_PKMNBLEWAWAYSTICKYWEB]         = sText_PkmnBlewAwayStickyWeb,
    [STRINGID_PKMNBLEWAWAYSTEALTHROCK]       = sText_PkmnBlewAwayStealthRock,
    [STRINGID_IONDELUGEON]                   = sText_IonDelugeOn,
    [STRINGID_TOPSYTURVYSWITCHEDSTATS]       = sText_TopsyTurvySwitchedStats,
    [STRINGID_TERRAINBECOMESMISTY]           = sText_TerrainBecomesMisty,
    [STRINGID_TERRAINBECOMESGRASSY]          = sText_TerrainBecomesGrassy,
    [STRINGID_TERRAINBECOMESELECTRIC]        = sText_TerrainBecomesElectric,
    [STRINGID_TERRAINBECOMESPSYCHIC]         = sText_TerrainBecomesPsychic,
    [STRINGID_TARGETELECTRIFIED]             = sText_TargetElectrified,
    [STRINGID_MEGAEVOREACTING]               = sText_MegaEvoReacting,
    [STRINGID_MEGAEVOEVOLVED]                = sText_MegaEvoEvolved,    
    [STRINGID_DRASTICALLY]                   = sText_drastically,
    [STRINGID_SEVERELY]                      = sText_severely,
    [STRINGID_NOEFFECTONTARGET]              = sText_NoEffectOnTarget,
    [STRINGID_BURSTINGFLAMESHIT]             = sText_BurstingFlames,
    [STRINGID_BESTOWITEMGIVING]              = sText_BestowItemGiving,
    [STRINGID_THIRDTYPEADDED]                = sText_ThirdTypeAdded,
    [STRINGID_FELLFORFEINT]                  = sText_FellForFeint,
    [STRINGID_POKEMONCANNOTUSEMOVE]          = sText_PokemonCannotUseMove,
    [STRINGID_COVEREDINPOWDER]               = sText_CoveredInPowder,
    [STRINGID_POWDEREXPLODES]                = sText_PowderExplodes,
    [STRINGID_BELCHCANTSELECT]               = sText_BelchCantUse,
    [STRINGID_SPECTRALTHIEFSTEAL]            = sText_SpectralThiefSteal,
    [STRINGID_GRAVITYGROUNDING]              = sText_GravityGrounding,
    [STRINGID_MISTYTERRAINPREVENTS]          = sText_MistyTerrainPreventsStatus,
    [STRINGID_GRASSYTERRAINHEALS]            = sText_GrassyTerrainHeals,
    [STRINGID_ELECTRICTERRAINPREVENTS]       = sText_ElectricTerrainPreventsSleep,
    [STRINGID_PSYCHICTERRAINPREVENTS]        = sText_PsychicTerrainPreventsPriority,
    [STRINGID_SAFETYGOGGLESPROTECTED]        = sText_SafetyGooglesProtected,
    [STRINGID_FLOWERVEILPROTECTED]           = sText_FlowerVeilProtected,
    [STRINGID_SWEETVEILPROTECTED]            = sText_SweetVeilProtected,
    [STRINGID_AROMAVEILPROTECTED]            = sText_AromaVeilProtected,
    [STRINGID_CELEBRATEMESSAGE]              = sText_CelebrateMessage,
    [STRINGID_USEDINSTRUCTEDMOVE]            = sText_UsedInstructedMove,
    [STRINGID_THROATCHOPENDS]                = sText_ThroatChopEnds,
    [STRINGID_PKMNCANTUSEMOVETHROATCHOP]     = sText_PkmnCantUseMoveThroatChop,    
    [STRINGID_LASERFOCUS]                    = sText_LaserFocusMessage,
    [STRINGID_GEMACTIVATES]                  = sText_GemActivates,
    [STRINGID_BERRYDMGREDUCES]               = sText_BerryDmgReducing,
    [STRINGID_TARGETATEITEM]                 = sText_TargetAteItem,
    [STRINGID_AIRBALLOONFLOAT]               = sText_AirBalloonFloat,
    [STRINGID_AIRBALLOONPOP]                 = sText_AirBalloonPop,
    [STRINGID_INCINERATEBURN]                = sText_IncinerateBurn,
    [STRINGID_BUGBITE]                       = sText_BugBite,
    [STRINGID_ILLUSIONWOREOFF]               = sText_IllusionWoreOff,
    [STRINGID_ATTACKERCUREDTARGETSTATUS]     = sText_AttackerCuredTargetStatus,
    [STRINGID_ATTACKERLOSTTYPE]              = sText_AttackerLostType,
    [STRINGID_HEALERCURE]                    = sText_HealerCure,
    [STRINGID_SCRIPTINGABILITYSTATRAISE]     = sText_ScriptingAbilityRaisedStat,
    [STRINGID_RECEIVERABILITYTAKEOVER]       = sText_ReceiverAbilityTakeOver,
    [STRINGID_PKNMABSORBINGPOWER]            = sText_PkmnAbsorbingPower,
    [STRINGID_NOONEWILLBEABLETORUNAWAY]      = sText_NoOneWillBeAbleToRun,
    [STRINGID_DESTINYKNOTACTIVATES]          = sText_DestinyKnotActivates,
    [STRINGID_CLOAKEDINAFREEZINGLIGHT]       = sText_CloakedInAFreezingLight,
    [STRINGID_STATWASNOTLOWERED]             = sText_StatWasNotLowered,
    [STRINGID_FERVENTWISHREACHED]            = sText_FerventWishReached,
    [STRINGID_AIRLOCKACTIVATES]              = sText_AirLockActivates,
    [STRINGID_PRESSUREENTERS]                = sText_PressureActivates,
    [STRINGID_DARKAURAENTERS]                = sText_DarkAuraActivates,
    [STRINGID_FAIRYAURAENTERS]               = sText_FairyAuraActivates,
    [STRINGID_AURABREAKENTERS]               = sText_AuraBreakActivates,
    [STRINGID_COMATOSEENTERS]                = sText_ComatoseActivates,
    [STRINGID_SCREENCLEANERENTERS]           = sText_ScreenCleanerActivates,
    [STRINGID_FETCHEDPOKEBALL]               = sText_FetchedPokeBall,
    [STRINGID_BATTLERABILITYRAISEDSTAT]      = sText_BattlerAbilityRaisedStat,
    [STRINGID_ASANDSTORMKICKEDUP]            = sText_ASandstormKickedUp,
    [STRINGID_PKMNSWILLPERISHIN3TURNS]       = sText_PkmnsWillPerishIn3Turns,
    [STRINGID_ABILITYRAISEDSTATDRASTICALLY]  = sText_AbilityRaisedStatDrastically,  
    [STRINGID_AURAFLAREDTOLIFE]              = sText_AuraFlaredToLife,

        [STRINGID_ASONEENTERS] = sText_AsOneEnters,
        [STRINGID_CURIOUSMEDICINEENTERS] = sText_CuriousMedicineEnters,
        [STRINGID_CANACTFASTERTHANKSTO] = sText_CanActFaster,
        [STRINGID_MICLEBERRYACTIVATES] = sText_MicleBerryActivates,
        [STRINGID_PKMNSHOOKOFFTHETAUNT] = sText_PkmnShookOffTheTaunt,
        [STRINGID_PKMNGOTOVERITSINFATUATION] = sText_PkmnGotOverItsInfatuation,
        [STRINGID_ITEMCANNOTBEREMOVED] = sText_ItemCannotBeRemoved,
        [STRINGID_STICKYBARBTRANSFER] = sText_StickyBarbTransfer,
        [STRINGID_PKMNBURNHEALED] = sText_PkmnBurnHealed,
        [STRINGID_REDCARDACTIVATE] = sText_RedCardActivate,
        [STRINGID_EJECTBUTTONACTIVATE] = sText_EjectButtonActivate,
        [STRINGID_ATKGOTOVERINFATUATION] = sText_AttackerGotOverInfatuation,
        [STRINGID_TORMENTEDNOMORE] = sText_TormentedNoMore,
        [STRINGID_HEALBLOCKEDNOMORE] = sText_HealBlockedNoMore,
        [STRINGID_ATTACKERBECAMEFULLYCHARGED] = sText_AttackerBecameFullyCharged,
        [STRINGID_ATTACKERBECAMEASHSPECIES] = sText_AttackerBecameAshSpecies,
        [STRINGID_EXTREMELYHARSHSUNLIGHT] = sText_ExtremelyHarshSunlight,
        [STRINGID_EXTREMESUNLIGHTFADED] = sText_ExtremeSunlightFaded,
        [STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT] = sText_MoveEvaporatedInTheHarshSunlight,
        [STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED] = sText_ExtremelyHarshSunlightWasNotLessened,
        [STRINGID_HEAVYRAIN] = sText_HeavyRain,
        [STRINGID_HEAVYRAINLIFTED] = sText_HeavyRainLifted,
        [STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN] = sText_MoveFizzledOutInTheHeavyRain,
        [STRINGID_NORELIEFROMHEAVYRAIN] = sText_NoReliefFromHeavyRain,
        [STRINGID_MYSTERIOUSAIRCURRENT] = sText_MysteriousAirCurrent,
        [STRINGID_STRONGWINDSDISSIPATED] = sText_StrongWindsDissipated,
        [STRINGID_MYSTERIOUSAIRCURRENTBLOWSON] = sText_MysteriousAirCurrentBlowsOn,
        [STRINGID_ATTACKWEAKENEDBYSTRONGWINDS] = sText_AttackWeakenedByStrongWinds,
        [STRINGID_STUFFCHEEKSCANTSELECT] = sText_StuffCheeksCantSelect,
        [STRINGID_PKMNREVERTEDTOPRIMAL] = sText_PkmnRevertedToPrimal,
        [STRINGID_BUTPOKEMONCANTUSETHEMOVE] = sText_ButPokemonCantUseTheMove,
        [STRINGID_BUTHOOPACANTUSEIT] = sText_ButHoopaCantUseIt,
        [STRINGID_BROKETHROUGHPROTECTION] = sText_BrokeThroughProtection,
        [STRINGID_ABILITYALLOWSONLYMOVE] = sText_AbilityAllowsOnlyMove,
        [STRINGID_SWAPPEDABILITIES] = sText_SwappedAbilities,
        [STRINGID_PASTELVEILPROTECTED] = sText_PastelVeilProtected,
        [STRINGID_PASTELVEILENTERS] = sText_PastelVeilEnters,
        [STRINGID_BATTLERTYPECHANGEDTO] = sText_BattlerTypeChangedTo,
        [STRINGID_BOTHCANNOLONGERESCAPE] = sText_BothCanNoLongerEscape,
        [STRINGID_CANTESCAPEDUETOUSEDMOVE] = sText_CantEscapeDueToUsedMove,
        [STRINGID_PKMNBECAMEWEAKERTOFIRE] = sText_PkmnBecameWeakerToFire,
        [STRINGID_ABOUTTOUSEPOLTERGEIST] = sText_PkmnAboutToBeAttackedByItsItem,
        [STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE] = sText_CantEscapeBecauseOfCurrentMove,
        [STRINGID_TARGETTOOHEAVY] = sText_TargetTooHeavy,
        [STRINGID_PKMNTOOKTARGETHIGH] = sText_PkmnTookTargetHigh,        
    [STRINGID_CUPIDSARROWSTRUCK]             = sText_FellInLoveAtFirstSight,
    [STRINGID_PKMNALREADYFROZEN]             = sText_PkmnWasAlreadyFrozen,
    [STRINGID_SNAPTRAP]                      = sText_SnapTrap,
    [STRINGID_PKMNSTOPPEDROOSTING]           = sText_PkmnRoostEnds,
    [STRINGID_CONFIRMFORGETMOVE]             = sText_ConfirmForgetMove,
    [STRINGID_TERRAINBECOMESFIRE]            = sText_TerrainBecomesScorched,
    [STRINGID_TERRAINBECOMESWATER]           = sText_TerrainBecomesFlooded,
    [STRINGID_TERRAINBECOMESDEEPWATER]       = sText_TerrainBecomesOceanic,
    [STRINGID_CRASHEDTOTHEGROUND]            = sText_FlyingEnemyCrashedDown,
    [STRINGID_DEFEATISTACTIVATED]            = sText_DefeatistActivates,
    [STRINGID_PKMNHURTBYFROSTBITE]           = sText_PkmnHurtByFrostbite,
    [STRINGID_IRONWILL_ATKCANCEL]             = sText_IronWill_AtkCancel,
    [STRINGID_STEALTHROCKABROSBED]           = sText_StealthRockAbsorbed,
    [STRINGID_PICKUP_ITEM]                   = sText_Battle_Pickup,
    [STRINGID_TIGER_MOM_ACTIVATES]          = sText_TigerMomActivation,
    [STRINGID_DEFROST_POKEMON]               = sText_PkmnDefrosted,
    [STRINGID_CORRUPTIONENTERS]              = sText_CorruptionActivates,
    [STRINGID_BANDITENTERS]                  = sText_BanditActivates,
    [STRINGID_ANTICIPATE_EXPLOSION]          = sText_AnticipateExplosion,
    [STRINGID_ANTICIPATE_OHKO]               = sText_AnticipateOHKO,
    [STRINGID_ANTICIPATE_DEFAULT]            = sText_AnticipateDefault,
    [STRINGID_SPITE_BADLUCK]                 = sText_SpiteBadLuck,
    [STRINGID_SPITE_TOTAL_LOSS]              = sText_SpiteTotalLoss,
    [STRINGID_PKMNSPOISONWORSENED]           = sText_PkmnsPoisonWorsened,
    [STRINGID_STENCHENTERS]                  = sText_StenchEnters,
    [STRINGID_STENCHENDS]                    = sText_StenchExits,
    [STRINGID_WELLRESTED]                    = sText_PkmnWellRested,
    [STRINGID_PKMNHURTSWITH2]                = sText_PkmnHurtsWith2,
    [STRINGID_PKMNSABILITYPREVENTSABILITY]   = sText_PkmnsAbilityPreventsAbility,
    [STRINGID_STICKYHOLDABSORBEDITEM]        = sText_StickyHoldAbsorb,
    [STRINGID_METEORBEAMCHARGING]            = sText_MeteorBeamCharging,
    [STRINGID_HEATUPBEAK]                    = sText_HeatingUpBeak,
    [STRINGID_EMPATHIC_CURSE_ACTIVATES]      = sText_PkmnHurtEmpathCurse,
    [STRINGID_ATTACKER_STURDY]               = sText_AttackerEnduredViaSturdy,
    [STRINGID_TARGETSXWHIPPEDUPSANDSTORM]    = sText_TargetsXWhippedUpSandstorm,
    [STRINGID_ATTACKER_ABILITYHURTS_TARGET]  = sText_AttackerHurtsPkmnWith,
    [STRINGID_PKMNINFESTED]                  = sText_Infested,
    [STRINGID_PKMNPANICKED]                  = sText_PkmnPanicked,
    [STRINGID_ABILITYNULLIFYTYPEDAMAGE]      = sText_PkmnNullifyTypeViaAbility,
    [STRINGID_CAUGHTMONDROPPEDITEM]          = sText_ReceiveditemfromCaughtMon,
    [STRINGID_MONROOSTING]                   = sText_PkmnRoosting,
    [STRINGID_ATK_RAGEBUILDING]              = sText_AttackerRageBuilding,
    [STRINGID_ATK_RAGEABATED]                = sText_AttackerRageEnded,
    [STRINGID_BIND_NO_PP]                    = sText_BindMoveOutofPP, 
    [STRINGID_FEMME_FATALE]                  = sText_FemmeFataleBlocks,
    [STRINGID_ABILITY_LOSTRESOLVE]           = sText_Ability_LostResolve,
    [STRINGID_AURA_OF_LIGHT_AWOKE]           = sText_AuraofLightAwaken,
    [STRINGID_PKMNMOVESEALEDNOMORE]         = sText_PkmnInthralledNoMore,
    [STRINGID_PKMNMOVESEALED]              = sText_PkmnIsInthralled,
    [STRINGID_ATEBERRY]                    = sText_BelchEatBerry,
    [STRINGID_PHOENIX_CLEANSE]             = sText_PhoenixCleanse,  
    [STRINGID_PLAYER_FOREWARN]             = sText_PlayerForewarn,
    [STRINGID_ENEMY_FOREAWRN]              = sText_EnemyForewarn, 
    [STRINGID_PLAYER_ALERT]                = sText_PlayerForewarnalert,
    [SRINGID_ENEMY_ALERT]                  = sText_EnemyForewarnalert,
    [STRINGID_ANTICIPATE_STRONG_MOVE]      = sText_AnticipateStrongestMove,
    [STRINGID_FORECAST_BLIZZARD]           = sText_ForecastBlizzard,
    [STRINGID_FORECAST_DUST_STORM]         = sText_ForecastDuststorm,
    [STRINGID_FORECAST_HEATWAVE]           = sText_ForecastHeatwave,
    [STRINGID_FORECAST_TORRENTIAL_RAIN]    = sText_ForecastTorrentialrain,
    [STRINGID_FORECAST_SANDSTORM]          = sText_ForecastSandstorm,
    [STRINGID_FORECAST_HAIL]               = sText_ForecastHail,
    [STRINGID_FORECAST_RAIN]               = sText_ForecastRain,
    [STRINGID_FORECAST_SUNNY]              = sText_ForecastSunny,
    [STRINGID_FORECAST_PREDICTION]         = sText_ForecastPrediction,
    [STRINGID_RAIN]                        = sText_Rain, 
    [STRINGID_SUN]                         = sText_Sun, 
    [STRINGID_SAND]                        = sText_Sand, 
    [STRINGID_HAIL]                        = sText_Hail, 
    [STRINGID_STATWENTBACKDOWN]             = sText_StatWentBackDown,
    [STRINGID_CELEBRATE]                    = sText_CelebrateTrollString,
    [STRINGID_ANTICIPATE_SOME_MOVE]         = sText_AnticipatedMove,
    [STRINGID_JUDGMENT]                      = sText_JudgmentString,
    [STRINGID_GROUND_NULLIFY]                = sText_GroundNullifiesEarth,
    [STRINGID_NOE_FLIGHT]                    = COMPOUND_STRING("{B_SCR_ACTIVE_NAME_WITH_PREFIX} is flying under the radar!"),
    [STRINGID_WONDER_GUARD_ENTERS]           = sText_WonderGuardEnters,
    [STRINGID_WONDER_GUARD_ENDS]             = sText_WonderGuardEnds,
    [STRINGID_DEF_RAGEABATED]                = sText_DefenderRageEnded,
    [STRINGID_IMMUTABLEWIND_ENTERS]          = COMPOUND_STRING("A strange cold wind blows!"),
    [STRINGID_IMMUTABLEWIND_ENDS]            = COMPOUND_STRING("The strange wind\nfinally subsided!"),
    [STRINGID_ITEMTOBAG]                     = sText_ItemaddedtoBag,
    [STRINGID_DAMP_PREVENTS_AFTERMATH]       = sText_PkmnPreventsAbilityUsage,
    [STRINGID_CUPIDSARROWSTRUCK_BOTH]        = COMPOUND_STRING("{B_SCR_ACTIVE_ABILITY} struck both targets!"),
    [STRINGID_ATK_CUTECHARM]                 = sText_AttakersXInfatuatedY,
    [STRINGID_INVERSIONTRANSFORM]            = sText_InversionTransform,
    [STRINGID_BATTLERABILITYSTAT_INCREASE_ENDS] = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} increase from\n{B_ATK_ABILITY} came to an end!"),
    [STRINGID_SWITCH_LOCK_ENDS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is no longer bound!"),
    [STRINGID_BEINGHITCHARGEDPKMNWITHPOWER]   = COMPOUND_STRING("Being hit by {B_CURRENT_MOVE}\ncharged {B_DEF_NAME_WITH_PREFIX} with power!"),
    [STRINGID_REFLECT_INTIMIDATE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} sent\nthe effect back to {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_CHANGE_ABILITY_TO]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s abiity changed\nto {B_BUFF1}!"),
    [STRINGID_HEAT_TRANCE_HPUP]              = sText_HeatTranceHpUp,
    [STIRNGID_SPIKESABSORBED]               = COMPOUND_STRING("The pointed spikes around {B_ATK_TEAM2}'s team\nsunk into the ground!"),
    [STRINGID_CONSUMED_HAZARD]              = COMPOUND_STRING("{B_SCR_ACTIVE_NAME_WITH_PREFIX} consumed the {STR_VAR_2}\nthanks to {B_SCR_ACTIVE_ABILITY}!"),
    [STRINGID_PKMNBLEWAWAYSHARPSTEEL]       = sText_PkmnBlewAwaySteelSurge,
    [STRINGID_SHARPSTEELFLOATS]            = COMPOUND_STRING("Floating steel spears\nsurround {B_DEF_TEAM2}'s Pokémon!"),
    [STRINGID_SHARPSTEEL_ABSORBED]          = COMPOUND_STRING("The steel spears disappeared\nfrom around {B_ATK_TEAM2}'s team!"),
    [STRINGID_SHARPSTEELDMG]                = COMPOUND_STRING("The sharp steel bit into {B_SCR_ACTIVE_NAME_WITH_PREFIX}!"),
    [STRINGID_RAGINGBULL_BREAKSTHROUGH]     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} broke through the foe's defenses!"),
    [STRINGID_SUPERSWEETAROMAWAFTS]                 = COMPOUND_STRING("A supersweet aroma is wafting from\nthe syrup covering {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_FORCEDTOSURFACE]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was forced\nto surface!{PAUSE 36}"),
    [STRINGID_PKMNINSNAPTRAP]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} got trapped by\na snap trap!"),
    [STRINGID_THUNDERCAGETRAPPED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was caught in\na shocking trap!"),
    [STRINGID_TAKECAUGHTMONFROMPC]              = COMPOUND_STRING("Take Caught Mon From PC?"),
    [STRINGID_MOONLIGHT_SHINING_BRIGHT]              = COMPOUND_STRING("The Moon's light shown brightly!"),
    [STRINGID_MOONLIGHT_SHINES]              = COMPOUND_STRING("Moonlight shines down."),
    [STRINGID_MOONLIGHTFADED]              = COMPOUND_STRING("The Moon's rays faded from view.{PAUSE 36}"),
    [STRINGID_STARTEDSNOW]              = COMPOUND_STRING("It started to snow!"),
    [STRINGID_PKMNSXINTENSIFIEDMOONLIGHT] = sText_PkmnsXIntensifiedMoon,
    [STRINGID_ACIDRAIN_FALLS]           = COMPOUND_STRING("A toxic rain began to fall!"),
    [STRINGID_HURTBYRAIN]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is seared\nby ACID RAIN!"),
    [STRINGID_TARGETISGETTINGSERIOUS]             = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is getting serious now!"),
    [STRINGID_TARGETCHANGEDMODE]             = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} entered Showdown Mode!\p"),
    [STRINGID_BATTLER_ON_A_ROLL]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is on a roll!"), //for flame wheel simple but works well enough
    [STRINGID_PKMNDROPPEDTEMP]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} dropped the temperature!"),
    [STRINGID_PKMNSWARMED]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was trapped\nin a swirling Swarm!"),
    [STRINGID_PKMNCAMETOITSSENSES]       = COMPOUND_STRING("{B_SCR_ACTIVE_NAME_WITH_PREFIX} came to its senses!"),
    [STRINGID_PKMNRETURNEDTOAIR]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} returned to the air!"),
=======
const u8 *const gBattleStringsTable[STRINGID_COUNT] =
{
    [STRINGID_TRAINER1LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER1_LOSE_TEXT}"),
    [STRINGID_PKMNGAINEDEXP]                        = COMPOUND_STRING("{B_BUFF1} gained{B_BUFF2} {B_BUFF3} Exp. Points!\p"),
    [STRINGID_PKMNGREWTOLV]                         = COMPOUND_STRING("{B_BUFF1} grew to Lv. {B_BUFF2}!{WAIT_SE}\p"),
    [STRINGID_PKMNLEARNEDMOVE]                      = COMPOUND_STRING("{B_BUFF1} learned {B_BUFF2}!{WAIT_SE}\p"),
    [STRINGID_TRYTOLEARNMOVE1]                      = COMPOUND_STRING("{B_BUFF1} wants to learn the move {B_BUFF2}.\p"),
    [STRINGID_TRYTOLEARNMOVE2]                      = COMPOUND_STRING("However, {B_BUFF1} already knows four moves.\p"),
    [STRINGID_TRYTOLEARNMOVE3]                      = COMPOUND_STRING("Should another move be forgotten and replaced with {B_BUFF2}?"),
    [STRINGID_PKMNFORGOTMOVE]                       = COMPOUND_STRING("{B_BUFF1} forgot {B_BUFF2}…\p"),
    [STRINGID_STOPLEARNINGMOVE]                     = COMPOUND_STRING("{PAUSE 32}Do you want to give up on having {B_BUFF1} learn {B_BUFF2}?"),
    [STRINGID_DIDNOTLEARNMOVE]                      = COMPOUND_STRING("{B_BUFF1} did not learn {B_BUFF2}.\p"),
    [STRINGID_PKMNLEARNEDMOVE2]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} learned {B_BUFF1}!"),
    [STRINGID_ATTACKMISSED]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s attack missed!"),
    [STRINGID_PKMNPROTECTEDITSELF]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} protected itself!"),
    [STRINGID_STATSWONTINCREASE2]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s stats won't go any higher!"),
    [STRINGID_ITDOESNTAFFECT]                       = COMPOUND_STRING("It doesn't affect {B_DEF_NAME_WITH_PREFIX2}…"),
    [STRINGID_SCR_ITDOESNTAFFECT]                   = COMPOUND_STRING("It doesn't affect {B_SCR_NAME_WITH_PREFIX2}…"),
    [STRINGID_BATTLERFAINTED]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} fainted!\p"),
    [STRINGID_PLAYERGOTMONEY]                       = COMPOUND_STRING("You got ¥{B_BUFF1} for winning!\p"),
    [STRINGID_PLAYERWHITEOUT]                       = COMPOUND_STRING("You have no more Pokémon that can fight!\p"),
    [STRINGID_PLAYERWHITEOUT2_WILD]                 = COMPOUND_STRING("You panicked and dropped ¥{B_BUFF1}…"),
    [STRINGID_PLAYERWHITEOUT2_TRAINER]              = COMPOUND_STRING("You gave ¥{B_BUFF1} to the winner…"),
    [STRINGID_PLAYERWHITEOUT3]                      = COMPOUND_STRING("You were overwhelmed by your defeat!"),
    [STRINGID_PREVENTSESCAPE]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} prevents escape with {B_SCR_ABILITY}!\p"),
    [STRINGID_HITXTIMES]                            = COMPOUND_STRING("The Pokémon was hit {B_BUFF1} time(s)!"), //SV has dynamic plural here
    [STRINGID_PKMNFELLASLEEP]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} fell asleep!"),
    [STRINGID_PKMNMADESLEEP]                        = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} made {B_EFF_NAME_WITH_PREFIX2} sleep!"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYASLEEP]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is already asleep!"),
    [STRINGID_PKMNALREADYASLEEP2]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is already asleep!"),
    [STRINGID_PKMNWASPOISONED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was poisoned!"),
    [STRINGID_PKMNPOISONEDBY]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was poisoned by {B_SCR_NAME_WITH_PREFIX2}'s {B_BUFF1}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYPOISON]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by its poisoning!"),
    [STRINGID_PKMNALREADYPOISONED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is already poisoned!"),
    [STRINGID_PKMNBADLYPOISONED]                    = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was badly poisoned!"),
    [STRINGID_PKMNENERGYDRAINED]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} had its energy drained!"),
    [STRINGID_PKMNWASBURNED]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was burned!"),
    [STRINGID_PKMNBURNEDBY]                         = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} burned {B_EFF_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYBURN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by its burn!"),
    [STRINGID_PKMNWASFROZEN]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was frozen solid!"),
    [STRINGID_PKMNFROZENBY]                         = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} froze {B_EFF_NAME_WITH_PREFIX2} solid!"), //not in gen 5+, ability popup
    [STRINGID_PKMNISFROZEN]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is frozen solid!"),
    [STRINGID_PKMNWASDEFROSTED]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} thawed out!"),
    [STRINGID_PKMNWASDEFROSTED2]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} thawed out!"),
    [STRINGID_PKMNWASDEFROSTEDBY]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} melted the ice!"),
    [STRINGID_PKMNWASPARALYZED]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} is paralyzed, so it may be unable to move!"),
    [STRINGID_PKMNWASPARALYZEDBY]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} paralyzed {B_EFF_NAME_WITH_PREFIX2}, so it may be unable to move!"), //not in gen 5+, ability popup
    [STRINGID_PKMNISPARALYZED]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} couldn't move because it's paralyzed!"),
    [STRINGID_PKMNISALREADYPARALYZED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is already paralyzed!"),
    [STRINGID_PKMNHEALEDPARALYSIS]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was cured of paralysis!"),
    [STRINGID_STATSWONTINCREASE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} won't go any higher!"),
    [STRINGID_STATSWONTDECREASE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} won't go any lower!"),
    [STRINGID_PKMNISCONFUSED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is confused!"),
    [STRINGID_PKMNHEALEDCONFUSION]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} snapped out of its confusion!"),
    [STRINGID_PKMNWASCONFUSED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} became confused!"),
    [STRINGID_PKMNALREADYCONFUSED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is already confused!"),
    [STRINGID_PKMNFELLINLOVE]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} fell in love!"),
    [STRINGID_PKMNINLOVE]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is in love with {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNIMMOBILIZEDBYLOVE]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is immobilized by love!"),
    [STRINGID_PKMNCHANGEDTYPE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} transformed into the {B_BUFF1} type!"),
    [STRINGID_PKMNFLINCHED]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} flinched and couldn't move!"),
    [STRINGID_PKMNREGAINEDHEALTH]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s HP was restored."),
    [STRINGID_PKMNHPFULL]                           = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s HP is full!"),
    [STRINGID_PKMNRAISEDSPDEF]                      = COMPOUND_STRING("Light Screen made {B_ATK_TEAM2} team stronger against special moves!"),
    [STRINGID_PKMNRAISEDDEF]                        = COMPOUND_STRING("Reflect made {B_ATK_TEAM2} team stronger against physical moves!"),
    [STRINGID_PKMNCOVEREDBYVEIL]                    = COMPOUND_STRING("{B_ATK_TEAM1} team cloaked itself in a mystical veil!"),
    [STRINGID_PKMNUSEDSAFEGUARD]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is protected by Safeguard!"),
    [STRINGID_PKMNSAFEGUARDEXPIRED]                 = COMPOUND_STRING("{B_ATK_TEAM1} team is no longer protected by Safeguard!"),
    [STRINGID_PKMNWENTTOSLEEP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} went to sleep!"), //not in gen 5+
    [STRINGID_PKMNSLEPTHEALTHY]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} slept and restored its HP!"),
    [STRINGID_PKMNWHIPPEDWHIRLWIND]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} whipped up a whirlwind!"),
    [STRINGID_PKMNTOOKSUNLIGHT]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} absorbed light!"),
    [STRINGID_PKMNLOWEREDHEAD]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tucked in its head!"),
    [STRINGID_PKMNISGLOWING]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became cloaked in a harsh light!"),
    [STRINGID_PKMNFLEWHIGH]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} flew up high!"),
    [STRINGID_PKMNDUGHOLE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} burrowed its way under the ground!"),
    [STRINGID_PKMNSQUEEZEDBYBIND]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was squeezed by {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNTRAPPEDINVORTEX]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} became trapped in the vortex!"),
    [STRINGID_PKMNWRAPPEDBY]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was wrapped by {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNCLAMPED]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} clamped down on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNHURTBY]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is hurt by {B_BUFF1}!"),
    [STRINGID_PKMNFREEDFROM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was freed from {B_BUFF1}!"),
    [STRINGID_PKMNCRASHED]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} kept going and crashed!"),
    [STRINGID_PKMNSHROUDEDINMIST]                   = COMPOUND_STRING("{B_ATK_PREFIX2} became\nshrouded in MIST!"),
    [STRINGID_PKMNPROTECTEDBYMIST]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is protected by the mist!"),
    [STRINGID_PKMNGETTINGPUMPED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is getting\npumped!"),
    [STRINGID_PKMNHITWITHRECOIL]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was damaged by the recoil!"),
    [STRINGID_PKMNPROTECTEDITSELF2]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} protected itself!"),
    [STRINGID_PKMNBUFFETEDBYSANDSTORM]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is buffeted by the sandstorm!"),
    [STRINGID_PKMNPELTEDBYHAIL]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is buffeted by the hail!"),
    [STRINGID_PKMNSEEDED]                           = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was seeded!"),
    [STRINGID_PKMNEVADEDATTACK]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} avoided the attack!"),
    [STRINGID_PKMNSAPPEDBYLEECHSEED]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s health is sapped by Leech Seed!"),
    [STRINGID_PKMNFASTASLEEP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is fast asleep."),
    [STRINGID_PKMNWOKEUP]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} woke up!"),
    [STRINGID_PKMNUPROARKEPTAWAKE]                  = COMPOUND_STRING("But the uproar kept {B_SCR_NAME_WITH_PREFIX2} awake!"),
    [STRINGID_PKMNWOKEUPINUPROAR]                   = COMPOUND_STRING("The uproar woke {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNCAUSEDUPROAR]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} caused an uproar!"),
    [STRINGID_PKMNMAKINGUPROAR]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is making an uproar!"),
    [STRINGID_PKMNCALMEDDOWN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} calmed down."),
    [STRINGID_PKMNCANTSLEEPINUPROAR]                = COMPOUND_STRING("But {B_DEF_NAME_WITH_PREFIX2} can't sleep in an uproar!"),
    [STRINGID_PKMNSTOCKPILED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stockpiled {B_BUFF1}!"),
    [STRINGID_PKMNCANTSLEEPINUPROAR2]               = COMPOUND_STRING("But {B_DEF_NAME_WITH_PREFIX2} can't sleep in an uproar!"),
    [STRINGID_UPROARKEPTPKMNAWAKE]                  = COMPOUND_STRING("But the uproar kept {B_DEF_NAME_WITH_PREFIX2} awake!"),
    [STRINGID_PKMNSTAYEDAWAKEUSING]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} stayed awake using its {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSTORINGENERGY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is storing energy!"),
    [STRINGID_PKMNUNLEASHEDENERGY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} unleashed its energy!"),
    [STRINGID_PKMNFATIGUECONFUSION]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} became confused due to fatigue!"),
    [STRINGID_PLAYERPICKEDUPMONEY]                  = COMPOUND_STRING("You picked up ¥{B_BUFF1}!\p"),
    [STRINGID_PKMNUNAFFECTED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is unaffected!"),
    [STRINGID_PKMNTRANSFORMEDINTO]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} transformed into {B_BUFF1}!"),
    [STRINGID_PKMNMADESUBSTITUTE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} put in a substitute!"),
    [STRINGID_PKMNHASSUBSTITUTE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} already has a substitute!"),
    [STRINGID_SUBSTITUTEDAMAGED]                    = COMPOUND_STRING("The substitute took damage for {B_DEF_NAME_WITH_PREFIX2}!\p"),
    [STRINGID_PKMNSUBSTITUTEFADED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s substitute faded!\p"),
    [STRINGID_PKMNMUSTRECHARGE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} must recharge!"),
    [STRINGID_PKMNRAGEBUILDING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s rage is building!"),
    [STRINGID_PKMNMOVEWASDISABLED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} was disabled!"),
    [STRINGID_PKMNMOVEISDISABLED]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} is disabled!\p"),
    [STRINGID_PKMNMOVEDISABLEDNOMORE]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s move is no longer disabled!"),
    [STRINGID_PKMNGOTENCORE]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} must do an encore!"),
    [STRINGID_PKMNGOTENCOREDMOVE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} can only use {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNENCOREENDED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} ended its encore!"),
    [STRINGID_PKMNTOOKAIM]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} took aim at {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSKETCHEDMOVE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sketched {B_BUFF1}!"),
    [STRINGID_PKMNTRYINGTOTAKEFOE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is hoping to take its attacker down with it!"),
    [STRINGID_PKMNTOOKFOE]                          = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} took its attacker down with it!"),
    [STRINGID_PKMNREDUCEDPP]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s PP was reduced!"),
    [STRINGID_PKMNSTOLEITEM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stole {B_EFF_NAME_WITH_PREFIX2}'s {B_LAST_ITEM}!"),
    [STRINGID_TARGETCANTESCAPENOW]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} can no longer escape!"),
    [STRINGID_PKMNFELLINTONIGHTMARE]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} began having a nightmare!"),
    [STRINGID_PKMNLOCKEDINNIGHTMARE]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is locked in a nightmare!"),
    [STRINGID_PKMNLAIDCURSE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cut its own HP and put a curse on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNAFFLICTEDBYCURSE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is afflicted by the curse!"),
    [STRINGID_SPIKESSCATTERED]                      = COMPOUND_STRING("Spikes were scattered on the ground all around {B_DEF_TEAM2} team!"),
    [STRINGID_PKMNHURTBYSPIKES]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was hurt by the spikes!"),
    [STRINGID_PKMNIDENTIFIED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was identified!"),
    [STRINGID_PKMNPERISHCOUNTFELL]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s perish count fell to {B_BUFF1}!"),
    [STRINGID_PKMNBRACEDITSELF]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} braced itself!"),
    [STRINGID_PKMNENDUREDHIT]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} endured the hit!"),
    [STRINGID_MAGNITUDESTRENGTH]                    = COMPOUND_STRING("Magnitude {B_BUFF1}!"),
    [STRINGID_PKMNCUTHPMAXEDATTACK]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cut its own HP and maximized its Attack!"),
    [STRINGID_PKMNCOPIEDSTATCHANGES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} copied {B_EFF_NAME_WITH_PREFIX2}'s stat changes!"),
    [STRINGID_PKMNGOTFREE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} got free of {B_DEF_NAME_WITH_PREFIX2}'s {B_BUFF1}!"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNSHEDLEECHSEED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} shed Leech Seed!"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNBLEWAWAYSPIKES]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} blew away Spikes!"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNFLEDFROMBATTLE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} fled from battle!"),
    [STRINGID_PKMNFORESAWATTACK]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} foresaw an attack!"),
    [STRINGID_PKMNTOOKATTACK]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} took the {B_BUFF1} attack!"),
    [STRINGID_PKMNATTACK]                           = COMPOUND_STRING("{B_BUFF1}'s attack!"), //not in gen 5+
    [STRINGID_PKMNCENTERATTENTION]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} became the center of attention!"),
    [STRINGID_PKMNCHARGINGPOWER]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} began charging power!"),
    [STRINGID_NATUREPOWERTURNEDINTO]                = COMPOUND_STRING("Nature Power turned into {B_CURRENT_MOVE}!"),
    [STRINGID_PKMNSTATUSNORMAL]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s status returned to normal!"),
    [STRINGID_PKMNHASNOMOVESLEFT]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} has no moves left that it can use!\p"),
    [STRINGID_PKMNSUBJECTEDTOTORMENT]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was subjected to torment!"),
    [STRINGID_PKMNCANTUSEMOVETORMENT]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can't use the same move twice in a row due to the torment!\p"),
    [STRINGID_PKMNTIGHTENINGFOCUS]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is tightening its focus!"),
    [STRINGID_PKMNFELLFORTAUNT]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} fell for the taunt!"),
    [STRINGID_PKMNCANTUSEMOVETAUNT]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can't use {B_CURRENT_MOVE} after the taunt!\p"),
    [STRINGID_PKMNREADYTOHELP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is ready to help {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSWITCHEDITEMS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} switched items with its target!"),
    [STRINGID_PKMNCOPIEDFOE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} copied {B_DEF_NAME_WITH_PREFIX2}'s Ability!"),
    [STRINGID_PKMNWISHCAMETRUE]                     = COMPOUND_STRING("{B_BUFF1}'s wish came true!"),
    [STRINGID_PKMNPLANTEDROOTS]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} planted its roots!"),
    [STRINGID_PKMNABSORBEDNUTRIENTS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} absorbed nutrients with its roots!"),
    [STRINGID_PKMNANCHOREDITSELF]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} anchored itself with its roots!"),
    [STRINGID_PKMNWASMADEDROWSY]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} grew drowsy!"),
    [STRINGID_PKMNKNOCKEDOFF]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} knocked off {B_DEF_NAME_WITH_PREFIX2}'s {B_LAST_ITEM}!"),
    [STRINGID_PKMNSWAPPEDABILITIES]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} swapped Abilities with its target!"),
    [STRINGID_PKMNSEALEDOPPONENTMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sealed any moves its target shares with it!"),
    [STRINGID_PKMNCANTUSEMOVESEALED]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can't use its sealed {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNWANTSGRUDGE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} wants its target to bear a grudge!"),
    [STRINGID_PKMNLOSTPPGRUDGE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} lost all its PP due to the grudge!"),
    [STRINGID_PKMNSHROUDEDITSELF]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} shrouded itself with Magic Coat!"),
    [STRINGID_PKMNMOVEBOUNCED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} bounced the {B_CURRENT_MOVE} back!"),
    [STRINGID_PKMNWAITSFORTARGET]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} waits for a target to make a move!"),
    [STRINGID_PKMNSNATCHEDMOVE]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} snatched {B_SCR_NAME_WITH_PREFIX2}'s move!"),
    [STRINGID_PKMNMADEITRAIN]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} made it rain!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPROTECTEDBY]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was protected by {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSUSAGE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} prevents {B_ATK_NAME_WITH_PREFIX2} from using {B_CURRENT_MOVE}!"), //I don't see this in SV text
    [STRINGID_PKMNRESTOREDHPUSING]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} restored HP using its {B_SCR_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNCHANGEDTYPEWITH]                  = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}'s {B_EFF_ABILITY} made it the {B_BUFF1} type!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSROMANCEWITH]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} prevents romance!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSCONFUSIONWITH]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} prevents confusion!"), //not in gen 5+, ability popup
    [STRINGID_PKMNRAISEDFIREPOWERWITH]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} raised the power of Fire-type moves!"), //not in gen 5+, ability popup
    [STRINGID_PKMNANCHORSITSELFWITH]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} anchors itself with {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNCUTSATTACKWITH]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} cuts {B_DEF_NAME_WITH_PREFIX2}'s Attack!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSSTATLOSSWITH]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} prevents stat loss!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTSWITH]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by {B_DEF_NAME_WITH_PREFIX2}'s {B_BUFF1}!"),
    [STRINGID_PKMNTRACED]                           = COMPOUND_STRING("It traced {B_BUFF1}'s {B_BUFF2}!"),
    [STRINGID_STATSHARPLY]                          = COMPOUND_STRING("sharply "),
    [STRINGID_STATROSE]                             = COMPOUND_STRING("rose!"),
    [STRINGID_STATHARSHLY]                          = COMPOUND_STRING("harshly "),
    [STRINGID_STATFELL]                             = COMPOUND_STRING("fell!"),
    [STRINGID_ATTACKERSSTATROSE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}rose!"), //need compare to FR
    [STRINGID_DEFENDERSSTATROSE]                    = gText_DefendersStatRose,
    [STRINGID_SCRIPTINGSTATROSE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}rose!"),
    [STRINGID_ATTACKERSSTATFELL]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}fell!"),
    [STRINGID_DEFENDERSSTATFELL]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}fell!"),
    [STRINGID_CRITICALHIT]                          = COMPOUND_STRING("A critical hit!"),
    [STRINGID_ONEHITKO]                             = COMPOUND_STRING("It's a one-hit KO!"),
    [STRINGID_123POOF]                              = COMPOUND_STRING("One…{PAUSE 10}two…{PAUSE 10}and…{PAUSE 10}{PAUSE 20}{PLAY_SE SE_BALL_BOUNCE_1}ta-da!\p"),
    [STRINGID_ANDELLIPSIS]                          = COMPOUND_STRING("And…\p"),
    [STRINGID_NOTVERYEFFECTIVE]                     = COMPOUND_STRING("It's not very effective…"),
    [STRINGID_SUPEREFFECTIVE]                       = COMPOUND_STRING("It's super effective!"),
    [STRINGID_GOTAWAYSAFELY]                        = COMPOUND_STRING("{PLAY_SE SE_FLEE}Got away safely!\p"),
    [STRINGID_WILDPKMNFLED]                         = COMPOUND_STRING("{PLAY_SE SE_FLEE}The wild {B_BUFF1} fled!"),
    [STRINGID_NORUNNINGFROMTRAINERS]                = COMPOUND_STRING("No! There's no running from a Trainer battle!\p"),
    [STRINGID_CANTESCAPE]                           = COMPOUND_STRING("You can't escape!\p"),
    [STRINGID_DONTLEAVEBIRCH]                       = COMPOUND_STRING("PROF. BIRCH: Don't leave me like this!\p"), //no decapitalize until it is everywhere
    [STRINGID_BUTNOTHINGHAPPENED]                   = COMPOUND_STRING("But nothing happened!"),
    [STRINGID_BUTITFAILED]                          = COMPOUND_STRING("But it failed!"),
    [STRINGID_ITHURTCONFUSION]                      = COMPOUND_STRING("It hurt itself in its confusion!"),
    [STRINGID_STARTEDTORAIN]                        = COMPOUND_STRING("It started to rain!"),
    [STRINGID_DOWNPOURSTARTED]                      = COMPOUND_STRING("A downpour started!"), // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
    [STRINGID_RAINCONTINUES]                        = COMPOUND_STRING("Rain continues to fall."), //not in gen 5+
    [STRINGID_DOWNPOURCONTINUES]                    = COMPOUND_STRING("The downpour continues."), // unused
    [STRINGID_RAINSTOPPED]                          = COMPOUND_STRING("The rain stopped."),
    [STRINGID_SANDSTORMBREWED]                      = COMPOUND_STRING("A sandstorm kicked up!"),
    [STRINGID_SANDSTORMRAGES]                       = COMPOUND_STRING("The sandstorm is raging."),
    [STRINGID_SANDSTORMSUBSIDED]                    = COMPOUND_STRING("The sandstorm subsided."),
    [STRINGID_SUNLIGHTGOTBRIGHT]                    = COMPOUND_STRING("The sunlight turned harsh!"),
    [STRINGID_SUNLIGHTSTRONG]                       = COMPOUND_STRING("The sunlight is strong."), //not in gen 5+
    [STRINGID_SUNLIGHTFADED]                        = COMPOUND_STRING("The sunlight faded."),
    [STRINGID_STARTEDHAIL]                          = COMPOUND_STRING("It started to hail!"),
    [STRINGID_HAILCONTINUES]                        = COMPOUND_STRING("The hail is crashing down."),
    [STRINGID_HAILSTOPPED]                          = COMPOUND_STRING("The hail stopped."),
    [STRINGID_STATCHANGESGONE]                      = COMPOUND_STRING("All stat changes were eliminated!"),
    [STRINGID_COINSSCATTERED]                       = COMPOUND_STRING("Coins were scattered everywhere!"),
    [STRINGID_TOOWEAKFORSUBSTITUTE]                 = COMPOUND_STRING("But it does not have enough HP left to make a substitute!"),
    [STRINGID_SHAREDPAIN]                           = COMPOUND_STRING("The battlers shared their pain!"),
    [STRINGID_BELLCHIMED]                           = COMPOUND_STRING("A bell chimed!"),
    [STRINGID_FAINTINTHREE]                         = COMPOUND_STRING("All Pokémon that heard the song will faint in three turns!"),
    [STRINGID_NOPPLEFT]                             = COMPOUND_STRING("There's no PP left for this move!\p"), //not in gen 5+
    [STRINGID_BUTNOPPLEFT]                          = COMPOUND_STRING("But there was no PP left for the move!"),
    [STRINGID_PLAYERUSEDITEM]                       = COMPOUND_STRING("You used {B_LAST_ITEM}!"),
    [STRINGID_WALLYUSEDITEM]                        = COMPOUND_STRING("WALLY used {B_LAST_ITEM}!"), //no decapitalize until it is everywhere
    [STRINGID_TRAINERBLOCKEDBALL]                   = COMPOUND_STRING("The Trainer blocked your Poké Ball!"),
    [STRINGID_DONTBEATHIEF]                         = COMPOUND_STRING("Don't be a thief!"),
    [STRINGID_ITDODGEDBALL]                         = COMPOUND_STRING("It dodged your thrown Poké Ball! This Pokémon can't be caught!"),
    [STRINGID_YOUMISSEDPKMN]                        = COMPOUND_STRING("You missed the Pokémon!"),
    [STRINGID_PKMNBROKEFREE]                        = COMPOUND_STRING("Oh no! The Pokémon broke free!"),
    [STRINGID_ITAPPEAREDCAUGHT]                     = COMPOUND_STRING("Aww! It appeared to be caught!"),
    [STRINGID_AARGHALMOSTHADIT]                     = COMPOUND_STRING("Aargh! Almost had it!"),
    [STRINGID_SHOOTSOCLOSE]                         = COMPOUND_STRING("Gah! It was so close, too!"),
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER]               = COMPOUND_STRING("Gotcha! {B_DEF_NAME} was caught!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p"),
    [STRINGID_GOTCHAPKMNCAUGHTWALLY]                = COMPOUND_STRING("Gotcha! {B_DEF_NAME} was caught!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}"),
    [STRINGID_GIVENICKNAMECAPTURED]                 = COMPOUND_STRING("Would you like to give {B_DEF_NAME} a nickname?"),
    [STRINGID_PKMNSENTTOPC]                         = COMPOUND_STRING("{B_DEF_NAME} has been sent to {B_PC_CREATOR_NAME} PC!"), //Still used lanette's pc since terminology is different
    [STRINGID_PKMNDATAADDEDTODEX]                   = COMPOUND_STRING("{B_DEF_NAME}'s data has been added to the Pokédex!\p"),
    [STRINGID_ITISRAINING]                          = COMPOUND_STRING("It's raining!"),
    [STRINGID_SANDSTORMISRAGING]                    = COMPOUND_STRING("The sandstorm is raging!"),
    [STRINGID_CANTESCAPE2]                          = COMPOUND_STRING("You couldn't get away!\p"),
    [STRINGID_PKMNIGNORESASLEEP]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} ignored orders and kept sleeping!"),
    [STRINGID_PKMNIGNOREDORDERS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} ignored orders!"),
    [STRINGID_PKMNBEGANTONAP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} began to nap!"),
    [STRINGID_PKMNLOAFING]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is loafing around!"),
    [STRINGID_PKMNWONTOBEY]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} won't obey!"),
    [STRINGID_PKMNTURNEDAWAY]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} turned away!"),
    [STRINGID_PKMNPRETENDNOTNOTICE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} pretended not to notice!"),
    [STRINGID_ENEMYABOUTTOSWITCHPKMN]               = COMPOUND_STRING("{B_TRAINER1_NAME_WITH_CLASS} is about to send out {B_BUFF2}.\pWill you switch your Pokémon?"),
    [STRINGID_CREPTCLOSER]                          = COMPOUND_STRING("{B_PLAYER_NAME} crept closer to {B_OPPONENT_MON1_NAME}!"), //safari
    [STRINGID_CANTGETCLOSER]                        = COMPOUND_STRING("{B_PLAYER_NAME} can't get any closer!"), //safari
    [STRINGID_PKMNWATCHINGCAREFULLY]                = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} is watching carefully!"), //safari
    [STRINGID_PKMNCURIOUSABOUTX]                    = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} is curious about the {B_BUFF1}!"), //safari
    [STRINGID_PKMNENTHRALLEDBYX]                    = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} is enthralled by the {B_BUFF1}!"), //safari
    [STRINGID_PKMNIGNOREDX]                         = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} completely ignored the {B_BUFF1}!"), //safari
    [STRINGID_THREWPOKEBLOCKATPKMN]                 = COMPOUND_STRING("{B_PLAYER_NAME} threw a {POKEBLOCK} at the {B_OPPONENT_MON1_NAME}!"), //safari
    [STRINGID_OUTOFSAFARIBALLS]                     = COMPOUND_STRING("{PLAY_SE SE_DING_DONG}ANNOUNCER: You're out of Safari Balls! Game over!\p"), //safari
    [STRINGID_PKMNSITEMCUREDPARALYSIS]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} cured its paralysis!"),
    [STRINGID_PKMNSITEMCUREDPOISON]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} cured its poison!"),
    [STRINGID_PKMNSITEMHEALEDBURN]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} cured its burn!"),
    [STRINGID_PKMNSITEMDEFROSTEDIT]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} defrosted it!"),
    [STRINGID_PKMNSITEMWOKEIT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} woke it up!"),
    [STRINGID_PKMNSITEMSNAPPEDOUT]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} snapped it out of its confusion!"),
    [STRINGID_PKMNSITEMCUREDPROBLEM]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} cured its {B_BUFF1} problem!"),
    [STRINGID_PKMNSITEMRESTOREDHEALTH]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} restored its health using its {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDPP]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} restored PP to its move {B_BUFF1} using its {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDSTATUS]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} returned its stats to normal using its {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE]           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} restored a little HP using its {B_LAST_ITEM}!"),
    [STRINGID_ITEMALLOWSONLYYMOVE]                  = COMPOUND_STRING("{B_LAST_ITEM} only allows the use of {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNHUNGONWITHX]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} hung on using its {B_LAST_ITEM}!"),
    [STRINGID_EMPTYSTRING3]                         = COMPOUND_STRING(""),
    [STRINGID_PKMNSXRESTOREDHPALITTLE2]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} restored its HP a little!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} whipped up a sandstorm!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXPREVENTSYLOSS]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} prevents {B_BUFF1} loss!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXINFATUATEDY]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} infatuated {B_ATK_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXMADEYINEFFECTIVE]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} made {B_CURRENT_MOVE} ineffective!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXCUREDYPROBLEM]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} cured its {B_BUFF1} problem!"), //not in gen 5+, ability popup
    [STRINGID_ITSUCKEDLIQUIDOOZE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sucked up the liquid ooze!"),
    [STRINGID_PKMNTRANSFORMED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} transformed!"),
    [STRINGID_ELECTRICITYWEAKENED]                  = COMPOUND_STRING("Electricity's power was weakened!"),
    [STRINGID_FIREWEAKENED]                         = COMPOUND_STRING("Fire's power was weakened!"),
    [STRINGID_PKMNHIDUNDERWATER]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} hid underwater!"),
    [STRINGID_PKMNSPRANGUP]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sprang up!"),
    [STRINGID_HMMOVESCANTBEFORGOTTEN]               = COMPOUND_STRING("HM moves can't be forgotten now.\p"),
    [STRINGID_XFOUNDONEY]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} found one {B_LAST_ITEM}!"),
    [STRINGID_PLAYERDEFEATEDTRAINER1]               = COMPOUND_STRING("Player defeated\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!\p"),
    [STRINGID_SOOTHINGAROMA]                        = COMPOUND_STRING("A soothing aroma wafted through the area!"),
    [STRINGID_ITEMSCANTBEUSEDNOW]                   = COMPOUND_STRING("Items can't be used now.{PAUSE 64}"), //not in gen 5+, i think
    [STRINGID_USINGITEMSTATOFPKMNROSE]              = COMPOUND_STRING("Using {B_LAST_ITEM}, the {B_BUFF1} of {B_SCR_NAME_WITH_PREFIX2} {B_BUFF2}rose!"), //todo: update this, will require code changes
    [STRINGID_USINGITEMSTATOFPKMNFELL]              = COMPOUND_STRING("Using {B_LAST_ITEM}, the {B_BUFF1} of {B_SCR_NAME_WITH_PREFIX2} {B_BUFF2}fell!"),
    [STRINGID_PKMNUSEDXTOGETPUMPED]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} used the {B_LAST_ITEM} to get pumped!"),
    [STRINGID_PKMNSXMADEYUSELESS]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} made {B_CURRENT_MOVE} useless!"), //not in gen 5+, ability popup
    [STRINGID_PKMNTRAPPEDBYSANDTOMB]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} became trapped by the quicksand!"),
    [STRINGID_EMPTYSTRING4]                         = COMPOUND_STRING(""),
    [STRINGID_ABOOSTED]                             = COMPOUND_STRING(" a boosted"),
    [STRINGID_PKMNSXINTENSIFIEDSUN]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} intensified the sun's rays!"), //not in gen 5+, ability popup
    [STRINGID_YOUTHROWABALLNOWRIGHT]                = COMPOUND_STRING("You throw a Ball now, right? I… I'll do my best!"),
    [STRINGID_PKMNSXTOOKATTACK]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} took the attack!"), //In gen 5+ but without naming the ability
    [STRINGID_PKMNCHOSEXASDESTINY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} chose Doom Desire as its destiny!"),
    [STRINGID_PKMNLOSTFOCUS]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} lost its focus and couldn't move!"),
    [STRINGID_USENEXTPKMN]                          = COMPOUND_STRING("Use next Pokémon?"),
    [STRINGID_PKMNFLEDUSINGITS]                     = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} fled using its {B_LAST_ITEM}!\p"),
    [STRINGID_PKMNFLEDUSING]                        = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} fled using {B_ATK_ABILITY}!\p"), //not in gen 5+
    [STRINGID_PKMNWASDRAGGEDOUT]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was dragged out!\p"),
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} normalized its status!"),
    [STRINGID_TRAINER1USEDITEM]                     = COMPOUND_STRING("{B_ATK_TRAINER_NAME_WITH_CLASS} used {B_LAST_ITEM}!"),
    [STRINGID_BOXISFULL]                            = COMPOUND_STRING("The Box is full! You can't catch any more!\p"),
    [STRINGID_PKMNAVOIDEDATTACK]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} avoided the attack!"),
    [STRINGID_PKMNSXMADEITINEFFECTIVE]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} made it ineffective!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXPREVENTSFLINCHING]              = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}'s {B_EFF_ABILITY} prevents flinching!"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYHASBURN]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is already burned!"),
    [STRINGID_STATSWONTDECREASE2]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s stats won't go any lower!"),
    [STRINGID_PKMNSXBLOCKSY]                        = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} blocks {B_CURRENT_MOVE}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXWOREOFF]                        = COMPOUND_STRING("{B_ATK_TEAM1} team's {B_BUFF1} wore off!"),
    [STRINGID_THEWALLSHATTERED]                     = COMPOUND_STRING("The wall shattered!"), //not in gen5+, uses "your teams light screen wore off!" etc instead
    [STRINGID_PKMNSXCUREDITSYPROBLEM]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} cured its {B_BUFF1} problem!"), //not in gen 5+, ability popup
    [STRINGID_ATTACKERCANTESCAPE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can't escape!"),
    [STRINGID_PKMNOBTAINEDX]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} obtained {B_BUFF1}."),
    [STRINGID_PKMNOBTAINEDX2]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} obtained {B_BUFF2}."),
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} obtained {B_BUFF1}.\p{B_DEF_NAME_WITH_PREFIX} obtained {B_BUFF2}."),
    [STRINGID_BUTNOEFFECT]                          = COMPOUND_STRING("But it had no effect!"),
    [STRINGID_TWOENEMIESDEFEATED]                   = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER2_LOSE_TEXT}"),
    [STRINGID_PKMNINCAPABLEOFPOWER]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} appears incapable of using its power!"),
    [STRINGID_GLINTAPPEARSINEYE]                    = COMPOUND_STRING("A glint appears in {B_SCR_NAME_WITH_PREFIX2}'s eyes!"),
    [STRINGID_PKMNGETTINGINTOPOSITION]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is getting into position!"),
    [STRINGID_PKMNBEGANGROWLINGDEEPLY]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} began growling deeply!"),
    [STRINGID_PKMNEAGERFORMORE]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is eager for more!"),
    [STRINGID_DEFEATEDOPPONENTBYREFEREE]            = COMPOUND_STRING("{B_PLAYER_MON1_NAME} defeated the opponent {B_OPPONENT_MON1_NAME} in a REFEREE's decision!"),
    [STRINGID_LOSTTOOPPONENTBYREFEREE]              = COMPOUND_STRING("{B_PLAYER_MON1_NAME} lost to the opponent {B_OPPONENT_MON1_NAME} in a REFEREE's decision!"),
    [STRINGID_TIEDOPPONENTBYREFEREE]                = COMPOUND_STRING("{B_PLAYER_MON1_NAME} tied the opponent {B_OPPONENT_MON1_NAME} in a REFEREE's decision!"),
    [STRINGID_QUESTIONFORFEITMATCH]                 = COMPOUND_STRING("Would you like to forfeit the match and quit now?"),
    [STRINGID_FORFEITEDMATCH]                       = COMPOUND_STRING("The match was forfeited."),
    [STRINGID_PKMNTRANSFERREDSOMEONESPC]            = gText_PkmnTransferredSomeonesPC,//have fr version may use that
    [STRINGID_PKMNTRANSFERREDLANETTESPC]            = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL]                = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL]                = gText_PkmnTransferredLanettesPCBoxFull,//have fr version may use that
    [STRINGID_TRAINER1WINTEXT]                      = COMPOUND_STRING("{B_TRAINER1_WIN_TEXT}"),
    [STRINGID_TRAINER2WINTEXT]                      = COMPOUND_STRING("{B_TRAINER2_WIN_TEXT}"),
    [STRINGID_ENDUREDSTURDY]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} endured the hit using {B_DEF_ABILITY}!"),
    [STRINGID_POWERHERB]                            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became fully charged due to its {B_LAST_ITEM}!"),
    [STRINGID_HURTBYITEM]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by the {B_LAST_ITEM}!"),
    [STRINGID_PSNBYITEM]                            = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was badly poisoned by the {B_LAST_ITEM}!"),
    [STRINGID_BRNBYITEM]                            = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was burned by the {B_LAST_ITEM}!"),
    [STRINGID_DEFABILITYIN]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} activates!"),
    [STRINGID_GRAVITYINTENSIFIED]                   = COMPOUND_STRING("Gravity intensified!"),
    [STRINGID_TARGETIDENTIFIED]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was identified!"),
    [STRINGID_TARGETWOKEUP]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} woke up!"),
    [STRINGID_PKMNSTOLEANDATEITEM]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stole and ate its target's {B_LAST_ITEM}!"),
    [STRINGID_TAILWINDBLEW]                         = COMPOUND_STRING("The Tailwind blew from behind {B_ATK_TEAM2} team!"),
    [STRINGID_PKMNWENTBACK]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} went back to {B_ATK_TRAINER_NAME}!"),
    [STRINGID_PKMNCANTUSEITEMSANYMORE]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} can't use items anymore!"),
    [STRINGID_PKMNFLUNG]                            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} flung its {B_LAST_ITEM}!"),
    [STRINGID_PKMNPREVENTEDFROMHEALING]             = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was prevented from healing!"),
    [STRINGID_PKMNSWITCHEDATKANDDEF]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} switched its Attack and Defense!"),
    [STRINGID_PKMNSABILITYSUPPRESSED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s Ability was suppressed!"),
    [STRINGID_SHIELDEDFROMCRITICALHITS]             = COMPOUND_STRING("Lucky Chant shielded {B_ATK_TEAM2} team from critical hits!"),
    [STRINGID_SWITCHEDATKANDSPATK]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} switched all changes to its Attack and Sp. Atk\pwith its target!"),
    [STRINGID_SWITCHEDDEFANDSPDEF]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} switched all changes to its Defense and Sp. Def\pwith its target!"),
    [STRINGID_PKMNACQUIREDABILITY]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} acquired {B_DEF_ABILITY}!"),
    [STRINGID_POISONSPIKESSCATTERED]                = COMPOUND_STRING("Poison spikes were scattered on the ground all around {B_DEF_TEAM2} team!"),
    [STRINGID_PKMNSWITCHEDSTATCHANGES]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} switched stat changes with its target!"),
    [STRINGID_PKMNSURROUNDEDWITHVEILOFWATER]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} surrounded itself with a veil of water!"),
    [STRINGID_PKMNLEVITATEDONELECTROMAGNETISM]      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} levitated with electromagnetism!"),
    [STRINGID_PKMNTWISTEDDIMENSIONS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} twisted the dimensions!"),
    [STRINGID_POINTEDSTONESFLOAT]                   = COMPOUND_STRING("Pointed stones float in the air around {B_DEF_TEAM2} team!"),
    [STRINGID_CLOAKEDINMYSTICALMOONLIGHT]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became cloaked in mystical moonlight!"),
    [STRINGID_TRAPPEDBYSWIRLINGMAGMA]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} became trapped by swirling magma!"),
    [STRINGID_VANISHEDINSTANTLY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} vanished instantly!"),
    [STRINGID_PROTECTEDTEAM]                        = COMPOUND_STRING("{B_CURRENT_MOVE} protected {B_ATK_TEAM2} team!"),
    [STRINGID_SHAREDITSGUARD]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} shared its guard with the target!"),
    [STRINGID_SHAREDITSPOWER]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} shared its power with the target!"),
    [STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON]         = COMPOUND_STRING("It created a bizarre area in which Defense and Sp. Def stats are swapped!"),
    [STRINGID_BECAMENIMBLE]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became nimble!"),
    [STRINGID_HURLEDINTOTHEAIR]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was hurled into the air!"),
    [STRINGID_HELDITEMSLOSEEFFECTS]                 = COMPOUND_STRING("It created a bizarre area in which Pokémon's held items lose their effects!"),
    [STRINGID_FELLSTRAIGHTDOWN]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} fell straight down!"),
    [STRINGID_TARGETCHANGEDTYPE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} transformed into the {B_BUFF1} type!"),
    [STRINGID_PKMNACQUIREDSIMPLE]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} acquired Simple!"), //shouldn't directly use the name
    [STRINGID_KINDOFFER]                            = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} took the kind offer!"),
    [STRINGID_RESETSTARGETSSTATLEVELS]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s stat changes were removed!"),
    [STRINGID_ALLYSWITCHPOSITION]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} and {B_SCR_NAME_WITH_PREFIX2} switched places!"),
    [STRINGID_RESTORETARGETSHEALTH]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s HP was restored!"),
    [STRINGID_TOOKPKMNINTOTHESKY]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} took {B_DEF_NAME_WITH_PREFIX2} into the sky!"),
    [STRINGID_FREEDFROMSKYDROP]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was freed from the Sky Drop!"),
    [STRINGID_POSTPONETARGETMOVE]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s move was postponed!"),
    [STRINGID_REFLECTTARGETSTYPE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became the same type as {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_TRANSFERHELDITEM]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM} from {B_ATK_NAME_WITH_PREFIX2}"),
    [STRINGID_EMBARGOENDS]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can use items again!"),
    [STRINGID_ELECTROMAGNETISM]                     = COMPOUND_STRING("electromagnetism"),
    [STRINGID_BUFFERENDS]                           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} wore off!"),
    [STRINGID_TELEKINESISENDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was freed from the telekinesis!"),
    [STRINGID_TAILWINDENDS]                         = COMPOUND_STRING("{B_ATK_TEAM1} team's Tailwind petered out!"),
    [STRINGID_LUCKYCHANTENDS]                       = COMPOUND_STRING("{B_ATK_TEAM1} team's Lucky Chant wore off!"),
    [STRINGID_TRICKROOMENDS]                        = COMPOUND_STRING("The twisted dimensions returned to normal!"),
    [STRINGID_WONDERROOMENDS]                       = COMPOUND_STRING("Wonder Room wore off, and Defense and Sp. Def stats returned to normal!"),
    [STRINGID_MAGICROOMENDS]                        = COMPOUND_STRING("Magic Room wore off, and held items' effects returned to normal!"),
    [STRINGID_MUDSPORTENDS]                         = COMPOUND_STRING("The effects of Mud Sport have faded."),
    [STRINGID_WATERSPORTENDS]                       = COMPOUND_STRING("The effects of Water Sport have faded."),
    [STRINGID_GRAVITYENDS]                          = COMPOUND_STRING("Gravity returned to normal!"),
    [STRINGID_AQUARINGHEAL]                         = COMPOUND_STRING("A veil of water restored {B_ATK_NAME_WITH_PREFIX2}'s HP!"),
    [STRINGID_ELECTRICTERRAINENDS]                  = COMPOUND_STRING("The electricity disappeared from the battlefield."),
    [STRINGID_MISTYTERRAINENDS]                     = COMPOUND_STRING("The mist disappeared from the battlefield."),
    [STRINGID_PSYCHICTERRAINENDS]                   = COMPOUND_STRING("The weirdness disappeared from the battlefield!"),
    [STRINGID_GRASSYTERRAINENDS]                    = COMPOUND_STRING("The grass disappeared from the battlefield."),
    [STRINGID_TARGETABILITYSTATRAISE]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"),
    [STRINGID_TARGETSSTATWASMAXEDOUT]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} maxed its {B_BUFF1}!"),
    [STRINGID_ATTACKERABILITYSTATRAISE]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"),
    [STRINGID_POISONHEALHPUP]                       = COMPOUND_STRING("The poisoning healed {B_ATK_NAME_WITH_PREFIX2} a little bit!"), //don't think this message is displayed anymore
    [STRINGID_BADDREAMSDMG]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is tormented!"),
    [STRINGID_MOLDBREAKERENTERS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} breaks the mold!"),
    [STRINGID_TERAVOLTENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is radiating a bursting aura!"),
    [STRINGID_TURBOBLAZEENTERS]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is radiating a blazing aura!"),
    [STRINGID_SLOWSTARTENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is slow to get going!"),
    [STRINGID_SLOWSTARTEND]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} finally got its act together!"),
    [STRINGID_SOLARPOWERHPDROP]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} takes its toll!"), //don't think this message is displayed anymore
    [STRINGID_AFTERMATHDMG]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt!"),
    [STRINGID_ANTICIPATIONACTIVATES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} shuddered!"),
    [STRINGID_FOREWARNACTIVATES]                    = COMPOUND_STRING("{B_SCR_ABILITY} alerted {B_SCR_NAME_WITH_PREFIX2} to {B_EFF_NAME_WITH_PREFIX2}'s {B_BUFF1}!"),
    [STRINGID_ICEBODYHPGAIN]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} healed it a little bit!"), //don't think this message is displayed anymore
    [STRINGID_SNOWWARNINGHAIL]                      = COMPOUND_STRING("It started to hail!"),
    [STRINGID_FRISKACTIVATES]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} frisked {B_DEF_NAME_WITH_PREFIX2} and found its {B_LAST_ITEM}!"),
    [STRINGID_UNNERVEENTERS]                        = COMPOUND_STRING("{B_EFF_TEAM1} team is too nervous to eat Berries!"),
    [STRINGID_HARVESTBERRY]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} harvested its {B_LAST_ITEM}!"),
    [STRINGID_MAGICBOUNCEACTIVATES]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} bounced the {B_ATK_NAME_WITH_PREFIX2} back!"),
    [STRINGID_PROTEANTYPECHANGE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} transformed it into the {B_BUFF1} type!"),
    [STRINGID_SYMBIOSISITEMPASS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} passed its {B_LAST_ITEM} to {B_EFF_NAME_WITH_PREFIX2} through {B_LAST_ABILITY}!"),
    [STRINGID_STEALTHROCKDMG]                       = COMPOUND_STRING("Pointed stones dug into {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_TOXICSPIKESABSORBED]                  = COMPOUND_STRING("The poison spikes disappeared from the ground around {B_EFF_TEAM2} team!"),
    [STRINGID_TOXICSPIKESPOISONED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was poisoned!"),
    [STRINGID_TOXICSPIKESBADLYPOISONED]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was badly poisoned!"),
    [STRINGID_STICKYWEBSWITCHIN]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was caught in a sticky web!"),
    [STRINGID_HEALINGWISHCAMETRUE]                  = COMPOUND_STRING("The healing wish came true for {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_HEALINGWISHHEALED]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} regained health!"),
    [STRINGID_LUNARDANCECAMETRUE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} became cloaked in mystical moonlight!"),
    [STRINGID_CURSEDBODYDISABLED]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} was disabled by {B_DEF_NAME_WITH_PREFIX2}'s {B_DEF_ABILITY}!"),
    [STRINGID_ATTACKERACQUIREDABILITY]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} acquired {B_ATK_ABILITY}!"),
    [STRINGID_TARGETABILITYSTATLOWER]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} {B_BUFF2}lowered its {B_BUFF1}!"),
    [STRINGID_TARGETSTATWONTGOHIGHER]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} won't go any higher!"),
    [STRINGID_PKMNMOVEBOUNCEDABILITY]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} was bounced back by {B_DEF_NAME_WITH_PREFIX2}'s {B_DEF_ABILITY}!"),
    [STRINGID_IMPOSTERTRANSFORM]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} transformed into {B_DEF_NAME_WITH_PREFIX2} using {B_LAST_ABILITY}!"),
    [STRINGID_ASSAULTVESTDOESNTALLOW]               = COMPOUND_STRING("The effects of the {B_LAST_ITEM} prevent status moves from being used!\p"),
    [STRINGID_GRAVITYPREVENTSUSAGE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can't use {B_CURRENT_MOVE} because of gravity!\p"),
    [STRINGID_HEALBLOCKPREVENTSUSAGE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was prevented from healing!\p"),
    [STRINGID_NOTDONEYET]                           = COMPOUND_STRING("This move effect is not done yet!\p"),
    [STRINGID_STICKYWEBUSED]                        = COMPOUND_STRING("A sticky web has been laid out on the ground around {B_DEF_TEAM2} team!"),
    [STRINGID_QUASHSUCCESS]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s move was postponed!"),
    [STRINGID_PKMNBLEWAWAYTOXICSPIKES]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} blew away Toxic Spikes!"),
    [STRINGID_PKMNBLEWAWAYSTICKYWEB]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} blew away Sticky Web!"),
    [STRINGID_PKMNBLEWAWAYSTEALTHROCK]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} blew away Stealth Rock!"),
    [STRINGID_IONDELUGEON]                          = COMPOUND_STRING("A deluge of ions showers the battlefield!"),
    [STRINGID_TOPSYTURVYSWITCHEDSTATS]              = COMPOUND_STRING("All stat changes on {B_DEF_NAME_WITH_PREFIX2} were inverted!"),
    [STRINGID_TERRAINBECOMESMISTY]                  = COMPOUND_STRING("Mist swirled around the battlefield!"),
    [STRINGID_TERRAINBECOMESGRASSY]                 = COMPOUND_STRING("Grass grew to cover the battlefield!"),
    [STRINGID_TERRAINBECOMESELECTRIC]               = COMPOUND_STRING("An electric current ran across the battlefield!"),
    [STRINGID_TERRAINBECOMESPSYCHIC]                = COMPOUND_STRING("The battlefield got weird!"),
    [STRINGID_TARGETELECTRIFIED]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s moves have been electrified!"),
    [STRINGID_MEGAEVOREACTING]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ITEM} is reacting to {B_ATK_TRAINER_NAME}'s Mega Ring!"), //actually displays the type of mega ring in inventory, but we didnt implement them :(
    [STRINGID_MEGAEVOEVOLVED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} has Mega Evolved into Mega {B_BUFF1}!"),
    [STRINGID_DRASTICALLY]                          = COMPOUND_STRING("drastically "),
    [STRINGID_SEVERELY]                             = COMPOUND_STRING("severely "),
    [STRINGID_INFESTATION]                          = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} has been afflicted with an infestation by {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_NOEFFECTONTARGET]                     = COMPOUND_STRING("It won't have any effect on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_BURSTINGFLAMESHIT]                    = COMPOUND_STRING("The bursting flames hit {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_BESTOWITEMGIVING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM} from {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_THIRDTYPEADDED]                       = COMPOUND_STRING("{B_BUFF1} type was added to {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_FELLFORFEINT]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} fell for the feint!"),
    [STRINGID_POKEMONCANNOTUSEMOVE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cannot use {B_CURRENT_MOVE}!"),
    [STRINGID_COVEREDINPOWDER]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is covered in powder!"),
    [STRINGID_POWDEREXPLODES]                       = COMPOUND_STRING("When the flame touched the powder on the Pokémon, it exploded!"),
    [STRINGID_BELCHCANTSELECT]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} hasn't eaten any held Berries, so it can't possibly belch!\p"),
    [STRINGID_SPECTRALTHIEFSTEAL]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stole the target's boosted stats!"),
    [STRINGID_GRAVITYGROUNDING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} fell from the sky due to the gravity!"),
    [STRINGID_MISTYTERRAINPREVENTS]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} surrounds itself with a protective mist!"),
    [STRINGID_GRASSYTERRAINHEALS]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is healed by the grassy terrain!"),
    [STRINGID_ELECTRICTERRAINPREVENTS]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} surrounds itself with electrified terrain!"),
    [STRINGID_PSYCHICTERRAINPREVENTS]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is protected by the Psychic Terrain!"),
    [STRINGID_SAFETYGOGGLESPROTECTED]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is not affected thanks to its {B_LAST_ITEM}!"),
    [STRINGID_FLOWERVEILPROTECTED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} surrounded itself with a veil of petals!"),
    [STRINGID_SWEETVEILPROTECTED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} can't fall asleep due to a veil of sweetness!"),
    [STRINGID_AROMAVEILPROTECTED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is protected by an aromatic veil!"),
    [STRINGID_CELEBRATEMESSAGE]                     = COMPOUND_STRING("Congratulations, {B_PLAYER_NAME}!"),
    [STRINGID_USEDINSTRUCTEDMOVE]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} followed {B_ATK_NAME_WITH_PREFIX2}'s instructions!"),
    [STRINGID_THROATCHOPENDS]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can use sound-based moves again!"),
    [STRINGID_PKMNCANTUSEMOVETHROATCHOP]            = COMPOUND_STRING("The effects of Throat Chop prevent {B_ATK_NAME_WITH_PREFIX2} from using certain moves!\p"),
    [STRINGID_LASERFOCUS]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} concentrated intensely!"),
    [STRINGID_GEMACTIVATES]                         = COMPOUND_STRING("The {B_LAST_ITEM} strengthened {B_ATK_NAME_WITH_PREFIX2}'s power!"),
    [STRINGID_BERRYDMGREDUCES]                      = COMPOUND_STRING("The {B_LAST_ITEM} weakened the damage to {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_AIRBALLOONFLOAT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} floats in the air with its Air Balloon!"),
    [STRINGID_AIRBALLOONPOP]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s Air Balloon popped!"),
    [STRINGID_INCINERATEBURN]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}'s {B_LAST_ITEM} was burnt up!"),
    [STRINGID_BUGBITE]                              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stole and ate its target's {B_LAST_ITEM}!"),
    [STRINGID_ILLUSIONWOREOFF]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s illusion wore off!"),
    [STRINGID_ATTACKERCUREDTARGETSTATUS]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cured {B_DEF_NAME_WITH_PREFIX2}'s problem!"),
    [STRINGID_ATTACKERLOSTFIRETYPE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} burned itself out!"),
    [STRINGID_HEALERCURE]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_LAST_ABILITY} cured {B_SCR_NAME_WITH_PREFIX2}'s problem!"),
    [STRINGID_SCRIPTINGABILITYSTATRAISE]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"),
    [STRINGID_RECEIVERABILITYTAKEOVER]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} was taken over!"),
    [STRINGID_PKNMABSORBINGPOWER]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is absorbing power!"),
    [STRINGID_NOONEWILLBEABLETORUNAWAY]             = COMPOUND_STRING("No one will be able to run away during the next turn!"),
    [STRINGID_DESTINYKNOTACTIVATES]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} fell in love because of the {B_LAST_ITEM}!"),
    [STRINGID_CLOAKEDINAFREEZINGLIGHT]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became cloaked in a freezing light!"),
    [STRINGID_CLEARAMULETWONTLOWERSTATS]            = COMPOUND_STRING("The effects of the {B_LAST_ITEM} held by {B_SCR_NAME_WITH_PREFIX2} prevents its stats from being lowered!"),
    [STRINGID_FERVENTWISHREACHED]                   = COMPOUND_STRING("{B_ATK_TRAINER_NAME}'s fervent wish has reached {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_AIRLOCKACTIVATES]                     = COMPOUND_STRING("The effects of the weather disappeared."),
    [STRINGID_PRESSUREENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is exerting its pressure!"),
    [STRINGID_DARKAURAENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is radiating a dark aura!"),
    [STRINGID_FAIRYAURAENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is radiating a fairy aura!"),
    [STRINGID_AURABREAKENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} reversed all other Pokémon's auras!"),
    [STRINGID_COMATOSEENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is drowsing!"),
    [STRINGID_SCREENCLEANERENTERS]                  = COMPOUND_STRING("All screens on the field were cleansed!"),
    [STRINGID_FETCHEDPOKEBALL]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} found a {B_LAST_ITEM}!"),
    [STRINGID_ASANDSTORMKICKEDUP]                   = COMPOUND_STRING("A sandstorm kicked up!"),
    [STRINGID_PKMNSWILLPERISHIN3TURNS]              = COMPOUND_STRING("Both Pokémon will perish in three turns!"),  //don't think this message is displayed anymore
    [STRINGID_AURAFLAREDTOLIFE]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s aura flared to life!"),
    [STRINGID_ASONEENTERS]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} has two Abilities!"),
    [STRINGID_CURIOUSMEDICINEENTERS]                = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}'s stat changes were removed!"),
    [STRINGID_CANACTFASTERTHANKSTO]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can act faster than normal, thanks to its {B_BUFF1}!"),
    [STRINGID_MICLEBERRYACTIVATES]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} boosted the accuracy of its next move using {B_LAST_ITEM}!"),
    [STRINGID_PKMNSHOOKOFFTHETAUNT]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} shook off the taunt!"),
    [STRINGID_PKMNGOTOVERITSINFATUATION]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} got over its infatuation!"),
    [STRINGID_ITEMCANNOTBEREMOVED]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s item cannot be removed!"),
    [STRINGID_STICKYBARBTRANSFER]                   = COMPOUND_STRING("The {B_LAST_ITEM} attached itself to {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNBURNHEALED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s burn was cured!"),
    [STRINGID_REDCARDACTIVATE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} held up its Red Card against {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_EJECTBUTTONACTIVATE]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is switched out with the {B_LAST_ITEM}!"),
    [STRINGID_ATKGOTOVERINFATUATION]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} got over its infatuation!"),
    [STRINGID_TORMENTEDNOMORE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is no longer tormented!"),
    [STRINGID_HEALBLOCKEDNOMORE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is cured of its heal block!"),
    [STRINGID_ATTACKERBECAMEFULLYCHARGED]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became fully charged due to its bond with its trainer!\p"),
    [STRINGID_ATTACKERBECAMEASHSPECIES]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became Ash-Greninja!\p"),
    [STRINGID_EXTREMELYHARSHSUNLIGHT]               = COMPOUND_STRING("The sunlight turned extremely harsh!"),
    [STRINGID_EXTREMESUNLIGHTFADED]                 = COMPOUND_STRING("The extremely harsh sunlight faded!"),
    [STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT]     = COMPOUND_STRING("The Water-type attack evaporated in the extremely harsh sunlight!"),
    [STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED] = COMPOUND_STRING("The extremely harsh sunlight was not lessened at all!"),
    [STRINGID_HEAVYRAIN]                            = COMPOUND_STRING("A heavy rain began to fall!"),
    [STRINGID_HEAVYRAINLIFTED]                      = COMPOUND_STRING("The heavy rain has lifted!"),
    [STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN]         = COMPOUND_STRING("The Fire-type attack fizzled out in the heavy rain!"),
    [STRINGID_NORELIEFROMHEAVYRAIN]                 = COMPOUND_STRING("There is no relief from this heavy rain!"),
    [STRINGID_MYSTERIOUSAIRCURRENT]                 = COMPOUND_STRING("Mysterious strong winds are protecting Flying-type Pokémon!"),
    [STRINGID_STRONGWINDSDISSIPATED]                = COMPOUND_STRING("The mysterious strong winds have dissipated!"),
    [STRINGID_MYSTERIOUSAIRCURRENTBLOWSON]          = COMPOUND_STRING("The mysterious strong winds blow on regardless!"),
    [STRINGID_ATTACKWEAKENEDBSTRONGWINDS]           = COMPOUND_STRING("The mysterious strong winds weakened the attack!"),
    [STRINGID_STUFFCHEEKSCANTSELECT]                = COMPOUND_STRING("It can't use the move because it doesn't have a Berry!\p"),
    [STRINGID_PKMNREVERTEDTOPRIMAL]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s Primal Reversion! It reverted to its primal state!"),
    [STRINGID_BUTPOKEMONCANTUSETHEMOVE]             = COMPOUND_STRING("But {B_ATK_NAME_WITH_PREFIX2} can't use the move!"),
    [STRINGID_BUTHOOPACANTUSEIT]                    = COMPOUND_STRING("But {B_ATK_NAME_WITH_PREFIX2} can't use it the way it is now!"),
    [STRINGID_BROKETHROUGHPROTECTION]               = COMPOUND_STRING("It broke through {B_DEF_NAME_WITH_PREFIX2}'s protection!"),
    [STRINGID_ABILITYALLOWSONLYMOVE]                = COMPOUND_STRING("{B_ATK_ABILITY} only allows the use of {B_CURRENT_MOVE}!\p"),
    [STRINGID_SWAPPEDABILITIES]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} swapped Abilities with its target!"),
    [STRINGID_PASTELVEILENTERS]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was cured of its poisoning!"),
    [STRINGID_BATTLERTYPECHANGEDTO]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s type changed to {B_BUFF1}!"),
    [STRINGID_BOTHCANNOLONGERESCAPE]                = COMPOUND_STRING("Neither Pokémon can run away!"),
    [STRINGID_CANTESCAPEDUETOUSEDMOVE]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} can no longer escape because it used No Retreat!"),
    [STRINGID_PKMNBECAMEWEAKERTOFIRE]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} became weaker to fire!"),
    [STRINGID_ABOUTTOUSEPOLTERGEIST]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is about to be attacked by its {B_BUFF1}!"),
    [STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE]       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} can no longer escape because of Octolock!"),
    [STRINGID_NEUTRALIZINGGASENTERS]                = COMPOUND_STRING("Neutralizing gas filled the area!"),
    [STRINGID_NEUTRALIZINGGASOVER]                  = COMPOUND_STRING("The effects of the neutralizing gas wore off!"),
    [STRINGID_TARGETTOOHEAVY]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is too heavy to be lifted!"),
    [STRINGID_PKMNTOOKTARGETHIGH]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} took {B_DEF_NAME_WITH_PREFIX2} into the sky!"),
    [STRINGID_PKMNINSNAPTRAP]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} got trapped by a snap trap!"),
    [STRINGID_METEORBEAMCHARGING]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is overflowing with space power!"),
    [STRINGID_HEATUPBEAK]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} started heating up its beak!"),
    [STRINGID_COURTCHANGE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} swapped the battle effects affecting each side of the field!"),
    [STRINGID_ZPOWERSURROUNDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} surrounded itself with its Z-Power!"),
    [STRINGID_ZMOVEUNLEASHED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} unleashes its full-force Z-Move!"),
    [STRINGID_ZMOVERESETSSTATS]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} returned its decreased stats to normal using its Z-Power!"),
    [STRINGID_ZMOVEALLSTATSUP]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} boosted its stats using its Z-Power!"),
    [STRINGID_ZMOVEZBOOSTCRIT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} boosted its critical-hit ratio using its Z-Power!"),
    [STRINGID_ZMOVERESTOREHP]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} restored its HP using its Z-Power!"),
    [STRINGID_ZMOVESTATUP]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} boosted its stats using its Z-Power!"),
    [STRINGID_ZMOVEHPTRAP]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s HP was restored by the Z-Power!"),
    [STRINGID_ATTACKEREXPELLEDTHEPOISON]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} managed to expel the poison so you wouldn't worry!"),
    [STRINGID_ATTACKERSHOOKITSELFAWAKE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} shook itself awake so you wouldn't worry!"),
    [STRINGID_ATTACKERBROKETHROUGHPARALYSIS]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} gathered all its energy to break through its paralysis so you wouldn't worry!"),
    [STRINGID_ATTACKERHEALEDITSBURN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cured its burn through sheer determination so you wouldn't worry!"),
    [STRINGID_ATTACKERMELTEDTHEICE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melted the ice with its fiery determination so you wouldn't worry!"),
    [STRINGID_TARGETTOUGHEDITOUT]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} toughed it out so you wouldn't feel sad!"),
    [STRINGID_ATTACKERLOSTELECTRICTYPE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} used up all its electricity!"),
    [STRINGID_ATTACKERSWITCHEDSTATWITHTARGET]       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} switched {B_BUFF1} with its target!"),
    [STRINGID_BEINGHITCHARGEDPKMNWITHPOWER]         = COMPOUND_STRING("Being hit by {B_CURRENT_MOVE} charged {B_DEF_NAME_WITH_PREFIX2} with power!"),
    [STRINGID_SUNLIGHTACTIVATEDABILITY]             = COMPOUND_STRING("The harsh sunlight activated {B_SCR_NAME_WITH_PREFIX2}'s Protosynthesis!"),
    [STRINGID_STATWASHEIGHTENED]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} was heightened!"),
    [STRINGID_ELECTRICTERRAINACTIVATEDABILITY]      = COMPOUND_STRING("The Electric Terrain activated {B_SCR_NAME_WITH_PREFIX2}'s Quark Drive!"),
    [STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT]   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} weakened the {B_BUFF1} of all surrounding Pokémon!\p"),
    [STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN]  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} gained strength from the fallen!"),
    [STRINGID_PKMNSABILITYPREVENTSABILITY]          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} prevents {B_DEF_NAME_WITH_PREFIX2}'s {B_DEF_ABILITY} from working!"), //not in gen 5+, ability popup
    [STRINGID_PREPARESHELLTRAP]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} set a shell trap!"),
    [STRINGID_SHELLTRAPDIDNTWORK]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s shell trap didn't work!"),
    [STRINGID_SPIKESDISAPPEAREDFROMTEAM]            = COMPOUND_STRING("The spikes disappeared from the ground around {B_ATK_TEAM2} team!"),
    [STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("The poison spikes disappeared from the ground around {B_ATK_TEAM2} team!"),
    [STRINGID_STICKYWEBDISAPPEAREDFROMTEAM]         = COMPOUND_STRING("The sticky web has disappeared from the ground around {B_ATK_TEAM2} team!"),
    [STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("The pointed stones disappeared from around {B_ATK_TEAM2} team!"),
    [STRINGID_COULDNTFULLYPROTECT]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} couldn't fully protect itself and got hurt!"),
    [STRINGID_STOCKPILEDEFFECTWOREOFF]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s stockpiled effect wore off!"),
    [STRINGID_PKMNREVIVEDREADYTOFIGHT]              = COMPOUND_STRING("{B_BUFF1} was revived and is ready to fight again!"),
    [STRINGID_ITEMRESTOREDSPECIESHEALTH]            = COMPOUND_STRING("{B_BUFF1} had its HP restored."),
    [STRINGID_ITEMCUREDSPECIESSTATUS]               = COMPOUND_STRING("{B_BUFF1} had its status healed!"),
    [STRINGID_ITEMRESTOREDSPECIESPP]                = COMPOUND_STRING("{B_BUFF1} had its PP restored!"),
    [STRINGID_THUNDERCAGETRAPPED]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} trapped {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNHURTBYFROSTBITE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by its frostbite!"),
    [STRINGID_PKMNGOTFROSTBITE]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} got frostbite!"),
    [STRINGID_PKMNSITEMHEALEDFROSTBITE]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_LAST_ITEM} cured its frostbite!"),
    [STRINGID_ATTACKERHEALEDITSFROSTBITE]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cured its frostbite through sheer determination so you wouldn't worry!"),
    [STRINGID_PKMNFROSTBITEHEALED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s frostbite was cured!"),
    [STRINGID_PKMNFROSTBITEHEALED2]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s frostbite was cured!"),
    [STRINGID_PKMNFROSTBITEHEALEDBY]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} cured its frostbite!"),
    [STRINGID_MIRRORHERBCOPIED]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} used its Mirror Herb to mirror its opponent's stat changes!"),
    [STRINGID_STARTEDSNOW]                          = COMPOUND_STRING("It started to snow!"),
    [STRINGID_SNOWCONTINUES]                        = COMPOUND_STRING("Snow continues to fall."), //not in gen 5+ (lol)
    [STRINGID_SNOWSTOPPED]                          = COMPOUND_STRING("The snow stopped."),
    [STRINGID_SNOWWARNINGSNOW]                      = COMPOUND_STRING("It started to snow!"),
    [STRINGID_PKMNITEMMELTED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} corroded {B_DEF_NAME_WITH_PREFIX2}'s {B_LAST_ITEM}!"),
    [STRINGID_ULTRABURSTREACTING]                   = COMPOUND_STRING("Bright light is about to burst out of {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_ULTRABURSTCOMPLETED]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} regained its true power through Ultra Burst!"),
    [STRINGID_TEAMGAINEDEXP]                        = COMPOUND_STRING("The rest of your team gained Exp. Points thanks to the Exp. Share!\p"),
    [STRINGID_CURRENTMOVECANTSELECT]                = COMPOUND_STRING("{B_BUFF1} cannot be used!\p"),
    [STRINGID_TARGETISBEINGSALTCURED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is being salt cured!"),
    [STRINGID_TARGETISHURTBYSALTCURE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is hurt by {B_BUFF1}!"),
    [STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP]      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} got covered in sticky candy syrup!"),
    [STRINGID_SHARPSTEELFLOATS]                     = COMPOUND_STRING("Sharp-pointed pieces of steel started floating around {B_DEF_TEAM2} Pokémon!"),
    [STRINGID_SHARPSTEELDMG]                        = COMPOUND_STRING("The sharp steel bit into {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNBLEWAWAYSHARPSTEEL]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} blew away sharp steel!"),
    [STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM]        = COMPOUND_STRING("The pieces of steel surrounding {B_ATK_TEAM2} Pokémon disappeared!"),
    [STRINGID_TEAMTRAPPEDWITHVINES]                 = COMPOUND_STRING("{B_DEF_TEAM1} Pokémon got trapped with vines!"),
    [STRINGID_PKMNHURTBYVINES]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is hurt by G-Max Vine Lash's ferocious beating!"),
    [STRINGID_TEAMCAUGHTINVORTEX]                   = COMPOUND_STRING("{B_DEF_TEAM1} Pokémon got caught in a vortex of water!"),
    [STRINGID_PKMNHURTBYVORTEX]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is hurt by G-Max Cannonade's vortex!"),
    [STRINGID_TEAMSURROUNDEDBYFIRE]                 = COMPOUND_STRING("{B_DEF_TEAM1} Pokémon were surrounded by fire!"),
    [STRINGID_PKMNBURNINGUP]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is burning up within G-Max Wildfire's flames!"),
    [STRINGID_TEAMSURROUNDEDBYROCKS]                = COMPOUND_STRING("{B_DEF_TEAM1} Pokémon became surrounded by rocks!"),
    [STRINGID_PKMNHURTBYROCKSTHROWN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is hurt by rocks thrown out by G-Max Volcalith!"),
    [STRINGID_MOVEBLOCKEDBYDYNAMAX]                 = COMPOUND_STRING("The move was blocked by the power of Dynamax!"),
    [STRINGID_ZEROTOHEROTRANSFORMATION]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} underwent a heroic transformation!"),
    [STRINGID_THETWOMOVESBECOMEONE]                 = COMPOUND_STRING("The two moves have become one! It's a combined move!{PAUSE 16}"),
    [STRINGID_ARAINBOWAPPEAREDONSIDE]               = COMPOUND_STRING("A rainbow appeared in the sky on {B_ATK_TEAM2} team's side!"),
    [STRINGID_THERAINBOWDISAPPEARED]                = COMPOUND_STRING("The rainbow on {B_ATK_TEAM2} team's side disappeared!"),
    [STRINGID_WAITINGFORPARTNERSMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is waiting for {B_ATK_PARTNER_NAME}'s move…{PAUSE 16}"),
    [STRINGID_SEAOFFIREENVELOPEDSIDE]               = COMPOUND_STRING("A sea of fire enveloped {B_DEF_TEAM2} team!"),
    [STRINGID_HURTBYTHESEAOFFIRE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by the sea of fire!"),
    [STRINGID_THESEAOFFIREDISAPPEARED]              = COMPOUND_STRING("The sea of fire around {B_ATK_TEAM2} team disappeared!"),
    [STRINGID_SWAMPENVELOPEDSIDE]                   = COMPOUND_STRING("A swamp enveloped {B_DEF_TEAM2} team!"),
    [STRINGID_THESWAMPDISAPPEARED]                  = COMPOUND_STRING("The swamp around {B_ATK_TEAM2} team disappeared!"),
    [STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is preparing to tell a chillingly bad joke!"),
    [STRINGID_HOSPITALITYRESTORATION]               = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} drank down all the matcha that {B_SCR_NAME_WITH_PREFIX2} made!"),
    [STRINGID_ELECTROSHOTCHARGING]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} absorbed electricity!"),
    [STRINGID_ITEMWASUSEDUP]                        = COMPOUND_STRING("The {B_LAST_ITEM} was used up…"),
    [STRINGID_ATTACKERLOSTITSTYPE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} lost its {B_BUFF1} type!"),
    [STRINGID_SHEDITSTAIL]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} shed its tail to create a decoy!"),
    [STRINGID_CLOAKEDINAHARSHLIGHT]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} became cloaked in a harsh light!"),
    [STRINGID_SUPERSWEETAROMAWAFTS]                 = COMPOUND_STRING("A supersweet aroma is wafting from the syrup covering {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_DIMENSIONSWERETWISTED]                = COMPOUND_STRING("The dimensions were twisted!"),
    [STRINGID_BIZARREARENACREATED]                  = COMPOUND_STRING("A bizarre area was created in which Pokémon's held items lose their effects!"),
    [STRINGID_BIZARREAREACREATED]                   = COMPOUND_STRING("A bizarre area was created in which Defense and Sp. Def stats are swapped!"),
    [STRINGID_TIDYINGUPCOMPLETE]                    = COMPOUND_STRING("Tidying up complete!"),
    [STRINGID_PKMNTERASTALLIZEDINTO]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terastallized into the {B_BUFF1} type!"),
    [STRINGID_BOOSTERENERGYACTIVATES]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} used its {B_LAST_ITEM} to activate {B_SCR_ABILITY}!"),
    [STRINGID_FOG_ROLLED_IN]                       = COMPOUND_STRING("A thick fog rolled in!"),
    [STRINGID_FOGISDEEP]                            = COMPOUND_STRING("The fog is deep…"),
    [STRINGID_FOGLIFTED]                            = COMPOUND_STRING("The fog lifted."),
    [STRINGID_PKMNMADESHELLGLEAM]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} made its shell gleam! It's distorting type matchups!"),
    [STRINGID_FICKLEBEAMDOUBLED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is going all out for this attack!"),
    [STRINGID_COMMANDERACTIVATES]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was swallowed by Dondozo and became Dondozo's commander!"),
    [STRINGID_BATTERYCONSUMED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was absorbed by Vikavolt and became Vikavolt's battery!")
    [STRINGID_POKEFLUTECATCHY]                      = COMPOUND_STRING("{B_PLAYER_NAME} played the {B_LAST_ITEM}.\pNow, that's a catchy tune!"),
    [STRINGID_POKEFLUTE]                            = COMPOUND_STRING("{B_PLAYER_NAME} played the {B_LAST_ITEM}."),
    [STRINGID_MONHEARINGFLUTEAWOKE]                 = COMPOUND_STRING("The Pokémon hearing the flute awoke!"),
    [STRINGID_SUNLIGHTISHARSH]                      = COMPOUND_STRING("The sunlight is harsh!"),
    [STRINGID_ITISHAILING]                          = COMPOUND_STRING("It's hailing!"),
    [STRINGID_ITISSNOWING]                          = COMPOUND_STRING("It's snowing!"),
    [STRINGID_ISCOVEREDWITHGRASS]                   = COMPOUND_STRING("The battlefield is covered with grass!"),
    [STRINGID_MISTSWIRLSAROUND]                     = COMPOUND_STRING("Mist swirls around the battlefield!"),
    [STRINGID_ELECTRICCURRENTISRUNNING]             = COMPOUND_STRING("An electric current is running across the battlefield!"),
    [STRINGID_SEEMSWEIRD]                           = COMPOUND_STRING("The battlefield seems weird!"),
    [STRINGID_WAGGLINGAFINGER]                      = COMPOUND_STRING("Waggling a finger let it use {B_CURRENT_MOVE}!"),
    [STRINGID_BLOCKEDBYSLEEPCLAUSE]                 = COMPOUND_STRING("Sleep Clause kept {B_DEF_NAME_WITH_PREFIX2} awake!"),
    [STRINGID_SUPEREFFECTIVETWOFOES]                = COMPOUND_STRING("It's super effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}!"),
    [STRINGID_NOTVERYEFFECTIVETWOFOES]              = COMPOUND_STRING("It's not very effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}!"),
    [STRINGID_ITDOESNTAFFECTTWOFOES]                = COMPOUND_STRING("It doesn't affect {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}…"),
    [STRINGID_SENDCAUGHTMONPARTYORBOX]              = COMPOUND_STRING("Add {B_DEF_NAME} to your party?"),
    [STRINGID_PKMNSENTTOPCAFTERCATCH]               = gText_PkmnSentToPCAfterCatch, //have fr version may use that
    [STRINGID_PKMNDYNAMAXED]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} grew huge into its Dynamax form!"),
    [STRINGID_PKMNGIGANTAMAXED]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} grew huge into its Gigantamax form!"),
    [STRINGID_TIMETODYNAMAX]                        = COMPOUND_STRING("Time to Dynamax!"),
    [STRINGID_TIMETOGIGANTAMAX]                     = COMPOUND_STRING("Time to Gigantamax!"),
    [STRINGID_QUESTIONFORFEITBATTLE]                = COMPOUND_STRING("Would you like to give up on this battle and quit now? Quitting the battle is the same as losing the battle."),
    [STRINGID_POWERCONSTRUCTPRESENCEOFMANY]         = COMPOUND_STRING("You sense the presence of many!"),
    [STRINGID_POWERCONSTRUCTTRANSFORM]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} transformed into its Complete Forme!"),
    [STRINGID_ABILITYSHIELDPROTECTS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s Ability is protected by the effects of its {B_LAST_ITEM}!"),
>>>>>>> bb41e5622c (Refactor move target failure (#8696))
    
   

    [STRINGID_TRAINER2CLASS]                 = sText_Trainer2Class,
    [STRINGID_TRAINER2NAME]                  = sText_Trainer2Name,
    [STRINGID_PLAYERWHITEDOUT]               = sText_PlayerWhiteout2,
    [STRINGID_MONTOOSCAREDTOMOVE]            = sText_TooScaredToMove,
    [STRINGID_GHOSTGETOUTGETOUT]             = sText_GetOutGetOut,
    [STRINGID_SILPHSCOPEUNVEILED]            = sText_SilphScopeUnveil,
    [STRINGID_GHOSTWASMAROWAK]               = sText_TheGhostWas,
    [STRINGID_TRAINER1MON1COMEBACK]          = sText_Trainer1RecallPkmn1,
    [STRINGID_TRAINER1WINTEXT]               = sText_Trainer1WinText,
    [STRINGID_TRAINER1MON2COMEBACK]          = sText_Trainer1RecallPkmn2,
    [STRINGID_TRAINER1MON1AND2COMEBACK]      = sText_Trainer1RecallBoth
};
//end turn name scripts need to use B_ATK_NAME_WITH_PREFIX,  scr_active name or anything else causes issues

//may be able to use for wondeguard miss with multhit moves
/*
const u16 gMissStringIds[] = {
    STRINGID_ATTACKMISSED,
    STRINGID_PKMNPROTECTEDITSELF,
    STRINGID_PKMNAVOIDEDATTACK,
    STRINGID_AVOIDEDDAMAGE,
    STRINGID_PKMNMAKESGROUNDMISS
};*/

//print effect based on current fixated moves
//for end turn
#define FIXATION_STRING_TABLE
const u16 gFixationMoveStringIds[] = {
    [MOVE_FLAME_WHEEL]      = STRINGID_BATTLER_ON_A_ROLL,
};

//will keep this, and setup just a few special abilities to announce themselves
//some of these are necessary as they announce activation not switchin
const u16 gSwitchInAbilityStringIds[] =
{
    [B_MSG_SWITCHIN_MOLDBREAKER] = STRINGID_MOLDBREAKERENTERS,
    [B_MSG_SWITCHIN_TERAVOLT] = STRINGID_TERAVOLTENTERS,
    [B_MSG_SWITCHIN_TURBOBLAZE] = STRINGID_TURBOBLAZEENTERS,
    [B_MSG_SWITCHIN_SLOWSTART] = STRINGID_SLOWSTARTENTERS,
    [B_MSG_SWITCHIN_DARKAURA] = STRINGID_DARKAURAENTERS,
    [B_MSG_SWITCHIN_FAIRYAURA] = STRINGID_FAIRYAURAENTERS,
    [B_MSG_SWITCHIN_AURABREAK] = STRINGID_AURABREAKENTERS,
    [B_MSG_SWITCHIN_ANTICIPATION] = STRINGID_ANTICIPATIONACTIVATES,
    [B_MSG_SWITCHIN_FOREWARN] = STRINGID_FOREWARNACTIVATES,
    [B_MSG_SWITCHIN_PASTEL_VEIL] = STRINGID_PASTELVEILENTERS,
    [B_MSG_SWITCHIN_CURIOUS_MEDICINE] = STRINGID_CURIOUSMEDICINEENTERS,
    [B_MSG_SWITCHIN_SCREENCLEANER] = STRINGID_SCREENCLEANERENTERS,
    [B_MSG_SWITCHIN_COMATOSE] = STRINGID_COMATOSEENTERS,
    [B_MSG_SWITCHIN_CORRUPTION] = STRINGID_CORRUPTIONENTERS,
    [B_MSG_SWITCHIN_STENCH] = STRINGID_STENCHENTERS,
    [B_MSG_SWITCHIN_PRESSURE] = STRINGID_PRESSUREENTERS,
    //not using these
    /*
    [B_MSG_SWITCHIN_UNNERVE] = STRINGID_UNNERVEENTERS,
    [B_MSG_SWITCHIN_ASONE] = STRINGID_ASONEENTERS,
    */
    [B_MSG_SWITCHIN_NEUTRALIZING_GAS] = STRINGID_NEUTRALIZINGGASENTERS,
    [B_MSG_SWITCHIN_IMMUTABLE_WIND] = STRINGID_IMMUTABLEWIND_ENTERS,
    [B_MSG_SWITCHIN_BANDIT] = STRINGID_BANDITENTERS,
    [B_MSG_SWITCHIN_FLUORESCENT] = STRINGID_PKMNTOOKSUNLIGHT,
    [B_MSG_SWITCHIN_WONDERGUARD] = STRINGID_WONDER_GUARD_ENTERS,
    [B_MSG_SWITCHIN_SUPERSWEET_SYRUP] = STRINGID_SUPERSWEETAROMAWAFTS

};//no comma needed at end

const u16 gNoEscapeStringIds[] = {
    STRINGID_CANTESCAPE,
    STRINGID_DONTLEAVEBIRCH,
    STRINGID_PREVENTSESCAPE,
    STRINGID_CANTESCAPE2,
    STRINGID_ATTACKERCANTESCAPE
};

//need add fog
const u16 gMoveWeatherChangeStringIds[] = {
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,    
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW]      = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_MOONLIGHT] = STRINGID_MOONLIGHT_SHINING_BRIGHT,
    [B_MSG_STARTED_ACID_RAIN] = STRINGID_ACIDRAIN_FALLS,
    [B_MSG_STARTED_FOG]       = STRINGID_FOG_ROLLED_IN,
};

const u16 gWeatherTurnStringIds[] =
{
    [B_MSG_WEATHER_TURN_RAIN]         = STRINGID_RAINCONTINUES,
    [B_MSG_WEATHER_TURN_DOWNPOUR]     = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_WEATHER_TURN_SUN]          = STRINGID_SUNLIGHTSTRONG,
    [B_MSG_WEATHER_TURN_SANDSTORM]    = STRINGID_SANDSTORMRAGES,
    [B_MSG_WEATHER_TURN_HAIL]         = STRINGID_HAILCONTINUES,
    [B_MSG_WEATHER_TURN_SNOW]         = STRINGID_SNOWCONTINUES,
    [B_MSG_WEATHER_TURN_MOON]         = STRINGID_MOONLIGHT_SHINES,
    [B_MSG_WEATHER_TURN_ACID_RAIN]    = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_WEATHER_TURN_FOG]          = STRINGID_FOGISDEEP,
    [B_MSG_WEATHER_TURN_STRONG_WINDS] = STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
};

const u16 gWeatherDmgStringIds[] = {
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL,
    [B_MSG_ACID_RAIN] = STRINGID_HURTBYRAIN,
};

const u16 gWeatherEndsStringIds[B_MSG_WEATHER_END_COUNT] =
{
    [B_MSG_WEATHER_END_RAIN]         = STRINGID_RAINSTOPPED,
    [B_MSG_WEATHER_END_SUN]          = STRINGID_SUNLIGHTFADED,
    [B_MSG_WEATHER_END_SANDSTORM]    = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_WEATHER_END_HAIL]         = STRINGID_HAILSTOPPED,
    [B_MSG_WEATHER_END_SNOW]         = STRINGID_SNOWSTOPPED,
    [B_MSG_WEATHER_END_MOON]         = STRINGID_MOONLIGHTFADED,
    [B_MSG_WEATHER_END_ACID_RAIN]    = STRINGID_RAINSTOPPED,
    [B_MSG_WEATHER_END_FOG]          = STRINGID_FOGLIFTED,
    [B_MSG_WEATHER_END_STRONG_WINDS] = STRINGID_STRONGWINDSDISSIPATED,
};


/*
const u16 gProtectLikeUsedStringIds[] = {
    STRINGID_PKMNPROTECTEDITSELF2,
    STRINGID_PKMNBRACEDITSELF,
    STRINGID_BUTITFAILED
};*/

const u16 gReflectLightScreenSafeguardStringIds[] = {
    STRINGID_BUTITFAILED,
    STRINGID_PKMNRAISEDDEF,
    STRINGID_PKMNRAISEDDEFALITTLE,
    STRINGID_PKMNRAISEDSPDEF,
    STRINGID_PKMNRAISEDSPDEFALITTLE,
    STRINGID_PKMNCOVEREDBYVEIL
};

const u16 gLeechSeedStringIds[] = {
    STRINGID_PKMNSEEDED,
    STRINGID_PKMNEVADEDATTACK,
    STRINGID_ITDOESNTAFFECT,
    STRINGID_PKMNSAPPEDBYLEECHSEED,
    STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gRestUsedStringIds[] = {
    STRINGID_PKMNWENTTOSLEEP,
    STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] = {
    STRINGID_PKMNMAKINGUPROAR,
    STRINGID_PKMNCALMEDDOWN
};

const u16 gStockpileUsedStringIds[] = {
    STRINGID_PKMNSTOCKPILED,
    STRINGID_PKMNCANTSTOCKPILE
};

const u16 gWokeUpStringIds[] = {
    STRINGID_PKMNWOKEUP,
    STRINGID_PKMNWOKEUPINUPROAR,
    STRINGID_PKMNWOKEUPREFRESHED
};

const u16 gSwallowFailStringIds[] = {
    STRINGID_FAILEDTOSWALLOW,
    STRINGID_PKMNHPFULL
};

const u16 gUproarAwakeStringIds[] = {
    STRINGID_PKMNCANTSLEEPINUPROAR2,
    STRINGID_UPROARKEPTPKMNAWAKE,
    STRINGID_PKMNSTAYEDAWAKEUSING
};

const u16 gStatUpStringIds[] = {
    [B_MSG_ATTACKER_STAT_ROSE] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_ROSE] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_INCREASE] = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_ROSE_EMPTY] = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_ROSE_ITEM] = STRINGID_USINGXTHEYOFZN,
    [B_MSG_USED_DIRE_HIT] = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] = {
    [B_MSG_ATTACKER_STAT_FELL] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_FELL] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_DECREASE] = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_FELL_EMPTY] = STRINGID_EMPTYSTRING3
};

//do I still use this?
const u16 gFirstTurnOfTwoStringIds[] = {

    [B_MSG_TURN1_RAZOR_WIND]    = STRINGID_PKMNWHIPPEDWHIRLWIND,     // MOVE_RAZOR_WIND
    [B_MSG_TURN1_SOLAR_BEAM]    = STRINGID_PKMNTOOKSUNLIGHT,         // MOVE_SOLAR_BEAM
    [B_MSG_TURN1_SKULL_BASH]    = STRINGID_PKMNLOWEREDHEAD,          // MOVE_SKULL_BASH
    [B_MSG_TURN1_FLY]           = STRINGID_PKMNFLEWHIGH,             // MOVE_FLY    use for sky attack too
    [B_MSG_TURN1_DIG]           = STRINGID_PKMNDUGHOLE,              // MOVE_DIG
    [B_MSG_TURN1_DIVE]          = STRINGID_PKMNHIDUNDERWATER,        // MOVE_DIVE
    [B_MSG_TURN1_BOUNCE]        = STRINGID_PKMNSPRANGUP,             // MOVE_BOUNCE
    [B_MSG_TURN1_PHANTOM_FORCE] = STRINGID_VANISHEDINSTANTLY,        // MOVE_PHANTOM_FORCE
    [B_MSG_TURN1_GEOMANCY]      = STRINGID_PKNMABSORBINGPOWER,       // MOVE_GEOMANCY
    [B_MSG_TURN1_FREEZE_SHOCK]  = STRINGID_CLOAKEDINAFREEZINGLIGHT,  // MOVE_FREEZE_SHOCK
    [B_MSG_TURN1_SKY_DROP]      = STRINGID_PKMNTOOKTARGETHIGH,       // MOVE_SKY_DROP
    [B_MSG_TURN1_METEOR_BEAM]   = STRINGID_METEORBEAMCHARGING,       // MOVE_METEOR_BEAM
    [B_MSG_TURN1_COLD_FRONT]   = STRINGID_PKMNDROPPEDTEMP,       // MOVE_COLD_FRONT
};

//used in wrap battlescript which is from move effect wrap which makes status wrap
//easiest way to make effects is to canibalize this and make a separate status & move effect & battlescript
//and put the appropriate string in each one. also make catch all define for trap status like I hvae for the effects
//use to make sure trap effects don't overlap  *actually I'll prob allow that since they're all separate now its functionally possible
//don't forget trap effect exclusion for floating enemies, not including magmastorm
//use grounded function rather than just floating species array, so it'll work when grounded
//ok this is linked to gTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] = {

    [B_MSG_WRAPPED_BIND]        = STRINGID_PKMNSQUEEZEDBYBIND,     // MOVE_BIND
    [B_MSG_WRAPPED_WRAP]        = STRINGID_PKMNWRAPPEDBY,          // MOVE_WRAP
    [B_MSG_WRAPPED_FIRE_SPIN]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_FIRE_SPIN
    [B_MSG_WRAPPED_CLAMP]       = STRINGID_PKMNCLAMPED,            // MOVE_CLAMP
    [B_MSG_WRAPPED_WHIRLPOOL]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_WHIRLPOOL
    [B_MSG_WRAPPED_SAND_TOMB]   = STRINGID_PKMNTRAPPEDBYSANDTOMB,  // MOVE_SAND_TOMB
    [B_MSG_WRAPPED_MAGMA_STORM] = STRINGID_TRAPPEDBYSWIRLINGMAGMA, // MOVE_MAGMA_STORM
    [B_MSG_WRAPPED_SWARM] = STRINGID_PKMNSWARMED,            // MOVE_INFESTATION   //now swarm
    [B_MSG_WRAPPED_SNAP_TRAP]   = STRINGID_PKMNINSNAPTRAP,         // MOVE_SNAP_TRAP
    [B_MSG_WRAPPED_THUNDER_CAGE]= STRINGID_THUNDERCAGETRAPPED,     // MOVE_THUNDER_CAGE
};//need to add snaptrap, thundercage

const u16 gMistUsedStringIds[] = {
    STRINGID_PKMNSHROUDEDINMIST,
    STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] = {
    STRINGID_PKMNGETTINGPUMPED,
    STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] = {
    STRINGID_PKMNTRANSFORMEDINTO,
    STRINGID_BUTITFAILED
};

const u16 gSubsituteUsedStringIds[] = {
    STRINGID_PKMNMADESUBSTITUTE,
    STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] = {
    STRINGID_PKMNWASPOISONED,
    STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] = {
    STRINGID_PKMNWASPARALYZED,
    STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] = {
    STRINGID_PKMNFELLASLEEP,
    STRINGID_PKMNMADESLEEP
};

const u16 gGotBurnedStringIds[] = {
    STRINGID_PKMNWASBURNED,
    STRINGID_PKMNBURNEDBY
};

const u16 gGotFrozenStringIds[] = {
    STRINGID_PKMNWASFROZEN,
    STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] = {
    STRINGID_PKMNWASDEFROSTED2,
    STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] = {
    STRINGID_ATTACKMISSED,
    STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] = {
    STRINGID_PKMNFELLINLOVE,
    STRINGID_PKMNSXINFATUATEDY
};

const u16 gLeechSeedDrainStringIds[] = {
    STRINGID_PKMNENERGYDRAINED,
    STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] = {
    STRINGID_ELECTRICITYWEAKENED,
    STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] = {
    STRINGID_BELLCHIMED,
    STRINGID_BELLCHIMED,
    STRINGID_BELLCHIMED,
    STRINGID_BELLCHIMED,
    STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] = {
    STRINGID_PKMNFORESAWATTACK,
    STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] = {
    STRINGID_PKMNBROKEFREE,
    STRINGID_ITAPPEAREDCAUGHT,
    STRINGID_AARGHALMOSTHADIT,
    STRINGID_SHOOTSOCLOSE
};

const u16 gWeatherContinuesStringIds[] = {
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_SANDSTORMISRAGING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_SUNLIGHTSTRONG,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING,
    STRINGID_ITISRAINING
};

const u16 gInobedientStringIds[] = {
    [B_MSG_LOAFING] = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY] = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY] = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE
};

const u16 gSafariPokeblockResultStringIds[] = {
    STRINGID_PKMNWATCHINGCAREFULLY,
    STRINGID_PKMNANGRY,
    STRINGID_PKMNEATING
};

const u16 gTrainerItemCuredStatusStringIds[] = {
    STRINGID_PKMNSITEMSNAPPEDOUT,
    STRINGID_PKMNSITEMCUREDPARALYSIS,
    STRINGID_PKMNSITEMDEFROSTEDIT,
    STRINGID_PKMNSITEMHEALEDBURN,
    STRINGID_PKMNSITEMCUREDPOISON,
    STRINGID_PKMNSITEMWOKEIT
};

const u16 gBerryEffectStringIds[] = {
    STRINGID_PKMNSITEMCUREDPROBLEM,
    STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gBRNPreventionStringIds[] = {
    STRINGID_PKMNSXPREVENTSBURNS,
    STRINGID_PKMNSXPREVENTSYSZ,
    STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPRLZPreventionStringIds[] = {
    STRINGID_PKMNPREVENTSPARALYSISWITH,
    STRINGID_PKMNSXPREVENTSYSZ,
    STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPSNPreventionStringIds[] = {
    STRINGID_PKMNPREVENTSPOISONINGWITH,
    STRINGID_PKMNSXPREVENTSYSZ,
    STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gItemSwapStringIds[] = {
    STRINGID_PKMNOBTAINEDX,
    STRINGID_PKMNOBTAINEDX2,
    STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] = {
    STRINGID_PKMNRAISEDFIREPOWERWITH,
    STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_ATTACKMISSED,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_AVOIDED_DMG] = STRINGID_AVOIDEDDAMAGE,
    [B_MSG_GROUND_MISS] = STRINGID_PKMNMAKESGROUNDMISS,
    [B_MSG_ABILITY_TYPE_MISS]   = STRINGID_ABILITYNULLIFYTYPEDAMAGE
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECT_FAILED]   = STRINGID_BUTITFAILED,
    [B_MSG_PROTECTED_TEAM]   = STRINGID_PROTECTEDTEAM
};

const u16 gCaughtMonStringIds[] = {
    STRINGID_PKMNTRANSFERREDSOMEONESPC,
    STRINGID_PKMNTRANSFERREDBILLSPC,
    STRINGID_PKMNBOXSOMEONESPCFULL,
    STRINGID_PKMNBOXBILLSPCFULL
};

const u16 gDoubleBattleRecallStrings[] = {
    STRINGID_TRAINER1MON1COMEBACK,
    STRINGID_TRAINER1MON1COMEBACK,
    STRINGID_TRAINER1MON2COMEBACK,
    STRINGID_TRAINER1MON1AND2COMEBACK
};

//SEARCH //trap effects  for functionality
//for all traps I change lower stats by 2 stages
const u16 gTrappingMoves[] = {
    MOVE_BIND,      //same for wrap, lower speed of wrapped target 2 stages  / changing to encore effect, because found bug that did that for some reason
    MOVE_WRAP,
    MOVE_FIRE_SPIN, //increases burn chance //serenge grace is effect *2 by requires no setup, I think I can get away w * 3 here actually do more to near guarantee 50-60%
    MOVE_CLAMP,     //no extra wrap effect,  but give flich chance on hit //changed mind you're staying clamped on them, so for duration statused target has chance to flinch when attacking
    MOVE_WHIRLPOOL, // lower speed of wrapped target 1 stage    //already does double damage to underwater target
    MOVE_SAND_TOMB, // decrease accuracy of wrapped target  //do double damage to underground target, use sandpit description from emerald
    MOVE_MAGMA_STORM,   //heatran specific, might buff to give guaranteed burn, don't need lower damage since its lowered from 120 already
    MOVE_SWARM,   //since bug infestations can cause structural integrity issues, think I'll make this lower def & sp def or just def
    MOVE_SNAP_TRAP,     //still to do, effect not made yet, since bear traps hurt more you move, I'll make it hurt attacker every time they use a move just use hurt atacker script
    MOVE_THUNDER_CAGE, //canbelieve I always forget this
    0xFFFF              //think will make snaptrap the only affect that persists if user switches out/faints as its physical trap
};
//logic invaded once again, floating/flying mon should be immunte to trap moves, will exclude magma storm from that as its a legendary move
//will make these buffs slightly situational but would do a lot for the overall strategy and nuance of the game

//ported for updated battlescript
const u16 gStatusConditionsStringIds[] =
{
    STRINGID_PKMNWASPOISONED,
    STRINGID_PKMNBADLYPOISONED, 
    STRINGID_PKMNWASBURNED, 
    STRINGID_PKMNWASPARALYZED, 
    STRINGID_PKMNFELLASLEEP,
    STRINGID_PKMNFROSTBITTEN //add for sake of transferring freeeze rn just via psychoshift
};//why is there no freeze here?

const u16 gRoomsStringIds[] =
{
    STRINGID_PKMNTWISTEDDIMENSIONS, STRINGID_TRICKROOMENDS,
    STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON, STRINGID_WONDERROOMENDS,
    STRINGID_HELDITEMSLOSEEFFECTS, STRINGID_MAGICROOMENDS,
    STRINGID_EMPTYSTRING3
};

/*const u16 gZEffectStringIds[] =
{
    [B_MSG_Z_RESET_STATS] = STRINGID_ZMOVERESETSSTATS,
    [B_MSG_Z_ALL_STATS_UP] = STRINGID_ZMOVEALLSTATSUP,
    [B_MSG_Z_BOOST_CRITS] = STRINGID_ZMOVEZBOOSTCRIT,
    [B_MSG_Z_FOLLOW_ME] = STRINGID_PKMNCENTERATTENTION,
    [B_MSG_Z_RECOVER_HP] = STRINGID_ZMOVERESTOREHP,
    [B_MSG_Z_STAT_UP] = STRINGID_ZMOVESTATUP,
    [B_MSG_Z_HP_TRAP] = STRINGID_ZMOVEHPTRAP,
};*/

const u16 gMentalHerbCureStringIds[] =
{
    [B_MSG_MENTALHERBCURE_INFATUATION] = STRINGID_ATKGOTOVERINFATUATION,
    [B_MSG_MENTALHERBCURE_TAUNT] = STRINGID_BUFFERENDS,
    [B_MSG_MENTALHERBCURE_ENCORE] = STRINGID_PKMNENCOREENDED,
    [B_MSG_MENTALHERBCURE_TORMENT] = STRINGID_TORMENTEDNOMORE,
    [B_MSG_MENTALHERBCURE_HEALBLOCK] = STRINGID_HEALBLOCKEDNOMORE,
    [B_MSG_MENTALHERBCURE_DISABLE] = STRINGID_PKMNMOVEDISABLEDNOMORE,
};


const u16 gTerrainStringIds[B_MSG_TERRAIN_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY] = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC] = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY] = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_TERRAIN_END_MISTY] = STRINGID_MISTYTERRAINENDS,
    [B_MSG_TERRAIN_END_ELECTRIC] = STRINGID_ELECTRICTERRAINENDS,
    [B_MSG_TERRAIN_END_PSYCHIC] = STRINGID_PSYCHICTERRAINENDS,
    [B_MSG_TERRAIN_END_GRASSY] = STRINGID_GRASSYTERRAINENDS,
};

const u16 gTerrainPreventsStringIds[] =
{
    [B_MSG_TERRAINPREVENTS_MISTY] = STRINGID_MISTYTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_ELECTRIC] = STRINGID_ELECTRICTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_PSYCHIC] = STRINGID_PSYCHICTERRAINPREVENTS
};

const u16 gMagicCoatBounceStringIds[] =
{
    STRINGID_PKMNMOVEBOUNCED, STRINGID_PKMNMOVEBOUNCEDABILITY
};

const u16 gHealingWishStringIds[] =
{
    STRINGID_HEALINGWISHCAMETRUE, STRINGID_LUNARDANCECAMETRUE
};

const u16 gDmgHazardsStringIds[] =
{
    [B_MSG_PKMNHURTBYSPIKES]   = STRINGID_PKMNHURTBYSPIKES,
    [B_MSG_STEALTHROCKDMG]     = STRINGID_STEALTHROCKDMG,
    [B_MSG_SHARPSTEELDMG]      = STRINGID_SHARPSTEELDMG,
    [B_MSG_POINTEDSTONESFLOAT] = STRINGID_POINTEDSTONESFLOAT,
    [B_MSG_SPIKESSCATTERED]    = STRINGID_SPIKESSCATTERED,
    [B_MSG_SHARPSTEELFLOATS]   = STRINGID_SHARPSTEELFLOATS,
};

const u16 gSwitchInAbilityStringIds[] =
{
    [B_MSG_SWITCHIN_MOLDBREAKER] = STRINGID_MOLDBREAKERENTERS,
    [B_MSG_SWITCHIN_TERAVOLT] = STRINGID_TERAVOLTENTERS,
    [B_MSG_SWITCHIN_TURBOBLAZE] = STRINGID_TURBOBLAZEENTERS,
    [B_MSG_SWITCHIN_SLOWSTART] = STRINGID_SLOWSTARTENTERS,
    [B_MSG_SWITCHIN_UNNERVE] = STRINGID_UNNERVEENTERS,
    [B_MSG_SWITCHIN_ANTICIPATION] = STRINGID_ANTICIPATIONACTIVATES,
    [B_MSG_SWITCHIN_FOREWARN] = STRINGID_FOREWARNACTIVATES,
    [B_MSG_SWITCHIN_PRESSURE] = STRINGID_PRESSUREENTERS,
    [B_MSG_SWITCHIN_DARKAURA] = STRINGID_DARKAURAENTERS,
    [B_MSG_SWITCHIN_FAIRYAURA] = STRINGID_FAIRYAURAENTERS,
    [B_MSG_SWITCHIN_AURABREAK] = STRINGID_AURABREAKENTERS,
    [B_MSG_SWITCHIN_COMATOSE] = STRINGID_COMATOSEENTERS,
    [B_MSG_SWITCHIN_SCREENCLEANER] = STRINGID_SCREENCLEANERENTERS,
    [B_MSG_SWITCHIN_ASONE] = STRINGID_ASONEENTERS,
    [B_MSG_SWITCHIN_CURIOUS_MEDICINE] = STRINGID_CURIOUSMEDICINEENTERS,
    [B_MSG_SWITCHIN_PASTEL_VEIL] = STRINGID_PASTELVEILENTERS,
    [B_MSG_SWITCHIN_NEUTRALIZING_GAS] = STRINGID_NEUTRALIZINGGASENTERS,
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_ATTACKMISSED,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW]      = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_FOG]       = STRINGID_FOGCREPTUP, // Unused, can use for custom moves that set fog
};

const u16 gAbilityWeatherChangeStringId[] =
{
    [B_MSG_STARTED_DRIZZLE]        = STRINGID_PKMNMADEITRAIN,
    [B_MSG_STARTED_SAND_STREAM]    = STRINGID_PKMNSXWHIPPEDUPSANDSTORM,
    [B_MSG_STARTED_DROUGHT]        = STRINGID_PKMNSXINTENSIFIEDSUN,
    [B_MSG_STARTED_HAIL_WARNING]   = STRINGID_SNOWWARNINGHAIL,
    [B_MSG_STARTED_SNOW_WARNING]   = STRINGID_SNOWWARNINGSNOW,
    [B_MSG_STARTED_DESOLATE_LAND]  = STRINGID_EXTREMELYHARSHSUNLIGHT,
    [B_MSG_STARTED_PRIMORDIAL_SEA] = STRINGID_HEAVYRAIN,
    [B_MSG_STARTED_STRONG_WINDS]   = STRINGID_MYSTERIOUSAIRCURRENT,
};

const u16 gWeatherEndsStringIds[B_MSG_WEATHER_END_COUNT] =
{
    [B_MSG_WEATHER_END_RAIN]         = STRINGID_RAINSTOPPED,
    [B_MSG_WEATHER_END_SUN]          = STRINGID_SUNLIGHTFADED,
    [B_MSG_WEATHER_END_SANDSTORM]    = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_WEATHER_END_HAIL]         = STRINGID_HAILSTOPPED,
    [B_MSG_WEATHER_END_SNOW]         = STRINGID_SNOWSTOPPED,
    [B_MSG_WEATHER_END_FOG]          = STRINGID_FOGLIFTED,
    [B_MSG_WEATHER_END_STRONG_WINDS] = STRINGID_STRONGWINDSDISSIPATED,
};

const u16 gWeatherTurnStringIds[] =
{
    [B_MSG_WEATHER_TURN_RAIN]         = STRINGID_RAINCONTINUES,
    [B_MSG_WEATHER_TURN_DOWNPOUR]     = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_WEATHER_TURN_SUN]          = STRINGID_SUNLIGHTSTRONG,
    [B_MSG_WEATHER_TURN_SANDSTORM]    = STRINGID_SANDSTORMRAGES,
    [B_MSG_WEATHER_TURN_HAIL]         = STRINGID_HAILCONTINUES,
    [B_MSG_WEATHER_TURN_SNOW]         = STRINGID_SNOWCONTINUES,
    [B_MSG_WEATHER_TURN_FOG]          = STRINGID_FOGISDEEP,
    [B_MSG_WEATHER_TURN_STRONG_WINDS] = STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECTED_TEAM]   = STRINGID_PROTECTEDTEAM,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_ATTACKER_STAT_CHANGED] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_CHANGED] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_CHANGE]      = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_CHANGE_EMPTY]     = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_CHANGED_ITEM]     = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_USED_DIRE_HIT]         = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] =
{
    [B_MSG_ATTACKER_STAT_CHANGED] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_CHANGED] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_CHANGE]      = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_CHANGE_EMPTY]     = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_CHANGED_ITEM]     = STRINGID_USINGITEMSTATOFPKMNFELL,
};

// Index copied from move's index in sTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    [B_MSG_WRAPPED_BIND]        = STRINGID_PKMNSQUEEZEDBYBIND,     // MOVE_BIND
    [B_MSG_WRAPPED_WRAP]        = STRINGID_PKMNWRAPPEDBY,          // MOVE_WRAP
    [B_MSG_WRAPPED_FIRE_SPIN]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_FIRE_SPIN
    [B_MSG_WRAPPED_CLAMP]       = STRINGID_PKMNCLAMPED,            // MOVE_CLAMP
    [B_MSG_WRAPPED_WHIRLPOOL]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_WHIRLPOOL
    [B_MSG_WRAPPED_SAND_TOMB]   = STRINGID_PKMNTRAPPEDBYSANDTOMB,  // MOVE_SAND_TOMB
    [B_MSG_WRAPPED_MAGMA_STORM] = STRINGID_TRAPPEDBYSWIRLINGMAGMA, // MOVE_MAGMA_STORM
    [B_MSG_WRAPPED_INFESTATION] = STRINGID_INFESTATION,            // MOVE_INFESTATION
    [B_MSG_WRAPPED_SNAP_TRAP]   = STRINGID_PKMNINSNAPTRAP,         // MOVE_SNAP_TRAP
    [B_MSG_WRAPPED_THUNDER_CAGE]= STRINGID_THUNDERCAGETRAPPED,     // MOVE_THUNDER_CAGE
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrostbiteStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNGOTFROSTBITE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNGOTFROSTBITE,
};

const u16 gFrostbiteHealedStringIds[] =
{
    [B_MSG_FROSTBITE_HEALED]         = STRINGID_PKMNFROSTBITEHEALED2,
    [B_MSG_FROSTBITE_HEALED_BY_MOVE] = STRINGID_PKMNFROSTBITEHEALEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED2,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_ATTACKMISSED,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = (B_OVERWORLD_SNOW >= GEN_9 ? STRINGID_ITISSNOWING : STRINGID_ITISHAILING),
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_FOGISDEEP,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_FOGISDEEP,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTISHARSH,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gTerrainStartsStringIds[] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_MISTSWIRLSAROUND,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_ELECTRICCURRENTISRUNNING,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_SEEMSWEIRD,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_ISCOVEREDWITHGRASS,
};

const u16 gPrimalWeatherBlocksStringIds[] =
{
    [B_MSG_PRIMAL_WEATHER_FIZZLED_BY_RAIN]      = STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,
    [B_MSG_PRIMAL_WEATHER_EVAPORATED_IN_SUN]    = STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 CureStatusBerryEffectStringID[] =
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_PKMNSITEMCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_PKMNSITEMCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_PKMNSITEMHEALEDBURN,
    [B_MSG_CURED_FREEEZE] = STRINGID_PKMNSITEMDEFROSTEDIT,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PKMNSITEMHEALEDFROSTBITE,
    [B_MSG_CURED_SLEEP] = STRINGID_PKMNSITEMWOKEIT,
    [B_MSG_CURED_PROBLEM]     = STRINGID_PKMNSITEMCUREDPROBLEM,
    [B_MSG_NORMALIZED_STATUS] = STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]   = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]   = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL]  = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL]  = STRINGID_PKMNBOXLANETTESPCFULL,
    [B_MSG_SWAPPED_INTO_PARTY] = STRINGID_PKMNSENTTOPCAFTERCATCH,
};

const u16 gStatusConditionsStringIds[] =
{
    STRINGID_PKMNWASPOISONED, STRINGID_PKMNBADLYPOISONED, STRINGID_PKMNWASBURNED, STRINGID_PKMNWASPARALYZED, STRINGID_PKMNFELLASLEEP, STRINGID_PKMNGOTFROSTBITE
};

const u16 gDamageNonTypesStartStringIds[] =
{
    [B_MSG_TRAPPED_WITH_VINES]  = STRINGID_TEAMTRAPPEDWITHVINES,
    [B_MSG_CAUGHT_IN_VORTEX]    = STRINGID_TEAMCAUGHTINVORTEX,
    [B_MSG_SURROUNDED_BY_FIRE]  = STRINGID_TEAMSURROUNDEDBYFIRE,
    [B_MSG_SURROUNDED_BY_ROCKS] = STRINGID_TEAMSURROUNDEDBYROCKS,
};

const u16 gDamageNonTypesDmgStringIds[] =
{
    [B_MSG_HURT_BY_VINES]        = STRINGID_PKMNHURTBYVINES,
    [B_MSG_HURT_BY_VORTEX]       = STRINGID_PKMNHURTBYVORTEX,
    [B_MSG_BURNING_UP]           = STRINGID_PKMNBURNINGUP,
    [B_MSG_HURT_BY_ROCKS_THROWN] = STRINGID_PKMNHURTBYROCKSTHROWN,
};

//already has blew away a
//different beceause one effects your side
//other effects opposing side
//but unsure why need specific string in first place
//especially when multiple effects can be set
//its not gonna print a separate message 
//for each obstacle type
//might as well just generalize it
//blew away obstacles from (your) opposing field
//check if correct vsonic
const u16 gDefogHazardsStringIds[] =
{
    [HAZARDS_SPIKES] = STRINGID_SPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STICKY_WEB] = STRINGID_STICKYWEBDISAPPEAREDFROMTEAM,
    [HAZARDS_TOXIC_SPIKES] = STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STEALTH_ROCK] = STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM,
    [HAZARDS_STEELSURGE] = STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM,
};

const u16 gSpinHazardsStringIds[] =
{
    [HAZARDS_SPIKES] = STRINGID_PKMNBLEWAWAYSPIKES,
    [HAZARDS_STICKY_WEB] = STRINGID_PKMNBLEWAWAYSTICKYWEB,
    [HAZARDS_TOXIC_SPIKES] = STRINGID_PKMNBLEWAWAYTOXICSPIKES,
    [HAZARDS_STEALTH_ROCK] = STRINGID_PKMNBLEWAWAYSTEALTHROCK,
    [HAZARDS_STEELSURGE] = STRINGID_PKMNBLEWAWAYSHARPSTEEL,
};

const u8 gText_PkmnIsEvolving[] = _("What?\n{STR_VAR_1} is evolving!");
const u8 gText_CongratsPkmnEvolved[] = _("Congratulations! Your {STR_VAR_1}\nevolved into {STR_VAR_2}!{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("Huh? {STR_VAR_1}\nstopped evolving!\p");
const u8 gText_EllipsisQuestionMark[] = _("……?\p");
const u8 gText_WhatWillPkmnDo[] = _("What will\n{B_BUFF1} do?");
const u8 gText_WhatWillPlayerThrow[] = _("What will {B_PLAYER_NAME}\nthrow?");
const u8 gText_WhatWillOldManDo[] = _("What will the\nold man do?");
const u8 gText_LinkStandby[] = _("{PAUSE 16}Link standby…");
const u8 gText_BattleMenu[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}FIGHT{CLEAR_TO 56}BAG\nPOKéMON{CLEAR_TO 56}RUN");
const u8 gText_SafariZoneMenu[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}BALL{CLEAR_TO 56}BAIT\nROCK{CLEAR_TO 56}RUN");
const u8 gText_MoveInterfacePP[] = _("PP ");
const u8 gText_BattleMoveInterfacePP[] = _("PP");
const u8 gText_MoveInterfaceType[] = _("TYPE/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}"); //0 for shadow looks pretty good, but this afects both move name and move type
const u8 gUnknown_83FE779[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}どの わざを\nわすれさせたい?");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}Yes\nNo");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}Switch\nwhich?");
const u8 gUnknown_83FE7B6[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}");
const u8 gUnknown_83FE7BF[] = _("{RIGHT_ARROW_2}");
const u8 gUnknown_83FE7C2[] = _("{PLUS}");
const u8 gUnknown_83FE7C5[] = _("-");

const u8 gUnknown_83FE7C7[] = _("{FONT 0}Max{FONT 2} HP");
const u8 gUnknown_83FE7D4[] = _("ATTACK ");
const u8 gUnknown_83FE7DC[] = _("DEFENSE");
const u8 gUnknown_83FE7E4[] = _("SP. ATK");
const u8 gUnknown_83FE7EC[] = _("SP. DEF");

//unused
const u8 *const gUnknown_83FE7F4[] = {
    gUnknown_83FE7C7,
    gUnknown_83FE7E4,
    gUnknown_83FE7D4,
    gUnknown_83FE7EC,
    gUnknown_83FE7DC,
    sText_Speed
};

const u8 gText_SafariBalls[] = _("{HIGHLIGHT 2}SAFARI BALLS"); //
const u8 gText_HighlightRed_Left[] = _("{HIGHLIGHT 2}Left: ");
const u8 gText_HighlightRed[] = _("{HIGHLIGHT 2}");
const u8 gText_Sleep[] = _("sleep");
const u8 gText_Poison[] = _("poison");
const u8 gText_Burn[] = _("burn");
const u8 gText_Paralysis[] = _("paralysis");
const u8 gText_Ice[] = _("ice");
const u8 gText_Confusion[] = _("confusion");
const u8 gText_Love[] = _("love");
const u8 gUnknown_83FE859[] = _("  ");
const u8 gUnknown_83FE85C[] = _("\n");
const u8 gUnknown_83FE85E[] = _("\n");
const u8 gUnknown_83FE860[] = _(" is");
const u8 gUnknown_83FE864[] = _(" is");
const u8 gText_BadEgg[] = _("Bad EGG");
const u8 gUnknown_83FE870[] = _("ミツル");
const u8 gText_Win[] = _("{HIGHLIGHT 0}Win");
const u8 gText_Loss[] = _("{HIGHLIGHT 0}Loss");
const u8 gText_Draw[] = _("{HIGHLIGHT 0}Draw");
static const u8 sText_SpaceIs[] = _(" is");
static const u8 sText_ApostropheS[] = _("'s");
const u8 gNormal_movetype[] = _("a NORMAL move");
const u8 gFighting_movetype[] = _("a FIGHTING move");
const u8 gFlying_movetype[] = _("a FLYING move");
const u8 gPoison_movetype[] = _("a POISON move");
const u8 gGround_movetype[] = _("a GROUND move");
const u8 gRock_movetype[] = _("a ROCK move");
const u8 gBug_movetype[] = _("a BUG move");
const u8 gGhost_movetype[] = _("a GHOST move");
const u8 gSteel_movetype[] = _("a STEEL move");
const u8 gUnknown_movetype[] = _("a ??? move");
const u8 gFire_movetype[] = _("a FIRE move");
const u8 gWater_movetype[] = _("a WATER move");
const u8 gGrass_movetype[] = _("a GRASS move");
const u8 gElectric_movetype[] = _("an ELECTRIC move");
const u8 gPsychic_movetype[] = _("a PSYCHIC move");
const u8 gIce_movetype[] = _("an ICE move");
const u8 gDragon_movetype[] = _("a DRAGON move");
const u8 gDark_movetype[] = _("a DARK move");
const u8 gFairy_movetype[] = _("a FAIRY move"); //Fairy addition; make sure to add this in, where others are referenced.
const u8 gSound_movetype[] = _("a SOUND move");
const u8 gText_TimeBoard[] = _("TIME BOARD");
const u8 gText_ClearTime[] = _("CLEAR TIME"); // Unused
const u8 gText_XMinYZSec[] = _("{STR_VAR_1}MIN. {STR_VAR_2}.{STR_VAR_3}SEC.");
const u8 gUnknown_83FE9A9[] = _("1F");
const u8 gUnknown_83FE9AC[] = _("2F");
const u8 gUnknown_83FE9AF[] = _("3F");
const u8 gUnknown_83FE9B2[] = _("4F");
const u8 gUnknown_83FE9B5[] = _("5F");
const u8 gUnknown_83FE9B8[] = _("6F");
const u8 gUnknown_83FE9BB[] = _("7F");
const u8 gUnknown_83FE9BE[] = _("8F");

const u8 *const gTrainerTowerChallengeTypeTexts[NUM_TOWER_CHALLENGE_TYPES] = {
    gOtherText_Single,
    gOtherText_Double,
    gOtherText_Knockout,
    gOtherText_Mixed
};

const u8 gUnknown_83FE9D4[] = _("{PLAY_SE SE_FLEE}{B_TRAINER1_CLASS} {B_TRAINER1_NAME} fled!"); //
static const u8 sText_PlayerLostAgainstTrainer1[] = _("Player lost against\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("Player battled to a draw against\n{B_TRAINER1_CLASS} {B_TRAINER1_NAME}!");

static const u8 *const sATypeMove_Table[] = {
    gNormal_movetype,
    gFighting_movetype,
    gFlying_movetype,
    gPoison_movetype,
    gGround_movetype,
    gRock_movetype,
    gBug_movetype,
    gGhost_movetype,
    gSteel_movetype,
    gUnknown_movetype,
    gFire_movetype,
    gWater_movetype,
    gGrass_movetype,
    gElectric_movetype,
    gPsychic_movetype,
    gIce_movetype,
    gDragon_movetype,
    gDark_movetype,
    gFairy_movetype,
    gSound_movetype
};

//find out why this here
static const u16 sGrammarMoveUsedTable[] = {
    MOVE_SWORDS_DANCE,
    MOVE_STRENGTH,
    MOVE_GROWTH,
    MOVE_HARDEN,
    MOVE_MINIMIZE,
    MOVE_SMOKESCREEN,
    MOVE_WITHDRAW,
    MOVE_DEFENSE_CURL,
    MOVE_EGG_BOMB,
    MOVE_SMOG,
    MOVE_BONE_CLUB,
    MOVE_FLASH,
    MOVE_SPLASH,
    MOVE_ACID_ARMOR,
    MOVE_BONEMERANG,
    MOVE_REST,
    MOVE_SHARPEN,
    MOVE_SUBSTITUTE,
    MOVE_MIND_READER,
    MOVE_SNORE,
    MOVE_PROTECT,
    MOVE_SPIKES,
    MOVE_ENDURE,
    MOVE_ROLLOUT,
    MOVE_SWAGGER,
    MOVE_SLEEP_TALK,
    MOVE_HIDDEN_POWER,
    MOVE_PSYCH_UP,
    MOVE_EXTREME_SPEED,
    MOVE_FOLLOW_ME,
    MOVE_TRICK,
    MOVE_ASSIST,
    MOVE_INGRAIN,
    MOVE_KNOCK_OFF,
    MOVE_CAMOUFLAGE,
    MOVE_SPOOK,
    MOVE_ODOR_SLEUTH,
    MOVE_GRASS_WHISTLE,
    MOVE_SHEER_COLD,
    MOVE_MUDDY_WATER,
    MOVE_IRON_DEFENSE,
    MOVE_BOUNCE,
    MOVE_NONE,

    MOVE_TELEPORT,
    MOVE_RECOVER,
    MOVE_BIDE,
    MOVE_AMNESIA,
    MOVE_FLAIL,
    MOVE_TAUNT,
    MOVE_BULK_UP,
    MOVE_NONE,

    MOVE_MEDITATE,
    MOVE_AGILITY,
    MOVE_MIMIC,
    MOVE_DOUBLE_TEAM,
    MOVE_BARRAGE,
    MOVE_TRANSFORM,
    MOVE_STRUGGLE,
    MOVE_SCARY_FACE,
    MOVE_CHARGE,
    MOVE_WISH,
    MOVE_BRICK_BREAK,
    MOVE_YAWN,
    MOVE_FEATHER_DANCE,
    MOVE_TEETER_DANCE,
    MOVE_MUD_SPORT,
    MOVE_FAKE_TEARS,
    MOVE_WATER_SPORT,
    MOVE_CALM_MIND,
    MOVE_NONE,

    MOVE_POUND,
    MOVE_SCRATCH,
    MOVE_VICE_GRIP,
    MOVE_WING_ATTACK,
    MOVE_FLY,
    MOVE_BIND,
    MOVE_SLAM,
    MOVE_HORN_ATTACK,
    MOVE_WRAP,
    MOVE_THRASH,
    MOVE_TAIL_WHIP,
    MOVE_LEER,
    MOVE_BITE,
    MOVE_GROWL,
    MOVE_ROAR,
    MOVE_SING,
    MOVE_PECK,
    MOVE_ABSORB,
    MOVE_STRING_SHOT,
    MOVE_EARTHQUAKE,
    MOVE_FISSURE,
    MOVE_DIG,
    MOVE_TOXIC,
    MOVE_SCREECH,
    MOVE_METRONOME,
    MOVE_LICK,
    MOVE_CLAMP,
    MOVE_CONSTRICT,
    MOVE_POISON_GAS,
    MOVE_BUBBLE,
    MOVE_SLASH,
    MOVE_SPIDER_WEB,
    MOVE_NIGHTMARE,
    MOVE_CURSE,
    MOVE_FORESIGHT,
    MOVE_CHARM,
    MOVE_ATTRACT,
    MOVE_ROCK_SMASH,
    MOVE_UPROAR,
    MOVE_SPIT_UP,
    MOVE_SWALLOW,
    MOVE_TORMENT,
    MOVE_FLATTER,
    MOVE_ROLE_PLAY,
    MOVE_ENDEAVOR,
    MOVE_TICKLE,
    MOVE_COVET,
    MOVE_NONE
};

void BufferStringBattle(u32 battler, u16 stringId)
{
    s32 i;
    const u8 *stringPtr = NULL;

    sBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleResources->bufferA[battler][4]);
    gLastUsedItem = sBattleMsgDataPtr->lastItem;
    gLastUsedAbility = sBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = sBattleMsgDataPtr->scrActive;
    *(&gBattleStruct->scriptPartyIdx) = sBattleMsgDataPtr->bakScriptPartyIdx;
    *(&gBattleStruct->hpScale) = sBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = sBattleMsgDataPtr->itemEffectBattler;
    *(&gBattleStruct->stringMoveType) = sBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = sBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = sBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = sBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = sBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringId)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_GHOST)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_GHOST_UNVEILED)
                    stringPtr = sText_TheGhostAppeared;
                else
                    stringPtr = sText_GhostAppearedCantId;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_WildPkmnAppeared2;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) // interesting, looks like they had something planned for wild double battles
                stringPtr = sText_TwoWildPkmnAppeared;  //important
            else if (gBattleTypeFlags & BATTLE_TYPE_OLD_MAN_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = sText_GoTwoPkmn;
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_LINK)
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
                    stringPtr = sText_Trainer1SentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sText_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_PkmnOkComeBack;
            else
                stringPtr = sText_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sText_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_GoForItPkmn;
            else
                stringPtr = sText_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainerMultiSentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
                    stringPtr = sText_Trainer1SentOutPkmn2;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn2;
            }
            else
            {
                stringPtr = sText_Trainer1SentOutPkmn2;
            }
        }
        break;
    case STRINGID_USEDMOVE: // pokemon used a move msg
        ChooseMoveUsedParticle(gBattleTextBuff1); // buff1 doesn't appear in the string, leftover from japanese move names

        if (sBattleMsgDataPtr->currentMove >= MOVES_COUNT)
            StringCopy(gBattleTextBuff2, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        else
            GetMoveName(gBattleTextBuff2, sBattleMsgDataPtr->currentMove);

        ChooseTypeOfMoveUsedString(gBattleTextBuff2);
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(battler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
                stringPtr = gUnknown_83FE9D4;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (GetBattlerSide(battler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    default: // load a string from the table
        if (stringId >= STRINGID_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringId];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8* src)
{
    BattleStringExpandPlaceholders(src, gDisplayedStringBattle);
}

static const u8 *BattleStringGetOpponentNameByTrainerId(u16 trainerId, u8 *text, u8 multiplayerId, u8 battlerId)
{
    const u8 *toCpy;


    /*else if (trainerId == TRAINER_UNION_ROOM)
    {
        toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
    }*/
    if (trainerId == TRAINER_LINK_OPPONENT)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battlerId)].name;
        else
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battlerId) & BIT_SIDE].name;
    }
    /*else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CopyFrontierBrainTrainerName(text);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
    {
        GetFrontierTrainerName(text, trainerId);
        toCpy = text;
    }

    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
    {
        GetEreaderTrainerName(text);
        toCpy = text;
    }*/
    else
    {
        toCpy = gTrainers[trainerId].trainerName;
    }

    return toCpy;
}

static const u8 *BattleStringGetOpponentClassByTrainerId(u16 trainerId)
{
    const u8 *toCpy;

    /*if (trainerId == TRAINER_UNION_ROOM)
        toCpy = gTrainerClassNames[GetUnionRoomTrainerClass()];*/

    /*else if (trainerId == TRAINER_FRONTIER_BRAIN)
        toCpy = gTrainerClassNames[GetFrontierBrainTrainerClass()];

    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
        toCpy = gTrainerClassNames[GetFrontierOpponentClass(trainerId)];*/

    if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
        toCpy = gTrainerClassNames[GetEreaderTrainerClassId()];

    else
        toCpy = gTrainerClassNames[gTrainers[trainerId].trainerClass];

    return toCpy;
}

static const u8 *BattleStringGetOpponentName(u8 *text, u8 multiplayerId, u8 battlerId)
{
    const u8 *toCpy;

    switch (GetBattlerPosition(battlerId))
    {
    case B_POSITION_OPPONENT_LEFT:
        toCpy = BattleStringGetOpponentNameByTrainerId(gTrainerBattleOpponent_A, text, multiplayerId, battlerId);
        break;
    case B_POSITION_OPPONENT_RIGHT:
        if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI))// && !BATTLE_TWO_VS_ONE_OPPONENT)
            toCpy = BattleStringGetOpponentNameByTrainerId(gTrainerBattleOpponent_B, text, multiplayerId, battlerId);
        else
            toCpy = BattleStringGetOpponentNameByTrainerId(gTrainerBattleOpponent_A, text, multiplayerId, battlerId);
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetPlayerName(u8 *text, u8 battlerId)
{
    const u8 *toCpy;

    switch (GetBattlerPosition(battlerId))
    {
    case B_POSITION_PLAYER_LEFT:
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            toCpy = gLinkPlayers[0].name;
        else
            toCpy = gSaveBlock2Ptr->playerName;
        break;
    case B_POSITION_PLAYER_RIGHT:
        if (gBattleTypeFlags & BATTLE_TYPE_LINK && gBattleTypeFlags & (BATTLE_TYPE_RECORDED | BATTLE_TYPE_MULTI))
        {
            toCpy = gLinkPlayers[2].name;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        {
            //GetFrontierTrainerName(text, gPartnerTrainerId);
            //toCpy = text;
        }
        else
        {
            toCpy = gSaveBlock2Ptr->playerName;
        }
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetTrainerName(u8 *text, u8 multiplayerId, u8 battlerId)
{
    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        return BattleStringGetPlayerName(text, battlerId);
    else
        return BattleStringGetOpponentName(text, multiplayerId, battlerId);
}


static const u8* TryGetStatusString(u8 *src) //important
{
    u32 i;
    u8 status[] = _("$$$$$$$");
    u32 chars1, chars2;
    u8* statusPtr;

    statusPtr = status;
    for (i = 0; i < 8; i++)
    {
        if (*src == EOS)
            break;
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32*)(&status[0]);
    chars2 = *(u32*)(&status[4]);

    for (i = 0; i < NELEMS(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32*)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32*)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

static void GetBattlerNick(u32 battlerId, u8 *dst)
{
    struct Pokemon *mon, *illusionMon;
    u16 species;

    if (GET_BATTLER_SIDE(battlerId) == B_SIDE_PLAYER)
        mon = &gPlayerParty[gBattlerPartyIndexes[battlerId]];
    else
        mon = &gEnemyParty[gBattlerPartyIndexes[battlerId]];

    species = GetMonData(mon, MON_DATA_SPECIES);
    illusionMon = GetIllusionMonPtr(battlerId);
    
    if (illusionMon != NULL)
        mon = illusionMon;
    GetMonData(mon, MON_DATA_NICKNAME, dst);
    if (StringCompare(gBaseStats[species].speciesName, dst) == IDENTICAL) /*if not nicknamed reassign tempStr to speciesname, making it update capitalization*/\
        GetSpeciesName(dst, species);
    else
        StringGet_Nickname(dst);
}

#define HANDLE_NICKNAME_STRING_CASE(battlerId)                \
    if (GetBattlerSide(battlerId) != B_SIDE_PLAYER)                     \
    {                                                                   \
                                                                        \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
                                                                        \
    GetBattlerNick(battlerId, text);                                     \
     toCpy = text;/*StringAppend(text, sText_EndCap);   */              

    //above made and works to uncap long strings but is stop gap not real fix */ toCpy = text;

//vosnic need redo entire function smh
u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst, u32 dstSize) //logic for buffers thought had to match charmap.txt but apparently not
{                                                               //ok so,  the charmap matches the buffer value, not the name for some reason -__-
    u32 dstID = 0; // if they used dstID, why not use srcId as well?
    const u8 *toCpy = NULL;
    // This buffer may hold either the name of a trainer, Pokémon, or item.
    u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];
    u8 multiplayerId;
    u8 *textStart = &text[0]; //idk what is prob useful
    s32 i;
    u8 fontId = FONT_NORMAL;
    //prob won't need below cuz have functions for
    u8 side;
    struct Pokemon *party;
    u16 species;


    multiplayerId = GetMultiplayerId();

    // Clear destination first
    while (dstID < dstSize)
    {
        dst[dstID] = EOS;
        dstID++;
    }

    dstID = 0;
    while (*src != EOS)
    {
        if (*src == PLACEHOLDER_BEGIN)  //comb over this and battle messages, check difference in buffers used, between this and emerald expansion. 
        {   //for stuff that could work better
            src++;
            u32 classLength = 0;
            u32 nameLength = 0;
            const u8 *classString;
            const u8 *nameString;
            switch (*src)
            {
            case B_BUFF1:   //B_BUFF1
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_BUFF2:   //B_BUFF2
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                    toCpy = gBattleTextBuff2;
                break;
            case B_BUFF3:   //B_BUFF3
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                    toCpy = gBattleTextBuff3;
                break;
            case B_COPY_VAR_1:  //B_COPY_VAR_1
                toCpy = gStringVar1;
                break;
            case B_COPY_VAR_2:  //B_COPY_VAR_2
                toCpy = gStringVar2;
                break;
            case B_COPY_VAR_3:  //B_COPY_VAR_3
                toCpy = gStringVar3;
                break;
            case B_PLAYER_MON1_NAME: // B_PLAYER_MON1_NAME  first player poke name
            GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), text);
                toCpy = text;
                /*GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_OPPONENT_MON1_NAME: //B_OPPONENT_MON1_NAME   first enemy poke name
            GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), text);
                toCpy = text;
                /*GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_PLAYER_MON2_NAME: //B_PLAYER_MON2_NAME   second player poke name
            GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT), text);
                toCpy = text;
                /*GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_OPPONENT_MON2_NAME: //B_OPPONENT_MON2_NAME   second enemy poke name
            GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), text);
                toCpy = text;
                /*GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_LINK_PLAYER_MON1_NAME: //B_LINK_PLAYER_MON1_NAME     link first player poke name
            GetBattlerNick(GetBattlerAtPosition(gLinkPlayers[multiplayerId].id), text);
                toCpy = text;
                /*GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_LINK_OPPONENT_MON1_NAME: //B_LINK_OPPONENT_MON1_NAME   link first opponent poke name
            GetBattlerNick(GetBattlerAtPosition(gLinkPlayers[multiplayerId].id ^ 1), text);
                toCpy = text;
                /*GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 1]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_LINK_PLAYER_MON2_NAME: //B_LINK_PLAYER_MON2_NAME     link second player poke name
            GetBattlerNick(GetBattlerAtPosition(gLinkPlayers[multiplayerId].id ^ 2), text);
                toCpy = text;
                /*GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 2]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_LINK_OPPONENT_MON2_NAME: //B_LINK_OPPONENT_MON2_NAME     link second opponent poke name
            GetBattlerNick(GetBattlerAtPosition(gLinkPlayers[multiplayerId].id ^ 3), text);
                toCpy = text;
                /*GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 3]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;*/
                break;
            case B_ATK_NAME_WITH_PREFIX_MON1: //B_ATK_NAME_WITH_PREFIX_MON1  only battlerId 0/1
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker) //not used in emerald, ssee if remove
                break;  //dont need to text is fixed, issue was things were using this macro that didn't
            case B_ATK_PARTNER_NAME: //B_ATK_PARTNER_NAME
            //HANDLE_NICKNAME_STRING_CASE(GetBattlerAtPosition(BATTLE_PARTNER(gBattlerAttacker))) //think this is right?
            GetBattlerNick(BATTLE_PARTNER(gBattlerAttacker), text);
                /*if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    
                    GetMonData(
                        &gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) +
                                                           2]], MON_DATA_NICKNAME, text);
                else
                    GetMonData(
                        &gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) +
                                                          2]], MON_DATA_NICKNAME, text);

                StringGet_Nickname(text);*/
                toCpy = text;
                break;
            case B_ATK_NAME_WITH_PREFIX: //B_ATK_NAME_WITH_PREFIX
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker)
                break;
            case B_DEF_NAME_WITH_PREFIX: //B_DEF_NAME_WITH_PREFIX
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget)
                break;
            case B_EFF_NAME_WITH_PREFIX: //B_EFF_NAME_WITH_PREFIX
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler)
                break;
            case B_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler)
                break;
            case B_CURRENT_MOVE: //B_CURRENT_MOVE
                if (sBattleMsgDataPtr->currentMove >= MOVES_COUNT)
                    toCpy = (const u8 *)&sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                {
                    GetMoveName(gStringVar3, sBattleMsgDataPtr->currentMove);
                    toCpy = gStringVar3;
                }                    
                break;
            case B_LAST_MOVE: //B_LAST_MOVE  originally used move name
                if (sBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT)
                    toCpy = (const u8 *)&sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                {
                    GetMoveName(gStringVar4, sBattleMsgDataPtr->originallyUsedMove);
                    toCpy = gStringVar4;                    
                }
                break;
            case B_LAST_ITEM: //B_LAST_ITEM  last used item
                if (gBattleTypeFlags & BATTLE_TYPE_LINK)
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleStruct->multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleStruct->multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleStruct->multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                                toCpy = sText_EnigmaBerry;
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;            
            case B_LAST_ABILITY: //B_LAST_ABILITY    last used ability
                //toCpy = gAbilityNames[gLastUsedAbility];
                GetAbilityName(text, gLastUsedAbility);
                toCpy = text;
                break;
            case B_ATK_ABILITY: //B_ATK_ABILITY
                //toCpy = gAbilityNames[sBattlerAbilities[gBattlerAttacker]]; 
                GetAbilityName(text, sBattlerAbilities[gBattlerAttacker]);
                toCpy = text;
                break;
            case B_DEF_ABILITY: //B_DEF_ABILITY
                //toCpy = gAbilityNames[sBattlerAbilities[gBattlerTarget]];
                GetAbilityName(text, sBattlerAbilities[gBattlerTarget]);
                toCpy = text;
                break;
            case B_SCR_ACTIVE_ABILITY: //B_SCR_ACTIVE_ABILITY  scripting active ability
                //toCpy = gAbilityNames[sBattlerAbilities[gBattleScripting.battler]];
                GetAbilityName(text, sBattlerAbilities[gBattleScripting.battler]);
                toCpy = text;
                break;
            case B_EFF_ABILITY: //B_EFF_ABILITY  effect battlerId ability
                //toCpy = gAbilityNames[sBattlerAbilities[gEffectBattler]];
                GetAbilityName(text, sBattlerAbilities[gEffectBattler]);
                toCpy = text;
                break;
            case B_TRAINER1_CLASS: //B_TRAINER1_CLASS   trainer class name
                /*if (gTrainerBattleOpponent_A == SECRET_BASE_OPPONENT)
                    toCpy = gTrainerClassNames[GetSecretBaseTrainerNameIndex()];
                else */if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
                    toCpy = gTrainerClassNames[GetUnionRoomTrainerClass()];
                else if (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
                    toCpy = gTrainerClassNames[GetBattleTowerTrainerClassNameId()];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
                    toCpy = gTrainerClassNames[GetTrainerTowerOpponentClass()];
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                    toCpy = gTrainerClassNames[GetEreaderTrainerClassId()];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_A].trainerClass];
                break;
            case B_TRAINER1_NAME: //B_TRAINER1_NAME  trainer1 name
                /*if (gTrainerBattleOpponent_A == SECRET_BASE_OPPONENT)
                {
                    for (i = 0; i < (s32)NELEMS(gBattleResources->secretBase->trainerName); i++)
                        text[i] = gBattleResources->secretBase->trainerName[i];
                    text[i] = EOS;
                    toCpy = text;
                }*/
                if (gTrainerBattleOpponent_A == TRAINER_OPPONENT_C00)
                {
                    toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
                {
                    GetBattleTowerTrainerName(text);
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
                {
                    GetTrainerTowerOpponentName(text);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                {
                    CopyEReaderTrainerName5(text);
                    toCpy = text;
                }
                else
                {
                    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == CLASS_RIVAL
                     || gTrainers[gTrainerBattleOpponent_A].trainerClass == CLASS_RIVAL_2
                     || gTrainers[gTrainerBattleOpponent_A].trainerClass == CLASS_CHAMPION_2)
                        toCpy = GetExpandedPlaceholder(PLACEHOLDER_ID_RIVAL);
                    else
                        toCpy = gTrainers[gTrainerBattleOpponent_A].trainerName;// can prob use this to save value for custom mon
                }//i.e the custom starter unlelss its already working  save value pull value type thing
                break;
            case B_LINK_PLAYER_NAME: //B_LINK_PLAYER_NAME
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_LINK_PARTNER_NAME: //B_LINK_PARTNER_NAME
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_LINK_OPPONENT1_NAME: //B_LINK_OPPONENT1_NAME
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_LINK_OPPONENT2_NAME: //B_LINK_OPPONENT2_NAME
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(
                    BATTLE_PARTNER(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id)))].name;
                break;
            case B_LINK_SCR_TRAINER_NAME: //B_LINK_SCR_TRAINER_NAME  link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_PLAYER_NAME: //B_PLAYER_NAME
                toCpy = gSaveBlock2Ptr->playerName;
                /*if (toCpy != text && *toCpy != CHAR_FIXED_CASE && !(*src & PLACEHOLDER_FIXED_MASK)) {
                    *text = CHAR_MISC_CAP;
                    StringCopyN(text+1, toCpy, PLAYER_NAME_LENGTH + 1);
                    toCpy = text;*/
                break;
            case B_TRAINER1_LOSE_TEXT: //B_TRAINER1_LOSE_TEXT
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
                {
                    GetTrainerTowerOpponentLoseText(gStringVar4, 0);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TRAINER1_WIN_TEXT: //B_TRAINER1_WIN_TEXT
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
                {
                    GetTrainerTowerOpponentWinText(gStringVar4, 0);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerWonSpeech();
                }
                break;
            case B_TRAINER2_LOSE_TEXT:  //B_TRAINER2_LOSE_TEXT
                GetTrainerTowerOpponentLoseText(gStringVar4, 1);
                toCpy = gStringVar4;
                break;
            case B_TRAINER2_WIN_TEXT:   //B_TRAINER2_WIN_TEXT
                GetTrainerTowerOpponentWinText(gStringVar4, 1);
                toCpy = gStringVar4;
                break;
            case B_26: //B_26   don't know what for?
               // HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, *(&gBattleStruct->scriptPartyIdx))
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler)
                break;
            case B_PC_CREATOR_NAME: //B_PC_CREATOR_NAME lanette pc
                if (FlagGet(FLAG_SYS_UPDATED_PC))
                    toCpy = sText_Bills;
                else
                    toCpy = sText_Someones;
                break;
            case B_ATK_PREFIX1: //B_ATK_PREFIX1
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_DEF_PREFIX1: //B_DEF_PREFIX1
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_ATK_PREFIX2: //B_ATK_PREFIX2
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_DEF_PREFIX2: //B_DEF_PREFIX2
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_ATK_PREFIX3: //B_ATK_PREFIX3
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_DEF_PREFIX3: //B_DEF_PREFIX3
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break; 
            case B_TRAINER2_CLASS:  //B_TRAINER2_CLASS
                toCpy = BattleStringGetOpponentClassByTrainerId(gTrainerBattleOpponent_B);
                break;
            case B_TRAINER2_NAME:   //B_TRAINER2_NAME
                toCpy = BattleStringGetOpponentNameByTrainerId(gTrainerBattleOpponent_B, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                break;
            case B_PARTNER_CLASS:   //B_PARTNER_CLASS
                //toCpy = gTrainerClassNames[GetFrontierOpponentClass(gPartnerTrainerId)];
                break;//prob need to add back when I get around to adding fronteir stuff but no partners in base game
            case B_PARTNER_NAME:    //B_PARTNER_NAME
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                break;
            case B_ATK_TRAINER_NAME:    //B_ATK_TRAINER_NAME
                toCpy = BattleStringGetTrainerName(text, multiplayerId, gBattlerAttacker);
                break;
            case B_ATK_TRAINER_CLASS:   //B_ATK_TRAINER_CLASS //messes w player formatting so shifted, remove space append space when actually using 
                switch (GetBattlerPosition(gBattlerAttacker))
                {
                case B_POSITION_PLAYER_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                       // toCpy = gTrainerClassNames[GetFrontierOpponentClass(gPartnerTrainerId)];  not in default game so hod off for now
                    toCpy = BattleStringGetOpponentClassByTrainerId(gPartnerTrainerId);
                    StringCopy(text, toCpy);
                    StringAppend(text, sText_space);
                    toCpy = text;
                    break;//until fronteir inclusion
                case B_POSITION_OPPONENT_LEFT:
                    toCpy = BattleStringGetOpponentClassByTrainerId(gTrainerBattleOpponent_A);
                    StringCopy(text, toCpy);
                    StringAppend(text, sText_space);
                    toCpy = text;
                    break;
                case B_POSITION_OPPONENT_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)// && !BATTLE_TWO_VS_ONE_OPPONENT)
                        toCpy = BattleStringGetOpponentClassByTrainerId(gTrainerBattleOpponent_B);
                    else
                        toCpy = BattleStringGetOpponentClassByTrainerId(gTrainerBattleOpponent_A);
                    StringCopy(text, toCpy);
                    StringAppend(text, sText_space);
                    toCpy = text;
                    break;//hopefully these work, vsonic need test
                }
                break;
            case B_TRAINER1_NAME_WITH_CLASS: // trainer1 name with trainer class
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_ATK_TEAM1:   //B_ATK_TEAM1
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_ATK_TEAM2:   //B_ATK_TEAM2
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_DEF_NAME: // B_DEF_NAME  target name kinda replacement for B_OPPONENT_MON1_NAME  that can just read the target, over just 1 battler
                GetBattlerNick(gBattlerTarget, text);     //which if I setup corrctly I think could be used to more easily adapt mon caught for wild doubles need test
                toCpy = text;
                break;
            case B_DEF_TEAM1:   //B_DEF_TEAM1
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Opposing1;
                else
                    toCpy = sText_Your1;
                break;
            case B_DEF_TEAM2:   //B_DEF_TEAM2
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Opposing2;
                else
                    toCpy = sText_Your2;
                break;
            case B_EFF_TEAM1:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_EFF_TEAM2:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_ATK_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerAttacker)
                break;
            case B_DEF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerTarget)
                break;
            case B_EFF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gEffectBattler)
                break;
            case B_SCR_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattleScripting.battler)
                break;
            }

            // missing if (toCpy != NULL) check
            //while (*toCpy != EOS && toCpy != NULL)
            if (toCpy != NULL)
            {
            while (*toCpy != EOS)
            {
                dst[dstID] = *toCpy;
                dstID++;
                toCpy++;
            }
            }
            if (*src == B_TRAINER1_LOSE_TEXT || *src == B_TRAINER1_WIN_TEXT
             || *src == B_TRAINER2_LOSE_TEXT || *src == B_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = 9;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    return dstID;
}

static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcId = 1;
    u32 value = 0;
    //u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];    //used to copy these values to that use b_buff_1/2/3  needs to be large enough to hold all  the length constants. name length is 12, but move name & ability name are longers so make 20
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 hword;

    *dst = EOS;
    while (src[srcId] != B_BUFF_EOS)
    {
        switch (src[srcId])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcId + 1]);
            StringAppend(dst, gBattleStringsTable[hword]);
            srcId += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcId + 1])
            {
            case 1:
                value = src[srcId + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcId + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcId + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcId + 2]);
            srcId += src[srcId + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            GetMoveName(gStringVar3, T1_READ_16(&src[srcId + 1]));
            StringAppend(dst, gStringVar3);
            srcId += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypesInfo[src[srcId + 1]].name);
            srcId += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
        {
            u8 side = GetBattlerSide(src[srcId + 1]);
            struct Pokemon *party = (side == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;

            if (side == B_SIDE_PLAYER)
            {
                GetMonData(&gPlayerParty[src[srcId + 2]], MON_DATA_NICKNAME, nickname);
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                    StringAppend(dst, sText_FoePkmnPrefix);
                else
                    StringAppend(dst, sText_WildPkmnPrefix);

                GetMonData(&gEnemyParty[src[srcId + 2]], MON_DATA_NICKNAME, nickname);
            } //think overflow issue came from this, bellsprout is at 13 w + 6 from this its at 21 above text buffer
            
            if (StringCompare(gBaseStats[GetMonData(&party[src[srcId + 2]], MON_DATA_SPECIES)].speciesName, nickname) == IDENTICAL) //if not nicknamed reassign tempStr to speciesname, making it update capitalization
                GetSpeciesName(nickname, GetMonData(&party[src[srcId + 2]], MON_DATA_SPECIES));
            else
                StringGet_Nickname(nickname);
                
            StringAppend(dst, nickname);
            srcId += 3;
        }
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcId + 1]]);
            srcId += 2;
            break;
        case B_BUFF_SPECIES: // species name
            GetSpeciesName(dst, T1_READ_16(&src[srcId + 1]));
            srcId += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix   //used in buffers PREPARE_MON_NICK_BUFFER
            GetBattlerNick(src[srcId + 1], dst);
            srcId += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcId + 1]]);
            srcId += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            //StringAppend(dst, gAbilityNames[src[srcId + 1]]); //idk how I missed replacing this?
            GetAbilityName(dst, T1_READ_16(&src[srcId + 1]));
            srcId += 3;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcId + 1]);
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
            {
                if (hword == ITEM_ENIGMA_BERRY)
                {
                    if (gLinkPlayers[gBattleStruct->multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcId += 3;
            break;
        }
    }
}

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "は" or "の") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void ChooseMoveUsedParticle(u8* textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == sBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sText_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sText_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "を つかった！". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "した！". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "を した！" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " こうげき！" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void ChooseTypeOfMoveUsedString(u8* dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == sBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sText_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sText_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sText_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sText_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sText_ExclamationMark5);
        break;
    }
}

//used by BattlePutTextOnWindow formats the text within the window IDs
//this is only the text not where the text is displayed within its individual window 
//each constant refers to a windowID that is the window/area for each value within the main window/border of the menu
static const struct BattleWindowText sTextOnWindowsInfo_Normal[] = {
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xf),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xf),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL_COPY_1,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_SMALL,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_SMALL,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_SMALL,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_SMALL,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_SMALL,
        .x = 3,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },// since these are my values within my window if I want to left or right align my text it should use the .x value from here!
    //x value of 0 is left aligned
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL_COPY_1,
        .x = 4,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 9,
        .bgColor = 14,
        .shadowColor = 10,
    },//.x value is probalby not 1 to 1 with window width as width of pp is 5, but x value is 10
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xe),//set to 0x0 to better see window border set back to 0xe when done adjusting
        .fontId = FONT_SMALL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL_COPY_1,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL_COPY_1,
        .x = 4,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 0,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_SMALL,
        .x = 0x20,
        .y = 0,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 2,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 2,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xe),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 2,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 0,
        .shadowColor = 6,
    },
    [B_WIN_OAK_OLD_MAN] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_MALE,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    }
};

const u8 gUnknown_83FEC90[] = {0x04, 0x05, 0x02, 0x02};

// windowId: Upper 2 bits are text flags
//   x40: Use NPC context-defined font
//   x80: Inhibit window clear
void BattlePutTextOnWindow(const u8 *text, u8 windowId) {
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;
    int x;
    u8 context;

    u8 textFlags = windowId & 0xC0;
    windowId &= 0x3F;
    if (!(textFlags & 0x80))
        FillWindowPixelBuffer(windowId, sTextOnWindowsInfo_Normal[windowId].fillValue);
    if (textFlags & 0x40) {
        context = ContextNpcGetTextColor();
        printerTemplate.fontId = gUnknown_83FEC90[context];
    }
    else {
        printerTemplate.fontId = sTextOnWindowsInfo_Normal[windowId].fontId;
    }

    if (B_WIN_MOVE_NAME_1 <= windowId && windowId <= B_WIN_MOVE_NAME_4)
    {
        // We cannot check the actual width of the window because
        // B_WIN_MOVE_NAME_1 and B_WIN_MOVE_NAME_3 are 16 wide for
        // Z-move details.
        /*if (gBattleStruct->zmove.viewing && windowId == B_WIN_MOVE_NAME_1)
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 16 * TILE_WIDTH);
        else*/
        //i'm not using z moves so should be able to get actual width here
        printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, sStandardBattleWindowTemplates[windowId].width * TILE_WIDTH);
    }

    switch (windowId)
    {
    case B_WIN_VS_PLAYER:
    case B_WIN_VS_OPPONENT:
    case B_WIN_VS_MULTI_PLAYER_1:
    case B_WIN_VS_MULTI_PLAYER_2:
    case B_WIN_VS_MULTI_PLAYER_3:
    case B_WIN_VS_MULTI_PLAYER_4:
        x = (48 - GetStringWidth(sTextOnWindowsInfo_Normal[windowId].fontId, text,
                                 sTextOnWindowsInfo_Normal[windowId].letterSpacing)) / 2;
        break;
    case B_WIN_VS_OUTCOME_DRAW:
    case B_WIN_VS_OUTCOME_LEFT:
    case B_WIN_VS_OUTCOME_RIGHT:
        x = (64 - GetStringWidth(sTextOnWindowsInfo_Normal[windowId].fontId, text,
                                 sTextOnWindowsInfo_Normal[windowId].letterSpacing)) / 2;
        break;
    default:
        x = sTextOnWindowsInfo_Normal[windowId].x;
        break;
    }
    if (x < 0)
        x = 0;
    printerTemplate.currentChar = text;
    printerTemplate.windowId = windowId;
    printerTemplate.x = x;
    printerTemplate.y = sTextOnWindowsInfo_Normal[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = sTextOnWindowsInfo_Normal[windowId].letterSpacing;
    printerTemplate.lineSpacing = sTextOnWindowsInfo_Normal[windowId].lineSpacing;
    printerTemplate.accentColor = 0;
    printerTemplate.fgColor = sTextOnWindowsInfo_Normal[windowId].fgColor;
    printerTemplate.bgColor = sTextOnWindowsInfo_Normal[windowId].bgColor;
    printerTemplate.shadowColor = sTextOnWindowsInfo_Normal[windowId].shadowColor;
    if (windowId == B_WIN_OAK_OLD_MAN)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if ((gBattleTypeFlags & BATTLE_TYPE_LINK) || ((gBattleTypeFlags & BATTLE_TYPE_POKEDUDE) && windowId != B_WIN_OAK_OLD_MAN))
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == B_WIN_OAK_OLD_MAN)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_LINK)
            speed = OPTIONS_TEXT_SPEED_FASTER; //1 is text speed mid, link batles are ungodly slow so think will shift this
        else
            speed = GetPlayerBattleTextSpeedDelay(); //if this is only speed variable think will make function specific for this
        gTextFlags.canABSpeedUpPrint = TRUE;
    }
    else
    {
        speed = sTextOnWindowsInfo_Normal[windowId].speed;
        gTextFlags.canABSpeedUpPrint = FALSE;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);
    if (!(textFlags & 0x80))
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_BOTH);
    }
}

bool8 BattleStringShouldBeColored(u16 stringId)
{
    if (stringId == STRINGID_TRAINER1LOSETEXT || stringId == STRINGID_TRAINER2CLASS || stringId == STRINGID_TRAINER1WINTEXT || stringId == STRINGID_TRAINER2NAME)
        return TRUE;
    return FALSE;
}

void SetPpNumbersPaletteInMoveSelection(u32 battler)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[battler]],
                                      chooseMoveStruct->maxPp[gMoveSelectionCursor[battler]]);

    gPlttBufferUnfaded[92] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[91] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[92], &gPlttBufferFaded[92], sizeof(u16));
    CpuCopy16(&gPlttBufferUnfaded[91], &gPlttBufferFaded[91], sizeof(u16));
}

void SetMoveTypePaletteInMoveSelection_Singles(u32 battler, u16 move, u8 moveType)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct*)(&gBattleResources->bufferA[battler][4]);
    const u16 *palPtr = gMoveTypePal;
    u8 var = GetTypeEffectivenessState_Singles(battler, move, moveType);//hopefully I understood this correctly

    //takes state and shift to return different
    //value in pal gPPTextPalette
    //simple fix make new palette 
    //way its setup whatever foreground is
    //shadow will be 1 color above

    if (!IsDisplayTypeEffectivenessOn())
        var = 0;


    gPlttBufferUnfaded[89] = palPtr[(var) + 0]; //foreground color
    gPlttBufferUnfaded[90] = palPtr[(var) + 1]; //shadow color
    //uses palette 5, 16 values in a palette
    //so start value is 80,
    //important parts of text are shadow color and fg color
    //find those based on relevenat window /B_WIN_PP uses 11 and 12 for those
    //which when added to 80 are 91 & 92 respectively

    //for move  type window those values are 15 & 13 also palette 5
    //so I need 95 and 93
    //changed colors as needed value that wasn't used elsewhere
    //in battle menu

    CpuCopy16(&gPlttBufferUnfaded[89], &gPlttBufferFaded[89], sizeof(u16));
    CpuCopy16(&gPlttBufferUnfaded[90], &gPlttBufferFaded[90], sizeof(u16));

}

//reorganized pallete so targetting works 
//for dual target make return highest effectiveness of enemy mon hit
//i.e return based on priority, normal effect at bottom,
//w incrasing resist as it rises w super at the top
//last thing believe need try take into account is move target random, 
//not sure will work for now
//for some reason doubles check isn't working?
void SetMoveTypePaletteInMoveSelection_Doubles(u32 battler, u16 move, u8 moveType)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct*)(&gBattleResources->bufferA[battler][4]);
    const u16 *palPtr = gMoveTypePal;
    u8 var; //hopefully I understood this correctly
    
    if (gMovesInfo[move].target == TARGET_USER
    || gMovesInfo[move].target == TARGET_OPPONENTS_FIELD
    || !IsDisplayTypeEffectivenessOn())
        var = 0;
    else if (gMovesInfo[move].target == TARGET_BOTH 
    || gMovesInfo[move].target == TARGET_ALL_BATTLERS
    || gMovesInfo[move].target == TARGET_FOES_AND_ALLY)
        var = max(GetTypeEffectivenessState_Doubles(move,moveType, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)), GetTypeEffectivenessState_Doubles(move,moveType, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)));
    else if (gMovesInfo[move].target == TARGET_RANDOM)
    {
        if (Random() & 1)
            var = GetTypeEffectivenessState_Doubles(move,moveType, GetBattlerPosition(B_POSITION_OPPONENT_LEFT));
        else
            var = GetTypeEffectivenessState_Doubles(move,moveType, GetBattlerPosition(B_POSITION_OPPONENT_RIGHT));
    }//best I can do is guess
    else
        var = GetTypeEffectivenessState_Doubles(move,moveType, GetBattlerPosition(gMultiUsePlayerCursor));
    //takes state and shift to return different
    //value in pal gPPTextPalette
    //simple fix make new palette 
    //way its setup whatever foreground is
    //shadow will be 1 color above


    gPlttBufferUnfaded[89] = palPtr[(var) + 0]; //foreground color
    gPlttBufferUnfaded[90] = palPtr[(var) + 1]; //shadow color
    //uses palette 5, 16 values in a palette
    //so start value is 80,
    //important parts of text are shadow color and fg color
    //find those based on relevenat window /B_WIN_PP uses 11 and 12 for those
    //which when added to 80 are 91 & 92 respectively

    //for move  type window those values are 15 & 13 also palette 5
    //so I need 95 and 93
    //changed colors as needed value that wasn't used elsewhere
    //in battle menu

    CpuCopy16(&gPlttBufferUnfaded[89], &gPlttBufferFaded[89], sizeof(u16));
    CpuCopy16(&gPlttBufferUnfaded[90], &gPlttBufferFaded[90], sizeof(u16));

}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}//used with color palette 3 is normal font color
//1 is  yellow, 2 is red  //correspondes to value in palette

u8 GetTypeEffectivenessState_Singles(u32 battler, u16 move, u8 moveType) //for singles
{
    if (!IsDoubleBattle()) //oddly gbattlertarget is same as attacker at this point without this
    {    gBattlerTarget = (GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerPosition(battler))));
        //gBattlerAttacker = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    }
    //else
    //    return 0;
    if (gMovesInfo[move].target == TARGET_USER
    || gMovesInfo[move].target == TARGET_OPPONENTS_FIELD
    || !IsDisplayTypeEffectivenessOn())
        return 0; //initially forgot this part for self target moves

    if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, gBattlerTarget, FALSE) == UQ_4_12(1.0))
    {
        return 0; //default color
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, gBattlerTarget, FALSE) >= UQ_4_12(1.55))
    {
       return 13; //green //if I want to return the greatest need exchange place of this and 13
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, gBattlerTarget, FALSE) == UQ_4_12(0.0))
    {
       return 8; //grey
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, gBattlerTarget, FALSE) == UQ_4_12(0.775))
    {
       return 2; //yellow
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, gBattlerTarget, FALSE) <= UQ_4_12(0.5))
    {
       return 6; //red
    }
    
    return 0; //needed for modern I think
}

//decide targetId with loop
u8 GetTypeEffectivenessState_Doubles(u16 move, u8 moveType, u8 targetId) //for doubles
{


    if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, targetId, FALSE) == UQ_4_12(1.0))
    {
        return 0; //defautl color
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, targetId, FALSE) >= UQ_4_12(1.55))
    {
       return 13; //green
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, targetId, FALSE) == UQ_4_12(0.0))
    {
       return 8; //grey
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, targetId, FALSE) == UQ_4_12(0.775))
    {
       return 2; //yellow
    }
    else if (CalcTypeEffectivenessMultiplier(move, moveType, gBattlerAttacker, targetId, FALSE) <= UQ_4_12(0.5))
    {
       return 6; //red
    }
    
    return 0; //needed for modern I think
}