#pragma once

#include <memory>
#include "Scab.hpp"

class CircleCollider : private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<CircleCollider>;

	CircleCollider(GameObject& parent, float radius) :
		parent(parent),
		radius(radius)
	{ }
		
	virtual ~CircleCollider() { }

	GameObject& parent;
	float radius;
protected:
private:
};