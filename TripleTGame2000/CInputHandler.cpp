/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : CInputHandler.cpp
Description : Handles keyboard and mouse input, tracking press, release, and movement states each frame
Author : Bryn Carter
Mail : bryn.carter@mds.ac.nz
**************************************************************************/
#include "CInputHandler.h"

CInputHandler* CInputHandler::instance = nullptr;

CInputHandler::~CInputHandler()
{
}

CInputHandler::CInputHandler()
{
    // Default controls
    m_bindings[PLAYER_ONE] = {
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::Space
    };

    m_bindings[PLAYER_TWO] = {
        sf::Keyboard::Key::Up,
        sf::Keyboard::Key::Down,
        sf::Keyboard::Key::Left,
        sf::Keyboard::Key::Right,
        sf::Keyboard::Key::Enter
    };
}

CInputHandler* CInputHandler::getInstance()
{
    if (instance == nullptr)
        instance = new CInputHandler();
    return instance;
}

void CInputHandler::UpdateInput()
{
    m_prevKeyDown = m_keyDown;
    for (int id = 0; id < sf::Keyboard::KeyCount; id++)
        m_keyDown[id] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(id));

    for (int id = 0; id < sf::Keyboard::KeyCount; id++) {
        m_keyPressed[id] = (m_keyDown[id] && !m_prevKeyDown[id]);
        m_keyReleased[id] = (!m_keyDown[id] && m_prevKeyDown[id]);
    }

    m_prevMouseDown = m_mouseDown;
    for (int id = 0; id < sf::Mouse::ButtonCount; id++)
        m_mouseDown[id] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(id));

    for (int id = 0; id < sf::Mouse::ButtonCount; id++) {
        m_mousePressed[id] = m_mouseDown[id] && !m_prevMouseDown[id];
        m_mouseReleased[id] = !m_mouseDown[id] && m_prevMouseDown[id];
    }

    // One movement vector per player, Uses the key states gathered above, so add a player and it just works.
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        const SBindings& keys = m_bindings[player];

        m_vInputVector[player] = sf::Vector2f(
            float(KeyHeld(keys.right) - KeyHeld(keys.left)),
            float(KeyHeld(keys.up) - KeyHeld(keys.down))
        );
    }
}

void CInputHandler::UpdateMousePos(sf::RenderWindow& window)
{
    m_mousePosPixels = sf::Mouse::getPosition(window);
}
