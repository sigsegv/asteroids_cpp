#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class Asteroid : public GameObject
{
public:
	Asteroid();

	virtual void update(float elapsedSeconds);
protected:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
};