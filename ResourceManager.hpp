#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

/**
 * Manages resources
 */
class ResourceManager
{
public:
	static ResourceManager& instance();

	sf::Texture& getTexture(int id);
	sf::Image& getImage(int id);
private:
	//static ResourceManager* sInstance;
	//static sf::Mutex sMutex;

	using TexturePtr = std::unique_ptr<sf::Texture>;
	using ImagePtr = std::unique_ptr<sf::Texture>;

	TexturePtr loadTexture(int id);
	
	std::map<int, TexturePtr> mTextures;
	std::map<int, ImagePtr> mImages;
};