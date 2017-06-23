#pragma once

#include <cassert>
#include <limits>
#include "Scab.hpp"
#include "Vector2Util.hpp"

using Vector2Utilf = Vector2Util<float>; 

/**
	* Returns the scale factor needed to scale original to desired, while preserving the aspect ratio
	*/
template<typename T>
float calcScaleFactor(const sf::Rect<T>& original, const sf::Rect<T>& desired)
{
	assert(original.width > 0.0);
	assert(original.height > 0.0);
	const float scale_x = desired.width / original.width;
	const float scale_y = desired.height / original.height;
	return std::max(scale_x, scale_y);
}

template<typename T>
float calcDistance(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	const sf::Vector2<T> delta(b - a);
	return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}

template<typename T>
unsigned int UInt(T v)
{
	return static_cast<unsigned int>(v);
}
template<typename T>
unsigned int Float(T v)
{
	return static_cast<float>(v);
}
#ifdef _DEBUG
inline unsigned int UInt(float v)
{
	assert(v >= 0.0);
	assert(v <= std::numeric_limits<unsigned int>::max());
	return static_cast<unsigned int>(v);
}
inline float Float(unsigned int v)
{
	assert(v <= std::numeric_limits<float>::max());
	return static_cast<float>(v);
}
#endif

