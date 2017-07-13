#pragma once

#include "Scab.hpp"
#include "GameObject.hpp"

class SpriteObject : public GameObject
{
public:
    SpriteObject();
    SpriteObject(const std::string& filename, const sf::Rect<float>& desiredDimensions);
protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;    
    void spriteInit(const std::string& filename, const sf::Rect<float>& desiredDimensions);

    sf::Sprite mSprite;
private:
};
