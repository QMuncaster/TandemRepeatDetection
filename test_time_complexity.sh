#!/bin/sh

g++ -W -Wall -pedantic --std=c++17 -o tr.o tr.cpp
g++ -W -Wall -pedantic --std=c++17 -o tr_fast.o tr_fast.cpp

echo "generating long squarefree via method 1"
python generate_squarefree.py 40000000 1 > tests/long/long_sqf_1.in

echo "generating long squarefree via method 2"
python generate_squarefree.py 40000000 2 > tests/long/long_sqf_2.in
                    #  10^6 = 1000000
                    #  10^7 = 10000000
                    #  10^8 = 100000000

echo "running O(n) algorithm"
command time -f "\ntime=%es\n" ./tr_fast.o < tests/long/long_sqf_1.in
command time -f "\ntime=%es\n" ./tr_fast.o < tests/long/long_sqf_2.in

echo "running O(nlogn) algorithm"
command time -f "\ntime=%es\n" ./tr.o < tests/long/long_sqf_1.in
command time -f "\ntime=%es\n" ./tr.o < tests/long/long_sqf_2.in
