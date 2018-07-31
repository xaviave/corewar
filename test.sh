./exe_corewar -d $1 champs/examples/helltrain.cor champs/examples/fluttershy.cor > tmp1
./corewar -dump $1 champs/examples/helltrain.cor champs/examples/fluttershy.cor > tmp2

diff tmp1 tmp2

rm tmp1 tmp2
