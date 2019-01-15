@echo off
title Compiling Knights Tour...
color 03
cls
echo.
echo Compiling...
echo.
g++ -std=c++11 ./src/knights_tour.cpp ./src/parameters.cpp ./src/solver.cpp ./src/validator.cpp ./src/hal-windows.cpp -o ./bin/knights_tour
echo.
echo Done!
echo.
pause
exit
