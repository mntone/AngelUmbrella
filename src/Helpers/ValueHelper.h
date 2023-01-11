#pragma once
#include <winrt/base.h>

namespace winrt::Mntone::AngelUmbrella::Helpers {

	template<typename T, typename Enable = void>
	struct ValueHelper final {
		static constexpr ::winrt::Windows::Foundation::IInspectable DefaultValue() noexcept {
			return T { };
		}

		static constexpr bool HasValue(::winrt::Windows::Foundation::IInspectable const& value) noexcept {
			return nullptr != value;
		}
	};

	template<typename T>
	struct ValueHelper<T, std::enable_if_t<std::is_base_of_v<::winrt::Windows::Foundation::IInspectable, T> && std::is_same_v<::winrt::Windows::Foundation::IInspectable, T>>> final {
		static constexpr ::winrt::Windows::Foundation::IInspectable DefaultValue() noexcept {
			return ::winrt::Windows::Foundation::IInspectable { nullptr };
		}

		static constexpr bool HasValue(::winrt::Windows::Foundation::IInspectable const& value) noexcept {
			if (nullptr == value) {
				return false;
			} else {
				std::optional<::winrt::hstring> string { value.try_as<hstring>() };
				return !(string.has_value() && string.value().empty());
			}
		}
	};

	template<typename T>
	struct ValueHelper<T, std::enable_if_t<std::is_base_of_v<::winrt::Windows::Foundation::IInspectable, T> && !std::is_same_v<::winrt::Windows::Foundation::IInspectable, T>>> final {
		static constexpr ::winrt::Windows::Foundation::IInspectable DefaultValue() noexcept {
			return ::winrt::Windows::Foundation::IInspectable { nullptr };
		}

		static constexpr bool HasValue(::winrt::Windows::Foundation::IInspectable const& value) noexcept {
			return nullptr != value;
		}
	};

	template<>
	struct ValueHelper<::winrt::hstring, void> final {
	private:
		static constexpr ::std::wstring_view empty_ { L"" };

	public:
		static inline ::winrt::Windows::Foundation::IInspectable DefaultValue() noexcept {
			return ::winrt::box_value(::winrt::hstring(empty_));
		}

		static inline bool HasValue(::winrt::Windows::Foundation::IInspectable const& value) noexcept {
			return !::winrt::unbox_value<::winrt::hstring>(value).empty();
		}
	};

	template<>
	struct ValueHelper<bool, void> final {
		static inline ::winrt::Windows::Foundation::IInspectable DefaultValue() noexcept {
			return ::winrt::box_value<bool>(false);
		}

		static inline bool HasValue(::winrt::Windows::Foundation::IInspectable const& value) noexcept {
			return nullptr != value;
		}
	};

}
