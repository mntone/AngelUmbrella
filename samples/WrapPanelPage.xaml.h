#pragma once
#include "WrapPanelPage.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct WrapPanelPage: WrapPanelPageT<WrapPanelPage> {
		WrapPanelPage();
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {

	struct WrapPanelPage: WrapPanelPageT<WrapPanelPage, implementation::WrapPanelPage> {
	};

}
