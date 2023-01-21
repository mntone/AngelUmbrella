#pragma once
#include "App.xaml.g.h"
#include <winrt/Mntone.AngelUmbrella.Converters.h>
#include <winrt/Mntone.AngelUmbrella.Navigation.h>

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct App: AppT<App> {
		App();

		void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

	private:
		Microsoft::UI::Xaml::Window window { nullptr };
	};

}
