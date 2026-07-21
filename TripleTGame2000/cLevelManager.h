#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include "string"

class cAudioManager;

class cLevelManager
{
public:
	cLevelManager();
	~cLevelManager();

	//std::vector<cActor*> m_Actors;
	//std::vector<cTriggerActor*> m_TriggerActors;
	//std::vector<cTriggerableActor*> m_TriggerableActors;

	//std::vector<ActorType> m_DynamicObjectsToSpawn;
	std::vector<sf::Vector2f> m_DynamicObjectSpawnLocations;

	std::vector<char> m_LoadedLevelChars;
	std::vector<char> m_LevelIDChars;

	std::vector<std::string> m_LevelFilePaths;
	std::vector<std::string> m_LevelIDFilePaths;

	int LevelWidth = 0;
	int LevelHeight = 0;


	// Purpose: Loads the level with the specified ID
	void LoadLevel(int _levelID);


	// Purpose: Unloads the current level
	void Unloadlevel();

	// Purpose: Draws the actors to the specified window
	void Draw(sf::RenderWindow* _window);

	// Purpose: Updates the level
	void Update(float _deltatime);

	//// Purpose: Retrieves the player pointer
	//// Return: A pointer to the player
	//cPlayer* GetPlayerPointer();

	//// Purpose: Retrieves the level type
	//// Return: The level type
	//LevelType GetLevelType();

	//// Purpose: Retrieves the physics manager
	//// Return: A pointer to the physics manager
	//cPhysicsManager* GetPhysicsManager();

	// Purpose: Retrieves the current level ID
	// Return: The level ID
	int GetCurrentLevelID();

	//// Purpose: Retrieves the vector of triggerable actors
	//// Return: A vector of triggerable actor pointers
	//std::vector<cTriggerableActor*> GetTriggerablesVec();

	//// Purpose: Sets the player pointer
	//void SetPlayerPointer(cPlayer* _player);


private:
	// Purpose: Loads the IDs for the specified level ID
	void LoadIDChars(int _levelID);

	// Purpose: Creates all actors in the level
	void CreateActors();

	// Purpose: Connects triggerable actors to the triggers in the level
	void ConnectTriggerActors();

	// Purpose: Spawns dynamic objects in the level
	void SpawnDynamicObjects();


	//cPlayer* m_PlayerPointer;
	//cNextLevelBlock* m_NextLevelBlockPointer;
	//LevelType m_LevelType;
	//cPhysicsManager* m_GlobalPhysicsManager;
	cAudioManager* m_GlobalAudioManager;

	int m_CurrentLevelID;
};