#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>



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



	void PollWindow();
	void WindowDraw();


	inline float GetDeltaTime() { return m_DeltaTime; }

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

	//// ~ CAMERAS
	//cCamera* m_MainCamera;
};

