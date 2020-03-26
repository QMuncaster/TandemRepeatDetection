#!/bin/bash

# tests manually created large strings
make

IMP_EXE=${1:-"tr.o"}

cd "tests/"
IMP_EXE="../$IMP_EXE"
IMP_DIR="out/"

FILES="$(ls -v manual/*.in)"
for f in $FILES
do
    file="$(basename $f .in)"
    echo -e "\nfile $file"

    # echo "running implementation"
    $IMP_EXE < $f
    echo ""
done
