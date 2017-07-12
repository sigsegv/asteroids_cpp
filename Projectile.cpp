#include "Projectile.hpp"
#include "Game.hpp"
#include "Util.hpp"

Projectile::Projectile()
{
	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);

	collider.reset(new CircleCollider(*this, 2.0));
	Game::instance->collisionSystem.addCollider(*collider);

    spriteInit("assets/textures/laserRed06.png", { 0.0, 0.0, 4.0, 4.0 });
}

void Projectile::onCollision(const Collision& /*collision*/)
{
	markForRemoval();
}

void Projectile::updateCurrent(float elapsedSeconds)
{
	if (!Game::instance->insideBounds(this->getPosition()))
	{
		markForRemoval();
	}
}
