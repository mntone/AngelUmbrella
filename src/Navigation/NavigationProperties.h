#pragma once
#include "Navigation/NavigationProperties.g.h"

namespace winrt::Mntone::AngelUmbrella::Navigation::implementation {

	struct NavigationProperties final {
		static inline void Initialize() {
			props_.DelayInitIfNeeded();
		}

		static inline Windows::UI::Xaml::Interop::TypeName GetPageType(Microsoft::UI::Xaml::Controls::NavigationViewItem const& item) {
			return unbox_value<Windows::UI::Xaml::Interop::TypeName>(item.GetValue(props_.PageType));
		}

		static inline void SetPageType(
			Microsoft::UI::Xaml::Controls::NavigationViewItem const& item,
			Windows::UI::Xaml::Interop::TypeName const& value) {
			item.SetValue(props_.PageType, box_value(value));
		}

		static inline Windows::Foundation::IInspectable GetParameter(Microsoft::UI::Xaml::Controls::NavigationViewItem const& item) {
			return item.GetValue(props_.Parameter);
		}

		static inline void SetParameter(
			Microsoft::UI::Xaml::Controls::NavigationViewItem const& item,
			Windows::Foundation::IInspectable const& value) {
			item.SetValue(props_.Parameter, value);
		}

		static inline Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo GetTransitionInfo(Microsoft::UI::Xaml::Controls::NavigationViewItem const& item) {
			return unbox_value<Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo>(item.GetValue(props_.TransitionInfo));
		}

		static inline void SetTransitionInfo(
			Microsoft::UI::Xaml::Controls::NavigationViewItem const& item,
			Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo const& value) {
			item.SetValue(props_.TransitionInfo, value);
		}

		static winrt::Microsoft::UI::Xaml::DependencyProperty PageTypeProperty() noexcept { return props_.PageType; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty ParameterProperty() noexcept { return props_.Parameter; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty TransitionInfoProperty() noexcept { return props_.TransitionInfo; }

	private:
		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			Microsoft::UI::Xaml::DependencyProperty PageType { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Parameter { nullptr };
			Microsoft::UI::Xaml::DependencyProperty TransitionInfo { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Navigation::factory_implementation {

	struct NavigationProperties: NavigationPropertiesT<NavigationProperties, implementation::NavigationProperties> {
	};

}
