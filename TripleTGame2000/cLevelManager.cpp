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


			sf::Vector2f CurrentSpawnPosition = sf::Vector2f(x * TileSize, y * TileSize);
			bool TriggerOnActivate = true;
			bool IsntDynamic = false;
			bool IsDynamic = true;
			sAnimationInfo AnimInfo(0, 0, 7, 0, 12.0f);

			switch (m_LoadedLevelChars[y * LevelWidth + x])
			{
				// LabTile (X)
				case 'X':
					NewActor = std::make_shared<cCube>(cTextureManager::GetInstance().m_CubeTex, IsDynamic);
					NewActor->SetPosition(CurrentSpawnPosition);
					//NewActor->SetSpawnPosition(CurrentSpawnPosition);

					m_GameObjects.push_back(NewActor);
					break;

					// DissapearingPlatform (T)
				case 'T':
					
					NewActor = std::make_shared<cCube>(cTextureManager::GetInstance().m_TestAnimTex, IsDynamic, AnimInfo, 32, 32);
					NewActor->SetPosition(CurrentSpawnPosition);
					//NewActor->SetSpawnPosition(CurrentSpawnPosition);

					m_GameObjects.push_back(NewActor);
					break;

				default:
					break;
			}

		}
	}

	//SpawnDynamicObjects();
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

void cLevelManager::Update(float _deltatime)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Update(_deltatime);
	}
}

void cLevelManager::Draw(sf::RenderWindow* _window)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		_window->draw(m_GameObjects[i]->GetSprite());
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
