#live %0
.name "zork"
##.comment "ok"
.comment "I'M ALIIIIVE"
live %0
#ok

l2:		sti r1, %:live, %1
		ld 478372, r3
		and r1, %0, r1
#		and r1, %0, r1

live:	live	%1
		zjmp %:live

