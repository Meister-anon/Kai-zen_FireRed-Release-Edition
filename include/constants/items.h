#ifndef GUARD_CONSTANTS_ITEMS_H
#define GUARD_CONSTANTS_ITEMS_H
// because of my change to the item table I need to change all values that are ITEM_(some hex value) into ITEM_NONE I think..yeah I do, because they were previously
//auto aligned with a question mark icon & palette.   actually imma leave it for now, since I plan to fill those placeholders in.

//actually I think this file just needs to match the items.json //yup confirmed
//believe none of these notes matter
//planning replace item list w EE values for add enum Item
//just need check all fr items exist in EE
//think make pyscript w given list
//read item list from EE
//if search in array is in EE list
//remove from FR array and then print at end
//will show remaining items would need to add back
//can do that using template of attempt2.py
//following that update my item struct for whatever
//stuff from EE I still need want
//and see about integrating tm list data with
//items.h file make it add new tms item data at end of list
//in format of struct

#define ITEM_NONE 0
#define ITEM_POKE_BALL 1
#define ITEM_GREAT_BALL 2
#define ITEM_SAFARI_BALL 3
#define ITEM_ULTRA_BALL 4
#define ITEM_MASTER_BALL 5
#define ITEM_NET_BALL 6
#define ITEM_DIVE_BALL 7
#define ITEM_NEST_BALL 8
#define ITEM_REPEAT_BALL 9
#define ITEM_TIMER_BALL 10
#define ITEM_LUXURY_BALL 11
#define ITEM_PREMIER_BALL 12


#define ITEM_POTION 13
#define ITEM_ANTIDOTE 14
#define ITEM_BURN_HEAL 15
#define ITEM_ICE_HEAL 16
#define ITEM_AWAKENING 17
#define ITEM_PARALYZE_HEAL 18
#define ITEM_FULL_RESTORE 19
#define ITEM_MAX_POTION 20
#define ITEM_HYPER_POTION 21
#define ITEM_SUPER_POTION 22
#define ITEM_FULL_HEAL 23
#define ITEM_REVIVE 24
#define ITEM_MAX_REVIVE 25
#define ITEM_FRESH_WATER 26
#define ITEM_SODA_POP 27
#define ITEM_LEMONADE 28
#define ITEM_MOOMOO_MILK 29
#define ITEM_ENERGY_POWDER 30
#define ITEM_ENERGY_ROOT 31
#define ITEM_HEAL_POWDER 32
#define ITEM_REVIVAL_HERB 33
#define ITEM_ETHER 34
#define ITEM_MAX_ETHER 35
#define ITEM_ELIXIR 36
#define ITEM_MAX_ELIXIR 37
#define ITEM_LAVA_COOKIE 38
#define ITEM_BLUE_FLUTE 39
#define ITEM_YELLOW_FLUTE 40
#define ITEM_RED_FLUTE 41
#define ITEM_BLACK_FLUTE 42
#define ITEM_WHITE_FLUTE 43
#define ITEM_BERRY_JUICE 44
#define ITEM_SACRED_ASH 45
#define ITEM_SHOAL_SALT 46
#define ITEM_SHOAL_SHELL 47
#define ITEM_RED_SHARD 48
#define ITEM_BLUE_SHARD 49
#define ITEM_YELLOW_SHARD 50
#define ITEM_GREEN_SHARD 51
#define ITEM_034 52
#define ITEM_035 53
#define ITEM_036 54
#define ITEM_037 55
#define ITEM_038 56
#define ITEM_039 57
#define ITEM_03A 58
#define ITEM_03B 59
#define ITEM_03C 60
#define ITEM_03D 61
#define ITEM_03E 62
#define ITEM_HP_UP 63
#define ITEM_PROTEIN 64
#define ITEM_IRON 65
#define ITEM_CARBOS 66
#define ITEM_CALCIUM 67
#define ITEM_RARE_CANDY 68
#define ITEM_PP_UP 69
#define ITEM_ZINC 70
#define ITEM_PP_MAX 71
#define ITEM_048 72
#define ITEM_GUARD_SPEC 73
#define ITEM_DIRE_HIT 74
#define ITEM_X_ATTACK 75
#define ITEM_X_DEFENSE 76
#define ITEM_X_SPEED 77
#define ITEM_X_ACCURACY 78
#define ITEM_X_SP_ATK 79
#define ITEM_POKE_DOLL 80
#define ITEM_FLUFFY_TAIL 81
#define ITEM_X_SP_DEF 82
#define ITEM_SUPER_REPEL 83
#define ITEM_MAX_REPEL 84
#define ITEM_ESCAPE_ROPE 85
#define ITEM_REPEL 86
#define ITEM_ABILITY_CAPSULE 87	//remmbeber need change logic of this, so lets me select the slot to change to
#define ITEM_058 88
#define ITEM_059 89
#define ITEM_05A 90
#define ITEM_05B 91
#define ITEM_05C 92
#define ITEM_SUN_STONE 93
#define ITEM_MOON_STONE 94
#define ITEM_FIRE_STONE 95
#define ITEM_THUNDER_STONE 96
#define ITEM_WATER_STONE 97
#define ITEM_LEAF_STONE 98
#define ITEM_DAWN_STONE 99
#define ITEM_DUSK_STONE 100
#define ITEM_SHINY_STONE 101 //in-game will be known as dazzling stone
#define ITEM_ICE_STONE 102
#define ITEM_TINY_MUSHROOM 103
#define ITEM_BIG_MUSHROOM 104
#define ITEM_069 105
#define ITEM_PEARL 106
#define ITEM_BIG_PEARL 107
#define ITEM_STARDUST 108
#define ITEM_STAR_PIECE 109
#define ITEM_NUGGET 110
#define ITEM_HEART_SCALE 111
#define ITEM_070 112
#define ITEM_071 113
#define ITEM_072 114
#define ITEM_073 115
#define ITEM_074 116
#define ITEM_075 117
#define ITEM_WHIPPED_DREAM 118
#define ITEM_SACHET 119
#define ITEM_OVAL_STONE 120
#define ITEM_ORANGE_MAIL 121
#define ITEM_HARBOR_MAIL 122
#define ITEM_GLITTER_MAIL 123
#define ITEM_MECH_MAIL 124
#define ITEM_WOOD_MAIL 125
#define ITEM_WAVE_MAIL 126
#define ITEM_BEAD_MAIL 127
#define ITEM_SHADOW_MAIL 128
#define ITEM_TROPIC_MAIL 129
#define ITEM_DREAM_MAIL 130
#define ITEM_FAB_MAIL 131
#define ITEM_RETRO_MAIL 132
#define ITEM_CHERI_BERRY 133
#define ITEM_CHESTO_BERRY 134
#define ITEM_PECHA_BERRY 135
#define ITEM_RAWST_BERRY 136
#define ITEM_ASPEAR_BERRY 137
#define ITEM_LEPPA_BERRY 138
#define ITEM_ORAN_BERRY 139
#define ITEM_PERSIM_BERRY 140
#define ITEM_LUM_BERRY 141
#define ITEM_SITRUS_BERRY 142
#define ITEM_FIGY_BERRY 143
#define ITEM_WIKI_BERRY 144
#define ITEM_MAGO_BERRY 145
#define ITEM_AGUAV_BERRY 146
#define ITEM_IAPAPA_BERRY 147
#define ITEM_RAZZ_BERRY 148
#define ITEM_BLUK_BERRY 149
#define ITEM_NANAB_BERRY 150
#define ITEM_WEPEAR_BERRY 151
#define ITEM_PINAP_BERRY 152
#define ITEM_POMEG_BERRY 153
#define ITEM_KELPSY_BERRY 154
#define ITEM_QUALOT_BERRY 155
#define ITEM_HONDEW_BERRY 156
#define ITEM_GREPA_BERRY 157
#define ITEM_TAMATO_BERRY 158
#define ITEM_CORNN_BERRY 159
#define ITEM_MAGOST_BERRY 160
#define ITEM_RABUTA_BERRY 161
#define ITEM_NOMEL_BERRY 162
#define ITEM_SPELON_BERRY 163
#define ITEM_PAMTRE_BERRY 164
#define ITEM_WATMEL_BERRY 165
#define ITEM_DURIN_BERRY 166
#define ITEM_BELUE_BERRY 167
#define ITEM_LIECHI_BERRY 168
#define ITEM_GANLON_BERRY 169
#define ITEM_SALAC_BERRY 170
#define ITEM_PETAYA_BERRY 171
#define ITEM_APICOT_BERRY 172
#define ITEM_LANSAT_BERRY 173
#define ITEM_STARF_BERRY 174
#define ITEM_ENIGMA_BERRY 175
#define ITEM_PROTECTOR 176 // add more evo "use" items below 0B2
#define ITEM_DRAGON_SCALE 177
#define ITEM_EXP_NULL 178 //last value for can be used on pokemon  //i.e via party menu
#define ITEM_BRIGHT_POWDER 179
#define ITEM_WHITE_HERB 180
#define ITEM_MACHO_BRACE 181
#define ITEM_EXP_SHARE 182
#define ITEM_QUICK_CLAW 183
#define ITEM_SOOTHE_BELL 184
#define ITEM_MENTAL_HERB 185
#define ITEM_CHOICE_BAND 186
#define ITEM_KINGS_ROCK 187
#define ITEM_SILVER_POWDER 188
#define ITEM_AMULET_COIN 189
#define ITEM_CLEANSE_TAG 190
#define ITEM_SOUL_DEW 191
#define ITEM_DEEP_SEA_TOOTH 192
#define ITEM_DEEP_SEA_SCALE 193
#define ITEM_SMOKE_BALL 194
#define ITEM_EVERSTONE 195
#define ITEM_FOCUS_BAND 196
#define ITEM_LUCKY_EGG 197
#define ITEM_SCOPE_LENS 198
#define ITEM_HONEY 199
#define ITEM_LEFTOVERS 200
#define ITEM_0C9 201
#define ITEM_LIGHT_BALL 202
#define ITEM_SOFT_SAND 203
#define ITEM_HARD_STONE 204
#define ITEM_MIRACLE_SEED 205
#define ITEM_BLACK_GLASSES 206
#define ITEM_BLACK_BELT 207
#define ITEM_MAGNET 208
#define ITEM_MYSTIC_WATER 209
#define ITEM_SHARP_BEAK 210
#define ITEM_POISON_BARB 211
#define ITEM_NEVER_MELT_ICE 212
#define ITEM_SPELL_TAG 213
#define ITEM_TWISTED_SPOON 214
#define ITEM_CHARCOAL 215
#define ITEM_DRAGON_FANG 216
#define ITEM_SILK_SCARF 217
#define ITEM_0DA 218
#define ITEM_SHELL_BELL 219
#define ITEM_0DC 220
#define ITEM_0DD 221
#define ITEM_LUCKY_PUNCH 222
#define ITEM_METAL_POWDER 223
#define ITEM_THICK_CLUB 224
#define ITEM_LEEK 225
#define ITEM_PRISM_SCALE 226 // will make this an evo hold item level up, but because its milotic and difficult, make it random %4 only evolve while 0, so a 1 in 5 each level up.
#define ITEM_RAZOR_CLAW 227
#define ITEM_EVIOLITE 228
#define ITEM_EVIOLITE_FAIL 229
#define ITEM_0E6 230
#define ITEM_0E7 231
#define ITEM_0E8 232
#define ITEM_0E9 233
//Power Items
#define ITEM_POWER_WEIGHT 234	//hp
#define ITEM_POWER_BRACER 235	//atk	
#define ITEM_POWER_BELT 236		//def
#define ITEM_POWER_LENS 237		//sp.atk
#define ITEM_POWER_BAND 238	    //sp.def
#define ITEM_POWER_ANKLET 239   //speed
//Fossils
#define ITEM_SAIL_FOSSIL 240		//amaura
#define ITEM_JAW_FOSSIL 241			//tyrunt
#define ITEM_PLUME_FOSSIL 242		//archen
#define ITEM_COVER_FOSSIL 243		//tirtouga
#define ITEM_FOSSILIZED_BIRD 244	//dracozolt = bird + drake
#define ITEM_FOSSILIZED_FISH 245	//dracovish = fish + drake
#define ITEM_SKULL_FOSSIL 246		//craniados
#define ITEM_ARMOR_FOSSIL 247		//shieldon
#define ITEM_FOSSILIZED_DINO 248	//arctozolt = bird + dino
#define ITEM_FOSSILIZED_DRAKE 249	//arctovish = fish + dino
#define ITEM_0FA 250
#define ITEM_0FB 251
#define ITEM_0FC 252
#define ITEM_0FD 253
#define ITEM_RED_SCARF 254
#define ITEM_BLUE_SCARF 255
#define ITEM_PINK_SCARF 256
#define ITEM_GREEN_SCARF 257
#define ITEM_YELLOW_SCARF 258
#define ITEM_MACH_BIKE 259
#define ITEM_COIN_CASE 260
#define ITEM_ITEMFINDER 261
#define ITEM_OLD_ROD 262
#define ITEM_GOOD_ROD 263
#define ITEM_SUPER_ROD 264
#define ITEM_SS_TICKET 265
#define ITEM_CONTEST_PASS 266
#define ITEM_10B 267
#define ITEM_WAILMER_PAIL 268
#define ITEM_DEVON_GOODS 269
#define ITEM_SOOT_SACK 270
#define ITEM_BASEMENT_KEY 271
#define ITEM_ACRO_BIKE 272
#define ITEM_POKEBLOCK_CASE 273
#define ITEM_LETTER 274
#define ITEM_EON_TICKET 275
#define ITEM_RED_ORB 276
#define ITEM_BLUE_ORB 277
#define ITEM_SCANNER 278
#define ITEM_GO_GOGGLES 279
#define ITEM_METEORITE 280
#define ITEM_ROOM_1_KEY 281
#define ITEM_ROOM_2_KEY 282
#define ITEM_ROOM_4_KEY 283
#define ITEM_ROOM_6_KEY 284
#define ITEM_STORAGE_KEY 285
#define ITEM_ROOT_FOSSIL 286	//lileep
#define ITEM_CLAW_FOSSIL 287	//anorith
#define ITEM_DEVON_SCOPE 288    //for some reason used as filter in shop menu?
#define ITEM_TM01 289
#define ITEM_TM02 290
#define ITEM_TM03 291
#define ITEM_TM04 292
#define ITEM_TM05 293
#define ITEM_TM06 294
#define ITEM_TM07 295
#define ITEM_TM08 296
#define ITEM_TM09 297
#define ITEM_TM10 298
#define ITEM_TM11 299
#define ITEM_TM12 300
#define ITEM_TM13 301
#define ITEM_TM14 302
#define ITEM_TM15 303
#define ITEM_TM16 304
#define ITEM_TM17 305
#define ITEM_TM18 306
#define ITEM_TM19 307
#define ITEM_TM20 308
#define ITEM_TM21 309
#define ITEM_TM22 310
#define ITEM_TM23 311
#define ITEM_TM24 312
#define ITEM_TM25 313
#define ITEM_TM26 314
#define ITEM_TM27 315
#define ITEM_TM28 316
#define ITEM_TM29 317
#define ITEM_TM30 318
#define ITEM_TM31 319
#define ITEM_TM32 320
#define ITEM_TM33 321
#define ITEM_TM34 322
#define ITEM_TM35 323
#define ITEM_TM36 324
#define ITEM_TM37 325
#define ITEM_TM38 326
#define ITEM_TM39 327
#define ITEM_TM40 328
#define ITEM_TM41 329
#define ITEM_TM42 330
#define ITEM_TM43 331
#define ITEM_TM44 332
#define ITEM_TM45 333
#define ITEM_TM46 334
#define ITEM_TM47 335
#define ITEM_TM48 336
#define ITEM_TM49 337
#define ITEM_TM50 338
//tm Expansion
#define ITEM_TM51 339
#define ITEM_TM52 340
#define ITEM_TM53 341
#define ITEM_TM54 342
#define ITEM_TM55 343
#define ITEM_TM56 344
#define ITEM_TM57 345
#define ITEM_TM58 346
#define ITEM_TM59 347
#define ITEM_TM60 348
#define ITEM_TM61 349
#define ITEM_TM62 350
#define ITEM_TM63 351
#define ITEM_TM64 352
#define ITEM_TM65 353
#define ITEM_TM66 354
#define ITEM_TM67 355
#define ITEM_TM68 356
#define ITEM_TM69 357
#define ITEM_TM70 358
#define ITEM_TM71 359
#define ITEM_TM72 360
#define ITEM_TM73 361
#define ITEM_TM74 362
#define ITEM_TM75 363
#define ITEM_TM76 364
#define ITEM_TM77 365
#define ITEM_TM78 366
#define ITEM_TM79 367
#define ITEM_TM80 368
#define ITEM_TM81 369
#define ITEM_TM82 370
#define ITEM_TM83 371
#define ITEM_TM84 372
#define ITEM_TM85 373
#define ITEM_TM86 374
#define ITEM_TM87 375
#define ITEM_TM88 376
#define ITEM_TM89 377
#define ITEM_TM90 378
#define ITEM_TM91 379
#define ITEM_TM92 380
#define ITEM_TM93 381
#define ITEM_TM94 382
#define ITEM_TM95 383
#define ITEM_TM96 384
#define ITEM_TM97 385
#define ITEM_TM98 386
#define ITEM_TM99 387
#define ITEM_TM100 388
#define ITEM_TM101 389
#define ITEM_TM102 390
#define ITEM_TM103 391
#define ITEM_TM104 392
#define ITEM_TM105 393
#define ITEM_TM106 394
#define ITEM_TM107 395
#define ITEM_TM108 396
#define ITEM_TM109 397
#define ITEM_TM110 398
#define ITEM_TM111 399
#define ITEM_TM112 400
#define ITEM_TM113 401
#define ITEM_TM114 402
#define ITEM_TM115 403
#define ITEM_TM116 404
#define ITEM_TM117 405
#define ITEM_TM118 406
#define ITEM_TM119 407
#define ITEM_TM120 408
#define ITEM_TM121 409
#define ITEM_TM122 410
#define ITEM_TM123 411
#define ITEM_TM124 412
#define ITEM_TM125 413
#define ITEM_TM126 414
#define ITEM_TM127 415
#define ITEM_TM128 416
#define ITEM_TM129 417
#define ITEM_TM130 418
#define ITEM_TM131 419
#define ITEM_TM132 420
#define ITEM_TM133 421
#define ITEM_TM134 422
#define ITEM_TM135 423
#define ITEM_TM136 424
#define ITEM_TM137 425
#define ITEM_TM138 426
#define ITEM_TM139 427
#define ITEM_TM140 428
#define ITEM_TM141 429
#define ITEM_TM142 430
#define ITEM_TM143 431
#define ITEM_TM144 432
#define ITEM_TM145 433
#define ITEM_TM146 434
#define ITEM_TM147 435
#define ITEM_TM148 436
#define ITEM_TM149 437
#define ITEM_TM150 438
#define ITEM_TM151 439
#define ITEM_TM152 440
#define ITEM_TM153 441
#define ITEM_TM154 442
#define ITEM_TM155 443
#define ITEM_TM156 444
#define ITEM_TM157 445  
#define ITEM_TM158 446
#define ITEM_TM159 447
#define ITEM_TM160 448
#define ITEM_TM161 449//end of tms   +110 /seperated tms from item id sequence putting further tms on end

#define ITEM_HM01 450 
#define ITEM_HM02 451
#define ITEM_HM03 452
#define ITEM_HM04 453
#define ITEM_HM05 454
#define ITEM_HM06 455
#define ITEM_HM07 456
#define ITEM_HM08 457
#define ITEM_HM09 458

#define ITEM_TM01_FOCUS_PUNCH ITEM_TM01
#define ITEM_TM02_DRAGON_CLAW ITEM_TM02
#define ITEM_TM03_WATER_PULSE ITEM_TM03
#define ITEM_TM04_CALM_MIND ITEM_TM04
#define ITEM_TM05_ROAR ITEM_TM05
#define ITEM_TM06_TOXIC ITEM_TM06
#define ITEM_TM07_HAIL ITEM_TM07
#define ITEM_TM08_BULK_UP ITEM_TM08
#define ITEM_TM09_BULLET_SEED ITEM_TM09
#define ITEM_TM10_HIDDEN_POWER ITEM_TM10
#define ITEM_TM11_SUNNY_DAY ITEM_TM11
#define ITEM_TM12_TAUNT ITEM_TM12
#define ITEM_TM13_ICE_BEAM ITEM_TM13
#define ITEM_TM14_BLIZZARD ITEM_TM14
#define ITEM_TM15_HYPER_BEAM ITEM_TM15
#define ITEM_TM16_LIGHT_SCREEN ITEM_TM16
#define ITEM_TM17_PROTECT ITEM_TM17
#define ITEM_TM18_RAIN_DANCE ITEM_TM18
#define ITEM_TM19_GIGA_DRAIN ITEM_TM19  //potentialy replace w mega drain since buffed
#define ITEM_TM20_SAFEGUARD ITEM_TM20
#define ITEM_TM21_FRUSTRATION ITEM_TM21
#define ITEM_TM22_SOLAR_BEAM ITEM_TM22
#define ITEM_TM23_IRON_TAIL ITEM_TM23
#define ITEM_TM24_THUNDERBOLT ITEM_TM24
#define ITEM_TM25_THUNDER ITEM_TM25
#define ITEM_TM26_EARTHQUAKE ITEM_TM26
#define ITEM_TM27_RETURN ITEM_TM27
#define ITEM_TM28_DIG ITEM_TM28
#define ITEM_TM29_PSYCHIC ITEM_TM29
#define ITEM_TM30_SHADOW_BALL ITEM_TM30
#define ITEM_TM31_BRICK_BREAK ITEM_TM31
#define ITEM_TM32_DOUBLE_TEAM ITEM_TM32
#define ITEM_TM33_REFLECT ITEM_TM33
#define ITEM_TM34_SHOCK_WAVE ITEM_TM34
#define ITEM_TM35_FLAMETHROWER ITEM_TM35
#define ITEM_TM36_SLUDGE_BOMB ITEM_TM36
#define ITEM_TM37_SANDSTORM ITEM_TM37
#define ITEM_TM38_FIRE_BLAST ITEM_TM38
#define ITEM_TM39_ROCK_TOMB ITEM_TM39
#define ITEM_TM40_AERIAL_ACE ITEM_TM40
#define ITEM_TM41_TORMENT ITEM_TM41
#define ITEM_TM42_FACADE ITEM_TM42
#define ITEM_TM43_SECRET_POWER ITEM_TM43
#define ITEM_TM44_REST ITEM_TM44
#define ITEM_TM45_ATTRACT ITEM_TM45
#define ITEM_TM46_THIEF ITEM_TM46
#define ITEM_TM47_STEEL_WING ITEM_TM47
#define ITEM_TM48_SKILL_SWAP ITEM_TM48
#define ITEM_TM49_SNATCH ITEM_TM49
#define ITEM_TM50_OVERHEAT ITEM_TM50 //expand and add onto list at bottom of file


//keep in mind also expanding learnsets
//so more moves will be there too
//can't put too much in tms  or learnsets wont feel unique

//I can leave some of that stuff in learnsets instead and it'll help keep the total tm list from getting too big
//keep roost in tms but revise gen 4 list and plans for gen 7 8 9 stuff
//on note from pcg in rhh discord, plan group things of similar category together i.e trap moves  elemental punches and fangs together
//moves of similar category or power
//with razor leaf now added to list of elemental slashes as the grass slash, put those together  w shadow claw night slash etc.
//cross poison , pycho cut , x scissor
//think will order this list based off of the categories of the gen 4 list,
//ex. when get to slash moves put all my stuff there
//make dual wingbeat a tm
#define TM_EXPANSION

#define ITEM_TM51_WILD_CHARGE   ITEM_TM51
#define ITEM_TM52_ROOST ITEM_TM52
#define ITEM_TM53_TELEPORT ITEM_TM53
#define ITEM_TM54_QUASH ITEM_TM54
#define ITEM_TM55_HONE_CLAWS ITEM_TM55
#define ITEM_TM56_BRINE ITEM_TM56
#define ITEM_TM57_CHARGE_BEAM ITEM_TM57
#define ITEM_TM58_ENDURE ITEM_TM58
#define ITEM_TM59_DRAGON_PULSE ITEM_TM59
#define ITEM_TM60_THUNDER_PUNCH ITEM_TM60
#define ITEM_TM61_FIRE_PUNCH ITEM_TM61
#define ITEM_TM62_ICE_PUNCH ITEM_TM62
#define ITEM_TM63_SHADOW_PUNCH ITEM_TM63
#define ITEM_TM64_POISON_JAB ITEM_TM64
#define ITEM_TM65_DRAIN_PUNCH ITEM_TM65
#define ITEM_TM66_COMET_PUNCH ITEM_TM66
#define ITEM_TM67_WILL_O_WISP ITEM_TM67
#define ITEM_TM68_MEMENTO ITEM_TM68
#define ITEM_TM69_SILVER_WIND ITEM_TM69
#define ITEM_TM70_OMINOUS_WIND ITEM_TM70
#define ITEM_TM71_FLING ITEM_TM71
#define ITEM_TM72_EMBARGO ITEM_TM72
#define ITEM_TM73_RECYCLE ITEM_TM73
#define ITEM_TM74_HEAL_BLOCK ITEM_TM74
#define ITEM_TM75_THUNDER_FANG ITEM_TM75
#define ITEM_TM76_FIRE_FANG ITEM_TM76
#define ITEM_TM77_ICE_FANG ITEM_TM77
#define ITEM_TM78_EXPLOSION ITEM_TM78 //want to add double edge above this, tm like it was in gen 1 vsonic
#define ITEM_TM79_SHADOW_CLAW ITEM_TM79
#define ITEM_TM80_NIGHT_SLASH ITEM_TM80
#define ITEM_TM81_RAZOR_LEAF ITEM_TM81
#define ITEM_TM82_X_SCISSOR ITEM_TM82
#define ITEM_TM83_CROSS_POISON ITEM_TM83
#define ITEM_TM84_PSYCHO_CUT ITEM_TM84
#define ITEM_TM85_FALSE_SWIPE ITEM_TM85 //think put metal claw after this nvm too miuch work ut at end
#define ITEM_TM86_PAYBACK ITEM_TM86
#define ITEM_TM87_GIGA_IMPACT ITEM_TM87
#define ITEM_TM88_ROCK_POLISH ITEM_TM88
#define ITEM_TM89_MUD_SPORT ITEM_TM89
#define ITEM_TM90_WATER_SPORT ITEM_TM90
#define ITEM_TM91_AURORA_VEIL ITEM_TM91
#define ITEM_TM92_STONE_EDGE ITEM_TM92
#define ITEM_TM93_REVENGE ITEM_TM93
#define ITEM_TM94_AVALANCHE ITEM_TM94
#define ITEM_TM95_THUNDER_WAVE ITEM_TM95
#define ITEM_TM96_GLARE ITEM_TM96
#define ITEM_TM97_GYRO_BALL ITEM_TM97
#define ITEM_TM98_ELECTRO_BALL ITEM_TM98
#define ITEM_TM99_SWORDS_DANCE ITEM_TM99
#define ITEM_TM100_POWER_TRICK ITEM_TM100
#define ITEM_TM101_POWER_SHIFT ITEM_TM101
#define ITEM_TM102_POWER_SWAP ITEM_TM102
#define ITEM_TM103_GUARD_SWAP ITEM_TM103
#define ITEM_TM104_SPEED_SWAP ITEM_TM104
#define ITEM_TM105_STEALTH_ROCK ITEM_TM105
#define ITEM_TM106_SPIKES ITEM_TM106
#define ITEM_TM107_FIRE_SPIN ITEM_TM107
#define ITEM_TM108_SAND_TOMB ITEM_TM108
#define ITEM_TM109_WHIRLPOOL ITEM_TM109
#define ITEM_TM110_SWARM ITEM_TM110
#define ITEM_TM111_PSYCH_UP ITEM_TM111
#define ITEM_TM112_CAPTIVATE ITEM_TM112
#define ITEM_TM113_CONFIDE ITEM_TM113
#define ITEM_TM114_FAKE_TEARS ITEM_TM114
#define ITEM_TM115_ACID_SPRAY ITEM_TM115
#define ITEM_TM116_DARK_PULSE ITEM_TM116
#define ITEM_TM117_ROCK_THROW ITEM_TM117
#define ITEM_TM118_POWER_GEM ITEM_TM118
#define ITEM_TM119_SLEEP_TALK ITEM_TM119
#define ITEM_TM120_SNORE ITEM_TM120
#define ITEM_TM121_NATURAL_GIFT ITEM_TM121
#define ITEM_TM122_GRASS_KNOT ITEM_TM122
#define ITEM_TM123_SWAGGER ITEM_TM123
#define ITEM_TM124_PLUCK ITEM_TM124
#define ITEM_TM125_BUG_BITE ITEM_TM125
#define ITEM_TM126_U_TURN ITEM_TM126
#define ITEM_TM127_VOLT_SWITCH ITEM_TM127
#define ITEM_TM128_FLIP_TURN ITEM_TM128
#define ITEM_TM129_UP_ROOT ITEM_TM129
#define ITEM_TM130_DIVE_BOMB ITEM_TM130
#define ITEM_TM131_SUBSTITUTE ITEM_TM131
#define ITEM_TM132_FLASH_CANNON ITEM_TM132
#define ITEM_TM133_AGILITY ITEM_TM133
#define ITEM_TM134_TRICK_ROOM ITEM_TM134
#define ITEM_TM135_MAGIC_ROOM ITEM_TM135
#define ITEM_TM136_WONDER_ROOM ITEM_TM136
#define ITEM_TM137_GRAVITY ITEM_TM137
#define ITEM_TM138_DRAINING_KISS ITEM_TM138
#define ITEM_TM139_LEECH_LIFE ITEM_TM139
#define ITEM_TM140_FROST_BREATH ITEM_TM140
#define ITEM_TM141_WEATHER_BALL ITEM_TM141
#define ITEM_TM142_FLAME_CHARGE ITEM_TM142
#define ITEM_TM143_DUAL_WINGBEAT ITEM_TM143
#define ITEM_TM144_KNOCK_OFF ITEM_TM144
#define ITEM_TM145_BEAT_UP ITEM_TM145
#define ITEM_TM146_RAGE ITEM_TM146
#define ITEM_TM147_MAGIC_COAT ITEM_TM147
#define ITEM_TM148_ICICLE_SPEAR ITEM_TM148
#define ITEM_TM149_ACROBATICS ITEM_TM149
#define ITEM_TM150_ASSURANCE ITEM_TM150
#define ITEM_TM151_SOLAR_BLADE ITEM_TM151
#define ITEM_TM152_ICY_WIND ITEM_TM152
#define ITEM_TM153_METAL_CLAW ITEM_TM153
#define ITEM_TM154_HOLD_BACK ITEM_TM154
#define ITEM_TM155_HEADBUTT ITEM_TM155
#define ITEM_TM156_HI_JUMP_KICK ITEM_TM156
#define ITEM_TM157_DOUBLE_EDGE ITEM_TM157
#define ITEM_TM158_MISTY_EXPLOSION ITEM_TM158
#define ITEM_TM159_SNOWBALL ITEM_TM159
#define ITEM_TM160_ENERGY_BALL ITEM_TM160  
#define ITEM_TM161_CELEBRATE ITEM_TM161


#define ITEM_HM01_CUT ITEM_HM01
#define ITEM_HM02_FLY ITEM_HM02
#define ITEM_HM03_SURF ITEM_HM03
#define ITEM_HM04_STRENGTH ITEM_HM04
#define ITEM_HM05_FLASH ITEM_HM05
#define ITEM_HM06_ROCK_SMASH ITEM_HM06
#define ITEM_HM07_WATERFALL ITEM_HM07
#define ITEM_HM08_DIVE ITEM_HM08 //can add rock climb right after this simple enough
#define ITEM_HM09_ROCK_CLIMB ITEM_HM09 //will add, plan use rock climb to revolutionize cave mapping/travel, same as surf can be used as map transition

#define ITEM_MEGA_RING 459    
// FireRed/LeafGreen  believe this is key items actually maybe..?
#define ITEM_OAKS_PARCEL 460
#define ITEM_POKE_FLUTE 461
#define ITEM_SECRET_KEY 462
#define ITEM_BIKE_VOUCHER 463
#define ITEM_GOLD_TEETH 464
#define ITEM_OLD_AMBER 465		//aerodactyl
#define ITEM_CARD_KEY 466
#define ITEM_LIFT_KEY 467
#define ITEM_HELIX_FOSSIL 468	//omanyte
#define ITEM_DOME_FOSSIL 469	//kabuto
#define ITEM_SILPH_SCOPE 470
#define ITEM_BICYCLE 471
#define ITEM_TOWN_MAP 472
#define ITEM_VS_SEEKER 473
#define ITEM_FAME_CHECKER 474
#define ITEM_TM_CASE 475
#define ITEM_BERRY_POUCH 476
#define ITEM_TEACHY_TV 477
#define ITEM_OMNI_BOX 478 // tempt name, set pre status in partys
#define ITEM_TRI_PASS 479 //  AND they meet whatever other condition they have
#define ITEM_RAINBOW_PASS 480
#define ITEM_TEA 481
#define ITEM_MYSTIC_TICKET 482
#define ITEM_AURORA_TICKET 483 /*
#define ITEM_POWDER_JAR 483 */
#define ITEM_MAGMA_EMBLEM 484
#define ITEM_OLD_SEA_MAP 485
#define ITEM_RUBY 486
#define ITEM_SAPPHIRE 487
#define ITEM_ULTIMA_BRACE 488
#define ITEM_EV_SHACKLES  489
// Secondary Set of Use items  (mostly for evo) 
#define ITEM_CHOICE_SCARF 490  //need to change these items in items.json so they are evo items.
#define ITEM_CHOICE_SPECS 491 //don't forget to list in evolutions table as well
#define ITEM_FOCUS_SASH 492
#define ITEM_WIDE_LENS 493
#define ITEM_ZOOM_LENS 494
#define ITEM_METRONOME 495
//#define ITEM_LINK_CABLE 493 	// not gonna need this, if can just make use whatever item I want

#define ITEM_ABOMASITE 496
#define ITEM_ABSOLITE 497
#define ITEM_AERODACTYLITE 498
#define ITEM_AGGRONITE 499
#define ITEM_ALAKAZITE 500
#define ITEM_ALTARIANITE 501
#define ITEM_AMPHAROSITE 502
#define ITEM_AUDINITE 503
#define ITEM_BANETTITE 504
#define ITEM_BEEDRILLITE 505
#define ITEM_BLASTOISINITE 506
#define ITEM_BLAZIKENITE 507
#define ITEM_CAMERUPTITE 508
#define ITEM_CHARIZARDITE_X 509
#define ITEM_CHARIZARDITE_Y 510
#define ITEM_DIANCITE 511
#define ITEM_GALLADITE 512
#define ITEM_GARCHOMPITE 513
#define ITEM_GARDEVOIRITE 514
#define ITEM_GENGARITE 515
#define ITEM_GLALITITE 516
#define ITEM_GYARADOSITE 517
#define ITEM_HERACRONITE 518
#define ITEM_HOUNDOOMINITE 519
#define ITEM_KANGASKHANITE 520
#define ITEM_LATIASITE 521
#define ITEM_LATIOSITE 522
#define ITEM_LOPUNNITE 523
#define ITEM_LUCARIONITE 524
#define ITEM_MANECTITE 525
#define ITEM_MAWILITE 526
#define ITEM_MEDICHAMITE 527
#define ITEM_METAGROSSITE 528
#define ITEM_MEWTWONITE_X 529
#define ITEM_MEWTWONITE_Y 530
#define ITEM_PIDGEOTITE 531
#define ITEM_PINSIRITE 532
#define ITEM_SABLENITE 533
#define ITEM_SALAMENCITE 534
#define ITEM_SCEPTILITE 535
#define ITEM_SCIZORITE 536
#define ITEM_SHARPEDONITE 537
#define ITEM_SLOWBRONITE 538
#define ITEM_STEELIXITE 539
#define ITEM_SWAMPERTITE 540
#define ITEM_TYRANITARITE 541
#define ITEM_VENUSAURITE 542 //extra new megas below
#define ITEM_TORTERRAITE 543
#define ITEM_MAROWAKONITE 544//end of mega
//K looks like it doesn't matter where I put it except the use items,
// because effects and bag placement are set in the items.h file.
#define ITEM_MEGA_BRACELET 545 // should move set as key item.  //updated json item data should match
/*
//More hold items
// Z Crystals
#define ITEM_Z_RING                   569
#define ITEM_NORMALIUM_Z              570
#define ITEM_FIGHTINIUM_Z             571
#define ITEM_FLYINIUM_Z               572
#define ITEM_POISONIUM_Z              573
#define ITEM_GROUNDIUM_Z              574
#define ITEM_ROCKIUM_Z                575
#define ITEM_BUGINIUM_Z               576
#define ITEM_GHOSTIUM_Z               577
#define ITEM_STEELIUM_Z               578
#define ITEM_FIRIUM_Z                 579
#define ITEM_WATERIUM_Z               580
#define ITEM_GRASSIUM_Z               581
#define ITEM_ELECTRIUM_Z              582
#define ITEM_PSYCHIUM_Z               583
#define ITEM_ICIUM_Z                  584
#define ITEM_DRAGONIUM_Z              585
#define ITEM_DARKINIUM_Z              586
#define ITEM_FAIRIUM_Z                587
#define ITEM_ALORAICHIUM_Z            588
#define ITEM_DECIDIUM_Z               589
#define ITEM_EEVIUM_Z                 590
#define ITEM_INCINIUM_Z               591
#define ITEM_KOMMONIUM_Z              592
#define ITEM_LUNALIUM_Z               593
#define ITEM_LYCANIUM_Z               594
#define ITEM_MARSHADIUM_Z             595
#define ITEM_MEWNIUM_Z                596
#define ITEM_MIMIKIUM_Z               597
#define ITEM_PIKANIUM_Z               598
#define ITEM_PIKASHUNIUM_Z            599
#define ITEM_PRIMARIUM_Z              600
#define ITEM_SNORLIUM_Z               601
#define ITEM_SOLGANIUM_Z              602
#define ITEM_TAPUNIUM_Z               603
#define ITEM_ULTRANECROZIUM_Z         604
//3nd set non-use held items
#define ITEM_CHOICE_SCARF 267
#define ITEM_CHOICE_SPECS 268
#define ITEM_FOCUS_SASH 269
#define ITEM_WIDE_LENS 270
#define ITEM_ZOOM_LENS 271
#define ITEM_METRONOME 272
#define ITEM_MUSCLE_BAND 273
#define ITEM_WISE_GLASSES 274
#define ITEM_EXPERT_BELT 275
#define ITEM_LIGHT_CLAY 276
#define ITEM_ICY_ROCK 277
#define ITEM_SMOOTH_ROCK 278
#define ITEM_HEAT_ROCK 279
#define ITEM_DAMP_ROCK 280
#define ITEM_DESTINY_KNOT 281
#define ITEM_GRIP_CLAW 282      //when do item port, change to description to say reinforce trap effects (to match suction cups and give that better context) last 8 turns and last if user switches
#define ITEM_LIFE_ORB 283
#define ITEM_TOXIC_ORB 284
#define ITEM_FLAME_ORB 285
#define ITEM_SNOW_GLOBE 285  //set freeze status freeze dmg is 1/16 plan balance make freeze damage 1/8 when holding this also balanced by being frozen re-freeze odds hmm actually put that on item itself
#define ITEM_STICKY_BARB 286
#define ITEM_IRON_BALL 288
#define ITEM_LAGGING_TAIL 289
#define ITEM_SHED_SHELL 290
#define ITEM_BIG_ROOT 291
#define ITEM_FLOAT_STONE 293
#define ITEM_ROCKY_HELMET 294
#define ITEM_AIR_BALLOON 295
#define ITEM_RED_CARD 296
#define ITEM_RING_TARGET 297
#define ITEM_BINDING_BAND 298
#define ITEM_EJECT_BUTTON 299
#define ITEM_ABSORB_BULB 300
#define ITEM_CELL_BATTERY 301
#define ITEM_LUMINOUS_MOSS 302
#define ITEM_SNOWBALL 303
#define ITEM_WEAKNESS_POLICY 304
#define ITEM_ASSAULT_VEST 305
#define ITEM_SAFETY_GOGGLES 306
#define ITEM_ADRENALINE_ORB 307
#define ITEM_TERRAIN_EXTENDER 308
#define ITEM_PROTECTIVE_PADS 309
#define ITEM_ELECTRIC_SEED 310
#define ITEM_PSYCHIC_SEED 311
#define ITEM_MISTY_SEED 312
#define ITEM_GRASSY_SEED 313*/
//END of 3nd set of non Use items
//Start of 3nd use items
#define ITEM_UP_GRADE 546  //need to change these items in items.json so they are evo items.
#define ITEM_ELECTIRIZER 547 //don't forget to list in evolutions table as well
#define ITEM_MAGMARIZER 548
#define ITEM_DUBIOUS_DISC 549
#define ITEM_REAPER_CLOTH 550
#define ITEM_METAL_COAT 551
//Form Change Items
#define ITEM_ALOLAN_SAND     552
#define ITEM_GALAR_SAND     553
#define ITEM_HISUIAN_SAND     554
#define ITEM_PALDEAN_SAND   555 //rename use paldea stuff for select mon, just keep pokemon opal eeveelution as omage
// Incenses
#define ITEM_SEA_INCENSE 556
#define ITEM_LAX_INCENSE 557
#define ITEM_BLACK_SLUDGE 558
#define ITEM_BAD_ONION 559 //  ok these new values for incense are actually better, since they aren't supposed to be for use, just hold.



/*#define ITEM_ODD_INCENSE 387
#define ITEM_ROCK_INCENSE 388
#define ITEM_FULL_INCENSE 389
#define ITEM_WAVE_INCENSE 390
#define ITEM_ROSE_INCENSE 391
#define ITEM_LUCK_INCENSE 392
#define ITEM_PURE_INCENSE 393
// Plates          - changed arceus so not using these
#define ITEM_INSECT_PLATE 323
#define ITEM_DREAD_PLATE 324
#define ITEM_DRACO_PLATE 325
#define ITEM_ZAP_PLATE 326
#define ITEM_PIXIE_PLATE 327
#define ITEM_FIST_PLATE 328
#define ITEM_FLAME_PLATE 329
#define ITEM_SKY_PLATE 330
#define ITEM_SPOOKY_PLATE 331
#define ITEM_MEADOW_PLATE 332
#define ITEM_EARTH_PLATE 333
#define ITEM_ICICLE_PLATE 334
#define ITEM_TOXIC_PLATE 335
#define ITEM_MIND_PLATE 336
#define ITEM_STONE_PLATE 337
#define ITEM_IRON_PLATE 338
#define ITEM_SPLASH_PLATE 339
// Gems
#define ITEM_BUG_GEM 340
#define ITEM_DARK_GEM 341
#define ITEM_DRAGON_GEM 342
#define ITEM_ELECTRIC_GEM 343
#define ITEM_FAIRY_GEM 344
#define ITEM_FIGHTING_GEM 345
#define ITEM_FIRE_GEM 346
#define ITEM_FLYING_GEM 347
#define ITEM_GHOST_GEM 348
#define ITEM_GRASS_GEM 349
#define ITEM_GROUND_GEM 350
#define ITEM_ICE_GEM 351
#define ITEM_NORMAL_GEM 352
#define ITEM_POISON_GEM 353
#define ITEM_PSYCHIC_GEM 354
#define ITEM_ROCK_GEM 355
#define ITEM_STEEL_GEM 356
#define ITEM_WATER_GEM 357
#define ITEM_SOUND_GEM 358
// Memories
#define ITEM_BUG_MEMORY 372
#define ITEM_DARK_MEMORY 373
#define ITEM_DRAGON_MEMORY 374
#define ITEM_ELECTRIC_MEMORY 375
#define ITEM_FAIRY_MEMORY 376
#define ITEM_FIGHTING_MEMORY 377
#define ITEM_FIRE_MEMORY 378
#define ITEM_FLYING_MEMORY 379
#define ITEM_GHOST_MEMORY 380
#define ITEM_GRASS_MEMORY 381
#define ITEM_GROUND_MEMORY 382
#define ITEM_ICE_MEMORY 383
#define ITEM_POISON_MEMORY 384
#define ITEM_PSYCHIC_MEMORY 385
#define ITEM_ROCK_MEMORY 386
#define ITEM_STEEL_MEMORY 387
#define ITEM_WATER_MEMORY 388
// Drives
#define ITEM_DOUSE_DRIVE 389
#define ITEM_SHOCK_DRIVE 390
#define ITEM_BURN_DRIVE 391
#define ITEM_CHILL_DRIVE 392

//extra key items
#define ITEM_BEATER
#define ITEM_BEATER
#define ITEM_BEATER
#define ITEM_GRACIDEA
#define ITEM_ODD_KEYSTONE
#define ITEM_ADAMANT_ORB
#define ITEM_LUSTROUS_ORB
#define ITEM_GRISEOUS_ORB */


#define ITEM_SCENT_CASE 560 //USE TM CASE grahpic for holding region scent vials

//New Tms - w diff setup no longer need to hard lock number to item id I guess
#define ITEM_TM_FLASH_FREEZE 561
#define ITEM_TM_TRAILBLAZE 562
#define ITEM_TM_FOCUS_BLAST 563
#define ITEM_TM_PSYCHO_BOOST 564
#define ITEM_TM_FLATTER 565
#define ITEM_TM_AEROBLAST 566
#define ITEM_TM_SUPERPOWER 567
#define ITEM_SAFARI_BALL_2 568 //for safari expansion get around safari zone ball scripts
#define ITEM_TM_MOONDANCE 569
#define ITEM_TM_ACID_RAIN 570
#define ITEM_N_A 571 
// keep this as last item value, needs be +1 last defined item value   emerald stuff needs to be a separate value, otherwise seems to make duplicate error// keep this as last item value, needs be +1 last defined item value   emerald stuff needs to be a separate value, otherwise seems to make duplicate error
#define ITEMS_COUNT ITEM_N_A + 1
#define ITEM_FIELD_ARROW ITEM_N_A//field arrow isn't defined as an item, it just end of item_menu_icons.c list
// Emerald   BUT based on list from vanilla its actually ID was equal to items N_A, circumventing that equation.

#define LAST_ITEM_INDEX ITEM_N_A - 1

enum __attribute__((packed)) Item
{
    ITEM_NONE = 0,

    // Poké Balls
    ITEM_POKE_BALL = 1,
    ITEM_GREAT_BALL = 2,
    ITEM_ULTRA_BALL = 3,
    ITEM_MASTER_BALL = 4,
    ITEM_PREMIER_BALL = 5,
    ITEM_HEAL_BALL = 6,
    ITEM_NET_BALL = 7,
    ITEM_NEST_BALL = 8,
    ITEM_DIVE_BALL = 9,
    ITEM_DUSK_BALL = 10,
    ITEM_TIMER_BALL = 11,
    ITEM_QUICK_BALL = 12,
    ITEM_REPEAT_BALL = 13,
    ITEM_LUXURY_BALL = 14,
    ITEM_LEVEL_BALL = 15,
    ITEM_LURE_BALL = 16,
    ITEM_MOON_BALL = 17,
    ITEM_FRIEND_BALL = 18,
    ITEM_LOVE_BALL = 19,
    ITEM_FAST_BALL = 20,
    ITEM_HEAVY_BALL = 21,
    ITEM_DREAM_BALL = 22,
    ITEM_SAFARI_BALL = 23,
    ITEM_SPORT_BALL = 24,
    ITEM_PARK_BALL = 25,
    ITEM_BEAST_BALL = 26,
    ITEM_CHERISH_BALL = 27,

    // Medicine
    ITEM_POTION = 28,
    ITEM_SUPER_POTION = 29,
    ITEM_HYPER_POTION = 30,
    ITEM_MAX_POTION = 31,
    ITEM_FULL_RESTORE = 32,
    ITEM_REVIVE = 33,
    ITEM_MAX_REVIVE = 34,
    ITEM_FRESH_WATER = 35,
    ITEM_SODA_POP = 36,
    ITEM_LEMONADE = 37,
    ITEM_MOOMOO_MILK = 38,
    ITEM_ENERGY_POWDER = 39,
    ITEM_ENERGYPOWDER = ITEM_ENERGY_POWDER, // Pre-Gen VI name
    ITEM_ENERGY_ROOT = 40,
    ITEM_HEAL_POWDER = 41,
    ITEM_REVIVAL_HERB = 42,
    ITEM_ANTIDOTE = 43,
    ITEM_PARALYZE_HEAL = 44,
    ITEM_PARLYZ_HEAL = ITEM_PARALYZE_HEAL, // Pre-Gen VI name
    ITEM_BURN_HEAL = 45,
    ITEM_ICE_HEAL = 46,
    ITEM_AWAKENING = 47,
    ITEM_FULL_HEAL = 48,
    ITEM_ETHER = 49,
    ITEM_MAX_ETHER = 50,
    ITEM_ELIXIR = 51,
    ITEM_MAX_ELIXIR = 52,
    ITEM_BERRY_JUICE = 53,
    ITEM_SACRED_ASH = 54,
    ITEM_SWEET_HEART = 55,
    ITEM_MAX_HONEY = 56,

    // Regional Specialties
    ITEM_PEWTER_CRUNCHIES = 57,
    ITEM_RAGE_CANDY_BAR = 58,
    ITEM_RAGECANDYBAR = ITEM_RAGE_CANDY_BAR, // Pre-Gen VI name
    ITEM_LAVA_COOKIE = 59,
    ITEM_OLD_GATEAU = 60,
    ITEM_CASTELIACONE = 61,
    ITEM_LUMIOSE_GALETTE = 62,
    ITEM_SHALOUR_SABLE = 63,
    ITEM_BIG_MALASADA = 64,

    // Vitamins
    ITEM_HP_UP = 65,
    ITEM_PROTEIN = 66,
    ITEM_IRON = 67,
    ITEM_CALCIUM = 68,
    ITEM_ZINC = 69,
    ITEM_CARBOS = 70,
    ITEM_PP_UP = 71,
    ITEM_PP_MAX = 72,

    // EV Feathers
    ITEM_HEALTH_FEATHER = 73,
    ITEM_HEALTH_WING = ITEM_HEALTH_FEATHER, // Pre-Gen VIII name
    ITEM_MUSCLE_FEATHER = 74,
    ITEM_MUSCLE_WING = ITEM_MUSCLE_FEATHER, // Pre-Gen VIII name
    ITEM_RESIST_FEATHER = 75,
    ITEM_RESIST_WING = ITEM_RESIST_FEATHER, // Pre-Gen VIII name
    ITEM_GENIUS_FEATHER = 76,
    ITEM_GENIUS_WING = ITEM_GENIUS_FEATHER, // Pre-Gen VIII name
    ITEM_CLEVER_FEATHER = 77,
    ITEM_CLEVER_WING = ITEM_CLEVER_FEATHER, // Pre-Gen VIII name
    ITEM_SWIFT_FEATHER = 78,
    ITEM_SWIFT_WING = ITEM_SWIFT_FEATHER, // Pre-Gen VIII name

    // Ability Modifiers -consolidating just make 1 item for both
    ITEM_ABILITY_CAPSULE = 79,
    ITEM_ABILITY_PATCH = 80,

    // Mints
    ITEM_LONELY_MINT = 81,
    ITEM_ADAMANT_MINT = 82,
    ITEM_NAUGHTY_MINT = 83,
    ITEM_BRAVE_MINT = 84,
    ITEM_BOLD_MINT = 85,
    ITEM_IMPISH_MINT = 86,
    ITEM_LAX_MINT = 87,
    ITEM_RELAXED_MINT = 88,
    ITEM_MODEST_MINT = 89,
    ITEM_MILD_MINT = 90,
    ITEM_RASH_MINT = 91,
    ITEM_QUIET_MINT = 92,
    ITEM_CALM_MINT = 93,
    ITEM_GENTLE_MINT = 94,
    ITEM_CAREFUL_MINT = 95,
    ITEM_SASSY_MINT = 96,
    ITEM_TIMID_MINT = 97,
    ITEM_HASTY_MINT = 98,
    ITEM_JOLLY_MINT = 99,
    ITEM_NAIVE_MINT = 100,
    ITEM_SERIOUS_MINT = 101,

    // Candy
    ITEM_RARE_CANDY = 102,
    ITEM_EXP_CANDY_XS = 103,
    ITEM_EXP_CANDY_S = 104,
    ITEM_EXP_CANDY_M = 105,
    ITEM_EXP_CANDY_L = 106,
    ITEM_EXP_CANDY_XL = 107,
    ITEM_DYNAMAX_CANDY = 108,

    // Medicinal Flutes
    ITEM_BLUE_FLUTE = 109,
    ITEM_YELLOW_FLUTE = 110,
    ITEM_RED_FLUTE = 111,

    // Encounter-modifying Flutes
    ITEM_BLACK_FLUTE = 112,
    ITEM_WHITE_FLUTE = 113,

    // Encounter Modifiers
    ITEM_REPEL = 114,
    ITEM_SUPER_REPEL = 115,
    ITEM_MAX_REPEL = 116,
    ITEM_LURE = 117,
    ITEM_SUPER_LURE = 118,
    ITEM_MAX_LURE = 119,

    ITEM_ESCAPE_ROPE = 120,

    // X Items
    ITEM_X_ATTACK = 121,
    ITEM_X_DEFENSE = 122,
    ITEM_X_DEFEND = ITEM_X_DEFENSE, // Pre-Gen VI name
    ITEM_X_SP_ATK = 123,
    ITEM_X_SPECIAL = ITEM_X_SP_ATK, // Pre-Gen VI name
    ITEM_X_SP_DEF = 124,
    ITEM_X_SPEED = 125,
    ITEM_X_ACCURACY = 126,

    ITEM_DIRE_HIT = 127,
    ITEM_GUARD_SPEC = 128,

    // Escape Items
    ITEM_POKE_DOLL = 129,
    ITEM_FLUFFY_TAIL = 130,
    ITEM_POKE_TOY = 131,

    ITEM_MAX_MUSHROOMS = 132,

    // Treasures
    ITEM_BOTTLE_CAP = 133,
    ITEM_GOLD_BOTTLE_CAP = 134,
    ITEM_NUGGET = 135,
    ITEM_BIG_NUGGET = 136,
    ITEM_TINY_MUSHROOM = 137,
    ITEM_TINYMUSHROOM = ITEM_TINY_MUSHROOM, // Pre-Gen VI name
    ITEM_BIG_MUSHROOM = 138,
    ITEM_BALM_MUSHROOM = 139,
    ITEM_BALMMUSHROOM = ITEM_BALM_MUSHROOM, // Pre-Gen VI name
    ITEM_PEARL = 140,
    ITEM_BIG_PEARL = 141,
    ITEM_PEARL_STRING = 142,
    ITEM_STARDUST = 143,
    ITEM_STAR_PIECE = 144,
    ITEM_COMET_SHARD = 145,
    ITEM_SHOAL_SALT = 146,
    ITEM_SHOAL_SHELL = 147,
    ITEM_RED_SHARD = 148,
    ITEM_BLUE_SHARD = 149,
    ITEM_YELLOW_SHARD = 150,
    ITEM_GREEN_SHARD = 151,
    ITEM_HEART_SCALE = 152,
    ITEM_HONEY = 153,
    ITEM_RARE_BONE = 154,
    ITEM_ODD_KEYSTONE = 155,
    ITEM_PRETTY_FEATHER = 156,
    ITEM_PRETTY_WING = ITEM_PRETTY_FEATHER, // Pre-Gen VIII name
    ITEM_RELIC_COPPER = 157,
    ITEM_RELIC_SILVER = 158,
    ITEM_RELIC_GOLD = 159,
    ITEM_RELIC_VASE = 160,
    ITEM_RELIC_BAND = 161,
    ITEM_RELIC_STATUE = 162,
    ITEM_RELIC_CROWN = 163,
    ITEM_STRANGE_SOUVENIR = 164,

    // Fossils
    ITEM_HELIX_FOSSIL = 165,
    ITEM_DOME_FOSSIL = 166,
    ITEM_OLD_AMBER = 167,
    ITEM_ROOT_FOSSIL = 168,
    ITEM_CLAW_FOSSIL = 169,
    ITEM_ARMOR_FOSSIL = 170,
    ITEM_SKULL_FOSSIL = 171,
    ITEM_COVER_FOSSIL = 172,
    ITEM_PLUME_FOSSIL = 173,
    ITEM_JAW_FOSSIL = 174,
    ITEM_SAIL_FOSSIL = 175,
    ITEM_FOSSILIZED_BIRD = 176,
    ITEM_FOSSILIZED_FISH = 177,
    ITEM_FOSSILIZED_DRAKE = 178,
    ITEM_FOSSILIZED_DINO = 179,

    // Mulch
    ITEM_GROWTH_MULCH = 180,
    ITEM_DAMP_MULCH = 181,
    ITEM_STABLE_MULCH = 182,
    ITEM_GOOEY_MULCH = 183,
    ITEM_RICH_MULCH = 184,
    ITEM_SURPRISE_MULCH = 185,
    ITEM_BOOST_MULCH = 186,
    ITEM_AMAZE_MULCH = 187,

    // Apricorns
    ITEM_RED_APRICORN = 188,
    ITEM_BLUE_APRICORN = 189,
    ITEM_BLU_APRICORN = ITEM_BLUE_APRICORN, // Pre-Gen VI name
    ITEM_YELLOW_APRICORN = 190,
    ITEM_YLW_APRICORN = ITEM_YELLOW_APRICORN, // Pre-Gen VI name
    ITEM_GREEN_APRICORN = 191,
    ITEM_GRN_APRICORN = ITEM_GREEN_APRICORN, // Pre-Gen VI name
    ITEM_PINK_APRICORN = 192,
    ITEM_PNK_APRICORN = ITEM_PINK_APRICORN, // Pre-Gen VI name
    ITEM_WHITE_APRICORN = 193,
    ITEM_WHT_APRICORN = ITEM_WHITE_APRICORN, // Pre-Gen VI name
    ITEM_BLACK_APRICORN = 194,
    ITEM_BLK_APRICORN = ITEM_BLACK_APRICORN, // Pre-Gen VI name

    ITEM_WISHING_PIECE = 195,
    ITEM_GALARICA_TWIG = 196,
    ITEM_ARMORITE_ORE = 197,
    ITEM_DYNITE_ORE = 198,

    // Mail
    FIRST_MAIL_INDEX = 199,
    ITEM_ORANGE_MAIL = FIRST_MAIL_INDEX,
    ITEM_HARBOR_MAIL = 200,
    ITEM_GLITTER_MAIL = 201,
    ITEM_MECH_MAIL = 202,
    ITEM_WOOD_MAIL = 203,
    ITEM_WAVE_MAIL = 204,
    ITEM_BEAD_MAIL = 205,
    ITEM_SHADOW_MAIL = 206,
    ITEM_TROPIC_MAIL = 207,
    ITEM_DREAM_MAIL = 208,
    ITEM_FAB_MAIL = 209,
    ITEM_RETRO_MAIL = 210,

    // Evolution Items
    ITEM_FIRE_STONE = 211,
    ITEM_WATER_STONE = 212,
    ITEM_THUNDER_STONE = 213,
    ITEM_THUNDERSTONE = ITEM_THUNDER_STONE, // Pre-Gen VI name
    ITEM_LEAF_STONE = 214,
    ITEM_ICE_STONE = 215,
    ITEM_SUN_STONE = 216,
    ITEM_MOON_STONE = 217,
    ITEM_SHINY_STONE = 218, //IN GAME call dazzling stone
    ITEM_DUSK_STONE = 219,
    ITEM_DAWN_STONE = 220,
    ITEM_SWEET_APPLE = 221,
    ITEM_TART_APPLE = 222,
    ITEM_CRACKED_POT = 223,
    ITEM_CHIPPED_POT = 224,
    ITEM_GALARICA_CUFF = 225,
    ITEM_GALARICA_WREATH = 226,
    ITEM_DRAGON_SCALE = 227,
    ITEM_UPGRADE = 228,
    ITEM_UP_GRADE = ITEM_UPGRADE, // Pre-Gen VIII name
    ITEM_PROTECTOR = 229,
    ITEM_ELECTIRIZER = 230,
    ITEM_MAGMARIZER = 231,
    ITEM_DUBIOUS_DISC = 232,
    ITEM_REAPER_CLOTH = 233,
    ITEM_PRISM_SCALE = 234,
    ITEM_WHIPPED_DREAM = 235,
    ITEM_SACHET = 236,
    ITEM_OVAL_STONE = 237,
    ITEM_STRAWBERRY_SWEET = 238,
    ITEM_LOVE_SWEET = 239,
    ITEM_BERRY_SWEET = 240,
    ITEM_CLOVER_SWEET = 241,
    ITEM_FLOWER_SWEET = 242,
    ITEM_STAR_SWEET = 243,
    ITEM_RIBBON_SWEET = 244,

    ITEM_EVERSTONE = 245,

    //Form change non-key items
    // Nectars
    ITEM_RED_NECTAR = 246,
    ITEM_YELLOW_NECTAR = 247,
    ITEM_PINK_NECTAR = 248,
    ITEM_PURPLE_NECTAR = 249,

    // Plates
    ITEM_FLAME_PLATE = 250,
    ITEM_SPLASH_PLATE = 251,
    ITEM_ZAP_PLATE = 252,
    ITEM_MEADOW_PLATE = 253,
    ITEM_ICICLE_PLATE = 254,
    ITEM_FIST_PLATE = 255,
    ITEM_TOXIC_PLATE = 256,
    ITEM_EARTH_PLATE = 257,
    ITEM_SKY_PLATE = 258,
    ITEM_MIND_PLATE = 259,
    ITEM_INSECT_PLATE = 260,
    ITEM_STONE_PLATE = 261,
    ITEM_SPOOKY_PLATE = 262,
    ITEM_DRACO_PLATE = 263,
    ITEM_DREAD_PLATE = 264,
    ITEM_IRON_PLATE = 265,
    ITEM_PIXIE_PLATE = 266,

    // Drives
    ITEM_DOUSE_DRIVE = 267,
    ITEM_SHOCK_DRIVE = 268,
    ITEM_BURN_DRIVE = 269,
    ITEM_CHILL_DRIVE = 270,

    // Memories
    ITEM_FIRE_MEMORY = 271,
    ITEM_WATER_MEMORY = 272,
    ITEM_ELECTRIC_MEMORY = 273,
    ITEM_GRASS_MEMORY = 274,
    ITEM_ICE_MEMORY = 275,
    ITEM_FIGHTING_MEMORY = 276,
    ITEM_POISON_MEMORY = 277,
    ITEM_GROUND_MEMORY = 278,
    ITEM_FLYING_MEMORY = 279,
    ITEM_PSYCHIC_MEMORY = 280,
    ITEM_BUG_MEMORY = 281,
    ITEM_ROCK_MEMORY = 282,
    ITEM_GHOST_MEMORY = 283,
    ITEM_DRAGON_MEMORY = 284,
    ITEM_DARK_MEMORY = 285,
    ITEM_STEEL_MEMORY = 286,
    ITEM_FAIRY_MEMORY = 287,

    ITEM_RUSTED_SWORD = 288,
    ITEM_RUSTED_SHIELD = 289,

    // Colored Orbs
    ITEM_RED_ORB = 290,
    ITEM_BLUE_ORB = 291,

    // Mega Stones
    ITEM_VENUSAURITE = 292,
    ITEM_CHARIZARDITE_X = 293,
    ITEM_CHARIZARDITE_Y = 294,
    ITEM_BLASTOISINITE = 295,
    ITEM_BEEDRILLITE = 296,
    ITEM_PIDGEOTITE = 297,
    ITEM_ALAKAZITE = 298,
    ITEM_SLOWBRONITE = 299,
    ITEM_GENGARITE = 300,
    ITEM_KANGASKHANITE = 301,
    ITEM_PINSIRITE = 302,
    ITEM_GYARADOSITE = 303,
    ITEM_AERODACTYLITE = 304,
    ITEM_MEWTWONITE_X = 305,
    ITEM_MEWTWONITE_Y = 306,
    ITEM_AMPHAROSITE = 307,
    ITEM_STEELIXITE = 308,
    ITEM_SCIZORITE = 309,
    ITEM_HERACRONITE = 310,
    ITEM_HOUNDOOMINITE = 311,
    ITEM_TYRANITARITE = 312,
    ITEM_SCEPTILITE = 313,
    ITEM_BLAZIKENITE = 314,
    ITEM_SWAMPERTITE = 315,
    ITEM_GARDEVOIRITE = 316,
    ITEM_SABLENITE = 317,
    ITEM_MAWILITE = 318,
    ITEM_AGGRONITE = 319,
    ITEM_MEDICHAMITE = 320,
    ITEM_MANECTITE = 321,
    ITEM_SHARPEDONITE = 322,
    ITEM_CAMERUPTITE = 323,
    ITEM_ALTARIANITE = 324,
    ITEM_BANETTITE = 325,
    ITEM_ABSOLITE = 326,
    ITEM_GLALITITE = 327,
    ITEM_SALAMENCITE = 328,
    ITEM_METAGROSSITE = 329,
    ITEM_LATIASITE = 330,
    ITEM_LATIOSITE = 331,
    ITEM_LOPUNNITE = 332,
    ITEM_GARCHOMPITE = 333,
    ITEM_LUCARIONITE = 334,
    ITEM_ABOMASITE = 335,
    ITEM_GALLADITE = 336,
    ITEM_AUDINITE = 337,
    ITEM_DIANCITE = 338,

    // Gems
    ITEM_NORMAL_GEM = 339,
    ITEM_FIRE_GEM = 340,
    ITEM_WATER_GEM = 341,
    ITEM_ELECTRIC_GEM = 342,
    ITEM_GRASS_GEM = 343,
    ITEM_ICE_GEM = 344,
    ITEM_FIGHTING_GEM = 345,
    ITEM_POISON_GEM = 346,
    ITEM_GROUND_GEM = 347,
    ITEM_FLYING_GEM = 348,
    ITEM_PSYCHIC_GEM = 349,
    ITEM_BUG_GEM = 350,
    ITEM_ROCK_GEM = 351,
    ITEM_GHOST_GEM = 352,
    ITEM_DRAGON_GEM = 353,
    ITEM_DARK_GEM = 354,
    ITEM_STEEL_GEM = 355,
    ITEM_FAIRY_GEM = 356,

    // Z-Crystals
    ITEM_NORMALIUM_Z = 357,
    ITEM_FIRIUM_Z = 358,
    ITEM_WATERIUM_Z = 359,
    ITEM_ELECTRIUM_Z = 360,
    ITEM_GRASSIUM_Z = 361,
    ITEM_ICIUM_Z = 362,
    ITEM_FIGHTINIUM_Z = 363,
    ITEM_POISONIUM_Z = 364,
    ITEM_GROUNDIUM_Z = 365,
    ITEM_FLYINIUM_Z = 366,
    ITEM_PSYCHIUM_Z = 367,
    ITEM_BUGINIUM_Z = 368,
    ITEM_ROCKIUM_Z = 369,
    ITEM_GHOSTIUM_Z = 370,
    ITEM_DRAGONIUM_Z = 371,
    ITEM_DARKINIUM_Z = 372,
    ITEM_STEELIUM_Z = 373,
    ITEM_FAIRIUM_Z = 374,
    ITEM_PIKANIUM_Z = 375,
    ITEM_EEVIUM_Z = 376,
    ITEM_SNORLIUM_Z = 377,
    ITEM_MEWNIUM_Z = 378,
    ITEM_DECIDIUM_Z = 379,
    ITEM_INCINIUM_Z = 380,
    ITEM_PRIMARIUM_Z = 381,
    ITEM_LYCANIUM_Z = 382,
    ITEM_MIMIKIUM_Z = 383,
    ITEM_KOMMONIUM_Z = 384,
    ITEM_TAPUNIUM_Z = 385,
    ITEM_SOLGANIUM_Z = 386,
    ITEM_LUNALIUM_Z = 387,
    ITEM_MARSHADIUM_Z = 388,
    ITEM_ALORAICHIUM_Z = 389,
    ITEM_PIKASHUNIUM_Z = 390,
    ITEM_ULTRANECROZIUM_Z = 391,

    // Species-specific Held Items
    ITEM_LIGHT_BALL = 392,
    ITEM_LEEK = 393,
    ITEM_STICK = ITEM_LEEK, // Pre-Gen VIII name
    ITEM_THICK_CLUB = 394,
    ITEM_LUCKY_PUNCH = 395,
    ITEM_METAL_POWDER = 396,
    ITEM_QUICK_POWDER = 397,
    ITEM_DEEP_SEA_SCALE = 398,
    ITEM_DEEPSEASCALE = ITEM_DEEP_SEA_SCALE, // Pre-Gen VI name
    ITEM_DEEP_SEA_TOOTH = 399,
    ITEM_DEEPSEATOOTH = ITEM_DEEP_SEA_TOOTH, // Pre-Gen VI name
    ITEM_SOUL_DEW = 400,
    ITEM_ADAMANT_ORB = 401,
    ITEM_LUSTROUS_ORB = 402,
    ITEM_GRISEOUS_ORB = 403,

    // Incenses
    ITEM_SEA_INCENSE = 404,
    ITEM_LAX_INCENSE = 405,
    ITEM_ODD_INCENSE = 406,
    ITEM_ROCK_INCENSE = 407,
    ITEM_FULL_INCENSE = 408,
    ITEM_WAVE_INCENSE = 409,
    ITEM_ROSE_INCENSE = 410,
    ITEM_LUCK_INCENSE = 411,
    ITEM_PURE_INCENSE = 412,

    // Contest Scarves
    ITEM_RED_SCARF = 413,
    ITEM_BLUE_SCARF = 414,
    ITEM_PINK_SCARF = 415,
    ITEM_GREEN_SCARF = 416,
    ITEM_YELLOW_SCARF = 417,

    // EV Gain Modifiers
    ITEM_MACHO_BRACE = 418,
    ITEM_POWER_WEIGHT = 419,
    ITEM_POWER_BRACER = 420,
    ITEM_POWER_BELT = 421,
    ITEM_POWER_LENS = 422,
    ITEM_POWER_BAND = 423,
    ITEM_POWER_ANKLET = 424,

    // Type-boosting Held Items
    ITEM_SILK_SCARF = 425,
    ITEM_CHARCOAL = 426,
    ITEM_MYSTIC_WATER = 427,
    ITEM_MAGNET = 428,
    ITEM_MIRACLE_SEED = 429,
    ITEM_NEVER_MELT_ICE = 430,
    ITEM_NEVERMELTICE = ITEM_NEVER_MELT_ICE, // Pre-Gen VI name
    ITEM_BLACK_BELT = 431,
    ITEM_BLACKBELT = ITEM_BLACK_BELT, // Gen II name
    ITEM_POISON_BARB = 432,
    ITEM_SOFT_SAND = 433,
    ITEM_SHARP_BEAK = 434,
    ITEM_TWISTED_SPOON = 435,
    ITEM_TWISTEDSPOON = ITEM_TWISTED_SPOON, // Pre-Gen VI name
    ITEM_SILVER_POWDER = 436,
    ITEM_SILVERPOWDER = ITEM_SILVER_POWDER, // Pre-Gen VI name
    ITEM_HARD_STONE = 437,
    ITEM_SPELL_TAG = 438,
    ITEM_DRAGON_FANG = 439,
    ITEM_BLACK_GLASSES = 440,
    ITEM_BLACKGLASSES = ITEM_BLACK_GLASSES, // Pre-Gen VI name
    ITEM_METAL_COAT = 441,

    // Choice Items
    ITEM_CHOICE_BAND = 442,
    ITEM_CHOICE_SPECS = 443,
    ITEM_CHOICE_SCARF = 444,

    // Status Orbs
    ITEM_FLAME_ORB = 445,
    ITEM_TOXIC_ORB = 446,

    // Weather Rocks
    ITEM_DAMP_ROCK = 447,
    ITEM_HEAT_ROCK = 448,
    ITEM_SMOOTH_ROCK = 449,
    ITEM_ICY_ROCK = 450,

    // Terrain Seeds
    ITEM_ELECTRIC_SEED = 451,
    ITEM_PSYCHIC_SEED = 452,
    ITEM_MISTY_SEED = 453,
    ITEM_GRASSY_SEED = 454,

    // Type-activated Stat Modifiers
    ITEM_ABSORB_BULB = 455,
    ITEM_CELL_BATTERY = 456,
    ITEM_LUMINOUS_MOSS = 457,
    ITEM_SNOWBALL = 458,

    // Misc. Held Items
    ITEM_BRIGHT_POWDER = 459,
    ITEM_BRIGHTPOWDER = ITEM_BRIGHT_POWDER, // Pre-Gen VI name
    ITEM_WHITE_HERB = 460,
    ITEM_EXP_SHARE = 461,
    ITEM_EXP_ALL = ITEM_EXP_SHARE, // Gen I name
    ITEM_QUICK_CLAW = 462,
    ITEM_SOOTHE_BELL = 463,
    ITEM_MENTAL_HERB = 464,
    ITEM_KINGS_ROCK = 465,
    ITEM_AMULET_COIN = 466,
    ITEM_CLEANSE_TAG = 467,
    ITEM_SMOKE_BALL = 468,
    ITEM_FOCUS_BAND = 469,
    ITEM_LUCKY_EGG = 470,
    ITEM_SCOPE_LENS = 471,
    ITEM_LEFTOVERS = 472,
    ITEM_SHELL_BELL = 473,
    ITEM_WIDE_LENS = 474,
    ITEM_MUSCLE_BAND = 475,
    ITEM_WISE_GLASSES = 476,
    ITEM_EXPERT_BELT = 477,
    ITEM_LIGHT_CLAY = 478,
    ITEM_LIFE_ORB = 479,
    ITEM_POWER_HERB = 480,
    ITEM_FOCUS_SASH = 481,
    ITEM_ZOOM_LENS = 482,
    ITEM_METRONOME = 483,
    ITEM_IRON_BALL = 484,
    ITEM_LAGGING_TAIL = 485,
    ITEM_DESTINY_KNOT = 486,
    ITEM_BLACK_SLUDGE = 487,
    ITEM_GRIP_CLAW = 488,
    ITEM_STICKY_BARB = 489,
    ITEM_SHED_SHELL = 490,
    ITEM_BIG_ROOT = 491,
    ITEM_RAZOR_CLAW = 492,
    ITEM_RAZOR_FANG = 493,
    ITEM_EVIOLITE = 494,
    ITEM_FLOAT_STONE = 495,
    ITEM_ROCKY_HELMET = 496,
    ITEM_AIR_BALLOON = 497,
    ITEM_RED_CARD = 498,
    ITEM_RING_TARGET = 499,
    ITEM_BINDING_BAND = 500,
    ITEM_EJECT_BUTTON = 501,
    ITEM_WEAKNESS_POLICY = 502,
    ITEM_ASSAULT_VEST = 503,
    ITEM_SAFETY_GOGGLES = 504,
    ITEM_ADRENALINE_ORB = 505,
    ITEM_TERRAIN_EXTENDER = 506,
    ITEM_PROTECTIVE_PADS = 507,
    ITEM_THROAT_SPRAY = 508,
    ITEM_EJECT_PACK = 509,
    ITEM_HEAVY_DUTY_BOOTS = 510,
    ITEM_BLUNDER_POLICY = 511,
    ITEM_ROOM_SERVICE = 512,
    ITEM_UTILITY_UMBRELLA = 513,

    // Berries
    FIRST_BERRY_INDEX = 514,
    ITEM_CHERI_BERRY = FIRST_BERRY_INDEX,
    ITEM_CHESTO_BERRY = 515,
    ITEM_PECHA_BERRY = 516,
    ITEM_RAWST_BERRY = 517,
    ITEM_ASPEAR_BERRY = 518,
    ITEM_LEPPA_BERRY = 519,
    ITEM_ORAN_BERRY = 520,
    ITEM_PERSIM_BERRY = 521,
    ITEM_LUM_BERRY = 522,
    ITEM_SITRUS_BERRY = 523,
    ITEM_FIGY_BERRY = 524,
    ITEM_WIKI_BERRY = 525,
    ITEM_MAGO_BERRY = 526,
    ITEM_AGUAV_BERRY = 527,
    ITEM_IAPAPA_BERRY = 528,
    ITEM_RAZZ_BERRY = 529,
    ITEM_BLUK_BERRY = 530,
    ITEM_NANAB_BERRY = 531,
    ITEM_WEPEAR_BERRY = 532,
    ITEM_PINAP_BERRY = 533,
    ITEM_POMEG_BERRY = 534,
    ITEM_KELPSY_BERRY = 535,
    ITEM_QUALOT_BERRY = 536,
    ITEM_HONDEW_BERRY = 537,
    ITEM_GREPA_BERRY = 538,
    ITEM_TAMATO_BERRY = 539,
    ITEM_CORNN_BERRY = 540,
    ITEM_MAGOST_BERRY = 541,
    ITEM_RABUTA_BERRY = 542,
    ITEM_NOMEL_BERRY = 543,
    ITEM_SPELON_BERRY = 544,
    ITEM_PAMTRE_BERRY = 545,
    ITEM_WATMEL_BERRY = 546,
    ITEM_DURIN_BERRY = 547,
    ITEM_BELUE_BERRY = 548,
    ITEM_CHILAN_BERRY = 549,
    ITEM_OCCA_BERRY = 550,
    ITEM_PASSHO_BERRY = 551,
    ITEM_WACAN_BERRY = 552,
    ITEM_RINDO_BERRY = 553,
    ITEM_YACHE_BERRY = 554,
    ITEM_CHOPLE_BERRY = 555,
    ITEM_KEBIA_BERRY = 556,
    ITEM_SHUCA_BERRY = 557,
    ITEM_COBA_BERRY = 558,
    ITEM_PAYAPA_BERRY = 559,
    ITEM_TANGA_BERRY = 560,
    ITEM_CHARTI_BERRY = 561,
    ITEM_KASIB_BERRY = 562,
    ITEM_HABAN_BERRY = 563,
    ITEM_COLBUR_BERRY = 564,
    ITEM_BABIRI_BERRY = 565,
    ITEM_ROSELI_BERRY = 566,
    ITEM_LIECHI_BERRY = 567,
    ITEM_GANLON_BERRY = 568,
    ITEM_SALAC_BERRY = 569,
    ITEM_PETAYA_BERRY = 570,
    ITEM_APICOT_BERRY = 571,
    ITEM_LANSAT_BERRY = 572,
    ITEM_STARF_BERRY = 573,
    ITEM_ENIGMA_BERRY = 574,
    ITEM_MICLE_BERRY = 575,
    ITEM_CUSTAP_BERRY = 576,
    ITEM_JABOCA_BERRY = 577,
    ITEM_ROWAP_BERRY = 578,
    ITEM_KEE_BERRY = 579,
    ITEM_MARANGA_BERRY = 580,
    ITEM_ENIGMA_BERRY_E_READER = 581,
    LAST_BERRY_INDEX =  ITEM_ENIGMA_BERRY_E_READER,

    // TMs/HMs
    ITEM_TM01 = 582,
    ITEM_TM02 = 583,
    ITEM_TM03 = 584,
    ITEM_TM04 = 585,
    ITEM_TM05 = 586,
    ITEM_TM06 = 587,
    ITEM_TM07 = 588,
    ITEM_TM08 = 589,
    ITEM_TM09 = 590,
    ITEM_TM10 = 591,
    ITEM_TM11 = 592,
    ITEM_TM12 = 593,
    ITEM_TM13 = 594,
    ITEM_TM14 = 595,
    ITEM_TM15 = 596,
    ITEM_TM16 = 597,
    ITEM_TM17 = 598,
    ITEM_TM18 = 599,
    ITEM_TM19 = 600,
    ITEM_TM20 = 601,
    ITEM_TM21 = 602,
    ITEM_TM22 = 603,
    ITEM_TM23 = 604,
    ITEM_TM24 = 605,
    ITEM_TM25 = 606,
    ITEM_TM26 = 607,
    ITEM_TM27 = 608,
    ITEM_TM28 = 609,
    ITEM_TM29 = 610,
    ITEM_TM30 = 611,
    ITEM_TM31 = 612,
    ITEM_TM32 = 613,
    ITEM_TM33 = 614,
    ITEM_TM34 = 615,
    ITEM_TM35 = 616,
    ITEM_TM36 = 617,
    ITEM_TM37 = 618,
    ITEM_TM38 = 619,
    ITEM_TM39 = 620,
    ITEM_TM40 = 621,
    ITEM_TM41 = 622,
    ITEM_TM42 = 623,
    ITEM_TM43 = 624,
    ITEM_TM44 = 625,
    ITEM_TM45 = 626,
    ITEM_TM46 = 627,
    ITEM_TM47 = 628,
    ITEM_TM48 = 629,
    ITEM_TM49 = 630,
    ITEM_TM50 = 631,
    //Tm Expansion cut values above this
    //have add on to end using py script update
    //using created list
    //attempt use py script to update this
    //copy previous value increment each line that digit , is found
    //if works should be able to sub and just update by deleting these
    //-50 for all below values
    ITEM_TM51 = 632,
    ITEM_TM52 = 633,
    ITEM_TM53 = 634,
    ITEM_TM54 = 635,
    ITEM_TM55 = 636,
    ITEM_TM56 = 637,
    ITEM_TM57 = 638,
    ITEM_TM58 = 639,
    ITEM_TM59 = 640,
    ITEM_TM60 = 641,
    ITEM_TM61 = 642,
    ITEM_TM62 = 643,
    ITEM_TM63 = 644,
    ITEM_TM64 = 645,
    ITEM_TM65 = 646,
    ITEM_TM66 = 647,
    ITEM_TM67 = 648,
    ITEM_TM68 = 649,
    ITEM_TM69 = 650,
    ITEM_TM70 = 651,
    ITEM_TM71 = 652,
    ITEM_TM72 = 653,
    ITEM_TM73 = 654,
    ITEM_TM74 = 655,
    ITEM_TM75 = 656,
    ITEM_TM76 = 657,
    ITEM_TM77 = 658,
    ITEM_TM78 = 659,
    ITEM_TM79 = 660,
    ITEM_TM80 = 661,
    ITEM_TM81 = 662,
    ITEM_TM82 = 663,
    ITEM_TM83 = 664,
    ITEM_TM84 = 665,
    ITEM_TM85 = 666,
    ITEM_TM86 = 667,
    ITEM_TM87 = 668,
    ITEM_TM88 = 669,
    ITEM_TM89 = 670,
    ITEM_TM90 = 671,
    ITEM_TM91 = 672,
    ITEM_TM92 = 673,
    ITEM_TM93 = 674,
    ITEM_TM94 = 675,
    ITEM_TM95 = 676,
    ITEM_TM96 = 677,
    ITEM_TM97 = 678,
    ITEM_TM98 = 679,
    ITEM_TM99 = 680,
    ITEM_TM100 = 681,

    ITEM_HM01 = 682,
    ITEM_HM02 = 683,
    ITEM_HM03 = 684,
    ITEM_HM04 = 685,
    ITEM_HM05 = 686,
    ITEM_HM06 = 687,
    ITEM_HM07 = 688,
    ITEM_HM08 = 689,


    /* Expands to:
     *   ITEM_TM_FOCUS_PUNCH = ITEM_TM01,
     *   ...
     *   ITEM_HM_CUT = ITM_HM01,
     *   ... */
    /*#define ENUM_TM(n, id) CAT(ITEM_TM_, id) = CAT(ITEM_TM, n),
    #define ENUM_HM(n, id) CAT(ITEM_HM_, id) = CAT(ITEM_HM, n),
    #define TO_TMHM_NUMS(a, ...) (__VA_ARGS__)
    RECURSIVELY(R_ZIP(ENUM_TM, TO_TMHM_NUMS NUMBERS_256, (FOREACH_TM(APPEND_COMMA))))
    RECURSIVELY(R_ZIP(ENUM_HM, TO_TMHM_NUMS NUMBERS_256, (FOREACH_HM(APPEND_COMMA))))
    #undef ENUM_TM
    #undef ENUM_HM
    #undef TO_TMHM_NUMS*/

    // Charms
    ITEM_OVAL_CHARM = 690,
    ITEM_SHINY_CHARM = 691,
    ITEM_CATCHING_CHARM = 692,
    ITEM_EXP_CHARM = 693,

    // Form-changing Key Items
    ITEM_ROTOM_CATALOG = 694,
    ITEM_GRACIDEA = 695,
    ITEM_REVEAL_GLASS = 696,
    ITEM_DNA_SPLICERS = 697,
    ITEM_ZYGARDE_CUBE = 698,
    ITEM_PRISON_BOTTLE = 699,
    ITEM_N_SOLARIZER = 700,
    ITEM_N_LUNARIZER = 701,
    ITEM_REINS_OF_UNITY = 702,

    // Battle Mechanic Key Items
    ITEM_MEGA_RING = 703,
    ITEM_Z_POWER_RING = 704,
    ITEM_DYNAMAX_BAND = 705,

    // Misc. Key Items
    ITEM_BICYCLE = 706,
    ITEM_MACH_BIKE = 707,
    ITEM_ACRO_BIKE = 708,
    ITEM_OLD_ROD = 709,
    ITEM_GOOD_ROD = 710,
    ITEM_SUPER_ROD = 711,
    ITEM_DOWSING_MACHINE = 712,
    ITEM_ITEMFINDER = ITEM_DOWSING_MACHINE, // Pre-Gen IV name
    ITEM_DOWSING_MCHN = ITEM_DOWSING_MACHINE, // Gen IV-V name
    ITEM_TOWN_MAP = 713,
    ITEM_VS_SEEKER = 714,
    ITEM_TM_CASE = 715,
    ITEM_BERRY_POUCH = 716,
    ITEM_POKEMON_BOX_LINK = 717,
    ITEM_POKEMON_BOX = ITEM_POKEMON_BOX_LINK, // Pre-Gen VIII name
    ITEM_COIN_CASE = 718,
    ITEM_POWDER_JAR = 719,
    ITEM_WAILMER_PAIL = 720,
    ITEM_POKE_RADAR = 721,
    ITEM_POKEBLOCK_CASE = 722,
    ITEM_SOOT_SACK = 723,
    ITEM_POKE_FLUTE = 724,
    ITEM_FAME_CHECKER = 725,
    ITEM_TEACHY_TV = 726,

    // Story Key Items
    ITEM_SS_TICKET = 727,
    ITEM_EON_TICKET = 728,
    ITEM_MYSTIC_TICKET = 729,
    ITEM_AURORA_TICKET = 730,
    ITEM_OLD_SEA_MAP = 731,
    ITEM_LETTER = 732,
    ITEM_DEVON_PARTS = 733,
    ITEM_DEVON_GOODS = ITEM_DEVON_PARTS, // Pre-Gen VI name
    ITEM_GO_GOGGLES = 734,
    ITEM_DEVON_SCOPE = 735,
    ITEM_BASEMENT_KEY = 736,
    ITEM_SCANNER = 737,
    ITEM_STORAGE_KEY = 738,
    ITEM_KEY_TO_ROOM_1 = 739,
    ITEM_RM_1_KEY = ITEM_KEY_TO_ROOM_1, // Pre-Gen VI name
    ITEM_KEY_TO_ROOM_2 = 740,
    ITEM_RM_2_KEY = ITEM_KEY_TO_ROOM_2, // Pre-Gen VI name
    ITEM_KEY_TO_ROOM_4 = 741,
    ITEM_RM_4_KEY = ITEM_KEY_TO_ROOM_4, // Pre-Gen VI name
    ITEM_KEY_TO_ROOM_6 = 742,
    ITEM_RM_6_KEY = ITEM_KEY_TO_ROOM_6, // Pre-Gen VI name
    ITEM_METEORITE = 743,
    ITEM_MAGMA_EMBLEM = 744,
    ITEM_CONTEST_PASS = 745,
    ITEM_PARCEL = 746,
    ITEM_OAKS_PARCEL = ITEM_PARCEL, // Pre-Gen IV name
    ITEM_SECRET_KEY = 747,
    ITEM_BIKE_VOUCHER = 748,
    ITEM_GOLD_TEETH = 749,
    ITEM_CARD_KEY = 750,
    ITEM_LIFT_KEY = 751,
    ITEM_SILPH_SCOPE = 752,
    ITEM_TRI_PASS = 753,
    ITEM_RAINBOW_PASS = 754,
    ITEM_TEA = 755,
    ITEM_RUBY = 756,
    ITEM_SAPPHIRE = 757,

    // GEN IX ITEMS
    ITEM_ABILITY_SHIELD = 758,
    ITEM_CLEAR_AMULET = 759,
    ITEM_PUNCHING_GLOVE = 760,
    ITEM_COVERT_CLOAK = 761,
    ITEM_LOADED_DICE = 762,
    ITEM_AUSPICIOUS_ARMOR = 763,
    ITEM_BOOSTER_ENERGY = 764,
    ITEM_BIG_BAMBOO_SHOOT = 765,
    ITEM_GIMMIGHOUL_COIN = 766,
    ITEM_LEADERS_CREST = 767,
    ITEM_MALICIOUS_ARMOR = 768,
    ITEM_MIRROR_HERB = 769,
    ITEM_SCROLL_OF_DARKNESS = 770,
    ITEM_SCROLL_OF_WATERS = 771,
    ITEM_TERA_ORB = 772,
    ITEM_TINY_BAMBOO_SHOOT = 773,

    ITEM_BUG_TERA_SHARD = 774,
    ITEM_DARK_TERA_SHARD = 775,
    ITEM_DRAGON_TERA_SHARD = 776,
    ITEM_ELECTRIC_TERA_SHARD = 777,
    ITEM_FAIRY_TERA_SHARD = 778,
    ITEM_FIGHTING_TERA_SHARD = 779,
    ITEM_FIRE_TERA_SHARD = 780,
    ITEM_FLYING_TERA_SHARD = 781,
    ITEM_GHOST_TERA_SHARD = 782,
    ITEM_GRASS_TERA_SHARD = 783,
    ITEM_GROUND_TERA_SHARD = 784,
    ITEM_ICE_TERA_SHARD = 785,
    ITEM_NORMAL_TERA_SHARD = 786,
    ITEM_POISON_TERA_SHARD = 787,
    ITEM_PSYCHIC_TERA_SHARD = 788,
    ITEM_ROCK_TERA_SHARD = 789,
    ITEM_STEEL_TERA_SHARD = 790,
    ITEM_WATER_TERA_SHARD = 791,

    ITEM_ADAMANT_CRYSTAL = 792,
    ITEM_GRISEOUS_CORE = 793,
    ITEM_LUSTROUS_GLOBE = 794,

    ITEM_BLACK_AUGURITE = 795,
    ITEM_LINKING_CORD = 796,
    ITEM_PEAT_BLOCK = 797,
    ITEM_BERSERK_GENE = 798,

    ITEM_FAIRY_FEATHER = 799,
    ITEM_SYRUPY_APPLE = 800,
    ITEM_UNREMARKABLE_TEACUP = 801,
    ITEM_MASTERPIECE_TEACUP = 802,
    ITEM_CORNERSTONE_MASK = 803,
    ITEM_WELLSPRING_MASK = 804,
    ITEM_HEARTHFLAME_MASK = 805,
    ITEM_HEALTH_MOCHI = 806,
    ITEM_MUSCLE_MOCHI = 807,
    ITEM_RESIST_MOCHI = 808,
    ITEM_GENIUS_MOCHI = 809,
    ITEM_CLEVER_MOCHI = 810,
    ITEM_SWIFT_MOCHI = 811,
    ITEM_FRESH_START_MOCHI = 812,
    ITEM_GLIMMERING_CHARM = 813,
    ITEM_METAL_ALLOY = 814,
    ITEM_STELLAR_TERA_SHARD = 815,

    ITEM_JUBILIFE_MUFFIN = 816,
    ITEM_REMEDY = 817,
    ITEM_FINE_REMEDY = 818,
    ITEM_SUPERB_REMEDY = 819,
    ITEM_AUX_EVASION = 820,
    ITEM_AUX_GUARD = 821,
    ITEM_AUX_POWER = 822,
    ITEM_AUX_POWERGUARD = 823,
    ITEM_CHOICE_DUMPLING = 824,
    ITEM_SWAP_SNACK = 825,
    ITEM_TWICE_SPICED_RADISH = 826,
    ITEM_POKESHI_DOLL = 827,

    ITEM_STRANGE_BALL = 828,

    // Legends Z-A Mega Stones
    ITEM_CLEFABLITE = 829,
    ITEM_VICTREEBELITE = 830,
    ITEM_STARMINITE = 831,
    ITEM_DRAGONINITE = 832,
    ITEM_MEGANIUMITE = 833,
    ITEM_FERALIGITE = 834,
    ITEM_SKARMORITE = 835,
    ITEM_FROSLASSITE = 836,
    ITEM_EMBOARITE = 837,
    ITEM_EXCADRITE = 838,
    ITEM_SCOLIPITE = 839,
    ITEM_SCRAFTINITE = 840,
    ITEM_EELEKTROSSITE = 841,
    ITEM_CHANDELURITE = 842,
    ITEM_CHESNAUGHTITE = 843,
    ITEM_DELPHOXITE = 844,
    ITEM_GRENINJITE = 845,
    ITEM_PYROARITE = 846,
    ITEM_FLOETTITE = 847,
    ITEM_MALAMARITE = 848,
    ITEM_BARBARACITE = 849,
    ITEM_DRAGALGITE = 850,
    ITEM_HAWLUCHANITE = 851,
    ITEM_ZYGARDITE = 852,
    ITEM_DRAMPANITE = 853,
    ITEM_FALINKSITE = 854,

    // Legends Z-A: Mega Dimension DLC Mega Stones
    ITEM_HEATRANITE = 855,
    ITEM_DARKRANITE = 856,
    ITEM_ZERAORITE = 857,
    ITEM_RAICHUNITE_X = 858,
    ITEM_RAICHUNITE_Y = 859,
    ITEM_CHIMECHITE = 860,
    ITEM_ABSOLITE_Z = 861,
    ITEM_STARAPTITE = 862,
    ITEM_GARCHOMPITE_Z = 863,
    ITEM_LUCARIONITE_Z = 864,
    ITEM_GOLURKITE = 865,
    ITEM_MEOWSTICITE = 866,
    ITEM_CRABOMINITE = 867,
    ITEM_GOLISOPITE = 868,
    ITEM_MAGEARNITE = 869,
    ITEM_SCOVILLAINITE = 870,
    ITEM_BAXCALIBRITE = 871,
    ITEM_TATSUGIRINITE = 872,
    ITEM_GLIMMORANITE = 873,

    //Custom items + tm expansion
    ITEM_EXP_NULL,
    ITEM_EVIOLITE_FAIL,


    ITEMS_COUNT,
    ITEM_FIELD_ARROW = ITEMS_COUNT,
};

#define FIRST_BERRY_INDEX ITEM_CHERI_BERRY
#define LAST_BERRY_INDEX ITEM_ENIGMA_BERRY
#define ITEM_TO_BERRY(itemId)(((itemId - FIRST_BERRY_INDEX) + 1))

//#define NUM_TECHNICAL_MACHINES 161 //change to 120 later  / or more plan to add on to tms I think for ease spreading certain moves
//#define NUM_HIDDEN_MACHINES     9

//copy from emerald for replacing the numerical values in type field in items.json
// Item type IDs (used to determine the exit callback)
//#define ITEM_USE_MAIL           0
#define ITEM_USE_PARTY_MENU       1
#define ITEM_USE_FIELD            2
#define ITEM_USE_PBLOCK_CASE      3
#define ITEM_USE_BAG_MENU         4 // No exit callback, stays in bag menu / firered seem to use a nonconstant value, but its used with switch cases with fallthrough //I may have confused that for wrong type, the itemeffect type?
#define ITEM_USE_PARTY_MENU_MOVES 5 //so I believe the overall effect should be identical?  mostly seen in pokeball variants

// Secondary IDs for rods
#define OLD_ROD   0
#define GOOD_ROD  1
#define SUPER_ROD 2

// changing this doesn't actually do anything
// outside of the debug menu
#define MAX_BAG_ITEM_CAPACITY  999
#define MAX_PC_ITEM_CAPACITY   999
#define MAX_BERRY_CAPACITY     999

// Check if the item is one that can be used on a Pokemon.
//ok seems to be slightly different than what I thought, it doesn't decided if an item has use menu option
//that's sContextMenuItems_Field, thsi instead is used in getitem effect type
//and pokemonuseitemeffects & pokemonitemusenoeffect
//ok what those do is decide if an item gets used i.e if it triggers its effect
//pokemonitemusenoeffect tells under what condition using an item will trigger
//"it wont have an effect" text
#define IS_POKEMON_ITEM(item) ((item) > ITEM_PREMIER_BALL && (item) <= ITEM_DRAGON_SCALE)
#define IS_POKEMON_ITEM2(item) ((item) > ITEM_MEGA_BRACELET && (item) < ITEM_SEA_INCENSE)
//BECAUSE of this need to add mega stones in somewhere before to cutoff.
// or copy function for define and create a new range, for IS_POKEMON_ITEM2
//that way I can just add on to end. but before N_A
//speaking of why is it even using a range?  all items that you can't use
//have fieldusefunc oakstopsyou, should just use that as the check shouldn't I?
//if fielduseFunc = oakstopsyou it can't be used
//yup that did it, replaced ranged for a check for oakstopsyou or null
#endif  // GUARD_CONSTANTS_ITEMS_H