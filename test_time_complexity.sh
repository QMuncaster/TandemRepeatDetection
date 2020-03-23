#!/bin/sh

g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr.o tr.cpp
python generate_squarefree.py > long_sqf.in

echo "running O(n) algorithm"
command time -f "\ntime=%es\n" ./tr_fast.o < long_sqf.in

echo "running O(nlogn) algorithm"
command time -f "\ntime=%es\n" ./tr.o < long_sqf.in

echo "running O(n^2) algorithm"
command time -f "\ntime=%es\n" ./tr_bf.o < long_sqf.in
