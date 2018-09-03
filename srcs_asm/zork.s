.name "zork"
.comment "I'M ALIIIIVE"

lfork %:l2
live %1890
l2:		sti r1, %:live, %1
l2:		sti r1, %:live, %1
		and r1, 42, r4

live:	live %1
		zjmp %:live
