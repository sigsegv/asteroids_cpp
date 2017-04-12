#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"
#include "KinematicSystem.hpp"
#include "CollisionSystem.hpp"
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

	const sf::FloatRect& getBounds() const;
	/**
	 * return true of position outside of bound areas
	 */
	bool insideBounds(const sf::Vector2f& position) const;
	/**
	 * Get new position for wrap around effect
	 */
	sf::Vector2f warpAround(const sf::Vector2f& position) const;

	void attachNode(GameObject::Ptr object);
	GameObject::Ptr detachNode(const GameObject& object);

	KinematicSystem kinematicSystem;
	CollisionSystem collisionSystem;
private:
	GameObject mRoot;
	sf::RenderWindow mWindow;
	sf::FloatRect mPlayBounds;
};