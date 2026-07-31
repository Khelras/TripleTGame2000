#include "cLevelManager.h"
#include "cAudioManager.h"
#include "cTextureManager.h"
#include <fstream> // Include fstream for reading

// GameObject includes so LevelManager can spawn them
#include "cTriggerableObj.h"
#include "cTriggerObj.h"
#include "cCube.h"

cLevelManager::cLevelManager(cAudioManager* _AudioManager)
{
	m_GlobalAudioManager = _AudioManager;
	m_CurrentLevelID = 0;

	m_LevelFilePaths.push_back("Levels/Level1.txt");
	m_LevelIDFilePaths.push_back("Levels/Level1IDs.txt");
}

cLevelManager::~cLevelManager()
{
}



// ~~~~~ -= LEVEL LOADING =- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cLevelManager::LoadLevel(int _levelID)
{
	Unloadlevel();
	LoadIDChars(_levelID);

	m_CurrentLevelID = _levelID;

	std::fstream LoadFileStream;
	LoadFileStream.open(m_LevelFilePaths[_levelID], std::ios::in);

	std::string LoadFileString;
	LevelWidth = 0;
	LevelHeight = 0;

	if (LoadFileStream.is_open())
	{
		while (std::getline(LoadFileStream, LoadFileString))
		{
			if (LevelWidth == 0) {
				LevelWidth = std::size(LoadFileString);
			}
			assert(std::size(LoadFileString) == LevelWidth);

			for (int i = 0; i < std::size(LoadFileString); i++)
			{
				m_LoadedLevelChars.push_back(LoadFileString[i]);
			}
			LevelHeight++;
		}
		LoadFileStream.close();
	}
	CreateActors();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cLevelManager::LoadIDChars(int _levelID)
{
	std::fstream LoadFileStream;
	LoadFileStream.open(m_LevelIDFilePaths[_levelID], std::ios::in);

	std::string LoadFileString;
	LevelWidth = 0;
	LevelHeight = 0;

	if (LoadFileStream.is_open())
	{
		while (std::getline(LoadFileStream, LoadFileString))
		{
			if (LevelWidth == 0) {
				LevelWidth = std::size(LoadFileString);
			}
			assert(std::size(LoadFileString) == LevelWidth);

			for (int i = 0; i < std::size(LoadFileString); i++)
			{
				m_LevelIDChars.push_back(LoadFileString[i]);
			}
			LevelHeight++;
		}
		LoadFileStream.close();
	}
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cLevelManager::Unloadlevel()
{
	// Destroy the Box2D world and reset the unique pointers for the player characters
	m_Rock.reset();
	m_Air.reset();

	for (b2Body* body : m_staticBodies)
	{
		if (body != nullptr)
		{
			m_world.DestroyBody(body);
		}
	}

	m_staticBodies.clear();  // Clear the vector of static bodies

	// Clear vectors
	m_GameObjects.clear();
	m_LoadedLevelChars.clear();
	m_LevelIDChars.clear();
	m_TriggerObjects.clear();
	m_TriggerableObjects.clear();
	//m_DynamicObjectsToSpawn.clear();
	//m_DynamicObjectSpawnLocations.clear();




	LevelWidth = 0;
	LevelHeight = 0;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


void cLevelManager::CreateActors()
{
	int TileSize = 32;
	for (int y = 0; y < LevelHeight; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			// Actor Pointers & Other Variables
			std::shared_ptr<cGameObject> NewActor = nullptr;


			sf::Vector2f CurrentSpawnPosition(x * TileSize + TileSize * 0.5f, y * TileSize + TileSize * 0.5f);
			bool TriggerOnActivate = true;
			bool IsntDynamic = false;
			bool IsDynamic = true;
			sAnimationInfo TestAnimInfo(0, 0, 7, 0, 12.0f);

			switch (m_LoadedLevelChars[y * LevelWidth + x])
			{
				// Cube (X)
				case 'X':
					NewActor = std::make_shared<cCube>(cTextureManager::GetInstance().m_CubeTex, IsntDynamic);
					NewActor->SetPosition(CurrentSpawnPosition);
					//NewActor->SetSpawnPosition(CurrentSpawnPosition);

					m_GameObjects.push_back(NewActor);

					break;

				// DissapearingPlatform (T)
				case 'T':
					
					NewActor = std::make_shared<cCube>(cTextureManager::GetInstance().m_TestAnimTex, IsDynamic, TestAnimInfo, 32, 32);
					NewActor->SetPosition(CurrentSpawnPosition);
					//NewActor->SetSpawnPosition(CurrentSpawnPosition);

					m_GameObjects.push_back(NewActor);
					break;

				case 'R':
					// Rock (R)
					m_Rock = std::make_unique<cCharacterController>(m_world, CurrentSpawnPosition, PLAYER_ONE, EGravityDirection::Horizontal, cTextureManager::GetInstance().m_RockTex);
					
					break;

				case 'A':
					// Air (A)
					m_Air = std::make_unique<cCharacterController>(m_world, CurrentSpawnPosition, PLAYER_TWO, EGravityDirection::Vertical, cTextureManager::GetInstance().m_AirTex);
					
					break;

				default:
					break;
			}

		}
	}

	//SpawnDynamicObjects();
	CreateMergedStaticObjects();
	ConnectTriggerables();
}

void cLevelManager::ConnectTriggerables()
{
	for (int i = 0; i < m_TriggerableObjects.size(); i++)
	{
		int CurrentID = m_TriggerableObjects[i]->GetID();

		// Connect Every Trigger that has the same ID
		for (int j = 0; j < m_TriggerObjects.size(); j++)
		{
			if (CurrentID == m_TriggerObjects[j]->GetID())
			{
				m_TriggerObjects[j]->SetConnectedActor(m_TriggerableObjects[i]);
			}
		}
	}
}
void cLevelManager::CreateStaticBody(const sf::Vector2f& position, const sf::Vector2f& size)
{
	const float PixelsPerMeter = 32.0f; // Conversion factor from pixels to meters
	const float TileSize = 32.0f; // Assuming each tile is 32 pixels

	//init body definition and type
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	// Set the position of the static body in Box2D world coordinates (meters)
	bodyDef.position.Set(position.x / PixelsPerMeter, position.y / PixelsPerMeter);

	b2Body* staticBody = m_world.CreateBody(&bodyDef);
	b2PolygonShape shape;

	// Set the shape of the static body (a box) in Box2D world coordinates (meters)
	shape.SetAsBox(size.x / (2 * PixelsPerMeter), size.y / (2 * PixelsPerMeter)); // Half-width and half-height

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.0f; // Set friction if needed
	fixtureDef.density = 1.0f; // Set density if needed
	fixtureDef.restitution = 0.0f; // Set restitution (bounciness) if needed

	staticBody->CreateFixture(&fixtureDef);

	m_staticBodies.push_back(staticBody); // Store the static body for cleanup later

}
void cLevelManager::CreateMergedStaticObjects()
{
	int TileSize = 32;

	std::vector<bool> used(LevelWidth * LevelHeight, false); // Keep track of which tiles have been merged

	for (int y = 0; y < LevelHeight; y++) // Iterate through each row of the level
	{
		for (int x = 0; x < LevelWidth; x++) // Iterate through each column of the level
		{
			if (m_LoadedLevelChars[y * LevelWidth + x] == 'X') // If the current tile is a static tile
			{
				int startIndex = y * LevelWidth + x;

				if (m_LoadedLevelChars[startIndex] != 'X' || used[startIndex]) // If the tile is not a static tile or has already been merged, skip it
				{
					continue;
				}

				// Find the width and height of the merged static object
				int width = 1;
				int height = 1;
				// Check for horizontal merge
				while (x + width < LevelWidth)
				{
					int index = y * LevelWidth * x + width;

					if (m_LoadedLevelChars[index] != 'X' || used[index])
					{
						break;
					}

					++width;
				}
				// Check for vertical merge
				bool canMergeVertically = true;
				
				//Expand Downwards onlty if the entire next row is mergeable
				while (y + height < LevelHeight && canMergeVertically)
				{
					for (int i = 0; i < width; ++i)
					{
						int index = (y + height) * LevelWidth + (x + i);
						if (m_LoadedLevelChars[index] != 'X' || used[index])
						{
							canMergeVertically = false;
							break;
						}
					}
					if (canMergeVertically)
					{
						++height;
					}
				}

				// Mark the merged tiles as used
				for (int dy = 0; dy < height; ++dy)
				{
					for (int dx = 0; dx < width; ++dx)
					{
						int index = (y + dy) * LevelWidth + (x + dx);
						used[index] = true;
					}
				}

				// Create a single static body for the merged object
				float widthPixels = static_cast<float>(width * TileSize);
				float heightPixels = static_cast<float>(height * TileSize);
				sf::Vector2f mergedPosition(x * TileSize + widthPixels * 0.5f, y * TileSize + heightPixels * 0.5f);
				sf::Vector2f mergedSize(widthPixels, heightPixels);

				CreateStaticBody(mergedPosition, mergedSize);
			}
		}
	}
}
/// <summary> Update all m_GameObjects /// </summary>
void cLevelManager::Update(float _deltatime)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Update(_deltatime);
	}

	CInputHandler* inputHandler = CInputHandler::getInstance();

	const sf::Vector2f rockInput = inputHandler->InputVector(PLAYER_ONE);
	const sf::Vector2f airInput = inputHandler->InputVector(PLAYER_TWO);

	if (m_Rock)
	{
		m_Rock->Update(_deltatime, rockInput);
	}

	if (m_Air)
	{
		m_Air->Update(_deltatime, airInput);
	}

	m_world.Step(_deltatime, 8, 3); // Step the Box2D world with the given delta time

	m_Rock->UpdateVisuals(_deltatime);
	m_Air->UpdateVisuals(_deltatime);
}

void cLevelManager::Draw(sf::RenderWindow* _window)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		_window->draw(m_GameObjects[i]->GetSprite());
	}

	if (m_Rock)
	{
		m_Rock->DrawCharacters(*_window);
	}

	if (m_Air)
	{
		m_Air->DrawCharacters(*_window);
	}
}

int cLevelManager::GetCurrentLevelID()
{
	return m_CurrentLevelID;
}

std::vector<std::shared_ptr<cTriggerableObj>> cLevelManager::GetTriggerablesVec()
{
	return m_TriggerableObjects;
}
