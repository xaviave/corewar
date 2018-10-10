.name "Tu Pac"
.comment "
Live the life of a thug nigga
Until the day I die
Live the life of a boss playa
All eyes on me
'Cause even gettin' high
All eyes on me
Live the life of a thug nigga
Until the day I die
Live the life of a boss playa
'Cause even gettin' high
(Heeyyy, to my nigga 'Pac!)"

	ld %880, r8
	ld %16778753, r9
	ld %4, r10
	ld %72618000, r11
	ld %269090801, r6
	live %456
	fork %:save
	zjmp %:attack

init:
	st r1, 6
	live %0
	ld %720, r2
	st r2, -19
	ld %3489662465, r3
	st r3, -28
	ld %0, r2
	zjmp %:attack

save:
	st r1, 6
	live  %546
	st r8, 1023
	st r9, 1022
	st r10, 1021
	st r11, 1020
	st r12, 1019
	fork %993
	sti r1, %:save2, %1
	fork %:save2
	add r16, r16, r16
	zjmp %:save

save2:
	live%4
	add r16, r16, r16
	zjmp %:save2

place:
	ld %01, r10
	st r10, -330
	st r1, -331
	ld %190055686, r10
	st r10, -339
	ld %67763801, r10
	st r10, -347
	ld %0, r4
	zjmp %:init

attack:
	live %0
	ld %190054915, r2
	ld %-19, r3
	ld %190056198, r5
	ld %-410, r6;
	ld %190056454, r7
	ld %190054915, r8
	ld %00, r4
	zjmp %:place
