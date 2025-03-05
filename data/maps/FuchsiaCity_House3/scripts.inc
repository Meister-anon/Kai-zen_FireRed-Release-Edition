FuchsiaCity_House3_MapScripts:: @ 816D894
	.byte 0

FuchsiaCity_House3_EventScript_MoveDeleter:: @ 816D895
	lock
	faceplayer
	msgbox FuchsiaCity_House3_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

@plan completely change this, no move delete
@instead takes money to teach how to delete moves
@so you can do it from the pc whenever you want
@check daycare logic for how to setup
@FLAG_TAUGHT_MOVE_DELETE
@ use gText_1_2_and_Poof before string saying player learned how to forget moves
FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter:: @ 816D8B0
	@msgbox FuchsiaCity_House3_Text_WhichMonShouldForgetMove
	call_if_set FLAG_MET_MOVE_DELETER FuchsiaCity_House3_EventScript_ReturnForgetMove
	call_if_unset FLAG_MET_MOVE_DELETER FuchsiaCity_House3_EventScript_TryToForgetMove
	@think populate money box here if agree to spend
	@special ChoosePartyMon
	@waitstate
	@compare VAR_0x8004, PARTY_SIZE
	@goto_if_ge FuchsiaCity_House3_EventScript_CancelForgetMove
	msgbox FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FuchsiaCity_House3_EventScript_LearnedToForget
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_TryToForgetMove::
	setflag FLAG_MET_MOVE_DELETER
	msgbox FuchsiaCity_House3_Text_YouWantMeToDeleteAMove
	return

FuchsiaCity_House3_EventScript_ReturnForgetMove::
	msgbox FuchsiaCity_House3_Text_TeachYouHowToDeleteMove
	return

FuchsiaCity_House3_EventScript_LearnedToForget::
	msgbox gText_1_2_and_Poof
	msgbox FuchsiaCity_House3_Text_PlayerLearnedToForget
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox FuchsiaCity_House3_Text_PlayerHasLearnedToForgetCompletely
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
	msgbox FuchsiaCity_House3_Text_ComeAgainToForgetOtherMoves
	release
	end
