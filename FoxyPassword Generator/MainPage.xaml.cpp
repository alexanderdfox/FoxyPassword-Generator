//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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
using namespace std;

MainPage::MainPage()
{
	InitializeComponent();
	numberGen();
}

void FoxyPassword_Generator::MainPage::generate_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	String ^ actPass = passWord(int(passSize->Value),specialsCheck->IsChecked->Value,vowelsCheck->IsChecked->Value,constanantsCheck->IsChecked->Value,numbersCheck->IsChecked->Value,
		customBool->IsChecked->Value, customChars->Text, upperButton->IsChecked->Value,lowerButton->IsChecked->Value);
	password->Text = actPass;
}

wchar_t FoxyPassword_Generator::MainPage::getChar(bool specialChars, bool vowelChars, bool constChars, bool numChars, bool customBool, String ^ customChars) {

	String ^ numbers = "0123456789";
	String ^ constanants = "bcdfghjklmnpqrstvwxyz";
	String ^ vowels = "aeiouy";
	String ^ specials = "!#$&*-_.";
	String ^ all = specials + vowels + constanants + numbers;
	String ^ allC = specials + vowels + constanants + numbers + customChars;
	String ^ nC = numbers + customChars;
	String ^ cC = constanants + customChars;
	String ^ vC = vowels + customChars;
	String ^ sC = specials + customChars;
	String ^ ncv = numbers + constanants + vowels;
	String ^ cns = constanants + numbers + specials;
	String ^ vns = vowels + numbers + specials;
	String ^ vcs = vowels + constanants + specials;
	String ^ vc = vowels + constanants;
	String ^ vs = vowels + specials;
	String ^ nc = numbers + constanants;
	String ^ ns = numbers + specials;
	String ^ cs = constanants + specials;
	String ^ vn = vowels + numbers;
	String ^ ncvC = numbers + constanants + vowels + customChars;
	String ^ cnsC = constanants + numbers + specials + customChars;
	String ^ vnsC = vowels + numbers + specials + customChars;
	String ^ vcsC = vowels + constanants + specials + customChars;
	String ^ vcC = vowels + constanants + customChars;
	String ^ vsC = vowels + specials + customChars;
	String ^ ncC = numbers + constanants + customChars;
	String ^ nsC = numbers + specials + customChars;
	String ^ csC = constanants + specials + customChars;
	String ^ vnC = vowels + numbers + customChars;
	int n = rand() % numbers->Length();
	int v = rand() % vowels->Length();
	int c = rand() % constanants->Length();
	int s = rand() % specials->Length();
	int Cn = rand() % nC->Length();
	int Cv = rand() % vC->Length();
	int Cc = rand() % cC->Length();
	int Cs = rand() % sC->Length();
	int a = rand() % all->Length();
	int aC = rand() % allC->Length();
	int C = customChars->Length();
	if (C > 0) {
		C = rand() % customChars->Length();
	}
	else if (C == 0 && customBool == true) {
		customBool = false;
	}
	int NCV = rand() % ncv->Length();
	int CNS = rand() % cns->Length();
	int VNS = rand() % vns->Length();
	int VCS = rand() % vcs->Length();
	int VC = rand() % vc->Length();
	int VS = rand() % vs->Length();
	int NC = rand() % nc->Length();
	int NS = rand() % ns->Length();
	int CS = rand() % cs->Length();
	int VN = rand() % vn->Length();
	int NCVc = rand() % ncvC->Length();
	int CNSc = rand() % cnsC->Length();
	int VNSc = rand() % vnsC->Length();
	int VCSc = rand() % vcsC->Length();
	int VCc = rand() % vcC->Length();
	int VSc = rand() % vsC->Length();
	int NCc = rand() % ncC->Length();
	int NSc = rand() % nsC->Length();
	int CSc = rand() % csC->Length();
	int VNc = rand() % vnC->Length();
	wchar_t theChar;

	if (specialChars && vowelChars && constChars && numChars && customBool) {
		auto it = allC->Begin();
		theChar = it[aC];
	}
	else if (!specialChars && !vowelChars && !constChars && !numChars && customBool) {
		auto it = customChars->Begin();
		theChar = it[C];
	}
	else if (!specialChars && !vowelChars && !constChars && numChars && customBool) {
		auto it = nC->Begin();
		theChar = it[Cn];
	}
	else if (!specialChars && !vowelChars && constChars && !numChars && customBool) {
		auto it = cC->Begin();
		theChar = it[Cc];
	}
	else if (!specialChars && vowelChars && !constChars && !numChars && customBool) {
		auto it = vC->Begin();
		theChar = it[Cv];
	}
	else if (specialChars && !vowelChars && !constChars && !numChars && customBool) {
		auto it = sC->Begin();
		theChar = it[Cs];
	}
	else if (!specialChars && vowelChars && constChars && numChars && customBool) {
		auto it = ncvC->Begin();
		theChar = it[NCVc];
	}
	else if (specialChars && !vowelChars && constChars && numChars && customBool) {
		auto it = cnsC->Begin();
		theChar = it[CNSc];
	}
	else if (specialChars && vowelChars && !constChars && numChars && customBool) {
		auto it = vnsC->Begin();
		theChar = it[VNSc];
	}
	else if (specialChars && vowelChars && constChars && !numChars && customBool) {
		auto it = vcsC->Begin();
		theChar = it[VCSc];
	}
	else if (!specialChars && vowelChars && constChars && !numChars && customBool) {
		auto it = vcC->Begin();
		theChar = it[VCc];
	}
	else if (!specialChars && !vowelChars && constChars && numChars && customBool) {
		auto it = ncC->Begin();
		theChar = it[NCc];
	}
	else if (!specialChars && vowelChars && !constChars && numChars && customBool) {
		auto it = vnC->Begin();
		theChar = it[VNc];
	}
	else if (specialChars && !vowelChars && !constChars && numChars && customBool) {
		auto it = nsC->Begin();
		theChar = it[NSc];
	}
	else if (specialChars && vowelChars && !constChars && !numChars && customBool) {
		auto it = vsC->Begin();
		theChar = it[VSc];
	}
	else if (specialChars && !vowelChars && constChars && !numChars && customBool) {
		auto it = csC->Begin();
		theChar = it[CSc];
	}
	else if (specialChars && vowelChars && constChars && numChars && !customBool) {
		auto it = all->Begin();
		theChar = it[a];
	}
	else if (!specialChars && !vowelChars && !constChars && numChars && !customBool) {
		auto it = numbers->Begin();
		theChar = it[n];
	}
	else if (!specialChars && !vowelChars && constChars && !numChars && !customBool) {
		auto it = constanants->Begin();
		theChar = it[c];
	}
	else if (!specialChars && vowelChars && !constChars && !numChars && !customBool) {
		auto it = vowels->Begin();
		theChar = it[v];
	}
	else if (specialChars && !vowelChars && !constChars && !numChars && !customBool) {
		auto it = specials->Begin();
		theChar = it[s];
	}
	else if (!specialChars && vowelChars && constChars && numChars && !customBool) {
		auto it = ncv->Begin();
		theChar = it[NCV];
	}
	else if (specialChars && !vowelChars && constChars && numChars && !customBool) {
		auto it = cns->Begin();
		theChar = it[CNS];
	}
	else if (specialChars && vowelChars && !constChars && numChars && !customBool) {
		auto it = vns->Begin();
		theChar = it[VNS];
	}
	else if (specialChars && vowelChars && constChars && !numChars && !customBool) {
		auto it = vcs->Begin();
		theChar = it[VCS];
	}
	else if (!specialChars && vowelChars && constChars && !numChars && !customBool) {
		auto it = vc->Begin();
		theChar = it[VC];
	}
	else if (!specialChars && !vowelChars && constChars && numChars && !customBool) {
		auto it = nc->Begin();
		theChar = it[NC];
	}
	else if (!specialChars && vowelChars && !constChars && numChars && !customBool) {
		auto it = vn->Begin();
		theChar = it[VN];
	}
	else if (specialChars && !vowelChars && !constChars && numChars && !customBool) {
		auto it = ns->Begin();
		theChar = it[NS];
	}
	else if (specialChars && vowelChars && !constChars && !numChars && !customBool) {
		auto it = vs->Begin();
		theChar = it[VS];
	}
	else if (specialChars && !vowelChars && constChars && !numChars && !customBool) {
		auto it = cs->Begin();
		theChar = it[CS];
	}

	return theChar;
}

String ^ FoxyPassword_Generator::MainPage::passWord(int length, bool specialChars, bool vowelChars, bool constChars, bool numChars, bool customBool, String ^ customChars, bool upperOnly, bool lowerOnly) {
	String ^ pass;
	int r = rand() % 5;

	for (int i = 1; i <= length; i++) {

		int r = rand() % 5;

		if ((upperOnly && lowerOnly) || (!upperOnly && !lowerOnly)) {
			if (r % 2 == 1) {
				wchar_t theChar = tolower(getChar(specialChars, vowelChars, constChars, numChars, customBool, customChars));
				pass += theChar.ToString();
			}
			else {
				wchar_t theChar = toupper(getChar(specialChars, vowelChars, constChars, numChars, customBool, customChars));
				pass += theChar.ToString();
			}
		}
		else if (upperOnly && !lowerOnly) {
			wchar_t theChar = toupper(getChar(specialChars, vowelChars, constChars, numChars, customBool, customChars));
			pass += theChar.ToString();
		}
		else if (!upperOnly && lowerOnly) {
			wchar_t theChar = tolower(getChar(specialChars, vowelChars, constChars, numChars, customBool, customChars));
			pass += theChar.ToString();
		}
		else {
			pass = "";
		}

	}

	if (pass == "") {
		pass = "ERROR!";
	}

	return pass;
}

int FoxyPassword_Generator::MainPage::numberGen()
{
	srand(int(time(0)));
	int myRand = rand() % int(time(0));
	srand(myRand);
	return myRand;
}