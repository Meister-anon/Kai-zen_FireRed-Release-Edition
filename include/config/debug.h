#ifndef GUARD_CONFIG_DEBUG_H
#define GUARD_CONFIG_DEBUG_H

// Overworld Debug
#define DEBUG_OVERWORLD_MENU            TRUE                // Enables an overworld debug menu to change flags, variables, giving pokemon and more, accessed by holding R and pressing START while in the overworld by default.
#define DEBUG_OVERWORLD_HELD_KEYS       (R_BUTTON)          // The keys required to be held to open the debug menu.
#define DEBUG_OVERWORLD_TRIGGER_EVENT   pressedStartButton  // The event that opens the menu when holding the key(s) defined in DEBUG_OVERWORLD_HELD_KEYS.
#define DEBUG_OVERWORLD_IN_MENU         TRUE                // Replaces the overworld debug menu button combination with a start menu entry (above Pokédex).

#define DEBUG_AI_DELAY_TIMER            FALSE   // If set to TRUE, displays the number of frames it takes for the AI to choose a move. Replaces the "What will PKMN do" text. Useful for devs or anyone who modifies the AI code and wants to see if it doesn't take too long to run.

//test config no other place to put this
#define B_USE_FROSTBITE                 FALSE      // In PLA, Frostbite replaces Freeze. Enabling this flag does the same here. Moves can still be cherry-picked to either Freeze or Frostbite. Freeze-Dry, Secret Power & Tri Attack depend on this config.


#endif // GUARD_CONFIG_DEBUG_H