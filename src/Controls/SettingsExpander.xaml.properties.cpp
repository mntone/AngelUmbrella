#include "pch.h"
#include "SettingsExpander.xaml.h"
#if __has_include("./Controls/SettingsExpander.g.cpp")
#include "./Controls/SettingsExpander.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace ::winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsExpander::DependencyProperties SettingsExpander::props_;

void SettingsExpander::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(SettingsExpander);

	DEFINE_DP_CALLBACK(
		Description,
		winrt::IInspectable,
		SettingsExpander,
		&SettingsExpander::OnDescriptionChangedStatic);

	DEFINE_DP(ExpanderContent, winrt::IInspectable, SettingsExpander);

	DEFINE_DP_CALLBACK(
		HeaderIcon,
		winrt::Microsoft::UI::Xaml::Controls::IconElement,
		SettingsExpander,
		&SettingsExpander::OnHeaderIconChangedStatic);

	DEFINE_DP_METADATA(
		Orientation,
		winrt::Microsoft::UI::Xaml::Controls::Orientation,
		SettingsExpander,
		winrt::PropertyMetadata(
			winrt::box_value(winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)));

	initialized_ = true;
}
