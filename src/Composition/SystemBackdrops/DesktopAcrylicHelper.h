#pragma once
#include "Composition/SystemBackdrops/DesktopAcrylicHelper.g.h"

#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

namespace winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::implementation {

	struct DesktopAcrylicHelper final {
		static void SetColors(
			Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController const& controller,
			Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme const& theme);

		static void SetColors(
			Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController const& controller,
			Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme const& theme);

		static void SetColors(
			Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController const& controller,
			Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicTheme const& theme,
			Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind const& kind);

		static void SetColors(
			Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController const& controller,
			Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme const& theme,
			Mntone::AngelUmbrella::Composition::SystemBackdrops::DesktopAcrylicKind const& kind);
	};

}

namespace winrt::Mntone::AngelUmbrella::Composition::SystemBackdrops::factory_implementation {

	struct DesktopAcrylicHelper: DesktopAcrylicHelperT<DesktopAcrylicHelper, implementation::DesktopAcrylicHelper> {
	};

}
