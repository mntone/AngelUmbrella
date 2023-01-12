#pragma once
#include "Converters/BooleanToVisibilityConverter.g.h"

namespace winrt::Mntone::AngelUmbrella::Converters::implementation {

	struct BooleanToVisibilityConverter: BooleanToVisibilityConverterT<BooleanToVisibilityConverter> {
		BooleanToVisibilityConverter() noexcept;

		Windows::Foundation::IInspectable Convert(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language) const;
		Windows::Foundation::IInspectable ConvertBack(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language) const;
	};

}

namespace winrt::Mntone::AngelUmbrella::Converters::factory_implementation {

	struct BooleanToVisibilityConverter: BooleanToVisibilityConverterT<BooleanToVisibilityConverter, implementation::BooleanToVisibilityConverter> {
	};

}
