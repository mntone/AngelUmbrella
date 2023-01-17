#pragma once
#include "Controls/OddEvenStyleSelector.g.h"

namespace winrt::Mntone::AngelUmbrella::Controls::implementation {

	struct OddEvenStyleSelector: OddEvenStyleSelectorT<OddEvenStyleSelector> {
		OddEvenStyleSelector() noexcept;

		Microsoft::UI::Xaml::Style SelectStyleCore(
			Windows::Foundation::IInspectable const& item,
			Microsoft::UI::Xaml::DependencyObject const& container) const;

		inline Microsoft::UI::Xaml::Style OddStyle() const noexcept {
			return oddStyle_;
		}
		inline void OddStyle(Microsoft::UI::Xaml::Style const& value) noexcept {
			oddStyle_ = value;
		}

		inline Microsoft::UI::Xaml::Style EvenStyle() const noexcept {
			return evenStyle_;
		}
		inline void EvenStyle(Microsoft::UI::Xaml::Style const& value) noexcept {
			evenStyle_ = value;
		}

	private:
		Microsoft::UI::Xaml::Style oddStyle_, evenStyle_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Controls::factory_implementation {

	struct OddEvenStyleSelector: OddEvenStyleSelectorT<OddEvenStyleSelector, implementation::OddEvenStyleSelector> {
	};

}
