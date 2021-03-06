#!/bin/bash

# times runtime for generated squarefree strings 
make

if [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "generating long squarefree via method 1"
    python test_generators/generate_squarefree.py $1 1 > tests/long/long_sqf_1.in

    echo "generating long squarefree via method 2"
    python test_generators/generate_squarefree.py $1 2 > tests/long/long_sqf_2.in
                        #  10^6 = 1000000
                        #  10^7 = 10000000
                        #  10^8 = 100000000
fi

echo "running O(n) algorithm"
command time -f "\ntime=%es\n" ./tr_fast.o < tests/long/long_sqf_1.in
command time -f "\ntime=%es\n" ./tr_fast.o < tests/long/long_sqf_2.in

echo "running O(nlogn) algorithm"
command time -f "\ntime=%es\n" ./tr.o < tests/long/long_sqf_1.in
command time -f "\ntime=%es\n" ./tr.o < tests/long/long_sqf_2.in
