#include "global.h"
#include "gflib.h"
#include "item.h"
#include "util.h"
#include "random.h"
#include "pokedex.h"
#include "money.h"
#include "pokemon_icon.h"
#include "mail.h"
#include "event_data.h"
#include "strings.h"
#include "pokemon_special_anim.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary_screen.h"
#include "task.h"
#include "naming_screen.h"
#include "overworld.h"
#include "party_menu.h"
#include "trainer_pokemon_sprites.h"
#include "field_specials.h"
#include "pokemon.h"
#include "new_menu_helpers.h"
#include "battle.h"
#include "battle_message.h"
#include "battle_anim.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "battle_scripts.h"
#include "battle_string_ids.h"
#include "reshow_battle_screen.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "constants/battle_anim.h"
#include "constants/battle_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/items.h"
#include "constants/hold_effects.h"
#include "constants/songs.h"
#include "constants/moves.h"
#include "constants/abilities.h"
#include "constants/pokemon.h"
#include "constants/maps.h"

#define DEFENDER_IS_PROTECTED ((gProtectStructs[gBattlerTarget].protected) && (gBattleMoves[gCurrentMove].flags & FLAG_PROTECT_AFFECTED))

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
#define CMD_ARGS(...) const struct __attribute__((packed)) { u8 opcode; MEMBERS(__VA_ARGS__) const u8 nextInstr[0]; } *const cmd  = (const void *)gBattlescriptCurrInstr
#define VARIOUS_ARGS(...) CMD_ARGS(u8 battler, u8 id, ##__VA_ARGS__)
#define NATIVE_ARGS(...) CMD_ARGS(void (*func)(void), ##__VA_ARGS__)
//cmd args used for battle script commands
//various used for varios commands/args
//native args used in place of cmd args for native args/commands which is a cmd arg that uses call native to call a function and lists its arguements as well.
//native is best option, as it is the best of both worlds of cmd args and various args, in that it calls logic to be used, and is all from a single byte, rather bypassing the limit of 255 commands 
//but doesn't have the issue of various where you have to use a switch case and write the logic there explicitly.
//you can just make a function and call it, cleanly elsewhere.

#define MEMBERS(...) VARARG_8(MEMBERS_, __VA_ARGS__)
#define MEMBERS_0()
#define MEMBERS_1(a) a;
#define MEMBERS_2(a, b) a; b;
#define MEMBERS_3(a, b, c) a; b; c;
#define MEMBERS_4(a, b, c, d) a; b; c; d;
#define MEMBERS_5(a, b, c, d, e) a; b; c; d; e;
#define MEMBERS_6(a, b, c, d, e, f) a; b; c; d; e; f;
#define MEMBERS_7(a, b, c, d, e, f, g) a; b; c; d; e; f; g;
#define MEMBERS_8(a, b, c, d, e, f, g, h) a; b; c; d; e; f; g; h;

//started to understand it, put here for future reference and ease of porting future emerald stuff

extern const u8 *const gBattleScriptsForBattleEffects[];

static bool8 IsTwoTurnsMove(u16 move);
static void TrySetDestinyBondToHappen(void);
static void CheckWonderGuardAndLevitate(void);//attempted replace, not currently using, attempt using emerald equivalent CalcTypeEffectivenessMultiplier need test,then can remove funtion
static u32 ChangeStatBuffs(s8 statValue, u32 statId, u32 flags, const u8 *BS_ptr);
static void sub_8026480(void);
static bool8 sub_80264D0(void);
static void DrawLevelUpWindow1(void);
static void DrawLevelUpWindow2(void);
static bool8 sub_8026648(void);
static void PutMonIconOnLvlUpBox(void);
static void PutLevelAndGenderOnLvlUpBox(void);
static bool32 HasAttackerFaintedTarget(void);
static void HandleTerrainMove(u32 moveEffect);
//static void RecalcBattlerStats(u32 battler, struct Pokemon *mon);  old setup can use emerald version non static now
static void TransformRecalcBattlerStats(u32 battler, struct Pokemon *mon, u16 TargetAbility, u16 TransformSpecies);
static void SetDmgHazardsBattlescript(u8 battlerId, u8 multistringId);
//since its not static
static bool8 IsBattlerProtected(u8 battlerId, u16 move);//gabe me compiler double definition error so made static
//static void ProtectBreak(void); add back later when I figure it out
static u8 WeightBoostedDamageFormula(void); //new seismic toss boost
static bool32 ChangeOrderTargetAfterAttacker(void);
static bool32 TrySetTargetToNextPursuiter(u32 battlerDef);

static void SpriteCB_MonIconOnLvlUpBox(struct Sprite *sprite);

static void atk00_attackcanceler(void); //all commands must be ordered in .inc file
static void atk01_accuracycheck(void);
static void atk02_attackstring(void);
static void atk03_ppreduce(void);
static void atk04_critcalc(void);
static void atk05_damagecalc(void);
static void atk06_typecalc(void);
static void atk07_adjustnormaldamage(void);
static void atk08_adjustnormaldamage2(void);
static void atk09_attackanimation(void);
static void atk0A_waitanimation(void);
static void atk0B_healthbarupdate(void);
static void atk0C_datahpupdate(void);
static void atk0D_critmessage(void);
static void atk0E_effectivenesssound(void);
static void atk0F_resultmessage(void);
static void atk10_printstring(void);
static void atk11_printselectionstring(void);
static void atk12_waitmessage(void);
static void atk13_printfromtable(void);
static void atk14_printselectionstringfromtable(void);
static void atk15_setmoveeffectwithchance(void);
static void atk16_seteffectprimary(void);
static void atk17_seteffectsecondary(void);
static void atk18_clearstatusfromeffect(void);
static void atk19_tryfaintmon(void);
static void atk1A_dofaintanimation(void);
static void atk1B_cleareffectsonfaint(void);
static void atk1C_jumpifstatus(void);
static void atk1D_jumpifstatus2(void);
static void atk1E_jumpbasedonability(void);
static void atk1F_jumpifsideaffecting(void);
static void atk20_jumpifstat(void);
static void atk21_jumpifstatus3condition(void);
static void atk22_jumpbasedontype(void);
static void atk23_getexp(void);
static void atk24_confirmlosingteam(void);
static void atk25_movevaluescleanup(void);
static void atk26_setmultihit(void);    //mostly unused just used for pursuit for some reason so kept
static void atk27_decrementmultihit(void);
static void atk28_goto(void);
static void atk29_jumpifbyte(void);
static void atk2A_jumpifhalfword(void);
static void atk2B_jumpifword(void);
static void atk2C_jumpifarrayequal(void);
static void atk2D_jumpifarraynotequal(void);
static void atk2E_setbyte(void);
static void atk2F_addbyte(void);
static void atk30_subbyte(void);
static void atk31_copyarray(void);
static void atk32_copyarraywithindex(void);
static void atk33_orbyte(void);
static void atk34_orhalfword(void);
static void atk35_orword(void);
static void atk36_bicbyte(void);
static void atk37_bichalfword(void);
static void atk38_bicword(void);
static void atk39_pause(void);
static void atk3A_waitstate(void);
static void atk3B_healthbar_update(void);
static void atk3C_return(void);
static void atk3D_end(void);
static void atk3E_end2(void);
static void atk3F_end3(void);
static void atk40_jumpifaffectedbyprotect(void);
static void atk41_call(void);
static void atk42_missinghealthtoDmg(void);    //replaced was jumpiftype2
static void atk43_jumpifabilitypresent(void);
static void atk44_endselectionscript(void);
static void atk45_playanimation(void);
static void atk46_playanimation2(void);
static void atk47_setgraphicalstatchangevalues(void);
static void atk48_playstatchangeanimation(void);
static void atk49_moveend(void);
static void atk4A_typecalc2(void);
static void atk4B_returnatktoball(void);
static void atk4C_getswitchedmondata(void);
static void atk4D_switchindataupdate(void);
static void atk4E_switchinanim(void);
static void atk4F_jumpifcantswitch(void);
static void atk50_openpartyscreen(void);
static void atk51_switchhandleorder(void);
static void atk52_switchineffects(void);
static void atk53_trainerslidein(void);
static void atk54_playse(void);
static void atk55_fanfare(void);
static void atk56_playfaintcry(void);
static void atk57_endlinkbattle(void);
static void atk58_returntoball(void);
static void atk59_handlelearnnewmove(void);
static void atk5A_yesnoboxlearnmove(void);
static void atk5B_yesnoboxstoplearningmove(void);
static void atk5C_hitanimation(void);
static void atk5D_getmoneyreward(void);
static void atk5E(void);
static void atk5F_swapattackerwithtarget(void);
static void atk60_incrementgamestat(void);
static void atk61_drawpartystatussummary(void);
static void atk62_hidepartystatussummary(void);
static void atk63_jumptocalledmove(void);
static void atk64_statusanimation(void);
static void atk65_status2animation(void);
static void atk66_chosenstatusanimation(void);
static void atk67_yesnobox(void);
static void atk68_cancelallactions(void);
static void atk69_adjustsetdamage(void);
static void atk6A_removeitem(void);
static void atk6B_atknameinbuff1(void);
static void atk6C_drawlvlupbox(void);
static void atk6D_resetsentmonsvalue(void);
static void atk6E_setatktoplayer0(void);
static void atk6F_makevisible(void);
static void atk70_recordlastability(void);
static void atk71_buffermovetolearn(void);
static void atk72_jumpifplayerran(void);
static void atk73_hpthresholds(void);
static void atk74_hpthresholds2(void);
static void atk75_useitemonopponent(void);
static void atk76_various(void);
static void atk77_setprotectlike(void);
static void atk78_faintifabilitynotdamp(void);
static void atk79_setatkhptozero(void);
static void atk7A_jumpifnexttargetvalid(void);
static void atk7B_tryhealportionhealth(void);
static void atk7C_trymirrormove(void);
static void atk7D_setrain(void);
static void atk7E_setreflect(void);
static void atk7F_setseeded(void);
static void atk80_manipulatedamage(void);
static void atk81_trysetrest(void);
static void atk82_jumpifnotfirstturn(void);
static void atk83_nop(void);
static void atk84_jumpifcantmakeasleep(void);
static void atk85_stockpile(void);
static void atk86_stockpiletobasedamage(void);
static void atk87_stockpiletohpheal(void);
static void atk88_sethpdrain(void);
static void atk89_statbuffchange(void);
static void atk8A_normalisebuffs(void);
static void atk8B_setbide(void);
static void atk8C_confuseifrepeatingattackends(void);
static void atk8D_setmultihitcounter(void); //will be unused upgrading to emerald, done no longer used can replace
static void atk8E_initmultihitstring(void);
static void atk8F_forcerandomswitch(void);
static void atk90_tryconversiontypechange(void);
static void atk91_givepaydaymoney(void);
static void atk92_setlightscreen(void);
static void atk93_tryKO(void);
static void atk94_damagetohalftargethp(void);
static void atk95_setsandstorm(void);
static void atk96_weatherdamage(void);
static void atk97_tryinfatuating(void);
static void atk98_updatestatusicon(void);
static void atk99_setmist(void);
static void atk9A_setfocusenergy(void);
static void atk9B_transformdataexecution(void);
static void atk9C_setsubstitute(void);
static void atk9D_mimicattackcopy(void);
static void atk9E_metronome(void);
static void atk9F_dmgtolevel(void);
static void atkA0_psywavedamageeffect(void);
static void atkA1_counterdamagecalculator(void);
static void atkA2_mirrorcoatdamagecalculator(void);
static void atkA3_disablelastusedattack(void);
static void atkA4_trysetencore(void);
static void atkA5_painsplitdmgcalc(void);
static void atkA6_settypetorandomresistance(void);
static void atkA7_setalwayshitflag(void);
static void atkA8_copymovepermanently(void);
static void atkA9_trychoosesleeptalkmove(void);
static void atkAA_setdestinybond(void);
static void atkAB_trysetdestinybondtohappen(void);
static void atkAC_remaininghptopower(void);
static void atkAD_tryspiteppreduce(void);
static void atkAE_healpartystatus(void);
static void atkAF_cursetarget(void);
static void atkB0_trysetspikes(void);
static void atkB1_setforesight(void);
static void atkB2_trysetperishsong(void);
static void atkB3_rolloutdamagecalculation(void);
static void atkB4_jumpifconfusedandstatmaxed(void);
static void atkB5_furycuttercalc(void);
static void atkB6_happinesstodamagecalculation(void);
static void atkB7_presentdamagecalculation(void);
static void atkB8_setsafeguard(void);
static void atkB9_magnitudedamagecalculation(void);
static void atkBA_jumpifnopursuitswitchdmg(void);
static void atkBB_setsunny(void);
static void atkBC_maxattackhalvehp(void);
static void atkBD_copyfoestats(void);
static void atkBE_rapidspinfree(void);
static void atkBF_setdefensecurlbit(void);
static void atkC0_recoverbasedonsunlight(void);
static void atkC1_hiddenpowercalc(void);  //not used
static void atkC2_selectfirstvalidtarget(void);
static void atkC3_trysetfutureattack(void);
static void atkC4_trydobeatup(void);
static void atkC5_setsemiinvulnerablebit(void);
static void atkC6_clearsemiinvulnerablebit(void);
static void atkC7_setminimize(void);
static void atkC8_sethail(void);
static void atkC9_jumpifattackandspecialattackcannotfall(void);
static void atkCA_setforcedtarget(void);
static void atkCB_setcharge(void);
static void atkCC_callterrainattack(void);
static void atkCD_cureifburnedparalysedorpoisoned(void);
static void atkCE_settorment(void);
static void atkCF_jumpifnodamage(void);
static void atkD0_settaunt(void);
static void atkD1_trysethelpinghand(void);
static void atkD2_tryswapitems(void);
static void atkD3_trycopyability(void);
static void atkD4_trywish(void);
static void atkD5_trysetroots(void);
static void atkD6_doubledamagedealtifdamaged(void);
static void atkD7_setyawn(void);
static void atkD8_setdamagetohealthdifference(void);
static void atkD9_scaledamagebyhealthratio(void);
static void atkDA_tryswapabilities(void);
static void atkDB_tryimprison(void);
static void atkDC_trysetgrudge(void);
static void atkDD_weightdamagecalculation(void);
static void atkDE_assistattackselect(void);
static void atkDF_setmagiccoat(void);
static void atkE0_trysetsnatch(void);
static void atkE1_trygetintimidatetarget(void);
static void atkE2_switchoutabilities(void);
static void atkE3_jumpifhasnohp(void);
static void atkE4_getsecretpowereffect(void);
static void atkE5_pickup(void);             //unused can replace
static void atkE6_docastformchangeanimation(void);
static void atkE7_trycastformdatachange(void);
static void atkE8_settypebasedhalvers(void);
static void atkE9_setweatherballtype(void); //not used
static void atkEA_tryrecycleitem(void);
static void atkEB_settypetoterrain(void);
static void atkEC_pursuitrelated(void);
static void atkED_snatchsetbattlers(void);
static void atkEE_removelightscreenreflect(void);
static void atkEF_handleballthrow(void);
static void atkF0_givecaughtmon(void);
static void atkF1_trysetcaughtmondexflags(void);
static void atkF2_displaydexinfo(void);
static void atkF3_trygivecaughtmonnick(void);
static void atkF4_subattackerhpbydmg(void);
static void atkF5_removeattackerstatus1(void);
static void atkF6_finishaction(void);
static void atkF7_finishturn(void);
static void atkF8_setroost(void);
static void atkF9_mondamaged(void); // made this command to work for exponcatch, might remove if mondamaged works
static void atkFA_sethealblock(void);
static void atkFB_setgravity(void);
static void atkFC_setmiracle_eye(void);
static void atkFD_settailwind(void);
static void atkFE_setembargo(void);
static void atkFF_callnative(void);//put rest in bs native //left logic below as they will be static functions here, nvm can remove they aren't static they are just void?


void (* const gBattleScriptingCommandsTable[])(void) =
{
    atk00_attackcanceler,
    atk01_accuracycheck,
    atk02_attackstring,
    atk03_ppreduce,
    atk04_critcalc,
    atk05_damagecalc,
    atk06_typecalc,
    atk07_adjustnormaldamage,
    atk08_adjustnormaldamage2,
    atk09_attackanimation,
    atk0A_waitanimation,
    atk0B_healthbarupdate,
    atk0C_datahpupdate,
    atk0D_critmessage,
    atk0E_effectivenesssound,
    atk0F_resultmessage,
    atk10_printstring,
    atk11_printselectionstring,
    atk12_waitmessage,
    atk13_printfromtable,
    atk14_printselectionstringfromtable,
    atk15_setmoveeffectwithchance,
    atk16_seteffectprimary,
    atk17_seteffectsecondary,
    atk18_clearstatusfromeffect,
    atk19_tryfaintmon,
    atk1A_dofaintanimation,
    atk1B_cleareffectsonfaint,
    atk1C_jumpifstatus,
    atk1D_jumpifstatus2,
    atk1E_jumpbasedonability,
    atk1F_jumpifsideaffecting,
    atk20_jumpifstat,
    atk21_jumpifstatus3condition,
    atk22_jumpbasedontype,
    atk23_getexp,
    atk24_confirmlosingteam,
    atk25_movevaluescleanup,
    atk26_setmultihit,
    atk27_decrementmultihit,
    atk28_goto,
    atk29_jumpifbyte,
    atk2A_jumpifhalfword,
    atk2B_jumpifword,
    atk2C_jumpifarrayequal,
    atk2D_jumpifarraynotequal,
    atk2E_setbyte,
    atk2F_addbyte,
    atk30_subbyte,
    atk31_copyarray,
    atk32_copyarraywithindex,
    atk33_orbyte,
    atk34_orhalfword,
    atk35_orword,
    atk36_bicbyte,
    atk37_bichalfword,
    atk38_bicword,
    atk39_pause,
    atk3A_waitstate,
    atk3B_healthbar_update,
    atk3C_return,
    atk3D_end,
    atk3E_end2,
    atk3F_end3,
    atk40_jumpifaffectedbyprotect,
    atk41_call,
    atk42_missinghealthtoDmg,
    atk43_jumpifabilitypresent,
    atk44_endselectionscript,
    atk45_playanimation,
    atk46_playanimation2,
    atk47_setgraphicalstatchangevalues,
    atk48_playstatchangeanimation,
    atk49_moveend,
    atk4A_typecalc2,
    atk4B_returnatktoball,
    atk4C_getswitchedmondata,
    atk4D_switchindataupdate,
    atk4E_switchinanim,
    atk4F_jumpifcantswitch,
    atk50_openpartyscreen,
    atk51_switchhandleorder,
    atk52_switchineffects,
    atk53_trainerslidein,
    atk54_playse,
    atk55_fanfare,
    atk56_playfaintcry,
    atk57_endlinkbattle,
    atk58_returntoball,
    atk59_handlelearnnewmove,
    atk5A_yesnoboxlearnmove,
    atk5B_yesnoboxstoplearningmove,
    atk5C_hitanimation,
    atk5D_getmoneyreward,
    atk5E,
    atk5F_swapattackerwithtarget,
    atk60_incrementgamestat,
    atk61_drawpartystatussummary,
    atk62_hidepartystatussummary,
    atk63_jumptocalledmove,
    atk64_statusanimation,
    atk65_status2animation,
    atk66_chosenstatusanimation,
    atk67_yesnobox,
    atk68_cancelallactions,
    atk69_adjustsetdamage,
    atk6A_removeitem,
    atk6B_atknameinbuff1,
    atk6C_drawlvlupbox,
    atk6D_resetsentmonsvalue,
    atk6E_setatktoplayer0,
    atk6F_makevisible,
    atk70_recordlastability,
    atk71_buffermovetolearn,
    atk72_jumpifplayerran,
    atk73_hpthresholds,
    atk74_hpthresholds2,
    atk75_useitemonopponent,
    atk76_various,
    atk77_setprotectlike,
    atk78_faintifabilitynotdamp,
    atk79_setatkhptozero,
    atk7A_jumpifnexttargetvalid,
    atk7B_tryhealportionhealth,
    atk7C_trymirrormove,
    atk7D_setrain,
    atk7E_setreflect,
    atk7F_setseeded,
    atk80_manipulatedamage,
    atk81_trysetrest,
    atk82_jumpifnotfirstturn,
    atk83_nop,
    atk84_jumpifcantmakeasleep,
    atk85_stockpile,
    atk86_stockpiletobasedamage,
    atk87_stockpiletohpheal,
    atk88_sethpdrain,
    atk89_statbuffchange,
    atk8A_normalisebuffs,
    atk8B_setbide,
    atk8C_confuseifrepeatingattackends,
    atk8D_setmultihitcounter,
    atk8E_initmultihitstring,
    atk8F_forcerandomswitch,
    atk90_tryconversiontypechange,
    atk91_givepaydaymoney,
    atk92_setlightscreen,
    atk93_tryKO,
    atk94_damagetohalftargethp,
    atk95_setsandstorm,
    atk96_weatherdamage,
    atk97_tryinfatuating,
    atk98_updatestatusicon,
    atk99_setmist,
    atk9A_setfocusenergy,
    atk9B_transformdataexecution,
    atk9C_setsubstitute,
    atk9D_mimicattackcopy,
    atk9E_metronome,
    atk9F_dmgtolevel,
    atkA0_psywavedamageeffect,
    atkA1_counterdamagecalculator,
    atkA2_mirrorcoatdamagecalculator,
    atkA3_disablelastusedattack,
    atkA4_trysetencore,
    atkA5_painsplitdmgcalc,
    atkA6_settypetorandomresistance,
    atkA7_setalwayshitflag,
    atkA8_copymovepermanently,
    atkA9_trychoosesleeptalkmove,
    atkAA_setdestinybond,
    atkAB_trysetdestinybondtohappen,
    atkAC_remaininghptopower,
    atkAD_tryspiteppreduce,
    atkAE_healpartystatus,
    atkAF_cursetarget,
    atkB0_trysetspikes,
    atkB1_setforesight,
    atkB2_trysetperishsong,
    atkB3_rolloutdamagecalculation,
    atkB4_jumpifconfusedandstatmaxed,
    atkB5_furycuttercalc,
    atkB6_happinesstodamagecalculation,
    atkB7_presentdamagecalculation,
    atkB8_setsafeguard,
    atkB9_magnitudedamagecalculation,
    atkBA_jumpifnopursuitswitchdmg,
    atkBB_setsunny,
    atkBC_maxattackhalvehp,
    atkBD_copyfoestats,
    atkBE_rapidspinfree,
    atkBF_setdefensecurlbit,
    atkC0_recoverbasedonsunlight,
    atkC1_hiddenpowercalc,
    atkC2_selectfirstvalidtarget,
    atkC3_trysetfutureattack,
    atkC4_trydobeatup,
    atkC5_setsemiinvulnerablebit,
    atkC6_clearsemiinvulnerablebit,
    atkC7_setminimize,
    atkC8_sethail,
    atkC9_jumpifattackandspecialattackcannotfall,
    atkCA_setforcedtarget,
    atkCB_setcharge,
    atkCC_callterrainattack,
    atkCD_cureifburnedparalysedorpoisoned,
    atkCE_settorment,
    atkCF_jumpifnodamage,
    atkD0_settaunt,
    atkD1_trysethelpinghand,
    atkD2_tryswapitems,
    atkD3_trycopyability,
    atkD4_trywish,
    atkD5_trysetroots,
    atkD6_doubledamagedealtifdamaged,
    atkD7_setyawn,
    atkD8_setdamagetohealthdifference,
    atkD9_scaledamagebyhealthratio,
    atkDA_tryswapabilities,
    atkDB_tryimprison,
    atkDC_trysetgrudge,
    atkDD_weightdamagecalculation,
    atkDE_assistattackselect,
    atkDF_setmagiccoat,
    atkE0_trysetsnatch,
    atkE1_trygetintimidatetarget,
    atkE2_switchoutabilities,
    atkE3_jumpifhasnohp,
    atkE4_getsecretpowereffect,
    atkE5_pickup,   //unused
    atkE6_docastformchangeanimation,
    atkE7_trycastformdatachange,
    atkE8_settypebasedhalvers,
    atkE9_setweatherballtype,
    atkEA_tryrecycleitem,
    atkEB_settypetoterrain,
    atkEC_pursuitrelated,
    atkED_snatchsetbattlers,
    atkEE_removelightscreenreflect,
    atkEF_handleballthrow,
    atkF0_givecaughtmon,
    atkF1_trysetcaughtmondexflags,
    atkF2_displaydexinfo,
    atkF3_trygivecaughtmonnick,
    atkF4_subattackerhpbydmg,
    atkF5_removeattackerstatus1,
    atkF6_finishaction,
    atkF7_finishturn,
    atkF8_setroost,
    atkF9_mondamaged,
    atkFA_sethealblock,
    atkFB_setgravity,
    atkFC_setmiracle_eye,
    atkFD_settailwind,
    atkFE_setembargo,
    atkFF_callnative,   //no more values added, just replace pickup 
};

/*struct StatFractions
{
    u8 dividend;
    u8 divisor;
};*/

//planning to set for both pause and wait message
//right now its based on text speed but when get changes from pokeabbie
//for battle think will change to work based off her options settings instead
static const u8 gPauseValue[] = {
    [B_WAIT_TIME_LONG]      = 0x40,
    [B_WAIT_TIME_MED]       = 0x30,
    [B_WAIT_TIME_SHORT]    = 0x20,
    [B_WAIT_TIME_SHORTEST] = 0x10,
    [B_WAIT_TIME_BRIEFEST]  = 0x7,
    [B_WAIT_TIME_CLEAR_BUFF] = 0x5,
    [B_WAIT_TIME_CLEAR_BUFF_2] = 0x1,
    [B_WAIT_TIME_UNIQUE] = 0x2B, //for multihit miss and sleep heal
    [B_WAIT_TIME_LONG_LONG] = 0x63,  //for mon block ball message
    [B_WAIT_TIME_IMPORTANT_STRINGS] = 0x61, //for scaling important string wait times, ability effects state changes etc.

};

static s8 SetWaitTimeModifier(u8 BattleSpeed, u16 value); //setup to adjust wait time based on speed
static u8 SetPauseTimeModifier(u8 BattleSpeed, u16 value); //specifically for pause

const struct StatFractions gAccuracyStageRatios[] =
{
    {  33, 100 }, // -6
    {  36, 100 }, // -5
    {  43, 100 }, // -4
    {  50, 100 }, // -3
    {  60, 100 }, // -2
    {  75, 100 }, // -1
    {   1,   1 }, //  0
    { 133, 100 }, // +1
    { 166, 100 }, // +2
    {   2,   1 }, // +3
    { 233, 100 }, // +4
    { 133,  50 }, // +5
    {   3,   1 }, // +6
};

// The chance is 1/N for each stage. 0 - +4
// value  1 would be 100% crit late gen has stage 3 & u as 100%, I could do that? would have   good dark deal synergy...
//making my own version of crit stages, gen 2 high crit moves were +2 so 1/4, rather than making +2, I'll raise the value for stage 1
//and keep stage 2 where it is, would make things mostly balance out since people use high crit w scope lens so it'll still be the same
//its just not so bad without the scope boost,  just unsure if want to use value of 5 or 6
//decied to use 6, way it balances out each stat would be about a 10% crit increase until stage 4
//static const u16 sCriticalHitChance[] = { 16, 6, 4, 3, 1 };   values used for referenced, but moved to .h to make global use for ai file
const u16 gCriticalHitChance[] = { 16, 6, 4, 3, 1 };

s8 GetInverseCritChance(u8 battlerAtk, u8 battlerDef, u32 move)//stil don't know what for
{
    s32 critChanceIndex = AICalcCritChance(battlerAtk, battlerDef, move, FALSE);
    if (critChanceIndex < 0)
        return -1;
    else
        return gCriticalHitChance[critChanceIndex]; //seems potentialy show crit ratio?
}


#define BENEFITS_FROM_LEEK(battler, holdEffect)((holdEffect == HOLD_EFFECT_LEEK) && (GET_BASE_SPECIES_ID(gBattleMons[battler].species) == SPECIES_FARFETCHD || gBattleMons[battler].species == SPECIES_SIRFETCHD))
s32 AICalcCritChance(u8 battlerAtk, u8 battlerDef, u32 move, bool32 recordAbility)
{
    s32 critChance = 0;
    u32 abilityAtk = GetBattlerAbility(gBattlerAttacker);
    u32 abilityDef = GetBattlerAbility(gBattlerTarget);
    u32 holdEffectAtk = GetBattlerHoldEffect(battlerAtk, TRUE);

    if (gSideStatuses[battlerDef] & SIDE_STATUS_LUCKY_CHANT
        || gStatuses3[gBattlerAttacker] & STATUS3_CANT_SCORE_A_CRIT)
    {
        critChance = -1;
    }
    else if (DoesTargetAbilityBlockCrit(battlerDef))
    {
        if (recordAbility)
            RecordAbilityBattle(battlerDef, abilityDef);
        critChance = -1;    //never crit
    }
    else if (gStatuses3[battlerAtk] & STATUS3_LASER_FOCUS
        || (gBattleMoves[gCurrentMove].flags & FLAG_ALWAYS_CRIT)
        || (abilityAtk == ABILITY_MERCILESS && gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY))
         {
        critChance = -2;    //always crit
         }
    else
    {
        critChance = 2 * ((gBattleMons[gBattlerAttacker].status2 & STATUS2_FOCUS_ENERGY) != 0)
            + (gBattleMoves[gCurrentMove].flags & FLAG_HIGH_CRIT)
            + (holdEffectAtk == HOLD_EFFECT_SCOPE_LENS)
            + 2 * (holdEffectAtk == HOLD_EFFECT_LUCKY_PUNCH && gBattleMons[gBattlerAttacker].species == SPECIES_CHANSEY)
            + 2 * BENEFITS_FROM_LEEK(battlerAtk, holdEffectAtk)
            + 2 * ((GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_DARK_DEAL) && abilityAtk != ABILITY_DARK_DEAL)
            + (abilityAtk == ABILITY_SUPER_LUCK)
            + (abilityAtk == ABILITY_DARK_DEAL);

        if (critChance >= ARRAY_COUNT(gCriticalHitChance))
            critChance = ARRAY_COUNT(gCriticalHitChance) - 1;   //because array starts at 0
    }

    return critChance;
}

//not used - put in disobedience it does work -not sure if can use elsewhere tho
s32 CalculateMoveDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 moveType, s32 fixedBasePower, bool32 isCrit, bool32 randomFactor, bool32 updateFlags)
{
    return DoMoveDamageCalc(move, battlerAtk, battlerDef, moveType, fixedBasePower, isCrit, randomFactor,
        updateFlags, CalcTypeEffectivenessMultiplier(move, moveType, battlerAtk, battlerDef, updateFlags));
}



//note in setmoveeffect has check for status & sStatusFlagsForMoveEffects[gbattlescripting.moveeffect]
//realized could potentialy overlap w status1 etc.
//but see no status2 that would match a status1 is on here,
//need be careful with this
//vsonic important
static const u32 sStatusFlagsForMoveEffects[NUM_MOVE_EFFECTS] =
{
    [MOVE_EFFECT_SLEEP] = STATUS1_SLEEP,
    [MOVE_EFFECT_POISON] = STATUS1_POISON,
    [MOVE_EFFECT_BURN] = STATUS1_BURN,
    [MOVE_EFFECT_FREEZE] = STATUS1_FREEZE,
    [MOVE_EFFECT_PARALYSIS] = STATUS1_PARALYSIS,
    [MOVE_EFFECT_TOXIC] = STATUS1_TOXIC_POISON,
    [MOVE_EFFECT_INFESTATION] = STATUS4_INFESTATION,
    [MOVE_EFFECT_CONFUSION] = STATUS2_CONFUSION,
    [MOVE_EFFECT_FLINCH] = STATUS2_FLINCHED,
    [MOVE_EFFECT_UPROAR] = STATUS2_UPROAR,
    [MOVE_EFFECT_CHARGING] = STATUS2_MULTIPLETURNS,
    [MOVE_EFFECT_WRAP] = STATUS2_WRAPPED,
    [MOVE_EFFECT_PREVENT_ESCAPE] = STATUS2_ESCAPE_PREVENTION,
    [MOVE_EFFECT_SWITCH_LOCKED] = STATUS2_SWITCH_LOCKED,
    [MOVE_EFFECT_NIGHTMARE] = STATUS2_NIGHTMARE,
    [MOVE_EFFECT_THRASH] = STATUS2_LOCK_CONFUSE,
    [MOVE_EFFECT_ATTRACT] = STATUS2_INFATUATION,    //didn't work couldn't use infatuatedwith
};//actually rather than making this u64 prob should try putting in different status field since it doesn't need to be all status2 Ian use status4
//mof don't think the gba can parse u64, it can only go up to 3 mbs?

static const u8 *const sMoveEffectBS_Ptrs[] =
{
    [0] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SLEEP] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_POISON] = BattleScript_MoveEffectPoison,
    [MOVE_EFFECT_BURN] = BattleScript_MoveEffectBurn,
    [MOVE_EFFECT_FREEZE] = BattleScript_MoveEffectFreeze,
    [MOVE_EFFECT_PARALYSIS] = BattleScript_MoveEffectParalysis,
    [MOVE_EFFECT_TOXIC] = BattleScript_MoveEffectToxic,
    //[MOVE_EFFECT_PLACEHOLDER_STATUS1] = BattleScript_MoveEffectSpiritLock,
    [MOVE_EFFECT_INFESTATION] = BattleScript_MoveEffectInfestation,
    //[MOVE_EFFECT_TOXIC] = BattleScript_MoveEffectToxic, //think should put spirit lock here so values stay in order
    [MOVE_EFFECT_CONFUSION] = BattleScript_MoveEffectConfusion,
    [MOVE_EFFECT_FLINCH] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_TRI_ATTACK] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_UPROAR] = BattleScript_MoveEffectUproar,
    [MOVE_EFFECT_PAYDAY] = BattleScript_MoveEffectPayDay,
    [MOVE_EFFECT_CHARGING] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_WRAP] = BattleScript_MoveEffectWrap,
    [MOVE_EFFECT_RECOIL_25] = BattleScript_MoveEffectRecoil,
    [MOVE_EFFECT_ATK_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_DEF_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SPD_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SP_ATK_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SP_DEF_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_ACC_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_EVS_PLUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_ATK_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_DEF_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SPD_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SP_ATK_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SP_DEF_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_ACC_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_EVS_MINUS_1] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_RECHARGE] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_RAGE] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_STEAL_ITEM] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_PREVENT_ESCAPE] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_SWITCH_LOCKED] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_NIGHTMARE] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_ALL_STATS_UP] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_RAPIDSPIN] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_REMOVE_STATUS] = BattleScript_MoveEffectSleep,
    [MOVE_EFFECT_ATK_DEF_DOWN] = BattleScript_MoveEffectSleep,//BattleScript_MoveEffectFallInLove
    [MOVE_EFFECT_DEF_SPDEF_DOWN] = BattleScript_MoveEffectSleep,//BattleScript_MoveEffectFallInLove
    [MOVE_EFFECT_RECOIL_33] = BattleScript_MoveEffectRecoil,
    [MOVE_EFFECT_MED_RECOIL_W_STATUS] = BattleScript_MoveEffectRecoilWithStatus,
    [MOVE_EFFECT_SPD_MINUS_2] = BattleScript_MoveEffectSleep,    
    [MOVE_EFFECT_ATTRACT] = BattleScript_MoveEffectAttract,   //see if it works as is, or I need actuall battlescript for this
    
}; //don't know why a lot of these default to sleep, but I added attract to hopefully do something?
//those that default to sleep have their effects set in SetMoveEffect function 

// not used
static const struct WindowTemplate sUnusedWinTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 3,
    .width = 7,
    .height = 15,
    .paletteNum = 31,
    .baseBlock = 0x3F,
};

static const u16 gUnknown_82506D0[] = INCBIN_U16("graphics/battle_interface/unk_battlebox.gbapal");
static const u32 gUnknown_82506F0[] = INCBIN_U32("graphics/battle_interface/unk_battlebox.4bpp.lz");

// not used
static const u8 sRubyLevelUpStatBoxStats[] =
{
    MON_DATA_MAX_HP, MON_DATA_SPATK, MON_DATA_ATK,
    MON_DATA_SPDEF, MON_DATA_DEF, MON_DATA_SPEED
};

static const struct OamData sOamData_MonIconOnLvlUpBox =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

#define MON_ICON_LVLUP_BOX_TAG 0xD75A

static const struct SpriteTemplate sSpriteTemplate_MonIconOnLvlUpBox =
{
    .tileTag = MON_ICON_LVLUP_BOX_TAG,
    .paletteTag = MON_ICON_LVLUP_BOX_TAG,
    .oam = &sOamData_MonIconOnLvlUpBox,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_MonIconOnLvlUpBox
};

static const u16 sProtectSuccessRates[] =
{ 
    USHRT_MAX,
    USHRT_MAX / 2, 
    USHRT_MAX / 4, 
    USHRT_MAX / 8
};

#define FORBIDDEN_MIMIC         (1 << 0)
#define FORBIDDEN_METRONOME     (1 << 1)
#define FORBIDDEN_ASSIST        (1 << 2)
#define FORBIDDEN_COPYCAT       (1 << 3)
#define FORBIDDEN_SLEEP_TALK    (1 << 4)
#define FORBIDDEN_INSTRUCT      (1 << 5)
#define FORBIDDEN_PARENTAL_BOND (1 << 6)


#define MIMIC_FORBIDDEN_END             0xFFFE
#define METRONOME_FORBIDDEN_END         0xFFFF
#define ASSIST_FORBIDDEN_END            0xFFFF
#define MULTI_TASK_FORBIDDEN_END        0xFFFF
#define FORBIDDEN_INSTRUCT_END          0xFFFF


static const u8 sForbiddenMoves[MOVES_COUNT] =
{
    [MOVE_NONE] = 0xFF, // Can't use a non-move lol
    [MOVE_STRUGGLE] = 0xFF, // Neither Struggle
    [MOVE_AFTER_YOU] = FORBIDDEN_METRONOME,
    [MOVE_APPLE_ACID] = FORBIDDEN_METRONOME,
    [MOVE_ARM_THRUST] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_ASSIST] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_ASTRAL_BARRAGE] = FORBIDDEN_METRONOME,
    [MOVE_AURA_WHEEL] = FORBIDDEN_METRONOME,
    [MOVE_BADDY_BAD] = FORBIDDEN_METRONOME,
    [MOVE_BANEFUL_BUNKER] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_BARRAGE] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_BEAK_BLAST] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_BEAT_UP] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_BEHEMOTH_BASH] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_BEHEMOTH_BLADE] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_BELCH] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_BESTOW] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_BIDE] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND, // Note: Bide should work with Parental Bond. This will be addressed in future.
    [MOVE_BLAST_BURN] = FORBIDDEN_INSTRUCT,
    [MOVE_BODY_PRESS] = FORBIDDEN_METRONOME,
    [MOVE_BONE_RUSH] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_BONEMERANG] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_BOUNCE] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_BOUNCY_BUBBLE] = FORBIDDEN_METRONOME,
    [MOVE_BRANCH_POKE] = FORBIDDEN_METRONOME,
    [MOVE_BREAKING_SWIPE] = FORBIDDEN_METRONOME,
    [MOVE_BULLET_SEED] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_BUZZY_BUZZ] = FORBIDDEN_METRONOME,
    [MOVE_CELEBRATE] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_CHATTER] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_MIMIC | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_CIRCLE_THROW] = FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_CLANGOROUS_SOUL] = FORBIDDEN_METRONOME,
    [MOVE_COMET_PUNCH] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_COPYCAT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_COUNTER] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_COVET] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_CRAFTY_SHIELD] = FORBIDDEN_METRONOME,
    [MOVE_DECORATE] = FORBIDDEN_METRONOME,
    [MOVE_DESTINY_BOND] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_DETECT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_DIAMOND_STORM] = FORBIDDEN_METRONOME,
    [MOVE_DIG] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_DIVE] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_DOUBLE_IRON_BASH] = FORBIDDEN_METRONOME | FORBIDDEN_PARENTAL_BOND,
    [MOVE_DOUBLE_HIT] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_DOUBLE_KICK] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_DOUBLE_SLAP] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_DRAGON_ASCENT] = FORBIDDEN_METRONOME,
    [MOVE_DRAGON_ENERGY] = FORBIDDEN_METRONOME,
    [MOVE_DRAGON_DARTS] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_DRAGON_TAIL] = FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_DRUM_BEATING] = FORBIDDEN_METRONOME,
    [MOVE_DUAL_STRIKE] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_DUAL_WINGBEAT] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_DYNAMAX_CANNON] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_ENDEAVOR] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_ENDURE] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_ETERNABEAM] = FORBIDDEN_METRONOME | FORBIDDEN_INSTRUCT,
    [MOVE_EXPLOSION] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_FALSE_SURRENDER] = FORBIDDEN_METRONOME,
    [MOVE_FEINT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_FIERY_WRATH] = FORBIDDEN_METRONOME,
    [MOVE_FINAL_GAMBIT] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_FISSURE] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_FLEUR_CANNON] = FORBIDDEN_METRONOME,
    [MOVE_FLING] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_FLOATY_FALL] = FORBIDDEN_METRONOME,
    [MOVE_FLY] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_FOCUS_PUNCH] = FORBIDDEN_INSTRUCT,
    [MOVE_FOLLOW_ME] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_FREEZE_SHOCK] = FORBIDDEN_METRONOME | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_FREEZING_GLARE] = FORBIDDEN_METRONOME,
    [MOVE_FREEZY_FROST] = FORBIDDEN_METRONOME,
    [MOVE_FURY_ATTACK] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_FURY_SWIPES] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_GEAR_GRIND] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_GEOMANCY] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_GIGA_IMPACT] = FORBIDDEN_INSTRUCT,
    [MOVE_GLACIAL_LANCE] = FORBIDDEN_METRONOME,
    [MOVE_GLITZY_GLOW] = FORBIDDEN_METRONOME,
    [MOVE_GRAV_APPLE] = FORBIDDEN_METRONOME,
    [MOVE_GUILLOTINE] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_HELPING_HAND] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_HOLD_HANDS] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_HORN_DRILL] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_HYDRO_CANNON] = FORBIDDEN_INSTRUCT,
    [MOVE_HYPER_BEAM] = FORBIDDEN_INSTRUCT,
    [MOVE_HYPERSPACE_FURY] = FORBIDDEN_METRONOME,
    [MOVE_HYPERSPACE_HOLE] = FORBIDDEN_METRONOME,
    [MOVE_ICE_BALL] = FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_ICE_BURN] = FORBIDDEN_METRONOME | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_ICICLE_SPEAR] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_INSTRUCT] = FORBIDDEN_METRONOME | FORBIDDEN_INSTRUCT,
    [MOVE_JUNGLE_HEALING] = FORBIDDEN_METRONOME,
    [MOVE_KINGS_SHIELD] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_INSTRUCT,
    [MOVE_LIFE_DEW] = FORBIDDEN_METRONOME,
    [MOVE_LIGHT_OF_RUIN] = FORBIDDEN_METRONOME,
    [MOVE_MAT_BLOCK] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_ME_FIRST] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_METEOR_ASSAULT] = FORBIDDEN_METRONOME | FORBIDDEN_INSTRUCT,
    [MOVE_METEOR_BEAM] = FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_METRONOME] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_MIMIC] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_MIMIC | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_MIND_BLOWN] = FORBIDDEN_METRONOME,
    [MOVE_MIRROR_COAT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_MIRROR_MOVE] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_MISTY_EXPLOSION] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_MOONGEIST_BEAM] = FORBIDDEN_METRONOME,
    [MOVE_NATURE_POWER] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_NATURES_MADNESS] = FORBIDDEN_METRONOME,
    [MOVE_OBSTRUCT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_INSTRUCT,
    [MOVE_ORIGIN_PULSE] = FORBIDDEN_METRONOME,
    [MOVE_OUTRAGE] = FORBIDDEN_INSTRUCT,
    [MOVE_OVERDRIVE] = FORBIDDEN_METRONOME,
    [MOVE_PHANTOM_FORCE] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_PHOTON_GEYSER] = FORBIDDEN_METRONOME,
    [MOVE_PRISMATIC_LASER] = FORBIDDEN_INSTRUCT,
    [MOVE_PROTECT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_PYRO_BALL] = FORBIDDEN_METRONOME,
    [MOVE_QUASH] = FORBIDDEN_METRONOME,
    [MOVE_QUICK_GUARD] = FORBIDDEN_METRONOME,
    [MOVE_RAGE_POWDER] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_RAZOR_WIND] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_RELIC_SONG] = FORBIDDEN_METRONOME,
    [MOVE_ROAR] = FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_ROAR_OF_TIME] = FORBIDDEN_INSTRUCT,
    [MOVE_ROCK_BLAST] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_ROCK_WRECKER] = FORBIDDEN_INSTRUCT,
    [MOVE_ROLLOUT] = FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SAPPY_SEED] = FORBIDDEN_METRONOME,
    [MOVE_SCALE_SHOT] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_SECRET_SWORD] = FORBIDDEN_METRONOME,
    [MOVE_SELF_DESTRUCT] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_SHADOW_FORCE] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SHEER_COLD] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_SHELL_TRAP] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_SIZZLY_SLIDE] = FORBIDDEN_METRONOME,
    [MOVE_SKETCH] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_MIMIC | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_SKULL_BASH] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SKY_ATTACK] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SKY_DROP] = FORBIDDEN_ASSIST | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SLEEP_TALK] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT,
    [MOVE_SNAP_TRAP] = FORBIDDEN_METRONOME,
    [MOVE_SNARL] = FORBIDDEN_METRONOME,
    [MOVE_SNATCH] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_INSTRUCT,
    [MOVE_SNORE] = FORBIDDEN_METRONOME,
    [MOVE_SOLAR_BEAM] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SOLAR_BLADE] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SPARKLY_SWIRL] = FORBIDDEN_METRONOME,
    [MOVE_SPECTRAL_THIEF] = FORBIDDEN_METRONOME,
    [MOVE_SPIKE_CANNON] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_SPIKE_SHIELD] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_SPIRIT_BREAK] = FORBIDDEN_METRONOME,
    [MOVE_SPLISHY_SPLASH] = FORBIDDEN_METRONOME,
    [MOVE_SPOTLIGHT] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_STEAM_ERUPTION] = FORBIDDEN_METRONOME,
    [MOVE_STEEL_BEAM] = FORBIDDEN_METRONOME,
    [MOVE_STRANGE_STEAM] = FORBIDDEN_METRONOME,
    [MOVE_SUNSTEEL_STRIKE] = FORBIDDEN_METRONOME,
    [MOVE_SURGING_STRIKES] = FORBIDDEN_METRONOME | FORBIDDEN_PARENTAL_BOND,
    [MOVE_SWITCHEROO] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_TAIL_SLAP] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_TECHNO_BLAST] = FORBIDDEN_METRONOME,
    [MOVE_THIEF] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_THOUSAND_ARROWS] = FORBIDDEN_METRONOME,
    [MOVE_THOUSAND_WAVES] = FORBIDDEN_METRONOME,
    [MOVE_THRASH] = FORBIDDEN_INSTRUCT,
    [MOVE_THUNDER_CAGE] = FORBIDDEN_METRONOME,
    [MOVE_THUNDEROUS_KICK] = FORBIDDEN_METRONOME,
    [MOVE_TRANSFORM] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT | FORBIDDEN_MIMIC | FORBIDDEN_INSTRUCT,
    [MOVE_TRICK] = FORBIDDEN_METRONOME | FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_TRIPLE_AXEL] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_TRIPLE_KICK] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_TWINEEDLE] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_UPROAR] = FORBIDDEN_SLEEP_TALK | FORBIDDEN_INSTRUCT | FORBIDDEN_PARENTAL_BOND,
    [MOVE_V_CREATE] = FORBIDDEN_METRONOME,
    [MOVE_VEEVEE_VOLLEY] = FORBIDDEN_METRONOME,
    [MOVE_WATER_SHURIKEN] = FORBIDDEN_PARENTAL_BOND,
    [MOVE_WHIRLWIND] = FORBIDDEN_ASSIST | FORBIDDEN_COPYCAT,
    [MOVE_WICKED_BLOW] = FORBIDDEN_METRONOME,
    [MOVE_WIDE_GUARD] = FORBIDDEN_METRONOME,
    [MOVE_ZIPPY_ZAP] = FORBIDDEN_METRONOME,
};

static const u16 sMoveEffectsForbiddenToInstruct[] =
{
    EFFECT_ASSIST,
    //EFFECT_BEAK_BLAST,
    EFFECT_BELCH,
    EFFECT_BIDE,
    //EFFECT_CELEBRATE,
    //EFFECT_CHATTER,
    EFFECT_COPYCAT,
    //EFFECT_DYNAMAX_CANNON,
    EFFECT_FOCUS_PUNCH,
    EFFECT_GEOMANCY,
    //EFFECT_HOLD_HANDS,
    EFFECT_INSTRUCT,
    EFFECT_ME_FIRST,
    EFFECT_METRONOME,
    EFFECT_MIMIC,
    EFFECT_MIRROR_MOVE,
    EFFECT_NATURE_POWER,
    //EFFECT_OBSTRUCT,
    EFFECT_RAMPAGE,
    EFFECT_RECHARGE,
    EFFECT_RECOIL,
    EFFECT_ROLLOUT,
    EFFECT_SEMI_INVULNERABLE,
    //EFFECT_SHELL_TRAP,
    EFFECT_SKETCH,
    //EFFECT_SKY_DROP,
    EFFECT_SKULL_BASH,
    EFFECT_SLEEP_TALK,
    EFFECT_SOLARBEAM,
    EFFECT_TRANSFORM,
    EFFECT_TWO_TURNS_ATTACK,
    EFFECT_UPROAR,
    FORBIDDEN_INSTRUCT_END
};



static const u16 sMovesForbiddenToCopy[] =
{
    MOVE_METRONOME,
    MOVE_STRUGGLE,
    MOVE_SKETCH,
    MOVE_MIMIC,
    MIMIC_FORBIDDEN_END,
    MOVE_COUNTER,
    MOVE_MIRROR_COAT,
    MOVE_PROTECT,
    MOVE_DETECT,
    MOVE_ENDURE,
    MOVE_DESTINY_BOND,
    MOVE_SLEEP_TALK,
    MOVE_THIEF,
    MOVE_FOLLOW_ME,
    MOVE_SNATCH,
    MOVE_HELPING_HAND,
    MOVE_COVET,
    MOVE_TRICK,
    //MOVE_FOCUS_PUNCH,
    METRONOME_FORBIDDEN_END
};

//raising the left numbers higher, will let you do more damage from higher percent hp
static const u8 sFlailHpScaleToPowerTable[] =
{
    4, 200,
    12, 150,
    19, 100,
    25, 80,
    32, 40,
    68, 20
};

//these two arrays relate only to multi_task, could probably do with just 1, but just some extra redundancy
//ledian buff taking multi hit & fury cutt effect out of this to make like skill link
//FOR MOVES that cant work with multitask setup, or would be broken
//rage added as effect can't work in setup - tired
static const u16 sMultiTaskExcludedEffects[] =
{ 
    //EFFECT_MAGNITUDE, //variable power  made function to account for
    EFFECT_ROLLOUT,
    EFFECT_SKY_ATTACK,
    EFFECT_SOLARBEAM,
    EFFECT_SKULL_BASH,
    EFFECT_SEMI_INVULNERABLE,
    //EFFECT_RAZOR_WIND,  //canremove from exclusions since changed to two_typed effect well, razorwind as an effect isn't used at all now
    EFFECT_MULTI_HIT,
    EFFECT_FURY_CUTTER,
    EFFECT_DOUBLE_HIT,
    EFFECT_TRIPLE_KICK,
    EFFECT_SUPER_FANG,
    EFFECT_ENDEAVOR,
    EFFECT_SONIC_SCREECH,
    EFFECT_COUNTER, //because can't crit
    EFFECT_LEVEL_DAMAGE, //same
    EFFECT_DRAGON_RAGE,
    EFFECT_BIDE,
    EFFECT_PRESENT, //since making multi-hit would work,  give delibird multitask, since like santa everywhere at once
    EFFECT_MIRROR_COAT,
    EFFECT_BEAT_UP,
    EFFECT_TWINEEDLE,
    EFFECT_EXPLOSION,  //ya ALMOST snuck by me, but not quite!!
    EFFECT_FUTURE_SIGHT,  //yeah, you can come too!! I gotcha.
    EFFECT_UPROAR,
    EFFECT_RAMPAGE,
    EFFECT_OHKO, //no pokemon I'm giving this to normally learns a ohko move, so I may leave in for something potentially fun for the player.
    //EFFECT_RAGE,  same as magnitude
    //EFFECT_TWO_TURNS_ATTACK // because I'm not using two turns attack??  doube check this
    MULTI_TASK_FORBIDDEN_END
}; //had add multi hit effects back to this, it only affects dmg share from dmg calc macro

// the moves that are multihit without the effect i.e use setmultihit or setmultihitcounter, before going to multihitloop...it was only twinneedle
//so don't need this now
/*static const u16 sBlockedMoves[] =
{};*/

//remember to change logic and buff the weak ones vsonic
static const u16 sNaturePowerMoves[] =
{
    [BATTLE_TERRAIN_GRASS] = MOVE_STUN_SPORE,
    [BATTLE_TERRAIN_LONG_GRASS] = MOVE_RAZOR_LEAF,
    [BATTLE_TERRAIN_SAND] = MOVE_EARTHQUAKE,
    [BATTLE_TERRAIN_UNDERWATER] = MOVE_HYDRO_PUMP,
    [BATTLE_TERRAIN_WATER] = MOVE_SURF,
    [BATTLE_TERRAIN_POND] = MOVE_BUBBLE_BEAM,
    [BATTLE_TERRAIN_MOUNTAIN] = MOVE_ROCK_SLIDE,
    [BATTLE_TERRAIN_CAVE] = MOVE_SHADOW_BALL,
    [BATTLE_TERRAIN_BUILDING] = MOVE_SWIFT,
    [BATTLE_TERRAIN_PLAIN] = MOVE_SWIFT
};

u16 GetNaturePowerMove(void)
{
    if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
        return MOVE_MOONBLAST;
    else if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
        return MOVE_THUNDERBOLT;
    else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
        return MOVE_ENERGY_BALL;
    else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
        return MOVE_PSYCHIC;
    else if (sNaturePowerMoves == MOVE_NONE)
        return MOVE_TRI_ATTACK;
    return sNaturePowerMoves[gBattleTerrain];
}


static const u16 sWeightToDamageTable[] =
{
    50, 40,
    200, 60,    //geodude is here
    500, 75,
    1000, 85,  //graveler is here
    2400, 100,  //onix is here  //snorlax is double this
    10000, 120,
    0xFFFF, 0xFFFF
};


static const u8 sTerrainToType[] =
{
    TYPE_GRASS,  // tall grass
    TYPE_GRASS,  // long grass
    TYPE_GROUND, // sand
    TYPE_WATER,  // underwater
    TYPE_WATER,  // water
    TYPE_WATER,  // pond water
    TYPE_ROCK,   // rock
    TYPE_ROCK,   // cave
    TYPE_NORMAL, // building
    TYPE_NORMAL, // plain
};

//if I add more balls may need to adjust this also see how it links to each ball
//ok think this is problem with ball reorder need to change this,
//yup this was it, vsonic
static const u8 sBallCatchBonuses[] =
{
    [BALL_POKE]   =  10,
    [BALL_GREAT]  =  15,
    [BALL_SAFARI] =  15,
    [BALL_ULTRA]  =  20,
   
};

// not used
static const u32 gUnknown_8250898 = 0xFF7EAE60;

static bool32 TryAegiFormChange(void)
{
    u16 effect = gBattleMoves[gCurrentMove].effect;
    // Only Aegislash with Stance Change can transform, transformed mons cannot.
    if (GetBattlerAbility(gBattlerAttacker) != ABILITY_STANCE_CHANGE
        || gBattleMons[gBattlerAttacker].status2 & STATUS2_TRANSFORMED)
        return FALSE;

    switch (gBattleMons[gBattlerAttacker].species)
    {
    default:
        return FALSE;
    case SPECIES_AEGISLASH: // Shield -> Blade  //myust be damaging move, so this should be if status or couter 
        //if (gBattleMoves[gCurrentMove].power == 0)
        if (IS_MOVE_STATUS(gCurrentMove) || IsMoveCounterAttack(gCurrentMove))
            return FALSE;
        gBattleMons[gBattlerAttacker].species = SPECIES_AEGISLASH_BLADE;
        break;
    case SPECIES_AEGISLASH_BLADE: // Blade -> Shield
        if (gCurrentMove != MOVE_KINGS_SHIELD)
            return FALSE;
        gBattleMons[gBattlerAttacker].species = SPECIES_AEGISLASH;
        break;
    }

    BattleScriptPushCursor();
    gBattlescriptCurrInstr = BattleScript_AttackerFormChange;
    return TRUE;
}

bool32 ProteanTryChangeType(u32 battler, u32 ability, u32 move, u32 moveType)
{
      if ((ability == ABILITY_PROTEAN || ability == ABILITY_LIBERO)
         && (gBattleMons[battler].type1 != moveType || gBattleMons[battler].type2 != moveType) //removed type 3 logic didn't make sense
         && move != MOVE_STRUGGLE
         && moveType != TYPE_MYSTERY
         && moveType != TYPE_SOUND) //seems effevt isn't based on being an attack and incudes status moves too
    {
        SET_BATTLER_TYPE_PROTEAN(gBattlerAttacker, moveType); //made new type set that doesn't affect type 3, for sake of moves that shift type 3
        return TRUE; //done
    }
    return FALSE;
}

static void atk00_attackcanceler(void) //vsonic
{
    CMD_ARGS();
    s32 i, moveType;
    u8 j;
    GET_MOVE_TYPE(gCurrentMove,moveType)


    if (gBattleOutcome)
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }
    if (gBattleMons[gBattlerAttacker].hp == 0 && !(gHitMarker & HITMARKER_NO_ATTACKSTRING))
    {
        gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
        gBattlescriptCurrInstr = BattleScript_MoveEnd;
        return;
    }
    //how does this work for effects that set effect, but don't stop move from attacking?
    //does it just not read everything below so all else gets ignored?
    //even if it potentially shouldn't?
    //ex if I had sleep checker and freeze check I should run
    //would it stop at sleep and never check/decrement freeze logic?
    
    //* checked its a switch case without breaks so yes,
    //unless I allowed fall through it would only stop
    //when it hit a single condition
    //think what I can do is rearrange order of attack cancel,
    //so thinks that aren't mutually exclusive could activate ex.
    //ex sleep check wake up, but then triggering paralysis.
    //I would set it to fallthrough, if sleep wouldn't stop attack,
    //then check if paralysis would stop it, if not continue on 
    //to be sure double check my understanding of switch cases
    if (AtkCanceller_UnableToUseMove())
        return;
    // Check Protean activation.
    if (ProteanTryChangeType(gBattlerAttacker, GetBattlerAbility(gBattlerAttacker), gCurrentMove, moveType))
    {
        PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
        gBattlerAbility = gBattlerAttacker;
        BattleScriptPushCursor();
        PrepareStringBattle(STRINGID_EMPTYSTRING3, gBattlerAttacker);
        gBattleCommunication[MSG_DISPLAY] = 1;
        gBattlescriptCurrInstr = BattleScript_ProteanActivates;
        return;
    }

    if (AtkCanceller_UnableToUseMove2())
        return;
    if (AbilityBattleEffects(ABILITYEFFECT_MOVES_BLOCK, gBattlerTarget, 0, 0, 0))
        return;
    if (!gBattleMons[gBattlerAttacker].pp[gCurrMovePos] && gCurrentMove != MOVE_STRUGGLE && !(gHitMarker & (HITMARKER_ALLOW_NO_PP | HITMARKER_NO_ATTACKSTRING))
     && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS))
    {
        gBattlescriptCurrInstr = BattleScript_NoPPForMove;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        return;
    }

    //think will move this to move end clear bit effects
    //so if lastused move 
    //double check if that goes before or after
    //my sandstorm damage, that is in endturn field effects
    /*if (gStatuses3[gBattlerAttacker] & STATUS3_CHARGED_UP 
    && gBattleMoves[gLastMoves[gBattlerAttacker]].type == TYPE_ELECTRIC
    && gBattleMoves[gLastMoves[gBattlerAttacker]].split != SPLIT_STATUS)
        gStatuses3[gBattlerAttacker] &= ~STATUS3_CHARGED_UP;
    */
   //moved becuase belie this not cleared until nextz move is 
   //being used, messing up my wind power change

    //split conditions, gave higher odds to iron will
    //as its affects are all odds based with no consistent affect
    if (!gBattleStruct->isAtkCancelerForCalledMove 
        && (GetBattlerAbility(gBattlerTarget) == ABILITY_IRON_WILL) //remove flinch affect for  pressure just give dmg drop
        && IsBlackFogNotOnField()
        && !gSpecialStatuses[gBattlerAttacker].Lostresolve //sinceit returns needs value to allow skip so doesnt loop
        && gBattlerTarget != gBattlerAttacker) //need to ensure not self target
        {
            if ((Random() % 5 < 2) //40% 
            && gBattleMoves[gCurrentMove].split != SPLIT_STATUS) //only non status moves
            {
                gSpecialStatuses[gBattlerAttacker].Lostresolve++;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_Pressure_IronWill_LostResolve;
                return;
            } //should do dmg drop but not cancel move
            //damage drop should go in damagecalc, no point in it being here...

        } //moved effect out here, as otherwise caused freeze

    else if (!gBattleStruct->isAtkCancelerForCalledMove 
        && (GetBattlerAbility(gBattlerTarget) == ABILITY_HI_PRESSURE
        || GetBattlerAbility(gBattlerTarget) == ABILITY_PRESSURE)
        && IsBlackFogNotOnField()
        && !gSpecialStatuses[gBattlerAttacker].Lostresolve //sinceit returns needs value to allow skip so doesnt loop
        && gBattlerTarget != gBattlerAttacker)
    {
        if (((Random() % 3) == 1) //40% -...can't remember why I had different odds for these, potentially testing balance?
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS) //only non status moves
        {
            gSpecialStatuses[gBattlerAttacker].Lostresolve++;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_Pressure_IronWill_LostResolve;
            return;
        } //should do dmg drop but not cancel move

    } 

    if (GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_CACOPHONY
    && gBattleMoves[gCurrentMove].flags & FLAG_SOUND)
        gSpecialStatuses[gBattlerAttacker].Cacophonyboosted = TRUE;

    if (gBattleResources->flags->flags[gBattlerAttacker] & RESOURCE_FLAG_EMERGENCY_EXIT
    && gDisableStructs[gBattlerAttacker].EmergencyExitTimer == 0
    && GetBattlerAbility(gBattlerAttacker) == ABILITY_EMERGENCY_EXIT) 
    {   
        //need remove this to prevent loop, but can use special status I think for move end check?
        gBattleResources->flags->flags[gBattlerAttacker] &= ~RESOURCE_FLAG_EMERGENCY_EXIT;
        gSpecialStatuses[gBattlerAttacker].EmergencyExit = TRUE;
        if (gBattleMoves[gCurrentMove].split != SPLIT_STATUS)
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_EffectAttackUpBeforeMove;
            return;//works seems only reason froze was I didn't have the return here at end
        }
        
    }

    if (TryAegiFormChange())
        return;


    gHitMarker &= ~(HITMARKER_ALLOW_NO_PP);
    if (!(gHitMarker & HITMARKER_OBEYS) 
     && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS))
    {

        switch (gBattleStruct->obedienceResult)
        {
        case OBEYS:
            break;
        case DISOBEYS_LOAFS:
            // Randomly select, then print a disobedient string
            // B_MSG_LOAFING, B_MSG_WONT_OBEY, B_MSG_TURNED_AWAY, or B_MSG_PRETEND_NOT_NOTICE
            gBattleCommunication[MULTISTRING_CHOOSER] = Random() % 4;
            
            //lower healing than truant
            if (!(gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_HEAL_BLOCK))
            {
            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
            if (gBattleMoveDamage == 0)
                gBattleMoveDamage = 1;
            gBattleMoveDamage *= -1;
            }
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
            return;
        case DISOBEYS_HITS_SELF:
            gBattlerTarget = gBattlerAttacker;
            gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker], &gBattleMons[gBattlerAttacker], MOVE_POUND, 0, 40, 0, gBattlerAttacker, gBattlerAttacker);
            gBattlescriptCurrInstr = BattleScript_IgnoresAndHitsItself;
            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
            gHitMarker |= HITMARKER_OBEYS;
            return;
        case DISOBEYS_FALL_ASLEEP:
            gBattlescriptCurrInstr = BattleScript_IgnoresAndFallsAsleep;
            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
            //gMoveResultFlags |= MOVE_RESULT_MISSED;
            return;
        case DISOBEYS_WHILE_ASLEEP:
            gBattlescriptCurrInstr = BattleScript_IgnoresWhileAsleep;
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            return;
        case DISOBEYS_RANDOM_MOVE:
            gCalledMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
            SetAtkCancellerForCalledMove();
            gBattlescriptCurrInstr = BattleScript_IgnoresAndUsesRandomMove;
            gBattlerTarget = GetMoveTarget(gCalledMove, NO_TARGET_OVERRIDE);
            gHitMarker |= HITMARKER_DISOBEDIENT_MOVE;
            gHitMarker |= HITMARKER_OBEYS;
            return;
        }
    }
    gHitMarker |= HITMARKER_OBEYS;

    

    if (gProtectStructs[gBattlerTarget].bounceMove  //target has magic coat effect/ already setup and should work as sidestatus, could replace with timer check but don't need to
        && gBattleMoves[gCurrentMove].flags & FLAG_MAGIC_COAT_AFFECTED
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_INFILTRATOR   //since this is a screen-like, needed add infiltrator bypass
        && !(GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_CACOPHONY && gBattleMoves[gCurrentMove].flags & FLAG_SOUND)
        && !gProtectStructs[gBattlerAttacker].usesBouncedMove) //move attacker is using is not one already bounced
    {
        PressurePPLose(gBattlerAttacker, gBattlerTarget, MOVE_MAGIC_COAT);
        //gProtectStructs[gBattlerTarget].bounceMove = FALSE; //removes magic coat effect from target after activating, (removing this line as I made multi turn
        gProtectStructs[gBattlerTarget].usesBouncedMove = TRUE;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        // Edge case for bouncing a powder move against a grass type pokemon.
        SetAtkCancellerForCalledMove();
        if (DoesPranksterBlockMove(gCurrentMove, gBattlerTarget, gBattlerAttacker, TRUE))
        {
            // Opponent used a prankster'd magic coat -> reflected status move should fail against a dark-type attacker
            gBattlerTarget = gBattlerAttacker;
            gBattlescriptCurrInstr = BattleScript_MagicCoatBouncePrankster;//effect is accurate, its saying target using magic coat also has prankster, so it should fail against a dark type
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_MagicCoatBounce;
        }
        return;
    }
    else if (GetBattlerAbility(gBattlerTarget) == ABILITY_MAGIC_BOUNCE
        && gBattleMoves[gCurrentMove].flags & FLAG_MAGIC_COAT_AFFECTED
        && !gProtectStructs[gBattlerAttacker].usesBouncedMove)  //still working on proper setup for new magic coat need double check if ported magic bounce stuff for statbuffchange, as its similar effect
    {
        RecordAbilityBattle(gBattlerTarget, ABILITY_MAGIC_BOUNCE);
        gProtectStructs[gBattlerTarget].usesBouncedMove = TRUE;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        // Edge case for bouncing a powder move against a grass type pokemon.
        SetAtkCancellerForCalledMove();
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_MagicCoatBounce;
        return;
    }

    else if ((GetBattlerAbility(gBattlerTarget) == ABILITY_FOREWARN)
    //&& gBattlerAttacker == gForewarnedBattler  //spefiic condition just for forewarn, extra leway given to anticipation
    && gBattlerAttacker == gDisableStructs[gBattlerTarget].forewarnedBattler //redid effect realized as weas would be reset if two forewarn mon on enemy side
    && gDisableStructs[gBattlerTarget].forewarnedMove != MOVE_UNAVAILABLE // ^ works //edit had wrong battler listed, forgot to properly adjust
    && gDisableStructs[gBattlerTarget].forewarnedMove != MOVE_NONE) //works perfectly
    {
        //if (gCurrentMove == gDisableStructs[gBattlerTarget].forewarnedMove)
        if (!IS_MOVE_STATUS(gCurrentMove))
        {
            
            gMoveResultFlags |= MOVE_RESULT_MISSED;     //that way can make sure it lasts entire battle, not cleard on switch or faingt
            gLastLandedMoves[gBattlerTarget] = 0;
            gLastHitByType[gBattlerTarget] = 0;//not sur ethat will work but need figure out how to do ,. can make new struct thats' only cleared on battle start and end
            gBattleCommunication[MISS_TYPE] = B_MSG_AVOIDED_DMG; //check target matches forewarn user
        }
        //gDisableStructs[gBattlerTarget].forewarnedMove = MOVE_UNAVAILABLE; //ensures, only works for first turn - set in battle_main        
        gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)] = TRUE;
    }
    else if ((GetBattlerAbility(gBattlerTarget) == ABILITY_ANTICIPATION)
    && gDisableStructs[gBattlerTarget].anticipatedMove != MOVE_UNAVAILABLE
    && gDisableStructs[gBattlerTarget].anticipatedMove != MOVE_NONE)
    {
        //if (gCurrentMove == gDisableStructs[gBattlerTarget].anticipatedMove)
        if (!IS_MOVE_STATUS(gCurrentMove))
        {

            gMoveResultFlags |= MOVE_RESULT_MISSED;
            gLastLandedMoves[gBattlerTarget] = 0;
            gLastHitByType[gBattlerTarget] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_AVOIDED_DMG;
        }
        //gDisableStructs[gBattlerTarget].anticipatedMove = MOVE_UNAVAILABLE; //issue if move used doesn't go through attak canceler this doesn't remove status
        gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)] = TRUE;
        //put here since ability completion is based on attack being done, not actually using the move stored by ability
        //appears to work now
    }

    for (i = 0; i < gBattlersCount; ++i)
    {
        if ((gProtectStructs[gBattlerByTurnOrder[i]].stealMove) && gBattleMoves[gCurrentMove].flags & FLAG_SNATCH_AFFECTED)
        {
            PressurePPLose(gBattlerAttacker, gBattlerByTurnOrder[i], MOVE_SNATCH);
            gProtectStructs[gBattlerByTurnOrder[i]].stealMove = FALSE;
            gBattleScripting.battler = gBattlerByTurnOrder[i];
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_SnatchedMove;
            return;
        }
    }
    /*if (gSpecialStatuses[gBattlerTarget].lightningRodRedirected)    //THE special status are so these can go here and cancel the move animatoin
    {   //I may change that save me some ewram and let the animation play, but change it so the target gets a heal animation play and then the stat boost & text
        gSpecialStatuses[gBattlerTarget].lightningRodRedirected = FALSE;
        gLastUsedAbility = ABILITY_LIGHTNING_ROD;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_TookAttack;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }*/ //should be fine to remove this now, 

    //think I can use attack canceler to reset targetting?
    //just need loop side for absorb abiliy w check for if can absorb

    //ok I don't even remembere what I did regarding this...

    /*depending on how things go I may decide/need to make a new animation for absorb moves
    actually better idea is to make the extra effect animation and just insert it as a conditional call
    into the normal functions so it doesn't take up more space.
    
    best case I can slot it into animation after the visual effects but before the target recoil.
    so the animation plays the target doesn't get knock back because the ability nulls it
    and it plays the heal or stat buff visual & sound instead the new function should be called & end in a return or a end, 
    vsonic IMPORTANT
    */
    if (gProtectStructs[gBattlerTarget].shieldBashed && (gBattleMoves[gCurrentMove].flags & FLAG_PROTECT_AFFECTED))
    {
        if (IsMoveMakingContact(gCurrentMove, gBattlerAttacker))
        {
            gProtectStructs[gBattlerAttacker].touchedProtectLike = TRUE;
            
        }
    }
    else if (IsBattlerProtected(gBattlerTarget, gCurrentMove)
        && (gCurrentMove != MOVE_CURSE || IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GHOST))
        && ((!IsTwoTurnsMove(gCurrentMove) || (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS))) //what does this even????! vsonic
        && gBattleMoves[gCurrentMove].effect != EFFECT_SUCKER_PUNCH)
    {
        if (IsMoveMakingContact(gCurrentMove, gBattlerAttacker))
            gProtectStructs[gBattlerAttacker].touchedProtectLike = TRUE;
        CancelMultiTurnMoves(gBattlerAttacker);
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0;

        if (gSpecialStatuses[gBattlerAttacker].parentalBondState == PARENTAL_BOND_1ST_HIT)
        {
            gSpecialStatuses[gBattlerAttacker].parentalBondState = PARENTAL_BOND_OFF; // No second hit if first hit was blocked
            gSpecialStatuses[gBattlerAttacker].multiHitOn = 0;
            gMultiHitCounter = 0;
        }

        gBattleCommunication[MISS_TYPE] = B_MSG_PROTECTED;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    else if (gProtectStructs[gBattlerTarget].beakBlastCharge && IsMoveMakingContact(gCurrentMove, gBattlerAttacker))
    {
        gProtectStructs[gBattlerAttacker].touchedProtectLike = TRUE;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    else
    {
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

static bool32 JumpIfMoveFailed(u8 adder, u16 move) //updated to emerald standard
{
    //const u8 *BS_ptr = gBattlescriptCurrInstr + adder;

    if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
    {
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0;
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        return TRUE;
    }
    else
    {
        TrySetDestinyBondToHappen();
        if (AbilityBattleEffects(ABILITYEFFECT_ABSORBING, gBattlerTarget, 0, 0, move)) //what do?
            return TRUE;
    }
    gBattlescriptCurrInstr += adder;
    return FALSE;
}

static void atk40_jumpifaffectedbyprotect(void)
{
    if (IsBattlerProtected(gBattlerTarget, gCurrentMove))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        JumpIfMoveFailed(5, 0);
        gBattleCommunication[6] = 1;
    }
    else
    {
        gBattlescriptCurrInstr += 5;
    }
}

static bool8 JumpIfMoveAffectedByProtect(u16 move)
{
    bool8 affected = FALSE;

    if (IsBattlerProtected(gBattlerTarget, gCurrentMove))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        JumpIfMoveFailed(7, move);
        gBattleCommunication[6] = 1;
        affected = TRUE;
    }
    return affected;
}

static bool8 IsBattlerProtected(u8 battlerId, u16 move)//IMPORTANT change to false if protectbreak condition met
{ //setprotectlike does the protection, then hre I can undo it when this gets checked in attack canceleror
    //make sure add check for if move is protect affected to all protectstructs listed below

    if (GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_CACOPHONY && gBattleMoves[move].flags & FLAG_SOUND)
        return FALSE;
    else if (IsMoveMakingContact(move, gBattlerAttacker) && GetBattlerAbility(gBattlerAttacker) == ABILITY_UNSEEN_FIST)
        return FALSE;
    else if ((gProtectStructs[battlerId].protected) && (gBattleMoves[gCurrentMove].flags & FLAG_PROTECT_AFFECTED))
        return TRUE;
    else if (gBattleMoves[move].effect == MOVE_EFFECT_FEINT)
        return FALSE;
    else if (gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_WIDE_GUARD
        && gBattleMoves[move].target & (MOVE_TARGET_BOTH | MOVE_TARGET_FOES_AND_ALLY))
        return TRUE;
    else if (gProtectStructs[battlerId].banefulBunkered)
        return TRUE;
    else if (gProtectStructs[battlerId].spikyShielded)
        return TRUE;
    else if (gProtectStructs[battlerId].kingsShielded && gBattleMoves[move].power != 0)
        return TRUE;
    else if (gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_QUICK_GUARD
        && GetChosenMovePriority(gBattlerAttacker) > 0)
        return TRUE;
    else if (gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_CRAFTY_SHIELD //user side moves shouldnt affect i.e aromatherapy also perish song bypasses vsonic
        && IS_MOVE_STATUS(move))
        return TRUE;
    else if (gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_MAT_BLOCK
        && !IS_MOVE_STATUS(move))
        return TRUE;
    
    else
        return FALSE;
}



static bool8 AccuracyCalcHelper(u16 move)//fiugure how to add blizzard hail accuracy ignore  //done
{   //in emerald these are else ifs, rather than if, think will change to that so it checks through all instead of just 1st true
    if (gStatuses3[gBattlerTarget] & STATUS3_ALWAYS_HITS && gDisableStructs[gBattlerTarget].battlerWithSureHit == gBattlerAttacker)
    {
        JumpIfMoveFailed(7, move);
        return TRUE;
    }

    else if (gBattleMoves[move].effect == EFFECT_TOXIC
        && IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_POISON))   //ironically with type chart change I don't need this
    {
        JumpIfMoveFailed(7, move);
        return TRUE;
    }
    else if (gBattleStruct->pursuitTarget & (1u << gBattlerTarget)) //hopefully gbattleratrget is right here? vsonic
    {
        JumpIfMoveFailed(7, move);
        return TRUE;
    }
    else if (move == MOVE_SANDSEAR_STORM
    && gBattleWeather & WEATHER_RAIN_ANY)
    {
        JumpIfMoveFailed(7, move);
        return TRUE;
    }

    /*if (!(gHitMarker & HITMARKER_IGNORE_ON_AIR) && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        JumpIfMoveFailed(7, move);
        return TRUE;
    }
    gHitMarker &= ~HITMARKER_IGNORE_ON_AIR;

    if (!(gHitMarker & HITMARKER_IGNORE_UNDERGROUND) && gStatuses3[gBattlerTarget] & STATUS3_UNDERGROUND)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        JumpIfMoveFailed(7, move);
        return TRUE;
    }
    gHitMarker &= ~HITMARKER_IGNORE_UNDERGROUND;

    if (!(gHitMarker & HITMARKER_IGNORE_UNDERWATER) && gStatuses3[gBattlerTarget] & STATUS3_UNDERWATER)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        JumpIfMoveFailed(7, move);
        return TRUE;
    }
    gHitMarker &= ~HITMARKER_IGNORE_UNDERWATER;*/

    // If the attacker has the ability No Guard and they aren't targeting a Pokemon involved in a Sky Drop with the move Sky Drop, move hits.
    else if (GetBattlerAbility(gBattlerAttacker) == ABILITY_NO_GUARD && (move != MOVE_SKY_DROP || gBattleStruct->skyDropTargets[gBattlerTarget] == 0xFF))
    {
        if (!JumpIfMoveFailed(7, move))
            RecordAbilityBattle(gBattlerAttacker, ABILITY_NO_GUARD);
        return TRUE;
    }

    // If the target has the ability No Guard and they aren't involved in a Sky Drop or the current move isn't Sky Drop, move hits.
    else if (GetBattlerAbility(gBattlerTarget) == ABILITY_NO_GUARD && (move != MOVE_SKY_DROP || gBattleStruct->skyDropTargets[gBattlerTarget] == 0xFF))
    {
        if (!JumpIfMoveFailed(7, move))
            RecordAbilityBattle(gBattlerTarget, ABILITY_NO_GUARD);
        return TRUE;
    }

    if ((gStatuses3[gBattlerTarget] & STATUS3_SEMI_INVULNERABLE)//i beleve this is the replacement for the hitmarker values for semi invul, just need to add flags to omve data
        || (!(gBattleMoves[move].flags & FLAG_DMG_IN_AIR) && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR)
        || (!(gBattleMoves[move].flags & FLAG_DMG_2X_IN_AIR) && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR)
        || (!(gBattleMoves[move].flags & FLAG_DMG_2X_UNDERGROUND) && gStatuses3[gBattlerTarget] & STATUS3_UNDERGROUND)
        || (!(gBattleMoves[move].flags & FLAG_DMG_2X_UNDERWATER) && gStatuses3[gBattlerTarget] & STATUS3_UNDERWATER))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        JumpIfMoveFailed(7, move);
        return TRUE;
    }

    if (move == MOVE_SHEER_COLD && IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_ICE))
    {
        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        JumpIfMoveFailed(7, move);
        return TRUE;
    }

    if ((IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_RAIN_ANY) && (gBattleMoves[move].effect == EFFECT_THUNDER || gBattleMoves[move].effect == EFFECT_HURRICANE))
        || ((IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_HAIL_ANY)) && move == MOVE_BLIZZARD)
        || (gBattleMoves[move].effect == EFFECT_ALWAYS_HIT || gBattleMoves[move].effect == EFFECT_VITAL_THROW)
        || ((gStatuses3[gBattlerTarget] & STATUS3_MINIMIZED) && (gBattleMoves[move].flags & FLAG_DMG_MINIMIZE)))
    {
        JumpIfMoveFailed(7, move);
        return TRUE;
    }   //this will do weather buffs but double check think I added this elsewhere? plus I don't think I'd want it to be surehit but its fine i guess

    if (gBattleMoves[move].accuracy == 0)   //MOVED OUT HERE for wonderskin buff? yeah affect isn't in base wonderskin   
    {
        if (IS_MOVE_STATUS(move) 
        && (GetBattlerAbility(gBattlerTarget) == ABILITY_WONDER_SKIN
        || GetBattlerAbility(gBattlerTarget) == ABILITY_IMMUTABLE_WIND))
            return FALSE;
        else
        {
            JumpIfMoveFailed(7, move);
            return TRUE;
        }
    }
    

    return FALSE;
}

#define ACCURACY_BASED_ABILITIES
static void atk01_accuracycheck(void)
{
    u16 move = T2_READ_16(gBattlescriptCurrInstr + 5);  //should be reading acc of current moves,
    u8 moveType;
    u16 holdEffectAtk = GetBattlerHoldEffect(gBattlerAttacker, TRUE);

    GET_MOVE_TYPE(gCurrentMove, moveType); 

    if ((gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE
        && !BtlCtrl_OakOldMan_TestState2Flag(1)
        && gBattleMoves[move].power != 0
        && GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        || (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE
            && !BtlCtrl_OakOldMan_TestState2Flag(2)
            && gBattleMoves[move].power == 0
            && GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        || (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE))
    {
        JumpIfMoveFailed(7, move);  //looks like this makes it so player cant miss in first rival battle? (and no one can crit as well)
        return; //seems to be too ensure the battle messages for dmg & lowering stats play, not really likely to be an issue but ok
    }

    //with move expansion at some point this could be an issue but very unlikely
    //seems much simpler to remove them, ratrher than move  just use lock on status check
    //and already have logic for accuracy 0  in AccuracyCalcHelper to skip acc check
    if (move == NO_ACC_CALC || move == NO_ACC_CALC_CHECK_LOCK_ON) 
    {
        if (gStatuses3[gBattlerTarget] & STATUS3_ALWAYS_HITS && move == NO_ACC_CALC_CHECK_LOCK_ON && gDisableStructs[gBattlerTarget].battlerWithSureHit == gBattlerAttacker)
            gBattlescriptCurrInstr += 7;
        else if (gStatuses3[gBattlerTarget] & (STATUS3_SEMI_INVULNERABLE))
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        else if (!JumpIfMoveAffectedByProtect(0))
            gBattlescriptCurrInstr += 7;
    }
    else if (gSpecialStatuses[gBattlerAttacker].parentalBondState == PARENTAL_BOND_2ND_HIT
            || (GetBattlerAbility(gBattlerAttacker) == ABILITY_SKILL_LINK && gMultiHitCounter > 0 && gMultiHitCounter != gMultiTask)
            || (gCurrentMove == MOVE_SURGING_STRIKES && gMultiHitCounter != gMultiTask)//for rebalancing trose moves, to keep in line with wicked blow
            //|| holdEffectAtk == HOLD_EFFECT_LOADED_DICE
            || DoesBattlerAbilityAbsorbMoveType(gBattlerTarget, moveType)
            || DoesBattlerAbilityAbsorbMoveType(BATTLE_PARTNER(gBattlerTarget), moveType)) //drawn in moves are supposed to never miss so this should hopefully do that
    {
        //think have surging strikes right now, can't use move arguemnt as that isn't gcurr move, and need exclude first hit
        // No acc checks for second hit of Parental Bond or skill linked moves, removed other multihit as I want those to work differently, now all go through acc check on each hit
        //gBattlescriptCurrInstr += 7;
        JumpIfMoveFailed(7, gCurrentMove); //ok so was RAELLY stupid, adding ability absorb to skip here,
        //messed up the call to the abilityeffect in the firstplace somehow so had I wasn't calling the ability bracket at all
    }

    else
    {
        u8 type;
        u16 calc;
        u16 abilityAtk = GetBattlerAbility(gBattlerAttacker);
        u16 abilityDef = GetBattlerAbility(gBattlerTarget);



        if (move == MOVE_NONE)
            move = gCurrentMove;
        GET_MOVE_TYPE(move, type);
        if (JumpIfMoveAffectedByProtect(move) || AccuracyCalcHelper(move))
            return;

        calc = GetTotalAccuracy(
            gBattlerAttacker,
            gBattlerTarget,
            move,
            abilityAtk,
            abilityDef,
            holdEffectAtk,
            GetBattlerHoldEffect(gBattlerTarget, TRUE)
        );

        
        
        // final calculation
        if ((Random() % 100 + 1) > calc)    //turns accuracy value into a percent by comparing on a base 100 scale, by lowering random num I can effectively raise acc of all moves
        {   //but it would be shifting the scale, and actually only really benefit high accuracy moves i.e if I shifted to random 95, 95 accuracy would then be 100
            //now if I added a check that filtered for moveacc below a certain value with filters to exclude certain effects that have their acc changed by conditions i.e thunder
            //I could boost all moves accuracy without having to go through entire move list...
            //hmm would work but not as targetted as if I did it myself, and I find other things along the way so I'll continue as I am..

            gMoveResultFlags |= MOVE_RESULT_MISSED;
            if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_BLUNDER_POLICY)
                gBattleStruct->blunderPolicy = TRUE;    // Only activates from missing through acc/evasion checks

            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
                && (gBattleMoves[move].target == MOVE_TARGET_BOTH || gBattleMoves[move].target == MOVE_TARGET_FOES_AND_ALLY))
                gBattleCommunication[MISS_TYPE] = B_MSG_AVOIDED_ATK;
            else
                gBattleCommunication[MISS_TYPE] = B_MSG_MISSED;

            gDisableStructs[gBattlerAttacker].furyCutterCounter = 0;  //reset if miss
            gMultiHitCounter = 0; //if miss reset to 0, think this was reason, grouded stuff wasn't triggering, has check for counter being 0
            //unsure if needed but keeping for now
            //removed encountered new glitch of move not ending

            /*
             if (gBattleMoves[gCurrentMove].effect == EFFECT_DRAGON_DARTS
                && !recalcDragonDarts // So we don't jump back and forth between targets
                && CanTargetPartner(gBattlerAttacker, gBattlerTarget)
                && !TargetFullyImmuneToCurrMove(gBattlerAttacker, BATTLE_PARTNER(gBattlerTarget)))
            {
                // Smart target to partner if miss
                gBattlerTarget = BATTLE_PARTNER(gBattlerTarget);
                gMoveResultFlags &= ~MOVE_RESULT_MISSED;
                AccuracyCheck(TRUE, nextInstr, failInstr, move);
                return;
            }
            */

            //if (gBattleMoves[move].power)   //i ALREADY have a typecalc I don't need this to update move result flags I think?
            //am I using this at all?
            CalcTypeEffectivenessMultiplier(move, type, gBattlerAttacker, gBattlerTarget, FALSE);    //this is only instance where uses TRUE, without that it doesn't change effectiveness
            //emerald used true because it made this the type calc, but I'm not replacing typecalc command 
            //i'm putting this there, so in the typecalc function I'll set true there, everywhere else will be false.
            //pretty sure it has everything needed for wonderguard stuff to work regardless/without updating move result
            //-looks to be working
            
            //using this worked perfectly, so can confirm new type chart is solid
            //removing this as it has foresight logic, emerald uses typecalc? hopefully
            //can do that without doubling the multiplier.
            //nvm not using typecalc, forgot I ported emerald's CalcTypeEffectivenessMultiplier function, 
            //that's what's used in emerald think can just copy it straight over
            //CheckWonderGuardAndLevitate(); //change levitate portion of function to use grounded logic
        //may put this back need test more on a working system
        
        //this runs type check against base chart, compares result to abilities then sets result flags
        //I came to conclusion this isn't actually necessary since type calc already does that?
        //dif is checkwonder gaurd set move_result_no effect while otehrs set missed
        //so I changed type calc for thsoe abilities to use no effect for all but telepathy
        //and am aremoving  this check all together to just be done in typecalc
        //also means CalcTypeEffectivenessMultiplier isnt' being used anywhere currently
        //thinnk shuold put in ai_typecalc functino since that was original plan
        //to just have it there so it could calc type at anytime
        //without needing the typecalc bs command
        }
        JumpIfMoveFailed(7, move);
    }
}

/*  //planned replacement for above, need include my custom changes like multihit acc rework
static void AccuracyCheck(bool32 recalcDragonDarts, const u8 *nextInstr, const u8 *failInstr, u16 move)
{
    u32 moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, move);
    u32 abilityAtk = GetBattlerAbility(gBattlerAttacker);
    u32 abilityDef = GetBattlerAbility(gBattlerTarget);
    u32 holdEffectAtk = GetBattlerHoldEffect(gBattlerAttacker, TRUE);

    if (move == ACC_CURR_MOVE)
        move = gCurrentMove;

    if (move == NO_ACC_CALC_CHECK_LOCK_ON)
    {
        if (gStatuses3[gBattlerTarget] & STATUS3_ALWAYS_HITS && gDisableStructs[gBattlerTarget].battlerWithSureHit == gBattlerAttacker)
            gBattlescriptCurrInstr = nextInstr;
        else if (gStatuses3[gBattlerTarget] & (STATUS3_SEMI_INVULNERABLE))
            gBattlescriptCurrInstr = failInstr;
        else if (!JumpIfMoveAffectedByProtect(gCurrentMove))
            gBattlescriptCurrInstr = nextInstr;
        if (GetActiveGimmick(gBattlerAttacker) == GIMMICK_DYNAMAX)
        {
            if (gProtectStructs[gBattlerTarget].maxGuarded)
                gBattlescriptCurrInstr = nextInstr;
            else
                AbilityBattleEffects(ABILITYEFFECT_ABSORBING, gBattlerTarget, 0, 0, gCurrentMove);
        }
    }
    else if (gSpecialStatuses[gBattlerAttacker].parentalBondState == PARENTAL_BOND_2ND_HIT
        || (gSpecialStatuses[gBattlerAttacker].multiHitOn
        && (abilityAtk == ABILITY_SKILL_LINK || holdEffectAtk == HOLD_EFFECT_LOADED_DICE
        || !(gMovesInfo[move].effect == EFFECT_TRIPLE_KICK || gMovesInfo[move].effect == EFFECT_POPULATION_BOMB))))
    {
        // No acc checks for second hit of Parental Bond or multi hit moves, except Triple Kick/Triple Axel/Population Bomb
        gBattlescriptCurrInstr = nextInstr;
    }
    else
    {
        u32 accuracy;
        u32 type = GetMoveType(move);

        if (JumpIfMoveAffectedByProtect(move))
            return;
        if (AccuracyCalcHelper(move))
            return;

        accuracy = GetTotalAccuracy(
            gBattlerAttacker,
            gBattlerTarget,
            move,
            abilityAtk,
            abilityDef,
            holdEffectAtk,
            GetBattlerHoldEffect(gBattlerTarget, TRUE)
        );

        if (!RandomPercentage(RNG_ACCURACY, accuracy))
        {
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            if (holdEffectAtk == HOLD_EFFECT_BLUNDER_POLICY)
                gBattleStruct->blunderPolicy = TRUE;    // Only activates from missing through acc/evasion checks

            if (gMovesInfo[gCurrentMove].effect == EFFECT_DRAGON_DARTS
                && !recalcDragonDarts // So we don't jump back and forth between targets
                && CanTargetPartner(gBattlerAttacker, gBattlerTarget)
                && !TargetFullyImmuneToCurrMove(gBattlerAttacker, BATTLE_PARTNER(gBattlerTarget)))
            {
                // Smart target to partner if miss
                gBattlerTarget = BATTLE_PARTNER(gBattlerTarget);
                gMoveResultFlags &= ~MOVE_RESULT_MISSED;
                AccuracyCheck(TRUE, nextInstr, failInstr, move);
                return;
            }

            if (IsDoubleBattle() &&
                (moveTarget == MOVE_TARGET_BOTH || moveTarget == MOVE_TARGET_FOES_AND_ALLY))
                gBattleCommunication[MISS_TYPE] = B_MSG_AVOIDED_ATK;
            else
                gBattleCommunication[MISS_TYPE] = B_MSG_MISSED;

            if (gMovesInfo[move].power)
                CalcTypeEffectivenessMultiplier(move, type, gBattlerAttacker, gBattlerTarget, abilityDef, TRUE);
        }
        JumpIfMoveFailed(7, move);
    }
}

static void Cmd_accuracycheck(void)
{
    CMD_ARGS(const u8 *failInstr, u16 move);

    // The main body of this function has been moved to AccuracyCheck() to accomodate
    // Dragon Darts' multiple accuracy checks on a single attack;
    // each dart can try to re-target once after missing.
    AccuracyCheck(FALSE, cmd->nextInstr, cmd->failInstr, cmd->move);
}
*/

static void atk02_attackstring(void)
{
    if (!gBattleControllerExecFlags)
    {
        if (!(gHitMarker & (HITMARKER_NO_ATTACKSTRING | HITMARKER_ATTACKSTRING_PRINTED)))
        {
            PrepareStringBattle(STRINGID_USEDMOVE, gBattlerAttacker);
            gHitMarker |= HITMARKER_ATTACKSTRING_PRINTED;
        }
        ++gBattlescriptCurrInstr;
        gBattleCommunication[MSG_DISPLAY] = 0;
    }
}

//believe this is for setmondata
//battle util does battle pp
//this does adjusting mon data to match?
static void atk03_ppreduce(void)
{
    s32 ppToDeduct = 1; //not 100% but this seems to be more about targetting than the actual drop?
    //as that has a function for handling that
    //pp is 1, for normal move use,
    //then increments if true here,
    //so need do 2 for hi pressure believe

    if (!gBattleControllerExecFlags)
    {
        if (!gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure)
        {
            switch (gBattleMoves[gCurrentMove].target)//realize needs to add here as well as the util.c to make hi pressure work?
            {
            case MOVE_TARGET_FOES_AND_ALLY:
                ppToDeduct += AbilityBattleEffects(ABILITYEFFECT_COUNT_ON_FIELD, gBattlerAttacker, ABILITY_PRESSURE, 0, 0);
                ppToDeduct += AbilityBattleEffects(ABILITYEFFECT_COUNT_ON_FIELD, gBattlerAttacker, ABILITY_HI_PRESSURE, 0, 0);
                ppToDeduct += AbilityBattleEffects(ABILITYEFFECT_COUNT_ON_FIELD, gBattlerAttacker, ABILITY_HI_PRESSURE, 0, 0);
                break;
            case MOVE_TARGET_BOTH:
            case MOVE_TARGET_OPPONENTS_FIELD:
                ppToDeduct += AbilityBattleEffects(ABILITYEFFECT_COUNT_OTHER_SIDE, gBattlerAttacker, ABILITY_PRESSURE, 0, 0);
                ppToDeduct += AbilityBattleEffects(ABILITYEFFECT_COUNT_OTHER_SIDE, gBattlerAttacker, ABILITY_HI_PRESSURE, 0, 0);
                ppToDeduct += AbilityBattleEffects(ABILITYEFFECT_COUNT_OTHER_SIDE, gBattlerAttacker, ABILITY_HI_PRESSURE, 0, 0);
                break;
            default:    //loks like normal battle, but with a check to make sure move isn't a self targetting move?
                if (gBattlerAttacker != gBattlerTarget && GetBattlerAbility(gBattlerTarget) == ABILITY_PRESSURE)
                    ++ppToDeduct;
                if (gBattlerAttacker != gBattlerTarget && GetBattlerAbility(gBattlerTarget) == ABILITY_HI_PRESSURE)
                    ppToDeduct += 2;
                break;
            }
        }
        if (!(gHitMarker & (HITMARKER_NO_PPDEDUCT | HITMARKER_NO_ATTACKSTRING)) && gBattleMons[gBattlerAttacker].pp[gCurrMovePos])
        {
            gProtectStructs[gBattlerAttacker].notFirstStrike = 1;

            // For item Metronome, echoed voice
            if (gCurrentMove == gLastResultingMoves[gBattlerAttacker]
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && !WasUnableToUseMove(gBattlerAttacker))
                gBattleStruct->sameMoveTurns[gBattlerAttacker]++;
            else
                gBattleStruct->sameMoveTurns[gBattlerAttacker] = 0;

            if (gBattleMons[gBattlerAttacker].pp[gCurrMovePos] > ppToDeduct)
                gBattleMons[gBattlerAttacker].pp[gCurrMovePos] -= ppToDeduct;
            else
                gBattleMons[gBattlerAttacker].pp[gCurrMovePos] = 0;

            if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_TRANSFORMED)
                && !((gDisableStructs[gBattlerAttacker].mimickedMoves) & gBitTable[gCurrMovePos]))
            {
                gActiveBattler = gBattlerAttacker;
                BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + gCurrMovePos, 0, 1, &gBattleMons[gBattlerAttacker].pp[gCurrMovePos]);
                MarkBattlerForControllerExec(gBattlerAttacker);
            }
        }
        gHitMarker &= ~(HITMARKER_NO_PPDEDUCT);
        ++gBattlescriptCurrInstr;
    }
}


static void atk04_critcalc(void)    //working/works
{
    u8 holdEffect;
    u16 item, critChance;

    item = gBattleMons[gBattlerAttacker].item;
    if (item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[gBattlerAttacker].holdEffect;
    else
        holdEffect = GetBattlerHoldEffect(gBattlerAttacker, TRUE); //find out if all these all these +'s affect the total effect chance?
    gPotentialItemEffectBattler = gBattlerAttacker; //realized these don't increase total crit chance but are all the things that raise crit odds,
    //+'s raise crit ratio by 1 stage, 2x raises two stages etc.
    critChance = 2 * ((gBattleMons[gBattlerAttacker].status2 & STATUS2_FOCUS_ENERGY) != 0)
        +((gBattleMoves[gCurrentMove].flags & FLAG_HIGH_CRIT) != 0)
        + (holdEffect == HOLD_EFFECT_SCOPE_LENS)   
        + 2 * (holdEffect == HOLD_EFFECT_LUCKY_PUNCH && gBattleMons[gBattlerAttacker].species == SPECIES_CHANSEY)
        + 2 * BENEFITS_FROM_LEEK(gPotentialItemEffectBattler, holdEffect)
        + (GetBattlerAbility(gBattlerAttacker) == ABILITY_SUPER_LUCK) //what does this do?? I guess it raiss 1 stage? if ability super luck?
        + (GetBattlerAbility(gBattlerAttacker) == ABILITY_DARK_DEAL)
        + 2 * ((GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_DARK_DEAL) && GetBattlerAbility(gBattlerAttacker) != ABILITY_DARK_DEAL);    
    //HOPE works for raising crit chanc 2 stages if partner ability is dark deal
    //should make mutually exclusive, i.e can't get dark deal user buff & partner buff

    if (critChance >= NELEMS(gCriticalHitChance))
        critChance = NELEMS(gCriticalHitChance) - 1; // minus 1 because arrays start at 0


    //while everything here is calculating crit damage, so need to add gCritMultiplier = 3; for that crit boosting ability
   else if ((!(DoesTargetAbilityBlockCrit(gBattlerTarget)))
     && !(gStatuses3[gBattlerAttacker] & STATUS3_CANT_SCORE_A_CRIT)
     && !(gBattleTypeFlags & BATTLE_TYPE_OLD_MAN_TUTORIAL)
     && (Random() % gCriticalHitChance[critChance] == 0) //sets crit odds by array and crit ratio, random % selects crit odds based on stat stage i.e if 0, uses 1st value in array i.e random 16 == 0 for 1 in 16 crit chance
     && (!(gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE) || BtlCtrl_OakOldMan_TestState2Flag(1))
     && !(gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
     && !(gBattleMoves[gCurrentMove].flags & FLAG_ALWAYS_CRIT)
     && !(gStatuses3[gBattlerAttacker] & STATUS3_LASER_FOCUS)
     && !((GetBattlerAbility(gBattlerAttacker) == ABILITY_MERCILESS) && gBattleMons[gBattlerTarget].status1 & STATUS1_PSN_ANY) //unsure if this is right
     && !(gSideStatuses[gBattlerTarget] & SIDE_STATUS_LUCKY_CHANT))
    {
        gCritMultiplier = 2;
        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_SNIPER)  //could possibly be if instead of else if
        {
            gCritMultiplier = 3;
        }

    }//...why did I make this an else if I have no idea, and see no reason for doing it...
    //ok now I see I set it for always crit effects
    //to go here //think to make simpler will replace this line with a check for if ability blocks crit
   else if ((!(DoesTargetAbilityBlockCrit(gBattlerTarget)))
        && !(gStatuses3[gBattlerAttacker] & STATUS3_CANT_SCORE_A_CRIT)
        && !(gBattleTypeFlags & BATTLE_TYPE_OLD_MAN_TUTORIAL)
        && (!(gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE) || BtlCtrl_OakOldMan_TestState2Flag(1))
        && !(gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
        && ((gBattleMoves[gCurrentMove].flags & FLAG_ALWAYS_CRIT)
            || ((GetBattlerAbility(gBattlerAttacker) == ABILITY_MERCILESS) && gBattleMons[gBattlerTarget].status1 & STATUS1_PSN_ANY)
            || gStatuses3[gBattlerAttacker] & STATUS3_LASER_FOCUS)
         && !(gSideStatuses[gBattlerTarget] & SIDE_STATUS_LUCKY_CHANT)) //may run as regular if, but should set crit effect without regarding chance
        {
            gCritMultiplier = 2;
            if (GetBattlerAbility(gBattlerAttacker) == ABILITY_SNIPER)  //could possibly be if instead of else if, but should be fine
            {
                gCritMultiplier = 3;
            }
        } 
    
    else
        gCritMultiplier = 1;
    if (!IsBlackFogNotOnField()
    || gCurrentMove == MOVE_SURGING_STRIKES
    || gCurrentMove == MOVE_WICKED_BLOW) //black fog on field no one can crit, and urshifu signature rebalance
        gCritMultiplier = 1;
    
    ++gBattlescriptCurrInstr;
}

bool8 DoesTargetAbilityBlockCrit(u8 Targetbattler)
{
    u16 ability = GetBattlerAbility(Targetbattler);
    bool8 block = FALSE;

     if (ability == ABILITY_BATTLE_ARMOR
        || ability == ABILITY_SHELL_ARMOR
        || (ability == ABILITY_MAGMA_ARMOR && IsPhysicalMove(gBattlerAttacker, gCurrentMove)) //removed physical move macro for function consolidating effects
        || ability == ABILITY_INNER_FOCUS
        || (ability == ABILITY_TANGLED_FEET && gBattleMons[Targetbattler].status2 & STATUS2_CONFUSION))
        block = TRUE;

    return block;
}//replace steadfast with inner focus, makes more thematic sense
//considering whether should add exclusion for canbeconfused to tangledfeet,
//since bug mon can be confused but are immune to confuse effects because of other sense,
//so would never hit themselves? well still makes sense, it forces them to rely on
//other sense making them stronger, without the draw back so yeah that's fine
//note find bug mon can give tangled feet to lol, think the new gen 8 one,
//that's a centipede that gives orders to troup if it is a bug hmm
//don't "need" to add bug as tangled feet has already been added to exclusion so mon never hit themselves

static void TryUpdateRoundTurnOrder(void)
{
    if (IsDoubleBattle())  //Potentially Add on for rotation etc.
    {
        u32 i;
        u32 j = 0;
        u32 k = 0;
        u32 currRounder = 0;
        u8 roundUsers[3] = {0xFF, 0xFF, 0xFF};
        u8 nonRoundUsers[3] = {0xFF, 0xFF, 0xFF};
        for (i = 0; i < gBattlersCount; i++)
        {
            if (gBattlerByTurnOrder[i] == gBattlerAttacker)
            {
                currRounder = i + 1; // Current battler going after attacker
                break;
            }
        }

        // Get battlers after us using round
        for (i = currRounder; i < gBattlersCount; i++)
        {
            if (gChosenMoveByBattler[gBattlerByTurnOrder[i]] == MOVE_ROUND)
                roundUsers[j++] = gBattlerByTurnOrder[i];
            else
                nonRoundUsers[k++] = gBattlerByTurnOrder[i];
        }

        // update turn order for round users
        for (i = 0; roundUsers[i] != 0xFF && i < 3; i++)
        {
            gBattlerByTurnOrder[currRounder] = roundUsers[i];
            gProtectStructs[roundUsers[i]].quash = TRUE; // Make it so their turn order can't be changed again
            currRounder++;
        }

        // Update turn order for non-round users
        for (i = 0; nonRoundUsers[i] != 0xFF && i < 3; i++)
        {
            gBattlerByTurnOrder[currRounder] = nonRoundUsers[i];
            currRounder++;
        }
    }
}

bool8 CanMultiTask(u16 move) //works, but now I need to negate the jump, because it will still attack multiple times otherwise  done!
{
    u16 i;
    for (i = 0; sMultiTaskExcludedEffects[i] != MULTI_TASK_FORBIDDEN_END && sMultiTaskExcludedEffects[i] != gBattleMoves[move].effect; ++i);
    ;
    if (sMultiTaskExcludedEffects[i] == MULTI_TASK_FORBIDDEN_END
    && gBattleMoves[move].split != SPLIT_STATUS) //should mean if loop through till end, move can be multi tasked
        return TRUE;
    else
        return FALSE;
}

//damgage formula emerald puts stab checks here
//fire red puts it all in typecalc
static void atk05_damagecalc(void)
{
    u32 sideStatus = gSideStatuses[GetBattlerSide(gBattlerTarget)]; // rolled effects into calcbasedamage

    

    //think dynamicbasepower here just means if dynamicbasepower not 0, use it instead fo move power? //yup confirmed
    gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker],
                                            &gBattleMons[gBattlerTarget],
                                            gCurrentMove,
                                            sideStatus,
                                            gDynamicBasePower,
                                            gBattleStruct->dynamicMoveType,
                                            gBattlerAttacker,
                                            gBattlerTarget);
    //consider apply type setting right here,
    //before crit, so I have a smaller number to deal w
    //so even less chance of overflow

    //apply crit
    gBattleMoveDamage = gBattleMoveDamage * gCritMultiplier;// * gBattleScripting.dmgMultiplier; // this makes it so gcritmultiplier value is how much crit is, so sniper shuold work
    if (gStatuses3[gBattlerAttacker] & STATUS3_CHARGED_UP && GetMoveType(TYPE_ELECTRIC, gBattlerAttacker) == TYPE_ELECTRIC)//pretty sure no longer using dmgMultiplier?
        gBattleMoveDamage *= 2;
    if (gProtectStructs[gBattlerAttacker].helpingHand)
        gBattleMoveDamage = gBattleMoveDamage * 15 / 10; 
    
    ++gBattlescriptCurrInstr;
}

s32 AI_CalcDmgFormula(u8 attacker, u8 defender) //made for ai .c update
{
    u32 sideStatus = gSideStatuses[GetBattlerSide(defender)];

   

    gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[attacker],
                                            &gBattleMons[defender],
                                            gCurrentMove,
                                            sideStatus,
                                            gDynamicBasePower,
                                            gBattleStruct->dynamicMoveType,
                                            attacker,
                                            defender);
    //gMultiTask = 0;
    gBattleMoveDamage = gBattleMoveDamage * gCritMultiplier;// * gBattleScripting.dmgMultiplier; //so dmgMultiplier isn't used so does it default to 0? vsonic checekd it defaults to 1 so not a problem
    if (gStatuses3[attacker] & STATUS3_CHARGED_UP && GetMoveType(TYPE_ELECTRIC, attacker) == TYPE_ELECTRIC)  //but its actually something I can remove, just replace with gbattlemovedmg *=2 need do not rn
        gBattleMoveDamage *= 2;
    if (gProtectStructs[attacker].helpingHand)
        gBattleMoveDamage = gBattleMoveDamage * 15 / 10;

    return gBattleMoveDamage;
}

void AI_CalcDmg(u8 attacker, u8 defender) //needed for ai script  , brought back upadted to match
{
    u32 sideStatus = gSideStatuses[GetBattlerSide(defender)];

    

    gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[attacker],
                                            &gBattleMons[defender],
                                            gCurrentMove,
                                            sideStatus,
                                            gDynamicBasePower,
                                            gBattleStruct->dynamicMoveType,
                                            attacker,
                                            defender);
    //gMultiTask = 0;
    gBattleMoveDamage = gBattleMoveDamage * gCritMultiplier;// * gBattleScripting.dmgMultiplier;
    if (gStatuses3[attacker] & STATUS3_CHARGED_UP && GetMoveType(TYPE_ELECTRIC, attacker) == TYPE_ELECTRIC)
        gBattleMoveDamage *= 2;
    if (gProtectStructs[attacker].helpingHand)
        gBattleMoveDamage = gBattleMoveDamage * 15 / 10;
    
}

#define TYPE_DMG_MODULATER
//can use this to setup inverse world ability for giratina origin
//realized should put multiplier conditionals OUTSIDE of the switch, so they can be processed properly inside it.
//Differnt from emerald function as it sets multiplier and move result flags togther, which is why it needs the swich
//separating it out makes it easier to shift multiplier  with conditionals, but can still just do it at the top here.
//The only effect types I need to handle with this function, rather than just the type calc functions, are those that effect multiple types
//rather than just requiring a single line edit, like scrappy, freeze dry etc. 
//I don't see this used literally anywhere?? 
void ModulateDmgByType(u8 multiplier)   //Put all ability effects above ring target.
{
    u8 moveType = 0;
    GET_MOVE_TYPE(gCurrentMove,moveType); //need add delta stream logic for inverse battles and inverse abilities vsonic

    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_INVERSE_WORLD)
    {
        if (multiplier == TYPE_MUL_NOT_EFFECTIVE)
            multiplier = TYPE_MUL_SUPER_EFFECTIVE;

        else if (multiplier == TYPE_MUL_NO_EFFECT)
            multiplier = TYPE_MUL_NORMAL;
    }

    if (GetBattlerAbility(gBattlerTarget) == ABILITY_INVERSE_WORLD)//neutral = no effect,  not effective = super,  super = not effective
    {
        //if ; else if conditional for multiplier shift
        if (multiplier == TYPE_MUL_NOT_EFFECTIVE)
            multiplier = TYPE_MUL_SUPER_EFFECTIVE; 

        else if (multiplier == TYPE_MUL_SUPER_EFFECTIVE)
            multiplier = TYPE_MUL_NOT_EFFECTIVE;

        else if (multiplier == TYPE_MUL_NO_EFFECT)
            multiplier = TYPE_MUL_NORMAL;

        else if (multiplier == TYPE_MUL_NORMAL)
            multiplier = TYPE_MUL_NO_EFFECT;
    }

    if (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_RING_TARGET
        && multiplier == TYPE_MUL_NO_EFFECT)
        multiplier = TYPE_MUL_NORMAL;   //not 100 on if it would work but should turn no effect into normal effectiveness
    
    if (IsBattlerWeatherAffected(gBattlerTarget, WEATHER_STRONG_WINDS)) //ok think best put this in mod damage multiplier to change multiplier to neutral
    {
        if (!DoesSideHaveAbility(gBattlerAttacker, ABILITY_CLOUD_NINE))
        {
            if (IS_BATTLER_OF_TYPE(gBattlerTarget,TYPE_FLYING))
            {
                if (moveType == TYPE_ROCK
                || moveType == TYPE_ELECTRIC
                || moveType == TYPE_ICE)
                {
                    if (multiplier == TYPE_MUL_SUPER_EFFECTIVE)
                    {
                        multiplier = TYPE_MUL_NORMAL;
                    }
                } //replace with 
            }//ok thanks to DaWoblefet on youtube, I now know how this ability works and the proper way to set this up
        }
    }

    gBattleMoveDamage = gBattleMoveDamage * multiplier / 10;    //sets dmg from multiplier
    if (gBattleMoveDamage == 0 && multiplier)   //doesn't need to be below switch, just below multiplier augments
        gBattleMoveDamage = 1;
    
    switch (multiplier) //typecalc adjusts multiplier passed 2x or .5,  this uses multiplier to set flag, which decides effectiveness sound
    {
    case TYPE_MUL_NO_EFFECT:
        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        gMoveResultFlags &= ~MOVE_RESULT_NOT_VERY_EFFECTIVE;
        gMoveResultFlags &= ~MOVE_RESULT_SUPER_EFFECTIVE;
        break;  
    case TYPE_MUL_NOT_EFFECTIVE:
        /*if (gBattleMoves[gCurrentMove].power && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            gMoveResultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
            gMoveResultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
        }*/
        if (gBattleMoves[gCurrentMove].power && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE) //since it sets result flag for each type, I think what this means is remove super flag 
                gMoveResultFlags &= ~MOVE_RESULT_SUPER_EFFECTIVE; // if next multiplier is not very effective, effect becomes neutral.
            else
                gMoveResultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        }
        break;
    case TYPE_MUL_SUPER_EFFECTIVE:
        /*if (gBattleMoves[gCurrentMove].power && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            gMoveResultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
            gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
        }*/
        if (gBattleMoves[gCurrentMove].power && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            if (gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
                gMoveResultFlags &= ~MOVE_RESULT_NOT_VERY_EFFECTIVE;
            else
                gMoveResultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
        }
        break;
    case TYPE_MUL_NORMAL:
        /*if (gBattleMoves[gCurrentMove].power && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
        }*/
        if (gBattleMoves[gCurrentMove].power && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            //doesnt set flags
        }
        break;
    }//case normal isn't shown here, because its the absence of any of the flags, so moving through the case and skipping each block, would auto set normal effctiveness
    //and base game had no need to explicitly set something as normal

} //reverted to old setup, potentailly issue was case typemulnrmal?

#define TYPE_AND_STAB_CHECK //-review this make sure it makes sense to put before damagecalc at all
static void atk06_typecalc(void) //ok checks type think sets effectiveness, but also does stab, with that in mind this MUST go after damagecalc function or stab doesn't work.
{   //from the looks of it, typecalc before damagecalc is just to decide if the move should land and does'nt augment damage?
    s32 i = 0;  //believe that's right as moves like rollout had typecalc first used command typecalc2 which didn't have a stab check
    u8 moveType, argument; //as gbattlemovedamage is set by damagecalc, any use of it beforehand would be multiplying by 0
    u8 type1 = gBattleMons[gBattlerTarget].type1, type2 = gBattleMons[gBattlerTarget].type2, type3 = gBattleMons[gBattlerTarget].type3;
    u16 effect = gBattleMoves[gCurrentMove].effect; //just realized should prob swap these for battlemons types since all types can shift, find where base stats becomes battlemons
    uq4_12_t multiplier;

    ///had add counter and the like, as otherwise triggers supesr effective
    if (gCurrentMove == MOVE_STRUGGLE || gCurrentMove == MOVE_BIDE || gCurrentMove == MOVE_COUNTER || gCurrentMove == MOVE_MIRROR_COAT || gCurrentMove == MOVE_METAL_BURST) //should let hit ghost types could just remove typecalc bs from script instead...
    {
        ++gBattlescriptCurrInstr;
        return;
    }

    if (gBattleMons[gBattlerAttacker].species == SPECIES_ARCEUS && gCurrentMove == MOVE_JUDGMENT)
    {
        //set here tobe arceus only effect
        u32 i;
        bool8 foundType = 0;

        for (i = 0; i < NUMBER_OF_MON_TYPES; i++)//realized problem I'm attempting to set typep before I've selecteed a target...rage works as its based on the attacker type which is alwayss known/constant
        {
            //ok checked this, it can recognize uq 1.55 but when I multiply its something else?
            //tested w uq 8_8 and it does match up at == 1.55 at least
            //in type effectiveness option it also proves it recognizes == 0.775 ???
            //ok setup debug option to just show type effectiveness so I can see what's happening
            if (CalcTypeEffectivenessMultiplier(gCurrentMove, i, gBattlerAttacker, gBattlerTarget, FALSE) >= UQ_4_12(1.55)) //issue was ground check wasn't included in update result flag check
            {
                gBattleStruct->dynamicMoveType = i; //set dynamic type, which assigns to movetype in getmovetype below
                //SetJudgmentTypeString(i);
                foundType = TRUE;
                break; //ok found issue, its not wrong grounded logic, its that calctypeeff, sets it to miss and play floating string
            }//and since this is a loop it encounters the ground loop, before it gets to rock so I need to do a switch case
            //but i need a way to get the type I need
        }


        if (!(foundType)) //IDK What's happening right now, - put result brackets around ground check now fixed
            gBattleStruct->dynamicMoveType = TYPE_MYSTERY;  //
        
    }
    argument = gBattleMoves[gCurrentMove].argument;
    GET_MOVE_TYPE(gCurrentMove, moveType); //could put above, but setting here to ensure all passing/working correctly
    SetJudgmentTypeString(moveType); //putting logic above get type fixed it, this moslty works, just issue with rock moves triggering ground exclusion for floating mon
    multiplier = CalcTypeEffectivenessMultiplier(gCurrentMove, moveType, gBattlerAttacker, gBattlerTarget, TRUE);
    // check stab
    if (effect != EFFECT_COUNTER && effect != EFFECT_MIRROR_COAT)   //skip stab-likes for mirror coat & counter
    {
        //Special condition for arceus, gives stab in everything, and is neutral to everything with type change
        //arceus wont terra because it already "has" every type
        //so change to else if, after adding unique terra from above comment section
        if (gBattleMons[gBattlerAttacker].species == SPECIES_ARCEUS)
        {
            gBattleMoveDamage = gBattleMoveDamage * 135;
            gBattleMoveDamage = gBattleMoveDamage / 100;
        }//for psuedo terra could instead use arceus plates for this,  rather than changing type
        //holding them will make judgement take on the type of plate, and boost dmg by 25%
        
        else if (IS_BATTLER_OF_TYPE(gBattlerAttacker, moveType)
            || (gBattleMoves[gCurrentMove].effect == EFFECT_TWO_TYPED_MOVE
                && IS_BATTLER_OF_TYPE(gBattlerAttacker, argument)))
        {
            if (GetBattlerAbility(gBattlerAttacker) == ABILITY_ADAPTABILITY)
            {
                gBattleMoveDamage = gBattleMoveDamage * 175;
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }
            else
            {
                gBattleMoveDamage = gBattleMoveDamage * 135;
                gBattleMoveDamage = gBattleMoveDamage / 100;
            } //wanted to add small boost to this for joat inclusvive to stab but couldn't do, it had stronger effect on not effective than super
                //so anything added here would just disincentive using coverage/non stab moves
        }
        //on the other hand keeping it inclusive could work/be fine as my meta would already be more focused on the mon stats/stab typing etc. than super effective coverage moves
        //so it'd be played more like have a solid stab move, have 2 or so status moves, and a coverage move (that possibly has its own secondary effect/debuff)
        //if it was inclusive it'd already suit that type of setup, it'd make them even more suited for that format, the stab move woudl be even stronger
        //and their coverage move would also be more useful than on non-normal mon.
        //and that also highlights the strength of your type, as being more linked to moves of that type  
        //the mileage would be limited to how many resist you.  but that's more a buff to those already strong types than normal...
        //and I cant boost joat while keeping it exclusive as then it'd just be the arceus buff
        //ok will keep it as it currently is, but to get the most of this will have to greatly tweak movesets so normal types
        //actually have the type options to be THE coverage warriors try to keep things make sense, they get most coverage
        //but not somehting that should be super against their alternate typing? like normal/flying not getting an ice/electric move?
        //check gen 4 tutor moveset for first example of coverage moves to learn, from bulbapedia

        //joat check jack of all trades  inclusive normal type dmg buff 
        //joat stacks w stab long as not normal move, added mystrey type exclusion for normalize change
        //forgot calculatebasedamage in pokemon.c, has it set so mystery type does 0 damage will need to remove that. 
        //why does it even do that? there are no mystery moves, is it an extra failsafe for hidden power?
        else if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_NORMAL)) //added mystery line to prevent triggering joat, on normalize
        {
            if ((moveType != TYPE_NORMAL && moveType != TYPE_MYSTERY)
                || (gBattleMoves[gCurrentMove].effect == EFFECT_TWO_TYPED_MOVE
                    && (argument != TYPE_NORMAL && argument != TYPE_MYSTERY)))
            {
                gBattleMoveDamage = gBattleMoveDamage * 117; //on recomendation from uploading cut power back
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }
        } //changed joat to be non inclusive with stab

        /*else if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GROUND)) //BONUS for groud mon, to balance changes
        {
            if ((moveType == TYPE_ROCK)
                || (gBattleMoves[gCurrentMove].effect == EFFECT_TWO_TYPED_MOVE
                    && (argument == TYPE_ROCK)))
            {
                gBattleMoveDamage = gBattleMoveDamage * 115;
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }
        }*/

        //alt terra, terra is glorified 3rd type, so my idea  is just make it change type 3
        //but would also need to add the part where terra of same type as mon doubles stab.
        //it turnsm 1.5 stab into adaptability  2.0 stab so from +50% to +100%
        //my version would be once per battle, also, but wouldn't require recharging for more options, 
        //I don't think I can come up with a way to get around giving up item slot for it though
        //ok so 1.5 up to 2.0  is  a 33% increase so I can do a multiplier of 1.34 to do equivalent boost for terra
        //so gbattleMoveDamage *= 134;
        //gbattleMoveDamage / 100;

        /*if ((type3 == type1 || type3 == type2)
            && type3 == moveType)
        {
            gbattleMoveDamage *= 134;
            gbattleMoveDamage /= 100;
        }
        */ //keep above arceus check think put above joat check as well, but make this inclusive
        //make normal type geod/psuedo terra have previous joat effect where it stacks with stab  at 125%, so lower buff wider effect
        //also add flag or special status for this form, so its distinct from joat

        
    }
    /*if (gBattleMons[gBattlerTarget].ability == ABILITY_LEVITATE && moveType == TYPE_GROUND)
    {
        gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
        gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0;
        gBattleCommunication[6] = moveType;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }*/
    
    //need to add to ai, they can't understand this.(double check, but is in ai type calc function)
    //dmg undergroud  is just for thousand arrows and since I changed type and made it based of being grounded instead
    //think can just remove that flag entirely freeing up more options for later
    //groudn is neutral to flying but just can't hit them if htey aren't grounded
    //so replace this check with just flag dmg_in_air which thousand arrows ALSO has
    if (!(IsBattlerGrounded(gBattlerTarget)) && moveType == TYPE_GROUND && !(gBattleMoves[gCurrentMove].flags & FLAG_GROUND_HITS_FLOATING)) 
    {
        gMoveResultFlags |= (MOVE_RESULT_MISSED);
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0; //typecalc & typecalc2 are different, tp2 doesn't have this
        gBattleCommunication[6] = B_MSG_GROUND_MISS;
    }
    if (moveType == TYPE_WATER && GetBattlerAbility(gBattlerTarget) == ABILITY_LIQUID_SOUL) //new buff for liquid soul
    {
        gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0; //typecalc & typecalc2 are different, tp2 doesn't have this
        PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
        gBattleCommunication[6] = B_MSG_ABILITY_TYPE_MISS;

        gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);

    }
    else if (gBattleMons[gBattlerTarget].hp != 0)
    {
        // take type effectiveness - multiply, return actual damage done
        gBattleMoveDamage = ApplyModifier(multiplier, gBattleMoveDamage);  
        //tested type replacemente seems to work, need more indepth test doduo etc.
        //seems to work differently than base, super/resisted dmg doen't cancel out becuase dif multipliers, 
        //-addressed issue
        //think applymod should do everything I need does the last divide 
        //after applying to dmg and then rounds idk...

        /*while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE) //identified issue with typecalc, its only reading type 1 for some reason,
        {
            if (TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT)
            {
                if (gBattleMons[gBattlerTarget].status2 & STATUS2_FORESIGHT)
                    break;//
                //could potentially put scrappy logic right here, would just need do attacker abiilty scrappy break
                //I think my current setup would work though.
                i += 3; //don't undeerstand what this is doing.     //ok now I get it, starts at i+0 2 more arguments in row, using +3 moves to the next row
                continue;//its a while lloop, instead of a for loop, but this is essentially the ++i part, its the increment that changes type, which is why its also at the bottom
            }//logic is while atk type isnt endtable i.e last row of type chart, do stuff inside, then at bottom increment to next row and start again. 
            else if (TYPE_EFFECT_ATK_TYPE(i) == moveType)//loops through entire type chart
            {
                // check type1
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)//this define checks the type chart, chart is broken into 3 fields per row, i reads the row
                {
                    
                        ModulateDmgByType(TYPE_EFFECT_MULTIPLIER(i));   //which will translate to correct effectiveness sound message etc.
                }
                // check type2
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2) //emerald update literally just adds a check for type 3
                {
                        ModulateDmgByType(TYPE_EFFECT_MULTIPLIER(i));
                }
                //check type3
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {
                        ModulateDmgByType(TYPE_EFFECT_MULTIPLIER(i));
                                                                    //ok this function is setting the multiplyer here
                                                                        //while calc2 is setting the effectiveness flag
                        //seems modulatedmgbytype  & modbytype2 may be the same as only 2 has a flag argument?
                }
               
            
            }
            
            i += 3;
        }
        */
    } //think can remove the attacksthisturn from this so I can use it in attackcanceler
    //  its not really doing anything here, and I already have if move power isn't 0
    if ((GetBattlerAbility(gBattlerTarget) == ABILITY_WONDER_GUARD && gBattleStruct->SingleUseAbilityTimers[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)])
     && (!(gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE) || ((gMoveResultFlags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
     && gBattleMoves[gCurrentMove].power)   //I know understand this and why it works, its saying if not super effective, and then, 
    {                           //uses both super effective and not very effective bit flags, which balance out to normal effectiveness with or, so only super effective can dmg
        gLastUsedAbility = ABILITY_WONDER_GUARD;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0;
        gBattleCommunication[6] = B_MSG_AVOIDED_DMG;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    if (GetBattlerAbility(gBattlerTarget) == ABILITY_DISPIRIT_GUARD
        && (!(gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE) || ((gMoveResultFlags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        && gBattleMoves[gCurrentMove].power)//this using power means typeless moves get through as made them all power 0
    {
        gLastUsedAbility = ABILITY_DISPIRIT_GUARD;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0;
        gBattleCommunication[6] = B_MSG_AVOIDED_DMG;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    if (gBattleMons[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerAttacker)))].ability == ABILITY_TELEPATHY
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)    //hopefully works, should just make my move not hit ally partner
    {
        gLastUsedAbility = ABILITY_TELEPATHY;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0;
        gBattleCommunication[6] = B_MSG_AVOIDED_DMG;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    if (gMoveResultFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
        gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
    ++gBattlescriptCurrInstr;
}

//think understand now, funciton is in accuract check because it sets move result as missed if type doesn't  hit wonderguard or levitate/the opponent
//its a bit of weird logic, reads type chart before typecalc uses flags rather than moveresult
//for things besides what would be no effect, use of flags is so type readings etc. don't go beyond this function
//I believe they are used in equivalence of moveresult flags
//not 100% but I believe this can be safely removed/ignored and left to typecalc to handle
//yup no longer using this
static void CheckWonderGuardAndLevitate(void)   //can leave as it is, logic i need is in grouded function also included wherever this is called.  think can remove
{
    u8 flags = 0;
    s32 i = 0;
    u8 moveType,argument;
    u8 type1 = gBattleMons[gBattlerTarget].type1, type2 = gBattleMons[gBattlerTarget].type2, type3 = gBattleMons[gBattlerTarget].type3;

    if (gCurrentMove == MOVE_STRUGGLE || !gBattleMoves[gCurrentMove].power)
        return;//if move is struggle or 0 power ignores checks
    argument = gBattleMoves[gCurrentMove].argument;
    GET_MOVE_TYPE(gCurrentMove, moveType);
    //&& !IsBattlerGrounded(battlerDef)

    if (!(IsBattlerGrounded(gBattlerTarget)) && moveType == TYPE_GROUND && !(gBattleMoves[gCurrentMove].flags & FLAG_GROUND_HITS_FLOATING))
    {
        gBattleCommunication[6] = B_MSG_GROUND_MISS;
        return;
    } 
        
    if (moveType == TYPE_WATER && GetBattlerAbility(gBattlerTarget) == ABILITY_LIQUID_SOUL) //new buff for liquid soul
    {
        gLastUsedAbility = ABILITY_LIQUID_SOUL;
        PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
        gBattleCommunication[6] = B_MSG_ABILITY_TYPE_MISS;
        RecordAbilityBattle(gBattlerTarget, ABILITY_LIQUID_SOUL);
        return;

    }
    while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE)    //as of now doesnt have two type logic, seeking to replace function use
    {
        /*if (TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT)
        {
            if (gBattleMons[gBattlerTarget].status2 & STATUS2_FORESIGHT)//normal ghost is still after foresight need to change later but can still u
                break;
            i += 3;
            continue;
        }*///shouldn't I jsust be able to make these else ifs? should already mean if type 2 not type 1, if I use else if etc.
        if (TYPE_EFFECT_ATK_TYPE(i) == moveType) //same for tyep 3, just be else if type 3 && type 3 != type mystey
        {
            // check no effect 
            if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
            {
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                {
                    gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                    gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
                }
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                {
                    gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                    gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
                }
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {
                    gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                    gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
                }
            }
            // check no effect  //need add type 3 arguments to this
            /*if (TYPE_EFFECT_DEF_TYPE(i) == type1
                && TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
            {
                gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
            }
            if (TYPE_EFFECT_DEF_TYPE(i) == type2 &&
                type1 != type2 &&
                TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
            {
                gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
            }
            if (type3 != TYPE_MYSTERY)
            {
                if ((TYPE_EFFECT_DEF_TYPE(i) == type3)
                    && (type3 != type2 
                    && type3 != type1))
                {
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                    {
                        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                        gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
                    }
                    
                }
            }*/
            // check super effective
            if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
            {
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                {
                    flags |= 1;
                }
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                {
                    flags |= 1;
                }
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {
                    flags |= 1;
                }
            }
            // check super effective
            /*if (TYPE_EFFECT_DEF_TYPE(i) == type1 && TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                flags |= 1;
            if (TYPE_EFFECT_DEF_TYPE(i) == type2
             && type1 != type2
             && TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                flags |= 1;
            if (type3 != TYPE_MYSTERY)
            {
                if ((TYPE_EFFECT_DEF_TYPE(i) == type3)
                    && (type3 != type2 
                    && type3 != type1))
                {
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                    {
                        flags |= 1;
                    }
                    
                }
            }*/

            // check not very effective
            if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
            {
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                {
                    flags |= 2;
                }
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                {
                    flags |= 2;
                }
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {
                    flags |= 2;
                }
            }
            
            // check not very effective
            /*if (TYPE_EFFECT_DEF_TYPE(i) == type1 && TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                flags |= 2;
            if (TYPE_EFFECT_DEF_TYPE(i) == type2
             && type1 != type2
             && TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                flags |= 2;
             if (type3 != TYPE_MYSTERY)
            {
                if ((TYPE_EFFECT_DEF_TYPE(i) == type3)
                    && (type3 != type2 
                    && type3 != type1))
                {
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                    {
                        flags |= 2;
                    }
                    
                }
            }*/
            
        }
        
        i += 3;
    }
    if (GetBattlerAbility(gBattlerTarget) == ABILITY_WONDER_GUARD)
    {
        if (((flags & 2) || !(flags & 1)) && gBattleMoves[gCurrentMove].power) //think mean if not very effect, or not super effective
        {
            gLastUsedAbility = ABILITY_WONDER_GUARD;
            gBattleCommunication[6] = 3; //somehow this is reading gmissstringIds in battle_message.c, think something to do with resultmessage comm
            RecordAbilityBattle(gBattlerTarget, ABILITY_WONDER_GUARD);
        }
    }
    else if (GetBattlerAbility(gBattlerTarget) == ABILITY_DISPIRIT_GUARD)
    {
        if (((flags & 1) || !(flags & 2)) && gBattleMoves[gCurrentMove].power) //think reversing was right. 
        { //    I believe it says if super effectie, or not Not effective, do same as wonder guard.
            gLastUsedAbility = ABILITY_DISPIRIT_GUARD;
            gBattleCommunication[6] = 3;
            RecordAbilityBattle(gBattlerTarget, ABILITY_DISPIRIT_GUARD);
        }
    } // the way this reads confuses me, I may just replace with cfru argument instead, nvm I just reversed whatever was in wonderguard function.
    else if (gBattleMons[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerAttacker)))].ability == ABILITY_TELEPATHY
       && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)
    {
        gLastUsedAbility = ABILITY_TELEPATHY;
        gBattleCommunication[6] = 3; //vbelieve sets moveresult miss
        RecordAbilityBattle(gBattlerTarget, ABILITY_TELEPATHY);
    }   //vsonic IMPORTANT
}

// same as ModulateDmgByType except different arguments
static void ModulateDmgByType2(u8 multiplier, u16 move, u8 *flags)//maybe do dual type here?
{
    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_INVERSE_WORLD
        && multiplier == TYPE_MUL_NOT_EFFECTIVE)
        multiplier = TYPE_MUL_SUPER_EFFECTIVE;

    if (GetBattlerAbility(gBattlerTarget) == ABILITY_INVERSE_WORLD)//neutral = no effect,  not effective = super,  super = not effective
    {
        //if ; else if conditional for multiplier shift
        if (multiplier == TYPE_MUL_NOT_EFFECTIVE)
            multiplier = TYPE_MUL_SUPER_EFFECTIVE;

        else if (multiplier == TYPE_MUL_SUPER_EFFECTIVE)
            multiplier = TYPE_MUL_NOT_EFFECTIVE;

        else if (multiplier == TYPE_MUL_NO_EFFECT)
            multiplier = TYPE_MUL_NORMAL;

        else if (multiplier == TYPE_MUL_NORMAL)
            multiplier = TYPE_MUL_NO_EFFECT;
    }

    if (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_RING_TARGET
        && multiplier == TYPE_MUL_NO_EFFECT)
        multiplier = TYPE_MUL_NORMAL;   //not 100 on if it would work but should turn no effect into normal effectiveness

    gBattleMoveDamage = gBattleMoveDamage * multiplier / 10;
    if (gBattleMoveDamage == 0 && multiplier != TYPE_MUL_NO_EFFECT)
        gBattleMoveDamage = 1;
    switch (multiplier) //ok difference is for some reason it uses a flag pointer argument rather than gmoveresultflags?
    {                   //so the first one sets it, but this one only points to it?
    case TYPE_MUL_NO_EFFECT:
        *flags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        *flags &= ~MOVE_RESULT_NOT_VERY_EFFECTIVE;
        *flags &= ~MOVE_RESULT_SUPER_EFFECTIVE;
        //gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        //gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);
        break;
    case TYPE_MUL_NOT_EFFECTIVE:
        //gMoveResultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        //gMoveResultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
        if (gBattleMoves[move].power && !(*flags & MOVE_RESULT_NO_EFFECT))
        {
            if (*flags & MOVE_RESULT_SUPER_EFFECTIVE)
                *flags &= ~MOVE_RESULT_SUPER_EFFECTIVE;
            else
                *flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        }
        break;
    case TYPE_MUL_SUPER_EFFECTIVE:
        //gMoveResultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
        //gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
        if (gBattleMoves[move].power && !(*flags & MOVE_RESULT_NO_EFFECT))
        {
            if (*flags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
                *flags &= ~MOVE_RESULT_NOT_VERY_EFFECTIVE;
            else
                *flags |= MOVE_RESULT_SUPER_EFFECTIVE;
        }
        break;
    case TYPE_MUL_NORMAL:
      //  gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
        break;
    }
}

//appears to be used for ai logic?
u8 TypeCalc(u16 move, u8 attacker, u8 defender)
{
    s32 i = 0;
    u8 flags = 0;
    u8 moveType,argument;
    u8 type1 = gBattleMons[defender].type1, type2 = gBattleMons[defender].type2, type3 = gBattleMons[defender].type3;
    u16 effect = gBattleMoves[gCurrentMove].effect;
    u16 multiplier;

    if (move == MOVE_STRUGGLE || move ==  MOVE_BIDE)
        return 0;
    argument = gBattleMoves[move].argument;
    GET_MOVE_TYPE(move,moveType);
    //GET_MOVE_TYPE(gCurrentMove,argument);
    multiplier = CalcTypeEffectivenessMultiplier(gCurrentMove, moveType, attacker, defender, FALSE);
    // check stab
    if (effect != EFFECT_COUNTER && effect != EFFECT_MIRROR_COAT)   //skip stab-likes for mirror coat & counter
    {
        //Special condition for arceus, gives stab in everything, and is neutral to everything with type change
        //arceus wont terra because it already "has" every type
        //so change to else if, after adding unique terra from above comment section
        if (gBattleMons[attacker].species == SPECIES_ARCEUS)
        {
            gBattleMoveDamage = gBattleMoveDamage * 135;
            gBattleMoveDamage = gBattleMoveDamage / 100;
        } //for psuedo terra could instead use arceus plates for this,  rather than changing type
        //holding them will make judgement take on the type of plate, and boost dmg by 25%

        else if (IS_BATTLER_OF_TYPE(attacker, moveType)
            || (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE
                && IS_BATTLER_OF_TYPE(attacker, argument)))
        {
            if (GetBattlerAbility(attacker) == ABILITY_ADAPTABILITY)
            {
                gBattleMoveDamage = gBattleMoveDamage * 175;
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }
            else
            {
                gBattleMoveDamage = gBattleMoveDamage * 135;
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }

        }

        //joat check jack of all trades  inclusive normal type dmg buff 
        //joat stacks w stab long as not normal move,  aka jack of all types?
        else if (IS_BATTLER_OF_TYPE(attacker, TYPE_NORMAL)) //added mystery line to prevent triggering joat, on normalize
        {
            if ((moveType != TYPE_NORMAL && moveType != TYPE_MYSTERY)
                || (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE
                    && (argument != TYPE_NORMAL && argument != TYPE_MYSTERY)))
            {
                gBattleMoveDamage = gBattleMoveDamage * 117; //cut back on recomendation
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }
        }//changed joat to be non inclusive with stab

        /*else if (IS_BATTLER_OF_TYPE(attacker, TYPE_GROUND)) //BONUS for groud mon, to balance changes
        {
            if ((moveType == TYPE_ROCK)
                || (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE
                    && (argument == TYPE_ROCK)))
            {
                gBattleMoveDamage = gBattleMoveDamage * 115;
                gBattleMoveDamage = gBattleMoveDamage / 100;
            }
        }*/

    }

    if (!(IsBattlerGrounded(defender)) //set without ! it means if function is TRUE aka non-zero
        && moveType == TYPE_GROUND //just realized grounded already has conditions for levitate so I just need that.
        && !(gBattleMoves[move].flags & FLAG_GROUND_HITS_FLOATING))
    {
        flags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    if (moveType == TYPE_WATER && GetBattlerAbility(gBattlerTarget) == ABILITY_LIQUID_SOUL) //new buff for liquid soul
    {
        flags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);

    }
    else if (gBattleMons[defender].hp != 0)
    {
        // take type effectiveness
        gBattleMoveDamage = ApplyModifier(multiplier, gBattleMoveDamage);
        /*while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE)
        {
            if (TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT)
            {
                if (gBattleMons[defender].status2 & STATUS2_FORESIGHT)
                    break;
                i += 3;
                continue;
            }

            else if (TYPE_EFFECT_ATK_TYPE(i) == moveType)
            {
                // check type1
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                        ModulateDmgByType2(TYPE_EFFECT_MULTIPLIER(i), move, &flags);
                // check type2
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                        ModulateDmgByType2(TYPE_EFFECT_MULTIPLIER(i), move, &flags);
                
                //check type3
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {
                        ModulateDmgByType2(TYPE_EFFECT_MULTIPLIER(i), move, &flags);
                }
            }
            i += 3;
        }//attempt at setting dual type moves
        */
    }    
    if ((gBattleMons[defender].ability == ABILITY_WONDER_GUARD && gBattleStruct->SingleUseAbilityTimers[gBattlerPartyIndexes[defender]][GetBattlerSide(defender)])
     && !(flags & MOVE_RESULT_MISSED)     
     && (!(flags & MOVE_RESULT_SUPER_EFFECTIVE) || ((flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
     && gBattleMoves[move].power)
     {
        flags |= MOVE_RESULT_MISSED;
        
     }
        

    if (gBattleMons[defender].ability == ABILITY_DISPIRIT_GUARD
        && !(flags & MOVE_RESULT_MISSED)        
        && (!(flags & MOVE_RESULT_NOT_VERY_EFFECTIVE) || ((flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        && gBattleMoves[move].power)
    {
        flags |= MOVE_RESULT_MISSED;

    }

    if (gBattleMons[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerAttacker)))].ability == ABILITY_TELEPATHY
        && !(flags & MOVE_RESULT_MISSED)
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)    //hopefully works, should just make my move not hit ally partner
    {
        flags |= MOVE_RESULT_MISSED;

    }
    return flags;
}

u8 AI_TypeCalc(u16 move, u16 targetSpecies, u16 targetAbility) //facepalm was using species for battler argument
{
    s32 i = 0;
    u8 flags = 0;
    u8 type1 = gBattleMons[gBattlerTarget].type1, type2 = gBattleMons[gBattlerTarget].type2, type3 = gBattleMons[gBattlerTarget].type3;
    u8 moveType,argument;
    u16 multiplier;

    if (move == MOVE_STRUGGLE || move ==  MOVE_BIDE)
        return 0;
    argument = gBattleMoves[move].argument; //think should replace with getmovetype macro?
    //moveType = gBattleMoves[move].type; //think don't need to change this since battle_main has function for type change
    GET_MOVE_TYPE(move, moveType);
    multiplier = CalcTypeEffectivenessMultiplier(gCurrentMove, moveType, gBattlerAttacker, gBattlerTarget, FALSE); //cehck this if need change 

    if (!(IsBattlerGrounded(gBattlerTarget)) //set without ! it means if function is TRUE aka non-zero
        && moveType == TYPE_GROUND && !(gBattleMoves[move].flags & FLAG_GROUND_HITS_FLOATING))
    {
        flags = MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE;
    }
    if (moveType == TYPE_WATER && targetAbility == ABILITY_LIQUID_SOUL) //new buff for liquid soul
    {
        flags = MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE;

    }
    else if (gBattleMons[gBattlerTarget].hp != 0)
    {
        // take type effectiveness
        gBattleMoveDamage = ApplyModifier(multiplier, gBattleMoveDamage);

        /*while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE) //vsonic also missing two typed logic need add back
        {
            if (TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT)
            {
                i += 3;
                continue;
            }
            if (TYPE_EFFECT_ATK_TYPE(i) == moveType)
            {
                // check type1
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                        ModulateDmgByType2(TYPE_EFFECT_MULTIPLIER(i), move, &flags);
                // check type2
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                        ModulateDmgByType2(TYPE_EFFECT_MULTIPLIER(i), move, &flags);

                //check type3
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {

                        ModulateDmgByType2(TYPE_EFFECT_MULTIPLIER(i), move, &flags);
                }
            }            
            i += 3;
        }*/
    }
    if ((targetAbility == ABILITY_WONDER_GUARD && gBattleStruct->SingleUseAbilityTimers[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)])
     && (!(flags & MOVE_RESULT_SUPER_EFFECTIVE) || ((flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
     && gBattleMoves[move].power)
     {
        flags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        
     }

    if (targetAbility == ABILITY_DISPIRIT_GUARD
        && (!(flags & MOVE_RESULT_NOT_VERY_EFFECTIVE) || ((flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        && gBattleMoves[move].power)
    {
        flags |= MOVE_RESULT_DOESNT_AFFECT_FOE;

    }

    if (gBattleMons[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerAttacker)))].ability == ABILITY_TELEPATHY
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)    //hopefully works, should just make my move not hit ally partner
    {
        flags |= MOVE_RESULT_MISSED;

    }
    return flags;

}

//can remove "canMultiTask" line, but would need to add in a few more effect exclusions,
//do later vsonic
//ok issue with this is its playing wrong species, jst a matter of including enemy party index
static inline void ApplyRandomDmgMultiplier(void) //vsonic test works
{
    u16 rand = Random(); //add can multi task to this filter list // but put ability not multitask
    u16 randPercent = 100 - (rand % 16); //make g values to to store random percent for battler
    //if randPercent is 100 before attack animation run cry with below
    struct Pokemon *mon;
    u16 species; 

    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT) //use this instead taken from mega logic
            mon = &gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]];  //mon being transformed
        else
            mon = &gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]];

    species = GetMonData(mon, MON_DATA_SPECIES);

    //facepalm only noticed this with growl, but I forgot to exclude from STATUS MOVES
    if ((randPercent == 100 || IS_CRIT) 
    && GetBattleMoveSplit(gCurrentMove) != SPLIT_STATUS
    && gBattleMoves[gCurrentMove].effect != EFFECT_MULTI_HIT
    && !(gBattleMoves[gCurrentMove].flags & FLAG_ALWAYS_CRIT) //hope this is still right vsonic
    && gBattleMoves[gCurrentMove].effect != EFFECT_TRIPLE_KICK
    && gBattleMoves[gCurrentMove].effect != EFFECT_BEAT_UP
    && gBattleMoves[gCurrentMove].effect != EFFECT_RECOIL_IF_MISS
    && (CanMultiTask(gCurrentMove) == TRUE) //can remove put this here  for blocking two turn but don't think need to
    && GetBattlerAbility(gBattlerAttacker) != ABILITY_MULTI_TASK) //think shoudl do it, as this is ALWAYS called after critcalc
            PlayCry_Normal(species, 25); //its inline so I "think" that will work and play in the adjustnormaldamage script
    //added effect check to keep from triggering to frequently, as to become annoying
    if (gBattleMoveDamage != 0)//extra thing need look into, moves like disarming voice already play cry, need make sure can't double play
    {
        gBattleMoveDamage *= randPercent;
        gBattleMoveDamage /= 100;
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
    }
}// vsonic IMPORTANT look into SoundTask_WaitForCry && SoundTask_PlayDoubleCry etc. in battle anims

static void Unused_ApplyRandomDmgMultiplier(void)//garbage data for test
{
    ApplyRandomDmgMultiplier();
}

static void atk07_adjustnormaldamage(void)
{
    u8 holdEffect, param, moveType;
    GET_MOVE_TYPE(gCurrentMove,moveType);

    ApplyRandomDmgMultiplier();//high low rolls
    if (gBattleMons[gBattlerTarget].item == ITEM_ENIGMA_BERRY)
    {
        holdEffect = gEnigmaBerries[gBattlerTarget].holdEffect;
        param = gEnigmaBerries[gBattlerTarget].holdEffectParam;
    }
    else
    {
        holdEffect = GetBattlerHoldEffect(gBattlerTarget, TRUE);
        param = ItemId_GetHoldEffectParam(gBattleMons[gBattlerTarget].item);
    }
    gPotentialItemEffectBattler = gBattlerTarget;
    if (holdEffect == HOLD_EFFECT_FOCUS_BAND && (Random() % 100) < param)
    {
        RecordItemEffectBattle(gBattlerTarget, holdEffect);
        gSpecialStatuses[gBattlerTarget].focusBanded = 1;
    }
    else if (holdEffect == HOLD_EFFECT_FOCUS_SASH && BATTLER_MAX_HP(gBattlerTarget))
    {
        RecordItemEffectBattle(gBattlerTarget, holdEffect);
        gSpecialStatuses[gBattlerTarget].focusSashed = TRUE;
    }
    else if (GetBattlerAbility(gBattlerTarget) == ABILITY_STURDY && BATTLER_MAX_HP(gBattlerTarget)) //gen 5 sturdy
    {
        RecordAbilityBattle(gBattlerTarget, ABILITY_STURDY);
        gSpecialStatuses[gBattlerTarget].sturdied = TRUE;
    }

    /*if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_SUBSTITUTE)
     && (gBattleMoves[gCurrentMove].effect == EFFECT_FALSE_SWIPE || gProtectStructs[gBattlerTarget].endured || gSpecialStatuses[gBattlerTarget].focusBanded
         || gSpecialStatuses[gBattlerTarget].focusSashed)
     && gBattleMons[gBattlerTarget].hp <= gBattleMoveDamage)
    {
        gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
        if (gProtectStructs[gBattlerTarget].endured
            && gMultiHitCounter == 0) //should work but change lateer tothe one where decrement is 0. --gmultihit something like that.
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_ENDURED; //and don't forget sturdy
        }
        else if (gSpecialStatuses[gBattlerTarget].focusBanded
            && gMultiHitCounter == 0)   //it works pretty sure the logic its using is if not a multi hit move since only multihit uses the counter
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
    }
    ++gBattlescriptCurrInstr;*/

    //looking at this pretty sure both these need to go above sturdied stuff
    if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMoveDamage >= 1)
        gSpecialStatuses[gBattlerAttacker].damagedMons |= gBitTable[gBattlerTarget];

    // Check gems and damage reducing berries.
    if (gSpecialStatuses[gBattlerTarget].berryReduced
        && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
        && gBattleMons[gBattlerTarget].item)
    {
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_BerryReduceDmg;
        gLastUsedItem = gBattleMons[gBattlerTarget].item;
    }
    if (gSpecialStatuses[gBattlerAttacker].gemBoost
        && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
        && gBattleMons[gBattlerAttacker].item)
    {
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_GemActivates;
        gLastUsedItem = gBattleMons[gBattlerAttacker].item;
    }

    // WEATHER_STRONG_WINDS prints a string when it's about to reduce the power
    // of a move that is Super Effective against a Flying-type Pok�mon.
    if (gBattleWeather & WEATHER_STRONG_WINDS) //ok think best put this in mod damage multiplier to change multiplier to neutral
    {
        if (IS_BATTLER_OF_TYPE(gBattlerTarget,TYPE_FLYING))
        {
            if (moveType == TYPE_ROCK
            || moveType == TYPE_ELECTRIC
            || moveType == TYPE_ICE)
            {

                gBattlerAbility = gBattlerTarget;//dont think this part really needed? keep anyway
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AttackWeakenedByStrongWinds;
            }
        }//ok thanks to DaWoblefet on youtube, I now know how this ability works and the proper way to set this up
        //is indeed in the multiplier logic for modulatedmgbytype in type calc, can leave this here to just do the string logic though
        
    }
    //need setup equivalent of gettypemodifier, think I can do by double looping through the type chart array
    //in battlemain.c  gTypeEffectiveness
    //first use i to loop entire array, use j to loop through attacking types
    //set defense type to type flying
    //finally use condition on return if [j][type_flying] == super effective do thing
    //possibly need to adjust layout of array to be able to read value in atk type def type == effectiveness format
    
    //now that I ported other type chart think can just use that actually, should be simple?

    if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_SUBSTITUTE)
     && (gBattleMoves[gCurrentMove].effect == EFFECT_FALSE_SWIPE || gProtectStructs[gBattlerTarget].endured || gSpecialStatuses[gBattlerTarget].focusBanded || gSpecialStatuses[gBattlerTarget].focusSashed || gSpecialStatuses[gBattlerTarget].sturdied)
     && gBattleMons[gBattlerTarget].hp <= gBattleMoveDamage
     && (gMultiHitCounter == 0 || gMultiHitCounter == gMultiTask))
    {
        gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
        if (gProtectStructs[gBattlerTarget].endured)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_ENDURED;
        }
        else if (gSpecialStatuses[gBattlerTarget].focusBanded)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
        else if (gSpecialStatuses[gBattlerTarget].focusSashed)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
        else if (gSpecialStatuses[gBattlerTarget].sturdied)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedAbility = ABILITY_STURDY;
        }
    }


    
     ++gBattlescriptCurrInstr;
}

// The same as 0x7 except it doesn't check for false swipe move effect.
//only used in future sight/doom desire & confusion self hit, so false swipe doesn't even matter...
//strange in that case this command is prob useless and can just use the normal version
static void atk08_adjustnormaldamage2(void)
{
    u8 holdEffect, param;

    ApplyRandomDmgMultiplier();
    if (gBattleMons[gBattlerTarget].item == ITEM_ENIGMA_BERRY)
    {
        holdEffect = gEnigmaBerries[gBattlerTarget].holdEffect;
        param = gEnigmaBerries[gBattlerTarget].holdEffectParam;
    }
    else
    {
        holdEffect = GetBattlerHoldEffect(gBattlerTarget, TRUE);
        param = ItemId_GetHoldEffectParam(gBattleMons[gBattlerTarget].item);
    }
    gPotentialItemEffectBattler = gBattlerTarget;
    if (holdEffect == HOLD_EFFECT_FOCUS_BAND && (Random() % 100) < param)
    {
        RecordItemEffectBattle(gBattlerTarget, holdEffect);
        gSpecialStatuses[gBattlerTarget].focusBanded = 1;
    }
    else if (holdEffect == HOLD_EFFECT_FOCUS_SASH && BATTLER_MAX_HP(gBattlerTarget))
    {
        RecordItemEffectBattle(gBattlerTarget, holdEffect);
        gSpecialStatuses[gBattlerTarget].focusSashed = TRUE;
    }
    else if (GetBattlerAbility(gBattlerTarget) == ABILITY_STURDY && BATTLER_MAX_HP(gBattlerTarget)) //gen 5 sturdy
    {
        RecordAbilityBattle(gBattlerTarget, ABILITY_STURDY);
        gSpecialStatuses[gBattlerTarget].sturdied = TRUE;
    }

     if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_SUBSTITUTE)
     && (gBattleMoves[gCurrentMove].effect == EFFECT_FALSE_SWIPE || gProtectStructs[gBattlerTarget].endured || gSpecialStatuses[gBattlerTarget].focusBanded || gSpecialStatuses[gBattlerTarget].focusSashed || gSpecialStatuses[gBattlerTarget].sturdied)
     && gBattleMons[gBattlerTarget].hp <= gBattleMoveDamage
     && (gMultiHitCounter == 0 || gMultiHitCounter == gMultiTask))
    {
        gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
        if (gProtectStructs[gBattlerTarget].endured)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_ENDURED;
        }
        else if (gSpecialStatuses[gBattlerTarget].focusBanded)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
        else if (gSpecialStatuses[gBattlerTarget].focusSashed)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
        else if (gSpecialStatuses[gBattlerTarget].sturdied)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedAbility = ABILITY_STURDY;
        }
    }

//END:
  //  gBattlescriptCurrInstr++;

    if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMoveDamage >= 1)
        gSpecialStatuses[gBattlerAttacker].damagedMons |= gBitTable[gBattlerTarget];

    // Check gems and damage reducing berries.
    if (gSpecialStatuses[gBattlerTarget].berryReduced
        && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
        && gBattleMons[gBattlerTarget].item)
    {
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_BerryReduceDmg;
        gLastUsedItem = gBattleMons[gBattlerTarget].item;
    }
    if (gSpecialStatuses[gBattlerAttacker].gemBoost
        && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
        && gBattleMons[gBattlerAttacker].item)
    {
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_GemActivates;
        gLastUsedItem = gBattleMons[gBattlerAttacker].item;
    }

    // WEATHER_STRONG_WINDS prints a string when it's about to reduce the power
    // of a move that is Super Effective against a Flying-type Pok�mon.
   /* if (gBattleWeather & WEATHER_STRONG_WINDS)
    {
        if ((gBattleMons[gBattlerTarget].type1 == TYPE_FLYING
         && GetTypeModifier(moveType, gBattleMons[gBattlerTarget].type1) >= UQ_4_12(1.55))
         || (gBattleMons[gBattlerTarget].type2 == TYPE_FLYING
         && GetTypeModifier(moveType, gBattleMons[gBattlerTarget].type2) >= UQ_4_12(1.55))
         || (gBattleMons[gBattlerTarget].type3 == TYPE_FLYING
         && GetTypeModifier(moveType, gBattleMons[gBattlerTarget].type3) >= UQ_4_12(1.55)))
        {
            gBattlerAbility = gBattlerTarget;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_AttackWeakenedByStrongWinds;
        }
    }*/
    //need setup equivalent of gettypemodifier, think I can do by double looping through the type chart array
    //in battlemain.c  gTypeEffectiveness
    //first use i to loop entire array, use j to loop through attacking types
    //set defense type to type flying
    //finally use condition on return if [j][type_flying] == super effective do thing
    //possibly need to adjust layout of array to be able to read value in atk type def type == effectiveness format
    //ported emerald type setup still in processing, but when setup can use that to read its own chart for use here
    //as this command goes in scripts without typecalc,  main adjsutnormaldamage can juse use gmoveresult super effective
    //as it goes after type calc always...wait if the moves this is used for can never do super effective dmg then...
    //there's no point in it being here...  *facepalm
     ++gBattlescriptCurrInstr;  //AGAIN i FORGOT THIS!!!
}

//look into figure why multi task isn't playing animation again, pretty sure it did previously
//nvm 1, pretty sure it was never setup properly til now, 
//2 decided with feedback its better to just play animation once. (plus makes more sense with original concept idea is hitting with multiple instances of move at once)
//so instituting bug as feature
static void atk09_attackanimation(void)
{
    if (!gBattleControllerExecFlags)
    {
        if ((gHitMarker & HITMARKER_NO_ANIMATIONS) && (gCurrentMove != MOVE_TRANSFORM && gCurrentMove != MOVE_SUBSTITUTE))
        {
            BattleScriptPush(gBattlescriptCurrInstr + 1);
            gBattlescriptCurrInstr = BattleScript_Pausex20;
            ++gBattleScripting.animTurn;
            ++gBattleScripting.animTargetsHit;
        }
        else
        {
            if ((gBattleMoves[gCurrentMove].target & MOVE_TARGET_BOTH
                || gBattleMoves[gCurrentMove].target & MOVE_TARGET_FOES_AND_ALLY
                || gBattleMoves[gCurrentMove].target & MOVE_TARGET_DEPENDS)
             && gBattleScripting.animTargetsHit)  //believe this is play animation once, rather than again for each target hit
            { //also that above line is why powdersnow didn't work, it was a dual target move, and I believe animtargetshit was set on first pass, so it executed this after
                ++gBattlescriptCurrInstr;
                return;
            }
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)) //do animation only if not move result no effect
            {
                if ((GetBattlerAbility(gBattlerAttacker) == ABILITY_MULTI_TASK)
                && CanMultiTask(gCurrentMove)
                && gBattleScripting.animTargetsHit)
                {
                    ++gBattlescriptCurrInstr;
                    return;
                }
                gActiveBattler = gBattlerAttacker;
                BtlController_EmitMoveAnimation(BUFFER_A, gCurrentMove, gBattleScripting.animTurn, gBattleMovePower, gBattleMoveDamage, gBattleMons[gBattlerAttacker].friendship, &gDisableStructs[gBattlerAttacker]);
                ++gBattleScripting.animTurn;
                ++gBattleScripting.animTargetsHit;
                MarkBattlerForControllerExec(gBattlerAttacker);
                ++gBattlescriptCurrInstr;          
            }
            else
            {
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_Pausex20;
            }
        }
    }
}

static void atk0A_waitanimation(void)
{
    if (!gBattleControllerExecFlags)
        ++gBattlescriptCurrInstr;
}

static void atk0B_healthbarupdate(void)
{
    if (!gBattleControllerExecFlags)
    {
        if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);

            if (DoesSubstituteBlockMove(gBattlerAttacker, gActiveBattler, gCurrentMove) && gDisableStructs[gActiveBattler].substituteHP && !(gHitMarker & HITMARKER_IGNORE_SUBSTITUTE))
            {
                PrepareStringBattle(STRINGID_SUBSTITUTEDAMAGED, gActiveBattler);
            }
            else if (DoesDisguiseBlockMove(gBattlerAttacker, gActiveBattler, gCurrentMove)) //added change for easier filtering
            { //add or logic, for rockyhelmet and rock skin etc. here
                
            }
            else if (!DoesDisguiseBlockMove(gBattlerAttacker, gActiveBattler, gCurrentMove))
            {
                s16 healthValue;
                s32 currDmg = gBattleMoveDamage;
                s32 maxPossibleDmgValue = 10000; // not present in R/S, ensures that huge damage values don't change sign
                
                if (currDmg <= maxPossibleDmgValue)
                    healthValue = currDmg;
                else
                    healthValue = maxPossibleDmgValue;
                BtlController_EmitHealthBarUpdate(BUFFER_A, healthValue);
                MarkBattlerForControllerExec(gActiveBattler);
                if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER && gBattleMoveDamage > 0)
                    gBattleResults.playerMonWasDamaged = TRUE;
            }
        }
        gBattlescriptCurrInstr += 2;
    }
}

//also I wonder why these aren't unified commands
//they always go together I think? - yeah they do
//dropped for now but attempt consolidate effets later
static void atk0C_datahpupdate(void)
{
    //u32 moveType; //removed this as its a hold over from when moves didn't use split and instead relied on type order
    u16 move = gCurrentMove;

    if (!gBattleControllerExecFlags)
    {

        if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
            if (DoesSubstituteBlockMove(gBattlerAttacker, gActiveBattler, gCurrentMove) && gDisableStructs[gActiveBattler].substituteHP && !(gHitMarker & HITMARKER_IGNORE_SUBSTITUTE))
            {
                if (gDisableStructs[gActiveBattler].substituteHP >= gBattleMoveDamage)
                {
                    if (gSpecialStatuses[gActiveBattler].dmg == 0)
                        gSpecialStatuses[gActiveBattler].dmg = gBattleMoveDamage;
                    gDisableStructs[gActiveBattler].substituteHP -= gBattleMoveDamage;
                    gHpDealt = gBattleMoveDamage;
                }
                else
                {
                    if (gSpecialStatuses[gActiveBattler].dmg == 0)
                        gSpecialStatuses[gActiveBattler].dmg = gDisableStructs[gActiveBattler].substituteHP;
                    gHpDealt = gDisableStructs[gActiveBattler].substituteHP;
                    gDisableStructs[gActiveBattler].substituteHP = 0;
                }
                // check substitute fading
                if (gDisableStructs[gActiveBattler].substituteHP == 0)
                {
                    gBattlescriptCurrInstr += 2;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SubstituteFade;
                    return;
                }
            }//add or logic, for rockyhelmet and rock skin etc.
            else if (DoesDisguiseBlockMove(gBattlerAttacker, gActiveBattler, gCurrentMove) && !(gHitMarker & HITMARKER_IGNORE_SUBSTITUTE))
            {
                gBattleMons[gActiveBattler].species = SPECIES_MIMIKYU_BUSTED;//  need this line to show correct form
                //would prefer to pull from form_change_table rather than change species
                gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)] = TRUE; //should keep disguise from working again
                gBattleMoveDamage = 1;
                BattleScriptPush(gBattlescriptCurrInstr += 2); //use this instead of pushcursor, keeps from repeating curr script
                //BattleScriptPushCursor(); //ability line works, but doesn't transform into correct form //,keeps species change, above line does have effect
                gBattlescriptCurrInstr = BattleScript_TargetFormChange; //prevents ability reset on faint
                return;
            }
            else
            {
                gHitMarker &= ~(HITMARKER_IGNORE_SUBSTITUTE);
                if (gBattleMoveDamage < 0) // hp goes up
                {
                    gBattleMons[gActiveBattler].hp -= gBattleMoveDamage;
                    if (gBattleMons[gActiveBattler].hp > gBattleMons[gActiveBattler].maxHP)
                        gBattleMons[gActiveBattler].hp = gBattleMons[gActiveBattler].maxHP;

                }
                else // hp goes down
                {
                    if (gHitMarker & HITMARKER_SKIP_DMG_TRACK)
                    {
                        gHitMarker &= ~(HITMARKER_SKIP_DMG_TRACK);
                    }
                    else
                    {
                        gTakenDmg[gActiveBattler] += gBattleMoveDamage;
                        if (gBattlescriptCurrInstr[1] == BS_TARGET)
                            gTakenDmgByBattler[gActiveBattler] = gBattlerAttacker;
                        else
                            gTakenDmgByBattler[gActiveBattler] = gBattlerTarget;
                    }

                    if (gBattleMons[gActiveBattler].hp > gBattleMoveDamage)
                    {
                        gBattleMons[gActiveBattler].hp -= gBattleMoveDamage;
                        gHpDealt = gBattleMoveDamage;
                    }
                    else
                    {
                        gHpDealt = gBattleMons[gActiveBattler].hp;
                        gBattleMons[gActiveBattler].hp = 0;
                    }
                    if (!gSpecialStatuses[gActiveBattler].dmg && !(gHitMarker & HITMARKER_PASSIVE_DAMAGE))
                        gSpecialStatuses[gActiveBattler].dmg = gHpDealt;
                    if (IsPhysicalMove(gBattlerAttacker,gCurrentMove) //vsonic check, hopefully right
                        && !(gHitMarker & HITMARKER_PASSIVE_DAMAGE) && gCurrentMove != MOVE_PAIN_SPLIT)
                    {
                        gProtectStructs[gActiveBattler].physicalDmg = gHpDealt;
                        gSpecialStatuses[gActiveBattler].physicalDmg = gHpDealt;
                        if (gBattlescriptCurrInstr[1] == BS_TARGET)
                        {
                            gProtectStructs[gActiveBattler].physicalBattlerId = gBattlerAttacker;
                            gSpecialStatuses[gActiveBattler].physicalBattlerId = gBattlerAttacker;
                        }
                        else
                        {
                            gProtectStructs[gActiveBattler].physicalBattlerId = gBattlerTarget;
                            gSpecialStatuses[gActiveBattler].physicalBattlerId = gBattlerTarget;
                        }
                    }
                    else if (!IsPhysicalMove(gBattlerAttacker,gCurrentMove) && !(gHitMarker & HITMARKER_PASSIVE_DAMAGE)) //changed from special to not phsyical to account for status moves
                    {   //keep that's how it is in emerald
                        gProtectStructs[gActiveBattler].specialDmg = gHpDealt;
                        gSpecialStatuses[gActiveBattler].specialDmg = gHpDealt;
                        if (gBattlescriptCurrInstr[1] == BS_TARGET)
                        {
                            gProtectStructs[gActiveBattler].specialBattlerId = gBattlerAttacker;
                            gSpecialStatuses[gActiveBattler].specialBattlerId = gBattlerAttacker;
                        }
                        else
                        {
                            gProtectStructs[gActiveBattler].specialBattlerId = gBattlerTarget;
                            gSpecialStatuses[gActiveBattler].specialBattlerId = gBattlerTarget;
                        }
                    }
                }
                gHitMarker &= ~(HITMARKER_PASSIVE_DAMAGE);
                BtlController_EmitSetMonData(BUFFER_A, REQUEST_HP_BATTLE, 0, sizeof(gBattleMons[gActiveBattler].hp), &gBattleMons[gActiveBattler].hp);
                MarkBattlerForControllerExec(gActiveBattler);
            }//foud it vsonic request hp battle here is what's causing issue w transform hp update
            //actually this may not be it, think instead of mon data its just assigning a value based on data given
            //but hten I wonder why it happens at all rather than just  assigning the value
            //without this, hp still changes when takin damage, but no longer 
            //updates at battle end
        }
        else //need look into this think may be for status moves? / and with how I changed some status moves to read type this may be an issue
        {
            gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]); //no think for no efect stuff that miss etc.
            if (gSpecialStatuses[gActiveBattler].dmg == 0)
                gSpecialStatuses[gActiveBattler].dmg = 0xFFFF;
        }
        gBattlescriptCurrInstr += 2;
    }
}

static void atk0D_critmessage(void)
{
    if (!gBattleControllerExecFlags)
    {
        if (gCritMultiplier > 1 && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            PrepareStringBattle(STRINGID_CRITICALHIT, gBattlerAttacker);
            gBattleCommunication[MSG_DISPLAY] = 1;
        }
        ++gBattlescriptCurrInstr;
    }
}

static void atk0E_effectivenesssound(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = gBattlerTarget;
        if (!(gMoveResultFlags & MOVE_RESULT_MISSED))
        {
            switch (gMoveResultFlags & (u8)(~(MOVE_RESULT_MISSED)))
            {
            case MOVE_RESULT_SUPER_EFFECTIVE:
                BtlController_EmitPlaySE(0, SE_SUPER_EFFECTIVE);
                MarkBattlerForControllerExec(gActiveBattler);
                break;
            case MOVE_RESULT_NOT_VERY_EFFECTIVE:
                BtlController_EmitPlaySE(0, SE_NOT_EFFECTIVE);
                MarkBattlerForControllerExec(gActiveBattler);
                break;
            case MOVE_RESULT_DOESNT_AFFECT_FOE:
            case MOVE_RESULT_FAILED:
                // no sound
                break;
            case MOVE_RESULT_FOE_ENDURED:
            case MOVE_RESULT_ONE_HIT_KO:
            case MOVE_RESULT_FOE_HUNG_ON:
            default:
                if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)
                {
                    BtlController_EmitPlaySE(0, SE_SUPER_EFFECTIVE);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                else if (gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
                {
                    BtlController_EmitPlaySE(0, SE_NOT_EFFECTIVE);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                else if (!(gMoveResultFlags & (MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_FAILED)))
                {
                    BtlController_EmitPlaySE(0, SE_EFFECTIVE);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                break;
            }
        }
        ++gBattlescriptCurrInstr;
    }
}

static void atk0F_resultmessage(void) //covers the battle message displayed after attacks
{
    u32 stringId = 0;
    u8 moveType;
    GET_MOVE_TYPE(gCurrentMove,moveType);


    //vsonic //seems to work partially? prevent repeat messages, if kill in one hit with multihit, still shows for 2 hits - decided this is fine
    //forgot multihit resultmessage was somehting I added, believe just for sake of battle flow?
    //feels faster to get the effectinvess at start rather than waiting for last hit
    if (!gBattleControllerExecFlags) //need find a way to better mesh with multihit result message, to prevent replaying string if current/previous string is the same
    {
        if (gMoveResultFlags & MOVE_RESULT_MISSED && (!(gMoveResultFlags & MOVE_RESULT_DOESNT_AFFECT_FOE) || gBattleCommunication[6] > 2))
        {
            stringId = gMissStringIds[gBattleCommunication[6]];
            gBattleCommunication[MSG_DISPLAY] = 1;
        }
        else
        {

            gBattleCommunication[MSG_DISPLAY] = 1;
            switch (gMoveResultFlags & (u8)(~(MOVE_RESULT_MISSED)))
            {
            case MOVE_RESULT_SUPER_EFFECTIVE:
                if (!(gBattleMoves[gCurrentMove].power)) //try skip message  if status move, works - its f ppower 0, will use to exclude moves that should ignore type like counter
                    break;
                else if (VarGet(VAR_LAST_MULTIHIT_RESULT) == STRINGID_SUPEREFFECTIVE)
                    break;
                else
                    stringId = STRINGID_SUPEREFFECTIVE;
                break;
            case MOVE_RESULT_NOT_VERY_EFFECTIVE:
                if (CalcTypeEffectivenessMultiplier(gCurrentMove, moveType, gBattlerAttacker, gBattlerTarget, FALSE) == UQ_4_12_TO_INT((UQ_4_12(1.55) * UQ_4_12(0.5)) + UQ_4_12_ROUND))
                    gBattleCommunication[MSG_DISPLAY] = 0; //should keep effect remove message, keep not very effective sound
                else if (!(gBattleMoves[gCurrentMove].power)) //try skip message  if status move, seems to work
                    break;//think can use var to store multihit result message string id, (at end, if super or not effective)
                else if (VarGet(VAR_LAST_MULTIHIT_RESULT) == STRINGID_NOTVERYEFFECTIVE)
                    break;//looks odd but works, I made sure to clear it, point of this was to save on ewram consumptiion
                else //then here can compare value to be set and do else if  break if they match then just need to reset value of var in endurn continue battle & finish battle
                    stringId = STRINGID_NOTVERYEFFECTIVE;
                break;
            case MOVE_RESULT_ONE_HIT_KO:
                stringId = STRINGID_ONEHITKO;
                break;
            case MOVE_RESULT_FOE_ENDURED:
                stringId = STRINGID_PKMNENDUREDHIT;
                break;
            case MOVE_RESULT_FAILED:
                stringId = STRINGID_BUTITFAILED;
                break;
            case MOVE_RESULT_DOESNT_AFFECT_FOE:
                stringId = STRINGID_ITDOESNTAFFECT;
                break;
            case MOVE_RESULT_FOE_HUNG_ON:
                {
                    gMoveResultFlags &= ~(MOVE_RESULT_FOE_ENDURED | MOVE_RESULT_FOE_HUNG_ON);

                    if (gSpecialStatuses[gBattlerTarget].sturdied)
                    {
                        gSpecialStatuses[gBattlerTarget].sturdied = FALSE;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_SturdiedMsg;

                    }

                    else
                    {
                        gLastUsedItem = gBattleMons[gBattlerTarget].item;
                        gPotentialItemEffectBattler = gBattlerTarget;                    
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_HangedOnMsg;
                    }
                    return;
                }
            default:
                if (gMoveResultFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
                {
                    stringId = STRINGID_ITDOESNTAFFECT;
                }
                else if (gMoveResultFlags & MOVE_RESULT_ONE_HIT_KO)
                {
                    gMoveResultFlags &= ~(MOVE_RESULT_ONE_HIT_KO);
                    gMoveResultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE);
                    gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_OneHitKOMsg;
                    return;
                }
                else if (gMoveResultFlags & MOVE_RESULT_FOE_ENDURED)
                {
                    gMoveResultFlags &= ~(MOVE_RESULT_FOE_ENDURED | MOVE_RESULT_FOE_HUNG_ON);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_EnduredMsg;
                    return;
                }
                else if (gMoveResultFlags & MOVE_RESULT_FOE_HUNG_ON)
                {
                    gMoveResultFlags &= ~(MOVE_RESULT_FOE_ENDURED | MOVE_RESULT_FOE_HUNG_ON);

                    if (gSpecialStatuses[gBattlerTarget].sturdied)
                    {
                        gSpecialStatuses[gBattlerTarget].sturdied = FALSE;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_SturdiedMsg;

                    }

                    else
                    {
                        gLastUsedItem = gBattleMons[gBattlerTarget].item;
                        gPotentialItemEffectBattler = gBattlerTarget;                    
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_HangedOnMsg;
                    }
                    return;
                }
                else if (gMoveResultFlags & MOVE_RESULT_FAILED)
                {
                    stringId = STRINGID_BUTITFAILED;
                }
                else
                {
                    gBattleCommunication[MSG_DISPLAY] = 0;
                }
            }
        }
        
        if (stringId)
        {
            PrepareStringBattle(stringId, gBattlerAttacker);
        }
            
        ++gBattlescriptCurrInstr;
    }
}

static void atk10_printstring(void)
{
    CMD_ARGS(u16 stringid);
    if (gBattleControllerExecFlags == 0)
    {
        u16 stringid = cmd->stringid;

        gBattlescriptCurrInstr = cmd->nextInstr;
        PrepareStringBattle(stringid, gBattlerAttacker);
        gBattleCommunication[MSG_DISPLAY] = 1;
    }
}

static void atk11_printselectionstring(void)
{
    gActiveBattler = gBattlerAttacker;
    BtlController_EmitPrintSelectionString(0, T2_READ_16(gBattlescriptCurrInstr + 1));
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 3;
    gBattleCommunication[MSG_DISPLAY] = 1;
}

static void atk12_waitmessage(void)
{

    if (!gBattleControllerExecFlags)
    {
        if (!gBattleCommunication[MSG_DISPLAY])
        {
            gBattlescriptCurrInstr += 3;
        }
        else
        {
            u16 toWait = T2_READ_16(gBattlescriptCurrInstr + 1);
            u8 BattleSpeed = GetBattleSpeedOption();
            
            if (BattleSpeed > OPTIONS_BATTLE_SPEED_1X)
            {
                if (gSaveBlock2Ptr->optionsBattleSceneOff == TRUE)
                    BattleSpeed = OPTIONS_BATTLE_SPEED_2X;
                
                if (toWait == B_WAIT_TIME_UNIQUE || toWait == B_WAIT_TIME_LONG_LONG || toWait == B_WAIT_TIME_IMPORTANT_STRINGS) //this outta do it
                {
                    toWait = SetWaitTimeModifier(BattleSpeed, toWait);
                }
                else
                    toWait += SetWaitTimeModifier(BattleSpeed, toWait);
            } //at plus 4 gets kinda blinding to read messages so may drop these back some
            
            //if (GetPlayerTextSpeed() > OPTIONS_TEXT_SPEED_FAST && toWait < B_WAIT_TIME_BRIEFEST)
            //    toWait += 1;

            //only used for wait, not pause but just wrap into above function
            //nvm can't wrap in as this is a direct assignment
            //else if (GetPlayerTextSpeed() > OPTIONS_TEXT_SPEED_FAST && toWait == B_WAIT_TIME_UNIQUE)
            //    toWait = B_WAIT_TIME_SHORT;

            if (++gPauseCounterBattle >= gPauseValue[toWait])
            {
                gPauseCounterBattle = 0;
                gBattlescriptCurrInstr += 3;
                gBattleCommunication[MSG_DISPLAY] = 0;
            }
        }
    }
}

static void atk13_printfromtable(void)
{
    CMD_ARGS(const u16 *table);

    if (gBattleControllerExecFlags == 0)
    {
        const u16 *table = cmd->table;
        table += gBattleCommunication[MULTISTRING_CHOOSER];

        gBattlescriptCurrInstr = cmd->nextInstr;
        PrepareStringBattle(*table, gBattlerAttacker);
        gBattleCommunication[MSG_DISPLAY] = 1;
    }
}

static void atk14_printselectionstringfromtable(void)
{
    if (!gBattleControllerExecFlags)
    {
        const u16 *ptr = (const u16 *) T1_READ_PTR(gBattlescriptCurrInstr + 1);

        ptr += gBattleCommunication[MULTISTRING_CHOOSER];
        gActiveBattler = gBattlerAttacker;
        BtlController_EmitPrintSelectionString(0, *ptr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 5;
        gBattleCommunication[MSG_DISPLAY] = 1;
    }
}

u8 GetBattlerTurnOrderNum(u8 battlerId)
{
    s32 i;
    
    for (i = 0; i < gBattlersCount && gBattlerByTurnOrder[i] != battlerId; ++i);
    return i;
}

static void CheckSetUnburden(u8 battlerId)
{
    if (GetBattlerAbility(battlerId) == ABILITY_UNBURDEN)
    {
        gBattleResources->flags->flags[battlerId] |= RESOURCE_FLAG_UNBURDEN;
        RecordAbilityBattle(battlerId, ABILITY_UNBURDEN);
    }
}

void TryRestoreStolenItems(void)
{
    u32 i;
    u16 stolenItem = ITEM_NONE;
    u16 heldItem;

    for (i = 0; i < PARTY_SIZE; i++)
    {   
        heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
        if (gBattleStruct->itemStolen[i].stolen)
        {
            stolenItem = gBattleStruct->itemStolen[i].originalItem;
            if (stolenItem != ITEM_NONE && ItemId_GetPocket(stolenItem) != POCKET_BERRY_POUCH)  //seems like not fleshed out enough imo, if mon received an item before battle end
            {   //this wouldn't work correctly, so rather than just setting an item that would overwrite any item it received, it should do a check for items and add original
                //to bag if iteme isn't 0
                if (heldItem == ITEM_NONE)
                    SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &stolenItem);  // Restore stolen non-berry items
                else
                    AddBagItem(stolenItem, 1); //ok that oughta do it.  with this I should be able to le
            }
        }
    }
}

bool32 CanStealItem(u8 battlerStealing, u8 battlerItem, u16 item)
{
 // Check if the battler trying to steal should be able to


    if (!CanBattlerGetOrLoseItem(battlerItem, item)      // Battler with item cannot have it stolen
        || !CanBattlerGetOrLoseItem(battlerStealing, item)) // Stealer cannot take the item
        return FALSE;

    return TRUE;
}

void TrySaveExchangedItem(u8 battlerId, u16 stolenItem)
{
    // Because BtlController_EmitSetMonData does SetMonData, we need to save the stolen item only if it matches the battler's original
    // So, if the player steals an item during battle and has it stolen from it, it will not end the battle with it (naturally)

    // If mon's original item matches what is being stolen, save it to be restored at end of battle
    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER
        && stolenItem == gBattleStruct->itemStolen[gBattlerPartyIndexes[battlerId]].originalItem)
        gBattleStruct->itemStolen[gBattlerPartyIndexes[battlerId]].stolen = TRUE;

}

// battlerStealer steals the item of battlerItem
//make script for swapping item, chck fi one exists already
void StealTargetItem(u8 battlerStealer, u8 battlerItem)
{
    
    gLastUsedItem = gBattleMons[battlerItem].item;

    if (gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[battlerItem]][GetBattlerSide(battlerItem)] == ITEM_NONE)
        gBattleMons[battlerItem].item = ITEM_NONE;
    else
    {    
        gBattleMons[battlerItem].item = gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[battlerItem]][GetBattlerSide(battlerItem)];
        gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[battlerItem]][GetBattlerSide(battlerItem)] = ITEM_NONE;
    }//if mon stolen frmo has secondary item their held item is replaced w secondary item slot

    RecordItemEffectBattle(battlerItem, 0);    //just for ai

    if (gBattleMons[battlerItem].item == ITEM_NONE)
    {
        CheckSetUnburden(battlerItem);  //target is losing item so give unburden boost, if possible
        if (gBattleMons[battlerItem].ability != ABILITY_GORILLA_TACTICS)
            gBattleStruct->choicedMove[battlerItem] = MOVE_NONE;
    }
    gActiveBattler = battlerItem;
    BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gBattlerTarget].item), &gBattleMons[battlerItem].item);  // remove/set target item
    MarkBattlerForControllerExec(battlerItem);
    
    //Ability base item steal
    if ((GetBattlerAbility(battlerStealer) == ABILITY_PICKPOCKET
    || GetBattlerAbility(battlerStealer) == ABILITY_MAGICIAN)
    && gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[battlerStealer]][GetBattlerSide(battlerStealer)] == ITEM_NONE)
    {
        if (gBattleMons[battlerStealer].item == ITEM_NONE)
        {
            RecordItemEffectBattle(battlerStealer, ItemId_GetHoldEffect(gLastUsedItem));
            gBattleMons[battlerStealer].item = gLastUsedItem;

            gActiveBattler = battlerStealer;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gLastUsedItem), &gLastUsedItem); // set attacker item
            MarkBattlerForControllerExec(battlerStealer);//thinkk above is filling held item field using data from glastuseditem?

            /*gActiveBattler = battlerItem;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gBattlerTarget].item), &gBattleMons[battlerItem].item);  // remove target item
            MarkBattlerForControllerExec(battlerItem);
            */

            gBattleResources->flags->flags[battlerStealer] &= ~RESOURCE_FLAG_UNBURDEN; //this means lose unburden boost as you're gaining an item
            TrySaveExchangedItem(battlerItem, gLastUsedItem); //if player loses item it tries to save it

        }

        else //held item ability steal
        {
            //this is for ai I think, not sure if correct
            RecordItemEffectBattle(battlerStealer, ItemId_GetHoldEffect(gLastUsedItem));
            gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[battlerStealer]][GetBattlerSide(battlerStealer)] = gLastUsedItem;

            gActiveBattler = battlerStealer;
            /*BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gLastUsedItem), &gLastUsedItem); // set attacker item
            MarkBattlerForControllerExec(battlerStealer);*/

            /*gActiveBattler = battlerItem;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gBattlerTarget].item), &gBattleMons[battlerItem].item);  // remove target item
            MarkBattlerForControllerExec(battlerItem);
            */

            gBattleResources->flags->flags[battlerStealer] &= ~RESOURCE_FLAG_UNBURDEN; //this means lose unburden boost as you're gaining an item
            TrySaveExchangedItem(battlerItem, gLastUsedItem); //if player loses item it tries to save it

        }
    }
    else //normal item steal
    {

        if (gBattleMons[battlerStealer].item == ITEM_NONE)
        {
            RecordItemEffectBattle(battlerStealer, ItemId_GetHoldEffect(gLastUsedItem));
            gBattleMons[battlerStealer].item = gLastUsedItem;

            gActiveBattler = battlerStealer;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gLastUsedItem), &gLastUsedItem); // set attacker item
            MarkBattlerForControllerExec(battlerStealer);

            /*gActiveBattler = battlerItem;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gBattlerTarget].item), &gBattleMons[battlerItem].item);  // remove target item
            MarkBattlerForControllerExec(battlerItem);
            */

            gBattleResources->flags->flags[battlerStealer] &= ~RESOURCE_FLAG_UNBURDEN; //this means lose unburden boost as you're gaining an item
            TrySaveExchangedItem(battlerItem, gLastUsedItem); //if player loses item it tries to save it

        }

        else if (GET_BATTLER_SIDE(battlerStealer) == B_SIDE_PLAYER) //if side player because don't think bag logic would work for opponent don't want to break something
        {
            AddBagItem(gLastUsedItem, 1); //allows steal item if holding item
        }//ok think that outta do it
    }
    
    
}

//loseitembattler
//considering changing to use in place of current 
//magma armor sticky hold lose item logic

/*This Ability prevents the held item of the Pokémon with this Ability
from being taken by Covet, Thief, Pickpocket, or Magician;
eaten by Bug Bite or Pluck; destroyed by Incinerate or Corrosive Gas;
or removed by Knock Off. It also prevents the Pokémon from being affected
by other Pokémon's Trick or Switcheroo (even if it has no held item), but not its own.

Sticky Hold does not prevent a Sticky Barb being transferred by its own effect.*/
//move effet added so will use this for all effects, bug bite incinerate etc.
//if used for those put move effect in other wise put 0 for move effect
//looks to work now using to replace knock off bug bite incinerate i.e knock off likes
//hmm well bug bite should be stealing so not use this?
//yeah bug bite doesnt work w this, idk why bug bite doesn't work with this??
//it DOES with stealitem but I would have to do more with that
bool32 TryKnockOffBattleScript(u32 loseitembattler, u32 EffectUser, u16 moveEffect)
{
    if (gBattleMons[loseitembattler].item != ITEM_NONE
        && CanBattlerGetOrLoseItem(loseitembattler, gBattleMons[loseitembattler].item)
        && !NoAliveMonsForEitherParty())
    {
        if (GetBattlerAbility(loseitembattler) == ABILITY_STICKY_HOLD && IsBattlerAlive(loseitembattler))
        {
            gBattlerAbility = loseitembattler;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_StickyHoldActivates;
            RecordAbilityBattle(loseitembattler, ABILITY_STICKY_HOLD);
        }   //block knock off/item theft
        else
        {
            u32 side = GetBattlerSide(loseitembattler);

            gLastUsedItem = gBattleMons[loseitembattler].item;

            if (gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[loseitembattler]][GetBattlerSide(loseitembattler)] == ITEM_NONE)
                gBattleMons[loseitembattler].item = ITEM_NONE;
            else
            {    
                gBattleMons[loseitembattler].item = gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[loseitembattler]][GetBattlerSide(loseitembattler)];
                gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[loseitembattler]][GetBattlerSide(loseitembattler)] = ITEM_NONE;
            }
            if (gBattleMons[loseitembattler].ability != ABILITY_GORILLA_TACTICS)
                gBattleStruct->choicedMove[loseitembattler] = MOVE_NONE;
            
            // In Gen 5+, Knock Off removes the target's item rather than rendering it unusable.
            //if (B_KNOCK_OFF_REMOVAL >= GEN_5)
            //if (gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[loseitembattler]][GetBattlerSide(loseitembattler)] == ITEM_NONE)
            
                gActiveBattler = loseitembattler;
                BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[loseitembattler].item), &gBattleMons[loseitembattler].item);
                MarkBattlerForControllerExec(loseitembattler);
            
            /*else
            {

                //gWishFutureKnock.knockedOffMons[side] |= 1u << gBattlerPartyIndexes[loseitembattler];
            }//if want return item after battle
            */

            //gWishFutureKnock.knockedOffMons[side] |= gBitTable[gBattlerPartyIndexes[loseitembattler]];
            
            if (gBattleMons[loseitembattler].item == ITEM_NONE)
                CheckSetUnburden(loseitembattler);

            BattleScriptPushCursor();

            if (moveEffect == MOVE_EFFECT_INCINERATE)
                gBattlescriptCurrInstr = BattleScript_MoveEffectIncinerate;
            else if (moveEffect == MOVE_EFFECT_BUG_BITE)
                gBattlescriptCurrInstr = BattleScript_MoveEffectBugBite;
            else if (GetBattlerAbility(EffectUser) == ABILITY_STICKY_HOLD)
            {   
                gBattlescriptCurrInstr = BattleScript_StickyHoldKnockoff;
                RecordAbilityBattle(EffectUser, ABILITY_STICKY_HOLD);
            }
            else if (GetBattlerAbility(EffectUser) == ABILITY_MAGMA_ARMOR)
            { 
                gBattlescriptCurrInstr = BattleScript_MoveEffectIncinerate;
                RecordAbilityBattle(EffectUser, ABILITY_MAGMA_ARMOR);
            }
            else
                gBattlescriptCurrInstr = BattleScript_KnockedOff;
            //*(u8 *)((u8 *)(&gBattleStruct->choicedMove[loseitembattler]) + 0) = 0;
            //*(u8 *)((u8 *)(&gBattleStruct->choicedMove[loseitembattler]) + 1) = 0;   //for now put this to keep standard firered setup
        }
        return TRUE;
    }
    return FALSE;
}

static const u16 sFinalStrikeOnlyEffects[] =
{
    EFFECT_RELIC_SONG,
    EFFECT_BUG_BITE,
    EFFECT_THIEF,
    EFFECT_LOSETYPE_HIT,
    EFFECT_SECRET_POWER,
    EFFECT_SMACK_DOWN,
    EFFECT_SPARKLING_ARIA,
    EFFECT_SMELLINGSALT,
    EFFECT_WAKE_UP_SLAP,
    EFFECT_HIT_ESCAPE,
    EFFECT_RECOIL,
    EFFECT_HIT_PREVENT_ESCAPE,
    EFFECT_HIT_SWITCH_TARGET,
};

bool8 IsMoveAffectedByParentalBond(u16 move, u8 battlerId)
{
    if (gBattleMoves[move].split != SPLIT_STATUS
        && !(sForbiddenMoves[move] & FORBIDDEN_PARENTAL_BOND))
    {
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        {
            switch (GetBattlerMoveTargetType(battlerId, move))
            {
                // Both foes are alive, spread move strikes once
            case MOVE_TARGET_BOTH:
                if (CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) >= 2)
                    return FALSE;
                break;
                // Either both foes or one foe and its ally are alive; spread move strikes once
            case MOVE_TARGET_FOES_AND_ALLY:
                if (CountAliveMonsInBattle(BATTLE_ALIVE_EXCEPT_ATTACKER) >= 2)
                    return FALSE;
                break;
            default:
                break;
            }
        }
        return TRUE;
    }
    return FALSE;
}

static bool8 IsFinalStrikeEffect(u16 move)
{
    u32 i;
    u16 moveEffect = gBattleMoves[move].effect;

    for (i = 0; i < ARRAY_COUNT(sFinalStrikeOnlyEffects); i++)
    {
        if (moveEffect == sFinalStrikeOnlyEffects[i])
            return TRUE;
    }
    return FALSE;
}

#define INCREMENT_RESET_RETURN                  \
{                                               \
    ++gBattlescriptCurrInstr;                   \
    gBattleScripting.moveEffect = 0;            \
    return;                                     \
} 

// cant put comments after lines on side, 
//compiler doesn't like it
//believe don't need them increment reset return is same as
//++gBattlescriptCurrInstr;
//return;

#define RESET_RETURN                            \
{                                               \
    gBattleScripting.moveEffect = 0;            \
    return;                                     \
}

#define MOVE_EEFFCTS 
// when ready will redefine what prevents applying status here, don't forget setyawn  after that grfx for status animation next
//function update complete, remaining is multi status update, will do later
//think  this is the issue, somthing causing wrap effect, so assumings move effects are being triggered oddly
//sets status based on moves, in bs called from setmoveeffectwithchance
//but some things can bypass this function to set status directly
//usually ability logic or item logic
void SetMoveEffect(bool32 primary, u32 certain) 
{

    u32 flags = 0;
    u16 battlerAbility, AttackerAbility;
    bool32 statusChanged = FALSE;
    s32 affectsUser, byTwo, i = 0; // 0x40 otherwise
    bool32 mirrorArmorReflected = ((GetBattlerAbility(gBattlerTarget) == ABILITY_MIRROR_ARMOR) || (GetBattlerAbility(gBattlerTarget) == ABILITY_EMPATH));
    bool8 activateAfterFaint = FALSE;

    switch (gBattleScripting.moveEffect) // Set move effects which happen later on
    {//ported but don't know why need, knock off works without moveeffect2 by default? -its a change for modern item effects, to make sure effects trigger after item effect
    case MOVE_EFFECT_KNOCK_OFF:
    //case MOVE_EFFECT_SMACK_DOWN:
    case MOVE_EFFECT_REMOVE_STATUS:
        gBattleStruct->moveEffect2 = gBattleScripting.moveEffect;
        ++gBattlescriptCurrInstr;
        return;
    case MOVE_EFFECT_STEALTH_ROCK:  //test
    //case MOVE_EFFECT_SPIKES:
    case MOVE_EFFECT_PAYDAY:
    case MOVE_EFFECT_STEAL_ITEM:
    case MOVE_EFFECT_BUG_BITE:
        activateAfterFaint = TRUE;
        break;
    } 

    if (gBattleScripting.moveEffect & MOVE_EFFECT_AFFECTS_USER)  //because of bit logic  and value of affects user, this means if given move effect does not return 0, make affect user return true, meant to always return non 0 value
    {
        gEffectBattler = gBattlerAttacker; // battlerId that effects get applied on
        gBattleScripting.moveEffect &= ~(MOVE_EFFECT_AFFECTS_USER); //looked into contact move multihit bug I think this is the cause, it swaps targetting around
        affectsUser = MOVE_EFFECT_AFFECTS_USER; //and remove affects user when move effect/ability would be triggered but can reactivate before moveend/turnend
        gBattleScripting.battler = gBattlerTarget; // theoretically the attacker
    }//so success condition is,  2 bytes? so can fit higher values/more move effects, and can filter/set affect user and effect certain to true non zero values
    else
    {
        gEffectBattler = gBattlerTarget;
        gBattleScripting.battler = gBattlerAttacker;
    }
    if (gBattleTypeFlags & BATTLE_TYPE_POKEDUDE
     && gBattleScripting.moveEffect != 1
     && GetBattlerSide(gEffectBattler) == B_SIDE_OPPONENT)
    {
        ++gBattlescriptCurrInstr;
        return;
    }
    battlerAbility = GetBattlerAbility(gEffectBattler); //port      is for target ability
    AttackerAbility = GetBattlerAbility(gBattlerAttacker);   //for attacker ability

    // Just in case this flag is still set
    gBattleScripting.moveEffect &= ~MOVE_EFFECT_CERTAIN;

    if (battlerAbility == ABILITY_SHIELD_DUST 
     && !primary
     && (gBattleScripting.moveEffect <= MOVE_EFFECT_TRI_ATTACK || gBattleScripting.moveEffect >= MOVE_EFFECT_FLAME_BURST)) // Exclude stat lowering effects)  //skip script command if in threshold
    {
        if (battlerAbility == ABILITY_SHIELD_DUST)
            RecordAbilityBattle(gEffectBattler, battlerAbility);
        ++gBattlescriptCurrInstr;
        return; //like emerald so is correct
    }
    if (gSideStatuses[GET_BATTLER_SIDE(gEffectBattler)] & SIDE_STATUS_SAFEGUARD //safegaurd check is here already dont need safeguard in status functions
     //&& !(gHitMarker & HITMARKER_IGNORE_SAFEGUARD) //removing this not part of status check functions from emerald is becuase this was removed in later gen
     && !primary            //more consistent and easier to setup function logic if I just remove it.
     && gBattleScripting.moveEffect <= MOVE_EFFECT_CONFUSION)   //skip script command if in threshold
    {
        ++gBattlescriptCurrInstr;
        return;
    }

    if (TestSheerForceFlag(gBattlerAttacker, gCurrentMove) && affectsUser != MOVE_EFFECT_AFFECTS_USER)
        INCREMENT_RESET_RETURN

    if (gBattleMons[gEffectBattler].hp == 0 && !activateAfterFaint)
        INCREMENT_RESET_RETURN

    if (DoesSubstituteBlockMove(gBattlerAttacker, gEffectBattler, gCurrentMove) && affectsUser != MOVE_EFFECT_AFFECTS_USER)
        INCREMENT_RESET_RETURN

    if (gBattleScripting.moveEffect <= PRIMARY_STATUS_MOVE_EFFECT) // status change
    {
        switch (sStatusFlagsForMoveEffects[gBattleScripting.moveEffect])  //find out what this exactly is
        {//for switch to work, parenthesis value in "switch" most be a single value,  value in case must also be a single value
        case STATUS1_SLEEP:  //best switch case example
            // check active uproar
            if (battlerAbility != ABILITY_SOUNDPROOF)
                for (gActiveBattler = 0;
                    gActiveBattler < gBattlersCount && !(gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR);
                    ++gActiveBattler);
            else
                gActiveBattler = gBattlersCount; //why is vital spirit etc. not here? check later  has jumpifcantmakeasleep that checks these abilities so think this is fine

            if (!(CanSleep(gEffectBattler)))
                break;
            
            if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS)
            && gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST)    
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }
            
            if (gActiveBattler != gBattlersCount)
                break;
            CancelMultiTurnMoves(gEffectBattler); //if it passes all checks cancel multi turn moves and appply sleep. I think
            statusChanged = TRUE;
            break;//NEED to better check swithch statements to see if break ends entire switch, or it just makes it continue checking for matches in other cases
        case STATUS1_POISON: //checked break ends entire switch function, but they have fallthrough, w/o breaks it would continue to next case
            if ((battlerAbility == ABILITY_IMMUNITY || battlerAbility == ABILITY_PASTEL_VEIL || battlerAbility == ABILITY_COMATOSE)// so when multi status is set will need to remove breaks
             && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN))//and reorganize statements so it follows alternate paths rather than just going down
            {   //so make it if   and else using multiple or operands to group up the thinigs that break status and status changd will equal false
                // then an else that will do the normal things that go along with status being applied. and then keeps going without a break
                gLastUsedAbility = battlerAbility;
                RecordAbilityBattle(gEffectBattler, gLastUsedAbility);
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_PSNPrevention;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                return;
            }
            
            /*if (!(CanPoisonType(gBattleScripting.battler, gEffectBattler) //corrossion logic here
                && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN)))
            {
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_PSNPrevention;
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                return;
            }*/  //need properly review this for later

            //put no effect check here, below ability checks above status1 check
            //needs else if here only to make sure it takes into account corrosion check from above
            //vsonic will need change move type checks to use getmovetype or check settypebeforeusingmove function to get actual move type
            else if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS)
            && (AttackerAbility != ABILITY_CORROSION 
            && AttackerAbility != ABILITY_POISONED_LEGACY)
            && gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST)    
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }//think add poisoned legacy to this - done below
            

            /*if (IS_BATTLER_OF_TYPE(gEffectBattler, TYPE_POISON))
                break;
            if (IS_BATTLER_OF_TYPE(gEffectBattler, TYPE_STEEL))
                break;  */

            if (!(CanBePoisoned(gBattleScripting.battler, gEffectBattler)))
                break;

            /*if (gBattleMons[gEffectBattler].status1)
                break;*/    //removed this line, has check in battlescript, think will just not do text string, there's no way to do it simply?
            //instead can just do jump in commands to set move effect toxic,  just need to remove poison with this function
            //think this shouldn't go here, status is set below this so it would set twice?
             //OK THIS hopefully works.?   //should remove poison and set toxic, the missing part is setting toxic counter value
            //dont know if works as I want but it compiles
            
           /* else if (gBattleMons[gEffectBattler].status1)   //realized i could keep this, if i use else if,  since thsi should mean if status1 not 0?
                break;*/ //removed put comparative logic in ported function
            statusChanged = TRUE;
            break;
            
            /*if (CanBePoisoned(gBattleScripting.battler, gEffectBattler))
            {
                   
                statusChanged = TRUE;
                break;
            }
            else if (!(CanPoisonType(gBattleScripting.battler, gEffectBattler)))
            {
                gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
            }
            break;*/
            
        /*case STATUS1_SPIRIT_LOCK: //can set theese 2 up when reorddr status constants
            if ((battlerAbility == ABILITY_COMATOSE)// so when multi status is set will need to remove breaks
             && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN))
            { 
                gLastUsedAbility = battlerAbility;
                RecordAbilityBattle(gEffectBattler, gLastUsedAbility);
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_PSNPrevention; //make uniuque sctript for spirit loke  block
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                return;
            }

            if (IS_BATTLER_OF_TYPE(gEffectBattler, TYPE_FAIRY))
                break;

            //put no effect check here, below ability checks above status1 check
            if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS)
            && gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST)    
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }

            if (gBattleMons[gEffectBattler].status1)
                break;
            statusChanged = TRUE;
            break;
        */
        case STATUS1_BURN:
            if ((battlerAbility == ABILITY_WATER_VEIL
                || battlerAbility == ABILITY_WATER_BUBBLE
                || battlerAbility == ABILITY_COMATOSE)
             && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN))
            {
                gLastUsedAbility = battlerAbility;
                RecordAbilityBattle(gEffectBattler, battlerAbility);
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_BRNPrevention;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                return;
            }
    
            if (IS_BATTLER_OF_TYPE(gEffectBattler, TYPE_FIRE)
             && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN))
            {
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_BRNPrevention;
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                return;
            }
            if (!(CanBeBurned(gEffectBattler)))
                break;

            //put no effect check here, below ability checks above status1 check
            //pretty sure this is deprecated code from idea to make status go through type checks,
            //think rn status never sets result no effect,
            //planned use for hard mode tho? so could remove
            //normal/ghost exception for later
            if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS)
            && gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST)    
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }

            statusChanged = TRUE;
            break;
        case STATUS1_FREEZE:
            if (!(CanBeFrozen(gEffectBattler)))
                break;

            //put no effect check here, below ability checks above status1 check
            if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS)
            && gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST)   
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }

            CancelMultiTurnMoves(gEffectBattler);
            statusChanged = TRUE;
            //moved freeze timer below w sleep //2-4 turns for frozn should work  - nvm using value of 3, can have 2 full turns of freeze, decrement in end turn
            break;  //new note, made change to freeze, but don't want move to just be a switch as I'll lose the end turn, think I will adapt frostbite
            //from arceus my plan, when freeze timer  reaches zero, apply frostbite, which will continue end turn damage but allow enemy to attack.
            //freeze status cure effects would remove frostbite, after freeze, as well as if applied during freez.
            //so frostbite would take efffect when frozen turn counter reaches zero and last item effect/battle effect wasn't freeze cure  vsonic IMPORTANT
        case STATUS1_PARALYSIS:
        {
            u8 movetype;
            GET_MOVE_TYPE(gCurrentMove,movetype) //unsure if this will be tracking the corret battler ie effect battler

            if (battlerAbility == ABILITY_LIMBER || battlerAbility == ABILITY_COMATOSE)
            {
                if (primary == TRUE || certain == MOVE_EFFECT_CERTAIN)
                {
                    gLastUsedAbility = battlerAbility;
                    RecordAbilityBattle(gEffectBattler, gLastUsedAbility);
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_PRLZPrevention;
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0; //ability status prevention
                    return;
                }
                else
                    break;
            }
           
           if (!(CanBeParalyzed(gEffectBattler)))
                break;

            

            //put no effect check here, below ability checks above status1 check
            if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS)
            && gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST)    
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }

            statusChanged = TRUE;
            break;
        }
        case STATUS1_TOXIC_POISON:
        
            if ((battlerAbility == ABILITY_IMMUNITY || battlerAbility == ABILITY_PASTEL_VEIL || battlerAbility == ABILITY_COMATOSE) 
            && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN))
            {
                gLastUsedAbility = battlerAbility;
                RecordAbilityBattle(gEffectBattler, gLastUsedAbility);
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_PSNPrevention;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                return;
            }
            
            /*if (!(CanPoisonType(gBattleScripting.battler, gEffectBattler))
             && (primary == TRUE || certain == MOVE_EFFECT_CERTAIN))
            {
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_PSNPrevention;
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;  //this tells it which string to choose within the gPSNPreventionStringIds array
                return;
            }*/  //paralysis works and this si removed, removing for now, but think need multistring choice 2 for status blocking abilities

            if (!CanBePoisoned(gBattleScripting.battler, gEffectBattler))
                break;
            //put no effect check here, below ability checks above status1 check
            //I guess put this here? its passed most checks
            else if ((gMoveResultFlags & MOVE_RESULT_NO_EFFECT && gBattleMoves[gCurrentMove].split == SPLIT_STATUS && AttackerAbility != ABILITY_CORROSION && AttackerAbility != ABILITY_POISONED_LEGACY)
            && (gBattleMoves[gCurrentMove].type != TYPE_NORMAL
            && gBattleMoves[gCurrentMove].type != TYPE_GHOST))   //extra protection to make sure doesn't overwrite ability logic
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; //do jump
                break;
            }
            /*if (gBattleMons[gEffectBattler].status1)    //for poison worsend need change this to status1 != poison break, will let it set toxic if normal poison
                break;*/
            //attempting to just remove, as status checks etc. are already part of battlescript
            //need to better understand what setmoveeffect is doing

            if (CanBePoisoned(gBattleScripting.battler, gEffectBattler))
            {
                   
                statusChanged = TRUE;
                break;
            }
            else if (!CanPoisonType(gBattleScripting.battler, gEffectBattler))
            {
                gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
            }
            break;
        }        
        if (statusChanged == TRUE)
        {
            BattleScriptPush(gBattlescriptCurrInstr + 1);//hmm or what I could do is keep full sleep turns but counter by letting heal, so you get free dmg but you may need to expend more to kill
                //yeah I like that a lot better, ok set it up like traunt, but end turn, that way you still get 2 chances to catch a wild mon before it starts to heal
            //makes rest better, which is fine but should be no issues, just test and tweak heal value
            if (sStatusFlagsForMoveEffects[gBattleScripting.moveEffect] == STATUS1_SLEEP)//>>>actually way this is counted it decrements before effect takes palce (i.e in atk canceler not end turn)
            {
                if (gSpecialStatuses[gBattlerAttacker].Cacophonyboosted)
                    gBattleStruct->SleepTimer[gBattlerPartyIndexes[gEffectBattler]][GetBattlerSide(gEffectBattler)] = 5;
                else
                    gBattleStruct->SleepTimer[gBattlerPartyIndexes[gEffectBattler]][GetBattlerSide(gEffectBattler)] = ((Random() % 3) + 3);
                gBattleMons[gEffectBattler].status1 |= sStatusFlagsForMoveEffects[gBattleScripting.moveEffect];
                //gBattleMons[gEffectBattler].status1 |= ((Random() % 3) + 3); //duration of sleep, and its 2-5 here. /changed to 2-4 /guarantees 1 free turn unless earlybird  //confirmed
                gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                
                if (gBattleMons[gEffectBattler].status2 & STATUS2_RAGE) //would be any time miss, with ANY attack, so don't really want that            
                {
                    ClearRageStatuses(gEffectBattler);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RageEnds; //need test doesn't work, no message
                } //just realized I'm not activating this logic since I'm using yawn, that bypasses this function
            }
            else if (sStatusFlagsForMoveEffects[gBattleScripting.moveEffect] == STATUS1_FREEZE)
            {
                gDisableStructs[gEffectBattler].FrozenTurns = 3;    //means 2 turns of freeze
                gBattleMons[gEffectBattler].status1 |= sStatusFlagsForMoveEffects[gBattleScripting.moveEffect];
                gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];

                if (gBattleMons[gEffectBattler].status2 & STATUS2_RAGE) //would be any time miss, with ANY attack, so don't really want that            
                {
                    ClearRageStatuses(gEffectBattler);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RageEnds; //need test
                }
            } //moved here for clarity
            else if (sStatusFlagsForMoveEffects[gBattleScripting.moveEffect] == STATUS1_POISON)
            {
                if (gBattleMons[gEffectBattler].status1 & STATUS1_POISON)//now i understand the note,
                {   //the two lins are removing the status even though, the prior logic ensured that no status was set, ironically necessary for my changes
                    // It's redundant, because at this point we know the status1 value is 0.
                    gBattleMons[gEffectBattler].status1 &= ~(STATUS1_TOXIC_POISON); //^not my notes
                    gBattleMons[gEffectBattler].status1 &= ~(STATUS1_POISON);
                    gBattleMons[gEffectBattler].status1 |= STATUS1_TOXIC_POISON;
                    gBattleStruct->ToxicTurnCounter[gBattlerPartyIndexes[gEffectBattler]][GetBattlerSide(gEffectBattler)] = 2;
                    //attempting set toxic counter, to start above normal poison base dmg //will o 3/16
                    gBattlescriptCurrInstr = BattleScript_PoisonWorsened;
                }
                else if (GetBattlerAbility(gBattlerAttacker) == ABILITY_POISONED_LEGACY
                && (gBattleMons[gBattlerAttacker].hp <= (gBattleMons[gBattlerAttacker].maxHP / 2)))
                {
                    gBattleMons[gEffectBattler].status1 &= ~(STATUS1_TOXIC_POISON);
                    gBattleMons[gEffectBattler].status1 &= ~(STATUS1_POISON); //extra protection
                    gBattleMons[gEffectBattler].status1 |= STATUS1_TOXIC_POISON;
                    gBattleStruct->ToxicTurnCounter[gBattlerPartyIndexes[gEffectBattler]][GetBattlerSide(gEffectBattler)] = 2;
                    gBattlescriptCurrInstr = BattleScript_MoveEffectToxic; //setup its own message ability severely poisoned I think
                    
                }
                else //normal poison setting
                {
                    gBattleMons[gEffectBattler].status1 |= sStatusFlagsForMoveEffects[gBattleScripting.moveEffect];
                    gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                }
                
            }
            else if (sStatusFlagsForMoveEffects[gBattleScripting.moveEffect] == STATUS1_TOXIC_POISON)
            {
                if (GetBattlerAbility(gBattlerAttacker) == ABILITY_POISONED_LEGACY
                && (gBattleMons[gBattlerAttacker].hp <= (gBattleMons[gBattlerAttacker].maxHP / 2)))
                {
                    gBattleMons[gEffectBattler].status1 &= ~(STATUS1_TOXIC_POISON);
                    gBattleMons[gEffectBattler].status1 &= ~(STATUS1_POISON); //extra protection
                    //gBattleMons[gEffectBattler].status1 |= sStatusFlagsForMoveEffects[gBattleScripting.moveEffect];
                    gBattleStruct->ToxicTurnCounter[gBattlerPartyIndexes[gEffectBattler]][GetBattlerSide(gEffectBattler)] = 2; //works now, awesome
                    //gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                } //ok issue was setting wrong thing, toxic turn is a counter, but gDisableStructs[gActiveBattler].toxicTurn is the actual dmg part
                //else //normal toxic setting
                //{
                    gBattleMons[gEffectBattler].status1 |= sStatusFlagsForMoveEffects[gBattleScripting.moveEffect];
                    gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                //}
            }            
            else //normal status setting
            {
                gBattleMons[gEffectBattler].status1 |= sStatusFlagsForMoveEffects[gBattleScripting.moveEffect];
                gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
            }
            gActiveBattler = gEffectBattler;
            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gEffectBattler].status1);  //not really sure what this is doing but leave it
            MarkBattlerForControllerExec(gActiveBattler);
           gBattleCommunication[MULTISTRING_CHOOSER] = 0; //add infestation and spirit lock when done to below
            // for synchronize / empath / empathic curse
            if (gBattleScripting.moveEffect == MOVE_EFFECT_POISON
             || gBattleScripting.moveEffect == MOVE_EFFECT_TOXIC
             || gBattleScripting.moveEffect == MOVE_EFFECT_PARALYSIS
             //|| (gBattleScripting.moveEffect == MOVE_EFFECT_FREEZE && gDisableStructs[gEffectBattler].FrozenTurns == 0)
             //|| gBattleScripting.moveEffect == MOVE_EFFECT_ATTRACT // doestn' yet exist, I'm trying to add
             || gBattleScripting.moveEffect == MOVE_EFFECT_BURN) //figure out how infatuation works 
             {
                u8 *synchronizeEffect = &gBattleStruct->synchronizeMoveEffect;
                *synchronizeEffect = gBattleScripting.moveEffect; 
                gHitMarker |= HITMARKER_SYNCHRONIZE_EFFECT;
             }//Think adding stat drop copy shoud be simple as  copying and putting in the right place, right here is just for status1
            //nvm realized this really is a mirror armor copy so just use that logic
        }
        else if (statusChanged == FALSE)
        {
            ++gBattlescriptCurrInstr;
        }
        return;
    }   //end case move effects less than 6 i.e toxic and below, ok this is potentially what it means by primary, its all status1 stuff
    else
    {       //think this means if status set is the same as the one being attempted to be set, skip to next battle string. i.e can't confuse if already confused?
        //for fear of overlap may remove this line, and remove status2 from sStatusFlagsForMoveEffects[gBattleScripting.moveEffect]) 
        //instead just put explicit status check within the case
        /*if (gBattleMons[gEffectBattler].status2 & sStatusFlagsForMoveEffects[gBattleScripting.moveEffect]) //not gonna be a problem for trap status as using dif status for each
        {                                           //and just put in each case, lan like magic gaurd check, check macro and do increment, with a one line paste
            ++gBattlescriptCurrInstr;
        }
        else*/
        {
            u8 side;
            u32 TrapDuration;
            u32 i;

            //best do cacophony effect change here
            //do based on move
            //howl parting shot etc. can stay as they are
            //as they are spcific move based, I just need to change the general ones
            if (ShouldCacophonyElevateMoveEffect(gCurrentMove))
                CacophonyElevateMoveEffect();

            switch (gBattleScripting.moveEffect)
            {
            case MOVE_EFFECT_CONFUSION:
                if (!CanBeConfused(gEffectBattler))
                {
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    if (gSpecialStatuses[gBattlerAttacker].Cacophonyboosted)
                        gDisableStructs[gEffectBattler].ConfusionTurns = 5;
                    else
                        gDisableStructs[gEffectBattler].ConfusionTurns = ((Random() % 4) + 2); //think this odds for confusion duration again 2-5
                    // If the confusion is activating due to being released from Sky Drop, go to "confused due to fatigue" script.
                    // Otherwise, do normal confusion script.
                    //ok confusion turn etc. set the base status as well, so without it I need to manually set status
                    gBattleMons[gEffectBattler].status2 |= STATUS2_CONFUSION;
                        if (gCurrentMove == MOVE_SKY_DROP)
                        {
                            gBattleMons[gEffectBattler].status2 &= ~(STATUS2_LOCK_CONFUSE);
                            gBattlerAttacker = gEffectBattler;
                            gBattlescriptCurrInstr = BattleScript_ThrashConfuses;
                        }
                        else
                        {
                            BattleScriptPush(gBattlescriptCurrInstr + 1);
                            gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                        }
                }
                break;
            case MOVE_EFFECT_INFESTATION:
            {
                if (gBattleMons[gEffectBattler].status4 & STATUS4_INFESTATION) //not gonna be a problem for trap status as using dif status for each
                {                                           //and just put in each case, lan like magic gaurd check, check macro and do increment, with a one line paste
                    ++gBattlescriptCurrInstr;
                }
                else
                {

                gBattleMons[gEffectBattler].status4 |= STATUS4_INFESTATION;
                
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                }
            }
            break;
            case MOVE_EFFECT_FLINCH:
                if (battlerAbility == ABILITY_INNER_FOCUS || battlerAbility == ABILITY_FEMME_FATALE)
                {
                    if (primary == TRUE || certain == MOVE_EFFECT_CERTAIN)
                    {
                        gLastUsedAbility = battlerAbility;
                        gBattlerAbility = gEffectBattler;
                        RecordAbilityBattle(gEffectBattler, battlerAbility);
                        gBattlescriptCurrInstr = BattleScript_FlinchPrevention;
                    }
                    else
                    {
                        ++gBattlescriptCurrInstr;
                    }
                }
                else
                {
                    if (gBattleMons[gEffectBattler].status2 & STATUS2_FLINCHED)
                    {                                           //and just put in each case, lan like magic gaurd check, check macro and do increment, with a one line paste
                        ++gBattlescriptCurrInstr;
                    }
                    else
                    {

                        if (GetBattlerTurnOrderNum(gEffectBattler) > gCurrentTurnActionNumber)
                            gBattleMons[gEffectBattler].status2 |= STATUS2_FLINCHED;
                        ++gBattlescriptCurrInstr;
                    }
                }
                break;
            case MOVE_EFFECT_UPROAR:
                if (!(gBattleMons[gEffectBattler].status2 & STATUS2_UPROAR))
                {
                    gBattleMons[gEffectBattler].status2 |= STATUS2_MULTIPLETURNS;
                    gBattleMons[gEffectBattler].status2 |= STATUS2_UPROAR;
                    gLockedMoves[gEffectBattler] = gCurrentMove;
                    //gBattleMons[gEffectBattler].status2 |= ((Random() & 3) + 2) << 4;   //believe means 2-5
                    gDisableStructs[gEffectBattler].uproarTurns = 3;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                }
                else
                {
                    ++gBattlescriptCurrInstr;
                }
                break;
            case MOVE_EFFECT_PAYDAY:
                // Don't scatter coins on the second hit of Parental Bond
                if (GET_BATTLER_SIDE(gBattlerAttacker) == B_SIDE_PLAYER && gSpecialStatuses[gBattlerAttacker].parentalBondState != PARENTAL_BOND_2ND_HIT)
                {
                    u16 PayDay = gPaydayMoney;
                    gPaydayMoney += (gBattleMons[gBattlerAttacker].level * 5);
                    if (PayDay > gPaydayMoney)
                        gPaydayMoney = 0xFFFF;
                }
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                break;
            case MOVE_EFFECT_HAPPY_HOUR:
                if (GET_BATTLER_SIDE(gBattlerAttacker) == B_SIDE_PLAYER && !gBattleStruct->moneyMultiplierMove)
                {
                    gBattleStruct->moneyMultiplier *= 2;
                    gBattleStruct->moneyMultiplierMove = TRUE;
                }
                gBattlescriptCurrInstr++;
                break;
            case MOVE_EFFECT_TRI_ATTACK:
                if (gBattleMons[gEffectBattler].status1)
                {
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleScripting.moveEffect = Random() % 3 + 3;
                    SetMoveEffect(FALSE, 0);
                }
                break;
            case MOVE_EFFECT_CHARGING:
                gBattleMons[gEffectBattler].status2 |= STATUS2_MULTIPLETURNS;
                gLockedMoves[gEffectBattler] = gCurrentMove;
                gProtectStructs[gEffectBattler].chargingTurn = 1;
                ++gBattlescriptCurrInstr;
                break;//v IMPORTANT v       //think I'll put traj extra effects in the pokemon.c "damage" formula since it handles concurrent stuff
            case MOVE_EFFECT_WRAP:  //make envionment trap status4 define update other trap moveeffcts below than add end turn effects in util.c
                //if ((gBattleMons[gEffectBattler].status2 & STATUS2_WRAPPED) || (gBattleMons[gEffectBattler].status1 & STATUS1_WRAPPED)) was right this was cause of bind bug, work on setup new effect 
                /*if (gBattleMons[gEffectBattler].status2 & STATUS2_WRAPPED)  //if already wrapped do nothing/revamp wrapped status to be catch all for all traps
                {
                    ++gBattlescriptCurrInstr; //when done change wrapped check to, if wrapped move == currentmove (I think, need to see how set multiple wraps, 
                    //could just set different timer for each but still do all here)
                } */  //removed this put increment inside switch case
                //will change to only cover bind and wrap //put new status effects in util.c copy this function for each new wrap effect
                //else //need figure out skip logic,  for above, cant use status wrapped
                {
                     //put at top then set Trap Duration then into switch case based on wrappedmove to set individual timers and status 
                     //removed wrappedmove as its used for other things like move buffer will use for environment only as that one keeps  original 
                     //setup where it will pull move from wrapped move set here
                    gBattleStruct->wrappedBy[gEffectBattler] = gBattlerAttacker;  //still need setup wrappyby logic in battle_main
                    //I undestand this now first turn is turn status is applied so to get 2-5 full turns 3-6 value is needed
                    //but...I want that luck feelig of the enemy breaking out next turn so I'd like to set it to 2-6 but that is...convoluted
                    //potentially even more so as its using random & and not random %  since the and function uses bitwise exclusion I believe?
                    //***vsonic important for balance think need exclude bind from this as it locks move
                    if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_GRIP_CLAW
                        || (GetBattlerAbility(gBattlerAttacker) == ABILITY_SUCTION_CUPS))   //BUFF for suction cups
                    {
                        TrapDuration = 8;  //changed to 8 here, as actual trap duration is n - 1,  so this actually matches expected 7 turn duration
                        //gDisableStructs[gEffectBattler].wrapTurns = 7;
                        //gBattleMons[gEffectBattler].status1 |= STATUS1_WRAPPED; //not doing staus1, instead in battle_main where status2 clear is , check for wrap and hold effect of wrapped by
                        //if hold effect of wrappedby is grip claw etc. (checks above) then don't remove status when swithing, won't need to do status1
                    }
                    else 
                    {   //just lasting longer seems a bit useless maybe make it a status1 so you can switch out and still trap enemy?
                        //readjusted base duration for strengthened effects
                        //think this should be 2-4 turns
                        TrapDuration = ((Random() % 3) + 3);   //will do 2-6 turns , did wrong, need use + 3, with how works value 2 is 1 turn instead of 2 turns of trap
                        
                    } //as will be using separate timers for each wrap move, will put wrap duration on a constant/variable  and then pass it to the relevant timer directly
                    
                    switch (gCurrentMove) //point of all these is just to set status and timer
                    {           //think I can put the skip here,  if move specific timer isn't 0 incrment/skip, otherwise  set duration, set status, and gBattleScripting.moveEffect
                    case MOVE_BIND:
                    {
                        u8 k,numMoves;
                        u32 Rand = Random() % 3;
                        u32 selection;
                        
                    if (gBattleMons[gEffectBattler].status4 & STATUS4_BIND) //mos things arodn repo use status2 wrapped for if trap set, rework that
                        ++gBattlescriptCurrInstr;       //since added multiple statuses and timers make bool  true/valse set below for if trapped
                    else                                //same as how sturdied focus sashed etc. set battler trapped  when set timers, then clear when clear status
                    {                                   //replace its a trap status with that as well if used


                        if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_GRIP_CLAW
                        || (GetBattlerAbility(gBattlerAttacker) == ABILITY_SUCTION_CUPS))   //BUFF for suction cups
                        {
                            TrapDuration = 6;  //should be a 5 turn duration
                        }

                    
                        gDisableStructs[gEffectBattler].bindTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_BIND; //moved effect to attk canceler

                        //should skip everything if first turn/just switched, moved setting logic to battle_main battle action process
                        //that version will never struggle, so you're safer on switch in
                        //somehow this works exactly as I want, works even if switching into bind...
                        if (gDisableStructs[gEffectBattler].bindedMove == MOVE_NONE && gLastMoves[gEffectBattler] != MOVE_NONE) //gave in and set to work within encore restrictions
                        {
                            for (i = 0; i < MAX_MON_MOVES; ++i)
                                if (gBattleMons[gEffectBattler].moves[i] == gLastMoves[gEffectBattler]) //select last used move
                                    break; //if finds a move would stop between 0-3, otherwise would be 4

                            for (k = 0; k < MAX_MON_MOVES; ++k) //used for movepos
                                if (gBattleMons[gEffectBattler].moves[k] == gChosenMoveByBattler[gEffectBattler]) //select last used move
                                    break;
                                    
                            for (numMoves = 0; gBattleMons[gEffectBattler].moves[numMoves] != MOVE_NONE; ++numMoves)
                                if (gBattleMons[gEffectBattler].moves[numMoves] == MOVE_NONE)
                                    break;

                            if (gLastMoves[gEffectBattler] == MOVE_STRUGGLE
                            || gLastMoves[gEffectBattler] == MOVE_ENCORE
                            || gLastMoves[gEffectBattler] == MOVE_TRANSFORM
                            //|| gLastMoves[gEffectBattler] == MOVE_NONE
                            || gLastMoves[gEffectBattler] == MOVE_MIMIC
                            || gLastMoves[gEffectBattler] == MOVE_SKETCH
                            || gLastMoves[gEffectBattler] == MOVE_SLEEP_TALK
                            || gLastMoves[gEffectBattler] == MOVE_MIRROR_MOVE)
                                i = 4;  //if the move it finds is banned also set i to 4

                            if (i != 4
                            && gLastMoves[gEffectBattler] != MOVE_NONE
                            && gBattleMons[gEffectBattler].pp[i] != 0)
                            {
                                gDisableStructs[gEffectBattler].bindedMove = gBattleMons[gEffectBattler].moves[i];
                                gDisableStructs[gEffectBattler].bindMovepos = i;
                            }
                            else if (i == 4
                            && gLastMoves[gEffectBattler] != MOVE_NONE) //should be out of pp for selected move just struggle to avoid reloop
                            {
                                gDisableStructs[gEffectBattler].bindedMove = MOVE_STRUGGLE;
                                
                            }
                            else if (gLastMoves[gEffectBattler] == MOVE_NONE) //try pick random move with pp, if bind is faster than enemy
                            {
                                selection = Random() % numMoves;
                                if (Rand == 0)
                                    gChosenMoveByBattler[gEffectBattler] = MOVE_STRUGGLE;
                                else
                                    gChosenMoveByBattler[gEffectBattler] = gBattleMons[gEffectBattler].moves[selection];

                                if (gChosenMoveByBattler[gEffectBattler] == MOVE_STRUGGLE
                                || gChosenMoveByBattler[gEffectBattler] == MOVE_ENCORE
                                || gChosenMoveByBattler[gEffectBattler] == MOVE_TRANSFORM
                                //|| gChosenMoveByBattler[gEffectBattler] == MOVE_NONE
                                || gChosenMoveByBattler[gEffectBattler] == MOVE_MIMIC
                                || gChosenMoveByBattler[gEffectBattler] == MOVE_SKETCH
                                || gChosenMoveByBattler[gEffectBattler] == MOVE_SLEEP_TALK
                                || gChosenMoveByBattler[gEffectBattler] == MOVE_MIRROR_MOVE)
                                    gChosenMoveByBattler[gEffectBattler] = MOVE_STRUGGLE;

                                gDisableStructs[gEffectBattler].bindedMove = gChosenMoveByBattler[gEffectBattler];//gBattleMons[gEffectBattler].moves[j];
                                gDisableStructs[gEffectBattler].bindMovepos = selection;
                            }
                               
                        } //idk what's wrong this should work for every situation far as I can tell?
                        //unless issue was using target and not effectbattler, i don't see howbut idk


                        
                    }
                        break;
                    }
                    case MOVE_WRAP:
                    if (gBattleMons[gEffectBattler].status2 & STATUS2_WRAPPED)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gDisableStructs[gEffectBattler].wrapTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status2 |= STATUS2_WRAPPED;
                    } //if  use individual timer for identifier instead of status for these can do more and save space, without needing to take up flags                 
                        break; //idk if can do, otherwise could just make status 4  environmentTrapTurns
                    case MOVE_FIRE_SPIN:
                    if (gDisableStructs[gEffectBattler].environmentTrapTurns) //vsonic make message environment trap already in effect 
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gBattleStruct->wrappedMove[gEffectBattler] = gCurrentMove;
                        gDisableStructs[gEffectBattler].environmentTrapTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_FIRE_SPIN;
                    }
                        break;
                    case MOVE_WHIRLPOOL:
                     if (gDisableStructs[gEffectBattler].environmentTrapTurns)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gBattleStruct->wrappedMove[gEffectBattler] = gCurrentMove;
                        gDisableStructs[gEffectBattler].environmentTrapTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_WHIRLPOOL;
                    }
                        break;
                    case MOVE_SAND_TOMB:
                     if (gDisableStructs[gEffectBattler].environmentTrapTurns)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gBattleStruct->wrappedMove[gEffectBattler] = gCurrentMove;
                        gDisableStructs[gEffectBattler].environmentTrapTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_SAND_TOMB;
                    }
                        break;
                    case MOVE_MAGMA_STORM:
                     if (gDisableStructs[gEffectBattler].environmentTrapTurns)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gBattleStruct->wrappedMove[gEffectBattler] = gCurrentMove;
                        gDisableStructs[gEffectBattler].environmentTrapTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_MAGMA_STORM;
                    }
                        break;
                    case MOVE_CLAMP:
                    if (gBattleMons[gEffectBattler].status4 & STATUS4_CLAMP)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gDisableStructs[gEffectBattler].clampTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_CLAMP;
                    }
                        break;
                    case MOVE_SWARM:
                    if (gBattleMons[gEffectBattler].status4 & STATUS4_SWARM)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gDisableStructs[gEffectBattler].swarmTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_SWARM;
                    }
                        break;
                    case MOVE_SNAP_TRAP:
                    if (gBattleMons[gEffectBattler].status4 & STATUS4_SNAP_TRAP) //snap trap by default should stay if you switch out, grip claw just makes it last longer
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gDisableStructs[gEffectBattler].snaptrapTurns = 5; //since supposed to be 4-5 turns - done effect lasts 4 turns
                        gBattleMons[gEffectBattler].status4 |= STATUS4_SNAP_TRAP;
                    }
                        break; 
                    case MOVE_THUNDER_CAGE:
                    if (gBattleMons[gEffectBattler].status4 & STATUS4_THUNDER_CAGE)
                        ++gBattlescriptCurrInstr;
                    else
                    {
                        gDisableStructs[gEffectBattler].thundercageTurns = TrapDuration;
                        gBattleMons[gEffectBattler].status4 |= STATUS4_THUNDER_CAGE;
                    }
                        break;   //phoned in for now, change to non enviro trapp later, think   

                    }

                    BattleScriptPush(gBattlescriptCurrInstr + 1);//below set based on move effect so will need to change move effect within switch case
                    gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect]; //just for displaying battle message for specific wrap move, so dont need change moveeffect
                    for (gBattleCommunication[MULTISTRING_CHOOSER] = 0; ; ++gBattleCommunication[MULTISTRING_CHOOSER]) //think this just loops till find current move?
                    {
                        if (gBattleCommunication[MULTISTRING_CHOOSER] > NUM_TRAPPING_MOVES - 1)
                            break;
                        if (gTrappingMoves[gBattleCommunication[MULTISTRING_CHOOSER]] == gCurrentMove)
                            break;                  //what I mean by that is, I could keep all traps in effect wrap, and use wrap turns, but then set a different status for each move at the bottom after checking which move was used to trap
                    }//believe this is only for reading from the trapstring table can prob remove for other trap effects
                }//multistring > 4 would be a problem if I didn't split off the moves from the wrap effect
                break;
            /*case MOVE_EFFECT_RECOIL_25: // 25% recoil   also struggle
                gBattleMoveDamage = (gHpDealt) / 4;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (GetBattlerAbility(gEffectBattler) == ABILITY_PARENTAL_BOND)
                    gBattleMoveDamage *= 2;
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];
                break;*/
            case MOVE_EFFECT_ATK_PLUS_1:
            case MOVE_EFFECT_DEF_PLUS_1:
            case MOVE_EFFECT_SPD_PLUS_1:
            case MOVE_EFFECT_SP_ATK_PLUS_1:
            case MOVE_EFFECT_SP_DEF_PLUS_1:
            case MOVE_EFFECT_ACC_PLUS_1:
            case MOVE_EFFECT_EVS_PLUS_1:
                if (NoAliveMonsForEitherParty()
                    || ChangeStatBuffs(SET_STAT_BUFF_VALUE(1),
                        gBattleScripting.moveEffect - MOVE_EFFECT_ATK_PLUS_1 + 1,
                        affectsUser | STAT_CHANGE_UPDATE_MOVE_EFFECT, NULL))
                {
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleScripting.animArg1 = gBattleScripting.moveEffect & ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                    gBattleScripting.animArg2 = 0;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_StatUp;
                }
                break;
            case MOVE_EFFECT_ATK_MINUS_1:
            case MOVE_EFFECT_DEF_MINUS_1:
            case MOVE_EFFECT_SPD_MINUS_1:
            case MOVE_EFFECT_SP_ATK_MINUS_1:
            case MOVE_EFFECT_SP_DEF_MINUS_1:
            case MOVE_EFFECT_ACC_MINUS_1:
            case MOVE_EFFECT_EVS_MINUS_1:
                //flags = affectsUser;
               
               if (affectsUser == MOVE_EFFECT_AFFECTS_USER)
                    flags = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN;
                else
                    flags = 0;
                
                if (mirrorArmorReflected)
                    flags |= (STAT_CHANGE_BS_PTR * !affectsUser);
                else
                    flags |= STAT_CHANGE_UPDATE_MOVE_EFFECT;

               if ((gBattleScripting.moveEffect == MOVE_EFFECT_ACC_MINUS_1) && IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GROUND)
                && (gBattleStruct->dynamicMoveType == TYPE_GROUND
                || gBattleMoves[gCurrentMove].type == TYPE_GROUND
                || gBattleMoves[gCurrentMove].argument == TYPE_GROUND)
                && GetBattleMoveSplit(gCurrentMove) != SPLIT_STATUS) //status already covered in other function
                {
                    gBattleScripting.moveEffect &= ~(MOVE_EFFECT_CERTAIN);
                    gBattleScripting.moveEffect = 0;
                    gBattleScripting.multihitMoveEffect = 0;
                    //BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_GroundNullifiesEarth;
                    return; //oh adding the return fixed it o.0
                } 

                /*if (mirrorArmorReflected && !affectsUser)
                    flags |= STAT_CHANGE_BS_PTR;
                if (ChangeStatBuffs(SET_STAT_BUFF_VALUE(1) | STAT_BUFF_NEGATIVE,
                                    gBattleScripting.moveEffect - MOVE_EFFECT_ATK_MINUS_1 + 1,
                                    flags | STAT_CHANGE_UPDATE_MOVE_EFFECT, 
                                    gBattlescriptCurrInstr + 1))
                {
                    if (!mirrorArmorReflected)
                    ++gBattlescriptCurrInstr;
                }*/

               //issue appears to be here, changing flags to 0 or something else makes defense drop work correctly
                if (ChangeStatBuffs(SET_STAT_BUFF_VALUE(1) | STAT_BUFF_NEGATIVE,
                                    gBattleScripting.moveEffect - MOVE_EFFECT_ATK_MINUS_1 + 1,
                                    flags, gBattlescriptCurrInstr + 1) == STAT_CHANGE_DIDNT_WORK)
                {
                    if (!mirrorArmorReflected)
                        gBattlescriptCurrInstr++;
                }
                else
                {
                    gBattleScripting.animArg1 = gBattleScripting.moveEffect & ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                    gBattleScripting.animArg2 = 0;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_StatDown;
                }
                break;
            case MOVE_EFFECT_ATK_PLUS_2:
            case MOVE_EFFECT_DEF_PLUS_2:
            case MOVE_EFFECT_SPD_PLUS_2:
            case MOVE_EFFECT_SP_ATK_PLUS_2:
            case MOVE_EFFECT_SP_DEF_PLUS_2:
            case MOVE_EFFECT_ACC_PLUS_2:
            case MOVE_EFFECT_EVS_PLUS_2:
                if (NoAliveMonsForEitherParty()
                    || ChangeStatBuffs(SET_STAT_BUFF_VALUE(2),
                                    gBattleScripting.moveEffect - MOVE_EFFECT_ATK_PLUS_2 + 1,
                                    affectsUser | STAT_CHANGE_UPDATE_MOVE_EFFECT, NULL))
                {
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleScripting.animArg1 = gBattleScripting.moveEffect & ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                    gBattleScripting.animArg2 = 0;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_StatUp;
                }
                break;
            case MOVE_EFFECT_ATK_MINUS_2:
            case MOVE_EFFECT_DEF_MINUS_2:
            case MOVE_EFFECT_SPD_MINUS_2:
            case MOVE_EFFECT_SP_ATK_MINUS_2:
            case MOVE_EFFECT_SP_DEF_MINUS_2:
            case MOVE_EFFECT_ACC_MINUS_2:
            case MOVE_EFFECT_EVS_MINUS_2:
                //flags = affectsUser;

                if (affectsUser == MOVE_EFFECT_AFFECTS_USER)
                    flags = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN;
                else
                    flags = 0;
                
                if (mirrorArmorReflected)
                    flags |= (STAT_CHANGE_BS_PTR * !affectsUser);
                else
                    flags |= STAT_CHANGE_UPDATE_MOVE_EFFECT;

                if ((gBattleScripting.moveEffect == MOVE_EFFECT_ACC_MINUS_2) && IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GROUND)
                && (gBattleStruct->dynamicMoveType == TYPE_GROUND
                || gBattleMoves[gCurrentMove].type == TYPE_GROUND
                || gBattleMoves[gCurrentMove].argument == TYPE_GROUND)
                && GetBattleMoveSplit(gCurrentMove) != SPLIT_STATUS) //status already covered in other function
                {
                    gBattleScripting.moveEffect &= ~(MOVE_EFFECT_CERTAIN);
                    gBattleScripting.moveEffect = 0;
                    gBattleScripting.multihitMoveEffect = 0;
                    //BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_GroundNullifiesEarth;
                    return; //oh adding the return fixed it o.0
                }

                if (ChangeStatBuffs(SET_STAT_BUFF_VALUE(2) | STAT_BUFF_NEGATIVE,
                                    gBattleScripting.moveEffect - MOVE_EFFECT_ATK_MINUS_2 + 1,
                                    flags, gBattlescriptCurrInstr + 1) == STAT_CHANGE_DIDNT_WORK)
                {
                    if (!mirrorArmorReflected)
                        gBattlescriptCurrInstr++;
                }
               
                //if (mirrorArmorReflected && !affectsUser)
                //    flags |= STAT_CHANGE_BS_PTR;

                /*if (ChangeStatBuffs(SET_STAT_BUFF_VALUE(2) | STAT_BUFF_NEGATIVE,
                                    gBattleScripting.moveEffect - MOVE_EFFECT_ATK_MINUS_2 + 1,
                                    flags | STAT_CHANGE_UPDATE_MOVE_EFFECT,
                                    gBattlescriptCurrInstr + 1))
                {
                    if (!mirrorArmorReflected)
                    ++gBattlescriptCurrInstr;
                }*/
                else
                {
                    gBattleScripting.animArg1 = gBattleScripting.moveEffect & ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                    gBattleScripting.animArg2 = 0;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_StatDown;
                }
                break;
            case MOVE_EFFECT_RECHARGE:
                gDisableStructs[gEffectBattler].rechargeTimer = 1;
                gLockedMoves[gEffectBattler] = gCurrentMove;
                ++gBattlescriptCurrInstr;
                break;
            case MOVE_EFFECT_RAGE:
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_RAGE)
            {
                if (gDisableStructs[gBattlerAttacker].rageCounter != 5) //with curr setup would max at a move of bp 75
                {
                        gDisableStructs[gBattlerAttacker].rageCounter++; //ok would need to see if this works, since in this script setmoveeffect is before atk, this should work but idk
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_AttackerRageBuilding; //this works perfectly
                }
                else
                    ++gBattlescriptCurrInstr;
                
            }
            else
            {
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_RAGE; //add check for status2 rage, if set just go to next instruction
                ++gBattlescriptCurrInstr;
            }
                break;
            case MOVE_EFFECT_STEAL_ITEM:
                {
                    if (!CanStealItem(gBattlerAttacker, gBattlerTarget, gBattleMons[gBattlerTarget].item)) //thief i think
                    {
                        ++gBattlescriptCurrInstr;
                        break;
                    }
                    //side = GetBattlerSide(gBattlerAttacker);
                    /*if (GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT //prevents opponent stealing player item in specific battle types 
                     && !(gBattleTypeFlags &
                          (BATTLE_TYPE_EREADER_TRAINER
                          | BATTLE_TYPE_BATTLE_TOWER
                          | BATTLE_TYPE_LINK))
                     && gTrainerBattleOpponent_A != 0x400)
                    {
                        ++gBattlescriptCurrInstr;
                    }
                    else if (!(gBattleTypeFlags &
                             (BATTLE_TYPE_EREADER_TRAINER
                             | BATTLE_TYPE_BATTLE_TOWER
                             | BATTLE_TYPE_LINK))
                         && gTrainerBattleOpponent_A != 0x400
                         && (gWishFutureKnock.knockedOffMons[side] & gBitTable[gBattlerPartyIndexes[gBattlerAttacker]]))
                    {
                        ++gBattlescriptCurrInstr;
                    }*/ //think are just trainr type restrictions 
                    else if (gBattleMons[gBattlerTarget].item
                        && GetBattlerAbility(gBattlerTarget) == ABILITY_STICKY_HOLD)
                    {
                        gBattlescriptCurrInstr = BattleScript_StickyHoldActivates;
                        gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
                        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
                    }
                    else if (//gBattleMons[gBattlerAttacker].item != ITEM_NONE
                          gBattleMons[gBattlerTarget].item == ITEM_ENIGMA_BERRY
                          || gBattleMons[gBattlerTarget].item == ITEM_NONE)
                    {
                        ++gBattlescriptCurrInstr;
                    }
                    else //success condition
                    {
                        StealTargetItem(gBattlerAttacker, gBattlerTarget);  // Attacker steals target item
                       // gBattleMons[gBattlerAttacker].item = ITEM_NONE; // Item assigned later on with thief (see MOVE_END_CHANGED_ITEMS) - is this even needed?
                       if (gBattleMons[gBattlerAttacker].item == ITEM_NONE)
                        gBattleStruct->changedItems[gBattlerAttacker] = gLastUsedItem; // Stolen item to be assigned later - onlyh need do if actual assing item to self
                        BattleScriptPush(gBattlescriptCurrInstr + 1);
                        gBattlescriptCurrInstr = BattleScript_ItemSteal;
                        //*(u8 *)((u8 *)(&gBattleStruct->choicedMove[gBattlerTarget]) + 0) = 0;
                        //*(u8 *)((u8 *)(&gBattleStruct->choicedMove[gBattlerTarget]) + 1) = 0;
                    }//NEED test hopefullyu works, original code used gbattlertarget, emerald stuff used attacker
                }
                break;
            case MOVE_EFFECT_PREVENT_ESCAPE:
                if (gBattleMons[gEffectBattler].status2 & STATUS2_ESCAPE_PREVENTION)
                {                                           //and just put in each case, lan like magic gaurd check, check macro and do increment, with a one line paste
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleMons[gBattlerTarget].status2 |= STATUS2_ESCAPE_PREVENTION;
                    gDisableStructs[gBattlerTarget].battlerPreventingEscape = gBattlerAttacker;
                    ++gBattlescriptCurrInstr;
                }
                break;
            case MOVE_EFFECT_SWITCH_LOCKED:
                if (gBattleMons[gBattlerTarget].status2 & STATUS2_SWITCH_LOCKED)
                {
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleMons[gBattlerTarget].status2 |= STATUS2_SWITCH_LOCKED;
                    gDisableStructs[gBattlerTarget].SwitchBinding = 3;
                     ++gBattlescriptCurrInstr;
                }               
                break;
            case MOVE_EFFECT_NIGHTMARE:
                if (gBattleMons[gEffectBattler].status2 & STATUS2_NIGHTMARE)
                {                                           //and just put in each case, lan like magic gaurd check, check macro and do increment, with a one line paste
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleMons[gBattlerTarget].status2 |= STATUS2_NIGHTMARE;
                    ++gBattlescriptCurrInstr;
                }
                break;
            case MOVE_EFFECT_ALL_STATS_UP:
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_AllStatsUp;
                break;
            case MOVE_EFFECT_RAPIDSPIN:
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_RapidSpinAway;
                break;
            case MOVE_EFFECT_ATK_DEF_DOWN: // SuperPower    //use same trick did for trap effects make stat drop certain put 25% recoil in augment or vice versa, nvm just did atk drop 
                if (!NoAliveMonsForEitherParty()){
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_AtkDefDown;
                }
                break;
            case MOVE_EFFECT_DEF_SPDEF_DOWN: //og close combat now changed, but keep effect for test
            if (!NoAliveMonsForEitherParty()){
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_DefSpDefDown;
                }
                break;
            case MOVE_EFFECT_HEAVY_RECOIL:
            case MOVE_EFFECT_RECOIL_25:
            case MOVE_EFFECT_MED_RECOIL_W_STATUS: //volt tackle etc.
            case MOVE_EFFECT_RECOIL_33: // Double Edge / removed below to use upgraded recoil setup
                /*gBattleMoveDamage = gHpDealt / 3;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;*/
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_MoveEffectRecoil;
                break;
            case MOVE_EFFECT_THRASH:
                if (gBattleMons[gEffectBattler].status2 & STATUS2_LOCK_CONFUSE) //move effect thrash sets status lock confusion I think? so do nothing if already set?
                {
                    ++gBattlescriptCurrInstr;
                }
                else
                {
                    gBattleMons[gEffectBattler].status2 |= STATUS2_MULTIPLETURNS;
                    gLockedMoves[gEffectBattler] = gCurrentMove;
                    gBattleMons[gEffectBattler].status2 |= STATUS2_LOCK_CONFUSE;   //thrash for 2-3 turns
                    gDisableStructs[gEffectBattler].rampageMoveTurns = ((Random() & 1) + 2); //thrash for 2-3 turns
                }
                break;
            /*case MOVE_EFFECT_KNOCK_OFF:
                if (battlerAbility == ABILITY_STICKY_HOLD)
                {
                    if (gBattleMons[gEffectBattler].item == ITEM_NONE)
                    {
                        ++gBattlescriptCurrInstr;
                    }
                    else
                    {
                        gLastUsedAbility = ABILITY_STICKY_HOLD;
                        gBattlescriptCurrInstr = BattleScript_StickyHoldActivates;
                        RecordAbilityBattle(gEffectBattler, ABILITY_STICKY_HOLD);
                    }
                    break;
                }
                if (gBattleMons[gEffectBattler].item)
                {
                    side = GetBattlerSide(gEffectBattler);
                    gLastUsedItem = gBattleMons[gEffectBattler].item;
                    gBattleMons[gEffectBattler].item = ITEM_NONE;
                    gWishFutureKnock.knockedOffMons[side] |= gBitTable[gBattlerPartyIndexes[gEffectBattler]];
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_KnockedOff;
                    *(u8 *)((u8 *)(&gBattleStruct->choicedMove[gEffectBattler]) + 0) = 0;
                    *(u8 *)((u8 *)(&gBattleStruct->choicedMove[gEffectBattler]) + 1) = 0;
                }
                else
                {
                    ++gBattlescriptCurrInstr;
                }
                TryKnockOffBattleScript(gBattlerTarget);
                break;*/
            case MOVE_EFFECT_SP_ATK_TWO_DOWN: // Overheat - based on emerald kaizo, changing overheat to recoil move
                if (!NoAliveMonsForEitherParty()){
                BattleScriptPush(gBattlescriptCurrInstr + 1);
                gBattlescriptCurrInstr = BattleScript_SAtkDown2;
                }
                break;
            case MOVE_EFFECT_CLEAR_SMOG:
                for (i = 0; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[gEffectBattler].statStages[i] != DEFAULT_STAT_STAGE)
                        break;
                }
                if ((gSpecialStatuses[gEffectBattler].physicalDmg || gSpecialStatuses[gEffectBattler].specialDmg) && i != NUM_BATTLE_STATS)
                {
                    for (i = 0; i < NUM_BATTLE_STATS; i++)
                        gBattleMons[gEffectBattler].statStages[i] = DEFAULT_STAT_STAGE;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_MoveEffectClearSmog;
                }
                break;
            case MOVE_EFFECT_FLAME_BURST:
                if (IsBattlerAlive(BATTLE_PARTNER(gBattlerTarget))
                    && !(gStatuses3[BATTLE_PARTNER(gBattlerTarget)] & STATUS3_SEMI_INVULNERABLE)
                    && GetBattlerAbility(BATTLE_PARTNER(gBattlerTarget)) != ABILITY_MAGIC_GUARD)
                {
                    gBattleScripting.savedBattler = BATTLE_PARTNER(gBattlerTarget);
                    gBattleMoveDamage = gBattleMons[BATTLE_PARTNER(gBattlerTarget)].hp / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattlescriptCurrInstr = BattleScript_MoveEffectFlameBurst;
                }
                break;
            case MOVE_EFFECT_FEINT:
                if (IsBattlerProtected(gBattlerTarget, gCurrentMove))
                {
                    gProtectStructs[gBattlerTarget].protected = FALSE;
                    gSideStatuses[GetBattlerSide(gBattlerTarget)] &= ~SIDE_STATUS_WIDE_GUARD;
                    gSideStatuses[GetBattlerSide(gBattlerTarget)] &= ~SIDE_STATUS_QUICK_GUARD;
                    gSideStatuses[GetBattlerSide(gBattlerTarget)] &= ~SIDE_STATUS_CRAFTY_SHIELD;
                    gSideStatuses[GetBattlerSide(gBattlerTarget)] &= ~SIDE_STATUS_MAT_BLOCK;
                    gProtectStructs[gBattlerTarget].spikyShielded = FALSE;
                    gProtectStructs[gBattlerTarget].kingsShielded = FALSE;
                    gProtectStructs[gBattlerTarget].banefulBunkered = FALSE;
                    gProtectStructs[gBattlerTarget].obstructed = FALSE;
                    //gProtectStructs[gBattlerTarget].silkTrapped = FALSE;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    if (gCurrentMove == MOVE_HYPERSPACE_FURY)
                        gBattlescriptCurrInstr = BattleScript_HyperspaceFuryRemoveProtect;  //WORK OUT and try to use for protect break plan
                    else
                        gBattlescriptCurrInstr = BattleScript_MoveEffectFeint;
                }
                break;
            case MOVE_EFFECT_SPECTRAL_THIEF:
                if (!NoAliveMonsForEitherParty())
                {
                    gBattleStruct->stolenStats[0] = 0; // Stats to steal.
                    gBattleScripting.animArg1 = 0;
                    for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
                    {
                        if (gBattleMons[gBattlerTarget].statStages[i] > DEFAULT_STAT_STAGE && gBattleMons[gBattlerAttacker].statStages[i] != MAX_STAT_STAGE)
                        {
                            gBattleStruct->stolenStats[0] |= gBitTable[i];
                            // Store by how many stages to raise the stat.
                            gBattleStruct->stolenStats[i] = gBattleMons[gBattlerTarget].statStages[i] - DEFAULT_STAT_STAGE;
                            while (gBattleMons[gBattlerAttacker].statStages[i] + gBattleStruct->stolenStats[i] > MAX_STAT_STAGE)
                                gBattleStruct->stolenStats[i]--;
                            gBattleMons[gBattlerTarget].statStages[i] = DEFAULT_STAT_STAGE;

                            if (gBattleStruct->stolenStats[i] >= 2)
                                byTwo++;

                            if (gBattleScripting.animArg1 == 0)
                            {
                                if (byTwo)
                                    gBattleScripting.animArg1 = STAT_ANIM_PLUS2 - 1 + i;
                                else
                                    gBattleScripting.animArg1 = STAT_ANIM_PLUS1 - 1 + i;
                            }
                            else
                            {
                                if (byTwo)
                                    gBattleScripting.animArg1 = STAT_ANIM_MULTIPLE_PLUS2;
                                else
                                    gBattleScripting.animArg1 = STAT_ANIM_MULTIPLE_PLUS1;
                            }
                        }
                    }

                    if (gBattleStruct->stolenStats[0] != 0)
                    {
                        BattleScriptPush(gBattlescriptCurrInstr + 1);
                        gBattlescriptCurrInstr = BattleScript_SpectralThiefSteal;
                    }
                }
                break;
            case MOVE_EFFECT_V_CREATE:
                if (!NoAliveMonsForEitherParty())
                {
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_VCreateStatLoss;
                }
                break;
            case MOVE_EFFECT_CORE_ENFORCER:
                if (GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget)
                    && !NoAliveMonsForEitherParty())
                {
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_MoveEffectCoreEnforcer;
                }
                break;
            case MOVE_EFFECT_THROAT_CHOP:
                gDisableStructs[gEffectBattler].throatChopTimer = 2;
                gBattlescriptCurrInstr++;
                break;
            case MOVE_EFFECT_INCINERATE:
                if ((gBattleMons[gEffectBattler].item >= FIRST_BERRY_INDEX && gBattleMons[gEffectBattler].item <= LAST_BERRY_INDEX)
                    || (GetBattlerHoldEffect(gEffectBattler, FALSE) == HOLD_EFFECT_GEMS)
                    )
                {
                    
                    TryKnockOffBattleScript(gEffectBattler, gBattlerAttacker, gBattleScripting.moveEffect);
                }
                break;
            case MOVE_EFFECT_BUG_BITE:
                if (ItemId_GetPocket(gBattleMons[gEffectBattler].item) == POCKET_BERRY_POUCH
                    && battlerAbility != ABILITY_STICKY_HOLD)
                {
                    
                    TryKnockOffBattleScript(gEffectBattler, gBattlerAttacker, gBattleScripting.moveEffect);
                } //vsonic potentially, can emulate to make my vers belch work, where consumes users berry if held
                break;//nvm forgot move effects go at end of move
            case MOVE_EFFECT_RELIC_SONG:
                if (GetBattlerAbility(gBattlerAttacker) != ABILITY_SHEER_FORCE && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_TRANSFORMED))
                {
                    if (gBattleMons[gBattlerAttacker].species == SPECIES_MELOETTA)
                    {
                        gBattleMons[gBattlerAttacker].species = SPECIES_MELOETTA_PIROUETTE;
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeMoveEffect);
                    }
                    else if (gBattleMons[gBattlerAttacker].species == SPECIES_MELOETTA_PIROUETTE)
                    {
                        gBattleMons[gBattlerAttacker].species = SPECIES_MELOETTA;
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeMoveEffect);
                    }
                }
                break;
            case MOVE_EFFECT_TRAP_BOTH:
                if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_ESCAPE_PREVENTION) && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_ESCAPE_PREVENTION))
                {
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_BothCanNoLongerEscape;
                }
                if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_ESCAPE_PREVENTION))
                    gDisableStructs[gBattlerTarget].battlerPreventingEscape = gBattlerAttacker;

                if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_ESCAPE_PREVENTION))
                    gDisableStructs[gBattlerAttacker].battlerPreventingEscape = gBattlerTarget;

                gBattleMons[gBattlerTarget].status2 |= STATUS2_ESCAPE_PREVENTION;
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_ESCAPE_PREVENTION;
                break; //vsonic important check for issues w double apply would need be double battle to test
            case MOVE_EFFECT_SCALE_SHOT:
                if (!NoAliveMonsForEitherParty())
                {
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_DefDownSpeedUp;
                }
                break;
            case MOVE_EFFECT_LOSE_TYPE: //equivalent burn up etc.
                // This seems unnecessary but is done to make it work properly with Parental Bond
                BattleScriptPush(gBattlescriptCurrInstr + 1);   //^not my note
                gBattlescriptCurrInstr = BattleScript_AttackerRemoveType;
                break;
            case MOVE_EFFECT_ROUND:
                TryUpdateRoundTurnOrder(); // If another Pok�mon uses Round before the user this turn, the user will use Round directly after it
                gBattlescriptCurrInstr++;
                break;
            case MOVE_EFFECT_STEALTH_ROCK:
                if (!(gSideStatuses[GetBattlerSide(gEffectBattler)] & SIDE_STATUS_STEALTH_ROCK))
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_POINTEDSTONESFLOAT;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_StealthRockActivates;
                }
                break;
            }
            
        }
    }//end of move effect checks
    gBattleScripting.moveEffect = 0;
    gBattleScripting.multihitMoveEffect = 0;  //added here for seteffetprimary & seteffectsecondary as they bypass seteffedtwithchance that clears moveeffects after use
                                                //also fix for contact ability status bug
}

#define SPECIAL_TRAP_EFFECTCHANCE
static void atk15_setmoveeffectwithchance(void) //occurs to me that fairy moves weren't meant with applying a status in mind, so all fairy moves would have other effects
{ //so I think I'll need to make some code specifically to apply the effect separate from fairy moves normal effect
    //right now I'm thinking if move is fairy and does damage, that's a good starting point, and I may exclude certain other moves as well,
    //that are high damage already and should be left alone, so something like like current move does not equal move list of moves from array.

    //I can probably put it here, since the secondary effect chance field isn't completely necessary I think.
    //just need to make percentChance = 10, under the conditions I already listed above.  and to specifcially be for settign spirit lock

    //hey old me, that ish is all wrong, without secondary chance, effects won't apply, and that's dealt with in battle_moves file
    //
    CMD_ARGS();
    u32 percentChance,argumentChance;
    u8 atkHoldEffectParam = GetBattlerHoldEffectParam(gBattlerAttacker, gBattleMons[gBattlerAttacker].item); //for kings rock
    if (gBattleMoves[gCurrentMove].effect != EFFECT_TWO_TYPED_MOVE)
    {

        if (gBattleMoves[gCurrentMove].argumentEffectChance == 0)   //to ensure arguments already set work, so dont need to add argumentchance to every move
            argumentChance = gBattleMoves[gCurrentMove].secondaryEffectChance;  //but keeps from using the percentChance 0 makes certain effect for arguments
        else                                                                //not a major issue if can just keep important/main effects to effect not argument, 
            argumentChance = gBattleMoves[gCurrentMove].argumentEffectChance;   //just make sure argument never has effect that would need to be set certain (just use 100 if need to)
    }
    //THIS IS WHY IT WAS CONFUSING battlescripting.moveEffect AREN'T moveeffects they are just "effects"
    //MOVE EFFECT is a completely different thing that is actually being set by this function  not battlescripting.moveEffect!!!!
    //wrong again it IS moveeffect the EFFECT goes to battlescript which assings a move effect and is stored in scripting.moveEffect to read here

    if ((gBattleScripting.moveEffect != gBattleMoves[gCurrentMove].argument) && gBattleScripting.moveEffect != 0) //on second look think this won't work as variosargumetotmoveeffect may be 
        percentChance = gBattleMoves[gCurrentMove].secondaryEffectChance;   //setting the argumentt as the move effct?
    else if ((gBattleScripting.moveEffect == gBattleMoves[gCurrentMove].argument) && gBattleMoves[gCurrentMove].argument != 0
        && gBattleMoves[gCurrentMove].effect != EFFECT_TWO_TYPED_MOVE)
        percentChance = argumentChance; //confused it doesn't use them interchangeably so may work? think is different?
    //since I didn't understand scripting.moveEffect this was the isue it was always defaulting to 0 as above block didn't read

    //cacophony boost
    if (ShouldCacophonyBoostEffectChance(gCurrentMove))
        percentChance *= 2;

    //hail based freeze boost, -lowered given new mechanic
    if ((gBattleWeather & WEATHER_HAIL_ANY)
        && gBattleScripting.moveEffect == MOVE_EFFECT_FREEZE) //think this is better?
        percentChance = (percentChance * 150) / 100; //= gBattleMoves[gCurrentMove].secondaryEffectChance * 2;  //its good, happened 2 out of 5 hits. decided to make it 1/16 dmg
    
    //freeze boost, for later counter effect for ice toxic orb 
    if (gBattleMons[gBattlerTarget].status1 & STATUS1_FREEZE
     && gBattleScripting.moveEffect == MOVE_EFFECT_FREEZE)
        percentChance = (percentChance * 150) / 100;
      
    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_SERENE_GRACE) //way if else-if works,they are paired and only the one that is true will be executed
        percentChance *= 2;                                         //if I need to execute multiple, than use multiple ifs instead  vsonic
    
    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_FRISK && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)) //
        percentChance = (percentChance * 150) / 100;

    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_DARK_DEAL) //is excluded
        percentChance = (percentChance * 150) / 100;

    else if (GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_DARK_DEAL) //hopefully stacks
        percentChance *= 2; //ok now the order is right

    if (gBattleScripting.moveEffect == MOVE_EFFECT_FLINCH
        && GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_FLINCH) //kings rock, make it link with move effect chance
        percentChance = (percentChance * (atkHoldEffectParam + 100)) / 100; //ex (20 * 110) = 2200  / 100 = 22  w this serene grace applies once not twice for kings rock

        

    

    //for these to work must be placed in .effect member of battle_moves.h they aren't used in argument,
    //these are the main effects of the move
    //I could set it to gbattlescripting.moveeffect and it'd work for both but I don't want that.
    //this is a restriction for the sake of structure.
    //to separate primary effects from  secondary effects
    
    //rather than doing all this can replace with if secondary effect chance equals 0, set certain
    //triggers for effect when secondary effect chance is 0, and erroneously for argument if secondary effect chance is 0, and argument effect chance is 0
    //last case should not happen as I should have arugment chance set for moves that dont have secondary effect chance already.
    if (percentChance == 0) //seems to have issue when using certain on no effect moves so preventing that here
        gBattleScripting.moveEffect |= MOVE_EFFECT_CERTAIN;  //ok I don't know difference but this works without issue 
        //SetMoveEffect(0, MOVE_EFFECT_CERTAIN); 
        //think this was issue for effects always procing, not proper exclusions/checks on this
        //added them above, testing

   /* if (gBattleMoves[gCurrentMove].effect == ITS_A_TRAP)   //if this works make a define for trap effects & separate effect & move effect & battlscript for each
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN);  //that way may not need to make a separate status,// seems to work no apparent bugs
    //will need to remove infestation from this as I want to use that as new bug specific status also
    //is best way to do other than making an entirely new status of same effect\

    if (gBattleMoves[gCurrentMove].effect == EFFECT_HIT_ESCAPE) //eventually turn thse into switch case
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN); 
    
    if (gBattleMoves[gCurrentMove].effect == EFFECT_LOSETYPE_HIT)
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN); 

    if (gBattleMoves[gCurrentMove].effect == EFFECT_TWO_TYPED_MOVE) //mostly so I can add para chance to splishy splash
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN);

    if (gBattleMoves[gCurrentMove].effect == EFFECT_SPEED_UP_HIT)       //go over 100%  effects, see which I can put here to just make certain, may be able to do all.
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN);

    if (gBattleMoves[gCurrentMove].effect == EFFECT_BUG_BITE)
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN); */
    
    //tested confirmed change works
    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_POISONED_LEGACY
        && (gBattleMons[gBattlerAttacker].hp <= (gBattleMons[gBattlerAttacker].maxHP / 2))) //make sure effects only activate when in a pinch
    {
        if (gBattleScripting.moveEffect == MOVE_EFFECT_POISON || gBattleScripting.moveEffect == MOVE_EFFECT_TOXIC)
            gBattleScripting.moveEffect |= MOVE_EFFECT_CERTAIN;  //gauranteed poison
    }
    //vsonic suddenly rememberd I don't need to go off argument or battle effect
    //as they all get set to move effect and gbattlescript.moveeffect I can just simply use that
    //and it'll work whether its the effect or argument that sets it initially. *FACEPALM

    /*if (gBattleMoves[gCurrentMove].effect == EFFECT_RECHARGE) 
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN);  may not need as recharge alrady works with 0 effect chance - actually it works because the battlescript already sets it to certain
        yeah don't need because the move effect sets a status and the status is what prevents attack,
        so can safely set dynamic ppunch to recharge and add current effect as augment
        oh wait its focus punch*/

    //trap effects
    if ((gBattleMons[gBattlerTarget].status4 == STATUS4_FIRE_SPIN)
        /*&& ((gBattleMoves[gCurrentMove].effect == EFFECT_BURN_HIT || gBattleMoves[gCurrentMove].effect == EFFECT_SCALD)
        || (gBattleMoves[gCurrentMove].argument == EFFECT_BURN_HIT || gBattleMoves[gCurrentMove].argument == EFFECT_SCALD))*/
        && gBattleScripting.moveEffect == MOVE_EFFECT_BURN)
    {
        percentChance *= 6; //so 60% odds average and guaranteed with sun set

        if (gBattleWeather & WEATHER_SUN_ANY)
        {
            percentChance *= 2;
        } //should make burn guaranteed if also have sun set
        //and yes this is what i had in mind, over sun boosting burn odds globally
           
    }
    //gBattleScripting.moveEffect = (MOVE_EFFECT_CONFUSION | MOVE_EFFECT_CERTAIN);

    if (TestSheerForceFlag(gBattlerAttacker, gCurrentMove))
    {
        gBattleScripting.moveEffect = MOVE_EFFECT_NOTHING_0;
    } //attempt extra protection for sheer force 

    if (gBattleScripting.moveEffect & MOVE_EFFECT_CERTAIN    //believe is like weather, just means its aplying that affect? so this makes it certain
     && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
    {
        gBattleScripting.moveEffect &= ~(MOVE_EFFECT_CERTAIN);
        SetMoveEffect(0, MOVE_EFFECT_CERTAIN);
    }
    else if (Random() % 100 <= percentChance    //random % here, is a chance to fail, higher percent chance less chance to fail, if random higher than moveefect chance doesn't set
          && gBattleScripting.moveEffect         //believe just means and has move effect?  i.e moveeffect not 0
          && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))   //didn't miss && enemy isn't immune
    {
        if (percentChance >= 100)
            SetMoveEffect(0, MOVE_EFFECT_CERTAIN);
        else
            SetMoveEffect(0, 0);
    }
    else //doesn't have move effect  /need double check and make sure two_typed_moves aren't passing type from arguemnt to moveEffect 
    {                                               //argumenttomoveeffect was taking them but I added conditional to exclude it
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    gBattleScripting.moveEffect = 0;
    gBattleScripting.multihitMoveEffect = 0;    //sMULTIHIT_EFFECT believe its this
}

static void atk16_seteffectprimary(void)
{
    SetMoveEffect(TRUE, 0);
}

static void atk17_seteffectsecondary(void)
{
    SetMoveEffect(FALSE, 0);
}

static bool32 TryCheekPouch(u32 battlerId, u32 itemId)
{
    if (ItemId_GetPocket(itemId) == POCKET_BERRY_POUCH //changed name for easier port to firered
        && GetBattlerAbility(battlerId) == ABILITY_CHEEK_POUCH
        && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK)
        && gBattleStruct->ateBerry[GetBattlerSide(battlerId)] & gBitTable[gBattlerPartyIndexes[battlerId]]
        && !BATTLER_MAX_HP(battlerId))
    {
        gBattleMoveDamage = gBattleMons[battlerId].maxHP / 3;
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;
        gBattlerAbility = battlerId;
        BattleScriptPush(gBattlescriptCurrInstr + 2);
        gBattlescriptCurrInstr = BattleScript_CheekPouchActivates;
        return TRUE;
    }
    return FALSE;
}


// Used by Bestow and Symbiosis to take an item from one battler and give to another.
static void BestowItem(u32 battlerAtk, u32 battlerDef)
{
    gLastUsedItem = gBattleMons[battlerAtk].item;

    gActiveBattler = battlerAtk;
    gBattleMons[battlerAtk].item = ITEM_NONE;
    BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[battlerAtk].item), &gBattleMons[battlerAtk].item);
    MarkBattlerForControllerExec(battlerAtk);
    CheckSetUnburden(battlerAtk);

    gActiveBattler = battlerDef;
    gBattleMons[battlerDef].item = gLastUsedItem;
    BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[battlerDef].item), &gBattleMons[battlerDef].item);
    MarkBattlerForControllerExec(battlerDef);
    gBattleResources->flags->flags[battlerDef] &= ~RESOURCE_FLAG_UNBURDEN;
}

#define SYMBIOSIS_CHECK(battler, ally)                                                                                               \
    GetBattlerAbility(ally) == ABILITY_SYMBIOSIS                   \
    && gBattleMons[battler].item == ITEM_NONE                      \
    && gBattleMons[ally].item != ITEM_NONE                         \
    && CanBattlerGetOrLoseItem(battler, gBattleMons[ally].item)    \
    && CanBattlerGetOrLoseItem(ally, gBattleMons[ally].item)       \
    && gBattleMons[battler].hp != 0                                \
    && gBattleMons[ally].hp != 0

// Called by Cmd_removeitem. itemId represents the item that was removed, not being given.
static bool32 TrySymbiosis(u32 battler, u32 itemId)
{
    if (!gBattleStruct->itemStolen[gBattlerPartyIndexes[battler]].stolen
        && gBattleStruct->changedItems[battler] == ITEM_NONE
        && GetBattlerHoldEffect(battler, TRUE) != HOLD_EFFECT_EJECT_BUTTON
        && GetBattlerHoldEffect(battler, TRUE) != HOLD_EFFECT_EJECT_PACK
        && !(gSpecialStatuses[battler].gemBoost)
        && gCurrentMove != MOVE_FLING //Fling and damage-reducing berries are handled separately.
        && !gSpecialStatuses[battler].berryReduced
        && SYMBIOSIS_CHECK(battler, BATTLE_PARTNER(battler)))
    {
        BestowItem(BATTLE_PARTNER(battler), battler);
        gLastUsedAbility = gBattleMons[BATTLE_PARTNER(battler)].ability;
        gBattleScripting.battler = gBattlerAbility = BATTLE_PARTNER(battler);
        gBattlerAttacker = battler;
        BattleScriptPush(gBattlescriptCurrInstr + 2);
        gBattlescriptCurrInstr = BattleScript_SymbiosisActivates;
        return TRUE;
    }
    return FALSE;
}

static void atk18_clearstatusfromeffect(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);

    if (gBattleScripting.moveEffect <= MOVE_EFFECT_TOXIC)
        gBattleMons[gActiveBattler].status1 &= (~sStatusFlagsForMoveEffects[gBattleScripting.moveEffect]);
    else   
    {
        gBattleMons[gActiveBattler].status2 &= (~sStatusFlagsForMoveEffects[gBattleScripting.moveEffect]);
        gBattleMons[gActiveBattler].status4 &= (~sStatusFlagsForMoveEffects[gBattleScripting.moveEffect]);
    }
    gBattleScripting.moveEffect = 0;
    gBattleScripting.multihitMoveEffect = 0;
    gBattlescriptCurrInstr += 2;
    
}

#define NEW_STURDY_EFFECT_PT3
static void atk19_tryfaintmon(void)
{
    CMD_ARGS(u8 battler, bool8 fromSpikes, const u8 *ptr);
    const u8 *BS_ptr;

    if (cmd->fromSpikes != 0)
    {
        gActiveBattler = GetBattlerForBattleScript(cmd->battler);
        if (gHitMarker & HITMARKER_FAINTED(gActiveBattler))  //believe this is for self-faint
        {
            BS_ptr = cmd->ptr;
            BattleScriptPop();
            gBattlescriptCurrInstr = BS_ptr;
            gSideStatuses[GetBattlerSide(gActiveBattler)] &= ~(SIDE_STATUS_SPIKES_DAMAGED | SIDE_STATUS_TOXIC_SPIKES_DAMAGED | SIDE_STATUS_STEALTH_ROCK_DAMAGED | SIDE_STATUS_STICKY_WEB_DAMAGED);
        }
        else //think jump to another instruction
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
    else  //not spikes?  basing off emerald 
    {
        u8 battlerId;

        if (cmd->battler == BS_ATTACKER)
        {
            gActiveBattler = gBattlerAttacker;
            battlerId = gBattlerTarget;
            BS_ptr = BattleScript_FaintAttacker;
        }
        else //if bs not bs attacker 
        {
            gActiveBattler = gBattlerTarget;
            battlerId = gBattlerAttacker;
            BS_ptr = BattleScript_FaintTarget;
        }
        if (!(gAbsentBattlerFlags & gBitTable[gActiveBattler])
         && gBattleMons[gActiveBattler].hp == 0)    //if mon is fainted i.e 0 hp
        {
            gHitMarker |= HITMARKER_FAINTED(gActiveBattler);
            BattleScriptPush(cmd->nextInstr);
            gBattlescriptCurrInstr = BS_ptr;
            if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)// player mon faint
            {
                gHitMarker |= HITMARKER_PLAYER_FAINTED;
                if (gBattleResults.playerFaintCounter < 0xFF)
                    ++gBattleResults.playerFaintCounter;
                AdjustFriendshipOnBattleFaint(gActiveBattler);
                gSideTimers[B_SIDE_PLAYER].retaliateTimer = 2;
            }
            else //enemy side faint
            {
                if (gBattleResults.opponentFaintCounter < 0xFF)
                    ++gBattleResults.opponentFaintCounter;
                gBattleResults.lastOpponentSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_SPECIES);
                *(u8 *)(&gBattleStruct->field_182) = gBattlerAttacker;  //tracks defeated species
                gSideTimers[B_SIDE_OPPONENT].retaliateTimer = 2;
            }
            
            if ((gHitMarker & HITMARKER_DESTINYBOND) && gBattleMons[gBattlerAttacker].hp != 0)
            {
                gHitMarker &= ~(HITMARKER_DESTINYBOND);
                BattleScriptPush(gBattlescriptCurrInstr);
                if (CanSurviveInstantKOWithSturdy(battlerId))
                {
                    gBattleMoveDamage = (gBattleMons[battlerId].hp - 1);//hopefully limits explosion to once per battle for mon whenever special status are cleared in main
                    gSpecialStatuses[battlerId].sturdyhungon = TRUE;
                    gBattlescriptCurrInstr = BattleScript_DestinyBondSturdied; //need test should call sturdymessage
                }
                else
                {
                    gBattleMoveDamage = gBattleMons[battlerId].hp;
                    gBattlescriptCurrInstr = BattleScript_DestinyBondTakesLife;
                }
                    
            }
            if ((gStatuses3[gBattlerTarget] & STATUS3_GRUDGE)
             && !(gHitMarker & HITMARKER_GRUDGE) //unsuire why thsi si here far as I can tell its just skips if other end turn effects are in play?
             && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget)
             && IsBattlerAlive(gBattlerAttacker)
             && gCurrentMove != MOVE_STRUGGLE)
            {
                u8 moveIndex = *(gBattleStruct->chosenMovePositions + gBattlerAttacker);

                gBattleMons[gBattlerAttacker].pp[moveIndex] = 0;
                BattleScriptPush(gBattlescriptCurrInstr);
                gBattlescriptCurrInstr = BattleScript_GrudgeTakesPp; //is only a string, has no funcitonality 
                gActiveBattler = gBattlerAttacker;
                BtlController_EmitSetMonData(0, moveIndex + REQUEST_PPMOVE1_BATTLE, 0, 1, &gBattleMons[gActiveBattler].pp[moveIndex]);
                MarkBattlerForControllerExec(gActiveBattler);
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleMons[gBattlerAttacker].moves[moveIndex])
            }
        }
        else
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
}

static void atk1A_dofaintanimation(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        BtlController_EmitFaintAnimation(0);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 2;
    }
}

static void atk1B_cleareffectsonfaint(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        gBattleMons[gActiveBattler].status1 = 0;
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 0x4, &gBattleMons[gActiveBattler].status1);
        MarkBattlerForControllerExec(gActiveBattler);
        FaintClearSetData(); // Effects like attractions, trapping, etc.
        gBattlescriptCurrInstr += 2;
    }
}

static void atk1C_jumpifstatus(void)
{
    u8 battlerId = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    u32 flags = T2_READ_32(gBattlescriptCurrInstr + 2);
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 6);

    if (gBattleMons[battlerId].status1 & flags && gBattleMons[battlerId].hp != 0)
        gBattlescriptCurrInstr = jumpPtr;
    else
        gBattlescriptCurrInstr += 10;
}

static void atk1D_jumpifstatus2(void)
{
    u8 battlerId = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    u32 flags = T2_READ_32(gBattlescriptCurrInstr + 2);
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 6);

    if (gBattleMons[battlerId].status2 & flags && gBattleMons[battlerId].hp != 0)
        gBattlescriptCurrInstr = jumpPtr;
    else
        gBattlescriptCurrInstr += 10;
}

//sigh ok this was the problem with multitask its still not right, for some reason animation isn't playing
//split into jumpifability and jumpifnotability
static void atk1E_jumpbasedonability(void)
{
    
    CMD_ARGS(u8 battler, u16 ability, u8 jumpCondition, const u8 *jumpInstr);
    u32 battlerId;
    bool32 hasAbility = FALSE;
    u32 ability = cmd->ability;
    //u32 ability = T2_READ_16(gBattlescriptCurrInstr + 2);

    //switch (gBattlescriptCurrInstr[1]) //hodge podge port of rh emerald stuff mixed with vanilla firered macros
        //with adjusted type
    switch (cmd->battler) //change for cmd args update, hope works
    {
    default:
        battlerId = GetBattlerForBattleScript(cmd->battler);

        if (GetBattlerAbility(battlerId) == ability)
        {
            if (ability == ABILITY_MULTI_TASK)
            {
                if (CanMultiTask(gCurrentMove)) //seems to be workign now, but some move animations dont show still investigating
                {
                    hasAbility = TRUE; //if shouldn't multitask will fail to jump to portion that gives moves multi hit effect
                } //only used in, low kick script, and non multihit scripts
                else
                    hasAbility = FALSE;
            }
            else if (ability == ABILITY_CACOPHONY)
            {
                if (gBattleMoves[gCurrentMove].flags & FLAG_SOUND)
                    hasAbility = TRUE;
                else
                    hasAbility = FALSE;
            }
            else if (ability == ABILITY_STURDY)
            {
                if (IsBattlerAlive(battlerId))
                    hasAbility = TRUE;
            }
            else
                hasAbility = TRUE;
        }
        break;
    case BS_ATTACKER_SIDE:
        battlerId = AbilityBattleEffects(ABILITYEFFECT_CHECK_BATTLER_SIDE, gBattlerAttacker, ability, 0, 0);
        if (battlerId)
        {
            --battlerId;
            hasAbility = TRUE;
        }
        break;
    case BS_TARGET_SIDE:
        battlerId = AbilityBattleEffects(ABILITYEFFECT_CHECK_OTHER_SIDE, gBattlerAttacker, ability, 0, 0);
        if (battlerId)
        {
            --battlerId;
            hasAbility = TRUE;
        }
        break;
    }

    if (cmd->jumpCondition == TRUE)// jump if has ability
    {
        if (hasAbility)
        {
            gLastUsedAbility = ability;
            gBattlescriptCurrInstr = cmd->jumpInstr;
            //gBattlescriptCurrInstr = T2_READ_PTR(gBattlescriptCurrInstr + 4);
            RecordAbilityBattle(battlerId, gLastUsedAbility);
            gBattleScripting.battlerWithAbility = battlerId;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
    else if (cmd->jumpCondition == FALSE) //jump if not has ability
    {
        if (!(hasAbility))
        {

            gBattlescriptCurrInstr = cmd->jumpInstr;
            //gBattlescriptCurrInstr = T2_READ_PTR(gBattlescriptCurrInstr + 4);
        }
        else
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
}

static void atk1F_jumpifsideaffecting(void)
{
    CMD_ARGS(u8 battler, u32 sidestatus, const u8 *jumpInstr);
    u8 side;
    u32 sidestatus;
    const u8 *jumpInstr;
    

    if (cmd->battler == BS_ATTACKER)
        side = GET_BATTLER_SIDE(gBattlerAttacker);
    else
        side = GET_BATTLER_SIDE(gBattlerTarget);

    sidestatus = cmd->sidestatus;
    jumpInstr = cmd->jumpInstr;

    if (gSideStatuses[side] & sidestatus)
        gBattlescriptCurrInstr = jumpInstr;
    else
        gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atk20_jumpifstat(void)
{
    u8 ret = 0;
    u8 battlerId = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    u8 value = gBattleMons[battlerId].statStages[gBattlescriptCurrInstr[3]];

    switch (gBattlescriptCurrInstr[2])
    {
    case CMP_EQUAL:
        if (value == gBattlescriptCurrInstr[4])
            ++ret;
        break;
    case CMP_NOT_EQUAL:
        if (value != gBattlescriptCurrInstr[4])
            ++ret;
        break;
    case CMP_GREATER_THAN:
        if (value > gBattlescriptCurrInstr[4])
            ++ret;
        break;
    case CMP_LESS_THAN:
        if (value < gBattlescriptCurrInstr[4])
            ++ret;
        break;
    case CMP_COMMON_BITS:
        if (value & gBattlescriptCurrInstr[4])
            ++ret;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(value & gBattlescriptCurrInstr[4]))
            ++ret;
        break;
    }
    if (ret)
        gBattlescriptCurrInstr = T2_READ_PTR(gBattlescriptCurrInstr + 5);
    else
        gBattlescriptCurrInstr += 9;
}

static void atk21_jumpifstatus3condition(void) //breaks into jumpif, and jump if not
{
    u32 flags;
    const u8 *jumpPtr;

    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    flags = T2_READ_32(gBattlescriptCurrInstr + 2);
    jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 7);
    if (gBattlescriptCurrInstr[6])
    {
        if (gStatuses3[gActiveBattler] & flags)
            gBattlescriptCurrInstr += 11;
        else
            gBattlescriptCurrInstr = jumpPtr;
    }
    else
    {
        if (gStatuses3[gActiveBattler] & flags)
            gBattlescriptCurrInstr = jumpPtr;
        else
            gBattlescriptCurrInstr += 11;
    }
}

/*static void atk22_jumpiftype(void)
{
    u8 battlerId = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    u8 type = gBattlescriptCurrInstr[2];
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 3);

    if (IS_BATTLER_OF_TYPE(battlerId, type))
        gBattlescriptCurrInstr = jumpPtr;
    else
        gBattlescriptCurrInstr += 7;
}*/

static void atk22_jumpbasedontype(void)  //may need to adjust currinstr values
{
    u8 battlerId = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    u8 type = gBattlescriptCurrInstr[2];
    const u8* jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 4);

    // jumpiftype
    if (gBattlescriptCurrInstr[3])  //TRUE
    {
        if (IS_BATTLER_OF_TYPE(battlerId, type))
            gBattlescriptCurrInstr = jumpPtr;
        else
            gBattlescriptCurrInstr += 8;
    }
    // jumpifnottype
    else       //FALSE
    {
        if (!IS_BATTLER_OF_TYPE(battlerId, type))
            gBattlescriptCurrInstr = jumpPtr;
        else
            gBattlescriptCurrInstr += 8;
    }
}

//realized this is woefully in accurate also had old hp scaling in it so was just pattently wrong...
static inline s32  HP_StatRecalc(s32 iv, s32 ev)
{
    s32 level = GetLevelFromMonExp(&gPlayerParty[gBattleStruct->expGetterMonId]);
    u16 species =  GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPECIES, NULL);
    u16 ability = GetMonAbility(&gPlayerParty[gBattleStruct->expGetterMonId]);
    u8 baseStat = gBaseStats[species].baseHP;     
    s32 n;            
    s32 newMaxHP;  

    if (ability == ABILITY_DISPIRIT_GUARD)
        n = 2 * baseStat + ((iv * 160) / 100) + (iv * 2 - ((iv * 120) / 100));
    else
        n = 2 * baseStat + ((iv * 160) / 100) + (iv * 2 - ((iv * 180) / 100)); 

    if (ability == ABILITY_WONDER_GUARD)          
        newMaxHP = 1;
    else if (ability == ABILITY_DISPIRIT_GUARD)
        newMaxHP = (((n + ev / 4) * level) / 100) + level;
    else
        newMaxHP = (((n + ev / 4) * level) / 100) + level + 10;   

    return newMaxHP; 
}

//also had old stat formula...
static inline s32 StatReclacForLevelup(s32 iv, s32 ev, u8 statIndex)
{        
    u8 baseStat;
    s32 n;      
    u8 nature;
    u16 species =  GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPECIES, NULL);
    //this may be part ofthe problem if expgettermonid is not what I thought,
    //and doens't actually hold battlers place in party, cheked it does hold party position
    s32 level = GetLevelFromMonExp(&gPlayerParty[gBattleStruct->expGetterMonId]); 

    switch(statIndex) //beleive using expgettermonId within gbattlemons was wrong, monid isn't battler id trying diff 
    {
        case STAT_ATK:
            baseStat = gBaseStats[species].baseAttack;
            break;
        case STAT_DEF:
            baseStat = gBaseStats[species].baseDefense;
            break;
        case STAT_SPEED:
            baseStat = gBaseStats[species].baseSpeed;
            break;
        case STAT_SPATK:
            baseStat = gBaseStats[species].baseSpAttack;
            break;
        case STAT_SPDEF:
            baseStat = gBaseStats[species].baseSpDefense;
            break;
        
    }

    n = (((2 * baseStat + ((iv * 170) /100) + ev / 4) * level) / 100) + 5;          
    nature = GetNature(&gPlayerParty[gBattleStruct->expGetterMonId]);                
    n = ModifyStatByNature(nature, n, statIndex);                                       
    return n;                                                                           
}


#define EXP_FUNCTION
static void atk23_getexp(void)
{
    CMD_ARGS(u8 battler);
    u16 item;
    s32 i; // also used as stringId
    u8 holdEffect;
    s32 sentIn;
    s32 viaExpShare = 0;
    u16 *exp = &gBattleStruct->expValue;
    u8 *expMonId = &gBattleStruct->expGetterMonId;

    //values for stat recalc for transformed mons level up
    s32 hpIV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HP_IV, NULL);
    s32 hpEV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HP_EV, NULL);
    s32 attackIV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_ATK_IV, NULL);
    s32 attackEV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_ATK_EV, NULL);
    s32 defenseIV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_DEF_IV, NULL);
    s32 defenseEV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_DEF_EV, NULL);
    s32 speedIV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPEED_IV, NULL);
    s32 speedEV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPEED_EV, NULL);
    s32 spAttackIV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPATK_IV, NULL);
    s32 spAttackEV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPATK_EV, NULL);
    s32 spDefenseIV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPDEF_IV, NULL);
    s32 spDefenseEV = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPDEF_EV, NULL);


    gBattlerFainted = GetBattlerForBattleScript(cmd->battler);
    sentIn = gSentPokesToOpponent[(gBattlerFainted & 2) >> 1];
    switch (gBattleScripting.atk23_getexpState)
    {
    case 0: // check if should receive exp at all
        if (GetBattlerSide(gBattlerFainted) != B_SIDE_OPPONENT
         || (gBattleTypeFlags &
            (BATTLE_TYPE_LINK
            | BATTLE_TYPE_TRAINER_TOWER
            | BATTLE_TYPE_BATTLE_TOWER
            | BATTLE_TYPE_SAFARI
            | BATTLE_TYPE_EREADER_TRAINER)))
        {
            gBattleScripting.atk23_getexpState = 6; // goto last case
        }
        else
        {
            ++gBattleScripting.atk23_getexpState;
            gBattleStruct->givenExpMons |= gBitTable[gBattlerPartyIndexes[gBattlerFainted]];
        }
        break;
    case 1: // calculate experience points to redistribute
        {
            u32 calculatedExp;
            s32 viaSentIn;
            u8 expCut = 2;

            //considered addding a max level exclusion for sentin and expshare,
            //but it makes more sense to leave it, tho they don't gain more exp
            //it is taking some of the effort off other mon so makes sense to still count them
            //for the split, hmm but will add make sure mon is not fainted
            //ok hopefully this works
            for (viaSentIn = 0, i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
                {
                        if (gBitTable[i] & sentIn)
                            ++viaSentIn;
                        item = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
                        if (item == ITEM_ENIGMA_BERRY)
                            holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
                        else
                            holdEffect = ItemId_GetHoldEffect(item);
                        if (GetMonData(&gPlayerParty[i], MON_DATA_EXP_SHARE_STATE) == EXP_SHARE
                        && (GetMonData(&gPlayerParty[i], MON_DATA_HP)))
                            ++viaExpShare;
                }
            }
            calculatedExp = gBaseStats[gBattleMons[gBattlerFainted].species].expYield * gBattleMons[gBattlerFainted].level / 7;
            if (viaExpShare) // at least one mon is getting exp via exp share
            {
                //50% split - believe this is portion of exp for sent in mons?
                //not yet sure how to exclude from mon w exp share rn its applied on top if they get sent in
                //ah its applied in case 2, can just add an exception
                //for if not using exp share
                //leaving of for now, but could be done by setting check for usign expshare & sentin w else if
                //but point of sending in an exp share mon is to add extra boost to exp gain
                //and the change I planned (reasigning gexpshareexp if sent in to use viaExpShare rather than the flat 25% cut)
                //could have the effect of zeroeing out the extra exp from exp share
                //ex get 50% from being sent in, but only add 1 exp from exp share because split
                //replaced calculatedExp / 2 for ease of readability
                *exp = ((calculatedExp * 50) / 100) / viaSentIn;
                if (*exp == 0)
                    *exp = 0; // having this be 1 ensures a gain of exp of 1 no matter what. I changed to 0

                //if more than one exp share user caps at 25% exp
                if (viaExpShare > 1)
                    gExpShareExp = ((calculatedExp * 50) / 100) / expCut;
                else
                    gExpShareExp = ((calculatedExp * 50) / 100) / viaExpShare;
                if (gExpShareExp == 0)
                    gExpShareExp = 1;
            }
            else
            {
                *exp = calculatedExp / viaSentIn;
                if (*exp == 0)
                    *exp = 0;
                gExpShareExp = 0;
            }
            ++gBattleScripting.atk23_getexpState;
            gBattleStruct->expGetterMonId = 0;
            gBattleStruct->sentInPokes = sentIn;
        }
        // fall through
    case 2: // set exp value to the poke in expgetter_id and print message
        if (!gBattleControllerExecFlags)
        {
            item = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HELD_ITEM);
            if (item == ITEM_ENIGMA_BERRY)
                holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
            else
                holdEffect = ItemId_GetHoldEffect(item);
            //need identify and set specific case for exp null, for that,
            //block exp skip most logic but still set evs and friendship increase
            //if they were sent in
            //belive translates to, if not sent in and not holding exp share,
            //so what I need is, if sent in, but holding exp null
            if ((GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_EXP_SHARE_STATE) != EXP_SHARE) && !(gBattleStruct->sentInPokes & 1))
            {
                *(&gBattleStruct->sentInPokes) >>= 1;
                gBattleScripting.atk23_getexpState = 5;
                gBattleMoveDamage = 0; // used for exp
            }
            else if (GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_LEVEL) == MAX_LEVEL)
            {
                *(&gBattleStruct->sentInPokes) >>= 1;
                gBattleScripting.atk23_getexpState = 3;  //commented out to remove the jump to case 5. should allow for ev gain at max level
                gBattleMoveDamage = 0; // used for exp // confirmed from Lunos, apparently the case jump only happens after everything in the code block is run so he added the evgain function here and it ran even though it was below the case jump
                MonGainEVs(&gPlayerParty[gBattleStruct->expGetterMonId]);// his method works but not sure if stats will change since think that's in case 3,  so I'm removing the jump and putting ev gain to here.
            } //hopefully this works without issue
            else if (GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_EXP_SHARE_STATE) == EXP_NULL)
            {
                *(&gBattleStruct->sentInPokes) >>= 1;
                gBattleScripting.atk23_getexpState = 3;  //commented out to remove the jump to case 5. should allow for ev gain at max level
                gBattleMoveDamage = 0; // used for exp // confirmed from Lunos, apparently the case jump only happens after everything in the code block is run so he added the evgain function here and it ran even though it was below the case jump
                MonGainEVs(&gPlayerParty[gBattleStruct->expGetterMonId]);// his method works but not sure if stats will change since think that's in case 3,  so I'm removing the jump and putting ev gain to here.
                AdjustFriendship(&gPlayerParty[gBattleStruct->expGetterMonId], FRIENDSHIP_EVENT_EXP_GAINED); //
            } //hopefully this works without issue
            else
            {
                // music change in wild battle after fainting a poke
                if (!(gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_POKEDUDE))
                 && gBattleMons[0].hp
                 && !gBattleStruct->wildVictorySong)
                {
                    BattleStopLowHpSound();
                    PlayBGM(MUS_VICTORY_WILD);
                    ++gBattleStruct->wildVictorySong;
                }
                if (GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HP))
                {
                    //should be able to do streamer/creator mode exp boost here
                    //would be total exp  * multiplier /size of party,
                    //or maybe multiplier will be a switch case determined by party size
                    //that way you boost consistently regardless of team size
                    //again need implement level cap in creator mode
                    //*don't want normal players acceessing this so won't put in options
                    //if they want to play normally in their downtime have interacting with
                    //house gamestation bring up option to toggle creator mode off/on
                    //use flag check created at time of game creation
                    //so even after turning it off,  it can still tell it was a game
                    //created with creator mode in mind
                    if (gBattleStruct->sentInPokes & 1)
                        gBattleMoveDamage = *exp;
                    else
                        gBattleMoveDamage = 0;
                    if (GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_EXP_SHARE_STATE) == EXP_SHARE)
                        gBattleMoveDamage += gExpShareExp;
                    
                    if (holdEffect == HOLD_EFFECT_LUCKY_EGG)
                        gBattleMoveDamage = (gBattleMoveDamage * 150) / 100; //since gBattlemovedamage is *exp, this is for the 1.5 exp boost from lucky egg I can make exp 0 here.
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        gBattleMoveDamage = (gBattleMoveDamage * 150) / 100;
                    if (IsTradedMon(&gPlayerParty[gBattleStruct->expGetterMonId])
                     && !(gBattleTypeFlags & BATTLE_TYPE_POKEDUDE))
                    {
                        gBattleMoveDamage = (gBattleMoveDamage * 150) / 100;
                        i = STRINGID_ABOOSTED;
                    }
                    else
                    {
                        i = STRINGID_EMPTYSTRING4;
                    }
                    // get exp getter battlerId
                    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                    {
                        if (!(gBattlerPartyIndexes[2] != gBattleStruct->expGetterMonId) && !(gAbsentBattlerFlags & gBitTable[2]))
                            gBattleStruct->expGetterBattlerId = 2;
                        else
                        {
                            if (!(gAbsentBattlerFlags & gBitTable[0]))
                                gBattleStruct->expGetterBattlerId = 0;
                            else
                                gBattleStruct->expGetterBattlerId = 2;
                        }
                    }
                    else
                    {
                        gBattleStruct->expGetterBattlerId = 0;
                    }
                    PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattleStruct->expGetterBattlerId, gBattleStruct->expGetterMonId);
                    // buffer 'gained' or 'gained a boosted'
                    PREPARE_STRING_BUFFER(gBattleTextBuff2, i);
                    PREPARE_WORD_NUMBER_BUFFER(gBattleTextBuff3, 5, gBattleMoveDamage);
                    PrepareStringBattle(STRINGID_PKMNGAINEDEXP, gBattleStruct->expGetterBattlerId);
                    MonGainEVs(&gPlayerParty[gBattleStruct->expGetterMonId]);
                    AdjustFriendship(&gPlayerParty[gBattleStruct->expGetterMonId], FRIENDSHIP_EVENT_EXP_GAINED); //apparently friendship calculation doesnt have a filter for if mon is alive
                }//so it triggers regardless,  but putting here ensures that it would only activate if mon is alive,
                gBattleStruct->sentInPokes >>= 1;
                ++gBattleScripting.atk23_getexpState;
            }
        }
        break;
    case 3: // Set stats and give exp
        if (!gBattleControllerExecFlags) //this is what i need to change for transform level up, think can use a version fo calc_stat but just remove set stat part
        {                                           //my species isn't changed with transform so it should properly read the right base stats, so if mew or ditto is using it it'd still work
            gBattleBufferB[gBattleStruct->expGetterBattlerId][0] = 0;
            if (GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HP))// && GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_LEVEL) != MAX_LEVEL)
            { // that and case 2 change were all for ev again/stat change @ level 100, think peak condition/phsycal prime like track stars. they can still get small marginal gains form training
                //or is this all just ev gain and not leve up? or is itboth??
                if (gBattleMons[gBattleStruct->expGetterMonId].status2 & STATUS2_TRANSFORMED)
                {
                    gBattleResources->beforeLvlUp->stats[STAT_HP] = HP_StatRecalc(hpIV, hpEV);
                    gBattleResources->beforeLvlUp->stats[STAT_ATK] = StatReclacForLevelup(attackIV, attackEV, STAT_ATK);
                    gBattleResources->beforeLvlUp->stats[STAT_DEF] = StatReclacForLevelup(defenseIV, defenseEV, STAT_DEF);
                    gBattleResources->beforeLvlUp->stats[STAT_SPEED] = StatReclacForLevelup(speedIV, speedEV, STAT_SPEED);
                    gBattleResources->beforeLvlUp->stats[STAT_SPATK] = StatReclacForLevelup(spAttackIV, spAttackEV, STAT_SPATK);
                    gBattleResources->beforeLvlUp->stats[STAT_SPDEF] = StatReclacForLevelup(spDefenseIV, spDefenseEV, STAT_SPDEF);
                }
                else
                {
                    gBattleResources->beforeLvlUp->stats[STAT_HP] = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_MAX_HP);
                    gBattleResources->beforeLvlUp->stats[STAT_ATK] = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_ATK);
                    gBattleResources->beforeLvlUp->stats[STAT_DEF] = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_DEF);
                    gBattleResources->beforeLvlUp->stats[STAT_SPEED] = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPEED);
                    gBattleResources->beforeLvlUp->stats[STAT_SPATK] = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPATK);
                    gBattleResources->beforeLvlUp->stats[STAT_SPDEF] = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPDEF);
                }
                gActiveBattler = gBattleStruct->expGetterBattlerId;
                BtlController_EmitExpUpdate(0, gBattleStruct->expGetterMonId, gBattleMoveDamage);
                MarkBattlerForControllerExec(gActiveBattler);                
            }
            ++gBattleScripting.atk23_getexpState;
        }
        break;
    case 4: // lvl up if necessary
        if (!gBattleControllerExecFlags)
        {
            gActiveBattler = gBattleStruct->expGetterBattlerId;
            if (gBattleBufferB[gActiveBattler][0] == CONTROLLER_TWORETURNVALUES && gBattleBufferB[gActiveBattler][1] == RET_VALUE_LEVELED_UP)
            {
                u16 temp, battlerId = 0xFF;
                //in single believe gBattleStruct->expGetterBattlerId; will always be 0 or 2", and 0 is player battler
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && gBattlerPartyIndexes[gActiveBattler] == gBattleStruct->expGetterMonId)
                    HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], gActiveBattler);
                PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gActiveBattler, gBattleStruct->expGetterMonId);
                PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff2, 3, GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_LEVEL));
                BattleScriptPushCursor();
                gLeveledUpInBattle |= gBitTable[gBattleStruct->expGetterMonId];
                gBattlescriptCurrInstr = BattleScript_LevelUp;
                gBattleMoveDamage = (gBattleBufferB[gActiveBattler][2] | (gBattleBufferB[gActiveBattler][3] << 8));
                AdjustFriendship(&gPlayerParty[gBattleStruct->expGetterMonId], FRIENDSHIP_EVENT_GROW_LEVEL);
                // update battle mon structure after level up
                //according to bulbapedia transformed stats are only recalced on levelup up to gen3
                //so I should probably add a value here to exclude transformed mon
                if (gBattlerPartyIndexes[0] == gBattleStruct->expGetterMonId && gBattleMons[0].hp
                && !gBattleMons[0].status2 & STATUS2_TRANSFORMED)
                {
                    gBattleMons[0].level = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_LEVEL);
                    gBattleMons[0].hp = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HP);
                    gBattleMons[0].maxHP = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_MAX_HP);
                    gBattleMons[0].attack = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_ATK);
                    gBattleMons[0].defense = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_DEF);
                    // Why is this duplicated?
                    //gBattleMons[0].speed = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPEED);
                    gBattleMons[0].speed = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPEED);
                    gBattleMons[0].spAttack = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPATK);
                    gBattleMons[0].spDefense = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPDEF);
                }
                // What is else if?     fixed speed dup, & sp def exclusion
                if (gBattlerPartyIndexes[2] == gBattleStruct->expGetterMonId && gBattleMons[2].hp 
                && !gBattleMons[2].status2 & STATUS2_TRANSFORMED && (gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
                {
                    gBattleMons[2].level = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_LEVEL);
                    gBattleMons[2].hp = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_HP);
                    gBattleMons[2].maxHP = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_MAX_HP);
                    gBattleMons[2].attack = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_ATK);
                    gBattleMons[2].defense = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_DEF);
                    // Duplicated again, but this time there's no Sp Defense
                    gBattleMons[2].speed = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPEED);
                    gBattleMons[2].spDefense = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPDEF);
                    gBattleMons[2].spAttack = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPATK);

                    //if (gStatuses3[battlerId] & STATUS3_POWER_TRICK)
                      //  SWAP(gBattleMons[battlerId].attack, gBattleMons[battlerId].defense, temp);
                }
                gBattleScripting.atk23_getexpState = 5;
            }
            else
            {
                gBattleMoveDamage = 0;
                gBattleScripting.atk23_getexpState = 5;
            }
        }
        break;
    case 5: // looper increment /TRY DO for pokedex & evo setup   //can't remember plan for that?
        if (gBattleMoveDamage) // there is exp to give, goto case 3 that gives exp
        {
            gBattleScripting.atk23_getexpState = 3;
        }
        else
        {
            ++gBattleStruct->expGetterMonId;
            if (gBattleStruct->expGetterMonId < PARTY_SIZE) // this is a mon id, so I believe this just says check every pokemon in party
                gBattleScripting.atk23_getexpState = 2; // loop again
            else
                gBattleScripting.atk23_getexpState = 6; // we're done
        }
        break;
    case 6: // increment instruction
        if (!gBattleControllerExecFlags)
        {
            // not sure why gf clears the item and ability here
            gBattleMons[gBattlerFainted].item = ITEM_NONE;
            gBattleMons[gBattlerFainted].ability = ABILITY_NONE;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        break;
    }
}

// For battles that aren't BATTLE_TYPE_LINK or BATTLE_TYPE_RECORDED_LINK, the only thing this
// command does is check whether the player has won/lost by totaling each team's HP. 
//It then sets gBattleOutcome accordingly, if necessary.
static void atk24_confirmlosingteam(void)
{
    CMD_ARGS(const u8 *jumpInstr);
    u16 HP_count = 0;
    s32 i;

    if (!gBattleControllerExecFlags)
    {
        for (i = 0; i < PARTY_SIZE; ++i)
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
                HP_count += GetMonData(&gPlayerParty[i], MON_DATA_HP);
        if (HP_count == 0)
            gBattleOutcome |= B_OUTCOME_LOST;
        for (HP_count = 0, i = 0; i < PARTY_SIZE; ++i)
            if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES) && !GetMonData(&gEnemyParty[i], MON_DATA_IS_EGG))
                HP_count += GetMonData(&gEnemyParty[i], MON_DATA_HP);
        if (HP_count == 0)
            gBattleOutcome |= B_OUTCOME_WON;
        if (gBattleOutcome == 0 && (gBattleTypeFlags & BATTLE_TYPE_LINK))
        {
            s32 foundPlayer;
            s32 foundOpponent;

            for (foundPlayer = 0, i = 0; i < gBattlersCount; i += 2)
            {
                u32 *ptr = &gHitMarker;
                u32 hitMarkerUnk = 0x10000000;
                
                ++i;
                --i;
                if ((hitMarkerUnk << i) & *ptr && !gSpecialStatuses[i].faintedHasReplacement)
                    ++foundPlayer;
            }
            for (foundOpponent = 0, i = 1; i < gBattlersCount; i += 2)
            {
                u32 *ptr = &gHitMarker;
                u32 hitMarkerUnk = 0x10000000;
                
                {
                    u8 match;

                    ++match;
                    --match;
                }
                if ((hitMarkerUnk << i) & *ptr && !gSpecialStatuses[i].faintedHasReplacement)
                    ++foundOpponent;
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                if (foundOpponent + foundPlayer > 1)
                     gBattlescriptCurrInstr = cmd->jumpInstr;
                else
                    gBattlescriptCurrInstr = cmd->nextInstr;
            }
            else
            {
                if (foundOpponent != 0 && foundPlayer != 0)
                    gBattlescriptCurrInstr = cmd->jumpInstr;
                else
                    gBattlescriptCurrInstr = cmd->nextInstr;
            }
        }
        else
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
}

static void MoveValuesCleanUp(void)
{
    gMoveResultFlags = 0;
    //gBattleScripting.dmgMultiplier = 1;
    gCritMultiplier = 1;
    gBattleScripting.moveEffect = 0;
    gBattleCommunication[6] = 0;
    gHitMarker &= ~(HITMARKER_DESTINYBOND);
    gHitMarker &= ~(HITMARKER_SYNCHRONIZE_EFFECT);

}

static void atk25_movevaluescleanup(void)
{
    MoveValuesCleanUp();
    gBattlescriptCurrInstr += 1;
}

static void atk26_setmultihit(void) //for now still used, for pursuit dmg
{
    gMultiHitCounter = gBattlescriptCurrInstr[1];
    gBattlescriptCurrInstr += 2;
}

static void atk27_decrementmultihit(void)
{
    if (--gMultiHitCounter == 0)
        gBattlescriptCurrInstr += 5;
    else
        gBattlescriptCurrInstr = T2_READ_PTR(gBattlescriptCurrInstr + 1);
}

static void atk28_goto(void)
{
    gBattlescriptCurrInstr = T2_READ_PTR(gBattlescriptCurrInstr + 1);
}

static void atk29_jumpifbyte(void)
{
    u8 caseID = gBattlescriptCurrInstr[1];
    const u8 *memByte = T2_READ_PTR(gBattlescriptCurrInstr + 2);
    u8 value = gBattlescriptCurrInstr[6];
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 7);

    gBattlescriptCurrInstr += 11;

    switch (caseID)
    {
    case CMP_EQUAL:
        if (*memByte == value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_NOT_EQUAL:
        if (*memByte != value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_GREATER_THAN:
        if (*memByte > value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_LESS_THAN:
        if (*memByte < value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_COMMON_BITS:
        if (*memByte & value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(*memByte & value))
            gBattlescriptCurrInstr = jumpPtr;
        break;
    }
}

static void atk2A_jumpifhalfword(void)
{
    u8 caseID = gBattlescriptCurrInstr[1];
    const u16 *memHword = T2_READ_PTR(gBattlescriptCurrInstr + 2);
    u16 value = T2_READ_16(gBattlescriptCurrInstr + 6);
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 8);

    gBattlescriptCurrInstr += 12;
    switch (caseID)
    {
    case CMP_EQUAL:
        if (*memHword == value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_NOT_EQUAL:
        if (*memHword != value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_GREATER_THAN:
        if (*memHword > value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_LESS_THAN:
        if (*memHword < value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_COMMON_BITS:
        if (*memHword & value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(*memHword & value))
            gBattlescriptCurrInstr = jumpPtr;
        break;
    }
}

static void atk2B_jumpifword(void)
{
    u8 caseID = gBattlescriptCurrInstr[1];
    const u32 *memWord = T2_READ_PTR(gBattlescriptCurrInstr + 2);
    u32 value = T1_READ_32(gBattlescriptCurrInstr + 6);
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 10);

    gBattlescriptCurrInstr += 14;
    switch (caseID)
    {
    case CMP_EQUAL:
        if (*memWord == value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_NOT_EQUAL:
        if (*memWord != value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_GREATER_THAN:
        if (*memWord > value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_LESS_THAN:
        if (*memWord < value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_COMMON_BITS:
        if (*memWord & value)
            gBattlescriptCurrInstr = jumpPtr;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(*memWord & value))
            gBattlescriptCurrInstr = jumpPtr;
        break;
    }
}

static void atk2C_jumpifarrayequal(void)
{
    const u8 *mem1 = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    const u8 *mem2 = T2_READ_PTR(gBattlescriptCurrInstr + 5);
    u32 size = gBattlescriptCurrInstr[9];
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 10);
    u8 i;

    for (i = 0; i < size; ++i)
    {
        if (*mem1 != *mem2)
        {
            gBattlescriptCurrInstr += 14;
            break;
        }
        ++mem1, ++mem2;
    }
    if (i == size)
        gBattlescriptCurrInstr = jumpPtr;
}

static void atk2D_jumpifarraynotequal(void)
{
    u8 equalBytes = 0;
    const u8 *mem1 = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    const u8 *mem2 = T2_READ_PTR(gBattlescriptCurrInstr + 5);
    u32 size = gBattlescriptCurrInstr[9];
    const u8 *jumpPtr = T2_READ_PTR(gBattlescriptCurrInstr + 10);
    u8 i;

    for (i = 0; i < size; ++i)
    {
        if (*mem1 == *mem2)
            ++equalBytes;
        ++mem1, ++mem2;
    }
    if (equalBytes != size)
        gBattlescriptCurrInstr = jumpPtr;
    else
        gBattlescriptCurrInstr += 14;
}

static void atk2E_setbyte(void)
{
    u8 *memByte = T2_READ_PTR(gBattlescriptCurrInstr + 1);

    *memByte = gBattlescriptCurrInstr[5];
    gBattlescriptCurrInstr += 6;
}

static void atk2F_addbyte(void)
{
    u8 *memByte = T2_READ_PTR(gBattlescriptCurrInstr + 1);

    *memByte += gBattlescriptCurrInstr[5];
    gBattlescriptCurrInstr += 6;
}

static void atk30_subbyte(void)
{
    u8 *memByte = T2_READ_PTR(gBattlescriptCurrInstr + 1);

    *memByte -= gBattlescriptCurrInstr[5];
    gBattlescriptCurrInstr += 6;
}

static void atk31_copyarray(void)
{
    u8 *dest = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    const u8 *src = T2_READ_PTR(gBattlescriptCurrInstr + 5);
    s32 size = gBattlescriptCurrInstr[9];
    s32 i;

    for (i = 0; i < size; ++i)
    {
        dest[i] = src[i];
    }
    gBattlescriptCurrInstr += 10;
}

static void atk32_copyarraywithindex(void)
{
    u8 *dest = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    const u8 *src = T2_READ_PTR(gBattlescriptCurrInstr + 5);
    const u8 *index = T2_READ_PTR(gBattlescriptCurrInstr + 9);
    s32 size = gBattlescriptCurrInstr[13];
    s32 i;

    for (i = 0; i < size; ++i)
    {
        dest[i] = src[i + *index];
    }
    gBattlescriptCurrInstr += 14;
}

static void atk33_orbyte(void)
{
    u8 *memByte = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    *memByte |= gBattlescriptCurrInstr[5];
    gBattlescriptCurrInstr += 6;
}

static void atk34_orhalfword(void)
{
    u16 *memHword = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    u16 val = T2_READ_16(gBattlescriptCurrInstr + 5);

    *memHword |= val;
    gBattlescriptCurrInstr += 7;
}

static void atk35_orword(void)
{
    u32 *memWord = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    u32 val = T2_READ_32(gBattlescriptCurrInstr + 5);

    *memWord |= val;
    gBattlescriptCurrInstr += 9;
}

static void atk36_bicbyte(void)
{
    u8 *memByte = T2_READ_PTR(gBattlescriptCurrInstr + 1);

    *memByte &= ~(gBattlescriptCurrInstr[5]);
    gBattlescriptCurrInstr += 6;
}

static void atk37_bichalfword(void)
{
    u16 *memHword = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    u16 val = T2_READ_16(gBattlescriptCurrInstr + 5);

    *memHword &= ~val;
    gBattlescriptCurrInstr += 7;
}

static void atk38_bicword(void)
{
    u32 *memWord = T2_READ_PTR(gBattlescriptCurrInstr + 1);
    u32 val = T2_READ_32(gBattlescriptCurrInstr + 5);

    *memWord &= ~val;
    gBattlescriptCurrInstr += 9;
}

//if I changed this to check array which returned actually pause value
//I could link it to text speed, so pause time is shorter
//would be simple as making array gPauseValue and putting
//what gets assigned to value in that
//gPauseValue(T2_READ_16(gBattlescriptCurrInstr + 1))
//and change the values in the sript to be values of array i.e 0-last value
//wher highest is shortest time
//would just need check if text speed is greater than fast, 
//and value does not equal last value instruct
//vsonic IMPORTANT
//will do this, just need replace all pause values with the constants


 // can use this as example, but replace stringIds on right with actual pause time
//ok tested and it works
static void atk39_pause(void) 
{
    if (!gBattleControllerExecFlags)
    {
        u8 BattleSpeed = GetBattleSpeedOption();
        u16 value = T2_READ_16(gBattlescriptCurrInstr + 1);

        //with increasd speed work backwards from limit,
        //i.e when using +1 the limit is wait time briefest,
        //when using +2, I need to start one level back
        if (BattleSpeed > OPTIONS_BATTLE_SPEED_1X)
        {
            if (gSaveBlock2Ptr->optionsBattleSceneOff == TRUE)
                BattleSpeed = OPTIONS_BATTLE_SPEED_2X;

            value += SetPauseTimeModifier(BattleSpeed, value); //use switch case
        }
            
            
        if (++gPauseCounterBattle >= gPauseValue[value]) //how is this working with values that don't fit into array i.e aren't set w buffers?
        {
            gPauseCounterBattle = 0;
            gBattlescriptCurrInstr += 3;
        }
    }
}

//decided handle separately wait time unique and long long are only used by waitmessage not pause
static u8 SetPauseTimeModifier(u8 BattleSpeed, u16 value)
{

    switch (BattleSpeed) 
    {
        case OPTIONS_BATTLE_SPEED_1X:
            return 0; //don't change wait time
        break;
        case OPTIONS_BATTLE_SPEED_2X: //this seems to be fine
        if (value < B_WAIT_TIME_BRIEFEST)
            return BattleSpeed;
        else
            return 0; //don't change wait time
        break;
        case OPTIONS_BATTLE_SPEED_3X:
        if (value < B_WAIT_TIME_SHORTEST) //plan do else if, w bs - 1 for values above cutoff
            return BattleSpeed;
        else if (value < B_WAIT_TIME_CLEAR_BUFF) //B_WAIT_TIME_CLEAR_BUFF
            return BattleSpeed - 1;
        else
            return 0; //don't change wait time
        break;
        case OPTIONS_BATTLE_SPEED_4X: 
        //if (value < B_WAIT_TIME_SHORT) //plan do else if, w bs - 1 for values above cutoff
        //   return BattleSpeed;
        if (value == B_WAIT_TIME_LONG)
            return BattleSpeed - 2;
        //else if (value < B_WAIT_TIME_CLEAR_BUFF) //using this means briefest uses 0x5 instead of 0x7, so slightly faster
        //    return BattleSpeed - 2;
        else
            return 0; //don't change wait time
        break;
    }
}

//rather than try negative just add \p  to certain strings
//don't want to miss,can just A press through it simple enough
static s8 SetWaitTimeModifier(u8 BattleSpeed, u16 value) 
{

    switch (BattleSpeed) //only unique & LongLong & Longest are assigning
    {
        case OPTIONS_BATTLE_SPEED_1X:
        if (value == B_WAIT_TIME_UNIQUE)
            return value;
        else if (value == B_WAIT_TIME_LONG_LONG)
            return B_WAIT_TIME_CLEAR_BUFF_2;
        else if (value == B_WAIT_TIME_IMPORTANT_STRINGS)
            return B_WAIT_TIME_LONG;
        else
            return 0; //don't change wait time
        break;
        case OPTIONS_BATTLE_SPEED_2X: //this seems to be fine
        if (value < B_WAIT_TIME_BRIEFEST)
            return 1;
        else if (value == B_WAIT_TIME_UNIQUE)
            return B_WAIT_TIME_SHORT;
        else if (value == B_WAIT_TIME_LONG_LONG)
            return B_WAIT_TIME_MED;
        else if (value == B_WAIT_TIME_IMPORTANT_STRINGS && GetPlayerTextSpeed() > OPTIONS_TEXT_SPEED_FAST)
            return B_WAIT_TIME_LONG;
        else if (value == B_WAIT_TIME_IMPORTANT_STRINGS)
            return B_WAIT_TIME_MED;
        else
            return 0; //don't change wait time
        break;
        case OPTIONS_BATTLE_SPEED_3X:
        
        if (value == B_WAIT_TIME_SHORT && GetPlayerTextSpeed() > OPTIONS_TEXT_SPEED_MID) //plan do else if, w bs - 1 for values above cutoff
           return 6; //turn short into long long
        else if (value == B_WAIT_TIME_IMPORTANT_STRINGS && GetPlayerTextSpeed() < OPTIONS_TEXT_SPEED_FAST)
            return B_WAIT_TIME_LONG;
        else if (value < B_WAIT_TIME_SHORT) //put here w else if means for lower text speeds
            return 1;
        //else if (value < B_WAIT_TIME_CLEAR_BUFF) //B_WAIT_TIME_CLEAR_BUFF
        //    return 0;
        else if (value == B_WAIT_TIME_UNIQUE)
            return value;
        else if (value == B_WAIT_TIME_LONG_LONG || B_WAIT_TIME_IMPORTANT_STRINGS)
            return value;
        else
            return 0; //don't change wait time
        break;
        case OPTIONS_BATTLE_SPEED_4X: 
        if (value == B_WAIT_TIME_SHORT && GetPlayerTextSpeed() > OPTIONS_TEXT_SPEED_MID) //plan do else if, w bs - 1 for values above cutoff
           return 6; //turn short into long long - works
        else if (value == B_WAIT_TIME_IMPORTANT_STRINGS && GetPlayerTextSpeed() < OPTIONS_TEXT_SPEED_FAST)
            return B_WAIT_TIME_LONG;
        //if (value == B_WAIT_TIME_LONG)
        //    return BattleSpeed - 2;
        //else if (value < B_WAIT_TIME_CLEAR_BUFF) //using this means briefest uses 0x5 instead of 0x7, so slightly faster
        //    return BattleSpeed - 2;
        else if (value == B_WAIT_TIME_UNIQUE)
            return value;
        else if (value == B_WAIT_TIME_LONG_LONG || B_WAIT_TIME_IMPORTANT_STRINGS)
            return value;
        else
            return 0; //don't change wait time
        break;
    }
}

static void atk3A_waitstate(void)
{
    if (!gBattleControllerExecFlags)
        ++gBattlescriptCurrInstr;
}

static void atk3B_healthbar_update(void)
{
    if (gBattlescriptCurrInstr[1] == BS_TARGET)
        gActiveBattler = gBattlerTarget;
    else
        gActiveBattler = gBattlerAttacker;
    BtlController_EmitHealthBarUpdate(0, gBattleMoveDamage);
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 2;
}

static void atk3C_return(void)
{
    BattleScriptPop();
}

static void atk3D_end(void)
{
    gMoveResultFlags = 0;
    gActiveBattler = 0;
    gCurrentActionFuncId = B_ACTION_TRY_FINISH;
}

static void atk3E_end2(void)
{
    gActiveBattler = 0;
    gCurrentActionFuncId = B_ACTION_TRY_FINISH;
}

static void atk3F_end3(void) // pops the main function stack
{
    BattleScriptPop();
    if (gBattleResources->battleCallbackStack->size != 0)
        gBattleResources->battleCallbackStack->size--;
    gBattleMainFunc = gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size];
}

static void atk41_call(void)
{
    BattleScriptPush(gBattlescriptCurrInstr + 5);
    gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
}

static void atk42_missinghealthtoDmg(void) //replaced was no longer needed, was jumpiftype2 to use put before damagecalc
{
    if (gBattleMoves[gCurrentMove].effect == EFFECT_FINAL_GAMBIT)   //decided to use move power for this, can use move damage for else if/others
    { 
        gBattleMovePower = (gBattleMons[gBattlerAttacker].maxHP - gBattleMons[gBattlerAttacker].hp);
        gBattleMovePower = (gBattleMovePower * 120) /100;   //since not using movedamage, and faint as result give extra boost
            ++gBattlescriptCurrInstr;
    }
    else
        ++gBattlescriptCurrInstr;
}

static void atk43_jumpifabilitypresent(void)
{
    if (AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, T1_READ_16(gBattlescriptCurrInstr + 1), 0, 0))
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 3);
    else
        gBattlescriptCurrInstr += 7;
}

static void atk44_endselectionscript(void)
{
    *(gBattlerAttacker + gBattleStruct->selectionScriptFinished) = TRUE;
}

static void atk45_playanimation(void)
{
    const u16 *argumentPtr;

    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    argumentPtr = T2_READ_PTR(gBattlescriptCurrInstr + 3);
    if (gBattlescriptCurrInstr[2] == B_ANIM_STATS_CHANGE
     || gBattlescriptCurrInstr[2] == B_ANIM_SNATCH_MOVE
     || gBattlescriptCurrInstr[2] == B_ANIM_SUBSTITUTE_FADE
     || gBattlescriptCurrInstr[2] == B_ANIM_SILPH_SCOPED)
    {
        BtlController_EmitBattleAnimation(0, gBattlescriptCurrInstr[2], *argumentPtr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 7;
    }
    else if (gHitMarker & HITMARKER_NO_ANIMATIONS)
    {
        BattleScriptPush(gBattlescriptCurrInstr + 7);
        gBattlescriptCurrInstr = BattleScript_Pausex20;
    }
    else if (gBattlescriptCurrInstr[2] == B_ANIM_RAIN_CONTINUES
          || gBattlescriptCurrInstr[2] == B_ANIM_SUN_CONTINUES
          || gBattlescriptCurrInstr[2] == B_ANIM_SANDSTORM_CONTINUES
          || gBattlescriptCurrInstr[2] == B_ANIM_HAIL_CONTINUES)
    {
        BtlController_EmitBattleAnimation(0, gBattlescriptCurrInstr[2], *argumentPtr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 7;
    }
    else if (gStatuses3[gActiveBattler] & STATUS3_SEMI_INVULNERABLE)
    {
        gBattlescriptCurrInstr += 7;
    }
    else
    {
        BtlController_EmitBattleAnimation(0, gBattlescriptCurrInstr[2], *argumentPtr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 7;
    }
}

static void atk46_playanimation2(void) // animation Id is stored in the first pointer
{
    const u16 *argumentPtr;
    const u8 *animationIdPtr;

    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    animationIdPtr = T2_READ_PTR(gBattlescriptCurrInstr + 2);
    argumentPtr = T2_READ_PTR(gBattlescriptCurrInstr + 6);
    if (*animationIdPtr == B_ANIM_STATS_CHANGE
     || *animationIdPtr == B_ANIM_SNATCH_MOVE
     || *animationIdPtr == B_ANIM_SUBSTITUTE_FADE)
    {
        BtlController_EmitBattleAnimation(0, *animationIdPtr, *argumentPtr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 10;
    }
    else if (gHitMarker & HITMARKER_NO_ANIMATIONS)
    {
        gBattlescriptCurrInstr += 10;
    }
    else if (*animationIdPtr == B_ANIM_RAIN_CONTINUES
          || *animationIdPtr == B_ANIM_SUN_CONTINUES
          || *animationIdPtr == B_ANIM_SANDSTORM_CONTINUES
          || *animationIdPtr == B_ANIM_HAIL_CONTINUES)
    {
        BtlController_EmitBattleAnimation(0, *animationIdPtr, *argumentPtr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 10;
    }
    else if (gStatuses3[gActiveBattler] & STATUS3_SEMI_INVULNERABLE)
    {
        gBattlescriptCurrInstr += 10;
    }
    else
    {
        BtlController_EmitBattleAnimation(0, *animationIdPtr, *argumentPtr);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 10;
    }
}

static void atk47_setgraphicalstatchangevalues(void)    //may need change this too since stat buffs go up to +-3 in later gen
{
    // don't know if need default from emerald or not
    u8 value = GET_STAT_BUFF_VALUE_WITH_SIGN(gBattleScripting.statChanger);

    switch (value)
    {
    case SET_STAT_BUFF_VALUE(1): // +1
        value = STAT_ANIM_PLUS1;
        break;
    case SET_STAT_BUFF_VALUE(2): // +2
        value = STAT_ANIM_PLUS2;
        break;
    case SET_STAT_BUFF_VALUE(3): // +3
        value = STAT_ANIM_PLUS2;
        break;
    case SET_STAT_BUFF_VALUE(1) | STAT_BUFF_NEGATIVE: // -1
        value = STAT_ANIM_MINUS1;
        break;
    case SET_STAT_BUFF_VALUE(2) | STAT_BUFF_NEGATIVE: // -2
        value = STAT_ANIM_MINUS2;
        break;
    case SET_STAT_BUFF_VALUE(3) | STAT_BUFF_NEGATIVE: // -3
        value = STAT_ANIM_MINUS2;
        break;
    default: // <-12,-4> and <4, 12>
        if (value & STAT_BUFF_NEGATIVE)
            value = STAT_ANIM_MINUS2 + 1;
        else
            value = STAT_ANIM_PLUS2 + 1;
        break;
    }
    gBattleScripting.animArg1 = GET_STAT_BUFF_ID(gBattleScripting.statChanger) + value - 1;
    gBattleScripting.animArg2 = 0;
    ++gBattlescriptCurrInstr;
}

#define STAT_ANIM_W_ABILITIES
static void atk48_playstatchangeanimation(void)
{
    u32 ability;
    u32 currStat = 0;
    u16 statAnimId = 0;
    s32 changeableStatsCount = 0;
    u8 statsToCheck = 0;
    u8 flags;

    ability = GetBattlerAbility(gActiveBattler);
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    statsToCheck = gBattlescriptCurrInstr[2];
    flags = gBattlescriptCurrInstr[3];

    // Handle Contrary and Simple
    if (ability == ABILITY_CONTRARY)
        flags ^= STAT_ANIM_MINUS1;
    else if (ability == ABILITY_SIMPLE)
        flags |= STAT_CHANGE_STAT_BY_TWO;

    if (flags & STAT_CHANGE_STAT_NEGATIVE) // goes down
    {
        s16 startingStatAnimId;
        if (flags & STAT_CHANGE_STAT_BY_TWO)
            startingStatAnimId = STAT_ANIM_MINUS2 - 1;
        else
            startingStatAnimId = STAT_ANIM_MINUS1 - 1;

        while (statsToCheck != 0)
        {
            if (statsToCheck & 1)
            {
                if (flags & STAT_CHANGE_DONT_CHECK_LOWER)
                {
                    if (gBattleMons[gActiveBattler].statStages[currStat] > 0)
                    {
                        statAnimId = startingStatAnimId + currStat;
                        ++changeableStatsCount;
                    }
                }
                else if ((!gSideTimers[GET_BATTLER_SIDE(gActiveBattler)].mistTimer
                        || (!IsBlackFogNotOnField() && gSideTimers[GET_BATTLER_SIDE(gActiveBattler)].mistTimer))
                        && ability != ABILITY_CLEAR_BODY
                        && ability != ABILITY_LEAF_GUARD
                        && ability != ABILITY_FULL_METAL_BODY
                        && ability != ABILITY_WHITE_SMOKE
                        && ability != ABILITY_LIQUID_METAL
                        && !(ability == ABILITY_KEEN_EYE && currStat == STAT_ACC)
                        && !(ability == ABILITY_SIXTH_SENSE && currStat == STAT_ACC)
                        && !(ability == ABILITY_TANGLED_FEET && currStat == STAT_SPEED)
                        && !(ability == ABILITY_QUICK_FEET && currStat == STAT_SPEED)
                        && !(ability == ABILITY_AVIATOR && currStat == STAT_SPEED)
                        && !(ability == ABILITY_RUN_AWAY && currStat == STAT_SPEED)
                        && !(ability == ABILITY_HYPER_CUTTER && currStat == STAT_ATK)
                        && !(ability == ABILITY_BIG_PECKS && currStat == STAT_ATK)
                        && !(ability == ABILITY_BIG_PECKS && currStat == STAT_DEF)
                        && !IsFlowerVeilProtected(gActiveBattler))
                {
                    if (gBattleMons[gActiveBattler].statStages[currStat] > 0)
                    {
                        statAnimId = startingStatAnimId + currStat;
                        ++changeableStatsCount;
                    }
                }
            }
            statsToCheck >>= 1; //this is correct
            ++currStat;
        }

        if (changeableStatsCount > 1) // more than one stat, so the color is gray
        {
            if (flags & STAT_CHANGE_STAT_BY_TWO)
                statAnimId = STAT_ANIM_MULTIPLE_MINUS2;
            else
                statAnimId = STAT_ANIM_MULTIPLE_MINUS1;
        }
    }
    else // goes up
    {
        s16 startingStatAnimId;
        if (flags & STAT_CHANGE_STAT_BY_TWO)
            startingStatAnimId = STAT_ANIM_PLUS2 - 1;
        else
            startingStatAnimId = STAT_ANIM_PLUS1 - 1;

        while (statsToCheck != 0)
        {
            if (statsToCheck & 1 && gBattleMons[gActiveBattler].statStages[currStat] < 0xC)
            {
                statAnimId = startingStatAnimId + currStat;
                ++changeableStatsCount;
            }
            statsToCheck >>= 1;
            ++currStat;
        }
        if (changeableStatsCount > 1) // more than one stat, so the color is gray
        {
            if (flags & STAT_CHANGE_STAT_BY_TWO)
                statAnimId = STAT_ANIM_MULTIPLE_PLUS2;
            else
                statAnimId = STAT_ANIM_MULTIPLE_PLUS1;
        }
    }
    if (flags & STAT_CHANGE_ONLY_MULTIPLE && changeableStatsCount < 2)
    {
        gBattlescriptCurrInstr += 4;
    }
    else if (changeableStatsCount != 0 && !gBattleScripting.statAnimPlayed)
    {
        BtlController_EmitBattleAnimation(0, B_ANIM_STATS_CHANGE, statAnimId);
        MarkBattlerForControllerExec(gActiveBattler);
        if (flags & STAT_CHANGE_ONLY_MULTIPLE && changeableStatsCount > 1)
            gBattleScripting.statAnimPlayed = TRUE;
        gBattlescriptCurrInstr += 4;
    }
    else
    {
        gBattlescriptCurrInstr += 4;
    }
}


static u32 GetNextTarget(u32 moveTarget)
{
    u32 i;
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (i != gBattlerAttacker
            && IsBattlerAlive(i)
            && !(gBattleStruct->targetsDone[gBattlerAttacker] & gBitTable[i])
            && (GetBattlerSide(i) != GetBattlerSide(gBattlerAttacker) || moveTarget == MOVE_TARGET_FOES_AND_ALLY))
            break;
    }
    return i;
}

#define ATK_49_MOVEEND
static void atk49_moveend(void) //need to update this //equivalent Cmd_moveend  //vsonic IMPORTANT
{
    CMD_ARGS(u8 endMode, u8 endState);  //filled in missing values and put in order of constants file 

    s32 i;
    bool32 effect = FALSE;
    u8 moveType = 0;
    u8 holdEffectAtk = 0;
    u16 *choicedMoveAtk = NULL;
    u8 endMode, endState; //renamed for compatibility with emerald
    u16 originallyUsedMove; //need reordere cases below

    if (gChosenMove == MOVE_UNAVAILABLE)
        originallyUsedMove = MOVE_NONE;
    else
        originallyUsedMove = gChosenMove;
    endMode = cmd->endMode;
    endState = cmd->endState;
    if (gBattleMons[gBattlerAttacker].item == ITEM_ENIGMA_BERRY)
        holdEffectAtk = gEnigmaBerries[gBattlerAttacker].holdEffect;
    else
        holdEffectAtk = GetBattlerHoldEffect(gBattlerAttacker, TRUE);
    choicedMoveAtk = &gBattleStruct->choicedMove[gBattlerAttacker];
    GET_MOVE_TYPE(gCurrentMove, moveType);
    do //comb function, and check for any custom effecst
    {// otherwise safe to completely replace with emerald function
        //will require transfrerring bs_commands.h constants file move end values as well. 
        switch (gBattleScripting.atk49_state) //order is mostly the same, just starts with protectlike effects instead of rage
        {   //realiz order does matter as this is the order effects will take place - matters for the cases themselves, and the order of effects within the case
        case MOVE_END_PROTECT_LIKE_EFFECT:
            if (gProtectStructs[gBattlerAttacker].touchedProtectLike)
            {
                if (gProtectStructs[gBattlerTarget].spikyShielded)
                {
                    
                    if (GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD) //dmg & spikes
                    {
                        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_SPIKE_SHIELD);//move change mostly works except spikes are set on wrong side with bs commad
                        BattleScriptPushCursor(); //trysetspikes  need swap sides of argumen    //think done?, tested and worked in emerald
                        gBattlescriptCurrInstr = BattleScript_SpikyShieldEffect;
                        effect = 1;
                    }
                    else //no dmg just spikes
                    {
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_SetSpikesfromSpikyShield;
                        effect = 1;
                    }
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE; //think need to put at end since set spikes requires this to be true
                }
                else if (gProtectStructs[gBattlerTarget].shieldBashed && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD)
                {
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE;
                    if (!(gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)) //use wonder guard effect logic to help here pretty much long as not super effective do counter damage
                    {
                        gBattleMoveDamage = (gBattleMons[gBattlerTarget].defense / 2); //should be damgage is 1/2 target defense
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_SHIELD_BASH);
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_ShieldBash;//needs animation  //done -make better eventually
                        effect = 1;
                    }
                    /*else if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE) //should do what i want
                    {
                        ++gBattleScripting.atk49_state;
                        break;
                    }*/  //having this broke things so removed, for some reason non damaging moves were being caught i.e growl
                }
                else if (gProtectStructs[gBattlerTarget].kingsShielded)
                {
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE;
                    i = gBattlerAttacker;
                    gBattlerAttacker = gBattlerTarget;
                    gBattlerTarget = i; // gBattlerTarget and gBattlerAttacker are swapped in order to activate Defiant, if applicable
                    gBattleScripting.moveEffect = MOVE_EFFECT_ATK_MINUS_1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_KingsShieldEffect;
                    effect = 1;
                }
                else if (gProtectStructs[gBattlerTarget].banefulBunkered)
                {
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE;
                    gBattleScripting.moveEffect = MOVE_EFFECT_POISON | MOVE_EFFECT_AFFECTS_USER;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_BANEFUL_BUNKER);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BanefulBunkerEffect;
                    effect = 1;
                }
                else if (gProtectStructs[gBattlerTarget].obstructed && gCurrentMove != MOVE_SUCKER_PUNCH)
                {
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE;
                    i = gBattlerAttacker;
                    gBattlerAttacker = gBattlerTarget;
                    gBattlerTarget = i; // gBattlerTarget and gBattlerAttacker are swapped in order to activate Defiant, if applicable
                    gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_2;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_KingsShieldEffect;
                    effect = 1;
                }
                else if (gProtectStructs[gBattlerTarget].silkTrapped)
                {
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE;
                    i = gBattlerAttacker;
                    gBattlerAttacker = gBattlerTarget;
                    gBattlerTarget = i; // gBattlerTarget and gBattlerAttacker are swapped in order to activate Defiant, if applicable
                    gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_KingsShieldEffect;
                    effect = 1;
                }
                // Not strictly a protect effect, but works the same way
                else if (gProtectStructs[gBattlerTarget].beakBlastCharge
                    && CanBeBurned(gBattlerAttacker)
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
                {
                    gProtectStructs[gBattlerAttacker].touchedProtectLike = FALSE;
                    gBattleMons[gBattlerAttacker].status1 = STATUS1_BURN;
                    gActiveBattler = gBattlerAttacker;
                    BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, sizeof(gBattleMons[gActiveBattler].status1), &gBattleMons[gActiveBattler].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                    BattleScriptPushCursor();
                   // gBattlescriptCurrInstr = BattleScript_BeakBlastBurn;  vsonic  need add updated gen 8 stuff
                    effect = 1;
                }

            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_RAGE: // rage check
            if (gBattleMons[gBattlerTarget].status2 & STATUS2_RAGE
             && gBattleMons[gBattlerTarget].hp != 0
             //&& gBattlerAttacker != gBattlerTarget //may remove this, would let confusion hits count for rage building, realistic and double edge balance
             && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget) //keep this wouldn't want to just attack your own mon in doubles 
             && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
             && TARGET_TURN_DAMAGED
             && gBattleMoves[gCurrentMove].power
             && IsBlackFogNotOnField()
             && gBattleMons[gBattlerTarget].statStages[STAT_ATK] < MAX_STAT_STAGE)    //not max atk
            {
                if (gDisableStructs[gBattlerAttacker].rageCounter != 5)
                    gDisableStructs[gBattlerAttacker].rageCounter++;
                ++gBattleMons[gBattlerTarget].statStages[STAT_ATK];
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_RageIsBuilding;
                effect = TRUE;
            }
            /*else if (gBattleMons[gBattlerAttacker].status2 & STATUS2_RAGE //would be any time miss, with ANY attack, so don't really want that
            && gBattleMoves[gCurrentMove].power
            && (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)) //think changing to put w attack cancelers so freeze, sleep paralysis spirit lock pressure & think flinch
            {
                ClearRageStatuses();
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_RageEnds; //tested and works, just need make message
                effect = TRUE;
            } //so removing this, and putting in canclers instead  */
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_ROOST:
            if (gDisableStructs[gBattlerAttacker].RoostTimer == 4)
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_Roosting;
                effect = TRUE;
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_DEFROST: // defrosting/thaw check //for target 
            if (gBattleMons[gBattlerTarget].status1 & STATUS1_FREEZE
             && gBattleMons[gBattlerTarget].hp != 0
             && gBattleMoveDamage != 0 // test to see if this works right. should be all damaging fire moves above 60 power can defrost.
             && gBattlerAttacker != gBattlerTarget
             && TARGET_TURN_DAMAGED
             && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
             && !(gHitMarker & HITMARKER_UNABLE_TO_USE_MOVE) //logic from canceler fix thaw bug
             && (CanThaw(gCurrentMove))) //test vsonic
            {
                gBattleMons[gBattlerTarget].status1 &= ~(STATUS1_FREEZE);
                gActiveBattler = gBattlerTarget;
                BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gBattlerTarget].status1);
                MarkBattlerForControllerExec(gActiveBattler);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_DefrostedViaFireMove;
                effect = TRUE;
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_SYNCHRONIZE_TARGET: // target synchronize
            if (AbilityBattleEffects(ABILITYEFFECT_SYNCHRONIZE, gBattlerTarget, 0, 0, 0))
                effect = TRUE;
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_MOVE_END_ABILITIES: // Such as abilities activating on contact(Poison Spore, Rough Skin, etc.).
            if (AbilityBattleEffects(ABILITYEFFECT_MOVE_END, gBattlerTarget, 0, 0, 0))// "calls" function, which checks if things can activate, and returns effect+ making it true
                effect = TRUE;
            ++gBattleScripting.atk49_state;
            break;
         case MOVE_END_ABILITIES_ATTACKER: // Poison Touch, possibly other in the future
            if (AbilityBattleEffects(ABILITYEFFECT_MOVE_END_ATTACKER, gBattlerAttacker, 0, 0, 0))
                effect = TRUE;
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_STATUS_IMMUNITY_ABILITIES: // status immunities
            if (AbilityBattleEffects(ABILITYEFFECT_IMMUNITY, 0, 0, 0, 0))
                effect = TRUE; // it loops through all battlers, so we increment after its done with all battlers
            else
                ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_SYNCHRONIZE_ATTACKER: // attacker synchronize
            if (AbilityBattleEffects(ABILITYEFFECT_ATK_SYNCHRONIZE, gBattlerAttacker, 0, 0, 0))
                effect = TRUE;
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_CHOICE_MOVE: // update choice band move
            if (gHitMarker & HITMARKER_OBEYS //need updat ai file prob replace with emerald expansion ai files
             && (holdEffectAtk == HOLD_EFFECT_CHOICE_BAND || GetBattlerAbility(gBattlerAttacker) == ABILITY_GORILLA_TACTICS)
             && gChosenMove != MOVE_STRUGGLE 
             && (*choicedMoveAtk == 0 || *choicedMoveAtk == 0xFFFF))
            {
                if (gChosenMove == MOVE_BATON_PASS && !(gMoveResultFlags & MOVE_RESULT_FAILED))
                {
                    ++gBattleScripting.atk49_state;
                    break;
                }
                *choicedMoveAtk = gChosenMove;
            }
            for (i = 0; i < MAX_MON_MOVES; ++i)
            {
                if (gBattleMons[gBattlerAttacker].moves[i] == *choicedMoveAtk)
                    break;
            }
            if (i == MAX_MON_MOVES)
                *choicedMoveAtk = 0;
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_CHANGED_ITEMS: // changed held items
            for (i = 0; i < gBattlersCount; ++i)
            {
                u16 *changedItem = &gBattleStruct->changedItems[i];
                
                if (*changedItem != ITEM_NONE)
                {
                    gBattleMons[i].item = *changedItem;
                    *changedItem = ITEM_NONE;
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_ATTACKER_INVISIBLE: // make attacker sprite invisible
            if (gStatuses3[gBattlerAttacker] & (STATUS3_SEMI_INVULNERABLE)
             && gHitMarker & HITMARKER_NO_ANIMATIONS)
            {
                gActiveBattler = gBattlerAttacker;
                BtlController_EmitSpriteInvisibility(0, TRUE);
                MarkBattlerForControllerExec(gActiveBattler);
                ++gBattleScripting.atk49_state;
                return;
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_ATTACKER_VISIBLE: // make attacker sprite visible
            if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT
             || !(gStatuses3[gBattlerAttacker] & (STATUS3_SEMI_INVULNERABLE))
             || WasUnableToUseMove(gBattlerAttacker))
            {
                gActiveBattler = gBattlerAttacker;
                BtlController_EmitSpriteInvisibility(0, FALSE);
                MarkBattlerForControllerExec(gActiveBattler);
                gStatuses3[gBattlerAttacker] &= ~(STATUS3_SEMI_INVULNERABLE);
                gSpecialStatuses[gBattlerAttacker].restoredBattlerSprite = 1;
                ++gBattleScripting.atk49_state;
                return;
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_TARGET_VISIBLE: // make target sprite visible
            if (!gSpecialStatuses[gBattlerTarget].restoredBattlerSprite
             && gBattlerTarget < gBattlersCount
             && !(gStatuses3[gBattlerTarget] & STATUS3_SEMI_INVULNERABLE))
            {
                gActiveBattler = gBattlerTarget;
                BtlController_EmitSpriteInvisibility(0, FALSE);
                MarkBattlerForControllerExec(gActiveBattler);
                gStatuses3[gBattlerTarget] &= ~(STATUS3_SEMI_INVULNERABLE);
                ++gBattleScripting.atk49_state;
                return;
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_ITEM_EFFECTS_TARGET:
            if (ItemBattleEffects(ITEMEFFECT_TARGET, gBattlerTarget, FALSE))
                effect = TRUE;
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_MOVE_EFFECTS2: // For effects which should happen after target items, for example Knock Off after damage from Rocky Helmet.
        {
            switch (gBattleStruct->moveEffect2)
            {
            case MOVE_EFFECT_KNOCK_OFF:
                effect = TryKnockOffBattleScript(gBattlerTarget, gBattlerAttacker, gBattleStruct->moveEffect2);
                break;
            /*case MOVE_EFFECT_SMACK_DOWN: //remove this instead do in MOVE_END_GROUND_TARGET
                if (!(IsBattlerGrounded(gBattlerTarget)) && IsBattlerAlive(gBattlerTarget))
                {
                    gStatuses3[gBattlerTarget] |= STATUS3_SMACKED_DOWN;
                    gStatuses3[gBattlerTarget] &= ~(STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS | STATUS3_ON_AIR);
                    effect = TRUE;
                    BattleScriptPush(gBattlescriptCurrInstr);
                    gBattlescriptCurrInstr = BattleScript_MoveEffectSmackDown;
                }
                break;*/
            case MOVE_EFFECT_REMOVE_STATUS: // Smelling salts, Wake-Up Slap, Sparkling Aria
                if ((gBattleMons[gBattlerTarget].status1 & gBattleMoves[gCurrentMove].argument) && IsBattlerAlive(gBattlerTarget))
                {
                    gBattleMons[gBattlerTarget].status1 &= ~(gBattleMoves[gCurrentMove].argument);

                    gActiveBattler = gBattlerTarget;
                    BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                    effect = TRUE;
                    BattleScriptPush(gBattlescriptCurrInstr);
                    switch (gBattleMoves[gCurrentMove].argument)
                    {
                    case STATUS1_PARALYSIS:
                        gBattlescriptCurrInstr = BattleScript_TargetPRLZHeal;
                        break;
                    case STATUS1_SLEEP:
                        gBattlescriptCurrInstr = BattleScript_TargetWokeUp;
                        break;
                    case STATUS1_BURN:
                        gBattlescriptCurrInstr = BattleScript_TargetBurnHeal;
                        break;
                    }
                }
                break; // MOVE_EFFECT_REMOVE_STATUS
            }
            gBattleStruct->moveEffect2 = 0;
            ++gBattleScripting.atk49_state;
            break; // MOVEEND_MOVE_EFFECTS2
        }
        case MOVE_END_ITEM_EFFECTS_ALL: // item effects for all battlers
            if (ItemBattleEffects(ITEMEFFECT_MOVE_END, 0, FALSE))
                effect = TRUE;
            else
                ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_KINGSROCK: // king's rock and shell bell
            if (ItemBattleEffects(ITEMEFFECT_KINGSROCK, 0, FALSE))  //with change to item effect to be just kingsrock look into if I need to change mov end
                effect = TRUE;  //yes change this to only kingsrock 
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_SUBSTITUTE: // update substitute
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gDisableStructs[i].substituteHP == 0)
                    gBattleMons[i].status2 &= ~(STATUS2_SUBSTITUTE);
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_GROUND_TARGET: //for some reason retriggering so think, grounded isn't being set right?
            if (!IsBattlerGrounded(gBattlerTarget) 
            && IsBattlerAlive(gBattlerTarget) //not working at all for some reason
            //&& gMultiHitCounter == 0  //removing this line seemed to fix issue of not dispalying, didn't need as should only trigger if 0/move complete
            && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && TARGET_TURN_DAMAGED)// !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)) //should make sure doesn't trigger till end of multihit
            {           //result no effect didn't work so replace w target must take dmg
                //double checked and EE uses them together for some reason
                if (((gBattleMoves[gCurrentMove].flags & FLAG_DMG_IN_AIR) && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR)
                || ((gBattleMoves[gCurrentMove].flags & FLAG_DMG_2X_IN_AIR) && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR))   //using fly
                {
                    CancelMultiTurnMoves(gBattlerTarget); //just for fly /skydrop
                    gSprites[gBattlerSpriteIds[gBattlerTarget]].invisible = FALSE;
                    //gStatuses3[gActiveBattler] &= ~(STATUS3_ON_AIR); // doesn't need this part handled in cancelmultiturn
                    gStatuses3[gBattlerTarget] |= STATUS3_SMACKED_DOWN;
                    gStatuses3[gBattlerTarget] &= ~(STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS | STATUS3_ON_AIR); //think need these, were part of smack down
                    effect = TRUE;
                    BattleScriptPush(gBattlescriptCurrInstr);
                    gBattlescriptCurrInstr = BattleScript_GroundFlyingEnemywithoutGravity;

                }//NEW bs for   //didnt need move damage multiplier that's already accounted for by damage calc

                else if ((gBattleMoves[gCurrentMove].flags & FLAG_DMG_IN_AIR)
                || (gBattleMoves[gCurrentMove].flags & FLAG_DMG_2X_IN_AIR)) //redid thnik tryign bitwise stuff was why this at times failed to set grounding
                {
                    gStatuses3[gBattlerTarget] |= STATUS3_SMACKED_DOWN;
                    gStatuses3[gBattlerTarget] &= ~(STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS | STATUS3_ON_AIR);
                    effect = TRUE;
                    BattleScriptPush(gBattlescriptCurrInstr);
                    gBattlescriptCurrInstr = BattleScript_MoveEffectSmackDown; //just a battle message
                }//for some reason seems doesn't always work?,idk what's going on with this thing...
                

                //I "think" this will work? //vsonic IMPORTANT...completey forgot I did this
                //if paralysis is in grounded function may not need set smacked down here
                else if (gBattleScripting.moveEffect == MOVE_EFFECT_PARALYSIS
                && !(gStatuses3[gBattlerTarget] & STATUS3_SMACKED_DOWN)
                && !gBattleMons[gBattlerTarget].status1 & STATUS1_SLEEP
                )
                {
                    gStatuses3[gBattlerTarget] |= STATUS3_SMACKED_DOWN;
                    gStatuses3[gBattlerTarget] &= ~(STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS | STATUS3_ON_AIR); //think need these, were part of smack down
                    effect = TRUE;
                    BattleScriptPush(gBattlescriptCurrInstr);
                    gBattlescriptCurrInstr = BattleScript_GroundFlyingEnemywithStatus;
                }

                else if (gBattleScripting.moveEffect == MOVE_EFFECT_SLEEP
                && !(gStatuses3[gBattlerTarget] & STATUS3_SMACKED_DOWN)
                && !gBattleMons[gBattlerTarget].status1 & STATUS1_PARALYSIS)
                {
                    gStatuses3[gBattlerTarget] |= STATUS3_SMACKED_DOWN;
                    gStatuses3[gBattlerTarget] &= ~(STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS | STATUS3_ON_AIR); //think need these, were part of smack down
                    effect = TRUE;
                    BattleScriptPush(gBattlescriptCurrInstr);
                    gBattlescriptCurrInstr = BattleScript_GroundFlyingEnemywithStatus;
                } //need makes its own script, too exchausted to fly

            } //vsonic need test
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_SKY_DROP_CONFUSE: // If a Pokemon was released from Sky Drop and was in LOCK_CONFUSE, go to "confused due to fatigue" scripts and clear Sky Drop data.
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gBattleStruct->skyDropTargets[i] == 0xFE)
                {
                    u8 targetId;
                    // Find the battler id of the Pokemon that was held by Sky Drop
                    for (targetId = 0; targetId < gBattlersCount; targetId++)
                    {
                        if (gBattleStruct->skyDropTargets[targetId] == i)
                            break;
                    }

                    // Set gBattlerAttacker to the battler id of the target
                    gBattlerAttacker = targetId;

                    // Jump to "confused due to fatigue" script
                    gBattlescriptCurrInstr = BattleScript_ThrashConfuses;

                    // Clear skyDropTargets data
                    gBattleStruct->skyDropTargets[i] = 0xFF;
                    gBattleStruct->skyDropTargets[targetId] = 0xFF;
                    return;
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_UPDATE_LAST_MOVES:
            if ((gMoveResultFlags & (MOVE_RESULT_FAILED | MOVE_RESULT_DOESNT_AFFECT_FOE))
             || (gBattleMons[gBattlerAttacker].status2 & (STATUS2_FLINCHED))
             || gProtectStructs[gBattlerAttacker].prlzImmobility)
                gBattleStruct->lastMoveFailed |= gBitTable[gBattlerAttacker];
            else
                gBattleStruct->lastMoveFailed &= ~(gBitTable[gBattlerAttacker]);

            // Set ShellTrap to activate after the attacker's turn if target was hit by a physical move.
            if (gBattleMoves[gChosenMoveByBattler[gBattlerTarget]].effect == EFFECT_SHELL_TRAP
                && gBattlerTarget != gBattlerAttacker
                && GetBattlerSide(gBattlerTarget) != GetBattlerSide(gBattlerAttacker)
                && gProtectStructs[gBattlerTarget].physicalDmg
                && gProtectStructs[gBattlerTarget].physicalBattlerId == gBattlerAttacker
                && !TestSheerForceFlag(gBattlerAttacker, gCurrentMove))
            {
                gProtectStructs[gBattlerTarget].shellTrap = TRUE;
                // Change move order in double battles, so the hit mon with shell trap moves immediately after being hit.
                if (IsDoubleBattle())
                {
                    ChangeOrderTargetAfterAttacker();
                }
            }


            if (gHitMarker & HITMARKER_SWAP_ATTACKER_TARGET)
            {
                gActiveBattler = gBattlerAttacker;
                gBattlerAttacker = gBattlerTarget;
                gBattlerTarget = gActiveBattler;
                gHitMarker &= ~(HITMARKER_SWAP_ATTACKER_TARGET);
            }
            if (!gSpecialStatuses[gBattlerAttacker].dancerUsedMove)//ported need check
            {
                gDisableStructs[gBattlerAttacker].usedMoves |= gBitTable[gCurrMovePos];
                gBattleStruct->lastMoveTarget[gBattlerAttacker] = gBattlerTarget;
                if (gHitMarker & HITMARKER_ATTACKSTRING_PRINTED)
                {
                    gLastPrintedMoves[gBattlerAttacker] = gChosenMove;
                    gLastUsedMove = gCurrentMove;
                }
            }

            if (!(gAbsentBattlerFlags & gBitTable[gBattlerAttacker])
             && !(gBattleStruct->absentBattlerFlags & gBitTable[gBattlerAttacker])
             && gBattleMoves[originallyUsedMove].effect != EFFECT_HEALING_WISH
             && gBattleMoves[originallyUsedMove].effect != EFFECT_BATON_PASS)
            {
                if (gHitMarker & HITMARKER_OBEYS)
                {
                    gLastMoves[gBattlerAttacker] = gChosenMove;
                    gLastResultingMoves[gBattlerAttacker] = gCurrentMove;
                }
                else
                {
                    gLastMoves[gBattlerAttacker] = 0xFFFF;
                    gLastResultingMoves[gBattlerAttacker] = 0xFFFF;
                }

                if (!(gHitMarker & HITMARKER_FAINTED(gBattlerTarget)))
                    gLastHitBy[gBattlerTarget] = gBattlerAttacker;

                if (gHitMarker & HITMARKER_OBEYS && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
                {
                    if (gChosenMove == 0xFFFF)
                    {
                        gLastLandedMoves[gBattlerTarget] = gChosenMove;
                    }
                    else
                    {
                        gLastLandedMoves[gBattlerTarget] = gCurrentMove;
                        GET_MOVE_TYPE(gCurrentMove, gLastHitByType[gBattlerTarget]);
                    }
                }
                else
                {
                    gLastLandedMoves[gBattlerTarget] = 0xFFFF;
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_MIRROR_MOVE: // mirror move
            if (!(gAbsentBattlerFlags & gBitTable[gBattlerAttacker])
             && !(gBattleStruct->absentBattlerFlags & gBitTable[gBattlerAttacker])
             && gBattleMoves[originallyUsedMove].flags & FLAG_MIRROR_MOVE_AFFECTED
             && gHitMarker & HITMARKER_OBEYS
             && gBattlerAttacker != gBattlerTarget
             && !(gHitMarker & HITMARKER_FAINTED(gBattlerTarget))
             && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
            {
                gBattleStruct->lastTakenMove[gBattlerTarget] = gChosenMove;
                gBattleStruct->lastTakenMoveFrom[gBattlerTarget][gBattlerAttacker] = gChosenMove;
            }
            ++gBattleScripting.atk49_state;
            break;
        /*case MOVE_END_NEXT_TARGET: // For moves hitting two opposing Pokemon.
            if (!(gHitMarker & HITMARKER_UNABLE_TO_USE_MOVE)
             && gBattleTypeFlags & BATTLE_TYPE_DOUBLE
             && !gProtectStructs[gBattlerAttacker].chargingTurn
             && gBattleMoves[gCurrentMove].target == MOVE_TARGET_BOTH
             && !(gHitMarker & HITMARKER_NO_ATTACKSTRING))
            {
                u8 battlerId = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
                if (gBattleMons[battlerId].hp != 0)
                {
                    gBattlerTarget = battlerId;
                    gHitMarker |= HITMARKER_NO_ATTACKSTRING;
                    gBattleScripting.atk49_state = 0;
                    MoveValuesCleanUp();
                    BattleScriptPush(gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect]);
                    gBattlescriptCurrInstr = BattleScript_FlushMessageBox;
                    return;
                }
                else
                {
                    gHitMarker |= HITMARKER_NO_ATTACKSTRING;
                }
            }
            ++gBattleScripting.atk49_state;
            break;*/
        
        case MOVE_END_MULTIHIT_MOVE:
        {
           /* if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && !(gHitMarker & HITMARKER_UNABLE_TO_USE_MOVE)
            && gMultiHitCounter
            && !(gCurrentMove == MOVE_PRESENT && gBattleStruct->presentBasePower == 0)) // Silly edge case
            {
                gBattleScripting.multihitString[4]++;
                if (--gMultiHitCounter == 0)
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MultiHitPrintStrings;
                    effect = TRUE;
                }
                else
                {
                    if (gCurrentMove == MOVE_DRAGON_DARTS)  //vsonic
                    {
                        // TODO
                    }

                    if (gBattleMons[gBattlerAttacker].hp
                    && gBattleMons[gBattlerTarget].hp
                    && (gChosenMove == MOVE_SLEEP_TALK || !(gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP))
                    && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE))
                    {
                        if (gSpecialStatuses[gBattlerAttacker].parentalBondState)
                            gSpecialStatuses[gBattlerAttacker].parentalBondState--;

                        gHitMarker |= (HITMARKER_NO_PPDEDUCT | HITMARKER_NO_ATTACKSTRING);
                        gBattleScripting.animTargetsHit = 0;
                        gBattleScripting.atk49_state = 0;
                        gSpecialStatuses[gBattlerTarget].sturdied = 0;  //forgto this wasn't a gen3 affect, it didn't do this til gen 5 o.0
                        gSpecialStatuses[gBattlerTarget].focusBanded = 0; // Delete this line to make Focus Band last for the duration of the whole move turn.
                        gSpecialStatuses[gBattlerTarget].focusSashed = 0; // Delete this line to make Focus Sash last for the duration of the whole move turn.
   //this line may be issue makes sure hit    gSpecialStatuses[gBattlerAttacker].multiHitOn = TRUE;
                        MoveValuesCleanUp();
                        BattleScriptPush(gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect]);
                        gBattlescriptCurrInstr = BattleScript_FlushMessageBox;
                        return;
                    }
                    else
                    {
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_MultiHitPrintStrings;
                        effect = TRUE;
                    }
                }
            }
            gMultiHitCounter = 0;
            gSpecialStatuses[gBattlerAttacker].parentalBondState = PARENTAL_BOND_OFF;
            gSpecialStatuses[gBattlerAttacker].multiHitOn = 0;*/
            //gMultiHitCounter = 0;  //removing from acc check didn't undo issue so is it somehow this? yup this was the problem
            ++gBattleScripting.atk49_state;
            break;
        }
        case MOVE_END_MAGICIAN:    //this and pickpocket should go in abilityeffects function instead, this should only be for   actual move effect only, think wil move the item stuff recently ported from emerald out too
            if (GetBattlerAbility(gBattlerAttacker) == ABILITY_MAGICIAN
                && gCurrentMove != MOVE_FLING && gCurrentMove != MOVE_NATURAL_GIFT
                && gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[gBattlerAttacker]][GetBattlerSide(gBattlerAttacker)] == ITEM_NONE
                && gBattleMons[gBattlerTarget].item != ITEM_NONE
                && IsBattlerAlive(gBattlerAttacker)
                && TARGET_TURN_DAMAGED
                //&& CanStealItem(gBattlerAttacker, gBattlerTarget, gBattleMons[gBattlerTarget].item)
                && !gSpecialStatuses[gBattlerAttacker].gemBoost   // In base game, gems are consumed after magician would activate.
                && !(gWishFutureKnock.knockedOffMons[GetBattlerSide(gBattlerTarget)] & gBitTable[gBattlerPartyIndexes[gBattlerTarget]])
                && !DoesSubstituteBlockMove(gBattlerAttacker, gBattlerTarget, gCurrentMove)
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && (GetBattlerAbility(gBattlerTarget) != ABILITY_STICKY_HOLD || !IsBattlerAlive(gBattlerTarget)))
            {
                StealTargetItem(gBattlerAttacker, gBattlerTarget);
                gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_MagicianActivates;
                effect = TRUE;
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_EJECT_BUTTON:    //think move to itemeffects function, no this is how it is seteup in emerald too
        {
            if (gBattleMoves[gCurrentMove].effect != EFFECT_HIT_SWITCH_TARGET
                && IsBattlerAlive(gBattlerAttacker)
                //&& !TestSheerForceFlag(gBattlerAttacker, gCurrentMove)    removed sheerforce logic as I'm convinced that's just anothr bug
                && (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER || (gBattleTypeFlags & BATTLE_TYPE_TRAINER)))
            {
                // Since we check if battler was damaged, we don't need to check move result.
                // In fact, doing so actually prevents multi-target moves from activating eject button properly
                u8 battlers[4] = { 0, 1, 2, 3 };
                SortBattlersBySpeed(battlers, FALSE);
                for (i = 0; i < gBattlersCount; i++)
                {
                    u8 battler = battlers[i];
                    // Attacker is the damage-dealer, battler is mon to be switched out
                    if (IsBattlerAlive(battler)
                        && GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EJECT_BUTTON
                        && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                        && (gSpecialStatuses[battler].physicalDmg != 0 || gSpecialStatuses[battler].specialDmg != 0))
                        //&& CountUsablePartyMons(battler) > 0)  // Has mon to switch into / also part of ai updatee can prob replace w somethin else? chck if has alive mon in party not in first slot i.e 0 party index vsonic
                    {
                        gActiveBattler = gBattleScripting.battler = battler;
                        gLastUsedItem = gBattleMons[battler].item;
                        if (gBattleMoves[gCurrentMove].effect == EFFECT_HIT_ESCAPE)
                            gBattlescriptCurrInstr = BattleScript_MoveEnd;  // Prevent user switch-in selection
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_EjectButtonActivates;
                        effect = TRUE;
                        break; // Only the fastest Eject Button activates
                    }
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        }
        case MOVE_END_RED_CARD:    //think move to itemeffects function
        {
            if (gBattleMoves[gCurrentMove].effect != EFFECT_HIT_SWITCH_TARGET
                && IsBattlerAlive(gBattlerAttacker))
                //&& !TestSheerForceFlag(gBattlerAttacker, gCurrentMove))
                //&& GetBattlerAbility(gBattlerAttacker) != ABILITY_GUARD_DOG)
            {
                // Since we check if battler was damaged, we don't need to check move result.
                // In fact, doing so actually prevents multi-target moves from activating red card properly
                u8 battlers[4] = { 0, 1, 2, 3 };
                    SortBattlersBySpeed(battlers, FALSE);
                    for (i = 0; i < gBattlersCount; i++)
                    {
                        u8 battler = battlers[i];
                        // Search for fastest hit pokemon with a red card
                        // Attacker is the one to be switched out, battler is one with red card
                        if (battler != gBattlerAttacker
                            && IsBattlerAlive(battler)
                            && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                            && GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_RED_CARD
                            && (gSpecialStatuses[battler].physicalDmg != 0 || gSpecialStatuses[battler].specialDmg != 0)
                            && CanBattlerSwitch(gBattlerAttacker))
                        {
                            gLastUsedItem = gBattleMons[battler].item;
                            gActiveBattler = gBattleStruct->savedBattlerTarget = gBattleScripting.battler = battler;  // Battler with red card
                            gEffectBattler = gBattlerAttacker;
                            if (gBattleMoves[gCurrentMove].effect == EFFECT_HIT_ESCAPE)
                                gBattlescriptCurrInstr = BattleScript_MoveEnd;  // Prevent user switch-in selection
                            BattleScriptPushCursor();
                            gBattlescriptCurrInstr = BattleScript_RedCardActivates;
                            effect = TRUE;
                            break;  // Only fastest red card activates
                        }
                    }
            }
            ++gBattleScripting.atk49_state;
            break;
        }
        case MOVE_END_EJECT_PACK:  //think move to item effects function
            {
                u8 battlers[4] = {0, 1, 2, 3};
                SortBattlersBySpeed(battlers, FALSE);
                for (i = 0; i < gBattlersCount; i++)
                {
                    u8 battler = battlers[i];
                    if (IsBattlerAlive(battler)
                     //&& gProtectStructs[battler].statFell     Vsonic  potentially replace w gSpecialStatuses[battler].statLowered
                     && gProtectStructs[battler].disableEjectPack == 0
                     && GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EJECT_PACK
                     && !(gCurrentMove == MOVE_PARTING_SHOT && CanBattlerSwitch(gBattlerAttacker)))  // Does not activate if attacker used Parting Shot and can switch out
                     //&& CountUsablePartyMons(battler) > 0)  // Has mon to switch into / also part of ai updatee can prob replace w somethin else? chck if has alive mon in party not in first slot i.e 0 party index vsonic
                    {
                        //gProtectStructs[battler].statFell = FALSE;
                        gActiveBattler = gBattleScripting.battler = battler;
                        gLastUsedItem = gBattleMons[battler].item;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_EjectPackActivates;
                        effect = TRUE;
                        break;  // Only fastest eject pack activates
                    }
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_LIFEORB_SHELLBELL:
            if (ItemBattleEffects(ITEMEFFECT_LIFEORB_SHELLBELL, 0, FALSE))
                effect = TRUE;
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_PICKPOCKET:  //looks clunky, think they had troble setting up will attempt to do it better (uncommented in case that was issue, still must revamp)
            if (IsBattlerAlive(gBattlerAttacker)
              && gBattleMons[gBattlerAttacker].item != ITEM_NONE        // Attacker must be holding an item
              && !(gWishFutureKnock.knockedOffMons[GetBattlerSide(gBattlerAttacker)] & gBitTable[gBattlerPartyIndexes[gBattlerAttacker]])   // But not knocked off
              && !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove))  // Pickpocket doesn't activate for sheer force
              && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)    // Pickpocket requires contact
              && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))           // Obviously attack needs to have worked
            {
                u8 battlers[4] = {0, 1, 2, 3};
                SortBattlersBySpeed(battlers, FALSE); //If multiple Pok�mon with this Ability are hit by the same move that made contact,
                for (i = 0; i < gBattlersCount; i++)//Pickpocket will activate for the fastest one that does not already have an item.
                {
                    u8 battler = battlers[i];
                    // Attacker is mon who made contact, battler is mon with pickpocket
                    if (battler != gBattlerAttacker                                                     // Cannot pickpocket yourself
                      && GetBattlerAbility(battler) == ABILITY_PICKPOCKET                               // Target must have pickpocket ability
                      && TARGET_TURN_DAMAGED                                                       // Target needs to have been damaged
                      && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)              // Subsitute unaffected
                      && IsBattlerAlive(battler)                                                        // Battler must be alive to pickpocket
                      && gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)] == ITEM_NONE                                   // Pickpocketer can't have an item already
                      && CanStealItem(battler, gBattlerAttacker, gBattleMons[gBattlerAttacker].item))   // Cannot steal plates, mega stones, etc
                    {
                        gBattlerTarget = gBattlerAbility = battler;
                        // Battle scripting is super brittle so we shall do the item exchange now (if possible)
                        if (GetBattlerAbility(gBattlerAttacker) != ABILITY_STICKY_HOLD)
                            StealTargetItem(gBattlerTarget, gBattlerAttacker);  // Target takes attacker's item

                        gEffectBattler = gBattlerAttacker;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_Pickpocket;   // Includes sticky hold check to print separate string
                        effect = TRUE;
                        break; // Pickpocket activates on fastest mon, so exit loop.
                    }
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_DANCER: // Special case because it's so annoying     //think this stays here, in emerald its actually in util.c & here??  very strange effect
            if (gBattleMoves[gCurrentMove].flags & FLAG_DANCE)
            {
                u8 battler, nextDancer = 0;

                if (!(gBattleStruct->lastMoveFailed & gBitTable[gBattlerAttacker]
                    || (!gSpecialStatuses[gBattlerAttacker].dancerUsedMove
                        && gProtectStructs[gBattlerAttacker].usesBouncedMove)))
                {   // Dance move succeeds
                    // Set target for other Dancer mons; set bit so that mon cannot activate Dancer off of its own move
                    if (!gSpecialStatuses[gBattlerAttacker].dancerUsedMove)
                    {
                        gBattleScripting.savedBattler = gBattlerTarget | 0x4;
                        gBattleScripting.savedBattler |= (gBattlerAttacker << 4);
                        gSpecialStatuses[gBattlerAttacker].dancerUsedMove = TRUE;
                    }
                    for (battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
                    {
                        if (GetBattlerAbility(battler) == ABILITY_DANCER && !gSpecialStatuses[battler].dancerUsedMove)
                        {
                            if (!nextDancer || (gBattleMons[battler].speed < gBattleMons[nextDancer & 0x3].speed))
                                nextDancer = battler | 0x4;
                        }
                    }
                    if (nextDancer && AbilityBattleEffects(ABILITYEFFECT_MOVE_END_OTHER, nextDancer & 0x3, 0, 0, 0))
                        effect = TRUE;
                }
            }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_EMERGENCY_EXIT:
                //last condition should if target not fainted or enemy has more mon in party
                //using special status this never triggered because status was alraedy cleared for wimpout
                if ((gBattleResources->flags->flags[gBattlerAttacker] & RESOURCE_FLAG_EMERGENCY_EXIT
                || gSpecialStatuses[gBattlerAttacker].EmergencyExit)
                && (!(gHitMarker & HITMARKER_FAINTED(gBattlerTarget)) || CountUsablePartyMons(gBattlerTarget) > 0)
                && gMultiHitCounter == 0) //to prevent switchout before multihit move ends
                {
                    gBattleResources->flags->flags[gBattlerAttacker] &= ~RESOURCE_FLAG_EMERGENCY_EXIT;
                    //needed this part to prevent repeat switchout
                    gSpecialStatuses[gBattlerAttacker].EmergencyExit = FALSE;
                    
                    if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER || GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    && CountUsablePartyMons(gBattlerAttacker) > 0
                    && (CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) || CountUsablePartyMons(gBattlerTarget) > 0)) //believe this causes to skip to next case
                    {
                    /*#if B_ABILITY_POP_UP == TRUE
                        gBattlescriptCurrInstr = BattleScript_EmergencyExit;
                    #else*/
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_EmergencyExitNoPopUp;
                        effect = TRUE;
                        return;
                    //#endif
                    }
                    else if ((CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) || CountUsablePartyMons(gBattlerTarget) > 0)
                    && (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER)))
                    {
                    /*#if B_ABILITY_POP_UP == TRUE
                        gBattlescriptCurrInstr = BattleScript_EmergencyExitWild;
                    #else*/
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_EmergencyExitWildNoPopUp;
                        effect = TRUE;
                        return;
                    //#endif
                    }
                    
                }
            ++gBattleScripting.atk49_state;
            break;
        case MOVE_END_SYMBIOSIS:
            for (i = 0; i < gBattlersCount; i++)
            {
                if ((gSpecialStatuses[i].berryReduced
                    || gSpecialStatuses[i].gemBoost
                    ) && SYMBIOSIS_CHECK(i, BATTLE_PARTNER(i)))
                {
                    BestowItem(BATTLE_PARTNER(i), i);
                    gLastUsedAbility = gBattleMons[BATTLE_PARTNER(i)].ability;
                    gBattleScripting.battler = gBattlerAbility = BATTLE_PARTNER(i);
                    gBattlerAttacker = i;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SymbiosisActivates;
                    effect = TRUE;
                }
            }
            ++gBattleScripting.atk49_state;  
            break;
        case MOVE_END_INFATUATION:
        {
            struct Pokemon *monAttacker, *monTarget;
            u16 speciesAttacker, speciesTarget;
            u32 personalityAttacker, personalityTarget;

            u16 targetAbility = GetBattlerAbility(gBattlerTarget);

            

            if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                monAttacker = &gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]];
            else
                monAttacker = &gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]];
            if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                monTarget = &gPlayerParty[gBattlerPartyIndexes[gBattlerTarget]];
            else
                monTarget = &gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]];
            speciesAttacker = GetMonData(monAttacker, MON_DATA_SPECIES);
            personalityAttacker = GetMonData(monAttacker, MON_DATA_PERSONALITY);
            speciesTarget = GetMonData(monTarget, MON_DATA_SPECIES);
            personalityTarget = GetMonData(monTarget, MON_DATA_PERSONALITY);

            if ((gBattleMoves[gCurrentMove].effect == EFFECT_ATTRACT_HIT)
            && TARGET_TURN_DAMAGED
            && GetBattlerAbility(gBattlerTarget) != ABILITY_OBLIVIOUS
            && GetBattlerAbility(gBattlerTarget) != ABILITY_FEMME_FATALE) //if meets conditions for attract hit\  add ABILITY_FEMME_FATALE
            {
                if (GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == GetGenderFromSpeciesAndPersonality(speciesTarget, personalityTarget)
                || GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == MON_GENDERLESS
                || GetGenderFromSpeciesAndPersonality(speciesTarget, personalityTarget) == MON_GENDERLESS) //if gender matches for infatuation
                    PrepareStringBattle(STRINGID_PKMNFELLINLOVE, gActiveBattler); //test
            }
        
        ++gBattleScripting.atk49_state;
        break;
        }
        case MOVE_END_TWOTURN_MOVES:
            if (gCurrentMove == MOVE_SKY_ATTACK)
            {
                if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)) //if not status which should only be on 2nd turn of move
                {
                    SET_STATCHANGER(STAT_EVASION, 2, TRUE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SkyattackMoveEndStatDrop; //should work but need test
                }
            }
            ++gBattleScripting.atk49_state;  
            break;
        case MOVE_END_NEXT_TARGET: // For moves hitting two opposing Pokemon.
        {
            u16 moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove);
            // Set a flag if move hits either target (for throat spray that can't check damage)
            if (!(gHitMarker & HITMARKER_UNABLE_TO_USE_MOVE)
             && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
                gProtectStructs[gBattlerAttacker].targetNotAffected = FALSE;

            gBattleStruct->targetsDone[gBattlerAttacker] |= gBitTable[gBattlerTarget];
            if (!(gHitMarker & HITMARKER_UNABLE_TO_USE_MOVE)
                && gBattleTypeFlags & BATTLE_TYPE_DOUBLE
                && !gProtectStructs[gBattlerAttacker].chargingTurn
                && (moveTarget == MOVE_TARGET_BOTH
                    || moveTarget == MOVE_TARGET_FOES_AND_ALLY)
                && !(gHitMarker & HITMARKER_NO_ATTACKSTRING))
            {
                u32 nextTarget = GetNextTarget(moveTarget);
                gHitMarker |= HITMARKER_NO_PPDEDUCT;

                if (nextTarget != MAX_BATTLERS_COUNT)
                {
                    gBattleStruct->moveTarget[gBattlerAttacker] = gBattlerTarget = nextTarget; // Fix for moxie spread moves
                    gBattleScripting.atk49_state = 0;
                    MoveValuesCleanUp();
                    gBattleScripting.moveEffect = gBattleScripting.savedMoveEffect; //this line not in originalfunciton think issue
                    BattleScriptPush(gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect]); //issue was saveMoveEffect wasn't assigned, so value was random
                    gBattlescriptCurrInstr = BattleScript_FlushMessageBox;
                    return;
                }
                // Check if the move used was actually a bounced move. If so, we need to go back to the original attacker and make sure, its move hits all 2 or 3 pokemon.
                else if (gProtectStructs[gBattlerAttacker].usesBouncedMove)
                {
                    u8 originalBounceTarget = gBattlerAttacker;
                    gBattlerAttacker = gBattleStruct->attackerBeforeBounce;
                    gBattleStruct->targetsDone[gBattlerAttacker] |= gBitTable[originalBounceTarget];
                    gBattleStruct->targetsDone[originalBounceTarget] = 0;

                    nextTarget = GetNextTarget(moveTarget);
                    if (nextTarget != MAX_BATTLERS_COUNT)
                    {
                        // We found another target for the original move user.
                        gBattleStruct->moveTarget[gBattlerAttacker] = gBattlerTarget = nextTarget;
                        gBattleScripting.atk49_state = 0;
                        gBattleScripting.animTurn = 0;
                        gBattleScripting.animTargetsHit = 0;
                        MoveValuesCleanUp();
                        BattleScriptPush(gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect]);
                        gBattlescriptCurrInstr = BattleScript_FlushMessageBox;
                        return;
                    }
                }

                gHitMarker |= HITMARKER_NO_ATTACKSTRING;
                gHitMarker &= ~HITMARKER_NO_PPDEDUCT;
            }
            //RecordLastUsedMoveBy(gBattlerAttacker, gCurrentMove);   with ai update, remove for now
            ++gBattleScripting.atk49_state;
            break;
        }
        case MOVE_END_CLEAR_BITS: // Clear/Set bits for things like using a move for all targets and all hits.
            if (gSpecialStatuses[gBattlerAttacker].instructedChosenTarget)
                *(gBattleStruct->moveTarget + gBattlerAttacker) = gSpecialStatuses[gBattlerAttacker].instructedChosenTarget & 0x3;
            if (gSpecialStatuses[gBattlerAttacker].dancerOriginalTarget)
                *(gBattleStruct->moveTarget + gBattlerAttacker) = gSpecialStatuses[gBattlerAttacker].dancerOriginalTarget & 0x3;

        /*#if B_RAMPAGE_CANCELLING >= GEN_5
            if (gBattleMoves[gCurrentMove].effect == EFFECT_RAMPAGE // If we're rampaging
              && (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)         // And it is unusable
              && (gBattleMons[gBattlerAttacker].status2 & STATUS2_LOCK_CONFUSE) != STATUS2_LOCK_CONFUSE_TURN(1))  // And won't end this turn
                CancelMultiTurnMoves(gBattlerAttacker); // Cancel it
        #endif*/
        
        //think will move this to move end clear bit effects
    //so if lastused move 
    //double check if that goes before or after
    //my sandstorm damage, that is in endturn field effects
    //vsonic test see if works as I want
    if (gStatuses3[gBattlerAttacker] & STATUS3_CHARGED_UP 
    && gBattleMoves[gLastMoves[gBattlerAttacker]].type == TYPE_ELECTRIC
    && gBattleMoves[gLastMoves[gBattlerAttacker]].split != SPLIT_STATUS)
        gStatuses3[gBattlerAttacker] &= ~STATUS3_CHARGED_UP;

            gBattleStruct->targetsDone[gBattlerAttacker] = 0;
            gProtectStructs[gBattlerAttacker].usesBouncedMove = FALSE;
            //gProtectStructs[gBattlerAttacker].targetAffected = FALSE; think dont need
            gBattleStruct->ateBoost[gBattlerAttacker] = 0;
            gStatuses3[gBattlerAttacker] &= ~STATUS3_ME_FIRST;
            gSpecialStatuses[gBattlerAttacker].gemBoost = FALSE;
            gSpecialStatuses[gBattlerAttacker].damagedMons = 0;
            gSpecialStatuses[gBattlerTarget].berryReduced = FALSE;
            gBattleScripting.moveEffect = 0;
            gBattleStruct->isAtkCancelerForCalledMove = FALSE;
            // clear attacker z move data
            /*//gBattleStruct->zmove.active = FALSE;
            //gBattleStruct->zmove.toBeUsed[gBattlerAttacker] = MOVE_NONE;
            //gBattleStruct->zmove.effect = EFFECT_HIT;*/
            ++gBattleScripting.atk49_state; //vsonic
            break;
        case MOVE_END_PURSUIT_NEXT_ACTION:
            if (gBattleStruct->pursuitTarget & (1u << gBattlerTarget))
            {
                u32 storedTarget = gBattlerTarget;
                if (TrySetTargetToNextPursuiter(gBattlerTarget))
                {
                    ChangeOrderTargetAfterAttacker();
                    *(gBattleStruct->moveTarget + gBattlerTarget) = storedTarget;
                    gBattlerTarget = storedTarget;
                }
                else if (IsBattlerAlive(gBattlerTarget))
                {
                    gBattlerAttacker = gBattlerTarget;

                    //don't think I need?
                    if (gBattleStruct->pursuitSwitchByMove)
                        gBattlescriptCurrInstr = BattleScript_MoveSwitchOpenPartyScreen;
                    else
                        gBattlescriptCurrInstr = BattleScript_DoSwitchOut;
                    
                    *(gBattleStruct->monToSwitchIntoId + gBattlerTarget) = gBattleStruct->pursuitStoredSwitch;
                    gBattleStruct->pursuitTarget = 0;
                    gBattleStruct->pursuitSwitchByMove = FALSE;
                    gBattleStruct->pursuitStoredSwitch = 0;
                    effect = TRUE;
                }
            }
            ++gBattleScripting.atk49_state; //vsonic
            break;
        case MOVE_END_COUNT:
            break;
        }

        if (endMode == 1 && effect == FALSE)    //what sets mode?  state is supposed to be atk49state / sMOVEEND_STATE ok nvm,  atk49state is sMOVEEND_STATE and state is a value being compared and adjusted to that value
            gBattleScripting.atk49_state = MOVE_END_COUNT;
        if (endMode == 2 && endState == gBattleScripting.atk49_state) //endmode sets loop conditions, 
            gBattleScripting.atk49_state = MOVE_END_COUNT;

    } while (gBattleScripting.atk49_state != MOVE_END_COUNT && effect == FALSE);

    if (gBattleScripting.atk49_state == MOVE_END_COUNT && effect == FALSE)  //believe this is essentially for endmode0 ?, endmode can be 0,1 or 2,  1 & 2 are caught above
        gBattlescriptCurrInstr = cmd->nextInstr;    //if it passes those it goes to this, so think this is default condiiton. i.e mode 0
}

//doesn't have stab check
//emerald doesn't use this, removed from brick break and rollout, leaving for moves that 
//don't do type damage. will remove changes keep basic
//its completely pointless I think?  yeah emerald doesn't have this and replaced it with healblock
//edit no longer used - need test but think can replace
//can replace for counter and mirror coat no problem, rollout and brick break are janky so need extra logic to take place of its purpose there
//workign on with new macro callif, to do something based on need in function based on moveeffect
static void atk4A_typecalc2(void)   //aight this is only for counter, mirror coat, rollout, & brick break?  ok I get it now, its becuase those moves specifcially don't get stab, would just need put type calc above dmg calc
{
    u8 flags = 0;
    s32 i = 0;
    u8 moveType;
    u8 argument = gBattleMoves[gCurrentMove].argument;
    u8 type1 = gBattleMons[gBattlerTarget].type1, type2 = gBattleMons[gBattlerTarget].type2, type3 = gBattleMons[gBattlerTarget].type3;
    u16 multiplier;

    GET_MOVE_TYPE(gCurrentMove, moveType);

    multiplier = CalcTypeEffectivenessMultiplier(gCurrentMove, moveType, gBattlerAttacker, gBattlerTarget, FALSE);
    /*if (gBattleMons[gBattlerTarget].ability == ABILITY_LEVITATE && moveType == TYPE_GROUND)
   {
       gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
       gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
       gLastLandedMoves[gBattlerTarget] = 0;
       gBattleCommunication[6] = moveType;
       RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
   }*/
    if (!(IsBattlerGrounded(gBattlerTarget)) && moveType == TYPE_GROUND
        && !(gBattleMoves[gCurrentMove].flags & FLAG_GROUND_HITS_FLOATING))
    {
        gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
        gLastLandedMoves[gBattlerTarget] = 0;
        gBattleCommunication[6] = moveType;

    }
    if (moveType == TYPE_WATER && GetBattlerAbility(gBattlerTarget) == ABILITY_LIQUID_SOUL) //new buff for liquid soul
    {
        gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
        gLastLandedMoves[gBattlerTarget] = 0;
        gLastHitByType[gBattlerTarget] = 0; //typecalc & typecalc2 are different, tp2 doesn't have this
        gBattleCommunication[6] = moveType;

        gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);

    }
    else if (gBattleMons[gBattlerTarget].hp != 0) //change to make sure doesnt exclude things w else
    {
        // take type effectiveness
        gBattleMoveDamage = ApplyModifier(multiplier, gBattleMoveDamage);
        /*while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE)
        {
            if (TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT)
            {
                if (gBattleMons[gBattlerTarget].status2 & STATUS2_FORESIGHT)
                {
                    break;
                }
                else
                {
                    i += 3; //read next type
                    continue;
                }
            }
            if (TYPE_EFFECT_ATK_TYPE(i) == moveType)
            {
                // check type1
                if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                {

                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                    {
                        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                        break;
                    }
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                    {
                        flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;    //this code is weird why does it use gmoveresultflags and then swap variable?
                    }
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                    {
                        flags |= MOVE_RESULT_SUPER_EFFECTIVE;
                    }
                }
                // check type2
                else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                {

                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                    {
                        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                        break;
                    }
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                    {
                        flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
                    }
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                    {
                        flags |= MOVE_RESULT_SUPER_EFFECTIVE;
                    }
                }
                //check type3
                else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                {

                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                    {
                        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                        break;
                    }
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                    {
                        flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
                    }
                    if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                    {
                        flags |= MOVE_RESULT_SUPER_EFFECTIVE;
                    }                        

                }
                    
            }

            if (gBattleMoves[gCurrentMove].effect == EFFECT_TWO_TYPED_MOVE) //will need to add or for any special custom dual types, like splishy splash 
            {
                if (TYPE_EFFECT_ATK_TYPE(i) == argument)
                {
                    // check type1
                    if (TYPE_EFFECT_DEF_TYPE(i) == type1)
                    {

                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                        {
                            gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                            break;
                        }
                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                        {
                            flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;    //this code is weird why does it use gmoveresultflags and then swap variable?
                        }
                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                        {
                            flags |= MOVE_RESULT_SUPER_EFFECTIVE;
                        }
                    }
                    // check type2
                    else if (TYPE_EFFECT_DEF_TYPE(i) == type2)
                    {

                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                        {
                            gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                            break;
                        }
                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                        {
                            flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
                        }
                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                        {
                            flags |= MOVE_RESULT_SUPER_EFFECTIVE;
                        }
                    }
                    //check type3
                    else if (TYPE_EFFECT_DEF_TYPE(i) == type3 && type3 != TYPE_MYSTERY)
                    {

                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NO_EFFECT)
                        {
                            gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
                            break;
                        }
                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_NOT_EFFECTIVE)
                        {
                            flags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
                        }
                        if (TYPE_EFFECT_MULTIPLIER(i) == TYPE_MUL_SUPER_EFFECTIVE)
                        {
                            flags |= MOVE_RESULT_SUPER_EFFECTIVE;
                        }                            

                    }
                }
            }
            i += 3;
        } */
    }
    if ((GetBattlerAbility(gBattlerTarget) == ABILITY_WONDER_GUARD && gBattleStruct->SingleUseAbilityTimers[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)])
     && !(flags & MOVE_RESULT_NO_EFFECT)    
     && (!(flags & MOVE_RESULT_SUPER_EFFECTIVE) || ((flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
     && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)
    {
        gLastUsedAbility = ABILITY_WONDER_GUARD;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gBattleCommunication[6] = 3;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    if (GetBattlerAbility(gBattlerTarget) == ABILITY_DISPIRIT_GUARD
        && !(flags & MOVE_RESULT_NO_EFFECT)       
        && (!(flags & MOVE_RESULT_NOT_VERY_EFFECTIVE) || ((flags & (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)) == (MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)
    {
        gLastUsedAbility = ABILITY_DISPIRIT_GUARD;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gBattleCommunication[6] = 3;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    if (gBattleMons[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerAttacker)))].ability == ABILITY_TELEPATHY
        && gBattleMoves[gCurrentMove].split != SPLIT_STATUS)    //hopefully works, should just make my move not hit ally partner
    {
        gLastUsedAbility = ABILITY_TELEPATHY;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastLandedMoves[gBattlerTarget] = 0;
        gBattleCommunication[6] = 3;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    if (gMoveResultFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
        gProtectStructs[gBattlerAttacker].targetNotAffected = TRUE;
    ++gBattlescriptCurrInstr;
}

static void atk4B_returnatktoball(void)
{
    gActiveBattler = gBattlerAttacker;
    if (!(gHitMarker & HITMARKER_FAINTED(gActiveBattler)))
    {
        BtlController_EmitReturnMonToBall(0, 0);
        MarkBattlerForControllerExec(gActiveBattler);
    }
    ++gBattlescriptCurrInstr;
}

static void atk4C_getswitchedmondata(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        gBattlerPartyIndexes[gActiveBattler] = *(gBattleStruct->monToSwitchIntoId + gActiveBattler);
        BtlController_EmitGetMonData(0, REQUEST_ALL_BATTLE, gBitTable[gBattlerPartyIndexes[gActiveBattler]]);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 2;
    }
}

#define BASESTATS_TO_BATTLEMONS_CONVERSION
static void atk4D_switchindataupdate(void)  //important, think can use THIS to make switchin abilities repeat, would work for both fainted and turn switched.
{ // ok switch in repeat isn't here can do it elsewhere
    struct BattlePokemon oldData;
    s32 i;
    u8 *monData;
    u16 species,applied_species;

    

    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        oldData = gBattleMons[gActiveBattler];
        monData = (u8 *)(&gBattleMons[gActiveBattler]);

        for (i = 0; i < sizeof(struct BattlePokemon); ++i)
        {
            monData[i] = gBattleBufferB[gActiveBattler][4 + i]; //not 100% what this does but seems tobe populating new mon data
        } //if I put species checks above this it doesn't correctly load data

        species = gBattleMons[gActiveBattler].species;
        //for some reason broke shit and now loading wrong mon type when switching?
        //turns everything into species 0, normal type
        //I was putting it above definition of activebattler so poplated w nothing

        if (gBaseStats[GetFormSpeciesId(species, 0)].flags == F_HAS_COSMETIC_FORMS)
        applied_species = GetFormSpeciesId(species, 0);
        else
            applied_species = species;

        if (species == SPECIES_PIKACHU_ROCK_STAR
        || species == SPECIES_PIKACHU_BELLE
        || species == SPECIES_PIKACHU_POP_STAR
        || species == SPECIES_PIKACHU_PH_D
        || species == SPECIES_PIKACHU_LIBRE
        || species == SPECIES_BASCULIN_WHITE_STRIPED)
            applied_species = species;

        gBattleMons[gActiveBattler].type1 = gBaseStats[applied_species].type1;
        gBattleMons[gActiveBattler].type2 = gBaseStats[applied_species].type2;
        gBattleMons[gActiveBattler].type3 = TYPE_MYSTERY;
        gBattleMons[gActiveBattler].ability = GetAbilityBySpecies(applied_species, gBattleMons[gActiveBattler].abilityNum);
        // check knocked off item
        i = GetBattlerSide(gActiveBattler);
        if (gWishFutureKnock.knockedOffMons[i] & gBitTable[gBattlerPartyIndexes[gActiveBattler]])
            gBattleMons[gActiveBattler].item = 0;
        if (gBattleMoves[gCurrentMove].effect == EFFECT_BATON_PASS)
        {
            for (i = 0; i < NUM_BATTLE_STATS; ++i)
            {
                gBattleMons[gActiveBattler].statStages[i] = oldData.statStages[i];
            }
            gBattleMons[gActiveBattler].status2 = oldData.status2;
        }
        SwitchInClearSetData();
        gBattleScripting.battler = gActiveBattler;
        PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gActiveBattler, gBattlerPartyIndexes[gActiveBattler]);
        gBattlescriptCurrInstr += 2;
    }
} //type issue I'm having seems to be fixed, by switchign which I believe is this functinon, I think somehow I'm being set to species 0 for wilds which is type normal?

static void atk4E_switchinanim(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT
         && !(gBattleTypeFlags & 
              (BATTLE_TYPE_LINK
            | BATTLE_TYPE_LEGENDARY
            | BATTLE_TYPE_OLD_MAN_TUTORIAL
            | BATTLE_TYPE_POKEDUDE
            | BATTLE_TYPE_EREADER_TRAINER
            | BATTLE_TYPE_GHOST)))
            HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
        gAbsentBattlerFlags &= ~(gBitTable[gActiveBattler]);
        BtlController_EmitSwitchInAnim(0, gBattlerPartyIndexes[gActiveBattler], gBattlescriptCurrInstr[2]);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 3;
    }
}

bool32 CanBattlerSwitch(u32 battlerId)
{
    s32 i, lastMonId, battlerIn1, battlerIn2;
    bool32 ret = FALSE;
    struct Pokemon *party;

    if (BATTLE_TWO_VS_ONE_OPPONENT && GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
    {
        battlerIn1 = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        battlerIn2 = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        party = gEnemyParty;

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&party[i], MON_DATA_HP) != 0
             && GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE
             && !GetMonData(&party[i], MON_DATA_IS_EGG)
             && i != gBattlerPartyIndexes[battlerIn1] && i != gBattlerPartyIndexes[battlerIn2])
                break;
        }

        ret = (i != PARTY_SIZE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
            party = gEnemyParty;
        else
            party = gPlayerParty;

        lastMonId = 0;
        if (battlerId & 2)
            lastMonId = MULTI_PARTY_SIZE;

        for (i = lastMonId; i < lastMonId + MULTI_PARTY_SIZE; i++)
        {
            if (GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE
             && !GetMonData(&party[i], MON_DATA_IS_EGG)
             && GetMonData(&party[i], MON_DATA_HP) != 0
             && gBattlerPartyIndexes[battlerId] != i)
                break;
        }

        ret = (i != lastMonId + MULTI_PARTY_SIZE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER)
        {
            if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
            {
                party = gPlayerParty;

                lastMonId = 0;
                if (GetLinkTrainerFlankId(GetBattlerMultiplayerId(battlerId)) == TRUE)
                    lastMonId = MULTI_PARTY_SIZE;
            }
            else
            {
                party = gEnemyParty;

                if (battlerId == 1)
                    lastMonId = 0;
                else
                    lastMonId = MULTI_PARTY_SIZE;
            }
        }
        else
        {
            if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
                party = gEnemyParty;
            else
                party = gPlayerParty;

            lastMonId = 0;
            if (GetLinkTrainerFlankId(GetBattlerMultiplayerId(battlerId)) == TRUE)
                lastMonId = MULTI_PARTY_SIZE;
        }

        for (i = lastMonId; i < lastMonId + MULTI_PARTY_SIZE; i++)
        {
            if (GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE
             && !GetMonData(&party[i], MON_DATA_IS_EGG)
             && GetMonData(&party[i], MON_DATA_HP) != 0
             && gBattlerPartyIndexes[battlerId] != i)
                break;
        }

        ret = (i != lastMonId + MULTI_PARTY_SIZE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
    {
        party = gEnemyParty;

        lastMonId = 0;
        if (battlerId == B_POSITION_OPPONENT_RIGHT)
            lastMonId = PARTY_SIZE / 2;

        for (i = lastMonId; i < lastMonId + (PARTY_SIZE / 2); i++)
        {
            if (GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE
             && !GetMonData(&party[i], MON_DATA_IS_EGG)
             && GetMonData(&party[i], MON_DATA_HP) != 0
             && gBattlerPartyIndexes[battlerId] != i)
                break;
        }

        ret = (i != lastMonId + (PARTY_SIZE / 2));
    }
    else
    {
        if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
        {
            battlerIn1 = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);

            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                battlerIn2 = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
            else
                battlerIn2 = battlerIn1;

            party = gEnemyParty;
        }
        else
        {
            // Check if attacker side has mon to switch into
            battlerIn1 = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);

            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                battlerIn2 = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
            else
                battlerIn2 = battlerIn1;

            party = gPlayerParty;
        }

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&party[i], MON_DATA_HP) != 0
             && GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE
             && !GetMonData(&party[i], MON_DATA_IS_EGG)
             && i != gBattlerPartyIndexes[battlerIn1] && i != gBattlerPartyIndexes[battlerIn2])
                break;
        }

        ret = (i != PARTY_SIZE);
    }
    return ret;
}

#define OTHER_SWITCH_EFFECTS_1
static void atk4F_jumpifcantswitch(void)
{
    s32 i;
    s32 lastMonId;
    struct Pokemon *party;

    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1] & ~(ATK4F_DONT_CHECK_STATUSES));
    if (!(gBattlescriptCurrInstr[1] & ATK4F_DONT_CHECK_STATUSES)
    && !CanBattlerEscape(gActiveBattler))
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 2);
    }
    else
    {
        if (CanBattlerSwitch(gActiveBattler))
            gBattlescriptCurrInstr += 6;//cmd->nextInstr;
        else
           gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 2);//cmd->jumpInstr;
    }  

}

static void ChooseMonToSendOut(u8 slotId)
{
    *(gBattleStruct->battlerPartyIndexes + gActiveBattler) = gBattlerPartyIndexes[gActiveBattler];
    BtlController_EmitChoosePokemon(0, PARTY_ACTION_SEND_OUT, slotId, 0, gBattleStruct->battlerPartyOrders[gActiveBattler]);
    MarkBattlerForControllerExec(gActiveBattler);
}

static void atk50_openpartyscreen(void)
{
    u32 flags;
    u8 hitmarkerFaintBits;
    u8 battlerId;
    const u8 *jumpPtr;

    battlerId = 0;
    flags = 0;
    jumpPtr = T1_READ_PTR(gBattlescriptCurrInstr + 2);
    if (gBattlescriptCurrInstr[1] == 5)
    {
        if ((gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI)) != BATTLE_TYPE_DOUBLE)
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gHitMarker & HITMARKER_FAINTED(gActiveBattler))
                {
                    if (HasNoMonsToSwitch(gActiveBattler, 6, 6))
                    {
                        gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                        gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                        BtlController_EmitLinkStandbyMsg(0, 2);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                    else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                    {
                        ChooseMonToSendOut(6);
                        gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                    }
                }
                else
                {
                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        {
            u8 faintedHasReplacement_0, faintedHasReplacement_1, faintedHasReplacement_2, faintedHasReplacement_3;

            hitmarkerFaintBits = gHitMarker >> 0x1C;
            if (gBitTable[0] & hitmarkerFaintBits)
            {
                gActiveBattler = 0;
                if (HasNoMonsToSwitch(0, 6, 6))
                {
                    gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                    gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                    BtlController_EmitCmd42(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                {
                    ChooseMonToSendOut(gBattleStruct->monToSwitchIntoId[2]);
                    gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                }
                else
                {
                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                    flags |= 1;
                }
            }
            if (gBitTable[2] & hitmarkerFaintBits && !(gBitTable[0] & hitmarkerFaintBits))
            {
                gActiveBattler = 2;
                if (HasNoMonsToSwitch(2, 6, 6))
                {
                    gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                    gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                    BtlController_EmitCmd42(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                {
                    ChooseMonToSendOut(gBattleStruct->monToSwitchIntoId[0]);
                    gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                }
                else if (!(flags & 1))
                {
                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
            if (gBitTable[1] & hitmarkerFaintBits)
            {
                gActiveBattler = 1;
                if (HasNoMonsToSwitch(1, 6, 6))
                {
                    gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                    gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                    BtlController_EmitCmd42(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                {
                    ChooseMonToSendOut(gBattleStruct->monToSwitchIntoId[3]);
                    gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                }
                else
                {
                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                    flags |= 2;
                }
            }
            if (gBitTable[3] & hitmarkerFaintBits && !(gBitTable[1] & hitmarkerFaintBits))
            {
                gActiveBattler = 3;
                if (HasNoMonsToSwitch(3, 6, 6))
                {
                    gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                    gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                    BtlController_EmitCmd42(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                {
                    ChooseMonToSendOut(gBattleStruct->monToSwitchIntoId[1]);
                    gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                }
                else if (!(flags & 2))
                {
                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
            faintedHasReplacement_0 = gSpecialStatuses[0].faintedHasReplacement;
            if (!faintedHasReplacement_0)
            {
                faintedHasReplacement_2 = gSpecialStatuses[2].faintedHasReplacement;
                if (!faintedHasReplacement_2 && hitmarkerFaintBits != 0)
                {
                    if (gAbsentBattlerFlags & gBitTable[0])
                        gActiveBattler = 2;
                    else
                        gActiveBattler = 0;

                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }

            }
            faintedHasReplacement_1 = gSpecialStatuses[1].faintedHasReplacement;
            if (!faintedHasReplacement_1)
            {
                faintedHasReplacement_3 = gSpecialStatuses[3].faintedHasReplacement;
                if (!faintedHasReplacement_3 && hitmarkerFaintBits != 0)
                {
                    if (gAbsentBattlerFlags & gBitTable[1])
                        gActiveBattler = 3;
                    else
                        gActiveBattler = 1;
                    BtlController_EmitLinkStandbyMsg(0, 2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
        }
        gBattlescriptCurrInstr += 6;
    }
    else if (gBattlescriptCurrInstr[1] == 6)
    {
        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                hitmarkerFaintBits = gHitMarker >> 0x1C;
                if (gBitTable[2] & hitmarkerFaintBits && gBitTable[0] & hitmarkerFaintBits)
                {
                    gActiveBattler = 2;
                    if (HasNoMonsToSwitch(2, gBattleBufferB[0][1], 6))
                    {
                        gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                        gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                        BtlController_EmitCmd42(0);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                    else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                    {
                        ChooseMonToSendOut(gBattleStruct->monToSwitchIntoId[0]);
                        gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                    }
                }
                if (gBitTable[3] & hitmarkerFaintBits && hitmarkerFaintBits & gBitTable[1])
                {
                    gActiveBattler = 3;
                    if (HasNoMonsToSwitch(3, gBattleBufferB[1][1], 6))
                    {
                        gAbsentBattlerFlags |= gBitTable[gActiveBattler];
                        gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
                        BtlController_EmitCmd42(0);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                    else if (!gSpecialStatuses[gActiveBattler].faintedHasReplacement)
                    {
                        ChooseMonToSendOut(gBattleStruct->monToSwitchIntoId[1]);
                        gSpecialStatuses[gActiveBattler].faintedHasReplacement = 1;
                    }
                }
                gBattlescriptCurrInstr += 6;
            }
            else
            {
                gBattlescriptCurrInstr += 6;
            }
        }
        else
        {
            gBattlescriptCurrInstr += 6;
        }

        hitmarkerFaintBits = gHitMarker >> 0x1C;

        gBattlerFainted = 0;
        while (1)
        {
            if (gBitTable[gBattlerFainted] & hitmarkerFaintBits)
                break;
            if (gBattlerFainted >= gBattlersCount)
                break;
            ++gBattlerFainted;
        }

        if (gBattlerFainted == gBattlersCount)
            gBattlescriptCurrInstr = jumpPtr;
    }
    else
    {
        if (gBattlescriptCurrInstr[1] & OPEN_PARTY_ALLOW_CANCEL)
            hitmarkerFaintBits = PARTY_ACTION_CHOOSE_MON; // Used here as the caseId for the EmitChoose function.
        else
            hitmarkerFaintBits = PARTY_ACTION_SEND_OUT;
        battlerId = GetBattlerForBattleScript(gBattlescriptCurrInstr[1] & ~(OPEN_PARTY_ALLOW_CANCEL));
        if (gSpecialStatuses[battlerId].faintedHasReplacement)
        {
            gBattlescriptCurrInstr += 6;
        }
        else if (HasNoMonsToSwitch(battlerId, 6, 6))
        {
            gActiveBattler = battlerId;
            gAbsentBattlerFlags |= gBitTable[gActiveBattler];
            gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
            gBattlescriptCurrInstr = jumpPtr;
        }
        else
        {
            gActiveBattler = battlerId;
            *(gBattleStruct->battlerPartyIndexes + gActiveBattler) = gBattlerPartyIndexes[gActiveBattler];
            BtlController_EmitChoosePokemon(0, hitmarkerFaintBits, *(gBattleStruct->monToSwitchIntoId + (gActiveBattler ^ 2)), 0, gBattleStruct->battlerPartyOrders[gActiveBattler]);
            MarkBattlerForControllerExec(gActiveBattler);
            gBattlescriptCurrInstr += 6;
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_LEFT && gBattleResults.playerSwitchesCounter < 0xFF)
                ++gBattleResults.playerSwitchesCounter;

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
                {
                    if (gActiveBattler != battlerId)
                    {
                        BtlController_EmitLinkStandbyMsg(0, 2);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                }
            }
            else
            {
                gActiveBattler = GetBattlerAtPosition(GetBattlerPosition(battlerId) ^ BIT_SIDE);
                if (gAbsentBattlerFlags & gBitTable[gActiveBattler])
                    gActiveBattler ^= BIT_FLANK;
                BtlController_EmitLinkStandbyMsg(0, 2);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
    }
}

static void atk51_switchhandleorder(void)
{
    s32 i;

    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        switch (gBattlescriptCurrInstr[2])
        {
        case 0:
            for (i = 0; i < gBattlersCount; ++i)
                if (gBattleBufferB[i][0] == 0x22)
                    *(gBattleStruct->monToSwitchIntoId + i) = gBattleBufferB[i][1];
            break;
        case 1:
            if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                UpdatePartyOwnerOnSwitch_NonMulti(gActiveBattler);
            break;
        case 2:
            gBattleCommunication[0] = gBattleBufferB[gActiveBattler][1];
            *(gBattleStruct->monToSwitchIntoId + gActiveBattler) = gBattleBufferB[gActiveBattler][1];

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) &= 0xF;
                *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) |= (gBattleBufferB[gActiveBattler][2] & 0xF0);
                *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 1) = gBattleBufferB[gActiveBattler][3];
                *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) &= (0xF0);
                *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) |= (gBattleBufferB[gActiveBattler][2] & 0xF0) >> 4;
                *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 2) = gBattleBufferB[gActiveBattler][3];
            }
            else
            {
                UpdatePartyOwnerOnSwitch_NonMulti(gActiveBattler);
            }
            PREPARE_SPECIES_BUFFER(gBattleTextBuff1, gBattleMons[gBattlerAttacker].species)
            PREPARE_MON_NICK_BUFFER(gBattleTextBuff2, gActiveBattler, gBattleBufferB[gActiveBattler][1])
            break;
        }
        gBattlescriptCurrInstr += 3;
    }
}

static bool32 NoAliveMonsForPlayer(void)
{
    u32 i;
    u32 HP_count = 0;

    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER) // && (gPartnerTrainerId == TRAINER_STEVEN_PARTNER || gPartnerTrainerId >= TRAINER_CUSTOM_PARTNER))
    {
        for (i = 0; i < MULTI_PARTY_SIZE; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
                HP_count += GetMonData(&gPlayerParty[i], MON_DATA_HP);
        }
    }
    else
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
               // && (!(gBattleTypeFlags & BATTLE_TYPE_ARENA) || !(gBattleStruct->arenaLostPlayerMons & gBitTable[i])))
            {
                HP_count += GetMonData(&gPlayerParty[i], MON_DATA_HP);
            }
        }
    }

    return (HP_count == 0);
}

static bool32 NoAliveMonsForOpponent(void)
{
    u32 i;
    u32 HP_count = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES) && !GetMonData(&gEnemyParty[i], MON_DATA_IS_EGG))
            //&& (!(gBattleTypeFlags & BATTLE_TYPE_ARENA) || !(gBattleStruct->arenaLostOpponentMons & gBitTable[i])))
        {
            HP_count += GetMonData(&gEnemyParty[i], MON_DATA_HP);
        }
    }

    return (HP_count == 0);
}

bool32 NoAliveMonsForEitherParty(void)
{
    return (NoAliveMonsForPlayer() || NoAliveMonsForOpponent());
}

u32 GetTotalAccuracy(u32 battlerAtk, u32 battlerDef, u32 move, u32 atkAbility, u32 defAbility, u32 atkHoldEffect, u32 defHoldEffect)
{
        
        s8 buff, evasionStage;
        u32 calc, moveAcc, i;
        u8 accStage = gBattleMons[battlerAtk].statStages[STAT_ACC];
        u8 atkParam = GetBattlerHoldEffectParam(battlerAtk, gBattleMons[battlerAtk].item);
        u8 defParam = GetBattlerHoldEffectParam(battlerDef, gBattleMons[battlerDef].item);

        
        gPotentialItemEffectBattler = battlerDef;
        evasionStage = gBattleMons[battlerDef].statStages[STAT_EVASION];

        if (atkAbility == ABILITY_UNAWARE || atkAbility == ABILITY_KEEN_EYE || atkAbility == ABILITY_SIXTH_SENSE)
            evasionStage = DEFAULT_STAT_STAGE;
        if (gBattleMoves[move].flags & FLAG_STAT_STAGES_IGNORED)
            evasionStage = DEFAULT_STAT_STAGE;
        if (defAbility == ABILITY_UNAWARE)
            accStage = DEFAULT_STAT_STAGE;

        if (gBattleMons[battlerDef].status2 & STATUS2_FORESIGHT || gStatuses3[battlerDef] & STATUS3_MIRACLE_EYED)    //if used foresight against target they can't evade
        {
            //u8 accStage = gBattleMons[gBattlerAttacker].statStages[STAT_ACC];

            buff = accStage;
        }
        else
        {
            //u8 accStage = gBattleMons[gBattlerAttacker].statStages[STAT_ACC];

            buff = accStage + DEFAULT_STAT_STAGE - evasionStage;
        } //this the line that links accuracy and evasion I believe

        

       

        if (buff < MIN_STAT_STAGE)
            buff = MIN_STAT_STAGE;
        if (buff > MAX_STAT_STAGE)
            buff = MAX_STAT_STAGE;

        //trap effects - //remember plan to setup effect to persist post user switching out
        /*if ((gBattleMons[battlerAtk].status4 & STATUS4_SAND_TOMB))  //hope works should lower accruacy 2 stages if trapped by sandtomb
        {
            accStage -= 2;
        }*/

        moveAcc = gBattleMoves[move].accuracy;
         //think I just need nest if, and have my default value in an else

        //cacophony boost
        if (ShouldCacophonyBoostAccuracy(move))
            moveAcc = 100;

        
        

        if (gCurrentMove == MOVE_FURY_CUTTER) { //still not quite right, doesn't display right message for things like wonderguard

            //Logic for altering animation used in battle_anim_effects_2
            if (gDisableStructs[gBattlerAttacker].furyCutterCounter == gMultiTask)
                gDisableStructs[gBattlerAttacker].furyCutterCounter = 0;
           
            if (gDisableStructs[gBattlerAttacker].furyCutterCounter != gMultiTask)  //increment until reach 5
               ++gDisableStructs[gBattlerAttacker].furyCutterCounter; //removing to test that it isn't incrementing twice. (it was)
            
            //acc drop effect
            gDisableStructs[gBattlerAttacker].furyCutterAccDrop = moveAcc;

                for (i = 1; i <= (gMultiTask - gMultiHitCounter); ++i) { //triggers on second hit, so i = 1 - current num hits, i =3 on4th hit
                    
                    if (i == 2) //should be 3rd hit
                    {
                        gDisableStructs[gBattlerAttacker].furyCutterAccDrop = 95; //set 3rd hit to 95, 4th hit remains the same, set main acc to 100, to ensure first 2 hits land
                    }
                    
                    if (i == 3) //makes only trigger onlast 4th hit, to slightly lower chance of landing 4th hit if you rolled it
                   {
                        gDisableStructs[gBattlerAttacker].furyCutterAccDrop -= (i - 1); 
                        gDisableStructs[gBattlerAttacker].furyCutterAccDrop *= 92; //so far is working to stop the move,
                        gDisableStructs[gBattlerAttacker].furyCutterAccDrop /= 100;
                   }  //makes 4th hit have 85 accuracy
                 //if (i == 3) 
                 //{/
                 //   gDisableStructs[gBattlerAttacker].furyCutterAccDrop -= 16; //weighting for last 2 hits, only need to do for one i value as its all passed to next
                 //}
                    //gDisableStructs[gBattlerAttacker].furyCutterAccDrop *= 95; //so far is working to stop the move,
                    //gDisableStructs[gBattlerAttacker].furyCutterAccDrop /= 100;  //may replace with just moveAcc  still don't know why not working
                    
                } //seems still overperforming potentially drop above 7 to a 8 or 9? or drop to third hit ni stead of 4th? by changing == 3 to ==2 ?  check later vsonic

            moveAcc = gDisableStructs[gBattlerAttacker].furyCutterAccDrop;
        } 

        // check Thunder on sunny weather / need add hail blizzard buff?(IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_RAIN_ANY)
        //don't rememeber why I used effect thunder instead of gcurrentmove
        if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SUN_ANY) && (gBattleMoves[move].effect == EFFECT_THUNDER || gBattleMoves[move].effect == EFFECT_HURRICANE))
            moveAcc = 65;   //make slightly more forgiving
        // Check Wonder Skin.
        if ((GetBattlerAbility(gBattlerTarget) == ABILITY_WONDER_SKIN
        || GetBattlerAbility(gBattlerTarget) == ABILITY_IMMUTABLE_WIND) 
        && IS_MOVE_STATUS(move) && moveAcc != 50)   //changed so can include 0 accuracy status moves.
            moveAcc = 50;       //as many status moves were changed later gen and would be excluded from wonder skin    

        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_SPACE_CONTROL
        && !IS_MOVE_STATUS(move))
            moveAcc = 100;
        

        if (moveAcc > 100)
            moveAcc = 100; // to prevent possible broken values.

        calc = gAccuracyStageRatios[buff].dividend * moveAcc;
        calc /= gAccuracyStageRatios[buff].divisor;

        //with introduction of floating & flyign nerfs decide flying types
        //need something extra to help them stand out
        //came up with flying ace, idea flying gives you high ground and flying types
        //are more manouvarble than any other floating mon,
        //so flying types in air, should get an advantage against grounded mon
        //everyone hates evasion mechanics so I'm not gonna go crazy here,
        //just enough to make things miss that otherwise wouldn't
        //adding exceptions since not in sandstorm sight is a factor
        //thnk can drop this further looked at calc, and a single stage acc drop
        //is 75% stacking sandstorm sandveil and this at 10% are 10% below that,
        //and don't even equate to a 2 stage drop which is 60
        //need to be careful, as it does acc drop without actually dropping stat stage
        //don't want to overdo, but 5% drop at 95% is pretty much completely unnoticeable
        //but it makes all accuracy drops more effective, cna treat like other games,
        //marginal gains being the main focus not strength of individual effects
        if (IsBattlerGrounded(gBattlerAttacker)
        && !IsBattlerGrounded(gBattlerTarget)
        && IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_FLYING)
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_KEEN_EYE
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SIXTH_SENSE)
            calc = (calc * 88) / 100;  //was 93, dropped to 88
        //think may lower this a bit more?
        //if I drop to .8 (won't actually) it'd effectively be enough to lower a stat stage drop to the next stage down

        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_COMPOUND_EYES
            || GetBattlerAbility(gBattlerAttacker) == ABILITY_ILLUMINATE)   
            calc = (calc * 130) / 100; // 1.3 compound eyes boost

        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_VICTORY_STAR
        ||  GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_VICTORY_STAR) //nvm acc calc is trash boosting to equal speed boost
            calc = (calc * 120) / 100; // 1.1 victory star boost / seems small but is enough for effective acc

        //when I get around to it, safety goggles item should also go on these I thnk
        //hold effect already set but think will just setup like umbrella
        //done wrapped it into weather affected
        if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SANDSTORM_ANY) 
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_ROCK)
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_STEEL)
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GROUND)
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_RUSH
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_VEIL
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_FORCE
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_WIND_RIDER    //addition since is wind move
        && !DoesSideHaveAbility(gBattlerAttacker, ABILITY_CLOUD_NINE) //need test hope works
        && gBattleMons[gBattlerAttacker].species != SPECIES_CASTFORM)
            calc = (calc * 90) / 100; // new 10% sandstorm loss (extra effect given since hail got extra stuff) changed to 5%, changed back given mudsport changes

        //trap effect, //changed so doesn't stack w sandstorm
        if (((gBattleMons[gBattlerAttacker].status4 & STATUS4_SAND_TOMB)
        && IsBlackFogNotOnField())
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_ROCK)
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_STEEL)
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GROUND)
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_RUSH
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_VEIL
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_FORCE
        && gBattleMons[gBattlerAttacker].species != SPECIES_CASTFORM)
        {
            calc = (calc * 80) / 100; //since most mon that have this also have access to sandstorm or are in desert made less punishing
            //moveAcc = (moveAcc * 60) / 100; //euivalent of a 2 stage acc drop
        }//leaving keen eye and sixth sense out of this and sandstorm acc drop, 
        //as special exclusions to strengthen affect/mechanic
        //realize that 75 is one stat stage drop, and since its temporary effect
        //I think will make this 80% and have it actually stack w sandstorm
        //at those levels its just slightly more than a full stat drop
        //but again only for the duration of both effects


        if (GetBattlerAbility(gBattlerTarget) == ABILITY_SAND_VEIL && IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SANDSTORM_ANY))
            calc = (calc * 80) / 100; // 1.2 sand veil loss
        if (GetBattlerAbility(gBattlerTarget) == ABILITY_SNOW_CLOAK && IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_HAIL_ANY))
            calc = (calc * 80) / 100; //
        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_HUSTLE && IsPhysicalMove(gBattlerAttacker,move)) //can put status based evasion/accuracy effects here
            calc = (calc * 95) / 100; // 20% hustle loss   removed low accuracy effcts,  so changed to 5% accuracy drop

        
        if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATED_WITH(battlerAtk)) //need to figure out how to lower evasion to go along with these accuracy boosts.
            calc = (calc * 140) / 100;
           // evasionStage = 3;
        if ((gBattleMons[battlerDef].status2 & STATUS2_CONFUSION) && defAbility != ABILITY_TANGLED_FEET) //thought instead of self attack, make confusion chance to change move target to random
            calc = (calc * 120) / 100; //that way they're still doing the same move, but they also have chance to hit attack themselves with it .
            //evasionStage = 5; // with that there should be as much benefit as danger in being confused, singled moves could hit everyone, etc. random & interesting..

        if ((defAbility == ABILITY_TANGLED_FEET) && gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
            calc = (calc * 50) / 100;
            //evasionStage *= 2;//raises evasion double but evasion calcs different so thats +3 intead of +2
        //12 stage base is 6 goes up to 12 & down to 0

        if (gBattleMons[battlerDef].status2 & STATUS2_WRAPPED)
                calc = (calc * 115) / 100;//  should still select normally before hand, but it just change when executed.
            //evasionStage = 3;
        if (gBattleMons[battlerDef].status4 & ITS_A_TRAP_STATUS4)  //I hpoe this works
            calc = (calc * 115) / 100;//  should still select normally before hand, but it just change when executed.
            //evasionStage = 3;
        //if (gBattleMons[battlerDef].status1 & ITS_A_TRAP_STATUS1)  //I hpoe this works
        //    calc = (calc * 115) / 100;//  should still select normally before hand, but it just change when executed.
            //evasionStage = 3; //note need to add logic for trap effects for pokemon catching,
            //don't use dodge pokeball effect when trapped, and add slight increase to catch chance, I think make it less than status chance but make it inclusive
            //so they stack

        if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP) { //.target = MOVE_TARGET_SELECTED, 
            if (IS_BATTLER_OF_TYPE(battlerDef,TYPE_PSYCHIC)) //important chek this think have function for type checking
                calc = (calc * 105) / 100; // to take advantage of these buffs I want to have a button to display real move accuracy in battle. maybe L
            else
                //     calc = (calc * 260) / 100; // gBattleMoves[gCurrentMove].target that's the comamnd I need, then just set the target I want
                calc = (calc * 160) / 100;//if I set it random % I can do more with it, I can make it use the normal confused hit itself, text command if it lands on target user.
        }
        if (gBattleMons[battlerDef].status1 & STATUS1_BURN)
                   calc = (calc * 110) / 100;
            //evasionStage = 4;
        if (gBattleMons[battlerDef].status1 & STATUS1_POISON) // I think I may remove the accuracy buff and just keep evasion drop, or make it more severe.
            calc = (calc * 110) / 100; //depends on how evasion works, if lowered evasion alone increases chance of move hitting, then I don't need accuracy buff.
         //   evasionStage = 4;
        if (gBattleMons[battlerDef].status1 & STATUS1_FREEZE)
            calc = (calc * 160) / 100;
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS) //ok evasion and accuracy stages are put together, so I'll just use evasion.
            calc = (calc * 130) / 100;
          //  evasionStage = 3;
        if (gBattleMons[battlerDef].status1 & STATUS1_TOXIC_POISON)
            calc = (calc * 115) / 100;
            //evasionStage = 3;


        if (defHoldEffect == HOLD_EFFECT_EVASION_UP)
            calc = (calc * (100 - defParam)) / 100;
        // Attacker's hold effect - took cleaned up version from EE
        switch (atkHoldEffect)
        {
        case HOLD_EFFECT_WIDE_LENS:
            calc = (calc * (100 + atkParam)) / 100;
            break;
        case HOLD_EFFECT_ZOOM_LENS:
            if (GetBattlerTurnOrderNum(battlerAtk) > GetBattlerTurnOrderNum(battlerDef))
                calc = (calc * (100 + atkParam)) / 100;
            break;
        }

        if (gProtectStructs[battlerAtk].usedMicleBerry)
        {
            gProtectStructs[battlerAtk].usedMicleBerry = FALSE;
            if (atkAbility == ABILITY_RIPEN)
                calc = (calc * 140) / 100;  // ripen gives 40% acc boost
            else
                calc = (calc * 120) / 100;  // 20% acc boost
        }

        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            calc = (calc * 5) / 3; // 1.66 Gravity acc boost

        return calc;
}

//vsonic no brain power left look later
//into why this clears destiny bond, action yes no?
static void SetDmgHazardsBattlescript(u8 battlerId, u8 multistringId)
{
    gBattleMons[battlerId].status2 &= ~STATUS2_DESTINY_BOND;
    gHitMarker &= ~HITMARKER_DESTINYBOND;
    gBattleScripting.battler = battlerId;
    gBattleCommunication[MULTISTRING_CHOOSER] = multistringId;

    BattleScriptPushCursor();
    if (gBattlescriptCurrInstr[1] == BS_TARGET)
        gBattlescriptCurrInstr = BattleScript_DmgHazardsOnTarget;
    else if (gBattlescriptCurrInstr[1] == BS_ATTACKER)
        gBattlescriptCurrInstr = BattleScript_DmgHazardsOnAttacker;
    else
        gBattlescriptCurrInstr = BattleScript_DmgHazardsOnFaintedBattler;
}

/*u32 IsAbilityPreventingEscape(u32 battlerId)   copied here to understand how to make ability search funciton, escape prevention already implemented
{
    u32 id;
    #if B_GHOSTS_ESCAPE >= GEN_6
        if (IS_BATTLER_OF_TYPE(battlerId, TYPE_GHOST))
            return 0;
    #endif
    #if B_SHADOW_TAG_ESCAPE >= GEN_4
        if ((id = IsAbilityOnOpposingSide(battlerId, ABILITY_SHADOW_TAG)) && GetBattlerAbility(battlerId) != ABILITY_SHADOW_TAG)
    #else
        if (id = IsAbilityOnOpposingSide(battlerId, ABILITY_SHADOW_TAG))
    #endif
        return id;
    if ((id = IsAbilityOnOpposingSide(battlerId, ABILITY_ARENA_TRAP)) && IsBattlerGrounded(battlerId))
        return id;
    if ((id = IsAbilityOnOpposingSide(battlerId, ABILITY_MAGNET_PULL)) && IS_BATTLER_OF_TYPE(battlerId, TYPE_STEEL))
        return id;

    return 0;


    if ((i = IsAbilityPreventingEscape(gActiveBattler)))    since 0 in the function means no ability they add 1 in the function return
    {                                                           when its used it then subtracts 1 to get the actual battlerId
        gBattleScripting.battler = i - 1;       -important line
        gLastUsedAbility = gBattleMons[i - 1].ability;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PREVENTS_ESCAPE;
        return 2;
    }

    u32 IsAbilityOnSide(u32 battlerId, u32 ability)
{
    if (IsBattlerAlive(battlerId) && GetBattlerAbility(battlerId) == ability)
        return battlerId + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battlerId)) && GetBattlerAbility(BATTLE_PARTNER(battlerId)) == ability)
        return BATTLE_PARTNER(battlerId) + 1;
    else
        return 0;
}

THIS MAY BE THE KEY,  they use a constant to return the battlerId of the mon with the ability they are looking for at top with id
 because the abilityonside function uses id + 1 to identify the battler

 I can use i - 1 to set the mon affected by battlescript, and have it use their id
 that way I can make it all work on one script using battle attacker instead of needin to make two,
 long as I set gactivebattler to battlerattacker
 
 From there I just need to call the relevant script include a return at the bottom instead of an end script.
 set activebattler back to me i.e use id + 1 and continue the normal switch in script from there.
 and I should be able to do all that from the switch in effect function

 because things execute in order I'll need to put my switch code and everything
 AFTER the neutralizing gas code but before the hazard code. 

 order of steps,switch in, if gactivebattler on opposite side == ability
 gactivebattler or gBattleScripting.battler = i - 1;
 
 then use switch case to pick the ability
 for each ability case make a battlescript that activates like normal ability but with return instead of end condition
 in the function switch case put a call for that battle script
 and after that put battlerid back on switching in mon with 
 gactivebattler or gBattleScripting.battler = i + 1;        IMPORTANT need to identify if these 2 are different or have identical use here

 (only need make new battlescript if original ability activate battlescript doesn't end in return)

 -edit- ok I now understand the +1  and -1 don't work that way so what I may need to do is save the
 initial battlerid before the switch to another constant value (j)  so I can just set gactivebattler or battlescript.battler back that way
 by just using an "="  -edit end 5/30/22-

 then have it continue through the rest of the switchineffects function as normal.
 may have to put a return in the function for that so it continues to the outside effects
 5-29-22  IMPORTANT
}*/

static void atk52_switchineffects(void) //important, think can put ability reset here.. also prob need add stealth rock toxic spikes to this
{ //yeah realized this is where I need to change it, need to add activation of switch in abilities again here
    //actually side status already does what I want, what if I just make intimidate and
    //and the like side status?
    //yeah I believe I can do trace intimidate resets here

    //will use a switch case to make this more efficient
    //use GetBattlerAbility function to returnability 
    //with IsAbilityOnOpposingSide function think if I put it inside the other
    //it'll return the battle id, then I can use that to return the ability itself
    //
    //use switch to check if its intimidate, trace, or synchronize

    //intimidate lower avtivebattler attack stat, and play the intimidate text
    //since can't use intimidate script will have to make new text to run

    //for trace check if ability is already the same as the mon with trace
    //and give a percent chance to reactivate trace for a new ability
    //or just make it always activate just to reveil what ability is.
    //yeah I like that better       (since I don't use ability pop up)

    //make synchronize the one that works on chance,        -try 40% first
    //and change ability so self afflicted status also activates the ability

    //all abilities use active battler for targetting
    s32 i; 
    s32 j;

    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]); //this makes gActiveBattler the battler the script is referencing
    j = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]); //when it uses atker or target on the script its different from gBattlescriptCurrInstr[1] itself
    UpdateSentPokesToOpponentValue(gActiveBattler);
    gHitMarker &= ~(HITMARKER_FAINTED(gActiveBattler));
    gSpecialStatuses[gActiveBattler].faintedHasReplacement = 0;


    //side = GetBattlerSide(gBattleScripting.battler); //added for switch case for intimidate I'll add, will be same as trygetintimidatetarget
    //will make new battle script to be called, identical to intimidate but switching target with attacker
    
    // Neutralizing Gas announces itself before hazards
    //potentialy should hvae swapped this for abilitybattleeffects  neutralizing gas case, idk.
    if (gBattleMons[gActiveBattler].ability == ABILITY_NEUTRALIZING_GAS && gSpecialStatuses[gActiveBattler].announceNeutralizingGas == 0)
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_NEUTRALIZING_GAS;
        gSpecialStatuses[gActiveBattler].announceNeutralizingGas = TRUE;
        gBattlerAbility = gActiveBattler;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_SwitchInAbilityMsgRet;
    }

    else if (gBattleMons[gActiveBattler].ability == ABILITY_IMMUTABLE_WIND && gSpecialStatuses[gActiveBattler].announceNeutralizingGas == 0)
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_IMMUTABLE_WIND;
        gSpecialStatuses[gActiveBattler].announceNeutralizingGas = TRUE;
        gBattlerAbility = gActiveBattler;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_SwitchInAbilityMsgRet;
    }
     
    //base fire red spike/hazard logic
    /*if (!(gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_SPIKES_DAMAGED)
     && (gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_SPIKES)
     && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_FLYING)
     && gBattleMons[gActiveBattler].ability != ABILITY_LEVITATE
     && !IsBattlerGrounded(gActiveBattler)) //if grounded works can remove flying and levitate check
    {
        u8 spikesDmg; //I have no idea what this function is doing other than setting spike damage

        gSideStatuses[GetBattlerSide(gActiveBattler)] |= SIDE_STATUS_SPIKES_DAMAGED;
        spikesDmg = (5 - gSideTimers[GetBattlerSide(gActiveBattler)].spikesAmount) * 2;
        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / (spikesDmg);
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleScripting.battler = gActiveBattler;
        BattleScriptPushCursor();
        if (gBattlescriptCurrInstr[1] == BS_TARGET)
            gBattlescriptCurrInstr = BattleScript_SpikesOnTarget;
        else if (gBattlescriptCurrInstr[1] == BS_ATTACKER)
            gBattlescriptCurrInstr = BattleScript_SpikesOnAttacker;
        else
            gBattlescriptCurrInstr = BattleScript_SpikesOnFaintedBattler;//spike logic and damamge formula
    }*/
    if (!(gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_SPIKES_DAMAGED)
        && (gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_SPIKES)
        && GetBattlerAbility(gActiveBattler) != ABILITY_MAGIC_GUARD
        && IsBattlerAffectedByHazards(gActiveBattler, FALSE)
        && IsBattlerGrounded(gActiveBattler))
    {
        u8 spikesDmg = (5 - gSideTimers[GetBattlerSide(gActiveBattler)].spikesAmount) * 2;
        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / (spikesDmg);
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;

        gSideStatuses[GetBattlerSide(gActiveBattler)] |= SIDE_STATUS_SPIKES_DAMAGED;
        SetDmgHazardsBattlescript(gActiveBattler, 0);
    }
    else if (!(gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_STEALTH_ROCK_DAMAGED)
        && (gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_STEALTH_ROCK)
        && IsBattlerAffectedByHazards(gActiveBattler, FALSE)
        && GetBattlerAbility(gActiveBattler) != ABILITY_MAGIC_GUARD
        && IsBlackFogNotOnField())
    {
        gSideStatuses[GetBattlerSide(gActiveBattler)] |= SIDE_STATUS_STEALTH_ROCK_DAMAGED;
        gBattleMoveDamage = GetStealthHazardDamage(gBattleMoves[MOVE_STEALTH_ROCK].type, gActiveBattler);
        //also defined in ai upgrade, do something later vsonic
        if (gBattleMoveDamage != 0)
            SetDmgHazardsBattlescript(gActiveBattler, 1);
    }
    else if (!(gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_TOXIC_SPIKES_DAMAGED)
        && (gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_TOXIC_SPIKES)
        && IsBattlerGrounded(gActiveBattler))
    {
        gSideStatuses[GetBattlerSide(gActiveBattler)] |= SIDE_STATUS_TOXIC_SPIKES_DAMAGED;
        if (IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_POISON)) // Absorb the toxic spikes.
        {
            gSideStatuses[GetBattlerSide(gActiveBattler)] &= ~SIDE_STATUS_TOXIC_SPIKES;
            gSideTimers[GetBattlerSide(gActiveBattler)].toxicSpikesAmount = 0;
            gBattleScripting.battler = gActiveBattler;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_ToxicSpikesAbsorbed;
        }
        else if (IsBattlerAffectedByHazards(gActiveBattler, TRUE))
        {
            if (!(gBattleMons[gActiveBattler].status1 & STATUS1_ANY)
                && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_STEEL)
                && GetBattlerAbility(gActiveBattler) != ABILITY_IMMUNITY
                && !IsAbilityOnSide(gActiveBattler, ABILITY_PASTEL_VEIL)
                && !(gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_SAFEGUARD)
                && !(gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN))
            {
                if (gSideTimers[GetBattlerSide(gActiveBattler)].toxicSpikesAmount >= 2)
                    gBattleMons[gActiveBattler].status1 |= STATUS1_TOXIC_POISON;
                else
                    gBattleMons[gActiveBattler].status1 |= STATUS1_POISON;

                BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, sizeof(gBattleMons[gActiveBattler].status1), &gBattleMons[gActiveBattler].status1);
                MarkBattlerForControllerExec(gActiveBattler);
                gBattleScripting.battler = gActiveBattler;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ToxicSpikesPoisoned;
            }
        }
    }
    else if (!(gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_STICKY_WEB_DAMAGED)
        && (gSideStatuses[GetBattlerSide(gActiveBattler)] & SIDE_STATUS_STICKY_WEB)
        && IsBattlerAffectedByHazards(gActiveBattler, FALSE)
        && IsBattlerGrounded(gActiveBattler))
    {
        gSideStatuses[GetBattlerSide(gActiveBattler)] |= SIDE_STATUS_STICKY_WEB_DAMAGED;
        gBattleScripting.battler = gActiveBattler;
        SET_STATCHANGER(STAT_SPEED, 2, TRUE);
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_StickyWebOnSwitchIn;
    }
    //end of hazard
    else
    {
        if (gBattleMons[gActiveBattler].ability == ABILITY_TRUANT)
            gDisableStructs[gActiveBattler].truantCounter = 1;
        if (!AbilityBattleEffects(ABILITYEFFECT_ON_SWITCHIN, gActiveBattler, 0, 0, 0)
         && !ItemBattleEffects(ITEMEFFECT_ON_SWITCH_IN, gActiveBattler, FALSE))
        {
            gSideStatuses[GetBattlerSide(gActiveBattler)] &= ~(SIDE_STATUS_SPIKES_DAMAGED);

            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gBattlerByTurnOrder[i] == gActiveBattler)
                    gActionsByTurnOrder[i] = B_ACTION_CANCEL_PARTNER;
            }
            for (i = 0; i < gBattlersCount; ++i)
            {
                u16 *hpOnSwitchout = &gBattleStruct->hpOnSwitchout[GetBattlerSide(i)];
                *hpOnSwitchout = gBattleMons[i].hp;
            }

            if (gBattlescriptCurrInstr[1] == 5)
            {
                u32 hitmarkerFaintBits = gHitMarker >> 0x1C;

                ++gBattlerFainted;
                while (TRUE)
                {
                    if (hitmarkerFaintBits & gBitTable[gBattlerFainted] && !(gAbsentBattlerFlags & gBitTable[gBattlerFainted]))
                        break;
                    if (gBattlerFainted >= gBattlersCount)
                        break;
                    ++gBattlerFainted;
                }
            }
            gBattlescriptCurrInstr += 2;
        }
    }  //end of else, think I can put other logic for switchin below this

    /*if (gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK)   //i don't remember why this is here but switch in anti-heal would be amazing
        //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK; //vsonic        //think setup heal block switch in ability
    {
        break;
    }*/

    //start of extra code, 1st attempt at reactivating switch in abilities,  think just delete at start over  in battle_util.c as new abilityeffect
    //believe the switch case and will put the id of the battle on variable i
    /*for (i = 0; i < gBattlersCount; ++i)
    {//will need to put "gBattleScripting.battler = i - 1;" in top of every switch case
        //syntax was wrong before made an adjustment so hopefully this works/or at least copmiles
        
        if (IsAbilityOnOpposingSide(gActiveBattler, gBattleMons[i].ability)) {

            switch (gBattleMons[i].ability) //I don't understand what a switch is actually doing apparently
            {
            case ABILITY_INTIMIDATE:
                //gBattleScripting.battler = i - 1;
                gActiveBattler = i - 1; //should set current script "target" to mon with ability found from switch case
                //gLastUsedAbility = gBattleMons[gActiveBattler].ability;  other part of intimidate activation already does this
                BattleScriptPushCursor(); //I may need to set intimidatedMon to 0
                gBattlescriptCurrInstr = BattleScript_IntimidateActivates;
                gActiveBattler = j; //should reset activebattler back to original target for post switch actions
                break;
            case ABILITY_ANTICIPATION:
                gActiveBattler = i - 1;
                gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ReactivateIntimidate;
                gActiveBattler = j;
                break;
            case ABILITY_FRISK:
                gActiveBattler = i - 1;
                gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ReactivateIntimidate;
                gActiveBattler = j;
                break;
            case ABILITY_FOREWARN:
                gActiveBattler = i - 1;
                gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ReactivateIntimidate;
                gActiveBattler = j;
                break;
            case ABILITY_TRACE:
                gActiveBattler = i - 1;
                gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ReactivateIntimidate;
                gActiveBattler = j;
                break;
            case ABILITY_SYNCHRONIZE:
                gActiveBattler = i - 1;
                gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ReactivateIntimidate;
                gActiveBattler = j;
                break;
            }
        }
    } */   
}

//check clean repo if trainer slide in is at right position
//thnink snifted backgrounds may need to move oponent to right side?
static void atk53_trainerslidein(void) 
{
    if (!gBattlescriptCurrInstr[1])
        gActiveBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    else
        gActiveBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    BtlController_EmitTrainerSlide(0);
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 2;
}

static void atk54_playse(void)
{
    gActiveBattler = gBattlerAttacker;
    BtlController_EmitPlaySE(0, T2_READ_16(gBattlescriptCurrInstr + 1));
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 3;
}

static void atk55_fanfare(void)
{
    gActiveBattler = gBattlerAttacker;
    BtlController_EmitPlayFanfare(0, T2_READ_16(gBattlescriptCurrInstr + 1));
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 3;
}

static void atk56_playfaintcry(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    BtlController_EmitFaintingCry(0);
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 2;
}

static void atk57_endlinkbattle(void)
{
    gActiveBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    BtlController_EmitEndLinkBattle(0, gBattleOutcome);
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 1;
}

static void atk58_returntoball(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    BtlController_EmitReturnMonToBall(0, 1);
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 2;
}

static void atk59_handlelearnnewmove(void) //specific to in battle move learn?
{
    CMD_ARGS(const u8 *learnedMovePtr, const u8 *nothingToLearnPtr, bool8 isFirstMove);
    const u8 *learnedMovePtr = cmd->learnedMovePtr; //1st ptr
    const u8 *nothingToLearnPtr = cmd->nothingToLearnPtr; //2nd ptr

    u16 learnMove = MonTryLearningNewMove(&gPlayerParty[gBattleStruct->expGetterMonId], cmd->isFirstMove);
    
    while (learnMove == MON_ALREADY_KNOWS_MOVE) //normal but when would function ever be 0xFFFE?  //think found,   MON_ALREADY_KNOWS_MOVE ?
        learnMove = MonTryLearningNewMove(&gPlayerParty[gBattleStruct->expGetterMonId], 0);
    if (learnMove == MOVE_NONE) //don't learn move or nothing to learn
    {
        gBattlescriptCurrInstr = nothingToLearnPtr;
    }
    else if (learnMove == MON_HAS_MAX_MOVES) //not a move?   //think LEVEL_UP_END ?
    {
        gBattlescriptCurrInstr = cmd->nextInstr; //this is issue, 
    } //meaning problem is within script BattleScript_AskToLearnMove
    else
    {
        gActiveBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT); //specifically this
        if (gBattlerPartyIndexes[gActiveBattler] == gBattleStruct->expGetterMonId
         && !(gBattleMons[gActiveBattler].status2 & STATUS2_TRANSFORMED)) //with transform change think can remove this condition
        {
            GiveMoveToBattleMon(&gBattleMons[gActiveBattler], learnMove); //oh wait no this just means don't add the move to the mon in battle, so yeah keep transform block
        }
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        {
            gActiveBattler = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
            if (gBattlerPartyIndexes[gActiveBattler] == gBattleStruct->expGetterMonId
             && !(gBattleMons[gActiveBattler].status2 & STATUS2_TRANSFORMED))
            {
                GiveMoveToBattleMon(&gBattleMons[gActiveBattler], learnMove);
            }
        }
        gBattlescriptCurrInstr = learnedMovePtr;
    }
}

static void atk5A_yesnoboxlearnmove(void)
{
     CMD_ARGS(const u8 *forgotMovePtr);

    u8 movePosition = GetMoveSlotToReplace(); //for some reason only works on top line
    u16 moveId = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_MOVE1 + movePosition); //neeed to change 1 of these
    gActiveBattler = 0;//Kurausukun & The Sylph is in  cleared it up for me, variables have to be declared first at the top of a code block above gactivebat in this case

    switch (gBattleScripting.learnMoveState)
    {
    case 0:
        HandleBattleWindow(0x17, 8, 0x1D, 0xD, 0);
        BattlePutTextOnWindow(gText_BattleYesNoChoice, 0xE);
        ++gBattleScripting.learnMoveState; //goes to next case
        gBattleCommunication[CURSOR_POSITION] = 0;  //sets cursor default position
        BattleCreateYesNoCursorAt();
        break;
    case 1:
        if (JOY_NEW(DPAD_UP) && gBattleCommunication[CURSOR_POSITION] != 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 0;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(DPAD_DOWN) && gBattleCommunication[CURSOR_POSITION] == 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 1;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            if (gBattleCommunication[CURSOR_POSITION] == 0)
            {
                HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
                ++gBattleScripting.learnMoveState;  //case 2
            }
            else
            {
                gBattleScripting.learnMoveState = 8; 
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            gBattleScripting.learnMoveState = 8; //not sure why but this line needs 8
        } //even though 7 works above...because they were both wrong
        break;
    case 2: //should be selection for move to forget, continues after a move is chosen
        if (!gPaletteFade.active)
        {
            FreeAllWindowBuffers();
            ShowSelectMovePokemonSummaryScreen(gPlayerParty, gBattleStruct->expGetterMonId, gPlayerPartyCount - 1, ReshowBattleScreenAfterMenu, gMoveToLearn);
            ++gBattleScripting.learnMoveState; //above line is the problem^  //specificallyu expgetter
                                                //nvm this isn't' the problem, its showing the summary screen for said mon, but buffering the moves is done separately THAT'S the issue
                                                //as I see its showing the correct mon name and image, but if I change 2nd value it shows a different mon
        }
        break;
    case 3: //replaces move whne you answer yes, if it can be deleted
        if (!gPaletteFade.active && gMain.callback2 == BattleMainCB2)
        {
            //u8 movePosition = GetMoveSlotToReplace();
            PREPARE_MOVE_BUFFER(gBattleTextBuff2, moveId) //sets move forgotten to buffer2

            if (movePosition == 4) //I need to save this value to use in later case, so hope works the valeu of move selected and doesn't overwrite
            {
                gBattleScripting.learnMoveState = 8;
            }
            else
            {
                ++gBattleScripting.learnMoveState;
            }
        }
        break;
    case 4:
        PrepareStringBattle(STRINGID_CONFIRMFORGETMOVE, gActiveBattler); //should print confirm text
        ++gBattleScripting.learnMoveState;
        break;
    case 5:
        HandleBattleWindow(0x17, 8, 0x1D, 0xD, 0);
        BattlePutTextOnWindow(gText_BattleYesNoChoice, B_WIN_YESNO);
        ++gBattleScripting.learnMoveState;
        gBattleCommunication[CURSOR_POSITION] = 0;
        BattleCreateYesNoCursorAt();
        break;
    case 6:
        if (JOY_NEW(DPAD_UP) && gBattleCommunication[CURSOR_POSITION] != 0)//navigation of yes/no
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 0;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(DPAD_DOWN) && gBattleCommunication[CURSOR_POSITION] == 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 1;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(A_BUTTON))//actual selection for do you want to forget move
        {
            PlaySE(SE_SELECT);

            if (gBattleCommunication[1] != 0) //if select no
            {
                //gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1); //follow pointer
                HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
                gBattlescriptCurrInstr = cmd->nextInstr;// don't jump don't forget move progress to next script
            }
            else //move to next script if select yes
                //gBattlescriptCurrInstr += 5;  won't to use pointer and learn move just need to continue in this case
            {
                HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
                //gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1); bruh this extra jump was literaly the problem!!
                ++gBattleScripting.learnMoveState;
                //want to continue to next state and do move replacement and jump  everything else just move to next script

            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            //gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1); //follow pointer
            HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
            gBattlescriptCurrInstr = cmd->nextInstr; // don't jump don't forget move progress to next script
        }
        break;
    case 7: //put rest of move replace heree
        if (!gPaletteFade.active && gMain.callback2 == BattleMainCB2)
        {
            //u8 movePosition = GetMoveSlotToReplace();

            if (movePosition != 4)
            {
                //u16 moveId = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_MOVE1 + movePosition);

                gBattlescriptCurrInstr = cmd->forgotMovePtr; //does jump to 123 poof
                //PREPARE_MOVE_BUFFER(gBattleTextBuff2, moveId) //sets move forgotten to buffer2
                    RemoveMonPPBonus(&gPlayerParty[gBattleStruct->expGetterMonId], movePosition);
                SetMonMoveSlot(&gPlayerParty[gBattleStruct->expGetterMonId], gMoveToLearn, movePosition);
                if (gBattlerPartyIndexes[0] == gBattleStruct->expGetterMonId
                    && !(gBattleMons[0].status2 & STATUS2_TRANSFORMED)
                    && !(gDisableStructs[0].mimickedMoves & gBitTable[movePosition]))
                {//believe condition specific to in  battle level up move learning
                    RemoveBattleMonPPBonus(&gBattleMons[0], movePosition);
                    SetBattleMonMoveSlot(&gBattleMons[0], gMoveToLearn, movePosition);
                }
                if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
                    && gBattlerPartyIndexes[2] == gBattleStruct->expGetterMonId
                    && !(gBattleMons[2].status2 & STATUS2_TRANSFORMED)
                    && !(gDisableStructs[2].mimickedMoves & gBitTable[movePosition]))
                {
                    RemoveBattleMonPPBonus(&gBattleMons[2], movePosition);
                    SetBattleMonMoveSlot(&gBattleMons[2], gMoveToLearn, movePosition);
                }
            }
        }
        break;
    case 8:  //case 4
        HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
        gBattlescriptCurrInstr = cmd->nextInstr;  //skip jump ptr, move to next instruction
        break;
    case 9: //not used?
        if (!gBattleControllerExecFlags)
        {

            gBattleScripting.learnMoveState = 2;
        }
        break;
    
    }
}

static void atk5B_yesnoboxstoplearningmove(void)
{
    switch (gBattleScripting.learnMoveState)
    {
    case 0:
        HandleBattleWindow(0x17, 8, 0x1D, 0xD, 0);
        BattlePutTextOnWindow(gText_BattleYesNoChoice, 0xE);
        ++gBattleScripting.learnMoveState;
        gBattleCommunication[CURSOR_POSITION] = 0;
        BattleCreateYesNoCursorAt();
        break;
    case 1:
        if (JOY_NEW(DPAD_UP) && gBattleCommunication[CURSOR_POSITION] != 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 0;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(DPAD_DOWN) && gBattleCommunication[CURSOR_POSITION] == 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 1;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);

            if (gBattleCommunication[1] != 0)
                gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
            else
                gBattlescriptCurrInstr += 5;
            HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
            HandleBattleWindow(0x17, 0x8, 0x1D, 0xD, WINDOW_CLEAR);
        }
        break;
    }
}

static void atk5C_hitanimation(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
    {
        gBattlescriptCurrInstr += 2;
    }
    else if (!(gHitMarker & HITMARKER_IGNORE_SUBSTITUTE)
          || !(gBattleMons[gActiveBattler].status2 & STATUS2_SUBSTITUTE)
          || gDisableStructs[gActiveBattler].substituteHP == 0)
    {
        BtlController_EmitHitAnimation(0);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 2;
    }
    else
    {
        gBattlescriptCurrInstr += 2;
    }
}

static void atk5D_getmoneyreward(void)
{
    u32 i = 0;
    u32 moneyReward;
    u8 lastMonLevel = 0;

    const struct TrainerMonItemCustomMoves *party4; //This needs to be out here

    if (gBattleOutcome == B_OUTCOME_WON)
    {
        /*if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
        {
            moneyReward = gBattleResources->secretBase->party.levels[0] * 20 * gBattleStruct->moneyMultiplier;
        }
        else
        {*/
            switch (gTrainers[gTrainerBattleOpponent_A].partyFlags)
            {
            case 0:
                {
                    const struct TrainerMonNoItemDefaultMoves *party1 = gTrainers[gTrainerBattleOpponent_A].party.NoItemDefaultMoves;
                    
                    lastMonLevel = party1[gTrainers[gTrainerBattleOpponent_A].partySize - 1].lvl;
                }
                break;
            case F_TRAINER_PARTY_CUSTOM_MOVESET:
                {
                    const struct TrainerMonNoItemCustomMoves *party2 = gTrainers[gTrainerBattleOpponent_A].party.NoItemCustomMoves;
                    
                    lastMonLevel = party2[gTrainers[gTrainerBattleOpponent_A].partySize - 1].lvl;
                }
                break;
            case F_TRAINER_PARTY_HELD_ITEM:
                {
                    const struct TrainerMonItemDefaultMoves *party3 = gTrainers[gTrainerBattleOpponent_A].party.ItemDefaultMoves;
                    
                    lastMonLevel = party3[gTrainers[gTrainerBattleOpponent_A].partySize - 1].lvl;
                }
                break;
            case (F_TRAINER_PARTY_CUSTOM_MOVESET | F_TRAINER_PARTY_HELD_ITEM):
                {
                    party4 = gTrainers[gTrainerBattleOpponent_A].party.ItemCustomMoves;
                    
                    lastMonLevel = party4[gTrainers[gTrainerBattleOpponent_A].partySize - 1].lvl;
                }
                break;
            }
            for (; gTrainerMoneyTable[i].classId != 0xFF; i++)
            {
                if (gTrainerMoneyTable[i].classId == gTrainers[gTrainerBattleOpponent_A].trainerClass)
                    break;
            }
            party4 = gTrainers[gTrainerBattleOpponent_A].party.ItemCustomMoves; // Needed to Match. Has no effect.
            moneyReward = 4 * lastMonLevel * gBattleStruct->moneyMultiplier * (gBattleTypeFlags & BATTLE_TYPE_DOUBLE ? 2 : 1) * gTrainerMoneyTable[i].value;
        //}
        AddMoney(&gSaveBlock1Ptr->money, moneyReward);
    }
    else
    {
        moneyReward = ComputeWhiteOutMoneyLoss();
    }
    PREPARE_WORD_NUMBER_BUFFER(gBattleTextBuff1, 5, moneyReward);
    if (moneyReward)
        gBattlescriptCurrInstr += 5;
    else
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
}

static void atk5E(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);

    switch (gBattleCommunication[0])
    {
    case 0:
        BtlController_EmitGetMonData(0, REQUEST_ALL_BATTLE, 0);
        MarkBattlerForControllerExec(gActiveBattler);
        ++gBattleCommunication[0];
        break;
    case 1:
         if (!gBattleControllerExecFlags)
         {
            s32 i;
            struct BattlePokemon *bufferPoke = (struct BattlePokemon *) &gBattleBufferB[gActiveBattler][4];
            
            for (i = 0; i < MAX_MON_MOVES; ++i)
            {
                gBattleMons[gActiveBattler].moves[i] = bufferPoke->moves[i];
                gBattleMons[gActiveBattler].pp[i] = bufferPoke->pp[i];
            }
            gBattlescriptCurrInstr += 2;
         }
         break;
    }
}

static void atk5F_swapattackerwithtarget(void)
{
    gActiveBattler = gBattlerAttacker;
    gBattlerAttacker = gBattlerTarget;
    gBattlerTarget = gActiveBattler;
    if (gHitMarker & HITMARKER_SWAP_ATTACKER_TARGET)
        gHitMarker &= ~(HITMARKER_SWAP_ATTACKER_TARGET);
    else
        gHitMarker |= HITMARKER_SWAP_ATTACKER_TARGET;
    ++gBattlescriptCurrInstr;
}

static void atk60_incrementgamestat(void)
{
    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        IncrementGameStat(gBattlescriptCurrInstr[1]);
    gBattlescriptCurrInstr += 2;
}

static void atk61_drawpartystatussummary(void)
{
    s32 i;
    struct Pokemon *party;
    struct HpAndStatus hpStatuses[PARTY_SIZE];

    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);

        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            party = gPlayerParty;
        else
            party = gEnemyParty;

        for (i = 0; i < PARTY_SIZE; ++i)
        {
            if (GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
             || GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
            {
                hpStatuses[i].hp = 0xFFFF;
                hpStatuses[i].status = 0;
            }
            else
            {
                hpStatuses[i].hp = GetMonData(&party[i], MON_DATA_HP);
                hpStatuses[i].status = GetMonData(&party[i], MON_DATA_STATUS);
            }
        }
        BtlController_EmitDrawPartyStatusSummary(0, hpStatuses, 1);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 2;
    }
}

static void atk62_hidepartystatussummary(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    BtlController_EmitHidePartyStatusSummary(0);
    MarkBattlerForControllerExec(gActiveBattler);
    gBattlescriptCurrInstr += 2;
}

static void atk63_jumptocalledmove(void) //can't tell differenc between what these do
{
    if (gBattlescriptCurrInstr[1]) //if not 0
        gCurrentMove = gCalledMove;
    else
        gChosenMove = gCurrentMove = gCalledMove;
    gBattlescriptCurrInstr = gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect];
}

//Used for only status1, eventually goes into chosenstatusanimation command
static void atk64_statusanimation(void)//eventually figure update this for spirit lock
{
    u8 isStatus1 = 1;
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        if (!(gStatuses3[gActiveBattler] & STATUS3_SEMI_INVULNERABLE)
         && gDisableStructs[gActiveBattler].substituteHP == 0
         && !(gHitMarker & HITMARKER_NO_ANIMATIONS))
        {
            BtlController_EmitStatusAnimation(0, isStatus1, gBattleMons[gActiveBattler].status1);
            MarkBattlerForControllerExec(gActiveBattler);
        }
        gBattlescriptCurrInstr += 2;
    }
}

//vsonic
//is just for status2 but eventually goes into chosenstatusanimation
static void atk65_status2animation(void) //use this for intimidate confuse effect make new battlescript with just this effect & a return /maybe not don't remembber why made note
{
    u32 wantedToAnimate;
    u8 isStatus2 = 2;

    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        wantedToAnimate = T1_READ_32(gBattlescriptCurrInstr + 2);
        if (!(gStatuses3[gActiveBattler] & STATUS3_SEMI_INVULNERABLE)
         && gDisableStructs[gActiveBattler].substituteHP == 0
         && !(gHitMarker & HITMARKER_NO_ANIMATIONS))
        {
            BtlController_EmitStatusAnimation(0, isStatus2, gBattleMons[gActiveBattler].status2 & wantedToAnimate);
            MarkBattlerForControllerExec(gActiveBattler);
        }
        gBattlescriptCurrInstr += 6;
    }
}

//STILL can't get the animation to play for this damn thing???
//everyting works corretly execept the new status, so dive into that smh
static void atk66_chosenstatusanimation(void) //filters for status 2, but then can play any animation, status2 or not
{
    u32 wantedStatus;
    u8 statusCat = gBattlescriptCurrInstr[2];

    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        wantedStatus = T1_READ_32(gBattlescriptCurrInstr + 3);
        if (!(gStatuses3[gActiveBattler] & STATUS3_SEMI_INVULNERABLE)
         && gDisableStructs[gActiveBattler].substituteHP == 0
         && !(gHitMarker & HITMARKER_NO_ANIMATIONS))
        {
            //takes true false as condition for logic if is status2 or not
            //fills logic for InitAndLaunchChosenStatusAnimation
            switch (statusCat)
            {
                case 1:
                    BtlController_EmitStatusAnimation(0, gBattlescriptCurrInstr[2], gBattleMons[gActiveBattler].status1 & wantedStatus);
                break;
                case 2:
                    BtlController_EmitStatusAnimation(0, gBattlescriptCurrInstr[2], gBattleMons[gActiveBattler].status2 & wantedStatus);
                break;
                case 3:
                    BtlController_EmitStatusAnimation(0, gBattlescriptCurrInstr[2], gStatuses3[gActiveBattler] & wantedStatus);
                break;
                case 4:
                    BtlController_EmitStatusAnimation(0, gBattlescriptCurrInstr[2], gBattleMons[gActiveBattler].status4 & wantedStatus);
                break;
            }
            MarkBattlerForControllerExec(gActiveBattler);
        }
        gBattlescriptCurrInstr += 7;
    }
}

static void atk67_yesnobox(void)
{
    switch (gBattleCommunication[0])
    {
    case 0:
        HandleBattleWindow(0x17, 8, 0x1D, 0xD, 0);
        BattlePutTextOnWindow(gText_BattleYesNoChoice, 0xE);
        ++gBattleCommunication[0];
        gBattleCommunication[CURSOR_POSITION] = 0;
        BattleCreateYesNoCursorAt();
        break;
    case 1:
        if (JOY_NEW(DPAD_UP) && gBattleCommunication[CURSOR_POSITION] != 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 0;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(DPAD_DOWN) && gBattleCommunication[CURSOR_POSITION] == 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 1;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(B_BUTTON))
        {
            gBattleCommunication[CURSOR_POSITION] = 1;
            PlaySE(SE_SELECT);
            HandleBattleWindow(0x17, 8, 0x1D, 0xD, WINDOW_CLEAR);
            ++gBattlescriptCurrInstr;
        }
        else if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            HandleBattleWindow(0x17, 8, 0x1D, 0xD, WINDOW_CLEAR);
            ++gBattlescriptCurrInstr;
        }
        break;
    }
}

static void atk68_cancelallactions(void)
{
    s32 i;

    for (i = 0; i < gBattlersCount; ++i)
        gActionsByTurnOrder[i] = B_ACTION_CANCEL_PARTNER;
    ++gBattlescriptCurrInstr;
}

// The same as 0x7, except there's no random damage multiplier.
static void atk69_adjustsetdamage(void)
{
    u8 holdEffect, param;

    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_SONAR)
    {
        if (gBattleMoves[gCurrentMove].flags & FLAG_SOUND)  //specifically for boosting sonic screech fixed dmg
        {
            gBattleMoveDamage = gBattleMoveDamage * 15;
            gBattleMoveDamage = gBattleMoveDamage / 10;
        }
    }

    if (gBattleMons[gBattlerTarget].item == ITEM_ENIGMA_BERRY)
    {
        holdEffect = gEnigmaBerries[gBattlerTarget].holdEffect;
        param = gEnigmaBerries[gBattlerTarget].holdEffectParam;
    }
    else
    {
        holdEffect = GetBattlerHoldEffect(gBattlerTarget, TRUE);
        param = ItemId_GetHoldEffectParam(gBattleMons[gBattlerTarget].item);
    }
    gPotentialItemEffectBattler = gBattlerTarget;
    
    if (holdEffect == HOLD_EFFECT_FOCUS_BAND && (Random() % 100) < param)
    {
        RecordItemEffectBattle(gBattlerTarget, holdEffect);
        gSpecialStatuses[gBattlerTarget].focusBanded = TRUE;
    }
    else if (holdEffect == HOLD_EFFECT_FOCUS_SASH && BATTLER_MAX_HP(gBattlerTarget))
    {
        RecordItemEffectBattle(gBattlerTarget, holdEffect);
        gSpecialStatuses[gBattlerTarget].focusSashed = TRUE;
    }
    else if (GetBattlerAbility(gBattlerTarget) == ABILITY_STURDY && BATTLER_MAX_HP(gBattlerTarget)) //gen 5 sturdy
    {
        RecordAbilityBattle(gBattlerTarget, ABILITY_STURDY);
        gSpecialStatuses[gBattlerTarget].sturdied = TRUE;
    }
    if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_SUBSTITUTE)
     && (gBattleMoves[gCurrentMove].effect == EFFECT_FALSE_SWIPE || gProtectStructs[gBattlerTarget].endured || gSpecialStatuses[gBattlerTarget].focusBanded || gSpecialStatuses[gBattlerTarget].focusSashed || gSpecialStatuses[gBattlerTarget].sturdied)
     && gBattleMons[gBattlerTarget].hp <= gBattleMoveDamage
     && (gMultiHitCounter == 0 || gMultiHitCounter == gMultiTask))
    {
        gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
        if (gProtectStructs[gBattlerTarget].endured)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_ENDURED;
        }
        else if (gSpecialStatuses[gBattlerTarget].focusBanded)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
        else if (gSpecialStatuses[gBattlerTarget].focusSashed)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedItem = gBattleMons[gBattlerTarget].item;
        }
        else if (gSpecialStatuses[gBattlerTarget].sturdied)
        {
            gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
            gLastUsedAbility = ABILITY_STURDY;
        }
    }
    ++gBattlescriptCurrInstr;
}


//realize should just put BS_checksecondaryItemslot
//in this function
static void atk6A_removeitem(void) //vsonic
{
    CMD_ARGS(u8 battler);

    u16 itemId = 0;
    u16 secondaryItem = 0;

    //think I get it, supposed to trigger item use scripts,
    //which would take me to removeitem, but don't actually have an item to use
    //as you're using the enemies berry item not your own?
    /*Bug Bite/Pluck can consume berries despite not meeting the HP threshold?
    Or other activation limitations.*/
    if (gBattleScripting.overrideBerryRequirements)
    {
        // bug bite / pluck - don't remove current item
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }

    gActiveBattler = GetBattlerForBattleScript(cmd->battler);
    itemId = gBattleMons[gActiveBattler].item;
    secondaryItem = gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)];

    // Popped Air Balloon cannot be restored by any means.
    // Corroded items cannot be restored either.
    if (GetBattlerHoldEffect(gActiveBattler, TRUE) != HOLD_EFFECT_AIR_BALLOON)
        //&& gBattleMoves[gCurrentMove].effect != EFFECT_CORROSIVE_GAS)
        gBattleStruct->usedHeldItems[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)] = itemId; // Remember if switched out

    gBattleMons[gActiveBattler].item = ITEM_NONE;
    if (gBattleMons[gActiveBattler].item == ITEM_NONE && secondaryItem != ITEM_NONE)
    {
        gBattleMons[gActiveBattler].item = secondaryItem;
        gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)] = ITEM_NONE;
    
        //gBattleResources->flags->flags[gActiveBattler] &= ~RESOURCE_FLAG_UNBURDEN; //this means lose unburden boost as you're gaining an item

        BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gActiveBattler].item), &gBattleMons[gActiveBattler].item);
        MarkBattlerForControllerExec(gActiveBattler);
    }
    else
    {
        BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gActiveBattler].item), &gBattleMons[gActiveBattler].item);
        MarkBattlerForControllerExec(gActiveBattler);
    }
        

    CheckSetUnburden(gActiveBattler);

    //ClearBattlerItemEffectHistory(gActiveBattler); emerald ai update
    if (!TryCheekPouch(gActiveBattler, itemId) && !TrySymbiosis(gActiveBattler, itemId))
        gBattlescriptCurrInstr = cmd->nextInstr;
}

void BS_TrySymbiosis(void)
{
    NATIVE_ARGS();
    //called by Bestow, Fling, and Bug Bite, which don't work with Cmd_removeitem.
    u32 partner = BATTLE_PARTNER(gBattlerAttacker);
    if (SYMBIOSIS_CHECK(gBattlerAttacker, partner))
    {
        BestowItem(partner, gBattlerAttacker);
        gLastUsedAbility = gBattleMons[partner].ability;
        gBattleScripting.battler = gBattlerAbility = partner;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_SymbiosisActivates;
        return;
    }

    gBattlescriptCurrInstr = cmd->nextInstr;
}

//why didn't I just fold this into remove item?
//its tied in after every case of remove item so makes no sense 
//to not just put in it...
/*void BS_checksecondaryItemslot(void)
{
    

    NATIVE_ARGS(u8 battler);

    u16 itemId = 0;
    u16 secondaryItem = 0;

    

    gActiveBattler = GetBattlerForBattleScript(cmd->battler);
    itemId = gBattleMons[gActiveBattler].item;
    secondaryItem = gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)];

    if (itemId == ITEM_NONE && secondaryItem != ITEM_NONE)
    {
        gBattleMons[gActiveBattler].item = secondaryItem;
        gBattleStruct->SecondaryItemSlot[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)] = ITEM_NONE;
    
        gBattleResources->flags->flags[gActiveBattler] &= ~RESOURCE_FLAG_UNBURDEN; //this means lose unburden boost as you're gaining an item

        BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gActiveBattler].item), &gBattleMons[gActiveBattler].item);
        MarkBattlerForControllerExec(gActiveBattler);
    }
    
    

    gBattlescriptCurrInstr = cmd->nextInstr;
}*/

static void atk6B_atknameinbuff1(void)
{
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
    ++gBattlescriptCurrInstr;
}

static void atk6C_drawlvlupbox(void)
{
    if (gBattleScripting.atk6C_drawlvlupboxState == 0)
    {
        if (IsMonGettingExpSentOut())
            gBattleScripting.atk6C_drawlvlupboxState = 3;
        else
            gBattleScripting.atk6C_drawlvlupboxState = 1;
    }

    switch (gBattleScripting.atk6C_drawlvlupboxState)
    {
    case 1:
        gBattle_BG2_Y = 0x60;
        SetBgAttribute(2, BG_ATTR_PRIORITY, 0);
        ShowBg(2);
        sub_8026480();
        gBattleScripting.atk6C_drawlvlupboxState = 2;
        break;
    case 2:
        if (!sub_80264D0())
            gBattleScripting.atk6C_drawlvlupboxState = 3;
        break;
    case 3:
        gBattle_BG1_X = 0;
        gBattle_BG1_Y = 0x100;
        SetBgAttribute(0, BG_ATTR_PRIORITY, 1);
        SetBgAttribute(1, BG_ATTR_PRIORITY, 0);
        ShowBg(0);
        ShowBg(1);
        HandleBattleWindow(18, 7, 0x1D, 0x13, WINDOW_x80);
        gBattleScripting.atk6C_drawlvlupboxState = 4;
        break;
    case 4:
        DrawLevelUpWindow1();
        PutWindowTilemap(12);
        CopyWindowToVram(12, COPYWIN_BOTH);
        ++gBattleScripting.atk6C_drawlvlupboxState;
        break;
    case 5:
    case 7:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            gBattle_BG1_Y = 0;
            ++gBattleScripting.atk6C_drawlvlupboxState;
        }
        break;
    case 6:
        if (gMain.newKeys)
        {
            PlaySE(SE_SELECT);
            DrawLevelUpWindow2();
            CopyWindowToVram(12, COPYWIN_GFX);
            ++gBattleScripting.atk6C_drawlvlupboxState;
        }
        break;
    case 8:
        if (gMain.newKeys)
        {
            PlaySE(SE_SELECT);
            HandleBattleWindow(18, 7, 0x1D, 0x13, WINDOW_x80 | WINDOW_CLEAR);
            ++gBattleScripting.atk6C_drawlvlupboxState;
        }
        break;
    case 9:
        if (!sub_8026648())
        {
            ClearWindowTilemap(13);
            CopyWindowToVram(13, COPYWIN_MAP);
            ClearWindowTilemap(12);
            CopyWindowToVram(12, COPYWIN_MAP);
            SetBgAttribute(2, BG_ATTR_PRIORITY, 2);
            ShowBg(2);
            gBattleScripting.atk6C_drawlvlupboxState = 10;
        }
        break;
    case 10:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            SetBgAttribute(0, BG_ATTR_PRIORITY, 0);
            SetBgAttribute(1, BG_ATTR_PRIORITY, 1);
            ShowBg(0);
            ShowBg(1);
            ++gBattlescriptCurrInstr;
        }
        break;
    }
}
//this may be it, double check how transform handles stats
//believe major part of issue was transform logic used
//setmondata so my stats weren't my actual stats
static void DrawLevelUpWindow1(void)
{
    u16 currStats[NUM_STATS];

    GetMonLevelUpWindowStats(&gPlayerParty[gBattleStruct->expGetterMonId], currStats);
    DrawLevelUpWindowPg1(12, gBattleResources->beforeLvlUp->stats, currStats, 0xE, 0xD, 0xF);
}

static void DrawLevelUpWindow2(void)
{
    u16 currStats[NUM_STATS];

    GetMonLevelUpWindowStats(&gPlayerParty[gBattleStruct->expGetterMonId], currStats);
    DrawLevelUpWindowPg2(12, currStats, 0xE, 0xD, 0xF);
}

static void sub_8026480(void)
{
    gBattle_BG2_Y = 0;
    gBattle_BG2_X = 0x1A0;
    LoadPalette(gUnknown_82506D0, 0x60, 0x20);
    CopyToWindowPixelBuffer(13, gUnknown_82506F0, 0, 0);
    PutWindowTilemap(13);
    CopyWindowToVram(13, COPYWIN_BOTH);
    PutMonIconOnLvlUpBox();
}

static bool8 sub_80264D0(void)
{
    if (IsDma3ManagerBusyWithBgCopy())
        return TRUE;
    if (gBattle_BG2_X == 0x200)
        return FALSE;
    if (gBattle_BG2_X == 0x1A0)
        PutLevelAndGenderOnLvlUpBox();
    gBattle_BG2_X += 8;
    if (gBattle_BG2_X >= 0x200)
        gBattle_BG2_X = 0x200;
    return (gBattle_BG2_X != 0x200);
}

static void PutLevelAndGenderOnLvlUpBox(void)
{
    u16 monLevel;
    u8 monGender;
    struct TextPrinterTemplate printerTemplate;
    u8 *txtPtr;
    u8 *txtPtr2;

    monLevel = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_LEVEL);
    monGender = GetMonGender(&gPlayerParty[gBattleStruct->expGetterMonId]);
    GetMonNickname(&gPlayerParty[gBattleStruct->expGetterMonId], gStringVar4);
    printerTemplate.currentChar = gStringVar4;
    printerTemplate.windowId = 13;
    printerTemplate.fontId = 0;
    printerTemplate.x = 32;
    printerTemplate.y = 0;
    printerTemplate.currentX = 32;
    printerTemplate.currentY = 0;
    printerTemplate.letterSpacing = 0;
    printerTemplate.lineSpacing = 0;
    printerTemplate.unk = 0;
    printerTemplate.fgColor = TEXT_COLOR_WHITE;
    printerTemplate.bgColor = TEXT_COLOR_TRANSPARENT;
    printerTemplate.shadowColor = TEXT_COLOR_DARK_GREY;
    AddTextPrinter(&printerTemplate, 0xFF, NULL);
    txtPtr = gStringVar4;
    gStringVar4[0] = 0xF9;
    *++txtPtr = 5;
    *++txtPtr = 0;
    txtPtr2 = txtPtr + 1;
    txtPtr = ConvertIntToDecimalStringN(++txtPtr, monLevel, STR_CONV_MODE_LEFT_ALIGN, 3);
    txtPtr = StringFill(txtPtr, 0, 5);
    txtPtr = txtPtr2 + 4;
    if (monGender != MON_GENDERLESS)
    {
        if (monGender == MON_MALE)
        {
            txtPtr = WriteColorChangeControlCode(txtPtr, 0, 0xC);
            txtPtr = WriteColorChangeControlCode(txtPtr, 1, 0xD);
            *(txtPtr++) = CHAR_MALE;
        }
        else
        {
            txtPtr = WriteColorChangeControlCode(txtPtr, 0, 0xE);
            txtPtr = WriteColorChangeControlCode(txtPtr, 1, 0xF);
            *(txtPtr++) = CHAR_FEMALE;
        }
        *(txtPtr++) = EOS;
    }
    printerTemplate.y = 10;
    printerTemplate.currentY = 10;
    AddTextPrinter(&printerTemplate, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(13, COPYWIN_GFX);
}

static bool32 IsRototillerAffected(u32 battlerId)
{
    if (!(IsBattlerAlive(battlerId)))
        return FALSE;
    if (!(IsBattlerGrounded(battlerId)))
        return FALSE;   // Only grounded battlers affected
    if (!(IS_BATTLER_OF_TYPE(battlerId, TYPE_GRASS)))
        return FALSE;   // Only grass types affected
    if (gStatuses3[battlerId] & STATUS3_SEMI_INVULNERABLE)
        return FALSE;   // Rototiller doesn't affected semi-invulnerable battlers
    if (DoesPranksterBlockMove(MOVE_ROTOTILLER, gBattlerAttacker, battlerId, FALSE))
        return FALSE;
    return TRUE;
}

static bool8 sub_8026648(void)
{
    if (gBattle_BG2_X == 0x1A0)
        return FALSE;
    if (gBattle_BG2_X - 16 < 0x1A0)
        gBattle_BG2_X = 0x1A0;
    else
        gBattle_BG2_X -= 16;
    return (gBattle_BG2_X != 0x1A0);
}

#define sDestroy                    data[0]
#define sSavedLvlUpBoxXPosition     data[1]

static void PutMonIconOnLvlUpBox(void) //don't understand this, if expp getter is storing corect idea, for displaying monthat levels why is the move data wrong...
{
    u8 spriteId;
    const u16 *iconPal;
    struct SpriteSheet iconSheet;
    struct SpritePalette iconPalSheet;
    u16 species = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_SPECIES);
    u32 personality = GetMonData(&gPlayerParty[gBattleStruct->expGetterMonId], MON_DATA_PERSONALITY);
    const u8 *iconPtr = GetMonIconPtr(species, personality, 1);

    iconSheet.data = iconPtr;
    iconSheet.size = 0x200;
    iconSheet.tag = MON_ICON_LVLUP_BOX_TAG;
    iconPal = GetValidMonIconPalettePtr(species);
    iconPalSheet.data = iconPal;
    iconPalSheet.tag = MON_ICON_LVLUP_BOX_TAG;
    LoadSpriteSheet(&iconSheet);
    LoadSpritePalette(&iconPalSheet);
    spriteId = CreateSprite(&sSpriteTemplate_MonIconOnLvlUpBox, 256, 10, 0);
    gSprites[spriteId].sDestroy = FALSE;
    gSprites[spriteId].sSavedLvlUpBoxXPosition = gBattle_BG2_X;
}

static void SpriteCB_MonIconOnLvlUpBox(struct Sprite* sprite)
{
    sprite->pos2.x = sprite->sSavedLvlUpBoxXPosition - gBattle_BG2_X;
    if (sprite->pos2.x != 0)
    {
        sprite->sDestroy = TRUE;
    }
    else if (sprite->sDestroy)
    {
        DestroySprite(sprite);
        FreeSpriteTilesByTag(MON_ICON_LVLUP_BOX_TAG);
        FreeSpritePaletteByTag(MON_ICON_LVLUP_BOX_TAG);
    }
}

bool32 IsMonGettingExpSentOut(void)
{
    if (gBattlerPartyIndexes[0] == gBattleStruct->expGetterMonId) //believe index 0 is 1st battle party slot i.e player side left
        return TRUE;
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && gBattlerPartyIndexes[2] == gBattleStruct->expGetterMonId)
        return TRUE;
    return FALSE;
}

static void atk6D_resetsentmonsvalue(void)
{
    ResetSentPokesToOpponentValue();
    ++gBattlescriptCurrInstr;
}

static void atk6E_setatktoplayer0(void)
{
    gBattlerAttacker = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    ++gBattlescriptCurrInstr;
}

static void atk6F_makevisible(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    BtlController_EmitSpriteInvisibility(0, FALSE);
    MarkBattlerForControllerExec(gActiveBattler);

    gBattlescriptCurrInstr += 2;
}

static void atk70_recordlastability(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
    RecordAbilityBattle(gActiveBattler, gLastUsedAbility);
    gBattlescriptCurrInstr += 2; // UB: Should be + 2, one byte for command and one byte for battlerId argument.
}

void BufferMoveToLearnIntoBattleTextBuff2(void)
{
    PREPARE_MOVE_BUFFER(gBattleTextBuff2, gMoveToLearn);
}

static void atk71_buffermovetolearn(void)
{
    BufferMoveToLearnIntoBattleTextBuff2();
    ++gBattlescriptCurrInstr;
}

static void atk72_jumpifplayerran(void)
{
    if (TryRunFromBattle(gBattlerFainted))
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    else
        gBattlescriptCurrInstr += 5;
}

static void atk73_hpthresholds(void)
{
    u8 opposingBattler;
    s32 result;

    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        opposingBattler = gActiveBattler ^ BIT_SIDE;

        result = gBattleMons[opposingBattler].hp * 100 / gBattleMons[opposingBattler].maxHP;
        if (result == 0)
            result = 1;
        if (result > 69 || !gBattleMons[opposingBattler].hp)
            gBattleStruct->hpScale = 0;
        else if (result > 39)
            gBattleStruct->hpScale = 1;
        else if (result > 9)
            gBattleStruct->hpScale = 2;
        else
            gBattleStruct->hpScale = 3;
    }
    gBattlescriptCurrInstr += 2;
}

static void atk74_hpthresholds2(void)
{
    u8 opposingBattler;
    s32 result;
    u8 hpSwitchout;

    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
        opposingBattler = gActiveBattler ^ BIT_SIDE;
        hpSwitchout = *(gBattleStruct->hpOnSwitchout + GetBattlerSide(opposingBattler));
        result = (hpSwitchout - gBattleMons[opposingBattler].hp) * 100 / hpSwitchout;

        if (gBattleMons[opposingBattler].hp >= hpSwitchout)
            gBattleStruct->hpScale = 0;
        else if (result <= 29)
            gBattleStruct->hpScale = 1;
        else if (result <= 69)
            gBattleStruct->hpScale = 2;
        else
            gBattleStruct->hpScale = 3;
    }
    gBattlescriptCurrInstr += 2;
}

static void atk75_useitemonopponent(void)
{
    gBattlerInMenuId = gBattlerAttacker;
    PokemonUseItemEffects(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]], gLastUsedItem, gBattlerPartyIndexes[gBattlerAttacker], 0, 1);
    ++gBattlescriptCurrInstr;
}

#define DEFOG_CLEAR(status, structField, battlescript, move)\
{                                                           \
    if (*sideStatuses & status)                             \
    {                                                       \
        if (clear)                                          \
        {                                                   \
            if (move)                                       \
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, move);\
            *sideStatuses &= ~(status);                     \
            sideTimer->structField = 0;                     \
            BattleScriptPushCursor();                       \
            gBattlescriptCurrInstr = battlescript;          \
        }                                                   \
        return TRUE;                                        \
    }                                                       \
}

static bool32 ClearDefogHazards(u8 battlerAtk, bool32 clear)
{
    s32 i;
    for (i = 0; i < 2; i++)
    {
        struct SideTimer *sideTimer = &gSideTimers[i];
        u32 *sideStatuses = &gSideStatuses[i]; //to make it work I can either upgrade gSudeStaatuses to u32 (taking more ewram)
        //or I can swap the movevaleu for aurora_veil for something below 255

        gBattlerAttacker = i;
        if (GetBattlerSide(battlerAtk) != i) //ok this is throwing up large integer error because move aurora veil is above 255 u8
        {
            DEFOG_CLEAR(SIDE_STATUS_REFLECT, reflectTimer, BattleScript_SideStatusWoreOffReturn, MOVE_REFLECT);
            DEFOG_CLEAR(SIDE_STATUS_LIGHTSCREEN, lightscreenTimer, BattleScript_SideStatusWoreOffReturn, MOVE_LIGHT_SCREEN);
            DEFOG_CLEAR(SIDE_STATUS_MIST, mistTimer, BattleScript_SideStatusWoreOffReturn, MOVE_MIST);
            DEFOG_CLEAR(SIDE_STATUS_AURORA_VEIL, auroraVeilTimer, BattleScript_SideStatusWoreOffReturn, MOVE_AURORA_VEIL);
            DEFOG_CLEAR(SIDE_STATUS_SAFEGUARD, safeguardTimer, BattleScript_SideStatusWoreOffReturn, MOVE_SAFEGUARD);
            DEFOG_CLEAR(SIDE_STATUS_HEAL_BLOCK, healBlockTimer, BattleScript_SideStatusWoreOffReturn, MOVE_HEAL_BLOCK); //HOPE WORKS
            DEFOG_CLEAR(SIDE_STATUS_MAGIC_COAT, MagicTimer, BattleScript_SideStatusWoreOffReturn, MOVE_MAGIC_COAT); //HOPE WORKS
        }
        DEFOG_CLEAR(SIDE_STATUS_SPIKES, spikesAmount, BattleScript_SpikesFree, 0);
        DEFOG_CLEAR(SIDE_STATUS_STEALTH_ROCK, stealthRockAmount, BattleScript_StealthRockFree, 0);
        DEFOG_CLEAR(SIDE_STATUS_TOXIC_SPIKES, toxicSpikesAmount, BattleScript_ToxicSpikesFree, 0);
        DEFOG_CLEAR(SIDE_STATUS_STICKY_WEB, stickyWebAmount, BattleScript_StickyWebFree, 0);
    }

    return FALSE;
}

u32 IsFlowerVeilProtected(u32 battler) //prvent stat drop & status change for user & ally
{
    if (IS_BATTLER_OF_TYPE(battler, TYPE_GRASS) || GetBattlerAbility(battler) == ABILITY_FLOWER_VEIL)
        return IsAbilityOnSide(battler, ABILITY_FLOWER_VEIL); //will return true or false, based on if ability present
    else
        return 0;
}

u32 IsLeafGuardProtected(u32 battler)
{
    if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SUN_ANY))
        return GetBattlerAbility(battler) == ABILITY_LEAF_GUARD;
    else
        return 0;
}

//uses battlemons over getbattlerability
//because ability is immune to removal
bool32 IsShieldsDownProtected(u32 battler)
{
    return (gBattleMons[battler].ability == ABILITY_SHIELDS_DOWN
        && gBattleMons[battler].species == SPECIES_MINIOR);
}

u32 IsAbilityStatusProtected(u32 battler)
{
    return IsFlowerVeilProtected(battler)
        || IsLeafGuardProtected(battler)
        || IsShieldsDownProtected(battler);
}

bool32 CanUseLastResort(u8 battlerId)
{
    u32 i;
    u32 knownMovesCount = 0, usedMovesCount = 0;

    for (i = 0; i < 4; i++)
    {
        if (gBattleMons[battlerId].moves[i] != MOVE_NONE)
            knownMovesCount++;
        if (i != gCurrMovePos && gDisableStructs[battlerId].usedMoves & gBitTable[i]) // Increment used move count for all moves except current Last Resort.
            usedMovesCount++;
    }

    return (knownMovesCount >= 2 && usedMovesCount >= knownMovesCount - 1);
}

static bool32 HasAttackerFaintedTarget(void)
{
    if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
        && gBattleMoves[gCurrentMove].power != 0
        && (gLastHitBy[gBattlerTarget] == 0xFF || gLastHitBy[gBattlerTarget] == gBattlerAttacker)
        && gBattleStruct->moveTarget[gBattlerAttacker] == gBattlerTarget
        && gBattlerTarget != gBattlerAttacker
        && gCurrentTurnActionNumber == GetBattlerTurnOrderNum(gBattlerAttacker)
        && (gChosenMove == gChosenMoveByBattler[gBattlerAttacker] || gChosenMove == gBattleMons[gBattlerAttacker].moves[gChosenMovePos]))
        return TRUE;
    else
        return FALSE;
}

static void HandleTerrainMove(u32 moveEffect)
{
    u32 statusFlag = 0;
    u8 *timer = NULL;

    switch (moveEffect)
    {
    case EFFECT_MISTY_TERRAIN:
        statusFlag = STATUS_FIELD_MISTY_TERRAIN, timer = &gFieldTimers.terrainTimer;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        break;
    case EFFECT_GRASSY_TERRAIN:
        statusFlag = STATUS_FIELD_GRASSY_TERRAIN, timer = &gFieldTimers.terrainTimer;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        break;
    case EFFECT_ELECTRIC_TERRAIN:
        statusFlag = STATUS_FIELD_ELECTRIC_TERRAIN, timer = &gFieldTimers.terrainTimer;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        break;
    case EFFECT_PSYCHIC_TERRAIN:
        statusFlag = STATUS_FIELD_PSYCHIC_TERRAIN, timer = &gFieldTimers.terrainTimer;
        gBattleCommunication[MULTISTRING_CHOOSER] = 3;
        break;
    }

    if (gFieldStatuses & statusFlag || statusFlag == 0)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 3);
    }
    else
    {
        gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;
        gFieldStatuses |= statusFlag;
        if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_TERRAIN_EXTENDER)
            *timer = 8;
        else
            *timer = 5;
        gBattlescriptCurrInstr += 7;
    }
}

/*
static void RecalcBattlerStats(u32 battler, struct Pokemon *mon)
{
    CalculateMonStats(mon);
    gBattleMons[battler].level = GetMonData(mon, MON_DATA_LEVEL);
    gBattleMons[battler].hp = GetMonData(mon, MON_DATA_HP);
    gBattleMons[battler].maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
    gBattleMons[battler].ability = GetMonAbility(mon);
    gBattleMons[battler].type1 = gBaseStats[gBattleMons[battler].species].type1;
    gBattleMons[battler].type2 = gBaseStats[gBattleMons[battler].species].type2;
} */  //old version emerald version does same thing, just separated out to be more flexible

//think chang take ability and species arguement, 
//species just to pass to transformmonstats function (and type stuff at bottom)
static void TransformRecalcBattlerStats(u32 battler, struct Pokemon *mon, u16 TargetAbility, u16 TransformSpecies)
{
    /*u16 target; //mon is mon being transformed, i.e attacker using transformative effect
    if (GetBattlerSide(gBattlerTarget) == B_SIDE_OPPONENT)
        target = GetMonAbility(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]]);
    else
        target = GetMonAbility(&gPlayerParty[gBattlerPartyIndexes[gBattlerTarget]]);
    */
    TransformedMonHP(mon, TargetAbility, TransformSpecies);
    TransformedMonStats(mon, TargetAbility, TransformSpecies);  ///set stat based on species, dbl check it sets mondata, below assigns it for battle
    //gBattleMons[battler].level = GetMonData(mon, MON_DATA_LEVEL); //since don't want to change level may remove this 
    //thinking set values to what I want in above function do I even need these?  possibly ressting stat, remove or put inside other function
    /*gBattleMons[battler].hp = GetMonData(mon, MON_DATA_HP); 
    gBattleMons[battler].maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
    */
    gBattleMons[battler].ability = TargetAbility;  //think work? yup works
    gBattleMons[battler].type1 = gBaseStats[TransformSpecies].type1; //think safe to replace battlemons here, as already fails if mon is transformed, and no other time species would change
    gBattleMons[battler].type2 = gBaseStats[TransformSpecies].type2;
    //gBattleMons[battler].type2 = gBaseStats[gBattleMons[gBattlerTarget].species].type2;
    //set type 3 in function after this  function is used
}

//dif between new form change and my transform logic, keep above function for those use these for otheress
void RecalcBattlerStats(u32 battler, struct Pokemon *mon)
{
    CalculateMonStats(mon);
    CopyMonLevelAndBaseStatsToBattleMon(battler, mon);
    CopyMonAbilityAndTypesToBattleMon(battler, mon);
}

void CopyMonLevelAndBaseStatsToBattleMon(u32 battler, struct Pokemon *mon)
{
    gBattleMons[battler].level = GetMonData(mon, MON_DATA_LEVEL);
    gBattleMons[battler].hp = GetMonData(mon, MON_DATA_HP);
    gBattleMons[battler].maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
}

void CopyMonAbilityAndTypesToBattleMon(u32 battler, struct Pokemon *mon)
{
    gBattleMons[battler].ability = GetMonAbility(mon);
    gBattleMons[battler].type1 = gBaseStats[gBattleMons[battler].species].type1;
    gBattleMons[battler].type2 = gBaseStats[gBattleMons[battler].species].type2;
    //gBattleMons[battler].type3 = TYPE_MYSTERY;  not adding that as will cause issue with other stuff, if change type 3
    //type3 will be someting mon not normally able to control themselves
}


u32 GetHighestStatId(u32 battlerId)
{
    u32 i, highestId = STAT_ATK, highestStat = gBattleMons[battlerId].attack;

    for (i = STAT_DEF; i < NUM_STATS; i++)
    {
        u16 *statVal = &gBattleMons[battlerId].attack + (i - 1); //of note doesn't include hp so could be why - 1   //also thinkm this is dereferencing so need the asterisk etc here
        if (*statVal > highestStat) //effect of line above is to increse stored stat, i starts at defense whchi is value 2,  but ti reads stat attack + (i -1)  which is attack + 1,  i.e defense stat so same value we're on
        {
            highestStat = *statVal;
            highestId = i; //sets highestId to atk at start, then checks other stats so if not passed it auto returns attack
        }
    }
    return highestId;
}

// Return True if the order was changed, and false if the order was not changed(for example because the target would move after the attacker anyway).
static bool32 ChangeOrderTargetAfterAttacker(void)
{
    u32 i;
    u8 data[MAX_BATTLERS_COUNT];

    if (GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget)
        || GetBattlerTurnOrderNum(gBattlerAttacker) + 1 == GetBattlerTurnOrderNum(gBattlerTarget))
        return FALSE;

    for (i = 0; i < gBattlersCount; i++)
        data[i] = gBattlerByTurnOrder[i];
    if (GetBattlerTurnOrderNum(gBattlerAttacker) == 0 && GetBattlerTurnOrderNum(gBattlerTarget) == 2)
    {
        gBattlerByTurnOrder[1] = gBattlerTarget;
        gBattlerByTurnOrder[2] = data[1];
        gBattlerByTurnOrder[3] = data[3];
    }
    else if (GetBattlerTurnOrderNum(gBattlerAttacker) == 0 && GetBattlerTurnOrderNum(gBattlerTarget) == 3)
    {
        gBattlerByTurnOrder[1] = gBattlerTarget;
        gBattlerByTurnOrder[2] = data[1];
        gBattlerByTurnOrder[3] = data[2];
    }
    else // Attacker == 1, Target == 3
    {
        gBattlerByTurnOrder[2] = gBattlerTarget;
        gBattlerByTurnOrder[3] = data[2];
    }
    return TRUE;
}

static u32 CalculateBattlerPartyCount(u32 battler)
{
    u32 count;
    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        count = CalculatePlayerPartyCount();
    else
        count = CalculateEnemyPartyCount();
    return count;
}

#define VARIOUS_BS_COMMANDS

static void atk76_various(void) //will need to add all these emerald various commands to the inc...
{                   //will also need to go through all the new stuff and make sure any
    //functions they relay on have already been ported. THen do the inc stuff.
    CMD_ARGS(u8 battler, u8 id);
    
    struct Pokemon *mon;
    u32 side, bits;
    s32 i, j;
    u8 data[10];
    u32 monToCheck, status;
    u16 species;
    u8 abilityNum;
    u16 lastMove = gLastMoves[gBattlerTarget];
    u8 lost_type = gBattleMoves[gCurrentMove].argument;
    u32 battler;
    //u16 lastMove = gLastResultingMoves[gBattlerAttacker]; //why did I need to use this, when this "gLastMoves[gbattlertargt]" existed?
    

    if (gBattleControllerExecFlags)
        return;

    battler = GetBattlerForBattleScript(cmd->battler); //mostly for form change use of various
    gActiveBattler = battler; //since using outdated btlcontroler may need this?
    //-_- yup that was the entire problem, imposter etc. properly transforms now
    switch (cmd->id) //put every case within brackets, and add VARIOUS_ARGS  to everythihng, battler arg alread covered by cmd
    {

    case VARIOUS_CANCEL_MULTI_TURN_MOVES:
    {
        VARIOUS_ARGS();
        CancelMultiTurnMoves(battler);
        break;
    }
    case VARIOUS_SET_MAGIC_COAT_TARGET:
    {
        VARIOUS_ARGS();
        gBattlerAttacker = gBattlerTarget;
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (gSideTimers[side].followmeTimer != 0 && gBattleMons[gSideTimers[side].followmeTarget].hp != 0)
            gBattlerTarget = gSideTimers[side].followmeTarget;
        else
            gBattlerTarget = battler;
        break;
    }
    case VARIOUS_IS_RUNNING_IMPOSSIBLE:
    {
        VARIOUS_ARGS();
        gBattleCommunication[0] = IsRunningFromBattleImpossible();
        break;
    }
    case VARIOUS_GET_MOVE_TARGET:
    {
        VARIOUS_ARGS();
        gBattlerTarget = GetMoveTarget(gCurrentMove, 0);
        break;
    }
    case VARIOUS_GET_BATTLER_FAINTED:
    {
        VARIOUS_ARGS();
        if (gHitMarker & HITMARKER_FAINTED(battler))
            gBattleCommunication[0] = TRUE;
        else
            gBattleCommunication[0] = FALSE;
        break;
    }
    case VARIOUS_RESET_INTIMIDATE_TRACE_BITS:
    {   
        VARIOUS_ARGS();
        //RESETS the switchin effect, that is the trigger for the abillity activation
        gSpecialStatuses[battler].intimidatedMon = 0;//pairs with battle_util.c
        gSpecialStatuses[battler].traced = 0; //BattleScript_IntimidateActivates
        gSpecialStatuses[battler].tigerMomAttacked = 0; //new special status, but uses BattleScript_IntimidateActivates
        break; // & trygetintimidatetarget command in this file
    }
    case VARIOUS_UPDATE_CHOICE_MOVE_ON_LVL_UP:
    {
        VARIOUS_ARGS();
        if (gBattlerPartyIndexes[0] == gBattleStruct->expGetterMonId || gBattlerPartyIndexes[2] == gBattleStruct->expGetterMonId)
        {
            u16 *choicedMove;

            if (gBattlerPartyIndexes[0] == gBattleStruct->expGetterMonId)
                battler = 0;
            else
                battler = 2;
            choicedMove = &gBattleStruct->choicedMove[battler];
            for (i = 0; i < MAX_MON_MOVES; ++i)
            {
                if (gBattleMons[battler].moves[i] == *choicedMove)
                    break;
            }
            if (i == MAX_MON_MOVES)
                *choicedMove = MOVE_NONE;
        }
        break;
    }
    case VARIOUS_RESET_PLAYER_FAINTED:
    {
        VARIOUS_ARGS();
        if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_DOUBLE))
         && gBattleTypeFlags & BATTLE_TYPE_TRAINER
         && gBattleMons[0].hp != 0
         && gBattleMons[1].hp != 0)
            gHitMarker &= ~(HITMARKER_PLAYER_FAINTED);
        break;
    }
    case VARIOUS_GET_BATTLERS_FOR_RECALL:
    {
        VARIOUS_ARGS();
        i = 0; // redundant
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        battler = 1;
        for (i = 0; battler < MAX_BATTLERS_COUNT; battler += 2)
        {
            if (battler < gBattlersCount && gBattleMons[battler].hp != 0)
                gBattleCommunication[MULTISTRING_CHOOSER] |= gBitTable[i];
            ++i;
        }
        break;
    }
    case VARIOUS_RETURN_OPPONENT_MON1:
    {
        VARIOUS_ARGS();
        battler = 1;
        if (gBattleMons[battler].hp != 0)
        {
            BtlController_EmitReturnMonToBall(0, 0);
            MarkBattlerForControllerExec(battler);
        }
        break;
    }
    case VARIOUS_RETURN_OPPONENT_MON2:
    {
        VARIOUS_ARGS();
        if (gBattlersCount > 3)
        {
            battler = 3;
            if (gBattleMons[battler].hp != 0)
            {
                BtlController_EmitReturnMonToBall(0, 0);
                MarkBattlerForControllerExec(battler);
            }
        }
        break;
    }
    case VARIOUS_PLAY_MOVE_ANIMATION:
    {
        VARIOUS_ARGS(u16 move);
        BtlController_EmitMoveAnimation(BUFFER_A, cmd->move, gBattleScripting.animTurn, 0, 0, gBattleMons[battler].friendship, &gDisableStructs[battler]);//, gMultiHitCounter);
        MarkBattlerForControllerExec(battler); //don't know why friendship and multihit are used
        gBattlescriptCurrInstr = cmd->nextInstr;//temp remove multihit as base functino doesn't have that argument, need update
        return;
    }
    case VARIOUS_CHECK_POKEFLUTE:
    {
        VARIOUS_ARGS();
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        monToCheck = 0;
        for (i = 0; i < gBattlersCount; ++i)
        {
            if (gBattleMons[i].ability != ABILITY_SOUNDPROOF)
            {
                gBattleMons[i].status1 &= ~STATUS1_SLEEP;
                gBattleMons[i].status2 &= ~STATUS2_NIGHTMARE;

            }
        }
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);
            abilityNum = GetMonData(&gPlayerParty[i], MON_DATA_ABILITY_NUM);
            status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
            if (species != SPECIES_NONE
             && species != SPECIES_EGG
             && status & AILMENT_FNT
             && GetAbilityBySpecies(species, abilityNum) != ABILITY_SOUNDPROOF)
                monToCheck |= (1 << i);
        }
        if (monToCheck)
        {
            battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            status = 0;
            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, monToCheck, 4, &status);
            MarkBattlerForControllerExec(battler);
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        }
        monToCheck = 0;
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES_OR_EGG);
            abilityNum = GetMonData(&gEnemyParty[i], MON_DATA_ABILITY_NUM);
            status = GetMonData(&gEnemyParty[i], MON_DATA_STATUS);

            if (species != SPECIES_NONE
             && species != SPECIES_EGG
             && status & AILMENT_FNT
             && GetAbilityBySpecies(species, abilityNum) != ABILITY_SOUNDPROOF)
                monToCheck |= (1 << i);
        }
        if (monToCheck)
        {
            battler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            status = 0;
            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, monToCheck, 4, &status);
            MarkBattlerForControllerExec(battler);
            gBattleCommunication[5] = 1;
        }
        break;
    }
    case VARIOUS_SET_TELEPORT_OUTCOME:
    {
        VARIOUS_ARGS();
        // Don't end the battle if one of the wild mons teleported from the wild double battle
        // and its partner is still alive.
        if (GetBattlerSide(battler) == B_SIDE_OPPONENT && IsBattlerAlive(BATTLE_PARTNER(battler)))
        {
            gAbsentBattlerFlags |= gBitTable[battler];
            gHitMarker |= HITMARKER_FAINTED(battler);
            gBattleMons[battler].hp = 0;
            SetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_HP, &gBattleMons[battler].hp);
            SetHealthboxSpriteInvisible(gHealthboxSpriteIds[battler]);
            FaintClearSetData();
        }
        else if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        {
            gBattleOutcome = B_OUTCOME_PLAYER_TELEPORTED;
        }
        else
        {
            gBattleOutcome = B_OUTCOME_MON_TELEPORTED;
        }
        break;//this isnt in base firered so switch in stuff is handled elsewhere typically  -battle startfunctino in main *facepalm
    }
    case VARIOUS_SWITCHIN_ABILITIES:
    {
        VARIOUS_ARGS();
        gBattlescriptCurrInstr = cmd->nextInstr;
        AbilityBattleEffects(ABILITYEFFECT_NEUTRALIZINGGAS, battler, 0, 0, 0);
        AbilityBattleEffects(ABILITYEFFECT_ON_SWITCHIN, battler, 0, 0, 0);
        AbilityBattleEffects(ABILITYEFFECT_INTIMIDATE2, battler, 0, 0, 0);//hope can use for tiger mom
        AbilityBattleEffects(ABILITYEFFECT_TRACE, battler, 0, 0, 0);
        return; //not sure what this does  its only used in mega evo and trace in gen 8 emerald expansion
    }
    case VARIOUS_SAVE_TARGET:
    {
        VARIOUS_ARGS();
        gBattleStruct->savedBattlerTarget = gBattlerTarget;
        break;
    }
    case VARIOUS_RESTORE_TARGET:
    {
        VARIOUS_ARGS();
        gBattlerTarget = gBattleStruct->savedBattlerTarget;
        break;
    }
    case VARIOUS_INSTANT_HP_DROP:
    {
        VARIOUS_ARGS();
        BtlController_EmitHealthBarUpdate(0, INSTANT_HP_BAR_DROP);
        MarkBattlerForControllerExec(battler);
        break;
    }
    case VARIOUS_CLEAR_STATUS:
    {
        VARIOUS_ARGS();
        gBattleMons[battler].status1 = 0;
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
        MarkBattlerForControllerExec(battler);
        break;
    }
    case VARIOUS_RESTORE_PP:
    {
        VARIOUS_ARGS();
        for (i = 0; i < 4; i++)
        {
            gBattleMons[battler].pp[i] = CalculatePPWithBonus(gBattleMons[battler].moves[i], gBattleMons[battler].ppBonuses, i);
            data[i] = gBattleMons[battler].pp[i];
        }
        data[i] = gBattleMons[battler].ppBonuses;
        BtlController_EmitSetMonData(0, REQUEST_PP_DATA_BATTLE, 0, 5, data);
        MarkBattlerForControllerExec(battler);
        break;
    }
    case VARIOUS_CAN_TELEPORT:
    {  
        VARIOUS_ARGS();
        //new logic for teleport
        gBattleCommunication[0] = CanTeleport(battler);
        break;
    }
    case VARIOUS_TRY_ACTIVATE_MOXIE:
    {   
        VARIOUS_ARGS(); 
        // and chilling neigh + as one ice rider
        if ((GetBattlerAbility(battler) == ABILITY_MOXIE
            || GetBattlerAbility(battler) == ABILITY_CHILLING_NEIGH
            || GetBattlerAbility(battler) == ABILITY_AS_ONE_ICE_RIDER)
            && HasAttackerFaintedTarget()
            && !NoAliveMonsForEitherParty()
            && gBattleMons[gBattlerAttacker].statStages[STAT_ATK] != MAX_STAT_STAGE)
        {
            u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

            //PlayCry_Normal(species, 25);
            PlayCry_ByMode(species, 25, CRY_MODE_DOUBLES); //i THINK may be shorter, so potentially better
            gBattleMons[gBattlerAttacker].statStages[STAT_ATK]++;
            SET_STATCHANGER(STAT_ATK, 1, FALSE);
            PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_ATK);
            BattleScriptPush(cmd->nextInstr);
            gLastUsedAbility = GetBattlerAbility(battler);
            gBattlescriptCurrInstr = BattleScript_RaiseStatOnFaintingTarget;
            return;
        }
        break;
    }
    case VARIOUS_TRY_ACTIVATE_GRIM_NEIGH:
    {   
        VARIOUS_ARGS(); 
        // and as one shadow rider
        if ((GetBattlerAbility(battler) == ABILITY_GRIM_NEIGH
            || GetBattlerAbility(battler) == ABILITY_AS_ONE_SHADOW_RIDER)
            && HasAttackerFaintedTarget()
            && !NoAliveMonsForEitherParty()
            && gBattleMons[gBattlerAttacker].statStages[STAT_SPATK] != MAX_STAT_STAGE)
        {
            u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

            //PlayCry_Normal(species, 25);
            PlayCry_ByMode(species, 25, CRY_MODE_DOUBLES); //i THINK may be shorter, so potentially better
            gBattleMons[gBattlerAttacker].statStages[STAT_SPATK]++;
            SET_STATCHANGER(STAT_SPATK, 1, FALSE);
            PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPATK);
            BattleScriptPush(cmd->nextInstr);
            gLastUsedAbility = GetBattlerAbility(battler);
            //if (GetBattlerAbility(battler) == ABILITY_AS_ONE_SHADOW_RIDER)
              //  gBattleScripting.abilityPopupOverwrite = gLastUsedAbility = ABILITY_GRIM_NEIGH;
            gBattlescriptCurrInstr = BattleScript_RaiseStatOnFaintingTarget;
            return;
        }
        break;
    }
    case VARIOUS_TRY_ACTIVATE_RECEIVER:
    { 
        VARIOUS_ARGS(); 
        // Partner gets fainted's ally ability
        gBattlerAbility = BATTLE_PARTNER(battler); //need to test, didn't want ot take of ewram making gbattlerAbility so replaced with a variable
        i = GetBattlerAbility(gBattlerAbility);
        if (IsBattlerAlive(gBattlerAbility)
            && (i == ABILITY_RECEIVER || i == ABILITY_POWER_OF_ALCHEMY)) //need test after changes
        {
            switch (gBattleMons[battler].ability) //since only one pokemon has received, I decided I'll let the type guards be in the list
            { // Can't copy these abilities.        //also allowed it to work with trace, 
            
            case ABILITY_POWER_OF_ALCHEMY:
            case ABILITY_RECEIVER:
            case ABILITY_FORECAST:
            case ABILITY_MULTITYPE:
            case ABILITY_FLOWER_GIFT:
            case ABILITY_ILLUSION:
            case ABILITY_RKS_SYSTEM:
            case ABILITY_ZEN_MODE:
            case ABILITY_STANCE_CHANGE:
            case ABILITY_IMPOSTER:
            case ABILITY_INVERSION:
            case ABILITY_POWER_CONSTRUCT:
            case ABILITY_BATTLE_BOND:
            case ABILITY_SCHOOLING:
            case ABILITY_COMATOSE:
            case ABILITY_SHIELDS_DOWN:
            case ABILITY_DISGUISE:
                break;
            default:

                gBattleStruct->tracedAbility[gBattlerAbility] = gBattleMons[battler].ability; // re-using the variable for trace
                gBattleScripting.battler = battler;
                BattleScriptPush(cmd->nextInstr);
                gBattlescriptCurrInstr = BattleScript_ReceiverActivates;
                return;
            }
        }
        break;
    }
    case VARIOUS_TRY_ACTIVATE_BEAST_BOOST:
    {
        VARIOUS_ARGS(); 
        i = GetHighestStatId(battler);
        if (GetBattlerAbility(battler) == ABILITY_BEAST_BOOST
            && HasAttackerFaintedTarget()
            && !NoAliveMonsForEitherParty()
            && gBattleMons[gBattlerAttacker].statStages[i] != MAX_STAT_STAGE)
        {
            //PlayCry_Normal(species, 25);
            PlayCry_ByMode(species, 25, CRY_MODE_DOUBLES); //i THINK may be shorter, so potentially better
            gBattleMons[gBattlerAttacker].statStages[i]++;
            SET_STATCHANGER(i, 1, FALSE);
            PREPARE_STAT_BUFFER(gBattleTextBuff1, i);
            BattleScriptPush(cmd->nextInstr);
            gBattlescriptCurrInstr = BattleScript_AttackerAbilityStatRaise;
            return;
        }
        break;
    }
    case VARIOUS_TRY_ACTIVATE_SOULHEART:
    {
        VARIOUS_ARGS(); 
        while (gBattleStruct->soulheartBattlerId < gBattlersCount)
        {
            gBattleScripting.battler = gBattleStruct->soulheartBattlerId++;
            if (GetBattlerAbility(gBattleScripting.battler) == ABILITY_SOUL_HEART
                && IsBattlerAlive(gBattleScripting.battler)
                && !NoAliveMonsForEitherParty()
                && gBattleMons[gBattleScripting.battler].statStages[STAT_SPATK] != MAX_STAT_STAGE)
            {
                gBattleMons[gBattleScripting.battler].statStages[STAT_SPATK]++;
                SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPATK);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ScriptingAbilityStatRaise;
                return;
            }
        }
        gBattleStruct->soulheartBattlerId = 0;
        break;
    }
    case VARIOUS_TRY_ACTIVATE_FELL_STINGER:
    {
        VARIOUS_ARGS(); 
        if (gBattleMoves[gCurrentMove].effect == EFFECT_FELL_STINGER
            && HasAttackerFaintedTarget()
            && !NoAliveMonsForEitherParty()
            && gBattleMons[gBattlerAttacker].statStages[STAT_ATK] != MAX_STAT_STAGE)
        {
           // if (B_FELL_STINGER_STAT_RAISE >= GEN_7)
              //  SET_STATCHANGER(STAT_ATK, 3, FALSE);
            //else
                SET_STATCHANGER(STAT_ATK, 2, FALSE);

            PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_ATK);
            BattleScriptPush(cmd->nextInstr);
            gBattlescriptCurrInstr = BattleScript_FellStingerRaisesStat;
            return;
        }
        break;
    }
    case VARIOUS_SET_LUCKY_CHANT:
    {
        VARIOUS_ARGS(const u8 *failInstr); 
        if (!(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_LUCKY_CHANT))
        {
            gSideStatuses[GET_BATTLER_SIDE(battler)] |= SIDE_STATUS_LUCKY_CHANT;
            gSideTimers[GET_BATTLER_SIDE(battler)].luckyChantBattlerId = battler;
            gSideTimers[GET_BATTLER_SIDE(battler)].luckyChantTimer = 5;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_SUCKER_PUNCH_CHECK:
    {
        VARIOUS_ARGS(const u8 *failInstr); 
        u16 move = gBattleMons[gBattlerTarget].moves[gBattleStruct->chosenMovePositions[gBattlerTarget]];

        if (GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget))
            gBattlescriptCurrInstr = cmd->failInstr;
        //else if (gBattleMoves[move].power == 0)
        else if (IS_MOVE_STATUS(move) && move != MOVE_ME_FIRST)
            gBattlescriptCurrInstr = cmd->failInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_SET_SIMPLE_BEAM:
    {
        VARIOUS_ARGS(const u8 *failInstr); 
        if (IsEntrainmentTargetOrSimpleBeamBannedAbility(gBattleMons[battler].ability))
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            if (GetBattlerAbility(gBattlerTarget) == ABILITY_NEUTRALIZING_GAS)
                gSpecialStatuses[gBattlerTarget].neutralizingGasRemoved = TRUE;

            else if (GetBattlerAbility(gBattlerTarget) == ABILITY_IMMUTABLE_WIND)
                gSpecialStatuses[gBattlerTarget].neutralizingGasRemoved = TRUE;

            gBattleMons[gBattlerTarget].ability = ABILITY_SIMPLE;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_ENTRAINMENT:
    {
        VARIOUS_ARGS(const u8 *failInstr); 
        if (IsEntrainmentBannedAbilityAttacker(GetBattlerAbility(gBattlerAttacker))
            || IsEntrainmentTargetOrSimpleBeamBannedAbility(GetBattlerAbility(gBattlerTarget)))
        {
            gBattlescriptCurrInstr = cmd->failInstr;
            return;
        }

        if (gBattleMons[gBattlerTarget].ability == gBattleMons[gBattlerAttacker].ability)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gBattleMons[gBattlerTarget].ability = gBattleMons[gBattlerAttacker].ability;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_INVERT_STAT_STAGES:
    {
        VARIOUS_ARGS(); 
        for (i = 0; i < NUM_BATTLE_STATS; i++)
        {
            if (gBattleMons[battler].statStages[i] < 6) // Negative becomes positive.
                gBattleMons[battler].statStages[i] = 6 + (6 - gBattleMons[battler].statStages[i]);
            else if (gBattleMons[battler].statStages[i] > 6) // Positive becomes negative.
                gBattleMons[battler].statStages[i] = 6 - (gBattleMons[battler].statStages[i] - 6);
        }
        break;
    }
    case VARIOUS_SET_TERRAIN:
    {
        VARIOUS_ARGS(const u8 *failInstr); //see if new setup of function works
        //removed use as not used in EE
        //HandleTerrainMove(gBattleMoves[gCurrentMove].effect); 
        u32 statusFlag = 0;
        u8 timer = 0;

        switch (gBattleMoves[gCurrentMove].effect)
        {

            case EFFECT_MISTY_TERRAIN:
                statusFlag = STATUS_FIELD_MISTY_TERRAIN;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                break;
            case EFFECT_GRASSY_TERRAIN:
                statusFlag = STATUS_FIELD_GRASSY_TERRAIN;
                gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                break;
            case EFFECT_ELECTRIC_TERRAIN:
                statusFlag = STATUS_FIELD_ELECTRIC_TERRAIN;
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                break;
            case EFFECT_PSYCHIC_TERRAIN:
                statusFlag = STATUS_FIELD_PSYCHIC_TERRAIN;
                gBattleCommunication[MULTISTRING_CHOOSER] = 3;
                break;
        }

        if (gFieldStatuses & statusFlag || statusFlag == 0)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;
            gFieldStatuses |= statusFlag;
            if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_TERRAIN_EXTENDER)
                timer = 8;
            else
                timer = 5;
            gFieldTimers.terrainTimer = timer;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_ME_FIRST:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        u16 effect = gBattleMoves[gBattleMons[gBattlerTarget].moves[gBattleStruct->chosenMovePositions[gBattlerTarget]]].effect;
        u16 move = gBattleMons[gBattlerTarget].moves[gBattleStruct->chosenMovePositions[gBattlerTarget]];

        if (GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget))
            gBattlescriptCurrInstr = cmd->failInstr;
        //else if (gBattleMoves[gBattleMons[gBattlerTarget].moves[gBattleStruct->chosenMovePositions[gBattlerTarget]]].power == 0)
        else if (IS_MOVE_STATUS(move))
            gBattlescriptCurrInstr = cmd->failInstr;
        else
        {
            
            switch (move)
            {
            case MOVE_STRUGGLE:
            case MOVE_BEAK_BLAST:
            case MOVE_BELCH:
            case MOVE_SHELL_TRAP:
            case MOVE_THIEF:
            case MOVE_COVET:
            case MOVE_COUNTER:
            case MOVE_MIRROR_COAT:
            case MOVE_METAL_BURST:
            case MOVE_ME_FIRST:
                gBattlescriptCurrInstr = cmd->failInstr;
                break;
            default:
                gCalledMove = move;
                gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
                gBattlerTarget = GetMoveTarget(gCalledMove, 0);
                gStatuses3[gBattlerAttacker] |= STATUS3_ME_FIRST;
                gBattlescriptCurrInstr = cmd->nextInstr;
                break;
            }
        }
        return;
    }
    case VARIOUS_TRY_ELECTRIFY:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget))
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gStatuses4[gBattlerTarget] |= STATUS4_ELECTRIFIED;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_REFLECT_TYPE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gBattleMons[gBattlerTarget].species == SPECIES_ARCEUS || gBattleMons[gBattlerTarget].species == SPECIES_SILVALLY)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else if (gBattleMons[gBattlerTarget].type1 == TYPE_MYSTERY && gBattleMons[gBattlerTarget].type2 != TYPE_MYSTERY)
        {
            gBattleMons[gBattlerAttacker].type1 = gBattleMons[gBattlerTarget].type2;
            gBattleMons[gBattlerAttacker].type2 = gBattleMons[gBattlerTarget].type2;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else if (gBattleMons[gBattlerTarget].type1 != TYPE_MYSTERY && gBattleMons[gBattlerTarget].type2 == TYPE_MYSTERY)
        {
            gBattleMons[gBattlerAttacker].type1 = gBattleMons[gBattlerTarget].type1;
            gBattleMons[gBattlerAttacker].type2 = gBattleMons[gBattlerTarget].type1;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else if (gBattleMons[gBattlerTarget].type1 == TYPE_MYSTERY && gBattleMons[gBattlerTarget].type2 == TYPE_MYSTERY)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gBattleMons[gBattlerAttacker].type1 = gBattleMons[gBattlerTarget].type1;
            gBattleMons[gBattlerAttacker].type2 = gBattleMons[gBattlerTarget].type2;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_HANDLE_FORM_CHANGE:{  //equiv of VARIOUS_HANDLE_FORM_CHANGE in EE, handles all form change
    
        VARIOUS_ARGS(u8 case_);
        if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
            mon = &gEnemyParty[gBattlerPartyIndexes[battler]];
        else
            mon = &gPlayerParty[gBattlerPartyIndexes[battler]];

        // Change species.
        if (cmd->case_ == 0)
        {
            /* What was the idea here?
            if (!gBattleTextBuff1)
                PREPARE_SPECIES_BUFFER(gBattleTextBuff1, gBattleMons[battler].species);
            */
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_SPECIES_BATTLE, gBitTable[gBattlerPartyIndexes[battler]], sizeof(gBattleMons[battler].species), &gBattleMons[battler].species);
            MarkBattlerForControllerExec(battler); //hopefully works, EE has more args in emitsetmondata
        }
        // Change stats.
        else if (cmd->case_ == 1)
        {
            RecalcBattlerStats(battler, mon);
        }
        /*
        // Update healthbox. - this is from EE, below it is my way test later
        else
        {
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], mon, HEALTHBOX_ALL);
        }
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
        */
        // Update healthbox and elevation.
        else
        {
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], mon, HEALTHBOX_ALL);
            //CreateMegaIndicatorSprite(battler, 0);   make attempt at later
            if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
                SetBattlerShadowSpriteCallback(battler, gBattleMons[battler].species);
        }
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_TRY_LAST_RESORT:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (CanUseLastResort(battler))
            gBattlescriptCurrInstr = cmd->nextInstr;
        else
            gBattlescriptCurrInstr = cmd->failInstr;
        return;
    }
    case VARIOUS_ARGUMENT_STATUS_EFFECT:    // argumentstatuseffect currently replacing uses of this
    {    
        VARIOUS_ARGS();
        switch (gBattleMoves[gCurrentMove].argument)//can add more status to this, flinch confusion etc.
        {
        case STATUS1_BURN:
            gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
            break;
        case STATUS1_FREEZE:
            gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE;
            break;
        case STATUS1_PARALYSIS:
            gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
            break;
        case STATUS1_POISON:
            gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
            break;
        case STATUS1_TOXIC_POISON:
            gBattleScripting.moveEffect = MOVE_EFFECT_TOXIC;
            break;
        default:
            gBattleScripting.moveEffect = 0; //if not any of those sets moveeffect to 0
            break;
        }
        if (gBattleScripting.moveEffect != 0)
        {
            BattleScriptPush(cmd->nextInstr);
            gBattlescriptCurrInstr = BattleScript_EffectWithChance;
            return;
        }
        break;//this is broken right now, but on the other hand, I also don't need this
    }
    case VARIOUS_TRY_HIT_SWITCH_TARGET:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (IsBattlerAlive(gBattlerAttacker)
            && IsBattlerAlive(gBattlerTarget)
            && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && TARGET_TURN_DAMAGED
            && GetBattlerAbility(gBattlerTarget) != ABILITY_GUARD_DOG)
        {
            gBattlescriptCurrInstr = BattleScript_ForceRandomSwitch; //ok guess because it goes to other battlescript?
        } //think missing some logic as setup abilities that cant switch without this? i.e suction cups etc.
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_TRY_AUTOTOMIZE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (GetBattlerWeight(battler) > 1)
        {
            gDisableStructs[battler].autotomizeCount++;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_TRY_COPYCAT:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (lastMove == 0xFFFF || (sForbiddenMoves[lastMove] & FORBIDDEN_COPYCAT))
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gCalledMove = lastMove;
            gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
            gBattlerTarget = GetMoveTarget(gCalledMove, 0);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_INSTRUCT:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        for (i = 0; sMoveEffectsForbiddenToInstruct[i] != FORBIDDEN_INSTRUCT_END; i++)
        {
            if (sMoveEffectsForbiddenToInstruct[i] == gBattleMoves[gLastMoves[gBattlerTarget]].effect)
                break;
        }
        if (gLastMoves[gBattlerTarget] == 0 || gLastMoves[gBattlerTarget] == 0xFFFF || sMoveEffectsForbiddenToInstruct[i] != FORBIDDEN_INSTRUCT_END
            || gLastMoves[gBattlerTarget] == MOVE_STRUGGLE || gLastMoves[gBattlerTarget] == MOVE_KINGS_SHIELD)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gSpecialStatuses[gBattlerTarget].instructedChosenTarget = *(gBattleStruct->moveTarget + gBattlerTarget) | 0x4;
            gBattlerAttacker = gBattlerTarget;
            gCalledMove = gLastMoves[gBattlerAttacker];
            for (i = 0; i < MAX_MON_MOVES; i++)
            {
                if (gBattleMons[gBattlerAttacker].moves[i] == gCalledMove)
                {
                    gCurrMovePos = i;
                    i = 4;
                    break;
                }
            }
            if (i != 4 || gBattleMons[gBattlerAttacker].pp[gCurrMovePos] == 0)
                gBattlescriptCurrInstr = cmd->failInstr;
            else
            {
                gBattlerTarget = gBattleStruct->lastMoveTarget[gBattlerAttacker];
                gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
                PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, battler, gBattlerPartyIndexes[battler]);
                gBattlescriptCurrInstr = cmd->nextInstr;
            }
        }
        return;
    /*}
    case VARIOUS_ABILITY_POPUP:
    {  //still need add even if not use
        CreateAbilityPopUp(battler, gBattleMons[battler].ability, (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) != 0);
        break;*/
    }
    case VARIOUS_DEFOG:
    {
        VARIOUS_ARGS(u8 clear, const u8 *failInstr);
        if (cmd->clear) // Clear
        {
            if (ClearDefogHazards(gEffectBattler, TRUE))
                return;
            else
                gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            if (ClearDefogHazards(battler, FALSE))
                gBattlescriptCurrInstr = cmd->nextInstr;
            else
                gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_JUMP_IF_TARGET_ALLY:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            gBattlescriptCurrInstr = cmd->nextInstr;
        else
            gBattlescriptCurrInstr = cmd->jumpInstr;
        return;
    }
    case VARIOUS_TRY_SYNCHRONOISE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (!DoBattlersShareType(gBattlerAttacker, gBattlerTarget))
            gBattlescriptCurrInstr = cmd->failInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_LOSE_TYPE:
    {
        VARIOUS_ARGS();
         //changed to use move argument, rather than having to read script ptr, that way leaves room for removing enemy type with moves of a different type than type being lost
        for (i = 0; i < 3; i++) //TEST, since there's only 3 types shouldn't this only need to increment up to 2 not 3?
        {   //nah it should be 3, way for loops work, it'll not execute when the value is 3., it checks the value before executing the block.
            if (gBattleMons[battler].type1 != gBattleMons[battler].type2) //if multitype mon
            {
                if (*(u8*)(&gBattleMons[battler].type1 + i) == lost_type)    //believe +i is checking each battler
                    *(u8*)(&gBattleMons[battler].type1 + i) = TYPE_MYSTERY;  //nvm its checking the different types type 1 typ2 & type 3 since its not using 4 hmm
                
            }
            else if (gBattleMons[battler].type1 == gBattleMons[battler].type2)//actually since this would be for entire battle not just switchin, type 3 is irrelevant
            {
               //type3 defaults to mystery logic was wrong here, point was to avoid mon becoming typeless
                //pros cons to each can't remember why I wanted to use type normal over mysery
                //but guess this is better far as balance?
                    if (*(u8*)(&gBattleMons[battler].type1 + i) == lost_type)
                        *(u8*)(&gBattleMons[battler].type1 + i) = TYPE_NORMAL;
                //}//it should default to normal long as mon is monotype even if a 3rd type has been set that is not equal to type being lost or mystery.
                            //as type 3 is lost on switch I believe.
            }
        }
        PREPARE_TYPE_BUFFER(gBattleTextBuff3, lost_type);
        gBattlescriptCurrInstr = cmd->nextInstr;    //post change unsure bout this part
        return;
    }
    case VARIOUS_PSYCHO_SHIFT:
    { 
        VARIOUS_ARGS(const u8 *failInstr);
        //transfers status condition
        

        // Psycho shift works
        if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_POISON) && CanBePoisoned(gBattlerAttacker, gBattlerTarget))
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        else if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_TOXIC_POISON) && CanBePoisoned(gBattlerAttacker, gBattlerTarget))
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        else if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_BURN) && CanBeBurned(gBattlerTarget))
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        else if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_PARALYSIS) && CanBeParalyzed(gBattlerTarget))
            gBattleCommunication[MULTISTRING_CHOOSER] = 3;
        else if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP) && CanSleep(gBattlerTarget))
            gBattleCommunication[MULTISTRING_CHOOSER] = 4;
        else if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE) && CanBeFrozen(gBattlerTarget))
            gBattleCommunication[MULTISTRING_CHOOSER] = 5;
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
            return;
        }


            gBattleMons[gBattlerTarget].status1 = gBattleMons[gBattlerAttacker].status1 & STATUS1_ANY; //may have to change to |= if get multi status 1 setup
            battler = gBattlerTarget;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
            MarkBattlerForControllerExec(battler);
            gBattlescriptCurrInstr = cmd->nextInstr;

        return;
    }
    case VARIOUS_CURE_STATUS:
    { 
        VARIOUS_ARGS();
        gBattleMons[battler].status1 = 0;
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
        MarkBattlerForControllerExec(battler);
        break;
    }
    case VARIOUS_POWER_TRICK:
    {
        VARIOUS_ARGS();
        gStatuses3[battler] ^= STATUS3_POWER_TRICK;
        SWAP(gBattleMons[battler].attack, gBattleMons[battler].defense, i);
        break;
    }
    case VARIOUS_AFTER_YOU:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (ChangeOrderTargetAfterAttacker())
        {
            gSpecialStatuses[gBattlerTarget].afterYou = 1;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_BESTOW:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gBattleMons[gBattlerAttacker].item == ITEM_NONE
            || gBattleMons[gBattlerTarget].item != ITEM_NONE
            || !CanBattlerGetOrLoseItem(gBattlerAttacker, gBattleMons[gBattlerAttacker].item)
            || !CanBattlerGetOrLoseItem(gBattlerTarget, gBattleMons[gBattlerAttacker].item))
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            BestowItem(gBattlerAttacker, gBattlerTarget);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;//think need if here to exclude two_type_moves as its not meant to read the argument as a move effect
    }
    case VARIOUS_ARGUMENT_TO_MOVE_EFFECT:
    {   
        VARIOUS_ARGS();
        //argumenttomoveeffect works with seconaryeffectchance can prob also do like move effect set certain or effect user
        //if (gBattleMoves[gCurrentMove].effect != EFFECT_TWO_TYPED_MOVE)
        if (gBattleMoves[gCurrentMove].effect != EFFECT_TWO_TYPED_MOVE                
        && gBattleMoves[gCurrentMove].effect != EFFECT_LOSETYPE_HIT)
            gBattleScripting.moveEffect = gBattleMoves[gCurrentMove].argument; //potentially need make argument field for bs. as well vsonic
        break;  //I think what this does is, pass the argument to move effect? and then it gets read by seteffectwithchance function?
    }
    case VARIOUS_SPECTRAL_THIEF:
    {
        VARIOUS_ARGS();
        // Raise stats
        for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
        {
            if (gBattleStruct->stolenStats[0] & gBitTable[i])
            {
                gBattleStruct->stolenStats[0] &= ~(gBitTable[i]);
                SET_STATCHANGER(i, gBattleStruct->stolenStats[i], FALSE);
                if (ChangeStatBuffs(GET_STAT_BUFF_VALUE_WITH_SIGN(gBattleScripting.statChanger), i, MOVE_EFFECT_CERTAIN | MOVE_EFFECT_AFFECTS_USER, NULL) == STAT_CHANGE_WORKED)
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_StatUpMsg;
                    return;
                }
            }
        }
        break;
    }
    case VARIOUS_SET_POWDER:
    {
        VARIOUS_ARGS();
        gBattleMons[battler].status2 |= STATUS2_POWDER;
        break;
    }
    case VARIOUS_ACUPRESSURE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        bits = 0;
        for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
        {
            if (gBattleMons[battler].statStages[i] != MAX_STAT_STAGE)
                bits |= gBitTable[i];
        }
        if (bits)
        {
            u32 statId;
            do
            {
                statId = (Random() % (NUM_BATTLE_STATS - 1)) + 1;
            } while (!(bits & gBitTable[statId]));

            SET_STATCHANGER(statId, 2, FALSE);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_JUMP_IF_NOT_GROUNDED:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (!(IsBattlerGrounded(battler)))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_ROAR_FAILS:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (WILD_DOUBLE_BATTLE
            && GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER
            && GetBattlerSide(gBattlerTarget) == B_SIDE_OPPONENT
            && IS_WHOLE_SIDE_ALIVE(gBattlerTarget))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else if (WILD_DOUBLE_BATTLE
            && GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT
            && GetBattlerSide(gBattlerTarget) == B_SIDE_OPPONENT)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_ABSENT:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (!IsBattlerAlive(battler))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_SHIELDS_DOWN_PROTECTED:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (IsShieldsDownProtected(battler))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_NOT_HOLD_EFFECT:
    {
        VARIOUS_ARGS(u8 holdEffect, const u8 *jumpInstr);
        if (GetBattlerHoldEffect(battler, TRUE) != cmd->holdEffect)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_NO_ALLY:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (!IsBattlerAlive(BATTLE_PARTNER(battler)))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_TRY_FAIRY_LOCK:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gFieldStatuses |= STATUS_FIELD_FAIRY_LOCK;
            gFieldTimers.fairyLockTimer = 2;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_GET_STAT_VALUE:
    {
        VARIOUS_ARGS(u8 statValue);
        i = cmd->statValue;
        gBattleMoveDamage = *(u16*)(&gBattleMons[battler].attack) + (i - 1);
        gBattleMoveDamage *= gStatStageRatios[gBattleMons[battler].statStages[i]][0];
        gBattleMoveDamage /= gStatStageRatios[gBattleMons[battler].statStages[i]][1];
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_FULL_HP:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (BATTLER_MAX_HP(battler))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        break;
    }
    case VARIOUS_JUMP_IF_NOT_FULL_HP:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (!(BATTLER_MAX_HP(battler)))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_TRY_FRISK:
    {
        VARIOUS_ARGS();
        while (gBattleStruct->friskedBattler < gBattlersCount)
        {
            gBattlerTarget = gBattleStruct->friskedBattler++;
            if (GET_BATTLER_SIDE2(battler) != GET_BATTLER_SIDE2(gBattlerTarget)
                && IsBattlerAlive(gBattlerTarget)
                && gBattleMons[gBattlerTarget].item != ITEM_NONE)
            {
                gLastUsedItem = gBattleMons[gBattlerTarget].item;
                RecordItemEffectBattle(gBattlerTarget, GetBattlerHoldEffect(gBattlerTarget, FALSE));
                BattleScriptPushCursor();
                // If Frisk identifies two mons' items, show the pop-up only once.
                if (gBattleStruct->friskedAbility)
                {
                    gBattlescriptCurrInstr = BattleScript_FriskMsg;
                }
                else
                {
                    gBattleStruct->friskedAbility = TRUE;
                    //gBattlescriptCurrInstr = BattleScript_FriskMsgWithPopup;
                }
                return;
            }
        }
        gBattleStruct->friskedBattler = 0;
        gBattleStruct->friskedAbility = FALSE;
        break;
    }
    case VARIOUS_TRY_ILLUSION_OFF:
    {
        VARIOUS_ARGS();
        if (GetIllusionMonPtr(battler) != NULL)
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_IllusionOff;
            return;
        }
        break;
    }
    case VARIOUS_SET_SPRITEIGNORE0HP:
    {
        VARIOUS_ARGS(bool8 ignore0HP);
        gBattleStruct->spriteIgnore0Hp = cmd->ignore0HP;
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_UPDATE_NICK:
    {
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
            mon = &gPlayerParty[gBattlerPartyIndexes[battler]];
        else
            mon = &gEnemyParty[gBattlerPartyIndexes[battler]];
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], mon, HEALTHBOX_NICK);
        break;
    }
    case VARIOUS_JUMP_IF_NOT_BERRY:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (ItemId_GetPocket(gBattleMons[battler].item) == POCKET_BERRY_POUCH)
            gBattlescriptCurrInstr = cmd->nextInstr;
        else
            gBattlescriptCurrInstr = cmd->jumpInstr;
        return;
    }
    case VARIOUS_CHECK_IF_GRASSY_TERRAIN_HEALS:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if ((gStatuses3[battler] & (STATUS3_SEMI_INVULNERABLE))
            || BATTLER_MAX_HP(battler)
            || !gBattleMons[battler].hp) //hopefully works
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }//vsonic important , need test terrain affect, may replace w isbattlerterrainaffected function
        else if (IsBattlerTerrainAffected(battler, STATUS_FIELD_GRASSY_TERRAIN)) //IsBattlerTerrainAffected(battler, STATUS_FIELD_GRASSY_TERRAIN)
        {
            gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
            if (gBattleMoveDamage == 0)
                gBattleMoveDamage = 1;
            gBattleMoveDamage *= -1;

            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_GRAVITY_ON_AIRBORNE_MONS:
    {
        VARIOUS_ARGS();
        if (gStatuses3[battler] & STATUS3_ON_AIR)
            CancelMultiTurnMoves(battler);

        gStatuses3[battler] &= ~(STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS | STATUS3_ON_AIR);
        break;
    /*}
    case VARIOUS_HANDLE_TRAINER_SLIDE_MSG:
    {
        if (gBattlescriptCurrInstr[3] == 0)
        {
            gBattleScripting.savedDmg = gBattlerSpriteIds[battler];
            HideBattlerShadowSprite(battler);
        }
        else if (gBattlescriptCurrInstr[3] == 1)
        {
            BtlController_EmitPrintString(0, STRINGID_TRAINERSLIDE);
            MarkBattlerForControllerExec(battler);
        }
        else
        {
            gBattlerSpriteIds[battler] = gBattleScripting.savedDmg;
            if (gBattleMons[battler].hp != 0)
            {
                SetBattlerShadowSpriteCallback(battler, gBattleMons[battler].species);
                BattleLoadOpponentMonSpriteGfx(&gEnemyParty[gBattlerPartyIndexes[battler]], battler);
            }
        }
        gBattlescriptCurrInstr += 4;
        return;
    }
    case VARIOUS_TRY_TRAINER_SLIDE_MSG_FIRST_OFF:
    {
        if (ShouldDoTrainerSlide(battler, gTrainerBattleOpponent_A, TRAINER_SLIDE_FIRST_DOWN))
        {
            BattleScriptPush(gBattlescriptCurrInstr + 3);
            gBattlescriptCurrInstr = BattleScript_TrainerSlideMsgRet;
            return;
        }
        break;
    }
    case VARIOUS_TRY_TRAINER_SLIDE_MSG_LAST_ON:
    {
        if (ShouldDoTrainerSlide(battler, gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_SWITCHIN))
        {
            BattleScriptPush(gBattlescriptCurrInstr + 3);
            gBattlescriptCurrInstr = BattleScript_TrainerSlideMsgRet;
            return;
        }
        break;*/
    }
    case VARIOUS_SET_AURORA_VEIL:
    {
        VARIOUS_ARGS();
        if (gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_AURORA_VEIL
            || !IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_HAIL_ANY))
        {
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
        else
        {
            gSideStatuses[GET_BATTLER_SIDE(battler)] |= SIDE_STATUS_AURORA_VEIL;
            if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_LIGHT_CLAY)
                gSideTimers[GET_BATTLER_SIDE(battler)].auroraVeilTimer = 8;
            else
                gSideTimers[GET_BATTLER_SIDE(battler)].auroraVeilTimer = 5;
            gSideTimers[GET_BATTLER_SIDE(battler)].auroraVeilBattlerId = battler;

            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && CountAliveMonsInBattle(BATTLE_ALIVE_ATK_SIDE) == 2)
                gBattleCommunication[MULTISTRING_CHOOSER] = 5;
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 5;
        }
        break;
    }
    case VARIOUS_TRY_END_NEUTRALIZING_GAS:
    {
        VARIOUS_ARGS();
        if (gSpecialStatuses[battler].neutralizingGasRemoved)
        {
            gSpecialStatuses[battler].neutralizingGasRemoved = FALSE;
            if (gBattleMons[battler].ability == ABILITY_NEUTRALIZING_GAS)
            {
                BattleScriptPush(cmd->nextInstr);
                gBattlescriptCurrInstr = BattleScript_NeutralizingGasExits;
            }
            else if (gBattleMons[battler].ability == ABILITY_IMMUTABLE_WIND)
            {
                BattleScriptPush(cmd->nextInstr);
                gBattlescriptCurrInstr = BattleScript_ImmutableWindExits; //make unique strange winds subsided
            }
            return;
        }
        break;
    }
    case VARIOUS_TRY_END_STENCH:
    {
        VARIOUS_ARGS();
        if (gSpecialStatuses[battler].stenchRemoved)
        {
            gSpecialStatuses[battler].stenchRemoved = FALSE;
            BattleScriptPush(cmd->nextInstr);
            gBattlescriptCurrInstr = BattleScript_StenchExits;
            return;
        }
        break;
    }
    case VARIOUS_TRY_THIRD_TYPE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (IS_BATTLER_OF_TYPE(battler, gBattleMoves[gCurrentMove].argument))
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gBattleMons[battler].type3 = gBattleMoves[gCurrentMove].argument;
            PREPARE_TYPE_BUFFER(gBattleTextBuff1, gBattleMoves[gCurrentMove].argument);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    /*}
    case VARIOUS_DESTROY_ABILITY_POPUP:
    {
        DestroyAbilityPopUp(battler);
        break;*/
    }
    case VARIOUS_TOTEM_BOOST:
    {
        /*VARIOUS_ARGS(const u8 *jumpInstr);
        battler = gBattlerAttacker;
        if (gTotemBoosts[battler].stats == 0)
        {
            gBattlescriptCurrInstr = cmd->nextInstr;    // stats done, exit
        }
        else
        {
            for (i = 0; i < (NUM_BATTLE_STATS - 1); i++)
            {
                if (gTotemBoosts[battler].stats & (1 << i))
                {
                    if (gTotemBoosts[battler].statChanges[i] <= -1)
                        SET_STATCHANGER(i + 1, abs(gTotemBoosts[battler].statChanges[i]), TRUE);
                    else
                        SET_STATCHANGER(i + 1, gTotemBoosts[battler].statChanges[i], FALSE);

                    gTotemBoosts[battler].stats &= ~(1 << i);
                    gBattleScripting.battler = battler;
                    gBattlerTarget = battler;
                    if (gTotemBoosts[battler].stats & 0x80)
                    {
                        gTotemBoosts[battler].stats &= ~0x80; // set 'aura flared to life' flag
                        gBattlescriptCurrInstr = BattleScript_TotemFlaredToLife;
                    }
                    else
                    {
                        gBattlescriptCurrInstr = cmd->jumpInstr;   // do boost
                    }
                    return;
                }
            }
            gBattlescriptCurrInstr = cmd->nextInstr;    // exit if loop failed (failsafe)
        }
        return;
        */
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    case VARIOUS_MOVEEND_ITEM_EFFECTS:
    {
        VARIOUS_ARGS();
        if (ItemBattleEffects(ITEMEFFECT_NORMAL, battler, FALSE))
            return;
        break;
    }
    case VARIOUS_ROOM_SERVICE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_ROOM_SERVICE && TryRoomService(battler))
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return; //vsonic IMPORTANT consider planter or way to get more of these as they are single use
    }
    case VARIOUS_TERRAIN_SEED: //apparently are held items that activate on terrain and boost stats
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_SEEDS)
        {
            u8 effect = 0; //swapped stat buff of grass & psychic
            u16 item = gBattleMons[battler].item;
            switch (GetBattlerHoldEffectParam(battler, item))
            {
            case HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN:
                effect = TryHandleSeed(battler, STATUS_FIELD_ELECTRIC_TERRAIN, STAT_DEF, item, FALSE);
                break;
            case HOLD_EFFECT_PARAM_GRASSY_TERRAIN:
                effect = TryHandleSeed(battler, STATUS_FIELD_GRASSY_TERRAIN, STAT_SPDEF, item, FALSE);
                break;
            case HOLD_EFFECT_PARAM_MISTY_TERRAIN:
                effect = TryHandleSeed(battler, STATUS_FIELD_MISTY_TERRAIN, STAT_SPDEF, item, FALSE);
                break;
            case HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN:
                effect = TryHandleSeed(battler, STATUS_FIELD_PSYCHIC_TERRAIN, STAT_DEF, item, FALSE);
                break;
            }

            if (effect)
                return;
        }
        gBattlescriptCurrInstr = cmd->failInstr;
        return;
    }
    case VARIOUS_MAKE_INVISIBLE:
    {
        VARIOUS_ARGS();
        if (gBattleControllerExecFlags)
            break;
        
        BtlController_EmitSpriteInvisibility(BUFFER_A, TRUE);
        MarkBattlerForControllerExec(battler);
        break;
    }
    case VARIOUS_JUMP_IF_TERRAIN_AFFECTED:
    {
        VARIOUS_ARGS(u32 terrain, const u8 *jumpInstr);
        u32 flags = T1_READ_32(gBattlescriptCurrInstr + 3);
        if (IsBattlerTerrainAffected(battler, flags))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_EERIE_SPELL_PP_REDUCE:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gLastMoves[battler] != 0 && gLastMoves[battler] != 0xFFFF)
        {
            s32 i;

            for (i = 0; i < MAX_MON_MOVES; i++)
            {
                if (gLastMoves[battler] == gBattleMons[battler].moves[i])
                    break;
            }

            if (i != MAX_MON_MOVES && gBattleMons[battler].pp[i] != 0)
            {
                s32 ppToDeduct = 3;

                if (gBattleMons[battler].pp[i] < ppToDeduct)
                    ppToDeduct = gBattleMons[battler].pp[i];

                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gLastMoves[battler])
                ConvertIntToDecimalStringN(gBattleTextBuff2, ppToDeduct, STR_CONV_MODE_LEFT_ALIGN, 1);
                PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff2, 1, ppToDeduct)
                gBattleMons[battler].pp[i] -= ppToDeduct;
                if (!(gDisableStructs[battler].mimickedMoves & gBitTable[i])
                    && !(gBattleMons[battler].status2 & STATUS2_TRANSFORMED))
                {
                    BtlController_EmitSetMonData(BUFFER_A, REQUEST_PPMOVE1_BATTLE + i, 0, sizeof(gBattleMons[battler].pp[i]), &gBattleMons[battler].pp[i]);
                    MarkBattlerForControllerExec(battler);
                }
                
                if (gBattleMons[battler].pp[i] == 0 && gBattleStruct->skyDropTargets[battler] == 0xFF)
                    CancelMultiTurnMoves(battler);
                
                gBattlescriptCurrInstr = cmd->nextInstr;    // continue
            }
            else
            {
                gBattlescriptCurrInstr = cmd->failInstr;   // cant reduce pp
            }
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;   // cant reduce pp
        }
        return;
    }
    case VARIOUS_JUMP_IF_TEAM_HEALTHY:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && IsBattlerAlive(BATTLE_PARTNER(battler)))
        {
            u8 partner = BATTLE_PARTNER(battler);
            if ((gBattleMons[battler].hp == gBattleMons[battler].maxHP && !(gBattleMons[battler].status1 & STATUS1_ANY))
             && (gBattleMons[partner].hp == gBattleMons[partner].maxHP && !(gBattleMons[partner].status1 & STATUS1_ANY)))
                gBattlescriptCurrInstr = cmd->jumpInstr;   // fail
            else
                gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else // single battle
        {
            if (gBattleMons[battler].hp == gBattleMons[battler].maxHP && !(gBattleMons[battler].status1 & STATUS1_ANY))
                gBattlescriptCurrInstr = cmd->jumpInstr;   // fail
            else
                gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_HEAL_QUARTER_HP:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;

        if (gBattleMons[battler].hp == gBattleMons[battler].maxHP)
            gBattlescriptCurrInstr = cmd->failInstr;    // fail
        else
            gBattlescriptCurrInstr = cmd->nextInstr;   // can heal
        return;
    }
    case VARIOUS_REMOVE_TERRAIN:
    {
        VARIOUS_ARGS();
        gFieldTimers.terrainTimer = 0;
        switch (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY)
        {
        case STATUS_FIELD_MISTY_TERRAIN:
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            break;
        case STATUS_FIELD_GRASSY_TERRAIN:
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
            break;
        case STATUS_FIELD_ELECTRIC_TERRAIN:
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            break;
        case STATUS_FIELD_PSYCHIC_TERRAIN:
            gBattleCommunication[MULTISTRING_CHOOSER] = 3;
            break;
        default:
            gBattleCommunication[MULTISTRING_CHOOSER] = 4;  // failsafe
            break;
        }
        gFieldStatuses &= ~STATUS_FIELD_TERRAIN_ANY;    // remove the terrain
        TryToRevertMimicry(); // restore the types of Pok�mon with Mimicry
        break;
    }
    case VARIOUS_JUMP_IF_UNDER_200:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        // If the Pokemon is less than 200 kg, or weighing less than 441 lbs, then Sky Drop will work. Otherwise, it will fail.
        if (GetBattlerWeight(gBattlerTarget) < 441)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_SET_SKY_DROP:
    {
        VARIOUS_ARGS();
        gStatuses3[gBattlerTarget] |= (STATUS3_SKY_DROPPED | STATUS3_ON_AIR);
        /* skyDropTargets holds the information of who is in a particular instance of Sky Drop. 
           This is needed in the }
    case that multiple Pokemon use Sky Drop in the same turn or if
           the target of a Sky Drop faints while in the air.*/
        gBattleStruct->skyDropTargets[gBattlerAttacker] = gBattlerTarget;
        gBattleStruct->skyDropTargets[gBattlerTarget] = gBattlerAttacker;
        
        // End any multiturn effects caused by the target except STATUS2_LOCK_CONFUSE
        gBattleMons[gBattlerTarget].status2 &= ~(STATUS2_MULTIPLETURNS);
        gBattleMons[gBattlerTarget].status2 &= ~(STATUS2_UPROAR);
        gBattleMons[gBattlerTarget].status2 &= ~(STATUS2_BIDE);
        gDisableStructs[gBattlerTarget].rolloutTimer = 0;
        
        // End any Follow Me/Rage Powder effects caused by the target
        if (gSideTimers[GetBattlerSide(gBattlerTarget)].followmeTimer != 0 && gSideTimers[GetBattlerSide(gBattlerTarget)].followmeTarget == gBattlerTarget)
            gSideTimers[GetBattlerSide(gBattlerTarget)].followmeTimer = 0;

        break;
    }
    case VARIOUS_CLEAR_SKY_DROP:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        // Check to see if the initial target of this Sky Drop fainted before the 2nd turn of Sky Drop.
        // If so, make the move fail. If not, clear all of the statuses and continue the move.
        if (gBattleStruct->skyDropTargets[gBattlerAttacker] == 0xFF)
            gBattlescriptCurrInstr = cmd->failInstr;
        else
        {
            gBattleStruct->skyDropTargets[gBattlerAttacker] = 0xFF;          
            gBattleStruct->skyDropTargets[gBattlerTarget] = 0xFF;
            gStatuses3[gBattlerTarget] &= ~(STATUS3_SKY_DROPPED | STATUS3_ON_AIR);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        
        // Confuse target if they were in the middle of Petal Dance/Outrage/Thrash when targeted.
        if (gBattleMons[gBattlerTarget].status2 & STATUS2_LOCK_CONFUSE)
            gBattleScripting.moveEffect = (MOVE_EFFECT_CONFUSION | MOVE_EFFECT_CERTAIN);
        return;
    }
    case VARIOUS_SKY_DROP_YAWN:
    { 
        VARIOUS_ARGS();
        // If the mon that's sleeping due to Yawn was holding a Pokemon in Sky Drop, release the target and clear Sky Drop data.
        if (gBattleStruct->skyDropTargets[gEffectBattler] != 0xFF && !(gStatuses3[gEffectBattler] & STATUS3_SKY_DROPPED))
        {
            // Set the target of Sky Drop as gEffectBattler
            gEffectBattler = gBattleStruct->skyDropTargets[gEffectBattler];

            // Clear skyDropTargets data
            gBattleStruct->skyDropTargets[gBattleStruct->skyDropTargets[gEffectBattler]] = 0xFF;
            gBattleStruct->skyDropTargets[gEffectBattler] = 0xFF;
            
            // If the target was in the middle of Outrage/Thrash/etc. when targeted by Sky Drop, confuse them on release and do proper animation
            if (gBattleMons[gEffectBattler].status2 & STATUS2_LOCK_CONFUSE && CanBeConfused(gEffectBattler))
            {
                gBattleMons[gEffectBattler].status2 &= ~(STATUS2_LOCK_CONFUSE);
                gBattlerAttacker = gEffectBattler;
                gBattleMons[gBattlerTarget].status2 |= STATUS2_CONFUSION; //edit of original value /important test
                gBattlescriptCurrInstr = BattleScript_ThrashConfuses;
                return;
            }
        }
        break;
    }
    case VARIOUS_JUMP_IF_PRANKSTER_BLOCKED:
    { 
        VARIOUS_ARGS(const u8 *jumpInstr);
        //for some reason not currently used?
        if (DoesPranksterBlockMove(gCurrentMove, gBattlerAttacker, battler, TRUE))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_TRY_TO_CLEAR_PRIMAL_WEATHER:
    {
        bool8 shouldNotClear = FALSE;

        for (i = 0; i < gBattlersCount; i++)
        {
            u32 ability = GetBattlerAbility(i);
            if (((ability == ABILITY_DESOLATE_LAND && gBattleWeather & WEATHER_PRIMAL_ANY)
             || (ability == ABILITY_PRIMORDIAL_SEA && gBattleWeather & WEATHER_RAIN_PRIMAL)
             || (ability == ABILITY_DELTA_STREAM && gBattleWeather & WEATHER_STRONG_WINDS))
             && IsBattlerAlive(i))
                shouldNotClear = TRUE;
        }
        if (gBattleWeather & WEATHER_SUN_PRIMAL && !shouldNotClear)
        {
            gBattleWeather &= ~WEATHER_SUN_PRIMAL;  //can't remembr why removed these, but all strings are defined now so...
            PrepareStringBattle(STRINGID_EXTREMESUNLIGHTFADED, battler);
            gBattleCommunication[MSG_DISPLAY] = 1;
        }
        else if (gBattleWeather & WEATHER_RAIN_PRIMAL && !shouldNotClear)
        {
            gBattleWeather &= ~WEATHER_RAIN_PRIMAL;
            PrepareStringBattle(STRINGID_HEAVYRAINLIFTED, battler);
            gBattleCommunication[MSG_DISPLAY] = 1;
        }
        else if (gBattleWeather & WEATHER_STRONG_WINDS && !shouldNotClear)
        {
            gBattleWeather &= ~WEATHER_STRONG_WINDS;
            PrepareStringBattle(STRINGID_STRONGWINDSDISSIPATED, battler);
            gBattleCommunication[MSG_DISPLAY] = 1;
        }
        break;  //add in 2nd round of string updates
    }
    case VARIOUS_GET_ROTOTILLER_TARGETS:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        // Gets the battlers to be affected by rototiller. If there are none, print 'But it failed!'
        {
            u32 count = 0;
            for (i = 0; i < gBattlersCount; i++)
            {
                gSpecialStatuses[i].rototillerAffected = FALSE;
                if (IsRototillerAffected(i))
                {
                    gSpecialStatuses[i].rototillerAffected = TRUE;
                    count++;
                }
            }
            
            if (count == 0)
                gBattlescriptCurrInstr = cmd->failInstr;   // Rototiller fails
            else
                gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_JUMP_IF_NOT_ROTOTILLER_AFFECTED:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gSpecialStatuses[battler].rototillerAffected)
        {
            gSpecialStatuses[battler].rototillerAffected = FALSE;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;   // Unaffected by rototiller - print STRINGID_NOEFFECTONTARGET
        }
        return;
    }
    case VARIOUS_TRY_ACTIVATE_BATTLE_BOND:
    {
        if (gBattleMons[gBattlerAttacker].species == SPECIES_GRENINJA
            && GetBattlerAbility(gBattlerAttacker) == ABILITY_BATTLE_BOND
            && HasAttackerFaintedTarget()
            && CalculateBattlerPartyCount(gBattlerTarget) > 1)
        {
            PREPARE_SPECIES_BUFFER(gBattleTextBuff1, gBattleMons[gBattlerAttacker].species);
            gBattleStruct->changedSpecies[GET_BATTLER_SIDE2(gBattlerAttacker)][gBattlerPartyIndexes[gBattlerAttacker]] = gBattleMons[gBattlerAttacker].species;
            gBattleMons[gBattlerAttacker].species = SPECIES_GRENINJA_ASH;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BattleBondActivatesOnMoveEndAttacker;
            return;
        }
        break;
    }
    case VARIOUS_CONSUME_BERRY:
    {
        VARIOUS_ARGS(bool8 fromBattler);
        if (gBattleScripting.overrideBerryRequirements == 2)
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
            return;
        }

        if (cmd->fromBattler) //if uses attacker or target berry
            gLastUsedItem = gBattleMons[battler].item;

        gBattleStruct->ateBerry[battler & BIT_SIDE] |= 1u << gBattlerPartyIndexes[battler];
        gBattleScripting.battler = gEffectBattler = gBattlerTarget = battler;    // Cover all berry effect battlerId cases. e.g. ChangeStatBuffs uses target ID
        if (ItemBattleEffects(ITEMEFFECT_USE_LAST_ITEM, battler, FALSE))
            return;
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;

    }
    case VARIOUS_JUMP_IF_CANT_REVERT_TO_PRIMAL:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_PRIMAL_REVERSION) == SPECIES_NONE)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_WEATHER_AFFECTED:
    {
        VARIOUS_ARGS(u32 weather, const u8 *jumpInstr);
        u32 weatherFlags = cmd->weather;
        if (IsBattlerWeatherAffected(battler, weatherFlags))
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_APPLY_PLASMA_FISTS:
    {
        for (i = 0; i < gBattlersCount; i++)
            gStatuses4[i] |= STATUS4_PLASMA_FISTS;
        break;
    }
    case VARIOUS_JUMP_IF_SPECIES:
    {
        VARIOUS_ARGS(u16 species, const u8 *jumpInstr);
        if (gBattleMons[battler].species == cmd->species)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_PHOTON_GEYSER_CHECK: //added EE updated version below commented out for now
    {
        u32 attackerAtkStat = gBattleMons[gBattlerAttacker].attack;
        u8 attackerAtkStage = gBattleMons[gBattlerAttacker].statStages[STAT_ATK];
        u32 attackerSpAtkStat = gBattleMons[gBattlerAttacker].spAttack;

        gSwapDamageCategory = FALSE;

        attackerAtkStat *= gStatStageRatios[attackerAtkStage][0];
        attackerAtkStat /= gStatStageRatios[attackerAtkStage][1];

        attackerAtkStage = gBattleMons[gBattlerAttacker].statStages[STAT_SPATK];
        attackerSpAtkStat *= gStatStageRatios[attackerAtkStage][0];
        attackerSpAtkStat /= gStatStageRatios[attackerAtkStage][1];

        if (attackerAtkStat > attackerSpAtkStat)
            gSwapDamageCategory = TRUE;
        break;
    }
    case VARIOUS_SHELL_SIDE_ARM_CHECK:
    { // 0% chance GameFreak actually checks this way according to DaWobblefet, but this is the only functional explanation at the moment
        u32 attackerAtkStat = gBattleMons[gBattlerAttacker].attack;
        u32 targetDefStat = gBattleMons[gBattlerTarget].defense;
        u32 attackerSpAtkStat = gBattleMons[gBattlerAttacker].spAttack;
        u32 targetSpDefStat = gBattleMons[gBattlerTarget].spDefense;
        u8 statStage;
        u32 physical;
        u32 special;

        gSwapDamageCategory = FALSE;

        statStage = gBattleMons[gBattlerAttacker].statStages[STAT_ATK];
        attackerAtkStat *= gStatStageRatios[statStage][0];
        attackerAtkStat /= gStatStageRatios[statStage][1];

        statStage = gBattleMons[gBattlerTarget].statStages[STAT_DEF];
        targetDefStat *= gStatStageRatios[statStage][0];
        targetDefStat /= gStatStageRatios[statStage][1];

        physical = ((((2 * gBattleMons[gBattlerAttacker].level / 5 + 2) * gBattleMoves[gCurrentMove].power * attackerAtkStat) / targetDefStat) / 50);

        statStage = gBattleMons[gBattlerAttacker].statStages[STAT_SPATK];
        attackerSpAtkStat *= gStatStageRatios[statStage][0];
        attackerSpAtkStat /= gStatStageRatios[statStage][1];

        statStage = gBattleMons[gBattlerTarget].statStages[STAT_SPDEF];
        targetSpDefStat *= gStatStageRatios[statStage][0];
        targetSpDefStat /= gStatStageRatios[statStage][1];

        special = ((((2 * gBattleMons[gBattlerAttacker].level / 5 + 2) * gBattleMoves[gCurrentMove].power * attackerSpAtkStat) / targetSpDefStat) / 50);

        if (((physical > special) || (physical == special && (Random() % 2) == 0)))
            gSwapDamageCategory = TRUE;
        break;
    }
    case VARIOUS_JUMP_IF_LEAF_GUARD_PROTECTED:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (IsLeafGuardProtected(battler))
        {
            gBattlerAbility = battler;
            gBattlescriptCurrInstr = cmd->jumpInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_SET_ATTACKER_STICKY_WEB_USER:
    {
        // For Mirror Armor:"If the Pok�mon with this Ability is affected by Sticky Web, the effect is reflected back to the Pok�mon which set it up.
        //  If Pok�mon which set up Sticky Web is not on the field, no Pok�mon have their Speed lowered."
        gBattlerAttacker = gBattlerTarget;  // Initialize 'fail' condition
        SET_STATCHANGER(STAT_SPEED, 2, TRUE);
        if (gBattleStruct->stickyWebUser != 0xFF)
            gBattlerAttacker = gBattleStruct->stickyWebUser;
        break;
    }
    case VARIOUS_CUT_1_3_HP_RAISE_STATS:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        bool8 atLeastOneStatBoosted = FALSE;
        u16 hpFraction = max(1, gBattleMons[gBattlerAttacker].maxHP / 3);

        for (i = 1; i < NUM_STATS; i++)
        {
            if (CompareStat(gBattlerAttacker, i, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                atLeastOneStatBoosted = TRUE;
                break;
            }
        }
        if (atLeastOneStatBoosted && gBattleMons[gBattlerAttacker].hp > hpFraction)
        {
            gBattleMoveDamage = hpFraction;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        else
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        return;
    }
    case VARIOUS_SET_OCTOLOCK:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gDisableStructs[battler].octolock)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gDisableStructs[battler].octolock = TRUE;
            gBattleMons[battler].status2 |= STATUS2_ESCAPE_PREVENTION;
            gDisableStructs[battler].battlerPreventingEscape = gBattlerAttacker;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_CHECK_POLTERGEIST:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gBattleMons[battler].item == ITEM_NONE
           || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM
           || GetBattlerAbility(battler) == ABILITY_KLUTZ)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            PREPARE_ITEM_BUFFER(gBattleTextBuff1, gBattleMons[battler].item);
            GetItemName(gBattleTextBuff1, gBattleMons[battler].item);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_NO_RETREAT:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gDisableStructs[battler].noRetreat)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            if (!(gBattleMons[battler].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION | STATUS2_SWITCH_LOCKED)))
                gDisableStructs[battler].noRetreat = TRUE;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_TRY_TAR_SHOT:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (gDisableStructs[battler].tarShot)
        {
            gBattlescriptCurrInstr = cmd->failInstr;
        }
        else
        {
            gDisableStructs[battler].tarShot = TRUE;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
        return;
    }
    case VARIOUS_CAN_TAR_SHOT_WORK:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        // Tar Shot will fail if it's already been used on the target and its speed can't be lowered further
        if (!gDisableStructs[battler].tarShot 
            && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
            gBattlescriptCurrInstr = cmd->nextInstr;
        else
            gBattlescriptCurrInstr = cmd->failInstr;
        return;
    }
    case VARIOUS_TRY_TO_APPLY_MIMICRY:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        bool8 isMimicryDone = FALSE;

        if (GetBattlerAbility(battler) == ABILITY_MIMICRY)
        {
            TryToApplyMimicry(battler, TRUE);
            isMimicryDone = TRUE;
        }
        if (!isMimicryDone)
            gBattlescriptCurrInstr = cmd->failInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_CANT_FLING:
    {
        VARIOUS_ARGS(const u8 *failInstr);
        if (!CanFling(battler))
            gBattlescriptCurrInstr = cmd->failInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_CURE_CERTAIN_STATUSES:
    {
        VARIOUS_ARGS();
        // Check infatuation
        if (gBattleMons[battler].status2 & STATUS2_INFATUATION)
        {
            gBattleMons[battler].status2 &= ~(STATUS2_INFATUATION);
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_INFATUATION;  // STRINGID_TARGETGOTOVERINFATUATION
            StringCopy(gBattleTextBuff1, gStatusConditionString_LoveJpn);
        }
        // Check taunt
        if (gDisableStructs[battler].tauntTimer != 0)
        {
            gDisableStructs[battler].tauntTimer = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_TAUNT;
            PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_TAUNT);
        }
        // Check encore
        if (gDisableStructs[battler].encoreTimer != 0)
        {
            gDisableStructs[battler].encoredMove = 0;
            gDisableStructs[battler].encoreTimer = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_ENCORE;   // STRINGID_PKMNENCOREENDED
        }
        // Check torment
        if (gBattleMons[battler].status2 & STATUS2_TORMENT)
        {
            gBattleMons[battler].status2 &= ~(STATUS2_TORMENT);
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_TORMENT;
        }
        // Check disable
        if (gDisableStructs[battler].disableTimer != 0)
        {
            gDisableStructs[battler].disableTimer = 0;
            gDisableStructs[battler].disabledMove = 0;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_DISABLE;
        }
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_TRY_RESET_NEGATIVE_STAT_STAGES:
    {
        VARIOUS_ARGS();
        battler = gBattlerTarget;
        for (i = 0; i < NUM_BATTLE_STATS; i++)
            if (gBattleMons[battler].statStages[i] < DEFAULT_STAT_STAGE)
                gBattleMons[battler].statStages[i] = DEFAULT_STAT_STAGE;
        gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_LAST_USED_ITEM_BERRY:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (ItemId_GetPocket(gLastUsedItem) == POCKET_BERRY_POUCH)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_LAST_USED_ITEM_HOLD_EFFECT:
    {
        VARIOUS_ARGS(u8 holdEffect, const u8 *jumpInstr);
        if (ItemId_GetHoldEffect(gLastUsedItem) == cmd->holdEffect)
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_WAIT_FANFARE:
    {
        if (!IsFanfareTaskInactive())
            return;
        break;
    }
    case VARIOUS_SAVE_BATTLER_ITEM:
    {
        gBattleResources->battleHistory->heldItems[battler] = gBattleMons[battler].item;
        break;
    }
    case VARIOUS_RESTORE_BATTLER_ITEM:
    {
        gBattleMons[battler].item = gBattleResources->battleHistory->heldItems[battler];
        break;
    }
    case VARIOUS_BATTLER_ITEM_TO_LAST_USED_ITEM:
    {
        gBattleMons[battler].item = gLastUsedItem;
        break;
    }
    case VARIOUS_JUMP_IF_EMERGENCY_EXITED:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (gSpecialStatuses[battler].EmergencyExit)   //if true
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    case VARIOUS_JUMP_IF_BATTLE_END:
    {
        VARIOUS_ARGS(const u8 *jumpInstr);
        if (NoAliveMonsForEitherParty())
            gBattlescriptCurrInstr = cmd->jumpInstr;
        else
            gBattlescriptCurrInstr = cmd->nextInstr;
        return;
    }
    
    
    } // End of switch (gBattlescriptCurrInstr[2])

    gBattlescriptCurrInstr = cmd->nextInstr;
}
    
void BS_TryQuash(void)
{
    NATIVE_ARGS(const u8 *failInstr);
    u32 i;

    // It's true if foe is faster, has a bigger priority, or switches
    if (GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget))
    {
        gBattlescriptCurrInstr = cmd->failInstr;
        return;
    }

    // If the above condition is not true, it means we are faster than the foe, so we can set the quash bit
    gProtectStructs[gBattlerTarget].quash = TRUE;
    for (i = 0; i < gBattlersCount; i++)
    {
        gBattlerByTurnOrder[i] = i;
    }
    for (i = 0; i < gBattlersCount - 1; i++)
    {
        s32 j;
        for (j = i + 1; j < gBattlersCount; j++)
        {
            if (!gProtectStructs[i].quash
             && !gProtectStructs[j].quash
             && GetWhoStrikesFirst(gBattlerByTurnOrder[i], gBattlerByTurnOrder[j], FALSE))
                SwapTurnOrder(i, j);
        }
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

void BS_CheckParentalBondCounter(void)
{
    NATIVE_ARGS(u8 counter, const u8 *jumpInstr);
    // Some effects should only happen on the first or second strike of Parental Bond,
    // so a way to check this in battle scripts is useful
    if (gSpecialStatuses[gBattlerAttacker].parentalBondState == cmd->counter && IsBattlerAlive(gBattlerTarget))
        gBattlescriptCurrInstr = cmd->jumpInstr;
    else
        gBattlescriptCurrInstr = cmd->nextInstr;
}

/*void BS_SetPhotonGeyserCategory(void)
{
    NATIVE_ARGS();
    if (!((gMovesInfo[gCurrentMove].effect == EFFECT_TERA_BLAST && GetActiveGimmick(gBattlerAttacker) != GIMMICK_TERA)
            || (gMovesInfo[gCurrentMove].effect == EFFECT_TERA_STARSTORM && GetActiveGimmick(gBattlerAttacker) != GIMMICK_TERA && gBattleMons[gBattlerAttacker].species == SPECIES_TERAPAGOS_STELLAR)))
        gBattleStruct->swapDamageCategory = (GetCategoryBasedOnStats(gBattlerAttacker) != gMovesInfo[gCurrentMove].category);
    gBattlescriptCurrInstr = cmd->nextInstr;
}*/

static void atk77_setprotectlike(void)
{
    CMD_ARGS();

    bool32 fail = TRUE;
    bool32 notLastTurn = TRUE;

    if (!(gBattleMoves[gLastResultingMoves[gBattlerAttacker]].flags & FLAG_PROTECTION_MOVE))
        gDisableStructs[gBattlerAttacker].protectUses = 0;

    if (gCurrentTurnActionNumber == (gBattlersCount - 1))
        notLastTurn = FALSE;
    if (sProtectSuccessRates[gDisableStructs[gBattlerAttacker].protectUses] >= Random() && notLastTurn)
    {
        if (!gBattleMoves[gCurrentMove].argument) // Protects one mon only.
        {
            if (gBattleMoves[gCurrentMove].effect == EFFECT_PROTECT)
            {
                gProtectStructs[gBattlerAttacker].protected = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_ITSELF;
            }
            if (gBattleMoves[gCurrentMove].effect == EFFECT_SHIELD_BASH)
            {
                gProtectStructs[gBattlerAttacker].shieldBashed = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_BRACED_ITSELF;
            }
            if (gBattleMoves[gCurrentMove].effect == EFFECT_ENDURE)
            {
                gProtectStructs[gBattlerAttacker].endured = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_BRACED_ITSELF;
            }
            else if (gCurrentMove == MOVE_SPIKE_SHIELD)
            {
                gProtectStructs[gBattlerAttacker].spikyShielded = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_ITSELF;
            }
            else if (gCurrentMove == MOVE_KINGS_SHIELD)
            {
                gProtectStructs[gBattlerAttacker].kingsShielded = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_ITSELF;
            }
            else if (gCurrentMove == MOVE_BANEFUL_BUNKER)
            {
                gProtectStructs[gBattlerAttacker].banefulBunkered = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_ITSELF;
            }
            else if (gCurrentMove == MOVE_OBSTRUCT)
            {
                gProtectStructs[gBattlerAttacker].obstructed = TRUE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_ITSELF;
            }
            ++gDisableStructs[gBattlerAttacker].protectUses;
            fail = FALSE;
        }
        else // Protects the whole side.
        {
            u8 side = GetBattlerSide(gBattlerAttacker);
            if (gCurrentMove == MOVE_WIDE_GUARD && !(gSideStatuses[side] & SIDE_STATUS_WIDE_GUARD))
            {
                gSideStatuses[side] |= SIDE_STATUS_WIDE_GUARD;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_TEAM;
                ++gDisableStructs[gBattlerAttacker].protectUses;
                fail = FALSE;
            }
            else if (gCurrentMove == MOVE_QUICK_GUARD && !(gSideStatuses[side] & SIDE_STATUS_QUICK_GUARD))
            {
                gSideStatuses[side] |= SIDE_STATUS_QUICK_GUARD;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_TEAM;
                ++gDisableStructs[gBattlerAttacker].protectUses;
                fail = FALSE;
            }
            else if (gCurrentMove == MOVE_CRAFTY_SHIELD && !(gSideStatuses[side] & SIDE_STATUS_CRAFTY_SHIELD))
            {
                gSideStatuses[side] |= SIDE_STATUS_CRAFTY_SHIELD;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_TEAM;
                ++gDisableStructs[gBattlerAttacker].protectUses;
                fail = FALSE;
            }
            else if (gCurrentMove == MOVE_MAT_BLOCK && !(gSideStatuses[side] & SIDE_STATUS_MAT_BLOCK))
            {
                gSideStatuses[side] |= SIDE_STATUS_MAT_BLOCK;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PROTECTED_TEAM;
                fail = FALSE;
            }
        }
        
        
    }
    if (fail)
    {
        gDisableStructs[gBattlerAttacker].protectUses = 0;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        gMoveResultFlags |= MOVE_RESULT_MISSED;
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

#define NEW_STURDY_EFFECT
static void atk78_faintifabilitynotdamp(void) //explosion
{
    if (!gBattleControllerExecFlags)
    {
        for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; ++gBattlerTarget)
            if (GetBattlerAbility(gBattlerTarget) == ABILITY_DAMP)
                break;
        if (gBattlerTarget == gBattlersCount)
        {
            gActiveBattler = gBattlerAttacker;

            if (CanSurviveInstantKOWithSturdy(gActiveBattler)) //ok remember this was added to not make it spamable
            {
                gBattleMoveDamage = (gBattleMons[gActiveBattler].hp - 1);//hopefully limits explosion to once per battle for mon whenever special status are cleared in main
                RecordAbilityBattle(gActiveBattler, ABILITY_STURDY);
                gLastUsedAbility = ABILITY_STURDY;
            }
            else
                gBattleMoveDamage = gBattleMons[gActiveBattler].hp;
            BtlController_EmitHealthBarUpdate(0, INSTANT_HP_BAR_DROP);   //moves hp bar, not actually doing damage, that's in setatkhptozero
            MarkBattlerForControllerExec(gActiveBattler);
            ++gBattlescriptCurrInstr;

            for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; ++gBattlerTarget)
                if (gBattlerTarget != gBattlerAttacker && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget]))
                    break;
        }
        else
        {
            gLastUsedAbility = ABILITY_DAMP;
            RecordAbilityBattle(gBattlerTarget, gBattleMons[gBattlerTarget].ability);
            gBattlescriptCurrInstr = BattleScript_DampStopsExplosion;
        }
    }
}

#define NEW_STURDY_PT2
static void atk79_setatkhptozero(void)//explosion wish healing moves etc.
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = gBattlerAttacker;
        if (CanSurviveInstantKOWithSturdy(gActiveBattler))
        {
            gBattleMons[gActiveBattler].hp = 1;
            gSpecialStatuses[gActiveBattler].sturdyhungon = TRUE;
        }
        else
            gBattleMons[gActiveBattler].hp = 0;

        BtlController_EmitSetMonData(0, REQUEST_HP_BATTLE, 0, 2, &gBattleMons[gActiveBattler].hp);
        MarkBattlerForControllerExec(gActiveBattler);
        ++gBattlescriptCurrInstr;
    }
}

static void atk7A_jumpifnexttargetvalid(void)
{
    const u8 *jumpPtr = T1_READ_PTR(gBattlescriptCurrInstr + 1);

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        for (++gBattlerTarget; ; ++gBattlerTarget)
            if (gBattlerTarget != gBattlerAttacker && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget]))
                break;
        if (gBattlerTarget >= gBattlersCount)
            gBattlescriptCurrInstr += 5;
        else
            gBattlescriptCurrInstr = jumpPtr;
    }
    else
    {
        gBattlescriptCurrInstr += 5;
    }
}

static void atk7B_tryhealportionhealth(void)
{
    const u8 *failPtr = T1_READ_PTR(gBattlescriptCurrInstr + 1);

    if (gBattlescriptCurrInstr[5] == BS_ATTACKER)
        gBattlerTarget = gBattlerAttacker;
        
    if (gCurrentMove != MOVE_PURIFY && gCurrentMove != MOVE_ROOST)
        gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 3;
    else
        gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 2; //since purify is so specific that gets to keep half health heal /same for roost

    if (gBattleMoveDamage == 0)
        gBattleMoveDamage = 1;
    gBattleMoveDamage *= -1;
    if (gBattleMons[gBattlerTarget].hp == gBattleMons[gBattlerTarget].maxHP)
        gBattlescriptCurrInstr = failPtr;
    else
        gBattlescriptCurrInstr += 6;
}

//nvm plannin gcustom versino if possible
static void atk7C_trymirrormove(void) //need update with emerald logic  vsonic
{
    s32 validMovesCount;
    s32 i;
    u16 move;
    u16 movesArray[3];

    for (i = 0; i < 3; ++i)
        movesArray[i] = 0;
    for (validMovesCount = 0, i = 0; i < gBattlersCount; ++i)
    {

        if (i != gBattlerAttacker)
        {
            move = gBattleStruct->lastTakenMoveFrom[gBattlerAttacker][i];
            if (move != MOVE_NONE && move != 0xFFFF)
                movesArray[validMovesCount++] = move;
        }
    }
    move = gBattleStruct->lastTakenMove[gBattlerAttacker]; //not quite what it should be, should ne just targetted doesn't have to be hit  by uit
    //move++;move--;  the hell is this??
    if (move != MOVE_NONE && move != 0xFFFF)
    {
        gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
        gCurrentMove = move;
        gBattlerTarget = GetMoveTarget(gCurrentMove, 0);
        SetAtkCancellerForCalledMove();
        gBattlescriptCurrInstr = gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect];
    }
    else if (validMovesCount != 0)
    {
        gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
        i = Random() % validMovesCount;
        gCurrentMove = movesArray[i];
        gBattlerTarget = GetMoveTarget(gCurrentMove, 0);
        SetAtkCancellerForCalledMove();
        gBattlescriptCurrInstr = gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect];
    }
    else
    {
        gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = TRUE;
        ++gBattlescriptCurrInstr;
    }
}

static void atk7E_setreflect(void)
{
    if (gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_REFLECT)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    else
    {
        gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] |= SIDE_STATUS_REFLECT;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].reflectTimer = 5;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].reflectBattlerId = gBattlerAttacker;

        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && CountAliveMonsInBattle(BATTLE_ALIVE_ATK_SIDE) == 2)
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        else
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    ++gBattlescriptCurrInstr;
}

static void atk7F_setseeded(void)  //removed grass immunity - revisit
{
    if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT || gStatuses3[gBattlerTarget] & STATUS3_LEECHSEED)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    /*else if (IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GRASS))  //grass being immune to leechseed makes no sense to me, they have energy too.
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2; //matter of fact, since they're actually plants I'd expect it to be MORE effective against them.
    }*/ // or at least heal for more i.e be more nutrient rich, same if used against ground, or water type, well maybe more water types, 
    //since grounded isn't necessarily made of earth, just more suited for the dry environment.  also plants can steal nutrients from other plants, typically throughts roots so more or less same
    else
    {
        gStatuses3[gBattlerTarget] |= gBattlerAttacker; //figure what this does    //is it hits? STATUS3_LEECHSEED_BATTLER
        gStatuses3[gBattlerTarget] |= STATUS3_LEECHSEED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    ++gBattlescriptCurrInstr;
}

static void atk80_manipulatedamage(void)
{
    CMD_ARGS(u8 mode);
    switch (cmd->mode) //reads value 1 byte after command, i.e next argument in script
    {
    case NEGATIVE_DMG:
        gBattleMoveDamage *= -1;
        break;
    case RECOIL_DMG:    //think will separate thisback out
        ///do based on move effect  
        if (gBattleMoveDamage > gHpDealt)
            gBattleMoveDamage = gHpDealt;//ok reason this was wrong, was because it was after dmg calc
            //so target hp was already 0 if I fainted them, therefore assigning dmg to 0 making recoil just 1
            //should be fine now, think I had set it to target hp...

        switch (gBattleMoves[gCurrentMove].effect)
        {
            case EFFECT_50_RECOIL:   //head smash etc.
                gBattleMoveDamage = ((gBattleMons[gBattlerAttacker].maxHP / 10) + (gBattleMoveDamage / 10));
                gBattleMoveDamage *= 8;
                gBattleMoveDamage /= 3;
                //gBattleMoveDamage /= 2;
            break;
            case EFFECT_RECOIL:
                gBattleMoveDamage = ((gBattleMons[gBattlerAttacker].maxHP / 10) + (gBattleMoveDamage / 10));
                //gBattleMoveDamage /= 4; //w raichu min dmg should be 3
            break;
            case EFFECT_33_RECOIL_W_STATUS: //volt tackle etc.
            case EFFECT_DOUBLE_EDGE:
                gBattleMoveDamage = ((gBattleMons[gBattlerAttacker].maxHP / 10) + (gBattleMoveDamage / 10));
                gBattleMoveDamage += (gBattleMoveDamage / 2);
                //gBattleMoveDamage /= 3; //double edge damag
            break;
        }

        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_PARENTAL_BOND)
            gBattleMoveDamage *= 2;

        //vsonic potentially turn above into macro for ease o fuse

        //believe need this since not tied to hp dealt,
        //with supers etc. it would calc higher
        //honestly don't really like this the more I test/use it
        // the miss effect makes more sense, just use my hp not targets
        //how much they feel the hit is based on their stats
        //how hard I feel the hit should be based on my own
         

        //ok new formula 1/8th of max hp + 1/10th of damage done
        //still limited to the lesser of enemy remaining health
        //idea being using the move hurts a fixed amount,
        //and the other part is a scaler for how hard i'm hitting


        //gbattlemovedamage += (gbattlemovedamage / 3) //for 1/3rd and 1/2 add extra 3rd or 1/2 of formula?

        //if (gBattleMoves[gCurrentMove].effect == EFFECT_50_RECOIL) //believe was initially hi jump kick miss?
        //    gBattleMoveDamage /= 2;

       /* if ((gBattleMons[gBattlerTarget].maxHP / 3) < gBattleMoveDamage)
            gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 3;*/  //removed doesn't make sense even if helpful, plus gen4 removed it anyway

        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        break;  //only used for recoil miss, make define so can use name properly, oh I already did
    case RECOIL_MISS_DMG:
        if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT) //miss
            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;    //dmg for immunity rolled into one command
        
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        break;
    case DOUBLE_DMG:
        gBattleMoveDamage *= 2;
        break;
    case DMG_1_8_TARGET_HP:
        gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 8;
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        break;
    case DMG_FULL_ATTACKER_HP:
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP;
        break;
    case DMG_CURR_ATTACKER_HP:
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].hp;
        break;
    case DMG_BIG_ROOT:  //think handled in util.c can skip
        gBattleMoveDamage = GetDrainedBigRootHp(gBattlerAttacker, gBattleMoveDamage);
        break; //nope this uses the battle_util.c stuff actually, gbattlemovedamage argument ie heal amount, is set from sethpdrain bs command
    case DMG_1_2_ATTACKER_HP:
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 2;
        break;
    case DMG_RECOIL_FROM_IMMUNE:
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4; //think no longer need can just use top recoil effect
        break;
    
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atk81_trysetrest(void) //would be useful to track if sleep was set with rest, with my new changes, hmm could make status3 rest? or status4 set it here and remove when sleep turns end if it is on
{
    const u8 *failJump = T1_READ_PTR(gBattlescriptCurrInstr + 1); //keep onback burner test rest first 
    
    gActiveBattler = gBattlerTarget = gBattlerAttacker;
    gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP * (-1);
    if (gBattleMons[gBattlerTarget].hp == gBattleMons[gBattlerTarget].maxHP)
    {
        gBattlescriptCurrInstr = failJump;
    }
    else
    {
        if (gBattleMons[gBattlerTarget].status1 & ((u8)(~STATUS1_SLEEP)))
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        else
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        gBattleMons[gBattlerTarget].status1 = STATUS1_SLEEP;
        gBattleStruct->SleepTimer[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)] = 3; //sleep turns rest is fixed
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 5;
    }
}

static void atk82_jumpifnotfirstturn(void)
{
    const u8 *failJump = T1_READ_PTR(gBattlescriptCurrInstr + 1);

    if (gDisableStructs[gBattlerAttacker].isFirstTurn)
        gBattlescriptCurrInstr += 5;
    else
        gBattlescriptCurrInstr = failJump;
}

static void atk83_nop(void)
{
    ++gBattlescriptCurrInstr;
}

bool8 UproarWakeUpCheck(u8 battlerId)
{
    s32 i;

    for (i = 0; i < gBattlersCount; ++i)
    {
        if (!(gBattleMons[i].status2 & STATUS2_UPROAR)
         || gBattleMons[battlerId].ability == ABILITY_SOUNDPROOF)
            continue;
        gBattleScripting.battler = i;

        if (gBattlerTarget == 0xFF)
            gBattlerTarget = i;
        else if (gBattlerTarget == i)
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        else
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        break;
    }
    if (i == gBattlersCount)
        return FALSE;
    else
        return TRUE;
}

static void atk84_jumpifcantmakeasleep(void) //vsonic keep an eye on/check EE
{
    const u8 *jumpPtr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    u16 ability = GetBattlerAbility(gBattlerTarget);

    if (UproarWakeUpCheck(gBattlerTarget))
    {
        gBattlescriptCurrInstr = jumpPtr;
    }
    else if (ability == ABILITY_INSOMNIA
        || ability == ABILITY_VITAL_SPIRIT
        || ability == ABILITY_COMATOSE
        || gSideStatuses[GetBattlerSide(gBattlerTarget)] & SIDE_STATUS_SAFEGUARD
        || IsAbilityOnSide(gBattlerTarget, ABILITY_SWEET_VEIL)
        || IsAbilityOnSide(gBattlerTarget, ABILITY_AURA_OF_LIGHT)
        || IsAbilityStatusProtected(gBattlerTarget)
        || IsBattlerTerrainAffected(gBattlerTarget, STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_MISTY_TERRAIN))
    {
        gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        gBattlescriptCurrInstr = jumpPtr;
        RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
    }
    else
    {
        gBattlescriptCurrInstr += 5;
    }
}

static void atk85_stockpile(void)
{
    if (gDisableStructs[gBattlerAttacker].stockpileCounter == 3)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    else
    {
        ++gDisableStructs[gBattlerAttacker].stockpileCounter;
        PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[gBattlerAttacker].stockpileCounter)
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    ++gBattlescriptCurrInstr;
}

static void atk86_stockpiletobasedamage(void)
{
    const u8 *jumpPtr = T1_READ_PTR(gBattlescriptCurrInstr + 1);

    if (gDisableStructs[gBattlerAttacker].stockpileCounter == 0)
    {
        gBattlescriptCurrInstr = jumpPtr;
    }
    else
    {
        if (gBattleCommunication[6] != 1)
        {
            gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker], &gBattleMons[gBattlerTarget], gCurrentMove,
                                                    gSideStatuses[GetBattlerSide(gBattlerTarget)], 0,
                                                    0, gBattlerAttacker, gBattlerTarget)
                                * gDisableStructs[gBattlerAttacker].stockpileCounter;
            gBattleScripting.animTurn = gDisableStructs[gBattlerAttacker].stockpileCounter;

            if (gProtectStructs[gBattlerAttacker].helpingHand)
                gBattleMoveDamage = gBattleMoveDamage * 15 / 10;
        }
        gDisableStructs[gBattlerAttacker].stockpileCounter = 0;
        gBattlescriptCurrInstr += 5;
    }
}

static void atk87_stockpiletohpheal(void)
{
    const u8 *jumpPtr = T1_READ_PTR(gBattlescriptCurrInstr + 1);

    if (gDisableStructs[gBattlerAttacker].stockpileCounter == 0)
    {
        gBattlescriptCurrInstr = jumpPtr;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    else if (gBattleMons[gBattlerAttacker].maxHP == gBattleMons[gBattlerAttacker].hp)
    {
        gDisableStructs[gBattlerAttacker].stockpileCounter = 0;
        gBattlescriptCurrInstr = jumpPtr;
        gBattlerTarget = gBattlerAttacker;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    else
    {
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / (1 << (3 - gDisableStructs[gBattlerAttacker].stockpileCounter));
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;
        gBattleScripting.animTurn = gDisableStructs[gBattlerAttacker].stockpileCounter;
        gDisableStructs[gBattlerAttacker].stockpileCounter = 0;
        gBattlescriptCurrInstr += 5;
        gBattlerTarget = gBattlerAttacker;
    }
}//vsonic keep an eye on this

//need to make absorbing life from ghosts damaging- DONE  vsonic
//adapted to emerald logic using manipulatedmg big root in script, to set values negative
//actually makes this easier to calc too
//moved ghost drain to big root logic(function) as majority of
//base effect is done in that now anyway
//redid setup to use argumenteffectchance more effiicient setup
static void atk88_sethpdrain(void) 
{
    
    CMD_ARGS();
    u8 argumentchance = gBattleMoves[gCurrentMove].argumentEffectChance;
    //set gbattlemovedamage : normal hp drain dmg
    
    if (gBattleMoves[gCurrentMove].effect == EFFECT_ABSORB && argumentchance == 0)
        gBattleMoveDamage = (gHpDealt / 2);
    else if (gBattleMoves[gCurrentMove].effect == EFFECT_ABSORB && argumentchance != 0) //issue seems to bne this part?
        gBattleMoveDamage = ((gHpDealt * argumentchance) / 100);

    
    if (IsBattlerTerrainAffected(gBattlerAttacker, STATUS_FIELD_MISTY_TERRAIN))
        gBattleMoveDamage = (150 * gBattleMoveDamage) / 100; //may cut down //vsonic

    if (gBattleMoveDamage == 0)
        gBattleMoveDamage = 1; //think this is needed to not freeze?  yup //try removing, some hp issue 
    
    gBattlescriptCurrInstr = cmd->nextInstr;
}

static u16 ReverseStatChangeMoveEffect(u16 moveEffect)
{
    switch (moveEffect)
    {
        // +1
    case MOVE_EFFECT_ATK_PLUS_1:
        return MOVE_EFFECT_ATK_MINUS_1;
    case MOVE_EFFECT_DEF_PLUS_1:
        return MOVE_EFFECT_DEF_MINUS_1;
    case MOVE_EFFECT_SPD_PLUS_1:
        return MOVE_EFFECT_SPD_MINUS_1;
    case MOVE_EFFECT_SP_ATK_PLUS_1:
        return MOVE_EFFECT_SP_ATK_MINUS_1;
    case MOVE_EFFECT_SP_DEF_PLUS_1:
        return MOVE_EFFECT_SP_DEF_MINUS_1;
    case MOVE_EFFECT_ACC_PLUS_1:
        return MOVE_EFFECT_ACC_MINUS_1;
    case MOVE_EFFECT_EVS_PLUS_1:
        return MOVE_EFFECT_EVS_MINUS_1;
        // -1
    case MOVE_EFFECT_ATK_MINUS_1:
        return MOVE_EFFECT_ATK_PLUS_1;
    case MOVE_EFFECT_DEF_MINUS_1:
        return MOVE_EFFECT_DEF_PLUS_1;
    case MOVE_EFFECT_SPD_MINUS_1:
        return MOVE_EFFECT_SPD_PLUS_1;
    case MOVE_EFFECT_SP_ATK_MINUS_1:
        return MOVE_EFFECT_SP_ATK_PLUS_1;
    case MOVE_EFFECT_SP_DEF_MINUS_1:
        return MOVE_EFFECT_SP_DEF_PLUS_1;
    case MOVE_EFFECT_ACC_MINUS_1:
        return MOVE_EFFECT_ACC_PLUS_1;
    case MOVE_EFFECT_EVS_MINUS_1:
        // +2
    case MOVE_EFFECT_ATK_PLUS_2:
        return MOVE_EFFECT_ATK_MINUS_2;
    case MOVE_EFFECT_DEF_PLUS_2:
        return MOVE_EFFECT_DEF_MINUS_2;
    case MOVE_EFFECT_SPD_PLUS_2:
        return MOVE_EFFECT_SPD_MINUS_2;
    case MOVE_EFFECT_SP_ATK_PLUS_2:
        return MOVE_EFFECT_SP_ATK_MINUS_2;
    case MOVE_EFFECT_SP_DEF_PLUS_2:
        return MOVE_EFFECT_SP_DEF_MINUS_2;
    case MOVE_EFFECT_ACC_PLUS_2:
        return MOVE_EFFECT_ACC_MINUS_2;
    case MOVE_EFFECT_EVS_PLUS_2:
        return MOVE_EFFECT_EVS_MINUS_2;
        // -2
    case MOVE_EFFECT_ATK_MINUS_2:
        return MOVE_EFFECT_ATK_PLUS_2;
    case MOVE_EFFECT_DEF_MINUS_2:
        return MOVE_EFFECT_DEF_PLUS_2;
    case MOVE_EFFECT_SPD_MINUS_2:
        return MOVE_EFFECT_SPD_PLUS_2;
    case MOVE_EFFECT_SP_ATK_MINUS_2:
        return MOVE_EFFECT_SP_ATK_PLUS_2;
    case MOVE_EFFECT_SP_DEF_MINUS_2:
        return MOVE_EFFECT_SP_DEF_PLUS_2;
    case MOVE_EFFECT_ACC_MINUS_2:
        return MOVE_EFFECT_ACC_PLUS_2;
    case MOVE_EFFECT_EVS_MINUS_2:
        return MOVE_EFFECT_EVS_PLUS_2;
    }
}

#define STAT_CHANGE_WORKED      0
#define STAT_CHANGE_DIDNT_WORK  1

//all stat changes go through this function, if from a move effect sets statId in setmoveeffect than calls this function.
//if from ability uses setstatchanger for Id & stat stage, and has a statbuffchange comamnd in their bs, that calls this function using value from setstatchanger
//flag mirror armor prevents stat change from being reflected by mirror armor?
//flag move affects user should make stat apply on attacker rather than target -I think
#define STAT_CHANGE_ABILITIES
static u32 ChangeStatBuffs(s8 statValue, u32 statId, u32 flags, const u8 *BS_ptr)
{
    bool32 certain = FALSE;
    bool32 notProtectAffected = FALSE;
    u32 index;
    u16 activeBattlerAbility;
    bool32 affectsUser = (flags & MOVE_EFFECT_AFFECTS_USER);
    bool32 mirrorArmored = (flags & STAT_CHANGE_MIRROR_ARMOR);
    

    if (affectsUser)
        gActiveBattler = gBattlerAttacker;
    else
        gActiveBattler = gBattlerTarget;

    activeBattlerAbility = GetBattlerAbility(gActiveBattler);

    gSpecialStatuses[gActiveBattler].changedStatsBattlerId = gBattlerAttacker;

    flags &= ~(MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_MIRROR_ARMOR);

    if (flags & MOVE_EFFECT_CERTAIN)
        certain = TRUE;
    flags &= ~(MOVE_EFFECT_CERTAIN);

    if (flags & STAT_CHANGE_NOT_PROTECT_AFFECTED)
        ++notProtectAffected;
    flags &= ~(STAT_CHANGE_NOT_PROTECT_AFFECTED);


    if (activeBattlerAbility == ABILITY_CONTRARY)
    {
        statValue ^= STAT_BUFF_NEGATIVE;
        gBattleScripting.statChanger ^= STAT_BUFF_NEGATIVE;
        RecordAbilityBattle(gActiveBattler, activeBattlerAbility);
        if (flags & STAT_CHANGE_UPDATE_MOVE_EFFECT)
        {
            flags &= ~STAT_CHANGE_UPDATE_MOVE_EFFECT;
            gBattleScripting.moveEffect = ReverseStatChangeMoveEffect(gBattleScripting.moveEffect);
        }
    }
    else if (activeBattlerAbility == ABILITY_SIMPLE)
    {
        statValue = (SET_STAT_BUFF_VALUE(GET_STAT_BUFF_VALUE(statValue) * 2)) | ((statValue <= -1) ? STAT_BUFF_NEGATIVE : 0);
    }

    PREPARE_STAT_BUFFER(gBattleTextBuff1, statId)

    if (statValue <= -1) // Stat decrease.
    {
        //these are set of exclusions that prevenet stat drop
        //afterwards it attempts to do stat change
        if (gSideTimers[GET_BATTLER_SIDE(gActiveBattler)].mistTimer
            && IsBlackFogNotOnField()
            && !certain && gCurrentMove != MOVE_CURSE
            && !(gActiveBattler == gBattlerTarget && GetBattlerAbility(gBattlerAttacker) == ABILITY_INFILTRATOR)
            && !(GetBattlerAbility(BATTLE_PARTNER(gBattlerAttacker)) == ABILITY_CACOPHONY && gBattleMoves[gCurrentMove].flags & FLAG_SOUND))
        {
            if (flags == STAT_CHANGE_BS_PTR)
            {
                if (gSpecialStatuses[gActiveBattler].statLowered)
                {
                    gBattlescriptCurrInstr = BS_ptr;
                }
                else
                {
                    BattleScriptPush(BS_ptr);
                    gBattleScripting.battler = gActiveBattler;
                    gBattlescriptCurrInstr = BattleScript_MistProtected;
                    gSpecialStatuses[gActiveBattler].statLowered = 1;
                }
            }
            return STAT_CHANGE_DIDNT_WORK;
        }
        else if (gCurrentMove != MOVE_CURSE
            && notProtectAffected != TRUE && JumpIfMoveAffectedByProtect(0))
        {
            gBattlescriptCurrInstr = BattleScript_ButItFailed;
            return STAT_CHANGE_DIDNT_WORK;
        }
        else if ((activeBattlerAbility == ABILITY_CLEAR_BODY
                  || activeBattlerAbility == ABILITY_LEAF_GUARD
                  || activeBattlerAbility == ABILITY_WHITE_SMOKE
                  || activeBattlerAbility == ABILITY_FULL_METAL_BODY
                  || activeBattlerAbility == ABILITY_LIQUID_METAL)
            && (!affectsUser || mirrorArmored) && !certain && gCurrentMove != MOVE_CURSE)
        {
            if (flags == STAT_CHANGE_BS_PTR)
            {
                if (gSpecialStatuses[gActiveBattler].statLowered)
                {
                    gBattlescriptCurrInstr = BS_ptr;
                }
                else
                {
                    BattleScriptPush(BS_ptr);
                    gBattleScripting.battler = gActiveBattler;
                    //gBattlerAbility = gActiveBattler;
                    gBattlescriptCurrInstr = BattleScript_AbilityNoStatLoss;
                    gLastUsedAbility = activeBattlerAbility;
                    RecordAbilityBattle(gActiveBattler, gLastUsedAbility);
                    gSpecialStatuses[gActiveBattler].statLowered = 1;
                }
            }
            return STAT_CHANGE_DIDNT_WORK;
        }
        else if ((IsFlowerVeilProtected(gActiveBattler)) && !certain) //thinnk this will work?
        {
            if (flags == STAT_CHANGE_BS_PTR)
            {
              
                    BattleScriptPush(BS_ptr);
                    gBattleScripting.battler = gActiveBattler;
                    //gBattlerAbility = index - 1;
                    gBattlerAbility = ABILITY_FLOWER_VEIL; //think thi sis right?
                    gBattlescriptCurrInstr = BattleScript_FlowerVeilProtectsRet;
                    gLastUsedAbility = ABILITY_FLOWER_VEIL;
                    //gSpecialStatuses[gActiveBattler].statLowered = TRUE; pretty sure this should be false

            }
            return STAT_CHANGE_DIDNT_WORK;
        }
        
        else if ((activeBattlerAbility == ABILITY_TANGLED_FEET
            || activeBattlerAbility == ABILITY_QUICK_FEET
            || activeBattlerAbility == ABILITY_RUN_AWAY
            || activeBattlerAbility == ABILITY_AVIATOR)
            && !certain && statId == STAT_SPEED)
        {
            if (flags == STAT_CHANGE_BS_PTR)
            {
                BattleScriptPush(BS_ptr);
                gBattleScripting.battler = gActiveBattler;
                //gBattlerAbility = gActiveBattler;
                gBattlescriptCurrInstr = BattleScript_AbilityNoSpecificStatLoss;
                gLastUsedAbility = activeBattlerAbility;
                RecordAbilityBattle(gActiveBattler, gLastUsedAbility);
            }
            return STAT_CHANGE_DIDNT_WORK;
        }
        
        else if (!certain
        && ((activeBattlerAbility == ABILITY_KEEN_EYE && statId == STAT_ACC)
        || (activeBattlerAbility == ABILITY_SIXTH_SENSE && statId == STAT_ACC)
        || (activeBattlerAbility == ABILITY_HYPER_CUTTER && statId == STAT_ATK)
        || (activeBattlerAbility == ABILITY_BIG_PECKS && statId == STAT_ATK)
        || (activeBattlerAbility == ABILITY_BIG_PECKS && statId == STAT_DEF)))
        {
        if (flags == STAT_CHANGE_BS_PTR)
        {
            BattleScriptPush(BS_ptr);
            gBattleScripting.battler = gActiveBattler;
            //gBattlerAbility = gActiveBattler;
            gBattlescriptCurrInstr = BattleScript_AbilityNoSpecificStatLoss;
            gLastUsedAbility = activeBattlerAbility;
            RecordAbilityBattle(gActiveBattler, gLastUsedAbility);
        }
        return STAT_CHANGE_DIDNT_WORK;
        }

        else if (activeBattlerAbility == ABILITY_MIRROR_ARMOR && !affectsUser && !mirrorArmored && gBattlerAttacker != gBattlerTarget && gActiveBattler == gBattlerTarget)
        {
            if (flags == STAT_CHANGE_BS_PTR)
            {
                SET_STATCHANGER(statId, GET_STAT_BUFF_VALUE(statValue) | STAT_BUFF_NEGATIVE, TRUE);
                BattleScriptPush(BS_ptr);
                gBattleScripting.battler = gActiveBattler;
                gBattlerAbility = gActiveBattler; //says battler ability ut seems to take battler argument not ability?
                if (gCurrentMove == MOVE_NONE)
                    gBattlescriptCurrInstr = BattleScript_MirrorArmorReflect; //skip animation for abilities that stat drop
                else
                    gBattlescriptCurrInstr = BattleScript_MirrorArmorAttackAnimation;
                RecordAbilityBattle(gActiveBattler, activeBattlerAbility);
            }
            return STAT_CHANGE_DIDNT_WORK;
        }
        else if (activeBattlerAbility == ABILITY_EMPATH && !affectsUser && !mirrorArmored && gBattlerAttacker != gBattlerTarget && gActiveBattler == gBattlerTarget)
        {
            if (flags == STAT_CHANGE_BS_PTR) //think not necessary other than being able to set a return at end/outside base logic
            {
                SET_STATCHANGER(statId, GET_STAT_BUFF_VALUE(statValue) | STAT_BUFF_NEGATIVE, TRUE);
                //SET_STATCHANGER2(gBattleScripting.savedStatChanger, statId, GET_STAT_BUFF_VALUE(statValue) | STAT_BUFF_NEGATIVE, TRUE);
                BattleScriptPush(BS_ptr); //used to end original script goes to return, 
                //gBattleScripting.battler = gActiveBattler; //sets battler executing the script
                //gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                //gBattlerAbility = gActiveBattler;
                if (gCurrentMove == MOVE_NONE)
                    gBattlescriptCurrInstr = BattleScript_EmpathActivates; //skip animation for abilities that stat drop
                else
                    gBattlescriptCurrInstr = BattleScript_EmpathAttackAnimation;

                RecordAbilityBattle(gActiveBattler, activeBattlerAbility);//removed affects user, set mirror armor flag instead to avoid loop
            }//WORKS!!  ...effect works but causes graphic glitch when try to attack after, but only with move, doesn't do for ability stat drops...
            //potentially means issue is to do with my  attack animation fix so check that //tested nope that wasn't it...
                return STAT_CHANGE_DIDNT_WORK;  //not sure how thsi and mirror armor avoid looping as they call functions that execute stateebuffchange/this function again.
            //understand now, the bs for mirrr armor sets affectUser, so soon as it starts the battlescript it can't retrigger the logic here
            //so I need to set affectuser  to avoid loop, then I need set battler to gactivebattler so changes apply to correct target
            //since I'm doing changes for different batlres I need to change value of sbattler from within bs which I did.
            //my script ends in ends mirror armor ends in return,  meaning it goes back to original attacker script
            //reason for that is this stupid game puts the stat effects BEFORE the animation, so for moves you have to return to main function
            //for the move to play out correctly.
            //my script can't do that as I'm playing the animation from within my script
            //this isn't a problem for abilities that drop stat as they don't use a move effect
            //but for moves that drop stat its a problem as it prevents the animation from playing.
            //think I can do a check for if gbattlescipting.moveeffect == 0,
            //above the part that change gbattlescriptCurrInstr and just make a separate script
            //above the main one that just does attackanimation & waitanimation
            //-VSONIC IMPORTANT is this still relevant?  need review
        }
        else if (GetBattlerAbility(gActiveBattler) == ABILITY_SHIELD_DUST && !flags)
        {
            return STAT_CHANGE_DIDNT_WORK;
        }
        else // try to decrease
        {
        

            statValue = -GET_STAT_BUFF_VALUE(statValue);
            if (gBattleMons[gActiveBattler].statStages[statId] == 1)
                statValue = -1;
            else if (gBattleMons[gActiveBattler].statStages[statId] == 2 && statValue < -2)
                statValue = -2;
            gBattleTextBuff2[0] = B_BUFF_PLACEHOLDER_BEGIN;
            index = 1;
            if (statValue == -2)
            {
                gBattleTextBuff2[1] = B_BUFF_STRING;
                gBattleTextBuff2[2] = STRINGID_STATHARSHLY;
                gBattleTextBuff2[3] = STRINGID_STATHARSHLY >> 8;
                index = 4;
            }
            else if (statValue <= -3)
            {
                gBattleTextBuff2[1] = B_BUFF_STRING;
                gBattleTextBuff2[2] = STRINGID_SEVERELY & 0xFF;
                gBattleTextBuff2[3] = STRINGID_SEVERELY >> 8;
                index = 4;
            }
            gBattleTextBuff2[index++] = B_BUFF_STRING;
            gBattleTextBuff2[index++] = STRINGID_STATFELL;
            gBattleTextBuff2[index++] = STRINGID_STATFELL >> 8;
            gBattleTextBuff2[index] = B_BUFF_EOS;

            if (gBattleMons[gActiveBattler].statStages[statId] == MIN_STAT_STAGE)
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STAT_WONT_DECREASE;
            else
            {
                //vsonic for eject pack
                //gProtectStructs[gActiveBattler].statFell = TRUE;   // Eject pack, lash out
                gBattleCommunication[MULTISTRING_CHOOSER] = (gBattlerTarget == gActiveBattler); // B_MSG_ATTACKER_STAT_FELL or B_MSG_DEFENDER_STAT_FELL
            }
           //expression not assignment so return either 0 or 1

        }
    }
    else // stat increase
    {
        statValue = GET_STAT_BUFF_VALUE(statValue);
        if (gBattleMons[gActiveBattler].statStages[statId] == 11)   //keep it from raising beyond max
            statValue = 1;
        else if (gBattleMons[gActiveBattler].statStages[statId] == 10 && statValue > 2)
            statValue = 2;
        gBattleTextBuff2[0] = B_BUFF_PLACEHOLDER_BEGIN;
        index = 1;
        if (statValue == 2)
        {
            gBattleTextBuff2[1] = B_BUFF_STRING;
            gBattleTextBuff2[2] = STRINGID_STATSHARPLY;
            gBattleTextBuff2[3] = STRINGID_STATSHARPLY >> 8;
            index = 4;
        }
        else if (statValue >= 3)
        {
            gBattleTextBuff2[1] = B_BUFF_STRING;
            gBattleTextBuff2[2] = STRINGID_DRASTICALLY & 0xFF;
            gBattleTextBuff2[3] = STRINGID_DRASTICALLY >> 8;
            index = 4;
        }
        gBattleTextBuff2[index++] = B_BUFF_STRING;
        gBattleTextBuff2[index++] = STRINGID_STATROSE;
        gBattleTextBuff2[index++] = STRINGID_STATROSE >> 8;
        gBattleTextBuff2[index] = B_BUFF_EOS;

        if (gBattleMons[gActiveBattler].statStages[statId] == MAX_STAT_STAGE)
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STAT_WONT_INCREASE;
        else
        {
            u32 statIncrease;
            if ((statValue + gBattleMons[gActiveBattler].statStages[statId]) > MAX_STAT_STAGE)
                statIncrease = MAX_STAT_STAGE - gBattleMons[gActiveBattler].statStages[statId];
            else
                statIncrease = statValue;
            
            gBattleCommunication[MULTISTRING_CHOOSER] = (gBattlerTarget == gActiveBattler);
            //gProtectStructs[gActiveBattler].statRaised = TRUE;

            // Check Mirror Herb / Opportunist
            /*for (index = 0; index < gBattlersCount; index++)
            {
                if (GetBattlerSide(index) == GetBattlerSide(gActiveBattler))
                    continue; // Only triggers on opposing side

                if (GetBattlerAbility(index) == ABILITY_OPPORTUNIST
                 && gProtectStructs[gActiveBattler].activateOpportunist == 0) // don't activate opportunist on other mon's opportunist raises
                {
                    gProtectStructs[index].activateOpportunist = 2;      // set stats to copy
                }
                if (GetBattlerHoldEffect(index, TRUE) == HOLD_EFFECT_MIRROR_HERB)
                {
                    gProtectStructs[index].eatMirrorHerb = 1;
                }

                if (gProtectStructs[index].activateOpportunist == 2 || gProtectStructs[index].eatMirrorHerb == 1)
                {
                    gQueuedStatBoosts[index].stats |= (1 << (statId - 1));    // -1 to start at atk
                    gQueuedStatBoosts[index].statChanges[statId - 1] += statIncrease;
                }
            }
            */ //vsonic
        }

    }
    gBattleMons[gActiveBattler].statStages[statId] += statValue;
    if (gBattleMons[gActiveBattler].statStages[statId] < MIN_STAT_STAGE)
        gBattleMons[gActiveBattler].statStages[statId] = MIN_STAT_STAGE;
    if (gBattleMons[gActiveBattler].statStages[statId] > MAX_STAT_STAGE)
        gBattleMons[gActiveBattler].statStages[statId] = MAX_STAT_STAGE;

    /*if (gBattleCommunication[MULTISTRING_CHOOSER] == B_MSG_STAT_WONT_INCREASE && flags & STAT_CHANGE_BS_PTR)
        gMoveResultFlags |= MOVE_RESULT_MISSED;*/ //according to GriffinR this is why animation change didn't work
    if (gBattleCommunication[MULTISTRING_CHOOSER] == B_MSG_STAT_WONT_INCREASE && !(flags & STAT_CHANGE_BS_PTR)) //I have no memory of why I changed this...
        return STAT_CHANGE_DIDNT_WORK;
        
    return STAT_CHANGE_WORKED;  //this looks to be the issue, I forgot to put this back...

}//because I changed the battle script I believe this should play the animation
//but still not affect the stats
//it worked animation played, message played, and it still activated the flinch effect
//will need to update ai to be able to switch to clense stats in a way I want.

//will have to give some leeway since ai countering everything like unbound
//insane mode isn't fun, maybe do nothing if they'd die when you're stat boosting
//but switch to their highest defense/resisting mon next
//or switch out the mon after it takes the attack if it calculates it can survive it.
//to the high defense mon.

static void atk89_statbuffchange(void) //alternate logic for if stat change fails,
{
    CMD_ARGS(u16 flags, const u8 *jumpptr);

    u16 flags = cmd->flags;
    const u8 *ptrBefore = gBattlescriptCurrInstr;
    const u8 *jumpPtr = cmd->jumpptr;

    if (ChangeStatBuffs(GET_STAT_BUFF_VALUE_WITH_SIGN(gBattleScripting.statChanger), GET_STAT_BUFF_ID(gBattleScripting.statChanger), flags, jumpPtr) == STAT_CHANGE_WORKED)
        gBattlescriptCurrInstr = cmd->nextInstr;
    else if (gBattlescriptCurrInstr == ptrBefore) // Prevent infinite looping.
        gBattlescriptCurrInstr = jumpPtr;
}/*//important parts are ChangeStatBuffs function (directly above) and the stat change move effect cases in setmoveeffect  ex.MOVE_EFFECT_ATK_PLUS_1
//as well as SetMoveEffect function (needs to be updated to u32) and remembering to adjust include/battle.h battlescripting struct & constants/bs_commands.h
//and replace gBattleCommunication[MOVE_EFFECT_BYTE] with gBattleScripting.moveEffect  in bs_commands.c & battle_util.c
also need to update the macro values for statbuffchange & setmoveeffect in battle_script.inc*/

bool32 TryResetBattlerStatChanges(u8 battler)
{
    u32 j;
    bool32 ret = FALSE;

    gDisableStructs[battler].stockpileDef = 0;
    gDisableStructs[battler].stockpileSpDef = 0;
    for (j = 0; j < NUM_BATTLE_STATS; j++)
    {
        if (gBattleMons[battler].statStages[j] != DEFAULT_STAT_STAGE)
            ret = TRUE; // returns TRUE if any stat was reset

        gBattleMons[battler].statStages[j] = DEFAULT_STAT_STAGE;
    }

    return ret;
}

static void atk8A_normalisebuffs(void) // haze
{
    s32 i, j;

    for (i = 0; i < gBattlersCount; ++i)
        for (j = 0; j < NUM_BATTLE_STATS; ++j)
            gBattleMons[i].statStages[j] = 6;
    ++gBattlescriptCurrInstr;
}

static void atk8B_setbide(void)
{
    if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE))
    {
        gDisableStructs[gBattlerAttacker].bideTimer = 3;//would like ot make timer one turn shorter, but then its a near guaranteed kill?
        gTakenDmg[gBattlerAttacker] = 0; //believe resetting damag to 0 so it doesn't count anything from previous turn?
        gBattleMons[gBattlerAttacker].status2 |= STATUS2_BIDE;
    }
    gBattlescriptCurrInstr++;
}

static void atk8C_confuseifrepeatingattackends(void)
{
    if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_LOCK_CONFUSE))
        gBattleScripting.moveEffect = (MOVE_EFFECT_THRASH | MOVE_EFFECT_AFFECTS_USER);
    ++gBattlescriptCurrInstr;
}

//replaced with upgraded emerald logic set in attack canceler so no longer needed/ can replace
static void atk8D_setmultihitcounter(void)  //setmultihit   looks like I should put skill link here, is it not already setup? do for multitask as well  yeah ABILITY_SKILL_LINK isn't setup yet huh
{
   // gMultiTask = gMultiHitCounter;  //not sure if doing this way will work, but I'll try it
    //multihitcounter is outside of the loop and only run once, so if it copies the value from here
    //instead of directly it may work.
    /*if (gBattlescriptCurrInstr[1]) //if has a value beside command i.e is a fixed hit multi hit move
    {
        gMultiHitCounter = gBattlescriptCurrInstr[1];
    }
    else
    {
        gMultiHitCounter = Random() % 4; //return a number between 0 & 3
        if (gMultiHitCounter > 1) 
            gMultiHitCounter = (Random() % 4) + 2; // if non 0, multihit is between 2-5 htis
        else // value 0 or 1
            gMultiHitCounter += 2; //else add 2 to multi counter, returning a multihit of 2 or 3.
    }
   // gMultiTask = gMultiHitCounter;
    gBattlescriptCurrInstr += 2;*/
    ++gBattlescriptCurrInstr;
}


static void atk8E_initmultihitstring(void)
{
    PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 1, 0)
    ++gBattlescriptCurrInstr;
}

//vsonic see if can use for hit escape etc. if needed?
static bool8 TryDoForceSwitchOut(void)
{
    if (gBattleMons[gBattlerAttacker].level >= gBattleMons[gBattlerTarget].level)
    {
        *(gBattleStruct->battlerPartyIndexes + gBattlerTarget) = gBattlerPartyIndexes[gBattlerTarget];
    }
    else
    {
        u16 random = Random() & 0xFF;
        
        if ((u32)((random * (gBattleMons[gBattlerAttacker].level + gBattleMons[gBattlerTarget].level) >> 8) + 1) <= (gBattleMons[gBattlerTarget].level / 4))
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
            return FALSE;
        }
        *(gBattleStruct->battlerPartyIndexes + gBattlerTarget) = gBattlerPartyIndexes[gBattlerTarget];
    }
    gBattlescriptCurrInstr = BattleScript_SuccessForceOut;
    return TRUE;
}

#define MON_CAN_BATTLE(mon) (((GetMonData(mon, MON_DATA_SPECIES) && GetMonData(mon, MON_DATA_IS_EGG) != TRUE && GetMonData(mon, MON_DATA_HP))))

static void atk8F_forcerandomswitch(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        u8 i;
        struct Pokemon *party;
        u8 valid;
        u8 val;

        if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
            party = gPlayerParty;
        else
            party = gEnemyParty;
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            valid = 0;
            val = 0;
            if (GetLinkTrainerFlankId(GetBattlerMultiplayerId(gBattlerTarget)) == 1)
                val = 3;
            for (i = val; i < val + 3; ++i)
            {
                if (GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE
                 && !GetMonData(&party[i], MON_DATA_IS_EGG)
                 && GetMonData(&party[i], MON_DATA_HP) != 0)
                    ++valid;
            }
        }
        else
        {
            valid = 0;
            for (i = 0; i < 6; ++i) //loops through the party for a valid mon
            {
                if (GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE //is a pokemom
                 && !GetMonData(&party[i], MON_DATA_IS_EGG) //not an egg
                 && GetMonData(&party[i], MON_DATA_HP) != 0) //not fainted
                    ++valid;
            }
        }

        if ((valid < 2 && (gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI)) != BATTLE_TYPE_DOUBLE)
         || (valid < 3 && (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && !(gBattleTypeFlags & BATTLE_TYPE_MULTI)))
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        else if (TryDoForceSwitchOut())
        {
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                do
                {
                    val = Random() % 3;
                    if (GetLinkTrainerFlankId(GetBattlerMultiplayerId(gBattlerTarget)) == 1)
                        i = val + 3;
                    else
                        i = val;
                }
                while (i == gBattlerPartyIndexes[gBattlerTarget]
                      || i == gBattlerPartyIndexes[gBattlerTarget ^ 2]
                      || !MON_CAN_BATTLE(&party[i]));
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                {
                    do
                    {
                        i = Random() % 6;
                    }
                    while (i == gBattlerPartyIndexes[gBattlerTarget]
                        || i == gBattlerPartyIndexes[gBattlerTarget ^ 2]
                        || !MON_CAN_BATTLE(&party[i]));
                }
                else
                {
                    do
                    {
                        i = Random() % 6;
                    }
                    while (i == gBattlerPartyIndexes[gBattlerTarget]
                        || !MON_CAN_BATTLE(&party[i]));
                }
            }
            *(gBattleStruct->monToSwitchIntoId + gBattlerTarget) = i;
            if (!IsMultiBattle())
                UpdatePartyOwnerOnSwitch_NonMulti(gBattlerTarget);
            SwitchPartyOrderLinkMulti(gBattlerTarget, i, 0);
            SwitchPartyOrderLinkMulti(gBattlerTarget ^ 2, i, 1);
        }
    }
    else
    {
        TryDoForceSwitchOut();
    }
}

// randomly changes user's type to one of its moves' type
//incomplete still working on
//changed mind, decided make into gen 6 version of conversion,
//use other idea for conversion 2, instead
//changing to first slot makes better
//both improved consistency and increased versatility
static void atk90_tryconversiontypechange(void)
{
    CMD_ARGS(const u8 *failInstr);

    u8 validMoves = 0;
    u8 moveChecked = 0;
    u8 moveType = 0;

    /*while (validMoves < MAX_MON_MOVES)
    {
        if (gBattleMons[gBattlerAttacker].moves[validMoves] == MOVE_NONE)
            break;
        ++validMoves;
    }
    for (moveChecked = 0; moveChecked < validMoves; ++moveChecked)
    {
        moveType = gBattleMoves[gBattleMons[gBattlerAttacker].moves[moveChecked]].type;
        if (moveType == TYPE_MYSTERY)
        {
            if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GHOST)) //dumb if they are already ghost it would do nothing
                moveType = TYPE_GHOST;
            else
                moveType = TYPE_NORMAL;
        }
        if (moveType != gBattleMons[gBattlerAttacker].type1
            && moveType != gBattleMons[gBattlerAttacker].type2)
        {
            break;
        }
    }
    if (moveChecked == validMoves)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        do
        {
            while ((moveChecked = Random() & 3) >= validMoves);
            moveType = gBattleMoves[gBattleMons[gBattlerAttacker].moves[moveChecked]].type;
            if (moveType == TYPE_MYSTERY)
            {
                if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GHOST))
                    moveType = TYPE_GHOST;
                else
                    moveType = TYPE_NORMAL;
            }
        }
        while (moveType == gBattleMons[gBattlerAttacker].type1
            || moveType == gBattleMons[gBattlerAttacker].type2);
        SET_BATTLER_TYPE(gBattlerAttacker, moveType);
        PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
        gBattlescriptCurrInstr += 5;
    }
    */
    // Changes user's type to its first move's type - ends loop soon as finds a move aka first move
    for (moveChecked = 0; moveChecked < MAX_MON_MOVES; moveChecked++)
    {
        if (gBattleMons[gBattlerAttacker].moves[moveChecked] != MOVE_NONE)
        {
            moveType = gBattleMoves[gBattleMons[gBattlerAttacker].moves[moveChecked]].type;
            break;
        }
    }
    if (IS_BATTLER_OF_TYPE(gBattlerAttacker, moveType))
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
    else
    {
        //SET_BATTLER_TYPE(gBattlerAttacker, moveType);
        if (gCurrentMove == MOVE_CONVERSION)
        gBattleMons[gBattlerAttacker].type1 = moveType;//tweak just change main type, mostly for porygon so swap normal, for alt types
        else if (gCurrentMove == MOVE_CONVERSION_2)
        gBattleMons[gBattlerAttacker].type2 = moveType;
        PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

static void atk91_givepaydaymoney(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK) && gPaydayMoney != 0)
    {
        u32 bonusMoney = gPaydayMoney * gBattleStruct->moneyMultiplier;

        AddMoney(&gSaveBlock1Ptr->money, bonusMoney);
        PREPARE_HWORD_NUMBER_BUFFER(gBattleTextBuff1, 5, bonusMoney)
        BattleScriptPush(gBattlescriptCurrInstr + 1);
        gBattlescriptCurrInstr = BattleScript_PrintPayDayMoneyString;
    }
    else
    {
        ++gBattlescriptCurrInstr;
    }
}

static void atk92_setlightscreen(void)
{
    if (gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_LIGHTSCREEN)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    else
    {
        gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] |= SIDE_STATUS_LIGHTSCREEN;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].lightscreenTimer = 5;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].lightscreenBattlerId = gBattlerAttacker;
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && CountAliveMonsInBattle(BATTLE_ALIVE_ATK_SIDE) == 2)
            gBattleCommunication[MULTISTRING_CHOOSER] = 4;
        else
            gBattleCommunication[MULTISTRING_CHOOSER] = 3;
    }
    ++gBattlescriptCurrInstr;
}

static void atk93_tryKO(void) //EFFECT_OHKO   ohko moves
{
    u8 holdEffect, param;
    u16 targetAbility = GetBattlerAbility(gBattlerTarget);

    if (gBattleMons[gBattlerTarget].item == ITEM_ENIGMA_BERRY)
    {
       holdEffect = gEnigmaBerries[gBattlerTarget].holdEffect;
       param = gEnigmaBerries[gBattlerTarget].holdEffectParam;
    }
    else
    {
        holdEffect = GetBattlerHoldEffect(gBattlerTarget, TRUE);
        param = ItemId_GetHoldEffectParam(gBattleMons[gBattlerTarget].item);
    }
    gPotentialItemEffectBattler = gBattlerTarget;
    if (holdEffect == HOLD_EFFECT_FOCUS_BAND && (Random() % 100) < param)
    {
        RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_FOCUS_BAND);
        gSpecialStatuses[gBattlerTarget].focusBanded = TRUE;
    }

    if (holdEffect == HOLD_EFFECT_FOCUS_SASH && BATTLER_MAX_HP(gBattlerTarget))
    {
        RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_FOCUS_SASH);
        gSpecialStatuses[gBattlerTarget].focusSashed = TRUE;
    }

    if (GetBattlerAbility(gBattlerTarget) == ABILITY_STURDY) //oh forgot this just makes all ohko moves miss
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gLastUsedAbility = ABILITY_STURDY;
        gBattlescriptCurrInstr = BattleScript_SturdyPreventsOHKO;
        RecordAbilityBattle(gBattlerTarget, ABILITY_STURDY);
    }
    else
    {
        u16 chance;

        //decided don't want ot add space control to this
        //would be too much
        if ((((gStatuses3[gBattlerTarget] & STATUS3_ALWAYS_HITS)
                && gDisableStructs[gBattlerTarget].battlerWithSureHit == gBattlerAttacker)
                || GetBattlerAbility(gBattlerAttacker) == ABILITY_NO_GUARD
                || targetAbility == ABILITY_NO_GUARD)
                && !(gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE))
        {
            if (gBattleMons[gBattlerAttacker].level >= (gBattleMons[gBattlerTarget].level - 3))
                chance = TRUE;
            else
                chance = FALSE;
        }
        else //check default setup cant tell what this is
        {   //acc falls lower if below level, now that its possible for move to hit from lower level
            chance = gBattleMoves[gCurrentMove].accuracy + (gBattleMons[gBattlerAttacker].level - gBattleMons[gBattlerTarget].level);

           if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE && gBattleMons[gBattlerAttacker].level > gBattleMons[gBattlerTarget].level)
                chance *=  2;
            else if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE && gBattleMons[gBattlerAttacker].level <= gBattleMons[gBattlerTarget].level)
                chance = chance;
           else if (gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
                chance = 0;
           else
                chance /= 2;

            if (Random() % 100 + 1 < chance && gBattleMons[gBattlerAttacker].level >= (gBattleMons[gBattlerTarget].level - 3))
                chance = TRUE;
            else
                chance = FALSE;
        }
        if (chance) //ohko lands
        {
            if (gProtectStructs[gBattlerTarget].endured)
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
                gMoveResultFlags |= MOVE_RESULT_FOE_ENDURED;
            }
            else if (gSpecialStatuses[gBattlerTarget].focusBanded)
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
                gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
                gLastUsedItem = gBattleMons[gBattlerTarget].item;
            }
            else if (gSpecialStatuses[gBattlerTarget].focusSashed)
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
                gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
                gLastUsedItem = gBattleMons[gBattlerTarget].item;
            }
            else if (gSpecialStatuses[gBattlerTarget].sturdied)
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - 1;
                gMoveResultFlags |= MOVE_RESULT_FOE_HUNG_ON;
                gLastUsedAbility = ABILITY_STURDY;
            }
            else
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].hp;
                gMoveResultFlags |= MOVE_RESULT_ONE_HIT_KO;
            }
            gBattlescriptCurrInstr += 5;
        }
        else
        {
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            if (gBattleMons[gBattlerAttacker].level >= gBattleMons[gBattlerTarget].level - 3)
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 1;
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        } //would like add message specifically for type resist miss, but could just try to fit into move description
    } //was able to fit logic into description
}

static void atk94_damagetohalftargethp(void) // super fang
{
    gBattleMoveDamage = gBattleMons[gBattlerTarget].hp / 2;
    if (gBattleMoveDamage == 0)
        gBattleMoveDamage = 1;
    ++gBattlescriptCurrInstr;
}


static void atk96_weatherdamage(void)
{
    u32 ability = GetBattlerAbility(gBattlerAttacker);

    if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags)
     && (GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT))
    {
        gBattleMoveDamage = 0;
        ++gBattlescriptCurrInstr;
        return;
    }
    if (IsBattlerAlive(gBattlerAttacker) && ability != ABILITY_MAGIC_GUARD
        && !(ability == ABILITY_WONDER_GUARD && gBattleStruct->SingleUseAbilityTimers[gBattlerPartyIndexes[gBattlerAttacker]][GetBattlerSide(gBattlerAttacker)])
        && !DoesSideHaveAbility(gBattlerAttacker, ABILITY_CLOUD_NINE)
        && !(gStatuses3[gBattlerAttacker] & STATUS3_UNDERGROUND)
        && !(gStatuses3[gBattlerAttacker] & STATUS3_UNDERWATER)  
        && !(gStatuses3[gBattlerAttacker] & STATUS3_PHANTOM_FORCE) //specific so flying still affected
        && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_SAFETY_GOGGLES)
    {
        if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SANDSTORM_ANY))
        {
            if (!IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_ROCK)
             && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_STEEL)
             && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GROUND)
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_OVERCOAT
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_RUSH
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_VEIL
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_SAND_FORCE
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_WIND_RIDER  //buff for wind rider, as sandstorm is wind move
             && gBattleMons[gBattlerAttacker].species != SPECIES_CASTFORM)
            {
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 16;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
            }
            else
            {
                gBattleMoveDamage = 0;
            }
        }
        if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_HAIL))
        {
            if (!IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_ICE) //add ice weather abilities
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_OVERCOAT
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_SNOW_CLOAK
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_ICE_BODY
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_ABSOLUTE_ZERO
             && GetBattlerAbility(gBattlerAttacker) != ABILITY_GLACIAL_ICE
             && gBattleMons[gBattlerAttacker].species != SPECIES_CASTFORM)
            {
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 16;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
            }
            else
            {
                gBattleMoveDamage = 0;
            }
        }
    }
    else
    {
        gBattleMoveDamage = 0;
    }
    if (gAbsentBattlerFlags & gBitTable[gBattlerAttacker])
        gBattleMoveDamage = 0;
    ++gBattlescriptCurrInstr;
}

static void atk97_tryinfatuating(void)  
{
    struct Pokemon *monAttacker, *monTarget;
    u16 speciesAttacker, speciesTarget;
    u32 personalityAttacker, personalityTarget;

    u16 targetAbility = GetBattlerAbility(gBattlerTarget);
    u16 attackerAbility = GetBattlerAbility(gBattlerAttacker); //attempt set cupid arrow here
    

    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        monAttacker = &gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]];
    else
        monAttacker = &gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]];
    if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
        monTarget = &gPlayerParty[gBattlerPartyIndexes[gBattlerTarget]];
    else
        monTarget = &gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]];
    speciesAttacker = GetMonData(monAttacker, MON_DATA_SPECIES);
    personalityAttacker = GetMonData(monAttacker, MON_DATA_PERSONALITY);
    speciesTarget = GetMonData(monTarget, MON_DATA_SPECIES);
    personalityTarget = GetMonData(monTarget, MON_DATA_PERSONALITY);

    //cupids arrow works regardless of gender so need figure how do that, or just remove the exclusion for gender from these adn just keep it as it is
    if (targetAbility == ABILITY_OBLIVIOUS) //add ABILITY_FEMME_FATALE in else if, special message femme fatalle prevents infatuation
    {
        if (GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == GetGenderFromSpeciesAndPersonality(speciesTarget, personalityTarget))
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);   //jump to fail condition
        }
        else {
        
            gBattlescriptCurrInstr = BattleScript_AbilityPreventsMoodShift;
            gLastUsedAbility = targetAbility;
            RecordAbilityBattle(gBattlerTarget, targetAbility);
        }
    }
    else if (targetAbility == ABILITY_FEMME_FATALE) //add ABILITY_FEMME_FATALE in else if, special message femme fatalle prevents infatuation
    {
        if (GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == GetGenderFromSpeciesAndPersonality(speciesTarget, personalityTarget)
        /*&& attackerAbility != ABILITY_CUPIDS_ARROW*/)  //remember is ability effect done on switchin so separate from this command
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);   //jump to fail condition
        }
        else {

            gBattlescriptCurrInstr = BattleScript_AbilityFemmeFatale;
            gLastUsedAbility = targetAbility;
            RecordAbilityBattle(gBattlerTarget, targetAbility);
        }
    }
    else
    {
        if (GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == GetGenderFromSpeciesAndPersonality(speciesTarget, personalityTarget)
         || gBattleMons[gBattlerTarget].status2 & STATUS2_INFATUATION
         || GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == MON_GENDERLESS
         || GetGenderFromSpeciesAndPersonality(speciesTarget, personalityTarget) == MON_GENDERLESS)
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);   //jump to fail condition
        }
        else if (gBattleMoves[gCurrentMove].effect != EFFECT_ATTRACT && gBattleMoves[gCurrentMove].effect != EFFECT_ATTRACT_HIT) 
        {
            gBattlescriptCurrInstr += 5; //to exclude other effects taht meets success condition to attract
        }
        else
        {
            gBattleMons[gBattlerTarget].status2 |= STATUS2_INFATUATED_WITH(gBattlerAttacker);//can make attract hit battle script idk if would be unbalanced ?
            gBattlescriptCurrInstr += 5;        //would just need to replace the move end and but it failed jumps, with jumps to the hit battlescript
        }
    }//vsonic come back to this
}

static void atk98_updatestatusicon(void)
{
    if (!gBattleControllerExecFlags)
    {
        if (gBattlescriptCurrInstr[1] == BS_PLAYER2)
        {
            for (gActiveBattler = gBattleControllerExecFlags; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (!(gAbsentBattlerFlags & gBitTable[gActiveBattler]))
                {
                    BtlController_EmitStatusIconUpdate(0, gBattleMons[gActiveBattler].status1, gBattleMons[gActiveBattler].status2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
            gBattlescriptCurrInstr += 2;
        }
        else if (gBattlescriptCurrInstr[1] == BS_ATTACKER_WITH_PARTNER)
        {
            gActiveBattler = gBattlerAttacker;
            if (!(gAbsentBattlerFlags & gBitTable[gActiveBattler]))
            {
                BtlController_EmitStatusIconUpdate(0, gBattleMons[gActiveBattler].status1, gBattleMons[gActiveBattler].status2);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
            {
                gActiveBattler = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_FLANK);
                if (!(gAbsentBattlerFlags & gBitTable[gActiveBattler]))
                {
                    BtlController_EmitStatusIconUpdate(0, gBattleMons[gActiveBattler].status1, gBattleMons[gActiveBattler].status2);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
            gBattlescriptCurrInstr += 2;
        }
        else
        {

            gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);
            BtlController_EmitStatusIconUpdate(0, gBattleMons[gActiveBattler].status1, gBattleMons[gActiveBattler].status2);
            MarkBattlerForControllerExec(gActiveBattler);
            gBattlescriptCurrInstr += 2;
        }
    }
}

static void atk99_setmist(void)
{
    u32 i;

    if (gCurrentMove == MOVE_MIST) {

        if (gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].mistTimer)
        {
            gMoveResultFlags |= MOVE_RESULT_FAILED;
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        }
        else
        {
            gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].mistTimer = 5;
            gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].mistBattlerId = gBattlerAttacker;
            gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] |= SIDE_STATUS_MIST;
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
    }
    else if (gCurrentMove == MOVE_HAZE)
    {
        //if (gFieldTimers.HazeTimer) //haze timer not 0
        if (gFieldStatuses & STATUS_FIELD_BLACK_FOG)
        {
            gMoveResultFlags |= MOVE_RESULT_FAILED;
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        }
        else
        {
            
            gFieldStatuses |= STATUS_FIELD_BLACK_FOG;
            gFieldTimers.HazeTimer = 4; //is 3 turns,  potentially drop to timer 3?idk 
            for (i = 0; i < gBattlersCount; ++i) //since this isn't supposed to change species I'm gonna need to remove status2 one by one to preserve transform
            {
                //gBattleMons[i].status2 &= ~(STATUS2_WRAPPED); nvm just skip effect in util
                gBattleMons[i].status2 &= ~(STATUS2_FOCUS_ENERGY);
                gBattleMons[i].status2 &= ~(STATUS2_RAGE);  //black fog would reset atk boost but this would also let you get a hit in if faster before they use rage again
                gBattleMons[i].status2 &= ~(STATUS2_SUBSTITUTE); //for further consideration
                gBattleMons[i].status2 &= ~(STATUS2_CONFUSION); //doing other effect with confusion is annoying so just remove it here
            }
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }

    }
    ++gBattlescriptCurrInstr;
}

static void atk9A_setfocusenergy(void)
{
    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_FOCUS_ENERGY)
    {
        gMoveResultFlags |= MOVE_RESULT_FAILED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    else
    {
        gBattleMons[gBattlerAttacker].status2 |= STATUS2_FOCUS_ENERGY;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    ++gBattlescriptCurrInstr;
}

static void atk9B_transformdataexecution(void) //add ability check logic, make new ability counter_form, with different transform logic, to change to opposing type mon
{
    gChosenMove = 0xFFFF;
    ++gBattlescriptCurrInstr;
    if (gBattleMons[gBattlerTarget].status2 & STATUS2_TRANSFORMED
        || gStatuses3[gBattlerTarget] & STATUS3_SEMI_INVULNERABLE)
    {
        gMoveResultFlags |= MOVE_RESULT_FAILED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    else //do transform  used for move transform and imposter,  need find portion that makes transform take ivs and evs of target, as well as explicitly only take base stats
    {   //excluding hp
        s32 i;
        u8 *battleMonAttacker, *battleMonTarget;
        struct Pokemon *mon;
        u32 found_species = 0xffff;
        u16 original_ability = GetBattlerAbility(gBattlerAttacker); //store transformer ability for differeing logic
        u16 targetAbility, TransformSpecies;

        gBattleMons[gBattlerAttacker].status2 |= STATUS2_TRANSFORMED;
        gDisableStructs[gBattlerAttacker].disabledMove = MOVE_NONE;
        gDisableStructs[gBattlerAttacker].disableTimer = 0;
        gDisableStructs[gBattlerAttacker].inthralledMove = MOVE_NONE;
        gDisableStructs[gBattlerAttacker].inthrallTimer = 0;
        gDisableStructs[gBattlerAttacker].mimickedMoves = 0;


        if (gCurrentMove == MOVE_TRANSFORM)
        {
            
            PREPARE_SPECIES_BUFFER(gBattleTextBuff1, GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_SPECIES));
        }

        //put new ditto hidden ability species search  here, set to target species
        else if (original_ability == ABILITY_INVERSION)
        {
            u16 baseStatLimit;
            u32 i, badgecount, DualresistTypes = 0, storedTypes = 0, storedTypes2 = 0;
            u32 targetType = gBattleMons[gBattlerTarget].type1;
            u32 targetType2 = gBattleMons[gBattlerTarget].type2;
            u32 ValidTypes; //check for how many type storages have values, will be used to random which to use
            u32 FoundType = 0;

            badgecount = GetNumBadges();


            if (badgecount <= 1)
                baseStatLimit = 340;
            else if (badgecount <= 3)
                baseStatLimit = 457;
            else
                baseStatLimit = 0xffff; //effective infinity, i.e no limit
            
            

            for (i = 0; i < NUMBER_OF_MON_TYPES; i++) // Find all types that resist.
            {
                if (GetTypeModifier(targetType, i) <= UQ_4_12(0.5)
                && GetTypeModifier(targetType2, i) <= UQ_4_12(0.5))
                    DualresistTypes |= 1u << i;

                switch (GetTypeModifier(targetType, i))
                {
                case UQ_4_12(0):
                case UQ_4_12(0.5):
                    //ensure doesn't add a type that is weak to opponent other type
                    if (GetTypeModifier(targetType2, i) <= UQ_4_12(1.0))
                    storedTypes |= 1u << i; //if value match criteria add to field
                    break;
                }

                switch (GetTypeModifier(targetType2, i))
                {
                case UQ_4_12(0):
                case UQ_4_12(0.5):
                    //ensure doesn't add a type that is weak to opponent other type
                    if (GetTypeModifier(targetType, i) <= UQ_4_12(1.0))
                    storedTypes2 |= 1u << i; //if value match criteria add to field
                    break;
                }
            }

            if (DualresistTypes) //if has type that resists both
            {
                while (DualresistTypes != 0)
                {
                    i = Random() % NUMBER_OF_MON_TYPES; //pick random type
                    if (DualresistTypes & (1u << i)) //if that type is within member
                    {
                        //if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))//replace w macro for species check
                        {
                            //DualresistTypes &= ~(1u << i); // Type resists, but the user is already of this type.
                            DualresistTypes = i;
                            break; //end loop
                        }
                        /*else
                        {
                            SET_BATTLER_TYPE(gBattlerAttacker, i);
                            PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                            gBattlescriptCurrInstr = cmd->nextInstr;
                            return; //shouold end and avoid fail instr
                        }*/
                    }//think it loops random i, excluding battlers current type, until finds a type that matches
                    //the field
                }
            }

             if (storedTypes) //if has type that resists type 1
            {
                while (storedTypes != 0)
                {
                    i = Random() % NUMBER_OF_MON_TYPES; //pick random type
                    if (storedTypes & (1u << i)) //if that type is within member
                    {
                        //if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))//replace w macro for species check
                        {
                            //DualresistTypes &= ~(1u << i); // Type resists, but the user is already of this type.
                            storedTypes = i;
                            break; //end loop
                        }
                        /*else
                        {
                            SET_BATTLER_TYPE(gBattlerAttacker, i);
                            PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                            gBattlescriptCurrInstr = cmd->nextInstr;
                            return; //shouold end and avoid fail instr
                        }*/
                    }//think it loops random i, excluding battlers current type, until finds a type that matches
                    //the field
                }
            }

             if (storedTypes2) //if has type that resists type 2
            {
                while (storedTypes2 != 0)
                {
                    i = Random() % NUMBER_OF_MON_TYPES; //pick random type
                    if (storedTypes2 & (1u << i)) //if that type is within member
                    {
                        //if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))//replace w macro for species check
                        {
                            //DualresistTypes &= ~(1u << i); // Type resists, but the user is already of this type.
                            storedTypes2 = i;
                            break; //end loop
                        }
                        /*else
                        {
                            SET_BATTLER_TYPE(gBattlerAttacker, i);
                            PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                            gBattlescriptCurrInstr = cmd->nextInstr;
                            return; //shouold end and avoid fail instr
                        }*/
                    }//think it loops random i, excluding battlers current type, until finds a type that matches
                    //the field
                }
            }

            if (DualresistTypes || storedTypes || storedTypes2)
            {
                while (FoundType == 0)
                {
                    ValidTypes = Random() % 3; //value between 0 and 2

                    switch (ValidTypes)
                    {
                        case 0:
                            FoundType = DualresistTypes;
                            break;
                        case 1:
                            FoundType = storedTypes;
                            break;
                        case 2:
                            FoundType = storedTypes2;
                            break;

                    }
                }
            }

            if (FoundType)
            {
                while (found_species == 0xffff)
                {
                    i = Random() % BASE_SPECIES_COUNT;
                    if (IS_SPECIES_OF_TYPE(i, FoundType)
                    && gBaseStats[i].flags != FLAG_LEGENDARY_POKEMON
                    && gBaseStats[i].flags != F_ULTRA_BEAST)
                    {
                        //do 2nd check for if species passes bst limiter
                        if (GetBaseStatTotal(i) <= baseStatLimit)
                            found_species = i;
                            //break;//setting found species to i, should already break loop, but adding break just in case
                            //THIS THIS WAS THE PROBLEM!!! agaopgoaegrl
                            //was breaking out early FUCK
                    }
                }//need to set this to not use species that would be super effective weak to any of targe type
            }
            //found_species = mon search
            //annoying but think will need to add a bst filter based on badge
            //to balance think can get rid of the filter around 4th badge tho,
            //so not that bad
            //no badge to 1 badge limit to 340 bst,
            //>= 1 badge limit 340
            //>= 3 badges limit 450
            //think that's all I need?
            //to increase pool make random chance to use 
            //dual resist or type 1/type2 resist
            //simple code random % 3 w switch case,
            //set type search to stored value based on that,
            //i.e case 0 typesearch  = dual resist
            PREPARE_SPECIES_BUFFER(gBattleTextBuff1, found_species);
        }
        
        //do species search assign found species to value
        //PREPARE_SPECIES_BUFFER(gBattleTextBuff1, found_species)//for counter-form search species to use and assign to this value so it will be target species
        //idk why but imposter shows correct name, inversion just shows as adaptability,
        //but imposter doesn't work w the ability name cap, while the messed up version of inversion,
        //does show as capped, even if the wrong ability
        //fixed was problem w abilitybuffer, fixed now, but still unsure,
        //why it worked for one and not the other
           if (original_ability == ABILITY_IMPOSTER || original_ability == ABILITY_INVERSION)
            {
                gDisableStructs[gBattlerAttacker].transformedViaAbility = original_ability;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff2, original_ability); //for imposter & inversion
            }

            if (gCurrentMove == MOVE_TRANSFORM || original_ability == ABILITY_IMPOSTER)
            {
                battleMonAttacker = (u8*)(&gBattleMons[gBattlerAttacker]);
                battleMonTarget = (u8*)(&gBattleMons[gBattlerTarget]); //v changed should make only copy move data
                for (i = offsetof(struct BattlePokemon, moves[0]); i < offsetof(struct BattlePokemon, moves[4]); ++i) //ok THIS is what tells it to explicitly take values excluding hp. it loops and copies values from struct down to hp.
                    battleMonAttacker[i] = battleMonTarget[i]; //to get this to work would need change value from struct higher htan pp, and replace i = 0 with accurate byte value of starting value
            
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_OPPONENT)
                {
                    //base version takes battle ability not mon ability,
                    //which exactly tracks ability changes, 
                    //but its more useful as a reveal to just show its default ability
                    //hmm but there's more you can do in doubles w a ditto using the transform move,
                    //if it copies the current ability, in the case you swap off a bad ability
                    //ok will use battle, 9/10 its same result, but has opporutinty for more flexibility
                    //targetAbility = GetMonAbility(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]]);
                    TransformSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_SPECIES, NULL);

                }
                else
                {
                    //targetAbility = GetMonAbility(&gPlayerParty[gBattlerPartyIndexes[gBattlerTarget]]);
                    TransformSpecies = GetMonData(&gPlayerParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_SPECIES, NULL);
                }
                targetAbility = GetBattlerAbility(gBattlerTarget);

            }//NEEDED to separate as counter_form wouldn't be using battler data to find species/moves it would only be able to asign moves by levelup use trainerparty move selector function for that
                //works sets moves correctly
            else if (original_ability == ABILITY_INVERSION) //not using transform, ability is inversion
            {
                targetAbility = GetAbilityBySpecies(found_species, Random() % 4);
                TransformSpecies = found_species;
            }

        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT) //use this instead taken from mega logic
            mon = &gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]];  //mon being transformed
        else
            mon = &gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]];

       
        
        

        // Change stats //stats based on target species but not actually changing my species, visual is handled already in another file, makes stat reversion easier w another calcstat
        TransformRecalcBattlerStats(gBattlerAttacker, mon, targetAbility, TransformSpecies); //rather than using this to change species to populate sum screen with transferrd abilitynum,
        //just go to summary screen and change line to read the targets abilitynum if current move transform or ability imposter/inversion
        //need find way for one time change that resets on faint/switch/battle end, and that won't just keep changing every turn long as status2 is transformed/trace etc.

        //face palm, literally what I neeed, just need update 
        //like summary screen, but since is in battle stuff,
        //think can specifically filter for status transformed?
        UpdateHealthboxAttribute(gHealthboxSpriteIds[gBattlerAttacker], mon, HEALTHBOX_ALL); //should update hp values in healthox

        
        
        //put new hidden ability counter form move logic here
        if (original_ability == ABILITY_INVERSION) 
        {
            //test may need adjust  in case causes permanent move change, 
            //since appears to work on struct, not battle data?
            //new setup tested seems to work,
            //also reveals issue of inversion failing
            //seems to be due to effect confusion/overlap?
            //seems to be doing species none somehow?
            GiveBattleMonInitialMoveset_Fast(mon, TransformSpecies);  //already changed species of mon so this alone may be enough?
            gBattleStruct->overwrittenAbilities[gBattlerAttacker] = targetAbility; //GetAbilityBySpecies(found_species, Random() % 4); //think this should work?
        }//think this is populating the struct to keep track of abilities but not actually setting it?
        else
        {
            //do type 3 and ability slot set based on target
            gBattleMons[gBattlerAttacker].type3 = gBattleMons[gBattlerTarget].type3;
            //gBattleMons[gActiveBattler].abilty =  GetBattlerAbility(gBattlerTarget);
            gBattleStruct->overwrittenAbilities[gBattlerAttacker] = targetAbility; //GetBattlerAbility(gBattlerTarget);

        }

        for (i = 0; i < MAX_MON_MOVES; ++i) //logic for pp
        {
            gBattleMons[gBattlerAttacker].pp[i] = gBattleMoves[gBattleMons[gBattlerAttacker].moves[i]].pp;// 5; //pretty sure this is just to avoid issues as min pp is 5  vsonic
        } //else sets all pp to 5,  wants to set as max pp
        gActiveBattler = gBattlerAttacker;
        BtlController_EmitResetActionMoveSelection(0, RESET_MOVE_SELECTION);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
}

static void atk9C_setsubstitute(void)
{
    u32 hp = gBattleMons[gBattlerAttacker].maxHP / 4;

    if (gBattleMons[gBattlerAttacker].maxHP / 4 == 0)
        hp = 1;
    if (gBattleMons[gBattlerAttacker].hp <= hp)
    {
        gBattleMoveDamage = 0;
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
    }
    else
    {
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4; // one bit value will only work for pokemon which max hp can go to 1020(which is more than possible in games)
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMons[gBattlerAttacker].status2 |= STATUS2_SUBSTITUTE;
        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_WRAPPED);
        gDisableStructs[gBattlerAttacker].substituteHP = gBattleMoveDamage;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        gHitMarker |= HITMARKER_IGNORE_SUBSTITUTE;
    }
    ++gBattlescriptCurrInstr;
}

static bool8 IsMoveUncopyableByMimic(u16 move)
{
    s32 i;

    for (i = 0; sMovesForbiddenToCopy[i] != MIMIC_FORBIDDEN_END && sMovesForbiddenToCopy[i] != move; ++i);
    return (sMovesForbiddenToCopy[i] != MIMIC_FORBIDDEN_END);
}

static void atk9D_mimicattackcopy(void)
{
    gChosenMove = 0xFFFF;
    if (IsMoveUncopyableByMimic(gLastMoves[gBattlerTarget])
        || gBattleMons[gBattlerAttacker].status2 & STATUS2_TRANSFORMED
        || gLastMoves[gBattlerTarget] == 0
        || gLastMoves[gBattlerTarget] == 0xFFFF)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        s32 i;

        for (i = 0; i < MAX_MON_MOVES; ++i)
        {
            if (gBattleMons[gBattlerAttacker].moves[i] == gLastMoves[gBattlerTarget])
                break; //believe it means do nothing if current move is same as target move
        }
        if (i == MAX_MON_MOVES)
        {
            if (gCurrentMove == MOVE_SKETCH)
            { 
                gBattleMons[gBattlerAttacker].moves[gCurrMovePos] = gLastMoves[gBattlerTarget];
                if (gBattleMoves[gLastMoves[gBattlerTarget]].pp < 5)
                    gBattleMons[gBattlerAttacker].pp[gCurrMovePos] = gBattleMoves[gLastMoves[gBattlerTarget]].pp;
                else
                    gBattleMons[gBattlerAttacker].pp[gCurrMovePos] = gBattleMoves[gLastMoves[gBattlerTarget]].pp;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gLastMoves[gBattlerTarget])
                    gDisableStructs[gBattlerAttacker].mimickedMoves |= gBitTable[gCurrMovePos];
                gBattlescriptCurrInstr += 5;
            } //CHANGED should let you have max pp for move, or close to it..
            else
            {
                gBattleMons[gBattlerAttacker].moves[gCurrMovePos] = gLastMoves[gBattlerTarget];
                if (gBattleMoves[gLastMoves[gBattlerTarget]].pp < 5)
                    gBattleMons[gBattlerAttacker].pp[gCurrMovePos] = gBattleMoves[gLastMoves[gBattlerTarget]].pp;
                else
                    gBattleMons[gBattlerAttacker].pp[gCurrMovePos] = 5;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gLastMoves[gBattlerTarget])
                    gDisableStructs[gBattlerAttacker].mimickedMoves |= gBitTable[gCurrMovePos];
                gBattlescriptCurrInstr += 5;
            }
        }
        else
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
    }
}

//think can use this for pickup battle setup
//looks like it picks random value, than casts it to the move limit. and then adds conditionals to limit the value further
/*i.e looks for random value if value greater than move count random search again
* then if passes that filter, if move is on the banned moves list, stop and go back to step 1 search
* if it clears the banned move list go ahead and dothe effect i.e use the move
* 
* so rather than trying to make a list of moves with a loop, can just loop all possible values
* and just filter from there to what I want.
*/
static void atk9E_metronome(void) //speaknig of prob need change this, value for move expansion think (Random() % LAST_MOVE_INDEX) + 1
{

    do
    {
        gCurrentMove = (Random() % MOVES_COUNT);
    } while (sForbiddenMoves[gCurrentMove] & FORBIDDEN_METRONOME || gCurrentMove == MOVE_NONE); //keep checking long as move is forbidden
    
    if (!(sForbiddenMoves[gCurrentMove] & FORBIDDEN_METRONOME))
    {
        gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
        SetAtkCancellerForCalledMove();
        gBattlescriptCurrInstr = gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect];
        gBattlerTarget = GetMoveTarget(gCurrentMove, 0);
        return;
    }
    /*while (1)
    {
        s32 i;

        gCurrentMove = (Random() & 0x1FF) + 1;
        if (gCurrentMove >= MOVES_COUNT)
            continue;
        for (i = 0; i < MAX_MON_MOVES; ++i); // redundant
        i = -1;
        while (1)
        {
            ++i;
            if (sMovesForbiddenToCopy[i] == gCurrentMove)
                break;
            if (sMovesForbiddenToCopy[i] == METRONOME_FORBIDDEN_END)
                break;
            if (sForbiddenMoves[gCurrentMove] & FORBIDDEN_METRONOME)
                break;
        }
        if (sMovesForbiddenToCopy[i] == METRONOME_FORBIDDEN_END)
        {
            gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
            gBattlescriptCurrInstr = gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect];
            gBattlerTarget = GetMoveTarget(gCurrentMove, 0);
            return;
        }
    }*/
}

static u8 WeightBoostedDamageFormula(void)
{
    s32 i;
    u8 damage;

    for (i = 0; sWeightToDamageTable[i] != 0xFFFF; i += 2) //go to next row, if not 0xffff
    {
        if (sWeightToDamageTable[i] > GetBattlerWeight(gBattlerTarget)) //using this function over base species weight allows automize, float stone, heavy and light metal to have affect on dmg formula
            break;
    }
    if (sWeightToDamageTable[i] != 0xFFFF) //will always break before reach ffff, max dmg 120
        damage = sWeightToDamageTable[i + 1];

    return damage;
}

//used for seismic toss, adjust using move filter and GetBattlerWeight function
//actually plan to make new function just for weight scaling similar to flail
//atkAC_remaininghptopower function  check target level break if they are below a certain level
//that way it'd only do normal seismic damage for early game
//would overperform essentially oneshot heavy targets, may rework it into a nerf?
//can't work on mon two times users weight?
//then bring in the weight based boost,
//ran quick check double weight is far too low for how much weight varies think 4x instead is teh limit
//ex primape is 300,  machoke is 700,  while in oxic is 2400
static void atk9F_dmgtolevel(void) 
{
    u8 max_skill_lvl = 50;
    u8 level_Limiter = gBattleMons[gBattlerAttacker].level;
    u32 weightscaling = WeightBoostedDamageFormula();
    u8 lvl_scaling = 85;  //means % dmg is from lvl

    if (gCurrentMove == MOVE_SEISMIC_TOSS)
    {
        //need to remove this, was bad idea,
        //logically makes sense, but if I do dmg based on weight
        //doesn't really work
        //if (GetBattlerWeight(gBattlerTarget) > (GetBattlerWeight(gBattlerAttacker) * 4))
        //    gMoveResultFlags |= MOVE_RESULT_FAILED;

        //if (level_Limiter < max_skill_lvl)
        {
            gBattleMoveDamage = ((gBattleMons[gBattlerAttacker].level * lvl_scaling) / 100) + ((weightscaling / 4) * (level_Limiter / max_skill_lvl)); //max 145 or +45% lvl
        }
        //else
          //  gBattleMoveDamage = ((gBattleMons[gBattlerAttacker].level * lvl_scaling) / 100) + weightscaling;    //max dmg 205;
    }
    else
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].level;
    ++gBattlescriptCurrInstr;
}

static void atkA0_psywavedamageeffect(void) //talk with unfolding scales too high, misunderstood what actual hp ranges were for lvls, 1.75 one shots/2shots bringin gback to 1.5 ceiling remove from direct random value to damage.
{
    s32 randDamage;
    u8 scaler = 50;
    u8 lvl = gBattleMons[gBattlerAttacker].level;

    //experession/condition? value : value2  see if use for different values without having to use big if elses etc
    //found its ternary operator if value before ? is true value uses value before colon, else uses value after colon
    randDamage = (Random() % 6) + 2; //VALUe between 2-7 with scaler is 70% up to 120%

    randDamage *= 10;   //becomes a value between 0 & 100
    gBattleMoveDamage = lvl * (randDamage + scaler) / 100;  
    ++gBattlescriptCurrInstr;
    //lvl 50 max roll 60,  lvl 100 max roll 120, 
} //adjust sesimic toss, kinda op at high levels given super effectgive changes I made, especially since I already boosted it to do more damage for weight, think bring down to 85% lvl

static void atkA1_counterdamagecalculator(void)
{
    u8 sideAttacker = GetBattlerSide(gBattlerAttacker);
    u8 sideTarget = GetBattlerSide(gProtectStructs[gBattlerAttacker].physicalBattlerId);

    if (gProtectStructs[gBattlerAttacker].physicalDmg
     && sideAttacker != sideTarget
     && gBattleMons[gProtectStructs[gBattlerAttacker].physicalBattlerId].hp)
    {
        gBattleMoveDamage = gProtectStructs[gBattlerAttacker].physicalDmg * 2;

        if (gSideTimers[sideTarget].followmeTimer && gBattleMons[gSideTimers[sideTarget].followmeTarget].hp)
            gBattlerTarget = gSideTimers[sideTarget].followmeTarget;
        else
            gBattlerTarget = gProtectStructs[gBattlerAttacker].physicalBattlerId;

        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = 1;
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

// a copy of atkA1 with the physical -> special field changes
static void atkA2_mirrorcoatdamagecalculator(void)
{
    u8 sideAttacker = GetBattlerSide(gBattlerAttacker);
    u8 sideTarget = GetBattlerSide(gProtectStructs[gBattlerAttacker].specialBattlerId);

    if (gProtectStructs[gBattlerAttacker].specialDmg && sideAttacker != sideTarget && gBattleMons[gProtectStructs[gBattlerAttacker].specialBattlerId].hp)
    {
        gBattleMoveDamage = gProtectStructs[gBattlerAttacker].specialDmg * 2;
        if (gSideTimers[sideTarget].followmeTimer && gBattleMons[gSideTimers[sideTarget].followmeTarget].hp)
            gBattlerTarget = gSideTimers[sideTarget].followmeTarget;
        else
            gBattlerTarget = gProtectStructs[gBattlerAttacker].specialBattlerId;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = 1;
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkA3_disablelastusedattack(void)
{
    s32 i;

    for (i = 0; i < MAX_MON_MOVES; ++i)
    {
        if (gBattleMons[gBattlerTarget].moves[i] == gLastMoves[gBattlerTarget])
            break;
    }
    if (gDisableStructs[gBattlerTarget].disabledMove == MOVE_NONE
        && i != MAX_MON_MOVES && gBattleMons[gBattlerTarget].pp[i] != 0)
    {
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleMons[gBattlerTarget].moves[i])
        gDisableStructs[gBattlerTarget].disabledMove = gBattleMons[gBattlerTarget].moves[i];
        gDisableStructs[gBattlerTarget].disableTimer = (Random() % 4) + 2;  //replaced & 3
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkA4_trysetencore(void)
{
    s32 i;

    for (i = 0; i < MAX_MON_MOVES; ++i)
        if (gBattleMons[gBattlerTarget].moves[i] == gLastMoves[gBattlerTarget]) //select last used move
            break;
    if (gLastMoves[gBattlerTarget] == MOVE_STRUGGLE
     || gLastMoves[gBattlerTarget] == MOVE_ENCORE
     || gLastMoves[gBattlerTarget] == MOVE_TRANSFORM
     || gLastMoves[gBattlerTarget] == MOVE_MIMIC
     || gLastMoves[gBattlerTarget] == MOVE_SKETCH
     || gLastMoves[gBattlerTarget] == MOVE_SLEEP_TALK
     || gLastMoves[gBattlerTarget] == MOVE_MIRROR_MOVE)
        i = 4;
    if (gDisableStructs[gBattlerTarget].encoredMove == MOVE_NONE
     && i != 4
     && gBattleMons[gBattlerTarget].pp[i] != 0)
    {
        gDisableStructs[gBattlerTarget].encoredMove = gBattleMons[gBattlerTarget].moves[i];
        gDisableStructs[gBattlerTarget].encoredMovePos = i;
        gDisableStructs[gBattlerTarget].encoreTimer = (Random() & 3) + 3;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkA5_painsplitdmgcalc(void)
{
    if (!(gBattleMons[gBattlerTarget].status2 & STATUS2_SUBSTITUTE))
    {
        s32 hpDiff = (gBattleMons[gBattlerAttacker].hp + gBattleMons[gBattlerTarget].hp) / 2;
        s32 painSplitHp = gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - hpDiff;
        u8 *storeLoc = (void *)(&gBattleScripting.painSplitHp);

        storeLoc[0] = (painSplitHp);
        storeLoc[1] = (painSplitHp & 0x0000FF00) >> 8;
        storeLoc[2] = (painSplitHp & 0x00FF0000) >> 16;
        storeLoc[3] = (painSplitHp & 0xFF000000) >> 24;
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].hp - hpDiff;
        gSpecialStatuses[gBattlerTarget].dmg = 0xFFFF;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

//keep eye on this and compare to emerald version, for ditto new transform effect //vsonic important
//think would reference pickup logic for setting up what to loop over
//could roll a random number below mega data, and just decrement or increment (only increment if until value end species i.e would not go into megas)
//think what i'll do is roll random number, then random % 2 to either increment or decrement, (if /else if base on value)
//and go until find a mon that matches the rolled resisting type, or just do decrement if I go through species list that way,
//higher chance of encounting a full evolved form than a baby form, which is more valuable
static void atkA6_settypetorandomresistance(void) // conversion z  
{
    CMD_ARGS(const u8 *failInstr);

   /* if (gLastLandedMoves[gBattlerAttacker] == MOVE_NONE
     || gLastLandedMoves[gBattlerAttacker] == 0xFFFF)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else if (IsTwoTurnsMove(gLastLandedMoves[gBattlerAttacker])
          && gBattleMons[gLastHitBy[gBattlerAttacker]].status2 & STATUS2_MULTIPLETURNS)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {*/
        //change use storedType to loop so not auto using,
        //
        u32 i, DualresistTypes = 0, storedTypes = 0, storedTypes2 = 0;
        u32 hitByType = gLastHitByType[gBattlerAttacker];
        u32 targetType = gBattleMons[gBattlerTarget].type1;
        u32 targetType2 = gBattleMons[gBattlerTarget].type2;
        u32 typeFocus = Random() % 2; //decide which type to use for search

        //since sound is neutral, can reduce loop amount to just type sound
        //think can use this for Ditto new ability, to find type of mon to use 
        //then just find a mon that works
        for (i = 0; i < NUMBER_OF_MON_TYPES; i++) // Find all types that resist.
        {
            if (GetTypeModifier(targetType, i) <= UQ_4_12(0.5)
            && GetTypeModifier(targetType2, i) <= UQ_4_12(0.5))
                DualresistTypes |= 1u << i;

            switch (GetTypeModifier(targetType, i))
            {
            case UQ_4_12(0):
            case UQ_4_12(0.5):
                //ensure doesn't add a type that is weak to opponent other type
                if (GetTypeModifier(targetType2, i) <= UQ_4_12(1.0))
                storedTypes |= 1u << i; //if value match criteria add to field
                break;
            }

            switch (GetTypeModifier(targetType2, i))
            {
            case UQ_4_12(0):
            case UQ_4_12(0.5):
                //ensure doesn't add a type that is weak to opponent other type
                if (GetTypeModifier(targetType, i) <= UQ_4_12(1.0))
                storedTypes2 |= 1u << i; //if value match criteria add to field
                break;
            }
        }

        if (DualresistTypes) //if has type that resists both
        {
            while (DualresistTypes != 0)
            {
                i = Random() % NUMBER_OF_MON_TYPES;
                if (DualresistTypes & (1u << i))
                {
                    if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))
                    {
                        DualresistTypes &= ~(1u << i); // Type resists, but the user is already of this type.
                    }   //believe what this does is, remove stored type from value and continue loop
                    else
                    {
                        SET_BATTLER_TYPE(gBattlerAttacker, i);
                        PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                        gBattlescriptCurrInstr = cmd->nextInstr;
                        return; //shouold end and avoid fail instr
                    }
                }//think it loops random i, excluding battlers current type, until finds a type that matches
                //the field
            }
        }
        else //if no dual resist
        {

            if (storedTypes && storedTypes2) //if both type1 & type2 has a resist or immunity
            {

                if (typeFocus == 0) //if rolls to use target type 1 for resist
                {
                    while (storedTypes != 0)
                    {
                        i = Random() % NUMBER_OF_MON_TYPES;
                        if (storedTypes & (1u << i))
                        {
                            if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))
                            {
                                storedTypes &= ~(1u << i); // Type resists, but the user is already of this type.
                            }
                            else
                            {
                                SET_BATTLER_TYPE(gBattlerAttacker, i);
                                PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                                gBattlescriptCurrInstr = cmd->nextInstr;
                                return; //shouold end and avoid fail instr
                            }
                        }//think it loops random i, excluding battlers current type, until finds a type that matches
                        //the field
                    }
                }
                else if (typeFocus == 1) //if rolls to use target type 2 for resist
                {
                    while (storedTypes2 != 0)
                    {
                        i = Random() % NUMBER_OF_MON_TYPES;
                        if (storedTypes2 & (1u << i))
                        {
                            if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))
                            {
                                storedTypes2 &= ~(1u << i); // Type resists, but the user is already of this type.
                            }
                            else
                            {
                                SET_BATTLER_TYPE(gBattlerAttacker, i);
                                PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                                gBattlescriptCurrInstr = cmd->nextInstr;
                                return; //shouold end and avoid fail instr
                            }
                        }//think it loops random i, excluding battlers current type, until finds a type that matches
                        //the field
                    }
                }
            }
            else if (storedTypes || storedTypes2) //if either has a resist
            {
                //if stored 1 doens't have a resist, than pass the values from type 2
                //automatically defaults to type 1 if type2 is blank so no ne for logic there
                if (storedTypes == 0)
                    storedTypes = storedTypes2;

                while (storedTypes != 0)
                {
                    i = Random() % NUMBER_OF_MON_TYPES;
                    if (storedTypes & (1u << i))
                    {
                        if (IS_BATTLER_OF_TYPE(gBattlerAttacker, i))
                        {
                            storedTypes &= ~(1u << i); // Type resists, but the user is already of this type.
                        }
                        else
                        {
                            SET_BATTLER_TYPE(gBattlerAttacker, i);
                            PREPARE_TYPE_BUFFER(gBattleTextBuff1, i);
                            gBattlescriptCurrInstr = cmd->nextInstr;
                            return; //shouold end and avoid fail instr
                        }
                    }//think it loops random i, excluding battlers current type, until finds a type that matches
                    //the field
                }
            }
        }

        gBattlescriptCurrInstr = cmd->failInstr;
    //}
}

static void atkA7_setalwayshitflag(void)
{
    gStatuses3[gBattlerTarget] &= ~(STATUS3_ALWAYS_HITS);
    gStatuses3[gBattlerTarget] |= 0x10;
    gDisableStructs[gBattlerTarget].battlerWithSureHit = gBattlerAttacker;
    ++gBattlescriptCurrInstr;
}

static void atkA8_copymovepermanently(void) // sketch
{
    gChosenMove = 0xFFFF;
    if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_TRANSFORMED)
     && gLastPrintedMoves[gBattlerTarget] != MOVE_STRUGGLE
     && gLastPrintedMoves[gBattlerTarget] != 0
     && gLastPrintedMoves[gBattlerTarget] != 0xFFFF
     && gLastPrintedMoves[gBattlerTarget] != MOVE_SKETCH
     && gLastPrintedMoves[gBattlerTarget] != MOVE_MONOTYPE)
    {
        s32 i;

        for (i = 0; i < MAX_MON_MOVES; ++i)
            if (gBattleMons[gBattlerAttacker].moves[i] != MOVE_SKETCH && gBattleMons[gBattlerAttacker].moves[i] == gLastPrintedMoves[gBattlerTarget])
                break;
        if (i != MAX_MON_MOVES)
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        else // sketch worked
        {
            struct MovePpInfo movePpData;

            gBattleMons[gBattlerAttacker].moves[gCurrMovePos] = gLastPrintedMoves[gBattlerTarget];
            gBattleMons[gBattlerAttacker].pp[gCurrMovePos] = gBattleMoves[gLastPrintedMoves[gBattlerTarget]].pp;
            gActiveBattler = gBattlerAttacker;
            for (i = 0; i < MAX_MON_MOVES; ++i)
            {
                movePpData.moves[i] = gBattleMons[gBattlerAttacker].moves[i];
                movePpData.pp[i] = gBattleMons[gBattlerAttacker].pp[i];
            }
            movePpData.ppBonuses = gBattleMons[gBattlerAttacker].ppBonuses;
            BtlController_EmitSetMonData(0, REQUEST_MOVES_PP_BATTLE, 0, sizeof(struct MovePpInfo), &movePpData);
            MarkBattlerForControllerExec(gActiveBattler);
            PREPARE_MOVE_BUFFER(gBattleTextBuff1, gLastPrintedMoves[gBattlerTarget])
            gBattlescriptCurrInstr += 5;
        }
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static bool8 IsTwoTurnsMove(u16 move) //prob need to add on to this
{
    if (gBattleMoves[move].effect == EFFECT_SKULL_BASH
     || gBattleMoves[move].effect == EFFECT_RAZOR_WIND
     || gBattleMoves[move].effect == EFFECT_SKY_ATTACK
     || gBattleMoves[move].effect == EFFECT_SOLARBEAM
     || gBattleMoves[move].effect == EFFECT_SEMI_INVULNERABLE
     || gBattleMoves[move].effect == EFFECT_BIDE)
        return TRUE;
    else
        return FALSE;
}

static bool8 IsInvalidForSleepTalk(u16 move)
{
    if (move == MOVE_NONE || move == MOVE_SLEEP_TALK || move == MOVE_ASSIST
     || move == MOVE_MIRROR_MOVE || move == MOVE_METRONOME || MOVE_REST)
        return TRUE;
    else
        return FALSE;
}

static bool8 IsInvalidForAssist(u16 move)
{
    if (move == MOVE_NONE || move == MOVE_ASSIST
     || move == MOVE_MIRROR_MOVE || move == MOVE_METRONOME)
        return TRUE;
    else
        return FALSE;
}


static void atkA9_trychoosesleeptalkmove(void)
{
    s32 i;
    u8 unusableMovesBits = 0;

    for (i = 0; i < MAX_MON_MOVES; ++i)
    {
        if (IsInvalidForSleepTalk(gBattleMons[gBattlerAttacker].moves[i])
         //|| gBattleMons[gBattlerAttacker].moves[i] == MOVE_FOCUS_PUNCH
         || gBattleMons[gBattlerAttacker].moves[i] == MOVE_UPROAR
         || IsTwoTurnsMove(gBattleMons[gBattlerAttacker].moves[i]))
        {
            unusableMovesBits |= gBitTable[i];
        }
    }
    unusableMovesBits = CheckMoveLimitations(gBattlerAttacker, unusableMovesBits, ~(MOVE_LIMITATION_PP));
    if (unusableMovesBits == 0xF) // all 4 moves cannot be chosen
    {
        gBattlescriptCurrInstr += 5;
    }
    else // at least one move can be chosen
    {
        u32 movePosition;

        do
            movePosition = Random() & 3;
        while ((gBitTable[movePosition] & unusableMovesBits));
        gCalledMove = gBattleMons[gBattlerAttacker].moves[movePosition];
        gCurrMovePos = movePosition;
        gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
        gBattlerTarget = GetMoveTarget(gCalledMove, 0);
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkAA_setdestinybond(void)
{
    gBattleMons[gBattlerAttacker].status2 |= STATUS2_DESTINY_BOND;
    ++gBattlescriptCurrInstr;
}

static void TrySetDestinyBondToHappen(void)
{
    u8 sideAttacker = GetBattlerSide(gBattlerAttacker);
    u8 sideTarget = GetBattlerSide(gBattlerTarget);

    if (gBattleMons[gBattlerTarget].status2 & STATUS2_DESTINY_BOND
     && sideAttacker != sideTarget
     && !(gHitMarker & HITMARKER_GRUDGE))
        gHitMarker |= HITMARKER_DESTINYBOND;
}

static void atkAB_trysetdestinybondtohappen(void)
{
    TrySetDestinyBondToHappen();
    ++gBattlescriptCurrInstr;
}

static void atkAC_remaininghptopower(void) //changed from 48 to 64 since apparently gen 2-4 used 64 multiplier
{
    s32 i;  //changed back since a lower multiplier gets you more damage at 64 50% health scales to 32 at 48 50% health scales ot 24
    s32 hpFraction = GetScaledHPFraction(gBattleMons[gBattlerAttacker].hp, gBattleMons[gBattlerAttacker].maxHP, 36);

    for (i = 0; i < (s32)sizeof(sFlailHpScaleToPowerTable); i += 2)
    {
        if (hpFraction <= sFlailHpScaleToPowerTable[i])
            break;
    }
    gDynamicBasePower = sFlailHpScaleToPowerTable[i + 1];
    ++gBattlescriptCurrInstr;
}

static void atkAD_tryspiteppreduce(void) //vsonic need test, for odds and if effect needs tweaking
{
    if (gLastMoves[gBattlerTarget] != MOVE_NONE && gLastMoves[gBattlerTarget] != 0xFFFF)
    {
        s32 i;
        u16 luck = Random() % 10; //0-9 , 1-in-10 oddds, base 10 pp move, what odds do I want/need?
        s32 ppToDeduct; //i want the effect to be rare, but the effect itself to still be worthwhile, but not broken.

        for (i = 0; i < MAX_MON_MOVES; ++i)//move only has base 10 pp buff bad luck odds, to be more feasible.
            if (gLastMoves[gBattlerTarget] == gBattleMons[gBattlerTarget].moves[i]) //check after but think its 30% odds now, 0-9 if less than 4
                break;
        if (i != MAX_MON_MOVES && gBattleMons[gBattlerTarget].pp[i] != 0
            && (!TestSheerForceFlag(gBattlerAttacker, gCurrentMove)))       //test think should work? 
        {//if works would fail to do pp drop if eerie spell used on a sheer force mon, and instead jump to damage phase and boost damage.
            
            if (luck == 0) {
                ppToDeduct = 10;//gBattleMons[gBattlerTarget].pp[i];//want to make text for extranormal effects, 1st is mon "had bad luck", other is mon's "luck ran out!"
                PREPARE_STRING_BUFFER(gBattleTextBuff3, STRINGID_SPITE_TOTAL_LOSS);//too much
            }
            //these strings would run before the normal sprite text
            else if (luck > 3) { //if 4,5,6,7,8, or 9;  do normal effect  6 out of 10 60% odds  this shuold be perfect, still need test
                ppToDeduct = ((Random() % 2) + 4); //removes 4-5 pp   //new more consistent effect, min 4 drop, on move just used so base 5 pp moves get removed
                PREPARE_STRING_BUFFER(gBattleTextBuff3, STRINGID_EMPTYSTRING3);
            }
            else if (luck > 0) {  //might go down to + 3      (should be 3 & below not 0)  3 2 1
                ppToDeduct = 7;//10;    //bad luck clause, since uses else if, should automatically exclude values above 3  shoudl be 1-3
                PREPARE_STRING_BUFFER(gBattleTextBuff3, STRINGID_SPITE_BADLUCK);
            }//rebalanced odds 1-10 to 1-16
            

            if (gBattleMons[gBattlerTarget].pp[i] < ppToDeduct)
                ppToDeduct = gBattleMons[gBattlerTarget].pp[i];
            PREPARE_MOVE_BUFFER(gBattleTextBuff1, gLastMoves[gBattlerTarget])
                ConvertIntToDecimalStringN(gBattleTextBuff2, ppToDeduct, 0, 1);
            PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff2, 2, ppToDeduct)//update make new define that will be text "all"
                gBattleMons[gBattlerTarget].pp[i] -= ppToDeduct; //make a condition that if true will make gBattleTextBuff2, use that define for all rather than a number
            gActiveBattler = gBattlerTarget;
            if (!(gDisableStructs[gActiveBattler].mimickedMoves & gBitTable[i])
                && !(gBattleMons[gActiveBattler].status2 & STATUS2_TRANSFORMED))
            {
                BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + i, 0, 1, &gBattleMons[gActiveBattler].pp[i]);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            gBattlescriptCurrInstr += 5;
            if (gBattleMons[gBattlerTarget].pp[i] == 0)
                CancelMultiTurnMoves(gBattlerTarget);
        }
        else
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkAE_healpartystatus(void)
{
    u32 zero = 0;
    u8 toHeal = 0;

    if (gCurrentMove == MOVE_HEAL_BELL)
    {
        struct Pokemon *party;
        s32 i;

        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
            party = gPlayerParty;
        else
            party = gEnemyParty;
        if (GetBattlerAbility(gBattlerAttacker) != ABILITY_SOUNDPROOF)
        {
            gBattleMons[gBattlerAttacker].status1 = 0;
            gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_NIGHTMARE);
        }
        else
        {
            RecordAbilityBattle(gBattlerAttacker, gBattleMons[gBattlerAttacker].ability);
            gBattleCommunication[MULTISTRING_CHOOSER] |= 1;
        }
        gActiveBattler = gBattleScripting.battler = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_FLANK);
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
         && !(gAbsentBattlerFlags & gBitTable[gActiveBattler]))
        {
            if (GetBattlerAbility(gActiveBattler) != ABILITY_SOUNDPROOF)
            {
                gBattleMons[gActiveBattler].status1 = 0;
                gBattleMons[gActiveBattler].status2 &= ~(STATUS2_NIGHTMARE);
            }
            else
            {
                RecordAbilityBattle(gActiveBattler, gBattleMons[gActiveBattler].ability);
                gBattleCommunication[MULTISTRING_CHOOSER] |= 2;
            }
        }
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            u16 species = GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG);
            u8 abilityNum = GetMonData(&party[i], MON_DATA_ABILITY_NUM);

            if (species != SPECIES_NONE && species != SPECIES_EGG)
            {
                u16 ability;

                if (gBattlerPartyIndexes[gBattlerAttacker] == i)
                    ability = GetBattlerAbility(gBattlerAttacker);
                else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
                      && gBattlerPartyIndexes[gActiveBattler] == i
                      && !(gAbsentBattlerFlags & gBitTable[gActiveBattler]))
                    ability = GetBattlerAbility(gActiveBattler);
                else
                    ability = GetAbilityBySpecies(species, abilityNum);
                if (ability != ABILITY_SOUNDPROOF)
                    toHeal |= (1 << i);
            }
        }
    }
    else // Aromatherapy
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = 4;
        toHeal = 0x3F;
        gBattleMons[gBattlerAttacker].status1 = 0;
        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_NIGHTMARE);
        gActiveBattler = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_FLANK);
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
         && !(gAbsentBattlerFlags & gBitTable[gActiveBattler]))
        {
            gBattleMons[gActiveBattler].status1 = 0;
            gBattleMons[gActiveBattler].status2 &= ~(STATUS2_NIGHTMARE);
        }

    }
    if (toHeal)
    {
        gActiveBattler = gBattlerAttacker;
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, toHeal, 4, &zero);
        MarkBattlerForControllerExec(gActiveBattler);
    }
    ++gBattlescriptCurrInstr;
}

static void atkAF_cursetarget(void)
{
    if (gCurrentMove != MOVE_DRYADS_CURSE)
    {
        if (gBattleMons[gBattlerTarget].status2 & STATUS2_CURSED)
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        else
        {
            gBattleMons[gBattlerTarget].status2 |= STATUS2_CURSED;
            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 2;
            if (gBattleMoveDamage == 0)
                gBattleMoveDamage = 1;
            gBattlescriptCurrInstr += 5;
        }
    }
    else  //kinda backwards but would work if dryads curse will curse targeet without the attacker health cut
    {
        if (gBattleMons[gBattlerTarget].status2 & STATUS2_CURSED)
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        else
        {
            gBattleMons[gBattlerTarget].status2 |= STATUS2_CURSED;
            gBattlescriptCurrInstr += 5;
        }
    }
    
}

static void atkB0_trysetspikes(void)
{
    u8 targetSide = GetBattlerSide(gBattlerAttacker) ^ BIT_SIDE; //opposite attacker?

    if (gProtectStructs[gBattlerTarget].spikyShielded)  //doesn't need extra clause already has move end clause for touch protect like. 
        targetSide = GetBattlerSide(gBattlerTarget) ^ BIT_SIDE; //hope works and fixes spiky shield issue WORKS!!!
    //think the conditional was the problem


    if (gSideTimers[targetSide].spikesAmount == 3)
    {
        gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = 1;
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gSideStatuses[targetSide] |= SIDE_STATUS_SPIKES;
        ++gSideTimers[targetSide].spikesAmount;
        gBattlescriptCurrInstr += 5;
    }
}

static void atkB1_setforesight(void)
{
    gBattleMons[gBattlerTarget].status2 |= STATUS2_FORESIGHT;
    ++gBattlescriptCurrInstr;
}

static void atkB2_trysetperishsong(void)
{
    s32 i;
    s32 notAffectedCount = 0;
    u32 opposingSide = GetBattlerSide(BATTLE_OPPOSITE(gBattlerAttacker));

    for (i = 0; i < gBattlersCount; ++i)
    {
        if (gStatuses3[i] & STATUS3_PERISH_SONG
         || (gBattleMons[i].ability == ABILITY_SOUNDPROOF && i != gBattlerAttacker)
        )
        {
            ++notAffectedCount;
        }
        else
        {
            gStatuses3[i] |= STATUS3_PERISH_SONG;

            //want to setup so only opposite side has lower counter
            if (gSpecialStatuses[gBattlerAttacker].Cacophonyboosted
            && GetBattlerSide(i) == opposingSide)
                gDisableStructs[i].perishSongTimer = 2;
            else
                gDisableStructs[i].perishSongTimer = 3;
        }
    }
    PressurePPLoseOnUsingPerishSong(gBattlerAttacker);
    if (notAffectedCount == gBattlersCount)
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    else
        gBattlescriptCurrInstr += 5;
}

static void atkB4_jumpifconfusedandstatmaxed(void)
{
    if (gBattleMons[gBattlerTarget].status2 & STATUS2_CONFUSION
     && gBattleMons[gBattlerTarget].statStages[gBattlescriptCurrInstr[1]] == 12)
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 2);
    else
        gBattlescriptCurrInstr += 6;
}

static void atkB7_presentdamagecalculation(void) //setup logic to jump ptr if heal
{
    CMD_ARGS(const u8 *jumpInstr, const u8 *failInstr);
    //const u8 *jumpPtr = T1_READ_PTR(gBattlescriptCurrInstr + 1);  could add but don't need

    /* Don't reroll present effect/power for the second hit of Parental Bond.
     * Not sure if this is the correct behaviour, but bulbapedia states
     * that if present heals the foe, it doesn't strike twice, and if it deals
     * damage, the second strike will always deal damage too. This is a simple way
     * to replicate that effect.
     */
   // if (gSpecialStatuses[gBattlerAttacker].parentalBondState != PARENTAL_BOND_2ND_HIT) //parental bond logic would ensure dmg isn't varied so you get same power constant for 2nd hit
    if (gCurrentMove == MOVE_PRESENT) //potentially weighing name change to present rush, so its clear its diff, but kinda long
    {
        s32 rand = Random() & 0xFF; //think random value between 0 -256?
        /*if (rand < 102)
        {
            gDynamicBasePower = 60;
        }
        else if (rand < 178)
        {
            gDynamicBasePower = 80;
        }
        else */
        if (rand < 204) //do damage
        {
            gDynamicBasePower = 24; //plan move to hit 3-5 times at 5 hits would equal 120 dmg former max dmg setup in mutihitcounter2 - done, last is test, and check odds of heal vs dmg
        }
        else //heal
        {
            gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 12;
            if (gBattleMoveDamage == 0)
                gBattleMoveDamage = 1;
            gBattleMoveDamage *= -1;

            if (gBattleMons[gBattlerTarget].maxHP == gBattleMons[gBattlerTarget].hp)
            {
                gBattlescriptCurrInstr = cmd->failInstr; //think remove, just put string in script w hp check?
                return;
            }
            else
            {
                gMoveResultFlags &= ~(MOVE_RESULT_DOESNT_AFFECT_FOE); //removes doesnt affect so can heal anyone
                gBattlescriptCurrInstr = cmd->jumpInstr;
                return;
            }
                
        }
    
       /* if (rand < 204)
        {
            gBattlescriptCurrInstr = BattleScript_HitFromCritCalc;
        }
        else if (gBattleMons[gBattlerTarget].maxHP == gBattleMons[gBattlerTarget].hp)
        {
            gBattlescriptCurrInstr = BattleScript_ReturnAlreadyAtFullHp;
        }
        else
        {
            gMoveResultFlags &= ~(MOVE_RESULT_DOESNT_AFFECT_FOE);
            gBattlescriptCurrInstr = BattleScript_PresentHealTarget;
        } */
    }
    gBattlescriptCurrInstr = cmd->nextInstr; //this is issue its a pointer it has to go passed the pointer
}

static void atkB8_setsafeguard(void)
{
    if (gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_SAFEGUARD)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    else
    {
        gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] |= SIDE_STATUS_SAFEGUARD;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].safeguardTimer = 5;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].safeguardBattlerId = gBattlerAttacker;
        gBattleCommunication[MULTISTRING_CHOOSER] = 5;
    }
    ++gBattlescriptCurrInstr;
}

static void atkB3_rolloutdamagecalculation(void)
{

    s32 i;

    if (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)) // first hit
    {
        gDisableStructs[gBattlerAttacker].rolloutTimer = 5;
        gDisableStructs[gBattlerAttacker].rolloutTimerStartValue = 5;
        gBattleMons[gBattlerAttacker].status2 |= STATUS2_MULTIPLETURNS;
        gLockedMoves[gBattlerAttacker] = gCurrentMove;
    }
    if (--gDisableStructs[gBattlerAttacker].rolloutTimer == 0) // last hit
        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_MULTIPLETURNS);
    gDynamicBasePower = gBattleMoves[gCurrentMove].power;
    for (i = 1; i < (5 - gDisableStructs[gBattlerAttacker].rolloutTimer); ++i)
        gDynamicBasePower *= 2;
    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_DEFENSE_CURL)
        gDynamicBasePower *= 2;
    ++gBattlescriptCurrInstr;

}

static void atkB5_furycuttercalc(void)
{
    u32 i;

    if (gCurrentMove == MOVE_FURY_CUTTER) //changing script to just use the multi-hit bs, need to add this to its loop though,
        //so to ensure it doesn't trigger for other moves, made the entire thing contingent on move fury cutter, 
        //will need to find & test other multi hit (try spearow fury attack,) to ensure I didn't break it.
    {
        
        gDynamicBasePower = gBattleMoves[gCurrentMove].power; //it's working now.


        for (i = 0; i < (gMultiTask - gMultiHitCounter); ++i) //...changed this and damage multiplier actually works -_-
        {                 
            //if (gMultiHitCounter == (gMultiTask - 1)) //should only trigger on 4th hit if you roll the 4th hit
              //  gDynamicBasePower *= 2;  //change do nothing, so it stops boosting dmg after 3 hits //still equates to a base 110 move
            //else
                gDynamicBasePower += 10;  //rebalance, raise base power to 15, change to additive boost, higher scale on early hits slightly lower on end
                                            //new rebalance
                //new note what this does is loop dmg multiplier to ensure dmg is boosted based on how high couter is
            // berserker *= 3;  //change from 3 to 1, for large test, should reduce accuracy by 4 each hit if its working
                //berserker /= 4; 
        }//dizzyegg confirms doing this way also works for establishing 3/4
        //++gBattlescriptCurrInstr; // if done right power should double and accuracy should drop off by a fourth each hti

    }
    ++gBattlescriptCurrInstr;// had to move to accuracy function battlescript was below the accuracy check if done here
} //don't know if i'm just unlucky but it seeems to be hitting every time, so I'm still unsure
//if the accuracy reduction on hit is working  ok did test, accuracy reduction or accuracy checks just aren't working at all.

void BS_rageboostcalc(void)
{
    NATIVE_ARGS();
    u8 rageCounter = gDisableStructs[gBattlerAttacker].rageCounter;

    if (gCurrentMove == MOVE_RAGE)
    {

        if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
        {
            gDisableStructs[gBattlerAttacker].rageCounter = 0;
            gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_RAGE);
            gBattlescriptCurrInstr = BattleScript_MoveMissedPause; //create custom message rage abated 
        }
        else
        {
            gDynamicBasePower = (gBattleMoves[gCurrentMove].power + (10 * rageCounter)); //douesn't boost power till take hit or use move again

            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atkB6_happinesstodamagecalculation(void)
{
    if (gBattleMoves[gCurrentMove].effect == EFFECT_RETURN)
        gDynamicBasePower = 10 * (gBattleMons[gBattlerAttacker].friendship) / 25;
    else // EFFECT_FRUSTRATION
        gDynamicBasePower = 10 * (255 - gBattleMons[gBattlerAttacker].friendship) / 25;
    ++gBattlescriptCurrInstr;
}

static void atkB9_magnitudedamagecalculation(void)
{
    s32 magnitude = Random() % 100;

    if (magnitude < 5)
    {
        gDynamicBasePower = 10;
        magnitude = 4;
    }
    else if (magnitude < 15)
    {
        gDynamicBasePower = 30;
        magnitude = 5;
    }
    else if (magnitude < 35)
    {
        gDynamicBasePower = 50;
        magnitude = 6;
    }
    else if (magnitude < 65)
    {
        gDynamicBasePower = 70;
        magnitude = 7;
    }
    else if (magnitude < 85)
    {
        gDynamicBasePower = 90;
        magnitude = 8;
    }
    else if (magnitude < 95)
    {
        gDynamicBasePower = 110;
        magnitude = 9;
    }
    else
    {
        gDynamicBasePower = 150;
        magnitude = 10;
    }
    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 2, magnitude)
    for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; ++gBattlerTarget)
        if (gBattlerTarget != gBattlerAttacker && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget])) // a valid target was found
            break;
    ++gBattlescriptCurrInstr;
}

//consolidate moves with varied power that dont require a jump here
//will be return frustration magnitude, and snowball, since decide want to keep type on that
//could also be rage & fury cutter it seems
void BS_VariablePowerCalc(void) 
{
    NATIVE_ARGS();
    s32 magnitude = Random() % 100;
    s32 snowball = Random() % 30;
    u8 rageCounter = gDisableStructs[gBattlerAttacker].rageCounter;
    u32 i;

    switch (gBattleMoves[gCurrentMove].effect)
    {
        case EFFECT_MAGNITUDE:
        {
            if (magnitude < 5)
            {
                gDynamicBasePower = 10;
                magnitude = 4;
            }
            else if (magnitude < 15)
            {
                gDynamicBasePower = 30;
                magnitude = 5;
            }
            else if (magnitude < 35)
            {
                gDynamicBasePower = 50;
                magnitude = 6;
            }
            else if (magnitude < 65)
            {
                gDynamicBasePower = 70;
                magnitude = 7;
            }
            else if (magnitude < 85)
            {
                gDynamicBasePower = 90;
                magnitude = 8;
            }
            else if (magnitude < 95)
            {
                gDynamicBasePower = 110;
                magnitude = 9;
            }
            else
            {
                gDynamicBasePower = 150;
                magnitude = 10;
            }
            PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 2, magnitude)
            for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; ++gBattlerTarget)
            {
                if (gBattlerTarget != gBattlerAttacker && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget])) // a valid target was found
                    break;
            }
            //gBattlescriptCurrInstr = cmd->nextInstr;
        
        }
        break;
        case EFFECT_RAGE:
        if (gCurrentMove == MOVE_RAGE)
        {

            if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            {
                gDisableStructs[gBattlerAttacker].rageCounter = 0;
                gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_RAGE);
                gBattlescriptCurrInstr = BattleScript_MoveMissedPause; //create custom message rage abated 
            }
            else
            {
                gDynamicBasePower = (gBattleMoves[gCurrentMove].power + (10 * rageCounter)); //douesn't boost power till take hit or use move again

                //gBattlescriptCurrInstr = cmd->nextInstr;
            }
        }
        break;
        case EFFECT_RETURN:
        gDynamicBasePower = 10 * (gBattleMons[gBattlerAttacker].friendship) / 25; //new friendship change makes return initially weaker and scale up slower
        break;
        case EFFECT_FRUSTRATION:
        gDynamicBasePower = 10 * (255 - gBattleMons[gBattlerAttacker].friendship) / 25; //ironically it makes frustration actually viable in game,
        break;
        case EFFECT_FURY_CUTTER:
        if (gCurrentMove == MOVE_FURY_CUTTER) //changing script to just use the multi-hit bs, need to add this to its loop though,
        //so to ensure it doesn't trigger for other moves, made the entire thing contingent on move fury cutter, 
        //will need to find & test other multi hit (try spearow fury attack,) to ensure I didn't break it.
        {
            
            gDynamicBasePower = gBattleMoves[gCurrentMove].power; //it's working now.


            for (i = 0; i < (gMultiTask - gMultiHitCounter); ++i) //...changed this and damage multiplier actually works -_-
            {                 
                gDynamicBasePower += 10;  //rebalance, raise base power to 15, change to additive boost, higher scale on early hits slightly lower on end
                                                //new rebalance
                    //new note what this does is loop dmg multiplier to ensure dmg is boosted based on how high couter is
                // berserker *= 3;  //change from 3 to 1, for large test, should reduce accuracy by 4 each hit if its working
                    //berserker /= 4; 
            }//dizzyegg confirms doing this way also works for establishing 3/4
            //++gBattlescriptCurrInstr; // if done right power should double and accuracy should drop off by a fourth each hti

            // had to move to accuracy function battlescript was below the accuracy check if done here

        }
        break;
        case EFFECT_SNOWBALL:
        {
            if (snowball < 8) //pwr 45  65  80
                gDynamicBasePower = 45;
            else if (snowball < 21)
                gDynamicBasePower = 65;
            else
                gDynamicBasePower = 80;
        }   
        break;
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

//think eventually make loop array to check
//for now just do quick or conditional
//vsonic used to replace logic of move_pursuit in functions for effect
//so can now take diff moves
//believe callable moves should be excluded from this
//as the effect 
//nvm callable moves that don't rely on someone else using a move first
//should work as its a move effect regardless of how weirdly its coded
//intent of idea, when you use the move it can hit peopple switching out
//double nevermind way calledmove works it doesn't decide what move its calling
//until the move gets used, think of like this
//battler A selects Pursuit, they already know what they want to do and are prepared
//battler B doesn't know, and instead decides to reach in a bag to decide their move, then act after
//that way it doesn't make sense
//So the only thing to worry about is hit escape ability escape, and maybe teleport,
//but teleport could work like baton pass, in which case its excluded
u8 CanMoveHitSwitchingTarget(u16 move)
{
    if (move == MOVE_PURSUIT
    || move == MOVE_SPIRIT_SHACKLE)
        return TRUE;

    return FALSE;
}

u8 IsExemptFromPursuit(u32 battler)
{
    u16 move, ability;
    move = gLastPrintedMoves[battler];
    ability = GetBattlerAbility(battler);

    if (move == MOVE_TELEPORT
    || move == MOVE_BATON_PASS)
        return TRUE;

    else if (ability == ABILITY_RUN_AWAY
    || ability == ABILITY_AVIATOR)
        return TRUE;

    return FALSE;
}


static bool32 TrySetTargetToNextPursuiter(u32 battlerDef)
{
    u32 i;
    for (i = gCurrentTurnActionNumber + 1; i < gBattlersCount; i++)
    {
        u32 battler = gBattlerByTurnOrder[i];
        if (gChosenActionByBattler[battler] == B_ACTION_USE_MOVE
        && CanMoveHitSwitchingTarget(gChosenMoveByBattler[battler])
        && IsBattlerAlive(battlerDef)
        && IsBattlerAlive(battler)
        && GetBattlerSide(battler) != GetBattlerSide(battlerDef)
        && !(gBattleMons[battler].status1 & STATUS1_SLEEP)
        && (gDisableStructs[battler].FrozenTurns == 0)    //new freeze check    /means not frozen
        && !gDisableStructs[battler].truantCounter
        && !IsExemptFromPursuit(battlerDef)
        /*&& (B_PURSUIT_TARGET >= GEN_4 || *(gBattleStruct->moveTarget + battler) == battlerDef)
        && !IsGimmickSelected(battler, GIMMICK_Z_MOVE)
        && !IsGimmickSelected(battler, GIMMICK_DYNAMAX)
        && GetActiveGimmick(battler) != GIMMICK_DYNAMAX*/
        )
        {
            gBattlerTarget = battler;
            return TRUE;
        }

    }
    return FALSE;
}
//looks weird but pretty sure done this way,
//because swaps attacker and target via command after this
//no its because attacker is the one switching out
//it switches target w attacker after so they can attack w the move
//use glastusedmove to exclude things that pursuit shouldn't hit
//ex find target, if last used move (can use that because should only work if slower anyway)
//is teleport or baton pass, than set pursuit to false
//actually use gLastPrintedMoves[gBattlerAttacker]
//as that allows me to take battlerId argument
static void atkBA_jumpifnopursuitswitchdmg(void)
{

    /*Pursuit will now hit any adjacent opponent that attempts to switch out
    (but not more than one per turn), regardless of who it originally targeted. 
    
    With this in mind belive what I need to setup is a battle loop
    based on turn order...
    Luckily this function seems to have that gBattlerByTurnOrder[]
    If I loop that and use battlerbyturnorder for the battler 
    of gchosemovebybattler I THINK it would be correct/accurate
    would just need a check for it not being on the same side as attacker
    */

   u32 savedTarget = gBattlerTarget;

   /*for (i = gCurrentTurnActionNumber + 1; i < gBattlersCount; ++i)
   {
        if (GetBattlerSide(gBattlerByTurnOrder[i]) != GetBattlerSide(gBattlerAttacker))
        {
            if (CanMoveHitSwitchingTarget(gChosenMoveByBattler[gBattlerByTurnOrder[i]]))
            {
                canPursuit = TRUE;
                gBattlerTarget = gBattlerByTurnOrder[i];
                //gActionsByTurnOrder[i] = B_ACTION_TRY_FINISH;
                break;
            }
        }
   }*/
   //if this works remove other use of canmovehitswitchtarget
   //works!!
   //but weird type bug also is still there
   //type bug and potentially dmg bug is only there
   //when I use manual switch, if I trigger pursuit from hit escape type is fine

    //tested got pursuited when I was slower...
    //puruit hit me, then I used u_turn
    //after I selected my switch target boosted pursuit hit me again...
    //hopefully.wait this would only stop it if I'm the last battler to move
    //idk what anymore, woah surprinsngly this actually worked
    //...it doesn't work?
   //if (gCurrentTurnActionNumber >= gBattlerTarget)
   // canPursuit = FALSE;

    

    if (TrySetTargetToNextPursuiter(gBattlerAttacker))
    {
        //This pair may not be strickly necessary
        //gCurrentMove = gChosenMoveByBattler[gBattlerTarget];
        //gCurrMovePos = gChosenMovePos = *(gBattleStruct->chosenMovePositions + gBattlerTarget);
        ChangeOrderTargetAfterAttacker();
        gBattleStruct->pursuitTarget = 1u << gBattlerAttacker;
        gBattleStruct->pursuitSwitchByMove = gActionsByTurnOrder[gCurrentTurnActionNumber] == B_ACTION_USE_MOVE;
        gBattleStruct->pursuitStoredSwitch = gBattleStruct->monToSwitchIntoId[gBattlerAttacker];
        *(gBattleStruct->moveTarget + gBattlerTarget) = gBattlerAttacker;
        gBattlerTarget = savedTarget;
        gBattlescriptCurrInstr += 5;

    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }//something weird here when it does the switch out dmg, type calc is wrong?
}

static void atkBB_setsunny(void)
{
    CMD_ARGS();

    if (!TryChangeBattleWeather(gBattlerAttacker, ENUM_WEATHER_SUN, FALSE))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_WEATHER_FAILED;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STARTED_SUNLIGHT;
    }

    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atk7D_setrain(void)
{
    CMD_ARGS();

    if (!TryChangeBattleWeather(gBattlerAttacker, ENUM_WEATHER_RAIN, FALSE))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_WEATHER_FAILED;   //this values align with gMoveWeatherChangeStringIds
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STARTED_RAIN;
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atkC8_sethail(void)
{
    CMD_ARGS();

    if (!TryChangeBattleWeather(gBattlerAttacker, ENUM_WEATHER_HAIL, FALSE))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_WEATHER_FAILED;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STARTED_HAIL;
    }

    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atk95_setsandstorm(void)
{
    CMD_ARGS();

    if (!TryChangeBattleWeather(gBattlerAttacker, ENUM_WEATHER_SANDSTORM, FALSE))
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_WEATHER_FAILED;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STARTED_SANDSTORM;
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atkBC_maxattackhalvehp(void) // belly drum
{

    if (gBattleMons[gBattlerAttacker].statStages[STAT_ATK] < 12
     && gBattleMons[gBattlerAttacker].hp > (gBattleMons[gBattlerAttacker].maxHP / 2))
    {
        gBattleMons[gBattlerAttacker].statStages[STAT_ATK] = 12;
        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 2;
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkBD_copyfoestats(void) // psych up
{
    s32 i;

    for (i = 0; i < NUM_BATTLE_STATS; ++i)
        gBattleMons[gBattlerAttacker].statStages[i] = gBattleMons[gBattlerTarget].statStages[i];
    gBattlescriptCurrInstr += 5; // Has an unused jump ptr(possibly for a failed attempt) parameter.
}

static void atkBE_rapidspinfree(void) //need fix this clear isn't right
{
    CMD_ARGS();
    u8 atkSide = GetBattlerSide(gBattlerAttacker);
    /*if (gBattleMons[gBattlerAttacker].status2 & STATUS2_WRAPPED)
    {
        gBattleScripting.battler = gBattlerTarget;
        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_WRAPPED);
        gBattlerTarget = *(gBattleStruct->wrappedBy + gBattlerAttacker);
        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
        gBattleTextBuff1[1] = B_BUFF_MOVE;
        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gBattlerAttacker * 2 + 0);
        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gBattlerAttacker * 2 + 1);
        gBattleTextBuff1[4] = B_BUFF_EOS;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_WrapFree;
    }*/
    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_WRAPPED
    || gBattleMons[gBattlerAttacker].status4 & ITS_A_TRAP_STATUS4) //potentiall change to all ifs, to just clear everything vsonic add more status
    {
        gBattleScripting.battler = gBattlerTarget;
        gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_WRAPPED;
        gBattleMons[gBattlerAttacker].status4 &= ~ITS_A_TRAP_STATUS4; //hopefully works
        gBattlerTarget = *(gBattleStruct->wrappedBy + gBattlerAttacker);
        //PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gBattlerAttacker]); //chaned to freed from all traps and hazards!
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_RapidSpinTrapHazardClear; //chaned to freed from all traps and hazards! - done
    }
    else if (gStatuses3[gBattlerAttacker] & STATUS3_LEECHSEED)
    {
        gStatuses3[gBattlerAttacker] &= ~STATUS3_LEECHSEED;
        gStatuses3[gBattlerAttacker] &= ~STATUS3_LEECHSEED_BATTLER;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_LeechSeedFree;
    }
    else if (gSideStatuses[atkSide] & SIDE_STATUS_SPIKES) //change spike to not be mutually exclusive, but use same counters
    {
        gSideStatuses[atkSide] &= ~(SIDE_STATUS_SPIKES); //to balance, you can use multiple diffeent spike types but can't stack max of each
        gSideTimers[atkSide].spikesAmount = 0; //i.e if stealth rocks and toxic spikes are on field you can only get a single stack of spikes
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_SpikesFree;
    }
    else if (gSideStatuses[atkSide] & SIDE_STATUS_TOXIC_SPIKES)
    {
        gSideStatuses[atkSide] &= ~SIDE_STATUS_TOXIC_SPIKES;
        gSideTimers[atkSide].toxicSpikesAmount = 0;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_ToxicSpikesFree;
    }
    else if (gSideStatuses[atkSide] & SIDE_STATUS_STICKY_WEB)
    {
        gSideStatuses[atkSide] &= ~SIDE_STATUS_STICKY_WEB;
        gSideTimers[atkSide].stickyWebAmount = 0;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_StickyWebFree;
    }
    else if (gSideStatuses[atkSide] & SIDE_STATUS_STEALTH_ROCK)
    {
        gSideStatuses[atkSide] &= ~SIDE_STATUS_STEALTH_ROCK;
        gSideTimers[atkSide].stealthRockAmount = 0;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_StealthRockFree;
    }
    /*else if (gSideStatuses[atkSide] & SIDE_STATUS_STEELSURGE)
    {
        gSideStatuses[atkSide] &= ~SIDE_STATUS_STEELSURGE;
        gSideTimers[atkSide].steelsurgeAmount = 0;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_SteelsurgeFree;
    }*/
    else
    {
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}


static void atkBF_setdefensecurlbit(void)
{
    gBattleMons[gBattlerAttacker].status2 |= STATUS2_DEFENSE_CURL;
    ++gBattlescriptCurrInstr;
}

static void atkC0_recoverbasedonsunlight(void) //since requires setting sun, will keep the boost at its current levels
{
    gBattlerTarget = gBattlerAttacker;
    if (gBattleMons[gBattlerAttacker].hp != gBattleMons[gBattlerAttacker].maxHP)
    {
        if (gCurrentMove == MOVE_SHORE_UP)
        {
            if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SANDSTORM_ANY))
                //gBattleMoveDamage = 20 * GetNonDynamaxMaxHP(gBattlerAttacker) / 30;
                gBattleMoveDamage = 20 * gBattleMons[gBattlerAttacker].maxHP / 30;
            else
                //gBattleMoveDamage = GetNonDynamaxMaxHP(gBattlerAttacker) / 3;
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 3;
        }
        else if (gBattleWeather == 0 || !IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_ANY)) //pretty sure need replace weatherhaseffect w function that has umbrella logic in it
            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 3;
        else if (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SUN_ANY))
            gBattleMoveDamage = 20 * gBattleMons[gBattlerAttacker].maxHP / 30;
        else if (GetBattlerAbility(gBattlerAttacker) == ABILITY_FLUORESCENCE && IsBlackFogNotOnField()) //eitehr give boosted heal, or make it heal the normal amount regardless of weather change
            gBattleMoveDamage = 20 * gBattleMons[gBattlerAttacker].maxHP / 30; //it has low bst overall so just keep full boost here, cut solar beam boost
        else // not sunny weather
            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;

        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;

        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

s16 atk_diff(void) {
    s16 diff = (gBattleMons[gBattlerTarget].attack - gBattleMons[gBattlerAttacker].attack);
    if (diff <= 0)
    {
        diff = 0;
    }
    return diff;
}

s16 spatk_diff(void) {
    s16 diff = (gBattleMons[gBattlerTarget].spAttack - gBattleMons[gBattlerAttacker].spAttack);
    if (diff <= 0) {
        diff = 0;
    }
    return diff;
}

#define HIDDENPOWER_CALC
static void atkC1_hiddenpowercalc(void) //no longer need
{
    CMD_ARGS();

    s32 powerBits;
    s16 i, j;
    u8 moveSplit = gBattleMoves[gCurrentMove].split;
    if (gCurrentMove == MOVE_HIDDEN_POWER)
    {
        powerBits = ((gBattleMons[gBattlerAttacker].hpIV & 2) >> 1)
            | ((gBattleMons[gBattlerAttacker].attackIV & 2) << 0)
            | ((gBattleMons[gBattlerAttacker].defenseIV & 2) << 1)
            | ((gBattleMons[gBattlerAttacker].speedIV & 2) << 2)
            | ((gBattleMons[gBattlerAttacker].spAttackIV & 2) << 3)
            | ((gBattleMons[gBattlerAttacker].spDefenseIV & 2) << 4);
        
        gDynamicBasePower = (35 * powerBits) / 63 + 45;
    }
    //looked on bulbapedia understand the calc now, ivs will return a value of 0 or 1, if all 1 it sums to 63 cancles out divisor leaving just the 40.
    //to be added on to the 30 if its 0 everything inside cancels leaving just the 30, which is why hidden power
    //scales between 30 and 70.
    //so to change the floor value I just need to raise the outside value, to adjust the max I change teh 40.
    //whatever value I make it, when added to the outside value will bethe max
    //normal move is now base power 60, I'll make it 50 and have it scale up to 80
    //made base power 45, scales up to 80 /keeping in mind my boost
    //// Subtract 3 instead of 1 below because 2 types are excluded (TYPE_NORMAL and TYPE_MYSTERY)
   /* gBattleStruct->dynamicMoveType = ((NUMBER_OF_MON_TYPES - 3) * typeBits) / 63 + 1; //think changing from 15 to 16 adds one more type to options so now have fairy
    if (gBattleStruct->dynamicMoveType == TYPE_MYSTERY)
        gBattleStruct->dynamicMoveType = TYPE_FAIRY; // or may need to increase it by 6 to get over other types to 21 since the +1 and ++ adds 2 tellign the last type added
    gBattleStruct->dynamicMoveType |= F_DYNAMIC_TYPE_1 | F_DYNAMIC_TYPE_2;
   // gBattleStruct->dynamicMoveType |= 0xC0; // i.e 15 +2= 17 which is type dark 0x11 == 17
    */

    // don't know if this workks still need to add 1.7 boost if lower than opponenent stat
        //make sure I use the right stat field so it calculates dynamically not just use base stat by take into account stat changing moves too.
        // stat atk seems to be your stat stage for that specifc stat
      //  u16 move = MOVE_HIDDEN_POWER;

      //moved split logic to calculatebasedamage in pokemon.c

    


    
    gBattlescriptCurrInstr = cmd->nextInstr; //moved downhere to hopefully make sure it doesn't jump scripts until everything done

    //compare abililty_download that is most similar as it does a boost based on opponenet stat comparison
    // gCurrentMove = gChosenMove = MOVE_HIDDEN_POWER;
        //realized will need function call to set i & j value. so will make two functions and comme back.
}

static void atkC2_selectfirstvalidtarget(void)
{
    for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; ++gBattlerTarget)
        if (gBattlerTarget != gBattlerAttacker && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget]))
            break;
    ++gBattlescriptCurrInstr;
}

//want to set 2, so make new counter and make it default to that if other != 0
//this is used for future sight and doom desire I want this specifically for future sight only
static void atkC3_trysetfutureattack(void) 
{
    if (gCurrentMove == MOVE_FUTURE_SIGHT)
    {
        if ((gWishFutureKnock.futureSightCounter[gBattlerTarget]) && (gWishFutureKnock.futureSightCounter2[gBattlerTarget])) //prevents spamming each turn
        {   //when set upgrade, change to if both counters do not equal 0
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1); //its not showing the failed message and I don't know why
            //ok think its because it plays after moves are done ni move result, and would be on turn, where it would play on move end
            //so the move landing overwrites the move failed script I think, annoying but not a major issue
            //also since this doesn't do super or seem to get stab, its not super op,
            //despite being 120bp .
        }
        else if ((gWishFutureKnock.futureSightCounter[gBattlerTarget] == 0) || (gWishFutureKnock.futureSightCounter2[gBattlerTarget] == 0))
        {
            gWishFutureKnock.futureSightMove[gBattlerTarget] = gCurrentMove;
            gWishFutureKnock.futureSightAttacker[gBattlerTarget] = gBattlerAttacker;
            if (!(gWishFutureKnock.futureSightCounter[gBattlerTarget])) //if counter 0 set counter
            gWishFutureKnock.futureSightCounter[gBattlerTarget] = 3;
            else if ((gWishFutureKnock.futureSightCounter[gBattlerTarget]) && (!gWishFutureKnock.futureSightCounter2[gBattlerTarget]))
            gWishFutureKnock.futureSightCounter2[gBattlerTarget] = 3;//should be if counter 1 used, but counter 2 empty set counter 2

            gWishFutureKnock.futureSightDmg[gBattlerTarget] = CalculateBaseDamage(&gBattleMons[gBattlerAttacker],
                                                                                &gBattleMons[gBattlerTarget],
                                                                                gCurrentMove,
                                                                                gSideStatuses[GetBattlerSide(gBattlerTarget)],
                                                                                0,
                                                                                0,
                                                                                gBattlerAttacker,
                                                                                gBattlerTarget);
            if (gProtectStructs[gBattlerAttacker].helpingHand)
                gWishFutureKnock.futureSightDmg[gBattlerTarget] = gWishFutureKnock.futureSightDmg[gBattlerTarget] * 15 / 10;
            /*if (gCurrentMove == MOVE_DOOM_DESIRE)
                gBattleCommunication[MULTISTRING_CHOOSER] = 1;
            else*/
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            //gBattlescriptCurrInstr += 5;
        }
    }
    else
    {
        if (gWishFutureKnock.futureSightCounter[gBattlerTarget] != 0 && gWishFutureKnock.futureSightCounter2[gBattlerTarget] != 0) //prevents spamming each turn
        {   //to avoid issues with move name, don't allow doom desire if either couner is in use
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        else
        {
            gWishFutureKnock.futureSightMove[gBattlerTarget] = gCurrentMove;
            gWishFutureKnock.futureSightAttacker[gBattlerTarget] = gBattlerAttacker;
            gWishFutureKnock.futureSightCounter[gBattlerTarget] = 3;
            gWishFutureKnock.futureSightDmg[gBattlerTarget] = CalculateBaseDamage(&gBattleMons[gBattlerAttacker],
                                                                                &gBattleMons[gBattlerTarget],
                                                                                gCurrentMove,
                                                                                gSideStatuses[GetBattlerSide(gBattlerTarget)],
                                                                                0,
                                                                                0,
                                                                                gBattlerAttacker,
                                                                                gBattlerTarget);
            if (gProtectStructs[gBattlerAttacker].helpingHand)
                gWishFutureKnock.futureSightDmg[gBattlerTarget] = gWishFutureKnock.futureSightDmg[gBattlerTarget] * 15 / 10;
            if (gCurrentMove == MOVE_DOOM_DESIRE)
                gBattleCommunication[MULTISTRING_CHOOSER] = 1; //potentially add on, if more moves used, 
            //else
              //  gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            //gBattlescriptCurrInstr += 5;
        }
    }
    gBattlescriptCurrInstr += 5;
    //vsonic IMPORTANT
}//may add a way to do a second future sight before timer is up for a bit of strategy
//should be simple as adding a 2nd futureSightCounter, with same effects
//but make it default to counter2 if the first counter isn't 0.
//then add the anti spam thing to the counter 2, so if both counters are being used
//nothing will be done the move will fail.

//problem is there's no way to make the player aware of this change,
//so what I think I'll do is add a special event to lavender town
//after you defeat cubone's mother the priest will say there still apears to be 
//a dark presence here. when you reach the top of the tower

// the lights should flash and a mismagius should appear
//I'll give it pain split and future sight to better make use 
//of the move change and show off the effect
//as well as give you something special you can potentially catch there.

//need compare against battler use same logic I did for sum screen stat recalc vsonic
#define BEAT_UP_LOGIC
static void atkC4_trydobeatup(void) //beatup is still typeless in gen3 so no stab,
// I'm going to augment this add psuedo stab by increasing damage if pokemon attacking is dark type
//redo as normal multihit effect that loops based on number of mon in party this function would serve as alternate dmgcalc
//can put number of hits
{
    struct Pokemon *party;
    //u16 gDynamicBasePower = 0; //setting to 0, made it not insta kill,
    //still don't know if it now works propperly against defenses, believe it should.

    //u16 power = gBattleMoves[gCurrentMove].power = GetMonData(&party[gBattleCommunication[0]], STAT_ATK) / 10 + 5;

    // talked with GriffinR, gbattlemovedamage deals with the hp damage dealt,
    //but it still factors in enemy defenses in the final damage calculation
    //because ofthe calculatebasedamage function in damagecalc command

    //since I'm not doing damagecalc because I'm taking damage from each mon in party
    //I need to make this do everything damagecalc does to, get the to use
    //enemy defenses in damage calc, so I need to adapt the calculatebasedamage function for this effect
    //everything else is already done here.

    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;
    if (gBattleMons[gBattlerTarget].hp == 0) //why isn't this ending the move?
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        u8 beforeLoop = gBattleCommunication[0];

        for (;gBattleCommunication[0] < PARTY_SIZE; ++gBattleCommunication[0])
        {
            if (GetMonData(&party[gBattleCommunication[0]], MON_DATA_HP)
             && GetMonData(&party[gBattleCommunication[0]], MON_DATA_SPECIES_OR_EGG)
             && GetMonData(&party[gBattleCommunication[0]], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
             && !GetMonData(&party[gBattleCommunication[0]], MON_DATA_STATUS))
                break; // continue party loop if mon alive, not an egg, and not statused

            //fails when attacker is statused but that is default behavior I guess
            //can't exactly think of how to make exclusion that fits all cases, unless do a battlerId return/specific battle position
            //need test later will only attempt if move has different behavior if statuses beat up user is 2nd battler in doubles
            //right now it breaks at 0, but if it does something different if it breaks at 1, I'll have to adjust for 
            //consistency
        }
        if (gBattleCommunication[0] < PARTY_SIZE) 
        { //don't want to use base attack that would ignore all gains
            PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattleCommunication[0])
            gBattlescriptCurrInstr += 9;
            //gBattleMoveDamage = gBaseStats[GetMonData(&party[gBattleCommunication[0]], MON_DATA_SPECIES)].baseAttack;
            gBattleMoveDamage = ((GetMonData(&party[gBattleCommunication[0]], MON_DATA_ATK2)) / 4 + 1); //was too high at early levels scaled down for consistency
            
            //gBattleMoveDamage = (gBattleMons[GetMonData(&party[gBattleCommunication[0]], MON_DATA_ATK2)].attack) / 10 + 5;
            //gBattleMons
            //I think using this, makes it do fixed damage, instead of use base power,
            //which is fine exect I think it excludes it from defense calculations
            //so I'm going to try using gdynamicbasepower and see if the damage is still the same-ish

            //ok using stat_atk, may have been a problem, think I'l do an equivalency check
            //so that if its &party[gBattleCommunication[0] it'll use actual stat, and for the others use base stat.
            //that way it can still be boosted..

            //stat_atk is fine, the ENTIRE reason damage was so broken was because the script, didn't
            //have a damaagecalc command in it  FACEPALM!!!
            //still weird since the default didn't need one, but whatever...

            //gBattleMoveDamage *= power;
            //gBattleMoveDamage *= (GetMonData(&party[gBattleCommunication[0]], MON_DATA_LEVEL) * 2 / 5 + 2);
            //gBattleMoveDamage /= gBaseStats[gBattleMons[gBattlerTarget].species].baseDefense;
            //gBattleMoveDamage = (gBattleMoveDamage / 50) + 2; //this most likely will do nothing, and stat_atk is hhe problem but I'll try it.
            
            //didn't work think will just exclude from helping hand boost
            /*if (gProtectStructs[&party[gBattleCommunication[0]]].helpingHand) //think will work should apply once to battler on field only
                gBattleMoveDamage = (150 * gBattleMoveDamage) / 100;*/
            //may adjst later to be like below, replace gbattleattacker
            //and make it only work on the attacking pokemon's hit.
            //or what I can do is, keep gbattleattacker, and run getMondata species & personality
            //and if party[gbattlecommunication[0] match it,
            //THEN gbattlemovedamage = what I have below.

            //i.e if gBaseStats[GetMonData(gbattleAttacker, MON_DATA_SPECIES)
            // && gBaseStats[GetMonData(gbattleAttacker, MON_DATA_PERSONALITY)
            // == gBaseStats[GetMonData(&party[gBattleCommunication[0]], MON_DATA_SPECIES)
            // && gBaseStats[GetMonData(&party[gBattleCommunication[0]], MON_DATA_PERSONALITY)

            //if gbattleattacker has helping hand flag
            //step 1, get species & personality of attacker,
            //step 2, compare with party loop,
            //step 3, another if statement, if equal increase battle damage for party loop[0]

            //vsonic think need readjust this use battler inplace of gbasestats ??
           if (gBaseStats[GetMonData(&party[gBattleCommunication[0]], MON_DATA_SPECIES)].type1 == TYPE_DARK
                || gBaseStats[GetMonData(&party[gBattleCommunication[0]], MON_DATA_SPECIES)].type2 == TYPE_DARK
                || gBattleMons[gBattlerAttacker].type3 == TYPE_DARK)
           {
                //gBattleMoveDamage = gBattleMoveDamage * 15 / 10;
               gBattleMoveDamage = (135 * gBattleMoveDamage) / 100;
               //gBattleMoveDamage = gBattleMoveDamage * gCritMultiplier * gBattleScripting.dmgMultiplier;
           } //thikn that above line doubled crit damage again.

           gBattleMoveDamage = gBattleMoveDamage * gCritMultiplier; //should allow to crit without damagecalc, make sure have crit message

           //   3/26/23 am unsure if this extra increment is necesary for loop should be incrementing already?
           //checked - yes its necessary, for is looping for end condition/to break, this is a second loop
           //that does the actual damage 

                //gBattleMoveDamage = ((gBattleMons[GetMonData(&party[gBattleCommunication[0]], MON_DATA_ATK2)].attack) / 10 + 5) * 15 / 10;
            ++gBattleCommunication[0]; // THIS stab boost may not be right, get second opinion,
             // it may actually only boost total damage instead of individual hit
            //while I would like to use isbattlertype, this is looping the entire party, and that macro can only check battlers
        }
        else if (beforeLoop != 0) //edited 3/26/23 think it should all work out now. ?
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        else
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 5);
    }
} //if I did this correctly it should still be typeless, but calculate on battle attack
//instead of species base attack, give stab multiplier if attaking party member is type dark
// as well as use the gen 5 base power calculation

static void atkC5_setsemiinvulnerablebit(void)  //thsi command is why move effect doesn't use secondaryeffectchance its handled in battlescript
{
    switch (gCurrentMove)   //this sets the status but the logic  is handled in accuracyhelper function
    {
    case MOVE_FLY:
    case MOVE_BOUNCE:
    case MOVE_SKY_DROP:
        gStatuses3[gBattlerAttacker] |= STATUS3_ON_AIR;
        gStatuses3[gBattlerAttacker] &= ~(STATUS3_SMACKED_DOWN); //remove grounding by flying/taking to the air //don't forget moves w hit in air flag have priority aginst in air targetgs
        gBattleResources->flags->flags[gBattlerAttacker] &= ~(RESOURCE_FLAG_ROOST); //end roost
        gDisableStructs[gBattlerAttacker].RoostTimer = 0;
        gDisableStructs[gBattlerAttacker].trenchRunTimer = 0;        
        break;
    case MOVE_DIG:
        gStatuses3[gBattlerAttacker] |= STATUS3_UNDERGROUND;
        break;
    case MOVE_DIVE:
        gStatuses3[gBattlerAttacker] |= STATUS3_UNDERWATER;
        break;
    case MOVE_PHANTOM_FORCE:
    case MOVE_SHADOW_FORCE:
        gStatuses3[gBattlerAttacker] |= STATUS3_PHANTOM_FORCE;
        break;
    }
    ++gBattlescriptCurrInstr;
}

static void atkC6_clearsemiinvulnerablebit(void)
{
    gStatuses3[gBattlerAttacker] &= ~STATUS3_SEMI_INVULNERABLE;
    ++gBattlescriptCurrInstr;
}

static void atkC7_setminimize(void)
{
    if (gHitMarker & HITMARKER_OBEYS)
        gStatuses3[gBattlerAttacker] |= STATUS3_MINIMIZED;
    ++gBattlescriptCurrInstr;
}

static void atkC9_jumpifattackandspecialattackcannotfall(void) // memento
{
    if (gBattleMons[gBattlerTarget].statStages[STAT_ATK] == 0
     && gBattleMons[gBattlerTarget].statStages[STAT_SPATK] == 0
     && gBattleCommunication[6] != 1)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gActiveBattler = gBattlerAttacker;
        if (CanSurviveInstantKOWithSturdy(gActiveBattler))
            gBattleMoveDamage = gBattleMons[gActiveBattler].hp - 1;
        else
            gBattleMoveDamage = gBattleMons[gActiveBattler].hp;
        BtlController_EmitHealthBarUpdate(0, INSTANT_HP_BAR_DROP);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 5;
    }
}

static void atkCA_setforcedtarget(void) // follow me
{
    gSideTimers[GetBattlerSide(gBattlerAttacker)].followmeTimer = 1;
    gSideTimers[GetBattlerSide(gBattlerAttacker)].followmeTarget = gBattlerAttacker;
    ++gBattlescriptCurrInstr;
}

static void atkCB_setcharge(void)
{
    CMD_ARGS(u8 battler);
    u8 battler = cmd->battler;
    gStatuses3[battler] |= STATUS3_CHARGED_UP;
    gBattlescriptCurrInstr = cmd->nextInstr;
}

static void atkCC_callterrainattack(void) // nature power
{
    gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
    gCurrentMove = GetNaturePowerMove();//sNaturePowerMoves[gBattleTerrain];
    gBattlerTarget = GetMoveTarget(gCurrentMove, 0);
    SetAtkCancellerForCalledMove();
    BattleScriptPush(gBattleScriptsForBattleEffects[gBattleMoves[gCurrentMove].effect]);
    ++gBattlescriptCurrInstr;
}

static void atkCD_cureifburnedparalysedorpoisoned(void) // refresh
{
    if (gBattleMons[gBattlerAttacker].status1 & (STATUS1_POISON | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON))
    {
        gBattleMons[gBattlerAttacker].status1 = 0;
        gBattlescriptCurrInstr += 5;
        gActiveBattler = gBattlerAttacker;
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
        MarkBattlerForControllerExec(gActiveBattler);
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkCE_settorment(void)
{
    if (gBattleMons[gBattlerTarget].status2 & STATUS2_TORMENT
        || GetBattlerAbility(gBattlerTarget) == ABILITY_UNAWARE
        || GetBattlerAbility(gBattlerTarget) == ABILITY_OWN_TEMPO
        || GetBattlerAbility(gBattlerTarget) == ABILITY_OBLIVIOUS
        || GetBattlerAbility(gBattlerTarget) == ABILITY_FEMME_FATALE)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gBattleMons[gBattlerTarget].status2 |= STATUS2_TORMENT;
        gBattlescriptCurrInstr += 5;
    }
}

static void atkCF_jumpifnodamage(void)
{
    if (gProtectStructs[gBattlerAttacker].physicalDmg || gProtectStructs[gBattlerAttacker].specialDmg)
        gBattlescriptCurrInstr += 5;
    else
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
}

static void atkD0_settaunt(void)    //adjusted setup to be more in line with torment
{
    NATIVE_ARGS(const u8* failInstr);

    if ((gDisableStructs[gBattlerTarget].tauntTimer != 0)
        || GetBattlerAbility(gBattlerTarget) == ABILITY_UNAWARE 
        || GetBattlerAbility(gBattlerTarget) == ABILITY_OWN_TEMPO
        || GetBattlerAbility(gBattlerTarget) == ABILITY_OBLIVIOUS
        || GetBattlerAbility(gBattlerTarget) == ABILITY_FEMME_FATALE)
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
    else
    {
        gDisableStructs[gBattlerTarget].tauntTimer = 3;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    
}//consider increasing timer for modern vsonic
//and text indicators, end turn mon calmed down
//-done

static void atkD1_trysethelpinghand(void)
{
    gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_FLANK);
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
     && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget])
     && !gProtectStructs[gBattlerAttacker].helpingHand
     && !gProtectStructs[gBattlerTarget].helpingHand)
    {
        gProtectStructs[gBattlerTarget].helpingHand = 1;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkD2_tryswapitems(void) // trick
{
    // opponent can't swap items with player in regular battles
    //change this later, would need setup logic so item gets recovered at battle end, just like knockoff
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER
     || (GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT
         && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER))
         && gTrainerBattleOpponent_A != TRAINER_SECRET_BASE))
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        u8 sideAttacker = GetBattlerSide(gBattlerAttacker);
        u8 sideTarget = GetBattlerSide(gBattlerTarget);

        // you can't swap items if they were knocked off in regular battles
        if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER))
         && gTrainerBattleOpponent_A != TRAINER_SECRET_BASE
         && (gWishFutureKnock.knockedOffMons[sideAttacker] & gBitTable[gBattlerPartyIndexes[gBattlerAttacker]]
            || gWishFutureKnock.knockedOffMons[sideTarget] & gBitTable[gBattlerPartyIndexes[gBattlerTarget]]))
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        // can't swap if two pokemon don't have an item
        // or if either of them is an enigma berry or a mail
        else if ((gBattleMons[gBattlerAttacker].item == 0 && gBattleMons[gBattlerTarget].item == 0)
              || gBattleMons[gBattlerAttacker].item == ITEM_ENIGMA_BERRY
              || gBattleMons[gBattlerTarget].item == ITEM_ENIGMA_BERRY
              || IS_ITEM_MAIL(gBattleMons[gBattlerAttacker].item)
              || IS_ITEM_MAIL(gBattleMons[gBattlerTarget].item)
              || GetBattlerAbility(gBattlerTarget) == ABILITY_KLUTZ)  //ADDED klutz mon would just drop it, could make logic for that, if klutz mon has held item it'd default to knocked off on swith in
        {                                                                   //"mon dropped it's "glastusditem"/helditem!" so that'd only be an ability reveal if you were dumb enough to leave an item on a klutz mon  vsonic
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        // check if ability prevents swapping
        else if (GetBattlerAbility(gBattlerTarget) == ABILITY_STICKY_HOLD)
        {
            gBattlescriptCurrInstr = BattleScript_StickyHoldActivates;
            gLastUsedAbility = GetBattlerAbility(gBattlerTarget);
            RecordAbilityBattle(gBattlerTarget, gLastUsedAbility);
        }
        // took a while, but all checks passed and items can be safely swapped
        else
        {
            u16 oldItemAtk, *newItemAtk;

            newItemAtk = &gBattleStruct->changedItems[gBattlerAttacker];
            oldItemAtk = gBattleMons[gBattlerAttacker].item;
            *newItemAtk = gBattleMons[gBattlerTarget].item;
            gBattleMons[gBattlerAttacker].item = ITEM_NONE;
            gBattleMons[gBattlerTarget].item = oldItemAtk;
            gActiveBattler = gBattlerAttacker;
            BtlController_EmitSetMonData(0, REQUEST_HELDITEM_BATTLE, 0, 2, newItemAtk);
            MarkBattlerForControllerExec(gBattlerAttacker);
            gActiveBattler = gBattlerTarget;
            BtlController_EmitSetMonData(0, REQUEST_HELDITEM_BATTLE, 0, 2, &gBattleMons[gBattlerTarget].item);
            MarkBattlerForControllerExec(gBattlerTarget);
            gBattleStruct->choicedMove[gBattlerTarget] = MOVE_NONE;
            gBattleStruct->choicedMove[gBattlerAttacker] = MOVE_NONE;
            /*(u8 *)((u8 *)(&gBattleStruct->choicedMove[gBattlerTarget]) + 0) = 0;
            *(u8 *)((u8 *)(&gBattleStruct->choicedMove[gBattlerTarget]) + 1) = 0;

            *(u8 *)((u8 *)(&gBattleStruct->choicedMove[gBattlerAttacker]) + 0) = 0;
            *(u8 *)((u8 *)(&gBattleStruct->choicedMove[gBattlerAttacker]) + 1) = 0;*/
            gBattlescriptCurrInstr += 5;
            PREPARE_ITEM_BUFFER(gBattleTextBuff1, *newItemAtk)
            PREPARE_ITEM_BUFFER(gBattleTextBuff2, oldItemAtk)
            GetItemName(gBattleTextBuff1, *newItemAtk);
            GetItemName(gBattleTextBuff2, oldItemAtk);
            if (oldItemAtk != ITEM_NONE && *newItemAtk != ITEM_NONE)
                gBattleCommunication[MULTISTRING_CHOOSER] = 2; // attacker's item -> <- target's item
            else if (oldItemAtk == ITEM_NONE && *newItemAtk != ITEM_NONE)
                gBattleCommunication[MULTISTRING_CHOOSER] = 0; // nothing -> <- target's item
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 1; // attacker's item -> <- nothing
        }
    }
}

static void atkD3_trycopyability(void) // role play
{
    if (gBattleMons[gBattlerTarget].ability != ABILITY_NONE) //changed to remove excluding abilities like wonderguard
    {
        gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerTarget].ability;
        gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkD4_trywish(void)
{
    switch (gBattlescriptCurrInstr[1]) //figure out how this works
    {
    case 0: // use wish
        if (gWishFutureKnock.wishCounter[gBattlerAttacker] == 0)
        {
            gWishFutureKnock.wishCounter[gBattlerAttacker] = 2;
            gWishFutureKnock.wishMonId[gBattlerAttacker] = gBattlerPartyIndexes[gBattlerAttacker];
            gBattlescriptCurrInstr += 6;
        }
        else
        {
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 2);
        }
        break;
    case 1: // heal effect
        PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattlerTarget, gWishFutureKnock.wishMonId[gBattlerTarget])
        gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 2;
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;
        if (gBattleMons[gBattlerTarget].hp == gBattleMons[gBattlerTarget].maxHP)
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 2);
        else
            gBattlescriptCurrInstr += 6;
        break;
    }
}

static void atkD5_trysetroots(void) // ingrain
{
    if (gStatuses3[gBattlerAttacker] & STATUS3_ROOTED)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gStatuses3[gBattlerAttacker] |= STATUS3_ROOTED;
        gBattlescriptCurrInstr += 5;
    }
}

void BS_trysetaquaring(void)    //aqua ring
{
    if (gStatuses3[gBattlerAttacker] & STATUS3_AQUA_RING)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gStatuses3[gBattlerAttacker] |= STATUS3_AQUA_RING;
        gBattlescriptCurrInstr += 5;
    }
}

static void atkD6_doubledamagedealtifdamaged(void) //move revenge, test used call if works
{
    if ((gProtectStructs[gBattlerAttacker].physicalDmg != 0
        && gProtectStructs[gBattlerAttacker].physicalBattlerId == gBattlerTarget)
     || (gProtectStructs[gBattlerAttacker].specialDmg != 0
        && gProtectStructs[gBattlerAttacker].specialBattlerId == gBattlerTarget))
    {
        gBattleMoveDamage *= 2;
        //gBattleScripting.dmgMultiplier = 2;
    }
    ++gBattlescriptCurrInstr;
}

static void atkD7_setyawn(void)
{
    CMD_ARGS(const u8 *failInstr);

    if (gStatuses3[gBattlerTarget] & STATUS3_YAWN
        || gBattleMons[gBattlerTarget].status1 & STATUS1_ANY)
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
    else if (IsBattlerTerrainAffected(gBattlerTarget, STATUS_FIELD_ELECTRIC_TERRAIN))
    {
        // When Yawn is used while Electric Terrain is set and drowsiness is set from Yawn being used against target in the previous turn:
        // "But it failed" will display first.
        gBattlescriptCurrInstr = BattleScript_ElectricTerrainPrevents;
    }
    else if (IsBattlerTerrainAffected(gBattlerTarget, STATUS_FIELD_MISTY_TERRAIN))
    {
        // When Yawn is used while Misty Terrain is set and drowsiness is set from Yawn being used against target in the previous turn:
        // "But it failed" will display first.
        gBattlescriptCurrInstr = BattleScript_MistyTerrainPrevents;
    }
    else
    {
        gStatuses3[gBattlerTarget] |= STATUS3_YAWN;
        gDisableStructs[gBattlerTarget].YawnTimer = 1;
        CancelMultiTurnMoves(gBattlerTarget);
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

void BS_JumpandClearRage(void)
{
     NATIVE_ARGS(const u8 *jumpInstr);

    if (gBattleMons[gBattlerTarget].status2 & STATUS2_RAGE) 
    {   
        ClearRageStatuses(gBattlerTarget); //clear message adding to script
        gBattlescriptCurrInstr = cmd->jumpInstr;
    }
    else
        gBattlescriptCurrInstr = cmd->nextInstr;
}



static void atkD8_setdamagetohealthdifference(void) //make case here for final gambit
{//remember wanted to change how final gambit works more damage lower your hp or it equals health lost?
    //could do percent of hp lost, and then also add an extra fixed hp damage on top so it can actually kill
    //like say %hp lost + 40hp.
    if (gBattleMons[gBattlerTarget].hp <= gBattleMons[gBattlerAttacker].hp)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else //should prob make new command instead actually
    {
        gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - gBattleMons[gBattlerAttacker].hp;
        gBattlescriptCurrInstr += 5;
    }
} //to get percent do gbatmovedamage = (target.hp * attacker.hp/attacker.maxhp) -40    //for final gambit
//then I need to change this conditional to make it

//that was wrong, that way would do the opposite of what I want it would be less damage the lower my hp.
//I need to make move damgage teh percentage of hp I've lost, not percentage I have remainnig.
//to do that I need attacker.max hp - attacker.hp / attacker.max hp * target.max hp + 40

//alternatively (((attacker.max hp - attacker.hp) / attacker.max hp) * target.hp) + attacker.maxhp
//more complex but scales with level and isn't a guaranteed 1 shot regardless of level. actually this may be even stronger
//will change the move to instead of faint attacker, reduce attaker hp to 1.
//i.e all their energy is spent, plus it makes the move useful for power leveling.

static void atkD9_scaledamagebyhealthratio(void)    //eruption
{
    if (gDynamicBasePower == 0)
    {
        u8 power = gBattleMoves[gCurrentMove].power;
        
        gDynamicBasePower = gBattleMons[gBattlerAttacker].hp * power / gBattleMons[gBattlerAttacker].maxHP;
        if (gDynamicBasePower == 0)
            gDynamicBasePower = 1;
    }
    ++gBattlescriptCurrInstr;
}

static void atkDA_tryswapabilities(void) // skill swap . //remember need to remove wonderguard from all abiility swap functions,. because game freak
{
    if ((gBattleMons[gBattlerAttacker].ability == 0
        && gBattleMons[gBattlerTarget].ability == 0)
     || gMoveResultFlags & MOVE_RESULT_NO_EFFECT) //not sure if nor effect clause would still prevent working on wonderguard.
     {
         gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
     }//doesn't use getbattlerability as can swap even if ability isn't in effect
    else
    {
        u16 abilityAtk = gBattleMons[gBattlerAttacker].ability;
        
        gBattleMons[gBattlerAttacker].ability = gBattleMons[gBattlerTarget].ability;
        gBattleMons[gBattlerTarget].ability = abilityAtk;  //potentially use this as an example of how to swap hp for wonderguard swap

            gBattlescriptCurrInstr += 5;
    }
}//make skill swap status and apply to both mon  vsonic

static void atkDB_tryimprison(void)
{
    if ((gStatuses3[gBattlerAttacker] & STATUS3_IMPRISONED_OTHERS))
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        u8 battlerId, sideAttacker;

        sideAttacker = GetBattlerSide(gBattlerAttacker);
        PressurePPLoseOnUsingImprison(gBattlerAttacker);
        for (battlerId = 0; battlerId < gBattlersCount; ++battlerId)
        {
            if (sideAttacker != GetBattlerSide(battlerId))
            {
                s32 attackerMoveId;

                for (attackerMoveId = 0; attackerMoveId < MAX_MON_MOVES; ++attackerMoveId)
                {
                    s32 i;

                    for (i = 0; i < MAX_MON_MOVES; ++i)
                    {
                        if (gBattleMons[gBattlerAttacker].moves[attackerMoveId] == gBattleMons[battlerId].moves[i]
                         && gBattleMons[gBattlerAttacker].moves[attackerMoveId] != MOVE_NONE)
                            break;
                    }
                    if (i != MAX_MON_MOVES)
                        break;
                }
                if (attackerMoveId != MAX_MON_MOVES)
                {
                    gStatuses3[gBattlerAttacker] |= STATUS3_IMPRISONED_OTHERS;
                    gBattlescriptCurrInstr += 5;
                    break;
                }
            }
        }
        if (battlerId == gBattlersCount) // In Generation 3 games, Imprison fails if the user doesn't share any moves with any of the foes
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkDC_trysetgrudge(void)
{
    if (gStatuses3[gBattlerAttacker] & STATUS3_GRUDGE)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gStatuses3[gBattlerAttacker] |= STATUS3_GRUDGE;
        gBattlescriptCurrInstr += 5; // this means to skip forward 5 steps in the battle script, command listing. useful for selecting specific effects.
    } //   Also useful to use call or goto instead of jump if use call, should be able to return as I want. with "return;"
}

static void atkDD_weightdamagecalculation(void)
{
    s32 i;

    for (i = 0; sWeightToDamageTable[i] != 0xFFFF; i += 2) //go to next row, if not 0xffff
    {
        if (sWeightToDamageTable[i] > GetBattlerWeight(gBattlerTarget))
            break;  //tells it to stop loop, sets damage
    }
    if (sWeightToDamageTable[i] != 0xFFFF)
        gDynamicBasePower = sWeightToDamageTable[i + 1];
    //else
      //  gDynamicBasePower = 120;
    ++gBattlescriptCurrInstr;
}

static void atkDE_assistattackselect(void)
{
    s32 chooseableMovesNo = 0;
    struct Pokemon *party;
    s32 monId, moveId;
    u16 *movesArray = gBattleStruct->assistPossibleMoves;

    if (GET_BATTLER_SIDE(gBattlerAttacker) != B_SIDE_PLAYER)
        party = gEnemyParty;
    else
        party = gPlayerParty;
    for (monId = 0; monId < PARTY_SIZE; ++monId)
    {
        if (monId == gBattlerPartyIndexes[gBattlerAttacker]
         || GetMonData(&party[monId], MON_DATA_SPECIES_OR_EGG) == SPECIES_NONE
         || GetMonData(&party[monId], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
            continue;
        for (moveId = 0; moveId < MAX_MON_MOVES; ++moveId)
        {
            s32 i = 0;
            u16 move = GetMonData(&party[monId], MON_DATA_MOVE1 + moveId);

            if (IsInvalidForAssist(move))
                continue;
            for (; sMovesForbiddenToCopy[i] != ASSIST_FORBIDDEN_END && move != sMovesForbiddenToCopy[i]; ++i);
            if (sMovesForbiddenToCopy[i] != ASSIST_FORBIDDEN_END || move == MOVE_NONE)
                continue;
            movesArray[chooseableMovesNo] = move;
            ++chooseableMovesNo;
        }
    }
    if (chooseableMovesNo)
    {
        gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
        gCalledMove = movesArray[((Random() & 0xFF) * chooseableMovesNo) >> 8];
        gBattlerTarget = GetMoveTarget(gCalledMove, 0);
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkDF_setmagiccoat(void)
{

    gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = TRUE;
    
    if (gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_MAGIC_COAT)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    else
    {
        gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] |= SIDE_STATUS_MAGIC_COAT;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].MagicTimer = 3;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].MagicBattlerId = gBattlerAttacker;

        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && CountAliveMonsInBattle(BATTLE_ALIVE_ATK_SIDE) == 2)
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        else
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;

        gProtectStructs[gBattlerAttacker].bounceMove = TRUE; //setup done, bounce effect removed along with status in battle_util.c
    }
    ++gBattlescriptCurrInstr;
}


static void atkE0_trysetsnatch(void) // snatch
{
    gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = 1;
    if (gCurrentTurnActionNumber == gBattlersCount - 1) // moves last turn
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gProtectStructs[gBattlerAttacker].stealMove = 1;
        gBattlescriptCurrInstr += 5;
    }
}

//setting up new copy ability think can just use all same values?
static void atkE1_trygetintimidatetarget(void) //I'd like to be able to get it ot target based on the case id abilityeffect in the util.c
//ABILITYEFFECT_INTIMIDATE2 is the one  for switchin  so changing the targetting for just that should make it work how I want
//maybe do it like trace and have the targetting built into the activation function
{
    u8 side; //if use of gbattletarget messes up switchin use, I can take notes from synchronize ability scrpit
    //and add different activation to the function based on if its attacker or target  IMPORTANT

    //will prob need to put below line in condition for ability intimidate vs tiger mom, possibly can use same line
    gBattleScripting.battler = gBattleStruct->intimidateBattler;//linked with intimidate in util.c, it finds mon with intimidate/condition and sets that battler to the battlescript battler
    side = GetBattlerSide(gBattleScripting.battler); //
    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gBattleMons[gBattleScripting.battler].ability) //sets mon ability to string buffer for activation text i believe
    for (;gBattlerTarget < gBattlersCount; ++gBattlerTarget) //loops through battlers to find mon on opposite side to mon
        if (GetBattlerSide(gBattlerTarget) != side && !(gAbsentBattlerFlags & gBitTable[gBattlerTarget]))
            break; //If they are on the opposite side and not absent, it breaks to end the loop, saying that its found an valid target
    
    if (gBattlerTarget >= gBattlersCount) //from Griffin R if it break before reaching the end of the loop then gBattlerTarget >= gBattlersCount will be false. 
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    else //It has found a valid target for intimidate, and it won't take jump to the specified pointer, it will instead move to the next command
        gBattlescriptCurrInstr += 5;
}//this prob important for my implementaiton of intimidate, since
//I need to have selective targetting, since I don't want it to reactivate
//for mon that have already been intimidated.  unless i switch in again

//switch is handled by 2 battle scripts  BattleScript_DoSwitchOut  & BattleScript_FaintedMonTryChooseAnother
//will use BattleScript_FaintedMonChooseAnother  if no party members let besides last mon

//instead of changing intimdiate/switch in funcitons
//I think the best way may be to make a psudo similar bs command function, and add it to every switch battle script
//make sure it activates on attacker since all switch stuff uses attacker
//and make a function that will loop through all the abilities I want to reactivate with a switch case that
//will recreate the effects  hopefully will not have to make new strings.

//essentially I'm not going to be able to actually reactivate the scripts because of how they activate
//so I'll just make it look like they are activating/have the same effect

//WILL NEED to make sure I have something to prevent it activating in the case I switch in, when the enemy is also switching mon.
//otherwise I think it would cause a double activation or loop. 
//as it would call the normal switch in activation as well.  //assuming that's possible since it runs on turn order...
//might not be if I switch in, and the enemy hasn't brought there mon in, or they switch in, and I"m not on the field yet.
//do an explosion test...

static void atkE2_switchoutabilities(void) //emerald has logic for switchin that fixes issue of switchin activating too early so copy switchin postpone setup
{
    CMD_ARGS(u8 battler); //cmd args works now that I fixed setup

    gActiveBattler = GetBattlerForBattleScript(cmd->battler);
    if (GetBattlerAbility(gActiveBattler) == ABILITY_NEUTRALIZING_GAS)    //looks like put here so it goes first just like in switch-in (..oh this is why I guess)
    {
        gBattleMons[gActiveBattler].ability = ABILITY_NONE;
        BattleScriptPush(gBattlescriptCurrInstr);
        gBattlescriptCurrInstr = BattleScript_NeutralizingGasExits;
    }
    else if (GetBattlerAbility(gActiveBattler) == ABILITY_IMMUTABLE_WIND)    //looks like put here so it goes first just like in switch-in (..oh this is why I guess)
    {
        gBattleMons[gActiveBattler].ability = ABILITY_NONE;
        BattleScriptPush(gBattlescriptCurrInstr);
        gBattlescriptCurrInstr = BattleScript_ImmutableWindExits; //change
    }
    else if (GetBattlerAbility(gActiveBattler) == ABILITY_STENCH) //doesn't work with if, so putting in else if, to change order of list...
    {
        gBattleMons[gActiveBattler].ability = ABILITY_NONE; //ok think I understand what this is for now, without this it loops, so removing ability lets it not retrigger
        BattleScriptPush(gBattlescriptCurrInstr);
        gBattlescriptCurrInstr = BattleScript_StenchExits;
    }//else if worked,
    else if (GetBattlerAbility(gActiveBattler) == ABILITY_AFTERMATH
    && IsBattlerAlive(gBattlerTarget)) //vsonic still in progress - think missing that was issue that caused reactivate
    {
        if ((IsAbilityOnField(ABILITY_DAMP)))
        {
            for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; ++gBattlerTarget)
            if (GetBattlerAbility(gBattlerTarget) == ABILITY_DAMP)
                break;
            gLastUsedAbility = ABILITY_AFTERMATH;
            RecordAbilityBattle(gBattlerTarget, gBattleMons[gBattlerTarget].ability);
            BattleScriptPush(gBattlescriptCurrInstr);
            gBattlescriptCurrInstr = BattleScript_DampPreventsAftermathOnSwitch; //consider replace with break, so no message just switch out
            gBattleMons[gActiveBattler].ability = ABILITY_NONE;
        }
        else//does work for both battlers or just one enemy, if one, how does it select target? need work that out
        {
            PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gBattleMons[gActiveBattler].ability)
            //--gBattleMons[gBattlerTarget].statStages[STAT_SPEED]; //don't know if will properly trigger animation or not
            gBattleMons[gActiveBattler].ability = ABILITY_NONE; //this was the issue same as others,  with push command keeping ability causes loop issue
            //works for target setting, will set to opponent directly accross from user
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                gBattlerTarget = BATTLE_OPPOSITE(BATTLE_PARTNER(gActiveBattler));
            
            gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 16; //potentially make 1/16th as its just meant to do chip damage & break bands and can retrigger?
            if (gBattleMoveDamage == 0) //occurred to me only having smaller chip damage on this withuot the slow wouldn't make the ability useful considering you need to 
                gBattleMoveDamage = 1; //pivot to make it useful so you'd be takeing two hits not just this one, think will put slow on switchout as well.
            BattleScriptPush(gBattlescriptCurrInstr);
            gBattlescriptCurrInstr = BattleScript_AftermathOnSwitch; //think stat drop should work now? since i'm bs attacker used swapattackerwithtarget to change battlescript to target for speed drop then
            //SET_STATCHANGER(STAT_SPEED, 1, TRUE);
        }//think can't go any further with this till I Fix battles..
    } //how would this work in doubles? technically I want this to only hit one?
    //check in doubles, but otherwise I need a targetting thing to specifically 
    //set gbattletarget
    else //noticeable differnece is values in switch, dont use battlescript  and are meant to affect the mon they are on/mon switching?
    {
        switch (GetBattlerAbility(gActiveBattler))
        {
        case ABILITY_SHAMAN_CURE:
        case ABILITY_NATURAL_CURE:
            gBattleMons[gActiveBattler].status1 = 0;
            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, gBitTable[*(gBattleStruct->battlerPartyIndexes + gActiveBattler)], 4, &gBattleMons[gActiveBattler].status1);
            MarkBattlerForControllerExec(gActiveBattler); //think 4 bytes because dealing with status with is u32
            break;
        case ABILITY_WETIKO:
        case ABILITY_REGENERATOR: //just added
            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 3;
            gBattleMoveDamage += gBattleMons[gActiveBattler].hp;
            if (gBattleMoveDamage > gBattleMons[gActiveBattler].maxHP)
                gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP;
            BtlController_EmitSetMonData(0, REQUEST_HP_BATTLE, gBitTable[*(gBattleStruct->battlerPartyIndexes + gActiveBattler)], 2, &gBattleMoveDamage);
            MarkBattlerForControllerExec(gActiveBattler); //think 2 bytes because dealing with hp wish is u16
            break;
        case ABILITY_CUPIDS_ARROW:
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)//if cupid arrow switches out withotu another on field clear infatuation
        {
            if (GetBattlerAbility(BATTLE_PARTNER(gActiveBattler)) != ABILITY_CUPIDS_ARROW)
            {
                gBattleMons[gBattlerTarget].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler));
                gBattleMons[BATTLE_PARTNER(gBattlerTarget)].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler));
            }
        }
        else
            gBattleMons[gBattlerTarget].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler));
        break;//works how I want, even with faint
        }
        
        gBattlescriptCurrInstr = cmd->nextInstr;
        //gBattlescriptCurrInstr += 2;

    }
    
} //this had wrong brackets this entire time *facepalm

 
static void atkE3_jumpifhasnohp(void)
{
    gActiveBattler = GetBattlerForBattleScript(gBattlescriptCurrInstr[1]);

    if (gBattleMons[gActiveBattler].hp == 0)
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 2);
    else
        gBattlescriptCurrInstr += 6;
}

static void atkE4_getsecretpowereffect(void)
{
    switch (gBattleTerrain)
    {
    case BATTLE_TERRAIN_GRASS:
        gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
        break;
    case BATTLE_TERRAIN_LONG_GRASS:
        gBattleScripting.moveEffect = MOVE_EFFECT_SLEEP;
        break;
    case BATTLE_TERRAIN_SAND:
        gBattleScripting.moveEffect = MOVE_EFFECT_ACC_MINUS_1;
        break;
    case BATTLE_TERRAIN_UNDERWATER:
        gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_1;
        break;
    case BATTLE_TERRAIN_WATER:
        gBattleScripting.moveEffect = MOVE_EFFECT_ATK_MINUS_1;
        break;
    case BATTLE_TERRAIN_POND:
        gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
        break;
    case BATTLE_TERRAIN_MOUNTAIN:
        gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
        break;
    case BATTLE_TERRAIN_CAVE:
        gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
        break;
    default:
        gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
        break;
    }
    ++gBattlescriptCurrInstr;
}



#define PICKUP_LOGIC
static void atkE5_pickup(void) //effect will go in battle_util.c end turn ability clause, this will be kept here to prevent need to reordder bs macros
//why is this a bs command when the ability has no in battle effect?
{//ok all this was almost a waste pick up doesn't work how I thought it did. -_- it doesn't have an effect on battle
    //but its effect is trigger by battle. I'm removing this and changing to a overworld/field effect function.
    //putting here makes macro to be called at end of battle, it then sets an item from the list to your mons held item slot
    //which would only apply if mon wasnt holding anything -_-

    //will add end turn effect to battle_util.c to pick up random use item if not holding anything.
    //and if succeeds anounce the picked up item and set to held item slot, like default function
    //SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &sPickupItems[j]); 

    /*s32 i;
    u32 j;
    u16 species, heldItem;
    u32 ability;

    for (i = 0; i < PARTY_SIZE; ++i)
    {
        species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);
        heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
        /*if (GetMonData(&gPlayerParty[i], MON_DATA_ABILITY_NUM) != ABILITY_NONE) //important need change this
            ability = gBaseStats[species].abilities[1]; //well no mon have pipckup as hidden ability so this prob fine
        else
            ability = gBaseStats[species].abilities[0];
        if (GetMonData(&gPlayerParty[i], MON_DATA_ABILITY_NUM) == ABILITY_NONE)
            ability = gBaseStats[species].abilities[0];
        else if (GetMonData(&gPlayerParty[i], MON_DATA_ABILITY_NUM) == 1)
            ability = gBaseStats[species].abilities[1];
        else if (GetMonData(&gPlayerParty[i], MON_DATA_ABILITY_NUM) == 2)
            ability = gBaseStats[species].abilityHidden[0];
        else
            ability = gBaseStats[species].abilityHidden[1];

        if (ability == ABILITY_PICKUP //&& /*species != SPECIES_NONE && species != SPECIES_EGG && //heldItem == ITEM_NONE //remove this later
            && !(Random() % 6))    //random %10 is odds, its saying will trigger on a 10% chance when random returns 0
        {
            s32 random = Random() % 100; //then anothr set of rng, return a value betwen 0-99 and loops through pickup array until reach 
            //and odds value greater than your percent chance

            for (j = 0; j < ARRAY_COUNT(sPickupItems); ++j) //may add on to this, add better items
                if (sPickupItems[j].chance > random)    //effect isn't really random, so want to change?, may make pick a value between 15 rathre than loop it
                    break;//and exclusively for the tm return, I want to make it reset the itemid, so it returns a random tm/hm to get more use out of it
            //SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &sPickupItems[j]); 
            if (AddBagItem(&sPickupItems[j], 1) == TRUE) 
            {
                //AddBagItem(&sPickupItems[j], 1);  think don't need this, believe its doing the add, and then filtering for success condition
                GetMonNickname(&gPlayerParty[i], gStringVar2);
                CopyItemName(&sPickupItems[j]), gStringVar1);
                StringExpandPlaceholders(gStringVar4, gText_MonPickedUpItem);//most parts done, just need overworld textbox notification
                ShowFieldAutoScrollMessage(gStringVar4);
                
            }
            
        }//change this line to a script that will stop player, bufer found item to auto close window, and use AddBagItem, so it goes to bag.
        //this will allow actually running a held item on pickup mon, getting more use out of them
    }*/
    ++gBattlescriptCurrInstr;
}


static void atkE6_docastformchangeanimation(void)
{
    gActiveBattler = gBattleScripting.battler;
    if (gBattleMons[gActiveBattler].status2 & STATUS2_SUBSTITUTE)
        *(&gBattleStruct->formToChangeInto) |= 0x80;
    BtlController_EmitBattleAnimation(0, B_ANIM_CASTFORM_CHANGE, gBattleStruct->formToChangeInto);
    MarkBattlerForControllerExec(gActiveBattler);
    ++gBattlescriptCurrInstr;
}

static void atkE7_trycastformdatachange(void)
{
    u8 form;

    ++gBattlescriptCurrInstr;
    form = CastformDataTypeChange(gBattleScripting.battler);
    if (form)
    {
        BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
        *(&gBattleStruct->formToChangeInto) = form - 1;
    }
}

static void atkE8_settypebasedhalvers(void) // water and mud sport
{
    CMD_ARGS(const u8 *jumpInstr);
    bool8 worked = FALSE;
    
    if (gBattleMoves[gCurrentMove].effect == EFFECT_MUD_SPORT)
    {
        if (!(gSideStatuses[GetBattlerSide(gBattlerAttacker)] & SIDE_STATUS_MUDSPORT))
        {
            gSideStatuses[GetBattlerSide(gBattlerAttacker)] |= SIDE_STATUS_MUDSPORT;
            gSideTimers[GetBattlerSide(gBattlerAttacker)].mudSportTimer = 5;
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            worked = TRUE;
        }
    }
    else // water sport
    {
        if (!(gSideStatuses[GetBattlerSide(gBattlerAttacker)] & SIDE_STATUS_WATERSPORT))
        {
            gSideStatuses[GetBattlerSide(gBattlerAttacker)] |= SIDE_STATUS_WATERSPORT;
            gSideTimers[GetBattlerSide(gBattlerAttacker)].waterSportTimer = 5;
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
            worked = TRUE;
        }
    }
    if (worked)
        gBattlescriptCurrInstr = cmd->nextInstr;
    else
        gBattlescriptCurrInstr = cmd->jumpInstr;
}

//not using now, movedlogic to settypebeforeusingmove
static void atkE9_setweatherballtype(void)//think move to settypebeforeusemove function so it'll show in sum menu
{
    /*if (WEATHER_HAS_EFFECT)
    {
        //if (gBattleWeather & WEATHER_ANY)
        //    gBattleScripting.dmgMultiplier = 2;  //moved to calcbasdmg function in pokemon c
        if (gBattleWeather & WEATHER_RAIN_ANY) //TEST TO MAKE SURE WORKS - works
            *(&gBattleStruct->dynamicMoveType) = TYPE_WATER | 0x80;
        else if (gBattleWeather & WEATHER_SANDSTORM_ANY)
            *(&gBattleStruct->dynamicMoveType) = TYPE_ROCK | 0x80;
        else if (gBattleWeather & WEATHER_SUN_ANY)
            *(&gBattleStruct->dynamicMoveType) = TYPE_FIRE | 0x80;
        else if (gBattleWeather & WEATHER_HAIL_ANY)
            *(&gBattleStruct->dynamicMoveType) = TYPE_ICE | 0x80;
        else if (gBattleWeather & WEATHER_STRONG_WINDS)
            *(&gBattleStruct->dynamicMoveType) = TYPE_FLYING | 0x80;
        else
            *(&gBattleStruct->dynamicMoveType) = TYPE_NORMAL | 0x80;
    }
    ++gBattlescriptCurrInstr;*/
}

static void atkEA_tryrecycleitem(void) //vsonic need to update check
{
    u16 *usedHeldItem;

    gActiveBattler = gBattlerAttacker;
    usedHeldItem = &gBattleStruct->usedHeldItems[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)];
    if (*usedHeldItem != ITEM_NONE && gBattleMons[gActiveBattler].item == ITEM_NONE)
    {
        gLastUsedItem = *usedHeldItem;
        *usedHeldItem = ITEM_NONE;
        gBattleMons[gActiveBattler].item = gLastUsedItem;
        BtlController_EmitSetMonData(0, REQUEST_HELDITEM_BATTLE, 0, 2, &gBattleMons[gActiveBattler].item);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}


static void HandleScriptMegaPrimalBurst(u32 caseId, u32 battler, u32 type)
{
    struct Pokemon *party = GetBattlerParty(battler);
    struct Pokemon *mon = &party[gBattlerPartyIndexes[battler]];
    u32 position = GetBattlerPosition(battler);
    u32 side = GetBattlerSide(battler);

    // Change species.
    if (caseId == 0)
    {
        if (type == HANDLE_TYPE_MEGA_EVOLUTION)
        {
            if (!TryBattleFormChange(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM))
                TryBattleFormChange(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE);
        }
        else if (type == HANDLE_TYPE_PRIMAL_REVERSION)
            TryBattleFormChange(battler, FORM_CHANGE_BATTLE_PRIMAL_REVERSION);
        else
            TryBattleFormChange(battler, FORM_CHANGE_BATTLE_ULTRA_BURST);

        PREPARE_SPECIES_BUFFER(gBattleTextBuff1, gBattleMons[battler].species);

        BtlController_EmitSetMonData(BUFFER_A, REQUEST_SPECIES_BATTLE, gBitTable[gBattlerPartyIndexes[battler]], sizeof(gBattleMons[battler].species), &gBattleMons[battler].species);
        MarkBattlerForControllerExec(battler); //ported from emerald again need check since emitsetmondata is different
    }
    // Update healthbox and elevation and play cry.
    else
    {
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], mon, HEALTHBOX_ALL);
        if (side == B_SIDE_OPPONENT)
            SetBattlerShadowSpriteCallback(battler, gBattleMons[battler].species);
        if (type == HANDLE_TYPE_MEGA_EVOLUTION)
            gBattleStruct->mega.alreadyEvolved[position] = TRUE;
        //if (type == HANDLE_TYPE_ULTRA_BURST)
        //    gBattleStruct->burst.alreadyBursted[position] = TRUE;
    }
}

bool32 CanCamouflage(u8 battlerId)
{
    if (IS_BATTLER_OF_TYPE(battlerId, sTerrainToType[gBattleTerrain]))
        return FALSE;
    return TRUE;
}

static void atkEB_settypetoterrain(void)
{
    if (!IS_BATTLER_OF_TYPE(gBattlerAttacker, sTerrainToType[gBattleTerrain]))
    {
        SET_BATTLER_TYPE(gBattlerAttacker, sTerrainToType[gBattleTerrain]);
        PREPARE_TYPE_BUFFER(gBattleTextBuff1, sTerrainToType[gBattleTerrain]);
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

//unused
static UNUSED void atkEC_pursuitrelated(void)
{
    gActiveBattler = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_FLANK);

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
     && !(gAbsentBattlerFlags & gBitTable[gActiveBattler])
     && gChosenActionByBattler[gActiveBattler] == 0
     && CanMoveHitSwitchingTarget(gChosenMoveByBattler[gActiveBattler]))
    {
        gActionsByTurnOrder[gActiveBattler] = 11;
        gCurrentMove = gChosenMoveByBattler[gActiveBattler];
        gBattlescriptCurrInstr += 5;
        gBattleScripting.animTurn = 1;
        gBattleScripting.field_25_pursuitDoublesAttacker = gBattlerAttacker;
        gBattlerAttacker = gActiveBattler;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkED_snatchsetbattlers(void)
{
    gEffectBattler = gBattlerAttacker;
    if (gBattlerAttacker == gBattlerTarget)
        gBattlerAttacker = gBattlerTarget = gBattleScripting.battler;
    else
        gBattlerTarget = gBattleScripting.battler;
    gBattleScripting.battler = gEffectBattler;
    ++gBattlescriptCurrInstr;
}

static void atkEE_removelightscreenreflect(void) // brick break     //no longer need this can remove
{
    u8 opposingSide = GetBattlerSide(gBattlerAttacker) ^ BIT_SIDE;  //not using right now, 

    if (gSideTimers[opposingSide].reflectTimer || gSideTimers[opposingSide].lightscreenTimer)
    {
        gSideStatuses[opposingSide] &= ~(SIDE_STATUS_REFLECT);
        gSideStatuses[opposingSide] &= ~(SIDE_STATUS_LIGHTSCREEN);
        gSideTimers[opposingSide].reflectTimer = 0;
        gSideTimers[opposingSide].lightscreenTimer = 0;
        gBattleScripting.animTurn = 1;
        gBattleScripting.animTargetsHit = 1;
    }
    else
    {
        gBattleScripting.animTurn = 0;
        gBattleScripting.animTargetsHit = 0;
    }
    ++gBattlescriptCurrInstr;
}

//not using yet, but seems to be something for selecting catch target in wild double
//possibly flawed may have to tweak if I use

/*static u8 GetCatchingBattler(void)
{
    if (IsBattlerAlive(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)))
        return GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    else
        return GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
}*/

#define CATCHING_LOGIC

static void atkEF_handleballthrow(void) //important changed
{
    u8 ballMultiplier = 0;

    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = gBattlerAttacker;
        gBattlerTarget = gBattlerAttacker ^ BIT_SIDE;
        if (gBattleTypeFlags & BATTLE_TYPE_GHOST)
        {
            BtlController_EmitBallThrowAnim(0, BALL_GHOST_DODGE);
            MarkBattlerForControllerExec(gActiveBattler);
            gBattlescriptCurrInstr = BattleScript_GhostBallDodge;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            BtlController_EmitBallThrowAnim(0, BALL_TRAINER_BLOCK);
            MarkBattlerForControllerExec(gActiveBattler);
            gBattlescriptCurrInstr = BattleScript_TrainerBallBlock;
        }
        else if (gBattleTypeFlags & (BATTLE_TYPE_POKEDUDE | BATTLE_TYPE_OLD_MAN_TUTORIAL))
        {
            BtlController_EmitBallThrowAnim(0, BALL_3_SHAKES_SUCCESS);
            MarkBattlerForControllerExec(gActiveBattler);
            gBattlescriptCurrInstr = BattleScript_OldMan_Pokedude_CaughtMessage;
        }
        else
        {
            u32 odds;
            u8 catchRate;
            u16 targetSpecies = GetFormChangeTargetSpecies(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], FORM_CHANGE_END_BATTLE, 0);

            if (gLastUsedItem == ITEM_SAFARI_BALL)
                catchRate = gBattleStruct->safariCatchFactor * 1275 / 100;
            else
                catchRate = gBaseStats[gBattleMons[gBattlerTarget].species].catchRate;
            if (gLastUsedItem > ITEM_MASTER_BALL) //pretty much if pokeball is one of the special balls (not poke, great, ultra, or master
            {
                switch (gLastUsedItem)
                {
                case ITEM_NET_BALL:
                    if (IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_WATER) || IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_BUG))
                        ballMultiplier = 30;
                    else
                        ballMultiplier = 10;
                    break;
                case ITEM_DIVE_BALL:
                    if (GetCurrentMapType() == MAP_TYPE_UNDERWATER)
                        ballMultiplier = 35;
                    else
                        ballMultiplier = 10;
                    break;
                case ITEM_NEST_BALL:
                    if (gBattleMons[gBattlerTarget].level < 40)
                    {
                        ballMultiplier = 40 - gBattleMons[gBattlerTarget].level;
                        if (ballMultiplier <= 9)
                            ballMultiplier = 10;
                    }
                    else
                    {
                        ballMultiplier = 10;
                    }
                    break;
                case ITEM_REPEAT_BALL:
                    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gBattlerTarget].species), FLAG_GET_CAUGHT))
                        ballMultiplier = 30;
                    else
                        ballMultiplier = 10;
                    break;
                case ITEM_TIMER_BALL:
                    ballMultiplier = (gBattleResults.battleTurnCounter * 3) + 10;
                    if (ballMultiplier > 40)
                        ballMultiplier = 40;
                    break;
                case ITEM_LUXURY_BALL:
                case ITEM_PREMIER_BALL:
                    ballMultiplier = 10;
                    break;
                }
            }
            else
                ballMultiplier = sBallCatchBonuses[ItemIdToBallId(gLastUsedItem)];
            odds = (catchRate * ballMultiplier / 10) * (gBattleMons[gBattlerTarget].maxHP * 3 - gBattleMons[gBattlerTarget].hp * 2) / (3 * gBattleMons[gBattlerTarget].maxHP);
            
            if ((gBattleMons[gBattlerTarget].status1 & STATUS1_SLEEP || gDisableStructs[gBattlerTarget].FrozenTurns != 0)) //juset realiszed I could stack statsus bonsu by including status 2, since right now rules exclude status 1 overlap
                odds *= 2;
            if (gBattleMons[gBattlerTarget].status1 & (STATUS1_POISON | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON))
                odds = (odds * 15) / 10;
            if (gBattleMons[gBattlerTarget].status1 & STATUS1_FREEZE && gDisableStructs[gBattlerTarget].FrozenTurns == 0)
                odds = (odds * 15) / 10;

            if (gBattleMons[gBattlerTarget].status2 & STATUS2_CONFUSION)    //add ifs for status 2 to stack on top of status 1 liek here //include recharge, infatuation, nightmare, curse, & escape prevention & wrap etc
                odds += (odds / 10);  //TO increase catch chance by 10%,
            if (gBattleMons[gBattlerTarget].status2 & STATUS2_WRAPPED)
                odds += (odds / 5);
            else if (gBattleMons[gBattlerTarget].status4 & (ITS_A_TRAP_STATUS4))//(STATUS4_BIND | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_MAGMA_STORM | STATUS4_SWARM | STATUS4_SNAP_TRAP))
                odds += (odds / 5);
            if (gBattleMons[gBattlerTarget].status2 & STATUS2_INFATUATION)
                odds += (odds / 2);
            if (gBattleMons[gBattlerTarget].status2 & STATUS2_NIGHTMARE)
                odds += (odds / 8);
            if (gBattleMons[gBattlerTarget].status2 & STATUS2_CURSED)
                odds += (odds / 10);
            if (gBattleMons[gBattlerTarget].status4 & STATUS4_INFESTATION)    //add ifs for status 2 to stack on top of status 1 liek here //include recharge, infatuation, nightmare, curse, & escape prevention & wrap etc
                odds += (odds / 10); 
            if (gBattleMons[gBattlerTarget].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_SWITCH_LOCKED))
                odds += (odds / 10);
            if (gDisableStructs[gBattlerTarget].rechargeTimer)
                odds += (odds / 4);

            if (gLastUsedItem != ITEM_SAFARI_BALL)
            {
                if (gLastUsedItem == ITEM_MASTER_BALL)
                {
                    gBattleResults.usedMasterBall = TRUE;
                }
                else
                {
                    //used ultra ball previously as that was first ball id passed /excluding master ball
                    //don't really need to do that as already excludes lastitem masterball for condition
                    if (gBattleResults.catchAttempts[ItemIdToBallId(gLastUsedItem)] < 0xFF)
                        ++gBattleResults.catchAttempts[ItemIdToBallId(gLastUsedItem)];
                }
            }
            if (((odds > 254) || (gLastUsedItem == ITEM_MASTER_BALL))
                && gBattleResults.playerMonWasDamaged == TRUE) // mon caught  //successful capture
            {
                BtlController_EmitBallThrowAnim(0, BALL_3_SHAKES_SUCCESS);
                TryBattleFormChange(gBattlerTarget, FORM_CHANGE_END_BATTLE);
                MarkBattlerForControllerExec(gActiveBattler);
                gBattlescriptCurrInstr = BattleScript_ExpOnCatch;
                SetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_POKEBALL, &gLastUsedItem);
                if (CalculatePlayerPartyCount() == 6)
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0; // party full
                else
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1; //add to party
            }
            else if ((odds > 254) || (gLastUsedItem == ITEM_MASTER_BALL)) // mon caught  //successful capture
            {
                BtlController_EmitBallThrowAnim(0, BALL_3_SHAKES_SUCCESS);
                TryBattleFormChange(gBattlerTarget, FORM_CHANGE_END_BATTLE);
                MarkBattlerForControllerExec(gActiveBattler);
                gBattlescriptCurrInstr = BattleScript_SuccessBallThrow;
                SetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_POKEBALL, &gLastUsedItem);
                if (CalculatePlayerPartyCount() == 6)
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0; // party full
                else
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1; //add to party
            }
            else // mon may be caught, calculate shakes
            {
                u8 shakes;
                
        
                odds = Sqrt(Sqrt(16711680 / odds));
                odds = 1048560 / odds;
                for (shakes = 0; shakes < 4 && Random() < odds; ++shakes);
                //if (gLastUsedItem == ITEM_MASTER_BALL) // moved above for convenience
                //    shakes = BALL_3_SHAKES_SUCCESS; // why calculate the shakes before that check?
               // BtlController_EmitBallThrowAnim(0, shakes);
                //MarkBattlerForControllerExec(gActiveBattler);
                if (shakes == BALL_3_SHAKES_SUCCESS && gBattleResults.playerMonWasDamaged == TRUE) // mon caught, copy of the code above
                {
                    BtlController_EmitBallThrowAnim(0, BALL_3_SHAKES_SUCCESS);
                    TryBattleFormChange(gBattlerTarget, FORM_CHANGE_END_BATTLE);
                    MarkBattlerForControllerExec(gActiveBattler);
                    gBattlescriptCurrInstr = BattleScript_ExpOnCatch;
                    SetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_POKEBALL, &gLastUsedItem);
                    if (CalculatePlayerPartyCount() == 6)
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                }
                else if (shakes == BALL_3_SHAKES_SUCCESS) // mon caught, copy of the code above
                {
                    BtlController_EmitBallThrowAnim(0, BALL_3_SHAKES_SUCCESS);
                    TryBattleFormChange(gBattlerTarget, FORM_CHANGE_END_BATTLE);  //form change fix for mon caught i.e disguise etc.
                    MarkBattlerForControllerExec(gActiveBattler);
                    gBattlescriptCurrInstr = BattleScript_SuccessBallThrow;
                    SetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]], MON_DATA_POKEBALL, &gLastUsedItem);
                    if (CalculatePlayerPartyCount() == 6)
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                }
                else if (!(gBattleTypeFlags & BATTLE_TYPE_SAFARI))
                    //ok think my above functions messed up the else, so I had to explicitly define the fail conditions here

                    // not caught  think this is the part I need to change to replace shakes with miss or block
                { //based on brackets this should be if odds are  "less than 254"  and shake is guaranteed to fail,  meaning all fail.
                    u16 catchstate;
                    catchstate = Random() % 5; // while I prefer the idea that the only time its in the ball it stays in the ball. it may be more interesting game wise
                   // if (!gHasFetchedBall)
                     //   gLastUsedBall = gLastUsedItem;

                    if (catchstate == 0 || catchstate == 1)  { // to add a 3rd option where it can shake and fail normally.
                        BtlController_EmitBallThrowAnim(0, BALL_TRAINER_BLOCK);
                        MarkBattlerForControllerExec(gActiveBattler);
                        gBattlescriptCurrInstr = BattleScript_WildMonBallBlock;
                    }
                    if (catchstate == 2 || catchstate == 3) {
                        BtlController_EmitBallThrowAnim(0, BALL_GHOST_DODGE);
                        MarkBattlerForControllerExec(gActiveBattler);
                        gBattlescriptCurrInstr = BattleScript_NonGhost_BallDodge;
                    }
                    if (catchstate == 4 && shakes != BALL_3_SHAKES_SUCCESS) {//extra protection -_-
                        BtlController_EmitBallThrowAnim(0, shakes);
                        MarkBattlerForControllerExec(gActiveBattler);
                        gBattlescriptCurrInstr = BattleScript_ShakeBallThrow;   //normal catch shake mechanic in case I decide to do, but I want this to be least chosen option
                    }    // so insteaad of %3  I may do %5 and give the first 2 sates 2 success criteria (i.e 0,1 & 2,3   then have this only work on 4.  will have to test odds in effect)
                }
                else 
                {
                    BtlController_EmitBallThrowAnim(0, shakes);
                    MarkBattlerForControllerExec(gActiveBattler);
                    gBattlescriptCurrInstr = BattleScript_ShakeBallThrow;
                }//intend to be for safari, works
            } //dodge animation isn't working for safari mon, want to change to use base game animations
        }
    }
}

//oh I can do the take held item stuff here nice
static void atkF0_givecaughtmon(void) //useful if I set up alt storage,
{
    u16 heldItem = GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_HELD_ITEM);
    u16 clearItem = ITEM_NONE;
    if (GiveMonToPlayer(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]]) != MON_GIVEN_TO_PARTY) //if mon going to pc, is this codeblok
    {
        
        if (!ShouldShowBoxWasFullMessage())
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            StringCopy(gStringVar1, GetBoxNamePtr(VarGet(VAR_PC_BOX_TO_SEND_MON)));
            GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_NICKNAME, gStringVar2);
        }
        else
        {
            StringCopy(gStringVar1, GetBoxNamePtr(VarGet(VAR_PC_BOX_TO_SEND_MON))); // box the mon was sent to
            GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_NICKNAME, gStringVar2);
            StringCopy(gStringVar3, GetBoxNamePtr(GetPCBoxToSendMon())); //box the mon was going to be sent to
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        }
        if (FlagGet(FLAG_SYS_UPDATED_PC)) //will change to bill when get to that point
            ++gBattleCommunication[MULTISTRING_CHOOSER];

        if (heldItem != ITEM_NONE)
        {
            
            AddBagItem(heldItem, 1); //need battle message for this
            PREPARE_ITEM_BUFFER(gBattleTextBuff3, heldItem);
            GetItemName(gBattleTextBuff3, heldItem);
            PrepareStringBattle(STRINGID_CAUGHTMONDROPPEDITEM, gBattlerAttacker);
           // gBattlescriptCurrInstr = BattleScript_TakeItemfromCaughtMon; change think use buff3 and end with return 
        }
    }
    //gBattleResults.caughtMonSpecies = gBattleMons[gBattlerAttacker ^ BIT_SIDE].species; //thinkm this is why can't catch both mon? it uses side? is that why?
    GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_NICKNAME, gBattleResults.caughtMonNick);
    ++gBattlescriptCurrInstr;
}

static void atkF1_trysetcaughtmondexflags(void)
{
    u16 species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL);
    u32 personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, NULL);

    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT)) //if mon caught skip, 
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else    //otherwise trigger set caught
    {
        HandleSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT, personality);
        gBattleResults.caughtMonSpecies = gBattleMons[gBattlerAttacker ^ BIT_SIDE].species; //moved here to attempt use for speed up

        //may not need this since it is already in displaydexinfo via registermontopokedex?
        /*if (species > NATIONAL_SPECIES_COUNT
        && !(GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetFormSpeciesId(species, 0)), FLAG_GET_SEEN))
        && gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION
        || gBaseStats[SanitizeSpeciesId(species)].flags == SPECIES_FLAG_PRIMAL_REVERSION) //actually shouldn't need gender form here
        {
            HandleSetPokedexFlag(SpeciesToNationalPokedexNum(GetFormSpeciesId(species, 0)), FLAG_SET_SEEN, personality); //if catch form should set base form is seen so can navigate to dex page
        }*/
        gBattlescriptCurrInstr += 5;
    }
}

static void atkF2_displaydexinfo(void)
{
    u16 species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL);

    switch (gBattleCommunication[0])
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_WHITE);
        ++gBattleCommunication[0];
        break;
    case 1:
        if (!gPaletteFade.active)
        {
            FreeAllWindowBuffers();
            gBattleCommunication[TASK_ID] = DexScreen_RegisterMonToPokedex(species);
            ++gBattleCommunication[0];
        }
        break;
    case 2:
        if (!gPaletteFade.active
            && gMain.callback2 == BattleMainCB2
            && !gTasks[gBattleCommunication[TASK_ID]].isActive)
        {
            CpuFill32(0, (void *)VRAM, VRAM_SIZE);
            SetVBlankCallback(VBlankCB_Battle);
            ++gBattleCommunication[0];
        }
        break;
    case 3:
        InitBattleBgsVideo();
        LoadBattleTextboxAndBackground();
        gBattle_BG3_X = 0x100;
        ++gBattleCommunication[0];
        break;
    case 4:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            CreateMonPicSprite_HandleDeoxys(species,
                                            FALSE,
                                            gBattleMons[B_POSITION_OPPONENT_LEFT].personality,
                                            TRUE,
                                            120,
                                            64,
                                            0,
                                            0xFFFF);
            CpuFill32(0, gPlttBufferFaded, BG_PLTT_SIZE);
            BeginNormalPaletteFade(0x1FFFF, 0, 0x10, 0, RGB_BLACK);
            ShowBg(0);
            ShowBg(3);
            ++gBattleCommunication[0];
        }
        break;
    case 5:
        if (!gPaletteFade.active)
            ++gBattlescriptCurrInstr;
        break;
    }
}

void HandleBattleWindow(u8 xStart, u8 yStart, u8 xEnd, u8 yEnd, u8 flags)
{
    s32 destY, destX;
    u16 var = 0;

    for (destY = yStart; destY <= yEnd; ++destY)
    {
        for (destX = xStart; destX <= xEnd; ++destX)
        {
            if (destY == yStart)
            {
                if (destX == xStart)
                    var = 0x1022;
                else if (destX == xEnd)
                    var = 0x1024;
                else
                    var = 0x1023;
            }
            else if (destY == yEnd)
            {
                if (destX == xStart)
                    var = 0x1028;
                else if (destX == xEnd)
                    var = 0x102A;
                else
                    var = 0x1029;
            }
            else
            {
                if (destX == xStart)
                    var = 0x1025;
                else if (destX == xEnd)
                    var = 0x1027;
                else
                    var = 0x1026;
            }
            if (flags & WINDOW_CLEAR)
                var = 0;
            if (flags & WINDOW_x80)
                CopyToBgTilemapBufferRect_ChangePalette(1, &var, destX, destY, 1, 1, 0x11);
            else
                CopyToBgTilemapBufferRect_ChangePalette(0, &var, destX, destY, 1, 1, 0x11);
        }
    }
    CopyBgTilemapBufferToVram(1);
}

void BattleCreateYesNoCursorAt(void)
{
    u16 src[2];

    src[0] = 1;
    src[1] = 2;
    CopyToBgTilemapBufferRect_ChangePalette(0, src, 0x18, 9 + (2 * gBattleCommunication[1]), 1, 2, 0x11);
    CopyBgTilemapBufferToVram(0);
}

void BattleDestroyYesNoCursorAt(void)
{
    u16 src[2];

    src[0] = 32;
    src[1] = 32;
    CopyToBgTilemapBufferRect_ChangePalette(0, src, 0x18, 9 + (2 * gBattleCommunication[1]), 1, 2, 0x11);
    CopyBgTilemapBufferToVram(0);
}

static void atkF3_trygivecaughtmonnick(void)
{
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        HandleBattleWindow(0x17, 8, 0x1D, 0xD, 0);
        BattlePutTextOnWindow(gText_BattleYesNoChoice, 0xE);
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[CURSOR_POSITION] = 0;
        BattleCreateYesNoCursorAt();
        break;
    case 1:
        if (JOY_NEW(DPAD_UP) && gBattleCommunication[CURSOR_POSITION] != 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 0;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(DPAD_DOWN) && gBattleCommunication[CURSOR_POSITION] == 0)
        {
            PlaySE(SE_SELECT);
            BattleDestroyYesNoCursorAt();
            gBattleCommunication[CURSOR_POSITION] = 1;
            BattleCreateYesNoCursorAt();
        }
        if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            if (gBattleCommunication[CURSOR_POSITION] == 0)
            {
                ++gBattleCommunication[MULTIUSE_STATE];
                BeginFastPaletteFade(3);
            }
            else
            {
                gBattleCommunication[MULTIUSE_STATE] = 4;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            gBattleCommunication[MULTIUSE_STATE] = 4;
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_NICKNAME, gBattleStruct->caughtMonNick);
            FreeAllWindowBuffers();
            DoNamingScreen(NAMING_SCREEN_CAUGHT_MON, gBattleStruct->caughtMonNick,
                           GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_SPECIES),
                           GetMonGender(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]]),
                           GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_PERSONALITY, NULL),
                           BattleMainCB2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 3:
        if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
        {
            SetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker ^ BIT_SIDE]], MON_DATA_NICKNAME, gBattleStruct->caughtMonNick);
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        }
        break;
    case 4:
        if (CalculatePlayerPartyCount() == PARTY_SIZE)
            gBattlescriptCurrInstr += 5;
        else
            gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
        break;
    }
}

static void atkF4_subattackerhpbydmg(void)
{
    gBattleMons[gBattlerAttacker].hp -= gBattleMoveDamage;
    ++gBattlescriptCurrInstr;
}

static void atkF5_removeattackerstatus1(void) //this doesn't appear to be used anywhere?
{
    gBattleMons[gBattlerAttacker].status1 = 0;
    ++gBattlescriptCurrInstr;
}

static void atkF6_finishaction(void)
{
    gCurrentActionFuncId = B_ACTION_FINISHED;
}

static void atkF7_finishturn(void)
{
    gCurrentActionFuncId = B_ACTION_FINISHED;
    gCurrentTurnActionNumber = gBattlersCount;
}

//vsonic need remember to add to ai decision tree
//since so niche decide keep at 50% heal
//potentially make it only work if used on floating mon?
//would make it the only heal move that is on a cooldown tho...
//plus w flying change you're already losing the flying type evasion bonus
//hmm ok I like idea of it only works if floating since idea is you're meant to rest on the ground
//(will make it be roost timer not floating)
//then just do an end turn to heal a small portion each turn you're
//in roost status
//making move work only if floating mon/not grounded is too difficult,
//instead just make sure to only give to mon  that can float typically
//or birds I guess
static void atkF8_setroost(void) { //actually I don't like this type change idea so not gonna do it.
    CMD_ARGS(const u8* failInstr);
    if (gDisableStructs[gBattlerAttacker].RoostTimer == 0) //!IsBattlerGrounded(gBattlerTarget)
    {
        //u16 virtue = Random() % 4; //had to make start value timer and set equal so they use the same value without recalc
        gDisableStructs[gBattlerAttacker].RoostTimer = 4; //setting timer to 4, should give 3 full turns
        //gDisableStructs[gBattlerAttacker].RoostTimerStartValue = 0;
        //u8 timervalue = gDisableStructs[gBattlerAttacker].RoostTimer && gDisableStructs[gBattlerAttacker].RoostTimerStartValue;

        
        // gDisableStructs[gBattlerAttacker].RoostTimer = gDisableStructs[gBattlerAttacker].RoostTimerStartValue += virtue;
        //gDisableStructs[gBattlerAttacker].RoostTimer += virtue;
        //REMOVED random effect
        //ok made slight adjustment here, I think since its starts at zero, this should be enough that timer is always increased when setting roost
        //which shoud give a nice balance to repeatedly using the move.

        //should be set timer value, and if flag not set, set flag
        if (!(gBattleResources->flags->flags[gBattlerAttacker] & RESOURCE_FLAG_ROOST)) //check if this means flag not set
            gBattleResources->flags->flags[gBattlerAttacker] |= RESOURCE_FLAG_ROOST;  //why do I need this if I have a timer? but potentially use for trenchrun

        //need to come up with adjustment to ensure subsequent uses of roost can't give
        //a value lower than what's already on the timer.

        //think I can use += virtue to do what I want so if timer isn't 0, and roost is set,
        //the value gets added to time remaining.

        /*else if (gDisableStructs[gBattlerAttacker].RoostTimer && gDisableStructs[gBattlerAttacker].RoostTimerStartValue != 0)
            timervalue += virtue;*/


        // then check if need to update battlescript to for a loop like gravity
        //need make change for flying type 1 || type 2 & resource flag roost

        //actually don't need to change anything, forgot I removed round to flying immunity
        //so when ground hits, it should just be treated as a normally effective attack without interfering

        /*
        // Pure flying type.
        if (gBattleMons[gBattlerAttacker].type1 == TYPE_FLYING && gBattleMons[gBattlerAttacker].type2 == TYPE_FLYING)
        {
            gBattleStruct->roostTypes[gBattlerAttacker][0] = TYPE_FLYING;
            gBattleStruct->roostTypes[gBattlerAttacker][1] = TYPE_FLYING;
            gBattleStruct->roostTypes[gBattlerAttacker][2] = TYPE_FLYING;
            SET_BATTLER_TYPE(gBattlerAttacker, TYPE_NORMAL);
        }
        // Dual Type with Flying Type.
        else if ((gBattleMons[gBattlerAttacker].type1 == TYPE_FLYING && gBattleMons[gBattlerAttacker].type2 != TYPE_FLYING)
            || (gBattleMons[gBattlerAttacker].type2 == TYPE_FLYING && gBattleMons[gBattlerAttacker].type1 != TYPE_FLYING))
        {
            gBattleStruct->roostTypes[gBattlerAttacker][0] = gBattleMons[gBattlerAttacker].type1;
            gBattleStruct->roostTypes[gBattlerAttacker][1] = gBattleMons[gBattlerAttacker].type2;
            if (gBattleMons[gBattlerAttacker].type1 == TYPE_FLYING)
                gBattleMons[gBattlerAttacker].type1 = TYPE_MYSTERY;
            if (gBattleMons[gBattlerAttacker].type2 == TYPE_FLYING)
                gBattleMons[gBattlerAttacker].type2 = TYPE_MYSTERY;
        }
        // Non-flying type.
        else if (!IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_FLYING))
        {*/
        //gBattleStruct->roostTypes[gBattlerAttacker][0] = gBattleMons[gBattlerAttacker].type1;
        //gBattleStruct->roostTypes[gBattlerAttacker][1] = gBattleMons[gBattlerAttacker].type2;
        gBattlescriptCurrInstr = cmd->nextInstr; 
    }
    else
        gBattlescriptCurrInstr = cmd->failInstr;

    
} //should have effect of doing pretty much nothing

static void atkF9_mondamaged(void) //edited based on recommendation from mcgriffin & egg (aka dizzyegg)
{
    //screw it. can't make it work when enemy is damaged probably something to do with how playermonwasdamaged works
    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER && gBattleMoveDamage > 0)
        gBattleResults.playerMonWasDamaged = TRUE; //besides that still makes good sense, you only grow when your body exerts itself/exeriences pain
       
    ++gBattlescriptCurrInstr; //without this script doesn't continue stays stuck on this
    //also leanred that order matters for stacked ifs or else ifs, since it will
    //take the first true statement for either if or else if.
    //..i think, need to read logic
    

    //plus that would avoid any confusion from combining and with else statements
}

static void atkFA_sethealblock(void) {
    if (gSideStatuses[GET_BATTLER_SIDE(gBattlerTarget)] & SIDE_STATUS_HEAL_BLOCK)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK; // apply status to target and set side status   //don't think i need this
        gSideStatuses[GET_BATTLER_SIDE(gBattlerTarget)] |= SIDE_STATUS_HEAL_BLOCK;
        gSideTimers[GET_BATTLER_SIDE(gBattlerTarget)].healBlockTimer = 5;
        gSideTimers[GET_BATTLER_SIDE(gBattlerTarget)].healBlockBattlerId = gBattlerTarget;

        //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK;
        //gDisableStructs[gBattlerTarget].healBlockTimer = 5;
        gBattlescriptCurrInstr += 5;
    }//should work but need test, effect I want is a side status that blocks healing moves & items, but 
}//with clense effects are able to clear the status from individual mon, without removing the entire side status
//unless used defog
//new idea, make side status heal block, apply status 3 heal block on switch in, long as timer isn't 0
//this would let normal moves clear the status separately from the full side status
//just need to set it up so side status timer running out would clear side status and 
//staus 3 heal block from any mon on side.

/*if (gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_SAFEGUARD)
    {
        gMoveResultFlags |= MOVE_RESULT_MISSED;
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
    }
    else
    {
        gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] |= SIDE_STATUS_SAFEGUARD;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].safeguardTimer = 5;
        gSideTimers[GET_BATTLER_SIDE(gBattlerAttacker)].safeguardBattlerId = gBattlerAttacker;
        gBattleCommunication[MULTISTRING_CHOOSER] = 5;
    }*/

static void atkFB_setgravity(void) {
    if (gFieldStatuses & STATUS_FIELD_GRAVITY)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gFieldStatuses |= STATUS_FIELD_GRAVITY;
        gFieldTimers.gravityTimer = 5;
        gBattlescriptCurrInstr += 5;
    }
}

static void atkFC_setmiracle_eye(void) {
    if (!(gStatuses3[gBattlerTarget] & STATUS3_MIRACLE_EYED))
    {
        gStatuses3[gBattlerTarget] |= STATUS3_MIRACLE_EYED;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

static void atkFD_settailwind(void) {
    u8 side = GetBattlerSide(gBattlerAttacker);

    if (!(gSideStatuses[side] & SIDE_STATUS_TAILWIND))
    {
        gSideStatuses[side] |= SIDE_STATUS_TAILWIND;
        gSideTimers[side].tailwindBattlerId = gBattlerAttacker;
        gSideTimers[side].tailwindTimer = 3;
        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

/*gSideStatuses[GET_BATTLER_SIDE(gBattlerTarget)] |= SIDE_STATUS_HEAL_BLOCK;
        gSideTimers[GET_BATTLER_SIDE(gBattlerTarget)].healBlockTimer = 5;
        gSideTimers[GET_BATTLER_SIDE(gBattlerTarget)].healBlockBattlerId = gBattlerTarget;
        
        STATUS3_EMBARGO*/

static void atkFE_setembargo(void) {
    if (gSideStatuses[GET_BATTLER_SIDE(gBattlerTarget)] & SIDE_STATUS_EMBARGO)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gSideStatuses[GET_BATTLER_SIDE(gBattlerTarget)] |= SIDE_STATUS_EMBARGO;
        gSideTimers[GET_BATTLER_SIDE(gBattlerTarget)].embargoTimer = 5;
        gBattlescriptCurrInstr += 5;
    }
}

 //Lunos said bs caps at 0xFF has 1 byte limit, so to get aroudn that pret used call native, can call as many functions as they want through this command
 //replace all commands above this one with call native logic
static void atkFF_callnative(void) 
{
    CMD_ARGS(void (*func)(void));
    void (*func)(void) = cmd->func;
    func();
}

//native functions start    //shuold work but still need to finish adding nativeargs
//port form stuff
void BS_HandleMegaEvolution(void)
{
    NATIVE_ARGS(u8 battler, u8 caseId);

    u8 battler = GetBattlerForBattleScript(cmd->battler);
    HandleScriptMegaPrimalBurst(cmd->caseId, battler, HANDLE_TYPE_MEGA_EVOLUTION);
    gBattlescriptCurrInstr = cmd->nextInstr;
}

void BS_HandlePrimalReversion(void)
{
    NATIVE_ARGS(u8 battler, u8 caseId);

    u8 battler = GetBattlerForBattleScript(cmd->battler);
    HandleScriptMegaPrimalBurst(cmd->caseId, battler, HANDLE_TYPE_PRIMAL_REVERSION);
    gBattlescriptCurrInstr = cmd->nextInstr;
}

void BS_HandleUltraBurst(void)
{
    NATIVE_ARGS(u8 battler, u8 caseId);

    u8 battler = GetBattlerForBattleScript(cmd->battler);
    HandleScriptMegaPrimalBurst(cmd->caseId, battler, HANDLE_TYPE_ULTRA_BURST);
    gBattlescriptCurrInstr = cmd->nextInstr;
}

//copy from EE believe this just handles recording
//battler/ability data? doesn't do affect itself
//guess simplifies logic within case block
void BS_TryWindRiderPower(void)
{
    NATIVE_ARGS(u8 battler, const u8 *failInstr);

    u32 battler = GetBattlerForBattleScript(cmd->battler);
    u16 ability = GetBattlerAbility(battler);
    if (GetBattlerSide(battler) == GetBattlerSide(gBattlerAttacker)
        && (ability == ABILITY_WIND_RIDER || ability == ABILITY_WIND_POWER))
    {
        gLastUsedAbility = ability;
        RecordAbilityBattle(battler, gLastUsedAbility);
        gBattlerAbility = gBattleScripting.battler = battler;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    else
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
}

void BS_modifybattlerstatstage(void)
{

}

void BS_setstickyweb(void) 
{
    NATIVE_ARGS(const u8 *ptr);
    u8 targetSide = GetBattlerSide(gBattlerTarget);
    if (gSideStatuses[targetSide] & SIDE_STATUS_STICKY_WEB)
    {
        gBattlescriptCurrInstr = cmd->ptr;
    }
    else
    {
        gSideStatuses[targetSide] |= SIDE_STATUS_STICKY_WEB;
        gSideTimers[targetSide].stickyWebAmount = 1;
        gBattleStruct->stickyWebUser = gBattlerAttacker;    // For Mirror Armor
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

void BS_settoxicspikes(void) 
{
    NATIVE_ARGS(const u8 *ptr);
    u8 targetSide = GetBattlerSide(gBattlerTarget);
    if (gSideTimers[targetSide].toxicSpikesAmount >= 2)
    {
        gBattlescriptCurrInstr = cmd->ptr;
    }
    else
    {
        gSideTimers[targetSide].toxicSpikesAmount++;
        gSideStatuses[targetSide] |= SIDE_STATUS_TOXIC_SPIKES;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

void BS_TryHealPulse(void)
{
    NATIVE_ARGS(const u8 *failInstr);

    if (BATTLER_MAX_HP(gBattlerTarget))
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
    else
    {
        if (GetBattlerAbility(gBattlerAttacker) == ABILITY_MEGA_LAUNCHER && gBattleMoves[gCurrentMove].flags & FLAG_MEGA_LAUNCHER_BOOST)
            //gBattleMoveDamage = -(GetNonDynamaxMaxHP(gBattlerTarget) * 75 / 100);
            gBattleMoveDamage = -(75 * gBattleMons[gBattlerTarget].maxHP) / 100;
        else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && gCurrentMove == MOVE_FLORAL_HEALING)
            //gBattleMoveDamage = -(GetNonDynamaxMaxHP(gBattlerTarget) * 2 / 3);
            gBattleMoveDamage = -(20 * gBattleMons[gBattlerTarget].maxHP) / 30;
        else
            //gBattleMoveDamage = -(GetNonDynamaxMaxHP(gBattlerTarget) / 3);
            gBattleMoveDamage = -gBattleMons[gBattlerTarget].maxHP / 3;

        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = -1;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

void BS_TrySoak(void)
{
    NATIVE_ARGS(const u8 *failInstr);

    if (gBattleMons[gBattlerTarget].type1 == gBattleMoves[gCurrentMove].argument && gBattleMons[gBattlerTarget].type2 == gBattleMoves[gCurrentMove].argument)
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
    else
    {
        SET_BATTLER_TYPE_PROTEAN(gBattlerTarget, gBattleMoves[gCurrentMove].argument);
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

void BS_setgastroacid(void)
{
    NATIVE_ARGS(const u8 *ptr);
    if (IsGastroAcidBannedAbility(gBattleMons[gBattlerTarget].ability))
    {
        gBattlescriptCurrInstr = cmd->ptr;
    }
    else
    {
        if (gBattleMons[gBattlerTarget].ability == ABILITY_NEUTRALIZING_GAS)
            gSpecialStatuses[gBattlerTarget].neutralizingGasRemoved = TRUE;

        if (gBattleMons[gBattlerTarget].ability == ABILITY_IMMUTABLE_WIND)
            gSpecialStatuses[gBattlerTarget].neutralizingGasRemoved = TRUE;

        else if (gBattleMons[gBattlerTarget].ability == ABILITY_STENCH)
            gSpecialStatuses[gBattlerTarget].stenchRemoved = TRUE;

        gStatuses3[gBattlerTarget] |= STATUS3_GASTRO_ACID;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

void BS_jumpifateberry(void) //for belch,
{
    NATIVE_ARGS(u8 battler, const u8 *jumpInstr);
    u32 battler = GetBattlerForBattleScript(cmd->battler);

    if (gBattleStruct->ateBerry[GetBattlerSide(battler)] & gBitTable[gBattlerPartyIndexes[battler]])
        gBattlescriptCurrInstr = cmd->jumpInstr;
    else
        gBattlescriptCurrInstr = cmd->nextInstr;
}

static void HandleRoomMove(u32 statusFlag, u8 *timer, u8 stringId)
{
    if (gFieldStatuses & statusFlag)
    {
        gFieldStatuses &= ~(statusFlag);
        *timer = 0;
        gBattleCommunication[MULTISTRING_CHOOSER] = stringId + 1;
    }
    else
    {
        gFieldStatuses |= statusFlag;
        *timer = 5;
        gBattleCommunication[MULTISTRING_CHOOSER] = stringId;
    }
}

void BS_setroom(void) {
    NATIVE_ARGS();
    switch (gBattleMoves[gCurrentMove].effect)
    {
    case EFFECT_TRICK_ROOM:
        HandleRoomMove(STATUS_FIELD_TRICK_ROOM, &gFieldTimers.trickRoomTimer, 0);
        break;
    case EFFECT_WONDER_ROOM:
        HandleRoomMove(STATUS_FIELD_WONDER_ROOM, &gFieldTimers.wonderRoomTimer, 2);
        break;
    case EFFECT_MAGIC_ROOM:
        HandleRoomMove(STATUS_FIELD_MAGIC_ROOM, &gFieldTimers.magicRoomTimer, 4);
        break;
    default:
        gBattleCommunication[MULTISTRING_CHOOSER] = 6;
        break;
    }
    gBattlescriptCurrInstr = cmd->nextInstr;
}

void BS_setstealthrock(void) { //check where rest of spikes handled
    NATIVE_ARGS(const u8 *ptr);
    u8 targetSide = GetBattlerSide(gBattlerTarget);
    if (gSideStatuses[targetSide] & SIDE_STATUS_STEALTH_ROCK)
    {
        gBattlescriptCurrInstr = cmd->ptr;
    }
    else
    {
        gSideStatuses[targetSide] |= SIDE_STATUS_STEALTH_ROCK;
        gSideTimers[targetSide].stealthRockAmount = 1;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

//used in function that already confirms ability,
//use in conjunction w ability check to confirm,
//mon should
bool32 IsStallActive(u8 battler)
{
    u16 move = gBattleMons[battler].moves[*(gBattleStruct->chosenMovePositions + battler)];

    //changed from not power 0, to not status better condition
    if (GetBattlerAbility(battler) == ABILITY_STALL
    && !IS_MOVE_STATUS(move)) 
        return TRUE;
        
    return FALSE;

}

//added back sound exclusion for more nuance
bool32 DoesSubstituteBlockMove(u8 battlerAtk, u8 battlerDef, u32 move) //sound bypass is dumb, guess now it works how I want
{
    if (!(gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE))
        return FALSE;
    else if (gBattleMoves[move].flags & FLAG_SOUND)
        return FALSE;
    else if (gBattleMoves[move].flags & FLAG_HIT_IN_SUBSTITUTE)
        return FALSE;
    else if (GetBattlerAbility(battlerAtk) == ABILITY_INFILTRATOR)
        return FALSE;
    else
        return TRUE;
}

//test with doubles, keep an eye on
bool32 DoesDisguiseBlockMove(u8 battlerAtk, u8 battlerDef, u32 move) //plan add rocky helm rough skin passive dmg to things that can break /vsonic
{
    if (GetBattlerAbility(battlerDef) != ABILITY_DISGUISE
        //|| gBattleMons[battlerDef].species != SPECIES_MIMIKYU   //since species transforms to busted afterwards, this is line that makes it one time only
        || (gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[battlerDef]][GetBattlerSide(battlerDef)] == TRUE && gBattleMons[battlerDef].ability == ABILITY_DISGUISE)
        || gBattleMons[battlerDef].status2 & STATUS2_TRANSFORMED //^new change seems to work without species, but need check w double batte ensure not just spot 0
        //|| gBattleMoves[move].power == 0      /need/want it to track with the mon as it moves so if I switch it, the status still applies,
        || IS_MOVE_STATUS(move)                 //hmm I guess simple as look into status then since status1 stays with mon, no matter where switch
        || gHitMarker & HITMARKER_IGNORE_DISGUISE
        || gProtectStructs[battlerAtk].confusionSelfDmg) //should allow conufusion dmg through without breaking form -works, just makes more sense, 
        return FALSE; //its not the same as substitute where its a different object, disguise is part of the mon
    else
        return TRUE;
} //seems this is main logic for ability effect

//may not need sub block? don't really need it but using will save time
//vsonic need update correctly
void BS_jumpifsubstituteblocks(void) 
{
     NATIVE_ARGS(const u8 *jumpInstr);
    if (DoesSubstituteBlockMove(gBattlerAttacker, gBattlerTarget, gCurrentMove))
        gBattlescriptCurrInstr = cmd->jumpInstr;
    else
        gBattlescriptCurrInstr = cmd->nextInstr;
}

//take weather flag from script make value u32 to ensure no miss
//but values are u16 as of now,
//used for adapation of wind rider to work w sandstorm

void BS_jumpifnotweatheraffected(void) 
{
     NATIVE_ARGS(u8 battler, u32 weatherflags, const u8 *jumpInstr);
    if (IsBattlerWeatherAffected(cmd->battler, cmd->weatherflags))
        gBattlescriptCurrInstr = cmd->nextInstr;
    else
        gBattlescriptCurrInstr = cmd->jumpInstr;
}

//setup for new wind power effect to make compatible with base script
//and doesn't activate wind rider (which would cause attack increase each turn)
void BS_endturnSkipWindRiderActivation(void)
{
    NATIVE_ARGS(u8 battler, const u8 *jumpInstr);
    u8 battler = cmd->battler;
    u16 ability = GetBattlerAbility(battler);
    
    if (gCurrentTurnActionNumber >= gBattlersCount) // everyone did their actions, turn finished
    {
        if (ability == ABILITY_WIND_RIDER)
            gBattlescriptCurrInstr = cmd->jumpInstr;
    }

    gBattlescriptCurrInstr = cmd->nextInstr;

}


//for those that want it
void BS_trainerslideout(void) 
{
    NATIVE_ARGS(u8 param); 

    //gActiveBattler = GetBattlerAtPosition(gBattlescriptCurrInstr[1]);
    gActiveBattler = GetBattlerAtPosition(cmd->param);
    BtlController_EmitTrainerSlideBack(0);
    MarkBattlerForControllerExec(gActiveBattler);

    gBattlescriptCurrInstr = cmd->nextInstr;
} //aparently I just completely forgot to rename this??

static const u16 sTelekinesisBanList[] =
{
    SPECIES_DIGLETT,
    SPECIES_DUGTRIO,
    SPECIES_DIGLETT_ALOLAN,
    SPECIES_DUGTRIO_ALOLAN,
    SPECIES_SANDYGAST,
    SPECIES_PALOSSAND,
    SPECIES_GENGAR_MEGA,
};

bool32 IsTelekinesisBannedSpecies(u16 species)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sTelekinesisBanList); i++)
    {
        if (species == sTelekinesisBanList[i])
            return TRUE;
    }
    return FALSE;
}

//extra effect only trigger if has an argument
//no idea why didn't think to do that in the first place
void BS_setargumenteffectwithchance(void) //different effect for in hit, where actually setting effect
{
    NATIVE_ARGS();
    //if (gBattleMoves[gCurrentMove].effect != EFFECT_TWO_TYPED_MOVE)
    if (gBattleMoves[gCurrentMove].effect != EFFECT_TWO_TYPED_MOVE                
        && gBattleMoves[gCurrentMove].effect != EFFECT_LOSETYPE_HIT
        && gBattleMoves[gCurrentMove].argument)
    {
        gBattleScripting.moveEffect = gBattleMoves[gCurrentMove].argument; //potentially need make argument field for bs. as well vsonic
        atk15_setmoveeffectwithchance(); //looks weird but believe its necessary with my setup of argumenttomoveeffect
    }   
    else 
        gBattlescriptCurrInstr = cmd->nextInstr;
    //attempt remove this see what happens,
    //if its causing a skip,
    //the function it calls should have all logic needed to move script forward?
}//HAH that was literally it, I was skipping too far forward

//will use this replace arguemtn logic move effect set function later
/*void BS_setadditionaleffects(void)
{
    NATIVE_ARGS();

    if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
    {
        if (gMovesInfo[gCurrentMove].numAdditionalEffects > gBattleStruct->additionalEffectsCounter)
        {
            u32 percentChance;
            const struct AdditionalEffect *additionalEffect = &gMovesInfo[gCurrentMove].additionalEffects[gBattleStruct->additionalEffectsCounter];
            const u8 *currentPtr = gBattlescriptCurrInstr;

            // Various checks for if this move effect can be applied this turn
            if (CanApplyAdditionalEffect(additionalEffect))
            {
                percentChance = CalcSecondaryEffectChance(gBattlerAttacker, GetBattlerAbility(gBattlerAttacker), additionalEffect);

                // Activate effect if it's primary (chance == 0) or if RNGesus says so
                if ((percentChance == 0) || RandomPercentage(RNG_SECONDARY_EFFECT + gBattleStruct->additionalEffectsCounter, percentChance))
                {
                    gBattleScripting.moveEffect = additionalEffect->moveEffect | (MOVE_EFFECT_AFFECTS_USER * (additionalEffect->self));

                    SetMoveEffect(
                        percentChance == 0, // a primary effect
                        percentChance >= 100 // certain to happen
                    );
                }
            }

            // Move script along if we haven't jumped elsewhere
            if (gBattlescriptCurrInstr == currentPtr)
                gBattlescriptCurrInstr = cmd->nextInstr;

            // Call setadditionaleffects again in the case of a move with multiple effects
            gBattleStruct->additionalEffectsCounter++;
            if (gMovesInfo[gCurrentMove].numAdditionalEffects > gBattleStruct->additionalEffectsCounter)
                gBattleScripting.moveEffect = MOVE_EFFECT_CONTINUE;
            else
                gBattleScripting.moveEffect = gBattleStruct->additionalEffectsCounter = 0;
        }
        else
        {
            gBattleScripting.moveEffect = 0;
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
    }
    else
    {
        gBattleScripting.moveEffect = 0;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }

    gBattleScripting.multihitMoveEffect = 0;
}
*/

void BS_settelekinesis(void) {

    if (gStatuses3[gBattlerTarget] & (STATUS3_SMACKED_DOWN)
        && !IsTelekinesisBannedSpecies(gBattleMons[gBattlerTarget].species))
    {
        gStatuses3[gBattlerTarget] &= ~(STATUS3_SMACKED_DOWN);
        gStatuses3[gBattlerTarget] |= STATUS3_TELEKINESIS;
        gDisableStructs[gBattlerTarget].telekinesisTimer = 3;
        gBattlescriptCurrInstr += 5;
    }

    if (gStatuses3[gBattlerTarget] & (STATUS3_TELEKINESIS | STATUS3_ROOTED)
        || gFieldStatuses & STATUS_FIELD_GRAVITY
        || IsTelekinesisBannedSpecies(gBattleMons[gBattlerTarget].species))
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {
        gStatuses3[gBattlerTarget] |= STATUS3_TELEKINESIS;
        gDisableStructs[gBattlerTarget].telekinesisTimer = 3;
        gBattlescriptCurrInstr += 5;
    }
}

void BS_swapstatstages(void) {
    u8 statId = T1_READ_8(gBattlescriptCurrInstr + 1);
    s8 atkStatStage = gBattleMons[gBattlerAttacker].statStages[statId];
    s8 defStatStage = gBattleMons[gBattlerTarget].statStages[statId];

    gBattleMons[gBattlerAttacker].statStages[statId] = defStatStage;
    gBattleMons[gBattlerTarget].statStages[statId] = atkStatStage;

    gBattlescriptCurrInstr += 2;
}

void BS_averagestats(void) {
    u8 statId = T1_READ_8(gBattlescriptCurrInstr + 1);
    u16 atkStat = *(u16*)((&gBattleMons[gBattlerAttacker].attack) + (statId - 1));
    u16 defStat = *(u16*)((&gBattleMons[gBattlerTarget].attack) + (statId - 1));
    u16 average = (atkStat + defStat) / 2;

    *(u16*)((&gBattleMons[gBattlerAttacker].attack) + (statId - 1)) = average;
    *(u16*)((&gBattleMons[gBattlerTarget].attack) + (statId - 1)) = average;

    gBattlescriptCurrInstr += 2;
}

void BS_jumpifoppositegenders(void) {
    u32 atkGender = GetGenderFromSpeciesAndPersonality(gBattleMons[gBattlerAttacker].species, gBattleMons[gBattlerAttacker].personality);
    u32 defGender = GetGenderFromSpeciesAndPersonality(gBattleMons[gBattlerTarget].species, gBattleMons[gBattlerTarget].personality);

    if ((atkGender == MON_MALE && defGender == MON_FEMALE) || (atkGender == MON_FEMALE && defGender == MON_MALE))
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    else
        gBattlescriptCurrInstr += 5;
}

void BS_trygetbaddreamstarget(void) {
    u8 badDreamsMonSide = GetBattlerSide(gBattlerAttacker);
    for (; gBattlerTarget < gBattlersCount; gBattlerTarget++)
    {
        if (GetBattlerSide(gBattlerTarget) == badDreamsMonSide)
            continue;
        if ((gBattleMons[gBattlerTarget].status1 & STATUS1_SLEEP || GetBattlerAbility(gBattlerTarget) == ABILITY_COMATOSE)
            && IsBattlerAlive(gBattlerTarget))
            break;
    }

    if (gBattlerTarget >= gBattlersCount)
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    else
        gBattlescriptCurrInstr += 5;
}

void BS_tryworryseed(void) {
    NATIVE_ARGS(const u8* failInstr);

    switch (GetBattlerAbility(gBattlerTarget))
    {
    case ABILITY_INSOMNIA:
    case ABILITY_MULTITYPE:
    case ABILITY_TRUANT:
    case ABILITY_STANCE_CHANGE:
    case ABILITY_DISGUISE:
        gBattlescriptCurrInstr = cmd->failInstr;
        break;
    default:
        gBattleMons[gBattlerTarget].ability = ABILITY_INSOMNIA;
        gBattlescriptCurrInstr = cmd->nextInstr;
        break;
    }
}

void BS_metalburstdamagecalculator(void) {
    u8 sideAttacker = GetBattlerSide(gBattlerAttacker);
    u8 sideTarget = 0; //vsonic need double check if this is what should be

    if (gProtectStructs[gBattlerAttacker].physicalDmg
        && sideAttacker != (sideTarget = GetBattlerSide(gProtectStructs[gBattlerAttacker].physicalBattlerId))
        && gBattleMons[gProtectStructs[gBattlerAttacker].physicalBattlerId].hp)
    {
        gBattleMoveDamage = gProtectStructs[gBattlerAttacker].physicalDmg * 150 / 100;

        if (gSideTimers[sideTarget].followmeTimer && gBattleMons[gSideTimers[sideTarget].followmeTarget].hp)
            gBattlerTarget = gSideTimers[sideTarget].followmeTarget;
        else
            gBattlerTarget = gProtectStructs[gBattlerAttacker].physicalBattlerId;

        gBattlescriptCurrInstr += 5;
    }
    else if (gProtectStructs[gBattlerAttacker].specialDmg
        && sideAttacker != (sideTarget = GetBattlerSide(gProtectStructs[gBattlerAttacker].specialBattlerId))
        && gBattleMons[gProtectStructs[gBattlerAttacker].specialBattlerId].hp)
    {
        gBattleMoveDamage = gProtectStructs[gBattlerAttacker].specialDmg * 150 / 100;

        if (gSideTimers[sideTarget].followmeTimer && gBattleMons[gSideTimers[sideTarget].followmeTarget].hp)
            gBattlerTarget = gSideTimers[sideTarget].followmeTarget;
        else
            gBattlerTarget = gProtectStructs[gBattlerAttacker].specialBattlerId;

        gBattlescriptCurrInstr += 5;
    }
    else
    {
        gSpecialStatuses[gBattlerAttacker].ppNotAffectedByPressure = 1;
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
}

void BS_setattackerstatus3(void) {
    u32 flags = T1_READ_32(gBattlescriptCurrInstr + 1);

    if (gStatuses3[gBattlerAttacker] & flags)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 5);
    }
    else
    {
        gStatuses3[gBattlerAttacker] |= flags;
        if (flags & STATUS3_MAGNET_RISE)
            gDisableStructs[gBattlerAttacker].magnetRiseTimer = 5;
        if (flags & STATUS3_LASER_FOCUS)
            gDisableStructs[gBattlerAttacker].laserFocusTimer = 2;
        gBattlescriptCurrInstr += 9;
    }
}

void BS_setiondeluge(void) //removed under_score in name seemed to prevent use
{ //since battlescript alrady sets field effect, just sets timer here
    NATIVE_ARGS();
    gFieldTimers.IonDelugeTimer = 4;
    gBattlescriptCurrInstr = cmd->nextInstr;
}

void BS_setuserstatus3(void)
{
    u32 flags = T1_READ_32(gBattlescriptCurrInstr + 1);

    if (gStatuses3[gBattlerAttacker] & flags)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 5);
    }
    else
    {
        gStatuses3[gBattlerAttacker] |= flags;
        if (flags & STATUS3_MAGNET_RISE)
            gDisableStructs[gBattlerAttacker].magnetRiseTimer = 5;
        if (flags & STATUS3_LASER_FOCUS)
            gDisableStructs[gBattlerAttacker].laserFocusTimer = 2;
        gBattlescriptCurrInstr += 9;
    }

}

//replacing w timer instead
void BS_SetTrenchRun(void)
{
    NATIVE_ARGS(const u8 *ptr);

    if (gDisableStructs[gBattlerAttacker].trenchRunTimer)
    {
        gBattlescriptCurrInstr = cmd->ptr;
    }
    else
    {
        gDisableStructs[gBattlerAttacker].trenchRunTimer = 4; //4 turns if fast, 3 turns if slower
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}
void BS_setuserstatus4(void)  //right now just usiong to set status groudned, for trenchrun
{
    u32 flags = T1_READ_32(gBattlescriptCurrInstr + 1);

    if (gStatuses4[gBattlerAttacker] & flags)
    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 5);
    }
    else
    {
        gStatuses4[gBattlerAttacker] |= flags;

        gBattlescriptCurrInstr += 9;
    }

}

void BS_typebaseddmgboost(void)
{
    NATIVE_ARGS();

    u8 typeArgument = gBattleMoves[gCurrentMove].argument;
    u8 EffectMultiplier = gBattleMoves[gCurrentMove].argumentEffectChance;

    if (gBattleMoves[gCurrentMove].effect == EFFECT_TARGET_TYPE_DAMAGE)
    {
        gDynamicBasePower = gBattleMoves[gCurrentMove].power;

        /*if (gBattleMons[gBattlerTarget].type1 != TYPE_FIGHTING
            || gBattleMons[gBattlerTarget].type2 != TYPE_FIGHTING)
            gDynamicBasePower = gBattleMoves[gCurrentMove].power;*/

        if (IS_BATTLER_OF_TYPE(gBattlerTarget,typeArgument))
            gDynamicBasePower = (gDynamicBasePower * EffectMultiplier) / 10;
        
    }
   gBattlescriptCurrInstr = cmd->nextInstr;
}

//checked isn't actually used for making move attack this turn, its just in typecalc for wonderguard telepathy stuff
//setting of attack this turn is set in battlescript so replace that and make use this
//make it a call native, battlerId should default to gbattlerattacker/bs_attacker
//can remove move argument and just replace with gcurrentmove
//potentially make this defualt script setup for attack this turn, 
//then can make simple setup for abilities thaat bypass that and just put here.
//plan setup dialga time ability make also remove recahrge turns for dmg cut
void BS_AttacksThisTurn(void) // Note: returns 1 if it's a charging turn, otherwise 2
{
    NATIVE_ARGS(const u8 *ptr);
    bool8 Thisturn = FALSE;
    // first argument is unused
    if ((gBattleMoves[gCurrentMove].effect == EFFECT_SOLARBEAM) //rebalanced effect not using special status for
     && (IsBattlerWeatherAffected(gBattlerAttacker, WEATHER_SUN_ANY)
      || (GetBattlerAbility(gBattlerAttacker) == ABILITY_FLUORESCENCE && IsBlackFogNotOnField())) 
    )                                                
        Thisturn = TRUE;             //not using most of below but will keep as is incase I plan to expand this function/macros use beyond just solar beam   

    else if (gBattleMoves[gCurrentMove].effect == EFFECT_SKULL_BASH
     || gBattleMoves[gCurrentMove].effect == EFFECT_RAZOR_WIND
     || gBattleMoves[gCurrentMove].effect == EFFECT_SKY_ATTACK
     || gBattleMoves[gCurrentMove].effect == EFFECT_SOLARBEAM
     || gBattleMoves[gCurrentMove].effect == EFFECT_SEMI_INVULNERABLE
     || gBattleMoves[gCurrentMove].effect == EFFECT_BIDE
     || gHitMarker & HITMARKER_CHARGING)  //not sure how this works??  oh nvm note above seems to clarify
            Thisturn = FALSE;
    else
        Thisturn = TRUE;

    if (Thisturn == TRUE)
       gBattlescriptCurrInstr = cmd->ptr; //do jump

    else
       gBattlescriptCurrInstr = cmd->nextInstr;
    
} //vsonic double check, nvm planning to only use for solar beam/fluorescence so can leave other setups as they are

//should let multihit moves display effectiveness of first hit
//causes freeze for no apparent reason
void BS_Multihit_resultmessage(void) //there are no multihit status moves I don't need a fix for this -__-
{
    NATIVE_ARGS();
    u32 stringId = 0;
    u8 moveType;
    GET_MOVE_TYPE(gCurrentMove,moveType);

    
    if (!gBattleControllerExecFlags) //need to ues else if, or breaks messaging
    {
        if (gMultiHitCounter > 1 && gMultiHitCounter == gMultiTask) //should be only first hit of multi hit
        {
            if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE) //above works but then when it goes to result on last hit it displays same string again, need to ensure string displayed is not same
            {
                stringId = STRINGID_SUPEREFFECTIVE;
                gBattleCommunication[MSG_DISPLAY] = 1;
            }

            else if (gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
            {
              if (CalcTypeEffectivenessMultiplier(gCurrentMove, moveType, gBattlerAttacker, gBattlerTarget, FALSE) == UQ_4_12_TO_INT((UQ_4_12(1.55) * UQ_4_12(0.5)) + UQ_4_12_ROUND))
                {
                    stringId = STRINGID_EMPTYSTRING3;
                    gBattleCommunication[MSG_DISPLAY] = 1;
                    gBattlescriptCurrInstr = cmd->nextInstr;
                }
              else
              {
                stringId = STRINGID_NOTVERYEFFECTIVE;
                gBattleCommunication[MSG_DISPLAY] = 1;
              }
            }
            else
            {
                gBattleCommunication[MSG_DISPLAY] = 0;
                gBattlescriptCurrInstr = cmd->nextInstr;
            }

        }
        else
        {
            stringId = STRINGID_EMPTYSTRING3;
            gBattleCommunication[MSG_DISPLAY] = 1;
            gBattlescriptCurrInstr = cmd->nextInstr;
        } //using this setup doesn't clear effect message but it doesn't seem to freeze, and otherwise it good
        // ...sigh ok now it freezes when reuse multiple times in single battle?? check multitask multihitcounter if there's some sort of stacking
        /*
        else //changes fixed most, but now only freezes if faint before counter reaches 0?
        {
            stringId = STRINGID_EMPTYSTRING3;
            gBattleCommunication[MSG_DISPLAY] = 1;
            //++gBattlescriptCurrInstr;
        }
        */


        if (stringId)
        {
            VarSet(VAR_LAST_MULTIHIT_RESULT, stringId); //store string for resultmessage comparison
            PrepareStringBattle(stringId, gBattlerAttacker);
            gBattlescriptCurrInstr = cmd->nextInstr;
        }
                   
    
    }
    
    //gBattlescriptCurrInstr = cmd->nextInstr;
}

//not technical call, replacement for bad code logic, will allow me to just slot in whatever I need
//more or less
void BS_call_if(void) //comparing to jumpifholdeffect
{   //gBattlescriptCurrInstr[1] value read from script
    //for reading sript arguments first read value of entire script command i.e callnative is 5 bytes
    //so  first argument of a callnative command is curr instr + 5;
    //T1_READ_16(gBattlescriptCurrInstr + 5); tells it to read a 2 byte section, 5 byte ahead,
    //so in this case would coresponde to the effect after call native command.
    NATIVE_ARGS(u16 effect); //thought wasn't working but seems to be working?
    //need test if above is actually working, otherwise use read_16 instead
    if (gBattleMoves[gCurrentMove].effect == cmd->effect) //if move effect equals script effect run logic, else skip
    {
        switch(gBattleMoves[gCurrentMove].effect)   //specifically makes it only trigger on effect listed in script, allows me to put wherever I Need, without issue
        {
            //replacing typecalc2 in rollout, purpose 
            //is to cancel multiturn moves if no effect, to stop rollout
            //taken out of rolloutdamagecalculation
            case EFFECT_ROLLOUT:
                if (gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                {
                    CancelMultiTurnMoves(gBattlerAttacker);
                    gBattlescriptCurrInstr = BattleScript_MoveMissedPause;
                }
                break;
            //trying to replace typecalc2 in brick break
            //it does weird logic to make move calc as missing/no effect when breakig a barrier 
            //then running typecalc to, to reinstitute dmg? 
            //make function for screen check
            //do jump if find screen will need do animation, its suppposed to hit even if against type doesnt work on
            //move around comands in script, for screen removal command directly after screen check, if find screen continue, otherwise jump to normal attack etc.
            //plan break animation after screen removal, think need put dmg related scripts below the effect
            //believe order could be, accuracy check, screen check-jump, screen remove, atk string pp remove atk animation wait animation, screen break animation, 
            //critcalc dmg calc type calc jump if no result to result strings at end of normal script
            ////now after that is values you jump to if there is no screen, which should be all normal move values,

            //that would work but would invalidate this function, other option
            //is make 2 brick break bs scripts one for normal, one for if detect screen, 
            //and just have the screen check in this function, and set curr instruction based on that for easy clean navigation
            //end result the actual brick break effect script would just be this one command 
            case EFFECT_BRICK_BREAK:
                if (TryRemoveScreens(gBattlerAttacker)) //replace with function check for screens / adapted screen cleaner logic, rather than make from scratch
                {
                    gBattlescriptCurrInstr = BattleScript_BrickBreakWithScreens;//may be able to do something similar to fury cutter where anim effects used a stored value to change animation?
                    return;
                } 
                else
                {
                    gBattlescriptCurrInstr = BattleScript_BrickBreakNoScreens;
                    return; //addding returns to this seem to make scritp read correctly?
                }                    
                break;//removes screens from start, still need to setup script with screens, need understand how wall animation worked in default script
                
            /*case EFFECT_SWARM:  //think dn't need this set elsewhere
            if (!(gDisableStructs[gEffectBattler].swarmTurns)) //for trap status
            {
                if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_GRIP_CLAW
                    || (GetBattlerAbility(gBattlerAttacker) == ABILITY_SUCTION_CUPS))   //BUFF for suction cups - need work on better define setup this vsonic
                {
                    gDisableStructs[gEffectBattler].swarmTurns = 7;
                }   //and check util.c so both status4 & status1 gets cleared when timer hits 0
                else    //just lasting longer seems a bit useless maybe make it a status1 so you can switch out and still trap enemy?
                    gDisableStructs[gEffectBattler].swarmTurns = ((Random() % 5) + 2);   //will do 2-6 turns

                    gBattleMons[gActiveBattler].status4 |= STATUS4_INFESTATION; //wasn't planning to include status in this but think need it for animation to play properly
            }
                break;*/
            case EFFECT_ACCURACY_DOWN:            
                if ((IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GROUND) 
                && (gBattleStruct->dynamicMoveType == TYPE_GROUND
                || gBattleMoves[gCurrentMove].type == TYPE_GROUND
                || gBattleMoves[gCurrentMove].argument == TYPE_GROUND))
                && gBattleMoves[gCurrentMove].split == SPLIT_STATUS) //for sand attack etvc.
                {
                    gBattlescriptCurrInstr = BattleScript_NotAffected; 
                    return;
                } //planned effect ground types can't have accuracy dropped by groud moves set rest in move effect
            break;
            case EFFECT_TARGET_TYPE_DAMAGE:
            if (gCurrentMove == MOVE_ROCK_SMASH)
                gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_1;
                gBattlescriptCurrInstr = cmd->nextInstr;
                break;       
            case EFFECT_TWO_TYPED_MOVE:
            if (gCurrentMove == MOVE_MUDDY_WATER)
                gBattleScripting.moveEffect = MOVE_EFFECT_ACC_MINUS_1;
            else if (gCurrentMove == MOVE_SPLISHY_SPLASH)
                gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
            else if (gCurrentMove == MOVE_FREEZE_SHOCK)
                gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
            else if (gCurrentMove == MOVE_BOLTBEAM)
                gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE;
            else if (gCurrentMove == MOVE_ICE_BURN)
                gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
                gBattlescriptCurrInstr = cmd->nextInstr;
                break;    
            case EFFECT_PARALYZE:
            if ((IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_ELECTRIC) && gBattleMoves[gCurrentMove].type == TYPE_ELECTRIC)
            && gBattleMoves[gCurrentMove].split == SPLIT_STATUS) //for thunder wave
            {
                gBattlescriptCurrInstr = BattleScript_NotAffected; 
                return;
            }     
            break;
            case EFFECT_REVENGE:
                atkD6_doubledamagedealtifdamaged();
                break;
            case EFFECT_JUDGMENT:
                if (gCurrentMove == MOVE_JUDGMENT && gBattleStruct->dynamicMoveType != TYPE_MYSTERY)
                    PrepareStringBattle(STRINGID_JUDGMENT, gBattlerAttacker); //SEE IF thsi works
            break;

        }
    }
    gBattlescriptCurrInstr = cmd->nextInstr;

     //had to put in hitfromcritcalc for rollout, so put intr increment back in, so won't break everything else, 
    //will only trigger for whatever effect is listed here, but still needs to be put where it makes senes for the effect
    //+3 because effects are 2 bytes, and macro is 1 actually wrong, talked witwh griffinR, callnative is 5, then effect is 2, so should be 7
}

/*static void atk41_call(void)
{
    BattleScriptPush(gBattlescriptCurrInstr + 5);
    gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
}
*/

void BS_getmoveeffect(void)//transfer move effects mostly for multihit but also used for multitask so each hit can apply aeffect
{
    NATIVE_ARGS(); //change logic for this, best way to do it would be with effect to moveeffect table/array
    //that way I can do most of them with a single line on a default case, leaving me to only need to write out the exceptions/complex effects
    //like case EFFECT_TARGET_TYPE_DAMAGE:  
    //setup table? maybe switch  with effects and an line for affectsuser = true  if it is true otherwise leae blank
    // than at bottom of effects list   if affectsuser = true  set MOVE_EFFECT_AFFECTS_USER as well
    //wouldnt need to set certain as that could be handled by percent chance being 0    in setmoveeffectwithchance
    //having that woud simplify this, but also change how I use setmoveeffect for thebetter  //vsonic


    switch (gBattleMoves[gCurrentMove].effect) //add on as needed, mostly just for multitask, as movevaluescleanup would remove move effect during loop
    {
        case EFFECT_POISON_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
            break;
        case EFFECT_BURN_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
            break;
        case EFFECT_FREEZE_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE;
            break;
        case EFFECT_PARALYZE_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
            break;
        case EFFECT_TOXIC_FANG:
        gBattleScripting.moveEffect = MOVE_EFFECT_TOXIC;
            break;
        case EFFECT_FLINCH_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
            break;
        case EFFECT_CONFUSE_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
            break;
        case EFFECT_TWINEEDLE:
        gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
            break;
        case EFFECT_DOUBLE_IRON_BASH:
        gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
            break;
        case EFFECT_TARGET_TYPE_DAMAGE:
            if (gCurrentMove == MOVE_ROCK_SMASH)
                gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_1;
            break;
        case EFFECT_TWO_TYPED_MOVE:
            if (gCurrentMove == MOVE_MUDDY_WATER)
                gBattleScripting.moveEffect = MOVE_EFFECT_ACC_MINUS_1;
            break;
        case EFFECT_SPEED_DOWN_HIT:
        gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
            break;
        //case EFFECT_INFESTATION:      //no longer called this and moved to argument to set this
        //gBattleScripting.moveEffect = MOVE_EFFECT_INFESTATION;
        //    break;
        default:
            gBattleScripting.moveEffect = MOVE_EFFECT_NOTHING_0;
            break;

    }

    gBattlescriptCurrInstr = cmd->nextInstr;
}