#pragma once
#include "SettingsWindow.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct SettingsWindow: SettingsWindowT<SettingsWindow> {
		SettingsWindow();

		void NavigationViewSelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

		void NavigationViewDisplayModeChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewDisplayModeChangedEventArgs const& args);
		void NavigationViewPaneClosing(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewPaneClosingEventArgs const& args);
		void NavigationViewPaneOpening(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Windows::Foundation::IInspectable const& args);

	private:
		bool TryGoBack();
		bool TryGoForward();
		void UpdateTitlebarMargin(Microsoft::UI::Xaml::Controls::NavigationView const& navigationView);

	public:  // - Callbacks
		void OnPointerPressed(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnKeyboardBackRequested(Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args);
		void OnKeyboardForwardRequested(Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args);

	protected:
		LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

	private:
		void OnTitleBarBackRequested(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewBackRequestedEventArgs const& args);
		void OnCanGoBackChanged(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyProperty const& property);
		//void OnSystemBackRequested(Windows::Foundation::IInspectable const& sender, Windows::UI::Core::BackRequestedEventArgs const& args);

		static LRESULT WndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

	private:
		

	private: // - Variables
		WNDPROC nextWndProc_;
		//Windows::UI::Core::SystemNavigationManager::BackRequested_revoker backRequestedRevoker_;
	};

}

//namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {
//
//	struct SettingsWindow: SettingsWindowT<SettingsWindow, implementation::SettingsWindow> {
//	};
//
//}
