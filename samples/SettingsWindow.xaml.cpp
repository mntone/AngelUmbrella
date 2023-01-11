#include "pch.h"
#include "SettingsWindow.xaml.h"
#if __has_include("SettingsWindow.g.cpp")
#include "SettingsWindow.g.cpp"
#endif

#include <microsoft.ui.xaml.window.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>

#include "SettingsWindow_RootPage.xaml.h"

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_Samples_ClassPointer = L"Mntone.AngelUmbrella.Samples.ClassPointer";
}

namespace winrt {
	using namespace ::winrt::Windows::Foundation::Collections;
	using namespace ::winrt::Windows::Globalization;
	using namespace ::winrt::Windows::System;
	using namespace ::winrt::Windows::UI::Core;

	using namespace ::winrt::Microsoft::UI;
	using namespace ::winrt::Microsoft::UI::Input;
	using namespace ::winrt::Microsoft::UI::Windowing;
	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Input;
	using namespace ::winrt::Microsoft::UI::Xaml::Media::Animation;

	using namespace ::winrt::Mntone::AngelUmbrella::Samples;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

SettingsWindow::SettingsWindow() {
	InitializeComponent();

	// Subclassing
	HWND hWnd { nullptr };
	winrt::impl::com_ref<IWindowNative> windowNative { m_inner.as<IWindowNative>() };
	check_hresult(windowNative->get_WindowHandle(&hWnd));
	check_bool(SetPropW(hWnd, resources::Mntone_AngelUmbrella_Samples_ClassPointer.data(), this));
	LONG_PTR nextWndProc = SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&SettingsWindow::WndProcStatic));
	check_bool(nextWndProc);
	nextWndProc_ = reinterpret_cast<WNDPROC>(nextWndProc);

	// Init the titlebar
	ExtendsContentIntoTitleBar(true);
	SetTitleBar(titlebar());

	// Init the frame
	Frame frame { rootFrame() };
	WINRT_ASSERT(frame);
	WINRT_ASSERT(!frame.Content());

	IVectorView<hstring> languages { ApplicationLanguages::Languages() };
	frame.Language(languages.GetAt(0));
	frame.RegisterPropertyChangedCallback(Frame::CanGoBackProperty(), { this, &SettingsWindow::OnCanGoBackChanged });
	frame.CacheSize(2);

	// Init the navview
	NavigationView navigationView { this->navigationView() };
	navigationView.BackRequested({ this, &SettingsWindow::OnTitleBarBackRequested });
	navigationView.SelectedItem(navigationView.MenuItems().GetAt(0));

	// Note: WinUI 3 isn't working: https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/desktop-to-uwp-supported-api
	//backRequestedRevoker_ = SystemNavigationManager::GetForCurrentView().BackRequested(auto_revoke, { this, &SettingsWindow::OnSystemBackRequested });

	// Navigate
	frame.Navigate(xaml_typename<winrt::SettingsWindow_RootPage>(), nullptr, SuppressNavigationTransitionInfo());
}

void SettingsWindow::OnPointerPressed(IInspectable const& sender, PointerRoutedEventArgs const& args) {
	// Instead of event CoreWindow.PointerPressed
	PointerPointProperties properties { args.GetCurrentPoint(Content()).Properties() };
	if (properties.IsXButton1Pressed()) {
		if (TryGoBack()) {
			args.Handled(true);
		}
	} else if (properties.IsXButton2Pressed()) {
		if (TryGoForward()) {
			args.Handled(true);
		}
	}
}

void SettingsWindow::OnKeyboardBackRequested(KeyboardAccelerator const& /*sender*/, KeyboardAcceleratorInvokedEventArgs const& args) {
	if (args.Handled() || !TryGoBack()) return;
	args.Handled(true);
}

void SettingsWindow::OnKeyboardForwardRequested(KeyboardAccelerator const& /*sender*/, KeyboardAcceleratorInvokedEventArgs const& args) {
	if (args.Handled() || !TryGoForward()) return;
	args.Handled(true);
}

void SettingsWindow::OnTitleBarBackRequested(NavigationView const& /*sender*/, NavigationViewBackRequestedEventArgs const& /*args*/) {
	TryGoBack();
}

void SettingsWindow::OnCanGoBackChanged(Microsoft::UI::Xaml::DependencyObject const& sender, Microsoft::UI::Xaml::DependencyProperty const& property) {
	navigationView().IsBackEnabled(unbox_value<bool>(sender.GetValue(property)));
}

//void SettingsWindow::OnSystemBackRequested(IInspectable const& sender, BackRequestedEventArgs const& args) {
//	if (args.Handled() || !TryGoBack()) return;
//	args.Handled(true);
//}

bool SettingsWindow::TryGoBack() {
	Frame frame { rootFrame() };
	if (frame.CanGoBack()) {
		frame.GoBack();
		return true;
	}
	return false;
}

bool SettingsWindow::TryGoForward() {
	Frame frame { rootFrame() };
	if (frame.CanGoForward()) {
		frame.GoForward();
		return true;
	}
	return false;
}

LRESULT SettingsWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept {
	if (WM_GETMINMAXINFO == message) {
		MINMAXINFO& minmaxInfo { *reinterpret_cast<MINMAXINFO*>(lParam) };
		minmaxInfo.ptMinTrackSize.x = 360;
		minmaxInfo.ptMinTrackSize.y = 270;
		return FALSE;
	}
	return CallWindowProcW(nextWndProc_, hWnd, message, wParam, lParam);
}

LRESULT SettingsWindow::WndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept {
	SettingsWindow* that { static_cast<SettingsWindow*>(GetPropW(hWnd, resources::Mntone_AngelUmbrella_Samples_ClassPointer.data())) };
	if (that) {
		return that->WndProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}

void SettingsWindow::NavigationViewDisplayModeChanged(NavigationView const& sender, NavigationViewDisplayModeChangedEventArgs const& /*args*/) {
	Border titlebar { this->titlebar() };
	Thickness margin { titlebar.Margin() };
	if (NavigationViewDisplayMode::Minimal == sender.DisplayMode()) {
		margin.Left = 2.0 * sender.CompactPaneLength();
		navigationView().IsPaneToggleButtonVisible(true);
	} else {
		margin.Left = sender.CompactPaneLength();
		navigationView().IsPaneToggleButtonVisible(false);
	}
	titlebar.Margin(std::move(margin));

	UpdateTitlebarMargin(sender);
}

void SettingsWindow::NavigationViewPaneClosing(NavigationView const& sender, NavigationViewPaneClosingEventArgs const& /*args*/) {
	UpdateTitlebarMargin(sender);
}

void SettingsWindow::NavigationViewPaneOpening(NavigationView const& sender, IInspectable const& /*args*/) {
	UpdateTitlebarMargin(sender);
}

constexpr int smallLeftIndent = 4;
constexpr int largeLeftIndent = 24;

void SettingsWindow::UpdateTitlebarMargin(NavigationView const& navigationView) {
	TextBlock caption { this->caption() };
	caption.TranslationTransition(Vector3Transition());

	NavigationViewDisplayMode displayMode { navigationView.DisplayMode() };
	if (NavigationViewDisplayMode::Expanded == displayMode && navigationView.IsPaneOpen()
		|| NavigationViewDisplayMode::Minimal == displayMode) {
		caption.Translation({ smallLeftIndent, 0, 0 });
	} else {
		caption.Translation({ largeLeftIndent, 0, 0 });
	}
}
