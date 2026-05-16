@echo off
rem ============================================================================
rem Vehicle Management System Build Script
rem ============================================================================

echo [BUILD] Starting Compilation...

rem Run the g++ compiler
g++ -IInclude Source/*.cpp -o VehicleManagSys.exe

rem Check if compilation was successful
if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Compilation complete.
    echo [RUN] Launching Vehicle Management System...
    echo.
    VehicleManagSys.exe
) else (
    echo.
    echo [ERROR] Compilation failed! Check the errors above.
    echo.
    pause
)
