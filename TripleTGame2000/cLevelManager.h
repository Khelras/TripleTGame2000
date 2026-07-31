#pragma once

#include "SFML/Graphics.hpp"
#include "cGameObject.h"
#include <vector>
#include <string>
#include <box2d/box2d.h>
#include <memory>
#include "cCharacterController.h"

class cAudioManager;
class cTriggerObj;
class cTriggerableObj;

class cLevelManager
{
public:
	cLevelManager(cAudioManager* _AudioManager);
	~cLevelManager();


	//std::vector<EObjectType> m_DynamicObjectsToSpawn;
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
	//cPlayer* GetPlayerPointer();

	//// Purpose: Retrieves the level type
	//LevelType GetLevelType();

	//// Purpose: Retrieves the physics manager
	//cPhysicsManager* GetPhysicsManager();

	// Purpose: Retrieves the current level ID
	int GetCurrentLevelID();

	// Purpose: Retrieves the vector of triggerable objects
	std::vector<std::shared_ptr<cTriggerableObj>> GetTriggerablesVec();

	//// Purpose: Sets the player pointer
	//oid SetPlayerPointer(cPlayer* _player);


private:
	// Purpose: Loads the IDs for the specified level ID
	void LoadIDChars(int _levelID);

	// Purpose: Creates all actors in the level
	void CreateActors();

	// Purpose: Connects triggerable objects to the triggers in the level
	void ConnectTriggerables();

	//// Purpose: Spawns dynamic objects in the level
	//void SpawnDynamicObjects();

	// Purpose: Creates a static body in the Box2D world at the specified position and size
	void CreateStaticBody(const sf::Vector2f& position, const sf::Vector2f& size);
	void CreateMergedStaticObjects(); // Merges adjacent static bodies into a single body

	std::vector<std::shared_ptr<cGameObject>> m_GameObjects;
	std::vector<std::shared_ptr<cTriggerObj>> m_TriggerObjects;
	std::vector<std::shared_ptr<cTriggerableObj>> m_TriggerableObjects;

	//cPlayer* m_PlayerPointer;
	//cNextLevelBlock* m_NextLevelBlockPointer;
	//LevelType m_LevelType;
	//cPhysicsManager* m_GlobalPhysicsManager;

	cAudioManager* m_GlobalAudioManager;

	int m_CurrentLevelID;

	//make a unique pointer to the player character controllers
	std::unique_ptr <cCharacterController> m_Rock;
	std::unique_ptr <cCharacterController> m_Air;

	b2World m_world{ b2Vec2(0.0f, 0.0f) }; // Initialize Box2D world with zero gravity

	std::vector<b2Body*> m_staticBodies; // Store static bodies for cleanup

};