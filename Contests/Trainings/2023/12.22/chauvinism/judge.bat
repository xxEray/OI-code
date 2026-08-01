@echo off

set file=chauvinism

g++ ../%file%.cpp -o %file% -O2 -Wl,--stack=1024000000
g++ bf.cpp -o bf -Wl,--stack=1024000000 -O2
g++ gen.cpp -o gen -O2
g++ chk.cpp -o chk -O2

:loop
gen %random% > %file%.in
bf < %file%.in > %file%.ans
%file% < %file%.in > %file%.out
chk
if %errorlevel% == 0 goto loop

color 40
pause
