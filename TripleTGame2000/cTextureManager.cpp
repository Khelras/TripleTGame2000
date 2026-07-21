#include "cTextureManager.h"

cTextureManager::cTextureManager()
{
	// Cube Tex
	m_CubeTex = std::make_shared<sf::Texture>();
	if (!m_CubeTex->loadFromFile("Sprites/LabTile1.png"))
		std::cout << "Failed to load - " << "SSprites/LabTile1.png\n";
}

cTextureManager::~cTextureManager()
{
}
