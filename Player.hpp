#pragma once

#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"
#include "GameObject.hpp"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void onCollision(GameObject& other) override;
protected:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void updateCurrent(float elapsedSeconds) override;
private:
	float mRotationSpeed;
	float mMainThruster;
	sf::Sprite mSprite;
	sf::Texture mTexture;
};