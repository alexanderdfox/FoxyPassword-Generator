@echo off
REM Build Script for FoxyPassword Generator
REM Run this script on Windows with Visual Studio installed

echo ========================================
echo Building FoxyPassword Generator (Secure)
echo ========================================

REM Check if we're in the right directory
if not exist "FoxyPassword Generator.sln" (
    echo ERROR: FoxyPassword Generator.sln not found!
    echo Please run this script from the project root directory.
    pause
    exit /b 1
)

echo.
echo [1/4] Checking Visual Studio installation...
where msbuild >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: MSBuild not found!
    echo Please install Visual Studio 2019/2022 with C++/WinRT workload.
    echo Or run from "Developer Command Prompt for VS"
    pause
    exit /b 1
)

echo [2/4] Cleaning previous builds...
if exist "FoxyPassword Generator\Release" (
    rmdir /s /q "FoxyPassword Generator\Release"
    echo Cleaned Release directory.
)

echo [3/4] Building solution...
msbuild "FoxyPassword Generator.sln" ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxPackageSigningEnabled=true ^
    /p:AppxPackageSigningTimestampDigestAlgorithm=SHA256 ^
    /p:AppxPackageSigningTimestampServer=http://timestamp.digicert.com ^
    /verbosity:minimal ^
    /nologo

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [4/4] Build completed successfully! ✅
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
    echo    - Ensure Visual Studio 2019/2022 is installed
    echo    - Install C++/WinRT workload
    echo    - Install Windows 10 SDK (10.0.19041.0+)
    echo    - Run from Developer Command Prompt
    echo.
)

pause
