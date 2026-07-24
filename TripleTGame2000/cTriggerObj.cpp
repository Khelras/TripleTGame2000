#include "cTriggerObj.h"
#include "cTriggerableObj.h"

cTriggerObj::cTriggerObj(std::shared_ptr<sf::Texture> _NotTriggeredTex, std::shared_ptr<sf::Texture> _TriggeredTex, bool _IsDynamic) : cGameObject(_NotTriggeredTex, _IsDynamic)
{
	m_TriggeredTex = _TriggeredTex;
	m_NotTriggeredTex = _NotTriggeredTex;

	m_ObjType = EObjectType::TRIGGER;
	m_IsTriggered = false;
	m_ID = -1;
	m_IsTriggerOnContact = false;
	m_CanBeTriggered = true;
}

cTriggerObj::~cTriggerObj()
{
}

void cTriggerObj::ToggleIsTriggered()
{
	SetIsTriggered(!m_IsTriggered);
	m_CanBeTriggered = false;
}

void cTriggerObj::SetIsTriggered(bool _Triggered)
{
	// Lots of logic here
}

bool cTriggerObj::GetIsTriggered()
{
	return m_IsTriggered;
}

bool cTriggerObj::GetIsTriggerOnContact()
{
	return m_IsTriggerOnContact;
}

void cTriggerObj::SetConnectedActor(std::shared_ptr<cTriggerableObj> _TriggerableObj)
{
	m_ConnectedActors.push_back(_TriggerableObj);
}

void cTriggerObj::SetCanBeTriggered(bool _CanBeTriggered)
{
	m_CanBeTriggered = _CanBeTriggered;
}

bool cTriggerObj::GetCanBeTriggered()
{
	return m_CanBeTriggered;
}

std::shared_ptr<sf::Texture> cTriggerObj::GetTriggeredTex()
{
	return m_TriggeredTex;
}

std::shared_ptr<sf::Texture> cTriggerObj::GetNotTriggeredTex()
{
	return m_NotTriggeredTex;
}

void cTriggerObj::SetID(int _ID)
{
	m_ID = _ID;
}

int cTriggerObj::GetID()
{
	return m_ID;
}

