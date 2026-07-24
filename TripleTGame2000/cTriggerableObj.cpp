#include "cTriggerableObj.h"



//cTriggerableObj::cTriggerableObj(std::shared_ptr<sf::Texture> _AnimatedTex, bool _IsDynamic, int _FrameWidth, int _FrameHeight, int _StartX, int _StartY, int _EndX, int _EndY)
//{
//}

cTriggerableObj::cTriggerableObj(std::shared_ptr<sf::Texture> _NotTriggeredTex, std::shared_ptr<sf::Texture> _TriggeredTex, bool _IsDynamic) : cGameObject(_NotTriggeredTex, _IsDynamic)
{
}

cTriggerableObj::~cTriggerableObj()
{
}



bool cTriggerableObj::GetIsTriggered()
{
	return m_IsTriggered;
}

bool cTriggerableObj::GetIsTriggeredOnActivate()
{
	return m_IsTriggeredOnActivate;
}

void cTriggerableObj::SetID(int _ID)
{
	m_ID = _ID;
}

int cTriggerableObj::GetID()
{
	return m_ID;
}