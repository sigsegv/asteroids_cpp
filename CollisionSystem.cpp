#include "CollisionSystem.hpp"
#include "GameObject.hpp"
#include "Util.hpp"

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
	if (mColliders.size() < 2) return;

	std::vector<Collision::Ptr> collisions;

	Colliders::iterator active = mColliders.begin(), end = mColliders.end();
	for (; active != end; ++active)
	{
		CircleCollider& activeCollider = **active;
		const sf::Vector2f activeColliderCentre(activeCollider.parent.getPosition());
		Colliders::iterator other = active;
		for(++other; other != end; ++other)
		{
			CircleCollider& otherCollider = **other;
			const sf::Vector2f otherColliderCentre(otherCollider.parent.getPosition());
			const float distance = calcDistance(activeColliderCentre, otherColliderCentre);
			if (distance < activeCollider.radius + otherCollider.radius)
			{
				Collision::Ptr collision(new Collision(activeCollider.parent, otherCollider.parent, sf::Vector2f()));
				collisions.push_back(std::move(collision));
			}
		}
	}
	for (Collision::Ptr& collision : collisions)
	{
		collision->gameObject1.onCollision(*collision);
		collision->gameObject2.onCollision(*collision);
	}
}
