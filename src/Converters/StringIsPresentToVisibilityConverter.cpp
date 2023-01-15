#include "pch.h"
#include "StringIsPresentToVisibilityConverter.h"
#if __has_include("Converters/StringIsPresentToVisibilityConverter.g.cpp")
#include "Converters/StringIsPresentToVisibilityConverter.g.cpp"
#endif

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::UI::Xaml::Interop;

	using namespace ::winrt::Microsoft::UI::Xaml;
}

using namespace winrt::Mntone::AngelUmbrella::Converters::implementation;

StringIsPresentToVisibilityConverter::StringIsPresentToVisibilityConverter() noexcept {
}

winrt::IInspectable StringIsPresentToVisibilityConverter::Convert(IInspectable const& value, [[maybe_unused]] TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<Visibility>() == targetType);

	std::optional<hstring> string { value.try_as<hstring>() };
	return box_value(string.has_value() && !string.value().empty() ? Visibility::Visible : Visibility::Collapsed);
}

winrt::IInspectable StringIsPresentToVisibilityConverter::ConvertBack(IInspectable const& /*value*/, TypeName const& /*targetType*/, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	throw hresult_not_implemented();
}
