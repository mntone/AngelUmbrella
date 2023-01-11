#include "pch.h"
#include "SettingsCard.xaml.h"

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_UI_Controls_SettingsCard { L"Mntone.AngelUmbrella.UI.Controls.SettingsCard" };
	constexpr std::wstring_view Mntone_AngelUmbrella_UI_Controls_SettingsCard_Uri { L"ms-appx:///Mntone.AngelUmbrella/UI/Controls/SettingsCard.xaml" };
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
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Input;

	using namespace ::winrt::Mntone::AngelUmbrella::Helpers;
	using namespace ::winrt::Mntone::AngelUmbrella::UI::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::UI::Controls::implementation;

SettingsCard::SettingsCard() noexcept {
	props_.DelayInitIfNeeded();
	DefaultStyleKey(box_value(resources::Mntone_AngelUmbrella_UI_Controls_SettingsCard));
	DefaultStyleResourceUri(Uri { resources::Mntone_AngelUmbrella_UI_Controls_SettingsCard_Uri });
}

void SettingsCard::OnApplyTemplate() {
	__super::OnApplyTemplate();

	OnOrientationChanged(Orientation());
	OnDescriptionChanged(Description());
	OnHeaderChanged(Header());
	OnHeaderIconChanged(HeaderIcon());
	OnIsClickEnabledChanged(IsClickEnabled());
	VisualStateManager::GoToState(*this, IsEnabled() ? states::Normal : states::Disabled, true);
	IsEnabledChanged(&SettingsCard::OnIsEnabledChangedStatic); // The listener is the same lifecycle to the object.
}

void SettingsCard::OnIsEnabledChangedStatic(IInspectable const& sender, DependencyPropertyChangedEventArgs const& args) {
	VisualStateManager::GoToState(sender.as<Control>(), unbox_value<bool>(args.NewValue()) ? states::Normal : states::Disabled, true);
}

void SettingsCard::OnKeyDown(KeyRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnKeyDown(args);

		switch (args.Key()) {
		case VirtualKey::Enter:
		case VirtualKey::Space:
		case VirtualKey::GamepadA:
			VisualStateManager::GoToState(*this, states::Pressed, true);
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
			VisualStateManager::GoToState(*this, states::Normal, true);
			break;
		}
	}
}

void SettingsCard::OnPointerEntered(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerEntered(args);

		VisualStateManager::GoToState(*this, states::PointerOver, true);
	}
}

void SettingsCard::OnPointerPressed(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerPressed(args);

		VisualStateManager::GoToState(*this, states::Pressed, true);
	}
}

void SettingsCard::OnPointerReleased(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerReleased(args);

		winrt::SettingsCard proj { *this };
		winrt::Windows::Foundation::Numerics::float2 point { args.GetCurrentPoint(proj).Position() };
		if (point.x < 0 || point.y < 0 || point.x > ActualWidth() || point.y > ActualHeight()) {
			VisualStateManager::GoToState(proj, states::Normal, true);
		} else {
			VisualStateManager::GoToState(proj, states::PointerOver, true);
		}
	}
}

void SettingsCard::OnPointerExited(PointerRoutedEventArgs const& args) const {
	if (IsClickEnabled()) {
		__super::OnPointerExited(args);

		VisualStateManager::GoToState(*this, states::Normal, true);
	}
}

void SettingsCard::OnButtonIconChanged(bool isClickEnabled) {
	FrameworkElement element { GetTemplateChild(controls::ActionIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(isClickEnabled ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsCard::OnDescriptionChanged(IInspectable const& newValue) {
	FrameworkElement element { GetTemplateChild(controls::Description).try_as<FrameworkElement>() };
	if (element) {
		if (ValueHelper<IInspectable>::HasValue(newValue)) {
			element.Visibility(Visibility::Visible);
			VisualStateManager::GoToState(*this, states::HeaderAndDescription, true);
		} else {
			element.Visibility(Visibility::Collapsed);
			VisualStateManager::GoToState(*this, states::HeaderOnly, true);
		}
	}
}

void SettingsCard::OnHeaderIconChanged(IconElement const& newValue) {
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

void SettingsCard::OnIsClickEnabledChanged(bool newValue) {
	if (newValue) {
		IsTabStop(true);
		OnButtonIconChanged(true);
	} else {
		IsTabStop(false);
		VisualStateManager::GoToState(*this, states::Normal, true); // Force-reset states.
		OnButtonIconChanged(false);
	}
}

void SettingsCard::OnOrientationChanged(winrt::Orientation newValue) {
	if (ValueHelper<IInspectable>::HasValue(Header())) {
		VisualStateManager::GoToState(*this, newValue == Orientation::Vertical ? states::Vertical : states::Horizontal, true);
	} else {
		VisualStateManager::GoToState(*this, states::Vertical, true);
	}
}

void SettingsCard::OnDescriptionChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnDescriptionChanged(args.NewValue());
}

void SettingsCard::OnHeaderIconChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnHeaderIconChanged(
		args.NewValue().as<Microsoft::UI::Xaml::Controls::IconElement>());
}

void SettingsCard::OnHeaderChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnHeaderChanged(args.NewValue());
}

void SettingsCard::OnIsClickEnabledChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnIsClickEnabledChanged(
		winrt::unbox_value<bool>(args.NewValue()));
}

void SettingsCard::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsCard>(sender.as<winrt::SettingsCard>())->OnOrientationChanged(
		winrt::unbox_value<winrt::Orientation>(args.NewValue()));
}
