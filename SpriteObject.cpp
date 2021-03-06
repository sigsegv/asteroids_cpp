#include "SpriteObject.hpp"
#include <cassert>
#include "Util.hpp"
#include "ResourceManager.hpp"

SpriteObject::SpriteObject()
{
    
}

SpriteObject::SpriteObject(const std::string& filename, const sf::Rect<float>& desiredDimensions)
{
    spriteInit(filename, desiredDimensions);
}

void SpriteObject::spriteInit(const std::string& filename, const sf::Rect<float>& desiredDimensions)
{
    mSprite.setTexture(ResourceManager::instance->getTextureFromFile(filename));
    
    sf::FloatRect bounds = mSprite.getLocalBounds();
    const float scale = calcScaleFactor<float>(bounds, desiredDimensions);
    setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setScale({ scale, scale });
}

void SpriteObject::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
