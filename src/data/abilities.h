#include "config.h"

//checked in fire red limit is 40 chars per line, changing description length to 80/    changed to 82 max
//based on suction cups I kinda have more space?  so more like 41 per line?
//template - top line: literal effect\n bottom line: flavor text    -flipped usually put flavor text on top, effect on bottom
//if you can't cleanly do a mix of both. over the full space
//*note if ability text extends over the line i.e more than 40 chars on a line,
//even if max is below total limit causes a overflow glitch, that corrupts summary screen data

const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No special ability."),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = _("Stench"),
        .description = COMPOUND_ABILITY_STRING("Can repel wild POKéMON and trainers.\nAll battlers have a chance to flinch."),
        .aiRating = 4,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("Drizzle"),
        .description = COMPOUND_ABILITY_STRING("Summons rain in battle."),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("Speed Boost"),
        .description = COMPOUND_ABILITY_STRING("Gradually boosts SPEED."),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("Battle Armor"),
        .description = COMPOUND_ABILITY_STRING("Blocks critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },
    //suprised this only a two

    [ABILITY_STURDY] =
    {
        .name = _("Sturdy"),
        .description = COMPOUND_ABILITY_STRING("Negates 1-hit KO moves.\nResists moves that would otherwise OHKO."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = _("Damp"),
        .description = COMPOUND_ABILITY_STRING("Dampens area preventing explosions.\nAnd weakens incoming fire damage."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = _("Limber"),
        .description = COMPOUND_ABILITY_STRING("Prevents paralysis."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("Sand Veil"),
        .description = COMPOUND_ABILITY_STRING("Ups evasion in a sandstorm."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = _("Static"),
        .description = COMPOUND_ABILITY_STRING("May Paralyze on contact."),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("Volt Absorb"),
        .description = COMPOUND_ABILITY_STRING("Turns incomming electric damage into HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("Water Absorb"),
        .description = COMPOUND_ABILITY_STRING("Turns incomming water damage into HP.\nSlight HP recovery in rain and fog."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("Oblivious"),
        .description = COMPOUND_ABILITY_STRING("Prevents attraction.\nBlocks Intimidate, Taunt, and Torment."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("Cloud Nine"),
        .description = COMPOUND_ABILITY_STRING("Blocks all negative weather effects for\nthe user and most effects for the team."),
        .aiRating = 6,
        .breakable = TRUE,
    },
    //may need to make breakable
    //vsonic need to work out

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("Compound Eyes"),
        .description = COMPOUND_ABILITY_STRING("Raises accuracy."),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("Insomnia"),
        .description = COMPOUND_ABILITY_STRING("Prevents sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("Color Change"),
        .description = COMPOUND_ABILITY_STRING("Changes secondary type\nto match incomming attack."),
        .aiRating = 5,
    },
    //potentially should add mold breaker leaving off for now
    //concpet stance change isn't breakable

    [ABILITY_IMMUNITY] =
    {
        .name = _("Immunity"),
        .description = COMPOUND_ABILITY_STRING("Prevents poisoning."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("Flash Fire"),
        .description = COMPOUND_ABILITY_STRING("Draws in and powers up fire moves"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("Shield Dust"),
        .description = COMPOUND_ABILITY_STRING("Protective dust shields the Pokémon\nfrom the additional effects of moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("Own Tempo"),
        .description = COMPOUND_ABILITY_STRING("Prevents confusion.\nBlocks Intimidate, Taunt, and Torment."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("Suction Cups"),
        .description = COMPOUND_ABILITY_STRING("Firmly anchors itself, stops force switch.\nTrap move effects last longer."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("Intimidate"),
        .description = COMPOUND_ABILITY_STRING("Lowers the foe's ATTACK."),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("Shadow Tag"),
        .description = COMPOUND_ABILITY_STRING("Prevents non-ghost foes from escaping.\nAlso drops their speed."),
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("Rough Skin"),
        .description = COMPOUND_ABILITY_STRING("Hurts to make contact."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("Wonder Guard"),
        .description = COMPOUND_ABILITY_STRING("“Super effective” hits.\nIgnores most other damage for 4 turns."),
        .aiRating = 10,
        .breakable = TRUE,
        .isSingleUse = TRUE,
        .timer = WONDER_GUARD_TIMER,
    },

    [ABILITY_FEMME_FATALE] =
    {
        .name = _("Femme Fatale"),
        .description = COMPOUND_ABILITY_STRING("Immune to Infatuation and Intimidation.\nAlso blocks Flinch, Taunt, and Torment."),
        .aiRating = 6,
        .breakable = TRUE,
    },//based off oblivious but double check effect, for flags and ratings

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("Effect Spore"),
        .description = COMPOUND_ABILITY_STRING("Leaves spores on contact.\nSpores apply a variety of statuses."),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("Synchronize"),
        .description = COMPOUND_ABILITY_STRING("Passes on status problems."),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("Clear Body"),
        .description = COMPOUND_ABILITY_STRING("Prevents stat reduction."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("Natural Cure"),
        .description = COMPOUND_ABILITY_STRING("Heals status upon switching out."),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("Lightning Rod"),
        .description = COMPOUND_ABILITY_STRING("Draws in electrical moves.\nAlso raises Sp. Atk one stage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("Serene Grace"),
        .description = COMPOUND_ABILITY_STRING("Increases chance of added effects."),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("Swift Swim"),
        .description = COMPOUND_ABILITY_STRING("Raises SPEED in rain."),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("Chlorophyll"),
        .description = COMPOUND_ABILITY_STRING("Raises SPEED in sunshine."),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("Illuminate"),
        .description = COMPOUND_ABILITY_STRING("Encounter rate increases.\nRaises accuracy and enables Flash."),
        .aiRating = 0,
    },
    //my version doesn't prevent stat drop so not breakable

    [ABILITY_TRACE] =
    {
        .name = _("Trace"),
        .description = COMPOUND_ABILITY_STRING("Copies special ability."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("Huge Power"),
        .description = COMPOUND_ABILITY_STRING("Raises ATTACK double."),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("Poison Point"),
        .description = COMPOUND_ABILITY_STRING("Contact with the Pokémon\nmay poison the attacker."),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("Inner Focus"),
        .description = COMPOUND_ABILITY_STRING("Focuses intensely to prevent Flinching,\nCritical Hits, and Intimidation."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("Magma Armor"),
        .description = COMPOUND_ABILITY_STRING("Prevents freezing, burns items on contact\nboosts Sp.Def and blocks physical crits."),
        .aiRating = 3,
        .breakable = TRUE,
    },
    //how does breakable work
    //this burns items on contact 
    //and blocks physical crits
    //I think I'd want mold breaker to only
    //break through the crit protection
    //idk if it makes sense to avoid burning items
    //for example checkked flamebody and that 
    //isn't affected by moldbreaker
    //ok looked into EE, breakable makes it read 
    //as no ability, but despite being breakable
    //it also has ability checks that ignore moldbreaker
    //so certain times it reads the ability as is, 
    //allowing its effect to activate
    //so I would just need to use that version for item burn check
    //and the full check for physical crit
    //am just unsure if that is true to how it should be used
    //got it, from bulbapedia
    //(Ignorable Abilities are most Abilities that could 
    //potentially negatively affect the success, 
    //damage, or effects of a move.)
    //which is why magma armor is breakable but otherwise ignored 
    //for moldbreaker, it gets broken to allow freezing
    //since otherwise the move success would be affected
    //I can do what I want, break the crits
    //but keep the item burn up
    //as crits affect damage, but the item loss
    //doens't affect success or damage of moves used

    [ABILITY_WATER_VEIL] =
    {
        .name = _("Water Veil"),
        .description = COMPOUND_ABILITY_STRING("Prevents burns."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("Magnet Pull"),
        .description = COMPOUND_ABILITY_STRING("Traps STEEL-type POKéMON with magnetism\nAlso drops their speed."),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("Soundproof"),
        .description = COMPOUND_ABILITY_STRING("Avoids sound-based moves."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("Rain Dish"),
        .description = COMPOUND_ABILITY_STRING("Moderate HP recovery in rain."),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("Sand Stream"),
        .description = COMPOUND_ABILITY_STRING("Summons a sandstorm."),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("Pressure"),
        .description = COMPOUND_ABILITY_STRING("Raises foe's PP usage.\nMay make foe too afraid to attack well."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("Thick Fat"),
        .description = COMPOUND_ABILITY_STRING("Reduces Heat-and-cold effectiveness."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("Early Bird"),
        .description = COMPOUND_ABILITY_STRING("Awakens quickly from sleep, refreshed.\nCleanses stat drops on awaken."),
        .aiRating = 5,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("Flame Body"),
        .description = COMPOUND_ABILITY_STRING("May cause Burn on contact.\nCan't be frozen and hatches eggs faster."),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("Run Away"),
        .description = COMPOUND_ABILITY_STRING("Makes escaping easier.\nPrevents loss of speed except from traps."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    //vsonic just realized with new effect changes
    //this is breakable now, so would need to go over 
    //and reevaluate these

    [ABILITY_KEEN_EYE] =
    {
        .name = _("Keen Eye"),
        .description = COMPOUND_ABILITY_STRING("Prevents loss of accuracy. Slightly\nboosts Acc and ignores evasion changes."),
        .aiRating = 1,
        .breakable = TRUE,
    },//vsonic

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("Hyper Cutter"),
        .description = COMPOUND_ABILITY_STRING("Prevents ATTACK reduction."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = _("Pickup"),
        .description = COMPOUND_ABILITY_STRING("May pick up items."),
        .aiRating = 2,
    },

    [ABILITY_TRUANT] =
    {
        .name = _("Truant"),
        .description = COMPOUND_ABILITY_STRING("Only moves every other turn.\nBut heals while at rest."),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },//vsnoic

    [ABILITY_HUSTLE] =
    {
        .name = _("Hustle"),
        .description = COMPOUND_ABILITY_STRING("Trades a small accuracy drop for power.\n5% accuracy drop for 50% Atk boost."),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("Cute Charm"),
        .description = COMPOUND_ABILITY_STRING("May Infatuate on contact.\nAlways Infatuates when hit."),
        .aiRating = 3,
    },

    [ABILITY_PLUS] =
    {
        .name = _("Plus"),
        .description = COMPOUND_ABILITY_STRING("Boost Sp.Atk. if MINUS or Elec. on field.\nPwr up if Elec./MINUS ally is in a pinch"),
        .aiRating = 2,
    },

    [ABILITY_MINUS] =
    {
        .name = _("Minus"),
        .description = COMPOUND_ABILITY_STRING("Boost Sp.Atk. if PLUS or Elec. on field.\nPwr up when Elec./PLUS ally is in a pinch"),
        .aiRating = 2,
    },

    [ABILITY_FORECAST] =
    {
        .name = _("Forecast"),
        .description = COMPOUND_ABILITY_STRING("Predicts, the coming weather.\nWeather extenders enhance prediction."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },////since giving to non castform consider tweak a bit more, put some effects on just castform like weather drop immunity

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("Sticky Hold"),
        .description = COMPOUND_ABILITY_STRING("Prevents item theft.\nAbsorbs foe's item on contact."),
        .aiRating = 3,
        .breakable = TRUE,
    },//not like magician foes item is just lost

    [ABILITY_SHED_SKIN] =
    {
        .name = _("Shed Skin"),
        .description = COMPOUND_ABILITY_STRING("Heals the body by shedding.\nMay attempt to cure status."),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = _("Guts"),
        .description = COMPOUND_ABILITY_STRING("Ups ATTACK if suffering from status."),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("Marvel Scale"),
        .description = COMPOUND_ABILITY_STRING("Ups DEFENSE if suffering from status."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("Liquid Ooze"),
        .description = COMPOUND_ABILITY_STRING("Draining causes injury."),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("Overgrow"),
        .description = COMPOUND_ABILITY_STRING("Ups GRASS moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = _("Blaze"),
        .description = COMPOUND_ABILITY_STRING("Ups FIRE moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = _("Torrent"),
        .description = COMPOUND_ABILITY_STRING("Ups WATER moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = _("Swarm"),
        .description = COMPOUND_ABILITY_STRING("Ups BUG moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("Rock Head"),
        .description = COMPOUND_ABILITY_STRING("Prevents recoil damage.\nBoosts headbutt moves."),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("Drought"),
        .description = COMPOUND_ABILITY_STRING("Summons sunlight in battle."),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("Arena Trap"),
        .description = COMPOUND_ABILITY_STRING("Stops grounded foe from fleeing.\nAlso drops their speed. +Encounter rate"),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("Vital Spirit"),
        .description = COMPOUND_ABILITY_STRING("Prevents sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("White Smoke"),
        .description = COMPOUND_ABILITY_STRING("Prevents stat drops by foes."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("Pure Power"),
        .description = COMPOUND_ABILITY_STRING("Doubles attack stat."),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("Shell Armor"),
        .description = COMPOUND_ABILITY_STRING("Blocks critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CACOPHONY] =
    {
        .name = _("Cacophony"),
        .description = COMPOUND_ABILITY_STRING("+Snd Dmg. Boosts ally Sound-move effects\nand helps bypass screens and protects."),
        .aiRating = 1,
    }, //low rating cuz very niche activation

    [ABILITY_AIR_LOCK] =
    {
        .name = _("Air Lock"),
        .description = COMPOUND_ABILITY_STRING("Negates weather effects."),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = _("Tangled Feet"),
        .description = COMPOUND_ABILITY_STRING("Ups evasion, speed, and avoids crits\nif confused. Prevents loss of speed."),
        .aiRating = 5,
        .breakable = TRUE,
    },////drunken fist type deal /put w bug immunity so doesn't hit itself

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = _("Motor Drive"),
        .description = COMPOUND_ABILITY_STRING("Raises speed if hit by Electricity."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = _("Rivalry"),
        .description = COMPOUND_ABILITY_STRING("Powers up against same gender opponents."),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = _("Steadfast"),
        .description = COMPOUND_ABILITY_STRING("Determination raises speed on flinch\nor taking “Super effective” hits."),
        .aiRating = 2,
    },//vsonic

    [ABILITY_SNOW_CLOAK] =
    {
        .name = _("Snow Cloak"),
        .description = COMPOUND_ABILITY_STRING("Ups evasion in Hail and Snow."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = _("Gluttony"),
        .description = COMPOUND_ABILITY_STRING("Eats Berries early."),
        .aiRating = 3,
    },//vsonic

    [ABILITY_ANGER_POINT] =
    {
        .name = _("Anger Point"),
        .description = COMPOUND_ABILITY_STRING("Raises attack if hit by “Critical” hits,\n“Super effective” hits, or Intimidated."),
        .aiRating = 6,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = _("Unburden"),
        .description = COMPOUND_ABILITY_STRING("Using a hold item ups Speed."),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = _("Heatproof"),
        .description = COMPOUND_ABILITY_STRING("Lowers effectiveness of Fire and burn."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("Simple"),
        .description = COMPOUND_ABILITY_STRING("Prone to wild stat changes."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = _("Dry Skin"),
        .description = COMPOUND_ABILITY_STRING("Takes slight Dmg in Sun absorbs water.\nHeals in rain/fog, takes more Fire Dmg."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = _("Download"),
        .description = COMPOUND_ABILITY_STRING("Adjusts offensive power favorably,\nto foe's defenses."),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = _("Iron Fist"),
        .description = COMPOUND_ABILITY_STRING("Boosts Punching moves."),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = _("Poison Heal"),
        .description = COMPOUND_ABILITY_STRING("Heals if poisoned or PSN-type holds\na toxic item. Also clears toxic spikes."),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = _("Adaptability"),
        .description = COMPOUND_ABILITY_STRING("Boosts same type attacks."),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = _("Skill Link"),
        .description = COMPOUND_ABILITY_STRING("Multi-hit moves hit 5 times.\nOnly first hit gets accuracy check."),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = _("Hydration"),
        .description = COMPOUND_ABILITY_STRING("Cures status ailments and other\nnegative effects in rain."),
        .aiRating = 4,
    }, //buffs still in works

    [ABILITY_SOLAR_POWER] =
    {
        .name = _("Solar Power"),
        .description = COMPOUND_ABILITY_STRING("Powers up in sunshine. Boosting Sp. Atk.\nBut is hurt by its uncontrollable power."),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = _("Quick Feet"),
        .description = COMPOUND_ABILITY_STRING("Ups Speed if statused or Intimdated.\nPrevents loss of speed except from traps."),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = _("Normalize"),
        .description = COMPOUND_ABILITY_STRING("PKMN exudes a completely average aura.\nAll moves become True Normal."),
        .aiRating = 2,
    },

    [ABILITY_SNIPER] =
    {
        .name = _("Sniper"),
        .description = COMPOUND_ABILITY_STRING("Boosts critical hits."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = _("Magic Guard"),
        .description = COMPOUND_ABILITY_STRING("Only damaged by attacks\nand ignores indirect damage."),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = _("No Guard"),
        .description = COMPOUND_ABILITY_STRING("Can't guard but bypasses foe guard mode.\nAll attacks used by/against the user hit."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = _("Stall"),
        .description = COMPOUND_ABILITY_STRING("Damaging moves go last sans Trick Room.\nIt bides its time to greatly boost power."),
        .aiRating = 1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = _("Technician"),
        .description = COMPOUND_ABILITY_STRING("Boosts weaker moves."),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = _("Leaf Guard"),
        .description = COMPOUND_ABILITY_STRING("Prevents stat drop by hiding in leaves.\nAlso blocks status problems in sunshine."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = _("Klutz"),
        .description = COMPOUND_ABILITY_STRING("Can't use hold items, but takes less\nphysical dmg. Prevents recoil damage."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = _("Mold Breaker"),
        .description = COMPOUND_ABILITY_STRING("Moves ignore ability affects,\ninnate effects and affinities."),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = _("Super Luck"),
        .description = COMPOUND_ABILITY_STRING("Critical hits land more often."),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = _("Aftermath"),
        .description = COMPOUND_ABILITY_STRING("Contact hurts on faint and lowers speed.\nAlso does reduced effects on switch."),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = _("Anticipation"),
        .description = COMPOUND_ABILITY_STRING("Senses danger via instinct or nature.\nEnables the Pokémon to avoid danger once"),
        .aiRating = 5,
        .isSingleUse = TRUE,
        .timer = 1,
        .numAllowedInParty = 1,
    },

    [ABILITY_FOREWARN] =
    {
        .name = _("Forewarn"),
        .description = COMPOUND_ABILITY_STRING("Predicts a foe's move with psychic power.\nAvoids an attack from said foe once."),
        .aiRating = 5,
        .isSingleUse = TRUE,
        .timer = 1,
        .numAllowedInParty = 1,
    },

    [ABILITY_UNAWARE] =
    {
        .name = _("Unaware"),
        .description = COMPOUND_ABILITY_STRING("Ignores stat changes for dmg and acc.\nBlocks Intimidate, Taunt, and Torment."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = _("Tinted Lens"),
        .description = COMPOUND_ABILITY_STRING("Ups damage if move's type is resisted."),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = _("Filter"),
        .description = COMPOUND_ABILITY_STRING("Weakens incoming “Super effective”\nmoves."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = _("Slow Start"),
        .description = COMPOUND_ABILITY_STRING("Takes a while to get going.\nClears all ailments upon power awakening."),
        .aiRating = -2,
        .breakable = TRUE,
        .isSingleUse = TRUE,
        .timer = SLOW_START_TIMER,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = _("Scrappy"),
        .description = COMPOUND_ABILITY_STRING("Attacks bypass immunities of Ghost-type\nPokémon to deal neutral damage."),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = _("Storm Drain"),
        .description = COMPOUND_ABILITY_STRING("Draws in Water moves.\nBoosting Sp.Attack."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = _("Ice Body"),
        .description = COMPOUND_ABILITY_STRING("Slight HP recovery in Hail and Snow."),
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = _("Solid Rock"),
        .description = COMPOUND_ABILITY_STRING("Weakens incoming “Super effective”\nmoves."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = _("Snow Warning"),
        .description = COMPOUND_STRING("Summons snow in battle."),
        .aiRating = 8,
    },

    
    //attempt separate hail /snow set abilities
    //distribution would be a problem would want both
    //but can't have both some would have to be learned
    //...huh actually no, every mon that gets snow warning
    //has an open space I could slot in this
    //mega abomasnow would have to split base ability
    //potentially doable
    [ABILITY_CRYOSTORM] =
    {
        .name = _("Cryo-Storm"),
        .description = COMPOUND_ABILITY_STRING("Summons a hailstorm in battle."),
        .aiRating = 8,
    },
    

    [ABILITY_HONEY_GATHER] =
    {
        .name = _("Honey Gather"),
        .description = COMPOUND_ABILITY_STRING("May gather Honey gives off a sweet scent\nRecovers a little HP if holding Honey."),
        .aiRating = 4,
    },

    [ABILITY_FRISK] =
    {
        .name = _("Frisk"),
        .description = COMPOUND_ABILITY_STRING("Checks the foes' item. Also raises\nchance of extra effects on contact."),
        .aiRating = 4,
    },//vsonic

    [ABILITY_RECKLESS] =
    {
        .name = _("Reckless"),
        .description = COMPOUND_ABILITY_STRING("Boosts moves with recoil."),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = _("Multitype"),
        .description = COMPOUND_ABILITY_STRING("The Omnipotent One.\nIs every type."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = _("Flower Gift"),
        .description = COMPOUND_ABILITY_STRING("Transforms in sunshine."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },//cherrim ability needed to transform

    [ABILITY_BAD_DREAMS] =
    {
        .name = _("Bad Dreams"),
        .description = COMPOUND_ABILITY_STRING("Damages sleeping Pokémon."),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = _("Pickpocket"),
        .description = COMPOUND_ABILITY_STRING("Braces itself, to steal the foe's\nheld item when they make contact."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = _("Sheer Force"),
        .description = COMPOUND_ABILITY_STRING("Trades extra move effects for power."),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = _("Contrary"),
        .description = COMPOUND_ABILITY_STRING("Inverts stat changes."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = _("Unnerve"),
        .description = COMPOUND_ABILITY_STRING("Foes can't eat Berries.\nAlso raises their PP usage."),
        .aiRating = 6,
    },

    [ABILITY_DEFIANT] =
    {
        .name = _("Defiant"),
        .description = COMPOUND_ABILITY_STRING("Ups Attack if stats lowered.\nOr if suffering from status."),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = _("Defeatist"),
        .description = COMPOUND_ABILITY_STRING("Lowers offense and gives up at half HP.\nRaises speed to make escaping easier."),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = _("Cursed Body"),
        .description = COMPOUND_ABILITY_STRING("Disables moves on contact."),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = _("Healer"),
        .description = COMPOUND_ABILITY_STRING("If partner is statused, may attempt to\nheal them. Cures status."),
        .aiRating = 0,
    },//vsonic

    [ABILITY_FRIEND_GUARD] =
    {
        .name = _("Friend Guard"),
        .description = COMPOUND_ABILITY_STRING("Lowers damage to partner."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = _("Weak Armor"),
        .description = COMPOUND_ABILITY_STRING("When hit with a physical attack\nlowers defense and sharply raises speed."),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = _("Heavy Metal"),
        .description = COMPOUND_ABILITY_STRING("Doubles weight.\nBoosts power of STEEL moves."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = _("Light Metal"),
        .description = COMPOUND_ABILITY_STRING("Halves weight.\nRaises priority of STEEL moves."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = _("Multiscale"),
        .description = COMPOUND_ABILITY_STRING("Halves damage taken at full HP."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = _("Toxic Boost"),
        .description = COMPOUND_ABILITY_STRING("Ups Attack if poisoned or has Toxic orb.\nAnd ignores poison damage."),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = _("Flare Boost"),
        .description = COMPOUND_ABILITY_STRING("Ups Sp. Atk if burned or has Flame orb.\nAnd ignores burn damage."),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = _("Harvest"),
        .description = COMPOUND_ABILITY_STRING("May recycle a used Berry.\nGuaranteed recycle in sunny weather."),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = _("Telepathy"),
        .description = COMPOUND_ABILITY_STRING("Can't be damaged by an ally."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = _("Moody"),
        .description = COMPOUND_ABILITY_STRING("Stats change gradually."),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = _("Overcoat"),
        .description = COMPOUND_ABILITY_STRING("Blocks weather damage and powder effects"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = _("Poison Touch"),
        .description = COMPOUND_ABILITY_STRING("May poison a target when the Pokémon\nmakes contact."),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = _("Regenerator"),
        .description = COMPOUND_ABILITY_STRING("Restores a portion of HP\nupon switching out."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = _("Big Pecks"),
        .description = COMPOUND_ABILITY_STRING("Prevents Attack and Defense drop\nfrom external effects."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = _("Sand Rush"),
        .description = COMPOUND_ABILITY_STRING("Ups Speed in a sandstorm."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = _("Wonder Skin"),
        .description = COMPOUND_ABILITY_STRING("May avoid status problems."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = _("Analytic"),
        .description = COMPOUND_ABILITY_STRING("Moving last boosts power."),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = _("Illusion"),
        .description = COMPOUND_ABILITY_STRING("Appears as a partner."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = _("Imposter"),
        .description = COMPOUND_ABILITY_STRING("Transforms into the foe."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },//vsonic idk if finished this plan was transform into species that resists foe

    [ABILITY_INFILTRATOR] =
    {
        .name = _("Infiltrator"),
        .description = COMPOUND_ABILITY_STRING("Stealthily bypasses barriers and walls.\nAlso bypasses Substitute and Disguise."),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = _("Mummy"),
        .description = COMPOUND_ABILITY_STRING("Spreads with contact.\nOverwrites the attackers ability."),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = _("Moxie"),
        .description = COMPOUND_ABILITY_STRING("KOs raise Attack."),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = _("Justified"),
        .description = COMPOUND_ABILITY_STRING("Raises Attack if Intimidated\nor hit by Dark or Ghost moves."),
        .aiRating = 6,
    },

    [ABILITY_RATTLED] =
    {
        .name = _("Rattled"),
        .description = COMPOUND_ABILITY_STRING("Raises Speed if Intimdated or\nhit by Dark, Bug, or Ghost moves."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = _("Magic Bounce"),
        .description = COMPOUND_ABILITY_STRING("Reflects status moves and non-redirected\nstat decreases from abilities."),
        .aiRating = 9,
        .breakable = TRUE,
    },//reflects intimidate likes, gave small bit of mirror armor effect

    [ABILITY_SAP_SIPPER] =
    {
        .name = _("Sap Sipper"),
        .description = COMPOUND_ABILITY_STRING("Draws in Grass moves\nto increase Attack."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = _("Prankster"),
        .description = COMPOUND_ABILITY_STRING("Status moves get a priority boost."),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = _("Sand Force"),
        .description = COMPOUND_ABILITY_STRING("Powers up in a sandstorm."),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = _("Iron Barbs"),
        .description = COMPOUND_ABILITY_STRING("Hurts to make contact."),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = _("Zen Mode"),
        .description = COMPOUND_ABILITY_STRING("Transforms at half HP."),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = _("Victory Star"),
        .description = COMPOUND_ABILITY_STRING("Raises party accuracy and speed."),
        .aiRating = 7,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = _("Turboblaze"),
        .description = COMPOUND_ABILITY_STRING("Moldbreaker and Flash Fire."),
        .aiRating = 9,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = _("Teravolt"),
        .description = COMPOUND_ABILITY_STRING("Moldbreaker and Lightning Rod."),
        .aiRating = 9,
    },
    //with change should be breakable 
    //but will take point from full metal body 
    //and leave off

    [ABILITY_AROMA_VEIL] =
    {
        .name = _("Aroma Veil"),
        .description = COMPOUND_ABILITY_STRING("Protects itself and allies from effects\nthat prevent the use of moves."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = _("Flower Veil"),
        .description = COMPOUND_ABILITY_STRING("Protects Grass-types on user's side\nfrom status and stat changing effects."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = _("Cheek Pouch"),
        .description = COMPOUND_ABILITY_STRING("Eating Berries restores HP.\nCan Belch without eating a berry."),
        .aiRating = 4,
    },//vsonic cant remeber what note for

    [ABILITY_PROTEAN] =
    {
        .name = _("Protean"),
        .description = COMPOUND_ABILITY_STRING("Changes type to used move."),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = _("Fur Coat"),
        .description = COMPOUND_ABILITY_STRING("Raises Defense."),
        .aiRating = 7,
        .breakable = TRUE,
    },//vsonic make better description

    [ABILITY_MAGICIAN] =
    {
        .name = _("Magician"),
        .description = COMPOUND_ABILITY_STRING("Steals foe's item when it does dmg."),
        .aiRating = 5,
    },//figure out better description

    [ABILITY_BULLETPROOF] =
    {
        .name = _("Bulletproof"),
        .description = COMPOUND_ABILITY_STRING("Immune to ball-based projectiles\nand explosions."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = _("Competitive"),
        .description = COMPOUND_ABILITY_STRING("Ups Sp. Atk. if stats lowered.\nOr if suffering from status."),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = _("Strong Jaw"),
        .description = COMPOUND_ABILITY_STRING("Boosts biting moves."),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = _("Refrigerate"),
        .description = COMPOUND_ABILITY_STRING("Normal moves become Ice."),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = _("Sweet Veil"),
        .description = COMPOUND_ABILITY_STRING("Protects party from sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = _("Stance Change"),
        .description = COMPOUND_ABILITY_STRING("Changes form based on moves used."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = _("Gale Wings"),
        .description = COMPOUND_ABILITY_STRING("Flying moves get a priority boost\nwhen at above 50% HP."),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = _("Mega Launcher"),
        .description = COMPOUND_ABILITY_STRING("Boosts pulse moves."),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = _("Grass Pelt"),
        .description = COMPOUND_ABILITY_STRING("Prevents critical hits.\nUps Defense when on grassy terrain."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = _("Symbiosis"),
        .description = COMPOUND_ABILITY_STRING("Passes its item to an ally."),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = _("Tough Claws"),
        .description = COMPOUND_ABILITY_STRING("Boosts contact moves."),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = _("Pixilate"),
        .description = COMPOUND_ABILITY_STRING("Normal and Sound moves become Fairy."),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = _("Gooey"),
        .description = COMPOUND_ABILITY_STRING("Lowers Speed on contact."),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = _("Aerilate"),
        .description = COMPOUND_ABILITY_STRING("Normal moves become Flying."),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = _("Parental Bond"),
        .description = COMPOUND_ABILITY_STRING("Moves hit twice second hit does less dmg."),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = _("Dark Aura"),
        .description = COMPOUND_ABILITY_STRING("Boosts Dark moves."),
        .aiRating = 6,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = _("Fairy Aura"),
        .description = COMPOUND_ABILITY_STRING("Boosts Fairy moves."),
        .aiRating = 6,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = _("Aura Break"),
        .description = COMPOUND_ABILITY_STRING("Reverse aura abilities.\nWeakens Dark and Fairy moves."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = _("Primordial Sea"),
        .description = COMPOUND_ABILITY_STRING("Summons heavy rain."),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = _("Desolate Land"),
        .description = COMPOUND_ABILITY_STRING("Summons intense sunlight."),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = _("Delta Stream"),
        .description = COMPOUND_ABILITY_STRING("Summons strong winds, that cover the\nweaknesses of flying and wind types."),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = _("Stamina"),
        .description = COMPOUND_ABILITY_STRING("Boosts Defense when hit."),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = _("Wimp Out"),
        .description = COMPOUND_ABILITY_STRING("Flees if HP below half after attacking."),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = _("Emergency Exit"),
        .description = COMPOUND_ABILITY_STRING("When HP falls below half delivers a\nsudden vindictive attack then flees."),
        .aiRating = 5,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = _("Water Compaction"),
        .description = COMPOUND_ABILITY_STRING("Water attacks sharply boosts Defense.\nSligthtly resists water damage."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MERCILESS] =
    {
        .name = _("Merciless"),
        .description = COMPOUND_ABILITY_STRING("Deals critical damage to poisoned foes."),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = _("Shields Down"),
        .description = COMPOUND_ABILITY_STRING("If HP above 50% boosts Def blocks status\nWhen below, shell breaks and boosts atk."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = _("Stakeout"),
        .description = COMPOUND_ABILITY_STRING("2x damage if targets switched in mid turn\n50% boost to foes replacing fainted ally"),
        .aiRating = 6,
    },//made just swith in generally easier to use balaned by limited distribution

    [ABILITY_WATER_BUBBLE] =
    {
        .name = _("Water Bubble"),
        .description = COMPOUND_ABILITY_STRING("Guards from fire damage and burns.\nBoosts power of user water moves."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = _("Steelworker"),
        .description = COMPOUND_ABILITY_STRING("Powers up Steel moves."),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = _("Berserk"),
        .description = COMPOUND_ABILITY_STRING("Boosts the Pokémon's Sp. Atk if\nan attack drops its HP to half or less."),
        .aiRating = 5,
    },//vsonic

    [ABILITY_SLUSH_RUSH] =
    {
        .name = _("Slush Rush"),
        .description = COMPOUND_ABILITY_STRING("Raises Speed in hail and snow."),
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = _("Long Reach"),
        .description = COMPOUND_ABILITY_STRING("Never makes contact. Boosts priority\nof non-contact physical moves."),
        .aiRating = 5,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = _("Liquid Voice"),
        .description = COMPOUND_ABILITY_STRING("Makes sound moves become Water Type."),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = _("Triage"),
        .description = COMPOUND_ABILITY_STRING("Healing moves get a priority boost."),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = _("Galvanize"),
        .description = COMPOUND_ABILITY_STRING("Normal moves become Electric and\ngain a boost in power."),
        .aiRating = 8,
    },//vsonic pretty sure need change all these to work on normal and sound

    [ABILITY_SURGE_SURFER] =
    {
        .name = _("Surge Surfer"),
        .description = COMPOUND_ABILITY_STRING("Faster on electric terrain."),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = _("Schooling"),
        .description = COMPOUND_ABILITY_STRING("Heals on switch, and forms together\nif lvl. 20+ and above a quarter Max HP"),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = _("Disguise"),
        .description = COMPOUND_ABILITY_STRING("Decoy protects it once."),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = _("Battle Bond"),
        .description = COMPOUND_ABILITY_STRING("Changes form after a KO."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },//considered making mega but think will make unique form akin to mega
    //while allowing my form to replace the mega it did get

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = _("Power Construct"),
        .description = COMPOUND_ABILITY_STRING("Cells aid it when Hp falls below half,\ntransforming it to its complete form."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },//vsoni not treated like mega but could give mega hp recover
    //that said mon still gains hp since forms have increased hp

    [ABILITY_CORROSION] =
    {
        .name = _("Corrosion"),
        .description = COMPOUND_ABILITY_STRING("Able to Poison any type\neven if otherwise immune."),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = _("Comatose"),
        .description = COMPOUND_ABILITY_STRING("Always drowsing.\nRecovers HP slightly each turn."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = _("Queenly Majesty"),
        .description = COMPOUND_ABILITY_STRING("Blocks boosted priority moves\nfor itself and allies and Intimidate."),
        .aiRating = 8,//6,
        .breakable = TRUE,
    },//idk if gen 9 change but realized affects entire side o.0

    [ABILITY_INNARDS_OUT] =
    {
        .name = _("Innards Out"),
        .description = COMPOUND_ABILITY_STRING("On faint hurts foe for last hp dmg dealt.\nIf damaged on switch-in strikes back."),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = _("Dancer"),
        .description = COMPOUND_ABILITY_STRING("Dances along with others.\nUses Dance Move right after previous user"),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = _("Battery"),
        .description = COMPOUND_ABILITY_STRING("Boosts ally's Sp. Atk if ally is Vikavolt\ncombines with and powers up ally."),
        .aiRating = 0,
    },
    //vsonic think idea was turn this into vikavolt version of tatsugiri dondozo effect
    //1 stage boost to all battle stats
    //just regular ancient power stuff skip acc eva

    [ABILITY_FLUFFY] =
    {
        .name = _("Fluffy"),
        .description = COMPOUND_ABILITY_STRING("Takes increased damage from FIRE moves.\nTakes reduced damage from contact moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = _("Dazzling"),
        .description = COMPOUND_ABILITY_STRING("Blocks boosted priority moves\nfor itself and allies."),
        .aiRating = 5,
        .breakable = TRUE,
    }, //didn't know this description repeated pretty sure effect is now different

    [ABILITY_SOUL_HEART] =
    {
        .name = _("Soul-Heart"),
        .description = COMPOUND_ABILITY_STRING("KOs raise Sp. Atk."),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = _("Tangling Hair"),
        .description = COMPOUND_ABILITY_STRING("Lowers Speed on contact."),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = _("Receiver"),
        .description = COMPOUND_ABILITY_STRING("Copies ally's ability."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = _("Power Of Alchemy"),
        .description = COMPOUND_ABILITY_STRING("Copies ally's ability."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = _("Beast Boost"),
        .description = COMPOUND_ABILITY_STRING("KOs boost the Pokémon's best stat."),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = _("RKS System"),
        .description = COMPOUND_ABILITY_STRING("Held Memories change its type."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = _("Electric Surge"),
        .description = COMPOUND_ABILITY_STRING("Field becomes Electric. Ups Elec. moves\nand prevents grounded from sleeping."),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = _("Psychic Surge"),
        .description = COMPOUND_ABILITY_STRING("Field becomes weird. Ups Psych. moves\nNon-spread prio. moves fail on grounded."),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = _("Misty Surge"),
        .description = COMPOUND_ABILITY_STRING("Field becomes misty. Weaken Dragon moves\nBoosts attack recovery & blocks statusing"),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = _("Grassy Surge"),
        .description = COMPOUND_ABILITY_STRING("Field becomes grassy. Ups Grass moves.\nSlight HP recovery for grounded Pokémon."),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = _("Full Metal Body"),
        .description = COMPOUND_ABILITY_STRING("Prevents stat reduction."),
        .aiRating = 4,
    },//vsonic
    //not breakable for some reason

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = _("Shadow Shield"),
        .description = COMPOUND_ABILITY_STRING("Halves damage taken at full HP."),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = _("Prism Armor"),
        .description = COMPOUND_ABILITY_STRING("Weakens incoming “Super effective”\nmoves."),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = _("Neuroforce"),
        .description = COMPOUND_ABILITY_STRING("Ups power of “supereffective” moves."),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = _("Intrepid Sword"),
        .description = COMPOUND_ABILITY_STRING("The Hero arrives!\nUps Attack for one turn on entry."),
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = _("Dauntless Shield"),
        .description = COMPOUND_ABILITY_STRING("The Hero arrives!\nUps Defense for one turn on entry."),
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = _("Libero"),
        .description = COMPOUND_ABILITY_STRING("Changes type to used move."),
    },//vsonic see if changed may revert back, to making monotype
    //oh it is set to that, type 1 and 2 are changed but type 3 stays the same

    [ABILITY_BALL_FETCH] =
    {
        .name = _("Ball Fetch"),
        .description = COMPOUND_ABILITY_STRING("May Fetch failed Poké Balls back to bag.\nImmediately returns Ball Moves to user."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = _("Cotton Down"),
        .description = COMPOUND_ABILITY_STRING("Lower Speed of all when hit."),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = _("Propeller Tail"),
        .description = COMPOUND_ABILITY_STRING("Ignores foe's redirection."),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = _("Mirror Armor"),
        .description = COMPOUND_ABILITY_STRING("Reflect stat decreases back to the user."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = _("Gulp Missile"),
        .description = COMPOUND_ABILITY_STRING("If hit, spits prey caught in its mouth."),
        .aiRating = 3,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = _("Stalwart"),
        .description = COMPOUND_ABILITY_STRING("Ignores foe's redirection."),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = _("Steam Engine"),
        .description = COMPOUND_ABILITY_STRING("Fire or Water hits up Speed.\nAlso shortens Egg Hatch Time."),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("Punk Rock"),
        .description = COMPOUND_ABILITY_STRING("Ups and resists sound attacks."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = _("Sand Spit"),
        .description = COMPOUND_ABILITY_STRING("Creates a sandstorm if hit."),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = _("Ice Scales"),
        .description = COMPOUND_ABILITY_STRING("Halves damage taken from special moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = _("Ripen"),
        .description = COMPOUND_ABILITY_STRING("Doubles effect of Berries."),
        .aiRating = 4,
    },//vsonic

    [ABILITY_ICE_FACE] =
    {
        .name = _("Ice Face"),
        .description = COMPOUND_ABILITY_STRING("Takes 2 physical hits then changes form.\nHail and snow renews this ability."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = _("Power Spot"),
        .description = COMPOUND_ABILITY_STRING("Powers up ally moves."),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = _("Mimicry"),
        .description = COMPOUND_ABILITY_STRING("Changes type on terrain."),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = _("Screen Cleaner"),
        .description = COMPOUND_ABILITY_STRING("Removes walls of light."),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = _("Steely Spirit"),
        .description = COMPOUND_ABILITY_STRING("Boosts user's and ally's Steel moves."),
        .aiRating = 2, //vsonic
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = _("Perish Body"),
        .description = COMPOUND_ABILITY_STRING("Foe faints in 3 turns if hit."),
        .aiRating = 4,
    },
    //no longer makes user faint, only low value cuz of who its on.
    //idea being ghosts can't die.  also mon is frail as cheese

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = _("Wandering Spirit"),
        .description = COMPOUND_ABILITY_STRING("Trade abilities on contact."),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = _("Gorilla Tactics"),
        .description = COMPOUND_ABILITY_STRING("Ups Attack and Sp.Attack but locks moves"),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = _("Neutralizing Gas"),
        .description = COMPOUND_ABILITY_STRING("All Abilities are nullified."),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = _("Pastel Veil"),
        .description = COMPOUND_ABILITY_STRING("Protects team from poison."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = _("Hunger Switch"),
        .description = COMPOUND_ABILITY_STRING("Changes form each turn.\nBoosts type dmg based on form."),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },//
    //only importance of form is the type of its siganture ability
    //aura wheel swaps between electric or dark type
    //mon was zu but think just needs better moves
    //but could give little push here as well could give it the iron fist bonus
    //shouldn't be too crazy make function to return hunger switch type
    //use that for logic in aura wheel and type to boost

    [ABILITY_QUICK_DRAW] =
    {
        .name = _("Quick Draw"),
        .description = COMPOUND_ABILITY_STRING("Moves first occasionally."),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = _("Unseen Fist"),
        .description = COMPOUND_ABILITY_STRING("Contact moves at or below 75 power\nevades protection."),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = _("Curious Medicine"),
        .description = COMPOUND_ABILITY_STRING("Remove ally's stat changes."),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("Transistor"),
        .description = COMPOUND_ABILITY_STRING("Ups Electric-type moves by 30 percent."),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = _("Dragon's Maw"),
        .description = COMPOUND_ABILITY_STRING("Ups Dragon-type moves by 50 percent."),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = _("Chilling Neigh"),
        .description = COMPOUND_ABILITY_STRING("KOs boost Attack stat."),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = _("Grim Neigh"),
        .description = COMPOUND_ABILITY_STRING("KOs boost Sp. Atk stat."),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = _("As One"),
        .description = COMPOUND_ABILITY_STRING("Foes can't eat Berries and\nKOs boost Attack stat."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = _("As One"),
        .description = COMPOUND_ABILITY_STRING("Foes can't eat Berries and\nKOs boost Sp. Atk stat."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },//want to remove pp loss from this just keep on unnerve
    //should be fine just need explicitly put unnerve in pp stuff

    [ABILITY_LINGERING_AROMA] =
    {
        .name = _("Lingering Aroma"),
        .description = COMPOUND_STRING("Spreads with contact.\nOverwrites attacker ability."),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = _("Seed Sower"),
        .description = COMPOUND_STRING("Turns the ground into Grassy Terrain\nwhen the Pokémon is hit by an attack."),//vsonic
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = _("Thermal Exchange"),
        .description = COMPOUND_STRING("Boosts Attack when hit by a Fire move.\nThe Pokémon also cannot be burned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = _("Anger Shell"),
        .description = COMPOUND_STRING("When an attack drops its HP to <= half,\ndef stats fall, ups Atk stats and speed."),//vsonic
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = _("Purifying Salt"),
        .description = COMPOUND_ABILITY_STRING("The Pokémon's pure salt protects it.\nReduces Ghost damage and blocks status."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = _("Well-Baked Body"),
        .description = COMPOUND_STRING("The Pokémon takes is immune to Fire moves\nInstead, its Defense is sharply boosted."), //vsonic
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = _("Wind Rider"),
        .description = COMPOUND_ABILITY_STRING("Takes no damage from Wind Effects instead\nps Atk if the target of a wind effect."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = _("Guard Dog"),
        .description = COMPOUND_STRING("Boosts the Pokémon’s Atk if intimidated.\nMoves or items that force switch out fail"),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = _("Rocky Payload"),
        .description = COMPOUND_STRING("Powers up Rock moves by 50 percent."),
        .aiRating = 6,
    },//didn't realize that's what this did, but its basically fake stab
    //do I need to lower it to match new stab
    //mon its on isn't that good so will live at default

    [ABILITY_WIND_POWER] =
    {
        .name = _("Wind Power"),
        .description = COMPOUND_STRING("The Pokémon becomes charged by wind moves\nboosting the power of its next Elec. move"),
        .aiRating = 4,
    },//vsonic wind moves not set yet

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = _("Zero to Hero"),
        .description = COMPOUND_STRING("Changes form on switch out."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = _("Commander"),
        .description = COMPOUND_STRING("Commands from Dondozo."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },//make better description mention stat boosts

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = _("Electromorphosis"),
        .description = COMPOUND_STRING("The Pokémon becomes charged when damaged,\nboosting the power of its next Elec. move"),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = _("Protosynthesis"),
        .description = COMPOUND_STRING("Sun boosts best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = _("Quark Drive"),
        .description = COMPOUND_STRING("Elec. field ups best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = _("Good as Gold"),
        .description = COMPOUND_STRING("Avoids status problems."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = _("Vessel of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Sp.Atk by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = _("Sword of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Defense by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = _("Tablets of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Speed by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = _("Beads of Ruin"),
        .description = COMPOUND_ABILITY_STRING("Lowers Sp.Def by 25 percent\nfor all mon without this ability."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = _("Orichalcum Pulse"),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = _("Hadron Engine"),
        .description = COMPOUND_STRING("Field becomes Electric."),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = _("Opportunist"),
        .description = COMPOUND_STRING("Copies foe's stat change."),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = _("Cud Chew"),
        .description = COMPOUND_STRING("Eats a used berry again."),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = _("Sharpness"),
        .description = COMPOUND_ABILITY_STRING("A specialist in sharp cutting attacks.\nPowers up Slicing-moves."),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = _("Supreme Overlord"),
        .description = COMPOUND_STRING("Inherits fallen's strength."),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = _("Costar"),
        .description = COMPOUND_STRING("Copies ally's stat changes."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = _("Toxic Debris"),
        .description = COMPOUND_STRING("Throws poison spikes if hit."),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = _("Armor Tail"),
        .description = COMPOUND_ABILITY_STRING("Blocks boosted priority moves\nfor itself and allies."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = _("Earth Eater"),
        .description = COMPOUND_STRING("Eats ground to heal HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = _("Mycelium Might"),
        .description = COMPOUND_STRING("Status moves never fail."),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = _("Hospitality"),
        .description = COMPOUND_STRING("Restores ally's HP."),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = _("Mind's Eye"),
        .description = COMPOUND_STRING("Ignores the immunities of GHOST types.\nIgnore Evasion checks and Acc can't fall."),
        .aiRating = 8,
        .breakable = TRUE,
    },//not mix of scrappy is just foresight
    //...oh its keen eye scrappy o.0
    //giving base scrappy not updated effects as ability and mon with it are already op

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Speed."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Attack."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Sp. Def."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Defense."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = _("Toxic Chain"),
        .description = COMPOUND_STRING("The corrosive chain empowers its moves.\nMay badly poison any target of attack."),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = _("Supersweet Syrup"),
        .description = COMPOUND_ABILITY_STRING("Gives off a sweet scent.\nAlso lowers foes evasion on switch-in."),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = _("Tera Shift"),
        .description = COMPOUND_STRING("Terastallizes upon entry."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = _("Tera Shell"),
        .description = COMPOUND_STRING("Resists all at full HP."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = _("Teraform Zero"),
        .description = COMPOUND_STRING("Zeroes weather and terrain."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = _("Poison Puppeteer"),
        .description = COMPOUND_STRING("Confuses poisoned foes."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    //Begin of Custom abilities
    [ABILITY_DISPIRIT_GUARD] =
    {
        .name = _("Dispirit Guard"),
        .description = COMPOUND_ABILITY_STRING("“Not very effective” hits."),
        .aiRating = 8,
        .breakable = TRUE,
    },
    //may change but rn includes what was previously neutral hits as resisted
    //
    
    [ABILITY_NUISANCE] =
    {
        .name = _("Nuisance"),
        .description = COMPOUND_ABILITY_STRING("“Weak attacks” get a priority boost.\nExcludes variable power moves."),
        .aiRating = 5,
    },
    
    [ABILITY_MULTI_TASK] =
    {
        .name = _("Multi-Task"),
        .description = COMPOUND_ABILITY_STRING("Damaging Attacks are multi-hit.\nMulti-hit moves hit 5 times."),
        .aiRating = 4,
    },
    
    [ABILITY_SIROCCO] =
    {
        .name = _("Sirocco"),
        .description = COMPOUND_ABILITY_STRING("Kicks up a sandstorm on contact."),
        .aiRating = 4,
    },
    
    [ABILITY_HI_PRESSURE] =
    {
        .name = _("Hi-Pressure"),
        .description = COMPOUND_ABILITY_STRING("Sharply raises foe's PP usage.\nMay make foe too afraid to attack well."),
        .aiRating = 7,
        .breakable = TRUE,
    },
    
    [ABILITY_CUPIDS_ARROW] =
    {
        .name = _("Cupid's Arrow"),
        .description = COMPOUND_ABILITY_STRING("Infatuates foes upon switching in."),
        .aiRating = 0,
    },
    
    [ABILITY_BATTLE_MATRON] =
    {
        .name = _("Battle Matron"),
        .description = COMPOUND_ABILITY_STRING("Powers up moves to protect young PKMN.\nBoost damage if ally not fully evolved."),
        .aiRating = 0,
    },
    
    [ABILITY_LIQUID_SOUL] =
    {
        .name = _("Liquid Soul"),
        .description = COMPOUND_ABILITY_STRING("Recalls a time it dwelled in the sea.\nReduces Damage from Water-type moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },
    
    [ABILITY_OCEAN_MEMORY] =
    {
        .name = _("Ocean Memory"),
        .description = COMPOUND_ABILITY_STRING("Turns users Water moves into Ghost moves\nand is immune to Water dmg."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_OVERCHARGE] =
    {
        .name = _("Overcharge"),
        .description = COMPOUND_ABILITY_STRING("Ups ELECTRIC moves in a pinch.\nThe POKéMON charges up to the max!"),
        .aiRating = 5,
        
    },
    
    [ABILITY_PHOTOSYNTHESIZE] =
    {
        .name = _("Photosynthesize"),
        .description = COMPOUND_ABILITY_STRING("Moderate HP recovery in sun."),
        .aiRating = 3,
    },
    
    [ABILITY_GLACIAL_ICE] =
    {
        .name = _("Glacial Ice"),
        .description = COMPOUND_ABILITY_STRING("Is immune to fire,\nand turns ice and hail and snow into hp."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_LAVA_FISSURE] =
    {
        .name = _("Lava Fissure"),
        .description = COMPOUND_ABILITY_STRING("Draws in and powers up fire moves\nPrevents Freeze, field becomes scorched."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_TOADSTOOL_NYMPH] =
    {
        .name = _("Toadstool Nymph"),
        .description = COMPOUND_ABILITY_STRING("Add STAB on FAIRY moves. A fae blessing\ngiven for devotion to nature."),
        .aiRating = 3,
    },
    
    [ABILTY_UNKNOWN_POWER] =
    {
        .name = _("Unknown Power"),
        .description = COMPOUND_ABILITY_STRING("A mysterious ability from the unown\ndimension, doubles power when with unown"),
        .aiRating = 2,
    },
    
    [ABILITY_PURIFYING_AURA] =
    {
        .name = _("Purifying Aura"),
        .description = COMPOUND_ABILITY_STRING("Status heal.The POKéMON flares its aura\npurifying itself and allies in reach."),
        .aiRating = 0,
    },
    
    [ABILITY_SQUALL] =
    {
        .name = _("Squall"),
        .description = COMPOUND_ABILITY_STRING("Summons a rain shower,\nthat temporarily drenches the field."),
        .aiRating = 7,
    },
    
    [ABILITY_SUN_DISK] =
    {
        .name = _("Sun Disk"),
        .description = COMPOUND_ABILITY_STRING("The POKéMON gives thanks to the sun.\nTemporarily boosting sunlight in battle."),
        .aiRating = 7,
    },
    
    [ABILITY_TOUGH_SPINES] =
    {
        .name = _("Tough Spines"),
        .description = COMPOUND_ABILITY_STRING("Stabs the foe with thorn like spines\non contact."),
        .aiRating = 6,
    },
    
    [ABILITY_EROSION] =
    {
        .name = _("Erosion"),
        .description = COMPOUND_ABILITY_STRING("Breaks down incoming Rock-type attacks,\nand uses the minerals to heal itself."),
        .aiRating = 7,
        .breakable = TRUE,
    },
    
    [ABILITY_LIQUID_METAL] =
    {
        .name = _("Liquid Metal"),
        .description = COMPOUND_ABILITY_STRING("A strange light-weight body, immune to\nstat reduction that resists physical dmg"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_MUSCLE_MAGIC] =
    {
        .name = _("Muscle Magic"),
        .description = COMPOUND_ABILITY_STRING("Special moves become Physical contact.\nControl the elements with pure Muscle!"),
        .aiRating = 5,
    },
    
    [ABILITY_TIGER_CUB] =
    {
        .name = _("Tiger Cub"),
        .description = COMPOUND_ABILITY_STRING("To rise to the high expectations\nof the pride. Ups resisted move dmg."),
        .aiRating = 7,
    },
    
    [ABILITY_TIGER_MOM] =
    {
        .name = _("Tiger Mom"),
        .description = COMPOUND_ABILITY_STRING("Postures with an overbearing presence.\nLowers the foe's DEFENSE."),
        .aiRating = 7,
    },
    
    [ABILITY_DARK_DEAL] =
    {
        .name = _("Dark Deal"),
        .description = COMPOUND_ABILITY_STRING("Increases crit and effect chance. Halves\npartner's 80+ pwr moves to share ability."),
        .aiRating = 6,
    },//vsonic looks good but not fully accurate as it doubels effect for partner
    
    [ABILITY_CORRUPTION] =
    {
        .name = _("Corruption"),
        .description = COMPOUND_ABILITY_STRING("The user's corrupted influence spreads\ndecay. Preventing the foe from healing."),
        .aiRating = 0,
    },//heal block
    //for sake of balance rather than enemy side
    //could potentially make it work for every battler except the user
    //so would loop all battlers except attacker/holder
    //and set heal block volatile for them
    //and rather than timer won't clear until battler is off field
    //essentailly same setup as neutralizing gas vsonic

    
    [ABILITY_BANDIT_KING] =
    {
        .name = _("Bandit King"),
        .description = COMPOUND_ABILITY_STRING("This POKéMON posesses a covetous nature.\nIt won't let its targets use items."),
        .aiRating = 0,
    },
    
    [ABILITY_AVIATOR] =
    {
        .name = _("Aviator"),
        .description = COMPOUND_ABILITY_STRING("An uncontested ace that always escapes.\nStops speed loss, gains FLYING Affinity."), 
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic maybe just need add breakable ot do thing rather than needing moldbreaker check function?
    //yeah think all I need for moldbreaker negate is set every affinity ability as breakable
    //well no its meant to ignore affinity itself not just the ability
    //so its supposed to work through the type would still need negation function
    //or put logic directly into affinity function by adding, atk battler
    //and atk ability arguments to it?
    
    [ABILITY_USURPER] =
    {
        .name = _("Usurper"),
        .description = COMPOUND_ABILITY_STRING("Ups Atk and Sp. Atk. if stats lowered\nor if suffering from status."),
        .aiRating = 10,
    },
    
    [ABILITY_INVERSE_WORLD] =
    {
        .name = _("Inverse World"),
        .description = COMPOUND_ABILITY_STRING("Inverts incoming damage,\nand resisted or immune attacks."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },//vsonic IMPORTANT //is field wide effect similar to neutralizing gas unsure what to do with?
    
    [ABILITY_SONAR] =
    {
        .name = _("Sonar"),
        .description = COMPOUND_ABILITY_STRING("Emits infrasonic sound with each attack.\nBoosts sound based move damage by 1.5x"),
        .aiRating = 0,
    },
    
    [ABILITY_ECOSYSTEM] =
    {
        .name = _("Ecosystem"),
        .description = COMPOUND_ABILITY_STRING("Makes Grass resist Ice damage.\nSets third type to water."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_ABSOLUTE_ZERO] =
    {
        .name = _("Absolute Zero"),
        .description = COMPOUND_ABILITY_STRING("Makes Dragon resist Ice damage.\nFreezes all Water-type moves."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_FEATHER_JACKET] =
    {
        .name = _("Feather Jacket"),
        .description = COMPOUND_ABILITY_STRING("Protected from the cold by\na jacket of downy feathers."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_POISONED_LEGACY] =
    {
        .name = _("Poisoned Legacy"),
        .description = COMPOUND_ABILITY_STRING("Can ignore PSN Imm/Rst. In a pinch ups\nPSN & ensures toxic if move can poison."),
        .aiRating = 0,
    },//ugly as hell but only way could fit all effets...
    
    [ABILITY_JEWEL_METABOLISM] =
    {
        .name = _("Jewel Metabolism"),
        .description = COMPOUND_ABILITY_STRING("Consumes Rock-type moves.\nAlso raises Defense one stage."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_INVERSION] =
    {
        .name = _("Inversion"),
        .description = COMPOUND_ABILITY_STRING("Transforms into a copy that resists\nthe type of the foe."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },//upgraded imposter
    
    [ABILITY_WETIKO] =
    {
        .name = _("Wetiko"),
        .description = COMPOUND_ABILITY_STRING("The Wendigo curse, all moves become Ice.\nHeals upon switching out."),
        .aiRating = 9,
    },
    
    [ABILITY_EMPATH] =
    {
        .name = _("Empath"),
        .description = COMPOUND_ABILITY_STRING("Passes on status problems.\nAs well as stat reductions."),
        .aiRating = 0,
    },//upgraded Trace same conditions
    //why am I calling this trace when its synchronize?     
    
    [ABILITY_EMPATHIC_CURSE] =
    {
        .name = _("Empathic Curse"),
        .description = COMPOUND_ABILITY_STRING("Passes on status problems.\nAnd a portion of its pain as damage."),
        .aiRating = 0,
    },
    
    [ABILITY_INTHRALL] =
    {
        .name = _("Inthrall"),
        .description = COMPOUND_ABILITY_STRING("When the PKMN hits the foe with a move\nit seals their memory disabling a move."),
        .aiRating = 0,
    },
    
    [ABILITY_IRON_WILL] =
    {
        .name = _("Iron Will"),
        .description = COMPOUND_ABILITY_STRING("May make enemy too fearful to attack\nor unable to use their full strength."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_LIVEWIRE] =
    {
        .name = _("Livewire"),
        .description = COMPOUND_ABILITY_STRING("Body made of electricity\nUps damage of electric moves."),
        .aiRating = 0,
    },
    
    [ABILITY_GALEFORCE] =
    {
        .name = _("GaleForce"),
        .description = COMPOUND_ABILITY_STRING("Immune to wind-based moves\nBoosts Sp. Atk when hit by them."),
        .aiRating = 6,
        .breakable = TRUE,
    },
    
    [ABILITY_LETHAL_LEGS] =
    {
        .name = _("Lethal Legs"),
        .description = COMPOUND_ABILITY_STRING("Boosts Kicking moves."),
        .aiRating = 6,
    },
    
    [ABILITY_TOXUNGUE] =
    {
        .name = _("Toxunge"),
        .description = COMPOUND_ABILITY_STRING("Strikes foe with toxungen covered tongue\nMay Paralyze on contact."),
        .aiRating = 4,
    },
    
    [ABILITY_OMNIPOTENT_AIDE] =
    {
        .name = _("Omnipotent Aide"),
        .description = COMPOUND_ABILITY_STRING("Gives priority to healing effects.\nBut can only heal allies not itself."),
        .aiRating = 0,
    },
    
    [ABILITY_FLUORESCENCE] =
    {
        .name = _("Fluorescence"),
        .description = COMPOUND_ABILITY_STRING("Naturally absorbs sunlight.\nBoosts speed and Sp.Atk in sun."),
        .aiRating = 0,
    },
    
    [ABILITY_SPECTRE] =
    {
        .name = _("Spectre"),
        .description = COMPOUND_ABILITY_STRING("A speeding Blur!\nBoosts Evasion on Switch-in."),
        .aiRating = 0,
        .isSingleUse = TRUE,
        .timer = SPECTRE_TIMER,
    },
    
    [ABILITY_AURA_OF_LIGHT] =
    {
        .name = _("Aura of Light"),
        .description = COMPOUND_ABILITY_STRING("Wakes allies on switch-in and prevents\nsleep. Also cuts damage from dark moves."),
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic
    
    [ABILITY_DESPAIR] =
    {
        .name = _("Despair"),
        .description = COMPOUND_ABILITY_STRING("Even the waking world becomes a nightmare\nHealing becomes dmg for opposing side."),
        .aiRating = 0,
    },
    //todo - anti heal ability for opposing side plan darkrai use
    //in practice does pretty much same as bad dreams when they try to sleep
    //they'd take damage intead of healing
    //but darkrai won't be healed from it
    //considering if I should put extra protection on this
    //if heal is greater than quarter hp either divide by 2
    //or cap at quarter hp, similar to trap effects
    //use min function I think -done
    //exclusive ability
    
    [ABILITY_RISING_PHOENIX] =
    {
        .name = _("Rising Phoenix"),
        .description = COMPOUND_ABILITY_STRING("Cures status heals and cleanses field if\nhit by fire. May also burn on contact."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_DREAD_WING] =
    {
        .name = _("Dread Wings"),
        .description = COMPOUND_ABILITY_STRING("Spreads despair. Foes take more damage.\nWeakens foes Physical Attacks."),
        .aiRating = 0,
        .breakable = TRUE,
    },//potentially make these two un suppressable?
    //no being unsuppressable is only for things
    //that would break or cause glitches otherwise
    
    [ABILITY_PLAGUE_WINGS] =
    {
        .name = _("Plague Wings"),
        .description = COMPOUND_ABILITY_STRING("Spreads powder-like scales on attack.\nThat apply a variety of statuses."),
        .aiRating = 5,
    },
    
    [ABILITY_TOXIC_WING] =
    {
        .name = _("Toxic Wing"),
        .description = COMPOUND_ABILITY_STRING("Spreads poison powder on attack.\nMay poison the foe."),
        .aiRating = 5,
    },
    
    [ABILITY_PHANTOM_TOUCH] =
    {
        .name = _("Phantom Touch"),
        .description = COMPOUND_ABILITY_STRING("Contact moves ignore the immunities\nof GHOST types."),
        .aiRating = 6,
    },
    
    [ABILITY_APOTHEOSCENT] =
    {
        .name = _("Apotheoscent"),
        .description = COMPOUND_ABILITY_STRING("Ignores accuracy and evasion changes.\nImmune to effects of being confused."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_WEIGHTED_GI] =
    {
        .name = _("Weighted Gi"),
        .description = COMPOUND_ABILITY_STRING("Casts off weighted clothes or fur\nwhen in a pinch boosting SPEED."),
        .aiRating = 5,
    },
    
    [ABILITY_VOLT_DASH] =
    {
        .name = _("Volt Dash"),
        .description = COMPOUND_ABILITY_STRING("Turns electricity into HP\nand gradually boosts SPEED."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_IMMUTABLE_WIND] =
    {
        .name = _("Immutable Wind"),
        .description = COMPOUND_ABILITY_STRING("Summons winds that nullify foes abilities\nand blow status moves off course."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },
    
    [ABILITY_EVERGREEN] =
    {
        .name = _("Evergreen"),
        .description = COMPOUND_ABILITY_STRING("Summons Grassy Terrain on switch-in.\nMay also Harvest a Berry."),
        .aiRating = 9,
    },
    
    [ABILITY_SHAMAN_CURE] =
    {
        .name = _("Shaman Cure"),
        .description = COMPOUND_ABILITY_STRING("Protects party from poison.\nCures own status upon switching out."),
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic
    
    [ABILITY_UNCHAINED_MELODY] =
    {
        .name = _("Unchained Melody"),
        .description = COMPOUND_ABILITY_STRING("Boosts damage of Normal moves\nand converts them to Sound type."),
        .aiRating = 7,
    },
    
    [ABILITY_ENAMEL] =
    {
        .name = _("Enamel"),
        .description = COMPOUND_ABILITY_STRING("Increased heat protection. Immune to burn."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_BONE_ARMOR] =
    {
        .name = _("Bone Armor"),
        .description = COMPOUND_ABILITY_STRING("Increased heat protection. Blocks burn.\nPrevents recoil and force switch."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_STORM_BREAK] =
    {
        .name = _("Storm Break"),
        .description = COMPOUND_ABILITY_STRING("User creates a gust of wind dissipating\nweather effects on entry."),
        .aiRating = 5,
    },
    
    [ABILITY_SPACE_CONTROL] =
    {
        .name = _("Space Control"),
        .description = COMPOUND_ABILITY_STRING("Attacks via portal, attacks are 100% Acc\nAdapted to space is immune to Ice Dmg."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_COLD_EMBRACE] =
    {
        .name = _("Cold Embrace"),
        .description = COMPOUND_ABILITY_STRING("Releases sub-zero breath when close.\nMay Freeze foe when they make contact."),
        .aiRating = 4,
    },
    
    [ABILITY_TIME_CONTROL] =
    {
        .name = _("Time Control"),
        .description = COMPOUND_ABILITY_STRING("Every two turns can distort time\nnegating charging and recharge turns."),
        .aiRating = 0,
    },
    
    [ABILITY_TORCHSOUL] =
    {
        .name = _("Torch Soul"),
        .description = COMPOUND_ABILITY_STRING("Possesses a burning inner-flame.\nGain FIRE Affinity and boosts Fire moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },
    
    [ABILITY_GRUNGE] =
    {
        .name = _("Grunge"),
        .description = COMPOUND_ABILITY_STRING("Gain POISON Affinity and boosts damage\ndone by Poison-type moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },
    
    [ABILITY_SWIFT_JUSTICE] =
    {
        .name = _("Swift Justice"),
        .description = COMPOUND_ABILITY_STRING("Stikes swiftly and decisively.\nBoosts damage if attacks before target."),
        .aiRating = 0,
    },
    
    [ABILITY_TOOLS_OF_THE_TRADE] =
    {
        .name = _("Tools of the Trade"),
        .description = COMPOUND_ABILITY_STRING("{UP_ARROW}dmg to foes switching faster or trapped\nUps DEF if statused or stat drops"),
        .aiRating = 7,
        .breakable = TRUE,
    },
    //would like this to boost pursuit dmg
    //idk if it does that
    //breaks stat buff from status not stat drop
    //pretty sure still missing some effects like reduced sleep time...
    
    [ABILITY_TROJAN_SWORD] =
    {
        .name = _("Trojan Sword"),
        .description = COMPOUND_ABILITY_STRING("Blocks Intimdiate and\nboosts slicing attacks."),
        .aiRating = 0,
    },
    
    [ABILITY_HEAT_TRANCE] =
    {
        .name = _("Heat Trance"),
        .description = COMPOUND_ABILITY_STRING("Elated by all things spicy and hot.\nHeals by burn or sun, cuts Fire Dmg taken"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_DESERT_DWELLER] =
    {
        .name = _("Desert Dweller"),
        .description = COMPOUND_ABILITY_STRING("Adapted to the extremes of the desert.\nLessens effect of Heat Cold and burn."),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_FAIRY_MIST] =
    {
        .name = _("Fairy Mist"),
        .description = COMPOUND_ABILITY_STRING("Normal and Sound moves become Fairy.\nSets Misty Terrain upon entering battle."),
        .aiRating = 0,
    },//vsonic
    
    [ABILITY_COMPASS] =
    {
        .name = _("Compass"),
        .description = COMPOUND_ABILITY_STRING("Locks-on and moves unerringly to foe.\nAll moves used by and against will land."),
        .aiRating = 8,
    },
    
    [ABILITY_HANDS_OF_FATE] =
    {
        .name = _("Hands of Fate"),
        .description = COMPOUND_ABILITY_STRING("Protected from shadowy forces and traps.\nReduces Ghost/Dark dmg and blocks status"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_DUST_DEVIL] =
    {
        .name = _("Dust Devil"),
        .description = COMPOUND_ABILITY_STRING("Immune to wind damage. Sets Sandstorm.\nUps Attack if the target of a wind effect"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_PLASMA_OVERDRIVE] =
    {
        .name = _("Plasma Overdrive"),
        .description = COMPOUND_ABILITY_STRING("Moves ignore ability affects, and draws\nin FIRE/ELEC to up Fire moves or Sp. Atk"),
        .aiRating = 0,
        .breakable = TRUE,
    },
    
    [ABILITY_CREATION_ENGINE] =
    {
        .name = _("Creation Engine"),
        .description = COMPOUND_ABILITY_STRING("Gain STAB and Immunity to Ice Fire & Elec\nWater moves targetting user become Ice."),
        .aiRating = 0,
        .breakable = TRUE,
    },//vsonic
    
    [ABILITY_DARK_CORONA] =
    {
        .name = _("Dark Corona"),
        .description = COMPOUND_ABILITY_STRING("A Tainted Crown of spikes that hurts\nand may poison when foes make contact."),
        .aiRating = 7,
    },
    
    [ABILITY_LUNAR_SOLSTICE] =
    {
        .name = _("Lunar Solstice"),
        .description = COMPOUND_ABILITY_STRING("The POKéMON celebrates the moon.\nTemporarily boosts moonlight in battle."),
        .aiRating = 9,
    },
    
    [ABILITY_LUNAR_POWER] =
    {
        .name = _("Lunar Power"),
        .description = COMPOUND_ABILITY_STRING("Powers up in strong moonlight.\nBoosts Sp. Def avoids Moon based attacks."),
        .aiRating = 3,
        .breakable = TRUE,
    },
    
    [ABILITY_NEW_MOON] =
    {
        .name = _("New Moon"),
        .description = COMPOUND_ABILITY_STRING("Moderate HP recovery in moonlight.\nAlso absorbs Moon based attacks."),
        .aiRating = 3,
        .breakable = TRUE,
    },
    
    [ABILITY_TOXIC_DELUGE] =
    {
        .name = _("Toxic Deluge"),
        .description = COMPOUND_ABILITY_STRING("Summons Acid Rain to Battle."),
        .aiRating = 9,
    },
    
    [ABILITY_RESOLUTE] =
    {
        .name = _("Resolute"),
        .description = COMPOUND_ABILITY_STRING("Changes form if suffering from status\nor if HP falls to or below half Max HP."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },
    
    [ABILITY_PIERCING_HORN] =
    {
        .name = _("Piercing Horn"),
        .description = COMPOUND_ABILITY_STRING("Boosts headbutt moves.\nAttacks foes with sharpened horns."),
        .aiRating = 5,
    },
    
    [ABILITY_X_SIGHT] =
    {
        .name = _("X Sight"),
        .description = COMPOUND_ABILITY_STRING("X-ray Vision reveals battlers held items\nand bypasses Acc check when above 50% hp."),
        .aiRating = 0,
    },//vsonic luxaray specific, may remove trace block?
    
    [ABILITY_PRECISE_STRIKE] =
    {
        .name = _("Precise Strike"),
        .description = COMPOUND_ABILITY_STRING("Powers up Critical Hits.\nDelivers attacks direct to weak points."),
        .aiRating = 3,
    },

    [ABILITY_BRAVERY] =
    {
        .name = _("Bravery"),
        .description = COMPOUND_ABILITY_STRING("Raises Sp. Attack if Intimidated\nor hit by Dark or Ghost moves."),
        .aiRating = 6,
    },

    [ABILITY_FUGUE] =
    {
        .name = _("Fugue"),
        .description = COMPOUND_ABILITY_STRING("Makes sleep and confusion more effective\nConfuse max turns sleep is more accurate"),
        .aiRating = 4,
    },
    //think change this, making sleep two consistent makes it predictible
    //and easy to immediately reset
    //change to boost acc of sleep effects
    //i.e turn hypnosis into spore for this mon only

    [ABILITY_SECRET_ARTS] =
    {
        .name = _("Secret Arts"),
        .description = COMPOUND_ABILITY_STRING("Ignores target guard mode. Contact moves\nup to 75 power also evade protection."),
        .aiRating = 5,
    },

    [ABILITY_REIKI] = 
    {
        .name = _("Reiki"),
        .description = COMPOUND_ABILITY_STRING("Prevents Flinch, Crit, and Intimidation.\nIgnores the immunities of GHOST types."),
        .aiRating = 7,
        .breakable = TRUE,
    },//inner focus + scrappy for mega mewtwo x idea
    //perfect fusion of mental and physical energy

    [ABILITY_AURORA_SHIFT] =
    {
        .name = _("Aurora Shift"),
        .description = COMPOUND_ABILITY_STRING("Sets Aurora Veil upon enter battle\nCan set once regardless of weather."),
        .aiRating = 5,
        .isSingleUse = TRUE,
    },
    //deoxys def ability will replace pressure
    //Sets aurora veil first time enters field if icy weather isn't on field
    //otherwise ste aurora veil on switch in icy weather
};

