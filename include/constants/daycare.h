#ifndef GUARD_DAYCARE_CONSTANTS_H
#define GUARD_DAYCARE_CONSTANTS_H

// Parent compatibility scores - changed compatibility formula from odds based to fixed value
#define PARENTS_INCOMPATIBLE       0
#define PARENTS_LOW_COMPATIBILITY  1//20
#define PARENTS_MED_COMPATIBILITY  4//50 //change to 2 and 4, then make bonus 4x max
#define PARENTS_MAX_COMPATIBILITY  8//70 //or maybe leave as is idk

// Daycare state
#define DAYCARE_NO_MONS     0
#define DAYCARE_EGG_WAITING 1
#define DAYCARE_ONE_MON     2
#define DAYCARE_TWO_MONS    3

#define INHERITED_IV_COUNT 3
#define EGG_HATCH_LEVEL 1//5 /CHANGED decided to use 1, like EM plus makes ng+ being lvl 1 make more sense
#define EGG_GENDER_MALE 0x8000  // used to create a male egg from a female-only parent species (e.g. Nidoran)

#define DAYCARE_LEVEL_MENU_EXIT 5
#define DAYCARE_EXITED_LEVEL_MENU 2 // would be redundant with above if GF had used the same value

// Array buffers
#define EGG_MOVES_ARRAY_COUNT           10
#define EGG_LVL_UP_MOVES_ARRAY_COUNT    50

#endif //GUARD_DAYCARE_CONSTANTS_H
