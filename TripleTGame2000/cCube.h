#pragma once

#include "cGameObject.h"

class cCube : public cGameObject
{
public:

	cCube(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic);
	~cCube();

	virtual void Start() override;
	virtual void Update() override;

private:
};

