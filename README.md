.
Branch Goals:

IMPORTANT:

test/text.c
Expansion already has file that perfectly catches
string length and if it finds bounds of a given
graphic measured using pixels

when I get test system working use above file path
to edit tests to fit my values
hard part prob be dex page and figure how to get
pixel width since I don't want to take entire space
as that would break indent well no can use 2 tests
one for fitting the default space 
2nd for max space should I need it
and only return error if fails both
guess just warning if fails first

also need add wall werror to cpp flags for modern
to catch code errors pretty much entire point of modern
and I'm not taking advantage of it forgot
only reason I turned it off was to find issues
why modern wouldn't build now that Ive addressed them all
need to turn back on.
unfortunately have bunch of code that doesn't follow modern
standard and needs to be fixed.

think wait till have everything merged back to master to fix smh

I know now expansion fundamentally changed ai
and all their ai updates have been done to the base version
not at all preserving how base ai worked. *facepalm*

so with battle system updates I'll have to go back and redo the ai
to ATTEMPT to make it decision whise work like base game,
along with any changes between fire red and emerald

AND THEN make my own ai changes that I had planned
to handle switch logic, plan for that was switch counter
based on category or level of trainer ex ace and gym leader
w elite four being highest  young trainer being lower usually
giving them max amount of switches so its doesn't become
an annoying infinite counter fest

But keep randomness in as well especially at lower levels.
might not be as bad alex mentioned

the basic flags from gen3 are "check bad move, try to faint and check viability". If only those 3 flags are used the AI will feel familiar to gen 3

also of note "if you remove check viability it will never use a status move"


//important note battle move info callback is too slow
//still noticeably slower than opening party menu from battle
//when don't think should be


//for randomizer certain species forms require their item
    //to be the form i.e areus forms are meaningless
    //without the plates now, as the plate is what activates ability
    //and changes form,
    //so need setup so if spawned the held item MUST always
    //be the corresponding item necesssary to enter form

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

noticed viridian forest seems darker than normal overworld
wonder if there is an effect there I can use 
for night time or tinting caves to replace full black circle

IMPORTANT note for later
for randomizer consisder setup restricted runs
rather than have to remake all encouters
let randomize to only a set type of mon for wild encouters
so players can do runs with only a certain type of mon
doesn't have to be monotype
then randomize existing encouters to mon of said type
within range of bst so progression doesn't get broken


only odd thing to work out are surf/fishing encouters
guess look for mon that match part water part restrcited type

make new weather into Tms think give in early game
best way for player to get idea of new effects

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
