#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

#include "global.h"

// In the Generation 3 games, Asserts were used in various debug builds.
// Ruby/Sapphire and Emerald do not have these asserts while Fire Red
// still has them in the ROM. This is because the developers forgot
// to define NDEBUG before release, however this has been changed as
// Ruby's actual debug build does not use the AGBPrint features.
#define NDEBUG

// Fire Red likely forgot to define NDEBUG/NOAGBPRN before release, leading
// to the inclusion of asserts in the retail ROM.

// Define the game version for use elsewhere
#if defined(FIRERED)
#define GAME_VERSION VERSION_FIRE_RED
#else // Default version seems to be LeafGreen
#define GAME_VERSION VERSION_LEAF_GREEN
#endif // GAME_VERSION

// rev1 renamed the source folder for reasons
#if REVISION == 0
#define CODE_ROOT "C:/WORK/POKeFRLG/src/pm_lgfr_ose/source/"
#else
#define CODE_ROOT "C:/WORK/POKeFRLG/Src/pm_lgfr_ose/source/"
#endif // REVISION

#define ABSPATH(x) (CODE_ROOT x)

// Learnset helper toggles
//#define P_LEARNSET_HELPER_TEACHABLE TRUE        // If TRUE, teachable_learnsets.h will be populated by tools/learnset_helpers/teachable.py using the included JSON files based on available TMs and tutors.

// To enable printf debugging, comment out "#define NDEBUG". This allows
// the various AGBPrint functions to be used. (See include/gba/isagbprint.h).
// See below for enabling different pretty printing versions.

#ifndef NDEBUG

#define PRETTY_PRINT_MINI_PRINTF (0)
#define PRETTY_PRINT_LIBC (1)

#define LOG_HANDLER_AGB_PRINT (0)
#define LOG_HANDLER_NOCASH_PRINT (1)
#define LOG_HANDLER_MGBA_PRINT (2)

// Use this switch to choose a handler for pretty printing.
// NOTE: mini_printf supports a custom pretty printing formatter to display preproc encoded strings. (%S)
//       some libc distributions (especially dkp arm-libc) will fail to link pretty printing.
#define PRETTY_PRINT_HANDLER (PRETTY_PRINT_MINI_PRINTF)

// Use this switch to choose a handler for printf output.
// NOTE: These will only work on the respective emulators and should not be used in a productive environment.
//       Some emulators or real hardware might (and is allowed to) crash if they are used.
//       AGB_PRINT is supported on respective debug units.

#define LOG_HANDLER (LOG_HANDLER_MGBA_PRINT)
#endif


#ifdef ENGLISH
#define UNITS_IMPERIAL
#else
#define UNITS_METRIC
#endif // ENGLISH

#define BUGFIX
#define UBFIX
#define SPECIES_NAME_EXPANSION
#define NEW_MEGA_FORMS //add data for new megas using gigantimax sprites/forms etc.

#define GEN_9 0



#define B_SNOW_WARNING FALSE

// ORAS Dowsing Machine
#define I_ORAS_DOWSING_FLAG         0           // Replace 0 with an unused flag to enable the Dowsing Machine mechanic from ORAS.
#define I_ORAS_DOWSING_SOUNDS       TRUE        // If TRUE, the Dowsing Machine will make sounds based on how far away the hidden item is.
#define I_ORAS_DOWSING_COLOR_PAL    15          // The color within the palette that will change based on proximity to the item.
// Color values for the ORAS dowsing distances/anims
#define I_ORAS_DOWSING_COLOR_NONE   RGB_GRAY
#define I_ORAS_DOWSING_COLOR_SLOW   RGB2GBA(56, 120, 255)
#define I_ORAS_DOWSING_COLOR_NORMAL RGB2GBA(24, 216, 24)
#define I_ORAS_DOWSING_COLOR_FAST   RGB2GBA(255, 255, 40)
#define I_ORAS_DOWSING_COLOR_FASTER RGB_RED

// Crashes may occur due to section reordering in the modern build,
// so we force BUGFIX here.
#if MODERN
#ifndef BUGFIX
#define BUGFIX
#endif // BUGFIX
#ifndef UBFIX
#define UBFIX
#endif // UBFIX
#endif // MODERN

#endif // GUARD_CONFIG_H
