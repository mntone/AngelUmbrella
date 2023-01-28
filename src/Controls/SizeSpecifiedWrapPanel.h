#pragma once
#include "Controls/SizeSpecifiedWrapPanel.g.h"

namespace winrt::Mntone::AngelUmbrella::Controls::implementation {

	struct SizeSpecifiedWrapPanel: SizeSpecifiedWrapPanelT<SizeSpecifiedWrapPanel> {
		SizeSpecifiedWrapPanel();

		Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size const& availableSize);
		Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size const& finalSize);

	private:
		static void OnLayoutMetricsChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnOrientationChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	public:  // - Properties
		inline double ItemHeight() const { return GetValue(props_.ItemHeight).as<double>(); }
		inline void ItemHeight(double value) const { SetValue(props_.ItemHeight, box_value(value)); }

		inline double ItemWidth() const { return GetValue(props_.ItemWidth).as<double>(); }
		inline void ItemWidth(double value) const { SetValue(props_.ItemWidth, box_value(value)); }

		inline double HorizontalSpacing() const { return GetValue(props_.HorizontalSpacing).as<double>(); }
		inline void HorizontalSpacing(double value) const { SetValue(props_.HorizontalSpacing, box_value(value)); }

		inline Microsoft::UI::Xaml::Controls::Orientation Orientation() const { return GetValue(props_.Orientation).as<Microsoft::UI::Xaml::Controls::Orientation>(); }
		inline void Orientation(Microsoft::UI::Xaml::Controls::Orientation value) const { SetValue(props_.Orientation, box_value(value)); }

		inline double VerticalSpacing() const { return GetValue(props_.VerticalSpacing).as<double>(); }
		inline void VerticalSpacing(double value) const { SetValue(props_.VerticalSpacing, box_value(value)); }

		inline static Microsoft::UI::Xaml::DependencyProperty ItemHeightProperty() noexcept { return props_.ItemHeight; }
		inline static Microsoft::UI::Xaml::DependencyProperty ItemWidthProperty() noexcept { return props_.ItemWidth; }
		inline static Microsoft::UI::Xaml::DependencyProperty HorizontalSpacingProperty() noexcept { return props_.HorizontalSpacing; }
		inline static Microsoft::UI::Xaml::DependencyProperty OrientationProperty() noexcept { return props_.Orientation; }
		inline static Microsoft::UI::Xaml::DependencyProperty VerticalSpacingProperty() noexcept { return props_.VerticalSpacing; }

	private: // - Variables
		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			Microsoft::UI::Xaml::DependencyProperty ItemHeight { nullptr };
			Microsoft::UI::Xaml::DependencyProperty ItemWidth { nullptr };
			Microsoft::UI::Xaml::DependencyProperty HorizontalSpacing { nullptr };
			Microsoft::UI::Xaml::DependencyProperty Orientation { nullptr };
			Microsoft::UI::Xaml::DependencyProperty VerticalSpacing { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Controls::factory_implementation {

	struct SizeSpecifiedWrapPanel: SizeSpecifiedWrapPanelT<SizeSpecifiedWrapPanel, implementation::SizeSpecifiedWrapPanel> {
	};

}
