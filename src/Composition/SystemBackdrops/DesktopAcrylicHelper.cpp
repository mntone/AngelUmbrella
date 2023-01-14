#include "pch.h"
#include "DesktopAcrylicHelper.h"
#if __has_include("./Composition/SystemBackdrops/DesktopAcrylicHelper.g.cpp")
#include "./Composition/SystemBackdrops/DesktopAcrylicHelper.g.cpp"
#endif

#include <winrt/Windows.UI.ViewManagement.h>

// Asset from https://www.figma.com/community/file/1159947337437047524 (Windows UI 3)
template<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind>
struct DesktopAcrylicColorsResources final: public std::false_type {
	static_assert(!value, "This class has to be implemented for desired type");
};

template<>
struct DesktopAcrylicColorsResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::Light,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Default> final: public std::true_type {
	static constexpr unsigned char BackgroundColorComponent { 0xFC };
	static constexpr unsigned char BorderColorComponent { 0x1F };
	static constexpr unsigned char FallbackColorComponent { 0xF9 };
	static constexpr float LuminosityOpacity { 0.85f };
	static constexpr float TintOpacity { 0.f };
};

template<>
struct DesktopAcrylicColorsResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::Light,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Base> final: public std::true_type {
	static constexpr unsigned char BackgroundColorComponent { 0xF3 };
	static constexpr unsigned char BorderColorComponent { 0x1F };
	static constexpr unsigned char FallbackColorComponent { 0xEE };
	static constexpr float LuminosityOpacity { 0.9f };
	static constexpr float TintOpacity { 0.f };
};

template<>
struct DesktopAcrylicColorsResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::Dark,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Default> final: public std::true_type {
	static constexpr unsigned char BackgroundColorComponent { 0x2C };
	static constexpr unsigned char BorderColorComponent { 0xAA };
	static constexpr unsigned char FallbackColorComponent { 0x2C };
	static constexpr float LuminosityOpacity { 0.96f };
	static constexpr float TintOpacity { 0.15f };
};

template<>
struct DesktopAcrylicColorsResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::Dark,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Base> final: public std::true_type {
	static constexpr unsigned char BackgroundColorComponent { 0x20 };
	static constexpr unsigned char BorderColorComponent { 0xAA };
	static constexpr unsigned char FallbackColorComponent { 0x1C };
	static constexpr float LuminosityOpacity { 0.96f };
	static constexpr float TintOpacity { 0.5f };
};

template<typename Resources>
struct DesktopAcrylicColors final {
	inline void SetColors(::winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController const& controller) {
		constexpr unsigned char backgroundComponent { Resources::BackgroundColorComponent };
		constexpr ::winrt::Windows::UI::Color backgroundColor { 0xFF, backgroundComponent, backgroundComponent, backgroundComponent };
		controller.TintColor(backgroundColor);

		controller.TintOpacity(Resources::TintOpacity);
		controller.LuminosityOpacity(Resources::LuminosityOpacity);

		constexpr unsigned char fallbackComponent { Resources::FallbackColorComponent };
		constexpr ::winrt::Windows::UI::Color fallbackColor { 0xFF, fallbackComponent, fallbackComponent, fallbackComponent };
		controller.FallbackColor(fallbackColor);
	}
};

template<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind>
struct DesktopAcrylicColorsAccentResources final: public std::false_type {
	static_assert(!value, "This class has to be implemented for desired type");
};

template<>
struct DesktopAcrylicColorsAccentResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::AccentLight,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Default> final: public std::true_type {
	static constexpr ::winrt::Windows::UI::ViewManagement::UIColorType ColorType { ::winrt::Windows::UI::ViewManagement::UIColorType::AccentLight3 };
	static constexpr float LuminosityOpacity { 0.9f };
	static constexpr float TintOpacity { 0.8f };
};

template<>
struct DesktopAcrylicColorsAccentResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::AccentLight,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Base> final: public std::true_type {
	static constexpr ::winrt::Windows::UI::ViewManagement::UIColorType ColorType { ::winrt::Windows::UI::ViewManagement::UIColorType::AccentLight3 };
	static constexpr float LuminosityOpacity { 0.8f };
	static constexpr float TintOpacity { 0.8f };
};

template<>
struct DesktopAcrylicColorsAccentResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::AccentDark,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Default> final: public std::true_type {
	static constexpr ::winrt::Windows::UI::ViewManagement::UIColorType ColorType { ::winrt::Windows::UI::ViewManagement::UIColorType::AccentDark1 };
	static constexpr float LuminosityOpacity { 0.8f };
	static constexpr float TintOpacity { 0.8f };
};

template<>
struct DesktopAcrylicColorsAccentResources<
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme::AccentDark,
	::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind::Base> final: public std::true_type {
	static constexpr ::winrt::Windows::UI::ViewManagement::UIColorType ColorType { ::winrt::Windows::UI::ViewManagement::UIColorType::AccentDark2 };
	static constexpr float LuminosityOpacity { 0.8f };
	static constexpr float TintOpacity { 0.8f };
};

template<typename Resources>
struct DesktopAcrylicColorsAccent final {
	inline void SetColors(::winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController const& controller) {
		::winrt::Windows::UI::Color themeColor { uiSettings_.GetColorValue(Resources::ColorType) };
		controller.TintColor(themeColor);
		controller.TintOpacity(Resources::TintOpacity);
		controller.LuminosityOpacity(Resources::LuminosityOpacity);
		controller.FallbackColor(themeColor);
	}

private:
	::winrt::Windows::UI::ViewManagement::UISettings const uiSettings_ { };
};

namespace winrt {
	using namespace ::winrt::Microsoft::UI::Composition::SystemBackdrops;

	using namespace ::winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops;
}

using namespace winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::implementation;

constexpr winrt::DesktopAcrylicTheme ConvertSystemBackdropThemeToDesktopAcrylicTheme(winrt::SystemBackdropTheme const& theme) {
	switch (theme) {
	case winrt::SystemBackdropTheme::Light:
		return winrt::DesktopAcrylicTheme::Light;
	case winrt::SystemBackdropTheme::Dark:
		return winrt::DesktopAcrylicTheme::Dark;
	case winrt::SystemBackdropTheme::Default:
	default:
		return winrt::DesktopAcrylicTheme::Default;
	}
}

void DesktopAcrylicHelper::SetColors(DesktopAcrylicController const& controller, DesktopAcrylicTheme const& theme) {
	switch (theme) {
	case DesktopAcrylicTheme::Light:
		DesktopAcrylicColors<DesktopAcrylicColorsResources<DesktopAcrylicTheme::Light, DesktopAcrylicKind::Default>>().SetColors(controller);
		break;
	case DesktopAcrylicTheme::AccentLight:
		DesktopAcrylicColorsAccent<DesktopAcrylicColorsAccentResources<DesktopAcrylicTheme::AccentLight, DesktopAcrylicKind::Default>>().SetColors(controller);
		break;
	case DesktopAcrylicTheme::AccentDark:
		DesktopAcrylicColorsAccent<DesktopAcrylicColorsAccentResources<DesktopAcrylicTheme::AccentDark, DesktopAcrylicKind::Default>>().SetColors(controller);
		break;
	case DesktopAcrylicTheme::Default:
	case DesktopAcrylicTheme::Dark:
	default:
		DesktopAcrylicColors<DesktopAcrylicColorsResources<DesktopAcrylicTheme::Dark, DesktopAcrylicKind::Default>>().SetColors(controller);
		break;
	}
}

void DesktopAcrylicHelper::SetColors(DesktopAcrylicController const& controller, SystemBackdropTheme const& theme) {
	DesktopAcrylicTheme acrylicTheme { ConvertSystemBackdropThemeToDesktopAcrylicTheme(theme) };
	SetColors(controller, acrylicTheme);
}

void DesktopAcrylicHelper::SetColors(DesktopAcrylicController const& controller, DesktopAcrylicTheme const& theme, DesktopAcrylicKind const& kind) {
	if (DesktopAcrylicKind::Base == kind) {
		switch (theme) {
		case DesktopAcrylicTheme::Light:
			DesktopAcrylicColors<DesktopAcrylicColorsResources<DesktopAcrylicTheme::Light, DesktopAcrylicKind::Base>>().SetColors(controller);
			break;
		case DesktopAcrylicTheme::AccentLight:
			DesktopAcrylicColorsAccent<DesktopAcrylicColorsAccentResources<DesktopAcrylicTheme::AccentLight, DesktopAcrylicKind::Base>>().SetColors(controller);
			break;
		case DesktopAcrylicTheme::AccentDark:
			DesktopAcrylicColorsAccent<DesktopAcrylicColorsAccentResources<DesktopAcrylicTheme::AccentDark, DesktopAcrylicKind::Base>>().SetColors(controller);
			break;
		case DesktopAcrylicTheme::Default:
		case DesktopAcrylicTheme::Dark:
		default:
			DesktopAcrylicColors<DesktopAcrylicColorsResources<DesktopAcrylicTheme::Dark, DesktopAcrylicKind::Base>>().SetColors(controller);
			break;
		}
	} else {
		SetColors(controller, theme);
	}
}

void DesktopAcrylicHelper::SetColors(DesktopAcrylicController const& controller, SystemBackdropTheme const& theme, DesktopAcrylicKind const& kind) {
	DesktopAcrylicTheme acrylicTheme { ConvertSystemBackdropThemeToDesktopAcrylicTheme(theme) };
	SetColors(controller, acrylicTheme, kind);
}
