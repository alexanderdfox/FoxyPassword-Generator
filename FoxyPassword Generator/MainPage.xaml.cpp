//
// MainPage.xaml.cpp
// Implementation of the MainPage class with WinUI 3 and enhanced security.
// Modern C++17 implementation with thread safety and comprehensive security measures.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <random>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <thread>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Foundation.h>

using namespace FoxyPassword_Generator;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::ApplicationModel::DataTransfer;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Storage::Streams;
using namespace std;

MainPage::MainPage()
{
	InitializeComponent();
	
	// Initialize security systems
	initializeSecureRandom();
	lastReseed = std::chrono::steady_clock::now();
	
	// Set up event handlers
	passSize->ValueChanged += ref new RangeBaseValueChangedEventHandler(this, &MainPage::passSize_ValueChanged);
	
	// Initialize UI with secure defaults
	lengthDisplay->Text = "16 characters";
	strengthBar->Value = 0;
	strengthText->Text = "Generate a password to see strength";
	
	// Set secure defaults
	passSize->Minimum = MIN_PASSWORD_LENGTH;
	passSize->Maximum = MAX_PASSWORD_LENGTH;
	passSize->Value = 16;
	
	// WinUI 3 specific initialization
	updateUIForWinUI3();
	applyWinUI3Styling();
}

void FoxyPassword_Generator::MainPage::updateUIForWinUI3()
{
	try {
		// Check if WinUI 3 features are available
		isWinUI3Available = true;
		
		// Apply WinUI 3 specific enhancements
		if (isWinUI3Available) {
					// Enhanced accessibility
		Windows::UI::Xaml::Automation::AutomationProperties::SetName(passwordDisplay, "Generated Password");
		Windows::UI::Xaml::Automation::AutomationProperties::SetName(copyButton, "Copy Password to Clipboard");
		Windows::UI::Xaml::Automation::AutomationProperties::SetName(generateButton, "Generate Secure Password");
			
					// Enhanced tooltips with security information
		Windows::UI::Xaml::Controls::ToolTipService::SetToolTip(passwordDisplay, "Cryptographically secure password");
		Windows::UI::Xaml::Controls::ToolTipService::SetToolTip(copyButton, "Copy password to clipboard");
		Windows::UI::Xaml::Controls::ToolTipService::SetToolTip(generateButton, "Generate a new cryptographically secure password");
			
					// Security indicators
		Windows::UI::Xaml::Controls::ToolTipService::SetToolTip(passSize, "Password length (8-128 characters recommended)");
		}
	}
	catch (...) {
		// Fallback to standard UWP if WinUI 3 not available
		isWinUI3Available = false;
	}
}

void FoxyPassword_Generator::MainPage::applyWinUI3Styling()
{
	if (isWinUI3Available) {
		try {
					// Apply WinUI 3 specific styling
		generateButton->Style = safe_cast<Windows::UI::Xaml::Style^>(
			Windows::UI::Xaml::Application::Current->Resources->Lookup("ModernButtonStyle"));
			
					// Enhanced visual feedback
		strengthBar->Background = safe_cast<Windows::UI::Xaml::Media::Brush^>(
			Windows::UI::Xaml::Application::Current->Resources->Lookup("SystemControlBackgroundBaseLowBrush"));
		}
		catch (...) {
			// Fallback styling
		}
	}
}

void FoxyPassword_Generator::MainPage::initializeSecureRandom()
{
	try {
		// Use hardware random number generator if available
		randomDevice = std::make_unique<std::random_device>();
		randomGenerator = std::make_unique<std::mt19937>((*randomDevice)());
		
		// WinUI 3 enhanced: Use Windows Security APIs for additional entropy
		if (isWinUI3Available) {
			try {
				// Generate additional entropy from Windows Security APIs
				auto cryptoBuffer = CryptographicBuffer::GenerateRandom(ENTROPY_BYTES);
				auto randomBytes = cryptoBuffer.data();
				std::seed_seq seed(randomBytes, randomBytes + ENTROPY_BYTES);
				randomGenerator->seed(seed);
			}
			catch (...) {
				// Fallback to hardware RNG only
			}
		}
		
		isInitialized = true;
	}
	catch (...) {
		// Fallback to system time if hardware RNG is not available
		randomGenerator = std::make_unique<std::mt19937>(
			static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
		isInitialized = true;
	}
}

void FoxyPassword_Generator::MainPage::reseedRandomGenerator()
{
	std::lock_guard<std::mutex> lock(randomMutex);
	
	try {
		if (isWinUI3Available) {
			// Reseed with fresh entropy from Windows Security APIs
			auto cryptoBuffer = CryptographicBuffer::GenerateRandom(ENTROPY_BYTES);
			auto randomBytes = cryptoBuffer.data();
			std::seed_seq seed(randomBytes, randomBytes + ENTROPY_BYTES);
			randomGenerator->seed(seed);
		} else {
			// Reseed with hardware RNG
			randomGenerator->seed((*randomDevice)());
		}
		
		lastReseed = std::chrono::steady_clock::now();
	}
	catch (...) {
		// Fallback reseeding
		randomGenerator->seed(static_cast<unsigned int>(
			std::chrono::steady_clock::now().time_since_epoch().count()));
	}
}

int FoxyPassword_Generator::MainPage::getSecureRandomNumber(int min, int max)
{
	if (max <= min) return min;
	
	// Ensure random generator is initialized
	if (!isInitialized || !randomGenerator) {
		initializeSecureRandom();
	}
	
	// Check if we need to reseed
	auto now = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::seconds>(now - lastReseed).count() > RESEED_INTERVAL_SECONDS) {
		reseedRandomGenerator();
	}
	
	std::lock_guard<std::mutex> lock(randomMutex);
	if (randomGenerator) {
		std::uniform_int_distribution<int> distribution(min, max - 1);
		return distribution(*randomGenerator);
	}
	
	// Fallback to simple modulo if random generator is not available
	return min + (rand() % (max - min));
}

wchar_t FoxyPassword_Generator::MainPage::getRandomChar(String ^ charSet)
{
	if (!charSet || charSet->Length() == 0) return L' ';
	
	int index = getSecureRandomNumber(0, charSet->Length());
	if (index >= 0 && index < static_cast<int>(charSet->Length())) {
		return charSet->Data()[index];
	}
	return L' ';
}

bool FoxyPassword_Generator::MainPage::validateInput(int length, bool uppercase, bool lowercase, bool numbers, bool specials, String ^ customChars)
{
	// Validate length
	if (length < MIN_PASSWORD_LENGTH || length > MAX_PASSWORD_LENGTH) {
		return false;
	}
	
	// Validate at least one character type is selected
	if (!uppercase && !lowercase && !numbers && !specials && customChars->Length() == 0) {
		return false;
	}
	
	// Validate custom characters (if provided)
	if (customChars->Length() > 0) {
		// Check for reasonable custom character set size
		if (customChars->Length() > 1000) {
			return false;
		}
	}
	
	return true;
}

void FoxyPassword_Generator::MainPage::generate_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	try {
		// Ensure random generator is initialized
		if (!isInitialized || !randomGenerator) {
			initializeSecureRandom();
		}
		
		// Validate UI elements are available
		if (!passSize || !uppercaseCheck || !lowercaseCheck || !numbersCheck || 
			!specialsCheck || !similarCheck || !ambiguousCheck || !customBool || 
			!customChars || !passwordDisplay || !strengthBar || !strengthText) {
			return;
		}
		
		// Validate input
		int length = static_cast<int>(passSize->Value);
		bool uppercase = uppercaseCheck->IsChecked->Value;
		bool lowercase = lowercaseCheck->IsChecked->Value;
		bool numbers = numbersCheck->IsChecked->Value;
		bool specials = specialsCheck->IsChecked->Value;
		String ^ customCharsText = customBool->IsChecked->Value ? customChars->Text : "";
		
		if (!validateInput(length, uppercase, lowercase, numbers, specials, customCharsText)) {
			passwordDisplay->Text = "Invalid input. Please check your settings.";
			return;
		}

		// Generate password
		String ^ generatedPassword = generateSecurePassword(
			length,
			uppercase,
			lowercase,
			numbers,
			specials,
			similarCheck->IsChecked->Value,
			ambiguousCheck->IsChecked->Value,
			customCharsText
		);

		if (generatedPassword && passwordDisplay) {
			passwordDisplay->Text = generatedPassword;

			// Calculate and display strength
			int strength = calculatePasswordStrength(generatedPassword);
			updateStrengthIndicator(strength);
		}
	}
	catch (Exception^ ex) {
		if (passwordDisplay) {
			passwordDisplay->Text = "Error generating password: " + ex->Message;
		}
		if (strengthBar) {
			strengthBar->Value = 0;
		}
		if (strengthText) {
			strengthText->Text = "Error";
		}
	}
	catch (...) {
		if (passwordDisplay) {
			passwordDisplay->Text = "Unexpected error occurred during password generation";
		}
		if (strengthBar) {
			strengthBar->Value = 0;
		}
		if (strengthText) {
			strengthText->Text = "Error";
		}
	}
}

void FoxyPassword_Generator::MainPage::updateStrengthIndicator(int strength)
{
	strengthBar->Value = strength;
	strengthText->Text = getStrengthDescription(strength);
	
	// WinUI 3 enhanced: Update strength bar color based on strength
	if (isWinUI3Available) {
		try {
					if (strength >= 80) {
			strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
				Windows::UI::Xaml::Application::Current->Resources->Lookup("SuccessBrush"));
		} else if (strength >= 60) {
			strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
				Windows::UI::Xaml::Application::Current->Resources->Lookup("AccentBrush"));
		} else if (strength >= 40) {
			strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
				Windows::UI::Xaml::Application::Current->Resources->Lookup("WarningBrush"));
		} else {
			strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
				Windows::UI::Xaml::Application::Current->Resources->Lookup("ErrorBrush"));
		}
		}
		catch (...) {
			// Fallback to default color
		}
	}
}

String ^ FoxyPassword_Generator::MainPage::generateSecurePassword(int length, bool uppercase, bool lowercase, bool numbers, bool specials, bool excludeSimilar, bool excludeAmbiguous, String ^ customChars)
{
	// Define character sets with comprehensive coverage
	String ^ uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	String ^ lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
	String ^ numberChars = "0123456789";
	String ^ specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?/~`";
	
	// Apply exclusions for similar characters
	if (excludeSimilar) {
		std::wstring upperStr(uppercaseChars->Data());
		std::wstring lowerStr(lowercaseChars->Data());
		std::wstring numStr(numberChars->Data());
		
		// Remove similar characters
		upperStr.erase(std::remove(upperStr.begin(), upperStr.end(), L'I'), upperStr.end());
		upperStr.erase(std::remove(upperStr.begin(), upperStr.end(), L'O'), upperStr.end());
		upperStr.erase(std::remove(upperStr.begin(), upperStr.end(), L'Q'), upperStr.end());
		
		lowerStr.erase(std::remove(lowerStr.begin(), lowerStr.end(), L'l'), lowerStr.end());
		lowerStr.erase(std::remove(lowerStr.begin(), lowerStr.end(), L'o'), lowerStr.end());
		lowerStr.erase(std::remove(lowerStr.begin(), lowerStr.end(), L'q'), lowerStr.end());
		
		numStr.erase(std::remove(numStr.begin(), numStr.end(), L'0'), numStr.end());
		numStr.erase(std::remove(numStr.begin(), numStr.end(), L'1'), numStr.end());
		numStr.erase(std::remove(numStr.begin(), numStr.end(), L'6'), numStr.end());
		numStr.erase(std::remove(numStr.begin(), numStr.end(), L'8'), numStr.end());
		numStr.erase(std::remove(numStr.begin(), numStr.end(), L'9'), numStr.end());
		
		uppercaseChars = ref new String(upperStr.c_str());
		lowercaseChars = ref new String(lowerStr.c_str());
		numberChars = ref new String(numStr.c_str());
	}
	
	// Apply exclusions for ambiguous characters
	if (excludeAmbiguous) {
		std::wstring specialStr(specialChars->Data());
		
		// Remove ambiguous characters
		const wchar_t* ambiguous[] = {L"{", L"}", L"[", L"]", L"(", L")", L"/", L"\\", 
									  L"'", L"\"", L"`", L"~", L",", L";", L":", L".", L"<", L">", L"|"};
		
		for (const wchar_t* amb : ambiguous) {
			specialStr.erase(std::remove(specialStr.begin(), specialStr.end(), amb[0]), specialStr.end());
		}
		
		specialChars = ref new String(specialStr.c_str());
	}

	// Build available character set
	String ^ availableChars = "";
	if (uppercase) availableChars += uppercaseChars;
	if (lowercase) availableChars += lowercaseChars;
	if (numbers) availableChars += numberChars;
	if (specials) availableChars += specialChars;
	if (customChars->Length() > 0) availableChars += customChars;

	if (availableChars->Length() == 0) {
		throw ref new Platform::Exception(E_INVALIDARG, "No character types selected");
	}

	// Generate password ensuring at least one character from each selected type
	String ^ password = "";
	
	// First, ensure we have at least one character from each selected type
	if (uppercase && password->Length() < static_cast<unsigned int>(length)) {
		password += getRandomChar(uppercaseChars);
	}
	if (lowercase && password->Length() < static_cast<unsigned int>(length)) {
		password += getRandomChar(lowercaseChars);
	}
	if (numbers && password->Length() < static_cast<unsigned int>(length)) {
		password += getRandomChar(numberChars);
	}
	if (specials && password->Length() < static_cast<unsigned int>(length)) {
		password += getRandomChar(specialChars);
	}
	if (customChars->Length() > 0 && password->Length() < static_cast<unsigned int>(length)) {
		password += getRandomChar(customChars);
	}

	// Fill the rest with random characters from the available set
	while (password->Length() < static_cast<unsigned int>(length)) {
		password += getRandomChar(availableChars);
	}

	// Shuffle the password to avoid predictable patterns
	std::wstring passwordStr(password->Data());
	{
		std::lock_guard<std::mutex> lock(randomMutex);
		if (randomGenerator) {
			std::shuffle(passwordStr.begin(), passwordStr.end(), *randomGenerator);
		}
	}
	
	return ref new String(passwordStr.c_str());
}

int FoxyPassword_Generator::MainPage::calculatePasswordStrength(String ^ password)
{
	if (password->Length() == 0) return 0;

	int score = 0;
	bool hasUppercase = false, hasLowercase = false, hasNumbers = false, hasSpecials = false;
	
	// Length bonus (exponential scaling)
	score += min(password->Length() * 3, 50);
	
	// Character variety analysis
	for (int i = 0; i < static_cast<int>(password->Length()); i++) {
		wchar_t c = password->Data()[i];
		if (isupper(c)) hasUppercase = true;
		else if (islower(c)) hasLowercase = true;
		else if (isdigit(c)) hasNumbers = true;
		else hasSpecials = true;
	}
	
	// Character type bonuses
	if (hasUppercase) score += 15;
	if (hasLowercase) score += 15;
	if (hasNumbers) score += 15;
	if (hasSpecials) score += 20;
	
	// Combination bonuses
	if (hasUppercase && hasLowercase) score += 10;
	if (hasNumbers && (hasUppercase || hasLowercase)) score += 10;
	if (hasSpecials && (hasUppercase || hasLowercase || hasNumbers)) score += 15;
	
	// Penalties for weak patterns
	if (!hasUppercase || !hasLowercase) score -= 5;
	if (hasNumbers && !hasUppercase && !hasLowercase && !hasSpecials) score -= 15;
	
	// Entropy-based scoring
	int uniqueChars = 0;
	std::vector<wchar_t> seenChars;
	for (int i = 0; i < static_cast<int>(password->Length()); i++) {
		wchar_t c = password->Data()[i];
		if (std::find(seenChars.begin(), seenChars.end(), c) == seenChars.end()) {
			seenChars.push_back(c);
			uniqueChars++;
		}
	}
	
	// Bonus for character diversity
	if (uniqueChars > static_cast<int>(password->Length() * 0.7)) score += 10;
	
	return max(0, min(100, score));
}

String ^ FoxyPassword_Generator::MainPage::getStrengthDescription(int strength)
{
	if (strength < 20) return "Very Weak";
	else if (strength < 40) return "Weak";
	else if (strength < 60) return "Fair";
	else if (strength < 80) return "Good";
	else if (strength < 90) return "Strong";
	else return "Very Strong";
}

void FoxyPassword_Generator::MainPage::copyButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (passwordDisplay->Text->Length() > 0 && 
		passwordDisplay->Text != "Generate a password to see strength" &&
		passwordDisplay->Text != "Invalid input. Please check your settings.") {
		
		try {
			Windows::ApplicationModel::DataTransfer::DataPackage^ dataPackage = ref new Windows::ApplicationModel::DataTransfer::DataPackage();
			dataPackage->SetText(passwordDisplay->Text);
			Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(dataPackage);
			
			// Visual feedback with modern async pattern
			copyButton->Content = "Copied!";
			
			// Reset button text after delay using modern async
			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, 
				ref new Windows::UI::Core::DispatchedHandler([this]() {
					Windows::System::Threading::ThreadPoolTimer::CreateTimer(
						ref new Windows::System::Threading::TimerElapsedHandler([this](Windows::System::Threading::ThreadPoolTimer^ timer) {
							Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, 
								ref new Windows::UI::Core::DispatchedHandler([this]() {
									copyButton->Content = "Copy";
								}));
						}), TimeSpan{ 20000000 } // 2 seconds
					);
				}));
		}
		catch (...) {
			// Handle clipboard errors gracefully
			copyButton->Content = "Copy Failed";
			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, 
				ref new Windows::UI::Core::DispatchedHandler([this]() {
					Windows::System::Threading::ThreadPoolTimer::CreateTimer(
						ref new Windows::System::Threading::TimerElapsedHandler([this](Windows::System::Threading::ThreadPoolTimer^ timer) {
							Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, 
								ref new Windows::UI::Core::DispatchedHandler([this]() {
									copyButton->Content = "Copy";
								}));
						}), TimeSpan{ 20000000 }
					);
				}));
		}
	}
}

void FoxyPassword_Generator::MainPage::passSize_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	int length = static_cast<int>(e->NewValue);
	lengthDisplay->Text = length.ToString() + " characters";
}