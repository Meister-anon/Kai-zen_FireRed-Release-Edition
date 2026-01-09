
Branch Goals:

Create new battle mechanic that allows for retrying 
trainer battles from trainer slide in.

also port give up feature branch
think is on aqua base replace run in trainer battles with give up

take part of that and rework for my needs

thought further on considering,
do effect by making battle flag.

so can exclude from battles I don't want
to have it on.

like elite four

can replace BATTLE_TYPE_EREADER_TRAINER

think what I may want to do is
set value automatically if not a battle that shouldn't allow retry

make inline or something
and set battle flag on set battle data if should

i.e  battletype flags |= BATTLE_TYPE_BATTLE_RETRY

then want split run\give up option ito

retry \ give up

forgot also had plan for special battle type for legendaries to change
how master balls are done so they're not so boring

plan is "use" master ball
and instad of throwing it triggers a script

legendary pokemon reacted to master ball
does like x y  they get a 2 stage totem style stat boost.

and you have to fight and defeat them at the boosted form
to get the guaranteed capture.

pretty much they'll respect your power
instead of falling off scren when fainted
trigger script  legendar pokemon respected your skill as a trainer!

then trigger the toss master ball animation and continue as normal from there

would work like battle retry assigns battle type when use item
and from there use the battle type arg to change how things play out

look into how trainer block is handled should help