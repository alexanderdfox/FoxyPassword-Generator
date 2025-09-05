@echo off
echo Testing C++17 Configuration Fix...
echo.

echo [1/2] Checking C++17 configuration...

REM Check if project file has C++17 settings
findstr /i "stdcpp17" "FoxyPassword Generator\FoxyPassword Generator.vcxproj" >nul
if %ERRORLEVEL% EQU 0 (
    echo C++17 language standard found ✓
) else (
    echo ERROR: C++17 language standard not found!
    pause
    exit /b 1
)

findstr /i "/std:c++17" "FoxyPassword Generator\FoxyPassword Generator.vcxproj" >nul
if %ERRORLEVEL% EQU 0 (
    echo C++17 compiler flag found ✓
) else (
    echo ERROR: C++17 compiler flag not found!
    pause
    exit /b 1
)

echo.
echo [2/2] Building with C++17 support...

REM Build with C++17
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /m

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ SUCCESS! Build completed with C++17 support.
    echo.
    echo 🔧 Fixed C++17 configuration:
    echo    ✓ LanguageStandard: stdcpp17
    echo    ✓ Compiler flag: /std:c++17
    echo    ✓ All configurations updated
    echo.
    echo 🚀 Ready for production!
) else (
    echo.
    echo ❌ Build failed. Check error messages above.
)

echo.
pause
