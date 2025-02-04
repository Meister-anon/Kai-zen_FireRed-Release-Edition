#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "config.h"
#include "gba/gba.h"
#include "constants/rgb.h"
#include <string.h>
#include "constants/global.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/sound.h"
#include "option_menu.h"
#include "tm_List_data.h"
#include "field_specials.h" //this is the file I used to set dynamic starter type checks

// Prevent cross-jump optimization.
#define BLOCK_CROSS_JUMP asm("");

// to help in decompiling
#define asm_comment(x) asm volatile("@ -- " x " -- ")
#define asm_unified(x) asm(".syntax unified\n" x "\n.syntax divided")

/*#if defined (__APPLE__) || defined (__CYGWIN__) || defined(__CLION_IDE__)
// Get the IDE to stfu

// We define it this way to fool preproc.
#define INCBIN(...) {0}
#define INCBIN_U8  INCBIN
#define INCBIN_U16 INCBIN
#define INCBIN_U32 INCBIN
#define INCBIN_S8  INCBIN
#define INCBIN_S16 INCBIN
#define INCBIN_S32 INCBIN
#define _(x) (x)
#define __(x) (x)
#endif // __APPLE__

#define NELEMS(array) (sizeof(array) / sizeof((array)[0]))*/
//Old IDE stuff archived for reference

// IDE support
#if defined(__APPLE__) || defined(__CYGWIN__) || defined(__INTELLISENSE__)
// We define these when using certain IDEs to fool preproc
#define _(x)        (x)
#define __(x)       (x)
#define INCBIN(...) {0}
#define INCBIN_U8   INCBIN
#define INCBIN_U16  INCBIN
#define INCBIN_U32  INCBIN
#define INCBIN_S8   INCBIN
#define INCBIN_S16  INCBIN
#define INCBIN_S32  INCBIN
#endif // IDE support

/* Check if VA_OPT_ is supported by the compiler. GCC's version should be at least 9.5*/
#define PP_THIRD_ARG(a,b,c,...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(,),TRUE,FALSE,)
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)

#if !VA_OPT_SUPPORTED
#error ERROR: VA_OPT__ is not supported. Please update your gcc compiler to version 10 or higher
#endif // VA_OPT_SUPPORTED

#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

// Alias of ARRAY_COUNT using GameFreak's name from AgbAssert calls.
#define NELEMS(array) ARRAY_COUNT(array)

#define SWAP(a, b, temp)    \
{                           \
    temp = a;               \
    a = b;                  \
    b = temp;               \
}


// useful math macros --chaange type redef before capped most at u16 much better now u32
typedef s16 q4_12_t;
typedef u32 uq4_12_t;
//my addition
typedef u16 uq8_8_t;

#define Q_4_12_SHIFT (12)
#define UQ_4_12_SHIFT (12)

#define Q_8_8_SHIFT (8)
#define UQ_8_8_SHIFT (8)

/*From Wikipedia 
Q numbers are a ratio of two integers: the numerator is kept in storage, the denominator 

d is equal to 2n.

Consider the following example:

The Q8 denominator equals 2^8 = 256
1.5 equals 384/256

Q is signed so splits in 2 to hold the range positive and negative
UQ is unsigned Q number only holds positive so more space

The shift is used in place of multiplication and division
as its faster on most machines I think requiers a power of 2 denominator
*/

//note from Sbird on EE use of Qnumber and all the rounding
/*
We are mostly trying to replicate what the original games did.
All of the rounding at weird places is so that
we dont have off by n errors down the line. 
Yes you are losing precision that way at some places,
and thats intentional
*/
//so if I'm able to preserve the multiplier
//I would then multiply by damage and
//then divide by divisor I can keep the most accurate representation
//again necessary becasue of my change to type multipliers

//now there's an issue w overflow if I use uq_4_12 it multiplies by 4096
//doing that and multiplying by dmg  could overflow even u32
//so I think what I would want is instead to use uq_8_8
//which would be multiply by 2^8 instead of 2^12
//which is a difference of 256 compared against 4096
//which would never overflow a u32 storage type

/*I still need to store multipler within thing,
am unsure if storing actual decimal or if represents 1.
ex. uq 0.01  1 percent is it actually doing 0.01 * 4096 / 4096?
I think it is actually tracking hte decimal as the intelisense 
shows its value as 40,  is confusing as I thought division hadn't happened yet
*/

/*
    also of note from commentor on fixed point article

    "One surprise for me when I started using fixed point was
    that I had to be careful of underflow, not overflow."

    "...With fixed point, my biggest problem has been underflow.
    Multiplying 0.01 x 0.01 gives a smaller number, 0.0001.
    I've performed many mathematical operations that ended
    up with a result of all zeros, due to underflow.  
    I've found that I have to scale up my values to avoid underflow."
*/
//this is an issue because it can only be represented by doubles
//i.e 0.00
//ok I was just wrong doubles aren't limited to just 2 decimal digits
//floats can store 6-7 and doubles can store up to 15 decimal digits
//so if the fixed point stuff is storing in doubles correctly
//as I assume/think, it should have no trouble storing my entire
//multiplier not just the first 2 digits as I thought

//think I'll use UQ_8_8
//for my type effectiveness work,
//store on a u32
//potential issue is when I have to multiply,
//I don't pwant to lose the decimals
//could use float
//but if I make inline, and put in pokemon.c dmg function
//may not need to worry about that, as could get multiplier
//and use it immediately could make function dmg as an argument,
//and multiply the dmg into the multiplier,
//then use return UQ_8_8_TO_INT(dmg) to get dmg and return that

//think that could work, would just need ai stuff
//for get the multiplier look into


// Converts a number to Q8.8 fixed-point format
#define Q_8_8(n) ((s16)((n) * 256))
//my addition
#define UQ_8_8(n) ((uq8_8_t)((n) * 256))

// Converts a number to Q4.12 fixed-point format
#define Q_4_12(n)  ((q4_12_t)((n) * 4096))
#define UQ_4_12(n)  ((uq4_12_t)((n) * 4096))

// Converts a number to Q24.8 fixed-point format
#define Q_24_8(n)  ((s32)((n) << 8))

// Converts a Q8.8 fixed-point format number to a regular integer
#define Q_8_8_TO_INT(n) ((s32)((n) / 256))
//my addition
#define UQ_8_8_TO_INT(n) ((u32)((n) / 256))


// Converts a Q4.12 fixed-point format number to a regular integer
#define Q_4_12_TO_INT(n)  ((s32)((n) / 4096))
#define UQ_4_12_TO_INT(n)  ((u32)((n) / 4096))

// Converts a Q24.8 fixed-point format number to a regular integer
#define Q_24_8_TO_INT(n) ((s32)((n) >> 8))

// Rounding value for Q4.12 fixed-point format
#define Q_4_12_ROUND ((1) << (Q_4_12_SHIFT - 1))
#define UQ_4_12_ROUND ((1) << (UQ_4_12_SHIFT - 1))

//my addition - added for type multiplier refactor
//but no longer need
#define Q_8_8_ROUND ((1) << (Q_8_8_SHIFT - 1))
#define UQ_8_8_ROUND ((1) << (UQ_8_8_SHIFT - 1))

// Basic arithmetic for fixed point number formats
// Consumers should use encapsulated functions where possible

// FP API does not provide sanity checks against overflows

static inline uq4_12_t uq4_12_add(uq4_12_t a, uq4_12_t b)
{
    return a + b;
}

static inline uq4_12_t uq4_12_subtract(uq4_12_t a, uq4_12_t b)
{
    return a - b;
}

//or maybe I need this, yeah most likely this, may remove rounding,
//to keep accuracy until final step?
//believe shift is to remove the  extra multiplication of 4096
//and think what this is doing is rounding then doin the shift
//but then again I think thats a typical part of fixed point stuff? idk
//believe is functionally equivalent to the current effect, which works perfectly for my needs
//so no need to change it
static inline uq4_12_t uq4_12_multiply(uq4_12_t a, uq4_12_t b)
{
    u32 product = (u32) a * b;
    return (product + UQ_4_12_ROUND) >> UQ_4_12_SHIFT;
    //return (product) >> UQ_4_12_SHIFT;
}

//my addition
static inline uq8_8_t uq8_8_multiply(uq8_8_t a, uq8_8_t b)
{
    u32 product = (u32) a * b;
    return (product + UQ_8_8_ROUND) >> UQ_8_8_SHIFT;
}

static inline uq4_12_t uq4_12_multiply_half_down(uq4_12_t a, uq4_12_t b)
{
    u32 product = (u32) a * b;
    return (product + UQ_4_12_ROUND - 1) >> UQ_4_12_SHIFT;
}

static inline uq4_12_t uq4_12_divide(uq4_12_t dividend, uq4_12_t divisor)
{
    if (divisor == UQ_4_12(0.0)) return UQ_4_12(0);
    return (dividend << UQ_4_12_SHIFT) / divisor;
}

// Multiplies value by the UQ_4_12 number modifier.
// Returns an integer, rounded to nearest (rounding down on n.5)
//may be able to use this for type multiplier, but what I want is round to two digits i.e 2.43 
static inline u32 uq4_12_multiply_by_int_half_down(uq4_12_t modifier, u32 value)
{
    return UQ_4_12_TO_INT((modifier * value) + UQ_4_12_ROUND - 1);
}

// Multiplies value by the UQ_4_12 number modifier.
// Returns an integer, rounded to nearest (rounding up on n.5)
static inline u32 uq4_12_multiply_by_int_half_up(uq4_12_t modifier, u32 value)
{
    return UQ_4_12_TO_INT((modifier * value) + UQ_4_12_ROUND);
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b))

#if MODERN
#define abs(x) (((x) < 0) ? -(x) : (x))
#endif

// Used in cases where division by 0 can occur in the retail version.
// Avoids invalid opcodes on some emulators, and the otherwise UB.
#ifdef UBFIX
#define SAFE_DIV(a, b) ((b) ? (a) / (b) : 0)
#else
#define SAFE_DIV(a, b) ((a) / (b))
#endif

#define IS_POW_OF_TWO(n) (((n) & ((n)-1)) == 0)

// The below macro does a%n, but (to match) will switch to a&(n-1) if n is a power of 2.
// There are cases where GF does a&(n-1) where we would really like to have a%n, because
// if n is changed to a value that isn't a power of 2 then a&(n-1) is unlikely to work as
// intended, and a%n for powers of 2 isn't always optimized to use &.
//#define MOD(a, n)(((n) & ((n)-1)) ? ((a) % (n)) : ((a) & ((n)-1)))

//since I don't care about matching I can just do the intended effect
//is simple short hand can most oft be used to replace
//random() % n  not sure what point is otherwise
//ex. MOD(Random(), MAX_MON_MOVES)  but this appears longer not shorter?
#define MOD(a, n) ((a) % (n))

// There are many quirks in the source code which have overarching behavioral differences from
// a number of other files. For example, diploma.c seems to declare rodata before each use while
// other files declare out of order and must be at the beginning. There are also a number of
// macros which differ from one file to the next due to the method of obtaining the result, such
// as these below. Because of this, there is a theory (Two Team Theory) that states that these
// programming projects had more than 1 "programming team" which utilized different macros for
// each of the files that were worked on.
#define T1_READ_8(ptr)  ((ptr)[0])
#define T1_READ_16(ptr) ((ptr)[0] | ((ptr)[1] << 8))
#define T1_READ_32(ptr) ((ptr)[0] | ((ptr)[1] << 8) | ((ptr)[2] << 16) | ((ptr)[3] << 24))
#define T1_READ_PTR(ptr) (u8*) T1_READ_32(ptr)

// T2_READ_8 is a duplicate to remain consistent with each group.
#define T2_READ_8(ptr)  ((ptr)[0])
#define T2_READ_16(ptr) ((ptr)[0] + ((ptr)[1] << 8))
#define T2_READ_32(ptr) ((ptr)[0] + ((ptr)[1] << 8) + ((ptr)[2] << 16) + ((ptr)[3] << 24))
#define T2_READ_PTR(ptr) (void*) T2_READ_32(ptr)

#define HIBYTE(n) (((n) >> 8) & 0xFF)
#define LOBYTE(n) ((n) & 0xFF)
#define HIHALF(n) (((n) & 0xFFFF0000) >> 16)
#define LOHALF(n) ((n) & 0xFFFF)
// This macro is required to prevent the compiler from optimizing
// a dpad up/down check in sub_812CAD8 (fame_checker.c).
// We suspect it was used globally.
// GameFreak never ceases to amaze.
// TODO: Propagate use of this macro
#define TEST_BUTTON(field, button) ({(field) & (button);})
#define JOY_NEW(button)  TEST_BUTTON(gMain.newKeys,  button)
#define JOY_HELD(button) TEST_BUTTON(gMain.heldKeys, button)
#define JOY_HELD_RAW(button) TEST_BUTTON(gMain.heldKeysRaw, button)
#define JOY_REPT(button) TEST_BUTTON(gMain.newAndRepeatedKeys, button)

extern u8 gStringVar1[];
extern u8 gStringVar2[];
extern u8 gStringVar3[];
extern u8 gStringVar4[];

#define S16TOPOSFLOAT(val)   \
({                           \
    s16 v = (val);           \
    float f = (float)v;      \
    if(v < 0) f += 65536.0f; \
    f;                       \
})

#define DIV_ROUND_UP(val, roundBy)(((val) / (roundBy)) + (((val) % (roundBy)) ? 1 : 0))

#define ROUND_BITS_TO_BYTES(numBits)(((numBits) / 8) + (((numBits) % 8) ? 1 : 0))

#define DEX_FLAGS_NO (ROUND_BITS_TO_BYTES(NUM_SPECIES)) //num species here affects ewram believe going into saveablock
#define NUM_FLAG_BYTES (ROUND_BITS_TO_BYTES(FLAGS_COUNT)) //this also affects ewram but to a lesser degree than num_species

// Calls m0/m1/.../m8 depending on how many arguments are passed.
#define VARARG_8(m, ...) CAT(m, NARG_8(__VA_ARGS__))(__VA_ARGS__)
#define NARG_8(...) NARG_8_(_, ##__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define NARG_8_(_, a, b, c, d, e, f, g, h, N, ...) N

#define CAT(a, b) CAT_(a, b)
#define CAT_(a, b) a ## b
//logic for prete emeralds new cmd argms stuff its confusing to read so i dont like it
//changed mind adding
#define STR(a) STR_(a)
#define STR_(a) #a

// Converts a string to a compound literal, essentially making it a pointer to const u8
#define COMPOUND_STRING(str) (const u8[]) _(str) //ported to use dex entry strings from EE

//move description version
#define COMPOUND_MOVE_STRING(str) (const u8[MOVE_DESCRIPTION_LENGTH + 1]) _(str)

//replacement version so can use compound string logic w my ability stuff and keep my limiter
#define COMPOUND_ABILITY_STRING(str) (const u8[ABILITY_DESCRIPTION_LENGTH + 1]) _(str)

//same for trainer names in trainers.h before can use need check all name values for repeats, replace replace w static string
#define COMPOUND_TRAINER_NAME_STRING(str) (const u8[TRAINER_NAME_LENGTH + 1]) _(str)

/* Expands to the first/second/third/fourth argument. */
#define FIRST(a, ...) a
#define SECOND(a, ...) __VA_OPT__(FIRST(__VA_ARGS__))
#define THIRD(a, ...) __VA_OPT__(SECOND(__VA_ARGS__))
#define FOURTH(a, ...) __VA_OPT__(THIRD(__VA_ARGS__))

/* Expands to everything but the first x arguments */
#define EXCEPT_1(a, ...) __VA_OPT__(__VA_ARGS__)
#define EXCEPT_2(a, ...) __VA_OPT__(EXCEPT_1(__VA_ARGS__))
#define EXCEPT_3(a, ...) __VA_OPT__(EXCEPT_2(__VA_ARGS__))
#define EXCEPT_4(a, ...) __VA_OPT__(EXCEPT_3(__VA_ARGS__))

/* 'UNPACK (x, y, z)' expands to 'x, y, z'.
 * Useful for passing arguments which may contain commas into a macro. */
#define UNPACK(...) __VA_ARGS__

/* Expands to 'macro(...args, ...)'. */
#define INVOKE_WITH(macro, args, ...) INVOKE_WITH_(macro, UNPACK args __VA_OPT__(, __VA_ARGS__))
#define INVOKE_WITH_(macro, ...) macro(__VA_ARGS__)

/* Recursive macros.
 * Based on https://www.scs.stanford.edu/~dm/blog/va-opt.html
 *
 * Macros prefixed with R_ are recursive, to correctly expand them the
 * top-level macro which references them should use 'RECURSIVELY' around
 * them. 'RECURSIVELY' cannot be nested, hence the top-level macro must
 * use it so that a recursive macro is able to reference another
 * recursive macro. */

#define RECURSIVELY(...) RECURSIVELY_4(RECURSIVELY_4(RECURSIVELY_4(RECURSIVELY_4(__VA_ARGS__))))
#define RECURSIVELY_4(...) RECURSIVELY_3(RECURSIVELY_3(RECURSIVELY_3(RECURSIVELY_3(__VA_ARGS__))))
#define RECURSIVELY_3(...) RECURSIVELY_2(RECURSIVELY_2(RECURSIVELY_2(RECURSIVELY_2(__VA_ARGS__))))
#define RECURSIVELY_2(...) RECURSIVELY_1(RECURSIVELY_1(RECURSIVELY_1(RECURSIVELY_1(__VA_ARGS__))))
#define RECURSIVELY_1(...) __VA_ARGS__

/* Useful for deferring expansion until the second scan. See
 * https://www.scs.stanford.edu/~dm/blog/va-opt.html for more info. */
#define PARENS ()

/* Expands to 'macro(a)' for each 'a' in '...' */
#define R_FOR_EACH(macro, ...) __VA_OPT__(R_FOR_EACH_(macro, __VA_ARGS__))
#define R_FOR_EACH_(macro, a, ...) macro(a) __VA_OPT__(R_FOR_EACH_P PARENS (macro, __VA_ARGS__))
#define R_FOR_EACH_P() R_FOR_EACH_

/* Expands to 'macro(...args, a)' for each 'a' in '...'. */
#define R_FOR_EACH_WITH(macro, args, ...) __VA_OPT__(R_FOR_EACH_WITH_(macro, args, __VA_ARGS__))
#define R_FOR_EACH_WITH_(macro, args, a, ...) INVOKE_WITH(macro, args, a) __VA_OPT__(R_FOR_EACH_WITH_P PARENS (macro, args, __VA_ARGS__))
#define R_FOR_EACH_WITH_P() R_FOR_EACH_WITH_

/* Picks the xth VA_ARG if it exists, otherwise returns a default value */
#define DEFAULT(_default, ...) FIRST(__VA_OPT__(__VA_ARGS__, ) _default)
#define DEFAULT_2(_default, ...) DEFAULT(_default __VA_OPT__(, SECOND(__VA_ARGS__)))
#define DEFAULT_3(_default, ...) DEFAULT(_default __VA_OPT__(, THIRD(__VA_ARGS__)))
#define DEFAULT_4(_default, ...) DEFAULT(_default __VA_OPT__(, FOURTH(__VA_ARGS__)))


/* (Credit to MGriffin) A rather monstrous way of finding the set bit in a word.
Invalid input causes a compiler error. Sample: https://cexplore.karathan.at/z/x1hm7B */
#define BIT_INDEX(n) \
    (n) == (1 << 0) ? 0 : \
    (n) == (1 << 1) ? 1 : \
    (n) == (1 << 2) ? 2 : \
    (n) == (1 << 3) ? 3 : \
    (n) == (1 << 4) ? 4 : \
    (n) == (1 << 5) ? 5 : \
    (n) == (1 << 6) ? 6 : \
    (n) == (1 << 7) ? 7 : \
    (n) == (1 << 8) ? 8 : \
    (n) == (1 << 9) ? 9 : \
    (n) == (1 << 10) ? 10 : \
    (n) == (1 << 11) ? 11 : \
    (n) == (1 << 12) ? 12 : \
    (n) == (1 << 13) ? 13 : \
    (n) == (1 << 14) ? 14 : \
    (n) == (1 << 15) ? 15 : \
    (n) == (1 << 16) ? 16 : \
    (n) == (1 << 17) ? 17 : \
    (n) == (1 << 18) ? 18 : \
    (n) == (1 << 19) ? 19 : \
    (n) == (1 << 20) ? 20 : \
    (n) == (1 << 21) ? 21 : \
    (n) == (1 << 22) ? 22 : \
    (n) == (1 << 23) ? 23 : \
    (n) == (1 << 24) ? 24 : \
    (n) == (1 << 25) ? 25 : \
    (n) == (1 << 26) ? 26 : \
    (n) == (1 << 27) ? 27 : \
    (n) == (1 << 28) ? 28 : \
    (n) == (1 << 29) ? 29 : \
    (n) == (1 << 30) ? 30 : \
    (n) == (1 << 31) ? 31 : \
    *(u32 *)NULL

#define COMPRESS_BITS_0 0, 1
#define COMPRESS_BITS_1 1, 1
#define COMPRESS_BITS_2 2, 1
#define COMPRESS_BITS_3 3, 1
#define COMPRESS_BITS_4 4, 1
#define COMPRESS_BITS_5 5, 1
#define COMPRESS_BITS_6 6, 1
#define COMPRESS_BITS_7 7, 1

/* Will try and compress a set bit (or up to three sequential bits) into a single byte
Input must be of the form (upper << lower) where upper can be up to 3, lower up to 31 */
#define COMPRESS_BITS(_val) COMPRESS_BITS_STEP_2 _val
#define COMPRESS_BITS_STEP_2(_unpacked) COMPRESS_BITS_STEP_3(COMPRESS_BITS_## _unpacked)
#define COMPRESS_BITS_STEP_3(...) COMPRESS_BITS_STEP_4(__VA_ARGS__)
#define COMPRESS_BITS_STEP_4(upper, lower) (((upper % 8) << 5) + (BIT_INDEX(lower)))

/* Will read a compressed bit stored by COMPRESS_BIT into a single byte */
#define UNCOMPRESS_BITS(compressed) ((compressed >> 5) << (compressed & 0x1F))


/*#define CAP_ABILITY_STRING(str) _("{ABILITY_CAP}"str"{END_CAP}") //should hopefully set code for cap into string
//WORKS!

//default is length + 1 for string terminator
//addition of ext codes added 5 to length?
//ok for some reason it works with +5 now?
//if understand right its +5 because the ext codes are 2 bytes and the +1 from string end
#define CAP_SPECIES_STRING(str) _("{SPECIES_CAP}"str"{END_CAP}") 

#define CAP_MOVE_STRING(str) _("{MOVE_CAP}"str"{END_CAP}") 

#define CAP_ITEM_STRING(str) _("{ITEM_CAP}"str"{END_CAP}") 

#define CAP_CHARACTER_BUFF_STRING(str) _("{CHARACTER_NAME_CAP}"str"{END_CAP}") 


//will most likely never use
#define CAP_COMPOUND_STRING(str) (const u8[]) _("{CAPS}"str"{END_CAP}")
//for individual words can buffer to stringvar and use that idk

*/
// This produces an error at compile-time if expr is zero.
// It looks like file.c:line: size of array `id' is negative
#define STATIC_ASSERT(expr, id) typedef char id[(expr) ? 1 : -1];

struct Coords8
{
    s8 x;
    s8 y;
};

struct UCoords8
{
    u8 x;
    u8 y;
};

struct Coords16
{
    s16 x;
    s16 y;
};

struct UCoords16
{
    u16 x;
    u16 y;
};

struct Coords32
{
    s32 x;
    s32 y;
};

struct UCoords32
{
    u32 x;
    u32 y;
};

//in case I need to hardcode tm/hm for speed in tm case disc loop
//used for GetTMHMNumberandCategory
typedef enum
{
    NEITHER,
    TM_MOVE,
    HM_MOVE

}MoveCat;

#define GROUPED_SPECIES_ENUMS
typedef enum
{
    UNFEZANT,       //PERCENT_FEMALE(50)
    PYROAR,         //PERCENT_FEMALE(87.5)
    MEOWSTIC,       //PERCENT_FEMALE(50)
    INDEEDEE,       //PERCENT_FEMALE(50)
    BASCULEGION,    //PERCENT_FEMALE(50)
    OINKOLOGNE,     //PERCENT_FEMALE(50)
    FRILLISH,       //PERCENT_FEMALE(50)
    JELLICENT,      //PERCENT_FEMALE(50)
}GenderForms;

typedef enum
{
    EARLY_ROUTE_BIRDS,
    ALCREMIE_FORMS,
    VIVILLION_FORMS,
}SpeciesGroups;

typedef enum
{
    EARLY_ROUTE_BIRDS_END = 2,
    ALCREMIE_FORMS_END = 63,
    VIVILLION_FORMS_END = 20,
}SpeciesGroupsTerminators; //use size of array

/*global enums meant for
new mon generation logic,
to allow splitting a single species
for json between multiple values

Matches to global arrays in grouped_species_tables.h*/


struct Time //want month seasons potentialy add here
{
    /*0x00*/ s16 days;
    /*0x02*/ s8 hours;
    /*0x03*/ s8 minutes;
    /*0x04*/ s8 seconds;
};//month logic already included/in port in rtc file

struct Pokedex
{
    /*0x00*/ u8 order;
    /*0x01*/ u8 mode;
    /*0x02*/ //u8 unusedRS; // must equal 0xDA in order to have National mode
    /*0x03*/ u8 nationalMagic; // set to 0xB9 when national dex is first enabled
    /*0x04*/ u32 unownPersonality; // set when you first see Unown
    /*0x08*/ u32 spindaPersonality; // set when you first see Spinda
    /*0x0C*/ //u32 unknown3;
    /*0x10*/ u8 owned[DEX_FLAGS_NO];
    /*0x44*/ u8 seen[DEX_FLAGS_NO];
};//removed 2 portions for save block space

/*struct PokemonJumpResults // possibly used in the game itself?
{
    u16 jumpsInRow;
    u16 field2;
    u16 excellentsInRow;
    u16 field6;
    u32 field8;
    u32 bestJumpScore;
};

struct BerryPickingResults // possibly used in the game itself? Size may be wrong as well
{
    u32 bestScore;
    u16 berriesPicked;
    u16 berriesPickedInRow;
    u8 field_8;
    u8 field_9;
    u8 field_A;
    u8 field_B;
    u8 field_C;
    u8 field_D;
    u8 field_E;
    u8 field_F;
};

struct BerryCrush
{
    u16 berryCrushResults[4];
    u32 berryPowderAmount;
    u32 unk;
};*/

#define PLAYER_NAME_LENGTH   7
/*
#define LINK_B_RECORDS_COUNT 5

struct LinkBattleRecord
{
    u8 name[PLAYER_NAME_LENGTH + 1];
    u16 trainerId;
    u16 wins;
    u16 losses;
    u16 draws;
};

struct LinkBattleRecords
{
    struct LinkBattleRecord entries[LINK_B_RECORDS_COUNT];
    u8 languages[LINK_B_RECORDS_COUNT];
};
*/
#include "constants/game_stat.h"
#include "global.fieldmap.h"
#include "global.berry.h"
#include "pokemon.h"

struct BattleTowerRecord // record mixing
{
    /*0x00*/ u8 battleTowerLevelType; // 0 = level 50, 1 = level 100
    /*0x01*/ u8 trainerClass;
    /*0x02*/ u16 winStreak;
    /*0x04*/ u8 name[OT_NAME_LENGTH + 1];
    /*0x0C*/ u8 trainerId[4];
    /*0x10*/ u16 greeting[6];
    /*0x1C*/ struct BattleTowerPokemon party[3];
    /*0xA0*/ u32 checksum;
};

struct BattleTowerEReaderTrainer
{
    /*0x4A0 0x3F0 0x00*/ u8 unk0;
    /*0x4A1 0x3F1 0x01*/ u8 trainerClass;
    /*0x4A2 0x3F2 0x02*/ u16 winStreak;
    /*0x4A4 0x3F4 0x04*/ u8 name[OT_NAME_LENGTH + 1];
    /*0x4AC 0x3FC 0x0C*/ u8 trainerId[4];
    /*0x4B0 0x400 0x10*/ u16 greeting[6];
    /*0x4BC 0x40C 0x1C*/ u16 farewellPlayerLost[6];
    /*0x4C8 0x418 0x28*/ u16 farewellPlayerWon[6];
    /*0x4D4 0x424 0x34*/ struct BattleTowerPokemon party[3];
    /*0x558 0x4A8 0xB8*/ u32 checksum;
};

struct BattleTowerData // Leftover from R/S
{
    /*0x0000, 0x00B0*/ struct BattleTowerRecord playerRecord;
    /*0x00A4, 0x0154*/ struct BattleTowerRecord records[5]; // from record mixing
    /*0x03D8, 0x0488*/ u16 firstMonSpecies; // species of the first pokemon in the player's battle tower party
    /*0x03DA, 0x048A*/ u16 defeatedBySpecies; // species of the pokemon that defated the player
    /*0x03DC, 0x048C*/ u8 defeatedByTrainerName[OT_NAME_LENGTH + 1];
    /*0x03E4, 0x0494*/ u8 firstMonNickname[POKEMON_NAME_LENGTH]; // nickname of the first pokemon in the player's battle tower party
    /*0x03F0, 0x04A0*/ struct BattleTowerEReaderTrainer ereaderTrainer;
    /*0x04AC, 0x055C*/ u8 battleTowerLevelType:1; // 0 = level 50; 1 = level 100
    /*0x04AC, 0x055C*/ u8 unk_554:1;
    /*0x04AD, 0x055D*/ u8 battleOutcome;
    /*0x04AE, 0x055E*/ u8 var_4AE[2];
    /*0x04B0, 0x0560*/ u16 curChallengeBattleNum[2]; // 1-based index of battle in the current challenge. (challenges consist of 7 battles)
    /*0x04B4, 0x0564*/ u16 curStreakChallengesNum[2]; // 1-based index of the current challenge in the current streak.
    /*0x04B8, 0x0568*/ u16 recordWinStreaks[2];
    /*0x04BC, 0x056C*/ u8 battleTowerTrainerId; // index for gBattleTowerTrainers table
    /*0x04BD, 0x056D*/ u8 selectedPartyMons[0x3]; // indices of the 3 selected player party mons.
    /*0x04C0, 0x0570*/ u16 prizeItem;
    /*0x04C2, 0x0572*/ u8 battledTrainerIds[6];
    /*0x04C8, 0x0578*/ u16 totalBattleTowerWins;
    /*0x04CA, 0x057A*/ u16 bestBattleTowerWinStreak;
    /*0x04CC, 0x057C*/ u16 currentWinStreaks[2];
    /*0x04D0, 0x0580*/ u8 lastStreakLevelType; // 0 = level 50, 1 = level 100.  level type of the last streak. Used by tv to report the level mode.
    /*0x04D1, 0x0581*/ u8 filler_4D1[0x317];
}; /* size = 0x7E8 */

//u16 values need to be no even bytes or they add extra padding
//C rule learned from Mggriffin
struct SaveBlock2
{
    /*0x000*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x008*/ u8 playerGender; // MALE, FEMALE
    /*0x009*/ u8 specialSaveWarpFlags;
    /*0x00A*/ u8 playerTrainerId[4];
    /*0x00E*/ u16 playTimeHours;
    /*0x010*/ u8 playTimeMinutes;
    /*0x011*/ u8 playTimeSeconds;
    /*0x012*/ u8 playTimeVBlanks;
    /*0x013*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x014*/ u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
              u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
    /*0x15*/  u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
              u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
              u16 optionsBattleSceneOff:1; // whether battle animations are disabled
              u16 regionMapZoom:1; // whether the map is zoomed in - u16 speread bit field over 2 bytes 3 5 = 8,then 4 1s
              u16 optionsBattleSpeed:2; //for pokabbie setup navie battle speed up should be 4 options for 1-4x
              u16 optionsEventSpeedup:1;
              u16 optionsNuzlockeMode:1;
              u16 NewPlaceholder:15;
              u16 optionsDisplayTypeEffect:1;
    /*0x018*/ struct Pokedex pokedex; //may need new size value fo rthis?
    /*0x090*/ u8 filler_90[0x6];
    /*0x098*/ struct Time localTimeOffset;
    /*0x0A0*/ struct Time lastBerryTreeUpdate;
    /*0x0A8*/ //u32 gcnLinkFlags; // Read by Pokemon Colosseum/XD - not needed, plus needed space for mon data
    /*0x0AC*/ u8 field_AC;
    /*0x0AD*/ u8 field_AD;
    /*0x0B0*/ struct BattleTowerData battleTower;
    /*0x898*/ u16 mapView[0x100];
    /*0xA98*/ //struct LinkBattleRecords linkBattleRecords;
    /*0xAF0*/ //struct BerryCrush berryCrush;
    /*0xB00*/ //struct PokemonJumpResults pokeJump;
    /*0xB10*/ //struct BerryPickingResults berryPick;
    /*0xB20*/ u8 filler_B20[0x400];
    /*0xF20*/ u32 encryptionKey;
}; // size: 0xF24

extern struct SaveBlock2 *gSaveBlock2Ptr;

struct SecretBaseParty
{
    u32 personality[PARTY_SIZE];
    u16 moves[PARTY_SIZE * 4];
    u16 species[PARTY_SIZE];
    u16 heldItems[PARTY_SIZE];
    u8 levels[PARTY_SIZE];
    u16 evs[PARTY_SIZE];
};

struct SecretBaseRecord
{
    /*0x1A9C*/ u8 secretBaseId;
    /*0x1A9D*/ u8 sbr_field_1_0:4;
    /*0x1A9D*/ u8 gender:1;
    /*0x1A9D*/ u8 sbr_field_1_5:1;
    /*0x1A9D*/ u8 sbr_field_1_6:2;
    /*0x1A9E*/ u8 trainerName[PLAYER_NAME_LENGTH];
    /*0x1AA5*/ u8 trainerId[4]; // byte 0 is used for determining trainer class
    /*0x1AA9*/ u8 language;
    /*0x1AAA*/ u16 sbr_field_e;
    /*0x1AAC*/ u8 sbr_field_10;
    /*0x1AAD*/ u8 sbr_field_11;
    /*0x1AAE*/ u8 decorations[16];
    /*0x1ABE*/ u8 decorationPos[16];
    /*0x1AD0*/ struct SecretBaseParty party;
};

struct WarpData
{
    s8 mapGroup;
    s8 mapNum;
    s8 warpId;
    s16 x, y;
};

struct ItemSlot
{
    u16 itemId;
    u16 quantity;
};

struct Pokeblock
{
    u8 color;
    u8 spicy;
    u8 dry;
    u8 sweet;
    u8 bitter;
    u8 sour;
    u8 feel;
};

struct Roamer
{
    /*0x00*/ u32 ivs;
    /*0x04*/ u32 personality;
    /*0x08*/ u16 species;
    /*0x0A*/ u16 hp;
    /*0x0C*/ u8 level;
    /*0x0D*/ u8 status;
    /*0x0E*/ u8 cool;
    /*0x0F*/ u8 beauty;
    /*0x10*/ u8 cute;
    /*0x11*/ u8 smart;
    /*0x12*/ u8 tough;
    /*0x13*/ bool8 active;
    /*0x14*/ u8 filler[0x8];
};

struct RivalParty
{
    /*0x00*/ u32 ivs;
    /*0x04*/ u32 personality;
    /*0x08*/ u16 species;
    /*0x0A*/ u16 hp;
    /*0x0C*/ u8 level;
    /*0x0D*/ u8 status;
    /*0x0E*/ u8 cool;
    /*0x0F*/ u8 beauty;
    /*0x10*/ u8 cute;
    /*0x11*/ u8 smart;
    /*0x12*/ u8 tough;
    /*0x13*/ bool8 active;
    /*0x14*/ u8 filler[0x8];
};//value I added to eventually store rival party data so is consistant all game

struct RamScriptData
{
    u8 magic;
    u8 mapGroup;
    u8 mapNum;
    u8 objectId;
    u8 script[995];
};

struct RamScript
{
    u32 checksum;
    struct RamScriptData data;
};

/*struct EasyChatPair
{
    u16 unk0_0:7;
    u16 unk0_7:7;
    u16 unk1_6:1;
    u16 unk2;
    u16 words[2];
};*/ /*size = 0x8*/

struct MailStruct
{
    /*0x00*/ u16 words[9];
    /*0x12*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x1A*/ u8 trainerId[4];
    /*0x1E*/ u16 species;
    /*0x20*/ u16 itemId;
};


//struct MauvilleManBard
//{
 //   /*0x00*/ u8 id;
//    /*0x02*/ u16 songLyrics[BARD_SONG_LENGTH];
 //   /*0x0E*/ u16 temporaryLyrics[BARD_SONG_LENGTH];
 //   /*0x1A*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
 //   /*0x22*/ u8 filler_2DB6[0x3];
 //   /*0x25*/ u8 playerTrainerId[TRAINER_ID_LENGTH];
//    /*0x29*/ bool8 hasChangedSong;
//    /*0x2A*/ u8 language;
//}; /*size = 0x2C*/

//struct MauvilleManGiddy
//{
//    /*0x00*/ u8 id;
//    /*0x01*/ u8 taleCounter;
//    /*0x02*/ u8 questionNum;
//    /*0x04*/ u16 randomWords[10];
//    /*0x18*/ u8 questionList[8];
//    /*0x20*/ u8 language;
//}; /*size = 0x2C*/


/*struct MauvilleManCommon
{
    u8 id;
};

struct MauvilleManStoryteller
{
    u8 id;
    bool8 alreadyRecorded;
    u8 filler2[2];
    u8 gameStatIDs[NUM_STORYTELLER_TALES];
    u8 trainerNames[NUM_STORYTELLER_TALES][PLAYER_NAME_LENGTH];
    u8 statValues[NUM_STORYTELLER_TALES][4];
    u8 language[NUM_STORYTELLER_TALES];
};



struct MauvilleManHipster
{
    u8 id;
    bool8 alreadySpoken;
    u8 language;
};

struct MauvilleOldManTrader
{
    u8 id;
    u8 decorIds[NUM_TRADER_ITEMS];
    u8 playerNames[NUM_TRADER_ITEMS][11];
    u8 alreadyTraded;
    u8 language[NUM_TRADER_ITEMS];
};

typedef union OldMan
{
    struct MauvilleManCommon common;
    struct MauvilleManBard bard;
    struct MauvilleManGiddy giddy;
    struct MauvilleManHipster hipster;
    struct MauvilleOldManTrader trader;
    struct MauvilleManStoryteller storyteller;
    u8 filler[0x40];
} OldMan;
*/

struct RecordMixing_UnknownStructSub
{
    u32 unk0;
    u8 data[0x34];
    //u8 data[0x38];
};

struct RecordMixing_UnknownStruct
{
    struct RecordMixing_UnknownStructSub data[2];
    u32 unk70;
    u16 unk74[0x2];
};

struct RecordMixingGiftData
{
    u8 unk0;
    u8 quantity;
    u16 itemId;
    u8 filler4[8];
};

struct RecordMixingGift
{
    int checksum;
    struct RecordMixingGiftData data;
};

struct ContestWinner
{
    u32 personality;
    u32 trainerId;
    u16 species;
    u8 contestCategory;
    u8 monName[POKEMON_NAME_LENGTH + 1];
    u8 trainerName[OT_NAME_LENGTH + 1];
    u8 contestRank;
};

/*struct DayCareMail
{
    struct MailStruct message;
    u8 OT_name[OT_NAME_LENGTH + 1];
    u8 monName[POKEMON_NAME_LENGTH + 1];
    u8 gameLanguage:4;
    u8 monLanguage:4;
};*/

struct DaycareMon
{
    struct BoxPokemon mon;
    //struct DayCareMail mail; //dont have mail so can remove this as well
    u32 steps;
};//this steps is exp gain, but uses daycaremon value in other struct for assigning count to mon

#define DAYCARE_MON_COUNT   2 //plan to raise, / or not

//stepcounter is used for duration of egg cycle, how many steps until lower egg cycle
//
struct DayCare
{
    struct DaycareMon route5_daycareMon[DAYCARE_MON_COUNT];//since ruote 5 daycare seems to hvae its own daycaremon steps, think can use this in place of saveblock route5
    struct DaycareMon mons[DAYCARE_MON_COUNT];
    u16 offspringPersonality;
    u16 route5_offspringPersonality;
    u8 eggTimer; //times egg generation, i.e used w compat to set how long till generate an egg
    u8 route5_eggTimer;
    u8 eggCount;
    u8 boost; //created value to increase compatibility and speed egg production
    u8 stepCounter; //if I add more mon would require a separate step counter for each pairing...or not since it alraedy works based on individual mon?
}; //this isn't exp gain its for egg hatching/eggs //actually think thats based on daycaremon steps value, not this stepcounter
//I'm going to keep the daycare mon count the same,
//what I'll do instead is change save struct value/add another one
//so the route 5 day care can hold 2 mons and do egg breeding too,
//but the 4 island care will still be special as you'll
//have more access to items by then,
//and think can also make the special service 
//for speeding up breeding exclusive to the old couple
//will make a special service, rather than an item,
//and will be an addition to the text the old woman says

/*struct RecordMixingDayCareMail
{
    struct DayCareMail mail[DAYCARE_MON_COUNT];
    u32 numDaycareMons;
    bool16 holdsItem[DAYCARE_MON_COUNT];
};*/ //can remove

struct MENewsJisanStruct
{
    u8 unk_0_0:2;
    u8 unk_0_2:3;
    u8 unk_0_5:3;
    u8 berry;
};

struct QuestLogNPCData
{
    u32 x:8;
    u32 negx:1;
    u32 y:8;
    u32 negy:1;
    u32 elevation:6;
    u32 movementType:8;
};

#define BERRY_TREES_COUNT  128
#define MAIL_COUNT         (PARTY_SIZE + 10)
#define PC_MAIL_NUM(i)     (PARTY_SIZE + (i))

struct QuestLogObjectEvent
{
    /*0x00*/ u8 active:1;
    /*0x00*/ u8 triggerGroundEffectsOnStop:1;
    /*0x00*/ u8 disableCoveringGroundEffects:1;
    /*0x00*/ u8 landingJump:1;
    /*0x00*/ u8 frozen:1;
    /*0x00*/ u8 facingDirectionLocked:1;
    /*0x00*/ u8 disableAnim:1;
    /*0x00*/ u8 enableAnim:1;
    /*0x01*/ u8 inanimate:1;
    /*0x01*/ u8 invisible:1;
    /*0x01*/ u8 offScreen:1;
    /*0x01*/ u8 trackedByCamera:1;
    /*0x01*/ u8 isPlayer:1;
    /*0x01*/ u8 spriteAnimPausedBackup:1;
    /*0x01*/ u8 spriteAffineAnimPausedBackup:1;
    /*0x01*/ u8 disableJumpLandingGroundEffect:1;
    /*0x02*/ u8 fixedPriority:1;
    /*0x02*/ u8 mapobj_unk_18:4;
    /*0x02*/ u8 unused_02_5:3;
    /*0x03*/ u8 mapobj_unk_0B_0:4;
    /*0x03*/ u8 elevation:4;
    /*0x04*/ u8 graphicsId;
    /*0x05*/ u8 animPattern;
    /*0x06*/ u8 trainerType;
    /*0x07*/ u8 localId;
    /*0x08*/ u8 mapNum;
    /*0x09*/ u8 mapGroup;
    /*0x0a*/ s16 x;
    /*0x0c*/ s16 y;
    /*0x0e*/ u8 trainerRange_berryTreeId;
    /*0x0f*/ u8 previousMetatileBehavior;
    /*0x10*/ u8 directionSequenceIndex;
    /*0x11*/ u8 animId;
};

struct QuestLog
{
    /*0x0000*/ u8 startType;
    /*0x0001*/ u8 mapGroup;
    /*0x0002*/ u8 mapNum;
    /*0x0003*/ u8 warpId;
    /*0x0004*/ s16 x;
    /*0x0006*/ s16 y;
    /*0x0008*/ struct QuestLogObjectEvent unk_008[OBJECT_EVENTS_COUNT];

    // These arrays hold the game state for
    // playing back the quest log
    /*0x0148*/ u8 flags[NUM_FLAG_BYTES];
    /*0x02c8*/ u16 vars[VARS_COUNT];
    /*0x0468*/ struct QuestLogNPCData npcData[64];
    /*0x0568*/ u16 script[128];
    /*0x0668*/ u16 end[0];
};

#include "fame_checker.h"

struct FameCheckerSaveData
{
    /*3a54*/ u16 pickState:2;
    u16 flavorTextFlags:12;
    u16 unk_0_E:2;
};

#define NUM_EASY_CHAT_EXTRA_PHRASES 33
#define EASY_CHAT_EXTRA_PHRASES_SIZE ((NUM_EASY_CHAT_EXTRA_PHRASES >> 3) + (NUM_EASY_CHAT_EXTRA_PHRASES % 8 ? 1 : 0))

struct MEWonderNewsData
{
    u16 newsId;
    u8 shareState;
    u8 unk_03;
    u8 unk_04[40];
    u8 unk_2C[10][40];
};

struct MEWonderNewsStruct
{
    u32 crc;
    struct MEWonderNewsData data;
};

struct MEWonderCardData
{
    u16 cardId;
    u16 unk_02;
    u32 unk_04;
    u8 unk_08_0:2;
    u8 unk_08_2:4;
    u8 shareState:2;
    u8 recvMonCapacity;
    u8 unk_0A[40];
    u8 unk_32[40];
    u8 unk_5A[4][40];
    u8 unk_FA[40];
    u8 unk_122[40];
};

struct MEWonderCardStruct
{
    u32 crc;
    struct MEWonderCardData data;
};

struct MEventBuffer_3430_Sub
{
    u16 linkWins;
    u16 linkLosses;
    u16 linkTrades;
    u16 unk_06;
    u16 distributedMons[2][7]; // [0][x] = species
                               // [1][x] = ???
};

struct MEventBuffer_3430
{
    u32 crc;
    struct MEventBuffer_3430_Sub data;
};

struct MEventBuffers
{
    /*0x000 0x3120*/ struct MEWonderNewsStruct menews;
    /*0x1c0 0x32e0*/ struct MEWonderCardStruct mecard;
    /*0x310 0x3430*/ struct MEventBuffer_3430 buffer_310;
    /*0x338 0x3458*/ u16 ec_profile_maybe[4];
    /*0x340 0x3460*/ struct MENewsJisanStruct me_jisan;
    /*0x344 0x3464*/ u32 unk_344[2][5];
}; // 0x36C 0x348C

struct TrainerTower
{
    u32 timer;
    u32 bestTime;
    u8 floorsCleared;
    u8 unk9;
    bool8 receivedPrize:1;
    bool8 checkedFinalTime:1;
    bool8 spokeToOwner:1;
    bool8 hasLost:1;
    bool8 unkA_4:1;
    bool8 validated:1;
};

struct TrainerRematchState //since not using vs seeker, can repurpose this or remove plan for pc exp gain since need counter
{
    u16 stepCounter;
    u8 rematches[100];
};


struct TrainerNameRecord
{
    u32 trainerId;
    u8 trainerName[OT_NAME_LENGTH + 1];
};//assume needed for questlog

// For external event data storage. The majority of these may have never been used.
// In FRLG, the only known used fields are the PokeCoupon and BoxRS ones, but hacking the distribution discs allows FRLG to receive events and set the others
struct ExternalEventData
{
    u8 unknownExternalDataFields1[7]; // if actually used, may be broken up into different fields.
    u32 unknownExternalDataFields2:8;
    u32 currentPokeCoupons:24; // PokéCoupons stored by Pokémon Colosseum and XD from Mt. Battle runs. Earned PokéCoupons are also added to totalEarnedPokeCoupons. Colosseum/XD caps this at 9,999,999, but will read up to 16,777,215.
    u32 gotGoldPokeCouponTitleReward:1; // Master Ball from Jp Colosseum Bonus Disc; for reaching 30,000 totalEarnedPokeCoupons
    u32 gotSilverPokeCouponTitleReward:1; // Light Ball Pikachu from JP Colosseum Bonus Disc; for reaching 5000 totalEarnedPokeCoupons
    u32 gotBronzePokeCouponTitleReward:1; // PP Max from JP Colosseum Bonus Disc; for reaching 2500 totalEarnedPokeCoupons
    u32 receivedAgetoCelebi:1; // from JP Colosseum Bonus Disc
    u32 unknownExternalDataFields3:4;
    u32 totalEarnedPokeCoupons:24; // Used by the JP Colosseum bonus disc. Determines PokéCoupon rank to distribute rewards. Unread in International games. Colosseum/XD caps this at 9,999,999.
    u8 unknownExternalDataFields4[5]; // if actually used, may be broken up into different fields.
} __attribute__((packed)); /*size = 0x14*/

// For external event flags. The majority of these may have never been used.
// In FRLG, Jirachi cannot normally be received, but hacking the distribution discs allows FRLG to receive Jirachi and set the flag
struct ExternalEventFlags
{
    u8 usedBoxRS:1; // Set by Pokémon Box: Ruby & Sapphire; denotes whether this save has connected to it and triggered the free False Swipe Swablu Egg giveaway.
    u8 boxRSEggsUnlocked:2; // Set by Pokémon Box: Ruby & Sapphire; denotes the number of Eggs unlocked from deposits; 1 for ExtremeSpeed Zigzagoon (at 100 deposited), 2 for Pay Day Skitty (at 500 deposited), 3 for Surf Pichu (at 1499 deposited)
    u8 padding:5;
    u8 unknownFlag1;
    u8 receivedGCNJirachi; // Both the US Colosseum Bonus Disc and PAL/AUS Pokémon Channel use this field. One cannot receive a WISHMKR Jirachi and CHANNEL Jirachi with the same savefile.
    u8 unknownFlag3;
    u8 unknownFlag4;
    u8 unknownFlag5;
    u8 unknownFlag6;
    u8 unknownFlag7;
    u8 unknownFlag8;
    u8 unknownFlag9;
    u8 unknownFlag10;
    u8 unknownFlag11;
    u8 unknownFlag12;
    u8 unknownFlag13;
    u8 unknownFlag14;
    u8 unknownFlag15;
    u8 unknownFlag16;
    u8 unknownFlag17;
    u8 unknownFlag18;
    u8 unknownFlag19;
    u8 unknownFlag20;

} __attribute__((packed));/*size = 0x15*/

#define UNION_ROOM_KB_ROW_COUNT 10 //find out what this is?

struct SaveBlock1
{
    /*0x0000*/ struct Coords16 pos;
    /*0x0004*/ struct WarpData location;
    /*0x000C*/ struct WarpData continueGameWarp;
    /*0x0014*/ struct WarpData dynamicWarp;
    /*0x001C*/ struct WarpData lastHealLocation;
    /*0x0024*/ struct WarpData escapeWarp;
    /*0x002C*/ u16 savedMusic;
    /*0x002E*/ u8 weather;
    /*0x002F*/ u8 weatherCycleStage;
    /*0x0030*/ u8 flashLevel;
    /*0x0032*/ u16 mapLayoutId;
    /*0x0034*/ u8 playerPartyCount;
    /*0x0038*/ struct Pokemon playerParty[PARTY_SIZE];
    /*0x0290*/ u32 money;
    /*0x0294*/ u16 coins;
    /*0x0296*/ u16 registeredItem; // registered for use with SELECT button
    /*0x0298*/ struct ItemSlot pcItems[PC_ITEMS_COUNT];
    /*0x0310*/ struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    /*0x03b8*/ struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    /*0x0430*/ struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    /*0x0464*/ struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    /*0x054c*/ struct ItemSlot bagPocket_Berries[BAG_BERRIES_COUNT];
    /*0x05F8*/ u8 seen1[DEX_FLAGS_NO];
    /*0x062C*/ //u16 berryBlenderRecords[3]; // unused
    /*0x0632*/ //u8 field_632[6]; // unused? //believe these 2 for vs seeker so could remove later?
    /*0x0638*/ u16 trainerRematchStepCounter; //appears, doesn't need to be in struct? its alwaysu referred to by saveblockptr not the trainerrematch struct
    /*0x063A*/ u8 ALIGNED(2) trainerRematches[100]; //think can safely remove
               u32 oakRanchStepCounter; //using for pc exp gain, set to 0 on new game, need have functino check for if mon in pc if yes increment w steps if no reset counter
    /*0x06A0*/ struct ObjectEvent objectEvents[OBJECT_EVENTS_COUNT];
    /*0x08E0*/ struct ObjectEventTemplate objectEventTemplates[64];
    /*0x0EE0*/ u8 flags[NUM_FLAG_BYTES];
    /*0x1000*/ u16 vars[VARS_COUNT];
    /*0x1200*/ u32 gameStats[NUM_GAME_STATS];//don't know how much but can prob save some by removing some of these
    /*0x1300*/ struct QuestLog questLog[QUEST_LOG_SCENE_COUNT];
    /*0x2CA0*/ u16 easyChatProfile[6];
    /*0x2CAC*/ u16 easyChatBattleStart[6];
    /*0x2CB8*/ u16 easyChatBattleWon[6];
    /*0x2CC4*/ u16 easyChatBattleLost[6];
    /*0x2CD0*/ struct MailStruct mail[MAIL_COUNT]; //still to remove
    /*0x2F10*/ u8 additionalPhrases[EASY_CHAT_EXTRA_PHRASES_SIZE];
    /*0x2F18*/ //OldMan oldMan; // unused  //emerald exlusive mauwile man stuff
    /*0x2F54*/ //struct EasyChatPair easyChatPairs[5]; // unused
    /*0x2F80*/ struct DayCare daycare;
    /*0x309C*/ u8 giftRibbons[11]; //check this since removed some this may not bneed to be 11
    /*0x30A7*/ struct ExternalEventData externalEventData; //can remove external events would like make some way of giving within game
    /*0x30BB*/ struct ExternalEventFlags externalEventFlags;
    /*0x30D0*/ struct Roamer roamer; //remove other stuff then make copy of this but 6 array for rival mon data
               struct RivalParty rivalTeamData[PARTY_SIZE];
    /*0x30EC*/ struct EnigmaBerry enigmaBerry;
    /*0x3120*/ struct MEventBuffers mysteryEventBuffers;
    /*0x348C*/ u8 filler_348C[400]; //assume this is to hold mystery event data?
    /*0x361C*/ struct RamScript ramScript;
    /*0x3A08*/ u8 filler3A08[16];
    /*0x3A18*/ u8 seen2[DEX_FLAGS_NO];
    /*0x3A4C*/ u8 rivalName[PLAYER_NAME_LENGTH + 1];  //think keeping famechecker, unique little fire red thing remove other stuff
    /*0x3A54*/ struct FameCheckerSaveData fameChecker[NUM_FAMECHECKER_PERSONS];
    /*0x3A94*/ u8 filler3A94[0x40];
    /*0x3AD4*/ u8 registeredTexts[UNION_ROOM_KB_ROW_COUNT][21]; //if not using union room may be able to remove
    /*0x3BA8*/ struct TrainerNameRecord trainerNameRecords[20]; //look into if this is just for record mixing
    /*0x3C98*/ //struct DaycareMon route5DayCareMon; //if the othe rthing works I guesss I remove this?
    /*0x3D24*/ u8 filler3D24[0x10];
    /*0x3D34*/ u32 towerChallengeId;
     /*0x3D38*/ struct TrainerTower trainerTower[NUM_TOWER_CHALLENGE_TYPES];  //not battle tower its trainer tower, look into if usbale if not remove  vsonic
}; // size: 0x3D68

struct MapPosition
{
    s16 x;
    s16 y;
    s8 height;
};

extern struct SaveBlock1* gSaveBlock1Ptr;
extern u8 gReservedSpritePaletteCount;

#endif // GUARD_GLOBAL_H
