.equ LOCALID_MOM, 1

PalletTown_PlayersHouse_1F_MapScripts:: @ 8168C08
	.byte 0

PalletTown_PlayersHouse_1F_EventScript_Mom:: @ 8168C09
	lock
	faceplayer
	goto_if_set FLAG_BEAT_RIVAL_IN_OAKS_LAB, PalletTown_PlayersHouse_1F_EventScript_MomHeal
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale
	compare VAR_RESULT, FEMALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale
	closemessage
	applymovement LOCALID_MOM, Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale:: @ 8168C38
	msgbox PalletTown_PlayersHouse_1F_Text_AllBoysLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale:: @ 8168C41
	msgbox PalletTown_PlayersHouse_1F_Text_AllGirlsLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomHeal:: @ 8168C4A
	msgbox PalletTown_PlayersHouse_1F_Text_YouShouldTakeQuickRest
	closemessage
	call EventScript_OutOfCenterPartyHeal
	msgbox PalletTown_PlayersHouse_1F_Text_LookingGreatTakeCare
	release
	end

@ Displays special text if interacted with from side or back (which are normally inaccessible)
PalletTown_PlayersHouse_1F_EventScript_TV:: @ 8168C62
	lockall
	compare VAR_FACING, DIR_NORTH
	goto_if_eq PalletTown_PlayersHouse_1F_EventScript_TVScreen
	msgbox PalletTown_PlayersHouse_1F_Text_OopsWrongSide
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreen:: @ 8168C78
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_TVScreenMale
	compare VAR_RESULT, FEMALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreenMale:: @ 8168C91
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVFourBoysOnRailroad
	return

PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale:: @ 8168C9A
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVGirlOnBrickRoad
	return

PalletTown_PlayersHouse_1F_EventScript_ReceiveMomsGiftTriggerLeft:: @ 81692E7
	lockall
	setvar VAR_MOMS_GIFT, 1
	goto PalletTown_PlayersHouse_1F_EventScript_MomEventScript
	end

PalletTown_PlayersHouse_1F_EventScript_ReceiveMomsGiftTriggerMid:: @ 81692F3
	lockall
	setvar VAR_MOMS_GIFT, 2
	goto PalletTown_PlayersHouse_1F_EventScript_MomEventScript
	end

PalletTown_PlayersHouse_1F_EventScript_ReceiveMomsGiftTriggerRight:: @ 81692FF
	lockall
	setvar VAR_MOMS_GIFT, 3
	goto PalletTown_PlayersHouse_1F_EventScript_MomEventScript
	end

PalletTown_PlayersHouse_1F_EventScript_MomEventScript:: @ 816930B
	textcolor 0
	applymovement LOCALID_MOM, Movement_FaceDown
	waitmovement 0
	msgbox PalletTown_PlayersHouse_1F_Text_NearlyForgot
	applymovement OBJ_EVENT_ID_PLAYER, Movement_FaceUp
	compare VAR_MOMS_GIFT, 1
	goto_if_eq PalletTown_PlayersHouse_1F_EventScript_MomApproachForBattleLeft
	compare VAR_MOMS_GIFT, 2
	goto_if_eq PalletTown_PlayersHouse_1F_EventScript_MomApproachForBattleMid
	compare VAR_MOMS_GIFT, 3
	goto_if_eq PalletTown_PlayersHouse_1F_EventScript_MomApproachForBattleRight
	end

PalletTown_PlayersHouse_1F_EventScript_MomApproachForBattleLeft:: @ 8169CFF
	applymovement LOCALID_MOM, PalletTown_PlayersHouse_1F_Movement_MomWalksToPlayerLeft
	waitmovement 0
	call PalletTown_PlayersHouse_1F_EventScript_ReceiveExpNull
	release
	end

PalletTown_PlayersHouse_1F_EventScript_MomApproachForBattleMid:: @ 8169D0F
	applymovement LOCALID_MOM, PalletTown_PlayersHouse_1F_Movement_MomWalksToPlayerMid
	waitmovement 0
	call PalletTown_PlayersHouse_1F_EventScript_ReceiveExpNull
	release
	end

PalletTown_PlayersHouse_1F_EventScript_MomApproachForBattleRight:: @ 8169D1F
	applymovement LOCALID_MOM, PalletTown_PlayersHouse_1F_Movement_MomWalksToPlayerRight
	waitmovement 0
	call PalletTown_PlayersHouse_1F_EventScript_ReceiveExpNull
	release
	end

PalletTown_PlayersHouse_1F_Movement_MomWalksToPlayerLeft::
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

PalletTown_PlayersHouse_1F_Movement_MomWalksToPlayerMid::
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_down
	step_end
	
	
PalletTown_PlayersHouse_1F_Movement_MomWalksToPlayerRight::
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

	
@new event script for receive exp null
@want trigger right at door so don''t have to worry
@about doing a walk back
PalletTown_PlayersHouse_1F_EventScript_ReceiveExpNull::
	msgbox PalletTown_PlayersHouse_1F_Text_MomsGift
	giveitem ITEM_EXP_NULL
	setflag FLAG_GOT_EXP_NULL_FROM_MOM
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	msgbox PalletTown_PlayersHouse_1F_Text_ReceiveExpShare
	msgbox PalletTown_PlayersHouse_1F_Text_EndingResponse
	return

	
