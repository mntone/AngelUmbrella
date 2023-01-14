#include "pch.h"
#include "SettingsExpanderAutomationPeer.h"
#if __has_include("./Automation/Peers/SettingsExpanderAutomationPeer.g.cpp")
#include "./Automation/Peers/SettingsExpanderAutomationPeer.g.cpp"
#endif

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsExpander { L"Mntone.AngelUmbrella.Controls.SettingsExpander" };
}

namespace winrt {
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Automation::Peers;
}

using namespace winrt::Mntone::AngelUmbrella::Automation::Peers::implementation;
using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsExpanderAutomationPeer::SettingsExpanderAutomationPeer(Controls::SettingsExpander const& owner) noexcept
	: SettingsExpanderAutomationPeer_base(owner) {
}

winrt::AutomationOrientation SettingsExpanderAutomationPeer::GetOrientationCore() const {
	if (auto const impl = GetImpl()) {
		switch (impl->Orientation()) {
		case Orientation::Vertical:
			return AutomationOrientation::Vertical;
		case Orientation::Horizontal:
			return AutomationOrientation::Horizontal;
		}
	}
	return AutomationOrientation::None;
}

winrt::hstring SettingsExpanderAutomationPeer::GetClassNameCore() const {
	return winrt::hstring { resources::Mntone_AngelUmbrella_Controls_SettingsExpander };
}

winrt::impl::com_ref<SettingsExpander> SettingsExpanderAutomationPeer::GetImpl() const {
	impl::com_ref<SettingsExpander> impl { nullptr };
	if (auto settingsExpander = Owner().try_as<SettingsExpander>()) {
		settingsExpander.copy_to(impl.put());
	}
	return impl;
}
