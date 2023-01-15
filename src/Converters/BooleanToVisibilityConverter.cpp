#include "pch.h"
#include "BooleanToVisibilityConverter.h"
#if __has_include("Converters/BooleanToVisibilityConverter.g.cpp")
#include "Converters/BooleanToVisibilityConverter.g.cpp"
#endif

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::UI::Xaml::Interop;

	using namespace ::winrt::Microsoft::UI::Xaml;
}

using namespace winrt::Mntone::AngelUmbrella::Converters::implementation;

BooleanToVisibilityConverter::BooleanToVisibilityConverter() noexcept {
}

winrt::IInspectable BooleanToVisibilityConverter::Convert(IInspectable const& value, [[maybe_unused]] TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<Visibility>() == targetType);

	std::optional<bool> boolean { value.try_as<bool>() };
	return boolean.has_value() ? box_value(boolean.value() ? Visibility::Visible : Visibility::Collapsed) : DependencyProperty::UnsetValue();
}

winrt::IInspectable BooleanToVisibilityConverter::ConvertBack(IInspectable const& value, [[maybe_unused]] TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<bool>() == targetType);

	std::optional<Visibility> visibility { value.try_as<Visibility>() };
	return visibility.has_value() ? box_value(Visibility::Visible == visibility) : IInspectable { nullptr };
}
