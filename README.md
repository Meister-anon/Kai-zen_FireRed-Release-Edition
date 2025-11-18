
Branch Goals:

found move effect bug was caused by issue w modern/agbcc
it only exists on modern now.

So need to go over the sym file again and fix things that
are noticeabley different sizes to hopefully fix this.


of note ai functions i.e ai_check_bad_move etc.
seem to be diff size  most functions in ai files are off sized

08086d78 g 00001990 DoFieldEndTurnEffects
08088708 g 00002148 DoBattlerEndTurnEffects
AbilityBattleEffects

also massive size diff between builds
as of yet unable to identify any clue to cause