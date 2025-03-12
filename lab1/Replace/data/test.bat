@echo off

set PROGRAM="%~1"

rem without arguments expected 0
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem with arguments expected 0
%PROGRAM% data\test1\input_1.txt "%TEMP%\dog.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\dog.txt" data\test1\output_1.txt > nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

rem with arguments expected 0
%PROGRAM% data\test2\input_2.txt "%TEMP%\12345.txt" 1231234 XYZ
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\12345.txt" data\test2\output_2.txt > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

rem empty search string
%PROGRAM% data\test3\input_3.txt "%TEMP%\tut.txt" "" tam
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\tut.txt" data\test3\output_3.txt > nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

rem huge text 
%PROGRAM% data\test4\input_4.txt "%TEMP%\bigText.txt" we lama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\bigText.txt" data\test4\output_4.txt > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

rem line 12312312345
%PROGRAM% data\test5\input_5.txt "%TEMP%\12312312345.txt" 1231234 123
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\12312312345.txt" data\test5\output_5.txt > nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

rem empty input file
%PROGRAM% data\test6\emptyInput.txt "%TEMP%\emptyOut.txt" la lama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\emptyOut.txt" data\test6\emptyOutput.txt > nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

rem a line is missing
echo Test 7
rem %PROGRAM% data\test2\input_2.txt "%TEMP%\outputTest.txt" 
rem if NOT ERRORLEVEL 1 goto err

rem a non-existent input file
%PROGRAM% nonExistFile.txt "%TEMP%\output.txt" 123 ABC
if NOT ERRORLEVEL 1 goto err

rem a non-existent output file
%PROGRAM% data\test1\input_1.txt data\test\ouput.txt 984 ABC
if NOT ERRORLEVEL 1 goto err

exit /b 0

:err
echo Program testing failed
exit /b 1