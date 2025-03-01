LavenderTown_House2_MapScripts:: @ 816B265
	.byte 0

LavenderTown_House2_EventScript_NameRater:: @ 816B266
	lock
	faceplayer
	msgbox LavenderTown_House2_Text_WantMeToRateNicknames, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq LavenderTown_House2_EventScript_ChooseMon
	compare VAR_RESULT, NO
	goto_if_eq LavenderTown_House2_EventScript_DontRateNickname
	end

@so think will change this potentially make daily event
@instead of rename, check a mon with a nickname
@and high friendship and give the player something
LavenderTown_House2_EventScript_ChooseMon:: @ 816B287
	msgbox LavenderTown_House2_Text_CritiqueWhichMonsNickname
	fadescreen FADE_TO_BLACK
	special ChooseBoxMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, LavenderTown_House2_EventScript_CheckCanRateMon
	goto LavenderTown_House2_EventScript_DontRateNickname
	end

LavenderTown_House2_EventScript_DontRateNickname:: @ 816B2AA
	msgbox LavenderTown_House2_Text_ISeeComeVisitAgain
	release
	end

@I don''t understand what''s wrong,
@this breaks the ismonnicknamed special just DOESNT work
@vsonic change this add friendship check,
@if friendship high enough & nicknamed
@give special item
LavenderTown_House2_EventScript_CheckCanRateMon:: @ 816B2B4
	@specialvar VAR_RESULT, GetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq LavenderTown_House2_EventScript_CantNicknameEgg
	special BufferMonNickname
	specialvar VAR_0x8002, IsMonNicknamed
	goto_if_eq VAR_0x8002, FALSE, LavenderTown_House2_EventScript_PokemonNotNicknamed
	specialvar VAR_RESULT, GetSelectedMonFriendship
	compare VAR_RESULT, 6  @ Max friendship
	goto_if_ne LavenderTown_House2_EventScript_NameCouldBeBetter
	call_if_eq LavenderTown_House2_EventScript_GreatNameGiveReward
	release
	end

@go back to mon selection
LavenderTown_House2_EventScript_PokemonNotNicknamed::
	msgbox LavenderTown_House2_Text_DoesntHaveNickname
	goto LavenderTown_House2_EventScript_ChooseMon

LavenderTown_House2_EventScript_NameCouldBeBetter::
	msgbox LavenderTown_House2_Text_PokemonNotUsedtoName
	release
	end

LavenderTown_House2_EventScript_GreatNameGiveReward::
	msgbox LavenderTown_House2_Text_PokemonWonderfulName
	@make special for giving reward here
	return


LavenderTown_House2_EventScript_CantNicknameEgg:: @ 816B307
	msgbox LavenderTown_House2_Text_ThatIsMerelyAnEgg
	release
	end

LavenderTown_House2_EventScript_CantNicknameTradeMon:: @ 816B311
	msgbox LavenderTown_House2_Text_TrulyImpeccableName
	release
	end

LavenderTown_House2_EventScript_ChooseNewNickname:: @ 816B31B
	msgbox LavenderTown_House2_Text_WhatShallNewNicknameBe
	call EventScript_ChangePokemonNickname
	specialvar VAR_RESULT, NameRaterWasNicknameChanged
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq LavenderTown_House2_EventScript_ChoseNewNickname
	msgbox LavenderTown_House2_Text_FromNowOnShallBeKnownAsSameName
	release
	end

LavenderTown_House2_EventScript_ChoseNewNickname:: @ 816B345
	msgbox LavenderTown_House2_Text_FromNowOnShallBeKnownAsName
	release
	end
