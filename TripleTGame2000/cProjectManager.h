#pragma once

#include <SFML/Graphics.hpp>
#include "cLevelManager.h"
#include "cAudioManager.h"
#include <iostream>
#include <vector>
#include <string>
#include "CUIManager.h"

class cCamera;

class cProjectManager
{
public:

	// SINGLETON
	static cProjectManager& GetInstance()
	{
		static cProjectManager Instance; // created only once since its static
		return Instance;
	}

	void Start();
	void RunProgram();
	void Update();

	// Runs the game itself, only while the UI is in the GAME state
	void UpdateGame();

	void PollWindow();
	void WindowDraw();


	inline float GetDeltaTime() { return m_DeltaTime; }
	inline float GetLevelTime() { return m_LevelTime; }

private:
	cProjectManager();
	~cProjectManager();

	sf::RenderWindow m_Window;
	sf::RenderWindow m_DebugWindow;
	static const unsigned int m_WindowWidth = 1280;
	static const unsigned int m_WindowHeight = 950;

	// ~ DELTATIME
	sf::Clock m_Clock;
	float m_DeltaTime;

	// ~ LEVEL TIMER
	float m_LevelTime; // seconds left in the current level
	float m_LevelTimeLimit = 60.0f; // what it resets to when a level starts
	EUIState m_LastUIState = MENU; // so we can tell when a level begins

	//// ~ CAMERAS
	cCamera* m_MainCamera;

	cAudioManager m_GlobalAudioManager;
	cLevelManager* m_LevelManager;
};

