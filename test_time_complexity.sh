#!/bin/sh

g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr.o tr.cpp
python generate_squarefree.py > long_sqf.in
./tr.o < long_sqf.in