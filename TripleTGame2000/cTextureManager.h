#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class cTextureManager
{
public:

	// SINGLETON
	static cTextureManager& GetInstance()
	{
		static cTextureManager Instance; // created only once since its static
		return Instance;
	}

	std::shared_ptr<sf::Texture> m_CubeTex;
	std::shared_ptr<sf::Texture> m_TestAnimTex;

	//air and rock textures
	std::shared_ptr<sf::Texture> m_AirTex;
	std::shared_ptr<sf::Texture> m_RockTex;

private:
	cTextureManager();
	~cTextureManager();

	// Delete copy constructor and assignment operator to prevent copying
	cTextureManager(const cTextureManager&) = delete;
	cTextureManager& operator=(const cTextureManager&) = delete;
};

