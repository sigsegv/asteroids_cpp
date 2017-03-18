#include "KinematicSystem.hpp"
#include "KinematicBody.hpp"
#include "GameObject.hpp"

KinematicSystem::KinematicSystem()
{}

void KinematicSystem::update(float elapsedSeconds) const
{
	for (KinematicBody* body : mBodies)
	{
		const sf::Vector2f delta(body->velocity * elapsedSeconds);
		body->parent.move(delta);
		body->parent.rotate(body->rotationalVelocity * elapsedSeconds);
	}
}

void KinematicSystem::addBody(KinematicBody& body)
{
	mBodies.push_back(&body);
}

void KinematicSystem::removeBody(KinematicBody& body)
{
	mBodies.remove(&body);
}
