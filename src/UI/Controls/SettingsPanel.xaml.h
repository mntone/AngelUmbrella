#pragma once
#include "./UI/Controls/SettingsPanel.g.h"

namespace winrt::Mntone::AngelUmbrella::UI::Controls::implementation {

	struct SettingsPanel: SettingsPanel_base<SettingsPanel> {
		SettingsPanel() noexcept;

		void OnApplyTemplate() const;

	private:
		inline void OnButtonIconChanged(bool isClickEnabled) const;

	public:
		inline void OnDescriptionChanged(winrt::Windows::Foundation::IInspectable const& newValue) const;
		inline void OnHeaderIconChanged(winrt::Microsoft::UI::Xaml::Controls::IconElement const& newValue) const;
		inline void OnHeaderChanged(winrt::Windows::Foundation::IInspectable const& newValue) const;
		inline void OnOrientationChanged(winrt::Microsoft::UI::Xaml::Controls::Orientation newValue) const;

	private:
		static void OnDescriptionChangedStatic(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnHeaderIconChangedStatic(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnHeaderChangedStatic(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnOrientationChangedStatic(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	public:  // - Properties
		inline winrt::Microsoft::UI::Xaml::Controls::IconElement ActionIcon() const { return GetValue(props_.ActionIcon).as<winrt::Microsoft::UI::Xaml::Controls::IconElement>(); }
		inline void ActionIcon(winrt::Microsoft::UI::Xaml::Controls::IconElement const& value) const { SetValue(props_.ActionIcon, value); }

		inline winrt::hstring ActionIconTooltip() const { return winrt::unbox_value<winrt::hstring>(GetValue(props_.ActionIconTooltip)); }
		inline void ActionIconTooltip(winrt::param::hstring const& value) const { SetValue(props_.ActionIconTooltip, winrt::box_value(value)); }

		inline winrt::Windows::Foundation::IInspectable Description() const { return GetValue(props_.Description); }
		inline void Description(winrt::Windows::Foundation::IInspectable const& value) const { SetValue(props_.Description, value); }

		inline winrt::Microsoft::UI::Xaml::Controls::IconElement HeaderIcon() const { return GetValue(props_.HeaderIcon).as<winrt::Microsoft::UI::Xaml::Controls::IconElement>(); }
		inline void HeaderIcon(winrt::Microsoft::UI::Xaml::Controls::IconElement const& value) const { SetValue(props_.HeaderIcon, value); }

		inline winrt::Windows::Foundation::IInspectable Header() const { return GetValue(props_.Header); }
		inline void Header(winrt::Windows::Foundation::IInspectable const& value) const { SetValue(props_.Header, value); }

		inline winrt::Microsoft::UI::Xaml::Controls::Orientation Orientation() const { return winrt::unbox_value<winrt::Microsoft::UI::Xaml::Controls::Orientation>(GetValue(props_.Orientation)); }
		inline void Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation value) const { SetValue(props_.Orientation, winrt::box_value(value)); }

		static winrt::Microsoft::UI::Xaml::DependencyProperty ActionIconProperty() noexcept { return props_.ActionIcon; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty ActionIconTooltipProperty() noexcept { return props_.ActionIconTooltip; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty DescriptionProperty() noexcept { return props_.Description; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderIconProperty() noexcept { return props_.HeaderIcon; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderProperty() noexcept { return props_.Header; }
		static winrt::Microsoft::UI::Xaml::DependencyProperty OrientationProperty() noexcept { return props_.Orientation; }

	private: // - Variables
		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			winrt::Microsoft::UI::Xaml::DependencyProperty ActionIcon { nullptr };
			winrt::Microsoft::UI::Xaml::DependencyProperty ActionIconTooltip { nullptr };
			winrt::Microsoft::UI::Xaml::DependencyProperty Description { nullptr };
			winrt::Microsoft::UI::Xaml::DependencyProperty HeaderIcon { nullptr };
			winrt::Microsoft::UI::Xaml::DependencyProperty Header  { nullptr };
			winrt::Microsoft::UI::Xaml::DependencyProperty Orientation { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::UI::Controls::factory_implementation {

	struct SettingsPanel: SettingsPanelT<SettingsPanel, implementation::SettingsPanel> {
	};

}
