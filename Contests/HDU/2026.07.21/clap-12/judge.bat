@echo off

g++ gen.cpp -o gen -O2 -std=c++17
g++ ..\12.cpp -o 12 -O2 -std=c++17

:loop
gen > in.txt
12 < in.txt > out.txt
fc out.txt ans.txt
if %errorlevel% == 0 goto loop

color 40
pause