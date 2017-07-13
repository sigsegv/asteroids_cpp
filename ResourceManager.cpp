#include "ResourceManager.hpp"
#include <cassert>
#include "Util.hpp"

ResourceManager* ResourceManager::instance = 0;

ResourceManager::ResourceManager()
{
    ResourceManager::instance = this;
}

sf::Texture& ResourceManager::getTextureFromFile(const std::string& filename)
{
    unsigned int hash = hashString(filename);
    if(!mTextures.count(hash))
    {
        mTextures[hash] = loadTextureFromFile(filename);
    }
    return *mTextures[hash].get();
}

ResourceManager::TexturePtr ResourceManager::loadTextureFromFile(const std::string& filename)
{
    TexturePtr texture = std::make_unique<sf::Texture>();
    if(!texture->loadFromFile(filename)) throw std::runtime_error("[ERROR] Failed to load " + filename);
    return texture;
}
