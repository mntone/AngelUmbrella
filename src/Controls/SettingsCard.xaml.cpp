#include "pch.h"
#include "SettingsCard.xaml.h"

#include <winrt/Microsoft.UI.Xaml.Automation.Peers.h>

#include "SettingsCardAutomationPeer.h"

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsCard { L"Mntone.AngelUmbrella.Controls.SettingsCard" };
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsCard_Uri { L"ms-appx:///Mntone.AngelUmbrella/Controls/SettingsCard.xaml" };
}

namespace controls {
	constexpr std::wstring_view ActionIcon { L"ActionIcon" };
	constexpr std::wstring_view Description { L"Description" };
	constexpr std::wstring_view HeaderIcon { L"HeaderIcon" };
	constexpr std::wstring_view Header { L"Header" };
}

namespace states {
	constexpr std::wstring_view Normal { L"Normal" };
	constexpr std::wstring_view PointerOver { L"PointerOver" };
	constexpr std::wstring_view Pressed { L"Pressed" };
	constexpr std::wstring_view Disabled { L"Disabled" };

	constexpr std::wstring_view HeaderOnly { L"HeaderOnly" };
	constexpr std::wstring_view HeaderAndDescription { L"HeaderAndDescription" };

	constexpr std::wstring_view Vertical { L"Vertical" };
	constexpr std::wstring_view Horizontal { L"Horizontal" };
}

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::System;

	using namespace ::winrt::Microsoft::UI::Input;
	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Automation;
	using namespace ::winrt::Microsoft::UI::Xaml::Automation::Peers;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Input;

	using namespace ::winrt::Mntone::AngelUmbrella::Helpers;
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsCard::SettingsCard() {
	props_.DelayInitIfNeeded();
	DefaultStyleKey(box_value(resources::Mntone_AngelUmbrella_Controls_SettingsCard));
	DefaultStyleResourceUri(Uri { resources::Mntone_AngelUmbrella_Controls_SettingsCard_Uri });
}

void SettingsCard::OnApplyTemplate() const {
	__super::OnApplyTemplate();

	OnOrientationChanged(Orientation());
	OnDescriptionChanged(Description());
	OnHeaderChanged(Header());
	OnHeaderIconChanged(HeaderIcon());
	OnIsClickEnabledChanged(IsClickEnabled(), false);

	VisualStateManager::GoToState(*this, IsEnabled() ? states::Normal : states::Disabled, false);
	IsEnabledChanged(&SettingsCard::OnIsEnabledChangedStatic); // The listener is the same lifecycle to the object.
}

winrt::Automation::Peers::AutomationPeer SettingsCard::OnCreateAutomationPeer() const {
	return make<Automation::Peers::implementation::SettingsCardAutomationPeer>(*this);
}

void SettingsCard::OnIsEnabledChangedStatic(IInspectable const& sender, DependencyPropertyChangedEventArgs const& args) {
	VisualStateManager::GoToState(
		sender.as<Control>(),
		unbox_value<bool>(args.NewValue()) ? states::Normal : states::Disabled,
		XamlHelpers::IsAnimationsEnabled());
}

void SettingsCard::OnKeyDown(KeyRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnKeyDown(args);
	}
}

void SettingsCard::OnKeyUp(KeyRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnKeyUp(args);
	}
}

void SettingsCard::OnPointerEntered(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerEntered(args);
	}
}

void SettingsCard::OnPointerPressed(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerPressed(args);
	}
}

void SettingsCard::OnPointerReleased(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerReleased(args);
	}
}

void SettingsCard::OnPointerExited(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerExited(args);
	}
}

void SettingsCard::UpdateActionIcon(bool isClickEnabled) const {
	FrameworkElement element { GetTemplateChild(controls::ActionIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(isClickEnabled ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsCard::OnDescriptionChanged(IInspectable const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::Description).try_as<FrameworkElement>() };
	if (element) {
		VisualStateManager::GoToState(*this, ValueHelper<IInspectable>::HasValue(newValue) ? states::HeaderAndDescription : states::HeaderOnly, false);
	}
}

void SettingsCard::OnHeaderIconChanged(IconElement const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::HeaderIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(newValue != nullptr ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsCard::OnHeaderChanged(IInspectable const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::Header).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(ValueHelper<IInspectable>::HasValue(newValue) ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsCard::OnIsClickEnabledChanged(bool newValue, bool useTransitions) const {
	if (newValue) {
		IsTabStop(true);
		UpdateActionIcon(true);
	} else {
		IsTabStop(false);
		VisualStateManager::GoToState(*this, states::Normal, useTransitions); // Force-reset states.
		UpdateActionIcon(false);
	}
}

void SettingsCard::OnOrientationChanged(winrt::Orientation newValue) const {
	if (ValueHelper<IInspectable>::HasValue(Header())) {
		VisualStateManager::GoToState(*this, newValue == Orientation::Vertical ? states::Vertical : states::Horizontal, false);
	} else {
		VisualStateManager::GoToState(*this, states::Vertical, false);
	}
}

void SettingsCard::OnDescriptionChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnDescriptionChanged(args.NewValue());
}

void SettingsCard::OnHeaderIconChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnHeaderIconChanged(args.NewValue().as<IconElement>());
}

void SettingsCard::OnHeaderChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnHeaderChanged(args.NewValue());
}

void SettingsCard::OnIsClickEnabledChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnIsClickEnabledChanged(unbox_value<bool>(args.NewValue()));
}

void SettingsCard::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnOrientationChanged(
		unbox_value<winrt::Orientation>(args.NewValue()));
}
