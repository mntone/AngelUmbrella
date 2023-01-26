#pragma once
#include "Triggers/ControlSizeTrigger.g.h"

namespace winrt::Mntone::AngelUmbrella::Triggers::implementation {

	struct ControlSizeTrigger: ControlSizeTriggerT<ControlSizeTrigger> {
		ControlSizeTrigger();

	private:
		inline void UpdateTrigger(double minWidth, double minHeight) const;

	private:
		void OnTargetElementSizeChanged(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& args);

		inline void OnMinWidthChanged(double newValue) const;
		inline void OnMinHeightChanged(double newValue) const;
		inline void OnTargetElementChanged(Microsoft::UI::Xaml::FrameworkElement const& newValue);

		static void OnMinWidthChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnMinHeightChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);
		static void OnTargetElementChangedStatic(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args);

	public:  // - Properties
		inline double MinWidth() const { return GetValue(props_.MinWidth).as<double>(); }
		inline void MinWidth(double value) const { SetValue(props_.MinWidth, box_value(value)); }

		inline double MinHeight() const { return GetValue(props_.MinHeight).as<double>(); }
		inline void MinHeight(double value) const { SetValue(props_.MinHeight, box_value(value)); }

		inline Microsoft::UI::Xaml::FrameworkElement TargetElement() const { return GetValue(props_.TargetElement).as<Microsoft::UI::Xaml::FrameworkElement>(); }
		inline void TargetElement(Microsoft::UI::Xaml::FrameworkElement const& value) const { SetValue(props_.TargetElement, value); }

		inline static Microsoft::UI::Xaml::DependencyProperty MinWidthProperty() noexcept { return props_.MinWidth; }
		inline static Microsoft::UI::Xaml::DependencyProperty MinHeightProperty() noexcept { return props_.MinHeight; }
		inline static Microsoft::UI::Xaml::DependencyProperty TargetElementProperty() noexcept { return props_.TargetElement; }

	private: // - Variables
		Windows::Foundation::Size size_;
		Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker revoker_;

		struct DependencyProperties final {
			void DelayInitIfNeeded();

			bool initialized_ { false };
			Microsoft::UI::Xaml::DependencyProperty MinWidth { nullptr };
			Microsoft::UI::Xaml::DependencyProperty MinHeight { nullptr };
			Microsoft::UI::Xaml::DependencyProperty TargetElement { nullptr };
		};
		static DependencyProperties props_;
	};

}

namespace winrt::Mntone::AngelUmbrella::Triggers::factory_implementation {

	struct ControlSizeTrigger: ControlSizeTriggerT<ControlSizeTrigger, implementation::ControlSizeTrigger> {
	};

}
