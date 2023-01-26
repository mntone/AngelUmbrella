#pragma once
#include "./Controls/SettingsExpander.g.h"

namespace winrt::Mntone::AngelUmbrella::Controls::implementation {

	struct SettingsExpander: SettingsExpander_base<SettingsExpander> {
		SettingsExpander();

		void OnApplyTemplate() const;

		void OnPointerEntered(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) const;
		void OnPointerExited(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) const;

	private:
		static void OnIsEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	private:
		inline void OnDescriptionChanged(Windows::Foundation::IInspectable const& newValue) const;
		inline void OnHeaderIconChanged(Microsoft::UI::Xaml::Controls::IconElement const& newValue) const;
		inline void OnOrientationChanged(Microsoft::UI::Xaml::Controls::Orientation newValue) const;

		static void OnDescriptionChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnHeaderIconChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnOrientationChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	public:  // - Properties
		inline Windows::Foundation::IInspectable Description() const { return GetValue(props_.Description); }
		inline void Description(Windows::Foundation::IInspectable const& value) const { SetValue(props_.Description, value); }

		inline Windows::Foundation::IInspectable ExpanderContent() const { return GetValue(props_.ExpanderContent); }
		inline void ExpanderContent(Windows::Foundation::IInspectable const& value) const { SetValue(props_.ExpanderContent, value); }

		inline Microsoft::UI::Xaml::Controls::IconElement HeaderIcon() const { return GetValue(props_.HeaderIcon).as<Microsoft::UI::Xaml::Controls::IconElement>(); }
		inline void HeaderIcon(Microsoft::UI::Xaml::Controls::IconElement const& value) const { SetValue(props_.HeaderIcon, value); }

		inline Microsoft::UI::Xaml::Controls::Orientation Orientation() const { return winrt::unbox_value<Microsoft::UI::Xaml::Controls::Orientation>(GetValue(props_.Orientation)); }
		inline void Orientation(Microsoft::UI::Xaml::Controls::Orientation value) const { SetValue(props_.Orientation, box_value(value)); }

		inline static Microsoft::UI::Xaml::DependencyProperty DescriptionProperty() noexcept { return props_.Description; }
		inline static Microsoft::UI::Xaml::DependencyProperty ExpanderContentProperty() noexcept { return props_.ExpanderContent; }
		inline static Microsoft::UI::Xaml::DependencyProperty HeaderIconProperty() noexcept { return props_.HeaderIcon; }
		inline static Microsoft::UI::Xaml::DependencyProperty OrientationProperty() noexcept { return props_.Orientation; }

	private: // - Variables
		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			Microsoft::UI::Xaml::DependencyProperty Description { nullptr };
			Microsoft::UI::Xaml::DependencyProperty ExpanderContent { nullptr };
			Microsoft::UI::Xaml::DependencyProperty HeaderIcon { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Orientation { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Controls::factory_implementation {

	struct SettingsExpander: SettingsExpanderT<SettingsExpander, implementation::SettingsExpander> {
	};

}
