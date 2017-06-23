#pragma once

#include <cstdint>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ostream>
#include <SFML/System/Vector2.hpp>

/**
* 2D Vector (or point)
*/
template <typename T>
class Vector2Util
{
public:
	/**
	* The length of this vector
	*
	* @returns the length of this vector
	*/
	static constexpr real_t magnitude(const sf::Vector2<T>& v) noexcept
	{
		// TODO make constexpr
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	/**
	* This vector with length of 1
	*
	* @returns This vector with length of 1
	*/
	static sf::Vector2<T> unit(const sf::Vector2<T>& v)
	{
		// TODO make constexpr
		const real_t mag = magnitude(v);
		if (mag == 0.0) return sf::Vector2<T>{ 0, 0 };
		return v / mag;
	}

	/**
	* Dot product of this and other
	*
	* @param other other vector
	* @returns Dot product of this and other
	*/
	static constexpr real_t dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b) noexcept
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	* Get a normal vector of this vector
	*
	* @returns one of the two possible normal vectors
	*/
	static constexpr sf::Vector2<T> normal(const sf::Vector2<T>& v) noexcept
	{
		return sf::Vector2<T>{ -v.y, v.x };
	}

	/**
	* The distance between this and other
	*
	* @param other other vector
	* @returns magnitude of this - other
	*/
	static constexpr real_t distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b) noexcept
	{
		return magnitude(b - a);
	}

	/**
	* Get the angle between this and other
	*
	* @param other other vector
	* @returns angle between this and other in radians
	*/
	static real_t angle(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
	{
		return std::acos(dot(a, b) / magnitude(a) * magnitude(b));
	}
	
	/**
	 * Get the angle, as defined by converting from cartesian to polar coords.
	 *
	 * @param v the vector
	 * @returns polar coordinate angle in degrees
	 */
	static real_t angle(const sf::Vector2<T>& v)
	{
		const sf::Vector2<T> u = unit(v);
		return std::atan(u.y / u.x);
	}

	/**
	 * Return unit vector representing a rotation of angle
	 * @param angle in radians
	 */
	static sf::Vector2<T> fromAngle(real_t angle)
	{
		return{std::cos(angle), std::sin(angle)};
	}
};

//template<typename T>
//std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
//{
//	return os << "<" << v.x << ", " << v.y << ">";
//}
