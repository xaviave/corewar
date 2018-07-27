.name "zo;rk"
.comment "I'M ALIIIIVE"
live %0
l2:		sti r1, %:live, %1 ##;
		and r1, %0, r1
		live %0 ; #
;
live:	live %1
		zjmp %:live ;
 ;
