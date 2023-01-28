#pragma once
#include "winrt/base.h"

namespace winrt {

	template<std::floating_point _Float>
	constexpr bool close(_Float value1, _Float value2) {
		if (value1 == value2) {
			return true;
		}

		_Float num { (std::abs(value1) + std::abs(value2) + static_cast<_Float>(10)) * std::numeric_limits<_Float>::epsilon() };
		_Float num2 { value1 - value2 };
		if (0 - num < num2) {
			return num > num2;
		}
		return false;
	}

	template<std::floating_point _Float>
	constexpr bool greaterThan(_Float value1, _Float value2) {
		if (value1 > value2) {
			return !close<_Float>(value1, value2);
		}
		return false;
	}

	inline constexpr Windows::Foundation::Numerics::float2 invert(Windows::Foundation::Numerics::float2 const& vec) {
		return Windows::Foundation::Numerics::float2(vec.y, vec.x);
	}

	template<bool invert>
	inline constexpr float to_u(Windows::Foundation::Numerics::float2 const& size);
	template<> inline constexpr float to_u<false>(Windows::Foundation::Numerics::float2 const& size) { return size.x; }
	template<> inline constexpr float to_u<true>(Windows::Foundation::Numerics::float2 const& size) { return size.y; }

	template<bool invert>
	inline constexpr float to_v(Windows::Foundation::Numerics::float2 const& size);
	template<> inline constexpr float to_v<false>(Windows::Foundation::Numerics::float2 const& size) { return size.y; }
	template<> inline constexpr float to_v<true>(Windows::Foundation::Numerics::float2 const& size) { return size.x; }

	template<bool invert>
	inline constexpr float to_u(Windows::Foundation::Size const& size);
	template<> inline constexpr float to_u<false>(Windows::Foundation::Size const& size) { return size.Width; }
	template<> inline constexpr float to_u<true>(Windows::Foundation::Size const& size) { return size.Height; }

	template<bool invert>
	inline constexpr float to_v(Windows::Foundation::Size const& size);
	template<> inline constexpr float to_v<false>(Windows::Foundation::Size const& size) { return size.Height; }
	template<> inline constexpr float to_v<true>(Windows::Foundation::Size const& size) { return size.Width; }

	template<bool inverted>
	inline constexpr Windows::Foundation::Numerics::float2 to_uv(Windows::Foundation::Numerics::float2 const& vec);
	template<> inline constexpr Windows::Foundation::Numerics::float2 to_uv<false>(Windows::Foundation::Numerics::float2 const& vec) { return vec; }
	template<> inline constexpr Windows::Foundation::Numerics::float2 to_uv<true>(Windows::Foundation::Numerics::float2 const& vec) { return invert(vec); }

}
