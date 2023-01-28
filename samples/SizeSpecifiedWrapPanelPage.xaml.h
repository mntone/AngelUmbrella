#pragma once
#include "SizeSpecifiedWrapPanelPage.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct SizeSpecifiedWrapPanelPage: SizeSpecifiedWrapPanelPageT<SizeSpecifiedWrapPanelPage> {
		SizeSpecifiedWrapPanelPage();
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {

	struct SizeSpecifiedWrapPanelPage: SizeSpecifiedWrapPanelPageT<SizeSpecifiedWrapPanelPage, implementation::SizeSpecifiedWrapPanelPage> {
	};

}
