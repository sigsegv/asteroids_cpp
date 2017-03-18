#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"

class KinematicBody : private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<KinematicBody>;

	KinematicBody(GameObject& parent) : parent(parent), rotationalVelocity(0.0f)
	{

	}

	GameObject& parent;
	float rotationalVelocity;
	sf::Vector2f velocity;
};
