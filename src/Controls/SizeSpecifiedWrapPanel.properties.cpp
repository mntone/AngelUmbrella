#include "pch.h"
#include "SizeSpecifiedWrapPanel.h"
#if __has_include("Controls/SizeSpecifiedWrapPanel.g.cpp")
#include "Controls/SizeSpecifiedWrapPanel.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace ::winrt::Mntone::AngelUmbrella::Controls::implementation;

SizeSpecifiedWrapPanel::DependencyProperties SizeSpecifiedWrapPanel::props_;

void SizeSpecifiedWrapPanel::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(SizeSpecifiedWrapPanel);

	double nan { std::numeric_limits<double>::signaling_NaN() };

	DEFINE_DP_METADATA(
		ItemHeight,
		double,
		SizeSpecifiedWrapPanel,
		PropertyMetadata(
			box_value(nan),
			PropertyChangedCallback(&SizeSpecifiedWrapPanel::OnLayoutMetricsChangedStatic)));

	DEFINE_DP_METADATA(
		ItemWidth,
		double,
		SizeSpecifiedWrapPanel,
		PropertyMetadata(
			box_value(nan),
			PropertyChangedCallback(&SizeSpecifiedWrapPanel::OnLayoutMetricsChangedStatic)));

	DEFINE_DP_CALLBACK(
		HorizontalSpacing,
		double,
		SizeSpecifiedWrapPanel,
		&SizeSpecifiedWrapPanel::OnLayoutMetricsChangedStatic);

	DEFINE_DP_METADATA(
		Orientation,
		Microsoft::UI::Xaml::Controls::Orientation,
		SizeSpecifiedWrapPanel,
		PropertyMetadata(
			box_value(Microsoft::UI::Xaml::Controls::Orientation::Horizontal),
			PropertyChangedCallback(&SizeSpecifiedWrapPanel::OnOrientationChangedStatic)));

	DEFINE_DP_CALLBACK(
		VerticalSpacing,
		double,
		SizeSpecifiedWrapPanel,
		&SizeSpecifiedWrapPanel::OnLayoutMetricsChangedStatic);

	initialized_ = true;
}
