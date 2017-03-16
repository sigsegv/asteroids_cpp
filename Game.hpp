#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"
#include "KinematicSystem.hpp"
#include "GameObject.hpp"

class Game
{
public:
	static Game* instance;

	Game();

	void run();
	void update(const sf::Time& elapsedTime);
	void processEvents();
	void render();

	/**
	 * return true of position outside of bound areas
	 */
	bool insideBounds(const sf::Vector2f& position) const;
	/**
	 * Get new position for wrap around effect
	 */
	sf::Vector2f warpAround(const sf::Vector2f& position) const;

	KinematicSystem kinematicSystem;
private:
	sf::RenderWindow mWindow;
	GameObject mRoot;
	sf::FloatRect mPlayBounds;
};