#ifndef GUARD_OPTION_MENU_H
#define GUARD_OPTION_MENU_H

void CB2_OptionsMenuFromStartMenu(void);

u8 IsEventSpeedupOn(void);
u8 IsNuzlockeModeOn(void);
u16 GetSetLvlCap(void); //for my dynamic lvl cap returns max lvl if cap off
u8 IsDisplayTypeEffectivenessOn(void);

#endif //GUARD_OPTION_MENU_H
