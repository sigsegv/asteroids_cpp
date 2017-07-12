#include "SpriteObject.hpp"
#include <cassert>
#include "Util.hpp"

SpriteObject::SpriteObject()
{
    
}

void SpriteObject::spriteInit(const std::string& filename, const sf::Rect<float>& desiredDimensions)
{
    assert(mTexture.loadFromFile(filename));
    mSprite.setTexture(mTexture);
    
    sf::FloatRect bounds = mSprite.getLocalBounds();
    const float scale = calcScaleFactor<float>(bounds, desiredDimensions);
    setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    setScale({ scale, scale });
}
