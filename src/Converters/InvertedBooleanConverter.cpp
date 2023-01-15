#include "pch.h"
#include "InvertedBooleanConverter.h"
#if __has_include("Converters/InvertedBooleanConverter.g.cpp")
#include "Converters/InvertedBooleanConverter.g.cpp"
#endif

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::UI::Xaml::Interop;

	using namespace ::winrt::Microsoft::UI::Xaml;
}

using namespace winrt::Mntone::AngelUmbrella::Converters::implementation;

InvertedBooleanConverter::InvertedBooleanConverter() noexcept {
}

winrt::IInspectable InvertedBooleanConverter::Convert(IInspectable const& value, [[maybe_unused]] TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<bool>() == targetType);

	std::optional<bool> boolean { value.try_as<bool>() };
	return boolean.has_value() ? box_value(!boolean.value()) : DependencyProperty::UnsetValue();
}

winrt::IInspectable InvertedBooleanConverter::ConvertBack(IInspectable const& value, [[maybe_unused]] TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<bool>() == targetType);

	std::optional<bool> boolean { value.try_as<bool>() };
	return boolean.has_value() ? box_value(!boolean.value()) : IInspectable { nullptr };
}
