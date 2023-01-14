#include "pch.h"
#include "DesktopAcrylicWindow.xaml.h"
#if __has_include("DesktopAcrylicWindow.g.cpp")
#include "DesktopAcrylicWindow.g.cpp"
#endif

#include "winrt/Mntone.AngelUmbrella.Composition.SystemBackdrops.h"

#pragma region DispatcherQueueSupport

#include <DispatcherQueue.h>

class DispatcherQueueSupport final {
public:
	static void EnsureDispatcherQueueController() {
		if (nullptr != dispatcherQueueController_) return;

		DispatcherQueueOptions options {
			sizeof(DispatcherQueueOptions),
			DQTYPE_THREAD_CURRENT,
			DQTAT_COM_NONE,
		};

		ABI::Windows::System::IDispatcherQueueController* dispatchQueueController { nullptr };
		winrt::check_hresult(CreateDispatcherQueueController(options, &dispatchQueueController));
		dispatcherQueueController_ = { dispatchQueueController, winrt::take_ownership_from_abi };
	}

private:
	static winrt::Windows::Foundation::IInspectable dispatcherQueueController_;
};

winrt::Windows::Foundation::IInspectable DispatcherQueueSupport::dispatcherQueueController_ { nullptr };

#pragma endregion

namespace winrt {
	using namespace ::winrt::Windows::Foundation;

	using namespace ::winrt::Microsoft::UI::Composition;
	using namespace ::winrt::Microsoft::UI::Composition::SystemBackdrops;
	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Data;

	using namespace ::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

#pragma region Converters

constexpr winrt::DesktopAcrylicTheme GetBaseTheme(winrt::DesktopAcrylicTheme const& theme) {
	switch (theme) {
	case winrt::DesktopAcrylicTheme::Light:
	case winrt::DesktopAcrylicTheme::AccentLight:
		return winrt::DesktopAcrylicTheme::Light;
	case winrt::DesktopAcrylicTheme::Dark:
	case winrt::DesktopAcrylicTheme::AccentDark:
		return winrt::DesktopAcrylicTheme::Dark;
	case winrt::DesktopAcrylicTheme::Default:
	default:
		return winrt::DesktopAcrylicTheme::Default;
	}
}

constexpr winrt::ElementTheme ConvertDesktopAcrylicThemeToElementTheme(winrt::DesktopAcrylicTheme const& theme) {
	switch (theme) {
	case winrt::DesktopAcrylicTheme::Light:
	case winrt::DesktopAcrylicTheme::AccentLight:
		return winrt::ElementTheme::Light;
	case winrt::DesktopAcrylicTheme::Dark:
	case winrt::DesktopAcrylicTheme::AccentDark:
		return winrt::ElementTheme::Dark;
	case winrt::DesktopAcrylicTheme::Default:
	default:
		return winrt::ElementTheme::Default;
	}
}

constexpr winrt::DesktopAcrylicTheme ConvertElementThemeToDesktopAcrylicTheme(winrt::ElementTheme const& theme) {
	switch (theme) {
	case winrt::ElementTheme::Light:
		return winrt::DesktopAcrylicTheme::Light;
	case winrt::ElementTheme::Dark:
		return winrt::DesktopAcrylicTheme::Dark;
	case winrt::ElementTheme::Default:
	default:
		return winrt::DesktopAcrylicTheme::Default;
	}
}

constexpr winrt::SystemBackdropTheme ConvertElementThemeToSystemBackdropTheme(winrt::ElementTheme const& theme) {
	switch (theme) {
	case winrt::ElementTheme::Light:
		return winrt::SystemBackdropTheme::Light;
	case winrt::ElementTheme::Dark:
		return winrt::SystemBackdropTheme::Dark;
	case winrt::ElementTheme::Default:
	default:
		return winrt::SystemBackdropTheme::Default;
	}
}

#pragma endregion

DesktopAcrylicWindow::DesktopAcrylicWindow()
	: activatedRevoker_()
	, backdropConfiguration_(nullptr)
	, backdropController_(nullptr)
	, theme_(DesktopAcrylicTheme::Default)
	, kind_(DesktopAcrylicKind::Default)
	, syncActiveState_(true)
	, propertyChanged_() {
	InitializeComponent();
	WINRT_ASSERT(DesktopAcrylicController::IsSupported());
	DispatcherQueueSupport::EnsureDispatcherQueueController(); // Note: It's required by backdrop effect.

	SystemBackdropConfiguration configuration { SystemBackdropConfiguration() };
	configuration.IsInputActive(true);
	backdropConfiguration_ = configuration;

	activatedRevoker_ = Activated(auto_revoke, { this, &DesktopAcrylicWindow::OnWindowActivated });
	Closed({ this, &DesktopAcrylicWindow::OnWindowClosed }); // The listener is the same lifecycle to the object.

	DesktopAcrylicController controller { DesktopAcrylicController() };
	controller.SetSystemBackdropConfiguration(configuration);
	controller.AddSystemBackdropTarget(m_inner.as<winrt::ICompositionSupportsSystemBackdrop>());
	backdropController_ = controller;

	FrameworkElement rootElement { Content().as<FrameworkElement>() };
	switch (rootElement.ActualTheme()) {
	case ElementTheme::Light:
		DesktopAcrylicHelper::SetColors(backdropController_, DesktopAcrylicTheme::Light);
		break;
	case ElementTheme::Default:
	case ElementTheme::Dark:
	default:
		DesktopAcrylicHelper::SetColors(backdropController_, DesktopAcrylicTheme::Dark);
		break;
	}
	rootElement.ActualThemeChanged({ this, &DesktopAcrylicWindow::OnContentThemeChanged }); // The listener is the same lifecycle to the object.
}

void DesktopAcrylicWindow::UpdateDesktopAcrylicColors(bool changeBaseTheme, FrameworkElement const& element) const {
	FrameworkElement rootElement { nullptr != element ? element : Content().as<FrameworkElement>() };
	if (changeBaseTheme) {
		ElementTheme baseTheme { ConvertDesktopAcrylicThemeToElementTheme(theme_) };
		rootElement.RequestedTheme(baseTheme);

		SystemBackdropTheme backdropTheme { ConvertElementThemeToSystemBackdropTheme(baseTheme) };
		backdropConfiguration_.Theme(backdropTheme);
	}

	DesktopAcrylicTheme realTheme { DesktopAcrylicTheme::Default == theme_
		? ConvertElementThemeToDesktopAcrylicTheme(rootElement.ActualTheme())
		: theme_ };
	DesktopAcrylicHelper::SetColors(backdropController_, realTheme, kind_);
}

void DesktopAcrylicWindow::OnWindowActivated(IInspectable const& /*sender*/, WindowActivatedEventArgs const& args) const {
	if (syncActiveState_) {
		backdropConfiguration_.IsInputActive(WindowActivationState::Deactivated != args.WindowActivationState());
	}
}

void DesktopAcrylicWindow::OnWindowClosed(IInspectable const& /*sender*/, WindowEventArgs const& /*args*/) {
	activatedRevoker_.revoke();
	backdropController_ = nullptr;
	backdropConfiguration_ = nullptr;
}

void DesktopAcrylicWindow::OnContentThemeChanged(FrameworkElement const& sender, IInspectable const& /*args*/) const {
	UpdateDesktopAcrylicColors(true, sender);
}

void DesktopAcrylicWindow::Theme(int value) noexcept {
	DesktopAcrylicTheme castedValue { static_cast<DesktopAcrylicTheme>(value) };
	if (theme_ != castedValue) {
		bool changeBaseTheme { GetBaseTheme(theme_) != GetBaseTheme(castedValue) };
		theme_ = castedValue;
		propertyChanged_(*this, PropertyChangedEventArgs { L"Theme" });

		UpdateDesktopAcrylicColors(changeBaseTheme);
	}
}

void DesktopAcrylicWindow::Kind(int value) noexcept {
	DesktopAcrylicKind castedValue { static_cast<DesktopAcrylicKind>(value) };
	if (kind_ != castedValue) {
		kind_ = castedValue;
		propertyChanged_(*this, PropertyChangedEventArgs { L"Kind" });

		UpdateDesktopAcrylicColors(false);
	}
}

void DesktopAcrylicWindow::SyncActiveState(bool value) noexcept {
	if (syncActiveState_ != value) {
		syncActiveState_ = value;
		propertyChanged_(*this, PropertyChangedEventArgs { L"SyncActiveState" });
	}
}
