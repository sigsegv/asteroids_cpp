#include "Player.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "KinematicBody.hpp"
#include "CollisionSystem.hpp"
#include "Cannon.hpp"
#include "Asteroid.hpp"

Player::Player() :
	mRotationSpeed(180.0f),
	mMainThruster(500.0f)
{
	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);

	collider.reset(new CircleCollider(*this, 10.0));
	Game::instance->collisionSystem.addCollider(*collider);

    spriteInit("assets/textures/playerShip1_green.png", { 0.0, 0.0, 20.0, 20.0 });

    sf::FloatRect bounds = mSprite.getLocalBounds();
	Cannon::Ptr cannon(new Cannon());
	cannon->setPosition(bounds.width / 2.f, -bounds.height / 2.f); // place canon at nose
	attachNode(std::move(cannon));
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

void Player::onCollision(const Collision& collision)
{
	GameObject& other = &collision.gameObject1 != this ? collision.gameObject1 : collision.gameObject2;
	if (typeid(other) == typeid(Asteroid))
	{
		markForRemoval();
		Game::instance->onPlayerDestroyed();
	}
}
