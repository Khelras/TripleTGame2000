#pragma once

#include <SFML/Graphics.hpp>
#include "cSpriteRenderer.h"
#include <iostream>
#include <string>

enum EObjectType
{
	NONE = 0,
	WALL = 1,
	TRIGGER = 2,
	TRIGGERABLE = 3,
};

class cGameObject
{
public:
	cGameObject(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic);
	cGameObject(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic, sAnimationInfo _AnimInfo, int _FrameWidth, int _FrameHeight);
	~cGameObject();

	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;

	// Purpose: Draws Object to the window
	virtual void Draw(sf::RenderWindow* _Window);

	// Purpose: Sets the current position
	void SetPosition(sf::Vector2f _Pos);

	// Purpose: Adds to the current position
	void AddPosition(sf::Vector2f _Pos);

	void SetScale(sf::Vector2f _Scale);

	sf::Sprite& GetSprite();

	// Purpose: Caluclates an angle of the input vector
	sf::Angle CalculateAngle(sf::Vector2f _Vector);

	sf::Vector2f inline GetPosition() { return m_Position; }

protected:

	sf::Vector2f m_Position;
	sf::Angle m_Angle;
	cSpriteRenderer m_SpriteRenderer;
	bool m_IsDynamic;

	EObjectType m_ObjType;
};

