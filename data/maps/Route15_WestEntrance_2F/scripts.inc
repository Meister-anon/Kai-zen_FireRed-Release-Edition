.equ REQUIRED_CAUGHT_MONS, 50

Route15_WestEntrance_2F_MapScripts:: @ 8170092
	.byte 0

Route15_WestEntrance_2F_EventScript_LeftBinoculars:: @ 8170093
	lockall
	msgbox Route15_WestEntrance_2F_Text_LargeShiningBird
	drawmonpic SPECIES_ARTICUNO, 10, 3
	delay 20
	waitbuttonpress
	erasemonpic
	setvar VAR_0x8004, SPECIES_ARTICUNO
	special SetSeenMon
	releaseall
	end

Route15_WestEntrance_2F_EventScript_RightBinoculars:: @ 81700B0
	msgbox Route15_WestEntrance_2F_Text_SmallIslandOnHorizon, MSGBOX_SIGN
	end

@figure something else to put here
@as moving exp share earliers
@hmm should i make this the mega ring?
Route15_WestEntrance_2F_EventScript_Aide:: @ 81700B9
	lock
	faceplayer
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_MEGA_RING_FROM_OAKS_AIDE, Route15_WestEntrance_2F_EventScript_AlreadyGotMegaRing
	msgbox Route15_WestEntrance_2F_Text_GiveItemIfCaughtEnough, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetPokedexCount
	getnumberstring 2, VAR_0x8006
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	compare VAR_0x8006, REQUIRED_CAUGHT_MONS
	goto_if_lt Aide_EventScript_HaventCaughtEnough
	msgbox Route15_WestEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_MEGA_RING, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Aide_EventScript_NoRoomForItem
	giveitem_msg Route15_WestEntrance_2F_Text_ReceivedItemFromAide, ITEM_MEGA_RING, 1, MUS_OBTAIN_KEY_ITEM
	setflag FLAG_GOT_MEGA_RING_FROM_OAKS_AIDE
	msgbox Route15_WestEntrance_2F_Text_ExplainMegaRing
	release
	end

Route15_WestEntrance_2F_EventScript_AlreadyGotMegaRing:: @ 817013B
	msgbox Route15_WestEntrance_2F_Text_ExplainMegaRing
	release
	end

Route15_WestEntrance_2F_EventScript_GetAideRequestInfo:: @ 8170145
	getnumberstring 0, REQUIRED_CAUGHT_MONS
	getitemname 1, ITEM_EXP_SHARE
	return
