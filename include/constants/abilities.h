#ifndef GUARD_CONSTANTS_ABILITIES_H
#define GUARD_CONSTANTS_ABILITIES_H

 enum __attribute__((packed)) Ability
{
 ABILITY_NONE,
 ABILITY_STENCH,
 ABILITY_DRIZZLE,
 ABILITY_SPEED_BOOST,
 ABILITY_BATTLE_ARMOR,
 ABILITY_STURDY,
 ABILITY_DAMP,      //reduce fire damage, also blocks aftermath
 ABILITY_LIMBER,
 ABILITY_SAND_VEIL,
 ABILITY_STATIC,
 ABILITY_VOLT_ABSORB,
 ABILITY_WATER_ABSORB,
 ABILITY_OBLIVIOUS,
 ABILITY_CLOUD_NINE,
 ABILITY_COMPOUND_EYES,
 ABILITY_INSOMNIA,
 ABILITY_COLOR_CHANGE,
 ABILITY_IMMUNITY,
 ABILITY_FLASH_FIRE,
 ABILITY_SHIELD_DUST,
 ABILITY_OWN_TEMPO,
 ABILITY_SUCTION_CUPS,
 ABILITY_INTIMIDATE,
 ABILITY_SHADOW_TAG,
 ABILITY_ROUGH_SKIN,
 ABILITY_WONDER_GUARD,
 ABILITY_FEMME_FATALE, //since removing can replace with something else idk what though possibly anercomps random high roller ability or perhaps a community poll
 ABILITY_EFFECT_SPORE,  //ABILITY_FEMME_FATALE  replacement for levitate  //think will also give to jinx as well
 ABILITY_SYNCHRONIZE,
 ABILITY_CLEAR_BODY,
 ABILITY_NATURAL_CURE,
 ABILITY_LIGHTNING_ROD,
 ABILITY_SERENE_GRACE,
 ABILITY_SWIFT_SWIM,
 ABILITY_CHLOROPHYLL,
 ABILITY_ILLUMINATE,
 ABILITY_TRACE,
 ABILITY_HUGE_POWER, //given mostly bunny mon as japanese "pun" related to bunnies or moon goddess
 ABILITY_POISON_POINT,
 ABILITY_INNER_FOCUS,
 ABILITY_MAGMA_ARMOR,
 ABILITY_WATER_VEIL,
 ABILITY_MAGNET_PULL,
 ABILITY_SOUNDPROOF,
 ABILITY_RAIN_DISH,
 ABILITY_SAND_STREAM,
 ABILITY_PRESSURE,
 ABILITY_THICK_FAT,
 ABILITY_EARLY_BIRD,
 ABILITY_FLAME_BODY,
 ABILITY_RUN_AWAY,
 ABILITY_KEEN_EYE,
 ABILITY_HYPER_CUTTER,
 ABILITY_PICKUP,
 ABILITY_TRUANT,
 ABILITY_HUSTLE,
 ABILITY_CUTE_CHARM,
 ABILITY_PLUS,
 ABILITY_MINUS,
 ABILITY_FORECAST,
 ABILITY_STICKY_HOLD,
 ABILITY_SHED_SKIN,
 ABILITY_GUTS,
 ABILITY_MARVEL_SCALE,
 ABILITY_LIQUID_OOZE,
 ABILITY_OVERGROW,
 ABILITY_BLAZE,
 ABILITY_TORRENT,
 ABILITY_SWARM,
 ABILITY_ROCK_HEAD,
 ABILITY_DROUGHT,
 ABILITY_ARENA_TRAP,
 ABILITY_VITAL_SPIRIT,
 ABILITY_WHITE_SMOKE,
 ABILITY_PURE_POWER,  //nother pun I believe japanese refers to yoga, and is separate ability since other is for rabbits so give pure power over huge power if decide to use boost
 ABILITY_SHELL_ARMOR,
 ABILITY_CACOPHONY, //used made new effect - default effect equal to soundproof
 ABILITY_AIR_LOCK,

 ABILITIES_COUNT_GEN3,

// Gen_4
 ABILITY_TANGLED_FEET = ABILITIES_COUNT_GEN3,
 ABILITY_MOTOR_DRIVE,
 ABILITY_RIVALRY,
 ABILITY_STEADFAST,
 ABILITY_SNOW_CLOAK,
 ABILITY_GLUTTONY,
 ABILITY_ANGER_POINT,
 ABILITY_UNBURDEN,
 ABILITY_HEATPROOF,
 ABILITY_SIMPLE,
 ABILITY_DRY_SKIN,
 ABILITY_DOWNLOAD,
 ABILITY_IRON_FIST,
 ABILITY_POISON_HEAL,
 ABILITY_ADAPTABILITY,
 ABILITY_SKILL_LINK,
 ABILITY_HYDRATION,    //plan buff to include any negative status, so yawn think attraction taunt torment and also destiny bond  perish song? nah too much
 ABILITY_SOLAR_POWER,
 ABILITY_QUICK_FEET,
 ABILITY_NORMALIZE, //gets power boost + stab, but always neutral dmg, have to give to weak mon, is pretty much huge power
 ABILITY_SNIPER,
 ABILITY_MAGIC_GUARD,
 ABILITY_NO_GUARD,
 ABILITY_STALL,	//made specifically and only for sableye, doesnt synergize with trick room potentially worst abilityin the game... vsonic  -fixed
 ABILITY_TECHNICIAN,
 ABILITY_LEAF_GUARD,
 ABILITY_KLUTZ,
 ABILITY_MOLD_BREAKER, //this is actually much better than I thought, hits wonderguard ignores things that affect move dmg or absorb abilities etc.
 ABILITY_SUPER_LUCK,
 ABILITY_AFTERMATH, //do something more with this, maybe give a switch out effect and then strengthen faint effect?,/5,/6 or like a weaker counter, takes portion of movedmg??
 ABILITY_ANTICIPATION, //oh aftermath already does _2/5 enemy max health
 ABILITY_FOREWARN,
 ABILITY_UNAWARE,
 ABILITY_TINTED_LENS,
 ABILITY_FILTER,
 ABILITY_SLOW_START,
 ABILITY_SCRAPPY,
 ABILITY_STORM_DRAIN,
 ABILITY_ICE_BODY,
 ABILITY_SOLID_ROCK,
 ABILITY_SNOW_WARNING,
 ABILITY_HONEY_GATHER, //add woot change idea that holding honey will act like leftovers
 ABILITY_FRISK,
 ABILITY_RECKLESS,
 ABILITY_MULTITYPE,
 ABILITY_FLOWER_GIFT,
 ABILITY_BAD_DREAMS,

 ABILITIES_COUNT_GEN4,

// Gen_5
 ABILITY_PICKPOCKET = ABILITIES_COUNT_GEN4,
 ABILITY_SHEER_FORCE,
 ABILITY_CONTRARY,
 ABILITY_UNNERVE, //bad in game buffing with og pressure effect of additional pp useage, leans into unnerving aura idea
 ABILITY_DEFIANT,
 ABILITY_DEFEATIST,
 ABILITY_CURSED_BODY,
 ABILITY_HEALER,
 ABILITY_FRIEND_GUARD,
 ABILITY_WEAK_ARMOR,
 ABILITY_HEAVY_METAL, //potentially boost power of steel type moves?
 ABILITY_LIGHT_METAL, //potentially boost priority of steel type moves
 ABILITY_MULTISCALE,
 ABILITY_TOXIC_BOOST,
 ABILITY_FLARE_BOOST,
 ABILITY_HARVEST,
 ABILITY_TELEPATHY,
 ABILITY_MOODY,
 ABILITY_OVERCOAT,
 ABILITY_POISON_TOUCH,
 ABILITY_REGENERATOR,
 ABILITY_BIG_PECKS,
 ABILITY_SAND_RUSH,
 ABILITY_WONDER_SKIN,
 ABILITY_ANALYTIC,
 ABILITY_ILLUSION,
 ABILITY_IMPOSTER, //remeber check todo list for plan for this, setup extra case effect for wilds i.e only mon in party effect
 ABILITY_INFILTRATOR,
 ABILITY_MUMMY,
 ABILITY_MOXIE,
 ABILITY_JUSTIFIED,
 ABILITY_RATTLED,
 ABILITY_MAGIC_BOUNCE,
 ABILITY_SAP_SIPPER,
 ABILITY_PRANKSTER,
 ABILITY_SAND_FORCE,
 ABILITY_IRON_BARBS,
 ABILITY_ZEN_MODE,
 ABILITY_VICTORY_STAR,
 ABILITY_TURBOBLAZE,
 ABILITY_TERAVOLT,

 ABILITIES_COUNT_GEN5,

// Gen_6
 ABILITY_AROMA_VEIL = ABILITIES_COUNT_GEN5,
 ABILITY_FLOWER_VEIL,
 ABILITY_CHEEK_POUCH,
 ABILITY_PROTEAN,
 ABILITY_FUR_COAT,
 ABILITY_MAGICIAN,
 ABILITY_BULLETPROOF,
 ABILITY_COMPETITIVE,
 ABILITY_STRONG_JAW,
 ABILITY_REFRIGERATE,
 ABILITY_SWEET_VEIL,
 ABILITY_STANCE_CHANGE,
 ABILITY_GALE_WINGS,
 ABILITY_MEGA_LAUNCHER,
 ABILITY_GRASS_PELT,
 ABILITY_SYMBIOSIS,
 ABILITY_TOUGH_CLAWS,
 ABILITY_PIXILATE,
 ABILITY_GOOEY,
 ABILITY_AERILATE,
 ABILITY_PARENTAL_BOND,
 ABILITY_DARK_AURA,
 ABILITY_FAIRY_AURA,
 ABILITY_AURA_BREAK,
 ABILITY_PRIMORDIAL_SEA,
 ABILITY_DESOLATE_LAND,
 ABILITY_DELTA_STREAM,

 ABILITIES_COUNT_GEN6,

// Gen_7
 ABILITY_STAMINA = ABILITIES_COUNT_GEN6,
 ABILITY_WIMP_OUT,
 ABILITY_EMERGENCY_EXIT,
 ABILITY_WATER_COMPACTION,
 ABILITY_MERCILESS,
 ABILITY_SHIELDS_DOWN,
 ABILITY_STAKEOUT,
 ABILITY_WATER_BUBBLE,
 ABILITY_STEELWORKER,
 ABILITY_BERSERK,
 ABILITY_SLUSH_RUSH,
 ABILITY_LONG_REACH,
 ABILITY_LIQUID_VOICE,
 ABILITY_TRIAGE,
 ABILITY_GALVANIZE,
 ABILITY_SURGE_SURFER,
 ABILITY_SCHOOLING,
 ABILITY_DISGUISE,
 ABILITY_BATTLE_BOND,
 ABILITY_POWER_CONSTRUCT,
 ABILITY_CORROSION,
 ABILITY_COMATOSE,
 ABILITY_QUEENLY_MAJESTY,
 ABILITY_INNARDS_OUT,
 ABILITY_DANCER,
 ABILITY_BATTERY, //dex entry charjabug it power up vikavolt so does version of commander of tatsugiri want do just for charjabug
 ABILITY_FLUFFY,
 ABILITY_DAZZLING,
 ABILITY_SOUL_HEART,
 ABILITY_TANGLING_HAIR,
 ABILITY_RECEIVER,
 ABILITY_POWER_OF_ALCHEMY,
 ABILITY_BEAST_BOOST,
 ABILITY_RKS_SYSTEM,
 ABILITY_ELECTRIC_SURGE,
 ABILITY_PSYCHIC_SURGE,
 ABILITY_MISTY_SURGE,
 ABILITY_GRASSY_SURGE,
 ABILITY_FULL_METAL_BODY,
 ABILITY_SHADOW_SHIELD,
 ABILITY_PRISM_ARMOR,
 ABILITY_NEUROFORCE,

 ABILITIES_COUNT_GEN7,

// Gen_8
 ABILITY_INTREPID_SWORD = ABILITIES_COUNT_GEN7,
 ABILITY_DAUNTLESS_SHIELD,
 ABILITY_LIBERO,
 ABILITY_BALL_FETCH,
 ABILITY_COTTON_DOWN,
 ABILITY_PROPELLER_TAIL,
 ABILITY_MIRROR_ARMOR,
 ABILITY_GULP_MISSILE,
 ABILITY_STALWART,
 ABILITY_STEAM_ENGINE,
 ABILITY_PUNK_ROCK,
 ABILITY_SAND_SPIT,
 ABILITY_ICE_SCALES,
 ABILITY_RIPEN,
 ABILITY_ICE_FACE,
 ABILITY_POWER_SPOT,
 ABILITY_MIMICRY,
 ABILITY_SCREEN_CLEANER,
 ABILITY_STEELY_SPIRIT,
 ABILITY_PERISH_BODY,
 ABILITY_WANDERING_SPIRIT,
 ABILITY_GORILLA_TACTICS,
 ABILITY_NEUTRALIZING_GAS,
 ABILITY_PASTEL_VEIL,
 ABILITY_HUNGER_SWITCH,
 ABILITY_QUICK_DRAW,
 ABILITY_UNSEEN_FIST,
 ABILITY_CURIOUS_MEDICINE,
 ABILITY_TRANSISTOR,
 ABILITY_DRAGONS_MAW,
 ABILITY_CHILLING_NEIGH,
 ABILITY_GRIM_NEIGH,
 ABILITY_AS_ONE_ICE_RIDER,
 ABILITY_AS_ONE_SHADOW_RIDER,

 ABILITIES_COUNT_GEN8,

// Gen_9
 ABILITY_LINGERING_AROMA = ABILITIES_COUNT_GEN8,
 ABILITY_SEED_SOWER,
 ABILITY_THERMAL_EXCHANGE,
 ABILITY_ANGER_SHELL,
 ABILITY_PURIFYING_SALT,
 ABILITY_WELL_BAKED_BODY,
 ABILITY_WIND_RIDER,
 ABILITY_GUARD_DOG,
 ABILITY_ROCKY_PAYLOAD,
 ABILITY_WIND_POWER,
 ABILITY_ZERO_TO_HERO,
 ABILITY_COMMANDER,
 ABILITY_ELECTROMORPHOSIS,
 ABILITY_PROTOSYNTHESIS,
 ABILITY_QUARK_DRIVE,
 ABILITY_GOOD_AS_GOLD,
 ABILITY_VESSEL_OF_RUIN,
 ABILITY_SWORD_OF_RUIN,
 ABILITY_TABLETS_OF_RUIN,
 ABILITY_BEADS_OF_RUIN,
 ABILITY_ORICHALCUM_PULSE,
 ABILITY_HADRON_ENGINE,
 ABILITY_OPPORTUNIST,
 ABILITY_CUD_CHEW,
 ABILITY_SHARPNESS,
 ABILITY_SUPREME_OVERLORD,
 ABILITY_COSTAR,
 ABILITY_TOXIC_DEBRIS,
 ABILITY_ARMOR_TAIL,
 ABILITY_EARTH_EATER,
 ABILITY_MYCELIUM_MIGHT,
 ABILITY_HOSPITALITY,
 ABILITY_MINDS_EYE,
 ABILITY_EMBODY_ASPECT_TEAL_MASK,
 ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK,
 ABILITY_EMBODY_ASPECT_WELLSPRING_MASK,
 ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK,
 ABILITY_TOXIC_CHAIN,
 ABILITY_SUPERSWEET_SYRUP,
 ABILITY_TERA_SHIFT,
 ABILITY_TERA_SHELL,
 ABILITY_TERAFORM_ZERO,   //alter make also break all other terra and long as on field no one else can use terra does default cloud, w terrain clear idk can't tell if it removes them or not maybe it does?
 ABILITY_POISON_PUPPETEER,

 ABILITIES_COUNT_GEN9,

//CUSTOM ABILITIES
 ABILITY_DISPIRIT_GUARD = ABILITIES_COUNT_GEN9,
 ABILITY_NUISANCE,		//can't remember original plan for this, but I effectively made better prankster..
 ABILITY_MULTI_TASK,
 ABILITY_SIROCCO,
 ABILITY_HI_PRESSURE,
 ABILITY_CUPIDS_ARROW,
 ABILITY_BATTLE_MATRON,
 ABILITY_LIQUID_SOUL,
 ABILITY_OCEAN_MEMORY,
 ABILITY_OVERCHARGE,
 ABILITY_PHOTOSYNTHESIZE,
 ABILITY_GLACIAL_ICE,	//fire immunity + ice body effect	REGICE ability
 ABILITY_LAVA_FISSURE, // pending heatran ability
 ABILITY_TOADSTOOL_NYMPH, // pending Shiinotic ability
 ABILTY_UNKNOWN_POWER,	//unown specific ability similar to plus minus but if partner is unown
 ABILITY_PURIFYING_AURA, //Suicune ability  mix of healer & shedskin but gauranteed
 ABILITY_SQUALL,	//temp versions of drizzle/drought
 ABILITY_SUN_DISK,
 ABILITY_TOUGH_SPINES,	//rough skin for grass types spines can also be bone/spikes
 ABILITY_EROSION,	//regirock ability, rock absorb also absorbs stealth rocks on switchin
 ABILITY_LIQUID_METAL,	//Registeel exclusive 
 ABILITY_MUSCLE_MAGIC,
 ABILITY_TIGER_CUB,	//tinted lens copy
 ABILITY_TIGER_MOM,	//alt version intimidate, drops defense instead of atk, defense drop may be too strong, instead consider speed drop, idea still works, tiger mom pressures you so you cant make a decision i.e lowering your speed
 ABILITY_DARK_DEAL,   //
 ABILITY_CORRUPTION,   //anti heal switch in ability,  users corrupted influence spreads decay, preventing foe from healing, giving to guzzlord etc. make side based effect
 ABILITY_BANDIT_KING,   //embargo on switch in
 ABILITY_AVIATOR,   //Usually flying type, an experienced flyer who's speed can't be lowered  flying version of run away //ok change what will do is make class of ability that gives all benefits of type based bonus, aviator will give all benefits flying types get
 ABILITY_USURPER,	//NEW giratina base ability
 ABILITY_INVERSE_WORLD,	//NEW giratina origin ability
 ABILITY_SONAR,	//sound move boost for bat pokemon,  double move damage, mostly to make sonic boom do dragon breath damage, and be strong early HA only
 ABILITY_ECOSYSTEM,		//MEGA torterra excluive
 ABILITY_ABSOLUTE_ZERO,		//kyurem excluive
 ABILITY_FEATHER_JACKET,	//hisuian decidueye inspired by dex entry and smisonian arcticle cold climate birds have "They had fluffier jackets" to insulate them from cold
 ABILITY_POISONED_LEGACY, // poison pinch ability, for poipoile as its technically a starter,  inspired by marriagetoxin manga, boost poison in a pinch and if poison target will be bad poison consider set to turn, so it does full dmg,st turn
 ABILITY_JEWEL_METABOLISM, //can't think of a name right now, this is just a sableye rock absorb based on dex entry, hmm maybe do more boost damage to rock types? ok, instead of raising hp, boosts def as eaten rocks form more crystals ok i like that
 ABILITY_INVERSION, //  - for ditto  - still to do - mostly works now 
 ABILITY_WETIKO, // for my version crabominable mix of refrigerate & regenerator
 ABILITY_EMPATH, // upgraded synchronize, copies stat change too, not for umbreon psychic only
 ABILITY_EMPATHIC_CURSE, //ability for Mespirit - synchronize with dmg reflect
 ABILITY_INTHRALL, //ability for Uxie - anticipation except it seals the move so it can't be used/selected  //magician conditions, anticipation function logic
 ABILITY_IRON_WILL, //abillity for Azelf - mix of pressure where it can paralyze the attacker, but lower odds, as thye also have to break will pressure odds that lower dmg done
 ABILITY_LIVEWIRE, //for rotom base, weaker version of transistor
 ABILITY_GALEFORCE,
 ABILITY_LETHAL_LEGS, //hitmonlee ability boost kicking moves
 ABILITY_TOXUNGUE,    //Likitung line signature paralytic poison touch
 ABILITY_OMNIPOTENT_AIDE,//for Fraeyjta, can use healing moves for itself, but transfers any heal it would receive to battle partner (if heal target mon with this ability change target to battle partner, otherwise fail)
                                    //if this mon uses a healing move its priority gets increased long as it has a living battle partner, for balanve remove priority effect if status,,  logic is ABILITY_TRIAGE 
                                    //heal priority setup, target swap is not working yet - look at lightning rod?
 ABILITY_FLUORESCENCE,     
 ABILITY_SPECTRE,  //latios & latias ability raise evasiveness on switch in
 ABILITY_AURA_OF_LIGHT,//CRESELIA ABILITY prevent sleep for self and allies, plus reduce dark damage on side - done setup
 ABILITY_DESPAIR, //nother idea true anti heal, gbattlemovedamage *-1  if attempts to heal re-reverses damage formula, so it causes you to take damage instead. 
                                    //give to darkrai //use stringutil to change strings ids like intimidate angerpoint etc. //think put in bigroot function, heal commands and sleep end turn
 ABILITY_RISING_PHOENIX, //MOLTRES ability,  slight DxD reference
 ABILITY_DREAD_WING, //aka burnout GALARIAN MOLTRES ABILITY, tweaking status to fit, set similar to unaware, when attacknig lower enemy def/sp def when target lower foe attack
                            //should be equivalent to amount of, stat stage drop
 ABILITY_PLAGUE_WINGS, //butterfree ability, effect spore no contect, work like powder move, grass immune
 ABILITY_PHANTOM_TOUCH,  //cubone line, contact only scrappy
 ABILITY_APOTHEOSCENT,  //immune to affect of being confused like bugs, and prevent acc drop  for mon w extra senses, fightnig psychic ghost insinct etc.
                                    //planned for parasect if made grass ghost, so still keep bug type confuse exclusion
 ABILITY_WEIGHTED_GI,     //dbz themed in a pinch fighting abiility, boost speed throwing off weights in a pinch boost,.5x or,x, give to bulky fighting types and mienshoo line (based on dex entry)
 ABILITY_VOLT_DASH,       //thunderous therian ability volt absorb + speed boost
 ABILITY_IMMUTABLE_WIND,   //Tornadus therian ability, neutralizing gas + wonder skin

 ABILITY_EVERGREEN,   //celebi ability
 ABILITY_SHAMAN_CURE, //shaman base ability
 ABILITY_UNCHAINED_MELODY,  //NORMAL MOVES into sound moves
 ABILITY_ENAMEL,
 ABILITY_BONE_ARMOR,  //abilities for faedentin and bone fairy evo, //cuts fire damage, bone armor also has force switch prevention, think also recoil?
 ABILITY_STORM_BREAK, //old cloud nine effect, by for flying types, pretty much delta stream but just to break weather have to find birds I have space to give this to
 ABILITY_SPACE_CONTROL, //hmm domain expansion? nah too long, palkia ability uses portals to make moves,% accurate and is immune to ice because adapted to void of space
 ABILITY_COLD_EMBRACE,    //froslass ability 
 ABILITY_TOXIC_WING,
 ABILITY_TIME_CONTROL, //new dialga ability
 ABILITY_TORCHSOUL, //fire affinity ability, embroar
 ABILITY_GRUNGE,  //poison affinity / can't be poisoned should also give poison boost? or should I go more creative give all moves chance to poison?
 ABILITY_SWIFT_JUSTICE, //virizion new ability boost damage if move first
 ABILITY_TOOLS_OF_THE_TRADE, //FATE reference //new ability for spidops combine insomnia stakeout analytic and guts/defiant but weaker effects for all if only sleeps one turn could boost defense and get heal? if heal doesn't work just block sleep altogether
 ABILITY_TROJAN_SWORD,  //idea for buff iron leaves, block intimidate and gives sharpness
 ABILITY_HEAT_TRANCE, //SCOVILLAIN capsakid buff burn healing since is fire type still not great as requires holding flame orb guess can fing it if I don't need it?
 ABILITY_DESERT_DWELLER, //new cacturne line ability heat proof + thick fat
 ABILITY_FAIRY_MIST, //for iron valiant combine misty surge w pixilate
 ABILITY_COMPASS, //no guard clone for onix nosepass binacle as designed around compasses
 ABILITY_HANDS_OF_FATE, //purifying salt clone for binacle as designed around hamsa protective ward against the evil eye, think also give specific immunity to shadow tag mean look and decidueye move
 ABILITY_DUST_DEVIL, //combine sandstream & wind rider for new bug psuedo
 ABILITY_PLASMA_OVERDRIVE, //custom moldbreaker lightningrod flash fire for zekrom/reshiram fusion
 ABILITY_CREATION_ENGINE, //custom ability for original dragon //power over fire electricity and ice  //consider rename to creation engine as zek resh based aruond turbine
 ABILITY_DARK_CORONA, //initial intended ability for larvalking tough spines + poison point
 ABILITY_LUNAR_SOLSTICE, //moon version of sundisk
 ABILITY_LUNAR_POWER, //moon version of solar power //think may add on can't be damaged by moon based attacks? like balistic
 ABILITY_NEW_MOON, //heal by moonlight think also heal from taking moon based attacks?
 ABILITY_TOXIC_DELUGE,  //acid rain ability
 ABILITY_RESOLUTE,  //planned ability for lokix to enter showdown mode same idea as ash greninja
 ABILITY_PIERCING_HORN,
 ABILITY_X_SIGHT, //luxray new signature ability frisk plus bypass acc check when above half hp, as dex entry says its xray vision requires a lot of energy
 ABILITY_PRECISE_STRIKE, //fighting version of sniper, for storm throw buff
 ABILITY_BRAVERY,  //keldeo version justified
 ABILITY_FUGUE,   //wow this being #404 is so appropriate lmao, malamar new signature ability confusion & sleep always max turns
 ABILITY_CRYOSTORM, //for separating hail ability from snow ability
 ABILITY_SECRET_ARTS, //shadow mega greninja ability part no guard part unseen fist to break protect and guard
 ABILITIES_COUNT //   ability count is last ability number +, since we have to count ability,
};

#endif  // GUARD_CONSTANTS_ABILITIES_H
