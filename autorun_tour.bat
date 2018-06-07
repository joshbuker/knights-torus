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
if %current% gtr %final% goto toosmall
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
if %current% gtr %final% goto eof
if %current%==%final% goto eof
set /a current=%current%*2
goto begin
:toosmall
title Knight's Tour Calculator - Input Too Small
echo %final% is too small, please use a value greater than %current%
echo.
pause
exit
:eof
title Knight's Tour Calculator - Finished
pause
exit
