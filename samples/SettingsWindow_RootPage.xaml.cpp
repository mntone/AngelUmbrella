#include "pch.h"
#include "SettingsWindow_RootPage.xaml.h"
#if __has_include("SettingsWindow_RootPage.g.cpp")
#include "SettingsWindow_RootPage.g.cpp"
#endif

#include "SettingsWindow_DetailPage.g.h"

namespace winrt {
	using namespace ::winrt::Windows::Foundation;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Media::Animation;

	using namespace ::winrt::Mntone::AngelUmbrella::Samples;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

SettingsWindow_RootPage::SettingsWindow_RootPage() {
	InitializeComponent();

	ItemCollection itemCollection { listView().Items() };
	for (int i = 0; i < 100; ++i) {
		itemCollection.Append(box_value(i));
	}
}

void SettingsWindow_RootPage::ListViewItemClick(IInspectable const& /*sender*/, ItemClickEventArgs const& /*args*/) {
	winrt::Frame frame { Frame() };
	if (frame) {
		SlideNavigationTransitionInfo info;
		info.Effect(SlideNavigationTransitionEffect::FromRight);
		frame.Navigate(xaml_typename<winrt::SettingsWindow_DetailPage>(), nullptr, info);
	}
}
