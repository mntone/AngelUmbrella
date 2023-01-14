#include "pch.h"
#include "SettingsPanel.xaml.h"

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsPanel { L"Mntone.AngelUmbrella.Controls.SettingsPanel" };
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsPanel_Uri { L"ms-appx:///Mntone.AngelUmbrella/Controls/SettingsPanel.xaml" };
}

namespace controls {
	constexpr std::wstring_view ActionIcon { L"ActionIcon" };
	constexpr std::wstring_view Description { L"Description" };
	constexpr std::wstring_view HeaderIcon { L"HeaderIcon" };
	constexpr std::wstring_view Header { L"Header" };
}

namespace states {
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
	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsPanel::SettingsPanel() noexcept {
	props_.DelayInitIfNeeded();
	DefaultStyleKey(box_value(resources::Mntone_AngelUmbrella_Controls_SettingsPanel));
	DefaultStyleResourceUri(Uri { resources::Mntone_AngelUmbrella_Controls_SettingsPanel_Uri });
}

void SettingsPanel::OnApplyTemplate() const {
	__super::OnApplyTemplate();

	OnOrientationChanged(Orientation());
	OnDescriptionChanged(Description());
	OnHeaderChanged(Header());
	OnHeaderIconChanged(HeaderIcon());
}

void SettingsPanel::OnButtonIconChanged(bool isClickEnabled) const {
	FrameworkElement element { GetTemplateChild(controls::ActionIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(isClickEnabled ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsPanel::OnDescriptionChanged(IInspectable const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::Description).try_as<FrameworkElement>() };
	if (element) {
		VisualStateManager::GoToState(*this, ValueHelper<IInspectable>::HasValue(newValue) ? states::HeaderAndDescription : states::HeaderOnly, false);
	}
}

void SettingsPanel::OnHeaderIconChanged(IconElement const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::HeaderIcon).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(newValue != nullptr ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsPanel::OnHeaderChanged(IInspectable const& newValue) const {
	FrameworkElement element { GetTemplateChild(controls::Header).try_as<FrameworkElement>() };
	if (element) {
		element.Visibility(ValueHelper<IInspectable>::HasValue(newValue) ? Visibility::Visible : Visibility::Collapsed);
	}
}

void SettingsPanel::OnOrientationChanged(winrt::Orientation newValue) const {
	if (ValueHelper<IInspectable>::HasValue(Header())) {
		VisualStateManager::GoToState(*this, newValue == Orientation::Vertical ? states::Vertical : states::Horizontal, false);
	} else {
		VisualStateManager::GoToState(*this, states::Vertical, false);
	}
}

void SettingsPanel::OnDescriptionChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsPanel>(sender.as<winrt::SettingsPanel>())->OnDescriptionChanged(args.NewValue());
}

void SettingsPanel::OnHeaderIconChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsPanel>(sender.as<winrt::SettingsPanel>())->OnHeaderIconChanged(args.NewValue().as<IconElement>());
}

void SettingsPanel::OnHeaderChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsPanel>(sender.as<winrt::SettingsPanel>())->OnHeaderChanged(args.NewValue());
}

void SettingsPanel::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
	get_self<SettingsPanel>(sender.as<winrt::SettingsPanel>())->OnOrientationChanged(
		unbox_value<winrt::Orientation>(args.NewValue()));
}
