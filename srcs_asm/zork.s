.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		zjmp %:live
		and r1, %0, r1

		zjmp %42
		zjmp %:live
live:	live %1
