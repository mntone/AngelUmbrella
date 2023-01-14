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
	constexpr std::wstring_view Content { L"Content" };
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

SettingsCard::SettingsCard() noexcept: loaded_(false) {
	props_.DelayInitIfNeeded();
	DefaultStyleKey(box_value(resources::Mntone_AngelUmbrella_Controls_SettingsCard));
	DefaultStyleResourceUri(Uri { resources::Mntone_AngelUmbrella_Controls_SettingsCard_Uri });
}

void SettingsCard::OnApplyTemplate() {
	__super::OnApplyTemplate();

	OnOrientationChanged(Orientation());
	OnDescriptionChanged(Description());
	OnHeaderChanged(IInspectable { nullptr }, Header());
	OnHeaderIconChanged(HeaderIcon());
	OnIsClickEnabledChanged(IsClickEnabled(), false);

	VisualStateManager::GoToState(*this, IsEnabled() ? states::Normal : states::Disabled, false);
	IsEnabledChanged(&SettingsCard::OnIsEnabledChangedStatic); // The listener is the same lifecycle to the object.
	loaded_ = true;
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

		switch (args.Key()) {
		case VirtualKey::Enter:
		case VirtualKey::Space:
		case VirtualKey::GamepadA:
			VisualStateManager::GoToState(*this, states::Pressed, XamlHelpers::IsAnimationsEnabled());
			break;
		}
	}
}

void SettingsCard::OnKeyUp(KeyRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnKeyUp(args);
		switch (args.Key()) {
		case VirtualKey::Enter:
		case VirtualKey::Space:
		case VirtualKey::GamepadA:
			VisualStateManager::GoToState(*this, states::Normal, XamlHelpers::IsAnimationsEnabled());
			break;
		}
	}
}

void SettingsCard::OnPointerEntered(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerEntered(args);

		VisualStateManager::GoToState(*this, states::PointerOver, XamlHelpers::IsAnimationsEnabled());
	}
}

void SettingsCard::OnPointerPressed(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerPressed(args);

		VisualStateManager::GoToState(*this, states::Pressed, XamlHelpers::IsAnimationsEnabled());
	}
}

void SettingsCard::OnPointerReleased(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerReleased(args);

		winrt::SettingsCard proj { *this };
		winrt::Windows::Foundation::Numerics::float2 point { args.GetCurrentPoint(proj).Position() };
		if (point.x < 0 || point.y < 0 || point.x > ActualWidth() || point.y > ActualHeight()) {
			VisualStateManager::GoToState(proj, states::Normal, XamlHelpers::IsAnimationsEnabled());
		} else {
			VisualStateManager::GoToState(proj, states::PointerOver, XamlHelpers::IsAnimationsEnabled());
		}
	}
}

void SettingsCard::OnPointerExited(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerExited(args);

		VisualStateManager::GoToState(*this, states::Normal, XamlHelpers::IsAnimationsEnabled());
	}
}

void SettingsCard::ClearContentAutomation() const {
	FrameworkElement element { GetTemplateChild(controls::Content).try_as<FrameworkElement>() };
	if (element) {
		ClearValue(AutomationProperties::NameProperty());
		ClearValue(AutomationProperties::HelpTextProperty());
	}
}

void SettingsCard::UpdateContentAutomation() const {
	FrameworkElement element { GetTemplateChild(controls::Content).try_as<FrameworkElement>() };
	if (element) {
		std::optional<hstring> header { Header().try_as<hstring>() };
		if (header && !header.value().empty()) {
			AutomationProperties::SetName(*this, header.value());

			std::optional<hstring> description { Description().try_as<hstring>() };
			if (description.has_value() && !description.value().empty()) {
				AutomationProperties::SetHelpText(*this, description.value());
			}
		}
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
		if (nullptr != newValue) {
			VisualStateManager::GoToState(*this, states::HeaderAndDescription, false);

			std::optional<hstring> description { newValue.try_as<hstring>() };
			if (description && !description.value().empty()) {
				//AutomationProperties::SetHelpText(*this, description.value());
			} else {
				//ClearValue(AutomationProperties::HelpTextProperty());
			}
		} else {
			VisualStateManager::GoToState(*this, states::HeaderOnly, false);
			//ClearValue(AutomationProperties::HelpTextProperty());
		}
	}
}

void SettingsCard::OnHeaderIconChanged(IconElement const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::HeaderIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(newValue != nullptr ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsCard::OnHeaderChanged(IInspectable const& oldValue, IInspectable const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::Header).try_as<FrameworkElement>() };
	if (element) {
		if (nullptr != newValue) {
			element.Visibility(Visibility::Visible);

			std::optional<hstring> header { newValue.try_as<hstring>() };
			if (header && !header.value().empty()) {
				//AutomationProperties::SetName(*this, header.value());
			} else {
				//ClearValue(AutomationProperties::NameProperty());
			}
		} else {
			element.Visibility(Visibility::Collapsed);
			//ClearValue(AutomationProperties::NameProperty());
		}
	}

	//if (loaded_) {
	//	if (auto peer = FrameworkElementAutomationPeer::FromElement(*this)) {
	//		// Compare detail
	//		peer.RaisePropertyChangedEvent(AutomationElementIdentifiers::NameProperty(), oldValue, newValue);
	//	}
	//}
}

void SettingsCard::OnIsClickEnabledChanged(bool newValue, bool useTransitions) const {
	if (newValue) {
		IsTabStop(true);
		//UpdateContentAutomation();
		UpdateActionIcon(true);
	} else {
		IsTabStop(false);
		//ClearContentAutomation();
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
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnHeaderChanged(args.OldValue(), args.NewValue());
}

void SettingsCard::OnIsClickEnabledChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnIsClickEnabledChanged(unbox_value<bool>(args.NewValue()));
}

void SettingsCard::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnOrientationChanged(
		unbox_value<winrt::Orientation>(args.NewValue()));
}
