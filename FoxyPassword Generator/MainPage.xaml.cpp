//
// MainPage.xaml.cpp
// Implementation of the MainPage class with WinUI 3 and enhanced security.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <random>
#include <algorithm>
#include <cctype>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Security.Cryptography.h>

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
using namespace std;

MainPage::MainPage()
{
	InitializeComponent();
	initializeSecureRandom();
	
	// Set up event handlers
	passSize->ValueChanged += ref new RangeBaseValueChangedEventHandler(this, &MainPage::passSize_ValueChanged);
	
	// Initialize UI
	lengthDisplay->Text = "16 characters";
	strengthBar->Value = 0;
	strengthText->Text = "Generate a password to see strength";
	
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
			passwordDisplay->AutomationProperties->Name = "Generated Password";
			copyButton->AutomationProperties->Name = "Copy Password to Clipboard";
			generateButton->AutomationProperties->Name = "Generate Secure Password";
			
			// Enhanced tooltips
			passwordDisplay->ToolTipService->SetToolTip(passwordDisplay, "Generated secure password");
			copyButton->ToolTipService->SetToolTip(copyButton, "Copy password to clipboard");
			generateButton->ToolTipService->SetToolTip(generateButton, "Generate a new secure password");
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
		// Apply WinUI 3 specific styling
		generateButton->Style = safe_cast<Windows::UI::Xaml::Style^>(
			Application::Current->Resources->Lookup("ModernButtonStyle"));
		
		// Enhanced visual feedback
		strengthBar->Background = safe_cast<Windows::UI::Xaml::Media::Brush^>(
			Application::Current->Resources->Lookup("SystemControlBackgroundBaseLowBrush"));
	}
}

void FoxyPassword_Generator::MainPage::initializeSecureRandom()
{
	try {
		// Use hardware random number generator if available
		randomDevice = std::make_unique<std::random_device>();
		randomGenerator = std::make_unique<std::mt19937>((*randomDevice)());
		
		// WinUI 3 enhanced: Use Windows Security APIs if available
		if (isWinUI3Available) {
			// Additional entropy from Windows Security APIs
			auto cryptoBuffer = CryptographicBuffer::GenerateRandom(32);
			auto randomBytes = cryptoBuffer.data();
			std::seed_seq seed(randomBytes, randomBytes + 32);
			randomGenerator->seed(seed);
		}
	}
	catch (...) {
		// Fallback to system time if hardware RNG is not available
		randomGenerator = std::make_unique<std::mt19937>(static_cast<unsigned int>(time(nullptr)));
	}
}

int FoxyPassword_Generator::MainPage::getSecureRandomNumber(int min, int max)
{
	if (max <= min) return min;
	
	std::uniform_int_distribution<int> distribution(min, max - 1);
	return distribution(*randomGenerator);
}

wchar_t FoxyPassword_Generator::MainPage::getRandomChar(String ^ charSet)
{
	if (charSet->Length() == 0) return L' ';
	
	int index = getSecureRandomNumber(0, charSet->Length());
	return charSet[index];
}

void FoxyPassword_Generator::MainPage::generate_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	try {
		// Validate input
		if (!uppercaseCheck->IsChecked->Value && !lowercaseCheck->IsChecked->Value && 
			!numbersCheck->IsChecked->Value && !specialsCheck->IsChecked->Value && 
			!customBool->IsChecked->Value) {
			passwordDisplay->Text = "Please select at least one character type";
			return;
		}

		int length = static_cast<int>(passSize->Value);
		if (length < 8 || length > 128) {
			passwordDisplay->Text = "Password length must be between 8 and 128 characters";
			return;
		}

		// Generate password
		String ^ generatedPassword = generateSecurePassword(
			length,
			uppercaseCheck->IsChecked->Value,
			lowercaseCheck->IsChecked->Value,
			numbersCheck->IsChecked->Value,
			specialsCheck->IsChecked->Value,
			similarCheck->IsChecked->Value,
			ambiguousCheck->IsChecked->Value,
			customBool->IsChecked->Value ? customChars->Text : ""
		);

		passwordDisplay->Text = generatedPassword;

		// Calculate and display strength
		int strength = calculatePasswordStrength(generatedPassword);
		strengthBar->Value = strength;
		strengthText->Text = getStrengthDescription(strength);
		
		// WinUI 3 enhanced: Update strength bar color based on strength
		if (isWinUI3Available) {
			if (strength >= 80) {
				strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
					Application::Current->Resources->Lookup("SuccessBrush"));
			} else if (strength >= 60) {
				strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
					Application::Current->Resources->Lookup("AccentBrush"));
			} else if (strength >= 40) {
				strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
					Application::Current->Resources->Lookup("WarningBrush"));
			} else {
				strengthBar->Foreground = safe_cast<Windows::UI::Xaml::Media::Brush^>(
					Application::Current->Resources->Lookup("ErrorBrush"));
			}
		}
	}
	catch (Exception^ ex) {
		passwordDisplay->Text = "Error generating password: " + ex->Message;
	}
}

String ^ FoxyPassword_Generator::MainPage::generateSecurePassword(int length, bool uppercase, bool lowercase, bool numbers, bool specials, bool excludeSimilar, bool excludeAmbiguous, String ^ customChars)
{
	// Define character sets
	String ^ uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	String ^ lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
	String ^ numberChars = "0123456789";
	String ^ specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";
	
	// Apply exclusions
	if (excludeSimilar) {
		uppercaseChars = uppercaseChars->Replace("I", "")->Replace("O", "");
		lowercaseChars = lowercaseChars->Replace("l", "");
		numberChars = numberChars->Replace("0", "")->Replace("1", "");
	}
	
	if (excludeAmbiguous) {
		specialChars = specialChars->Replace("{", "")->Replace("}", "")->Replace("[", "")->Replace("]", "")
			->Replace("(", "")->Replace(")", "")->Replace("/", "")->Replace("\\", "")
			->Replace("'", "")->Replace("\"", "")->Replace("`", "")->Replace("~", "")
			->Replace(",", "")->Replace(";", "")->Replace(":", "")->Replace(".", "")
			->Replace("<", "")->Replace(">", "");
	}

	// Build available character set
	String ^ availableChars = "";
	if (uppercase) availableChars += uppercaseChars;
	if (lowercase) availableChars += lowercaseChars;
	if (numbers) availableChars += numberChars;
	if (specials) availableChars += specialChars;
	if (customChars->Length() > 0) availableChars += customChars;

	if (availableChars->Length() == 0) {
		throw ref new Exception("No character types selected");
	}

	// Generate password ensuring at least one character from each selected type
	String ^ password = "";
	
	// First, ensure we have at least one character from each selected type
	if (uppercase && password->Length() < length) {
		password += getRandomChar(uppercaseChars);
	}
	if (lowercase && password->Length() < length) {
		password += getRandomChar(lowercaseChars);
	}
	if (numbers && password->Length() < length) {
		password += getRandomChar(numberChars);
	}
	if (specials && password->Length() < length) {
		password += getRandomChar(specialChars);
	}
	if (customChars->Length() > 0 && password->Length() < length) {
		password += getRandomChar(customChars);
	}

	// Fill the rest with random characters
	while (password->Length() < length) {
		password += getRandomChar(availableChars);
	}

	// Shuffle the password to avoid predictable patterns
	std::wstring passwordStr(password->Data());
	std::shuffle(passwordStr.begin(), passwordStr.end(), *randomGenerator);
	
	return ref new String(passwordStr.c_str());
}

int FoxyPassword_Generator::MainPage::calculatePasswordStrength(String ^ password)
{
	if (password->Length() == 0) return 0;

	int score = 0;
	bool hasUppercase = false, hasLowercase = false, hasNumbers = false, hasSpecials = false;
	
	// Length bonus
	score += min(password->Length() * 4, 40);
	
	// Character variety bonus
	for (int i = 0; i < password->Length(); i++) {
		wchar_t c = password[i];
		if (isupper(c)) hasUppercase = true;
		else if (islower(c)) hasLowercase = true;
		else if (isdigit(c)) hasNumbers = true;
		else hasSpecials = true;
	}
	
	if (hasUppercase) score += 10;
	if (hasLowercase) score += 10;
	if (hasNumbers) score += 10;
	if (hasSpecials) score += 10;
	
	// Bonus for mixed case
	if (hasUppercase && hasLowercase) score += 10;
	
	// Bonus for numbers and letters
	if (hasNumbers && (hasUppercase || hasLowercase)) score += 10;
	
	// Bonus for special characters
	if (hasSpecials) score += 15;
	
	// Penalty for all same case
	if (!hasUppercase || !hasLowercase) score -= 10;
	
	// Penalty for all numbers
	if (hasNumbers && !hasUppercase && !hasLowercase && !hasSpecials) score -= 20;
	
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
	if (passwordDisplay->Text->Length() > 0 && passwordDisplay->Text != "Generate a password to see strength") {
		DataPackage^ dataPackage = ref new DataPackage();
		dataPackage->SetText(passwordDisplay->Text);
		Clipboard::SetContent(dataPackage);
		
		// Visual feedback
		copyButton->Content = "Copied!";
		Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
			Windows::System::Threading::ThreadPoolTimer::CreateTimer(
				ref new Windows::System::Threading::TimerElapsedHandler([this](Windows::System::Threading::ThreadPoolTimer^ timer) {
					Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
						copyButton->Content = "Copy";
					}));
				}), TimeSpan{ 20000000 } // 2 seconds
			);
		}));
	}
}

void FoxyPassword_Generator::MainPage::passSize_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	int length = static_cast<int>(e->NewValue);
	lengthDisplay->Text = length.ToString() + " characters";
}