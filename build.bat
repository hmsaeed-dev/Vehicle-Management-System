@echo off
:: ============================================================================
:: Vehicle Management System Build Script
:: ============================================================================

echo [BUILD] Starting Compilation...

:: Check if the executable is already running (Windows won't let us overwrite it)
tasklist /FI "IMAGENAME eq VehicleManagementSystem.exe" 2>NUL | find /I /N "VehicleManagementSystem.exe">NUL
if "%ERRORLEVEL%"=="0"
(
    echo [ERROR] The program is currently running!
    echo Please close the Vehicle Management System window and try again.
    pause
    exit /b
)

:: Run the g++ compiler
:: -IInclude: Tells the compiler where to find .h files
:: Source/*.cpp: Compiles all C++ files in the Source folder
:: -o CarRentalSystem.exe: Names the final program
g++ -IInclude Source/*.cpp -o VehicleManagementSystem.exe

:: Check if the previous command (g++) succeeded
if %errorlevel% equ 0
(
    echo [SUCCESS] Compilation complete.
    echo [RUN] Launching Vehicle Management System...
    echo.
    VehicleManagementSystem.exe
)
else
(
    echo.
    echo [ERROR] Compilation failed! Please check the errors above.
    echo.
    pause
)
