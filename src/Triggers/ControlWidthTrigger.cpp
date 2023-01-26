#include "pch.h"
#include "ControlWidthTrigger.h"

namespace winrt {
	using namespace ::winrt::Windows::Foundation;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;

	using namespace ::winrt::Mntone::AngelUmbrella::Triggers;
}

using namespace winrt::Mntone::AngelUmbrella::Triggers::implementation;

ControlWidthTrigger::ControlWidthTrigger(): width_(0.f) {
	props_.DelayInitIfNeeded();
}

void ControlWidthTrigger::UpdateTrigger(double minWidth) const {
	bool active { false };
	if (TargetElement()) {
		if (minWidth >= 0.0) {
			active = width_ >= minWidth;
		}
	}
	SetActive(active);
}

void ControlWidthTrigger::OnTargetElementSizeChanged(IInspectable const& /*sender*/, SizeChangedEventArgs const& args) {
	Size newSize { args.NewSize() };

	double minWidth { MinWidth() };
	if (minWidth >= 0.0) {
		if (width_ != newSize.Width) {
			width_ = newSize.Width;
			UpdateTrigger(minWidth);
		}
	}
}

void ControlWidthTrigger::OnMinWidthChanged(double newValue) const {
	UpdateTrigger(newValue);
}

void ControlWidthTrigger::OnTargetElementChanged(Microsoft::UI::Xaml::FrameworkElement const& newValue) {
	revoker_.revoke();

	UpdateTrigger(MinWidth());

	if (newValue) {
		revoker_ = newValue.SizeChanged(auto_revoke, SizeChangedEventHandler(this, &ControlWidthTrigger::OnTargetElementSizeChanged));
	}
}

void ControlWidthTrigger::OnMinWidthChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	double oldValue { args.OldValue().as<double>() };
	double newValue { args.NewValue().as<double>() };
	if (oldValue >= 0.0 || newValue >= 0.0) {
		get_self<ControlWidthTrigger>(sender.as<winrt::ControlWidthTrigger>())->OnMinWidthChanged(newValue);
	}
}

void ControlWidthTrigger::OnTargetElementChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<ControlWidthTrigger>(sender.as<winrt::ControlWidthTrigger>())->OnTargetElementChanged(args.NewValue().as<FrameworkElement>());
}
