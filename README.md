
Branch Goals:

found move effect bug was caused by issue w modern/agbcc
it only exists on modern now.

So need to go over the sym file again and fix things that
are noticeabley different sizes to hopefully fix this.


of note ai functions i.e ai_check_bad_move etc.
seem to be diff size  most functions in ai files are off sized

agbcc       modern
000016ac g 00001990 DoFieldEndTurnEffects
0000273c g 00002148 DoBattlerEndTurnEffects
00008d64 g 00006d54 AbilityBattleEffects

