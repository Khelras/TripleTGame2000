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

class CUILabel
{
public:
    CUILabel(const std::string& _sName, sf::Vector2f _vPosition, const std::string& _sText, const sf::Font& _font, int _iFontSize, sf::Color _color, bool _bCentered);

    const std::string& GetName() const { return m_sName; }

    void SetText(const std::string& _sText);
    void SetColor(sf::Color _color) { m_text.setFillColor(_color); }

    void Draw(sf::RenderWindow& window);

private:
    sf::Text m_text;
    std::string m_sName;
    sf::Vector2f m_vPosition;
    bool m_bCentered;

    void Reposition();
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

    CUILabel& AddLabel(EUIState _eState, const std::string& _sName, const std::string& _sText, float _fX, float _fY, int _iFontSize = 24, sf::Color _color = sf::Color::White, bool _bCentered = false);

    // Returns false if no label by that name exists.
    bool SetLabelText(const std::string& _sName, const std::string& _sText);
    bool SetLabelColor(const std::string& _sName, sf::Color _color);

    // nullptr if not found. Do not store this, SetupUI invalidates it.
    CUILabel* FindLabel(const std::string& _sName);

private:
    CUIManager() = default;
    CUIManager(const CUIManager&) = delete;
    CUIManager& operator=(const CUIManager&) = delete;

    static CUIManager* instance;

    // unique_ptr so the references handed out by AddButton stay valid
    std::vector<std::unique_ptr<CButton>> m_buttons[STATE_COUNT];
    std::vector<std::unique_ptr<CUILabel>> m_labels[STATE_COUNT];
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
