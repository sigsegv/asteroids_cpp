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
			projectile->setPosition(getWorldPosition());
			projectile->setRotation(getWorldRotation());
			const float deg_rotation = projectile->getRotation();
			const float rad_rotation = deg_rotation / 180.0 * M_PI;
			sf::Vector2f velocity = Vector2Utilf::fromAngle(rad_rotation);
			velocity = velocity * sVelocity;
			projectile->kinematicBody->velocity = velocity;
			Game::instance->attachNode(std::move(projectile));
			mCoolDown = sCoolDown;
		}
	}
}
