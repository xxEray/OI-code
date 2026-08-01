@echo off
title A

:loop
generator %random% > in.txt
participant < in.txt > out.txt
jury < in.txt > ans.txt
fc out.txt ans.txt
if %errorlevel% == 0 goto loop

pause