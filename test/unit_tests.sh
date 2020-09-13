#!/bin/bash

if [ "$1" = "" ];then
    echo "usage: $0 <output file>"
    echo "   output file - the file to save output in"
    echo "   if output file exists, this script will append to it"
    exit 0;
fi

total = 0;
maxpts = 0;
let "maxpts=10"
dest="$1"
TESTFILES=./test/testFiles
OUTPUTFILES=./test/testOutput

addPoint() {
    let "total=total+1"
}

removePoint() {
    if [ "$total" == 0 ]; then
        let "total=total-1"
    else 
        let "total=total-1"
    fi
}

displayFinal() {
    echo "$total out of $maxpts tests PASSED" >> $dest
}

if [ -f $dest ];
then
    removePoint
	echo
	echo "unit_tests.sh: output file $dest exists, appending to it"
	echo
else
    addPoint
fi

echo >> $dest
echo "unit_tests.sh -- running smoke tests" >> $dest
echo >> $dest

make
if [ ! $? -eq 0 ];then
    removePoint
    echo "unit_tests: FAIL - make returned non-zero"  >> $dest
    exit 1
else 
    addPoint
fi

if [ ! -x "./bin/piLeib" ];then
    removePoint
    echo "MAKE: FAIL - no exe named piLeib in ./bin/" >> $dest
    exit 1
else
    addPoint
fi

if [ ! -x "./bin/fibonacci" ];then
    removePoint
    echo "MAKE: FAIL - no exe named piLeib in ./bin/" >> $dest
    exit 1
else    
    addPoint
fi

if [ ! -x "./bin/mm" ];then
    removePoint
    echo "MAKE: FAIL - no exe named piLeib in ./bin/" >> $dest
    exit 1
else
    addPoint
fi

if [ ! -x "./bin/mv" ];then
    removePoint
    echo "MAKE: FAIL - no exe named piLeib in ./bin/" >> $dest
    exit 1
else
    addPoint
fi

if [ ! -x "./bin/piMonte" ];then
    removePoint
    echo "MAKE: FAIL - no exe named piLeib in ./bin/" >> $dest
    exit 1
else  
    addPoint
fi

echo "START: Testing Leibniz's Pi Estimation" >> $dest
./bin/piLeib 100 >> ./output/output.txt
if test "$?" = "-1"
then   
    removePoint
    echo "PiLeib: FAIL - commands with arguments do not work" >> $dest
	exit 1
else 
    addPoint
fi

diff -i -w -B ./output/output.txt $TESTFILES/piLeib100.txt >>diff.out
if [ "$?" == 0 ]; then 
    addPoint
    rm diff.out
    echo "---SUCCESS: piLeib 100" >> $dest
else
    removePoint
    echo "ERROR: piLeib did not calculate with value 100 correctly" >> $dest
    echo "Note: The diff result is in ./diff.out"
fi

rm -f ./output/output.txt

./bin/piLeib 1000 >> ./output/output.txt
diff -i -w -B ./output/output.txt $TESTFILES/piLeib1000.txt >>diff.out
if [ "$?" == 0 ]; then 
    addPoint
    rm diff.out
    echo "---SUCCESS: piLeib 1000" >> $dest
else
    removePoint
    echo "ERROR: piLeib did not calculate with value 1000 correctly" >> $dest
    echo "Note: The diff result is in ./diff.out"
fi

make clean
if [ "$?" == 0 ]; then 
    addPoint
else
    removePoint
    echo "ERROR: make clean did not work"
fi


displayFinal