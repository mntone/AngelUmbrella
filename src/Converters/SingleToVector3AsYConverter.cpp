#include "pch.h"
#include "SingleToVector3AsYConverter.h"
#if __has_include("Converters/SingleToVector3AsYConverter.g.cpp")
#include "Converters/SingleToVector3AsYConverter.g.cpp"
#endif

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::Foundation::Numerics;
	using namespace ::winrt::Windows::UI::Xaml::Interop;

	using namespace ::winrt::Microsoft::UI::Xaml;
}

using namespace winrt::Mntone::AngelUmbrella::Converters::implementation;

SingleToVector3AsYConverter::SingleToVector3AsYConverter() noexcept {
}

winrt::IInspectable SingleToVector3AsYConverter::Convert(IInspectable const& value, TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<float3>() == targetType);

	std::optional<float> single { value.try_as<float>() };
	return single.has_value() ? box_value(float3(0.f, single.value(), 0.f)) : DependencyProperty::UnsetValue();
}

winrt::IInspectable SingleToVector3AsYConverter::ConvertBack(IInspectable const& value, TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& /*language*/) const {
	WINRT_ASSERT(xaml_typename<float>() == targetType);

	std::optional<float3> vector { value.try_as<float3>() };
	return vector.has_value() ? box_value(vector.value().y) : IInspectable { nullptr };
}
