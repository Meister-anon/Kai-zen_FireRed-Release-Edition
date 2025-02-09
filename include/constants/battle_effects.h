#ifndef GUARD_CONSTANTS_BATTLE_EFFECTS_H
#define GUARD_CONSTANTS_BATTLE_EFFECTS_H

#define EFFECT_HIT 0
#define EFFECT_SLEEP 1
#define EFFECT_POISON_HIT 2
#define EFFECT_ABSORB 3
#define EFFECT_BURN_HIT 4
#define EFFECT_FREEZE_HIT 5
#define EFFECT_PARALYZE_HIT 6
#define EFFECT_EXPLOSION 7
#define EFFECT_DREAM_EATER 8
#define EFFECT_MIRROR_MOVE 9
#define EFFECT_ATTACK_UP 10
#define EFFECT_DEFENSE_UP 11
#define EFFECT_SPEED_UP 12
#define EFFECT_SPECIAL_ATTACK_UP 13
#define EFFECT_SPECIAL_DEFENSE_UP 14 //unused..actually used in later gen
#define EFFECT_ACCURACY_UP 15 //unused..actually used in later gen
#define EFFECT_EVASION_UP 16
#define EFFECT_ALWAYS_HIT 17
#define EFFECT_ATTACK_DOWN 18
#define EFFECT_DEFENSE_DOWN 19
#define EFFECT_SPEED_DOWN 20
#define EFFECT_SPECIAL_ATTACK_DOWN 21  // unused..actually used in later gen
#define EFFECT_SPECIAL_DEFENSE_DOWN 22  // unused..actually used in later gen
#define EFFECT_ACCURACY_DOWN 23
#define EFFECT_EVASION_DOWN 24
#define EFFECT_HAZE 25
#define EFFECT_BIDE 26
#define EFFECT_RAMPAGE 27
#define EFFECT_ROAR 28
#define EFFECT_MULTI_HIT 29
#define EFFECT_CONVERSION 30
#define EFFECT_FLINCH_HIT 31
#define EFFECT_RESTORE_HP 32
#define EFFECT_TOXIC 33
#define EFFECT_PAY_DAY 34
#define EFFECT_LIGHT_SCREEN 35
#define EFFECT_TRI_ATTACK 36
#define EFFECT_REST 37
#define EFFECT_OHKO 38
#define EFFECT_RAZOR_WIND 39
#define EFFECT_SUPER_FANG 40
#define EFFECT_DRAGON_RAGE 41
#define EFFECT_TRAP 42	//keep for bind & wrap, need separate whirlpool effects & check how i have effects implemented this also effects move_thunder_cage a regi eleki exclusive
#define EFFECT_HIGH_CRITICAL 43	//CAN replace, new implementation is to use flag for high crit no move uses this anymore.
#define EFFECT_DOUBLE_HIT 44
#define EFFECT_RECOIL_IF_MISS 45
#define EFFECT_MIST 46
#define EFFECT_FOCUS_ENERGY 47
#define EFFECT_RECOIL 48
#define EFFECT_CONFUSE 49
#define EFFECT_ATTACK_UP_2 50
#define EFFECT_DEFENSE_UP_2 51
#define EFFECT_SPEED_UP_2 52
#define EFFECT_SPECIAL_ATTACK_UP_2 53
#define EFFECT_SPECIAL_DEFENSE_UP_2 54
#define EFFECT_ACCURACY_UP_2 55 // added
#define EFFECT_EVASION_UP_2 56 // added - adding for trench run -since want to be one time boost make it call bs for evasion drop from function command
#define EFFECT_TRANSFORM 57
#define EFFECT_ATTACK_DOWN_2 58
#define EFFECT_DEFENSE_DOWN_2 59
#define EFFECT_SPEED_DOWN_2 60
#define EFFECT_SPECIAL_ATTACK_DOWN_2 61
#define EFFECT_SPECIAL_DEFENSE_DOWN_2 62
#define EFFECT_ACCURACY_DOWN_2 63 //added
#define EFFECT_EVASION_DOWN_2 64 //added
#define EFFECT_REFLECT 65
#define EFFECT_POISON 66
#define EFFECT_PARALYZE 67
#define EFFECT_ATTACK_DOWN_HIT 68
#define EFFECT_DEFENSE_DOWN_HIT 69
#define EFFECT_SPEED_DOWN_HIT 70
#define EFFECT_SPECIAL_ATTACK_DOWN_HIT 71
#define EFFECT_SPECIAL_DEFENSE_DOWN_HIT 72
#define EFFECT_ACCURACY_DOWN_HIT 73
#define EFFECT_EVASION_DOWN_HIT 74 // unused.. ok i get why this isn't needed,
#define EFFECT_SKY_ATTACK 75 // post gen 3 accu & evas got wrapped into one calc
#define EFFECT_CONFUSE_HIT 76
#define EFFECT_TWINEEDLE 77
#define EFFECT_VITAL_THROW 78	//doesn't actually do anything, is just a hit effect with a name
#define EFFECT_SUBSTITUTE 79
#define EFFECT_RECHARGE 80
#define EFFECT_RAGE 81
#define EFFECT_MIMIC 82
#define EFFECT_METRONOME 83
#define EFFECT_LEECH_SEED 84
#define EFFECT_SPLASH 85
#define EFFECT_DISABLE 86
#define EFFECT_LEVEL_DAMAGE 87
#define EFFECT_PSYWAVE 88
#define EFFECT_COUNTER 89
#define EFFECT_ENCORE 90
#define EFFECT_PAIN_SPLIT 91
#define EFFECT_SNORE 92
#define EFFECT_CONVERSION_Z 93
#define EFFECT_LOCK_ON 94
#define EFFECT_SKETCH 95
#define EFFECT_UNUSED_60 96  // thaw
#define EFFECT_SLEEP_TALK 97
#define EFFECT_DESTINY_BOND 98
#define EFFECT_FLAIL 99
#define EFFECT_SPITE 100
#define EFFECT_FALSE_SWIPE 101
#define EFFECT_HEAL_BELL 102
#define EFFECT_QUICK_ATTACK 103
#define EFFECT_TRIPLE_KICK 104
#define EFFECT_THIEF 105
#define EFFECT_MEAN_LOOK 106
#define EFFECT_NIGHTMARE 107
#define EFFECT_MINIMIZE 108
#define EFFECT_CURSE 109
#define EFFECT_HEALING_WISH 110 //replaced unused value  vsonic
#define EFFECT_PROTECT 111
#define EFFECT_SPIKES 112
#define EFFECT_FORESIGHT 113
#define EFFECT_PERISH_SONG 114
#define EFFECT_SANDSTORM 115
#define EFFECT_ENDURE 116
#define EFFECT_ROLLOUT 117
#define EFFECT_SWAGGER 118
#define EFFECT_FURY_CUTTER 119
#define EFFECT_ATTRACT 120
#define EFFECT_RETURN 121
#define EFFECT_PRESENT 122
#define EFFECT_FRUSTRATION 123
#define EFFECT_SAFEGUARD 124
#define EFFECT_UNUSED_7D 125     //was thaw hit, unused
#define EFFECT_MAGNITUDE 126
#define EFFECT_BATON_PASS 127
#define EFFECT_PURSUIT 128
#define EFFECT_RAPID_SPIN 129
#define EFFECT_SONIC_SCREECH 130
#define EFFECT_TWO_TURNS_ATTACK 131
#define EFFECT_MORNING_SUN 132
#define EFFECT_SYNTHESIS 133
#define EFFECT_MOONLIGHT 134
#define EFFECT_HIDDEN_POWER 135 //no longer used vsonic
#define EFFECT_RAIN_DANCE 136
#define EFFECT_SUNNY_DAY 137
#define EFFECT_DEFENSE_UP_HIT 138
#define EFFECT_ATTACK_UP_HIT 139
#define EFFECT_ALL_STATS_UP_HIT 140
#define EFFECT_UNUSED_8D 141  // incomplete fake out in gen 2   vsonic
#define EFFECT_BELLY_DRUM 142
#define EFFECT_PSYCH_UP 143
#define EFFECT_MIRROR_COAT 144
#define EFFECT_SKULL_BASH 145
#define EFFECT_TWISTER 146
#define EFFECT_EARTHQUAKE 147
#define EFFECT_FUTURE_SIGHT 148
#define EFFECT_GUST 149
#define EFFECT_FLINCH_MINIMIZE_HIT 150  // STOMP ASTONISH EXTRASENSORY NEEDLE_ARM
#define EFFECT_SOLARBEAM 151
#define EFFECT_THUNDER 152
#define EFFECT_TELEPORT 153
#define EFFECT_BEAT_UP 154
#define EFFECT_SEMI_INVULNERABLE 155
#define EFFECT_DEFENSE_CURL 156
#define EFFECT_SOFTBOILED 157
#define EFFECT_FAKE_OUT 158
#define EFFECT_UPROAR 159
#define EFFECT_STOCKPILE 160
#define EFFECT_SPIT_UP 161
#define EFFECT_SWALLOW 162
#define EFFECT_UNUSED_A3 163
#define EFFECT_HAIL 164
#define EFFECT_TORMENT 165
#define EFFECT_FLATTER 166
#define EFFECT_WILL_O_WISP 167
#define EFFECT_MEMENTO 168
#define EFFECT_FACADE 169
#define EFFECT_FOCUS_PUNCH 170
#define EFFECT_SMELLINGSALT 171
#define EFFECT_FOLLOW_ME 172
#define EFFECT_NATURE_POWER 173
#define EFFECT_CHARGE 174
#define EFFECT_TAUNT 175
#define EFFECT_HELPING_HAND 176
#define EFFECT_TRICK 177
#define EFFECT_ROLE_PLAY 178
#define EFFECT_WISH 179
#define EFFECT_ASSIST 180
#define EFFECT_INGRAIN 181
#define EFFECT_SUPERPOWER 182
#define EFFECT_MAGIC_COAT 183
#define EFFECT_RECYCLE 184
#define EFFECT_REVENGE 185
#define EFFECT_BRICK_BREAK 186
#define EFFECT_YAWN 187
#define EFFECT_KNOCK_OFF 188
#define EFFECT_ENDEAVOR 189
#define EFFECT_ERUPTION 190
#define EFFECT_SKILL_SWAP 191
#define EFFECT_IMPRISON 192
#define EFFECT_REFRESH 193
#define EFFECT_GRUDGE 194
#define EFFECT_SNATCH 195
#define EFFECT_LOW_KICK 196
#define EFFECT_SECRET_POWER 197
#define EFFECT_DOUBLE_EDGE 198
#define EFFECT_TEETER_DANCE 199
#define EFFECT_BLAZE_KICK 200
#define EFFECT_MUD_SPORT 201
#define EFFECT_TOXIC_FANG 202
#define EFFECT_WEATHER_BALL 203 //unused vsonic
#define EFFECT_OVERHEAT 204
#define EFFECT_TICKLE 205
#define EFFECT_COSMIC_POWER 206
#define EFFECT_SKY_UPPERCUT 207
#define EFFECT_BULK_UP 208
#define EFFECT_POISON_TAIL 209 //put placeholder back here incase its needed
#define EFFECT_WATER_SPORT 210 //feel stupid poison_tail wasn't even an effect FP
#define EFFECT_CALM_MIND 211
#define EFFECT_DRAGON_DANCE 212 // ok EFFECT_POISON_TAIL is an effect based on battle_moves.h
#define EFFECT_CAMOUFLAGE 213 //but isn't in emerald list o effects...ok got it that was a cfru thing
/*   figured it out poison_tail was an effect in gen3 but changed in pokeemerald so that's prop why its replaced with placeholder
#define EFFECT_HEAL_PULSE 214
#define EFFECT_HEALING_WISH 215
#define EFFECT_ROOST 216
#define EFFECT_HURRICANE 217 */

// New move effects
#define EFFECT_PLEDGE 214
#define EFFECT_FLING 215
#define EFFECT_NATURAL_GIFT 216
#define EFFECT_WAKE_UP_SLAP 217
#define EFFECT_WRING_OUT 218
#define EFFECT_HEX 219
#define EFFECT_ASSURANCE 220
#define EFFECT_TRUMP_CARD 221
#define EFFECT_ACROBATICS 222
#define EFFECT_HEAT_CRASH 223
#define EFFECT_PUNISHMENT 224
#define EFFECT_STORED_POWER 225
#define EFFECT_ELECTRO_BALL 226
#define EFFECT_GYRO_BALL 227
#define EFFECT_ECHOED_VOICE 228
#define EFFECT_PAYBACK 229
#define EFFECT_ROUND 230
#define EFFECT_BRINE 231
#define EFFECT_VENOSHOCK 232
#define EFFECT_RETALITATE 233
#define EFFECT_BULLDOZE 234
#define EFFECT_FOUL_PLAY 235
#define EFFECT_PSYSHOCK 236
#define EFFECT_ROOST 237
#define EFFECT_GRAVITY 238
#define EFFECT_MIRACLE_EYE 239
#define EFFECT_TAILWIND 240
#define EFFECT_EMBARGO 241
#define EFFECT_AQUA_RING 242
#define EFFECT_TRICK_ROOM 243
#define EFFECT_WONDER_ROOM 244
#define EFFECT_MAGIC_ROOM 245
#define EFFECT_MAGNET_RISE 246
#define EFFECT_TOXIC_SPIKES 247
#define EFFECT_GASTRO_ACID 248
#define EFFECT_STEALTH_ROCK 249
#define EFFECT_TELEKINESIS 250
#define EFFECT_POWER_SWAP 251
#define EFFECT_GUARD_SWAP 252
#define EFFECT_HEART_SWAP 253
#define EFFECT_POWER_SPLIT 254
#define EFFECT_GUARD_SPLIT 255
#define EFFECT_STICKY_WEB 256
#define EFFECT_METAL_BURST 257
#define EFFECT_LUCKY_CHANT 258
#define EFFECT_SUCKER_PUNCH 259
#define EFFECT_SPECIAL_DEFENSE_DOWN_HIT_2 260
#define EFFECT_SIMPLE_BEAM 261
#define EFFECT_ENTRAINMENT 262
#define EFFECT_HEAL_PULSE 263
#define EFFECT_QUASH 264
#define EFFECT_ION_DELUGE 265
#define EFFECT_FREEZE_DRY 266
#define EFFECT_TOPSY_TURVY 267
#define EFFECT_MISTY_TERRAIN 268
#define EFFECT_GRASSY_TERRAIN 269
#define EFFECT_ELECTRIC_TERRAIN 270
#define EFFECT_PSYCHIC_TERRAIN 271
#define EFFECT_ATTACK_ACCURACY_UP 272
#define EFFECT_ATTACK_SPATK_UP 273
#define EFFECT_HURRICANE 274
#define EFFECT_TWO_TYPED_MOVE 275
#define EFFECT_ME_FIRST 276
#define EFFECT_SPEED_UP_HIT 277	//made certain in bs_commands.c so effect should still work without needing to be 100
#define EFFECT_QUIVER_DANCE 278
#define EFFECT_COIL 279
#define EFFECT_ELECTRIFY 280
#define EFFECT_SCALD 281
#define EFFECT_REFLECT_TYPE 282
#define EFFECT_SOAK 283
#define EFFECT_GROWTH 284
#define EFFECT_CLOSE_COMBAT 285
#define EFFECT_LAST_RESORT 286
#define EFFECT_33_RECOIL_W_STATUS 287
#define EFFECT_FLINCH_STATUS 288
#define EFFECT_50_RECOIL 289
#define EFFECT_SHELL_SMASH 290
#define EFFECT_SHIFT_GEAR 291
#define EFFECT_DEFENSE_UP_3 292
#define EFFECT_NOBLE_ROAR 293 // Atk and Sp atk down by 1
#define EFFECT_VENOM_DRENCH 294
#define EFFECT_TOXIC_THREAD 295
#define EFFECT_CLEAR_SMOG 296
#define EFFECT_HIT_SWITCH_TARGET 297
#define EFFECT_FINAL_GAMBIT 298
#define EFFECT_CHANGE_TYPE_ON_ITEM 299 // Techno Blast, Multi Attack, Judgment
#define EFFECT_AUTOTOMIZE 300
#define EFFECT_COPYCAT 301
#define EFFECT_DEFOG 302
#define EFFECT_HIT_ENEMY_HEAL_ALLY 303 // Pollen Puff
#define EFFECT_SMACK_DOWN 304
#define EFFECT_SYNCHRONOISE 305
#define EFFECT_PSYCHO_SHIFT 306
#define EFFECT_POWER_TRICK 307
#define EFFECT_FLAME_BURST 308
#define EFFECT_AFTER_YOU 309
#define EFFECT_BESTOW 310
#define EFFECT_ROTOTILLER 311
#define EFFECT_FLOWER_SHIELD 312
#define EFFECT_HIT_PREVENT_ESCAPE 313
#define EFFECT_SPEED_SWAP 314
#define EFFECT_DEFENSE_UP2_HIT 315
#define EFFECT_REVELATION_DANCE 316
#define EFFECT_AURORA_VEIL 317
#define EFFECT_THIRD_TYPE 318
#define EFFECT_FEINT 319
#define EFFECT_SPARKLING_ARIA 320
#define EFFECT_ACUPRESSURE 321
#define EFFECT_AROMATIC_MIST 322
#define EFFECT_POWDER 323
#define EFFECT_SP_ATTACK_UP_HIT 324
#define EFFECT_BELCH 325
#define EFFECT_PARTING_SHOT 326
#define EFFECT_SPECTRAL_THIEF 327
#define EFFECT_V_CREATE 328
#define EFFECT_MAT_BLOCK 329
#define EFFECT_STOMPING_TANTRUM 330
#define EFFECT_CORE_ENFORCER 331
#define EFFECT_INSTRUCT 332
#define EFFECT_THROAT_CHOP 333
#define EFFECT_LASER_FOCUS 334
#define EFFECT_MAGNETIC_FLUX 335
#define EFFECT_GEAR_UP 336
#define EFFECT_INCINERATE 337
#define EFFECT_BUG_BITE 338
#define EFFECT_STRENGTH_SAP 339
#define EFFECT_MIND_BLOWN 340
#define EFFECT_PURIFY 341
#define EFFECT_LOSETYPE_HIT 342
#define EFFECT_SHORE_UP 343
#define EFFECT_GEOMANCY 344
#define EFFECT_FAIRY_LOCK 345
#define EFFECT_ALLY_SWITCH 346
#define EFFECT_RELIC_SONG 347 // Relic Song
#define EFFECT_HIT_ESCAPE 348
#define EFFECT_WORRY_SEED 349
#define EFFECT_FELL_STINGER 350
#define EFFECT_CAPTIVATE 351
#define EFFECT_ALWAYS_CRIT 352  //effect free no longer used, done w flag instead
#define EFFECT_HAMMER_ARM 353
#define EFFECT_FUSION_COMBO 354
#define EFFECT_HEAL_BLOCK 355
#define EFFECT_SPECIAL_ATTACK_UP_3 356 //tailglow
#define EFFECT_STRENGTH_UP_HIT 357 //HOPE works, point is to increase attack before hit
#define EFFECT_BODY_PRESS 358
#define EFFECT_EERIE_SPELL 359
#define EFFECT_JUNGLE_HEALING 360
#define EFFECT_COACHING 361
#define EFFECT_LASH_OUT 362
#define EFFECT_GRASSY_GLIDE 363
#define EFFECT_REMOVE_TERRAIN 364
#define EFFECT_DYNAMAX_DOUBLE_DMG 365
#define EFFECT_DECORATE 366
#define EFFECT_SNIPE_SHOT 367
#define EFFECT_STUFF_CHEEKS 368
#define EFFECT_GRAV_APPLE 369
#define EFFECT_EVASION_UP_HIT 370
#define EFFECT_DOUBLE_IRON_BASH 371
#define EFFECT_GLITZY_GLOW 372
#define EFFECT_BADDY_BAD 373
#define EFFECT_SAPPY_SEED 374
#define EFFECT_FREEZY_FROST 375
#define EFFECT_SPARKLY_SWIRL 376
#define EFFECT_PLASMA_FISTS 377
#define EFFECT_HYPERSPACE_FURY 378
#define EFFECT_AURA_WHEEL 379
#define EFFECT_PHOTON_GEYSER 380
#define EFFECT_SHELL_SIDE_ARM 381
#define EFFECT_TERRAIN_PULSE 382
#define EFFECT_JAW_LOCK 383
#define EFFECT_NO_RETREAT 384
#define EFFECT_TAR_SHOT 385
#define EFFECT_POLTERGEIST 386
#define EFFECT_OCTOLOCK 387
#define EFFECT_CLANGOROUS_SOUL 388
#define EFFECT_BOLT_BEAK 389
#define EFFECT_SKY_DROP 390

#define EFFECT_ATTACKER_DEFENSE_DOWN_HIT 391
#define EFFECT_MONOTYPE 392 //new sketch
#define EFFECT_SKETCH_STAT_UP 393 //stat increase for sketch should jump to script but not use effect alone
#define EFFECT_FLASH 394
#define EFFECT_COCOON 395
#define EFFECT_FLASH_FREEZE 396
//#define EFFECT_FIRE_SPIN 398 //needed these separate because otherwise, game doesn't allow multiple traps to be applied //changed rather than multile effects just use multi status 
#define EFFECT_DRYADS_CURSE 397
#define EFFECT_SHIELD_BASH 398
#define EFFECT_ATTRACT_HIT 399	//NEED test
#define EFFECT_EXPANDING_FORCE 400	//Just to fill space
#define EFFECT_TRIPLE_ARROWS 401	//triple arrow change
#define EFFECT_SPECIAL_ATTACK_UP_HIT 402
#define EFFECT_VICTORY_DANCE                403
#define EFFECT_TEATIME                      404
#define EFFECT_ATTACK_UP_USER_ALLY          405 // Howl 8th Gen ver.
#define EFFECT_TARGET_TYPE_DAMAGE       406 //right now rock smash & cut, dmg multiplier is argument chance /10 
#define EFFECT_TRENCH_RUN               407  //ujnsure if done, know still needs message string
#define EFFECT_HIT_SET_ENTRY_HAZARD 408     //for now just for stone axe
#define EFFECT_SNOWBALL 409 //separated from psywave effect do variable pwr intsead of flat damage
#define EFFECT_CELEBRATE 410
#define EFFECT_JUDGMENT 411 //defaults to hit, but still needed for other logic
#define EFFECT_SHELL_TRAP 412
#define EFFECT_SWITCH_BIND 413 //spirit shackle buff, temp escape prevention doesn't require user stay in
#define EFFECT_NETTLE_WHIP 414 //BURN HIT grass types are immune to effect, like power moves

/*MOVE_FIRE_SPIN, //increases burn chance //serenge grace is effect *2 by requires no setup, I think I can get away w * 3 here actually do more to near guarantee 50-60%
MOVE_CLAMP,     //no extra wrap effect,  but give flich chance on hit //changed mind you're staying clamped on them, so for duration statused target has chance to flinch when attacking
MOVE_WHIRLPOOL, // lower speed of wrapped target 1 stage    //already does double damage to underwater target
MOVE_SAND_TOMB, // decrease accuracy of wrapped target  //do double damage to underground target, use sandpit description from emerald
MOVE_MAGMA_STORM,   //heatran specific, might buff to give guaranteed burn, don't need lower damage since its lowered from 120 already
MOVE_SWARM,   //since bug infestations can cause structural integrity issues, think I'll make this lower def & sp def or just def
MOVE_SNAP_TRAP,*/	//since physical will make only trap that doesn't go away on switch or faint, also changed from grass to steel type

#endif  // GUARD_CONSTANTS_BATTLE_EFFECTS_H
// gBattleScriptsForBattleEffects found at top of battle_scripts_1.s
//must be in same order as this file.  because they are pointers
//the battle_script below that don't matter far as order

//in gBattleScriptsForBattleEffects effect_hit is used to stand in for unused effects 
//so should be able to be safely replaced
