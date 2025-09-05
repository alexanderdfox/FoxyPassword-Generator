@echo off
REM Clean Build Script for FoxyPassword Generator
REM This script provides a clean build experience

echo ========================================
echo FoxyPassword Generator - Clean Build
echo ========================================

echo.
echo [1/3] Checking project structure...

REM Check if we're in the right directory
if not exist "FoxyPassword Generator.sln" (
    echo ERROR: FoxyPassword Generator.sln not found!
    echo Please run this script from the project root directory.
    pause
    exit /b 1
)

echo Project structure verified ✓

echo.
echo [2/3] Building Release x64...

REM Build with x64 platform
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /m

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [3/3] Build completed successfully! ✅
    echo.
    echo 📁 Build outputs:
    echo    Executable: FoxyPassword Generator\x64\Release\PackageLayout\FoxyPassword Generator.exe
    echo    Package: FoxyPassword Generator\x64\Release\PackageUploadLayout\
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
    echo    - Check docs/ folder for detailed guides
    echo.
)

pause
