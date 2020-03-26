#!/bin/bash

# tests randomly generated strings and compares to O(n^2) output
make

IMP_EXE=${1:-"tr.o"}

cd "tests/"
IMP_EXE="../$IMP_EXE"
STD_EXE="../tr_bf.o"

IMP_DIR="out/"
STD_DIR="std/"

FILES="$(ls -v in/*.in)"
for f in $FILES
do
    file="$(basename $f .in)"
    echo -e "\nfile $file"

    # echo -e "running implementation"
    $IMP_EXE < $f > ${IMP_DIR}${file}.out

    # echo -e "running comparison standard"
    $STD_EXE < $f > ${STD_DIR}${file}.out

    # echo -e "printing disagreements"
    paste -d ':' ${IMP_DIR}${file}.out ${STD_DIR}${file}.out | grep -nvE "YES:YES|NO:NO"

    echo -en "no_count/total = "
    no_count=$(grep -c "NO" ${IMP_DIR}${file}.out)
    total=$(wc -l < ${IMP_DIR}${file}.out)
    total=$((total+1)) # unix doesn't count last line as no CRLF
    ratio=$((100*no_count/total))
    echo -e "$no_count/$total = $ratio%"
done
