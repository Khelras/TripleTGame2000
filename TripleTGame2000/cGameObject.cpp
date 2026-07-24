#include "cGameObject.h"

cGameObject::cGameObject(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic)
{
	m_ObjType = EObjectType::NONE;
	m_IsDynamic = _IsDynamic;

	// Set Sprite origin
	sf::Vector2i HalfTexSize = m_SpriteRenderer.GetSprite()->getTextureRect().size / 2;
	m_SpriteRenderer.GetSprite()->setOrigin({ (float)HalfTexSize.x, (float)HalfTexSize.y });

	m_Angle = sf::degrees(0.0f);
}

cGameObject::cGameObject(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic, sAnimationInfo _AnimInfo, int _FrameWidth, int _FrameHeight)
{
	m_ObjType = EObjectType::NONE;
	m_IsDynamic = _IsDynamic;
	m_SpriteRenderer.SetAnimInfo(_AnimInfo);

	// Sprite Stuff
	m_SpriteRenderer.InitializeSprite(_Texture, _FrameWidth, _FrameHeight);
	m_SpriteRenderer.SetSpriteAnimation(_AnimInfo);
	SetPosition(m_Position);
}

cGameObject::~cGameObject()
{
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::Draw(sf::RenderWindow* _Window)
{
	_Window->draw(*m_SpriteRenderer.GetSprite());
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::SetPosition(sf::Vector2f _Pos)
{
	m_Position = _Pos;
	m_SpriteRenderer.GetSprite()->setPosition({ m_Position.x, m_Position.y });
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::AddPosition(sf::Vector2f _Pos)
{
	sf::Vector2f NewPos = m_Position + _Pos;
	m_Position = NewPos;

	m_SpriteRenderer.GetSprite()->setPosition({ m_Position.x, m_Position.y });
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void cGameObject::SetScale(sf::Vector2f _Scale)
{
	m_SpriteRenderer.GetSprite()->setScale(_Scale);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
sf::Sprite& cGameObject::GetSprite()
{
	return *m_SpriteRenderer.GetSprite();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
sf::Angle cGameObject::CalculateAngle(sf::Vector2f _Vector)
{
	return sf::radians(atan2(_Vector.y, _Vector.x));
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //