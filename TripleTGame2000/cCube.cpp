#include "cCube.h"

cCube::cCube(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic) : cGameObject(_Texture, _IsDynamic)
{
	m_ObjType = EObjectType::WALL;
}

cCube::cCube(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic, sAnimationInfo _AnimInfo, int _FrameWidth, int _FrameHeight) : cGameObject(_Texture, _IsDynamic, _AnimInfo, _FrameWidth, _FrameHeight)
{
	m_ObjType = EObjectType::WALL;
}

cCube::~cCube()
{
}

void cCube::Start()
{
}

void cCube::Update(float _DeltaTime)
{
	m_SpriteRenderer.UpdateSprite(_DeltaTime);
}
