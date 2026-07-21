/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : CButton.cpp
Description : Implements an interactive UI button that handles hover, press, and click behavior with visual feedback
Author : Bryn Carter
Mail : bryn.carter@mds.ac.nz
**************************************************************************/

#include "CButton.h"
#include <algorithm>

// sf::Color channels are 8 bit, so brightening has to be clamped or it wraps around
static sf::Color Shade(sf::Color color, int amount)
{
    return sf::Color((std::uint8_t)std::clamp((int)color.r + amount, 0, 255), (std::uint8_t)std::clamp((int)color.g + amount, 0, 255), (std::uint8_t)std::clamp((int)color.b + amount, 0, 255), color.a);
}

CButton::CButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string& text, const sf::Font& font, int fontSize, std::function<void()> onClick) : m_text(font, text, fontSize), m_onClick(std::move(onClick))
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(color);
    m_shape.setOrigin(size * 0.5f);

    m_idleColor = color;
    m_hoverColor = Shade(color, 20);
    m_pressColor = Shade(color, -20);

    m_text.setFillColor(sf::Color::White);
    CenterText();
}

void CButton::HandleEvent(sf::RenderWindow& window)
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool inside = m_shape.getGlobalBounds().contains(mouse);
    bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    m_hovered = inside && !m_pressed;

    // Pressed this frame
    if (inside && mouseDown && !m_wasMouseDown)
    {
        m_pressed = true;
        m_targetScale = 0.95f;
    }

    // Released this frame, counts as a click only if it started on this button
    if (!mouseDown && m_wasMouseDown)
    {
        if (m_pressed && inside && m_onClick)
        {
            m_onClick();
        }
        m_pressed = false;
        m_targetScale = 1.0f;
    }

    m_wasMouseDown = mouseDown;
}

void CButton::Update(float dt)
{
    m_currentScale += (m_targetScale - m_currentScale) * dt * 10.0f;
    m_shape.setScale({ m_currentScale, m_currentScale });

    if (m_pressed)
        m_shape.setFillColor(m_pressColor);
    else if (m_hovered)
        m_shape.setFillColor(m_hoverColor);
    else
        m_shape.setFillColor(m_idleColor);
}

void CButton::Draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
    window.draw(m_text);
}

void CButton::SetText(const std::string& text)
{
    m_text.setString(text);
    CenterText();
}

void CButton::CenterText()
{
    sf::FloatRect bounds = m_text.getLocalBounds();

    m_text.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });

    m_text.setPosition(m_shape.getPosition());
}
