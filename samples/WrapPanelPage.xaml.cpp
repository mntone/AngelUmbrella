#include "pch.h"
#include "WrapPanelPage.xaml.h"
#if __has_include("WrapPanelPage.g.cpp")
#include "WrapPanelPage.g.cpp"
#endif

#include "ViewModels\ColorDataViewModel.h"

namespace winrt {
	using namespace ::winrt::Windows::UI;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Samples::implementation;

void AppendChildren(winrt::UIElementCollection const& collection) {
	using namespace winrt;

	for (auto const& viewModel : Mntone::AngelUmbrella::Samples::ViewModels::implementation::ColorDataViewModel::Assets()) {
		TextBlock textBlock;
		textBlock.Foreground(Media::SolidColorBrush(viewModel.PreferredDarkForeground() ? Colors::Black() : Colors::White()));
		textBlock.Text(viewModel.Name());
		textBlock.TextTrimming(TextTrimming::CharacterEllipsis);
		textBlock.VerticalAlignment(VerticalAlignment::Center);

		Border border;
		border.Background(Media::SolidColorBrush(viewModel.Color()));
		border.Child(textBlock);
		border.Padding(ThicknessHelper::FromUniformLength(8.0));

		collection.Append(border);
	}
}

WrapPanelPage::WrapPanelPage() {
	InitializeComponent();

	AppendChildren(DefaultWrapPanel().Children());
}
