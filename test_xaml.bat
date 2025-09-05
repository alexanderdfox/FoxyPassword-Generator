@echo off
echo Testing XAML XML Parsing Fix...
echo.

echo [1/2] Checking for XML parsing errors...

REM Try to build just the XAML to check for parsing errors
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /t:MarkupCompilePass1 /m

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [2/2] ✅ XAML parsing successful! No XML entity errors.
    echo.
    echo 🔧 Fixed XML entities:
    echo    ✓ &amp; for ampersand (&)
    echo    ✓ &quot; for quote (")
    echo    ✓ &lt; and &gt; for angle brackets (< >)
    echo.
    echo 🚀 Ready for full build!
) else (
    echo.
    echo ❌ XAML parsing still has errors. Check the output above.
)

echo.
pause
