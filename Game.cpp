#include "Game.hpp"
#include <random>
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Util.hpp"

namespace
{

}

Game* Game::instance = 0;

Game::Game() :
    mAsteroids(0),
    mLevel(0)
{
	instance = this;
}

void Game::run()
{
	mWindow.create(sf::VideoMode(1280, 960), "SFML Application");
	mPlayBounds.width = Float(mWindow.getSize().x);
	mPlayBounds.height = Float(mWindow.getSize().y);

    nextLevel();

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

void Game::nextLevel()
{
    ++mLevel;
    
    Player::Ptr player(new Player());
    mRoot.attachNode(std::move(player));
    
    // create throw away asteroid to see what radius a large one is
    const real_t largeAsteroidRadius = Asteroid::createAsteroid({0.0, 0.0}, {0.0, 0.0}, 0.0, Asteroid::Size::large)->collider->radius;
    const real_t baseVelocity = 20.0 + (mLevel * 5.0);
    const real_t widthHalf = mPlayBounds.width / 2.0;
    const real_t heightHalf = mPlayBounds.height / 2.0;
    const real_t maxEdge = std::max(widthHalf, heightHalf);
    const real_t maxHalfEdge = maxEdge / 2.0;
    const real_t maxDistance = maxHalfEdge - largeAsteroidRadius;
    const uint_t numAsteroids = mLevel + 4;
    const real_t deltaRadian = 2.0 * M_PI / numAsteroids;
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<> distribution(0, 1);
    real_t r =  distribution(generator) ;
    const real_t initialRadian = r * 2.0 * M_PI;
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
        const real_t directionRadian = (distribution(generator) * 2.0 * M_PI);
        const real_t speed = distribution(generator) * 100.0 + baseVelocity;
        sf::Vector2f velocity = Vector2Utilf::fromAngle(directionRadian)  * speed;
        const real_t rotationalVelocity = (distribution(generator) * 30.0) + 5.0;
        mRoot.attachNode(Asteroid::createAsteroid(position, velocity, rotationalVelocity, Asteroid::Size::large));
    }
}
