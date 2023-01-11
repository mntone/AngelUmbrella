#pragma once
#include "SettingsWindow_RootPage.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct SettingsWindow_RootPage: SettingsWindow_RootPageT<SettingsWindow_RootPage> {
		SettingsWindow_RootPage();

		void ListViewItemClick(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& args);
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {

	struct SettingsWindow_RootPage: SettingsWindow_RootPageT<SettingsWindow_RootPage, implementation::SettingsWindow_RootPage> {
	};

}
