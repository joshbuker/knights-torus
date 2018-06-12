@echo off
title Knight's Tour Calculator - Initializing
color 03
cls
echo.
echo Josh's Knights Tour Program
echo.
set /p bX=Enter Board Width)  
set /p bY=Enter Board Height) 
echo.
echo Starting position counts starting from 1, not 0.
echo.
set /p sX=Enter starting X) 
set /p sY=Enter starting Y) 
echo.
title Knight's Tour Calculator - Running
color 0F
echo Executing program...
"%cd%\bin\knights_tour.exe" %sX% %sY% %bX% %bY%
title Knight's Tour Calculator - Finished
pause
exit
