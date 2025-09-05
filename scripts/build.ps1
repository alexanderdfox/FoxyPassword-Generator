# PowerShell Build Script for FoxyPassword Generator
# Run this script on Windows with Visual Studio installed

param(
    [string]$Configuration = "Release",
    [string]$Platform = "x64",
    [switch]$Clean,
    [switch]$Deploy,
    [switch]$Package
)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Building FoxyPassword Generator (Secure)" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

# Check if we're in the right directory
if (-not (Test-Path "FoxyPassword Generator.sln")) {
    Write-Host "ERROR: FoxyPassword Generator.sln not found!" -ForegroundColor Red
    Write-Host "Please run this script from the project root directory." -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

# Check for MSBuild
Write-Host "`n[1/5] Checking Visual Studio installation..." -ForegroundColor Green
$msbuildPath = Get-Command msbuild -ErrorAction SilentlyContinue
if (-not $msbuildPath) {
    Write-Host "ERROR: MSBuild not found!" -ForegroundColor Red
    Write-Host "Please install Visual Studio 2019/2022 with C++/WinRT workload." -ForegroundColor Yellow
    Write-Host "Or run from 'Developer Command Prompt for VS'" -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host "MSBuild found at: $($msbuildPath.Source)" -ForegroundColor Green

# Clean if requested
if ($Clean) {
    Write-Host "`n[2/5] Cleaning previous builds..." -ForegroundColor Green
    $releasePath = "FoxyPassword Generator\Release"
    if (Test-Path $releasePath) {
        Remove-Item -Path $releasePath -Recurse -Force
        Write-Host "Cleaned Release directory." -ForegroundColor Green
    }
}

# Build solution
Write-Host "`n[3/5] Building solution..." -ForegroundColor Green
$buildArgs = @(
    "FoxyPassword Generator.sln",
    "/p:Configuration=$Configuration",
    "/p:Platform=$Platform",
    "/p:AppxPackageSigningEnabled=true",
    "/p:AppxPackageSigningTimestampDigestAlgorithm=SHA256",
    "/p:AppxPackageSigningTimestampServer=http://timestamp.digicert.com",
    "/verbosity:minimal",
    "/nologo"
)

$buildResult = & msbuild $buildArgs

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n[4/5] Build completed successfully! ✅" -ForegroundColor Green
    
    Write-Host "`n📁 Build outputs:" -ForegroundColor Cyan
    $exePath = "FoxyPassword Generator\Release\PackageLayout\FoxyPassword Generator.exe"
    if (Test-Path $exePath) {
        $fileSize = (Get-Item $exePath).Length / 1KB
        Write-Host "   Executable: $exePath ($([math]::Round($fileSize, 1)) KB)" -ForegroundColor White
    }
    
    $packagePath = "FoxyPassword Generator\Release\PackageUploadLayout"
    if (Test-Path $packagePath) {
        Write-Host "   Package: $packagePath" -ForegroundColor White
    }
    
    Write-Host "`n🔒 Security features included:" -ForegroundColor Cyan
    Write-Host "   ✓ Cryptographically secure random generation" -ForegroundColor Green
    Write-Host "   ✓ Hardware-based entropy" -ForegroundColor Green
    Write-Host "   ✓ Input validation" -ForegroundColor Green
    Write-Host "   ✓ Password strength analysis" -ForegroundColor Green
    Write-Host "   ✓ Professional UI/UX" -ForegroundColor Green
    
    # Deploy if requested
    if ($Deploy) {
        Write-Host "`n[5/5] Deploying to local machine..." -ForegroundColor Green
        $deployArgs = @(
            "FoxyPassword Generator.sln",
            "/p:Configuration=$Configuration",
            "/p:Platform=$Platform",
            "/t:Deploy"
        )
        & msbuild $deployArgs
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Deployment successful! App should launch automatically." -ForegroundColor Green
        }
    }
    
    # Create package if requested
    if ($Package) {
        Write-Host "`n[5/5] Creating app package..." -ForegroundColor Green
        Write-Host "Please use Visual Studio to create app packages:" -ForegroundColor Yellow
        Write-Host "Project → Store → Create App Packages" -ForegroundColor Yellow
    }
    
    Write-Host "`n🚀 Next steps:" -ForegroundColor Cyan
    Write-Host "   1. Test the application locally" -ForegroundColor White
    Write-Host "   2. Create app package for distribution" -ForegroundColor White
    Write-Host "   3. Deploy to Windows Store (optional)" -ForegroundColor White
    
} else {
    Write-Host "`n❌ Build failed! Please check the error messages above." -ForegroundColor Red
    
    Write-Host "`n🔧 Troubleshooting:" -ForegroundColor Yellow
    Write-Host "   - Ensure Visual Studio 2019/2022 is installed" -ForegroundColor White
    Write-Host "   - Install C++/WinRT workload" -ForegroundColor White
    Write-Host "   - Install Windows 10 SDK (10.0.19041.0+)" -ForegroundColor White
    Write-Host "   - Run from Developer Command Prompt" -ForegroundColor White
}

Write-Host "`nBuild script completed." -ForegroundColor Cyan
Read-Host "Press Enter to exit"
