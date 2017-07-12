#pragma once

#include "Scab.hpp"
#include "SpriteObject.hpp"

class Projectile : public SpriteObject
{
public:
	Projectile();

	virtual void onCollision(const Collision& other) override;
protected:
	virtual void updateCurrent(float elapsedSeconds) override;
private:
};
