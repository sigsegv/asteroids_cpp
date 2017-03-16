#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"

class KinematicBody : private sf::NonCopyable
{
public:
	typedef std::unique_ptr<KinematicBody> Ptr;

	KinematicBody(GameObject& parent) : parent(parent)
	{

	}

	GameObject& parent;
	sf::Vector2f velocity;
};
