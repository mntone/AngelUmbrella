#include "pch.h"
#include "OddEvenStyleSelector.h"
#if __has_include("Controls/OddEvenStyleSelector.g.cpp")
#include "Controls/OddEvenStyleSelector.g.cpp"
#endif

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::UI::Xaml::Interop;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

OddEvenStyleSelector::OddEvenStyleSelector() noexcept
	: oddStyle_(nullptr)
	, evenStyle_(nullptr) {
}

winrt::Microsoft::UI::Xaml::Style OddEvenStyleSelector::SelectStyleCore(IInspectable const& /*item*/, DependencyObject const& container) const {
	ItemsControl itemsControl { ItemsControl::ItemsControlFromItemContainer(container) };
	int index { itemsControl.IndexFromContainer(container) };
	if (index % 2) {
		return oddStyle_;
	} else {
		return evenStyle_;
	}
}
