#include "CollisionSystem.hpp"
#include "GameObject.hpp"

CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::addCollider(CircleCollider & collider)
{
	mColliders.push_back(&collider);
}

void CollisionSystem::removeCollider(CircleCollider & collider)
{
	mColliders.remove(&collider);
}

void CollisionSystem::check()
{
	Colliders temp(mColliders); // make copy so colliders can get removed
	Colliders::iterator active = temp.begin(), end = temp.end();
	for (; active != end; ++active)
	{
		CircleCollider& activeCollider = **active;
		const sf::Vector2f activeColliderCentre(activeCollider.parent.getPosition());
		Colliders::iterator other = ++active;
		for(; other != end; ++other)
		{
			CircleCollider& otherCollider = **other;
			const sf::Vector2f otherColliderCentre(otherCollider.parent.getPosition());
			const float distance = calcDistance(activeColliderCentre, otherColliderCentre);
			if (distance < activeCollider.radius + otherCollider.radius)
			{
				activeCollider.parent.onCollision(otherCollider.parent);
				otherCollider.parent.onCollision(activeCollider.parent);
			}
		}
	}
}
