#include "pch.h"
#include "DateTimeToStringConverter.h"
#if __has_include("Converters/DateTimeToStringConverter.g.cpp")
#include "Converters/DateTimeToStringConverter.g.cpp"
#endif

constexpr std::wstring_view kDateTimeFormatDefault { L"longdate longtime" };
constexpr std::wstring_view kTimeZoneUTC { L"UTC" };

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::Globalization::DateTimeFormatting;
	using namespace ::winrt::Windows::UI::Xaml::Interop;

	using namespace ::winrt::Microsoft::UI::Xaml;
}

using namespace winrt::Mntone::AngelUmbrella::Converters::implementation;

DateTimeToStringConverter::DateTimeToStringConverter() noexcept
	: format_(kDateTimeFormatDefault)
	, formatter_(nullptr) {
}

winrt::IInspectable DateTimeToStringConverter::Convert(IInspectable const& value, [[maybe_unused]] TypeName const& targetType, IInspectable const& /*parameter*/, hstring const& language) {
	WINRT_ASSERT(xaml_typename<hstring>() == targetType /* C++/WinRT */ || (TypeName { hstring(std::wstring_view(L"String")), TypeKind::Metadata }) == targetType /* C# */);

	if (nullptr == formatter_) {
		if (!language.empty()) {
			formatter_ = DateTimeFormatter(format_, { language });
		} else {
			formatter_ = DateTimeFormatter(format_);
		}
	} else {
		auto currentLanguages { formatter_.Languages() };
		bool hasCurrentLang { currentLanguages.Size() != 0 };
		if (!language.empty()) {
			if (hasCurrentLang && language != currentLanguages.GetAt(0)) {
				formatter_ = DateTimeFormatter(format_, { language });
			}
		} else if (hasCurrentLang) {
			formatter_ = DateTimeFormatter(format_);
		}
	}

	std::optional<DateTime> datetime { value.try_as<DateTime>() };
	if (datetime) {
		hstring string { formatter_.Format(datetime.value(), kTimeZoneUTC) };
		return box_value(string);
	} else {
		return DependencyProperty::UnsetValue();
	}
}

winrt::IInspectable DateTimeToStringConverter::ConvertBack(IInspectable const& /*value*/, TypeName const& /*targetType*/, IInspectable const& /*parameter*/, hstring const& /*language*/) {
	throw hresult_not_implemented();
}
