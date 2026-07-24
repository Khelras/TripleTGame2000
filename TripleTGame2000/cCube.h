#pragma once

#include "cGameObject.h"

class cCube : public cGameObject
{
public:

	cCube(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic);
	cCube(std::shared_ptr<sf::Texture> _Texture, bool _IsDynamic, sAnimationInfo _AnimInfo, int _FrameWidth, int _FrameHeight);
	~cCube();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
};

