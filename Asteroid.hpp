#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class Asteroid : public GameObject
{
public:
	enum class Size { small, large };

	Asteroid(Size size);

	virtual void onCollision(GameObject& other) override;
	virtual void update(float elapsedSeconds) override;
protected:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Size mSize;
	sf::Texture mTexture;
	sf::Sprite mSprite;
};