# 🔐 FoxyPassword Generator

A professional-grade password generator built with C++/WinRT and UWP for Windows 10/11. Features cryptographically secure random number generation, modern UI design, and comprehensive security features.

## ✨ Features

### 🔒 Security Features
- **Cryptographically Secure RNG**: Uses `std::random_device` and Windows Security APIs
- **Hardware-Based Entropy**: Leverages `CryptographicBuffer::GenerateRandom` for additional entropy
- **Input Validation**: Comprehensive validation to prevent attacks
- **Password Strength Analysis**: Real-time strength calculation and visualization
- **Character Exclusion**: Options to exclude similar and ambiguous characters
- **Memory Safety**: Smart pointers and RAII patterns
- **Thread Safety**: Mutex-protected random number generation

### 🎨 Modern UI/UX
- **UWP Design**: Native Windows 10/11 styling and controls
- **Fluent Design System**: Modern card-based layout with proper spacing
- **Responsive Layout**: Adapts to different screen sizes
- **Accessibility**: Screen reader support and keyboard navigation
- **Visual States**: Proper hover and press animations
- **Professional Typography**: Clean, readable fonts

### ⚙️ Password Generation
- **Customizable Length**: 8-128 characters
- **Character Sets**: Uppercase, lowercase, numbers, special characters
- **Custom Characters**: User-defined character sets
- **Exclusion Options**: Similar characters (l, 1, I, 0, O) and ambiguous characters
- **Real-time Preview**: See password strength as you configure options
- **One-Click Copy**: Easy password copying to clipboard

## 🚀 Quick Start

### Prerequisites
- **Windows 10/11** (version 1903 or later)
- **Visual Studio 2022** with C++/WinRT workload
- **Windows 10 SDK** (10.0.19041.0 or later)

### Building
```cmd
# Quick build using PowerShell script
scripts\build.ps1

# Or using batch script
scripts\build.bat

# Manual build
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /m
```

### Running
1. Build the project using one of the methods above
2. Navigate to `FoxyPassword Generator\x64\Release\PackageLayout\`
3. Run `FoxyPassword Generator.exe`

## 📁 Project Structure

```
FoxyPassword-Generator/
├── 📁 .github/workflows/           # GitHub Actions CI/CD
│   └── 📄 msbuild.yml              # Automated build workflow
├── 📁 FoxyPassword Generator/      # Main project directory
│   ├── 📄 App.xaml/.cpp/.h         # Application entry point
│   ├── 📄 MainPage.xaml/.cpp/.h    # Main UI and password generation logic
│   ├── 📄 Package.appxmanifest     # App package manifest
│   ├── 📄 FoxyPassword Generator.vcxproj # Project configuration
│   ├── 📄 pch.cpp/.h              # Precompiled headers
│   └── 📁 Assets/                  # App icons and images
│       ├── 🖼️ LockScreenLogo.scale-200.png
│       ├── 🖼️ SplashScreen.scale-200.png
│       ├── 🖼️ Square150x150Logo.scale-200.png
│       ├── 🖼️ Square44x44Logo.scale-200.png
│       ├── 🖼️ Square44x44Logo.targetsize-24_altform-unplated.png
│       ├── 🖼️ StoreLogo.png
│       └── 🖼️ Wide310x150Logo.scale-200.png
├── 📁 scripts/                     # Build and cleanup scripts
│   ├── 🔧 build.bat               # Windows batch build script
│   ├── 🔧 build.ps1               # PowerShell build script
│   ├── 🔧 clean.bat               # Windows batch cleanup script
│   └── 🔧 clean.ps1               # PowerShell cleanup script
├── 📄 .gitignore                   # Comprehensive ignore rules
├── 📄 FoxyPassword Generator.sln  # Solution file
├── 📄 README.md                   # This file
└── 📄 LICENSE                     # GPL v3 License
```

## 🔧 Technical Details

### Security Implementation
- **Random Number Generation**: `std::random_device` + `std::mt19937`
- **Windows Security APIs**: `CryptographicBuffer::GenerateRandom`
- **Password Strength**: Entropy-based calculation with character set analysis
- **Input Validation**: Comprehensive bounds checking and sanitization
- **Thread Safety**: Mutex-protected random number generation

### UI Framework
- **UWP**: Modern Windows 10/11 native controls
- **XAML**: Declarative UI with proper data binding
- **Visual States**: UWP-compatible hover/press animations
- **Theme Resources**: Automatic light/dark mode support

### Build Configuration
- **Platform**: x64 and x86 (Win32)
- **Windows SDK**: 10.0.19041.0
- **Toolset**: Visual Studio 2022 (v143)
- **Language Standard**: C++17

## 🛠️ Recent Updates

### Bug Fixes
- **Fixed Generate Button Crash**: Resolved XAML styling errors that caused crashes
- **Improved Error Handling**: Added comprehensive null checks and validation
- **Enhanced Thread Safety**: Fixed race conditions in random number generation
- **Cleaned Up Project**: Removed generated files and added proper `.gitignore`

### Code Quality Improvements
- **Better Error Messages**: More informative error handling throughout
- **Input Validation**: Enhanced validation for all user inputs
- **Memory Safety**: Improved smart pointer usage and RAII patterns
- **Code Organization**: Cleaner project structure with proper separation

## 🧹 Project Maintenance

### Cleaning Build Artifacts
```cmd
# Clean using PowerShell script
scripts\clean.ps1

# Or using batch script
scripts\clean.bat
```

### Git Workflow
The project includes a comprehensive `.gitignore` that excludes:
- Build outputs (`Debug/`, `Release/`, `bin/`, `obj/`)
- Generated files (`Generated Files/`, `*.g.h`, `*.xbf`)
- Temporary files (`*.tmp`, `*.log`, `*.user`)
- Security-sensitive files (`*.pfx`, certificates)
- IDE files (`.vs/`, `.vscode/`)

## 🛡️ Security Notice

This application generates cryptographically secure passwords using:
- Hardware-based random number generation
- Windows Security APIs for additional entropy
- Local processing (no data transmission)
- Input validation and bounds checking
- Memory-safe C++ practices
- Thread-safe operations

**Always verify password strength** and use appropriate length for your security requirements.

## 📄 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly
5. Commit your changes (`git commit -m 'Add some amazing feature'`)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

### Development Guidelines
- Follow C++17 best practices
- Use RAII and smart pointers
- Add comprehensive error handling
- Test on both Debug and Release configurations
- Update documentation for new features

## 🐛 Troubleshooting

### Common Issues
- **Build Errors**: Ensure Visual Studio 2022 with C++/WinRT workload is installed
- **SDK Issues**: Verify Windows 10 SDK (10.0.19041.0+) is installed
- **Runtime Crashes**: Check that all dependencies are properly installed

### Getting Help
- Check the [Issues](https://github.com/yourusername/FoxyPassword-Generator/issues) page
- Review the build logs for specific error messages
- Ensure all prerequisites are met

## 📞 Support

For issues and questions:
- Open an issue on GitHub
- Check existing issues for solutions
- Review the troubleshooting section above

---

**Built with ❤️ for Windows 10/11 using UWP and C++/WinRT**
