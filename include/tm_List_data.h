//Recomendation, if you want to remove things from the tm or hm lists//
//Delete them rather than commenting them out //

//dont understand but seems to be directly tied to changing size of this array
//if I remove substitute then add attract there's no issue?
//idk whats happening may need to just move this back to pokemon.c
//don't want to though would rather get this working
/*
static const u16 sUniversalMoves[] =
{
    //MOVE_ATTRACT,// everything breaks because of this??
    MOVE_BIDE,
    MOVE_FRUSTRATION,
    MOVE_HIDDEN_POWER,
    MOVE_MIMIC,
    MOVE_NATURAL_GIFT,
    MOVE_RAGE,
    MOVE_RETURN,
    MOVE_SECRET_POWER,
    MOVE_SUBSTITUTE,
    MOVE_TERA_BLAST,
};
*/

//new macro to include tmhm order within bag
#define TMHM(id, order) {.itemId = id, .tmhmId = order}

struct TmHmOrder
{
    u16 itemId;
    u16 tmhmId;
};

//Guide Notes//
//** HM list MUST stay above TM list **//
//** Ensure no whitespace after move ids, it'll interupt py script **/
//* Use Shift + Click to highlight range to check spacing *//
//** To add to the lists in this file add the move id where you want it **//
//** And ensure itemdata is setup src/data/items.h properly for a TM or HM**//
//** pocket must be POCKET_TM_CASE, TMs have importance 0, HMs use importance 1 **//
#define TMHM_LIST
static const u16 gHM_Moves[] =
{
    MOVE_CUT,
    MOVE_FLY,
    MOVE_SURF,
    MOVE_STRENGTH,
    MOVE_FLASH,
    MOVE_ROCK_SMASH,
    MOVE_WATERFALL,
    MOVE_DIVE,
    MOVE_ROCK_CLIMB,
    LIST_END
};


static const u16 gTM_Moves[] =
{
    MOVE_FOCUS_PUNCH,
    MOVE_DRAGON_CLAW,
    MOVE_WATER_PULSE,
    MOVE_CALM_MIND,
    MOVE_ROAR,
    MOVE_TOXIC,
    MOVE_HAIL,
    MOVE_BULK_UP,
    MOVE_BULLET_SEED,
    MOVE_HIDDEN_POWER,
    MOVE_SUNNY_DAY,
    MOVE_TAUNT,
    MOVE_ICE_BEAM,
    MOVE_BLIZZARD,
    MOVE_HYPER_BEAM,
    MOVE_LIGHT_SCREEN,
    MOVE_PROTECT,
    MOVE_RAIN_DANCE,
    MOVE_GIGA_DRAIN,
    MOVE_SAFEGUARD,
    MOVE_FRUSTRATION,
    MOVE_SOLAR_BEAM,
    MOVE_IRON_TAIL,
    MOVE_THUNDERBOLT,
    MOVE_THUNDER,
    MOVE_EARTHQUAKE,
    MOVE_RETURN,
    MOVE_DIG,
    MOVE_PSYCHIC,
    MOVE_SHADOW_BALL,
    MOVE_BRICK_BREAK,
    MOVE_DOUBLE_TEAM,
    MOVE_REFLECT,
    MOVE_SHOCK_WAVE,
    MOVE_FLAMETHROWER,
    MOVE_SLUDGE_BOMB,
    MOVE_SANDSTORM,
    MOVE_FIRE_BLAST,
    MOVE_ROCK_TOMB,
    MOVE_AERIAL_ACE,
    MOVE_TORMENT,
    MOVE_FACADE,
    MOVE_SECRET_POWER,
    MOVE_REST,
    MOVE_ATTRACT,
    MOVE_THIEF,
    MOVE_STEEL_WING,
    MOVE_SKILL_SWAP,
    MOVE_SNATCH,
    MOVE_OVERHEAT,
    MOVE_PSYCHO_BOOST,
    MOVE_WILD_CHARGE,
    MOVE_ROOST,
    MOVE_TELEPORT,
    MOVE_QUASH,
    MOVE_HONE_CLAWS,
    MOVE_BRINE,
    MOVE_CHARGE_BEAM,
    MOVE_ENDURE,
    MOVE_DRAGON_PULSE,
    MOVE_THUNDER_PUNCH,
    MOVE_FIRE_PUNCH,
    MOVE_ICE_PUNCH,
    MOVE_SHADOW_PUNCH,
    MOVE_POISON_JAB,
    MOVE_DRAIN_PUNCH,
    MOVE_COMET_PUNCH,
    MOVE_WILL_O_WISP,
    MOVE_FLASH_FREEZE,
    MOVE_FOCUS_BLAST,
    MOVE_MEMENTO,
    MOVE_SILVER_WIND,
    MOVE_OMINOUS_WIND,
    MOVE_FLING,
    MOVE_EMBARGO,
    MOVE_RECYCLE,
    MOVE_HEAL_BLOCK,
    MOVE_THUNDER_FANG,
    MOVE_FIRE_FANG,
    MOVE_ICE_FANG,
    MOVE_SUPERPOWER,
    MOVE_EXPLOSION,
    MOVE_SHADOW_CLAW,
    MOVE_NIGHT_SLASH,
    MOVE_RAZOR_LEAF,
    MOVE_X_SCISSOR,
    MOVE_CROSS_POISON,
    MOVE_PSYCHO_CUT,
    MOVE_FALSE_SWIPE,
    MOVE_PAYBACK,
    MOVE_GIGA_IMPACT,
    MOVE_ROCK_POLISH,
    MOVE_MUD_SPORT,
    MOVE_WATER_SPORT,
    MOVE_AURORA_VEIL,
    MOVE_STONE_EDGE,
    MOVE_REVENGE,
    MOVE_AVALANCHE,
    MOVE_THUNDER_WAVE,
    MOVE_GLARE,
    MOVE_GYRO_BALL,
    MOVE_ELECTRO_BALL,
    MOVE_SWORDS_DANCE,
    MOVE_POWER_TRICK,
    MOVE_POWER_SHIFT,
    MOVE_POWER_SWAP,
    MOVE_GUARD_SWAP,
    MOVE_SPEED_SWAP,
    MOVE_STEALTH_ROCK,
    MOVE_SPIKES,
    MOVE_FIRE_SPIN,
    MOVE_SAND_TOMB,
    MOVE_WHIRLPOOL,
    MOVE_SWARM,
    MOVE_PSYCH_UP,
    MOVE_CAPTIVATE,
    MOVE_CONFIDE,
    MOVE_FAKE_TEARS,
    MOVE_ACID_SPRAY,
    MOVE_DARK_PULSE,
    MOVE_ROCK_THROW,
    MOVE_POWER_GEM,
    MOVE_SLEEP_TALK,
    MOVE_SNORE,
    MOVE_NATURAL_GIFT,
    MOVE_GRASS_KNOT,
    MOVE_SWAGGER,
    MOVE_FLATTER,
    MOVE_PLUCK,
    MOVE_BUG_BITE,
    MOVE_U_TURN,
    MOVE_VOLT_SWITCH,
    MOVE_FLIP_TURN,
    MOVE_UP_ROOT,
    MOVE_DIVE_BOMB,
    MOVE_SUBSTITUTE,
    MOVE_FLASH_CANNON,
    MOVE_AGILITY,
    MOVE_TRICK_ROOM,
    MOVE_MAGIC_ROOM,
    MOVE_WONDER_ROOM,
    MOVE_GRAVITY,
    MOVE_DRAINING_KISS,
    MOVE_LEECH_LIFE,
    MOVE_FROST_BREATH,
    MOVE_MOONDANCE,
    MOVE_ACID_RAIN,
    MOVE_WEATHER_BALL,
    MOVE_FLAME_CHARGE,
    MOVE_TRAILBLAZE,
    MOVE_DUAL_WINGBEAT,
    MOVE_KNOCK_OFF,
    MOVE_BEAT_UP,
    MOVE_RAGE,
    MOVE_MAGIC_COAT,
    MOVE_ICICLE_SPEAR,
    MOVE_ACROBATICS,
    MOVE_AEROBLAST,
    MOVE_ASSURANCE,
    MOVE_SOLAR_BLADE,
    MOVE_ICY_WIND,
    MOVE_METAL_CLAW,
    MOVE_HOLD_BACK,
    MOVE_HEADBUTT,
    MOVE_HI_JUMP_KICK,
    MOVE_DOUBLE_EDGE,
    MOVE_MISTY_EXPLOSION,
    MOVE_SNOWBALL,
    MOVE_ENERGY_BALL,
    MOVE_CELEBRATE,
    LIST_END
};


//ok seems pretty dumb
//but defining static globally seems to have worked...
//it compiles at least

#define NUM_TECHNICAL_MACHINES (ARRAY_COUNT(gTM_Moves) - 1) //change to 120 later  / or more plan to add on to tms I think for ease spreading certain moves
#define NUM_HIDDEN_MACHINES    (ARRAY_COUNT(gHM_Moves) - 1)

//add sound moves to list,
//round, echoed voice, hyper voice
//also smack down and think focus blast
//think give echoed voice to zubat line, as learned move or tm?
//hmm both yeah both
//need to go over scarlett violet tms and add a few 
//adding rock slide for hitmonlee 
//add gunk shot to list, poison types have WOEFULLY bad stab options *facepalm
//also venom drench  & sludge wave
//draco meteor and dragon ascent will be tutor moves
//want add other move I added as a screan to list alongside reflect and light screen
//magic coat that's it
//add heatwave
//add scorching sands
//need add flatter aroud swagger
//add flash freeze  ice will o wisp and give to lunatone
//add obstruct? or keep that in learnsets sparingly?
//venoshock
//power up punch need add
//add or may just give to mon I want in learnset
//yeah think I want punch just in learnset
//instead want ancient power as tm, simpler
//for breeding mon that evolve via ancient power

//also toss in psycho boost, but be sparing with destribution
//release deoxys signature move as Psychic type Close Combat
//power excused because not 100 acc

//add earth power , body slam
// add MOVE_BREAKING_SWIPE
//consider rename this file to item_List_data
//for adding berry data to this
//long as keep above tm hm stuff should have no effect
//on generated data below, can get benefit of dynamic berry list
//as well



/////////FILE_END///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//
// DO NOT MODIFY BELOW THE LINE! It is auto-generated from scripts_py/tm_list.py
//


static const struct TmHmOrder gTMHM_List[] = {
    [ITEM_HM01] = TMHM(ITEM_HM01, 0),
    [ITEM_HM02] = TMHM(ITEM_HM02, 1),
    [ITEM_HM03] = TMHM(ITEM_HM03, 2),
    [ITEM_HM04] = TMHM(ITEM_HM04, 3),
    [ITEM_HM05] = TMHM(ITEM_HM05, 4),
    [ITEM_HM06] = TMHM(ITEM_HM06, 5),
    [ITEM_HM07] = TMHM(ITEM_HM07, 6),
    [ITEM_HM08] = TMHM(ITEM_HM08, 7),
    [ITEM_HM09] = TMHM(ITEM_HM09, 8),
    [ITEM_TM01] = TMHM(ITEM_TM01, 9),
    [ITEM_TM02] = TMHM(ITEM_TM02, 10),
    [ITEM_TM03] = TMHM(ITEM_TM03, 11),
    [ITEM_TM04] = TMHM(ITEM_TM04, 12),
    [ITEM_TM05] = TMHM(ITEM_TM05, 13),
    [ITEM_TM06] = TMHM(ITEM_TM06, 14),
    [ITEM_TM07] = TMHM(ITEM_TM07, 15),
    [ITEM_TM08] = TMHM(ITEM_TM08, 16),
    [ITEM_TM09] = TMHM(ITEM_TM09, 17),
    [ITEM_TM10] = TMHM(ITEM_TM10, 18),
    [ITEM_TM11] = TMHM(ITEM_TM11, 19),
    [ITEM_TM12] = TMHM(ITEM_TM12, 20),
    [ITEM_TM13] = TMHM(ITEM_TM13, 21),
    [ITEM_TM14] = TMHM(ITEM_TM14, 22),
    [ITEM_TM15] = TMHM(ITEM_TM15, 23),
    [ITEM_TM16] = TMHM(ITEM_TM16, 24),
    [ITEM_TM17] = TMHM(ITEM_TM17, 25),
    [ITEM_TM18] = TMHM(ITEM_TM18, 26),
    [ITEM_TM19] = TMHM(ITEM_TM19, 27),
    [ITEM_TM20] = TMHM(ITEM_TM20, 28),
    [ITEM_TM21] = TMHM(ITEM_TM21, 29),
    [ITEM_TM22] = TMHM(ITEM_TM22, 30),
    [ITEM_TM23] = TMHM(ITEM_TM23, 31),
    [ITEM_TM24] = TMHM(ITEM_TM24, 32),
    [ITEM_TM25] = TMHM(ITEM_TM25, 33),
    [ITEM_TM26] = TMHM(ITEM_TM26, 34),
    [ITEM_TM27] = TMHM(ITEM_TM27, 35),
    [ITEM_TM28] = TMHM(ITEM_TM28, 36),
    [ITEM_TM29] = TMHM(ITEM_TM29, 37),
    [ITEM_TM30] = TMHM(ITEM_TM30, 38),
    [ITEM_TM31] = TMHM(ITEM_TM31, 39),
    [ITEM_TM32] = TMHM(ITEM_TM32, 40),
    [ITEM_TM33] = TMHM(ITEM_TM33, 41),
    [ITEM_TM34] = TMHM(ITEM_TM34, 42),
    [ITEM_TM35] = TMHM(ITEM_TM35, 43),
    [ITEM_TM36] = TMHM(ITEM_TM36, 44),
    [ITEM_TM37] = TMHM(ITEM_TM37, 45),
    [ITEM_TM38] = TMHM(ITEM_TM38, 46),
    [ITEM_TM39] = TMHM(ITEM_TM39, 47),
    [ITEM_TM40] = TMHM(ITEM_TM40, 48),
    [ITEM_TM41] = TMHM(ITEM_TM41, 49),
    [ITEM_TM42] = TMHM(ITEM_TM42, 50),
    [ITEM_TM43] = TMHM(ITEM_TM43, 51),
    [ITEM_TM44] = TMHM(ITEM_TM44, 52),
    [ITEM_TM45] = TMHM(ITEM_TM45, 53),
    [ITEM_TM46] = TMHM(ITEM_TM46, 54),
    [ITEM_TM47] = TMHM(ITEM_TM47, 55),
    [ITEM_TM48] = TMHM(ITEM_TM48, 56),
    [ITEM_TM49] = TMHM(ITEM_TM49, 57),
    [ITEM_TM50] = TMHM(ITEM_TM50, 58),
    [ITEM_TM_PSYCHO_BOOST] = TMHM(ITEM_TM_PSYCHO_BOOST, 59),
    [ITEM_TM51] = TMHM(ITEM_TM51, 60),
    [ITEM_TM52] = TMHM(ITEM_TM52, 61),
    [ITEM_TM53] = TMHM(ITEM_TM53, 62),
    [ITEM_TM54] = TMHM(ITEM_TM54, 63),
    [ITEM_TM55] = TMHM(ITEM_TM55, 64),
    [ITEM_TM56] = TMHM(ITEM_TM56, 65),
    [ITEM_TM57] = TMHM(ITEM_TM57, 66),
    [ITEM_TM58] = TMHM(ITEM_TM58, 67),
    [ITEM_TM59] = TMHM(ITEM_TM59, 68),
    [ITEM_TM60] = TMHM(ITEM_TM60, 69),
    [ITEM_TM61] = TMHM(ITEM_TM61, 70),
    [ITEM_TM62] = TMHM(ITEM_TM62, 71),
    [ITEM_TM63] = TMHM(ITEM_TM63, 72),
    [ITEM_TM64] = TMHM(ITEM_TM64, 73),
    [ITEM_TM65] = TMHM(ITEM_TM65, 74),
    [ITEM_TM66] = TMHM(ITEM_TM66, 75),
    [ITEM_TM67] = TMHM(ITEM_TM67, 76),
    [ITEM_TM_FLASH_FREEZE] = TMHM(ITEM_TM_FLASH_FREEZE, 77),
    [ITEM_TM_FOCUS_BLAST] = TMHM(ITEM_TM_FOCUS_BLAST, 78),
    [ITEM_TM68] = TMHM(ITEM_TM68, 79),
    [ITEM_TM69] = TMHM(ITEM_TM69, 80),
    [ITEM_TM70] = TMHM(ITEM_TM70, 81),
    [ITEM_TM71] = TMHM(ITEM_TM71, 82),
    [ITEM_TM72] = TMHM(ITEM_TM72, 83),
    [ITEM_TM73] = TMHM(ITEM_TM73, 84),
    [ITEM_TM74] = TMHM(ITEM_TM74, 85),
    [ITEM_TM75] = TMHM(ITEM_TM75, 86),
    [ITEM_TM76] = TMHM(ITEM_TM76, 87),
    [ITEM_TM77] = TMHM(ITEM_TM77, 88),
    [ITEM_TM_SUPERPOWER] = TMHM(ITEM_TM_SUPERPOWER, 89),
    [ITEM_TM78] = TMHM(ITEM_TM78, 90),
    [ITEM_TM79] = TMHM(ITEM_TM79, 91),
    [ITEM_TM80] = TMHM(ITEM_TM80, 92),
    [ITEM_TM81] = TMHM(ITEM_TM81, 93),
    [ITEM_TM82] = TMHM(ITEM_TM82, 94),
    [ITEM_TM83] = TMHM(ITEM_TM83, 95),
    [ITEM_TM84] = TMHM(ITEM_TM84, 96),
    [ITEM_TM85] = TMHM(ITEM_TM85, 97),
    [ITEM_TM86] = TMHM(ITEM_TM86, 98),
    [ITEM_TM87] = TMHM(ITEM_TM87, 99),
    [ITEM_TM88] = TMHM(ITEM_TM88, 100),
    [ITEM_TM89] = TMHM(ITEM_TM89, 101),
    [ITEM_TM90] = TMHM(ITEM_TM90, 102),
    [ITEM_TM91] = TMHM(ITEM_TM91, 103),
    [ITEM_TM92] = TMHM(ITEM_TM92, 104),
    [ITEM_TM93] = TMHM(ITEM_TM93, 105),
    [ITEM_TM94] = TMHM(ITEM_TM94, 106),
    [ITEM_TM95] = TMHM(ITEM_TM95, 107),
    [ITEM_TM96] = TMHM(ITEM_TM96, 108),
    [ITEM_TM97] = TMHM(ITEM_TM97, 109),
    [ITEM_TM98] = TMHM(ITEM_TM98, 110),
    [ITEM_TM99] = TMHM(ITEM_TM99, 111),
    [ITEM_TM100] = TMHM(ITEM_TM100, 112),
    [ITEM_TM101] = TMHM(ITEM_TM101, 113),
    [ITEM_TM102] = TMHM(ITEM_TM102, 114),
    [ITEM_TM103] = TMHM(ITEM_TM103, 115),
    [ITEM_TM104] = TMHM(ITEM_TM104, 116),
    [ITEM_TM105] = TMHM(ITEM_TM105, 117),
    [ITEM_TM106] = TMHM(ITEM_TM106, 118),
    [ITEM_TM107] = TMHM(ITEM_TM107, 119),
    [ITEM_TM108] = TMHM(ITEM_TM108, 120),
    [ITEM_TM109] = TMHM(ITEM_TM109, 121),
    [ITEM_TM110] = TMHM(ITEM_TM110, 122),
    [ITEM_TM111] = TMHM(ITEM_TM111, 123),
    [ITEM_TM112] = TMHM(ITEM_TM112, 124),
    [ITEM_TM113] = TMHM(ITEM_TM113, 125),
    [ITEM_TM114] = TMHM(ITEM_TM114, 126),
    [ITEM_TM115] = TMHM(ITEM_TM115, 127),
    [ITEM_TM116] = TMHM(ITEM_TM116, 128),
    [ITEM_TM117] = TMHM(ITEM_TM117, 129),
    [ITEM_TM118] = TMHM(ITEM_TM118, 130),
    [ITEM_TM119] = TMHM(ITEM_TM119, 131),
    [ITEM_TM120] = TMHM(ITEM_TM120, 132),
    [ITEM_TM121] = TMHM(ITEM_TM121, 133),
    [ITEM_TM122] = TMHM(ITEM_TM122, 134),
    [ITEM_TM123] = TMHM(ITEM_TM123, 135),
    [ITEM_TM_FLATTER] = TMHM(ITEM_TM_FLATTER, 136),
    [ITEM_TM124] = TMHM(ITEM_TM124, 137),
    [ITEM_TM125] = TMHM(ITEM_TM125, 138),
    [ITEM_TM126] = TMHM(ITEM_TM126, 139),
    [ITEM_TM127] = TMHM(ITEM_TM127, 140),
    [ITEM_TM128] = TMHM(ITEM_TM128, 141),
    [ITEM_TM129] = TMHM(ITEM_TM129, 142),
    [ITEM_TM130] = TMHM(ITEM_TM130, 143),
    [ITEM_TM131] = TMHM(ITEM_TM131, 144),
    [ITEM_TM132] = TMHM(ITEM_TM132, 145),
    [ITEM_TM133] = TMHM(ITEM_TM133, 146),
    [ITEM_TM134] = TMHM(ITEM_TM134, 147),
    [ITEM_TM135] = TMHM(ITEM_TM135, 148),
    [ITEM_TM136] = TMHM(ITEM_TM136, 149),
    [ITEM_TM137] = TMHM(ITEM_TM137, 150),
    [ITEM_TM138] = TMHM(ITEM_TM138, 151),
    [ITEM_TM139] = TMHM(ITEM_TM139, 152),
    [ITEM_TM140] = TMHM(ITEM_TM140, 153),
    [ITEM_TM141] = TMHM(ITEM_TM141, 154),
    [ITEM_TM142] = TMHM(ITEM_TM142, 155),
    [ITEM_TM_TRAILBLAZE] = TMHM(ITEM_TM_TRAILBLAZE, 156),
    [ITEM_TM143] = TMHM(ITEM_TM143, 157),
    [ITEM_TM144] = TMHM(ITEM_TM144, 158),
    [ITEM_TM145] = TMHM(ITEM_TM145, 159),
    [ITEM_TM146] = TMHM(ITEM_TM146, 160),
    [ITEM_TM147] = TMHM(ITEM_TM147, 161),
    [ITEM_TM148] = TMHM(ITEM_TM148, 162),
    [ITEM_TM149] = TMHM(ITEM_TM149, 163),
    [ITEM_TM_AEROBLAST] = TMHM(ITEM_TM_AEROBLAST, 164),
    [ITEM_TM150] = TMHM(ITEM_TM150, 165),
    [ITEM_TM151] = TMHM(ITEM_TM151, 166),
    [ITEM_TM152] = TMHM(ITEM_TM152, 167),
    [ITEM_TM153] = TMHM(ITEM_TM153, 168),
    [ITEM_TM154] = TMHM(ITEM_TM154, 169),
    [ITEM_TM155] = TMHM(ITEM_TM155, 170),
    [ITEM_TM156] = TMHM(ITEM_TM156, 171),
    [ITEM_TM157] = TMHM(ITEM_TM157, 172),
    [ITEM_TM158] = TMHM(ITEM_TM158, 173),
    [ITEM_TM159] = TMHM(ITEM_TM159, 174),
    [ITEM_TM160] = TMHM(ITEM_TM160, 175),
    [ITEM_TM161] = TMHM(ITEM_TM161, 176),
};