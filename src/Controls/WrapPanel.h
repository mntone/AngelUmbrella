#pragma once
#include "Controls/WrapPanel.g.h"

namespace winrt::Mntone::AngelUmbrella::Controls::implementation {

	struct WrapPanel: WrapPanelT<WrapPanel> {
		WrapPanel();

		Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size const& availableSize);
		Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size const& finalSize);

	private:
		static void OnLayoutMetricsChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnOrientationChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	public:  // - Properties
		inline double HorizontalSpacing() const { return GetValue(props_.HorizontalSpacing).as<double>(); }
		inline void HorizontalSpacing(double value) const { SetValue(props_.HorizontalSpacing, box_value(value)); }

		inline Microsoft::UI::Xaml::Controls::Orientation Orientation() const { return GetValue(props_.Orientation).as<Microsoft::UI::Xaml::Controls::Orientation>(); }
		inline void Orientation(Microsoft::UI::Xaml::Controls::Orientation value) const { SetValue(props_.Orientation, box_value(value)); }

		inline double VerticalSpacing() const { return GetValue(props_.VerticalSpacing).as<double>(); }
		inline void VerticalSpacing(double value) const { SetValue(props_.VerticalSpacing, box_value(value)); }

		inline static Microsoft::UI::Xaml::DependencyProperty HorizontalSpacingProperty() noexcept { return props_.HorizontalSpacing; }
		inline static Microsoft::UI::Xaml::DependencyProperty OrientationProperty() noexcept { return props_.Orientation; }
		inline static Microsoft::UI::Xaml::DependencyProperty VerticalSpacingProperty() noexcept { return props_.VerticalSpacing; }

	private: // - Variables
		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			Microsoft::UI::Xaml::DependencyProperty HorizontalSpacing { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Orientation { nullptr };
			Microsoft::UI::Xaml::DependencyProperty VerticalSpacing { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Controls::factory_implementation {

	struct WrapPanel: WrapPanelT<WrapPanel, implementation::WrapPanel> {
	};

}
