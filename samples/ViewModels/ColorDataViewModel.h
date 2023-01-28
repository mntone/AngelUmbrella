#pragma once
#include "ViewModels\ColorDataViewModel.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::ViewModels::implementation {

	struct ColorDataViewModel: ColorDataViewModelT<ColorDataViewModel> {
		ColorDataViewModel(param::hstring const& name, Windows::UI::Color const& color) noexcept;

		inline hstring Name() const noexcept { return name_; }
		inline constexpr Windows::UI::Color Color() const noexcept { return color_; }
		inline constexpr int Luminance() const noexcept {
			return (299 * color_.R + 587 * color_.G + 114 * color_.B) / 2550;
		}
		inline constexpr bool PreferredDarkForeground() const noexcept {
			return Luminance() > 50;
		}

		static std::vector<::winrt::Mntone::AngelUmbrella::Samples::ViewModels::ColorDataViewModel> Assets();

	private:
		hstring name_;
		Windows::UI::Color color_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::ViewModels::factory_implementation {

	struct ColorDataViewModel: ColorDataViewModelT<ColorDataViewModel, implementation::ColorDataViewModel> {
	};

}
