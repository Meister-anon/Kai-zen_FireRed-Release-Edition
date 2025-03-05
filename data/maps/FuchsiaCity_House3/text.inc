FuchsiaCity_House3_Text_WouldYouLikeToForgetMove:: @ 81993B9
    .string "Uh…\n"
    .string "Oh, yes, I'm the MOVE DELETER.\p"
    .string "Did you come here to make POKéMON\n"
    .string "forget their moves?\p"
    .string "Would you like me to do that?$"

FuchsiaCity_House3_Text_WhichMonShouldForgetMove:: @ 8199421
    .string "Which POKéMON should forget a\n"
    .string "move?$"

@long message so use flag set so it only plays
@for first time
FuchsiaCity_House3_Text_YouWantMeToDeleteAMove::
    .string "Well\. I don't do that anymore!\p"
    .string "After offering my service freely\n"
    .string "to every trainer that stops by,\l"
    .string "I realized something\.\p"
    .string "I COULD BE MAKING MONEY!!\p"
    .string "So I stopped deleting moves\n"
    .string "and instead for a small fee\l"
    .string "I'll teach you how to do it!$"

@follow up message that will play
@get special populate w cost do open moneybox
@like daycare etc.
FuchsiaCity_House3_Text_TeachYouHowToDeleteMove::
    .string "If you would like to learn\n"
    .string "how to delete moves for your\l"
    .string "POKéMON, I can teach you.$"

FuchsiaCity_House3_Text_PlayerLearnedToForget::
    .string "{PAUSE 0x20}1, {PAUSE 0x0F}2, and {PAUSE 0x0F}‥ {PAUSE 0x0F}‥ {PAUSE 0x0F}‥ {PAUSE 0x0F}{PLAY_SE SE_BALL_BOUNCE_1}Poof!\p"
    .string "{PLAYER} learned how to forget moves!$"

FuchsiaCity_House3_Text_TeachCost::
    .string "It'll only cost you\n"
    .string "the low price of ¥{STR_VAR_2}!$"

FuchsiaCity_House3_Text_PlayerHasLearnedToForgetCompletely:: @ 81994B1
    .string "It worked to perfection!\p"
    .string "You can now delete moves for\n"
    .string "your POKéMON from the pc.$"

FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten:: @ 8199445
    .string "Which move should be forgotten?$"

FuchsiaCity_House3_Text_MonOnlyKnowsOneMove:: @ 8199465
    .string "{STR_VAR_1} seems to know only one\n"
    .string "move…$"

FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten:: @ 8199485
    .string "Hm! {STR_VAR_1}'s {STR_VAR_2}?\n"
    .string "That move should be forgotten?$"

FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely:: @ 81994B1
    .string "It worked to perfection!\p"
    .string "{STR_VAR_1} has forgotten\n"
    .string "{STR_VAR_2} completely.$"


FuchsiaCity_House3_Text_ComeAgainToForget:: @ 81994EA
    .string "Come again if you decide you\n"
    .string "want to learn to forget moves.$"

@end message for already learned skill
FuchsiaCity_House3_Text_ComeAgainToRememberToForget:: @ 81994EA
    .string "I can see you already know\n"
    .string "how to delete moves.\p"
    .string "Feel free to stop by if you\n"
    .string "ever need a reminder on\l"
    .string "how to forget!$"

FuchsiaCity_House3_Text_NoEggShouldKnowMoves:: @ 819951F
    .string "What?\n"
    .string "No EGG should know any moves.$"

