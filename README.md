# 🔐 FoxyPassword Generator

A professional-grade password generator built with C++/WinRT and WinUI 3 for Windows 11. Features cryptographically secure random number generation, modern UI design, and comprehensive security features.

## ✨ Features

### 🔒 Security Features
- **Cryptographically Secure RNG**: Uses `std::random_device` and Windows Security APIs
- **Hardware-Based Entropy**: Leverages `CryptographicBuffer::GenerateRandom` for additional entropy
- **Input Validation**: Comprehensive validation to prevent attacks
- **Password Strength Analysis**: Real-time strength calculation and visualization
- **Character Exclusion**: Options to exclude similar and ambiguous characters
- **Memory Safety**: Smart pointers and RAII patterns

### 🎨 Modern UI/UX
- **WinUI 3 Design**: Native Windows 11 styling and controls
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

## 📁 Project Structure

```
FoxyPassword-Generator/
├── 📁 FoxyPassword Generator/          # Main project directory
│   ├── 📄 App.xaml                      # Application resources and styling
│   ├── 📄 App.xaml.cpp/.h               # Application entry point
│   ├── 📄 MainPage.xaml                 # Main UI layout
│   ├── 📄 MainPage.xaml.cpp/.h         # Password generation logic
│   ├── 📄 Package.appxmanifest          # App package manifest
│   ├── 📄 FoxyPassword Generator.vcxproj # Project configuration
│   ├── 📄 FoxyPassword Generator.sln   # Solution file
│   ├── 📄 pch.cpp/.h                   # Precompiled headers
│   └── 📁 Assets/                       # App icons and images
│       ├── 🖼️ LockScreenLogo.scale-200.png
│       ├── 🖼️ SplashScreen.scale-200.png
│       ├── 🖼️ Square150x150Logo.scale-200.png
│       ├── 🖼️ Square44x44Logo.scale-200.png
│       ├── 🖼️ Square44x44Logo.targetsize-24_altform-unplated.png
│       ├── 🖼️ StoreLogo.png
│       └── 🖼️ Wide310x150Logo.scale-200.png
├── 📁 docs/                             # Documentation
│   ├── 📄 BUILD.md                      # Detailed build instructions
│   ├── 📄 QUICK_BUILD.md               # Quick build reference
│   ├── 📄 VS_INSTALL_GUIDE.md          # Visual Studio installation guide
│   ├── 📄 VS_SETUP.md                  # Visual Studio setup guide
│   ├── 📄 WINUI_MIGRATION.md           # WinUI 3 migration guide
│   ├── 📄 SDK_VERSION_FIX.md           # SDK version troubleshooting
│   └── 📄 SECURITY_ANALYSIS.md         # Security feature analysis
├── 📁 scripts/                          # Build scripts
│   ├── 🔧 build.bat                    # Windows batch build script
│   └── 🔧 build.ps1                    # PowerShell build script
├── 📄 README.md                         # This file
└── 📄 LICENSE                           # MIT License
```

## 🚀 Quick Start

### Prerequisites
- **Windows 10/11** (version 1903 or later)
- **Visual Studio 2022** with C++/WinRT workload
- **Windows 10 SDK** (10.0.22621.0 or later)

### Building
```cmd
# Quick build
scripts\build.bat

# Or PowerShell
scripts\build.ps1

# Manual build
msbuild "FoxyPassword Generator.sln" /p:Configuration=Release /p:Platform=x64 /m
```

### Running
1. Build the project
2. Navigate to `FoxyPassword Generator\x64\Release\PackageLayout\`
3. Run `FoxyPassword Generator.exe`

## 🔧 Technical Details

### Security Implementation
- **Random Number Generation**: `std::random_device` + `std::mt19937`
- **Windows Security APIs**: `CryptographicBuffer::GenerateRandom`
- **Password Strength**: Entropy-based calculation with character set analysis
- **Input Validation**: Comprehensive bounds checking and sanitization

### UI Framework
- **WinUI 3**: Modern Windows 11 native controls
- **XAML**: Declarative UI with proper data binding
- **Visual States**: UWP-compatible hover/press animations
- **Theme Resources**: Automatic light/dark mode support

### Build Configuration
- **Platform**: x64 and x86 (Win32)
- **Windows SDK**: 10.0.22621.0
- **Toolset**: Visual Studio 2022 (v143)
- **Language Standard**: C++17

## 📚 Documentation

- **[Build Guide](docs/BUILD.md)** - Detailed build instructions
- **[Quick Build](docs/QUICK_BUILD.md)** - Fast build reference
- **[VS Installation](docs/VS_INSTALL_GUIDE.md)** - Visual Studio setup
- **[VS Configuration](docs/VS_SETUP.md)** - Project configuration
- **[WinUI Migration](docs/WINUI_MIGRATION.md)** - WinUI 3 features
- **[SDK Troubleshooting](docs/SDK_VERSION_FIX.md)** - Common issues
- **[Security Analysis](docs/SECURITY_ANALYSIS.md)** - Security features

## 🛡️ Security Notice

This application generates cryptographically secure passwords using:
- Hardware-based random number generation
- Windows Security APIs for additional entropy
- Local processing (no data transmission)
- Input validation and bounds checking
- Memory-safe C++ practices

**Always verify password strength** and use appropriate length for your security requirements.

## 📄 License

This project is licensed under the GPL 3 License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📞 Support

For issues and questions:
- Check the [documentation](docs/) first
- Review [common issues](docs/SDK_VERSION_FIX.md)
- Open an issue on GitHub

---


**Built with ❤️ for Windows 11 using WinUI 3**
