//
// MainPage.xaml.h
// Declaration of the MainPage class with WinUI 3 support.
//

#pragma once

#include "MainPage.g.h"
#include <random>
#include <memory>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>

using namespace Platform;
using namespace winrt::Windows::ApplicationModel::DataTransfer;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;

namespace FoxyPassword_Generator
{
	/// <summary>
	/// A secure password generator page with WinUI 3, professional UI and cryptography-grade random generation.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		// UI Event Handlers
		void generate_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void copyButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void passSize_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		
		// Password Generation Methods
		String ^ generateSecurePassword(int length, bool uppercase, bool lowercase, bool numbers, bool specials, bool excludeSimilar, bool excludeAmbiguous, String ^ customChars);
		wchar_t getRandomChar(String ^ charSet);
		int calculatePasswordStrength(String ^ password);
		String ^ getStrengthDescription(int strength);
		
		// Security Methods
		void initializeSecureRandom();
		int getSecureRandomNumber(int min, int max);
		
		// WinUI 3 Specific Methods
		void updateUIForWinUI3();
		void applyWinUI3Styling();
		
		// Member Variables
		std::unique_ptr<std::random_device> randomDevice;
		std::unique_ptr<std::mt19937> randomGenerator;
		
		// WinUI 3 Enhanced Security
		bool isWinUI3Available;
	};
}
