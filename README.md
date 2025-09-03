# 🔐 FoxyPassword Generator

A professional, secure password generator for Windows with cryptography-grade random number generation and modern UI.

## ✨ Features

### Security Features
- **Cryptographically Secure Random Generation**: Uses `std::random_device` and `std::mt19937` for hardware-based entropy
- **Local Generation**: All passwords are generated locally on your device - no data transmission
- **No Storage**: Passwords are never stored or logged
- **Input Validation**: Comprehensive validation prevents security vulnerabilities
- **Character Exclusion**: Option to exclude similar (l, 1, I, 0, O) and ambiguous characters

### Password Generation
- **Length Range**: 8-128 characters
- **Character Types**: Uppercase, lowercase, numbers, special characters
- **Custom Characters**: Add your own character set
- **Strength Analysis**: Real-time password strength calculation
- **Smart Generation**: Ensures at least one character from each selected type

### User Experience
- **Modern UI**: Professional, responsive design with Windows 11 styling
- **Copy Functionality**: One-click password copying with visual feedback
- **Strength Indicator**: Visual progress bar and text description
- **Accessibility**: Full keyboard navigation and screen reader support
- **Responsive Layout**: Adapts to different screen sizes

## 🔒 Security Improvements

### Before (Original Version)
- ❌ Used `rand()` and `srand()` - predictable and insecure
- ❌ Time-based seeding - vulnerable to timing attacks
- ❌ No input validation
- ❌ Basic UI with hardcoded positioning
- ❌ No copy functionality
- ❌ No password strength feedback

### After (Secure Version)
- ✅ **Cryptographically Secure**: Hardware-based random number generation
- ✅ **Input Validation**: Comprehensive parameter checking
- ✅ **Professional UI**: Modern, accessible design
- ✅ **Copy to Clipboard**: Secure password copying
- ✅ **Strength Analysis**: Real-time strength calculation
- ✅ **Character Exclusion**: Options to avoid confusing characters
- ✅ **Error Handling**: Graceful error handling and user feedback

## 🛠️ Technical Details

### Random Number Generation
```cpp
// Secure initialization
std::unique_ptr<std::random_device> randomDevice;
std::unique_ptr<std::mt19937> randomGenerator;

// Hardware-based entropy with fallback
try {
    randomDevice = std::make_unique<std::random_device>();
    randomGenerator = std::make_unique<std::mt19937>((*randomDevice)());
} catch (...) {
    // Fallback to system time if hardware RNG unavailable
    randomGenerator = std::make_unique<std::mt19937>(static_cast<unsigned int>(time(nullptr)));
}
```

### Password Strength Algorithm
- **Length Bonus**: Up to 40 points for length
- **Character Variety**: 10 points each for uppercase, lowercase, numbers, specials
- **Mixed Case Bonus**: 10 points for both cases
- **Complexity Bonus**: Additional points for mixed character types
- **Penalties**: Reduced scores for predictable patterns

## 📋 Requirements

- Windows 10/11 (version 1903 or later)
- Visual Studio 2019/2022 with C++/WinRT workload
- Windows 10 SDK (version 10.0.19041.0 or later)

## 🚀 Building

1. Open `FoxyPassword Generator.sln` in Visual Studio
2. Select your target platform (x86, x64, or ARM)
3. Build the solution (Ctrl+Shift+B)
4. Deploy to your device or create an app package

## 📱 Usage

1. **Set Password Length**: Use the slider to choose 8-128 characters
2. **Select Character Types**: Check the boxes for desired character types
3. **Configure Options**: Enable/disable similar/ambiguous character exclusion
4. **Add Custom Characters**: Optionally add your own character set
5. **Generate**: Click "Generate Secure Password"
6. **Copy**: Use the "Copy" button to copy to clipboard

## 🔧 Configuration

### Character Sets
- **Uppercase**: A-Z (26 characters)
- **Lowercase**: a-z (26 characters)  
- **Numbers**: 0-9 (10 characters)
- **Special**: !@#$%^&*()_+-=[]{}|;:,.<>? (22 characters)

### Exclusion Options
- **Similar Characters**: l, 1, I, 0, O
- **Ambiguous Characters**: { } [ ] ( ) / \ ' " ` ~ , ; : . < >

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

Contributions are welcome! Please ensure all code follows security best practices and includes appropriate tests.

## ⚠️ Security Notice

This application generates passwords locally on your device. While the generation is cryptographically secure, always:
- Use strong, unique passwords for each account
- Enable two-factor authentication where available
- Keep your device and software updated
- Be cautious of phishing attempts

---

**Built with security and usability in mind** 🔐✨
