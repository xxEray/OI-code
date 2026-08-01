@echo off

:loop
array-gen %random%
array < data.txt > out.txt
array-std < data.txt > ans.txt
fc out.txt ans.txt
if %errorlevel% == 0 goto loop

pause
