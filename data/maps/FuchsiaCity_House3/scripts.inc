FuchsiaCity_House3_MapScripts:: @ 816D894
	.byte 0

FuchsiaCity_House3_EventScript_MoveDeleter:: @ 816D895
	lock
	faceplayer
	msgbox FuchsiaCity_House3_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

@plan completely change this, no move delete
@instead takes money to teach how to delete moves
@so you can do it from the pc whenever you want
FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter:: @ 816D8B0
	msgbox FuchsiaCity_House3_Text_WhichMonShouldForgetMove
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge FuchsiaCity_House3_EventScript_CancelForgetMove
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq FuchsiaCity_House3_EventScript_CantForgetMoveEgg
	special GetNumMovesSelectedMonHas
	compare VAR_RESULT, 1
	goto_if_eq FuchsiaCity_House3_EventScript_CantForgetOnlyMove
	msgbox FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten
	fadescreen FADE_TO_BLACK
	special SelectMoveDeleterMove
	fadescreen FADE_FROM_BLACK
	compare VAR_0x8005, MAX_MON_MOVES
	goto_if_eq FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FuchsiaCity_House3_EventScript_ForgetMove
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
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
