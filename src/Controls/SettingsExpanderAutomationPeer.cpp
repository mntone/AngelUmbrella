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

winrt::hstring SettingsExpanderAutomationPeer::GetClassNameCore() const {
	return winrt::hstring { resources::Mntone_AngelUmbrella_Controls_SettingsExpander };
}

winrt::AutomationOrientation SettingsExpanderAutomationPeer::GetOrientationCore() const {
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

winrt::hstring SettingsExpanderAutomationPeer::GetHelpTextCore() const {
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

winrt::hstring SettingsExpanderAutomationPeer::GetNameCore() const {
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

winrt::com_ptr<SettingsExpander> SettingsExpanderAutomationPeer::GetImpl() const {
	com_ptr<SettingsExpander> impl { nullptr };
	if (auto settingsExpander = Owner().try_as<SettingsExpander>()) {
		impl = settingsExpander->get_strong();
	}
	return impl;
}
