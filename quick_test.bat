@echo off
echo Testing Fixed Solution Configuration...
echo.

REM Test x64 build (recommended)
echo Building Release|x64...
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /m

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ SUCCESS! Build completed without ARM errors.
    echo.
    echo 📁 Output location: FoxyPassword Generator\Release\PackageLayout\
    echo 🚀 Ready for deployment!
) else (
    echo.
    echo ❌ Build failed. Check error messages above.
)

echo.
pause
