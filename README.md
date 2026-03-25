.
Branch Goals:

able to build with latest commits but animations are not  playig correctly
on branch attempted merge anims update with effects update
game is unplayable yet compiles, initial plan was continue updating anims branch
but no real idea where problems lay.

Instead new plan with expansion updates that add Firered changes
plan re add animation and battle controler specific things fully replace systems
with EE values then review other branch to add back my custom stuff
mostly just acid rain, custom weather fog for lavender tower (in case I need to remove that)
and my player move info callback, which hopefully can be done in a cleaner way

tldr replace animation files and controler files w EE equivalents add back 
few custom things.

If can figure out workspaces that later comparison repplication can hopefully 
go smoother

Note to keep eye on battle anim constant i.e mon scared ghost dodge ball etc.
B_ANIM_LVL_UP_EVOLVE
#define B_ANIM_INFESTATION              0x2C
#define B_ANIM_MOONLIGHT_SHINES         0x2D    //should be setup now?
#define B_ANIM_ACID_RAIN_CONTINUES      0x2E
#define B_ANIM_SNOW_CONTINUES           0x2F
#define B_ANIM_FOG_CONTINUES            0x30

#define BALL_GHOST_DODGE        6 /btl controler
CONTROLLER_MOVEINFO
void BtlController_EmitMoveInfo(u32 battler, u32 bufferId);

GhostBallDodge -in battle_anim_special - should be safe is FR specific

// Inflicting damage is key
#define FIRST_BATTLE_MSG_FLAG_INFLICT_DMG    0x1
// Lowering stats is advantageous
#define FIRST_BATTLE_MSG_FLAG_STAT_CHG       0x2
// Keep an eye on your HP
#define FIRST_BATTLE_MSG_FLAG_HP_RESTORE     0x4
// for opening party menu swtich
#define FIRST_BATTLE_MSG_FLAG_PARTY_MENU     0x8
//  move learn ui adjusts (for first time learn new move)
#define FIRST_LEARNED_MOVE_MSG_FLAG         0x10 //should this be 10?  
//^custom  for displaying can move to stat screen from level up move info

very important need keep type effectiveness display setup as well
*** end of new note

Need split off extra changes to other branches
leaving only the battle_moves.h flag related changes 
was new_battle_update_branch  delete deprecated remotes as well

so plan finish flag related changes i.e update to no longer use flag
checks in battle moves use inline functions that check for members
after that I can depreciate the branch and merge or cherry pick over
the stuff needed for flags leaving everything else to go to 
another branch to continue work.

update battle_moves.h file flags to EE standard
end goal remove .flags field
much better filtering and will eventually update
name and move description and animation field to move blocks
unsure if will do in this branch or separate one later

Presently have updated file with all data from EE file
still to do is set struct values for my custom effects
and go over all the flags I added/previously may have updated i.e pulse moves punching moves etc. effects I may have added to moves that previously didn't have them essentially.

NOTE**(
    for terrastilizing several normal effects are now sound
    lowing reason to terra normal
    so to counter for terrastilizing normal type
    have it increase joat boost
    i.e if pokemon was normal and terras normal boost joat

    typically the boost recieved is doubled 1.5 becomes 2x

    if I double joat it becomes 1.34  where stab is 1.35

    simplest way to get bonus is base multiplier x 2 - 1

    so for normal going terra normal you'd have
    both doubled stab bonus on normal moves

    and essentially fake stab on EVERY other type
)

and add the member if necessary

want contests since I enjoyed them so for now keeping contest data just
commented out
at completion can remove w regex replace

think handeling bs update in batl controller branch
so think can leave defining addtionalEffects over there
and just pull changes in when that's done?


next goals


Dedcide much smarter to split out battle file update into
diff branches.

This one will be for battle anims
