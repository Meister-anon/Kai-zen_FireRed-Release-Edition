Branch Goals:

Ability reworks testing for things
to complex to be assured of to do on master.

rn testing color change and ball fetch reworks

color change set type based on terrain and weather
default to set type 2 or 3  look at mimicry for planned effect

and ball fetch is more direct clone of Dancer
user returns ball moves from enemy side back to user

Unlike Dancer this won't work affect ally
Still need to research origin effect more to see how this would work. ex. is it only one per turn activate?
or if both foes use target move cat will it activate for both?

ball fetch update is done swapping efforts to color change

working on Raduziel version of color change
i.e defensive protean that changes type
before getting hit.

simple change to make hard to get right.
need proper place to set message that effect
happens and then return to battlescript
so think need one of the push cursors placed
within one of the general use battle script commands

thought attack canceler but realized would change type even on miss, place that makes
most sense is attack string
but some moves have accuracy check AFTER
attack string for some reason

current plan get working figure edge cases after.

think do like stench/neutralizing gas?
push cursor paired with script that ends in return

look up BattleScript_StenchExits

else if (gBattleMons[gActiveBattler].ability == ABILITY_STENCH
         && !(gAbsentBattlerFlags & (1u << gActiveBattler))
         && !IsBattlerAlive(gActiveBattler))
        {
            gBattleMons[gActiveBattler].ability = ABILITY_NONE;
            BattleScriptPush(gBattlescriptCurrInstr);
            gBattlescriptCurrInstr = BattleScript_StenchExits;
            return;
        }

may need  new move struct value
i.e check if bs has acc check AFTER atk string

then maybe a special status like intimidate
just to indicate that color change has completed

so doesn't double complete
but thinking will have to put checks in both
atk string AND the accuracy check command
to accound for the difference in moves

actually think change would need to be on
battle effect rather than
move?

i.e where emerald has

yeah battle effect as that determines batltle script.

so add on to that struct value for 
true/false acc check after attack string

set with false for default to cut down extra work
i.e most scripts have acc check before atk string
so do accCheckPost/AfterAtkString

false would be default so wouldn't have to even 
add it for most

special status for finish color change

rathern color change done think pre-hit ability done

note- check special status if it doesn't clear
at end of battler action it would stop things like
dancer etc.
unless want to make that a balancing thing
and can't react to more than one change 
per action?

would make sense also dancer likes would always be the same attack that hit initially anyway
so no problem there actually.

just like switchin ability logic
ok and I THINK it should already work 
even with things like dancer done this way

and new ability effect to call function logic 
itself just do abilityaffectfunction call
for new ability affect and battler set to target I think

within just do ability check 
battle script push
and then just make sure to have bs end in a return.

so should set type, print message,
and then return to normal battle script
to finish move for attacker

so get move type and buffer battler name w prefix

think put new ability effect at end of list
before closing stuff 

*should there be attacker pre hit affects?

I think no?
basic purpos of doing this right before attack hits is only for defensive reaction
and affect that would affect the attacker
or involve their battle partner
could just be a constant effect or triggered
in damage calc etc.

there'd be no reason for the attacker or their partner to stop their attack just to do something

...unless something crazy like parter checks 
move that is being used if its resisted
they could add their type to move to either
change its type or make it a two typed move?

fuck it I'll leave that for someone else to
decide/figure out. I'll only do target based effect

ability cat 
Pre-Hit_Reaction

did color change effect
plan top add adaptability boost on changed type i.e type 2

but can't make effect in my version of game
better to just do after battle script refactor
annoying smh



