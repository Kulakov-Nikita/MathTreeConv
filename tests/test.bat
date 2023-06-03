@echo off
setlocal enabledelayedexpansion

set appPath=D:\MathTreeConv\x64\Debug\MathTreeConv.exe
set basePath=D:\MathTreeConv\tests

for /L %%i in (1, 1, 10) do (
    set "inputPath=%basePath%\in%%i.txt"
    set "outputPath=%basePath%\out%%i.txt"

    echo Running test case %%i

    "%appPath%" "!inputPath!" "!outputPath!"

    echo Test case %%i completed.
    echo.
)

echo All test cases completed.
pause