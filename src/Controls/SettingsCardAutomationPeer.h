#pragma once
#include "./Automation/Peers/SettingsCardAutomationPeer.g.h"

namespace winrt::Mntone::AngelUmbrella::Automation::Peers::implementation {

	struct SettingsCardAutomationPeer: SettingsCardAutomationPeerT<SettingsCardAutomationPeer> {
		SettingsCardAutomationPeer(Controls::SettingsCard const& owner) noexcept;

		// IAutomationPeerOverrides
		Microsoft::UI::Xaml::Automation::Peers::AutomationControlType GetAutomationControlTypeCore() const;
		hstring GetClassNameCore() const;
		Microsoft::UI::Xaml::Automation::Peers::AutomationOrientation GetOrientationCore() const;
		hstring GetHelpTextCore() const;
		hstring GetNameCore() const;

	private:
		com_ptr<Controls::implementation::SettingsCard> GetImpl() const;
	};

}

namespace winrt::Mntone::AngelUmbrella::Automation::Peers::factory_implementation {

	struct SettingsCardAutomationPeer: SettingsCardAutomationPeerT<SettingsCardAutomationPeer, implementation::SettingsCardAutomationPeer> {
	};

}
