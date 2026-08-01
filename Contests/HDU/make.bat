@echo off
cd %~dp0
set "dt=%date%"
set filename=%dt:~0,4%.%dt:~5,2%.%dt:~8,2%
if not exist %filename% mkdir %filename%