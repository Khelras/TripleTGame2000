#include "cGameObject.h"

cGameObject::cGameObject(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic)
{
	m_Sprite = std::make_shared<sf::Sprite>(*_Texture);

	// Set Sprite origin
	sf::Vector2i HalfTexSize = m_Sprite->getTextureRect().size / 2;
	m_Sprite->setOrigin({ (float)HalfTexSize.x, (float)HalfTexSize.y });

	m_Angle = sf::degrees(0.0f);
}

cGameObject::~cGameObject()
{
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::Draw(sf::RenderWindow* _Window)
{
	_Window->draw(*m_Sprite);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::SetPosition(sf::Vector2f _Pos)
{
	m_Position = _Pos;
	m_Sprite->setPosition({ m_Position.x, m_Position.y });
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::AddPosition(sf::Vector2f _Pos)
{
	sf::Vector2f NewPos = m_Position + _Pos;
	m_Position = NewPos;

	m_Sprite->setPosition({ m_Position.x, m_Position.y });
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::SetScale(sf::Vector2f _Scale)
{
	m_Sprite->setScale(_Scale);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
sf::Sprite& cGameObject::GetSprite() const
{
	return *m_Sprite;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
sf::Angle cGameObject::CalculateAngle(sf::Vector2f _Vector)
{
	return sf::radians(atan2(_Vector.y, _Vector.x));
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //