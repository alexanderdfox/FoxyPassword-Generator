# 🔧 Visual Studio Installation Guide

## Quick Fix Steps

### Step 1: Run Diagnostic Tool
```cmd
check_vs.bat
```
This will tell you exactly what's missing.

### Step 2: Install Visual Studio (if needed)

1. **Download Visual Studio 2022 Community**
   - Go to: https://visualstudio.microsoft.com/downloads/
   - Click "Download Visual Studio Community 2022"
   - It's **FREE** for individual developers

2. **Run the Installer**
   - Launch the downloaded `.exe` file
   - Wait for Visual Studio Installer to load

3. **Select Workloads**
   - ✅ **Universal Windows Platform development**
   - ✅ **C++ (v143) Universal Windows Platform tools**
   - ✅ **Windows 10 SDK (10.0.19041.0)**

4. **Install**
   - Click "Install" button
   - Wait 30-60 minutes for installation
   - Restart computer if prompted

### Step 3: Use Developer Command Prompt

**Instead of regular Command Prompt, use:**
```
Start Menu → Visual Studio 2022 → Developer Command Prompt for VS 2022
```

Then navigate to your project and run:
```cmd
cd "C:\path\to\FoxyPassword-Generator"
build.bat
```

### Step 4: Alternative - Add MSBuild to PATH

If you prefer using regular Command Prompt:

1. **Find MSBuild location**
   ```cmd
   dir "C:\Program Files\Microsoft Visual Studio\2022\*\MSBuild\Current\Bin\MSBuild.exe"
   ```

2. **Add to PATH**
   - Right-click "This PC" → Properties
   - Advanced system settings → Environment Variables
   - Edit "Path" → Add new entry:
   ```
   C:\Program Files\Microsoft Visual Studio\2022\*\MSBuild\Current\Bin
   ```

## Common Issues & Solutions

### Issue: "MSBuild not found"
**Solution:** Use Developer Command Prompt or install Visual Studio

### Issue: "Windows SDK not found"
**Solution:** Install Windows 10 SDK 10.0.19041.0+ from Visual Studio Installer

### Issue: "C++/WinRT workload missing"
**Solution:** In Visual Studio Installer → Modify → Workloads → Check "Universal Windows Platform development"

### Issue: "Certificate not found"
**Solution:** Right-click project → Properties → Signing → Create Test Certificate

## Verification

After installation, run:
```cmd
check_vs.bat
```

You should see:
- ✅ Visual Studio found
- ✅ MSBuild found in PATH
- ✅ Windows SDK found
- ✅ C++/WinRT workload available

## Next Steps

Once Visual Studio is properly installed:
1. Run `check_vs.bat` to verify
2. Use Developer Command Prompt
3. Run `build.bat` to build the secure password generator

---
*This will give you a professional, secure password generator with cryptography-grade random generation!*
