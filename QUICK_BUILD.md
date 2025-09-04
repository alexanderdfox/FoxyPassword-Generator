# 🚀 Quick Build Guide for Windows

## Prerequisites
- Windows 10/11 with Visual Studio 2019/2022
- C++/WinRT workload installed
- Windows 10 SDK (10.0.19041.0+)

## Quick Build Commands

### Option 1: Automated Script (Recommended)
```cmd
# Run from project root directory
build.bat
```

### Option 2: PowerShell Script (Advanced)
```powershell
# Basic build
.\build.ps1

# Build with deployment
.\build.ps1 -Deploy

# Clean build
.\build.ps1 -Clean

# Build for different platform
.\build.ps1 -Platform x86
```

### Option 3: Manual Build
```cmd
# From Developer Command Prompt
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64
```

## Expected Output
```
Release/PackageLayout/FoxyPassword Generator.exe  (~200-250 KB)
Release/PackageUploadLayout/                     (Store package)
```

## Troubleshooting
- **MSBuild not found**: Install Visual Studio with C++/WinRT workload
- **SDK missing**: Install Windows 10 SDK 10.0.19041.0+
- **Certificate issues**: Create test certificate in project properties

## Security Features Built-In
✅ Cryptographically secure random generation  
✅ Hardware-based entropy  
✅ Input validation  
✅ Password strength analysis  
✅ Professional UI/UX  

---
*For detailed instructions, see BUILD.md*
