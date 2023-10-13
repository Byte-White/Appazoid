@echo off
cd ../
cmake -B out -DAZ_TEST_BUILD=OFF
cmake --build out
PAUSE