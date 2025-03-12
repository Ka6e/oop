@echo off

set PROGRAM="%~1"

rem without arguments
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem 1 arguments
%PROGRAM% 34 > nul
if NOT ERRORLEVEL 1 goto err

rem with 2 arguments
%PROGRAM% 34 2 > nul
if NOT ERRORLEVEL 1 goto err

rem succesefuly
%PROGRAM% 10 2 5 > nul
if ERRORLEVEL 1 goto err

rem invalid notation
%PROGRAM% 2 37 0001 > nul
if NOT ERRORLEVEL 1 goto err

rem max value
%PROGRAM% 10 36 2147483647 > nul
if ERRORLEVEL 1 goto err

rem overflox
%PROGRAM% 10 36 2147483648 > nul
if NOT ERRORLEVEL 1 goto err

rem min value
%PROGRAM% 10 36 -2147483647 > nul
if ERRORLEVEL 1 goto err

rem проверить на int min - 1
%PROGRAM% 10 16 -2147483648 > nul
if NOT ERRORLEVEL 1 goto err

rem zero
%PROGRAM% 7 12 0 > nul
if ERRORLEVEL 1 goto err

rem binary
%PROGRAM% 2 8 01011010 > nul
if ERRORLEVEL 1 goto err

rem from 20 to 2
%PROGRAM% 20 34 5C7E2D > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Tests failed
exit 1

