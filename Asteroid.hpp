#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class Asteroid : public GameObject
{
public:
	enum class Size { small, large };

	Asteroid(Size size);

	virtual void onCollision(const Collision& other) override;

	static Asteroid::Ptr Asteroid::createAsteroid(const sf::Vector2f& position, const sf::Vector2f& velocity, real_t rotational_velocity, Asteroid::Size sz);
protected:
	virtual void updateCurrent(float elapsedSeconds) override;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	const Size mSize;
	sf::Texture mTexture;
	sf::Sprite mSprite;

	void breakupAsteroid();
};