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

	void update(float elapsedSeconds) override;
protected:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	float mRotationSpeed;
	float mMainThruster;
	sf::Sprite mSprite;
	sf::Texture mTexture;
};