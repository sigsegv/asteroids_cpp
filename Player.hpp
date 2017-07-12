#pragma once

#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"
#include "SpriteObject.hpp"

class Player : public SpriteObject
{
public:
	Player();
	~Player();

	void onCollision(const Collision& other) override;
protected:
//	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void updateCurrent(float elapsedSeconds) override;
private:
	float mRotationSpeed;
	float mMainThruster;
};
