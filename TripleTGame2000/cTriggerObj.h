#pragma once

#include <SFML/Graphics.hpp>
#include "cGameObject.h"

class cTriggerableObj;

class cTriggerObj : public cGameObject
{
public:
	cTriggerObj(std::shared_ptr<sf::Texture> _NotTriggeredTex, std::shared_ptr<sf::Texture> _TriggeredTex, bool _IsDynamic);
	~cTriggerObj();

	// Purpose: Handles the logic for when 'E' is pressed while colliding
	virtual void EPressedWhileColliding() = 0;


	// Purpose: Toggles the trigger state
	void ToggleIsTriggered();

	// Purpose: Checks if the trigger activates on contact
	bool GetIsTriggerOnContact();

	// Purpose: Connects the trigger to a triggerable actor
	void SetConnectedActor(std::shared_ptr<cTriggerableObj> _TriggerableObj);


	// Purpose: Sets the triggered state
	void SetIsTriggered(bool _Triggered);

	// Purpose: Checks if the trigger is triggered
	bool GetIsTriggered();


	// Purpose: Sets whether the triggers can be triggered
	void SetCanBeTriggered(bool _CanBeTriggered);

	// Purpose: Checks if the trigger can be triggered
	bool GetCanBeTriggered();


	// Purpose: Gets the texture when triggered
	std::shared_ptr<sf::Texture> GetTriggeredTex();

	// Purpose: Gets the texture when not triggered
	std::shared_ptr<sf::Texture> GetNotTriggeredTex();


	// Purpose: Sets the triggers ID
	void SetID(int _ID);

	// Purpose: Gets the actors ID
	int GetID();


protected:
	std::vector<std::shared_ptr<cTriggerableObj>> m_ConnectedActors;
	int m_ID;
	bool m_IsTriggered;
	bool m_IsTriggerOnContact;
	bool m_CanBeTriggered;

	// Sprites
	std::shared_ptr<sf::Texture> m_TriggeredTex;
	std::shared_ptr<sf::Texture> m_NotTriggeredTex;
};

