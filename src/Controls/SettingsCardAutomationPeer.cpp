#include "pch.h"
#include "SettingsCardAutomationPeer.h"
#if __has_include("./Automation/Peers/SettingsCardAutomationPeer.g.cpp")
#include "./Automation/Peers/SettingsCardAutomationPeer.g.cpp"
#endif

namespace resources {
	constexpr std::wstring_view Mntone_AngelUmbrella_Controls_SettingsCard { L"Mntone.AngelUmbrella.Controls.SettingsCard" };
}

namespace winrt {
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
	using namespace ::winrt::Microsoft::UI::Xaml::Automation::Peers;
}

using namespace winrt::Mntone::AngelUmbrella::Automation::Peers::implementation;
using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

SettingsCardAutomationPeer::SettingsCardAutomationPeer(Controls::SettingsCard const& owner) noexcept
	: SettingsCardAutomationPeer_base(owner) {
}

winrt::AutomationControlType SettingsCardAutomationPeer::GetAutomationControlTypeCore() const {
	if (auto const impl { GetImpl() }) {
		if (impl->IsClickEnabled()) {
			return AutomationControlType::Button;
		}
	}
	return AutomationControlType::Group;
}

winrt::hstring SettingsCardAutomationPeer::GetClassNameCore() const {
	return winrt::hstring { resources::Mntone_AngelUmbrella_Controls_SettingsCard };
}

winrt::AutomationOrientation SettingsCardAutomationPeer::GetOrientationCore() const {
	AutomationOrientation orientation { __super::GetOrientationCore() };
	if (AutomationOrientation::None == orientation) {
		if (auto const impl { GetImpl() }) {
			switch (impl->Orientation()) {
			case Orientation::Vertical:
				orientation = AutomationOrientation::Vertical;
				break;
			case Orientation::Horizontal:
				orientation = AutomationOrientation::Horizontal;
				break;
			}
		}
	}
	return orientation;
}

winrt::hstring SettingsCardAutomationPeer::GetHelpTextCore() const {
	hstring helpText { __super::GetHelpTextCore() };
	if (helpText.empty()) {
		if (auto const impl { GetImpl() }) {
			std::optional<hstring> description { impl->Description().try_as<hstring>() };
			if (description && !description.value().empty()) {
				helpText = description.value();
			}
		}
	}
	return helpText;
}

winrt::hstring SettingsCardAutomationPeer::GetNameCore() const {
	hstring name { __super::GetNameCore() };
	if (name.empty()) {
		if (auto const impl { GetImpl() }) {
			std::optional<hstring> header { impl->Header().try_as<hstring>() };
			if (header && !header.value().empty()) {
				name = header.value();
			}
		}
	}
	return name;
}

winrt::com_ptr<SettingsCard> SettingsCardAutomationPeer::GetImpl() const {
	com_ptr<SettingsCard> impl { nullptr };
	if (auto settingsCard = Owner().try_as<SettingsCard>()) {
		impl = settingsCard->get_strong();
	}
	return impl;
}
