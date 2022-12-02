@echo off
SETLOCAL

set str=%1
echo.%str%

REM Trim Quotes - Remove surrounding quotes via FOR command
for /f "useback tokens=*" %%a in ('%str%') do set str=%%~a


SET LOG2NMEAPATH=%~dp0
echo.%LOG2NMEAPATH%


"%LOG2NMEAPATH%log2nmea.exe" -i "%str%"