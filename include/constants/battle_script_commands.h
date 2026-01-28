#ifndef GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
#define GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H



enum BattleScriptOpcode
{
    B_SCR_OP_ATTACKCANCELER,
    B_SCR_OP_ACCURACYCHECK,
    B_SCR_OP_PRINTATTACKSTRING,
    B_SCR_OP_PRINTSELECTIONSTRINGFROMTABLE,
    B_SCR_OP_SETCRITPROTECT, //was critcalc since moves to dmgcalc
    B_SCR_OP_DAMAGECALC,
    B_SCR_OP_TYPECALC,
    B_SCR_OP_ADJUSTDAMAGE,
    B_SCR_OP_MULTIHITRESULTMESSAGE,
    B_SCR_OP_ATTACKANIMATION,
    B_SCR_OP_WAITANIMATION,
    B_SCR_OP_HEALTHBARUPDATE,
    B_SCR_OP_DATAHPUPDATE,
    B_SCR_OP_CRITMESSAGE,
    B_SCR_OP_EFFECTIVENESSSOUND,
    B_SCR_OP_RESULTMESSAGE,
    B_SCR_OP_PRINTSTRING,
    B_SCR_OP_PRINTSELECTIONSTRING,
    B_SCR_OP_WAITMESSAGE,
    B_SCR_OP_PRINTFROMTABLE,
    B_SCR_OP_SETPREATTACKADDITIONALEFFECT,
    B_SCR_OP_SETADDITIONALEFFECTS,
    B_SCR_OP_SETEFFECTPRIMARY,
    B_SCR_OP_SETEFFECTSECONDARY,
    B_SCR_OP_CLEARVOLATILE,
    B_SCR_OP_TRYFAINTMON,
    B_SCR_OP_DOFAINTANIMATION,
    B_SCR_OP_CLEAREFFECTSONFAINT,
    B_SCR_OP_JUMPIFSTATUS,
    B_SCR_OP_JUMPIFVOLATILE,
    B_SCR_OP_JUMPBASEDONABILITY,
    B_SCR_OP_JUMPIFSIDEAFFECTING,
    B_SCR_OP_JUMPIFSTAT,
    B_SCR_OP_JUMPIFSTATIGNORECONTRARY,
    B_SCR_OP_JUMPBASEDONTYPE,
    B_SCR_OP_GETEXP,
    B_SCR_OP_CHECKTEAMSLOST,
    B_SCR_OP_MOVEVALUESCLEANUP,
    B_SCR_OP_SETMULTIHIT,
    B_SCR_OP_DECREMENTMULTIHIT,
    B_SCR_OP_GOTO,
    B_SCR_OP_JUMPIFBYTE,
    B_SCR_OP_JUMPIFHALFWORD,
    B_SCR_OP_JUMPIFWORD,
    B_SCR_OP_JUMPIFARRAYEQUAL,
    B_SCR_OP_JUMPIFARRAYNOTEQUAL,
    B_SCR_OP_SETBYTE,
    B_SCR_OP_ADDBYTE,
    B_SCR_OP_SUBBYTE,
    B_SCR_OP_COPYARRAY,
    B_SCR_OP_COPYARRAYWITHINDEX,
    B_SCR_OP_ORBYTE,
    B_SCR_OP_ORHALFWORD,
    B_SCR_OP_ORWORD,
    B_SCR_OP_BICBYTE,
    B_SCR_OP_BICHALFWORD,
    B_SCR_OP_BICWORD,
    B_SCR_OP_PAUSE,
    B_SCR_OP_WAITSTATE,
    B_SCR_OP_ISDMGBLOCKEDBYDISGUISE,
    B_SCR_OP_RETURN,
    B_SCR_OP_END,
    B_SCR_OP_END2,
    B_SCR_OP_END3,
    B_SCR_OP_SETCHARGINGTURN,
    B_SCR_OP_CALL,
    B_SCR_OP_SETROOST,
    B_SCR_OP_JUMPIFABILITYPRESENT,
    B_SCR_OP_ENDSELECTIONSCRIPT,
    B_SCR_OP_PLAYANIMATION,
    B_SCR_OP_PLAYANIMATION_VAR,
    B_SCR_OP_JUMPFIFSEMIINVULNERABLE,
    B_SCR_OP_TRAINERSLIDEIN,
    B_SCR_OP_MOVEEND,
    B_SCR_OP_SETHEALBLOCK,
    B_SCR_OP_RETURNATKTOBALL,
    B_SCR_OP_GETSWITCHEDMONDATA,
    B_SCR_OP_SWITCHINDATAUPDATE,
    B_SCR_OP_SWITCHINANIM,
    B_SCR_OP_JUMPIFCANTSWITCH,
    B_SCR_OP_OPENPARTYSCREEN,
    B_SCR_OP_SWITCHHANDLEORDER,
    B_SCR_OP_SWITCHINEFFECTS,
    B_SCR_OP_SWITCHINEVENTS,
    B_SCR_OP_PLAYSE,
    B_SCR_OP_FANFARE,
    B_SCR_OP_PLAYFAINTCRY,
    B_SCR_OP_ENDLINKBATTLE,
    B_SCR_OP_RETURNTOBALL,
    B_SCR_OP_HANDLELEARNNEWMOVE,
    B_SCR_OP_YESNOBOXLEARNMOVE,
    B_SCR_OP_YESNOBOXSTOPLEARNINGMOVE,
    B_SCR_OP_HITANIMATION,
    B_SCR_OP_GETMONEYREWARD,
    B_SCR_OP_UPDATEBATTLERMOVES,
    B_SCR_OP_SWAPATTACKERWITHTARGET,
    B_SCR_OP_INCREMENTGAMESTAT,
    B_SCR_OP_DRAWPARTYSTATUSSUMMARY,
    B_SCR_OP_HIDEPARTYSTATUSSUMMARY,
    B_SCR_OP_JUMPTOCALLEDMOVE,
    B_SCR_OP_STATUSANIMATION,
    B_SCR_OP_FUTURESIGHTTARGETFAILURE,
    B_SCR_OP_GETPOSSIBLENEXTTARGET,
    B_SCR_OP_YESNOBOX,
    B_SCR_OP_CANCELALLACTIONS,
    B_SCR_OP_SETGRAVITY,
    B_SCR_OP_REMOVEITEM,
    B_SCR_OP_ATKNAMEINBUFF1,
    B_SCR_OP_DRAWLVLUPBOX,
    B_SCR_OP_RESETSENTMONSVALUE,
    B_SCR_OP_SETATKTOPLAYER0,
    B_SCR_OP_MAKEVISIBLE,
    B_SCR_OP_RECORDABILITY,
    B_SCR_OP_BUFFERMOVETOLEARN,
    B_SCR_OP_JUMPIFPLAYERRAN,
    B_SCR_OP_HPTHRESHOLDS,
    B_SCR_OP_HPTHRESHOLDS2,
    B_SCR_OP_USEITEMONOPPONENT,
    B_SCR_OP_UNUSED_0X78,
    B_SCR_OP_SETPROTECTLIKE,
    B_SCR_OP_TRYEXPLOSION,
    B_SCR_OP_SETATKHPTOZERO,
    B_SCR_OP_JUMPIFNEXTTARGETVALID,
    B_SCR_OP_TRYHEALHALFHEALTH,
    B_SCR_OP_UNUSED_0X7E,
    B_SCR_OP_SETFIELDWEATHER,
    B_SCR_OP_SETREFLECT,
    B_SCR_OP_SETSEEDED,
    B_SCR_OP_MANIPULATEDAMAGE,
    B_SCR_OP_TRYSETREST,
    B_SCR_OP_UNUSED_0X82,
    B_SCR_OP_UNUSED_0X83,
    B_SCR_OP_JUMPIFUPROARWAKES,
    B_SCR_OP_STOCKPILE,
    B_SCR_OP_STOCKPILETOBASEDAMAGE,
    B_SCR_OP_STOCKPILETOHPHEAL,
    B_SCR_OP_UNUSED_0X88,
    B_SCR_OP_STATBUFFCHANGE,
    B_SCR_OP_NORMALISEBUFFS,
    B_SCR_OP_SETBIDE,
    B_SCR_OP_TWOTURNMOVESCHARGESTRINGANDANIMATION,
    B_SCR_OP_TRYNONVOLATILESTATUS,
    B_SCR_OP_INITMULTIHITSTRING,
    B_SCR_OP_FORCERANDOMSWITCH,
    B_SCR_OP_TRYCONVERSIONTYPECHANGE,
    B_SCR_OP_GIVEPAYDAYMONEY,
    B_SCR_OP_SETLIGHTSCREEN,
    B_SCR_OP_TRYKO,
    B_SCR_OP_CHECKNONVOLATILETRIGGER,
    B_SCR_OP_COPYBIDEDMG,
    B_SCR_OP_ANIMATEWILDPOKEMONAFTERFAILEDPOKEBALL,
    B_SCR_OP_TRYINFATUATING,
    B_SCR_OP_UPDATESTATUSICON,
    B_SCR_OP_SETMIST,
    B_SCR_OP_SETFOCUSENERGY,
    B_SCR_OP_TRANSFORMDATAEXECUTION,
    B_SCR_OP_SETSUBSTITUTE,
    B_SCR_OP_MIMICATTACKCOPY,
    B_SCR_OP_SETCALLEDMOVE,
    B_SCR_OP_UNUSED_0X9F,
    B_SCR_OP_UNUSED_0XA0,
    B_SCR_OP_UNUSED_0XA1,
    B_SCR_OP_UNUSED_0XA2,
    B_SCR_OP_DISABLELASTUSEDATTACK,
    B_SCR_OP_TRYSETENCORE,
    B_SCR_OP_PAINSPLITDMGCALC,
    B_SCR_OP_CHANGETYPETORESISTTARGET,
    B_SCR_OP_SETALWAYSHITFLAG,
    B_SCR_OP_COPYMOVEPERMANENTLY,
    B_SCR_OP_UNUSED_0XA9,
    B_SCR_OP_UNUSED_AA,
    B_SCR_OP_UNUSED_0XAB,
    B_SCR_OP_SETTAILWIND,
    B_SCR_OP_TRYSPITEPPREDUCE,
    B_SCR_OP_HEALPARTYSTATUS,
    B_SCR_OP_CURSETARGET,
    B_SCR_OP_TRYSETSPIKES,
    B_SCR_OP_SETVOLATILE,
    B_SCR_OP_TRYSETPERISHSONG,
    B_SCR_OP_UNUSED_0XB3,
    B_SCR_OP_JUMPIFCONFUSEDANDSTATMAXED,
    B_SCR_OP_UNUSED_0XB5,
    B_SCR_OP_SETEMBARGO,
    B_SCR_OP_PRESENTDAMAGECALCULATION,
    B_SCR_OP_SETSAFEGUARD,
    B_SCR_OP_MAGNITUDEDAMAGECALCULATION,
    B_SCR_OP_JUMPIFNOPURSUITSWITCHDMG,
    B_SCR_OP_TRYACTIVATEITEM,
    B_SCR_OP_HALVEHP,
    B_SCR_OP_COPYFOESTATS,
    B_SCR_OP_RAPIDSPINFREE,
    B_SCR_OP_UNUSED_0XBF,
    B_SCR_OP_RECOVERBASEDONSUNLIGHT,
    B_SCR_OP_SETSTICKYWEB,
    B_SCR_OP_SELECTFIRSTVALIDTARGET,
    B_SCR_OP_SETFUTUREATTACK,
    B_SCR_OP_TRYDOBEATUP,
    B_SCR_OP_SETSEMIINVULNERABLEBIT,
    B_SCR_OP_UNUSED_0XC6,
    B_SCR_OP_UNUSED_0XC7,
    B_SCR_OP_UNUSED_C8,
    B_SCR_OP_TRYMEMENTO,
    B_SCR_OP_SETFORCEDTARGET,
    B_SCR_OP_UNUSED_0XCB,
    B_SCR_OP_UNUSED_0XCC,
    B_SCR_OP_CURESTATUSWITHMOVE,
    B_SCR_OP_SETTORMENT,
    B_SCR_OP_UNUSED_0XCF,
    B_SCR_OP_SETTAUNT,
    B_SCR_OP_TRYSETHELPINGHAND,
    B_SCR_OP_TRYSWAPITEMS,
    B_SCR_OP_TRYCOPYABILITY,
    B_SCR_OP_TRYWISH,
    B_SCR_OP_SETTOXICSPIKES,
    B_SCR_OP_SETGASTROACID,
    B_SCR_OP_SETYAWN,
    B_SCR_OP_UNUSED0XD8,
    B_SCR_OP_SETROOM,
    B_SCR_OP_TRYSWAPABILITIES,
    B_SCR_OP_TRYIMPRISON,
    B_SCR_OP_SETSTEALTHROCK,
    B_SCR_OP_TRYSETVOLATILE,
    B_SCR_OP_UNUSED_0XDE,
    B_SCR_OP_SETMAGICCOAT,
    B_SCR_OP_TRYSETSNATCH,
    B_SCR_OP_UNUSED2,
    B_SCR_OP_SWITCHOUTABILITIES,
    B_SCR_OP_JUMPIFHASNOHP,
    B_SCR_OP_UNUSED_0XE4,
    B_SCR_OP_GENERATEENDBATTLEITEM,
    B_SCR_OP_UNUSED_0XE6,
    B_SCR_OP_UNUSED_0XE7,
    B_SCR_OP_SETTYPEBASEDHALVERS,
    B_SCR_OP_JUMPIFSUBSTITUTEBLOCKS,
    B_SCR_OP_TRYRECYCLEITEM,
    B_SCR_OP_SETTYPETOENVIRONMENT,
    B_SCR_OP_PURSUITDOUBLES,
    B_SCR_OP_SNATCHSETBATTLERS,
    B_SCR_OP_UNUSED_0XEE,
    B_SCR_OP_HANDLEBALLTHROW,
    B_SCR_OP_GIVECAUGHTMON,
    B_SCR_OP_TRYSETCAUGHTMONDEXFLAGS,
    B_SCR_OP_DISPLAYDEXINFO,
    B_SCR_OP_TRYGIVECAUGHTMONNICK,
    B_SCR_OP_SORTBATTLERS,
    B_SCR_OP_REMOVEATTACKERSTATUS1,
    B_SCR_OP_FINISHACTION,
    B_SCR_OP_FINISHTURN,
    B_SCR_OP_TRAINERSLIDEOUT,
    B_SCR_OP_SETTELEKINESIS,
    B_SCR_OP_SWAPSTATSTAGES,
    B_SCR_OP_AVERAGESTATS,
    B_SCR_OP_JUMPIFCAPTIVATEAFFECTED,
    B_SCR_OP_SETNONVOLATILESTATUS,
    B_SCR_OP_TRYOVERWRITEABILITY,
    B_SCR_OP_CALLNATIVE,
};

//ok this needs to match the Battlescripting struct in include/battle.h
// + 1 if u8,   +2 if u16,   +4 if u32,  if bracket multiply value in bracket by type
//ex  u8 multihitString[6];    6 x  +1  = +6
//go up from previous value, not inclusive, so not counting that last value based on your found number and that's next values starting point
//ex last value 24  it is u16 so you go Up 2 from 24, - 25, 26, your next value is 26
//emerald also goes over 32, so that dosen't seem to be a hard limit this is fine

// Battle Scripting and BattleCommunication addresses
#define sPAINSPLIT_HP gBattleScripting					// s32 painSplitHp;	4 byte 0 1 2 3
#define sBIDE_DMG gBattleScripting + 4					//s32 bideDmg;	4 byte 4 5 6 7
#define sMULTIHIT_STRING gBattleScripting + 8			//u8 multihitString[6]; 6 1byte  8 9 a b c d

// think don't use sdmg_multiplier anymore since put dmg shift into flag least for semi invul, still have some to adjust facade & pursit, thencan remove
#define sSAVED_STRINGID gBattleScripting + 0xE		    //2 bytes now /u8 twoTurnsMoveStringId; 1 byte f //becomes savedStringId in EE can be used for multiple things thinkm make 2 byte to be able store actual stringids
#define sB_ANIM_ARG1 gBattleScripting + 0x10			//u8 animArg1; 1 byte 0x10
#define sB_ANIM_ARG2 gBattleScripting + 0x11			//u8 animArg2; 1 byte 0x11
//I also moved triple kick power to functions so could remove?
#define sMULTIHIT_EFFECT gBattleScripting + 0x12		//u16 multihitMoveEffect; 2 byte 0x16 0x17	 //stores move effect for multihit moves, like twineedle uses it to store poison
#define sMOVEEND_STATE gBattleScripting + 0x14			//u8 atk49_state; 1 byte 0x14
#define sBATTLER_WITH_ABILITY gBattleScripting + 0x15	//u8 battlerWithAbility; 1 byte 0x15
#define sSTATCHANGEID gBattleScripting + 0x16           //statChangeId new value for dynamic stat set, this stat id will be passed to statchanger stat argument
#define sBATTLER gBattleScripting + 0x17				//u8 battler; 1 byte 0x1c
#define sB_ANIM_TURN gBattleScripting + 0x18			//u8 animTurn; 1 byte 0x1d
#define sB_ANIM_TARGETS_HIT gBattleScripting + 0x19		//u8 animTargetsHit; 1 byte 0x1e
#define sSTATCHANGER gBattleScripting + 0x1A			//u8 statChanger; 1 byte 0x1f
#define sSTAT_ANIM_PLAYED gBattleScripting + 0x1B		//bool8 statAnimPlayed; 1 byte 0x20
#define sGIVEEXP_STATE gBattleScripting + 0x1C			//u8 atk23_getexpState; 1 byte 0x21
#define sBATTLE_STYLE gBattleScripting + 0x1D			//u8 battleStyle; 1 byte 0x22   //switch or set
#define sLVLBOX_STATE gBattleScripting + 0x1E			//u8 atk6C_drawlvlupboxState; 1 byte 0x23
#define sLEARNMOVE_STATE gBattleScripting + 0x1F		//u8 learnMoveState; 1 byte 0x24
#define sPURSUIT_DOUBLE_DAMAGE gBattleScripting + 0x20	//u8 field_25_pursuitDoublesAttacker; 1 byte 0x25    //unsure of use  maybe i changed but does'nt seem used
#define sRESHOW_MAIN_STATE gBattleScripting + 0x21		//u8 reshowMainState; 1 byte 0x26
#define sRESHOW_HELPER_STATE gBattleScripting + 0x22	//u8 reshowHelperState; 1 byte 0x27
#define sLVLUP_HP gBattleScripting + 0x23				//u8 field_23;	1 byte 0x31		//nothing in struct below this think all used values must go above here
//end of default New values below
#define sSAVED_STAT_CHANGER gBattleScripting + 0x24		//u8 savedStatChanger; 1 byte 0x28	for moody

#define sSAVED_BATTLER (gBattleScripting + 0x25)		//u8 savedBattler; 1 byte 0x29
//#define sILLUSION_NICK_HACK gBattleScripting + 0x25	//need add this eventually
//
//#define sFIXED_ABILITY_POPUP         (gBattleScripting + 0x26) // fixedPopup
//#define sABILITY_OVERWRITE           (gBattleScripting + 0x27) // abilityPopupOverwrite


#define sSWITCH_CASE (gBattleScripting + 0x26)			//u8 switchCase; 1 byte 0x2a    // switchCase  used for red card special swith condition	//FORCED SWITCH?
#define sBERRY_OVERRIDE	(gBattleScripting + 0x27)		//u8 overrideBerryRequirements; 1 byte 0x2b  // overrideBerryRequirements  //ok this seems to just mean don't consume berry???  
#define sSAVED_DMG gBattleScripting + 0x28				//s32 savedDmg; 4 byte 0x2d 0x2e 0x2f 0x30
//#define sMON_CAUGHT     (gBattleScripting + 0x33) // monCaught NOT NEEDED, only used in emerald for succesful captures to incremennt game stat capture
#define sSAVED_MOVE_EFFECT gBattleScripting + 0x2C		//u16 savedMoveEffect; 2 byte 0x18 0x19         // savedMoveEffect
#define sMOVE_EFFECT gBattleScripting + 0x2E			//u16 moveEffect; 2 byte 0x1a 0x1b          // moveEffect   //these really are move effect
#define sSTICKY_WEB_STAT_DROP (gBattleScripting + 0x30) //u8 stickyWebStatDrop; 1 byte 0x2c  // overrideBerryRequirements

//shifted from hexadecimal as not compatible w battle script for some reason
// array entries for battle communication
#define MULTIUSE_STATE          0
#define CURSOR_POSITION         1
#define TASK_ID                 1 // task Id and cursor position share the same field
#define SPRITES_INIT_STATE1     1 // shares the Id as well
#define SPRITES_INIT_STATE2     2
#define MOVE_EFFECT_BYTE        3
#define ACTIONS_CONFIRMED_COUNT 4
#define MULTISTRING_CHOOSER     5
#define MISS_TYPE               6
#define MSG_DISPLAY             7
#define BATTLE_COMMUNICATION_ENTRIES_COUNT  0x8

//battle communication stuff
#define cEFFECT_CHOOSER gBattleCommunication + MOVE_EFFECT_BYTE        //figure what gBattleCommunication is and how works. vsonic
#define cMULTISTRING_CHOOSER gBattleCommunication + MULTISTRING_CHOOSER

#define cMISS_TYPE           (gBattleCommunication + MISS_TYPE)


//GetBattlerForBattleScript
// Battle Script defines for getting the wanted battler
#define BS_TARGET                   0
#define BS_ATTACKER                 1
#define BS_EFFECT_BATTLER           2
#define BS_FAINTED                  3
#define BS_ATTACKER_WITH_PARTNER    4 // for atk98_updatestatusicon
#define BS_FAINTED_MULTIPLE_1       5 // for openpartyscreen
#define BS_FAINTED_MULTIPLE_2       6 // for openpartyscreen
#define BS_BATTLER_0                7
#define BS_ATTACKER_SIDE            8 // for atk1E_jumpifability
#define BS_TARGET_SIDE				9 // for atk1E_jumpifability
#define BS_SCRIPTING                10 // gBattleScripting.battler
#define BS_PLAYER1                  11
#define BS_OPPONENT1                12
#define BS_PLAYER2                  13 // for atk98_updatestatusicon  /?? i don't remember tis
#define BS_OPPONENT2                14
#define BS_ABILITY_BATTLER          15	//port from emerald
#define BS_ATTACKER_PARTNER         16
#define BS_TARGET_PARTNER           17 //last two my additions for ability messages

// used for openpartyscreen
#define OPEN_PARTY_ALLOW_CANCEL     0x80

// compare operands
#define CMP_EQUAL               0x0
#define CMP_NOT_EQUAL           0x1
#define CMP_GREATER_THAN        0x2
#define CMP_LESS_THAN           0x3
#define CMP_COMMON_BITS         0x4
#define CMP_NO_COMMON_BITS      0x5

// TODO: documentation	//need to set bs.inc various to the order of this file      doesn't need to match order at all
// atk76, various
#define VARIOUS_CANCEL_MULTI_TURN_MOVES         0
#define VARIOUS_SET_MAGIC_COAT_TARGET           1
#define VARIOUS_IS_RUNNING_IMPOSSIBLE           2
#define VARIOUS_GET_MOVE_TARGET                 3
#define VARIOUS_GET_BATTLER_FAINTED                          4
#define VARIOUS_RESET_INTIMIDATE_TRACE_BITS     5
#define VARIOUS_UPDATE_CHOICE_MOVE_ON_LVL_UP    6
#define VARIOUS_RESET_PLAYER_FAINTED			7
#define VARIOUS_GET_BATTLERS_FOR_RECALL                          8
#define VARIOUS_RETURN_OPPONENT_MON1            9
#define VARIOUS_RETURN_OPPONENT_MON2            10
#define VARIOUS_CHECK_POKEFLUTE                 11
#define VARIOUS_WAIT_FANFARE                    12
//emerald ported luckily doesn't have to be in sequence so I'll just leave
//here in case they're needed
#define VARIOUS_SET_TELEPORT_OUTCOME            25
#define VARIOUS_SWITCHIN_ABILITIES				28
#define VARIOUS_SAVE_TARGET                     29
#define VARIOUS_RESTORE_TARGET                  30
#define VARIOUS_INSTANT_HP_DROP                 31
#define VARIOUS_CLEAR_STATUS                    32
#define VARIOUS_RESTORE_PP                      33
#define VARIOUS_TRY_ACTIVATE_MOXIE              34
#define VARIOUS_TRY_ACTIVATE_FELL_STINGER       35
#define VARIOUS_PLAY_MOVE_ANIMATION             36
#define VARIOUS_SET_LUCKY_CHANT                 37
#define VARIOUS_SUCKER_PUNCH_CHECK              38
#define VARIOUS_SET_SIMPLE_BEAM                 39
#define VARIOUS_TRY_ENTRAINMENT                 40
#define VARIOUS_SET_LAST_USED_ABILITY           41
#define VARIOUS_TRY_HEAL_PULSE                  42  //unused
#define VARIOUS_JUMP_IF_SHELL_TRAPPED           43  //replaced after you
#define VARIOUS_INVERT_STAT_STAGES              44
#define VARIOUS_SET_TERRAIN                     45
#define VARIOUS_TRY_ME_FIRST                    46
#define VARIOUS_JUMP_IF_BATTLE_END              47
#define VARIOUS_TRY_ELECTRIFY                   48
#define VARIOUS_TRY_REFLECT_TYPE                49
#define VARIOUS_TRY_SOAK                        50  //unused
#define VARIOUS_HANDLE_FORM_CHANGE              51 //will callnative don't need various, but bothersome to remove
#define VARIOUS_TRY_LAST_RESORT                 52
#define VARIOUS_ARGUMENT_STATUS_EFFECT          53
#define VARIOUS_TRY_HIT_SWITCH_TARGET           54
#define VARIOUS_TRY_AUTOTOMIZE                  55
#define VARIOUS_TRY_COPYCAT                     56
#define VARIOUS_ABILITY_POPUP                   57
#define VARIOUS_DEFOG                           58
#define VARIOUS_JUMP_IF_TARGET_ALLY             59
#define VARIOUS_TRY_SYNCHRONOISE                60
#define VARIOUS_PSYCHO_SHIFT                    61
#define VARIOUS_CURE_ALL_STATUS1                     62
#define VARIOUS_POWER_TRICK                     63
#define VARIOUS_AFTER_YOU                       64
#define VARIOUS_BESTOW                          65
#define VARIOUS_ARGUMENT_TO_MOVE_EFFECT         66
#define VARIOUS_JUMP_IF_NOT_GROUNDED            67
#define VARIOUS_HANDLE_TRAINER_SLIDE_MSG        68
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_FIRST_OFF 69
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_LAST_ON   70
#define VARIOUS_SET_AURORA_VEIL                 71
#define VARIOUS_TRY_THIRD_TYPE                  72
#define VARIOUS_ACUPRESSURE                     73
#define VARIOUS_SET_POWDER                      74
#define VARIOUS_SPECTRAL_THIEF                  75
#define VARIOUS_GRAVITY_ON_AIRBORNE_MONS        76
#define VARIOUS_CHECK_IF_GRASSY_TERRAIN_HEALS   77
#define VARIOUS_JUMP_IF_ROAR_FAILS              78
#define VARIOUS_TRY_INSTRUCT                    79
#define VARIOUS_JUMP_IF_NOT_BERRY               80
#define VARIOUS_TRACE_ABILITY                   81
#define VARIOUS_UPDATE_NICK                     82
#define VARIOUS_TRY_ILLUSION_OFF                83
#define VARIOUS_SET_SPRITEIGNORE0HP             84 //have space here after consolidating form change stuff //vsonic

#define VARIOUS_GET_STAT_VALUE                  86
#define VARIOUS_JUMP_IF_FULL_HP                 87
#define VARIOUS_LOSE_TYPE                       88
#define VARIOUS_TRY_ACTIVATE_SOULHEART          89
#define VARIOUS_TRY_ACTIVATE_RECEIVER           90
#define VARIOUS_TRY_ACTIVATE_BEAST_BOOST        91
#define VARIOUS_TRY_FRISK                       92
//#define VARIOUS_JUMP_IF_SHIELDS_DOWN_PROTECTED  93    //unused  vsonic
#define VARIOUS_TRY_FAIRY_LOCK                  94
#define VARIOUS_JUMP_IF_NO_ALLY                 95
#define VARIOUS_POISON_TYPE_IMMUNITY            96
#define VARIOUS_JUMP_IF_NOT_HOLD_EFFECT         97
#define VARIOUS_INFATUATE_WITH_BATTLER          98
#define VARIOUS_SET_LAST_USED_ITEM              99
#define VARIOUS_PARALYZE_TYPE_IMMUNITY          100
#define VARIOUS_JUMP_IF_ABSENT                  101
#define VARIOUS_DESTROY_ABILITY_POPUP           102
#define VARIOUS_TOTEM_BOOST                     103 //removed as didn't want to use
#define VARIOUS_TRY_ACTIVATE_GRIM_NEIGH         104
#define VARIOUS_MOVEEND_ITEM_EFFECTS            105
//think will introduce character that will give seeds for berries
#define VARIOUS_TERRAIN_SEED                        106
#define VARIOUS_MAKE_INVISIBLE                      107
#define VARIOUS_ROOM_SERVICE                        108
#define VARIOUS_JUMP_IF_TERRAIN_AFFECTED            109
#define VARIOUS_EERIE_SPELL_PP_REDUCE               110
#define VARIOUS_JUMP_IF_TEAM_HEALTHY                111
#define VARIOUS_TRY_HEAL_QUARTER_HP                 112
#define VARIOUS_REMOVE_TERRAIN                      113
#define VARIOUS_JUMP_IF_PRANKSTER_BLOCKED           114
#define VARIOUS_TRY_TO_CLEAR_PRIMAL_WEATHER         115
#define VARIOUS_GET_ROTOTILLER_TARGETS              116
#define VARIOUS_JUMP_IF_NOT_ROTOTILLER_AFFECTED     117
#define VARIOUS_TRY_ACTIVATE_BATTLE_BOND            118
#define VARIOUS_CONSUME_BERRY                       119
#define VARIOUS_JUMP_IF_CANT_REVERT_TO_PRIMAL       120 //have space to add below, from consolidating form change stuff as in EE

#define VARIOUS_APPLY_PLASMA_FISTS                  122
#define VARIOUS_JUMP_IF_SPECIES                     123
#define VARIOUS_UPDATE_ABILITY_POPUP                124
#define VARIOUS_JUMP_IF_WEATHER_AFFECTED            125
#define VARIOUS_JUMP_IF_LEAF_GUARD_PROTECTED        126
#define VARIOUS_SET_ATTACKER_STICKY_WEB_USER        127
#define VARIOUS_TRY_TO_APPLY_MIMICRY                128
#define VARIOUS_PHOTON_GEYSER_CHECK                 129
#define VARIOUS_SHELL_SIDE_ARM_CHECK                130
#define VARIOUS_TRY_NO_RETREAT                      131
#define VARIOUS_TRY_TAR_SHOT                        132
#define VARIOUS_CAN_TAR_SHOT_WORK                   133
#define VARIOUS_CHECK_POLTERGEIST                   134
#define VARIOUS_SET_OCTOLOCK                        135
#define VARIOUS_CUT_1_3_HP_RAISE_STATS              136
#define VARIOUS_TRY_END_NEUTRALIZING_GAS            137
#define VARIOUS_JUMP_IF_UNDER_200                   138
#define VARIOUS_SET_SKY_DROP                        139
#define VARIOUS_CLEAR_SKY_DROP                      140
#define VARIOUS_SKY_DROP_YAWN                       141
#define VARIOUS_JUMP_IF_CANT_FLING                  142
#define VARIOUS_JUMP_IF_HOLD_EFFECT                 143
#define VARIOUS_CURE_CERTAIN_STATUSES               144
#define VARIOUS_TRY_RESET_NEGATIVE_STAT_STAGES      145
#define VARIOUS_JUMP_IF_LAST_USED_ITEM_BERRY        146
#define VARIOUS_JUMP_IF_LAST_USED_ITEM_HOLD_EFFECT  147
#define VARIOUS_SAVE_BATTLER_ITEM                   148
#define VARIOUS_RESTORE_BATTLER_ITEM                149
#define VARIOUS_BATTLER_ITEM_TO_LAST_USED_ITEM      150
#define VARIOUS_GROUND_FLYING_TARGET_2XDMGFLAG      151	//new bs command  to ground flying targets if hit by my w flag 2xdmg on air
#define VARIOUS_JUMP_IF_NOT_FULL_HP					152	
#define VARIOUS_TRY_END_STENCH						153	
//#define VARIOUS_RESET_FOREWARN_ANTICIPATION_BITS	154		pretty sure don't need doing different way.
#define VARIOUS_JUMP_IF_EMERGENCY_EXITED			154		//default implement, plan to just use for wimp out
#define VARIOUS_BLANK			155 //not in updated emerlad expansion?

#define VARIOUS_SET_BEAK_BLAST                       156
#define VARIOUS_SWAP_SIDE_STATUSES                   157
#define VARIOUS_SWAP_STATS                           158
#define VARIOUS_JUMP_IF_ROD                          159
#define VARIOUS_JUMP_IF_ABSORB                       160
#define VARIOUS_JUMP_IF_MOTOR                        161
#define VARIOUS_TEATIME_INVUL                        162
#define VARIOUS_TEATIME_TARGETS                      163
#define VARIOUS_TRY_WIND_RIDER_POWER                 164
#define VARIOUS_ACTIVATE_WEATHER_CHANGE_ABILITIES    165
#define VARIOUS_ACTIVATE_TERRAIN_CHANGE_ABILITIES    166
#define VARIOUS_STORE_HEALING_WISH                   167
#define VARIOUS_HIT_SWITCH_TARGET_FAILED             168
#define VARIOUS_JUMP_IF_SHELL_TRAP                   169
#define VARIOUS_TRY_REVIVAL_BLESSING                 170
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_Z_MOVE         171
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_MEGA_EVOLUTION 172
#define VARIOUS_CAN_TELEPORT                        173 //set fr new teleport logic


// atk80, dmg manipulation
#define NEGATIVE_DMG					0
#define RECOIL_DMG					1	//udated this should do miss & immunity
#define RECOIL_MISS_DMG             9
#define DOUBLE_DMG						2
#define DMG_1_8_TARGET_HP				3
#define DMG_FULL_ATTACKER_HP			4
#define DMG_CURR_ATTACKER_HP			5
#define DMG_1_2_ATTACKER_HP				6
#define DMG_BIG_ROOT					7
#define DMG_MISTY_HEAL_BOOST		    8 // Used to calculate recoil for the Gen 4 version of Jump Kick, will tweak and instead consolidate in case 1

// Cmd_jumpifcantswitch
#define SWITCH_IGNORE_ESCAPE_PREVENTION   (1 << 7)


//equivalent of STAT_BUFF_ALLOW_PTR  just has different name
//& STAT_BUFF_NOT_PROTECT_AFFECTED

// statchange defines
#define STAT_CHANGE_ALLOW_PTR                  (1 << 0) // If set, allow use of jumpptr. Set in every use of statbuffchange		//equivalent stat_change_allow_ptr
#define STAT_CHANGE_MIRROR_ARMOR			(1 << 1)	// Stat change redirection caused by Mirror Armor ability.
#define STAT_CHANGE_NOT_PROTECT_AFFECTED    (1 << 5)
#define STAT_CHANGE_UPDATE_MOVE_EFFECT		(1 << 6)	//still don't know what does

// atk48
// stat change flags for Cmd_playstatchangeanimation
#define STAT_CHANGE_NEGATIVE             (1 << 0)
#define STAT_CHANGE_BY_TWO               (1 << 1)
#define STAT_CHANGE_MULTIPLE_STATS       (1 << 2)
#define STAT_CHANGE_DONT_CHECK_LOWER         (1 << 3)   //STAT_CHANGE_CANT_PREVENT

// stat flags for Cmd_playstatchangeanimation
#define BIT_HP                      (1 << 0)
#define BIT_ATK                     (1 << 1)
#define BIT_DEF                     (1 << 2)
#define BIT_SPEED                   (1 << 3)
#define BIT_SPATK                   (1 << 4)
#define BIT_SPDEF                   (1 << 5)
#define BIT_ACC                     (1 << 6)
#define BIT_EVASION                 (1 << 7)

enum SetMoveEffectFlags
{
    NO_FLAGS          = 0,
    EFFECT_PRIMARY    = (1 << 0),
    EFFECT_CERTAIN    = (1 << 1),
};

// cases for Cmd_moveend - Order matters!
enum MoveEndEffects
{
    MOVEEND_SET_VALUES,
    MOVEEND_PROTECT_LIKE_EFFECT,
    MOVEEND_GRUDGE,
    MOVEEND_DESTINY_BOND,
    MOVEEND_ABSORB,
    MOVEEND_RAGE,
    MOVEEND_DRAGON_RAGE,
    MOVEEND_ROOST, //needed for end turn print string after set effect
    MOVEEND_SYNCHRONIZE_TARGET,
    MOVEEND_ABILITIES,
    MOVEEND_ABILITIES_ATTACKER,
    MOVEEND_STATUS_IMMUNITY_ABILITIES, // TODO: Do berries come before????
    MOVEEND_SYNCHRONIZE_ATTACKER,
    MOVEEND_ATTACKER_INVISIBLE,
    MOVEEND_ATTACKER_VISIBLE,
    MOVEEND_TARGET_VISIBLE,
    MOVEEND_GROUND_TARGET,
    MOVEEND_SEMI_INVULNERABLE_INTERRUPT,
    MOVEEND_ITEM_EFFECTS_TARGET,
    MOVEEND_ITEM_EFFECTS_ATTACKER_1,
    MOVEEND_SYMBIOSIS,
    MOVEEND_SUBSTITUTE,
    MOVEEND_SKY_DROP_CONFUSE,
    MOVEEND_UPDATE_LAST_MOVES,
    MOVEEND_MIRROR_MOVE,
    MOVEEND_DEFROST,
    MOVEEND_NEXT_TARGET, // Everything up until here is handled for each strike of a spread move
    MOVEEND_HP_THRESHHOLD_ITEMS_TARGET, // Activation only during a multi hit move / ability (Parental Bond)
    MOVEEND_MULTIHIT_MOVE, //still unsure if I need and what does may use just for parental bond or dragon darts
    MOVEEND_MOVE_BLOCK,
    MOVEEND_ITEM_EFFECTS_ATTACKER_2,
    MOVEEND_ABILITY_BLOCK, //seems magician handled here, also moxie likes and battle bond
    MOVEEND_SHEER_FORCE, // If move is Sheer Force affected, skip to Hit Escape + One
    MOVEEND_COLOR_CHANGE, // Color Change / Berserk / Anger Shell //w my rework color change would be removed from this vsonic
    MOVEEND_KEE_MARANGA_HP_THRESHOLD_ITEM_TARGET,
    MOVEEND_RED_CARD,
    MOVEEND_EJECT_BUTTON,
    MOVEEND_LIFE_ORB_SHELL_BELL,
    MOVEEND_FORM_CHANGE, //form change after using move mega ray, for things like this think need update my idea of form change need revert party mon if in mega form and not sent out yet think of as transferring mega energy
    MOVEEND_EMERGENCY_EXIT, // need tweak to integrate with my changed version
    MOVEEND_EJECT_PACK,
    MOVEEND_HIT_ESCAPE,
    MOVEEND_ITEMS_EFFECTS_ALL,
    MOVEEND_WHITE_HERB,
    MOVEEND_OPPORTUNIST,
    MOVEEND_MIRROR_HERB,
    MOVEEND_PICKPOCKET,
    MOVEEND_THIRD_MOVE_BLOCK,
    MOVEEND_CHANGED_ITEMS,
    MOVEEND_SAME_MOVE_TURNS,
    MOVEEND_CLEAR_BITS,
    MOVEEND_DANCER,
    MOVEEND_FETCH_BALL,
    MOVEEND_PURSUIT_NEXT_ACTION,
    MOVEEND_COUNT,

    // This guarantees a correct jump if new moveends are added directly after MOVEEND_HIT_ESCAPE
    MOVEEND_JUMP_TO_HIT_ESCAPE_PLUS_ONE = (MOVEEND_HIT_ESCAPE + 1),
};

// switch cases
#define B_SWITCH_NORMAL     0
#define B_SWITCH_HIT        1   // dragon tail, circle throw
#define B_SWITCH_RED_CARD   2

enum StatusTrigger
{
    TRIGGER_ON_MOVE,
    TRIGGER_ON_ABILITY,
    TRIGGER_ON_PROTECT,
};

enum TriggerOnFieldStatus
{
    ON_ANY,
    ON_TERRAIN,
    ON_WEATHER,
};

enum HealthUpdate
{
    PASSIVE_HP_UPDATE,
    MOVE_DAMAGE_HP_UPDATE,
};

//turn these into enum later
// atk49, moveend cases
/*#define MOVE_END_PROTECT_LIKE_EFFECT			   0
#define MOVE_END_RAGE                              1
#define MOVE_END_DRAGON_RAGE                       2
#define MOVE_END_ROOST                             3
#define MOVE_END_DEFROST                           4
#define MOVE_END_SYNCHRONIZE_TARGET                5
#define MOVE_END_MOVE_END_ABILITIES                6
#define MOVE_END_ABILITIES_ATTACKER				   7 //increment above 1
#define MOVE_END_STATUS_IMMUNITY_ABILITIES         8
#define MOVE_END_SYNCHRONIZE_ATTACKER              9
#define MOVE_END_CHOICE_MOVE                       10
#define MOVE_END_CHANGED_ITEMS                     11
#define MOVE_END_ATTACKER_INVISIBLE                12
#define MOVE_END_ATTACKER_VISIBLE                  13
#define MOVE_END_TARGET_VISIBLE                    14
#define MOVE_END_GROUND_TARGET                     15 //put here so cancel sky drop stuff = swap put before 14 so can filter for air balloon held item
#define MOVE_END_SEMI_INVULNERABLE_INTERRUPT       16   //used for dig and dive to give string for effect same as effect for fly
#define MOVE_END_ITEM_EFFECTS_TARGET			   17
#define MOVE_END_MOVE_EFFECTS2					   18     //extra stuff from setmoveffect that has to be set later 
#define MOVE_END_ITEM_EFFECTS_ALL                  19
#define MOVE_END_KINGSROCK						   20  //item effect need to be bfore kingsrock for things like rocky helm I guess
#define MOVE_END_SUBSTITUTE                        21 
//only triger if curr move is a two turn move i guess
#define MOVE_END_SKY_DROP_CONFUSE				   22
#define MOVE_END_UPDATE_LAST_MOVES                 23
#define MOVE_END_MIRROR_MOVE                       24

#define MOVE_END_MULTIHIT_MOVE					   25   //added don't need, except for dragon darts but coudl potentially setup in bs maybe rename for parental bond instead?
#define MOVE_END_MAGICIAN                          26    // Occurs after final multi-hit strike, and after other items/abilities would activate
#define MOVE_END_EJECT_BUTTON                      27
#define MOVE_END_RED_CARD                          28
#define MOVE_END_EJECT_PACK                        29
#define MOVE_END_LIFEORB_SHELLBELL                 30    // Includes shell bell, throat spray, etc
#define MOVE_END_PICKPOCKET                        31
#define MOVE_END_DANCER							   32
#define MOVE_END_FETCH_BALL                        33
#define MOVE_END_EMERGENCY_EXIT					   34
#define MOVE_END_SYMBIOSIS						   35
#define MOVE_END_INFATUATION                       36  //to setup for attract hit effect, just need set STRINGID_PKMNFELLINLOVE //actually don't think need, do w moveeffect instead
#define MOVE_END_NEXT_TARGET                       37 //was last value before count, in base firered
#define MOVE_END_CLEAR_BITS						   38
#define MOVE_END_PURSUIT_NEXT_ACTION               39
#define MOVE_END_COUNT							   40
*/

#endif // GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
