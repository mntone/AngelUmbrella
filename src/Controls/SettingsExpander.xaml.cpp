#include "pch.h"
#include "SettingsExpander.xaml.h"

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsExpander { L"Mntone.AngelUmbrella.Controls.SettingsExpander" };
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsExpander_Uri { L"ms-appx:///Mntone.AngelUmbrella/Controls/SettingsExpander.xaml" };
}

namespace controls {
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

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Input;

	using namespace ::winrt::Mntone::AngelUmbrella::Helpers;
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsExpander::SettingsExpander() noexcept {
	props_.DelayInitIfNeeded();
	DefaultStyleKey(box_value(resources::Mntone_AngelUmbrella_Controls_SettingsExpander));
	DefaultStyleResourceUri(Uri { resources::Mntone_AngelUmbrella_Controls_SettingsExpander_Uri });
}

void SettingsExpander::OnApplyTemplate() const {
	__super::OnApplyTemplate();

	OnOrientationChanged(Orientation());
	OnDescriptionChanged(Description());
	OnHeaderIconChanged(HeaderIcon());

	VisualStateManager::GoToState(*this, IsEnabled() ? states::Normal : states::Disabled, false);
	IsEnabledChanged(&SettingsExpander::OnIsEnabledChangedStatic); // The listener is the same lifecycle to the object.
}

void SettingsExpander::OnIsEnabledChangedStatic(IInspectable const& sender, DependencyPropertyChangedEventArgs const& args) {
	VisualStateManager::GoToState(
		sender.as<Control>(),
		unbox_value<bool>(args.NewValue()) ? states::Normal : states::Disabled,
		XamlHelpers::IsAnimationsEnabled());
}

void SettingsExpander::OnPointerEntered(PointerRoutedEventArgs const& args) const {
	__super::OnPointerEntered(args);

	VisualStateManager::GoToState(*this, states::PointerOver, XamlHelpers::IsAnimationsEnabled());
}

void SettingsExpander::OnPointerExited(PointerRoutedEventArgs const& args) const {
	__super::OnPointerExited(args);

	VisualStateManager::GoToState(*this, states::Normal, XamlHelpers::IsAnimationsEnabled());
}

void SettingsExpander::OnDescriptionChanged(IInspectable const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::Description).try_as<FrameworkElement>() };
	if (element) {
		VisualStateManager::GoToState(*this, ValueHelper<IInspectable>::HasValue(newValue) ? states::HeaderAndDescription : states::HeaderOnly, false);
	}
}

void SettingsExpander::OnHeaderIconChanged(IconElement const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::HeaderIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(ValueHelper<IInspectable>::HasValue(newValue) ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsExpander::OnOrientationChanged(winrt::Orientation newValue) const {
	if (ValueHelper<IInspectable>::HasValue(Header())) {
		VisualStateManager::GoToState(*this, newValue == Orientation::Vertical ? states::Vertical : states::Horizontal, false);
	} else {
		VisualStateManager::GoToState(*this, states::Vertical, false);
	}
}

void SettingsExpander::OnDescriptionChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsExpander>(sender.as<winrt::SettingsExpander>())->OnDescriptionChanged(args.NewValue());
}

void SettingsExpander::OnHeaderIconChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsExpander>(sender.as<winrt::SettingsExpander>())->OnHeaderIconChanged(args.NewValue().as<IconElement>());
}

void SettingsExpander::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsExpander>(sender.as<winrt::SettingsExpander>())->OnOrientationChanged(
		unbox_value<winrt::Orientation>(args.NewValue()));
}
