#pragma once

#include "Scab.hpp"
#include "SpriteObject.hpp"

class Asteroid : public SpriteObject
{
public:
	enum class Size { small, large };

	Asteroid(Size size);

	virtual void onCollision(const Collision& other) override;

	static Ptr createAsteroid(const sf::Vector2f& position, const sf::Vector2f& velocity, real_t rotational_velocity, Asteroid::Size sz);
protected:
	virtual void updateCurrent(float elapsedSeconds) override;
private:
	const Size mSize;

	void breakupAsteroid();
};
