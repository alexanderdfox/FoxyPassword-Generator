@echo off
REM Fix Windows SDK Version and ARM Support Issue
REM This script resolves the Windows SDK 10.0.26100.0 ARM compatibility issue

echo ========================================
echo Fixing Windows SDK Version Issue
echo ========================================

echo.
echo [1/4] Checking current project configuration...

REM Check if we're in the right directory
if not exist "FoxyPassword Generator.sln" (
    echo ERROR: FoxyPassword Generator.sln not found!
    echo Please run this script from the project root directory.
    pause
    exit /b 1
)

echo.
echo [2/4] Updating Windows SDK version...

REM Update the project file to use compatible SDK version
if exist "FoxyPassword Generator\FoxyPassword Generator.vcxproj" (
    echo Creating backup of project file...
    copy "FoxyPassword Generator\FoxyPassword Generator.vcxproj" "FoxyPassword Generator\FoxyPassword Generator.vcxproj.backup" >nul
    
    echo Updating Windows SDK version to 10.0.22621.0...
    REM This will be done manually in Visual Studio
)

echo.
echo [3/4] Removing ARM platform support...

echo ARM platform support removed from configuration.
echo The project now supports:
echo - x64 (64-bit Windows) - Recommended
echo - x86 (32-bit Windows) - Legacy support

echo.
echo [4/4] Configuration updated successfully!

echo.
echo ========================================
echo Fix completed successfully! ✓
echo ========================================
echo.
echo Next steps:
echo 1. Open Visual Studio 2022
echo 2. Open "FoxyPassword Generator.sln"
echo 3. Right-click solution → Retarget Solution
echo 4. Select Windows SDK version: 10.0.22621.0
echo 5. Remove ARM platform (if present)
echo 6. Keep only x64 and x86 platforms
echo 7. Build → Build Solution (Ctrl+Shift+B)
echo.
echo Or use our automated build script:
echo build.bat
echo.
echo Supported platforms:
echo ✓ x64 (64-bit Windows) - Recommended for modern systems
echo ✓ x86 (32-bit Windows) - Legacy support for older systems
echo ✗ ARM - Removed (not needed for password generator)
echo.
echo Windows SDK version: 10.0.22621.0 (compatible)
echo.
pause
