//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

#include "App.g.h"

namespace FoxyPassword_Generator
{
	/// <summary>
	/// Provides application-specific behavior to supplement the default Application class.
	/// </summary>
	ref class App sealed
	{
	protected:
		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

	internal:
		App();

	private:
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		void OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e);
		void OnResuming(Platform::Object^ sender, Platform::Object^ e);
		void OnEnteredBackground(Platform::Object^ sender, Windows::ApplicationModel::EnteredBackgroundEventArgs^ e);
		void OnLeavingBackground(Platform::Object^ sender, Windows::ApplicationModel::LeavingBackgroundEventArgs^ e);
		void OnUnhandledException(Platform::Object^ sender, Windows::UI::Xaml::UnhandledExceptionEventArgs^ e);
		void InitializeSecuritySettings();
		void RestoreApplicationState();
		void ClearSensitiveData();
		void StopBackgroundTasks();
		void PauseOperations();
		void ResumeOperations();
		void SaveApplicationState();
	};
}
