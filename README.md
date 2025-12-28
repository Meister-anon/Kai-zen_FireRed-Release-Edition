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
