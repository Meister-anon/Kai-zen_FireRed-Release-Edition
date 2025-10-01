#ifndef FPMATH_H_
#define FPMATH_H_

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

// useful math macros --chaange type redef before capped most at u16 much better now u32
typedef s16 q4_12_t;
typedef u32 uq4_12_t;
//my addition
typedef u16 uq8_8_t;

#define Q_4_12_SHIFT (12)
#define UQ_4_12_SHIFT (12)

#define Q_8_8_SHIFT (8)
#define UQ_8_8_SHIFT (8)

#define Q_4_12_SHIFT (12)
#define UQ_4_12_SHIFT (12)

// Converts a number to Q8.8 fixed-point format
#define Q_8_8(n) ((s16)((n) * 256))
//my addition
#define UQ_8_8(n) ((uq8_8_t)((n) * 256))

// Converts a number to Q4.12 fixed-point format
#define Q_4_12(n)  ((q4_12_t)((n) * 4096))
#define UQ_4_12(n)  ((uq4_12_t)((n) * 4096 + 0.5))
#define UQ_4_12_FLOORED(n)  ((uq4_12_t)((n) * 4096))

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


static inline uq4_12_t uq4_12_multiply(uq4_12_t a, uq4_12_t b)
{
    u32 product = (u32) a * b;
    return (product + UQ_4_12_ROUND) >> UQ_4_12_SHIFT;
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

#endif // FPMATH_H_
