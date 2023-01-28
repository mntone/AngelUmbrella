#include "pch.h"
#include "SizeSpecifiedWrapPanel.h"

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

SizeSpecifiedWrapPanel::SizeSpecifiedWrapPanel() {
	props_.DelayInitIfNeeded();
}

template<bool inverted>
inline winrt::Size MeasureCore(
	winrt::UIElementCollection const& collection,
	winrt::float2 const itemSize,
	winrt::float2 const constraint,
	winrt::float2 const spacing) {
	using namespace winrt;

	bool const useItemU { !std::isnan(itemSize.x) && greaterThan(itemSize.x, 0.f) };
	bool const useItemV { !std::isnan(itemSize.y) && greaterThan(itemSize.y, 0.f) };
	float2 const availableSize {
		useItemU ? itemSize.x : constraint.x,
		useItemV ? itemSize.y : constraint.y,
	};

	if (useItemU) {
		uint32_t const count { collection.Size() };
		uint32_t const uCount { static_cast<uint32_t>(std::floor(static_cast<float>(constraint.x + spacing.x) / (itemSize.x + spacing.x))) };
		uint32_t vCount { count / uCount };
		if (count - vCount * uCount != 0) {
			vCount += 1;
		}
		return Size(uCount * availableSize.x, vCount * availableSize.y);
	}

	float2 current { float2::zero() };
	float2 expectedItem { itemSize };
	float2 expectedLine { float2(-spacing.x, 0.f) };
	for (UIElement const child : collection) {
		child.Measure(availableSize);

		float2 const desiredSize { to_uv<inverted>(child.DesiredSize()) };
		expectedItem = float2(
			useItemU ? itemSize.x : desiredSize.x,
			useItemV ? itemSize.y : desiredSize.y);
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

winrt::Size SizeSpecifiedWrapPanel::MeasureOverride(Size const& constraintSize) {
	bool inverted { Orientation::Vertical == Orientation() };
	UIElementCollection const children { Children() };

	Size measureSize;
	if (inverted) {
		float2 const invItemSize(static_cast<float>(ItemHeight()), static_cast<float>(ItemWidth()));
		float2 const invConstraintSize { invert(constraintSize) };
		float2 const invSpacing(static_cast<float>(VerticalSpacing()), static_cast<float>(HorizontalSpacing()));
		measureSize = invert(MeasureCore<true>(children, invItemSize, invConstraintSize, invSpacing));
	} else {
		float2 const itemSize(static_cast<float>(ItemWidth()), static_cast<float>(ItemHeight()));
		float2 const spacing(static_cast<float>(HorizontalSpacing()), static_cast<float>(VerticalSpacing()));
		measureSize = MeasureCore<false>(children, itemSize, constraintSize, spacing);
	}
	return measureSize;
}

template<bool inverted, typename Itr, std::enable_if_t<std::is_same_v<typename Itr::value_type, winrt::UIElement>, std::nullptr_t> = nullptr>
inline void ArrangeLine(Itr begin, Itr end, float itemU, float spacingU, float v, float nextVDiff, bool useItemU) {
	using namespace winrt;

	float offsetU { 0.f };
	for (auto itr { begin }; itr != end; ++itr) {
		UIElement const& child { *itr };
		WINRT_ASSERT(nullptr != child);

		float u { useItemU ? itemU : to_u<inverted>(child.DesiredSize()) };
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
	winrt::float2 const itemSize,
	winrt::float2 const finalSize,
	winrt::float2 const spacing) {
	using namespace winrt;

	bool const useItemU { !std::isnan(itemSize.x) && greaterThan(itemSize.x, 0.f) };
	bool const useItemV { !std::isnan(itemSize.y) && greaterThan(itemSize.y, 0.f) };

	float currentV { 0.f };
	auto cur { collection.begin() };
	auto const end { collection.end() };

	if (useItemU) {
		uint32_t const uCount { static_cast<uint32_t>(std::floor(static_cast<float>(finalSize.x + spacing.x) / (itemSize.x + spacing.x))) };

		uint32_t pos { 0 };
		float expectedItemV { 0.f };
		float expectedLineV { 0.f };
		for (auto itr { cur }; itr != end; ++itr) {
			UIElement const child { *itr };
			WINRT_ASSERT(nullptr != child);

			float2 const desiredSize { to_uv<inverted>(child.DesiredSize()) };
			expectedItemV = useItemV ? itemSize.y : desiredSize.y;
			if (pos++ == uCount) {
				ArrangeLine<inverted>(cur, itr, itemSize.x, spacing.x, currentV, expectedLineV, useItemU);
				currentV += expectedLineV + spacing.y;
				expectedLineV = expectedItemV;
				cur = itr;
				pos = 1;
			} else {
				expectedLineV = (std::max)(expectedItemV, expectedLineV);
			}
		}
		if (cur != end) {
			ArrangeLine<inverted>(cur, end, itemSize.x, spacing.x, currentV, expectedLineV, useItemU);
		}
		return;
	}

	float2 expectedItem { itemSize };
	float2 expectedLine { float2(-spacing.x, 0.f) };
	for (auto itr { cur }; itr != end; ++itr) {
		UIElement const child { *itr };
		WINRT_ASSERT(nullptr != child);

		float2 const desiredSize { to_uv<inverted>(child.DesiredSize()) };
		expectedItem = float2(
			useItemU ? itemSize.x : desiredSize.x,
			useItemV ? itemSize.y : desiredSize.y);
		if (greaterThan(expectedLine.x + spacing.x + expectedItem.x, finalSize.x)) {
			ArrangeLine<inverted>(cur, itr, itemSize.x, spacing.x, currentV, expectedLine.y, useItemU);
			currentV += expectedLine.y + spacing.y;
			expectedLine = expectedItem;

			if (greaterThan(expectedItem.x, finalSize.x)) {
				ArrangeLine<inverted>(itr, itr + 1, itemSize.x, spacing.x, currentV, expectedItem.y, useItemU);
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
		ArrangeLine<inverted>(cur, end, itemSize.x, spacing.x, currentV, expectedLine.y, useItemU);
	}
}

winrt::Size SizeSpecifiedWrapPanel::ArrangeOverride(Size const& finalSize) {
	bool inverted { Orientation::Vertical == Orientation() };

	UIElementCollection const& children { Children() };
	if (inverted) {
		float2 const invItemSize(static_cast<float>(ItemHeight()), static_cast<float>(ItemWidth()));
		float2 const invFinalSize { invert(finalSize) };
		float2 const invSpacing(static_cast<float>(VerticalSpacing()), static_cast<float>(HorizontalSpacing()));
		ArrangeCore<true>(children, invItemSize, invFinalSize, invSpacing);
	} else {
		float2 const itemSize(static_cast<float>(ItemWidth()), static_cast<float>(ItemHeight()));
		float2 const spacing(static_cast<float>(HorizontalSpacing()), static_cast<float>(VerticalSpacing()));
		ArrangeCore<false>(children, itemSize, finalSize, spacing);
	}
	return finalSize;
}

void SizeSpecifiedWrapPanel::OnLayoutMetricsChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& /*args*/) {
	get_self<SizeSpecifiedWrapPanel>(sender.as<winrt::SizeSpecifiedWrapPanel>())->InvalidateMeasure();
}

void SizeSpecifiedWrapPanel::OnOrientationChangedStatic(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& /*args*/) {
	get_self<SizeSpecifiedWrapPanel>(sender.as<winrt::SizeSpecifiedWrapPanel>())->InvalidateMeasure();
}


