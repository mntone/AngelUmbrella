#include "pch.h"
#include "NavigationProperties.h"
#if __has_include("./Navigation/NavigationProperties.g.cpp")
#include "./Navigation/NavigationProperties.g.cpp"
#endif

#define DELAY_INIT_DP // Delay Init
#include "Helpers/DependencyPropertyHelper.h"

namespace projection { // Need to build
	using namespace ::winrt::Mntone::AngelUmbrella::Navigation;
}

using namespace ::winrt::Mntone::AngelUmbrella::Navigation::implementation;

NavigationProperties::DependencyProperties NavigationProperties::props_;

void NavigationProperties::DependencyProperties::DelayInitIfNeeded() {
	if (initialized_) return;

	DEFINE_PARENT_TYPENAME(NavigationProperties);

	DEFINE_DP(
		PageType,
		Windows::UI::Xaml::Interop::TypeName,
		NavigationProperties);

	DEFINE_DP(
		Parameter,
		Windows::Foundation::IInspectable,
		NavigationProperties);

	DEFINE_DP(
		TransitionInfo,
		Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo,
		NavigationProperties);

	initialized_ = true;
}
