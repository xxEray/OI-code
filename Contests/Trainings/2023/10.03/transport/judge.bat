@echo off

set file=transport

g++ ../%file%.cpp -o %file% -O2 -Wl,--stack=1024000000
g++ bf.cpp -o bf -Wl,--stack=1024000000 -O2
g++ gen.cpp -o gen -O2

:loop
gen %random% > %file%.in
bf < %file%.in > %file%.ans
%file%
fc %file%.out %file%.ans
if %errorlevel% == 0 goto loop

color 40
pause
