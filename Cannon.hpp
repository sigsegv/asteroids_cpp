#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class Cannon : public GameObject
{
public:
	Cannon();
protected:
	virtual void updateCurrent(float elapsedSeconds) override;
private:
	static const float sCoolDown;
	static const float sVelocity;
	float mCoolDown;
};
