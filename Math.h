#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Scab.hpp"

constexpr real_t PI   = static_cast<real_t>(M_PI);
constexpr real_t PI_2 = static_cast<real_t>(M_PI_2);
constexpr real_t PI_4 = static_cast<real_t>(M_PI_4);

inline constexpr real_t deg2Rad(real_t deg)
{
	return deg / 180.0f * PI;
}
