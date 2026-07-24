#include "cCube.h"

cCube::cCube(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic) : cGameObject(_Texture, _IsDynamic)
{
	m_ObjType = EObjectType::WALL;
}

cCube::~cCube()
{
}

void cCube::Start()
{
}

void cCube::Update()
{
}
