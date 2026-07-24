/***********************************************************************
//Bachelor of Software Engineering
//Media Design School
//Auckland
//New Zealand
//(c) [2025] Media Design School
//File Name : cSpriteRenderer.h
//Description : Declaration of the SpriteRenderer class
// Author : Ariel Apfel
//Mail : ariel.apfel@mds.ac.nz
//**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

struct sAnimationInfo
{
	sAnimationInfo(int _xStart, int _yStart, int _xEnd, int _yEnd, float _AnimSpeed, int _LoopNum = -1)
	{
		m_IsAnimating = true;
		m_AnimXStart = _xStart;
		m_AnimYStart = _yStart;
		m_AnimXEnd = _xEnd;
		m_AnimYEnd = _yEnd;
		m_AnimXCurrent = 0;
		m_AnimYCurrent = 0;
		m_AnimSpeed = _AnimSpeed;
		m_AnimTimer = 0.0f;

		if (_LoopNum == 1) m_DoesAnimationLoop = false;
		else			   m_DoesAnimationLoop = true;
	}

	sAnimationInfo() 
	{
		m_IsAnimating = false;
	}

	bool m_IsAnimating = false;
	int m_AnimXStart = 0;
	int m_AnimYStart = 0;
	int m_AnimXEnd = 0;
	int m_AnimYEnd = 0;

	int m_AnimXCurrent = 0;
	int m_AnimYCurrent = 0;

	float m_AnimSpeed = 0.0f;
	float m_AnimTimer = 0.0f;

	int m_LoopAmount = -1;
	bool m_DoesAnimationLoop = true;
};

class cSpriteRenderer
{
public:
	cSpriteRenderer();
	~cSpriteRenderer();


	// Purpose: Initializes the sprite from a file path
	void InitializeSprite(std::shared_ptr<sf::Texture> _Texture);

	// Purpose: Initializes the sprite from a texture pointer with frame dimensions
	void InitializeSprite(std::shared_ptr<sf::Texture> _Texture, int _FrameWidth, int _FrameHeight);

	// Purpose: Flips the sprite horizontally if true
	void SetFlipH(bool _FlipX);

	// Purpose: Flips the sprite vertically if true
	void SetFlipY(bool _FlipY);

	// Purpose: Updates the sprite animation based on delta time
	void UpdateSprite(float _DeltaTime);

	// Purpose: Starts sprite animation from start to end frames, looping a specified amount (-1 = infinite)
	void SetSpriteAnimation(sAnimationInfo _AnimInfo);

	// Purpose: Sets the sprite to a specific frame, optionally disabling animation
	void SetSpriteFrame(int _XFrame, int _YFrame, bool _DisableAnimation = true);

	// Purpose: Sets the speed of the sprite animation
	void SetAnimationSpeed(float _Speed);

	// Purpose: Sets whether the current animation should loop
	void SetDoesnAnimLoop(bool _DoesAnimLoop);

	// Purpose: Returns Pointer to the sprite
	std::shared_ptr<sf::Sprite> GetSprite();

	// Purpose: Returns Pointer to the texture
	std::shared_ptr<sf::Texture> GetTexture();

	// Purpose: Returns Animation Info
	sAnimationInfo GetAnimInfo();

	inline void SetAnimInfo(sAnimationInfo _AnimInfo) { m_AnimInfo = _AnimInfo; }

private:
	std::shared_ptr<sf::Sprite> m_Sprite;
	std::shared_ptr<sf::Texture> m_Texture;
	sf::Vector2i m_FrameSize;
	sAnimationInfo m_AnimInfo;
};

