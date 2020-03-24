#!/bin/sh

g++ -W -Wall -pedantic --std=c++17 -O3 -o tr.o tr.cpp
g++ -W -Wall -pedantic --std=c++17 -O3 -o tr_fast.o tr_fast.cpp

#                      10^6 = 1000000
#                      10^7 = 10000000
#                      10^8 = 100000000
python generate_squarefree.py 10000007 > long_sqf.in

echo "running O(nlogn) algorithm"
command time -f "\ntime=%es\n" ./tr.o < long_sqf.in

echo "running O(n) algorithm"
command time -f "\ntime=%es\n" ./tr_fast.o < long_sqf.in

# echo "running O(n^2) algorithm"
# command time -f "\ntime=%es\n" ./tr_bf.o < long_sqf.in
