/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : CUIManager.cpp
Description : Manages all UI states, buttons, and menus, handling input, drawing, and transitions between screens
Author : Bryn Carter
Mail : bryn.carter@mds.ac.nz
**************************************************************************/

#include "CUIManager.h"
#include <iostream>

CUIManager* CUIManager::instance = nullptr;

// How many levels the level select screen offers
static const int LEVEL_COUNT = 6;

CUILabel::CUILabel(const std::string& _sName, sf::Vector2f _vPosition, const std::string& _sText, const sf::Font& _font, int _iFontSize, sf::Color _color, bool _bCentered) : m_text(_font, _sText, _iFontSize), m_sName(_sName), m_vPosition(_vPosition), m_bCentered(_bCentered)
{
    m_text.setFillColor(_color);
    Reposition();
}

void CUILabel::SetText(const std::string& _sText)
{
    m_text.setString(_sText);
    Reposition(); // a centred label has to re-centre when the text length changes
}

void CUILabel::Draw(sf::RenderWindow& window)
{
    window.draw(m_text);
}

void CUILabel::Reposition()
{
    sf::FloatRect bounds = m_text.getLocalBounds();

    if (m_bCentered)
    {
        m_text.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
    }
    else
    {
        m_text.setOrigin({ bounds.position.x, bounds.position.y });
    }

    m_text.setPosition(m_vPosition);
}

CUIManager* CUIManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CUIManager();
    }
    return instance;
}

bool CUIManager::LoadFont(const std::string& _sFontPath)
{
    if (!m_font.openFromFile(_sFontPath))
    {
        std::cout << "Warning: could not load font from " << _sFontPath << "\n";
        return false;
    }
    return true;
}

CButton& CUIManager::AddButton(EUIState _eState, const std::string& _sText, sf::Color _color, std::function<void()> _onClick)
{
    float width = m_vWindowSize.x / 6.0f;
    float height = m_vWindowSize.y / 12.0f;
    float centerX = m_vWindowSize.x / 2.0f;

    sf::Vector2f position(centerX, m_fNextButtonY[_eState]);

    // Next button sits below this shit
    m_fNextButtonY[_eState] += height * 1.15f;

    m_buttons[_eState].push_back(std::make_unique<CButton>(position, sf::Vector2f(width, height), _color, _sText, m_font, 24, std::move(_onClick)));

    return *m_buttons[_eState].back();
}

CUILabel& CUIManager::AddLabel(EUIState _eState, const std::string& _sName, const std::string& _sText, float _fX, float _fY, int _iFontSize, sf::Color _color, bool _bCentered)
{
    sf::Vector2f position(m_vWindowSize.x * _fX, m_vWindowSize.y * _fY);

    m_labels[_eState].push_back(std::make_unique<CUILabel>(
        _sName, position, _sText, m_font, _iFontSize, _color, _bCentered));

    return *m_labels[_eState].back();
}

CUILabel* CUIManager::FindLabel(const std::string& _sName)
{
    for (int i = 0; i < STATE_COUNT; i++)
    {
        for (auto& label : m_labels[i])
        {
            if (label->GetName() == _sName)
                return label.get();
        }
    }
    return nullptr;
}

bool CUIManager::SetLabelText(const std::string& _sName, const std::string& _sText)
{
    CUILabel* label = FindLabel(_sName);
    if (label == nullptr) return false;

    label->SetText(_sText);
    return true;
}

bool CUIManager::SetLabelColor(const std::string& _sName, sf::Color _color)
{
    CUILabel* label = FindLabel(_sName);
    if (label == nullptr) return false;

    label->SetColor(_color);
    return true;
}

void CUIManager::SetupUI(sf::Vector2u _vWindowSize)
{
    m_vWindowSize = _vWindowSize;

    // Clear out any previous layout (so this can be called again on resize)
    for (int i = 0; i < STATE_COUNT; i++)
    {
        m_buttons[i].clear();
        m_labels[i].clear();
        m_fNextButtonY[i] = m_vWindowSize.y * 0.28f;
    }

    const sf::Color BLUE = sf::Color(60, 160, 255);
    const sf::Color GREEN = sf::Color(60, 200, 60);
    const sf::Color GREY = sf::Color(100, 100, 100);
    const sf::Color RED = sf::Color(200, 60, 60);

    // Main Menu
    m_titles[MENU] = "Triple T Game";

    AddButton(MENU, "Play", BLUE, [this]()
    {
        SetState(GAME);
    });

    AddButton(MENU, "Level Select", GREEN, [this]()
    {
        SetState(LEVEL_SELECT);
    });

    AddButton(MENU, "Settings", GREY, [this]()
    {
        SetState(SETTINGS);
    });

    AddButton(MENU, "Quit", RED, [this]()
    {
        m_bQuit = true;
    });

    // Level
    m_titles[LEVEL_SELECT] = "Select Level";

    for (int level = 1; level <= LEVEL_COUNT; level++)
    {
        AddButton(LEVEL_SELECT, "Level " + std::to_string(level), BLUE, [this, level]()
        {
            m_iSelectedLevel = level;
            SetState(GAME);
        });
    }

    AddButton(LEVEL_SELECT, "Back", GREY, [this]()
    {
        SetState(MENU);
    });

    // Settings
    m_titles[SETTINGS] = "Settings";

    // A toggle updates its own text, so there is nothing to rebuild
    CButton& vsync = AddButton(SETTINGS, "VSync: ON", BLUE);
    vsync.SetOnClick([this, &vsync]()
    {
        m_bVSync = !m_bVSync;
        vsync.SetText(m_bVSync ? "VSync: ON" : "VSync: OFF");
    });

    CButton& volume = AddButton(SETTINGS, "Volume: 100%", GREEN);
    volume.SetOnClick([this, &volume]()
    {
        m_iVolume -= 10;
        if (m_iVolume < 0) m_iVolume = 100;
        volume.SetText("Volume: " + std::to_string(m_iVolume) + "%");
    });

    AddButton(SETTINGS, "Back", GREY, [this]()
    {
        SetState(MENU);
    });

    // Level Complete
    m_titles[LEVEL_COMPLETE] = "Level Complete";

    AddButton(LEVEL_COMPLETE, "Next Level", GREEN, [this]()
    {
        m_iSelectedLevel++;

        if (m_iSelectedLevel > LEVEL_COUNT)
        {
            m_iSelectedLevel = 1;
            SetState(MENU); // finished the last level
        }
        else
        {
            SetState(GAME);
        }
    });

    AddButton(LEVEL_COMPLETE, "Retry", BLUE, [this]()
    {
        SetState(GAME);
    });

    AddButton(LEVEL_COMPLETE, "Main Menu", GREY, [this]()
    {
        SetState(MENU);
    });

}

// Shit works

void CUIManager::HandleEvent(sf::RenderWindow& window)
{
    for (auto& button : m_buttons[m_eCurrentState])
    {
        button->HandleEvent(window);
    }
}

void CUIManager::Update(float _dT)
{
    for (auto& button : m_buttons[m_eCurrentState])
    {
        button->Update(_dT);
    }
}

void CUIManager::Draw(sf::RenderWindow& window)
{
    DrawTitle(window);

    for (auto& button : m_buttons[m_eCurrentState])
    {
        button->Draw(window);
    }

    // Labels last, so a HUD always sits on top
    for (auto& label : m_labels[m_eCurrentState])
    {
        label->Draw(window);
    }
}

void CUIManager::DrawTitle(sf::RenderWindow& window)
{
    const std::string& title = m_titles[m_eCurrentState];
    if (title.empty()) return;

    sf::Text text(m_font, title, 48);
    text.setFillColor(sf::Color::White);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
    text.setPosition({ m_vWindowSize.x / 2.0f, m_vWindowSize.y * 0.15f });

    window.draw(text);
}
