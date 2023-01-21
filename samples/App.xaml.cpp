#include "pch.h"
#include "App.xaml.h"

#include "SettingsWindow.xaml.h"

namespace winrt {
	using namespace ::winrt::Windows::Foundation;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Navigation;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

App::App() {
	// Require vvv HERE vvv to use NavigationProperties.
	Navigation::NavigationProperties::Initialize();

	InitializeComponent();

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
	UnhandledException([this](IInspectable const&, UnhandledExceptionEventArgs const& e) {
		if (IsDebuggerPresent()) {
			auto errorMessage = e.Message();
			__debugbreak();
		}
	});
#endif
}

void App::OnLaunched(LaunchActivatedEventArgs const&) {
	window = make<SettingsWindow>();
	window.Activate();
}
