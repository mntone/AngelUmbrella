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
	if (auto const impl = GetImpl()) {
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
	if (auto const impl = GetImpl()) {
		switch (impl->Orientation()) {
		case Orientation::Vertical:
			return AutomationOrientation::Vertical;
		case Orientation::Horizontal:
			return AutomationOrientation::Horizontal;
		}
	}
	return __super::GetOrientationCore();
}

winrt::hstring SettingsCardAutomationPeer::GetFullDescriptionCore() const {
	hstring helpText { __super::GetFullDescriptionCore() };
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

void SettingsCardAutomationPeer::Invoke() const {
	//Owner().
}

winrt::impl::com_ref<SettingsCard> SettingsCardAutomationPeer::GetImpl() const {
	impl::com_ref<SettingsCard> impl { nullptr };
	if (auto settingsCard = Owner().try_as<SettingsCard>()) {
		settingsCard.copy_to(impl.put());
	}
	return impl;
}
