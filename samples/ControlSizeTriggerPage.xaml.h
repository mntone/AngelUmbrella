#pragma once
#include "ControlSizeTriggerPage.g.h"

namespace winrt::Mntone::AngelUmbrella::Samples::implementation {

	struct ControlSizeTriggerPage: ControlSizeTriggerPageT<ControlSizeTriggerPage> {
		ControlSizeTriggerPage();
	};

}

namespace winrt::Mntone::AngelUmbrella::Samples::factory_implementation {

	struct ControlSizeTriggerPage: ControlSizeTriggerPageT<ControlSizeTriggerPage, implementation::ControlSizeTriggerPage> {
	};

}
