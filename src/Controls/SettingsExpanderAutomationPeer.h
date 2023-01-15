#pragma once
#include "./Automation/Peers/SettingsExpanderAutomationPeer.g.h"

namespace winrt::Mntone::AngelUmbrella::Automation::Peers::implementation {

	struct SettingsExpanderAutomationPeer: SettingsExpanderAutomationPeerT<SettingsExpanderAutomationPeer> {
		SettingsExpanderAutomationPeer(Controls::SettingsExpander const& owner) noexcept;

		// IAutomationPeerOverrides
		hstring GetClassNameCore() const;
		Microsoft::UI::Xaml::Automation::Peers::AutomationOrientation GetOrientationCore() const;
		hstring GetHelpTextCore() const;
		hstring GetNameCore() const;

	private:
		com_ptr<Controls::implementation::SettingsExpander> GetImpl() const;
	};

}

namespace winrt::Mntone::AngelUmbrella::Automation::Peers::factory_implementation {

	struct SettingsExpanderAutomationPeer: SettingsExpanderAutomationPeerT<SettingsExpanderAutomationPeer, implementation::SettingsExpanderAutomationPeer> {
	};

}
