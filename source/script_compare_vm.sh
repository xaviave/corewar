#/bin/bash

let "SUCCESS = 0";
let "FAIL = 0";
let "ALL = 0";

for CHAMP1 in ./champs/{.,examples,championships/*/*}/*.cor; do
	for CHAMP2 in ./champs/{.,examples,championships/*/*}/*.cor; do
	if [ "$1" != "" ]
	then
		echo "run test on $CHAMP1 $CHAMP2 with dump = $1";
		./../corewar -dump $1 $CHAMP1 $CHAMP2 > tmp1;
		./exe_corewar -d $1 $CHAMP1 $CHAMP2 > tmp2;
	else
		echo "run test on $CHAMP1 $CHAMP2 without dump";
		./../corewar $CHAMP1 $CHAMP2 > tmp1;
		./exe_corewar $CHAMP1 $CHAMP2 > tmp2;
	fi
		DIFF=$(diff tmp1 tmp2);
		if [ "$DIFF" != "" ]
		then
			echo "\033[31mfail on $CHAMP1 $CHAMP2\033[0m"
			let "FAIL++";
		else
			echo "\033[32msuccess on $CHAMP1 $CHAMP2\033[0m"
			let "SUCCESS++";
		fi
		rm tmp1 tmp2;
		let "ALL++";
	done
done

echo "You have $SUCCESS success and $FAIL fail(s) on $ALL test(s)";
