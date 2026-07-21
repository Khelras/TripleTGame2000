/*
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : CInputHandler.h
Description : Header file that defines the CInputHandler singleton class responsible for processing keyboard and mouse input states within the game window
Author : Bryn Carter
Mail : bryn.carter@mds.ac.nz
*/
#pragma once
#include <array>
#include "SFML/Graphics.hpp"

enum EPlayer
{
	PLAYER_ONE,
	PLAYER_TWO,
	PLAYER_COUNT // Get the size
};

// Which keys drive a player
struct SBindings
{
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key action;
};

class CInputHandler
{
private:
	static CInputHandler* instance;
	~CInputHandler();

	CInputHandler(const CInputHandler&) = delete;
	CInputHandler& operator=(const CInputHandler&) = delete;

	sf::RenderWindow* m_window = nullptr;
	sf::Vector2i m_mousePosPixels{ 0,0 };

	std::array<bool, sf::Mouse::ButtonCount> m_mouseDown{};
	std::array<bool, sf::Mouse::ButtonCount> m_prevMouseDown{};
	std::array<bool, sf::Mouse::ButtonCount> m_mousePressed{};
	std::array<bool, sf::Mouse::ButtonCount> m_mouseReleased{};

	std::array<bool, sf::Keyboard::KeyCount> m_keyDown{};
	std::array<bool, sf::Keyboard::KeyCount> m_prevKeyDown{};
	std::array<bool, sf::Keyboard::KeyCount> m_keyPressed{};
	std::array<bool, sf::Keyboard::KeyCount> m_keyReleased{};

	SBindings m_bindings[PLAYER_COUNT];
	sf::Vector2f m_vInputVector[PLAYER_COUNT];

	// sf::Keyboard::Key::Unknown is -1, so every lookup has to be range checked
	static bool IsValidKey(sf::Keyboard::Key key)
	{
		return int(key) >= 0 && int(key) < int(sf::Keyboard::KeyCount);
	}

public:
	CInputHandler();
	static CInputHandler* getInstance();
	void SetWindow(sf::RenderWindow* window) { m_window = window; }
	sf::RenderWindow* GetWindow() const { return m_window; }

	void UpdateInput();
	void UpdateMousePos(sf::RenderWindow& window);
	sf::Vector2i MousePixels() const { return m_mousePosPixels; }

	// Movement for one player, x and y each -1, 0 or 1
	sf::Vector2f InputVector(EPlayer player) const { return m_vInputVector[player]; }

	// That player's action key, so game code never hardcodes a key
	bool ActionHeld(EPlayer player) const { return KeyHeld(m_bindings[player].action); }
	bool ActionPressed(EPlayer player) const { return KeyPressed(m_bindings[player].action); }
	bool ActionReleased(EPlayer player) const { return KeyReleased(m_bindings[player].action); }

	// Rebind a player at runtime, e.g. from a controls menu
	void SetBindings(EPlayer player, const SBindings& bindings) { m_bindings[player] = bindings; }
	const SBindings& GetBindings(EPlayer player) const { return m_bindings[player]; }

	bool KeyHeld(sf::Keyboard::Key key) const { return IsValidKey(key) && m_keyDown[int(key)]; }
	bool KeyPressed(sf::Keyboard::Key key) const { return IsValidKey(key) && m_keyPressed[int(key)]; }
	bool KeyReleased(sf::Keyboard::Key key) const { return IsValidKey(key) && m_keyReleased[int(key)]; }

	bool MouseHeld(sf::Mouse::Button button) const { return m_mouseDown[int(button)]; }
	bool MousePressed(sf::Mouse::Button button) const { return m_mousePressed[int(button)]; }
	bool MouseReleased(sf::Mouse::Button button) const { return m_mouseReleased[int(button)]; }

};

