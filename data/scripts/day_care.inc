Route5_PokemonDayCare_EventScript_DaycareMan:: @ 81BF398
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	special SetPlayerAtRoute5Daycare
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_EGG_WAITING
	goto_if_eq Route5_EventScript_DaycareEggWaiting
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route5_PokemonDayCare_EventScript_CheckOnMon
	compare VAR_RESULT, DAYCARE_TWO_MONS
	goto_if_eq Route5_PokemonDayCare_EventScript_CheckOnMon
	msgbox Route5_PokemonDayCare_Text_WantMeToRaiseMon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_PokemonDayCare_EventScript_TryGiveMon
	msgbox Route5_PokemonDayCare_Text_ComeAgain
	release
	end

Route5_PokemonDayCare_EventScript_TryGiveMon:: @ 81BF3DD
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 1
	goto_if_eq Route5_PokemonDayCare_EventScript_OnlyOneMonInParty
	msgbox Route5_PokemonDayCare_Text_WhichMonShouldIRaise
	fadescreen FADE_TO_BLACK
	special ChooseBoxMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route5_PokemonDayCare_EventScript_ComeAgain
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	specialvar VAR_0x8002, CheckBlockExpGainInDaycare
	call_if_eq VAR_0x8002, TRUE, Route5_PokemonDayCare_EventScript_ConfirmExpStateAndSelection
	msgbox Route5_PokemonDayCare_Text_LookAfterMonForAWhile
	waitse
	playmoncry VAR_0x8005, 0
	msgbox Route5_PokemonDayCare_Text_ComeSeeMeInAWhile
	waitmoncry
	special StoreSelectedPokemonInDaycare
	compare VAR_0x8008, NUZLOCKE_BANNED_MON
	goto_if_eq Route5_PokemonDayCare_EventScript_SorryCantRaiseThat
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route5_PokemonDayCare_CanRaiseOneMore
	release
	end

Route5_PokemonDayCare_EventScript_ConfirmExpStateAndSelection::
	msgbox Route5_PokemonDayCare_Text_MonWontGetStronger, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route5_PokemonDayCare_EventScript_TryGiveMon
	return

Route5_PokemonDayCare_EventScript_ComeAgain:: @ 81BF444
	special ClearVarPlayerAtRoute5Daycare
	msgbox Route5_PokemonDayCare_Text_ComeAnytimeYouLike
	release
	end

Route5_PokemonDayCare_EventScript_SorryCantRaiseThat::
	setvar VAR_0x8008, 0
	msgbox Route5_PokemonDayCare_Text_CantRaiseThat
	goto Route5_PokemonDayCare_EventScript_TryGiveMon

Route5_PokemonDayCare_EventScript_OnlyOneMonInParty:: @ 81BF452
	special ClearVarPlayerAtRoute5Daycare
	msgbox Route5_PokemonDayCare_Text_OnlyHaveOneMonWithYou
	release
	end

Route5_PokemonDayCare_EventScript_OnlyOneAliveMonInParty:: @ 81BF460
	special ClearVarPlayerAtRoute5Daycare
	msgbox Route5_PokemonDayCare_Text_WhatWillYouBattleWith
	release
	end

Route5_PokemonDayCare_EventScript_CheckOnMon:: @ 81BF46E
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route5_DayCare_CheckOn1Mon
	compare VAR_RESULT, DAYCARE_TWO_MONS
	goto_if_eq Route5_DayCare_CheckOn2Mon
	end

Route5_DayCare_CheckOn1Mon::
	special GetDaycareMonNicknames	@needed to reset name stored for scripts
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	compare VAR_RESULT, 0
	call_if_ne Route5_PokemonDayCare_EventScript_MonHasGrownByXLevels
	compare VAR_RESULT, 0
	call_if_eq Route5_PokemonDayCare_EventScript_NotEnoughTime
	msgbox DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_PokemonDayCare_EventScript_TryRetrieveMon	
	goto Route5_PokemonDayCare_CanRaiseOneMore
	end

Route5_DayCare_CheckOn2Mon::
	special GetDaycareMonNicknames
	msgbox DayCare_Text_YourMonsAreDoingFine
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call FourIsland_PokemonDayCare_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call FourIsland_PokemonDayCare_DisplayLevelsGained
	msgbox DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route5_PokemonDayCare_EventScript_ComeAgain
	release
	end

Route5_PokemonDayCare_EventScript_MonHasGrownByXLevels:: @ 81BF4AA
	msgbox Route5_PokemonDayCare_Text_MonHasGrownByXLevels
	return

Route5_PokemonDayCare_EventScript_NotEnoughTime:: @ 81BF4B3
	msgbox Route5_PokemonDayCare_Text_MonNeedsToSpendMoreTime
	return

Route5_PokemonDayCare_EventScript_TryRetrieveMon:: @ 81BF4BC
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq Route5_PokemonDayCare_EventScript_NoRoomInParty
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route5_PokemonDayCare_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	compare VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU
	goto_if_eq Route5_PokemonDayCare_EventScript_ComeAgain
	goto Route5_PokemonDayCare_CostPrompt
	end

Route5_PokemonDayCare_EventScript_RetrieveMon:: @ 81BF4EA
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_RS_SHOP
	@updatemoneybox 0, 0, 0
	copyvar VAR_0x8008, VAR_RESULT
	getpartysize
	subvar VAR_RESULT, 1
	getpartymonname 0, VAR_RESULT
	copyvar VAR_RESULT, VAR_0x8008
	msgbox Route5_PokemonDayCare_Text_ThankYouHeresMon
	textcolor 3
	waitse
	playmoncry VAR_RESULT, 0
	msgbox Route5_PokemonDayCare_Text_PlayerGotMonBack
	call EventScript_RestorePrevTextColor
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route5_PokemonDayCare_AskRetrieveOtherMon
	goto Route5_PokemonDayCare_EventScript_ComeAgain
	release
	end

Route5_PokemonDayCare_EventScript_NoRoomInParty:: @ 81BF533
	special ClearVarPlayerAtRoute5Daycare
	msgbox Route5_PokemonDayCare_Text_YouveGotNoRoomForIt
	end

Route5_PokemonDayCare_EventScript_CloseMoneyBox:: @ 81BF541
	hidemoneybox 0, 0
	release
	end

@put converted 4 island scripts here

Route5_PokemonDayCare_CanRaiseOneMore:: @ 8171A01
	special GetDaycareMonNicknames
	msgbox DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_PokemonDayCare_EventScript_TryGiveMon
	goto Route5_PokemonDayCare_EventScript_ComeAgain
	end

Route5_EventScript_DaycareEggWaiting:: @ 8167D9B
	msgbox DayCare_Text_DoYouWantEgg, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_EventScript_DaycareAcceptEgg
	msgbox DayCare_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_EventScript_DaycareAcceptEgg
	msgbox DayCare_Text_IllKeepIt
	clearflag FLAG_PENDING_ROUTE_5_DAYCARE_EGG
	special RejectEggFromDayCare	@dont need clear here, already in special
	release
	end

Route5_EventScript_DaycareAcceptEgg:: @ 8167DD1
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	compare VAR_RESULT, PARTY_SIZE
	goto_if_ne Route5_EventScript_DaycareReceivedEgg
	msgbox DayCare_Text_YouHaveNoRoomForIt
	special ClearVarPlayerAtRoute5Daycare
	release
	end

Route5_EventScript_DaycareReceivedEgg:: @ 8167DEB
	textcolor 3
	message DayCare_Text_ReceivedEgg
	call EventScript_RestorePrevTextColor
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox DayCare_Text_TakeGoodCareOfIt
	special GiveEggFromDaycare	@same as rejectegg clear var is already part of macro
	clearflag FLAG_PENDING_ROUTE_5_DAYCARE_EGG
	release
	end

Route5_PokemonDayCare_CostPrompt:: @ 8171ACF
	special GetDaycareCost
	msgbox Route5_PokemonDayCare_Text_OweMeXForMonsReturn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_PokemonDayCare_CheckEnoughMoney
	goto Route5_PokemonDayCare_EventScript_ComeAgain
	end

Route5_PokemonDayCare_CheckEnoughMoney:: @ 8171AEB
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	compare VAR_RESULT, TRUE
	goto_if_eq Route5_PokemonDayCare_EventScript_RetrieveMon
	msgbox DayCare_Text_NotEnoughMoney
	special ClearVarPlayerAtRoute5Daycare
	release
	end

Route5_PokemonDayCare_AskRetrieveOtherMon:: @ 8171B4E
	msgbox DayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route5_PokemonDayCare_EventScript_TryRetrieveMon
	specialvar VAR_RESULT, GetDaycareState
	compare VAR_RESULT, DAYCARE_ONE_MON
	goto_if_eq Route5_PokemonDayCare_CanRaiseOneMore	
	goto Route5_PokemonDayCare_EventScript_ComeAgain
	end


@@end custom scripts @@
EventScript_EggHatch:: @ 81BF546
	lockall
	msgbox DayCare_Text_Huh
	special EggHatch
	waitstate
	releaseall
	end
