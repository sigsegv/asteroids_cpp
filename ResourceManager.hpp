#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

/**
 * Manages resources
 */
class ResourceManager
{
public:
	static ResourceManager* instance;
    
    ResourceManager();

    sf::Texture& getTextureFromFile(const std::string& filename);
private:

	using TexturePtr = std::unique_ptr<sf::Texture>;

	TexturePtr loadTextureFromFile(const std::string& filename);
	
	std::unordered_map<unsigned int, TexturePtr> mTextures;
};
