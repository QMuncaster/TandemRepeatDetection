#!/bin/sh

# for files too slow to run std comparison on

g++ -W -Wall -pedantic --std=c++17 -O3 -o tr.o tr.cpp
g++ -W -Wall -pedantic --std=c++17 -O3 -o tr_fast.o tr_fast.cpp
g++ -W -Wall -pedantic --std=c++17 -O3 -o tr_bf.o tr_bf.cpp

IMP_EXE=${1:-"tr.o"}

cd "tests/"
IMP_EXE="../$IMP_EXE"
IMP_DIR="out/"

FILES="$(ls -v manual/*.in)"
for f in $FILES
do
    file="$(basename $f .in)"
    echo "\nfile $file"

    # echo "running implementation"
    $IMP_EXE < $f
    echo ""
done
