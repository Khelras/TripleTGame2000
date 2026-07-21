#include "cLevelManager.h"
#include "cAudioManager.h"
#include <fstream> // Include fstream for reading

cLevelManager::cLevelManager()
{
	m_GlobalAudioManager = new cAudioManager();
}

cLevelManager::~cLevelManager()
{
	m_LevelFilePaths.push_back("Levels/Level1.txt");
	m_LevelIDFilePaths.push_back("Levels/Level1IDs.txt");
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
}

void cLevelManager::Update(float _deltatime)
{
}





int cLevelManager::GetCurrentLevelID()
{
	return m_CurrentLevelID;
}