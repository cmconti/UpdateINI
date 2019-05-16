@SETLOCAL ENABLEDELAYEDEXPANSION
@echo off

set exe=..\Release\UpdateINI.exe
if /I .%1. EQU .Debug. set exe=..\Debug\UpdateINI.exe

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1

echo Write Non existant file
%exe% -s Section Key Value "%~dp0\TestOut.ini"
echo %ERRORLEVEL% 
if 0 EQU %ERRORLEVEL% (
    fc "%~dp0\Test1.ini" "%~dp0\TestOut.ini"
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1

echo update existing file with same value
copy "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
%exe% -s Section Key Value "%~dp0\TestOut.ini"
if 0 EQU %ERRORLEVEL% (
    fc "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1

echo update existing file with different value
copy "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
%exe% -s Section Key Value2 "%~dp0\TestOut.ini"
if 0 EQU %ERRORLEVEL% (
    fc "%~dp0\Test2.ini" "%~dp0\TestOut.ini" > nul 2>&1
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1

echo update existing file with new key
copy "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
%exe% -s Section Key2 Value2 "%~dp0\TestOut.ini"
if 0 EQU %ERRORLEVEL% (
    fc "%~dp0\Test3.ini" "%~dp0\TestOut.ini" > nul 2>&1
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1
del "%~dp0\out.txt" > nul 2>&1

echo missing -s param
copy "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
%exe% Section Key2 Value2 "%~dp0\TestOut.ini" > out.txt
if 0 EQU %ERRORLEVEL% (
    fc "%~dp0\Usage.txt" "%~dp0\out.txt" > nul 2>&1
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1
del "%~dp0\out.txt" > nul 2>&1

echo missing param
copy "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
%exe% -s Section Key2 Value2 > out.txt
if -1 EQU %ERRORLEVEL% (
    fc "%~dp0\Usage.txt" "%~dp0\out.txt" > nul 2>&1
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1
del "%~dp0\out.txt" > nul 2>&1

echo write to invalid filename
copy "%~dp0\Test1.ini" "%~dp0\TestOut.ini" > nul 2>&1
%exe% -s Section Key2 Value2 "%~dp0" > out.txt 2>&1
if 123 EQU %ERRORLEVEL% (
    fc "%~dp0\Err123.txt" "%~dp0\out.txt" > nul 2>&1
    if 0 EQU !ERRORLEVEL! SET fail=0
)
if %fail% EQU 0 (echo passed) else (echo failed)

set fail=1
del "%~dp0\TestOut.ini" > nul 2>&1
del "%~dp0\out.txt" > nul 2>&1

ENDLOCAL