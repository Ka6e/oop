@echo off

set PROGRAM="%~1"

rem without arguments
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem empty file
%PROGRAM% crypt data\test2\emptyInput.txt "%TEMP%\emptyOutput.txt" 25 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\emptyOutput.txt" data\test2\emptyOutput.txt > nul
if ERRORLEVEL 1 goto err

rem invalid key format
%PROGRAM% crypt data\test1\input.txt "%TEMP%\cryptOutput.txt" F 
if NOT ERRORLEVEL 1 goto err

rem invalid key format
%PROGRAM% crypt data\test1\input "%TEMP%\cryptOutput.txt" -1 
if NOT ERRORLEVEL 1 goto err

rem invalid key format 
%PROGRAM% crypt data\test1\input "%TEMP%\cryptOutput.txt" 256 
if NOT ERRORLEVEL 1 goto err

rem sucesseful crypt
%PROGRAM% crypt data\test1\input.txt "%TEMP%\cryptOutput1.txt" 15 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\cryptOutput1.txt" data\test1\output.txt > nul
if ERRORLEVEL 1 goto err

rem sucesseful decrypt 
%PROGRAM% decrypt data\test3\input.txt "%TEMP%\decryptOutput.txt" 15
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\decryptOutput.txt" data\test3\output.txt > nul
if ERRORLEVEL 1 goto err

rem non-existing input
%PROGRAM% crypt nonExistingFile.txt "%TEMP%\nonExistingFileInput.txt" 210
if NOT ERRORLEVEL 1 goto err


rem non-exisstring output
%PROGRAM% crypt data\test1\input.txt "data\test1\CRYPT.txt" 10
echo %ERRORLEVEL%
rem if NOT ERRORLEVEL 1 goto err

echo All test sucessed
exit /b 0

:err
echo Program testing failed
exit /b 1