#include "pch.h"
#include "SettingsWindow_DetailPage.xaml.h"
#if __has_include("SettingsWindow_DetailPage.g.cpp")
#include "SettingsWindow_DetailPage.g.cpp"
#endif

#include "DesktopAcrylicWindow.xaml.h"

namespace winrt {
	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

SettingsWindow_DetailPage::SettingsWindow_DetailPage() {
	InitializeComponent();
}

void SettingsWindow_DetailPage::OnDesktopAcrylicWindowOpening(IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/) const {
	auto window { make<implementation::DesktopAcrylicWindow>() };
	window.Activate();
}
