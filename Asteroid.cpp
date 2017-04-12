#include "Asteroid.hpp"
#include "Game.hpp"

Asteroid::Asteroid(Size size) :
	mSize(size)
{
	float gameSize = 1.0;
	if (size == Asteroid::Size::small)
	{
		mTexture.loadFromFile("assets/textures/meteorGrey_small2.png");
		gameSize = 15.0;
	}
	else
	{
		mTexture.loadFromFile("assets/textures/meteorGrey_big1.png");
		gameSize = 50.0;
	}
	mSprite.setTexture(mTexture);
	sf::FloatRect bounds = mSprite.getLocalBounds();
	const float scale = calcScaleFactor<float>(bounds, { 0.0, 0.0, gameSize, gameSize });
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	setScale({ scale, scale });
	setPosition(100.f, 100.f);

	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);
	kinematicBody->velocity = sf::Vector2f(-50.0f, -50.0f);
	kinematicBody->rotationalVelocity = 10.0f;

	collider.reset(new CircleCollider(*this, gameSize));
	Game::instance->collisionSystem.addCollider(*collider);
}

void Asteroid::onCollision(const Collision& /*collision*/)
{
	markForRemoval();
}

void Asteroid::updateCurrent(float /*elapsedSeconds*/)
{
	if (!Game::instance->insideBounds(getPosition()))
	{
		setPosition(Game::instance->warpAround(getPosition()));
	}
}

void Asteroid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
