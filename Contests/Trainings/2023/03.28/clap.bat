@echo off

:loop
gen %random% > in.txt
problemsetter < in.txt > out.txt
echo accepted
if %errorlevel% == 0 goto loop