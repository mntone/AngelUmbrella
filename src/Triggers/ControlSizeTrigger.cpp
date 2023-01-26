#include "pch.h"
#include "ControlSizeTrigger.h"

namespace winrt {
	using namespace ::winrt::Windows::Foundation;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;

	using namespace ::winrt::Mntone::AngelUmbrella::Triggers;
}

using namespace winrt::Mntone::AngelUmbrella::Triggers::implementation;

ControlSizeTrigger::ControlSizeTrigger() {
	props_.DelayInitIfNeeded();
}

void ControlSizeTrigger::UpdateTrigger(double minWidth, double minHeight) const {
	bool active { false };
	if (TargetElement()) {
		if (minWidth >= 0.0) {
			if (minHeight >= 0.0) {
				active = size_.Width >= minWidth && size_.Height >= minHeight;
			} else {
				active = size_.Width >= minWidth;
			}
		} else if (minHeight >= 0.0) {
			active = size_.Height >= minHeight;
		}
	}
	SetActive(active);
}

void ControlSizeTrigger::OnTargetElementSizeChanged(IInspectable const& /*sender*/, SizeChangedEventArgs const& args) {
	Size newSize { args.NewSize() };

	double minWidth { MinWidth() };
	double minHeight { MinHeight() };
	if (minWidth >= 0.0) {
		if (minHeight >= 0.0) {
			size_ = newSize;
			UpdateTrigger(minWidth, minHeight);
		} else {
			if (size_.Width != newSize.Width) {
				size_.Width = newSize.Width;
				UpdateTrigger(minWidth, minHeight);
			}
		}
	} else if (minHeight >= 0.0) {
		if (size_.Height != newSize.Height) {
			size_.Height = newSize.Height;
			UpdateTrigger(minWidth, minHeight);
		}
	}
}

void ControlSizeTrigger::OnMinWidthChanged(double newValue) const {
	UpdateTrigger(newValue, MinHeight());
}

void ControlSizeTrigger::OnMinHeightChanged(double newValue) const {
	UpdateTrigger(MinWidth(), newValue);
}

void ControlSizeTrigger::OnTargetElementChanged(Microsoft::UI::Xaml::FrameworkElement const& newValue) {
	revoker_.revoke();

	UpdateTrigger(MinWidth(), MinHeight());

	if (newValue) {
		revoker_ = newValue.SizeChanged(auto_revoke, SizeChangedEventHandler(this, &ControlSizeTrigger::OnTargetElementSizeChanged));
	}
}

void ControlSizeTrigger::OnMinWidthChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	double oldValue { args.OldValue().as<double>() };
	double newValue { args.NewValue().as<double>() };
	if (oldValue >= 0.0 || newValue >= 0.0) {
		get_self<ControlSizeTrigger>(sender.as<winrt::ControlSizeTrigger>())->OnMinWidthChanged(newValue);
	}
}

void ControlSizeTrigger::OnMinHeightChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	double oldValue { args.OldValue().as<double>() };
	double newValue { args.NewValue().as<double>() };
	if (oldValue >= 0.0 || newValue >= 0.0) {
		get_self<ControlSizeTrigger>(sender.as<winrt::ControlSizeTrigger>())->OnMinHeightChanged(newValue);
	}
}

void ControlSizeTrigger::OnTargetElementChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<ControlSizeTrigger>(sender.as<winrt::ControlSizeTrigger>())->OnTargetElementChanged(args.NewValue().as<FrameworkElement>());
}
