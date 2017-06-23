#include "Projectile.hpp"
#include "Game.hpp"
#include "Util.hpp"

Projectile::Projectile()
{
	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);

	collider.reset(new CircleCollider(*this, 2.0));
	Game::instance->collisionSystem.addCollider(*collider);

	assert(mTexture.loadFromFile("assets/textures/laserRed06.png"));
	mSprite.setTexture(mTexture);

	sf::FloatRect bounds = mSprite.getLocalBounds();
	const float scale = calcScaleFactor<float>(bounds, { 0.0, 0.0, 4.0, 4.0 });
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	setScale({ scale, scale });
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

void Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
