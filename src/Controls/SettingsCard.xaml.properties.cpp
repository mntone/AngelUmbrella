#include "pch.h"
#include "SettingsCard.xaml.h"
#if __has_include("./Controls/SettingsCard.g.cpp")
#include "./Controls/SettingsCard.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace ::winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsCard::DependencyProperties SettingsCard::props_;

void SettingsCard::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(SettingsCard);

	DEFINE_DP_METADATA(
		ActionIcon,
		Microsoft::UI::Xaml::Controls::IconElement,
		SettingsCard,
		PropertyMetadata(box_value(hstring(L"\ue974"))));

	DEFINE_DP_METADATA(
		ActionIconTooltip,
		hstring,
		SettingsCard,
		PropertyMetadata(box_value(hstring(L"More"))));

	DEFINE_DP_CALLBACK(
		Description,
		winrt::IInspectable,
		SettingsCard,
		&SettingsCard::OnDescriptionChangedStatic);

	DEFINE_DP_CALLBACK(
		HeaderIcon,
		Microsoft::UI::Xaml::Controls::IconElement,
		SettingsCard,
		&SettingsCard::OnHeaderIconChangedStatic);

	DEFINE_DP_CALLBACK(
		Header,
		winrt::IInspectable,
		SettingsCard,
		&SettingsCard::OnHeaderChangedStatic);

	DEFINE_DP_CALLBACK(
		IsClickEnabled,
		bool,
		SettingsCard,
		&SettingsCard::OnIsClickEnabledChangedStatic);

	DEFINE_DP_METADATA(
		Orientation,
		Microsoft::UI::Xaml::Controls::Orientation,
		SettingsCard,
		PropertyMetadata(
			box_value(Microsoft::UI::Xaml::Controls::Orientation::Horizontal),
			PropertyChangedCallback(&SettingsCard::OnOrientationChangedStatic)));

	initialized_ = true;
}
