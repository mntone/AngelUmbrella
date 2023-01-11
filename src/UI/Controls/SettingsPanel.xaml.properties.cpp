#include "pch.h"
#include "SettingsPanel.xaml.h"
#if __has_include("./UI/Controls/SettingsPanel.g.cpp")
#include "./UI/Controls/SettingsPanel.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "UI/Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::UI::Controls;
}

using namespace ::winrt::Mntone::AngelUmbrella::UI::Controls::implementation;

SettingsPanel::DependencyProperties SettingsPanel::props_;

void SettingsPanel::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(SettingsPanel);

	DEFINE_DP_METADATA(
		ActionIcon,
		winrt::Microsoft::UI::Xaml::Controls::IconElement,
		SettingsPanel,
		winrt::PropertyMetadata(winrt::box_value(winrt::hstring(L"\ue974"))));

	DEFINE_DP_METADATA(
		ActionIconTooltip,
		winrt::hstring,
		SettingsPanel,
		winrt::PropertyMetadata(winrt::box_value(winrt::hstring(L"More"))));

	DEFINE_DP_CALLBACK(
		Description,
		winrt::IInspectable,
		SettingsPanel,
		&SettingsPanel::OnDescriptionChangedStatic);

	DEFINE_DP_CALLBACK(
		HeaderIcon,
		winrt::Microsoft::UI::Xaml::Controls::IconElement,
		SettingsPanel,
		&SettingsPanel::OnHeaderIconChangedStatic);

	DEFINE_DP_CALLBACK(
		Header,
		winrt::IInspectable,
		SettingsPanel,
		&SettingsPanel::OnHeaderChangedStatic);

	DEFINE_DP_METADATA(
		Orientation,
		winrt::Microsoft::UI::Xaml::Controls::Orientation,
		SettingsPanel,
		winrt::PropertyMetadata(
			winrt::box_value(winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal),
			winrt::PropertyChangedCallback(&SettingsPanel::OnOrientationChangedStatic)));

	initialized_ = true;
}
