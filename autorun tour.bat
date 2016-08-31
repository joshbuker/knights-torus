@echo off
title Knight's Tour Calculator - Initializing
color 03
cls
echo.
echo Josh's Knights Tour Program
echo.
set current=8
set /p final=Enter Final Board Size)
echo.
title Knight's Tour Calculator - Running
:begin
color 0F
echo.
echo Executing program...
set /a bX=%current%
set /a bY=%current%
set /a sX=%current%/2
set /a sY=%current%/2
"%cd%\knights_tour.exe" %sX% %sY% %bX% %bY%
echo.
if %current%==%final% goto eof
set /a current=%current%*2
goto begin
:eof
title Knight's Tour Calculator - Finished
pause
exit