#pragma once

#include <list>
#include <SFML/graphics.hpp>
#include "Scab.hpp"

class KinematicSystem
{
public:
	KinematicSystem();

	void update(float elapsedSeconds) const;

	void addBody(KinematicBody& body);
	void removeBody(KinematicBody& body);
private:
	std::list<KinematicBody*> mBodies;
};
