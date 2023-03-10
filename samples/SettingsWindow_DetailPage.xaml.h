#pragma once
#include "SettingsWindow_DetailPage.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct SettingsWindow_DetailPage: SettingsWindow_DetailPageT<SettingsWindow_DetailPage> {
		SettingsWindow_DetailPage();

		void OnDesktopAcrylicWindowOpening(
			Windows::Foundation::IInspectable const& sender,
			Microsoft::UI::Xaml::RoutedEventArgs const& args) const;
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {

	struct SettingsWindow_DetailPage: SettingsWindow_DetailPageT<SettingsWindow_DetailPage, implementation::SettingsWindow_DetailPage> {
	};

}
