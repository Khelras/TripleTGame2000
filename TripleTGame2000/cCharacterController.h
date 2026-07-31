#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>

#include "cSpriteRenderer.h"
#include "CInputHandler.h"

enum class EGravityDirection
{
	Horizontal,
	Vertical
};

class cCharacterController
{
public:
	cCharacterController(b2World& _world, const sf::Vector2f& _startPos, EPlayer _player, EGravityDirection _movementAxis, std::shared_ptr<sf::Texture> _Texture);
	~cCharacterController();

	void Update(float _deltaTime, const sf::Vector2f& _Input);
	void DrawCharacters(sf::RenderWindow& _window);

	void FlipGravityDirection();
	void UpdateVisuals(float _deltaTime);

	// Getters
	b2Body* GetBody() const { return m_body; }

private:
	void CreatePhysicsBody(b2World& _world, const sf::Vector2f& _startPos);

	void ApplyMovement(const sf::Vector2f& _Input);
	void ApplyCustomGravity();
	void UpdateSprite();
	

	b2World* m_world = nullptr;
	EPlayer m_player;
	EGravityDirection m_movementAxis;
	b2Body* m_body = nullptr;
	cSpriteRenderer m_spriteRenderer;
	float m_movementSpeed = 5.0f;
	float m_gravityStrength = 9.81f;
	float m_GravityDirection = 1.0f; // 1.0 for down, -1.0 for up

	//Box 2D apparently works betteer when using meters instead of pixels, so we need to convert pixels to meters for the physics calculations
	static constexpr float PixelsPerMeter = 32.0f; // Conversion factor from pixels to meters 

};

