unsure why my kaizen version doesn't have a read me file
when pret had one but oh well.

adding this now will fix later but for now 
will use this file to outline purpose of each individual feature branch


next goals

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