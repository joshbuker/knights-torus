@echo off
title Compiling Knights Tour...
color 03
cls
echo.
echo Compiling...
echo.
g++ knights_tour.cpp hal-windows.cpp -o knights_tour
echo.
echo Done!
echo.
pause
exit
