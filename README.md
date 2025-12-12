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


updating battle effects and scripts to EE
standard in prep for ability effect changes etc.

step by step to not be overwhelmed 
will need replace battle effects
and move effects

a lot of refactors done for moves
so scripts are changed a lot
ex explosion refactor
does everything in c code rather than 
needing like 7 different bs scripts

big impact is the changes I made will need
to be reintroduced,
 a major effect is my call_if logic
 which I THINK shouldn't be a big deal
 and will just be handled by the additional_effects struct


 process is go over moves
 see what if any effects I changed from default.

 same for custom changse to any move effects

 if none replace with emerald version
 if their are custom changes then preserve
 effect as needed to keep track of new changes
 if no better way to do them with new functionality incoming

 ex submission in ee is just effect hit
 but I've updated to recoil move that
 brick breaks, and goes through protect

 so may have case to include effect now

 also of note most bs commands I made to 
 load power or daamgae change efects
 can prob just wrap into EE damage calc
 makes more senes to just have all in one function
 rather than a bunch of commands slapped in randomly smh

 ex. typebaseddmgboost
 variablepowercalc
 presentdamagecalculation

 also revise multihit to use strikecout filed and how they set
 which will remove multihit bs 
 
 concern is just fury cutter moslty
 since supposed to incrase in damage base on counter

 if can use strike count to hold num total hits
 should be able to remove one counter
 prob multi task counter and just keep multihit counter



 New idea for arceus genesect type null/sylvally
 but requires complete item expansion smh - noting for now

 //may give move property so can distinguish between the moves
    //of shared effect
    //PROB best to just do same thing I did with judgment
    //think will change effect of plates and drive
    //drive especially has little use
    //so what think will do is give it a type resist
    //so fire drive would give you a resistance to fire type moves for genesect
    //hmm ok think do something different for plates
    //rather than giving single type waakness since would be worse
    //than its existing effect would set to give type attribute and benefits
    //so give type affinity i.e fire cant be burned
    //and then also give the benefit of the types resistances
    //but without becoming said type
    //think check type argument from plate fire plate
    //integrate with type check, when found item
    //check if attack type would be resisted by item arg type
    //if so calc damage using said type
    //sounds good, think will make memories do same thing as drive
    //to drive home its not arceus
    //or keep memories to default
    //yeah think like that better that way memories and plates
    //are similarly linked while drive gets its own
    //distinct effect