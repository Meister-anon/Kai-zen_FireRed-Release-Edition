#ifndef GUARD_HOLD_EFFECTS_H
#define GUARD_HOLD_EFFECTS_H

#define HOLD_EFFECT_NONE            0
#define HOLD_EFFECT_RESTORE_HP      1
#define HOLD_EFFECT_CURE_PAR        2
#define HOLD_EFFECT_CURE_SLP        3
#define HOLD_EFFECT_CURE_PSN        4
#define HOLD_EFFECT_CURE_BRN        5
#define HOLD_EFFECT_CURE_FRZ        6
#define HOLD_EFFECT_RESTORE_PP      7
#define HOLD_EFFECT_CURE_CONFUSION  8
#define HOLD_EFFECT_CURE_STATUS     9
#define HOLD_EFFECT_CONFUSE_SPICY  10
#define HOLD_EFFECT_CONFUSE_DRY    11
#define HOLD_EFFECT_CONFUSE_SWEET  12
#define HOLD_EFFECT_CONFUSE_BITTER 13
#define HOLD_EFFECT_CONFUSE_SOUR   14
#define HOLD_EFFECT_ATTACK_UP      15
#define HOLD_EFFECT_DEFENSE_UP     16
#define HOLD_EFFECT_SPEED_UP       17
#define HOLD_EFFECT_SP_ATTACK_UP   18
#define HOLD_EFFECT_SP_DEFENSE_UP  19
#define HOLD_EFFECT_CRITICAL_UP    20
#define HOLD_EFFECT_RANDOM_STAT_UP 21
#define HOLD_EFFECT_EVASION_UP     22
#define HOLD_EFFECT_RESTORE_STATS  23
#define HOLD_EFFECT_MACHO_BRACE    24  //post ev change, make general training tool, will add to every stat rather than being targetted ads about +30 bst to all.
#define HOLD_EFFECT_EXP_SHARE      25
#define HOLD_EFFECT_QUICK_CLAW     26
#define HOLD_EFFECT_HAPPINESS_UP   27
#define HOLD_EFFECT_MENTAL_HERB    28
#define HOLD_EFFECT_CHOICE_BAND    29
#define HOLD_EFFECT_FLINCH         30
#define HOLD_EFFECT_BUG_POWER      31
#define HOLD_EFFECT_DOUBLE_PRIZE   32
#define HOLD_EFFECT_CLEANSE_TAG    33   //used for cleanse tag only, no real effect rename hold_effect_cleanse tag, add to battle_util.c to do weaker version of shed skin
#define HOLD_EFFECT_SOUL_DEW       34
#define HOLD_EFFECT_DEEP_SEA_TOOTH 35
#define HOLD_EFFECT_DEEP_SEA_SCALE 36
#define HOLD_EFFECT_CAN_ALWAYS_RUN 37
#define HOLD_EFFECT_PREVENT_EVOLVE 38
#define HOLD_EFFECT_FOCUS_BAND     39
#define HOLD_EFFECT_LUCKY_EGG      40
#define HOLD_EFFECT_SCOPE_LENS     41
#define HOLD_EFFECT_STEEL_POWER    42
#define HOLD_EFFECT_LEFTOVERS      43
#define HOLD_EFFECT_DRAGON_SCALE   44
#define HOLD_EFFECT_LIGHT_BALL     45
#define HOLD_EFFECT_GROUND_POWER   46
#define HOLD_EFFECT_ROCK_POWER     47   //type boosters not gems, hard stone
#define HOLD_EFFECT_GRASS_POWER    48   //grass seed
#define HOLD_EFFECT_DARK_POWER     49
#define HOLD_EFFECT_FIGHTING_POWER 50
#define HOLD_EFFECT_ELECTRIC_POWER 51
#define HOLD_EFFECT_WATER_POWER    52
#define HOLD_EFFECT_FLYING_POWER   53
#define HOLD_EFFECT_POISON_POWER   54
#define HOLD_EFFECT_ICE_POWER      55
#define HOLD_EFFECT_GHOST_POWER    56
#define HOLD_EFFECT_PSYCHIC_POWER  57
#define HOLD_EFFECT_FIRE_POWER     58
#define HOLD_EFFECT_DRAGON_POWER   59
#define HOLD_EFFECT_NORMAL_POWER   60
#define HOLD_EFFECT_UP_GRADE       61
#define HOLD_EFFECT_SHELL_BELL     62
#define HOLD_EFFECT_LUCKY_PUNCH    63
#define HOLD_EFFECT_METAL_POWDER   64
#define HOLD_EFFECT_THICK_CLUB     65
#define HOLD_EFFECT_LEEK           66

// Gen4 hold effects.
#define HOLD_EFFECT_CHOICE_SCARF   67
#define HOLD_EFFECT_CHOICE_SPECS   68
#define HOLD_EFFECT_DAMP_ROCK      69   //change to weather extenders , boost type move 10%, use itemid of held item rather than hold effect
#define HOLD_EFFECT_GRIP_CLAW      70
#define HOLD_EFFECT_HEAT_ROCK      71
#define HOLD_EFFECT_ICY_ROCK       72
#define HOLD_EFFECT_LIGHT_CLAY     73
#define HOLD_EFFECT_SMOOTH_ROCK    74
#define HOLD_EFFECT_POWER_HERB     75
#define HOLD_EFFECT_BIG_ROOT       76
#define HOLD_EFFECT_EXPERT_BELT    77
#define HOLD_EFFECT_LIFE_ORB       78
#define HOLD_EFFECT_METRONOME      79
#define HOLD_EFFECT_MUSCLE_BAND    80
#define HOLD_EFFECT_WIDE_LENS      81
#define HOLD_EFFECT_WISE_GLASSES   82
#define HOLD_EFFECT_ZOOM_LENS      83
#define HOLD_EFFECT_LAGGING_TAIL   84
#define HOLD_EFFECT_FOCUS_SASH     85
#define HOLD_EFFECT_FLAME_ORB      86
#define HOLD_EFFECT_TOXIC_ORB      87
#define HOLD_EFFECT_STICKY_BARB    88
#define HOLD_EFFECT_IRON_BALL      89
#define HOLD_EFFECT_BLACK_SLUDGE   90
#define HOLD_EFFECT_DESTINY_KNOT   91
#define HOLD_EFFECT_SHED_SHELL     92
#define HOLD_EFFECT_QUICK_POWDER   93
#define HOLD_EFFECT_ADAMANT_ORB    94
#define HOLD_EFFECT_LUSTROUS_ORB   95
#define HOLD_EFFECT_GRISEOUS_ORB   96
#define HOLD_EFFECT_GRACIDEA       97
#define HOLD_EFFECT_RESIST_BERRY   98
#define HOLD_EFFECT_POWER_ITEM     99
#define HOLD_EFFECT_RESTORE_PCT_HP 100
#define HOLD_EFFECT_MICLE_BERRY    101
#define HOLD_EFFECT_CUSTAP_BERRY   102
#define HOLD_EFFECT_JABOCA_BERRY   103
#define HOLD_EFFECT_ROWAP_BERRY    104
#define HOLD_EFFECT_KEE_BERRY      105
#define HOLD_EFFECT_MARANGA_BERRY  106
#define HOLD_EFFECT_PLATE          107

// Gen5 hold effects
#define HOLD_EFFECT_FLOAT_STONE    117
#define HOLD_EFFECT_EVIOLITE       118
#define HOLD_EFFECT_ASSAULT_VEST   119
#define HOLD_EFFECT_DRIVE          120
#define HOLD_EFFECT_GEMS           121
#define HOLD_EFFECT_ROCKY_HELMET   122
#define HOLD_EFFECT_AIR_BALLOON    123
#define HOLD_EFFECT_RED_CARD       124
#define HOLD_EFFECT_RING_TARGET    125
#define HOLD_EFFECT_BINDING_BAND   126
#define HOLD_EFFECT_EJECT_BUTTON   127
#define HOLD_EFFECT_ABSORB_BULB    128
#define HOLD_EFFECT_CELL_BATTERY   129

// Gen6 hold effects
#define HOLD_EFFECT_FAIRY_POWER     139 //since made its own type potentially need make sound_power item
#define HOLD_EFFECT_MEGA_STONE      140 //idea call it deci bell?
#define HOLD_EFFECT_SAFETY_GOGGLES  141
#define HOLD_EFFECT_LUMINOUS_MOSS   142
#define HOLD_EFFECT_SNOWBALL        143
#define HOLD_EFFECT_WEAKNESS_POLICY 144
#define HOLD_EFFECT_PRIMAL_ORB      145

// Gen7 hold effects
#define HOLD_EFFECT_PROTECTIVE_PADS  154
#define HOLD_EFFECT_TERRAIN_EXTENDER 155
#define HOLD_EFFECT_SEEDS            156
#define HOLD_EFFECT_ADRENALINE_ORB   157
#define HOLD_EFFECT_MEMORY           158
#define HOLD_EFFECT_Z_CRYSTAL        159



// Gen8 hold effects
#define HOLD_EFFECT_UTILITY_UMBRELLA    169
#define HOLD_EFFECT_EJECT_PACK          170
#define HOLD_EFFECT_ROOM_SERVICE        171
#define HOLD_EFFECT_BLUNDER_POLICY      172
#define HOLD_EFFECT_HEAVY_DUTY_BOOTS    173
#define HOLD_EFFECT_THROAT_SPRAY        174
#define HOLD_EFFECT_ULTIMA_BRACE		175 // block exp multiply ev gain *exp=0		I guess could just be stronger version of my new macho brace effect?
#define HOLD_EFFECT_POWER_WEIGHT		176
#define HOLD_EFFECT_POWER_BRACER		177
#define HOLD_EFFECT_POWER_BELT			178
#define HOLD_EFFECT_POWER_ANKLET		179
#define HOLD_EFFECT_POWER_LENS			180
#define HOLD_EFFECT_POWER_BAND			181
//vsonic
#define HOLD_EFFECT_POWERITEM 182   // since stat reaise is based on secondary id, pretty sure can just use this and remoe all other power item hold effects

#define HOLD_EFFECT_CURE_ATTRACT		183

//custom hold effects
#define HOLD_EFFECT_SOUND_POWER     184   //call deci bell (I think)
#define HOLD_EFFECT_SNOW_GLOBE      185   //ice orb,
/*#define HOLD_EFFECT_ALOLAN_SAND     184
#define HOLD_EFFECT_GALAR_SAND      185
#define HOLD_EFFECT_HISUIAN_SAND    186
#define HOLD_EFFECT_CEFERIA_SAND    187*/   
//don't need these realized only need distinct hold effects, for effects that are used in-battle

// Terrain seed params
#define HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN  0
#define HOLD_EFFECT_PARAM_GRASSY_TERRAIN    1
#define HOLD_EFFECT_PARAM_MISTY_TERRAIN     2
#define HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN   3


//#define HOLD_EFFECT_EV_SHACKLES	   176 // block ev gain, either just that with 0 drawback or double exp gain.


#define HOLD_EFFECT_CHOICE(holdEffect)((holdEffect == HOLD_EFFECT_CHOICE_BAND || holdEffect == HOLD_EFFECT_CHOICE_SCARF || holdEffect == HOLD_EFFECT_CHOICE_SPECS))


#endif // GUARD_HOLD_EFFECTS_H
