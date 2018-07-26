.name "zork"
.comment "I'M ALIIIIVE"

live %0
sti		r10, 10, %0
live %0
sti		r10, %-10, %0
live %0
#ok

l2:		sti r1, %:live, %1
		live             %0
		xor	r10, r10,r10 # pour rien
		and r1, %0, r1
#		and r8, %0, r1

live:	live	%1
		zjmp %:live
		aff r1

