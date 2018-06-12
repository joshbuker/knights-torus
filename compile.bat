@echo off
title Compiling Knights Tour...
color 03
cls
echo.
echo Compiling...
echo.
g++ ./src/knights_tour.cpp ./src/parameters.cpp ./src/solver.cpp ./src/validator.cpp ./src/hal-windows.cpp -o ./bin/knights_tour
echo.
echo Done!
echo.
pause
exit
