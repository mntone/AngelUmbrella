#include "pch.h"
#include "XamlHelpers.h"

#include <winrt/Windows.UI.ViewManagement.h>

namespace winrt {
	using namespace ::winrt::Windows::UI::ViewManagement;
}

using namespace winrt::Mntone::AngelUmbrella::Helpers;

bool XamlHelpers::IsAnimationsEnabled() {
	UISettings uiSettings { UISettings() };
	return uiSettings.AnimationsEnabled();
}
