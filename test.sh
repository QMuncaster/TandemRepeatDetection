#!/bin/sh

g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr.o tr.cpp
g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr_fast.o tr_fast.cpp
g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr_bf.o tr_bf.cpp

cd "tests/"
FILES="$(ls -v in/*.in)"

IMP_DIR="out/"
# IMP_EXE="../tr.o"
IMP_EXE="../tr_fast.o"

STD_DIR="std/"
STD_EXE="../tr_bf.o"

for f in $FILES
do
    file="$(basename $f .in)"
    echo "\nfile $file"

    # echo "running implementation"
    $IMP_EXE < $f > ${IMP_DIR}${file}.out

    # echo "running comparison standard"
    $STD_EXE < $f > ${STD_DIR}${file}.out

    # echo "printing disagreements"
    paste -d ':' ${IMP_DIR}${file}.out ${STD_DIR}${file}.out | grep -nvE "YES:YES|NO:NO"

    echo "no_count/total = \c"
    no_count=$(grep -c "NO" ${IMP_DIR}${file}.out)
    total=$(wc -l < ${IMP_DIR}${file}.out)
    total=$((total+1)) # unix doesn't count last line as no CRLF
    ratio=$((100*no_count/total))
    echo "$no_count/$total = $ratio%"
done
