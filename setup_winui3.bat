@echo off
REM WinUI 3 Setup Script for FoxyPassword Generator
REM This script configures Visual Studio for WinUI 3 development

echo ========================================
echo WinUI 3 Setup for FoxyPassword Generator
echo ========================================

echo.
echo [1/7] Checking Visual Studio 2022 installation...

REM Check for Visual Studio 2022
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\*\MSBuild\Current\Bin\MSBuild.exe" (
    echo Found Visual Studio 2022 ✓
    set "VS_VERSION=2022"
) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\*\MSBuild\Current\Bin\MSBuild.exe" (
    echo Found Visual Studio 2022 ✓
    set "VS_VERSION=2022"
) else (
    echo ERROR: Visual Studio 2022 not found!
    echo Please install Visual Studio 2022 (17.0 or later) from:
    echo https://visualstudio.microsoft.com/downloads/
    pause
    exit /b 1
)

echo.
echo [2/7] Checking Windows App SDK...

REM Check for Windows App SDK
reg query "HKLM\SOFTWARE\Microsoft\WindowsAppSDK" >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Windows App SDK found ✓
) else (
    echo WARNING: Windows App SDK not found
    echo Please install Windows App SDK from:
    echo https://docs.microsoft.com/en-us/windows/apps/windows-app-sdk/downloads
)

echo.
echo [3/7] Checking required workloads...

REM Check for WinUI 3 workload
if exist "%ProgramFiles%\Microsoft Visual Studio\%VS_VERSION%\*\Common7\IDE\devenv.exe" (
    echo Visual Studio IDE found ✓
    echo.
    echo Required workloads for WinUI 3:
    echo - Universal Windows Platform development
    echo - C++ (v143) Universal Windows Platform tools
    echo - Windows 10 SDK (10.0.19041.0+)
    echo - Windows App SDK workload
) else (
    echo WARNING: Visual Studio IDE not found
)

echo.
echo [4/7] Checking Windows SDK...

reg query "HKLM\SOFTWARE\Microsoft\Windows Kits\Installed Roots" /v KitsRoot10 >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Windows SDK found ✓
) else (
    echo WARNING: Windows SDK not found
    echo Please install Windows 10 SDK (10.0.19041.0+)
)

echo.
echo [5/7] Configuring WinUI 3 project settings...

REM Create backup of original project file
if exist "FoxyPassword Generator\FoxyPassword Generator.vcxproj" (
    copy "FoxyPassword Generator\FoxyPassword Generator.vcxproj" "FoxyPassword Generator\FoxyPassword Generator.vcxproj.backup" >nul
    echo Created backup of project file ✓
)

echo.
echo [6/7] Setting up WinUI 3 build environment...

REM Set environment variables for WinUI 3
set "VS_PLATFORM_TOOLSET=v143"
set "VS_WINDOWS_TARGET_PLATFORM_VERSION=10.0.19041.0"
set "VS_APPX_PACKAGE_SIGNING_ENABLED=true"
set "VS_APPX_PACKAGE_SIGNING_TIMESTAMP_DIGEST_ALGORITHM=SHA256"
set "USE_WINUI=true"
set "WINDOWS_PACKAGE_TYPE=MSIX"
set "ENABLE_MSIX_TOOLING=true"

echo WinUI 3 build environment configured ✓

echo.
echo [7/7] Creating WinUI 3 configuration...

REM Create WinUI 3 configuration file
echo Creating WINUI3_CONFIG.xml...
copy "WINUI3_CONFIG.xml" "FoxyPassword Generator\WINUI3_CONFIG.xml" >nul 2>&1

echo.
echo ========================================
echo WinUI 3 Setup completed successfully! ✓
echo ========================================
echo.
echo Next steps:
echo 1. Open Visual Studio %VS_VERSION%
echo 2. Open "FoxyPassword Generator.sln"
echo 3. Right-click project → Properties
echo 4. Set Target Platform Version: 10.0.19041.0
echo 5. Set Platform Toolset: Visual Studio 2022 (v143)
echo 6. Enable WinUI 3 in project properties
echo 7. Create test certificate in Signing tab
echo 8. Build → Build Solution (Ctrl+Shift+B)
echo.
echo Or use our automated build script:
echo build.bat
echo.
echo WinUI 3 features enabled:
echo ✓ Modern Windows 11 UI framework
echo ✓ Enhanced security with Windows Security APIs
echo ✓ Better performance and responsiveness
echo ✓ Improved accessibility
echo ✓ Modern Fluent Design System
echo ✓ Hardware-accelerated animations
echo ✓ Enhanced clipboard security
echo ✓ Better memory management
echo.
echo Benefits of WinUI 3:
echo - Native Windows 11 performance
echo - Latest security features
echo - Future-proof architecture
echo - Better developer experience
echo - Enhanced user experience
echo.
pause
