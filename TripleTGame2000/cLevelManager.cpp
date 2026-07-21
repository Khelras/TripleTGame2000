#include "cLevelManager.h"
#include "cAudioManager.h"
#include "cTextureManager.h"
#include <fstream> // Include fstream for reading

// GameObject includes so LevelManager can spawn them
#include "cCube.h"

cLevelManager::cLevelManager(cAudioManager* _audiomanager)
{
	m_GlobalAudioManager = _audiomanager;
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
				LevelWidth = LoadFileString.size();
			}
			assert(LoadFileString.size() == LevelWidth);

			for (int i = 0; i < LoadFileString.size(); i++)
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
				LevelWidth = LoadFileString.size();
			}
			assert(LoadFileString.size() == LevelWidth);

			for (int i = 0; i < LoadFileString.size(); i++)
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
	//// Clear Actors
	//for (int i = 0; i < m_Actors.size(); i++)
	//{
	//	delete m_Actors[i];
	//	m_Actors[i] = nullptr;
	//}
	//m_Actors.clear();

	// Clear vectors
	m_LoadedLevelChars.clear();
	m_LevelIDChars.clear();
	//m_TriggerActors.clear();
	//m_TriggerableActors.clear();
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
			cGameObject* NewActor = nullptr;


			sf::Vector2f CurrentSpawnPosition = sf::Vector2f(x * TileSize, y * TileSize);
			bool TriggerOnActivate = true;
			bool IsntDynamic = false;
			bool IsDynamic = true;


			switch (m_LoadedLevelChars[y * LevelWidth + x])
			{
				// LabTile (X)
				case 'X':
					NewActor = new cCube(cTextureManager::GetInstance().m_CubeTex, IsDynamic);
					NewActor->SetPosition(CurrentSpawnPosition);
					//NewActor->SetSpawnPosition(CurrentSpawnPosition);

					m_Actors.push_back(NewActor);
					break;

				default:
					break;
			}
		}
	}

	//SpawnDynamicObjects();
	//ConnectTriggerActors();
}

void cLevelManager::Update(float _deltatime)
{
}

void cLevelManager::Draw(sf::RenderWindow* _window)
{
	for (int i = 0; i < m_Actors.size(); i++)
	{
		_window->draw(m_Actors[i]->GetSprite());
	}
}





int cLevelManager::GetCurrentLevelID()
{
	return m_CurrentLevelID;
}