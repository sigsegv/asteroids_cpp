#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class Projectile : public GameObject
{
public:
	Projectile();

	virtual void onCollision(GameObject& other) override;
protected:
	virtual void updateCurrent(float elapsedSeconds) override;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
};