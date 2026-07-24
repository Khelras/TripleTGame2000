#pragma once
#include "cGameObject.h"

class cTriggerableObj: public cGameObject
{
public:
	//cTriggerableObj(std::shared_ptr<sf::Texture> _AnimatedTex, bool _IsDynamic, int _FrameWidth, int _FrameHeight, int _StartX, int _StartY, int _EndX, int _EndY);
	cTriggerableObj(std::shared_ptr<sf::Texture> _NotTriggeredTex, std::shared_ptr<sf::Texture>_TriggeredTex, bool _IsDynamic);
	~cTriggerableObj();


	// Purpose: Sets the ID
	void SetID(int _id);

	// Purpose: Retrieves the ID
	int GetID();

	// Purpose: Checks if the triggerable has been triggered
	bool GetIsTriggered();

	// Purpose: Checks if the triggerable triggers when activated
	bool GetIsTriggeredOnActivate();

	// Purpose: Activates the trigger
	virtual void Activate() = 0;

	// Purpose: Deactivates the trigger
	virtual void Deactivate() = 0;

private:
	int m_ID;
	bool m_IsTriggered;
	bool m_IsTriggeredOnActivate = true;
	std::shared_ptr<sf::Texture> m_TriggeredSprite;
	std::shared_ptr<sf::Texture> m_NotTriggeredSprite;
};

