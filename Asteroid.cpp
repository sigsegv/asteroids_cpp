#include "Asteroid.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "Math.h"

namespace
{
constexpr real_t GameSizeSmall = 15.0f;
constexpr real_t GameSizeLarge = 50.0f;
}

Asteroid::Asteroid(Size size) :
	mSize(size)
{
	float gameSize = 1.0f;
    std::string filepath;
	if (size == Asteroid::Size::small)
	{
		filepath = "assets/textures/meteorGrey_small2.png";
		gameSize = GameSizeSmall;
	}
	else
	{
		filepath = "assets/textures/meteorGrey_big1.png";
		gameSize = GameSizeLarge;
	}
    spriteInit(filepath, {0.0f, 0.0f, gameSize, gameSize});

	kinematicBody.reset(new KinematicBody(*this));
	Game::instance->kinematicSystem.addBody(*kinematicBody);
	kinematicBody->rotationalVelocity = 10.0f;

	collider.reset(new CircleCollider(*this, gameSize / 2.0f));
	Game::instance->collisionSystem.addCollider(*collider);
}

void Asteroid::onCollision(const Collision& /*collision*/)
{
	markForRemoval();
	Game::instance->onAsteroidDestroyed();
	if (mSize == Size::large) breakupAsteroid();
}

void Asteroid::updateCurrent(float /*elapsedSeconds*/)
{
	if (!Game::instance->insideBounds(getPosition()))
	{
		setPosition(Game::instance->warpAround(getPosition()));
	}
}

Asteroid::Ptr Asteroid::createAsteroid(const sf::Vector2f& position, const sf::Vector2f& velocity, real_t rotational_velocity, Asteroid::Size sz)
{
	Asteroid::Ptr asteroid(new Asteroid(sz));
	asteroid->setPosition(position);
	asteroid->kinematicBody->velocity = velocity;
	asteroid->kinematicBody->rotationalVelocity = rotational_velocity;
	return asteroid;
}

void Asteroid::breakupAsteroid()
{
	constexpr real_t rad_delta_angle = deg2Rad(120.0f);
	constexpr real_t rad_angle1 = PI_4;
	constexpr real_t rad_angle2 = rad_angle1 + rad_delta_angle;
	constexpr real_t rad_angle3 = rad_angle2 + rad_delta_angle;

	constexpr real_t displacement = GameSizeLarge / 2.0f;
	constexpr real_t rotational_velocity = 20.0f;
	constexpr real_t delta_velocity = 50.0f;
	const sf::Vector2f position = getPosition();

	const sf::Vector2f u1 = Vector2Utilf::fromAngle(rad_angle1);
	const sf::Vector2f d1 = u1 * displacement;
	const sf::Vector2f v1 = u1 * delta_velocity;

	Asteroid::Ptr asteroid1 = createAsteroid(position + d1, kinematicBody->velocity + v1, rotational_velocity, Asteroid::Size::small);

	const sf::Vector2f u2 = Vector2Utilf::fromAngle(rad_angle2);
	const sf::Vector2f d2 = u2 * displacement;
	const sf::Vector2f v2 = u2 * delta_velocity;

	Asteroid::Ptr asteroid2 = createAsteroid(position + d2, kinematicBody->velocity + v2, rotational_velocity, Asteroid::Size::small);

	const sf::Vector2f u3 = Vector2Utilf::fromAngle(rad_angle3);
	const sf::Vector2f d3 = u3 * displacement;
	const sf::Vector2f v3 = u3 * delta_velocity;

	Asteroid::Ptr asteroid3 = createAsteroid(position + d3, kinematicBody->velocity + v3, rotational_velocity, Asteroid::Size::small);

    Game::instance->attachNode(std::move(asteroid1), Game::Layer::middleGround);
	Game::instance->attachNode(std::move(asteroid2), Game::Layer::middleGround);
	Game::instance->attachNode(std::move(asteroid3), Game::Layer::middleGround);
	Game::instance->onAsteroidCreated();
	Game::instance->onAsteroidCreated();
	Game::instance->onAsteroidCreated();
}
