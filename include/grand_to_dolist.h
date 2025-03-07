#ifndef GUARD_GRAND_TO_DOLIST_H
#define GUARD_GRAND_TO_DOLIST_H

/*this file is to be an itemized list of things I plan to do/my progress.
with the intention of cleaning up my files, so I dont have comments everywhere
and to help ensure I don't lose track of things

Procedure--
include a file I am working in with line stamps		*as you can use includes to navigate to said file*
and a brief description of what my goal is there
each thing should be checked off when done
//OK REALIZED I can use goto's with variabls as a shortcut parts of to .c files

note: personal notes within repo- zsonic used as points removed ewram was also spots to double check,
but forgot and eventually used vsonic instead for notation to refer back to

*/

/*
* note from CompuMax in pret   fire red debug system not removed actually takese up ewram so going through removal process saves space.
* 
* Make the following change to include/config.h To get some space in the EWRAM and IWRAM
// #define NDEBUG
To
#define NDEBUG

And in common_syms/main.txt remove the following lines:
sVcountAfterSound
sVcountAtIntr
sVcountBeforeSound
 
Meister_anon � Today at 6:22 PM
thank you very much,  what does the com_sym stuff do? so I know what I'm doing.
CompuMax � Today at 6:24 PM
The first change is defining that it does not include the DEBUG used during the development and testing of the game. Since they forgot to remove it before publishing the ROM. 
And the second change removes the references in IWRAM from references used in the DEBUG
Meister_anon � Today at 6:25 PM
ok so its all part of the same removal?  for taking out the debug stuff?
CompuMax � Today at 6:26 PM
Exactly
* 
* [tested in pret and works so adapting for main repo, worked for expanding species name]
* Explanation for why it works
* 
* 
* did you inspect how much space you needed in iwram before moving stuff to ewram?
CompuMax � 06/03/2021 10:23 AM
No, but now that you mention it, it could be the IWRAM that is generating the problem for me.
I am still installing the mixer in pokeemerald to rule out that the tutorial has overlooked something
PikalaxALT � 06/03/2021 10:24 AM,<<<
one thing you can do is set config.h to define NDEBUG
that'd give you back 0xB4 bytes in IWRAM
CompuMax � 06/03/2021 10:33 AM
Oh! Thanks! I will do it
Although I imagine that I am exceeding the IWRAM when compiling, it should show an error, right?
PikalaxALT � 06/03/2021 10:35 AM<<<<
it'll also give you back something like 0x754 bytes in EWRAM, which is huge



Notes on health box
I'm wondering why its using TextIntoHealthboxObject twice
CompuMax � Today at 8:33 PM
@Meister_anon Because the Healthboxes are too big, they are divided into 2 OBJs of 64x64
What the first TextIntoHealthBox does is copy the first 6 tiles that make up the nickname to the first OBJ
Then depending if you are in a double battle or not, determine where to copy the remaining 7 tiles into the next OBJ


Meister_anon � Today at 12:46 PM
ok I see it now, I luckily came close to the right solution,  32 x 4bpp is the same thing as I had before 0x400 etc.
and is still half of the playersidee values so the relation is the same.

but since the player first textintoHealth function ended in 6
the 2nd function needs the value 6 * TILE_SIZE_4BPP

and since the enemy side ends in 7  that's why I need 7 * TILE_SIZE_4BPP


Palachu � Today at 4:06 AM
Fun fact: the new character limit for Pokemon as of Gen. 6 is actually 12 (Crabominable and since Gen. 9 also Squawkabilly)

Stat calc Iv allocation note

Meister_anon � Yesterday at 10:29 PM
ok so apparently trainer mon have ivs and are used the same way, but unlike wild mon, they aren't set randomly,  it uses fix values to generate the same ivs for each stat?
but most have 0?
GriffinR � Yesterday at 10:33 PM
That's correct
Meister_anon � Yesterday at 10:52 PM
awesome glad I understand that now



Meister_anon � Yesterday at 11:33 PM
I don't understand bit wise so I'm just gonna have to ask this.
since trainer mon personality is also fixed and based on trainer name and mon species name.

does that mean rematching the rival, or other enemies you face multiple times, with different teams,

is it possible their mon could have completely different abilities when they evolve?
As personality determines the ability slot.

GriffinR � Yesterday at 11:36 PM
No, because the way they're generated will never set the first bit of the personality. NPC trainer pokemon will never use the alternate ability
Other things like their natures would change, though
Meister_anon � Today at 12:15 AM
hmm I see, so if I want them to be able to, I need to make it use non fixed personality, or set it up to be able to set the ability from trainer party

GriffinR � Today at 12:26 AM
This is where the first byte of each pokemon's personality is set (none of these values have the first bit set).
You could calculate this byte any way you like, including setting the first bit

if (gTrainers[trainerNum].battleType == TRUE)
                personalityValue = 0x80;
            else if (gTrainers[trainerNum].encounterMusic_gender & F_TRAINER_FEMALE)
                personalityValue = 0x78; // Use personality more likely to result in a female Pok�mon
            else
                personalityValue = 0x88; // Use personality more likely to result in a male Pok�mon

                apparently ecounter music field uses/has a gender value

[I don't udnerstanad what he meant about the bit/bytes but I can add an abilit num field to party data
and make it select the abiliity that way  il.e abilitynum 1 = ability slot x and so and so
also consider better way of assigning personality and adding nature selection to custom fields as well.
They used 2, relatively static fields here to attempt uniformity for rematches.

as it stands personality would change if mon evolves, which would change nature, but not ability,
but because of the attempt at tying mon gender to player gender, trainer mon would never naturally
have anything besides their default ability.

I can add an extra check to get around the personality shift. I think.
pretty much use the name hash to chcek for multiple instances of that trainer occuring.

from their loop through their partry find the personality value as normal,
for other appearances check each party slot for a mon of that evo line, if its in the evo line,
but the species value isn't the same,  compare personality values and have the personality value 
set at the first encounter overwrite the current value.

slightly complex but would ensure consistent nature and abiility

plan:
set direction selection for ability num & nature for custom trainer data

but for default making this change so fighting the same trainer again when they have stronger/evolved mon
would result in the same nature and abilty as first time encountering them, (would require setting it so ability can be different)

checked trainername (which is used for personalityvalue  /namehash, never changes,
so can ues that reliably, 

incase names are reused filter for trainer class as well.
only time trainerclass is every changed is for rival.
and can easily filter for him only with "isrivalbattle" function.   
(thankfully rival name "Terry" is not reused its only for rival
so check is rival battle, make loop just trainername ignore class)

logic is to loop gTrainers until you find the first instance of a trainer name(and class) that matches
the current gTrainer trainer num  trainer name
once you find that loop through that party for a mon in the evo line as the mon in the current trainer party
if you don't find a like evo line species  move to next mon in party and break out back to continue main loop
at next instance of matching trainer name.

If you do find a matching evo line speices, check if the actual species name matches the current trainer species name,
if it does match  break and continue checking the rest of party if all match do nothing, as there is no cause for a different personality value

if the evo line matches, but the species names don't match, we found our criteria, overwrite namehash of current species with that of original instance
that way even when the mon is evolved it will keep identical personality i.e identical nature

use u32 values for i, to make move faster/more efficiently
also attempt to do all this with new function rather than in createnpctrainerparty function
as this is a massive implementation and I'd rather not make the function look any uglier

would call personalityvaluechecksum or sometihng

//function value set & value comparison logic

Meister_anon � Today at 10:10 AM
Does a function have to return a  value, for it to be used as a value comparison?
like does it only make sense to use logic x == function

if that function is built to return a value?
Kurausukun � Today at 10:20 AM
I don't see how else it would work
Otherwise you're comparing with whatever garbage is in the register



Meister_anon � Today at 2:09 PM
what does it mean when this value is used?   " \ "
I see that in the repo in some places,  its not the division one

I'm assuming it does something similar to commenting?
GriffinR � Today at 2:44 PM
No, this wouldn't be a comment. It's a backslash, its meaning depends on the context. For example in a string n is just the character n, but \n is a newline
In general it's used as an indicator to treat what follows in a different way

Kurausukun � Today at 5:00 PM
It's called an escape sequence
If you Google it you will find more info

Meister_anon � Today at 5:24 PM
ok looked into it, but the way its used wasn't mentioned in the resource i found.
the escape was used at the end of a line, where a constant was being defined.

I'm guessing using the escape that way lets you extend the values for a define for
further than a single line?
GriffinR � Today at 5:35 PM
Yes, that'd be to carry the definition onto the next line


Meister_anon � Today at 12:18 PM
Can someone give me a heads up on why this text causes issue in pokedex entries?

"will-o�-the-wisp"

from what I can tell all the characters individually are used in other dex entries.

GriffinR � Today at 12:21 PM
� is not the same as '
Meister_anon � Today at 12:21 PM
ok got it,
alright easy fix to make then
you can prob tell yes, I copy pasted from online
GriffinR � Today at 12:23 PM
You can also add it to the charmap by putting a '�' = B4 in charmap.txt. It was added to pokeemerald's, it just hasn't been added to pokefirered's yet.
This would treat it the same way as '
Meister_anon � Today at 12:24 PM
good to know,  
oh wait,
you're saying it would default to the same character oh ok cool.
ok I prob will do that then.

Meister_anon � Today at 9:08 PM

can someone explain how foresight works for me?
i know its supposed to get passed the no effect multiplier for typing but I'm not understanding how.

 is it changing the move type so it hits neutral, but while TYPE_FORESIGHT
is in the table, its not listed under type names.
Kurausukun � Today at 9:10 PM
It's a massive hack
It's just in the type effectiveness chart
Meister_anon � Today at 9:11 PM
is the i+3 making it go to type_endtable and somehow skipping typeset so it does neutral or something?
Kurausukun � Today at 9:12 PM
I forget exactly how it works, but I remember it being stupid
Meister_anon � Today at 9:13 PM
sigh I can imagine.
The Sylph is In � Today at 9:13 PM
If the defender has the foresight status, it breaks out and stops checking the type effectiveness table (and ghost�s normal/fighting immunities conveniently are located after type_foresight)
Kurausukun � Today at 9:14 PM
Also you're reading that wrong, the break keeps it from going to +3
Yeah, what they said
Meister_anon � Today at 9:14 PM
yup that'd do it.
and it defaults to normal multiplier which is why it does neutral (I think)
Kurausukun � Today at 9:15 PM
Yes
Meister_anon � Today at 9:16 PM
ok just needed to understand that so I could setup scrappy logic.
just need to double check I didn't move those type checks.

if not I should be able to just have it use the same logic to make that work.
Thanks to both of you. 
Kurausukun � Today at 9:17 PM
Yeah that should work


Meister_anon � Yesterday at 8:55 PM
yo archie think you can help me with something,
I'm workign on an effect and I think I'm misunderstanding a line, it seems to be used elsewhere about exactly how I have it, and I think I've already fixed any pointer issus I had
&gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]];


does this mean the target is the enemy, or does it mean the mon the enemy is targetting?
Archie � Yesterday at 9:17 PM
This code seems like it should only be running when you are targeting an enemy mon
gBattlerTarget is the mon currently being targeted by a move
Indexing that in gBattlerPartyIndexes pulls out the position in the party that Pokemon is in
Then it's indexed in gEnemyParty which is the array holding all the structs of the enemy mons
So it's just pulling out the enemy mon struct for the mon that is being targeted
But it's only for enemy mons, to do the same with the player you would just swap with gPlayerParty

*/

//Learned from Kurausukun can see ewram and memory use by checking pokefire.map file I have 0x5800 or so ewram left
//a pretty solid amount, potentially after things are settled can setup table or something to store trainer party data,
//so values are the same when fighting them again. not a necessity but would be realistic and nice to do if I have the space too...

//Single extra note, for battle script,  I think when I use a call, it has to end in a return
//but I can't use a return when jumping I instead have to use a goto

//I've decided I'm not making 2 things rather than a rom base at emerald expansion standard, and my own game with all the features I like
//I'm making one project Kai-zen Red  will be everything I want, my vision for what pokemon should be.
//It will have everything, and be THE rom base for fire red projects going forward!! -4/18/2023  11:12am  MEISTER!!

/*
* Streamer mode,  set flag option for new game start only not in game STREAMER MODE/CREATOR MODE  for streamers/content creators, 
* gives every mon pokerus, make pokerus increase exp gain x 12, set ev gain multiplier to 4 in MonGainEVs,
* global exp share on by default, gym leader based lvl cap, trainer lvl scaling to average party/highest mon,
* give all ev items, macho brace, ultima brace, and power items.
* That way won't need rare candies just for streamers.
* 
* Have it as a message setup before the oak intro, or the last line before player spawns
*/

//realized text buffers used in battle_message.c allign with values in charmap.txt, the names used are those, and the value is from battle_message.h

//NOTE-:
//.4bpp name and gbapal graphic define names have to match to be able to build pal from png     /ex below use "eviolite" as name
//const u32 gItemIcon_Eviolite[] = INCBIN_U32("graphics/items/icons/eviolite.4bpp.lz");
//const u32 gItemIconPalette_Eviolite[] = INCBIN_U32("graphics/items/icon_palettes/eviolite.gbapal.lz");

//redid base stats field need properly fill macros then remove stat fields
//setup basestattotl function like kurausukun said, need proplery setup item grahpic swap for eviolite
//find how species is set. search  CanEvioliteActivate   to find where put function/item icon stuff

//zygrade forms are wonky the way they set them up is odd, they separated zygrade out into multiple species based on if it had power construct or not
//rather than just making that an alternate ability for the same species

// plan to just fold it all into a single ability aura break & powerconstruction
//they also made the base zygrade the 50% form rather htan the base 10% form, whem that one is usually the one you initially get
//so I need to remove the extra species, and change the graphic values so base zygrade coresponds to the 10% form
//will end up with SPECIES_ZYGARDE_10 , SPECIES_ZYGARDE_15, SPECIES_ZYGARDE_COMPLETE
//With a single ability, hmm no I'll keep two abilities but fold aura break affects into power construct as well.
//because you may want to just keep the faster form, rather than changing to a slower but bulkier form when low hp
//and allow ability capsule to work with it, to change it  -time consuming so do later not now

//note make weather rocks also boost move type damaage, so I'm not losing out for example I have a hard stoneo for rock dmg
// but if I want a smooth rock for extending weather make the holder also get a rock/groud type move boost,
//think need boost to a lesser degree for balance but still need the boost to get use out of it
//think will do old bonus 10% for these, keep 20% for specialized boost items themselves - done but need add to descriptions when do item expansion

//realized since plan to have easy access move relearner
//there's no purpose for prisms scales or heart scales,
//can use for move turtor but think would also do version of idea from anthroyd server
//where a mon can learn any move, more specifically using a scale will allow a mon to learn
//a tm move that is otherwise outside of its learnset.

//and since its a rare material to find, doesn't even need to cost levels.
//plus this is a cool thing that adds a bit of realism, like in the show
//where mon could use moves they aren't capable of learning in game.
 

//TODO:
/*Add logic for when flying types are grounded they take neutral damage from fighting types
* also do same for electric based on doduo, idea of flying weakness to electricity
* is them flying high in the air makes them more likely to be hit by lightning
* but doduo can't fly, so that doesn't make sense, so to account for that,
* make all grounded flying types neutral to electricity, - done
*
* added that along with tweaking fossil typing for early gen fossils
* also adjusted primary status setting status moves to add type checks
* will fail for mon immune to them  
* will allow for more nuance and also easier abiity selection 
* as based on type some mon may not need abilities like insomnia to prevent sleep
* as they would be realtively protected  i.e nuzleaf which powder move change
* is suddenly immune to all grass sleep moves, as well as psychic sleep moves via its dark type
* so its effectively safe from being put to sleep already
* freeing it up to use better abilities
*
*
* 
* Another point make roost work/ground mon even if full hp, as extra nuance
* so they can take shelter against lighting, still need work out logic for going back into air
*logic says roost should last for timer duration or use of a flying move,
* but if you expand the idea to just staying low to the ground i.e low elevation flight?
* the idea can work, so just make FLY and SKY DROP auto break grounded status if roosted/smacked down
*
* extra idea, potentially make move other than roost that gives "grounded" status for flying mon
* maybe call it 'Trench Run'  so low level flight, to make more palatbile give its own effect
* thinking raise evasiveness one level, since the strategy is usually used for aircraft to dodge radar

*Nap-of-the-earth (NOE) is a type of very low-altitude flight course
* used by military aircraft to avoid enemy detection and attack in a high-threat environment.
* Other, mostly older terms include "contour flying", "ground-hugging", 
*"terrain masking", "flying under the radar" and "hedgehopping".
*
* While "Trench Run" isn't exactly the most accurate name its best I can come up with for this idea
* Description: "For 3 turns the user\nswitches to low level flight\nboosing evasiveness.\nAlso losing its Electric\nweakness, for the duration."
* rather than setting another thing, think just use roost timer/logic for grounding, hmm
* nah make just make new status for this, and put that in isbattlergrouded function
*anyway move just makes grounded, which would trigger typecalc change, and 
*just have move raise evasiveness if not already have status/used.  give effct evasion up 2
*
* Look at how emerald handeled smack down and roost logic for ground type dmg -
* 
* Setup moves with flag 2x dmg on air to remove on air status and ground target when they hit flying target
* -done
* 
* comb pokedex_text_fr.h  remove unused dex entries save a little more space, also look over dex entries
* that are boring see if entries can be improved from parts of pokemondb entries
* 
* adjust charmap based on emerald update, for other style apostrophe - DONE thanks to griffinR
* 
* Changed OHKO moves, so they have a chance to land when below level. -DONE
* (since its luck, set it to work when attacker up to 7 levels below the target
* if (Random() % 100 + 1 < chance && gBattleMons[gBattlerAttacker].level >= (gBattleMons[gBattlerTarget].level - 7))
* 
* go over summary screen again, on mon skills page to give ability description more room.
* go back and see if I can't raise the ability name box, (not the Ability LABEL)  and possibly exp bar too.
* then recapitalize all type names in ability descriptions like "Ups GRASS moves" rather than  "Ups Grass moves"
* it just looks nice, and fits the fire red style more
* 
* test hidden ability selection odds again, when able to build - DONE
* 
* changing trainer ivs to be random, as most are just set to 0, -DONE
* (change works I actually lost starter fight after this,for now will leave monitemcustommove as fixed, as I think those use max value
* and making random would actually make things easier) 
* 
* note researching abilities on bulb/db I've come to conclusion ability slots follow a pattern
* slot 1 is a natural capability/ability of the mon i.e intimidatation strong jaws a cute charm etc.
* slot 2 offers some form of boost or synergy
* while the hidden ability slot is meant to be something special/unique that allows it to fit into a different niche or a niche.
* consider comb over ability allocation to make sure correctly follows this logic
* 
* forgot, set rival to devault moves, as custom move works weird where when you remove move argument
* from mon, instead of defaulting to normal move learn it defaults to no moves and mon can only struggle.
* need to redo custom move logic so if no move arguemnt use normal setinitial mon learnset function?
* GiveMonInitialMoveset
* 
* had to do that because I setup randomized starter, either I make a look up table that,
* can check starter actual species and then make custom moveset for EACH starter option
* or set it to use initial mon moveset if exlcuding move argument (prefer the latter but the former would be useful too) - DONE!!!
* 
* (tweaked setup, now rather than just replacing fixediv with randomiv constant in createmon function,
* it'll default to that itself if fixediv less than 30, and a value of 30 and above is only used for elite four)
* 
* the struggle is ENDED! now if a mon in custom moves template doesn't have a move argument listed it'll default to normal learnset  
* just need to set rival trainer matches back to customs and remove comments - DONE
* 
* need to comb over custom moves compared to learnset in some(possibly many) cases it seems custom moves
* actually are just to make things easier -
* 
* as note above says  trainer ivs are set the same for all stats, and require a value of 255 to equate to 31 max ivs
* going to setup so random trainers noitem default move, use random ivs, will actually make things more difficult/interesting/balanced
* then can set it up so gyms/custom move trainers use actual iv distributions
* 
* or could keep all ivs random,(as that also matches matsuda intentions)  and instead
* setup custom fields to set nature, and evs. and perhaps abilitynum

* -will treat ivs as hidden stat for player side as matsuda wanted, ivs won't be adjustable with an item.-
* -you can change nature, change ability, but ivs will be hard locked to the individual mon.-
* -with my ev change you'll be able to overcome bad ivs anyway, and ivs are stronger to make more of a difference as well.-
* 
* -(checked my iv change compared to base game evs, effect in the stat formula. 
* -(base game evs add 63 per stat for 2, my iv change gives ivs potential for higher stat
* -(increase than fully ev training mon, so you can get really cool stuff now tryign to iv hunt)
* 
* think I will treat rival starter same as roamer, where the iv data is intentionally 
* -also need roll back the gen 3 change where roaming mon can run away while asleep gonna assume that's a bug in the code
* 
* mon personality is also fixed for trainers, but I think I would like to keep that constant,
* so for rematches trainers would atleast have the same ability,
* the personality value is derived from a combination of the trainer name, and mon species name.
* 
* Not doing nature tweak, can overcome nature stat loss with Evs anyway, now that can set Evs,
* Ivs have been reorganized so it maxes at 31 without needing the mask.
* 
* Last change is adding the ability filter, will allow for consistent ability selection, also adding logic to random ability for trainers
* which is an improvement as apparently trainers would only ever have the 1st slot ability.
* 
* also plan to consolidate trainer party structs to only do TrainerMonItemCustomMoves would make editing trainers much easier.
* 
* there isn't really much reason to have more structs than just TrainerMonItemCustomMoves, since I've fixed the move error
only values needed in selction are lvl and species, everything else can be left empty and can safely default to zero.
Check definition of struct to find base/default values.

Still need to add u8 abilityNum field so ability can track w repeated trainers,
but setup like iv field, so if left blank can just set a random value
Using multiple structs was to save memory, it wouldn't cost me too too much to consolidate
but to attempt to compensate change iv, to u8 field. its only u16 for the weird masking they do.
would require combing all trainer fields and translating from mask back to max 31
change in code would just be fixedIV = partyData[i].iv  removing the mask and 255 divisor
would only save me 1 byte for every trainer party, which would balance by adding the abilityNum field
but still a net positive

put abilityNum field below lvl, make constant defines so don't have to just use 0-3

since I want leaving blank to be set random ability, I can't use value 0 as set mon ability num
so i will need to make a function to do it, "i" value of 0 will default to setting randomly
then if not 0,  use setmondata ability num i-1    so  i value of 1, will be abilitynum 0 etc.

simple logic for this, adjusted my abilityNum defines to start at 1, for first slot rather than 0.
With that I can use GetMondata ability num, if 0 set a random abilityNum between 0-3
 
 if not 0, use setmondata abilityNum [abilityNum - 1]  then it'll set the correct ability based on the define name.

 since this is so simple I don't actually need a new function for this, should be able to do with like 4 lines of code

 do u8 abillityNum = partyData[i].abilityNum;  to pull abilityNum from list  (would default to 0 if leftblank
 then do if else
 if abilityNum 0  setmondata MON_DATA_ABILITY_NUM random % 4
 else setmondata MON_DATA_ABILITY_NUM  abilityNum-1

* DONE!!  need test, should set ability, think I'm worried about is the random ability part.
* 
* ok confirmed firered & emerald use different font, which explains why lowercase firered font is so ugly
* port I guess the lowercase charmap from emerald expansion, that way lowercase stuff can look better
* or maybe just port a few select ones, the ones that look bad are the curved ones,  n m r etc. I think c as well?
* 
* note make more space can remove "recorded"  battletowererecord stuff etcc as its for recordmixign mechanic
* 
* don't forget redo z-move stuff i.e implement it, people like them so put in game, worried about breaking balance since I'm already making all mon good.
* 
* learned pp ups effect on moves is limited to increasing basae pp by 60%  5-8  1.6 boost 15 to 24 1.6 boost  10 to 16 1.6 boost.
* 
* buffed sturdy to survive explosion need add to ai logic
* 
* for abilities that boost stats, think want setup a a function that doesn't exactly reveal the ability to the player
* but just acts as a signifier that one reached an activation condition,  with a hint in the color of animation
* 
* plan loop battlers check for actiation condition if active check stat that would be raised and play appropriate stat animation color
* just need figure where to put
* 
* for mudsport watersport or moves that boost stat, think can play animationn on turn move used, and on switch in.
* i.e if gcurrentmove is watersport and side check mon is battler grass play speed boost animation
* 
* will prob make a bs command for this and put function in battle_script_commands.c can easily put in switch script  no text for these
* 
* 
* General Notes end:
*/
goto NEW_STURDY_EFFECT  //logic in faintifabilitynotdamp for hpbar drop
goto NEW_STURDY_PT2     //logic in setatkhptozero for hp data update, effects like memento explosion not healing wish
goto NEW_STURDY_EFFECT_PT3 //last part of effect logic in tryfaintmon, for destiny bond

goto TRAINER_PARTY_DATA
goto TRAINER_DATA_STRUCTS

goto B_ANIM_CONSTANTS //for porting animation, need set constant for recognition in battlescript

//unrelated but any file that has ewram_data must be included in sym_ewram.txt

goto SRC_DATA_DEFINES //this where they must be defined for including elsewhere

goto SRC_DATA_FILES //IMPORTANT all .h files in src/data folder MUST be included in data.c here or can't be found
/* realized logic for damage on air targets was incomplete 
* correcting setup - DONE
* 
* Forgot to replace all instances of Levitate in basestats -
* 
* need replace gBattleMons[gActiveBattler].ability with GetBattlerAbility(gActiveBattler)  for ability check, so suppresants work
* compare to emerald for which valus should change - DONE
* 
* increase quick claw success odds - DONE doubled to 40%
* 
* idea meister fight similar to fights but with all my favorite mon  i.e mon with favorite changes
* think team will have sudowoodo shiinotic heatran etc.  
* will be full custom move and ability fight, but think won't use items
* will appear randomly on mirage island, same as legendaries can appear
* will setup like oaks lab, where soon as you walk up to a certain point, I'll come down from the stairs
* same as oak shtick, will have black version of rival sprite,  and use some of character I'm impersonating lines,
* play rival music this should be after the oak impersonation where I tell the player about new game plus
* like rival fight, should the player lose it shouldn't trigger whiteout, instead I'll heal their pokemon
* (since its already hard enough to get to mirage island dont want it to just be gone) 
* and give em the " better luck next time, smell ya later" and walk away actually no make it the teleport animation lol so I just spin away
* me appearing is not mutually exclusive to a legendary appearing so if I show up there can still be a legendary.
* 
* change iv formula, to give ivs more expression  will increase by 2.4 
* since iv allocation is random, I think I can leave ev cap where it is.
* decided won't actually make item to increase ivs,
* based on matsuda perspective, of it just being natural potentiall
* and that my increased ev cap was meant to fill in the gap left in customization. anyway - TESTED | DONE,
* 
* 
* more efficient player pc actions, be able to close pc while holding mon,
* make it put mon back where you had it then press again to close pc
* logic when picking up mon to move have it save current position before moving,  for both cursor and the mon
* when pressing B while holding mon, set cursor to original position, do put down animation and return mon to original position.
* 
* When using the move pokemon dialogue allow for depositing all your mon, as you can still withdraw mon before returning to overworld.
* instead of bringing up last mon text make "you have no mon left" if you hit cancel before putting mon back in team.
* pretty much jsut a safety to make sure you don't accidentally go out with no mon, which I think would break the game.
* 
* Add Hold A option for the orange cursor, to withdraw and deposit mon menus plan is let you deposit/withdraw multiple mon at once.
* right now when using selection cursor(orange one) it goes straight to box selection with a multi select option.
* you'd still need to order your mon properlu before you used new drag/drop option but that woudl stil be far better.
* 
* want it to auto detect free spots within the box you want to deposit mon into and just slot them into those positions
* automatically based on order of first mon selected and first free space encounterd top to bottom.
* 
* make new text for functioality, if not enough slots for selected mon in box,  bring up yes no dialogue
* "Not enough space in box, deposit anyway?"
* If you sselect yes, it'll do the loop depositing mon into the box until its full, it'll then
* loop through the next boxes until it finds free slots and deposit the remainder there.
* 
* And if the box is full, don't bring up a dialogue just say "Box is full"  and make you select a different one.
* 
* Use that new logic for when on the move pokemomn menu and you have mon selected and are trying to place them as well.
* Rather than the stupid thing of it holding them in a straight line and you only able to place them in a space of a flat line.
* 
* So if you have a group of mon selected, but there are filled slots preventing you from putting them down in a line.
* Use that same looping logic for placing htem within the box, just make it look for n number of free slots
* and auto place them, with the cursor going to the position of the last placed mon, so you know where they are.
*/



goto TOTAL_BOXES_COUNT  //values to consider
/*I think min I need is 36, so not quite triple, keep in mind adding cefirian forms as well, as few gen 9 mon

// I think if I can get that cfru thing, where you carry a secondary storage on you that may solve it, you can keep the important pokemon on you, and just swap from the pc.
// allowing me to cut down on the needed number of boxes.

//but I'd need to set the thing able to carry about 200 or 300 pokemon and able to register it, to change the after/catch action,
//so when it's registered caught pokemon go directly to this closer storage instead of the pc.

//that way pressing the register button would swap the default location new pokemon go, so if you have a pokemon you want to use, right away, just hit register before you catch.
//this still requiers save expansion, but its just a more efficient interface.

/*ok NOW I rememberw where I was going with this,  I'd need like 40 boxes to hold everyone, and thats only for catching 1 of everything,
* so rather than having to scroll through 40 boxes, it'd be better to have 2 holding places, to split the load in half.
* It would still be a pain, hmm unless I added some extra automated sorting features?
* hmmm. intersting very interesting
* Curruent box format has no sorting feature/no basic format, its essentially pure LIFO last mon caught is first in box/slot
* But if instead I made it auto filter by typing even if I had many many boxes, it'd make it easier to find things
* because they would be limited options.   as its grouped rather than essentially random.
*
* Ok this can only work based on type 1 there are 19 types in the game (including mystery, not including sound)
* 19 x 2 is 38, so that may work, can give every type (excluding mystery) 2 boxes
* Organize boxes in the order of the type chart i.e normal fighting flying etc.
* Which each pair of boxes together, before moving to the next type
* Naming convention:  Normal  Normal 2,  Fighting Fighting 2 Flying etc.
*
* All boxes aren't available from game start, typically the game checks caught count/pokedex and adds more boxes with time.
* ok maybe not, game opened with 14 boxes. hm ok so I kinda prefer it adding more boxes as you go. need to see where that is
* and why I assumed it worked that way, it must work that way somewhere.
*
* If I can get that, I'll start the game with no boxes, but add them based on type 1 of the mon caught
* can just use the 1 island pc is offline at this time script if player tries to use viridian pc for pokemon storage.
* before getting the pokedex.
*
* Now making 2 of every box makes sense from a bases template idea, but it may not be the most efficient.
* for the actual data/mon. Also if people add more or change things having it based on the actual total
* would future proof things.
*
* since number of mon in each type isn't equal as well.
* So the other idea is intead of 2 of every type, at game launch read through species data
*  reading & counting the type 1 of every mon, until you get to species end,
* then take the value for each type value and divide by 30, for the number of mon you can fit in a box
* to then determine how many boxes you need for that type.
*
* would have a variable for each type  would use u8 normaltype, fighttype, flyingtype, poisontype, fairy dark etc = 0;
* use switch case for type1
* use actual type values for case TYPE_NORMAL etc.
* and in the code block increment the type constants i madde
*
* i.e
* case TYPE_NORMAL
* ++normaltype;
*
* at bottom after switch, loop through  type variables, divide by in_box_count (30)
* and then use the final values to determine box count for each type
*
* (oh forgot there's macros for roundig I can use the round down so I get whole values from this)
*
* if <= 1  box count = 1 ;  if == 2 box count = 2;   if == 3 box count = 3;
*
* take some total and make that new value of total_boxes_count
* that would need to run before/at compile and do the whole malloc thing I think?
* Since its determining/changing a constant
*
*/

goto MORE_PCLOGIC   // note change effect from ctrl selecting mon leave withdrawal normal, make deposit do deposit all. loop party read type and auto deposit in type box
/*Issue left to work out, removing all mon from party, puts corrupted mon in slot, based on original first slot mon species
also puts grey question mark in 1st slot party menu when no mon there*/

goto PLAYERPC_CONST_WORKAROUND //workaorund for const pointer for setting item names cap for player pc also use for dex - attempted seems work for dex
//teste on dex realized its essentially exacty the same as the code I had already written in effect
//which means the workaround  isn't a workaround and most likely has the exact same memory problems that exist in the dex?
//fixed, redid had use after free issue instead of buffering,  just capped string at listmenu print

goto TRAINER_REMATCH //stuff
//notes lost attempt remade, plan for rematchable trainers  with overworld stuff game is already broken into badge based leveling
/*so do plus/minus average trainer level based on number of gym badges when you return to an area, (also based on your team level)
* this way everything would scale properly to your levels
* i.e considering the normal path you're meant to take you should be at certain paths/maps at a certain gym badge count.
* use that as the base scale and then plus or minus levels from the enemy team based on how many badges you actually have.
* only issue is custom moveset trainers but not hard to work around
*
*also consider doing for wild's go back to area with gym badge or 2 above, and at least 1(could make 2-3 instead? unsure) mon in the new lvl range
* and wild mon will spawn at the higher level, also consider having different encounter tables.  
*i.e add some evolved form mon in there where they weren't before, and maybe some rarer stronger mon too.
* could do something like every two gym badges area upgrades? up to a point, early areas so should overall be lower than the later areas
* once all boosts applied.
*
*plan alternate ways for getting through barriers, like paying off oak's aides to get rewards if you don't want to catch everything
*
* something occured to me, there are a "limited" number of trainers you can have, that's down to trainer flags,
* i.e the trainer info showed in trainer page, but that limit doesn't exist for number of trainer parties I can make...
* so theoretically I can make multiple different parties for a single trainer
* but then just use a function to shift the party value etc.
* I can setup non-static battles that way???
* imagine a trainer has default moves and 2 mon, then under different conditions they have custom moves 5 mon and its a double battle o.0
*
* ok double battles etc. are cool but its hard to plan out everything individually so what if, I just made a check in battle setup, if the trainer CAN 
* double battle, i.e search party size for trainer talking and player,  then set up an random chance for it to switch from single to a double battle!
*
* I could also do that for triple/rotation battles, and since everyone is rematchable it'd make them feel more unique, like hey I feel like doing it a little different today.
* file is src/data/trainers.h   first would need to make party field take the category/struct the name I chose uses in trainer_parties.h rather than needing it specified.
* after that I need alter these bottom 4 categories.
        .battleType = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sTrainerMons_TeamAqua1),
        .party = {.NoItemDefaultMoves = sTrainerMons_TeamAqua1}
* 
* while I"m at it replace battleType member with battleType u8 rather than bool8,   with values 0-3  
* 0 = singles, 1 = doubles, 2 = rotation, 3 = triples hmmm... potential 4th option  
*2 v 1 battles, mostly for evil teams (would be with mycustom 2v1 version though, where you get extra action at before turn end)
* if need be bring back dmg cut from double battles but just for 2 v 1 battles, but  they had 2 v 1 in sun moon so idk, might be fine -(nvm sun moon ai is dumb af)
*
* anyway, since would be using same value 0 and 1 for single double, would only require renaming category- DONE except found value were actually aligned with gbattletypeflags
* in battle_main or battle_setup I found it assigned the gbattletypeflags based on the value from trainers struct
* and since I made it u8, but trainer flags went up to u32, I needed to move around the values for the battle types I wanted to use
*and make sure they were all below 0x100 i.e 256 
* did that now just need setup a function that for rematch, has a chance to change the trainer struct value for battleType
*setup checks for determining which battle type the trainer & player are capable of doing,
* and then do switch for setting different randomizer based on that, which would set the battle type I want
* now I don't need a bunch of different variations for everyone,
* for space can do most adjusting with functions, can adjust lvl and battle type and ai with functions
* but for custom moves and increases to number of party mon that would have to be done separately
*  but I could also reset moves field to 0, if they were already in the custom struct, to make use default lvl up. hmm
* so I could make everything custom, actually set custom moves, but then use a function check to not use them and instead use default.
* until rematch, which would be a flag check for if you entered the area before could also do badge check either or both *shrug
*
* if done that way, would greatly cut down on amount of extra space I'd need to take up with additional party data,
* would just pair down a fully custom value, since I have npc function already set to set random values on certain things
* if move field is 0, sets normal learnset, if ivs less than min, sets random ivs, if abilitynum 0 sets random ability.
* and item alraedy defaults to none if 0, so I could fully customize these and then make psuedo default parties.
* and adjust level as I chose...  holy shit o.0
*...now what happens if I directly set party size, to a value lower than the actual number of mon in party data array?
* if I can do that,...and it 0's out the values above the number I give then, I can also easily set custom party size..o.0
* if so I can make full parties in a single party set and just change the value with a function so party size is what I want.
* and it counts on order of mon top to bottom, so would be simple to get how I want it.
* like say I add a shuckle on to brocks team,  party size using nelms for his struct would then be 3 instead of 2.
* but if I can set it to 2, the shuckle would be in the struct but just left off for the battle.
*
* IT WORKS!!  I can set the actual trainer party to as many mon as I want, and if I change party size it'll just only right up to that amount!
* ok new plan was going to keep other trainer structs but with that realization there's no reason to use anyting other than TrainerMonItemCustomMoves
* I can fill in everything and then just zero out the data with function checks, to set it how I want o.0
*
* it saves a bit of space, for fields you're not going to use, but with code I can do so much with it
* there's no reason not to considering the extra utility I get out of doing so.
* now all changes would need to go into CreateNPCTrainerParty in battle_main
* now removing the extra structs is also a major plus because it allows me to GREATLY pair down that function
* so I would just have a single case for the struct rather than different valuyes for each one.
*
* ok doing this, need setup function that checks thing/sets default value for party size  gtrainers[trainerid].partysize
*   DEFAULT_SIZE would be the normal party size for base game, I could make brock have as many mon as I want,
* but base game he has 2, so defautl size should be 2, each trainerId would have a default_size value for what they had in base game
* then I expand based on progression criteria for rematches, up to the max, which would just use the actual value in the
* struct nelms party size, so I could just skip the partisize setting and it'd just use the normal value for them.
*
* thing still to figure is it better to just add a member to the trainers struct for defualt size, which I could easily just fill in.
* but would take up ewram for gtrainers
* or should I make a function with u8 Default_Size  and then just make a massive switch case in said function with all Ids from gtrainers
* and have it return party size to use  so function would need default size & party size members
* and then each case block would need default_size listed at top in brackets then a check for rematch what value party size should be
* and at end of case block set gtrainers.partySize to default size or calculated value for partysize for that trainer
* think need include a break as well, so if it skips all criteriea for filtering it'll just use the size actually in the array for true party
* make function take trainerNum like npctrainerparty, the argument it uses for that is gTrainerBattleOpponent_A
* so putting the function in npctrainerparty I can just make switchase use traineNum and itll go to teh proper trainer id
* so at end of each case block I can put  gtrainers[trainerNum].partySize
*
*this function that sets party size would nneed go at top of CreateNPCTrainerParty function right below ZeroEnemyPartyMons function
* now issue i'm working with now is,  should make multiple functions for filtering of each part
* or a single function put right at the top, that filters everything, since its more or less the same criteria,
* and Im gonna be using just one struct
* the function would be filtering what the create function reads of the trainers struct data, not actually changing that since its const (struct isn't const just gtrainers itself so maybe not anissue?)
* I could make multiple functions that return void but take trainerNum argument, or some similar but may be simplest just do the one
*would need variable value for each member of trainer struct lvl item move abiitynum partysize etc.
* then I can run my filters and assign the values as I desire  
* -(got info amount of physical text in funcitons doesnt matter for size it gets compacted for compile, so do everything with just 1 function not in struct)
* 
* next step need remove partyFlags from trainer struct, need do that, because partysize uses that as pprt of argument (kinda)
* so remove that  to save more space, for setting customitem moves as only trainer struct will offset the increase in values slightly
* since major change, commit current things before attempting
* 
* other note, for idea to have emerlad in game idk if fire red actually has trainer flags for all the emerlad mon still in it, it might and seems to?
* but in case not idea for reusing trainer flags,  rather than just have the flag itself be check for trainer, split it between the regions
* so flag 0x1 alone wouldn't be the check for if battled trainer, it'd be set flag 0x1 while on a map sec that is wihtin region for fire red
* then can use flag 0x1 for emerald trainer, and it wouldnt count as set until encountered them while in max sec that is within region emerald
* thus allowing to reuse flags based on map sec/ fire red, or in emerlad ruby saph  (I think)
* idea is make a two part check, so when flag set, check map sec and set 0 or 1 for encounterd in fire red vs emerald
* or 1 for encounterd in fire red  2 for encounterd in emearld and 3 for encounterd both
* nah do like how battle_main does the trainer party flags  held item is a value custom moves is another value
* and custom moves w held items  assigns them both  like so F_TRAINER_PARTY_CUSTOM_MOVESET | F_TRAINER_PARTY_HELD_ITEM
* ENCOUNTERED_IN_FR could be 1 << 0 (i.e 1)  ENCOUNTERED_IN_RS could be 1 << 1 (i.e 2)  
* so make new macro check to replace basic flag check,  so the flag can be reused 
*
*make choose ai flags for individual pokemon, instead of party/trainer - look into how ai works consider if doable, think would make sense/be better may require full overhaul though.
* also add pp bonus setting to custom moves,for more strategy/control //important
*
* also did steadfast buff made activate off of super effective and flinch simlar to how I did anger point accessibility buff
* had also plans to go back and redo some back sprites that were bad I'm lookin at chespin right now
* think that's all the notes I lost but of course can't recall...
*
* breeding/overworld buff give everstone and destiny knot overworld effects, be counterparts
* since putting all of everstones effects onto eviolite, i.e stopping evolution it needed its own effect
* now holding everstone on lead mon will have wild mon spawn with the same gender as it where possible. idea ever is remaining the same/being the same
*
* destiny knot, when held by lead mon in party wild mon will have the opposite gender where possible. idea finding your destined one.
*Vsonic Important - also of note still to do add gen 9 egg move stuff 
i.e post gen breeding moves don't give incineroar fake out access, 

 //co dependent status - cure cancel out brn cant be with freeze  sleep cant be w spirit lock  psn cant be w toxic
 //moved freeze decrement to atk cancelr like sleep  still get 3 turns i.e free switch and an attack, but more beneficial if opponent is faster but it balances out
 //if their faster you take an extra hit on turn they get frozen,  if they are slower they get the hit on the turn they unfreeze

 //removed logic inside MOVE_END_MULTIHIT_MOVE ported from emerald that broke accuracy for fury cutter issue was multihiton part, remember to redo later
 //make change where only fury cutter goes through accuracy check each time
 //think simple to do   if gmultitask != 0 && gmultihitcounter != gmultitask (should only be after first hit of multihit)
 // and move != MOVE_FURY_CUTTER

 //nvm just not doing that, remembered originally wanted more consistent effect for multihit they can all misss
 //skill link and parental bond will be the only exceptions
 //fury cutter will also work differently. as it has the accuracy drop varying number of hits too would be too much
 //every other multihit will have varied hits, and a chance to miss each hit, to make less punishing as my plan was to buff said moves, they get an accuracy boost
 //nothing lower than 90

 //reworked priml and meags stats,  normal weather works by who is slowest
 //change primal weather to work by who's fastest as normally weather cant be overridden

 //gameplay loop change - mon in pc game exp while walking like daycare
 //but dont make them learn moves, that way can just take them to  move relearner to learn what you want
 //and no one that has good moves would lose any (actually do same for daycare, its just inconvenient)
 //tweak pc introduciton messaging so its that you are sending them to oak and he 
 //says he'll make sure to let them out of their pokeball so they get some exercise
 //idea is same as anime, they aren't literally in the box the whole time, the pc is for 
 //transferring/moving them, in anime they are at oak's ranch

 //idea make mon immune to status moves of the same type as them i.e sand attack wont work on ground
 //thunder wave wont work on electric (thats already done since electric cant be paralyzed by electric moves)
 //normal wont be immune to any status move
 //just look into things moslty tied to element, see if can come up with something thats consistent and logical

 thikn I'm gonna scrap that idea, it'd be too much on top of already making status revolve aroudn type,
 if you had to worry about type immunity on top of, being able to play the move if the enemy was of same type it'd be too hard to playthem
 //I think I'd have to do one or the other in that case, either make same type immune to status or make type immunities immune to status
 //ok I like status being blocked by immunities more so scrap extra stuff and just keep that


 //in addition to built in nuzlocke/death mechanic, actually setup nuzlocke mode with flag check in options menu
 //exclude fainted mon from pc exp gain, make them stay fainted in pc
 //so setup exp gain logic for that to work only if mon hp isn't 0
 //don't heal party if white out, item effects that revive make cant use put nuzlocke mode
 //flag check not set in item use

 //co dependent statusing - cure cancel out brn cant be with freeze  sleep cant be w spirit lock  psn cant be w toxic
 //still working on new version of conversion and inversion ability for ditto

 //make sunny day and moon light field moves, to swap day night schedule
 //already done, but for effects taht set primary status made it so status moves have to pass type check (not be no effect) to work
 //for example nuzleaf being grass dark would not be able to be put to sleep by hypnosis as its dark type gives it psychic immunity
 //with powder move change that leaves it imune to nearly all methods of sleep outside of yawn and dark void 
 done with jumpifmovehadnoeffect BattleScript_NotAffected, only could swap to do in C /setmoveeffect function instead for more tailoring
 //but could just work with command/macro it should still be fine right now the command is before other checks,
 //I waffle on it but I think that's fine, it has no effect there is no point to putting it after other checks, and the animation just for that
 //only change planned left for that is making normal moves be the exception just make them work for everyone, and bypass type check.

 //jumpifmovehadnoeffect doesnt allow for adding specific logic, so plan make bs native function to replace
 that way can add what I need   if gMoveResultFlags & MOVE_RESULT_NO_EFFECT and gcurrent move type  != type normal  jump to fail condition done replaced setmultihitcounter2

 ok nvm removing those will instead do in C, as otherwise it'd bypass ability checks  in setmoveeffect, so it'll be the last check
 //before status1 checks  ok done, and made sure to include that its only for status moves, need test but should hopefully work

 still need find way to setup ABILITY_RUN_AWAY to be immune to pursuit switchout dmg
 //also think would like to buff pursuit, so like with switch it'd check if enemy was attempting to use pursuit, so
 //you'd take pursuit damage even if you rolled a succees on running - think done, setup jump script in switch command for ability

 note broke infestation trap and new bug status infestation into 2 different effects
//THe new bug status is infestation, ist a status4 for now, and it has the effect of lowering statused target defense by half same as burn does for attack

 the move infestation has been renamed swarm, it will do trap effect, and will also lower defense for duration (not done yet)  //redone done

 need setup ABILITY_SUCTION_CUPS with emerald logic where it increases odds of successful fishing if in lead
 ITS FIXED WRAP GAME FREEZING BUG IS FIXED IT WAS THE POKEMON.C I DIDN'T PROPERLY INITIALY THE STATUS4!!

 I just need to figure out the type issue for the most part now.

 task list:
fix type chart reading bug,     -fixed ...I'm a retarded idiot, it was all because I used gbasestats instead of gbattlemons 
fix move end wrap status bug that freezes game - done
re-add the graphic changes for pokedex
readjust summary screen graphic so longer ability names fit
fix windows and y coordinate values for pokedex graphics & double check new dex entries fit

trying to figure out type issue, its not modulate dmg by type I think, the dmg multipier is being adjusted, 
according to what its reading the type as, the issue is I know the types aren't matching what the effect should be

it was reading every mon as bulbasaurs type...because  I used gbasestats[gbattlertarget].type *FACEPUNCH
because gbattlertargeet can only default to a value between 0 and 4, and its in the species field so 
it makes type chart read the type of every target/battler as bulbasaur!!! which is why bug was always not very effective
and grass was pretty much non existent it was quad resist on everything

for some reason ghost moves seem to still not be reading correctly?

still need rework poison setup or set back to full normal, right now poison animation isn't playing before turn dmg

 thinking remove tynamo from bulbasaur ball found out it isnt actually steel no idea why Ithuoght it was.
 considering put in squirtle ball instead  nah doesn't get water moves, its best where it is I guess

 need check move olearn its doing weird things when I had it working 
  -replaced og jumps w wrong cmd args alues, thats fixed
  bug with battler switch still an issue
  -thief logic not right, theif takes target item gives to player battler
  even when holding an item.
  change to toss into bag, not give to mon if its already holding an item

 shadow_tasg reading wrong battle name for message for some reason check if just for oak battle and works norma elsewhere
 i.e put litwick in starter area

making own custom icons  for phsy special split.  new gen need know contact moev as well
will be small icons placed in blue space below accuracy for summary screen 
icons will be smaller
P for physical
S for special
C for contact
first two will be if else  based on split  and in first (slot)
but C will be  there regardless of split in second (slot) beside the split icons
decide better colors that I would like more
think I would like dark icon for special, won't have anything for status
use IsMoveMakingContact  for setting contact icon
since made new category of move that do grounding think should add icon for that as well.
check for that would be if flag dmg_in_air or 2x_dmg_in_air

may make icons the same color etc, so they can slot together and look seemless
think I'd just do dark grey background with white forground color for the lettering

changed scratch to ghost dmg worked fine so issue seems to be effect /moveeffect instead?  something in setmoveeffect logic
seems to be happening on lick and astonish?  flinch hit paralysis hit

also issue of moves missing when it shouldn't be possible i.e 100 accuracy moves  quick attack beat up
but wondergaurd etc is also not workign right, used tackle as a ghost move against wonder guard shedinja and 
it should have been super effectve but instead it had no effect?   so didn't read as super effective 

...I am going TO BLOW my FUCKING BRAINS OUT   the wrap bug came back??!
for some reason using ghost move on dispirit guard shedinja

ghost moves are also still not working on wondergaurd shedinja
I can only imagine its reading it as a pure neutral move

fury cutter still not workign fully far as the message, way it works if it doesn't kill  and doesn't do all hits
it won't say type effectiveness message it'll only show that it missed, if it kills or gets all hits it'll show message.

what I would want is show effectiveness on first hit, show miss on last hit if does so for multi hit
 * could do that, would just need make alterante result message command, that triggers inside loop, but is only on first hit
 i.e when gmultitask == gmultihitcounter (and is not 0)  since it would be below accuracy check it auto only trigger when hit
 should be simple and good, move would check accuracy do atk string and animatinon then when hits do multihit result msg
 show super or not very effective and continue, would need to include to skip the multhit result if move result is no effect
 as I think normal result message catches that  (it does)
 - ok did looks like its goood.

 also for shedinja make sure when swap woner guard not only does mon hp become one,  (not max hp)
 they also get the effect of healing items no longer working on them, so can't heal in battle
 pay close attention to revised type chart to see any mon that would become fully immune with wonder guard
 I think dispirit gaurd should swap hp and max hp and still allow for healing,
 but again need to check to make sure there are no mon that have 0 resistances as it
 doesn't have the thing of being easily taken out by weater or typeless dmg

no that's not it somehow ghost is only hitting mon that aren't grounded and aren't normal type?   or steel?? works on gligar doesnt work on magnemite
potential issue with grounded function logic?   gligar is flying type,  while magnemite should just be in floating species so a different check

that didnt seem to work?  but think can replace type check with else if, instead of using ifs, but worried bout messing with the structure too much
when it doesnt work 

for some reason ghost moves worked correctly in rival fight, but not outside it?  yeah ghost works right in BATTLE_TYPE_FIRST_BATTLE

multitask isn't working...dmg split is working but it isnt attackign multiple times..
 finished new seutp for rock smash cut etc.  type based effects, still no clue on multitask not working... - fixed, think I never  properly setup?

leech seed also isn't working, is being applied twice, and not healing the target instead is doing damage to them too,?
leech seed beign reaplied because its not setting status properly its being used does the end turn effect (improperly)
and then its over   ok I see what's happening its healing the wrong taret,  its healing the mon seeded, but also dealing dmg to them
so status is set oddly,/to wrong target?

 idea from sacredalmighty attempt add happiness/friendship meter,  this put in summary screen, on first page
 diretly above  pokeball,  think heart icon that fills up with happiness,
  grahpic should have heart beat graphic (the bar that moves on the machine)
  will put at vertical where friendship evo is, fill up use logic for exp bar fill up to setup graphic
  its not vertical bar but hopefully its not more complex than that, if I need to change graphic to be a vertical bar
  // a vertical slider top bar starts at starting friendship portion  everything else is black,   
  heart icon is at top of current friendship position, bar will always have a gold line on it,
  the gold line is the friendship evo point. if use bar, make heart icon fancier, 

on catch add mon held item to bag, with brief text trigger after pokedex logic

 //PokeballIcon_CaughtIn(y);// attempt to setup pokeball icon based on pokeball sprites/caught mon in for pokedex & summ screen

 looking into gameplay /gamefocus based on videos by acoutsticharmonia pokemon focuses more on level than skill

 which is true, level is the biggest factor of success even to the point where its a multilier in the damage formula (biggest one even)
 so on that what if I made level LESS impactful, outside of just meaning bigger stats?
 like say if I removed the level scaling from the dmg formula?

 doing that would mean the stats of the mon themselves matter much more allowing you to hit higher above your weight scale so to speak
 which would also let the game be more about strategy intead of just get levels do big damage

 for that look into hwo much levvel affects dmg formula - ok found it.  in pokemon.c calculatebasedamage function used for physical and special
 damage = damage * gBattleMovePower;
    //this multiplier alone gets close to /50 cut so higher level means higher less scaling ie stronger with level i.e level becomes MORE important with time
     damage *= (2 * attacker->level / 5 + 2);

 //alternate lvl scaling
    damage *= (attacker->level / 5 + 4);  //keeps things mostly the same at lower levels, if not slightly higher, but scales lower as you level
 //2ND alternative scaling
    damage *= ((attacker->level + 2) / 4 + 4);  //scales up slower on low side scales up higher w lvl later but still lower than norm
 //3rd scaler
    damage *= (((attacker->level * 110) / 100) / 4 + 3); //lowest early scaling slightly lower than 2nd method later scaling, still good deal below base

    (((attacker->level * 130) / 100) / 5 + 4);          or   (((attacker->level * 170) / 100) / 5 + 3);

    general consensous (((attacker->level * 160) / 100) / 5 + 3);  //closest to original scaling, w slightly higher early scaling for early difficulty, and lower later but not caps mostly at 85% drop from norm

        - starting point starting multiplier i.e base dmg - my version on right
 lvl 3 = 3                                  lvl 3 = 3
 lvl 5 = 4                                  lvl 5 = 5                              
 lvl 10 = 6                                 lvl 10 = 6
 lvl 15 = 8                                 lvl 15 = 7
 lvl 20 = 10                                lvl 20 = 8
 lvl 25 = 12                                lvl 25 = 9
 lvl 35 = 16                                lvl 35 = 11
 lvl 40 = 18                                lvl 40 = 12
 lvl 45 = 20                                lvl 45 = 13
 lvl 70 = 30
 lvl 100 = 42
                    

            real ex lvl 7 me vs lvl 9 foe 
   4.8  vs 5.6                  5.4  vs 5.8


   (((attacker->level * 110) / 100) / 5 + 4);
   //works brings up lower levels but still scales down for higher
   need to scale lower by lvl 10

   duh just use a different formula for those levels

   can use this formula but at lvl 9 or so change to + 3 for the end

 n^3 /sqroot(n^3) /5 - 5

 n^2 - n /2 +1

 (attacker->level * 140) / 100) /sqroot + 3

 (to see if this lvl dmg scaling keeps up with or exceeds stat growth with lvl  just compare stats now with growth based on stat formula)
  [n = (((2 * baseStat + ((iv * 240) /100) + ev / 4) * level) / 100) + 5;]   //can rmeove ev iv portion

    [SPECIES_LEAFEON] =
           //hp, atk, def, spd, spatk, spdef
         STATS(86, 110, 130, 95, 60, 65),

            remember all values are divide by 50 for final value for damage
    atk stat:
        lvl 7 = 20
        lvl 10 = 27
        lvl 15 = 38
        lvl 20 = 49
        lvl 25 = 60
        lvl 35 = 82
        lvl 40 = 93
        lvl 45 = 104
        lvl 70 = 159
        lvl 100 = 225

        ok trend seems to be stat growth is lower as you level, so higher scaling is to keep that sense of progression


 dmg multiplier inccreases by 2 every 5 levels, if you assume lvl 5 is base dmg, your dmg multiplier doubles every 10 levels
 btu that doesn't exactly mean total dmg doubes at that point as just leveling up makes available a greater portion of your total stats
 //essentially the lvl multuiplier is being added on top of a constantly greater scaling number (more or less)

damageHelper = spDefense;  (defense stat)

 damage = (damage / damageHelper);    high dmg multiplier gets cut down here since it divides by defense stat and includes stat buffs

 damage /= 50;  then seemss to also be done here again?  ok this makes slightly more sense, base move power was 25 with tackle being first move
                        //effect seems to be to balance dmg   higher your level you do larger portion of true dmg but never 100%
 
 so before level scaling and these large divisors damage as a value (move power) is multiplier from 25 to about 120 as of gen 3

 super multiplier change has larger effect than I first thought which is great, but still need to adjust lvl scaling of base dmg formula
 purpose of doing so is to act as counter balance for late game where you get far stronger moves, to ensure the multiplier change is still felt
 also considering stats have a higher ceiling, because of my iv change to stat formula
 
 ex. base game full super multiplier 4x weakness was enough to one shot near anything with a low power move
 same situation my game its a 2 shot, on average you take 1 extra hit but direct comparison you take 64% of the dmg   4x vs 2.56x
 so in that scenario something with bad defensive typing but is hyper offensive can still be a worthwhile pick and may be able to win

 very interesting, level bonus scales high but so do the damage cuts, but even with that level largely outclasses defenses/any other gain/metric
 which isn't in itself bad, because it gives a simple means of progresssion and feeling of growth, where you can obliterate lvl 5 and 10s when you get to be higher level
 where they used to be a struggle.

 run tests,   base dmg 20   damagehelper 100  multiply base by multiplier then divide by helper and divide by 50 to see end value
 (I changed super multiplier to balance game but that changed ratios i.e super hits vs normal hits vs stab hits, potentially would have been 
  better to instead change these dmg formula nunmbers?)

 -make my version terraform called geo-form or something


 statusing isn't working right, poison is dooing something weird, not activating
 and instead using attackers ability as check for if it should work?
 foe gligar used poison point on turns when it shoud poison
 me it instead said, foe gligar's toxic_boost had no effect on my pokemon? strange - somewhat fixed keep an eye on

 trainer repelent counter isn't working right, well it doesn't start at 0, ?
 pretty much its activating even when I don't have the item for trainer repellent  
 for now commented out in trainer_see.c

 fixed trainer repelent issue, part of the setup was missing but that wasn't problem, 
 issue is I forgot to update constant for var_ends /var count so the trainer repel var was being excluded from new game clear
 so it wasn't being assigned 0

 wonder guard has weird issue, which seems to be in my comparison repo as well,
 where killing wondergaurd mon gives exp normally but then for some reason it gets turned into a trainer battle.
 and the shendinja gets replaced with your own party data, if you faint the opposing mon its treated as taking out your own mon
 and can trigger a whiteout.   running causes no problems   - still need fix thi9s...
 -did further testing, it copies your mon data etc. to opponent side, but mon still has shedinja moveset but seems to have your stats as it does less dmg
 need figure this out  - fixed it was calc stats setting current hp to 1, if ability wonderguard that broke it...

 seems to also keep its wondergaurd ability? or the hp, as a single hit takes it out

  - double check fury cutter, wonder guard shedinja  hit me fury cutter animatino seemed wrong somehow
  like it played/struck multiple times per hit? may be imagination/mind playing tricks - its fine

 also related to plan of setting up custom physical/special contact non-contact icons
 since will need that in battle, and navigating to summary screen move info page  is tiring
 setup so pressing L, (or maybe select [select is move swap, use R instead] so L can still be for help menu? ) should navigaate directly 
 to the move info page (the page with move selection already selected)  pressing b once should take you back to battle.
 with cursor where you left it

 for streamer mode/nuzlocke mode rather than having exp limiting for level caps introduce sour candies that can lower level.
 and then make it so player team level is set to the level cap if they are above it.
 that way takes the stress out of it, if players want to grind levels and evolve or get better moves they can do so.
 and still be at the level cap, and if you are going the hardcore route, and you have an evo within the cap
 but you SOMEHOW manage to cancel your evolution, its not problem, just level up again, and then you can go do the gym
 with your evo as if you did it right the first time. !!

 note for the longer move names, since they only fit in the 2 right most slots in the battle menu. (2nd move slot and 4th move slot)
 after a move is learned run a check for move length and if the moves already in the right slots 
 aren't above the move limit, swap position of the longer move with one of those, random % 2  for which it takess if both are available

 that way player doesn't have to see that it doesn't fit elsewhere,  will put as function of move learn task thing
 after confirm move slot and go back to battle screen for 1 2 poof/learned move
 will need to put move swap loigic in summary screen as well, so if player swaps moves it'll go back to avoid visual bug
 dont think can do mid battle, unless I literally don't let the moves be swapped into certain slots...welp guess i'm doing that
 so that means putting it in 3 places, move learn, summary screen and battle menu*/
 goto MOVE_SWAP_FUNCTION

/*
 endure message also isn't working correctly? its showing mon endured the hit, whenever it takes dmg, rather than just when it would take dmg
 that would otherwise kill it.

 ok overall endure just isn't working, kakuna used endure on like 1 hp I still killed it

 bide isn't quite right, its not getting the priority boost on the turn it unleashes energy // nvm seems it is working

 something odd with bind, it partially reintroduced gen 1 bug, its locking in my moves and preventing me from picking a move if I'm binded
 yeah bind status is doing very weird things, its locking you in to whatever move was picked BEFORE you got binded
 i.e I use lick, I get binded, I select fight, and it skips straight to battle passed the move selection and uses lick

 //doesn't work perfectly, used bind scored a crit on me and game froze..

 what's crazy is that's actually a really good effect, especially on onix who is fast, think of it like it binds the taret up and squeezes them,
 making them too panicked to respond to directions from the trainer, so they just keep using the last move until released.

 so setup bind status as being locked into move,  and move is glastusedmove for battler  (encore its doing encore I saw battle message this time)

 I wouldn't have thought of that...once I figure out why that is happening, thinkj I will make that the standard effect for bind
 (normally encore fails if target hasn't chosen a move I'm assuming that's the freeze condition, for bind I plan to make it default to struggle if no move chosen)
 (yup confirmed that's the freee condition)

 redid trap status effects, need test, and still need setup bind effect to do encore like effect.

 Encore temporarily prevents the target from using any move except the last used move.

Encore fails if the last move the target used was Transform, Mimic, Sketch, Mirror Move, Sleep Talk, Encore itself, Struggle, or a move that has no PP left.
 It also fails if the foe has not used a move yet.

If the Pokémon affected by Encore runs out of PP for the affected move, the effects of Encore end immediately.
 If the move the Pokémon is locked into by Encore 
 is currently blocked by Disable, Gravity, Heal Block, Imprison, Taunt, Throat Chop, or Torment,
  the Pokémon will be forced to use Struggle. 

  for bind setup to default to struggle if they haven't selected a move yet, if they run out of pp, also default to struggle
  if they used one of the encore blocked moves, again default to struggle 

  - ok thikn finished bind effect need test -tseted doesnt work just freezes, 

  faint stuff isn't working fo rplayer - 

 ...absorb effects aren't working everything is triggering as if liquid ooze, on top of leech seed not healing...
 and the dmg is triggering and fainting before the hp bar even updates or triggers faint animation,
 so I did absorb with 3 hp left, the dmg I would take back would kill me, but it triggered whiteout before hp even fell...

 that seems to be happening for all things done via passive damage?  had bind status and got killed but my mon didnt do faint animation before whiteout
 ok so faint animation is just not playing as a result of battle now?? weird

 still no idea, what's wrong with absorb effcts, it seems to be linked with sethpdrain and or manipulateddamage commands
 but there is also weird case where if use absorb and get killed for some reason it triggers grudge logic, despite never setting grudge
 so apparently grudge is getting set ?
 - its only doing that on the turn I use absorb and should be healing from it,  but it doesn't heal intead it sets grudge?
 and if I die in that turn it mon loses all their pp - fixed think prob was change made to  sideeffecting command had wrong targetting
 atk0C_datahpupdate - sets ghpdealt think that is main isssue, since sethpdrain isnt properly cutting gbattlemovedmg so I take full dmg I do
  - fixed issue was jumpifhealblock, which used jumpifsideaffecting  I didn't properly setup after making sude status 4byte command rather than 2 byte

  - GetBattlerSide(gBattlerAttacker)  /should be useful for later

 - just realized most electric moves are named after thunder which has nothing to do with electricity instead of something like lightning
 like thunderbolt which means literally nothing...  go through rename electric moves  remove thunder
 think only reason it was used was for character limit, which I've expanded
  - think most games did this? prob for same reason back in the day, think will keep most unchanged
  in most cases it'd just expand the number of moves that break the move limit

 - look in to re- rebalancing ohko, think do like persona,  very low odds, doesn't work on stronger foes / bosses
  but a good chance to work on mon weak to the type, think double chance of working if move result super effective
  but counter balance by making it always go last, i.e a negaitve 1 priority move if only used for mon you are already strong against
  its not such a big deal, mostly allows you to shave off a 2 or 3 hit into a 1 but makes you have to take a hit for it
  shuoldn't be guaranteed can turn  horn drill and guillatine into  non normal type moves

  -ok done, made double chance of hitting if super effective and a higher level than your target, can't hit not effective
  and has half the chance of hitting everything neutral, raised the floor so can only work for 3 levels below not 7
  //and made the moves always go last, so you have to take a hit
  - so they're essentially just moves for fun,

  //attempt rework grouding, because levitate/floating change, make flag 2x in air and flag dmg in air set smack down to ground floating mon
    //all moves that have them are simple and can have their effects moved to the argument and done with arguemnttomoveeffect or completly replaced w effect hit
    //plan put logic in damage calc?  dmg modifiers will be done, by then, so safe to do there double check smackdown move effect  think its already setup
    //to not trigger till end of multihit but make sure
    //there's a couple different ways I can do this  have it take place of effect i.e gbatlescript.moveeffect will set smack down w moveend function
    //but that would mean I can never use the flag with a move that could have a complex effect.
    //alterantively I could put it into the argument so in damagecalc check move for flag, if flag set  argument to move_effect_smackdown
    //and then it would trigger same as if with moveeffect just goes through argumenttomoveeffect to moveend instead of setmoveeffet into move end

    //other option is just setting the status leaving both free. would require more setup, also couldn't use moveend to do any animations/text I want.
    //think would have to make timer for effect, set to 1, and put in end turn for status smackdown, counter should only do message etc.
    //when status3 smack down is set and counter is 1, after message plays decrement counter so doesn't repeat
    //to ensure hmm could potentially make moveend effect that just checks for flag?
    //if that works wont need smackdown move effect and can have the most flexibility as won't need to take up space in  effect or argument

    ok yeah can do that simply just make another main case for atk49_moveend  something like MOVEEND_GROUD_TARGET
    //once do that won't need various VARIOUS_GROUND_FLYING_TARGET_2XDMGFLAG   can just roll it in together

    did that done. and adjusted to ensure multihit doesn't trigger early, it needs testing, but I consider grounding rework done (excepting putting type logic back)
    properly setup for fly bounce sky drop to remove  smack down status, so you either switch out or use those moves again as a gamble to get resistances back
    also setup for them to cancel rolled in various lets them cancel flying moves as well, plus they have priority over in air mon
    last thing left to do is, put the grounded exclusions back for flying mon i.e fighting and electric doing neutral to flying when grounded

    -fixed issues with grounding w new flag setup seems to work

    make sure check other effects added for ground types, check think I added a sandstorm acc drop against ground mon? -yeah cut it down some
    double check for balance, also think need add more  moves with FLAG_DMG_2X_IN_AIR & FLAG_DMG_IN_AIR for ground mon

    think something like rolling into a ball and speeding up a hill to fly into the air to hit enemy
    use some variation of rollout with fly animations to roll up into air and then come down on enemy   lol spin dash XD  - need put in description

    -now back onto reworking bind effect,  then onto double checking contact ability status stuff, static works, but mostly unsure about
    the poison abilities. need review 

    don't forget change hazard i.e spikes stealth rock toxic spikes, to not be mutually exclusive, 
    balanced by sharing counters so setting stealth rocks  with toxic spikes would only allow a single use of regular spikes, rather than 3

    -need fix endure forgot that isn't working for some reason
    -make message for plus minus if doesn't exist in fire redm, pretty sure there was one in emerald?

    -tested def seems like NO contact status setting abilities are working static etc.
    //bug confusion immunity isn't working it still hit itself and takes damage  its supposed to do confusion animation but always go to  attack works
    -what's happening instead is whenever mon breaks through confusion to attack its freezing the game...-_-
    -sweet kiss is working again at least atually displays animation
    -double check roost, effect think was supposed to display message about being on ground, copy smack down flag setup
    -check message for roost timer end considering electric change with grounding consider idea roost timer not reset before runs out
    -setup full hp effect to just use move for grounding effect rather than to heal.  also consider lower heal

    they use tryhealhalfhealth  command, potentially change to 1/3rd  on other hand, its not meant to be gotten early
    so mid game when there are stronger moves its not as big of a deal. consider replaying persona to see as there's feels balanced
    you get different levels of heal to that scale with game, but you're also facing multiple opponents at once, sometimes 4 v 1

    move learn is even more broken than I thought, for evo mon learn move that wasn't in first slot i.e got exp but wasn't in first slot when evolved
    after battle, it displays the moves of the lead mon rather than the evolving mon...

    actually evo mon was in lead position, adn then was switched out thankfully didn't replace move of other mon, 
    it just didn't display the correct mon's moveset

    //bide priority on unleash still doesn't seem to be working, ... -works now, problem was bad logic in priority check
    trap animation setup rework is working, at least

    boost exp game, cut wrap around for exp down from 17,  you still gain exp from normal travel team at FAR FAR greater rate,
    it should be just below even -adjusted think is ok now
    - type based statsuing seems to work thunder wave fails to work on geodude so that's good
    -change fnt box to still display mon level, since moved graphics around they are in different places now

    //for idea of pokevial charing on winning batttles, just put a counter  in battle_main  HandleEndTurn_BattleWon
    every time battle outcome won and trainer flag is set, increment when ++counter equals 2 (or so), add a charge to vial
    //then make it wrap around back to 0
    will need do the whole var thing for that as well I beieve just like oak ranch var

    attempt rework for roost message REFUSES to display...
    ...apparently I wasn't even using teh roost bs, because I still had restore hp in the move effect
    so iot wasn't even  setting the grounding flag - is now working abnd displays both roost message and roost end message

    -must remember for bs, if not an effect in the top table must use double colon after battlescript name 
    or it won't define it

    -with how remove berry crush top right machine in pokemon center just breaks causing freeze?
    -or something else I did either way need better break script so just does nothing
    instead of attempting to start an event

    need make running shoes work inside / I think? if can raise walk speed etc. may not need to

  bind logic is half working, way I have it rn,  a faster bind mon will force target into a random move.
  but they aren't locked into it, and can select another one, but using the locked move directly seems to cause freeze?

 also  low kick buff seems to not be as impactful as I thought  had weight values too high, lowered field and adjusted power works better now
 -fixed, 

 hidden power over performing - was because bad logic, was getting ALL of the boosts because ordered badly
 rearranged, changed to use cmd args and now it works well enough I think, keep an eye on  - not properly showing type

 -weird issue disable seemed to cause freeze no idea why,  can't seem to reproduce yet
 and hidden power keeps changing the read type, even though the type itself isn't changing

 flag floating drop didn't work for flying types didn't work on zubat? - reworked battler grounded function

 for some reason camper to the left of nugget bridge end does't have any end text??
 -...no its everyone I somehow removed the end message for EVERY trainer. facepalm
 ....and in game trades are also not working wonderful - fixed trainer testing trades - trades fixed, issue was prior mail removal attempt made return before trade
  and sun disk isn't working right, sun isn't fading long as mon is alive? -wasn't wrong just forgot how I setup, revamped now works how I want

  based on pc should be able to fit and display item icons in party menu, 
  but need move party icons to fit better, right now for right side 
  of party menu, make icons on hover over move left instead of right, so they don't get cutoff by icon

  setup running allowed everywhere, except gyms - done

  -seems in general gen 8 icons too big? or is it just the starters, 
  it causes issue with move info page icon is too big to fit in box

  reworked box exp gain levels seems balanced across all levels now?
  and reworked protect like command to hopefully fix issue with bind not working


  //vsonic add further logic to SetRivalRandomStarterSpecies, in field_speciels.c
  long as player starter randomized first, can reroll this based on that to ensure type alignment matches advantage/disadvantage
 //inspired metronome/pickup logic, just need compare with respective player var i.e  bulb var == sbulbasaurball[value]  
 // && rival chrmanderball var  is scharmanderball[value]  reroll  this way I can preserve the relationship or at the least don't end up with an advantage to rival starter
 //for exmample if I as player roll value that gives me a tyrogue, rival is unable to save value for miltank, which would give me advantage.
 //instead if they landed on that they would reroll.  ...damn I miss vs studio. 

  very weird bug, attempting to trace adaptability mon, causes weird hp drop, unable to identify exact condition as it acted different between different cases.
  -hoping its just part of the weirdness of oak battle and it doesn't extend beyond the first fight
  - IMPORTANT   vsonic - checked and luckily it is,
  //just normal part of weirdness that comes wth switching during oak battle, only occurs on switch,
  in oak battle, so when finish setup and test everything, and remove test features, this will never be a problem
  as only one mon will be had, so there would be no switching.

  for different tile for more encounters i.e tal grass being double encounters and gen 2 style low grass being normal encounters but at a lower encounter rate
  way maps are setup  blank grass is meant for open areas you don't do anything on, so for separate encouters would need to rearrange tall grass
  tiles pair them back to give more space to open grass  rearranging maps so it fits together

  issue is encounter rate is handled by map, (not calle encounter rate?) its a separate value that determines how often you get encounters
  while wild encounter rate is how often certain mon show up
  possibly move wild_encounters.json to a C file

  ok so it is called encounter rate, and I was wrong, its not per map its per category, 
  so if I setup tall grass encounters I can set the rate lower

  most of the encounters aren't used they are just filled with teh same mon at different levels

  Meister_anon — Today at 6:13 PM
    Is there a reason the wild encounter file was kept in json?
    other than it just being a lot of work to change I guess. 
  Lunos — Today at 6:15 PM
    Because it makes it easier for Porymap to read its contents. Iirc that's the reason why the original .h was turned into a .json. 

    ok  look into how I would be able to change the file, as a json or a .h file  if I realy do have more access/ flexibility 
    or I'm overblowing the benefit in this case

    as it is, a mon needs to be in every spot of the encounter array, i.e if the encounter group i.e water/land encounters has x amount of spots
    they must all be filled or it'll break the game

    think can do everything I need in wild_pokemon_area.c & wild_encounter.c

    not sure how, gonna be able to adjust the json and encounter.c to limit number of encounters but keep teh same
    encounter rate ratio,  since it would create tabes with less than 100% odds
    not to mention how odd the fishing odds are setup

    could consolodate fishing logic to just use one size  for all rods,
    so rather than splitting all 10 spots between the 3 rods, they can all use 5

    pretty sure cant do if in json, hmmm no would just make it 15 rather than 10, no other way to set static encounters

  */
 goto ENCOUNTER_LOGIC //for wild encounters - this is reading encounter logic
 goto ENCOUNTER_GENERATOR // this is creating the encounter itself
 goto CHECK_CURR_MAP //checks/reads current map location
 /*
  for function giveboxmoninitialmoveset, used for createnpctrainerparty  craete task for move learn
  to help decide what moves to keep when moving through list rather than just deleting the first
  instead make priority list, if not normal type must have a dmging stab move, priority moves have ...priority over non stab dmg moves
  then status setting moves  and make switchout moves and debuffs/buffs their own category

  treat similar to ai gives everyhting a score to decide

  edit-note 12/23/24 do that rather than personality based learnsets,
  with that it'll just ensure mon have a usable/challenging moveset at any level
  vsonic, scrapping idea of personality based learnsets

 -note for couple waiting at bills house at cerulean cove turn then into a double battle.

 -adjustd confusion think bug exclusion should work, believe issue was wrong operator logic
 setup long ago before I understood it, had double negative and use or instead of and
 -need check further - bug check works other confusion logic does not, think its just targetting doesn't work

 -add message for overcoat block powder moves in battle_util.c

 -comatose isn't working causes freeze now for some reason smh/ needed end in end2 not return as its an endturn ability -fixed

 - make new evo methods for region variants flag check for region form,
 method evo_item_flag
 - evo_level_flag

 - potential telport field move upgrade, I know you can store exact map position, so think change teleport to be a two way.
 when in overworld wilds it'll teleport to last saved, heal spot.
 but if used when in a city, it can teleport to last saved location, so when you use teleport to go back, it'll store your 
 map sec and x y position in the map, and allow you to teleport back.
 would need to save location to value, and add logic loop to search through map secs and if your map sec matches within a city,
 if yes, teleport to last stored location if there is one. 
 if not in a city teleport to last used heal location when you reach city limit teleport location should be set to 0,
 if location is zero, and you attempt to use it within city, it'll just not work and display fail text/that can't be used now

 ok yeah def doing this, right now, if you use teleport inside city limits it just warps you back to the same heal spot,
 even if you're already standing on it,  think it also has specific logic for if used within a cave? can't remembver if it fails or warps to entrance
  - think can do with GetCurrentMapType function from overworld.c and the functions below it

 -for play consider swapping badge hm use of brock's gym and  surges gym
 -instead of flash make brock let player use surf (for small chance you spawn npc in pallet that gives you fishing access early)
 -give surge flash, since you don't need flash early, 
 - actually nvm cant get back to pallet until after surge anyway 
 so give surge surf and swap with koga so he gives fly instead
 -makes more sense anyway too, surge is in water town, and koga is a ninja so could "fly" - done seems to cause no issue?

 check strings for hm activate based on metatile i.e from overworld, potentially issue is just a missing check in function,
 but can't click on a tree to bring up should use cut message, I have to use it directly from menu

 need fix comatose prevent sleep messag, its displaying stayed awake rather than already asleep
 case was used hypnosis on abra

 new plan
 brock gives cut,
 misty gives surf,
 surge gives flash
 koga gives fly

 mudsport water sport weren't setup correctly fixed
 -fixed roost, fixed hidden power, fixed field/now side sport effects and fixed bide - ikeep eye on bide possibly lower counter by 1 turn

 saw video that mentioned omega ruby had portable berry trees, rather than needing to go around and plant in patches of soil
 so if I do that instead, and have a key item like the egg incubator where I can store 3-5 berry pots/trees I can carry with me
 it'll cut down on graphic changes I'd need to make, think I will add a berry shop to the game where can buy berries to plant in your pots
 think will give this item in celadon with berry crush guy, he'll give berry incense and the berry pots
 you can get a selection of berries via pick up ability, but then when you get to berry shop it'll be where you buy most berries.

 will put berry shop inside celadon gym/erika's gym makes most sense imo, make sure shop isn't available before fighting gym
 as it would trivialize things.   make script say, this is celadon city gyms personal berry keeper/stock sorry only erika can give permission to use this blah blah
 after erika loses and gives badge, she'll have extra text where she allows you to use the berry shop  
 think have berry prices from 200 up to 1200 based on value of berry

 to make berry pots more convenient think rather than having to check it and harvest it, when it becomes fully grown,
 the berries will be added to your inventory, and then 1 berry from the batch will be planted to start a new batch of trees.  
 based on last berry planted for each tree.  if a tree is planted and you want to swap it for another berry you can do that,
 just put a message saying the berries planted will be lost "are you sure" [start on no, make player move up to select yes option]
 then if click yes it'll remove the tree and plant a fresh berry to grow

 for plans for custom 2v1 battles will reserve for aggressive trainers, so evil team, and I think bikers as well, so bike road would have it.
 and double wild battles would have a chance to be this as well, think of it as aggressive mon that ambushed you, before you had a chance to prepare. 
 keep this to tall grass so a reasonable chance to avoid if they don't want it.

 think make special text when the condition occurs, maybe [PLAYER was ambushed by ...!]

 port emerald berry tag and have it replace fire red berry view nvm simply just need to port the check tag portion of berry menu
 the graphic and info needed for the dislay of all berries,  then can setup berrry incense idea

 working on rival starter select, remembered planned to give starter from oak, so need setup new movement patterns and text scripts for that

 -checking pound, but transforming ditto in rival battle also had weird issue again hoping that's just an oak battle issue,
  but  if it is that means I can't fix it? - fixed it, was bad operator logic in type calc around struggle
  had weird effect of making pound typeless, I had currentmove == (move struggle || move bind)  rather than using currentmove between each, very dumb

  - did rework on bind hopefully works better?

  somehow imposter broke -__-  now causes freeze
  ...ook so imposter stopped workiong because somehjow I removed VARIOUS_PLAY_MOVE_ANIMATION  ?
  idk why or how that happened.

  used emerald tyep setup to replace firered type chart,  mostly works but issue with mon that are super and then not very effective
  it doesn't cancel to 1, it multiplies so ends up with something below 1 and results in not very effective
  IMPORTANT TO CHANGE if something is super and resisted it should be neutral issue is this setup uses mod to set flags, not 
  vsonic IMPORTANT  - fixed.   put logic ni functino taht after reading 2nd type will check multiplier, and reset to neutral
  if it read a super and a resist, should work for dual type moves as well without issue I believe

  -realized it was already working that way my entire playtest, so kind of prefer it?
  will attempt remove message,

  in move learn page need remove window/buffer for status symbol, 
  i.e did move tutor with fainted mon, and fnt status icon, was over the place where the new mon icon is

  changed idea for move relearn since I'm planning to remove mon from pc from overworld if I rely on a pokemon center npc
  for move relearning, I won't be able to do that with the overworld set making it inferior
  so instead do move learn from within pc, before when you select a mon.
  //replace the "mark" option with "move learner" or something
  //and do it as I planned where it pulls up menu where shows pre evos and mon I have selected
  as options to read moves from

 function that will search pre evos, settigm current species to to target species
 have u16 species value that will be set to 0 in a loop, up to last species value or better up to mega
  FORMS_START  
  
  for (species = 0; species != FORMS_START; ++species)

  //if species evolves into target species  set targetspecies to species value and then set species to 0 to reset loop
   think also need a internal loop to make sure it checks every evolution within the species  think put asignemt and break in internal loop
   EVOS_PER_MON
   for (j = 0; j != EVOS_PER_MON; ++j)
   gEvolutionTable[species][j] 

  - functions setup still need test - made devolve function for use in cinnabar script event
  lab tech setup new research in exchange for 5k

  Start_TutorScriptFromPc
    msgbox TwoIsland_House_Text_TutorWhichMon
    special SelectMoveTutorMon
    waitstate
    compare VAR_0x8004, PARTY_SIZE
    goto_if_ge TwoIsland_House_EventScript_EndTutorMove
    special IsSelectedMonEgg
    compare VAR_RESULT, TRUE
    goto_if_eq TwoIsland_House_EventScript_CantTutorEgg
    compare VAR_0x8005, 0
    goto_if_eq TwoIsland_House_EventScript_NoMoveToTutorMon
    goto TwoIsland_House_EventScript_ChooseMoveToTeach
    end

  TwoIsland_House_EventScript_ChooseMoveToTeach:: @ 81716F4
    msgbox TwoIsland_House_Text_TeachWhichMove
    special DisplayMoveTutorMenu
    waitstate
    compare VAR_0x8004, 0
    goto_if_eq TwoIsland_House_EventScript_ChooseMonToTutor
    end

    /base example of what I'll need, will dig into and see what needs to be adjusted

    bad dreams not working 100%, caused freeze adn triggered enemy ability?
    and for some reason used future sight text ? -fixed
    line I removed before was actually necessary and without it, the script fell through 
    to future sight which was below it

    sticky hold doesn't seem to be working, script plays but doesn't take item
    if that doesn't work magma armor possibly doens't work
    but pickpocket seems to work correctly?

    -update bag, make medicine pouch, for heal items & cure items and add items added to bag from mart
    to top of list rather than going to bottom

    -stench flinch chance seems still too high?
    might be fine but it can roll high in some battles so maybe try weighting it
    -seems fine

    -encountered lightning rod, its not playing move animation like I thought it would with my change its also not probperly 
    displaying the stat that gets boosted, missing some text buffer that showcasses teh stat raised in the string
    but otherwise the boost appears to work?   - fixed message, still want animation to play so may remve script for (made move useless), well look into
    not that works may just leave as is, but need doubles test to ensure target swap is working correctly  - doubles not working
    
    -attempting to fix, testing with double battle south of fuchisia, goldeen seaking, either can have lightning rod
    plannign look at metal burst to see, if depends logic can help figure how to set targetting/

    -think almost have a working work aroudn,
    but also notice unaware isn't working right with infatuation, it diplays ability message rather than it failing if they are same gender
    -testing but should be fixed

    -worked on atempt to fix cupid arrow

    -ok absorb abilities adn the status exclusions is working, had to ugly code a work around, no idea how much of the existing/original code
    is still relevant to the effect...

    fuuuuucUUUUUUUCCCCKKKKK 
    idk why this is happening but now summary screen abilities and moves STOPPED WORKING WTF?!!!    

    ok rather htan a recent change it seems to be an overlooked issue to do with first mon out dying in a double battle?
    -ok nvm its legit just BEING in a double battle *facepalm
    not sure why but ability display AND  move dipslay for party is completely broken by this
    -ok fixed it was copy paste errors, I didn't correclty set the values in place cuz i was tired, also if else errors - but all good now

    same issue for endure -now fixed  (bad operator logic facepalm)

    descovered pursuit bug, raticate pursuited lvl 8 kakuna and for some reason it switched out without taking damage...

    sonic screech (argument effect status seting?) doesn't seem to be working, sonic screech soud move is supposed to have confuse chance
    but doesn't seem to be applying? - this still not working
    mightbe working?
    -been noticing weird thing, when in double battle and first mon uses effet,  folloedup by double target move, usually swift for me,
    sometimes the 2nd player mon takes the move effect of the first battler?

    which is how sonic screech was used followed by swift and then swift had set confusion??! o.0
    but I don't know HOW or whythis happens but possibly related to pursuit bug as it could be an issue of targetting and move effect swapping?

    ok on further test I confirm it ISN'T working, what's happening is swift is for some reason setting random effects...
    but only on the 2nd target? so something to do with move to next target?
    ok confirmed, swift or any dual target effect with no move effect to set itself 
    because of the command that swaps target, will take the move effect of the ofthe move last used
    by first battler, and set it, if there isn't one it'll roll a random effect to attemp tto set
    and yes it only works on second battle if there is one, so its 100% that script command doing it
    its the move end command specifically case MOVE_END_NEXT_TARGET

    -keep looking in to moveend_net_taret, seem find issue now multi hit moves aren't properly showing number o fhits
    it lands, but they just show hti 0 times,  and the animation gets hit twice/moved to second target?
    yeah think just issue with doubles so think something I just did with getmovetarget and doubles...-annoying
    -was in battle_controller_player, stuff to do with doubles maybe issue is it uses battle buffer rather than an actual check for double battle?

    ok that wasn't issue it was actually the new argument command being used in multihit, that was wrong need keep old argumenttomoveeffect in that,
    since it doesnt go to hit  =- fixed

    -need to set stockpile stat boosts, modern effects

    -thoughts, 5th move could be cool, but also like I felt, not really necessary in most cases,
    only few times I feel I really want it, think what I would do is treat it like an item.
    hold item, that gives mon 5th move slot.

    (watching wolfeyvc vid believe would need a few more restrictions)
    to ensure it isn't just used to make uber strong pokemon offensively stronger,
    since the idea is diversity first.

    think can do this by limiting it to bst.
    and put it on same level as mega evolution/dynamax by only allowing
    a single pokemon per team to use said item

    think would limit to bst 525? or something like that

    giving the mon the item to hold would trigger move relearn task,
    that allows you to select a move it previously learned to fill the slot.

    following that can replace with tm or whatever as needed.'
    -would need make considerations of if want item to be allowed to be stolen.

    with removal of item 5tm move data is scrubbed/removed pp bonus everything is removed.
    I "think" I would want it to be removable i.e can steal item, as counter measure

    IF I even add this "feature"
    -TOO MUCH UI WORK not doing this

    NOTE, when make dns, make sure night isn't too dark

    -ok sonic screech conufsion in argument isn't working because...I didn't proper.y setup argumenttomoveeffect
    it swaps the argument to move effect and setmoveeffect w chance would properly read it, but it never actually gets there to be read...FACEPALM
    emerald expansion ALWAYS sets argumenttomove effect before seteffecw chance because it still needs to actually
    trigger, the setmoveeffect function  - potentially raise odds to 15, maybe not,d as its just meant ot be extra effect

    -keep note, will make bug type moves trigger infested status and dont think fully setup?

    removed extraneous uses, of arguemtntomoveeffect, as long as script goes to effecthit I can just use my new version in its place.
    also found still need to add script for animation fro phantom force, check battle_script_1.s to see  in BattleScript_EffectSemiInvulnerable
    -testing to see if works WORKS!!!

    -fixed issue was gBattleScripting.savedMoveEffect, was added from emerald, butthe value wasn't assigned properly, so again set random value.
    still need to fix whatever is wrong with setmoveeffect that isn't letting sonic screech set confusion correctly

    move forget confirematino doesn't work for in battle evolution *facepalm* - need fix -fixed, 
    -prob still need check move tutors...

    -major issue, exp gain from catching mon skips seems not to trigger normal lvl up stuff even skipping evolution..
    ok foudn issue, it does do lvl up the issue is the name screen, it needs a callback to the battle instead of going to overworld,
    if mon could evolve or something, ok no its not move learn literally just catching mon exp doesn't trigger evo
    -fixed, issue was logic in FreeResetData_ReturnToOvOrDoEvolutions function ot battle_main, which I forgot to add exception to for catching mon to allow evolution

    -need fix target display and selection for moves,
    for doubles target and self target, it flashes wrong, flashes before you even select move,
    and for self target it doesn't let you confirm it auto uses move  - biggest issue
    -seems to be a cnofusing double effect, as there are 2 different types of highlighting
    for moves that affect self adn ally, its supposed to flash, before you select it, without confirmation?
    without doing the other effect which is for single target or double target where it only doe san effect on foe
    after you select the move, and its a different graphic from the flashing, it "blinks" instead
    - fixed blink is original effect flash is effect ported from EE, thought flash broke blink 
    but its working normally, so kept both and setup, double battle confirm on user target moves, got it to do blink as well.

    also working on making weather abilities uniform for setup - next task
    using this standard
    /if (gBattleWeather & WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT)
      {
          BattleScriptPushCursor();
          gBattlescriptCurrInstr = BattleScript_BlockedByPrimalWeatherRet;
          ++effect;
      }
      else if (TryChangeBattleWeather(battler, ENUM_WEATHER_SANDSTORM, TRUE))
      {
          gBattleScripting.battler = gActiveBattler = battler;
          BattleScriptPushCursor();
          gBattlescriptCurrInstr = BattleScript_SandSpitActivates;
          ++effect;
      }/

      just need replace all instances of weather setting with trychabgebattleweather function,
      and add exclusion for primal weather - done

      -fixed, done
      also fixed decrement of weather abilities, and it properly displays, weather fade message

      added new logic to set apart abilties that don't directly set weather i.e abilities that set weather on conact
      they follow same logic as move based weather setting

      -all that's missing is forecast messages

    -box exp gain seems to be working perfectly, better than exected even, as I progress through the game all my mon are ending up around the same level,
    even ones I've caught later compared to noes had from teh start of the game.  no one is greatly outpaced.
    its perfect   - was close needed level cap for when map opened up more and player could explore, added that
    /also plan add other level cap for new game plus - need add lvl caps for gym leaders, as players could just run back and forth to over level
    /least I think I need to do that?or should I just leave it, if they want to do that that's on them...

    //found move learn issue, its on are you sure you want to forget move,
    i.e confirm forget

    shadow tag not showing proper string data, check SetMonPreventsSwitchingString not sure if that is issue but look there first
    its showing wrnog battler with string i.e is showing my player mon (battler affected by ability) rather than the mon that used the ability
    its ex. arbok's shadowtag prevents switching, when the mon with shadow tag is the enemy gastly 
    -fixed

    - check if I setup planned buff which was to lower speed  -didn't do it, did now, and adjusted ability descriptions
    -now magnet pull arena trap and shadow tag, if they do trap, they lower speed equiv to one stage drop, 67%

    other issue, shadow tag on gastly caused issue with ghost battle type in pokemon tower added exception so can always flee,
    keep eye on for causing other issue w marowak fight  - need to check again becuase I forgot to test
    -I tihnk itd be fine? believe code is ghost battle no silph scope, and I only do marowak when I have silph scope?
    confirmed escape clause uses, battle type ghost without silph scope so its perfect

    -think add shuppet and duskull to pokemon tower in lavender town and raise base levels up, mon are a bit weak,  like 12-16 
    //so bumb up to 17-21 (also misdreavus) think just split up between diff levels
    //put mimikyu in basement of pokemon mansion - done

    -want to attemt fog upgrade/weather upgrade w for pokemon tower - think lookinto overworld.c and queslog for intended effect
    since quest log has a uniform effect that plays even over the player avatar/cast applied to entire screen
    nvm looks like questlog effect is nothing more than a palette fade, simple but effective. - think can't do,
    -from what I see the solutionn reuires a great deal of rework of map tiles
    maps data are split between 4 bgs,  bg 0 is for messages alone, 1-3 are map tiles,
    the apparent fix is putting everything on tile 1 & 2, and leaving weather effects etc. to layer 3

    -but I don't understand that stuff so I'd probi be better with a dedicated mapper, that can go through all the maps
    and see about adjusting them to fit to 2 bgs, after that weather can be updated more easily

    issue with sand tomb its not trapping/preventing escape -was most trap effects testing fixes now, cuz i separated them from wrap
    -fixed  had const logic off, used || instead of bitwise |  now it works

    still need double check arena trap - fixed

  SUBSTITUTE not completely working, it stops swapping after like 2 turns? not when it actually fades

  descovered issue with move learn,  after leave move selection for move to forget if Press A over no to forget move,
  it glitches out, but works correctly if you press B. -fixed guesss I was tired, just missed writing a line correctly

  //think on move page, (or summary page in general) I want the pokemon's held item, icon to be displayed
  in top right corner, parallel to the pokeball, its just good useful info i think.
  but would potentially need to flip item to right to make look reight?

 -hit escape effects not working, victribeel attempted use uproot move worked but then froze when it got ot switch step
 -fixed issue was jumpifbattlened wasn't set in various
  
 -ingrain isn't healing right, for some reason now, its not increasing the heal amount
 -ok so the issue seems to come up only on turns that a healign move is used, in this case giga drain,?
 -hard to test but seems tobe the case,  looking into GetDrainedBigRootHp to see if that is cause

 -redid setup still mot working, not increasing heal amount per turn
 - fixed setup issue was use of gspecialstatus, didn't realize, but it gets cleared every turn
 which prevented it from increasing, replaced w disablestructs and worked perfectly
 -did the setup, for toxic as well, now should work even if more than one status set 
 -toxic works, rebalanced ingrain and  aqua ring, maxes at approx 34% max health

 - for fixing move info lines, top two lines need to move down 1 pixel
 -3rd line is fine, bottom 2 rows need to move up 2 pixels

 -remember need fix thunder wave not working on electric types, display 
 -used callif, and fixed works now

 -ok anticipation not working right? somehow sabrina alakazaam read an explosion move from my hitmonchan?
 -believe fixed anticipation and forewarn messagoing still to do ffect

 -identified issue is to do with ancitipcation function,
 its reading all things as "strong move"  even if I have a super effective move

 -ok actually I think the issue is in my move data, I think somehow my moves are out of sequence after a certain point,
 as multiple moves around mud shot fail while moves below all work. if something is out of sequence,
 then it could actually be triggering different somehow? but the move effect is right so idk

 ...not moves out of a sequence it caps at move 255 its a freakin type limit error. FACEPALM
 -fixed

 -...somejow drought drizzle broken, causes infini loop on switch in smh fuck my life
  //seems to be switch in drought when drought effect is already active,
  so need make exclusion so doesn't reactivate if weather is strong sun? or sometning
  -done, issue was not keeping it from trying to reactivate if sun already set
  -unsure if primal works right

  -NOTE already set logic for compatibility for tmhm and level up learnsets, 
  same as evo can read from base stats or table. just a matter of filling them in now
  
  finished updating up to start of gen 4
  -finished updating up to forms
  -finished base stat update, making compatability commit for in between change
  -before removal of files

  -update teleport effect, works same in wild battles,
  but double battles works as a slow switch think shold be simple to do,
  just matter of check fi trainer battle, instead jump to switch can't cancel logic
  -ok that was wrong, but got it working by copying EE.

  it is -6 priority so doesn't trigger pursuit so EE version doesn't hvae that built into teh scritp
  In considering this I learned Lagging Tail and Stall don't make you move last, but last in priority bracket
  That's dumb -_-  no benefit you're just taking a fast mon and making them effectively slow.
  and doesn't interact w trick room/

  I plan to just make them set whatever move you use to -12 priority, basically works the same,
  only diff is not being able to use priority moves to get around effect.
  but the caviate is now you have a new niche, where you counter moves that gain power for going last
  and slow switch strats from things like teleport, and slow volt switch users etc.
  done
  /but need setup pursuit logic for teleport now, and look into other existing effects ensure no issues
  -not sure how to set pursuit, logic is convoluted,
  and emerald expansion doesn't appear to have set it up yet
  -talked w alex in RhH and confirmed,
  they're gonna work on it, in my free time see if I can't get my own fix going
  -would want to replace the long confusing setup for pusuit hit switchign out mon
  -i believe it should be possible to do with a bs command

  logic needed:
  set switch target,
  check if pursuit from enemy side can hit (i.e slower/lower priority than target) check whole side for doubles
  if yes, do attack animation, double damage and attempt faint
  if faints do normal faint switch logic/script

  if lives return and continue hit escape/teleport


  -believe fixed issues with bind last thing it fix is changing move
  that user uses if they are slower than bind user and havent yet used amove.
  rn my changes only affect the move they use AFTER they get bound
  -fixed that, issue was in battle_main, was excluding glastmove is move none etc.

  -IMPORTANT discoverd issue with forewarn anticipation smh
  ability fails no matter what after turn 1, because of bad code I wrote *FACEPALM
  logic in HandleEndTurn_ContinueBattle  that sets them to unavailable not only makes them single use,
  it makes them single use for ANYONE not just that mon, for the duration of the battle.
  so if you send out an anticipation/forewarn mon on turn 2, the text would play but the ability would never cancel the move.
  gDisableStructs[i].forewarnedMove = MOVE_UNAVAILABLE;
  because this ties it to the position of the battler NOT the specific mon itself *FACEPALM
  no checks or anything just auto settting it to unavailable smh

  DOUBLE chek this, 
  gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)] = TRUE;
  this line should prevent mon ability from retriggering for duration of battle. I think it stores proper place even post switch
  test with mimikyu see if works remove species check, to test only this factor alone
  if works for that, can use for forwarn etc. if needbe

  appears to work for mimikyu, removed species check, but not sure if that just works for battler position 0 or if it moves with teh mon itself
  would need to test double batttle

  in menatime used setup for forewarn anticipation, locking both slots if a mon with either ability has used it
  plan being to prevent players from being too lazy and just stacking anticipation and forewarn mon together,
  this way you'd get just one use of either for an entire battle as they would be linked.
  ...if I can do this right smh

  APPEARS to be working, caterpie with anticipation thrown on turn 2 still blocke move correctly
  clauses left to check, turn 2 caterpie after turn 1 weedle w anticipation
  and doube battle w anticipation/disguise mon switched back in from a different positinon ability initially activated from

  clause 1 passed,  on 2nd use ability activated but did not avoid the hit.
  but thinking issue is filter is too broad, its checking both sides and setting if found not setting for each side
  and its using gbattlerscount which pulls from both sides

  so this would only allow one side to use either ability, whoever was faster gets it, need to fix that
  on 2nd look the side part is fine it checks properly for that

  I think if I replace with a check for ability and if used singleuse ability I can then set unavailable I think I can make work?
  -confirmed singleuseability is properly tracking, was able to test in double battle

  note before forget STILL need to go back and redress use of battlemoves.power == 0  replace w status move in relevant places
  //some places I actually need/mean 0 power for typeless, but other places what I need is check if move is a status move

  =that seems done, before move back to big thing of workig on evo and graphics file\
  -work on setting pursuit for teleport below issue and  the other bugs I found for poison and bind
  well can do at same time  fast things to take mind off the slow things

  note do same change I did for hidden power, for return and frustration
  so its power is revealed?  I thikn that'd be good? or not idk

  think need change evo setup for mid evos
  rather than use the ceiling which is the base established level
  think will need use effort to raise of pre evo + level met
  otherwise I will need to lower all the levels, and the point of this system
  is to take significance away from the hard coded levels
  so for 2nd evo etc. use effort + level met, PLUS effort of curent evo
  as point  hmm actually need an extra filter, only take that route
  if effort + level met is LOWER than pre evo Ceiling
  -doner

  *plan for dealing with alt forms,
  can do with breeding but also setup an item
  alola incense, galar incense, hisui incense
  will set the flag on the mon its used on.
  setting the flag, will display an icon on the top right side of 
  summary window
  criteria will be if mon has n evo with said flag,
  otherwise item can't be used
  i.e if try to use hisui incense on pikachu it won't do anything,
  as it doesn't have a hisuian evolution,
  but if you use alola incense on  pikachu it will work.

  and by doing it this way with flag check, I can keep the "same" evo method
  it won't be same method but I would still be able to use thunderstone or levelup to evolve the mon
  if I have mother hold the item, the egg will be the alt form of the mon.

  the item will only be consumed when used on a pokemon not when held for breeding,
  believe I will have item be given initial by oak aide potentially create key item for
  aroma case/incense case, hmm potentially repurpose powder jar
  which was for berry crush that I removed?
  Rename Incense Jar or sometjhing maybe INcense Vial idk
  but it'll keep things better organized so i can access it easier

  //can't set base stats flag with item, that's a struct value, its static,
  //instead I need to go into pokemon.c and make new data value like I did with hatch
  cans still use species flag for checking evolution, need make new function leave it as true false
  //rather than returning the flag and comparing that against evo as people may make more forms
  and having more than 1 in the same species woul break it.
  //so instead justuse true false and have set mon data value match the target species
  //flag will be on 2nd param
  //ex. EVO_ITEM_FORM, ITEM_THUNDER_STONE, F_ALOLAN_FORM, SPECIES_RAICHU_ALOLAN
  use flag values to set data as its all numbers
  //will need to run in egg give fro mdaycare if was holding incense item

  need function for if species has alt form evo
  just as extra check
  -done
  tested and works,
  thing I need to do is actually create items that will set the flag in data
  and item use logic, logic should be can only be used on mon without form flag on their base stat
  as for some reason setting flag onto species that have base stats flag causes issues
  ie battle lags at start if flag is set on mon that have mega base stat?

  ok just realized that makes no sense, also of note pokeballs got shifted
  so I think its not that, its actually the struct data is slightly corrupted post change on current save
  so starting new game should fix any issues (hopefully)

  SIGH nope shit's broken, think need filler back smh
  filler and evo change wasn't the problem not sure how far problem expandds
  but for some reason battles with mega are weird lag, but first noticed issue is one I had before
  of game freezing on starter screen/selection

  was same issue as before in rival starter filter loop getfinalevo got stuck,
  this time it was because of evo changes and not having an evo method listed for species none
  set like rhh emerlad and it worked, so issue wasn't evo form branch setup

  MALDING, fixed issue started new save but NOW the evo decides to not work??
  it doestn' load the other mon, it only reads base form idk why that happens

  wasn't an issue,I just had another instance of the rom running 
  so it couldn't accept the changes.  everything is working  fine

  just need to actually make the items that would be used for this
  -done, made items forgot need make hold effet as well
  -WILL REMOVE DIDN'T actually need hold effect, could make "hold effect"
  //without actually needing hold effect,  hold effects as defined by file/game
  are only really needed for in battle effects

  daycare man can be done better setup trigger events on the groud
  at position where npc is off screen,  make it run the mapscript
  that would set him forward when I run accross it.
  that way can see egg is there without needing to enter into new map

  switch (GetPlayerFacingDirection())

  other issue with daycare egg text interefeers with pickup text script popup
  -fixed

  discovered new issue with party menu,
  with new layout for lv, gender, name.

  when using item on mon from summary screen for level up
  weird graphic glitch on lvl gender icon, think some kind of issue with window 
  -fixed issue was party_menu.h use of dimmensions

  new idea since have egg booost for daycare planned idea exp boost
  with plan to use exp share variant from pokemon opalo
  can use that for the exp boost
  plan is after mon is selected with exp share,
  can set targets as "priority" once in priority mode,
  they get boosted exp as if they were a traded mon
  up to the point where their level is equal to ave. lvl
  -excluding their data from calculation for lvl and party size
  (take mon as function argument, loop partydata
  if partydata == mon continue  i.e skip it for calculation)
  //
  check if mon is eligible for priority mode before bring up scripts
  //also plan set party window to color gold, if mon is priority
  on top of having the E icon

  set individual mon from party screen,
  set all from item menu

  @initial mart changes done,
  //kept celadon and 2 island mart on old setup as they were unique
  //still to add setup for 2nd mart clerk and remove queastionair object

  setup mart change since i'm on specials,
  change like I did givemon, to not need argument
  remove questionaire from all marts,
  and put 2nd shop keep there instead,
  who will pull from location specific items, 
  i.e special pewter town stock.

  while the main shopkeep will isntead pull from a general
  list based on badge count.

  so you won't need to run around to specific locations
  for your important items.

  ex. pewter city could sell mn stoons
  rock type items, and after you clear mt moon 
  could sell the opposing fossil that you didn't take.

  use FLAG_GOT_HELIX_FOSSIL  or
  FLAG_GOT_DOME_FOSSIL

  think can do an ifdef for it in array,

  use an get flag value see if dome is set,
  if it is def got dome
  #ifdef got dome  
  ITEM_HELIX
  elseif
  ITEM_DOME
  #endif

  something like that

  "some maniac ran in here about the buy of a century
  and tried to sell me on this funky rock"

  //actually no can't use that his script was talking about going to cinnabar

  idk do a flag check and run some unique text when the player goes in later

  realized item conditions for use aren't working correclty
  I need to check teh entire evo path not just the next evo.
  So I need to use my final evo function, I made in field_specials for starter selection
  I need to make it search for an evolution where the i value is for a species with one of the form flags set in base stats
  and base species does not have one of said flags.

  Then I need to lock in specifically what item would have an effect on it.
  so I need to make it return what item would work. i.e what item is in param 2
  actually no dont make it return the item, I'll need to check multiple items
  so instead I'll need it to take the item as an argument,
  and return true if the item matchhes teh criteria and matches param2 for any of the evos
  hmm, easier to check method actually, search for form evo method
  on i, and then read param 2 value check if it matches item

  that should be new function to confirm if can use item on mon,
  if works how I figure can use entire thing for item use and for hold effect check
  in daycare file
  -done but setting form flag by holding item not working

  change breeding egg occurance from odds tis fucking cancer,
  intead make it fixed step value with a multipier based on compatibility
  -done


  seen upgrade in EE need to add, additinal effects, and two_turn args logic
  battle_moves change that lets sheer force work
  for  two turn moves etc.
  ex. skullbash raises defense on charge turn,
  sheer force should block defense boost but raise power

  check if works with flare blitz as well, does recoil and burn,
  should still recoil just remove burn

  note from Josh aka ShinyDragonHunter
  in battle.h eventually change trainername to pointer instead of array
  and apply COMPOUNT_STRNIG  things in screenshot putting in decomp folder for later reference
  use to replace names make and use static strings for names that are reused
  should be statics believe put at top of file
  COMPOUNT_STRING logic saves you space in the case identical values are used more than once

  //replace repeats before change struct value
  then can just use  replace to put compound in


  found  what puts use on item,
  file item_menu.c  sContextMenuItems_Field
   checks the bag itself to determine if an item can be used out of battle.
   so would just need to put a change there, to make items unusable

   hmm btu doing so would mean the oak stops you text would never play...
   I forgot what the original reason for doing this was

  -do that inbetween reding items file,
  I removed it from being a json but I didn't set it up correctly to take advantage
  of the flexibility it now has

  done -working on item, Unfolding gave me idea for item context/idea
  make like jar/bottle of sand I had as a kid from the beach
  make glass bottle graphic w cork have sand and starfish pattern inside

  difference will be different color sand of each region normal for alola
  //think galar was irish so potentially black sand
  galar was irish and scottish mix

  had that wrong black sand is iceland not ireland

  alola has normla tan sand
  give galar reddish sand (since irish/scottish red heads)
  hisui  may go for silverish sand?

  NEW IDEA - pc sort function,
  will be before you open pc will be search function
  will loop boxes and order mon by filter and species number in case equal

  ex search flying types, will reorg mon from box 1 to end  by flying type 1 
  loop type 2 by type order and if type eqeual organize by species number

  ex flying/normal /normal /flying

  actually better go through species list by number 1 - end
  if type 1 or 2 matches type put first

  after get to end, of flying search
  or do like dex only display mon in search don't display others,
  should be simple mon are stored already so showing some not others
  wouldn't destroy their data

  wait that only exists in emerald version of dex...
  don't know what wouold have to do for that,

  add new search option to pc menu, go to search options
  click apply to do so
  and then take you to box one.

  note- was able to work out new evo method for milcery
  to let it change forms as it evolves.
  with help from Sbird and McGriffin, was able to bring my idea to fruition simply

  finish removing evolution table from use of rom, saved 100KB

  -attempting transition route5 daycare to 2 mon breeding daycare
  am making bunch of new function to hold route5 data
  since defaults are built for normal fields,
  but that's taking a lot of space etc.
  so wondering if I can instead do a state check in teh script
  to set a var that I'm at the route5 daycare not the other one.
  and make the default functions use, the route5 variants of the datafields
  rather than need to make a whole new function
  -possiblym with terniary operators?

  terniary only work on one line, filtered w var state instead,
  worked

  new buff for early bird wake up refreshed,
  on turn awaken mon gets a random stat buff to a non maxed stat
  believe can look into how moody done for effect
  -made effect haven't tested bs

  -discovered graphic issue when try to learn new move from battle
  statuses loaded in info window, persist and show over mon icon
  -doesn't show when view move info normallym, but from move learn it breaks

  fixed,

  potentially add new dex page for bst and evo, inspired by parallel emerald?
  for evo need caught mon and seen evo to display evolution?
*/
goto STRING_PLACEHOLDER_TABLE //string_util.c for planned misc cap replace more capped text w placeholders
goto NEW_PLACEHOLDER_CHARS //decided setup like this to cut down on space taken up
goto GAME_START_INITIALIZING
goto BATTLE_SPEED_UP  //pokAbbie in battle speed up
goto BATTLE_ANIM_DELAY_CMD //value for battle scrtip animations, not sure if can use, this & pokabbies set have small hickups w waitvisualtask finish
goto SCRIPT_DELAY //function for delay in event scripts set to new option when port pokieabbie changes but for now scripts move a bit faster
goto NEW_DEX_USE_NOTES //new big idea for more dex utility - more realism, make like show, look at battle bag callback, restrict movement for in battle
/*

  issue with nicknames mon with nicknames aren't having their name said
  because of how I did the name storing, need fix
  mon is nicknamed but its still just callign out the species name
  

  ok nickname is actually fine, its just calling wrong sting for battle,
  when in a trainer battleit works, when in a wild batle t shows species name not nickname

  ..ok nvm its actually working?  might be using diferent buffer at different hp levels idk

  -when I returned my nicknamed mon it used the Species name instead -_-

  seen works in party menu, not in battle
  so need use party menu function

  seems issue with dynamic starter relation
  fire ball w bulbasaur ball
  from left to right I rolled
  Togedamaru,  Helioptile, and togepi

  choice is based on final evo, so that gave me,
  electric/steel,   normal/electric,  and fairy/flying

  by my rules squirtle ball vs charmander ball works

  but makes no sense for the other,
  charmander ball should beat or resist bulbasaurball

  and yet steel beats fairy and electric beats flying
  fairy is not effective against steel, 
  and flying is resisted by BOTH electric and steel

  the entire relation is reversed???

  spacial rend broken animation breaks game,
  think same for good amount of later animations
  infestation replacement swarm is broken, 
  or more accurately the infestation status is?
  froze game

  -poisoned legacy not working, sets bad poison but never does dmg
  -not workign at all smh isn't even doing corrossion effect
  didn't let me poison bellsprout

  ok issue was my change for status moves to work off type chart
  since i had type calc in status function couldn't get passed immunity
  now has direct modifier adjustment for poison stat moves
  w cossosion/poisoned legacy

  fixed toxid dmg, not sure exactly what was wrong but adjusted the code blocks
  and it seems to be working correctly now

  would need to do same for any other ability that breaks through immunity...
  look into miracle eye -__-

  go through bst of mon that were final evos but got extra evos later
  (stuff like dusclops) for high defense mon especially
  and check if there are good to use with new eviolite,
  if not adjust their bst tobe above limit
  also think need work in global stat total limt as well.
  just to be safe,

  did that, but broke eviolite function in 
  GetItemIconGfxPtr, for displaying graphic (didn't work before anyway)
  need to find how it identifies which mon its pulling from
  and use that for the item/condition

  aftermath has bugs
  when used in trainer battles brings back dead mon during enemy trainer switch dialogue

  `When switching in the Shift "do you want to switch Pokemon" dialog during a trainer battle
Aftermath briefly revives the fallen Pokemon just to kill em again`

  compliments of unfolding

  `
 if aftermath kills your enemy and you switch into your forewarn pokemon, it warns you about a glitchy move
 `
 - seems fixed, believe issue was forgetting to put a condition
 for the target being alive on the funciton

 -infestation/swarm still broken - causes freeze
 not sure if problem w status or with animation
 as there are other animations that are broken

 -note instead of starter ditto have daycare man south of cerulean
 give gift ditto as compliments of your first visit
 /to commemorate your very fist patronage/visit

   NOTE**(
    in tune w legends arceus change
    and my goal of making status moves more relevant.
    What if I made every status move 
    excepting things that need go last/rely on a mvoe being used first
    into priority moves?
    Since you are already giving up damage to use them
    and have the chance to die before being able to use it

    that adds on extra push factors that would disincentavize using them
    plus makes sense there's no need to charge an attack
    or making contact w the enemy
    so makes sense for them to go first
    )

    try cut down on proliferation of muscle magic as it was meant to be special
    for mega marowak

    /plan can tkae off muscle magic but when introduce item
    //that allows set any ability, which would allow people to set muscle magic themselves,
    //and they'd feel smart for doing so, since it has so many good special moves!
    //since expanded save block can add new field to mon data
    //setcustom ability,  then just put logic that if field is 0,
    //use innate abilities, otherwise ability field will take the custom argument
    //will make task that sets selectred ability to field

    //rather than celadon think will have these be post game specific?
    sold at pokemon league after becoming champion

    to make available for new game plus
    after starting new game,
    can  go to league office and guy will let you in,
    saying huh you seem to have the qualities/look of a champion
    welcome.

    and at the first room there will be a mart available
    that sells the post game league stuff,
    so you can use them for more mon

    can potentially add back lost location field as well?
    need see if that adds on to ewram if not think I'm all for it
    (think bottom line is for fateful encounter text
    can just move to top line in parenthesis )
    then set reserve bottom line for nuzloke mode text for lost mon

    can make nuzloke mode option
    if set can't heal fainted mon, mon put in pc
    w zero hp remain as such

    so need item use logic, pc logic and pokemon center logic
    and also logic for any place that does heal after battle
    ok lucky most all was done w one command all that's left is pc logic
    and can't put in daycare believe fixed daycare
    need to exclde battle tower stuff
    ...oh there is no battle tower in fire red
    its trainer tower that is in fire red on sevii island

    -if get nuzlocke mode working thought put 
    nuzlocke counter on back of trainer card
    can put in saveblock would just need ensure that data is cleared
    so long as using same save ie. not deleted it stays
    need see how many values are stored on back fo trainer card
    could increment at new game long as nuzlocke option is on

    mon gets healed as side effect,
    of data passing to boxmon struct as boxmon doesn't store hp
    so when it comes out  hp just gets set back to max

    so will need to take that source on the wiki for setting hp to 0

    for floating mon, to make more clear change to have elevation as indicator
    w debug menu realized all floating mon have a shadow under them to denote they are floatin
    so that's a simple thing to do,

    //for mon that are flying can leave as is,
    remove shadow for all mon that have floating but aren't actually floating mon
    that way it can function as a secondary indicator

    -testing over max power in debug seems have odd effect of removing status?

    seems issue w early bird as well,
    way it works, if you use a stat changing move the same turn you wake up
    it forces the effect of the move to be teh same as the stat raised by early bird
    and the esame amount.

    i.e if early bird raises acc sharply adn you use harden, harden will again double raise your acc


    need fix sturdy, KO resist effects aren't working - sigh
    -fixed

    //go over bug type mon again that I buffed speed on,
    with trick room considerations may actually be making some mon worse,
    so go over things and consider if it can be used in trick room,
    enough bulk or enough offense, otherwise keep speed boost

    /go over hisuian/dlc mon make sure have proper hidden abilities,
    hisuian samorott and prob others were still default to base form

    //add sound moves to list,
    //round, echoed voice, hyper voice
    //also smack down and think focus blast
    //think give echoed voice to zubat line, as learned move or tm?
    //hmm both yeah both
    -also add rock slide

    //hmm think I also need some anti heal so make heal block a tm 
    and spread it around - oh I already made it a tm good job me

    in general go over gen9 tms to see what need add to my custom list
    /12/27/2024

    Notes for 2 v 1 battles,  2 enemies 1 player mon
    //unique for me is to rework turn setup to better balance,
    idea even though only 3 battler still have 4 turn actions,

    order of battlers different based on speed,
    Slowest battler is player:
    enemy mon both move, then player moves twice at end,

    if player is second fastest:
    player just moves between battlers and gets an extra turn at end

    Fastest battler is player:
    Player moves first, Fastest enemy moves, then player moves again before last enemy


    -also remember eventually setup turn order rework for to new gen setup,
    believe EE already has, most important thing is live speed recalcs
    for turn order, will be massive for status moves & abilities that affect speed
    adds an entire new aspect to battle

    -still working on setting up test system,
    need fix battle callback for move info
    fix transform level up stat display when switch mon 
    then fix ai
    //12/27/24

    -was able to fix transform level up switched to battlemons over mon data
    still has one issue left, transform mon hp not quite accurate
    //when max hp & curr hp shit when transform 
    not notieable until take damage and open party menu
    1/9/2025

    //note  attempt fuse healthbarupdate & datahpupdate
    into a single command, rather than a set of paired commands
    all the pushes and jumps is what makes it annoying but pretty sure is 
    doable

    also updated disguise w custom hp drop, for focus sash interaction,
    plus fixes for conversion like effects
    1/10/2025

    Presently trying to identify stat change bug
    raising stat via moody/early bird causes next status move to take prior stat Id
    instead of its own.
    have been notifid effect has never existied in EE, its something I did.
    1/15/2025

    redid status effects further update dmg in air moves
    redid recharge, confusion rampage moves like thrash 
    and lastly upraor to open up about 6 status2 slots.

    Ground rebalance notes:
    //could make idea it can't hit floating specifically because its gound based
    //if the attack is ranged/can get off the ground can say hey it should be able to hit

    //since maded grounded moves already have acc drop against flying, I guess its fine
    //to be less selective on what ground moves can hit floating mon
    //but this also means the moves have to hit mon in fly...
    //floating is diff from flying, would make more sense to split off effect
    //bonemerang makes sense to hit a flying mon but if a mon is high in the sky
    //no way a mud slap/mud bomb would hit it
    //plus they would ground the target,
    //which doesn't always make sense, so yeah will separate 
    //ground moves that dmg flying and ground moves that hit floating
    //only those that dmg flying should do grounding effect
    //but I somewhat need both more moves that ground flying, and that hit floating
    //but not too many as that will just invalidate the mechanic..hmmm
    make consolidate flag/macro like is in battle constants to be able to refer to all effects that hit floating
    -did that also adjusted accuracy calc consolidated in gettotalyaccuracy now uniform between normal and ai file
    1/15/2025

    //simplification of Idea for expshare based on pokemon opal
    give item set flag that effect should work,
    and then just handle via a party menu dialogue/task
    that sets a value to a new mon data value
    just like how I handled shininess just set mon data value for
    exp share, when on display E icon in party menu to denote effect
    plus can put in pc and return and will still have exp gain until you turn off

    Thinking just pressing L in party menu while hovering a mon
    will just set and un set it
    
    consider potentially interact w/removed by something in nuzlocke mode
    also people will want an all on off switch as well,
    so guess press start/select for that?

    *Note tangent idea, make other companion item
    none as Exp Null, opposite of exp share would 
    block all exp gain, so set potential gain to 0
    point of this is to be able to directly manage your levels

    Would alloow for challenge runs, i.e lvl 1 runs or level cap runs
    would work same as exp share but because you have both  would need to 
    be able to toggle the exp share item itself,
    so rather than it auto working soon as you acquire it,
    it has a off/on function, you select it and turn it off or on

    Changing state wouln't change what mon have been selected for exp affects
    it just should Grey out the EXP icon,  its Blue when on
    Grey when off for EXP Share

    but for Exp Null just make it Red for on
    and if you set null for a mon that previously had exp share,
    it should clear the exp share state
    ex. setmon expnull to true also sets expshare to false
    1/17/2025 vsonic important

    Notes on Shadow battler escape w flying/floating mon
    
    Note**(Flying birds and airplanes don’t cast a shadow on the ground
    because they are too small and too far away from the ground 
    to cast a prominent, observable shadow.)
    
    For relevance to the game that would be flying high in the air,
    like say in move dragon ascent Fly, or skydrop
    on average they aren't that high for normal combat,
    they are just floating or have the ability to leave the ground
    at that close high they would still have a shadow
    and should be affected by shadow tag etc.

    Ghosts are dead/ non corporeal so makes sense for them to 
    just not have a shadow at all and thus be immune to those 
    affects.
    1/16/2025

    Idea for pc, change,  remove back slash
    but also if nickname is same as species name just don't show nickname
    //new idea for nickname, only show backslash not nickname if same as species name
    -done
    1/17/2025

    Note**(
    Still plan to add effect for spirit shackle decidueye
    make lock in effect cancel people that try to escape (still exclues ghosts)
    along w the pursuit effect buff.

    Think may be able to  do with an extra status check
    and then just do a jump
    )

    //for exp share state stuff takes a lot of ewram to do in boxmon
    if I just do in mon and popluate when it moves from pc
    I could prob save large amount of space?
    BoxMonToMon would be where I have to set it to 0 on leaving pc etc.
    that's where mondata status is handled, and set to 0
    every other pokemon substract value is set in calcmon stats

    ok setup realized would want to mix exp share w exp null 
    for some cases, so don't set button prompt same for both
    Exp share activate with L button
    exp Null activate with Select button changed mind do Start button
    if right handed people use right sided shift
    its even better helps prevent mis clicks

    IMPORTANT, rolled likitongue as starter only had ghost move to damage
    can't hit any of the starter mon
    thouhgt already did but need to go over starter selection file


    ok idea, (can't remember what it was)
    setup flag check for oh I remember now,
    idea for giving exp block, keep exp share where it is,
    have mom give player exp block at start when leaving room

    hey sweetie, I stopped by the market today
    and got you something to help on your journey.
    idk what it does but I was told this was the most in demand item
    right now.  Something about EXP gain?

    =trick player into think getting game start exp share,
    plus joke about moms getting wrong birthday present from 
    the store

    Gives player Exp Null  (useful but pretty much useless for 90% at start of journey lol)
    
    for exp null script give use FLAG_GOT_EXP_NULL_FROM_MOM as the check
    
    Created flag values, need item graphic for exp null?
    potentially just do a recolor.

    last things to add fo reffect are logic in party_menu.c
    and replace exp share logc in battle_script_commands.c getexp
    1/17/2025
    
    check rebalance ingain/aqua ring healing to cap lower
    so is equivalent to other healing moves it just has to build up
    //had already done that but were not equal reset both to cap at 6 now
    meaning max heal is approx 37% of max hp
    1/18/2025

    psywave needs to be rebalanced lowside damage is far too low
    1/19/2025

    wind rider and wind power both ignore sandstorm despite it being a wind move
    wind rider gives immunity to wind moves and is also given to mon that are literally
    tumbleweeds -_-  
    So decide change wind rider at least to work when sandstorm is on field,
    and also give immunity to sandstorm damage
    put in switch in, is batler weather affected w sandstorm boost attack
    would be switch in and believe move end effects

    was able to setup, sandstorm logic based on tailwind script
    now working on unique buff for sandstorm effect for wind power
    different to how it works in tailwind, in sandstorm will reapply charge
    if not set each turn.
    Balanced by negatives, will not get sandstorm dmg or accuracy drop exclusions
    that wind rider gets'
    will need jump in script to skip wind rider if battler actions done
    well not just battler action done need all battlers finished actions
    
    found it 
    if (gCurrentTurnActionNumber >= gBattlersCount) // everyone did their actions, turn finished
    setup effect to jump looks like should work fine,
    last thing is also had to adjust charged status clear,
    moved effect to moveend clear rather than attack canceler
    not sure why was in atk canceleer but as set there,
    chage isn't removed until the next move is being used

    setting up windrider found modifybattlerstatstage command
    very good for adjusting stat stage much cleaner
    compare w EE and go about replacing stat changes with this command 
    where possible
    1/19/2025

    NOTE(**
    TESTED was able to confirm charged up status wasn't cleared
    until next move was used.
    
    ok realize with modular evolution levels, I decided I need
    to know what moves I'm close to getting to know if its a good
    idea to evolve now.

    To avoid taking up too much space idea is not to take all the moevs
    my plan is instead to ONLY take the next 3 moves from current level
    unsure where exactly to put, EE has similar thing in pokedex page
    but idk maybe I can put something in the summary screen

    Ok decided to put in summary screen, on move info page
    make new input for page press L to load next 4 moves
    replace pp w the lvl at which move is learned

    main benefit of doing it this way is, be able to use
    normal move info options to get more info on
    the potential incomming moves can read move description
    and see move characterstics (when I eventually setup category icons)

    may make this a new page, or in task treat it like that,
    cuz I want to return to normal moves and page
    when press B button.

    setup wise I'll either have to store my current moves in memeory
    to reassign, or just replace the summary screen stored value w new moves
    and can easily reset it based on my real moves that would be stored in
    pokemon struct, so no worry of anything being lost that way
    )
    vsonic IMPORTANT 1/19/2025

    //new idea from looking at facade,
    w new freeze status changes make new flame/toxic orb equivalent item
    "Snow Globe" effect is to set freeze status especially good 
    as it doesn't lower a stat normally, in light of that,
    believe need to add an extra detrement idea rn is being frostbitten
    increases odds of being frozen(again) freeze is very strong
    so not making this boost strong think 20-50 percent
    most freeze moves have 10% odds so this wopuld just bring them
    up to 15%

    bleakwind storm is 30, but since I'm not doubling
    this is still find and drops it from potential 60
    to just 45 which for a 5 pp move is still manageable
    1/19/2025

    revisit magic coat effect realise it reflects damage
    may need lower timer to 2 turns
    set 2 goes to 1 at end, next turn 1 goes to 0 at end 
    clear effect, so two full turns of effect
    well does'nt protect but is a deterent
    potentially broken if setup wrong,
    did I set as sidestatus or battler status... hmmm

    ok nto big deal was thinking of mirror coat
    magical coat just reflects status effects ex. leech seed etc.

    Squiretle ball starters complete moving to work on 
    magic bounce buff to counter intimidate
    reflect effect back to attacker bypassing dark checks etc.
    as magic.

    def names Magic Bounce, bounced/reflected the effect
    back on attacker name think do name without prefix nah use prefix

    undecided if still need message saying attack fell or not

    ok got intimidate reflect working, it does the attack stat fell
    without me needing to change anything it looks good I like how its
    going as of now

    **balance discussion
    intimidate best ability in the game, competitively
    I've added multiple exceptions, and now a full counter in magic bounce
    I believe its still good, magic bounce is relatively rare
    and on mon that are special attackers, and not too strong themselves
    so this makes them much stronger, without completely invalidating intimidate
    you just have to be more careful in how you use it
    I believe having a dark type intimdator being able to get passed the dark type immunity
    is an important part of the balance.

    Mostly from the consideration there are certain mon,
    urshifu cough you don't want running wild unchecked,
    so being able to intimidate them at the cost of running dark type
    seems like a good idea, (until you realize that just means more incineroar but...)
    idk I could prob get by with out it, since I made status moves go first,
    it would cost me a move turm, but I could just use charm or something 
    to knock the urshifu down.
    On the other hand keeping the dark immunity, ok nvm
    the intimidate immunity without dark breaking it is better
    because it doesn't incentive specifically using dark type intimidators
    which would again just put incenroar on top
    so removing that, and just leaving it as dark types being immune,
    puts everything on an more even playing field
    1/21/2025

    //add sludge wave as tm
    1/22/2025

    //don't forget will need to remove use of gbittable
    will be replaced w use of (1u << "storage value")
    1/23/2025

    early bird is fixed now need find what's wrong w moody
    as that bug doesn't exist in EE

    ...huh now that early bird is fixed, there's no moody issue?
    ...ok I think...the early bird "fix" was what broke moody *facepalm
    not the part related to attack canceler since that was blocked to only early bird
    but the changes I made in stat change logic,
    effectstatdown:
    it had logic for sSAVED_STAT_CHANGER  to  sSTATCHANGER
    assuming sSAVED_STAT_CHANGER never gets cleared, just constantly reassigned,
    that causes a problem smh
    -fixed
    1/23/2025

    //note for exp share change, for ui
    either need to undo change that allowed for showing status and lvl in party menu
    so status would cover lvl, 
    or I would fit exp symbol to end of name and before hp bar
    rn longest pokemon name is 12(+1) characters crabominable etc.
    if I have space then I can put the symbonl there
    tested looks like plenty of room there.
    note people will want quick set for entire party
    think best way to do that is just hold down button that normally
    does individual set, i.e hold down start, to set for entire party
    new Expshare icon will be about same size as status icons
    but EXP as text, deep blue for exp share, red for exp null

    test if that will fit by attempting put status icon
    in that space as well

    note make new string for rage
    use diff string for using rage move
    prefix atk name's rage grew!
    so can have diff string for move power growing and atk stage increasing
    vsonic 1/23/2025

    noteiced another bug w callback, for some resaon
    move info callback ignores the logic I setup 
    for not displying status graphic

    ok decided infested status will be permannet
    but swarm will be the temp version of it
    1/24/2025

    need double check disobedience logic
    mon with matching ot idea, received via give mon script
    was disobedient
    1/25/2025


    balancing bug status, 2 considerations main idea is bugs being annoying
    that would fit better if infestation was something that could be cleared on switch,
    as well as incentivizing use of the move swarm, which would inflict infest
    but prevent battler from switching out.

    I'm having trouble figuring how to get the health box to display new status icons
    and am unsure if I can even get it to display the correct colors
    as its not one solid color. and as the thing takes straight rgb values for palette
    I"m assuming it needs tobe one color.
    So I may not even be able to get it displayed correctly.

    To that end I could just make it a status 2...
    forcing a switch is still very impactful
    and would also allow me to set both poison and infestation
    together.

    Annoying to lose effort/but makes sense for balance
    and other considerations.
    1/25/2025

    noted issue with yawn, can't remmeber if decided to setup
    to set sleep at end turn,
    or on attacker next turn through atk canceler,
    but rn its reading the wrong battler as going to sleep
    think an issue of gactivebatter vs battlerattaker?
    need fix

    changes for chosenstatus anim are STILL 
    not working????!

    fixed animation was fine, issue was BS_setargumenteffectwithchance,
    has curr instruct jump where I shouldn't have
    then had other similar issue in the setmoveeffect function
    which I believe was due to a curr instruction increment outside of a case
    so both were triggering,
    I went throuhg the funciton an cleaned up all 
    events of it.

    it seems to have cleared that up.
    left now is to set an end turn retrigger for infested animation,

    then set swarm, effect
    needs to be different animation think can use the 
    move animation with the attacking bugs?

    just need make sure that plays first before infestation animation
    once get end turn working, go over infestation move effect
    and decide which moves should have it.

    I want it restrictly mostly to the bug moves only bug types get
    which is why I've removed it from u-turn

    reset use of IsBlackFogNotOnField
    realized effectively want effect to be like cloud nine
    with weather has effect
    so rather than funtion put everywhere setup more cleanly like a macro?
    cloud nine didn't end the effects it just blocked them
    
    make sure to consolidate effects I want it to have,
    //so know what Its meant to be  is in setmist command rn
    vsonic important 1/25/2025 - can prob add to weather has efect/logic where air lock is
    

    working on exp share
    find how to set in party menu
    then can do scripts,
    also clean up use of status1 spirit lock and status1 infestation
    not planning on using rn

    //set exp share and part loop effect,
    slightly convoluted so think will need create
    exp item user manual, will give w exp null from mom
    at game start.

    That way player should already be familiar with
    using the effect by the time they get the exp share for real.
    and yes that's assuming they actually read the manual

    if can order key items by id would 
    like to keep exp manual at top of key items tab
    1/27/2025

    //old idea may use elsewhere
    //idea change pokemon summary box from red to black to show dead ... play the runescape death music   XD

    Note*(
    Need adjust how exp share work now that have multiple,
    not quite triggering how I need,
    mon that is sent in if holding exp share affects exp distribution
    i.e 3 mon with exp share a 4th mon sent in,
    sent in mon gets 50% exp and other 50% is  distributed among the exp share mon evenly

    but if 4 mon have exp share and one is sent in
    that one will get 50%  from being sent in,
    PLUS the 50% divided exp thus lowering the amount the others get

    Need to figure out a better way to do that,  either exclude them from exp share effect
    if they are sent in, or something else.

    Undecided as of now,
    also plan change divisor method to speed up exp share a bit
    to account for using on more mon
    either give them all 50% or give them all 25% rather than
    dividing it by number of exp share users

    ok if numexp share users is greater than 1, give everyone 25% split
    25% is what you would get from 2 exp share users so this way 
    the grind is no worse for using on 2.

    alternately using on just one mon, you keep the normal 50% split
      
      //leaving of for tweaking sent in exp share hp, but could be done by setting check for usign expshare & sentin w else if
      //but point of sending in an exp share mon is to add extra boost to exp gain
      //and the change I planned (reasigning gexpshareexp if sent in to use viaExpShare rather than the flat 25% cut)
      //could have the effect of zeroeing out the extra exp from exp share
      //ex get 50% from being sent in, but only add 1 exp from exp share because split
      //replaced calculatedExp / 2 for ease of readability
    
    otherwise addin limit to cap split to 25% received exp
    )

    remember disobedience logic was off, tested
    and seems even more broken?
    playing wrong animation and not healing when loafing off,?
    plays heal animation but doesn't do anything??

    not much wrong here as I thought, mostly just a matter of
    changing default truant script, and not adding a heal argument to disobedience
    that's fixed, but noticed weird issue.

    when disobedience attempts to nap but then attempts to usse move
    triggers multiple effects someitmes, still tracking,
    that could be reason 

    took EE obidience logic and it seems to be fine now no issue?
    
    Thanks to Sbird sharing Ghoulslash's fog blend branch
    was able to accomplish wish of getting player to appear to be below fog.

    source info
    https://www.pokecommunity.com/threads/simple-modifications-directory.416647/page-9#post-10222192

    https://github.com/pret/pokeemerald/compare/master...ghoulslash:pokeemerald:fog

    need to fully understand it but for now it looks good for horizontal fog,
    but it doesn't yet work well with my dark fog,
    need to adjust and find what works
    1/28/2025 vsonic important

    */
   goto QUEST_LOG_UPDATE  //for if new item find should be updated in quest log
   goto FIELD_MOVE_LIST_LOGIC
   /*

   hmm think will actually do EE tmhm refactor
   so tmhm learnsets can just take move values

   not sure how tm order will be handled then,
   potentially still use sTMHMMoves for that?

   The issue in my mind with that was adding moves
   that AREN'T tms far as I could tell there isn't protection for that?
   
   Looked and its moslty handled by py scripts

   Note(moves are just moves, so think teachablelearnsets
   is just all moves it can learn, even if not a tm/hm
   but then when applying a tm it can filter if the move is
   a tm/hm move
   decide put move value for tm into secondary id
   that way don't need that weird move item transpose logic)

   see if I can do w python,
   looop src/data/items.h
   read .itemId if is item_tm##
   copy and store that value 
   replace item_tm## with MOVE
   and paste it into secondaryId  in place of the 0

   should be easy to do
   then can do same thing for tmhm learnset file,

   Did then also came up with idea to fully separate tmhm list
   from Item Id, mostly works, now just need to get the
   order Hms etc. are printed in the tm case to shift with the number change
   1/29/2025

   NOTE**(
   important note for tm  refactor tm list is decoupled from item id
   but there is no way to on compile limit the moves I add
   to mons tm learnsets to things that are actually tms,
   but I guess that didn't exist before,
   but if a move isn't a tm it won't show up thanks to my later function 
   chcks... ok its fine.

   So get tmhm leanrsets will pull the list along with whatever moves are on it,
   but if the moves don't pass the tmhm checks
   it won't show up in tm case,

   Meaning its, protected but you can have extra data that just won't be used at all.
   )

   just did tm refactor and setup tm list in global as static array
   so can use in num_tms num_hms constants

   unsure if that would break anything byitself,
   but just noticed corruption in palettes for mon picks
   at starter selection,  most likely memory leak,
   starters turtwig, squirtle, then fuecoco,
   feucoco is fine but after a while of going between the selections
   the former two's graphic pics were corrupted.
   
   I think they took on the colors of the last one,
   potentially an issue w my changed palette logic?
   potentially decompression buff?

   ...oh no, its goin further,
   the naming screen is broken...

   ok after get out of the task everything appears to be fine...
   
    for tm refactor believe last thing need to do,
    is get the tm case to print in the correct order,
    rn it changes ids correclty, but it does not
    change the order in which things are loaded
    within the tm case/ are printed to the tm case

    ex. putting fly before cut hm
    makes fly hm 1 but it still prints in the 2nd slot

    still working on removing old links of item id to tm hm
    search ITEM_HM0 & ITEM_TM for hits

    also plan set CanSpeciesLearnTMHM to use move id
    oh nvm I don't need to do that
    -did it, it did make sense to do,
    for all but tmcase I was using a large loop
    to find an item value to use
    changed species function and was able to remove loop
    only kept for tm case just using canmonlearntmhm there intead now
    2/1/2025- done

    almost fixed tm setting order in tm case
    last thing is fix itemtoTMHMId function,
    its the optimization works w loop but not switch rn

    following that, just go back to check for instances
    of the itemTM itemHM constants to replace if needed
    2/1/2025

    //got hlep from rhh on tm refactor realized for sort function
    need to have list ids created before function, creating list
    of things in function is too slow and takes too many resource
    plan to create file and or array of itemids in hmtm order
    based on hmarray and tm array in global.h file
    ghm_moves gtm_moves

    want to generate from a json/python script on make
    for futher optimzation (to not need to build every time you make)
    find some way of telling it to only rebuild list
    if there are changes in the global.h or src/data/items.h files

    global.h becuase that's where the tmhm lists are and items.h
    becuase there where you would change pocket item is in
    and the item importance
    to determine if its  a tmhm as well
    2/1/2025

    Addded make file changes and learnset jsons,
    in advance of using as template to create tm list file
    I prob don't need a json, I think I can just use python
    run from make file to do what I need.

    plan to keep all learnset data tho, as good to have 
    allows people to make game compatible with whatever gen they want.
    script isn't run unless config is set to true,
    //added to config.h file 
    2/2/2025

    got tmhm list python script working
    still todo properly set make file to only 
    run  script on builds when tm_List_data.h has been changed
    and work out how to display proper message at end of compile
    
    also idea to add gen9 egg move logic to project
    in gen9 when doing a picnic any mon with an empty move slot
    can pickup egg moves from other mon.

    Change daycare to be able to gain egg moves from other mon
    if has an empty move slot,

    Check how I changed daycare move learn,
    pretty sure I disabled it?

    once setup pc move delete move relearn,
    can prep mon put them in daycare
    and have them learn the egg move I want
    but if pc is oak ranch then perhaps they should be able
    to pick up pc moves from anyone in the box?

    can do extra dialogue for relearn 
    either relearn learnset moves
    or do egg move setting which will be based on any mon in box,
    or I can have it set auto w time via the daycare
    
    auto set in daycare,  manual set in pc/oak ranch
    double check how I have daycare move learn done,
    I know I completely disabled it for the box
    
    rather than relearn make pc dialogue
    to replace mark, be TEACH
    make that bring up dialgoue to pick from
    learnset, Egg, Tutor

    for tutor think check flag and once I've encounterd
    a move tutor I will learn how to teach it, like a tm,
    ex. went to mega kick mega punch tutor
    once I've used one or both I will be able to teach  both
    via the tutor dialogue,
    plan is have those tutors reset daily
    only one can be used a day and the other will refuse you
    
    if I pick kick, then go to pc the tutor
    option will let me select what encountered tutor moves
    that mon can learn, 
    returning "Pokemon/nickname has no available tutor moves"
    if I don't have a move yet for that species

    will need do like field moves and hms,
    keep flags for available tutors I've found,
    with list of what moves they give access to
    building a total list   vsonic important
    2/4/2025

    double check damage calc lvl 4 mankey at +3 
    seemed to do less damage than expected to mon
    several levels up.

    
    same level rattata got hit for 15
    3 levels up mankey took 5?

    defense is doubled so idk it may be fine
    looked at other game seems w lvl diff thats normal

    joke move tutor bullet seed, beside swallow :)
    or spit up and swallow either works

    ok issue, discovered why game break,
    alex says most likely memory corruption
    which is an existing memory issue from bad code,
    that can go unnoticed until triggered by access attempts
    from other code.

    it triggers on new game start so I'm assuming the new game
    is the issue, the hacky stuff done there to attempt
    adding in my control recs, if not that I have a major issue
    I need to diagnos 

    check bug catcher again potential issue?
    seems to have set ingrain some how?
    didn't see what caused it,
    it used bug bite and took my berry

    sigh ok SOMETHING is wrong bind broke AGAIN
    it triggered the same ingrain root issue
    not sure how it happened smh
    gonna assume its something weird going on w
    battle script commands or battle effects
    
    ok think its my sript? bug bite stealing a berry triggers 
    the glitch as well as bind,
    when bug bite is used again afterward the game freezes
    when thet trigger is used again it freezes teh game

    ...just using bug bite alone does it?
    don't even need to be holding an item
    will attempt new save see if somehow is because of shifted data
    from stuff was building, don't think touched anything
    that should affect it otherwise

    -was memory corruption apparently in new game intro,
    made some fixes there and it seems to have fixed itself,
    downloaded valgrind to analize my memory for further issues

    -Note**(
    Look into flag dmg in air 2x in air, see if they have logic for interupting
    flying moves etc. multiturn moves as well as just hitting fly
    makes sense as knock out of air,
    if so would be good use against sky drop as well
    make cehck to see if works


    Had a thought  inspired by something someone else was working on,
    and wanted to ask does it make sense, to separate the type icons 
    from the chart into separate files to get around the
    16 color palette limit or are their other issues I'm not aware of? 

    Idea in practice is keep the old gen type icons on the default list,
    then have fairy and any other new icons on a modern types image,
    and just do type checks and load from that file if its a newer type?

    If that worked would free up my type chart to 
    allow me to have the cleaner pokeball icons rather than
    the janky version I made
    )

    2/10/2025
    (remember refer back to note for owrk on black fog
    weather toggle flag toggle macro toggle)

    noted realized for task tm hm learn
    other move learn have to specifically load party menu
    //to not display exp grapics
    as it would block the can learn/not able to learn text

    nto exactly simple but not really hard either,
    requires setup new task that doesn't do normal graphic load
    //potential mode switch argument,
    //so would only display exp stuff
    if not mode move learn etc.

    also still has issue w tm rework setup
    need to print actual order rather than item name
    works fine for tm case but gText_ItemCantBeHeld
    is an issue need print based on order
    within tmhm list tmcase just uses GetTMNumberAndMoveString 
    2/10/2025 IMPORTANT
    -fixed just prevent then from being held,

    fixed bind it was just related to memory corruption
    fixing that fixed most things,
    but bug bite still has some small issue where
    it doesn't properly faint mon,
    mon dies but doesn't trigger faint logic mon sprite doesn't go down
    -found effect is tied to argument
    so think something to do w setting move effect
    doin 
    BattleScriptPush(gBattlescriptCurrInstr + 1);
    gBattlescriptCurrInstr = sMoveEffectBS_Ptrs[gBattleScripting.moveEffect];

    think the jump moves passed tryfaintmon
    think only way to solve may be getting the
    move effect refactor done...

    still fixing tm refactor need better sort option
    to fit tm options not in sequence based on item id

    then fix party menu exp share setup
    and add to script
    2/11/2025 

    can't figure out tm sorting,
    planning to use ghoulslashes bag sort
    which implements merge sort based on diff filters
    
    https://github.com/pret/pokeemerald/compare/master...ghoulslash:pokeemerald:bag_sort

    plan is do python stuff to 
    hard code the item names to match tmhm list
    then will have a filter to use to sort
    can use alphabetical filter to make work
    Hms would auto go first and pretty sure higher numbers would after lower numbers

    would need store length of ghm list to determine what number/ tmhm to print
    while loop over length of gtmhmlist
    use foundtm
    if found tm is less than legnth ghmlist
    (for now less than 9)
    name sub would be HM + (foundtm + 1) - since foudtm starts at 0
    ex. HM01 HM 02 etc.
    else
    would do TM + (foudtm - 8) should start at foudtm 9 so would reset to 1

    would add to botom of tm_list.py loop src/data/items.h
    for item id that matches place in gtmhmlist
    then search .name field and replace everything in double quotes
    nameSub is replace value

    ok I got the  sort working properly, my condition was just wrong,
    so hopefully can skip having to hard code the name values
    for work with hma may need to, anyway tho, just to prevent confusion hmmm
    anyway hmmm
    but for now just need test that item names display correctly
    in overworld, flsh freeze is set as 68,
    everything after that is shifted from the name value
    so all I'd have to do to test is drop ITEM_TM69 silver wind
    to pickup, if it displays as 70 its fine,
    if it displays anything else its not working
    2/12/2025

    NOTE**(
    for planned cap for ev gain,
    just leave it where default is, assuming 
    highest bst is 600  with base total you can add
    total 127 stat points to your mon
    so I should make it that ev gain caps 
    when your total bst adjusted for evs
    hits 727.

    That way you have more latitude for adjusting mon,
    should you want without making everything broken.

    The weaker things can come up, with effort,
    and the strongest things will stay where they are for the most part

    check effectivaly is ev gain is capped at 727
    hmm
    1st thought was only cap there for mon below 600 bst
    but if I do that for everyone
    then ubers are a beat more reachable as well, since the very top
    is effectively brought down a bit


    Also for pc access from overworld
    setup so mon sent to pc and immediately brought back
    brought back to party don't get their hp etc. refilled
    guess will hae to add a location argument
    to check for hwen accessing pc
    if location is not a fly destination don't heal
    when putting in pc, well check last entered
    region map I guess since usually you're in a building
    would need to include daycares as well
    ) - foud resource for that
    2/14/2025
    VSONIC IMPORTANT


    able to get party menu icons to display
    but still has issue with clear it does weird things
    icon dissapears when it shouldn't

    new idea put exp logic on one button,
    don't split for share and null,
    make it 3 button press share, null, off
    //what button press will do 
    should depen on what options are avaialable currenlty

    make other button be status setter 
    will be pre status allows setting
    status to a mon in overworld,
    idea is press button to cycle status
    hmm but then would be able to exploit
    to remove battle status, hmm
    unless I can make a new field
    statusedFromBattle?  make true false
    would be removed when status is removed

    could make it so cycle status never cycles to no status
    so it doesn't accidentaly...no I do want to be able to turn it off
    as that would also allow me to pre damage.

    could set poison and run back and forth till at hp I want 
    then turn off

    ok make value for battleSetStatus
    if that is set can't cycle status

    exp state w start button
    status w select button -done and doesn't appear to have set/clear glitch at exp does...
    2/14/2025

    consider, setting oak ranch as toggle?
    since apparenty some people would want low level mon
    think would need to make a boxmon toggle, then a option
    in box to block training
    block training as option into yes no,
    set boxmon value to stop it

    need a visual to tell at a glance its on,
    think see if can grey out mon not sure how to do that
    would need a monochrome palette
    would prob not look great for everything but ok
    look at mon palettes see if they follow some order of the colors used
    if so can put shades of black white in a specific order
    and it should look ok for most mon?
    2/17/2025

    //decided call it the omni box or something
    description: A unique box with special traits,
    Simulates the status  effects on selected pokemon.
    but cannot overwrite a status set in battle.

    says simulate to give reason why it doesn't change set status
    kind of like a heirarcical thing

    -finished fixing issus w status set and exp share state
    conditions have also been set,
    last thing is make the graphc for omni box
    and add other relevant item data for that
    and exp null
    Then add to scripts so can be given
    have teach tv old man give omni box
    have mom give exp null at game start
    omno box grahic rectangular brown box with black bordering,
    top of box has circular casings holding elemental energy
    one for each status set relatively matching color

    exp null just use exp share but different color I guess?
    //need setup party menu task modes or something
    //so can't set status/exp state while in move learn or doing certain tasks
    2/15/2025

    NOTE**(
    for pallet town fisherman decide make 1 in 10 chance to spawn on new game
    decided have him give old rod, with how other rod logic is done
    would be too annoying to try making good rod rod or something else fit
    new game leveling. 

    but was able to adjust w other changes so its not JUST magikarp
    you can get, but still all relatively low tier water mon
    
    idea for acquire new tms, give elemental punches from each trainer
    in saffron fighting dojo

    have poison jab be a hidden item in kogas gym that 
    reveals itself after he is defeated
    spawn at front near entrance

    best case want to be able to pick up even while
    its hidden

    setup pallet fishing guru and scripts
    on advice from lucky decide make oak ranch toggleable
    make box mon value to block exp gain, if you want to use a low level mon for strategy,
    not what I had in mind, but the entire point is more options so I should.

    Think what will do is keep it auto so people are aware of it,
    but institute the feature to block exp gain when I introduce the feature itself.
    i.e at bills house.

    idea I had is, rescue bill he tells about oak ranch
    joke hah hah pokemon aren't actually inside the pc that'd be ridiculous!
    after that whole spiel he remarks OH! that reminds me,
    then he rushes over to the pc make the pc light flash if I can,
    have him talk about an upgrade to the pc system he was working on.

    There its done.
    I just pushed the alpha version of the upgrade,
    now you should be able to select which mon, if any
    you want to exclude from the training at oak's ranch.

    The pc will perform effectively the same this is just
    meant to give trainers a bit more control over how their
    pokemon are raised.  *and that would be the end of that.

    /think then just have him launch into the normal SS Anne message 
    from there - should prob go into that now, setting up the feature would
    be ...no I'm not going to say it -_-

    from what i see bills pc doesn't flash?
    so instead just play sound effect while he's doin stuff

    bug bite broken freezing game again?
    unsure what caused hoping its just  the unfinished
    work i'm done on the pokemon storage system?

    bug noticed same turn stat change has graphic bug,
    ex mankey w anger point uses leer lowering target defense then gets crit
    activating anger point, the attack boost is applied correctly
    but it uses the green graphic rather than the red one for the stat change
    hmm seems to be an issue even if not used the same turn?

    bug endure isn't quite working right w multi hit or multitask ability one or other
    mon is dying to a multi hit move rather than holding on,
    and needing to be hit again to faint

    bug potenntial same terrain effects don't work,  starterrival had grassy surge,
    effect got triggered in everybattle??
    seems separate from me?

    very strange bug bite breaks as soon as all effects are done
    no matter how many bugs trigger after mvoe ends
    had used bug bite attack ended shell bell triggered
    then terrain healing activatd, THEN game froze
    even when set argument move effect to burn not infestation

    don'nt know why this keeps happeing so instead
    decide to do the move effects refactor after
    along w set of new updates

    ok realized exp share/ exp null aren't accesibility optimized
    resize letters  add null symbol 0 with slash through it
    add + sign for sure made new graphic looks good

    but idea for bill event sript small snag
    how to decide which direction he should go,
    I don't have triggers its based on talking to him,
    so I need player position to decide

    want to do movement script but need rely on relative position to player
    to decide movement so set that up as a new command I think
    check within one block, check trainer see distance
    idea return value 0 to 3 counter clockwise

    gSelectedObjectEvent = objectEventId;
    gSpecialVar_LastTalked = gObjectEvents[objectEventId].localId;
    gSpecialVar_Facing = direction;

    potentially these may do it?
    if I checked that lasttalked is same as current objectiD
    and then I can do the return based on direction player is facing?
    the direction I'm facing will tell me the opposite direction is blocked

    i.e if facing down, than up is blocked
    return value should be opposite facing direction

    if use current objecteveent id and lasttalked
    should be able to ensure player is within one tile
    
    GetObjectEventScriptPointerPlayerFacing
    u8 GetPlayerFacingDirection(void)

    //actually since this si going within a npc script
    //all I need is to return the opposite direction player is faving
    as they are already talking to the object in question

    decjide switch to use of GetPlayerPosition
    get object position use object id to determine which to look for
    if z coord is same object is impassable thus 
    cant move in that direction
    so return is based on player being in direction
    and z coord being the same

    New Idea add back gigantimax forms
    from Expansion graphics, 
    idea take gigantimax and turn into megas
    butterfree and lapras are what I'm thinking of rn

    Looking at show mon pic 
    think there could be something
    wrong w my implementation of decompression buffer
    removal. hmm

    NOTE**(
    Later comb over pokedex_entries.h file
    for species gen 4 up
    that use default entries

        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

    replace those values based on height,
    just search for a mon of same height
    that matches criteria
    essentially if mon is floating 
    look for a floating mon if it exists,
    pokemon offset is elevation a negative
    value there makes the pokemon float in
    size comparison box,

    hmm ok will have to do with python
    there's 8k plus values to replace oof
    ok store values for nat dex of species
    from gen1-3 
    loop the file once and build a table
    using all unique height values from that range
    storing all the scale offsets for later use
    think need a dictionary for that?


    -of note,
    there are variations within the same height value
    ex clampearl pikachu and mankey all use height value 4
    but are different sizes
    one is flat 1"  other is 1" 4'
    and last is 1" 6'  and the size reflects that diff

    so copying existing height based values isn't enough
    will, but should comb over list again to make small adjustments
    to suit

    )

    created boxmon value MON_DATA_BLOCK_BOX_EXP_GAIN
    set from within pc believe should be
    press start and will work on index hovering
    or selected mon,
    selected mon so can hopefully
    use the orange hand to set for a range at once
    
    for block exp plan make gray scale visual to easily identify
    effect is off, but palettes are all different,
    but believe found something that may work,
    the title screen uses 'TintPalette_GrayScale2'
    for the charizard/venusaur before the full color loads in

    think TintPalette_GrayScale has more contrast?
    so think may use that if I can

    Figure out how exp block should work
    since I want to work in daycare and box
    that means would need effect to not clear on removal from pc
    but the issue is I'd need to keep the visual
    efffect outside the pc, but then again if I get the 
    access from box working for daycare that 
    would solve all the problems.

    I could set the effect on a mon from within
    selection and when I set a mon to go to daycare
    it'd show the greyscale palette

    ok that'll work perfectly

    See if can attempt make dex scroll
    to all values from show mon page without
    having set limit for scroll
    //think if can somehow skip
    reading blank entires between curr and target entry/species
    instead read based on seen flag that would be great
    #check EE see what happens there
    checked and yeah EE has no problem moving
    betwen hundreds of entries to get to next value
   
    believe found it,  source function is Task_WaitForExitInfoScreen
    while main logic for movement/selection is TryDoInfoScreenScroll

    vsonic important

    found pc bug only one pokemon pokemon
    not able to cancel move bricks game smh
    -fixed issue was I set && when I should have set ||
    classic smh

    was able to test the vermillion custom script,
    it works without issue, but there's no message for it,
    need to see about making a message or if there's a give mon message script
    look at how trade stuff is done

    box access works now, but script is not quite
    right for selection, it doesn't accept the mon
    2/18/2025 - 2/19/2025 -fixed

    works for daycare etc. not for trade 
    all that stuff defaults to pokemon
    think would need to make specific box equivalent for everything
    or perhaps typecast some stuff??
    -fixed mostly, was issue w code for feature
    didn't properly filter and set the variables
    still doesn't work for in-game trade from box,
    but works when the mon you need is in your party.
    Trade logic uses pokemon so think will have to rewrite it,
    hmm could just make the entire thing use the box,
    and just have it use partyslot for the enemy so they're
    always choosing from party hmm that could work
    least for the in game stuff

    ex. &gPlayerParty[GetBoxCursorPosition()].box
    unsure if that will work well, for enemyparty unsure how box will for that
    don't think I can do anything nbut test it?
    based on struct it seems it should be fine?

    decide for trade since base setup worked for
    box from party,
    instead of scrapping make 2 versions
    for in party can just use normal setup,
    use trademonbox for other

    found middle ground testing now, -works
    also need adjust new naming setup to 
    account for not being able to rename 
    traded mon

    broke something, with box title is no longer dipslaying text correctly
    hmm ok its literally just the text font?

    just simple check for if can nickname,
    //if mon otid does not equal player id 
    return false, play fail sound effect
    -logic mon was raised w nickame, 
    would recognize a new name being used for it,
    its an animal

    setup new script for name rater made new specials
    to track if nicknamed that pair with ChooseBoxMon
    still need to add the list of items for name rater to give,
    and setup a timer,
    most likely on daily timer
    so don't worry about step counter

    ...ok something wrong w x defense its not working,
    need to figure that out?

    couldn't initialy find palette thing,
    decided instead, of doing palette grey
    add exp null icon on box display
    if have block exp thing,
    should be simpler

    changed mind decided just make sprite transperent
    same thing that's done on move item pc option
    simple clean and can be seen from a distance

    Also discovered option for how I want to do move delete move relearn,
    figured too clunky to add as list items 
    within pc,
    BUT, if instead I make them main list tasks
    it'd work perfectly!

    Would be just like select mon,
    only difference is changing what happens when I select a mon.

    Plan replace withdraw pokemon and deposit pokemon
    as they are never used anyway.

    With Delete Move,
    Relearn Move

    Just like how bill's pc changes pc options based on flag check,
    add the options as they become available.

    Otherwise Move Pokemon and Move Item will be only options
    There honestly isn't much point to have Withdraw and Deposit as options anyway
    -think can look at playerpc for figuring how to expand options
    w progression

    setup like select mon where press A on mon
    does task, think set callback to returntoPSS or reshowPSS
    then move Box_option stuff so move mon and move item is at top
    think want change move relearn menus so it selects from current mon
    or pre evos and generates list from that,
    just to cut down on list size a bit

    -may not do below, would be too much issue would just be annoying I think
    for most things. unnecessary at best

    Also need add nuzlocke banned to more checks
    //ex shouldn't be able to use for things that
    need to take a mon, should check if alive etc.
    ex. block from grooming, trade etc.
    //if (IsNuzlockeModeOn() && (GetCurrentBoxMonData(monId, MON_DATA_BOX_HP) == 0))
    2/24/2025
    )

    IDentified still have problem with new health setup
    HP MaxHP  the max hp and health bar
    is using that of the battler
    even if I'm healing a party member,
    because of that when I heal the hp bar
    glitches
    IMPORTANT
    2/25/2025

    Change summary screen remove gaphic press A
    to cancel replace with press L to rename
    since cant always come up with good nickname on catch
    believe would need a check for if doing so from within party
    or from the box, as would need a different callback
    -Finished callback, need to do lavender town event script
    change script from rename mon, to instead
    check if mon is nicknamed and if high friendship
    give a rare item as a congrats for a great nickname
    "Wow this pokemon really loves its Nickname!"
    "hmm I think this pokemon isn't used to its name yet"

    for party can use dex callback I already have setup
    but would need figure out pc stuff,
    hmm actually box setup can probably
    get me through that issue,
    since it shows how to return to proper
    box and slot
    so reattempt get summaryscreen to dex stuff working
    add new get inparty or box function to that
    so can toggle which callback to set/use
    after get that working can tackle new feature
    2/23/2025

    NOTE**(
    since make clean removes tools o
    from now on just make mostlyclean instead
    
    identified issue of event script not recognizing something as
    a constant, it needs to be included in the 
    event_scripts.s to be work

    add ability capsule to mart changes
    so can change abilities whenever you want
    in post game and in new game plus
    other ones use badge check have this use flag check
    FLAG_BECAME_LEAGUE_CHAMPION
    hmm think will keep roaming legendaries on for new game plus
    cuz funny to be reset to lvl 1 but run into a lvl 50
    Legendary and just get fucked

    Note change party menu so nuzlocke fainted mon
    don't move at all, just extra thing to make seem dead
    )

    planned
    updated event scripts & specials setup
    plan use python replace all event.inc
    .byte listings with callnatives to the scrcmd macros
    listed in script_cmd_table.inc
    to make more clear what they do, as names don't match

   //added magic coat as tm needs better move description
   also go over effect see if moves that reflect are up to date
   
   also go over daycare.c file see if SetEggBoost works
   pretty sure I got the special working but the comments show otherwise?
   1/30/2025

   for issue w starter pics look into CreatePicSprite
   see if that is related
   1/31/2025

    Unique hard mode baby!!!
    // check status move preference - idk if this is relevant thought of having type relation effect status moves but was too annoying?
    //I THINK I removed that? yeah I did, is never a thing but I experimented w it
    //makes in universe logic but is a bit too muc for players to keep in mind and to balance w learnsets 
    //and have status moves still be accessible and effective
    //hmm but actually if you want an extra challenge that could be a hard mode feature
    //would make completely different mon more or less viable as a result,
    //and force more thought on learnsets but if you chose the challenge there's no problem with adding complexity!
    
    in hard mode status moves take type effectivenss into account!
    -addition for mon at or above lvl 30, 
    //ensure they always have their strongest lvl 1 move if wild
    //and ivs no lower than 20 for all trainers
    //12/27/24

    Discover bug w 2 stat change in turn,
    need clear on effect otherwise next stat change effect
    will use that stat value
    ex. moody
    raised evasion dropped speed,
    then opponent used string shot which should lower speed,
    but it lowered my attack.

    Also Ability messages strench isn't setup right,
    if both player and foe have stench and one leaves,
    the effect is still in effect but instead of not triggering
    because stench is still on the field, it activates clear message
    and then reapplies it because enemy has stench

    also test inversion found hp glitch when switched out
     so some random case of switching is breaking hp
     hp exceeds max hp, bar
    ok foud issue somehow I can potion heal above max hp when transformed?
    //neeed double check this

    ok found a fix, its not perfect/doens't cover every condition,
    but realistiacally its fine since you wouldn't heal in the cases it doesn't cover
    as it looks like your health is full,
    and the change I added should still prevent over heal
    //1/11/2025

    Note since ditto now keeps its evs when you transform,
    its fine to have ditto take nature of the enemy,
    so it can get the utility of funtioning as a nature revealer.

    double poison still broken at times no idea why,
     added feebas logic as counterpart to magikarp
     has chance to spawn feebas every time encounter magikarp
    1/12/2025

    tweaked sprite gfx logic for transformation, removed use of gTransformedPersonalities
    //added my own disablestruct value to track ability that sourced transformation
    to ensure proper shininess of transformed sprite
    tested works no noticed issues in tests.
    /1/12/2025 tested w inversion, normal transform, and w unown created before change,
    and tested after change to ensure no differences betweeen.

    //also idea change stall to work w trick room since its such a big thing
    //make it so all stall mon go first in trick room 
    //takes worst ability makes it best,
    //can turn any mon into perfect trick room mon
    -done reworked to do effect from turn moveFirst function rather than 
    a flat priority set

    //new idea move switches out opponenet, then also switches out user
    //Think will call it Foil, as in foil the foes plan,
    //will be major disruption move low damage think bp 50,
    //and believe will make it a dark move, not sure on split 
    //but either way niche move that doesn't seem amazing for sceptile,
    //until you consider the mega
    /12/25/24

    re-reworked cloud nine and added default cloud nine as a flying ability
    //think give all cloud nine mon access to all weather moves (via tm)
    /12/29/24

    //for mega mon that change type realize will have to add that type
    move to their base learnset, believe at the time wasn't dnoe for the most part?
    -note give amphorous stronger dragon move if possible since apparently it can't learn draco meteor

    Also new idea for handling move setting,
    instead of having to find npc to teach/delete moves,
    make it find the npcs pay to be taught their skills,
    (oh you came here for me to teach your pokemon a move?
    well I don't do that anymore, sorry...but if you want
    I can teach you how, for a small fee of course. oh hoh hoh)

    Do same for move deleter, but since he's a forgetful old man,
    don't do a flag check for having already talked to him and new text,
    just make him do the same thing every time, meaning if player is forgetful enough
    he'll just keep taking their money lmao

    But after learning from them a new option will become available in the pc,
    select it and you can chose from forgetting or remembering a move, for the selected mon
    Will need to reorg where these npcs are, its a good feature
    want it to be accessible move deleter should be first as you won't have many moves 
    to remember early on.

    Ok think put move deleter npc in overpass building (same place find oak aide)
    to the side of the route to viridian forest, (over where diglett cave exits)
    So if you explore you can access it right after beating brock and learning cut,
    (rather than in fuchisia city) will serve purpose of expanding options
    (will allow deleting last move) like say making magikarp struggle.

    Move reminder is typically not available until 2 island but guess
    could make him replace the move deleter in fuchisia city?
    Is a bit later than I want, but you could also get to it earlier 
    with a B.O or access to a stench mon, you can probably,
    reach fuchisia by cerulean city soon as you get surf with a bit of luck
    -move reminder should check all learnerable moves from current form upto lvl
    and all prior evos, then create a list from that ignoring any overlapping moves

    think would need alloc and multiple loops,
    make 4 arrays in function alloc memory to them based on number of evos,
    i.e learnsetevo1 learnsetevo2 learnsetevo3 learnsetevo4 (just for caution)
    compositeLearnsetArray -total list

    if mon has 2 prior evos would use learnsetevo1 and 2 array, 
    then just pull from   current form species
    adding to teh compositeLearnsetArray as you go,

    when you check each new species/evo learnset compare the moves w the composite array
    if move is already there don't add/append think function needed is appendtolist?

    Think make B.O accessible in pewter (put in the flower patch)
    after obtaining cascade badge, so to get it you'll have to backtrack
    for it.
    12/30/2024
    

    Abilities are getting too complex for ability length,
    think I may need to add I think Sbirds scrolling ability box text

    If I could just scroll once, to at max have 4 lines, that'd be great.
    12/30/24

    //Note tweaked Recharge effect to allow player choice/action
    on recharge turn, pretty much just allows mon to have an item used on it
    or be switched out should it be chosen
    Gives recharge moves more room - for sake of balance could set recharge even if miss now?
    //nah not doing that, far too punishing
    //12/30/24

    //Changed Dragon Ascent to dragon move, make physical
    equivalent of Draco Meteor, setup as tutor move,
    do at cape brink where you learn starter hyper beam equivalents
    add another npc in the house who will teach the apex dragon moves
    for 2500 or 5000 cash.
    //12/31/24

    //setup gen 9 new abilis for legendaries quark drive oricalcum pulse
    along w the paradox abilities, effet mostly set by not quite right,
    as still haven't done item expansion to get the new items

    //buffed safety goggles, setup like utility umbrella
    //where blocks effects

    Also changed chingling into chimecho evolutino to
    make chimecho better, can run eviolite
    //12/31/24

    //checekd multiplier result and type effectiveness is near perfect,
    its exactly where it should be so no need to change anything regarding that 
    luckily

    double check anticipation logic, see if its supposed to end after one turn,
    or only when I get hit by the move I anticipated
    if I switch into doubles its kind of pointless to lock it to the move
    would make more sense to "sense" a move get info about it,
    but just avoid whatever comes, because you're anticipating an attack.

    Then anticipation and forewarn can effectively work the same but read different info
    or different quality/level of info.

    If it works that way then I feel perfectly fine, letting it just be a one turn thing
    -edit, checked it is one turn/attack, but the invul is linked to the specific move,
    will change that, it reveals info and gives invul, that will be  the effect
    //to balance will make exclude status moves something like killing intent
    =//ok effect done it forewarn returns exact move,
    anticipate returns category of move, or strongest move not name just info about move
    //now works, off whatever attacks comes at it first, does not activate for status moves

    mold breaker shold stop anticipation forewarn
    need set exclusion
    //also seems sticky hold and magma armor arent correctly removing items
    unsure if todo w change to item storagae values for 2nd item slot
    /1/4/2025

    Notice not only move info but also dex callback and transformation stat gain on lvl up
    seem to break on switch look into all 3 effects find what they have in common
    Presently those are my last known bugs, I guess someone presiante that 
    they are linked together
    /1.3.2025

    //VSONIC IMPORTANT keep in mind I apparently setup
    status effects sleep and paralysis to ground floating mon,
    keep an eye on and consider if I want to keep that

    major idea, base game setup is based around a specific set of mon,
    and guaranteed encountes if I instead switch enconter tables for pools.
    I could introduce much more variety and make a journey potentially feel more unique
    and add replay value, hey there's so many other mon you may not find on your first route
    This is obviously to the detriment of people looking for specific mon
    But is an interseting idea.

    I've added mechanics to make it more rewarding to grind/
    searching repeatedly for better versions of the same mon.
    better iv distributions planned nature filter
    and more abilities

    That runs somewhat counter to the idea of a larger pool of mon,
    but if balanced correctly could instead incentivize breeding,
    if you get one of the mon you can easily breed it with a ditto (which I give for free)
    to attempt getting other abilities, and also ability capsules will 
    eventually be made available
    
    would allow me to set species based on ecosystem,
    rather than exact species could say ok this area 
    has grassland/field birds  grassland pokemon
    //forest creatures are fewer but present,
    //and then some beach/waterfront creatures 
    //if it suits the area, and then just 
    //repeat the group for what should be more present
    //note that at present most places only have 2-4 mon available

    //wouldn't work with nature filter tho,
    //you want to know where a mon is turn on the filter
    //and then get that mon, if it was too low odds to reoccur
    it'd be a worthless system
    Vsonic Important

    -sigh seems to be some issue with speed logic,
    faster mon are going last...
    ...ok so its not turnorder or speed logic,
     for some reason just holding an item with
     HOLD_EFFECT_RESTORE_HP  auto makes me go last...
    -edit fixed
    sigh...it was a bad condition/operator logic,
    it was just luck that it defaulted to a hold effect value that I could actually find

    gave wonderguard weather immunity for duration
    iron ball now also increases weight by 50%
    and float stone now boosts rock type speed by 50%
    also finished adding last semi invul status to weather exclusion
    in air is still hit by sandstorm
    turned it into a counterpart of iron ball

    fixed wimpout and emergency exit rework,
    now working correctly in all scenarios

    identified issue w nuzlocke mode w pc,
    it occurs when scrolling between mon in the pc,
    from alive to dead,
    it for some reason clears it
    but only on view it doesn't change actual values?
    as reselecting after closing sum screen still shows them as fainted
    -fixed

    rebalanced multi-task fixed missed move exclusion removals as well.
    now much more in-line with normal dmg.

    fix give tm all, updatae tm case scroll logic, - done
    and begin tweak debug stuff for my changes

    don't believe properly setup embargo/bandit king
    code is in battle main adn util, but there isn't anythning aroudn
    item data that actually stops using items...

    early bird breaks self buffing status moves that activate same turn wake up
    and seems cupids arrow is also broken, trigers move use and
    freezes game - fixed

    also seems logic to work no matter gender of enemy mon for cupids arrow
    isn't working   
    -fixed

    talked w ppl in pret realized not able to fly between region maps
    i.e main map and seviis etc.

    with that in mind, create new fly input for swapping maps.
    the fly menu has a weird icon you can click on that functions as a cancel
    which is dumb since you can just press B.

    //alread instead of that make clicking the tab icon
    bring up a window for selecting other region maps

    //creates window over laying map and putting a grey out over
    the background map, and in orange letters create list for selecting which
    map to load on a press close box and fade out fade in to load
    that map instead of the other one.

    fly map already has grey out box for when hovering fly location
    use that to cover the entire map for grey out

    for pokedex from summ screen check pokemon_stoage_system_5 I think
    where it uses cb2 summary screen call back, 
    believe setting up callback function will be what I need

    -benefit being more intimdate knowledge of your team/party
    plus a quick and easy way to check evo methods
    simple things is make it nto scroll
    but if good can potentially do like storage/summary setup
    where scrolling in one will update the place of the other on return
    hmm but not sure if can create a list on the fly like that.

    probably can't, since even the alt lists or search dexs
    aren't actually made on the fly, but instead pulled from
    existing arrays or maybe not, emerald seems able to 
    populate a list based on conditions with a loop

    in fr searh dex is different built form static arrays
    in emerald its created from conditions

    I may not need to make an entirely separte function for the dex stuff
    if instead I do with callback, may be able to overright base logic
    w a check for saved callback, i.e if savecallback equals summ screen
    when press b, go to that instead of normal logic
     beliee can use Task_DexScreen_ShowMonPage  but mayuu 
     need intermediary function to set currentmon to dex species
     when both are static

    ...kinda dumb but realized the entire debung menu is essentially a callback i.e what I need
    all I have to do is emulate that.
    will also help for setting up pc access from overworld
    as it already has a menu option for that

    -took closer look seems other than battle debug
    seems they all just use existing callbacks to move between things
    rathe than anything custom, and all plans I have require
    things a bit more specific

    passing species not working 
    look at how pokemon storge does it

    -got working

    //attempt working on all planned callbacks for major feature update
    i.e move info from battle

    register mon from battle bring out dex. i.e press shift
    //will need to figure out area screen issue 

    add option menu for effectiveness of moves in battle toggle
    use red, orange, green, blue

    also on new game screen add recomended button message
    -done

    NOTE*(
    IMPORTANT thought from josh many mon in base stats file
    are cosmetic variants things like vivillion unown etc.
    are just taking up large space in for no reason, each entry takes up
    entire space of base stat struct regarldess of what you put in the block
    so make species graphic info file to hold the graphic data, keep the species constants
    but can remove from base stats if identical stats name learnset etc.
    since base stat update has learnsets placed in base stats would need
    to popuate learnset and stats from base species

    Think what will do is make functions for checking 
    if a cosmetic variant if true return stats from base form
    make base stat flag for cosmeiticforms on base species
    i.e on unown add flag hasCosmeticforms
    when puling species stats (wold only need in one place as battler stats
    are pulled from species stats at battle start)

    auto check form specices table  value 0 for base form
    if form has cosmetic form flag then use that form as species data
    form ability stats items etc.
    pretty much just use that as the species rather than actual species
    everything should fall into place following that

    can use form species table
    if (gbasestats[GetFormSpeciesId(species, 0)].flags == F_HAS_COSMETIC_FORMS)
      appliedSpecies = GetFormSpeciesId(species, 0);

    that's all need, would make take base stat data from base form
    then just finish setup species graphic function and all good
    //only things to keep an eye on are cosplay pika fomrms

    minior forms  and arceus/silvally

    pika forms are simple and mainly why didn't just reset species
    under check can do if species == (exclusion species) cosplaypika forms etc.
    appliedspecies = species simple enough for that part at least

    well don't have my grahpic data in base stats so can already make that change now
    made base setup, put code in learnset tmlearnset
    battle script for switch in for taking mon stats from base stats
    and in boxmon for setting intial learnets, unfortunately still working on graphics
    stuff so can't make test build, but will commit with adendum for now

    while was at it, setup vivillion evo similar to milcery
    and alcremie form and vivillion form groups
    but honestly could just do with function,

    could use the exact same functions used for evo they were patterned after
    unown form generation logic anyway

    no def don't do that -_-  unown doesn't change species it uses
    the base species for everything but changes form based on personality generated

    I want to actually generate a diff species so can easily link
    directly to the graphic table

    ok was able to get species grahpics file up and ready
    pointers are set just need to populate table
    then can remove the other files 
    plan to add species names to base stats as well

    Looking into python scripts to fill table

    and will go back to pokedex screen and see about
    getting the names to load in correctly
    I got it to work for other things so feel it should work
    think its just a matter of finding the correct buffer

    ex. got item names to work, for the player pc
    that scrolls and properly loads mon names.

    so no reason shouldn't be able to do same for dex.
    then can swap species name to base stats without issue


    so yeah instead just see about using the target species forms I made
    for alcremie and vivillon

    need to undo some things made to match existing tables
    /grahpics.h extern names

    also look into crt0.s file can prob remove uneeded tings
    based on EE version?

    and remove remainder of references to thos etablse
    but looks like regex python scripting is goated
    and I believe I have a handle on it

    go in line when I need to can only replace by using full file
    when I'm replacing distinct entries i.e species name
    as it works by replacing every instance of the occurance throughout the entire file
    can use it to quickly add species name to base stats file
    useam filter as initial py script
    but replace bracket species name

    just need exlusions for mega alolan megaX etc.


    )

    gltiched form stuff idk seems potentially directly related to ogerpon?
    hopefully best case ssssssssssssss...
    ok got lucky issue is literally just ogerpon not sure why though
    only happens when viewing ogerpon forms
    raised alloc value and ogerpon loaded, no idea how well it'll work but it loads

    also made adjustments to dex code so no cosmetic species
    outside num_species work

    may exclude species that evolve out of necessity,
    otherwise don't think can link up w proper forms.

    i.e blue floette evolving to blue florgess

    still have issue w dex evo page,
    doesn't make sense as eevee page worsk so don't 
    think can be because num mon,
    instead think its because of not properly defined
    evo methods
    -wasn't that
    annoying but seems still have issue
    potentially seems to do w a 2nd stage evo?

    only noticed or dipplin and mime jr so far.
    idk why I still have issues

    //made adjustment don't know what I'm doing
    //but it works for now

    also missed issue w nat dex for some reason
    doesn't build full list around values
    it only builds the initial value everything
    else is 0's...

    so something wrong w create list
    -fixed

    also somehow messed up old forms stuff,
    indeed zacian etc. not pulling from base form for dex..

    fixed issue,

    use python redo type dex list
    define type num by type list
    assign each type list to the text name of the type
    val0 is normal type which is "TYPE_NORMAL"
    loop base stats,  down to species_pecheraunt
    eading mon_types() to get type1 and type2
    for species
    will need constant loop until reach end of type list for both types
    order of addition to lis is, type order 
    if type is same use lowest dex num
    so think will also need species.h file 
    use SPECIES_NAME store number from species.h 
    to know what compare values
    hmm its possible I may need multiple dictionaries
    species dict. and type dict.
    and have to compare the base stats list against them both

    anyway loop base stats species,
    Set type1 & type2 to normal
    increment type2 before type1,

    loop species up to species pecharaunt until End = true
    start from bottom of base stats,
    if species matches type1 & type2 add to list
    put type increment at end of species list
    i.e 
    if species = species pecharaunt 
    {
    if type2 does not equal fairy increment type2,

    if type1 and type2 equal fairy
    End = TRUE

    if type 2 equals fairy and type1 does not equal fairy
    {
    increment type1
    reset type2 to 0/type_normal
    }
    }

    looked at emerald may be able to use
    that to build list from scratch
    seems to build from scratch fast enough
    if can do that would save space,
    by allowing removal of type list.

    and be able to build accurate lists regardless
    of type changes

    //nvm  can't do that, didn't realize
    but EE isn't building a full list
    if i set type to none,
    it just builds the normal nat dex listing
    which is why the load time isnt' longer
    its not loopign a type list at all.

    so I do need python and not the emerald logic
    for one EE doesn't work in specific order it just loops species list
    and adds any mon who matches  either of the type combinations
    I would need concurrent list loops to fill every type

    and while I could build it, it'd be very annoying to manage
    especially with having to use same index for scrolling
    so best just do with python
    
    ok if I'm loooping base stats
    think I won't need species num
    since it is already in order

    not sure if loop base stats file
    could instead loop the file once
    to build a dictionary
    using key species and storing type
    then I can just loop that dictionary
    as it should only have bulbasaur
    to pecharuant and have all species in proper order
    -fixed

    compared w pokefirered and noticed sound still off for some things
    start screen horns are incorrect
    so need go over sound data AGAIN




    seems gen 9 forms, aren't properly showing bst?
    palafin zero to palafin hero doesn't change
    everything else changed correctly at least

    triple check bandit kind and energency exit likes
    was in oak battle but bandit king still seems to show text
    for wrong side.

    and using emergency exit for last mon in battle 
    seemed to fail and end battle, even if move misses?
    in oak battle triggered stat buff attack,
    missed move but battle ended as if I won
    ,if oak battle still has logic for playeer not missing
    that could be the issue?

    -tested it does end wild battle 
    see if that's normal effect
    
    yup it ends  trainer battles too FUCK,
    need to fix
    --fixed

    IMPORTANT
    new idea for after put ai back in C,
    make ai struct for num switches
    so ai can't just constantly switch and make thing annoying
    idea, nuim switches should be n + 1 / 3,
    where n is teamsize, so min 1 switch, max around 2?
    or do n +1 / 2 to max at 3 potential

    make it potential so just cuz they have free switches doesn't mean
    they have to use them

    got graphics working still to do is pull in pal icon indexes
    and gen 9 indexes would need to pull from base stats
    and add species name and cry data of course
    was able to save some space with the graphic file not needing to use multiple arrays
    so hopefully will still be under after audio additions

    sigh ok graphics file update somehow broke trainer graphic callback
    so need to figure that out
    just look at functions that call trainer and mon pics think
    in decompress & pokemon.c

    need fix type effectiveness for single battles
    to add exclusion for move that target user
    -done

    but believe may still be some issue w dmg formula round lvl 9?
    for lvl scaling mon was just chickorita tested but
    w lvl scaling setup got destroyed by mon 5 levels above
    did barely any damage

    for some reason learn move dpads go to differnet battler no idea 
    how the hell that happened caused horrific strobe effect
    do NOT release patch until fix this

    was able to track and fix, whenI added summary screen battle callback
    meant to be used for move info in battle.

    I used an if when I should have used an else if
    and it triggered the other input function.

    can give new mon think issue is lack of dex data? no nat dex data
    idk but doesn't work to givee resets mon, guess need check 
    give via main scrit not debug even though uses same script?

    noticed list stil loads as 3 digit instead of 4 until scrolls?

    think should look into summary screen and see about increasing
    text spacing for stat display, if possible

    was apparently an unaddressed issue w letter spacing
    value was never actually being passed/used

    Redid the setup and now it works as expected

    hmm or not, since even for pre-existing mon debugger is being buggy 
    and just not giving me the mon? -  nah was cuz of somethig I had removed apparently

    *FACEPALM ok now for soem reason all mon are showing shiny in pc wonderful
    -fixedissue was hadn't properly updated all places new palette logic was setup
    was still using otid rather than shinycheck

    //need rework pp set on from debug,
    return to battle doesn't keep the pp change
    think its an issue of how I changed pp setup for the structs/getmon stuff.
    fixed, wasn't something I broke was part of debug that was never setup

    double check handle deoxys pic logic, causing some issue.
    may no longer need logic?

    checked removed and still same result, weird thing
    only base form deoxys icon is busted other forms work fine

    so is something directly linked to deoxys
    fixed 

    ok yeah dmg formula seems still fucked
    lowering dmg scaling lets you live better but
    that also means levels matter more, so you can't take out
    enemies levels above you

    //using desmos graphic tool and w3schools printfs
    was ableto come up with a much better dmg formula
    will use mix of that and previous found formula.
    will use old formula for early game to about lvl 5
    so it goes a bit faster  then use the better scaled formula throughout.
    doesn't need max

    ((((attacker->level*110)/100)/5)+(((attacker->level*168)/100)/13)+2)

    scaling is much better but it still falls off far too much at higher levels (20-30)
    so looks like i'll have to adjust curve at multiple quartiles to work.
    want to keep my balance mechanics so wrap those in..
    actually no those are perfect as is I think,
    what I need is just to adjust the normaldamage formula scaling by bracket
    i.e don't divide by 47  lower it 

    tested values in w3 and as levels grow slope gets
    closer to normal scaling level.
    and is more consistent.

    So idk what I need, using 46 should be as low as I go,
    but there are some points where its exactly at original scaling.

    I'm not sure why the scaling is seemingly so low with the values Ihave

    hmm remembered I also changed the stat formula so hp scaling is different.
    looking into difference of hp formula changes

    first look it scales about 20% higher on ave, but the higher base hp
    the lesser the effect is which is good, whith levels around 200
    its down to half averaging just 10%
    but that said it was made that way with the increased stat scaling in mind
    for other things, but it not acrsos the board this is just for max ivs.
    as I increased their potential so hunting multiple mon would be more relevant.



    idk why but I completely fucked the hp formula
    instead of hp and relevant stats being  relatively comparable
    I made the hp formula able to scale up to near 4x the size fuck me

    ok reworking lowering hp formula,
    lowering iv boost from 210 to 170 to approximate a mon
    that is 80% ev trained

    replace 200 with 2 and use other adjustment
    now hp scaled up by up to 30% with this stupid nonsense I did
    what this means is all my damagecalc adjustments are off.
    so all those numbers will have to be raised
    (by that I mean the part where you divide by a value to augmnet dmg)
    increase the numbers below 50 so they do less
    lower the number above 50 so it doesn't cut off as much

    ok new formula seems ok? overall bad cusotm formula added about 50 points to hp
    new cusom adds 30.  (at relevant level)

    may still sound like a lot but that's still about a 50% cut,
    so everything should die twice as fast.

    seems tobe doing ok, didn't need to change dmg from scaling?

    also of note ghost absorb dmg + liquid ooze seems to be working
    just fine, for clarity still better to make its own script effect
    move end ghost absorb or something?
    rather htan needing to calc damage twice
    with heal logic function think can just use hpdealt
    copy logic for endturnheal just make effect and call it
    well most liley a pushcursor callback w a return in script but yeah


    ok emergency exit failed when taking fury cutter
    not sure why, look into that

    actually think I figured it out, hp before is
    set on move choice?
    rather than switch in which makes it fail to check for hp on switch in
    in case switched into damage
    fix for that is setup hp before on switchinl,
    then set hpbefore in move choice only if not first turn
    i.e firstturn != 2, so only do that if not the switch in turn
    -yup that fixed it

    emergency exit just broken all together
    dmg formula weight more towards defense from getgo
    if you're lower level than enemy, you're still weighing
    directly against their defense,
    while your offense is not on the same level because
    of level scaling

    seems finished removals for removing species name
    saved .10% on rom space seems to be no issues?
    still unsure that dex isn't causing a memory leak but its working without issue
    for now.

    now back to python to finish making species graphic file

    see about using python to create new physical array for
    type weight etc.
    rn specifically thinking of the type arrays since my type changes have changed things
    chart organized by order of types, lists type 1 matching type 2 first
    and then it lists alternate type 2s based on numerical order of type constants
    should their be a matching type, it defaults to printing
    them in order of dex number low to high

    would need track mon, montype and create logic for determine type is matching
    and use that to say if mon type2 matches type1

    may need to do multiple passes at it,
    loop checking and adjusting for multiple conditions

    first pass just to print the types in order,
    then check for if order of matching mon are listed
    in order of lowest species number

    think can do check entry and entry + 1
    if entry + 1 is matching type to current entry
    and it has a lower dex number swap their placement 
    with current list

    looked into python it has sort function
    once i make the list I can make logic for
    sorting it with my own function
    so no problems there

   


    note for some reason area windows are off,
    area screen covers up portion of sevii map.
    not sure how that happened will need compare
    to base firered area page, as I don't remember ever
    changing anything

     think it may be the expanded mon name
    and for some reason addition of the bst stuff?
    seems its all using same window so same dimmenssions 
    can fix by making new window for area page,
    that or I'm missing a clear when I move to area page?

    IMPORTANT discovered some form of issue w quest log
    not sure if its event 2 itself
    or something directly tied to the shop
    but quest log of buying items in shop failed to load
    and froze game unless quickly clicked through
    -2nd thought think its change to mart logic
    I used dynamic setup now instead of the static mart list
    so could just be that I didn't make this info available to the quest log
    -checked and confirmed it is the mart that's doing this,
    check gShopMenuHistory see if can make work

    ok reverted mart command change it still doesn't work
    *facepalm, so idk how its broken great
    -fixed quest log issue, issue was bad item name logic

    setup move type function
    not often used but in move priority & for charge

    had idea for two typed move to change move type
    for two type moves with type change ability
    but game isn't setup to change 2nd move type

    so may just leave it as is?
    idea being ability is only strong enough to change main type?

    fixed nature power so recognizes called move
    double check it would change move type with abilities that change type
    -tested it does work

    also adjusted nuisance so it excludes 1 power variable power moves
    don't really like this change but couldn't figure out how best to 
    do it unless I potentially move all variable power moves into attack canceler?
    (think atk canceler is when prioritu is set)
    if I can do that then dynamicbasepower can be used
    can make a big function for this and save on some battle scripts
    but that's a big change so befor I do that need be 100% sure
    that priority is set/called in atk canceler
    and not because doesn't quite make sense makes more sense
    for it to be done before move use?

    ok we have a speed chek, then a priority check
    -think can't do  will just  leave to exclude pwr 1 moves

    
    eventually update setup for 2turns moves
    also go over statuses again and remove what I can
    prob the timers replace with struct values where I don't need
    to direclty refer to the status
    potentially needed for gen 9 additions
    also watched datodoya playthrough pokemon fr  and dmg balance seemed fine
    zangoose vs shuppet, potentially but with my drop to super dmg
    its possible I may need it just to get even, even though being even 
    isn't what I wanted?
    bottom line keep an eye on it at higher levels than early game
    possibly may only actually need the scale down part for weaker enemies

    also need ensure its still fun/challenging/exciting don't want it to just be 
    even even when fighting enemies far above you.
    so take note of that as well

    fixed icons pals garahpic file tec.
    tired need go over later

    still need fix missing grahpics
    some icon pals even copied aren't correct 
    but with my debug addition simple to find correct value
    for few missing
    fixed weren't missing issue was conflicting references,
    between use of old file and new graphics file

    also for some reason some of the offsets are off,
    just things lower than they should be it seems,
    ;had to adjust wo-chien by from 10 to 6

    and size is somewhat inconsequential,

    updated base stats evos for gen 9 mon to relative evo setup
    
    for issue w gen9 mon  of dex
    think its just becuz mon not seen/not in dex not actually
    something wrong hmm

    fixed cap and  order logic for dex, still not showing dex page for gen 9 mon,
    fixing that is next step, - prob just check drawmonpage I guess 
    
    then can get back to working on the stupid battle callbacks smh

    todo revise species list for removal of cosmetic forms
    first setup like unown, idea is move speices constant after num species
    so define exists but doesn't affect num species and doesn't require going on base stats array
    this will save both rom space and more importantly ewram

    issues, finding a fair/practical way to get the forms,
    simplest is just make it based on personality. btu don't know if that causes
    problems with chance of receiving certain forms etc.

    other concern is to still be able to display forms in form dex
    -may not be an issue but still

    rn did partial removal, alcremie forms aren't listed in species
    issue is blank space in debug menu, is only place would be visible.

    //need add gen 9 dex_entries, annoying since EE split to multiple fields onbase stat
    //but doable w python

    NOTE**(
    major IMPORTANT  idea
    item cloner, with addition of more mon  remove need
    for multiple means of having the same good item/battle item
    so you get the itme and then you can clone it.

    Now don't want this used for everything to invalidate
    everything, but would actually do really well for improving gameplay

    plan is to make it cost money as the resource to use it,
    think like an "app" so premium feature/in-app purchas to make it work.
    "Thank you for using Item-cloner, we look forward
    to your continued patronage!"

    rn thinking make around 700 maybe 850/900
    so its still more expensive than just buying 
    most items itself.

    only issue is poke stat items i.e calcium protien etc.
    could make exclude them as in-game pharmaceutical ban
    but wouold be nice for the player.

    lol fossils aren't key iteme so you can delay your fossil
    and have multiple and cloning fossils would be massive
    for money farming

    double check fossil, see if it uses level scaled function
    or it still comes out at level 5.
    alraedy fixed scaling its good,  but also fossil logic seems to be weird
    in script, seems potentialy only allows you to revive same fossil once?
    need test, but also change script to use a new command
    that handles all fossil logic, so can do it all with a single script,
    instead of jumping for each type of givemon for the fossil

    especially since will be adding like 10 more fossils to the list
    will do string buffers and flag sets based on item value given to revive
    like, oh that's a item_name fossil, it turns into stringvar species
    on give mon, set flag revived x fossil, if not set

    set var value to determine what sets
    so need 2 functions  one ot populate info for first phase
    giving item, and populating names for script

    and for giving the mon, and setting the flag on return.
    just have same table in each to build values off of,
    set var in first function to identify which fossil is being revived
    think will is have var be fossil being revived
    and have it store itemvalue

    if var fossil not 0 do stuff etc

    if I'm going to have players delay fossil to clone it 
    and have multiple. no  point in making it not scale

    but will exclude key items obviously.
    Think could give this at silph co?

    That way also won't need to give multiple of an item

    *Decided WILL add de-evolve to cinnibar
    with plan fix for learnset nothing will ever be missed
    and opens up room for strategy
    as certain abilities now work off nto being fully evolved
    and offers eviolite option

    even better with my changefs to see stat dist. and bst
    to know beforehand if eviolite would work

    )


    NOTE**(
      with encounter changes planned would not be able to repel filter stuff
    but if setup right I would still be able to use magnet pull etc.
    to pull out specific type mon...ok here's what I could do
    intead of limiting based on level, could intead do based on bst.

    would require indepth knowledge but that's fine
    check would be with repel up, you keep away 
    all mon that have bst below or equal to lead mon.

    with expanded effects for repel items pretty sure
    would specifically need base repel to do this??

    ok repel is 1, 1.5 and 2, technically I could still use those levels
    for the encounter filteriong  in TryGenerateWildMon function
    need figure wtf WILD_CHECK_REPEL  flag is for??

    as of yet haven't setup abilities that filter encounter
    so it'll filter level then use bst to filter species for repel

    )

    



    alt idea rather than directly take player level 
    can just set high to a function of original level and player level
    that way actual level is still dependent on area of the game
    so it different places are still different strength?

    I'm thinking 2x original high, + 1/3rd player team level?
    ex. viridian forest where things usually hit max 5/6
    given a team of around level 22
    it'd put the new level at around 17

    or use it for the low instead
    */
   goto CRY_LOGIC      //tested cry data before as preface before adding gen9 cry data and found cry data is borked *facepalm
   //not loading correct entires for forms, also cat names for forms are also messed up no idea when that started
   //think change cry function, take cry table out of inc, put into C file, so can more directly refer to cry value via species
   //looking into could potentially be issue only linked to dex, somehow from improper use of dexspecies?
   //nope its all fucked, identified thanks to debug menu

   /*
      ok its all messed up and beset fix I can gather is moving data to C for better ease of editing/organizing
      its in order of list and I think issue is just that species are not in the same order as cry file somehow
      well not really somehow I've moved things around quite a lot

      so I took the enum cry constant from EE, replaced hoen cries with it
      and think will update graphic info file to also take the audio data
      makes most sense, its all the data for species addition

      while stats will stay in stats, so I only need include stat data there i.e
      mon that are NOT cosmetic species

      only thing I"m unsure about is the whole reverse cry thing,
      its done w macro?
      would need function then to ensure still does the reversal.

      but if works can take some space back w the removal,
      of the extra cry table

      but anyway will need major python application
      to get data set, needs match cry names in directsounddata.inc

      so will need title decap names now in cry file

      replace CRY_ w Cry_ for the name itself run the title on just that section
      same logic as did for grahpics info first

      replace underscore w space, run title
      remove spoce to recombine and it should be fine

      after that I just need pull the new cry constants
      into the graphic info file and make my version of the 
      "GetCryIdBySpecies" function of expansion
      //is already in pokemon.c just commented out for later
   */

   goto WILDMON_LEVELSET
   /*

    make sure trainer pic slide in 
    is mover  over just slightly so its within circle
    -compared base firered its actually good,
    its working as it should

    sturdy not displaying hung on message..
    -fixed sturdy message issue was I made the flag valuie
    too big for type,  removed use of moveresult sturdied just wrapped in hang on logic
    works fine and don't need to take ewram to upgrade move result

    note remember tweak tentacool potentially
    to make a bulk mon that kills with status
    use poisoning and confusion/other passive damage
    (maybe)

    also need tweak nature power other callable moves
    they bypass type exceptions
    since it uses the original move type not the called move type
    ex. nature power turning into stun spore
    and stil affecting a grass type despite being a powder move

    decided want to turn off level scaling until I can properly set up
    so its not scaled until after you've already passed through an area once

    also of note, professors aide's dex check is still
    limited to kanto dex only
    need swap that for a national check

    sigh apparently I never fixed the leech seed toxic poison issue -_-
    works fine  when its normal poinson but if it increases
    to toxic poison it never increments/does damage

    ok nvm it works but sometimes doesn't?

    give beedrill fury cutter

    thoughts on scaling progression,
    best vrsion of open world has a world that changes as you progres
    to make it feel alive, nier style,  could do with level but thnk will do with badges instead
    add function for evolving encounter table based on badge count
    pt is for early areas to change think will make it 2-3 badges
    passed what you're expectd to have for the area,
    so last place that would be affected would be around 
    area available for 5th badge so I guess aroudn celadon fuchisia?

    random chance to evolve if able to evolve

    remember remove ditto from starter list instead give at first daycare
    removed castform ditto thievul from starter list
    added liepard line, gen 9 starters

    need fix issue w gen 9 mon failing to give before can do anything else now
    checked w give mon issue starts w cefireon
    -issue was use of gspeciesname where didn't have entires
    for those mon added, inprocess of removing uses of gspeciesname

    Think do for all maps post league champion,
    I guess exclude teh seviis?
    but for league champion think will increase odds of happening
    with this world itself will be a bit more challenging,
    since player has badge boosts even if they go back through
    with weaker mon, they have an easier time of it.

    ok so I apparently broke accuracy -_-
    hit mon with 7 sand attacks they never missed
    EVER

    issue was forgot put negative return in
    DoesBattlerAbilityAbsorbMoveType, so alawys was true

    was part of it, major issue was adding the ability check logic
    to skip acc check for absorb abilities to fit modern use
    made it skip teh abilityefect check that did the logic in the first place...
    so replaced w what oak battle uses and its fixed



    can implement for  new game plus as well.
    NOTE**(
    ShouldCapitalizeSpecies isstill used in several places
    can't remove gspeciesname use until all are replaced)

    Then after champion do all maps
    and increase odds of evolving
    get num evolutions random chance set
    of what evolution to set once decide to evolve
    tier 1 or tier 2 etc..

    adjusted formula seems ok?
    still unsure

    I FUCKING CAN'T I SOMEHOW BROKE BIND
    AGAIN!!!

    it makes them attack themselves with their moves
    instead of picking a random one *facepalm

    may have found bind issue  bind uses GetMoveTarget
    and I change that around when I was doing my logic for
    absorb abilities, so it may be gettign caught in that?
    - yeah issue was getmovetarget idk why I did it way I did,
    but was using gbattletarget before it was assigned so set to self
    works now doesn't break  move type absorb


    also something still off w damage calc

    anger point super effective move against morpeko 
    did like no dmg


    could be an issue w the transformation,
    also need change that so it doesn't grey out the mon

    zacian zamazenta ability being applied to enemy side on switch in
    need change text for embargo to not load battler name

    check count byte values for battle scripting struct also 
    have things should have removed already
    tried to update things for triple kick need test still works correctly

    gBattleScripting + 29  is battlescripting.battler

    -seems tobe working

    make sure go through abilities file search each
    to mkake sure abilities are actually setup
    ported lotof things but not all setup

    need update abilities changed to draw in move types
    attempted add accuracy bypass for absorb type abilities

    actually don't need change description still accurate

    note for wild/ai move learn 
    check moves for should delete
    based on if stab or if have damaging move

    issue ability gets removed when faint and try to view
    mon from summary

    so its issue with summary screen logic, if mon is
    fainted should default ot other thing

    also added species name to base stats now calling from there
    fix name use for dex and cane remove gspeciesname to save space

    replce cat icon split icons symbols, plan use gen 9 versions
    more minimalistic not ugly as sin

    NOTE*(
    Important thought, moves that remove ability worry seed etc.
    and mold breaker likes no longer affect mon that it would have that previously had levitate
    as its an inate characteristic now.

    need make exclusion to balance, what could do is make involve status
    i.e sleep paralysis make it unabe to fly

    and electric mon would still have the greater benefit
    as they are immune to most means of paralysis...yeah that could work
    
    good because makes status move important and not just limiting to 
    moves that hit in air, which are typically just one or two types  flying/rock

    think need returned to the air message for sleep ending and cure paralysis
    can do status cure and check if floating mon from base stats
    maybe make function, so check if asleep paralyzed or grounded set otherwise
    i.e STATUS3_SMACKED_DOWN  cured sleep/paralysis and not have sleep/paralysis or smacked down status
    )

   uxie ability inthrall still not sealing moves correctly, doing nothing rn.
   but also rebalanced its stats
   maybe need change to move end? idk

   note may be something saw in debug
   but rather than making battles randomly other types
   i.e I could make an option to set option for preferred battle type
   and make option for fixed battle types

   can also combine with random selection of battle type
   as base? then when option is on it gets fixed?

  //if add gen 9 legends wo-chien change its ability effect
  make tablet of ruin drop speed instead,
  ironically will make the ability work more for itself rather than
  as a support. its an equalizer so your mon technically aren't affected
  -done

  EE expansion breaks down mon into evo families and was able to tell form that
  there are far fewer mon in the game than I thought, 
  if you only catch on of each tree you have plenty of room. with my box expansion.
  By my count there are 537 pokemon families and this counts mon that don't evolve
  and legendries

  This means I can add gen 9! and still have room for catching everything nearly twice over
  not including forms of course like different regionals and megas but still more than enough

  //icon id for slashing/slicing moves boosted by sharpness
  just use 3 angled lines like a cut

  //removes that require specific status set to double damage
  //just makes them bad, is venoshack and barb barage for some reason only poison -_-
  //what they could be is double if statused and then extra boost if poisoned
  think 2x if status 2.3x if poison?
  -done

  Dunsparce other evo
  //learns hyperddrill at 32, delay till 40 add new evo at 32 to never have to see
    //that one
    
    //debuffed hp as plannin to actually add evo, just remodel sprite
    //waffling between leaving pure normal but making float, or normal poison and floating, giving it just a psychic weakness,
    //think I will do that actually, that removes its fighting weakness too. 
    //make evolved form float and normal poison make essentially star wars force awakened beast/ff14 jungle monster
    //but with wings
    //Oggdo Bogdo from star wars fallen order &
    //Fafnir of the North   from Final Fantasy 16
    //awaken old traits in its dna
    //regained ability to fly, larger armored form, retractable wings
    //inner poison sacs of paralytic poison extendable tongue  
    //remember still keep drill tails, think go chimera style give two tails
    //that end in drill tips
    //give toxungue ability

  can consolidate effects like I did for rocksmash/cut variable power based on status
  like I did that variable power based on type
  can make one effect like jungle heal but think for clarity would prefer
  to just make a single bs command for them and keep the scripts unique
  huh don't actually need to do that, effect is in pokemon.c apparently
  and I never actually setup venoshocks damage boost because I didn't realize that...
  -ok done perfect did added brine as well since I missed that
  

  when done check if I have room, if so would add priority
  to give more room for numbers for priority
  change graphic of move description field
  got plenty of space for top line, so can move the white part
  above text down a bit

  Though its regained the ability to fly
  it still spends most of its time underground.
  It retracts its wings and drills with its twin tails.

  Becadet  Normal/Bug - can't fly
  Buzzboy - unsure bug steel bug flying flying steel

  //note forgot to add freeze logic for status grounding, 

*/
goto Storage_SystemCallbacks  //has how pc moves to summ screen and tracks index
goto ADD_MOVE_CAT_ICONS //for move split etc.
goto GROUPED_SPECIES_ENUMS //for planned new species set setup, enum must match order of arrays bottom of grouped_species_tables.h
/*
    
    /*since gender form array only has 5 values
  can't use [SPECIES_NAME] = value,
  syntax as thata will just make the array massive
  and make number of vlaues the max value in it
  instead make a function that returns id value 
  based on given species.

  and use that as the species argument in the function
  that takees the form
  i.e make species check for what species to generate
  make switch case for each of each base species above
  that will assign a value to genderID

  u16 generate what speciesfrom json(species)
  {
    u8 FormTableId;
    switch (species)
    {
        case SPECIES_UNFEZANT:
        { 
            FromTableId = 0;
            return gGenderforms[FormTableId][GetGender(species)]
        }
        break;
        default:
        return species;
        break;
    } 
  }//something like this
  //decide make file handle both gender splits and grouped species
  //what I need here is a set of global enums
  //then I can tpe case UNFEZANT  and it'd be 0
  //like what i did for string compare..actually made global constant for that
  //here need enum that's global got that working
  now next thing is include the category species
  i.e  early_route_birds  for that rather than gender
  2nd field will be a randomizer for size of the array

  I think ee has some special random generators that are supposed
  to be more accurate to help prevent numbers not showing up more evenly
  belive yb taking into account previously generated numbers
  and re-weighting?
  but anyway look into those see about using them.
  may need to make category arrays global
  so can use specific generator for..OR
  do like formspecies and have terminator value
  since I have global enum arrays
  I can make an extra array for each category array
  to hold the size and then can just use 1 randomizer
  and still be able to set different max limiters
  -surprisngly got working without issue,
  still need setup better later and
  finish adding new logic added to pokemon.c
  CreateMonWithNature  to other places that use create mon
  but overall it works 



//believe num species is what mattters for ewram
//because of this
//#define DEX_FLAGS_NO (ROUND_BITS_TO_BYTES(NUM_SPECIES))
//believe that goes into the saveblock
//tested and confirmed

IMPORTANT - more encounter table optimizations
level scaling but not direct to level just shift max level generated based on average team level+
and can add a function to check if a mon should evolve, if so generate the evolved form
similar to how I have the rival, well rival is based on a constant so guess I"ll have to do that.
do evolve, and then use final evo function later.

first check level, and go up a single stage if couldn't evolve w level evolve at certain
player ave level say 25  then 40 or something.

think want everything to just go up one evo stage based on whats in the list?
if just make everything final evo that may be boring.

to do idea, need rework json, don't have max level...no instead check if player is above max level,
and replace max level with player average level.

just need to do some form of weighting based on player level 
relation to min level.

like if the min level is 40 below you don't realistically 
want those popping up.  so instead may be good idea to keep it to a 15-20
level range?   so I shift the max and then if diff between
player average and min level is greater than max range constant
shift to crate new min level that is equal to either
player ave - 15 or 20,  
or new max - 15 or 20

just need to adjust the ChooseWildMonLevel
function in wild_encounter.c its actually SUPER easy
since I've already made an average level function.


hmm this also further optimizes mon generation as list specifically keeps multiple versions of same encounter
just to have higher levels for it with this I've both removed the need for repeating same set of mon
in multiple different encounter tables,  AND the need for having repeating mon within the same evo table. o.0


will have to add some guard rails,
ex, people overlevel grinding, enemies sccale up
and suddenly they have an uber beefed up team
that's stronger than the gym.

so make gym list, scale levels up to like 1 level belw gym trianers
until after you've got the badge for that level of 
game progression? 

On surface that would break open world progression,
but areas you can get to early by exploring
are alays higher level than you so that's no problem.

also new idea add game option for levels scaling down
make toggle, what that will do is make wild encounters scale down 
to your level if you're below the max, main benefit is allowing
you to level up new mon/teams anywhere rather then having to  be 
stuck in early game areas

level scaling up will be default but scalign down will be a toggle.
option

this is also interesting as people could use the down scaling
to get to other areas, and catch mon for things they wouldn't normally have.

//like being able to get a hypno, or diglett/dugtrio, after brock, 
//before going through diglett cave/misty

very intersting
//add to misc options for option menu

Display Effectiveness - change text color to denote type effectiveness
//for dual target can't check all just change if color exists
//if super to some target make display super color
//single target can display on selection.
//for doubles make it display based on target

Level Scale down (find better name) - make levels scale down to
average team level or lowest mon, when toggled on

with level scaling setup don't need to include multiple instances
of same mon for level.

with species categories don't need to take multiple
slots for different species.

so I no longer am limited by slots at all,
which means I need to come up with a different system 
for encounter setup.

I think will attempt what unfolding mentioned 
and try for max 20 encounters per area
i.e land surf sand fishing

having more mon available is more exciting 
makes it more of a surprise when you find something new or rare.

but as mentoined there are those that want specific things
while I don't like it exactly using the dexnav will solve all
potential problems, with its search feature I can completely
remove the rng from encounters as needed.

BUT I don't want people to just walk in and use that immediately
I hate teh removal of teh mystery,
so instead I'll have it greyed out initially when you enter an area
but once you "complete" the area it'll fully activate
allowing you to see select and search for all encounters

(need figure how to make work for fishing)
will require changing condition logic for how dexnav works
and menu graphic by default it only has space for 10 species

make taller window have fields displayed as columns collapsed
clicking on them will open
them up filling with blankspace that icons will then be printed on.
will then need to setup to be able to scroll icons
vertically and horizontally to select species to generate.
right panel will hold general species info

///num abilities in a tiered box that is populated as you encounter
them.  don't require catching, no do require catching to fill out
actualy no just show abilities from the get go,
would take too much ewram to store ability data and captured

figure out how to include some form of catching incentive
since I want people to catch more since ivs are more impactful.
maybe catch a certain amount a fill a shiny meter to allow
generating a shiny?  sigh again that would require ewram...
and don't like the idea of mindlessly forcing people to catch///

Will need to add a set of flags to check for to show for completeion
of an area think can use map progression flags
ex.if I've been to viridian city then I've already cleared rt1
another option if I've been on a map, but am not currently on said map
can say I cleared it no need proper progression markers
otherwise people can just cheese it by walking in
then walking back out.

tldr dexnav search is a required feature for 
encounter size expansion will introduce it early on
but not immediately. have one of prof's
aides give it, or better tell them professor oak
has something for them and would like to see them,
can do that around vermillion by then should be able to 
get back to oaks lab through digglet tunnel.

making them go back to palette town should make them
aware of the mon scaling feature.

and once they get the dexnav they should be incentivized
to go through the old areas to see what they might have missed.

and this would be a good place to make them aware of the trainer rematch 
changes along with the trainer scaling.

ok perfect soon as player beats lt surge 
have prof aide approach them
make ground trigger

don't remember well but there may already be an aide in 
vermillion for after beating surge?
if so use him, just take on some stuff to his script

other wise set some triggers for alt scripts
one right in front of the pokemon center door
that would make an aide load inside
would want trigger after you heal at pokemon center,
so put activatoin var inside nurse joy script for vermillion

otherwise make a column along the entrance of the town
between the gym and town entrance have oak aide call out 
and approach player   - JULY 2024 - new quick way to find relevant notes just date them
vsonic


Note species name expansion caused issue with healthbox size
but editnig box is insanely difficult so counter idea
what if instead of changing the entire box I just shrink the health bar?
make it a little smaller and should be able to move lvl to bottom right corner w status
potentially...  actually no shirnk health bar and move to the side, then just bring lvl directly down, looks better that way

also for double battles when can press start to change player health box to display numbers instead
make that do same for enemy side, and see if can get that working for singles as well
ok reason why its not on singles is , it already shows numbers for player health
//but I can still make it show  enemy health as numbers, wouldn't need to break out a ruler
to get exact calculations demystifies things a bit but still takes skill
player needs to keep track of how much damage each move did and keep in mind random rolls etc.

Note numbers are same size as health bar, so will need to move those down as well
when I shrink the bar

SwapHpBarsWithHpText(); function for swapping hp bar with text numbers
doesn't fully work for opponenet side
July 2024

   
    
    for dex evo list page
    potentially identified issue w eevee page
    vaporeon doesn't shhow correctly icon wise
    but I think its getting replaced?

    from checking the evo methods
    I see that sylveon isn't getting on the list,
    and that a blank value is there,
    something unbound?
    also for some reason unfezant F is on the list intead of sylveon
    -finally fixed
    issue was I forgot to incrase field for evo screen target species



    exp candies kinda worthless unless you're trying to edge leveling
    when rare candies exist, so think will change exp candies based on that premise
    to make them easier to use.

    make them do the greater of percentage needed to level and fixed amount.
    exp .s  10% > 50 exp
    exp .m  30% > 200 exp
    exp .L  50% > 1000 exp
    exp .XL  70% > 7000 exp

    percentage done using to next level field
    (percent value x next level) / 100

    then can put the gain amount in item description
    so players now what and how much to use to get what they want
    
    move icons
    split
    unique category - punch kick headbutt etc.
    unique property - hit in air, double dmg in air, hit underwater, hit underground

    property is the only one that can overlap
    the others are exclusive
    //make new icons and use in summ screen
    make battle summ screen callback

    and summ pokedex screen callback

    punch move icon is box glove
    kick move icon is foot
    headbutt icon is helmet

    think hit in air just have generic bird icon
    one used for body type

    potentially replace phys icon w mon flexing 
    and special icon with abra w wavey psy patterns around it

    nah icon too small for that amount of detail


    need update icon graphics as well, EE has newer things for gen 8+ stuff and forms

    go over graphics in general, use sharedx saves take best between
    Emerald and Firered - don't forget EE icons too big in some cases

    fixed early bird , cupid's arrow seem work now

        //...dangit I want Beedet Beecadet SO BAD!!
    //baby form chubby Bee from It takes two,
    //in an aviator jacket adn oversized helmet
    //evolve slim sleecker with a plane
    //front sprite standing in front of the plane
    //back pic in the cockpit
    //Beecadet will be name of first form, 
    //evolve from can be FlyBee spin of Flyboy
    //actually on Change that to BuzzBoy  much better!

    pickpocket magician buffs, good for in game but not competitive
    since fails if hnolding item and always holding item.
    -my fix add field for secondary item slot, could use for thief
    but think will just use for the abilities.

    need add a script for this like I did for caught mon held items
    loop party check if item was taken i.e loop secondaryitem slot if not 0
    play script, item(s) added to bag

    idea if holding item, stolen item is instead put in secondary slot
    and will replace current held item if lost or consumed.

    still need setup new description for magician
    and battle strings for effect,
    of adding stolen items to bag if not stolen/consumed by battle end
    think will just do a simple item(s) added to bag.

    last part of effect to setup is the actual item passing itself,
    make function for assigning second slot to itemslot and clearing secondaryslot
    think need take battlerid argument, would trigger when consume or item stolen

    going over effect in item battle effects function
    thing need make bs commad to go in scripts patterned after removeitem
    that will take same script argument as remove item,
    but swap item from secondry slot to first and clear secondary

    then also a function for item stealing
    thinkm need use push cursor so it triggers item replaced
    actually should only display message for player side
    as otherwise battlers item doesn't get reveiled 

    note**(
    can make list of tms want everyone to have macro,
    and rather than add to individual tm learnset
    can put in function check if tm is this, anyone can learn it
    -make rest one of them
    ) - also note add updated sitrus berry effect
    -blood moon ursaluna for move bloodmoon simply setup like protect
    //but guaranteed ...actually don't need to do that, if lastusedmove
    by mon is same just make it fail, nah use lastlandedmvoe or lastsuccessfulmove something

   someting wrong with playanimation command  attempt use
   for infatuatnio animation, put up substitute animtion instead.
   but chosenstatusanimation command worked perfectly

    -rework samurott base sprite
    have image in Xshare folder

    what the absolute fuck I thought I fixed move learn??
    but skitty learned moves imd battle and
    despite only having two the game treated it as if it had max moves
    ok seems it was an issue caused by the debug stuff
    the quick move learn from boxmon?
    

    added the fix for it, and it seems to work corectly

    fixed aftermath fixed cupids arrow, 
    next thing setup pokedex info page view from
    summary screen, then graphic info page setup

    testing sturdy buffs those not working
    sturdy destiny bond takes no hp off me
    and plays the opponenets ability name instead of mine

    ok destiny bond isn'tbroken in debugger
    I just didn't understand how it works,
    it doesn't work off end turn but next action
    if they're killed before they make another action it faints the target
    works fine for in battle, but doesn't work for debugger
    where the effect isn't set in teh same turn
    so as soon as the battler attacks the effect is removed
    -fixed



    -note can save on ewram a bit by optimizing structs listed in battle_main
    did that can't make fieldtimers a bit field, but also need
    add rest of side timers to debugger

    also need change battle debugger ability set
    forgot I changed ability logic for party menu
    so the base setup causes bugs
    just copy the party menu setup, for in battle.

    -there's nothing wrong w battle debug ability setup
    its just the way that the debugger creates mon clashes with my setup
    usually every personality is different,
    but the debugger fills boxes with mon with all the same personality
    which causes issue, but for some reason species isn't read?

    other note copy pokemon debug logic for summary screen
    want to setup for a callback to pokedex info page
    so you can quickly check dex of party members
    think setup with callbacks, so can be different from base pokedex logic
    what want to do is callback to same page you were on before

    you open party menu on info page-first page of party menu
    press start and it opens the info page of dex
    press B on that page to return to summary screen page

    think will need to do like categorical dex logic
    where its a separate function with its own tasks and navigation
    so will be party dex page something like that
    have all logic for forms but never shows numerical list,
    doesn't scroll up and down,
    can still scroll through evo and area page


    //consildating own tempo obvliious unaware effects into category of abilities
    //simple/similar base but each with own different extra effect
    //no intimidate no taunt or torment

    for cacophony can do jumps/calls in script to account for effect
    effect makes all sound moves bypass walls and protection
    also enhances effect

    add perish song to debugger multiple other status

    status moves:
    stat chanaging, increase stat stage of drop by 1 if is 1 stage or 2 stage boost (considering just do for single stage)
    -decided boost stage if 1 stage boost otherwise just boost accuracy to 100
    //will need make function for should cacophony boost acc
    if status move and listed effects and cacophony boosted
    -in progress

    non-stat based enemy target, do damage with effect using copy of ability damage script
    
    status setting - ex. confusion or sleep, set max turns for this use cacophony boosted special status like where I have prankster setup
    -done

    damaging moves:
    if has effect double effect chance

    for effect set function would need do on move by move basic
    but think can use switch case, w move argument  and effect chance argument
    effect chance = cacophonyeffectboost(move, secondarychance or  argumentchance)

    something liek this

    -relevant effects
    attack down, roar, sleep, confuse, defense down 2, snore - may need skeep effect boost if that sets flinch - yeah causes flinch
    skip snore, perish song,  set counter 1 value lower if  cacophonyboosted
    hell bell, guess make it affect sound proof if boosted?
    not boosting spook cuz flinch chance
    sp def down 2, bug buzz sp atk down hit

    -finally fixed ability absorb setup,
    also cupid's arrow not quite right,
    if not battle start when switch in attempts to use move
    also infatuation fades sometimes when switch out?

    also not all ability effects ported were setup,
    just found harvest wasn't setup

    and embargo wasn't setup so bandit king also doesn't work
    ...of course they're not all setup I never setup emergency exit and wimpout either I think
    need to go over ability list, search ported ones and see if they have code to go with teh constant
    if not then I never setup

    don't think terrain is setup right either,
    and until that's fixed can't test evergreen,
    and need add terrain and weather stuff to debugger...

    as well as fix status issues with debugger
    put staus timers in first block w status 1,
    and setup wrap status and fix recharge status rage and torment and bide
    vsonic IMPORTANT

    decide leave status activation condition to just absorb abilities
    would be too much to deal with if had to avoid status with every ability
    //but would be a good potential counter for imtimidate
    but the question is would it be too much?
    if running the ability requires too much investment its not viable
    hope is to have good options far as counters, grass mon would be great as counters

    ok need put more thought into which abilities should specifically have these
    status based activation conditions applied to them.

    some abilities are passive, some are physical, some are mental,
    some are biological etc. some are more actively focused

    its easy to do filter for absorb abilities because they are reductive to overall gameplay
    by design it removes options, an entire type from use.
    Very strong with no counter.
    Intimidate is the same, reductive strong no real counter (till they started adding a bunch)
    or drawbacks, i.e very easy to activate/access

    Cacophony while strong, only has effect in doubles, and requires using a specific move type
    a good deal of setup is required so that wouldn't need to be filtered
    
    i.e abilities that require movement and to be in an unimpaired state
    such as absorb abilities where idea is, they are moving to jump in front of a move.

    and status abilities (intimidate) things that imply the user to be in a certain condition
    to work such as intimdate working becuase they are able to put on airs and scare the enemy
    can't do that if they are weakned

    since intimidate is switch in only rather than use canability absorb
    would just be status1

    lets do an extrapolation, abilities are good abilities are cool,
    they allow for unique strategies and variety in character use
    if you turn abilities off the game gets boring.

    But a part of how good something is, is measured in the quality of the counter play
    or how many options it creates around it.

    if you make status the factor for ability activation status setting gets more use,
    but on the other hand, toxic spikes suddenly gets very popular as well,
    as a simple means to block abilities on switch in.

    so def a good thing didn't decide to make every ability work that way

    other game change made staus moves use type calc,
    to make typing more relevant/effective than just, for doing big damage

    -for cacophony
    infiltrator and protect break portions of effect appear to work
    still to setup is specific move based effect boost

    idea of cacophony is sound based helping hand,
    makes it more efficient wall break and protect break is an extension of whhat sound already does
    hits all for neutral because nothing can ignore it, and bypasses substitute as well


    may potentially add item icon to summary screen box
    to show secondary slot item

    believe setup done for consumables just need to do for getting item stolen/knocked off
    believe that's done, and ready to test
    also go over battle struct things to clean those and others up as needed

    for some reason seems bs script setup for that stops items from working
    had wrong args  used cmd args instead of native args

    after get working check base stats, setup new unique abilities
    for celebit and base shaymin

    also major decision VSONIC IMPORTANT
    finally decided to NOT do all of expansion
    i'll make a qol hack /firered remake with just what I want
    no dynamax z-moves etc.  will prob keep tera just because it is interesting
    even with the stupid hats (don't port the hats -_-)
    and I'll have meags, along with a method of making them permanent evos

    got nuzlocke mode working,
    redid status batle effect updgrades
    fix oak speed strings

    belive have it all working 
    next thing is consolidate the pokemon substructs into boxmon
    using bit fields

    options menu stuff is setup (still need test)
    but need to figure out how to make sure teh cursor
    returns to the position I want on main menu
    i.e if exiting game options put main menu cursor on game menu options

    testing new options setup and low level dmg formula before moving
    to adjusting structs

    seems mostly ok, there is still an odd glitch where dead mon
    removed from pc back to party
    can have its hp refilled

    (attempt typeless moves to hit through wonder/dispirit gaurd
    they don't by default apparently, believe with new type setup
    the modifier will just be 1, and thanks to my multiplier change
    practically nothing hits for just 1
    
    so do mod 1, and not type normal or something or do it by effect 
    //probably do effect make a function holds all typeless dmg effects
    isMoveTypeless(move)  that'll do
    ) - don't need do that already had it set up, made typless moves power 0
    and had dispirit/wonderguard specificly set to block moves w power greater than 0

    battle speed up text still hard to read, may make pause logic and waitmessage
    speed up use different function

    //disable struct is removed on switch, so if you need to switch timer is reset
    //perhaps can do with side timer instead, timer not lost if mon switches
    //will only decrement if at end turn its on the field.
    //do for slow start and new wonder guard setup, wonder guard 4/5 turns
    //but then there's trickkery with switching put it on field at start of turn
    //then switch it out, the timer wouldn't decrement if its at end turn?
    //need look at turn order logic

    //also hard part get specific timer recognize specifically that mon, not just
    any mon with said ability, how does defeatis do it? -it uses disable struct so is cleared on switch

    for now just check slow start and test to make sure battlestruct slowstartdone
    is specific to the battler and not just the banttle slow,
    get 2 regigigas switch the other in when ones timer is done

    fuck, yup it just registers that a battler in that position has ended slow start,
    //its not  checking specifically that one.
    could add a personality check but would need to be a 6 field array
    to store for every battler..
    think can use this gBattlerPartyIndexes[gActiveBattler]

    ok looks like won't need ot make something new
    can use gBattleStruct->usedSingleUseAbility[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)]
    technically it doesn't just hold a true false
    if I change it to a u32 I can make it store personality
    //will prob need change field
    nah, think can keep name
    actually don't need to change all I need is a check for thing activating and tracking the specific battler
    this does that
    worked perfecetly!!

    uhh look into furry cutter endure interaction,
    unsure but think first hit failed to endure? - belive fixed issue was all multihit missed a first hit check

    now using for slowstart and wonderguard  
    new idea consider shedinja a wraith, add to dex entry
    give buff/debuff moves  like a spellcaster

    think will give immunity to status and weather dmg 
    -changed to immunity to status dmg

   - to make text more legible when speed up,
   rather than slow buffers add \p  ending to important text

   actually think may mkae on \s character that will do it
   based on battle speed up, and text sped being above mid
   so it doesn't interupt speed options where the current text works fine
   so someting like if battlespeed is 3x and text speed is greatrer than mid
   do the wait button press stuff i.e the \p stuff

   things like ability messages, battle effect/timer end messages
   is super simple and would allow people to go at their own pace even w
   max speed on, will just have to come over battle message file

   -setup done, works, just need decide where to put,
   weather abilities strings don't neem to need,
   as they use waitstate rather than a waitmessage
   think I just need after important things
   that use wait message short?
   yeah sunnt day etc. use wait long so that's fine
   its just wait short I believe, or for longer messages
   like say pickup and magma armor.

   on word from tardysoap went back removed new char use
   instead adjusted w wait times function seems works,
   adjusted short messages and long messages deemed important

   added eduardo asparagus decap branch shared by ravepossum
   will use like hgss file copy values I need for efficiency then remove

  nother important hting need fix agbc setup
  its not right at all, and will be a problem when sharing project

  also find special thing i setup to transfer and cap values
  that came from const struct will prob need for item cap

  find that before start messing with it
*/
goto CONST_CAP_WORKAROUND //found it

goto REFERENCE_ENDTURN_ABILITIES

goto ABILITY_ABSORB_CONDITION_FUNCTION //need update this function
/*

  note reinstate gen2 logic of roaming mon can't flee while asleep -_-

  //isn't this an issue like toxic counter gets reset if switch out?--
   ...yup and same for sleep and freeze..

  looked it up sleep timer toxic timer and since I adjusted to a timer
  now freeze timer also gets reset on switch out
  its unrealistic so changing that, you don't just get less poisoned
  or more frozen just because you're not in battle.

  huh, since freeze counts down not up that works differently
  and is actually good for balance, it makes you less frozen not more.
  which makes sense you could thaw out off screen.
  if it works how I think, you'd get frozen the timer would be set for 2 turns
  but if you switched out, it'd reset down to zero effectively thawing you out
  when you came back in. damn I like this actually, need test to make sure

  but if so then freeze can stay exactly as it is.
  -tested yup works like that exactly so perfect

  BUT you can go into deeper sleep so I will keep sleep as is,
  (plus it works better with my mechanic change)

  now not setting sleep like that doesn't mean I can't cut down the space
  by changing the setup to track, the mon I'll just reset it on switch in
  i.e if statused sleep and firsturn = 2 simple to do
  -done freed space for 2 new status1 conditions

  -test tiger mom works swarm not freezing, but still not quite right
  need setup separate end turn effect for infestation itself

  end turn swarm just has  chance to set swarm status
  if it then goes to end turn infestation rule

  vsonic, see if stench script works correctly in doubles
  believe want switchout to hit all, by faint to effect just batler that fainted

  setup ravepossum debug mode make testing much simpler/faster
  would prob make play testing easier as well

  PRIMARY_STATUS_MOVE_EFFECT

  //check inthrall seems not setup right, no message
  when set and no message when clear

  yawn seems to be working sleep seems to be working,still need to test
  toxic setup - tested toxic works and isn't broken since dmg stcks slowly

  will need the time setup I used for slow start and wondergurad

  now testing new status setup for yawn toxic and sleep
  only toxic used the new tracking battle timer setup

    idea ice version of contact status ability,
    would need to be on mon doesn't do big dmg,

    came up with ice steel type, like sticking your tongue on a frozen pole
    making contact has a chance to freeze

    //change annihalape evo to perform rage fist at max rage
    //rather than needing a new field I can set a flag like I do w

    new move idea "bodyguard" or "body guard" similar to move that makes user center of attention
    the moves of a selected target will instead target their battle partner
    give to clefairy and other support mon


    moved substructs to boxmon, made up a lot of space
    -note look into battle.h and cleaning up those structs as well
    
   still want to try get options menu to track cursor positino for main menu

    no other hard rules needed
    change options menu back to text options
    add misc options for battle speed up event speed up and nuzlocke mode
    //order event speed up, top, battle speed up, then nuzlocke mode last

 test bandit king and corruption

  re-evaluate battle scripts make sure
  typecalc is in right place for things,
  realizd gbattlemovedamage is set in damagecalc
  so type calc before damagecalc just sets result flags (checks whether should hit)
  doesn't actually add stab

 check item screen for impidimp it seems tobe closest value 
 make that for all of them, as it actually displays item
 =readjusted for item use most should fit,
 still doesn't lookright for tms though

 add rest of move effects to BS_getmoveeffect
 so multi task can be done

 still need work on brick break animation/effect  I think 

 revise hidden power and weather ball, so just use effect hit
 remove cases of their effects use and replace with move/gcurrent move
 -done

 Look into calculatebasedamage dmg formula, see if its not scaling too low,
 all I worry about is if I accidentally made level MORE impactful rather than less,
 plan was stats matter more, less boost from level gain so mon even at lower levels can still do solid dmg
 to enemy based on stats

 i.e 3-5 levels below you can still do things
 but still overall  raising the TTK so its not a one shot fest

 changed level scaling without changing defense side of dmg formula
 which made all moves do half damage they were supposed to...
 -fixed

 potentially port emerald expansions additional effect setup, would clean up scripts
  

  ,...ok bind is broken, I missed something,
   if you switch in on a bind it makes you struggle EVERY time. smh
   ...not sure how but its fixed now, think something to do with the usable moves change I made

   plus knocked off animation not right, its doing knock off item anim
   even if mon dies as a result of knock off

   ...actually yeah I'm gonna keep it like that,
   makes move more costly

   -I think I might add back the grass immunity to leech seed, 
   well no, that's only an issue because I gave leech seed to bug mon
  
  fixed issue w lag on oak ranch setup, testing new versions make sure no issues

  came up with new idea, similar to sonar w sonci screech
  could make strong jaw boost super fang.
  nothing too crazy but thing add an extra +10% target hp to dmg
  would allow super fang to actually kill

  idk why or how this happened but move confusion's animation is broken
  //meditate also uses same bg but it clears correctly,
  confusion just fails to clear the bg

  found issue, it was delay reduction combined with the battle main battle speedup

   speed up is moving 2 frames so I lost the buffer clear that was used in animations
   of delay 1.

   in delay command in battle_anim just added some extra logic for value 1
   to ensure buffer scales and can stil do its job

  and strong jaw is relatively rare so not a major powercreep/balance breaker

  major updgrade w potential issue emerald removed use of
  gActiveBattler, because way it was used caused potential issue,
  believe I dont have any but will still remove
  same way I'm upgrading bs commands to cmd args for more exact results

  also of note removal of gBitTable change was made because gBitTable was slow

  somehow sound is messed up, pokecenter heal, level up and few other sound effects are just off

  playfanfare MUS_HEAL - checking
  -belive found issue, it was voice group stuff, I ported emerald voice group setup
  and most things were fine I guess, but may have taken things from emerald?
  I can't rememenbr but check the voice group files

  $(MID) $< $@ -E -R$(STD_REVERB) -G008 -V090 -P5
  ok fixed it, G is the voicegroup  V is the volume, P is pan I think or something
  but issue was indeed teh voice group i copied files from EE

  -for anymore broken sounds I know what to look for
  ok voicegroups 6-9 are off, the new voice groups are unused
  
  - so find a fix ok found fix,
  issue  was songs.mk I changed the voice group files
  but didn't adjust the songs.mk which assigned voice groups to songs
  thankfully most are the same, could have been MUCH worse
  I don't need to replace voice groups I just need to adjust the
  few that were comprmised to match the values in emerald,
  since even the ones that are off now, have identical versions of the original fr voicegroups
  just under a different name

  thinking it was cry related but it wasn't?  oh right I copied them for move stuff
  anyway issue was while most are the same, some are very different.
  which is why healing etc. wasn't right, voicegroup 008 was completely diff
  which broke healing evo sound levelup and caught etc.

  I like the new organization of the voice groups but I don't need a majority of them
  I don't need to add any new sounds to teh songs.mk as of yet
  but all the voice groups are different what I need to do is go over the songs.mk
  and adjust everything that is off when compared to the pokefirered songs.mk

  if for some reason there is no equivalnet/overlap re-port the voicegroup from FR
  and give it a new name then assign that in current songs.mk

  -IMPORTANT
  expanded save block saves are slower planning to expand boxes
  need remove ewram good chunk need about 31 boxes then make box search 
  to display only mon want to see

  only way to get enough save space was removing back up save
  put this info on game start screen in bold
  so people know with recommendation to make a save state before every save attempt
  and to keep a copy of your save in a save folder
  saves are slower so may wan to use speed up while saving

  -added warning to new game intro
   
   or not, smh only fix I found was replacing the voicegroup with the original fire red value
   so think will replcae voicegroups with original fire red version
   can keep organization, but what I need to do is update the programmable wave data files
   based on new names, but layout is same and files are same so easy to adjust
   just need check the line value

   -still has issues w stat bar, and I think it is just the stat bar
   its not exclusive to just jumping to a different mon page,
   it happens when just scrolling between pages and reloading the evo page too.
    but also of note because stat growth is limited to width want to add new color
    to show how much stat is chaning, if stat filed is above 130 or 140 I want to change its color
    to a blue/purple. otherwise teh highest stats won't be noticeable by stat bar as being
    significantly different.
    cranidos to rampardos is best example.
    base attack increases 40 points but it only goes up an inch and stays same color
    meanwhile its hp goes up 30, and the bar moves double the distance going from orange to green

    huh I don't need to add a new color, it already has a color above green
    I just need to change when it triggers so I can see it
    adjusted w value down from 38 min, to 36 min,
    now loads blue color at approx stat value 145

    and issue w stat bar is strange and seems to be sectioned by the dex cat
    loading stat bars from categorical/habitat dex has no issues
    its just when loaded from the numerical dex that its an issue?
    
    -note make sure to change summary screen to also update battler type

    //fire spin seems todo more dmg than ember?  nah its fine

    -check sinistea sprite,/icon something seems wrong there
    -it showed as hoothoot in box?

    empath not syncing with defiant
    passes stat drop but it doesn't count for raising stat when it should
    -should be treated like mirror armor 

    mirrror armor, magic bounce, empath and magic coat need check with defiant should work

    -species name cap not fully set item use from party menu doesn't pull the correct name

    VSONIC IMPORTANT
    -realized need better fix for rival evo setup
    for eevees there's more i should do.
    the issue isn't just eevee its mon with branching evos on the same levle with different species
    tyrogue is another example
    so rather than just eevee I should check all the evos on the level
    find which are super or resist my type and then put those in a group 
    can use pre assign and free to make work, similar to icons in dexscreen
    make field of 10 array populate species to,
    loop values checking for non 0 values
    ie loop assigned species if 0 break
    and then use that for numEvos
    and do random % numEvos over array to pick species

    -to tell if has branching store targetspecies of curr species
    for evo 0
    loop till end of evos, if find target species that is not
    the stored species break and assign branching evos to true

    if that's true do rest of logic

    -note finished relative evo setup, last fix
    was adding value to track what level it evolves at, to make that the new floor

    ook nvm it DOES get to categorical dex, but something about the way taht dex loads evo page
    from info page, is able to clear the corruption??

    no idea what I did, categorical dex evo setup isn't quite right but it does fix
    one problem at leaset.

    its something about loading from the catdex to info page into evo that fixes it

    new note it appears to actuallybe the looading of the category page task that does it.
    it frees up memory,? like opening category from start
    as sometimes I have to open multiple pages to fix memory leak,
    if one page doesn't do it, I need to scroll go to another
    if that doesn't work then closing cat dex stuff and opening it again fixes it
    so its some part of the initial/early task that does what I need

    -sigh ok seems it can't fix ti ALL the time. but that may be because I undid the
    lock on jumping between evos for the numerical dex it worked for clearing before I did that

    revisit oak ranch triggers, it lags on opening pc,
    think move pc trigger to when opening pc since it has sound affect that plays
    if I make the call into a script command, I can run it right after the sound effect is triggerd
    to hopefully camoflauge it

    appears to lag more the more pokemon there are
    there's nothing I can do other than loop over every mon in box.
    best I can do is do lvl based skips based on the gym badge lvl cap
    assuming I even set that up

    didn't correctly setup
    need fix  levels are loosly setup
    but want tweak UpdatePokemonStorageSystemMonExp
    attempt do stuff w do while, intead fo double for loop
    to hopefully make less resource intensive

    question pret etc. if do while can be less resource hog
    than a double for loop

    also plan for gym scaling rebattle gym leaders whenver you want
    battle variation will be based on gym badge count and average party level
    if gym badges are less than the recommended it'll scale down
    if more it'll scale up.
    within that
    if your average party level is below the recommended it'll scale down
    if above hmmm idk may keep as is
    could leave lvl scaling to be contingent on badge scaling
    don't forget thing found with battle_main trainer party data as well.
    I can scale party size too,
    so on rematch for gym leaders etc. if badge count is higher than rec for area
    and long as trainer has less than 6 mon in party I can "scale"
    them by decreasing partysize field.

    to make that work would need program in max size and just shrink
    based on progression

    would mean would have party size based on map area
    or would need to setup a table that reads trainer id so I know which fight it is
    and pull default party size from that

    that way they appear to get stronger, when in actually I made them weaker from the 
    get go

  note think have hatterne replace castform in starter select
  -just figure some event to give it, probably in celadon?


  -also just noticed seemed missing the script for losing the rival battle in oaks lab
  where oak says he's dissapointed don't know how lost it but get it back
  -prob a  var change that I skipped?

  think something wrong with get data/set data or checksum  for hisuian growlith etc.
  idk why but that mon has been breaking things causing errors with decap setup

  think caps stuff isn't quite right, species issue w the pc
  shows uncapped base w the actual capped

  for some reason lost logic for setting base form of mon as seen
  if seen alt form, thought I had that set

  -not sure but seems arena trap doesn't have a battle message?

  -note with expanded mart need to remember to set toggle
  to be able to press up to go to bottom of list

  ok so it is setup the issue is givemon skips the logic for it
  since I only set it up to work in registermontodex which is just via catch

  -fixed

  -need slightly raise wormadams party menu icon, it clips when it bounces

  pumpkaboo back sprite elevation too high, in battle bounce
  creates gap between background

  found issue w pc, for some reason on catch when last box opened was full
  it reads current box as the one that's full and then proceeds to put mon
  in said box, the box isn't full though

  //issue w bandit king text, it uses wait until press
  but more than that, it uses wrong team side

  -fury cutter isn't doing alternate side slashing need fix that
  -tested fury cut w honedge since he never misses, and am 90%
  there's something wrong with dmg calc
  
  -seems its fixed, hisuian growlith gave me no issue

  look into damagecalc logic think may have possibility its defaulting things to 0
  because of new formulae, when it shouldn't

  have an attack do only 1 dmg, even w minus 3 defense drop, just because it was resisted
  -oh wait I did a minus 3 attack drop so it was neutral...

  -chekc make sure lansat berry is working properly

  added pokabbie's in game speed up, still need to make its own options menu setup for
  //that along with the delay and battle message pause reductions

  also for planned extra castform form, think need make battlers use dynamic vram form load
  apparently it uses 4, for everyone, just for castform.  
  for the sprites so it can load all the forms?

  change that to castform onlyu potentially add check, 
  for formspecies getbaseform, so even if change species will work?

  -note for move relearners in game, replace all their text
  with "huh who are you?  I...I can't remember why I'm here!"
  
  since I'll be making move relearn a commmon feature that can be done from pc

  //still looking into tmhm leanrset and addign fly to more mon
  keep in mind for key item to swap mon from pc,
  could use that to pull flying mon when you need
  plan was to have a timer restriction on it so players
  dont just use it to get rid of dead mon, to remove risk/pressure
  what I can do is, remove said restriction if using the item
  on a town/city map.

  only have that limit on route maps i.e maps you can't directly fly to.
  something like set step limit after using item,
  if on map can fly to, limit set to 0,
  otherwise set limit to something like 500 or something.

  //noticed seems rage activates even if you don't land the attack?
  //can't remember if that was intentional, checked yes it was,
  I was basing that on the gen 3 effect, where rage works even if it missed,
  I do have methods of clensing rage, so its fine i guess

  Current work is on dex, fixing memory leak issues I've discovered
  figure why in Task_SwitchScreensFromEvolutionScreen data[3] STILL doesn't work
  as it did in EE, but + 1 seems to clear things 

  unidentified memory glitch with stat bars/
  seems caused by moving back and forth between stats/area page
  and scrolling dex entries?

  -note now I've setup silloutes for mon not seen
  no reason to block off form on conditions
  just make sure they're blacked out

  ok opened nat dex on entry pikachu, opened evo page close to info
  scroll to end of dex seen mon view evo page of snover/last mon
  go back to info, scroll down back to pikachu open evo page and stat bars are glitched

  //appears to only happen on pikachu? only on mon with more than 1 evo
  so data [5 + 1] and higher?

  ok believe foudn issue I moved icoin pritn to data[5]
  but I forgot to update Task_SwitchScreensFromEvolutionScreen
  which is meant to clear them, it was still running over data[4]

  -tested that did fix. 
  but icon clear over pre evos seems to not work? completely
   -seems fixed, needed a better loop value that accounted for
   both pre evos and target species evos

   -isse w switching in weather switchin ability mon
   but seemingly just the ones that activate with sript drizzle/drought?
   ex. have other weather set w ability and then switch to mon with drizzle/squall etc.
   for some reason triggers primal reversion
   - found issue it was my primal reverision command had to update to current EE version
   it caused all mon without further evos to trigger primal reversion logic 
  

  and navigating to other evo with A is also not working but that's a different issue smh

  "fixed" pre evo setup for dex setup
  before it only stored a single pre evolution
  and it only stored them in values 0 and 1
  now you can store 3 pre evos, and 3 pre pre evos
  pre pre evos are paired so its only 1 for each pre evolution

  -seems this fix wasn't quite right,for some reason
  it is now setting pre pre evo to charizard, even when none should exist
  -fixed issue was lacking protection for resetting the same field,
  //which would increment num evos passed what it actually was

  this doesn't currently exist but would allow for branching evo
  would need to up the  buffer for targetspecies in teh evo data struct
  since now its possible to have 6 pre evos, along with the actual target species they evolve to
  again right now not a problem, but would be necessary later, and useful for when I get
  the scrolling methods list to work

  note-changed ev limit again realized stats gained from evs were about equal to a flat bst gain,
  so greatly lowered per stat ev increase, base game was 254 which allowed for 63 points in a  stat
  and about 121 bst increase overall, which was not enough to make bad mon viable.
  
  previous per stat was 564 allowing for 141 per stat, which was...insane thank god I never had evs working
  new set is 360 allowing much more reasonable + 90 per stat
  and with my 788 total ev cap this allows for maxing 2 stats + slightly more which ironically
  is similar to the default.
  
  further distinction the old cap of 510 when spread evenly gave +21 per stat
  with my increase to 788 you can a modest boost to that allowing for +32 per stat

  think what I can do to further balance ev boosting can put a limit
  on how far stats can grow for evs, think of it like a species/world/biological limit
  can make it so bst plus stat gain from evs can't go above 600

  -note figure out CreateMonWithEVSpread, see how works and if need adjust
  -I "think" its not being used?

  but adjustjed all places found that used previous ev setup
  still need to fix mon gain evs so can gain evs with training items etc.

  tweak to how use ev items, with incraesed limit to prevent things getting crazy
  has to be somewhat inconvenient which is why I removed evs from normal battle
  //tweak idea to add convienc ebut also a negative

  instead of getting ev boost items you get trainer kit, which like pokemon opal
  global exp setup whill let you asign training status to a mon, whiver mon in party you want.
  then assign which training item you want, it will then set that item to the mon's held item slot
  //with that you don't need to take up bag space

  it'll still slow the mon down in battle, and will consume an item slot to get the ev boost.
  //but its worth it and can be trainer faster

  think what I cna also do is assign different training levels to keep players from just
  tossing it on and forgetting about it.

  it'll set low medium high or short medium long i.e how long do you want to train
  and with that you wont be able to remove the item until training is complete

  since you can't remove it players would be less likely to set it to the longer limit.
  limit is based on ev gain, since you get so many per battle etc.
  (make sure remove it if you put mon in box, to prevent abuse it will not assign evs until finish training)

  when you've stored up the set amount of evs after battle
  when you return to overworld  a message will display
  X has finished training\n
  X gained Y {Stat} EVs!

  -think statbuffer can just be check for which training item is equiped

  will need ensure not in a scene, I guess just add check for 
  textprinter not active, and not moving via movement script

  umm make sure to refine ground boost, of being immune to ground based acc drops
 //form dex display not working right,
 is supposed to set the base form as seen, if its not, so you're able to navigate to the form

  make level evolved mon data value
  believe all defualt to 0 so no need to set at start
  but for evolution if mon data level evolved is 0,
  just return/use  level met
  otherwise return that, 
  only set lvl evo'd in evo function
  then use level evo'd in is mon past evolution level function

  archen archeops defeateist has issues,
  seems to retrigger, when hit at below hp threshold
  also script is triggered on mon that attacked, prob issue with battlescript

  or issue could be with specalstatus, know that was used for intimidate
  Unless I"m misremembering could be special status are cleared each turn?
  if so best cast is toss it over to disable structs or something

  again also seems I need to fix my weather setup normal weather abilities
  don't seem to be seting right? or just snow warning/sandstorm stuff
  -fixed weather,   guess I forgot to change the end conditions
  in end turn after I reworked it?

  for move relearn from pc, replace marking text from box
  instead replace it with "Learn"
  selecting will bring up box at bottom that is either
  "Move"  or "TM/HM"
  selecting tmhm will set callback to tm case
  where you can teach a mon a tm,
  otherwise you can open a new window which is for movelearn
  where you select a move from its learnset on a list up to their curr level
  or from prior evos, (can use dex pre evo options for that I guess)

  left window has, scrolling list, w icons for diff mon
  curr species on right most icons, pre evos to the left of it.

  moving left right on this menu, will swap which species learnset is shown in the list
  the main window will display the mons current moveset i.e the part menu move info page
  after you select a move to learn, all inputs will happen in this window

  -dex upgrades in progress, updating with hgss expansion stuff
  plus new idea haev de be more integrated feature for realism
  just like with show can use dex to get info on mon
  use in battle to do battle register, pulls up mon dex info page,
  allows player to see bst, and check evos etc. full dex page 
  will not be caught but will show all info and add to dex, as if caught
  will call feature battle register  and then return to battle when done
  
  Bring up by pressing L, from main battle menu (before select fight etc.) goes to select target
  when you press A on target loads that mons dex page

  current works-- cap/decap,  scrolling options menu
  //and make battle dex callback, and move info call back
  ,oh and finish mart upgrades will prob be best to load up porymap for that
  also need to re-enable debug mode for this and do the setup
  so I can use printf things to check function returns

  for plan evo page in dex, use blend effects (tm case update)
  to grey/black out the mon icons if I haven't seen the evo.

  got most of planed dex upgrade set, just have graphic issue and cleanup to do

  //can display the names no problem
  //for evo methods involving level, just display evo method name i.e Level Up
  sinee I made level evos none static

  otherwise display evo method and condition
  i.e evo method Use Item,  FIre Stone
  Level Up Hold Item   Grass Fluteor whatever
  stuff like that

  is wonderful feature that, saves time, and clears up any issues
  with changing evo methods etc.

  Multiple evo options for same target species display on same page

  for method that would evolve into different species i.e totally diff evo path
  ex. rockruff
  display up down arrows on evo page, and pressing down
  will reload with next set of sprites  and evo data

  so I need to loop evolutions for species and print data logn as it has same target species
  take logic used for printing bst onto window, to keep track
  use +=  existing dimensions value  
  ex. print on x, y if evo species has multiple methods for identical target species
  print following on same x position but y += 5

  then when I do next species can still use x , y but the y will be lower
  to accomodate the filled space 

  idea inspired by parallel emerald but actually
  seeems this is just a public resource, they slapped in.
  so I can hopefully look at the code for adapting it for myself

  ok found code its actually a feature branch made by xaman they slapped into their hack
  its also a part of EE, its the HGSS Dex config, has some bugs test EE version and let them know if bugs still exist

  for icons rather than scroll between evos, just make it clear and reload the next set of icons+
  -nvm just gonna make it scroll,
  anyway got stat bar part of dex ported over, next step
  is the sprites animations and evo display logic.

  perceived issue was that long evos (eevee) would run into the 
  dex bar, but simple fix is just to make it wrap.
  //put sprites a level above the line so if needed
  they can wrap down to the next level and be on line
  without hitting the stat bar, would only affect eevee 
  */
 goto CREDITS //FOR help with remembering who to credit, setup credits file to put who to thank for what resource etc. and for help

 /* 
  *vsonic IMPORTANT
  new idea have teach tv man give "Guide Booklet" which will have some info on the game changes
  mostly just use it for type chart and status stuff pluss the diff catgegory of moves
  i.e physical special status,  but also knock down moves
  have info about floating mon as well - think icon just wings
  //can put to the right of name on dex page

  -TYPE_FORESIGHT need remove all use of this, only left cases are in battle_ai_switch_items far as I can see


  -note also fixed missed type change in new chart, rock vs rock, was still neutral instead of resisted

  note think add dex symbol for if mon is floating
  and rather than array value think will just add to base stats
  makes more sense and would be easier to adjust and find, will just take slightly more space

  note also attempt pull/take font atribute max letter height stuff from EE

  made notes in form_change_tables.h for planned changes in handling
  arcues and silvally etc. abilities/forms

  see if can just use list menu stuff for scroll,
  and then have a unique process input function for options menu


  ;talked with Duke in Rhh he shared repo about setting cap based on text placeholer
  I worked out how to make it work for entire string, so can use for capitalizing/decapitalizing names
  planned set as option in menu (need make scrolling list for options menu + faster text)
  but want to be able to set individually for that realized I would need 
  separate buffs for each, ability name and species name

  -note made on  version of cap/decap found can't use COMPOUND_STRING macro for names of things that would get capped
  as it would prevent it from having a callable string name, ... so no compound strings for  names in ability move item species etc.

  //made alt version of elle's text speed up
  mine preverse the old speeds as well as adding the new ones,
  its long and ugly af but it works

  but discovered a graphic glitch in bag when attempt to remove an item that is the last of its list
  messes with the cursor

  issue is howit leaves the toss item menu, 
  if you don't toss an item when it leaves it splits cursor pos between 2 cursors

  if you do toss an item it separats cursor pos from the index somehow
  pretty much cursor moves to end of list i.e cancel, but when you attempt to move up or down
  it moves using the index you the cursor was initially at

  //movemnet logic is at field_player_avatar
  &  event_object_movement
  -

  plans for pokemon page start menu, summary screen
  press start on mon info page shift display evs
  replace total exp with total evs
  and would need make tileset edit so it says EVs not EXP.
  
  //taken from expansion config
  

  
Enable automatic decapitalization of *all* text
Exceptions:
- Several bigrams: TV, TM, HP, HM, PC, PP, PM
- Player names, nicknames, box names
- Strings beginning with {FIXED_CASE}
- C strings that use `_C` or `__C`
- ASM strings that use `.fixstr`
- If mirroring enabled, string addresses passed through MirrorPtr

#define DECAP_ENABLED FALSE
// Enables signaling that a string's case should be preserved
// by *mirroring* its address: i.e 08xxxxxx to 0Axxxxxx
// Unless you are targeting a different platform than the GBA,
// there aren't many reasons to disable this
#define DECAP_MIRRORING TRUE

// If TRUE, *all* Pokemon nicknames and player names will be decapitalized.
// Otherwise, their case will be preserved. Default FALSE
#define DECAP_NICKNAMES     FALSE

 //think will do what does in guolattine remove macro buff for things
 instead use add place holders using buffers, keep original string name
 just increase space for storage of strings i.n summary screen or in battle

 that way wonm't need to store expanded value in save block etc.
 so max string would be 11 or 12, keep same name length
 then make every place where species name/nick name is displayed use function
 to call data/  ex. getnickname /getspecies
 in that function put function that ads species_cap to start of name, and end_cap at end of it

 so just need extra space for display not storage



  next thing see if can do daycare man movement with function, rather than script
  if so, can make auto work with special, when egg is created
  idk may still just do with map trigger, 
  would save on things I need to run constantly

  logic needed:
  set switch target,
  check if pursuit from enemy side can hit (i.e slower/lower priority than target) check whole side for doubles
  if yes, do attack animation, double damage and attempt faint
  if faints do normal faint switch logic/script

  -fix double poison as well
  -..ok so apparently there's no issue with double poison?
  -unless it was actually part of the party menu window issue ? hmm
  well there's no issue with curing it, but double poison
  still resets the counter,  which I don't want it doing
  -ok fixed it, was trying to boost the wrong value, simple fix

  checked and toxic spikes seems off?
  effect appears to work, but graphic is bad,  for move animation
  
  -NOTE IMPORTANT major targetting issue, for self target moves in doubles when click select,
  attempts to target other mon on d pad press not locked to self as should be.
  -FIXED

  -NOTE: for new game plus only change your party mon to lvl 1, make sure player has chance to change team
  before reset, so they can pick who they want to start with.
  Also will need to turn off pc exp gain for mon from previous loop, until player gets certain badges
  -hm could also just wrap that into base setup, start at lvl 10 w no badges I guess or lvl 5 idk
  so no one at or above lvl cap would gain exp while in pc until player gets badge that puts them at
  the range to use said pokemon
  /All so you don't just chese the mode with high level mon, its supposed to be harder which is why you use
  lvl 1 pokemon rather than starting at 5

 -considered cutting all recovery effects, seems like I do, bulk is increased, healing is too strong
 lower half health heal to 1/3rd, for pure recovery moves
 -think I already did?

 Look into necrozma unique learnsets for each form

 -upgrade move belch, (pretty sure I haven't set it up yet either)
 -move only works after has used a berry, change effect so that if haven't used a berry
 but is holding a berry instead of failing it'll consume the berry and then use th move
 -move works but not consumign berry, 
  made work around for removing berry, need setup actual consume logic, thinkg
  need add more berry override to things, and call itembattleeffects switchin or something?
  -continuous use effect works, so if I can figure out consuming berry it'll all be set
  -ok NOW the work around works, sets ateberry in belch check function, and removes item in script,
  then jumps consume logic as it reads the item as having been consumed

  -adjusted pokemon tower and pokemon mansion

  - for power plant, make pokeballs w voltorb electrode reset -(works even better with planned recycle ow items)
  plan setup is make them special that have perfect ivs, set scrcmc macro make perfect iv mon, think that's th strat for that
  use giveperfectmon, createperfectmon,  givemon for bug gym fightring gym given mons,  and craetemon for special ow encounters like the voltorbs
  
  -think make long list of items for recycle list, so when items respawn they can be different, similar to how ow pickup works

  -plan adjust mimikyu disguise make rocky helm, rough skin likes break disguise
  -need chek order of effects with itemeffects to see how to make this trigger after

  -think would need to add extra endturn effect for that 
  put after rocky helm, and rough skin effects,  
  when they activate set hurtbyabilityitem as true, 

  then in disguise logic just check if its true, if so switch to busted form
  don't do for illusion, as that's not as beneficial/i.e dosen't give immunity otherwise

  check custom move setting for mon with no moves, see about changing setup so it replaces individual slot not all with moves
  if there isn't one listed allowign full flexibility
  i.e I could set moves to custom, but only set a single custom move, leaving the other 3 slots to be filled in by normla move learn logic
  thinking was replace blaines first growlthe with a ninetales, but would want to still make sure it has fire blast
  (stll do that but ninetales s stone evo so has no moves, so would need to make full custom anyway)
  -setup ninetales, to replace growlith think may want to change to give hold item so it can hold heat rock, to extend weather
  if rolls sun disk

  fixed issue with weather abilities, added belly drum for electabuzz, added level cap for box exp gain
  -realied planned effects for forewarn and anticipation are essentially disguise. 
  so look at that and make work based on that.+

  working on forewarn anticipate, found disguise glitch,
  cause is depracated form change setup, need to replace w EE version

  -fixed form chjange, think may put forewarna and anticipate back on special status,
  so everything is stored just for first turn, of switch in.
  looking at battlestruct touse, think that lasts entire battle?
  annoying but think would need setup like u16 usedHeldItems[PARTY_SIZE][NUM_BATTLE_SIDES];

  at battle start default to 0, when set activates canceler, then sets to move end so can't reactivate

  use forewarn user to set which battle side
  setup function hat takes battler argument (to use forewarn/anticipateuser) //can just use gbattlertarget
  to replace condition logic in attack canceler  CanforewarnActivate  something like that
 was planning to make this replace forewarned move, but realized can just put store thes the mon id
 side etc. when the battler is in and activates the forewarn and anticipation logic,
 don't need store side, can just use a party filter to say store for the party?
 can probably wrap into a single field rather than needing one for either ability,
 sometning like used one time ability, if works could pull disguise into this as well

 potentially make small array to store single use abilities make function that checks it and returns true or false
 if is single use ability, put in every ability checkin battle_util.
 so it'd  just automatically store when needed?

 would be good future proofing, and shuoldn't add much to processing as if it returns false it'll just do nothing
 hmm.

 so far I know of disguise anticipation and forewarn potentially zygardes form change?
 singleUseAbilities

 ex. battlesruct assignment
 *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureLo) = 1;
 gBattleStruct->multiplayerId = playerMultiplayerId;
 gBattleStruct->dynamicMoveType = TYPE_FAIRY; 
 gBattleStruct->lastTakenMoveFrom[i][2] = MOVE_NONE;

 gBattleStruct->usedHeldItems[i][B_SIDE_PLAYER] = FALSE;
 gBattleStruct->usedHeldItems[i][B_SIDE_OPPONENT] = FALSE;

 gBattleStruct->appearedInBattle = 0; //this also potentially useful, tracks all mon, w bitfield


 coild potentially do  if ((gBattleStruct->appearedInBattle & gBitTable[i])
 set used singleuse ability[partyindex[i]] something like that

 but if I'm putting in abilitybattleeffects there's no reason to check appearedinBattle as that's a given, they'd be on the field
 I don't need a condition filter, I just need what to set

 gBattleStruct->usedHeldItems[gBattlerPartyIndexes[gActiveBattler]][GetBattlerSide(gActiveBattler)] = itemId;
 think this works  just need to set true

 usedSingleUseAbility UsedOneTimeAbility

 in battlestartclearsetdata, most likely place

 fixed anticipation and forewarn now work properly w new effects
 but considering balance still unsure of,

 forewarn checks for strongest move, while anticipation checks only for explosive or super effective,
 in a normal playthrough strongest move is much more useful as ai typically selects the strongest move.

 also every mon has a strongest move, likelihood of a mon having a super move is based on teh weakness of your type.
 and its on bug which does have several but that still relies on you putting htem up against a disadvantgeous situation just to get use out of teh ability
 bugs are also weak stat wise etc.

 forewarn is for psychic  types that don't really need it

 to counter think what I can do is add that logic to anticipation,
 so I get same effect but don't get the benefit of a reveal

 anticipation logic will be
 check if explosive, check if ohko and can land it, check if super effective, else check strongest, messed sensed a strong move for last argument
 -done works, : )


  also discovered issue with new moltres ability not working,
  pretty sure problem is battle_util.c lpogic overlap
  issue only comes up with contact moves

  issue was I forget to put breaks in the absorb effect switch case, and hadn't defined the ability in the battle main absorb logic.
  also becauase of complexitiy of effect needed to activate multiple battle script at a single time one after another to set effect.
  First for absorb effect and then for status effects clear.
  couldn't do 2 bs in a single code block.

  So the solution was to use two different ability effect cases,  
  I kept normal effect in absorb  then filled the rest in the unused immunity case block

  it now works as planned

  as part of update for form chnage, need add SPECIES_FLAG_MEGA_FORM_PRIMAL_REVERSION to mon in bsae stats, flag was set but never assigned
  -done

  -adjusted battle message for multihit results, removed excessive repeat mostly in csae of multihit that kills in one hit
  flowsmuch better

  -remove argumetn/two typed move arguments from absorb abilities, if can't absorb all of it,
  no sense in nullyfing the whole thing...idk that's kinda how immunites work with it, if immune to one type
  the whole thing fails
  but I'd like it to avoid immunities like if one type is immune, ignore it, and just read it as a type all of the other type
  which makes more sense like make it break, and move on to next type rather than storing 0 multiplier?? yeah that could fowkewlknfew?/sa
  and if I do that it makes no sense to be able to absorb entire move... sigh

  -going back and forth on this, for now keeping argument absorbption 

  -found issue with badge counting for oak ranch exp gain, now fixed

   - adjusted cable club script addressed that issue that could cause freeze now fine

  -new note, create new task setup, for catching,  rather than mon goes to x box
   open holding mon just caught in box, i.e from cursor selection,
   so you can just put mon wherever you want instead of having to oranize later
   -scrapped

   then after placement and press B, just return to overworld
   should kick in right after naming task ends, just need to make sure it squares,
   with my added logic that removes mon held items

   -get feedback on this idea, while good for ocd/management very time consuming
   for just catching mon, and potentially unnecessary with planned idea to be able to access pc
   from overworld, limited though it shall be.

   //plan moving mon around doesn't consume charge, but actually removing mon/putting mon INTO pc would
   well, no just make it so only removing a mon consumes charge?

   -do that but keep idea of dropping mon where you want, on catch, its not that big of a time consumption.
   -fix thing before add new, planned changes fix forecast then fix menus, then do this, and check other listings

  plan for forecast, change separate message and transform into different abilitybattle effects,
  think make new ab case, just so I can make it work smoothly,
  think, missing some endturn weather logic, forecast hail is not working, not showing end turn hail,
  rain works though, ok so sun ALSO doesn't work...think only rain works, just because rain has overworld stuff..
  ok yeah only rain works... fixed issue was logic order smh

  -forecsat complete

  -need fix celesteela background, think just revert previous change made to it - Done

  //fixed pic height in dex, but realized, same issue in size chart, w trainer comparison, need raise those, that aren't
  in array, not sure how ot raise as can't just make window, need to actually elevate them, since need raise jutst the mon not teh trainer
  - seems may not be an issue, as some are already floating, think value may have elevations built in, issue just post gen stuff
  need to add and find etc.  found it, its gPokedexEntries[speciesId].pokemonOffset

  will need to further adjust pokedex, categories will remain as they are and be just for the kanto mon,
  with that, no need to adjust the window sizes, so that's less work done. -want to do this next, will be a major saver

  -ok but first, fix category page - DONE
  -also updated values to current pret standard

  finished up adjusting dex entires

  -clean up fairy icon, next, - think done
  -about have my fairy icon how I want it, need remember to eventually add the default fairy icon for those that
  want it

  -think still have issue w floatnig text, when done from switch in
  ok so issue is, if I damage it with a mon, than switch to a different mon, and use a knock down move,
  it doesn't trigger the text?
  ...seems very specific case, it just happens after using multihit? 
  I'm using fury attack with my beedrill, than switching to pidgey and using gust

  did somestuff not 100% but the issue seemed to have been, the condition for it to trigger only 
  when gmultihitcounter was 0, and I didn't have something clearing it for certain,
  I just assumed it cleared when move ended ie finish decrement, but the move could miss and not fully decrement to 0. etc.
  so I removed that condition, and added some extra counter clears, it seemed to fix it for the example I had, so for now am satisfied
  -calling Done  -(back to dex research)

  later note, port dive rock climb from ghoulslash repo in bookmarks
  setup rock climb to be able to work as a map transition

  also still need finish setup effect EFFECT_LOSETYPE_HIT
  so it lasts entire battle

  adjusting tmhm learnsets for floating mon expanding fly access
  -DONE  

  updated floating mon list at same time, 
  considering removing some or rehashing ground type rock move boost
  with so many ground exclusions.

  //potential idea revise or get more cohesive idea of what floating mon shoudl be
  and why they are immune to ground, thought being they can fly and get away at a moments notcie easily
  but I think? somemon just float, (because legless design) and aren't necessarily
  adept flyers or able to go much higher.

  like some are floating do to magnetism, more for an explanation for its design,
  idk how much of that translates to actual flight, and ability to reach higher than 
  apparent elevation.

  *note original idea was replacement for ability levitate, so started with mon that had levitate
  than thought of pokemon movie scene where a bunch of non-flying mon were used to fly people across ocean.
  gengar being one of them, so expanded idea to, lots of non flying mon are capable of flight and therefore being used to ferry people.

  need to go in further detail figure how to balance that

  also need fix guzzlord dex entry, it sounds stupid, pull something
  better to replace the last lines

  also noted issue with later gen mon having grossly high evo levels,
  dreepy being a first stage not evolving til 50 is a horrific example of such

  then work on dex efficiency issue got help from rhh

  AsparagusEduardo — Today at 12:52 PM
  it might just be that it's loading the entire list at once, instead of how Emerald does it, where it's loaded based on where on the list it is
  can't help you there, it's fundamentally flawed and needs a rewrite

  so from what he said, emerald already works how I wanted mine to go,
  so I can canibalize those and make something to fix firered

  gf just wrote bad code istead reusing the better existing code from rse

  //looking into listmenutemplate thing its exactly that a template used all over the rom
  for every used list, including the dex, but in emerald, its not used.

  So they used custom stuff for that, I guess that means I should take that
  instead of using the list menu stuff for firered dex?
  The entire file doesn't need tobe replaced, just the navigation stuff
  and potentially parts of the struct to be compatible w emerald functions

  either replace use of listmenu, or change it so it works like emerlald,
  and doesn't load entire list at once, instead load as scroll

  can't figur out gapless dex entries the non-numerical ones,
  can't get it to load without issue its been on this one thing a month, its too long
  for too little, especially with others progressing.
  so instead for az-lightest etc. lists I"ll just make it like numerical lists
  and use gaps, with that won't need last viewed struct value, and can just copy the setup for kanto
  to all the lists, just changing the list namme

  did that, but list still opens from 0, each time instead of storing place like other lists,
  if I'm going to do it this way, need it to keep its place and open from where was last left.

  -dex fixed, caught pokeball fixed, had adjust different from default but is passable

  -plan give expanded dex at start, change original pokedex script to I've heard rumor of previously
  unseen pokemon appearing all over the region, I've taken the liberty of upgrading my pokedex
  in advance/anticipation of these events, (write something better later)

  basic premise is get the nat dex at the start, change progression blockers from check for nat dex
  to check for defeating the elite four w flag check instead, which is usually when you get it.
  this way post game is unaffected.  -done

  next step, update expanded species to fill in catgegory lists
  -in progress at gen 6

  //tested gender forms, need to adjust make sure they pull same dex entry
  //since diff species but meant to be treated as same species
 //rn they default to 0, but display mon properly otherwise


  for updating oak speech for giving new uppgraded dex
  take part of text from nat dex scene use text
  PalletTown_ProfessorOaksLab_Text_OakSightingsOfRareMons

  mixed in with original script,
  think want to put this when oak picks up the dexs on the table
  or he walks up to them but instead of pick up
  turns the the player and rival, says rare mon text
  then turns back and picks them up.

  then i can do an edited version of the dex explanation
  where he says and so I took the liberty to upgrade my inventions


  --not worrying about dex wrap, I'll leave that for someone else
  

  add wrap around to dex pages,  i.e press up at top to go to bottom,
  can pull functionality from start menu page as it already has that
  i.e press start,then press up on pokedex and it'll take you to bottom at Exit -might just skip this, idk put on back burner for now?

  note, make activation message for poison barb, akin to cute charm
  //seems tiger mom isn't triggering quite right,
  displayed wrong ability name for effect

  tiger mom is too long text message, need reset/adjust
  
  
  //ok tiger mom works when you are using it,
  but when on opponent side it triggers as intimidate instead
  lowering attack, displaing intimidate message
  but issue is it also uses user ability name as its ability


  unfezeant Fs palette is FUCKED!!
  god damnit, idk how it went bad
  hopefully take new copy from emerald and it'll be fine
  -its the back sprite only - fixed took from RHH

  ...sigilyph back sprite is also fucked,
  but that's because they made it look like shit
  my god, gonna need to attempt remake in the image of sun/moon

  double check all sprites now, think can use dex fill test
  to fill all entries and check all front sprites
  //possibly also switch function, so dex stuff
  can read back sprites and check those too

  -redid form dex now that able to sillouette front pics
  removed need to have seen form to display it
  should be clearer for player and still spark player interest/curiosity
  as previous setup while clean/nice to me could be mistaken as bug

  just need to add setcaught to place where I mega evolve or primal evolve
  evolution I believe is already covered
  added, hopefully works - vsonic

  -plan for dex view,to add forms to dex,
  setup scroll arrow, on dex entry page left/right
  to attempt set it so on entry page can scroll right
  to swap to the form if seen/caught
  //would need to overrwrite nat dex to species stuff
  if dex species matches one of the forms
  think to do that neeed loop gFormSpeciesIdTables array
  against dexspecies

  //need add on to dex, make entries for mega forms and other forms
  but would need it to default to the base species dex number
  look at how dex convert to nat dex works ok I THINK
  I can keep it the same with converting to base species
  to make it pull the normal number
  but what I can do is, for the portion that pulls the dex entry,
  I can add a check compare dex species if above nat species, make entry use dex species value as index
  //long as entries are in order can make it pull that value

  -overall changes I"d need to make are add onto natdex aarray, add all forms to list
  wait they might already be in list?? - they're already added
  - add entries for forms to dex entries list in pokede_entries
  - make comparative function to rhh where I pull the dex entry from the array
  will be based on if dex species is greater than nat species count
  -then in scroll vertically function add logic for moving left and righht based on forms
  -mostly done, made ground work, added nat dex forms, adjusted constants
  made it able to read base species info for dex, other than entry
  last thin neeeded is add new dex entries for forms from EE
  then use functions (not macros) for getting base form and final form
  and use those to add on where I need to, to be able to move
  to that dex form, of course you have had to seen both the base and the other form
  to be able to move, but usually that's normal

  plan can just use species since idea is its something I've already seen or caught
  if I've seen teh form, be able to move to it from base species page
  via left right
  -want do work same way move vertical works,
  just fade in to the next species page w dex entry
  -oh change from monvertical its not that function I need to put it in
  its Task_DexScreen_ShowMonPage
  -got whole thing working, but still facing some odd graphic issue no some values
  -thiking could just be bit shift errors because its populating a random value, 
  /since I don't have dex entries added, also need to port categories for mon if they exist in EE
  -since some mon shift too greatly i.e legendary birds
  -or just make diff categories for them, and treat like I did uxie etc. three elves
  -and do specific changes just for them

  -note need add logic for mon area page for trainer size comparison,
  simpelest thing is just take base species values for size, but load mon pic
  based on dexSpecies -done

  plan create evo mothod based on ability will be reach level w ability
  and setup form change based on ability
  these ideas are for rock ruff own tempo and battle bond greninja
  w that I'll be able to remove them as species, and from form_species table
  that way it'll clean up their dex pages as well, as its otherwise identical to base form
  -done

  notes on evo change- IMPORTANT
  //evo change worked, added 2nd param, zeroed out for existing values, will just need fill for new method changes
  //if param 2 not mentioned in function still works fine

  //planned change more complex late gen evo methods they suck and no one likes them, (think need keep for parafin though)
  //ex. EVO_CRITICAL_HITS  change to level_critical_hit just be at level and land a critical hit and it would evolve
  //think will keep level to 25, since these are modern mon and typically 3rd stage evo?, but can easily adjust
  //ALWAYS order name convention to match order of param, i.e level critical hit 1st param level, 2nd param critical hit

  IMPORTANT, idk what happened but grahpic glitch when scroll now?
  //for some reason happens around value 200, attempt shift listitems buffers
  back to use calyrex as that is technically the max value for the dex
  hopefully its as simple as that -wasn't calyrex but changing max value did fix it
  -had to use 907 actual max species, not sure why that worked but glad

  IMPORTANT -Plan my version of species info changes
  what EE has is too much in one place, all the data isn't relevant to what you'd need at one time
  so my plan is take all the graphic stuff put in one file
  make new file graphic species info or something,
  it'll have front/back pic graphics and coordinates
  icon value and palette indecees as well as palette and shiny palette value

  think would like to take evolution data to base stats as would be helpful for balance to have it there
  //that looks simplest think will start with that - nope not simplest, very all or nothing
  but found that all instances that loop evos_per_mon constant get replaced with
  evolutions[k].method != EVOLUTIONS_END  (replace k w relevant variable)
  requires use of another function that sets evolutions to the correct species
  and one that sanitzes to reset it so it doesn't fill w wrong values it seems?
  //but at the least I can add values to base stats struct but just nop it out so it does nothing
  -ok easiest was doing learnset and tmhm learnset luckily was able to setup
  to work like how I wanted where if its nulled out, would instead seek out the current setup
  i.e tmhm learnset leveluplearnset and the evolution table
  w how complex it is and w my changes not sure how I'll be able ot do evo replace
  but for now attempting to testing levelup changes -WORKS
  -w addition of level learnset tm learnset and evo to base stats
  -needed to adjust order of includes in pokemon.c so those files are read BEFORE
  base stats gets read

  ok finished setting up evo logic to be read from base stats
  to get it to default back to gevolution table correctly I had to use
  the same constant for loops  as was used in the member for the table evos_per_mon
  but that conflicted with the base stat setup which used a different constant
  I got it to work w a ternary operator (conditional operator) which assigned either
  constant to a variable in the functions  and assigning the loop value to that constant,
  so its either evos_per_mon or evolutions_end based on condition
  -which is if the base stats value is null or not

  -finished basis for graphic file condensing, made in file species_graphic_info
  need fill array, have blank values until filled, just need to fill name buffer palIndex & pic Coordss
  I have name buffer in each bracket process is copy name buffer fill values, for all species
  2nd pass fill coordinates for front and back
  3rd final pass, fill in icon index

  after grahpic table is filled adjust functions to be able to read from that table rather than the other files
  need adjust table read, and file includes

  -for base stats need fill in learnset and evo data


  -check typecalc again, foud issue with it, counter and probably other fixed dmg moves
  are triggering, type effectiveness when they shouldn't be
  -fixed changed moves that should bypass typecalc to power 0 moves
  they still do proper damage

  -new note, plan for encounters since normal forms are same species just different colors,
  if there is a way to decide how that determines which form to display on encounter,
  perhaps I can do something simlar for forms that are different species,
  do something where it reads the species, checks form_Species_table_pointers
  and could do a random num using getfinalidfromspecies to return num forms in table
  and do a random based on that, or make a function to select odds
  leave blank it will do random % num forms, to do even odds,
  otherwise it'll take an input value and that'll be assigned to the 
  species listed in the json,  and the form will use 100 - that value as its odds
  ex.  PYROAR_FEMALE is species listed  in function value is 70,
  that leaves  PYROAR to occur 30% of the time for the given odds of that line

  -would prefer doing that as otherwise, I'd need to take up multiple lines
  for gender forms as they are separate species idk having more control would be nice
  but would be lost in binary, so perhaps just split it evenly?
  -this would just be for gendered forms? but would also want to do for cosplay pikachu
  not sure if I could? idea I would want is set normal pikachu
  up till a point, then has a chance to encounter any of the cosplay forms
  when pikachu is in table  ok that works, and species_pikachu_cosplay is already set
  to that table, so all I'd have to do is setup forms like that,
  set evenly and then late game set species to cosplay pikachu,
  add some logic to exclude specifically base pikachu from the form thing
  could make an array of species to exclude, can put base pikachu there along with all mega form only mon

  -ok yeah that works for me, have form encounter exclusion table for base pika and megas
  setup encounter function to check for mon that have forms and are not on array list
  and check number of forms they have then if they appear in encounter have even odds to occur
  probably exclude hisiun galarian forms as well, since they wouldn't want to be in same environment?

  -further thought, just make a list for mon it should be not excluded mon,
  since I'm thinking this would only be for gendered mon and the cosplay forms
  and I guess mon that just have alt colors like alcremie vivilion etc.
  well other than equal odds, would be better to weight it somehow?
  -basculin too  note need setup white stripe baculin, that's the hisuian form that evolves to basculegion

  one option is to separate pikachu and cosplay pikachu,
  give cosplay pikachu its own form table, that is only the forms
  not cosplay pikachu, then I can put cosplay_pikachu in the encounter table
  later in game, and it'd pull just the forms

  -would need a filter to ensure this doesn't occur for mega mon
  //hmm well can do a check is mega since all mega have the mega flag
  in their base stats data

  Fixed nat dex navigation issue


  //Important BIND still has freezing issue? happened when it locked into status move
  ...ok bind also somehow trigger future sight so that's wonderful -_-

  -issue with dark exclusion for intimidate seems my setup is causing some lag

  fixing dex entries, add on for forms, not all forms have entries so right now
  it instead defaults to base species dex entry, when done update functions to read new entries and category names

  -need to add new dexentries for pikaforms
  rotom forms as well.
  and values below SPECIES_MORPEKO_HANGRY in species.h
  still working on form dex, need add national dex values
  for forms that will be getting unique entries

  =testing, broke oak lab scripts with changes for post game nat dex eliminations
  review oak lab scripts see what I can do here - least I think its the nat dex script changes

  wasn't nat dex script changes, issue was fieldspecials,  it was improper setup/use of my evolution struct changes
  in the starter filter functions  specifically GetFinalEvo need rewrite it better
  -seems fixed

  -for some reason, dex num, not showing up correctly for summary screen
  its showing blank 000 - fixed issue was bad condition logic

  -still going through form dex make sure everything fits -

  -talked it through thought it through believe will leave forms as they are
  -dont change to base form for dex, or revert mon on catch
  -would be more accesible for randomizers etc. would just need to be particular about mon access

  -discovered issue with evo, again sigh, for some reason all mon being treated as eevee, when in veridian forest
  everyone that levels up evolves into leafeon.  -ok discovered its not everyone... 
  -hypothesizing its every mon below eevee species, some type of fall through?
  -fixed it, was an overflow, isue was I was using evolution method doesn't equal cap incrment i, rather than using i doesn't equal cap increment i.
  with that it would increment i infinitely going passed the limit into other species ranges etc.

  ok NOT fixed,  riolu somehow evolved into mankey
  -ok but that only happens when I build from base stats, not evo table?

  

  fixed, it was issue with base stats evo setup, my condition wasn't right for filterin the evo constant something with how i moved.
  it was the for loop condition

  -think want to put encounters in underpass between ceruleun and vermillion.  aka Underground Path
  would keep at lower encounter rate but think can use some night time mon there

  believe also need replace nidoran m / nidoran f trade since both are available before then.
  maybe do a trade for alt form of early available mon?  could be rattata for alolan rattata?
  
  s'not op, but would also be only early option for a dark type
  -done came up with better idea, trade rattata for galarian zigzagoon, something unique and a fake out

  work on box exp, pidgey seeems to gain too fast, that or they're actually just with me longer?


  -issue w dex navigation scroll down through dex info pages for some reason goes passed last entry?
  only on nat dex, and after retruning to info page fixes itself?

  -potentially rever the battlescript line change, where you can't check your party in swictch mode.
  i made it so if you select yes would like to switch mon, you can't cancel it and change your mind.
  but I like that, its already a blind switch, but that time is used more to take stock of your team.

  on the other hand, it forces you to think more and keep track of everyone's health yourself.

  -fixed cerulean city man, gym badge text based on my changes


  - idea replace fixed evos for level up method, for a value that checks for how many levels gained from when you caught it.
  could use a macro for this similar to evo.  would allow balanced level progression through evos regardless of when set.
  think macro would take 2 values, 1. number of levels passed met level.  &
  2 a min/max evo level a ceiling so no matter what level you encounter it, the levels don't bloat passed a reacable point.
  
  ex. EVO_Macro  charmander evo_level Level_Macro(10, 16), 0, charmeleon  

  and level macro is the lesser of level met + value 1,  and value 2
  for adjusting mon that should require more effort to evolve i.e mon w high bst
  use constants  low effort = 10,  mid effort = 15/20   high effort = 25/30
  the level ceiling would in most cases be the mons original evo level.

  ex. larvesta evolves at 59,  and goes from 200+ bst to 550. so shouldn't be able to get evo early
  so make that high effort category

  for futher even if I use a constant mon can still evo at differnet paces, this would be done through use of the growth rates
  say two mon both evolve at 10 levels the mon with fast growth rate would still get there faster and evolve "faster"
  ex. for grass starters that typically evolve at lower level, give faster growth rate

  - make sure to properly examine growth rates so know what they actually mean

  -may need set metlevel to 0 default to compile but metlevel 0 is exclusively used for hatched mon, and isnt changed when they hatch.
  so think I need to make a new state check for if a mon hatched from an egg or not.
  and use that in summary screen then can replace daycare egg thing with lvl 5
  could just make a Mon_Data_Hatched yes no  did that works.

  met level set as needed

  now issue with mid evo mon as met level doesn't change,
  so for the what need to do is use the level cap/ceiling of the pre evo as the starting point,
  rather than met level.

  i.e ceiling for most mon would be their current evo levels
  so charmander would be low effort, cap 16,  
  so for charmeleon it would use mid effort + pre evo(level cap   i.e 20 + 26   (or mid effort could be 15 either or)

  that should work, all would need is a check for if mon has a pre-evolution

  Noticed eggs hatch too fast and display the wrong messages because of friendship rework 
  since friendship is used for egg cycles/egg hatch time  ok was actually wrong about that,
  its working as normal

 -was able to fix dex scrolling it was issue of the else condition I removed from nat dex

  - fixed form dex, way its setup now,
  megas are treated differently, mega and primal reversion
  will be shown if you caught the base form as if you caught the mega too.
  ,I think need to go into other function, the one that flips to display the forms for mon
  and add logic for megas, it'll display on catch,
  but think if don't have mega ring shouldn't flip forms to display mega form.

  so need add logic to check forms, see if form species would have mega flag, or primal revert flag
  if so skip that form if don't have relevant keyitem
  OR  haven't seen the mega species.

  so filter for displaying form from dex navigation would be having mega ring or having seen the mega form
  DexScreen_TryDisplayForms

  -did so, far as I know is working withot issue

  area page isn't right, its showing mon type when seen but its not supposed to do that until catch on area page
  -fixed same as before changed value to true false, forgot to set false at definition, so garbage data made it always true

  ...discover new issue, zen mode for darmanitan is broken causes transform in opposiing mon...
  and messes with species catch logic, not sure why its doing so.

  only happens with ability zen mode
  -and only when at full hp, when it hits 50% hp it works normally,
  ability is supposed to swap to zenmode at 50% hp

  actually may not be an issue, if starts battle as normal darmanitan rather than zenmode,
  it works normally and transforms correctly when hits 50%

  -but if randomizer idk may be an issue, so look into I guess.

  -found issue w anticipation idk why its not working when it did previously
  moves were bide close combat leer tackle, against weedle issue could be bide, 1 pwr move
  -no it doesn't have logic for 1 pwr moves

  -surely i tested anticipation too and not just forewarn? I know the messages worked...

  -sigh found other issue, moves that  set poisoning status seem to not work well,/correclty
  -when used to reapply poison, the text displays but the toxic damage isn't right. rn using poison gas move to poison

  -ok other issue w poison, I use antidote to clear poison and that works, but for some reason,
  pokeball is still blocked out as if still poisoned/statused??

  more work needed on starter filter, found issue with resist mon and immune mon.
  player got azurill, rival got grookey,  
  -rival grass resists my water, but my fairy is immune to their grass, giving me the advantage, so can't have that.
  meanig I need to further revise the filter function
  -its ok for them to be immune to me, but I can't be immune to them
  --believe fixed, added check for atk multiplier value 0

  -DON'T FORGET, need put back yes/no box for teach tv script, so can avoid it, still have him give teach tv idk
  -done, not perfect but you can A press to skip through it and skip battle

  NOTES - for handling cosplay pika - can encouter forms, but then w item/npc can change costume to switch forms
  Cosplay Pikachu can switch between costumes at any time by going to any Contest Hall in the Hoenn region and talking to the Pokémon Breeder in the green room. 
  This Pokémon Breeder can also remove the costume.

  Upon removing a costume, Cosplay Pikachu will forget the special move associated
  with the previous costume. Upon putting on a new costume, 
  Cosplay Pikachu will learn the special move associated with the
  new costume. When changing costume, if Cosplay Pikachu knows four moves
  but not the special move of its previous costume, 
  the player will be prompted to replace a move with the new 
  exclusive move (Cosplay Pikachu cannot put on the new costume unless
  it does). If Cosplay Pikachu's only known move is the special move
  and the costume is removed, then it will learn Thunder Shock. 
  Cosplay Pikachu can remain in a costume even if it forgets the associated special move.

  //somehow I"m mising with moves that are 100 accuracy?!  needs to be fixed immediately
  ..oh wait nvm was against a pidgey, that I confused, it most likely just had tangled feet ability
  //well I know that works at least

  next - need see about making national stuff load faster
  and change searh filters to go to dex entry not cat page ...-DONE was as simple as changing a single value, found it by accident
  
  -RESOLVED found fix, still implementing,

  also new idea ghoulslash has rockclimb implementation port that,
  use it in caves to replace the stale ladder map transitions that make no sense.
  with that can link different map sections in caves more realistically and stoke sense of adventure and scale in cave syystems.
  can change map without fade in out, can do much more for cave systems, adding backdrop graphics for connections 
  that would otherwise be intermediaries i.e narrow paths could have diff camera angle, maybe have waterfall in back or something

  but I do need to adjust the mon offsets in the entries page for it to look right,
  then change the search option so it takes you to the dex entry page, NOT the category page.
  and seems need to fix the az anme search as doesn't seem to include everyone?

  =also need fix type2 window width for  area page -done

  -need take footprint graphics from EE repo, and update table for those
  -done, also revised, made define for no footprint, so can reuse single graphic instead of making one for each,
  saves about 200 uses of said files, so hopefully saves good deal of space,
  also removed byte defines of those files, replced w gMonFootprint_None curr rom size 19,479 kb  after  19450 kb,  seems bad but
  I did add a bunch of values I didn't have so it offset the savings, but they are still there...without footprints its 19729???
  //oh nvm I'm just retarded and dyslexic as usual *facepalm it said 19749  FACEPALM  ok so I did save space, and complete removal of footprint went even further
  //saving 4 more kb, new size is 19724   thank god I made a screenshot to compare against smh

  since I did that had idea just remove all footrints, its not really useful and just looks kinda ugly on dex page
  so deleted all footprints, replaced only kept blank zubat footprint, to just useful for everything


*/
 goto DEX_SCALING_AND_OFFSET  //pokedex_entries.h
  //pkscale/trainer scale,  then previous solution/pkOffset ot get converted value?  i.e 2.11/20 is approx 0
  //seems proper value, is about 10x found solution?  tested seems to about work, nut sure about negative values though -still to do

 goto FOOTPRINT_TABLE //table for dex footprint values
 goto POKEMON_GRAPHIC_DEFINES //footprint icons pics palettes etc.
/*
  - TMHM Expansion base setup complete, need actually add on to tm list now
  Wanted to make comprehensive list for better list,
  think what I want is mix of gen 1 tms,
  gen 4 tm list, and
  gen 7 8 and 9 tm list

  //gem 7 was best tm diversity, and  added a good deal more type variety and status moves to list,

  //what I like about gen 8 is it brought back some of the moves that were tms in gen 1,
  while also putting moves that were just type variations to the tm list making them much more accessible 
  than having to keep them in learnset,  i.e elemental punches.

  //gen 9 had some good points on this as well, specifically all the elemental fangs are teachable tms  (sans psychic fang which is new/exclusive)

  //think I would want to make the trap moves, false swipe, super fang, future sight tm moves as well.  (and magic coat)
  //-(oh gen8 list added all trap moves to tm list nice)
  //so thinking of having a tm list around 120,
  would need to setup all hms so rock climb as well so around 128 or 130 values total


 //revising logic for tm choice
  RavePossum — Today at 12:02 PM
  I feel like you can address that by locking strong TMs to the late game though. Continuing my example from before, if you put flamethrower in victory road (or even the post game!) it would address that quite a bit since learnsets are largely nearing their end by that point 
  Meister_anon — Today at 12:03 PM
  yeah definitely true,  guess I"m not crazy for thinking this then, so I should try to add variety and accessiblity but
  I need to also think of how strong something is like you said how valuable it is comparitive to everything 

  RavePossum — Today at 12:21 PM
  this is random as hell and reductive as fuck but for moves with no downsides:
  early game - no more than 50-60 effective BP
  mid game - no more than 70-80 effective BP
  late game and post game - go nuts idk

  Meister_anon — Today at 12:10 PM
 so what i'm working with rn is uhh, the base gen 3  list,
 I planned to add gen 4 as it was, and then  slotting in some gen 7 8 and 9 stuff as I saw fit,
 after these talks gonna go back and rework/filter what I had with this logic to come up with something better balanced
  //I can leave some of that stuff in learnsets instead and it'll help keep the total tm list from getting too big

  
  -can keep elemental punchs and fangs as tms bp 65 also is just easier to keep them there rather than
  bloating the learnset but for sake of gampelay wont put bunch of strong moves without drawbacks into tms
  keep trap as tms, remove future sight from tm list   can safely add status stuff, but no strong moves above like 75 for the most part

  -modern games evolved the tm list so everything you could possibly want would be accessible via tm, this was done for the benefit of competitive 
  which is good for them, but it has a large effect on the normal gameplay loop, making things more reliant on that
  and the level up set less relevant

  What do I want tms to be?
  My fav was gen 7 for the tm list, the moves they gave left me with so many options
  I want tms to be for options and variety not just for raw power,
  if its bloated to put something in the level learnset but I want it to be accessible,
  it makes sense to put it into the tm list  like the elemental punches

  for tm etc. making so kings rock affecs flinch moves, and flag will be on all moves that do damage, but will cap flinch chance at 20%
  for all moves that aren't very weak like astonish

  made new move end effect for two turn moves MOVE_END_TWOTURN_MOVES to attempt balance sky attack changes as part of flinch adjustments
  need to test and add text to it, ok added text, still need test

  rebalnced flinch chance, and in process adjusted pixilate to also encompass sound moves

  forwarn glitched when switching in first?
  //tested with intimidate, that works correctly, forewarn (and I assume anticipation)
  is missing sommething that makes it wait to activate until it has a viable target, i.e something 
  is on the otehr side, to activate

  think fouind it, intimidate tracce etc. are switchin abilities,
  but the part that triggers on switch in, is the setup not the actual ability
  that part has its own ability effect OUTSIDE of switchin

  -need setup like trace & intimidate2  case
  also of note, umm fix conversion move effects so it update mon typing in menus
  //potentially change to only change type 1 rather than pure change?

  if I can just change switchin to by default not activate until there is a mon on both sides of the field,
  that should fix everything?  but idk how that woudl interact with turn order stuff

  -fixed changed bs script made separate faint switcin script for switch mode, when chose to
  swap on after fainting enemy, prevents canceling switch, so less free, which is good,
  and now puts all switch  in stuff in that scenario to occur after new foe appears, preventing any glitches,


  re-evaluate how want conversion and conversion 2 to work,
  could be initial plan, or they work the same but one changes type 1 teh other changes type 2?
  ok original mvoes suckes, need find what my plans for it were, they're onthe bs commands for them ni bs commands.c

  pressure changed no flinch just take iron will dmg drop still working ods

  NOTE**(
    *note add a release optino party menu so can remove caught mon,
  without needing to go to pc, also confirmation so not done on accident
  make sure it defaults to teh no option not the yes optino, for people speed clicking
  (hopefully keep same pc animation of icon shrinking goodbye text, and then after animation done blank slot)
  -when setup task for getting items from releasing mon, so it works from there
  *-keep thinking on this, seems feature would only be useful if not playing with a full team
  //catching new mon not typically useful but if looking for a certain mon via pokenav/dexnav would be useful

  actually think what I'll do is make that separate menu, so field moves aren't affected
  press A on normal menu  bringms up normal stuff
  but press Select on hover over slot will open a different menu
  maybe can have ev train, expgain, and mon release on this select menu
  )
  */
goto MAY_BE_CATCH_LOGIC //look into see if forced left side is wide double catch doesn't work vsonic
/*
  - also seems defeatist not displaying correctly
  its supposed to trigger ran with ability if has special status?
  could the entire status be being set to wrong mon?
  -no confirmed effect is working, just some things not quite right,
  as its not triggering "ran w ability"like run away does

  facepalm I had the wrong battlerId in the function
  I was using active instead of battler

  got that fixed but ability name there isn't capped
  fixed

  for some reason bellsprout loads off cener for catdex
  ok not just bellsprout, think may have to do with
  the speed up, since never noticed before hand
  //should be possible to fix
  if I can exclude it from the battle stuff
  idk why it would have any affect on it though

  its skipping frames that's the issue,
  using battle result caught was able to fix

  NOTE**(
    but noticed seems speed causes issue when interacting w certain animations
    affect is causing script active sprite to blink for a moment
    and the mon block ball animation is doing that...
  )
  

  remember still haven't fixed all palette indecees for post gen mon?
  then need to change icons so fit menu

  still to do fix eevee page dex sprite load
  vaporeon disappears for some reason
  //also limit shown page evo methods
  to num on top line

  -fix onix dex entry -think Done

  all exisiting items are defined again - making new patch

  IMPORTANT DAMNIT I FORGOT ABOUT MOVE LEARN GLITCH *facepalm*
  need check level up as well but for sure evo move learn doesnt work correctly, not loading
  I can['t] remember if I fixed it...evolved caterpie i didn't fix it

  //need look into bide leech seed combo, potential bug there, hmmm or not, if i use leech seed and don't get hit
  it doesnt activate so taht means it isn't counting that as damage, the effect is just strong, 

  issue iss with lvl 0 moves not displaying in menu when learned i think

  confirmed issue si just with evo move learn, normal move learn doesn't have issue
  compare and figure out where exactly its wrong, prob something w lvl 0 move returns

  for function Task_EvolutionScene, checked it even reverted to default and it didn't change effect
  if I use MonTryLearningNewMove as opposed to teh evo function it seems to work correctly so not sure what's going on?
  No that's wrong, it doesn't work regardles of which function I use,
  so issue is somehwere else...

  ok  putting lvl 0 logic on MonTryLearningNewMove and go through move learn from normal battle,
  and taht works with no issue properly displaying moves, somehow its only the evo version that has issues
  but I can't identify WHERE the issue is

  ok issue was evolution scene wasn't actually setting the moves, it set the moves but it needed to also set it to the battlemon
  for it to display,  looked at bs commands version and somehow got it working...
  -DONE
  

  //with removal of battle ai port realize need to redo stealth rock rebalance...
*/
 goto TM_EXPANSION
  //point of seom tm set is to have them so its easier and I dont have to put them in learnsets
  //as they are variation moves of the same effect but no idea where to put them in overworld
  //so instead think I'll just have to give them at the very start of the game
  //via the mom, think have her run up as you're leaving same as oak, does the first time
  //and have her give the player a supply pack she's been saving for you
  //make it quick and brief as she doesn't want to hold you up/
  //will be punchign tms  fang tms and some berries
  //idk how to do this and not ruin teh early game balance curve...
  //could instead give the punches at saffron fighting gym
  //can add to theme each trainer is a master of a different punch
  //give on extra pokemon that has that punch move

  //guess I can give the fangs at start since only rattata could use it anyway
  //and they are relatively low power, also gives the rodents a little more staying power
  //progression wise

  //u-turns guess would just have to leave in open world
  //around safari zone I Guess and  2 island park

 /*

  //just learned because of the stupid items.json all tmhm values need their move descriptions to match this exact format
  gMoveDescription_moveId    aka gMoveDescription_RockClimb,  which I didn't do, to save time during porting

  from ee which uses gMOVE_IDDescription instead... because it isn't locked to the json
  //so would need to remove the items json, and remove the item data from the json_data_rules.mk file   make file

  //converted items.json to c file, thinking that'd give me more flex but still need to order tms all in one spot,
  //but there is some small benefit I guess, I can define things in my constants item file without needing
  to add it to my items.h without breaking building but that's still nto something I'd want to do for sake of not forgetting/losing track of things.

  //transitioned the files moved everything over, but now realize its untracked??
  asked in pret issue was the .gitignore file, it makes things not track/ignored by git,
  which makes sense as the file was previously derivitive of the json file

  so  for removing anything from json gonig forward
  process is removing the json.txt file of said name,  renaming the  .json to .h
  and removing the rules in json_data_rules.mk  and finally removing the created file name from the .gitignore

  IMPORTANT Update for two typed moves
  was able to use call if to assign simple move effects that take the secondary effect chance into account and run through the seteffectwchance funtion command
  as two typed moves don't actually take a move effect and just run normally throuhg effect_hit, they just have extra logic in typecalc that does the effect 
  //I thought it was impossible to keep normal move effcts after making two typed as it takes up both the effect and argument slot,
  //but for simple things that only require adding a move effect and not running through different scripts it should be possible
  //I may be able to do the more complex things as well, but would just require multiple call_ifs to manually navigate through scripts
  //ex. if I want it to be multihit and set poison I'd put logic in BS_getmoveeffect for poison_move_effect,  use call_if at top of effect_hit 
  //to jump to multihit script  and ad a clause in the multihit function if necessary for how many hits it should be.

  so yeah just a matter of putting call_if at top of effect_hit to jump to whatever existing battlescript I want it ot emulate
  //say I wanted a twotyped move that worked like overheat and did recoil, I'd make a goto to BattleScript_EffectOverheat
  and since overheat then goes to effecthit normally, I'd need to use jumpifmove to instead go to BattleScript_HitFromAtkCanceler
  to avoid a loop -actually overheat is still a simple effect, I'd just set the move effect for that, but you get the point

  
  foudn issue with pressure/high pressure, seems the attack cancel effect is running on wrongbattler for some reason
  its affecting the mon with pressure/hi-pressure or its just putting the animation on the wrong battler
  //could be trigging correctly otherwise

  -fixed animeation, and for onw deciding notouse exert pressre message for surprise effect

  was also no enter message no "exerting itrs pressure"

  

  //from battle_main.c field endturn function goes before battlerendturn
 //I THINK my abilitybattleeffects is triggered before this so foreast should be fine?
 //ok forecast is in switchin effects whictch goes firstturn, so that does trigger before this thankfully
 u8 DoFieldEndTurnEffects(void)  
 so new changes to forecast should track, setup weather logic so switchin should check and set weather 1st and predicted 
 and intead of setting twice if they match it'll just use double duration.
 also changed endturn forecast, so with struct storage of weather values, it can be compared so 
 shouldn't retrigger the same weather if they are equal, instead it'l just set double duration i.e 10 turns.
 and like I said before, holding weather extender rocks, don't extend it, they'll instead store set the weather constant
 - as of now tested works, changes didn't break effect still works as did before, uhhh need test case
 for they are the same, hard to test but just need confirm it works as planned

 -hex dmg boost doesn't seem tobe working? - done

 //fix quick powder work like metal powder for ditto where it would continue working even when transformed
 // also consider make grass specific text string, i.e x became revitalized , for water sport

 //fixed quick claw now has animation for activation

 -for pc move relearn that'll replace marking menu, 
 make version fo GetEggSpecies function from daycare.c take current species walk backwards appending each species 
 in evolution chain that isn't same as species to list, to use for move learn

 //for mon rebalance every poison move can set toxic, so don't need toxic to be as pervasive as gen 3,
 can give more variety with other poison moves that are more fitting.


  ok so its really simple, effect is just in atk0B_healthbarupdate & atk0C_datahpupdate
  -simply prevent health and hp data from being updated on hit,
  //check how substitute does it to attempt avoid rollout glitch
  //all I need is a check for if anticipation or forewarn should activate/has activated, and then just put the check in the data and hp bar function
  -dont thinkm will be issue w forewarn etc. but test anyway - prob need mon with only rollout as move

  - forewarn anticipation clear not workign right, realized only is triggered if use a mvoe that goes through attack canceler
  -change filter value, or see if there is an issue with just adding attackcanceler to every script, think that's a bad fix
  can potentially just put move change in endturn? should work since its a switch in  --moved clear to edturn and it worked

  -need fix multihit result message, make it not display. well nvm not much I can do if they die the next hit,
  but I guess I can attempt to do some logic like stringutil

  where if current string isn't same as string I want to display?
  that way if its displaying not effetive string, and hte enemy dies on next hit, or next hit is last hit, it shouldn't display result again?

  -testing buterfree plague wings seems work well, need test move that has 100% effect, see if it can still set effect
  //ok tested still works, so other move effects don't seem to prevent effect at all. hm
  welp I call this one done then

  -thought wish there was more bug variety, like bug flying rather tan just being a winged bug, would be cool
  if it was liek some bug bird hybrid, or a jet plane but a bug?  or better a helicpter, and its wings are shaped like properllors
  also more variety in starfish pokemon, since starfish can be so many different things
  buzzird,  a fly bird  - buzzing bird pokemon, part fly part bird
  head of a fly bird wings kinda like griffin

  Bedet Badet   bee droin dreems of bein a flying ace,  bee and pilot idea
  tandem pokemon  has paired evolution with a airplane/jet like pokemon,  when together Badet evolves 
  into piloting ace that flies the jet,   is a bug flying type

 Badet recovers crashed jet that can no longer fly on its own, and together they reach the sky
 -just ideas

 quick claw not woring.. arhauigsngakjrnlksj  had wrong battler values smh,  used battler1 in place was supposed to be battler2
  also futrther buffed quick claw,  made 55% odds,  tesed w stall feels much better, but not too consisitent, just moderaltey reliable now
  nvm forget its not just increase priority it makes move before everything, it was a bit hihg, cut back to 45%

  ok ghost absorb not working right, but just in case of leech seed
  when used leech seed on non-ghost  and switched in a ghost type as receiver of heal.
  it sapped all my hp.
  -had wrong targetting since leech set target logic was confusing, believe now have it correct,
  should change leeched hp to dmg only if activebattler is ghost, and target is not ghost, 
  again target is mon receiving hp - works  wait works w leech seed but not workin gon normal absorb effects??
  -done

  setup black fog, not currently working right, 
  change effect, make endturn effect, that resets, stats at end turn
  //replay normalize stats end message

  -haze/black fog freezing w new endturn need to figure out, for now turned off

  shadow tag still not right for some reason, though I fixed all those,
  not letting me switch if ghost, but I can run - ok fixed switch for ghosts,
  and text issue seems to have fixed itself, w fix to other code?
  //seems to be an issue that only appears/reappears when I have bad code elsewhere...

  new cubone line ability phantom touch, contact limited scrappy
  not for alolan marowak that keeps muscle magic,
  which is better since its likea witch doctor/mystic
  and also can't mega evolve to mega marowak

  -need test, if lightning rod etc.draw in status moves, ok yeah it draws them in, so status moves bypass.
  I think I would keep? need remember what my exclusion were, becUSE i KNOW i set electric can't be effeced by thunder wave,
  but was that not status of type, or just can't be effected by paralysis setting effects?
  /don't have another electric status move that targets I can check with, other than eerie impulse
  -ok was able to test, its just paralysis from electricity that doesn't work, other electric status moves still do their job
  -so think WILL make absorb abilities absorb status, just to make them special exceptions
  ...idk I need to consider this, becuase I literall made everything an absorb ability, and a retarget
  before I don't thjink volt absorb would force electric moves to land on it, it'd only just take them if hit by them

  comparing for balance and my absorb effects even lighting rod are differnet from default versions
  modern lighting rod raises sp atk and draws in eletric, but it draws in all electic, not just enemy moves also status moves

  so i kinda feel drawing status makes them too strong?
  but it doesn't make sense for some mon to be affected by the status either
  //ok I can work hits, what I"ll do is give status immunity but have it not give the normal effect
  //it'll just do the ability made move useless, so just cancel it out - done

  -set weather dmg to ignore castform regardless of ability, since it was created w weather in mind -done
  -still need forecast messages

  //curious what benefit/differencec between using .h or .json for items values
  comparing between enemeral, type and secondary id seem to have different uses.
  for pokeballs in firered type matches secodnary id, in emerald expansion type is constant as ITEM_USE_BAG_MENU

  -lower text height of, both hyphen, and apostrophe

 -setup vivillon to be able to access all forms in game,
 whenever spawned load one of the variant forms,
  think set spewpa in viridian, make it random chance what form it evolves into
  or attempt to make it a function based on personality value?

  new mirror move idea
  //tink want to change ot lastusedmove by whatever target you select, then when call move reset target based on target type of called move
    //is target user use on self, if target both or selected, swap target opponenet side
    //that way can copy move from any mon on fied, even your own battle partner, since its meant to just be a copy of what's seen.
    //think would set priority 1 to increase odds of getting mon you want, 
    //but then chose when attack goes off based on priority of called move,
    //i.e spearow used mirror move!,  copied foes Revenge, since  revenge is a -4 priority move,
    //script should end there, but then at turn order where spearow would attack if it used a minus 4 priority move,
    //spearow used Revenge!
    //so miror move goes off at priority one to say what move is copied.
    //then it checks turn order based on priority of move to see if it can attack now, if not script ends
    //and picks up to use the move at proper place in turn order
    //may need to set this with a status, so can just loop through battlers at turn order, and make it attack
    //if it has the status, similar to bide? without needing further input from player
    beilve would need to use get who strikesfrst to setup and potentially handleusemove

    if I get working, use setup for all moves that call other moves, so they can have correct priority to work properly
    may need a mirror move /called move status 


  -fixed brick break,  - fixed belch - still todo is set strings for forecast
  -remember plan to add berry shop to erika's gym

  -still an issue with koffing, abilities, does some weird error, something with stench or neutralizing gas
  before froze game, now it causes rain? - think this is fixed?

  -considering does IV change, invalidate the multiplier change,?  I think know because everyone has access,
  but rolling a 0 is way more punishing this way hmm - it didn't but it was still way too high, was higher than base game max ev investment
  -lowered that and instead lowered the dmg formula slightly, to help w balance as onix etc was still getting one shot
  -but not much I an do with that outside of making faster and giving better late/mid game moves

  -setting up moltres ability, added new ability for galarian moltres
  for normal moltres new ability need fix battle_util setup,  for fix negative status removal/cleanse  -setup need test

  =for illusion
  //set logic based on in battle, and not a trainer battlle, i.e just wild battle
    //or just battle with no other alive mon in party, if that's the case  search encounter table for map and gruop
    //i.e if I'm standing on land tile look for land data if I'm surfing look for water data
    //and set illusion mon to random mon from table, long as species does not equal actual species of battler

  fixed egg breeding, setup abilities that should speed up egg hatch, (think, should work)
  also fixed in game bug, where egg hatching took an extra cycle

  -unaware logic in pokemon.c is broken, something keeps it from doing and taking damage correctly
  -fixed had damage in wrong place, it was below dmg calc

  -was able to  test lightning rod,  redirect isn't working in doubles -fixed

  -change spawn legendaries, so now they don't leave after you defaeat them,
  they disappear but come back soon as you enter cave again,
  or a day has passed hwen I get timed events working,
  that way you have some interesting to fight,
  legendaries will cycle as you catch them/events are triggered

  need check physical models, to make sure I even have enough for all the legendaries

  -added lvl cap for box exp gain, game opens up around 5th gym, so put lvl cap at 6th badge,
  I think should be fine?

  -readded bw repel system

  -look into cleanse tag, doesn't seem to be working? or it doesn't 
  work like repel which is what I expect, ok doesn't work like repel it lowers encounter rate,
  lol which is ironically what I want super repels to do

  -give cheek pouch out of battle effeect, when ever using berry on mon, have it also heal

  -figured out sand attack groud immunity, setup like paralyze immunity for electric

  -discover major issue with field move setup? for some reason looking at rhyhorn breaks field learn menu,
  no idea why and causes freeze when attempt to back out of broken menu
  -only happened with rhydon, which could hold multiple hms, and had also been taught dig, which would add it 
  to the field move list,  issue fixed itself after removing dig, so problem seemed tobe a max limit either for the window size
  or the amount of items that could be added to the list
  the window appears to have enough physical space for all my option on rhydon ie space for one more field move listed
  but trying to display 5 field moves, breaks the menu, and has it shrink, and only show 3 options
  summary dig, and then the first hm only i.e cut  //need adjust party menu function to fix, somehow
  -fixed, limit was based on old values, expanded party window to 9 and was able to limit to 5 field moves without issue

  I could leave it as is, and just add a string, to it,
  like it works and is simple, the issue is youo lose out on nuance, like use belch with a pecha berry 
  ...hmm well actually this is fine, if you met the condition to eat a berry, it'd already activate,
  so doing it my way, "consumes" the berry losing you the option to use it.
  ok think will just add a string saying consumed berry - when I get it working rework,
  -to get effect of berry when use belch -this woluld only come into effect for early healing so idk maybe not?

 -found graphic for purified zone in pokemon tower floor 4, use that for resurection area, looks like a ritual space
  -put on top floor floor 7, for resurection, eventually remove encouters from floor 7
  -cool idea but may scrap it, would really interupt the flow of the game
  and no real way to logically have a mon die that won't feel like horrible rng,
  or require extreme neglect to the point of being unlikely to ever occur

  -but would make more sense in planned survival game, where you are planned to be facing
  unreasonable conditions, multi status random status, rough trainer gauntlets
  and racing to safety of the next town, so keep for that instead


 -for tm girl on top of celadon, she gives screen tms, add to script so she also gives magic guarad,
 to shwo off new buff

 also change items.json for dragon scale and protector, w items.h pokemon use constants to attempt finish setting as
 evo items but has issue, evolves mon but it becomes lvl 100?
 - don't know if because using item from before change, or what
 -well fixed that at leaset, issue was just adding evo stone item effect to item in item_effects.h
 -knowing that I need to add several more items i.e metal coat, upgrade etc. dubious disk

 -added mor eitems, adjusted defines, willneed to add more to json to properly display/work etc.

 -similar to cleanse tag  -but would need reason to keep using cleanse tag, think give extra effect similar to shedskin, has chance to cleansae status in battle
 -done, all seems to work, repel triggers 2/3rd enconter rate uses var to pick whcih repel is active, resets on bag use and eventscript bw repel use,
 appears tobe properly switching
 
-  new repel change make them all same duration but different strength/effect  match duartion to super repel
normal repel keeps enemies away up to your level
super repel keeps enemies away up to 1.5x your level
max repel keeps enemies away up to 2x your level 

gives consistent reason to keep using normal repel even in later game
in my game the extra repeles will be used for exploring other areas just to get to a gym, 
or to limit the danger you're in

what I could do also is use it to scale enemies, rather than blocking all enemies the extra repels, could instead scale enemies to your level
which wuold allow you to catch more mon/explore for mon mon to catch but keep them from being op for the player to use.

Like the lvl 29/31 dugtrio in diglett cave, can potentially add a bst component as well should I need to, since enough money and repels
could get the player to late content and get a high bst mon, even if at their level it'd still run through thingss.
idea for super/max, if enemy level is within range, but bst is too high, prevent lowering level

-add first instance of super repel afer 2nd gym badge, that way can use for diglett cave and potential to get to cinnabar

think what could do is have super/max repel lower normal encounter rate and then when you do get an encouter it'll be at your level.
lower encouter rate, if enemy level is within repel range  set them to player level, if above limit they'll spawn at normal level
but you still get the benefit of the lowered encounter rate

rather than each mart be different have them all have same wears, just expand based on gym badge count.
excluding celadon (potentially, celadon may use different mart script)
that way you don't need to keep flying aruond to different places looking for the item you need
(use should display hm function logic as template)

 add logic to script for gym guide where he mentions that the gym leaders
 pick their team based on the number of badges the challenger has.

-

 
  need to add script for thunder wave not paralyzing electric types etc.
  prob, just add extra check before can paralyze logic that goes to script no effect

 for some reason repel scripts stopped working?
 I had it setup to do black white style reapplication but now it isn't working..

 change prof oak aide in center by rock tunnel to give eviolite rather than everstone
 - actually give both, have him give 3 of each, change message to if don't want to evovle
 these items can help

 - see if possible to get flash to activate soon as you enter a cave
 instead of needing to pull from party menu - not 100% if want to do

 - look into for anthroyd see about havign custom amount of coins to buy 
 from gamble arena in celadon.
 should be simple, should just be a matter of
 having conversion i.e pressing up down on dpad increase/decreas coin amount
 by certain amount, for realism keep fixed amounts but add extra menu option
 for purchasing custom amount.
 -checked does 20-1 conversion 20 pokedollars per coin
 with fixed purchase amount at 1,000 for 50 
 and 10,000 for 500 coins
 prizes range from 200 to 9,999 coins (porygon)

 - add more prizes to gamecorner, will give reason for replay

 -was able to test and run away excemption to pursuit works

 10/24 
 idea dates for easier finding/discovery
 post update bs commands for switch things seem broken,
 but could be removing use of gactive battler
 but from their attempted to add use of battler to battlecontrolers
 which was much bigger change then expectged may revert for clean up

 noted issues, switch breaks battles, doesn't work correctly,
 also statusicon update w change from base setup,
 it no longer loads properly when status is applied
 status is set and effect works but for some reaons
 need to close and open main battle window for hp box to update.
 could be use of gactivebattler as well, or removal of loop?z -seems to be gativebattler
 -ended up reverting change but saving in separatee branch, would need repalce all activebat
 -and correctly update every battle controller function w battler argument

 had idea from Girldm,
 toothfairy pokemon, sneasler hit run type
 not strong, but evolves into bone fairy,
 clad in bone armor average speed high defense,
 think just keep base fairy?
 hmm like idea of teeth/bones resisting fire but dont like idea of making rock,
 well I could just do it with an ability?

 tooth fairy either dress made of bones, or tools/satchel/bag
  made from a tooth?

  bone fairy clads itself in bone armor,
  think what could do is make abilty bone armor,
  resists fire damage,

  could make tooth armor for tooth fairy,
  if both have fire resist ability bone fairy 
  version would be sturdy to also prevent force switch out -I guess I meant sturdyas in strong 
  -not actually the ability sturdy? think will also give recoil protection? as force switch is very situational

  -ok so base is fairy only but has fire resist ability, since teeth
  -dental protection? lol dental gaurd
  *changed dental guard to Enamel to better signify innate effect rather than an action

  -but evo becomes rock which resists fire already, but w ability it'll be quad resist
  -ok base ability can have resist fire, don't think it will stack if I make it resist on top
  -of a resisted type, so instead think will have to go reduce power root for the evo ability?
  -mmm test it, it may work?

  I like idea of that but not sure if want to be restrticted to
  having to have tooth dress for tooth fairy? - no tooth dress for base version/tooth fairy

  want bone fairy etheral beauty and scary monster

  //name for first form based on
  tooth
  Dentin:
  a calcareous material similar to but harder and denser than bone
  that composes the principal mass of a tooth
  FaeDentin
  Fay.dent.in
  10/8/24

  think for evo can make rock fairy,
  but floating or has wings so can fly

  yeah that works, still rare typing,
  only other is carbink diancie line,
  plus idea was make it a counterpart to mauwille in a way anyway

  apparently idea, think add status exclusion for grounding - completely forgot what this is

  12/4/2024 idea for 2nd form take name from WOrm aka parahumans of slaughterhouse nine char
  think name is bonesaw? find real name do something with that if possible
  -bonesaw is the name but character doesn't really fit, I want faedentin evo
  to be something of a graceful wreckless monster?
  but bonesaw is a bio surgeon the character/personality doesnt really fit it
  think make psueddo legendary (mythic) to avoid issue having to consider placement.
  since its an evo treat it like volcarona,

  10/31/2024 idea from lucky, make shiny more beneficial/reason shiny hunt
  every shiny mon will have perfect Ivs

  12/3/2024 attempt get back into flow, made changes for conversion moves, 
  change to conversion 1 & 2, believe should work as intended still to test
  Conversion now does moedern effect, convesion 2 is original effect,
  that changes based on target main type, rather than move last hit by

  both version only change type 1 aka main type now,
  need test if change is visible in summary screen

  ok conversion 2 changes both types, to single,
  while conversion 1 just changes main type,
  think I may make conversion 2 into new move Called Conversion Z (like porygon z)

  then make conversion 1 and 2 alternates of the same effect, that affect
  primary type and secondary type respectively

  looking into move ui, can't change window position or things in window,
  but think I can just adjust the movement of the outline individually, 
  to make it look better.

  -The last move window and the cancel window are fine just need to move the 
  others.
  -think its window 3 and 4? if you count first as window 0


  note while at it, actually test present effect to ensure it actually works -_-
  ok tested it MOSTLY works, only issue is the heal effect as I have it set doesn't work...
  no crashes, it just doesn't playheal animation, or do heal effect, but the heal text does display,
  and the move doesn't crash...ok nvm it DOES crash if it rolls the heal at the beginning/when
  enemy is max health *facepalm
  -further test its VERY broken -_- when the heal effect rolls, it changes my type
  for some reason
  
  -also of note damage seems to be far overperforming at times?
  or not?

  Look into effect and how animation is decided,
  may need make global value ewram to store present state
  i.e ShouldPresentHeal  True False
  and i guess add that value to least of values clean by the multi hit function,
  so it gets reset to false each new hit

  -actually no, adjusted bs command for present and seems to be fine now,
  still need test for full hp first hit heal message

  the crit dmg is weird idk what's goin on w that?
  seems to be hitting far higher than it should
  -or not?

  **but think I may increase access of conversion 1 and 2, or conversion in general,
  for normal types and other mon that are meant to be versatile like Kecleon

  New idea conversion Z, search for type that resists BOTH target's type first,
  ex. Houndoom Dark/Fire, Overlaps on Ghost

  So if it finds a match do that fist if not then do either or between the types
  would make more consistent in specific cases and be knowledge based gains.

  idea loop type list break if  type 1 and type 2 are resisted, otherwise continue
  end when reach last type i.e if typeSearch = Sound

  If I don't have anything for a double resist i.e double resist found is false,
  then continue w normal search, but store a type for type 1 and type 2,
  then just do a random % 2 to pick which gets applied
  where 0 is type 1,  1 is type 2
  -done

  -solarblade needs to be a TM, ex groudon learns solarbeam by level
  but realized usually its taught by tm, since it doesn't get it till 65
  changed to solarblade but there is no solarblade tm -Facepalm
  --think want conversion to be a learnt move -was already a tm just didn't see it


  In working on New Conversion effect, found potential way forward,
  for new ditto ability, that transforms to mon of a resisted type

  -setup new ability not yet tested, also adjusted species flags back down
  no longer using (1 << 8) realized cant
  also added data for 1 extra tm, was able to build
  but discoverd an increase in EWRAM, unsure exactly where came from
  so making note of differene appears to be 8 bytes
  use went from 251022, to 251030
  ,hmm and rom size took a somewhat significant jump down.??

  tested something I did broke the transoformation grahpic for the abilities
  but imposter still works far as data,
  inversion works "sometimes" completely unsure what makes it so,
  think something w my loop logic,
  think its moving on from the transform data command,
  before its finishing getting the data for some reason?
  as the values for species name is blank when it fails,
  even when it works the original ability name doesn't show for some reason,
  intead it only shows as Adaptability,???
  and move transfer isn't working for that,
  base move is still transform
  
  -was able to fix ability transfer graphic is stil broken,
  think has to do w HandleSpeciesGfxDataChange function in battle_gfx_sfx_util.c
  

  this value being passed to, appears to be used to determine the species of transformation graphic
  gBattleSpritesDataPtr->battlerData[battlerAtk].transformSpecies = targetSpecies;

  *tested seems to be right, commentd out in graphic function and passed my species value
  in transform logic,
  and while the animation STILL doesnt play, going to party menu and reloading battle graphics
  does load the correct image. hmm

  ok fixed everything, (almost) the issue was battle controler crap,
  playmoveanimation was a various command and I removed gactivebattler from that
  which meant all the btle controller stuff couldn't complete *facepalm
  after adding gactivebattler back to function animations played and mon transformed correctly

  -Last thing to test is if I still need my species work around,
  in the transform function, if so I'll just upadte the btl gfx function
  and remove all use of species there, and just use transformSpecies in everything
  that makes sense to.

  -sigh still issue, works for imposter but inversion which is meant to turn into diff mon,
  for some reason turns into target still... it worked before so idk what's happening here
  -...oh I undid my fix of course smh

  -reapplied "fix" and things seem to be on point, only issue is
  palette not updating and I just don't think I applied anything there,
  so should just be a matter of using right value there
  yeah already see what I need to do so no issue there

  unsure about use of battler id in gbattlerforms in gfx function
  -gBattleMonForms[battlerAtk] = gBattleMonForms[battlerDef];

  -hmm double check intened transform logic, think I was supposed to
  to the opposing mons nature right? so I can reveal the nature
  or did I undo that?

  it makes some sense to keep my own nature I guess?

  -also unsure if mon transformed into via switch in ability,
  that have their own switch in ability will be able to activate it.
  rn I assume yes?

  --tested mon turned into anticipation nincada and ability worked correctly

  bit of issue w how type calc works it could actually roll a mon,
  that is weak to the other type, when a better type match i.e dual resist does exist.
  is only an issue for dual type mon, but if the intent is to get a resist,
  it should never make you worse off, so setting you up for a weakness just makes it bad.

  add logic to ensure rolled is not weak to either of the targets types
  type result not < 1, so at best must be neutral
  to target type 1 & type 2

  noticed appears to be some issue w level up w the transform abilities?
  only seen w inversion so far,'
  when another mon gains exp and levels up when the transformed mon is on the field
  seems to cause some confussion in displaying the stats, I saw minus signs
  on lvl up instead of plus for some reason.

  hmm retrospect believe it was using original /base species stats of ditto
  mon I had on the field  and not of the mon that was leveling up,

  started w turtwig, switcched out to ditto who had higher stats,
  who then transformed losing said stats,  defeated enemy while transformed,
  gaining exp turtwig gained exp first and lvled up, showing negative stat gain,
  then ditto gained exp and leveled up, showing plus gain, even tho,
  its actual stats would be higher,  attempting to test again  soon
  -tested same result, think with my transformation changes,
  I need to review the setup I had for battle_script_commands
  in the get exp level up stuff,
  since in the past I did write custom  logic for 
  ditto transformed level up

  -confirmed situation of bug is level up of a mon not in first slot
  when a transformed mon is on the field/in battle

  So issue is what I thought, something w my transform logic,
  not properly tracking change in slot, its comparing base stats of current mon,
  not that of the mon that is actually leveling up

  -believe same issue is wrong w my move info setup,
  when I switch mon, the move info is still tracked to the mon
  originally in the first slot, not the one in the position now
  hmm actually no those are opposite problems,

  *note make end turn reversion for certain switch in abilities,
  to make a class of ability that is literally just for the turn they switch in,
  similar to stakeout.
  will use this to rework zamazenta and zacians abilities
  make them only apply on the turn they switch in,
  should apply battle start and mid battle switch ins
  is a bigger buff for zamazenta
  and to me is more align with who they are,
  they are the heroes that turn the tied as soon as they are on the field

  *=several things to consider other switch in negation abilities neutralizing gas
  so need to check if it activated in the first place, if not don't lower it in end turn.
  we have switch in ability done so think use something like I did for anticipation,
  where I check if the ability has activated, think I'll either lower it, yeah have 
  to lower it by 1 at end turn, nothing else works well,/without issue

  So check if it has activated, will do from within switch in activation,
  then in end turn logic, just lower it, if it activated
  and charater has x abililty, offers chance to switch off ability
  to keep the attack increase if you want to strategize that

  -believe with how I'll have to do it, the effect itself is going tobe 
  coded separate from the text of it,
  I think...well the full effect will be in separate places

  huh nvm was simpler than expected, just needed a protect struct
  but since making new category, think need make new case value
  to properly organize the new effects
  one turn switch in abilities
  -think got it working now just need test?
  made new category that should activate before end turn abilities

  ok ability is not quite right, its only working
  to decrease when I switch in mid turn, if I do battle start it doesn't work?
  --found issue believe, so it seems i just didn't understand how turn stuff works,
  faint and switch stuff is handled BEFORE the turn changes,
  meaning if I use protect structs the ability would be cleared
  before it could be used unless it was used mid turn...

  hmm ok think I can use gBattleResults.battleTurnCounter


  I know understand simplified a turn ends right before you're allowed to select moves
  so I think what I need to do is somehow exclude the turn battle starts
  from the clear
  and turn yuo switch in after  amon is fainted
  but somehow still make it activate for switch in mid turn/battle...

  so changnig back to disable structs and need to figure out where
  I can put the cleanse for it to work how people would expect
  but don't think can be in turn value clean up

  had to do good deal of turn order research but was able to get them working

  -NOTE**( make Bleakwind Strom exclusive move to Tornadus Therian form,
  if it is in the other form the move should get replaced w something else
  idk blizzard)

  also give tapu bulu better moves, notes on that in its base stats page
  
  tested later battles, dmg is very inconsistent and strange at upper levels,
  also for some reason sandstorm end turn doesn't seem to work?
  timer is working but effect doesn't play at end turn to do damgae??
  no animation either

  also surging strikes insn't working correctly, not doing full 3 hits

  //EFFECT_HIT_SWITCH_TARGET  not switching target...

  ran multihit (surging strikes) into cute charm effect triggered on first hit
  rather than last hit, need fix

  fixed issue w sandstorm was actually for ALL the weather effects...

  *Think need to test build to compare modern and agbcc to ensure didn't break something
  I didn't touch any structs or attempt optimizing so I don't think there should be but
  will test anyway.

  ran make old, rom size is comparable it also went down,
  but the ewram  is unchanged, on old to the previous numbers for modern,
  so there appears to be some issue here+

  -Note potential issue w use of IsMonShiny function,
  double check it works in rom without issue

  -Note move info callback still needs work, doesn't work if switch places,
  just reads original mon, i.e if first slot switches places, it still reads the original in its new place,
  or it just doesn't update the value after they get moved?

 potential issue? notsue the cause I stacked up my atk def boosts and defeated an enemy, 
 but my boosts seemed to go away? when teh next mon came out?  guessing something to do with dmg function
 semed to only be doing 1 dmg, so I guess its one of the dmg = 1 things I added?

  make field moves for morning sun & moonlight,  use those for changing time think set time to 7am or 7pm respectively

  */
 goto HM_USE_SCRIPT //scrcmd  function used to decide if mon can trigger overworld hm use, adjusted to use can learn move not move learned
 goto GET_BADGE_COUNT //trainer_card, made funtion to hopefully get badge count, use for repel, mart and other scaled effects
 goto REMOVED_RS_COMMANDS  //think stubbed function from rs mostly related to rtc & weather, need add back..scrmd 

 goto ITEMEFFECT_DATA

 goto FIX_WARP_RESPAWN_LOGIC //for heal warp location, on whiteout, and think relevant to teleport

 goto END_TURN_RESET

 goto TMHM_LIST //moved to tm_case place for listing of tmhms add on as needed as well as update technical_machine and hm count
 /*#define NUM_TECHNICAL_MACHINES 50 //change to 120 later  in item constants file
#define NUM_HIDDEN_MACHINES     9*/

 /*

    //attempt function that will put linebreaks in strings automatically, 
    take line limit input value i.e 20 chars, and make function read 
    based on some logic and decide where to put line breaks.
    1.go forward 20 chars, if the character preceding that char, is the one for a blank space
    \go back until preceeding character is not space, and insert \n line break character there
    2. for readability, ensure do not end line with a conjunction/contraction, i.e (or, of, and, if, but, when, then) etc.
    3.after insertion of linebreak see if you can go forward another 20 chars before you hit end string, and repeat step 1.
    4.once hit end string, read from start to end string, and ensure there are no spaces after linebreak characters, if there are spaces delete them
    \go forward from start of string while checking preceding two characters until you find the chars "\n" then check for space charactesr following
    \and delete them until the character that follows them is a non space character.

   add move description limiter, works perfect, just for max limit
   was able to setup no learn hm setting, i.e just need to be able to learn hm to use it
   and have badge that activates it of course, adjusted all scripts to fit,
   and for open world plans, (as much of that as I plan for) reordered
   hm acquisition order instead of flash being first cut is first, then surf
   with luck and repels, should be able to get to cinnabar, and be able to get fossil mon early
   as 2nd gym, don't plan to be able to do blaines gym etc. so don't think will add level scaling there
   intead do at later gym badges / more than 2nd badge

   think will need to add flag based npc, in viridian to prevent player from 
   doubling back and getting to vermillion early and getting stuck
   maybe not digglett cave should be impossible to get through, hmm
   but then again, if you're lucky enough w repels to get to the other side of diglet cave
   it'd be kind of cool, to be able to take on surge then and there hmmm

   with idea that gym leaders scale their teams based on number of badges players have
   it woudn't be odd exactly if I only level scale the gyms, and not the overworld/
   yeah that works for me, and with everyone being rematchable
   you can do them again if you want when you're stronger and have more badges

   so gym would be scaled to a lvl cap rather than your team level, (until 8th badge)
   think for 8th badge, have toughest team, but scaled to whatever level you bring in.

   if you want to take them with a low level team, but have 8 badges you should be a good enough
   trainer to handle a tougher team

   upgrade calcbasedamage to fix sidestatus argument
   I setup sp def buff for mud sport in likeness of sandstorm effect but its extrmeely inneffective.
   ground types typically have overlapping special weaknesses and low special w high defense

   sandstorm buff is 1.5x, I had planned to make it lower but w how sp def goes into damage calc, it already..
   but I think for it to have effectit needs to be double
   making 1.7 more than a 1/3rd cut since you need to invest a turn in it, and it doesn't do damage/passive damage
   to counter replacing sandstorm as the premier ground buff, strength alt effects of sandstorm, 
   its a buff for groud types and an evasion boost for them as well as adding extra passive dmg, the full package so to speak

    -need fix koga gym, most trainers there are psychic types, add more poison mon
    -w new poison v poison immunity having psychic is a good counter since the player would likely attempt to bring a part poison type

    give koga better mon variety, add some quilfish (think he doesn't have that)

   - fixed in-game trades to givemon at level around average of player team
   -and fix badge obedience set for taking odd badges, may remove obedience cool idea and realistic,
   but doesn't really work well? given freedom of play - checked notes attempted setup, adjusted leves and changed checks - test

   -need fix safari ball throw, atkEF_handleballthrow changeto use original ball throw logic for safari zone
   no need to make that more annoying - looks to be good now

   -take doduo out of safari zone, its literally available on the route outside town,
   remove common mon frmo safari zone, 

   -also plan buff tri attack, just make use split of whatever is highest attack stat,
   since many mon that got tri attack in gen 1 were physical attakers and then the type/move became special - done

   -need make sure ev gain setup is working

   also looks like stench has issue where it tries to activate on first turn
   -bug with copy cat or whatever kadabra's copy ability move is, it takes their health when they copy ability

  hmm could also be a neutralizing gas error? triggered when switched in castform against koffing
  thinking further probably was issue with neutralizing gas, and how worked with weird setup for forecast,
  script order is odd - need fix this it causes freeze or stench?
  -might be a combo of stench & neutralizing gas, what happens is  I take out a mon with one or the other,
  the leaving message doesn't play and then when the next mon comes in with said ability it causes the game to freeze
  -can't remmber If I attempted anything but it seems to be working fine now?

  keep eye on bind it mostly works, but when mon confusion hits itself it goes to struggle,
  need keep an eye on logic that causes struggle may want to remove that option,


  got it working, also using sound for first time, realized the play growl if crit is working, nice
  that'll be a nice qol upgrade if I can get the move animations to speed up, without breaking audio,
  so people won't need to speed up.   from ApplyRandomDmgMultiplier
  //small bit of work tweaking that to do still, just clean it up some and include more effects
  now sound works correctly, for enemy too, added more space in effect to free sound channels
  */
 goto NEW_TYPE_CALC_FORMULA //in battle_util.c keep testing new effectivness remove comment if decide to go back to normal
 goto SHOW_SUMMARY_SCREEN  //plan see if can use for battle move context, press L to jump to summary screen make callback go back to battle

  goto SPRITE_ANCHOR_CHORDS //men2.c  file for placement of tm on mon sprites
 /* descivored tm case glitch,  I fixed the mon placement previously but I believe when I go to party menu and then come back
  because I kept both versions its retruning to the wrong tm case logic

  IMPORTANT major issue w tm case,  canceling tn learning causes weirdm desync w tm case menu
  1st slot mon drifts as if it was using the mart tm movement logic

  also pressing B when attempting to learn tm, when the tm is on mon forehead,  teaches the move
  but cancels, the learn animation, and removes the item from the bag, even though I've set it to not remove 
  tms when learning them. (tms should be reusable)

  and tm learning doesn't follow normal move learn,  so I need to setup the forget move confirmation
  like I did for party menu but for tms smh

  current work:
  -testing fixes for tm case and setting up confirmation message for it - logic in partymenu.c
  fix call back, from tm use so doesn't break mon sprites display
  then finish working on bind
  fix gen 8  icon palette indicees, 
  also gen 8 mon (least I tink just them) icons too big, some don't fit w new summar screen move info page

  -sigh status animation for infatuation not playing - tested w cute charm
  -ok looks liek attract works fine, just cute charm was the issue?
  pretty sure never finished cupids arrow as well? need check fi that works, should infatuate and target like trace but ignore gender check


 note type bug existed before sheen removal so it isn't that
 & also grookey  & scorbunny have wrong palette for their icons+

 seems weird bug with move pound its ignoring type?

 for eventual setup for loop logic for field_specials, starter selection
 use if mod/multiplier to check if rival starter is super or greater, to player starter
  for starter base form or starter final evo  
  or rival starter or final evo resists  the player starter

  think plan put logic in function, and do for loop for if false

  reworked ABILITY_HONEY_GATHER into free sweet scent field move better ow effect imo and better niche
  as you fully control effect rather than just a encounter boost

  when do berry encounter logic will need to wrap it into sweet scent setup so
  it pulls just those encounters w nature etc.

  still need setup field move port stuff, and figure how add stuff withuot repeating
  need write new ability description for ABILITY_HONEY_GATHER,  also change setup to match new pickup
  so don't need to keep slot empty to do anything,  just make it add to bag with message display in ow after battle

  thinbk honey gather description, pickup honey blahg blah attracts wild mon honey sent soak into skin or something

  honey pickup isnt setup yet, port from emearld later and then adjust  with my ow pickup function in mind
  to remove need for held item slot to be empty, jsut have it put into bag

  bloodmoon ursaluna looks dumb, change put mark on chest not head, similar to ursarnig where mark was on chest makes it stand out more
  as an alternate to normal ursaluna  large red ring on chest that glows with mystic power prob make smaller than ursaring's
  also make green scar eye glow a bit if can, or just really stand out new front sprite reared back instad of hunched
  to better display symbol on chest

  //reworked infatation set, cupids arrow, flower veil tweak and setup cresselia ability similar to sweet veil fairy aura
  //doing to remove levitate and setup femme fatale  -done finish setup femme fatale

  setup most abilities for 3 elf spirits, plan think need put grounded icon, for mon in mon summary screen
  to show that its grounded i.e doduo etc.  mostly for flying type mon
  
  separate note planned move cat icons will be physical special, contact and grounding

  -finished trap effect setup, all working, still need test swarm, but should work.
  //added setup for grip claw and suction cup idea, so trap duration will be 7 turns and allow user to switch out
  //and still keep the trap effects

  -still to do fix issue with pickup, where it doesn't proplery consume item until 2nd turn
  -think done, redid item consumption based on emerald and think fixed it

  -note rebalance seismic toss, its too strong, upholding was right, got lvl 100 onix and its max hp is still under 200 
  ... oh then a different one had hp over 260... idk anymore man, guess its fine, onix has one of lowest hp in game anyway


  //remember to make values to store rival starter data in, i.e personality nature etc. or just personality if everything is based on that
  same as roamer. think may make for entire rival party, potentially put in battle main?
  can make store entire value of party only reset personality if mon isn't the same species or an evolution
  //since slots move a bit, think I will have to loop 6 times, looking for each mon

  -nother break double kick is causing game freeze, seems to be just against opponents of certain type combo
  i.e super effective and resist type, so I'd assume it was something todo with my new type calc, but it doenst effect all moves of that type,
  jus double kick?   triple kick works perfectly fine

  its something to do with type calc or result message
  -also result message for wonder guard aren't qutite right, for things that do no effect it just shows no effect, 
  not wondergaurd prevents, which idk maybe that's correct??
  

  -also for mon summary screen need swap placement of name and lvl info,  at lvl 100 it runs together, so just put name on left
  then level data after? hmm would still look strange for longer name mon, just move name over slightly - done

  -planned new version give pokemon command, rather than having to balance given pokemon via script for progression 
  instead set given pokemon to average of players current party level. so wheever its done the mon will be on par with what player is using.

  inspiration for idea is lapras you get in celadon, its always too low level, then also mon in safron, and with plan to add more gift mon
  its a good idea, think will do long as gift mon isn't an egg,,  plan take original command, set it so if level is left blank or 0,
  code will fill in field and set leve to average of party level - DONE doesn't impact mon caught, or lvl 5 mon

  */
 goto DEX_REGISTER_DATA //plan remove nat dex checks so can show all mon - done, giving nat dex at start, removed nat dex from checks for game progression
 goto SUMM_MAIN_WINDOW //main summary screen box, where mon sprite is shown
 goto CUSTOM_SETUP_GIVEMON //change for givemon script command, so don't have to worry about setting level just use whatever and it'll match
 //player average level so mon given can actually be used, excludes lvl 5 mon, as tey are meant to be at that level.
 //this includes starters, fossils and magikarp given by mt moon.  this change does not effect caught mon 
 //can use average level function to scale enemy parties i.e level scaling

 //but other idea was use gym badges to scale consider later

 /* -double check sturdy effect make sure works fully how I planned

  planning make muddy water  water groudn EFFECT_TWO_TYPED_MOVE, my versin is already different as two types moves can get stab
  default version doesnt get that, way move works is if one type has no effect entire move fails
  even if 2nd type would be super effective, sounds odd, but technically is consistent with other moves

  //think want to make into two typed move, make custom effect so can set accuracy drop in bs would drop power to compensate
    //thinking water//ground bp 65, would still be strong as most things weak to water are also weak to ground
 

  identified issue with palette icon, its gMonIconPaletteIndices  //seems can go to 0-5
  the indicees aren't right compared to emerald its different
  need to go through and adjust all these they can differ per icon, so different evo can have different indicee values that work
  //seems to just be an issue w gen 8 far as I can see though at least

  also triple check species_names.h seems some names are still truncated found corviknight and corvisquire were off truncated by 1

  - after that will still need to adjust icon size, prob just take it in grahpicsgale scale it down and put it back in buffer dimmenssions
  //

 ok noted type bug works off whatever was last there, if your last fight was a trainer battle and the values were set correctly
 you'll go into your next fight in the same state,  switching out clears it, as there's a function that properly sets type from base stats
 if you fight a wild mon and have bug glitch, and then fight trainer it will carry over the type bug and treat them as type none
 need to see if it works both ways, if trainer swtiches and it populates correctly and I then fight a wild non will it also work correcltyu

 identified and fixed type bug, problem was BattleIntroDrawTrainersOrMonsSprites, its the function that sets type before battle start
 problem was battlestruct was set to 0, but I never added type3 to this function, so it was essentially making type 3 default to normal
 so type bug is gone, now I have to deal with the 4 other bugs I found in the process...

 //not nat dex mon don't trigger pokedex script on catch, need fix

 there's now also a move learn bug...if I select no to move learn, without goiong to move deletion selection
 it'll display as if I deleted the move I was trying to learn and replaced it with  the move I was declined to learn...
 1 2 poof deleted baby doll eyes and learned baby doll eyes,...actually nvm it completely replaced my first move...
 even though I declined to learn the move   sigh   
  - still working on , seems part of that was do to being leech seeeded while its broken?
  - oh that was issue from lvl 0 move learn, separated into 2 separate move learn funcions, lvl 0 just for evo

  - move learn still has some issues, causes freeze when navigating yes no options for some reason
  -plan fix move learn, fix bind, then fix  tm case windows then mvoe on to dex update and fixes

  //status setting from abilities seems to not be working?  poison point doesn't seem to ever poison
  sweet kiss also doesn't work, atk string goes off but move does nothing?

 also forgot evo moves that are auto learned don't populate the screen i.e lvl 0 moves
 i.e learn 2 moves on evo from lvl 0, so but then learn a move from level up in the evo
 the lvl 0 moves dont show up so you're unable to replace them in the move learn screen
 only the moves you had prior to evo are displayed,
 but after evo they are shown

 - need check sound type change, former normal moves are now exempt abilities that change type from normal like pixelate etc.
 so check how that affects those abilities, i.e the mon that get them what former normal moves they have that were changed to sound.

 got help from kurausukun and shinny from pret, with oak ranch pc exp idea, it work but had bad optiomization that caused major lag.
 removing box encryption helped greatly, it was also recommended to put back the species check and not egg check for loop to further optimze
 and that building modern should help a good deal as well.   right now its down to about half a second at triple speed. so barely noticeable

 setup species checks, effect already worked, but need to further optimize/balance.
 right now each step is 2 exp, so lvl 5 mon would lvl up by the time you walk out of the pokemon center
 I think keep counter size but make it increment about ever 30 steps?  maybe 23?  
 (note if I'm running back and forth catching mon it wont really gain exp since counter would be resetting)
 (oh nvm its fine, since I made sure it wouldn't run function unless counter isn't 0)

 also would need it to scale, so think, add extra filter, before BoxMonAtGainExp  sets exp
 scale w level, case's must be constant so can't do scale with switch case
 would need to do if statements instead
 plan is based on level  (i.e if level is  greater than floor) multiply the exp to be gained by 
 an amount

 30 works well - think want just scale to keep it consistent

 can calc how much it needs shift,  
 medium fast exp gain uses simplest formula
 #define EXP_MEDIUM_FAST(n)(CUBE(n)) // (n)^3     where n is level

 lvl 5 = 125
 lvl 15 = 3375
 lvl 25 = 15625
 lvl 30
 lvl 35
 lvl 40
 lvl 50

 think when I get to lvl 15 try do exp ^ 2   so will be


 experience = GetMonData(&mon, MON_DATA_EXP) + ((gSaveBlock1Ptr->oakRanchStepCounter /= 30) * gSaveBlock1Ptr->oakRanchStepCounter);

  exp gain isn't working now for some reason, only gives exp to first slot mon?
 fixed issue was, wasn't using constant value for counter replaced 17 divisor with var that wraps at 17 before increments counter

  //change illusion ability effect for wilds, make select random mon from encounter table ability illusion
  //setup pressuer adjsutment so doesn't retrigger in same turn in doubles
  //moved base odds to hi pressure, remember only want on mewtwo for most part, plan to  replace with uniques for most legendaries
 /vsonic note

 defiant competitive also don't work for some reason, goes into infini loop when lowering stats smh

 held item spirte/icon think too big to use in held item slot but think can use make file rules to build smaller versions
 same idea as the logic for audio file compression for stuff that was too big

 see if can setup rules to build files in a certain folder an extra smaller icon in a icon folder
 so put all item graphics that can be held in a helditem folder  or just separate key items out
 and make all icons in there compile smaller versions into a helditem_icon folder
 - actually may not need to do that, looking at pc move item menu it already shows grahpic for item icon at perfect size for sprite

 next task  fix multi task, then aftermath, issue is targetting is on wrong side, and infini loops
 think best fix is just make switchout abilities case after switchin abilities then use switchout abilities done flag
 similar to how switchin abilities done works. - well nvm fixed aftermath, it mostly worked I just forgot to put the ability removal back
 - think fixed, but seems move animations taht call others don't seem to work for repeat hits, they play once
  and then nothing after, but dmg etc is working fine now

 frozen status not working, target can still attack even when supposed to be frozen solid
 fix in attack canceler logic

  - fixed issue was wrong battler logic, used gactive when I should have used gattacker

 - fixed mon cries, issue was firered table was in diff order than emerald table, prob because of 
 the firered weird bit table logic default used.

 -pickup still not quite right, when it picks up a berry and uses it same turn, it doesn't remove it
 so it gets resused  and lansat berry seems ot be displaying wrong message?

 - make message for aviator/run away   src atk mon safely escaped with ability buff
  message will play on switch, will make sense for why pursuit failed to hit them

 note * change run logic to work off battle speed stat, not just base stat

 also eventually go back to summary screen move descriptnions graphics and adjust lines 1 , 2, 5, & 6
 first group is too high,  2nd group is too low
 couldn't fit with existing tileset prob need to expand and add on to image

 also for physical special contact icons, isntead of one for each
 make icons that are combinations of them, so don't have to worry about them
 loading in separately

 so. physical contact,  special contact
 then, just physical  and just special

 just paint over contact side with transparent color, so it doesn't show up
  dark grey background, text in black, with deep purple text outline
  icons will be separated by a white stripe through the center
  will make it appear separate, and make it even easier blend w transparent color when other side is missing
  helps keep it symetrical as well
  rounded corners on outside flat inner side

 tm case decided I should go fuck myself -_-  
 graphic glitches on both sets even though haven't even changed windows yet
 but only when windows pop up i.e money window when trying to sell tm
 title glitches when try to use tms - fixed window isn't fully right 
 not fully working the messaeg box isn't fully changing color when displaying yes no window -

 -note later rearrange some ss anne trainers to force double fights,  possibly turn them into double battles random chance
  //and gentelman on second floor that talks about safari zone give rare mon to show he's been to teh safari zone

 //remember add FLY to more mon learnsets, refer to gFloatingSpecies list for starting point, note even pidgey learns fly, size irrelevant
 //emerald expansion changed how these are handled, more akin to levelup learnset, which removes the bit array limit allowing for many more learned moves
 //so will port that

 -rival starter evo didn't work, starter wasn't shown in ss anne fight instead duplicated existing entry
  restart  test to see if that was just because of save issues from rebuilding rom etc.

  restartin to test that, but need fix move learn bugs, first, after that go back to fixing bind setup

  tested looks like it is broken I'm so sure it worked before so idk wth us going on with this
  instead of evolving the stored starter species, its just copying the data of the mon before it...
  identified issue, it copies previous mon value when party size is larger than species data,
  it wasn't properly setting a species to teh slot, that was the issue, because it couldn't read a species it copied last mon

 //new effect for rage instead boost attack raise move power for rage each boost, formula gbattlemovepower = power + (10 * rage counter)
 //assume hit each turn and use each turn after first use, move gains 20 power each turn
 //Its power of anger type of attack would depend on mon type etc. so doesn't really make sense to be normal
  //ok got it fixed, setup dynamictype so move type will match mon's type 1, rather than just being normal 
  /think done had rearrange type order for mon that were normal

  for better balance, made  atk cancelers for status and truant remove rage status, doesn't affect rage counter
  sleep freeze paralysis pressure flinch spirit lock (when its done) and truant

  -still working on this, plan changed to put rage end message before normal status messages. search BattleScript_RageEnds - works

  rage looks fixed, foudn and fixed issue with contact abilities,  need add faint message for stench and neutraliing gas removal -eventually

  -need redownload opal for assets
  - also remember changes to status moves, that they use type for calculation now,
  just need remember to communicate that to playerS*

  - discovered MORE FUCKING BUGS, smog does dmg and poinsons, but then prevents user from switching
  future sight CAN'T kill, the target goes to 1 hp and then it just stops fucking doing dmg
 - branch poke doesn't have an animation

 -when mon in first slot is swapped out and gains exp to  level up 
 where it would learn a move its still displaying the wrong mon id slot
 its showing the mon swapped into slot instead of the actual place of the mon now
 can use summary screen personality search party loop to fix i think

 -believe fixed

 -also need do same thing for overworld move learn? it doesn't have confirmation message
 //icons for message for move learn from party menu/overworld isn't right.
 //with changes made, actually nvm just some icons don't sit right?
 //gen 8 icon grookey is too high? most work check gen 8 stuff  scorbunny also too big


  for pc access from ow to switch mon, make it not work when "indoors" that way it wont work when inside gyms or what is usually a guantlet
  plus if you are indoors it might be a pokemon center so there's no reason to.
  *note add feature so its not cheasable, pretty much can't just drop a mon in pc when its low
  and then take it back out immediately for free heals
  message: "blah blah blah pokemon name needs more time to recover"

  think do like I did summary screen logic, store pokemon personality value
  think do with a counter, when yuo open pc from overworld, it stores the personality values of every mon in the party
  to a field, before box opens,   if you deposit one of those mons into the box
  its passed to a global field (i.e g value)  so when you try to with draw a mon, if it matches one
  of the personality values it'll refuse to withdraw it, and put up the message from above.

  now here's where the counter comes in, after closing the box  you are on a 100 count step counter
  amd when that hits 0, the stored personality values are reset to 0, and you can take your originally deposited mon out.
  (potentially make counter 50 the point isn't to lock them out for a whole map,just to ensure player can't cheese and immediatley retrieve them)

  - plan make value to store rival starters ability num from first rival battle in oak lab, then use it to set the same ability 
  so at least that never changes for the whole game.
  - make g value, in battlemain default it to 0, in npc party for rival is first form,
  if g value not 0, use it to set abilityNum 
  else if g value is 0, take abilitynum after its set and store it in value.
  that way it'll be used for all other fights
  should default to 0, and be set to 0 at game start or I could just use a var I guess either works
  if I can store them with vars then I potentially store all abilitys for entire party but mon switch up I think,
  so think I'd prefer just to do it for starter

  -yawn change works, still testing but rage status removal seems to be solid

  *note go back and fix pickup display text,  give it a pause on the string - perfect that works great now

  made middle ground my new rage gets stab, and boosts base power of move each tiem it gets used or user gets hit
  and it still gains atk stat when user is hit

  finished setup, rage looks good, and was able to fix teh issue with displaying the right dynamic type, had the wrong value listed
  but note* need remember to remove marking option and text from pc menus

  setmovetypebeforemoveused isn't displaying correctly in battle_controller_player
  for some reason its resetting displayed type based on either type 1 of attacker, or its not working i.e reading dynamicmovetype as 0
  and showing the base move type


 enemy trainer sprite is not moving over to the correct spot on battle end, (I think)

 eventually will need update ai logic not to make more difficult just to adjust for the changes I've alerady made to stay consistent, like phy special split etc.
 pokemon cries for post gen 3 mon don't sound correct

 redo forecast changes give custom messages for entry, and think would like to make less random.
 something like when it enters, it'll display a like castform's Forecast predicts bright sun with a chance of hail!
 that would translate to , setting sun on its entry turn, with the next weather condition after sun to be hail.
 and it work that way each time before it changes the weather.
 for that i'd need to roll 2 random rolls at once, and store the second value to be stored and passed/used in the end turn
 (preferabbly after previous weather's dmg effects) to switch to next weather

 could use a timer here, so weather changes about every 2 turns, it doesn't have a lot of staying power so can't stick around for a longer duration
 so still have a switch in effect, and end turn effect, but  roll 2 timers at once, setup ewram value to store weather or a special status?
  specialstatus.forcasted weather? = to weather condition than I guess pass to forecasted weather and use it for weather argument in end turn function
  after 2 turn timer runs down,  and then set timer to 2 again and roll random value for forcasted weather

  don't exclude being able to roll the same weather twice, if that happens, just reset the duration of weather
   think make a separate message for when that happes, instead of 2 weather conditions say castform predicts its gonna be (sunny/rainy/hailing) for a long while!

   also think will change castform to normal ghost to make easier to switch in, and remove its ghost type when it transforms
   so use set_battle_type2 macro -done

   -wait that makes less sense than it just keeping the ghost part of  its typing, normal type boosts its dmg,
   //but thematically ghost is nicer, forecast is also a play on casper the friendly ghost
   -plus i undid the joat stacking, so there isn't really any benefit
   -well no I can keep stab no matter what form I'm in so that's much better.
   //think also make castform imune to the weather dmg drops, pretty much out of necessity, since forecast is changing weather
   //will link to forecast not castform, just for sake of strategizing, hmm or maybe species instead? yeah ability - done immune to all weather based dmg drops
   -chage make castform immune to weather, forecast just allows it to set it/predict it

   -extra plan make holding weather stones, decide what weather gets set, so instead of extending duration
   //it'll double predict the same weather essentially doubling normal duration, and since idea is that its not summoning weather
   //castform would be only other mon that uses weather timer, would make castform THE weather setter, but that's fine as its not op

   - done fixed issues with 1st version of forecast that caused freezes, as well as healing abilities like icebody rain dish that had the wrong script ending
   redid forecast with new setup in mind works perfectly so far.
   custom strings are still to do and further testing
   redid cherrim now a grass fire type when blooming
   -changed starters and flag renames also attempted fixing some issues with calculatebasedamage function, still in progress
   seems gbattlemovedamage doesn't work, the function only takes gbattlemovepower and damage as damage argumentes
   //so replace w damage, or move arguments that involve gbattlemovedamage to damagecalc script
   but if use dmg would need to include things in both physical and special side of function, unless I can consolidate it
   and just make it jump to physical special at end?

   checked dmg formula and base repo, looks like original game used stat incrases in place of gbattlemovedamage
   the way damage formula works its about equivalent, doubling relevant attacker stat or cutting it,
   would be equivalent to doubling or halving total damage

   for damage nullifycation think I would need to make attack stat 0, ?

   ok could make macro that returns attack or special attack stat based on if physical special
   should be able to allow me put weather effects in a single place before physical special logic
   and have it filter down properly into either  can't use for everything as some effects should be 
   explicitly one and not the other

   //endure still doesn't work, found summary screen works again, changed one thing idk fi tthat was the main issue
   or if it was forecast / identified teh issue, its something to do with swapping,
   it replaces the data for whatever mon you swap places with, everyone else is fine.
   //its just what happens when you swap places

   -fixed it, realized battlemons actually had a personality value I could use this entire time,
   replaced with that and everything works perfect, was also able to fix weather ball display

   another argument for making macro, things like explosion, work off effect but early gen is physical
   while later explosion likes are special, while still using effect explosion (except mind blown?)
   //so the defense cut wouldn't be appropriate, if it read the approriate split
   and then returned the correct stat (offense or defense stat macro for each)

   macro use terary operator take operator and value want to use
   OffensiveModifer(value){ if (usesDefStat) ? attack = (value * attack) / 100; : spAttack = (value * spAttack) / 100;}
   //great as done this can be used as both a multiplier and a cut
   OffensiveModifer(200)

   DefenseModifer(value){ if (usesDefStat) ? defense = (value * defense) / 100; : spDefense = (value * spDefense) / 100;}
    couldn't figure out ternaryu operator so just did normal if else macro, works perfectly

   seems to work, also finished adjusted calculatebasedamage, also swapped hidden power
   to use the changes  removed fairy type from mime,

   the modifiers don't seem to work when used with an else if conditional but luckily I never needed to

   also of note, the wild_encounters.json holds data for both version of game, fire red & leaf green
   to save space consolidate those things eventually so whatever version people build they get same encounters

   take encounters out fo altering cave and give standard locations,  
   add version exclusive mon as said above,
   and also some gen 2 mon are just not in the game these include:
   Snubbull/Granbull, Jynx, Girafarig, Mr. Mime, Chinchou, Farfetch'd,
   Lickitung, & Corsola


  -putting here cuz can't find pc note rn
  but change pc access in overworld to not allow putting mon in pc that are fainted, to avoid trivializing the game


 questioning whether, I should really make joat stack with stab?  its a strong effect and makes normal typing desirable as a boost
 but on the other hand why would you  ever use non stab moves, and the entire point is to capitalize on their flexibility

 theif/steal STILL not working right, tried steal item from pickup mon, for some reason stole it twice,
 so it didn't remove the item

 -confusion dmg not working properly, I set it back to pound rather than current move but it still seems to be
 applying move effects on self hit as if using that move, attempted use gchosen move rather tan gcurrent move for power override
 //as its already overriding the used move

  -issue with move display for last mon in party, instaed its showing data for first mon in party.
  or its showign the moevs but for the last mon, said thata because hidden power changed from  what it was on the first slot mon
  -but its readnig teh first mons moves  think has to do with GetMonMoveBySlotId
  //was able to reproduce happens when mon is in first slot dies and then has to switch with mon in party to continue battle.
  //think it doesn't clear its data properly from first slot? so treat it as if they are still there or soemthing? - fixed
  -missed replacing instances of gplayer party w battleindex

  -but based on type for hidden power its reading the mons ivs etc. the correct mon data, but is populating with the wrong moves?
 

//wanted to add small boost to this for joat inclusvive to stab but couldn't do, it had stronger effect on not effective than super
                //so anything added here would just disincentive using coverage/non stab moves

        //on the other hand keeping it inclusive could work/be fine as my meta would already be more focused on the mon stats/stab typing etc. than super effective coverage moves
        //so it'd be played more like have a solid stab move, have 2 or so status moves, and a coverage move (that possibly has its own secondary effect/debuff)
        //if it was inclusive it'd already suit that type of setup, it'd make them even more suited for that format, the stab move woudl be even stronger
        //and their coverage move would also be more useful than on non-normal mon.
        //and that also highlights the strength of your type, as being more linked to moves of that type  
        //the mileage would be limited to how many resist you.  but that's more a buff to those already strong types than normal...
        //and I cant boost joat while keeping it exclusive as then it'd just be the arceus buff
        //ok will keep it as it currently is, but to get the most of this will have to greatly tweak movesets so normal types
        //actually have the type options to be THE coverage warriors try to keep things make sense, they get most coverage
        //but not somehting that should be super against their alternate typing? like normal/flying not getting an ice/electric move?
        //check gen 4 tutor moveset for first example of coverage moves to learn, from bulbapedia (as that gen seems to have most variety in movesets)
        /after that check for moves based on characterstics of mon, i.e things they should be able to do , like how heatwave and ominous wind make sense for pidgey line
        as they are wind related  same for twister
        //so that leaves wind moves, wing moves, talon/claw moves slashing moves and beak/horn moves I think I can add as well
        and again from their exclude anything its non normal type would be weak too

        with grouned change essentially giving many more mon levitate, grounds offensive power is weakened
        I think I shoudl make a similar effect to joat for them, since grond and rock are close to same thing
        would give ground mon psuedo stab on rock moves one way rock doesnt get it for ground moves.
        same values as joat  so if they aren't losing out on damage by using a rock smack down to knock them down.
        need make more groud moves that can knock down opponents

        will use else if, so will be separate from stab and joat, so groudn rock mon won't be getting an extra boost
        it'l essentially be a groud mon using a rock move that isn't a rock type and not a normal type

        after learnset redux
        redo move set for wild mon/trainer mon ensure they have a damaging move regardless of where they are in learnset
        loop set check if has move with power, if not move loop learnset up to lvl, and replace the last learned move with the last deleted power move
        with priority given to moves with stab

    ...I think my crit isn't working??,  I've been using high crit moves but never getting a single crit, it worked before...
    (made new ability block crit functnion to replace else if or logic, testing) - works crit is working again

    need update stat drop ai logic for new abilities that block stat drops did that for leaf gaurd to test,
    trainers dont use stat dropping moves if found the correct ability, but wilds still ignore ability which is fine I guess

    slightly tweaked ai logic to use split rather than type for phys special stuff as well,  not 100 on if it works but it should

    //since FrozenTurns uses gDisableStructs it'll be cleared when battle ends/new battle starts
    this works if still frozen at battle end so not frozen solid on next battle makes more sense, but you'll still be frozen, just suffer end turn dmg until healed

    //potentially use moonlight, move animation and day/night shift for battle to make lunar weather condition
    //that boosts fairy sp def or fairy move dmg, then setup field move w sunny day to  auto shift 
    //day night schedule will be an ow triggering move, like using strength or fly
    //so think rather than an instant flip ship should greatly speed of time progression
    //so dns would shift each minute from current blend/ until it reaches the target time frame and then return to 
    //normal progression  i.e use moon dance, during afternoon, so each minute shift to  evening twilight to night
    //for opposite using sunny day from their would shift, from night, to twilight, to day.

 tweak for oak ranch/pc exp idea let it activate after the bill event
 after rescue him, add new event where he introduces himself as owner of pc, explains what pc is
 transfer device, rather than a storage device, can store items but not living things obviously.

 - changed, just put script there to bring attention to it
 
 but he's sure professor oak wouldn't mind taking care of them for a bit.
 so have him and player walk over to pc talk with oak, have him say he takes care of them at  his ranch
 and he'll take good care of them and let them out to get some exercise ( potentially explain they gain exp here or just let it be a surprise)

 set flag, after this event, so all mon in pc now start gaining exp. will need add to new game flag clear, idk may do with var? 
 either works i think.   from there continue with default script where he gives ss ane ticket etc.
  
  "That takes care of that, ... why do I feel like I'm forgeting something... Oh!" 

  so fire red has early day care but is only one that only has capacity for one mon,
  effectively locking breeding to end game as the only day care with space is on the Sevii Islands...

  so change that make route 5 day care have space for 2, and be able to do breeding logic.
  along with change to not overwrite moves.   and then boost up sevii island day care to have 6 spaces
  so you can breed 3 pairs.

  -change plan for breeding, instead of special table, use 
  nvm think I will need table, idea is first species is female mon or ditto,
  if species is ditto, read species of father species as female species argument,
  so check for breed method, either normal, which would have same species,
  or check type if type matches that of alt form, then get alt form mon
  or if mother species is holding an item that will set which form to create if possible,
  i.e galar escence  alola escense etc.

  breeding mon to use would still be worth doing becuase of rematch system, so you could go through gym challenge with different teams,
  and add them to different teams for later.

  -scaling plan number of badges + average level of team, first pass check for number of badges, if you already have the badge for said gym/
  check average team level, so use more complex team than first time, but level lowered to accomodate

  the only trainers I really care about scaling, are for scaling upwards, i.e if your team level is hiher than their level
  and for early trainers to get better teams based on your numer of badges

  can group trainers using trainer id, and their association with routes i.e before gym 1
  before gym 2 etc.

  -setup funciton for evolving last mon in party and for setting party to final evo, using functions made in field_specials.c for evolving mon

  //make new area sevii island to get all gen starters, rare safari zone, mon will be higher level but all starter form
  change because remove soble from starter choice, still hate that thing, but people will want it, so it'll be available end game

  In FireRed and LeafGreen, the Sevii Islands are accessible from the Vermilion City harbor via a system of boats called the Seagallop Ferries.
   To be able to access One, Two, and Three Islands, one needs a Tri-Pass, received from Celio after defeating Blaine on Cinnabar Island.
    To be able to access Four, Five, Six, and Seven Islands, one needs a Rainbow Pass,
     received from Celio in One Island, after entering the Hall of Fame and obtaining the National Pokédex.
      To be able to access Navel Rock, one needs a MysticTicket, and to be able to access Birth Island, one needs an AuroraTicket
      both of which can be obtained promotionally with Mystery Gift.

    have Celio give mysticTicket & AuroraTicket when he gives rainbox pass
  
  ok think best place to do that is on 2 island, accessible before pokemon league, also the place
  where you get the elemental hyper beams for the gen starters

  It has the game corner, which I've removed all teh wifi games, so can use that to instead be extra safari zone,
  think what will do is have a place you can walk through in the back, w teleport soud,
  what you do is select the zone you want, Starter zone,  Rare encouter zone, etc.
  and then you're player will do walk script, into the new area,  a different biom based on what you selected in the menu

  -add little easter egg, for first time encountering lace,  welcome to the 2 islane safari extravaganza
  we used to be a game corner but no one ever used it so...  after message will set flag that yuo encounter 2 island safari man
  so it'll default to basic script from then on.

  makes mapping easier as well, as I can just have it teleport to whatever I want,so don't need to use the same map assets for each

  change game logic so you can have  0 mon in party, if you are indoors, so you can unload all 6 into daycare.
  but then just have a block when you try to exit (close pc) and use oak start text you can't go outside without pokemon/its dangerous etc.

 since expanded move descriptions will have to expand tm case move description window, to fit the 2 extra lines
 remove one line from tm case scroll and bring graphic/values up to match

 also setup new tm case as separate instance from base tm case, so can use default one for selling tms, 
  - done, still need seutp so can use icons to select mon to use/give tms to

  //pick up seems to have glitc, not properlu clearing consumable items? either that
  or I just don't have berry juice setup right, it healed twice because it wasn't removed

  but after second heal it then read as consumed so pickup was able to apply new item - think fixed

  //didn't realize items in gen 3 didn't use the actual icon sprite, and instead use a general icon symbol
  //would like to change to icon sprite shuold be possible since can be used for knock off?



  also need that for eviolite changes to make sense

  major glitches leech seed - causes bad egg glitch very bad
  bind glitch seems to swap party data and other strange effects  not game breaking?
  wonder guard glitch, swaps party data and faints attacker if attacks themself,  very bad
  *notes -
  poison worsening doesn't seem to be working? hard to tell as only poison effect available is 10%
  //change poison sting to 100% rework script/logic and retry - fixed

  //for berries like pamtre berry that's only use seems to be berry powder
  in ceruleun berry crush/powder man instead of crushing these berries have him 
  use them to make the medicines like revival powder etc. or the herbs

  falseswipegaming change slow start give flag to make sure it doesn't retrigger
  -done think

  //issue with poison setting when on mon that cant be poisoned i.e poison on poison poison type - priority
  only happens on instance when it would actually set poison so issue must be setmoveefect function

  ok weird thing changed effect chance, it only happens when its 0, i.e set to certain, but doesn't happen at 100 for some reason??
    -fixed problem was how I setup certain effect in seteffectwithchance

    -need fix multitask setup works for fury cut but not multitask for some reason -fixed

 //broken leech seed on top of target poison/toxic breaks game..  force switch out weird stuff - fixed

  attempt set caps for box exp, to prevent over leveling, think limit to badge should just be a matter of changing condition, and swapping
  the exp gain logic used, think use base function (loweresst level) divided by 2, so still gain just much slower

 BS_AttacksThisTurn use to repolace normal script logic for attacking this turn

 //issue with grounding effets, its setting them even if move doesn't land?? attempted rock throw, but got paralzed
 but the enemy grounded message still played, and they got grounded

 didnt' realize bad dreams didn't heal?, and can't add healing to bad dreams withuot making darkrai broken

 potentially change magician to be  swap held item with enemy, if holding an item, store original item,
 so item doesn't swap back if attack target again,
 gives it a cool niche, -set base effect still need polish and make script for text activation -did, setup a base 1st attempt 
 gave magician its own description so not just sharing pickpocket

 //also fixed issue with thief, issue was pickup and restore items

 attempted setup for uxie ability, need test custom abilities for 3 elves
 -don't forget plan to add onto forwarn/anticipation function logic  stuff for toxic etc.

 still need setup brick break correctly - all thats left is the logic for bs if enemy has a screen up

 for party menu status icons, don't update dispayed icon if something already set i.e only if staus1 = 0 should you set/upadte icon
 don't display multi icons in party menu only show it in summary screen, that way can display lvl in party menu at all times.
 -//thiknk need to move status icon on rigth side over slightly, to avoid issue with lvl 100s - fixed

 for setting up omnipotent aide use HEALING_EFFECT constant, compare currenet move effect to it, and pass heal to partner if i have one
 // use is double battle  and is single battlem, if single battle make the effects fail, effect should still be applied as normal for the move
 //but the heal would just be passed to my partner, ex.  fraejta use rest, I still go to sleep, but my partner's hp is healed to max instead of mine
 //if heal is all done within script, think may just be a matter of changing bs_attacker to partner. if single battle or no alive parnter in a double.
 //just need to skip scripts for hp and hp bar update

 for fixing starter select think I can use  CalcTypeEffectivenessMultiplier and replace movetype arguemnt with the selected mons type 1...I think that works?
 or I check both, so check type 1 or type 2 is super or resisted
 ok so check fi type 1 or type 2 is super (>= 1)  then else if type 1 or type 2 is resisted (<= 1)
 think will check final evo, as target  exclude eevee from the logic

 if pass checks set species to value, if fails at any point reroll rival starter
 revised first condition is if rival starter not eevee, than do logic above
 //function name "should reroll/reset rival starter"

 put in another function, if that is true, reset and do random again think do for looop with if should reset is true
 -did this appears to work

 
 fixed intro trainer select text
 ...using constrict on wondergaurd shedinja breaks game...causes freeze   going over changes I realized - think fixed, missed a part of status stuff (double check)
*/

goto MYSTERY_GIFT_FLAGS //list of flags used for mystery gift events, for non legendary events can make give aways in game some how

goto COMPARISON_FILE  //file added for keeping track of things to port to this new repo to update to previous progress

goto CHECK_THIS //something potentially relevant for future multi battle/triple etc.

goto BOX_EXP_GAIN //setup box exp gain w help from kurausukuun and shiiny  oak ranch

goto HIDDENPOWER_CALC //changes made to hidden power dmg calc in bs commands c

goto BATTLE_MOVE_SWAP_LOGIC //use this for changes to prevent seeing the move length bug, prevent moves of certain length from being put/moved
//into a slot that isn't slot 2 or 4  limit is 13 chars

goto MON_TINT_LOGIC //tm_case.c stuff ported for new tm cacse that think can use for dexnav idea

goto BATTLE_START_VALUES //battle_main.c where mon values are set i.e ability typing etc. before battle start

//logic for the actual messages for oak in first battle, can setup extra messages for move learn here
//double exp gain for gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE  that way guarantee level up
//then afer level up go to sum screen move info page do what I want and exit back to battle for end stuff
goto OAK_MESSAGES 
goto OAK_OPEN_PARY_MENU //functnio for party menu stuff opening stuff etc....

goto BEAT_UP_LOGIC //bs commands file need adjust to work correctly for party based psuedo stab

goto AI_TYPE_DMG_PRECALC //battle_ai_switch_items seems to be for ai to read type chart and adjust calculated dmg? but theres also ai logic in bs commands?

goto BASESTATS_TO_BATTLEMONS_CONVERSION //battle_script_commands.c place where basestats types are transferred to battlemons struct for battle, done on switchin
goto POKEMON_TO_BATTLEMON  //pokemon.c other stuff relevant blah blah

goto DEPOSIT_TO_PCLOGIC //in pokemon.c covers box position, and how it reads space in the box
goto OTHER_BOX_LOGIC    //deals with moving mon and moving item logic
goto TRAINER_APPROACH_LOGIC //use for setup bad onion item effect, trainer repellent, also use for stench ability
goto TRAINER_SEE_SETUP //base values that go into trainer approach, for setting up the battle itself
/* 
* setup pokenav, show potential area encounters but want mon to be greyed out until you've seen them.
* so just see a silloette- I just don't like the existing effects that show you exactly what are in the area,
* so people decide from the getgo to just skip certain encounters, my way you can tell if you've found all the encounters
* and finding out who's around is more incentive to continue searching/exploring.
* could either use mon sillhoute or a non specific pokemon identifier i.e an icon to denote a pokemon
* that doesn't represent any specific one. potentially the old gen 1 pngs?
* 
* bad onion b.o trainer repellent figure logic think it would temporarily set trainer view of every trainer on
* current map/map section to 0, so its talk to fight,  like repel long as timer isn't 0- DONE
* 
* ok was actually really easy to setup, mostly done, also added to stench, the only thing left to do is setup
* the eventscripts for it, i.e the text, for reapplying the trainer repellent.   in UpdateBadOnionCounter
* 
* tweak field moves, since adding item use selection to summary menu.
* will keep cut and fly as field moves, and softboiled review list and think to remove others.
* as they work with metatile anyway.  and change sweet scent to an keyitem.
* that way can set to select and do quick encounters. -
* 
* make game run smoother, i.e faster base text, move animations, battle text
* movement speed as well, want to move twice as far, without needing to 
* change the actual walking animation. and make running slightly faster     
* pretty much optimizing things so speed up isnt so necessary,

karasukun mentioned the game DOES have different durations for fade in fade out effects
so one thing I can quickly do is speed those up, if base speed is 60fps my game runs on emulator at around 1k fps and that makes fade instantaneous
also speed that mon bounce in game I like where it is on 1k fps would want that to be close to base speed,
and slow it down to where it is normally when they get down to red hp.
but fwant to keep hp box buonce about where it is normally

I think base game is 30fps 120fps is perfect for character bounce so possibly 4x, 
think then drop down to 90fps
30fps for red health
think I'd like 120fps or 4x for full health, 90or 3x for above 50,  
60 fps 2x in yellow I think
30 fps 1x at red
120fps is also nice for some fadeins

ok checked with audio I now know 60 fps is normal speed

battle animation are better at 90fps so would need divide normal duration by 2/3rd to get a 50% increase

the pokemon bounce/shake in summary screen are perfect at 60fps, and it already slows down with lowered hp,
rate is good, potentially just copy  the rate for that for mon bounce in battle

* but not so fast the game loses the chill vibe -

side note, I think I would like to add a repel pouch hmm berry pouch is a key item isn't it? 
I could set it up like that, either a bag pouch or a key item that opens in to a list just for that category of items
* 
* redo disobedience mechanics to work on player mon, just for the sake of new game plus, as the point is to  make the game like new again
* and allow you to go through the trials with a different team.
* since I don't want to ruin player choice/fun, I will only make this apply in new game plus mode
* so use newgame+ flag to check if mon should be disobediant 
* 
* [keep track of  flags not to be reset by newgame+
* 
* find plans for new game + mode I think plan was you'd be sent back with all your items money, etc.
* but mon in your party would be reset to lvl 1. (keeping evs ivs moves friendship etc
* think change encounter data to lvl 1 met fateful encounter text)
* also reevaluate benefit of new game + as original idea as makign the game new again and having a way to get other starters...
* 
* hm actually think what I will do is set ALL mon to lvl 1, so you  can use anyone, but mon in box will auto level up based on pre-determined lvl caps so badges
* will set the mon in the box to a certain lvl, so you can just pick up whoever and go, without having to do levels on them
* that will be just for new game plus, since yuo keep evs and moves, think plan is set lvl to a few levels below average trainer/gym leader cap
*
* played OPAL effing amazing, incorporate the great qol stuff frome there, flame charge buff to raise speed, (oh it already does that lol)
* try to get meowth forms, setup exp share with icon on summary screen. [would make Cefireon ghost flying in my game]
* 
* -ALL THE ASSETS ARE INCLUDED WITH THE GAME ALL ICONS AND SPRITES SFAFWJAGRGARAGNSNIODNVNVDHFB
* 
* -checked can't use backgrounds as they're too large,  about 100x the size of typical gen 3 backgrounds/terrains
* -also their mon pics use 160 x 160 where base game uses 64 x 64, so would need to resize
* -64 is thankfully a flat percentage of 160, so percent based resize will make it fit perfectly. (hard part would prob be pallete conversion)
* 64 is 40% of 160.  so 160 reduce to 40% of full size and it'll fit perfectly
* 
* -base game terrain png is 64 x 88   opal terrain uses 512 x 288, hmm ok if I can resize potentially useful
* but I think I'll just take and resize mon pics only
* 
* Ok another thing to add from opal, ae capsules, items that boost IV's, rather than other stat items that boost evs- =SCRAPPED
* 
* -ok found mon data for opal I can put in learnsets  variant forms data etc in but for things like meowth
* where it has multiple variants only one data set is listed, so I hope/ assume stats are all the same but I don't have a learnset
* will assume identical moveset and just substitute in the type based move where you get it
* 
* [want to include opal forms/mon as an official region, far as my game is conscerned that is gen 9 its better than anything]
* [I'm treating that as its official] - like red is in the game anyway and it mentions kanto and oak and the pokedex
* -its only right to tie it all back in even if the story of opal takes place many decades after gen1, can consider 
* professor ebon/ebono to be a genenration or 2 younger than red, maybe can say something like he took 
* a pilgrimage in his youth as a young professor to kanto and worked with professor oak
* then again black don't crack, and he calls himself grandfatherly, so could possibly have him be around the same age
* maybe make a cameo as someone touring to learn to be a professor and furthr his knowledge of pokemon rather than a league champion]
* 
* plus item use text on summary rather than just give/take, to goto bag menu/medicine  bag select how many to use from there
* make stat boosting faster, also copy some of their item cost changes.
* copy logic from tossing items, calls same box.
* just change to "use how many?"
* make item use work with a loop, (keep in mind item use graphic need to make sure that only triggers once, per "use"
* change item use logic to use a loop,  value for "used" and quantity is "quantity selected"
* "used = 0, increment long as used is less than quantity selected"
* then need to filter use items that can be used in multi use
* i.e only healing and stat boosting items and pp ups.  not status cure items

for licquid oozwe need special logic for ghost change to absorb nmoves\

didn't work how I thought

change needed is just don't swap hp drain for ghost instead 
just add the max hp damage to gbattlemovedamage and leave  the negating swap to liquid ooze logic
while I was at it, redid ghost absorb setup moved ghost drain to bigroot formula 
setup like emerald where its in every healing script
redid strength sap bs script as well, as it seemed unnecessarily bloated

some abilities are only bad because they lack utility, they activate omce and  then you get no
use out of them.
I thinjk rather than adding effects thet can be fixed ht making a new
c=abilitty categiryt amd puttomg them there,

Idea, same as contact abilities are broken down imto
activation either attacker comtacting opponent or being targettted
switch in shoukd do tje same

make a category of abilities for oppomemt switch in (look at spikes)
and add existing ones there  things like frisk, which checks items,
or things like trace, 

think cam also look at setmoveffect logic for affectsuser for target swapping

NEW BIG IDEA
*with what I just learned about legends arceus came up with new idea
make berry incense using the berries, it'll be inspired by the prebattle nature checking
that was in legends arceus where they used the flavor of the berry to show which mon had what nature
since I know now the berry flavors align with the stats boosted by nature
I can set this up

Idea is, key item berry incense (name pending) use a berry in the item
it will create an aura/aroma around the player  setup a timer for the effect
will work similar to repel counter.

text will be "A "flavor" aroma wafts through the air"  
pretty much use sweet scent battle message but replace "sweet" with the flavor of 
whatever berry was used, for berries that have multiple flavors 
it'll display both/all ex. spicy and sweet  or spicy yet sweet aroma
can make multiple strings for if berry has more than one flavor

then the effect you get for consuming the berry in this way
is that mon you spawn will be GUARANTEED to have the a nature corresponding to the stat boost.
meaning if you use a spicy berry you're guaranteed a mon with an attack boosting nature.
it won't auto be adamant but that still cuts down on rng
as well as gives a good reason to have /farm berries

ok fire red doesn't have the display for berry flavor will need port that to firered sigh
//as well as berry trees

make function that alings with gBerryFlavorCompatibilityTable
read flavor of berry, and set nature to craete for mon based on that flavor

need figure out how to do that, as its not just random % 5
and one value for each nature

there are cases where flavor can overlap so you have 2 groups of naures 
or perhaps 3 even figure out later

//have this new item replace berry crush, and be given by old man in cerulean city
*/
goto BERRY_TO_NATURE_RELATION //pokemon.c logic for relating berry flavor to nature useful for ide

goto WILD_NATURE_SETTING //where nature is set for wild mon

goto STARTER_ULTIMATE_MOVE_SELECTION //function for setting who can learn frenzy plant etc
///need update with later mon starers

//note must find out why some bs macros in the .inc use 1f as a argument?

//and check this function for relevance Cmd_if_type_effectiveness

goto ITEM_ICON_SETTING //item_menu_icons.c
goto ITEM_ICONS_TABLE //the actual table plus notes
/*
 * setup new eviolite effect graphic swap here, compiles need test
 * 
 * all item icons are set with this function
 * 
 * //think raise boost 1.5x isn't really enough to be worth not evolving,
 * or even keep up with what stats would be at evolution
 * hmm or so I thought? but paras base 55 defense with evolving to parasect base 80 def
 * my eviolite def was higher than my evolved defense??
 * pre-evo def was 70 w eviolite,  post evo it was just 61
 * but my hp is much higher so overall I'm still bulkier post evo. hmm. I thinkI should still boost it up 2 points
 * keep an eye on consider may be too strong for some good mon but eh pve doesnt matter as much
 * 
 * changed affect, to only work on mon that aren't already good, i.e below a certain bst, using chansey as best example will use bst 450 as cap
 * with this value it won't affect mon already "good" will nolonger work for chansey
 * 
 * //now way for player to see their bst unles i make that, but no reason to have it other than for this
    //so instead plan to indicate if eviolite is working on mon in question by a palette affect
    //make greyed out palette version, or more simply make grey version of icon and add that without palette data so it takes the value for that and makes palette from that
    //then just have function that checks if eviolite could activate and if false, tell it to use the other graphic icon on the mon.
    //would confuse the player but they would be able to intuite that something is wrong and the item just wouldn't work for the mon in question.
    //activation condition would be exactly what have above, so replace those checks with full function  - ok done that
    //last thing is need to create the other version
 * 
 * 
*/


 goto ITEM_USE
/* 
* low cost of ev boost items.  1k or 2k per rebalance other things I like that cost economy balance
* get incubator so can hatch eggs easily while on the go, would greatly speed up breeding as well
* include flame body/fire ability in party boosts speed of all  
* rename mon and relearn moves from a npc/attendant in every pokemon center
* plan to put 2nd nurse attendant in front of counter by left corner (but not directly infront of flower)
*  to serve this purpose -
* 
* ok remembered I also wanted to setup move learn better, a lot of time you see a move 
* and it looks cool but you don't remember your mons stats, so you can't make a full informed decision
* so change the move learn screen where you can move left and right to slide out
* and it'll slide you to the main summary page that shows your mon info/ i.e stats & ability data etc.
* (believe need to add this in normal summary screen and evolution file?
* same as how had setup movelearn confirmation text)
* 
* ok for starter fight, add oak text in menu for when you level up and learn your first move,
* telling the player about the menu change.
* 
* hmm could possibly do with a flag check? first move learn flag, 
* on summary screen state of move learn if flag isn't already set,
* run the oak script just like when in battle for first time
* "OAK:What's this?!\n  {pokemon name} is learning a new move?\pSpectacular! Now if at any time during move selection\n
* "you want some help making with your decision. \pPress Left on the d-pad to see your stat info/data.\nAnd simple press Right to return here."
* and then set the flag
* 
* done that way it'll always get seen, regardless of if you win the rival fight or for some reason don't level your starter first
* check battle_controller_oak for text
* 
* or can just have a scripp to run, similar to how oak works in overworld
* so soon as your starter is leveling up and learning a move for the first time.
* oak text would pop up to inform you of the menu/dialogue changes
* 
* -further note, since I have so many moves, I will actually need to know the move split, would be hard to keep track of,
* on top of my changes. so add dialogue/functionality where when you have a move selected to display its description.
* Pressing Ctrl, would clear the move description and instead display the move split...
* Split: Physical.    
* Split: Special.
* Split: Status.
* 
* If you press Ctrl again, it should  go back to displayig move descriptions
* You should be able to move up and down from within the Move-Split page so it'll populate the split for each move as you go.
* 
* Pressing B, from there should close it as normal, and clear state, so when you press A on move again it displays the move description.
* 
* need to update name length to 12 base, so will need to move health bar - why do I need to move the halthbar?
* - can just move up sprite and shift name and lvl in summary scrn   
* -current plan put mon sprite, on pokeball, move species name to place of lvl, down and flush to the left.
* keep gender symbol where it is, or right align it, then move lvl symbol to top corner.
* 
* looks like I don't even have to move all of them, only need to move the 1st slot mon,
* and the 2nd for the doubles battle screen as well.
* Also the rest of the party mon icons already sit on the pokeball so it wouldnt look strange.
* 
* worked out have new party menu layout, everything fits, without moving hp bar
* idea widen status icon field  or add multiple status coord figures  to array
* should be able to fit multiple icons for multi status setup,
* just need to reduce total num possible concurrent status
* make some mutually exclusive(?)  like freeze and burn  relation
* (would stop using status1 any, I think instead I can use conditional (!(gBattleMons[gEffectBattler].status1)) || status1 != opposing status
* woul be in set move effect, rathr than setting status in that case it would just remove the opposing status
* plan to put in CanBeStatused functions already done for CanBePoisoned)
* 
* including my custom fairy status spirit lock  (which should be mix of para & burn) - change to special drop, or make paralysis like lower odds, 
* theres 7 effects but with exclusivity only  5 would be  active at once  - potentially change name to spellbound? - attempt use existing EE move sprites for status anim
* slp para burn psn/toxic & sprt                        --thinking some kind of swirl effct that rises up?
* thats still a bit much so i plan to link sleep & spirit lock
* like freeze &  burn are linked.  as sp lk is meant to be a mental impairment
* attempting to put to sleep makes sense as a curative
* so you'd get one turn to avoid sleep if you had spirit lock
* and spirit lock attempting to be set would disturb the sleep
* and wake them up.
*
* with further consideatino paralysis and spirit lock both havin gindividual stun chance wuold be far too much
*  so come up with bette effect for spirit lock thta doesn't include stun
*
* hmm what about instead fo not being able to attack they'll ignore direction?
* just like locked move, player won't be able to select a move,
* yeah I like that, say they panicked, either  redo last move or pick random move.
* think more impactful to pick random but idk if that would be too much randomness
*
* also considering change to only being able to set 2 statuses, 
* 
* that leavs with the more manageable 4 status to display on party menu.
* may not be able to do/fit, could instad atteampt same thing as status in battle idea,
* make it loop through the status set and just change the icon each time the mon bounces twice?
* potentially use  release Mon animation? so it transitino clean.
* //end turn name scripts need to use b_atk_name,  src_active name or anything else causes issues
* //buffed sleep, kept long sleep duration, balanced by giving off turn healing
* 
* Last thing before break is setup battle health box, need finish species name expansion, w pokedex box outline-
* 
* need give all dark type mon sucker punch in learnset, if a mon evolves into a dark type,  make sucker punch an evo move
* would be a problem for fairy if these moves are too far spread so backstab will be dark exclusive
* sucker punch will only be for dark fighting and (maybe) ghost types.
* can also readjust night slash think make dark ghost only? - check who learns it
* 
* Ok night slash is VERY spread out, proliferated I can bring that in to just dark normal maybe, (since fairy beats normal and normal is flexible)
* potentially ghost type as well, (but they also have shadow claw) but I don't want ghost to be for dark, what  water types were for ice...
* 
* That way this allows dark types avoid that issue,  that ice types had of irrelevance as other mon got ethe same access to the best moves of said type
* without having to deal/engage with the weaknesses.
* 
* Give shuckle better moves, it stats are fine, it just learn horrible moves.
* 
* still need to add zen mode type moves to normal learnset for darmanitan forms
* 
* Also need buff darmanitan, its type changes with zen mode, but it doesn't naturally learn any moves of that type -_-
* on top of that its main offensive stat swaps from physical to special, so when it goes into zen mode, all of its native moves
* just do no damgage how did they fuck this up so badly??
* ok this is mostly a problem for base darmanitan, the galaraian form at least stays a physical attacker
* 
* fix by splitting zenmode for the two forms into different abilities, keep zenmode for base.
* make galarian darmanitan zen awakening   make zen awakening work like schooling, where change into form on switchin,
* long as hp above 25%
* 
* for zenmode, make it swap when hp drops below 50%  also buff hp to synergize.
* as it gets a major defense boost when transformed. - DONE 
* -didn't need to split abilities, formchange let me change  hp threshold, also made switchin-
* 
* 
* buffed ABILITY_GORILLA_TACTICS  buffs both offense stats - DONE
* 
* still working on updating move descriptions
* -was able to use replace to define all move descriptions need to put in table to assign to moves
* all that's left after that is combing over again for proper spacing.   place "\n"  every 3 words would do it
* remember can place 5 per description - DONE!
* 
* need tests if toxic works, and if poison worsened works
* 
* make command for general intimidate ability checks, to clean up  the intimidate bs script
* will work for target only, check general stat drop prevention abilities, substitute, and other abilities that were buffed to ignore intimdidate
* will not include specific stat ability prevention i.e  hyper cutter  big pecks  stuff like that - 
* -actualy I could put those checks, in a function too.  since its not erestrictd like battlescript is
* 
* buff anger point, activate on super effective move result as well as crit. as both are 2x dmg.    - DONE
* most mon that get it aren't likely to survive either way, so gives it some play.  since crits are so rare anyway.
* 
* buff stench, its a bad ability, purely because every mon that has it, is too slow to every activate it.
* either change its effect, to something like a 1/3rd chance for extra damgae proc via, enemy can't stand the smell. 1/8th max hp.
* or I setup a new status/functionality for stench where the flinch status isn't removed, because usually flinch status gets set by move effect
* and is cleared at move end.   would have to set it to a timer i.e timer to 1, so  they attack have a chance to set flinch,
* and the status isn't cleared until timer hits 0, which would be at end of next turn, so the target will flinch next turn.
* -or, dont make it linked to using a contact move at all, and just make it work like old neutralizing gas.
* just being on the field can cause flinch chance, but also for your teammate.  i.e "a foul stench is in the air"
* would be a much better actually potentially boost flinch chance from 10% as it has negative side now too?
* 
* way it would work, if stench ability on field and ability not stench, random % chance to set status flinch to battler
* code is simple, just a matter of finding where to put it to work, atk canceler doesn't seem to be the right place.
* atk canceler has clause for flinch status, I just need a place to set it, ok atk canceler unable to use move
* may be the right place, I just need to put it at the top?
* and set stench as a switch in 
* 
* want to sets up as a status, as there should be moves/abiities you can partner with that could remove the negative aspects for your side etc.
* -note doesn't need to be a status, I could do function based exclusions, again like neutralizing gas.
* 
* abilities that will block the flinch, effect will be oblivious, inner focus, and leaf gaurd (potentially more if they involve, flinch protection, or good smells)
* -sweet veil & aroma veil & flower veil
* -DONE just need double check ability exclusions work correctly. 
*  ok yeah it was wrong, and I've definitly used that  logic in multiple places
* need to search != (ability     and || ability  to fix all instances I"m able to find. -DONE all ability instances corrected
* 
* idea, plan to have Bad Onion, economy for avoiding trainer, but thought could also have stench mon have that effct if front of party as well.
* doesn't need to be a thing, but would be in line with wild repel logic, 
* remember bad onion idea is set trainer view to 0, so you could walk right in front of a trainer and they wouldn't battle you.
* You'd have to directly talk to them to trigger battle.
* 
* -note potentially tweak this logic so it doesn't work indoors, that way it doesn't affect battler guantlets for story
* or just make it so it doesn't work in gyms, making it not work indoors would affct caves, and also  it not being useful
* when you're going through a trainer guantlet would kinda make it pointless? - leave more for playerchoice is my motto
* 
* ok I'll leave it as it is, if players want to use it to skip guantlets missing out on exp that's up to them, 
* but I need to see how that would affect certain points of the game like say nugget bridge.
* 
* may need to eithr disable based on  route/location or make alternative scripts to account for it...
* 
* Ironically its the change they made in gen 9, but my version is better as its linked to player choice rather than a global thing.
* 
* attempted setting up two type move effects, tyepcalc logic done, need make custom twotype effect for splishysplash, as want to add paralyze chance to it.
* believe will add twotypeeffect to list of certain effects so the effect chance will be exclusively for whatever move effect I set.
* I think adding the para chance is simple as just making a new effect and having its battlescript start with setmoveeffect paralysis 
* then when done with logic can just go to battlescript hit.
* 
* new idea buffing haze back to gen1 standard  renaming inspired by literal translation of japanese name, to Black Fog -attempt shift palette for move make darker
* also make end turn animation for, 
* A mysterious black haze covers the field/ 
* -an inpennetrabe block fog covers the field  blocking field effects, status effects and resetting stat changes for all battlers for the duration/ 3 turns

is an equalizers resets stats,  back to normal
clears secondary status, and while doesn't remove status1
all secondary effects from primary status are disabled for duration of the fog
no end turn poison, freeze burn, atk cut from burn is removed,
speed cut from paralysis is removed and paralysis chance is 0
as an extra bonus no critical hits can be landed during fog

guts boost from status is also undone. actually could just do neutralizing gas disable all abilities?
that would prob be too much, just limit to status related stuff, to put everyone on even footing 

Generation I
Haze resets the stat stages of both active Pok�mon to 0 and removes the stat reductions due to burns and paralysis.
It also lifts the effects of Focus Energy and Dire Hit, Mist and Guard Spec.,
X Accuracy, Leech Seed, Disable, Reflect and Light Screen from both sides of the field. 
Additionally, Haze cures confusion and turns bad poison into regular poison for both active Pok�mon,
and also removes any non-volatile status condition from the opponent.   

 -don't need to remove leech seed/poison just stop endturn from activating
-for focus energy dire hit also don't need to remove just prevent crit during fog
-grounds all as well, idea being dark fog is inpenetrable & can't see to fly - block fly & sky drop?
-my version wont remove extranormal status effects just keep them frm taking effect for duration
-i.e if reflect/light screen was in effect the defense boost wouldn't work but the effect would still be up
-and counting down, so there's a chance you can get the effect back when "haze" fades
-for strength of effect make lower duration i.e 3 turns (3 full turns)
-blocks weather effects as well -(non permanent weather) actually nvm I'll block all weather (excluding wind based weather i.e mega ray)
*as its not good design to have some mechancis just have a counter locked to only a specific character.
* so it'll become a weather counter also, but balanced by the consideration of pros and cons from its use as its field wide
* think only primary status will remove will be sleep which is temp anyway, freeze  is already balanced now for duration 
* blocks stealth rock , weather block mostly done sleep removal done, crit block done mist block done, float block done, nvm undonig change to just cant use fly or skydrop
* put that logic in atk canclor w sleep - done
need do end turn block status2 removal and side status block
-weather done, battler end turn done added grouned back
-blocked all side status I planned to, aurora veil, reflect ligh screen future sight wish perish song mist & stealth rocks
-status2 done, believe function of effect is complete

just left is refinereies, extra text end tur animation - final decision keeping name haze

Haze does not remove any non-volatile status ailments that the user has,
does not change the generic Minimize graphic back to the Pok�mon's regular image,
and does not reset either Pok�mon's current type, moves, or species.

-  covers the field in a strange black fog, resetting stat changs for all battlers and blocking outside effects and status effects for the duration

will need block weather animations for end turn, replace with haze animation

do a check for  field status black fog
if (gFieldStatuses & STATUS_FIELD_BLACK_FOG) - well I'm setting this as normal effect goes through long as black fog not on field so...
if (!(gFieldStatuses & STATUS_FIELD_BLACK_FOG))   && !gFieldStatuses & STATUS_FIELD_BLACK_FOG

made function for simple paste   IsBlackFogNotOnField()     if (!IsBlackFogNotOnField())

beleive all effects to interupt are in battle_util.c & pokemon.c, if I block fly/sky drop would need to put in atk cancler as well

* eventually came up with a buff for stall gave it double move power, buff so high because it'll be extra punishing in doubles elsewise
* now to figure out who I shuold give this too, would exclude mon from trick room, so could give to slow bulky mon that do low dmg,
* or some mon with average stats to give them the ability to potentially do delayed one shots
* could even put on blissey  - unrelated note healing uses gbattlemovedamage make sure be careful when using that...-
* 
* ok gave new stall to a few mon unsure how useful it'll be, I'll leave it up to future users
* to decide who should have it
* 
* /also setup infestation as bug status can do with augment may need to set a fixed change in case move has odds I can't set to certain
        //15% prob good if I need to. -

        made attempt at setting argumentchance separate from normal effectchance need test
*  fixed infestation  stat drop, and sandtomb stat drop all trap statuses should be workign now
* with argument chance set -need test if working - can add status chance to all fire/fairy/electric/ice/poison type moves 
* would be in line with expectation every fire move can burn every electric move can paralyze etc. just have lower odds for weaker moves etc.
* min would be 5%
*
* changing infestation, setup as bug status but forgot would need to separate effects out from the trap.  
* so renamed move infestation to swarm, need to set it up as that's the trap, and it does end turn damage.
* but the defense drop is tied to infested status so swarm should set infestation status, and clear it when swarm ends
* 
* need add on to ability description of aviator, defeatist, and run away that they are able to switch out even if trapped etc. can always switch
* 
* idea from Jaan pokemoonchallenges repel should be easilly accessed through L button/ button press in overworld 
* instead of requirin to go through menus.
* I'm using help menu which is on L R so would potentially need tweak things
* 
* Also players setting game mode to L = A would cause issue potentially disable option
* Set Help menu to L OR R,  set Repel Script/Function to the Alternate button since I have multiple variants of repel i.e bad onion
* think what I will do is make repel bag slot, and pressing Button prompt in overworld would auto open bag to that slot without being able to move to others.
* B press would return to overworld but from there you select which repel you want to use, and it'd continue as normal.
* 
* I alreeady have the BW  use another repel script setup for both versions so after that its no problem.
* 
* 
* ok two_typed_move effect just uses normal hit battlescript by default, giving it its own effect, was just for logic in typecalc
* so it reads the type from both move and argument.
* 
* so now that I set twotye as a certain effect, in setmoveeffectchance all I need to do to add effects to those,
* is set the chance & filter by move in the hit battlescript, to jump to the battlescript that sets moveeffect 
* i.e I can use BattleScript_EffectParalyzeHit for splishysplash as it auto jumps back to hit...
* ok use two jumps, one jump in bs_hit, and then a second jump in the destination script, that will jump to
* hit from atk cancelor or something so I can skip the first jump! ok that should work.
* -DONE need test
* 
* lATS
* 
* make early event script to set all mon as caught seen
* loop through species and set all flags, and unlock national dex
* may also give a few mon with script, this is to check pokedex entries fit
* 
* -note removing kanto dex from game, doesn't make sense to have
* will need to update/remove every insance of IsNationalPokedexEnabled checks throughout
* and then change IsNationalPokedexEnabled so it always returns true.
* essentially unlocking nat dex from the start, soon as you get pokedex
* or can just put EnableNationalPokedex in script when you receive pokedex?
* 
* type chart fixed found issue with some added sprites noties chespin has transparanecy alpha chennel is corrputer somehow need check
* note from watching pchal on run bun thunder wave has 100 accuracy spec to electric types 
* could potentially do that? ...oh nvm I already buffed accuracy its 100 by default
* 
* select front sprites from emerald expansion have the wrong transparency use file
* sprite correction pallete take first color.pal in ubuntu syncer folder
* replace first color in image palette with first color in loaded pallete via graphicsgale
* 
* can't check all mon with starters script rather, give pokedex and set all mon as seen
* that way can just scroll to see which ones are broken.
* 
* -now type chart is fixed that leaves 3 issues, 
* 1.move descriptions  are misalligned they are pointing to the wrong move descriptrions
* 2.battles are broken, soon as rival battle starts game breaks - don't know if just rival battle 
* 3.can't deposit into pc.  confirmed items can't check if mon as well
* 
*
*  THOUGHT attempt change item use, allow for using multiple of the same item at once.
* from outside of battle. i.e use 5 oran berries,  to equal 1 super potion.
* the item use image would play 1 time, but it would apply the effects of the item 
* all at once. check how it works, if it shows exact hp recorvered or just displays text for hp recovered.
* would only be for hp recovery level up, stat items, and pp ups.
* 
* pick item, add quanity argument do it like in mart buying an item,
* hopefully can shift total quantity as you move amount you plan to use. may not need to/have any benefit in doing it that way
* other than preference.
* after confirm to use that quantity, only then go to party menu.
* think just loop through portion that actually uses item n number of times, where n is quantity - 1
* i.e if you use 3 rare candies will use item and then loop 2 times
* 
* anthroyd advice need to start keeping list of things I plan to use for the thread and what I plan
* to introduce explicitly in-game I want my new type chart to mostly be discoveredd in game,
* but just have them aware that things are diffeerent and some things will be a new experiencee
* 
* [note use trainer school for majority of introduction to changes, expand the inside area add more npcs 
* [with more school book reading events to get more information, setup event script at the door, character well get exclamation mark over head
* [and walk over to greet player. "Oh! hey Welcome, to the narative exposition school of Trainer Knowledge
* [I bet you're surpised by the size of this place, there's been a lot of changes in the region recently
* [and we've had to make some expansions to keep up.  The teacher's giving a quiz today so everyone is reviewing their notes
* [but if you have question feel free to ask, talking about the subjects will help them ingrain the material.]
* 
* npc stops and walks back to their corner, releases player. if you talk to them again, before quiz they repeat, if you can pass the quiz the teacher my just give you a prize
* I think prize should be 10 rare candies?   can be done at any time, so could make the quiz harder to not make it so easy to trivialize early game?
* 
* //decided to bring back the help menu for this too but just for reading the type chart that should be the only thing which would still save on space
//as it wouldn't have to store a million different contexts.
//make empty "o" circle symbol be the symbol for neutral to all.  which would be curse and sound type
//so open help menu should only be able to select "Type Matchup List
//and on the list for "Using the Type Matachup List" just add the text for pure neutral
* 
* need double check trap effects, make sure effect_trap setup
* works correctly for thunder_cage since I didn't even know
* that was part of the effect -
* progress -checked since it uses effect_trap battle script is already setting wrap effect
* still checking statu1 to see if need it for allowing traps to persist after switch
* it seems ugly, think just need to make a grip glaw exclusion -
*/
goto CLEARDATA_ON_FAINT //if ((gBattleMons[i].status2 & STATUS2_WRAPPED) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
goto CLEARDATA_ON_SWITCH    //search, for status2_wrapped & wrappedby  implement new trap checks where it makes 
goto OTHER_SWITCH_EFFECTS_1 //goes to jumpifcantswitch bs command, need to update with trap effects
/*
* all traps used statuswrap before and wrapped by, need to make new struct value trappedby
* and have it set for other trap statuses or make wrapped by set with other statuses too
* each one has its own timer, so it doesn't matter if I dont check  each individual status set/applied at the time
just need make wrapppedby work with new trap statuses adn then set that if holding grip claw staus doesn't get cleared on switch
as well as the effect of increasing trap duration
*/

//updated battle_ai from script to .c file based on emerald expansion, everythinig should be defined but still needs tweaking
//files are battle_ai_util & battle_ai_main

/* POKEMON CHANGES -
* Finish Ability_Defeatist setup need to finish setting up
* the cleanse effect, actually can just do what runnaway does
* then that would just leave trap effects to remove then do hp drop
* realize I can bypass that by using emergency exit effect, as that gaurantees switch/does force switch
* for simplicity sake will skip the hp drop I was planning to do if statused with traps or escape prevention
* -escape prevention done need to setup guaranteed switch ALLOWANCE DONE and need add to switch in effects 
* -Setup Done need test but DONE for now
* - think I may bring trap escape hp drop back, will just need to fix my implementation of  new trap effects
* 
* buff in a pinch abilities, activate soon as hp hits yellow i.e 50% - DONE
* 
* General repo update compare to griff red modern fire red search #ifdef BUGFIX
* and replace bad code with bugfixes don't know if it'll make a differnce or not though - DONE ?  yeah done
* 
* Update pokedex_screen.c and other pokedex files with new function renames - DONE
* 
* NEED upgrade pokedex entry graphic so can fit emerald style longer dex entries. - DONE
* 
* Re-capitalize ability names, decapitalization doesn't look good in fire red menus - DONE  
* 
* Buffed static & flame body to apply on hit and when attacking. DONE
* 
* Need setup mon with static w new in a pinch ability overcharge -
* 
* setup poison in a pinch ability based on mc from marriage toxin ABILITY_POISONED_LEGACY
* boosts poison dmg, and if would poison sets toxic instead, and starts damage at turn 3 damage i.e will do 3/16 rather than 1/16 or 1/8(normal poison) on first turn
* also if move has a chance to poison it guarantees the poison 
* right now is only on poipole/naganadel line as those are elseworld starters, and in a pinch is usually starter only
* 
* Further buff cupid arrow for luvdisc make it ignore gender check, as its the love pokemon and something further to make it more unique. DONE
* 
* BUFFED unown, learnset and new ability - DONE
* 
* new ability idea, ash blossoms yugioh name inspired, single turn switchin effect for a bug type maybe volcarona
* sets up STATUS2_POWDER  on enemy side, use flag check, if flag present at end turn remove status
* make sure its a different status but with same effect, so if mon used move powder, it doesn't remove that as well.
* or could just do a logic test if battler status not STATUS2_POWDER  set powder and ability flag, that way it can't remove an existing instence of the status
* purpose is give free switch in on fire types, for type usually weak to them - 
* powder was original signature move of vivillion   -giving to accelgor as its like a ninja (also try to change front sprite remove stupid puckered lip thing)
* 
*  also plan change grumpig front sprite, made dark type, give someting more sinister looking, saved template images
*  ...change cloyster shiny so looks more sus, making pearl pink
* think make shell brownish red?
*
* ...*Looks left & right* ... should I buff sturdy so it lets exploding mon survive on 1hp o.0
* yup I'm DOIN it!!!
* - I DID THE THING!!!!!!!!!!
* 
* while looking at buffing poison heal, for poison types came up with buff for muk etc. sticky hold
* rather than just make a copy of gooey and lowering speed on contact. 
* Set so may steal/destroy enemy's held item on contact with sticky hold mon instead i.e battler absorbed the enemy's stuck item - DONE
* do for give to garbador as well, who for some reason doesn't have when its a literal collection of absorbed trash-
* 
* give gumshoos move first impressions and facade as evo moves, leaning into trump pokemon idea - DONE
* 
* nother wave of buffs, delcatty buff, will need change its pokedex entry to fit, made part ghost, cats have 9 lives
* may say delcatty is cat that died and came back intending to live its life to the fullest of its desire. - STILL WORKING on
* maybe something like, "to make the trainer who went through so much to gain their love and trust happy, this pokemon denied death
* and ressurected itself into a new form, it will refuse to die as long as their loved one lives" - DONE
* .there we go that would lend itself to why it doesn't need to be a delcatty to breed.
* 
* while looking at entires saw torterra entry doesn't make sense, came up with idea for MEGA torterra that would make it make sense.
* give unique ability that makes it a 3 type mon. since its supposed to be an entire ecosystem 
* it should have all the elements necessary to sustain life.  grass rock and water
* 
* make its base type  grass/rock
* and its ability will set its type 3 to type water
* 
*would naturally make it very strong both offensively and defensively, hmm but with change to ice type chart
* water no longer resists ice, leaving it 4x, so will need to make ability also reist ice
* Ability Name Ideas-Pangea, Ecosystem - DONE also i madee it rock not ground, so its only 2x to ice, ability leaves it neutral
* NOTE-| add mega pokemon to dex entries  mega torterra will be the "Continent" pokemon
* 
* idea for mega snorlax, (form is that of laughing buddha) floating in meditation zen mon,  normal psychic
* evolved to psychic powers when it realized how much opportunity for gluttony it lost out on by being unable to eat while asleep
* it can use its psychic powers to control itself even when sleeping its also no longer slowed by its mass due to its emense psychic power
* it removes itself from the shackles of gravity by instead pushing its weight onto its surrounding area instead.
* abiltity gravity bomb/pressure spiritual pressure ro something, it sets gravity on opponents or maybe everyone
* and doubles their weight as well.
* 
* signature move gravity pulse or something an attack that deals damage based on snorlax's weight
* 
* may consider buff plus/minus ability with same affect as overcharge, but only when the partner is in a pinch -
* can lead to an interesting plan where players ev build them for bulk
* yeah that works as the ability activates when a mon with plus/minus is on the field, but 
* if I make that action only be for if using the opposite ability as your partner its a different synergy - DONE need test
* 
* 
* companion ability to nuisance, cuts dynamicbasepower of partner moves in half,
* in exchange for serene grace style heightned effect chance INCLUDING heighteeend crit chance/odds.
* possibly done by dirrectly moding critchance, or by setting high crit flag to moves if possible
* the point of high crit is, it'd give a chance to overcome the negative, crit would double damage
* so you do normal move damage. plan to use in doubles with nuisance, lets them use stronger moves
* kind of a opposite to serene grace, think can do like this  
* if (!(gBattleMoves[move].flags & FLAG_HIGH_CRIT))
* gBattleMoves[move].flags |= FLAG_HIGH_CRIT
* - DONE
* 
* 
* made one hit kos a bit more usable/workable works when up to 7 levels below target- DONE  -com0opletely reworked, now limit to 3 levels
* 
* 
* fix typhlosion line learnset curve, bring in line with charizard - DONE
* 
* NEED double check trap logic, may not need to make them status 1, to keep from being reset when mon switches
* occured to me its not a status1 thing becuse confusion persists if mon switches, so its prob just somehting in trap logic?
* either way, reset status stuff so status1 doesn't move-
* 
* for wormadam line, buff anticipation ability with disguise effects,
* it warns of a super effective or ohko move, and gets a chance once a battle to dodge one super effective move
* allows for a chance to stay in rather than having to switch because you know a move is coming.
* is part of switch in effects i'm trying to make reactive, so if you don't take a super-effective hit and beat enemy, move should check again-
* 
* do similar for ability forwarn, since it checks the enemy for a move, set it so if they are targetted with said move
* it will miss, something like their psychic powers let them avoid damage, 
* think of it like them predicting an attack specifically from that move -  effct done, working on special case logic (think can just reset switchindone, to make reactivate
* - just  reset gSpecialStatuses[battler].switchInAbilityDone to false - think that's done
* 
* ( can use telepathy logic  for these effects, its essentially telepathy but single use)
* can attempt include type component to check which move woulda actually do most damage to me, more than just power based
* yeah I think that's a necessity, otherwise could check a move that would have no effect on my type or I resist it.
* all I would need to do is check type and decrease/increase power by the multiplier  and if immune read power as 0
* put that as bottom line for the mov the last augmentation / actually no would have to go inside each case
* 
* think it may be too powerful for these abilities to reactivate when new enemy switches in
* idk maybe not psychic type is usually pretty frail so this gives them slightly safer switch in, 
* and more longevity
* - or could just make it on use for the invul, but next turn it will still inform of the most damaging move
* just do a check similar to intimidate where it changes a variables value when the effect triggers
* 
* 
* gDisableStructs[battler].isFirstTurn == 2  is logic for mon switchig in, can use for switchin reactivation condition
* 
* //buff willl make strong so need a counter, make intimidate*switchin* fail if status 1    -also added dark exclusion and a couple other ability exclusions as buffs for those i.e oblivious unaware etc.
        // or if confused, if confusion success is same oddds as confusion success attack,
        //set to do confusion battlescript on attacker, instead of  intimiate script if fails
        //i.e play twirly birds over mon (use play status animation do for all abilities canceled by status) to indicate why intimidate didnt go off.
        //edit intimidat logic for that instead of here.    *would get annoying so make instant text, and short animation
        //can make function that checks if ability can be activated due to status, return true false, than can just use an else statement, to make 
        //the ability clause jump to bs script for fail condition play status animation look for confusion first, then loop through status1 volatile status
        //in order to choose which one to display, (mostly done for  later plan to be able to multi status a targt)
        //"name with prefix, couldn't activate B_Buff1" where buffer is ability name
* 
* realize ability leaf gaurd sucks, but have no idea how to fix it, I cant make sense of what it does other than pontentially 
* the mon taking shelter from the sun behind its leaves,/in a cocoon of leaves?
* if its hiding in leaves potentially more safe? or comfortable, so maybe prevent stat drops, at base, and then keep the base effect for in sun?
* I think splitting it up and giving it an effect outside of sun, would help improve it without having to do anything crazy. hmm
* so essentially grass type clear body, with extra effects for sun, that are debatable from a practical side..   ok I like this. - DONE
* 
* fix acelgor sprite change lips
* fix delibird learnset oh already done
*
*   forgot need change castform ability logic, 
* changes weather too often,  check switchin, don't want to always change weather if weather exists
* for end turn change want to lower odds, so can actually better take advantage of weather change if possible
*
*new plan buff present , make like tripel axel, make multi hit and boost power with each sucessive hit.
* so it becomes a crap shot gamble, either do big damage or a heal and the damage has a chance to outweigh the heal if there is one
* so its not a complete waste.  plan augment move damage by an amount each loop,
*  potentially ensure the heal and damage boost for the heal is to a lesser degree
*
* researched base power of move was random, from 40-120... and it healed for 1/4th target max hp smh
* no wonder its bad,  new thing base 120  guaranteed hit between 3-5 5 hit should be total 120  (24bp)
* lower healing odds,  but each hit have chance to  roll either damage or heal on hit, divide base heal by 3, as its meant to be able to land multiple times
* so each heal would do 1/12th targt max hp,  that way it'd take 3 heals to get back 1/4th max hp
*hmm if I do it that way don't need to increase damage - think done need test
*
*make new move snowball,  variable dmg physical attk, use psywave effect, keep ice ball animation for now, idea throw ice/snow ball of varying size and power or something
*will be physical ice version of psywave, potentially w chance to flinch
*
* thought give opal style heal vial, make menu for item use clause, full heal / and set mode  there are times/strategies where you don't want full hp , or to clear status
* so make it full restore, max potion, and set,  change item effect to that of those two items, for set make menu effect where you can explicitly set the hp to heal to.
* moving left and right adjusts hp by 10s up and down d pad moves it one digit at a time.   setup logic for hold as well.
*
* setup be able to accss pc on the go pull out and deposit mon whenever,
* thought was for things lilke emrald kaizo, those games are extra difficult and annoying to deal with, since you need specific things for each fight
* so to counter that have hp vial to fully heal your team free, giving you two tries, rather than a wipe the vial is used to heal you up, or you are put back 
*  to a position before the fight, out of trainer sight, and you are able to heal and try again.  
* if do that, need store map location  of trainer fought, and direction of entrance of map, to put player closer to the map entrance
* in relation to the trainer they fought, and out of their potential line of sight.
* think also say put them at a warp position x number of tiles awaym so they aren't far and away from where they were before they lost
*
*should you win a match the vial would be refreshed, so every time battle outcome won you refresh the vial.
*hmm could use that as battle streak, rather than having to go to pokemon center to refill vials.
* could instead need to win a certain amount of matches.
*
* shuold be a different benchamrk for each batle type. i.e wilds vs trainers
* beat or catch 3-5 wild mon,  or win 1 (or more idk) trainer battles to recharge vial.
*
* would need setup new gvalue counter for batte stat increments on battle outcome won, reset to 0 on vial use
* only count up if vial counter is 0, since don't need to track it if its full
*
* notes boosted/fixed setup for psywave and seismic toss
*
* note on advice from anthroyd give more mon fly, go by movie logic if it can float it can fly  just like in movie 2000 guy flew on his gengar
*
* adjust type for lycanroc forms, need adjust evo move adn learnsets, adjust abilities as well
*as I buffed all move accuracy keen eye isn't as good? could make it never miss, but would just be better no gaurd
* could give no gaurd a 10-20% dmg boost to compensate.. prob not?
*
* Give crabominable a better front sprite, its just ugly 
* -progress
* takng inspiration from wendigo lore mixed with abominable snowman - lore actually works too 
* since its a selfish mon that desires to conquer and be the best, so put it like its desires went ary.
* 
* potentially add dunsparce evo and make better evo, think take inspiration from Fafnir boss from FF 16
* plan make it ground flying,  more defensive higher atk and hp than dunsparce
*
* other idea tsuchinco has extra links give this instead extra heads one largeer main body potentially somewhat sleek
* but evolve with extra head or heads that also have powerful arms/claws for digging  
* the brains are linked like a cerberus its highly inteligent able to split  processing between its multiple heads 
* but they don't get in the way as they are secondary brains that can process more
* 
*  addendum - dunsaprce digs with tail drill not arms/claws so no arms with second head intead a second drill tail, that can be individually controlled
* tail is less stumpy instead being a longer thing tail ending in the drill but still just as strong/sturdy
* think  glameow tail but rather than coiled is wiry and sprite have it intwined with the other tail.
* - stronger wings as well     think for tails make them dark red and black, it doesnt need to be flyign type so could make ground electric?
* tails would be like jumper/battery cables

- like its body naturally generates electricity but it has no way of controlling its output 
thus it lives undergroud to keep itself perpetually grouded?  - maybe can say its ancient form was a thunder dragon but lost 
* control of  their power and/or were forced underground by new predators?
* 
* Fix Pyroar F sprite front & back , guys in pret won't do it, so I'll have to. its potentially worse than crabominable I can't even look at it.
* 
* remake SPECIES_GOTHITELLE line sprites, to something more in line with gothic lolita, not ugly may take inspiration from Ori for final evo,
* black/white bob/bangs instead of the weird spike spider hair
* -lost references with old pc, have ssd need get new laptop to recover
*
* new idea for new lenendary/mysthic/mythic mon ghost fairy
* ghost fairy is very good defensively kinda want ghost/fairy legend/mystic with wonderguard low dmg high hp kind of priestess character
* no recovery moves, least not for self, but buffs debuffs rituals (curse painsplit etc.) some dmg moves //high sp def barely there defense
* since only weakness would be steel which is usually physical / maybe make like poipoi its legendary here, but common in its own world?
* maybe like its a pokemon from the fae world , think want to use Priscilla from dark souls as inspiration for this character
* foud perfect pose, reference, just need to tweak to make less human.
*  wonder gaurd would be a hidden ability to take advantage of its very neutral defenses typiing 
* I also wanted to have more partner heal abilities, since their aren't many
* its main ability could be applying heal affects to partner, so any heal effects it gets could ONLY be applied/would be transferreld to its battle partner
* that would also keep it from being too horendously broken.
* /I'm thinking high hp, tiny defense like 25, practically no atk  midling sp atk like 50 high sp def and average speed? 60 speed?
* can't use priscillla as a name it just  sounds like a name not pokemon
* but after research, darksouls was inspired moslty by norse mythology
* and priscilla's character found in anor lando which was inspired by the milan cathedral in Italy
* so and pokemon usually takes name inspirations from the region of the thing in question
*and what its supposed to be.  pikachu originally japanese  uses pikapika and chuchu  which are japanese onomaopea for sound of sparklikng and mouse squeks for an electric mouse
*
* I'm making a fairy ghost princess/goddess/cleric type character
*  and using original reference  I'm looking at both italian and norse  frames
* in itially fairy are tied to fate/destiny the word they use for them is Fata (also they are all women so La Fata)
*
*   JaFraeyta.... Freyja  norse spelling freya  goddess of fertility kind giving protective, who presided over a realm of the norse afterlife, typically for common folk as opposited to valhala
* Fata italin for fairy,  but linkmed with fatae from latin, which are also called Fae
Fraeyjta  - think this spelling works, even in norse the j is silent, so this is a mix of latin word for fate, which in itialian is also fairy, and freyja norse goddess of fertility 
*                               //and ruler of the land of dead
* 
* pronounced fray-ee-ta
* 
* make cursola signature ability PERISH_BODY only activate for enemy mon
* watching JPR Poketrainer showed me how niche/bad it is, especially whene mon already has such low def stat
* even without perish song on it if it gets hit by a physical move its not sticking around long
* 
* Also give cursola better, more cursed sprite, based on image found
* 
* GIVE Turtonator more stab moves? or more early moves
* 
* fix sneasal-line give better moves to learnset
* it hass great stats, but is usually only encuotnered late game,
* and is hard to evolve.
* but the biggest issue is prob, that it doesn't seem to get any moves above like 50 power. -give beat down and brutal swing
* 
* added more buffs to paras line with ideas from youtubeer Zen Mode also leans
* into what I want of giving a good reason to use mon indivdually from their evolution
* if they change greatly between evos.
* so parasect gets ghost type, bring up sp def for eviolite on paras
* give parasect ghost moves  evolving to ghost will make FAR more defensive, but
* get less use out of effect spore with normal fighting immunity
* give parasct nightmare in learnset  potentially added ultra sun dex entry
* Also give it pain split  & shadow punch  and dream eater and destiny bond
* 
* make pressure & hi pressure work like paralysis chance to prevent  atk- DONE need test
* 
* made custom paralysis effect, electric types can be paralyzed, but only by non electric paralysis moves - DONE
* 
* buff for suction cups, give it built in grip claw, using a trap move with suction cups will extend its duration
* in addition to normal force switch prevention effects
* 
* give eviolite everstone effect where holding prevents evolution 
* potentially replace everstone, or give it some other effect thing it was useful for breeding?
* 
* make revisions to add grass moves to sudowoodo line lvl up and tm learnsets   thinkin ingrain & bullet seed
* think want to also add beatup if it doesn't have already
* 
* GIVE shiinotic creepier more cursed front sprite -
* and change type to grass ghost but give ability nymph spirit to give it triple stab, boosts fairy type moves think 
* will roll in illuminate effect aswell  as replacement, nymphs usually draw in forest creatures so it would work. -This part is done
* Ability name toadstool nymp
* 
* Need add more ghost moves to its learnset  also dryads curse
* will be its signature move, unsure of what stat to drop.  ok think I've decided to drop atk stat 1 stage,
* sudowoodo would also get the ability but since shiinotic is a sp atker w low physical atk, it'd be able to take best advantage of the move.
* 
* Finish setup for move Dryads Curse effect need do stat drop & animation -  think Stat drop done
* animation idea, ingrain roots and wrap/bind constrict anim but with a black or darker color?
* or ingrain with mon shake but without the orbs  -DONE, need test combined, ingrain and ghost curse
* 
* Setting up flash freeze to just use sheer cold animation for now- will prbo keep DONE
* 
* For different forms, i.e hisuan alolan galarain cefirian, setup icon similar to pokerus in summary screen
* that will show a pokemon has the relevant flag set, and will evolve into its alternate form
* perhaps can demonstrate to player, with one of the in-game trades?
* just want to put a little letter in the bottom right of summarys screen box where mon pic is
* A C G H hopefully of different color for each  thinking seafoam/light green for ceferia  orange or red for alola
* purple for Hisuian? maybe dark gold for galar idk
* 
* abra buff, gave comatose, slightly buffed health to help give a chance of staying as abra to keep status immunity
* buffing to give comatose end turn healing 1/8th max health  as it takes double damgae from hex etc.
* and guarantees sleep based damage without having to get hit by low accuracy sleep move.
* Also keep in mind plan to allow being damaged by multiple status 1s at once, which would mean removing
* volatile status immunity from comatose, so consider this balancing for a future nerf  - DONE consider give substitute to comatose mon if needed
* (prob just for abra, as it learns sub byb tm gen 1
* 
* want  to set status icon when ability is comatose since they are effectively asleep, can do that, just need the interface thing that sets the icon.
* only want it in battle, think would not put in summary screen to avoid confusion, with mon actually asleep.
* 
* STATUS NOTES-
* could put in exceptions for statuses but it wouldn't be for every ability as for others unchanged
* itd be a nerf, and it might not make sense to do for some and not every in the category, even if it makes sense.
* hmm ok I think I can make it work actually, it'd be the ones that don't require setting up weather or some other effect to work.
* i.e rain dish wouldn't need it. but again each thing is balanced with an intended draw back so prob best to just not do that for these.
* just for intimidate trace and the draw in attack abilities should be fine
* 
* ...many moves were tms in gen 1 were replaced with move tutors or just lost from learnsets, of those
* abra was indeed able to learn substitute in original red blue yellow... o.o
* 
* will reinstate gen 1 & 2 tms that were removed from tms  full list below -
Body Slam	 Normal   TM08
Counter	    Fighting  TM18
Double-Edge	 Normal   TM10
Dream Eater	 Psychic  TM42
Psywave      Psychic  TM46
Explosion	 Normal   TM47
Mega Kick	 Normal	  TM05
Mega Punch	 Normal	  TM01
Metronome	 Normal   TM35
Mimic	     Normal   TM31
Egg Bomb     Normal   TM37
Rock Slide	 Rock     TM48
Seismic Toss Fighting TM19
Softboiled	 Normal   TM41
Substitute	 Normal   TM50
Swords Dance Normal   TM03
Thunder Wave Electric TM45
* 
* Further adjust freeze status effect, plan setup current gen frotstbite for after target defrosts
* double check that I've already made freeze consistent and work like confusion/traps to last 2-5 turns
* long as target defrosts normally i.e not via thaw or ice cure/status cure effect target will remain with status1_frostbite
* would need to make sure it keeps the status1 freeze icon, so will need to change defrosting
* to not just remove frozen but set frostbite, OR just not remove freeeze so you keep the turn damage & icon
* 
* check freeze implementation, if used a timer can set it so it plays defrost text turn timer hits 0,
* [woudl need to check last used move and last hit by move, to check if timer reached zero as a result of
* the thaw effect or not.]
* and then display a different string for end turn if defrosted rather than thawed, would be hurt by frostbite
* only remove status icon  if thawed, or ice cured or status cured w items
* 
* check shed skin ability, after changing define values to fit new traps, the bitwise may go wonky?
* another reason to remove new status 1 traps for grip claw & implement with conditional logic instead
* so can set values back to normal
* 
* note* potentially  remove badge stat boosts? since I will have higher ev cap stuff idk.
* 
* maybe offer de-evolution option? since I'm buffing some pre evos to be alternate ways to use a mon
* as it may be better at times to use the pre evo, based on what you want.
* if I do, i think will setup on cinibar island in the fosil restoration lab,
* something like "in the course of our research on fossil revitilization we discovered a method for reversing
* pokemon evolution, a "de-evolution" process if you will" -
* 
* update level up learnsets from emerald gen 8 files, and then adjust learnsets as I chose 
* based on my learnset expansion, since I can fit more moves now
* 
* Make copy ability of tinted lens, for non bugs, call it protag powere or subversion of great expectations  tiger cub? -   DONE ubt need test
* litleo  other vrsino  tigr mom o.0 will lower target defense on switch specific for female variant evo -  setup need test
* text for tiger mom,  "blank cowed the enemy\ into submission"
*cowed - to cause (someone) to submit to one's wishes by intimidation.
* need update constants/battle.h status 3 defines tweak setup or move some things to status 4 and change fieldsports embargo heal block to work as side status-s
* 
* BUFFED pickpockeet to have slight contact based damage reduction
* 
* buffed illuminate added compound eyes accuracy boost
* 
* rework competitive, so it raises sp atk, when opononnt's stat increases and when attacker gets statuss1 i.e guts -
* -statsed sp atk boost done, need to setup tracker for enemy stat change and effect that would let me raise sp atk stage, in response
* take some ques from moody, which raises stats. -
* 
* make sure frisk ability has gen 6 effect where it reads all opponents items, make reactivate
* 
* 
* *note*  Nidoqueen line intentionally can't be breed, something to do with comprison to real life rhinos not being breedable in captivity.
* so just make sure nidoqueen are available to catch in places, put them in safari zone I guess...well no that'd be even worse.
* make them wild somewhere in mid game/late game  put in desert area I guess.
* 
* adjusted multihit bs messages, check fury cutter see if is satisfactory - 
* 
* go over move chart, adjusting for low accuracy moves, bring up everything below 75
* meta is revolves around 1 shot or 2 shot, so low accuracy moves would never be worth the risk and just never get used
* especially if it doesn't have some other effect besides damage - DONE
* 
* made changes to psychic fangs, need test -
* 
* last thing I could do before break, is adjust the summary info box for ability description
* actually simpler than I thought, all I need to do is move up the text and fill the bottom of the window, with the```
* description pixels - may not be able to move window? - DONE
* 
* noticed with ability names at 16 instead of 12,, will need to expand ability name graphic space in summary screen, -
* 
* buffed arceus, gave global stab, and changed to mystery type
* 
* check moves that rely on enemy using a move first, make sure they use last used move, so they don't 
* just fail if they are faster than the target - think mostly done, need check mirror move and setup sketch monotype changes
* 
* fix focus punch move will NEVER work as is, instead make into a one turn move with recharge effect will also add high flinch chance - DONE
* another thing that will need ai adjustment later
* 
* add rock throw to more fighting types (or make tm), only for muscled bulky arch types
* 
* anyway for mon that can setup  multiple type power/dmg buffs i.e terrain & weather or to be used with a terrain on on team.
* 
* made grass buffs, make grass version of u-turn aka up root can be taken advantage of by chlorophyl mons - DONE
* make up-root remove ingrain status to ensure you can get out if you want to/really need to -
* 
* new idea, supplement bug buff immunity to confusion,
* make bug archetype all about self buffs/getting stronger, as bugs ususally go through evolution/chrysalis to become better/stronger
* that way they can keep their parallel to grass types, which are all about debuffing enemy.
* give bug types accupressure and in doubles can assist setup with ally targetted swagger.
* consider ai strats with a flying tailwind, accupressure on a bug protect and swagger, but something bulky like whirlepede
* actually masquirene can have tailwind!!
* 
* found out about move "powder" a priority move that makes fire type attacks explode on attacker consuming the attack -_- 
* INSANE its signature move of vivilion spread around to other mon it makes sense for,  dustox vespiqueen beedrill butterfree etc.
* I guess flying bugs that could have to do with flowers? but not crawling bugs?  I'll come back to this later
* think give kleavor as the ace
* 
* ...there's no bug type gym in kanto...
* ...fuck it I'm making a "cool trainer" with  a bug team using that strat SOMEWHERE
* 
* OK came up with an idea!! in celadon we have the grass gym with erika, I can do the saffron city thing, 
* where we have a defunct gym/leader he can be bug type.  can also be like the fighting gym in saffron where for beating him
* he'll give a rare bug type.   but since its strong to grass, it can be lower level.
* 
* Use alternate story from saffron as this trainer would have type advantage so it can't be that he was bullied into giving up his gym/leader dreams.
* rathrer story will be, he dreamd of opening a bug gym, but then Erika (and her ilk/crew/team/group) came along and ruined everything!!
* ...well not really, it was hard managing the place with just me, so when they came along we decided to work something out. //in battle end text
* I had to give up my dream but I'm not too hurt about it, I can still show off the amazing poweer of bugs here instead
*  plus they were pretty nice about it.   pretty and nice. hehe. //post battle text
* 
* I can't give you a gym badge but for conquering my magnificent bugs, take your pick of of the 2 mon behind me.(steps to the side)
* use starter logic, to make random loop trigger and set a random bug  based on a yet to be made bug species list.
* the special thing is it'll be a perfect 31 IV mon.
* 
* make sure mon types have their own niche where needed, i.e bugs imune to confusion because of hive mind
* grass immune to powder, ease of access to status moves to take advantage of multi status and higher than average vitatliy as part of nature
* fire can't be burned, poison can't be poisoned etc. 
* 
* note -A badly poisoned Pok�mon will remain badly poisoned even if switched out or the battle ends, although the counter is reset. *bulbapedia
* didn't realize this is how it worked, thought I would have to set it that way myself nice
* 
* poison types can't be poisoned, meaning if they are given poison_heal as an ability they can never activate it,
* but!! black sludge if held by a non poison type deals poison damage! so I think I would use that as a way for 
* a poison type to activate poison_heal   
* 
* Think would give sparingly to special poison types, i.e stuff like grimer muk, which are literally poison, so giving more poison would just make them stronger
* 
* -all I need to do is setup new function for poison heal activation bool, true false  then I can just put it 
* everywhere poison heal activates and the new logic would work.
* 
* note realized multi status is going to be easy to setup, its not actually any different code wise to status2, which already allows that.
* only "difficult" part is going to be the qol/setting it up properly i.e the graphic stuff that make it look good/natural and professional.
* 
* need set water mud sport effect as side status, effect not setup as of now. setup  think done need test
* 
* was able to use ctrl h replacement, to quick define all move descriptions just need to slot into table.
* and would owr, then can fix naming convention later
* 
* realized for move effects I've changed that were tms or hms I need to update the item description with the new effects
* not just the move description so need to compare move_info.h  descriptions with that of items.json...
* 
* ok next job update from json -_-  for some reason pret hasn't done that yet for fire red -
* 
* need buff poison i think
* for poison think can just give sp def boosts, as poison specialists poison themselves to build up immunity to poison
* giving them a stronger than normal internal constitution. - DONE
* 
* also added uturn variant for flyig types - DONE  need test animations later
* 
* changed hail ice buff,  most ice types have higher sp def than def, and main weaknesses are 
* typically physical made 50% defense and 1/3rd sp def incrase
* make sure to test later  tweaked as realized not much raeson to pick sandstorm for rock ice types
* 
*   In order for a fire to start, your tinderand firewood must reach a combustible temperature.
    Fires in the summer, even after a summer rain, can be easier to start
    because the wood will be closer to a combustible temperature than even dry wood in the winter.
    You will need more heat to get your fire started in the cold. //logic for why fire dmg cut in hail

* change fire dmg cut by 66% in hail,  Ice dmg cut by 66% in strong sun
* this functions as an ice buff, as well as a grass buff, great boost for sunflora who is grass/fire
* and can set sun on switch in.
* 
* reworking poison type add normal type to pure poison that is poison as a function of animal attributes
* leave the more amorphous mon as pure poison - DONE
* 
* NOTE toss gastro acid on some prankster mon, mostly as kyogre groudon counters but still good to have
* 
* Remember setup ability Dark Deal companion ability to nuisance
* Also need to add other abilties listed in base stats comments/port over comments/notes
* 
* Dark deal effect
* companion ability to nuisance, most effect is on partner, 
* give user devils luck i.e increased crit rate or double effect chance random % 2 if move power greater than 1
* usr gets increased secondary effct chance OR crit, the partner gets both, but in exchange all moves above base power 70 get their power cut in half
* 
* sounds like a nerf but is meant to work together with nuisance which increass priority of moves if they are weak,
* essentially expanding the move pool that the ability can pick from.
* think can do effect with edits to set effect chance bs command/function and a flag set to add high crit flag to move?
* potentially do like focus energy where it raises crit ratio instead, so its more easiy controlled, i.e can better control the crit
* can use critcalc  function for partner boost, use + 2 * partner ability dark deal
* then do other part in seteffectchance function
* for mon with dark deal, get either or crit boost or seconaryr effect boost each turn, flip with random % 2.  between 0 or 1  choose crit booost, vs effect boost
* changed mind,   since it doesn't have negative effect just gave both effects at lower values than the partner.
* still need to write ability description but effects are complete -
* 
* Also buffed/adjusted crit stag ratios, a mix of late gen higher crit odds, with lower ones.
* approx 10% crit increase per stage up to stage 4 which is guaranteed crit
* 
* think will give this ability to murkrow line, since they're mob boss potentially obstigoon as well.
* 
* //then finish new grass move nettel something
* got set deciding to setup move descriptions in.c file remember can just add file, as remember I added updates from  pret
* to simplify adding files.
* 
* updated move descriptions and trainer tower fils to C files,  following pret commit history, double check later if there were any issues
* all that's left is setup animation for Nettle Whip/vine   - for now fill with generic vine whip animation
* 
* I think use vine whip animation, smack target 3 times, and then do astonish effect on target, where thy get the exclamation point thing. -
* 
* late gens restricted toxic, so only poison mon can learn it, that's too restrictive imo, I'll limit it to grass bug, poison and dark. -
* 
* think fixed setup for heal block as side status,  should work for blocking all items as well,  made new heal block switch in anti heal ability
* plan to give to guzzlord, try find other mon as well. -
* 
* because of embargo and heal block changes, need to setup new bs command jumpifsidestatus to replace use of jumpifstatus3 for them
* 
* also setting up embargo as side status ability, will give to theif mon, liepard  theival etc. also give them pickup if they don't have it. - DONE
* 
* nother idea true anti heal, gbattlemovedamage *-1  if attempts to heal re-reverses damage formula, so it causes you to take damage instead.
* imagine uses rest and just dies off rip 0.o
* can give to darkrai too, since you die in sleep when you're trying to rest use same move effect list as IsHealBlockPreventingMove
*ABILITY_DESPAIR  and look at itembattleeffects etc. setup like healblock has 5 turn timer or no timer, if permanent do if ability on opposing side
*
* 
* Give giratina new ability a combination of competitive and defiant, known as ursurper 
* 
* ability for giratina origin
* //idea inverse world being on the field forces inverse battle interaction reversing all type interactions for this mon,
    //what is super effective becommes an immunity,  so it can be tossed against things it normally is weak too?
    //yeah that works, would also make it immune to fairy and dragon  do something like how wonder gaurd works that shifts the applies effctiveness

    //check ability if super effectie make it no effect, if not very effective or no effect make it super effective
    //if normally effective make it  not very effective

    //attacks it does that would normally be not very effective to target become super effective
    //like wondergaurd will need to make special ai logic for
* 
* note from bulbapedia -  Telepathy is the most common Ability to have as a Hidden Ability. 
* - Telepathy Anticipates an ally's attack and dodges it.  -
* ok telepathy seems to be another levitate sitaution, it was only introduced to deal with a  mechanic change.
* i.e multi target moves, being able to hit everyone  i.e surf earthquake now hitting your teammate too.
* 
* in gen 3 that mechanic doesn't exist and I doubt I'll add it back, its pretty dumb, the idea is the pokemon is able to control the elements,
* and focus/target its attacks, so it makes no sense  they can avoid hitting their own teammates,
* or you'd have to expect you as a trainr was so bad, they would intenionally use a wide aoe move while your own pokemon was standing right in front of you.
* 
* it doesn't make sense, for anything other than explosion, which is clearly an indiscriminate massive uncontrolled blast.
* which is obviously the nature of an explosion - combed through moves adjustesd and removed moves that targetted allies too that didn't make sense - DONE
* 
* without that mechanic change telepathy doesnt really do anything, other than prevent you from targetting your allies with moves, which sometimes you want to do.
* It would become useful if I get my new confusion effect going which, would make characters attack others at random when the roll fails,
* rather than only hurting itself.
* 
* but confusion isnt everywhere so still rare uses case, 
* idk, could  change to have effect similar to how anticipation and forewarn now work?
* need check who all has ability
* nvm dont want to just copy effect as this already goes on psychic mon, which would have forewarn
* 
* yeah was right, its just like levitate, post gen 5 it was just slapped on everything for no reason, 
* or to help mon who's kit would be hurt by that dumb change.
* 
* for psychic mon, excluding woboffet line who actually would benefit from the effect, replace with forewarn, for legendaries just remove it -
* 
* in attempting to remove telepathy, made sound ability for noibat/other bats,sonar, decided to add confuse chance, to all(most) damaging sound based moves
* as loud noises disorient and super sonic is the og sound move.
* 
* -keeping telepathy on few mon, it has to be on a psychic type but is only really good for mon that are already strong
* so wouldn't feel the lack of ability, think will keep onlny for bulky psychic types? like the orangutan.
* 
* make new type sound type, treat like mystery, used for move but not for pokemon,  will make all normal sound moves type normal
* offensively neutral to everything (just don't add to type chart
* ...well nvm I'll add it, just so people know its there, type sound will be immune to type sound just so ppl know its there)
* delay implementation for now, would need edit to icon sheet, for new icon, -wanted to make icon white, but would blend in on summary screen
* as well as all places where types are used - icon added, to sheet, need to define new type in relevant areas, 
* and make sure it can read the location correctly for the new icon placement. - DONE
* 
* making sound type, but still keep flag check on moves for flag sound, still using that for soundproof. - DONE
* putting areas needed for new type addition below - DONE - still need update some moves with sound flag to sound type
* 
* seismic toss buff to make scale for end game with extra damage calced as a function of enemy weight
* weight measured in kg in game but way its done (since can't store decimlas) is every is muliplied by 10
* so 9.9 kg is 99 weight in game. and so on.
* plan is make a table/array based on these weight categories from bulbapedia
* since some mon are really light if I do flat weight it won't matter much so I think what I'll do is
* set up each category and make each a multiplier setup just like falil array
* where it uses max weight for the category as the array labels then in the function checks if less than weight at x use value at y..
* I think I want it to be max weight caps it at 2x dmg so you'll do 2 times level damage.
* way I'll have it work is if greater than 2nd to last max weight it'll just do 2x dmg so it hits everyone in that last category  (i.e this is where snorlax and most legendaries are)
* 
* actually nvm grass knot and low kick exist I'll base it on those ratios
* 
* will then scale with level to balance
* effect starts at level 20, so that'll be divisor mon hp should be high enough
* by lvl 50 I think, so will receive max effect at that point.
* i.e formula will be level + (weight booster * (level /50))  if level is below 50
* hm actually if I do it that way, I don't even need to limit the effect to being lvl 20
* it'll scale on its own.  -DONE
* 
* 1.1	0.0 lbs. to 21.8 lbs. (0.0 kg to 9.9 kg) //20 bsp for weight based moves
1.2	22.0 lbs. to 44.1 lbs. (10.0 kg to 20.0 kg) //40 bsp for weight based moves
1.3	44.3 lbs. to 54.9 lbs. (20.1 kg to 24.9 kg)
1.4	55.1 lbs. to 110.0 lbs. (25.0 kg to 49.9 kg) //60 bsp for weight based moves
1.5	110.2 lbs. to 132.1 lbs. (50.0 kg to 59.9 kg) //where low kick/grass knot hit 80 base power
1.6	132.3 lbs. to 218.0 lbs. (60.0 kg to 98.9 kg)
1.7	218.3 lbs. to 220.2 lbs. (99.0 kg to 99.9 kg)
1.8	220.5 lbs. to 225.5 lbs. (100.0 kg to 102.3 kg) //where low kick/grass knot hit 100 base power
1.9	225.8 lbs. to 330.5 lbs. (102.4 kg to 149.9 kg)
1.10	330.7 lbs. to 440.7 lbs. (150.0 kg to 199.9 kg)
1.11	440.9 lbs. to 451.3 lbs. (200.0 kg to 204.7 kg) //where low kick/grass knot hit max power
1.12	451.5 lbs. to 661.2 lbs. (204.8 kg to 299.9 kg)
1.13	661.4 lbs. to 677.0 lbs. (300.0 kg to 307.1 kg)
1.14	677.3 lbs. to 793.4 lbs. (307.2 kg to 359.9 kg)
1.15	793.7 lbs. to 902.8 lbs. (360.0 kg to 409.5 kg)
1.16	903.0 lbs. to 2204.4 lbs. (409.6 kg to 999.9 kg)

* 
* check gearup make sure it works and does stat raise for user/in singles
* 
* change burn up/burnout effect, since I want mystery type to be special, will instead replace fire type with normal type
* they get the benefit of joat that way instead, of the typeless benefit.
* if they have 2 types, than type removal can just make it mystery, but if they are just one type and I'd have a type removal effect
* they should become normal rather than pure typeless. - DONE need test
* 
* in process, made burn up its own category of effect, will treat like hyper beam make base 150
* but instead of recharging like starteres do the mon will lose its type for the battle. the ENTIRE battle, it won't just come back if they switch
* made psychic variant already and planning an electric variant.
* 
* For logic the type must be an element produced as a secondary effect of their normal function.
* i.e psychic powers, breathing fire, generating electricity
* all effects that can be exhausted.
* 
* a leap in logic but can potentially do fighting type and flying type,
* if think of it as they are too exhausted to maintain proper fighting technic, or become too exhausted to fly properly 
* Fighting version called  Shimon, after the final 8th gate in naruto
* 
* Final Flight for flying type
* 
* don't know name for electric variant yet, but it'll be a railgun type deal, focuses all their electrical energy into a codensed beam of energy
* 
* plasma railgun
* 
* can do poison to, see if ccan find name form marriage toxin
* user controls and condenses all their stored toxins/poison into a single attack
* 
* NEED write move descriptions 
* 
* RENAME move_descriptions to .h when done
*/  
goto TYPE_CHART
goto TYPE_NAMES
goto TYPE_DEFINES
goto TYPE_ICON_DATA //was missing something listing of the types and their order is in the graphics_file_rules.mk  file
goto TYPE_MODIFIER_ADJUSTMENTS //place for special case logic that overwrites normal type behavior
/* NOTE - still need to finish set message for spite changes, can do just like I did anticipation ability messages
* -DONE   also made eerie spell use the new spite effect rather than only taking 3 pp. //NEED test errie spell test if still works aftr sheer force logic added
* 
* tweaked moves that were target ally & foes, changed to more appropriate targetting, need adjust move descriptions to match - DONE
* 
* plan to setup special move tutor, for the lets go eevee and pikachu movs, like the starter tutors,
* pokemon must be max friendship, but this will be reusable.
* The stipulation is only ONE special move can be learned at a time, meaning if you want to get a different special move.
* You need to replace the existing one.
* 
* And yes they have to specifically be a pikachu, or eevee at the time not one of the evo forms.
* Use cinnibar de evolution for this, think would like this tutor to be mid/late game, but descoved before de-evo is possible?
* idk may not be necessary, just point is player fnids this when they've most likey evolved mon, and then realize OH this is a use for the
* de-evolution mechnaic!
* 
* event will be a pokemniac that loves pikachu and eevee, "blah blah I love pikachu and eevee, their wonderful, don't you agree?"
* "excited response, followed by no one knows these two better than me, let me show you just whats so special about them"
* open move tutor menu.
* "after closing, these moves are special and can only be learned by pikachu and eevee, before they evolve"
* "If you come back I'll teach your pikachu or eevee a special move any time!"
* 
* tutor will be free,  because thye like you, but also the deevolution will cost instead, 
* cinnibar island scientist:
* "we're not running a charity here we need all the funding we can get to continue our research
* Grant money isnt easy to come by!"
* 
* Also comb over stats again, to attempt to address power creep?
* not sure if it would matter, higher is still higher even if I bring things closer
* on the offensive side i.e atk sp atk speed  and my ev cap increase is technically already made to address this
* 
* //go over 100%  effects, see which I can make certain in bs commands.c seteffectwithchance function, I think I can do all,
* that way I free room for arguments if I chose to add then. -
* 
* Progression idea, mega evolution, planned for megas to be a special permanent evo only, but perhaps, 
* could actually include mega rings, as a temporary means of letting a pokemon reach the height of their power.
* 
* While the true form could be acheived through rigorous trile that lets someone be a mega permanently. to truly mega evolve.
* This would bypass the typical one mega evo per battle.
* Doing the normal mega thing would let people play that way as they want,
* but still let my preferred mega mechanic exist, as an extra thing to grind for.
* 
* Remember plan is make megas a way to turn normal mon into psuedo legendaries, rather than just adding +100 bst.
* 
*
* Look at changes to early gen mon, consider bringing back stats from gen 1 & 2
* where special atk & sp def were all one stat  see how it changes mon
* and if it makes sense for balance - DONE this was only for gen 1, it was changed in gen 2 and most gen1 mon were balanced with that in mind already
* 
* with buffs and planned addition of more mon early on, consider tweak to leveling function that will weight stat growth to later
* so you can have stronger mon in early areas without them being super op at low levels ( may not need ot its possible current function already balances that)
* if early levels aren't greatly different stat wise would make easier to balance mon for late game. -tested, not needed
* 
* Also consider tweaking how terrain switch works, make it stay as long as the ability surge mon is on the field
* want to work like  weather switch which I think works off last in?  may work off speed?
* make conditional where its supposed to decrement if they're on field timer equals "permanet" i.e timer = 5, if not on field decrement timer
* that way even if they get one shot its still valuable to put out as a setup.-
* 
* Do I want to make all terrain last until removed?
* then make ocean permanent terrain that can't be changed, is set by environment
* 
* Remove drizzle & drought from mon, and replace with new ability's instead of just giving everyone groudon and kyogre's abilities
* Thinking Squal in place of drizzle  and I guess High Noon in place of drought - DONE  test
* 
* setup weather moves, to increase duration of weather effect if used again
* if you count you don't need that, now question is, with being able to do that does that balance the low pp use?
* I think so, ok all weather moves will have pp 5, but be extendable if used again. - changed mind
* 
* that way kyogre and groudon can stay special.
* plan is other weather abilities will be temporary 5 turns like sunny day but better
* as it resets the timer at turn end as long as the mon is still on the field.
* think will need to make a new struct member for it, simialr to  wrapped by
* where it'll track the battler who set the weather condition
* check will be if current weather isn't permament/primal, and matches the weather that would be set by the ability 
* (as proof it wasn't overwritten by another weather ability) timer gets reset to 5 at end turn
* if said battler is still on the field. 
* make meber struct weathersetby  
* just need to set when ability actiavates like so gBattleStruct->wrappedBy[gEffectBattler] = gBattlerAttacker;
* do in ability battle effects just sub effectbattler for battler as ability function already uses battler as aits swithin fun stuff..
* 
* - think done, don't need weather set by,  permanent weather doesn't use timer. so dont need special stuct
* just need to use plusle minum ability on field check, linked with the weather condition its supposed to set,
* if weather is current just keep timer from going down - DONE  -revamped
* = - Changed effect from TryChangeBattleWeather for weather,   
* All switch in weather abilities ignore decrement while they are on field,  but none of them are permanent,
* and Groudon or Kyogre's abilities being on the field  prevent weather switch in  so they remain special.
* 
* No temp weather ability is able to overwrite primal weather abilities, except other primals,
* hierarchy is primal weather, groudon/kyogre weather, normal ability weather, move set weather
* 
* similar to original effect, but also gives more reason to use weather crystals, would make weather set last 8 turns from when ko'd/switch out
* so effectively permaent weather if enemy team doesn't have weather setter.
* without outright requiring yuo use the crystals.
* The longer effect is balanced by being modern and having things like neutralizing gas, gastro acid etc,
* 
* 
* TryChangeBattleWeather  need replace  LOGIC for all weather abilities with that function - DONE
* 
* primal weather also sets terrain,  for kyogre & groudon, mega rayquaza would only remove their weather condition
* where otherwise primal weather can't be changed.  so strengths them a bit as they keep the terrain
* 
* just confirming don't need weathersetby weather effects are done never assigned it, I just needed an on field check
* 
* change mudsport and watersport to be terrain clears, will still do 
* normal move effects but they will also clear terrain *idea from Sigel - 
* 
* change terrain function elements TryChangeBattleTerrain(u32 battler, u32 statusFlag, u8 *timer)
* to work like changeweather function replace timer pointer with true false for viaAbility - NULL doesn't need doing just adjust end turn terrain for abilities
* 
* so I can setup logic for terrain surge abilities  potentially make certain side wide type moves terrain clears as well
* i.e earthquake surf etc. -  NULL changed mind, makes terrain too accessible and thus overbearing.
* well that was dumb, was tired and literally crossed my wires,  I had an idea of them setting terrain as well,
* so they can clear terrain but not set and thats fine actually nvm, as terrain affects both sides, it would just be annoying to try to set terrain then destroy it
* with your own attack, when you were trying to do damage.  mud sport water sport as terrain clears are fine though
* 
* don't know if need snow terrain, since I have weather condition,
* and places where I'd set hail there's no need for snow terrain effect
* unless I make it exclusive to seasons/places where it only is snowy on the season, and hail for just places where its 
* winter/icy year round.? could work i guess
*/

goto WEATHER_AND_TERRAIN_EFFECTS
/* 
* 
* new ability idea from anercomp,  high roller (name pending)  comeback king  (?)
* ability that doubles in power whenever the mon misses (or move fails), a bit of move forgivenesss
* will essentially let them make up for lost damage from the miss.
* next attack becomes sure hit.   use same surehit logic  I did for traps
* what can do is make a value/member in battlsruct set to zero,
* and hvae it increment whenever the battler with the ability misses a move or fails to land an attack (put in accuracy calc/atk canceler))
* and thn in damagecalc multiply that value by gbattlemovedamage like the critmultiplier
* but use +1 since the value starts at 0.     if ability  gbattlemovedamage *=  (value + 1)
* 
* Go over field control effects again, i.e traps status terrain weather  drain abilities make sure everything remains in balance
* I don't want to turn things into a gimmick where the only thing ppl do is status or terrain I want them to be relatively equal options
* -
*/

/* adjust enemy battler placement for double battles, seems doubles aren't well optimized in fire red...for some reason
*  health boxes cover the enemy, need to move them higher, and move field they stand on by same amount
*
* moving sprite placement is a combination of gEnemyMonElevation  which is additionnal floating position for mon that fly/levitate and
* gMonFrontPicCoords  which is the coordinate for every mon, and can go into negative values to raise higher
* for non floating mon believe a tentative value of yoffset - 8 should put them where I need/want them.
* flying mon will be harder,   but will need to specifically filter the change for doubles only,
* which can do with IsDoubleBattle  function  this is from battle_anim_mons.c may actually be able to do all changes from there?
* while gmonfrontpick coords is the source it seems to be mainly accessed through GetBattlerYDelta,  and can make changes there and have
* it populate everything else rather than messing with src data, for extra protection
*
* need find differene betwen GetBattlerSpriteCoord & GetBattlerSpriteCoord2   they both go to GetBattlerYDelta
* but the first doesn't immediately go there, and allso handles some X values not just y
* also it uses this  "sBattlerCoords" before the other function does.
* not yet sure how to read it, but it seesms to prove/show that singles and doubles use separate values.
* also it SEEMS like position x y is determind by taking an average of the values in sBattlerCoords ?
* 
* near done, needed to move trainer pic as well also adjusted default battler position height for doubles
* battler right sat higher for some reason made more even, so height boost won't be uneven.
* still need to move terrain, updated defins but requires 4 pixel graphic edit to raise.
*/
goto SPRITE_COORDINATE_AND_ELEVATION_LOGIC
goto FRONT_PIC_TABLE    //table for front pic use rules to standardize mon brought in from expansion
goto MON_ELEVATION_TABLE    //SAME BUT for elevation    /some mon for pokedex need raising see if these are relevant-

goto METATILE_TYPES //of interest coud be behavrio fro recognizing grahpics as encounter tables i.e tilesets to grass water etc.

goto TERRAIN_DEFINES
goto FIELD_ENDTURN  //battle_util.c  includes weather & terrain decrement //still to do     vsonic
goto BATTLE_TERRAIN //Battle Terrain, NOT TERRAIN effect, is the entire battle field, including part battler sits on, can use to make terrain effect
goto BATTLE_SETUP_TERRAIN   //sets battle terrain from metatile/environment
/*
* New terrain notes
* 
* Overworld thunderstorm generates electric terrain //do more with this & nature power
* changing terrain can change nature power move? 
* 
//may do something with counters and advantage where certain overworld terrains can't be overwritten by certain terrain effects
//i.e scorched can't overrwrite ocean teerrain but can cancle flooded since its the opposit they cancel out, will need a seecon dus to make terrain
//also can't setup grass on desert or ocean terrain, but will work on flooded terrain  also will cancel scorched and need second use to work
//think have flood & ocean terrain have same effects but ocean is just harder to remove/permanent and only when surfing
//strengthen water as if in rain, and activate rain based abilities? 100% activating swift swim in ocean terrain 
//checked includes swift swim & hydration, exclude rain dish  but include dry skin
//think can make scorched activate abilities involving being burned or involving heat
//includes thermal exchange, guts, steam engine, well baked body, flare boost
//negative side activates dry skin
//may cut back on this so terrain isn't too overbearing/important  just check balance 
//should be fine just don't add flash fire
//plan setup misty with ocean terrain in gym as introduction to effect
* 
* further plans setup snowy terrain for mountains, and winter season.
* in addition to same effect as weather buffs, hail in this case for ice types.
* Since terrain is the mon being in their natural element, I will check and activate certain abilities 
* central to the element that make sense for each terrain.
*  snowy terrain would set snow cloak etc.
* 
* //look into how fild is generated i.e grass vs water when surfacing
//specifically the circle mon stand on, want put terrain effects on that
//simlest solution depending, may just be to edit the graphic for each,
//and have it white out, and reload the circle during fade
* 
* 
* the circle is attached to the backgrond presently so setting up different terrain would require every battle terrain have 5 or so variations
* just so I can change the circle. on top of needing 2 different sets for each because of needing to move the circle for single and doubles etc.
* 
* rather than that I'd prefer separating the circle graphic from the normal background base (look at opal grpahics think it does that)\
* if possible I'd like to use it as an object, similar to health box etc. is handled where I can just load it onto the background
* only question is if the pokemon would still sit correctly on that, or would they be under it, as an object would have a highr
* "priority"  if I can separate it, that would solve everything,  it would stil build from the tileset,
* but I can move the object dynamically with code, /a window rather than needing to make multiple variations
* 
* yeah opal has the battle background and then the png for the base to sit on separately
* base pokemon has it all tied up together  hopefully can separat without coming up on some gba limit
* 
* terrain would need to load in and slide in, like trainer sprites
* incidentally strainer sprite proves its possible to separate the sprite and have it sit on the background
* as the trainer sprite is also a png and does exactly that.
* 
*/


/* 
* NOTES PT 2.
*  add and change for regi effects, instead of player needing to know brail, setup archologist npc, maybe in pewter town museum.
* that will "translate" the text for you to read.   so when you initially find read it, a special flag will be set.
* in the museum npc he'll chech for those flags from lowest to highest, and read the first he finds each time you talk to him.
* have him be shocked excited then say let me translate  ... fades to black and returns
* Ah I see, the text means (maybe highlight translation) "blah blah blah" clears the first set flag and then sets another
* that'll change what happens when you click the wall, now that you know what it says, a box will come up asking if yuo want to do the thing
* i.e "use cut on wall?" yes/no  then check party for a mon that can and do it if possible, or return no one is able to use cut.
* 
* believe I've sstup rtc need to see if it works, further ssetup day night graphics (the good ones with proper night lighting)
* daily weekly monthly & seasonal events to make the world feel real.
* and time and season based encounter data
* would also need tile changes for areas that would get snow in winter
* deserts and tundras would remain unhanges year round
* 
* Emerald expansion dropped new  mon icons for legends arceus need update and add 
* - added stat data, need setup pokedex data and acual sprites/graphics and cry data, think will just use base mon cry rathr than new ones for space -
* 
* 
* planning space time events for palkia dialga, so for post game
* can use that as setup for hisuian mon appearing on the map.
* scientist is studying  time distortion then space distorition with his tech/device
* after both events are complete as thanks he'll give you a new version of his
* device hes working on.
* 
* Can have it as a filter add on to the pokenav/dexnav
* it'll be a filter to select, search for warped time/space
* a bush will shake and it'll spawn from the hisuian mon table
* that can spawn on that map.
* Believe will require converting encounter table from a json 
* to .c & .h file to use functions and arrays
* to decide what table to pull from.
* 
* -removed famechecker for space, have rival give dexnav in cerulean instead of famechecker
*   -believe need to redo this? - yeah need bring things back for fame checker work correctly
*
* - check fire fang somehow effect triggered weird script? didn't load right, said "ally's wore off"
*  and mon didn't faint??? possibly issue of attempt mail removal think undo
*
* -new plan for dexnav integration/synergy with hidden ability,
* with planned gameplay loop adjustments for catching i.e releasing mon to get items as you're expected to be catching multiple of the same mon
* to find ability nautre ivs etc.
* I need to adjust dexnav, before dexnav is how you get mon with hidden abilities and allows searching for specific mon
* Add on to this, that  you can use dexnav to find your perfect pokemon the dexnav search feature should populate
* as you have discovered more about the species.
* I.e raise its search level, and catch one with every possible ability.
* Once you've maxed that you unlock perfect search, which lets you essentially generate the perfect mon
* you set the mon species, set the ability, and can even set the nature! 
*
* for doing this keep track of search level for individual species for finding species in other locations
* if reach max level and unlock all dexnav features for mon, sets base stat flag for max search power, 
* dexnav will only lock feature and grey out a mon if it doesn't hvae max search level
* 
* think may not include search level as its already difficult to break through odds to find all abilieties
* if you get lucky and find them all quickly, don't want to hamstring the player by forcing them to keep searching
* if they get lucky they should be able to get the benefit of that.  keeps things fun and feels like a reward
* 
* Ivs won't be included as I'm going with matsuda idea that ivs should be hidden thing that you don't change.
* plus I've boosted evs so you can overcome any bad iv luck, with honest work, as it should be.
* 
* (make menu, in dexnav, you select the mon icon, that  takes you to a page that shows its mon pic
* info about how many you've caught/seen  places for the ability slots filled in with the ability name for each slot
* if the ability is none for that slot, just don't bring up relevant icons for it.
* othrewise just put a question mark in the fields if the mon has an ability but we have yet to descover it.)
* 
* also plan to add more encounters to each area on top of changing how tiles work, so grass not on the road, and rock not on sand can spawn encounters
* but hopefully can set separate encounter rate for said tiles so its a bit lower.
* 
* good way to add more encounters to maps without needing a lot of graphic work, 
* if I can do that, then patches of grass can be used as "tall grass" and have separate encounters and 
* higher chance for double wild encounters.   
* 
* Will need to fix and add double wild encounters, as its in the game but not fixed/properly coded
* 
* also setup special event for new game, where there is a random chance for the game to set a extra flag        1/30 or 1/50 odds
* that would trigger a traveling fishermin event script at the south side of pallet by the lake.
* rather than a battle he will give you the old rod, after a speel about teaching the youth/next generation the joy of fishing.
* 
* Fisherman, will be there at game start,  and disappear after you give oak the parcel.
* 
* add more than magikarp to old rod, things like lotad feebass etc.
* 
* add on to normal old rod event script if the flag for the traveling fisherman is set (actually just make it the same fisherman)
* he'll remark its good to see you again, ask if you've been using the rod.
* 
* and then give you a water pokemon around lvl 10 with a relatively low stat total.
* i.e need make function that will check type and then total all the stat fields.
* 
* or more simply use breeding check for first evolution species, and have him give a first evo water mon
* at level 10,  excluding legendary mon and manaphy etc.
* 
* could also use that for new game plus, were you would alrady have all the rods.
* 
* so instad each fisherman gives you a progressively better water pokemon instead of a better fishing rod
* 
*   //VSONIC IMPORTANT
* 
* species based  ai?? like archtyps for the type of battllere based on species data  i.e tricksters, more patient mon, harsh attackers, healers etc.
* had an old idea based around nature based learnsets, so wild mon would perform differently when you encounter them
* based on their nature
* 
* but learnset array like all arrays are static, (least in c) so I can't just filter the array
* but instead think can do by changing wild mon move learn, would potentially apply to wild mon and trainers without custom movesets
* can possibly apply filter for trainer struct  like  TrainerMonNoItemDefaultMoves
* 
* GiveBoxMonInitialMoveset is the function that deals with wild learnsets..I think, also includes function i think is for deleting 
* the first move it learned when learning a new move  tpye of FiFO process.
* so if add a lot more moves to base learnset, and the using functions to filter the array for what it decides to learn,
* or skip, to essentially make the mon move learning look more like the player decision making
* and once you catch it, what it has wouldn't matter as we have move relearners in the poke centers.
* 
* Learn more about learnset limit, and how to increase?
* Being able to add much more moves would be greatly impactful/helpful.
* would get rid of the long gap of not learning anything, and need to attempt to space things out
* the same way its done in base game.
* 
* move relearner
* max level iup moves
* 
* we're learning all the time, and can say mon learn faster, so argument its more natural.
* more options would allow for better/easier customization of style of play. - DONE
* -raised to 35, appears to work without issue, also had to raise move relearner/move tutor as it seems to use same thing
* 
* next goal setup better move relearner logic, so mon like stone evos don't just have no moves if you evolve early.
* make it so when you select a mon for move relearn you have the choice to choose from that mon's moveset
* or any of the pre evos move set, up to the level you're currently at.
* that way its more balanced and you don't just evolve and get all the moves, like the cases where pre-evos are 
* just all the same moves but ata lower level. 
* 
* So instead of looping pre evo moveset to lelarnset end just go up to current level.
* put move relearned in pokemon center, select mon, like normal, but then it opens a dialogue
* which moveset do you want to choose from?
* "Ninetales's Moveset"
* "Vulpix's Moveset"
* start with current species, and going down the evo line
* when you select here then it would open the moveset w moves learned by that mon up to your current level
* for some mon this would be unncessrary as learnset is the same, but for stone evos etc would be a major upgrade.
* 
* can setup list by reading evo logic in reverse
* use  GetEvolutionTargetSpecies(struct Pokemon *mon, u8 type, u16 evolutionItem)
* targetSpecies = gEvolutionTable[species][i].targetSpecies;
* 
* 
* that way you can return the pre evo
* start list as first value if can evolve returs 0, just return mon i.e species. -doesn't work either, would break for mid evos
* 
* and have it append to list.
* given that logic and the exaample given,...that wouldn't work, ok if I did it that way it'd
* only find the evo given the pre evo which is the oppoite of what I'm trying to do.
* 
* So instead return species of mon first, append that to list.
* and then read evo table in reverse from there.and include level compnonent
* that way ninetales would be added to lsit firt then it would look for pre evo and find vulpix
* and add it to list next, would then just need to break if can't find another pre evo
* 
* ok not technically possible to read in reverse, as it works by reading a given species value,
* than loops through evo methods reads parameteres and finds a target evo species from that.
* 
* without the x value you cant get to y, you can't read backwards.
* 
* 
* Instead load current species to separate target species value. Loop entire species list rather than using a given species
* stop when you find a species whos target species equals saved species value
* and return that species value as the pre evo and add to list
* 
* do repeat until you reach species list end (NUM_SPECIES or FORMS_START), that way you know you've found all the pre evos
* and no existing mon evolves into the one in question
* 
* want to exclude evolution method mega evolution
* 
* will need to make a function from this to find pre evo -
* 
* -will also use for de-evolution logic, will make functionality for others, but not use myself as there isn't a need in normal pokemon
* 
* thanks to emiyasora have a starting point for reference, forgot that breeding/daycare logic essentialy reads back through evolution.
* that may be what i need.
* GetEggSpecies     yup that works perfetctly,  it loops through species until it finds no mon that can evolve into that mon.
* 
* List apend logic can be taken from fieldmove append list
* 
* 
* idea for ev boosting gym do with safron city fighting gym  could give ev boost items there -
* 
* think will remove need for badges to use overworld hms, makes more logical sense.
* instead balance progression by availability of mon with those abilities.
* 
* only need mon that can learn the move to do hms.
* for fly/surf set it upp that you need a mon of a certain size.
* can do by comparing pokedex value, pokemon scale with trainer scale
* long as trainer scale is greater than pokemon scale, mon is bigger than player
* to give some wiggle room, will do if ((pokemoonscale - 30) is < trainerscale)
* 
* may do away with, if it ain't broke dont fix it type of situation,  doing this would create a forced list of mon
* you'd need to keep in your party, while its realistic, this is still a game, and the average player won't want to deal with that.
* 
* while technically I could do this without a problem, as I'm planning to  add the legends arceus holder that lets
* you carry extra pokemon outside of the party, and let you swap their place  on commmand.
*  that would essentially bring up a similar issue to hm slaves, but it just wouldn't be inconvenint, or as inconvenient.
* 
* Reconider later, still haven't even attempted adding the carry case.
* would be 6 (or less) extra slots of mon that would be held in a pc type thing
* simplest thing would be making 1 extra pc box, with fixed title only accessible via this item.
* no need for new logic, or graphic
* 
* //shifting 8 is the same as using 100, left shift << is multiplying,,  >> right shift is dividing
* 
* adjust filed move to only add to list when its available i.e need badge for hms even if you can learn it
* did I setup using hm use without needing to have learned it yet?
* idea is for hms  use tmhm learnset check.  ok hadn't done it, made an attempt need test
*/
goto FIELDMOVE_LISTMENU //partymenu.c setup for field hm use is here
goto CURSORSELECTION_FIELDMOVES
goto ABILITY_CAPSULE_DATA
/*
* change how ability capsule works, let it change current ability to any other abilities it has 
* make opena dialgoue displaying species abilities in order of slots and print to a box if not equal current ability
* so should print every possible ability excluding the one it currently has, populate selected ability to str_var_2
* 
* as it works now, it takes current ability to hidden ability 1 and fails to work if current ability is hidden ability
* my version will work no matter what your ability is and allow you to select any ability it can have.
* 
* similar logic to field moves loop options add to list if not ability none, and don't match the previous
* added abilities
* 
* make sure to exclude from new use logic I plan to make
*/


goto EV_GAIN
goto CATCHING_LOGIC
//notes for gameplayloop below
/*
* Need to adjust ball multiplier logic for catch.
* Add more pokeballs, add more status effect multipliers to augment catch odds.
* and NEED to change the current status augment odds so they'r additive instead of multiplicative.
* Current effect would be FAR too strong.
* I'm using IFs so they would all be inclusive
* just need to chanege from *= to an +=  I believe odds = (odds * 15) / 10;
* would become odds += ((odds * 15) / 10);
* As the way it works is takes whatever value is on the right,  and applies
* the operator to value on the left...actuallyy nvm that would actually be larger than if it was multiplicative
* my mental math was wrong, leave the function as it is, just add more status 2 & trap effects
*
* Set wild double battles, and allow catching both mon
* cleanest way is to store both mons data for the pokedex beforehand  (based on battlerId)
* and clear whoever dies.
* Then at end of battle do pokedex entries for both, make it loop
* just like other functions do, so have create function buffer mon
* to value or var used for speciees data zero out value if mon dies
* then have pokedex loop through functions baseed on var/value if they aren't 0
* -Progress-
* 
* game loop improvements, game is old, people are used to games being faster now,
* I want to fix that, on top of addressing the issue, of not having reason to grind.
* it needs better time/reward investment
* with my changes you'll spend more time catching the same mon, (or some people will)
* so I want to add arceus style improvements where you receive items for releasing mon.
* chose from multiple fields to add, at their own odds ev items, the items the mon gives/has a chance to hold (make sure every mon has some held item itemCommon & itemRare)
* and other random odds ends to sell,  but keep in mind also plan to eventually setup timed events with nuggets other item give aways for economy management.
* as well as plan to make all trainers rematchable which would make it easy to get more money from grinding battles.
* plan to do via time or a stepp counter, when condition is met, reset trainer flags of all npc on map.
* this would also give rise to need to use b.o  trainer repellent from pewter, further setting the realistic world economy, etc.
*
* thought on ev system, for most its too grindy, but grind isn't always bad it needs proper balance.
* and balancing your grind doesn't always mean to reduce the grind, but to improve the reward/effort ratio, and have it more seamlessly integrated into your core gameplay loop.
* the default system forced you to engage with the game in a patently abnormal way, searching out specific mon and just grinding them relentlessly before you could continue with the main story.
*a method that would have allowed you to continue as normal would be awarding evs for natural progression through the game, and since I can rematch trainers that's earsier for me to setup.
*my idea is beating important trainers, ace trainers, gym leaders, (and potentially gym trainers)  evil team leaders/admins  would net you battle points
* which don't go into evs, but allow you to allocate them specifically later, setup like exp, loop entire party, check summary screen, potentially put where had total exp
* if can fit it with needed ability slot changes
* ok it can't fit, BUT  what I can do is have the exp text change with pressing ctr to display evs for the mon,
* change it to show BP for battle points, and replace the number for exp to next level with amount of bp that mon has. pressing A
* will take you to stat info, same as move info is for pressing A on move page, here you can select the individual stat and 
* pressing using the dpad will alocate allocating  battle points,  up down is intervals of 1,  left right is intervals of 10 
* and once set they can't be removed.  so will need a confirmation message,  Pressing B will prompt to exit, if amount of battle points is different from before allocating/pressing B from within menu
* will prompt confirm message,  if its the same then no points were allocated and there is no consiquence to exit again, so just let the player retufn to menu normally
*make sure to setup outline same as move selection, press A to enter menu,  red outlined box appears at default top position, press again for it to blink and show selection.
*from there stat is selected and you can actually apply battle points.  
* Pressing B once, removes blinking and takes you back to stat selection  allowing move to next stat go to allocation phase.
* Pressing B again from ostat selection prompts the confirmtation message, not the first one.
*
* 
* -new idea make command for bs that goes before move animation for moves above 
* base power 1, give auditory alert for mon hitting for big damage
* i.e if mon hits max damage roll, or rolls a crit, the attacking mon will growl
* before/as the move animation goes off. either do a wait state or do a small time wait
* before animation comamnd to hopefully clear the audio channels
* 
* use PlayCry_Normal(GetMonData(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_SPECIES), 25);
* 
* would require rolling adjustnormaldamage & critcalc command into one, which 
* honeslty makes sense to do, just put crit calc at bottom  and change type of
* ApplyRandomDmgMultiplier so it returns randPercent  then I can just do a check for
* if is_Crit (critmultiplier >1) or randPercent == 100, or >=95 play growl/cry.
* -could get annoying but also a good qol perhaps don't use normal cry but a version of it
* maybe shortend version of it/faster but also lower pitch so it sounds normal? 
*
*nother new idea preview damage?
expansion has a  battle history component that saves moves and estimates ai dmg.

and othe  jrpgs, have the mechanic of being able to see how much dmg a certain attack would do to the enemy health bar.
and sometimes expected dmg you would take.

so I had the idea if we could get that!
we select a move and target and we can get the selected enemy health bar to flash with the amount of predicted dmg they would take
either make it perfectly accurate (somehow), or make it based on low roll or max roll dmg.

then on the defensive side you could  pick a known enemy move, and try to predict damage taken,
maybe even pull up the player party screen (or something) to show the estimated dmg for your entire team for said move.

that way pivot strats could be more intuitive, and you could make enemy ai more complex far as switching
without it being too cheap since the player can lookup their move (assuming they used it before in that battle)
so we also have some information, we can make use of.

thought process behind not making the prediction perfect is to leave somehting up to high skill/high knowledge players
and let them still have reason to run calcs, cuz people enjoy that.

edit will make display the low roll dmg for player prediction switching, so calcing the high roll is still needed for full info
I guess display max roll for the player dmg to the opponent?

plan is have it as a toggle, press L or select in battle, for info mode to get predictions
then press B or L while in info mode, to return to normal.
ok so press L while target selecting will display dmg predictions on target so will need check target type for move, to tell what to show
same for mon damage flicker thing

then would need figure out how to pull up history for a selected target and then pick a move to run dgm calcs with,
and have it show the entire party healthbar to show how much dmg said move would do against everyone.

I could specifically save it for pivoting, like the trainer considering their party given what they know of the enemy. ??

* 
* potential idea need recharge gems with element stones instead of removing item, after gem is used up in battle,
* add item to bag, that is a grey gem,  spent gem something,   late game wont need evo stones so this will be new use for them,
* Add Lore Gems captured power of the elements, from crystalizing/forming in environments near evo stones
* which is why they are able to boost the elements,  will make require two evo stones,  so elements
* that don't have a specific stone evo, can use combinations  i.e dusk/water for poison maybe
* fire gem  2 fire stones  stuff like that.     Gem collector that does this also place to buy gems at highish cost
* to make this sytem worth while   
* able to farm gems and fossils from underground  or just inside different caves, prob inside caves,
* save map space, simpler and gives reason to back track
* 
* other thing adjust play speed without needing speed up, so music doesn't get changed.
* make options menu flag for increasing movement speed. can reset to default from options menu like text.
* best case can move further without changing animation so it still has that laid back feel.
* have to ensure you still move actually occupy the space/x position or would cause object clipping.
* 
*  Also adjust move animation speed.  could potentially shift animation by a multipple so they all change equally?
* file battle_anim_scripts.s  look at commands for battle anims as well
* change move speed, text speed, and animation speed,
* make new faster but not instant text speed, already have how to, in screenshots
* 
* 
* plan to be able to catch every legendary one way or another, initial idea was they'd randomly show up in cerulean cave after mewtwo
* but that would be boring to always just go back through the same cave so instead.
* 
* have multiple different options for finding legendaries, cerulean cave, another hidden cave, 
* port mirage island but with better mechanics, i.e will appear once a month at midnight for one hour with an npc telling you if its available
* or when its coming each with their own set of legends to spawn. the rarest would go to mirage island the mystics i guess
* things like guzzlord could go to cerulean cave the dark or bad ones
* -could also put mirage island alerrt in space time upgrade for dexnav from time events
*/

goto POKEDEX_CATEGORY_CURSOR_DATA  //for setting up category page in pokedex and fixing outline issue
goto POKEDEX_PAGE_FUNCTIONS
goto CREATE_POKEDEX_PAGE // all values for creating pokedex page  DexScreen_PrintMonFlavorText  is function for dexx entires
goto PARTYMENU_GRAPHICS
/* Found species names were being slightly truncated in some cases, comb through added mon ppost gen 3
* all names fit current POKEMON_NAME_LENGTH  limit of 10 + 1, but some are shrunken to fit, 
* so edited party graphics box & was able to add 1 additional space no more.  need to increase name length by 1 to match
* 
* still has issue finding in battle values to adjust, need to move over gender icon
* found it ,its all in UpdateNickInHealthbox  -increased name length need to expand window width and adjust other parameters that 
* take mon name  i.e summary screen, & naming screen - playere health box works enemy can't figure out yet  
* - progress - fixed enemy health bar neeed to setup for the other places and test rest of party slots- DONE
* 
* found curreent gen name limit is 12, so need add ANOTHER space and will need to figure out how to move health bar to work smh
* plan to increase width of healthbox in battle to make names fit, potentiallly do same as category pokedex
* and have it generate different size box based on pokemon name length, just so it fits/doesn't look too big
* 
* name limit 12 is cutoff in pc, and I can't make the graphic bigger as
* there is no more space so instead I need to make the font smaller.
* 
* (new idea in place of markings put ability name of mon in selection on pc screen)
*
* also my need to re-capitalize species namees as well. it prob looks fine in emerald but for fire red looks a bit off
* espcially on some of the wider characters like M  -DONE  (unless I decide to go in and redo the font to look better myself that's it)
* 
* need search repo for values [10] & [11]  and replace with POKEMON_NAME_LENGTH & POKEMON_NAME_LENGTH + 1
* as for some reason gamefreak used fixed values for a lot of the game rather than the constant  - DONE
* need fix POKEMON_NAME_LENGTH expansion issue first, as it could just spread issue throughout even more areas 
* found new issue, pokemon names are using full buffer space even when name is shorter (or I made window too big?)
* need test later to fix forgot how window value works, I thought name & lvl were in same window
* so a shorter name should move lvl values over but maybe not,  consider change to append, so it'll add on to whateveer
* the name string is instead... -
* 
* 
* redoing species name expansion
* need adjust naming screen, parrty menu & pokedex fields again
* new change add all 3 category page images I made, and make
* each their own define and have game use species name length
* to decide which to use, name length 11 use mid, name length 12 uses large
* everything below 11 can use the original have different window dimmenssions for each
* 
* found similar issue potentially with healthbox and naming screen.
* adjusted naming screen for name length but now player is off.
* need to make it swap bgs somehow for player vs mon naming screen some kind of callback or something
* 
* same thing forhealth box, want to make it adjust based on use,  so size of name length use different width healthbox
* 
* for party menu move left column mon pic up and left,
* move name over 1 character,  same for right column 
* 
* considre swap placemnt of type icon and pp in summary.
* did still has issue, only solution I see is put type icons on separate windows
* buffer all of them to each window, and just use if conditional
* to tell which window window to display  or just buffer the same thing to all windows
* to all windows and then just in the funciton that puts the window up
* I just swap the window for each instead of using move window 5.
* 
* found just enough room, to fit move names with type icons, but need to adjust bin file for graphics.
* as needed to raise pp values with new move name placement for moves 1 & 3.
* was able to confirm I need to raise those spaces up 3 pixels to fit pp values.
* after that will need to make the space from the bottom smaller to make move name not floating.
* appears to be double the space for pp value? will balance out since moving in opposite direction so won't look too off.
* will add 3 pixels of white space to top of window, then will start with removing 6 pixels of white space from bottom of window
* tested its 3 & 3 perfect equal add 3 whitespace to top, and remove 3 from bottom.
* 
*/ 

goto LOWHP_MUSIC_FUNCTION //don't know how lost connect for thsi but its fixed now

goto BATTLE_HEALTHBOX_DATA  //seem to be true source of grahpics
goto HEALTHBOX_LOGIC	//health box for battle, enemy values at bottom of function, need add exp bar/values to that section.
goto EVOLUTION_LOGIC
/*  want battle evolution for player and opponenet for enemy need to work out how to give them exp.
* after they have exp need set function to make it feel real that they would level up i.e they aren't starting from 0.
* for that make random function that would get their needed exp to level and then random divide that by either 2, 3, or 4 to increase their chance of lvl in battle.
* player can use this and the above function to evolve, but enemy needs a specific one, that won't take out of battle, make it so if they can evolve they will. 
* use CFRU mega evolve animation for opponent. -
* 
* For getting mon to level up at least visually use healthbox function.  to make random level up
* decided use variation of exp function but insteead of using exp basd on their actual level generate a lower level.
* so thy need far less exp than a full level to make it seem like they're almost leveled up.
* (prob need to make exp bar linked to value returned by level function)
* to make a false level I'll make a function that'll return a random value between 5 and I think half their actual level.
* Random () % ((mon level/2) +5)    witha min exp for level 5, defeating practically anything in the game would be enough to level up.
* [thought normaly this effect would go away could attempt to find someway to store and make permanent? do the whole reverse rogue light thing?
* [enemy gets stronger...prob best to have it reset and not be permamnent...unless I want to make a fuck you hard mode] lol make hardmode flag XD
*
* level = GetMonData(mon, MON_DATA_LEVEL);
            exp = GetMonData(mon, MON_DATA_EXP);
            currLevelExp = gExperienceTables[gBaseStats[species].growthRate][level];
            currExpBarValue = exp - currLevelExp;
            maxExpBarValue = gExperienceTables[gBaseStats[species].growthRate][level + 1] - currLevelExp;
* 
* 
* Check if time works, add clocks to fire red setup hourly
* daily, weekly, Monthly time based events.
* Periodic overworld Weather conditions
* map based terrain and seasons as well
* Treat entire map like a globe, with different climates so differeent areas experience different weather baseed on season
* Then have different encounters based on season, mon migration if a climate shifts cold they move to a hotter area vice versa
* -Progress-
* 
* ABILITY IDEAS -
* 
* want to setup mega marowak themed after ancholysauras
* thick armor plating stronger bones
* new ability idea, is um damage reduction  I think 20%?
* 2nd ability turns every special move into a physical contact move as marowak learns moves like flamethrower but has trash sp atk 
* also good for machamp, inspired by Mashle believe will call elemental muscle - DONE
* hmm may actually be able to do a special animation for it,  like fire punch, can add the fist animation to the end of moves if ability is e.m ?
* would need to setup new macro?
* think can do same thing I did for truant and make new bs that will play an animation I want.
* think can do punch/foot animation and have it play the punch animation during or after the normal move animtion
* would need to setup like I did for multihit, do ability check and then play animation
* idk if I can gete timing perfect, but hopefully would work
* 
* ability liquid metal, for regi-steel effects of light metal, but also reduces damage from contact moves, like fluffy does
* not sure if will do full 50% reduction or do a 33% reduction instead. prob the latter
* could make it a metal absorb ability?  idk if I'll do this, would be interesting as it doesn't exist
* but not necissarly good as steel is so good as a defensive option not an offensive one.
* instead decide to mix in clear body effect - DONE
* 
* //Glacial Ice for regi-ice negates fire damage also combine with ice-body effect to heal during hail and add low chance to freeze on contact
    //make sure stacks with hail effect freeze chance boost 
    //think may also combine with volt absorb so ice attacks heal it, so its immune to fire & ice, but ice heals it - DONE
* 
* Rock Collctor (name pending) for regi rock //rock version of volt absorb, that also absorbs stealh rocks
* think will have it also heal if absorb stealth rocks
* Anthroyd came up with name "Erosion"  will use that.  wearing down rocks to use for healing minerals- DONE
* 
* note change stealth rock damage scaling, above neutral damage rather than 1/4 on weak and 1/2 on dual weak
* change to 1/6 on weak and 1/5 on dual weak. - done
* 
* for switch logic want to keep battle system as close to base fire red as possible,
* so mon almost never switch, but I want them to work logically with abilities
* so they should switch if they have an ability that works off of switching out like regenrator.
* 
* if opponent can kill them that turn switch, -(yuo can't kill them and/or they are faster
* otherwise stay in and try to kill, if after kill is at or below 50% hp.
* switch, basic regenerator/switch ability logic
* 
* -check adjust send out logic see if can filter for mon with a switch in ability that would be viable
* 
* purifying aura, Suicune Ability similar effect to healer, also mon removes all status effects on itself & allies at the end of turn
* in doubles heals status of ally on switchin as well. -DONE need test
* 
* need misdreavus mismagius ability to replace levitate, 
* could be trickster as mon is known to be a trickster and enjoy frightening people
* has relatively good speed so could be has a chance to make oppponent flinch when they attack
* as if they were popping in and out or maybe call it fright
* think would apply for non damamgnig attacks as well for extra utility,
* so just any attack that targets the opponent/doesn't target the user
* yeah I like that if targetted by this mon has a chance to get flinched
* possibly put in accuracy check?    think may also give pressure as a hidden ability
* 
* might also setup some ghost moves
* that can paralyze  or give it glare idk, something ghostly stare?  
* 
* -ok yeah shelving this ability prankster works fine, and over abundance of flinch would be un fun
* 
* look at danny phantom abilities? ghostly wail XD  base 120 dual hit, or base 100 ghost version of heatwave, well can make 120 I guess since ghost doesn't get super?
* bp 10
* 
* BUFF for Golisopod Emergency Exit, rather than it being the same as wimp out,
* keep main effect but tweak it to be more offensive instead of force switch on hp threshold.
* make it so you do a hit and run attack on your next turn.
* Upon reaching switch threshold, your next move gets boosted priority  (possibly make new status for it? like focus energy?)
* to guarantee goes first, similar to pursuit but lower, and then you switch out after attacking.
* 
* This gives multiple new avenus of use, can better plan your switch, have a chance to knock out the enemy,
* giving you a free switch, and just overall allows you to actually get some value out of the ability
* 
* Concept is hurt and decide to run, but you full force steal off on the enemy to get the last lick in.
* Think, may raise attack one stage as well? can do like strength should work fine. (think would also addd full status clense)
* [could do a whole false bravado thing, will play its growl when hit hp threshold maybe do flash red, then atk up animation and clear status*if statused*
* some kind of text message, (takes place in end turn, that hp fell.) then set emergency exit status, in same place as nuisance add priority boost for status
* last thing is figuring how to make it wait till end of next move to switch out, maybe set argument of next move to hit escape?
*  also since I want this to be an attack thing, think may setup like taunt where can't select a non damaging move during status
*.gDisableStructs[gBattlerTarget].tauntTimer = 2 - guess could do this
* 
* [total effect, if atk less than stage 6 set to 6, (same logic from crit effect), growl,  raise attack stat, set status1 0 to clear, remove confusion infatuation
* set emergency exit status]
* 
* hitescape uses effect 100,  will set up like traps where the effect will be certain, that way i can set hit escape without needing to worry about
* secondaryeffectchance of the move -  ok did that , but realized I can't use that for emergeny exit, it'd overwerite the effect of moves
* that have their own arguments  maybe do a flag check, set emergencyexit value to 1, and then have it decrement from move end 
* and auto switch out when its at 0.?  can set up switchout battlescript, using hitescape
* 
* consider make leech seed work like anime, where it wraps up the target
* meaning it would be a trap, preventing the enemy from switching, and a good buff to grass types
* as only they learn it, and only theye are immune to it. -
* 
* could do it but also may be too much, since switching is a big part of the game, but eh I'm just making traps actually viable
* nah I think I will do it, won't much change how players play the game (since enemy doesn't switch), and will just make grass better
* 
* revampt setup for new traps put infestation in CalculateBaseDamage by damagehelper
* will need to set like intimidate, so they need be statused AND not already aflicted by status i.e setup flag just like intimidatemon or switchindone
    //drop stat if flag not set, then when status is over need reset stat value so if not statused and status flag set, raise stat and remove status flag.
    //specialstatusInfested //will need for all trap status that affect stat stages
* 
*/


/* new megas won't have +100bst but instead will take a stat average value that is strong
* like say 615 or 630/635.  and will either reallocate or add to existing stats to get there.
* 
* most legendaries have base 600, and then others go up to 680  psuedo legends are also 600
* 
* mega marowak should have higher defenses (sp def too  since its armor can take most things) atk & bulk
* 
* rework existing megas stats by this standard -
* 
* also remember plan for new version of megas, instead of a temp buff, it'll be a special difficult to acvhive but permanent evolution
* you can have more than one mega on your team but it'll just be much harder to get them to mega evolve,
* and also you'll only be able to have a single mon of that species to mega evolve,  thing of it like ash greninja
* a mon you have a very deep bond with you go through trials with to be able to evolve stronger.
* 
* So you have to decide which mon you will go through the mega trials with, even breeding specifically for that in mind
* if you want the best possible outcome.
* 
* Don't forget plans to revamp breeding mechanics, using as a menes to get alternate forms
* people don't often use it anyway so may potentially get rid of egg groups, if skitty wailord works it can't make too much logic.
* will make breeding easier and remove some of the need to use ditto exclusively - note keep nidoqueen in cna't breed group for lore/makes sense
*
* could do based on personality instead? ok keep base effects for same species, maybe also same type like each other
* but for mon that would otherwise fall in diff egg group/ could make it work off personality to randomly
* decide their compatibility? - or just let everyone work for ease of use
* 
* other idea, be able to access pc from breeder desk selection, to remove need to go to pc and put
* mon in your party JUST to put them in the daycare. major time saver and convience feature
*  
* Consider increasing day care from 2 mons to 6, i.e 3 pairs of mon can be put in at a time.
* do some menu work and logic work so there are 3 plots/sections of the day care
* each plot/slot is treated separately and can house 2 mon that would be a breeding pair.
* 
* that way you can generate 3 eggs at a time. 
* and with inclusion of the opal egg incubator,  egg management would be FAR more efficient
* 
*/
goto TRAINER_MEMO_SUMMARY	//pokemon_summary_screen.c, scroll down for trainer memo functions
goto SUMMARY_GRAPHICS //graphics.c all graphic files, but this spot is for summary screen

goto MOVEICON_ABILITYDESC	//function for displaying move icons & ability info in summ screen
/* 
* Upgrade UI menu for new mechanics. Expanded move description & ability description & move name fields
* Adjusted summary screen menu for trainer memo, &\ move summary/info page.
* Need to find a fix for move icons misalignment in moves pags 
* rquires direct editing the tilemap to fit the icons/tiles - DONE
* 
* also move learn slot is not wide enough long moves in move learn slot get cut off - DONE
* 
* Also plan to add new string/logic for trainer memo box, for nuzlocke idea
* Where pokemon would die and be replaced by ashes when taken to pokemon center
* Which can be placed at pokemon tower in lavender town after plot point 
* for a chance to resurect your pokemon based on friendship -needs open slot to work
* Otherwise it'll serve as a record of your lost mon.
* if viewing dead mon in tower bring up the summary screen for them
* Pokemon ashes should store all mon data, as if it was the mon itself.
* with 3rd line of trainer memo, displaying where they died,
* i.e "Lost in *location* at *lvl* to *cause of death-either mon to kill it, or status that killed it.
* to severe burns, hypothermia, poison  burn poison & freezee/frostbite are status1s that do dot and can kill
* if left uncured/healed for a number of steps after mon dies to or with them.
*
* plan was revise lavender tower event, make head priest be posessed by evil spirit
* make it final boss of lavender tower, rockets to show off nuzlocke and revival
* mechanic, fight priest at top, with ghost team, defeat him,
* he says S-s....sa-ssave...m-e... 
* the screen flashses and then you're thrown into another fight,
* this time just a mismagius lvl 40 say something bout dark spirits 
* were drawn to the evil deeds of team rocket after cubone's mother was killed.
* this is a sacred place of renewal and resurection life and death exist here
* blah blah, to bring balance things must be made right.
*  priest goes to center screen flashes and marowak sprite appears, apparently resurected
* cubone walks up they both cry, and then walk off.  
* then have marowak appear in bottom left house of  lavender town along with the cubone
* change text of trainer in house to fit 
* This marowak just appeared here idk where she came from but cubone seems a lot happier now
*/

/* 
* 
* 
*/
goto LOGIC_FOR_MOVETYPE_CHANGE  //battle_main.c things like ion deluge pixelate etc.
goto TYPE_DMG_MODULATER //(inverse world ability logic/ sets the multiplier based on type, and handles effectiveness sound/move result
goto TYPE_AND_STAB_CHECK //battle_script_commands.c  type calc also where s.t.a.b is handled
/*
* plan buff normal types, their gimmick, is being highly adaptable for their lack of weakness and resisted damage
* but power creep(and new move restrictions) has made them lose their place, make sure pure normal always has very diverse move pool to chose from
* also as they lack stab, instead of trying to give them all insane stats to counter will instead make new jack - of - all - trades gimmick / effect
* for normal types   rather than the specialing of same - type - attack - bonus by being a normal type you have adaptability to do everything,
* so will come up with a smaller power bonus exclusively for normal types that applies to whatever type of moving they are using (excluding normal moves)
* that would stack with stab should they be a dual type - DONE
* inspiration from wolfeyvgc
* new effect calling it, jack of all trades  and gives reason to want normal as secondary type  25% non normal type damage buff
*
* changeed super multiplier to 1.5, considering change to 1.6 and changing stab multiplier to 1.4, think leave adaptability where it is 
* double check muscle magic swap doesn't affect things that already shift split, i.e psyshock hidden power, well then again them being physical would be best anyway
*/ 


goto PICKUP_LOGIC   //out of battle buffs done, moving to in battle buffs - need fix sets item but isn't random currently only setting stick?
//Changing pickup to not require empty item slot, do same for pickpocket, just put item in bag think done, should work for all Stealing moves

goto SPECIAL_TRAP_EFFECTCHANCE
goto STAT_AND_DAMAGE_ABILITIES_ETC // pokemon.c function for ability and item effects that affect damage calc

goto ENDTURN_EFFECTS    //battle_util.c   affects that take place after all battler turns

goto MOVE_EEFFCTS  //setmoveeffects move logic in battle_script_commands.c DONE   need update canbestatused functions in battle_util.c with my custom logic to be used here
//ex. CanBeParalyzed  will just make things easir to look at

goto ATK_49_MOVEEND //battle_script_commands.c  move end  still to do   vsonic

goto ABSORB_ABILITY_TARGETTING
goto STAT_ANIM_W_ABILITIES
goto STAT_CHANGE_ABILITIES
goto ACCURACY_BASED_ABILITIES   //other ability logic exists outside battle_util.c  make sure to go over all ability effects
goto ABILITYBATTLE_FUNCTION	//	battle_util.c function other more complex ability activation logic.  STILL need to update   vsonic
/*
* Setting up new effeets for absorb abilities
* make all work like lightnight rod and change targetting to draw in moves  -effect Done, working on messags and status effect
* counter balance is only does that if ability mon isn't statused //including status 2 cofusion & infations - think Done, did only confusion not infatuation
* 
* need to add new abilities to mold breaker and other ability exclussion lists
* 
* New signature ability for suicune
* purifying aura, similar effect to healer, also mon removes all status1 effects on itself & allies at the end of turn
* shed skin but not random  in doubles heals status of ally on switchin as well.   replace pressure think can use plus minus ability effect
* nvm plus/minus use field sport effect which is both sides of field I just want that prat to effect your side so partner on switch in
* plan to make on all status exlcuuding traps, to make it a great team mon for abrorbing mon or intimidate mon who's abilities get canceled
* with status 
* 
* tweak idea, to make bit less overpowered, will just do status1, leaving confusion and infatuation as viable options
* rather than not having an out/counter - DONE  *need test though
* 
* for setting up rattled to activate on intimidate add check for gSpecialStatuses[battler].intimidatedMon = 1;  if true i.e == 1 
* activate rattled
* note- think done
* 
* fix moves mirror move, copycat etc. sketch monotype to use lasthitby  value, rather than enemy or last used move for target, so it doesnt fail
* if used first. -_-
* gBattleResults.lastUsedMoveOpponent       gLastMoves[gBattlerTarget] instead 
* adjusted copycat, sketch seems to already work optimally, mirror move is very complex for some reason will need to take time to study
* also note monotype will take sketch place,   sketch will essentially be mirror move +
* 
* smeargle changes new moves -
* stat boosts, and change sketch to temporary move copy
* similar to ditto's transform, move is replaced for duration of battle, and pp is updated after
* moved copycat original effect to new move monotype
* change sketch to raise all stats 2 levels or all but speed stat?
* this way it can overcome the disadvantage of using another mons move with worse stats, and without type advanage.
* that way smeargle is turned from a failed artist, into a type of sevant that can improve on the original.
* increased priority of sketch, so I'll not increase speed stat
* 
* for the stat buff, think I will do like the high crit flags,
* rather than putting stat boost in battle script, could make ability just for smeargle,
* and have it work based on flag, check, for an "artistic move"  either sketch or monotype
* if either is used and stats aren't max, max out stats  (could be just offense stats) -similar to competitive & defiant
* 
* that way has a chance to actually do damgae with copied moves.
* for extra versatility can add assist to learnset to for more options.
* 
* //since I'm changing sketches effect to be temporary
    //and the current move has outside battle uses.
    //I think what I'll do is copy the current effect
    //and move it to another move I'll call
    //"hard copy" or something.

    //that move can be relearnabe to pick a moveset
    //and keep the 1pp thing.

    //ok I've decided I'll call it "Monotype" from the one-time art
    //print process 
* 
* buff to make magma armor unique, rather than just naother flame body (specially since I gave flame body freeze immunity
* first idea is give it incinerate effect, where it destroys enemy held item on contact
* othre idea is sp def damage reduction from being surrounded in magma shield //think i did both? yeah
* based on bulbapdia reading make function for if item can be removed/stolen
* 
* finish ability competitive buff, gave weaker version of guts to go with normal effects since stat drop is very situational
* 
* buff pidgey line, according to Zen Mode YT changes, give u-turn and my move dive bomb
* gave scrappy, think setup correctly so scrappy should work? need test
* 
* attempt make //mirror move use battlehistory to make it turn into any move already used in battle, that it doesn't already know?
* want to make it work like copycat, where the mirrormove turns into that move, either for the remainder of battle, or until switch out (in case you get a bad option)
* that said it would doubley suck if you got a good copy, switched out and lost it. so think will make it last for battle duration
* 
* rename sonic boom sonic screech, and make new move sonicboom, which will be special flying move think also do speed boost, so equivalent to flamecharge
* combine animations of agility, and wing attack, for new animation - DONE  need add to more mon, flying types high flying speed
* meant to be a little competition for fly
* 
* since sonic boom is something usually done while flying fast, but the move sonic boom, isn't learned by flying types, and has more to do with sound than speed
* 
* ideas from kip kebab new moves.  Forge (metal) change own rock type into steel, + 1 defense  - great for golemn-line /onix especially with my steel effectiveness change
* same with type loss effects make type last for battle duration so you have to think about using it. as single use, potentially change to +2 def boost
* yeah makes more sense as a single use move that in case of pure rock would change both types to steel, rather than just one. as making you rock steel would usually just be worse
* 
* Shrapnel Salvo (steel) 35 dmg, low acc, hit 2-5 times  - use spikes animation 
* 
* synchronize revamp keep normal bility for umbreon but otherwise replace with "empath" copies stat1 of synchronize but also copies stat drops to enemy.
* need look at mirror armor bs and moody bs, think secret will be using 2 statbuffchange commands - 
* 
* fix ditto make imposter its only ability (or just but  speed stat so it can transform easier) - change, with buffs to keep iv/ev make this its own ability counter-form 
* change imposter to be more than just a free transform on switch.
* instead make it transform into a random pokemon that resists the typeing of the target.
* will be pretty complex, need to use emerald way to read type effectiveness 
* loop through mon of type that resists, potentially need to put in list, but don't want to.
* /note found conversion2 battlescript alredy does that  atkA6_settypetorandomresistance
* so would need to run that, and then transfer type set to that of to mon to look for from loop of all species.
* its a void function so it doesn't return anything, so what I can do is, use the command to change dittos' type
* on entrance, and then use a command to check battler type, and then loop the imposter function/command to use that type
* 
* The copied stats (Attack, Defense, Special Attack, Special Defense, Speed) include the final values (as seen on the summary screen)
*  as well as the target's base stats, individual values, and effort values. (change this 
* -so it copies all the enemies stats  but keeps its normal hp stat ( so 9/10 its just an inferior version)
* also copies the enemies ivs and evs when most have 0, that seems horrible...  so change that so it keeps the users ivs and evs. - DONE? need test
* -appears wasn't working, not properly copying species/stats was just doing moves, didn't get target ability etc.
* working on retooling function having pointer errors -DONE changed to keep enemy ivs as to reveal their ivs along with ability
* 
* better idea for ability name thanks to Anercomp,  rathr than counterorm ability name will be "Inversion"  pairs well with imposter
*  base transform/imposoter logic seems to work, needs update hp box to show changed hp
*  also using setmondata seems to cause an issue where stat changes from transforming persist post battle
* I think the fix would be to make new "calcstat" define for my transform function and rather than
* doing a setmondata, I use getmondata and assign it the calc value  
* so new  calcstat ends with getmondata blah blah atk stat) = n
* 
* doing that I think I'd need to move the battler stat assingment into same function actually can just directy set battler stat with calcstat function
* should be much simpler
* 
* but doing setmondata makes the values show up in summaryscreen which I like, so I may just
* put a recalc in battle_main for battle end/switch out and or faint to reset stat valus for transformed mon, well can just do general stat recalc
* for most it would result in a net 0 change/do nothing, but for transformed mon etc. it would revert back to normal stats
* see about doing ability same way so it shows up in summary screen.
* 
* ok idea think I'll need to setup a "flag check" so for imposter etc. use if switchinability not done
* and then thing I'll need to add an extra check for transformed put at end of  transform bs.
* that way it won't repeat/recalculate everytime I attack
* 
* so full logic normal summar scren implementation then conditionals
* if ability that changes ability and switchin ability not done)  use target for ability check
* 
* transform abilities all use transform bs command which sets status trace also sets status
* if I link the sumemary to status it will auto revert when switch or faint as status2 is cleared.
* 
* check may potentially need to while,  actually no, if set data auto updates summary it should auto swap as is
* would just need skill swap status
* 
* there's al lot more moves/abilities that change ability I'd have to set
* but duoble checkd summary screen and all I need to do is change the ability value assinged to abilitydata
* 
* so just make a function that tells it what ability to return and assign it to abilitydata
* do conditional logic for moves should be simple as lastusedmove that landed succesfully/lastlandedmove
* as switch case,  and in each case just set return ability that move changes too.
* 
* ...or is it as simple as just doing abilitydata = gbattlemons[gactivebattler].ability... o.0 yup
* 
* else if (prob put this first actually) status 2 & status2_transform and not transformation done) use target for ability check
* 
* else normal abilitydata set
* 
* oh wait I can just use glastusedability since when they activate it goes there...
* 
* note switchInAbilityDone replaces intimidate special status in emerald, saves room and is easier than jus tmakign a bunch of status
* 
* 
* may also do for trace and other ability swap effects, since doing set data to ability rather than just swapping battleer ability seems to make it
* visible in summary screen would be great qol.
* 
* keep some ability for ditto other than imposter and inversion, so I can actually target my transform ability for strategy.
* since I'm fast...don't need to be fast could just make transform a priority move facepalm.  its no longer  a liability
* 
* just realized with these planned changed I've actually given ditto an entirely  different niche, 
* it can be the perfect mon for nuzlockes/catch testing, you can confirm the opponent ability just by transforming
* and honestly it'd prob be even more valuable if rather than your ivs,
* it displayed took the enemy ivs for stats, that way if you know the mons stat distribution
* not only could it be an ability checker it'd also be an iv checker.  (but it'd take some skill/knowledge which is just the type of thing i like)
* would make ev training ditto that much more important but higher benefit, think I'll make ditto an early game mon, 
* 
* note checked many mon learn grass knot for no apparent reason steel types fairy types  physical attackers etc.
* so think for physical attackers replace grass knot with branch poke or bullet seed, leaning more toward the former.
* 
* oh wait it gets those as a tm so guess I'd need to make branch poke a tm 
* //buffed low kick & other weight based movs so base 40 power kicks in faster, at 5kg rather than 10
* 
* -for summary screen change colors for nature stat display, I never liked red/blue it didn't make senes to me,
* instead changing to purple and light gray, contrast is color vs non-color making it more obvious which stat is the boost, and which is the draw back.
* color handeled by sLevelNickTextColors array
* 
* will finish logic after pickup, as its essentially the same functionality, loop array of values and pick/assign one based on logic
* 
* rock head buff like iron fist boost power head based moves  headbutt skull bash etc.
* moves list: head charge, head smash, headbutt, headlong rush, iron head, zen headbutt, skull bash - DONE
* 
* //revampt skull  bash along with other "moves w charging turns" they're outdated
* charging moves to change (that I haven't already)
* geomancy- signature of xerneas, make single turn move, but give fail chance if used repeatedly like protect likes, but higher odds
* 
* meteor beam- do sp atk boost before atk, like I did  strength boost, then make work like hyperbeam you need to recharge after so 1 turn move
* 
* skull bash- defense boost into recoil move potentially raise def 2 stages, need check how recoil dmg is calculated see if it bypasses defense
* recoil uses gbattlemovedamage and seems to bypass defense checks/damgage formula dmg vs defense
* is done in dmg calc bs command specifically with the calculatebasedamage function from the pokemon.c
* 
* 
* if would need to setup new recoiol effect that takes that percentage of dmg done
* and lets it run through the calcbasedmg or some equivalent of the defense side of it.
* with itself as the targeet, as runnign through same thing twice would just reaplly dmg buffs,
* rather than do drop defense based drop off of the original dmg.
* 
* ok looks like need to make offshoot function put into setmoveeffet in recoil arguments
* to take the calculated dmg and run it through defense checks, note 
* should be typeless dmg that makes contact.  i.e if user has fluffy and did recoil 
* as its a contact move recoil dmg taken would be reduced.  stuff like that
* 
* notes on defense setup for rrecoil, pass gbattlemovedamage into a version of defense side of CalculateBaseDamage function -     
* confusion dmg runs through damage formula and is affected by atk stat and defense
* confusion hit uses  
* gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker], &gBattleMons[gBattlerAttacker], MOVE_POUND, 0, 40, 0, gBattlerAttacker, gBattlerAttacker);
* function has type and power override, if I change type to sound or mystery it'd be neutral for all
*then potentially see if power override lets me slot in my own dmg amount so I could use hp delt by atk, or quater gbattlemovedmg or something?
*
* comtinue adding notes...
* array won't end well if size doesn't match random value, so do just like, starter selection random % nelems 
* but I'm making the list with the function logic,   so I cant do array nelms
* so read target's type set that as attack type then loop through entire species and if they would result
* in a not effective or no effect result.  I could add the species to list?  and then nelms the list and loop'
* over that to decide what it transforms into?
* need check if its possible to build an array from a function
* EDIT--
* try explaining agian, check target type, if target 2 matches target 1,
*  make one list and set that as atk type, and loop through all the species that
* have a defending type that  are not effective or no effect result.
* 
* Then randomly pick a species wihtin that list to transform into       -for conversion & inversion new transform ability
* 
* If the type 2 doesn't match type 1, make two lists of the above guuidelines
* select a random species, and then compare the species for each list,
* if the species are identical transform into that species.
* 
* if the species returned is different, random % 2 to pick one of the two species to transform into
* 
* I may need to do all the logic within one function rather than being able to make an array from the function
* as it looks like arrays have to be defined in size at build
* 
* So I think I need to create the list loop the list, and passive the species value to transform into
* to a variable, all within the same function...
* 
* USE type chart somehow
* new logic, like trace/intimidate pick a random target on enemy side,  if type 1 & 2 are the same use that
* otherwise loop one type then the other, and look for  a type that overlaps, that would result in a not very effective result
* if it finds a match for both use that, otherwise randomly chose from the combined typings and make mon mono type that
*
* -WITH ADDITION of ee logic for type chart just use that function, which should auto check overall type effectiveness
* actually in battle_main? or field_player_avatar ro something I made functions (in starter setup file) for checking effectiveness
* should be able to just use those
* 
* that would be new conversion effect,   conversion 2 would look for immunities and if found set as type 2, allowing mon to maintain stab.
* after fixing that, set conversion effct as logic for imposter, and then add a species check as well.
* 
* nother idea from jrppoketraier98  make move magiccoat work like a screen, where it lasts 3 turns etc.
*  after doing add to screencleaner, and list of effects brick break can shatter - done
* 
* tweaked costume pikachu based on radical red, where each is a different type.
* plan for distribution is, in mongeneration function for wild battles if species would be species pikachu, have 5% chance to swap and generate
* (do same thing for rotom, let it spawn in one of different forms as well as have item that can make it swap forms to use on it)
* a costume pikachu (not one of the hats)
* //since changed to radicla red standard will need to update learnsets, consider radical red showdown for learnets (will need to make diff learnset for each rotom form)
* -(also made base rotom have posesion rotom stats in base/lightbulb form)
*
* test rotom, gave custom dex entry based on legends dex - actually all I need to do is set rotom entry to starter.
* //working on rotom buffs need give each form own learnset, figure out swap between
* plan put seoondary type moves in learnset at pattern, check if learnset is from that type 2 then check the level of learnset
* and replace with move at that level from other form /species
*do similar thing for tms only problem is surf, but can just make it not learn surf as its a washing machine
*do like my version of rotom forms, line up learnsets and off type moves and thmhm sets with off time moves, 
*    //search moveset for move that matches learnsets replace with move from same spot in other form learnset  do same for tmhm so the replacement would be for the 
*    //appropriate type
*buff arena trap shadow tag, to lower enemy speed if they are trapped can do same for magnet pull and meanlook
* use IsAbilityPreventingEscape != 0  along with ability in quetion, lower speed, will exclude the abilities that block the effect
* think will just do simple stat drop, might exclude magnet pull?  arena trap & shado tag can be thought of as doing something to weaken the target explaining the slow
*and a reason why it would last, passed switchout, i.e arena trap pop out of ground bite leg, to slow
* can use IsRunningFromBattleImpossible != battle_run_success    actually nvm just gonna do for arena trap as the others don't make sense to last
*
* removed itemCommon itemRare from base stat data to add back later when item expansion done
* also gender based forms, I moved to new species etc. won't show up in pokedex as of yet.
* only the male/base form is displayed need to setup logic, for pokedex to move between the forms
* when on the main one. do setup for mon variants as well. - IMPORTANT
* pokedex listings are on pokemon.c   close to sSpeciesToHoennPokedexNum
* 
* check trainer_tower_sets.c   trainer tower sets have personality value, that seems to set personality
* for mon.  see if could use for setting nature in trainer stuff.
* 
* // NOTE: Because each Trainer uses a flag to determine when they are defeated, there is 
//       only space for 25 additional trainers before trainer flag space overflows.
//       MAX_TRAINERS_COUNT can be increased but will take up additional saveblock space
* 
* 
* to build had to define parts of mega implementation, did not add completely need to properly setup mega evolution etc.
* includes sprit defines values in battle_interface adn graphic files --removed piece of mega kept defines as caused errors add later
*
*
*rage buff,  gen 2 was continious move that boosted attack stage every time was hit.
*gen 3 onward it was no longer continuous but required you to keep using rage, for the atk stat to boost when taking damgage
*
*my change, using rage sucessfully applies rage status, that persists when ever take damage atk stat will raise, regardless of if using rage again
*so works more akin to focus energy
*but that would remove reason to use move again, so my idea if have rage status, using move will increase atk stat before attacking without needing to take damage 
*same as strength . with changes made I "think" I have just enouhg room to fit it into status 2?  nah status3 I have room in, not status2, would work just as well  
* I think, depends on if yawn change is right or not
*/

goto PRIORITY_EFFECTS	//battle_main.c all effects regarding priority changes go here.
//working on setting up an effect for rock toss and the other effects that do double damage to on air targets
//increased priority is done, still need to set atk canceler portion in battle_script_commands.c
//to cancel fly
//and set  grounded / smack down status if hit while in the air status.
//hmm ok just found there's a bs for that, various gravity on in air targets from emerald
//so guess I'll edit that       -look over and reconsider this

//ok checkd bs_scripts.inc the various command translates to bringdownairbornebattler
//the command doesn't have any logic secific to gravity instead its associated because
//its only placed  in the gravity battle script  so for effect I want  think
//I just need to make a new various bs command with the specific logic I want and place it in 
//the effect_hit command after damage calc to ensure the thing didn't miss.

goto VARIOUS_BS_COMMANDS	//long function for easily setting up new bs commands. and not need a new function
//macro is made in battle_script.inc

goto GROUNDED_FUNCTION //battle_util.c grounded logic, also right below floating mon list
/*
* Relevant Notes:
* Raised Pok�mon are not affected by Ground type moves, Spikes, Toxic Spikes nor Arena Trap.
* Pok�mon no longer stay raised (and cannot become raised) if Gravity or Ingrain is in effect, 
* the move Smack Down is used against them, or Iron Ball is held.
* 
* Its a status 3 so smackdown would be removed on switch 
* I think I want to also make it removed by fly and possibly several other flying moves
* as well as using telekinesis again.
*/

goto RUN_LOGIC_PT1 //battle_main.c 1st area that deals with running logic

goto RUN_LOGIC_PT2 //last part for setting up run based effects battle_main.c

goto TURN_ACTIONS_SWITCH_ETC // battle_main.c  HandleTurnActionSelectionState function deaels with logic  for turn actions i.e switching catching using moves etc.

goto EXP_FUNCTION //battle_script_commands.c has exp & level up logic, can be used as example for mid battle evo 
//	                and needed pokedex logic for double wilds check case 5
//should be able to do streamer/creator mode exp boost here
                    //would be total exp  * multiplier /size of party,
                    //or maybe multiplier will be a switch case determined by party size
                    //that way you boost consistently regardless of team size
                    //again need implement level cap in creator mode
                    //*don't want normal players acceessing this so won't put in options
                    //if they want to play normally in their downtime have interacting with
                    //house gamestation bring up option to toggle creator mode off/on
                    //use flag check created at time of game creation
                    //so even after turning it off,  it can still tell it was a game
                    //created with creator mode in mind
    //lil troll if they select creator mode a game creation
    //add a string to that says to "make sure to check your pc before you start your adventure"
    //will have potion and item that says "not a rarecandy"
    //it can't be used on a pokemon but sells for 90k or something - remember sell price is half of list price
    //item description will say "what were you expecting infiite rare candies?
    //thats pretty cringe bro."  XD
    //so they'll get mad thinking it was a troll, then see the exp boost is on
    //try to sell the item when they realize can't use it on a mon
    //and see its worth a fuckton and then see it was a double fake out!
    //the troll is THERE WAS NO troll!!!
/*
* ok also plan make assumpion of frienship actually a mechanic
* winning a normal battle with a pokemon will increase friendship by 1 point.
* 
* plan is check exp function, if mon received exp, and battle result was success/won  boost friendship
* don't worry about gBattleOutcome  just use get exp, that's all I really need
*/
goto FRIENDSHIP_FUNCTION


goto MOVE_LEARN_PROCESS 
/*
* changed this and evolution move learn process, to add stop gap to prevent accidentally deleting a move, like modern games.
* update the process chart at the top, for future users
*/

goto ENCOUNTER_COUNT_DATA
//data for encounter count i.e number of spaces for land/surf mon defines etc.


#endif //GUARD_GRAND_TO_DOLIST_H