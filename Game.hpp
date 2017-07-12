#pragma once

#include <cassert>
#include <array>
#include <SFML/Graphics.hpp>
#include "Scab.hpp"
#include "KinematicSystem.hpp"
#include "CollisionSystem.hpp"
#include "GameObject.hpp"

class Game
{
public:
    enum class Layer { backDrop, backGround, middleGround, foreGround, userInterface, layerCount };
    
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

	void attachNode(GameObject::Ptr object, Layer layer);
	GameObject::Ptr detachNode(const GameObject& object);
    
    void onAsteroidCreated();
    void onAsteroidDestroyed();
    void onPlayerDestroyed();

	KinematicSystem kinematicSystem;
	CollisionSystem collisionSystem;
private:
    void nextLevel();
    
    uint_t mAsteroids;
    uint_t mLevel;
    std::array<GameObject*, static_cast<size_t>(Layer::layerCount)> mLayers;
	GameObject mRoot;
	sf::RenderWindow mWindow;
	sf::FloatRect mPlayBounds;
};
