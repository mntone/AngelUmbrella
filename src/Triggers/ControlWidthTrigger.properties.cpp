#include "pch.h"
#include "ControlWidthTrigger.h"
#if __has_include("Triggers/ControlWidthTrigger.g.cpp")
#include "Triggers/ControlWidthTrigger.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Triggers;
}

using namespace ::winrt::Mntone::AngelUmbrella::Triggers::implementation;

ControlWidthTrigger::DependencyProperties ControlWidthTrigger::props_;

void ControlWidthTrigger::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(ControlWidthTrigger);

	DEFINE_DP_METADATA(
		MinWidth,
		double,
		ControlWidthTrigger,
		PropertyMetadata(
			box_value(-1.0),
			&ControlWidthTrigger::OnMinWidthChangedStatic));

	DEFINE_DP_CALLBACK(
		TargetElement,
		Microsoft::UI::Xaml::FrameworkElement,
		ControlWidthTrigger,
		&ControlWidthTrigger::OnTargetElementChangedStatic);

	initialized_ = true;
}
