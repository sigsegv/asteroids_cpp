#pragma once

#include <list>
#include "Scab.hpp"
#include "CircleCollider.hpp"

class CollisionSystem
{
public:
	CollisionSystem();

	void addCollider(CircleCollider& collider);
	void removeCollider(CircleCollider& collider);

	void check();
private:
	using Colliders = std::list<CircleCollider*>;
	Colliders mColliders;
};