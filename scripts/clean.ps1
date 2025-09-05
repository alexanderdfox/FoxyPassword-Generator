# PowerShell Clean Script for FoxyPassword Generator
# Removes build artifacts and temporary files

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Cleaning FoxyPassword Generator Project" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

# Function to safely remove directory
function Remove-DirectoryIfExists {
    param([string]$Path)
    if (Test-Path $Path) {
        Write-Host "Removing: $Path" -ForegroundColor Yellow
        Remove-Item -Path $Path -Recurse -Force
    }
}

# Function to safely remove files
function Remove-FilesIfExists {
    param([string]$Pattern)
    $files = Get-ChildItem -Path . -Filter $Pattern -Recurse -ErrorAction SilentlyContinue
    if ($files) {
        Write-Host "Removing files matching: $Pattern" -ForegroundColor Yellow
        $files | Remove-Item -Force
    }
}

Write-Host "`n[1/4] Removing build output directories..." -ForegroundColor Green
Remove-DirectoryIfExists "Debug"
Remove-DirectoryIfExists "Release"
Remove-DirectoryIfExists "x64"
Remove-DirectoryIfExists "x86"
Remove-DirectoryIfExists "ARM"
Remove-DirectoryIfExists "ARM64"
Remove-DirectoryIfExists "bin"
Remove-DirectoryIfExists "obj"

Write-Host "`n[2/4] Removing UWP build artifacts..." -ForegroundColor Green
Remove-DirectoryIfExists "AppPackages"
Remove-DirectoryIfExists "BundleArtifacts"
Remove-DirectoryIfExists "PackageArtifacts"
Remove-DirectoryIfExists "Generated Files"

Write-Host "`n[3/4] Removing temporary files..." -ForegroundColor Green
Remove-FilesIfExists "*.tmp"
Remove-FilesIfExists "*.temp"
Remove-FilesIfExists "*.log"
Remove-FilesIfExists "*.user"
Remove-FilesIfExists "*.suo"
Remove-FilesIfExists "*.userosscache"
Remove-FilesIfExists "*.userprefs"

Write-Host "`n[4/4] Clean completed! ✅" -ForegroundColor Green

Write-Host "`n📁 Current project structure:" -ForegroundColor Cyan
Get-ChildItem -Path . -Name | Where-Object { $_ -notlike ".*" } | Sort-Object

Write-Host "`nClean script completed." -ForegroundColor Cyan
Read-Host "Press Enter to exit"
