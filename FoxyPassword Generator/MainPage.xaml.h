//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

using namespace Platform;

namespace FoxyPassword_Generator
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void generate_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		wchar_t getChar(bool specialChars, bool vowelChars, bool constChars, bool numChars, bool customBool, String ^ customChars);
		String ^ passWord(int length, bool specialChars, bool vowelChars, bool constChars, bool numChars, bool customBool, String ^ customChars, bool upperOnly, bool lowerOnly);
		int numberGen();
	};
}
