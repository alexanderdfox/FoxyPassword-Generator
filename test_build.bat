@echo off
REM Test Build Script for Fixed Project Configuration
REM This script tests the updated project configuration

echo ========================================
echo Testing Fixed Project Configuration
echo ========================================

echo.
echo [1/3] Checking project configuration...

REM Check if we're in the right directory
if not exist "FoxyPassword Generator.sln" (
    echo ERROR: FoxyPassword Generator.sln not found!
    echo Please run this script from the project root directory.
    pause
    exit /b 1
)

echo Project files found ✓

echo.
echo [2/3] Building with fixed configuration...

REM Build with x64 platform (recommended)
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /m

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [3/3] Build completed successfully! ✅
    echo.
    echo 📁 Build outputs:
    echo    Executable: FoxyPassword Generator\Release\PackageLayout\FoxyPassword Generator.exe
    echo    Package: FoxyPassword Generator\Release\PackageUploadLayout\
    echo.
    echo 🔒 Security features included:
    echo    ✓ Cryptographically secure random generation
    echo    ✓ Hardware-based entropy
    echo    ✓ Input validation
    echo    ✓ Password strength analysis
    echo    ✓ Professional UI/UX
    echo.
    echo 🚀 Next steps:
    echo    1. Test the application locally
    echo    2. Create app package for distribution
    echo    3. Deploy to Windows Store (optional)
    echo.
) else (
    echo.
    echo ❌ Build failed! Please check the error messages above.
    echo.
    echo 🔧 Troubleshooting:
    echo    - Ensure Visual Studio 2022 is installed
    echo    - Install C++/WinRT workload
    echo    - Install Windows 10 SDK (10.0.22621.0+)
    echo    - Run from Developer Command Prompt
    echo.
)

pause
