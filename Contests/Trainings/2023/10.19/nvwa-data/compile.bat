@echo off

g++ gen.cpp -o gen -O2
g++ std.cpp -o std -O2 "-Wl,--stack=1024000000"