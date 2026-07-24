#include "cTextureManager.h"

cTextureManager::cTextureManager()
{
	// Cube Tex
	m_CubeTex = std::make_shared<sf::Texture>();
	if (!m_CubeTex->loadFromFile("Sprites/LabTile1.png"))
		std::cout << "Failed to load - " << "SSprites/LabTile1.png\n";

	// TestAnim Tex
	m_TestAnimTex = std::make_shared<sf::Texture>();
	if (!m_TestAnimTex->loadFromFile("Sprites/DissapearingPlatform.png"))
		std::cout << "Failed to load - " << "SSprites/DissapearingPlatform.png\n";
}

cTextureManager::~cTextureManager()
{
}
