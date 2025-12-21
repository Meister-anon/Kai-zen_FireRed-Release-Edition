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


Dedcide much smarter to split out battle file update into
diff branches.

This one will be for battle anims
