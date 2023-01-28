#include "pch.h"
#include "WrapPanel.h"

#include <concepts>

#include "Helpers/LayoutHelper.h"

namespace winrt {
	using namespace ::winrt::Windows::Foundation;
	using namespace ::winrt::Windows::Foundation::Numerics;

	using namespace ::winrt::Microsoft::UI::Xaml;
	using namespace ::winrt::Microsoft::UI::Xaml::Controls;

	using namespace ::winrt::Mntone::AngelUmbrella::Controls;
}

using namespace winrt::Mntone::AngelUmbrella::Controls::implementation;

WrapPanel::WrapPanel() {
	props_.DelayInitIfNeeded();
}

template<bool inverted>
inline winrt::Size MeasureCore(
	winrt::UIElementCollection const& collection,
	winrt::float2 const constraint,
	winrt::float2 const spacing) {
	using namespace winrt;

	float2 current { float2::zero() };
	float2 expectedItem { float2::zero() };
	float2 expectedLine { float2(-spacing.x, 0.f) };
	for (UIElement const child : collection) {
		child.Measure(constraint);

		expectedItem = to_uv<inverted>(child.DesiredSize());
		if (greaterThan(expectedLine.x + spacing.x + expectedItem.x, constraint.x)) {
			current.x = (std::max)(expectedLine.x, current.x);
			current.y += expectedLine.y + spacing.y;
			expectedLine = expectedItem;

			if (greaterThan(expectedItem.x, constraint.x)) {
				current.x = (std::max)(expectedItem.x, constraint.x);
				current.y += expectedItem.y + spacing.y;
				expectedLine = float2(-spacing.x, 0.f);
			}
		} else {
			expectedLine.x += spacing.x + expectedItem.x;
			expectedLine.y = (std::max)(expectedItem.y, expectedLine.y);
		}
	}
	current.x = (std::max)(expectedLine.x, current.x);
	current.y += spacing.y + expectedItem.y;
	return Size(current);
}

winrt::Size WrapPanel::MeasureOverride(Size const& constraintSize) {
	bool inverted { Orientation::Vertical == Orientation() };
	UIElementCollection const children { Children() };

	Size measureSize;
	if (inverted) {
		float2 const invConstraintSize { invert(constraintSize) };
		float2 const invSpacing(static_cast<float>(VerticalSpacing()), static_cast<float>(HorizontalSpacing()));
		measureSize = invert(MeasureCore<true>(children, invConstraintSize, invSpacing));
	} else {
		float2 const spacing(static_cast<float>(HorizontalSpacing()), static_cast<float>(VerticalSpacing()));
		measureSize = MeasureCore<false>(children, constraintSize, spacing);
	}
	return measureSize;
}

template<bool inverted, typename Itr, std::enable_if_t<std::is_same_v<typename Itr::value_type, winrt::UIElement>, std::nullptr_t> = nullptr>
inline void ArrangeLine(Itr begin, Itr end, float spacingU, float v, float nextVDiff) {
	using namespace winrt;

	float offsetU { 0.f };
	for (auto itr { begin }; itr != end; ++itr) {
		UIElement const& child { *itr };
		WINRT_ASSERT(nullptr != child);

		float u { to_u<inverted>(child.DesiredSize()) };
		if constexpr (inverted) {
			Rect finalRect { Rect(v, offsetU, nextVDiff, u) };
			child.Arrange(finalRect);
		} else {
			Rect finalRect { Rect(offsetU, v, u, nextVDiff) };
			child.Arrange(finalRect);
		}
		offsetU += spacingU + u;
	}
}

template<bool inverted>
inline void ArrangeCore(
	winrt::UIElementCollection const& collection,
	winrt::float2 const finalSize,
	winrt::float2 const spacing) {
	using namespace winrt;

	float currentV { 0.f };
	auto cur { collection.begin() };
	auto const end { collection.end() };

	float2 expectedItem { float2::zero() };
	float2 expectedLine { float2(-spacing.x, 0.f) };
	for (auto itr { cur }; itr != end; ++itr) {
		UIElement const child { *itr };
		WINRT_ASSERT(nullptr != child);

		expectedItem = to_uv<inverted>(child.DesiredSize());
		if (greaterThan(expectedLine.x + spacing.x + expectedItem.x, finalSize.x)) {
			ArrangeLine<inverted>(cur, itr, spacing.x, currentV, expectedLine.y);
			currentV += expectedLine.y + spacing.y;
			expectedLine = expectedItem;

			if (greaterThan(expectedItem.x, finalSize.x)) {
				ArrangeLine<inverted>(itr, itr + 1,  spacing.x, currentV, expectedItem.y);
				currentV += expectedItem.y + spacing.y;
				expectedLine = float2(-spacing.x, 0.f);
				cur = itr + 1;
			} else {
				cur = itr;
			}
		} else {
			expectedLine.x += spacing.x + expectedItem.x;
			expectedLine.y = (std::max)(expectedItem.y, expectedLine.y);
		}
	}
	if (cur != end) {
		ArrangeLine<inverted>(cur, end, spacing.x, currentV, expectedLine.y);
	}
}

winrt::Size WrapPanel::ArrangeOverride(Size const& finalSize) {
	bool inverted { Orientation::Vertical == Orientation() };

	UIElementCollection const& children { Children() };
	if (inverted) {
		float2 const invFinalSize { invert(finalSize) };
		float2 const invSpacing(static_cast<float>(VerticalSpacing()), static_cast<float>(HorizontalSpacing()));
		ArrangeCore<true>(children, invFinalSize, invSpacing);
	} else {
		float2 const spacing(static_cast<float>(HorizontalSpacing()), static_cast<float>(VerticalSpacing()));
		ArrangeCore<false>(children, finalSize, spacing);
	}
	return finalSize;
}

void WrapPanel::OnLayoutMetricsChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& /*args*/) {
	get_self<WrapPanel>(sender.as<winrt::WrapPanel>())->InvalidateMeasure();
}

void WrapPanel::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& /*args*/) {
	get_self<WrapPanel>(sender.as<winrt::WrapPanel>())->InvalidateMeasure();
}


