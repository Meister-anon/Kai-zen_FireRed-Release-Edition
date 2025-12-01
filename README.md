unsure why my kaizen version doesn't have a read me file
when pret had one but oh well.

adding this now will fix later but for now 
will use this file to outline purpose of each individual feature branch


next goals


-this is a test branch for evaluating changes planned for master

-of note odd bugs with neutralizing gas
not properly clearing when leave field I think
kept pixelate from updating move type
only fixed when sent in castform to activate their abilityeffect
so guess have to retrigger abilityeffect function to clear 
also on switch in if neutralizing gas mon comes in
taking a hit ends battle as if caught opposing mon
adding them to your team...

-confirmed this bug does exist in master - attempt fix on test master

finished removal of gactivebattler

following that can work out move flags rework
and gbit table removal w regex sub

keep lvl cap form change and guard style work for distractions

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

pokemon.c will most likely also be affected
so keep an eye out