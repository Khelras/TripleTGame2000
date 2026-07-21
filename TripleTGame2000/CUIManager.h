/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : CUIManager.h
Description : Header file for the UI Manager for handling different UI states
Author : Bryn Carter
Mail : bryn.carter@mds.ac.nz
**************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "CButton.h"

enum EUIState
{
    MENU,
    LEVEL_SELECT,
    SETTINGS,
    GAME,
    LEVEL_COMPLETE,
    STATE_COUNT // Get the size
};

class CUIManager
{
public:
    static CUIManager* getInstance();

    bool LoadFont(const std::string& _sFontPath);

    // Builds every screen. Call once after LoadFont, and again after a resize.
    void SetupUI(sf::Vector2u _vWindowSize);

    void HandleEvent(sf::RenderWindow& window);
    void Update(float _dT);
    void Draw(sf::RenderWindow& window);

    void SetState(EUIState _eNewState) { m_eCurrentState = _eNewState; }
    EUIState GetCurrentState() const { return m_eCurrentState; }

    // Set when Quit is pressed.
    bool WantsToQuit() const { return m_bQuit; }

    // Which level the player picked on the level select screen.
    int GetSelectedLevel() const { return m_iSelectedLevel; }

    CButton& AddButton(EUIState _eState, const std::string& _sText, sf::Color _color, std::function<void()> _onClick = nullptr);

private:
    CUIManager() = default;
    CUIManager(const CUIManager&) = delete;
    CUIManager& operator=(const CUIManager&) = delete;

    static CUIManager* instance;

    // unique_ptr so the references handed out by AddButton stay valid
    std::vector<std::unique_ptr<CButton>> m_buttons[STATE_COUNT];
    std::string m_titles[STATE_COUNT];

    EUIState m_eCurrentState = MENU;
    sf::Font m_font;
    bool m_bQuit = false;
    int m_iSelectedLevel = 1;

    // Settings values the UI shows. Read these from your game code.
    bool m_bVSync = true;
    int m_iVolume = 100;

    sf::Vector2u m_vWindowSize = { 800, 600 };
    float m_fNextButtonY[STATE_COUNT] = {}; // where the next button goes

    void DrawTitle(sf::RenderWindow& window);
};
