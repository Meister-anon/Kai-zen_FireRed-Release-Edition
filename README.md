.
Branch Goals:

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

and add the member if necessary

want contests since I enjoyed them so for now keeping contest data just
commented out
at completion can remove w regex replace

think handeling bs update in batl controller branch
so think can leave defining addtionalEffects over there
and just pull changes in when that's done?


next goals


-this is a test branch for evaluating changes planned for master

keeping type change of bug resisting electric
makes sense lot of bugs 
can generate or manipulate electricity or electric fields
even common bugs like bees

think to get this across to the player
best way is to adjust the bug trainer text
in viridian forest
add some bug facts about bugs generating electricity
give some bugs select low power electric moves

main diff they will still be able to be paralyzed

-of note odd bugs with neutralizing gas
not properly clearing when leave field I think
kept pixelate from updating move type
only fixed when sent in castform to activate their abilityeffect
so guess have to retrigger abilityeffect function to clear 
also on switch in if neutralizing gas mon comes in
taking a hit ends battle as if caught opposing mon
adding them to your team...

-confirmed this bug does exist in master
-fixed neutralizing gas

-major note more battle anim issues with speed up
seems morning sun which does blend effects
skips an important clear and the screen remains washed out
like a flash bang.

only fix is closing and opening party menu 
to refresh display maybe adding some sort of cleanse
as last command of all animations would help with that?

on btl ctrl update finish removal of gactivebattler

following that can work out move flags rework
and gbit table removal w regex sub

keep lvl cap form change and guard style work for distractions

go back and reorder all battle.h structs etc
to make sure they match old order
with new additions added to bottom to preserve order

most important replace all battle files with EE versions
after seeing just how much is changed with recent EE work
on color change no way I can just peicemeal it.

this includes battle animations moves battle_move effects
consolidating battle controller to degree necessary
battle script commands battle main and battle util
then I can just take ai files as they are

for ai think just need take my multiplier change logic
and the stuff for the hazard changes

take files exactly as they are from EE
then can prune out features I don't need like dynamax
and fit back in my custom stuff

rename things FR_ based on if exclusive to firered
when porting back.

order finish remove gactivebattler
do gbit table removal, then can create branch
to update all battle files

pokemon.c will most likely also be affected
so keep an eye out
