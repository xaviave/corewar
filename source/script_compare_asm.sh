#!/bin/bash

let "SUCCESS = 0";
let "FAIL = 0";
let "ALL = 0";

for FILENAME in ./champs/{.,examples,championships/*/*}/*.s; do

	COR=$FILENAME;
	COR=${COR%.*};
	COR="$COR.cor";

	./../asm $FILENAME > dontcare;
	if [ -e $COR ]
	then
		xxd $COR > test;
	fi
	./exe_asm $FILENAME > dontcare;
	if [ -e $COR ]
	then
		xxd $COR > exe_test;
	fi
	if [ -e "test" ] && [ -e "exe_test" ]
	then
		DIFF=$(diff test exe_test);
	elif [ -e "test" ] || [ -e "exe_test" ]
	then
		DIFF="fail";
	else
		DIFF="";
	fi
	if [ "$DIFF" != "" ]
	then
		echo "\033[31mfail on $FILENAME\033[0m"
		let "FAIL++";
	else
		echo "\033[32msuccess on $FILENAME\033[0m"
		let "SUCCESS++";
	fi
	if [ -e "test" ]
	then
		rm test;
	fi
	if [ -e "exe_test" ]
	then
		rm exe_test;
	fi
	rm dontcare;
	let "ALL++";
done

echo "You have $SUCCESS success and $FAIL fail(s) on $ALL test(s)";
