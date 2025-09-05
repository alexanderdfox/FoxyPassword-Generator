@echo off
REM Clean script for FoxyPassword Generator
REM Removes build artifacts and temporary files

echo Cleaning FoxyPassword Generator project...

REM Remove build output directories
if exist "Debug" rmdir /s /q "Debug"
if exist "Release" rmdir /s /q "Release"
if exist "x64" rmdir /s /q "x64"
if exist "x86" rmdir /s /q "x86"
if exist "ARM" rmdir /s /q "ARM"
if exist "ARM64" rmdir /s /q "ARM64"
if exist "bin" rmdir /s /q "bin"
if exist "obj" rmdir /s /q "obj"

REM Remove UWP specific build artifacts
if exist "AppPackages" rmdir /s /q "AppPackages"
if exist "BundleArtifacts" rmdir /s /q "BundleArtifacts"
if exist "PackageArtifacts" rmdir /s /q "PackageArtifacts"

REM Remove generated files
if exist "Generated Files" rmdir /s /q "Generated Files"

REM Remove temporary files
del /q *.tmp 2>nul
del /q *.temp 2>nul
del /q *.log 2>nul
del /q *.user 2>nul
del /q *.suo 2>nul
del /q *.userosscache 2>nul
del /q *.userprefs 2>nul

echo Clean completed!
pause
