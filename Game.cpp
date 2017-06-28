#include "Game.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Util.hpp"

namespace
{

}

Game* Game::instance = 0;

Game::Game()
{
	instance = this;
}

void Game::run()
{
	mWindow.create(sf::VideoMode(640, 480), "SFML Application");
	mPlayBounds.width = Float(mWindow.getSize().x);
	mPlayBounds.height = Float(mWindow.getSize().y);

	Player::Ptr player(new Player());
	mRoot.attachNode(std::move(player));

	
	mRoot.attachNode(Asteroid::createAsteroid({ 100.0, 100.0 }, { -50.0, -50.0 }, 10.0, Asteroid::Size::large));
	mRoot.attachNode(Asteroid::createAsteroid({ 500.0, 500.0 }, { 50.0, -50.0 }, 10.0, Asteroid::Size::large));
	mRoot.attachNode(Asteroid::createAsteroid({ 300.0, 300.0 }, { 50.0, 50.0 }, 10.0, Asteroid::Size::large));

	sf::Clock clock;
	sf::Time kTimePerFrame = sf::milliseconds(17); // 60 FPS
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		elapsedTimeSinceLastUpdate += clock.restart();
		if (elapsedTimeSinceLastUpdate >= kTimePerFrame)
		{
			elapsedTimeSinceLastUpdate -= kTimePerFrame;
			update(kTimePerFrame);
		}
		render();
	}
}

void Game::update(const sf::Time& elapsedTime)
{
	const float elapsedSeconds = elapsedTime.asSeconds();
	collisionSystem.check();
	kinematicSystem.update(elapsedSeconds);
	mRoot.update(elapsedSeconds);
	mRoot.cleanup();
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mRoot);
	mWindow.display();
}

const sf::FloatRect& Game::getBounds() const
{
	return mPlayBounds;
}

bool Game::insideBounds(const sf::Vector2f & position) const
{
	return mPlayBounds.contains(position);
}

sf::Vector2f Game::warpAround(const sf::Vector2f & position) const
{
	// warp even if on edge
	if (position.x <= mPlayBounds.left)
	{
		return{ mPlayBounds.width,position.y };
	}
	if (position.x >= mPlayBounds.left + mPlayBounds.width)
	{
		return{ mPlayBounds.left,position.y };
	}
	if (position.y <= mPlayBounds.top)
	{
		return{position.x, mPlayBounds.top + mPlayBounds.height };
	}
	if (position.y >= mPlayBounds.top + mPlayBounds.height)
	{
		return{ position.x, mPlayBounds.top };
	}
	assert(false);
	return position;
}

void Game::attachNode(GameObject::Ptr object)
{
	mRoot.attachNode(std::move(object));
}

GameObject::Ptr Game::detachNode(const GameObject & object)
{
	return mRoot.detachNode(object);
}

