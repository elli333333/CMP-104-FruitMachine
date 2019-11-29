#!/bin/sh

rm -rfv build
mkdir build
cmake -B build
cd build
make
mv FruitMachine ../output/FruitMachine
../output/FruitMachine