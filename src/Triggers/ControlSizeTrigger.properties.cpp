#include "pch.h"
#include "ControlSizeTrigger.h"
#if __has_include("Triggers/ControlSizeTrigger.g.cpp")
#include "Triggers/ControlSizeTrigger.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Triggers;
}

using namespace ::winrt::Mntone::AngelUmbrella::Triggers::implementation;

ControlSizeTrigger::DependencyProperties ControlSizeTrigger::props_;

void ControlSizeTrigger::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(ControlSizeTrigger);

	IInspectable minusOne { box_value(-1.0) };

	DEFINE_DP_METADATA(
		MinWidth,
		double,
		ControlSizeTrigger,
		PropertyMetadata(
			minusOne,
			&ControlSizeTrigger::OnMinWidthChangedStatic));

	DEFINE_DP_METADATA(
		MinHeight,
		double,
		ControlSizeTrigger,
		PropertyMetadata(
			minusOne,
			&ControlSizeTrigger::OnMinHeightChangedStatic));

	DEFINE_DP_CALLBACK(
		TargetElement,
		Microsoft::UI::Xaml::FrameworkElement,
		ControlSizeTrigger,
		&ControlSizeTrigger::OnTargetElementChangedStatic);

	initialized_ = true;
}
