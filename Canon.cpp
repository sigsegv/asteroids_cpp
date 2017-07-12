#include "Canon.hpp"
#include "Game.hpp"
#include "Projectile.hpp"

const float Canon::sCoolDown = 0.25;
const float Canon::sVelocity = 500.0;

Canon::Canon() :
	mCoolDown(0.0)
{
}

void Canon::updateCurrent(float elapsedSeconds)
{
	if (mCoolDown > 0.0)
	{
		mCoolDown -= elapsedSeconds;
		if (mCoolDown < 0.0) mCoolDown = 0.0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (mCoolDown == 0.0)
		{
			GameObject::Ptr projectile(new Projectile());
			// position and direct projectile
			projectile->setPosition(getWorldPosition());
			projectile->setRotation(getWorldRotation());
			// get ships velocity
			const sf::Vector2f parentVelocity = mParent->kinematicBody->velocity;
			// calc velocity
			sf::Transform transform;
			transform.rotate(projectile->getRotation());
			const sf::Vector2f direction = transform.transformPoint({ 0.0, -1.0 });
			const sf::Vector2f velocity = parentVelocity + (direction * sVelocity);
			projectile->kinematicBody->velocity = velocity;
            Game::instance->attachNode(std::move(projectile), Game::Layer::middleGround);
			mCoolDown = sCoolDown;
		}
	}
}
