#!/bin/bash

if [ "$1" = "" ];then
    echo "usage: $0 <output file>"
    echo "   output file - the file to save output in"
    echo "   if output file exists, this script will append to it"
    exit 0;
fi

total = 0
maxpts = 0
dest="$1"
TESTFILES=./test/testFiles
OUTPUTFILES=./test/testOutput

addPoint() {
    let "total=total+1"
    let "maxpts=maxpts+1"
}

removePoint() {
    if [ "$total" == 0 ]; then
        let "total=0"
        let "maxpts=maxpts+1"
    else 
        let "total=total-1"
        let "maxpts=maxpts+1"
    fi
}

displayFinal() {
    echo
    echo "-----$total out of $maxpts tests PASSED-----"
    if [ "$total" != "$maxpts" ]; then
        echo "Errors can be found in $dest"
    else 
        echo "Full Log can be found in $dest"
    fi
    echo "$total out of $maxpts tests PASSED" >> $dest
}

# ------------------------------------ SETUP TESTS  ------------------------------------
# These tests will exit and not continue if executable has not been created
if [ -f $dest ];
then
    removePoint
	echo >> $dest
	echo "unit_tests.sh: output file $dest exists, appending to it" >> $dest
	echo >> $dest
else
    addPoint
fi

echo
echo "***unit_tests.sh -- running tests***"
echo

make all
if [ ! $? -eq 0 ];then
    removePoint
    echo "unit_tests: FAIL - make returned non-zero"  >> $dest
    exit 1
else 
    addPoint
fi

if [ ! -x "./bin/mandelbrot" ];then
    removePoint
    echo "MAKE: FAIL - no exe named mandelbrot in ./bin/" >> $dest
    exit 1
else
    addPoint
fi

if [ ! -x "./bin/mandel-openmp" ];then
    removePoint
    echo "MAKE: FAIL - no exe named mandel-openmp in ./bin/" >> $dest
    exit 1
else    
    addPoint
fi

if [ ! -x "./bin/mandel-cuda" ];then
    removePoint
    echo "MAKE: FAIL - no exe named mandel-cuda in ./bin/" >> $dest
    exit 1
else    
    addPoint
fi

echo >> $dest
echo "CLEANING: ---" >> $dest
make clean
if [ "$?" == 0 ]; then 
    addPoint
    echo "---SUCCESS: make clean" >> $dest
else
    removePoint
    echo "ERROR: make clean did not work" >> $dest
fi

displayFinal