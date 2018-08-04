.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
;okman




		and r1, %1, r1

live:	live %1
		zjmp %:live
