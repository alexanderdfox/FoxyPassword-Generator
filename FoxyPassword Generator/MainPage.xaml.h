//
// MainPage.xaml.h
// Declaration of the MainPage class with WinUI 3 support and enhanced security.
//

#pragma once

#include "MainPage.g.h"
#include <random>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <atomic>
#include <mutex>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Foundation.h>

using namespace Platform;
using namespace winrt::Windows::ApplicationModel::DataTransfer;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Storage::Streams;

namespace FoxyPassword_Generator
{
	/// <summary>
	/// A secure password generator page with WinUI 3, professional UI and cryptography-grade random generation.
	/// Enhanced with modern C++17 features, thread safety, and comprehensive security measures.
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
		
		// Enhanced Security Methods
		void initializeSecureRandom();
		int getSecureRandomNumber(int min, int max);
		void reseedRandomGenerator();
		bool validateInput(int length, bool uppercase, bool lowercase, bool numbers, bool specials, String ^ customChars);
		
		// WinUI 3 Specific Methods
		void updateUIForWinUI3();
		void applyWinUI3Styling();
		void updateStrengthIndicator(int strength);
		
		// Modern C++ Security Members
		std::unique_ptr<std::random_device> randomDevice;
		std::unique_ptr<std::mt19937> randomGenerator;
		std::mutex randomMutex;
		std::atomic<bool> isInitialized{ false };
		std::chrono::steady_clock::time_point lastReseed;
		
		// WinUI 3 Enhanced Security
		bool isWinUI3Available;
		
		// Constants for security
		static constexpr int MIN_PASSWORD_LENGTH = 8;
		static constexpr int MAX_PASSWORD_LENGTH = 128;
		static constexpr int RESEED_INTERVAL_SECONDS = 300; // 5 minutes
		static constexpr int ENTROPY_BYTES = 64;
	};
}