@echo off

set file=yacolorful

g++ ../%file%.cpp -o %file% -O2 -Wl,--stack=1024000000
g++ chk.cpp -o chk -O2
g++ gen.cpp -o gen -O2

:loop
gen %random% > %file%.in
%file%
chk
if %errorlevel% == 0 goto loop

color 40
pause
