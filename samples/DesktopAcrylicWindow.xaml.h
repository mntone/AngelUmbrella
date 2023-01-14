#pragma once
#include "DesktopAcrylicWindow.g.h"

#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/impl/Mntone.AngelUmbrella.Composition.SystemBackdrops.0.h>

namespace winrt::Mntone::AngelUmbrella::Samples::implementation
{
    struct DesktopAcrylicWindow : DesktopAcrylicWindowT<DesktopAcrylicWindow>
    {
        DesktopAcrylicWindow();

	private:
		void UpdateDesktopAcrylicColors(bool changeBaseTheme, winrt::Microsoft::UI::Xaml::FrameworkElement const& element = nullptr) const;

		void OnWindowActivated(
			Windows::Foundation::IInspectable const& sender,
			Microsoft::UI::Xaml::WindowActivatedEventArgs const& args) const;
		void OnWindowClosed(
			Windows::Foundation::IInspectable const& sender,
			Microsoft::UI::Xaml::WindowEventArgs const& args);
		void OnContentThemeChanged(
			winrt::Microsoft::UI::Xaml::FrameworkElement const& sender,
			winrt::Windows::Foundation::IInspectable const& args) const;

	public:  // - Properties
		int Theme() const noexcept {
			return static_cast<int>(theme_);
		}
		void Theme(int value) noexcept;

		int Kind() const noexcept {
			return static_cast<int>(kind_);
		}
		void Kind(int value) noexcept;

		bool SyncActiveState() const noexcept {
			return syncActiveState_;
		}
		void SyncActiveState(bool value) noexcept;

		event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
			return propertyChanged_.add(handler);
		}
		void PropertyChanged(event_token const& token) {
			propertyChanged_.remove(token);
		}

	private:
		winrt::Microsoft::UI::Xaml::Window::Activated_revoker activatedRevoker_;
		Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration backdropConfiguration_;
		Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController backdropController_;

		Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme theme_;
		Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind kind_;
		bool syncActiveState_;
		event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;
    };
}
