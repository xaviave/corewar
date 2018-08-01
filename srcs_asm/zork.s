.name "zork"
.comment "I'M ALIIIIVE"

l2:	bfenusbgk	sti r1, %:live, %1
;okman




		and r1, %0, r1

live:	live %1
		zjmp %:live
