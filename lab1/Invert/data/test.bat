@echo off

set PROGRMAM="%~1"

rem without arguments
%PROGRMAM% > nul
if NOT ERRORLEVEL 1 goto err

rem empty file
%PROGRMAM% data\emptyInput.txt > nul
if NOT ERRORLEVEL 1 goto err

rem correct data
%PROGRMAM% data\input.txt > nul
if ERRORLEVEL 1 goto err

rem invalid data
%PROGRMAM% data\invalidMatrix.txt > nul
if NOT ERRORLEVEL 1 goto err


rem the degenerate matrix
%PROGRMAM% data\degenerateMatrix.txt > nul
if NOT ERRORLEVEL 1 goto err


rem missing line
%PROGRMAM% data\missingLine.txt > nul
if NOT ERRORLEVEL 1 goto err

rem missing row
%PROGRMAM% data\missingRow.txt > nul
if NOT ERRORLEVEL 1 goto err


echo All good
exit 0

err:
echo Test Failed
exit 1