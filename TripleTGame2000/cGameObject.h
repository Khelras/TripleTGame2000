#pragma once

#include <SFML/Graphics.hpp>

enum EObjectType
{
	NONE = 0,
	WALL = 1,
};

class cGameObject
{
public:
	cGameObject(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic);
	~cGameObject();

	virtual void Start() = 0;
	virtual void Update() = 0;

	// Purpose: Draws Object to the window
	virtual void Draw(sf::RenderWindow* _Window);

	// Purpose: Sets the current position
	void SetPosition(sf::Vector2f _Pos);

	// Purpose: Adds to the current position
	void AddPosition(sf::Vector2f _Pos);

	void SetScale(sf::Vector2f _Scale);

	sf::Sprite& GetSprite() const;

	// Purpose: Caluclates an angle of the input vector
	sf::Angle CalculateAngle(sf::Vector2f _Vector);

	sf::Vector2f inline GetPosition() { return m_Position; }

protected:

	sf::Vector2f m_Position;
	sf::Angle m_Angle;
	std::shared_ptr<sf::Sprite> m_Sprite;
	bool m_IsDynamic;
};

