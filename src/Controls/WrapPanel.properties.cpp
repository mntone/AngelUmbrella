#include "pch.h"
#include "WrapPanel.h"
#if __has_include("Controls/WrapPanel.g.cpp")
#include "Controls/WrapPanel.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace ::winrt::Mntone::AngelUmbrella::Controls::implementation;

WrapPanel::DependencyProperties WrapPanel::props_;

void WrapPanel::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(WrapPanel);

	DEFINE_DP_CALLBACK(
		HorizontalSpacing,
		double,
		WrapPanel,
		&WrapPanel::OnLayoutMetricsChangedStatic);

	DEFINE_DP_METADATA(
		Orientation,
		Microsoft::UI::Xaml::Controls::Orientation,
		WrapPanel,
		PropertyMetadata(
			box_value(Microsoft::UI::Xaml::Controls::Orientation::Horizontal),
			PropertyChangedCallback(&WrapPanel::OnOrientationChangedStatic)));

	DEFINE_DP_CALLBACK(
		VerticalSpacing,
		double,
		WrapPanel,
		&WrapPanel::OnLayoutMetricsChangedStatic);

	initialized_ = true;
}
