.name "null"
.comment "null"

ld %1,r3
ld %0,r4

zork:
add r2,r3,r2
sti r2,%50,%1
ld %0,r4
zjmp %:zork
