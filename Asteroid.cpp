#include "Asteroid.hpp"
#include "Game.hpp"

Asteroid::Asteroid(Size size) :
	mSize(size)
{
	mTexture.loadFromFile("assets/textures/meteorGrey_big1.png");
	mSprite.setTexture(mTexture);
	sf::FloatRect bounds = mSprite.getLocalBounds();
	const float scale = calcScaleFactor<float>(bounds, { 0.0, 0.0, 50.0, 50.0 });
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	setScale({ scale, scale });
	setPosition(100.f, 100.f);
	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);
	kinematicBody->velocity = sf::Vector2f(-50.0f, -50.0f);
	kinematicBody->rotationalVelocity = 10.0f;
}

<<<<<<< Updated upstream
void Asteroid::update(float elapsedSeconds)
=======
void Asteroid::onCollision(GameObject & other)
{
}

void Asteroid::update(float /*elapsedSeconds*/)
>>>>>>> Stashed changes
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
