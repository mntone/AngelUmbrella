#pragma once
#include "Converters/InvertedBooleanConverter.g.h"

namespace winrt::Mntone::AngelUmbrella::Converters::implementation {

	struct InvertedBooleanConverter: InvertedBooleanConverterT<InvertedBooleanConverter> {
		InvertedBooleanConverter() noexcept;

		Windows::Foundation::IInspectable Convert(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language) const;
		Windows::Foundation::IInspectable ConvertBack(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language) const;
	};

}

namespace winrt::Mntone::AngelUmbrella::Converters::factory_implementation {

	struct InvertedBooleanConverter: InvertedBooleanConverterT<InvertedBooleanConverter, implementation::InvertedBooleanConverter> {
	};

}
