@echo off
for /f %%i in ('dir /b/od %1.cpp %1.exe 2^>nul') do set L=%%i
if not "%L%"=="%1.exe" (
  g++ %1.cpp -std=c++17 -Wall -Wextra -Wshadow -O2 -D LOCAL ^
    -g -o %1 || (echo Compile failed.& exit /b 1)
)
%1
