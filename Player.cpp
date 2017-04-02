#include "Player.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "KinematicBody.hpp"
#include "CollisionSystem.hpp"
#include "Canon.hpp"

Player::Player() :
	mRotationSpeed(180.0f),
	mMainThruster(500.0f)
{
	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);

	collider.reset(new CircleCollider(*this, 10.0));
	Game::instance->collisionSystem.addCollider(*collider);

	mTexture.loadFromFile("assets/textures/playerShip1_green.png");
	mSprite.setTexture(mTexture);
	sf::FloatRect bounds = mSprite.getLocalBounds();
	const float scale = calcScaleFactor<float>(bounds, { 0.0, 0.0, 20.0, 20.0 });
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	setScale({ scale, scale });
	setPosition(Game::instance->getBounds().width / 2.0f, Game::instance->getBounds().height / 2.0f);

	Canon::Ptr canon(new Canon());
	canon->setPosition(bounds.width / 2.f, -bounds.height / 2.f); // place canon at nose
	attachNode(std::move(canon));
}

Player::~Player()
{
}

void Player::updateCurrent(float elapsedSeconds)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotate(elapsedSeconds * -mRotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotate(elapsedSeconds * mRotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sf::Transform transform;
		transform.rotate(getRotation());
		const sf::Vector2f offset = transform.transformPoint({ 0.0, -1.0 });
		kinematicBody->velocity = kinematicBody->velocity + (offset * (mMainThruster * elapsedSeconds));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

	}
	if (!Game::instance->insideBounds(getPosition()))
	{
		setPosition(Game::instance->warpAround(getPosition()));
	}
}

void Player::onCollision(GameObject & /*other*/)
{
	
}

void Player::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
