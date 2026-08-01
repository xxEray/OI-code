@echo off

cd %~dp0

g++ __judge.cpp -o __judge.exe -O2 -std=c++14 -fexec-charset=GBK

start __judge.exe

exit