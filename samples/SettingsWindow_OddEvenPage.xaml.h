#pragma once
#include "SettingsWindow_OddEvenPage.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct SettingsWindow_OddEvenPage: SettingsWindow_OddEvenPageT<SettingsWindow_OddEvenPage> {
		SettingsWindow_OddEvenPage();

		void ListViewItemClick(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& args);
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {

	struct SettingsWindow_OddEvenPage: SettingsWindow_OddEvenPageT<SettingsWindow_OddEvenPage, implementation::SettingsWindow_OddEvenPage> {
	};

}
