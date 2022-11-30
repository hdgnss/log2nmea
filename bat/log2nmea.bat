@echo off
SETLOCAL

set str=%1
echo.%str%

REM Trim Quotes - Remove surrounding quotes via FOR command
for /f "useback tokens=*" %%a in ('%str%') do set str=%%~a

set Programs="%ProgramFiles%"
if "%ProgramFiles(x86)%" NEQ "" (
    set Programs="%ProgramFiles(x86)%"
)
REM Trim the double-quotes
set Programs=%Programs:~1,-1%

SET LOG2NMEAPATH=%Programs%\log2nmea\
echo.%LOG2NMEAPATH%


"%LOG2NMEAPATH%log2nmea.exe" -i "%str%"