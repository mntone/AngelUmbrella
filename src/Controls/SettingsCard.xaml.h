#pragma once
#include "./Controls/SettingsCard.g.h"

namespace winrt::Mntone::AngelUmbrella::Controls::implementation {

	struct SettingsCard: SettingsCard_base<SettingsCard> {
		SettingsCard();

		void OnApplyTemplate() const;
		Microsoft::UI::Xaml::Automation::Peers::AutomationPeer OnCreateAutomationPeer() const;

		// internal:
		void OnPointerEntered(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) const;
		void OnPointerPressed(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) const;
		void OnPointerReleased(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) const;
		void OnPointerExited(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) const;

		void OnKeyDown(Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args) const;
		void OnKeyUp(Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args) const;

	private:
		static void OnIsEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

		inline void UpdateActionIcon(bool isClickEnabled) const;

	private:
		inline void OnDescriptionChanged(Windows::Foundation::IInspectable const& newValue) const;
		inline void OnHeaderIconChanged(Microsoft::UI::Xaml::Controls::IconElement const& newValue) const;
		inline void OnHeaderChanged(Windows::Foundation::IInspectable const& newValue) const;
		inline void OnIsClickEnabledChanged(bool newValue, bool useTransitions = true) const;
		inline void OnOrientationChanged(Microsoft::UI::Xaml::Controls::Orientation newValue) const;

		static void OnDescriptionChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnHeaderIconChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnHeaderChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnIsClickEnabledChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnOrientationChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	public:  // - Properties
		inline Microsoft::UI::Xaml::Controls::IconElement ActionIcon() const { return GetValue(props_.ActionIcon).as<Microsoft::UI::Xaml::Controls::IconElement>(); }
		inline void ActionIcon(Microsoft::UI::Xaml::Controls::IconElement const& value) const { SetValue(props_.ActionIcon, value); }

		inline hstring ActionIconTooltip() const { return unbox_value<hstring>(GetValue(props_.ActionIconTooltip)); }
		inline void ActionIconTooltip(param::hstring const& value) const { SetValue(props_.ActionIconTooltip, box_value(value)); }

		inline Windows::Foundation::IInspectable Description() const { return GetValue(props_.Description); }
		inline void Description(Windows::Foundation::IInspectable const& value) const { SetValue(props_.Description, value); }

		inline Microsoft::UI::Xaml::Controls::IconElement HeaderIcon() const { return GetValue(props_.HeaderIcon).as<Microsoft::UI::Xaml::Controls::IconElement>(); }
		inline void HeaderIcon(Microsoft::UI::Xaml::Controls::IconElement const& value) const { SetValue(props_.HeaderIcon, value); }

		inline Windows::Foundation::IInspectable Header() const { return GetValue(props_.Header); }
		inline void Header(Windows::Foundation::IInspectable const& value) const { SetValue(props_.Header, value); }

		inline bool IsClickEnabled() const { return unbox_value<bool>(GetValue(props_.IsClickEnabled)); }
		inline void IsClickEnabled(bool value) const { SetValue(props_.IsClickEnabled, box_value(value)); }

		inline Microsoft::UI::Xaml::Controls::Orientation Orientation() const { return unbox_value<Microsoft::UI::Xaml::Controls::Orientation>(GetValue(props_.Orientation)); }
		inline void Orientation(Microsoft::UI::Xaml::Controls::Orientation value) const { SetValue(props_.Orientation, box_value(value)); }

		inline static Microsoft::UI::Xaml::DependencyProperty ActionIconProperty() noexcept { return props_.ActionIcon; }
		inline static Microsoft::UI::Xaml::DependencyProperty ActionIconTooltipProperty() noexcept { return props_.ActionIconTooltip; }
		inline static Microsoft::UI::Xaml::DependencyProperty DescriptionProperty() noexcept { return props_.Description; }
		inline static Microsoft::UI::Xaml::DependencyProperty HeaderIconProperty() noexcept { return props_.HeaderIcon; }
		inline static Microsoft::UI::Xaml::DependencyProperty HeaderProperty() noexcept { return props_.Header; }
		inline static Microsoft::UI::Xaml::DependencyProperty IsClickEnabledProperty() noexcept { return props_.IsClickEnabled; }
		inline static Microsoft::UI::Xaml::DependencyProperty OrientationProperty() noexcept { return props_.Orientation; }

	private: // - Variables
		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			Microsoft::UI::Xaml::DependencyProperty ActionIcon { nullptr };
			Microsoft::UI::Xaml::DependencyProperty ActionIconTooltip { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Description { nullptr };
			Microsoft::UI::Xaml::DependencyProperty HeaderIcon { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Header  { nullptr };
			Microsoft::UI::Xaml::DependencyProperty IsClickEnabled { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Orientation { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Controls::factory_implementation {

	struct SettingsCard: SettingsCardT<SettingsCard, implementation::SettingsCard> {
	};

}
