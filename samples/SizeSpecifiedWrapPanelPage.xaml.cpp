#include "pch.h"
#include "SizeSpecifiedWrapPanelPage.xaml.h"
#if __has_include("SizeSpecifiedWrapPanelPage.g.cpp")
#include "SizeSpecifiedWrapPanelPage.g.cpp"
#endif

#include "ViewModels\ColorDataViewModel.h"

namespace winrt {
	using namespace ::winrt::Windows::UI;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

// Use this in WrapPanelPage.
extern void AppendChildren(winrt::UIElementCollection const& collection);

SizeSpecifiedWrapPanelPage::SizeSpecifiedWrapPanelPage() {
	InitializeComponent();

	AppendChildren(DefaultWrapPanel().Children());
}
