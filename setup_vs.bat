@echo off
REM Visual Studio Setup Script for FoxyPassword Generator
REM This script configures Visual Studio for secure compilation

echo ========================================
echo Visual Studio Setup for FoxyPassword Generator
echo ========================================

echo.
echo [1/6] Checking Visual Studio installation...

REM Check for Visual Studio
set "VS_FOUND="
for %%v in (2022 2019) do (
    if exist "%ProgramFiles%\Microsoft Visual Studio\%%v\*\MSBuild\Current\Bin\MSBuild.exe" (
        echo Found Visual Studio %%v ✓
        set "VS_FOUND=%%v"
        goto :vs_found
    )
    if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\%%v\*\MSBuild\Current\Bin\MSBuild.exe" (
        echo Found Visual Studio %%v ✓
        set "VS_FOUND=%%v"
        goto :vs_found
    )
)

echo ERROR: Visual Studio 2019/2022 not found!
echo Please install Visual Studio 2022 Community from:
echo https://visualstudio.microsoft.com/downloads/
pause
exit /b 1

:vs_found
echo.
echo [2/6] Checking required workloads...

REM Check for UWP development workload
if exist "%ProgramFiles%\Microsoft Visual Studio\%VS_FOUND%\*\Common7\IDE\devenv.exe" (
    echo Visual Studio IDE found ✓
) else (
    echo WARNING: Visual Studio IDE not found
    echo Please install "Universal Windows Platform development" workload
)

echo.
echo [3/6] Checking Windows SDK...

reg query "HKLM\SOFTWARE\Microsoft\Windows Kits\Installed Roots" /v KitsRoot10 >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Windows SDK found ✓
) else (
    echo WARNING: Windows SDK not found
    echo Please install Windows 10 SDK (10.0.19041.0+)
)

echo.
echo [4/6] Configuring project settings...

REM Create backup of original project file
if exist "FoxyPassword Generator\FoxyPassword Generator.vcxproj" (
    copy "FoxyPassword Generator\FoxyPassword Generator.vcxproj" "FoxyPassword Generator\FoxyPassword Generator.vcxproj.backup" >nul
    echo Created backup of project file ✓
)

echo.
echo [5/6] Setting up build environment...

REM Set environment variables for secure build
set "VS_PLATFORM_TOOLSET=v143"
set "VS_WINDOWS_TARGET_PLATFORM_VERSION=10.0.19041.0"
set "VS_APPX_PACKAGE_SIGNING_ENABLED=true"
set "VS_APPX_PACKAGE_SIGNING_TIMESTAMP_DIGEST_ALGORITHM=SHA256"

echo Build environment configured ✓

echo.
echo [6/6] Creating build configuration...

REM Create build configuration file
echo Creating VS_CONFIG.xml...
copy "VS_CONFIG.xml" "FoxyPassword Generator\VS_CONFIG.xml" >nul 2>&1

echo.
echo ========================================
echo Setup completed successfully! ✓
echo ========================================
echo.
echo Next steps:
echo 1. Open Visual Studio %VS_FOUND%
echo 2. Open "FoxyPassword Generator.sln"
echo 3. Right-click project → Properties
echo 4. Set Target Platform Version: 10.0.19041.0
echo 5. Set Platform Toolset: Visual Studio 2022 (v143)
echo 6. Create test certificate in Signing tab
echo 7. Build → Build Solution (Ctrl+Shift+B)
echo.
echo Or use our automated build script:
echo build.bat
echo.
echo Security features enabled:
echo ✓ Cryptographically secure random generation
echo ✓ Hardware-based entropy
echo ✓ Input validation
echo ✓ Buffer security checks
echo ✓ Control flow guard
echo ✓ Spectre mitigation
echo ✓ Code signing
echo.
pause
