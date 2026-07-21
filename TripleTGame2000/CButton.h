/*
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : CButton.h
Description : Header file that defines the CButton class responsible for creating, displaying, and handling interactive button behavior in the UI
Author : Bryn Carter
Mail : bryn.carter@mds.ac.nz
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class CButton
{
public:
    // The button stores the action it runs, so there is no index to match up.
    CButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string& text, const sf::Font& font, int fontSize, std::function<void()> onClick = nullptr);

    void HandleEvent(sf::RenderWindow& window);
    void Update(float dt);
    void Draw(sf::RenderWindow& window);

    void SetText(const std::string& text);
    void SetOnClick(std::function<void()> onClick) { m_onClick = std::move(onClick); }

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    std::function<void()> m_onClick;

    bool m_hovered = false;
    bool m_pressed = false;
    bool m_wasMouseDown = false; // for detecting the click, no input manager needed

    sf::Color m_idleColor;
    sf::Color m_hoverColor;
    sf::Color m_pressColor;

    float m_targetScale = 1.0f;
    float m_currentScale = 1.0f;

    void CenterText();
};
