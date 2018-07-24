#live %0
.name "zork"
##.comment "ok"
.comment "I'M ALIIIIVE"
live %0
#ok

l2:		sti r87, %:live, %1
		and r1, %0, r1
#		and r1, %0, r1

live:	live	%1
		zjmp %:live

