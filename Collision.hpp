#pragma once

#include "Scab.hpp"
#include "CircleCollider.hpp"
#include "GameObject.hpp"

/**
 * Represents a collision between two GameObjects and their respective colliders
 */
class Collision
{
public:
	using Ptr = std::unique_ptr<Collision>;

	Collision(GameObject& gameObject1, GameObject& gameObject2, const sf::Vector2f& location) :
		gameObject1(gameObject1),
		gameObject2(gameObject2),
		collider1(*gameObject1.collider),
		collider2(*gameObject2.collider),
		location(location)
	{ }

	GameObject &gameObject1, &gameObject2;
	CircleCollider &collider1, &collider2;
	sf::Vector2f location;
};