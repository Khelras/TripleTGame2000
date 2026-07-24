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

private:
	cTextureManager();
	~cTextureManager();
};

