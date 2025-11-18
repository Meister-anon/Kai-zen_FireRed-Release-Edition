#define BUG_TRACKING
/*

-11/14/25 -unresolved
potential major issues seems certain abilities not triggering
for player only foe?
modern noticed anticipation not procing


-11/5/25 - unresolved
dmging moves that lower stats get reflected
to setting battler, believe is a result of somehow
activating mirror armor refelction but unsure.

-double check that stat raising effects don't do same
believe it doesn't

also of note Anercomp seemed to have activated 
this effect (constrict on caterpie @1hp) and it caused a game freeze
-potential fix finish battle controller rework and battle script refactor
see if that fixes issue.

tracked issue...its part of the agbcc vs modern issue *facepalm
idk why it is but it is, so need go over sym file and fix rest of 
different size values

-apparently not the case talked with egg
and mention of -O flag (optimization) came up
turning that off for a reason I've yet to be informed of
is what caused my modern code to break.

possible my code is written in a way so bad
it just optimizes out things that shouldn't be?

Talked with Sbird this was confirmed smh
path forward is to use Eggs idea of 
separating my compile out between agbcc and modern by file/source file .c files
to identify which file is causing it.

So path forward is to research makefile stuff to learn how to 
do that.

GudF also has other idea to use __attribute__((optimize()))
or  #pragma GCC optimize 

according to them would achieve mostly same results but without
requiring to touch the makeFile, which may be better for me 
but I should also learn more about Makefile stuff just so I know 
I'm not screwing things up smh

also massive size diff between builds
as of yet unable to identify any clue to cause

agbcc

Memory region         Used Size  Region Size  %age Used
           EWRAM:      256681 B       256 KB     97.92%
           IWRAM:       28248 B        32 KB     86.21%
             ROM:    22340664 B        32 MB     66.58%

modern

Memory region         Used Size  Region Size  %age Used
           EWRAM:      256710 B       256 KB     97.93%
           IWRAM:       27864 B        32 KB     85.03%
             ROM:    22377452 B        32 MB     66.69%


comparing pret to see if diff between make and modern make

agbcc fire red
Memory region         Used Size  Region Size  %age Used
           EWRAM:      261040 B       256 KB     99.58%
           IWRAM:       29824 B        32 KB     91.02%
             ROM:    15403808 B        32 MB     45.91%

modern fire red
Memory region         Used Size  Region Size  %age Used
           EWRAM:      259182 B       256 KB     98.87%
           IWRAM:       29276 B        32 KB     89.34%
             ROM:     9357889 B        32 MB     27.89%
*/