@echo off

g++ gen.cpp -o gen -O2 -Wl,--stack=1024000000 -w
g++ std.cpp -o std -O2 -Wl,--stack=1024000000 -w
