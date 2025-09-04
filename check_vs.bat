@echo off
REM Visual Studio Installation Checker
REM Run this to diagnose build environment issues

echo ========================================
echo Visual Studio Installation Checker
echo ========================================

echo.
echo [1/5] Checking for Visual Studio installations...

REM Check for Visual Studio 2019/2022
set "VS_FOUND="
for %%v in (2022 2019) do (
    if exist "%ProgramFiles%\Microsoft Visual Studio\%%v\*\MSBuild\Current\Bin\MSBuild.exe" (
        echo Found Visual Studio %%v at: %ProgramFiles%\Microsoft Visual Studio\%%v\
        set "VS_FOUND=%%v"
        goto :found_vs
    )
    if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\%%v\*\MSBuild\Current\Bin\MSBuild.exe" (
        echo Found Visual Studio %%v at: %ProgramFiles(x86)%\Microsoft Visual Studio\%%v\
        set "VS_FOUND=%%v"
        goto :found_vs
    )
)

echo ERROR: No Visual Studio 2019/2022 found!
echo Please install Visual Studio 2019/2022 from:
echo https://visualstudio.microsoft.com/downloads/
goto :end

:found_vs
echo.
echo [2/5] Checking MSBuild availability...

where msbuild >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo MSBuild found in PATH ✓
    msbuild -version
) else (
    echo MSBuild not in PATH ❌
    echo.
    echo SOLUTION: Use Developer Command Prompt
    echo Start Menu → Visual Studio %VS_FOUND% → Developer Command Prompt
    echo.
    echo Or add MSBuild to PATH manually:
    echo set PATH=%%PATH%%;%ProgramFiles%\Microsoft Visual Studio\%VS_FOUND%\*\MSBuild\Current\Bin
)

echo.
echo [3/5] Checking Windows SDK...

reg query "HKLM\SOFTWARE\Microsoft\Windows Kits\Installed Roots" /v KitsRoot10 >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Windows SDK found ✓
    for /f "tokens=3" %%i in ('reg query "HKLM\SOFTWARE\Microsoft\Windows Kits\Installed Roots" /v KitsRoot10 2^>nul') do (
        echo SDK Location: %%i
    )
) else (
    echo Windows SDK not found ❌
    echo Please install Windows 10 SDK (10.0.19041.0+)
)

echo.
echo [4/5] Checking C++/WinRT workload...

if exist "%ProgramFiles%\Microsoft Visual Studio\%VS_FOUND%\*\Common7\IDE\devenv.exe" (
    echo Visual Studio IDE found ✓
    echo To install C++/WinRT workload:
    echo 1. Open Visual Studio Installer
    echo 2. Modify → Workloads
    echo 3. Check "Universal Windows Platform development"
    echo 4. Check "C++ (v143) Universal Windows Platform tools"
) else (
    echo Visual Studio IDE not found ❌
)

echo.
echo [5/5] Quick Fix Options:

echo.
echo OPTION 1: Use Developer Command Prompt
echo Start Menu → Visual Studio %VS_FOUND% → Developer Command Prompt for VS %VS_FOUND%
echo Then run: build.bat

echo.
echo OPTION 2: Install Missing Components
echo 1. Open Visual Studio Installer
echo 2. Modify → Workloads
echo 3. Check "Universal Windows Platform development"
echo 4. Install

echo.
echo OPTION 3: Manual PATH Setup
echo Add to PATH: %ProgramFiles%\Microsoft Visual Studio\%VS_FOUND%\*\MSBuild\Current\Bin

:end
echo.
echo ========================================
echo Check completed.
echo ========================================
pause
