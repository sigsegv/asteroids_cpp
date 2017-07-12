#include "Game.hpp"
#include <random>
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Util.hpp"
#include "Math.h"

namespace
{

}

Game* Game::instance = 0;

Game::Game() :
    mAsteroids(0),
    mLevel(0)
{
	instance = this;
    for(std::size_t i = 0; i < SizeT(Layer::layerCount); ++i)
    {
        GameObject::Ptr layer(new GameObject());
        mLayers[i] = layer.get();
        mRoot.attachNode(std::move(layer));
    }
}

void Game::run()
{
	mWindow.create(sf::VideoMode(768, 576), "SFML Application");
	mPlayBounds.width = Float(mWindow.getSize().x);
	mPlayBounds.height = Float(mWindow.getSize().y);

	Player::Ptr player(new Player());
	mRoot.attachNode(std::move(player));

    nextLevel();

	sf::Clock clock;
	sf::Time kTimePerFrame = sf::milliseconds(17); // 60 FPS
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		if (mAsteroids == 0) nextLevel();
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

void Game::attachNode(GameObject::Ptr object, Layer layer)
{
    mLayers[SizeT(layer)]->attachNode(std::move(object));
}

GameObject::Ptr Game::detachNode(const GameObject & object)
{
	return mRoot.detachNode(object);
}

void Game::nextLevel()
{
    ++mLevel;
	mAsteroids = 0;
    
    // create throw away asteroid to see what radius a large one is
    const real_t largeAsteroidRadius = Asteroid::createAsteroid({0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, Asteroid::Size::large)->collider->radius;
    const real_t baseVelocity = 20.0f + (mLevel * 5.0f);
    const real_t widthHalf = mPlayBounds.width / 2.0f;
    const real_t heightHalf = mPlayBounds.height / 2.0f;
    const real_t maxEdge = std::max(widthHalf, heightHalf);
    const real_t maxHalfEdge = maxEdge / 2.0f;
    const real_t maxDistance = maxHalfEdge - largeAsteroidRadius;
    const uint_t numAsteroids = mLevel + 4;
    const real_t deltaRadian = 2.0f * PI / numAsteroids;
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<real_t> distribution(0, 1);
    real_t r =  distribution(generator) ;
    const real_t initialRadian = r * 2.0f * PI;
    for(uint_t i = 0; i < numAsteroids; ++i)
    {
        const real_t radian = initialRadian + (deltaRadian * i);
        real_t distance = maxDistance;
        sf::Vector2f position = (Vector2Utilf::fromAngle(radian) * distance) + sf::Vector2f(widthHalf, heightHalf);
        while(!mPlayBounds.contains(position))
        {
            distance -= largeAsteroidRadius;
            position = (Vector2Utilf::fromAngle(radian) * distance) + sf::Vector2f(widthHalf, heightHalf);
            
        }
        const real_t directionRadian = (distribution(generator) * 2.0f * PI);
        const real_t speed = distribution(generator) * 100.0f + baseVelocity;
        sf::Vector2f velocity = Vector2Utilf::fromAngle(directionRadian)  * speed;
        const real_t rotationalVelocity = (distribution(generator) * 30.0f) + 5.0f;
        mRoot.attachNode(Asteroid::createAsteroid(position, velocity, rotationalVelocity, Asteroid::Size::large));
		++mAsteroids;
    }
}

void Game::onAsteroidCreated()
{
	++mAsteroids;
}

void Game::onAsteroidDestroyed()
{
	assert(mAsteroids > 0);
	--mAsteroids;
}

void Game::onPlayerDestroyed()
{

}
