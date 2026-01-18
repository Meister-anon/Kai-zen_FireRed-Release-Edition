.equ REQUIRED_OWNED_MONS, 20

Route10_PokemonCenter_1F_MapScripts:: @ 816FC2F
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route10_PokemonCenter_1F_OnTransition:: @ 816FC3A
	setworldmapflag FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F
	setrespawn SPAWN_ROUTE10
	end

Route10_PokemonCenter_1F_EventScript_Nurse:: @ 816FC41
	lock
	faceplayer
	call EventScript_PkmnCenterNurse
	release
	end

Route10_PokemonCenter_1F_EventScript_FatMan:: @ 816FC4A
	msgbox Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Gentleman:: @ 816FC53
	msgbox Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Youngster:: @ 816FC5C
	msgbox Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender, MSGBOX_NPC
	end

@now that eviolite and everstone dont stop evo
@replace these make purchasable from daycare npcs
@this is by the power plant maybe give modern items
@could do assault vest and some berries
@dont give everstone is after daycare would already have
@think save eviolite for later daycare 
@or could just make really expensive like 15k
@yeah think thats better vsonic important
@HOLD_EFFECT_AIR_BALLOON
@HOLD_EFFECT_FOCUS_SASH
@HOLD_EFFECT_FLOAT_STONE
@potential things to give here thinking use to introduce
@changed effect
Route10_PokemonCenter_1F_EventScript_Aide:: @ 816FC65
	lock
	faceplayer
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_FLOAT_STONE_FROM_OAKS_AIDE, Route10_PokemonCenter_1F_EventScript_AlreadyGotFloatstone
	msgbox Route10_PokemonCenter_1F_Text_GiveFloatstoneIfCaught20Mons, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetPokedexCount
	getnumberstring 2, VAR_0x8006
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	compare VAR_0x8006, REQUIRED_OWNED_MONS
	goto_if_lt Aide_EventScript_HaventCaughtEnough
	msgbox Route10_PokemonCenter_1F_Text_GreatHereYouGo
	@checkitemspace ITEM_EVERSTONE, 3
	checkitemspace ITEM_FLOAT_STONE, 3
	compare VAR_RESULT, FALSE
	goto_if_eq Aide_EventScript_NoRoomForItem
	giveitem ITEM_FLOAT_STONE, 3
	giveitem_msg Route10_PokemonCenter_1F_Text_ReceivedFloatstoneFromAide, ITEM_FLOAT_STONE, 3
	setflag FLAG_GOT_FLOAT_STONE_FROM_OAKS_AIDE
	msgbox Route10_PokemonCenter_1F_Text_ExplainFloatstone
	release
	end

Route10_PokemonCenter_1F_EventScript_AlreadyGotFloatstone:: @ 816FCE7
	msgbox Route10_PokemonCenter_1F_Text_ExplainFloatstone
	release
	end

Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo:: @ 816FCF1
	getnumberstring 0, REQUIRED_OWNED_MONS
	getitemname 1, ITEM_FLOAT_STONE
	return
