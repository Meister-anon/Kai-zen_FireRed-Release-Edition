FuchsiaCity_House3_MapScripts:: @ 816D894
	.byte 0

@think may actually move this to cerulean city,
@better to have earlier and not major deal plus
@after daycare upgrade can have synergy w daycare there
@can start having access to egg moves
@think add old man to berry master house?
FuchsiaCity_House3_EventScript_MoveDeleter:: @ 816D895
	lock
	faceplayer
	goto_if_set FLAG_TAUGHT_MOVE_DELETE, FuchsiaCity_House3_EventScript_AlreadyLearnedHowToForget
	msgbox FuchsiaCity_House3_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House3_EventScript_MoveDeleterScriptsStart
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

@plan completely change this, no move delete
@instead takes money to teach how to delete moves
@so you can do it from the pc whenever you want
@check daycare logic for how to setup
@FLAG_TAUGHT_MOVE_DELETE
@ use gText_1_2_and_Poof before string saying player learned how to forget moves
FuchsiaCity_House3_EventScript_MoveDeleterScriptsStart:: @ 816D8B0
	call_if_set FLAG_MET_MOVE_DELETER, FuchsiaCity_House3_EventScript_ReturnForgetMove
	call_if_unset FLAG_MET_MOVE_DELETER, FuchsiaCity_House3_EventScript_TryToForgetMove
	goto FuchsiaCity_House3_EventScript_CostPrompt
	end

FuchsiaCity_House3_EventScript_TryToForgetMove::
	setflag FLAG_MET_MOVE_DELETER
	msgbox FuchsiaCity_House3_Text_YouWantMeToDeleteAMove
	return

FuchsiaCity_House3_EventScript_ReturnForgetMove::
	msgbox FuchsiaCity_House3_Text_TeachYouHowToDeleteMove
	return

FuchsiaCity_House3_EventScript_LearnedToForget::
	setflag FLAG_TAUGHT_MOVE_DELETE
	playse SE_SHOP
	removemoney VAR_0x8005, 0
	updatemoneybox 0, 0, 0
	waitse
	hidemoneybox 0, 0
	msgbox FuchsiaCity_House3_Text_PlayerLearnedToForget
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	closemessage
	msgbox FuchsiaCity_House3_Text_PlayerHasLearnedToForgetCompletely
	release
	end

FuchsiaCity_House3_EventScript_CostPrompt:: @ 8171ACF
	textcolor 0
	showmoneybox 0, 0, 0
	special GetMoveDeleterMoveReminderCost
	msgbox FuchsiaCity_House3_Text_TeachCost, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FuchsiaCity_House3_EventScript_CheckEnoughMoney
	goto FuchsiaCity_House3_EventScript_CancelForgetMoveAtCostSelection
	end

FuchsiaCity_House3_EventScript_CheckEnoughMoney:: @ 8171AEB
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	compare VAR_RESULT, TRUE
	goto_if_eq FuchsiaCity_House3_EventScript_LearnedToForget
	hidemoneybox 0, 0
	msgbox DayCare_Text_NotEnoughMoney
	release
	end

FuchsiaCity_House3_EventScript_AlreadyLearnedHowToForget::
	msgbox FuchsiaCity_House3_Text_ComeAgainToRememberToForget
	release 
	end

FuchsiaCity_House3_EventScript_ForgetMove:: @ 816D919
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely
	release
	end

FuchsiaCity_House3_EventScript_CantForgetOnlyMove:: @ 816D92A
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonOnlyKnowsOneMove
	release
	end

FuchsiaCity_House3_EventScript_CantForgetMoveEgg:: @ 816D937
	msgbox FuchsiaCity_House3_Text_NoEggShouldKnowMoves
	release
	end

FuchsiaCity_House3_EventScript_CancelForgetMove:: @ 816D941
	msgbox FuchsiaCity_House3_Text_ComeAgainToForget
	release
	end

FuchsiaCity_House3_EventScript_CancelForgetMoveAtCostSelection:: @ 816D941
	hidemoneybox 0, 0
	msgbox FuchsiaCity_House3_Text_ComeAgainToForget
	release
	end
