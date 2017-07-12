#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class SpriteObject : public GameObject
{
public:
    SpriteObject();
protected:
    void spriteInit(const std::string& filename, const sf::Rect<float>& desiredDimensions);
    sf::Texture mTexture;
    sf::Sprite mSprite;
private:
};
