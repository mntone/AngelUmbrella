#pragma once
#include "Converters/SingleToVector3AsZConverter.g.h"

namespace winrt::Mntone::AngelUmbrella::Converters::implementation {

	struct SingleToVector3AsZConverter: SingleToVector3AsZConverterT<SingleToVector3AsZConverter> {
		SingleToVector3AsZConverter() noexcept;

		Windows::Foundation::IInspectable Convert(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language) const;
		Windows::Foundation::IInspectable ConvertBack(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language) const;
	};

}

namespace winrt::Mntone::AngelUmbrella::Converters::factory_implementation {

	struct SingleToVector3AsZConverter: SingleToVector3AsZConverterT<SingleToVector3AsZConverter, implementation::SingleToVector3AsZConverter> {
	};

}
